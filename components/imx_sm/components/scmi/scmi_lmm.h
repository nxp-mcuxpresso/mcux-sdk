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

#ifndef SCMI_LMM_H
#define SCMI_LMM_H

/*!
 * @addtogroup scmi_proto_lmm
 * @{
 */

/*!
 * @file
 * @brief Header file containing the client-side API for the System Control and
 * Management Interface (SCMI) lmm protocol.
 */

/* Defines */

/*!
 * @name SCMI lmm protocol message IDs
 */
/** @{ */
/*! Get logical machine attributes */
#define SCMI_MSG_LMM_ATTRIBUTES    0x3U
/*! Boot (power on and start) an LM */
#define SCMI_MSG_LMM_BOOT          0x4U
/*! Reset an LM */
#define SCMI_MSG_LMM_RESET         0x5U
/*! Shutdown (power off) an LM */
#define SCMI_MSG_LMM_SHUTDOWN      0x6U
/*! Wake (resume) an LM from a low power state */
#define SCMI_MSG_LMM_WAKE          0x7U
/*! Request an LM gracefully suspend (sleep) */
#define SCMI_MSG_LMM_SUSPEND       0x8U
/*! Configure LM notifications */
#define SCMI_MSG_LMM_NOTIFY        0x9U
/*! Read the reason the LM last booted/shutdown/reset */
#define SCMI_MSG_LMM_RESET_REASON  0xAU
/*! Power up an LM */
#define SCMI_MSG_LMM_POWER_ON      0xBU
/*! Read LM notification event */
#define SCMI_MSG_LMM_EVENT         0x0U
/** @} */

/*!
 * @name SCMI LMM max argument lengths
 */
/** @{ */
/*! Max length of the returned logical machine name */
#define SCMI_LMM_MAX_NAME     16U
/*! Max number of extended shutdown info words */
#define SCMI_LMM_MAX_EXTINFO  SCMI_ARRAY(16U, uint32_t)
/** @} */

/*!
 * @name SCMI actual LMM argument lengths
 */
/** @{ */
/*! Actual number of extended shutdown info words returned */
#define SCMI_LMM_NUM_EXTINFO  SCMI_LMM_SHUTDOWN_FLAG_EXT_LEN(msgRx->shutdownFlags)
/** @} */

/*!
 * @name SCMI LM ID
 */
/** @{ */
/*! LM ID to use to discover the callers LM ID */
#define SCMI_LMM_ID_DISCOVER  0xFFFFFFFFU
/** @} */

/*!
 * @name SCMI LM State
 */
/** @{ */
/*! LM off (shutdown) */
#define SCMI_LMM_STATE_OFF      0U
/*! LM on (booted/running) */
#define SCMI_LMM_STATE_ON       1U
/*! LM suspend (asleep) */
#define SCMI_LMM_STATE_SUSPEND  2U
/** @} */

/* Macros */

/*!
 * @name SCMI LMM protocol attributes
 */
/** @{ */
/*! Number of logical machines */
#define SCMI_LMM_PROTO_ATTR_NUM_LM(x)  (((x) & 0xFFU) >> 0U)
/** @} */

/*!
 * @name SCMI LM request flags
 */
/** @{ */
/*! Graceful request */
#define SCMI_LMM_FLAGS_GRACEFUL(x)  (((x) & 0x1U) << 0U)
/** @} */

/*!
 * @name SCMI boot reason flags
 */
/** @{ */
/*! Valid */
#define SCMI_LMM_BOOT_FLAG_VLD(x)      (((x) & 0x80000000U) >> 31U)
/*! Valid origin */
#define SCMI_LMM_BOOT_FLAG_ORG_VLD(x)  (((x) & 0x10000000U) >> 28U)
/*! LM source of action */
#define SCMI_LMM_BOOT_FLAG_ORIGIN(x)   (((x) & 0xF000000U) >> 24U)
/*! Valid error ID */
#define SCMI_LMM_BOOT_FLAG_ERR_VLD(x)  (((x) & 0x800000U) >> 23U)
/*! Error ID */
#define SCMI_LMM_BOOT_FLAG_ERR_ID(x)   (((x) & 0x7FFF00U) >> 8U)
/*! Reason */
#define SCMI_LMM_BOOT_FLAG_REASON(x)   (((x) & 0xFFU) >> 0U)
/** @} */

