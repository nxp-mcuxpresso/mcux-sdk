/*
 * Copyright 2019-2020 NXP
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

#define APP_BPP            4U /* Use 32-bit XRGB888 format. */
#define APP_PXP_PS_FORMAT  kPXP_PsPixelFormatRGB888
#define APP_PXP_AS_FORMAT  kPXP_AsPixelFormatARGB8888
#define APP_PXP_OUT_FORMAT kPXP_OutputPixelFormatARGB8888
#define APP_DC_FORMAT      kVIDEO_PixelFormatXRGB8888

typedef struct
{
    pxp_porter_duff_blend_mode_t mode;
    char *name;
} porter_duff_mode_name_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void APP_InitInputBuffer(void);
static void APP_InitLcdif(void);
static void APP_InitPxp(void);
static void APP_PorterDuff(void);
static void APP_BufferSwitchOffCallback(void *param, void *switchOffBuffer);

/*******************************************************************************
 * Variables
 ******************************************************************************/

AT_NONCACHEABLE_SECTION_ALIGN(static uint32_t s_DstBuffer[APP_IMG_HEIGHT][APP_IMG_WIDTH], FRAME_BUFFER_ALIGN);
AT_NONCACHEABLE_SECTION_ALIGN(static uint32_t s_SrcBuffer[APP_IMG_HEIGHT][APP_IMG_WIDTH], FRAME_BUFFER_ALIGN);
AT_NONCACHEABLE_SECTION_ALIGN(static uint32_t s_pxpOutputBuffer[2][APP_IMG_HEIGHT][APP_IMG_WIDTH], FRAME_BUFFER_ALIGN);

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

static const porter_duff_mode_name_t s_porterDuffModeNameTable[] = {
    {kPXP_PorterDuffSrc, "PorterDuffSrc"},         {kPXP_PorterDuffAtop, "PorterDuffAtop"},
    {kPXP_PorterDuffOver, "PorterDuffOver"},       {kPXP_PorterDuffIn, "PorterDuffIn"},
    {kPXP_PorterDuffOut, "PorterDuffOut"},         {kPXP_PorterDuffDst, "PorterDuffDst"},
    {kPXP_PorterDuffDstAtop, "PorterDuffDstAtop"}, {kPXP_PorterDuffDstOver, "PorterDuffDstOver"},
    {kPXP_PorterDuffDstIn, "PorterDuffDstIn"},     {kPXP_PorterDuffDstOut, "PorterDuffDstOut"},
    {kPXP_PorterDuffXor, "PorterDuffXor"},         {kPXP_PorterDuffClear, "PorterDuffClear"},
};

/*******************************************************************************
 * Code
 ******************************************************************************/

int main(void)
{
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\nPXP Porter Duff example start...\r\n");

    APP_InitInputBuffer();
    APP_InitPxp();
    APP_InitLcdif();
    APP_PorterDuff();

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
    g_dc.ops->setFrameBuffer(&g_dc, 0, (void *)s_pxpOutputBuffer[curLcdBufferIdx]);

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
        .bufferAddr  = (uint32_t)s_DstBuffer,
        .bufferAddrU = 0U,
        .bufferAddrV = 0U,
        .pitchBytes  = APP_IMG_WIDTH * APP_BPP,
    };

    PXP_SetProcessSurfaceBackGroundColor(APP_PXP, 0U);

    PXP_SetProcessSurfaceBufferConfig(APP_PXP, &psBufferConfig);

    /* AS config. */
    const pxp_as_buffer_config_t asBufferConfig = {
        .pixelFormat = APP_PXP_AS_FORMAT,
        .bufferAddr  = (uint32_t)s_SrcBuffer,
        .pitchBytes  = APP_IMG_WIDTH * APP_BPP,
    };

    PXP_SetAlphaSurfaceBufferConfig(APP_PXP, &asBufferConfig);

    /* Output config. */
    outputBufferConfig.pixelFormat    = APP_PXP_OUT_FORMAT;
    outputBufferConfig.interlacedMode = kPXP_OutputProgressive;
    outputBufferConfig.buffer0Addr    = (uint32_t)s_pxpOutputBuffer[0];
    outputBufferConfig.buffer1Addr    = 0U;
    outputBufferConfig.pitchBytes     = APP_IMG_WIDTH * APP_BPP;
    outputBufferConfig.width          = APP_IMG_WIDTH;
    outputBufferConfig.height         = APP_IMG_HEIGHT;

    PXP_SetOutputBufferConfig(APP_PXP, &outputBufferConfig);

    PXP_SetProcessSurfacePosition(APP_PXP, 0, 0, APP_IMG_WIDTH - 1, APP_IMG_HEIGHT - 1);
    PXP_SetAlphaSurfacePosition(APP_PXP, 0, 0, APP_IMG_WIDTH - 1, APP_IMG_HEIGHT - 1);

    /* Disable CSC1, it is enabled by default. */
    PXP_EnableCsc1(APP_PXP, false);
}

