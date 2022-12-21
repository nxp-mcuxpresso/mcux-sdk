/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file host_io_uart.h
 * @brief The host_io_uart.h file contains the Host Protocol interface definitions and configuration.
 */

#ifndef HOST_IO_UART_H_
#define HOST_IO_UART_H_

/*******************************************************************************
 * CMSIS Includes
 ******************************************************************************/
#include "Driver_USART.h"

/*******************************************************************************
 * Types and Definitions
 ******************************************************************************/
#define STREAMING_HEADER_LEN (4)  /* ISSDK Host Protocol defined Iso Cmd Header Length + Stream ID. */
#define HOST_RX_BUF_LEN (64)      /* MAX size of Rx Host CMDs. */
#define HOST_RSP_HDR_LEN (4)      /* Size of Host response message header. */
#define HOST_DEV_RSP_LEN (128)    /* MAX size of Host Dev Info Response. */
#define HOST_CMD_RSP_LEN (64)     /* MAX size of Host Command Response. */
#define MAX_HOST_STREAMS (4)      /* Max Streams that can be defined by the user Application. */
#define HOST_CMD_RESP_ACK (0x80)  /* HOST CMD Ack code. */
#define HOST_CMD_RESP_NACK (0xC6) /* HOST CMD Nack code. */
#define EVENT_STREAM_ID (0xFF)    /* Stream ID in ISO Message for posting Events (such as freefall) */

/*! @brief This structure holds information regarding the Encoding and RLI interface parameters. */
typedef struct
{
    void *deviceInfo;
    void *pCommDrv;
    void *pSPIparams;
    uint16_t slaveAddress;
} host_channel_params_t;

/*! @brief The Host Command Process Function ([IN]Command TAG, [IN]Commad Buffer, [OUT]Response Buffer,
 * [IN/OUT]MessageSize, [IN]BufferSize) */
typedef bool (*host_cmd_proc_fn_t)(uint8_t, uint8_t *, uint8_t *, size_t *, size_t);

/*! @brief This structure holds information to receive a packet of data to the host. */
typedef struct
{
    uint8_t rxState; /* Internal receive state */
    uint8_t mIndex;  /* Message index */
    uint8_t *pRxbuf; /* Receive buffer */
} host_rx_packet_t;

/*! @brief Bit aligned values for Host Protocol Interface IDs (Bits 5-6). */
#define HOST_PRO_INT_CMD_TAG (0x20) /* 1 */
#define HOST_PRO_INT_ISO_TAG (0x40) /* 2 */
#define HOST_PRO_INT_DEV_TAG (0x60) /* 3 */

/*! @brief Bit aligned values for Host Protocol Command Interface Type IDs (Bits 0-4). */
#define HOST_PRO_CMD_X_RES_TAG (0x00) /* 0 (Reserved) */
#define HOST_PRO_CMD_W_CFG_TAG (0x01) /* 1 */
#define HOST_PRO_CMD_R_CFG_TAG (0x02) /* 2 */
#define HOST_PRO_CMD_W_REG_TAG (0x03) /* 3 */
#define HOST_PRO_CMD_R_REG_TAG (0x04) /* 4 */

/*! @brief Bit aligned values for Host Protocol Command Interface Status IDs (Bit 7). */
#define HOST_PRO_CMD_WR_NAK_TAG (0x7F) /* 0 */
#define HOST_PRO_CMD_WR_ACK_TAG (0x80) /* 1 */

enum
{
    HOST_FORMAT_HDLC = 0,
    HOST_FORMAT_JSON,
    HOST_FORMAT_PLAIN,
};

enum
{
    HOST_MSG_HDR_TAG_OFFSET = 0,
    HOST_MSG_HDR_SEQ_OFFSET = 1,
    HOST_MSG_LEN_MSB_OFFSET = 2,
    HOST_MSG_LEN_LSB_OFFSET = 3,
    HOST_MSG_CMD_OPC_OFFSET = 4,
    HOST_MSG_CMD_ACT_OFFSET = 5,
    HOST_DEV_HDR_VER_OFFSET = 1,
    HOST_DEV_LEN_STR_OFFSET = 2,
    HOST_ISO_LEN_MSB_OFFSET = 1,
    HOST_ISO_LEN_LSB_OFFSET = 2,
    HOST_ISO_PAYLOAD_OFFSET = 3,
    HOST_MSG_CMD_SLAVE_ADDR_OFFSET = 4,
    HOST_MSG_CMD_REGIS_ADDR_OFFSET = 5,
    HOST_MSG_CMD_VALUE_OFFSET = 6,
    HOST_MSG_CMD_LENGTH_OFFSET = 6,
};

