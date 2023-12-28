/*
 * Copyright 2019-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_mipi_dsi_smartdma.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.mipi_dsi_smartdma"
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Callback when SMARTDMA done.
 *
 * @param param Callback parameter passed to SMARTDMA.
 */
static void DSI_SMARTDMA_Callback(void *param);

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Create the MIPI DSI handle.
 *
 * This function initializes the MIPI DSI handle which can be used for other transactional APIs.
 *
 * param base MIPI DSI host peripheral base address.
 * param handle Handle pointer.
 * param callback Callback function.
 * param userData User data.
 */
status_t DSI_TransferCreateHandleSMARTDMA(MIPI_DSI_HOST_Type *base,
                                          dsi_smartdma_handle_t *handle,
                                          dsi_smartdma_callback_t callback,
                                          void *userData)
{
    assert(NULL != handle);

    /* Zero the handle */
    (void)memset(handle, 0, sizeof(*handle));

    /* Initialize the handle */
    handle->dsi      = base;
    handle->callback = callback;
    handle->userData = userData;
    handle->isBusy   = false;

    SMARTDMA_InstallFirmware(SMARTDMA_DISPLAY_MEM_ADDR, s_smartdmaDisplayFirmware,
                             SMARTDMA_DISPLAY_FIRMWARE_SIZE);

    SMARTDMA_InstallCallback(DSI_SMARTDMA_Callback, handle);

    return kStatus_Success;
}

/*!
 * brief Abort current APB data transfer.
 *
 * param base MIPI DSI host peripheral base address.
 * param handle pointer to dsi_smartdma_handle_t structure which stores the transfer state.
 */
void DSI_TransferAbortSMARTDMA(MIPI_DSI_HOST_Type *base, dsi_smartdma_handle_t *handle)
{
    assert(NULL != handle);

    if (handle->isBusy)
    {
        SMARTDMA_Reset();
        /* Reset the state to idle. */
        handle->isBusy = false;
    }
}

/*!
 * brief Write display controller video memory using SMARTDMA.
 *
 * Perform data transfer using SMARTDMA, when transfer finished,
 * upper layer could be informed through callback function.
 *
 * param base MIPI DSI host peripheral base address.
 * param handle pointer to dsi_smartdma_handle_t structure which stores the transfer state.
 * param xfer Pointer to the transfer structure.
 *
 * retval kStatus_Success Data transfer started successfully.
 * retval kStatus_DSI_Busy Failed to start transfer because DSI is busy with pervious transfer.
 * retval kStatus_DSI_NotSupported Transfer format not supported.
 */
status_t DSI_TransferWriteMemorySMARTDMA(MIPI_DSI_HOST_Type *base,
                                         dsi_smartdma_handle_t *handle,
                                         dsi_smartdma_write_mem_transfer_t *xfer)
{
    assert(NULL != handle);

    status_t status;
    uint32_t smartdmaApi;

    if (handle->isBusy)
    {
        status = kStatus_DSI_Busy;
    }
    else
    {
        if (((xfer->inputFormat == kDSI_SMARTDMA_InputPixelFormatRGB565) &&
             ((xfer->outputFormat == kDSI_SMARTDMA_OutputPixelFormatRGB565) ||
              (xfer->outputFormat == kDSI_SMARTDMA_OutputPixelFormatRGB888))) ||
            ((xfer->inputFormat == kDSI_SMARTDMA_InputPixelFormatRGB888) &&
             (xfer->outputFormat == kDSI_SMARTDMA_OutputPixelFormatRGB888)) ||
            ((xfer->inputFormat == kDSI_SMARTDMA_InputPixelFormatXRGB8888) &&
             (xfer->outputFormat == kDSI_SMARTDMA_OutputPixelFormatRGB888)))
        {
            if (xfer->inputFormat == kDSI_SMARTDMA_InputPixelFormatRGB565)
            {
                if (xfer->outputFormat == kDSI_SMARTDMA_OutputPixelFormatRGB565)
                {
                    smartdmaApi = (uint32_t)kSMARTDMA_MIPI_RGB565_DMA;
                }
                else
                {
                    smartdmaApi = (uint32_t)kSMARTDMA_MIPI_RGB5652RGB888_DMA;
                }
            }
            else if (xfer->inputFormat == kDSI_SMARTDMA_InputPixelFormatRGB888)
            {
                smartdmaApi = (uint32_t)kSMARTDMA_MIPI_RGB888_DMA;
            }
            else
            {
                smartdmaApi = (uint32_t)kSMARTDMA_MIPI_XRGB2RGB_DMA;
            }

            if (xfer->twoDimension)
            {
                if (smartdmaApi == (uint32_t)kSMARTDMA_MIPI_RGB5652RGB888_DMA)
                {
                    return kStatus_DSI_NotSupported;
                }
                handle->param2d.p_buffer             = xfer->data;
                handle->param2d.minorLoop            = xfer->minorLoop;
                handle->param2d.minorLoopOffset      = xfer->minorLoopOffset;
                handle->param2d.majorLoop            = xfer->majorLoop;
                handle->param2d.smartdma_stack       = handle->smartdmaStack;
                handle->param2d.disablePixelByteSwap = (uint32_t)xfer->disablePixelByteSwap;
            }
            else
            {
                handle->param.p_buffer             = xfer->data;
                handle->param.buffersize           = xfer->dataSize;
                handle->param.smartdma_stack       = handle->smartdmaStack;
                handle->param.disablePixelByteSwap = (uint32_t)xfer->disablePixelByteSwap;
            }

            handle->isBusy = true;
            DSI_EnableInterrupts(base, (uint32_t)kDSI_InterruptGroup1ApbTxDone | (uint32_t)kDSI_InterruptGroup1HtxTo,
                                 0U);
            SMARTDMA_Reset();

            if (xfer->twoDimension)
            {
                smartdmaApi += 1U;
                SMARTDMA_Boot(smartdmaApi, &handle->param2d, 0);
            }
            else
            {
                SMARTDMA_Boot(smartdmaApi, &handle->param, 0);
            }

            status = kStatus_Success;
        }
        else
        {
            status = kStatus_DSI_NotSupported;
        }
    }

    return status;
}

/*!
 * brief Callback when SMARTDMA done.
 *
 * param param Callback parameter passed to SMARTDMA.
 */
static void DSI_SMARTDMA_Callback(void *param)
{
    dsi_smartdma_handle_t *handle = (dsi_smartdma_handle_t *)param;

    uint32_t intFlags1, intFlags2;

    DSI_DisableInterrupts(handle->dsi, (uint32_t)kDSI_InterruptGroup1ApbTxDone | (uint32_t)kDSI_InterruptGroup1HtxTo,
                          0U);

    DSI_GetAndClearInterruptStatus(handle->dsi, &intFlags1, &intFlags2);

    handle->isBusy = false;

    if (NULL != handle->callback)
    {
        handle->callback(handle->dsi, handle, kStatus_Success, handle->userData);
    }
}
