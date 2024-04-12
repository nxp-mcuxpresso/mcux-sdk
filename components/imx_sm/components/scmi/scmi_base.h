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

#ifndef SCMI_BASE_H
#define SCMI_BASE_H

/*!
 * @addtogroup scmi_proto_base
 * @{
 */

/*!
 * @file
 * @brief Header file containing the client-side API for the System Control and
 * Management Interface (SCMI) base protocol.
 */

/* Defines */

/*!
 * @name SCMI base protocol message IDs
 */
/** @{ */
/*! Get vendor identifier */
#define SCMI_MSG_BASE_DISCOVER_VENDOR                  0x3U
/*! Get sub-vendor identifier */
#define SCMI_MSG_BASE_DISCOVER_SUB_VENDOR              0x4U
/*! Get implementation version */
#define SCMI_MSG_BASE_DISCOVER_IMPLEMENTATION_VERSION  0x5U
/*! Discover protocols */
#define SCMI_MSG_BASE_DISCOVER_LIST_PROTOCOLS          0x6U
/*! Get agent information */
#define SCMI_MSG_BASE_DISCOVER_AGENT                   0x7U
/*! Set device permissions */
#define SCMI_MSG_BASE_SET_DEVICE_PERMISSIONS           0x9U
/*! Reset platform resource settings for an agent */
#define SCMI_MSG_BASE_RESET_AGENT_CONFIGURATION        0xBU
/** @} */

/*!
 * @name SCMI max base argument lengths
 */
/** @{ */
/*! Max length of the returned agent name */
#define SCMI_BASE_MAX_NAME              16U
/*! Max length of the returned vendor identifier */
#define SCMI_BASE_MAX_VENDORIDENTIFIER  16U
/*! Max number of protocols returned in one call */
#define SCMI_BASE_MAX_PROTOCOLS         SCMI_ARRAY(8U, uint32_t)
/** @} */

/*!
 * @name SCMI actual base argument lengths
 */
/** @{ */
/*! Actual number of protocol words returned */
#define SCMI_BASE_NUM_PROTOCOLS  (((msgRx->numProtocols - 1U) / 4U) + 1U)
/** @} */

/*!
 * @name SCMI agent ID
 */
/** @{ */
/*! Agent ID to use to discover the callers agent ID */
#define SCMI_BASE_ID_DISCOVER  0xFFFFFFFFU
/** @} */

/* Macros */

/*!
 * @name SCMI power protocol attributes
 */
/** @{ */
/*! Number of agents in the system */
#define SCMI_BASE_PROTO_ATTR_NUM_AGENTS(x)     (((x) & 0xFF00U) >> 8U)
/*! Number of protocols that are implemented, excluding the Base protocol */
#define SCMI_BASE_PROTO_ATTR_NUM_PROTOCOLS(x)  (((x) & 0xFFU) >> 0U)
/** @} */

/*!
 * @name SCMI base device permission flags
 */
/** @{ */
/*! Access Type */
#define SCMI_BASE_PERM_FLAGS_ACCESS_TYPE(x)  (((x) & 0x1U) << 0U)
/** @} */

/*!
 * @name SCMI base reset agents flags
 */
/** @{ */
/*! Permissions Reset */
#define SCMI_BASE_FLAGS_PERMISSIONS(x)  (((x) & 0x1U) << 0U)
/** @} */

/* Functions */

/*!
 * Get protocol version.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[out]    version  Protocol version. For this revision of the
 *                         specification, this value must be 0x20001
 *
 * This function returns the version of this protocol. For this version of the
 * specification, the value that is returned must be 0x20001, which corresponds
 * to version 2.1. See section 4.2.2.1 PROTOCOL_VERSION in the
 * [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_BaseProtocolVersion(uint32_t channel, uint32_t *version);

/*!
 * Get protocol attributes.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[out]    attributes  Protocol attributes:<BR>
 *                            Bits[31:16] Reserved, must be zero.<BR>
 *                            Bits[15:8] Number of agents in the system.<BR>
 *                            Bits[7:0] Number of protocols that are
 *                            implemented, excluding the Base protocol
 *
 * This function returns the implementation details that are associated with
 * this protocol. If the platform does not support agent discovery, then it
 * reports the number of agents in the system as zero, and all notifications
 * carry a zero in the \a agentId field. See section 4.2.2.3
 * PROTOCOL_ATTRIBUTES in the [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_BASE_PROTO_ATTR_NUM_AGENTS() - Number of agents in the system
 * - ::SCMI_BASE_PROTO_ATTR_NUM_PROTOCOLS() - Number of protocols that are
 *   implemented, excluding the Base protocol
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_BaseProtocolAttributes(uint32_t channel, uint32_t *attributes);

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
 * a specific message in this protocol.  An example message ID is
 * ::SCMI_MSG_BASE_DISCOVER_VENDOR. See section 4.2.2.4
 * PROTOCOL_MESSAGE_ATTRIBUTES in the [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: in case the message is implemented and available to
 *   use.
 * - ::SCMI_ERR_NOT_FOUND: if the message identified by \a messageId is not
 *   provided by this platform implementation.
 */
