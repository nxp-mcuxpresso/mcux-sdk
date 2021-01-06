/*
 * Copyright 2016-2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_SPI_DMA_H_
#define _FSL_SPI_DMA_H_

#include "fsl_ecspi.h"
#include "fsl_sdma.h"

/*!
 * @addtogroup ecspi_sdma
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @name Driver version */
/*@{*/
/*! @brief ECSPI FreeRTOS driver version. */
#define FSL_ECSPI_FREERTOS_DRIVER_VERSION (MAKE_VERSION(2, 2, 0))
/*@}*/

typedef struct _ecspi_sdma_handle ecspi_sdma_handle_t;

/*! @brief ECSPI SDMA callback called at the end of transfer. */
typedef void (*ecspi_sdma_callback_t)(ECSPI_Type *base, ecspi_sdma_handle_t *handle, status_t status, void *userData);

/*! @brief ECSPI SDMA transfer handle, users should not touch the content of the handle.*/
struct _ecspi_sdma_handle
{
    bool txInProgress;              /*!< Send transfer finished */
    bool rxInProgress;              /*!< Receive transfer finished */
    sdma_handle_t *txSdmaHandle;    /*!< DMA handler for ECSPI send */
    sdma_handle_t *rxSdmaHandle;    /*!< DMA handler for ECSPI receive */
    ecspi_sdma_callback_t callback; /*!< Callback for ECSPI SDMA transfer */
    void *userData;                 /*!< User Data for ECSPI SDMA callback */
    uint32_t state;                 /*!< Internal state of ECSPI SDMA transfer */
    uint32_t ChannelTx;             /*!< Channel for send handle */
    uint32_t ChannelRx;             /*!< Channel for receive handler */
};

/*******************************************************************************
 * APIs
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name DMA Transactional
 * @{
 */

/*!
 * @brief Initialize the ECSPI master SDMA handle.
 *
 * This function initializes the ECSPI master SDMA handle which can be used for other SPI master transactional APIs.
 * Usually, for a specified ECSPI instance, user need only call this API once to get the initialized handle.
 *
 * @param base ECSPI peripheral base address.
 * @param handle ECSPI handle pointer.
 * @param callback User callback function called at the end of a transfer.
 * @param userData User data for callback.
 * @param txHandle SDMA handle pointer for ECSPI Tx, the handle shall be static allocated by users.
 * @param rxHandle SDMA handle pointer for ECSPI Rx, the handle shall be static allocated by users.
 * @param eventSourceTx event source for ECSPI send, which can be found in SDMA mapping.
 * @param eventSourceRx event source for ECSPI receive, which can be found in SDMA mapping.
 * @param TxChannel SDMA channel for ECSPI send.
 * @param RxChannel SDMA channel for ECSPI receive.
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
                                          uint32_t RxChannel);

/*!
 * @brief Initialize the ECSPI Slave SDMA handle.
 *
 * This function initializes the ECSPI Slave SDMA handle which can be used for other SPI Slave transactional APIs.
 * Usually, for a specified ECSPI instance, user need only call this API once to get the initialized handle.
 *
 * @param base ECSPI peripheral base address.
 * @param handle ECSPI handle pointer.
 * @param callback User callback function called at the end of a transfer.
 * @param userData User data for callback.
 * @param txHandle SDMA handle pointer for ECSPI Tx, the handle shall be static allocated by users.
 * @param rxHandle SDMA handle pointer for ECSPI Rx, the handle shall be static allocated by users.
 * @param eventSourceTx event source for ECSPI send, which can be found in SDMA mapping.
 * @param eventSourceRx event source for ECSPI receive, which can be found in SDMA mapping.
 * @param TxChannel SDMA channel for ECSPI send.
 * @param RxChannel SDMA channel for ECSPI receive.
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
                                         uint32_t RxChannel);

/*!
 * @brief Perform a non-blocking ECSPI master transfer using SDMA.
 *
 * @note This interface returned immediately after transfer initiates.
 *
 * @param base ECSPI peripheral base address.
 * @param handle ECSPI SDMA handle pointer.
 * @param xfer Pointer to sdma transfer structure.
 * @retval kStatus_Success Successfully start a transfer.
 * @retval kStatus_InvalidArgument Input argument is invalid.
 * @retval kStatus_ECSPI_Busy EECSPI is not idle, is running another transfer.
 */
status_t ECSPI_MasterTransferSDMA(ECSPI_Type *base, ecspi_sdma_handle_t *handle, ecspi_transfer_t *xfer);

/*!
 * @brief Perform a non-blocking ECSPI slave transfer using SDMA.
 *
 * @note This interface returned immediately after transfer initiates.
 *
 * @param base ECSPI peripheral base address.
 * @param handle ECSPI SDMA handle pointer.
 * @param xfer Pointer to sdma transfer structure.
 * @retval kStatus_Success Successfully start a transfer.
 * @retval kStatus_InvalidArgument Input argument is invalid.
 * @retval kStatus_ECSPI_Busy EECSPI is not idle, is running another transfer.
 */
status_t ECSPI_SlaveTransferSDMA(ECSPI_Type *base, ecspi_sdma_handle_t *handle, ecspi_transfer_t *xfer);
/*!
 * @brief Abort a ECSPI master transfer using SDMA.
 *
 * @param base ECSPI peripheral base address.
 * @param handle ECSPI SDMA handle pointer.
 */
void ECSPI_MasterTransferAbortSDMA(ECSPI_Type *base, ecspi_sdma_handle_t *handle);
/*!
 * @brief Abort a ECSPI slave transfer using SDMA.
 *
 * @param base ECSPI peripheral base address.
 * @param handle ECSPI SDMA handle pointer.
 */
void ECSPI_SlaveTransferAbortSDMA(ECSPI_Type *base, ecspi_sdma_handle_t *handle);

/*! @} */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif
