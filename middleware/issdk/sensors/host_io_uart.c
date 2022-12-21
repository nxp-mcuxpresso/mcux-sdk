/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file host_io_uart.c
 * @brief The host_io_uart.c file contains definitions for UART based streaming interface
 * for sending and reseiving messages to and from Host using ISSDK Host Protocol.
 */

/*******************************************************************************
 * Standard C Includes
 ******************************************************************************/
#include <stdlib.h>

/*******************************************************************************
 * SDK Includes
 ******************************************************************************/
#include "fsl_common.h"

/*******************************************************************************
 * ISSDK Includes
 ******************************************************************************/
#include "host_io_uart.h"
#include "register_io_i2c.h"
#include "register_io_spi.h"
#include "data_format_hdlc.h"
#include "data_format_json.h"

/*******************************************************************************
 * Global Variables
 ******************************************************************************/
host_interface_handle_t gHostHandle = {0};
uint8_t gUartRxBuff, gHostRxBuff[HOST_RX_BUF_LEN];
host_rx_packet_t gHostRxPkt = {.pRxbuf = gHostRxBuff};
host_channel_params_t gHostChannelParams[MAX_HOST_STREAMS];
volatile bool bUartTxComplete, bUartRxPendingMsg, bUartErrorMsg;

/*******************************************************************************
 * Functions
 ******************************************************************************/
/* Callback functions to handle incomming messages form the Host over UART. */
void HOST_SignalEvent_t(uint32_t event)
{
    switch (event)
    {
        case ARM_USART_EVENT_RECEIVE_COMPLETE:
            bUartRxPendingMsg = true;
            break;
        case ARM_USART_EVENT_SEND_COMPLETE:
            bUartTxComplete = true;
            break;
        default:
            bUartErrorMsg = true;
            break;
    }
}

/* Function to lookup slave handle. */
uint8_t getSlaveIndex(uint8_t slaveAddress)
{
    for (uint8_t stream = 0; stream < MAX_HOST_STREAMS; stream++)
    {
        if (gHostChannelParams[stream].slaveAddress == slaveAddress)
        {
            return stream;
        }
    }

    /* If Address in not recognised, default to the first stream. */
    return 0;
}

/* Function to populate Streaming Packet Header.
 * Outgoing  Iso Packet Format: (As per ISSDK Host Protocol Definition)
 * Byte 0 : (Start Byte) HDLC Frame START MARKER. (Will be added by HDLC_Process_Tx_Msg())
 * Byte 1 : Frame TAG (Interface)
 * Byte 2 : Length    (Payload Length)
 * Byte 3+: Payload   (Depending upon sensor sample length + 1 for Stream ID)
 * Byte E : (End Byte) HDLC Frame STOP MARKER. (Will be added by HDLC_Process_Tx_Msg())
 */
void Host_IO_Add_ISO_Header(uint8_t streamID, uint8_t *pStreamingPacket, size_t sizePayload)
{
    if (pStreamingPacket == NULL)
    {
        return;
    }

    pStreamingPacket[HOST_MSG_HDR_TAG_OFFSET] = HOST_PRO_INT_ISO_TAG;
    pStreamingPacket[HOST_ISO_LEN_MSB_OFFSET] = (sizePayload + 1) >> 8;     /* Size of Sample + Stream ID */
    pStreamingPacket[HOST_ISO_LEN_LSB_OFFSET] = (sizePayload + 1) & 0x00FF; /* Size of Sample + Stream ID */
    pStreamingPacket[HOST_ISO_PAYLOAD_OFFSET] = streamID;
}

