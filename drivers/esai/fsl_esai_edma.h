/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_ESAI_EDMA_H_
#define _FSL_ESAI_EDMA_H_

#include "fsl_esai.h"
#include "fsl_edma.h"

/*!
 * @addtogroup esai_edma
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
#define FSL_ESAI_EDMA_DRIVER_VERSION (MAKE_VERSION(2, 1, 1)) /*!< Version 2.1.1 */
/*@}*/

typedef struct _esai_edma_handle esai_edma_handle_t;

/*! @brief ESAI eDMA transfer callback function for finish and error */
typedef void (*esai_edma_callback_t)(ESAI_Type *base, esai_edma_handle_t *handle, status_t status, void *userData);

/*! @brief ESAI DMA transfer handle, users should not touch the content of the handle.*/
struct _esai_edma_handle
{
    edma_handle_t *dmaHandle;                        /*!< DMA handler for ESAI send */
    uint8_t nbytes;                                  /*!< eDMA minor byte transfer count initially configured. */
    uint8_t bitWidth;                                /*!< Bit width for transfer, 8/16/24/32 bits */
    uint8_t slotLen;                                 /*!< Slot length of the audio data */
    uint8_t count;                                   /*!< The transfer data count in a DMA request */
    uint8_t sectionMap;                              /*!< Section enabled for transfer */
    uint32_t state;                                  /*!< Internal state for ESAI eDMA transfer */
    esai_edma_callback_t callback;                   /*!< Callback for users while transfer finish or error occurs */
    void *userData;                                  /*!< User callback parameter */
    edma_tcd_t tcd[ESAI_XFER_QUEUE_SIZE + 1U];       /*!< TCD pool for eDMA transfer. */
    esai_transfer_t esaiQueue[ESAI_XFER_QUEUE_SIZE]; /*!< Transfer queue storing queued transfer. */
    size_t transferSize[ESAI_XFER_QUEUE_SIZE];       /*!< Data bytes need to transfer */
    volatile uint8_t queueUser;                      /*!< Index for user to queue transfer. */
    volatile uint8_t queueDriver;                    /*!< Index for driver to get the transfer data and size */
};

/*******************************************************************************
 * APIs
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name eDMA Transactional
 * @{
 */

/*!
 * @brief Initializes the ESAI eDMA handle.
 *
 * This function initializes the ESAI master DMA handle, which can be used for other ESAI master transactional APIs.
 * Usually, for a specified ESAI instance, call this API once to get the initialized handle.
 *
 * @param base ESAI base pointer.
 * @param handle ESAI eDMA handle pointer.
 * @param base ESAI peripheral base address.
 * @param callback Pointer to user callback function.
 * @param userData User parameter passed to the callback function.
 * @param dmaHandle eDMA handle pointer, this handle shall be static allocated by users.
 */
void ESAI_TransferTxCreateHandleEDMA(ESAI_Type *base,
                                     esai_edma_handle_t *handle,
                                     esai_edma_callback_t callback,
                                     void *userData,
                                     edma_handle_t *dmaHandle);

/*!
 * @brief Initializes the ESAI Rx eDMA handle.
 *
 * This function initializes the ESAI slave DMA handle, which can be used for other ESAI master transactional APIs.
 * Usually, for a specified ESAI instance, call this API once to get the initialized handle.
 *
 * @param base ESAI base pointer.
 * @param handle ESAI eDMA handle pointer.
 * @param base ESAI peripheral base address.
 * @param callback Pointer to user callback function.
 * @param userData User parameter passed to the callback function.
 * @param dmaHandle eDMA handle pointer, this handle shall be static allocated by users.
 */
void ESAI_TransferRxCreateHandleEDMA(ESAI_Type *base,
                                     esai_edma_handle_t *handle,
                                     esai_edma_callback_t callback,
                                     void *userData,
                                     edma_handle_t *dmaHandle);

/*!
 * @brief Configures the ESAI Tx audio format.
 *
 * The audio format can be changed at run-time. This function configures the sample rate and audio data
 * format to be transferred. This function also sets the eDMA parameter according to formatting requirements.
 *
 * @param base ESAI base pointer.
 * @param handle ESAI eDMA handle pointer.
 * @param format Pointer to ESAI audio data format structure.
 * @param hckClockHz HCK clock frequency in Hz.
 * @param hclkSourceClockHz HCK clock source frequency in Hz.
 * @retval kStatus_Success Audio format set successfully.
 * @retval kStatus_InvalidArgument The input argument is invalid.
 */
