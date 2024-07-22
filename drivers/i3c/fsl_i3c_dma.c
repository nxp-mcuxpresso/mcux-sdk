/*
 * Copyright 2022-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_i3c_dma.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.i3c_dma"
#endif

#define WIDTH_1_BYTE 1U
#define WIDTH_2_BYTE 2U
#define WIDTH_4_BYTE 4U

/*! @brief States for the state machine used by transactional APIs. */
enum _i3c_dma_transfer_states
{
    kIdleState = 0,
    kIBIWonState,
    kSlaveStartState,
    kWaitRepeatedStartCompleteState,
    kStopState,
    kWaitForCompletionState,
    kAddressMatchState,
};

/*! @brief Common sets of flags used by the driver. */
enum _i3c_dma_flag_constants
{
    /*! All flags which are cleared by the driver upon starting a transfer. */
    kMasterClearFlags = kI3C_MasterSlaveStartFlag | kI3C_MasterControlDoneFlag | kI3C_MasterCompleteFlag |
                        kI3C_MasterArbitrationWonFlag | kI3C_MasterSlave2MasterFlag | kI3C_MasterErrorFlag,

    /*! IRQ sources enabled by the non-blocking transactional API. */
    kMasterDMAIrqFlags = kI3C_MasterSlaveStartFlag | kI3C_MasterControlDoneFlag | kI3C_MasterCompleteFlag |
                         kI3C_MasterArbitrationWonFlag | kI3C_MasterErrorFlag | kI3C_MasterSlave2MasterFlag,

    /*! Errors to check for. */
    kMasterErrorFlags = kI3C_MasterErrorNackFlag | kI3C_MasterErrorWriteAbortFlag |
#if !defined(FSL_FEATURE_I3C_HAS_NO_MERRWARN_TERM) || (!FSL_FEATURE_I3C_HAS_NO_MERRWARN_TERM)
                        kI3C_MasterErrorTermFlag |
#endif
                        kI3C_MasterErrorParityFlag | kI3C_MasterErrorCrcFlag | kI3C_MasterErrorReadFlag |
                        kI3C_MasterErrorWriteFlag | kI3C_MasterErrorMsgFlag | kI3C_MasterErrorInvalidReqFlag |
                        kI3C_MasterErrorTimeoutFlag,
    /*! All flags which are cleared by the driver upon starting a transfer. */
    kSlaveClearFlags = kI3C_SlaveBusStartFlag | kI3C_SlaveMatchedFlag | kI3C_SlaveBusStopFlag,

    /*! IRQ sources enabled by the non-blocking transactional API. */
    kSlaveDMAIrqFlags = kI3C_SlaveBusStartFlag | kI3C_SlaveMatchedFlag |
                        kI3C_SlaveBusStopFlag | /*kI3C_SlaveRxReadyFlag |*/
                        kI3C_SlaveDynamicAddrChangedFlag | kI3C_SlaveReceivedCCCFlag | kI3C_SlaveErrorFlag |
                        kI3C_SlaveHDRCommandMatchFlag | kI3C_SlaveCCCHandledFlag | kI3C_SlaveEventSentFlag,

    /*! Errors to check for. */
    kSlaveErrorFlags = kI3C_SlaveErrorOverrunFlag | kI3C_SlaveErrorUnderrunFlag | kI3C_SlaveErrorUnderrunNakFlag |
                       kI3C_SlaveErrorTermFlag | kI3C_SlaveErrorInvalidStartFlag | kI3C_SlaveErrorSdrParityFlag |
                       kI3C_SlaveErrorHdrParityFlag | kI3C_SlaveErrorHdrCRCFlag | kI3C_SlaveErrorS0S1Flag |
                       kI3C_SlaveErrorOverreadFlag | kI3C_SlaveErrorOverwriteFlag,
};

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Array to map I3C instance number to base pointer. */
static I3C_Type *const kI3cBases[] = I3C_BASE_PTRS;

/*! @brief DMA linked transfer descriptor. */
SDK_ALIGN(dma_descriptor_t static s_dma_table[ARRAY_SIZE(kI3cBases)][2], FSL_FEATURE_DMA_LINK_DESCRIPTOR_ALIGN_SIZE);

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
static void I3C_MasterTransferDMACallbackRx(dma_handle_t *dmaHandle, void *param, bool transferDone, uint32_t tcds)
{
    i3c_master_dma_handle_t *i3cHandle = (i3c_master_dma_handle_t *)param;
#if defined(FSL_FEATURE_I3C_HAS_ERRATA_052123) && (FSL_FEATURE_I3C_HAS_ERRATA_052123)
    uint32_t leftDataSize = i3cHandle->transfer.dataSize - i3cHandle->transDataSize;
    uint32_t instance     = I3C_GetInstance(i3cHandle->base);
    uint32_t unitDataLen;
#endif

    if (transferDone)
    {
#if defined(FSL_FEATURE_I3C_HAS_ERRATA_052123) && (FSL_FEATURE_I3C_HAS_ERRATA_052123)
        if (leftDataSize > 0U)
        {
            if (leftDataSize >= 6U)
            {
                unitDataLen = 6;
            }
            else if (leftDataSize >= 4U)
            {
                I3C_MasterSetWatermarks(i3cHandle->base, kI3C_TxTriggerOnEmpty, kI3C_RxTriggerUntilOneHalfOrMore, false,
                                        false);
                unitDataLen = 4;
            }
            else if (leftDataSize >= 2U)
            {
                I3C_MasterSetWatermarks(i3cHandle->base, kI3C_TxTriggerOnEmpty, kI3C_RxTriggerUntilOneQuarterOrMore,
                                        false, false);
                unitDataLen = 2;
            }
            else
            {
                I3C_MasterSetWatermarks(i3cHandle->base, kI3C_TxTriggerOnEmpty, kI3C_RxTriggerOnNotEmpty, false, false);
                unitDataLen = 1;
            }

            DMA_SetupDescriptor(
                &s_dma_table[instance][0],
                DMA_CHANNEL_XFER(true, false, true, false, sizeof(uint8_t), kDMA_AddressInterleave0xWidth,
                                 kDMA_AddressInterleave1xWidth, unitDataLen),
                (void *)(uint32_t *)(uint32_t)&i3cHandle->base->MRDATAB,
                (uint8_t *)i3cHandle->transfer.data + i3cHandle->transDataSize, NULL);
            DMA_SetChannelConfig(i3cHandle->rxDmaHandle->base, i3cHandle->rxDmaHandle->channel, NULL, true);
            DMA_SubmitChannelDescriptor(i3cHandle->rxDmaHandle, &s_dma_table[instance][0]);
            DMA_StartTransfer(i3cHandle->rxDmaHandle);
            i3cHandle->transDataSize += unitDataLen;
        }
        else
        {
#endif
            /* Read last data byte */
            i3cHandle->base->MCTRL |= I3C_MCTRL_RDTERM(1U);

            i3cHandle->state = (uint8_t)kStopState;
            I3C_MasterTransferDMAHandleIRQ(i3cHandle->base, i3cHandle);
#if defined(FSL_FEATURE_I3C_HAS_ERRATA_052123) && (FSL_FEATURE_I3C_HAS_ERRATA_052123)
        }
#endif
    }
}

