/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_asrc_sdma.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.easrc_sdma"
#endif

/*******************************************************************************
 * Definitations
 ******************************************************************************/
/*<! Structure definition for uart_sdma_private_handle_t. The structure is private. */
typedef struct _asrc_sdma_private_handle
{
    ASRC_Type *base;
    asrc_sdma_handle_t *handle;
} asrc_sdma_private_handle_t;
/*! @brief Private handle only used for internally. */
static asrc_sdma_private_handle_t s_sdmaPrivateHandle[FSL_FEATURE_SOC_ASRC_COUNT]
                                                     [ASRC_SUPPORT_MAXIMUM_CONTEXT_PROCESSOR_NUMBER];
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief ASRC SDMA callback for input data transfer finished.
 *
 * @param handle pointer to asrc_sdma_handle_t structure which stores the transfer state.
 * @param userData Parameter for user callback.
 * @param done If the DMA transfer finished.
 * @param tcds The TCD index.
 */
static void ASRC_InSDMACallback(sdma_handle_t *handle, void *userData, bool transferDone, uint32_t bdIndex);

/*!
 * @brief ASRC SDMA callback for output data transfer finished.
 *
 * @param handle pointer to asrc_sdma_handle_t structure which stores the transfer state.
 * @param userData Parameter for user callback.
 * @param done If the DMA transfer finished.
 * @param tcds The TCD index.
 */
static void ASRC_OutSDMACallback(sdma_handle_t *handle, void *userData, bool transferDone, uint32_t bdIndex);

/*!
 * @brief ASRC submit output request .
 *
 * @param base ASRC base address.
 * @param handle ASRC sdma handler.
 * @param outDataAddr output peripheral fifo address.
 * @param outDataSize output sdma transfer data size.
 *
 */
static status_t ASRC_TransferSubmitOutM2MSDMA(ASRC_Type *base,
                                              asrc_sdma_handle_t *handle,
                                              uint32_t *outDataAddr,
                                              uint32_t outDataSize);

/*!
 * @brief ASRC sdma transfer output request .
 *
 * @param base ASRC base address.
 * @param handle ASRC sdma handler.
 * @param outDataAddr output peripheral fifo address.
 * @param outDataSize output sdma transfer data size.
 *
 */
static status_t ASRC_TransferOutSDMA(ASRC_Type *base,
                                     asrc_sdma_handle_t *handle,
                                     uint32_t *outDataAddr,
                                     uint32_t outDataSize);

/*!
 * @brief ASRC sdma transfer input request .
 *
 * @param base ASRC base address.
 * @param handle ASRC sdma handler.
 * @param inDataAddr ASRC input sdma source address.
 * @param inDataSize input sdma transfer data size.
 */
static status_t ASRC_TransferInSDMA(ASRC_Type *base,
                                    asrc_sdma_handle_t *handle,
                                    uint32_t *inDataAddr,
                                    uint32_t inDataSize);
/*******************************************************************************
 * Code
 ******************************************************************************/
static void ASRC_InSDMACallback(sdma_handle_t *handle, void *userData, bool transferDone, uint32_t bdIndex)
{
    asrc_sdma_private_handle_t *privHandle = (asrc_sdma_private_handle_t *)userData;
    asrc_sdma_handle_t *asrcHandle         = privHandle->handle;
    status_t callbackStatus                = kStatus_ASRCIdle;

    /* If finished a block, call the callback function */
    asrcHandle->inDMAHandle.asrcQueue[asrcHandle->inDMAHandle.queueDriver] = NULL;

    asrcHandle->inDMAHandle.queueDriver = (asrcHandle->inDMAHandle.queueDriver + 1U) % ASRC_XFER_IN_QUEUE_SIZE;

    if (asrcHandle->inDMAHandle.asrcQueue[asrcHandle->inDMAHandle.queueDriver] == NULL)
    {
        ASRC_TransferAbortInSDMA(privHandle->base, asrcHandle);
        callbackStatus = kStatus_ASRCQueueIdle;
    }

    if (asrcHandle->inDMAHandle.callback != NULL)
    {
        (asrcHandle->inDMAHandle.callback)(privHandle->base, asrcHandle, callbackStatus,
                                           asrcHandle->inDMAHandle.userData);
    }
}

