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

#ifndef SCMI_FUSA_H
#define SCMI_FUSA_H

/*!
 * @addtogroup scmi_proto_fusa
 * @{
 */

/*!
 * @file
 * @brief Header file containing the client-side API for the System Control and
 * Management Interface (SCMI) fusa protocol.
 */

/* Defines */

/*!
 * @name SCMI FuSa protocol message IDs
 */
/** @{ */
/*! Get current FuSa system state */
#define SCMI_MSG_FUSA_FEENV_STATE_GET        0x3U
/*! Configure F-EENV notifications */
#define SCMI_MSG_FUSA_FEENV_STATE_NOTIFY     0x5U
/*! Get S-EENV state */
#define SCMI_MSG_FUSA_SEENV_STATE_GET        0x6U
/*! Set S-EENV state */
#define SCMI_MSG_FUSA_SEENV_STATE_SET        0x7U
/*! Get fault state */
#define SCMI_MSG_FUSA_FAULT_GET              0x8U
/*! Set fault state */
#define SCMI_MSG_FUSA_FAULT_SET              0x9U
/*! Enable/disable fault notifications */
#define SCMI_MSG_FUSA_FAULT_GROUP_NOTIFY     0xAU
/*! Temporarily disable fault handling */
#define SCMI_MSG_FUSA_SCHECK_EVNTRIG         0xBU
/*! Request manually-triggered execution of sCheck test */
#define SCMI_MSG_FUSA_SCHECK_TEST_EXEC       0xEU
/*! Read F-EENV state change notification event */
#define SCMI_MSG_FUSA_FEENV_STATE_EVENT      0x0U
/*! Read S-EENV state request notification event */
#define SCMI_MSG_FUSA_SEENV_STATE_REQ_EVENT  0x1U
/*! Read fault notification event */
#define SCMI_MSG_FUSA_FAULT_EVENT            0x2U
/** @} */

/*!
 * @name SCMI FuSa F-EENV states
 */
/** @{ */
/*! Initial state during boot up */
#define SCMI_FUSA_FEENV_STATE_INIT             0U
/*! Waiting for all S-EENVs to be safety ready */
#define SCMI_FUSA_FEENV_STATE_PRE_SAFETY       1U
/*! Running in normal safety context */
#define SCMI_FUSA_FEENV_STATE_SAFETY_RUNTIME   2U
/*! Before SoC reset or shutdown transitions */
#define SCMI_FUSA_FEENV_STATE_SOC_TERMINATING  3U
/** @} */

/*!
 * @name SCMI FuSa S-EENV states
 */
/** @{ */
/*! S-EENV is disabled */
#define SCMI_FUSA_SEENV_STATE_DISABLED        0U
/*! Initial S-EENV state */
#define SCMI_FUSA_SEENV_STATE_INIT            1U
/*! S-EENV is ready to transition to the RUNTIME state */
#define SCMI_FUSA_SEENV_STATE_SAFETY_READY    2U
/*! Running in normal safety context */
#define SCMI_FUSA_SEENV_STATE_SAFETY_RUNTIME  3U
/*! Transitioned to a terminal state */
#define SCMI_FUSA_SEENV_STATE_TERMINAL        4U
/** @} */

/*!
 * @name SCMI FUSA ID
 */
/** @{ */
/*! S-EENV ID to use to discover the callers S-EENV ID */
#define SCMI_FUSA_ID_DISCOVER  0xFFFFFFFFU
/** @} */

/* Macros */

/*!
 * @name SCMI FuSa protocol attributes 1
 */
/** @{ */
/*! Number of fault sources */
#define SCMI_FUSA_PROTO_ATTR1_NUM_FAULT(x)     (((x) & 0xFFFF0000U) >> 16U)
/*! Number of S-EENV ID in the system */
#define SCMI_FUSA_PROTO_ATTR1_NUM_SEENV_ID(x)  (((x) & 0xFF00U) >> 8U)
/*! Number of S-EENV LM in the system */
#define SCMI_FUSA_PROTO_ATTR1_NUM_SEENV_LM(x)  (((x) & 0xFFU) >> 0U)
/** @} */

/*!
 * @name SCMI FuSa notification flags
 */
/** @{ */
/*! Enable notifications for F-EENV state change */
#define SCMI_FUSA_FEENV_NOTIFY_ENABLE(x)  (((x) & 0x1U) << 0U)
/** @} */

/*!
 * @name SCMI FuSa fault get state flags
 */
/** @{ */
/*! Fault state */
#define SCMI_FUSA_FAULT_GET_STATE(x)  (((x) & 0x1U) >> 0U)
/** @} */

/*!
 * @name SCMI FuSa fault get state flags
 */
/** @{ */
/*! Fault state */
#define SCMI_FUSA_FAULT_SET_STATE(x)  (((x) & 0x3U) << 0U)
/** @} */

