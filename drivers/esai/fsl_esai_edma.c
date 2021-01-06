/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_esai_edma.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.esai_edma"
#endif

/*******************************************************************************
 * Definitations
 ******************************************************************************/
/* Used for 32byte aligned */
#define STCD_ADDR(address) (edma_tcd_t *)(((uint32_t)(address) + 32U) & ~0x1FU)

/*<! Structure definition for uart_edma_private_handle_t. The structure is private. */
typedef struct _esai_edma_private_handle
{
    ESAI_Type *base;
    esai_edma_handle_t *handle;
} esai_edma_private_handle_t;

/*!@brief _esai_edma_transfer_state */
enum
{
    kESAI_Busy = 0x0U, /*!< ESAI is busy */
    kESAI_Idle,        /*!< Transfer is done. */
};

/*<! Private handle only used for internally. */
static esai_edma_private_handle_t s_edmaPrivateHandle[FSL_FEATURE_SOC_ESAI_COUNT][2];

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief ESAI EDMA callback for send.
 *
 * @param handle pointer to esai_edma_handle_t structure which stores the transfer state.
 * @param userData Parameter for user callback.
 * @param done If the DMA transfer finished.
 * @param tcds The TCD index.
 */
static void ESAI_TxEDMACallback(edma_handle_t *handle, void *userData, bool done, uint32_t tcds);

/*!
 * @brief ESAI EDMA callback for receive.
 *
 * @param handle pointer to esai_edma_handle_t structure which stores the transfer state.
 * @param userData Parameter for user callback.
 * @param done If the DMA transfer finished.
 * @param tcds The TCD index.
 */
static void ESAI_RxEDMACallback(edma_handle_t *handle, void *userData, bool done, uint32_t tcds);

/*******************************************************************************
 * Code
 ******************************************************************************/
static void ESAI_TxEDMACallback(edma_handle_t *handle, void *userData, bool done, uint32_t tcds)
{
    esai_edma_private_handle_t *privHandle = (esai_edma_private_handle_t *)userData;
    esai_edma_handle_t *esaiHandle         = privHandle->handle;

    /* If finished a block, call the callback function */
    (void)memset(&esaiHandle->esaiQueue[esaiHandle->queueDriver], 0, sizeof(esai_transfer_t));
    esaiHandle->queueDriver = (esaiHandle->queueDriver + 1U) % ESAI_XFER_QUEUE_SIZE;
    if (esaiHandle->callback != NULL)
    {
        (esaiHandle->callback)(privHandle->base, esaiHandle, kStatus_ESAI_TxIdle, esaiHandle->userData);
    }

    /* If all data finished, just stop the transfer */
    if (esaiHandle->esaiQueue[esaiHandle->queueDriver].data == NULL)
    {
        ESAI_TransferAbortSendEDMA(privHandle->base, esaiHandle);
    }
}

static void ESAI_RxEDMACallback(edma_handle_t *handle, void *userData, bool done, uint32_t tcds)
{
    esai_edma_private_handle_t *privHandle = (esai_edma_private_handle_t *)userData;
    esai_edma_handle_t *esaiHandle         = privHandle->handle;

    /* If finished a block, call the callback function */
    (void)memset(&esaiHandle->esaiQueue[esaiHandle->queueDriver], 0, sizeof(esai_transfer_t));
    esaiHandle->queueDriver = (esaiHandle->queueDriver + 1U) % ESAI_XFER_QUEUE_SIZE;
    if (esaiHandle->callback != NULL)
    {
        (esaiHandle->callback)(privHandle->base, esaiHandle, kStatus_ESAI_RxIdle, esaiHandle->userData);
    }

    /* If all data finished, just stop the transfer */
    if (esaiHandle->esaiQueue[esaiHandle->queueDriver].data == NULL)
    {
        ESAI_TransferAbortReceiveEDMA(privHandle->base, esaiHandle);
    }
}

/*!
 * brief Initializes the ESAI eDMA handle.
 *
 * This function initializes the ESAI master DMA handle, which can be used for other ESAI master transactional APIs.
 * Usually, for a specified ESAI instance, call this API once to get the initialized handle.
 *
 * param base ESAI base pointer.
 * param handle ESAI eDMA handle pointer.
 * param base ESAI peripheral base address.
 * param callback Pointer to user callback function.
 * param userData User parameter passed to the callback function.
 * param dmaHandle eDMA handle pointer, this handle shall be static allocated by users.
 */
