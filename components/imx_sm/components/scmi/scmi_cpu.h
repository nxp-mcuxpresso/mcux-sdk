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

#ifndef SCMI_CPU_H
#define SCMI_CPU_H

/*!
 * @addtogroup scmi_proto_cpu
 * @{
 */

/*!
 * @file
 * @brief Header file containing the client-side API for the System Control and
 * Management Interface (SCMI) cpu protocol.
 */

/* Defines */

/*!
 * @name SCMI cpu protocol message IDs
 */
/** @{ */
/*! Get CPU attributes */
#define SCMI_MSG_CPU_ATTRIBUTES          0x3U
/*! Start a CPU */
#define SCMI_MSG_CPU_START               0x4U
/*! Stop a CPU */
#define SCMI_MSG_CPU_STOP                0x5U
/*! Set reset vector */
#define SCMI_MSG_CPU_RESET_VECTOR_SET    0x6U
/*! Set a CPU sleep target mode */
#define SCMI_MSG_CPU_SLEEP_MODE_SET      0x7U
/*! Set a CPU IRQ wake mask */
#define SCMI_MSG_CPU_IRQ_WAKE_SET        0x8U
/*! Set a CPU non-IRQ wake mask */
#define SCMI_MSG_CPU_NON_IRQ_WAKE_SET    0x9U
/*! Configure a list of power domain LPM configs */
#define SCMI_MSG_CPU_PD_LPM_CONFIG_SET   0xAU
/*! Configure a list of peripheral LPM configs */
#define SCMI_MSG_CPU_PER_LPM_CONFIG_SET  0xBU
/*! Get info for a CPU */
#define SCMI_MSG_CPU_INFO_GET            0xCU
/** @} */

/*!
 * @name SCMI max cpu argument lengths
 */
/** @{ */
/*! Max length of the returned CPU name */
#define SCMI_CPU_MAX_NAME          16U
/*! Max number mask words */
#define SCMI_CPU_MAX_MASK_T        SCMI_ARRAY(12U, uint32_t)
/*! Max number of configs sent in one call */
#define SCMI_CPU_MAX_PDCONFIGS_T   SCMI_ARRAY(8U, scmi_pd_lpm_config_t)
/*! Max number of configs sent in one call */
#define SCMI_CPU_MAX_PERCONFIGS_T  SCMI_ARRAY(8U, scmi_per_lpm_config_t)
/** @} */

/*!
 * @name SCMI actual cpu argument lengths
 */
/** @{ */
/*! Actual number of mask words sent */
#define SCMI_CPU_NUM_MASK_T        msgTx->numMask
/*! Actual number of configs sent */
#define SCMI_CPU_NUM_PDCONFIGS_T   numConfigs
/*! Actual number of configs sent */
#define SCMI_CPU_NUM_PERCONFIGS_T  numConfigs
/** @} */

/*!
 * @name SCMI CPU sleep modes
 */
/** @{ */
/*! On */
#define SCMI_CPU_SLEEP_RUN      0U
/*! Wait mode */
#define SCMI_CPU_SLEEP_WAIT     1U
/*! Stop mode */
#define SCMI_CPU_SLEEP_STOP     2U
/*! Suspend mode */
#define SCMI_CPU_SLEEP_SUSPEND  3U
/** @} */

/*!
 * @name SCMI CPU LPM settings
 */
/** @{ */
/*! Off */
#define SCMI_CPU_LPM_SETTING_ON_NEVER          0U
/*! Power on when domain is in RUN, off in WAIT/STOP/SUSPEND */
#define SCMI_CPU_LPM_SETTING_ON_RUN            1U
/*! Power on when domain is in RUN/WAIT, off in STOP/SUSPEND */
#define SCMI_CPU_LPM_SETTING_ON_RUN_WAIT       2U
/*! Power on when domain is in RUN/WAIT/STOP, off in SUSPEND */
#define SCMI_CPU_LPM_SETTING_ON_RUN_WAIT_STOP  3U
/*! Power always on */
#define SCMI_CPU_LPM_SETTING_ON_ALWAYS         4U
/** @} */

/*!
 * @name SCMI CPU run modes
 */
/** @{ */
/*! On */
#define SCMI_CPU_RUN_RUN    0U
/*! Wait mode */
#define SCMI_CPU_RUN_WAIT   1U
/*! Stop mode */
#define SCMI_CPU_RUN_STOP   2U
/*! Sleep mode */
#define SCMI_CPU_RUN_SLEEP  3U
/** @} */

/* Macros */

/*!
 * @name SCMI cpu protocol attributes
 */
/** @{ */
/*! Number of CPUs */
#define SCMI_CPU_PROTO_ATTR_NUM_CPUS(x)  (((x) & 0xFFFFU) >> 0U)
/** @} */

/*!
 * @name SCMI cpu reset vector set flags
 */
/** @{ */
/*! Resume flag */
#define SCMI_CPU_VEC_FLAGS_RESUME(x)  (((x) & 0x1U) << 31U)
/*! Start flag */
#define SCMI_CPU_VEC_FLAGS_START(x)   (((x) & 0x1U) << 30U)
/*! Boot flag */
#define SCMI_CPU_VEC_FLAGS_BOOT(x)    (((x) & 0x1U) << 29U)
/*! Table flag */
#define SCMI_CPU_VEC_FLAGS_TABLE(x)   (((x) & 0x1U) << 0U)
/** @} */

/*!
 * @name SCMI CPU sleep mode flags
 */
/** @{ */
/*! IRQ mux */
#define SCMI_CPU_FLAGS_IRQ_MUX(x)    (((x) & 0x1U) << 0U)
/*! Platform wake */
#define SCMI_CPU_FLAGS_PLAT_WAKE(x)  (((x) & 0x1U) << 1U)
/** @} */

/* Types */

/*!
 * SCMI CPU PD LPM configuration
 */
typedef struct
{
    /*! Power domain ID */
    uint32_t domainId;
    /*! LPM setting */
    uint32_t lpmSetting;
    /*! Retention mask */
    uint32_t retMask;
} scmi_pd_lpm_config_t;

/*!
 * SCMI CPU peripheral LPM configuration
 */
typedef struct
{
    /*! Peripheral ID */
    uint32_t perId;
    /*! LPM setting */
    uint32_t lpmSetting;
} scmi_per_lpm_config_t;

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
int32_t SCMI_CpuProtocolVersion(uint32_t channel, uint32_t *version);

/*!
 * Get protocol attributes.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[out]    attributes  Protocol attributes:<BR>
 *                            Bits[31:16] Reserved, must be zero.<BR>
 *                            Bits[15:0] Number of CPUs
 *
 * This function returns the implementation details associated with this
 * protocol.
 *
 * Access macros:
 * - ::SCMI_CPU_PROTO_ATTR_NUM_CPUS() - Number of CPUs
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 */
int32_t SCMI_CpuProtocolAttributes(uint32_t channel, uint32_t *attributes);

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
 * ::SCMI_MSG_CPU_ATTRIBUTES.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: in case the message is implemented and available to
 *   use.
 * - ::SCMI_ERR_NOT_FOUND: if the message identified by \a messageId is
 *   invalid or not implemented.
 */
int32_t SCMI_CpuProtocolMessageAttributes(uint32_t channel,
    uint32_t messageId, uint32_t *attributes);

/*!
 * Get CPU attributes.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in]     cpuId       Identifier for the CPU
 * @param[out]    attributes  CPU attributes:<BR>
 *                            Bits[31:0] Reserved, must be zero
 * @param[out]    name        A NULL terminated ASCII string with the CPU name,
 *                            of up to 16 bytes
 *
 * This function returns the attribute flags associated with a specific CPU.
 * The max name length is ::SCMI_CPU_MAX_NAME.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if valid attributes are returned.
 * - ::SCMI_ERR_NOT_FOUND: if \a cpuId does not point to a valid CPU.
 */
