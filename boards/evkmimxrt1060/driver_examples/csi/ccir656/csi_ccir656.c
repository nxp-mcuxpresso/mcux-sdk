/*
 * Copyright  2017-2019 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_pxp.h"
#include "display_support.h"
#include "camera_support.h"

#include "pin_mux.h"
#include "board.h"
#include "fsl_debug_console.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define APP_PXP PXP

/* Pixel format YUV422, bytesPerPixel is 2. */
#define APP_BPP 2

#define APP_CAMERA_FRAME_BUFFER_COUNT 4

/* LCD frame buffer format is RGB565. */
#define APP_LCD_BPP 2

#define APP_LCD_FRAME_BUFFER_COUNT 2

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void APP_BufferSwitchOffCallback(void *param, void *switchOffBuffer);
static void APP_InitCamera(void);
static void APP_InitDisplay(void);
static void APP_InitPxp(void);
static void APP_CSI_CCIR656(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
AT_NONCACHEABLE_SECTION_ALIGN(
    static uint16_t s_cameraBuffer[APP_CAMERA_FRAME_BUFFER_COUNT][DEMO_CAMERA_HEIGHT][DEMO_CAMERA_WIDTH],
    DEMO_CAMERA_BUFFER_ALIGN);
AT_NONCACHEABLE_SECTION_ALIGN(
    static uint16_t s_lcdBuffer[APP_LCD_FRAME_BUFFER_COUNT][DEMO_BUFFER_HEIGHT][DEMO_BUFFER_WIDTH], FRAME_BUFFER_ALIGN);

static volatile uint8_t s_lcdActiveFbIdx = 0;

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


static void APP_InitCamera(void)
{
    const camera_config_t cameraConfig = {
        .pixelFormat                = kVIDEO_PixelFormatYUYV,
        .bytesPerPixel              = APP_BPP,
        .resolution                 = FSL_VIDEO_RESOLUTION(DEMO_CAMERA_WIDTH, DEMO_CAMERA_HEIGHT),
        .frameBufferLinePitch_Bytes = DEMO_CAMERA_WIDTH * APP_BPP,
        .interface                  = kCAMERA_InterfaceCCIR656,
        .controlFlags               = DEMO_CAMERA_CONTROL_FLAGS,
        .framePerSec                = 30,
    };

    memset(s_cameraBuffer, 0, sizeof(s_cameraBuffer));

    BOARD_InitCameraResource();

    CAMERA_RECEIVER_Init(&cameraReceiver, &cameraConfig, NULL, NULL);

    if (kStatus_Success != CAMERA_DEVICE_Init(&cameraDevice, &cameraConfig))
    {
        PRINTF("Camera device initialization failed\r\n");
        while (1)
        {
            ;
        }
    }

    CAMERA_DEVICE_Start(&cameraDevice);

    /* Submit the empty frame buffers to buffer queue. */
    for (uint32_t i = 0; i < APP_CAMERA_FRAME_BUFFER_COUNT; i++)
    {
        CAMERA_RECEIVER_SubmitEmptyBuffer(&cameraReceiver, (uint32_t)(s_cameraBuffer[i]));
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_InitDEBUG_UARTPins();
    BOARD_InitSDRAMPins();
    BOARD_EarlyPrepareCamera();
    BOARD_InitCSIPins();
    BOARD_InitLCDPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("CSI CCIR656 example start...\r\n");

    APP_InitPxp();

    APP_InitCamera();

    APP_InitDisplay();

    APP_CSI_CCIR656();

    while (1)
    {
    }
}

static void APP_InitDisplay(void)
{
    status_t status;

    memset(s_lcdBuffer, 0, sizeof(s_lcdBuffer));

    BOARD_PrepareDisplayController();

    status = g_dc.ops->init(&g_dc);
    if (kStatus_Success != status)
    {
        PRINTF("Display initialization failed\r\n");
        assert(0);
    }

    g_dc.ops->getLayerDefaultConfig(&g_dc, 0, &fbInfo);
    fbInfo.pixelFormat = kVIDEO_PixelFormatRGB565;
    fbInfo.width       = DEMO_BUFFER_WIDTH;
    fbInfo.height      = DEMO_BUFFER_HEIGHT;
    fbInfo.startX      = DEMO_BUFFER_START_X;
    fbInfo.startY      = DEMO_BUFFER_START_Y;
    fbInfo.strideBytes = DEMO_BUFFER_WIDTH * APP_LCD_BPP;
    g_dc.ops->setLayerConfig(&g_dc, 0, &fbInfo);

    g_dc.ops->setCallback(&g_dc, 0, APP_BufferSwitchOffCallback, NULL);

    s_lcdActiveFbIdx = 0;
    s_newFrameShown  = false;
    g_dc.ops->setFrameBuffer(&g_dc, 0, s_lcdBuffer[s_lcdActiveFbIdx]);

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
    /*
     * Configure the PXP for color space conversion.
     */
    PXP_Init(APP_PXP);

    PXP_SetProcessSurfaceBackGroundColor(APP_PXP, 0U);

    PXP_SetProcessSurfacePosition(APP_PXP, 0U, 0U, DEMO_CAMERA_WIDTH - 1U, DEMO_CAMERA_HEIGHT - 1U);

    /* Disable AS. */
    PXP_SetAlphaSurfacePosition(APP_PXP, 0xFFFFU, 0xFFFFU, 0U, 0U);

    PXP_SetCsc1Mode(APP_PXP, kPXP_Csc1YCbCr2RGB);
    PXP_EnableCsc1(APP_PXP, true);
}

void APP_CSI_CCIR656(void)
{
    uint32_t cameraReceivedFrameAddr;
    void *lcdFrameAddr;

    pxp_ps_buffer_config_t psBufferConfig = {
        .pixelFormat = kPXP_PsPixelFormatUYVY1P422,
        .swapByte    = false,
        .bufferAddrU = 0U,
        .bufferAddrV = 0U,
        .pitchBytes  = DEMO_CAMERA_WIDTH * APP_BPP,
    };

    /* Output config. */
    pxp_output_buffer_config_t outputBufferConfig = {
        .pixelFormat    = kPXP_OutputPixelFormatRGB565,
        .interlacedMode = kPXP_OutputProgressive,
        .buffer1Addr    = 0U,
        .pitchBytes     = DEMO_BUFFER_WIDTH * APP_LCD_BPP,
        .width          = DEMO_BUFFER_WIDTH,
        .height         = DEMO_BUFFER_HEIGHT,
    };

    CAMERA_RECEIVER_Start(&cameraReceiver);

    while (1)
    {
        /* Wait to get the full frame buffer to show. */
        while (kStatus_Success != CAMERA_RECEIVER_GetFullBuffer(&cameraReceiver, &cameraReceivedFrameAddr))
        {
        }

        /* Wait for the previous frame buffer is shown, and there is available
           inactive buffer to fill. */
        while (s_newFrameShown == false)
        {
        }

        /* Convert the camera input picture to RGB format. */
        psBufferConfig.bufferAddr = cameraReceivedFrameAddr;
        PXP_SetProcessSurfaceBufferConfig(APP_PXP, &psBufferConfig);

        lcdFrameAddr                   = s_lcdBuffer[s_lcdActiveFbIdx ^ 1];
        outputBufferConfig.buffer0Addr = (uint32_t)lcdFrameAddr;
        PXP_SetOutputBufferConfig(APP_PXP, &outputBufferConfig);

        PXP_Start(APP_PXP);

        /* Wait for PXP process complete. */
        while (!(kPXP_CompleteFlag & PXP_GetStatusFlags(APP_PXP)))
        {
        }
        PXP_ClearStatusFlags(APP_PXP, kPXP_CompleteFlag);

        /* Return the camera buffer to camera receiver handle. */
        CAMERA_RECEIVER_SubmitEmptyBuffer(&cameraReceiver, (uint32_t)cameraReceivedFrameAddr);

        /* Show the new frame. */
        s_newFrameShown = false;
        g_dc.ops->setFrameBuffer(&g_dc, 0, lcdFrameAddr);
    }
}

static void APP_BufferSwitchOffCallback(void *param, void *switchOffBuffer)
{
    s_newFrameShown = true;
    s_lcdActiveFbIdx ^= 1;
}
