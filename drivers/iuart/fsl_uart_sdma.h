/*
 * Copyright 2016-2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_UART_SDMA_H_
#define _FSL_UART_SDMA_H_

#include "fsl_uart.h"
#include "fsl_sdma.h"

/*!
 * @addtogroup uart_sdma
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief UART SDMA driver version 2.1.1. */
#define FSL_UART_SDMA_DRIVER_VERSION (MAKE_VERSION(2, 1, 1))
/*@}*/

/* Forward declaration of the handle typedef. */
typedef struct _uart_sdma_handle uart_sdma_handle_t;

/*! @brief UART transfer callback function. */
typedef void (*uart_sdma_transfer_callback_t)(UART_Type *base,
                                              uart_sdma_handle_t *handle,
                                              status_t status,
                                              void *userData);

/*!
 * @brief UART sDMA handle
 */
struct _uart_sdma_handle
{
    uart_sdma_transfer_callback_t callback; /*!< Callback function. */
    void *userData;                         /*!< UART callback function parameter.*/
    size_t rxDataSizeAll;                   /*!< Size of the data to receive. */
    size_t txDataSizeAll;                   /*!< Size of the data to send out. */
    sdma_handle_t *txSdmaHandle;            /*!< The sDMA TX channel used. */
    sdma_handle_t *rxSdmaHandle;            /*!< The sDMA RX channel used. */
    volatile uint8_t txState;               /*!< TX transfer state. */
    volatile uint8_t rxState;               /*!< RX transfer state */
};

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name sDMA transactional
 * @{
 */

/*!
 * @brief Initializes the UART handle which is used in transactional functions.
 * @param base UART peripheral base address.
 * @param handle Pointer to the uart_sdma_handle_t structure.
 * @param callback UART callback, NULL means no callback.
 * @param userData User callback function data.
 * @param rxSdmaHandle User-requested DMA handle for RX DMA transfer.
 * @param txSdmaHandle User-requested DMA handle for TX DMA transfer.
 * @param eventSourceTx Eventsource for TX DMA transfer.
 * @param eventSourceRx Eventsource for RX DMA transfer.
 */
void UART_TransferCreateHandleSDMA(UART_Type *base,
                                   uart_sdma_handle_t *handle,
                                   uart_sdma_transfer_callback_t callback,
                                   void *userData,
                                   sdma_handle_t *txSdmaHandle,
                                   sdma_handle_t *rxSdmaHandle,
                                   uint32_t eventSourceTx,
                                   uint32_t eventSourceRx);

/*!
 * @brief Sends data using sDMA.
 *
 * This function sends data using sDMA. This is a non-blocking function, which returns
 * right away. When all data is sent, the send callback function is called.
 *
 * @param base UART peripheral base address.
 * @param handle UART handle pointer.
 * @param xfer UART sDMA transfer structure. See #uart_transfer_t.
 * @retval kStatus_Success if succeeded; otherwise failed.
 * @retval kStatus_UART_TxBusy Previous transfer ongoing.
 * @retval kStatus_InvalidArgument Invalid argument.
 */
status_t UART_SendSDMA(UART_Type *base, uart_sdma_handle_t *handle, uart_transfer_t *xfer);

/*!
 * @brief Receives data using sDMA.
 *
 * This function receives data using sDMA. This is a non-blocking function, which returns
 * right away. When all data is received, the receive callback function is called.
 *
 * @param base UART peripheral base address.
 * @param handle Pointer to the uart_sdma_handle_t structure.
 * @param xfer UART sDMA transfer structure. See #uart_transfer_t.
 * @retval kStatus_Success if succeeded; otherwise failed.
 * @retval kStatus_UART_RxBusy Previous transfer ongoing.
 * @retval kStatus_InvalidArgument Invalid argument.
 */
status_t UART_ReceiveSDMA(UART_Type *base, uart_sdma_handle_t *handle, uart_transfer_t *xfer);

/*!
 * @brief Aborts the sent data using sDMA.
 *
 * This function aborts sent data using sDMA.
 *
 * @param base UART peripheral base address.
 * @param handle Pointer to the uart_sdma_handle_t structure.
 */
void UART_TransferAbortSendSDMA(UART_Type *base, uart_sdma_handle_t *handle);

/*!
 * @brief Aborts the receive data using sDMA.
 *
 * This function aborts receive data using sDMA.
 *
 * @param base UART peripheral base address.
 * @param handle Pointer to the uart_sdma_handle_t structure.
 */
void UART_TransferAbortReceiveSDMA(UART_Type *base, uart_sdma_handle_t *handle);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_UART_SDMA_H_ */
