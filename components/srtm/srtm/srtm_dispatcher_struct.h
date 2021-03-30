/*
 * Copyright 2017, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SRTM_DISPATCHER_STRUCT_H__
#define __SRTM_DISPATCHER_STRUCT_H__

#include "srtm_defs.h"
#include "srtm_list.h"
#include "srtm_sem.h"
#include "srtm_mutex.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/**
 * @brief SRTM dispatcher message number to hold the received data.
 *
 * The received message is freed for reuse once it gets processed by the
 * dispatcher task. In a busy traffic, 8 received messages might be used
 * up and latter calling SRTM_Dispatcher_PostRecvData() from channel will
 * return failed. In this case, user need to augment the number.
 */
#ifndef SRTM_DISPATCHER_CONFIG_RX_MSG_NUMBER
#define SRTM_DISPATCHER_CONFIG_RX_MSG_NUMBER (8U)
#endif

/**
 * @brief SRTM dispatcher message maximum length in bytes.
 *
 * The maximum buffer length for SRTM_Dispatcher_PostRecvData() call. User
 * need to augment the number when there's long message in application
 * protocol.
 */
#ifndef SRTM_DISPATCHER_CONFIG_RX_MSG_MAX_LEN
#define SRTM_DISPATCHER_CONFIG_RX_MSG_MAX_LEN (256U)
#endif

/**
 * @brief SRTM dispatcher struct
 */
struct _srtm_dispatcher
{
    srtm_list_t cores;    /*!< SRTM peer core list head */
    srtm_list_t services; /*!< SRTM service list head */

    srtm_mutex_t mutex; /*!< Mutex for multi-task protection */
#if defined(SRTM_STATIC_API) && SRTM_STATIC_API
    srtm_mutex_buf_t mutexStatic;
#endif

    srtm_list_t freeRxMsgs;  /*!< Free Rx messages list to hold the callback Rx data */
    srtm_list_t messageQ;    /*!< Message queue to hold the messages to process */
    srtm_list_t waitingReqs; /*!< Message queue to hold the request waiting for the response */

    volatile bool stopReq; /*!< SRTM dispatcher stop request flag */
    bool started;          /*!< SRTM dispatcher started flag */
    srtm_sem_t startSig;   /*!< SRTM dispatcher start signal */
#if defined(SRTM_STATIC_API) && SRTM_STATIC_API
    srtm_sem_buf_t startSigStatic;
#endif
    srtm_sem_t stopSig;    /*!< SRTM dispatcher stop signal */
#if defined(SRTM_STATIC_API) && SRTM_STATIC_API
    srtm_sem_buf_t stopSigStatic;
#endif
    srtm_sem_t queueSig;   /*!< SRTM dispatcher messageQ signal */
#if defined(SRTM_STATIC_API) && SRTM_STATIC_API
    srtm_sem_buf_t queueSigStatic;
#endif
};

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Post received data from channel to dispatcher.
 *
 * @param dispatcher SRTM dispatcher handle.
 * @param channel The channel where Rx data is got from.
 * @param buf The buffer address of Rx data.
 * @param len The buffer len of Rx data in bytes.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_Dispatcher_PostRecvData(srtm_dispatcher_t disp, srtm_channel_t channel, void *buf, uint32_t len);

/*!
 * @brief The main message processor of dispatcher.
 *
 * The function MUST be called in dispatcher running thread context.
 *
 * @param dispatcher SRTM dispatcher handle.
 * @param msg The message to be handled.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_Dispatcher_ProcessMessage(srtm_dispatcher_t disp, srtm_message_t msg);

/*!
 * @brief Deliver all messages in the list sequentially and clean up the list.
 *
 * This function is used to combine some messages into one delivery to make sure the
 * messages can be handled in sequence without other messages interleaved. The messages
 * can be different type, e.g. combining procedure message and response message is allowed.
 *
 * @param disp SRTM dispatcher handle.
 * @param msgs Message list to send to peer core.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_Dispatcher_DeliverMessages(srtm_dispatcher_t disp, srtm_list_t *msgs);

#ifdef __cplusplus
}
#endif
/*! @} */

#endif /* __SRTM_DISPATCHER_STRUCT_H__ */
