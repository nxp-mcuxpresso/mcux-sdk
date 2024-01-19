/*
 * Copyright 2018-2021, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <string.h>
#include <assert.h>
#include <string.h>

#include "fsl_common.h"

#include "srtm_heap.h"
#include "srtm_list.h"
#include "srtm_dispatcher.h"
#include "srtm_service.h"
#include "srtm_service_struct.h"
#include "srtm_i2c_service.h"
#include "srtm_message.h"
#include "srtm_message_struct.h"
#include "srtm_channel.h"
#include "srtm_channel_struct.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Protocol definition */
#define SRTM_I2C_CATEGORY (0x9U)
#define SRTM_I2C_VERSION  (0x0100U)

#define SRTM_I2C_RETURN_CODE_SUCEESS     (0x0U)
#define SRTM_I2C_RETURN_CODE_FAIL        (0x1U)
#define SRTM_I2C_RETURN_CODE_UNSUPPORTED (0x2U)

typedef struct _srtm_i2c_service
{
    struct _srtm_service service;
    srtm_i2c_adapter_t adapter;
} *srtm_i2c_service_t;

static srtm_status_t SRTM_I2CService_Request(srtm_service_t service, srtm_request_t request);
static srtm_status_t SRTM_I2CService_Notify(srtm_service_t service, srtm_notification_t notif);

static i2c_bus_t SRTM_I2C_SearchBus(srtm_i2c_adapter_t adapter, uint8_t busID)
{
    uint8_t bus_num    = adapter->bus_structure.bus_num;
    i2c_bus_t busArray = adapter->bus_structure.buses;
    uint8_t i;

    for (i = 0U; i != bus_num; i++)
    {
        if (busArray[i].bus_id == busID)
        {
            break;
        }
    }

    return (i == bus_num) ? NULL : (busArray + i);
}

static srtm_status_t SRTM_I2CService_ReadBus(
    srtm_service_t service, uint8_t busID, uint16_t slaveAddr, uint8_t *buf, uint16_t len, uint16_t flags)
{
    srtm_i2c_service_t handle  = (srtm_i2c_service_t)(void *)service;
    srtm_i2c_adapter_t adapter = handle->adapter;
    i2c_bus_t targetBus;
    uint32_t base_addr;
    uint8_t switch_index;
    uint16_t switch_addr;
    srtm_i2c_switch_channel switch_channel;
    srtm_status_t status;
    srtm_i2c_type_t type;
    i2c_switch_t switch_inst;

    targetBus    = SRTM_I2C_SearchBus(adapter, busID);
    base_addr    = targetBus->base_addr;
    switch_index = targetBus->switch_idx;
    type         = targetBus->type;
    /*
     * Switch Channel
     */
    if (switch_index < adapter->bus_structure.switch_num)
    {
        switch_inst    = &adapter->bus_structure.switches[switch_index];
        switch_addr    = switch_inst->slaveAddr;
        switch_channel = targetBus->switch_channel;
        if (switch_inst->cur_channel != switch_channel)
        {
            (void)adapter->switchchannel(adapter, base_addr, type, switch_addr, switch_channel);
            switch_inst->cur_channel = switch_channel;
        }
    }
    /*
     * Read
     */
    status = adapter->read(adapter, base_addr, type, slaveAddr, buf, len, flags); // APP_SRTM_I2C_Read
    return status;
}

static srtm_status_t SRTM_I2CService_WriteBus(
    srtm_service_t service, uint8_t busID, uint16_t slaveAddr, uint8_t *buf, uint16_t len, uint16_t flags)
{
    srtm_i2c_service_t handle  = (srtm_i2c_service_t)(void *)service;
    srtm_i2c_adapter_t adapter = handle->adapter;
    i2c_bus_t targetBus;
    uint32_t base_addr;
    uint8_t switch_index;
    uint16_t switch_addr;
    srtm_i2c_switch_channel switch_channel;
    srtm_status_t status;
    srtm_i2c_type_t type;
    i2c_switch_t switch_inst;

    targetBus    = SRTM_I2C_SearchBus(adapter, busID);
    base_addr    = targetBus->base_addr;
    switch_index = targetBus->switch_idx;
    type         = targetBus->type;
    /*
     * Switch Channel
     */
    if (switch_index < adapter->bus_structure.switch_num)
    {
        switch_inst    = &adapter->bus_structure.switches[switch_index];
        switch_addr    = switch_inst->slaveAddr;
        switch_channel = targetBus->switch_channel;
        if (switch_inst->cur_channel != switch_channel)
        {
            (void)adapter->switchchannel(adapter, base_addr, type, switch_addr, switch_channel);
            switch_inst->cur_channel = switch_channel;
        }
    }
    /*
     * Write
     */
    status = adapter->write(adapter, base_addr, type, slaveAddr, buf, len, flags); // APP_SRTM_I2C_Write
    return status;
}

