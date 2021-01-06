/*
 * Copyright 2017, 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_camera.h"
#include "fsl_camera_receiver.h"
#include "fsl_camera_device.h"
#include "fsl_isi_camera_adapter.h"
#include "app_display.h"
#include "isi_config.h"
#include "isi_example.h"
#include "fsl_debug_console.h"

#include "pin_mux.h"
#include "board.h"

#include "fsl_irqsteer.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define APP_FRAME_BUFFER_COUNT 4
#define APP_BPP                2 /* In this exaple, the camera pixel format is RGB565. */

#ifndef APP_FB_STRIDE_ALIGN_BYTE
#define APP_FB_STRIDE_ALIGN_BYTE APP_BPP
#endif

#define APP_FB_STRIDE_BYTE (SDK_SIZEALIGN(APP_CAMERA_WIDTH * APP_BPP, APP_FB_STRIDE_ALIGN_BYTE))
/*******************************************************************************
 * Prototypes
 ******************************************************************************/



/*******************************************************************************
 * Variables
 ******************************************************************************/
AT_NONCACHEABLE_SECTION_ALIGN(static uint8_t s_frameBuffer[APP_FRAME_BUFFER_COUNT][SDK_SIZEALIGN(
                                  APP_CAMERA_HEIGHT * APP_FB_STRIDE_BYTE, APP_FB_ALIGN_BYTE)],
                              APP_FB_ALIGN_BYTE);

extern camera_device_handle_t cameraDevice;
extern camera_receiver_handle_t cameraReceiver;
/*******************************************************************************
 * Code
 ******************************************************************************/

/*
 * The callback function is called when the display controller updated the use
 * the new frame buffer. The previous active frame buffer address is returned
 * so that it could be submited to the camera buffer queue.
 */
void APP_DisplayFrameDoneCallback(uint32_t frameBuffer)
{
    CAMERA_RECEIVER_SubmitEmptyBuffer(&cameraReceiver, frameBuffer);
}

/*!
 * @brief Main function
 */
int main(void)
{
    uint32_t fullCameraBufferAddr;
    status_t status;

    const camera_config_t cameraConfig = {
        .pixelFormat                = kVIDEO_PixelFormatYUYV,
        .bytesPerPixel              = APP_BPP,
        .resolution                 = FSL_VIDEO_RESOLUTION(APP_CAMERA_WIDTH, APP_CAMERA_HEIGHT),
        .frameBufferLinePitch_Bytes = APP_CAMERA_WIDTH * APP_BPP,
#if (APP_CI_PI_MODE == CI_PI_MODE_GATE_CLOCK)
        .interface = kCAMERA_InterfaceGatedClock,
#elif (APP_CI_PI_MODE == CI_PI_MODE_NON_GATE_CLOCK)
        .interface = kCAMERA_InterfaceNonGatedClock,
#else
        .interface = kCAMERA_InterfaceCCIR656,
#endif
        .controlFlags = APP_CAMERA_CONTROL_FLAGS,
        .framePerSec  = APP_CAMERA_FRAME_RATE,
        .mipiChannel  = 0, /* Not used. */
        .csiLanes     = 0, /* Not used. */
    };

    BOARD_InitRpc();

    sc_ipc_t ipc;
    ipc = BOARD_GetRpcHandle();

    BOARD_InitPins(ipc);
    BOARD_BootClockRUN();
    sc_pm_set_resource_power_mode(ipc, SC_R_IRQSTR_M4_0, SC_PM_PW_MODE_ON);
    IRQSTEER_Init(IRQSTEER);
    BOARD_PrepareDisplay();
    BOARD_PrepareCamera();
    BOARD_InitMemory();
    BOARD_InitDebugConsole();

    SOC_SetIsiPermission((uint32_t)s_frameBuffer, (((uint32_t)(s_frameBuffer)) + sizeof(s_frameBuffer) - 1U));

    /* The camera input pixel format is YUV422, the ISI could convert to RGB565. */
    isi_ext_config_t isiExtConfig = {
        .outputBytesPerPixel   = APP_BPP,
        .outputPixelFormat     = kVIDEO_PixelFormatRGB565,
        .outputFrameResolution = FSL_VIDEO_RESOLUTION(APP_CAMERA_WIDTH, APP_CAMERA_HEIGHT),
        .flags                 = 0,
    };

    memset(s_frameBuffer, 0, sizeof(s_frameBuffer));

    PRINTF("ISI CI_PI example start...\r\n");

    /*
     * Initialize the display interface.
     * The first frame bufer is shown.
     */
    APP_InitDisplay((uint32_t)s_frameBuffer[0], APP_DisplayFrameDoneCallback);

    /*
     * Configure the camera.
     * First enable ISI, the enable CI_PI, at last enable the sensor.
     */
    status = CAMERA_RECEIVER_InitExt(&cameraReceiver, &cameraConfig, &isiExtConfig, NULL, NULL);

    if (kStatus_Success != status)
    {
        PRINTF("ISI initialize failed.\r\n");
        return -1;
    }

    /*
     * Submit the empty buffer to camera buffer queue.
     * The first buffer is used by the display. So submit from the second buffer.
     */
    for (uint32_t i = 1; i < APP_FRAME_BUFFER_COUNT; i++)
    {
        CAMERA_RECEIVER_SubmitEmptyBuffer(&cameraReceiver, (uint32_t)(s_frameBuffer[i]));
    }

    CAMERA_RECEIVER_Start(&cameraReceiver);

    BOARD_InitCameraInterface();

    status = CAMERA_DEVICE_Init(&cameraDevice, &cameraConfig);

    if (kStatus_Success != status)
    {
        PRINTF("Camera initialize failed.\r\n");
        return -1;
    }

    CAMERA_DEVICE_Start(&cameraDevice);

    while (1)
    {
        /* Wait to get the full frame buffer to show. */
        while (kStatus_Success != CAMERA_RECEIVER_GetFullBuffer(&cameraReceiver, &fullCameraBufferAddr))
        {
        }

        /* Wait for the display controller available to accept new frame buffer. */
        while (APP_IsDisplayFramePending())
        {
        }

        /* Pass the full frame buffer to display controller to show. */
        APP_SetDisplayFrameBuffer(fullCameraBufferAddr);
    }
}
