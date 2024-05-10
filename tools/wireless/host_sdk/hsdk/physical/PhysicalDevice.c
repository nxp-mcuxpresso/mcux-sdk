/*
 * \file PhysicalDevice.c
 * This is a source file that implements the generic device layer.
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __linux__
#    include <unistd.h>
#endif

#include "EventManager.h"
#include "Framer.h"
#include "PhysicalDevice.h"
#include "RawFrame.h"

#ifdef _USE_BT
#    include "BTDevice.h"
#endif

#ifdef __linux__pcap__
#    include "PCAPDevice.h"
#endif

#ifdef __linux__spi__
#   include "SPIDevice.h"
#endif

#include "UARTDevice.h"
#include "UART/UARTConfiguration.h"

#include "hsdkError.h"
#include "hsdkLogger.h"

/************************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
************************************************************************************/
#define RX_SIZE 0x8FF

/************************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
************************************************************************************/
static void *DeviceThreadRoutine(void *lpParameter);
static int AttachToConcreteImplementation(PhysicalDevice *device, char *deviceName);
static int DetachFromConcreteImplementation(PhysicalDevice *device);

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
static uint8_t LENGTH_FIELD_SIZE = 2;  // needed for ACKs
static uint8_t spiClearBus = 1;
static RawFrame* lastTx; // frame that will keep the last send frame
                     //so it can be resent in case of no ACK received 
static Event stopThreadWaitACK; // event to signal wait ACK thread stop


/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/


/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
* \brief    This is the initialized for a connectivity device. It creates a device
*           device corresponding to the type specified.
*
* \param[in] type           identifier for the device
* \param[in] pConfigData    pointer to a structure containing configuration data
* \param[in] deviceName     a string containing the name to identify the device;
                            it is essentially the character device created by the OS
* \param[in] ackPolicy      an integer specifying the policy for FSCI ACK
                            synchronization (none, TX, RX, both, global)
