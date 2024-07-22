/*
 * \file hsdkLogger.h
 * This is the header file for the Logger module.
 *
 * Copyright 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __HSDK_LOGGER__
#define __HSDK_LOGGER__

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "hsdkOSCommon.h"
#include "MessageQueue.h"

#ifdef __cplusplus
extern "C" {
#endif
/*! *********************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
********************************************************************************** */
/**
 * @brief The logger structure, containing a thread, a queue of messages to be
 * logged, a message count and an event signaling the end of logging.
 */
typedef struct {
    Thread loggerThread;	/**< A separate thread for the Logger. */
    MessageQueue *queue;	/**< Queue for Logger messages. */
    int referenceCount;		/**< The number of the logged messages. */
    Event stopThread;		/**< Event for signaling the Logger to stop. */
} Logger;

/*! *********************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
********************************************************************************** */
#define HSDK_ERROR 1
#define HSDK_WARNING 2
#define HSDK_INFO 3

/*! *********************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
********************************************************************************** */
void logMessage(int prio, const char *messageTag, const char *message, int threadId);
void initLogger(char *filename);
void closeLogger();

#ifdef __cplusplus
}
#endif

#endif
