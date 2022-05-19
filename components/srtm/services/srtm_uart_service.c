/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>
#include <string.h>

#include "srtm_heap.h"
#include "srtm_dispatcher.h"
#include "srtm_service.h"
#include "srtm_service_struct.h"
#include "srtm_uart_service.h"
#include "srtm_message.h"
#include "srtm_rpmsg_endpoint.h"
#include "rpmsg_lite.h"
#include "task.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*******************************************************************************
 * Code
 ******************************************************************************/
static uint8_t rx_buf[SRTM_UART_RECEIVE_BUFFER_SIZE];
static srtm_uart_adapter_t pAdapter;

struct srtm_uart_chan
{
    srtm_channel_t chan; /* srtm uart channel(endpoint) */
    uint8_t bus_id; /* bind bus_id with srtm uart channel(endpoint) */
    uint16_t flags; /* bind flags with srtm uart channel(endpoint) */
};

struct srtm_uart_chan srtm_uart_channels[SRTM_UART_ENDPOINT_MAX_NUM] = {0};

void SRTM_Uart_RxCallBack(void *pData, serial_manager_callback_message_t *message, serial_manager_status_t status)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    TaskHandle_t taskHandle;

    taskHandle = pAdapter->findReceiverTaskHandleByReadHandle(pAdapter, (serial_read_handle_t)pData);
    assert(taskHandle);
    /* Notify srtm uart receiver task that the RX buffer is available */
    vTaskNotifyGiveFromISR(taskHandle, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void SRTM_Uart_TxCallBack(void *pData, serial_manager_callback_message_t *message, serial_manager_status_t status)
{
}

static void SRTM_UartService_InitChan(void)
{
    uint8_t uart_id = 0;

    for (uart_id = 0; uart_id < SRTM_UART_ENDPOINT_MAX_NUM; uart_id++)
    {
        srtm_uart_channels[uart_id].bus_id = SRTM_UART_INVALID_BUS_ID;
    }
}

static void SRTM_UartService_FindChanByBusId(uint8_t bus_id, struct srtm_uart_chan **chan)
{
    uint8_t uart_id = 0;

    while (srtm_uart_channels[uart_id].chan != NULL)
    {
        if (srtm_uart_channels[uart_id].bus_id == bus_id)
        {
            break;
        }
        uart_id++;
    }

    *chan = &srtm_uart_channels[uart_id];
    assert(*chan);
}

static void SRTM_UartService_FindChanBySerialReadHandle(serial_read_handle_t read_handle, struct srtm_uart_chan **chan)
{
    uint8_t uart_id = 0;

    assert(read_handle);
    while (srtm_uart_channels[uart_id].chan != NULL)
    {
        if (srtm_uart_channels[uart_id].bus_id != SRTM_UART_INVALID_BUS_ID && pAdapter->findReadHandleByBusId(pAdapter, srtm_uart_channels[uart_id].bus_id) == read_handle)
        {
            break;
        }
        uart_id++;
    }

    *chan = &srtm_uart_channels[uart_id];
    assert(*chan);
}

static uint32_t SRTM_UartService_GetChannelsNumberBindToBusId(uint8_t bus_id)
{
    uint8_t uart_id = 0;
    uint32_t count = 0U;

    assert(uart_id < SRTM_UART_ENDPOINT_MAX_NUM);
    while (srtm_uart_channels[uart_id].chan != NULL)
    {
        if (srtm_uart_channels[uart_id].bus_id == bus_id)
        {
            count++;
        }
        uart_id++;
    }
    return count;
}

static srtm_status_t SRTM_UartService_FindUartIdByChannel(srtm_channel_t chan, uint8_t *uart_id)
{
    srtm_status_t status = SRTM_Status_Error;
    uint8_t i = 0;

    while (srtm_uart_channels[i].chan != NULL)
    {
       if (srtm_uart_channels[i].chan == chan)
       {
           status = SRTM_Status_Success;
           *uart_id = i;
           break;
       }
       i++;
    }
    return status;
}

static struct srtm_uart_chan *SRTM_UartService_FindChanByUartId(uint8_t uart_id)
{
    assert(uart_id < SRTM_UART_ENDPOINT_MAX_NUM);

    assert(srtm_uart_channels[uart_id].chan != NULL);
    return &srtm_uart_channels[uart_id];
}

static void SRTM_UartService_BindChanByUartId(srtm_channel_t chan, uint8_t bus_id, uint16_t flags, uint8_t uart_id)
{
    assert(uart_id < SRTM_UART_ENDPOINT_MAX_NUM);
    if (chan != NULL && srtm_uart_channels[uart_id].chan == NULL)
    {
        srtm_uart_channels[uart_id].chan = chan;
    }

    if (srtm_uart_channels[uart_id].bus_id == SRTM_UART_INVALID_BUS_ID && bus_id != SRTM_UART_INVALID_BUS_ID)
    {
        srtm_uart_channels[uart_id].bus_id = bus_id;
    }

    if (srtm_uart_channels[uart_id].flags == 0U && flags != 0U)
    {
        srtm_uart_channels[uart_id].flags = flags;
    }
}

typedef enum
{
    STATUS_IDLE = 0U,
    STATUS_PREAMBLE1,
    STATUS_PREAMBLE2,
    STATUS_PREAMBLE3,
    STATUS_DST,
    STATUS_DATA_LEN,
    STATUS_DATA,
    STATUS_END0,
    STATUS_END1,
} FRAME_STATUS;

struct frame_ctrl
{
    FRAME_STATUS state;
    uint8_t idx; /* data index */
    uint8_t payload_len;
    uint8_t tmp_buf[SRTM_UART_RECEIVE_BUFFER_SIZE];
};

static struct frame_ctrl frm_ctl = {0};

struct frame_data
{
    uint8_t dst;
    uint8_t data_len;
    uint8_t data[SRTM_UART_FRAME_DATA_SIZE];
};
static struct frame_data frm_data = {0};


static void SRTM_UART_SendData(srtm_uart_adapter_t adapter, srtm_channel_t chan, uint8_t *data, uint8_t data_len)
{
    /* send notify from mcore to acore */
    if (pAdapter->service != NULL && chan != NULL)
    {
        pAdapter->sendNotify(pAdapter->service, chan, data, data_len);
    }
}

static void SRTM_UART_ProcessData(uint8_t *buf, uint32_t buf_len)
{
    uint8_t *end;

    if (buf_len == 0)
    {
        return;
    }

    end = buf + buf_len;
    for (; buf < end; buf++)
    {
        switch (frm_ctl.state)
        {
            case STATUS_IDLE:
            {
                frm_ctl.idx = 0;
                if (*buf == MULTI_UART_MSG_PREAMBLE0)
                {
                    frm_ctl.state = STATUS_PREAMBLE1; /* expect MULTI_UART_MSG_PREAMBLE1 */
                }
                else
                {
                    frm_ctl.state = STATUS_IDLE; /* got a wrong data, drop it */
                }
                break;
            }
            case STATUS_PREAMBLE1:
            {
                if (*buf == MULTI_UART_MSG_PREAMBLE1)
                {
                    frm_ctl.state = STATUS_PREAMBLE2; /* expect MULTI_UART_MSG_PREAMBLE2 */
                }
                else
                {
                    frm_ctl.state = STATUS_IDLE; /* got a wrong data, drop it */
                }
                break;
            }
            case STATUS_PREAMBLE2:
            {
                if (*buf == MULTI_UART_MSG_PREAMBLE2)
                {
                    frm_ctl.state = STATUS_PREAMBLE3; /* expect MULTI_UART_MSG_PREAMBLE3 */
                }
                else
                {
                    frm_ctl.state = STATUS_IDLE; /* got a wrong data, drop it */
                }
                break;
            }
            case STATUS_PREAMBLE3:
            {
                if (*buf == MULTI_UART_MSG_PREAMBLE3)
                {
                    frm_ctl.state = STATUS_DST; /* expect dst */
                }
                else
                {
                    frm_ctl.state = STATUS_IDLE; /* got a wrong data, drop it */
                }
                break;
            }
            case STATUS_DST:
            {
                frm_data.dst = *buf; /* store dst port */
                frm_ctl.state = STATUS_DATA_LEN; /* expect data len */
                break;
            }
            case STATUS_DATA_LEN:
            {
                frm_ctl.payload_len = *buf; /* store data len */
                frm_ctl.state = STATUS_DATA; /* expect data(data number = payload_len) */
                break;
            }
            case STATUS_DATA:
            {
                if (frm_ctl.idx < frm_ctl.payload_len)
                {
                    frm_ctl.tmp_buf[frm_ctl.idx++] = *buf;
                    if (frm_ctl.payload_len == frm_ctl.idx)
                    {
                        struct srtm_uart_chan *chan;
                        frm_data.data_len = frm_ctl.payload_len;
                        env_memcpy(frm_data.data, frm_ctl.tmp_buf, frm_data.data_len);
                        chan = SRTM_UartService_FindChanByUartId(frm_data.dst);
                        SRTM_UART_SendData(pAdapter, chan->chan, frm_data.data, frm_data.data_len);
                        frm_ctl.state = STATUS_IDLE; /* expect next frame data */
                    }
                }
                break;
            }
            default:
            {
                PRINTF("%s: %d: wrong state\r\n", __func__, __LINE__);
                break;
            }
        }
    }
}

void SRTM_Uart_ReceiverTask(void *pvParameters)
{
    serial_manager_status_t status = kStatus_SerialManager_Error;
    int i = 0;
    uint32_t read_bytes = 0;
    struct srtm_uart_chan *chan = NULL;
    serial_read_handle_t read_handle = (serial_read_handle_t)pvParameters;
    while(1)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        if (i + SRTM_UART_WANT_TO_READ_BYTES > sizeof(rx_buf))
        {
            i = 0;
        }
        status = SerialManager_TryRead(read_handle, &rx_buf[i], SRTM_UART_WANT_TO_READ_BYTES, &read_bytes);
        if (status == kStatus_SerialManager_Success && read_bytes > 0)
        {
           SRTM_UartService_FindChanBySerialReadHandle(read_handle, &chan);
           if (chan->flags & SRTM_UART_SUPPORT_MULTI_UART_MSG_FLAG) /* parse multi uart message protocol data */
           {
               SRTM_UART_ProcessData(&rx_buf[i], read_bytes);
           }
           else
           {
               SRTM_UART_SendData(pAdapter, chan->chan, &rx_buf[i], read_bytes);
           }
           i += read_bytes;
        }
    }
}

