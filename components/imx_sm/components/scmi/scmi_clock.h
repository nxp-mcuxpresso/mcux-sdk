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

#ifndef SCMI_CLOCK_H
#define SCMI_CLOCK_H

/*!
 * @addtogroup scmi_proto_clock
 * @{
 */

/*!
 * @file
 * @brief Header file containing the client-side API for the System Control and
 * Management Interface (SCMI) clock protocol.
 */

/* Defines */

/*!
 * @name SCMI clock protocol message IDs
 */
/** @{ */
/*! Get clock attributes */
#define SCMI_MSG_CLOCK_ATTRIBUTES            0x3U
/*! Get clock rate description */
#define SCMI_MSG_CLOCK_DESCRIBE_RATES        0x4U
/*! Set clock rate */
#define SCMI_MSG_CLOCK_RATE_SET              0x5U
/*! Get clock rate */
#define SCMI_MSG_CLOCK_RATE_GET              0x6U
/*! Set clock configuration */
#define SCMI_MSG_CLOCK_CONFIG_SET            0x7U
/*! Get clock configuration */
#define SCMI_MSG_CLOCK_CONFIG_GET            0xBU
/*! Get all possible parents */
#define SCMI_MSG_CLOCK_POSSIBLE_PARENTS_GET  0xCU
/*! Set clock parent */
#define SCMI_MSG_CLOCK_PARENT_SET            0xDU
/*! Get clock parent */
#define SCMI_MSG_CLOCK_PARENT_GET            0xEU
/*! Get clock permissions */
#define SCMI_MSG_CLOCK_GET_PERMISSIONS       0xFU
/** @} */

/*!
 * @name SCMI max clock argument lengths
 */
/** @{ */
/*! Max length of the returned clock name */
#define SCMI_CLOCK_MAX_NAME     16U
/*! Max number of rates returned in one call */
#define SCMI_CLOCK_MAX_RATES    SCMI_ARRAY(8U, scmi_clock_rate_t)
/*! Max number of parents returned in one call */
#define SCMI_CLOCK_MAX_PARENTS  SCMI_ARRAY(8U, uint32_t)
/** @} */

/*!
 * @name SCMI actual clock argument lengths
 */
/** @{ */
/*! Actual number of rates returned */
#define SCMI_CLOCK_NUM_RATES    SCMI_CLOCK_NUM_RATE_FLAGS_NUM_RATES(msgRx->numRatesFlags)
/*! Actual number of parents returned */
#define SCMI_CLOCK_NUM_PARENTS  SCMI_CLOCK_NUM_PARENT_FLAGS_NUM_PARENTS(msgRx->numParentsFlags)
/** @} */

/*!
 * @name SCMI clock round options
 */
/** @{ */
/*! Round up */
#define SCMI_CLOCK_ROUND_DOWN  0U
/*! Round down */
#define SCMI_CLOCK_ROUND_UP    1U
/*! Round to nearest */
#define SCMI_CLOCK_ROUND_AUTO  2U
/** @} */

/*!
 * @name SCMI clock state
 */
/** @{ */
/*! Disable clock */
#define SCMI_CLOCK_STATE_DISABLE  0U
/*! Enable clock */
#define SCMI_CLOCK_STATE_ENABLE   1U
/*! Reserved for future use */
#define SCMI_CLOCK_STATE_RESV     2U
/*! No state change */
#define SCMI_CLOCK_STATE_NA       3U
/** @} */

/*!
 * @name SCMI extended clock config
 */
/** @{ */
/*! Not used */
#define SCMI_CLOCK_EXT_NONE   0x0U
/*! Duty in percent */
#define SCMI_CLOCK_EXT_DUTY   0x1U
/*! Phase in mrad */
#define SCMI_CLOCK_EXT_PHASE  0x2U
/*! Spread spectrum */
#define SCMI_CLOCK_EXT_SSC    0x80U
/** @} */

/* Macros */

/*!
 * @name SCMI clock protocol attributes
 */
/** @{ */
/*! Maximum number of pending asynchronous clock rate changes supported by the
    platform */
#define SCMI_CLOCK_PROTO_ATTR_MAX_PENDING(x)  (((x) & 0xFF0000U) >> 16U)
/*! Number of clocks */
#define SCMI_CLOCK_PROTO_ATTR_NUM_CLOCKS(x)   (((x) & 0xFFFFU) >> 0U)
/** @} */

