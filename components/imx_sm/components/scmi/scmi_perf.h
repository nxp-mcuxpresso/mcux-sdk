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

#ifndef SCMI_PERF_H
#define SCMI_PERF_H

/*!
 * @addtogroup scmi_proto_perf
 * @{
 */

/*!
 * @file
 * @brief Header file containing the client-side API for the System Control and
 * Management Interface (SCMI) perf protocol.
 */

/* Defines */

/*!
 * @name SCMI perf protocol message IDs
 */
/** @{ */
/*! Get performance domain attributes */
#define SCMI_MSG_PERFORMANCE_DOMAIN_ATTRIBUTES  0x3U
/*! Get performance level descriptions */
#define SCMI_MSG_PERFORMANCE_DESCRIBE_LEVELS    0x4U
/*! Set performance limits */
#define SCMI_MSG_PERFORMANCE_LIMITS_SET         0x5U
/*! Get performance limits */
#define SCMI_MSG_PERFORMANCE_LIMITS_GET         0x6U
/*! Set performance level */
#define SCMI_MSG_PERFORMANCE_LEVEL_SET          0x7U
/*! Get performance level */
#define SCMI_MSG_PERFORMANCE_LEVEL_GET          0x8U
/** @} */

/*!
 * @name SCMI max performance domain argument lengths
 */
/** @{ */
/*! Max length of the returned performance domain name */
#define SCMI_PERF_MAX_NAME        16U
/*! Max number of levels returned in one call */
#define SCMI_PERF_MAX_PERFLEVELS  SCMI_ARRAY(8U, scmi_perf_level_t)
/** @} */

/*!
 * @name SCMI actual performance argument lengths
 */
/** @{ */
/*! Actual number of levels returned */
#define SCMI_PERF_NUM_PERFLEVELS  SCMI_PERF_NUM_LEVELS_NUM_LEVELS(msgRx->numLevels)
/** @} */

/*!
 * @name SCMI performance power units
 */
/** @{ */
/*! Power consumption of performance levels is expressed in an abstract linear
    scale */
#define SCMI_PERF_POWER_UNIT_ABSTRACT  0U
/*! Power consumption of performance levels is expressed in mW */
#define SCMI_PERF_POWER_UNIT_MW        1U
/*! Power consumption of performance levels is expressed in uW */
#define SCMI_PERF_POWER_UNIT_UW        2U
/** @} */

/* Macros */

/*!
 * @name SCMI performance protocol attributes
 */
/** @{ */
/*! Power Unit */
#define SCMI_PERF_PROTO_ATTR_POWER_UNIT(x)   (((x) & 0x30000U) >> 16U)
/*! Number of performance domains */
#define SCMI_PERF_PROTO_ATTR_NUM_DOMAINS(x)  (((x) & 0xFFFFU) >> 0U)
/** @} */

/*!
 * @name SCMI performance message attributes
 */
/** @{ */
/*! FastChannel Support */
#define SCMI_PERF_MSG_ATTR_FAST(x)  (((x) & 0x1U) >> 0U)
/** @} */

/*!
 * @name SCMI performance domain attributes
 */
/** @{ */
/*! Can set limits */
#define SCMI_PERF_ATTR_LIMIT(x)         (((x) & 0x80000000U) >> 31U)
/*! Can set performance level */
#define SCMI_PERF_ATTR_LEVEL(x)         (((x) & 0x40000000U) >> 30U)
/*! Performance limits change notifications support */
#define SCMI_PERF_ATTR_LIMIT_NOTIFY(x)  (((x) & 0x20000000U) >> 29U)
/*! Performance level change notifications support */
#define SCMI_PERF_ATTR_LEVEL_NOTIFY(x)  (((x) & 0x10000000U) >> 28U)
/*! FastChannel Support */
#define SCMI_PERF_ATTR_FAST(x)          (((x) & 0x8000000U) >> 27U)
/*! Extended performance domain name */
#define SCMI_PERF_ATTR_EXT_NAME(x)      (((x) & 0x4000000U) >> 26U)
/*! Level Indexing Mode */
#define SCMI_PERF_ATTR_IDX_MODE(x)      (((x) & 0x2000000U) >> 25U)
/** @} */

