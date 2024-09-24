/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_XSPI_EDMA_H_
#define FSL_XSPI_EDMA_H_

#include "fsl_xspi.h"
#include "fsl_edma.h"

/*!
 * @addtogroup xspi_edma
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief XSPI EDMA driver version 2.0.2. */
#define FSL_XSPI_EDMA_DRIVER_VERSION (MAKE_VERSION(2, 0, 2))
/*@}*/

typedef struct _xspi_edma_handle xspi_edma_handle_t;

/*! @brief XSPI eDMA transfer callback function for finish and error */
typedef void (*xspi_edma_callback_t)(XSPI_Type *base, xspi_edma_handle_t *handle, status_t status, void *userData);

/*! @brief eDMA transfer configuration */
typedef enum _xspi_edma_ntransfer_size
{
    kXSPI_EDMAnSize1Bytes  = 0x1U,  /*!< Source/Destination data transfer size is 1 byte every time */
    kXSPI_EDMAnSize2Bytes  = 0x2U,  /*!< Source/Destination data transfer size is 2 bytes every time */
    kXSPI_EDMAnSize4Bytes  = 0x4U,  /*!< Source/Destination data transfer size is 4 bytes every time */
    kXSPI_EDMAnSize8Bytes  = 0x8U,  /*!< Source/Destination data transfer size is 8 bytes every time */
    kXSPI_EDMAnSize32Bytes = 0x20U, /*!< Source/Destination data transfer size is 32 bytes every time */
} xspi_edma_transfer_nsize_t;

/*! @brief XSPI DMA transfer handle, users should not touch the content of the handle.*/
struct _xspi_edma_handle
{
    edma_handle_t *txDmaHandle;              /*!< eDMA handler for XSPI Tx. */
    edma_handle_t *rxDmaHandle;              /*!< eDMA handler for XSPI Rx. */
    size_t transferSize;                     /*!< Bytes need to transfer. */
    xspi_edma_transfer_nsize_t nsize;        /*!< eDMA SSIZE/DSIZE in each transfer. */
    uint32_t nbytes;                         /*!< eDMA minor byte transfer count initially configured. */
    uint8_t count;                           /*!< The transfer data count in a DMA request. */
    uint32_t state;                          /*!< Internal state for XSPI eDMA transfer. */
    xspi_edma_callback_t completionCallback; /*!< A callback function called after the eDMA transfer is finished. */
    void *userData;                          /*!< User callback parameter */
};

/*******************************************************************************
 * APIs
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name XSPI eDMA Transactional
 * @{
 */

/*!
 * @brief Initializes the XSPI handle for transfer which is used in transactional functions and set the callback.
 *
 * @param base XSPI peripheral base address
 * @param handle Pointer to xspi_edma_handle_t structure
 * @param callback XSPI callback, NULL means no callback.
 * @param userData User callback function data.
 * @param txDmaHandle User requested DMA handle for TX DMA transfer.
 * @param rxDmaHandle User requested DMA handle for RX DMA transfer.
 */
void XSPI_TransferCreateHandleEDMA(XSPI_Type *base,
                                   xspi_edma_handle_t *handle,
                                   xspi_edma_callback_t callback,
                                   void *userData,
                                   edma_handle_t *txDmaHandle,
                                   edma_handle_t *rxDmaHandle);

/*!
 * @brief Update XSPI EDMA transfer source data transfer size(SSIZE) and destination data transfer size(DSIZE).
 *
 * @param base XSPI peripheral base address
 * @param handle Pointer to xspi_edma_handle_t structure
 * @param nsize XSPI DMA transfer data transfer size(SSIZE/DSIZE), by default the size is
 * kFLEXPSI_EDMAnSize1Bytes(one byte).
 * @see xspi_edma_transfer_nsize_t               .
 */
void XSPI_TransferUpdateSizeEDMA(XSPI_Type *base, xspi_edma_handle_t *handle, xspi_edma_transfer_nsize_t nsize);

/*!
 * @brief Transfers XSPI data using an eDMA non-blocking method.
 *
 * This function writes/receives data to/from the XSPI transmit/receive FIFO. This function is non-blocking.
 * @param base XSPI peripheral base address.
 * @param handle Pointer to xspi_edma_handle_t structure
 * @param xfer XSPI transfer structure.
 * @retval kStatus_XSPI_Busy     XSPI is busy transfer.
 * @retval kStatus_InvalidArgument  The watermark configuration is invalid, the watermark should be power of
                                    2 to do successfully EDMA transfer.
 * @retval kStatus_Success          XSPI successfully start edma transfer.
 */
status_t XSPI_TransferEDMA(XSPI_Type *base, xspi_edma_handle_t *handle, xspi_transfer_t *xfer);

/*!
 * @brief Aborts the transfer data using eDMA.
 *
 * This function aborts the transfer data using eDMA.
 *
 * @param base XSPI peripheral base address.
 * @param handle Pointer to xspi_edma_handle_t structure
 */
void XSPI_TransferAbortEDMA(XSPI_Type *base, xspi_edma_handle_t *handle);

/*!
 * @brief Gets the transferred counts of transfer.
 *
 * @param base XSPI peripheral base address.
 * @param handle Pointer to xspi_edma_handle_t structure.
 * @param count Bytes transfer.
 * @retval kStatus_Success Succeed get the transfer count.
 * @retval kStatus_NoTransferInProgress There is not a non-blocking transaction currently in progress.
 */
status_t XSPI_TransferGetTransferCountEDMA(XSPI_Type *base, xspi_edma_handle_t *handle, size_t *count);

/* @} */

#if defined(__cplusplus)
}
#endif

/* @} */

#endif /* FSL_XSPI_EDMA_H_ */
