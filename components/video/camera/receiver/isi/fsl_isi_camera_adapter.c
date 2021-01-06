/*
 * Copyright 2017, 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_camera.h"
#include "fsl_camera_receiver.h"
#include "fsl_isi.h"
#include "fsl_isi_camera_adapter.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Map for the fourcc format to ISI format. */
typedef struct _isi_output_format_map
{
    video_pixel_format_t fourccFormat;
    isi_output_format_t isiFormat;
} isi_output_format_map_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static status_t ISI_ADAPTER_Init(camera_receiver_handle_t *handle,
                                 const camera_config_t *config,
                                 camera_receiver_callback_t callback,
                                 void *userData);

static status_t ISI_ADAPTER_Deinit(camera_receiver_handle_t *handle);

static status_t ISI_ADAPTER_Start(camera_receiver_handle_t *handle);

static status_t ISI_ADAPTER_Stop(camera_receiver_handle_t *handle);

static status_t ISI_ADAPTER_SubmitEmptyBuffer(camera_receiver_handle_t *handle, uint32_t buffer);

static status_t ISI_ADAPTER_GetFullBuffer(camera_receiver_handle_t *handle, uint32_t *buffer);

static status_t ISI_ADAPTER_InitExt(camera_receiver_handle_t *handle,
                                    const camera_config_t *config,
                                    const void *extConfig,
                                    camera_receiver_callback_t callback,
                                    void *userData);

/*******************************************************************************
 * Variables
 ******************************************************************************/
const camera_receiver_operations_t isi_ops = {.init              = ISI_ADAPTER_Init,
                                              .deinit            = ISI_ADAPTER_Deinit,
                                              .start             = ISI_ADAPTER_Start,
                                              .stop              = ISI_ADAPTER_Stop,
                                              .submitEmptyBuffer = ISI_ADAPTER_SubmitEmptyBuffer,
                                              .getFullBuffer     = ISI_ADAPTER_GetFullBuffer,
                                              .init_ext          = ISI_ADAPTER_InitExt};

static const isi_output_format_map_t s_isiOutputFormatMap[] = {{
                                                                   .fourccFormat = kVIDEO_PixelFormatXRGB8888,
                                                                   .isiFormat    = kISI_OutputXRGB8888,
                                                               },
                                                               {
                                                                   .fourccFormat = kVIDEO_PixelFormatRGB888,
                                                                   .isiFormat    = kISI_OutputRGB888,
                                                               },
                                                               {
                                                                   .fourccFormat = kVIDEO_PixelFormatRGB565,
                                                                   .isiFormat    = kISI_OutputRGB565,
                                                               },
                                                               {
                                                                   .fourccFormat = kVIDEO_PixelFormatYUYV,
                                                                   .isiFormat    = kISI_OutputYUV422_1P8P,
                                                               }};

/*******************************************************************************
 * Code
 ******************************************************************************/

/* Load empty buffer to ISI module, only call this function when activeBufCnt < 2. */
static void ISI_ADAPTER_LoadEmptyBuffer(camera_receiver_handle_t *handle, uint32_t buffer)
{
    ISI_Type *isiBase               = ((isi_resource_t *)(handle->resource))->isiBase;
    isi_private_data_t *privateData = (isi_private_data_t *)(handle->privateData);

    privateData->activeBuf[privateData->outputBufIdx] = buffer;
    ISI_SetOutputBufferAddr(isiBase, privateData->outputBufIdx, buffer, 0, 0);
}

static status_t ISI_ADAPTER_GetIsiOutFormat(video_pixel_format_t fourccFormat, isi_output_format_t *isiFormat)
{
    uint32_t i;

    for (i = 0; i < ARRAY_SIZE(s_isiOutputFormatMap); i++)
    {
        if (s_isiOutputFormatMap[i].fourccFormat == fourccFormat)
        {
            *isiFormat = s_isiOutputFormatMap[i].isiFormat;
            return kStatus_Success;
        }
    }

    return kStatus_InvalidArgument;
}

static status_t ISI_ADAPTER_Init(camera_receiver_handle_t *handle,
                                 const camera_config_t *config,
                                 camera_receiver_callback_t callback,
                                 void *userData)
{
    isi_ext_config_t extConfig = {
        .outputBytesPerPixel   = config->bytesPerPixel,
        .outputFrameResolution = config->resolution,
        .outputPixelFormat     = config->pixelFormat,
        .flags                 = 0,
    };

    return ISI_ADAPTER_InitExt(handle, config, &extConfig, callback, userData);
}