/*!
 * @name SCMI performance domain rate limits
 */
/** @{ */
/*! Rate Limit in microseconds, indicating the minimum time required between
    successive requests */
#define SCMI_PERF_RATE_LIMIT_USECONDS(x)  (((x) & 0xFFFFFU) >> 0U)
/** @} */

/*!
 * @name SCMI performance num levels
 */
/** @{ */
/*! Number of remaining performance levels */
#define SCMI_PERF_NUM_LEVELS_REMAING_LEVELS(x)  (((x) & 0xFFFF0000U) >> 16U)
/*! Number of performance levels that are returned by this call */
#define SCMI_PERF_NUM_LEVELS_NUM_LEVELS(x)      (((x) & 0xFFFU) >> 0U)
/** @} */

/*!
 * @name SCMI performance level attributes
 */
/** @{ */
/*! Worst-case transition latency in microseconds to move from any supported
    performance to the level indicated by this entry in the array */
#define SCMI_PERF_LEVEL_ATTR_LATENCY(x)  (((x) & 0xFFFFU) >> 0U)
/** @} */

/* Types */

/*!
 * SCMI performance level
 */
typedef struct
{
    /*! Performance level value */
    uint32_t value;
    /*! Power cost */
    uint32_t powerCost;
    /*! Attributes */
    uint32_t attributes;
    /*! Indicative Frequency */
    uint32_t indicativeFrequency;
    /*! Level Index */
    uint32_t levelIndex;
} scmi_perf_level_t;

/* Functions */

/*!
 * Get protocol version.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[out]    version  Protocol version. For this revision of the
 *                         specification, this value must be 0x40000
 *
 * On success, this function returns the version of this protocol. For this
 * version of the specification, the value returned must be 0x40000, which
 * corresponds to version 4.0. See section 4.5.3.1 PROTOCOL_VERSION in the
 * [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_PerfProtocolVersion(uint32_t channel, uint32_t *version);

/*!
 * Get protocol attributes.
 *
 * @param[in]     channel                A2P channel for comms
 * @param[out]    attributes             Protocol attributes:<BR>
 *                                       Bits[31:18] Reserved, must be
 *                                       zero.<BR>
 *                                       Bits[17:16] Power Unit:<BR>
 *                                       Set to 2 if the power consumption of
 *                                       performance levels is expressed in
 *                                       uW.<BR>
 *                                       Set to 1 if the power consumption of
 *                                       performance levels is expressed in
 *                                       mW.<BR>
 *                                       Set to 0 if the power consumption of
 *                                       performance levels is expressed in an
 *                                       abstract linear scale.<BR>
 *                                       All other values are reserved and must
 *                                       not be used.<BR>
 *                                       Bits[15:0] Number of performance
 *                                       domains
 * @param[out]    statisticsAddressLow   Low address: The lower 32 bits of the
 *                                       physical address where the statistics
 *                                       shared memory region is located. This
 *                                       value should be 64-bit aligned. The
 *                                       address must be in the memory map of
 *                                       the calling agent. If the
 *                                       statisticsLen field is 0, then this
 *                                       field is invalid and must be ignored
 * @param[out]    statisticsAddressHigh  High address: The upper 32 bit of the
 *                                       physical address where the shared
 *                                       memory region is located. The address
 *                                       must be in the memory map of the
 *                                       calling agent. If the statisticsLen
 *                                       field is 0, then this field is invalid
 *                                       and must be ignored
 * @param[out]    statisticsLen          The length in bytes of the shared
 *                                       memory region. A value of 0 in this
 *                                       field indicates that the platform does
 *                                       not support the statistics shared
 *                                       memory region
 *
 * This function returns the attributes associated with this protocol. See
 * section 4.5.3.3 PROTOCOL_ATTRIBUTES in the [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_PERF_PROTO_ATTR_POWER_UNIT() - Power Unit
 * - ::SCMI_PERF_PROTO_ATTR_NUM_DOMAINS() - Number of performance domains
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_PerfProtocolAttributes(uint32_t channel, uint32_t *attributes,
    uint32_t *statisticsAddressLow, uint32_t *statisticsAddressHigh,
    uint32_t *statisticsLen);

/*!
 * Get protocol message attributes.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in]     messageId   Message ID of the message
 * @param[out]    attributes  Flags associated with a specific function in the
 *                            protocol.<BR>
 *                            Bits[31:1] Reserved, must be zero.<BR>
 *                            Bit[0] FastChannel Support.<BR>
 *                            Set to 1 if there is at least one dedicated
 *                            FastChannel available for this message.<BR>
 *                            Set to 0 if this there are no FastChannels
 *                            available this message
 *
 * On success, this function returns the implementation details associated with
 * a specific message in this protocol. An example message ID is
 * ::SCMI_MSG_PERFORMANCE_DOMAIN_ATTRIBUTES. See section 4.5.3.4
 * PROTOCOL_MESSAGE_ATTRIBUTES in the [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_PERF_MSG_ATTR_FAST() - FastChannel Support
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: in case the message is implemented and available to
 *   use.
 * - ::SCMI_ERR_NOT_FOUND: if the message identified by \a messageId is
 *   invalid or not provided by this platform implementation.
 */