void ESAI_TransferTxCreateHandleEDMA(ESAI_Type *base,
                                     esai_edma_handle_t *handle,
                                     esai_edma_callback_t callback,
                                     void *userData,
                                     edma_handle_t *dmaHandle)
{
    assert((handle != NULL) && (dmaHandle != NULL));

    uint32_t instance = ESAI_GetInstance(base);

    /* Zero the handle */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set esai base to handle */
    handle->dmaHandle = dmaHandle;
    handle->callback  = callback;
    handle->userData  = userData;

    /* Set ESAI state to idle */
    handle->state = (uint32_t)kESAI_Idle;

    s_edmaPrivateHandle[instance][0].base   = base;
    s_edmaPrivateHandle[instance][0].handle = handle;

    /* Need to use scatter gather */
    EDMA_InstallTCDMemory(dmaHandle, STCD_ADDR(handle->tcd), ESAI_XFER_QUEUE_SIZE);

    /* Install callback for Tx dma channel */
    EDMA_SetCallback(dmaHandle, ESAI_TxEDMACallback, &s_edmaPrivateHandle[instance][0]);
}

/*!
 * brief Initializes the ESAI Rx eDMA handle.
 *
 * This function initializes the ESAI slave DMA handle, which can be used for other ESAI master transactional APIs.
 * Usually, for a specified ESAI instance, call this API once to get the initialized handle.
 *
 * param base ESAI base pointer.
 * param handle ESAI eDMA handle pointer.
 * param base ESAI peripheral base address.
 * param callback Pointer to user callback function.
 * param userData User parameter passed to the callback function.
 * param dmaHandle eDMA handle pointer, this handle shall be static allocated by users.
 */
void ESAI_TransferRxCreateHandleEDMA(ESAI_Type *base,
                                     esai_edma_handle_t *handle,
                                     esai_edma_callback_t callback,
                                     void *userData,
                                     edma_handle_t *dmaHandle)
{
    assert((handle != NULL) && (dmaHandle != NULL));

    uint32_t instance = ESAI_GetInstance(base);

    /* Zero the handle */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set esai base to handle */
    handle->dmaHandle = dmaHandle;
    handle->callback  = callback;
    handle->userData  = userData;

    /* Set ESAI state to idle */
    handle->state = (uint32_t)kESAI_Idle;

    s_edmaPrivateHandle[instance][1].base   = base;
    s_edmaPrivateHandle[instance][1].handle = handle;

    /* Need to use scatter gather */
    EDMA_InstallTCDMemory(dmaHandle, STCD_ADDR(handle->tcd), ESAI_XFER_QUEUE_SIZE);

    /* Install callback for Tx dma channel */
    EDMA_SetCallback(dmaHandle, ESAI_RxEDMACallback, &s_edmaPrivateHandle[instance][1]);
}

/*!
 * brief Configures the ESAI Tx audio format.
 *
 * The audio format can be changed at run-time. This function configures the sample rate and audio data
 * format to be transferred. This function also sets the eDMA parameter according to formatting requirements.
 *
 * param base ESAI base pointer.
 * param handle ESAI eDMA handle pointer.
 * param format Pointer to ESAI audio data format structure.
 * param hckClockHz HCK clock frequency in Hz.
 * param hclkSourceClockHz HCK clock source frequency in Hz.
 * retval kStatus_Success Audio format set successfully.
 * retval kStatus_InvalidArgument The input argument is invalid.
 */
void ESAI_TransferTxSetFormatEDMA(
    ESAI_Type *base, esai_edma_handle_t *handle, esai_format_t *format, uint32_t hckClockHz, uint32_t hclkSourceClockHz)
{
    assert((handle != NULL) && (format != NULL));

    /* Configure the audio format to ESAI registers */
    ESAI_TxSetFormat(base, format, hckClockHz, hclkSourceClockHz);

    /* Get the transfer size from format, this should be used in EDMA configuration */
    ESAI_AnalysisSlot(format->slotType, &handle->slotLen, &handle->bitWidth);
    handle->sectionMap = format->sectionMap;

    /* Update the data channel ESAI used */
    handle->count = (uint8_t)FSL_FEATURE_ESAI_FIFO_SIZEn(base) -
                    (uint8_t)((base->TFCR & ESAI_TFCR_TFWM_MASK) >> ESAI_TFCR_TFWM_SHIFT);
}

/*!
 * brief Configures the ESAI Rx audio format.
 *
 * The audio format can be changed at run-time. This function configures the sample rate and audio data
 * format to be transferred. This function also sets the eDMA parameter according to formatting requirements.
 *
 * param base ESAI base pointer.
 * param handle ESAI eDMA handle pointer.
 * param format Pointer to ESAI audio data format structure.
 * param hckClockHz HCK clock frequency in Hz.
 * param hclkSourceClockHz HCK clock source frequency in Hz.
 * retval kStatus_Success Audio format set successfully.
 * retval kStatus_InvalidArgument The input argument is invalid.
 */
