/*
 * Copyright (c) 2021-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_lcdic_dma.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lcdic_dma"
#endif

/* Max transfer byte count in each DMA transfer. */
#define LCDIC_MAX_DMA_XFER_COUNT (DMA_MAX_TRANSFER_COUNT * 4U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief LCDIC TX DMA callback.
 *
 * @param dmaHandle DMA handle.
 * @param param Callback parameter.
 * @param dmaXferDone DMA transfer done or not.
 * @param intmode Interrupt mode, kDMA_IntA, kDMA_IntB, or kDMA_IntError.
 */
static void LCDIC_TransferSendDMACallback(dma_handle_t *dmaHandle, void *param, bool dmaXferDone, uint32_t intmode);

/*!
 * @brief LCDIC RX DMA callback.
 *
 * @param dmaHandle DMA handle.
 * @param param Callback parameter.
 * @param dmaXferDone DMA transfer done or not.
 * @param intmode Interrupt mode, kDMA_IntA, kDMA_IntB, or kDMA_IntError.
 */
static void LCDIC_TransferReceiveDMACallback(dma_handle_t *dmaHandle, void *param, bool dmaXferDone, uint32_t intmode);

/*!
 * @brief Handle the LCDIC DMA transfer done.
 *
 * Disables the related interrupts, disable DMA, calling user callback.
 *
 * @param base LCDIC peripheral base address.
 * @param handle LCDIC DMA driver handle.
 * @param status The status passing to user callback.
 */
static void LCDIC_TransferDoneDMA(lcdic_dma_handle_t *handle, status_t status);

/*!
 * @brief Send data array using DMA way.
 *
 * @param base LCDIC peripheral base address.
 * @param handle LCDIC DMA driver handle.
 * @param xfer Pointer to the transfer structure.
 * @retval kStatus_Success Successfully start a transfer.
 * @retval kStatus_InvalidArgument Input argument is invalid.
 */
static status_t LCDIC_TransferSendDataArrayDMA(LCDIC_Type *base,
                                               lcdic_dma_handle_t *handle,
                                               const lcdic_tx_xfer_t *xfer);

/*!
 * @brief Read data array using DMA way.
 *
 * @param base LCDIC peripheral base address.
 * @param handle LCDIC DMA driver handle.
 * @param xfer Pointer to the transfer structure.
 * @retval kStatus_Success Successfully start a transfer.
 * @retval kStatus_InvalidArgument Input argument is invalid.
 */
static status_t LCDIC_TransferReceiveDataArrayDMA(LCDIC_Type *base,
                                                  lcdic_dma_handle_t *handle,
                                                  const lcdic_rx_xfer_t *xfer);

/*!
 * @brief Submit RX transfer request to DMA.
 *
 * Submit the data transfer request saved in LCDIC DMA driver handle to DMA.
 *
 * @param handle LCDIC DMA driver handle.
 */
static void LCDIC_TransferSubmitRxDataDMA(lcdic_dma_handle_t *handle);

/*!
 * @brief Submit TX transfer request to DMA.
 *
 * Submit the data transfer request saved in LCDIC DMA driver handle to DMA.
 *
 * @param handle LCDIC DMA driver handle.
 */
static void LCDIC_TransferSubmitTxDataDMA(lcdic_dma_handle_t *handle);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*
 * brief LCDIC TX DMA callback.
 *
 * param handle DMA handle.
 * param param Callback parameter.
 * param dmaXferDone DMA transfer done or not.
 * param intmode Interrupt mode, kDMA_IntA, kDMA_IntB, or kDMA_IntError.
 */
static void LCDIC_TransferSendDMACallback(dma_handle_t *dmaHandle, void *param, bool dmaXferDone, uint32_t intmode)
{
    assert(dmaHandle != NULL);
    assert(param != NULL);

    lcdic_dma_handle_t *lcdicDmaHandle = (lcdic_dma_handle_t *)param;

    if (dmaXferDone)
    {
        LCDIC_TransferSubmitTxDataDMA(lcdicDmaHandle);
    }
}