/*!
 * @name SCMI shutdown reason flags
 */
/** @{ */
/*! Valid */
#define SCMI_LMM_SHUTDOWN_FLAG_VLD(x)      (((x) & 0x80000000U) >> 31U)
/*! Number of valid extended info words */
#define SCMI_LMM_SHUTDOWN_FLAG_EXT_LEN(x)  (((x) & 0x60000000U) >> 29U)
/*! Valid origin */
#define SCMI_LMM_SHUTDOWN_FLAG_ORG_VLD(x)  (((x) & 0x10000000U) >> 28U)
/*! LM source of action */
#define SCMI_LMM_SHUTDOWN_FLAG_ORIGIN(x)   (((x) & 0xF000000U) >> 24U)
/*! Valid error ID */
#define SCMI_LMM_SHUTDOWN_FLAG_ERR_VLD(x)  (((x) & 0x800000U) >> 23U)
/*! Error ID */
#define SCMI_LMM_SHUTDOWN_FLAG_ERR_ID(x)   (((x) & 0x7FFF00U) >> 8U)
/*! Reason */
#define SCMI_LMM_SHUTDOWN_FLAG_REASON(x)   (((x) & 0xFFU) >> 0U)
/** @} */

/*!
 * @name SCMI LMM notification flags
 */
/** @{ */
/*! Enable notifications for boot */
#define SCMI_LMM_NOTIFY_BOOT(x)      (((x) & 0x1U) << 0U)
/*! Enable notifications for shutdown */
#define SCMI_LMM_NOTIFY_SHUTDOWN(x)  (((x) & 0x1U) << 1U)
/*! Enable notifications for suspend (sleep) */
#define SCMI_LMM_NOTIFY_SUSPEND(x)   (((x) & 0x1U) << 2U)
/*! Enable notifications for wake (resume) */
#define SCMI_LMM_NOTIFY_WAKE(x)      (((x) & 0x1U) << 3U)
/** @} */

/*!
 * @name SCMI LM event flags
 */
/** @{ */
/*! Notification that an LM booted */
#define SCMI_LMM_EVENT_BOOT(x)      (((x) & 0x1U) >> 0U)
/*! Notification that an LM is shutdown */
#define SCMI_LMM_EVENT_SHUTDOWN(x)  (((x) & 0x2U) >> 1U)
/*! Notification that an LM suspended */
#define SCMI_LMM_EVENT_SUSPEND(x)   (((x) & 0x4U) >> 2U)
/*! Notification that an LM awakened */
#define SCMI_LMM_EVENT_WAKE(x)      (((x) & 0x8U) >> 3U)
/** @} */

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
int32_t SCMI_LmmProtocolVersion(uint32_t channel, uint32_t *version);

/*!
 * Get protocol attributes.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[out]    attributes  Protocol attributes:<BR>
 *                            Bits[31:8] Reserved, must be zero.<BR>
 *                            Bits[7:0] Number of logical machines
 *
 * This function returns the implementation details associated with this
 * protocol.
 *
 * Access macros:
 * - ::SCMI_LMM_PROTO_ATTR_NUM_LM() - Number of logical machines
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_LmmProtocolAttributes(uint32_t channel, uint32_t *attributes);

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
 * ::SCMI_MSG_LMM_ATTRIBUTES.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: in case the message is implemented and available to
 *   use.
 * - ::SCMI_ERR_NOT_FOUND: if the message identified by \a messageId is
 *   invalid or not provided by this platform implementation.
 */
int32_t SCMI_LmmProtocolMessageAttributes(uint32_t channel,
    uint32_t messageId, uint32_t *attributes);

