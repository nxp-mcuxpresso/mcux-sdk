/*
 * \file SPIDevice.c
 * This is a source file for the SPIDevice module.
 *
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <poll.h>

#include "PhysicalDevice.h"
#include "SPIDevice.h"
#include "SPIConfiguration.h"

#include "hsdkError.h"
#include "hsdkLogger.h"


/************************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
************************************************************************************/
static SPIHandle *InitSPIDevice(char *);
static int DestroySPIDevice(SPIHandle *);
static int InitDeviceAsSPI(PhysicalDevice *device);
static int SPIOpenPort(void *pDevice, void *configData);
static int SPIClosePort(void *pDevice);
static int SPIWrite(void *specificData, uint8_t *buf, uint32_t size);
static int SPIReadFSCIData(SPIHandle *device, uint8_t *buffer, uint32_t *count);
static int SPIRead(void *specificData, uint8_t *buf, uint32_t *size);
static int SPIInitialize(void *specificData, uint8_t clearBus);
static int SPIConfigure(void *specificData, void *configData);
static Event SPIGetWaitEvent(void *, void **);

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
#if DK07_HOST
    static int csfd;
#endif

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

int AttachToSPIDevice(PhysicalDevice *pDevice, char *deviceName)
{
    pDevice->deviceHandle = InitSPIDevice(deviceName);

    if (!pDevice->deviceHandle) {
        return HSDK_ERROR_ALLOC;
    }

    return InitDeviceAsSPI(pDevice);
}

int DetachFromSPIDevice(PhysicalDevice *pDevice)
{
    int rc = DestroySPIDevice((SPIHandle *)pDevice->deviceHandle);

    if (rc != HSDK_ERROR_SUCCESS) {
        return rc;
    }

    pDevice->deviceHandle = NULL;
    pDevice->open = NULL;
    pDevice->close = NULL;
    pDevice->read = NULL;
    pDevice->initialize = NULL;
    pDevice->write = NULL;
    pDevice->configure = NULL;

    return HSDK_ERROR_SUCCESS;
}

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

int InitDeviceAsSPI(PhysicalDevice *device)
{
    device->open = SPIOpenPort;
    device->close = SPIClosePort;
    device->read = SPIRead;
    device->initialize = SPIInitialize;
    device->write = SPIWrite;
    device->configure = SPIConfigure;
    device->waitable = SPIGetWaitEvent;

    return HSDK_ERROR_SUCCESS;
}


/*! *********************************************************************************
* \brief  Initializes an SPI device.
*
* \param[in] deviceName the name of the port for which the device is to be initialized
*
* \return a pointer to an SPIHandle
********************************************************************************** */
SPIHandle *InitSPIDevice(char *deviceName)
{
    if ((deviceName == NULL) || (strlen(deviceName) == 0)) {
        logMessage(HSDK_ERROR, "[SPIDevice]InitSPIDevice", "Device name is null or empty", HSDKThreadId());
        return NULL;
    }

    SPIHandle *device = (SPIHandle *)calloc(1, sizeof(SPIHandle));

    if (!device) {
        logMessage(HSDK_ERROR, "[SPIDevice]InitSPIDevice", "Memory allocation failed", HSDKThreadId());
        return NULL;
    }

    device->deviceName = strdup(deviceName);
    HSDKInvalidateDescriptor(&device->portHandle);

    return device;
}

/*! *********************************************************************************
* \brief  Free the space allocated for the SPI device as well as the events
*
* \param[in] device pointer to the SPIHandle structure
*
* \return 0 for success, -1 for failure
********************************************************************************** */
int DestroySPIDevice(SPIHandle *device)
{
    if (!device) {
        logMessage(HSDK_ERROR, "[SPIDevice]DestroySPIDevice", "Argument is null", HSDKThreadId());
        return HSDK_ERROR_INVALID;
    }

    if (HSDKIsDescriptorValid(device->portHandle)) {
        int rc = SPIClosePort(device);

        if (rc != HSDK_ERROR_SUCCESS) {
            return rc;
        }
    }

    free(device->deviceName);
    device->deviceName = NULL;
    free(device);

    return HSDK_ERROR_SUCCESS;
}