int32_t SCMI_BaseProtocolMessageAttributes(uint32_t channel,
    uint32_t messageId, uint32_t *attributes);

/*!
 * Get vendor identifier.
 *
 * @param[in]     channel           A2P channel for comms
 * @param[out]    vendorIdentifier  Null terminated ASCII string of up to 16
 *                                  bytes with a vendor name
 *
 * This function provides a vendor identifier ASCII string. Max string length
 * is ::SCMI_BASE_MAX_VENDORIDENTIFIER. See section 4.2.2.5
 * BASE_DISCOVER_VENDOR in the [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_BaseDiscoverVendor(uint32_t channel,
    uint8_t *vendorIdentifier);

/*!
 * Get sub-vendor identifier.
 *
 * @param[in]     channel           A2P channel for comms
 * @param[out]    vendorIdentifier  Null terminated ASCII string of up to 16
 *                                  bytes with a sub-vendor name
 *
 * On success, this optional function provides a sub vendor identifier ASCII
 * string. Max string length is ::SCMI_BASE_MAX_VENDORIDENTIFIER. See section
 * 4.2.2.6 BASE_DISCOVER_SUB_VENDOR in the [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_BaseDiscoverSubVendor(uint32_t channel,
    uint8_t *vendorIdentifier);

/*!
 * Get implementation version.
 *
 * @param[in]     channel                A2P channel for comms
 * @param[out]    implementationVersion  Build number from git
 *
 * This function provides a vendor-specific 32-bit implementation version. The
 * format of the version number is vendor-specific, but version numbers must be
 * strictly increasing so that a higher number indicates a more recent
 * implementation. See section 4.2.2.7 BASE_DISCOVER_IMPLEMENTATION_VERSION in
 * the [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_BaseDiscoverImplementationVersion(uint32_t channel,
    uint32_t *implementationVersion);

/*!
 * Discover protocols.
 *
 * @param[in]     channel       A2P channel for comms
 * @param[in]     skip          Number of protocols to skip
 * @param[out]    numProtocols  Number of protocols that are returned by this
 *                              call
 * @param[out]    protocols     Array of protocol identifiers. Listed are those
 *                              implemented, excluding the base protocol, with
 *                              four protocol identifiers packed into each
 *                              array element
 *
 * This function allows the agent to discover which protocols it is allowed to
 * access. The protocol list returned by this call should be in numeric
 * ascending order. Max number of protocol **words** is
 * ::SCMI_BASE_MAX_PROTOCOLS. See section 4.2.2.8 BASE_DISCOVER_LIST_PROTOCOLS
 * in the [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if a valid list of protocols is found.
 * - ::SCMI_ERR_INVALID_PARAMETERS: if skip field is invalid.
 */
int32_t SCMI_BaseDiscoverListProtocols(uint32_t channel, uint32_t skip,
    uint32_t *numProtocols, uint32_t *protocols);

/*!
 * Get agent information.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[in,out] agentId  Identifier of the agent whose identification is
 *                         requested. This field is:<BR>
 *                         - populated with the agent ID of the calling agent,
 *                         when the \a agentId parameter passed via the
 *                         function is 0xFFFFFFFF.<BR>
 *                         - identical to the \a agentId field passed via the
 *                         calling parameters, in all other cases
 * @param[out]    name     Null terminated ASCII string of up to 16 bytes in
 *                         length
 *
 * This optional function allows the caller to discover the name of an agent,
 * described through an ASCII string of up to 16 bytes. A caller can discover
 * if this function is implemented by calling the
 * SCMI_BaseProtocolMessageAttributes() function and passing the messageId of
 * this function. If the function is implemented,
 * SCMI_BaseProtocolMessageAttributes() returns SCMI_ERR_SUCCESS. Max name
 * length is ::SCMI_BASE_MAX_NAME.
 *
 * Agent identifiers, \a agentId, describe agents in the system that can use
 * the SCMI protocols. Not every agent can use all protocols, and some
 * protocols can offer different views to different agents. An \a agentId of 0
 * is reserved to identify the platform itself. If the function is not
 * implemented, the caller does not interpret agent identifiers in
 * notifications, and the platform sets \a agentId to zero in notifications.
 * Where supported, \a agentId values are sequential, start from one, and are
 * limited by the number of agents that is reported through
 * SCMI_BaseProtocolAttributes().
 *
 * If called with an \a agentId of 0, the string returned in the name parameter
 * must start with platform.
 *
 * An agent can discover its own agent ID and name by passing \a agentId of
 * ::SCMI_BASE_ID_DISCOVER. In this case, the function returns the agent ID and
 * name of the calling agent. See section 4.2.2.10 BASE_DISCOVER_AGENT in the
 * [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: If a valid agent identifier is found.
 * - ::SCMI_ERR_NOT_FOUND: if \a agentId does not point to a valid agent.
 */
int32_t SCMI_BaseDiscoverAgent(uint32_t channel, uint32_t *agentId,
    uint8_t *name);