#if defined(FSL_FEATURE_I3C_HAS_ERRATA_052123) && (FSL_FEATURE_I3C_HAS_ERRATA_052123)
static void I3C_MasterSetDMATxLoop(I3C_Type *base, i3c_master_dma_handle_t *handle, void *data, size_t dataSize)
{
    uint32_t address  = (uint32_t)&base->MWDATAH;
    uint32_t instance = I3C_GetInstance(base);

    if (dataSize == 1U)
    {
        DMA_SetupDescriptor(&s_dma_table[instance][0],
                            DMA_CHANNEL_XFER(false, false, true, false, WIDTH_1_BYTE, kDMA_AddressInterleave1xWidth,
                                             kDMA_AddressInterleave0xWidth, 1U),
                            (uint8_t *)data + handle->transDataSize, (void *)(uint32_t *)(uint32_t)&base->MWDATABE,
                            NULL);
    }
    else if (dataSize == 2U)
    {
        DMA_SetupDescriptor(&s_dma_table[instance][0],
                            DMA_CHANNEL_XFER(false, false, true, false, WIDTH_2_BYTE, kDMA_AddressInterleave1xWidth,
                                             kDMA_AddressInterleave0xWidth, 2U),
                            (uint8_t *)data + handle->transDataSize, (void *)(uint32_t *)(uint32_t)&base->MWDATAHE,
                            NULL);
    }
    else if (dataSize <= 8U)
    {
        (void)memset(&handle->workaroundBuff[0], 0, sizeof(handle->workaroundBuff));
        for (uint32_t i = 0; i < dataSize - 1U; i += 2U)
        {
            (void)memcpy((void *)&handle->workaroundBuff[i * 2U], (void *)((uint8_t *)data + handle->transDataSize + i),
                         2);
        }

        DMA_SetupDescriptor(&s_dma_table[instance][0],
                            DMA_CHANNEL_XFER(true, false, false, false, WIDTH_4_BYTE, kDMA_AddressInterleave1xWidth,
                                             kDMA_AddressInterleave0xWidth, ((dataSize - 1U) / 2U) * 4U),
                            &handle->workaroundBuff[0], (void *)(uint8_t *)address, &s_dma_table[instance][1]);

        if ((dataSize % 2U) != 0U)
        {
            (void)memcpy((void *)&handle->workaroundBuff[((dataSize - 1U) / 2U) * 4U],
                         (void *)((uint8_t *)data + handle->transDataSize + dataSize - 1U), 1);
            DMA_SetupDescriptor(&s_dma_table[instance][1],
                                DMA_CHANNEL_XFER(false, false, true, false, WIDTH_1_BYTE, kDMA_AddressInterleave1xWidth,
                                                 kDMA_AddressInterleave0xWidth, 1U),
                                &handle->workaroundBuff[((dataSize - 1U) / 2U) * 4U],
                                (void *)(uint32_t *)(uint32_t)&base->MWDATABE, NULL);
        }
        else
        {
            DMA_SetupDescriptor(&s_dma_table[instance][1],
                                DMA_CHANNEL_XFER(false, false, true, false, WIDTH_2_BYTE, kDMA_AddressInterleave1xWidth,
                                                 kDMA_AddressInterleave0xWidth, 2U),
                                &handle->workaroundBuff[((dataSize - 1U) / 2U) * 4U],
                                (void *)(uint32_t *)(uint32_t)&base->MWDATAHE, NULL);
        }
    }
    else
    {
        (void)memset(&handle->workaroundBuff[0], 0, sizeof(handle->workaroundBuff));
        for (uint32_t i = 0; i <= 6U; i += 2U)
        {
            (void)memcpy((void *)&handle->workaroundBuff[i * 2U], (void *)((uint8_t *)data + handle->transDataSize + i),
                         2);
        }
        DMA_SetupDescriptor(&s_dma_table[instance][0],
                            DMA_CHANNEL_XFER(true, false, true, false, WIDTH_4_BYTE, kDMA_AddressInterleave1xWidth,
                                             kDMA_AddressInterleave0xWidth, 16U),
                            (void *)&handle->workaroundBuff[0], (void *)(uint32_t *)address, NULL);
    }
    handle->transDataSize += ((dataSize <= 8U) ? dataSize : 8U);
    DMA_SetChannelConfig(handle->txDmaHandle->base, handle->txDmaHandle->channel, NULL, true);
    DMA_SubmitChannelDescriptor(handle->txDmaHandle, &s_dma_table[instance][0]);
    DMA_StartTransfer(handle->txDmaHandle);
}
#endif

static void I3C_MasterTransferDMACallbackTx(dma_handle_t *dmaHandle, void *param, bool transferDone, uint32_t tcds)
{
    i3c_master_dma_handle_t *i3cHandle = (i3c_master_dma_handle_t *)param;
#if defined(FSL_FEATURE_I3C_HAS_ERRATA_052123) && (FSL_FEATURE_I3C_HAS_ERRATA_052123)
    uint32_t leftBytes = i3cHandle->transferCount - i3cHandle->transDataSize;
#endif

    if (transferDone)
    {
#if defined(FSL_FEATURE_I3C_HAS_ERRATA_052123) && (FSL_FEATURE_I3C_HAS_ERRATA_052123)
        if (leftBytes > 0U)
        {
            I3C_MasterSetDMATxLoop(i3cHandle->base, i3cHandle, i3cHandle->transfer.data, leftBytes);
        }
        else
        {
#endif
            i3cHandle->base->MDATACTRL &= ~I3C_MDMACTRL_DMATB_MASK;
#if defined(FSL_FEATURE_I3C_HAS_ERRATA_052123) && (FSL_FEATURE_I3C_HAS_ERRATA_052123)
        }
#endif
    }
}

