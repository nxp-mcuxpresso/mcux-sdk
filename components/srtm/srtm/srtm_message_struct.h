/*
 * Copyright 2017, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SRTM_MESSAGE_STRUCT_H__
#define __SRTM_MESSAGE_STRUCT_H__

#include "srtm_defs.h"
#include "srtm_dispatcher.h"
#include "srtm_sem.h"
#include "srtm_list.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/**
 * @brief SRTM message type fields
 */
typedef enum _srtm_message_type
{
    SRTM_MessageTypeRequest = 0x00U, /*!< Request message */
    SRTM_MessageTypeResponse,        /*!< Response message for certain Request */
    SRTM_MessageTypeNotification,    /*!< Notification message that doesn't require response */
    SRTM_MessageTypeCommLast,        /*!< Last value of communication message */

    SRTM_MessageTypeProcedure = 0x40, /*!< Local procedure */
    SRTM_MessageTypeRawData   = 0x41, /*!< Raw data message */
} srtm_message_type_t;

/**
 * @brief SRTM message direction fields
 */
typedef enum _srtm_message_direct
{
    SRTM_MessageDirectNone = 0x00U, /*!< Local procedure message has no direction */
    SRTM_MessageDirectRx,           /*!< Received message */
    SRTM_MessageDirectTx,           /*!< Transfer message */
} srtm_message_direct_t;

SRTM_ANON_DEC_BEGIN

/**
 * @brief SRTM message structure
 */
typedef struct _srtm_message
{
    srtm_list_t node;             /*!< SRTM message list node to link to a list */
    srtm_message_type_t type;     /*!< SRTM message type */
    srtm_message_direct_t direct; /*!< SRTM message direction */
    void *data;                   /*!< SRTM raw data, including header and payload for CommMessage */
    uint32_t dataLen;             /*!< SRTM raw data bytes */
    srtm_channel_t channel;       /*!< SRTM communication channel */
    srtm_status_t error;          /*!< SRTM message error status */
    uint8_t priority;             /*!< SRTM message priority */
    srtm_message_free_t free;     /*!< SRTM user defined message free function */
    void *freeParam;              /*!< SRTM user defined message free param */

    union
    {
        struct
        {
            srtm_message_proc_cb_t cb; /*!< SRTM procedure message callabck function */
            void *param1;              /*!< SRTM procedure message callabck parameter */
            void *param2;              /*!< SRTM procedure message callabck parameter */
            srtm_sem_t sig;            /*!< SRTM procedure message signal to wait for procedure finish */
        } procMsg;
        struct
        {
            bool isSyncReq; /*!< Flag to indicate synchronized request */
            union
            {
                struct
                {
                    srtm_sem_t sig;       /*!< SRTM request message signal to wait for response */
                    srtm_response_t resp; /*!< SRTM request message response */
                } sync;                   /*!< SRTM request message from SRTM_Request() */
                struct
                {
                    srtm_dispatcher_resp_cb_t cb; /*!< SRTM request message response callabck */
                    void *param;                  /*!< SRTM request message response callabck parameter */
                } async;                          /*!< SRTM request message from SRTM_Deliver_Request() */
            };
        } reqMsg;
        struct
        {
            uint32_t dummy; /*!< SRTM response message unused field */
        } rspMsg;
        struct
        {
            uint32_t dummy; /*!< SRTM notification message unused field */
        } ntfMsg;
    };
} srtm_message;

/**
 * @brief SRTM communication packet head
 */
typedef SRTM_PACKED_BEGIN struct _srtm_packet_head
{
    union
    {
        struct
        {
            uint8_t category;
            uint8_t majorVersion;
            uint8_t minorVersion;
            uint8_t type;
            uint8_t command;
            uint8_t priority;
            uint8_t reserved[4U];
        };
        uint8_t header[10U];
    };
} SRTM_PACKED_END srtm_packet_head_t;

SRTM_ANON_DEC_END

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Create SRTM base message.
 *
 * @param len the data length in bytes.
 * @return SRTM base message handle, or NULL on failure.
 */
srtm_message_t SRTM_Message_Create(uint32_t len);

/*!
 * @brief Duplicate a SRTM message.
 *
 * @param msg The message to duplicate.
 * @return SRTM message handle, or NULL on failure.
 */
srtm_message_t SRTM_Message_Duplicate(srtm_message_t msg);

/*!
 * @brief Destroy SRTM base message.
 *
 * @param message SRTM base message handle.
 */
void SRTM_Message_Destroy(srtm_message_t message);

#ifdef __cplusplus
}
#endif

#endif /* __SRTM_MESSAGE_STRUCT_H__ */
