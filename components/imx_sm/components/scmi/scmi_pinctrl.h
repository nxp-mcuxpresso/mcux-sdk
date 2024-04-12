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

#ifndef SCMI_PINCTRL_H
#define SCMI_PINCTRL_H

/*!
 * @addtogroup scmi_proto_pinctrl
 * @{
 */

/*!
 * @file
 * @brief Header file containing the client-side API for the System Control and
 * Management Interface (SCMI) pinctrl protocol.
 */

/* Defines */

/*!
 * @name SCMI pinctrl protocol message IDs
 */
/** @{ */
/*! Get pin attributes */
#define SCMI_MSG_PINCTRL_ATTRIBUTES          0x3U
/*! Get pin configuration */
#define SCMI_MSG_PINCTRL_SETTINGS_GET        0x5U
/*! Set pin configuration */
#define SCMI_MSG_PINCTRL_SETTINGS_CONFIGURE  0x6U
/*! Request a pin */
#define SCMI_MSG_PINCTRL_REQUEST             0x7U
/*! Release a pin */
#define SCMI_MSG_PINCTRL_RELEASE             0x8U
/** @} */

/*!
 * @name SCMI max pin control argument lengths
 */
/** @{ */
/*! Max length of the returned pin name */
#define SCMI_PINCTRL_MAX_NAME       16U
/*! Max number of configs returned in one call */
#define SCMI_PINCTRL_MAX_CONFIGS    SCMI_ARRAY(12U, scmi_pin_config_t)
/*! Max number of configs sent in one call */
#define SCMI_PINCTRL_MAX_CONFIGS_T  SCMI_ARRAY(8U, scmi_pin_config_t)
/** @} */

/*!
 * @name SCMI actual pin control argument lengths
 */
/** @{ */
/*! Actual number of configs returned */
#define SCMI_PINCTRL_NUM_CONFIGS    SCMI_PINCTRL_NUM_CONFIG_FLAGS_NUM_CONFIGS(msgRx->numConfigs)
/*! Actual number of configs sent */
#define SCMI_PINCTRL_NUM_CONFIGS_T  (attributes >> 2)
/** @} */

/*!
 * @name SCMI pin control selectors
 */
/** @{ */
/*! Select pin */
#define SCMI_PINCTRL_SEL_PIN    0U
/*! Select group */
#define SCMI_PINCTRL_SEL_GROUP  1U
/*! Select function */
#define SCMI_PINCTRL_SEL_FUNC   2U
/** @} */

/*!
 * @name SCMI pin control types
 */
/** @{ */
/*! Mux type */
#define SCMI_PINCTRL_TYPE_MUX        192U
/*! Config type */
#define SCMI_PINCTRL_TYPE_CONFIG     193U
/*! Daisy ID type */
#define SCMI_PINCTRL_TYPE_DAISY_ID   194U
/*! Daisy config type */
#define SCMI_PINCTRL_TYPE_DAISY_CFG  195U
/** @} */

/*!
 * @name SCMI pin control selectors
 */
/** @{ */
/*! One specified by type */
#define SCMI_PINCTRL_CONFIG_FLAG_TYPE  0U
/*! All config types */
#define SCMI_PINCTRL_CONFIG_FLAG_ALL   1U
/*! No config types */
#define SCMI_PINCTRL_CONFIG_FLAG_NONE  2U
/** @} */

/*!
 * @name SCMI pin control selectors
 */
/** @{ */
/*! No function */
#define SCMI_PINCTRL_FUNC_NONE  0xFFFFFFFFU
/** @} */

/* Macros */

/*!
 * @name SCMI pin control protocol attributes (low)
 */
/** @{ */
/*! Number of groups */
#define SCMI_PINCTRL_PROTO_ATTR_LOW_NUM_GROUPS(x)  (((x) & 0xFFFF0000U) >> 16U)
/*! Number of pins */
#define SCMI_PINCTRL_PROTO_ATTR_LOW_NUM_PINS(x)    (((x) & 0xFFFFU) >> 0U)
/** @} */

