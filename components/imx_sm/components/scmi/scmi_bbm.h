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

#ifndef SCMI_BBM_H
#define SCMI_BBM_H

/*!
 * @addtogroup scmi_proto_bbm
 * @{
 */

/*!
 * @file
 * @brief Header file containing the client-side API for the System Control and
 * Management Interface (SCMI) bbm protocol.
 */

/* Defines */

/*!
 * @name SCMI bbm protocol message IDs
 */
/** @{ */
/*! Write a GPR value */
#define SCMI_MSG_BBM_GPR_SET         0x3U
/*! Read a GPR value */
#define SCMI_MSG_BBM_GPR_GET         0x4U
/*! Get attributes for an RTC */
#define SCMI_MSG_BBM_RTC_ATTRIBUTES  0x5U
/*! Set an RTC time */
#define SCMI_MSG_BBM_RTC_TIME_SET    0x6U
/*! Get an RTC time */
#define SCMI_MSG_BBM_RTC_TIME_GET    0x7U
/*! Set an RTC alarm */
#define SCMI_MSG_BBM_RTC_ALARM_SET   0x8U
/*! Read the button state */
#define SCMI_MSG_BBM_BUTTON_GET      0x9U
/*! Configure BBM RTC notifications */
#define SCMI_MSG_BBM_RTC_NOTIFY      0xAU
/*! Configure BBM button notifications */
#define SCMI_MSG_BBM_BUTTON_NOTIFY   0xBU
/*! Read BBM RTC notification events */
#define SCMI_MSG_BBM_RTC_EVENT       0x0U
/*! Read BBM button notification event */
#define SCMI_MSG_BBM_BUTTON_EVENT    0x1U
/** @} */

/*!
 * @name SCMI BBM max argument lengths
 */
/** @{ */
/*! Max length of the returned RTC name */
#define SCMI_BBM_MAX_NAME  16U
/** @} */

/* Macros */

/*!
 * @name SCMI BBM protocol attributes
 */
/** @{ */
/*! Number of RTCs */
#define SCMI_BBM_PROTO_ATTR_NUM_RTC(x)  (((x) & 0xFF0000U) >> 16U)
/*! Number of persistent storage (GPR) words */
#define SCMI_BBM_PROTO_ATTR_NUM_GPR(x)  (((x) & 0xFFFFU) >> 0U)
/** @} */

/*!
 * @name SCMI RTC attributes
 */
/** @{ */
/*! Bit width of RTC seconds */
#define SCMI_BBM_RTC_ATTR_SEC_WIDTH(x)   (((x) & 0xFF000000U) >> 24U)
/*! Bit width of RTC ticks */
#define SCMI_BBM_RTC_ATTR_TICK_WIDTH(x)  (((x) & 0xFF0000U) >> 16U)
/*! RTC ticks per second */
#define SCMI_BBM_RTC_ATTR_TICKS(x)       (((x) & 0xFFFFU) >> 0U)
/** @} */

/*!
 * @name SCMI BBM RTC flags
 */
/** @{ */
/*! RTC time format */
#define SCMI_BBM_RTC_FLAGS_TICKS(x)  (((x) & 0x1U) << 0U)
/** @} */

/*!
 * @name SCMI BBM RTC alarm flags
 */
/** @{ */
/*! RTC enable flag */
#define SCMI_BBM_ALARM_FLAGS_ENABLE(x)  (((x) & 0x1U) << 0U)
/** @} */

/*!
 * @name SCMI BBM RTC notification flags
 */
/** @{ */
/*! Enable RTC update notification */
#define SCMI_BBM_NOTIFY_RTC_UPDATED(x)   (((x) & 0x1U) << 2U)
/*! Enable RTC rollover notification */
#define SCMI_BBM_NOTIFY_RTC_ROLLOVER(x)  (((x) & 0x1U) << 1U)
/*! Enable RTC alarm notification */
#define SCMI_BBM_NOTIFY_RTC_ALARM(x)     (((x) & 0x1U) << 0U)
/** @} */

/*!
 * @name SCMI BBM button notification flags
 */
/** @{ */
/*! Enable button notifications */
#define SCMI_BBM_NOTIFY_BUTTON_DETECT(x)  (((x) & 0x1U) << 0U)
/** @} */

/*!
 * @name SCMI BBM RTC event flags
 */
