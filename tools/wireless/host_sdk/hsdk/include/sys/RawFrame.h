/*
 * \file RawFrame.h
 * This is the header file for the RawFrame module.
 *
 * Copyright 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __RAWFRAME_H__
#define __RAWFRAME_H__

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include <stdint.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WINDLL
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

/*! *********************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
********************************************************************************** */
/**
 * @brief Simple structure for encapsulating data. Has no protocol representation.
 */
typedef struct {
    uint32_t packetIndex;   /**< The index of the global count of RawFrames created. */
    uint8_t *aRawData;      /**< An array containing the data stored in the RawFrame. */
    uint32_t cbTotalSize;   /**< The size of the payload of the RawFrame. */
    uint32_t iCrtIndex;     /**< An index into the array used in processing the data contained within the structure. */
    time_t timeStamp;       /**< Timestamp of the creation of the RawFrame. */
} RawFrame;

/*! *********************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
********************************************************************************** */

/*! *********************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
********************************************************************************** */

/*! *********************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
********************************************************************************** */
uint8_t *GetAckFrame(uint8_t lengthFieldSize);
RawFrame *CreateTxRawFrame(uint8_t *data, uint32_t size);
RawFrame *CreateRxRawFrame(uint8_t *data, uint32_t size);
RawFrame *CloneRawFrame(RawFrame *frame);
DLLEXPORT void DestroyRawFrame(RawFrame *frame);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
