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

#ifndef SCMI_SENSOR_H
#define SCMI_SENSOR_H

/*!
 * @addtogroup scmi_proto_sensor
 * @{
 */

/*!
 * @file
 * @brief Header file containing the client-side API for the System Control and
 * Management Interface (SCMI) sensor protocol.
 */

/* Defines */

/*!
 * @name SCMI sensor protocol message IDs
 */
/** @{ */
/*! Get sensor descriptors */
#define SCMI_MSG_SENSOR_DESCRIPTION_GET    0x3U
/*! Configure sensor trip point notification */
#define SCMI_MSG_SENSOR_TRIP_POINT_NOTIFY  0x4U
/*! Configure sensor trip point */
#define SCMI_MSG_SENSOR_TRIP_POINT_CONFIG  0x5U
/*! Read sensor */
#define SCMI_MSG_SENSOR_READING_GET        0x6U
/*! Get sensor configuration */
#define SCMI_MSG_SENSOR_CONFIG_GET         0x9U
/*! Set sensor configuration */
#define SCMI_MSG_SENSOR_CONFIG_SET         0xAU
/*! Read sensor event */
#define SCMI_MSG_SENSOR_TRIP_POINT_EVENT   0x0U
/** @} */

/*!
 * @name SCMI max sensor argument lengths
 */
/** @{ */
/*! Max length of the returned sensor name */
#define SCMI_SENSOR_MAX_NAME      16U
/*! Max number of descriptors returned in one call */
#define SCMI_SENSOR_MAX_DESC      SCMI_ARRAY(8U, scmi_sensor_desc_t)
/*! Max number of readings returned in one call */
#define SCMI_SENSOR_MAX_READINGS  SCMI_ARRAY(4U, scmi_sensor_reading_t)
/** @} */

/*!
 * @name SCMI actual sensor argument lengths
 */
/** @{ */
/*! Actual number of descriptors returned */
#define SCMI_SENSOR_NUM_DESC      SCMI_SENSOR_NUM_SENSOR_FLAGS_NUM_DESCS(msgRx->numSensorFlags)
/*! Actual number of readings returned */
#define SCMI_SENSOR_NUM_READINGS  SCMI_SENSOR_MAX_READINGS
/** @} */

/*!
 * @name SCMI sensor TP events
 */
/** @{ */
/*! No event generation */
#define SCMI_SENSOR_TP_NONE  0U
/*! Event crossing positive direction */
#define SCMI_SENSOR_TP_POS   1U
/*! Event crossing negative direction */
#define SCMI_SENSOR_TP_NEG   2U
/*! Event crossed in either direction */
#define SCMI_SENSOR_TP_BOTH  3U
/** @} */

/* Macros */

/*!
 * @name SCMI sensor protocol attributes
 */
/** @{ */
/*! Maximum number of outstanding asynchronous functions that is supported by
    the platform */
#define SCMI_SENSOR_PROTO_ATTR_MAX_PENDING(x)  (((x) & 0xFF0000U) >> 16U)
/*! Number of sensors that is present and managed by the platform */
#define SCMI_SENSOR_PROTO_ATTR_NUM_SENSORS(x)  (((x) & 0xFFFFU) >> 0U)
/** @} */

/*!
 * @name SCMI num sensor flags
 */
/** @{ */
/*! Number of remaining sensor descriptors */
#define SCMI_SENSOR_NUM_SENSOR_FLAGS_REMAINING_DESCS(x)  (((x) & 0xFFFF0000U) >> 16U)
/*! Number of sensor descriptors that are returned by this current call */
#define SCMI_SENSOR_NUM_SENSOR_FLAGS_NUM_DESCS(x)        (((x) & 0xFFFU) >> 0U)
/** @} */

/*!
 * @name SCMI sensor attributes (low)
 */
/** @{ */
/*! Asynchronous sensor read support */
#define SCMI_SENSOR_ATTR_LOW_ASYNC(x)         (((x) & 0x80000000U) >> 31U)
/*! Continuous sensor update notification support */
#define SCMI_SENSOR_ATTR_LOW_CONTINUOUS(x)    (((x) & 0x40000000U) >> 30U)
/*! Extended sensor name */
#define SCMI_SENSOR_ATTR_LOW_EXT_NAME(x)      (((x) & 0x20000000U) >> 29U)
/*! Timestamp exponent */
#define SCMI_SENSOR_ATTR_LOW_TIME_EXP(x)      (((x) & 0x7C00U) >> 10U)
/*! Timestamp support */
#define SCMI_SENSOR_ATTR_LOW_TIME_SUPPORT(x)  (((x) & 0x200U) >> 9U)
/*! Extended attributes support */
#define SCMI_SENSOR_ATTR_LOW_EXT_ATTR(x)      (((x) & 0x100U) >> 8U)
/*! Number of trip points supported */
#define SCMI_SENSOR_ATTR_LOW_NUM_TP(x)        (((x) & 0xFFU) >> 0U)
/** @} */

/*!
 * @name SCMI sensor attributes (high)
 */
/** @{ */
/*! Number of axes */
#define SCMI_SENSOR_ATTR_HIGH_NUM_AXIS(x)      (((x) & 0x3F0000U) >> 16U)
/*! Exponent */
#define SCMI_SENSOR_ATTR_HIGH_SENSOR_EXP(x)    (((x) & 0xF800U) >> 11U)
/*! Axis support */
#define SCMI_SENSOR_ATTR_HIGH_AXIS_SUPPORT(x)  (((x) & 0x100U) >> 8U)
/*! SensorType */
#define SCMI_SENSOR_ATTR_HIGH_SENSOR_TYPE(x)   (((x) & 0xFFU) >> 0U)
/** @} */

/*!
 * @name SCMI sensor event control
 */
/** @{ */
/*! Controls generation of notifications on crossing of configured trip-points
 */
#define SCMI_SENSOR_EV_CTRL_ENABLE(x)  (((x) & 0x1U) << 0U)
/** @} */

/*!
 * @name SCMI sensor trip point event control
 */
/** @{ */
/*! Trip point ID */
#define SCMI_SENSOR_TP_EV_CTRL_TRIP_ID(x)  (((x) & 0xFFU) << 4U)
/*! Event control for the trip-point */
#define SCMI_SENSOR_TP_EV_CTRL(x)          (((x) & 0x3U) << 0U)
/** @} */

/*!
 * @name SCMI sensor read flags
 */
/** @{ */
/*! Async flag */
#define SCMI_SENSOR_READ_FLAGS_ASYNC(x)  (((x) & 0x1U) << 0U)
/** @} */

/*!
 * @name SCMI sensor config (get)
 */
/** @{ */
/*! Seconds */
#define SCMI_SENSOR_CONFIG_GET_UPDATE_INTV_SEC(x)  (((x) & 0xFFFF0000U) >> 16U)
/*! Twos complement format representing the power-of-10 multiplier that is
    applied to the sec field */
#define SCMI_SENSOR_CONFIG_GET_UPDATE_INTV_EXP(x)  (((x) & 0xF800U) >> 11U)
/*! Timestamp reporting */
#define SCMI_SENSOR_CONFIG_GET_TS_ENABLED(x)       (((x) & 0x2U) >> 1U)
/*! Sensor State */
#define SCMI_SENSOR_CONFIG_GET_ENABLED(x)          (((x) & 0x1U) >> 0U)
/** @} */

/*!
 * @name SCMI sensor config (set)
 */
/** @{ */
/*! Seconds */
#define SCMI_SENSOR_CONFIG_SET_UPDATE_INTV_SEC(x)  (((x) & 0xFFFFU) << 16U)
/*! Twos complement format representing the power-of-10 multiplier that is
    applied to the sec field */
#define SCMI_SENSOR_CONFIG_SET_UPDATE_INTV_EXP(x)  (((x) & 0x1FU) << 11U)
/*! Round up/down */
#define SCMI_SENSOR_CONFIG_SET_ROUND(x)            (((x) & 0x3U) << 9U)
/*! Timestamp reporting */
#define SCMI_SENSOR_CONFIG_SET_TS_ENABLE(x)        (((x) & 0x1U) << 1U)
/*! Sensor State */
#define SCMI_SENSOR_CONFIG_SET_ENABLE(x)           (((x) & 0x1U) << 0U)
/** @} */

