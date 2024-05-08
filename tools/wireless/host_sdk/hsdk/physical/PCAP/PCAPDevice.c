/*
 * \file PCAPDevice.c
 * This is a source file for the PCAPDevice module.
 *
 * Copyright 2015 Freescale Semiconductor, Inc.
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
#include <stdlib.h>
#include <string.h>

#include "PhysicalDevice.h"
#include "PCAPDevice.h"
#include "RawFrame.h"

#include "hsdkError.h"
#include "hsdkLogger.h"

/* Necessary headers for ioctl on MAC address. */
#ifdef __linux__
#   include <sys/ioctl.h>
#   include <sys/types.h>
#   include <sys/socket.h>
#   include <unistd.h>
#   include <net/if.h>
#endif

/************************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
************************************************************************************/
#define PCAP_DEBUG 0

#define SIZE_ETHERNET 14
#define SIZE_MACADDR 6
#define FSCI_ETHERTYPE 0x88B5

/************************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
************************************************************************************/
static PCAPHandle *InitPCAPDevice(char *);
static int DestroyPCAPDevice(PCAPHandle *);
static void InitDeviceAsPCAP(PhysicalDevice *);
static void PCAPCallback(u_char *, const struct pcap_pkthdr *, const u_char *);
static int PCAPOpenPort(void *, void *);
static int PCAPClosePort(void *);
static int PCAPWrite(void *pDevice, uint8_t *buffer, uint32_t count);
static Event PCAPGetWaitEvent(void *, void **);
static void FillEthernetHeader(char *);

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
static uint8_t ether_header[SIZE_ETHERNET] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0xB5};

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/
int AttachToPCAPDevice(PhysicalDevice *pDevice, char *ifName)
{
    pDevice->deviceHandle = InitPCAPDevice(ifName);
    if (pDevice->deviceHandle == NULL) {
        return -1;
    }

    InitDeviceAsPCAP(pDevice);

    /* Set the current PhysicalDevice as the parent for our handle. */
    ((PCAPHandle *)(pDevice->deviceHandle))->parent = pDevice;

    return 0;
}

int DetachFromPCAPDevice(PhysicalDevice *pDevice)
{
    int rc = DestroyPCAPDevice((PCAPHandle *)(pDevice->deviceHandle));
    if (rc != 0) {
        return rc;
    }

    pDevice->deviceHandle = NULL;
    pDevice->open = NULL;
    pDevice->close = NULL;
    pDevice->read = NULL;
    pDevice->write = NULL;
    pDevice->waitable = NULL;

    return 0;
}

void *PCAPLoopThreadRoutine(void *pDevice)
{
    int rc = 0;
    PhysicalDevice *device = (PhysicalDevice *) pDevice;
    PCAPHandle *handle = (PCAPHandle *)(device->deviceHandle);

    /* int pcap_loop(pcap_t *p, int cnt, pcap_handler callback, u_char *user); */
    rc = pcap_loop(handle->ifHandle, -1, PCAPCallback, (u_char *)device);
    if (rc == -1) {
        logMessage(HSDK_WARNING, "[PCAPDevice]PCAPLoopThreadRoutine pcap_loop", pcap_geterr(handle->ifHandle), HSDKThreadId());
    }

    return NULL;
}

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/
void InitDeviceAsPCAP(PhysicalDevice *device)
{
    device->open = PCAPOpenPort;
    device->close = PCAPClosePort;
    device->read = NULL;  //not used
    device->write = PCAPWrite;
    device->configure = NULL; // not used
    device->waitable = PCAPGetWaitEvent;
}

/*! *********************************************************************************
* \brief  Initializes an PCAP device.
*
* \param[in] ifName - the name of the interface for which the device is to be
* initialized, e.g. eth2.
*
* \return a pointer to an PCAPHandle
********************************************************************************** */
PCAPHandle *InitPCAPDevice(char *ifName)
{
    if (ifName == NULL || strlen(ifName) == 0) {
        logMessage(HSDK_ERROR, "[PCAPDevice]InitPCAPDevice", "Interface name is null or empty", HSDKThreadId());
        return NULL;
    }

    PCAPHandle *device = (PCAPHandle *) calloc(1, sizeof(PCAPHandle));
    if (device == NULL) {
        logMessage(HSDK_ERROR, "[PCAPDevice]InitPCAPDevice", "Memory allocation failed", HSDKThreadId());
        return NULL;
    }

    device->ifName = strdup(ifName);

    return device;
}