*
* \return None.
********************************************************************************** */
PhysicalDevice *InitPhysicalDevice(DeviceType type, void *pConfigData, char *deviceName, FsciAckPolicy policy)
{
    // Initialize the logger if not created, else do nothing
    initLogger(NULL);

    // Allocate the structure for a physical device
    PhysicalDevice *pConnDev = (PhysicalDevice *) calloc(1, sizeof(PhysicalDevice));
    if (pConnDev == NULL) {
        logMessage(HSDK_ERROR, "[PhysicalDevice]InitPhysicalDevice", "Allocate memory for PhysicalDevice failed", HSDKThreadId());
        return NULL;
    }

    logMessage(HSDK_INFO, "[PhysicalDevice]InitPhysicalDevice", "Allocated memory for PhysicalDevice", HSDKThreadId());

    // Set the configuration data for a physical device
    pConnDev->configurationData = pConfigData;

    // Set the configuration parameters for a physical device
    pConnDev->configParams = ParseConfig();
    if (policy != GLOBAL) {
        pConnDev->configParams->fsciTxAck = policy & TX;
        pConnDev->configParams->fsciRxAck = policy & RX;
    }

    // Initialize the message queue for the current device
    pConnDev->inMessages = InitializeMessageQueue(INT32_MAX);
    if (pConnDev->inMessages == NULL) {
        logMessage(HSDK_ERROR, "[PhysicalDevice]InitPhysicalDevice", "MessageQueue init failed", HSDKThreadId());
        free(pConnDev);
        return NULL;
    }

    logMessage(HSDK_INFO, "[PhysicalDevice]InitPhysicalDevice", "Initialized device's message queue", HSDKThreadId());

    // Create the event manager, responsible for calling the callbacks of the subscribed thread
    pConnDev->evtManager = CreateEventManager();
    if (pConnDev->evtManager == NULL) {
        logMessage(HSDK_ERROR, "[PhysicalDevice]InitPhysicalDevice", "EventManager creation failed", HSDKThreadId());
        free(pConnDev);
        return NULL;
    }

    logMessage(HSDK_INFO, "[PhysicalDevice]InitPhysicalDevice", "Created event manager for device", HSDKThreadId());

    pConnDev->status = PHYS_CLOSED;

    // Create the event startThread. It holds the thread from entering the loop until the port is configured or else
    // the thread will block waiting for an event that will never happen.
    pConnDev->startThread = HSDKCreateEvent(0);
    if (pConnDev->startThread == INVALID_EVENT_HANDLE) {
        logMessage(HSDK_ERROR, "[PhysicalDevice]InitPhysicalDevice", "Event startThread creation failed", HSDKThreadId());
        free(pConnDev);
        return NULL;
    }

    logMessage(HSDK_INFO, "[PhysicalDevice]InitPhysicalDevice", "Created startThread event", HSDKThreadId());

    // Create the event stopThread. It signals the thread to exit the loop.
    pConnDev->stopThread = HSDKCreateEvent(0);
    if (pConnDev->stopThread == INVALID_EVENT_HANDLE) {
        logMessage(HSDK_ERROR, "[PhysicalDevice]InitPhysicalDevice", "Event stopThread creation failed", HSDKThreadId());
        free(pConnDev);
        return NULL;
    }

    logMessage(HSDK_INFO, "[PhysicalDevice]InitPhysicalDevice", "Created stopThread event", HSDKThreadId());

    // Create the event sAnnounceTXACK. It signals that the TX ACK has been received.
    pConnDev->sAnnounceTXACK = HSDKCreateEvent(0);
    if (pConnDev->sAnnounceTXACK == INVALID_EVENT_HANDLE) {
        logMessage(HSDK_ERROR, "[PhysicalDevice]InitPhysicalDevice", "Event sAnnounceTXACK creation failed", HSDKThreadId());
        free(pConnDev);
        return NULL;
    }

    logMessage(HSDK_INFO, "[PhysicalDevice]InitPhysicalDevice", "Created sAnnounceTXACK event", HSDKThreadId());

    // Create the event sAnnounceTXACK. It signals that the TX ACK has been received.
    pConnDev->startTXACKTimeoutThread = HSDKCreateEvent(0);
    if (pConnDev->startTXACKTimeoutThread == INVALID_EVENT_HANDLE) {
        logMessage(HSDK_ERROR, "[PhysicalDevice]InitPhysicalDevice", "Event startTXACKTimeoutThread creation failed", HSDKThreadId());
        free(pConnDev);
        return NULL;
    }

    logMessage(HSDK_INFO, "[PhysicalDevice]InitPhysicalDevice", "Created startTXACKTimeoutThread event", HSDKThreadId());


    // Create the event sAnnounceTXACK. It signals that the TX ACK has been received.
    pConnDev->stopTXACKTimeoutThread = HSDKCreateEvent(0);
    if (pConnDev->stopTXACKTimeoutThread == INVALID_EVENT_HANDLE) {
        logMessage(HSDK_ERROR, "[PhysicalDevice]InitPhysicalDevice", "Event stopTXACKTimeoutThread creation failed", HSDKThreadId());
        free(pConnDev);
        return NULL;
    }

    logMessage(HSDK_INFO, "[PhysicalDevice]InitPhysicalDevice", "Created stopTXACKTimeoutThread event", HSDKThreadId());



    pConnDev->eventThread = INVALID_THREAD_HANDLE;
    pConnDev->type = type;

    AttachToConcreteImplementation(pConnDev, deviceName);

    logMessage(HSDK_INFO, "[PhysicalDevice]AttachToConcreteImplementation", "Attached to a concrete implementation", HSDKThreadId());

    return pConnDev;
}