/*!
 * @name SCMI FuSa fault event flags
 */
/** @{ */
/*! Fault state (1 detected, 0 resolved) */
#define SCMI_FUSA_FAULT_FLAG_STATE(x)  (((x) & 0x1U) >> 0U)
/** @} */

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
 * version 1.0.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_FusaProtocolVersion(uint32_t channel, uint32_t *version);

/*!
 * Get protocol attributes.
 *
 * @param[in]     channel      A2P channel for comms
 * @param[out]    attributes1  Protocol attributes 1:<BR>
 *                             Bits[31:16] Number of Fault sources (this number
 *                             defines valid range of the fault ID identifiers
 *                             used in the fault functions)<BR>
 *                             Bits[15:8] Number of S-EENV ID in the system<BR>
 *                             Bits[7:0] Number of S-EENV LM in the system (not
 *                             counting the F-EENV itself)
 * @param[out]    attributes2  Protocol attributes 2:<BR>
 *                             Bits[31:0] Reserved, must be zero
 *
 * This function returns the implementation details associated with this
 * protocol.
 *
 * Access macros:
 * - ::SCMI_FUSA_PROTO_ATTR1_NUM_FAULT() - Number of fault sources
 * - ::SCMI_FUSA_PROTO_ATTR1_NUM_SEENV_ID() - Number of S-EENV ID in the system
 * - ::SCMI_FUSA_PROTO_ATTR1_NUM_SEENV_LM() - Number of S-EENV LM in the system
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_FusaProtocolAttributes(uint32_t channel, uint32_t *attributes1,
    uint32_t *attributes2);

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
 * ::SCMI_MSG_FUSA_FEENV_STATE_GET.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: in case the message is implemented and available to
 *   use.
 * - ::SCMI_ERR_NOT_SUPPORTED: if FuSa not an enabled feature.
 * - ::SCMI_ERR_NOT_FOUND: if the message identified by \a messageId is
 *   invalid or not implemented.
 */
int32_t SCMI_FusaProtocolMessageAttributes(uint32_t channel,
    uint32_t messageId, uint32_t *attributes);

/*!
 * Get current FuSa system state.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[out]    feenvState  Parameter identifying the safety state of the
 *                            F-EENV
 * @param[out]    mselMode    Mode selector value as returned by SAF
 *
 * This function is used to get the current FuSa system state and operation
 * mode selected by the SAF mSel. An example state is
 * ::SCMI_FUSA_FEENV_STATE_PRE_SAFETY.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the current F-EENV state is returned successfully.
 * - ::SCMI_ERR_NOT_SUPPORTED: if FuSa not an enabled feature or the caller
 *   is not an S-EENV.
 * - ::SCMI_ERR_DENIED: if the calling agent is not allowed to get the F-EENV
 *   state.
 */
int32_t SCMI_FusaFeenvStateGet(uint32_t channel, uint32_t *feenvState,
    uint32_t *mselMode);

/*!
 * Configure F-EENV notifications.
 *
 * @param[in]     channel       A2P channel for comms
 * @param[in]     notifyEnable  Notification flags:<BR>
 *                              Bits[31:1] Reserved, must be zero.<BR>
 *                              Bit[0] State change notification:<BR>
 *                              Set to 1 to send notification.<BR>
 *                              Set to 0 if no notification
 *
 * This function is used to request notification on FuSa state changes.
 *
 * Access macros:
 * - ::SCMI_FUSA_FEENV_NOTIFY_ENABLE() - Enable notifications for F-EENV state
 *   change
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the notification state successfully updated.
 * - ::SCMI_ERR_NOT_SUPPORTED: if FuSa not an enabled feature or the caller
 *   is not an S-EENV.
 * - ::SCMI_ERR_DENIED: if the calling agent is not permitted to request the
 *   notification.
 */
int32_t SCMI_FusaFeenvStateNotify(uint32_t channel, uint32_t notifyEnable);

/*!
 * Get S-EENV state.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in,out] seenvId     Identifier of the S-EENV whose state is
 *                            requested. This field is:<BR>
 *                            - populated with the S-EENV ID of the calling
 *                            agent, when the \a seenvId parameter passed via
 *                            the function is 0xFFFFFFFF.<BR>
 *                            - identical to the \a seenvId field passed via
 *                            the calling parameters, in all other cases
 * @param[out]    lmId        Identifier of the LM which contains the S-EENV
 *                            identified by \a seenvId
 * @param[out]    seenvState  Parameter identifying the safety state of the
 *                            S-EENV
 *
 * This function is used by any S-EENV to retrieve information about itself as
 * it is recorded in the F-EENV internal memory. An example state is
 * ::SCMI_FUSA_SEENV_STATE_INIT.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the S-EENV state is returned successfully.
 * - ::SCMI_ERR_NOT_FOUND: if \a seenvId is out of range or not an S-EENV if
 *   self identifying.
 * - ::SCMI_ERR_NOT_SUPPORTED: if FuSa not an enabled feature or the caller
 *   is not an S-EENV.
 */
