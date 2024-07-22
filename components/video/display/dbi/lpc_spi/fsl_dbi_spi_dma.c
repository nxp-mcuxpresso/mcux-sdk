/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dbi.h"
#include "fsl_dbi_spi_dma.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief SPI DBI bus transfer complete callback function.
 */
static void DBI_SPI_DMA_TransferCompletedCallback(SPI_Type *base,
                                                  spi_dma_handle_t *handle,
                                                  status_t status,
                                                  void *userData);

/*******************************************************************************
 * Variables
 ******************************************************************************/
const dbi_iface_xfer_ops_t g_dbiIfaceSpiDmaXferOps = {
    .writeCommandData = DBI_SPI_DMA_WriteCommandData,
#if MCUX_DBI_IFACE_ENABLE_READ
    .readData = DBI_SPI_DMA_ReadData,
#endif /* MCUX_DBI_IFACE_ENABLE_READ */
    .writeMemory = DBI_SPI_DMA_WriteMemory,
};

/*******************************************************************************
 * Code
 ******************************************************************************/
static void DBI_SPI_DMA_TransferCompletedCallback(SPI_Type *base,
                                                  spi_dma_handle_t *handle,
                                                  status_t status,
                                                  void *userData)
{
    dbi_iface_t *dbiIface           = (dbi_iface_t *)userData;
    dbi_spi_dma_prv_data_t *prvData = (dbi_spi_dma_prv_data_t *)dbiIface->prvData;

    /* There is left data to send */
    if (prvData->leftTxDataLen > 0)
    {
        spi_transfer_t xfer = {0};

        spi_dma_handle_t *spiHandle = &prvData->spiHandle;
        SPI_Type *spi               = prvData->spi;

        xfer.txData      = prvData->txData;
        xfer.rxData      = NULL;
        xfer.configFlags = 0U;
        xfer.dataSize    = MIN(prvData->leftTxDataLen, DMA_MAX_TRANSFER_COUNT);

        /*
         * LPC SPI DMA can only send at most DMA_MAX_TRANSFER_COUNT one time, so
         * need to call SPI_MasterTransferDMA multiple times.
         */
        prvData->leftTxDataLen -= xfer.dataSize;
        prvData->txData += xfer.dataSize;

        SPI_MasterTransferDMA(spi, spiHandle, &xfer);
    }
    else
    {
        dbiIface->memDoneCallback(status, dbiIface->memDoneCallbackParam);
    }
}

status_t DBI_SPI_DMA_CreateHandle(dbi_iface_t *dbiIface,
                                  const dbi_spi_dma_config_t *config,
                                  dbi_spi_dma_prv_data_t *prvData)
{
    (void)memset(dbiIface, 0, sizeof(dbi_iface_t));

    dbiIface->xferOps        = &g_dbiIfaceSpiDmaXferOps;
    dbiIface->prvData        = prvData;
    prvData->dcPinFunc       = config->dcPinFunc;
    prvData->spi             = config->spi;
    prvData->spiDriverConfig = SPI_GetConfig(prvData->spi);
    prvData->dataWidth       = config->dataWidth;

    return SPI_MasterTransferCreateHandleDMA(config->spi, &prvData->spiHandle, DBI_SPI_DMA_TransferCompletedCallback,
                                             dbiIface, config->txDmaHandle, config->rxDmaHandle);
}

status_t DBI_SPI_DMA_WriteCommandData(dbi_iface_t *dbiIface, uint8_t command, const void *data, uint32_t len_byte)
{
    status_t status;
    spi_transfer_t xfer = {0};
    uint8_t cmd         = command;

    dbi_spi_dma_prv_data_t *prvData = (dbi_spi_dma_prv_data_t *)dbiIface->prvData;

    dbi_dc_pin_func_t dcPinFunc = prvData->dcPinFunc;
    SPI_Type *spi               = prvData->spi;

    /* command */
    dcPinFunc(0);
    xfer.txData      = (const uint8_t *)&cmd;
    xfer.rxData      = NULL;
    xfer.configFlags = kSPI_FrameAssert;
    xfer.dataSize    = 1;

    prvData->spiDriverConfig->dataWidth = kSPI_Data8Bits;
    status                              = SPI_MasterTransferBlocking(spi, &xfer);
    if (status != kStatus_Success)
    {
        return status;
    }

    if (len_byte > 0)
    {
        /* Data */
        dcPinFunc(1);
        xfer.txData      = (const uint8_t *)data;
        xfer.rxData      = NULL;
        xfer.configFlags = 0U;
        xfer.dataSize    = len_byte;

        status = SPI_MasterTransferBlocking(spi, &xfer);
    }

    return status;
}

