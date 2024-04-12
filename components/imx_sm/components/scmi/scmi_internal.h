/*
** ###################################################################
**
** Copyright 2023 NXP
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

#ifndef SCMI_INTERNAL_H
#define SCMI_INTERNAL_H

/*!
 * @addtogroup scmi_proto
 * @{
 */

/*!
 * @file
 * @brief Header file containing internal functions of the client-side API for
 * the System Control and Management Interface (SCMI).
 */

/* Includes */

#include <stdlib.h>

/* Defines */

/*!
 * @name SCMI protocol message IDs
 */
/** @{ */
/*! Base protocol */
#define SCMI_PROTOCOL_BASE         0x10U
/*! Power domain management protocol */
#define SCMI_PROTOCOL_POWER        0x11U
/*! System power management protocol */
#define SCMI_PROTOCOL_SYS          0x12U
/*! Performance domain management protocol */
#define SCMI_PROTOCOL_PERF         0x13U
/*! Clock management protocol */
#define SCMI_PROTOCOL_CLOCK        0x14U
/*! Sensor management protocol */
#define SCMI_PROTOCOL_SENSOR       0x15U
/*! Reset domain management protocol */
#define SCMI_PROTOCOL_RESET        0x16U
/*! Voltage domain management protocol */
#define SCMI_PROTOCOL_VOLTAGE      0x17U
/*! Pin control protocol */
#define SCMI_PROTOCOL_PINCTRL      0x19U
/*! LM management protocol */
#define SCMI_PROTOCOL_LMM          0x80U
/*! BBM management protocol */
#define SCMI_PROTOCOL_BBM          0x81U
/*! CPU management protocol */
#define SCMI_PROTOCOL_CPU          0x82U
/*! FuSa protocol */
#define SCMI_PROTOCOL_FUSA         0x83U
/*! Misc protocol */
#define SCMI_PROTOCOL_MISC         0x84U
/** @} */

/*! Macro to get upper 32 bits of a 64-bit value */
#define SCMI_UINT64_H(X)        ((uint32_t)((((uint64_t) (X)) >> 32U) & 0x0FFFFFFFFULL))

/*! Macro to get lower 32 bits of a 64-bit value */
#define SCMI_UINT64_L(X)        ((uint32_t)(((uint64_t) (X)) & 0x0FFFFFFFFULL))

/*! Critical section lock callout */
#define SCMI_A2P_LOCK(lock)

/*! Critical section unlock callout */
#define SCMI_A2P_UNLOCK(lock)

/*! Critical section lock callout for notification functions */
#define SCMI_P2A_LOCK(lock)

/*! Critical section lock callout for notification functions */
#define SCMI_P2A_UNLOCK(lock)

/* Types */

/*!
 * SCMI message with status
 */
typedef struct
{
    /*! Message header */
    uint32_t header;
    /*! Return status */
    int32_t status;
} msg_status_t;

/* Functions */

/*!
 * @name SCMI internal functions
 * @{
 */

/*!
 * Init buffer for exchanging a message.
 *
 * @param[in]     channel Channel for comms
 * @param[out]    msg     Pointer to return payload header address
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_INVALID_PARAMETERS: if the buffer address is incorrectly
 *   configured.
 */
int32_t SCMI_BufInit(uint32_t channel, void **msg);

/*!
 * Init constant buffer for exchanging a message.
 *
 * @param[in]     channel Channel for comms
 * @param[out]    msg     Pointer to return payload header address
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Same as SCMI_BufInit() except returned pointer is constant.
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_INVALID_PARAMETERS: if the buffer address is incorrectly
 *   configured.
 */
int32_t SCMI_BufInitC(uint32_t channel, const void **msg);

/*!
 * Get the payload header address.
 *
 * @param[in]     channel Channel for comms
 *
 * Returns the address of the payload header.

 * @return Returns the address (NULL = failure).
 */
void *SCMI_HdrAddrGet(uint32_t channel);