/*!
 * Set device permissions.
 *
 * @param[in]     channel   A2P channel for comms
 * @param[in]     agentId   Identifier of the Agent
 * @param[in]     deviceId  Identifier of the device
 * @param[in]     flags     Device permission flags:<BR>
 *                          Bits[31:1] Reserved, must be zero.<BR>
 *                          Bit[0] Access Type:<BR>
 *                          This bit defines the permissions of the agent to
 *                          access platform resources associated with the
 *                          device.<BR>
 *                          If set to 0, deny agent access to the device.<BR>
 *                          If set to 1, allow agent access to the device
 *
 * This function is used to indicate to the platform whether an agent has
 * permissions to access devices, as specified by a device identifier. An agent
 * can only operate on devices to which it has access, and by extension can
 * only operate on the power, performance, clock, sensor, reset and voltage
 * domains that are associated with that device. At system boot, the default
 * device-specific access permission of an agent is IMPLEMENTATION defined. Arm
 * recommends that only trusted agents in the system are given permission to
 * invoke this function.
 *
 * The Base protocol does not cover the discovery of device identifiers for
 * devices in a platform. This information is provided to the caller by way of
 * firmware tables in FDT or ACPI.
 *
 * A caller can discover if this function is implemented by calling the
 * SCMI_BaseProtocolMessageAttributes() function and passing the messageId of
 * this function. If the function is implemented,
 * SCMI_BaseProtocolMessageAttributes()  returns SCMI_ERR_SUCCESS. See section
 * 4.2.2.12 BASE_SET_DEVICE_PERMISSIONS in the [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_BASE_PERM_FLAGS_ACCESS_TYPE() - Access Type
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: in case the device permissions was set successfully
 *   for the agent specified by \a agentId.
 * - ::SCMI_ERR_NOT_FOUND: if \a agentId or \a deviceId does not exist.
 * - ::SCMI_ERR_INVALID_PARAMETERS: if \a flags is invalid.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the function is not supported.
 * - ::SCMI_ERR_DENIED: if the calling agent is not allowed to set the
 *   permissions of the agent specified by \a agentId.
 */
int32_t SCMI_BaseSetDevicePermissions(uint32_t channel, uint32_t agentId,
    uint32_t deviceId, uint32_t flags);

/*!
 * Reset platform resource settings for an agent.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[in]     agentId  Identifier of the Agent
 * @param[in]     flags    Reset agent flags:<BR>
 *                         Bits[31:1] Reserved, must be zero.<BR>
 *                         Bit[0] Permissions Reset:<BR>
 *                         If set to 0, maintain all access permission settings
 *                         of the agent.<BR>
 *                         If set to 1, reset all access permission settings of
 *                         the agent.<BR>
 *                         This function must always reset the platform
 *                         resource settings configured by the agent specified
 *                         by \a agentId. Platform resource settings refer to
 *                         Device, Power Domain, Performance Domain, Clocks,
 *                         Sensors and other settings configured by the agent
 *                         specified by \a agentId
 *
 * This function is used to reset platform resource settings that were
 * previously configured by an agent. Platform resource settings refer to power
 * domain, performance domain, clock, sensors and other settings associated
 * with a device that the agent has access to. This function can also be used
 * to reset agent-specific permission configurations to access devices and
 * protocols.
 *
 * When this function is called, the platform might need to flush all pending
 * requests from the agent that is undergoing configuration reset. It might
 * also need to wait for requests that are being processed on behalf of the
 * agent to complete. Alternatively, the platform can choose to abort all
 * agent-related transactions in flight and reset its configuration. The
 * platform needs to revert the platform resources that are solely dedicated to
 * the agent into their default state. Shared platform resources need to be
 * moved System Control and Management Interface into a state that continues to
 * meet the requirements of the remaining agents using that resource. Shared
 * platform resources are those which are shared among and used by multiple
 * agents. Agent configuration reset should not be confused with the reset of
 * the platform or its components.
 *
 * If the Permissions Reset flag is set, the platform resets all the device and
 * protocol access permissions that are configured for the agent. When
 * permission reset completes, IMPLEMENTATION defined platform-specific default
 * permissions are restored for that agent.
 *
 * Arm recommends that only trusted agents in the system are given permissions
 * to invoke this function for other agents. An agent can invoke this function
 * for itself.
 *
 * A caller can discover if this function is implemented by calling the
 * SCMI_BaseProtocolMessageAttributes() function and passing the messageId of
 * this function. If the function is implemented,
 * SCMI_BaseProtocolMessageAttributes() returns SCMI_ERR_SUCCESS. See section
 * 4.2.2.13 BASE_RESET_AGENT_CONFIGURATION in the [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_BASE_FLAGS_PERMISSIONS() - Permissions Reset
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: If a valid agent identifier is found.
 * - ::SCMI_ERR_NOT_FOUND: if \a agentId does not point to a valid agent.
 * - ::SCMI_ERR_DENIED: if the calling agent is not allowed to set the reset
 *   the agent specified by \a agentId.
 */
int32_t SCMI_BaseResetAgentConfiguration(uint32_t channel, uint32_t agentId,
    uint32_t flags);

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
int32_t SCMI_BaseNegotiateProtocolVersion(uint32_t channel,
    uint32_t version);

#endif /* SCMI_BASE_H */

/** @} */

