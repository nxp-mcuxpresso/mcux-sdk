/*
 * \file MessageQueue.c
 * This is a source file for the MessageQueue module.
 *
 * Copyright 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/************************************************************************************
 *************************************************************************************
 * Include
 *************************************************************************************
 ************************************************************************************/
#include <stdint.h>
#include <stdlib.h>
#include "MessageQueue.h"

#include "hsdkError.h"

/************************************************************************************
 *************************************************************************************
 * Private macros
 *************************************************************************************
 ************************************************************************************/

/************************************************************************************
 *************************************************************************************
 * Private prototypes
 *************************************************************************************
 ************************************************************************************/
static Node *CreateNode(void *pData);
static int DestroyNode(Node *pNode);

/************************************************************************************
 *************************************************************************************
 * Private type definitions
 *************************************************************************************
 ************************************************************************************/

/************************************************************************************
 *************************************************************************************
 * Public memory declarations
 *************************************************************************************
 ************************************************************************************/

/************************************************************************************
 *************************************************************************************
 * Private memory declarations
 *************************************************************************************
 ************************************************************************************/

/************************************************************************************
 *************************************************************************************
 * Public functions
 *************************************************************************************
 ************************************************************************************/


/*! *********************************************************************************
 * \brief  Initialize the given queue.
 *
 * \param[in] maxMessageFlow    maximum number of messages that may be hold at once
 *
 * \return None
 ********************************************************************************** */
MessageQueue *InitializeMessageQueue(uint32_t maxMessageFlow)
{
    MessageQueue *pMessageQueue = (MessageQueue *) calloc(1, sizeof(MessageQueue));
    if (pMessageQueue == NULL) {
        return NULL;
    }

    pMessageQueue->head = NULL;
    pMessageQueue->tail = NULL;
    pMessageQueue->lock = HSDKCreateLock();
    pMessageQueue->cAvailableData = 0;
    pMessageQueue->sAnnounceData = HSDKCreateEvent(0);

    return pMessageQueue;
}

/*! *********************************************************************************
 * \brief  Destroy the given queue.
 *
 * \param[in,out] pMessageQueue pointer to the queue to be freed
 *
 * \return None
 ********************************************************************************** */
int DestroyMessageQueue(MessageQueue *pMessageQueue)
{
    ClearMessageQueue(pMessageQueue);
    HSDKDestroyLock(pMessageQueue->lock);
    HSDKDestroyEvent(pMessageQueue->sAnnounceData);

    free(pMessageQueue);

    return HSDK_ERROR_SUCCESS;
}

/*! *********************************************************************************
 * \brief  Destroy the given queue.
 *
 * \param[in,out] pMessageQueue pointer to the queue to be freed
 *
 * \return None
 ********************************************************************************** */
int ClearMessageQueue(MessageQueue *pMessageQueue)
{
    HSDKAcquireLock(pMessageQueue->lock);
    while (!IsEmpty(pMessageQueue, 0)) {
        Node *node = (Node *)MessageQueueGet(pMessageQueue);
        DestroyNode(node);
    }
    HSDKReleaseLock(pMessageQueue->lock);

    return HSDK_ERROR_SUCCESS;
}

/*! *********************************************************************************
 * \brief  Add data to back the given queue.
 *
 * \param[in,out] pMessageQueue pointer to the queue
 * \param[in] pData pointer to data
 *
 * \return None
 ********************************************************************************** */
void MessageQueuePut(MessageQueue *pMessageQueue, void *pData)
{
    Node *pNode = CreateNode(pData);
    if (pNode == NULL) {
        return;
    }

    HSDKAcquireLock(pMessageQueue->lock);

    if (IsEmpty(pMessageQueue, 0)) {
        pMessageQueue->head = pNode;
        pMessageQueue->tail = pNode;
    } else {
        pMessageQueue->tail->next = pNode;
        pMessageQueue->tail = pNode;
    }

    HSDKReleaseLock(pMessageQueue->lock);
}
/*! *********************************************************************************
 * \brief  Get the data in the front of the queue.
 *
 * \param[in,out] pMessageQueue pointer to the queue
 *
 * \return NULL if the queue is empty or the data in the front of the queue
 ********************************************************************************** */