/*!
 * @name SCMI pin control protocol attributes (high)
 */
/** @{ */
/*! Number of functions */
#define SCMI_PINCTRL_PROTO_ATTR_HIGH_NUM_FUNCTIONS(x)  (((x) & 0xFFFFU) >> 0U)
/** @} */

/*!
 * @name SCMI pin control flags
 */
/** @{ */
/*! Selector */
#define SCMI_PINCTRL_FLAGS_SELECTOR(x)  (((x) & 0x3U) << 0U)
/** @} */

/*!
 * @name SCMI pin attributes
 */
/** @{ */
/*! Extended name */
#define SCMI_PINCTRL_ATTR_EXT_NAME(x)  (((x) & 0x80000000U) >> 31U)
/*! GPIO function descriptor */
#define SCMI_PINCTRL_ATTR_GPIO(x)      (((x) & 0x20000U) >> 17U)
/*! Pin-only function descriptor */
#define SCMI_PINCTRL_ATTR_PIN_ONLY(x)  (((x) & 0x10000U) >> 16U)
/*! Number of pins or groups */
#define SCMI_PINCTRL_ATTR_NUM(x)       (((x) & 0xFFFFU) >> 0U)
/** @} */

/*!
 * @name SCMI pin control get attributes
 */
/** @{ */
/*! Config flag */
#define SCMI_PINCTRL_GET_ATTR_CONFIG(x)        (((x) & 0x3U) << 18U)
/*! Selector */
#define SCMI_PINCTRL_GET_ATTR_SELECTOR(x)      (((x) & 0x3U) << 16U)
/*! Skip Configs */
#define SCMI_PINCTRL_GET_ATTR_SKIP_CONFIGS(x)  (((x) & 0xFFU) << 8U)
/*! ConfigType */
#define SCMI_PINCTRL_GET_ATTR_CONFIG_TYPE(x)   (((x) & 0xFFU) << 0U)
/** @} */

/*!
 * @name SCMI pin control num config flags
 */
/** @{ */
/*! Number of remaining configurations */
#define SCMI_PINCTRL_NUM_CONFIG_FLAGS_REMAING_CONFIGS(x)  (((x) & 0xFF000000U) >> 24U)
/*! Number of configurations that are returned by this call */
#define SCMI_PINCTRL_NUM_CONFIG_FLAGS_NUM_CONFIGS(x)      (((x) & 0xFFU) >> 0U)
/** @} */

/*!
 * @name SCMI pin control set attributes
 */
/** @{ */
/*! Function ID valid */
#define SCMI_PINCTRL_SET_ATTR_FUNCTION(x)     (((x) & 0x1U) << 10U)
/*! Number of configurations to set */
#define SCMI_PINCTRL_SET_ATTR_NUM_CONFIGS(x)  (((x) & 0xFFU) << 2U)
/*! Selector */
#define SCMI_PINCTRL_SET_ATTR_SELECTOR(x)     (((x) & 0x3U) << 0U)
/** @} */

/* Types */

/*!
 * SCMI pin control config
 */
typedef struct
{
    /*! The type of config */
    uint32_t type;
    /*! The configuration value */
    uint32_t value;
} scmi_pin_config_t;

/* Functions */

