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

#ifndef SCMI_MISC_H
#define SCMI_MISC_H

/*!
 * @addtogroup scmi_proto_misc
 * @{
 */

/*!
 * @file
 * @brief Header file containing the client-side API for the System Control and
 * Management Interface (SCMI) misc protocol.
 */

/* Defines */

/*!
 * @name SCMI misc protocol message IDs
 */
/** @{ */
/*! Set a control value */
#define SCMI_MSG_MISC_CONTROL_SET          0x3U
/*! Get a control value */
#define SCMI_MSG_MISC_CONTROL_GET          0x4U
/*! Initiate an action on a control value */
#define SCMI_MSG_MISC_CONTROL_ACTION       0x5U
/*! Get implementation build info */
#define SCMI_MSG_MISC_DISCOVER_BUILD_INFO  0x6U
/*! Get ROM passover data */
#define SCMI_MSG_MISC_ROM_PASSOVER_GET     0x7U
/*! Configure control notifications */
#define SCMI_MSG_MISC_CONTROL_NOTIFY       0x8U
/*! Get (reset) reason attributes */
#define SCMI_MSG_MISC_REASON_ATTRIBUTES    0x9U
/*! Read the reason the LM/system last booted/shutdown/reset */
#define SCMI_MSG_MISC_RESET_REASON         0xAU
/*! Get silicon info */
#define SCMI_MSG_MISC_SI_INFO              0xBU
/*! Get build config name */
#define SCMI_MSG_MISC_CFG_INFO             0xCU
/*! Get system log */
#define SCMI_MSG_MISC_SYSLOG               0xDU
/*! Read control notification event */
#define SCMI_MSG_MISC_CONTROL_EVENT        0x0U
/** @} */

/*!
 * @name SCMI max misc argument lengths
 */
/** @{ */
/*! Max length of the returned build date */
#define SCMI_MISC_MAX_BUILDDATE  16U
/*! Max length of the returned build time */
#define SCMI_MISC_MAX_BUILDTIME  16U
/*! Max length of the returned reason name */
#define SCMI_MISC_MAX_NAME       16U
/*! Max length of the returned silicon name */
#define SCMI_MISC_MAX_SINAME     16U
/*! Max length of the returned cfg name */
#define SCMI_MISC_MAX_CFGNAME    16U
/*! Max number value words */
#define SCMI_MISC_MAX_VAL_T      SCMI_ARRAY(8U, uint32_t)
/*! Max number return words */
#define SCMI_MISC_MAX_VAL        SCMI_ARRAY(8U, uint32_t)
/*! Max number argument words */
#define SCMI_MISC_MAX_ARG_T      SCMI_ARRAY(12U, uint32_t)
/*! Max number return words */
#define SCMI_MISC_MAX_RTN        SCMI_ARRAY(8U, uint32_t)
/*! Max number passover words */
#define SCMI_MISC_MAX_PASSOVER   SCMI_ARRAY(8U, uint32_t)
/*! Max number of extended shutdown info words */
#define SCMI_MISC_MAX_EXTINFO    SCMI_ARRAY(16U, uint32_t)
/*! Max number syslog words */
#define SCMI_MISC_MAX_SYSLOG     SCMI_ARRAY(8U, uint32_t)
/** @} */

/*!
 * @name SCMI actual misc argument lengths
 */
/** @{ */
/*! Actual number of value words sent */
#define SCMI_MISC_NUM_VAL_T     msgTx->numVal
/*! Actual number of return words returned */
#define SCMI_MISC_NUM_VAL       msgRx->numVal
/*! Actual number of argument words sent */
#define SCMI_MISC_NUM_ARG_T     msgTx->numArg
/*! Actual number of return words returned */
#define SCMI_MISC_NUM_RTN       msgRx->numRtn
/*! Actual number of passover words returned */
#define SCMI_MISC_NUM_PASSOVER  msgRx->numPassover
/*! Actual number of extended shutdown info words returned */
#define SCMI_MISC_NUM_EXTINFO   SCMI_MISC_SHUTDOWN_FLAG_EXT_LEN(msgRx->shutdownFlags)
/*! Actual number of syslog words returned */
#define SCMI_MISC_NUM_SYSLOG    SCMI_MISC_NUM_LOG_FLAGS_NUM_LOGS(msgRx->numLogFlags)
/** @} */