int32_t SCMI_FusaSeenvStateGet(uint32_t channel, uint32_t *seenvId,
    uint32_t *lmId, uint32_t *seenvState);

/*!
 * Set S-EENV state.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in]     seenvState  Parameter to set the safety state of the S-EENV
 * @param[in]     pingCookie  Cookie value last sent by the F-EENV
 *
 * This function is used by the S-EENVs to inform SM about transition to a new
 * state. The SM accepts this transition and records the S-EENV state
 * internally. Collecting the state information from all S-EENVs is important
 * for SM to transition between various F-EENV states. An example state is
 * ::SCMI_FUSA_SEENV_STATE_SAFETY_READY.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the S-EENV state is set successfully.
 * - ::SCMI_ERR_NOT_SUPPORTED: if FuSa not an enabled feature or the caller
 *   is not an S-EENV.
 * - ::SCMI_ERR_INVALID_PARAMETERS: if the requested state is invalid.
 */
int32_t SCMI_FusaSeenvStateSet(uint32_t channel, uint32_t seenvState,
    uint32_t pingCookie);

/*!
 * Get fault state.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[in]     faultId  Global fault identifier
 * @param[out]    flags    State of the fault:<BR>
 *                         Bits[31:1] Reserved, must be zero.<BR>
 *                         Bit[0] Fault state.<BR>
 *                         Set to 1 if the fault is set.<BR>
 *                         Set to 0 if the fault is cleared
 *
 * This function is used by the S-EENVs to determine an immediate state of a SW
 * fault (NCF). The agents (S-EENVs) shall not use this (and no other) RPC call
 * during fault resolution process. The fault ID and fault resolution state are
 * communicated directly using the direct channel.
 *
 * Access macros:
 * - ::SCMI_FUSA_FAULT_GET_STATE() - Fault state
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the fault state is returned successfully.
 * - ::SCMI_ERR_NOT_SUPPORTED: if FuSa not an enabled feature or the caller
 *   is not an S-EENV.
 * - ::SCMI_ERR_NOT_FOUND: if \a faultId is invalid.
 * - ::SCMI_ERR_DENIED: if the calling agent is not permitted to get the
 *   state.
 */
int32_t SCMI_FusaFaultGet(uint32_t channel, uint32_t faultId,
    uint32_t *flags);

/*!
 * Set fault state.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[in]     faultId  Global fault identifier
 * @param[in]     flags    State of the fault:<BR>
 *                         Bits[31:2] Reserved, must be zero.<BR>
 *                         Bit[1:0] Fault state.<BR>
 *                         Set to 0 to set the fault.<BR>
 *                         Set to 1 to clear the fault.<BR>
 *                         Set to 2 to report the fault is recovered.<BR>
 *                         Set to 3 to report the fault could not be reovered
 *
 * This function is used by the S-EENVs to assert a SW fault (NCF) at the FCCU
 * module.
 *
 * Access macros:
 * - ::SCMI_FUSA_FAULT_SET_STATE() - Fault state
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the fault state is set successfully.
 * - ::SCMI_ERR_NOT_SUPPORTED: if FuSa not an enabled feature or the caller
 *   is not an S-EENV.
 * - ::SCMI_ERR_NOT_FOUND: if \a faultId is invalid.
 * - ::SCMI_ERR_DENIED: if the calling agent is not permitted to set the
 *   state.
 */
int32_t SCMI_FusaFaultSet(uint32_t channel, uint32_t faultId,
    uint32_t flags);

/*!
 * Enable/disable fault notifications.
 *
 * @param[in]     channel          A2P channel for comms
 * @param[in]     faultIdFirst     First global fault identifier to be
 *                                 configured
 * @param[in]     faultMask        Mask of faults to modify.<BR>
 *                                 Set to 1 to modify the fault
 *                                 notification.<BR>
 *                                 Set to 0 to leave unmodified
 * @param[in]     notifyEnable     Fault notification enables.<BR>
 *                                 Set to 1 to enable a fault notification.<BR>
 *                                 Set to 0 to disable a fault
 *                                 notification.<BR>
 *                                 Only bits also set to 1 in \a faultMask are
 *                                 modified
 * @param[out]    faultIdFirstGet  Return equal to \a faultIdFirst
 * @param[out]    notifyEnabled    Fault notification enabled state.<BR>
 *                                 Set to 1 indicates the fault notification is
 *                                 enabled.<BR>
 *                                 Set to 0 indicates the fault notification is
 *                                 disabled
 *
 * This function is used to request notification on fault occurrence for one or
 * more faults. Up to 32 faults can be enabled or disabled using one call. The
 * \a faultIdFirst parameter is the faultId bit[0] of the other parameters maps
 * to. Each higher bit then maps to the next faultId.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the fault notification is updated successfully for
 *   some faults.
 * - ::SCMI_ERR_NOT_SUPPORTED: if FuSa not an enabled feature or the caller
 *   is not an S-EENV.
 * - ::SCMI_ERR_NOT_FOUND: if \a faultIdFirst is invalid.
 * - ::SCMI_ERR_DENIED: if the calling agent is not permitted to modify any
 *   of the requested notifications.
 */
