/*
 * Copyright 2016-2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_uart_sdma.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.iuart_sdma"
#endif

/*<! Structure definition for uart_sdma_private_handle_t. The structure is private. */
typedef struct _uart_sdma_private_handle
{
    UART_Type *base;
    uart_sdma_handle_t *handle;
} uart_sdma_private_handle_t;

/* UART SDMA transfer handle. */
enum _uart_sdma_tansfer_states
{
    kUART_TxIdle, /* TX idle. */
    kUART_TxBusy, /* TX busy. */
    kUART_RxIdle, /* RX idle. */
    kUART_RxBusy  /* RX busy. */
};

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*<! Private handle only used for internally. */
static UART_Type *const s_uartSdmaBases[] = UART_BASE_PTRS;
static uart_sdma_private_handle_t s_sdmaPrivateHandle[ARRAY_SIZE(s_uartSdmaBases)];

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief UART SDMA send finished callback function.
 *
 * This function is called when UART SDMA send finished. It disables the UART
 * TX SDMA request and sends @ref kStatus_UART_TxIdle to UART callback.
 *
 * @param handle The SDMA handle.
 * @param param Callback function parameter.
 */
static void UART_SendSDMACallback(sdma_handle_t *handle, void *param, bool transferDone, uint32_t tcds);

/*!
 * @brief UART SDMA receive finished callback function.
 *
 * This function is called when UART SDMA receive finished. It disables the UART
 * RX SDMA request and sends @ref kStatus_UART_RxIdle to UART callback.
 *
 * @param handle The SDMA handle.
 * @param param Callback function parameter.
 */
static void UART_ReceiveSDMACallback(sdma_handle_t *handle, void *param, bool transferDone, uint32_t tcds);

/*******************************************************************************
 * Code
 ******************************************************************************/

static void UART_SendSDMACallback(sdma_handle_t *handle, void *param, bool transferDone, uint32_t tcds)
{
    assert(param != NULL);

    uart_sdma_private_handle_t *uartPrivateHandle = (uart_sdma_private_handle_t *)param;

    if (transferDone)
    {
        UART_TransferAbortSendSDMA(uartPrivateHandle->base, uartPrivateHandle->handle);

        /* Wait for transmission complete */
        while (0U == (uartPrivateHandle->base->USR2 & UART_USR2_TXDC_MASK))
        {
        }

        if (uartPrivateHandle->handle->callback != NULL)
        {
            uartPrivateHandle->handle->callback(uartPrivateHandle->base, uartPrivateHandle->handle, kStatus_UART_TxIdle,
                                                uartPrivateHandle->handle->userData);
        }
    }
}

static void UART_ReceiveSDMACallback(sdma_handle_t *handle, void *param, bool transferDone, uint32_t tcds)
{
    assert(param != NULL);

    uart_sdma_private_handle_t *uartPrivateHandle = (uart_sdma_private_handle_t *)param;

    if (transferDone)
    {
        /* Disable transfer. */
        UART_TransferAbortReceiveSDMA(uartPrivateHandle->base, uartPrivateHandle->handle);

        if (uartPrivateHandle->handle->callback != NULL)
        {
            uartPrivateHandle->handle->callback(uartPrivateHandle->base, uartPrivateHandle->handle, kStatus_UART_RxIdle,
                                                uartPrivateHandle->handle->userData);
        }
    }
}

/*!
 * brief Initializes the UART handle which is used in transactional functions.
 * param base UART peripheral base address.
 * param handle Pointer to the uart_sdma_handle_t structure.
 * param callback UART callback, NULL means no callback.
 * param userData User callback function data.
 * param rxSdmaHandle User-requested DMA handle for RX DMA transfer.
 * param txSdmaHandle User-requested DMA handle for TX DMA transfer.
 * param eventSourceTx Eventsource for TX DMA transfer.
 * param eventSourceRx Eventsource for RX DMA transfer.
 */