/*!
 * @name SCMI Control ID Flags
 */
/** @{ */
/*! Flag bit indicating board control */
#define SCMI_MISC_CTRL_FLAG_BRD  0x8000U
/** @} */

/* Macros */

/*!
 * @name SCMI misc protocol attributes
 */
/** @{ */
/*! Number of board controls */
#define SCMI_MISC_PROTO_ATTR_NUM_BRD_CTRL(x)  (((x) & 0xFF000000U) >> 24U)
/*! Number of reasons */
#define SCMI_MISC_PROTO_ATTR_NUM_REASON(x)    (((x) & 0xFF0000U) >> 16U)
/*! Number of device controls */
#define SCMI_MISC_PROTO_ATTR_NUM_DEV_CTRL(x)  (((x) & 0xFFFFU) >> 0U)
/** @} */

/*!
 * @name SCMI reason flags
 */
/** @{ */
/*! System */
#define SCMI_MISC_REASON_FLAG_SYSTEM(x)  (((x) & 0x1U) << 0U)
/** @} */

/*!
 * @name SCMI boot reason flags
 */
/** @{ */
/*! Valid */
#define SCMI_MISC_BOOT_FLAG_VLD(x)      (((x) & 0x80000000U) >> 31U)
/*! Valid origin */
#define SCMI_MISC_BOOT_FLAG_ORG_VLD(x)  (((x) & 0x10000000U) >> 28U)
/*! LM source of action */
#define SCMI_MISC_BOOT_FLAG_ORIGIN(x)   (((x) & 0xF000000U) >> 24U)
/*! Valid error ID */
#define SCMI_MISC_BOOT_FLAG_ERR_VLD(x)  (((x) & 0x800000U) >> 23U)
/*! Error ID */
#define SCMI_MISC_BOOT_FLAG_ERR_ID(x)   (((x) & 0x7FFF00U) >> 8U)
/*! Reason */
#define SCMI_MISC_BOOT_FLAG_REASON(x)   (((x) & 0xFFU) >> 0U)
/** @} */

/*!
 * @name SCMI shutdown reason flags
 */
/** @{ */
/*! Valid */
#define SCMI_MISC_SHUTDOWN_FLAG_VLD(x)      (((x) & 0x80000000U) >> 31U)
/*! Number of valid extended info words */
#define SCMI_MISC_SHUTDOWN_FLAG_EXT_LEN(x)  (((x) & 0x60000000U) >> 29U)
/*! Valid origin */
#define SCMI_MISC_SHUTDOWN_FLAG_ORG_VLD(x)  (((x) & 0x10000000U) >> 28U)
/*! LM source of action */
#define SCMI_MISC_SHUTDOWN_FLAG_ORIGIN(x)   (((x) & 0xF000000U) >> 24U)
/*! Valid error ID */
#define SCMI_MISC_SHUTDOWN_FLAG_ERR_VLD(x)  (((x) & 0x800000U) >> 23U)
/*! Error ID */
#define SCMI_MISC_SHUTDOWN_FLAG_ERR_ID(x)   (((x) & 0x7FFF00U) >> 8U)
/*! Reason */
#define SCMI_MISC_SHUTDOWN_FLAG_REASON(x)   (((x) & 0xFFU) >> 0U)
/** @} */

/*!
 * @name SCMI misc num log flags
 */
/** @{ */
/*! Number of remaining log words */
#define SCMI_MISC_NUM_LOG_FLAGS_REMAING_LOGS(x)  (((x) & 0xFFF00000U) >> 20U)
/*! Number of log words that are returned by this call */
#define SCMI_MISC_NUM_LOG_FLAGS_NUM_LOGS(x)      (((x) & 0xFFFU) >> 0U)
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
int32_t SCMI_MiscProtocolVersion(uint32_t channel, uint32_t *version);