void ESAI_TransferTxSetFormatEDMA(ESAI_Type *base,
                                  esai_edma_handle_t *handle,
                                  esai_format_t *format,
                                  uint32_t hckClockHz,
                                  uint32_t hclkSourceClockHz);

/*!
 * @brief Configures the ESAI Rx audio format.
 *
 * The audio format can be changed at run-time. This function configures the sample rate and audio data
 * format to be transferred. This function also sets the eDMA parameter according to formatting requirements.
 *
 * @param base ESAI base pointer.
 * @param handle ESAI eDMA handle pointer.
 * @param format Pointer to ESAI audio data format structure.
 * @param hckClockHz HCK clock frequency in Hz.
 * @param hclkSourceClockHz HCK clock source frequency in Hz.
 * @retval kStatus_Success Audio format set successfully.
 * @retval kStatus_InvalidArgument The input argument is invalid.
 */
void ESAI_TransferRxSetFormatEDMA(ESAI_Type *base,
                                  esai_edma_handle_t *handle,
                                  esai_format_t *format,
                                  uint32_t hckClockHz,
                                  uint32_t hclkSourceClockHz);

/*!
 * @brief Performs a non-blocking ESAI transfer using DMA.
 *
 * @note This interface returns immediately after the transfer initiates. Call
 * ESAI_GetTransferStatus to poll the transfer status and check whether the ESAI transfer is finished.
 *
 * @param base ESAI base pointer.
 * @param handle ESAI eDMA handle pointer.
 * @param xfer Pointer to the DMA transfer structure.
 * @retval kStatus_Success Start a ESAI eDMA send successfully.
 * @retval kStatus_InvalidArgument The input argument is invalid.
 * @retval kStatus_TxBusy ESAI is busy sending data.
 */
status_t ESAI_TransferSendEDMA(ESAI_Type *base, esai_edma_handle_t *handle, esai_transfer_t *xfer);

/*!
 * @brief Performs a non-blocking ESAI receive using eDMA.
 *
 * @note This interface returns immediately after the transfer initiates. Call
 * the ESAI_GetReceiveRemainingBytes to poll the transfer status and check whether the ESAI transfer is finished.
 *
 * @param base ESAI base pointer
 * @param handle ESAI eDMA handle pointer.
 * @param xfer Pointer to DMA transfer structure.
 * @retval kStatus_Success Start a ESAI eDMA receive successfully.
 * @retval kStatus_InvalidArgument The input argument is invalid.
 * @retval kStatus_RxBusy ESAI is busy receiving data.
 */
status_t ESAI_TransferReceiveEDMA(ESAI_Type *base, esai_edma_handle_t *handle, esai_transfer_t *xfer);

/*!
 * @brief Aborts a ESAI transfer using eDMA.
 *
 * @param base ESAI base pointer.
 * @param handle ESAI eDMA handle pointer.
 */
void ESAI_TransferAbortSendEDMA(ESAI_Type *base, esai_edma_handle_t *handle);

/*!
 * @brief Aborts a ESAI receive using eDMA.
 *
 * @param base ESAI base pointer
 * @param handle ESAI eDMA handle pointer.
 */
void ESAI_TransferAbortReceiveEDMA(ESAI_Type *base, esai_edma_handle_t *handle);

/*!
 * @brief Gets byte count sent by ESAI.
 *
 * @param base ESAI base pointer.
 * @param handle ESAI eDMA handle pointer.
 * @param count Bytes count sent by ESAI.
 * @retval kStatus_Success Succeed get the transfer count.
 * @retval kStatus_NoTransferInProgress There is no non-blocking transaction in progress.
 */
status_t ESAI_TransferGetSendCountEDMA(ESAI_Type *base, esai_edma_handle_t *handle, size_t *count);

/*!
 * @brief Gets byte count received by ESAI.
 *
 * @param base ESAI base pointer
 * @param handle ESAI eDMA handle pointer.
 * @param count Bytes count received by ESAI.
 * @retval kStatus_Success Succeed get the transfer count.
 * @retval kStatus_NoTransferInProgress There is no non-blocking transaction in progress.
 */
status_t ESAI_TransferGetReceiveCountEDMA(ESAI_Type *base, esai_edma_handle_t *handle, size_t *count);

/*! @} */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif
