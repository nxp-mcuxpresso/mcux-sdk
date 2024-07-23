/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_uart_freertos.h"
#include <FreeRTOS.h>
#include <event_groups.h>
#include <semphr.h>

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.iuart_freertos"
#endif

static void UART_RTOS_Callback(UART_Type *base, uart_handle_t *state, status_t status, void *param)
{
    uart_rtos_handle_t *handle = (uart_rtos_handle_t *)param;
    BaseType_t xHigherPriorityTaskWoken, xResult;

    xHigherPriorityTaskWoken = pdFALSE;
    xResult                  = pdFAIL;

    if (status == kStatus_UART_RxIdle)
    {
        xResult = xEventGroupSetBitsFromISR(handle->rxEvent, RTOS_UART_COMPLETE, &xHigherPriorityTaskWoken);
    }
    else if (status == kStatus_UART_TxIdle)
    {
        xResult = xEventGroupSetBitsFromISR(handle->txEvent, RTOS_UART_COMPLETE, &xHigherPriorityTaskWoken);
    }
    else if (status == kStatus_UART_RxRingBufferOverrun)
    {
        xResult = xEventGroupSetBitsFromISR(handle->rxEvent, RTOS_UART_RING_BUFFER_OVERRUN, &xHigherPriorityTaskWoken);
    }
    else if (status == kStatus_UART_RxHardwareOverrun)
    {
        /* Clear Overrun flag (OR) in UART S1 register */
        UART_ClearStatusFlag(base, kUART_RxOverrunFlag);
        xResult =
            xEventGroupSetBitsFromISR(handle->rxEvent, RTOS_UART_HARDWARE_BUFFER_OVERRUN, &xHigherPriorityTaskWoken);
    }
    else
    {
        xResult = pdFAIL;
    }

    if (xResult != pdFAIL)
    {
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_RTOS_Init
 * Description   : Initializes the UART instance for application
 *
 *END**************************************************************************/
/*!
 * brief Initializes a UART instance for operation in RTOS.
 *
 * param handle The RTOS UART handle, the pointer to an allocated space for RTOS context.
 * param t_handle The pointer to the allocated space to store the transactional layer internal state.
 * param cfg The pointer to the parameters required to configure the UART after initialization.
 * return kStatus_Success, otherwise fail.
 */
int UART_RTOS_Init(uart_rtos_handle_t *handle, uart_handle_t *t_handle, const uart_rtos_config_t *cfg)
{
    status_t status;
    uart_config_t defcfg;

    if (NULL == handle)
    {
        return kStatus_InvalidArgument;
    }
    if (NULL == t_handle)
    {
        return kStatus_InvalidArgument;
    }
    if (NULL == cfg)
    {
        return kStatus_InvalidArgument;
    }
    if (NULL == cfg->base)
    {
        return kStatus_InvalidArgument;
    }
    if (0u == cfg->srcclk)
    {
        return kStatus_InvalidArgument;
    }
    if (0u == cfg->baudrate)
    {
        return kStatus_InvalidArgument;
    }

    handle->base    = cfg->base;
    handle->t_state = t_handle;
#if (configSUPPORT_STATIC_ALLOCATION == 1)
    handle->txSemaphore = xSemaphoreCreateMutexStatic(&handle->txSemaphoreBuffer);
#else
    handle->txSemaphore = xSemaphoreCreateMutex();
#endif
    if (NULL == handle->txSemaphore)
    {
        return kStatus_Fail;
    }
#if (configSUPPORT_STATIC_ALLOCATION == 1)
    handle->rxSemaphore = xSemaphoreCreateMutexStatic(&handle->rxSemaphoreBuffer);
#else
    handle->rxSemaphore = xSemaphoreCreateMutex();
#endif
    if (NULL == handle->rxSemaphore)
    {
        vSemaphoreDelete(handle->txSemaphore);
        return kStatus_Fail;
    }
#if (configSUPPORT_STATIC_ALLOCATION == 1)
    handle->txEvent = xEventGroupCreateStatic(&handle->txEventBuffer);
#else
    handle->txEvent     = xEventGroupCreate();
#endif
    if (NULL == handle->txEvent)
    {
        vSemaphoreDelete(handle->rxSemaphore);
        vSemaphoreDelete(handle->txSemaphore);
        return kStatus_Fail;
    }
#if (configSUPPORT_STATIC_ALLOCATION == 1)
    handle->rxEvent = xEventGroupCreateStatic(&handle->rxEventBuffer);
#else
    handle->rxEvent     = xEventGroupCreate();
#endif
    if (NULL == handle->rxEvent)
    {
        vEventGroupDelete(handle->txEvent);
        vSemaphoreDelete(handle->rxSemaphore);
        vSemaphoreDelete(handle->txSemaphore);
        return kStatus_Fail;
    }
    UART_GetDefaultConfig(&defcfg);

    defcfg.baudRate_Bps = cfg->baudrate;
    defcfg.parityMode   = cfg->parity;
#if defined(FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT) && FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT
    defcfg.stopBitCount = cfg->stopbits;
#endif

    status = UART_Init(handle->base, &defcfg, cfg->srcclk);
    if (kStatus_Success != status)
    {
        vEventGroupDelete(handle->rxEvent);
        vEventGroupDelete(handle->txEvent);
        vSemaphoreDelete(handle->rxSemaphore);
        vSemaphoreDelete(handle->txSemaphore);
        return kStatus_Fail;
    }
    UART_TransferCreateHandle(handle->base, handle->t_state, UART_RTOS_Callback, handle);
    UART_TransferStartRingBuffer(handle->base, handle->t_state, cfg->buffer, cfg->buffer_size);

    UART_EnableTx(handle->base, true);
    UART_EnableRx(handle->base, true);

    return kStatus_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_RTOS_Deinit
 * Description   : Deinitializes the UART instance and frees resources
 *
 *END**************************************************************************/
/*!
 * brief Deinitializes a UART instance for operation.
 *
 * This function deinitializes the UART module, sets all register values to reset value,
 * and frees the resources.
 *
 * param handle The RTOS UART handle.
 */
int UART_RTOS_Deinit(uart_rtos_handle_t *handle)
{
    UART_Deinit(handle->base);

    vEventGroupDelete(handle->txEvent);
    vEventGroupDelete(handle->rxEvent);

    /* Give the semaphore. This is for functional safety */
    (void)xSemaphoreGive(handle->txSemaphore);
    (void)xSemaphoreGive(handle->rxSemaphore);

    vSemaphoreDelete(handle->txSemaphore);
    vSemaphoreDelete(handle->rxSemaphore);

    /* Invalidate the handle */
    handle->base    = NULL;
    handle->t_state = NULL;

    return kStatus_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_RTOS_Send
 * Description   : Initializes the UART instance for application
 *
 *END**************************************************************************/
/*!
 * brief Sends data in the background.
 *
 * This function sends data. It is a synchronous API.
 * If the hardware buffer is full, the task is in the blocked state.
 *
 * param handle The RTOS UART handle.
 * param buffer The pointer to the buffer to send.
 * param length The number of bytes to send.
 */
int UART_RTOS_Send(uart_rtos_handle_t *handle, uint8_t *buffer, uint32_t length)
{
    EventBits_t ev;
    int retval = kStatus_Success;
    status_t status;

    if (NULL == handle->base)
    {
        /* Invalid handle. */
        return kStatus_Fail;
    }
    if (0u == length)
    {
        return kStatus_Success;
    }
    if (NULL == buffer)
    {
        return kStatus_InvalidArgument;
    }

    if (pdFALSE == xSemaphoreTake(handle->txSemaphore, 0))
    {
        /* We could not take the semaphore, exit with 0 data received */
        return kStatus_Fail;
    }

    handle->txTransfer.data     = (uint8_t *)buffer;
    handle->txTransfer.dataSize = (uint32_t)length;

    /* Non-blocking call */
    status = UART_TransferSendNonBlocking(handle->base, handle->t_state, &handle->txTransfer);
    if (status != kStatus_Success)
    {
        (void)xSemaphoreGive(handle->txSemaphore);
        return kStatus_Fail;
    }

    ev = xEventGroupWaitBits(handle->txEvent, RTOS_UART_COMPLETE, pdTRUE, pdFALSE, portMAX_DELAY);
    if ((ev & RTOS_UART_COMPLETE) == 0U)
    {
        retval = kStatus_Fail;
    }

    if (pdFALSE == xSemaphoreGive(handle->txSemaphore))
    {
        /* We could not post the semaphore, exit with error */
        retval = kStatus_Fail;
    }

    return retval;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_RTOS_Recv
 * Description   : Receives chars for the application
 *
 *END**************************************************************************/
/*!
 * brief Receives data.
 *
 * This function receives data from UART. It is a synchronous API. If data is immediately available,
 * it is returned immediately and the number of bytes received.
 *
 * param handle The RTOS UART handle.
 * param buffer The pointer to the buffer to write received data.
 * param length The number of bytes to receive.
 * param received The pointer to a variable of size_t where the number of received data is filled.
 */
int UART_RTOS_Receive(uart_rtos_handle_t *handle, uint8_t *buffer, uint32_t length, size_t *received)
{
    EventBits_t ev;
    size_t n              = 0;
    int retval            = kStatus_Fail;
    size_t local_received = 0;
    status_t status;

    if (NULL == handle->base)
    {
        /* Invalid handle. */
        return kStatus_Fail;
    }
    if (0u == length)
    {
        if (received != NULL)
        {
            *received = n;
        }
        return kStatus_Success;
    }
    if (NULL == buffer)
    {
        return kStatus_InvalidArgument;
    }

    /* New transfer can be performed only after current one is finished */
    if (pdFALSE == xSemaphoreTake(handle->rxSemaphore, portMAX_DELAY))
    {
        /* We could not take the semaphore, exit with 0 data received */
        return kStatus_Fail;
    }

    handle->rxTransfer.data     = buffer;
    handle->rxTransfer.dataSize = (uint32_t)length;

    /* Non-blocking call */
    status = UART_TransferReceiveNonBlocking(handle->base, handle->t_state, &handle->rxTransfer, &n);
    if (status != kStatus_Success)
    {
        (void)xSemaphoreGive(handle->rxSemaphore);
        return kStatus_Fail;
    }

    ev = xEventGroupWaitBits(handle->rxEvent,
                             RTOS_UART_COMPLETE | RTOS_UART_RING_BUFFER_OVERRUN | RTOS_UART_HARDWARE_BUFFER_OVERRUN,
                             pdTRUE, pdFALSE, portMAX_DELAY);
    if ((ev & RTOS_UART_HARDWARE_BUFFER_OVERRUN) != 0U)
    {
        /* Stop data transfer to application buffer, ring buffer is still active */
        UART_TransferAbortReceive(handle->base, handle->t_state);
        /* Prevent false indication of successful transfer in next call of UART_RTOS_Receive.
           RTOS_UART_COMPLETE flag could be set meanwhile overrun is handled */
        (void)xEventGroupClearBits(handle->rxEvent, RTOS_UART_COMPLETE);
        retval         = kStatus_UART_RxHardwareOverrun;
        local_received = 0;
    }
    else if ((ev & RTOS_UART_RING_BUFFER_OVERRUN) != 0U)
    {
        /* Stop data transfer to application buffer, ring buffer is still active */
        UART_TransferAbortReceive(handle->base, handle->t_state);
        /* Prevent false indication of successful transfer in next call of UART_RTOS_Receive.
           RTOS_UART_COMPLETE flag could be set meanwhile overrun is handled */
        (void)xEventGroupClearBits(handle->rxEvent, RTOS_UART_COMPLETE);
        retval         = kStatus_UART_RxRingBufferOverrun;
        local_received = 0;
    }
    else if ((ev & RTOS_UART_COMPLETE) != 0U)
    {
        retval         = kStatus_Success;
        local_received = length;
    }
    else
    {
        retval         = kStatus_UART_Error;
        local_received = 0;
    }

    /* Prevent repetitive NULL check */
    if (received != NULL)
    {
        *received = local_received;
    }

    /* Enable next transfer. Current one is finished */
    if (pdFALSE == xSemaphoreGive(handle->rxSemaphore))
    {
        /* We could not post the semaphore, exit with error */
        retval = kStatus_Fail;
    }
    return retval;
}