/*!
 * @name SCMI sensor event description
 */
/** @{ */
/*! Direction */
#define SCMI_SENSOR_EVENT_DIRECTION(x)  (((x) & 0x10000U) >> 16U)
/*! The identifier for the trip point that was crossed or reached */
#define SCMI_SENSOR_EVENT_TP_ID(x)      (((x) & 0xFFU) >> 0U)
/** @} */

/* Types */

/*!
 * SCMI sensor descriptor
 */
typedef struct
{
    /*! Identifier for the sensor */
    uint32_t sensorId;
    /*! Lower 32 bit of the sensor attributes */
    uint32_t sensorAttributesLow;
    /*! Upper 32 bit of the sensor attributes */
    uint32_t sensorAttributesHigh;
    /*! A NULL terminated UTF-8 format string with the sensor name, of up to 16
        bytes */
    uint8_t name[16];
} scmi_sensor_desc_t;

/*!
 * SCMI sensor reading
 */
typedef struct
{
    /*! Lower 32 bits of the sensor value */
    int32_t sensorValueLow;
    /*! Higher 32 bits of the sensor value */
    int32_t sensorValueHigh;
    /*! Lower 32 bits of the timestamp */
    uint32_t timestampLow;
    /*! Higher 32 bits of the timestamp */
    uint32_t timestampHigh;
} scmi_sensor_reading_t;

/* Functions */

/*!
 * Get protocol version.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[out]    version  Protocol version. For this revision of the
 *                         specification, this value must be 0x30001
 *
 * On success, this function returns the version of this protocol. For this
 * version of the specification, the return value must be 0x30001, which
 * corresponds to version 3.1. See section 4.7.2.1 PROTOCOL_VERSION in the
 * [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_SensorProtocolVersion(uint32_t channel, uint32_t *version);

/*!
 * Get protocol attributes.
 *
 * @param[in]     channel               A2P channel for comms
 * @param[out]    attributes            Protocol attributes:<BR>
 *                                      Bits[31:24] Reserved, must be zero.<BR>
 *                                      Bits[23:16] Maximum number of
 *                                      outstanding asynchronous functions that
 *                                      is supported by the platform.<BR>
 *                                      Bits[15:0] Number of sensors that is
 *                                      present and managed by the platform
 * @param[out]    sensorRegAddressLow   Low address: This value indicates the
 *                                      lower 32 bits of the physical address
 *                                      where the sensor shared memory region
 *                                      is located. This value should be 64-bit
 *                                      aligned. The address must be in the
 *                                      memory map of the calling agent. If the
 *                                      sensorRegLen field is 0, then this
 *                                      field is invalid and must be ignored by
 *                                      the agent
 * @param[out]    sensorRegAddressHigh  High address: This value indicates the
 *                                      upper 32 bits of the physical address
 *                                      where the shared memory region is
 *                                      located. The address must be in the
 *                                      memory map of the calling agent. If the
 *                                      sensorRegLen field is 0, then this
 *                                      field is invalid and must be ignored by
 *                                      the agent
 * @param[out]    sensorRegLen          Stats length: This value indicates the
 *                                      length in bytes of the shared memory
 *                                      region. A value of 0 in this field
 *                                      indicates that the platform does not
 *                                      implement the sensor shared memory
 *
 * This function returns the implementation details associated with this
 * protocol. See section 4.7.2.3 PROTOCOL_ATTRIBUTES in the
 * [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_SENSOR_PROTO_ATTR_MAX_PENDING() - Maximum number of outstanding
 *   asynchronous functions that is supported by the platform
 * - ::SCMI_SENSOR_PROTO_ATTR_NUM_SENSORS() - Number of sensors that is present
 *   and managed by the platform
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_SensorProtocolAttributes(uint32_t channel,
    uint32_t *attributes, uint32_t *sensorRegAddressLow,
    uint32_t *sensorRegAddressHigh, uint32_t *sensorRegLen);

/*!
 * Get protocol message attributes.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in]     messageId   Message ID of the message
 * @param[out]    attributes  Message attributes. Attributes that are
 *                            associated with the message that is specified by
 *                            message ID. Currently, this field returns the
 *                            value of 0
 *
 * On success, this function returns the implementation details associated with
 * a specific message in this protocol.
 *
 * If the message is not supported or implemented by the platform, then this
 * function returns a SCMI_ERR_NOT_FOUND status code. This allows calling
 * agents to comprehend which functions are supported on a platform and
 * configure themselves accordingly. An example message ID is
 * ::SCMI_MSG_SENSOR_DESCRIPTION_GET. See section 4.7.2.4
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
int32_t SCMI_SensorProtocolMessageAttributes(uint32_t channel,
    uint32_t messageId, uint32_t *attributes);

/*!
 * Get sensor descriptors.
 *
 * @param[in]     channel         A2P channel for comms
 * @param[in]     descIndex       Descriptor index
 * @param[out]    numSensorFlags  Flags for number of sensors:<BR>
 *                                Bits[31:16] Number of remaining sensor
 *                                descriptors.<BR>
 *                                Bits[15:12] Reserved, must be zero.<BR>
 *                                Bits[11:0] Number of sensor descriptors that
 *                                are returned by this current call
 * @param[out]    desc            An array of sensor descriptors
 *
 * This function can be used for sensor discovery on the platform. On success,
 * it returns an array of sensor descriptors. Max number of
 * ::SCMI_SENSOR_MAX_DESC. The sensor descriptor structure describes the sensor
 * properties, such as the unique identifier for the sensor, its name, number
 * of axes, reading types and other characteristics. The max name length is
 * ::SCMI_SENSOR_MAX_NAME. See section 4.7.2.5 SENSOR_DESCRIPTION_GET in the
 * [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_SENSOR_NUM_SENSOR_FLAGS_REMAINING_DESCS() - Number of remaining
 *   sensor descriptors
 * - ::SCMI_SENSOR_NUM_SENSOR_FLAGS_NUM_DESCS() - Number of sensor descriptors
 *   that are returned by this current call
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the sensor description was returned successfully.
 * - ::SCMI_ERR_INVALID_PARAMETERS: if \a descIndex out of range.
 */
