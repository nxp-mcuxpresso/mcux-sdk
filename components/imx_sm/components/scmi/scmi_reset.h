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

#ifndef SCMI_RESET_H
#define SCMI_RESET_H

/*!
 * @addtogroup scmi_proto_reset
 * @{
 */

/*!
 * @file
 * @brief Header file containing the client-side API for the System Control and
 * Management Interface (SCMI) reset protocol.
 */

/* Defines */

/*!
 * @name SCMI reset protocol message IDs
 */
/** @{ */
/*! Get reset domain attributes */
#define SCMI_MSG_RESET_DOMAIN_ATTRIBUTES  0x3U
/*! Reset domain */
#define SCMI_MSG_RESET                    0x4U
/** @} */

/*!
 * @name SCMI max reset argument lengths
 */
/** @{ */
/*! Max length of the returned reset domain name */
#define SCMI_RESET_MAX_NAME  16U
/** @} */

/*!
 * @name SCMI reset architectural reset states
 */
/** @{ */
/*! Max length of the returned clock name */
#define SCMI_RESET_ARCH_COLD  0x00000000U
/** @} */

/* Macros */

/*!
 * @name SCMI reset protocol attributes
 */
/** @{ */
/*! Number of reset domains */
#define SCMI_RESET_PROTO_ATTR_NUM_RESETS(x)  (((x) & 0xFFFFU) >> 0U)
/** @} */

/*!
 * @name SCMI reset attributes
 */
/** @{ */
/*! Asynchronous reset support */
#define SCMI_RESET_ATTR_ASYNC(x)          (((x) & 0x80000000U) >> 31U)
/*! Reset notifications support */
#define SCMI_RESET_ATTR_NOTIFICATIONS(x)  (((x) & 0x40000000U) >> 30U)
/*! Extended reset domain name */
#define SCMI_RESET_ATTR_EXT_NAME(x)       (((x) & 0x20000000U) >> 29U)
/** @} */

/*!
 * @name SCMI reset flags
 */
/** @{ */
/*! Async flag */
#define SCMI_RESET_FLAGS_ASYNC(x)   (((x) & 0x1U) << 2U)
/*! Explicit signal */
#define SCMI_RESET_FLAGS_SIGNAL(x)  (((x) & 0x1U) << 1U)
/*! Autonomous Reset action */
#define SCMI_RESET_FLAGS_AUTO(x)    (((x) & 0x1U) << 0U)
/** @} */

/*!
 * @name SCMI architectural reset states
 */
/** @{ */
/*! Architectural reset */
#define SCMI_RESET_STATE_ARCH(x)  (((x) & 0x1U) << 31U)
/** @} */

/* Functions */

/*!
 * Get protocol version.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[out]    version  Protocol version. For this revision of the
 *                         specification, this value must be 0x30001
 *
 * On success, this function returns the version of this protocol. For this
 * version of the specification, the value returned must be 0x30001, which
 * corresponds to version 3.1. See section 4.8.2.1 PROTOCOL_VERSION in the
 * [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_ResetProtocolVersion(uint32_t channel, uint32_t *version);

/*!
 * Get protocol attributes.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[out]    attributes  Protocol attributes:<BR>
 *                            Bits[31:16] Reserved, must be zero.<BR>
 *                            Bits[15:0] Number of reset domains
 *
 * This function returns the implementation details associated with this
 * protocol. See section 4.8.2.3 PROTOCOL_ATTRIBUTES in the
 * [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_RESET_PROTO_ATTR_NUM_RESETS() - Number of reset domains
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_ResetProtocolAttributes(uint32_t channel,
    uint32_t *attributes);

/*!
 * Get protocol message attributes.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in]     messageId   Message ID of the message
 * @param[out]    attributes  Message attributes. Flags that are associated
 *                            with a specific function in the protocol.<BR>
 *                            For all functions in this protocol, this
 *                            parameter has a value of 0
 *
 * On success, this function returns the implementation details associated with
 * a specific message in this protocol. An example message ID is
 * ::SCMI_MSG_RESET_DOMAIN_ATTRIBUTES. See section 4.8.2.4
 * PROTOCOL_MESSAGE_ATTRIBUTES in the [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: in case the message is implemented and available to
 *   use.
 * - ::SCMI_ERR_NOT_FOUND: if the message identified by \a messageId is
 *   invalid or not provided by this platform implementation.
 */
int32_t SCMI_ResetProtocolMessageAttributes(uint32_t channel,
    uint32_t messageId, uint32_t *attributes);

