/*
 * Copyright 2016-2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_ecspi_sdma.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.ecspi_sdma"
#endif

/*!
 * @brief Structure definition for ecspi_master_sdma_private_handle_t. The structure is private.
 */
typedef struct _ecspi_master_sdma_private_handle
{
    ECSPI_Type *base;            /*!< ECSPI peripheral base address. */
    ecspi_sdma_handle_t *handle; /*!< ecspi_sdma_handle_t handle */
} ecspi_master_sdma_private_handle_t;

/*!
 * @brief Structure definition for ecspi_slave_sdma_private_handle_t. The structure is private.
 */
typedef struct _ecspi_slave_sdma_private_handle
{
    ECSPI_Type *base;            /*!< ECSPI peripheral base address. */
    ecspi_sdma_handle_t *handle; /*!< ecspi_sdma_handle_t handle */
} ecspi_slave_sdma_private_handle_t;

/*! @brief ECSPI transfer state, which is used for ECSPI transactiaonl APIs' internal state. */
enum _ecspi_sdma_states_t
{
    kECSPI_Idle = 0x0, /*!< ECSPI is idle state */
    kECSPI_Busy        /*!< ECSPI is busy tranferring data. */
};
/*! @brief Base pointer array */
static ECSPI_Type *const s_ecspiBases[] = ECSPI_BASE_PTRS;
/*<! Private handle only used for internally. */
static ecspi_master_sdma_private_handle_t s_ecspiMasterSdmaPrivateHandle[ARRAY_SIZE(s_ecspiBases)];
static ecspi_slave_sdma_private_handle_t s_ecspiSlaveSdmaPrivateHandle[ARRAY_SIZE(s_ecspiBases)];
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief SDMA_EcspiMasterCallback after the ECSPI master transfer completed by using SDMA.
 * This is not a public API.
 */
static void SDMA_EcspiMasterCallback(sdma_handle_t *sdmaHandle,
                                     void *g_ecspiSdmaPrivateHandle,
                                     bool transferDone,
                                     uint32_t tcds);

/*!
 * @brief SDMA_EcspiSlaveCallback after the ECSPI slave transfer completed by using SDMA.
 * This is not a public API.
 */
static void SDMA_EcspiSlaveCallback(sdma_handle_t *sdmaHandle,
                                    void *g_ecspiSdmaPrivateHandle,
                                    bool transferDone,
                                    uint32_t tcds);
/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
static void SDMA_EcspiMasterCallback(sdma_handle_t *sdmaHandle,
                                     void *g_ecspiSdmaPrivateHandle,
                                     bool transferDone,
                                     uint32_t tcds)
{
    assert(sdmaHandle != NULL);
    assert(g_ecspiSdmaPrivateHandle != NULL);

    ecspi_master_sdma_private_handle_t *ecspiSdmaPrivateHandle;

    ecspiSdmaPrivateHandle = (ecspi_master_sdma_private_handle_t *)g_ecspiSdmaPrivateHandle;
    /* if channel is Tx channel, disable Tx channel SDMA enable*/
    if (sdmaHandle->channel == ecspiSdmaPrivateHandle->handle->ChannelTx)
    {
        ECSPI_EnableDMA((ecspiSdmaPrivateHandle->base), kECSPI_TxDmaEnable, false);
        ecspiSdmaPrivateHandle->handle->txInProgress = false;
        SDMA_SetChannelPriority(sdmaHandle->base, sdmaHandle->channel, 0);
        SDMA_AbortTransfer(sdmaHandle);
    }
    /* if channel is Rx channel, disable Rx channel SDMA enable*/
    else
    {
        ECSPI_EnableDMA((ecspiSdmaPrivateHandle->base), kECSPI_RxDmaEnable, false);
        ecspiSdmaPrivateHandle->handle->rxInProgress = false;
        SDMA_SetChannelPriority(sdmaHandle->base, sdmaHandle->channel, 0);
        SDMA_AbortTransfer(sdmaHandle);
    }
    /* if both channel is finished, then abort SDMA transfer*/
    if ((ecspiSdmaPrivateHandle->handle->txInProgress == false) &&
        (ecspiSdmaPrivateHandle->handle->rxInProgress == false))
    {
        ECSPI_MasterTransferAbortSDMA(ecspiSdmaPrivateHandle->base, ecspiSdmaPrivateHandle->handle);
        if (ecspiSdmaPrivateHandle->handle->callback != NULL)
        {
            ecspiSdmaPrivateHandle->handle->callback(ecspiSdmaPrivateHandle->base, ecspiSdmaPrivateHandle->handle,
                                                     kStatus_Success, ecspiSdmaPrivateHandle->handle->userData);
        }
        ecspiSdmaPrivateHandle->handle->state = (uint32_t)kECSPI_Idle;
    }
}

