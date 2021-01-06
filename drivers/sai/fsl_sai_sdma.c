/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_sai_sdma.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.sai_sdma"
#endif

/*******************************************************************************
 * Definitations
 ******************************************************************************/
/*<! Structure definition for uart_sdma_private_handle_t. The structure is private. */
typedef struct _sai_sdma_private_handle
{
    I2S_Type *base;
    sai_sdma_handle_t *handle;
} sai_sdma_private_handle_t;

/*!@brief _sai_sdma_transfer_state */
enum
{
    kSAI_Busy = 0x0U, /*!< SAI is busy */
    kSAI_Idle,        /*!< Transfer is done. */
};

static I2S_Type *const s_saiBases[] = I2S_BASE_PTRS;

/*<! Private handle only used for internally. */
static sai_sdma_private_handle_t s_sdmaPrivateHandle[FSL_FEATURE_SOC_I2S_COUNT][2];

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get the instance number for SAI.
 *
 * @param base SAI base pointer.
 */
static uint32_t SAI_GetInstance(I2S_Type *base);

/*!
 * @brief SAI SDMA callback for send.
 *
 * @param handle pointer to sai_sdma_handle_t structure which stores the transfer state.
 * @param userData Parameter for user callback.
 * @param done If the DMA transfer finished.
 * @param tcds The TCD index.
 */
static void SAI_TxSDMACallback(sdma_handle_t *handle, void *userData, bool transferDone, uint32_t bdIndex);

/*!
 * @brief SAI SDMA callback for receive.
 *
 * @param handle pointer to sai_sdma_handle_t structure which stores the transfer state.
 * @param userData Parameter for user callback.
 * @param done If the DMA transfer finished.
 * @param tcds The TCD index.
 */
static void SAI_RxSDMACallback(sdma_handle_t *handle, void *userData, bool transferDone, uint32_t bdIndex);

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t SAI_GetInstance(I2S_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_saiBases); instance++)
    {
        if (s_saiBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_saiBases));

    return instance;
}

static void SAI_TxSDMACallback(sdma_handle_t *handle, void *userData, bool transferDone, uint32_t bdIndex)
{
    sai_sdma_private_handle_t *privHandle = (sai_sdma_private_handle_t *)userData;
    sai_sdma_handle_t *saiHandle          = privHandle->handle;

    /* If finished a block, call the callback function */
    (void)memset(&saiHandle->saiQueue[saiHandle->queueDriver], 0, sizeof(sai_transfer_t));
    saiHandle->queueDriver = (saiHandle->queueDriver + 1U) % SAI_XFER_QUEUE_SIZE;
    /* Stop SDMA transfer */
    SDMA_StopChannel(handle->base, handle->channel);
    if (saiHandle->callback != NULL)
    {
        (saiHandle->callback)(privHandle->base, saiHandle, kStatus_SAI_TxIdle, saiHandle->userData);
    }

    /* If all data finished, just stop the transfer */
    if (saiHandle->saiQueue[saiHandle->queueDriver].data == NULL)
    {
        SAI_TransferAbortSendSDMA(privHandle->base, saiHandle);
    }
}

static void SAI_RxSDMACallback(sdma_handle_t *handle, void *userData, bool transferDone, uint32_t bdIndex)
{
    sai_sdma_private_handle_t *privHandle = (sai_sdma_private_handle_t *)userData;
    sai_sdma_handle_t *saiHandle          = privHandle->handle;

    /* If finished a block, call the callback function */
    (void)memset(&saiHandle->saiQueue[saiHandle->queueDriver], 0, sizeof(sai_transfer_t));
    saiHandle->queueDriver = (saiHandle->queueDriver + 1U) % SAI_XFER_QUEUE_SIZE;
    if (saiHandle->callback != NULL)
    {
        (saiHandle->callback)(privHandle->base, saiHandle, kStatus_SAI_RxIdle, saiHandle->userData);
    }

    /* If all data finished, just stop the transfer */
    if (saiHandle->saiQueue[saiHandle->queueDriver].data == NULL)
    {
        SAI_TransferAbortReceiveSDMA(privHandle->base, saiHandle);
    }
}