static void I3C_MasterSetTxDMA(
    I3C_Type *base, i3c_master_dma_handle_t *handle, dma_channel_config_t *txChannelConfig, void *data, size_t dataSize)
{
    uint32_t instance;
    uint32_t address;

    if (handle->transfer.busType == kI3C_TypeI3CDdr)
    {
        instance = I3C_GetInstance(base);

#if defined(FSL_FEATURE_I3C_HAS_NO_MASTER_DMA_WDATA_REG) && (FSL_FEATURE_I3C_HAS_NO_MASTER_DMA_WDATA_REG)
        address = (uint32_t)&base->MWDATAB;
#else
        address = (uint32_t)&base->MWDATAB1;
#endif
        DMA_PrepareChannelTransfer(txChannelConfig, data, (void *)(uint32_t *)address,
                                   DMA_CHANNEL_XFER(false, false, false, false, 1U, kDMA_AddressInterleave1xWidth,
                                                    kDMA_AddressInterleave0xWidth, dataSize),
                                   kDMA_MemoryToPeripheral, NULL, NULL);
    }
    else
    {
        if (dataSize == 1U)
        {
            address = (uint32_t)&base->MWDATABE;
            DMA_PrepareChannelTransfer(txChannelConfig, data, (void *)(uint32_t *)address,
                                       DMA_CHANNEL_XFER(false, false, true, false, 1U, kDMA_AddressInterleave1xWidth,
                                                        kDMA_AddressInterleave0xWidth, dataSize),
                                       kDMA_MemoryToPeripheral, NULL, NULL);
        }
        else
        {
            instance = I3C_GetInstance(base);

#if defined(FSL_FEATURE_I3C_HAS_NO_MASTER_DMA_WDATA_REG) && (FSL_FEATURE_I3C_HAS_NO_MASTER_DMA_WDATA_REG)
            address = (uint32_t)&base->MWDATAB;
#else
            address = (uint32_t)&base->MWDATAB1;
#endif
            DMA_PrepareChannelTransfer(txChannelConfig, data, (void *)(uint32_t *)address,
                                       DMA_CHANNEL_XFER(true, false, false, false, 1U, kDMA_AddressInterleave1xWidth,
                                                        kDMA_AddressInterleave0xWidth, dataSize - 1U),
                                       kDMA_MemoryToPeripheral, NULL, &(s_dma_table[instance][0]));

            address = (uint32_t)&base->MWDATABE;
            DMA_SetupDescriptor(&(s_dma_table[instance][0]),
                                DMA_CHANNEL_XFER(false, false, true, false, 1u, kDMA_AddressInterleave1xWidth,
                                                 kDMA_AddressInterleave0xWidth, 1U),
                                (uint8_t *)data + dataSize - 1U, (void *)(uint32_t *)address, NULL);
        }
    }
}

