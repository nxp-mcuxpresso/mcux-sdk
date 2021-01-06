/*
 * Copyright  2017-2019 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_elcdif.h"
#include "fsl_debug_console.h"

#include "fsl_gpio.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define APP_ELCDIF LCDIF

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
#define APP_DATA_BUS 16

/* Display. */
#define LCD_DISP_GPIO     GPIO1
#define LCD_DISP_GPIO_PIN 2
/* Back light. */
#define LCD_BL_GPIO     GPIO2
#define LCD_BL_GPIO_PIN 31

/* Frame buffer data alignment, for better performance, the LCDIF frame buffer should be 64B align. */
#define FRAME_BUFFER_ALIGN 64


/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void BOARD_EnableLcdInterrupt(void);
/* How many frames to show before swithing to the other picture. */
#define APP_FRAME_PER_PIC 60

/*******************************************************************************
 * Variables
 ******************************************************************************/
static volatile uint32_t s_curFrame = 0; /* Frame counting. */

AT_NONCACHEABLE_SECTION_ALIGN(static uint8_t s_frameBuffer[APP_IMG_HEIGHT][APP_IMG_WIDTH], FRAME_BUFFER_ALIGN);

uint32_t lutData[2][ELCDIF_LUT_ENTRY_NUM];

/*******************************************************************************
 * Code
 ******************************************************************************/
extern void APP_LCDIF_IRQHandler(void);

void LCDIF_IRQHandler(void)
{
    APP_LCDIF_IRQHandler();
}

/* Enable interrupt. */
void BOARD_EnableLcdInterrupt(void)
{
    EnableIRQ(LCDIF_IRQn);
}

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

    GPIO_PinWrite(LCD_DISP_GPIO, LCD_DISP_GPIO_PIN, 0);

    while (i--)
    {
    }

    GPIO_PinWrite(LCD_DISP_GPIO, LCD_DISP_GPIO_PIN, 1);

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


void APP_LCDIF_IRQHandler(void)
{
    uint32_t intStatus;

    intStatus = ELCDIF_GetInterruptStatus(APP_ELCDIF);

    ELCDIF_ClearInterruptStatus(APP_ELCDIF, intStatus);

    if (intStatus & kELCDIF_CurFrameDone)
    {
        s_curFrame++;
    }
    SDK_ISR_EXIT_BARRIER;
}

void APP_ELCDIF_Init(void)
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
        .bufferAddr    = (uint32_t)s_frameBuffer,
        .pixelFormat   = kELCDIF_PixelFormatRAW8,
        .dataBus       = kELCDIF_DataBus8Bit,
    };

    ELCDIF_RgbModeInit(APP_ELCDIF, &config);
#if (defined(APP_ELCDIF_HAS_DISPLAY_INTERFACE) && APP_ELCDIF_HAS_DISPLAY_INTERFACE)
    BOARD_InitDisplayInterface();
#endif

    /* Load the LUT data. */
    ELCDIF_UpdateLut(APP_ELCDIF, kELCDIF_Lut0, 0, lutData[0], ELCDIF_LUT_ENTRY_NUM);
    ELCDIF_UpdateLut(APP_ELCDIF, kELCDIF_Lut1, 0, lutData[1], ELCDIF_LUT_ENTRY_NUM);

    ELCDIF_EnableLut(APP_ELCDIF, true);
}

uint32_t APP_MakeLutData(uint8_t r, uint8_t g, uint8_t b)
{
#if (APP_DATA_BUS == 16)
    /* 16 bit data bus. */
    return (((r >> 3)) << 11) | (((g >> 2)) << 5) | (((b >> 3)) << 0);
#else
    /* 24-bit data bus. */
    return (r << 16) | (g << 8) | (b << 0);
#endif
}

/*
 * Fill the LUT data.
 *
 * The first LUT memory is red, the second LUT memory is blue.
 */
void APP_FillLutData(void)
{
    uint32_t i;

    for (i = 0; i < ELCDIF_LUT_ENTRY_NUM; i++)
    {
        lutData[0][i] = APP_MakeLutData(i, 0, 0);
    }

    for (i = 0; i < ELCDIF_LUT_ENTRY_NUM; i++)
    {
        lutData[1][i] = APP_MakeLutData(0, 0, i);
    }
}

/*
 * Fill the frame buffer.
 *
 * The color degree changes in horizontal direction.
 */
void APP_FillFrameBuffer(void)
{
    uint32_t i, j;

    for (i = 0; i < APP_IMG_HEIGHT; i++)
    {
        for (j = 0; j < APP_IMG_WIDTH; j++)
        {
            s_frameBuffer[i][j] = j;
        }
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    uint32_t lutIndex    = 0;
    uint32_t frameToWait = 0;

    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_InitSemcPins();
    BOARD_BootClockRUN();
    BOARD_InitLcdifPixelClock();
    BOARD_InitDebugConsole();
    BOARD_InitLcd();

    PRINTF("LCDIF LUT example start...\r\n");

    /* Clear the frame buffer. */
    memset(s_frameBuffer, 0, sizeof(s_frameBuffer));

    APP_FillLutData();
    APP_FillFrameBuffer();

    APP_ELCDIF_Init();

    BOARD_EnableLcdInterrupt();

    ELCDIF_EnableInterrupts(APP_ELCDIF, kELCDIF_CurFrameDoneInterruptEnable);
    ELCDIF_RgbModeStart(APP_ELCDIF);

    while (1)
    {
        frameToWait += APP_FRAME_PER_PIC;

        while (frameToWait != s_curFrame)
        {
        }

        lutIndex ^= 1U;

        /* The LSB of frame buffer determines which LUT memory to use. */
        ELCDIF_SetNextBufferAddr(APP_ELCDIF, (uint32_t)s_frameBuffer | lutIndex);
    }
}