/*!
 * Get logical machine attributes.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in,out] lmId        Return LM. Identifier of the LM whose
 *                            identification is requested. This field is:<BR>
 *                            - Populated with the lmId of the calling agent,
 *                            when the lmId parameter passed via the function
 *                            is 0xFFFFFFFF.<BR>
 *                            - Identical to the lmId field passed via the
 *                            calling parameters, in all other cases
 * @param[out]    attributes  LM attributes:<BR>
 *                            Bits[31:0] Reserved, must be zero
 * @param[out]    state       Current state of the LM
 * @param[out]    errStatus   Last error status recorded
 * @param[out]    name        A NULL terminated ASCII string with the LM name,
 *                            of up to 16 bytes
 *
 * The function returns information about an LM. An LM can discover its own LM
 * ID and name by passing an \a lmId of ::SCMI_LMM_ID_DISCOVER. In this case,
 * the function returns the LM ID and name of the calling LM. Note some SoC
 * cannot generate notifications on suspend/wake so the
 * ::SCMI_LMM_STATE_SUSPEND state may not be returned. Max name length is
 * ::SCMI_LMM_MAX_NAME.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if valid attributes are returned.
 * - ::SCMI_ERR_NOT_FOUND: if \a lmId does not point to a valid logical
 *   machine.
 * - ::SCMI_ERR_DENIED: if the calling agent is not allowed to get info for
 *   the LM specified by \a lmId.
 */
int32_t SCMI_LmmAttributes(uint32_t channel, uint32_t *lmId,
    uint32_t *attributes, uint32_t *state, int32_t *errStatus,
    uint8_t *name);

/*!
 * Boot (power on and start) an LM.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[in]     lmId     Identifier for the logical machine
 *
 * This function will boot (power on and start) an LM. An LMM_EVENT
 * notification will be sent to subscribing agents. It cannot be called on
 * itself.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the LM successfully booted.
 * - ::SCMI_ERR_NOT_FOUND: if the LM identified by \a lmId does not exist.
 * - ::SCMI_ERR_INVALID_PARAMETERS, if \a lmId is the same as the caller.
 * - ::SCMI_ERR_DENIED: if the calling agent is not allowed to manage the LM
 *   specified by \a lmId.
 */
int32_t SCMI_LmmBoot(uint32_t channel, uint32_t lmId);

/*!
 * Reset an LM.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[in]     lmId     Identifier for the logical machine
 * @param[in]     flags    Reset flags:<BR>
 *                         Bits[31:1] Reserved, must be zero.<BR>
 *                         Bit[0] Graceful request:<BR>
 *                         Set to 1 if the request is a graceful request.<BR>
 *                         Set to 0 if the request is a forceful request
 *
 * This function will reset an LM. If graceful, a SYSTEM_POWER_STATE_NOTIFIER
 * notification will be sent to the target LM to request it perform a reset. If
 * not, the LM is reset by shutting it down and then booting it (both
 * operations might result in an LMM_EVENT notification to subscribing agents).
 * It cannot be called on itself.
 *
 * Access macros:
 * - ::SCMI_LMM_FLAGS_GRACEFUL() - Graceful request
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the LM successfully booted.
 * - ::SCMI_ERR_NOT_FOUND: if the LM identified by \a lmId does not exist.
 * - ::SCMI_ERR_INVALID_PARAMETERS, if \a lmId is the same as the caller.
 * - ::SCMI_ERR_DENIED: if the calling agent is not allowed to manage the LM
 *   specified by \a lmId.
 */
int32_t SCMI_LmmReset(uint32_t channel, uint32_t lmId, uint32_t flags);

