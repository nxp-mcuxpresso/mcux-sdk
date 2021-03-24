/*
 * Copyright 2019-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dbi.h"
#include "fsl_dbi_flexio_edma.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief FLEXIO DBI bus transfer complete callback function.
 */
static void DBI_FLEXIO_EDMA_TransferCompletedCallback(FLEXIO_MCULCD_Type *base,
                                                      flexio_mculcd_edma_handle_t *handle,
                                                      status_t status,
                                                      void *userData);

/*******************************************************************************
 * Variables
 ******************************************************************************/
const dbi_xfer_ops_t g_dbiFlexioEdmaXferOps = {
    .writeCommand          = DBI_FLEXIO_EDMA_WriteCommand,
    .writeData             = DBI_FLEXIO_EDMA_WriteData,
    .writeMemory           = DBI_FLEXIO_EDMA_WriteMemory,
    .readMemory            = DBI_FLEXIO_EDMA_ReadMemory,
    .setMemoryDoneCallback = DBI_FLEXIO_EDMA_SetMemoryDoneCallback,
};

/*******************************************************************************
 * Code
 ******************************************************************************/
static void DBI_FLEXIO_EDMA_TransferCompletedCallback(FLEXIO_MCULCD_Type *base,
                                                      flexio_mculcd_edma_handle_t *handle,
                                                      status_t status,
                                                      void *userData)
{
    dbi_flexio_edma_xfer_handle_t *xferHandle = (dbi_flexio_edma_xfer_handle_t *)userData;

    if (kStatus_FLEXIO_MCULCD_Idle == status)
    {
        status = kStatus_Success;
    }

    xferHandle->memDoneCallback(status, xferHandle->userData);
}

void DBI_FLEXIO_EDMA_SetMemoryDoneCallback(void *dbiXferHandle, dbi_mem_done_callback_t callback, void *userData)
{
    dbi_flexio_edma_xfer_handle_t *xferHandle = (dbi_flexio_edma_xfer_handle_t *)dbiXferHandle;

    xferHandle->memDoneCallback = callback;
    xferHandle->userData        = userData;
}

status_t DBI_FLEXIO_EDMA_CreateXferHandle(dbi_flexio_edma_xfer_handle_t *dbiXferHandle,
                                          FLEXIO_MCULCD_Type *flexioLCD,
                                          edma_handle_t *txDmaHandle,
                                          edma_handle_t *rxDmaHandle)
{
    (void)memset(dbiXferHandle, 0, sizeof(dbi_flexio_edma_xfer_handle_t));

    return FLEXIO_MCULCD_TransferCreateHandleEDMA(flexioLCD, &dbiXferHandle->flexioHandle,
                                                  DBI_FLEXIO_EDMA_TransferCompletedCallback, dbiXferHandle, txDmaHandle,
                                                  rxDmaHandle);
}

status_t DBI_FLEXIO_EDMA_WriteCommand(void *dbiXferHandle, uint32_t command)
{
    dbi_flexio_edma_xfer_handle_t *xferHandle = (dbi_flexio_edma_xfer_handle_t *)dbiXferHandle;

    FLEXIO_MCULCD_Type *flexioLCD = xferHandle->flexioHandle.base;

    FLEXIO_MCULCD_StartTransfer(flexioLCD);
    FLEXIO_MCULCD_WriteCommandBlocking(flexioLCD, command);
    FLEXIO_MCULCD_StopTransfer(flexioLCD);

    return kStatus_Success;
}

status_t DBI_FLEXIO_EDMA_WriteData(void *dbiXferHandle, void *data, uint32_t len_byte)
{
    dbi_flexio_edma_xfer_handle_t *xferHandle = (dbi_flexio_edma_xfer_handle_t *)dbiXferHandle;

    FLEXIO_MCULCD_Type *flexioLCD = xferHandle->flexioHandle.base;

    FLEXIO_MCULCD_StartTransfer(flexioLCD);
    FLEXIO_MCULCD_WriteDataArrayBlocking(flexioLCD, data, len_byte);
    FLEXIO_MCULCD_StopTransfer(flexioLCD);

    return kStatus_Success;
}

status_t DBI_FLEXIO_EDMA_WriteMemory(void *dbiXferHandle, uint32_t command, const void *data, uint32_t len_byte)
{
    status_t status;

    flexio_mculcd_transfer_t xfer;

    dbi_flexio_edma_xfer_handle_t *xferHandle = (dbi_flexio_edma_xfer_handle_t *)dbiXferHandle;

    /* Callback is necessary to notify user. */
    assert(NULL != xferHandle->memDoneCallback);

    FLEXIO_MCULCD_Type *flexioLCD = xferHandle->flexioHandle.base;

    if (NULL != xferHandle->flexioHandle.txDmaHandle)
    {
        xfer.command             = command;
        xfer.mode                = kFLEXIO_MCULCD_WriteArray;
        xfer.dataAddrOrSameValue = (uint32_t)(const uint8_t *)data;
        xfer.dataSize            = len_byte;

        status = FLEXIO_MCULCD_TransferEDMA(flexioLCD, &xferHandle->flexioHandle, &xfer);
    }
    else
    {
        /* If DMA not enabled, use the blocking method. */
        FLEXIO_MCULCD_StartTransfer(flexioLCD);
        FLEXIO_MCULCD_WriteCommandBlocking(flexioLCD, command);
        FLEXIO_MCULCD_WriteDataArrayBlocking(flexioLCD, (const void *)data, (size_t)len_byte);
        FLEXIO_MCULCD_StopTransfer(flexioLCD);

        xferHandle->memDoneCallback(kStatus_Success, xferHandle->userData);

        status = kStatus_Success;
    }

    return status;
}

status_t DBI_FLEXIO_EDMA_ReadMemory(void *dbiXferHandle, uint32_t command, void *data, uint32_t len_byte)
{
    status_t status;

    flexio_mculcd_transfer_t xfer;

    dbi_flexio_edma_xfer_handle_t *xferHandle = (dbi_flexio_edma_xfer_handle_t *)dbiXferHandle;

    /* Callback is necessary to notify user. */
    assert(NULL != xferHandle->memDoneCallback);

    FLEXIO_MCULCD_Type *flexioLCD = xferHandle->flexioHandle.base;

    if (NULL != xferHandle->flexioHandle.rxDmaHandle)
    {
        xfer.command             = command;
        xfer.mode                = kFLEXIO_MCULCD_ReadArray;
        xfer.dataAddrOrSameValue = (uint32_t)(uint8_t *)data;
        xfer.dataSize            = len_byte;

        status = FLEXIO_MCULCD_TransferEDMA(flexioLCD, &xferHandle->flexioHandle, &xfer);
    }
    else
    {
        /* If DMA not enabled, use the blocking method. */
        FLEXIO_MCULCD_StartTransfer(flexioLCD);
        FLEXIO_MCULCD_WriteCommandBlocking(flexioLCD, command);
        FLEXIO_MCULCD_ReadDataArrayBlocking(flexioLCD, data, (size_t)len_byte);
        FLEXIO_MCULCD_StopTransfer(flexioLCD);

        xferHandle->memDoneCallback(kStatus_Success, xferHandle->userData);

        status = kStatus_Success;
    }

    return status;
}
