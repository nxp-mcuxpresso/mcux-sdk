/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dbi.h"
#include "fsl_dbi_lcdic_dma.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief LCDIC DBI bus transfer complete callback function.
 */
static void DBI_LCDIC_DMA_TransferCompletedCallback(LCDIC_Type *base,
                                                    lcdic_dma_handle_t *handle,
                                                    status_t status,
                                                    void *userData);

/*******************************************************************************
 * Variables
 ******************************************************************************/
const dbi_iface_xfer_ops_t g_dbiIfaceLcdicDmaXferOps = {
    .writeCommandData = DBI_LCDIC_DMA_WriteCommandData,
#if MCUX_DBI_IFACE_ENABLE_READ
    .readData = DBI_LCDIC_DMA_ReadData,
#endif /* MCUX_DBI_IFACE_ENABLE_READ */
    .writeMemory = DBI_LCDIC_DMA_WriteMemory,
};

/*******************************************************************************
 * Code
 ******************************************************************************/
static void DBI_LCDIC_DMA_TransferCompletedCallback(LCDIC_Type *base,
                                                    lcdic_dma_handle_t *handle,
                                                    status_t status,
                                                    void *userData)
{
    lcdic_tx_xfer_t txXfer;
    dbi_iface_t *dbiIface             = (dbi_iface_t *)userData;
    dbi_lcdic_dma_prv_data_t *prvData = (dbi_lcdic_dma_prv_data_t *)(dbiIface->prvData);
    uint32_t curSendLen;

    lcdic_dma_handle_t *lcdicHandle = &prvData->lcdicHandle;
    LCDIC_Type *lcdic               = lcdicHandle->lcdic;

    if (prvData->dataLen > 0U)
    {
        curSendLen = MIN(prvData->dataLen, LCDIC_MAX_BYTE_PER_TRX);

        /* Continue to send left part. */
        txXfer.cmd            = (uint8_t)kMIPI_DBI_WriteMemoryContinue;
        txXfer.teSyncMode     = kLCDIC_TeNoSync;
        txXfer.trxTimeoutMode = kLCDIC_ShortTimeout;
        txXfer.dataFormat     = prvData->dataFormat;
        txXfer.txData         = prvData->txData;
        txXfer.dataLen        = curSendLen;

        prvData->dataLen -= curSendLen;
        prvData->txData += curSendLen;

        (void)LCDIC_SendDataArrayDMA(lcdic, lcdicHandle, &txXfer);
    }
    else
    {
        dbiIface->memDoneCallback(status, dbiIface->memDoneCallbackParam);
    }
}

status_t DBI_LCDIC_DMA_CreateHandle(dbi_iface_t *dbiIface,
                                    const dbi_lcdic_dma_config_t *config,
                                    dbi_lcdic_dma_prv_data_t *prvData)
{
    (void)memset(dbiIface, 0, sizeof(dbi_iface_t));

    dbiIface->xferOps   = &g_dbiIfaceLcdicDmaXferOps;
    dbiIface->prvData   = prvData;
    prvData->dataFormat = config->dataFormat;
    prvData->teSyncMode = config->teSyncMode;

    return LCDIC_TransferCreateHandleDMA(config->lcdic, &prvData->lcdicHandle, DBI_LCDIC_DMA_TransferCompletedCallback,
                                         dbiIface, config->txDmaHandle, NULL, *config->dmaDesc);
}

status_t DBI_LCDIC_DMA_WriteCommandData(dbi_iface_t *dbiIface, uint8_t command, const void *data, uint32_t len_byte)
{
    lcdic_tx_xfer_t xfer = {0};
    status_t status;

    lcdic_dma_handle_t *lcdicHandle = &((dbi_lcdic_dma_prv_data_t *)(dbiIface->prvData))->lcdicHandle;
    LCDIC_Type *lcdic               = lcdicHandle->lcdic;

    if (0U == len_byte)
    {
        status = LCDIC_SendCommandBlocking(lcdic, command);
    }
    else
    {
        xfer.cmd            = command;
        xfer.teSyncMode     = kLCDIC_TeNoSync;
        xfer.trxTimeoutMode = kLCDIC_ShortTimeout;
        xfer.dataFormat     = kLCDIC_DataFormatByte;
        xfer.dataLen        = len_byte;
        xfer.txData         = data;

        status = LCDIC_SendDataArrayBlocking(lcdic, &xfer);
    }

    return status;
}

#if MCUX_DBI_IFACE_ENABLE_READ
status_t DBI_LCDIC_DMA_ReadData(dbi_iface_t *dbiIface, uint8_t command, void *data, uint32_t len_byte)
{
    lcdic_rx_xfer_t xfer = {0};

    lcdic_dma_handle_t *lcdicHandle = &((dbi_lcdic_dma_prv_data_t *)(dbiIface->prvData))->lcdicHandle;
    LCDIC_Type *lcdic               = lcdicHandle->lcdic;

    xfer.cmd            = command;
    xfer.dummyCount     = 0u;
    xfer.trxTimeoutMode = kLCDIC_ShortTimeout;
    xfer.dataFormat     = kLCDIC_DataFormatByte;
    xfer.dataLen        = len_byte;
    xfer.rxData         = data;

    return LCDIC_ReadDataArrayBlocking(lcdic, &xfer);
}
#endif /* MCUX_DBI_IFACE_ENABLE_READ */

status_t DBI_LCDIC_DMA_WriteMemory(dbi_iface_t *dbiIface, uint8_t command, const void *data, uint32_t len_byte)
{
    status_t status;
    lcdic_tx_xfer_t txXfer;

    dbi_lcdic_dma_prv_data_t *prvData = (dbi_lcdic_dma_prv_data_t *)(dbiIface->prvData);

    lcdic_dma_handle_t *lcdicHandle = &prvData->lcdicHandle;
    LCDIC_Type *lcdic               = lcdicHandle->lcdic;

    txXfer.cmd            = command;
    txXfer.teSyncMode     = prvData->teSyncMode;
    txXfer.trxTimeoutMode = kLCDIC_ShortTimeout;
    txXfer.dataFormat     = prvData->dataFormat;
    txXfer.txData         = data;

    if (len_byte > LCDIC_MAX_BYTE_PER_TRX)
    {
        prvData->dataLen = len_byte - LCDIC_MAX_BYTE_PER_TRX;
        prvData->txData  = ((const uint8_t *)data) + LCDIC_MAX_BYTE_PER_TRX;
        txXfer.dataLen   = LCDIC_MAX_BYTE_PER_TRX;
    }
    else
    {
        prvData->dataLen = 0u;
        txXfer.dataLen   = len_byte;
    }

    if (NULL != lcdicHandle->txDmaHandle)
    {
        status = LCDIC_SendDataArrayDMA(lcdic, lcdicHandle, &txXfer);
    }
    else
    {
        status = kStatus_Fail;
    }

    return status;
}