/*!
 * brief Initializes the SAI SDMA handle.
 *
 * This function initializes the SAI master DMA handle, which can be used for other SAI master transactional APIs.
 * Usually, for a specified SAI instance, call this API once to get the initialized handle.
 *
 * param base SAI base pointer.
 * param handle SAI SDMA handle pointer.
 * param base SAI peripheral base address.
 * param callback Pointer to user callback function.
 * param userData User parameter passed to the callback function.
 * param dmaHandle SDMA handle pointer, this handle shall be static allocated by users.
 */
void SAI_TransferTxCreateHandleSDMA(I2S_Type *base,
                                    sai_sdma_handle_t *handle,
                                    sai_sdma_callback_t callback,
                                    void *userData,
                                    sdma_handle_t *dmaHandle,
                                    uint32_t eventSource)
{
    assert((handle != NULL) && (dmaHandle != NULL));

    uint32_t instance = SAI_GetInstance(base);

    /* Zero the handle */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set sai base to handle */
    handle->dmaHandle   = dmaHandle;
    handle->callback    = callback;
    handle->userData    = userData;
    handle->eventSource = eventSource;

    /* Set SAI state to idle */
    handle->state = (uint32_t)kSAI_Idle;

    s_sdmaPrivateHandle[instance][0].base   = base;
    s_sdmaPrivateHandle[instance][0].handle = handle;

    SDMA_InstallBDMemory(dmaHandle, handle->bdPool, SAI_XFER_QUEUE_SIZE);

    /* Install callback for Tx dma channel */
    SDMA_SetCallback(dmaHandle, SAI_TxSDMACallback, &s_sdmaPrivateHandle[instance][0]);
}

/*!
 * brief Initializes the SAI Rx SDMA handle.
 *
 * This function initializes the SAI slave DMA handle, which can be used for other SAI master transactional APIs.
 * Usually, for a specified SAI instance, call this API once to get the initialized handle.
 *
 * param base SAI base pointer.
 * param handle SAI SDMA handle pointer.
 * param base SAI peripheral base address.
 * param callback Pointer to user callback function.
 * param userData User parameter passed to the callback function.
 * param dmaHandle SDMA handle pointer, this handle shall be static allocated by users.
 */
void SAI_TransferRxCreateHandleSDMA(I2S_Type *base,
                                    sai_sdma_handle_t *handle,
                                    sai_sdma_callback_t callback,
                                    void *userData,
                                    sdma_handle_t *dmaHandle,
                                    uint32_t eventSource)
{
    assert((handle != NULL) && (dmaHandle != NULL));

    uint32_t instance = SAI_GetInstance(base);

    /* Zero the handle */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set sai base to handle */
    handle->dmaHandle   = dmaHandle;
    handle->callback    = callback;
    handle->userData    = userData;
    handle->eventSource = eventSource;

    /* Set SAI state to idle */
    handle->state = (uint32_t)kSAI_Idle;

    s_sdmaPrivateHandle[instance][1].base   = base;
    s_sdmaPrivateHandle[instance][1].handle = handle;

    SDMA_InstallBDMemory(dmaHandle, handle->bdPool, SAI_XFER_QUEUE_SIZE);

    /* Install callback for Tx dma channel */
    SDMA_SetCallback(dmaHandle, SAI_RxSDMACallback, &s_sdmaPrivateHandle[instance][1]);
}