static status_t ISI_ADAPTER_Deinit(camera_receiver_handle_t *handle)
{
    ISI_Deinit(((isi_resource_t *)handle->resource)->isiBase);

    return kStatus_Success;
}

static status_t ISI_ADAPTER_Start(camera_receiver_handle_t *handle)
{
    uint32_t buffer;
    uint8_t i;

    ISI_Type *isiBase = ((isi_resource_t *)(handle->resource))->isiBase;

    isi_private_data_t *privateData;
    privateData = (isi_private_data_t *)(handle->privateData);

    /*
     * When transfer started, the empty frame buffers come from:
     * 1. The ring buffer: emptyRingBuf
     * 2. Previous active buffers: activeBufSave
     */
    /* If empty buffer count < 2, don't start the transfer. */
    if (VIDEO_RINGBUF_GetLength(&privateData->emptyRingBuf) + privateData->activeBufSaveCnt < ISI_MAX_ACTIVE_BUF)
    {
        return kStatus_Fail;
    }

    /*
     * When started, the ISI starts to save in output bufer 0.
     */
    privateData->outputBufIdx = 0;

    for (i = 0; i < ISI_MAX_ACTIVE_BUF; i++)
    {
        if (privateData->activeBufSaveCnt > 0U)
        {
            buffer = privateData->activeBufSave[--privateData->activeBufSaveCnt];
        }
        else
        {
            (void)VIDEO_RINGBUF_Get(&(privateData->emptyRingBuf), (void **)(&buffer));
        }
        privateData->activeBuf[i] = buffer;
        ISI_SetOutputBufferAddr(isiBase, i, buffer, 0, 0);
    }

    privateData->isTransferStarted = true;

    ISI_ClearInterruptStatus(isiBase, (uint32_t)kISI_FrameReceivedInterrupt);
    (void)ISI_EnableInterrupts(isiBase, (uint32_t)kISI_FrameReceivedInterrupt);
    ISI_Start(isiBase);

    return kStatus_Success;
}

static status_t ISI_ADAPTER_Stop(camera_receiver_handle_t *handle)
{
    uint32_t i;
    ISI_Type *isiBase               = ((isi_resource_t *)(handle->resource))->isiBase;
    isi_private_data_t *privateData = (isi_private_data_t *)(handle->privateData);

    ISI_Stop(isiBase);
    (void)ISI_DisableInterrupts(isiBase, (uint32_t)kISI_FrameReceivedInterrupt);
    ISI_ClearInterruptStatus(isiBase, (uint32_t)kISI_FrameReceivedInterrupt);

    /* Save current active buffer address. */
    privateData->activeBufSaveCnt = 0;
    for (i = 0; i < ISI_MAX_ACTIVE_BUF; i++)
    {
        if ((0U != privateData->activeBuf[i]) && (privateData->dropFrame != privateData->activeBuf[i]))
        {
            privateData->activeBufSave[privateData->activeBufSaveCnt++] = privateData->activeBuf[i];
        }
    }

    privateData->isTransferStarted = false;

    return kStatus_Success;
}

static status_t ISI_ADAPTER_SubmitEmptyBuffer(camera_receiver_handle_t *handle, uint32_t buffer)
{
    uint32_t interrupts;
    status_t status = kStatus_Success;

    ISI_Type *isiBase               = ((isi_resource_t *)(handle->resource))->isiBase;
    isi_private_data_t *privateData = (isi_private_data_t *)(handle->privateData);

    /*
     * There must be buffer to save the droped frame, so the first submit buffer
     * is used as droped frame buffer.
     */
    if (0U == privateData->dropFrame)
    {
        privateData->dropFrame = buffer;
    }
    else
    {
        /* Disable the interrupt to protect the index information in handle. */
        interrupts = ISI_DisableInterrupts(isiBase, (uint32_t)kISI_FrameReceivedInterrupt);

        /* Put the empty buffer to empty buffer queue. */
        status = VIDEO_RINGBUF_Put(&privateData->emptyRingBuf, (uint8_t *)buffer);

        if (0UL != (interrupts & (uint32_t)kISI_FrameReceivedInterrupt))
        {
            (void)ISI_EnableInterrupts(isiBase, (uint32_t)kISI_FrameReceivedInterrupt);
        }
    }

    return status;
}