static void ASRC_ReadFIFORemainedSampleSDMA(
    ASRC_Type *base, asrc_context_t context, uint32_t *outAddr, uint32_t outWidth, uint32_t size)
{
    uint32_t totalSize = size;
    uint32_t *addr     = outAddr;
    uint32_t i         = 0U;

    for (i = 0U; i < totalSize / outWidth; i++)
    {
        (void)ASRC_ReadFIFORemainedSample(base, context, addr, outWidth, 1U);
        addr = (uint32_t *)((uint32_t)addr + outWidth);
    }
}

static void ASRC_OutSDMACallback(sdma_handle_t *handle, void *userData, bool transferDone, uint32_t bdIndex)
{
    asrc_sdma_private_handle_t *privHandle = (asrc_sdma_private_handle_t *)userData;
    asrc_sdma_handle_t *asrcHandle         = privHandle->handle;
    uint32_t queueDriverIndex              = asrcHandle->outDMAHandle.queueDriver;
    status_t callbackStatus                = kStatus_ASRCIdle;

    /* If finished a block, call the callback function */
    asrcHandle->outDMAHandle.asrcQueue[queueDriverIndex] = NULL;
    asrcHandle->outDMAHandle.queueDriver                 = (uint8_t)(queueDriverIndex + 1U) % ASRC_XFER_OUT_QUEUE_SIZE;

    /* If all data finished, just stop the transfer */
    if (asrcHandle->outDMAHandle.asrcQueue[asrcHandle->outDMAHandle.queueDriver] == NULL)
    {
        if (asrcHandle->outDMAHandle.nonAlignSize != 0U)
        {
            /* please note that when read buffered samples, input sample will be ingored */
            ASRC_ReadFIFORemainedSampleSDMA(
                privHandle->base, asrcHandle->context, asrcHandle->outDMAHandle.nonAlignAddr,
                asrcHandle->outDMAHandle.bytesPerSample, asrcHandle->outDMAHandle.nonAlignSize);
            asrcHandle->outDMAHandle.nonAlignSize = 0U;
            asrcHandle->outDMAHandle.nonAlignAddr = NULL;
        }
        ASRC_TransferAbortOutSDMA(privHandle->base, asrcHandle);
        callbackStatus = kStatus_ASRCQueueIdle;
    }

    if (asrcHandle->outDMAHandle.callback != NULL)
    {
        (asrcHandle->outDMAHandle.callback)(privHandle->base, asrcHandle, callbackStatus,
                                            asrcHandle->outDMAHandle.userData);
    }
}

/*!
 * brief Initializes the ASRC input SDMA handle.
 *
 * This function initializes the ASRC input DMA handle, which can be used for other ASRC transactional APIs.
 * Usually, for a specified ASRC context, call this API once to get the initialized handle.
 *
 * param base ASRC base pointer.
 * param handle ASRC SDMA handle pointer.
 * param base ASRC peripheral base address.
 * param callback Pointer to user callback function.
 * param dmaHandle SDMA handle pointer, this handle shall be static allocated by users.
 * param eventSource ASRC input sdma event source.
 * param context ASRC context number.
 * param periphConfig peripheral configurations, used for peripheral to peripheral case.
 * param userData User parameter passed to the callback function.
 */
