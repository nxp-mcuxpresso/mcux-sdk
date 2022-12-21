/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/** 
* @file data_format_json.c
* @brief The data_format_json.c file implements JSON data format interfaces and services.
*/
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "data_format_json.h"
/*******************************************************************************
 * Variables
 ******************************************************************************/
const char *gpJsonHeader = {"{\"d\":{"};
const char *gpJsonFooter = "}}";
/*******************************************************************************
* Prototypes
******************************************************************************/

/* @brief This defines the json packet state: Note: - Just dummy state:@todo for the actual implementation
 */
typedef enum _json_packet_state_
{
    STATE_NONE,
    STATE_START_PACKET,
    STATE_PAYLOAD,
    STATE_END_PACKET,
} json_packet_state_t;
/*******************************************************************************
 * Code
 *****************************************************************************/
int32_t JSON_Serialize(char *pStr, char *pDataTagStr, char *pDataValue, json_format_t type, bool end)
{
    //@todo handle the validation error. may be need to re-do for the better implementation
    if (JSON_TYPE_OBJECT == type)
    {
        if (NULL != pStr)
        {
            if (0 == strlen(pStr))
            {
                // Add Header
                strcat(pStr, gpJsonHeader);
            }
            else
            {
                strcat(pStr, ",");
            }

            strcat(pStr, "\"");
            strcat(pStr, pDataTagStr);
            strcat(pStr, "\":");
            strcat(pStr, pDataValue);
        }
        // Add the footer
        if (end)
        {
            strcat(pStr, gpJsonFooter);
        }
    }
    return DATA_FORMAT_JSON_OK;
}
/*Note: Signature of this function may change based on the actual implemenation*/
int32_t JSON_Deserialize(void *pInData, void *pDataTag, char *pDataValue, json_format_t type)
{
    //@todo handle the validation error(array bounce. etc..) may need to redo for the better implementation
    return DATA_FORMAT_JSON_OK;
}
#if HOST_INTERFACE
void JSON_BlockDataRead_BlockingCall(host_interface_handle_t *pHandle, void *pRecvData)
{
    // @todo- This function does not implement exact json format.its an dummy implementation,
    // Need to implement proper handling for actual example applicaton
    comm_interface_t *pCommInt = pHandle->pCommInterface;
    uint8_t *pData = pRecvData;
    uint8_t data;
    bool isReceivedStream = false;
    uint8_t state = STATE_NONE;
    while (!isReceivedStream)
    {
        pCommInt->Receive(&pHandle->commHandle, (uint8_t *)&data, 1);
        switch (state)
        {
            case STATE_NONE:
            {
                if (data == '{')
                    state = STATE_START_PACKET;
                else
                    continue;
            }
            break;
            case STATE_START_PACKET:
            case STATE_PAYLOAD:
                if (data == '}')
                {
                    state = STATE_NONE;
                    isReceivedStream = true;
                }
                else
                {
                    *pData++ = data;
                }
                break;
            default:
                state = STATE_NONE;
                isReceivedStream = true;
                break;
        }
    }
}
//@todo- this is a dummy implemenation for a quick hack
int32_t JSON_Get_Stream_NonBlockingCall(void *pRecvData, uint8_t data, uint8_t *state, uint8_t *buffIndex)
{
    uint8_t *pData = pRecvData;
    bool isReceivedStream = false;

    switch (*state)
    {
        case STATE_NONE:
            if (data == '{')
                *state = STATE_START_PACKET;
            break;
        case STATE_START_PACKET:
        case STATE_PAYLOAD:
            if (data == '}')
            {
                *state = STATE_NONE;
                isReceivedStream = true;
                *buffIndex = 0;
            }
            else
            {
                *(pData + *buffIndex) = data;
                (*buffIndex)++;
            }
            break;
        default:
            *state = STATE_NONE;
            isReceivedStream = true;
            break;
    }
    if (isReceivedStream == true)
    {
        return DATA_FORMAT_JSON_OK;
    }
    else
    {
        return -1;
    }
}

/* TODO: Function to handle incomming JSON encoded bytes form the Host over UART. */
bool JSON_Process_Rx_Byte(uint8_t c, host_rx_packet_t *pHostRxPkt)
{
    return false;
}

/* TODO: Function to format data for JSON and send bytes to Host over UART. */
size_t JSON_Process_Tx_Msg(const uint8_t *pBuffer, uint8_t *pMsg, size_t size)
{
    memcpy(pMsg, pBuffer, size);
    return size;
}

#endif
