/*
 * Copyright  2017 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_pxp.h"
#include "fsl_elcdif.h"

#include "fsl_gpio.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define APP_ELCDIF LCDIF
#define APP_PXP    PXP

#define APP_IMG_HEIGHT 272
#define APP_IMG_WIDTH  480
#define APP_HSW        41
#define APP_HFP        4
#define APP_HBP        8
#define APP_VSW        10
#define APP_VFP        4
#define APP_VBP        2
#define APP_POL_FLAGS \
    (kELCDIF_DataEnableActiveHigh | kELCDIF_VsyncActiveLow | kELCDIF_HsyncActiveLow | kELCDIF_DriveDataOnRisingClkEdge)

/* Display. */
#define LCD_DISP_GPIO     GPIO1
#define LCD_DISP_GPIO_PIN 2
/* Back light. */
#define LCD_BL_GPIO     GPIO2
#define LCD_BL_GPIO_PIN 31

#define APP_LCDIF_DATA_BUS kELCDIF_DataBus16Bit

/*
 * Frame buffer data alignment.
 * The PXP input buffer, output buffer, and LCDIF frame buffer address 64B align.
 */
#define FRAME_BUFFER_ALIGN 64

/* PS input buffer is square. */
#define APP_PS_WIDTH  (APP_IMG_WIDTH / 2U)
#define APP_PS_HEIGHT (APP_IMG_HEIGHT / 2U)
#define APP_AS_WIDTH  (APP_IMG_WIDTH / 2U)
#define APP_AS_HEIGHT (APP_IMG_HEIGHT / 2U)

#define APP_PS_ULC_X ((APP_IMG_WIDTH / 2) - (APP_PS_SIZE / 2))
#define APP_PS_ULC_Y ((APP_IMG_HEIGHT / 2) - (APP_PS_SIZE / 2))
#define APP_PS_LRC_X ((APP_IMG_WIDTH / 2) + (APP_PS_SIZE / 2) - 1U)
#define APP_PS_LRC_Y ((APP_IMG_HEIGHT / 2) + (APP_PS_SIZE / 2) - 1U)

#if (defined(USE_RGB565) && USE_RGB565)

typedef uint16_t pixel_t;
#define APP_BPP            2U /* Use 16-bit RGB565 format. */
#define APP_RED            0xF100U
#define APP_GREEN          0x07E0U
#define APP_BLUE           0x001FU
#define APP_PXP_PS_FORMAT  kPXP_PsPixelFormatRGB565
#define APP_PXP_AS_FORMAT  kPXP_AsPixelFormatRGB565
#define APP_PXP_OUT_FORMAT kPXP_OutputPixelFormatRGB565
#define APP_DC_FORMAT      kVIDEO_PixelFormatRGB565
#define APP_LCDIF_FORMAT   kELCDIF_PixelFormatRGB565

#else

typedef uint32_t pixel_t;
#define APP_BPP            4U /* Use 32-bit XRGB888 format. */
#define APP_RED            0x00FF0000U
#define APP_GREEN          0x0000FF00U
#define APP_BLUE           0x000000FFU
#define APP_PXP_PS_FORMAT  kPXP_PsPixelFormatRGB888
#define APP_PXP_AS_FORMAT  kPXP_AsPixelFormatRGB888
#define APP_PXP_OUT_FORMAT kPXP_OutputPixelFormatRGB888
#define APP_DC_FORMAT      kVIDEO_PixelFormatXRGB8888
#define APP_LCDIF_FORMAT   kELCDIF_PixelFormatXRGB8888

#endif