static Event SPIGetWaitEvent(void *device, void **asyncMask)
{
    SPIHandle *pDevice = (SPIHandle *)device;
    Event evt = HSDKDeviceTriggerableEvent(pDevice->uioPortHandle, asyncMask);
#if DK07_HOST
    evt->gpioPollEvent = 1;
#endif

    return evt;
}


/*! *********************************************************************************
* \brief  Opens the specified port and creates the thread
*
* \param[in] pDevice    pointer to a SPI handle
* \param[in] configData configuration data to be used in configuring the SPI port
*
* \return 0 for success, -1 for failure
********************************************************************************** */
static int SPIOpenPort(void *pDevice, void *configData)
{
    int freeConfig = 0;
    SPIHandle *device = (SPIHandle *)pDevice;

    /* /dev/spidev-bus.device */
    device->portHandle = HSDKOpenFile(device->deviceName);

    if (!HSDKIsDescriptorValid(device->portHandle)) {
        logMessage(HSDK_ERROR, "[SPIDevice]SPIOpenPort", "Failed to open SPI port", HSDKThreadId());
        return HSDK_ERROR_INVALID;
    }

    /* data available pin: GPIO or UIO */
#if DK07_HOST
    device->uioPortHandle = open(SPI_DAP_DEV, O_RDONLY);
#elif IMX6ULEVK_HOST
    device->uioPortHandle = HSDKOpenFile(SPI_DAP_DEV);
#endif

    if (!HSDKIsDescriptorValid(device->uioPortHandle)) {
        logMessage(HSDK_ERROR, "[SPIDevice]SPIOpenPort", "Failed to open UIO port", HSDKThreadId());
        return HSDK_ERROR_INVALID;
    }

    SPIConfigurationData *pConfig = NULL;

    if (configData == NULL) {
        pConfig = defaultSettingsSPI();
        freeConfig = 1;
    } else {
        pConfig = (SPIConfigurationData *)configData;
    }

    device->lengthFieldSize = pConfig->lengthFieldSize;
    int rc = initPortSPI(device->portHandle, pConfig);

    if (rc < 0) {
        logMessage(HSDK_ERROR, "[SPIDevice]SPIOpenPort", "Failed to initialize port to the desired config", HSDKThreadId());
        return HSDK_ERROR_INVALID;
    }

    if (freeConfig) {
        freeSettingsSPI(pConfig);
        pConfig = NULL;
    }

#ifdef DEBUG
    printf("Opened and configured SPI device %s\n", device->deviceName);
#endif

    return HSDK_ERROR_SUCCESS;
}

/*! *********************************************************************************
* \brief  Close the opened port but do not free the memory.
*
* \param[in] device pointer to the SPI device
*
* \return 0 for success, -1 for failure
********************************************************************************** */
static int SPIClosePort(void *device)
{
    SPIHandle *crtDevice = (SPIHandle *)device;

    if (crtDevice == NULL) {
        logMessage(HSDK_ERROR, "[SPIDevice]SPIClosePort", "Trying to close on a NULL reference", HSDKThreadId());
        return HSDK_ERROR_INVALID;
    }

    int rc = HSDKCloseFile(crtDevice->portHandle);

    if (rc != HSDK_ERROR_SUCCESS) {
        logMessage(HSDK_WARNING, "[SPIDevice]SPIClosePort", "Trying to close an already closed port", HSDKThreadId());
        return HSDK_ERROR_INVALID;
    }

    HSDKInvalidateDescriptor(&crtDevice->portHandle);
    return HSDK_ERROR_SUCCESS;
}

/*! *********************************************************************************
* \brief  Write data to the SPI device.
*
* \param[in] specificData   a pointer to the SPI device
* \param[in] buffer         a byte array containing the data to be sent
* \param[in] count          number of bytes to be written
*
* \return a positive integer for success, -1 for failure
********************************************************************************** */
static int SPIWrite(void *specificData, uint8_t *buffer, uint32_t count)
{
    int rc;
    SPIHandle *device = (SPIHandle *)specificData;

#if DK07_HOST
    rc  = write(csfd, "0", 1);

    if (rc == -1) {
        perror("[SPIWrite] write CS with 0 fail");
        exit(1);
    }

#endif

    rc = HSDKWriteFile(device->portHandle, buffer, count);

    if (rc <= 0) {
        logMessage(HSDK_WARNING, "[SPIDevice]SPIWrite", "Error writing data to port", HSDKThreadId());
    }

#if DK07_HOST
    rc  = write(csfd, "1", 1);

    if (rc == -1) {
        perror("[SPIWrite] write CS with 1 fail");
        exit(1);
    }

#endif

    return rc;
}

