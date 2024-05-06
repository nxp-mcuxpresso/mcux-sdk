/*
 * \file PhysicalDevice.h
 * This is the header file for the PhysicalDevice module.
 *
 * Copyright 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __PHYS_DEVICE__
#define __PHYS_DEVICE__

/*! *********************************************************************************
*************************************************************************************
* Include
*************************************************************************************
********************************************************************************** */
#include <stdint.h>

#include "EventManager.h"
#include "hsdkOSCommon.h"
#include "MessageQueue.h"
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
*************************************************************************************
* Public type definitions
*************************************************************************************
********************************************************************************** */
/**
 * @brief Types of devices supported.
 */
typedef enum {
    UART,
    USB,
    PCAP,
    SPI,
    BT
} DeviceType;

/**
 * @brief Status of the device.
 */
typedef enum {
    PHYS_CLOSED,
    PHYS_OPENED,
    PHYS_ERROR
} DeviceStatus;

/**
* @brief Available policies for FSCI ACK synchronization.
*/
typedef enum {
    NONE,
    TX,
    RX,
    TX_RX,
    GLOBAL
} FsciAckPolicy;

/**
 * @brief Generic structure for interfacing with the lower level hardware.
 */
typedef struct {
    DeviceType type;            /**< The type of the device. */
    DeviceStatus status;        /**< Status of the physical device. */
    void *configurationData;    /**< Generic pointer to the specific device structure. */
    ConfigParams *configParams; /**< Pointer to the configuration parameters. */
    MessageQueue *inMessages;   /**< An inbox message queue for the device from which to send to the hardware. */
    EventManager *evtManager;   /**< Subscription based event handler to notify all registered components of an event. */
    void *deviceHandle;         /**< A generic handle for the device to send and receive data. */
    Thread eventThread;         /**< The thread to wait for events from the device. */
    Event startThread;          /**< An event used to synchronize the main thread and the eventThread. */
    Event stopThread;           /**< An event used to signal the eventThread to stop. */

    int(*open) (void *, void *);                /**< Function pointer for the device specific open function. It passes specificData as an argument. */
    int(*close) (void *);                       /**< Function pointer for the device specific close function. */
    int(*write) (void *, uint8_t *, uint32_t);  /**< Function pointer to the device specific function to write data into it. */
    int(*read) (void *, uint8_t *, uint32_t *); /**< Function pointer to the device specific function for reading data from it. */
    int(*initialize) (void *, uint8_t);         /**< SPI specific: read data available on the bus at thread start. */
    int(*configure) (void *, void *);           /**< Configuration function. */

    Event (*waitable) (void *, void **); /**< A pointer to a function that returns an event that is waitable until the data has arrived to be read. */

    Event sAnnounceTXACK;           /**< A semaphore to indicate TX ACK has been received */
    Event     startTXACKTimeoutThread;  /**< An event used to synchronize the ACK timeout thread and the startTXACKTimeoutThread. */
    Event     stopTXACKTimeoutThread;   /**< An event used to synchronize the ACK timeout thread and the stopTXACKTimeoutThread. */
} PhysicalDevice;


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
DLLEXPORT PhysicalDevice *InitPhysicalDevice(DeviceType, void *, char *, FsciAckPolicy);
DLLEXPORT int DestroyPhysicalDevice(PhysicalDevice *);
DLLEXPORT int OpenPhysicalDevice(PhysicalDevice *);
DLLEXPORT int ClosePhysicalDevice(PhysicalDevice *);
DLLEXPORT int ConfigurePhysicalDevice(PhysicalDevice *, void *);
DLLEXPORT int WritePhysicalDevice(void *, uint8_t *, uint32_t);
DLLEXPORT void AttachToPhysicalDevice(void *, void *, void(*Callback)(void *, void *));
DLLEXPORT void DetachFromPhysicalDevice(void *, void *);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
