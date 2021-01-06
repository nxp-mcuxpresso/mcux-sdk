/*
 * Copyright 2019 NXP
 * All rights reserved.
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

#define APP_IMG_WIDTH  DEMO_BUFFER_WIDTH
#define APP_IMG_HEIGHT DEMO_BUFFER_HEIGHT

#define APP_PS_WIDTH  APP_IMG_WIDTH
#define APP_PS_HEIGHT APP_IMG_HEIGHT

/* AS frame is square. */
#if (APP_IMG_WIDTH > APP_IMG_HEIGHT)
#define APP_AS_WIDTH  APP_IMG_HEIGHT
#define APP_AS_HEIGHT APP_IMG_HEIGHT
#else
#define APP_AS_WIDTH  APP_IMG_WIDTH
#define APP_AS_HEIGHT APP_IMG_WIDTH
#endif

typedef uint16_t pixel_t;
#define APP_BPP            2U /* Use 16-bit RGB565 format. */
#define APP_RED            0xF100U
#define APP_BLUE           0x001FU
#define APP_GREEN          0x07E0U
#define APP_YELLOW         (APP_RED | APP_GREEN)
#define APP_PXP_PS_FORMAT  kPXP_PsPixelFormatRGB565
#define APP_PXP_AS_FORMAT  kPXP_AsPixelFormatRGB565
#define APP_PXP_OUT_FORMAT kPXP_OutputPixelFormatRGB565
#define APP_DC_FORMAT      kVIDEO_PixelFormatRGB565

/*
 * AS pixel format is RGB565, when compared with color key, the pixel
 * is extended to RGB888.
 */
#define APP_COLOR_KEY_LOW(color) ((((color)&APP_BLUE) << 3U) | (((color)&APP_GREEN) << 5U) | (((color)&APP_RED) << 8U))

#define APP_COLOR_KEY_HIGH(color) (APP_COLOR_KEY_LOW(color) | 0x070307U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void APP_InitInputBuffer(void);
static void APP_InitLcdif(void);
static void APP_InitPxp(void);
static void APP_BufferSwitchOffCallback(void *param, void *switchOffBuffer);

/*******************************************************************************
 * Variables
 ******************************************************************************/

AT_NONCACHEABLE_SECTION_ALIGN(static pixel_t s_BufferLcd[APP_IMG_HEIGHT][APP_IMG_WIDTH], FRAME_BUFFER_ALIGN);
AT_NONCACHEABLE_SECTION_ALIGN(static pixel_t s_psBufferPxp[APP_PS_HEIGHT][APP_PS_WIDTH], FRAME_BUFFER_ALIGN);
AT_NONCACHEABLE_SECTION_ALIGN(static pixel_t s_asBufferPxp[APP_AS_HEIGHT][APP_AS_WIDTH], FRAME_BUFFER_ALIGN);