/*!
 * brief Configures the SAI Tx audio format.
 *
 * The audio format can be changed at run-time. This function configures the sample rate and audio data
 * format to be transferred. This function also sets the SDMA parameter according to formatting requirements.
 *
 * param base SAI base pointer.
 * param handle SAI SDMA handle pointer.
 * param format Pointer to SAI audio data format structure.
 * param mclkSourceClockHz SAI master clock source frequency in Hz.
 * param bclkSourceClockHz SAI bit clock source frequency in Hz. If bit clock source is master
 * clock, this value should equals to masterClockHz in format.
 * retval kStatus_Success Audio format set successfully.
 * retval kStatus_InvalidArgument The input argument is invalid.
 */
void SAI_TransferTxSetFormatSDMA(I2S_Type *base,
                                 sai_sdma_handle_t *handle,
                                 sai_transfer_format_t *format,
                                 uint32_t mclkSourceClockHz,
                                 uint32_t bclkSourceClockHz)
{
    assert((handle != NULL) && (format != NULL));

    /* Configure the audio format to SAI registers */
    SAI_TxSetFormat(base, format, mclkSourceClockHz, bclkSourceClockHz);

    /* Get the transfer size from format, this should be used in SDMA configuration */
    if (format->bitWidth == 24U)
    {
        handle->bytesPerFrame = 4U;
    }
    else
    {
        handle->bytesPerFrame = (uint8_t)(format->bitWidth / 8U);
    }

    /* Update the data channel SAI used */
    handle->channel = format->channel;

    if (format->channelNums == 0U)
    {
        format->channelNums = 1U;
    }
    handle->channelNums = format->channelNums;
    handle->channelMask = format->channelMask;
    if (format->channelNums > 1U)
    {
        /* fifo address offset, 4U is the address offset between each fifo */
        handle->fifoOffset = ((format->endChannel - format->channel) * 4U) / (format->channelNums - 1U);
    }
    else
    {
        handle->fifoOffset = 0U;
    }

#if defined(FSL_FEATURE_SAI_FIFO_COUNT) && (FSL_FEATURE_SAI_FIFO_COUNT > 1)
    handle->count = (uint8_t)((uint8_t)FSL_FEATURE_SAI_FIFO_COUNT - format->watermark) * format->channelNums;
#else
    handle->count = 1U * format->channelNums;
#endif /* FSL_FEATURE_SAI_FIFO_COUNT */

    /* Clear the channel enable bits until do a send/receive */
    base->TCR3 &= ~I2S_TCR3_TCE_MASK;
}

/*!
 * brief Configures the SAI Tx audio.
 *
 * param base SAI base pointer.
 * param handle SAI SDMA handle pointer.
 * param saiConfig sai configurations
 */
void SAI_TransferTxSetConfigSDMA(I2S_Type *base, sai_sdma_handle_t *handle, sai_transceiver_t *saiConfig)
{
    assert((handle != NULL) && (saiConfig != NULL));

    /* Configure the audio format to SAI registers */
    SAI_TxSetConfig(base, saiConfig);

    handle->bytesPerFrame = saiConfig->serialData.dataWordLength / 8U;

    /* Update the data channel SAI used */
    handle->channel = saiConfig->startChannel;

    if (saiConfig->channelNums == 0U)
    {
        saiConfig->channelNums = 1U;
    }
    handle->channelNums = saiConfig->channelNums;
    handle->channelMask = saiConfig->channelMask;
    if (saiConfig->channelNums > 1U)
    {
        /* fifo address offset, 4U is the address offset between each fifo */
        handle->fifoOffset = ((saiConfig->endChannel - saiConfig->startChannel) * 4U) / (saiConfig->channelNums - 1U);
    }
    else
    {
        handle->fifoOffset = 0U;
    }

#if defined(FSL_FEATURE_SAI_FIFO_COUNT) && (FSL_FEATURE_SAI_FIFO_COUNT > 1)
    handle->count =
        (uint8_t)((uint8_t)FSL_FEATURE_SAI_FIFO_COUNT - saiConfig->fifo.fifoWatermark) * saiConfig->channelNums;
#else
    handle->count = 1U * saiConfig->channelNums;
#endif /* FSL_FEATURE_SAI_FIFO_COUNT */

    /* Clear the channel enable bits until do a send/receive */
    base->TCR3 &= ~I2S_TCR3_TCE_MASK;
}