void UART_TransferCreateHandleSDMA(UART_Type *base,
                                   uart_sdma_handle_t *handle,
                                   uart_sdma_transfer_callback_t callback,
                                   void *userData,
                                   sdma_handle_t *txSdmaHandle,
                                   sdma_handle_t *rxSdmaHandle,
                                   uint32_t eventSourceTx,
                                   uint32_t eventSourceRx)
{
    assert(handle != NULL);

    uint32_t instance = UART_GetInstance(base);

    (void)memset(handle, 0, sizeof(*handle));

    handle->rxState = (uint8_t)kUART_RxIdle;
    handle->txState = (uint8_t)kUART_TxIdle;

    if (rxSdmaHandle != NULL)
    {
        rxSdmaHandle->eventSource = eventSourceRx;
    }

    if (txSdmaHandle != NULL)
    {
        txSdmaHandle->eventSource = eventSourceTx;
    }

    handle->rxSdmaHandle = rxSdmaHandle;
    handle->txSdmaHandle = txSdmaHandle;

    handle->callback = callback;
    handle->userData = userData;

    s_sdmaPrivateHandle[instance].base   = base;
    s_sdmaPrivateHandle[instance].handle = handle;

    /* Configure TX. */
    if (txSdmaHandle != NULL)
    {
        SDMA_SetCallback(handle->txSdmaHandle, UART_SendSDMACallback, &s_sdmaPrivateHandle[instance]);
    }

    /* Configure RX. */
    if (rxSdmaHandle != NULL)
    {
        SDMA_SetCallback(handle->rxSdmaHandle, UART_ReceiveSDMACallback, &s_sdmaPrivateHandle[instance]);
    }
}

/*!
 * brief Sends data using sDMA.
 *
 * This function sends data using sDMA. This is a non-blocking function, which returns
 * right away. When all data is sent, the send callback function is called.
 *
 * param base UART peripheral base address.
 * param handle UART handle pointer.
 * param xfer UART sDMA transfer structure. See #uart_transfer_t.
 * retval kStatus_Success if succeeded; otherwise failed.
 * retval kStatus_UART_TxBusy Previous transfer ongoing.
 * retval kStatus_InvalidArgument Invalid argument.
 */
