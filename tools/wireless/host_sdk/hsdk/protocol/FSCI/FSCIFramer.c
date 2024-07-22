/*
 * \file FsciFramer.c
 * This is a source file for the FSCIFramer module.
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
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "hsdkLogger.h"
#include "utils.h"
#include "RawFrame.h"
#include "FSCIFrame.h"
#include "FSCIFramer.h"

/************************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
************************************************************************************/
#define FSCI_MTU        2048

/************************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
************************************************************************************/
static uint8_t *CreatePacket(Framer *framer, uint8_t ogf, uint8_t ocf, uint32_t length, uint8_t *data, uint32_t crc, uint8_t crcFieldSize, uint32_t *size);
static uint8_t CalculateCRC(Framer *framer, FSCIFrame *frame);
static FSCIFrame *FSCIHandleNewFrame(Framer *framer);
static FrameStatus FSCIJunkData(Framer *framer, FSCIFrame **currentFrame, uint32_t *dataSize);
static FrameStatus FSCISyncField(Framer *framer, FSCIFrame **currentFrame, uint32_t *dataSize);
static FrameStatus FSCIOpCodeField(Framer *framer, FSCIFrame **currentFrame, uint32_t *dataSize);
static FrameStatus FSCIOpGroupField(Framer *framer, FSCIFrame **currentFrame, uint32_t *dataSize);
static FrameStatus FSCILengthField(Framer *framer, FSCIFrame **currentFrame, uint32_t *dataSize);
static FrameStatus FSCIDataField(Framer *framer, FSCIFrame **currentFrame, uint32_t *dataSize);
static FrameStatus FSCICrcField(Framer *framer, FSCIFrame **currentFrame, uint32_t *dataSize);
static FrameStatus FSCISecondCrcField(Framer *framer, FSCIFrame **currentFrame, uint32_t *dataSize);

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
#if defined __APPLE__ || defined __UCLIBC__
uint8_t __attribute__((weak)) ReadSingleByte(MessageQueue *queue)
{
    return 0;
}
uint8_t __attribute__((weak)) *ReadMultiByte(MessageQueue *queue, uint32_t cbDemanded)
{
    return NULL;
}
uint8_t __attribute__((weak)) *ReadDataUntilByte(MessageQueue *queue, uint16_t *cbSize, uint8_t startByte, uint8_t *found)
{
    return NULL;
}
#endif

/*! *********************************************************************************
* \brief    Transform a FSCIFrame into an array of bytes containing the frame elements.
*           It's a public wrapper for a private function and used for a function pointer
*           in the Framer structure.
*
* \param[in,out] framer a pointer to a Framer object
* \param[in] frame      a generic pointer to a frame, which is casted to a pointer to
*                       a FSCIFrame
* \param[in,out] size   a pointer to a variable holding the size of the returned array
*
* \return an array of bytes if succeeds, NULL otherwise
********************************************************************************** */
uint8_t *CreateFSCIPacket(Framer *framer, void *frame, uint32_t *size)
{
    FSCIFrame *fsciFrame = (FSCIFrame *) frame;

    return CreatePacket(framer, fsciFrame->opGroup, fsciFrame->opCode, fsciFrame->length, fsciFrame->data, fsciFrame->crc, (!(fsciFrame->virtualInterface)) ? 1 : 2, size);
}

void FSCI_transmitPayload(Framer *framer, uint8_t OG, uint8_t OC, void *pMsg, uint16_t msgLen, uint32_t fsciInterface)
{
    if (framer) {
        FSCIFrame *frame = CreateFSCIFrame(framer, OG, OC, (uint8_t *)pMsg, msgLen, fsciInterface);

        if (frame) {
            SendFrame(framer, frame);
            DestroyFSCIFrame(frame);
        }
    }
}

