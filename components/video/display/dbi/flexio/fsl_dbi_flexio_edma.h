/*
 * Copyright 2019-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_DBI_FLEXIO_EDMA_H_
#define _FSL_DBI_FLEXIO_EDMA_H_

#include "fsl_dbi.h"
#include "fsl_flexio_mculcd.h"
#include "fsl_flexio_mculcd_edma.h"

/*
 * Change log:
 *
 *   1.0.1
 *     - Fix MISRA-C 2012 issues.
 *
 *   1.0.0
 *     - Initial version
 */

/*!
 * @addtogroup dbi_flexio_edma
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief FLEXIO DBI interface (MCU LCD) transfer operation. */
typedef struct _dbi_flexio_edma_xfer_handle
{
    dbi_xfer_ops_t *xferOps;                  /*!< Transfer operations. */
    flexio_mculcd_edma_handle_t flexioHandle; /*!< FLEXIO DMA transfer handle. */
    dbi_mem_done_callback_t memDoneCallback;  /*!< The callback function when video memory access done. */
    void *userData;                           /*!< Parameter of @ref memDoneCallback */
} dbi_flexio_edma_xfer_handle_t;

/*! @brief FLEXIO DBI interface (MCU LCD) transfer operation. */
extern const dbi_xfer_ops_t g_dbiFlexioEdmaXferOps;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Create FLEXIO DBI transfer handle.
 *
 * @param[out] dbiXferHandle Pointer the handle that will be created.
 * @param[in] flexioLCD Pointer FLEXIO LCD structure.
 * @param[in] txDmaHandle Pointer to the DMA TX transfer handle, if you don't
 * want to use the function @ref DBI_FLEXIO_EDMA_WriteMemory, this could be NULL.
 * When this is NULL, the blocking method will be used instead of DMA method.
 * @param[in] txDmaHandle Pointer to the DMA RX transfer handle, if you don't
 * want to use the function @ref DBI_FLEXIO_EDMA_ReadMemory, this could be NULL.
 * When this is NULL, the blocking method will be used instead of DMA method.
 * @return Return true if success, otherwise return error code.
 */
status_t DBI_FLEXIO_EDMA_CreateXferHandle(dbi_flexio_edma_xfer_handle_t *dbiXferHandle,
                                          FLEXIO_MCULCD_Type *flexioLCD,
                                          edma_handle_t *txDmaHandle,
                                          edma_handle_t *rxDmaHandle);

/*!
 * @brief Write command through DBI.
 *
 * @param[in] dbiXferHandle Pointer the handle that created by @ref DBI_FLEXIO_EDMA_CreateXferHandle.
 * @param[in] command The command to send.
 * @return Return true if success, otherwise return error code.
 */
status_t DBI_FLEXIO_EDMA_WriteCommand(void *dbiXferHandle, uint32_t command);

/*!
 * @brief Write data through DBI.
 *
 * @param[in] dbiXferHandle Pointer the handle that created by @ref DBI_FLEXIO_EDMA_CreateXferHandle.
 * @param[in] data The data to send.
 * @param[in] len_byte The length of the data in bytes.
 * @return Return true if success, otherwise return error code.
 */
status_t DBI_FLEXIO_EDMA_WriteData(void *dbiXferHandle, void *data, uint32_t len_byte);

/*!
 * @brief Write data to the video memory through DBI.
 *
 * This function is faster than @ref DBI_FLEXIO_EDMA_WriteData because DMA is involved.
 *
 * @param[in] dbiXferHandle Pointer the handle that created by @ref DBI_FLEXIO_EDMA_CreateXferHandle.
 * @param[in] command The command sent before writing data.
 * @param[in] data The data to send.
 * @param[in] len_byte The length of the data in bytes.
 * @return Return true if success, otherwise return error code.
 */
status_t DBI_FLEXIO_EDMA_WriteMemory(void *dbiXferHandle, uint32_t command, const void *data, uint32_t len_byte);

/*!
 * @brief Read data from the video memory through DBI.
 *
 * @param[in] dbiXferHandle Pointer the handle that created by @ref DBI_FLEXIO_EDMA_CreateXferHandle.
 * @param[in] command The command sent before reading data.
 * @param[out] data The buffer to receive the data.
 * @param[in] len_byte The length of the data in bytes.
 * @return Return true if success, otherwise return error code.
 */
status_t DBI_FLEXIO_EDMA_ReadMemory(void *dbiXferHandle, uint32_t command, void *data, uint32_t len_byte);

/*!
 * @brief Register the callback function called when memory function done.
 *
 * The memory read and write functions are non-blocking function, when transaction
 * finished, callback is called to inform higher layer.
 *
 * @param[in] dbiXferHandle Pointer the handle that created by @ref DBI_FLEXIO_EDMA_CreateXferHandle.
 * @param[in] callback The callback when memory read or write finished.
 * @param[in] userData Parameter of the callback.
 */
void DBI_FLEXIO_EDMA_SetMemoryDoneCallback(void *dbiXferHandle, dbi_mem_done_callback_t callback, void *userData);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_DBI_FLEXIO_EDMA_H_ */
