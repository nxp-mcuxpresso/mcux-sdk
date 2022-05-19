/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "srtm_heap.h"
#include "srtm_uart_adapter.h"
#include "fsl_common.h"
#include "task.h" /* freertos */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#ifndef SRTM_UART_MAX_INSTANCE_NUM /* LPUART0, LPUART1, ..., LPUARTx , x is the uart instance number */
#define SRTM_UART_MAX_INSTANCE_NUM (10U)
#endif

extern void SRTM_Uart_ReceiverTask(void *pvParameters);

typedef struct _srtm_uart_handles_adapter
{
    struct _srtm_uart_adapter adapter;
    serial_handle_t serialHandle[SRTM_UART_MAX_INSTANCE_NUM];
    serial_write_handle_t serialWriteHandle[SRTM_UART_MAX_INSTANCE_NUM];
    serial_read_handle_t serialReadHandle[SRTM_UART_MAX_INSTANCE_NUM];
    TaskHandle_t receiverTaskHandle[SRTM_UART_MAX_INSTANCE_NUM];
} * srtm_uart_handles_adapter_t;

/*******************************************************************************
 * Code
 ******************************************************************************/
static serial_read_handle_t SRTM_UartAdapter_FindReadHandleByBusId(srtm_uart_adapter_t adapter,
                                            uint8_t busId)
{
    srtm_uart_handles_adapter_t handle = (srtm_uart_handles_adapter_t)(void *)adapter;
    if (busId >= SRTM_UART_MAX_INSTANCE_NUM)
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "%s: busId %d must less than max instance %d\r\n", __func__,
                           busId, SRTM_UART_MAX_INSTANCE_NUM);
        return NULL;
    }

    if (!handle->serialReadHandle[busId])
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "%s: busId %d not supported\r\n", __func__, busId);
        return NULL;
    }

    return handle->serialReadHandle[busId];
}

static srtm_status_t SRTM_UartAdapter_FindBusIdByReadHandle(srtm_uart_adapter_t adapter,
                                            serial_read_handle_t read_handle, uint8_t *bus_id)
{
    srtm_uart_handles_adapter_t handle = (srtm_uart_handles_adapter_t)(void *)adapter;
    uint8_t i = 0;

    assert(read_handle);
    for (i = 0; i < SRTM_UART_MAX_INSTANCE_NUM; i++)
    {
        if (handle->serialReadHandle[i] && handle->serialReadHandle[i] == read_handle)
        {
            *bus_id = i;
            break;
        }
    }

    if (i >= SRTM_UART_MAX_INSTANCE_NUM)
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "%s: cannot find read_handle\r\n", __func__);
        return SRTM_Status_Error;
    }

    return SRTM_Status_Success;
}

static TaskHandle_t SRTM_UartAdapter_FindReceiverTaskHandleByReadHandle(srtm_uart_adapter_t adapter,
                                            serial_read_handle_t read_handle)
{
    srtm_uart_handles_adapter_t handle = (srtm_uart_handles_adapter_t)(void *)adapter;
    uint8_t bus_id = SRTM_UART_INVALID_BUS_ID;

    assert(read_handle);

    if (SRTM_UartAdapter_FindBusIdByReadHandle(adapter, read_handle, &bus_id) == SRTM_Status_Success)
    {
        return handle->receiverTaskHandle[bus_id];
    }

    return NULL;
}

static srtm_status_t SRTM_UartAdapter_Send(srtm_uart_adapter_t adapter,
                                            uint8_t busId,
                                            uint8_t *data,
                                            uint32_t dataLen)
{
    srtm_uart_handles_adapter_t handle = (srtm_uart_handles_adapter_t)(void *)adapter;

    if (busId >= SRTM_UART_MAX_INSTANCE_NUM)
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "%s: busId %d must less than max instance %d\r\n", __func__,
                           busId, SRTM_UART_MAX_INSTANCE_NUM);
        return SRTM_Status_Error;
    }

    if (!handle->serialWriteHandle[busId])
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "%s: busId %d not supported\r\n", __func__, busId);
        return SRTM_Status_Error;
    }
    if (!data)
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "%s: invalid data\r\n", __func__);
        return SRTM_Status_Error;
    }

    if (!dataLen)
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "%s: invalid dataLen\r\n", __func__);
        return SRTM_Status_Error;
    }

    if (kStatus_SerialManager_Success == SerialManager_WriteNonBlocking(handle->serialWriteHandle[busId], data, dataLen))
    {
        return SRTM_Status_Success;
    }
    return SRTM_Status_Error;
}

srtm_uart_adapter_t SRTM_UartAdapter_Create(serial_handle_t serial_handles[], serial_write_handle_t write_handles[], serial_read_handle_t read_handles[], uint32_t handleNum)
{
    srtm_uart_handles_adapter_t handle;
    uint32_t i;

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    assert(serial_handles != NULL);
    assert(write_handles != NULL);
    assert(read_handles != NULL);
    assert(handleNum <= SRTM_UART_MAX_INSTANCE_NUM);

    handle = (srtm_uart_handles_adapter_t)SRTM_Heap_Malloc(sizeof(struct _srtm_uart_handles_adapter));
    assert(handle);

    memset(handle, 0, sizeof(struct _srtm_uart_handles_adapter));
    for (i = 0U; i < handleNum; i++)
    {
        handle->serialHandle[i] = serial_handles[i];
        handle->serialWriteHandle[i] = write_handles[i];
        handle->serialReadHandle[i] = read_handles[i];
	if (handle->serialReadHandle[i] != NULL)
	{
            if (xTaskCreate(SRTM_Uart_ReceiverTask, "SRTM Uart Receiver", 256U, (void *)(handle->serialReadHandle[i]), SRTM_UART_RECEIVER_TASK_PRIO, &handle->receiverTaskHandle[i]) != pdPASS)
            {
                SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "%s: Task creation failed!.\r\n", __func__);
                while (1);
            }
	}
    }

    /* Adapter interfaces. */
    handle->adapter.send = SRTM_UartAdapter_Send;
    handle->adapter.findReadHandleByBusId = SRTM_UartAdapter_FindReadHandleByBusId;
    handle->adapter.findBusIdByReadHandle = SRTM_UartAdapter_FindBusIdByReadHandle;
    handle->adapter.findReceiverTaskHandleByReadHandle = SRTM_UartAdapter_FindReceiverTaskHandleByReadHandle;

    return &handle->adapter;
}

void SRTM_UartAdapter_Destroy(srtm_uart_adapter_t adapter)
{
    assert(adapter);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    SRTM_Heap_Free(adapter);
}
