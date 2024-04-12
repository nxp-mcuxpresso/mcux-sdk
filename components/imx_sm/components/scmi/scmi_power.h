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

#ifndef SCMI_POWER_H
#define SCMI_POWER_H

/*!
 * @addtogroup scmi_proto_power
 * @{
 */

/*!
 * @file
 * @brief Header file containing the client-side API for the System Control and
 * Management Interface (SCMI) power protocol.
 */

/* Defines */

/*!
 * @name SCMI power protocol message IDs
 */
/** @{ */
/*! Get power domain attributes */
#define SCMI_MSG_POWER_DOMAIN_ATTRIBUTES  0x3U
/*! Set power state */
#define SCMI_MSG_POWER_STATE_SET          0x4U
/*! Get power state */
#define SCMI_MSG_POWER_STATE_GET          0x5U
/** @} */

/*!
 * @name SCMI max power argument lengths
 */
/** @{ */
/*! Max length of the returned power domain name */
#define SCMI_POWER_MAX_NAME  16U
/** @} */

/*!
 * @name SCMI power domain states
 */
/** @{ */
/*! On */
#define SCMI_POWER_DOMAIN_STATE_ON   0x00000000U
/*! Off, state lost */
#define SCMI_POWER_DOMAIN_STATE_OFF  0x40000000U
/** @} */

/* Macros */

/*!
 * @name SCMI power protocol attributes
 */
/** @{ */
/*! Number of power domains */
#define SCMI_POWER_PROTO_ATTR_NUM_DOMAINS(x)  (((x) & 0xFFFFU) >> 0U)
/** @} */

/*!
 * @name SCMI power domain attributes
 */
/** @{ */
/*! Power state change notifications support */
#define SCMI_POWER_ATTR_CHANGE(x)      (((x) & 0x80000000U) >> 31U)
/*! Power state asynchronous support */
#define SCMI_POWER_ATTR_ASYNC(x)       (((x) & 0x40000000U) >> 30U)
/*! Power state synchronous support */
#define SCMI_POWER_ATTR_SYNC(x)        (((x) & 0x20000000U) >> 29U)
/*! Power state change requested notifications support */
#define SCMI_POWER_ATTR_CHANGE_REQ(x)  (((x) & 0x10000000U) >> 28U)
/*! Extended power domain name */
#define SCMI_POWER_ATTR_EXT_NAME(x)    (((x) & 0x8000000U) >> 27U)
/** @} */

/*!
 * @name SCMI power state set flags
 */
/** @{ */
/*! Async flag */
#define SCMI_POWER_FLAGS_ASYNC(x)  (((x) & 0x1U) << 0U)
/** @} */

/* Functions */

/*!
 * Get protocol version.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[out]    version  Protocol version. For this revision of the
 *                         specification, this value must be 0x30001
 *
 * On success, this function returns the Protocol version. For this version of
 * the specification, the return value must be 0x30001, which corresponds to
 * version 3.1. See section 4.3.2.1 PROTOCOL_VERSION in the
 * [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_PowerProtocolVersion(uint32_t channel, uint32_t *version);

/*!
 * Get protocol attributes.
 *
 * @param[in]     channel                A2P channel for comms
 * @param[out]    attributes             Protocol attributes:<BR>
 *                                       Bits[31:16] Reserved, must be
 *                                       zero.<BR>
 *                                       Bits[15:0] Number of power domains
 * @param[out]    statisticsAddressLow   Low address: The lower 32 bits of the
 *                                       physical address where the statistics
 *                                       shared memory region is located
 * @param[out]    statisticsAddressHigh  High address: The upper 32 bits of the
 *                                       physical address where the statistics
 *                                       shared memory region is located
 * @param[out]    statisticsLen          The length in bytes of the statistics
 *                                       shared memory region. A value of 0 in
 *                                       this field indicates that the platform
 *                                       does not support the statistics shared
 *                                       memory region
 *
 * This function returns the implementation details associated with this
 * protocol. See section 4.3.2.3 PROTOCOL_ATTRIBUTES in the
 * [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_POWER_PROTO_ATTR_NUM_DOMAINS() - Number of power domains
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_PowerProtocolAttributes(uint32_t channel, uint32_t *attributes,
    uint32_t *statisticsAddressLow, uint32_t *statisticsAddressHigh,
    uint32_t *statisticsLen);

/*!
 * Get protocol message attributes.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in]     messageId   Message ID of the message
 * @param[out]    attributes  Message attributes. Flags that are associated
 *                            with a specific function in the protocol.<BR>
 *                            In the current version of the specification, this
 *                            value is always 0
 *
 * On success, this function returns the implementation details associated with
 * a specific message in this protocol. An example message ID is
 * ::SCMI_MSG_POWER_DOMAIN_ATTRIBUTES. See section 4.3.2.4
 * PROTOCOL_MESSAGE_ATTRIBUTES in the [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: in case the message is implemented and available to
 *   use.
 * - ::SCMI_ERR_NOT_FOUND: if the message identified by \a messageId is
 *   invalid or not implemented.
 */
int32_t SCMI_PowerProtocolMessageAttributes(uint32_t channel,
    uint32_t messageId, uint32_t *attributes);

