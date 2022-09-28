/*
 * \file RawFrame.c
 * This is a source file for the RawFrame module.
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
#include <stdlib.h>
#include <string.h>
#include "RawFrame.h"

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
RawFrame *CreateRawFrame(uint8_t *data, uint32_t size);

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
uint32_t RxIndex = 0;
uint32_t TxIndex = 0;

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
* \brief    Returns a FSCI-ACK frame.
*
* \param[in] lengthFieldSize    the size of the length field in bytes
*
* \return   a pointer to a byte array containing the data
********************************************************************************** */
uint8_t *GetAckFrame(uint8_t lengthFieldSize)
{
    static const uint8_t fsciAck1[6] =  { 0x02, 0xA4, 0xFD, 0x01, 0x00, 0x58 };
    static const uint8_t fsciAck2[7] =  { 0x02, 0xA4, 0xFD, 0x01, 0x00, 0x00, 0x58 };

    return (lengthFieldSize == 1) ? (uint8_t *)fsciAck1 : (uint8_t *)fsciAck2;
}

/*! *********************************************************************************
* \brief    Creates a received RawFrame. It increments rx counter
*
* \param[in,out] data
* \param[in,out] size
*
* \return   NULL on allocation failure, a pointer to a RawFrame object containing the
*           data
********************************************************************************** */
RawFrame *CreateRxRawFrame(uint8_t *data, uint32_t size)
{
    RawFrame *frame = CreateRawFrame(data, size);
    frame->packetIndex = RxIndex++;

    return frame;
}

/*! *********************************************************************************
* \brief    Creates a received RawFrame. It increments tx counter
*
* \param[in,out] data
* \param[in,out] size
*
* \return   NULL on allocation failure, a pointer to a RawFrame object containing the
*           data
********************************************************************************** */
RawFrame *CreateTxRawFrame(uint8_t *data, uint32_t size)
{
    RawFrame *frame = CreateRawFrame(data, size);
    frame->packetIndex = TxIndex++;
    return frame;
}


/*! *********************************************************************************
* \brief    Free the memory allocated for a RawFrame object.
*
* \param[in,out] frame
*
* \return   none
********************************************************************************** */
void DestroyRawFrame(RawFrame *frame)
{
    if (frame != NULL) {
        if (frame->aRawData != NULL) {
            free(frame->aRawData);
        }

        frame->aRawData = NULL;
        free(frame);
    }
}

RawFrame *CloneRawFrame(RawFrame *frame)
{
    RawFrame *newFrame = (RawFrame *)calloc(1, sizeof(RawFrame));

    if (!newFrame) {
        return NULL;
    }

    newFrame->timeStamp = frame->timeStamp;
    newFrame->aRawData = (uint8_t *)calloc(frame->cbTotalSize, sizeof(uint8_t));

    if (!newFrame->aRawData) {
        free(newFrame);
        return NULL;
    }

    memcpy(newFrame->aRawData, frame->aRawData, frame->cbTotalSize);

    newFrame->cbTotalSize = frame->cbTotalSize;
    newFrame->iCrtIndex = frame->iCrtIndex;
    newFrame->packetIndex = frame->packetIndex;

    return newFrame;
}


/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
* \brief    Creates a RawFrame. A RawFrame represents bytes received from the device
*           layer without any logical ordering into a format.
*
* \param[in,out] data
* \param[in,out] size
*
* \return   NULL on allocation failure, a pointer to a RawFrame object containing the
*           data
********************************************************************************** */
RawFrame *CreateRawFrame(uint8_t *data, uint32_t size)
{
    RawFrame *frame = (RawFrame *)calloc(1, sizeof(RawFrame));

    if (!frame) {
        return NULL;
    }

    frame->timeStamp = time(NULL);
    frame->aRawData = (uint8_t *)calloc(size, sizeof(uint8_t));

    if (!frame->aRawData) {
        free(frame);
        return NULL;
    }

    memcpy(frame->aRawData, data, size);

    frame->cbTotalSize = size;
    frame->iCrtIndex = 0;

    return frame;
}