/*!
 * Shutdown (power off) an LM.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[in]     lmId     Identifier for the logical machine
 * @param[in]     flags    Shutdown flags:<BR>
 *                         Bits[31:1] Reserved, must be zero.<BR>
 *                         Bit[0] Graceful request:<BR>
 *                         Set to 1 if the request is a graceful request.<BR>
 *                         Set to 0 if the request is a forceful request
 *
 * This function will shutdown (power off) an LM. If graceful, a
 * SYSTEM_POWER_STATE_NOTIFIER notification will be sent to the target LM to
 * request it perform a shutdown. If not, the LM is shutdown and an LMM_EVENT
 * notification sent to subscribing agents. It cannot be called on itself.
 *
 * Access macros:
 * - ::SCMI_LMM_FLAGS_GRACEFUL() - Graceful request
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the LM successfully booted.
 * - ::SCMI_ERR_NOT_FOUND: if the LM identified by \a lmid does not exist.
 * - ::SCMI_ERR_INVALID_PARAMETERS, if \a lmId is the same as the caller.
 * - ::SCMI_ERR_DENIED: if the calling agent is not allowed to manage the LM
 *   specified by \a lmId.
 */
int32_t SCMI_LmmShutdown(uint32_t channel, uint32_t lmId, uint32_t flags);

/*!
 * Wake (resume) an LM from a low power state.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[in]     lmId     Identifier for the logical machine
 *
 * This function will wake (resume) an LM from suspend assuming it is
 * subscribed to this event and the communication MU is a wake-up source. This
 * is done by sending a SYSTEM_POWER_STATE_NOTIFIER notification to the LM. It
 * cannot be called on itself.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the LM successfully booted.
 * - ::SCMI_ERR_NOT_FOUND: if the LM identified by \a lmId does not exist.
 * - ::SCMI_ERR_INVALID_PARAMETERS, if \a lmId is the same as the caller.
 * - ::SCMI_ERR_DENIED: if the calling agent is not allowed to manage the LM
 *   specified by \a lmId.
 */
int32_t SCMI_LmmWake(uint32_t channel, uint32_t lmId);

/*!
 * Request an LM gracefully suspend (sleep).
 *
 * @param[in]     channel  A2P channel for comms
 * @param[in]     lmId     Identifier for the logical machine
 *
 * This function will suspend (sleep) an LM. This is done by sending a
 * SYSTEM_POWER_STATE_NOTIFIER notification to the target LM. This is always a
 * graceful request and the LM must suspend itself when it gets the
 * notification. It cannot be called on itself.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the LM successfully booted.
 * - ::SCMI_ERR_NOT_FOUND: if the LM identified by \a lmId does not exist.
 * - ::SCMI_ERR_INVALID_PARAMETERS, if \a lmId is the same as the caller.
 * - ::SCMI_ERR_DENIED: if the calling agent is not allowed to manage the LM
 *   specified by \a lmId.
 */
int32_t SCMI_LmmSuspend(uint32_t channel, uint32_t lmId);

/*!
 * Configure LM notifications.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[in]     lmId     Identifier for the logical machine
 * @param[in]     flags    Notification flags:<BR>
 *                         Bits[31:3] Reserved, must be zero.<BR>
 *                         Bit[3] Wake (resume) notification:<BR>
 *                         Set to 1 to send notification.<BR>
 *                         Set to 0 if no notification.<BR>
 *                         Bit[2] Suspend (sleep) notification:<BR>
 *                         Set to 1 to send notification.<BR>
 *                         Set to 0 if no notification.<BR>
 *                         Bit[1] Shutdown (off) notification:<BR>
 *                         Set to 1 to send notification.<BR>
 *                         Set to 0 if no notification.<BR>
 *                         Bit[0] Boot (on) notification:<BR>
 *                         Set to 1 to send notification.<BR>
 *                         Set to 0 if no notification
 *
 * This function is used to subscribe to notifications of boot, shutdown,
 * sleep, and wake events from other LMs. It is not used for an LM to get
 * notifications about itself. This is done via the SYSTEM protocol
 * notifications. Those can be subscribed for using
 * SCMI_SystemPowerStateNotify(). Note some SoC designs do not allow
 * notification of sleep/wake events.
 *
 * Access macros:
 * - ::SCMI_LMM_NOTIFY_BOOT() - Enable notifications for boot
 * - ::SCMI_LMM_NOTIFY_SHUTDOWN() - Enable notifications for shutdown
 * - ::SCMI_LMM_NOTIFY_SUSPEND() - Enable notifications for suspend (sleep)
 * - ::SCMI_LMM_NOTIFY_WAKE() - Enable notifications for wake (resume)
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the notification state successfully updated.
 * - ::SCMI_ERR_NOT_FOUND: if the LM identified by \a lmid does not exist.
 * - ::SCMI_ERR_INVALID_PARAMETERS, if the input attributes flag specifies
 *   unsupported or invalid configurations.
 * - ::SCMI_ERR_DENIED: if the calling agent is not permitted to request the
 *   notification.
 */
