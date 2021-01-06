/*
 * Copyright 2017, 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_ISI_CAMERA_ADAPTER_H_
#define _FSL_ISI_CAMERA_ADAPTER_H_

#include "fsl_common.h"

/*
 * Change log:
 *
 *   1.0.1
 *     - Fix MISRA-C 2012 issues.
 *
 *   1.0.0
 *     - Initial version
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#ifndef ISI_CAMERA_QUEUE_SIZE
#define ISI_CAMERA_QUEUE_SIZE 4U
#endif

#if (ISI_CAMERA_QUEUE_SIZE < 3)
#error The ISI camera queue size should not be less than 3
#endif

#define ISI_MAX_ACTIVE_BUF 2U

/*
 * One empty room reserved to distinguish whether the queue is full or empty.
 */
#define ISI_CAMERA_ACTUAL_QUEUE_SIZE (ISI_CAMERA_QUEUE_SIZE + 1U)

/*! @brief The private data used by the ISI camera receiver. */
typedef struct _isi_private_data
{
    video_ringbuf_t fullRingBuf;                         /*!< The ring buffer to save full frame buffers. */
    video_ringbuf_t emptyRingBuf;                        /*!< The ring buffer to save empty frame buffers. */
    volatile uint8_t outputBufIdx;                       /*!< Current active output buffer index. */
    volatile bool isTransferStarted;                     /*!< Transfer started using ISI_ADAPTER_Start. */
    void *fullRingBufMem[ISI_CAMERA_ACTUAL_QUEUE_SIZE];  /*!< Memory for ring buffer. */
    void *emptyRingBufMem[ISI_CAMERA_ACTUAL_QUEUE_SIZE]; /*!< Memory for ring buffer. */
    uint32_t activeBuf[ISI_MAX_ACTIVE_BUF];              /*!< Active frame buffers. */
    uint32_t activeBufSave[ISI_MAX_ACTIVE_BUF];          /*!< Save the active buffer address when transfer stoped. */
    uint8_t activeBufSaveCnt;                            /*!< Valid buffers count saved in activeBufSave. */
    uint32_t dropFrame;                                  /*!< Buffer to save the droped frame. */
    camera_receiver_callback_t callback;                 /*!< Save the callback. */
    void *userData;                                      /*!< Parameter for the callback. */
} isi_private_data_t;

/*!
 * @brief The resources used by the ISI camera receiver.
 */
typedef struct _isi_resource
{
    ISI_Type *isiBase;    /*!< ISI peripheral register base. */
    uint8_t isiInputPort; /*!< ISI input port. */
} isi_resource_t;

/*!
 * @brief The resources used by the ISI camera receiver.
 */
enum _camera_isi_flags
{
    kCAMERA_ISI_FlipHorizontal = (1U << 0U), /*!< Horizontal flip. */
    kCAMERA_ISI_FlipVertical   = (1U << 1U), /*!< Vertical flip. */
};

/*!
 * @brief The resources used by the ISI camera receiver.
 */
typedef struct
{
    uint8_t outputBytesPerPixel;            /*!< Output byte per pixel. */
    video_pixel_format_t outputPixelFormat; /*!< Output frame pixel format. */
    uint32_t outputFrameResolution;         /*!< Output frame resolution. */
    uint8_t flags;                          /*!< Control flags. OR'ed value of @ref _camera_isi_flags */
} isi_ext_config_t;

/*! @brief ISI camera receiver operations structure. */
extern const camera_receiver_operations_t isi_ops;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief ISI camera adapter IRQ handler.
 *
 * Application should install this handler to the ISI IRQ handler.
 *
 * @param handle Camera receiver handle.
 */
void ISI_ADAPTER_IRQHandler(camera_receiver_handle_t *handle);
#if defined(__cplusplus)
}
#endif

#endif /* _FSL_ISI_CAMERA_ADAPTER_H_ */