/* PXP Output buffer config. */
static pxp_output_buffer_config_t outputBufferConfig;

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

    PRINTF("\r\nPXP Color Key example start...\r\n");

    APP_InitInputBuffer();
    APP_InitPxp();
    APP_InitLcdif();

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
    g_dc.ops->setFrameBuffer(&g_dc, 0, (void *)s_BufferLcd);

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

    /*
     * PS configure.
     *
     * PS is full screen background.
     */
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
    PXP_SetProcessSurfacePosition(APP_PXP, 0, 0, APP_IMG_WIDTH - 1U, APP_IMG_HEIGHT - 1U);

    /*
     * AS config.
     *
     * AS frame buffer is square, placed in the center of the screen.
     */
    const pxp_as_buffer_config_t asBufferConfig = {
        .pixelFormat = APP_PXP_AS_FORMAT,
        .bufferAddr  = (uint32_t)s_asBufferPxp,
        .pitchBytes  = APP_AS_WIDTH * APP_BPP,
    };

    PXP_SetAlphaSurfaceBufferConfig(APP_PXP, &asBufferConfig);

    /* AS in the center of the screen. */
    PXP_SetAlphaSurfacePosition(APP_PXP, (APP_IMG_WIDTH - APP_AS_WIDTH) / 2, (APP_IMG_HEIGHT - APP_AS_HEIGHT) / 2,
                                (APP_IMG_WIDTH + APP_AS_WIDTH) / 2 - 1, (APP_IMG_HEIGHT + APP_AS_HEIGHT) / 2 - 1);

    /*
     * Blend config.
     *
     * AS pixel format is RGB565, so the global alpha is used here for the
     * alpha blend.
     */
    const pxp_as_blend_config_t asBlendConfig = {
        .alpha = 128U, .invertAlpha = false, .alphaMode = kPXP_AlphaOverride, .ropMode = kPXP_RopMergeAs};

    PXP_SetAlphaSurfaceBlendConfig(APP_PXP, &asBlendConfig);

    /* Color key. */
    PXP_SetAlphaSurfaceOverlayColorKey(APP_PXP, APP_COLOR_KEY_LOW(APP_YELLOW), APP_COLOR_KEY_HIGH(APP_YELLOW));
    PXP_EnableAlphaSurfaceOverlayColorKey(APP_PXP, true);

    /* Output config. */
    outputBufferConfig.pixelFormat    = APP_PXP_OUT_FORMAT;
    outputBufferConfig.interlacedMode = kPXP_OutputProgressive;
    outputBufferConfig.buffer0Addr    = (uint32_t)s_BufferLcd;
    outputBufferConfig.buffer1Addr    = 0U;
    outputBufferConfig.pitchBytes     = APP_IMG_WIDTH * APP_BPP;
    outputBufferConfig.width          = APP_IMG_WIDTH;
    outputBufferConfig.height         = APP_IMG_HEIGHT;

    PXP_SetOutputBufferConfig(APP_PXP, &outputBufferConfig);

    /* Disable CSC1, it is enabled by default. */
    PXP_EnableCsc1(APP_PXP, false);

    /* Start PXP. */
    PXP_Start(APP_PXP);

    /* Wait for process complete. */
    while (!(kPXP_CompleteFlag & PXP_GetStatusFlags(APP_PXP)))
    {
    }

    PXP_ClearStatusFlags(APP_PXP, kPXP_CompleteFlag);
}

static void APP_InitInputBuffer(void)
{
    uint32_t i, j;

    /* PS buffer. */
#if (APP_IMG_HEIGHT > APP_IMG_WIDTH)
    for (i = 0; i < APP_PS_HEIGHT / 2; i++)
    {
        for (j = 0; j < APP_PS_WIDTH; j++)
        {
            s_psBufferPxp[i][j] = APP_BLUE;
        }
    }

    for (; i < APP_PS_HEIGHT; i++)
    {
        for (j = 0; j < APP_PS_WIDTH; j++)
        {
            s_psBufferPxp[i][j] = APP_RED;
        }
    }
#else
    for (i = 0; i < APP_PS_HEIGHT; i++)
    {
        for (j = 0; j < APP_PS_WIDTH / 2; j++)
        {
            s_psBufferPxp[i][j] = APP_BLUE;
        }

        for (; j < APP_PS_WIDTH; j++)
        {
            s_psBufferPxp[i][j] = APP_RED;
        }
    }
#endif

    /* AS buffer. */
    for (i = 0; i < APP_AS_HEIGHT; i++)
    {
        for (j = 0; j < APP_AS_WIDTH; j++)
        {
            s_asBufferPxp[i][j] = APP_GREEN;
        }
    }

    for (i = APP_AS_HEIGHT / 4; i < (APP_AS_HEIGHT * 3) / 4; i++)
    {
        for (j = APP_AS_WIDTH / 4; j < (APP_AS_WIDTH * 3) / 4; j++)
        {
            s_asBufferPxp[i][j] = APP_YELLOW;
        }
    }

    /* Output buffer. */
    memset(s_BufferLcd, 0x0U, sizeof(s_BufferLcd));
}

static void APP_BufferSwitchOffCallback(void *param, void *switchOffBuffer)
{
    s_newFrameShown = true;
}