/** @{ */
/*! RTC identifier */
#define SCMI_BBM_EVENT_RTC_ID(x)        (((x) & 0xFF000000U) >> 24U)
/*! RTC time was updated */
#define SCMI_BBM_EVENT_RTC_UPDATED(x)   (((x) & 0x4U) >> 2U)
/*! RTC rollover event notification */
#define SCMI_BBM_EVENT_RTC_ROLLOVER(x)  (((x) & 0x2U) >> 1U)
/*! RTC alarm notification */
#define SCMI_BBM_EVENT_RTC_ALARM(x)     (((x) & 0x1U) >> 0U)
/** @} */

/*!
 * @name SCMI BBM button event flags
 */
/** @{ */
/*! Button notification */
#define SCMI_BBM_EVENT_BUTTON_DETECTED(x)  (((x) & 0x1U) >> 0U)
/** @} */

/* Types */

/*!
 * SCMI RTC time
 */
typedef struct
{
    /*! Lower 32 bits of the time in seconds/ticks */
    uint32_t lower;
    /*! Upper 32 bits of the time in seconds/ticks */
    uint32_t upper;
} scmi_rtc_time_t;

/* Functions */

/*!
 * Get protocol version.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[out]    version  Protocol version. For this revision of the
 *                         specification, this value must be 0x10000
 *
 * This function returns the version of this protocol. For this version of the
 * specification, the value that is returned must be 0x10000, which corresponds
 * to version 1.0.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_BbmProtocolVersion(uint32_t channel, uint32_t *version);

/*!
 * Get protocol attributes.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[out]    attributes  Protocol attributes:<BR>
 *                            Bits[31:8] Number of RTC.<BR>
 *                            Bits[15:0] Number of persistent storage (GPR)
 *                            words
 *
 * This function returns the implementation details associated with this
 * protocol.
 *
 * Access macros:
 * - ::SCMI_BBM_PROTO_ATTR_NUM_RTC() - Number of RTCs
 * - ::SCMI_BBM_PROTO_ATTR_NUM_GPR() - Number of persistent storage (GPR) words
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_BbmProtocolAttributes(uint32_t channel, uint32_t *attributes);

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
 * ::SCMI_MSG_BBM_GPR_SET.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: in case the message is implemented and available to
 *   use.
 * - ::SCMI_ERR_NOT_FOUND: if the message identified by \a messageId is
 *   invalid or not provided by this platform implementation.
 */
int32_t SCMI_BbmProtocolMessageAttributes(uint32_t channel,
    uint32_t messageId, uint32_t *attributes);

/*!
 * Write a GPR value.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[in]     index    Index of GPR to write
 * @param[in]     value    32-bit value to write to the GPR
 *
 * This function allows an agent to write to persistent storage, a general
 * purpose register (GPR).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the GPR was successfully written.
 * - ::SCMI_ERR_NOT_FOUND: if the index is not valid.
 * - ::SCMI_ERR_DENIED: if the agent does not have permission to write the
 *   specified GPR.
 */
int32_t SCMI_BbmGprSet(uint32_t channel, uint32_t index, uint32_t value);

/*!
 * Read a GPR value.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[in]     index    Index of GPR to read
 * @param[out]    value    32-bit value read from the GPR
 *
 * This function allows an agent to read from persistent storage, a general
 * purpose register (GPR).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the GPR was successfully read.
 * - ::SCMI_ERR_NOT_FOUND: if the index is not valid.
 * - ::SCMI_ERR_DENIED: if the agent does not have permission to read the
 *   specified GPR.
 */
int32_t SCMI_BbmGprGet(uint32_t channel, uint32_t index, uint32_t *value);

/*!
 * Get attributes for an RTC.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in]     rtcId       Identifier of the RTC
 * @param[out]    attributes  RTC attributes:<BR>
 *                            Bit[31:24] Bit width of RTC seconds.<BR>
 *                            Bit[23:16] Bit width of RTC ticks.<BR>
 *                            Bits[15:0] RTC ticks per second
 * @param[out]    name        Null-terminated ASCII string of up to 16 bytes in
 *                            length describing the RTC name
 *
 * This function returns info about an RTC. This includes the bit width of the
 * RTC seconds, the RTC ticks, and the number of ticks per second. The max name
 * length is ::SCMI_BBM_MAX_NAME.
 *
 * Access macros:
 * - ::SCMI_BBM_RTC_ATTR_SEC_WIDTH() - Bit width of RTC seconds
 * - ::SCMI_BBM_RTC_ATTR_TICK_WIDTH() - Bit width of RTC ticks
 * - ::SCMI_BBM_RTC_ATTR_TICKS() - RTC ticks per second
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if valid power domain attributes are returned.
 * - ::SCMI_ERR_NOT_FOUND: if \a rtcId pertains to a non-existent RTC.
 */