static status_t ISI_ADAPTER_GetFullBuffer(camera_receiver_handle_t *handle, uint32_t *buffer)
{
    status_t status;
    uint32_t interrupts;
    ISI_Type *isiBase               = ((const isi_resource_t *)(handle->resource))->isiBase;
    isi_private_data_t *privateData = (isi_private_data_t *)(handle->privateData);

    /* Disable the interrupt to protect the index information in handle. */
    interrupts = ISI_DisableInterrupts(isiBase, (uint32_t)kISI_FrameReceivedInterrupt);

    status = VIDEO_RINGBUF_Get(&(privateData->fullRingBuf), (void **)buffer);

    if (0UL != (interrupts & (uint32_t)kISI_FrameReceivedInterrupt))
    {
        (void)ISI_EnableInterrupts(isiBase, (uint32_t)kISI_FrameReceivedInterrupt);
    }

    return status;
}

static status_t ISI_ADAPTER_InitExt(camera_receiver_handle_t *handle,
                                    const camera_config_t *config,
                                    const void *extConfig,
                                    camera_receiver_callback_t callback,
                                    void *userData)
{
    status_t status;
    isi_config_t isiConfig;
    isi_output_format_t isiOutputFormat;
    isi_private_data_t *privateData;
    isi_resource_t *resource;
    isi_flip_mode_t flipMode = kISI_FlipDisable;
    uint32_t flipFlag;
    const isi_ext_config_t *isiExtConfig = (const isi_ext_config_t *)extConfig;

    static const isi_csc_config_t cscConfigYUV2RGB = {
        .mode = kISI_CscYCbCr2RGB,
        .A1   = 1.164f,
        .A2   = 0.0f,
        .A3   = 1.596f,
        .B1   = 1.164f,
        .B2   = -0.392f,
        .B3   = -0.813f,
        .C1   = 1.164f,
        .C2   = 2.017f,
        .C3   = 0.0f,
        .D1   = -16,
        .D2   = -128,
        .D3   = -128,
    };

    static const isi_csc_config_t cscConfigRGB2YUV = {
        .mode = kISI_CscRGB2YCbCr,
        .A1   = 0.257f,
        .A2   = 0.504f,
        .A3   = 0.098f,
        .B1   = -0.148f,
        .B2   = -0.291f,
        .B3   = 0.439f,
        .C1   = 0.439f,
        .C2   = -0.368f,
        .C3   = -0.071f,
        .D1   = 16,
        .D2   = 128,
        .D3   = 128,
    };

    status = ISI_ADAPTER_GetIsiOutFormat(isiExtConfig->outputPixelFormat, &isiOutputFormat);

    if (kStatus_Success != status)
    {
        return status;
    }

    resource = (isi_resource_t *)(handle->resource);

    /* Initialize the ISI. */
    ISI_GetDefaultConfig(&isiConfig);
    isiConfig.isChannelBypassed    = false;
    isiConfig.isSourceMemory       = false;
    isiConfig.isYCbCr              = true;
    isiConfig.sourcePort           = resource->isiInputPort;
    isiConfig.mipiChannel          = config->mipiChannel;
    isiConfig.inputHeight          = FSL_VIDEO_EXTRACT_HEIGHT(config->resolution);
    isiConfig.inputWidth           = FSL_VIDEO_EXTRACT_WIDTH(config->resolution);
    isiConfig.outputFormat         = isiOutputFormat;
    isiConfig.outputLinePitchBytes = config->frameBufferLinePitch_Bytes;

    ISI_Init(resource->isiBase);
    ISI_SetConfig(resource->isiBase, &isiConfig);
    ISI_SetScalerConfig(resource->isiBase, isiConfig.inputWidth, isiConfig.inputHeight,
                        FSL_VIDEO_EXTRACT_WIDTH(isiExtConfig->outputFrameResolution),
                        FSL_VIDEO_EXTRACT_HEIGHT(isiExtConfig->outputFrameResolution));

    /* Color space. */
    if (VIDEO_IsYUV(isiExtConfig->outputPixelFormat))
    {
        if (VIDEO_IsYUV(config->pixelFormat))
        {
            ISI_EnableColorSpaceConversion(resource->isiBase, false);
        }
        else
        {
            ISI_SetColorSpaceConversionConfig(resource->isiBase, &cscConfigRGB2YUV);
            ISI_EnableColorSpaceConversion(resource->isiBase, true);
        }
    }
    else
    {
        if (VIDEO_IsYUV(config->pixelFormat))
        {
            ISI_SetColorSpaceConversionConfig(resource->isiBase, &cscConfigYUV2RGB);
            ISI_EnableColorSpaceConversion(resource->isiBase, true);
        }
        else
        {
            ISI_EnableColorSpaceConversion(resource->isiBase, false);
        }
    }

    /* flip. */
    flipFlag = isiExtConfig->flags & ((uint32_t)kCAMERA_ISI_FlipHorizontal | (uint32_t)kCAMERA_ISI_FlipVertical);
    switch (flipFlag)
    {
        case (uint32_t)kCAMERA_ISI_FlipHorizontal:
            flipMode = kISI_FlipHorizontal;
            break;

        case (uint32_t)kCAMERA_ISI_FlipVertical:
            flipMode = kISI_FlipVertical;
            break;

        case (uint32_t)kCAMERA_ISI_FlipVertical | (uint32_t)kCAMERA_ISI_FlipHorizontal:
            flipMode = kISI_FlipBoth;
            break;

        default:
            flipMode = kISI_FlipDisable;
            break;
    }

    ISI_SetFlipMode(resource->isiBase, flipMode);

    privateData = (isi_private_data_t *)(handle->privateData);
    (void)memset(privateData, 0, sizeof(*privateData));

    (void)VIDEO_RINGBUF_Init(&(privateData->fullRingBuf), privateData->fullRingBufMem, ISI_CAMERA_ACTUAL_QUEUE_SIZE);
    (void)VIDEO_RINGBUF_Init(&(privateData->emptyRingBuf), privateData->emptyRingBufMem, ISI_CAMERA_ACTUAL_QUEUE_SIZE);

    privateData->outputBufIdx      = 0;
    privateData->isTransferStarted = false;

    privateData->callback = callback;
    privateData->userData = userData;

    return kStatus_Success;
}

