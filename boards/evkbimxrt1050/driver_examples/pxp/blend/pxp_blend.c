/*
 * Copyright  2017-2019 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_pxp.h"
#include "display_support.h"

#include "fsl_gpio.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define APP_PXP PXP

/* Use RGB565 or XRGB8888 */
#define USE_RGB565 0

#define APP_IMG_WIDTH  DEMO_BUFFER_WIDTH
#define APP_IMG_HEIGHT DEMO_BUFFER_HEIGHT

#define APP_PS_WIDTH  (APP_IMG_WIDTH / 2U)
#define APP_PS_HEIGHT (APP_IMG_HEIGHT / 2U)
#define APP_AS_WIDTH  (APP_IMG_WIDTH / 2U)
#define APP_AS_HEIGHT (APP_IMG_HEIGHT / 2U)

#define APP_PS_ULC_X ((APP_IMG_WIDTH / 2) - (APP_PS_SIZE / 2))
#define APP_PS_ULC_Y ((APP_IMG_HEIGHT / 2) - (APP_PS_SIZE / 2))
#define APP_PS_LRC_X ((APP_IMG_WIDTH / 2) + (APP_PS_SIZE / 2) - 1U)
#define APP_PS_LRC_Y ((APP_IMG_HEIGHT / 2) + (APP_PS_SIZE / 2) - 1U)

#if USE_RGB565

typedef uint16_t pixel_t;
#define APP_BPP            2U /* Use 16-bit RGB565 format. */
#define APP_RED            0xF100U
#define APP_BLUE           0x001FU
#define APP_PXP_PS_FORMAT  kPXP_PsPixelFormatRGB565
#define APP_PXP_AS_FORMAT  kPXP_AsPixelFormatRGB565
#define APP_PXP_OUT_FORMAT kPXP_OutputPixelFormatRGB565
#define APP_DC_FORMAT      kVIDEO_PixelFormatRGB565

#else

typedef uint32_t pixel_t;
#define APP_BPP            4U /* Use 32-bit XRGB888 format. */
#define APP_RED            0x00FF0000U
#define APP_BLUE           0x000000FFU
#define APP_PXP_PS_FORMAT  kPXP_PsPixelFormatRGB888
#define APP_PXP_AS_FORMAT  kPXP_AsPixelFormatRGB888
#define APP_PXP_OUT_FORMAT kPXP_OutputPixelFormatRGB888
#define APP_DC_FORMAT      kVIDEO_PixelFormatXRGB8888

#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void APP_InitInputBuffer(void);
static void APP_InitLcdif(void);
static void APP_InitPxp(void);
static void APP_Blend(void);
static void APP_BufferSwitchOffCallback(void *param, void *switchOffBuffer);

/*******************************************************************************
 * Variables
 ******************************************************************************/

AT_NONCACHEABLE_SECTION_ALIGN(static pixel_t s_BufferLcd[2][APP_IMG_HEIGHT][APP_IMG_WIDTH], FRAME_BUFFER_ALIGN);
AT_NONCACHEABLE_SECTION_ALIGN(static pixel_t s_psBufferPxp[APP_PS_HEIGHT][APP_PS_WIDTH], FRAME_BUFFER_ALIGN);
AT_NONCACHEABLE_SECTION_ALIGN(static pixel_t s_asBufferPxp[APP_AS_HEIGHT][APP_AS_WIDTH], FRAME_BUFFER_ALIGN);

/* PXP Output buffer config. */
static pxp_output_buffer_config_t outputBufferConfig;

static uint8_t curLcdBufferIdx = 0;

/*
 * When new frame buffer sent to display, it might not be shown immediately.
 * Application could use callback to get new frame shown notification, at the
 * same time, when this flag is set, application could write to the older
 * frame buffer.
 */
static volatile bool s_newFrameShown = false;
static dc_fb_info_t fbInfo;

/*******************************************************************************
 * Code
 ******************************************************************************/

int main(void)
{
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\nPXP Blend example start...\r\n");

    APP_InitInputBuffer();
    APP_InitPxp();
    APP_InitLcdif();
    APP_Blend();

    while (1)
    {
    }
}