/*!
 * @name SCMI clock attributes
 */
/** @{ */
/*! Clock rate change notifications support */
#define SCMI_CLOCK_ATTR_CHANGE(x)      (((x) & 0x80000000U) >> 31U)
/*! Clock rate change requested notifications support */
#define SCMI_CLOCK_ATTR_CHANGE_REQ(x)  (((x) & 0x40000000U) >> 30U)
/*! Extended Clock name */
#define SCMI_CLOCK_ATTR_EXT_NAME(x)    (((x) & 0x20000000U) >> 29U)
/*! Parent clock identifier support */
#define SCMI_CLOCK_ATTR_PARENT(x)      (((x) & 0x10000000U) >> 28U)
/*! Extended configuration support */
#define SCMI_CLOCK_ATTR_EXT_CONFIG(x)  (((x) & 0x8000000U) >> 27U)
/*! Restricted clock */
#define SCMI_CLOCK_ATTR_RESTRICTED(x)  (((x) & 0x2U) >> 1U)
/*! Enabled/disabled */
#define SCMI_CLOCK_ATTR_ENABLED(x)     (((x) & 0x1U) >> 0U)
/** @} */

/*!
 * @name SCMI clock num rate flags
 */
/** @{ */
/*! Number of remaining rates */
#define SCMI_CLOCK_NUM_RATE_FLAGS_REMAING_RATES(x)  (((x) & 0xFFFF0000U) >> 16U)
/*! Return format */
#define SCMI_CLOCK_NUM_RATE_FLAGS_FORMAT(x)         (((x) & 0x1000U) >> 12U)
/*! Number of rates that are returned by this call */
#define SCMI_CLOCK_NUM_RATE_FLAGS_NUM_RATES(x)      (((x) & 0xFFFU) >> 0U)
/** @} */

/*!
 * @name SCMI clock rate flags
 */
/** @{ */
/*! Round up/down */
#define SCMI_CLOCK_RATE_FLAGS_ROUND(x)    (((x) & 0x3U) << 2U)
/*! Ignore delayed response */
#define SCMI_CLOCK_RATE_FLAGS_NO_RESP(x)  (((x) & 0x1U) << 1U)
/*! Async flag */
#define SCMI_CLOCK_RATE_FLAGS_ASYNC(x)    (((x) & 0x1U) << 0U)
/** @} */

/*!
 * @name SCMI clock config attributes
 */
/** @{ */
/*! Extended config type */
#define SCMI_CLOCK_CONFIG_SET_EXT_CONFIG(x)  (((x) & 0xFFU) << 16U)
/*! Enable/disable state */
#define SCMI_CLOCK_CONFIG_SET_ENABLE(x)      (((x) & 0x3U) << 0U)
/** @} */

/*!
 * @name SCMI clock config get flags
 */
/** @{ */
/*! Extended  config type */
#define SCMI_CLOCK_CONFIG_FLAGS_EXT_CONFIG(x)  (((x) & 0xFFU) << 0U)
/** @} */

/*!
 * @name SCMI clock config
 */
/** @{ */
/*! Enable/Disable */
#define SCMI_CLOCK_CONFIG_GET_ENABLE(x)  (((x) & 0x1U) >> 0U)
/** @} */

/*!
 * @name SCMI clock num rate flags
 */
/** @{ */
/*! Number of remaining parents */
#define SCMI_CLOCK_NUM_PARENT_FLAGS_REMAING_PARENTS(x)  (((x) & 0xFF000000U) >> 24U)
/*! Number of parent clock identifiers that are returned by this call */
#define SCMI_CLOCK_NUM_PARENT_FLAGS_NUM_PARENTS(x)      (((x) & 0xFFU) >> 0U)
/** @} */

/*!
 * @name SCMI clock permissions
 */
/** @{ */
/*! Clock state control */
#define SCMI_CLOCK_PERM_STATE(x)   (((x) & 0x80000000U) >> 31U)
/*! Clock parent control */
#define SCMI_CLOCK_PERM_PARENT(x)  (((x) & 0x40000000U) >> 30U)
/*! Clock rate control */
#define SCMI_CLOCK_PERM_RATE(x)    (((x) & 0x20000000U) >> 29U)
/** @} */