int32_t SCMI_SensorDescriptionGet(uint32_t channel, uint32_t descIndex,
    uint32_t *numSensorFlags, scmi_sensor_desc_t *desc);

/*!
 * Configure sensor trip point notification.
 *
 * @param[in]     channel             A2P channel for comms
 * @param[in]     sensorId            Identifier for the sensor
 * @param[in]     sensorEventControl  Event control:<BR>
 *                                    Bits[31:1] Reserved.<BR>
 *                                    Bit[0] Globally controls generation of
 *                                    notifications on crossing of configured
 *                                    trip-points pertaining to the specified
 *                                    sensor.<BR>
 *                                    If this bit is set to 1, notifications
 *                                    are sent whenever the sensor value
 *                                    crosses any of the trip-points that have
 *                                    been configured.<BR>
 *                                    If this bit is set to 0, no notifications
 *                                    are sent for any of the trip-points
 *
 * This function is used by the agent to globally control generation of
 * notifications on cross-over events for the trip-points that have been
 * configured using the SCMI_SensorTripPointConfig() function. See section
 * 4.7.2.8 SENSOR_TRIP_POINT_NOTIFY in the [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_SENSOR_EV_CTRL_ENABLE() - Controls generation of notifications on
 *   crossing of configured trip-points
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS.
 * - ::SCMI_ERR_NOT_FOUND: if \a sensorId does not point to an existing
 *   sensor.
 * - ::SCMI_ERR_INVALID_PARAMETERS: if the input \a sensorEventControl flag
 *   contains invalid or illegal settings.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the platform does not support trip point
 *   event notifications for the sensor.
 * - ::SCMI_ERR_DENIED: if the calling agent is not permitted to set a trip
 *   point on this sensor.
 */
int32_t SCMI_SensorTripPointNotify(uint32_t channel, uint32_t sensorId,
    uint32_t sensorEventControl);

