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

#ifndef SCMI_VOLTAGE_H
#define SCMI_VOLTAGE_H

/*!
 * @addtogroup scmi_proto_voltage
 * @{
 */

/*!
 * @file
 * @brief Header file containing the client-side API for the System Control and
 * Management Interface (SCMI) voltage protocol.
 */

/* Defines */

/*!
 * @name SCMI voltage protocol message IDs
 */
/** @{ */
/*! Get voltage domain attributes */
#define SCMI_MSG_VOLTAGE_DOMAIN_ATTRIBUTES  0x3U
/*! Get voltage level descriptions */
#define SCMI_MSG_VOLTAGE_DESCRIBE_LEVELS    0x4U
/*! Set voltage configuration */
#define SCMI_MSG_VOLTAGE_CONFIG_SET         0x5U
/*! Get voltage configuration */
#define SCMI_MSG_VOLTAGE_CONFIG_GET         0x6U
/*! Set voltage level */
#define SCMI_MSG_VOLTAGE_LEVEL_SET          0x7U
/*! Get voltage level */
#define SCMI_MSG_VOLTAGE_LEVEL_GET          0x8U
/** @} */

/*!
 * @name SCMI max voltage argument lengths
 */
/** @{ */
/*! Max length of the returned voltage domain name */
#define SCMI_VOLTAGE_MAX_NAME     16U
/*! Max number of voltage descriptions returned in one call */
#define SCMI_VOLTAGE_MAX_VOLTAGE  SCMI_ARRAY(8U, int32_t)
/** @} */

/*!
 * @name SCMI actual voltage argument lengths
 */
/** @{ */
/*! Actual number of voltage descriptions returned */
#define SCMI_VOLTAGE_NUM_VOLTAGE  SCMI_VOLTAGE_FLAGS_NUM_LEVELS(msgRx->flags)
/** @} */

/*!
 * @name SCMI voltage domain modes
 */
/** @{ */
/*! Off */
#define SCMI_VOLTAGE_DOMAIN_MODES_OFF  0x0U
/*! On */
#define SCMI_VOLTAGE_DOMAIN_MODES_ON   0x7U
/** @} */

/* Macros */

/*!
 * @name SCMI voltage protocol attributes
 */
/** @{ */
/*! Number of voltage domains */
#define SCMI_VOLTAGE_PROTO_ATTR_NUM_VOLTS(x)  (((x) & 0xFFFFU) >> 0U)
/** @} */

/*!
 * @name SCMI voltage domain attributes
 */
/** @{ */
/*! Asynchronous voltage level set support */
#define SCMI_VOLTAGE_ATTR_ASYNC(x)     (((x) & 0x80000000U) >> 31U)
/*! Extended voltage domain name */
#define SCMI_VOLTAGE_ATTR_EXT_NAME(x)  (((x) & 0x40000000U) >> 30U)
/** @} */

/*!
 * @name SCMI voltage description flags
 */
/** @{ */
/*! Number of remaining voltage levels */
#define SCMI_VOLTAGE_FLAGS_REMAINING_LEVELS(x)  (((x) & 0xFFFF0000U) >> 16U)
/*! Return format */
#define SCMI_VOLTAGE_FLAGS_FORMAT(x)            (((x) & 0x1000U) >> 12U)
/*! Number of voltage levels that are returned by this call */
#define SCMI_VOLTAGE_FLAGS_NUM_LEVELS(x)        (((x) & 0xFFFU) >> 0U)
/** @} */

/*!
 * @name SCMI voltage configs (set)
 */
/** @{ */
/*! Voltage mode */
#define SCMI_VOLTAGE_CONFIG_SET_MODE(x)  (((x) & 0xFU) << 0U)
/** @} */

/*!
 * @name SCMI voltage configs (get)
 */
/** @{ */
/*! Voltage mode */
#define SCMI_VOLTAGE_CONFIG_GET_MODE(x)  (((x) & 0xFU) >> 0U)
/** @} */