/* Types */

/*!
 * SCMI clock rate
 */
typedef struct
{
    /*! Lower 32 bits of the physical rate in Hertz */
    uint32_t lower;
    /*! Upper 32 bits of the physical rate in Hertz */
    uint32_t upper;
} scmi_clock_rate_t;

/* Functions */

/*!
 * Get protocol version.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[out]    version  Protocol version. For this revision of the
 *                         specification, this value must be 0x30000
 *
 * On success, this function returns the version of this protocol. For this
 * version of the specification, the return value must be 0x30000, which
 * corresponds to version 3.0. See section 4.6.2.1 PROTOCOL_VERSION in the
 * [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_ClockProtocolVersion(uint32_t channel, uint32_t *version);

/*!
 * Get protocol attributes.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[out]    attributes  Protocol attributes: <BR>
 *                            Bits[31:24] Reserved, must be zero.<BR>
 *                            Bits[23:16] Maximum number of pending
 *                            asynchronous clock rate changes supported by the
 *                            platform.<BR>
 *                            Bits[15:0] Number of clocks
 *
 * This function returns the implementation details associated with this
 * protocol. See section 4.6.2.3 PROTOCOL_ATTRIBUTES in the
 * [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_CLOCK_PROTO_ATTR_MAX_PENDING() - Maximum number of pending
 *   asynchronous clock rate changes supported by the platform
 * - ::SCMI_CLOCK_PROTO_ATTR_NUM_CLOCKS() - Number of clocks
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_ClockProtocolAttributes(uint32_t channel,
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
 * ::SCMI_MSG_CLOCK_ATTRIBUTES. See section 4.6.2.4 PROTOCOL_MESSAGE_ATTRIBUTES
 * in the [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: in case the message is implemented and available to
 *   use.
 * - ::SCMI_ERR_NOT_FOUND: if the message identified by \a messageId is
 *   invalid or not provided by this platform implementation.
 */
int32_t SCMI_ClockProtocolMessageAttributes(uint32_t channel,
    uint32_t messageId, uint32_t *attributes);

/*!
 * Get clock attributes.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in]     clockId     Identifier for the clock device
 * @param[out]    attributes  Clock attributes:<BR>
 *                            Bit[31] Clock rate change notifications
 *                            support.<BR>
 *                            Set to 1 if clock rate change notifications are
 *                            supported for this clock.<BR>
 *                            Set to 0 if clock rate change notifications are
 *                            not supported for this clock.<BR>
 *                            Bit[30] Clock rate change requested notifications
 *                            support.<BR>
 *                            Set to 1 if clock rate change requested
 *                            notifications are supported for this clock.<BR>
 *                            Set to 0 if clock rate change requested
 *                            notifications are not supported for this
 *                            clock.<BR>
 *                            Bit[29] Extended Clock name.<BR>
 *                            If set to 1, the clock name is greater than 16
 *                            bytes.<BR>
 *                            If set to 0, extended clock name is not
 *                            supported.<BR>
 *                            Bit[28] Parent clock identifier support.<BR>
 *                            Set to 1 if parent clock identifiers are
 *                            advertised for this clock.<BR>
 *                            Set to 0 if parent clock identifiers are not
 *                            advertised for this clock.<BR>
 *                            Bit[27] Extended configuration support.<BR>
 *                            Set to 1 if extended configurations are supported
 *                            for this clock. Extended configurations can be
 *                            accessed using the SCMI_ClockConfigSet() and the
 *                            SCMI_ClockConfigSet() functions.<BR>
 *                            Set to 0 if extended configurations are not
 *                            supported for this clock.<BR>
 *                            Bits[26:2] Reserved, must be zero.<BR>
 *                            Bit[1] Restricted clock.<BR>
 *                            Set to 1 if the clock has restrictions on
 *                            changing some of its configuration or settings,
 *                            and the CLOCK_GET_PERMISSIONS command, as
 *                            specified in Section 4.6.2.16, can be used to
 *                            discover the restrictions in place. Set to 0 if
 *                            either of the following are true:<BR>
 *                            -- The clock’s restrictions cannot be
 *                            discovered because CLOCK_GET_PERMISSIONS is not
 *                            implemented.<BR>
 *                            -- The clock has no restrictions on changing its
 *                            configuration or setting. Attempts to change a
 *                            restricted clock configuration or setting returns
 *                            DENIED.<BR>
 *                            Bit[0] Enabled/disabled.<BR>
 *                            If set to 1, the clock device is enabled.<BR>
 *                            If set to 0, the clock device is disabled
 * @param[out]    name        A NULL terminated ASCII string with the clock
 *                            name, of up to 16 bytes. When Bit[29] of
 *                            attributes field is set to 1, this field contains
 *                            the lower 15 bytes of the NULL terminated clock
 *                            name
 *
 * This function returns the attributes that are associated with a specific
 * clock. An agent might be allowed access to only a subset of the clocks
 * available in the system. The platform must thus guarantee that clocks that
 * an agent cannot access are not visible to it. The max name length is
 * ::SCMI_CLOCK_MAX_NAME. See section 4.6.2.5 CLOCK_ATTRIBUTES in the
 * [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_CLOCK_ATTR_CHANGE() - Clock rate change notifications support
 * - ::SCMI_CLOCK_ATTR_CHANGE_REQ() - Clock rate change requested notifications
 *   support
 * - ::SCMI_CLOCK_ATTR_EXT_NAME() - Extended Clock name
 * - ::SCMI_CLOCK_ATTR_PARENT() - Parent clock identifier support
 * - ::SCMI_CLOCK_ATTR_EXT_CONFIG() - Extended configuration support
 * - ::SCMI_CLOCK_ATTR_RESTRICTED() - Restricted clock
 * - ::SCMI_CLOCK_ATTR_ENABLED() - Enabled/disabled
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if valid clock attributes are returned.
 * - ::SCMI_ERR_NOT_FOUND: if \a clockId does not point to a valid clock
 *   device.
 */
