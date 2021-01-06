/*
 * Copyright (c) 2018, Freescale Semiconductor, Inc.
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_pdm_sdma.h"
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.pdm_sdma"
#endif

/*******************************************************************************
 * Definitations
 ******************************************************************************/

/*<! Structure definition for uart_sdma_private_handle_t. The structure is private. */
typedef struct _pdm_sdma_private_handle
{
    PDM_Type *base;
    pdm_sdma_handle_t *handle;
} pdm_sdma_private_handle_t;

/* Base pointer array */
static PDM_Type *const s_pdmBases[] = PDM_BASE_PTRS;

/*<! Private handle only used for internally. */
static pdm_sdma_private_handle_t s_sdmaPrivateHandle[ARRAY_SIZE(s_pdmBases)];

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief PDM SDMA callback for send.
 *
 * @param handle pointer to pdm_sdma_handle_t structure which stores the transfer state.
 * @param userData Parameter for user callback.
 * @param done If the DMA transfer finished.
 * @param tcds The TCD index.
 */
static void PDM_SDMACallback(sdma_handle_t *handle, void *userData, bool done, uint32_t tcds);
/*******************************************************************************
 * Code
 ******************************************************************************/
static void PDM_SDMACallback(sdma_handle_t *handle, void *userData, bool done, uint32_t tcds)
{
    pdm_sdma_private_handle_t *privHandle = (pdm_sdma_private_handle_t *)userData;
    pdm_sdma_handle_t *pdmHandle          = privHandle->handle;

    /* If finished a block, call the callback function */
    (void)memset(&pdmHandle->pdmQueue[pdmHandle->queueDriver], 0, sizeof(pdm_transfer_t));
    pdmHandle->queueDriver = (pdmHandle->queueDriver + 1U) % PDM_XFER_QUEUE_SIZE;
    if (pdmHandle->callback != NULL)
    {
        (pdmHandle->callback)(privHandle->base, pdmHandle, kStatus_PDM_Idle, pdmHandle->userData);
    }

    /* If all data finished, just stop the transfer */
    if (pdmHandle->pdmQueue[pdmHandle->queueDriver].data == NULL)
    {
        PDM_TransferAbortReceiveSDMA(privHandle->base, pdmHandle);
    }
}

/*!
 * brief Initializes the PDM eDMA handle.
 *
 * This function initializes the PDM DMA handle, which can be used for other PDM master transactional APIs.
 * Usually, for a specified PDM instance, call this API once to get the initialized handle.
 *
 * param base PDM base pointer.
 * param handle PDM eDMA handle pointer.
 * param base PDM peripheral base address.
 * param callback Pointer to user callback function.
 * param userData User parameter passed to the callback function.
 * param dmaHandle eDMA handle pointer, this handle shall be static allocated by users.
 * param dma request source.
 */
void PDM_TransferCreateHandleSDMA(PDM_Type *base,
                                  pdm_sdma_handle_t *handle,
                                  pdm_sdma_callback_t callback,
                                  void *userData,
                                  sdma_handle_t *dmaHandle,
                                  uint32_t eventSource)
{
    assert((handle != NULL) && (dmaHandle != NULL));

    uint32_t instance = PDM_GetInstance(base);

    /* Zero the handle */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set pdm base to handle */
    handle->dmaHandle   = dmaHandle;
    handle->callback    = callback;
    handle->userData    = userData;
    handle->eventSource = eventSource;
    handle->fifoWidth   = FSL_FEATURE_PDM_FIFO_WIDTH;

    /* Set PDM state to idle */
    handle->state = kStatus_PDM_Idle;

    s_sdmaPrivateHandle[instance].base   = base;
    s_sdmaPrivateHandle[instance].handle = handle;

    /* Need to use scatter gather */
    SDMA_InstallBDMemory(dmaHandle, handle->bdPool, PDM_XFER_QUEUE_SIZE);

    /* Install callback for Tx dma channel */
    SDMA_SetCallback(dmaHandle, PDM_SDMACallback, &s_sdmaPrivateHandle[instance]);
}

/*!
 * brief PDM channel configurations.
 *
 * param base PDM base pointer.
 * param handle PDM eDMA handle pointer.
 * param channel channel number.
 * param config channel configurations.
 */