/*!
 * Configure sensor trip point.
 *
 * @param[in]     channel           A2P channel for comms
 * @param[in]     sensorId          Identifier for the sensor
 * @param[in]     tripPointEvCtrl   Event control:<BR>
 *                                  Bits[31:12] Reserved.<BR>
 *                                  Bits[11:4] trip point ID: Identifier for
 *                                  the selected trip point. This value should
 *                                  be equal to or less than the total number
 *                                  of trip points that are supported by this
 *                                  sensor as advertised in its descriptor.<BR>
 *                                  Bits[3:2] Reserved for future use.<BR>
 *                                  Bits[1:0] Event control for the
 *                                  trip-point:<BR>
 *                                  If set to 0, disables event generation for
 *                                  this trip-point (this is the default
 *                                  state).<BR>
 *                                  If set to 1, enables event generation when
 *                                  this trip-point value is reached or crossed
 *                                  in a positive direction.<BR>
 *                                  If set to 2, enables event generation when
 *                                  this trip-point value is reached or crossed
 *                                  in a negative direction.<BR>
 *                                  If set to 3, enables event generation when
 *                                  this trip-point value is reached or crossed
 *                                  in either direction
 * @param[in]     tripPointValLow   Lower 32 bits of the sensor value:
 *                                  corresponds to this trip-point. The default
 *                                  value is 0
 * @param[in]     tripPointValHigh  Higher 32 bits of the sensor value:
 *                                  corresponds to this trip-point. The default
 *                                  value is 0
 *
 * This function is used for selecting and configuring a trip-point of
 * interest. Following the successful completion of this function, the platform
 * generates the SENSOR_TRIP_POINT_EVENT event
 *
 * System Control and Management Interface whenever the sensor value crosses
 * the programmed trip point value, provided notifications have been enabled
 * for trip-points globally using the SCMI_SensorTripPointNotify() function.
 *
 * Only one setting exists per sensor trip point. Nothing is aggregated across
 * agents or LM. See section 4.7.2.9 SENSOR_TRIP_POINT_CONFIG in the
 * [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_SENSOR_TP_EV_CTRL_TRIP_ID() - Trip point ID
 * - ::SCMI_SENSOR_TP_EV_CTRL() - Event control for the trip-point
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the sensor trip point was set successfully.
 * - ::SCMI_ERR_NOT_FOUND: if \a sensorId does not point to an existing
 *   sensor.
 * - ::SCMI_ERR_INVALID_PARAMETERS: if the input parameters specify incorrect
 *   or illegal values.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the platform does not support trip point
 *   event notifications for the sensor.
 * - ::SCMI_ERR_DENIED: if the calling agent is not permitted to set a trip
 *   point on this sensor.
 */
int32_t SCMI_SensorTripPointConfig(uint32_t channel, uint32_t sensorId,
    uint32_t tripPointEvCtrl, int32_t tripPointValLow,
    int32_t tripPointValHigh);

/*!
 * Read sensor.
 *
 * @param[in]     channel   A2P channel for comms
 * @param[in]     sensorId  Identifier for the sensor
 * @param[in]     flags     Read flags:<BR>
 *                          Bits[31:1] Reserved.<BR>
 *                          Bit[0] Async flag:<BR>
 *                          Set to 1 if the sensor is to be read
 *                          asynchronously.<BR>
 *                          Set to 0 to if the sensor is to be read
 *                          synchronously
 * @param[out]    readings  An array of sensor readings: where N is:<BR>
 *                          - 1 for sensors which measure scalar values.<BR>
 *                          - the number of sensor axes for sensors which
 *                          report values along axes. All axes should be
 *                          reported in order
 *
 * This function requests the platform to provide the current value of the
 * sensor that is represented by \a sensorId. The sensor should be in enabled
 * state before using this function. For synchronous mode of access, the
 * platform provides the sensor reading in the response to this function
 * itself. When the platform notices failure or fault conditions in the sensor
 * or its associated logic or circuitry, it returns the
 * ::SCMI_ERR_HARDWARE_ERROR status. The sensor reading structure provides the
 * sensor readings and the timestamp when they were collected. The max number
 * of readings is ::SCMI_SENSOR_MAX_READINGS. See section 4.7.2.12
 * SENSOR_READING_GET in the [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_SENSOR_READ_FLAGS_ASYNC() - Async flag
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the reading was successfully returned for a
 *   synchronous request or if the function was successfully enqueued for an
 *   asynchronous request.
 * - ::SCMI_ERR_NOT_FOUND: if \a sensorId does not point to an existing
 *   sensor.
 * - ::SCMI_ERR_INVALID_PARAMETERS: if the flags input specifies illegal or
 *   invalid settings.
 * - ::SCMI_ERR_PROTOCOL_ERROR: if the function is used to read updates from
 *   a disabled sensor.
 */