void ASRC_TransferInCreateHandleSDMA(ASRC_Type *base,
                                     asrc_sdma_handle_t *handle,
                                     asrc_sdma_callback_t callback,
                                     sdma_handle_t *dmaHandle,
                                     uint32_t eventSource,
                                     asrc_context_t context,
                                     const asrc_p2p_sdma_config_t *periphConfig,
                                     void *userData)
{
    assert((handle != NULL) && (dmaHandle != NULL));

    uint32_t instance = ASRC_GetInstance(base);

    /* Zero the handle */
    (void)memset(&handle->inDMAHandle, 0, sizeof(asrc_sdma_in_handle_t));

    /* Set asrc base to handle */
    handle->inDMAHandle.sdmaHandle  = dmaHandle;
    handle->inDMAHandle.callback    = callback;
    handle->inDMAHandle.userData    = userData;
    handle->inDMAHandle.eventSource = eventSource;

    /* Set ASRC state to idle */
    handle->inDMAHandle.state            = kStatus_ASRCIdle;
    handle->context                      = context;
    handle->inDMAHandle.peripheralConfig = periphConfig;

    s_sdmaPrivateHandle[instance][context].base   = base;
    s_sdmaPrivateHandle[instance][context].handle = handle;

    SDMA_InstallBDMemory(dmaHandle, handle->inDMAHandle.bdPool, ASRC_XFER_IN_QUEUE_SIZE);
    /* Install callback for in dma channel */
    SDMA_SetCallback(dmaHandle, ASRC_InSDMACallback, &s_sdmaPrivateHandle[instance][context]);
}

/*!
 * brief Initializes the ASRC output SDMA handle.
 *
 * This function initializes the ASRC out DMA handle, which can be used for other ASRC transactional APIs.
 * Usually, for a specified ASRC context, call this API once to get the initialized handle.
 *
 * param base ASRC base pointer.
 * param handle ASRC SDMA handle pointer.
 * param callback, ASRC outcallback.
 * param dmaHandle SDMA handle pointer, this handle shall be static allocated by users.
 * param eventSource ASRC output event source.
 * param context ASRC context number.
 * param periphConfig peripheral configurations, used for  case.
 * param userData User parameter passed to the callback function.
 */
void ASRC_TransferOutCreateHandleSDMA(ASRC_Type *base,
                                      asrc_sdma_handle_t *handle,
                                      asrc_sdma_callback_t callback,
                                      sdma_handle_t *dmaHandle,
                                      uint32_t eventSource,
                                      asrc_context_t context,
                                      const asrc_p2p_sdma_config_t *periphConfig,
                                      void *userData)
{
    assert((handle != NULL) && (dmaHandle != NULL));

    uint32_t instance = ASRC_GetInstance(base);

    /* Zero the handle */
    (void)memset(&handle->outDMAHandle, 0, sizeof(asrc_sdma_out_handle_t));

    /* Set asrc base to handle */
    handle->outDMAHandle.sdmaHandle       = dmaHandle;
    handle->outDMAHandle.callback         = callback;
    handle->outDMAHandle.userData         = userData;
    handle->outDMAHandle.eventSource      = eventSource;
    handle->outDMAHandle.peripheralConfig = periphConfig;

    /* Set ASRC state to idle */
    handle->outDMAHandle.state = kStatus_ASRCIdle;
    handle->context            = context;

    s_sdmaPrivateHandle[instance][context].base   = base;
    s_sdmaPrivateHandle[instance][context].handle = handle;

    /* Install callback for in dma channel */
    SDMA_SetCallback(dmaHandle, ASRC_OutSDMACallback, &s_sdmaPrivateHandle[instance][context]);
    SDMA_InstallBDMemory(dmaHandle, handle->outDMAHandle.bdPool, ASRC_XFER_OUT_QUEUE_SIZE);
}

/*!
 * brief Configures the ASRC context.
 *
 * param base ASRC base pointer.
 * param handle ASRC SDMA handle pointer.
 * param asrcConfig asrc context configurations.
 */