/*! *********************************************************************************
* \brief    The state machine used for merging the data received into frames.
*
* \param[in,out] framer         pointer to a Framer object
* \param[in,out] currentFrame   pointer to a frame to be dispatched
* \param[in,out] dataSize       the length of the frame
*
* \return the status of the current frame.
********************************************************************************** */
FrameStatus FSCIStateMachineDispatch(Framer *framer, void **currentFrame, uint32_t *dataSize)
{
    FSCIFrame *workingCopy = (FSCIFrame *)*currentFrame;
    FrameStatus status = SUFFICIENT_DATA;

    if (workingCopy == NULL) {
        workingCopy = FSCIHandleNewFrame(framer);

        if (!workingCopy)
            return INSUFFICIENT_DATA;

        status = SUFFICIENT_DATA;
        framer->currentState = FSCI_SM_JUNK_DATA;
    }

    /* Except for the JUNK_DATA state which returns in case of actual JUNK_DATA data received the cases
       fall-through to the next and break in case of insufficient data. */
    switch (framer->currentState) {

        case FSCI_SM_JUNK_DATA:
            status = FSCIJunkData(framer, &workingCopy, dataSize);

            if (status == JUNK_DATA)
                break;

        case FSCI_SM_SYNC:
            status = FSCISyncField(framer, &workingCopy, dataSize);

            if (status == INSUFFICIENT_DATA)
                break;

        case FSCI_SM_OGF:
            status = FSCIOpGroupField(framer, &workingCopy, dataSize);

            if (status == INSUFFICIENT_DATA)
                break;

        case FSCI_SM_OCF:
            status = FSCIOpCodeField(framer, &workingCopy, dataSize);

            if (status == INSUFFICIENT_DATA)
                break;

        case FSCI_SM_LENGTH:
            status = FSCILengthField(framer, &workingCopy, dataSize);

            if (status != SUFFICIENT_DATA)
                break;

        case FSCI_SM_DATA:
            status = FSCIDataField(framer, &workingCopy, dataSize);

            if (status == INSUFFICIENT_DATA)
                break;

        case FSCI_SM_CRC_FST:
            status = FSCICrcField(framer, &workingCopy, dataSize);

            if (status != SUFFICIENT_DATA)
                break;

        /* If different PAN ID, there are usually two bytes as CRC. */
        case FSCI_SM_CRC_SND:
            status = FSCISecondCrcField(framer, &workingCopy, dataSize);
    }

    *currentFrame = workingCopy;
    return status;
}

/*! *********************************************************************************
* \brief    Verifies if the data left inside the queue is enough to be considered a new packet.
*
* \param[in] framer             pointer to the Framer from where the message queue is accessed
* \param[in, out] currentFrame  pointer to a pointer to the FSCIFrame that is being constructed
* \param[in, out] dataSize      pointer to a variable indicating the size of the queue
*
* \return 1 if is enough data to keep the loop open for a new packet 0 otherwise 
********************************************************************************** */
int FSCIQueueDataVerification(Framer *framer, uint32_t *dataSize)
{
    /** The size of the smallest packet in FSCI, no data. Documentation about FSCI:
        Host Stack FSCI Reference Manual.pdf chapter 2.3 Overview and packet structure */
    uint32_t minFSCIPacketLength = FSCI_SYNC_SIZE + FSCI_OGF_SIZE + FSCI_OCF_SIZE + framer->lengthFieldSize + MAX_CRC_SIZE;

    if (*dataSize < minFSCIPacketLength) {
        return 0; 
    }
    else {
        /** If the data in the queue is enough to be consider at least a no data FSCI packet verify
            if the data in the queue is at least as big as the length of the presumed packet*/
        MessageQueue *queue = framer->queue;
        uint32_t length = 0; // length of the presumed packet 
        uint8_t returnValue = 0;
        /** Size of a FSCI packet header adding the size of the FSCI sync byte */
        uint8_t lenNoDataPacket = FSCI_SYNC_SIZE + FSCI_OGF_SIZE + FSCI_OCF_SIZE + framer->lengthFieldSize;
        
        uint8_t *peekData = PeekMultiByte(queue, lenNoDataPacket);

        if(peekData != NULL) {
            /** Verify if the first byte is the sync one */
            if(peekData[0] == FSCI_SYNC_BYTE) {
                if (framer->lengthFieldSize == 1) {
                   length = peekData[3];
                } 
                else {
                   length = peekData[3] + (peekData[4] << 8);
                }

                /** The size of presumed packet*/
                uint8_t sizePresumedPacket = FSCI_SYNC_SIZE + FSCI_OGF_SIZE + FSCI_OCF_SIZE + framer->lengthFieldSize + MAX_CRC_SIZE + length;

                if (*dataSize < sizePresumedPacket){
                    returnValue = 0; // data is not enough for a new packet stop the loop
                }
                else{
                    returnValue = 1;// data is  enough for a new packet keep the loop going 
                }
            } 
            else {
                returnValue = 1; // junk data keep the loop going 
            }
            
            free(peekData); 
        }
        
        return returnValue;
    }
}

/*! *********************************************************************************
* \brief    Returns the start state of the state machine.
*
* \return a value of  FSCIStateMachine
********************************************************************************** */
int FSCIStartState (void)
{
    return FSCI_SM_JUNK_DATA;
}