/*!
 * brief Configures the SAI Rx audio format.
 *
 * The audio format can be changed at run-time. This function configures the sample rate and audio data
 * format to be transferred. This function also sets the SDMA parameter according to formatting requirements.
 *
 * param base SAI base pointer.
 * param handle SAI SDMA handle pointer.
 * param format Pointer to SAI audio data format structure.
 * param mclkSourceClockHz SAI master clock source frequency in Hz.
 * param bclkSourceClockHz SAI bit clock source frequency in Hz. If a bit clock source is the master
 * clock, this value should equal to masterClockHz in format.
 * retval kStatus_Success Audio format set successfully.
 * retval kStatus_InvalidArgument The input argument is invalid.
 */
void SAI_TransferRxSetFormatSDMA(I2S_Type *base,
                                 sai_sdma_handle_t *handle,
                                 sai_transfer_format_t *format,
                                 uint32_t mclkSourceClockHz,
                                 uint32_t bclkSourceClockHz)
{
    assert((handle != NULL) && (format != NULL));

    /* Configure the audio format to SAI registers */
    SAI_RxSetFormat(base, format, mclkSourceClockHz, bclkSourceClockHz);

    /* Get the transfer size from format, this should be used in SDMA configuration */
    if (format->bitWidth == 24U)
    {
        handle->bytesPerFrame = 4U;
    }
    else
    {
        handle->bytesPerFrame = (uint8_t)(format->bitWidth / 8U);
    }

    /* configurations for multififo */
    if (format->channelNums == 0U)
    {
        format->channelNums = 1U;
    }

    handle->channelNums = format->channelNums;
    handle->channelMask = format->channelMask;

    if (format->channelNums > 1U)
    {
        /* fifo address offset, 4U is the address offset between each fifo */
        handle->fifoOffset = ((format->endChannel - format->channel) * 4U) / (format->channelNums - 1U);
    }
    else
    {
        handle->fifoOffset = 0U;
    }
    /* Update the data channel SAI used */
    handle->channel = format->channel;

#if defined(FSL_FEATURE_SAI_FIFO_COUNT) && (FSL_FEATURE_SAI_FIFO_COUNT > 1)
    handle->count = format->watermark * format->channelNums;
#else
    handle->count = 1U * format->channelNums;
#endif /* FSL_FEATURE_SAI_FIFO_COUNT */

    /* Clear the channel enable bits until do a send/receive */
    base->RCR3 &= ~I2S_RCR3_RCE_MASK;
}

/*!
 * brief Configures the SAI Rx audio.
 *
 * param base SAI base pointer.
 * param handle SAI SDMA handle pointer.
 * param saiConig sai configurations.
 */
void SAI_TransferRxSetConfigSDMA(I2S_Type *base, sai_sdma_handle_t *handle, sai_transceiver_t *saiConfig)
{
    assert((handle != NULL) && (saiConfig != NULL));

    /* Configure the audio format to SAI registers */
    SAI_RxSetConfig(base, saiConfig);

    handle->bytesPerFrame = saiConfig->serialData.dataWordLength / 8U;

    /* configurations for multififo */
    if (saiConfig->channelNums == 0U)
    {
        saiConfig->channelNums = 1U;
    }

    handle->channelNums = saiConfig->channelNums;
    handle->channelMask = saiConfig->channelMask;

    if (saiConfig->channelNums > 1U)
    {
        /* fifo address offset, 4U is the address offset between each fifo */
        handle->fifoOffset = ((saiConfig->endChannel - saiConfig->startChannel) * 4U) / (saiConfig->channelNums - 1U);
    }
    else
    {
        handle->fifoOffset = 0U;
    }
    /* Update the data channel SAI used */
    handle->channel = saiConfig->startChannel;

#if defined(FSL_FEATURE_SAI_FIFO_COUNT) && (FSL_FEATURE_SAI_FIFO_COUNT > 1)
    handle->count = saiConfig->fifo.fifoWatermark * saiConfig->channelNums;
#else
    handle->count = 1U * saiConfig->channelNums;
#endif /* FSL_FEATURE_SAI_FIFO_COUNT */

    /* Clear the channel enable bits until do a send/receive */
    base->RCR3 &= ~I2S_RCR3_RCE_MASK;
}