/*!
 * @name SCMI voltage set flags
 */
/** @{ */
/*! Async flag */
#define SCMI_VOLTAGE_SET_FLAGS_ASYNC(x)  (((x) & 0x1U) << 0U)
/** @} */

/* Functions */

/*!
 * Get protocol version.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[out]    version  Protocol version. For this revision of the
 *                         specification, this value must be 0x20001
 *
 * On success, this function returns the version of this protocol. For this
 * version of the specification, the return value must be 0x20001, which
 * corresponds to version 2.1. See section 4.9.2.1 PROTOCOL_VERSION in the
 * [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_VoltageProtocolVersion(uint32_t channel, uint32_t *version);

/*!
 * Get protocol attributes.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[out]    attributes  Protocol attributes:<BR>
 *                            Bits[31:16] Reserved, must be zero.<BR>
 *                            Bits[15:0] Number of voltage domains
 *
 * This function returns the implementation details associated with this
 * protocol. See section 4.9.2.3 PROTOCOL_ATTRIBUTES in the
 * [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_VOLTAGE_PROTO_ATTR_NUM_VOLTS() - Number of voltage domains
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_VoltageProtocolAttributes(uint32_t channel,
    uint32_t *attributes);

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
 * ::SCMI_MSG_VOLTAGE_DOMAIN_ATTRIBUTES. See section 4.9.2.4
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
int32_t SCMI_VoltageProtocolMessageAttributes(uint32_t channel,
    uint32_t messageId, uint32_t *attributes);

/*!
 * Get voltage domain attributes.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in]     domainId    Identifier for the domain. Domain identifiers are
 *                            limited to 16 bits, and the upper 16 bits of this
 *                            field are ignored by the platform
 * @param[out]    attributes  Domain attributes:<BR>
 *                            Bit[31] Asynchronous voltage level set
 *                            support.<BR>
 *                            Set to 1 if the voltage level of this domain can
 *                            be set asynchronously.<BR>
 *                            Set to 0 if the voltage level of this domain can
 *                            only be set synchronously.<BR>
 *                            Bit[30] Extended voltage domain name.<BR>
 *                            If set to 1, the voltage domain name is greater
 *                            than 16 bytes.<BR>
 *                            If set to 0, extended voltage domain name is not
 *                            supported.<BR>
 *                            Bits[29:0] Reserved, must be zero
 * @param[out]    name        Null-terminated ASCII string of up to 16 bytes in
 *                            length describing the voltage domain name. When
 *                            Bit[30] of attributes field is set to 1, this
 *                            field contains the lower 15 bytes of the NULL
 *                            terminated voltage domain name
 *
 * This function returns the attribute flags associated with a specific voltage
 * domain. The max name length is ::SCMI_VOLTAGE_MAX_NAME. See section 4.9.2.5
 * VOLTAGE_DOMAIN_ATTRIBUTES in the [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_VOLTAGE_ATTR_ASYNC() - Asynchronous voltage level set support
 * - ::SCMI_VOLTAGE_ATTR_EXT_NAME() - Extended voltage domain name
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if valid power domain attributes are returned.
 * - ::SCMI_ERR_NOT_FOUND: if \a domainId pertains to a non-existent domain.
 */
int32_t SCMI_VoltageDomainAttributes(uint32_t channel, uint32_t domainId,
    uint32_t *attributes, uint8_t *name);