status_t ASRC_TransferSetContextConfigSDMA(ASRC_Type *base,
                                           asrc_sdma_handle_t *handle,
                                           asrc_context_config_t *asrcConfig)
{
    assert((handle != NULL) && (asrcConfig != NULL));

    /* Configure the audio format to ASRC registers */
    if (ASRC_SetContextConfig(base, handle->context, asrcConfig) != kStatus_Success)
    {
        return kStatus_ASRCConfigureFailed;
    }

    if (asrcConfig->contextInput.dataFormat.dataWidth == kASRC_DataWidth16Bit)
    {
        handle->inDMAHandle.bytesPerSample = 2U;
    }
    else
    {
        handle->inDMAHandle.bytesPerSample = 4U;
    }

    if (asrcConfig->contextOutput.dataFormat.dataWidth == kASRC_DataWidth16Bit)
    {
        handle->outDMAHandle.bytesPerSample = 2U;
    }
    else
    {
        handle->outDMAHandle.bytesPerSample = 4U;
    }

    handle->dataChannels                  = asrcConfig->contextChannelNums;
    handle->outDMAHandle.asrcOutWatermark = (asrcConfig->contextOutput.watermark + 1U) * asrcConfig->contextChannelNums;
    handle->inDMAHandle.asrcInWatermark   = (asrcConfig->contextInput.watermark + 1U) * asrcConfig->contextChannelNums;

    return kStatus_Success;
}