/*!
 * brief Performs a non-blocking SAI transfer using DMA.
 *
 * note This interface returns immediately after the transfer initiates. Call
 * SAI_GetTransferStatus to poll the transfer status and check whether the SAI transfer is finished.
 *
 * param base SAI base pointer.
 * param handle SAI SDMA handle pointer.
 * param xfer Pointer to the DMA transfer structure.
 * retval kStatus_Success Start a SAI SDMA send successfully.
 * retval kStatus_InvalidArgument The input argument is invalid.
 * retval kStatus_TxBusy SAI is busy sending data.
 */
status_t SAI_TransferSendSDMA(I2S_Type *base, sai_sdma_handle_t *handle, sai_transfer_t *xfer)
{
    assert((handle != NULL) && (xfer != NULL));

    sdma_transfer_config_t config = {0};
    uint32_t destAddr             = SAI_TxGetDataRegisterAddress(base, handle->channel);
    sdma_handle_t *dmaHandle      = handle->dmaHandle;
    sdma_peripheral_t perType     = kSDMA_PeripheralNormal;

    /* Check if input parameter invalid */
    if ((xfer->data == NULL) || (xfer->dataSize == 0U) || ((handle->channelNums > 1U) && (handle->fifoOffset == 0U)) ||
        ((handle->channelNums > 1U) &&
         ((uint16_t)handle->count * handle->bytesPerFrame > (uint16_t)kSDMA_MultiFifoWatermarkLevelMask)))
    {
        return kStatus_InvalidArgument;
    }

    if (handle->saiQueue[handle->queueUser].data != NULL)
    {
        return kStatus_SAI_QueueFull;
    }

    /* Change the state of handle */
    handle->transferSize[handle->queueUser]      = xfer->dataSize;
    handle->saiQueue[handle->queueUser].data     = xfer->data;
    handle->saiQueue[handle->queueUser].dataSize = xfer->dataSize;

#if defined(FSL_FEATURE_SOC_SPBA_COUNT) && (FSL_FEATURE_SOC_SPBA_COUNT > 0)
    bool isSpba = SDMA_IsPeripheralInSPBA((uint32_t)base);
    /* Judge if the instance is located in SPBA */
    if (isSpba)
    {
        perType = kSDMA_PeripheralNormal_SP;
    }
#endif /* FSL_FEATURE_SOC_SPBA_COUNT */

    /* if channel numbers > 1U, should enable multififo */
    if (handle->channelNums > 1U)
    {
        perType = kSDMA_PeripheralMultiFifoSaiTX;
        /* multi fifo configurations */
        SDMA_SetMultiFifoConfig(&config, handle->channelNums, (uint32_t)handle->fifoOffset / sizeof(uint32_t) - 1UL);
    }

    /* Prepare sdma configure */
    SDMA_PrepareTransfer(&config, (uint32_t)xfer->data, destAddr, handle->bytesPerFrame, handle->bytesPerFrame,
                         (uint32_t)handle->count * handle->bytesPerFrame, xfer->dataSize, handle->eventSource, perType,
                         kSDMA_MemoryToPeripheral);

    if (handle->queueUser == SAI_XFER_QUEUE_SIZE - 1U)
    {
        SDMA_ConfigBufferDescriptor(&dmaHandle->BDPool[handle->queueUser], (uint32_t)(xfer->data), destAddr,
                                    config.destTransferSize, xfer->dataSize, true, true, true,
                                    kSDMA_MemoryToPeripheral);
    }
    else
    {
        SDMA_ConfigBufferDescriptor(&dmaHandle->BDPool[handle->queueUser], (uint32_t)(xfer->data), destAddr,
                                    config.destTransferSize, xfer->dataSize, true, true, false,
                                    kSDMA_MemoryToPeripheral);
    }

    handle->queueUser = (handle->queueUser + 1U) % SAI_XFER_QUEUE_SIZE;

    if (handle->state != (uint32_t)kSAI_Busy)
    {
        SDMA_SubmitTransfer(handle->dmaHandle, &config);

        /* Start DMA transfer */
        SDMA_StartTransfer(handle->dmaHandle);

        /* Enable DMA enable bit */
        SAI_TxEnableDMA(base, kSAI_FIFORequestDMAEnable, true);

        /* Enable SAI Tx clock */
        SAI_TxEnable(base, true);

        /* Enable the channel FIFO */
        base->TCR3 |= I2S_TCR3_TCE(handle->channelMask);
    }
    handle->state = (uint32_t)kSAI_Busy;

    return kStatus_Success;
}