/*!
 * brief Abort a ECSPI master transfer using SDMA.
 *
 * param base ECSPI peripheral base address.
 * param handle ECSPI SDMA handle pointer.
 */
void ECSPI_MasterTransferAbortSDMA(ECSPI_Type *base, ecspi_sdma_handle_t *handle)
{
    assert(handle != NULL);

    ECSPI_Enable(base, false);

    ECSPI_EnableDMA(base, kECSPI_DmaAllEnable, false);

    SDMA_AbortTransfer(handle->rxSdmaHandle);
    SDMA_AbortTransfer(handle->txSdmaHandle);

    handle->state = (uint32_t)kECSPI_Idle;
}

static void SDMA_EcspiSlaveCallback(sdma_handle_t *sdmaHandle,
                                    void *g_ecspiSdmaPrivateHandle,
                                    bool transferDone,
                                    uint32_t tcds)
{
    assert(sdmaHandle != NULL);
    assert(g_ecspiSdmaPrivateHandle != NULL);

    ecspi_slave_sdma_private_handle_t *ecspiSdmaPrivateHandle;

    ecspiSdmaPrivateHandle = (ecspi_slave_sdma_private_handle_t *)g_ecspiSdmaPrivateHandle;
    /* if channel is Tx channel, disable Tx channel SDMA enable*/
    if (sdmaHandle->channel == ecspiSdmaPrivateHandle->handle->ChannelTx)
    {
        ECSPI_EnableDMA((ecspiSdmaPrivateHandle->base), kECSPI_TxDmaEnable, false);
        ecspiSdmaPrivateHandle->handle->txInProgress = false;
        SDMA_SetChannelPriority(sdmaHandle->base, sdmaHandle->channel, 0);
        SDMA_AbortTransfer(sdmaHandle);
    }
    /* if channel is Rx channel, disable Rx channel SDMA enable*/
    else
    {
        ECSPI_EnableDMA((ecspiSdmaPrivateHandle->base), kECSPI_RxDmaEnable, false);
        ecspiSdmaPrivateHandle->handle->rxInProgress = false;
        SDMA_SetChannelPriority(sdmaHandle->base, sdmaHandle->channel, 0);
        SDMA_AbortTransfer(sdmaHandle);
    }
    /* if both channel is finished, then abort SDMA transfer*/
    if ((ecspiSdmaPrivateHandle->handle->txInProgress == false) &&
        (ecspiSdmaPrivateHandle->handle->rxInProgress == false))
    {
        ECSPI_MasterTransferAbortSDMA(ecspiSdmaPrivateHandle->base, ecspiSdmaPrivateHandle->handle);
        if (ecspiSdmaPrivateHandle->handle->callback != NULL)
        {
            ecspiSdmaPrivateHandle->handle->callback(ecspiSdmaPrivateHandle->base, ecspiSdmaPrivateHandle->handle,
                                                     kStatus_Success, ecspiSdmaPrivateHandle->handle->userData);
        }
        ecspiSdmaPrivateHandle->handle->state = (uint32_t)kECSPI_Idle;
    }
}

/*!
 * brief Abort a ECSPI slave transfer using SDMA.
 *
 * param base ECSPI peripheral base address.
 * param handle ECSPI SDMA handle pointer.
 */