static status_t ASRC_TransferSubmitOutM2MSDMA(ASRC_Type *base,
                                              asrc_sdma_handle_t *handle,
                                              uint32_t *outDataAddr,
                                              uint32_t outDataSize)
{
    sdma_transfer_config_t outConfig = {0};
    uint32_t asrcOutAddr             = ASRC_GetReadContextFifoAddr(base, handle->context);
    sdma_handle_t *outDMAHandle      = handle->outDMAHandle.sdmaHandle;
    uint32_t nonAlignSize            = 0U;
    uint32_t *nonAlignAddr           = NULL;
    uint32_t outWaterMarkSize = (uint32_t)handle->outDMAHandle.asrcOutWatermark * handle->outDMAHandle.bytesPerSample;

    if (handle->outDMAHandle.asrcQueue[handle->outDMAHandle.queueUser] != NULL)
    {
        return kStatus_ASRCQueueFull;
    }

    if (outDataSize < outWaterMarkSize)
    {
        handle->outDMAHandle.nonAlignSize = outDataSize;
        handle->outDMAHandle.nonAlignAddr = outDataAddr;

        return kStatus_Success;
    }
    else
    {
        nonAlignSize = outDataSize % outWaterMarkSize;
        nonAlignAddr = (void *)(uint32_t *)((uint32_t)outDataAddr + outDataSize - nonAlignSize);
    }

    if (handle->outDMAHandle.peripheralConfig == NULL)
    {
        /* since the ASRC output fifo will generate SDMA request only when output fifo sample number > output fifo
         * watermark, so part of data may need to polling out.
         */
        if (handle->outDMAHandle.nonAlignSize != 0U)
        {
            SDMA_PrepareTransfer(&outConfig, (uint32_t)asrcOutAddr,
                                 (uint32_t)(uint32_t *)handle->outDMAHandle.nonAlignAddr,
                                 handle->outDMAHandle.bytesPerSample, handle->outDMAHandle.bytesPerSample,
                                 outWaterMarkSize, handle->outDMAHandle.nonAlignSize, handle->outDMAHandle.eventSource,
                                 kSDMA_PeripheralASRCP2M, kSDMA_PeripheralToMemory);

            if (handle->outDMAHandle.queueUser == ASRC_XFER_OUT_QUEUE_SIZE - 1U)
            {
                SDMA_ConfigBufferDescriptor(
                    &outDMAHandle->BDPool[handle->outDMAHandle.queueUser], (uint32_t)(asrcOutAddr),
                    (uint32_t)(uint32_t *)handle->outDMAHandle.nonAlignAddr, outConfig.destTransferSize,
                    handle->outDMAHandle.nonAlignSize, false, true, true, kSDMA_PeripheralToMemory);
            }
            else
            {
                SDMA_ConfigBufferDescriptor(
                    &outDMAHandle->BDPool[handle->outDMAHandle.queueUser], (uint32_t)(asrcOutAddr),
                    (uint32_t)(uint32_t *)handle->outDMAHandle.nonAlignAddr, outConfig.destTransferSize,
                    handle->outDMAHandle.nonAlignSize, false, true, false, kSDMA_PeripheralToMemory);
            }

            handle->outDMAHandle.sdmaTransferSize[handle->outDMAHandle.queueUser] = handle->outDMAHandle.nonAlignSize;
            handle->outDMAHandle.asrcQueue[handle->outDMAHandle.queueUser]        = handle->outDMAHandle.nonAlignAddr;
            handle->outDMAHandle.queueUser    = (handle->outDMAHandle.queueUser + 1U) % ASRC_XFER_OUT_QUEUE_SIZE;
            handle->outDMAHandle.nonAlignSize = 0U;
            handle->outDMAHandle.nonAlignAddr = NULL;

            if (handle->outDMAHandle.asrcQueue[handle->outDMAHandle.queueUser] != NULL)
            {
                return kStatus_ASRCQueueFull;
            }
        }
        else
        {
            SDMA_PrepareTransfer(&outConfig, (uint32_t)asrcOutAddr, (uint32_t)outDataAddr,
                                 handle->outDMAHandle.bytesPerSample, handle->outDMAHandle.bytesPerSample,
                                 outWaterMarkSize, outDataSize - nonAlignSize, handle->outDMAHandle.eventSource,
                                 kSDMA_PeripheralASRCP2M, kSDMA_PeripheralToMemory);
        }

        if (handle->outDMAHandle.queueUser == ASRC_XFER_OUT_QUEUE_SIZE - 1U)
        {
            SDMA_ConfigBufferDescriptor(&outDMAHandle->BDPool[handle->outDMAHandle.queueUser], (uint32_t)(asrcOutAddr),
                                        (uint32_t)outDataAddr, outConfig.destTransferSize, outDataSize - nonAlignSize,
                                        false, true, true, kSDMA_PeripheralToMemory);
        }
        else
        {
            SDMA_ConfigBufferDescriptor(&outDMAHandle->BDPool[handle->outDMAHandle.queueUser], (uint32_t)(asrcOutAddr),
                                        (uint32_t)outDataAddr, outConfig.destTransferSize, outDataSize - nonAlignSize,
                                        false, true, false, kSDMA_PeripheralToMemory);
        }

        handle->outDMAHandle.sdmaTransferSize[handle->outDMAHandle.queueUser] = outDataSize - nonAlignSize;
        handle->outDMAHandle.asrcQueue[handle->outDMAHandle.queueUser]        = outDataAddr;
        handle->outDMAHandle.nonAlignSize                                     = nonAlignSize;
        handle->outDMAHandle.nonAlignAddr                                     = nonAlignAddr;

        handle->outDMAHandle.queueUser = (handle->outDMAHandle.queueUser + 1U) % ASRC_XFER_OUT_QUEUE_SIZE;

        if (handle->outDMAHandle.state != (uint32_t)kStatus_ASRCBusy)
        {
            /* submit ASRC transfer firstly */
            SDMA_SubmitTransfer(outDMAHandle, &outConfig);
            /* Start DMA transfer */
            SDMA_StartTransfer(outDMAHandle);

            /* enable ASRC DMA request */
            ASRC_EnableContextOutDMA(base, handle->context, true);
            ASRC_ClearInterruptStatus(base, kASRC_ContextAllInterruptStatus);

            if ((handle->outDMAHandle.peripheralConfig != NULL) &&
                (handle->outDMAHandle.peripheralConfig->startPeripheral != NULL))
            {
                /* start peripheral */
                handle->outDMAHandle.peripheralConfig->startPeripheral(true);
            }

            handle->outDMAHandle.state = kStatus_ASRCBusy;
        }
    }

    return kStatus_Success;
}

