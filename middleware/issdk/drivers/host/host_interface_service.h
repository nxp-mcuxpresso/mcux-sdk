/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/** 
* @file host_interface_service.h
* @brief The host_interface_service.h file describes the structures and definitions for the host.
*/

#ifndef HOST_INTERFACE_SERVICE_H_
#define HOST_INTERFACE_SERVICE_H_
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "comm_interface.h"

#define HOST_INTERFACE_OK 0
#define HOST_INTERFACE_VERSION ((1 << 4) | (0 & 0xF)) // Host Interface Version 1.0

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*  Interface functions Signature.*/
typedef void (*Host_Event_t)(uint32_t event); /*< Pointer to Host Event.*/

/* @brief This defines the handle to host
 */
typedef struct _host_interface_handle_
{
    comm_interface_t *pCommInterface;
    void *pInData;                     /*!< Input data for the callback .*/
    uint32_t status;                   /*!< Current Comm status.*/
    comm_handle_t commHandle;          /*!< pointer to a specific communication channel.*/
    Host_Event_t event;                /*!< Host Event callback: Future implementaion .*/
    comm_instance_type_t instanceType; /*!< COMM Instance Type .*/
} host_interface_handle_t;

/* @brief This defines the host interface config structure
 */
typedef struct _host_interface_config_
{
    uint32_t tbd; // tbd

} host_interface_config_t;

/* @brief This defines the host interface based events
 */
#define HOST_INTERFACE_EVENT_SEND_COMPLETE \
    (1UL << 0) ///< Send completed. Completed the data transfer. Useful for Asynchronous, non blocking calls
#define HOST_INTERFACE_EVENT_RECEIVE_COMPLETE \
    (1UL << 1) ///< Receive completed, Receved specifed bytes of data. Useful for Asynchronous, non blocking calls

typedef void (*BlockRead_t)(host_interface_handle_t *pHandle, void *pData); /*< Pointer to block read function.
User can implement start and end packet detection logic to determine unknown receive length.
This basically a data-interchangbility format dependent such as HDLC, JSON etc..*/
/******************************************************************************/
/*! @brief       The function to Initialize the Host
 *  @details     It initialize the host for the specified communucation channel and data format service.

 *  @param[in]   pHandle - pointer to the  interface handle
 *  @param[in]   type- host communication type
 *  @param[in]   pCommInstance - pointer to a communication object.
 *  @param[in]   inType - instanceType.
 *  @param[in]   event -  event handler callback
 *  @param[in]   pInData  - input data to underlying layers
 *  @return      ::HOST_Initialize() returns the status .
 *
 *  @Constraints None
 *
 *  @Reentrant   Yes
 */
int32_t HOST_Initialize(host_interface_handle_t *pHandle,
                        comm_type_t type,
                        void *pCommInstance,
                        comm_instance_type_t inType,
                        Host_Event_t event,
                        void *pInData);

/******************************************************************************/
/*! @brief       The function to Configure the Host
 *  @details     TBD

 *  @param[in]   pHandle - pointer to the  interface handle
 *  @param[in]   pConfigData - Host configuration information
 *  @return      ::HOST_Configure() returns the status .
 *
 *  @Constraints None
 *
 *  @Reentrant   Yes
 */
int32_t HOST_Configure(host_interface_handle_t *pHandle, void *pConfigData);
/******************************************************************************/
/*! @brief       The function to Send the data to the host
 *  @details     TBD

 *  @param[in]   pHandle - pointer to the  interface handle
 *  @param[in]   pData - pointer to a data to send
 *  @param[in]   size  - number of byte to send
 *  @return      ::HOST_Send() returns the status .
 *
 *  @Constraints None
 *
 *  @Reentrant   Yes
 */
int32_t HOST_Send(host_interface_handle_t *pHandle, uint8_t *pData, uint32_t size);

/*! @brief       The function to receive data from the host.
 *  @details     BlockRead callback function will be called only if Host is initialized with Blocking Call communication
 instance,
                 refer comm_instance_type_t inType HOST_Initialize() function.
                 If the host is initialized with blocking communication instance, This call will be blocked until
 BlockRead_t process returns provided BlockRead_t process is not NULL
                 else it will be blocked until specified number of requested bytes are received. User can implement own
 logic to separate packet start and end de-limiter in
                 BlockRead_t process to determine a stream or use provided Block Read function in the each Data Format.
                 If the host is intialized with NonBlocking Communication instance. This call will be immediately
 returns and Users Needs to Syschronous data based on
                 Host event HOST_INTERFACE_EVENT_RECEIVE_COMPLETE.
 *  @param[in]   pHandle   - pointer to the  interface handle.
 *  @param[out]  pData - pointer to data to be received.
 *  @param[out]  pRecvSize - number of byte received. This field is for the future use.
 *  @param[in]   size  - Nnumber of byte intend to receive, if user know. This argument has no impact if "BlockRead_t
 process" is not NULL and communication instance is Blocking
 *  @param[in]   process  - process function for the block data read. NOTE: This parameter is not valid, if
 communication Read function is Nonblocking.
    The logic in the callback can start and end packet data detection to get the unknown receive length stream data from
 the host.

 *  @return      ::HOST_Receive() returns the status .
 *
 *  @Constraints None
 *
 *  @Reentrant   Yes
 */
// Note: Signature of this function may change based on the implementation and usability.
int32_t HOST_Receive(
    host_interface_handle_t *pHandle, uint8_t *pData, uint32_t *pRecvSize, uint32_t size, BlockRead_t process);

#endif // HOST_INTERFACE_SERVICE_H_