static void APP_InitLcdif(void)
{
    status_t status;

    BOARD_PrepareDisplayController();

    status = g_dc.ops->init(&g_dc);
    if (kStatus_Success != status)
    {
        PRINTF("Display initialization failed\r\n");
        assert(0);
    }

    g_dc.ops->getLayerDefaultConfig(&g_dc, 0, &fbInfo);
    fbInfo.pixelFormat = APP_DC_FORMAT;
    fbInfo.width       = APP_IMG_WIDTH;
    fbInfo.height      = APP_IMG_HEIGHT;
    fbInfo.startX      = DEMO_BUFFER_START_X;
    fbInfo.startY      = DEMO_BUFFER_START_Y;
    fbInfo.strideBytes = APP_IMG_WIDTH * APP_BPP;
    g_dc.ops->setLayerConfig(&g_dc, 0, &fbInfo);

    g_dc.ops->setCallback(&g_dc, 0, APP_BufferSwitchOffCallback, NULL);

    s_newFrameShown = false;
    g_dc.ops->setFrameBuffer(&g_dc, 0, (void *)s_BufferLcd[curLcdBufferIdx]);

    /* For the DBI interface display, application must wait for the first
     * frame buffer sent to the panel.
     */
    if ((g_dc.ops->getProperty(&g_dc) & kDC_FB_ReserveFrameBuffer) == 0)
    {
        while (s_newFrameShown == false)
        {
        }
    }

    s_newFrameShown = true;

    g_dc.ops->enableLayer(&g_dc, 0);
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
    outputBufferConfig.pixelFormat    = APP_PXP_OUT_FORMAT;
    outputBufferConfig.interlacedMode = kPXP_OutputProgressive;
    outputBufferConfig.buffer0Addr    = (uint32_t)s_BufferLcd[0];
    outputBufferConfig.buffer1Addr    = 0U;
    outputBufferConfig.pitchBytes     = APP_IMG_WIDTH * APP_BPP;
    outputBufferConfig.width          = APP_IMG_WIDTH;
    outputBufferConfig.height         = APP_IMG_HEIGHT;

    PXP_SetOutputBufferConfig(APP_PXP, &outputBufferConfig);

    /* Disable CSC1, it is enabled by default. */
    PXP_EnableCsc1(APP_PXP, false);
}

static void APP_Blend(void)
{
    uint8_t curLcdBufferIdx = 1U;
    int8_t psIncX           = 1;
    int8_t psIncY           = 1;
    int8_t asIncX           = -1;
    int8_t asIncY           = -1;
    uint16_t psUlcX         = 0U;
    uint16_t psUlcY         = 0U;
    uint16_t asUlcX         = APP_IMG_WIDTH - APP_AS_WIDTH;
    uint16_t asUlcY         = APP_IMG_HEIGHT - APP_AS_HEIGHT;
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

        /*
         * Wait for the new set frame buffer active, so that the older frame
         * buffer is inactive, then PXP could output to the older frame buffer.
         */
        while (s_newFrameShown == false)
        {
        }

        /* Switch to the other LCD buffer. */
        curLcdBufferIdx ^= 1U;

        outputBufferConfig.buffer0Addr = (uint32_t)s_BufferLcd[curLcdBufferIdx];
        PXP_SetOutputBufferConfig(APP_PXP, &outputBufferConfig);

        /* Start PXP. */
        PXP_Start(APP_PXP);

        /* Wait for process complete. */
        while (!(kPXP_CompleteFlag & PXP_GetStatusFlags(APP_PXP)))
        {
        }

        PXP_ClearStatusFlags(APP_PXP, kPXP_CompleteFlag);

        s_newFrameShown = false;
        g_dc.ops->setFrameBuffer(&g_dc, 0, (void *)s_BufferLcd[curLcdBufferIdx]);

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

    memset(s_BufferLcd, 0x0U, sizeof(s_BufferLcd));
}

static void APP_BufferSwitchOffCallback(void *param, void *switchOffBuffer)
{
    s_newFrameShown = true;
}