static status_t ASRC_TransferOutSDMA(ASRC_Type *base,
                                     asrc_sdma_handle_t *handle,
                                     uint32_t *outDataAddr,
                                     uint32_t outDataSize)
{
    sdma_transfer_config_t outConfig = {0};
    uint32_t asrcOutAddr             = ASRC_GetReadContextFifoAddr(base, handle->context);
    sdma_handle_t *outDMAHandle      = handle->outDMAHandle.sdmaHandle;
    sdma_p2p_config_t p2pConfig      = {0U};

    if ((handle->outDMAHandle.peripheralConfig != NULL) && (handle->outDMAHandle.peripheralConfig->enableContinuous) &&
        (handle->outDMAHandle.state == (uint32_t)kStatus_ASRCBusy))
    {
        return kStatus_Success;
    }

    if (handle->outDMAHandle.asrcQueue[handle->outDMAHandle.queueUser] != NULL)
    {
        return kStatus_ASRCQueueFull;
    }

    if (handle->outDMAHandle.peripheralConfig != NULL)
    {
        p2pConfig.sourceWatermark    = handle->outDMAHandle.asrcOutWatermark;
        p2pConfig.destWatermark      = handle->outDMAHandle.peripheralConfig->watermark;
        p2pConfig.continuousTransfer = handle->outDMAHandle.peripheralConfig->enableContinuous;
        /* Prepare sdma configure */
        SDMA_PrepareP2PTransfer(&outConfig, (uint32_t)asrcOutAddr, (uint32_t)outDataAddr,
                                handle->outDMAHandle.bytesPerSample, handle->outDMAHandle.bytesPerSample,
                                (uint32_t)handle->outDMAHandle.asrcOutWatermark * handle->outDMAHandle.bytesPerSample,
                                outDataSize, handle->outDMAHandle.eventSource,
                                handle->outDMAHandle.peripheralConfig->eventSource, kSDMA_PeripheralASRCP2P,
                                &p2pConfig);

        handle->outDMAHandle.sdmaTransferSize[handle->outDMAHandle.queueUser] = outDataSize;
        handle->outDMAHandle.asrcQueue[handle->outDMAHandle.queueUser]        = outDataAddr;

        if (handle->outDMAHandle.queueUser == ASRC_XFER_OUT_QUEUE_SIZE - 1U)
        {
            SDMA_ConfigBufferDescriptor(&outDMAHandle->BDPool[handle->outDMAHandle.queueUser], (uint32_t)(asrcOutAddr),
                                        (uint32_t)outDataAddr, outConfig.destTransferSize, outDataSize, false, true,
                                        true, kSDMA_PeripheralToPeripheral);
        }
        else
        {
            SDMA_ConfigBufferDescriptor(&outDMAHandle->BDPool[handle->outDMAHandle.queueUser], (uint32_t)(asrcOutAddr),
                                        (uint32_t)outDataAddr, outConfig.destTransferSize, outDataSize, false, true,
                                        false, kSDMA_PeripheralToPeripheral);
        }

        handle->outDMAHandle.queueUser = (handle->outDMAHandle.queueUser + 1U) % ASRC_XFER_OUT_QUEUE_SIZE;

        if (handle->outDMAHandle.state != (uint32_t)kStatus_ASRCBusy)
        {
            /* submit ASRC transfer firstly */
            SDMA_SubmitTransfer(outDMAHandle, &outConfig);
            /* Start DMA transfer */
            SDMA_StartTransfer(outDMAHandle);

            /* enable ASRC DMA request */
            ASRC_EnableContextOutDMA(base, handle->context, true);
            ASRC_ClearInterruptStatus(base, kASRC_ContextAllInterruptStatus);

            if ((handle->outDMAHandle.peripheralConfig != NULL) &&
                (handle->outDMAHandle.peripheralConfig->startPeripheral != NULL))
            {
                /* start peripheral */
                handle->outDMAHandle.peripheralConfig->startPeripheral(true);
            }

            handle->outDMAHandle.state = kStatus_ASRCBusy;
        }
    }
    else
    {
        return ASRC_TransferSubmitOutM2MSDMA(base, handle, outDataAddr, outDataSize);
    }

    return kStatus_Success;
}