/*! *********************************************************************************
* \brief  A simple framer implemented at the SPI physical layer.
*
* \param[in]     device     a pointer to the SPI device
* \param[in,out] buffer     a byte array where the data shall be read into
* \param[in,out] count      number of bytes successfully read
*
* \return a positive integer for success, -1 for failure
********************************************************************************** */
static int SPIReadFSCIData(SPIHandle *device, uint8_t *buffer, uint32_t *count)
{
    int rc = 0;
    uint32_t fsci_header_len = 3 + device->lengthFieldSize;
    uint32_t fsci_payload_len = 0, sync_len = 1, curr_len = fsci_header_len;
    uint8_t fsci_header[fsci_header_len], no_more_data[fsci_header_len], *curr = fsci_header;
    uint8_t check_sync = 1, errored = 0, ffCtr = 0;

    /* Stop condition is all FFs. */
    memset(no_more_data, 0xFF, fsci_header_len);

    /* Do something in response to the interrupt:
         *      1st read FSCI header (SYNC(1) + OG(1) + OC(1) + LEN(1|2) = 4|5 bytes)
         *      2nd read payload + CRC(1)
         *      3rd repeat until only FFs                                          */
    while (1) {

        /* Read sync byte, allow several 0xFF skips. */
        if (check_sync) {

            if (ffCtr == fsci_header_len) {
                check_sync = 0;
                ffCtr = 0;
            }

            HSDKReadFile(device->portHandle, fsci_header, &sync_len);

            if (fsci_header[0] != 0x02) {
                ffCtr++;
                continue;
            } else {
                curr = fsci_header + 1;
                curr_len = fsci_header_len - 1;
            }
        } else {
            curr = fsci_header;
            curr_len = fsci_header_len;
        }

        /* Read header, expect FSCI synchronization byte 0x02 on first position. */
        rc = HSDKReadFile(device->portHandle, curr, &curr_len);

        if (rc != HSDK_ERROR_SUCCESS) {
            logMessage(HSDK_WARNING, "[SPIDevice]SPIRead", "Error reading FSCI header from port", HSDKThreadId());
            break;
        } else {
            if (fsci_header[0] == 0x02 && !errored) {
                memcpy(buffer + *count, fsci_header, fsci_header_len);
                *count += fsci_header_len;
            } else if (memcmp(fsci_header, no_more_data, fsci_header_len) == 0) {
                if (errored) {
                    rc = HSDK_ERROR_INVALID;
                }

                break;
            } else {
                logMessage(HSDK_WARNING, "[SPIDevice]SPIRead", "Unexpected bytes - frame dismissed", HSDKThreadId());
                errored = 1;
                continue;  // continue until all useful bytes are read
            }
        }

        if (fsci_header_len == 4) {
            fsci_payload_len = buffer[*count - 1] + 1;  // +1 for CRC
        } else {
            fsci_payload_len = buffer[*count - 2] + (buffer[*count - 1] << 8) + 1;  // +1 for CRC
        }

        rc = HSDKReadFile(device->portHandle, buffer + *count, &fsci_payload_len);

        if (rc != HSDK_ERROR_SUCCESS) {
            logMessage(HSDK_WARNING, "[SPIDevice]SPIRead", "Error reading FSCI payload from port", HSDKThreadId());
            break;
        }

        *count += fsci_payload_len;

        /* Check again sync for next packet. */
        check_sync = 1;
    }

    return rc;
}