/*! *********************************************************************************
* \brief   Closes the physical device if still active, detaches from the specific
*          device and deallocates the memory
*
*
* \param[in, out] device  pointer to the PhysicalDevice structure.
*
* \return None.
********************************************************************************** */
int DestroyPhysicalDevice(PhysicalDevice *device)
{
    // Check if the device exists
    if (device == NULL) {
        logMessage(HSDK_ERROR, "[PhysicalDevice]DestroyPhysicalDevice", "Physical device is NULL", HSDKThreadId());
        return HSDK_ERROR_INVALID;
    }

    int err;

    if (device->status == PHYS_OPENED) {
        err = ClosePhysicalDevice(device);
        if (err != HSDK_ERROR_SUCCESS) {
            logMessage(HSDK_ERROR, "[PhysicalDevice]DestroyPhysicalDevice", "Closing failed", HSDKThreadId());
            return err;
        }
    }

    err = HSDKDestroyEvent(device->sAnnounceTXACK);
    if (err != HSDK_ERROR_SUCCESS) {
        logMessage(HSDK_ERROR, "[PhysicalDevice]DestroyPhysicalDevice", "Error closing stopThread event", HSDKThreadId());
        return err;
    }

    err = HSDKDestroyEvent(device->startTXACKTimeoutThread);
    if (err != HSDK_ERROR_SUCCESS) {
        logMessage(HSDK_ERROR, "[PhysicalDevice]DestroyPhysicalDevice", "Error closing startTXACKTimeoutThread event", HSDKThreadId());
        return err;
    }

    err = HSDKDestroyEvent(device->stopTXACKTimeoutThread);
    if (err != HSDK_ERROR_SUCCESS) {
        logMessage(HSDK_ERROR, "[PhysicalDevice]DestroyPhysicalDevice", "Error closing stopTXACKTimeoutThread event", HSDKThreadId());
        return err;
    }

    err = HSDKDestroyEvent(device->stopThread);
    if (err != HSDK_ERROR_SUCCESS) {
        logMessage(HSDK_ERROR, "[PhysicalDevice]DestroyPhysicalDevice", "Error closing stopThread event", HSDKThreadId());
        return err;
    }

    err = HSDKDestroyEvent(device->startThread);
    if (err != HSDK_ERROR_SUCCESS) {
        logMessage(HSDK_ERROR, "[PhysicalDevice]DestroyPhysicalDevice", "Error stopping device thread", HSDKThreadId());
        return err;
    }

    err = DestroyMessageQueue(device->inMessages);
    device->inMessages = NULL;
    if (err != HSDK_ERROR_SUCCESS) {
        logMessage(HSDK_ERROR, "[PhysicalDevice]DestroyPhysicalDevice", "Error destroying message queue", HSDKThreadId());
        return err;
    }

    DestroyEventManager(device->evtManager);

    err = DetachFromConcreteImplementation(device);
    if (err != HSDK_ERROR_SUCCESS) {
        logMessage(HSDK_ERROR, "[PhysicalDevice]DestroyPhysicalDevice", "Error detaching from a concrete implementation of a physical device", HSDKThreadId());
        return err;
    }

    free(device);

    logMessage(HSDK_INFO, "[PhysicalDevice]DestroyPhysicalDevice", "Freed memory for physical device", HSDKThreadId());
    closeLogger();

    return HSDK_ERROR_SUCCESS;
}

/*! *********************************************************************************
* \brief   Open the specific device it is attached to
*
*
* \param[in, out] device  pointer to the PhysicalDevice structure.
*
* \return 0 for success, -1 for error
********************************************************************************** */
int OpenPhysicalDevice(PhysicalDevice *device)
{
    // Check if the device exists...
    if (device == NULL) {
        logMessage(HSDK_ERROR, "[PhysicalDevice]OpenPhysicalDevice", "Physical device is NULL", HSDKThreadId());
        return HSDK_ERROR_INVALID;
    }

    // and is not in the closed state.
    if (device->status != PHYS_CLOSED) {
        logMessage(HSDK_ERROR, "[PhysicalDevice]OpenPhysicalDevice", "Cannot open an opened or errored device", HSDKThreadId());
        return HSDK_ERROR_INVALID;
    }

    // Open device with the configured data. The open function also initializes the port
    int ret = device->open(device->deviceHandle, device->configurationData);
    if (ret == HSDK_ERROR_SUCCESS) {
        device->status = PHYS_OPENED;
        int sig = HSDKSignalEvent(device->startThread);
        if (sig != HSDK_ERROR_SUCCESS) {
            logMessage(HSDK_WARNING, "[PhysicalDevice]OpenPhysicalDevice", "Failed to signal thread to start", HSDKThreadId());
            device->status = PHYS_ERROR;
            return sig;
        }
    } else {
        device->status = PHYS_ERROR;
        return ret;
    }

    // Create a new thread to process data on device open not creation
    device->eventThread = HSDKCreateThread(DeviceThreadRoutine, device);
    if (device->eventThread == INVALID_THREAD_HANDLE) {
        logMessage(HSDK_ERROR, "[PhysicalDevice]OpenPhysicalDevice", "Physical device is NULL", HSDKThreadId());
        return HSDK_ERROR_INVALID;
    }

    logMessage(HSDK_INFO, "[PhysicalDevice]OpenPhysicalDevice", "Created and start device thread", HSDKThreadId());

#ifdef __linux__pcap__
    // Create a new thread which will run pcap_loop.
    if (device->type == PCAP) {
        Thread rxThread = HSDKCreateThread(PCAPLoopThreadRoutine, device);
        if (rxThread == INVALID_THREAD_HANDLE) {
            logMessage(HSDK_ERROR, "[PhysicalDevice]OpenPhysicalDevice", "rxThread creation failed", HSDKThreadId());
            return HSDK_ERROR_INVALID;
        }
    }
#endif

    return HSDK_ERROR_SUCCESS;
}