/*! *********************************************************************************
* \brief    Returns the final state of the state machine.
*
* \return a value of  FSCIStateMachine
********************************************************************************** */
int FSCIFinalState (void)
{
    return FSCI_SM_FINISHED_FRAME;
}

/*! *********************************************************************************
* \brief    Initializes the function pointers of the framer to the specific
*           FSCI functions.
*
* \param[in,out] framer     pointer to a framer
*
* \return None
********************************************************************************** */
void FSCIFramerInitialization(Framer *framer)
{
    framer->CreatePacket = CreateFSCIPacket;
    framer->StateMachineDispatch = FSCIStateMachineDispatch;
    framer->QueueDataVerification = FSCIQueueDataVerification;
    framer->SMStartState = FSCIStartState;
    framer->SMFinalState = FSCIFinalState;
}

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
* \brief    Private function for creation of a byte array which represents a FSCI Frame.
*
* \param[in] framer         pointer to the Framer
* \param[in] ogf            the opgroup of the frame
* \param[in] ocf            the opcode of the frame
* \param[in] length         the size of the payload
* \param[in] data           the payload of the frame
* \param[in] crc            the checksum of the frame
* \param[in] crcFieldSize   the size of the checksum
* \param[in] size           secondary return value - total size of the packet
*
* \return   NULL in case of allocation failure, otherwise an array of bytes with the
*           elements of the frame
********************************************************************************** */
static uint8_t *CreatePacket(Framer *framer, uint8_t ogf, uint8_t ocf, uint32_t length, uint8_t *data, uint32_t crc, uint8_t crcFieldSize, uint32_t *size)
{
    uint8_t *packet;
    uint8_t arCRC[2];
    uint8_t len[2];
    unsigned int i, crt = 0;
    /* CreatePacket creates a command packets and calculates its length from the
       protocol descriptor variable. */
    *size = FSCI_SYNC_SIZE + FSCI_OGF_SIZE + FSCI_OCF_SIZE + framer->lengthFieldSize + length + crcFieldSize;

    packet = (uint8_t *) calloc(*size, sizeof(uint8_t));

    if (!packet) {
        return NULL;
    }

    packet[crt++] = FSCI_SYNC_BYTE;
    packet[crt++] = ogf;
    packet[crt++] = ocf;

    Store16(length, len, framer->framerEndianness);

    for (i = 0; i < framer->lengthFieldSize; i++) {
        packet[crt++] = len[i];
    }

    for (i = 0; i < length; i++) {
        packet[crt++] = data[i];
    }

    Store16(crc, arCRC, framer->framerEndianness);

    for (i = 0; i < crcFieldSize; i++) {
        packet[crt++] = arCRC[i];
    }

    return packet;
}

/*! *********************************************************************************
* \brief    Computes the XOR CRC validation code for the received FSCIFrame.
*
* \param[in] framer     a pointer to the Framer
* \param[in] frame      a pointer to a FSCI frame on which to do the XOR computation
*
* \return a byte containing the CRC value
********************************************************************************** */
static uint8_t CalculateCRC(Framer *framer, FSCIFrame *frame)
{
    uint8_t crc = 0;
    uint16_t i;

    crc ^= frame->opGroup;
    crc ^= frame->opCode;

    if (framer->lengthFieldSize == 1) {
        crc ^= frame->length;
    } else {
        uint8_t arLength[2];
        Store16(frame->length, arLength, framer->framerEndianness);

        for (i = 0; i < framer->lengthFieldSize; i++) {
            crc ^= arLength[i];
        }
    }

    for (i = 0; i < frame->length; i++) {
        crc ^= frame->data[i];
    }

    return crc;
}

/*! *********************************************************************************
* \brief    Handles the creation of a new FSCIFrame.
*
* \param[in] framer     pointer to the Framer from where the message queue is accessed
*
* \return a pointer to a FSCIFrame
********************************************************************************** */
static FSCIFrame *FSCIHandleNewFrame(Framer *framer)
{
    MessageQueue *queue = framer->queue;

    RawFrame *rawFrame = (RawFrame *)PeekFront(queue);

    if (rawFrame == NULL) {
        logMessage(HSDK_WARNING, "[FSCIFramer]FSCIHandleNewFrame", "PeekFront returned NULL", HSDKThreadId());
        return NULL;
    }

    FSCIFrame *workingCopy = (FSCIFrame *)calloc(1, sizeof(FSCIFrame));

    if (workingCopy == NULL) {
        logMessage(HSDK_WARNING, "[FSCIFramer]FSCIHandleNewFrame", "workingCopy memory allocation failed", HSDKThreadId());
        return NULL;
    }

    workingCopy->timeStamp = rawFrame->timeStamp;
    workingCopy->index = rawFrame->packetIndex;

    return workingCopy;
}