/*
 * brief LCDIC RX DMA callback.
 *
 * param handle DMA handle.
 * param param Callback parameter.
 * param dmaXferDone DMA transfer done or not.
 * param intmode Interrupt mode, kDMA_IntA, kDMA_IntB, or kDMA_IntError.
 */
static void LCDIC_TransferReceiveDMACallback(dma_handle_t *dmaHandle, void *param, bool dmaXferDone, uint32_t intmode)
{
    assert(dmaHandle != NULL);
    assert(param != NULL);

    lcdic_dma_handle_t *lcdicDmaHandle = (lcdic_dma_handle_t *)param;

    if (dmaXferDone)
    {
        LCDIC_TransferSubmitRxDataDMA(lcdicDmaHandle);
    }
}

/*
 * brief Submit RX transfer request to DMA.
 *
 * Submit the data transfer request saved in LCDIC DMA driver handle to DMA.
 *
 * param handle LCDIC DMA driver handle.
 */
static void LCDIC_TransferSubmitRxDataDMA(lcdic_dma_handle_t *handle)
{
    dma_handle_t *dmaHandle = handle->rxDmaHandle;
    dma_descriptor_t *dmaDesc, *nextDmaDesc;
    bool startDMA = true;
    bool reloadDmaXferCfg;
    uint8_t xferSizeWordUnaligned = handle->xferSizeWordUnaligned;
    uint32_t xferSizeWordAligned  = handle->xferSizeWordAligned;

    LCDIC_EnableDMA(handle->lcdic, false);
    /*
     * If left word-size aligned data is more than LCDIC_MAX_DMA_XFER_COUNT,
     * start DMA to handle the first LCDIC_MAX_DMA_XFER_COUNT part.
     */
    if (xferSizeWordAligned > LCDIC_MAX_DMA_XFER_COUNT)
    {
        dmaDesc = &handle->dmaDesc[0];

        dmaDesc->xfercfg    = DMA_SetChannelXferConfig(false,                                  /* Reload */
                                                    true,                                   /* Clear Trigger. */
                                                    true,                                   /* intA */
                                                    false,                                  /* intB */
                                                    4U,                                     /* Width */
                                                    (uint8_t)kDMA_AddressInterleave0xWidth, /* Source increase. */
                                                    (uint8_t)kDMA_AddressInterleave1xWidth, /* Destination increase. */
                                                    LCDIC_MAX_DMA_XFER_COUNT);
        dmaDesc->srcEndAddr = (uint32_t *)(uintptr_t) & (handle->lcdic->RFIFO_RDATA);
        dmaDesc->dstEndAddr = DMA_DESCRIPTOR_END_ADDRESS(handle->rxData, 1U, LCDIC_MAX_DMA_XFER_COUNT, 4U);

        dmaDesc->linkToNextDesc = NULL;

        handle->xferSizeWordAligned = xferSizeWordAligned - LCDIC_MAX_DMA_XFER_COUNT;
        handle->txData += LCDIC_MAX_DMA_XFER_COUNT;
    }
    /*
     * If left word-size aligned data is equal or less than LCDIC_MAX_DMA_XFER_COUNT,
     * besides the word-size aligned part, a descriptor is setup to handle the
     * word-size unaligned part.
     */
    else if (xferSizeWordAligned > 0U)
    {
        if (xferSizeWordUnaligned > 0U)
        {
            /* If there is unaligned part, using transfer link. */
            reloadDmaXferCfg = true;
            nextDmaDesc      = &handle->dmaDesc[1];
        }
        else
        {
            reloadDmaXferCfg = false;
            nextDmaDesc      = NULL;
        }

        dmaDesc = &handle->dmaDesc[0];

        dmaDesc->xfercfg = DMA_SetChannelXferConfig(reloadDmaXferCfg,                       /* Reload */
                                                    true,                                   /* Clear Trigger. */
                                                    true,                                   /* intA */
                                                    false,                                  /* intB */
                                                    4U,                                     /* Width */
                                                    (uint8_t)kDMA_AddressInterleave0xWidth, /* Source increase. */
                                                    (uint8_t)kDMA_AddressInterleave1xWidth, /* Destination increase. */
                                                    xferSizeWordAligned);

        dmaDesc->srcEndAddr = (uint32_t *)(uintptr_t) & (handle->lcdic->RFIFO_RDATA);
        dmaDesc->dstEndAddr = DMA_DESCRIPTOR_END_ADDRESS(handle->rxData, 1U, xferSizeWordAligned, 4U);

        dmaDesc->linkToNextDesc = nextDmaDesc;

        /* All data will be sent out after this DMA transfer. */
        handle->xferSizeWordAligned   = 0UL;
        handle->xferSizeWordUnaligned = 0U;
    }
    else
    {
        if (xferSizeWordUnaligned > 0U)
        {
            /* Handle the unaligned part. */
            dmaDesc = &handle->dmaDesc[1];

            /* All data will be sent out after this DMA transfer. */
            handle->xferSizeWordUnaligned = 0U;
        }
        else
        {
            /*
             * All data received, fill the unaligned part to user array if necessary,
             * then call the callback to notify user.
             */
            startDMA = false;

            if (handle->rxSizeWordUnaligned > 0U)
            {
                LCDIC_ExtractByteFromWord(handle->tmpData, handle->rxData, handle->rxSizeWordUnaligned);
                handle->rxSizeWordUnaligned = 0U;
            }

            LCDIC_TransferDoneDMA(handle, kStatus_Success);
        }
    }

    if (startDMA)
    {
        DMA_SubmitChannelDescriptor(dmaHandle, dmaDesc);
        LCDIC_EnableDMA(handle->lcdic, true);
        DMA_StartTransfer(dmaHandle);
    }
}