/*! *********************************************************************************
* \brief   Closes the physical device and along with it the running thread
*
*
* \param[in, out] crtDevice  pointer to the PhysicalDevice structure.
*
* \return 0 for success
********************************************************************************** */
int ClosePhysicalDevice(PhysicalDevice *crtDevice)
{
    // Check if the device exists
    if (crtDevice == NULL) {
        logMessage(HSDK_ERROR, "[PhysicalDevice]ClosePhysicalDevice", "Physical device is NULL", HSDKThreadId());
        return HSDK_ERROR_INVALID;
    }

    if (crtDevice->status != PHYS_OPENED) {
        logMessage(HSDK_ERROR, "[PhysicalDevice]ClosePhysicalDevice", "Cannot close a closed device or errored device", HSDKThreadId());
        return HSDK_ERROR_INVALID;
    }

    int err;

    if (crtDevice->stopThread == INVALID_EVENT_HANDLE) {
        logMessage(HSDK_ERROR, "[PhysicalDevice]ClosePhysicalDevice", "stopThread event is invalid", HSDKThreadId());
        return HSDK_ERROR_INVALID;
    }

    err = HSDKSignalEvent(crtDevice->stopThread);
    if (err != HSDK_ERROR_SUCCESS) {
        logMessage(HSDK_ERROR, "[PhysicalDevice]ClosePhysicalDevice", "stopThread signaling error", HSDKThreadId());
        return err;
    }

    if (crtDevice->eventThread == INVALID_THREAD_HANDLE) {
        logMessage(HSDK_ERROR, "[PhysicalDevice]ClosePhysicalDevice", "EventThread thread is invalid", HSDKThreadId());
        return HSDK_ERROR_INVALID;
    }

    err = HSDKDestroyThread(crtDevice->eventThread);
    if (err != HSDK_ERROR_SUCCESS) {
        logMessage(HSDK_ERROR, "[PhysicalDevice]ClosePhysicalDevice", "Error destroying thread eventThread", HSDKThreadId());
        return err;
    }

    err = crtDevice->close(crtDevice->deviceHandle);

    if (err != HSDK_ERROR_SUCCESS) {
        logMessage(HSDK_ERROR, "[PhysicalDevice]ClosePhysicalDevice", "Error closing port", HSDKThreadId());
        return err;
    }

    crtDevice->status = PHYS_CLOSED;

    ClearMessageQueue(crtDevice->inMessages);

    return HSDK_ERROR_SUCCESS;
}

/*! *********************************************************************************
* \brief   Sets the configuration for a device to data
*
*
* \param[in, out] device  pointer to the PhysicalDevice structure.
* \param[in] data  pointer to the UARTConfiguration structure.
*
* \return 0 for success
********************************************************************************** */
int ConfigurePhysicalDevice(PhysicalDevice *device, void *data)
{
    device->configurationData = data;

    return HSDK_ERROR_SUCCESS;
}

/*! *********************************************************************************
* \brief   Accepts the data to be written and puts it in its thread message queue
*          to be written at the appropriate time
*
*
* \param[in, out] device   pointer to the PhysicalDevice structure.
* \param[in] buf           pointer to the data to be written
* \param[in] size          the size of the data to be written
*
* \return A positive integer for the size
********************************************************************************** */
int WritePhysicalDevice(void *device, uint8_t *buf, uint32_t size)
{
    int err;
    PhysicalDevice *crtDevice = (PhysicalDevice *) device;
    // Check if the device exists
    if (crtDevice == NULL) {
        logMessage(HSDK_ERROR, "[PhysicalDevice]WritePhysicalDevice", "Physical device is NULL", HSDKThreadId());
        return HSDK_ERROR_INVALID;
    }

    RawFrame *tx = CreateTxRawFrame(buf, size);
    MessageQueuePut(crtDevice->inMessages, tx);
    err = HSDKSignalEvent(crtDevice->inMessages->sAnnounceData);

    return err;
}