static void I3C_MasterRunDMATransfer(I3C_Type *base, i3c_master_dma_handle_t *handle, i3c_direction_t direction)
{
    void *data         = handle->transfer.data;
    size_t dataSize    = handle->transfer.dataSize;
    bool isEnableTxDMA = false;
    bool isEnableRxDMA = false;
    uint32_t instance  = I3C_GetInstance(base);
    dma_channel_config_t txChannelConfig;
    uint32_t address;
    uint32_t width;

    handle->transferCount = dataSize;

#if defined(FSL_FEATURE_I3C_HAS_ERRATA_052123) && (FSL_FEATURE_I3C_HAS_ERRATA_052123)
    I3C_MasterSetWatermarks(base, kI3C_TxTriggerOnEmpty, kI3C_RxTriggerUntilThreeQuarterOrMore, false, false);
#endif

    if (direction == kI3C_Write)
    {
#if defined(FSL_FEATURE_I3C_HAS_ERRATA_052123) && (FSL_FEATURE_I3C_HAS_ERRATA_052123)
        if (handle->subaddressCount != 0U)
        {
            data     = &handle->subaddressBuffer[0];
            dataSize = handle->subaddressCount;

            handle->transferCount += dataSize;
            handle->transDataSize = 0;
            I3C_MasterSetDMATxLoop(base, handle, data, dataSize);
        }
        else
        {
            handle->transDataSize = 0;
            I3C_MasterSetDMATxLoop(base, handle, data, dataSize);
        }
#else
        if ((handle->subaddressCount != 0U) && (handle->transfer.dataSize != 0U))
        {
            instance = I3C_GetInstance(base);
#if defined(FSL_FEATURE_I3C_HAS_NO_MASTER_DMA_WDATA_REG) && (FSL_FEATURE_I3C_HAS_NO_MASTER_DMA_WDATA_REG)
            address = (uint32_t)&base->MWDATAB;
#else
            address = (uint32_t)&base->MWDATAB1;
#endif
            DMA_PrepareChannelTransfer(&txChannelConfig, &handle->subaddressBuffer[0], (void *)(uint32_t *)address,
                                       DMA_CHANNEL_XFER(true, false, false, false, 1U, kDMA_AddressInterleave1xWidth,
                                                        kDMA_AddressInterleave0xWidth, handle->subaddressCount),
                                       kDMA_MemoryToPeripheral, NULL, &(s_dma_table[instance][0]));

            if (handle->transfer.dataSize == 1U)
            {
                address = (uint32_t)&base->MWDATABE;
                DMA_SetupDescriptor(&(s_dma_table[instance][0]),
                                    DMA_CHANNEL_XFER(false, false, true, false, 1U, kDMA_AddressInterleave1xWidth,
                                                     kDMA_AddressInterleave0xWidth, 1U),
                                    (uint8_t *)handle->transfer.data + handle->transfer.dataSize - 1U,
                                    (void *)(uint32_t *)address, NULL);
            }
            else
            {
                DMA_SetupDescriptor(&(s_dma_table[instance][0]),
                                    DMA_CHANNEL_XFER(true, false, false, false, 1U, kDMA_AddressInterleave1xWidth,
                                                     kDMA_AddressInterleave0xWidth, handle->transfer.dataSize - 1U),
                                    (uint8_t *)handle->transfer.data, (void *)(uint32_t *)address,
                                    &(s_dma_table[instance][1]));

                address = (uint32_t)&base->MWDATABE;
                DMA_SetupDescriptor(&(s_dma_table[instance][1]),
                                    DMA_CHANNEL_XFER(false, false, true, false, 1U, kDMA_AddressInterleave1xWidth,
                                                     kDMA_AddressInterleave0xWidth, 1U),
                                    (uint8_t *)handle->transfer.data + handle->transfer.dataSize - 1U,
                                    (void *)(uint32_t *)address, NULL);
            }
        }
        else
        {
            data     = (handle->subaddressCount != 0U) ? (&handle->subaddressBuffer[0]) : handle->transfer.data;
            dataSize = (handle->subaddressCount != 0U) ? handle->subaddressCount : handle->transfer.dataSize;

            I3C_MasterSetTxDMA(base, handle, &txChannelConfig, data, dataSize);
        }

        (void)DMA_SubmitChannelTransfer(handle->txDmaHandle, &txChannelConfig);
        DMA_StartTransfer(handle->txDmaHandle);
#endif
        isEnableTxDMA = true;
        width         = 2U;
    }
    else
    {
        if (handle->subaddressCount != 0U)
        {
            I3C_MasterSetTxDMA(base, handle, &txChannelConfig, &handle->subaddressBuffer[0], handle->subaddressCount);
            (void)DMA_SubmitChannelTransfer(handle->txDmaHandle, &txChannelConfig);
            DMA_StartTransfer(handle->txDmaHandle);
            isEnableTxDMA = true;
            /* I3C-DMA issue occurs for Tx bytes > 7, here can use width = 1. */
            /* width = 2U; */
        }

        address = (uint32_t)&base->MRDATAB;
#if defined(FSL_FEATURE_I3C_HAS_ERRATA_052123) && (FSL_FEATURE_I3C_HAS_ERRATA_052123)
        DMA_SetupDescriptor(&s_dma_table[instance][0],
                            DMA_CHANNEL_XFER(true, false, true, false, sizeof(uint8_t), kDMA_AddressInterleave0xWidth,
                                             kDMA_AddressInterleave1xWidth, (dataSize < 6U) ? dataSize : 6U),
                            (uint32_t *)address, (uint32_t *)data, NULL);
        handle->transDataSize = (dataSize < 6U) ? dataSize : 6U;

        DMA_SetChannelConfig(handle->rxDmaHandle->base, handle->rxDmaHandle->channel, NULL, true);
        DMA_SubmitChannelDescriptor(handle->rxDmaHandle, &(s_dma_table[instance][0]));
#else
        dma_transfer_config_t xferConfig;
        DMA_PrepareTransfer(&xferConfig, (uint32_t *)address, data, sizeof(uint8_t), dataSize, kDMA_PeripheralToMemory,
                            NULL);
        (void)DMA_SubmitTransfer(handle->rxDmaHandle, &xferConfig);
#endif
        DMA_StartTransfer(handle->rxDmaHandle);
        isEnableRxDMA = true;
        width         = 1U;
    }

    I3C_MasterEnableDMA(base, isEnableTxDMA, isEnableRxDMA, width);
}

static status_t I3C_MasterInitTransferStateMachineDMA(I3C_Type *base, i3c_master_dma_handle_t *handle)
{
    i3c_master_transfer_t *xfer = &handle->transfer;
    status_t result             = kStatus_Success;
    i3c_direction_t direction   = xfer->direction;

    /* Calculate command count and put into command buffer. */
    handle->subaddressCount = 0U;
    if (xfer->subaddressSize != 0U)
    {
        for (uint32_t i = xfer->subaddressSize; i > 0U; i--)
        {
            handle->subaddressBuffer[handle->subaddressCount++] = (uint8_t)((xfer->subaddress) >> (8U * (i - 1U)));
        }
    }

    if (xfer->busType != kI3C_TypeI3CDdr)
    {
        direction = (0UL != xfer->subaddressSize) ? kI3C_Write : xfer->direction;
    }

    /* For combination of write address and read data, need to do ReSTART after write. */
    if ((xfer->subaddressSize != 0U) && (direction == kI3C_Read))
    {
        if ((handle->transfer.busType != kI3C_TypeI3CDdr) && (0UL != xfer->dataSize))
        {
            handle->state = (uint8_t)kWaitRepeatedStartCompleteState;
        }
    }
    else
    {
        handle->state = (uint8_t)kWaitForCompletionState;
    }

    /* Handle no start option. */
    if (0U != (xfer->flags & (uint32_t)kI3C_TransferNoStartFlag))
    {
        /* No need to send start flag, directly go to send command or data. */
        if (direction == kI3C_Write)
        {
            /* Prepare the DMA Tx/Rx in advance. */
            I3C_MasterRunDMATransfer(base, handle, direction);
        }
        else
        {
            /* Only support write with no START signal. */
            return kStatus_InvalidArgument;
        }
    }
    else
    {
        /* Prepare the DMA Tx/Rx in advance. */
        I3C_MasterRunDMATransfer(base, handle, direction);

        if (0U != (xfer->flags & (uint32_t)kI3C_TransferRepeatedStartFlag))
        {
            result = I3C_MasterRepeatedStart(base, xfer->busType, xfer->slaveAddress, direction);
        }
        else
        {
            result = I3C_MasterStart(base, xfer->busType, xfer->slaveAddress, direction);
        }
    }

    return result;
}