/*!
 * Get power domain attributes.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in]     domainId    Identifier for the domain. Domain identifiers are
 *                            limited to 16 bits, and the upper 16 bits of this
 *                            field are ignored by the platform
 * @param[out]    attributes  Domain attributes:<BR>
 *                            Bit[31] Power state change notifications
 *                            support.<BR>
 *                            Set to 1 if power state change notifications are
 *                            supported on this domain.<BR>
 *                            Set to 0 if power state change notifications are
 *                            not supported on this domain.<BR>
 *                            Bit[30] Power state asynchronous support.<BR>
 *                            Set to 1 if power state can be set
 *                            asynchronously.<BR>
 *                            Set to 0 if power state cannot be set
 *                            asynchronously.<BR>
 *                            Bit[29] Power state synchronous support.<BR>
 *                            Set to 1 if power state can be set
 *                            synchronously.<BR>
 *                            Set to 0 if power state cannot be set
 *                            synchronously.<BR>
 *                            Bit[28] Power state change requested
 *                            notifications support.<BR>
 *                            Set to 1 if power state change requested
 *                            notifications are supported on this domain.<BR>
 *                            Set to 0 if power state change requested
 *                            notifications are not supported on this
 *                            domain.<BR>
 *                            Bit[27] Extended power domain name.<BR>
 *                            If set to 1, the power domain name is greater
 *                            than 16 bytes.<BR>
 *                            If set to 0, extended power domain name is not
 *                            supported
 * @param[out]    name        Null-terminated ASCII string of up to 16 bytes in
 *                            length describing the power domain name. When
 *                            Bit[27] of attributes field is set to 1, this
 *                            field returns the NULL terminated lower 15 bytes
 *                            of the power domain name
 *
 * This function returns the attribute flags associated with a specific power
 * domain. Max name length is ::SCMI_POWER_MAX_NAME. See section 4.3.2.5
 * POWER_DOMAIN_ATTRIBUTES in the [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_POWER_ATTR_CHANGE() - Power state change notifications support
 * - ::SCMI_POWER_ATTR_ASYNC() - Power state asynchronous support
 * - ::SCMI_POWER_ATTR_SYNC() - Power state synchronous support
 * - ::SCMI_POWER_ATTR_CHANGE_REQ() - Power state change requested
 *   notifications support
 * - ::SCMI_POWER_ATTR_EXT_NAME() - Extended power domain name
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if valid power domain attributes are returned.
 * - ::SCMI_ERR_NOT_FOUND: if \a domainId pertains to a non-existent domain.
 */
int32_t SCMI_PowerDomainAttributes(uint32_t channel, uint32_t domainId,
    uint32_t *attributes, uint8_t *name);

/*!
 * Set power state.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in]     flags       Power set flags:<BR>
 *                            Bits[31:1] Reserved, must be zero.<BR>
 *                            Bit[0] Async flag.<BR>
 *                            Set to 1 if power transition must be done
 *                            asynchronously.<BR>
 *                            Set to 0 if power state transition must be done
 *                            synchronously.<BR>
 *                            The async flag is ignored for application
 *                            processor domains
 * @param[in]     domainId    Identifier for the power domain
 * @param[in]     powerState  Parameter identifying the power state of the
 *                            domain. Note platform-specific
 *
 * This function allows an agent to set the power state of a power domain. The
 * SM only supports synchronous transitions, except for AP power domains that
 * are always asynchronous. Each agent can set a power state and the results
 * are aggregated. Domain will be set to the minimum to satisfy all settings.
 * An example power state is ::SCMI_POWER_DOMAIN_STATE_ON. Note that if a power
 * domain contains CPUs, the reset vectors for those are latched on power up
 * and must be set first using SCMI_CpuResetVectorSet(). See section 4.3.2.6
 * POWER_STATE_SET in the [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_POWER_FLAGS_ASYNC() - Async flag
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: for a power domain that can only be set synchronously,
 *   this status is returned after the power domain has transitioned to the
 *   desired state. For a power domain that is managed asynchronously, this
 *   status is returned if the function parameters are valid, and the power
 *   state change has been scheduled.
 * - ::SCMI_ERR_NOT_FOUND: if the power domain identified by \a domainId does
 *   not exist.
 * - ::SCMI_ERR_INVALID_PARAMETERS: if the requested power state does not
 *   represent a valid state for the power domain that is identified by \a
 *   domainId.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the request is not supported.
 * - ::SCMI_ERR_DENIED: if the calling agent is not allowed to set the state
 *   of this power domain. An example would be if this power domain is
 *   exclusive to another agent.
 */
int32_t SCMI_PowerStateSet(uint32_t channel, uint32_t domainId,
    uint32_t flags, uint32_t powerState);

/*!
 * Get power state.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in]     domainId    Identifier for the power domain
 * @param[out]    powerState  Parameter identifying the power state of the
 *                            domain. Note platform-specific
 *
 * This function allows the calling agent to request the current power state of
 * a power domain. An example power state is ::SCMI_POWER_DOMAIN_STATE_OFF. See
 * section 4.3.2.7 POWER_STATE_GET in the [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the current power state is returned successfully.
 * - ::SCMI_ERR_NOT_FOUND: if \a domainId does not point to a valid power
 *   domain.
 */
int32_t SCMI_PowerStateGet(uint32_t channel, uint32_t domainId,
    uint32_t *powerState);

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
 * 4.3.2.2 NEGOTIATE_PROTOCOL_VERSION in the [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the negotiated protocol version is supported by the
 *   platform. All commands, responses, and notifications post successful
 *   return of this command must comply with the negotiated version.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the protocol version is not supported.
 */
int32_t SCMI_PowerNegotiateProtocolVersion(uint32_t channel,
    uint32_t version);

#endif /* SCMI_POWER_H */

/** @} */