#ifndef APP_LCDIF_DATA_BUS
#define APP_LCDIF_DATA_BUS kELCDIF_DataBus24Bit
#endif
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void APP_InitInputBuffer(void);
static void APP_InitLcdif(void);
static void APP_InitPxp(void);
static void APP_HandShake(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*
 * In this example, the PXP block size is 8*8, so the buffer for hand shake
 * should be 16 lines.
 */
AT_NONCACHEABLE_SECTION_ALIGN(static pixel_t s_HandShakeBuffer[8 * 2][APP_IMG_WIDTH], FRAME_BUFFER_ALIGN);
AT_NONCACHEABLE_SECTION_ALIGN(static pixel_t s_psBufferPxp[APP_PS_HEIGHT][APP_PS_WIDTH], FRAME_BUFFER_ALIGN);
AT_NONCACHEABLE_SECTION_ALIGN(static pixel_t s_asBufferPxp[APP_AS_HEIGHT][APP_AS_WIDTH], FRAME_BUFFER_ALIGN);

/*******************************************************************************
 * Code
 ******************************************************************************/

/* Initialize the LCD_DISP. */
void BOARD_InitLcd(void)
{
    volatile uint32_t i = 0x1000U;

    gpio_pin_config_t config = {
        kGPIO_DigitalOutput,
        0,
        kGPIO_NoIntmode,
    };

    /* Reset the LCD. */
    GPIO_PinInit(LCD_DISP_GPIO, LCD_DISP_GPIO_PIN, &config);

    GPIO_WritePinOutput(LCD_DISP_GPIO, LCD_DISP_GPIO_PIN, 0);

    while (i--)
    {
    }

    GPIO_WritePinOutput(LCD_DISP_GPIO, LCD_DISP_GPIO_PIN, 1);

    /* Backlight. */
    config.outputLogic = 1;
    GPIO_PinInit(LCD_BL_GPIO, LCD_BL_GPIO_PIN, &config);
}

void BOARD_InitLcdifPixelClock(void)
{
    /*
     * The desired output frame rate is 60Hz. So the pixel clock frequency is:
     * (480 + 41 + 4 + 18) * (272 + 10 + 4 + 2) * 60 = 9.2M.
     * Here set the LCDIF pixel clock to 9.3M.
     */

    /*
     * Initialize the Video PLL.
     * Video PLL output clock is OSC24M * (loopDivider + (denominator / numerator)) / postDivider = 93MHz.
     */
    clock_video_pll_config_t config = {
        .loopDivider = 31,
        .postDivider = 8,
        .numerator   = 0,
        .denominator = 0,
    };

    CLOCK_InitVideoPll(&config);

    /*
     * 000 derive clock from PLL2
     * 001 derive clock from PLL3 PFD3
     * 010 derive clock from PLL5
     * 011 derive clock from PLL2 PFD0
     * 100 derive clock from PLL2 PFD1
     * 101 derive clock from PLL3 PFD1
     */
    CLOCK_SetMux(kCLOCK_LcdifPreMux, 2);

    CLOCK_SetDiv(kCLOCK_LcdifPreDiv, 4);

    CLOCK_SetDiv(kCLOCK_LcdifDiv, 1);
}


int main(void)
{
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitLcdifPixelClock();
    BOARD_InitDebugConsole();
    BOARD_InitLcd();

    PRINTF("\r\nPXP LCDIF hand shake example start...\r\n");

    APP_InitInputBuffer();
    APP_InitLcdif();
    APP_InitPxp();
    APP_HandShake();

    while (1)
    {
    }
}

static void APP_InitLcdif(void)
{
    const elcdif_rgb_mode_config_t config = {
        .panelWidth    = APP_IMG_WIDTH,
        .panelHeight   = APP_IMG_HEIGHT,
        .hsw           = APP_HSW,
        .hfp           = APP_HFP,
        .hbp           = APP_HBP,
        .vsw           = APP_VSW,
        .vfp           = APP_VFP,
        .vbp           = APP_VBP,
        .polarityFlags = APP_POL_FLAGS,
        .bufferAddr    = (uint32_t)s_HandShakeBuffer,
        .pixelFormat   = APP_LCDIF_FORMAT,
        .dataBus       = APP_LCDIF_DATA_BUS,
    };

#if (defined(APP_ELCDIF_HAS_DISPLAY_INTERFACE) && APP_ELCDIF_HAS_DISPLAY_INTERFACE)
    BOARD_InitDisplayInterface();
#endif

    ELCDIF_RgbModeInit(APP_ELCDIF, &config);

    ELCDIF_EnablePxpHandShake(APP_ELCDIF, true);

    ELCDIF_RgbModeStart(APP_ELCDIF);
}

static void APP_InitPxp(void)
{
    PXP_Init(APP_PXP);

    /* PS configure. */
    const pxp_ps_buffer_config_t psBufferConfig = {
        .pixelFormat = APP_PXP_PS_FORMAT,
        .swapByte    = false,
        .bufferAddr  = (uint32_t)s_psBufferPxp,
        .bufferAddrU = 0U,
        .bufferAddrV = 0U,
        .pitchBytes  = APP_PS_WIDTH * APP_BPP,
    };

    PXP_SetProcessSurfaceBackGroundColor(APP_PXP, 0U);

    PXP_SetProcessSurfaceBufferConfig(APP_PXP, &psBufferConfig);

    /* AS config. */
    const pxp_as_buffer_config_t asBufferConfig = {
        .pixelFormat = APP_PXP_AS_FORMAT,
        .bufferAddr  = (uint32_t)s_asBufferPxp,
        .pitchBytes  = APP_AS_WIDTH * APP_BPP,
    };

    const pxp_as_blend_config_t asBlendConfig = {.alpha       = 0U,    /* Don't care. */
                                                 .invertAlpha = false, /* Don't care. */
                                                 .alphaMode   = kPXP_AlphaRop,
                                                 .ropMode     = kPXP_RopMergeAs};

    PXP_SetAlphaSurfaceBufferConfig(APP_PXP, &asBufferConfig);
    PXP_SetAlphaSurfaceBlendConfig(APP_PXP, &asBlendConfig);

    /* Output config. */
    const pxp_output_buffer_config_t outputBufferConfig = {
        .pixelFormat    = APP_PXP_OUT_FORMAT,
        .interlacedMode = kPXP_OutputProgressive,
        .buffer0Addr    = (uint32_t)s_HandShakeBuffer,
        .buffer1Addr    = 0U,
        .pitchBytes     = APP_IMG_WIDTH * APP_BPP,
        .width          = APP_IMG_WIDTH,
        .height         = APP_IMG_HEIGHT,
    };

    PXP_SetOutputBufferConfig(APP_PXP, &outputBufferConfig);

    /* Disable CSC1, it is enabled by default. */
    PXP_EnableCsc1(APP_PXP, false);

    PXP_SetProcessBlockSize(APP_PXP, kPXP_BlockSize8);

    PXP_EnableLcdHandShake(APP_PXP, true);
}

static void APP_HandShake(void)
{
    int8_t psIncX   = 1;
    int8_t psIncY   = 1;
    int8_t asIncX   = -1;
    int8_t asIncY   = -1;
    uint16_t psUlcX = 0U;
    uint16_t psUlcY = 0U;
    uint16_t asUlcX = APP_IMG_WIDTH - APP_AS_WIDTH;
    uint16_t asUlcY = APP_IMG_HEIGHT - APP_AS_HEIGHT;
    uint16_t psLrcX, psLrcY, asLrcX, asLrcY;

    psLrcX = psUlcX + APP_PS_WIDTH - 1U;
    psLrcY = psUlcY + APP_PS_HEIGHT - 1U;
    asLrcX = asUlcX + APP_AS_WIDTH - 1U;
    asLrcY = asUlcY + APP_AS_HEIGHT - 1U;

    for (;;)
    {
        /* Prepare next buffer for LCD. */
        PXP_SetProcessSurfacePosition(APP_PXP, psUlcX, psUlcY, psLrcX, psLrcY);
        PXP_SetAlphaSurfacePosition(APP_PXP, asUlcX, asUlcY, asLrcX, asLrcY);

        /* Start PXP. */
        PXP_Start(APP_PXP);

        psLrcX += psIncX;
        psLrcY += psIncY;
        asLrcX += asIncX;
        asLrcY += asIncY;
        psUlcX += psIncX;
        psUlcY += psIncY;
        asUlcX += asIncX;
        asUlcY += asIncY;

        if (0 == asUlcX)
        {
            asIncX = 1;
        }
        else if (APP_IMG_WIDTH - 1 == asLrcX)
        {
            asIncX = -1;
        }

        if (0 == asUlcY)
        {
            asIncY = 1;
        }
        else if (APP_IMG_HEIGHT - 1 == asLrcY)
        {
            asIncY = -1;
        }

        if (0 == psUlcX)
        {
            psIncX = 1;
        }
        else if (APP_IMG_WIDTH - 1 == psLrcX)
        {
            psIncX = -1;
        }

        if (0 == psUlcY)
        {
            psIncY = 1;
        }
        else if (APP_IMG_HEIGHT - 1 == psLrcY)
        {
            psIncY = -1;
        }

        /* Wait for process complete. */
        while (!(kPXP_CompleteFlag & PXP_GetStatusFlags(APP_PXP)))
        {
        }

        PXP_ClearStatusFlags(APP_PXP, kPXP_CompleteFlag);
    }
}

static void APP_InitInputBuffer(void)
{
    uint32_t i, j;

    /* The PS buffer is BLUE rectangle, the AS buffer is RED rectangle. */

    for (i = 0; i < APP_PS_HEIGHT; i++)
    {
        for (j = 0; j < APP_PS_WIDTH; j++)
        {
            s_psBufferPxp[i][j] = APP_BLUE;
        }
    }

    for (i = 0; i < APP_PS_HEIGHT; i++)
    {
        for (j = 0; j < APP_PS_WIDTH; j++)
        {
            s_asBufferPxp[i][j] = APP_RED;
        }
    }

    memset(s_HandShakeBuffer, 0x0U, sizeof(s_HandShakeBuffer));
}