int32_t SCMI_CpuAttributes(uint32_t channel, uint32_t cpuId,
    uint32_t *attributes, uint8_t *name);

/*!
 * Start a CPU.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[in]     cpuId    Identifier for the CPU
 *
 * This function allows the calling agent to start a CPU. This function
 * implicitly powers up the domain containing the CPU. The reset vector is
 * latched on power up and must be set using SCMI_CpuResetVectorSet() before
 * starting the core.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the CPU is started successfully.
 * - ::SCMI_ERR_NOT_FOUND: if \a cpuId does not point to a valid CPU.
 * - ::SCMI_ERR_DENIED: if the calling agent is not allowed to start this
 *   CPU.
 */
int32_t SCMI_CpuStart(uint32_t channel, uint32_t cpuId);

/*!
 * Stop a CPU.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[in]     cpuId    Identifier for the CPU
 *
 * This function allows the calling agent to stop a CPU.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the CPU is stopped successfully.
 * - ::SCMI_ERR_NOT_FOUND: if \a cpuId does not point to a valid CPU.
 * - ::SCMI_ERR_DENIED: if the calling agent is not allowed to stop this CPU.
 */
int32_t SCMI_CpuStop(uint32_t channel, uint32_t cpuId);

/*!
 * Set reset vector.
 *
 * @param[in]     channel          A2P channel for comms
 * @param[in]     cpuId            Identifier for the CPU
 * @param[in]     flags            Reset vector flags:<BR>
 *                                 Bit[31] Resume flag.<BR>
 *                                 Set to 1 to update the reset vector used on
 *                                 resume.<BR>
 *                                 Bit[30] Boot flag.<BR>
 *                                 Set to 1 to update the reset vector used for
 *                                 boot.<BR>
 *                                 Bits[29:1] Reserved, must be zero.<BR>
 *                                 Bit[0] Table flag.<BR>
 *                                 Set to 1 if vector is the vector table base
 *                                 address.<BR>
 * @param[in]     resetVectorLow   Lower vector:<BR>
 *                                 If bit[0] of flags is 0, the lower 32 bits
 *                                 of the physical address where the CPU should
 *                                 execute from on reset.<BR>
 *                                 If bit[0] of flags is 1, the lower 32 bits
 *                                 of the vector table base address
 * @param[in]     resetVectorHigh  Upper vector:<BR>
 *                                 If bit[0] of flags is 0, the upper 32 bits
 *                                 of the physical address where the CPU should
 *                                 execute from on reset.<BR>
 *                                 If bit[0] of flags is 1, the upper 32 bits
 *                                 of the vector table base address
 *
 * This function configures the reset address for the CPU. Three addresses are
 * maintained:
 *
 * - Boot addresses which a CPU starts from when the LM is booted/reset, set
 * originally from the boot container
 *
 * - Start addresses which a CPU starts from when a CPU is started, set
 * originally from the boot addresses
 *
 * - Resume addresses which a CPU will start from when it exits
 * standby/suspend, set originally from the start addresses
 *
 * Note the start address is overwritten when an LM reboots. The resume address
 * is overwritten anytime a core boots. Also some CPUs allow the reset vector
 * (the address where the CPU will start execution) to be configured. Other
 * CPUs instead allow the base address of the vector table to be configured.
 * CPUs support one type or the other and if \a flags indicates the wrong type
 * then an error will be returned.
 *
 * Access macros:
 * - ::SCMI_CPU_VEC_FLAGS_RESUME() - Resume flag
 * - ::SCMI_CPU_VEC_FLAGS_START() - Start flag
 * - ::SCMI_CPU_VEC_FLAGS_BOOT() - Boot flag
 * - ::SCMI_CPU_VEC_FLAGS_TABLE() - Table flag
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the CPU reset vector is set successfully.
 * - ::SCMI_ERR_NOT_FOUND: if \a cpuId does not point to a valid CPU.
 * - ::SCMI_ERR_INVALID_PARAMETERS: if the requested vector type is not
 *   supported by this CPU.
 * - ::SCMI_ERR_DENIED: if the calling agent is not allowed to set the reset
 *   vector of this CPU.
 */