/*
 * brief Submit TX transfer request to DMA.
 *
 * Submit the data transfer request saved in LCDIC DMA driver handle to DMA.
 *
 * param handle LCDIC DMA driver handle.
 */
static void LCDIC_TransferSubmitTxDataDMA(lcdic_dma_handle_t *handle)
{
    dma_handle_t *dmaHandle = handle->txDmaHandle;
    dma_descriptor_t *dmaDesc, *nextDmaDesc;
    bool startDMA = true;
    bool reloadDmaXferCfg;
    uint8_t xferSizeWordUnaligned = handle->xferSizeWordUnaligned;
    uint32_t xferSizeWordAligned  = handle->xferSizeWordAligned;

    LCDIC_EnableDMA(handle->lcdic, false);
    /*
     * If left word-size aligned data is more than LCDIC_MAX_DMA_XFER_COUNT,
     * start DMA to send the first LCDIC_MAX_DMA_XFER_COUNT part.
     */
    if (xferSizeWordAligned > LCDIC_MAX_DMA_XFER_COUNT)
    {
        dmaDesc = &handle->dmaDesc[0];

        dmaDesc->xfercfg        = DMA_SetChannelXferConfig(false,                                  /* Reload */
                                                    true,                                   /* Clear Trigger. */
                                                    true,                                   /* intA */
                                                    false,                                  /* intB */
                                                    4U,                                     /* Width */
                                                    (uint8_t)kDMA_AddressInterleave1xWidth, /* Source increase. */
                                                    (uint8_t)kDMA_AddressInterleave0xWidth, /* Destination increase. */
                                                    LCDIC_MAX_DMA_XFER_COUNT);
        dmaDesc->srcEndAddr     = DMA_DESCRIPTOR_END_ADDRESS(handle->txData, 1U, LCDIC_MAX_DMA_XFER_COUNT, 4U);
        dmaDesc->dstEndAddr     = (uint32_t *)(uintptr_t) & (handle->lcdic->TFIFO_WDATA);
        dmaDesc->linkToNextDesc = NULL;

        handle->xferSizeWordAligned = xferSizeWordAligned - LCDIC_MAX_DMA_XFER_COUNT;
        handle->txData += LCDIC_MAX_DMA_XFER_COUNT;
    }
    /*
     * If left word-size aligned data is equal or less than LCDIC_MAX_DMA_XFER_COUNT,
     * besides the word-size aligned part, a descriptor is setup to send the
     * word-size unaligned part.
     */
    else if (xferSizeWordAligned > 0U)
    {
        /* If there is unaligned part, using transfer link. */
        if (xferSizeWordUnaligned > 0U)
        {
            reloadDmaXferCfg = true;
            nextDmaDesc      = &handle->dmaDesc[1];
        }
        else
        {
            reloadDmaXferCfg = false;
            nextDmaDesc      = NULL;
        }

        dmaDesc = &handle->dmaDesc[0];

        dmaDesc->xfercfg = DMA_SetChannelXferConfig(reloadDmaXferCfg,                       /* Reload */
                                                    true,                                   /* Clear Trigger. */
                                                    false,                                  /* intA */
                                                    false,                                  /* intB */
                                                    4U,                                     /* Width */
                                                    (uint8_t)kDMA_AddressInterleave1xWidth, /* Source increase. */
                                                    (uint8_t)kDMA_AddressInterleave0xWidth, /* Destination increase. */
                                                    xferSizeWordAligned);

        dmaDesc->srcEndAddr = DMA_DESCRIPTOR_END_ADDRESS(handle->txData, 1U, xferSizeWordAligned, 4U);
        dmaDesc->dstEndAddr = (uint32_t *)(uintptr_t) & (handle->lcdic->TFIFO_WDATA);

        dmaDesc->linkToNextDesc = nextDmaDesc;

        /* All data will be sent out after this DMA transfer. */
        handle->xferSizeWordAligned   = 0UL;
        handle->xferSizeWordUnaligned = 0U;
    }
    else
    {
        if (xferSizeWordUnaligned > 0U)
        {
            dmaDesc = &handle->dmaDesc[1];

            /* All data will be sent out after this DMA transfer. */
            handle->xferSizeWordUnaligned = 0U;
        }
        else
        {
            startDMA = false;
        }
    }

    if (startDMA)
    {
        DMA_SubmitChannelDescriptor(dmaHandle, dmaDesc);
        LCDIC_EnableDMA(handle->lcdic, true);
        DMA_StartTransfer(dmaHandle);
    }
}

