/*
 * \file Framer.c
 * This is a source file for the Framer module.
 *
 * Copyright 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/************************************************************************************
 *************************************************************************************
 * Include
 *************************************************************************************
 ************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RawFrame.h"
#include "Framer.h"
#include "FSCIFrame.h"
#include "FSCIFramer.h"

#include "hsdkError.h"
#include "hsdkLogger.h"

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
static void SendFsciAck(Framer *framer, FSCIFrame *frame);
static void AttachToConcreteImplementation(Framer *framer, FramerProtocol protocol);
static void DetachFromConcreteImplementation(Framer *framer);
static void *FramerThreadRoutine(void *lpParam);
static void FramerCallback(void *callee, void *object);

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
* \brief   Thread routine for each framer, which handles RawDataFrames acquired from
*          UART/SPI device, trying to merge them together to create a FSCIFrame and asses
*          its validity. Upon successful creation it sends the result upwards.
*
* \param[in,out] queue     queue of messages
* \param[in,out] cbSize    current number of bytes to be processed
* \param[in] startByte     synchronization byte, usually 0x02
* \param[in,out] found     flag that indicates whether the frames have the startByte
*
* \return  NULL in case of allocation failure, otherwise an array of bytes with the
*          junk bytes received until the next SYNC byte
********************************************************************************** */
uint8_t *ReadDataUntilByte(MessageQueue *queue, uint16_t *cbSize, uint8_t startByte, uint8_t *found)
{
    uint16_t cbProcessed, cbJunkBytes;
    RawFrame *pRawFrame;
    uint8_t *aResult, *tmp;
    cbJunkBytes = 4;
    aResult = (uint8_t *)calloc(cbJunkBytes, sizeof(uint8_t));

    if (!aResult) {
        return NULL;
    }

    cbProcessed = 0;

    while (!IsEmpty(queue, 1)) {
        pRawFrame = (RawFrame *)MessageQueueGet(queue);

        while ((pRawFrame->iCrtIndex < pRawFrame->cbTotalSize) && (pRawFrame->aRawData[pRawFrame->iCrtIndex] != startByte)) {
            aResult[cbProcessed] = pRawFrame->aRawData[pRawFrame->iCrtIndex];
            pRawFrame->iCrtIndex++;
            cbProcessed++;

            if (cbProcessed == cbJunkBytes) {
                cbJunkBytes *= 2;

                tmp = (uint8_t *)realloc(aResult, cbJunkBytes);

                if (tmp == NULL) {
                    free(aResult);
                    return NULL;
                } else {
                    aResult = tmp;
                }

                memset(aResult + cbProcessed, 0, cbJunkBytes - cbProcessed);
            }
        }

        if (pRawFrame->aRawData[pRawFrame->iCrtIndex] == startByte) {
            *found = 1;
        }

        if (pRawFrame->iCrtIndex == pRawFrame->cbTotalSize) {
            DestroyRawFrame(pRawFrame);
        } else {
            PushFront(queue, pRawFrame);
            break;
        }
    }

    *cbSize = cbProcessed;

    return aResult;
}

/*! *********************************************************************************
 * \brief   Reads a single byte from the queue of messages.
 *
 * \param[in] queue
 *
 * \return a uint8 for the byte
 ********************************************************************************** */
uint8_t ReadSingleByte(MessageQueue *queue)
{
    RawFrame *pRawFrame = (RawFrame *)MessageQueueGet(queue);

    if (pRawFrame == NULL) {
        return 0; // TODO
    }

    uint8_t single = pRawFrame->aRawData[pRawFrame->iCrtIndex];
    pRawFrame->iCrtIndex++;

    if (pRawFrame->iCrtIndex == pRawFrame->cbTotalSize) {
        DestroyRawFrame(pRawFrame);
    } else {
        PushFront(queue, pRawFrame);
    }

    return single;
}

/*! *********************************************************************************
 * \brief   Reads a number of bytes from the message queue.
 *
 * \param[in] queue
 * \param[in] cbDemanded
 *
 * \return an array of bytes
 ********************************************************************************** */
uint8_t *ReadMultiByte(MessageQueue *queue, uint32_t cbDemanded)
{
    uint32_t cbProcessed;
    RawFrame *pRawFrame;
    uint8_t *aResult;

    cbProcessed = 0;
    aResult = (uint8_t *)calloc(cbDemanded, sizeof(uint8_t));

    if (!aResult) {
        return NULL;
    }

    while (cbProcessed < cbDemanded) {
        pRawFrame = (RawFrame *)MessageQueueGet(queue);

        if (pRawFrame == NULL) {
            /* No more frames, return partial result. */
            return aResult;
        }

        if (pRawFrame->cbTotalSize - pRawFrame->iCrtIndex <= cbDemanded - cbProcessed) {
            memcpy(aResult + cbProcessed, pRawFrame->aRawData + pRawFrame->iCrtIndex, pRawFrame->cbTotalSize - pRawFrame->iCrtIndex);
            cbProcessed += (pRawFrame->cbTotalSize - pRawFrame->iCrtIndex);
            DestroyRawFrame(pRawFrame);
        } else {
            memcpy(aResult + cbProcessed, pRawFrame->aRawData + pRawFrame->iCrtIndex, cbDemanded - cbProcessed);
            pRawFrame->iCrtIndex += (cbDemanded - cbProcessed);
            cbProcessed = cbDemanded;
            PushFront(queue, pRawFrame);
        }
    }

    return aResult;
}

