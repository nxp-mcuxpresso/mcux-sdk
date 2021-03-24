/*
 * Copyright 2017, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SRTM_DISPATCHER__
#define __SRTM_DISPATCHER__

#include "srtm_defs.h"

/*!
 * @addtogroup srtm
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/**
 * @brief SRTM response callback function
 */
typedef void (*srtm_dispatcher_resp_cb_t)(srtm_dispatcher_t disp, srtm_message_t req, srtm_message_t resp, void *param);

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Create SRTM dispatcher object.
 *
 * @return SRTM dispacher handle, or NULL on failure.
 */
srtm_dispatcher_t SRTM_Dispatcher_Create(void);

/*!
 * @brief Destroy SRTM dispatcher object.
 *
 * @param disp SRTM dispatcher handle.
 */
void SRTM_Dispatcher_Destroy(srtm_dispatcher_t disp);

/*!
 * @brief Start SRTM dispatcher.
 *
 * @param disp SRTM dispatcher handle.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_Dispatcher_Start(srtm_dispatcher_t disp);

/*!
 * @brief Stop SRTM dispatcher.
 *
 * @param disp SRTM dispatcher handle.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_Dispatcher_Stop(srtm_dispatcher_t disp);

/*!
 * @brief Run SRTM dispatcher. Loop inside and never return.
 *
 * @param disp SRTM dispatcher handle.
 */
void SRTM_Dispatcher_Run(srtm_dispatcher_t disp);

/*!
 * @brief Add peer core to the SRTM dispatcher.
 *
 * @param disp SRTM dispatcher handle.
 * @param core SRTM peer core to add.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_Dispatcher_AddPeerCore(srtm_dispatcher_t disp, srtm_peercore_t core);

/*!
 * @brief Remove peer core from the SRTM dispatcher.
 *
 * @param disp SRTM dispatcher handle.
 * @param core SRTM peer core to remove.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_Dispatcher_RemovePeerCore(srtm_dispatcher_t disp, srtm_peercore_t core);

/*!
 * @brief Register service to the SRTM dispatcher to handle corresponding request/notification.
 *
 * @param disp SRTM dispatcher handle.
 * @param service SRTM service to register.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_Dispatcher_RegisterService(srtm_dispatcher_t disp, srtm_service_t service);

/*!
 * @brief Remove peer core from the SRTM dispatcher.
 *
 * @param disp SRTM dispatcher handle.
 * @param service SRTM service to unregister.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_Dispatcher_UnregisterService(srtm_dispatcher_t disp, srtm_service_t service);

/*!
 * @brief Send request to peer core and wait for the response.
 *
 * The request is created by user, and the response is created by SRTM dispatcher. User need to destroy
 * both to avoid memory leakage.
 *
 * @param disp SRTM dispatcher handle.
 * @param req SRTM request to send to peer core.
 * @param pResp SRTM response got from peer core. If request fails, the pResponse points to NULL.
 * @param timeout Maximum milliseconds to wait for the response.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_Dispatcher_Request(srtm_dispatcher_t disp,
                                      srtm_request_t req,
                                      srtm_response_t *pResp,
                                      uint32_t timeout);

/*!
 * @brief Deliver request to peer core and return immediately.
 *
 * The request is created by user, and transferred to SRTM dispatcher. When dispatcher receives the
 * response, it will call the user provided callback. User doesn't need to destroy either request
 * or response in the callback. They will both be destroyed after callback returns.
 * In case something wrong, user can get the error code with SRTM_Request_GetErrorCode(req) in
 * callback function.
 *
 * @param disp SRTM dispatcher handle.
 * @param req SRTM request to send to peer core.
 * @param callback User function to get the response.
 * @param param User paramter to be used in callback.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_Dispatcher_DeliverRequest(srtm_dispatcher_t disp,
                                             srtm_request_t req,
                                             srtm_dispatcher_resp_cb_t callback,
                                             void *param);

/*!
 * @brief Deliver response to peer core and return immediately.
 *
 * The response is created by user, and transferred to SRTM dispatcher. No response required.
 * User doesn't need to destroy the response. It will be destroyed after the message is sent.
 *
 * @param disp SRTM dispatcher handle.
 * @param resp SRTM response to send to peer core.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_Dispatcher_DeliverResponse(srtm_dispatcher_t disp, srtm_response_t resp);

/*!
 * @brief Deliver notification to peer core and return immediately.
 *
 * The notification is created by user, and transferred to SRTM dispatcher. No response required.
 * User doesn't need to destroy the notification. It will be destroyed after the message is sent.
 *
 * @param disp SRTM dispatcher handle.
 * @param notif SRTM notification to send to peer core.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_Dispatcher_DeliverNotification(srtm_dispatcher_t disp, srtm_notification_t notif);

/*!
 * @brief Deliver raw data message to peer core and return immediately.
 *
 * The raw data message is created by user, and transferred to SRTM dispatcher. No response
 * required. User doesn't need to destroy the raw data message. It will be destroyed after
 * the message is sent.
 *
 * @param disp SRTM dispatcher handle.
 * @param data Raw data message to send to peer core.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_Dispatcher_DeliverRawData(srtm_dispatcher_t disp, srtm_rawdata_t data);

/*!
 * @brief Deliver procedure message to dispatcher and return after the procedure is called.
 *
 * The procedure message is created by user. User need to destroy the message to avoid memory leakage after return.
 *
 * @param disp SRTM dispatcher handle.
 * @param proc SRTM procedure message to be called.
 * @param timeout Maximum milliseconds to wait for the response.
 *                Note the actual max wait time is "timeout" + "duration of the procedure"
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_Dispatcher_CallProc(srtm_dispatcher_t disp, srtm_procedure_t proc, uint32_t timeout);

/*!
 * @brief Deliver local procedure message to dispatcher and return immediately.
 *
 * The procedure message is created by user, and transferred to SRTM dispatcher. No response
 * required. User doesn't need to destroy the procedure message. It will be destroyed after
 * the procedure finishes.
 *
 * @param disp SRTM dispatcher handle.
 * @param proc Procedure message to dispatch.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_Dispatcher_PostProc(srtm_dispatcher_t disp, srtm_procedure_t proc);

#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* __SRTM_DISPATCHER__ */