/*!
 * Get voltage level descriptions.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in]     domainId    Identifier for the voltage domain
 * @param[in]     levelIndex  Index of the first voltage level. The first to be
 *                            described in the return voltage array
 * @param[out]    flags       Domain flags:<BR>
 *                            Descriptor for the voltage levels supported by
 *                            this domain.<BR>
 *                            Bits[31:16] Number of remaining voltage levels.
 *                            This field should be 0 if Bit[12] is 1.<BR>
 *                            Bits[15:13] Reserved, must be zero.<BR>
 *                            Bit[12] Return format:<BR>
 *                            If this bit is set to 1, the Voltage Array is a
 *                            triplet that constitutes a segment in the
 *                            following form:<BR>
 *                            voltage[0] is the lowest voltage level that the
 *                            domain supports.<BR>
 *                            voltage[1] is the highest voltage level that the
 *                            domain supports.<BR>
 *                            voltage[2] is the step size between two
 *                            successive voltage levels that the domain
 *                            supports.<BR>
 *                            If this bit is set to 0, each element of the
 *                            Voltage Array represents a discrete voltage level
 *                            that the voltage domain supports.<BR>
 *                            Bits[11:0] Number of voltage levels that are
 *                            returned by this call. This field should be 3 if
 *                            Bit[12] is 1
 * @param[out]    voltage     Voltage Array expressed in microvolts (uV):<BR>
 *                            If Bit[12] of the flags field is set to 0, each
 *                            array entry represents a discrete voltage
 *                            level.<BR>
 *                            If Bit[12] of the flags field is set to 1, then
 *                            each entry is a member of a segment {lowest
 *                            voltage level, highest voltage level, step size}
 *                            as described above.<BR>
 *                            N is specified by Bits[11:0] of flags field
 *
 * This function allows the agent to ascertain the voltage levels supported by
 * a voltage domain. On success, the function returns an array, which contains
 * a number of voltage level entries. Sometimes it might not be possible to
 * return the whole array with just one call. To solve this problem, the
 * interface allows multiple calls. It also returns the number of remaining
 * voltage levels. The size of the array returned depends on the number of
 * return values a given transport can support. The max number is
 * ::SCMI_VOLTAGE_MAX_VOLTAGE.
 *
 * Voltage domains can support many voltage levels and sometimes individually
 * describing each voltage level might be too onerous. In such cases, the
 * function can return only the lowest voltage level, the highest voltage level
 * and the step size between two successive voltage levels that the voltage
 * domain supports.
 *
 * The voltage levels returned by this call should be in numeric ascending
 * order. See section 4.9.2.6 VOLTAGE_DESCRIBE_LEVELS in the
 * [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_VOLTAGE_FLAGS_REMAINING_LEVELS() - Number of remaining voltage
 *   levels
 * - ::SCMI_VOLTAGE_FLAGS_FORMAT() - Return format
 * - ::SCMI_VOLTAGE_FLAGS_NUM_LEVELS() - Number of voltage levels that are
 *   returned by this call
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the voltage levels are returned successfully.
 * - ::SCMI_ERR_NOT_FOUND: if the domain identified by \a domainId does not
 *   exist.
 * - ::SCMI_ERR_OUT_OF_RANGE: if the \a levelIndex is outside of valid range.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the request is not supported.
 */
int32_t SCMI_VoltageDescribeLevels(uint32_t channel, uint32_t domainId,
    uint32_t levelIndex, uint32_t *flags, int32_t *voltage);

/*!
 * Set voltage configuration.
 *
 * @param[in]     channel   A2P channel for comms
 * @param[in]     domainId  Identifier for the voltage domain
 * @param[in]     config    Domain config:<BR>
 *                          Bits[31:4] Reserved, must be zero.<BR>
 *                          Bits[3:0] Mode: The operating mode the voltage
 *                          domain should be set to, as described in Table 21
 *
 * This function allows an agent to set the configuration of a voltage domain.
 * It allows each agent to set the mode for the domain. Mode is highest of all
 * agent settings. See section 4.9.2.7 VOLTAGE_CONFIG_SET in the
 * [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_VOLTAGE_CONFIG_SET_MODE() - Voltage mode
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the voltage domain configuration has been set
 *   successfully.
 * - ::SCMI_ERR_NOT_FOUND: if the voltage domain identified by \a domainId
 *   does not exist.
 * - ::SCMI_ERR_INVALID_PARAMETERS: if the requested configuration is not
 *   supported by the voltage domain.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the request is not supported.
 * - ::SCMI_ERR_DENIED: if the calling agent is not allowed to set the
 *   configuration of this voltage domain. An example would be if this voltage
 *   domain is exclusive to another agent.
 */