void ECSPI_SlaveTransferAbortSDMA(ECSPI_Type *base, ecspi_sdma_handle_t *handle)
{
    assert(handle != NULL);

    ECSPI_Enable(base, false);

    ECSPI_EnableDMA(base, kECSPI_RxDmaEnable, false);
    ECSPI_EnableDMA(base, kECSPI_TxDmaEnable, false);

    SDMA_AbortTransfer(handle->rxSdmaHandle);
    SDMA_AbortTransfer(handle->txSdmaHandle);

    handle->state = (uint32_t)kECSPI_Idle;
}

/*!
 * brief Initialize the ECSPI master SDMA handle.
 *
 * This function initializes the ECSPI master SDMA handle which can be used for other SPI master transactional APIs.
 * Usually, for a specified ECSPI instance, user need only call this API once to get the initialized handle.
 *
 * param base ECSPI peripheral base address.
 * param handle ECSPI handle pointer.
 * param callback User callback function called at the end of a transfer.
 * param userData User data for callback.
 * param txHandle SDMA handle pointer for ECSPI Tx, the handle shall be static allocated by users.
 * param rxHandle SDMA handle pointer for ECSPI Rx, the handle shall be static allocated by users.
 * param eventSourceTx event source for ECSPI send, which can be found in SDMA mapping.
 * param eventSourceRx event source for ECSPI receive, which can be found in SDMA mapping.
 * param TxChannel SDMA channel for ECSPI send.
 * param RxChannel SDMA channel for ECSPI receive.
 */
void ECSPI_MasterTransferCreateHandleSDMA(ECSPI_Type *base,
                                          ecspi_sdma_handle_t *handle,
                                          ecspi_sdma_callback_t callback,
                                          void *userData,
                                          sdma_handle_t *txHandle,
                                          sdma_handle_t *rxHandle,
                                          uint32_t eventSourceTx,
                                          uint32_t eventSourceRx,
                                          uint32_t TxChannel,
                                          uint32_t RxChannel)
{
    assert(handle != NULL);
    assert(txHandle != NULL);
    assert(rxHandle != NULL);
    uint32_t instance = ECSPI_GetInstance(base);

    /* Zero the handle */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set ECSPI base to handle */
    rxHandle->eventSource = eventSourceRx;
    txHandle->eventSource = eventSourceTx;
    handle->txSdmaHandle  = txHandle;
    handle->rxSdmaHandle  = rxHandle;
    handle->ChannelTx     = TxChannel;
    handle->ChannelRx     = RxChannel;
    handle->callback      = callback;
    handle->userData      = userData;

    /* Set ECSPI state to idle */
    handle->state = (uint32_t)kECSPI_Idle;

    /* Set handle to global state */
    s_ecspiMasterSdmaPrivateHandle[instance].base   = base;
    s_ecspiMasterSdmaPrivateHandle[instance].handle = handle;

    /* Install callback for Tx and Rx sdma channel */
    SDMA_SetCallback(handle->rxSdmaHandle, SDMA_EcspiMasterCallback, &s_ecspiMasterSdmaPrivateHandle[instance]);
    SDMA_SetCallback(handle->txSdmaHandle, SDMA_EcspiMasterCallback, &s_ecspiMasterSdmaPrivateHandle[instance]);
}

/*!
 * brief Initialize the ECSPI Slave SDMA handle.
 *
 * This function initializes the ECSPI Slave SDMA handle which can be used for other SPI Slave transactional APIs.
 * Usually, for a specified ECSPI instance, user need only call this API once to get the initialized handle.
 *
 * param base ECSPI peripheral base address.
 * param handle ECSPI handle pointer.
 * param callback User callback function called at the end of a transfer.
 * param userData User data for callback.
 * param txHandle SDMA handle pointer for ECSPI Tx, the handle shall be static allocated by users.
 * param rxHandle SDMA handle pointer for ECSPI Rx, the handle shall be static allocated by users.
 * param eventSourceTx event source for ECSPI send, which can be found in SDMA mapping.
 * param eventSourceRx event source for ECSPI receive, which can be found in SDMA mapping.
 * param TxChannel SDMA channel for ECSPI send.
 * param RxChannel SDMA channel for ECSPI receive.
 */
