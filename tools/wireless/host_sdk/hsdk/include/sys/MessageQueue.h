/*
 * \file MessageQueue.h
 * This is the header file for the MessageQueue module.
 *
 * Copyright 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __QUEUE_H__
#define __QUEUE_H__

/*! *********************************************************************************
 ************************************************************************************
 * Include
 ************************************************************************************
 ********************************************************************************* */
#include "hsdkOSCommon.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! *********************************************************************************
 ************************************************************************************
 * Public type definitions
 ************************************************************************************
 ********************************************************************************* */
/**
 * @brief Node structure for the MessageQueue structural elements.
 */
typedef struct _list {
    void *data;         /**< Generic pointer to data stored into the node. */
    struct _list *next; /**< Pointer to the next element in the list. */
} Node;

/**
 * @brief Queue structure for passing messages between components of HSDK different layers.
 */
typedef struct {
    Node *head;                 /**< Head of the queue. */
    Node *tail;                 /**< End of the queue. */
    uint32_t cAvailableData;    /**< A generic count of the data stored. Can be used to store number of messages of total size of messages. */
    Semaphore sAnnounceData;    /**< A semaphore to indicate availability of  messages to be processed. */
    Lock lock;                  /**< A lock to synchronize access to the message queue. */
} MessageQueue;


/*! *********************************************************************************
 ************************************************************************************
 * Public memory declarations
 ************************************************************************************
 ********************************************************************************* */

/*! *********************************************************************************
 ************************************************************************************
 * Public macros
 ************************************************************************************
 ********************************************************************************* */

/*! *********************************************************************************
 ************************************************************************************
 * Public prototypes
 ************************************************************************************
 ********************************************************************************* */
MessageQueue *InitializeMessageQueue(uint32_t maxMessageFlow);
int DestroyMessageQueue(MessageQueue *pMessageQueue);
int ClearMessageQueue(MessageQueue *pMessageQueue);
void MessageQueuePut(MessageQueue *pMessageQueue, void *pData);
void *MessageQueueGet(MessageQueue *pMessageQueue);
void MessageQueuePutWithSize(MessageQueue *pMessageQueue, void *pData, uint32_t);
uint32_t MessageQueueDecrementSize(MessageQueue *pMessageQueue, uint32_t);
uint32_t MessageQueueGetContentSize(MessageQueue *pMessageQueue);
uint8_t IsEmpty(MessageQueue *pMessageQueue, uint8_t synchronized);
void *PeekFront(MessageQueue *pMessageQueue);
void *PeekIndex(MessageQueue *pMessageQueue, uint32_t pIndex);
void PushFront(MessageQueue *pMessageQueue, void *pData);

#ifdef DEBUG
void InspectQueue(MessageQueue *pMessageQueue);
#endif

#ifdef __cplusplus
}
#endif

#endif
