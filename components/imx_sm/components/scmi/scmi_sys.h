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

#ifndef SCMI_SYS_H
#define SCMI_SYS_H

/*!
 * @addtogroup scmi_proto_sys
 * @{
 */

/*!
 * @file
 * @brief Header file containing the client-side API for the System Control and
 * Management Interface (SCMI) sys protocol.
 */

/* Defines */

/*!
 * @name SCMI sys protocol message IDs
 */
/** @{ */
/*! Set system power state */
#define SCMI_MSG_SYSTEM_POWER_STATE_SET       0x3U
/*! Configure system state notifications */
#define SCMI_MSG_SYSTEM_POWER_STATE_NOTIFY    0x5U
/*! Read system state notification event */
#define SCMI_MSG_SYSTEM_POWER_STATE_NOTIFIER  0x0U
/** @} */

/*!
 * @name SCMI system power states
 */
/** @{ */
/*! Shutdown (off) LM */
#define SCMI_SYS_STATE_SHUTDOWN       0x00000000U
/*! Reset LM */
#define SCMI_SYS_STATE_COLD_RESET     0x00000001U
/*! Reset LM, retain memory */
#define SCMI_SYS_STATE_WARM_RESET     0x00000002U
/*! Power up (on) LM */
#define SCMI_SYS_STATE_POWER_UP       0x00000003U
/*! Suspend (sleep) LM */
#define SCMI_SYS_STATE_SUSPEND        0x00000004U
/*! Wake (resume) LM */
#define SCMI_SYS_STATE_WAKE           0x80000000U
/*! Shutdown (off) full SoC */
#define SCMI_SYS_STATE_FULL_SHUTDOWN  0x80000001U
/*! Reset full SoC */
#define SCMI_SYS_STATE_FULL_RESET     0x80000002U
/*! Suspend (sleep) full SoC */
#define SCMI_SYS_STATE_FULL_SUSPEND   0x80000003U
/*! Wake (resume) full SoC */
#define SCMI_SYS_STATE_FULL_WAKE      0x80000004U
/*! Shutdown (off) LM group 0 */
#define SCMI_SYS_STATE_GRP_SHUTDOWN   0x80000005U
/*! Reset LM group 0 */
#define SCMI_SYS_STATE_GRP_RESET      0x80000006U
/*! Set suspend/shutdown mode */
#define SCMI_SYS_STATE_MODE           0xC0000000U
/** @} */

/* Macros */

/*!
 * @name SCMI system message attributes
 */
/** @{ */
/*! System warm reset support */
#define SCMI_SYS_MSG_ATTR_WARM(x)     (((x) & 0x80000000U) >> 31U)
/*! System suspend (sleep) support */
#define SCMI_SYS_MSG_ATTR_SUSPEND(x)  (((x) & 0x40000000U) >> 30U)
/** @} */

/*!
 * @name SCMI system power state flags
 */
/** @{ */
/*! Graceful request */
#define SCMI_SYS_FLAGS_GRACEFUL(x)  (((x) & 0x1U) << 0U)
/** @} */

/*!
 * @name SCMI system notification flags
 */
/** @{ */
/*! Notify enable */
#define SCMI_SYS_NOTIFY_ENABLE(x)  (((x) & 0x1U) << 0U)
/** @} */

/*!
 * @name SCMI system event flags
 */
