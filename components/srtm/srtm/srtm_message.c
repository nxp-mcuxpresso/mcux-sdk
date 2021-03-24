/*
 * Copyright 2017, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>
#include <assert.h>

#include "srtm_message_pool.h"
#include "srtm_message.h"
#include "srtm_message_struct.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
srtm_message_t SRTM_Message_Create(uint32_t len)
{
    srtm_message_t msg;

    msg = (srtm_message_t)SRTM_MessagePool_Alloc(sizeof(struct _srtm_message) + len);
    if (msg != NULL)
    {
#ifdef SRTM_ZEROIZE_MESSAGE_DATA
        (void)memset(msg, 0, sizeof(struct _srtm_message) + len);
#else
        (void)memset(msg, 0, sizeof(struct _srtm_message));
#endif
        msg->dataLen = len;
        if (len > 0UL) /* Data exists */
        {
            msg->data = msg + 1;
        }
        SRTM_List_Init(&msg->node);
    }

    return msg;
}

srtm_message_t SRTM_Message_Duplicate(srtm_message_t msg)
{
    srtm_message_t dup;

    assert(msg);

    dup = (srtm_message_t)SRTM_MessagePool_Alloc(sizeof(struct _srtm_message) + msg->dataLen);

    if (dup != NULL)
    {
        (void)memcpy(dup, msg, sizeof(struct _srtm_message));
        if (msg->dataLen != 0UL) /* Data exists */
        {
            dup->data = dup + 1;
        }
        SRTM_List_Init(&dup->node);
    }

    return dup;
}

void SRTM_Message_Destroy(srtm_message_t message)
{
    assert(message);

    if (message->free != NULL)
    {
        message->free(message, message->freeParam);
    }
    else
    {
        SRTM_MessagePool_Free(message);
    }
}

static srtm_message_t SRTM_CommMessage_Create(srtm_message_type_t type,
                                              srtm_message_direct_t direct,
                                              srtm_channel_t channel,
                                              uint8_t category,
                                              uint16_t version,
                                              uint8_t command,
                                              uint16_t payloadLen)
{
    srtm_message_t msg;
    srtm_packet_head_t *head;
    uint32_t dataLen = (uint32_t)sizeof(struct _srtm_packet_head) + payloadLen;

    msg = SRTM_Message_Create(dataLen);

    if (msg != NULL)
    {
        msg->type    = type;
        msg->direct  = direct;
        msg->channel = channel;

        head               = (srtm_packet_head_t *)(msg->data);
        head->category     = category;
        head->majorVersion = (uint8_t)SRTM_MESSAGE_MAJOR_VERSION(version);
        head->minorVersion = (uint8_t)SRTM_MESSAGE_MINOR_VERSION(version);
        head->type         = (uint8_t)type;
        head->command      = command;
        head->priority     = msg->priority;
    }

    return msg;
}

static void SRTM_CommMessage_Destroy(srtm_message_t message)
{
    SRTM_Message_Destroy(message);
}

static srtm_packet_head_t *SRTM_CommMessage_GetPacketHead(srtm_message_t message)
{
    srtm_packet_head_t *head;

    assert(message);
    assert(message->data);

    head = (srtm_packet_head_t *)(message->data);

    return head;
}

srtm_procedure_t SRTM_Procedure_Create(srtm_message_proc_cb_t procedure, void *param1, void *param2)
{
    srtm_message_t msg = SRTM_Message_Create(0);

    if (msg != NULL)
    {
        msg->type           = SRTM_MessageTypeProcedure;
        msg->direct         = SRTM_MessageDirectNone;
        msg->procMsg.cb     = procedure;
        msg->procMsg.param1 = param1;
        msg->procMsg.param2 = param2;
    }

    return msg;
}

void SRTM_Procedure_Destroy(srtm_procedure_t procedure)
{
    SRTM_Message_Destroy(procedure);
}

