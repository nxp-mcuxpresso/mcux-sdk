/*
 * \file PCAPDevice.h
 * This is the header file for the PCAPDevice module.
 *
 * Copyright 2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __PCAP_DEV_
#define __PCAP_DEV_

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include <pcap.h>

#include "PhysicalDevice.h"

/*! *********************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
********************************************************************************** */
/**
 * @brief Structure to identify a PCAP device.
 */
typedef struct {
    char *ifName;            /**< The network interface name in the operating system. */
    pcap_t *ifHandle;        /**< The file abstraction of the device in the operating system. */
    PhysicalDevice *parent;  /**< Needed for auto-recovery. */
} PCAPHandle;

/*! *********************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
********************************************************************************** */
int AttachToPCAPDevice(PhysicalDevice *pDevice, char *ifName);
int DetachFromPCAPDevice(PhysicalDevice *pDevice);
void *PCAPLoopThreadRoutine(void *pDevice);

#endif