srtm_service_t SRTM_I2CService_Create(srtm_i2c_adapter_t adapter)
{
    srtm_i2c_service_t handle;

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);
    handle = (srtm_i2c_service_t)SRTM_Heap_Malloc(sizeof(struct _srtm_i2c_service));
    assert(handle);

    adapter->service = &handle->service;
    handle->adapter  = adapter;

    SRTM_List_Init(&handle->service.node);
    handle->service.dispatcher = NULL;
    handle->service.category   = SRTM_I2C_CATEGORY;
    handle->service.destroy    = SRTM_I2CService_Destroy;
    handle->service.request    = SRTM_I2CService_Request;
    handle->service.notify     = SRTM_I2CService_Notify;

    return &handle->service;
}

void SRTM_I2CService_Destroy(srtm_service_t service)
{
    srtm_i2c_service_t handle = (srtm_i2c_service_t)(void *)service;

    assert(service);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    /* Service must be unregistered from dispatcher before destroy */
    assert(SRTM_List_IsEmpty(&service->node));

    SRTM_Heap_Free(handle);
}

void SRTM_I2CService_Reset(srtm_service_t service, srtm_peercore_t core)
{
    assert(service);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);
}

static srtm_status_t SRTM_I2CService_Request(srtm_service_t service, srtm_request_t request)
{
    srtm_status_t status;
    srtm_channel_t channel;
    uint8_t command;
    uint32_t payloadLen;
    srtm_response_t response;
    struct _srtm_i2c_payload *i2cReq;
    struct _srtm_i2c_payload *i2cResp;

    assert(service->dispatcher);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    channel    = SRTM_CommMessage_GetChannel(request);
    command    = SRTM_CommMessage_GetCommand(request);
    i2cReq     = (struct _srtm_i2c_payload *)(void *)SRTM_CommMessage_GetPayload(request);
    payloadLen = SRTM_CommMessage_GetPayloadLen(request);
    (void)payloadLen; /* try to fix warning: variable 'payloadLen' set but not used */
    assert(i2cReq);
    assert((uint32_t)(i2cReq->len + sizeof(struct _srtm_i2c_payload) - sizeof(i2cReq->data[0])) <= payloadLen);

    response =
        SRTM_Response_Create(channel, SRTM_I2C_CATEGORY, SRTM_I2C_VERSION, command,
                             (uint16_t)((sizeof(struct _srtm_i2c_payload) - sizeof(i2cReq->data[0])) + i2cReq->len));
    if (response == NULL)
    {
        return SRTM_Status_OutOfMemory;
    }

    i2cResp = (struct _srtm_i2c_payload *)(void *)SRTM_CommMessage_GetPayload(response);

    status = SRTM_Service_CheckVersion(service, request, SRTM_I2C_VERSION);
    if (status != SRTM_Status_Success)
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN, "%s: format error!\r\n", __func__);
        i2cResp->retCode = SRTM_I2C_RETURN_CODE_UNSUPPORTED;
    }
    else
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO,
                           "SRTM receive I2C request:cmd=%x, busID %d, slaveAddr 0x%x!, data %d bytes\r\n", command,
                           i2cReq->busID, i2cReq->slaveAddr, i2cReq->len);
        (void)memcpy(i2cResp, i2cReq,
                     (sizeof(struct _srtm_i2c_payload) - sizeof(i2cReq->data[0]) + (size_t)i2cReq->len));

        switch (command)
        {
            case (uint8_t)SRTM_I2C_CMD_READ:
                status = SRTM_I2CService_ReadBus(service, i2cResp->busID, i2cResp->slaveAddr, i2cResp->data,
                                                 i2cReq->len, i2cReq->flags);
                i2cResp->retCode =
                    status == SRTM_Status_Success ? SRTM_I2C_RETURN_CODE_SUCEESS : SRTM_I2C_RETURN_CODE_FAIL;
                break;
            case (uint8_t)SRTM_I2C_CMD_WRITE:
                status = SRTM_I2CService_WriteBus(service, i2cResp->busID, i2cResp->slaveAddr, i2cResp->data,
                                                  i2cReq->len, i2cReq->flags);
                i2cResp->retCode =
                    status == SRTM_Status_Success ? SRTM_I2C_RETURN_CODE_SUCEESS : SRTM_I2C_RETURN_CODE_FAIL;
                break;
            default:
                SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN, "%s: command %d unsupported!\r\n", __func__, command);
                assert(false);
                break;
        }
    }

    return SRTM_Dispatcher_DeliverResponse(service->dispatcher, response);
}

static srtm_status_t SRTM_I2CService_Notify(srtm_service_t service, srtm_notification_t notif)
{
    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN, "%s: command %d unsupported!\r\n", __func__,
                       SRTM_CommMessage_GetCommand(notif));

    return SRTM_Status_ServiceNotFound;
}