/*! *********************************************************************************
* \brief    Attach a framer for the current UART device. This enables events triggered
*           by the PhysicalDevice thread to be received by the framer
*
* \param[in,out] dev    pointer to the physDev device
* \param[in] observer   pointer to the observer that will receive events, usually
*                       this will be the framer
* \param[in] Callback   callback function that will be executed upon events
*
* \return none
********************************************************************************** */
void AttachToPhysicalDevice(void *dev, void *observer, void(*Callback) (void *callee, void *object))
{
    PhysicalDevice *physDev = (PhysicalDevice *) dev;
    RegisterToEventManager(physDev->evtManager, observer, Callback);

    // this info is needed for sending ACKs to the device
    LENGTH_FIELD_SIZE = ((Framer *)observer)->lengthFieldSize;
}

/*! *********************************************************************************
* \brief  Detach the framer for the current PhysicalDevice device.
*
* \param[in,out] dev        pointer to the physDev device
* \param[in,out] observer   pointer to the observer object
*
* \return none
********************************************************************************** */
void DetachFromPhysicalDevice(void *dev, void *observer)
{
    PhysicalDevice *physDev = (PhysicalDevice *) dev;
    DeregisterFromEvent(physDev->evtManager, observer);
}


/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
* \brief    Verifies if this is an ACKframe.
*
* \param[in] buffer             data to be verified
* \param[in] lengthFieldSize    the size of the length field in bytes
*
* \return   0 is an ACK otherwise false
********************************************************************************** */
static void *WaitACK(void* lpParameter) //PhysicalDevice* device, RawFrame* tx)
{
    PhysicalDevice* device = (PhysicalDevice*)lpParameter;

    uint8_t retries_left = device->configParams->numberOfRetries;
    uint8_t loop = 1;
    int8_t ret = 0;
    int triggeredEvent;
    int flagReleaseLock;

    Event eventArray[2];
    eventArray[0] = device->stopTXACKTimeoutThread;
    eventArray[1] = device->startTXACKTimeoutThread;

    while (loop) {

        flagReleaseLock = 0;// lock not released
        uint8_t retries_left = device->configParams->numberOfRetries;

        ret = HSDKWaitMultipleEvents(eventArray, 2, INFINITE_WAIT, &triggeredEvent);

        if (ret != HSDK_ERROR_SUCCESS) {
            break;
        }

        switch (triggeredEvent) {
        case 0:
            logMessage(HSDK_INFO, "[PhysicalDevice] WaitACK", "Wait ACK device thread finished", HSDKThreadId());
            loop = 0;
            return NULL;

            /* Case 1 - RX from the board - not used for PCAP. The handling of packets from board is made in PCAPCallback. */
        case 1:

            do {
                /* Poll for the ACK. */
                int rc = HSDKWaitEvent(device->sAnnounceTXACK, device->configParams->timeoutAckMs);
                /* Poll error */
#if __linux__
                if (rc == -1) {
#elif _WIN32
                if (rc == int(WAIT_FAILED)) {
#endif
                    perror("[CheckFSCIAck] poll");
                    logMessage(HSDK_ERROR, "[CheckFSCIAck] poll", strerror(errno), HSDKThreadId());
                    DestroyRawFrame(lastTx);
                    HSDKResetEvent(device->sAnnounceTXACK);
                    break;
                }
                /* Poll timeout */
#if __linux__
                else if (rc == 0) {
#elif _WIN32
                else if (rc == int(WAIT_TIMEOUT)) {
#endif
                    logMessage(HSDK_INFO, "[CheckFSCIAck] poll", "timeout", HSDKThreadId());

                    rc = device->write(device->deviceHandle, lastTx->aRawData, lastTx->cbTotalSize);
                    if (rc == -1) {
                        perror("[CheckFSCIAck] write");
                        logMessage(HSDK_ERROR, "[CheckFSCIAck] write", strerror(errno), HSDKThreadId());
                        DestroyRawFrame(lastTx);
                        break;
                    }
                    else {
                        retries_left--;
                    }
                }
                /* Poll success with POLLIN data */
#if __linux__
                else if (rc == 1) {
#elif _WIN32
                else if (rc == int(WAIT_OBJECT_0)) {
#endif
                    // ACK received 
                    HSDKReleaseLock(device->inMessages->lock);
                    flagReleaseLock = 1;// lock released
                    DestroyRawFrame(lastTx);

                    break;
                }
                /* Poll success, but no POLLIN data */
                else {
                    rc = device->write(device->deviceHandle, lastTx->aRawData, lastTx->cbTotalSize);
                    if (rc == -1) {
                        perror("[CheckFSCIAck] write");
                        logMessage(HSDK_ERROR, "[CheckFSCIAck] write", strerror(errno), HSDKThreadId());
                        DestroyRawFrame(lastTx);
                        break;
                    }
                    else {
                        retries_left--;
                    }
                }
            } while (retries_left);

            if(flagReleaseLock == 0) {
                // No ACK received 
                HSDKReleaseLock(device->inMessages->lock);
            }

            break;
        }

        HSDKResetEvent(eventArray[1]);
    }

    return NULL;
}

/*! *********************************************************************************
* \brief  Thread function which waits for either its termination or an event from the
* associated TTY/SPIDEV/COM port.
*
* \param[in] lpParameter    pointer to a PhysicalDevice
*
* \return None
********************************************************************************** */
static void *DeviceThreadRoutine(void *lpParameter)
{
    PhysicalDevice *device = (PhysicalDevice *) lpParameter;
    uint8_t *dataBuffer = (uint8_t *)calloc(RX_SIZE, sizeof(uint8_t));
    int8_t ret = 0;
    uint32_t bytesRead;
    int err, triggeredEvent;
    uint8_t loop = 1;
    void *asyncMask = NULL;
    RawFrame *tx;
    Thread ackTimeoutThread; // thread to process ACK timeout

    if (device->configParams->fsciTxAck) {
        // Create a new thread to process ACK timeout
        ackTimeoutThread = HSDKCreateThread(WaitACK, device);
        if (ackTimeoutThread == INVALID_THREAD_HANDLE) {
            logMessage(HSDK_ERROR, "[PhysicalDevice]DeviceThreadRoutine", "ackTimeoutThread is NULL", HSDKThreadId());
            return NULL;
        }

        logMessage(HSDK_INFO, "[PhysicalDevice]DeviceThreadRoutine", "Created and start device thread", HSDKThreadId());
    }

    Event eventArray[3];
    eventArray[0] = device->stopThread;
    eventArray[1] = device->startThread;
    ret = HSDKWaitMultipleEvents(eventArray, 2, INFINITE_WAIT, &triggeredEvent);

    if (triggeredEvent == 0) {
        goto threadFinishLabel;
    }

    /* stop event */
    eventArray[0] = device->stopThread;

    /* RX event */
    eventArray[1] = device->waitable(device->deviceHandle, &asyncMask);
    if (device->type == SPI) {
        device->initialize(device->deviceHandle, spiClearBus);
        spiClearBus = 0;
    }

    /* TX event */
    eventArray[2] = device->inMessages->sAnnounceData;

    while (loop) {

        ret = HSDKWaitMultipleEvents(eventArray, 3, INFINITE_WAIT, &triggeredEvent);

        if (ret != HSDK_ERROR_SUCCESS) {
#ifdef __linux__
            HSDKFinishTriggerableEvent(asyncMask);
#endif
            break;
        }

        switch (triggeredEvent) {
            case 0:
                logMessage(HSDK_INFO, "[PhysicalDevice]DeviceThreadRoutine", "Physical device thread finished", HSDKThreadId());
                loop = 0;
#ifdef __linux__
                HSDKFinishTriggerableEvent(asyncMask);
#endif

                if (device->configParams->fsciTxAck) {
                    int err;

                    if (device->stopTXACKTimeoutThread == INVALID_EVENT_HANDLE) {
                        logMessage(HSDK_ERROR, "[PhysicalDevice]DeviceThreadRoutine", "stopTXACKTimeoutThread event is invalid", HSDKThreadId());
                        break;
                    }

                    err = HSDKSignalEvent(device->stopTXACKTimeoutThread);
                    if (err != HSDK_ERROR_SUCCESS) {
                        logMessage(HSDK_ERROR, "[PhysicalDevice]DeviceThreadRoutine", "stopTXACKTimeoutThread signaling error", HSDKThreadId());
                        break;
                    }

                    if (ackTimeoutThread == INVALID_THREAD_HANDLE) {
                        logMessage(HSDK_ERROR, "[PhysicalDevice]DeviceThreadRoutine", "ackTimeoutThread thread is invalid", HSDKThreadId());
                        break;
                    }

                    err = HSDKDestroyThread(ackTimeoutThread);
                    if (err != HSDK_ERROR_SUCCESS) {
                        logMessage(HSDK_ERROR, "[PhysicalDevice]DeviceThreadRoutine", "Error destroying thread ackTimeoutThread", HSDKThreadId());
                        break;
                    }
                }
                
                break;

            /* Case 1 - RX from the board - not used for PCAP. The handling of packets from board is made in PCAPCallback. */
            case 1:
                bytesRead = (uint32_t)RX_SIZE;
                err = device->read(device->deviceHandle, dataBuffer, &bytesRead);
                if (err == HSDK_ERROR_SUCCESS && bytesRead > 0) {
                    RawFrame *frame = CreateRxRawFrame(dataBuffer, bytesRead);
                    NotifyOnSameEvent(device->evtManager, frame, (void *(*)(void *))CloneRawFrame);
                    DestroyRawFrame(frame);
                }

                if (device->type != SPI) {
                    HSDKFinishTriggerableEvent(asyncMask);
                    eventArray[1] = device->waitable(device->deviceHandle, &asyncMask);
                }

                memset(dataBuffer, 0, RX_SIZE);
                break;

            case 2:
                tx = (RawFrame *)MessageQueueGet(device->inMessages);
                if (tx != NULL) {
                    int err = device->write(device->deviceHandle, tx->aRawData, tx->cbTotalSize);

                    if (device->configParams->fsciTxAck) {
                        
                        HSDKAcquireLock(device->inMessages->lock);
                        lastTx = tx;
                        HSDKSignalEvent(device->startTXACKTimeoutThread);
                    }
                    else
                    {
                        DestroyRawFrame(tx);
                    }
                    
                    if (err < 0) {
                        device->status = PHYS_ERROR;
                    }
                }

                HSDKResetEvent(eventArray[2]);
        }
    }

    HSDKResetEvent(device->stopThread);

threadFinishLabel:
    ret = 0;
    free(dataBuffer);

    return NULL;
}


static int AttachToConcreteImplementation(PhysicalDevice *device, char *deviceName)
{
    switch (device->type) {
        case UART:
            AttachToUARTDevice(device, deviceName);
            break;
#ifdef __linux__pcap__
        case PCAP:
            AttachToPCAPDevice(device, deviceName);
            break;
#endif
#ifdef __linux__spi__
        case SPI:
            AttachToSPIDevice(device, deviceName);
            break;
#endif
#ifdef _USE_BT
        case BT:
            AttachToBTDevice(device);
            break;
#endif
        default:
            logMessage(HSDK_ERROR, "[PhysicalDevice]AttachToConcreteImplementation", "Not implemented", HSDKThreadId());
            return HSDK_ERROR_INVALID;
    }

    return HSDK_ERROR_SUCCESS;
}

static int DetachFromConcreteImplementation(PhysicalDevice *device)
{
    switch (device->type) {
        case UART:
            DetachFromUARTDevice(device);
            break;
#ifdef __linux__pcap__
        case PCAP:
            DetachFromPCAPDevice(device);
            break;
#endif
#ifdef __linux__spi__
        case SPI:
            DetachFromSPIDevice(device);
            break;
#endif
#ifdef _USE_BT
        case BT:
            DetachFromBTDevice(device);
            break;
#endif
        default:
            logMessage(HSDK_ERROR, "[PhysicalDevice]AttachToConcreteImplementation", "Not implemented", HSDKThreadId());
            return HSDK_ERROR_INVALID;
    }

    return HSDK_ERROR_SUCCESS;
}
