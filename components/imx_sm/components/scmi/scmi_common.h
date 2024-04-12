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

#ifndef SCMI_COMMON_H
#define SCMI_COMMON_H

/*!
 * @addtogroup scmi_proto
 * @{
 */

/*!
 * @file
 * @brief Header file containing the client-side API for the System Control and
 * Management Interface (SCMI) common functions.
 */

/* Defines */

/*! Max payload length */
#define SCMI_PAYLOAD_LEN                        100U

/*! Calc number of array elements */
#define SCMI_ARRAY(X, Y)                        ((SCMI_PAYLOAD_LEN - (X)) / sizeof(Y))

/*!
 * @name SCMI common protocol message IDs
 */
/** @{ */
/*! Get protocol version */
#define SCMI_MSG_PROTOCOL_VERSION               0x0U
/*! Get protocol attributes */
#define SCMI_MSG_PROTOCOL_ATTRIBUTES            0x1U
/*! Get protocol message attributes */
#define SCMI_MSG_PROTOCOL_MESSAGE_ATTRIBUTES    0x2U
/*! Negotiate the protocol version */
#define SCMI_MSG_NEGOTIATE_PROTOCOL_VERSION     0x10U
/** @} */

/*!
 * @anchor SCMI_STATUS
 * @name SCMI error codes
 */
/** @{ */
#define SCMI_ERR_SUCCESS             (0)     /*!< Successful completion of the command. */
#define SCMI_ERR_NOT_SUPPORTED       (-1)    /*!< The command or feature is not supported
                                                  or is supported but not within the calling
                                                  agents view of the platform. */
#define SCMI_ERR_INVALID_PARAMETERS  (-2)    /*!< One or more parameters passed to the command
                                                  are invalid or beyond legal limits. */
#define SCMI_ERR_DENIED              (-3)    /*!< The caller is not permitted to perform the
                                                  specific action, such as accessing a resource
                                                  or feature that it is not allowed to use. */
#define SCMI_ERR_NOT_FOUND           (-4)    /*!< The entity that is being accessed does not exist. */
#define SCMI_ERR_OUT_OF_RANGE        (-5)    /*!< Requested settings are outside the legal range */
#define SCMI_ERR_BUSY                (-6)    /*!< The platform is out of resources and thus unable
                                                  to process a command. */
#define SCMI_ERR_COMMS_ERROR         (-7)    /*!< The message could not be correctly transmitted. */
#define SCMI_ERR_GENERIC_ERROR       (-8)    /*!< The command failed to be processed owing to an
                                                  unspecified fault within the platform. */
#define SCMI_ERR_HARDWARE_ERROR      (-9)    /*!< A hardware error occurred in a platform
                                                  component during execution of a command. */
#define SCMI_ERR_PROTOCOL_ERROR      (-10)   /*!< Returned when the receiver detects that the
                                                  caller has violated the protocol specification. */
#define SCMI_ERR_IN_USE              (-11)   /*!< The resource is currently in use by the platform
                                                  or another agent and cannot be operated upon. */
#define SCMI_ERR_ABORT_ERROR         (-128)  /*!< The message was aborted. */
#define SCMI_ERR_CRC_ERROR           (-129)  /*!< The received message failed a CRC check. */
#define SCMI_ERR_MISSING_PARAMETERS  (-130)  /*!< One or more parameters is missing. */
#define SCMI_ERR_POWER               (-131)  /*!< Power domain dependency violation. */
#define SCMI_ERR_TEST                (-132)  /*!< Test error. Generally lack of an expected error. */
#define SCMI_ERR_SEQ_ERROR           (-133)  /*!< Sequence error. The message sent or recv. did not
                                                  include the required sequence number. */

/** @} */

/* Types */

/*!
 * SCMI sensor statistics area info
 */
typedef struct
{
    /*! Lower 32-bits of the address */
    uint32_t low;
    /*! Upper 32-bits of the address */
    uint32_t high;
    /*! Size in byes */
    uint32_t len;
} scmi_statistics_t;

/* Functions */

/*!
 * @name SCMI common functions
 * @{
 */

