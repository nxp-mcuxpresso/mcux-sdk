/*
 * \file SPIDevice.h
 * This is the header file for the SPIDevice module.
 *
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SPI_DEV__
#define __SPI_DEV__

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include <fcntl.h>
#include <unistd.h>
#include <linux/types.h>

#include "hsdkOSCommon.h"
#include "PhysicalDevice.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! *********************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
********************************************************************************** */
/**
 * @brief Structure to identify a SPI port.
 */
typedef struct {
    /*/dev/spidevB.C ... character special device, major number 153 with
    a dynamically chosen minor device number.  This is the node
    that userspace programs will open, created by "udev" or "mdev". */
    char *deviceName;
    /* The file descriptor abstraction of the device in the operating system. */
    File portHandle;
    /* Used to block for interrupts. */
    File uioPortHandle;
    /* Used to read packets in two chunks: header + payload and CRC. */
    uint8_t lengthFieldSize;
} SPIHandle;

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
#define DK07_HOST       (1)
#define IMX6ULEVK_HOST  (0)

#if DK07_HOST
    #define SPI_DAP_DEV "/sys/class/gpio/gpio42/value"
    #define SPI_CS_DEV  "/sys/class/gpio/gpio45/value"
#elif IMX6ULEVK_HOST
    #define SPI_DAP_DEV "/dev/uio0"
#else
    #error "Please select an SPI master host!"
#endif

/*! *********************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
********************************************************************************** */
int AttachToSPIDevice(PhysicalDevice *pDevice, char *deviceName);
int DetachFromSPIDevice(PhysicalDevice *pDevice);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