/*!
 * Get protocol attributes.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[out]    attributes  Protocol attributes:<BR>
 *                            Bits[31:24] Number of board controls.<BR>
 *                            Bits[23:16] Number of reasons.<BR>
 *                            Bits[15:0] Number of device controls
 *
 * This function returns the implementation details associated with this
 * protocol.
 *
 * Access macros:
 * - ::SCMI_MISC_PROTO_ATTR_NUM_BRD_CTRL() - Number of board controls
 * - ::SCMI_MISC_PROTO_ATTR_NUM_REASON() - Number of reasons
 * - ::SCMI_MISC_PROTO_ATTR_NUM_DEV_CTRL() - Number of device controls
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_MiscProtocolAttributes(uint32_t channel, uint32_t *attributes);

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
 * ::SCMI_MSG_MISC_CONTROL_SET.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: in case the message is implemented and available to
 *   use.
 * - ::SCMI_ERR_NOT_FOUND: if the message identified by \a messageId is
 *   invalid or not implemented.
 */
int32_t SCMI_MiscProtocolMessageAttributes(uint32_t channel,
    uint32_t messageId, uint32_t *attributes);

/*!
 * Set a control value.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[in]     ctrlId   Identifier for the control
 * @param[in]     numVal   Size of the value data
 * @param[in]     val      Value data array
 *
 * This function allows the calling agent to set a control value. No
 * aggregation is done and controls are exclusively access controlled. Max
 * number of data words is ::SCMI_MISC_MAX_VAL_T. The \a ctrlId parameter is a
 * device control unless the ::SCMI_MISC_CTRL_FLAG_BRD bit is set to make it a
 * board control.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the control is set successfully.
 * - ::SCMI_ERR_NOT_FOUND: if \a ctrlId does not point to a valid control.
 * - ::SCMI_ERR_DENIED: if the calling agent is not allowed to set this
 *   control.
 */
int32_t SCMI_MiscControlSet(uint32_t channel, uint32_t ctrlId,
    uint32_t numVal, const uint32_t *val);

/*!
 * Get a control value.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[in]     ctrlId   Identifier for the control
 * @param[out]    numVal   Size of the return data in words
 * @param[out]    val      Return data array
 *
 * This function allows the calling agent to get a control value. Max number of
 * data words is ::SCMI_MISC_MAX_VAL. The \a ctrlId parameter is a device
 * control unless the ::SCMI_MISC_CTRL_FLAG_BRD bit is set to make it a board
 * control.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the control is returned successfully.
 * - ::SCMI_ERR_NOT_FOUND: if \a ctrlId does not point to a valid control.
 * - ::SCMI_ERR_DENIED: if the calling agent is not allowed to get this
 *   control.
 */
int32_t SCMI_MiscControlGet(uint32_t channel, uint32_t ctrlId,
    uint32_t *numVal, uint32_t *val);

/*!
 * Initiate an action on a control value.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[in]     ctrlId   Identifier for the control
 * @param[in]     action   Action for the control
 * @param[in]     numArg   Size of the argument data
 * @param[in]     arg      Argument data array
 * @param[out]    numRtn   Size of the return data in words
 * @param[out]    rtn      Return data array
 *
 * This function allows the calling agent to initiate an action on a control.
 * Actions and action parameters are specific to a control. Max number of
 * argument words is ::SCMI_MISC_MAX_ARG_T. Max number of return words is
 * ::SCMI_MISC_MAX_RTN. The \a ctrlId parameter is a device control unless the
 * ::SCMI_MISC_CTRL_FLAG_BRD bit is set to make it a board control.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the action is successfully.
 * - ::SCMI_ERR_NOT_FOUND: if \a ctrlId does not point to a valid control.
 * - ::SCMI_ERR_DENIED: if the calling agent is not allowed to initiate the
 *   action on this control.
 */
int32_t SCMI_MiscControlAction(uint32_t channel, uint32_t ctrlId,
    uint32_t action, uint32_t numArg, const uint32_t *arg, uint32_t *numRtn,
    uint32_t *rtn);

