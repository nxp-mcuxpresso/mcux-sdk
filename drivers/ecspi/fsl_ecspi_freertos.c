/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_ecspi_freertos.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.ecspi_freertos"
#endif

static void ECSPI_RTOS_Callback(ECSPI_Type *base, ecspi_master_handle_t *drv_handle, status_t status, void *userData)
{
    ecspi_rtos_handle_t *handle = (ecspi_rtos_handle_t *)userData;
    BaseType_t reschedule;
    handle->async_status = status;
    (void)xSemaphoreGiveFromISR(handle->event, &reschedule);
    portYIELD_FROM_ISR(reschedule);
}

/*!
 * brief Initializes ECSPI.
 *
 * This function initializes the ECSPI module and related RTOS context.
 *
 * param handle The RTOS ECSPI handle, the pointer to an allocated space for RTOS context.
 * param base The pointer base address of the ECSPI instance to initialize.
 * param masterConfig Configuration structure to set-up ECSPI in master mode.
 * param srcClock_Hz Frequency of input clock of the ECSPI module.
 * return status of the operation.
 */
status_t ECSPI_RTOS_Init(ecspi_rtos_handle_t *handle,
                         ECSPI_Type *base,
                         const ecspi_master_config_t *masterConfig,
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

    (void)memset(handle, 0, sizeof(ecspi_rtos_handle_t));
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

    ECSPI_MasterInit(handle->base, masterConfig, srcClock_Hz);
    ECSPI_MasterTransferCreateHandle(handle->base, &handle->drv_handle, ECSPI_RTOS_Callback, (void *)handle);

    return kStatus_Success;
}

/*!
 * brief Deinitializes the ECSPI.
 *
 * This function deinitializes the ECSPI module and related RTOS context.
 *
 * param handle The RTOS ECSPI handle.
 */
status_t ECSPI_RTOS_Deinit(ecspi_rtos_handle_t *handle)
{
    ECSPI_Deinit(handle->base);
    vSemaphoreDelete(handle->event);
    vSemaphoreDelete(handle->mutex);

    return kStatus_Success;
}

/*!
 * brief Performs ECSPI transfer.
 *
 * This function performs an ECSPI transfer according to data given in the transfer structure.
 *
 * param handle The RTOS ECSPI handle.
 * param transfer Structure specifying the transfer parameters.
 * return status of the operation.
 */
status_t ECSPI_RTOS_Transfer(ecspi_rtos_handle_t *handle, ecspi_transfer_t *transfer)
{
    status_t status;

    /* Lock resource mutex */
    if (xSemaphoreTake(handle->mutex, portMAX_DELAY) != pdTRUE)
    {
        return kStatus_ECSPI_Busy;
    }

    status = ECSPI_MasterTransferNonBlocking(handle->base, &handle->drv_handle, transfer);
    if (status != kStatus_Success)
    {
        (void)xSemaphoreGive(handle->mutex);
        return status;
    }

    /* Wait for transfer to finish */
    if (xSemaphoreTake(handle->event, portMAX_DELAY) != pdTRUE)
    {
        return kStatus_ECSPI_Error;
    }

    /* Unlock resource mutex */
    (void)xSemaphoreGive(handle->mutex);

    /* Return status captured by callback function */
    return handle->async_status;
}