/*!
 * Get protocol version.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[out]    version  Protocol version. For this revision of the
 *                         specification, this value must be 0x10000
 *
 * On success, this function returns the Protocol version. For this version of
 * the specification, the return value must be 0x10000, which corresponds to
 * version 1.0. See section 4.11.2.1 PROTOCOL_VERSION in the
 * [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_PinctrlProtocolVersion(uint32_t channel, uint32_t *version);

/*!
 * Get protocol attributes.
 *
 * @param[in]     channel         A2P channel for comms
 * @param[out]    attributesLow   Low protocol attributes:<BR>
 *                                Bits[31:16] Number of pin groups.<BR>
 *                                Bits[15:0] Number of pins
 * @param[out]    attributesHigh  High protocol attributes:<BR>
 *                                Bits[31:16] Reserved, must be zero.<BR>
 *                                Bits[15:0] Number of functions
 *
 * This function returns the implementation details associated with this
 * protocol. See section 4.11.2.3 PROTOCOL_ATTRIBUTES in the
 * [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_PINCTRL_PROTO_ATTR_LOW_NUM_GROUPS() - Number of groups
 * - ::SCMI_PINCTRL_PROTO_ATTR_LOW_NUM_PINS() - Number of pins
 * - ::SCMI_PINCTRL_PROTO_ATTR_HIGH_NUM_FUNCTIONS() - Number of functions
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_PinctrlProtocolAttributes(uint32_t channel,
    uint32_t *attributesLow, uint32_t *attributesHigh);

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
 * ::SCMI_MSG_PINCTRL_ATTRIBUTES. The max name length is
 * ::SCMI_PINCTRL_MAX_NAME. See section 4.11.2.4 PROTOCOL_MESSAGE_ATTRIBUTES in
 * the [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: in case the message is implemented and available to
 *   use.
 * - ::SCMI_ERR_NOT_FOUND: if the message identified by \a messageId is
 *   invalid or not implemented.
 */
int32_t SCMI_PinctrlProtocolMessageAttributes(uint32_t channel,
    uint32_t messageId, uint32_t *attributes);

/*!
 * Get pin attributes.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in]     identifier  Identifier for the pin, group, or function.<BR>
 *                            Identifiers are limited to 16 bits, and the upper
 *                            16 bits of this field are ignored by the platform
 * @param[in]     flags       Selector:<BR>
 *                            Bits[31:2] Reserved, must be zero.<BR>
 *                            Bits[1:0] Selector: Whether the identifier field
 *                            selects a pin, a group, or a function.<BR>
 *                            0 - Pin<BR>
 *                            1 - Group<BR>
 *                            2 - Function<BR>
 *                            All other values are reserved for future use
 * @param[out]    attributes  Pin attributes:<BR>
 *                            The attributes of the pin, group, or function
 *                            identified by the identifier field in combination
 *                            with Bits[1:0] of the flag field in the
 *                            function.<BR>
 *                            Bit[31] Extended name.<BR>
 *                            If set to 1, the name is greater than 16
 *                            bytes.<BR>
 *                            If set to 0, extended name is not supported.<BR>
 *                            Bits[30:18] Reserved, must be zero.<BR>
 *                            Bit[17] GPIO function descriptor<BR>
 *                            Set to 0 if Bits[1:0] of the flags field in the
 *                            command is set to 2, and the function does not
 *                            support GPIO functionality.<BR>
 *                            Set to 1 if Bits[1:0] of the flags field in the
 *                            command is set to 2, and the function supports
 *                            GPIO functionality.<BR>
 *                            The agent should ignore the value of this bit if
 *                            Bits[1:0] of flags field in the command is set to
 *                            0 or 1.<BR>
 *                            This value of bit must not be 1 for more than one
 *                            function associated with a pin or a group.<BR>
 *                            Bit[16] Pin-only function descriptor.<BR>
 *                            Set to 0 if Bits[1:0] of the flags field in the
 *                            command is set to 2, and the function is only
 *                            supported by groups.<BR>
 *                            Set to 1 if Bits[1:0] of the flags field in the
 *                            command is set to 2, the function is a single-pin
 *                            function, and it is not supported by any group.
 *                            The function is only supported by individual
 *                            pins.<BR>
 *                            The agent should ignore the value of this bit if
 *                            Bits[1:0] of flags field in the command is set to
 *                            0 or 1.<BR>
 *                            Bits[15:0] Number of pins or groups.<BR>
 *                            - Set to 1, if Bits[1:0] of flags field in the
 *                            command is set to 0.<BR>
 *                            - Set to the number of pins in the group, if
 *                            Bits[1:0] of flags field in the command is set to
 *                            1.<BR>
 *                            - Set to the number of pins which can support the
 *                            function, if Bits[1:0] of flags field in the
 *                            command is set to 2 and Bit[16] of attributes
 *                            field is set to 1.<BR>
 *                            - Set to the number of groups which can support
 *                            the function in all other cases.<BR>
 * @param[out]    name        Null-terminated ASCII string of up to 16 bytes in
 *                            length describing the pin, group, or function
 *                            name. When Bit[31] of attributes field is set to
 *                            1, this field contains the lower 15 bytes of the
 *                            NULL terminated name
 *
 * This function returns the attributes associated with a specific function,
 * pin, or a group of pins. See section 4.11.2.5 PINCTRL_ATTRIBUTES in the
 * [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_PINCTRL_FLAGS_SELECTOR() - Selector
 * - ::SCMI_PINCTRL_ATTR_EXT_NAME() - Extended name
 * - ::SCMI_PINCTRL_ATTR_GPIO() - GPIO function descriptor
 * - ::SCMI_PINCTRL_ATTR_PIN_ONLY() - Pin-only function descriptor
 * - ::SCMI_PINCTRL_ATTR_NUM() - Number of pins or groups
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if valid attributes were returned.
 * - ::SCMI_ERR_NOT_FOUND: if the \a identifier field pertains to a
 *   non-existent pin, group, or function.
 */