int32_t SCMI_SensorReadingGet(uint32_t channel, uint32_t sensorId,
    uint32_t flags, scmi_sensor_reading_t *readings);

/*!
 * Get sensor configuration.
 *
 * @param[in]     channel       A2P channel for comms
 * @param[in]     sensorId      Identifier for the sensor
 * @param[out]    sensorConfig  Sensor config:<BR>
 *                              Bits[31:11] sensor update interval:<BR>
 *                              Bits[31:16] sec - Seconds.<BR>
 *                              Bits[15:11] exponent - twos complement format
 *                              representing the power-of-10 multiplier that is
 *                              applied to the sec field.<BR>
 *                              The time duration between successive updates of
 *                              the sensor value. The representation is in the
 *                              [sec] x 10[exponent] format, in units of
 *                              seconds.<BR>
 *                              This field is set to 0 if the sensor does not
 *                              require or support an update interval.<BR>
 *                              Bits[10:2] Reserved.<BR>
 *                              Bit[1] Timestamp reporting:<BR>
 *                              Set to 1 if the sensor value provided by the
 *                              platform is timestamped.<BR>
 *                              Set to 0 if the sensor value provided by the
 *                              platform is not timestamped.<BR>
 *                              Bit[0] Sensor State:<BR>
 *                              Set to 1 if the sensor is enabled.<BR>
 *                              Set to 0 if the sensor is disabled
 *
 * This function is used to read the sensor configuration. It returns the
 * configured sensor update interval, the sensor state and if timestamping is
 * enabled. See section 4.7.2.10 SENSOR_CONFIG_GET in the
 * [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_SENSOR_CONFIG_GET_UPDATE_INTV_SEC() - Seconds
 * - ::SCMI_SENSOR_CONFIG_GET_UPDATE_INTV_EXP() - Twos complement format
 *   representing the power-of-10 multiplier that is applied to the sec field
 * - ::SCMI_SENSOR_CONFIG_GET_TS_ENABLED() - Timestamp reporting
 * - ::SCMI_SENSOR_CONFIG_GET_ENABLED() - Sensor State
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the sensor configuration was returned successfully.
 * - ::SCMI_ERR_NOT_FOUND: if \a sensorId does not point to an existing
 *   sensor.
 */
int32_t SCMI_SensorConfigGet(uint32_t channel, uint32_t sensorId,
    uint32_t *sensorConfig);