/*!
 * brief Performs a non-blocking SAI receive using SDMA.
 *
 * note This interface returns immediately after the transfer initiates. Call
 * the SAI_GetReceiveRemainingBytes to poll the transfer status and check whether the SAI transfer is finished.
 *
 * param base SAI base pointer
 * param handle SAI SDMA handle pointer.
 * param xfer Pointer to DMA transfer structure.
 * retval kStatus_Success Start a SAI SDMA receive successfully.
 * retval kStatus_InvalidArgument The input argument is invalid.
 * retval kStatus_RxBusy SAI is busy receiving data.
 */
status_t SAI_TransferReceiveSDMA(I2S_Type *base, sai_sdma_handle_t *handle, sai_transfer_t *xfer)
{
    assert((handle != NULL) && (xfer != NULL));

    sdma_transfer_config_t config = {0};
    sdma_handle_t *dmaHandle      = handle->dmaHandle;
    uint32_t srcAddr              = SAI_RxGetDataRegisterAddress(base, handle->channel);
    sdma_peripheral_t perType     = kSDMA_PeripheralNormal;

    /* Check if input parameter invalid */
    if ((xfer->data == NULL) || (xfer->dataSize == 0U) || ((handle->channelNums > 1U) && (handle->fifoOffset == 0U)) ||
        ((handle->channelNums > 1U) &&
         ((uint16_t)handle->count * handle->bytesPerFrame > (uint16_t)kSDMA_MultiFifoWatermarkLevelMask)))
    {
        return kStatus_InvalidArgument;
    }

    if (handle->saiQueue[handle->queueUser].data != NULL)
    {
        return kStatus_SAI_QueueFull;
    }

    /* Update queue state  */
    handle->transferSize[handle->queueUser]      = xfer->dataSize;
    handle->saiQueue[handle->queueUser].data     = xfer->data;
    handle->saiQueue[handle->queueUser].dataSize = xfer->dataSize;

#if defined(FSL_FEATURE_SOC_SPBA_COUNT) && (FSL_FEATURE_SOC_SPBA_COUNT > 0)
    bool isSpba = SDMA_IsPeripheralInSPBA((uint32_t)base);
    /* Judge if the instance is located in SPBA */
    if (isSpba)
    {
        perType = kSDMA_PeripheralNormal_SP;
    }
#endif /* FSL_FEATURE_SOC_SPBA_COUNT */

    /* if channel numbers > 1U, should enable multififo */
    if (handle->channelNums > 1U)
    {
        perType = kSDMA_PeripheralMultiFifoSaiRX;
        /* multi fifo configurations */
        SDMA_SetMultiFifoConfig(&config, handle->channelNums, (uint32_t)handle->fifoOffset / sizeof(uint32_t) - 1UL);
    }

    /* Prepare sdma configure */
    SDMA_PrepareTransfer(&config, srcAddr, (uint32_t)xfer->data, handle->bytesPerFrame, handle->bytesPerFrame,
                         (uint32_t)handle->count * handle->bytesPerFrame, xfer->dataSize, handle->eventSource, perType,
                         kSDMA_PeripheralToMemory);

    if (handle->queueUser == SAI_XFER_QUEUE_SIZE - 1U)
    {
        SDMA_ConfigBufferDescriptor(&dmaHandle->BDPool[handle->queueUser], srcAddr, (uint32_t)xfer->data,
                                    config.destTransferSize, xfer->dataSize, true, true, true,
                                    kSDMA_PeripheralToMemory);
    }
    else
    {
        SDMA_ConfigBufferDescriptor(&dmaHandle->BDPool[handle->queueUser], srcAddr, (uint32_t)xfer->data,
                                    config.destTransferSize, xfer->dataSize, true, true, false,
                                    kSDMA_PeripheralToMemory);
    }

    handle->queueUser = (handle->queueUser + 1U) % SAI_XFER_QUEUE_SIZE;

    if (handle->state != (uint32_t)kSAI_Busy)
    {
        SDMA_SubmitTransfer(handle->dmaHandle, &config);

        /* Start DMA transfer */
        SDMA_StartTransfer(handle->dmaHandle);

        /* Enable DMA enable bit */
        SAI_RxEnableDMA(base, kSAI_FIFORequestDMAEnable, true);

        /* Enable SAI Rx clock */
        SAI_RxEnable(base, true);

        /* Enable the channel FIFO */
        base->RCR3 |= I2S_RCR3_RCE(handle->channelMask);
    }

    handle->state = (uint32_t)kSAI_Busy;

    return kStatus_Success;
}