int32_t SCMI_PinctrlAttributes(uint32_t channel, uint32_t identifier,
    uint32_t flags, uint32_t *attributes, uint8_t *name);

/*!
 * Get pin configuration.
 *
 * @param[in]     channel           A2P channel for comms
 * @param[in]     identifier        Identifier for the pin or group
 * @param[in]     attributes        Pin control set attributes:<BR>
 *                                  Bits[31:20] Reserved, must be zero.<BR>
 *                                  Bit[19:18] Config flag.<BR>
 *                                  When set to 0, only the configuration value
 *                                  for the configuration type specified by
 *                                  Bits[7:0] needs to be returned.<BR>
 *                                  When set to 1, configuration values for all
 *                                  relevant configuration types associated
 *                                  with the pin or group need to be returned.
 *                                  The returned configuration array is sorted
 *                                  in numerically increasing order of config
 *                                  types.<BR>
 *                                  When set to 2, no configuration values need
 *                                  to be returned. The command only returns
 *                                  the function selected for the pin or the
 *                                  group.<BR>
 *                                  All other values are reserved for future
 *                                  use.<BR>
 *                                  Bits[17:16] Selector: Whether the
 *                                  identifier field refers to a pin or a
 *                                  group.<BR>
 *                                  0 - Pin<BR>
 *                                  1 - Group<BR>
 *                                  All other values are reserved for future
 *                                  use.<BR>
 *                                  Bits[15:8] skipConfigs<BR>
 *                                  The number of configuration types to skip
 *                                  over, before returning the first
 *                                  configuration type and value in the return
 *                                  configuration array.<BR>
 *                                  This field is ignored if Bit[19:18] is set
 *                                  to 0 or 2.<BR>
 *                                  Bits[7:0] ConfigType: The type of
 *                                  config.<BR>
 *                                  This field is ignored if Bit[19:18] is set
 *                                  to 1 or 2
 * @param[out]    functionSelected  Function select:<BR>
 *                                  The function currently selected to be
 *                                  enabled by the pin or group specified in
 *                                  the input identifier field.<BR>
 *                                  This field is set to 0xFFFFFFFF if no
 *                                  function is currently enabled by the pin or
 *                                  group specified
 * @param[out]    numConfigs        Number of configs:<BR>
 *                                  Bits[31:24] Number of remaining
 *                                  configurations.<BR>
 *                                  Bits[23:8] Reserved, must be zero.<BR>
 *                                  Bits[7:0] Number of configurations that are
 *                                  returned by this call.<BR>
 *                                  This field should be set to 0 if Bit[19:18]
 *                                  of the attributes field of the command was
 *                                  set to 2.<BR>
 *                                  This field should be set to 1 if Bit[19:18]
 *                                  of the attributes field of the command was
 *                                  set to 0
 * @param[out]    configs           Array of configurations: sorted in
 *                                  numerically increasing config type
 *                                  order.<BR>
 *                                  This field should be ignored if Bit[19:18]
 *                                  of the attributes field of the command was
 *                                  set to 2.<BR>
 *                                  Size is specified by Bits[7:0] of the \a
 *                                  numConfigs field.<BR>
 *                                  Each array entry is composed of two 32-bit
 *                                  words containing the type and value
 *
 * This function can be used by an agent to get the pin or group configuration.
 * The max number of config is ::SCMI_PINCTRL_MAX_CONFIGS. See section 4.11.2.7
 * PINCTRL_SETTINGS_GET in the [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_PINCTRL_GET_ATTR_CONFIG() - Config flag
 * - ::SCMI_PINCTRL_GET_ATTR_SELECTOR() - Selector
 * - ::SCMI_PINCTRL_GET_ATTR_SKIP_CONFIGS() - Skip Configs
 * - ::SCMI_PINCTRL_GET_ATTR_CONFIG_TYPE() - ConfigType
 * - ::SCMI_PINCTRL_NUM_CONFIG_FLAGS_REMAING_CONFIGS() - Number of remaining
 *   configurations
 * - ::SCMI_PINCTRL_NUM_CONFIG_FLAGS_NUM_CONFIGS() - Number of configurations
 *   that are returned by this call
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the pin or group configuration was successfully
 *   returned.
 * - ::SCMI_ERR_NOT_FOUND: if the \a identifier field does not point to a
 *   valid pin or group.
 * - ::SCMI_ERR_INVALID_PARAMETERS, if the \a attributes flag specifies
 *   unsupported or invalid configurations.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the request is not supported.
 */
