/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**
* @file comm_interface.h
* @brief The comm_interface.h file describes the interface definition for the
 communication interface. Each commaunication instance needs to implement comm interface.
*/

#ifndef COMM_INTERFACE_H_
#define COMM_INTERFACE_H_
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define COMM_INTERFACE_OK 0 ///< Operation succeeded

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* @brief This defines the communication interface handle
 */
typedef struct _comm_handle_
{
    void *pComm;     /*!< pointer to a specific communication channel.*/
    uint32_t status; /*!< Current Comm status.*/
} comm_handle_t;

/* @brief This defines the communication interface control config
 */
typedef struct _comm_control_
{
    uint32_t control; /*!< The Control TAG.*/
    uint32_t arg;     /*!< The Control Arguement value.*/
} comm_control_t;

/* @brief This defines the different commmunication types
 */
typedef enum _comm_type_
{
    COMM_UART,
    COMM_BLUETOOTH,
    COMM_I2C,
    COMM_SOCKET,
    COMM_NFC,
} comm_type_t;

/* @brief This defines the different commmunication types
 */
typedef enum _comm_instance_type_
{
    COMM_BLOCKING,    // Blocking Read and Write Calls
    COMM_NONBLOCKING, // NonBlocking Read and Write Calls
} comm_instance_type_t;

/*  Interface functions Signature.*/
typedef void (*COMM_Event_t)(uint32_t event); /*< Pointer to Comm Event.*/
/*! @brief       The interface function to get the capability of the communication interface.*/
typedef int32_t(COMM_GetCapabilities_t)(comm_handle_t *pHandle);
/*! @brief       The interface function to initialize the communication interface.*/
typedef int32_t(COMM_Init_t)(comm_handle_t *pHandle, void *pCommInstance, COMM_Event_t event, void *pInitializeData);
/*! @brief       The interface function to configure the communication interface.*/
typedef int32_t(COMM_Config_t)(comm_handle_t *pHandle, void *pConfigData);
/*! @brief       The interface function to send data through the communication interface.*/
typedef int32_t(COMM_Send_t)(comm_handle_t *pHandle, void *pData, uint32_t size);
/*! @brief       The interface function to receive data through the communication interface.*/
typedef int32_t(COMM_Receive_t)(comm_handle_t *pHandle, void *pData, uint32_t size);
/*! @brief       The interface function to get the status of the comm.*/
typedef int32_t(COMM_GetStatus_t)(comm_handle_t *pHandle);

/* @brief This defines the function pointers for the comm interface.
 */
typedef struct _comm_interface_
{
    COMM_GetCapabilities_t *GetCapabilities; /*!< Pointer to the communication GetCapabilities() function. */
    COMM_Init_t *Init;                       /*!< Pointer to the communication Initialize() function. */
    COMM_Config_t *Configure;                /*!< Pointer to the communication Configure() function. */
    COMM_Send_t *Send;                       /*!< Pointer to the communication send() function. */
    COMM_Receive_t *Receive;                 /*!< Pointer to the communication receive() function. */
    COMM_GetStatus_t *GetStatus;             /*!< Pointer to the adapter GetStatus() function. */
} comm_interface_t;
#endif // COMM_INTERFACE_H_
