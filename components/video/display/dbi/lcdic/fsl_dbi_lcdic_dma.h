/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_DBI_LCDIC_DMA_H_
#define FSL_DBI_LCDIC_DMA_H_

#include "fsl_dbi.h"
#include "fsl_lcdic_dma.h"

/*
 * Change log:
 *
 *   1.0.0
 *     - Initial version
 */

/*!
 * @addtogroup dbi_lcdic_dma
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief LCDIC DBI interface transfer operation. */
extern const dbi_iface_xfer_ops_t g_dbiIfaceLcdicDmaXferOps;

typedef struct _dbi_lcdic_dma_prv_data
{
    lcdic_dma_handle_t lcdicHandle;    /*!< LCDIC DMA transfer handle. */
    volatile bool largeDataInProgress; /*!< Processing large data. */
    const uint8_t *txData;             /*!< Left data to send. */
    uint32_t dataLen;                  /*!< Left length to send. */
    uint8_t dataFormat;                /*!< Data format in video memory writing, see _lcdic_data_format. */
    uint8_t teSyncMode;                /*!< TE sync mode used in memory writing, see _lcdic_te_sync_mode. */
} dbi_lcdic_dma_prv_data_t;

typedef struct _dbi_lcdic_dma_config
{
    LCDIC_Type *lcdic;
    dma_handle_t *txDmaHandle;
    dma_descriptor_t (*dmaDesc)[2];
    uint8_t dataFormat; /*!< Data format in video memory writing, see _lcdic_data_format. */
    uint8_t teSyncMode; /*!< TE sync mode used in memory writing, see _lcdic_te_sync_mode. */
} dbi_lcdic_dma_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Create LCDIC DBI transfer handle.
 *
 * @param[out] dbiIface Pointer to the DBI interface.
 * @param[in] prvData Private data for DBI_LCDIC_DMA driver, uppwer layer only
 * need to pass in it, DBI_LCDIC_DMA driver will initialize it.
 * @param[in] config Configuration for the driver.
 * @return Return true if success, otherwise return error code.
 */
status_t DBI_LCDIC_DMA_CreateHandle(dbi_iface_t *dbiIface,
                                    const dbi_lcdic_dma_config_t *config,
                                    dbi_lcdic_dma_prv_data_t *prvData);

status_t DBI_LCDIC_DMA_WriteCommandData(dbi_iface_t *dbiIface, uint8_t command, const void *data, uint32_t len_byte);

#if MCUX_DBI_IFACE_ENABLE_READ
status_t DBI_LCDIC_DMA_ReadData(dbi_iface_t *dbiIface, uint8_t command, void *data, uint32_t len_byte);
#endif /* MCUX_DBI_IFACE_ENABLE_READ */

status_t DBI_LCDIC_DMA_WriteMemory(dbi_iface_t *dbiIface, uint8_t command, const void *data, uint32_t len_byte);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* FSL_DBI_LCDIC_DMA_H_ */