/* Both request and notify are called from SRTM dispatcher context */
/* Receive notify that from acore to mcore */
static srtm_status_t SRTM_UartService_ReceiveNotify(srtm_service_t service, srtm_notification_t notif)
{
    srtm_status_t status;
    srtm_uart_service_t handle  = (srtm_uart_service_t)(void *)service;
    srtm_uart_adapter_t adapter = handle->adapter;
    srtm_channel_t channel;
    uint8_t command;
    uint32_t payloadLen;
    struct _srtm_uart_payload *uartNotif;
    static uint8_t *data = NULL;
    uint8_t dataLen = 0;
    struct rpmsg_std_msg* msg = NULL;
    srtm_rpmsg_endpoint_t srtmEndpointHandle;
    struct multi_uart_msg* multi_ser_msg = NULL;
    static bool need_free_buf = false;
    uint8_t src_uart_id = SRTM_UART_INVALID_BUS_ID;

    assert(adapter);
    assert(service->dispatcher);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    channel    = SRTM_CommMessage_GetChannel(notif);
    srtmEndpointHandle = (srtm_rpmsg_endpoint_t)(void *)channel;
    command    = SRTM_CommMessage_GetCommand(notif);
    uartNotif     = (struct _srtm_uart_payload *)(void *)SRTM_CommMessage_GetPayload(notif);
    payloadLen = SRTM_CommMessage_GetPayloadLen(notif);

    status = SRTM_Service_CheckVersion(service, notif, SRTM_UART_VERSION);
    if ((status != SRTM_Status_Success) || (uartNotif == NULL))
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN, "%s format error!\r\n", __func__);
    }
    else
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO,
                           "SRTM receive UART request: cmd = 0x%x, busId = 0x%x, flags = 0x%x\n",
                           command, uartNotif->busId, uartNotif->flags);
        if (need_free_buf && data != NULL)
        {
            env_free_memory(data); /* free last malloc memory */
            data = NULL;
        }
        switch (command)
        {
            case SRTM_UART_CMD_SEND:
                assert(adapter->send);
                status = SRTM_UartService_FindUartIdByChannel(channel, &src_uart_id);
                if (status != SRTM_Status_Success)
                {
                    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN, "%s failed to find channel\r\n", __func__);
                    goto exit0;
                }
                if (uartNotif->flags & SRTM_UART_SUPPORT_RPMSG_OVER_UART_FLAG) /* send rpmsg over uart(uart) devices(currently not fully implementation, such as: need implement parse data when received rpmsg from uart) */
                {
                    dataLen = SRTM_RawData_GetDataLen(notif) + sizeof(struct rpmsg_std_msg) - 1;
                    msg = env_allocate_memory(dataLen);
                    assert(msg);
                    msg->hdr.src   = srtmEndpointHandle->rpmsgEndpoint->addr;
                    msg->hdr.dst   = srtmEndpointHandle->config.peerAddr;
                    msg->hdr.len   = (uint16_t)SRTM_RawData_GetDataLen(notif);
                    msg->hdr.flags = (uint16_t)RL_NO_FLAGS;
                    env_memcpy(&msg->data[0], SRTM_RawData_GetData(notif), SRTM_RawData_GetDataLen(notif));
                    data = (uint8_t *)msg;
                    need_free_buf = true;
                }
                else if (uartNotif->flags & SRTM_UART_SUPPORT_MULTI_UART_MSG_FLAG) /* multiple virtual tty mapped to one physical uart: add a header for peer side to choose which port is sent to */
                {
                    dataLen = payloadLen - (sizeof(struct _srtm_uart_payload) - sizeof(uartNotif->data[0]));
                    dataLen = dataLen + sizeof(struct multi_uart_msg_header);
                    multi_ser_msg = env_allocate_memory(dataLen);
                    assert(multi_ser_msg);
                    multi_ser_msg->header.preamble[0] = MULTI_UART_MSG_PREAMBLE0;
                    multi_ser_msg->header.preamble[1] = MULTI_UART_MSG_PREAMBLE1;
                    multi_ser_msg->header.preamble[2] = MULTI_UART_MSG_PREAMBLE2;
                    multi_ser_msg->header.preamble[3] = MULTI_UART_MSG_PREAMBLE3;
                    data = (uint8_t *)multi_ser_msg;
                    need_free_buf = true;
                    if (uartNotif->flags & SRTM_UART_SPECIFY_PORT_NUM_MASK) /* /dev/ttyRPMSG3 <---> /dev/ttyRPMSG7(dst_uart_id = 7), src uart id(3) != dst uart id(7) */
                    {
                        multi_ser_msg->header.dst_uart_id = (uartNotif->flags & SRTM_UART_PORT_NUM_MASK) >> SRTM_UART_PORT_NUM_SHIFT;
                    }
                    else /* /dev/ttyRPMSG3(first board) --> /dev/ttyRPMSG3(second board), src uart id(3) == dst uart id(3) */
                    {
                        multi_ser_msg->header.dst_uart_id = src_uart_id;
                    }
                    multi_ser_msg->header.data_len = payloadLen - (sizeof(struct _srtm_uart_payload) - sizeof(uartNotif->data[0]));
                    env_memcpy(&multi_ser_msg->data[0], &uartNotif->data[0], multi_ser_msg->header.data_len);
                }
                else /* one virtual tty mapped to one physical uart: pure user data from linux user space, use case: real uart on mcore side is directly conneted to a gps device */
                {
                    if (uartNotif->busId != SRTM_UART_INVALID_BUS_ID)
                    {
                        uint32_t cnt;
                        struct srtm_uart_chan *chan = NULL;

                        /* check relationship between virtual tty and physical uart */
                        cnt = SRTM_UartService_GetChannelsNumberBindToBusId(uartNotif->busId);
                        assert(cnt <= 1); /* one virtual tty mapped to one physical uart will be okay, if assert here, pls make sure that one physical uart is only bind to one virtual tty */
                        if (cnt == 1) /* There is one virtual tty that mapped to the physical uart, so need check whether current channel is equal to the virtual tty to guarantee that only one virtual tty mapped to the physical uart  */
                        {
                            SRTM_UartService_FindChanByBusId(uartNotif->busId, &chan);
                            assert(chan->chan == channel); /* make sure that only one virtual tty is bond to one physical uart */
                        }
                    }
                    data = (uint8_t *)&uartNotif->data[0];
                    dataLen = payloadLen - (sizeof(struct _srtm_uart_payload) - sizeof(uartNotif->data[0]));
                    need_free_buf = false;
                }

                SRTM_UartService_BindChanByUartId(NULL, uartNotif->busId, uartNotif->flags, src_uart_id);
                if (uartNotif->busId == SRTM_UART_INVALID_BUS_ID) /* directly print */
                {
                    data[dataLen - 1] = 0;
                    PRINTF("%s: %d, data = %s\r\n", __func__, __LINE__, data);
                    goto exit0;
                }
                else
                {
                    assert(adapter->send != NULL);
                    status = adapter->send(adapter, uartNotif->busId, data, dataLen); /* non blocking transfer mode */
                    goto exit1;
                }
                break;
            default:
                SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN, "%s: command %d unsupported\r\n", __func__, command);
                status = SRTM_Status_InvalidMessage;
                break;
        }
    }

