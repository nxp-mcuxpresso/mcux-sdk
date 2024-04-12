/*
** ###################################################################
**
** Copyright 2023-2024 NXP
**
** Redistribution and use in source and binary forms, with or without modification,
** are permitted provided that the following conditions are met:
**
** o Redistributions of source code must retain the above copyright notice, this list
**   of conditions and the following disclaimer.
**
** o Redistributions in binary form must reproduce the above copyright notice, this
**   list of conditions and the following disclaimer in the documentation and/or
**   other materials provided with the distribution.
**
** o Neither the name of the copyright holder nor the names of its
**   contributors may be used to endorse or promote products derived from this
**   software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
** ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
** (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
** ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**
** ###################################################################
*/

#ifndef SMT_H
#define SMT_H

/*!
 * @addtogroup smt_proto
 * @{
 */

/*!
 * @file
 * @brief Header file containing the client-side public API for the Shared Memory
 * Transport (SMT) as defined by SCMI v3.2 spec.
 */

/* Includes */

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/* Defines */

/*! SMT max number of channels */
#define SMT_MAX_CHN   24U

/*! SMT buffer size */
#define SMT_BUFFER_SIZE     128U
/*! SMT buffer header size */
#define SMT_BUFFER_HEADER   24U
/*! SMT buffer payload size */
#define SMT_BUFFER_PAYLOAD  (SMT_BUFFER_SIZE - SMT_BUFFER_HEADER - 4U)

/*!
 * @name SMT error codes
 */
/** @{ */
#define SMT_ERR_SUCCESS              (0)     /*!< Successful completion of the command. */
#define SMT_ERR_INVALID_PARAMETERS   (-2)    /*!< One or more parameters passed to the command
                                                  are invalid or beyond legal limits. */
#define SMT_ERR_COMMS_ERROR          (-7)    /*!< The message could not be correctly transmitted. */
#define SMT_ERR_PROTOCOL_ERROR       (-10)   /*!< Returned when the receiver detects that the
                                                  caller has violated the protocol specification. */
#define SMT_ERR_TIMEOUT_ERROR        (-127)  /*!< The transmission timed out. */
#define SMT_ERR_CRC_ERROR            (-128)  /*!< The received message failed a CRC check. */
/** @} */

/*!
 * @name SMT CRC types
 *
 * Types of CRC algorithms that can be configured for a channel.
 */
/** @{ */
/*! No CRC */
#define SMT_CRC_NONE    0U
/*! Simple and fast 32-bit exclusive-OR sum */
#define SMT_CRC_XOR     1U
/*! J1850 standard CRC */
#define SMT_CRC_J1850   2U
/*! CRC32 standard CRC */
#define SMT_CRC_CRC32   3U
/** @} */

/* Functions */

/*!
 * Configure an SMT channel.
 *
 * @param[in]     smtChannel  Channel for comms
 * @param[in]     mbInst      Mailbox instance
 * @param[in]     mbDoorbell  Doorbell index
 * @param[in]     sma         Shared memory address
 *
 * This function configures an SMT channel for client use. The \a
 * smtChannel parameter is the channel to configure. It is then used
 * for following calls to the SCMI API.
 *
 * The \a mbInst and \a mbDoorbell parameters depend on the kind of
 * mailbox used. For an MU, \a mbInst is the index into the SDK MU_BASE_PTRS
 * array. The \a mbDoorbell is the MU GI to use to trigger an interrupt
 * response.
 *
 * The \a sma parameter is the address of the shared memory area. For MUs with
 * an internal 1K SRAM, a value of 0 indicates to use that (128K per channel
 * spaced in order of doorbell).
 *
 * Note the SYstem Manager (SM) configuration will determine which MU is used
 * for a client and which doorbells are associated with A2P channels, P2A
 * notification channels, and FuSa notification channels.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SMT_ChannelConfig(uint32_t smtChannel, uint8_t mbInst,
    uint8_t mbDoorbell, uint32_t sma);

/*!
 * Get SMT buffer address.
 *
 * @param[in]     smtChannel  Channel for comms
 *
 * Returns the address of the header+payload section of the SMT shared
 * memory area.
 *
 * @return Returns the address of the header+payload section.
 */
void *SMT_HdrAddrGet(uint32_t smtChannel);

/*!
 * SMT wait for free.
 *
 * @param[in]     smtChannel  Channel for comms
 *
 * Blocks until the SMT channel becomes free.
 *
 * @return Returns true if the channel is free.
 */
bool SMT_ChannelFree(uint32_t smtChannel);

/*!
 * Set abort state.
 *
 * @param[in]     smtChannel  Channel for comms
 * @param[in]     state       True is assert abort
 *
 * This function asserts abort on the specified channel. For most MB
 * implementations this asserts for the entire mailbox, not just the
 * specified channel. After asserting, when all responses have come
 * back then call to deassert befire sending making another call.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SMT_AbortSet(uint32_t smtChannel, bool state);

/*!
 * Send an SMT message.
 *
 * @param[in]     smtChannel  Channel for comms
 * @param[in]     len         Length of buffer to send
 * @param[in]     callee      Communication direction
 * @param[in]     compInt     Caller wants a completion interrupt
 *
 * This function sends a message via SMT. The data should already be written
 * into the buffer returned by SMT_HdrAddrGet(). The \a len parameter is the
 * buffer length (inc. header) in bytes.
 *
 * The \a callee parameter indicates the channel direction. If false, then
 * this channel is used for A2P communication and a send (Tx) is a message
 * initiated by the caller and transitions the channel to busy. If true,
 * then this channel is used for P2A communication and a send (Tx) is in
 * response to a call and transitions the channel to free.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SMT_Tx(uint32_t smtChannel, uint32_t len, bool callee,
    bool compInt);

/*!
 * Receive an SMT message.
 *
 * @param[in]     smtChannel  Channel for comms
 * @param[in]     len         Length of buffer to send
 * @param[in]     callee      Communication direction
 *
 * This function receives a message via SMT. The data can then be accessed
 * at the buffer returned by SMT_HdrAddrGet(). The \a len parameter is the
 * buffer length (inc. header) in bytes.
 *
 * The \a callee parameter indicates the channel direction. If false, then
 * this channel is used for A2P communication and a receive (Rx) will
 * wait for the channel to be free indicating the SM has written a
 * response message. If true, then this channel is used for P2A communication
 * will wait for the channel to become busy indicating the SM has
 * initiated a message exchange.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SMT_Rx(uint32_t smtChannel, uint32_t *len, bool callee);

#endif /* SMT_H */

/** @} */