int32_t SCMI_ClockAttributes(uint32_t channel, uint32_t clockId,
    uint32_t *attributes, uint8_t *name);

/*!
 * Get clock rate description.
 *
 * @param[in]     channel        A2P channel for comms
 * @param[in]     clockId        Identifier for the clock device
 * @param[in]     rateIndex      Index to the first rate value. Will be first
 *                               described in the return rate array
 * @param[out]    numRatesFlags  Descriptor for the rates supported by this
 *                               clock.<BR>
 *                               Bits[31:16] Number of remaining rates. This
 *                               field should be 0 if Bit[12] is 1.<BR>
 *                               Bits[15:13] Reserved, must be zero.<BR>
 *                               Bit[12] Return format:<BR>
 *                               If this bit is set to 1, the Rate Array is a
 *                               triplet that constitutes a segment in the
 *                               following form:<BR>
 *                               rates[0] is the lowest physical rate that the
 *                               clock can synthesize in the segment.<BR>
 *                               rates[1] is the highest physical rate that the
 *                               clock can synthesize in the segment.<BR>
 *                               rates[2] is the step size between two
 *                               successive physical rates that the clock can
 *                               synthesize within the segment.<BR>
 *                               If this bit is set to 0, each element of the
 *                               rate array represents a discrete physical rate
 *                               that the clock can synthesize.<BR>
 *                               Bits[11:0] Number of rates that are returned
 *                               by this call. This field should be 3 if
 *                               Bit[12] is 1
 * @param[out]    rates          Rate array:<BR>
 *                               If Bit[12] of the numRatesFlags field is set
 *                               to 0, each array entry is composed of two
 *                               32-bit words and has the following format:<BR>
 *                               Lower word: Lower 32 bits of the physical rate
 *                               in Hertz.<BR>
 *                               Upper word: Upper 32 bits of the physical rate
 *                               in Hertz.<BR>
 *                               If Bit[12] of the numRatesFlags field is set
 *                               to 1, then each entry is a member of a segment
 *                               {lowest rate, highest rate, step size} as
 *                               described above.<BR>
 *                               N is specified by Bits[11:0] of numRatesFlags
 *                               field
 *
 * This function allows the agent to ascertain the valid rates to which the
 * clock can be set. On success, the function returns an array, which contains
 * a number of rate entries. Sometimes it might not be possible to return the
 * whole clock rate array with just one call. To solve this problem, the
 * interface allows multiple calls. It also returns the number of remaining
 * clock rates. The size of the array returned depends on the number of return
 * values a given transport can support. The max number is
 * ::SCMI_CLOCK_MAX_RATES.
 *
 * Clocks can support many rates and sometimes individually describing each
 * rate might be too onerous. In such cases, the function can return only the
 * lowest rate, the highest rate and the step size between two successive
 * physical rates that the clock device can synthesize.
 *
 * The clock rates returned by this call should be in numeric ascending order.
 * See section 4.6.2.6 CLOCK_DESCRIBE_RATES in the [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_CLOCK_NUM_RATE_FLAGS_REMAING_RATES() - Number of remaining rates
 * - ::SCMI_CLOCK_NUM_RATE_FLAGS_FORMAT() - Return format
 * - ::SCMI_CLOCK_NUM_RATE_FLAGS_NUM_RATES() - Number of rates that are
 *   returned by this call
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if valid clock rates were returned.
 * - ::SCMI_ERR_NOT_FOUND: if the clock identified by \a clockId does not
 *   exist.
 * - ::SCMI_ERR_OUT_OF_RANGE: if the rate_index is outside of valid range.
 */