/*
 * brief Send data array using DMA way.
 *
 * param base LCDIC peripheral base address.
 * param handle LCDIC DMA driver handle.
 * param xfer Pointer to the transfer structure.
 * retval kStatus_Success Successfully start a transfer.
 * retval kStatus_InvalidArgument Input argument is invalid.
 */
static status_t LCDIC_TransferSendDataArrayDMA(LCDIC_Type *base,
                                               lcdic_dma_handle_t *handle,
                                               const lcdic_tx_xfer_t *xfer)
{
    status_t status;
    uint32_t xferSizeWordAligned;
    uint8_t xferSizeWordUnaligned;
    uint32_t wordUnalignedData;
    dma_descriptor_t *dmaDesc;

    /* Data must be 4-byte aligned. */
    if (0U != (0x03U & (uint32_t)xfer->txData))
    {
        return kStatus_InvalidArgument;
    }

    status = LCDIC_PrepareSendDataArray(base, xfer, &xferSizeWordAligned, &xferSizeWordUnaligned, &wordUnalignedData);

    if (kStatus_Success == status)
    {
        handle->xferSizeWordUnaligned = xferSizeWordUnaligned;
        handle->xferSizeWordAligned   = xferSizeWordAligned;
        handle->tmpData               = wordUnalignedData;
        handle->txData                = xfer->txData;

        /*
         * There are two DMA descriptors in LCDIC DMA driver handle, the first is
         * used for 4-byte size aligned part, the second is for 4-byte size unaligned
         * part. For the second part, the descriptor is prepared during transfer started,
         * then used directly in DMA callback function.
         */
        /* If the data size is not word aligned, link descriptor is used. */
        if (xferSizeWordUnaligned > 0U)
        {
            dmaDesc = &handle->dmaDesc[1];

            dmaDesc->xfercfg =
                DMA_SetChannelXferConfig(false,                                  /* Reload */
                                         true,                                   /* Clear Trigger. */
                                         true,                                   /* intA */
                                         false,                                  /* intB */
                                         4U,                                     /* Width */
                                         (uint8_t)kDMA_AddressInterleave0xWidth, /* Source increase. */
                                         (uint8_t)kDMA_AddressInterleave0xWidth, /* Destination increase. */
                                         4U);
            dmaDesc->srcEndAddr     = &handle->tmpData;
            dmaDesc->dstEndAddr     = (uint32_t *)(uintptr_t) & (base->TFIFO_WDATA);
            dmaDesc->linkToNextDesc = NULL;
        }

        LCDIC_TransferSubmitTxDataDMA(handle);

        LCDIC_EnableInterrupts(base, (uint32_t)kLCDIC_CmdDoneInterrupt | (uint32_t)kLCDIC_TeTimeoutInterrupt |
                                         (uint32_t)kLCDIC_CmdTimeoutInterrupt);
    }

    return status;
}