/*! *********************************************************************************
* \brief  Free the space allocated for the PCAP device as well as the events.
*
* \param[in] device pointer to the PCAP handle.
*
* \return 0 for success, -1 for failure
********************************************************************************** */
int DestroyPCAPDevice(PCAPHandle *device)
{
    if (device == NULL) {
        logMessage(HSDK_ERROR, "[PCAPDevice]DestroyPCAPDevice", "Argument is null", HSDKThreadId());
        return -1;
    }

    if (device->ifHandle != NULL) {
        pcap_close(device->ifHandle);
    }

    free(device->ifName);
    device->ifName = NULL;
    /* Not our job to free our parent. */
    device->parent = NULL;
    free(device);

    return 0;
}


void PCAPCallback(u_char *userData, const struct pcap_pkthdr *h, const u_char *bytes)
{
#if PCAP_DEBUG
    printf("[%ld.%06ld] caplen %d, len %d\n", h->ts.tv_sec, h->ts.tv_usec, h->caplen, h->len);
#endif
    /* Strip Ethernet header */
    RawFrame *frame = CreateRxRawFrame(((uint8_t *)bytes) + SIZE_ETHERNET, h->caplen - SIZE_ETHERNET);
    if (frame == NULL) {
        logMessage(HSDK_ERROR, "[PCAPDevice]PCAPCallback", "Memory allocation failed", HSDKThreadId());
    }
    /* Notify */
    NotifyOnSameEvent(((PhysicalDevice *)userData)->evtManager, frame, (void *(*)(void *))CloneRawFrame);
    /* Destroy */
    DestroyRawFrame(frame);
}

/*! *********************************************************************************
* \brief  Opens the specified port and creates the thread
*
* \param[in] pDevice    pointer to an PCAP handle
* \param[in] configData configuration data, NULL for PCAP
*
* \return 0 for success, -1 for failure
********************************************************************************** */
int PCAPOpenPort(void *pDevice, void *configData)
{
    PCAPHandle *device = (PCAPHandle *) pDevice;
    char errbuf[PCAP_ERRBUF_SIZE];                  /* Error string */
    struct bpf_program fp;                          /* The compiled filter */
    char filter_exp[] = "ether proto 0x88B5";       /* The filter expression */

    /* Open the session in non-promiscuous mode. */
    device->ifHandle = pcap_open_live(device->ifName, BUFSIZ, 0, 100, errbuf);

    if (device->ifHandle == NULL) {
        fprintf(stderr, "Couldn't open device %s\n", errbuf);
        logMessage(HSDK_ERROR, "[PCAPDevice]PCAPOpenPort", errbuf, HSDKThreadId());
        return HSDK_ERROR_INVALID;
    }

    /* Compile and apply the filter */
    if (pcap_compile(device->ifHandle, &fp, filter_exp, 0, PCAP_NETMASK_UNKNOWN) == -1) {
        fprintf(stderr, "Couldn't parse filter %s: %s\n", filter_exp, pcap_geterr(device->ifHandle));
        logMessage(HSDK_ERROR, "[PCAPDevice]PCAPOpenPort", pcap_geterr(device->ifHandle), HSDKThreadId());
        return HSDK_ERROR_INVALID;
    }
    if (pcap_setfilter(device->ifHandle, &fp) == -1) {
        fprintf(stderr, "Couldn't install filter %s: %s\n", filter_exp, pcap_geterr(device->ifHandle));
        logMessage(HSDK_ERROR, "[PCAPDevice]PCAPOpenPort", pcap_geterr(device->ifHandle), HSDKThreadId());
        return HSDK_ERROR_INVALID;
    }

    /* Fill the global Ethernet header. */
    FillEthernetHeader(device->ifName);

    return HSDK_ERROR_SUCCESS;
}

/*! *********************************************************************************
* \brief  Close the opened port device but do no free the memory.
*
* \param[in] device pointer to the PCAP device
*
* \return 0 for success, -1 for failure
********************************************************************************** */
int PCAPClosePort(void *device)
{
    PCAPHandle *crtDevice = (PCAPHandle *) device;
    if (crtDevice == NULL) {
        logMessage(HSDK_ERROR, "[PCAPDevice]PCAPClosePort", "Trying to close on a NULL reference", HSDKThreadId());
        return HSDK_ERROR_INVALID;
    }

    pcap_close(crtDevice->ifHandle);

    return HSDK_ERROR_SUCCESS;
}