int32_t SCMI_ClockDescribeRates(uint32_t channel, uint32_t clockId,
    uint32_t rateIndex, uint32_t *numRatesFlags, scmi_clock_rate_t *rates);

/*!
 * Set clock rate.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[in]     flags    Rate flags:<BR>
 *                         Bits[31:4] Reserved, must be zero.<BR>
 *                         Bits[3:2] Round up/down:<BR>
 *                         If Bit[3] is set to 1, the platform rounds up/down
 *                         autonomously to choose a physical rate closest to
 *                         the requested rate, and Bit[2] is ignored.<BR>
 *                         If Bit[3] is set to 0, the platform:<BR>
 *                         -- rounds up if Bit[2] is set to 1<BR>
 *                         -- rounds down if Bit[2] is set to 0<BR>
 *                         Bit[1] Ignore delayed response:<BR>
 *                         If the Async flag, bit[0], is set to 1 and this bit
 *                         is set to 1, the platform does not send a
 *                         CLOCK_RATE_SET delayed response.<BR>
 *                         If the Async flag, bit[0], is set to 1 and this bit
 *                         is set to 0, the platform does send a CLOCK_RATE_SET
 *                         delayed response.<BR>
 *                         If the Async flag, bit[0], is set to 0, then this
 *                         bit field is ignored by the platform.<BR>
 *                         Bit[0] Async flag:<BR>
 *                         Set to 1 if clock rate is to be set asynchronously.
 *                         In this case the call is completed with
 *                         CLOCK_RATE_SET_COMPLETE message if bit[1] is set to
 *                         0. For more details, see section 4.6.3.1. A SUCCESS
 *                         return code in this case indicates that the platform
 *                         has successfully queued this function.<BR>
 *                         Set 0 to if the clock rate is to be set
 *                         synchronously. In this case, the call will return
 *                         when the clock rate setting has been completed
 * @param[in]     clockId  Identifier for the clock device
 * @param[in]     rate     Clock rate:<BR>
 *                         Lower word: Lower 32 bits of the physical rate in
 *                         Hertz.<BR>
 *                         Upper word: Upper 32 bits of the physical rate in
 *                         Hertz
 *
 * This function allows the caller to select the clock rate of a clock
 * synchronously or asynchronously. Nothing is aggregated and one rate exists
 * per clock.
 *
 * The function returns when the clock rate has been changed. If a clock is in
 * disabled state, the new rate takes effect when the clock has been
 * re-enabled. An example rounding value is ::SCMI_CLOCK_ROUND_DOWN. See
 * section 4.6.2.7 CLOCK_RATE_SET in the [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_CLOCK_RATE_FLAGS_ROUND() - Round up/down
 * - ::SCMI_CLOCK_RATE_FLAGS_NO_RESP() - Ignore delayed response
 * - ::SCMI_CLOCK_RATE_FLAGS_ASYNC() - Async flag
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the clock rate was set successfully for a
 *   synchronous request or if the function was successfully enqueued for an
 *   asynchronous request.
 * - ::SCMI_ERR_NOT_FOUND: if the clock identified by \a clockId does not
 *   exist.
 * - ::SCMI_ERR_INVALID_PARAMETERS: if the requested rate is not supported by
 *   the clock, or the flags parameter specifies invalid or illegal options.
 *   Might also be returned if power/clock conditions not met to allow setting
 *   of the rate.
 * - ::SCMI_ERR_BUSY: if there are too many asynchronous clock rate changes
 *   pending. The PROTOCOL_ATTRIBUTES function provides the maximum number of
 *   pending asynchronous clock rate changes supported by the platform.
 * - ::SCMI_ERR_DENIED: if the clock rate cannot be set because of
 *   dependencies, e.g. if there are other users of the clock.
 */