#if MCUX_DBI_IFACE_ENABLE_READ
status_t DBI_SPI_DMA_ReadData(dbi_iface_t *dbiIface, uint8_t command, void *data, uint32_t len_byte)
{
    status_t status;
    spi_transfer_t xfer = {0};
    uint8_t cmd         = command;

    dbi_spi_dma_prv_data_t *prvData = (dbi_spi_dma_prv_data_t *)dbiIface->prvData;

    dbi_dc_pin_func_t dcPinFunc = prvData->dcPinFunc;
    SPI_Type *spi               = prvData->spi;

    /* command */
    dcPinFunc(0);
    xfer.txData      = (const uint8_t *)&cmd;
    xfer.rxData      = NULL;
    xfer.configFlags = kSPI_FrameAssert;
    xfer.dataSize    = 1;

    prvData->spiDriverConfig->dataWidth = kSPI_Data8Bits;
    status                              = SPI_MasterTransferBlocking(spi, &xfer);
    if (status != kStatus_Success)
    {
        return status;
    }

    /* Data */
    dcPinFunc(1);
    xfer.txData      = NULL;
    xfer.rxData      = data;
    xfer.configFlags = 0U;
    xfer.dataSize    = len_byte;

    prvData->spiDriverConfig->dataWidth = prvData->dataWidth;
    status                              = SPI_MasterTransferBlocking(spi, &xfer);

    return status;
}
#endif /* MCUX_DBI_IFACE_ENABLE_READ */

status_t DBI_SPI_DMA_WriteMemory(dbi_iface_t *dbiIface, uint8_t command, const void *data, uint32_t len_byte)
{
    status_t status;
    spi_transfer_t xfer = {0};
    uint8_t cmd         = command;

    dbi_spi_dma_prv_data_t *prvData = (dbi_spi_dma_prv_data_t *)dbiIface->prvData;

    spi_dma_handle_t *spiHandle = &prvData->spiHandle;
    dbi_dc_pin_func_t dcPinFunc = prvData->dcPinFunc;
    SPI_Type *spi               = prvData->spi;

    /* command */
    dcPinFunc(0);
    xfer.txData      = (const uint8_t *)&cmd;
    xfer.rxData      = NULL;
    xfer.configFlags = kSPI_FrameAssert;
    xfer.dataSize    = 1;

    prvData->spiDriverConfig->dataWidth = kSPI_Data8Bits;
    status                              = SPI_MasterTransferBlocking(spi, &xfer);
    if (status != kStatus_Success)
    {
        return status;
    }
    /* Workaround, flush the TX FIFO. */
    spi->FIFOCFG &= ~SPI_FIFOCFG_ENABLETX_MASK;

    /* Data */
    dcPinFunc(1);
    xfer.txData      = (const uint8_t *)data;
    xfer.rxData      = NULL;
    xfer.configFlags = 0U;
    xfer.dataSize    = MIN(len_byte, DMA_MAX_TRANSFER_COUNT);

    /*
     * LPC SPI DMA can only send at most DMA_MAX_TRANSFER_COUNT one time, so
     * need to call SPI_MasterTransferDMA multiple times.
     */
    prvData->leftTxDataLen = len_byte - xfer.dataSize;
    prvData->txData        = (const uint8_t *)data + xfer.dataSize;

    spi->FIFOCFG |= SPI_FIFOCFG_ENABLETX_MASK;

    prvData->spiDriverConfig->dataWidth = prvData->dataWidth;
    status                              = SPI_MasterTransferDMA(spi, spiHandle, &xfer);

    return status;
}