/*! *********************************************************************************
* \brief    Handles the case for junk data. Data is considered junk until the first
*           valid frame starting with SYNC.
*
* \param[in] framer             pointer to the Framer from where the message queue is accessed
* \param[in, out] currentFrame  pointer to a pointer to the FSCIFrame that is being constructed
* \param[in, out] dataSize      pointer to a variable indicating the size of the queue
*
* \return the status of the frame
********************************************************************************** */
static FrameStatus FSCIJunkData(Framer *framer, FSCIFrame **currentFrame, uint32_t *dataSize)
{
    MessageQueue *queue = framer->queue;
    FSCIFrame *workingCopy = *currentFrame;
    uint16_t cbJunkSize = 0;
    uint8_t found = 0;
    workingCopy->data = ReadDataUntilByte(queue, &cbJunkSize, FSCI_SYNC_BYTE, &found);

    if (!cbJunkSize) {
        free(workingCopy->data);
        workingCopy->data = NULL;
        framer->currentState = FSCI_SM_SYNC;
        return SUFFICIENT_DATA;
    } else {
        workingCopy->length = cbJunkSize;
        *dataSize -= cbJunkSize;
        framer->currentState = FSCI_SM_FINISHED_FRAME;
        return JUNK_DATA;
    }
}

/*! *********************************************************************************
* \brief    Handles the case for the SYNC byte.
*
* \param[in] framer             pointer to the Framer from where the message queue is accessed
* \param[in, out] currentFrame  pointer to a pointer to the FSCIFrame that is being constructed
* \param[in, out] dataSize      pointer to a variable indicating the size of the queue
*
* \return the status of the frame
********************************************************************************** */
static FrameStatus FSCISyncField(Framer *framer, FSCIFrame **currentFrame, uint32_t *dataSize)
{
    if (*dataSize < 1)
        return INSUFFICIENT_DATA;

    MessageQueue *queue = framer->queue;
    (*currentFrame)->sync = ReadSingleByte(queue);
    *dataSize -= 1;
    framer->currentState = FSCI_SM_OGF;
    return SUFFICIENT_DATA;
}

/*! *********************************************************************************
* \brief    Handles the case for the OPGROUP byte.
*
* \param[in] framer             pointer to the Framer from where the message queue is accessed
* \param[in, out] currentFrame  pointer to a pointer to the FSCIFrame that is being constructed
* \param[in, out] dataSize      pointer to a variable indicating the size of the queue
*
* \return the status of the frame
********************************************************************************** */
static FrameStatus FSCIOpGroupField(Framer *framer, FSCIFrame **currentFrame, uint32_t *dataSize)
{
    if (*dataSize < 1)
        return INSUFFICIENT_DATA;

    MessageQueue *queue = framer->queue;
    (*currentFrame)->opGroup = ReadSingleByte(queue);
    *dataSize -= 1;
    framer->currentState = FSCI_SM_OCF;
    return SUFFICIENT_DATA;
}

/*! *********************************************************************************
* \brief    Handles the case for the OPCODE byte.
*
* \param[in] framer             pointer to the Framer from where the message queue is accessed
* \param[in, out] currentFrame  pointer to a pointer to the FSCIFrame that is being constructed
* \param[in, out] dataSize      pointer to a variable indicating the size of the queue
*
* \return the status of the frame
********************************************************************************** */
static FrameStatus FSCIOpCodeField(Framer *framer, FSCIFrame **currentFrame, uint32_t *dataSize)
{
    if (*dataSize < 1)
        return INSUFFICIENT_DATA;

    MessageQueue *queue = framer->queue;
    (*currentFrame)->opCode = ReadSingleByte(queue);
    *dataSize -= 1;
    framer->currentState = FSCI_SM_LENGTH;
    return SUFFICIENT_DATA;
}