void ESAI_TransferRxSetFormatEDMA(
    ESAI_Type *base, esai_edma_handle_t *handle, esai_format_t *format, uint32_t hckClockHz, uint32_t hclkSourceClockHz)
{
    assert((handle != NULL) && (format != NULL));

    /* Configure the audio format to ESAI registers */
    ESAI_RxSetFormat(base, format, hckClockHz, hclkSourceClockHz);

    /* Get the transfer size from format, this should be used in EDMA configuration */
    ESAI_AnalysisSlot(format->slotType, &handle->slotLen, &handle->bitWidth);
    handle->sectionMap = format->sectionMap;

    /* Update the data channel ESAI used */
    handle->count = (uint8_t)((base->TFCR & ESAI_TFCR_TFWM_MASK) >> ESAI_TFCR_TFWM_SHIFT);
}

/*!
 * brief Performs a non-blocking ESAI transfer using DMA.
 *
 * note This interface returns immediately after the transfer initiates. Call
 * ESAI_GetTransferStatus to poll the transfer status and check whether the ESAI transfer is finished.
 *
 * param base ESAI base pointer.
 * param handle ESAI eDMA handle pointer.
 * param xfer Pointer to the DMA transfer structure.
 * retval kStatus_Success Start a ESAI eDMA send successfully.
 * retval kStatus_InvalidArgument The input argument is invalid.
 * retval kStatus_TxBusy ESAI is busy sending data.
 */
status_t ESAI_TransferSendEDMA(ESAI_Type *base, esai_edma_handle_t *handle, esai_transfer_t *xfer)
{
    assert((handle != NULL) && (xfer != NULL));

    edma_transfer_config_t config = {0};
    uint32_t destAddr             = ESAI_TxGetDataRegisterAddress(base);

    /* Check if input parameter invalid */
    if ((xfer->data == NULL) || (xfer->dataSize == 0U))
    {
        return kStatus_InvalidArgument;
    }

    if (handle->esaiQueue[handle->queueUser].data != NULL)
    {
        return kStatus_ESAI_QueueFull;
    }

    /* Change the state of handle */
    handle->state = (uint32_t)kESAI_Busy;

    /* Update the queue state */
    handle->transferSize[handle->queueUser]       = xfer->dataSize;
    handle->esaiQueue[handle->queueUser].data     = xfer->data;
    handle->esaiQueue[handle->queueUser].dataSize = xfer->dataSize;
    handle->queueUser                             = (handle->queueUser + 1U) % ESAI_XFER_QUEUE_SIZE;

    /* Prepare edma configure */
    EDMA_PrepareTransfer(&config, xfer->data, handle->bitWidth / 8UL, (void *)(uint32_t *)destAddr,
                         handle->bitWidth / 8UL, (uint32_t)handle->count * handle->bitWidth / 8U, xfer->dataSize,
                         kEDMA_MemoryToPeripheral);

    /* Store the initially configured eDMA minor byte transfer count into the ESAI handle */
    handle->nbytes = handle->count * handle->bitWidth / 8U;

    (void)EDMA_SubmitTransfer(handle->dmaHandle, &config);

    /* Start DMA transfer */
    EDMA_StartTransfer(handle->dmaHandle);

    /* Enable ESAI Tx clock */
    ESAI_TxEnable(base, handle->sectionMap);

    return kStatus_Success;
}

/*!
 * brief Performs a non-blocking ESAI receive using eDMA.
 *
 * note This interface returns immediately after the transfer initiates. Call
 * the ESAI_GetReceiveRemainingBytes to poll the transfer status and check whether the ESAI transfer is finished.
 *
 * param base ESAI base pointer
 * param handle ESAI eDMA handle pointer.
 * param xfer Pointer to DMA transfer structure.
 * retval kStatus_Success Start a ESAI eDMA receive successfully.
 * retval kStatus_InvalidArgument The input argument is invalid.
 * retval kStatus_RxBusy ESAI is busy receiving data.
 */