int32_t SCMI_ClockRateSet(uint32_t channel, uint32_t clockId,
    uint32_t flags, scmi_clock_rate_t rate);

/*!
 * Get clock rate.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[in]     clockId  Identifier for the clock device
 * @param[out]    rate     Clock rate:<BR>
 *                         Lower word: Lower 32 bits of the physical rate in
 *                         Hertz.<BR>
 *                         Upper word: Upper 32 bits of the physical rate in
 *                         Hertz
 *
 * This function allows the calling agent to request the current clock rate. If
 * the clock is in disabled state, this function returns the rate at which the
 * clock device would be subsequently running when it has been re-enabled. See
 * section 4.6.2.8 CLOCK_RATE_GET in the [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the current clock rate was successfully returned.
 * - ::SCMI_ERR_NOT_FOUND: if the clock identified by \a clockId does not
 *   exist.
 * - ::SCMI_ERR_INVALID_PARAMETERS: if power/clock conditions not met to
 *   allow getting the rate.
 */
int32_t SCMI_ClockRateGet(uint32_t channel, uint32_t clockId,
    scmi_clock_rate_t *rate);

/*!
 * Set clock configuration.
 *
 * @param[in]     channel            A2P channel for comms
 * @param[in]     clockId            Identifier for the clock device
 * @param[in]     attributes         Config attributes:<BR>
 *                                   Bits[31:24] Reserved, must be zero.<BR>
 *                                   Bits[23:16] Extended config type.<BR>
 *                                   A value of 0 indicates that this field is
 *                                   unused.<BR>
 *                                   Bits[15:2] Reserved, must be zero.<BR>
 *                                   Bits[1:0] Enable/Disable:<BR>
 *                                   If set to 3, the state of the clock device
 *                                   is unchanged. It is invalid to use this
 *                                   value if Bits[23:16] is set to 0.<BR>
 *                                   The value of 2 is reserved for future
 *                                   use.<BR>
 *                                   If set to 1, the clock device is to be
 *                                   enabled.<BR>
 *                                   If set to 0, the clock device is to be
 *                                   disabled
 * @param[in]     extendedConfigVal  Extended config value:  corresponds to the
 *                                   extended configuration type specified by
 *                                   Bits[23:16] of attributes field.<BR>
 *                                   This field is used to set extended
 *                                   configuration of the clock device. It can
 *                                   be ignored if extended config type
 *                                   specified by Bits[23:16] of the attributes
 *                                   field is set to 0
 *
 * This function allows the calling agent to configure a clock device.
 * Enable/disable is aggregated so each agent can set. Clock is enabled if any
 * agents request it be enabled. See section 4.6.2.9 CLOCK_CONFIG_SET in the
 * [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_CLOCK_CONFIG_SET_EXT_CONFIG() - Extended config type
 * - ::SCMI_CLOCK_CONFIG_SET_ENABLE() - Enable/disable state
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the clock configuration has been set successfully.
 * - ::SCMI_ERR_NOT_FOUND: if the clock identified by \a clockId does not
 *   exist.
 * - ::SCMI_ERR_INVALID_PARAMETERS, if the input attributes flag specifies
 *   unsupported or invalid configurations. Might also be returned if
 *   power/clock conditions not met to allow configurating the clock.
 * - ::SCMI_ERR_DENIED: if the clock config cannot be set because of lack of
 *   permissions.
 */
int32_t SCMI_ClockConfigSet(uint32_t channel, uint32_t clockId,
    uint32_t attributes, uint32_t extendedConfigVal);

