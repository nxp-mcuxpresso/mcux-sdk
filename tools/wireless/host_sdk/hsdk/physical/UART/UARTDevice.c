/*
 * \file UARTDevice.c
 * This is a source file for the UARTDevice module.
 *
 * Copyright 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "PhysicalDevice.h"
#include "UARTDevice.h"
#include "UARTConfiguration.h"

#include "hsdkLogger.h"

#include "hsdkError.h"

#define MAX_LENGTH 256

/************************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
************************************************************************************/
static UARTHandle *InitUARTDevice(char *);
static int DestroyUARTDevice(UARTHandle *);
static void InitDeviceAsUART(PhysicalDevice *device);
static int UARTOpenPort(void *pDevice, void *configData);
static int UARTClosePort(void *pDevice);
static int UARTWrite(void *specificData, uint8_t *buf, uint32_t size);
static int UARTRead(void *specificData, uint8_t *buf, uint32_t *size);
static int UARTConfigure(void *specificData, void *configData);
static Event UARTGetWaitEvent(void *, void **);

/************************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

int AttachToUARTDevice(PhysicalDevice *pDevice, char *deviceName)
{
    pDevice->deviceHandle = InitUARTDevice(deviceName);
    if (!pDevice->deviceHandle) {
        return HSDK_ERROR_ALLOC;
    }
    InitDeviceAsUART(pDevice);

    return HSDK_ERROR_SUCCESS;
}

int DetachFromUARTDevice(PhysicalDevice *pDevice)
{
    int rc = DestroyUARTDevice((UARTHandle *)pDevice->deviceHandle);
    if (rc != HSDK_ERROR_SUCCESS) {
        return rc;
    }

    pDevice->deviceHandle = NULL;
    pDevice->open = NULL;
    pDevice->close = NULL;
    pDevice->read = NULL;
    pDevice->write = NULL;
    pDevice->configure = NULL;

    return HSDK_ERROR_SUCCESS;
}

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/
void InitDeviceAsUART(PhysicalDevice *device)
{
    device->open = UARTOpenPort;
    device->close = UARTClosePort;
    device->read = UARTRead;
    device->write = UARTWrite;
    device->configure = UARTConfigure;
    device->waitable = UARTGetWaitEvent;
}

/*! *********************************************************************************
* \brief  Initializes an UART device.
*
* \param[in] deviceName the name of the port for which the device is to be initialized
*
* \return a pointer to an UARTHandle
********************************************************************************** */
UARTHandle *InitUARTDevice(char *deviceName)
{
    if (!deviceName || strnlen(deviceName, MAX_LENGTH) == 0) {
        logMessage(HSDK_ERROR, "[UARTDevice]InitUARTDevice", "Device name is null or empty", HSDKThreadId());
        return NULL;
    }

    UARTHandle *device = (UARTHandle *)calloc(1, sizeof(UARTHandle));

    if (!device) {
        logMessage(HSDK_ERROR, "[UARTDevice]InitUARTDevice", "Memory allocation failed", HSDKThreadId());
        return NULL;
    }

    device->deviceName = strdup(deviceName);
    HSDKInvalidateDescriptor(&device->portHandle);
    return device;
}

/*! *********************************************************************************
* \brief  Free the space allocated for the uart device as well as the events
*
* \param[in] device pointer to the
*
* \return 0 for success, -1 for failure
********************************************************************************** */
int DestroyUARTDevice(UARTHandle *device)
{
    if (!device) {
        logMessage(HSDK_ERROR, "[UARTDevice]DestroyUARTDevice", "Argument is null", HSDKThreadId());
        return HSDK_ERROR_INVALID;
    }

    if (HSDKIsDescriptorValid(device->portHandle)) {
        int err = UARTClosePort(device);
        if (err != HSDK_ERROR_SUCCESS) {
            return err;
        }
    }

    free(device->deviceName);
    device->deviceName = NULL;
    free(device);

    return HSDK_ERROR_SUCCESS;
}


static Event UARTGetWaitEvent(void *device, void **asyncMask)
{
    UARTHandle *pDevice = (UARTHandle *)device;
    return HSDKDeviceTriggerableEvent(pDevice->portHandle, asyncMask);
}