/* Function to get Stream ID, set Encoding and configure RLI related parameters. */
uint8_t Host_IO_Init(ARM_DRIVER_USART *pDrv, void *pBus, void *pDevInfo, void *spiSlaveParams, uint16_t slaveAddress)
{
    static uint8_t streamID = 0;

    /* Configure the UART callback if not already configured. */
    if (gHostHandle.pCommInterface == NULL)
    {
        HOST_Initialize(&gHostHandle, COMM_UART, (void *)pDrv, COMM_NONBLOCKING, HOST_SignalEvent_t, NULL);
        do /* Flush RX buffer. */
        {
            bUartRxPendingMsg = false;
            HOST_Receive(&gHostHandle, &gUartRxBuff, NULL, 1, NULL);
        } while (bUartRxPendingMsg);
        bUartTxComplete = true; /* Reset TX Flag. */
        bUartErrorMsg = false;  /* Reset Error Flag. */
    }

    /* Host has to be accesible by 1 UART interface for all subscriptions
     * and Number of streams less than MAX. */
    if (gHostHandle.commHandle.pComm != pDrv || streamID == MAX_HOST_STREAMS)
    {
        return 0;
    }

    /* Save the I2C/SPI Bus handle. */
    gHostChannelParams[streamID].pCommDrv = pBus;
    gHostChannelParams[streamID].deviceInfo = pDevInfo;
    gHostChannelParams[streamID].slaveAddress = slaveAddress;

    /* If device type is I2C, Slave Handle will be NULL. */
    gHostChannelParams[streamID].pSPIparams = spiSlaveParams;

    return ++streamID;
}

/* Function to send bytes to Host over UART. */
void Host_IO_Send(uint8_t *pMsg, size_t size, uint8_t encoding)
{
    size_t encodedSize = 0;
    static uint8_t *pMsgEncoded = NULL;

    while (bUartTxComplete == false)
    {
        __NOP(); /* Wait if the previous Tx is still Pending. */
    }
    free(pMsgEncoded);

    switch (encoding)
    {
        case HOST_FORMAT_HDLC:
            pMsgEncoded = malloc(size * 2); /* Allocate 2x the size to compensate for escape characters. */
            encodedSize = HDLC_Process_Tx_Msg(pMsg, pMsgEncoded, size); /* Get the Encoded Message. */
            break;
        case HOST_FORMAT_JSON:
            pMsgEncoded = malloc(size * 4); /* Allocate 4x the size to compensate for string character encoding. */
            encodedSize = JSON_Process_Tx_Msg(pMsg, pMsgEncoded, size); /* Get the Encoded Message. */
            break;
        case HOST_FORMAT_PLAIN:
        default:
            pMsgEncoded = malloc(size);
            memcpy(pMsgEncoded, pMsg, size);
            encodedSize = size;
            break;
    }

    /* Send message to Host. */
    bUartTxComplete = false;
    HOST_Send(&gHostHandle, pMsgEncoded, encodedSize);
}

/*  Function to check Rx and process received bytes and (re)enable UART Rx.
 *  Command Types Supported :
 *  1) Write App Data - Start/Stop Streaming.
 *  2) Write Register Data - Register Address and Value.
 *  3) Read Register Data - Start Address and Number of Bytes.
 *  4) Read Device Info - Return Major/Minor + Board and Shield Names.
 *
 * Incoming Message Format (Host Commands): (As per ISSDK Host Protocol Definition)
 * Byte 0 : Frame TAG   (Interface|Command)
 * Byte 1 : Sequence ID (Random Txn Identifier)
 * Byte 2 : Length MSB  (Payload Length MSB)
 * Byte 3 : Length LSB  (Payload Length LSB)
 * Byte 4+: Payload
 *
 * Outgoing Respone Format (Host Commands): (As per ISSDK Host Protocol Definition)
 * Byte 0 : Frame TAG   (Status|Interface|Command)
 * Byte 1 : Sequence ID (Random Txn Identifier)
 * Byte 2 : Length MSB  (Payload Length MSB)
 * Byte 3 : Length LSB  (Payload Length LSB)
 * Byte 4+: Payload (Optional, depending upon requested operation)
 *
 * Incoming Message Format (ISO Command): (As per ISSDK Host Protocol Definition)
 * Byte 0 : Frame TAG   (Interface)
 * Byte 1 : Length MSB  (Payload Length MSB)
 * Byte 2 : Length LSB  (Payload Length LSB)
 * Byte 3+: Payload
 *
 * Incoming Message Format (Device Info): (As per ISSDK Host Protocol Definition)
 * Byte 0 : Frame TAG   (Interface)
 *
 * Outgoing Respone Format (Device Info): (As per ISSDK Host Protocol Definition)
 * Byte 0 : Frame TAG   (Interface)
 * Byte 1 : Version ID  (ISSDK : Major | Minor Numbers)
 * Byte 2 : Length of Board Name (Optional : populated by user callback)
 * Byte 3 : Length of Shield Name (Optional : populated by user callback)
 * Byte 4+: Payload (Board Name + Board Name) (Optional : populated by user callback)
 */