int32_t SCMI_LmmNotify(uint32_t channel, uint32_t lmId, uint32_t flags);

/*!
 * Read the reason the LM last booted/shutdown/reset.
 *
 * @param[in]     channel        A2P channel for comms
 * @param[in]     lmId           Identifier for the logical machine
 * @param[out]    bootFlags      Boot reason flags. This parameter has the
 *                               following format:<BR>
 *                               Bits[31] Valid.<BR>
 *                               Set to 1 if the entire reason is valid.<BR>
 *                               Set to 0 if the entire reason is not
 *                               valid.<BR>
 *                               Bits[30:29] Reserved, must be zero.<BR>
 *                               Bit[28] Valid origin:<BR>
 *                               Set to 1 if the origin field is valid.<BR>
 *                               Set to 0 if the origin field is not valid.<BR>
 *                               Bits[27:24] Origin.<BR>
 *                               Bit[23] Valid err ID:<BR>
 *                               Set to 1 if the error ID field is valid.<BR>
 *                               Set to 0 if the error ID field is not
 *                               valid.<BR>
 *                               Bits[22:8] Error ID.<BR>
 *                               Bit[7:0] Reason
 * @param[out]    shutdownFlags  Shutdown reason flags. This parameter has the
 *                               following format:<BR>
 *                               Bits[31] Valid.<BR>
 *                               Set to 1 if the entire reason is valid.<BR>
 *                               Set to 0 if the entire reason is not
 *                               valid.<BR>
 *                               Bits[30:29] Number of valid extended info
 *                               words.<BR>
 *                               Bit[28] Valid origin:<BR>
 *                               Set to 1 if the origin field is valid.<BR>
 *                               Set to 0 if the origin field is not valid.<BR>
 *                               Bits[27:24] Origin.<BR>
 *                               Bit[23] Valid err ID:<BR>
 *                               Set to 1 if the error ID field is valid.<BR>
 *                               Set to 0 if the error ID field is not
 *                               valid.<BR>
 *                               Bits[22:8] Error ID.<BR>
 *                               Bit[7:0] Reason
 * @param[out]    extInfo        Array of extended info words
 *
 * This function returns the boot/shutdown/reset reason for an LM. If possible
 * to capture, it also returns the LM that initiated the actions. Extended
 * shutdown info words are also returned if captured. The number depends on the
 * shutdown reason. All info is device specific. If the action is a reset then
 * the boot and shutdown reasons will be the same as a reset action consists of
 * a shutdown+boot all occurring for the same reason. If no unique action has
 * occurred for an LM, this will return the reasons for the system. Max number
 * of extended shutdown info words is ::SCMI_LMM_MAX_EXTINFO.
 *
 * Access macros:
 * - ::SCMI_LMM_BOOT_FLAG_VLD() - Valid
 * - ::SCMI_LMM_BOOT_FLAG_ORG_VLD() - Valid origin
 * - ::SCMI_LMM_BOOT_FLAG_ORIGIN() - LM source of action
 * - ::SCMI_LMM_BOOT_FLAG_ERR_VLD() - Valid error ID
 * - ::SCMI_LMM_BOOT_FLAG_ERR_ID() - Error ID
 * - ::SCMI_LMM_BOOT_FLAG_REASON() - Reason
 * - ::SCMI_LMM_SHUTDOWN_FLAG_VLD() - Valid
 * - ::SCMI_LMM_SHUTDOWN_FLAG_EXT_LEN() - Number of valid extended info words
 * - ::SCMI_LMM_SHUTDOWN_FLAG_ORG_VLD() - Valid origin
 * - ::SCMI_LMM_SHUTDOWN_FLAG_ORIGIN() - LM source of action
 * - ::SCMI_LMM_SHUTDOWN_FLAG_ERR_VLD() - Valid error ID
 * - ::SCMI_LMM_SHUTDOWN_FLAG_ERR_ID() - Error ID
 * - ::SCMI_LMM_SHUTDOWN_FLAG_REASON() - Reason
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the notification state successfully updated.
 * - ::SCMI_ERR_NOT_FOUND: if the LM identified by \a lmid does not exist.
 * - ::SCMI_ERR_DENIED: if the calling agent is not permitted to request the
 *   reset reason.
 */