int32_t SCMI_CpuResetVectorSet(uint32_t channel, uint32_t cpuId,
    uint32_t flags, uint32_t resetVectorLow, uint32_t resetVectorHigh);

/*!
 * Set a CPU sleep target mode.
 *
 * @param[in]     channel    A2P channel for comms
 * @param[in]     cpuId      Identifier for the CPU
 * @param[in]     flags      Sleep mode flags:<BR>
 *                           Bits[31:1] Reserved, must be zero.<BR>
 *                           Bit[0] IRQ mux:<BR>
 *                           If set to 1 the wakeup mux source is the GIC, else
 *                           if 0 then the GPC
 * @param[in]     sleepMode  Target sleep mode
 *
 * This function allows the calling agent to set sleep mode of a CPU. The CPU
 * will transition to this mode on its next WFI. An example sleep mode is
 * ::SCMI_CPU_SLEEP_RUN.
 *
 * Access macros:
 * - ::SCMI_CPU_FLAGS_IRQ_MUX() - IRQ mux
 * - ::SCMI_CPU_FLAGS_PLAT_WAKE() - Platform wake
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the CPU is started successfully.
 * - ::SCMI_ERR_NOT_FOUND: if \a cpuId does not point to a valid CPU.
 * - ::SCMI_ERR_INVALID_PARAMETERS: if \a sleepMode or \a flags is invalid.
 * - ::SCMI_ERR_DENIED: if the calling agent is not allowed to configure this
 *   CPU.
 */
int32_t SCMI_CpuSleepModeSet(uint32_t channel, uint32_t cpuId,
    uint32_t flags, uint32_t sleepMode);

/*!
 * Set a CPU IRQ wake mask.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[in]     cpuId    Identifier for the CPU
 * @param[in]     maskIdx  Index of first mask to set
 * @param[in]     numMask  Number of masks to set
 * @param[in]     mask     Mask data array
 *
 * This function allows the calling agent set the masks for CPU IRQ wake
 * sources. The max number of mask words is ::SCMI_CPU_MAX_MASK_T.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the CPU is started successfully.
 * - ::SCMI_ERR_NOT_FOUND: if \a cpuId does not point to a valid CPU.
 * - ::SCMI_ERR_INVALID_PARAMETERS: if \a maskIdx or \a numMask is invalid.
 * - ::SCMI_ERR_DENIED: if the calling agent is not allowed to configure this
 *   CPU.
 */
int32_t SCMI_CpuIrqWakeSet(uint32_t channel, uint32_t cpuId,
    uint32_t maskIdx, uint32_t numMask, const uint32_t *mask);

/*!
 * Set a CPU non-IRQ wake mask.
 *
 * @param[in]     channel  A2P channel for comms
 * @param[in]     cpuId    Identifier for the CPU
 * @param[in]     maskIdx  Index of first mask to set
 * @param[in]     numMask  Number of masks to set
 * @param[in]     mask     Mask data array
 *
 * This function allows the calling agent set the masks for CPU non-IRQ wake
 * sources. The max number of mask words is ::SCMI_CPU_MAX_MASK_T.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the CPU is started successfully.
 * - ::SCMI_ERR_NOT_FOUND: if \a cpuId does not point to a valid CPU.
 * - ::SCMI_ERR_INVALID_PARAMETERS: if \a maskIdx or \a numMask is invalid.
 * - ::SCMI_ERR_DENIED: if the calling agent is not allowed to configure this
 *   CPU.
 */
int32_t SCMI_CpuNonIrqWakeSet(uint32_t channel, uint32_t cpuId,
    uint32_t maskIdx, uint32_t numMask, const uint32_t *mask);