/*
 * brief Read data array using DMA way.
 *
 * param base LCDIC peripheral base address.
 * param handle LCDIC DMA driver handle.
 * param xfer Pointer to the transfer structure.
 * retval kStatus_Success Successfully start a transfer.
 * retval kStatus_InvalidArgument Input argument is invalid.
 */
static status_t LCDIC_TransferReceiveDataArrayDMA(LCDIC_Type *base,
                                                  lcdic_dma_handle_t *handle,
                                                  const lcdic_rx_xfer_t *xfer)
{
    status_t status;
    uint32_t xferSizeWordAligned;
    uint8_t xferSizeWordUnaligned;
    dma_descriptor_t *dmaDesc;

    /* Data must be 4-byte aligned. */
    if (0U != (0x03U & (uint32_t)xfer->rxData))
    {
        return kStatus_InvalidArgument;
    }

    status = LCDIC_PrepareReadDataArray(base, xfer, &xferSizeWordAligned, &xferSizeWordUnaligned);

    if (kStatus_Success == status)
    {
        handle->xferSizeWordUnaligned = xferSizeWordUnaligned;
        handle->xferSizeWordAligned   = xferSizeWordAligned;
        handle->rxData                = xfer->rxData;

        /*
         * There are two DMA descriptors in LCDIC DMA driver handle, the first is
         * used for 4-byte size aligned part, the second is for 4-byte size unaligned
         * part. For the second part, the descriptor is prepared during transfer started,
         * then used directly in DMA callback function.
         */

        /* If the data size is not word aligned, link descriptor is used. */
        if (xferSizeWordUnaligned > 0U)
        {
            dmaDesc = &handle->dmaDesc[1];

            dmaDesc->xfercfg =
                DMA_SetChannelXferConfig(false,                                  /* Reload */
                                         true,                                   /* Clear Trigger. */
                                         true,                                   /* intA */
                                         false,                                  /* intB */
                                         4U,                                     /* Width */
                                         (uint8_t)kDMA_AddressInterleave0xWidth, /* Source increase. */
                                         (uint8_t)kDMA_AddressInterleave0xWidth, /* Destination increase. */
                                         4U);
            dmaDesc->srcEndAddr     = (uint32_t *)(uintptr_t) & (base->RFIFO_RDATA);
            dmaDesc->dstEndAddr     = &handle->tmpData;
            dmaDesc->linkToNextDesc = NULL;
        }

        LCDIC_TransferSubmitRxDataDMA(handle);

        LCDIC_EnableInterrupts(base, (uint32_t)kLCDIC_TeTimeoutInterrupt | (uint32_t)kLCDIC_CmdTimeoutInterrupt);
    }

    return status;
}

/*
 * brief Handle the LCDIC DMA transfer done.
 *
 * Disables the related interrupts, disable DMA, calling user callback.
 *
 * param base LCDIC peripheral base address.
 * param handle LCDIC DMA driver handle.
 * param status The status passing to user callback.
 */