exit0:
    if (need_free_buf && data)
    {
       env_free_memory(data);
       data = NULL;
    }
exit1:
    return status; /* no response from local core to remote core */
}

/* Receive Request that from acore to mcore(currently don't have command that need send response from mcore to acore) */
static srtm_status_t SRTM_UartService_ReceiveRequest(srtm_service_t service, srtm_request_t request)
{
    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN, "%s: command %d unsupported\r\n", __func__,
                       SRTM_CommMessage_GetCommand(request));

    return SRTM_Status_ServiceNotFound;
}

static srtm_status_t SRTM_UartService_SendNotify(srtm_service_t service, srtm_channel_t chan, uint8_t *data, uint16_t data_len)
{
    srtm_uart_service_t handle = (srtm_uart_service_t)service;
    srtm_notification_t notif;
    struct _srtm_uart_payload *payload;

    assert(service);
    notif = SRTM_Notification_Create(chan, SRTM_UART_CATEGORY, SRTM_UART_VERSION, SRTM_UART_CMD_SEND, (uint16_t)sizeof(struct _srtm_uart_payload) - 1 + data_len); /* 1: struct _srtm_uart_payload occupy one byte for first data */
    if (notif == NULL)
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "%s: alloc notification failed.\r\n", __func__);
        return SRTM_Status_OutOfMemory;
    }
    payload        = (struct _srtm_uart_payload *)(void *)SRTM_CommMessage_GetPayload(notif);
    payload->busId  = (uint8_t)SRTM_UART_INVALID_BUS_ID; /* when send data from mcore to acore, don't need check bus id */
    env_memcpy(payload->data, data, data_len);
    SRTM_Dispatcher_DeliverNotification(handle->service.dispatcher, notif);

    return SRTM_Status_Success;
}