/*!
 * Send A2P command.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in]     protocolId  Protocol ID
 * @param[in]     messageId   Message ID
 * @param[in]     len         Length of buffer to send
 * @param[out]    header      Pointer to return header value
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Send a message from agent to platform (A2P). Calls the transport to
 * send the buffer. Blocks until the channel is free to send. The \a
 * channel parameter should be an A2P channel. The \a len parameter is
 * the size in bytes of the payload + header.
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_INVALID_PARAMETERS: if the buffer address is incorrectly
 *   configured.
 * - ::SCMI_ERR_OUT_OF_RANGE: if the channel is incorrectly configured.
 * - ::SCMI_ERR_PROTOCOL_ERROR: if the message is too big.
 */
int32_t SCMI_A2pTx(uint32_t channel, uint32_t protocolId,
    uint32_t messageId, uint32_t len, uint32_t *header);

/*!
 * Receive A2P response.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in]     minLen      Minimum length of response
 * @param[in]     header      Expected response header
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Receive a response message from an A2P message sent via SCMI_A2pTx().
 * Calls the transport to receive the buffer. Blocks until the response
 * is available. The \a channel parameter should be the A2P channel used
 * to send the command. The \a minLen is the minimum size message in bytes
 * expected including the payload + header. The \a header value should be
 * the one returned by SCMI_A2pTx().
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_INVALID_PARAMETERS: if the buffer address is incorrectly
 *   configured.
 * - ::SCMI_ERR_OUT_OF_RANGE: if the channel is incorrectly configured.
 * - ::SCMI_ERR_PROTOCOL_ERROR: if the header doesn't match or if the
 *   return message is too small.
 * - Otherwise, the status value contained in the response message.
 */
int32_t SCMI_A2pRx(uint32_t channel, uint32_t minLen, uint32_t header);

/*!
 * Receive P2A message.
 *
 * @param[in]     channel     P2A channel for comms
 * @param[in]     protocolId  Expected protocol ID
 * @param[in]     messageId   Expected message ID
 * @param[in]     minLen      Minimum length of message
 * @param[out]    header      Pointer to return header value
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Receive a message sent by the platform to the agent (P2A). Calls the
 * transport to receive the buffer. Blocks until the message is available.
 * The \a channel parameter should be a P2A channel. The \a protocolId and
 * \a messageId should be the expected values. The \a minLen is the minimum
 * size message in bytes expected including the payload + header.
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_INVALID_PARAMETERS: if the buffer address is incorrectly
 *   configured.
 * - ::SCMI_ERR_OUT_OF_RANGE: if the channel is incorrectly configured.
 * - ::SCMI_ERR_PROTOCOL_ERROR: if the header doesn't match or if the
 *   received message is too small.
 */
int32_t SCMI_P2aRx(uint32_t channel, uint32_t protocolId,
    uint32_t messageId, uint32_t minLen, uint32_t *header);

/*!
 * Send P2A response.
 *
 * @param[in]     channel     P2A channel for comms
 * @param[in]     len         Length of buffer to send
 * @param[in]     header      Return header value
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Send a response to a P2A message received via SCMI_P2aRx(). Calls the
 * transport to send the buffer. Blocks until the channel is free to send.
 * The \a channel parameter should be the P2A channel the message was
 * received on. The \a len parameter is the size in bytes of the payload +
 * header.
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_INVALID_PARAMETERS: if the buffer address is incorrectly
 *   configured.
 * - ::SCMI_ERR_OUT_OF_RANGE: if the channel is incorrectly configured.
 * - ::SCMI_ERR_PROTOCOL_ERROR: if the message is too big.
 */
int32_t SCMI_P2aTx(uint32_t channel, uint32_t len, uint32_t header);

/*!
 * Memory copy.
 *
 * @param[out]    dst     Destination pointer
 * @param[in]     src     Source pointer
 * @param[in]     len     Length to copy
 *
 * This function copies a memory block from \a src to \a dst.
 */
void SCMI_MemCpy(uint8_t *dst, const uint8_t *src, uint32_t len);

/*!
 * Bounded string copy.
 *
 * @param[out]    dst     Destination pointer
 * @param[in]     src     Source pointer
 * @param[in]     maxLen  Max length to copy
 *
 * This function copies a string from \a src to \a dst. The copy will
 * not exceed \a maxLen.
 */
void SCMI_StrCpy(uint8_t *dst, const uint8_t *src, uint32_t maxLen);

/** @} */

#endif /* SCMI_INTERNAL_H */

/** @} */