int32_t SCMI_BbmRtcAttributes(uint32_t channel, uint32_t rtcId,
    uint32_t *attributes, uint8_t *name);

/*!
 * Set an RTC time.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[in]     rtcId    Identifier of the RTC
 * @param[in]     flags    RTC flags:<BR>
 *                         Bits[31:1] Reserved, must be zero.<BR>
 *                         Bit[0] RTC time format:<BR>
 *                         Set to 1 if the time is in ticks.<BR>
 *                         Set to 0 if the time is in seconds
 * @param[in]     val      Time in seconds/ticks to write to the RTC
 *
 * This function allows an agent to set the RTC time. Time can be set in units
 * of ticks or seconds. Only one RTC time exists per RTC.
 *
 * Access macros:
 * - ::SCMI_BBM_RTC_FLAGS_TICKS() - RTC time format
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the RTC time was successfully set.
 * - ::SCMI_ERR_NOT_FOUND: if \a rtcId pertains to a non-existent RTC.
 * - ::SCMI_ERR_INVALID_PARAMETERS: if the time is not valid (beyond the
 *   range of the RTC).
 * - ::SCMI_ERR_DENIED: if the agent does not have permission to set the RTC.
 */
int32_t SCMI_BbmRtcTimeSet(uint32_t channel, uint32_t rtcId, uint32_t flags,
    scmi_rtc_time_t val);

/*!
 * Get an RTC time.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[in]     rtcId    Identifier of the RTC
 * @param[in]     flags    RTC flags:<BR>
 *                         Bits[31:1] Reserved, must be zero.<BR>
 *                         Bit[0] RTC time format:<BR>
 *                         Set to 1 if the time is in ticks.<BR>
 *                         Set to 0 if the time is in seconds
 * @param[out]    val      Time in seconds/ticks read from the RTC
 *
 * This function allows an agent to read the RTC time. Time can be read in
 * units of ticks or seconds.
 *
 * Access macros:
 * - ::SCMI_BBM_RTC_FLAGS_TICKS() - RTC time format
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the RTC time was successfully read.
 * - ::SCMI_ERR_NOT_FOUND: if \a rtcId pertains to a non-existent RTC.
 */
int32_t SCMI_BbmRtcTimeGet(uint32_t channel, uint32_t rtcId, uint32_t flags,
    scmi_rtc_time_t *val);

/*!
 * Set an RTC alarm.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[in]     rtcId    Identifier of the RTC
 * @param[in]     flags    Alarm flags:<BR>
 *                         Bits[31:1] Reserved, must be zero.<BR>
 *                         Bit[0] RTC enable flag:<BR>
 *                         Set to 1 if the RTC alarm should be enabled.<BR>
 *                         Set to 0 if the RTC alarm should be disabled
 * @param[in]     val      Alarm time in seconds to write to the RTC
 *
 * This function allows an agent to enable/disable and set the time for the RTC
 * alarm. The alarm can be set in seconds only. Alarm is maintained for each
 * LM.
 *
 * Access macros:
 * - ::SCMI_BBM_ALARM_FLAGS_ENABLE() - RTC enable flag
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the alarm was successfully set.
 * - ::SCMI_ERR_NOT_FOUND: if \a rtcId pertains to a non-existent RTC.
 * - ::SCMI_ERR_INVALID_PARAMETERS: if the time is not valid (beyond the
 *   range of the RTC alarm).
 * - ::SCMI_ERR_DENIED: if the agent does not have permission to set the RTC
 *   alarm.
 */
int32_t SCMI_BbmRtcAlarmSet(uint32_t channel, uint32_t rtcId,
    uint32_t flags, scmi_rtc_time_t val);

/*!
 * Read the button state.
 *
 * @param[in]     channel      A2P channel for comms
 * @param[out]    buttonState  State of the ON/OFF button
 *
 * This function allows an agent to read the ON/OFF button state.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the button status was read.
 */
int32_t SCMI_BbmButtonGet(uint32_t channel, uint32_t *buttonState);