static void LCDIC_TransferDoneDMA(lcdic_dma_handle_t *handle, status_t status)
{
    LCDIC_Type *lcdic = handle->lcdic;

    LCDIC_DisableInterrupts(lcdic, (uint32_t)kLCDIC_CmdDoneInterrupt | (uint32_t)kLCDIC_TeTimeoutInterrupt |
                                       (uint32_t)kLCDIC_CmdTimeoutInterrupt);

    LCDIC_EnableDMA(lcdic, false);

    handle->xferInProgress = false;

    if (NULL != handle->callback)
    {
        handle->callback(lcdic, handle, status, handle->userData);
    }
}

/*
 * brief Initialize the LCDIC DMA handle.
 *
 * This function initializes the LCDIC DMA handle which can be used for other LCDIC transactional APIs.
 * Usually, for a specified LCDIC instance, user need only call this API once to get the initialized handle.
 *
 * param base LCDIC peripheral base address.
 * param handle LCDIC handle pointer.
 * param callback User callback function called at the end of a transfer.
 * param userData User data for callback.
 * param txDmaHandle DMA handle pointer for LCDIC Tx, the handle shall be static allocated by users.
 * param rxDmaHandle DMA handle pointer for LCDIC Rx, the handle shall be static allocated by users.
 * param dmaDesc User allocated dma descriptor, it should be in non-cacheable region and 16-byte aligned.
 */
status_t LCDIC_TransferCreateHandleDMA(LCDIC_Type *base,
                                       lcdic_dma_handle_t *handle,
                                       lcdic_dma_callback_t callback,
                                       void *userData,
                                       dma_handle_t *txDmaHandle,
                                       dma_handle_t *rxDmaHandle,
                                       dma_descriptor_t dmaDesc[2])
{
    assert(NULL != handle);
    assert(!((NULL == txDmaHandle) && (NULL == rxDmaHandle)));

    uint32_t instance;

    dma_channel_trigger_t trigger = {
        .type = kDMA_RisingEdgeTrigger, .burst = kDMA_EdgeBurstTransfer1, .wrap = kDMA_NoWrap};

    if (((uint32_t)dmaDesc & ((uint32_t)FSL_FEATURE_DMA_LINK_DESCRIPTOR_ALIGN_SIZE - 1UL)) != 0UL)
    {
        return kStatus_InvalidArgument;
    }

    (void)memset(handle, 0, sizeof(lcdic_dma_handle_t));

    instance = LCDIC_GetInstance(base);

    handle->lcdic       = base;
    handle->txDmaHandle = txDmaHandle;
    handle->rxDmaHandle = rxDmaHandle;
    handle->callback    = callback;
    handle->userData    = userData;
    handle->dmaDesc     = dmaDesc;

    /* Configure RX callback. */
    if (rxDmaHandle != NULL)
    {
        DMA_SetChannelConfig(rxDmaHandle->base, rxDmaHandle->channel, &trigger, false);
        DMA_SetCallback(rxDmaHandle, LCDIC_TransferReceiveDMACallback, handle);

        LCDIC_SetRxThreshold(base, kLCDIC_RxThreshold0Word);
    }

    /* Configure TX callback. */
    if (txDmaHandle != NULL)
    {
        DMA_SetChannelConfig(txDmaHandle->base, txDmaHandle->channel, &trigger, false);
        DMA_SetCallback(txDmaHandle, LCDIC_TransferSendDMACallback, handle);

        LCDIC_SetTxThreshold(base, kLCDIC_TxThreshold0Word);
    }

    LCDIC_TransferInstallIRQHandler(instance, handle, LCDIC_TransferHandleIRQDMA);

    (void)EnableIRQ(LCDIC_GetIRQn(instance));

    return kStatus_Success;
}

/*
 * brief Perform a non-blocking LCDIC transfer using DMA.
 *
 * This function returned immediately after transfer initiates, monitor the transfer
 * done by callback.
 *
 * param base LCDIC peripheral base address.
 * param handle LCDIC DMA handle pointer.
 * param xfer Pointer to dma transfer structure.
 * retval kStatus_Success Successfully start a transfer.
 * retval kStatus_InvalidArgument Input argument is invalid.
 * retval kStatus_Busy LCDIC is not idle, is running another transfer.
 */