int32_t SCMI_PerfProtocolMessageAttributes(uint32_t channel,
    uint32_t messageId, uint32_t *attributes);

/*!
 * Get performance domain attributes.
 *
 * @param[in]     channel             A2P channel for comms
 * @param[in]     domainId            Identifier for the performance domain
 * @param[out]    attributes          Domain attributes:<BR>
 *                                    Bit[31] Can set limits.<BR>
 *                                    Set to 1 if calling agent is allowed to
 *                                    set the performance limits on the
 *                                    domain.<BR>
 *                                    Set to 0 if a calling agent is not
 *                                    allowed to set limits on the performance
 *                                    limits on the domain.<BR>
 *                                    Bit[30] Can set performance level.<BR>
 *                                    Set to 1 if calling agent is allowed to
 *                                    set the performance of a domain.<BR>
 *                                    Set to 0 if a calling agent is not
 *                                    allowed to set the performance of a
 *                                    domain.<BR>
 *                                    Only one agent can set the performance of
 *                                    a given domain.<BR>
 *                                    Bit[29] Performance limits change
 *                                    notifications support.<BR>
 *                                    Set to 1 if performance limits change
 *                                    notifications are supported for this
 *                                    domain.<BR>
 *                                    Set to 0 if performance limits change
 *                                    notifications are not supported for this
 *                                    domain.<BR>
 *                                    Bit[28] Performance level change
 *                                    notifications support.<BR>
 *                                    Set to 1 if performance level change
 *                                    notifications are supported for this
 *                                    domain.<BR>
 *                                    Set to 0 if performance level change
 *                                    notifications are not supported for this
 *                                    domain.<BR>
 *                                    Bit[27] FastChannel Support.<BR>
 *                                    Set to 1 if there is at least one
 *                                    FastChannel available for this
 *                                    domain.<BR>
 *                                    Set to 0 if there are no FastChannels
 *                                    available for this domain.<BR>
 *                                    Bit[26] Extended performance domain
 *                                    name.<BR>
 *                                    If set to 1, the performance domain name
 *                                    is greater than 16 bytes.<BR>
 *                                    If set to 0, extended performance domain
 *                                    name is not supported.<BR>
 *                                    Bit[25] Level Indexing Mode.<BR>
 *                                    If set to 1, it indicates that the
 *                                    platform uses Level Indexing Mode. All
 *                                    functions which utilize performance level
 *                                    as a parameter need to specify the
 *                                    corresponding level index instead of the
 *                                    performance level when Level Indexing
 *                                    Mode is used.<BR>
 *                                    If set to 0, Level Indexing Mode is not
 *                                    used.<BR>
 *                                    Bits[24:0] Reserved and set to zero
 * @param[out]    rateLimit           Rate limit:<BR>
 *                                    Bits[31:20] Reserved and set to zero.<BR>
 *                                    Bits[19:0] Rate Limit in microseconds,
 *                                    indicating the minimum time required
 *                                    between successive requests. A value of 0
 *                                    indicates that this field is not
 *                                    supported by the platform. This field
 *                                    does not apply to FastChannels
 * @param[out]    sustainedFreq       Base frequency:  corresponds to the
 *                                    sustained performance level. Expressed in
 *                                    units of kHz
 * @param[out]    sustainedPerfLevel  Sustained performance: performance level
 *                                    value that corresponds to the sustained
 *                                    performance delivered by the platform
 * @param[out]    name                Null terminated ASCII string of up to 16
 *                                    bytes in length describing a domain name.
 *                                    When Bit[26] of attributes field is set
 *                                    to 1, this field contains the lower 15
 *                                    bytes of the NULL terminated performance
 *                                    domain name
 *
 * This function returns attributes that are specific to a given domain. The
 * max name length is ::SCMI_PERF_MAX_NAME. See section 4.5.3.5
 * PERFORMANCE_DOMAIN_ATTRIBUTES in the [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_PERF_ATTR_LIMIT() - Can set limits
 * - ::SCMI_PERF_ATTR_LEVEL() - Can set performance level
 * - ::SCMI_PERF_ATTR_LIMIT_NOTIFY() - Performance limits change notifications
 *   support
 * - ::SCMI_PERF_ATTR_LEVEL_NOTIFY() - Performance level change notifications
 *   support
 * - ::SCMI_PERF_ATTR_FAST() - FastChannel Support
 * - ::SCMI_PERF_ATTR_EXT_NAME() - Extended performance domain name
 * - ::SCMI_PERF_ATTR_IDX_MODE() - Level Indexing Mode
 * - ::SCMI_PERF_RATE_LIMIT_USECONDS() - Rate Limit in microseconds, indicating
 *   the minimum time required between successive requests
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if valid performance domain attributes are found.
 * - ::SCMI_ERR_NOT_FOUND: if domainId does not point to a valid domain.
 */