void ECSPI_SlaveTransferCreateHandleSDMA(ECSPI_Type *base,
                                         ecspi_sdma_handle_t *handle,
                                         ecspi_sdma_callback_t callback,
                                         void *userData,
                                         sdma_handle_t *txHandle,
                                         sdma_handle_t *rxHandle,
                                         uint32_t eventSourceTx,
                                         uint32_t eventSourceRx,
                                         uint32_t TxChannel,
                                         uint32_t RxChannel)
{
    assert(handle != NULL);
    assert(txHandle != NULL);
    assert(rxHandle != NULL);
    uint32_t instance = ECSPI_GetInstance(base);

    /* Zero the handle */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set ECSPI base to handle */
    rxHandle->eventSource = eventSourceRx;
    txHandle->eventSource = eventSourceTx;
    handle->txSdmaHandle  = txHandle;
    handle->rxSdmaHandle  = rxHandle;
    handle->ChannelTx     = TxChannel;
    handle->ChannelRx     = RxChannel;
    handle->callback      = callback;
    handle->userData      = userData;

    /* Set ECSPI state to idle */
    handle->state = (uint32_t)kECSPI_Idle;

    /* Set handle to global state */
    s_ecspiSlaveSdmaPrivateHandle[instance].base   = base;
    s_ecspiSlaveSdmaPrivateHandle[instance].handle = handle;

    /* Install callback for Tx and Rx sdma channel */
    SDMA_SetCallback(handle->txSdmaHandle, SDMA_EcspiSlaveCallback, &s_ecspiSlaveSdmaPrivateHandle[instance]);
    SDMA_SetCallback(handle->rxSdmaHandle, SDMA_EcspiSlaveCallback, &s_ecspiSlaveSdmaPrivateHandle[instance]);
}

/*!
 * brief Perform a non-blocking ECSPI master transfer using SDMA.
 *
 * note This interface returned immediately after transfer initiates.
 *
 * param base ECSPI peripheral base address.
 * param handle ECSPI SDMA handle pointer.
 * param xfer Pointer to sdma transfer structure.
 * retval kStatus_Success Successfully start a transfer.
 * retval kStatus_InvalidArgument Input argument is invalid.
 * retval kStatus_ECSPI_Busy EECSPI is not idle, is running another transfer.
 */
status_t ECSPI_MasterTransferSDMA(ECSPI_Type *base, ecspi_sdma_handle_t *handle, ecspi_transfer_t *xfer)
{
    assert((base != NULL) && (handle != NULL) && (xfer != NULL));

    sdma_transfer_config_t xferConfig = {0U};
    sdma_peripheral_t perType         = kSDMA_PeripheralNormal;

    /* Check if ECSPI is busy */
    if (handle->state == (uint32_t)kECSPI_Busy)
    {
        return kStatus_ECSPI_Busy;
    }

    /* Check if the input arguments valid */
    if (((xfer->txData == NULL) && (xfer->rxData == NULL)) || (xfer->dataSize == 0U))
    {
        return kStatus_InvalidArgument;
    }
    ECSPI_Enable(base, true);
    handle->state = (uint32_t)kECSPI_Busy;

    ECSPI_SetChannelSelect(base, xfer->channel);

#if defined(FSL_FEATURE_SOC_SPBA_COUNT) && (FSL_FEATURE_SOC_SPBA_COUNT > 0)
    bool isSpba = SDMA_IsPeripheralInSPBA((uint32_t)base);
    /* Judge if the instance is located in SPBA */
    if (isSpba)
    {
        perType = kSDMA_PeripheralNormal_SP;
    }
#endif /* FSL_FEATURE_SOC_SPBA_COUNT */

    /* Prepare transfer. */
    SDMA_PrepareTransfer(&xferConfig, (uint32_t)xfer->txData, (uint32_t) & (base->TXDATA), sizeof(uint8_t),
                         sizeof(uint8_t), sizeof(uint8_t), xfer->dataSize, handle->txSdmaHandle->eventSource, perType,
                         kSDMA_MemoryToPeripheral);

    /* Submit transfer. */
    SDMA_SubmitTransfer(handle->txSdmaHandle, &xferConfig);

    /* Prepare transfer. */
    SDMA_PrepareTransfer(&xferConfig, (uint32_t) & (base->RXDATA), (uint32_t)xfer->rxData, sizeof(uint8_t),
                         sizeof(uint8_t), sizeof(uint8_t), xfer->dataSize, handle->rxSdmaHandle->eventSource, perType,
                         kSDMA_PeripheralToMemory);
    /* Submit transfer. */
    SDMA_SubmitTransfer(handle->rxSdmaHandle, &xferConfig);
    /* Start Rx transfer */
    handle->rxInProgress = true;
    SDMA_StartTransfer(handle->rxSdmaHandle);
    ECSPI_EnableDMA(base, kECSPI_RxDmaEnable, true);

    /* Start Tx transfer */
    handle->txInProgress = true;
    SDMA_StartTransfer(handle->txSdmaHandle);
    ECSPI_EnableDMA(base, kECSPI_TxDmaEnable, true);

    return kStatus_Success;
}