/*!
 * Get clock configuration.
 *
 * @param[in]     channel            A2P channel for comms
 * @param[in]     clockId            Identifier for the clock device
 * @param[in]     flags              Config flags:<BR>
 *                                   Bits[31:8] Reserved, must be zero.<BR>
 *                                   Bits[7:0] Extended config type.<BR>
 *                                   Value of 0 indicates that this field is
 *                                   unused
 * @param[out]    attributes         Reserved, must be zero
 * @param[out]    config             Config:<BR>
 *                                   Bits[31:1] Reserved, must be zero.<BR>
 *                                   Bit[0] Enable/Disable If set to 1, the
 *                                   clock device is enabled.<BR>
 *                                   If set to 0, the clock device is disabled
 * @param[out]    extendedConfigVal  Extended config value: corresponds to the
 *                                   extended configuration type specified by
 *                                   Bits[7:0] of the attributes field of the
 *                                   command.<BR>
 *                                   This field is ignored if the extended
 *                                   config type field specified by Bits[7:0]
 *                                   of the attributes field of the command is
 *                                   set to 0
 *
 * This function allows the calling agent to get the configuration of a clock
 * device. See section 4.6.2.10 CLOCK_CONFIG_GET in the [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_CLOCK_CONFIG_FLAGS_EXT_CONFIG() - Extended  config type
 * - ::SCMI_CLOCK_CONFIG_GET_ENABLE() - Enable/Disable
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the clock configuration has been successfully
 *   returned.
 * - ::SCMI_ERR_NOT_FOUND: if the clock identified by \a clockId does not
 *   exist.
 * - ::SCMI_ERR_INVALID_PARAMETERS, if the input attributes flag specifies
 *   unsupported or invalid configurations. Might also be returned if
 *   power/clock conditions not met to allow getting the configuration.
 */
int32_t SCMI_ClockConfigGet(uint32_t channel, uint32_t clockId,
    uint32_t flags, uint32_t *attributes, uint32_t *config,
    uint32_t *extendedConfigVal);

/*!
 * Get all possible parents.
 *
 * @param[in]     channel          A2P channel for comms
 * @param[in]     clockId          Identifier for the clock device
 * @param[in]     skipParents      The number of parents to skip over: those
 *                                 before returning the first possible parent
 *                                 in the return parent array
 * @param[out]    numParentsFlags  Descriptor for the possible parents for this
 *                                 clock.<BR>
 *                                 Bits[31:24] Number of remaining parents.<BR>
 *                                 Bits[23:8] Reserved, must be zero.<BR>
 *                                 Bits[7:0] Number of parent clock identifiers
 *                                 that are returned by this call
 * @param[out]    parents          Array of parents
 *
 * This function allows the calling agent to get all the possible parents of a
 * clock device. This function is useful in constructing a clock topology when
 * changing the parent clock of a clock device is sometimes required due to
 * implementation defined considerations like jitter, power, or other factors.
 * The max number of parents is ::SCMI_CLOCK_MAX_PARENTS. See section 4.6.2.14
 * CLOCK_POSSIBLE_PARENTS_GET in the [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_CLOCK_NUM_PARENT_FLAGS_REMAING_PARENTS() - Number of remaining
 *   parents
 * - ::SCMI_CLOCK_NUM_PARENT_FLAGS_NUM_PARENTS() - Number of parent clock
 *   identifiers that are returned by this call
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the possible clock parents have been successfully
 *   returned.
 * - ::SCMI_ERR_NOT_FOUND: if the clock identified by clock_id does not
 *   exist.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the request is not supported.
 * - ::SCMI_ERR_DENIED: if the calling agent is not allowed to get the
 *   possible parents.
 */
int32_t SCMI_ClockPossibleParentsGet(uint32_t channel, uint32_t clockId,
    uint32_t skipParents, uint32_t *numParentsFlags, uint32_t *parents);

