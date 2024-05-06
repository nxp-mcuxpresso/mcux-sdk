/*
 * \file SPIConfiguration.h
 * This is the header file for the SPIConfiguration module.
 *
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SPI_CONFIGURATION__
#define __SPI_CONFIGURATION__

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include <linux/spi/spidev.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <time.h>

#include "hsdkOSCommon.h"
#include "hsdkLogger.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! *********************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
********************************************************************************** */
/**
 * @brief Structure to encompass the attributes required for SPI configuration.
 */
typedef struct {
    uint8_t lengthFieldSize;  // the number of bytes the length field has in protocols
    uint8_t transferMode;
    // uint32_t fullTransferMode;
    // uint8_t bitJustification;
    uint8_t bitsPerWord;
    uint32_t maxSpeedHz;
} SPIConfigurationData;

/*! *********************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
********************************************************************************** */
SPIConfigurationData *defaultSettingsSPI();
void freeSettingsSPI(SPIConfigurationData *);
void setLengthFieldSize(SPIConfigurationData *, uint8_t);
void setSpeedHzSPI(SPIConfigurationData *, uint32_t);
int initPortSPI(File, SPIConfigurationData *);

#ifdef __cplusplus
}
#endif

#endif