/*! *********************************************************************************
 * \brief   Peek a number of bytes from the message queue.
 *
 * \param[in] queue
 * \param[in] cbDemanded
 *
 * \return an array of bytes
 ********************************************************************************** */
uint8_t *PeekMultiByte(MessageQueue *queue, uint32_t cbDemanded)
{
    uint32_t cbProcessed;
    RawFrame *pRawFrame;
    uint8_t *aResult;

    cbProcessed = 0;
    aResult = (uint8_t *)calloc(cbDemanded, sizeof(uint8_t));

    if (!aResult) {
        return NULL;
    }

    while (cbProcessed < cbDemanded) {
        pRawFrame = (RawFrame *)PeekIndex(queue, cbProcessed);

        if (pRawFrame == NULL) {
            /* No more frames, return partial result. */
            return aResult;
        }

        if (pRawFrame->cbTotalSize - pRawFrame->iCrtIndex <= cbDemanded - cbProcessed) {
            memcpy(aResult + cbProcessed, pRawFrame->aRawData + pRawFrame->iCrtIndex, pRawFrame->cbTotalSize - pRawFrame->iCrtIndex);
            cbProcessed += (pRawFrame->cbTotalSize - pRawFrame->iCrtIndex);
        } else {
            memcpy(aResult + cbProcessed, pRawFrame->aRawData + pRawFrame->iCrtIndex, cbDemanded - cbProcessed);
            cbProcessed = cbDemanded;
        }
    }

    return aResult;
}

/*! *********************************************************************************
 * \brief   Transmit a frame to the lower layer device to which the framer is connected
 *
 * \param[in] framer
 * \param[in] frame
 *
 * \return 0
 ********************************************************************************** */
int SendFrame(Framer *framer, void *frame)
{
    if (framer == NULL) {
        logMessage(HSDK_ERROR, "[Framer]SendFrame", "Framer is NULL", HSDKThreadId());
        return HSDK_ERROR_INVALID;
    }

    uint32_t size;
    uint8_t *packet = framer->CreatePacket(framer, frame, &size);

    int err = SendBytes(framer, packet, size);

    free(packet);

    return err;
}

int SendBytes(Framer *framer, uint8_t *packet, uint32_t size)
{
    return WritePhysicalDevice(framer->physicalLayer, packet, size);
}

static void SendFsciAck(Framer *framer, FSCIFrame *frame)
{
    PhysicalDevice *device = (PhysicalDevice *)(framer->physicalLayer);

    if (device->configParams->fsciRxAck) {
        /* Do not cascade ACKs. */
        if (frame->opGroup != 0xA4 || frame->opCode != 0xFD) {
            device->write(device->deviceHandle, GetAckFrame(framer->lengthFieldSize),
                          3 + framer->lengthFieldSize + 1 + 1);
            HSDKReleaseLock(device->inMessages->lock);
        }
    }
}


uint8_t *PackageFrame(Framer *framer, void *frame, uint32_t *size)
{
    if (framer == NULL) {
        logMessage(HSDK_ERROR, "[Framer]PackageFrame", "Framer is NULL", HSDKThreadId());
        return NULL;
    }

    if (framer->CreatePacket == NULL) {
        logMessage(HSDK_ERROR, "[Framer]PackageFrame", "CreatePacket function is NULL", HSDKThreadId());
        return NULL;
    }

    return framer->CreatePacket(framer, frame, size);
}

/*! *********************************************************************************
 * \brief   Initialize a framer object.
 *
 * \param[in,out] connDev       pointer to the physical layer device object the framer is attached
 * \param[in] protocol          the type of the framer, i.e. FSCI, HCI or ASCII
 * \param[in] lengthFieldSize   this framer will operate with frames having the length field on so many bytes
 * \param[in] crcFieldSize      this framer will operate with frames having the CRC field on so many bytes
 * \param[in] endian            the endianness of the framer
 *
 * \return NULL on allocation failure, a pointer to the Framer object otherwise
 ********************************************************************************** */