/*! *********************************************************************************
* \brief  Read data from the SPI device.
*
* \param[in] specificData   a pointer to the SPI device
* \param[in,out] buffer     a byte array where the data shall be read into
* \param[in,out] count      number of bytes successfully read
*
* \return a positive integer for success, -1 for failure
********************************************************************************** */
static int SPIRead(void *specificData, uint8_t *buffer, uint32_t *count)
{
    SPIHandle *device = (SPIHandle *)specificData;

    int rc = 0;
    uint32_t temp;
    ssize_t nb;

    *count = 0;

    /* Read the interrupt. */
    nb = read(device->uioPortHandle, &temp, sizeof(temp));

    if (nb == -1) {
        perror("[SPIRead] read the interrupt");
        exit(1);
    } else if (nb == 0) {
        printf("[SPIRead] read 0 bytes\n");
        return HSDK_ERROR_INVALID;
    }

#if DK07_HOST
    ssize_t csfdrc  = write(csfd, "0", 1);

    if (csfdrc == -1) {
        perror("write CS fail");
        exit(1);
    }

#endif

    /* Process available data. */
    rc = SPIReadFSCIData(device, buffer, count);

#if DK07_HOST
    csfdrc  = write(csfd, "1", 1);

    if (csfdrc == -1) {
        perror("write CS fail");
        exit(1);
    }

#elif IMX6ULEVK_HOST
    uint32_t info = 1;
    /* Unmask the interrupt. */
    nb = write(device->uioPortHandle, &info, sizeof(info));

    if (nb < sizeof(info)) {
        perror("write");
        close(device->uioPortHandle);
        exit(1);
    }

#endif

    return rc;
}

/*! *********************************************************************************
* \brief  Read data from the SPI device, before starting the device loop.
*
* \param[in] specificData   a pointer to the SPI device
* \param[in] clearBus       whether or not to read the data available on the bus
*
* \return a positive integer for success, -1 for failure
********************************************************************************** */
static int SPIInitialize(void *specificData, uint8_t clearBus)
{
    SPIHandle *device = (SPIHandle *)specificData;
    ssize_t nb;

#if DK07_HOST
    uint32_t temp;

    if (lseek(device->uioPortHandle, 0, SEEK_SET) == -1) {
        perror("lseek");
    }

    /* Read the interrupt. */
    nb = read(device->uioPortHandle, &temp, sizeof(temp));

    if (nb == -1) {
        perror("[SPIInitialize] read the interrupt");
        exit(1);
    } else if (nb == 0) {
        printf("[SPIInitialize] read 0 bytes\n");
        return HSDK_ERROR_INVALID;
    }

    csfd = open(SPI_CS_DEV, O_WRONLY);

    if (csfd == -1) {
        perror("open CS fail");
        exit(1);
    }

    int rc = write(csfd, "0", 1);

    if (rc == -1) {
        perror("[SPIInitialize] write CS with 0 fail");
        exit(1);
    }

#endif

    if (clearBus) {
        uint32_t RX_SIZE = 0x1000;
        uint8_t *buffer = malloc(RX_SIZE);

        if (buffer) {
            RX_SIZE = 0;
            SPIReadFSCIData(device, buffer, &RX_SIZE);
            free(buffer);
        }
    }

#if DK07_HOST
    rc  = write(csfd, "1", 1);

    if (rc == -1) {
        perror("[SPIInitialize] write CS with 1 fail");
        exit(1);
    }

#elif IMX6ULEVK_HOST
    uint32_t info = 1;
    /* Unmask the interrupt. */
    nb = write(device->uioPortHandle, &info, sizeof(info));

    if (nb < sizeof(info)) {
        perror("write");
        close(device->uioPortHandle);
        exit(1);
    }

#endif

    return HSDK_ERROR_SUCCESS;
}

/*! *********************************************************************************
* \brief  Wrapper over SPIOpen.
*
* \param[in] specificData   pointer to a SPI handle
* \param[in] configData     configuration data to be used in configuring the SPI port
*
* \return 0
********************************************************************************** */
static int SPIConfigure(void *specificData, void *configData)
{
    SPIHandle *device = (SPIHandle *)specificData;

    int rc = SPIClosePort(device);

    if (rc == HSDK_ERROR_SUCCESS) {
        return SPIOpenPort(device, configData);
    }

    return rc;
}