/*! *********************************************************************************
* \brief  Opens the specified port and creates the thread
*
* \param[in] pDevice    pointer to a UART handle
* \param[in] configData configuration data to be used in configuring the UART port
*
* \return 0 for success, -1 for failure
********************************************************************************** */
static int UARTOpenPort(void *pDevice, void *configData)
{
    int freeConfig = 0, rc = HSDK_ERROR_SUCCESS;

    UARTHandle *device = (UARTHandle *)pDevice;
#ifdef _WIN32
    char *systemPath = UARTSystemPath(device->deviceName);
    device->portHandle = HSDKOpenFile(systemPath);
    free(systemPath);
#elif __linux__ || __APPLE__
    device->portHandle = HSDKOpenFile(device->deviceName);
#endif

    if (!HSDKIsDescriptorValid(device->portHandle)) {
        logMessage(HSDK_ERROR, "[UARTDevice]UARTOpenPort", "Failed to open port", HSDKThreadId());
        return HSDK_ERROR_INVALID;
    }

    UARTConfigurationData *pConfig = NULL;
    if (configData == NULL) {
        pConfig = defaultConfigurationData();
        freeConfig = 1;
    } else {
        pConfig = (UARTConfigurationData *)configData;
    }

    int ret = InitPort(device->portHandle, pConfig);
    if (ret < 0) {
        logMessage(HSDK_ERROR, "[UARTDevice]UARTOpenPort", "Failed to initialize port to the desired config", HSDKThreadId());
        rc = HSDK_ERROR_INVALID;
    }

    if (freeConfig) {
        freeConfigurationData(pConfig);
    }


#ifdef DEBUG
    printf("Device %s\n", device->deviceName);
#endif

    return rc;
}

/*! *********************************************************************************
* \brief  Close the opened port device but do no free the memory. Also closes the thread.
*
* \param[in] device pointer to the UART device
*
* \return 0 for success, -1 for failure
********************************************************************************** */
static int UARTClosePort(void *device)
{
    UARTHandle *crtDevice = (UARTHandle *)device;
    if (crtDevice == NULL) {
        logMessage(HSDK_ERROR, "[UARTDevice]UARTClosePort", "Trying to close on a NULL reference", HSDKThreadId());
        return HSDK_ERROR_INVALID;
    }


    int ret = HSDKCloseFile(crtDevice->portHandle);
    if (ret != HSDK_ERROR_SUCCESS) {
        logMessage(HSDK_WARNING, "[UARTDevice]UARTClosePort", "Trying to close an already closed port", HSDKThreadId());
        return HSDK_ERROR_INVALID;
    }

    HSDKInvalidateDescriptor(&crtDevice->portHandle);
    return HSDK_ERROR_SUCCESS;
}

/*! *********************************************************************************
* \brief  Write data to the UART device.
*
* \param[in] specificData   a pointer to the UART device
* \param[in] buffer         a byte array containing the data to be sent
* \param[in] count          number of bytes to be written
*
* \return a positive integer for success, -1 for failure
********************************************************************************** */
static int UARTWrite(void *specificData, uint8_t *buffer, uint32_t count)
{
    UARTHandle *device = (UARTHandle *)specificData;

    int err = HSDKWriteFile(device->portHandle, buffer, count);

    if (err == -1) {
        logMessage(HSDK_WARNING, "[UARTDevice]UARTWrite", "Error writing data to port", HSDKThreadId());
    }
    return err;
}

/*! *********************************************************************************
* \brief  Read data to the UART device.
*
* \param[in] specificData   a pointer to the UART device
* \param[in,out] buffer     a byte array where the data shall be read into
* \param[in,out] count      number of bytes successfully read
*
* \return a positive integer for success, -1 for failure
********************************************************************************** */
static int UARTRead(void *specificData, uint8_t *buffer, uint32_t *count)
{
    UARTHandle *device = (UARTHandle *)specificData;

    int err = HSDKReadFile(device->portHandle, buffer, count);

    if (err != HSDK_ERROR_SUCCESS) {
        logMessage(HSDK_WARNING, "[UARTDevice]UARTRead", "Error reading data from port", HSDKThreadId());
    }
    return err;
}

/*! *********************************************************************************
* \brief  Wrapper over UARTOpen.
*
* \param[in] specificData   pointer to a UART handle
* \param[in] configData     configuration data to be used in configuring the UART port
*
* \return 0
********************************************************************************** */
static int UARTConfigure(void *specificData, void *configData)
{
    UARTHandle *device = (UARTHandle *)specificData;

    int rc = UARTClosePort(device);
    if (rc == HSDK_ERROR_SUCCESS) {
        return UARTOpenPort(device, configData);
    }

    return rc;
}