void Host_IO_Receive(host_cmd_proc_fn_t process_host_command, uint8_t encoding)
{
    uint8_t responseTag = gHostRxBuff[HOST_MSG_HDR_TAG_OFFSET] & HOST_PRO_CMD_WR_NAK_TAG;
    comm_control_t rxAbort = {.control = ARM_USART_ABORT_RECEIVE, .arg = 0};
    size_t dataLength, responseSize = HOST_RSP_HDR_LEN;
    bool bCmdSuccess = false, bMessageReceived = false;
    uint8_t *pMsgResponse = NULL;

    /* If error flag is set ABORT and RESTART transaction. */
    if (bUartErrorMsg)
    {
        bUartErrorMsg = false;
        bUartRxPendingMsg = false;
        HOST_Configure(&gHostHandle, &rxAbort);
        HOST_Receive(&gHostHandle, &gUartRxBuff, NULL, 1, NULL);
    }

    if (bUartRxPendingMsg)
    {
        switch (encoding)
        {
            case HOST_FORMAT_HDLC:
                bMessageReceived = HDLC_Process_Rx_Byte(gUartRxBuff, &gHostRxPkt);
                break;
            case HOST_FORMAT_JSON:
                bMessageReceived = JSON_Process_Rx_Byte(gUartRxBuff, &gHostRxPkt);
                break;
            default:
                break;
        }

        bUartErrorMsg = false;
        bUartRxPendingMsg = false;
        HOST_Receive(&gHostHandle, &gUartRxBuff, NULL, 1, NULL);
    }

    if (bMessageReceived)
    {
        do
        {
            dataLength = gHostRxPkt.mIndex;
            /* Check if it is a 1-byte Device Info Message from Host. */
            if ((gHostRxBuff[HOST_MSG_HDR_TAG_OFFSET] & HOST_PRO_INT_DEV_TAG) && (dataLength == 1))
            { /* Allocate memory for response packet for this command and populate the payload. */
                pMsgResponse = malloc(HOST_DEV_RSP_LEN);
                dataLength = 0; /* Incoming Payload is Zero. */
                if (process_host_command)
                { /* Call the user callback to proces the user specific payload. */
                    bCmdSuccess = process_host_command(gHostRxBuff[HOST_MSG_HDR_TAG_OFFSET], NULL,
                                                       pMsgResponse + HOST_DEV_LEN_STR_OFFSET, &dataLength,
                                                       HOST_DEV_RSP_LEN - HOST_DEV_LEN_STR_OFFSET);
                }
                if (bCmdSuccess == false)
                {
                    dataLength = 0;
                }

                responseTag = HOST_PRO_INT_DEV_TAG;
                responseSize = HOST_DEV_LEN_STR_OFFSET + dataLength;
                break;
            }
            dataLength = (((uint16_t)gHostRxBuff[HOST_ISO_LEN_MSB_OFFSET] << 8) | gHostRxBuff[HOST_ISO_LEN_LSB_OFFSET]);
            /* Check if it is an ISO Message from Host and has > 0 Byte payload. */
            if ((gHostRxBuff[HOST_MSG_HDR_TAG_OFFSET] & HOST_PRO_INT_ISO_TAG) && (dataLength > 0))
            {
                if (dataLength == (gHostRxPkt.mIndex - HOST_ISO_PAYLOAD_OFFSET) && process_host_command)
                { /* Call the user callback to proces the user specific payload if packet integrity is valid. */
                    process_host_command(gHostRxBuff[HOST_MSG_HDR_TAG_OFFSET], gHostRxBuff + HOST_ISO_PAYLOAD_OFFSET,
                                         NULL, /* No buffer since no response for ISO Messages. */
                                         &dataLength, 0);
                }
                return; /* No response for ISO Messages. */
            }

            dataLength = (((uint16_t)gHostRxBuff[HOST_MSG_LEN_MSB_OFFSET] << 8) | gHostRxBuff[HOST_MSG_LEN_LSB_OFFSET]);
            if (dataLength != (gHostRxPkt.mIndex - HOST_MSG_CMD_OPC_OFFSET)) /* Ensure packet integrity */
            {
                return; /* Drop corrupted and duplicate packets */
            }
            /* Allocate memory for response packet for this command. */
            pMsgResponse = malloc(responseSize);

            /* Check if it is a Command from Host to Write Register Data and has 3+ Byte payload (SlaveAddress,
             * RegisterAddress and ValuesToWrite). */
            if ((gHostRxBuff[HOST_MSG_HDR_TAG_OFFSET] == (HOST_PRO_INT_CMD_TAG | HOST_PRO_CMD_W_REG_TAG)) &&
                (dataLength >= 3))
            {
                int32_t status = ARM_DRIVER_ERROR;
                /* Fetch the slave bus handle using known Slave Address. */
                uint8_t deviceID = getSlaveIndex(gHostRxBuff[HOST_MSG_CMD_SLAVE_ADDR_OFFSET]);
                if (process_host_command)
                { /* Call the user callback to enable user pre-proces the register write payload (if required). */
                    process_host_command(gHostRxBuff[HOST_MSG_HDR_TAG_OFFSET],
                                         gHostRxBuff + HOST_MSG_CMD_SLAVE_ADDR_OFFSET, NULL, &dataLength, 0);
                }
                /* Confirm payload has enough number of bytes to write. */
                if (gHostChannelParams[deviceID].pCommDrv &&
                    gHostRxPkt.mIndex - HOST_MSG_CMD_SLAVE_ADDR_OFFSET >= dataLength)
                {
                    if (gHostChannelParams[deviceID].pSPIparams)
                    {
                        status = Register_SPI_BlockWrite(
                            gHostChannelParams[deviceID].pCommDrv, gHostChannelParams[deviceID].deviceInfo,
                            gHostChannelParams[deviceID].pSPIparams, gHostRxBuff[HOST_MSG_CMD_REGIS_ADDR_OFFSET],
                            gHostRxBuff + HOST_MSG_CMD_VALUE_OFFSET, dataLength - 2);
                    }
                    else
                    {
                        status = Register_I2C_BlockWrite(
                            gHostChannelParams[deviceID].pCommDrv, gHostChannelParams[deviceID].deviceInfo,
                            gHostRxBuff[HOST_MSG_CMD_SLAVE_ADDR_OFFSET], gHostRxBuff[HOST_MSG_CMD_REGIS_ADDR_OFFSET],
                            gHostRxBuff + HOST_MSG_CMD_VALUE_OFFSET, dataLength - 2);
                    }
                }
                if (ARM_DRIVER_OK == status)
                {
                    responseTag |= HOST_PRO_CMD_WR_ACK_TAG;
                }
                break;
            }
            /* Check if it is a Command from Host to Read Register Data and has 3 Byte payload (SlaveAddress,
             * RegisterAddress and BytesToRead). */
            if ((gHostRxBuff[HOST_MSG_HDR_TAG_OFFSET] == (HOST_PRO_INT_CMD_TAG | HOST_PRO_CMD_R_REG_TAG)) &&
                (dataLength == 3))
            {
                int32_t status = ARM_DRIVER_ERROR;
                /* Fetch the slave bus handle using known Slave Address. */
                uint8_t deviceID = getSlaveIndex(gHostRxBuff[HOST_MSG_CMD_SLAVE_ADDR_OFFSET]);
                /* Allocate memory as per updated size of response packet for this command. */
                free(pMsgResponse);
                pMsgResponse = malloc(responseSize + gHostRxBuff[HOST_MSG_CMD_LENGTH_OFFSET]);
                if (gHostChannelParams[deviceID].pCommDrv)
                {
                    if (gHostChannelParams[deviceID].pSPIparams)
                    {
                        status = Register_SPI_Read(
                            gHostChannelParams[deviceID].pCommDrv, gHostChannelParams[deviceID].deviceInfo,
                            gHostChannelParams[deviceID].pSPIparams, gHostRxBuff[HOST_MSG_CMD_REGIS_ADDR_OFFSET],
                            gHostRxBuff[HOST_MSG_CMD_LENGTH_OFFSET], pMsgResponse + responseSize);
                    }
                    else
                    {
                        status = Register_I2C_Read(
                            gHostChannelParams[deviceID].pCommDrv, gHostChannelParams[deviceID].deviceInfo,
                            gHostRxBuff[HOST_MSG_CMD_SLAVE_ADDR_OFFSET], gHostRxBuff[HOST_MSG_CMD_REGIS_ADDR_OFFSET],
                            gHostRxBuff[HOST_MSG_CMD_LENGTH_OFFSET], pMsgResponse + responseSize);
                    }
                }
                if (process_host_command)
                { /* Call the user callback to enable user post-process the register read payload (if required). */
                    process_host_command(gHostRxBuff[HOST_MSG_HDR_TAG_OFFSET],
                                         gHostRxBuff + HOST_MSG_CMD_SLAVE_ADDR_OFFSET, pMsgResponse + responseSize,
                                         &dataLength, gHostRxBuff[HOST_MSG_CMD_LENGTH_OFFSET]);
                }
                if (ARM_DRIVER_OK == status)
                {
                    responseTag |= HOST_PRO_CMD_WR_ACK_TAG;
                    responseSize += gHostRxBuff[HOST_MSG_CMD_LENGTH_OFFSET];
                }
                break;
            }
            /* Check if it is a Command from Host for Read/Write Configuration or User defined and has > 0 Byte payload.
             */
            if ((gHostRxBuff[HOST_MSG_HDR_TAG_OFFSET] & HOST_PRO_INT_CMD_TAG) && (dataLength > 0))
            { /* Allocate memory for max possible response packet size for this command and populate the payload. */
                free(pMsgResponse);
                pMsgResponse = malloc(HOST_CMD_RSP_LEN);
                if (process_host_command)
                { /* Call the user callback to proces the user specific payload. */
                    bCmdSuccess = process_host_command(gHostRxBuff[HOST_MSG_HDR_TAG_OFFSET],
                                                       gHostRxBuff + HOST_MSG_CMD_OPC_OFFSET,
                                                       pMsgResponse + HOST_MSG_CMD_OPC_OFFSET, &dataLength,
                                                       HOST_CMD_RSP_LEN - HOST_MSG_CMD_OPC_OFFSET);
                }
                if (bCmdSuccess)
                {
                    responseTag |= HOST_PRO_CMD_WR_ACK_TAG;
                }
                else
                {
                    dataLength = 0;
                }

                responseSize = HOST_MSG_CMD_OPC_OFFSET + dataLength;
                break;
            }
        } while (false);

        /* Populate the response packet header. */
        pMsgResponse[HOST_MSG_HDR_TAG_OFFSET] = responseTag;
        if (responseTag == HOST_PRO_INT_DEV_TAG)
        {
            pMsgResponse[HOST_DEV_HDR_VER_OFFSET] = HOST_INTERFACE_VERSION;
        }
        else
        {
            pMsgResponse[HOST_MSG_HDR_SEQ_OFFSET] = gHostRxBuff[HOST_MSG_HDR_SEQ_OFFSET];
            pMsgResponse[HOST_MSG_LEN_MSB_OFFSET] = (responseSize - HOST_RSP_HDR_LEN) >> 8;
            pMsgResponse[HOST_MSG_LEN_LSB_OFFSET] = (responseSize - HOST_RSP_HDR_LEN) & 0xFF;
        }

        /* Send response to Host. */
        Host_IO_Send(pMsgResponse, responseSize, encoding);
        free(pMsgResponse);
    }
}