void PDM_SetChannelConfigSDMA(PDM_Type *base,
                              pdm_sdma_handle_t *handle,
                              uint32_t channel,
                              const pdm_channel_config_t *config)
{
    assert(NULL != config);

    /* channel configurations */
    PDM_SetChannelConfig(base, channel, config);

    /* record end channel number */
    handle->endChannel = (uint8_t)channel;
    /* increase totoal enabled channel number */
    handle->channelNums++;
    /* increase count pre channel numbers */
    handle->count = (uint8_t)(handle->channelNums * (base->FIFO_CTRL & PDM_FIFO_CTRL_FIFOWMK_MASK));
}

/*!
 * brief Performs a non-blocking PDM receive using eDMA.
 *
 * note This interface returns immediately after the transfer initiates. Call
 * the PDM_GetReceiveRemainingBytes to poll the transfer status and check whether the PDM transfer is finished.
 *
 * param base PDM base pointer
 * param handle PDM eDMA handle pointer.
 * param xfer Pointer to DMA transfer structure.
 * retval kStatus_Success Start a PDM eDMA receive successfully.
 * retval kStatus_InvalidArgument The input argument is invalid.
 * retval kStatus_RxBusy PDM is busy receiving data.
 */
status_t PDM_TransferReceiveSDMA(PDM_Type *base, pdm_sdma_handle_t *handle, pdm_transfer_t *xfer)
{
    assert((handle != NULL) && (xfer != NULL));

    sdma_transfer_config_t config = {0};
    uint32_t startAddr =
        PDM_GetDataRegisterAddress(base, ((uint32_t)handle->endChannel - ((uint32_t)handle->channelNums - 1U)));
    sdma_peripheral_t perType = kSDMA_PeripheralMultiFifoPDM;

    /* Check if input parameter invalid */
    if ((xfer->data == NULL) || (xfer->dataSize == 0U))
    {
        return kStatus_InvalidArgument;
    }

    if (handle->pdmQueue[handle->queueUser].data != NULL)
    {
        return kStatus_PDM_QueueFull;
    }

    /* Update queue state  */
    handle->transferSize[handle->queueUser]      = xfer->dataSize;
    handle->pdmQueue[handle->queueUser].data     = xfer->data;
    handle->pdmQueue[handle->queueUser].dataSize = xfer->dataSize;

    /* Prepare sdma configure */
    SDMA_PrepareTransfer(&config, startAddr, (uint32_t)xfer->data, handle->fifoWidth, handle->fifoWidth,
                         (uint32_t)handle->count * handle->fifoWidth, xfer->dataSize, handle->eventSource, perType,
                         kSDMA_PeripheralToMemory);

    /* multi fifo configurations */
    SDMA_SetMultiFifoConfig(&config, handle->channelNums,
                            (uint32_t)FSL_FEATURE_PDM_FIFO_OFFSET / sizeof(uint32_t) - 1U);
    /* enable sw done for PDM */
    SDMA_SetDoneConfig(handle->dmaHandle->base, &config, kSDMA_PeripheralMultiFifoPDM, kSDMA_DoneSrcSW);

    if (handle->queueUser == PDM_XFER_QUEUE_SIZE - 1U)
    {
        SDMA_ConfigBufferDescriptor(&handle->bdPool[handle->queueUser], startAddr, (uint32_t)xfer->data,
                                    config.destTransferSize, xfer->dataSize, true, true, true,
                                    kSDMA_PeripheralToMemory);
    }
    else
    {
        SDMA_ConfigBufferDescriptor(&handle->bdPool[handle->queueUser], startAddr, (uint32_t)xfer->data,
                                    config.destTransferSize, xfer->dataSize, true, true, false,
                                    kSDMA_PeripheralToMemory);
    }

    handle->queueUser = (handle->queueUser + 1U) % PDM_XFER_QUEUE_SIZE;

    if (handle->state != (uint32_t)kStatus_PDM_Busy)
    {
        SDMA_SubmitTransfer(handle->dmaHandle, &config);

        /* Start DMA transfer */
        SDMA_StartTransfer(handle->dmaHandle);
    }

    handle->state = kStatus_PDM_Busy;

    /* Enable DMA enable bit */
    PDM_EnableDMA(base, true);
    /* enable PDM */
    PDM_Enable(base, true);

    return kStatus_Success;
}

/*!
 * brief Aborts a PDM receive using eDMA.
 *
 * param base PDM base pointer
 * param handle PDM eDMA handle pointer.
 */
void PDM_TransferAbortReceiveSDMA(PDM_Type *base, pdm_sdma_handle_t *handle)
{
    assert(handle != NULL);

    /* Disable dma */
    SDMA_AbortTransfer(handle->dmaHandle);

    /* Disable DMA enable bit */
    PDM_EnableDMA(base, false);

    /* Set the handle state */
    handle->state = kStatus_PDM_Idle;
}