/*!
 * Get reset domain attributes.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in]     domainId    Identifier for the reset domain
 * @param[out]    attributes  Domain attributes:<BR>
 *                            Bit[31] Asynchronous reset support.<BR>
 *                            Set to 1 if this domain can be reset
 *                            asynchronously.<BR>
 *                            Set to 0 if this domain can only be reset
 *                            synchronously.<BR>
 *                            Bit[30] Reset notifications support.<BR>
 *                            Set to 1 if reset notifications are supported for
 *                            this domain.<BR>
 *                            Set to 0 if reset notifications are not supported
 *                            for this domain.<BR>
 *                            Bit[29] Extended reset domain name.<BR>
 *                            If set to 1, the reset domain name is greater
 *                            than 16 bytes.<BR>
 *                            If set to 0, extended reset domain name is not
 *                            supported.<BR>
 *                            Bits[28:0] Reserved, must be zero
 * @param[out]    latency     Maximum time (in uS) required to reset. A value
 *                            of 0xFFFFFFFF indicates this field is not
 *                            supported by the platform
 * @param[out]    name        Null-terminated ASCII string of up to 16 bytes in
 *                            length describing the reset domain name. When
 *                            Bit[29] of attributes field is set to 1, this
 *                            field contains the lower 15 bytes of the NULL
 *                            terminated reset domain name
 *
 * This function returns attributes of the reset domain specified in the
 * function. The max name length is ::SCMI_MSG_RESET. See section 4.8.2.5
 * RESET_DOMAIN_ATTRIBUTES in the [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_RESET_ATTR_ASYNC() - Asynchronous reset support
 * - ::SCMI_RESET_ATTR_NOTIFICATIONS() - Reset notifications support
 * - ::SCMI_RESET_ATTR_EXT_NAME() - Extended reset domain name
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if valid reset domain attributes were returned.
 * - ::SCMI_ERR_NOT_FOUND: if domainId pertains to a non-existent domain.
 */
int32_t SCMI_ResetDomainAttributes(uint32_t channel, uint32_t domainId,
    uint32_t *attributes, uint32_t *latency, uint8_t *name);

/*!
 * Reset domain.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in]     domainId    Identifier for the reset domain
 * @param[in]     flags       Reset flags:<BR>
 *                            This parameter allows the agent to specify
 *                            additional conditions and requirements specific
 *                            to the request, and has the following format:<BR>
 *                            Bits[31:3] Reserved, must be zero.<BR>
 *                            Bit[2] Async flag. Only valid if Bit[0] is set to
 *                            1.<BR>
 *                            Set to 1 if the reset must complete
 *                            asynchronously.<BR>
 *                            Set to 0 if the reset must complete
 *                            synchronously.<BR>
 *                            Bit[1] Explicit signal. This flag is ignored when
 *                            Bit[0] is set to 1.<BR>
 *                            Set to 1 to explicitly assert reset signal.<BR>
 *                            Set to 0 to explicitly de-assert reset
 *                            signal.<BR>
 *                            Bit[0] Autonomous Reset action.<BR>
 *                            Set to 1 if the reset must be performed
 *                            autonomously by the platform.<BR>
 *                            Set to 0 if the reset signal shall be explicitly
 *                            asserted and de-asserted by the caller
 * @param[in]     resetState  The reset state being requested. The format of
 *                            this parameter is specified in Table 19
 *
 * This function allows an agent to reset the specified reset domain. The SM
 * only support synchronous reset requests. The platform might need to ensure
 * that the domain and all dependent logic have reached a state of quiescence
 * before performing the actual reset, although this is not mandatory. See
 * section 4.8.2.6 RESET in the [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_RESET_FLAGS_ASYNC() - Async flag
 * - ::SCMI_RESET_FLAGS_SIGNAL() - Explicit signal
 * - ::SCMI_RESET_FLAGS_AUTO() - Autonomous Reset action
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the operation was successful.
 * - ::SCMI_ERR_NOT_FOUND: if the reset domain identified by domainId does
 *   not exist.
 * - ::SCMI_ERR_INVALID_PARAMETERS: if an illegal or unsupported reset state
 *   is specified or if the flags field is invalid.
 * - ::SCMI_ERR_GENERIC_ERROR: if the operation failed, for example if there
 *   are other active users of the reset domain.
 * - ::SCMI_ERR_DENIED: if the calling agent is not allowed to reset the
 *   specified reset domain.
 */
int32_t SCMI_Reset(uint32_t channel, uint32_t domainId, uint32_t flags,
    uint32_t resetState);

/*!
 * Negotiate the protocol version.
 *
 * @param[in]     channel  A2P channel for comms
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
 * 4.8.2.2 NEGOTIATE_PROTOCOL_VERSION in the [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the negotiated protocol version is supported by the
 *   platform. All commands, responses, and notifications post successful
 *   return of this command must comply with the negotiated version.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the protocol version is not supported.
 */
int32_t SCMI_ResetNegotiateProtocolVersion(uint32_t channel,
    uint32_t version);

#endif /* SCMI_RESET_H */

/** @} */

