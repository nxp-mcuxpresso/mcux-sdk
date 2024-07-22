/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dspi_freertos.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.dspi_freertos"
#endif

static void DSPI_RTOS_Callback(SPI_Type *base, dspi_master_handle_t *drv_handle, status_t status, void *userData)
{
    dspi_rtos_handle_t *handle = (dspi_rtos_handle_t *)userData;
    BaseType_t reschedule = pdFALSE;
    handle->async_status = status;
    (void)xSemaphoreGiveFromISR(handle->event, &reschedule);
    portYIELD_FROM_ISR(reschedule);
}

/*!
 * brief Initializes the DSPI.
 *
 * This function initializes the DSPI module and the related RTOS context.
 *
 * param handle The RTOS DSPI handle, the pointer to an allocated space for RTOS context.
 * param base The pointer base address of the DSPI instance to initialize.
 * param masterConfig A configuration structure to set-up the DSPI in master mode.
 * param srcClock_Hz A frequency of the input clock of the DSPI module.
 * return status of the operation.
 */
status_t DSPI_RTOS_Init(dspi_rtos_handle_t *handle,
                        SPI_Type *base,
                        const dspi_master_config_t *masterConfig,
                        uint32_t srcClock_Hz)
{
    if (handle == NULL)
    {
        return kStatus_InvalidArgument;
    }

    if (base == NULL)
    {
        return kStatus_InvalidArgument;
    }

    (void)memset(handle, 0, sizeof(dspi_rtos_handle_t));

#if (configSUPPORT_STATIC_ALLOCATION == 1)
    handle->mutex = xSemaphoreCreateMutexStatic(&handle->mutexBuffer);
#else
    handle->mutex = xSemaphoreCreateMutex();
#endif
    if (handle->mutex == NULL)
    {
        return kStatus_Fail;
    }
#if (configSUPPORT_STATIC_ALLOCATION == 1)
    handle->event = xSemaphoreCreateBinaryStatic(&handle->semaphoreBuffer);
#else
    handle->event = xSemaphoreCreateBinary();
#endif
    if (handle->event == NULL)
    {
        vSemaphoreDelete(handle->mutex);
        return kStatus_Fail;
    }

    handle->base = base;

    DSPI_MasterInit(handle->base, masterConfig, srcClock_Hz);
    DSPI_MasterTransferCreateHandle(handle->base, &handle->drv_handle, DSPI_RTOS_Callback, (void *)handle);

    return kStatus_Success;
}

/*!
 * brief Deinitializes the DSPI.
 *
 * This function deinitializes the DSPI module and the related RTOS context.
 *
 * param handle The RTOS DSPI handle.
 */
status_t DSPI_RTOS_Deinit(dspi_rtos_handle_t *handle)
{
    DSPI_Deinit(handle->base);
    vSemaphoreDelete(handle->event);
    vSemaphoreDelete(handle->mutex);

    return kStatus_Success;
}

/*!
 * brief Performs the SPI transfer.
 *
 * This function performs the SPI transfer according to the data given in the transfer structure.
 *
 * param handle The RTOS DSPI handle.
 * param transfer A structure specifying the transfer parameters.
 * return status of the operation.
 */
status_t DSPI_RTOS_Transfer(dspi_rtos_handle_t *handle, dspi_transfer_t *transfer)
{
    status_t status;

    /* Lock resource mutex */
    if (xSemaphoreTake(handle->mutex, portMAX_DELAY) != pdTRUE)
    {
        return kStatus_DSPI_Busy;
    }

    status = DSPI_MasterTransferNonBlocking(handle->base, &handle->drv_handle, transfer);
    if (status != kStatus_Success)
    {
        (void)xSemaphoreGive(handle->mutex);
        return status;
    }

    /* Wait for transfer to finish */
    if (xSemaphoreTake(handle->event, portMAX_DELAY) != pdTRUE)
    {
        return kStatus_DSPI_Error;
    }

    /* Unlock resource mutex */
    (void)xSemaphoreGive(handle->mutex);

    /* Return status captured by callback function */
    return handle->async_status;
}