/*!
 * Get implementation build info.
 *
 * @param[in]     channel      A2P channel for comms
 * @param[out]    buildNum     Build number
 * @param[out]    buildCommit  Most significant 32 bits of the git commit hash
 * @param[out]    buildDate    Date of build. Null terminated ASCII string of
 *                             up to 16 bytes in length
 * @param[out]    buildTime    Time of build. Null terminated ASCII string of
 *                             up to 16 bytes in length
 *
 * This function is used to obtain information about the build including the
 * git commit hash, git build number, date and time. Max length of the build
 * date is ::SCMI_MISC_MAX_BUILDDATE. Max length of the time is
 * ::SCMI_MISC_MAX_BUILDTIME.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: in case the build info is returned.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the data is not available.
 */
int32_t SCMI_MiscDiscoverBuildInfo(uint32_t channel, uint32_t *buildNum,
    uint32_t *buildCommit, uint8_t *buildDate, uint8_t *buildTime);

/*!
 * Get ROM passover data.
 *
 * @param[in]     channel      A2P channel for comms
 * @param[out]    numPassover  Size of the passover data in words
 * @param[out]    passover     Passover data array
 *
 * This function is used to obtain the ROM passover data. The returned block of
 * words is structured as defined in the ROM passover section in the SoC RM.
 * Max number of passover words is ::SCMI_MISC_MAX_PASSOVER.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: in case the ROM passover data is returned.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the data is not available.
 */
int32_t SCMI_MiscRomPassoverGet(uint32_t channel, uint32_t *numPassover,
    uint32_t *passover);

/*!
 * Configure control notifications.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[in]     ctrlId   Identifier for the control
 * @param[in]     flags    Notification flags, varies by control
 *
 * This function allows an agent to enable/disable notification for a control.
 * The \a ctrlId parameter is a device control unless the
 * ::SCMI_MISC_CTRL_FLAG_BRD bit is set to make it a board control.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the notification successfully updated.
 * - ::SCMI_ERR_NOT_FOUND: if the LM identified by \a ctrlId does not exist.
 * - ::SCMI_ERR_INVALID_PARAMETERS, if the input attributes flag specifies
 *   unsupported or invalid configurations.
 * - ::SCMI_ERR_DENIED: if the calling agent is not permitted to request the
 *   notification.
 */
int32_t SCMI_MiscControlNotify(uint32_t channel, uint32_t ctrlId,
    uint32_t flags);

/*!
 * Get (reset) reason attributes.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in]     reasonId    Identifier for the reason
 * @param[out]    attributes  Reason attributes. This parameter has the
 *                            following format:<BR>
 *                            Bits[31:0] Reserved, must be zero
 * @param[out]    name        Null-terminated ASCII string of up to 16 bytes in
 *                            length describing the reason
 *
 * This function returns the attributes for a reason. Reasons are associated
 * with the system and LM reasons for boot, shutdown, and reset.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if valid reason attributes are returned.
 * - ::SCMI_ERR_NOT_FOUND: if \a reasonId pertains to a non-existent reason.
 */
int32_t SCMI_MiscReasonAttributes(uint32_t channel, uint32_t reasonId,
    uint32_t *attributes, uint8_t *name);