int32_t SCMI_FusaFaultGroupNotify(uint32_t channel, uint32_t faultIdFirst,
    uint32_t faultMask, uint32_t notifyEnable, uint32_t *faultIdFirstGet,
    uint32_t *notifyEnabled);

/*!
 * Temporarily disable fault handling.
 *
 * @param[in]     channel  A2P channel for comms
 *
 * This function is used by the S-EENV during sCheck event processing to
 * temporarily disable user handling of faults being tested. This is used
 * whenever an S-EENV sCheck is about to inject faults for testing purposes and
 * needs to pause normal SM fault processing. In this mode, the injected faults
 * are handled internally by SAF.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if fault handling disabled for the caller.
 * - ::SCMI_ERR_NOT_SUPPORTED: if FuSa not an enabled feature or the caller
 *   is not an S-EENV.
 * - ::SCMI_ERR_DENIED: if the calling agent is not permitted to request this
 *   command.
 */
int32_t SCMI_FusaScheckEvntrig(uint32_t channel);

/*!
 * Request manually-triggered execution of sCheck test.
 *
 * @param[in]     channel       A2P channel for comms
 * @param[in]     targetTestId  Identifier of sCheck target test to be executed
 *
 * This function is used by the S-EENV to request manually-triggered execution
 * of sCheck test. The target test is identified using the \a targetTestId
 * parameter. The test identifiers are assigned during SAF sCheck user
 * configuration.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if fault handling disabled for the caller.
 * - ::SCMI_ERR_NOT_SUPPORTED: if FuSa not an enabled feature or the caller
 *   is not an S-EENV.
 * - ::SCMI_ERR_DENIED: if the calling agent is not permitted to request an
 *   sCheck.
 */
int32_t SCMI_FusaScheckTestExec(uint32_t channel, uint32_t targetTestId);

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
int32_t SCMI_FusaNegotiateProtocolVersion(uint32_t channel,
    uint32_t version);

/*!
 * Read F-EENV state change notification event.
 *
 * @param[in]     channel     P2A notify channel for comms.
 * @param[out]    feenvState  Parameter identifying the requested state of the
 *                            F-EENV.
 * @param[out]    mselMode    Mode selector value as returned by SAF.
 *
 * This notification is sent when the SM (F-EENV) FuSa state machine is
 * requested to gracefully transition to a new state. See all F-EENV states for
 * the SCMI_FusaFeenvStateGet() function description. FuSa relevant agents
 * (S-EENVs) may react to the notification also by advancing to a new state
 * within their S-EENV state machine.
 *
 * To receive the notification, agents need to subscribe using the
 * SCMI_FusaFeenvStateNotify() function.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_FusaFeenvStateEvent(uint32_t channel, uint32_t *feenvState,
    uint32_t *mselMode);

/*!
 * Read S-EENV state request notification event.
 *
 * @param[in]     channel     P2A notify channel for comms.
 * @param[out]    pingCookie  Random cookie value
 *
 * This notification can be sent by the SM (F-EENV) any time to request the
 * S-EENVs to report their state using the SCMI_FusaSeenvStateSet() function.
 *
 * To receive the notification, agents need to subscribe using the
 * SCMI_FusaFeenvStateNotify() function. I.e. this notification is sent to any
 * S-EENV which has previously subscribed to F-EENV state notifications.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_FusaSeenvStateReqEvent(uint32_t channel, uint32_t *pingCookie);

/*!
 * Read fault notification event.
 *
 * @param[in]     channel  P2A notify channel for comms.
 * @param[out]    faultId  Global fault identifier
 * @param[out]    flags    Fault state flags
 *
 * This notification is sent by the SM fault handler called from the SAF eMCEM
 * driver when the FCCU reports a fault or when a previously reported fault has
 * been successfully resolved. This is an informative notification broadcast to
 * the agents who subscribed using the SCMI_FusaFaultGroupNotify() function.
 *
 * Access macros:
 * - ::SCMI_FUSA_FAULT_FLAG_STATE() - Fault state (1 detected, 0 resolved)
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_FusaFaultEvent(uint32_t channel, uint32_t *faultId,
    uint32_t *flags);

#endif /* SCMI_FUSA_H */

/** @} */