int32_t SCMI_PinctrlSettingsGet(uint32_t channel, uint32_t identifier,
    uint32_t attributes, uint32_t *functionSelected, uint32_t *numConfigs,
    scmi_pin_config_t *configs);

/*!
 * Set pin configuration.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in]     identifier  Identifier for the pin or group
 * @param[in]     functionId  Function ID:<BR>
 *                            Identifier for the function selected to be
 *                            enabled for the selected pin or group.<BR>
 *                            This field is set to 0xFFFFFFFF if no function
 *                            should be enabled by the pin or group.<BR>
 *                            This value of this field is ignored by the
 *                            platform if Bit[10] of the attributes field is
 *                            set to 0
 * @param[in]     attributes  Pin control get attributes:<BR>
 *                            Bits[31:11] Reserved, must be zero.<BR>
 *                            Bit[10] Function valid.<BR>
 *                            When set to 0, the function selection for the pin
 *                            or group does not need to change. The platform
 *                            ignores the value of the function_id field.<BR>
 *                            When set to 1, the function selection for the pin
 *                            or group needs to change and is specified by the
 *                            function_id field.<BR>
 *                            Bits[9:2] Number of configurations to set.<BR>
 *                            The maximum value of this field is limited by the
 *                            transport used. The agent needs to specify this
 *                            field such that the entire function can be
 *                            accommodated within the transport chosen.<BR>
 *                            Bits[1:0] Selector: Whether the identifier field
 *                            refers to a pin or a group.<BR>
 *                            0 - Pin<BR>
 *                            1 - Group<BR>
 *                            All other values are reserved for future use
 * @param[in]     configs     Array of configurations: sorted in numerically
 *                            increasing config type order.<BR>
 *                            Size is specified by Bits[9:2] of the \a
 *                            attributes field.<BR>
 *                            Each array entry is composed of two 32-bit words
 *                            containing the type and value
 *
 * This function can be used by an agent to set the pin or group configuration.
 * The max number of configs is ::SCMI_PINCTRL_MAX_CONFIGS_T. See section
 * 4.11.2.8 PINCTRL_SETTINGS_CONFIGURE in the [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_PINCTRL_SET_ATTR_FUNCTION() - Function ID valid
 * - ::SCMI_PINCTRL_SET_ATTR_NUM_CONFIGS() - Number of configurations to set
 * - ::SCMI_PINCTRL_SET_ATTR_SELECTOR() - Selector
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the pin or group configuration was successfully
 *   set.
 * - ::SCMI_ERR_NOT_FOUND: if \a identifier field does not point to a valid
 *   pin or group.
 * - ::SCMI_ERR_INVALID_PARAMETERS: if the input parameters specify incorrect
 *   or illegal values.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the configuration requested by this
 *   function is not supported by the pin or group.
 * - ::SCMI_ERR_DENIED: if the calling agent is not allowed to set the
 *   configuration of this pin or group.
 */