int32_t SCMI_VoltageConfigSet(uint32_t channel, uint32_t domainId,
    uint32_t config);

/*!
 * Get voltage configuration.
 *
 * @param[in]     channel   A2P channel for comms
 * @param[in]     domainId  Identifier for the voltage domain
 * @param[out]    config    Domain config:<BR>
 *                          Bits[31:4] Reserved, must be zero.<BR>
 *                          Bits[3:0] Mode: The operating mode of the voltage
 *                          domain, as described in Table 21
 *
 * This function allows the calling agent to request the configuration of a
 * voltage domain. See section 4.9.2.8 VOLTAGE_CONFIG_GET in the
 * [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_VOLTAGE_CONFIG_GET_MODE() - Voltage mode
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the voltage domain configuration was successfully
 *   returned.
 * - ::SCMI_ERR_NOT_FOUND: if \a domainId does not point to a valid voltage
 *   domain.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the request is not supported.
 */
int32_t SCMI_VoltageConfigGet(uint32_t channel, uint32_t domainId,
    uint32_t *config);

/*!
 * Set voltage level.
 *
 * @param[in]     channel       A2P channel for comms
 * @param[in]     domainId      Identifier for the voltage domain
 * @param[in]     flags         Voltage set flags:<BR>
 *                              Bits[31:1] Reserved, must be zero.<BR>
 *                              Bit[0] Async flag:<BR>
 *                              Set to 1 if the voltage level is to be set
 *                              asynchronously.<BR>
 *                              Set 0 to if the voltage level is to be set
 *                              synchronously. In this case, the call will
 *                              return when the voltage level has been set
 * @param[in]     voltageLevel  The voltage level, in microvolts (uV), to set
 *                              the domain to
 *
 * This function allows an agent to set the voltage level of a voltage domain.
 * Only one agent can set a voltage. No aggregation is supported. See section
 * 4.9.2.9 VOLTAGE_LEVEL_SET in the [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_VOLTAGE_SET_FLAGS_ASYNC() - Async flag
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the voltage domain has been set to the desired
 *   level.
 * - ::SCMI_ERR_NOT_FOUND: if the voltage domain identified by \a domainId
 *   does not exist.
 * - ::SCMI_ERR_INVALID_PARAMETERS: if the requested voltage level is not
 *   supported by the voltage domain.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the request is not supported.
 * - ::SCMI_ERR_DENIED: if the calling agent is not allowed to set the
 *   voltage level of this voltage domain. An example would be if this voltage
 *   domain is exclusive to another agent.
 */
int32_t SCMI_VoltageLevelSet(uint32_t channel, uint32_t domainId,
    uint32_t flags, int32_t voltageLevel);

/*!
 * Get voltage level.
 *
 * @param[in]     channel       A2P channel for comms
 * @param[in]     domainId      Identifier for the voltage domain
 * @param[out]    voltageLevel  The voltage level, in microvolts (uV), that the
 *                              domain is set to
 *
 * This function allows the calling agent to request the current voltage level
 * of a voltage domain. See section 4.9.2.10 VOLTAGE_LEVEL_GET in the
 * [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the voltage level of the domain was returned
 *   successfully.
 * - ::SCMI_ERR_NOT_FOUND: if \a domainId does not point to a valid voltage
 *   domain.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the request is not supported.
 */
int32_t SCMI_VoltageLevelGet(uint32_t channel, uint32_t domainId,
    int32_t *voltageLevel);

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
 * 4.9.2.2 NEGOTIATE_PROTOCOL_VERSION in the [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the negotiated protocol version is supported by the
 *   platform. All commands, responses, and notifications post successful
 *   return of this command must comply with the negotiated version.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the protocol version is not supported.
 */
int32_t SCMI_VoltageNegotiateProtocolVersion(uint32_t channel,
    uint32_t version);

#endif /* SCMI_VOLTAGE_H */

/** @} */