/*! *********************************************************************************
* \brief    Handles the case for the Length byte(s). The number of bytes of length is
*           determined by LengthFieldSize.
*
* \param[in] framer             pointer to the Framer from where the message queue is accessed
* \param[in, out] currentFrame  pointer to a pointer to the FSCIFrame that is being constructed
* \param[in, out] dataSize      pointer to a variable indicating the size of the queue
*
* \return the status of the frame
********************************************************************************** */
static FrameStatus FSCILengthField(Framer *framer, FSCIFrame **currentFrame, uint32_t *dataSize)
{
    if (*dataSize < framer->lengthFieldSize)
        return INSUFFICIENT_DATA;

    MessageQueue *queue = framer->queue;
    FSCIFrame *workingCopy = *currentFrame;

    if (framer->lengthFieldSize == 1) {
        workingCopy->length = ReadSingleByte(queue);
    } else {
        uint8_t *multibyte_length = ReadMultiByte(queue, framer->lengthFieldSize);
        workingCopy->length = Read16(multibyte_length, framer->framerEndianness);
        free(multibyte_length);
    }

    *dataSize -= framer->lengthFieldSize;

    /* protection against very large or desynchronized FSCI or IPv6 packets */
    if (workingCopy->length > FSCI_MTU) {
        workingCopy = NULL;
        framer->currentState = FSCIStartState();
        return JUNK_DATA;
    } else {
        framer->currentState = FSCI_SM_DATA;
        return SUFFICIENT_DATA;
    }

}

/*! *********************************************************************************
* \brief    Handles the case for the Data field.
*
* \param[in] framer             pointer to the Framer from where the message queue is accessed
* \param[in, out] currentFrame  pointer to a pointer to the FSCIFrame that is being constructed
* \param[in, out] dataSize      pointer to a variable indicating the size of the queue
*
* \return the status of the frame
********************************************************************************** */
static FrameStatus FSCIDataField(Framer *framer, FSCIFrame **currentFrame, uint32_t *dataSize)
{
    if (*dataSize < (*currentFrame)->length) {
        return INSUFFICIENT_DATA;
    }

    MessageQueue *queue = framer->queue;
    (*currentFrame)->data = ReadMultiByte(queue, (*currentFrame)->length);
    *dataSize -= (*currentFrame)->length;
    framer->currentState = FSCI_SM_CRC_FST;
    return SUFFICIENT_DATA;
}

/*! *********************************************************************************
* \brief    Handles the case for the checksum byte.
*
* \param[in] framer             pointer to the Framer from where the message queue is accessed
* \param[in, out] currentFrame  pointer to a pointer to the FSCIFrame that is being constructed
* \param[in, out] dataSize      pointer to a variable indicating the size of the queue
*
* \return the status of the frame
********************************************************************************** */
static FrameStatus FSCICrcField(Framer *framer, FSCIFrame **currentFrame, uint32_t *dataSize)
{
    if (*dataSize < 1) {
        return INSUFFICIENT_DATA;
    }

    FSCIFrame *workingCopy = *currentFrame;

    MessageQueue *queue = framer->queue;
    uint8_t crc = ReadSingleByte(queue);
    uint8_t calculatedCRC = CalculateCRC(framer, workingCopy);

    workingCopy->crc = crc;
    *dataSize -= 1;

    if (framer->crcFieldSize == 2) {
        framer->currentState = FSCI_SM_CRC_SND;

        if (*dataSize > 0) {
            return SUFFICIENT_DATA;
        } else {
            return INSUFFICIENT_DATA;
        }
    } else if (crc == calculatedCRC) {
        framer->currentState = FSCI_SM_FINISHED_FRAME;
        return VALID_FRAME;
    } else {
        framer->currentState = FSCI_SM_FINISHED_FRAME;
        return INVALID_CRC;
    }
}

/*! *********************************************************************************
* \brief    Handles the case in which a second byte for the checksum is required.
*
* \param[in] framer             pointer to the Framer from where the message queue is accessed
* \param[in, out] currentFrame  pointer to a pointer to the FSCIFrame that is being constructed
* \param[in, out] dataSize      pointer to a variable indicating the size of the queue
*
* \return the status of the frame
********************************************************************************** */
static FrameStatus FSCISecondCrcField(Framer *framer, FSCIFrame **currentFrame, uint32_t *dataSize)
{
    /* Mark second CRC byte state as final in the processing chain. */
    framer->currentState = FSCI_SM_FINISHED_FRAME;

    if (*dataSize < 1) {
        return INVALID_CRC;
    }

    MessageQueue *queue = framer->queue;
    FSCIFrame *workingCopy = *currentFrame;
    uint8_t crc = ReadSingleByte(queue);
    *dataSize -= 1;

    uint8_t calculatedCRC = CalculateCRC(framer, workingCopy);
    uint8_t oldCRC = workingCopy->crc;

    uint8_t aCRCArray[2] = {oldCRC, crc};
    workingCopy->crc = Read16(aCRCArray, framer->framerEndianness);

    if ((oldCRC ^ calculatedCRC) == crc) {
        return VALID_FRAME;
    } else {
        return INVALID_CRC;
    }
}