srtm_rawdata_t SRTM_RawData_Create(srtm_channel_t channel, uint32_t dataLen)
{
    srtm_message_t msg;

    msg = SRTM_Message_Create(dataLen);

    if (msg != NULL)
    {
        msg->type    = SRTM_MessageTypeRawData;
        msg->direct  = SRTM_MessageDirectTx;
        msg->channel = channel;
    }

    return msg;
}

void SRTM_RawData_Destroy(srtm_rawdata_t data)
{
    SRTM_Message_Destroy(data);
}

void *SRTM_RawData_GetData(srtm_rawdata_t data)
{
    assert(data);

    return data->data;
}

uint32_t SRTM_RawData_GetDataLen(srtm_rawdata_t data)
{
    assert(data);

    return data->dataLen;
}

srtm_request_t SRTM_Request_Create(
    srtm_channel_t channel, uint8_t category, uint16_t version, uint8_t command, uint16_t payloadLen)
{
    return SRTM_CommMessage_Create(SRTM_MessageTypeRequest, SRTM_MessageDirectTx, channel, category, version, command,
                                   payloadLen);
}

void SRTM_Request_Destroy(srtm_request_t request)
{
    SRTM_CommMessage_Destroy(request);
}

srtm_status_t SRTM_Request_GetErrorCode(srtm_request_t request)
{
    assert(request);

    return request->error;
}

srtm_response_t SRTM_Response_Create(
    srtm_channel_t channel, uint8_t category, uint16_t version, uint8_t command, uint16_t payloadLen)
{
    return SRTM_CommMessage_Create(SRTM_MessageTypeResponse, SRTM_MessageDirectTx, channel, category, version, command,
                                   payloadLen);
}

void SRTM_Response_Destroy(srtm_response_t response)
{
    SRTM_CommMessage_Destroy(response);
}

srtm_notification_t SRTM_Notification_Create(
    srtm_channel_t channel, uint8_t category, uint16_t version, uint8_t command, uint16_t payloadLen)
{
    return SRTM_CommMessage_Create(SRTM_MessageTypeNotification, SRTM_MessageDirectTx, channel, category, version,
                                   command, payloadLen);
}

void SRTM_Notification_Destroy(srtm_notification_t notification)
{
    SRTM_CommMessage_Destroy(notification);
}

uint8_t SRTM_Message_GetPriority(srtm_message_t message)
{
    assert(message);

    return message->priority;
}

void SRTM_Message_SetPriority(srtm_message_t message, uint8_t priority)
{
    srtm_packet_head_t *head;
    assert(message);

    message->priority = priority;
    if (message->type < SRTM_MessageTypeCommLast)
    {
        head           = SRTM_CommMessage_GetPacketHead(message);
        head->priority = priority;
    }
}

void SRTM_Message_SetFreeFunc(srtm_message_t message, srtm_message_free_t func, void *param)
{
    assert(message);

    message->free      = func;
    message->freeParam = param;
}

uint8_t SRTM_CommMessage_GetCategory(srtm_message_t message)
{
    srtm_packet_head_t *head = SRTM_CommMessage_GetPacketHead(message);

    return head->category;
}

uint16_t SRTM_CommMessage_GetVersion(srtm_message_t message)
{
    srtm_packet_head_t *head = SRTM_CommMessage_GetPacketHead(message);

    return (((uint16_t)(head->majorVersion)) << 8U) | head->minorVersion;
}

uint8_t SRTM_CommMessage_GetCommand(srtm_message_t message)
{
    srtm_packet_head_t *head = SRTM_CommMessage_GetPacketHead(message);

    return head->command;
}

uint8_t *SRTM_CommMessage_GetPayload(srtm_message_t message)
{
    assert(message);
    assert(message->data);

    return (uint8_t *)((srtm_packet_head_t *)(message->data) + 1);
}

uint32_t SRTM_CommMessage_GetPayloadLen(srtm_message_t message)
{
    assert(message);
    assert(message->dataLen >= sizeof(struct _srtm_packet_head));

    return message->dataLen - sizeof(struct _srtm_packet_head);
}

srtm_channel_t SRTM_CommMessage_GetChannel(srtm_message_t message)
{
    return message->channel;
}
