/*
 * \file FsciFrame.h
 * This is the header file for the FsciFrame module.
 *
 * Copyright 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __FSCI_FRAME__
#define __FSCI_FRAME__

/************************************************************************************
 ************************************************************************************
 * Include
 ************************************************************************************
 ***********************************************************************************/
#include <stdint.h>
#include <time.h>

#include "Framer.h"
#include "utils.h"

#ifdef _WINDLL
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*! *********************************************************************************
 ************************************************************************************
 * Public type definitions
 ************************************************************************************
 ********************************************************************************* */
/**
 * @brief A structure for the FSCI protocol.
 */
typedef struct {
    uint8_t sync;       /**< The sync byte field. */
    uint8_t opGroup;    /**< The operation group of the command or event. */
    uint8_t opCode;     /**< The operation code of the command or event. */
    uint32_t length;    /**< The length of the payload of the FSCIFrame. */
    uint8_t *data;      /**< The payload of the FSCIFrame. */
    /*! The checksum value of the frame. A XOR CRC between the bytes in length, data,
     * opCode, opGroup. This value is modified with the virtualInterface value, adding
     * a second byte to the CRC field in case the virtualInterface is not 0
     */
    uint32_t crc;
    /*! Timestamp of the FSCIFrame. It is the recorded timestamp of the RX of the SYNC
     * byte of the current FSCI if it is a received frame. It is the creation time of a
     * TX frame.
     */
    time_t timeStamp;
    uint32_t index;             /**< The index in the global sequence of received packets of the packet containing the SYNC byte. */
    endianness endian;          /**< The endianness of the frame. */
    uint8_t virtualInterface;   /**< The virtual interface on which the FSCIFrame is going to operate. */
} FSCIFrame;

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
/* The start byte of a FSCI frame. */
#define FSCI_SYNC_BYTE 0x02

/* Command field sizes. */
#define FSCI_SYNC_SIZE 1
#define FSCI_OGF_SIZE 1
#define FSCI_OCF_SIZE 1
#define MAX_CRC_SIZE 1
#define EXPECTED_CRC_SIZE 1

/*! *********************************************************************************
 ************************************************************************************
 * Public prototypes
 ************************************************************************************
 ********************************************************************************* */
DLLEXPORT FSCIFrame *CreateFSCIFrameAdHoc(uint8_t opGroup, uint8_t opCode, uint8_t *data, uint32_t length, uint8_t virtualId, uint8_t lengthFieldSize, endianness endian);
DLLEXPORT FSCIFrame *CreateFSCIFrame(Framer *framer, uint8_t opGroup, uint8_t opCode, uint8_t *data, uint32_t length, uint8_t virtualId);
DLLEXPORT FSCIFrame *CreateRawFSCIFrameAdHoc(uint8_t sync, uint8_t opGroup, uint8_t opCode, uint8_t *data, uint32_t length, uint32_t crc, uint8_t virtualId, endianness endian);
DLLEXPORT FSCIFrame *CreateRawFSCIFrame(Framer *framer, uint8_t sync, uint8_t opGroup, uint8_t opCode, uint8_t *data, uint32_t length, uint32_t crc, uint8_t virtualId);
DLLEXPORT void DestroyFSCIFrame(FSCIFrame *);
DLLEXPORT void PrintFSCIFrame(Framer *, FSCIFrame *);

#ifdef __cplusplus
}
#endif

#endif