/*!
 * Set clock parent.
 *
 * @param[in]     channel   A2P channel for comms
 * @param[in]     clockId   Identifier for the clock device
 * @param[in]     parentId  Identifier for the parent: aka clock device to set
 *                          as the parent of the clock specified by \a clockId
 *
 * This function allows the calling agent to change the parent of a clock
 * device. This function does not result in a change of the configured clock
 * rate, or the range of clock rates supported by its children clock devices.
 * However, in some cases changing the parent of a clock device might not be
 * possible without implicitly affecting other children clock devices sharing
 * the same parent. In these cases, it is recommended that all children clock
 * devices affected by this change should be explicitly disabled by the agent
 * and configured to the expected properties that the new parent supports,
 * before sending this function. See section 4.6.2.15 CLOCK_PARENT_SET in the
 * [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the clock parent has been set successfully.
 * - ::SCMI_ERR_NOT_FOUND: if the clock identified by \a clockId or \a
 *   parentId does not exist.
 * - ::SCMI_ERR_INVALID_PARAMETERS, if the parent is not an option for the
 *   specified clock.
 * - ::SCMI_ERR_OUT_OF_RANGE: changing the parent clock is not possible
 *   because of inability to maintain child clock requirements.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the request is not supported.
 * - ::SCMI_ERR_DENIED: if the calling agent is not allowed to set the
 *   parent.
 */
int32_t SCMI_ClockParentSet(uint32_t channel, uint32_t clockId,
    uint32_t parentId);

/*!
 * Get clock parent.
 *
 * @param[in]     channel   A2P channel for comms
 * @param[in]     clockId   Identifier for the clock device
 * @param[out]    parentId  Identifier for the parent: aka clock device to set
 *                          as the parent of the clock specified by \a clockId
 *
 * This function allows the calling agent to get the current parent of a clock
 * device. See section 4.6.2.16 CLOCK_PARENT_GET in the [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the clock parent has been successfully returned.
 * - ::SCMI_ERR_NOT_FOUND: if the clock identified by \a clockId does not
 *   exist.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the request is not supported.
 * - ::SCMI_ERR_DENIED: f the calling agent is not allowed to get the parent.
 */
int32_t SCMI_ClockParentGet(uint32_t channel, uint32_t clockId,
    uint32_t *parentId);

/*!
 * Get clock permissions.
 *
 * @param[in]     channel      A2P channel for comms
 * @param[in]     clockId      Identifier for the clock device
 * @param[out]    permissions  Permissions:<BR>
 *                             Bit[31] Clock state control<BR>
 *                             Set to 1 if the clock can be disabled or enabled
 *                             by the agent.<BR>
 *                             Set to 0 if the clock state cannot be changed by
 *                             the agent. Attempts to change the clock state
 *                             using SCMI_ClockConfigSet() function returns
 *                             DENIED.<BR>
 *                             Bit[30] Clock parent control<BR>
 *                             Set to 1 if the clock parent can be changed by
 *                             the agent.<BR>
 *                             Set to 0 if the clock parent cannot be changed
 *                             by the agent. SCMI_ClockParentSet() function
 *                             returns DENIED.<BR>
 *                             Bit[29] Clock rate control<BR>
 *                             Set to 1 if the clock rate can be changed by the
 *                             agent.<BR>
 *                             Set to 0 if the clock rate cannot be changed by
 *                             the agent. SCMI_ClockRateSet() function returns
 *                             DENIED.<BR>
 *                              Bits[28:0] Reserved, must be zero
 *
 * An agent might be restricted from changing certain configuration or settings
 * of a clock. This function returns the restrictions that are associated with
 * a specific clock. See section 4.6.2.17 CLOCK_GET_PERMISSIONS in the
 * [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_CLOCK_PERM_STATE() - Clock state control
 * - ::SCMI_CLOCK_PERM_PARENT() - Clock parent control
 * - ::SCMI_CLOCK_PERM_RATE() - Clock rate control
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if valid clock permissions are returned.
 * - ::SCMI_ERR_NOT_FOUND: if the clock identified by \a clockId does not
 *   exist.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the request is not supported.
 */
int32_t SCMI_ClockGetPermissions(uint32_t channel, uint32_t clockId,
    uint32_t *permissions);

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
 * 4.6.2.2 NEGOTIATE_PROTOCOL_VERSION in the [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the negotiated protocol version is supported by the
 *   platform. All commands, responses, and notifications post successful
 *   return of this command must comply with the negotiated version.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the protocol version is not supported.
 */
int32_t SCMI_ClockNegotiateProtocolVersion(uint32_t channel,
    uint32_t version);

#endif /* SCMI_CLOCK_H */

/** @} */

