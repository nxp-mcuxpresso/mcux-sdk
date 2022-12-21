/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/** 
* @file data_format_service.h
* @brief The format_service.h file describes the  interface and structures for the data-format standards.
*/

#ifndef DATA_FORMAT_SERVICE_H_
#define DATA_FORMAT_SERVICE_H_
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define DATA_FORMAT_OK 0 ///< Operation succeeded

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* @brief This defines the communication handle.
 */
typedef struct _comm_handle_
{
    void *pComm;     /*!< pointer to a specific communication channel.*/
    uint32_t status; /*!< Current Comm status.*/
} comm_handle_t;

/*  Event function signature.*/
typedef void (*DATA_FORMAT_Event_t)(void *pData); /*< Pointer to data format Event.*/

/*! @brief       The interface function to initialize the data-format service.*/
typedef int32_t(DATA_FORMAT_Init_t)(DATA_FORMAT_Event_t event, void *pInitializeData);
/*! @brief       The interface function to serialize the data*/
typedef int32_t(DATA_FORMAT_Serialize_t)(void *pData, uint32_t size, void *pDataElement);
/*! @brief       The interface function to deserialize the data.*/
typedef int32_t(DATA_FORMAT_Deserialize_t)(void *pData, uint32_t size, void *pDataElement);
/*! @brief       The interface function to append the data on the formated stream*/
typedef int32_t (DATA_FORMAT_Append_t))        (void * pData, uint32_t size, void* pDataElement));

/* @brief This defines the function pointers for the data format interface.
 */
typedef struct _data_format_interface_
{
    DATA_FORMAT_Init_t *Init;               /*!< Pointer to the data-format Initialize() function. */
    DATA_FORMAT_Serialize_t *Serialize;     /*!< Pointer to the data-format Serialize() function. */
    DATA_FORMAT_Deserialize_t *Deserialize; /*!< Pointer to the data-format Deserialize() function. */
    DATA_FORMAT_Append_t *Append;           /*!< Pointer to the data-format Append() function. */
} data_format_interface_t;
#endif // DATA_FORMAT_SERVICE_H_