/*!
 * brief Perform a non-blocking ECSPI slave transfer using SDMA.
 *
 * note This interface returned immediately after transfer initiates.
 *
 * param base ECSPI peripheral base address.
 * param handle ECSPI SDMA handle pointer.
 * param xfer Pointer to sdma transfer structure.
 * retval kStatus_Success Successfully start a transfer.
 * retval kStatus_InvalidArgument Input argument is invalid.
 * retval kStatus_ECSPI_Busy EECSPI is not idle, is running another transfer.
 */
status_t ECSPI_SlaveTransferSDMA(ECSPI_Type *base, ecspi_sdma_handle_t *handle, ecspi_transfer_t *xfer)
{
    assert((base != NULL) && (handle != NULL) && (xfer != NULL));

    sdma_transfer_config_t xferConfig;
    sdma_peripheral_t perType = kSDMA_PeripheralNormal;

    /* Check if ECSPI is busy */
    if (handle->state == (uint32_t)kECSPI_Busy)
    {
        return kStatus_ECSPI_Busy;
    }

    /* Check if the input arguments valid */
    if (((xfer->txData == NULL) && (xfer->rxData == NULL)) || (xfer->dataSize == 0U))
    {
        return kStatus_InvalidArgument;
    }
    ECSPI_Enable(base, true);
    handle->state = (uint32_t)kECSPI_Busy;

    ECSPI_SetChannelSelect(base, xfer->channel);

#if defined(FSL_FEATURE_SOC_SPBA_COUNT) && (FSL_FEATURE_SOC_SPBA_COUNT > 0)
    bool isSpba = SDMA_IsPeripheralInSPBA((uint32_t)base);
    /* Judge if the instance is located in SPBA */
    if (isSpba)
    {
        perType = kSDMA_PeripheralNormal_SP;
    }
#endif /* FSL_FEATURE_SOC_SPBA_COUNT */

    /* Prepare transfer. */
    SDMA_PrepareTransfer(&xferConfig, (uint32_t) & (base->RXDATA), (uint32_t)xfer->rxData, sizeof(uint8_t),
                         sizeof(uint8_t), sizeof(uint8_t), xfer->dataSize, handle->rxSdmaHandle->eventSource, perType,
                         kSDMA_PeripheralToMemory);
    /* Submit transfer. */
    SDMA_SubmitTransfer(handle->rxSdmaHandle, &xferConfig);

    /* Prepare transfer. */
    SDMA_PrepareTransfer(&xferConfig, (uint32_t)xfer->txData, (uint32_t) & (base->TXDATA), sizeof(uint8_t),
                         sizeof(uint8_t), sizeof(uint8_t), xfer->dataSize, handle->txSdmaHandle->eventSource, perType,
                         kSDMA_MemoryToPeripheral);

    /* Submit transfer. */
    SDMA_SubmitTransfer(handle->txSdmaHandle, &xferConfig);
    /* start Tx transfer */
    handle->txInProgress = true;
    ECSPI_EnableDMA(base, kECSPI_TxDmaEnable, true);
    SDMA_StartTransfer(handle->txSdmaHandle);

    /* start Rx transfer */
    handle->rxInProgress = true;
    ECSPI_EnableDMA(base, kECSPI_RxDmaEnable, true);
    SDMA_StartTransfer(handle->rxSdmaHandle);

    return kStatus_Success;
}