status_t LCDIC_TransferDMA(LCDIC_Type *base, lcdic_dma_handle_t *handle, const lcdic_xfer_t *xfer)
{
    status_t status = kStatus_InvalidArgument;

    if (((kLCDIC_XferSendDataArray == xfer->mode) &&
         (NULL == handle->txDmaHandle)) || /* send mode but no TX DMA handle. */
        ((kLCDIC_XferReceiveDataArray == xfer->mode) &&
         (NULL == handle->rxDmaHandle))) /* read mode but no RX DMA handle. */
    {
        return kStatus_InvalidArgument;
    }

    if (handle->xferInProgress)
    {
        return kStatus_Busy;
    }

    handle->xferInProgress = true;
    handle->xferMode       = xfer->mode;

    switch (xfer->mode)
    {
        case kLCDIC_XferCmdOnly:
            status = LCDIC_PrepareSendCommand(base, xfer->cmdToSendOnly);
            LCDIC_EnableInterrupts(base, (uint32_t)kLCDIC_CmdDoneInterrupt);
            break;

        case kLCDIC_XferSendRepeatData:
            status = LCDIC_PrepareSendRepeatData(base, &xfer->repeatTxXfer);
            LCDIC_EnableInterrupts(base, (uint32_t)kLCDIC_CmdDoneInterrupt | (uint32_t)kLCDIC_TeTimeoutInterrupt |
                                             (uint32_t)kLCDIC_CmdTimeoutInterrupt);
            break;

        case kLCDIC_XferSendDataArray:
            status = LCDIC_TransferSendDataArrayDMA(base, handle, &xfer->txXfer);
            break;

        case kLCDIC_XferReceiveDataArray:
            status = LCDIC_TransferReceiveDataArrayDMA(base, handle, &xfer->rxXfer);
            break;

        default:
            /* Should not reach here. */
            status = kStatus_InvalidArgument;
            break;
    }

    if (status != kStatus_Success)
    {
        handle->xferInProgress = false;
    }

    return status;
}

/*
 * brief LCDIC IRQ handler function work with DMA transactional APIs.
 *
 * IRQ handler to work with @ref LCDIC_TransferDMA.
 *
 * param base LCDIC peripheral base address.
 * param handle Pointer to the lcdic_dma_handle_t structure to store the transfer state.
 */
void LCDIC_TransferHandleIRQDMA(LCDIC_Type *base, void *handle)
{
    assert(NULL != handle);

    uint32_t intStat;
    status_t status;
    bool xferDone = false;

    lcdic_dma_handle_t *lcdicDmaHandle = (lcdic_dma_handle_t *)handle;

    if (lcdicDmaHandle->xferInProgress)
    {
        intStat = LCDIC_GetInterruptStatus(base);
        LCDIC_ClearInterruptStatus(base, intStat);

        /* Timeout. */
        if (0U != (intStat & ((uint32_t)kLCDIC_CmdTimeoutInterrupt | (uint32_t)kLCDIC_TeTimeoutInterrupt)))
        {
            if (kLCDIC_XferReceiveDataArray == lcdicDmaHandle->xferMode)
            {
                DMA_AbortTransfer(lcdicDmaHandle->rxDmaHandle);
            }
            else if (kLCDIC_XferSendDataArray == lcdicDmaHandle->xferMode)
            {
                DMA_AbortTransfer(lcdicDmaHandle->txDmaHandle);
            }
            else
            {
                /* Empty */
            }

            xferDone = true;
            status   = kStatus_Timeout;
        }
        else if (0U != (intStat & ((uint32_t)kLCDIC_CmdDoneInterrupt)))
        {
            if (lcdicDmaHandle->xferMode != kLCDIC_XferReceiveDataArray)
            {
                xferDone = true;
                status   = kStatus_Success;
            }
        }
        else
        {
            /* Empty. */
        }

        if (xferDone)
        {
            LCDIC_TransferDoneDMA(lcdicDmaHandle, status);
        }
    }
}
