/*
 * Copyright 2017, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SRTM_MESSAGE_H__
#define __SRTM_MESSAGE_H__

#include "srtm_defs.h"

/*!
 * @addtogroup srtm
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Get SRTM major version */
#define SRTM_MESSAGE_MAJOR_VERSION(ver) (((uint16_t)((ver)&0xFF00U)) >> 8U)
/*! @brief Get SRTM minor version */
#define SRTM_MESSAGE_MINOR_VERSION(ver) ((uint16_t)((ver)&0xFFU))

/**
 * @brief SRTM local procedure callback function
 */
typedef void (*srtm_message_proc_cb_t)(srtm_dispatcher_t dispatcher, void *param1, void *param2);

/**
 * @brief SRTM free function pointer
 */
typedef void (*srtm_message_free_t)(srtm_message_t message, void *param);

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Create SRTM local procedure message.
 *
 * @param procedure local procedure callback.
 * @param param1 user parameter 1 for the procedure callback.
 * @param param2 user parameter 2 for the procedure callback.
 * @return SRTM request handle, or NULL on failure.
 */
srtm_procedure_t SRTM_Procedure_Create(srtm_message_proc_cb_t procedure, void *param1, void *param2);

/*!
 * @brief Destroy SRTM local procedure message.
 *
 * @param procedure SRTM local procedure handle.
 */
void SRTM_Procedure_Destroy(srtm_procedure_t procedure);

/*!
 * @brief Create SRTM raw data message.
 *
 * @param channel corresponding SRTM channel the rawdata is from/to.
 * @param dataLen the raw data length in bytes.
 * @return SRTM raw data message handle, or NULL on failure.
 */
srtm_rawdata_t SRTM_RawData_Create(srtm_channel_t channel, uint32_t dataLen);

/*!
 * @brief Destroy SRTM raw data message.
 *
 * @param procedure SRTM raw data message handle.
 */
void SRTM_RawData_Destroy(srtm_rawdata_t data);

/*!
 * @brief Get SRTM data address of raw data message.
 *
 * @param message SRTM raw data message handle.
 * @return SRTM raw data address.
 */
void *SRTM_RawData_GetData(srtm_rawdata_t data);

/*!
 * @brief Get SRTM data length in bytes of raw data message.
 *
 * @param message SRTM raw data message handle.
 * @return SRTM raw data length in bytes.
 */
uint32_t SRTM_RawData_GetDataLen(srtm_rawdata_t data);

/*!
 * @brief Create SRTM request message.
 *
 * @param channel corresponding SRTM channel the request is from/to.
 * @param category SRTM application protocol category.
 * @param version SRTM application protocol version for the category.
 * @param command SRTM application protocol command for the category.
 * @param payloadLen SRTM application protocol payload.
 * @return SRTM request handle, or NULL on failure.
 */
srtm_request_t SRTM_Request_Create(
    srtm_channel_t channel, uint8_t category, uint16_t version, uint8_t command, uint16_t payloadLen);

/*!
 * @brief Destroy SRTM request message.
 *
 * @param request SRTM request handle.
 */
void SRTM_Request_Destroy(srtm_request_t request);

/*!
 * @brief Get request error code.
 *
 * Used in asynchronous request with callback response to indicate the request status.
 *
 * @param request SRTM request handle.
 * @return Error code for the request.
 */
srtm_status_t SRTM_Request_GetErrorCode(srtm_request_t request);

/*!
 * @brief Create SRTM response message.
 *
 * @param channel corresponding SRTM channel the response is from/to.
 * @param category SRTM application protocol category.
 * @param version SRTM application protocol version for the category.
 * @param command SRTM application protocol command for the category.
 * @param payloadLen SRTM application protocol payload.
 * @return SRTM response handle, or NULL on failure.
 */
srtm_response_t SRTM_Response_Create(
    srtm_channel_t channel, uint8_t category, uint16_t version, uint8_t command, uint16_t payloadLen);

/*!
 * @brief Destroy SRTM response message.
 *
 * @param response SRTM response handle.
 */
void SRTM_Response_Destroy(srtm_response_t response);

/*!
 * @brief Create SRTM notification message.
 *
 * @param channel corresponding SRTM channel the notification is from/to.
 * @param category SRTM application protocol category.
 * @param version SRTM application protocol version for the category.
 * @param command SRTM application protocol command for the category.
 * @param payloadLen SRTM application protocol payload length.
 * @return SRTM notification handle, or NULL on failure.
 */
srtm_notification_t SRTM_Notification_Create(
    srtm_channel_t channel, uint8_t category, uint16_t version, uint8_t command, uint16_t payloadLen);

/*!
 * @brief Destroy SRTM notification message.
 *
 * @param notification SRTM notification handle.
 */
void SRTM_Notification_Destroy(srtm_notification_t notification);

/*!
 * @brief Get SRTM priority of the message.
 *
 * @param message SRTM message handle.
 * @return SRTM priority value.
 */
uint8_t SRTM_Message_GetPriority(srtm_message_t message);

/*!
 * @brief Set SRTM priority of the message.
 *
 * @param message SRTM message handle.
 * @param priority SRTM message priority.
 */
void SRTM_Message_SetPriority(srtm_message_t message, uint8_t priority);

/*!
 * @brief Set SRTM message free function.
 * This is useful if the application want to reuse messages to avoid heap fragment. For example, user may
 * create messages and recycle them in a list with this user defined free function.
 *
 * @param message SRTM message handle.
 * @param func SRTM message free function.
 * @param param SRTM message free parameter.
 */
void SRTM_Message_SetFreeFunc(srtm_message_t message, srtm_message_free_t func, void *param);

/*!
 * @brief Get SRTM category of request/response/notification message.
 *
 * @param message SRTM request/response/notification message handle.
 * @return SRTM category value.
 */
uint8_t SRTM_CommMessage_GetCategory(srtm_message_t message);

/*!
 * @brief Get SRTM version of request/response/notification message.
 *
 * @param message SRTM request/response/notification message handle.
 *
 * @return SRTM version value. Major version is on MSB byte and minor version is on LSB byte.
 */
uint16_t SRTM_CommMessage_GetVersion(srtm_message_t message);

/*!
 * @brief Get SRTM command of request/response/notification message.
 *
 * @param message SRTM request/response/notification message handle.
 * @return SRTM command value.
 */
uint8_t SRTM_CommMessage_GetCommand(srtm_message_t message);

/*!
 * @brief Get SRTM payload address of request/response/notification message.
 *
 * @param message SRTM request/response/notification message handle.
 * @return SRTM payload address.
 */
uint8_t *SRTM_CommMessage_GetPayload(srtm_message_t message);

/*!
 * @brief Get SRTM payload length of request/response/notification message.
 *
 * @param message SRTM request/response/notification message handle.
 * @return SRTM payload length.
 */
uint32_t SRTM_CommMessage_GetPayloadLen(srtm_message_t message);

/*!
 * @brief Get SRTM message corresponding communication channel.
 *
 * @param message SRTM request/response/notification message handle.
 * @return SRTM communication channel.
 */
srtm_channel_t SRTM_CommMessage_GetChannel(srtm_message_t message);

#ifdef __cplusplus
}
#endif
/*! @} */

#endif /* __SRTM_MESSAGE_H__ */