static status_t I3C_MasterRunTransferStateMachineDMA(I3C_Type *base, i3c_master_dma_handle_t *handle, bool *isDone)
{
    status_t result     = kStatus_Success;
    bool state_complete = false;
    size_t rxCount      = 0;
    i3c_master_transfer_t *xfer;
    uint32_t status;
    uint32_t errStatus;

    /* Set default isDone return value. */
    *isDone = false;

    /* Check for errors. */
    status = (uint32_t)I3C_MasterGetPendingInterrupts(base);
    I3C_MasterClearStatusFlags(base, status);

    i3c_master_state_t masterState = I3C_MasterGetState(base);
    errStatus                      = I3C_MasterGetErrorStatusFlags(base);
    result                         = I3C_MasterCheckAndClearError(base, errStatus);
    if (kStatus_Success != result)
    {
        return result;
    }

    if (0UL != (status & (uint32_t)kI3C_MasterSlave2MasterFlag))
    {
        if (handle->callback.slave2Master != NULL)
        {
            handle->callback.slave2Master(base, handle->userData);
        }
    }

    if ((0UL != (status & (uint32_t)kI3C_MasterSlaveStartFlag)) && (handle->transfer.busType != kI3C_TypeI2C))
    {
        handle->state = (uint8_t)kSlaveStartState;
    }

    if ((masterState == kI3C_MasterStateIbiRcv) || (masterState == kI3C_MasterStateIbiAck))
    {
        handle->state = (uint8_t)kIBIWonState;
    }

    if (handle->state == (uint8_t)kIdleState)
    {
        return result;
    }

    if (handle->state == (uint8_t)kIBIWonState)
    {
        /* Get Rx fifo counts. */
        rxCount = (base->MDATACTRL & I3C_MDATACTRL_RXCOUNT_MASK) >> I3C_MDATACTRL_RXCOUNT_SHIFT;
    }

    /* Get pointer to private data. */
    xfer = &handle->transfer;

    while (!state_complete)
    {
        /* Execute the state. */
        switch (handle->state)
        {
            case (uint8_t)kSlaveStartState:
                /* Emit start + 0x7E */
                I3C_MasterEmitRequest(base, kI3C_RequestAutoIbi);
                handle->state  = (uint8_t)kIBIWonState;
                state_complete = true;
                break;

            case (uint8_t)kIBIWonState:
                if (masterState == kI3C_MasterStateIbiAck)
                {
                    handle->ibiType = I3C_GetIBIType(base);
                    if (handle->callback.ibiCallback != NULL)
                    {
                        handle->callback.ibiCallback(base, handle, handle->ibiType, kI3C_IbiAckNackPending);
                    }
                    else
                    {
                        I3C_MasterEmitIBIResponse(base, kI3C_IbiRespNack);
                    }
                }

                /* Make sure there is data in the rx fifo. */
                if (0UL != rxCount)
                {
                    if ((handle->ibiBuff == NULL) && (handle->callback.ibiCallback != NULL))
                    {
                        handle->callback.ibiCallback(base, handle, kI3C_IbiNormal, kI3C_IbiDataBuffNeed);
                    }
                    uint8_t tempData = (uint8_t)base->MRDATAB;
                    if (handle->ibiBuff != NULL)
                    {
                        handle->ibiBuff[handle->ibiPayloadSize++] = tempData;
                    }
                    rxCount--;
                    break;
                }
                else if (0UL != (status & (uint32_t)kI3C_MasterCompleteFlag))
                {
                    handle->ibiType    = I3C_GetIBIType(base);
                    handle->ibiAddress = I3C_GetIBIAddress(base);
                    state_complete     = true;
                    result             = kStatus_I3C_IBIWon;
                }
                else
                {
                    state_complete = true;
                }
                break;

            case (uint8_t)kWaitRepeatedStartCompleteState:
                /* We stay in this state until the master complete. */
                if (0UL != (status & (uint32_t)kI3C_MasterCompleteFlag))
                {
                    handle->state = (uint8_t)kWaitForCompletionState;
                    /* Send repeated start and slave address. */
                    result = I3C_MasterRepeatedStart(base, xfer->busType, xfer->slaveAddress, kI3C_Read);
                }

                state_complete = true;
                break;

            case (uint8_t)kWaitForCompletionState:
                /* We stay in this state until the master complete. */
                if (0UL != (status & (uint32_t)kI3C_MasterCompleteFlag))
                {
                    handle->state = (uint8_t)kStopState;
                }
                else
                {
                    state_complete = true;
                }
                break;

            case (uint8_t)kStopState:
                /* Only issue a stop transition if the caller requested it. */
                if (0UL == (xfer->flags & (uint32_t)kI3C_TransferNoStopFlag))
                {
                    handle->base->MDATACTRL &= ~I3C_MDMACTRL_DMAFB_MASK;

                    if (xfer->busType == kI3C_TypeI3CDdr)
                    {
                        I3C_MasterEmitRequest(base, kI3C_RequestForceExit);
                    }
                    else
                    {
                        I3C_MasterEmitRequest(base, kI3C_RequestEmitStop);
                    }
                }
                *isDone        = true;
                state_complete = true;
                break;

            default:
                assert(false);
                break;
        }
    }
    return result;
}

void I3C_MasterTransferCreateHandleDMA(I3C_Type *base,
                                       i3c_master_dma_handle_t *handle,
                                       const i3c_master_dma_callback_t *callback,
                                       void *userData,
                                       dma_handle_t *rxDmaHandle,
                                       dma_handle_t *txDmaHandle)
{
    uint32_t instance;

    assert(NULL != handle);

    /* Clear out the handle. */
    (void)memset(handle, 0, sizeof(*handle));

    /* Look up instance number */
    instance = I3C_GetInstance(base);

    handle->base        = base;
    handle->txDmaHandle = txDmaHandle;
    handle->rxDmaHandle = rxDmaHandle;
    handle->callback    = *callback;
    handle->userData    = userData;

    /* Save this handle for IRQ use. */
    s_i3cMasterHandle[instance] = handle;

    /* Set irq handler. */
    s_i3cMasterIsr = I3C_MasterTransferDMAHandleIRQ;

    DMA_SetCallback(handle->rxDmaHandle, I3C_MasterTransferDMACallbackRx, handle);
    DMA_SetCallback(handle->txDmaHandle, I3C_MasterTransferDMACallbackTx, handle);

    /* Clear all flags. */
    I3C_MasterClearErrorStatusFlags(base, (uint32_t)kMasterErrorFlags);
    I3C_MasterClearStatusFlags(base, (uint32_t)kMasterClearFlags);
    /* Reset fifos. These flags clear automatically. */
    base->MDATACTRL |= I3C_MDATACTRL_FLUSHTB_MASK | I3C_MDATACTRL_FLUSHFB_MASK;

    /* Enable NVIC IRQ, this only enables the IRQ directly connected to the NVIC.
     In some cases the I3C IRQ is configured through INTMUX, user needs to enable
     INTMUX IRQ in application code. */
    (void)EnableIRQ(kI3cIrqs[instance]);

    /* Clear internal IRQ enables and enable NVIC IRQ. */
    I3C_MasterEnableInterrupts(base, (uint32_t)kMasterDMAIrqFlags);
}

