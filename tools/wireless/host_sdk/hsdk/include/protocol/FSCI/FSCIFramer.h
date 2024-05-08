/*
 * \file FsciFramer.h
 * This is the header file for the FsciFramer module.
 *
 * Copyright 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __FSCI_FRAMER__
#define __FSCI_FRAMER__


/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include <stdint.h>

#include "Framer.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! *********************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
********************************************************************************** */
/**
 * @brief The FSCI state machine can be found in these states.
 */
typedef enum {
    FSCI_SM_JUNK_DATA,
    FSCI_SM_SYNC,
    FSCI_SM_OGF,
    FSCI_SM_OCF,
    FSCI_SM_LENGTH,
    FSCI_SM_DATA,
    FSCI_SM_CRC_FST,
    FSCI_SM_CRC_SND,
    FSCI_SM_FINISHED_FRAME
} FSCIStateMachine;

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
uint8_t *CreateFSCIPacket(Framer *framer, void *, uint32_t *);
int FSCIStartState (void);
int FSCIFinalState (void);
FrameStatus FSCIStateMachineDispatch(Framer *framer, void **currentFrame, uint32_t *dataSize);
int FSCIQueueDataVerification(Framer *framer, uint32_t *dataSize);
void FSCIFramerInitialization(Framer *framer);
DLLEXPORT void FSCI_transmitPayload(Framer *framer, uint8_t OG, uint8_t OC, void *pMsg, uint16_t msgLen, uint32_t fsciInterface);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