static void SRTM_I2C_HandleBusRead(srtm_dispatcher_t dispatcher, void *param1, void *param2)
{
    srtm_status_t status;
    srtm_i2c_payload_t i2c_payload = (srtm_i2c_payload_t)param1;
    srtm_service_t service         = (srtm_service_t)param2;
    status = SRTM_I2CService_ReadBus(service, i2c_payload->busID, i2c_payload->slaveAddr, i2c_payload->data,
                                     (uint8_t)i2c_payload->len, i2c_payload->flags);
    i2c_payload->retCode = (status == SRTM_Status_Success) ? SRTM_I2C_RETURN_CODE_SUCEESS : SRTM_I2C_RETURN_CODE_FAIL;
}

static void SRTM_I2C_HandleBusWrite(srtm_dispatcher_t dispatcher, void *param1, void *param2)
{
    srtm_status_t status;
    srtm_i2c_payload_t i2c_payload = (srtm_i2c_payload_t)param1;
    srtm_service_t service         = (srtm_service_t)param2;
    status = SRTM_I2CService_WriteBus(service, i2c_payload->busID, i2c_payload->slaveAddr, i2c_payload->data,
                                      (uint8_t)i2c_payload->len, i2c_payload->flags);
    i2c_payload->retCode = (status == SRTM_Status_Success) ? SRTM_I2C_RETURN_CODE_SUCEESS : SRTM_I2C_RETURN_CODE_FAIL;
}

srtm_status_t SRTM_I2C_RequestBusRead(
    srtm_service_t service, uint8_t busID, uint16_t slaveAddr, uint8_t *buf, uint16_t len)
{
    srtm_request_t request;
    srtm_status_t status;
    srtm_i2c_payload_t i2cReq;
    srtm_procedure_t proc;
    /*
     * Allocate an SRTM message and copy necessary information
     */
    request           = SRTM_Request_Create(NULL, SRTM_I2C_CATEGORY, SRTM_I2C_VERSION, (uint8_t)SRTM_I2C_CMD_READ,
                                            (uint16_t)((sizeof(struct _srtm_i2c_payload) - sizeof(uint8_t)) + len));
    i2cReq            = (struct _srtm_i2c_payload *)(void *)SRTM_CommMessage_GetPayload(request);
    i2cReq->busID     = busID;
    i2cReq->slaveAddr = slaveAddr;
    i2cReq->len       = len;
    (void)memset(i2cReq->data, 0, len);
    /*
     * Call proc in sync manner
     */
    proc = SRTM_Procedure_Create(SRTM_I2C_HandleBusRead, i2cReq, service);
    (void)SRTM_Dispatcher_CallProc(service->dispatcher, proc, SRTM_WAIT_FOR_EVER); /*synchronized call*/
    /*
     * Save proc exec result
     */
    (void)memcpy(buf, i2cReq->data, len);
    status = (srtm_status_t)i2cReq->retCode;
    /*
     * Clean the allocated SRTM object
     */
    SRTM_Procedure_Destroy(proc);
    SRTM_Response_Destroy(request);

    return status;
}

srtm_status_t SRTM_I2C_RequestBusWrite(
    srtm_service_t service, uint8_t busID, uint16_t slaveAddr, uint8_t *buf, uint16_t len, uint8_t needStop)
{
    srtm_request_t request;
    srtm_status_t status;
    srtm_i2c_payload_t i2cReq;
    srtm_procedure_t proc;
    /*
     * Allocate an SRTM message and copy necessary information
     */
    request           = SRTM_Request_Create(NULL, SRTM_I2C_CATEGORY, SRTM_I2C_VERSION, (uint8_t)SRTM_I2C_CMD_WRITE,
                                            (uint16_t)((sizeof(struct _srtm_i2c_payload) - sizeof(uint8_t)) + len));
    i2cReq            = (struct _srtm_i2c_payload *)(void *)SRTM_CommMessage_GetPayload(request);
    i2cReq->busID     = busID;
    i2cReq->slaveAddr = slaveAddr;
    i2cReq->len       = len;
    i2cReq->flags     = needStop > 0U ? (SRTM_I2C_FLAG_NEED_STOP) : 0U;

    (void)memcpy(i2cReq->data, buf, len);
    /*
     * Call proc in sync manner
     */
    proc = SRTM_Procedure_Create(SRTM_I2C_HandleBusWrite, i2cReq, service);
    (void)SRTM_Dispatcher_CallProc(service->dispatcher, proc, SRTM_WAIT_FOR_EVER); /*synchronized call*/
    /*
     * Save proc exec result
     */
    status = (srtm_status_t)i2cReq->retCode;
    /*
     * Clean the allocated SRTM object
     */
    SRTM_Procedure_Destroy(proc);
    SRTM_Response_Destroy(request);

    return status;
}