/*!
 * brief Performs a non-blocking DMA transaction on the I2C/I3C bus.
 *
 * param base The I3C peripheral base address.
 * param handle Pointer to the I3C master driver handle.
 * param transfer The pointer to the transfer descriptor.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_I3C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t I3C_MasterTransferDMA(I3C_Type *base, i3c_master_dma_handle_t *handle, i3c_master_transfer_t *transfer)
{
    assert(NULL != handle);
    assert(NULL != transfer);
    assert(transfer->subaddressSize <= sizeof(transfer->subaddress));

    i3c_master_state_t masterState = I3C_MasterGetState(base);
    bool checkDdrState;
    status_t result;

    /* Return busy if another transaction is in progress. */
    if (handle->state != (uint8_t)kIdleState)
    {
        return kStatus_I3C_Busy;
    }

    /* Return an error if the bus is already in use not by us. */
    checkDdrState = (transfer->busType == kI3C_TypeI3CDdr) ? (masterState != kI3C_MasterStateDdr) : true;
    if ((masterState != kI3C_MasterStateIdle) && (masterState != kI3C_MasterStateNormAct) && checkDdrState)
    {
        return kStatus_I3C_Busy;
    }

    /* Disable I3C IRQ sources while we configure stuff. */
    I3C_MasterDisableInterrupts(
        base, ((uint32_t)kMasterDMAIrqFlags | (uint32_t)kI3C_MasterRxReadyFlag | (uint32_t)kI3C_MasterTxReadyFlag));

    /* Save transfer into handle. */
    handle->transfer = *transfer;

    /* Configure IBI response type. */
    base->MCTRL &= ~I3C_MCTRL_IBIRESP_MASK;
    base->MCTRL |= I3C_MCTRL_IBIRESP(transfer->ibiResponse);

    /* Clear all flags. */
    I3C_MasterClearErrorStatusFlags(base, (uint32_t)kMasterErrorFlags);
    I3C_MasterClearStatusFlags(base, (uint32_t)kMasterClearFlags);
    /* Reset fifos. These flags clear automatically. */
    base->MDATACTRL |= I3C_MDATACTRL_FLUSHTB_MASK | I3C_MDATACTRL_FLUSHFB_MASK;

    /* Generate commands to send. */
    result = I3C_MasterInitTransferStateMachineDMA(base, handle);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Enable I3C internal IRQ sources. NVIC IRQ was enabled in CreateHandle() */
    I3C_MasterEnableInterrupts(base, (uint32_t)(kMasterDMAIrqFlags));

    if (transfer->busType == kI3C_TypeI2C)
    {
        I3C_MasterDisableInterrupts(base, (uint32_t)kI3C_MasterSlaveStartFlag);
    }

    return kStatus_Success;
}

void I3C_MasterTransferDMAHandleIRQ(I3C_Type *base, void *i3cHandle)
{
    i3c_master_dma_handle_t *handle = (i3c_master_dma_handle_t *)i3cHandle;
    status_t result;
    bool isDone;

    /* Don't do anything if we don't have a valid handle. */
    if (NULL == handle)
    {
        return;
    }

    result = I3C_MasterRunTransferStateMachineDMA(base, handle, &isDone);

    if (handle->state == (uint8_t)kIdleState)
    {
        return;
    }

    if (isDone || (result != kStatus_Success))
    {
        /* XXX handle error, terminate xfer */
        if ((result == kStatus_I3C_Nak) || (result == kStatus_I3C_IBIWon))
        {
            I3C_MasterEmitRequest(base, kI3C_RequestEmitStop);
        }

        /* Set handle to idle state. */
        handle->state = (uint8_t)kIdleState;

        /* Invoke IBI user callback. */
        if ((result == kStatus_I3C_IBIWon) && (handle->callback.ibiCallback != NULL))
        {
            handle->callback.ibiCallback(base, handle, handle->ibiType, kI3C_IbiReady);
            handle->ibiPayloadSize = 0;
        }

        /* Invoke callback. */
        if (NULL != handle->callback.transferComplete)
        {
            handle->callback.transferComplete(base, handle, result, handle->userData);
        }
    }
}

/*!
 * brief Get master transfer status during a dma non-blocking transfer
 *
 * param base I3C peripheral base address
 * param handle pointer to i2c_master_dma_handle_t structure
 * param count Number of bytes transferred so far by the non-blocking transaction.
 */
status_t I3C_MasterTransferGetCountDMA(I3C_Type *base, i3c_master_dma_handle_t *handle, size_t *count)
{
    assert(handle != NULL);

    if (NULL == count)
    {
        return kStatus_InvalidArgument;
    }

    /* Catch when there is not an active transfer. */
    if (handle->state == (uint8_t)kIdleState)
    {
        *count = 0;
        return kStatus_NoTransferInProgress;
    }

    /* There is no necessity to disable interrupts as we read a single integer value */
    i3c_direction_t dir = handle->transfer.direction;

    if (dir == kI3C_Read)
    {
        *count = handle->transferCount - DMA_GetRemainingBytes(handle->rxDmaHandle->base, handle->rxDmaHandle->channel);
    }
    else
    {
        *count = handle->transferCount - DMA_GetRemainingBytes(handle->txDmaHandle->base, handle->txDmaHandle->channel);
    }

    return kStatus_Success;
}

/*!
 * brief Abort a master dma non-blocking transfer in a early time
 *
 * param base I3C peripheral base address
 * param handle pointer to i2c_master_dma_handle_t structure
 */
void I3C_MasterTransferAbortDMA(I3C_Type *base, i3c_master_dma_handle_t *handle)
{
    if (handle->state != (uint8_t)kIdleState)
    {
        DMA_AbortTransfer(handle->txDmaHandle);
        DMA_AbortTransfer(handle->rxDmaHandle);

        I3C_MasterEnableDMA(base, false, false, 0);

        /* Reset fifos. These flags clear automatically. */
        base->MDATACTRL |= I3C_MDATACTRL_FLUSHTB_MASK | I3C_MDATACTRL_FLUSHFB_MASK;

        /* Send a stop command to finalize the transfer. */
        (void)I3C_MasterStop(base);

        /* Reset handle. */
        handle->state = (uint8_t)kIdleState;
    }
}