#if PCAP_DEBUG
void hex_dump(char *desc, uint8_t *data, int size)
{
    int i;
    uint8_t ascii_repr[17];

    if (desc != NULL)
        printf("%s:\n", desc);

    for (i = 0; i < size; i++) {
        if ((i % 16) == 0) {
            if (i != 0)
                printf("  %s\n", ascii_repr);

            printf("  %04x ", i);
        }

        printf(" %02x", data[i]);

        if ((data[i] < 0x20) || (data[i] > 0x7e))
            ascii_repr[i % 16] = '.';
        else
            ascii_repr[i % 16] = data[i];
        ascii_repr[(i % 16) + 1] = '\0';
    }

    while ((i % 16) != 0) {
        printf("   ");
        i++;
    }

    printf("  %s\n", ascii_repr);
}
#endif

/*! *********************************************************************************
* \brief  Write data to the PCAP device.
*
* \param[in] pDevice        a pointer to the PCAP device
* \param[in] buffer         a byte array containing the data to be sent
* \param[in] count          number of bytes to be written
*
* \return a positive integer for success, -1 for failure
********************************************************************************** */
int PCAPWrite(void *pDevice, uint8_t *buffer, uint32_t count)
{
    PCAPHandle *device = (PCAPHandle *) pDevice;

    /* Add Ethernet header */
    uint8_t finalBuf[SIZE_ETHERNET + count];
    memcpy(finalBuf, ether_header, SIZE_ETHERNET);
    memcpy(finalBuf + SIZE_ETHERNET, buffer, count);

    int rc = pcap_inject(device->ifHandle, finalBuf, SIZE_ETHERNET + count);
#if PCAP_DEBUG
    hex_dump("TX", finalBuf, SIZE_ETHERNET + count);
#endif
    if (rc == -1) {
        logMessage(HSDK_WARNING, "[PCAPDevice]PCAPWrite pcap_inject failed", pcap_geterr(device->ifHandle), HSDKThreadId());
        /* Usually the cause is: usb usb10-port1: disabled by hub (EMI?), re-enabling...
           Restart the live capture here. */
        PCAPClosePort(device);
        sleep(2);
        PCAPOpenPort(device, NULL);
        sleep(2);
        /* Re-establish RX path. */
        Thread rxThread = HSDKCreateThread(PCAPLoopThreadRoutine, device->parent);
        if (rxThread == INVALID_THREAD_HANDLE) {
            logMessage(HSDK_ERROR, "[PCAPWrite]HSDKCreateThread", "rxThread creation failed", HSDKThreadId());
            return HSDK_ERROR_INVALID;
        }
    }

    return HSDK_ERROR_SUCCESS;
}

Event PCAPGetWaitEvent(void *device, void **asyncMask)
{
    return NULL;
}


void FillEthernetHeader(char *ifName)
{
#ifdef __linux__
    int s, rc;
    struct ifreq buffer;

    if (ifName == NULL) {
        logMessage(HSDK_ERROR, "[FillEthernetHeader] ifName", "interface name cannot be NULL", HSDKThreadId());
        return;
    }

    s = socket(PF_INET, SOCK_DGRAM, 0);
    if (s == -1) {
        perror("FillEthernetHeader socket");
        logMessage(HSDK_ERROR, "[FillEthernetHeader] socket", strerror(errno), HSDKThreadId());
        return;
    }

    /* Get HW Address in buffer. */
    memset(&buffer, 0x00, sizeof(buffer));
    strncpy(buffer.ifr_name, ifName, IFNAMSIZ - 1);
    buffer.ifr_name[IFNAMSIZ - 1] = '\0';
    ioctl(s, SIOCGIFHWADDR, &buffer);

    rc = close(s);
    if (rc == -1) {
        perror("FillEthernetHeader close socket");
        logMessage(HSDK_ERROR, "[FillEthernetHeader] close socket", strerror(errno), HSDKThreadId());
    }

    /* Fill destination MAC address. */
    memcpy(ether_header, buffer.ifr_hwaddr.sa_data, SIZE_MACADDR);
    ether_header[3] = buffer.ifr_hwaddr.sa_data[5];
    ether_header[4] = buffer.ifr_hwaddr.sa_data[4];
    ether_header[5] = buffer.ifr_hwaddr.sa_data[3];

    /* Fill source MAC address. */
    memcpy(ether_header + SIZE_MACADDR, buffer.ifr_hwaddr.sa_data, SIZE_MACADDR);
#endif
}
