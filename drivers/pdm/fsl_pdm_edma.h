/*
 * Copyright 2019 - 2020, NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_PDM_EDMA_H_
#define _FSL_PDM_EDMA_H_

#include "fsl_edma.h"
#include "fsl_pdm.h"

/*!
 * @addtogroup pdm_edma PDM EDMA Driver
 * @ingroup pdm
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
#define FSL_PDM_EDMA_DRIVER_VERSION (MAKE_VERSION(2, 5, 0)) /*!< Version 2.5.0 */
/*@}*/

/*! @brief PDM edma handler */
typedef struct _pdm_edma_handle pdm_edma_handle_t;

/*! @brief PDM edma transfer */
typedef struct _pdm_edma_transfer
{
    volatile uint8_t *data;                  /*!< Data start address to transfer. */
    volatile size_t dataSize;                /*!< Total Transfer bytes size. */
    struct _pdm_edma_transfer *linkTransfer; /*!< linked transfer configurations */
} pdm_edma_transfer_t;

/*! @brief PDM eDMA transfer callback function for finish and error */
typedef void (*pdm_edma_callback_t)(PDM_Type *base, pdm_edma_handle_t *handle, status_t status, void *userData);

/*! @brief PDM DMA transfer handle, users should not touch the content of the handle.*/
struct _pdm_edma_handle
{
    edma_handle_t *dmaHandle;     /*!< DMA handler for PDM send */
    uint8_t count;                /*!< The transfer data count in a DMA request */
    uint32_t receivedBytes;       /*!< total transfer count */
    uint32_t state;               /*!< Internal state for PDM eDMA transfer */
    pdm_edma_callback_t callback; /*!< Callback for users while transfer finish or error occurs */
    bool isLoopTransfer;          /*!< loop transfer */
    void *userData;               /*!< User callback parameter */
    edma_tcd_t *tcd;              /*!< TCD pool for eDMA transfer. */
    uint32_t tcdNum;              /*!< TCD number */
    uint32_t tcdUser;             /*!< Index for user to queue transfer. */
    uint32_t tcdDriver;           /*!< Index for driver to get the transfer data and size */
    volatile uint32_t tcdUsedNum; /*!< Index for user to queue transfer. */

    uint8_t endChannel;  /*!< The last enabled channel */
    uint8_t channelNums; /*!< total channel numbers */
};

/*******************************************************************************
 * APIs
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name PDM eDMA Transactional
 * @{
 */

/*!
 * @brief Install EDMA descriptor memory.
 *
 * @param handle Pointer to EDMA channel transfer handle.
 * @param tcdAddr EDMA head descriptor address.
 * @param tcdNum EDMA link descriptor address.
 */
void PDM_TransferInstallEDMATCDMemory(pdm_edma_handle_t *handle, void *tcdAddr, size_t tcdNum);

/*!
 * @brief Initializes the PDM Rx eDMA handle.
 *
 * This function initializes the PDM slave DMA handle, which can be used for other PDM master transactional APIs.
 * Usually, for a specified PDM instance, call this API once to get the initialized handle.
 *
 * @param base PDM base pointer.
 * @param handle PDM eDMA handle pointer.
 * @param base PDM peripheral base address.
 * @param callback Pointer to user callback function.
 * @param userData User parameter passed to the callback function.
 * @param dmaHandle eDMA handle pointer, this handle shall be static allocated by users.
 */
void PDM_TransferCreateHandleEDMA(
    PDM_Type *base, pdm_edma_handle_t *handle, pdm_edma_callback_t callback, void *userData, edma_handle_t *dmaHandle);

/*!
 * @brief Configures the PDM channel.
 *
 * @param base PDM base pointer.
 * @param handle PDM eDMA handle pointer.
 * @param channel channel index.
 * @param config pdm channel configurations.
 */
void PDM_TransferSetChannelConfigEDMA(PDM_Type *base,
                                      pdm_edma_handle_t *handle,
                                      uint32_t channel,
                                      const pdm_channel_config_t *config);