static void I3C_SlaveTransferDMACallback(dma_handle_t *dmaHandle, void *param, bool transferDone, uint32_t tcds)
{
    i3c_slave_dma_handle_t *i3cHandle = (i3c_slave_dma_handle_t *)param;

    if (transferDone)
    {
        /* Simply diable dma enablement */
        if (i3cHandle->txDmaHandle == dmaHandle)
        {
            i3cHandle->base->SDMACTRL &= ~I3C_SDMACTRL_DMATB_MASK;
        }
        else
        {
            i3cHandle->base->SDMACTRL &= ~I3C_SDMACTRL_DMAFB_MASK;
        }
    }
}

/*!
 * brief Create a new handle for the I3C slave DMA APIs.
 *
 * The creation of a handle is for use with the DMA APIs. Once a handle
 * is created, there is not a corresponding destroy handle. If the user wants to
 * terminate a transfer, the I3C_SlaveTransferAbortDMA() API shall be called.
 *
 * For devices where the I3C send and receive DMA requests are OR'd together, the @a txDmaHandle
 * parameter is ignored and may be set to NULL.
 *
 * param base The I3C peripheral base address.
 * param handle Pointer to the I3C slave driver handle.
 * param callback User provided pointer to the asynchronous callback function.
 * param userData User provided pointer to the application callback data.
 * param rxDmaHandle Handle for the DMA receive channel. Created by the user prior to calling this function.
 * param txDmaHandle Handle for the DMA transmit channel. Created by the user prior to calling this function.
 */
void I3C_SlaveTransferCreateHandleDMA(I3C_Type *base,
                                      i3c_slave_dma_handle_t *handle,
                                      i3c_slave_dma_callback_t callback,
                                      void *userData,
                                      dma_handle_t *rxDmaHandle,
                                      dma_handle_t *txDmaHandle)
{
    uint32_t instance;

    assert(NULL != handle);

    /* Clear out the handle. */
    (void)memset(handle, 0, sizeof(*handle));

    /* Look up instance number */
    instance = I3C_GetInstance(base);

    handle->base        = base;
    handle->txDmaHandle = txDmaHandle;
    handle->rxDmaHandle = rxDmaHandle;
    handle->callback    = callback;
    handle->userData    = userData;

    /* Save this handle for IRQ use. */
    s_i3cSlaveHandle[instance] = handle;

    /* Set irq handler. */
    s_i3cSlaveIsr = I3C_SlaveTransferDMAHandleIRQ;

    DMA_SetCallback(handle->rxDmaHandle, I3C_SlaveTransferDMACallback, handle);
    DMA_SetCallback(handle->txDmaHandle, I3C_SlaveTransferDMACallback, handle);

    /* Clear internal IRQ enables and enable NVIC IRQ. */
    I3C_SlaveDisableInterrupts(base, (uint32_t)kSlaveDMAIrqFlags);

    /* Enable NVIC IRQ, this only enables the IRQ directly connected to the NVIC.
     In some cases the I3C IRQ is configured through INTMUX, user needs to enable
     INTMUX IRQ in application code. */
    (void)EnableIRQ(kI3cIrqs[instance]);

    /* Enable IRQ. */
    I3C_SlaveEnableInterrupts(base, (uint32_t)kSlaveDMAIrqFlags);
}

static void I3C_SlavePrepareTxDMA(I3C_Type *base, i3c_slave_dma_handle_t *handle)
{
    i3c_slave_dma_transfer_t *xfer = &handle->transfer;
    dma_channel_config_t txChannelConfig;
    uint32_t *txFifoBase;

    if (xfer->txDataSize == 1U)
    {
        txFifoBase = (uint32_t *)(uint32_t)&base->SWDATABE;
        DMA_PrepareChannelTransfer(&txChannelConfig, xfer->txData, (void *)txFifoBase,
                                   DMA_CHANNEL_XFER(false, false, true, false, 1u, kDMA_AddressInterleave1xWidth,
                                                    kDMA_AddressInterleave0xWidth, xfer->txDataSize),
                                   kDMA_MemoryToPeripheral, NULL, NULL);
    }
    else
    {
        uint32_t instance = I3C_GetInstance(base);

#ifdef I3C_SWDATAB1_DATA_MASK
        txFifoBase = (uint32_t *)(uint32_t)&base->SWDATAB1;
#else
        txFifoBase = (uint32_t *)(uint32_t)&base->SWDATAB;
#endif
        DMA_PrepareChannelTransfer(&txChannelConfig, xfer->txData, (void *)txFifoBase,
                                   DMA_CHANNEL_XFER(true, false, false, false, 1u, kDMA_AddressInterleave1xWidth,
                                                    kDMA_AddressInterleave0xWidth, xfer->txDataSize - 1U),
                                   kDMA_MemoryToPeripheral, NULL, &(s_dma_table[instance][0]));

        txFifoBase = (uint32_t *)(uint32_t)&base->SWDATABE;
        DMA_SetupDescriptor(&(s_dma_table[instance][0]),
                            DMA_CHANNEL_XFER(false, false, true, false, 1u, kDMA_AddressInterleave1xWidth,
                                             kDMA_AddressInterleave0xWidth, 1U),
                            xfer->txData + xfer->txDataSize - 1U, txFifoBase, NULL);
    }
    (void)DMA_SubmitChannelTransfer(handle->txDmaHandle, &txChannelConfig);
    DMA_StartTransfer(handle->txDmaHandle);
}

static void I3C_SlavePrepareRxDMA(I3C_Type *base, i3c_slave_dma_handle_t *handle)
{
    uint32_t *rxFifoBase           = (uint32_t *)(uint32_t)&base->SRDATAB;
    i3c_slave_dma_transfer_t *xfer = &handle->transfer;
    dma_channel_config_t rxChannelConfig;

    DMA_PrepareChannelTransfer(&rxChannelConfig, (void *)rxFifoBase, xfer->rxData,
                               DMA_CHANNEL_XFER(false, true, true, false, 1u, kDMA_AddressInterleave0xWidth,
                                                kDMA_AddressInterleave1xWidth, xfer->rxDataSize),
                               kDMA_PeripheralToMemory, NULL, NULL);
    (void)DMA_SubmitChannelTransfer(handle->rxDmaHandle, &rxChannelConfig);
    DMA_StartTransfer(handle->rxDmaHandle);
}

