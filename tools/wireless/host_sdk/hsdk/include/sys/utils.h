/*
 * \file utils.h
 * This is the header file for the helper functions.
 *
 * Copyright 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __UTILS__
#define __UTILS__

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WINDLL
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif
#ifdef __cplusplus
extern "C" {
#endif

/*! *********************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
********************************************************************************** */
/**
 * @brief Endianness types.
 */
typedef enum {
    _BIG_ENDIAN,
    _LITTLE_ENDIAN,
    _UNKNOWN_ENDIAN
} endianness;

/**
 * @brief Structure to store configuration parameters.
 */
typedef struct {
    uint8_t fsciTxAck;
    uint8_t numberOfRetries;
    int timeoutAckMs;
    uint8_t fsciRxAck;
} ConfigParams;

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
DLLEXPORT void Store16(uint16_t, uint8_t *, endianness);
DLLEXPORT void Store32(uint32_t, uint8_t *, endianness);
DLLEXPORT void Store64(uint64_t, uint8_t *, endianness);
DLLEXPORT uint16_t Read16(uint8_t *, endianness);
DLLEXPORT uint32_t Read32(uint8_t *, endianness);
DLLEXPORT uint64_t Read64(uint8_t *, endianness);
DLLEXPORT ConfigParams *ParseConfig(void);
DLLEXPORT char *UARTSystemPath(char *uartPath);

#ifdef __cplusplus
}
#endif

#endif