/** @{ */
/*! Graceful request */
#define SCMI_SYS_NOTIFIER_GRACEFUL(x)  (((x) & 0x1U) >> 0U)
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
 * version of the specification, the value returned must be 0x20001, which
 * corresponds to version 2.1. See section 4.4.2.1 PROTOCOL_VERSION in the
 * [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_SysProtocolVersion(uint32_t channel, uint32_t *version);

/*!
 * Get protocol attributes.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[out]    attributes  Protocol attributes:<BR>
 *                            Bits[31:0] Reserved, must be zero
 *
 * This function returns the implementation details associated with this
 * protocol. See section 4.4.2.3 PROTOCOL_ATTRIBUTES in the
 * [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_SysProtocolAttributes(uint32_t channel, uint32_t *attributes);

/*!
 * Get protocol message attributes.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in]     messageId   Message ID of the message
 * @param[out]    attributes  Message attributes: Flags associated with a
 *                            specific function in the protocol.<BR>
 *                            If message ID is for SYSTEM_POWER_STATE_SET, the
 *                            attributes have the following format:<BR>
 *                            Bit[31] System warm reset support.<BR>
 *                            Set to 1 if system warm reset is supported.<BR>
 *                            Set to 0 if system warm reset is not
 *                            supported.<BR>
 *                            Bit[30] System suspend support.<BR>
 *                            Set to 1 if system suspend is supported.<BR>
 *                            Set to 0 if system suspend is not supported.<BR>
 *                            Bits[29:0] Reserved, must be zero.<BR>
 *                            For all values of message ID, this value is zero
 *
 * On success, this function returns the implementation details associated with
 * a specific message in this protocol. An example message ID is
 * ::SCMI_MSG_SYSTEM_POWER_STATE_SET. See section 4.4.2.4
 * PROTOCOL_MESSAGE_ATTRIBUTES in the [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_SYS_MSG_ATTR_WARM() - System warm reset support
 * - ::SCMI_SYS_MSG_ATTR_SUSPEND() - System suspend (sleep) support
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: in case the message is implemented and available to
 *   use.
 * - ::SCMI_ERR_NOT_FOUND: if the message identified by \a messageId is
 *   invalid or not provided by this platform implementation.
 * - ::SCMI_ERR_NOT_SUPPORTED: when message ID is set to the
 *   SYSTEM_POWER_STATE_NOTIFY function identifier and notifications are not
 *   supported.
 */
int32_t SCMI_SysProtocolMessageAttributes(uint32_t channel,
    uint32_t messageId, uint32_t *attributes);

/*!
 * Set system power state.
 *
 * @param[in]     channel      A2P channel for comms
 * @param[in]     flags        Power state set flags. This parameter has the
 *                             following format:<BR>
 *                             Bits[31:1] Reserved, must be zero.<BR>
 *                             Bit[0] Graceful request. This flag is ignored
 *                             for power up requests.<BR>
 *                             Set to 1 if the request is a graceful
 *                             request.<BR>
 *                             Set to 0 if the request is a forceful request
 * @param[in]     systemState  System state. Can be one of:<BR>
 *                             0x0 System shutdown (off).<BR>
 *                             0x1 System cold reset.<BR>
 *                             0x2 System warm reset.<BR>
 *                             0x3 System power-up (boot).<BR>
 *                             0x4 System suspend (sleep).<BR>
 *                             0x5 - 0x7FFFFFFF Reserved, must not be
 *                             used.<BR>
 *                             0x80000000 - 0xFFFFFFFF Might be used for
 *                             vendor-defined implementations of system power
 *                             state. These can include additional parameters.
 *                             The prototype for vendor-defined calls is beyond
 *                             the scope of this specification
 *
 * This function is used to power down or reset the LM or full SoC. An example
 * power state is ::SCMI_SYS_STATE_SHUTDOWN. The ::SCMI_SYS_STATE_MODE state is
 * unique in that it does not cause an immediate state change. Instead,
 * bits[29:0] are aggregated and the and the resulting mode used the next time
 * the SoC suspends or is shutdown to determine what mode is entered. The
 * setting of the bits is SoC and board specific.
 *
 * Note the SCMI spec defines the standard states to affect the system. In SM,
 * the system in this case is defined as the LM the SCMI agent is a part of.
 * There are vendor-defined states to set the state of the full SoC (e.g.
 * ::SCMI_SYS_STATE_FULL_SHUTDOWN) but these require elevated permission to
 * set. See the @ref SYS_ARCH_LM section for more info.
 *
 * System power-up must only be available to agents other than a PSCI
 * implementation on systems that implement OSPM system view. Access depends on
 * if graceful, LM, or system state request. See section 4.4.2.5
 * SYSTEM_POWER_STATE_SET in the [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_SYS_FLAGS_GRACEFUL() - Graceful request
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_INVALID_PARAMETERS: if the requested power state is not valid.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the requested state is not supported for
 *   the calling agent.
 * - ::SCMI_ERR_DENIED: for system suspend requests when there are
 *   application processors, other than the caller, in a running or idle state.
 */
int32_t SCMI_SystemPowerStateSet(uint32_t channel, uint32_t flags,
    uint32_t systemState);

/*!
 * Configure system state notifications.
 *
 * @param[in]     channel       A2P channel for comms
 * @param[in]     notifyEnable  Notification flags:<BR>
 *                              Bits[31:1] Reserved, must be zero.<BR>
 *                              Bit[0] Notify enable:<BR>
 *                              If this value is set to 0, the platform does
 *                              not send any system power state notifier
 *                              messages to the calling agent.<BR>
 *                              If this value is set to 1, the platform does
 *                              send system power state notifier messages
 *                              functions to the calling agent
 *
 * This function is used to request notification of system power state
 * requests. This function might be used:
 *
 * - By the OSPM to receive notifications of graceful system power state
 * requests.
 *
 * - By a management agent or a privileged agent to be notified that the OSPM
 * requested a forceful transition.
 *
 * On initial boot of an agent, these notifications must be disabled by default
 * to that agent. See section 4.4.2.7 SYSTEM_POWER_STATE_NOTIFY in the
 * [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_SYS_NOTIFY_ENABLE() - Notify enable
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS
 * - ::SCMI_ERR_NOT_SUPPORTED: if notifications are not supported or
 *   available to the calling agent.
 * - ::SCMI_ERR_INVALID_PARAMETERS: if notify_enable specifies invalid or
 *   impermissible values.
 */
int32_t SCMI_SystemPowerStateNotify(uint32_t channel,
    uint32_t notifyEnable);

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
 * 4.4.2.2 NEGOTIATE_PROTOCOL_VERSION in the [SCMI Spec](@ref DOCS).
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the negotiated protocol version is supported by the
 *   platform. All commands, responses, and notifications post successful
 *   return of this command must comply with the negotiated version.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the protocol version is not supported.
 */
int32_t SCMI_SysNegotiateProtocolVersion(uint32_t channel,
    uint32_t version);

/*!
 * Read system state notification event.
 *
 * @param[in]     channel      P2A notify channel for comms.
 * @param[out]    agentId      Identifier for the agent that caused the event.
 *                             The event is a system power state transition.
 * @param[out]    flags        Notification events. This parameter has the
 *                             following format:<BR>
 *                             Bits[31:1] Reserved, must be zero.<BR>
 *                             Bit[0] Graceful request.<BR>
 *                             Set to 1 if the notification indicates that a
 *                             system power state transition has been
 *                             gracefully requested.<BR>
 *                             Set to 0 if the notification indicates that a
 *                             system power state has been forcibly requested.
 * @param[out]    systemState  System state. System power state that the system
 *                             has transitioned to, or which has been
 *                             requested.<BR>
 *                             Can be one of:<BR>
 *                             0x0 System shutdown (off).<BR>
 *                             0x1 System cold reset.<BR>
 *                             0x2 System warm reset.<BR>
 *                             0x3 System power-up (on).<BR>
 *                             0x4 System suspend (sleep).<BR>
 *                             0x5 - 0x7FFFFFFF Reserved, must not be
 *                             used.<BR>
 *                             0x80000000 - 0xFFFFFFFF Available for
 *                             vendor-defined implementations of system power
 *                             state. These can include additional parameters.
 *                             The prototype for vendor-defined call is beyond
 *                             the scope of this specification.
 * @param[out]    timeout      Timeout. This field is valid only when both the
 *                             following conditions are satisfied:<BR>
 *                             - The systemState field is system shutdown
 *                             (0x0), and<BR>
 *                             - Bit[0] of flags field is set to 1 (graceful
 *                             request)<BR>
 *                             This field indicates the platform-imposed
 *                             timeout, specified in milliseconds, enforced
 *                             from the point at which the platform sends a
 *                             graceful system shutdown notification to OSPM.
 *                             It indicates how long the platform waits for
 *                             OSPM to gracefully shutdown the system. On
 *                             timeout expiry, if the platform has not received
 *                             the system shutdown request from the PSCI agent,
 *                             or from OSPM for non-PSCI compliant systems, the
 *                             platform can proceed to forcefully shutdown the
 *                             system.<BR>
 *                             If the platform does not impose any timeout,
 *                             then this field is unused and must be set to
 *                             zero.
 *
 * If an agent has registered for system power state notifications with
 * SCMI_SystemPowerStateNotify(), the platform sends this notification to the
 * agent. Typically, the agent is either:
 *
 * - The OSPM that initiates a system power state transition in response to
 * this notification. The OSPM needs this notification to become aware that a
 * remote entity such as the management agent or the privileged agent is
 * requesting a graceful power state transition.
 *
 * - A management agent or a privileged agent that initiated a graceful power
 * state transition and is waiting for the OSPM to perform a power state
 * transition in response. The management agent or privileged agent needs this
 * notification to confirm that the platform controller has successfully
 * received the power state transition request from the PSCI agent, or from the
 * OSPM for non-PSCI compliant systems. See section 4.4.3.1
 * SYSTEM_POWER_STATE_NOTIFIER in the [SCMI Spec](@ref DOCS).
 *
 * Access macros:
 * - ::SCMI_SYS_NOTIFIER_GRACEFUL() - Graceful request
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_SystemPowerStateNotifier(uint32_t channel, uint32_t *agentId,
    uint32_t *flags, uint32_t *systemState, uint32_t *timeout);

#endif /* SCMI_SYS_H */

/** @} */

