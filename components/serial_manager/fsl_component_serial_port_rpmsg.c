/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_component_serial_manager.h"
#include "fsl_component_serial_port_internal.h"

#if (defined(SERIAL_PORT_TYPE_RPMSG) && (SERIAL_PORT_TYPE_RPMSG > 0U))
#include "fsl_adapter_rpmsg.h"

#include "fsl_component_serial_port_rpmsg.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#ifndef NDEBUG
#if (defined(DEBUG_CONSOLE_ASSERT_DISABLE) && (DEBUG_CONSOLE_ASSERT_DISABLE > 0U))
#undef assert
#define assert(n)
#else
/* MISRA C-2012 Rule 17.2 */
#undef assert
#define assert(n) \
    while (!(n))  \
    {             \
        ;         \
    }
#endif
#endif

typedef struct _serial_rpmsg_send_state
{
    serial_manager_callback_t callback;
    void *param;
} serial_rpmsg_send_state_t;

typedef struct _serial_rpmsg_recv_state
{
    serial_manager_callback_t callback;
    void *param;
#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
#else  /* !SERIAL_MANAGER_NON_BLOCKING_MODE */
    volatile uint8_t *data;
    volatile uint32_t len;
    volatile uint32_t sofar;
    volatile uint32_t remain;
#endif /* SERIAL_MANAGER_NON_BLOCKING_MODE */
} serial_rpmsg_recv_state_t;

typedef struct _serial_rpmsg_state
{
    RPMSG_HANDLE_DEFINE(rpmsgHandleBuffer);
    serial_rpmsg_recv_state_t rx;
    serial_rpmsg_send_state_t tx;
} serial_rpmsg_state_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

static hal_rpmsg_return_status_t Serial_RpmsgRxCallback(void *param, uint8_t *data, uint32_t len)
{
    serial_rpmsg_state_t *serialRpmsgHandle;
#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
    serial_manager_callback_message_t msg;
#else  /* !SERIAL_MANAGER_NON_BLOCKING_MODE */
    uint32_t bytes;
#endif /* SERIAL_MANAGER_NON_BLOCKING_MODE */

    if (NULL == param)
    {
        return kStatus_HAL_RL_RELEASE;
    }

    serialRpmsgHandle = (serial_rpmsg_state_t *)param;

#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
    /* Rx Idle */
    if ((NULL != serialRpmsgHandle->rx.callback))
    {
        msg.buffer = data;
        msg.length = len;
        serialRpmsgHandle->rx.callback(serialRpmsgHandle->rx.param, &msg, kStatus_SerialManager_Success);
    }
#else  /* !SERIAL_MANAGER_NON_BLOCKING_MODE */
    /* Receive buffer is ready */
    if (NULL != serialRpmsgHandle->rx.data)
    {
        bytes = (len <= (serialRpmsgHandle->rx.len - serialRpmsgHandle->rx.sofar)) ?
                    (len) :
                    (serialRpmsgHandle->rx.len - serialRpmsgHandle->rx.sofar);
        /* read out the last bytes */
        (void)memcpy((uint8_t *)&serialRpmsgHandle->rx.data[serialRpmsgHandle->rx.sofar], data, bytes);
        serialRpmsgHandle->rx.sofar += bytes;
        if (serialRpmsgHandle->rx.len == serialRpmsgHandle->rx.sofar)
        {
            serialRpmsgHandle->rx.data   = NULL;
            serialRpmsgHandle->rx.remain = len - bytes;
        }
    }
#endif /* SERIAL_MANAGER_NON_BLOCKING_MODE */
    return kStatus_HAL_RL_RELEASE;
}

serial_manager_status_t Serial_RpmsgInit(serial_handle_t serialHandle, void *serialConfig)
{
    serial_rpmsg_state_t *serialRpmsgHandle;
    serial_manager_config_t *serialRpmsgConfig;

    assert(serialConfig);
    assert(serialHandle);

    serialRpmsgHandle = (serial_rpmsg_state_t *)serialHandle;
    serialRpmsgConfig = (serial_manager_config_t *)serialConfig;

    if (kStatus_HAL_RpmsgSuccess != HAL_RpmsgInit((hal_rpmsg_handle_t)serialRpmsgHandle->rpmsgHandleBuffer,
                                                  (hal_rpmsg_config_t *)serialRpmsgConfig->portConfig))
    {
        return kStatus_SerialManager_Error;
    }

    if (kStatus_HAL_RpmsgSuccess != HAL_RpmsgInstallRxCallback((hal_rpmsg_handle_t)serialRpmsgHandle->rpmsgHandleBuffer,
                                                               Serial_RpmsgRxCallback, serialHandle))
    {
        return kStatus_SerialManager_Error;
    }

#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
#endif /* SERIAL_MANAGER_NON_BLOCKING_MODE */

    return kStatus_SerialManager_Success;
}

serial_manager_status_t Serial_RpmsgDeinit(serial_handle_t serialHandle)
{
    serial_rpmsg_state_t *serialRpmsgHandle;

    assert(serialHandle);

    serialRpmsgHandle = (serial_rpmsg_state_t *)serialHandle;

    (void)HAL_RpmsgDeinit((hal_rpmsg_handle_t)serialRpmsgHandle->rpmsgHandleBuffer);

    return kStatus_SerialManager_Success;
}

#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))

