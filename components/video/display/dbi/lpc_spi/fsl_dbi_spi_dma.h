/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_DBI_SPI_DMA_H_
#define FSL_DBI_SPI_DMA_H_

#include "fsl_dbi.h"
#include "fsl_spi_dma.h"

/*
 * Change log:
 *
 *   1.0.0
 *     - Initial version
 */

/*!
 * @addtogroup dbi_spi_dma
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief SPI DBI interface transfer operation. */
extern const dbi_iface_xfer_ops_t g_dbiIfaceSpiDmaXferOps;

typedef struct _dbi_spi_dma_prv_data
{
    SPI_Type *spi;                 /*!< Pointer to SPI peripheral. */
    spi_dma_handle_t spiHandle;    /*!< SPI DMA transfer handle. */
    dbi_dc_pin_func_t dcPinFunc;   /*!< Function to toggle DC pin. */
    const uint8_t *txData;         /*!< Pointer to the data to send. */
    uint32_t leftTxDataLen;        /*!< Left data length to send. */
    spi_config_t *spiDriverConfig; /*!< Driver configuration. */
    spi_data_width_t dataWidth;    /*!< Data width used in memory writing. */
} dbi_spi_dma_prv_data_t;

typedef struct _dbi_spi_dma_config
{
    SPI_Type *spi;
    dma_handle_t *txDmaHandle;
    dma_handle_t *rxDmaHandle;
    dbi_dc_pin_func_t dcPinFunc;
    spi_data_width_t dataWidth; /*!< Data width used in memory writing. */
} dbi_spi_dma_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Create SPI DBI transfer handle.
 *
 * @param[out] dbiIface Pointer to the DBI interface.
 * @param[in] spi Pointer to the SPI peripheral.
 * @param[in] txDmaHandle Pointer to the DMA TX transfer handle, used to write
 * data to the video memory.
 * @param[in] rxDmaHandle Pointer to the DMA RX transfer handle, needed by the
 * LPC SPI DMA driver.
 * @param[in] prvData Private data for DBI_SPI_DMA driver, uppwer layer only
 * need to pass in it, DBI_SPI_DMA driver will initialize it.
 * @return Return true if success, otherwise return error code.
 */
status_t DBI_SPI_DMA_CreateHandle(dbi_iface_t *dbiIface,
                                  const dbi_spi_dma_config_t *config,
                                  dbi_spi_dma_prv_data_t *prvData);

status_t DBI_SPI_DMA_WriteCommandData(dbi_iface_t *dbiIface, uint8_t command, const void *data, uint32_t len_byte);

#if MCUX_DBI_IFACE_ENABLE_READ
status_t DBI_SPI_DMA_ReadData(dbi_iface_t *dbiIface, uint8_t command, void *data, uint32_t len_byte);
#endif /* MCUX_DBI_IFACE_ENABLE_READ */

status_t DBI_SPI_DMA_WriteMemory(dbi_iface_t *dbiIface, uint8_t command, const void *data, uint32_t len_byte);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* FSL_DBI_SPI_DMA_H_ */