int32_t SCMI_PinctrlSettingsConfigure(uint32_t channel, uint32_t identifier,
    uint32_t functionId, uint32_t attributes,
    const scmi_pin_config_t *configs);

/*!
 * Request a pin.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in]     identifier  Identifier for the pin or group
 * @param[in]     flags       Selector: Whether the identifier field selects a
 *                            pin, or a group.<BR>
 *                            0 - Pin<BR>
 *                            1 - Group<BR>
 *                            All other values are reserved for future use
 *
 * This function is used by an agent to request exclusive control of a pin or
 * group. This would make the pin or group unavailable for any other agent
 * until SCMI_PinctrlRelease() has been called by the controlling agent.
 *
 * For the SM, this function is not required as pin access controls are static
 * and cannot be changed dynamically. See section 4.11.2.9 PINCTRL_REQUEST in
 * the [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_PINCTRL_FLAGS_SELECTOR() - Selector
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if exclusive control of the pin or group was granted.
 * - ::SCMI_ERR_NOT_FOUND: if the \a identifier field does not point to a
 *   valid pin or group.
 * - ::SCMI_ERR_INVALID_PARAMETERS: if the input parameters specify incorrect
 *   or illegal values.
 * - ::SCMI_ERR_DENIED: if the calling agent is not allowed to request this
 *   pin or group..
 * - ::SCMI_ERR_IN_USE: if the pin or group is currently under exclusive
 *   control of another agent.
 */
int32_t SCMI_PinctrlRequest(uint32_t channel, uint32_t identifier,
    uint32_t flags);

/*!
 * Release a pin.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in]     identifier  Identifier for the pin or group
 * @param[in]     flags       Selector: Whether the identifier field selects a
 *                            pin, or a group.<BR>
 *                            0 - Pin<BR>
 *                            1 - Group<BR>
 *                            All other values are reserved for future use
 *
 * This function is used by an agent to release exclusive control of a pin or
 * group. See section 4.11.2.10 PINCTRL_RELEASE in the [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if exclusive control of the pin or group was released.
 * - ::SCMI_ERR_NOT_FOUND: if the \a identifier field does not point to a
 *   valid pin or group.
 * - ::SCMI_ERR_INVALID_PARAMETERS: if the input parameters specify incorrect
 *   or illegal values.
 */
int32_t SCMI_PinctrlRelease(uint32_t channel, uint32_t identifier,
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
 * 4.11.2.2 NEGOTIATE_PROTOCOL_VERSION in the [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the negotiated protocol version is supported by the
 *   platform. All commands, responses, and notifications post successful
 *   return of this command must comply with the negotiated version.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the protocol version is not supported.
 */
int32_t SCMI_PinctrlNegotiateProtocolVersion(uint32_t channel,
    uint32_t version);

#endif /* SCMI_PINCTRL_H */

/** @} */

