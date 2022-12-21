/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
* @file data_format_hdlc.h
* @brief The data_format_hdlc.h file contains the Host interface definitions and configuration.
*/

#ifndef DATA_FORMAT_HDLC_H_
#define DATA_FORMAT_HDLC_H_

/*******************************************************************************
 * Standard C Includes
 ******************************************************************************/
#include <stdint.h>

/*******************************************************************************
 * ISSDK Includes
 ******************************************************************************/
#include "host_io_uart.h"

/*******************************************************************************
 * Types
 ******************************************************************************/
/*! @brief States for receiving a packet */
enum
{ /* Receiver state: Waiting for a packet marker */
  HOST_RX_STATE_WAITFORPACKETMARKER,
  /* Receiver state: Receiving data payload */
  HOST_RX_STATE_GETTINGPACKETDATA
};

/*******************************************************************************
 * APIs
 ******************************************************************************/
/* ===================================================================
 *  @brief       Function to handle incomming HDLC encoded bytes form the Host over UART.
 *  @details     This function will be called on receipt of every UART Byte
 *               and will do the HDLC combination to create a Host Message.
 *  @param[in]   uint8_t c The character in the UART payload.
 *  @param[in]   host_rx_packet_t *pHostRxPkt The Host Packet context structure.
 *  @return      bool Success/Failure.
 *  @constraints This should be the called only after DEBUG/UART has been initialized.
 *  @reeentrant  No
 * =================================================================== */
bool HDLC_Process_Rx_Byte(uint8_t c, host_rx_packet_t *pHostRxPkt);

/* ===================================================================
 *  @brief       Function to format bytes for HDLC to be sent to Host over UART.
 *  @details     This function will encode a Host Protocol formatted Message to be sent to Host over UART.
 *               The encoding adds a start and stop markers and inserts escape sequences for markers inside the packet.
 *  @param[in]   uint8_t *pbuffer The handle to the input buffer containing the Host message.
 *  @param[in]   uint8_t *pMsg    The handle to the output buffer containing the formatted Host message.
 *  @param[in]   size_t size     The number of bytes to be sent starting form the buffer.
 *  @return      size_t          Length of the encoded message.
 *  @constraints This should be the called only after DEBUG/UART has been initialized.
 *  @reeentrant  No
 * =================================================================== */
size_t HDLC_Process_Tx_Msg(const uint8_t *pBuffer, uint8_t *pMsg, size_t size);

#endif // DATA_FORMAT_HDLC_H_