int32_t SCMI_PerformanceDomainAttributes(uint32_t channel,
    uint32_t domainId, uint32_t *attributes, uint32_t *rateLimit,
    uint32_t *sustainedFreq, uint32_t *sustainedPerfLevel, uint8_t *name);

/*!
 * Get performance level descriptions.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in]     domainId    Identifier for the performance domain
 * @param[in]     skipIndex   Index to the first level: Number of performance
 *                            levels, in numerically ascending order of level
 *                            values, to skip over before returning the first
 *                            performance level in the return performance level
 *                            array
 * @param[out]    numLevels   Number of levels:<BR>
 *                            Bits[31:16] Number of remaining performance
 *                            levels.<BR>
 *                            Bits[15:12] Reserved, must be zero.<BR>
 *                            Bits[11:0] Number of performance levels that are
 *                            returned by this call
 * @param[out]    perfLevels  Array of performance levels: numeric ascending
 *                            order, to be described. N is specified by
 *                            Bits[11:0] of numLevels field. Each array entry
 *                            is composed of three 32-bit words with the
 *                            following format:<BR>
 *                            uint32 entry[0] Performance level value.<BR>
 *                            uint32 entry[1] Power cost.<BR>
 *                            A value of zero indicates that the power cost is
 *                            not reported by the platform.<BR>
 *                            uint32 entry[2] Attributes<BR>
 *                            Bits[31:16] Reserved, must be zero.<BR>
 *                            Bits[15:0] Worst-case transition latency in
 *                            microseconds to move from any supported
 *                            performance to the level indicated by this entry
 *                            in the array
 *
 * This function allows the agent to ascertain the discrete performance levels
 * that are supported by the platform, their respective power costs, transition
 * latency, clock frequency and level index. On success, the function returns
 * an array that consists of several performance level entries, each of which
 * describes an expected performance, power cost, transition latency, clock
 * frequency and level index. The performance levels returned by this call
 * should be in numerically ascending order of performance level values. The
 * power cost can be expressed in microwatts, milliwatts or on an abstract
 * scale (e.g. ::SCMI_PERF_POWER_UNIT_ABSTRACT). How the numbers in that scale
 * convert to the actual wattage is IMPLEMENTATION DEFINED, but the conversion
 * must be linear, meaning that a power of 2X is twice the power of X. The size
 * of the array depends on the number of return values that a given transport
 * can support. The max number is ::SCMI_PERF_MAX_PERFLEVELS. It might not be
 * possible to return information for all performance levels with just one
 * call. To solve this problem, the interface allows multiple calls, with a \a
 * skipIndex used to skip over performance levels which were returned by
 * previous calls. See section 4.5.3.6 PERFORMANCE_DESCRIBE_LEVELS in the
 * [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_PERF_NUM_LEVELS_REMAING_LEVELS() - Number of remaining performance
 *   levels
 * - ::SCMI_PERF_NUM_LEVELS_NUM_LEVELS() - Number of performance levels that
 *   are returned by this call
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if valid performance levels are returned.
 * - ::SCMI_ERR_NOT_FOUND: if domainId does not point to a valid domain.
 * - ::SCMI_ERR_OUT_OF_RANGE: if \a levelIndex is out of range.
 */