status_t UART_SendSDMA(UART_Type *base, uart_sdma_handle_t *handle, uart_transfer_t *xfer)
{
    assert(handle != NULL);
    assert(handle->txSdmaHandle != NULL);
    assert(xfer != NULL);
    assert(xfer->data != NULL);
    assert(xfer->dataSize != 0U);

    sdma_transfer_config_t xferConfig = {0U};
    status_t status;
    sdma_peripheral_t perType = kSDMA_PeripheralTypeUART;

    /* If previous TX not finished. */
    if ((uint8_t)kUART_TxBusy == handle->txState)
    {
        status = kStatus_UART_TxBusy;
    }
    else
    {
        handle->txState       = (uint8_t)kUART_TxBusy;
        handle->txDataSizeAll = xfer->dataSize;

#if defined(FSL_FEATURE_SOC_SPBA_COUNT) && (FSL_FEATURE_SOC_SPBA_COUNT > 0)
        bool isSpba = SDMA_IsPeripheralInSPBA((uint32_t)base);
        /* Judge if the instance is located in SPBA */
        if (isSpba)
        {
            perType = kSDMA_PeripheralTypeUART_SP;
        }
#endif /* FSL_FEATURE_SOC_SPBA_COUNT */

        /* Prepare transfer. */
        SDMA_PrepareTransfer(&xferConfig, (uint32_t)xfer->data, (uint32_t) & (base->UTXD), sizeof(uint8_t),
                             sizeof(uint8_t), sizeof(uint8_t), (uint32_t)xfer->dataSize,
                             handle->txSdmaHandle->eventSource, perType, kSDMA_MemoryToPeripheral);

        /* Submit transfer. */
        SDMA_SubmitTransfer(handle->txSdmaHandle, &xferConfig);

        SDMA_StartTransfer(handle->txSdmaHandle);

        /* Enable UART TX SDMA. */
        UART_EnableTxDMA(base, true);
        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Receives data using sDMA.
 *
 * This function receives data using sDMA. This is a non-blocking function, which returns
 * right away. When all data is received, the receive callback function is called.
 *
 * param base UART peripheral base address.
 * param handle Pointer to the uart_sdma_handle_t structure.
 * param xfer UART sDMA transfer structure. See #uart_transfer_t.
 * retval kStatus_Success if succeeded; otherwise failed.
 * retval kStatus_UART_RxBusy Previous transfer ongoing.
 * retval kStatus_InvalidArgument Invalid argument.
 */
status_t UART_ReceiveSDMA(UART_Type *base, uart_sdma_handle_t *handle, uart_transfer_t *xfer)
{
    assert(handle != NULL);
    assert(handle->rxSdmaHandle != NULL);
    assert(xfer != NULL);
    assert(xfer->data != NULL);
    assert(xfer->dataSize != 0U);

    sdma_transfer_config_t xferConfig = {0U};
    status_t status;
    sdma_peripheral_t perType = kSDMA_PeripheralTypeUART;

    /* If previous RX not finished. */
    if ((uint8_t)kUART_RxBusy == handle->rxState)
    {
        status = kStatus_UART_RxBusy;
    }
    else
    {
        handle->rxState       = (uint8_t)kUART_RxBusy;
        handle->rxDataSizeAll = xfer->dataSize;

#if defined(FSL_FEATURE_SOC_SPBA_COUNT) && (FSL_FEATURE_SOC_SPBA_COUNT > 0)
        bool isSpba = SDMA_IsPeripheralInSPBA((uint32_t)base);
        /* Judge if the instance is located in SPBA */
        if (isSpba)
        {
            perType = kSDMA_PeripheralTypeUART_SP;
        }
#endif /* FSL_FEATURE_SOC_SPBA_COUNT */

        /* Prepare transfer. */
        SDMA_PrepareTransfer(&xferConfig, (uint32_t) & (base->URXD), (uint32_t)xfer->data, sizeof(uint8_t),
                             sizeof(uint8_t), sizeof(uint8_t), (uint32_t)xfer->dataSize,
                             handle->rxSdmaHandle->eventSource, perType, kSDMA_PeripheralToMemory);

        /* Submit transfer. */
        SDMA_SubmitTransfer(handle->rxSdmaHandle, &xferConfig);

        SDMA_StartTransfer(handle->rxSdmaHandle);

        /* Enable UART RX SDMA. */
        UART_EnableRxDMA(base, true);

        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Aborts the sent data using sDMA.
 *
 * This function aborts sent data using sDMA.
 *
 * param base UART peripheral base address.
 * param handle Pointer to the uart_sdma_handle_t structure.
 */
void UART_TransferAbortSendSDMA(UART_Type *base, uart_sdma_handle_t *handle)
{
    assert(handle != NULL);
    assert(handle->txSdmaHandle != NULL);

    /* Disable UART TX SDMA. */
    UART_EnableTxDMA(base, false);

    /* Stop transfer. */
    SDMA_AbortTransfer(handle->txSdmaHandle);

    handle->txState = (uint8_t)kUART_TxIdle;
}

/*!
 * brief Aborts the receive data using sDMA.
 *
 * This function aborts receive data using sDMA.
 *
 * param base UART peripheral base address.
 * param handle Pointer to the uart_sdma_handle_t structure.
 */
void UART_TransferAbortReceiveSDMA(UART_Type *base, uart_sdma_handle_t *handle)
{
    assert(handle != NULL);
    assert(handle->rxSdmaHandle != NULL);

    /* Disable UART RX SDMA. */
    UART_EnableRxDMA(base, false);

    /* Stop transfer. */
    SDMA_AbortTransfer(handle->rxSdmaHandle);

    handle->rxState = (uint8_t)kUART_RxIdle;
}