serial_manager_status_t Serial_RpmsgWrite(serial_handle_t serialHandle, uint8_t *buffer, uint32_t length)
{
    serial_manager_callback_message_t msg;
    serial_rpmsg_state_t *serialRpmsgHandle;

    assert(serialHandle);
    assert(buffer);
    assert(length);

    serialRpmsgHandle = (serial_rpmsg_state_t *)serialHandle;

    if (kStatus_HAL_RpmsgSuccess !=
        HAL_RpmsgSend((hal_rpmsg_handle_t)serialRpmsgHandle->rpmsgHandleBuffer, buffer, length))
    {
        return kStatus_SerialManager_Error;
    }

    if (NULL != serialRpmsgHandle->tx.callback)
    {
        msg.buffer = buffer;
        msg.length = length;
        serialRpmsgHandle->tx.callback(serialRpmsgHandle->tx.param, &msg, kStatus_SerialManager_Success);
    }

    return kStatus_SerialManager_Success;
}

serial_manager_status_t Serial_RpmsgWriteBlocking(serial_handle_t serialHandle, uint8_t *buffer, uint32_t length)
{
    serial_rpmsg_state_t *serialRpmsgHandle;

    assert(serialHandle);
    assert(buffer);
    assert(length);

    serialRpmsgHandle = (serial_rpmsg_state_t *)serialHandle;

    if (kStatus_HAL_RpmsgSuccess !=
        HAL_RpmsgSend((hal_rpmsg_handle_t)serialRpmsgHandle->rpmsgHandleBuffer, buffer, length))
    {
        return kStatus_SerialManager_Error;
    }

    return kStatus_SerialManager_Success;
}

#else  /* !SERIAL_MANAGER_NON_BLOCKING_MODE */

serial_manager_status_t Serial_RpmsgWrite(serial_handle_t serialHandle, uint8_t *buffer, uint32_t length)
{
    serial_rpmsg_state_t *serialRpmsgHandle;

    assert(serialHandle);
    assert(buffer);
    assert(length);

    serialRpmsgHandle = (serial_rpmsg_state_t *)serialHandle;

    if (kStatus_HAL_RpmsgSuccess !=
        HAL_RpmsgSend((hal_rpmsg_handle_t)serialRpmsgHandle->rpmsgHandleBuffer, buffer, length))
    {
        return kStatus_SerialManager_Error;
    }

    return kStatus_SerialManager_Success;
}

serial_manager_status_t Serial_RpmsgRead(serial_handle_t serialHandle, uint8_t *buffer, uint32_t length)
{
    serial_rpmsg_state_t *serialRpmsgHandle;

    assert(serialHandle);
    assert(buffer);
    assert(length);

    serialRpmsgHandle = (serial_rpmsg_state_t *)serialHandle;

    serialRpmsgHandle->rx.data = buffer;
    serialRpmsgHandle->rx.len = length;
    serialRpmsgHandle->rx.sofar = 0;

    while (serialRpmsgHandle->rx.sofar < serialRpmsgHandle->rx.len)
        ;

    if (0U < serialRpmsgHandle->rx.remain)
    {
        /* The received bytes not equal to request. */
        return kStatus_SerialManager_Error;
    }

    return kStatus_SerialManager_Success;
}
#endif /* SERIAL_MANAGER_NON_BLOCKING_MODE */

#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
serial_manager_status_t Serial_RpmsgCancelWrite(serial_handle_t serialHandle)
{
    assert(serialHandle);

    return kStatus_SerialManager_Success;
}

serial_manager_status_t Serial_RpmsgInstallTxCallback(serial_handle_t serialHandle,
                                                      serial_manager_callback_t callback,
                                                      void *callbackParam)
{
    serial_rpmsg_state_t *serialRpmsgHandle;

    assert(serialHandle);

    serialRpmsgHandle = (serial_rpmsg_state_t *)serialHandle;

    serialRpmsgHandle->tx.callback = callback;
    serialRpmsgHandle->tx.param    = callbackParam;

    return kStatus_SerialManager_Success;
}

serial_manager_status_t Serial_RpmsgInstallRxCallback(serial_handle_t serialHandle,
                                                      serial_manager_callback_t callback,
                                                      void *callbackParam)
{
    serial_rpmsg_state_t *serialRpmsgHandle;

    assert(serialHandle);

    serialRpmsgHandle = (serial_rpmsg_state_t *)serialHandle;

    serialRpmsgHandle->rx.callback = callback;
    serialRpmsgHandle->rx.param    = callbackParam;

    return kStatus_SerialManager_Success;
}
#endif /* SERIAL_MANAGER_NON_BLOCKING_MODE */

serial_manager_status_t Serial_RpmsgEnterLowpower(serial_handle_t serialHandle)
{
    serial_rpmsg_state_t *serialRpmsgHandle;

    assert(serialHandle);

    serialRpmsgHandle = (serial_rpmsg_state_t *)serialHandle;

    if (kStatus_HAL_RpmsgSuccess != HAL_RpmsgEnterLowpower((hal_rpmsg_handle_t)serialRpmsgHandle->rpmsgHandleBuffer))
    {
        return kStatus_SerialManager_Error;
    }

    return kStatus_SerialManager_Success;
}

serial_manager_status_t Serial_RpmsgExitLowpower(serial_handle_t serialHandle)
{
    serial_rpmsg_state_t *serialRpmsgHandle;
    assert(serialHandle);

    serialRpmsgHandle = (serial_rpmsg_state_t *)serialHandle;

    if (kStatus_HAL_RpmsgSuccess != HAL_RpmsgExitLowpower((hal_rpmsg_handle_t)serialRpmsgHandle->rpmsgHandleBuffer))
    {
        return kStatus_SerialManager_Error;
    }

    return kStatus_SerialManager_Success;
}

#endif