/*! @brief This enum lists the Configuration Command Operation Codes. */
enum
{
    HOST_CMD_NOP = 0,     /* 0 (No Operation) */
    HOST_CMD_START,       /* 1 (Start Streaming) */
    HOST_CMD_STOP,        /* 2 (Stop Streaming) */
    HOST_CMD_FLASH_START, /* 3 (Enter FLASH Mode) */
    HOST_CMD_FLASH_BYTES, /* 4 (Bytes to FLASH) */
    HOST_CMD_FLASH_STOP,  /* 5 (Exit FLASH Mode) */
};

/*! @brief       Defines the HOST UART signal event handler.
 *  @details     The Signal Event Handler function required by host_io_uart.c.
 *  @param[in]   event The UART event that occured.
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      void
 */
void HOST_SignalEvent_t(uint32_t event);

/*******************************************************************************
 * APIs
 ******************************************************************************/
/* ===================================================================
 *  @brief       Function populate Streaming Packet Header.
 *  @details     This function sets up streaming related parameters in the ISO Message Header.
 *  @param[in]   uint8_t streamID The stream ID this packet corresponds.
 *  @param[in]   uint8_t *streamingPacket The handle to the buffer containing the streaming packet.
 *  @param[in]   size_t sizePayload       The size of the actual payload excluding the Header.
 *  @return      None
 *  @constraints This should be the called only after DEBUG Port has been initialized.
 *  @reeentrant  No
 * =================================================================== */
void Host_IO_Add_ISO_Header(uint8_t streamID, uint8_t *pStreamingPacket, size_t sizePayload);

/* ===================================================================
 *  @brief       Function to get Stream ID, set Encoding and configure RLI related parameters.
 *               Stream IDs are allocated incrementally everytime this API is called to for a new Stream.
 *               It also configures UART for receiving RLI messages form Host.
 *  @param[in]   ARM_DRIVER_USART *pDrv Pointer to the UART communication bus.
 *  @param[in]   void *pBus Pointer to the I2C/SPI communication bus for register read/write support.
 *  @param[in]   void *pDevInfo Pointer to the I2C/SPI device info structure.
 *  @param[in]   void *spiSlaveParams (Only for SPI) The handle to the structure containing SPI Slave parameters.
 *  @param[in]   uint16_t slaveAddress The Sensor's I2C Slave Address to identify the slave (required for both I2C/SPI).
 *  @return      uint8_t The unique ID for this stream.
 *  @constraints This should be the called only after DEBUG Port has been initialized.
 *  @reeentrant  No
 * =================================================================== */
uint8_t Host_IO_Init(ARM_DRIVER_USART *pDrv, void *pBus, void *pDevInfo, void *spiSlaveParams, uint16_t slaveAddress);

/* ===================================================================
 *  @brief       Function to send bytes to Host.
 *  @details     This function will send a Message to Host over UART.
 *  @param[in]   uint8_t *pMsg The handle to the buffer containing the formatted Host message.
 *  @param[in]   size_t size   The number of bytes to be sent starting form the buffer.
 *  @param[in]   uint8_t encoding The encoding format for Host communication (HDLC/JSON etc).
 *  @return      None.
 *  @constraints This should be the called only after ::Host_IO_Init() has been called.
 *  @reeentrant  No
 * =================================================================== */
void Host_IO_Send(uint8_t *pMsg, size_t size, uint8_t encoding);

/* ===================================================================
 *  @brief       Function to check Rx and process received bytes and (re)enable UART Rx.
 *  @details     This function will check if UART RX is active and if found inactive will enable it.
 *  @param[in]   host_cmd_proc_fn_t process_host_command The function to process the user defined payload.
 *  @param[in]   uint8_t encoding The encoding format for Host communication (HDLC/JSON etc).
 *  @return      void.
 *  @constraints This should be the called only after ::Host_IO_Init() has been called.
 *  @reeentrant  No
 * =================================================================== */
void Host_IO_Receive(host_cmd_proc_fn_t process_host_command, uint8_t encoding);

#endif // HOST_IO_UART_H_