void *MessageQueueGet(MessageQueue *pMessageQueue)
{
    Node *pNode;
    void *pData;
    pData = NULL;

    HSDKAcquireLock(pMessageQueue->lock);

    if (IsEmpty(pMessageQueue, 0)) {
        HSDKReleaseLock(pMessageQueue->lock);
        return NULL;
    }

    pNode = pMessageQueue->head;
    pMessageQueue->head = pMessageQueue->head->next;
    if (!pMessageQueue->head)
        pMessageQueue->tail = NULL;

    HSDKReleaseLock(pMessageQueue->lock);

    pData = pNode->data;
    DestroyNode(pNode);

    return pData;
}

/*! *********************************************************************************
 * \brief  Checks if the queue is empty
 *
 * \param[in] pMessageQueue pointer to the queue
 * \param[in] synchronized  bool, indicates that that queue should be read in a
 *                          synchronized manner or not
 *
 * \return 1 is the queue is empty and 0 otherwise.
 ********************************************************************************** */
uint8_t IsEmpty(MessageQueue *pMessageQueue, uint8_t synchronized)
{
    uint8_t result;
    if (synchronized) {
        HSDKAcquireLock(pMessageQueue->lock);
    }

    result = (pMessageQueue->head == NULL);

    if (synchronized) {
        HSDKReleaseLock(pMessageQueue->lock);
    }
    return result;
}

/*! *********************************************************************************
 * \brief  Puts data in the front of the queue
 *
 * \param[in, out] pMessageQueue pointer to the queue
 * \param[in] pData pointer to the data
 *
 * \return 1 is the queue is empty and 0 otherwise.
 ********************************************************************************** */
void PushFront(MessageQueue *pMessageQueue, void *pData)
{
    Node *pNode = CreateNode(pData);
    if (pNode == NULL) {
        return;
    }

    HSDKAcquireLock(pMessageQueue->lock);

    if (IsEmpty(pMessageQueue, 0)) {
        pMessageQueue->head = pNode;
        pMessageQueue->tail = pNode;
    } else {
        pNode->next = pMessageQueue->head;
        pMessageQueue->head = pNode;
    }

    HSDKReleaseLock(pMessageQueue->lock);
}

/*! *********************************************************************************
 * \brief  Gets the data in front of the queue without removing it.
 *
 * \param[in] pMessageQueue pointer to the queue
 *
 * \return NULL if the queue is empty, the data in front of the queue otherwise.
 ********************************************************************************** */
void *PeekFront(MessageQueue *pMessageQueue)
{
    Node *pNode;
    void *pData;

    HSDKAcquireLock(pMessageQueue->lock);

    if (IsEmpty(pMessageQueue, 0)) {
        HSDKReleaseLock(pMessageQueue->lock);
        return NULL;
    }

    pNode = pMessageQueue->head;
    pData = pNode->data;

    HSDKReleaseLock(pMessageQueue->lock);

    return pData;
}
/*! *********************************************************************************
 * \brief  Gets the data at a position in the queue without removing it.
 *
 * \param[in] pMessageQueue pointer to the queue
 * \param[in] pIndex position in the queue from where to get the data
 *
 * \return NULL if the queue is empty, the data at the position in the queue otherwise.
 ********************************************************************************** */
void *PeekIndex(MessageQueue *pMessageQueue, uint32_t pIndex)
{
    if (pIndex == 0) {
        return PeekFront(pMessageQueue);
    }

    Node *pNode;
    void *pData;

    HSDKAcquireLock(pMessageQueue->lock);

    if (IsEmpty(pMessageQueue, 0)) {
        HSDKReleaseLock(pMessageQueue->lock);
        return NULL;
    }

    pNode = pMessageQueue->head;
    uint32_t qIndex = 0;

    while(qIndex < pIndex)
    {
        if(pNode->next == NULL) {
            HSDKReleaseLock(pMessageQueue->lock);
            return NULL;
        }
        
        pNode = pNode->next;
        qIndex++;
    }
    pData = pNode->data;
    HSDKReleaseLock(pMessageQueue->lock);

    return pData;
}

/************************************************************************************
 *************************************************************************************
 * Private functions
 *************************************************************************************
 ************************************************************************************/

