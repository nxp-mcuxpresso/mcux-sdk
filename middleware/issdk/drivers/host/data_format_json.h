/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/** 
* @file data_format_json.h
* @brief The format_json.h file describes the structures and definitions for the data-format standard JSON.
*/

#ifndef DATA_FORMAT_JSON_H_
#define DATA_FORMAT_JSON_H_
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#define HOST_INTERFACE 1
#if HOST_INTERFACE
#include "host_interface_service.h"
#include "host_io_uart.h"
#endif
#define DATA_FORMAT_JSON_OK 0
/*******************************************************************************
 * Definitions
 ******************************************************************************/

typedef enum _json_format_
{
    JSON_TYPE_OBJECT, /* String value pair, Note: Value will be primitive data type*/
    JSON_TYPE_ARRAY   /* Array of Values*/
} json_format_t;
/******************************************************************************/
/*! @brief       The function to serialize the data,
 *  @details     it applys the serialization in single data element,
                 Once user finishes the data stream with different data tag, set end flag to TRUE.

 *  @param[in]   pStr - pointer to the data stream - formated data put into this buffer
 *  @param[in]   pDataTagStr - Data tag name for a data
 *  @param[in]   pDataValue - Data value
 *  @param[in]   type  - Json data type
 *  @param[in]   end - flag determine the end of data stream serialization.
 *  @return      ::JSON_Serialize() returns the status .
 *
 *  @Constraints None
 *
 *  @Reentrant   Yes
 */
int32_t JSON_Serialize(char *pStr, char *pDataTagStr, char *pDataValue, json_format_t type, bool end);

/*! @brief       The function to deserialize the data,
 *  @details     it applys the deserialization in a single data element,

 *  @param[in]   pStr - pointer to a formated data stream
 *  @param[out]  pDataTagStr - Data tag name for a data
 *  @param[out]  pDataValue - Data value
 *  @param[in]   type  - Json data type
 *  @return      ::JSON_Deserialize() returns the status .
 *
 *  @Constraints None
 *
 *  @Reentrant   Yes
 */
// Note: Signature of this function may change based on the implementation and usability.
int32_t JSON_Deserialize(void *pInData, void *pDataTag, char *pDataValue, json_format_t type);

#if HOST_INTERFACE

/*! @brief       The function provides block data read for the JSON stream, This is for Blocking receive call
 *  @details     This can be the argument to host interface

 *  @param[in]   pHandle - pointer to a formated data stream
 *  @param[out]  pRecvData -  Pointer to RecvBuffer;
 *  @return      None.
 *
 *  @Constraints None
 *
 *  @Reentrant   Yes
 */
// Note: Signature of this function may change based on the implementation and usability.
void JSON_BlockDataRead_BlockingCall(host_interface_handle_t *pHandle, void *pRecvData);

/*! @brief       This function is a helper function to get json stream where the data length is unknown
 *  @details     Basically look for start and end packets and form a packet

 *  @param[out]  pRecvData -  Pointer to RecvBuffer;
 *  @param[out]  data -  one byte of data received.
 *  @parma[in]   event     - status event for send complete and receive complete
 *  @return      DATA_FORMAT_JSON_OK, if data read is completed. else still get more data.
 *
 *  @Constraints None
 *
 *  @Reentrant   Yes
 */
// Note: Signature of this function may change based on the implementation and usability.

int32_t JSON_Get_Stream_NonBlockingCall(void *pRecvData, uint8_t data, uint8_t *state, uint8_t *buffIndex);

/*! @brief       Function to handle incomming JSON encoded bytes form the Host over UART.
 *  @details     This function will be called on receipt of every UART Byte
 *               and will do the JSON combination to create a Host Message.
 *  @param[in]   uint8_t c The character in the UART payload.
 *  @param[in]   host_rx_packet_t *pHostRxPkt The Host Packet context structure.
 *  @return      bool Success/Failure.
 *  @constraints This should be the called only after DEBUG/UART has been initialized.
 *  @reeentrant  No
 */
bool JSON_Process_Rx_Byte(uint8_t c, host_rx_packet_t *pHostRxPkt);

/*  @brief       Function to format bytes for JSON to be sent to Host over UART.
 *  @details     This function will encode a Host Protocol formatted Message to be sent to Host over UART.
 *  @param[in]   uint8_t *pbuffer The handle to the input buffer containing the Host message.
 *  @param[in]   uint8_t *pMsg    The handle to the output buffer containing the formatted Host message.
 *  @param[in]   size_t size     The number of bytes to be sent starting form the buffer.
 *  @return      size_t          Length of the encoded message.
 *  @constraints This should be the called only after DEBUG/UART has been initialized.
 *  @reeentrant  No
 */
size_t JSON_Process_Tx_Msg(const uint8_t *pBuffer, uint8_t *pMsg, size_t size);

#endif

#endif // DATA_FORMAT_JSON_H_