Framer *InitializeFramer(void *connDev, FramerProtocol protocol, uint8_t lengthFieldSize, uint8_t crcFieldSize, endianness endian)
{
    initLogger(NULL);

    Framer *framer = (Framer *)calloc(1, sizeof(Framer));

    if (!framer) {
        logMessage(HSDK_ERROR, "[Framer]InitializeFramer", "Allocate memory for Framer failed", HSDKThreadId());
        return NULL;
    }

    logMessage(HSDK_INFO, "[Framer]InitializeFramer", "Allocated memory for Framer", HSDKThreadId());

    framer->physicalLayer = connDev;
    framer->lengthFieldSize = lengthFieldSize;
    framer->crcFieldSize = crcFieldSize;
    framer->framerEndianness = endian;

    framer->stopThread = HSDKCreateEvent(0);

    if (framer->stopThread == INVALID_EVENT_HANDLE) {
        logMessage(HSDK_ERROR, "[Framer]InitializeFramer", "Event stopThread creation failed", HSDKThreadId());
        free(framer);
        return NULL;
    }

    logMessage(HSDK_INFO, "[Framer]InitializeFramer", "Created stopThread event", HSDKThreadId());

    framer->queue = InitializeMessageQueue(INT32_MAX);

    if (framer->queue == NULL) {
        logMessage(HSDK_ERROR, "[Framer]InitializeFramer", "MessageQueue init failed", HSDKThreadId());
        free(framer);
        return NULL;
    }

    logMessage(HSDK_INFO, "[Framer]InitializeFramer", "Initialized framer's message queue", HSDKThreadId());

    framer->evtManager = CreateEventManager();

    if (framer->evtManager == NULL) {
        logMessage(HSDK_ERROR, "[Framer]InitializeFramer", "EventManager creation failed", HSDKThreadId());
        free(framer);
        return NULL;
    }

    logMessage(HSDK_INFO, "[Framer]InitializeFramer", "Created event manager for framer", HSDKThreadId());

    AttachToPhysicalDevice(connDev, framer, FramerCallback);
    AttachToConcreteImplementation(framer, protocol);

    framer->framerThread = HSDKCreateThread(FramerThreadRoutine, framer);

    if (!framer->framerThread) {
        DetachFromPhysicalDevice(connDev, framer);
        DestroyMessageQueue(framer->queue);
        framer->queue = NULL;
        HSDKDestroyEvent(framer->stopThread);

        free(framer);
        return NULL;
    }

    return framer;
}

void SetLengthFieldSize(Framer *framer, uint8_t lengthFieldSize)
{
    framer->lengthFieldSize = lengthFieldSize;
}

void SetCrcFieldSize(Framer *framer, uint8_t crcFieldSize)
{
    framer->crcFieldSize = crcFieldSize;
}

void SetEndianness(Framer *framer, endianness endian)
{
    framer->framerEndianness = endian;
}

/*! *********************************************************************************
 * \brief   Frees the allocated memory of the specified Framer object
 *
 * \param[in] framer a pointer to the Framer object that is to be freed
 *
 * \return none
 ********************************************************************************** */
int DestroyFramer(Framer *framer)
{
    // Check if the device exists
    if (framer == NULL) {
        logMessage(HSDK_ERROR, "[Framer]DestroyFramer", "Framer is NULL", HSDKThreadId());
        return HSDK_ERROR_INVALID;
    }

    int err;

    DetachFromPhysicalDevice(framer->physicalLayer, framer);

    err = HSDKSignalEvent(framer->stopThread);

    if (err != HSDK_ERROR_SUCCESS) {
        logMessage(HSDK_ERROR, "[Framer]DestroyFramer", "Error in signaling the framer to stop", HSDKThreadId());
        return err;
    }

    err = HSDKDestroyThread(framer->framerThread);

    if (err != HSDK_ERROR_SUCCESS) {
        logMessage(HSDK_ERROR, "[Framer]DestroyFramer", "Error in closing the framer thread", HSDKThreadId());
        return err;
    }

    err = HSDKDestroyEvent(framer->stopThread);

    if (err != HSDK_ERROR_SUCCESS) {
        logMessage(HSDK_ERROR, "[Framer]DestroyFramer", "Error in destroying stopThread event", HSDKThreadId());
        return err;
    }

    DestroyEventManager(framer->evtManager);

    err = DestroyMessageQueue(framer->queue);
    framer->queue = NULL;

    if (err != HSDK_ERROR_SUCCESS) {
        logMessage(HSDK_ERROR, "[Framer]DestroyFramer", "Error in destroying the Message Queue", HSDKThreadId());
        return err;
    }

    framer->StateMachineDispatch = NULL;
    framer->physicalLayer = NULL;
    framer->SMStartState = NULL;
    framer->SMFinalState = NULL;

    free(framer);
    closeLogger();

    return HSDK_ERROR_SUCCESS;
}