int32_t SCMI_PerformanceDescribeLevels(uint32_t channel, uint32_t domainId,
    uint32_t skipIndex, uint32_t *numLevels, scmi_perf_level_t *perfLevels);

/*!
 * Set performance limits.
 *
 * @param[in]     channel   A2P channel for comms
 * @param[in]     domainId  Identifier for the performance domain
 * @param[in]     rangeMax  Maximum allowed performance level, or level
 *                          index.<BR>
 *                          If this field is set to 0, the platform ignores it
 *                          and any pre-existing limit on maximum allowed
 *                          performance level is left unchanged. Both rangeMax
 *                          and rangeMin cannot be zero at the same time
 * @param[in]     rangeMin  Minimum allowed performance level, or level
 *                          index.<BR>
 *                          If this field is set to 0, the platform ignores it
 *                          and any pre-existing limit on minimum allowed
 *                          performance level is left unchanged. Both rangeMax
 *                          and rangeMin cannot be zero at the same time
 *
 * This function allows the caller to set limits on the performance level of a
 * domain. Each agent can set a limit and the results are aggregated. Limits
 * will be set to the minimum range to satisfy all settings. If Level Indexing
 * Mode is used by the platform, the limits must be specified in level index
 * instead of the corresponding performance level. See section 4.5.3.7
 * PERFORMANCE_LIMITS_SET in the [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the function successfully set the limits of
 *   operation. If setting a limit requires modifying the current performance
 *   level of the domain, the function can return before this change has been
 *   completed. However, the change in performance level must still take place.
 * - ::SCMI_ERR_NOT_FOUND: if the performance domain identified by domainId
 *   does not exist.
 * - ::SCMI_ERR_OUT_OF_RANGE: if the limits set lie outside the highest and
 *   lowest performance levels that are described by
 *   PERFORMANCE_DESCRIBED_LEVELS, or if rangeMax and rangeMin are both zero.
 * - ::SCMI_ERR_DENIED: if the calling agent is not permitted to change the
 *   performance limits for the domain, as described by
 *   PERFORMANCE_DOMAIN_ATTRIBUTES.
 */