/*! *********************************************************************************
 * \brief  Create a Node pNode from the data given.
 *
 * \param[in] pData pointer to the data
 *
 * \return NULL if the allocation failed, the pNode otherwise
 ********************************************************************************** */
Node *CreateNode(void *pData)
{
    if (pData == NULL) {
        return NULL;
    }

    Node *pNode = (Node *) calloc(1, sizeof(Node));

    if (!pNode) {
        return NULL;
    }

    pNode->data = pData;
    pNode->next = NULL;

    return pNode;
}

/*! *********************************************************************************
 * \brief  Free the list pNode.
 *
 * \param[in,out] pNode pointer to the node

 * \return None
 ********************************************************************************** */
int DestroyNode(Node *pNode)
{
    pNode->next = NULL;
    pNode->data = NULL;

    free(pNode);

    return HSDK_ERROR_SUCCESS;
}

/*! *********************************************************************************
 * \brief  Enqueues an element in the MessageQueue with its corresponding size
 *
 * \param[in, out] pMessageQueue pointer to the MessageQueue
 * \param[in] pData pointer to the data to enqueue
 * \param[in] cSize size of the element enqueued

 * \return None
 ********************************************************************************** */
void MessageQueuePutWithSize(MessageQueue *pMessageQueue, void *pData, uint32_t cSize)
{
    Node *pNode = CreateNode(pData);
    if (pNode == NULL) {
        return;
    }

    HSDKAcquireLock(pMessageQueue->lock);

    if (IsEmpty(pMessageQueue, 0)) {
        pMessageQueue->head = pNode;
        pMessageQueue->cAvailableData += cSize;
        pMessageQueue->tail = pNode;
    } else {
        if (pMessageQueue->tail != NULL) {
            pMessageQueue->tail->next = pNode;
        }
        pMessageQueue->cAvailableData += cSize;
        pMessageQueue->tail = pNode;
    }

    HSDKReleaseLock(pMessageQueue->lock);
}

/*! *********************************************************************************
 * \brief  Decrements the attribute size of the MessageQueue with cSize if possible
 *
 * \param[in, out] pMessageQueue pointer to the MessageQueue
 * \param[in] cSize  amount to decrement
 *
 * \return An integer equal to the amount decremented
 ********************************************************************************** */
uint32_t MessageQueueDecrementSize(MessageQueue *pMessageQueue, uint32_t cSize)
{
    uint32_t result;
    HSDKAcquireLock(pMessageQueue->lock);
    if (pMessageQueue->cAvailableData < cSize) {
        result = 0;
    } else {
        pMessageQueue->cAvailableData -= cSize;
        result = cSize;
    }
    HSDKReleaseLock(pMessageQueue->lock);
    return result;
}

/*! *********************************************************************************
 * \brief  Gets the size attribute of the MessageQueue
 *
 * \param[in] pMessageQueue pointer to the MessageQueue
 *
 * \return An positive integer for the size of attributed to the MessageQueue
 ********************************************************************************** */
uint32_t MessageQueueGetContentSize(MessageQueue *pMessageQueue)
{
    uint32_t result;
    HSDKAcquireLock(pMessageQueue->lock);
    result = pMessageQueue->cAvailableData;
    HSDKReleaseLock(pMessageQueue->lock);
    return result;
}

#include <stdio.h>
#include "RawFrame.h"
/*! *********************************************************************************
 * \brief  Debug function to inspect the elements of the MessageQueue
 *
 * \param[in] pMessageQueue pointer to the MessageQueue

 * \return None
 ********************************************************************************** */
void InspectQueue(MessageQueue *pMessageQueue)
{
    HSDKAcquireLock(pMessageQueue->lock);
    Node *nod = pMessageQueue->head;
    uint32_t i;
    int nr = 0;
    while (nod != NULL) {
        nr++;
        RawFrame *frame = (RawFrame *) nod->data;
        nod = nod->next;
        printf("Node %d: %d %d     data: ", nr, frame->cbTotalSize, frame->iCrtIndex);
        for (i = 0; i < frame->cbTotalSize; i++)
            printf("%02x ", frame->aRawData[i]);
        printf("\n");
    }
    HSDKReleaseLock(pMessageQueue->lock);
}