void AttachToFramer(Framer *framer, void *observer, void(*Callback) (void *, void *))
{
    RegisterToEventManager(framer->evtManager, observer, Callback);
}

void DetachFromFramer(Framer *framer, void *observer)
{
    DeregisterFromEvent(framer->evtManager, observer);
}

/************************************************************************************
 *************************************************************************************
 * Private functions
 *************************************************************************************
 ************************************************************************************/
/*! *********************************************************************************
 * \brief   Thread routine for each framer, which handles RawDataFrames acquired from
 *          UartDevice, trying to merge them together to create a FSCIFrame and assess
 *          its validity. Upon successful creation it sends the result upwards
 *
 * \param[in] lpParam   a pointer to the thread routine parameters, i.e. a pointer to
 *                      the Framer structure.
 *
 * \return NULL on all accounts.
 ********************************************************************************** */
static void *FramerThreadRoutine(void *lpParam)
{
    Framer *framer = (Framer *)lpParam;
    FrameStatus status;
    void *response = NULL;
    uint8_t loop = 1;
    int triggeredEvent;
    int8_t ret = 0;
    uint32_t cbCrtAvailable, cbSaved;
    PhysicalDevice* device = (PhysicalDevice*)(framer->physicalLayer);

    Event eventArray[2];
    eventArray[0] = framer->stopThread;
    eventArray[1] = framer->queue->sAnnounceData;

    framer->currentState = framer->SMStartState();

    while (loop) {
        ret = HSDKWaitMultipleEvents(eventArray, 2, INFINITE_WAIT, &triggeredEvent);

        if (ret != HSDK_ERROR_SUCCESS) {
            loop = 0;
            continue;
        }

        switch (triggeredEvent) {
            case 0:
                logMessage(HSDK_INFO, "[Framer]FramerThreadRoutine", "Framer terminated", HSDKThreadId());
                return NULL;

            case 1:
                /* poll waked up on sAnnounceData, so we clear the event immediately */
                HSDKResetEvent(eventArray[1]);

                cbCrtAvailable = MessageQueueGetContentSize(framer->queue);

                if (cbCrtAvailable == 0) {
                    continue;
                }

                cbSaved = cbCrtAvailable;
                status = framer->StateMachineDispatch(framer, &response, &cbCrtAvailable);
                MessageQueueDecrementSize(framer->queue, cbSaved - cbCrtAvailable);

                if (response) {
                    if (status == INVALID_CRC) {
                        logMessage(HSDK_WARNING, "[Framer]FramerThreadRoutine", "Invalid CRC detected - frame dismissed.", HSDKThreadId());
                    } else if (status == VALID_FRAME) {
                        if (device->configParams->fsciRxAck) {
                            // verify received packet is not an ACK
                            if (((FSCIFrame*)response)->opGroup != 0xA4 || ((FSCIFrame*)response)->opCode != 0xFD) {
                                /* Prevent other TXs until we send back the ACK. */
                                HSDKAcquireLock(device->inMessages->lock);
                            }
                            SendFsciAck(framer, (FSCIFrame*)response);
                        }
                        
                        if (device->configParams->fsciTxAck) {
                            if (((FSCIFrame*)response)->opGroup == 0xA4 || ((FSCIFrame*)response)->opCode == 0xFD) {
                                HSDKSignalEvent(device->sAnnounceTXACK);
                            }
                        }

                        NotifyOnEvent(framer->evtManager, response);
                        response = NULL;
                    } else {
                        /* No action taken for JUNK_DATA, INSUFFICIENT_DATA or SUFFICIENT_DATA */
                    }
                }

                /* keep the loop going if there's data left to process */
                if (cbCrtAvailable > 0 && status != INSUFFICIENT_DATA) {
                    if((status == VALID_FRAME && framer->QueueDataVerification(framer, &cbCrtAvailable)) ||
                        (status != VALID_FRAME)) {
                        HSDKSignalEvent(eventArray[1]);
                    }         
                }

                if (framer->currentState == framer->SMFinalState()) {
                    framer->currentState = framer->SMStartState();
                }
        }
    }

    return NULL;
}

static void FramerCallback(void *callee, void *object)
{
    Framer *framer = (Framer *)callee;
    RawFrame *frame = (RawFrame *)object;
    MessageQueuePutWithSize(framer->queue, frame, frame->cbTotalSize);
    HSDKSignalEvent(framer->queue->sAnnounceData);
}

static void AttachToConcreteImplementation(Framer *framer, FramerProtocol protocol)
{
    switch (protocol) {
        case FSCI:
            FSCIFramerInitialization(framer);
            break;

        case HCI:
            // HCIFramerInitialization(framer);
            break;

        case ASCII:
            // ASCIIFramerInitialization(framer);
            break;

        default:
            logMessage(HSDK_ERROR, "[Framer]InitializeFramer", "Not implemented", HSDKThreadId());
    }
}