static status_t ASRC_TransferInSDMA(ASRC_Type *base,
                                    asrc_sdma_handle_t *handle,
                                    uint32_t *inDataAddr,
                                    uint32_t inDataSize)
{
    sdma_transfer_config_t inConfig = {0};
    uint32_t asrcInAddr             = ASRC_GetWriteContextFifoAddr(base, handle->context);
    sdma_handle_t *inDMAHandle      = handle->inDMAHandle.sdmaHandle;
    sdma_p2p_config_t p2pConfig     = {0U};

    if ((handle->inDMAHandle.peripheralConfig != NULL) && (handle->inDMAHandle.peripheralConfig->enableContinuous) &&
        (handle->inDMAHandle.state == (uint32_t)kStatus_ASRCBusy))
    {
        return kStatus_Success;
    }

    if (handle->inDMAHandle.asrcQueue[handle->inDMAHandle.queueUser] != NULL)
    {
        return kStatus_ASRCQueueFull;
    }

    if (handle->inDMAHandle.peripheralConfig != NULL)
    {
        p2pConfig.sourceWatermark    = handle->inDMAHandle.peripheralConfig->watermark;
        p2pConfig.destWatermark      = handle->inDMAHandle.asrcInWatermark;
        p2pConfig.continuousTransfer = handle->inDMAHandle.peripheralConfig->enableContinuous;

        /* Prepare sdma configure */
        SDMA_PrepareP2PTransfer(&inConfig, (uint32_t)inDataAddr, asrcInAddr,
                                handle->inDMAHandle.peripheralConfig->fifoWidth, handle->inDMAHandle.bytesPerSample,
                                (uint32_t)handle->inDMAHandle.asrcInWatermark * handle->inDMAHandle.bytesPerSample,
                                inDataSize, handle->inDMAHandle.peripheralConfig->eventSource,
                                handle->inDMAHandle.eventSource, kSDMA_PeripheralASRCP2P, &p2pConfig);
    }
    else
    {
        SDMA_PrepareTransfer(&inConfig, (uint32_t)inDataAddr, asrcInAddr, handle->inDMAHandle.bytesPerSample,
                             handle->inDMAHandle.bytesPerSample,
                             (uint32_t)handle->inDMAHandle.asrcInWatermark * handle->inDMAHandle.bytesPerSample,
                             inDataSize, handle->inDMAHandle.eventSource, kSDMA_PeripheralASRCM2P,
                             kSDMA_MemoryToPeripheral);
    }

    handle->inDMAHandle.sdmaTransferSize[handle->inDMAHandle.queueUser] = inDataSize;
    handle->inDMAHandle.asrcQueue[handle->inDMAHandle.queueUser]        = inDataAddr;

    if (handle->inDMAHandle.queueUser == ASRC_XFER_IN_QUEUE_SIZE - 1U)
    {
        SDMA_ConfigBufferDescriptor(&inDMAHandle->BDPool[handle->inDMAHandle.queueUser], (uint32_t)inDataAddr,
                                    asrcInAddr, inConfig.destTransferSize, inDataSize, true, true, true,
                                    kSDMA_MemoryToPeripheral);
    }
    else
    {
        SDMA_ConfigBufferDescriptor(&inDMAHandle->BDPool[handle->inDMAHandle.queueUser], (uint32_t)inDataAddr,
                                    asrcInAddr, inConfig.destTransferSize, inDataSize, true, true, false,
                                    kSDMA_MemoryToPeripheral);
    }

    handle->inDMAHandle.queueUser = (handle->inDMAHandle.queueUser + 1U) % ASRC_XFER_IN_QUEUE_SIZE;

    if (handle->inDMAHandle.state != (uint32_t)kStatus_ASRCBusy)
    {
        /* submit ASRC write transfer */
        SDMA_SubmitTransfer(inDMAHandle, &inConfig);
        /* Start DMA transfer */
        SDMA_StartTransfer(inDMAHandle);

        /* enable ASRC DMA request */
        ASRC_EnableContextInDMA(base, handle->context, true);
        ASRC_ClearInterruptStatus(base, kASRC_ContextAllInterruptStatus);
        /* enable context run */
        ASRC_EnableContextRun(base, handle->context, true);

        if ((handle->inDMAHandle.peripheralConfig != NULL) &&
            (handle->inDMAHandle.peripheralConfig->startPeripheral != NULL))
        {
            /* start peripheral */
            handle->inDMAHandle.peripheralConfig->startPeripheral(true);
        }

        handle->inDMAHandle.state = kStatus_ASRCBusy;
    }

    return kStatus_Success;
}

