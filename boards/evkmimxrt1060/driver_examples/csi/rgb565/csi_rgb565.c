/*
 * Copyright  2017-2019 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "display_support.h"
#include "camera_support.h"

#include "pin_mux.h"
#include "board.h"
#include "fsl_debug_console.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


#define APP_FRAME_BUFFER_COUNT 4
/* Pixel format RGB565, bytesPerPixel is 2. */
#define APP_BPP 2

#if (FRAME_BUFFER_ALIGN > DEMO_CAMERA_BUFFER_ALIGN)
#define DEMO_FRAME_BUFFER_ALIGN FRAME_BUFFER_ALIGN
#else
#define DEMO_FRAME_BUFFER_ALIGN DEMO_CAMERA_BUFFER_ALIGN
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void APP_BufferSwitchOffCallback(void *param, void *switchOffBuffer);
static void APP_InitCamera(void);
static void APP_InitDisplay(void);
static void APP_CSI_RGB565(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
AT_NONCACHEABLE_SECTION_ALIGN(
    static uint16_t s_frameBuffer[APP_FRAME_BUFFER_COUNT][DEMO_BUFFER_HEIGHT][DEMO_BUFFER_WIDTH],
    DEMO_FRAME_BUFFER_ALIGN);

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

    PRINTF("CSI RGB565 example start...\r\n");

    APP_InitCamera();

    APP_InitDisplay();

    APP_CSI_RGB565();

    while (1)
    {
    }
}

static void APP_InitCamera(void)
{
    const camera_config_t cameraConfig = {
        .pixelFormat   = kVIDEO_PixelFormatRGB565,
        .bytesPerPixel = APP_BPP,
        .resolution    = FSL_VIDEO_RESOLUTION(DEMO_CAMERA_WIDTH, DEMO_CAMERA_HEIGHT),
        /* Set the camera buffer stride according to panel, so that if
         * camera resoution is smaller than display, it can still be shown
         * correct in the screen.
         */
        .frameBufferLinePitch_Bytes = DEMO_BUFFER_WIDTH * APP_BPP,
        .interface                  = kCAMERA_InterfaceGatedClock,
        .controlFlags               = DEMO_CAMERA_CONTROL_FLAGS,
        .framePerSec                = 30,
    };

    memset(s_frameBuffer, 0, sizeof(s_frameBuffer));

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
    for (uint32_t i = 0; i < APP_FRAME_BUFFER_COUNT; i++)
    {
        CAMERA_RECEIVER_SubmitEmptyBuffer(&cameraReceiver, (uint32_t)(s_frameBuffer[i]));
    }
}

static void APP_InitDisplay(void)
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
    fbInfo.pixelFormat = kVIDEO_PixelFormatRGB565;
    fbInfo.width       = DEMO_BUFFER_WIDTH;
    fbInfo.height      = DEMO_BUFFER_HEIGHT;
    fbInfo.startX      = DEMO_BUFFER_START_X;
    fbInfo.startY      = DEMO_BUFFER_START_Y;
    fbInfo.strideBytes = DEMO_BUFFER_WIDTH * APP_BPP;
    g_dc.ops->setLayerConfig(&g_dc, 0, &fbInfo);

    g_dc.ops->setCallback(&g_dc, 0, APP_BufferSwitchOffCallback, NULL);
}

static void APP_CSI_RGB565(void)
{
    uint32_t cameraReceivedFrameAddr;

    CAMERA_RECEIVER_Start(&cameraReceiver);

    /* Wait to get the full frame buffer to show. */
    while (kStatus_Success != CAMERA_RECEIVER_GetFullBuffer(&cameraReceiver, &cameraReceivedFrameAddr))
    {
    }

    s_newFrameShown = false;
    g_dc.ops->setFrameBuffer(&g_dc, 0, (void *)cameraReceivedFrameAddr);

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

    while (1)
    {
        /* Wait to get the full frame buffer to show. */
        while (kStatus_Success != CAMERA_RECEIVER_GetFullBuffer(&cameraReceiver, &cameraReceivedFrameAddr))
        {
        }

        /* Wait for the previous frame buffer is shown. */
        while (s_newFrameShown == false)
        {
        }

        g_dc.ops->setFrameBuffer(&g_dc, 0, (void *)cameraReceivedFrameAddr);
    }
}

static void APP_BufferSwitchOffCallback(void *param, void *switchOffBuffer)
{
    s_newFrameShown = true;
    CAMERA_RECEIVER_SubmitEmptyBuffer(&cameraReceiver, (uint32_t)switchOffBuffer);
}
