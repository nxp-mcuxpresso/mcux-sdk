/*
 * Copyright 2021, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_LCDIC_DMA_H_
#define FSL_LCDIC_DMA_H_

#include "fsl_lcdic.h"
#include "fsl_dma.h"

/*!
 * @addtogroup lcdic_dma
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
#define FSL_LCDIC_DMA_DRIVER_VERSION (MAKE_VERSION(2, 1, 0))
/*! @} */

/* Forward declaration of the handle typedef. */
typedef struct _lcdic_dma_handle lcdic_dma_handle_t;

/*! @brief LCDIC DMA callback called at the end of transfer. */
typedef void (*lcdic_dma_callback_t)(LCDIC_Type *base, lcdic_dma_handle_t *handle, status_t status, void *userData);

/*! @brief LCDIC DMA transfer handle, users should not touch the content of the handle.*/
struct _lcdic_dma_handle
{
    LCDIC_Type *lcdic;
    volatile bool xferInProgress;  /*!< Transfer in progress */
    lcdic_xfer_mode_t xferMode;    /*!< On-going transfer mode. */
    dma_handle_t *txDmaHandle;     /*!< DMA handler for send */
    dma_handle_t *rxDmaHandle;     /*!< DMA handler for receive */
    lcdic_dma_callback_t callback; /*!< Callback when transfer finished. */
    void *userData;                /*!< User Data for callback */
    union
    {
        const uint8_t *txData; /*!< Pointer to the TX data. */
        uint8_t *rxData;       /*!< Pointer to the RX data. */
    };
    uint32_t xferSizeWordAligned;  /*!< 4-byte size aligned part or the transfer data size. */
    uint8_t xferSizeWordUnaligned; /*!< 4-byte size unaligned part of the transfer data size. */
    uint8_t rxSizeWordUnaligned;   /*!< Same as xferSizeWordUnaligned, it is only used for RX. */
    uint32_t tmpData;              /*!< To save temporary data during transfer. */
    dma_descriptor_t *dmaDesc;     /*!< Pointer to two DMA descriptor, should be 16-byte aligned. */
};

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name DMA Transactional
 * @{
 */

/*!
 * @brief Initialize the LCDIC DMA handle.
 *
 * This function initializes the LCDIC DMA handle which can be used for other LCDIC transactional APIs.
 * Usually, for a specified LCDIC instance, user need only call this API once to get the initialized handle.
 *
 * @param base LCDIC peripheral base address.
 * @param handle LCDIC handle pointer.
 * @param callback User callback function called at the end of a transfer.
 * @param userData User data for callback.
 * @param txDmaHandle DMA handle pointer for LCDIC Tx, the handle shall be static allocated by users.
 * @param rxDmaHandle DMA handle pointer for LCDIC Rx, the handle shall be static allocated by users.
 * @param dmaDesc User allocated dma descriptor, it should be in non-cacheable region and 16-byte aligned.
 */
status_t LCDIC_TransferCreateHandleDMA(LCDIC_Type *base,
                                       lcdic_dma_handle_t *handle,
                                       lcdic_dma_callback_t callback,
                                       void *userData,
                                       dma_handle_t *txDmaHandle,
                                       dma_handle_t *rxDmaHandle,
                                       dma_descriptor_t dmaDesc[2]);

/*!
 * @brief Perform a non-blocking LCDIC transfer using DMA.
 *
 * This function returned immediately after transfer initiates, monitor the transfer
 * done by callback.
 *
 * @param base LCDIC peripheral base address.
 * @param handle LCDIC DMA handle pointer.
 * @param xfer Pointer to dma transfer structure.
 * @retval kStatus_Success Successfully start a transfer.
 * @retval kStatus_InvalidArgument Input argument is invalid.
 * @retval kStatus_Busy LCDIC is not idle, is running another transfer.
 */
status_t LCDIC_TransferDMA(LCDIC_Type *base, lcdic_dma_handle_t *handle, const lcdic_xfer_t *xfer);

/*!
 * @brief Send data array using DMA.
 *
 * @param base LCDIC peripheral base address.
 * @param handle Pointer to the lcdic_handle_t structure to store the transfer state.
 * @param xfer LCDIC transfer structure.
 * @retval kStatus_Success Successfully start a transfer.
 * @retval kStatus_InvalidArgument Input argument is invalid.
 * @retval kStatus_Busy LCDIC driver is busy with another transfer.
 */
status_t LCDIC_SendDataArrayDMA(LCDIC_Type *base, lcdic_dma_handle_t *handle, const lcdic_tx_xfer_t *xfer);

/*!
 * @brief Read data array using DMA.
 *
 * @param base LCDIC peripheral base address.
 * @param handle Pointer to the lcdic_handle_t structure to store the transfer state.
 * @param xfer LCDIC transfer structure.
 * @retval kStatus_Success Successfully start a transfer.
 * @retval kStatus_InvalidArgument Input argument is invalid.
 * @retval kStatus_Busy LCDIC driver is busy with another transfer.
 */
status_t LCDIC_ReadDataArrayDMA(LCDIC_Type *base, lcdic_dma_handle_t *handle, const lcdic_rx_xfer_t *xfer);

/*!
 * @brief LCDIC IRQ handler function work with DMA transactional APIs.
 *
 * IRQ handler to work with @ref LCDIC_TransferDMA.
 *
 * @param base LCDIC peripheral base address.
 * @param handle Pointer to the lcdic_dma_handle_t structure to store the transfer state.
 */
void LCDIC_TransferHandleIRQDMA(LCDIC_Type *base, void *handle);

/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* FSL_LCDIC_DMA_H_ */