/*!
 * brief Aborts a SAI transfer using SDMA.
 *
 * param base SAI base pointer.
 * param handle SAI SDMA handle pointer.
 */
void SAI_TransferAbortSendSDMA(I2S_Type *base, sai_sdma_handle_t *handle)
{
    assert(handle != NULL);

    /* Disable dma */
    SDMA_AbortTransfer(handle->dmaHandle);

    /* Disable the channel FIFO */
    base->TCR3 &= ~I2S_TCR3_TCE_MASK;

    /* Disable DMA enable bit */
    SAI_TxEnableDMA(base, kSAI_FIFORequestDMAEnable, false);

    /* Reset the FIFO pointer, at the same time clear all error flags if set */
    base->TCSR |= (I2S_TCSR_FR_MASK | I2S_TCSR_SR_MASK);
    base->TCSR &= ~I2S_TCSR_SR_MASK;

    /* Disable Tx */
    SAI_TxEnable(base, false);

    /* Set the handle state */
    handle->state = (uint32_t)kSAI_Idle;
}

/*!
 * brief Aborts a SAI receive using SDMA.
 *
 * param base SAI base pointer
 * param handle SAI SDMA handle pointer.
 */
void SAI_TransferAbortReceiveSDMA(I2S_Type *base, sai_sdma_handle_t *handle)
{
    assert(handle != NULL);

    /* Disable dma */
    SDMA_AbortTransfer(handle->dmaHandle);

    /* Disable the channel FIFO */
    base->RCR3 &= ~I2S_RCR3_RCE_MASK;

    /* Disable DMA enable bit */
    SAI_RxEnableDMA(base, kSAI_FIFORequestDMAEnable, false);

    /* Disable Rx */
    SAI_RxEnable(base, false);

    /* Reset the FIFO pointer, at the same time clear all error flags if set */
    base->RCSR |= (I2S_RCSR_FR_MASK | I2S_RCSR_SR_MASK);
    base->RCSR &= ~I2S_RCSR_SR_MASK;

    /* Set the handle state */
    handle->state = (uint32_t)kSAI_Idle;
}