/*!
 * Configure a list of power domain LPM configs.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in]     cpuId       Identifier for the CPU
 * @param[in]     numConfigs  Number of power domains to configure
 * @param[in]     pdConfigs   LPM configuration data array
 *
 * This function configures the LPM setting and retention mask for an array of
 * automatic power domains applied when a CPU enters a sleep mode. The LPM
 * setting determines which range of CPU sleep modes will leave the power
 * domain on. An example LPM setting is ::SCMI_CPU_LPM_SETTING_ON_NEVER. Note
 * each CPU can have different settings and the hardware aggregates these
 * settings to determine the domain power state. The retention mask is specific
 * to a power domain and a SoC. The max number of configs is
 * ::SCMI_CPU_MAX_PDCONFIGS_T.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the CPU is started successfully.
 * - ::SCMI_ERR_NOT_FOUND: if \a cpuId or a power domain does not exist.
 * - ::SCMI_ERR_INVALID_PARAMETERS: if \a numConfigs or an LPM setting is
 *   invalid.
 * - ::SCMI_ERR_DENIED: if the calling agent is not allowed to configure this
 *   CPU.
 */
int32_t SCMI_CpuPdLpmConfigSet(uint32_t channel, uint32_t cpuId,
    uint32_t numConfigs, const scmi_pd_lpm_config_t *pdConfigs);

/*!
 * Configure a list of peripheral LPM configs.
 *
 * @param[in]     channel     A2P channel for comms
 * @param[in]     cpuId       Identifier for the CPU
 * @param[in]     numConfigs  Number of peripherals to configure
 * @param[in]     perConfigs  LPM configuration data array
 *
 * This function configures the LPM setting for an array of peripherals applied
 * when a CPU enters a sleep mode. The LPM setting determines which range of
 * CPU sleep modes will affect a peripheral's low-power handshake signals (e.g.
 * IPG_STOP, Q_CHN) . An example LPM setting is
 * ::SCMI_CPU_LPM_SETTING_ON_NEVER. Note each CPU can have different settings
 * and the hardware aggregates these settings to determine the peripheral
 * low-power state. The max number of configs is ::SCMI_CPU_MAX_PERCONFIGS_T.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the CPU is started successfully.
 * - ::SCMI_ERR_NOT_FOUND: if \a cpuId or a peripheral ID does not exist.
 * - ::SCMI_ERR_INVALID_PARAMETERS: if \a numConfigs or an LPM setting is
 *   invalid.
 * - ::SCMI_ERR_DENIED: if the calling agent is not allowed to configure this
 *   CPU.
 */
int32_t SCMI_CpuPerLpmConfigSet(uint32_t channel, uint32_t cpuId,
    uint32_t numConfigs, const scmi_per_lpm_config_t *perConfigs);

/*!
 * Get info for a CPU.
 *
 * @param[in]     channel          A2P channel for comms
 * @param[in]     cpuId            Identifier for the CPU
 * @param[out]    runMode          Run mode for the CPU
 * @param[out]    sleepMode        Sleep mode for the CPU
 * @param[out]    resetVectorLow   Reset vector low 32 bits for the CPU
 * @param[out]    resetVectorHigh  Reset vector high 32 bits for the CPU
 *
 * This function allows the calling agent to get information about a CPU. This
 * includes the run mode, sleep mode, and current reset vector.
 *
 * @return Returns the status (::SCMI_ERR_SUCCESS = success).
 *
 * Return errors (see @ref SCMI_STATUS "SCMI error codes"):
 * - ::SCMI_ERR_SUCCESS: if the CPU info is returned successfully.
 * - ::SCMI_ERR_NOT_FOUND: if \a cpuId does not exist.
 */
int32_t SCMI_CpuInfoGet(uint32_t channel, uint32_t cpuId, uint32_t *runMode,
    uint32_t *sleepMode, uint32_t *resetVectorLow,
    uint32_t *resetVectorHigh);

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
int32_t SCMI_CpuNegotiateProtocolVersion(uint32_t channel,
    uint32_t version);

#endif /* SCMI_CPU_H */

/** @} */