/*!
 * Read the reason the LM/system last booted/shutdown/reset.
 *
 * @param[in]     channel        A2P channel for comms
 * @param[in]     flags          Reason flags. This parameter has the following
 *                               format:<BR>
 *                               Bits[31:1] Reserved, must be zero.<BR>
 *                               Bit[0] System:<BR>
 *                               Set to 1 to return the system reason.<BR>
 *                               Set to 0 to return the LM reason
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
 * This function returns the boot/shutdown/reset reason for the LM or system.
 * If an LM hasn't changed state since system boot then the LM reason will be
 * the same as the system reason. If possible to capture, it also returns the
 * LM that initiated the actions. Extended shutdown info words are also
 * returned if captured. The number depends on the shutdown reason. All info is
 * device specific. If the action is a reset then the boot and shutdown reasons
 * will be the same as a reset action consists of a shutdown+boot all occurring
 * for the same reason. Max number of extended shutdown info words is
 * ::SCMI_MISC_MAX_EXTINFO.
 *
 * Access macros:
 * - ::SCMI_MISC_REASON_FLAG_SYSTEM() - System
 * - ::SCMI_MISC_BOOT_FLAG_VLD() - Valid
 * - ::SCMI_MISC_BOOT_FLAG_ORG_VLD() - Valid origin
 * - ::SCMI_MISC_BOOT_FLAG_ORIGIN() - LM source of action
 * - ::SCMI_MISC_BOOT_FLAG_ERR_VLD() - Valid error ID
 * - ::SCMI_MISC_BOOT_FLAG_ERR_ID() - Error ID
 * - ::SCMI_MISC_BOOT_FLAG_REASON() - Reason
 * - ::SCMI_MISC_SHUTDOWN_FLAG_VLD() - Valid
 * - ::SCMI_MISC_SHUTDOWN_FLAG_EXT_LEN() - Number of valid extended info words
 * - ::SCMI_MISC_SHUTDOWN_FLAG_ORG_VLD() - Valid origin
 * - ::SCMI_MISC_SHUTDOWN_FLAG_ORIGIN() - LM source of action
 * - ::SCMI_MISC_SHUTDOWN_FLAG_ERR_VLD() - Valid error ID
 * - ::SCMI_MISC_SHUTDOWN_FLAG_ERR_ID() - Error ID
 * - ::SCMI_MISC_SHUTDOWN_FLAG_REASON() - Reason
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_MiscResetReason(uint32_t channel, uint32_t flags,
    uint32_t *bootFlags, uint32_t *shutdownFlags, uint32_t *extInfo);

/*!
 * Get silicon info.
 *
 * @param[in]     channel   A2P channel for comms
 * @param[out]    deviceId  Silicon specific device ID
 * @param[out]    siRev     Silicon specific revision
 * @param[out]    partNum   Silicon specific part number
 * @param[out]    siName    Silicon name/revision. Null terminated ASCII string
 *                          of up to 16 bytes in length
 *
 * This function returns silicon info. The deviceId,  siRev, and partNum format
 * are specific to the silicon.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_MiscSiInfo(uint32_t channel, uint32_t *deviceId,
    uint32_t *siRev, uint32_t *partNum, uint8_t *siName);

/*!
 * Get build config name.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[out]    mSel     Mode selector value
 * @param[out]    cfgName  Config (cfg) file basename
 *
 * This function returns the basename of the SM configuration (cfg) file and
 * the mSel value.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: in case the cfg name is returned.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the name is not available.
 */
int32_t SCMI_MiscCfgInfo(uint32_t channel, uint32_t *mSel,
    uint8_t *cfgName);

/*!
 * Get system log.
 *
 * @param[in]     channel      A2P channel for comms
 * @param[in]     flags        Device specific flags that might impact the data
 *                             returned or clearing of the data
 * @param[in]     logIndex     Index to the first log word. Will be the first
 *                             element in the return array
 * @param[out]    numLogFlags  Descriptor for the log data returned by this
 *                             call.<BR>
 *                             Bits[31:20] Number of remaining log words.<BR>
 *                             Bits[15:12] Reserved, must be zero.<BR>
 *                             Bits[11:0] Number of log words that are returned
 *                             by this call
 * @param[out]    syslog       Log data array
 *
 * This function returns the system log. The format of this log is device
 * specific.
 *
 * Access macros:
 * - ::SCMI_MISC_NUM_LOG_FLAGS_REMAING_LOGS() - Number of remaining log words
 * - ::SCMI_MISC_NUM_LOG_FLAGS_NUM_LOGS() - Number of log words that are
 *   returned by this call
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the syslog returned sucessfully.
 * - ::SCMI_ERR_NOT_SUPPORTED: if the syslog is not available.
 */
int32_t SCMI_MiscSyslog(uint32_t channel, uint32_t flags, uint32_t logIndex,
    uint32_t *numLogFlags, uint32_t *syslog);

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
int32_t SCMI_MiscNegotiateProtocolVersion(uint32_t channel,
    uint32_t version);

/*!
 * Read control notification event.
 *
 * @param[in]     channel  P2A notify channel for comms.
 * @param[out]    ctrlId   Identifier for the control that caused the event.
 * @param[out]    flags    Event flags, varies by control.
 *
 * If an agent has registered for control notifications with
 * SCMI_MiscControlNotify(), the platform sends notifications to the agent.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_MiscControlEvent(uint32_t channel, uint32_t *ctrlId,
    uint32_t *flags);

#endif /* SCMI_MISC_H */

/** @} */