int32_t SCMI_PerformanceLimitsSet(uint32_t channel, uint32_t domainId,
    uint32_t rangeMax, uint32_t rangeMin);

/*!
 * Get performance limits.
 *
 * @param[in]     channel   A2P channel for comms
 * @param[in]     domainId  Identifier for the performance domain
 * @param[out]    rangeMax  Maximum allowed performance level, or level index
 * @param[out]    rangeMin  Minimum allowed performance level, or level index
 *
 * This function allows the agent to ascertain the range of allowed performance
 * levels, or level indices when Level Indexing Mode is used by the platform.
 * The returned value reflects the currently set limits for the performance
 * domain. These limits might have been set implicitly by the platform, or
 * explicitly by a preceding call to PERFORMANCE_LIMIT_SET.
 *
 * On success, the range return value provides the minimum and maximum allowed
 * performance level, or level index. One level is supported per LM. Results
 * are minimum performance to meet the requirements of all LM. See section
 * 4.5.3.8 PERFORMANCE_LIMITS_GET in the [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the performance limits are returned successfully.
 * - ::SCMI_ERR_NOT_FOUND: if domainId does not point to a valid domain.
 */
int32_t SCMI_PerformanceLimitsGet(uint32_t channel, uint32_t domainId,
    uint32_t *rangeMax, uint32_t *rangeMin);

/*!
 * Set performance level.
 *
 * @param[in]     channel           A2P channel for comms
 * @param[in]     domainId          Identifier for the performance domain
 * @param[in]     performanceLevel  Requested performance level, or level index
 *
 * This function allows the agent to set the performance level of a domain. If
 * Level Indexing Mode is used, the limits must be specified in level index
 * instead of the corresponding performance level. This function can return
 * before the domain has transitioned to the required performance level. The
 * platform simply has to acknowledge that it has received the function. See
 * section 4.5.3.9 PERFORMANCE_LEVEL_SET in the [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the platform has accepted the function and
 *   scheduled it for processing.
 * - ::SCMI_ERR_NOT_FOUND: if the domainId parameter does not point to a
 *   valid domain.
 * - ::SCMI_ERR_OUT_OF_RANGE: if the requested performance level is outside
 *   the currently allowed range.
 * - ::SCMI_ERR_DENIED: if the calling agent is not permitted to change the
 *   performance level for a domain, as described by
 *   PERFORMANCE_DOMAIN_ATTRIBUTES.
 */
int32_t SCMI_PerformanceLevelSet(uint32_t channel, uint32_t domainId,
    uint32_t performanceLevel);

/*!
 * Get performance level.
 *
 * @param[in]     channel           A2P channel for comms
 * @param[in]     domainId          Identifier for the performance domain
 * @param[out]    performanceLevel  Current performance level, or level index,
 *                                  of the domain
 *
 * On success, this function returns the current performance level of a domain,
 * or level index when Level Indexing Mode is used by the platform. Note the
 * performance level value that is returned by this function might be stale by
 * the time the function completes, as a subsequent performance change might
 * have been initiated in the meantime. See section 4.5.3.10
 * PERFORMANCE_LEVEL_GET in the [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the performance level is returned successfully
 * - ::SCMI_ERR_NOT_FOUND: if domainId does not point to a valid domain.
 */
int32_t SCMI_PerformanceLevelGet(uint32_t channel, uint32_t domainId,
    uint32_t *performanceLevel);

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
 * 4.5.3.2 NEGOTIATE_PROTOCOL_VERSION in the [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the negotiated protocol version is supported by the
 *   platform. All commands, responses, and notifications post successful
 *   return of this command must comply with the negotiated version.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the protocol version is not supported.
 */
int32_t SCMI_PerfNegotiateProtocolVersion(uint32_t channel,
    uint32_t version);

#endif /* SCMI_PERF_H */

/** @} */