void ISI_ADAPTER_IRQHandler(camera_receiver_handle_t *handle)
{
    uint32_t buf;
    uint32_t intStatus;
    status_t status;
    bool fullBufferReject           = false;
    ISI_Type *isiBase               = ((isi_resource_t *)(handle->resource))->isiBase;
    isi_private_data_t *privateData = (isi_private_data_t *)(handle->privateData);

    intStatus = ISI_GetInterruptStatus(isiBase);
    ISI_ClearInterruptStatus(isiBase, intStatus);

    /* If frame received interrupt does not happen, return directly. */
    if ((uint32_t)kISI_FrameReceivedInterrupt != ((uint32_t)kISI_FrameReceivedInterrupt & intStatus))
    {
        return;
    }

    buf = privateData->activeBuf[privateData->outputBufIdx];

    /* If current finished frame is not droped frame, then submit it to full buffer queue. */
    if (buf != privateData->dropFrame)
    {
        status = VIDEO_RINGBUF_Put(&privateData->fullRingBuf, (uint8_t *)buf);

        /* If the full buffer queue is not full. */
        if (kStatus_Success == status)
        {
            fullBufferReject = false;
            if (NULL != privateData->callback)
            {
                privateData->callback(handle, kStatus_Success, privateData->userData);
            }
        }
        /* If the full buffer queue is full. */
        else
        {
            fullBufferReject = true;
        }
    }

    /*
     * Now install the new buffer to ISI.
     * Check whether the transfer is stoped, because user may stop in callback.
     */
    if (privateData->isTransferStarted)
    {
        /*
         * If the finished buffer is rejected to be submited to full buffer queue,
         * then it will continued to be used, don't need to install empty buffer
         * in this case. So here only handle the not rejected case.
         */
        if (!fullBufferReject)
        {
            /* Get empty buffer. */
            if (kStatus_Success != VIDEO_RINGBUF_Get(&(privateData->emptyRingBuf), (void **)(&buf)))
            {
                /*
                 * If not available empty buffer, then the frame will be droped.
                 */
                buf = privateData->dropFrame;
            }

            ISI_ADAPTER_LoadEmptyBuffer(handle, buf);
        }
    }

    privateData->outputBufIdx ^= 1U;
}