/*!
 * Set abort state.
 *
 * @param[in]     channel  Channel for comms
 * @param[in]     state    True to assert abort
 *
 * This function asserts abort on the specified channel. For most MB
 * implementations this asserts for the entire mailbox, not just the
 * specified channel. After asserting, when all responses have come
 * back then call to deassert befire sending making another call.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_AbortSet(uint32_t channel, bool state);

/*!
 * Get protocol version.
 *
 * @param[in]     channel     Channel for comms
 * @param[in]     protocolId  Protocol ID
 * @param[out]    version     Returned protocol version
 *
 * This function returns the version of this protocol.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_ProtocolVersion(uint32_t channel, uint32_t protocolId,
    uint32_t *version);

/*!
 * Get protocol attributes.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in]     protocolId  Protocol ID
 * @param[out]    attributes  Varies by protocol
 *
 * This function returns the implementation details that are associated with
 * this protocol.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_ProtocolAttributes(uint32_t channel, uint32_t protocolId,
    uint32_t *attributes);

/*!
 * Get protocol message attributes.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in]     protocolId  Protocol ID
 * @param[in]     messageId   Message ID of the message
 * @param[out]    attributes  Flags that are associated with a specific command
 *                            in the protocol
 *
 * On success, this function returns the implementation details associated with
 * a specific message in this protocol.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: in case the message is implemented and available to
 *   use.
 * - ::SCMI_ERR_NOT_FOUND: if the message identified by \a messageId is not
 *   provided by this platform implementation.
 */
int32_t SCMI_ProtocolMessageAttributes(uint32_t channel,
    uint32_t protocolId, uint32_t messageId, uint32_t *attributes);

/*!
 * Negotiate the protocol version.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[in]     protocolId  Protocol ID
 * @param[in]     version  The negotiated protocol version the agent intends to
 *                         use
 *
 * This command is used to negotiate the protocol version that the agent
 * intends to use, if it does not support the version returned by the
 * SCMI_ProtocolVersion() function. There is no limit on the number of
 * negotiations which can be attempted by the agent. All commands, responses,
 * and notifications must comply with the protocol version which was last
 * negotiated successfully. Using protocol versions different from the version
 * returned by SCMI_ProtocolVersion() without successful negotiation is
 * considered best effort, and functionality is not guaranteed. See section
 * 4.2.2.2 NEGOTIATE_PROTOCOL_VERSION in the [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the negotiated protocol version is supported by the
 *   platform. All commands, responses, and notifications post successful
 *   return of this command must comply with the negotiated version.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the protocol version is not supported.
 */
int32_t SCMI_NegotiateProtocolVersion(uint32_t channel, uint32_t protocolId,
    uint32_t version);

/*!
 * Check P2A channel state.
 *
 * @param[in]     channel     P2A channel for comms
 * @param[out]    protocolId  Expected protocol ID
 * @param[out]    messageId   Expected message ID
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Checks if a message is pending on a P2A channel. If yes, returns the
 * message info \a protocolId and \a messageId so the appropriate function
 * can be called to receive the message. Does not block. Usually called by
 * the interrupt handler for the doorbell mechanism and the return info
 * used to call the protocol-specific handler.
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_PROTOCOL_ERROR: if no message is pending.
 * - ::SCMI_ERR_INVALID_PARAMETERS: if the buffer address is incorrectly
 *   configured.
 */
int32_t SCMI_P2aPending(uint32_t channel, uint32_t *protocolId,
    uint32_t *messageId);

/*!
 * Configure checking of sequence numbers for a channel.
 *
 * @param[in]     channel     P2A channel for comms
 * @param[in ]    enb         True = enable
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Note this only configures checking on a P2A channel. Checking
 * for A2P channels is determined by the SM configuration. The
 * default is for checking to be disabled.
 *
 * If checking is enabled, sequence numbers may need to be saved
 * and restored if state will be lost as is common with some
 * forms of suspend/resume. See SCMI_SequenceSave() and
 * SCMI_SequenceRestore().
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_INVALID_PARAMETERS: if the channel is invalid.
 */
int32_t SCMI_SequenceConfig(uint32_t channel, bool enb);

/*!
 * Save sequence numbers for all channels.
 *
 * Sequence numbers must be saved/restored if the agent will
 * lose state outside of the context of an SM-driven reset.
 *
 * @param[out]    sequences   Array to save sequences
 */
void SCMI_SequenceSave(uint32_t *sequences);

/*!
 * Restore sequence numbers for all channels.
 *
 * Sequence numbers must be saved/restored if the agent will
 * lose state outside of the context of an SM-driven reset.
 *
 * @param[in]     sequences   Array of sequences to load
 */
void SCMI_SequenceRestore(const uint32_t *sequences);

/** @} */

#endif /* SCMI_COMMON_H */

/** @} */

