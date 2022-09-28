/*
 * \file UARTDiscovery.h
 * This is the header file for the UARTDiscovery module.
 *
 * Copyright 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __UART_STATE__
#define __UART_STATE__

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include <stdint.h>

#include "EventManager.h"
#include "hsdkOSCommon.h"

#ifdef _WINDLL
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief The availability state of a UART device.
 */
typedef enum {
    NoInfo,
    Available,
    NotPluggedIn,
    InUse,
    DeviceError,
} Availability;

/**
 * @brief A structure for representing the state of a discovered device.
 */
typedef struct {
    Availability state;         /**< The state in which the device is currently in. */
    char *friendlyName;         /**< The human-readable name used in the system for the device. */
    char *deviceName;           /**< The system path of the device. */
    uint8_t isKinetisWDevice;   /**< Boolean for whether the device is a NXP Kinetis-W. */
    char *vid;                  /**< The vendor id of the device. */
    char *pid;                  /**< The product id of the device. */
} DeviceState;

/**
 * @brief The type of the hotplug triggered event.
 */
typedef enum {
    DeviceAdded,
    DeviceRemoved,
} DeviceNotificationEvent;

/**
 * @brief Structure to describe a device notification.
 */
typedef struct {
    DeviceNotificationEvent notifyEvent;    /**< The type of the event. */
    DeviceState *state;                     /**< The state of the device. */
} DeviceNotification;

/*! *********************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
********************************************************************************** */
DLLEXPORT DeviceState *GetAllDevices(uint32_t *);
DLLEXPORT void InitializeDeviceManager();
DLLEXPORT void DestroyDeviceManager();
DLLEXPORT void AttachToDeviceNotification(void *observer, void(*Callback) (void *, void *));
DLLEXPORT void DetachFromDeviceNotification(void *observer);
DLLEXPORT void DestroyDeviceState(DeviceState *deviceState);
DLLEXPORT void DestroyDeviceNotification(DeviceNotification *deviceNotification);
DLLEXPORT int isKinetisWDevice(const char *, const char *);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