/*!
 * brief Performs a non-blocking ASRC transfer using DMA.
 *
 *
 * param base ASRC base pointer.
 * param handle ASRC SDMA handle pointer.
 * param xfer ASRC xfer configurations pointer.
 * retval kStatus_Success Start a ASRC SDMA send successfully.
 * retval kStatus_InvalidArgument The input argument is invalid.
 * retval kStatus_TxBusy ASRC is busy sending data.
 */
status_t ASRC_TransferSDMA(ASRC_Type *base, asrc_sdma_handle_t *handle, asrc_transfer_t *xfer)
{
    assert((handle != NULL) && (xfer != NULL));

    uint32_t *inPtr = xfer->inDataAddr, *outPtr = xfer->outDataAddr;
    uint32_t inSize = xfer->inDataSize, inOneTimeSize = 0U;
    uint32_t outSize = xfer->outDataSize, outOneTimeSize = 0U;
    uint32_t outWaterMarkSize = ((uint32_t)handle->outDMAHandle.asrcOutWatermark * handle->outDMAHandle.bytesPerSample);

    while ((inSize != 0U) || (outSize != 0U))
    {
        if (outSize != 0U)
        {
            outOneTimeSize = outSize > 64000U ? (64000U - 64000U % outWaterMarkSize) : outSize;
            if (ASRC_TransferOutSDMA(base, handle, outPtr, outOneTimeSize) == kStatus_Success)
            {
                outSize -= outOneTimeSize;
                outPtr = (uint32_t *)((uint32_t)outPtr + outOneTimeSize);
            }
        }

        if (inSize != 0U)
        {
            inOneTimeSize = inSize > 64000U ? 64000U : inSize;
            if (ASRC_TransferInSDMA(base, handle, inPtr, inOneTimeSize) == kStatus_Success)
            {
                inSize -= inOneTimeSize;
                inPtr = (uint32_t *)((uint32_t)inPtr + inOneTimeSize);
            }
        }
    }

    return kStatus_Success;
}

/*!
 * brief Aborts a ASRC in transfer using SDMA.
 *
 * param base ASRC base pointer.
 * param handle ASRC SDMA handle pointer.
 */
void ASRC_TransferAbortInSDMA(ASRC_Type *base, asrc_sdma_handle_t *handle)
{
    assert(handle != NULL);

    /* Disable dma */
    SDMA_AbortTransfer(handle->inDMAHandle.sdmaHandle);

    /* enable context run */
    ASRC_EnableContextRunStop(base, handle->context, true);
    /* stop peripheral */
    if ((handle->inDMAHandle.peripheralConfig != NULL) &&
        (handle->inDMAHandle.peripheralConfig->startPeripheral != NULL))
    {
        handle->inDMAHandle.peripheralConfig->startPeripheral(false);
    }
    /* Set the handle state */
    handle->inDMAHandle.state = kStatus_ASRCIdle;
}

/*!
 * brief Aborts a ASRC out transfer using SDMA.
 *
 * param base ASRC base pointer.
 * param handle ASRC SDMA handle pointer.
 */
void ASRC_TransferAbortOutSDMA(ASRC_Type *base, asrc_sdma_handle_t *handle)
{
    assert(handle != NULL);

    /* Disable dma */
    SDMA_AbortTransfer(handle->outDMAHandle.sdmaHandle);
    /* enable ASRC DMA request */
    ASRC_EnableContextOutDMA(base, handle->context, false);
    /* enable context run */
    ASRC_EnableContextRun(base, handle->context, false);
    ASRC_EnableContextRunStop(base, handle->context, false);
    /* stop peripheral */
    if ((handle->outDMAHandle.peripheralConfig != NULL) &&
        (handle->outDMAHandle.peripheralConfig->startPeripheral != NULL))
    {
        handle->outDMAHandle.peripheralConfig->startPeripheral(false);
    }
    /* Set the handle state */
    handle->outDMAHandle.state = kStatus_ASRCIdle;
}