/*!
 * Configure BBM RTC notifications.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[in]     rtcId    Identifier of the RTC
 * @param[in]     flags    Notification flags:<BR>
 *                         Bits[31:3] Reserved, must be zero.<BR>
 *                         Bit[2] Update enable:<BR>
 *                         Set to 1 to send notification.<BR>
 *                         Set to 0 if no notification.<BR>
 *                         Bit[1] Rollover enable:<BR>
 *                         Set to 1 to send notification.<BR>
 *                         Set to 0 if no notification.<BR>
 *                         Bit[0] Alarm enable:<BR>
 *                         Set to 1 to send notification.<BR>
 *                         Set to 0 if no notification
 *
 * This function allows an agent to enable/disable notification on RTC events.
 * Events include:
 *
 * - RTC alarm configured with SCMI_BbmRtcAlarmSet()
 *
 * - RTC rollover (seconds counter has rolled over from max to zero
 *
 * - RTC updated by another agent via SCMI_BbmRtcTimeSet()
 *
 * Access macros:
 * - ::SCMI_BBM_NOTIFY_RTC_UPDATED() - Enable RTC update notification
 * - ::SCMI_BBM_NOTIFY_RTC_ROLLOVER() - Enable RTC rollover notification
 * - ::SCMI_BBM_NOTIFY_RTC_ALARM() - Enable RTC alarm notification
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the notification configuration was successfully
 *   updated.
 * - ::SCMI_ERR_NOT_FOUND: if \a rtcId pertains to a non-existent RTC.
 * - ::SCMI_ERR_DENIED: if the agent does not have permission to request RTC
 *   notifications.
 */
int32_t SCMI_BbmRtcNotify(uint32_t channel, uint32_t rtcId, uint32_t flags);

/*!
 * Configure BBM button notifications.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[in]     flags    Notification flags:<BR>
 *                         Bits[31:1] Reserved, must be zero.<BR>
 *                         Bit[0] Enable button:<BR>
 *                         Set to 1 to send notification.<BR>
 *                         Set to 0 if no notification
 *
 * This function allows an agent to enable/disable notification on the button
 * event. Various configuration parameters for the button are configured
 * statically within the board porting layer of SM.
 *
 * Access macros:
 * - ::SCMI_BBM_NOTIFY_BUTTON_DETECT() - Enable button notifications
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the notification configuration was successfully
 *   updated.
 * - ::SCMI_ERR_DENIED: if the agent does not have permission to request
 *   button notifications.
 */
int32_t SCMI_BbmButtonNotify(uint32_t channel, uint32_t flags);

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
 * considered best effort, and functionality is not guaranteed.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the negotiated protocol version is supported by the
 *   platform. All commands, responses, and notifications post successful
 *   return of this command must comply with the negotiated version.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the protocol version is not supported.
 */
int32_t SCMI_BbmNegotiateProtocolVersion(uint32_t channel,
    uint32_t version);

/*!
 * Read BBM RTC notification events.
 *
 * @param[in]     channel  P2A notify channel for comms.
 * @param[out]    flags    RTC events:<BR>
 *                         Bits[31:2] Reserved, must be zero.<BR>
 *                         Bit[1] RTC rollover notification:<BR>
 *                         1 RTC rollover detected.<BR>
 *                         0 no RTC rollover detected.<BR>
 *                         Bit[0] RTC alarm notification:<BR>
 *                         1 RTC alarm generated.<BR>
 *                         0 no RTC alarm generated.
 *
 * If an agent has registered for RTC notifications with SCMI_BbmRtcNotify(),
 * the platform sends notifications to the agent when the RTC alarm is
 * generated, the counter rolls over, or the time is updated via
 * SCMI_BbmRtcTimeSet().
 *
 * Access macros:
 * - ::SCMI_BBM_EVENT_RTC_ID() - RTC identifier
 * - ::SCMI_BBM_EVENT_RTC_UPDATED() - RTC time was updated
 * - ::SCMI_BBM_EVENT_RTC_ROLLOVER() - RTC rollover event notification
 * - ::SCMI_BBM_EVENT_RTC_ALARM() - RTC alarm notification
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_BbmRtcEvent(uint32_t channel, uint32_t *flags);

/*!
 * Read BBM button notification event.
 *
 * @param[in]     channel  P2A notify channel for comms.
 * @param[out]    flags    Button events:<BR>
 *                         Bits[31:1] Reserved, must be zero.<BR>
 *                         Bit[0] Button notification:<BR>
 *                         1 button change detected.<BR>
 *                         0 no button change detected.
 *
 * If an agent has registered for button notifications with
 * SCMI_BbmButtonNotify(), the platform sends a notification to the agent when
 * the button interrupt is generated.
 *
 * Access macros:
 * - ::SCMI_BBM_EVENT_BUTTON_DETECTED() - Button notification
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_BbmButtonEvent(uint32_t channel, uint32_t *flags);

#endif /* SCMI_BBM_H */

/** @} */