/*!
 * brief Prepares for a non-blocking DMA-based transaction on the I3C bus.
 *
 * The API will do DMA configuration according to the input transfer descriptor, and the data will be transferred when
 * there's bus master requesting transfer from/to this slave. So the timing of call to this API need be aligned
 * with master application to ensure the transfer is executed as expected.
 * Callback specified when the @a handle was created is invoked when the transaction has completed.
 *
 * param base The I3C peripheral base address.
 * param handle Pointer to the I3C slave driver handle.
 * param transfer The pointer to the transfer descriptor.
 * param eventMask Bit mask formed by OR'ing together #i3c_slave_transfer_event_t enumerators to specify
 *      which events to send to the callback. The transmit and receive events is not allowed to be enabled.
 * retval kStatus_Success The transaction was started successfully.
 * retval #kStatus_I3C_Busy Either another master is currently utilizing the bus, or another DMA
 *      transaction is already in progress.
 */
status_t I3C_SlaveTransferDMA(I3C_Type *base,
                              i3c_slave_dma_handle_t *handle,
                              i3c_slave_dma_transfer_t *transfer,
                              uint32_t eventMask)
{
    assert(NULL != handle);
    assert(NULL != transfer);

    bool txDmaEn = false, rxDmaEn = false;
    uint32_t width;

    if (handle->isBusy)
    {
        return kStatus_I3C_Busy;
    }

    /* Clear all flags. */
    I3C_SlaveClearErrorStatusFlags(base, (uint32_t)kSlaveErrorFlags);
    I3C_SlaveClearStatusFlags(base, (uint32_t)kSlaveClearFlags);
    /* Reset fifos. These flags clear automatically. */
    base->SDATACTRL |= I3C_SDATACTRL_FLUSHTB_MASK | I3C_SDATACTRL_FLUSHFB_MASK;

    handle->transfer  = *transfer;
    handle->eventMask = eventMask;

    if ((transfer->txData != NULL) && (transfer->txDataSize != 0U))
    {
        I3C_SlavePrepareTxDMA(base, handle);
        txDmaEn = true;
        width   = 2U;
    }

    if ((transfer->rxData != NULL) && (transfer->rxDataSize != 0U))
    {
        I3C_SlavePrepareRxDMA(base, handle);
        rxDmaEn = true;
        width   = 1U;
    }

    if (txDmaEn || rxDmaEn)
    {
        I3C_SlaveEnableDMA(base, txDmaEn, rxDmaEn, width);
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

void I3C_SlaveTransferDMAHandleIRQ(I3C_Type *base, void *i3cHandle)
{
    i3c_slave_dma_handle_t *handle = (i3c_slave_dma_handle_t *)i3cHandle;
    i3c_slave_dma_transfer_t *xfer;
    uint32_t flags;
    uint32_t errFlags;

    /* Check for a valid handle in case of a spurious interrupt. */
    if (NULL == handle)
    {
        return;
    }

    xfer = &handle->transfer;

    /* Get status flags. */
    flags    = I3C_SlaveGetStatusFlags(base);
    errFlags = I3C_SlaveGetErrorStatusFlags(base);

    /* Clear status flags. */
    I3C_SlaveClearStatusFlags(base, flags);

    if (0UL != (errFlags & (uint32_t)kSlaveErrorFlags))
    {
        xfer->event            = (uint32_t)kI3C_SlaveCompletionEvent;
        xfer->completionStatus = I3C_SlaveCheckAndClearError(base, errFlags);

        if ((0UL != (handle->eventMask & (uint32_t)kI3C_SlaveCompletionEvent)) && (NULL != handle->callback))
        {
            handle->callback(base, xfer, handle->userData);
        }
        return;
    }

    if (0UL != (flags & (uint32_t)kI3C_SlaveEventSentFlag))
    {
        xfer->event = (uint32_t)kI3C_SlaveRequestSentEvent;
        if ((0UL != (handle->eventMask & xfer->event)) && (NULL != handle->callback))
        {
            handle->callback(base, xfer, handle->userData);
        }
    }

    if (0UL != (flags & (uint32_t)kI3C_SlaveReceivedCCCFlag))
    {
        handle->isBusy = true;
        xfer->event    = (uint32_t)kI3C_SlaveReceivedCCCEvent;
        if ((0UL != (handle->eventMask & xfer->event)) && (NULL != handle->callback))
        {
            handle->callback(base, xfer, handle->userData);
        }
    }

    if (0UL != (flags & (uint32_t)kI3C_SlaveBusStopFlag))
    {
        if (handle->isBusy)
        {
            xfer->event            = (uint32_t)kI3C_SlaveCompletionEvent;
            xfer->completionStatus = kStatus_Success;
            handle->isBusy         = false;

            if ((0UL != (handle->eventMask & xfer->event)) && (NULL != handle->callback))
            {
                handle->callback(base, xfer, handle->userData);
            }
            I3C_SlaveTransferAbortDMA(base, handle);
        }
        else
        {
            return;
        }
    }

    if (0UL != (flags & (uint32_t)kI3C_SlaveMatchedFlag))
    {
        xfer->event    = (uint32_t)kI3C_SlaveAddressMatchEvent;
        handle->isBusy = true;
        if ((0UL != (handle->eventMask & (uint32_t)kI3C_SlaveAddressMatchEvent)) && (NULL != handle->callback))
        {
            handle->callback(base, xfer, handle->userData);
        }
    }

    if (0UL != (flags & (uint32_t)kI3C_SlaveBusHDRModeFlag))
    {
        handle->isBusy = true;
    }
}

/*!
 * brief Abort a slave dma non-blocking transfer in a early time
 *
 * param base I3C peripheral base address
 * param handle pointer to i3c_slave_dma_handle_t structure
 */
void I3C_SlaveTransferAbortDMA(I3C_Type *base, i3c_slave_dma_handle_t *handle)
{
    if (handle->isBusy)
    {
        DMA_AbortTransfer(handle->txDmaHandle);
        DMA_AbortTransfer(handle->rxDmaHandle);

        I3C_SlaveEnableDMA(base, false, false, 0);

        /* Reset fifos. These flags clear automatically. */
        base->SDATACTRL |= I3C_SDATACTRL_FLUSHTB_MASK | I3C_SDATACTRL_FLUSHFB_MASK;
    }
}