/*!
 * Set sensor configuration.
 *
 * @param[in]     channel       A2P channel for comms
 * @param[in]     sensorId      Identifier for the sensor
 * @param[in]     sensorConfig  Sensor config:<BR>
 *                              Bits[31:11] sensor update interval:<BR>
 *                              Bits[31:16] sec - Seconds.<BR>
 *                              Bits[15:11] exponent - twos complement format
 *                              representing the power-of-10 multiplier that is
 *                              applied to the sec field.<BR>
 *                              The time duration between successive updates of
 *                              the sensor value. The representation is in the
 *                              [sec] x 10[exponent] format, in units of
 *                              seconds.<BR>
 *                              This field should be set to 0 if the sensor
 *                              update interval does not need to be updated or
 *                              if the sensor does not support configuring the
 *                              sensor update interval.<BR>
 *                              Bits[10:9] Round up/down:<BR>
 *                              If Bit[10] is set to 1, the platform rounds
 *                              up/down autonomously to choose a sensor update
 *                              interval closest to the requested update
 *                              interval, and Bit[9] is ignored.<BR>
 *                              If Bit[10] is set to 0, then the platform
 *                              rounds up if Bit[9] is set to 1, and rounds
 *                              down if Bit[9] is set to 0.<BR>
 *                              Bits[8:2] Reserved.<BR>
 *                              Bit[1] Timestamp reporting:<BR>
 *                              Set to 1 if the sensor value provided by the
 *                              platform should be timestamped.<BR>
 *                              Set to 0 if the sensor value provided by the
 *                              platform should not be timestamped.<BR>
 *                              If the sensor does not support timestamp
 *                              reporting or its configuration, this bit should
 *                              be set to 0.<BR>
 *                              Bit[0] Sensor State:<BR>
 *                              Set to 1 if the sensor should be enabled.<BR>
 *                              Set to 0 if the sensor should be disabled
 *
 * This function is used to configure the sensor update interval and to enable
 * the timestamping of sensor values. This function can also be used to enable
 * or disable the sensor.
 *
 * If the sensor has been enabled, sensor values can be read using the
 * SCMI_SensorReadingGet() function or notified by the platform through
 * notifications. Sensor is enabled if any agent enables. See section 4.7.2.11
 * SENSOR_CONFIG_SET in the [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_SENSOR_CONFIG_SET_UPDATE_INTV_SEC() - Seconds
 * - ::SCMI_SENSOR_CONFIG_SET_UPDATE_INTV_EXP() - Twos complement format
 *   representing the power-of-10 multiplier that is applied to the sec field
 * - ::SCMI_SENSOR_CONFIG_SET_ROUND() - Round up/down
 * - ::SCMI_SENSOR_CONFIG_SET_TS_ENABLE() - Timestamp reporting
 * - ::SCMI_SENSOR_CONFIG_SET_ENABLE() - Sensor State
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the sensor configuration was set successfully.
 * - ::SCMI_ERR_NOT_FOUND: if \a sensorId does not point to an existing
 *   sensor.
 * - ::SCMI_ERR_INVALID_PARAMETERS: if the input parameters specify incorrect
 *   or illegal values.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the configuration requested by this
 *   function is not supported by the sensor.
 * - ::SCMI_ERR_DENIED: if the calling agent is not permitted to configure
 *   this sensor.
 */
int32_t SCMI_SensorConfigSet(uint32_t channel, uint32_t sensorId,
    uint32_t sensorConfig);

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
 * 4.7.2.2 NEGOTIATE_PROTOCOL_VERSION in the [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the negotiated protocol version is supported by the
 *   platform. All commands, responses, and notifications post successful
 *   return of this command must comply with the negotiated version.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the protocol version is not supported.
 */
int32_t SCMI_SensorNegotiateProtocolVersion(uint32_t channel,
    uint32_t version);

/*!
 * Read sensor event.
 *
 * @param[in]     channel        P2A notify channel for comms.
 * @param[out]    agentId        Refers to the agent that caused this event.
 *                               For the current version of the specification,
 *                               this field is set to 0 to indicate that the
 *                               platform is the generator of all sensor
 *                               events.
 * @param[out]    sensorId       Identifier for the sensor that has tripped.
 * @param[out]    tripPointDesc  Event flags:<BR>
 *                               Bits[31:17] Reserved.<BR>
 *                               Bit[16] Direction.<BR>
 *                               If set to 1, indicates that the trip point was
 *                               reached or crossed in the positive
 *                               direction.<BR>
 *                               If set to 0, indicates that the trip point was
 *                               reached or crossed in the negative
 *                               direction.<BR>
 *                               Bits[15:8] Reserved for future use.<BR>
 *                               Bits[7:0] trip point ID.<BR>
 *                               The identifier for the trip point that was
 *                               crossed or reached.
 *
 * This notification is issued by the platform when a sensor crosses a specific
 * trip point that the agent had requested event notification for, by using the
 * SCMI_SensorTripPointConfig() function.
 *
 * The platform might read sensors periodically using polling, or program
 * sensors to generate interrupts on trip points, depending on implementation.
 * If the sensor value changes such that it crosses several trip-points between
 * successive reads by the platform, then the platform might minimally send
 * only one notification to the agent to represent the multiple cross-over
 * condition. See section 4.7.4.1 SENSOR_TRIP_POINT_EVENT in the
 * [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_SENSOR_EVENT_DIRECTION() - Direction
 * - ::SCMI_SENSOR_EVENT_TP_ID() - The identifier for the trip point that was
 *   crossed or reached
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_SensorTripPointEvent(uint32_t channel, uint32_t *agentId,
    uint32_t *sensorId, uint32_t *tripPointDesc);

#endif /* SCMI_SENSOR_H */

/** @} */