int32_t SCMI_LmmResetReason(uint32_t channel, uint32_t lmId,
    uint32_t *bootFlags, uint32_t *shutdownFlags, uint32_t *extInfo);

/*!
 * Power up an LM.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[in]     lmId     Identifier for the logical machine
 *
 * This function will power on an LM. This allows code to be loaded into LM
 * memory, boot addresses set with SCMI_CpuResetVectorSet(), and then booted
 * via SCMI_LmmBoot(). It cannot be called on itself.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the LM successfully powered on.
 * - ::SCMI_ERR_NOT_FOUND: if the LM identified by \a lmId does not exist.
 * - ::SCMI_ERR_INVALID_PARAMETERS, if \a lmId is the same as the caller.
 * - ::SCMI_ERR_DENIED: if the calling agent is not allowed to manage the LM
 *   specified by \a lmId.
 */
int32_t SCMI_LmmPowerOn(uint32_t channel, uint32_t lmId);

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
int32_t SCMI_LmmNegotiateProtocolVersion(uint32_t channel,
    uint32_t version);

/*!
 * Read LM notification event.
 *
 * @param[in]     channel  P2A notify channel for comms.
 * @param[out]    lmId     Identifier for the LM that caused the transition.
 * @param[out]    eventLm  Identifier for the LM the event is for.
 * @param[out]    flags    LM events:<BR>
 *                         Bits[31:3] Reserved, must be zero.<BR>
 *                         Bit[3] Wake (resume) event:<BR>
 *                         1 LM has awakened.<BR>
 *                         0 not a wake event.<BR>
 *                         Bit[2] Suspend (sleep) event:<BR>
 *                         1 LM has suspended.<BR>
 *                         0 not a suspend event.<BR>
 *                         Bit[1] Shutdown (off) event:<BR>
 *                         1 LM has shutdown.<BR>
 *                         0 not a shutdown event.<BR>
 *                         Bit[0] Boot (on) event:<BR>
 *                         1 LM has booted.<BR>
 *                         0 not a boot event.
 *
 * If an agent has registered for notifications with SCMI_LmmNotify(), the
 * platform sends notifications to the agent when they boot, shutdown, suspend,
 * or wake. Note some SoC designs do not allow notification of sleep/wake
 * events.
 *
 * Access macros:
 * - ::SCMI_LMM_EVENT_BOOT() - Notification that an LM booted
 * - ::SCMI_LMM_EVENT_SHUTDOWN() - Notification that an LM is shutdown
 * - ::SCMI_LMM_EVENT_SUSPEND() - Notification that an LM suspended
 * - ::SCMI_LMM_EVENT_WAKE() - Notification that an LM awakened
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_LmmEvent(uint32_t channel, uint32_t *lmId, uint32_t *eventLm,
    uint32_t *flags);

#endif /* SCMI_LMM_H */

/** @} */