static void APP_PorterDuff(void)
{
    pxp_porter_duff_config_t pxpPorterDuffConfig;

    uint8_t modeIndex = 0;

    for (;;)
    {
        PRINTF("Currently show %s mode\r\n\r\n", s_porterDuffModeNameTable[modeIndex].name);

        PXP_GetPorterDuffConfig(s_porterDuffModeNameTable[modeIndex].mode, &pxpPorterDuffConfig);

        modeIndex++;
        if (modeIndex >= ARRAY_SIZE(s_porterDuffModeNameTable))
        {
            modeIndex = 0;
        }

        PXP_SetPorterDuffConfig(APP_PXP, &pxpPorterDuffConfig);

        /*
         * Wait for the new set frame buffer active, so that the older frame
         * buffer is inactive, then PXP could output to the older frame buffer.
         */
        while (s_newFrameShown == false)
        {
        }

        /* Switch to the other LCD buffer. */
        curLcdBufferIdx ^= 1U;

        outputBufferConfig.buffer0Addr = (uint32_t)s_pxpOutputBuffer[curLcdBufferIdx];
        PXP_SetOutputBufferConfig(APP_PXP, &outputBufferConfig);

        /* Start PXP. */
        PXP_Start(APP_PXP);

        /* Wait for process complete. */
        while (!(kPXP_CompleteFlag & PXP_GetStatusFlags(APP_PXP)))
        {
        }

        PXP_ClearStatusFlags(APP_PXP, kPXP_CompleteFlag);

        s_newFrameShown = false;
        g_dc.ops->setFrameBuffer(&g_dc, 0, (void *)s_pxpOutputBuffer[curLcdBufferIdx]);

        /* Delay at least 2s to show next mode. */
        for (uint32_t i = 0; i < 2; i++)
        {
            SDK_DelayAtLeastUs(1000 * 1000, SystemCoreClock);
        }
    }
}

static void APP_DrawRectangle(uint32_t *addr,
                              uint16_t startX,
                              uint16_t startY,
                              uint16_t width,
                              uint16_t height,
                              uint32_t color,
                              uint32_t strideWord)
{
    uint16_t x, y;

    for (y = startY; y < startY + height; y++)
    {
        for (x = startX; x < startX + width; x++)
        {
            *(addr + strideWord * y + x) = color;
        }
    }
}

static void APP_InitInputBuffer(void)
{
    memset(s_DstBuffer, 0, sizeof(s_DstBuffer));
    memset(s_SrcBuffer, 0, sizeof(s_SrcBuffer));
    memset(s_pxpOutputBuffer, 0, sizeof(s_pxpOutputBuffer));

    /* Draw blue rectangle in Dst buffer. */
    APP_DrawRectangle((uint32_t *)s_DstBuffer, 0, 0, APP_IMG_WIDTH / 2, APP_IMG_HEIGHT / 2, 0xFF0000FFU, APP_IMG_WIDTH);

    /* Draw red rectangle in Src buffer. */
    APP_DrawRectangle((uint32_t *)s_SrcBuffer, APP_IMG_WIDTH / 4, APP_IMG_HEIGHT / 4, APP_IMG_WIDTH / 2,
                      APP_IMG_HEIGHT / 2, 0xFFFF0000U, APP_IMG_WIDTH);
}

static void APP_BufferSwitchOffCallback(void *param, void *switchOffBuffer)
{
    s_newFrameShown = true;
}
