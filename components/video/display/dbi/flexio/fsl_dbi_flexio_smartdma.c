/*
 * Copyright 2019-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dbi.h"
#include "fsl_dbi_flexio_smartdma.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief FLEXIO DBI bus transfer complete callback function.
 */
static void DBI_FLEXIO_SMARTDMA_TransferCompletedCallback(FLEXIO_MCULCD_Type *base,
                                                          flexio_mculcd_smartdma_handle_t *handle,
                                                          status_t status,
                                                          void *userData);

/*******************************************************************************
 * Variables
 ******************************************************************************/
const dbi_xfer_ops_t g_dbiFlexioSmartdmaXferOps = {
    .writeCommand          = DBI_FLEXIO_SMARTDMA_WriteCommand,
    .writeData             = DBI_FLEXIO_SMARTDMA_WriteData,
    .writeMemory           = DBI_FLEXIO_SMARTDMA_WriteMemory,
    .readMemory            = DBI_FLEXIO_SMARTDMA_ReadMemory,
    .setMemoryDoneCallback = DBI_FLEXIO_SMARTDMA_SetMemoryDoneCallback,
};

/*******************************************************************************
 * Code
 ******************************************************************************/
static void DBI_FLEXIO_SMARTDMA_TransferCompletedCallback(FLEXIO_MCULCD_Type *base,
                                                          flexio_mculcd_smartdma_handle_t *handle,
                                                          status_t status,
                                                          void *userData)
{
    dbi_flexio_smartdma_xfer_handle_t *xferHandle = (dbi_flexio_smartdma_xfer_handle_t *)userData;

    if (kStatus_FLEXIO_MCULCD_Idle == status)
    {
        status = kStatus_Success;
    }

    xferHandle->memDoneCallback(status, xferHandle->userData);
}

void DBI_FLEXIO_SMARTDMA_SetMemoryDoneCallback(void *dbiXferHandle, dbi_mem_done_callback_t callback, void *userData)
{
    dbi_flexio_smartdma_xfer_handle_t *xferHandle = (dbi_flexio_smartdma_xfer_handle_t *)dbiXferHandle;

    xferHandle->memDoneCallback = callback;
    xferHandle->userData        = userData;
}

status_t DBI_FLEXIO_SMARTDMA_CreateXferHandle(dbi_flexio_smartdma_xfer_handle_t *dbiXferHandle,
                                              FLEXIO_MCULCD_Type *flexioLCD,
                                              const flexio_mculcd_smartdma_config_t *config)
{
    dbi_flexio_smartdma_xfer_handle_t *xferHandle = (dbi_flexio_smartdma_xfer_handle_t *)dbiXferHandle;

    (void)memset(xferHandle, 0, sizeof(dbi_flexio_smartdma_xfer_handle_t));

    return FLEXIO_MCULCD_TransferCreateHandleSMARTDMA(flexioLCD, &xferHandle->flexioHandle, config,
                                                      DBI_FLEXIO_SMARTDMA_TransferCompletedCallback, xferHandle);
}

status_t DBI_FLEXIO_SMARTDMA_WriteCommand(void *dbiXferHandle, uint32_t command)
{
    dbi_flexio_smartdma_xfer_handle_t *xferHandle = (dbi_flexio_smartdma_xfer_handle_t *)dbiXferHandle;

    FLEXIO_MCULCD_Type *flexioLCD = xferHandle->flexioHandle.base;

    FLEXIO_MCULCD_StartTransfer(flexioLCD);
    FLEXIO_MCULCD_WriteCommandBlocking(flexioLCD, command);
    FLEXIO_MCULCD_StopTransfer(flexioLCD);

    return kStatus_Success;
}

status_t DBI_FLEXIO_SMARTDMA_WriteData(void *dbiXferHandle, void *data, uint32_t len_byte)
{
    dbi_flexio_smartdma_xfer_handle_t *xferHandle = (dbi_flexio_smartdma_xfer_handle_t *)dbiXferHandle;

    FLEXIO_MCULCD_Type *flexioLCD = xferHandle->flexioHandle.base;

    FLEXIO_MCULCD_StartTransfer(flexioLCD);
    FLEXIO_MCULCD_WriteDataArrayBlocking(flexioLCD, data, len_byte);
    FLEXIO_MCULCD_StopTransfer(flexioLCD);

    return kStatus_Success;
}

status_t DBI_FLEXIO_SMARTDMA_WriteMemory(void *dbiXferHandle, uint32_t command, const void *data, uint32_t len_byte)
{
    flexio_mculcd_transfer_t xfer;

    dbi_flexio_smartdma_xfer_handle_t *xferHandle = (dbi_flexio_smartdma_xfer_handle_t *)dbiXferHandle;

    /* Callback is necessary to notify user. */
    assert(NULL != xferHandle->memDoneCallback);

    FLEXIO_MCULCD_Type *flexioLCD = xferHandle->flexioHandle.base;

    xfer.command             = command;
    xfer.mode                = kFLEXIO_MCULCD_WriteArray;
    xfer.dataAddrOrSameValue = (uint32_t)(const uint8_t *)data;
    xfer.dataSize            = len_byte;

    return FLEXIO_MCULCD_TransferSMARTDMA(flexioLCD, &xferHandle->flexioHandle, &xfer);
}

status_t DBI_FLEXIO_SMARTDMA_ReadMemory(void *dbiXferHandle, uint32_t command, void *data, uint32_t len_byte)
{
    /* FlexIO MCULCD SMARTDMA does not support read */
    return kStatus_Fail;
}