void SRTM_UartService_Destroy(srtm_service_t service)
{
    srtm_uart_service_t handle = (srtm_uart_service_t)(void *)service;

    assert(service);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    /* Service must be unregistered from dispatcher before destroy */
    assert(SRTM_List_IsEmpty(&service->node));

    SRTM_Heap_Free(handle);
}

srtm_service_t SRTM_UartService_Create(srtm_uart_adapter_t adapter)
{
    srtm_uart_service_t handle;

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    handle = (srtm_uart_service_t)SRTM_Heap_Malloc(sizeof(struct _srtm_uart_service));
    assert(handle);

    SRTM_UartService_InitChan();

    adapter->service = &handle->service;
    adapter->sendNotify = SRTM_UartService_SendNotify;
    adapter->bindChanByUartId = SRTM_UartService_BindChanByUartId;
    handle->adapter = adapter;
    pAdapter = adapter;

    SRTM_List_Init(&handle->service.node);
    handle->service.dispatcher = NULL;
    handle->service.category   = SRTM_UART_CATEGORY;
    handle->service.destroy    = SRTM_UartService_Destroy;
    handle->service.request    = SRTM_UartService_ReceiveRequest; /* receive request from acore and send response to acore */
    handle->service.notify     = SRTM_UartService_ReceiveNotify; /* receive notify from acore */

    return &handle->service;
}