status_t ESAI_TransferReceiveEDMA(ESAI_Type *base, esai_edma_handle_t *handle, esai_transfer_t *xfer)
{
    assert((handle != NULL) && (xfer != NULL));

    edma_transfer_config_t config = {0};
    uint32_t srcAddr              = ESAI_RxGetDataRegisterAddress(base);

    /* Check if input parameter invalid */
    if ((xfer->data == NULL) || (xfer->dataSize == 0U))
    {
        return kStatus_InvalidArgument;
    }

    if (handle->esaiQueue[handle->queueUser].data != NULL)
    {
        return kStatus_ESAI_QueueFull;
    }

    /* Change the state of handle */
    handle->state = (uint32_t)kESAI_Busy;

    /* Update queue state  */
    handle->transferSize[handle->queueUser]       = xfer->dataSize;
    handle->esaiQueue[handle->queueUser].data     = xfer->data;
    handle->esaiQueue[handle->queueUser].dataSize = xfer->dataSize;
    handle->queueUser                             = (handle->queueUser + 1U) % ESAI_XFER_QUEUE_SIZE;

    /* Prepare edma configure */
    EDMA_PrepareTransfer(&config, (void *)(uint32_t *)srcAddr, handle->bitWidth / 8UL, xfer->data,
                         handle->bitWidth / 8UL, (uint32_t)handle->count * handle->bitWidth / 8U, xfer->dataSize,
                         kEDMA_PeripheralToMemory);

    /* Store the initially configured eDMA minor byte transfer count into the ESAI handle */
    handle->nbytes = handle->count * handle->bitWidth / 8U;

    (void)EDMA_SubmitTransfer(handle->dmaHandle, &config);

    /* Start DMA transfer */
    EDMA_StartTransfer(handle->dmaHandle);

    /* Enable ESAI Rx clock */
    ESAI_RxEnable(base, handle->sectionMap);

    return kStatus_Success;
}

/*!
 * brief Aborts a ESAI transfer using eDMA.
 *
 * param base ESAI base pointer.
 * param handle ESAI eDMA handle pointer.
 */
void ESAI_TransferAbortSendEDMA(ESAI_Type *base, esai_edma_handle_t *handle)
{
    assert(handle != NULL);

    /* Disable dma */
    EDMA_AbortTransfer(handle->dmaHandle);

    /* Disable Tx */
    ESAI_TxEnable(base, 0x0);

    /* Set the handle state */
    handle->state = (uint32_t)kESAI_Idle;
}

/*!
 * brief Aborts a ESAI receive using eDMA.
 *
 * param base ESAI base pointer
 * param handle ESAI eDMA handle pointer.
 */
void ESAI_TransferAbortReceiveEDMA(ESAI_Type *base, esai_edma_handle_t *handle)
{
    assert(handle != NULL);

    /* Disable dma */
    EDMA_AbortTransfer(handle->dmaHandle);

    /* Disable Rx */
    ESAI_RxEnable(base, 0x0);

    /* Set the handle state */
    handle->state = (uint32_t)kESAI_Idle;
}

/*!
 * brief Gets byte count sent by ESAI.
 *
 * param base ESAI base pointer.
 * param handle ESAI eDMA handle pointer.
 * param count Bytes count sent by ESAI.
 * retval kStatus_Success Succeed get the transfer count.
 * retval kStatus_NoTransferInProgress There is no non-blocking transaction in progress.
 */
status_t ESAI_TransferGetSendCountEDMA(ESAI_Type *base, esai_edma_handle_t *handle, size_t *count)
{
    assert(handle != NULL);

    status_t status = kStatus_Success;

    if (handle->state != (uint32_t)kESAI_Busy)
    {
        status = kStatus_NoTransferInProgress;
    }
    else
    {
        *count = (handle->transferSize[handle->queueDriver] -
                  (uint32_t)handle->nbytes *
                      EDMA_GetRemainingMajorLoopCount(handle->dmaHandle->base, handle->dmaHandle->channel));
    }

    return status;
}

/*!
 * brief Gets byte count received by ESAI.
 *
 * param base ESAI base pointer
 * param handle ESAI eDMA handle pointer.
 * param count Bytes count received by ESAI.
 * retval kStatus_Success Succeed get the transfer count.
 * retval kStatus_NoTransferInProgress There is no non-blocking transaction in progress.
 */
status_t ESAI_TransferGetReceiveCountEDMA(ESAI_Type *base, esai_edma_handle_t *handle, size_t *count)
{
    assert(handle != NULL);

    status_t status = kStatus_Success;

    if (handle->state != (uint32_t)kESAI_Busy)
    {
        status = kStatus_NoTransferInProgress;
    }
    else
    {
        *count = (handle->transferSize[handle->queueDriver] -
                  (uint32_t)handle->nbytes *
                      EDMA_GetRemainingMajorLoopCount(handle->dmaHandle->base, handle->dmaHandle->channel));
    }

    return status;
}