/*!
 * @brief Performs a non-blocking PDM receive using eDMA.
 *
 * @note This interface returns immediately after the transfer initiates. Call
 * the PDM_GetReceiveRemainingBytes to poll the transfer status and check whether the PDM transfer is finished.
 *
 * 1. Scatter gather case:
 * This functio support dynamic scatter gather and staic scatter gather,
 * a. for the dynamic scatter gather case:
 * Application should call PDM_TransferReceiveEDMA function continuously to make sure new receive request is submit
 *before the previous one finish. b. for the static scatter gather case: Application should use the link transfer
 *feature and make sure a loop link transfer is provided, such as:
 * @code
 * pdm_edma_transfer_t pdmXfer[2] =
 *   {
 *       {
 *       .data  = s_buffer,
 *       .dataSize = BUFFER_SIZE,
 *       .linkTransfer = &pdmXfer[1],
 *       },
 *
 *       {
 *       .data  = &s_buffer[BUFFER_SIZE],
 *       .dataSize = BUFFER_SIZE,
 *       .linkTransfer = &pdmXfer[0]
 *       },
 *   };
 *@endcode
 *
 * 2. Multi channel case:
 * This function support receive multi pdm channel data, for example, if two channel is requested,
 * @code
 * PDM_TransferSetChannelConfigEDMA(DEMO_PDM, &s_pdmRxHandle_0, DEMO_PDM_ENABLE_CHANNEL_0, &channelConfig);
 * PDM_TransferSetChannelConfigEDMA(DEMO_PDM, &s_pdmRxHandle_0, DEMO_PDM_ENABLE_CHANNEL_1, &channelConfig);
 * PDM_TransferReceiveEDMA(DEMO_PDM, &s_pdmRxHandle_0, pdmXfer);
 * @endcode
 *Then the output data will be formatted as:
 * -------------------------------------------------------------------------
 * |CHANNEL0 | CHANNEL1 | CHANNEL0 | CHANNEL1 | CHANNEL0 | CHANNEL 1 | ....|
 * -------------------------------------------------------------------------
 *
 * @param base PDM base pointer
 * @param handle PDM eDMA handle pointer.
 * @param xfer Pointer to DMA transfer structure.
 * @retval kStatus_Success Start a PDM eDMA receive successfully.
 * @retval kStatus_InvalidArgument The input argument is invalid.
 * @retval kStatus_RxBusy PDM is busy receiving data.
 */
status_t PDM_TransferReceiveEDMA(PDM_Type *base, pdm_edma_handle_t *handle, pdm_edma_transfer_t *xfer);

/*!
 * @brief Terminate all PDM receive.
 *
 * This function will clear all transfer slots buffered in the pdm queue. If users only want to abort the
 * current transfer slot, please call PDM_TransferAbortReceiveEDMA.
 *
 * @param base PDM base pointer.
 * @param handle PDM eDMA handle pointer.
 */
void PDM_TransferTerminateReceiveEDMA(PDM_Type *base, pdm_edma_handle_t *handle);

/*!
 * @brief Aborts a PDM receive using eDMA.
 *
 * This function only aborts the current transfer slots, the other transfer slots' information still kept
 * in the handler. If users want to terminate all transfer slots, just call PDM_TransferTerminateReceiveEDMA.
 *
 * @param base PDM base pointer
 * @param handle PDM eDMA handle pointer.
 */
void PDM_TransferAbortReceiveEDMA(PDM_Type *base, pdm_edma_handle_t *handle);

/*!
 * @brief Gets byte count received by PDM.
 *
 * @param base PDM base pointer
 * @param handle PDM eDMA handle pointer.
 * @param count Bytes count received by PDM.
 * @retval kStatus_Success Succeed get the transfer count.
 * @retval kStatus_NoTransferInProgress There is no non-blocking transaction in progress.
 */
status_t PDM_TransferGetReceiveCountEDMA(PDM_Type *base, pdm_edma_handle_t *handle, size_t *count);

/*! @} */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif
