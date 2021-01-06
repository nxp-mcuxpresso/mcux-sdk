/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_ASMC_H_
#define _FSL_ASMC_H_

#include "fsl_common.h"

/*! @addtogroup asmc */
/*! @{ */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief ASMC driver version 2.0.1. */
#define FSL_ASMC_DRIVER_VERSION (MAKE_VERSION(2, 0, 1))
/*@}*/

/*!
 * @brief System Reset Status
 */
enum _asmc_system_reset_status_flags
{
    kASMC_LowLeakageWakeupResetFlag = ASMC_SRS_WAKEUP_MASK, /*!< Reset caused by LLWU module wakeup source. */
    kASMC_WatchdogResetFlag         = ASMC_SRS_WDOG1_MASK,  /*!< Reset caused by watchdog timeout.      */
    kASMC_ChipResetNotPORFlag       = ASMC_SRS_RES_MASK, /*!< Chip Reset caused by a source other than POR occurred. */
    kASMC_PowerOnResetFlag          = ASMC_SRS_POR_MASK, /*!< Reset caused by POR.        */
    kASMC_Core1LockupResetFlag      = ASMC_SRS_LOCKUP_MASK, /*!< Reset caused by core LOCKUP event.  */
    kASMC_SoftwareResetFlag         = ASMC_SRS_SW_MASK, /*!< Reset caused by software setting of SYSRESETREQ bit.    */
    kASMC_StopModeAcknowledgeErrorResetFlag =
        ASMC_SRS_SACKERR_MASK /*!< Reset caused by peripheral failure to acknowledge attempt to enter stop mode. */
};

/*!
 * @brief Power Modes Protection
 */
typedef enum _asmc_power_mode_protection
{
    kASMC_AllowPowerModeVlls = ASMC_PMPROT_AVLLS_MASK, /*!< Allow Very-Low-Leakage Stop Mode. */
    kASMC_AllowPowerModeLls  = ASMC_PMPROT_ALLS_MASK,  /*!< Allow Low-Leakage Stop Mode.      */
    kASMC_AllowPowerModeVlp  = ASMC_PMPROT_AVLP_MASK,  /*!< Allow Very-Low-Power Mode.        */
#if (defined(FSL_FEATURE_ASMC_HAS_HIGH_SPEED_RUN_MODE) && FSL_FEATURE_ASMC_HAS_HIGH_SPEED_RUN_MODE)
    kASMC_AllowPowerModeHsrun = ASMC_PMPROT_AHSRUN_MASK, /*!< Allow High Speed Run mode.        */
    kASMC_AllowPowerModeAll   = (ASMC_PMPROT_AVLLS_MASK | ASMC_PMPROT_ALLS_MASK | ASMC_PMPROT_AVLP_MASK |
                               ASMC_PMPROT_AHSRUN_MASK) /*!< Allow all power mode.              */
#else
    kASMC_AllowPowerModeAll =
        (ASMC_PMPROT_AVLLS_MASK | ASMC_PMPROT_ALLS_MASK | ASMC_PMPROT_AVLP_MASK) /*!< Allow all power mode. */
#endif /* FSL_FEATURE_ASMC_HAS_HIGH_SPEED_RUN_MODE */
} asmc_power_mode_protection_t;

/*!
 * @brief Power Modes in PMSTAT
 */
typedef enum _asmc_power_state
{
    kASMC_PowerStateRun  = 0x01U << 0U, /*!< 0000_0001 - Current power mode is RUN   */
    kASMC_PowerStateStop = 0x01U << 1U, /*!< 0000_0010 - Current power mode is STOP  */
    kASMC_PowerStateVlpr = 0x01U << 2U, /*!< 0000_0100 - Current power mode is VLPR  */
    kASMC_PowerStateVlpw = 0x01U << 3U, /*!< 0000_1000 - Current power mode is VLPW  */
    kASMC_PowerStateVlps = 0x01U << 4U, /*!< 0001_0000 - Current power mode is VLPS  */
    kASMC_PowerStateLls  = 0x01U << 5U, /*!< 0010_0000 - Current power mode is LLS   */
    kASMC_PowerStateVlls = 0x01U << 6U, /*!< 0100_0000 - Current power mode is VLLS  */
#if (defined(FSL_FEATURE_ASMC_HAS_HIGH_SPEED_RUN_MODE) && FSL_FEATURE_ASMC_HAS_HIGH_SPEED_RUN_MODE)
    kASMC_PowerStateHsrun = 0x01U << 7U /*!< 1000_0000 - Current power mode is HSRUN */
#endif                                  /* FSL_FEATURE_ASMC_HAS_HIGH_SPEED_RUN_MODE */
} asmc_power_state_t;

/*!
 * @brief Run mode definition
 */
typedef enum _asmc_run_mode
{
    kASMC_RunNormal = 0U, /*!< normal RUN mode.             */
    kASMC_RunVlpr   = 2U, /*!< Very-Low-Power RUN mode.     */
#if (defined(FSL_FEATURE_ASMC_HAS_HIGH_SPEED_RUN_MODE) && FSL_FEATURE_ASMC_HAS_HIGH_SPEED_RUN_MODE)
    kASMC_Hsrun = 3U /*!< High Speed Run mode (HSRUN). */
#endif               /* FSL_FEATURE_ASMC_HAS_HIGH_SPEED_RUN_MODE */
} asmc_run_mode_t;

/*!
 * @brief Stop mode definition
 */
typedef enum _asmc_stop_mode
{
    kASMC_StopNormal = 0U, /*!< Normal STOP mode.           */
    kASMC_StopVlps   = 2U, /*!< Very-Low-Power STOP mode.   */
    kASMC_StopLls    = 3U, /*!< Low-Leakage Stop mode.      */
    kASMC_StopVlls   = 4U  /*!< Very-Low-Leakage Stop mode. */
} asmc_stop_mode_t;

/*!
 * @brief Partial STOP option
 */
typedef enum _asmc_partial_stop_mode
{
    kASMC_PartialStop  = 0U, /*!< STOP - Normal Stop mode*/
    kASMC_PartialStop1 = 1U, /*!< Partial Stop with both system and bus clocks disabled*/
    kASMC_PartialStop2 = 2U, /*!< Partial Stop with system clock disabled and bus clock enabled*/
} asmc_partial_stop_option_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*! @name Auxiliary system mode controller APIs*/
/*@{*/

/*!
 * @brief Gets ASMC system reset status flags.
 *
 * This function gets all ASMC system reset status flags. The flag indicates the source
 * of the most recent MCU reset. The reset state of these bits depends on what caused
 * the MCU to reset. The flags are returned as the logical OR value of the enumerators
 * @ref _asmc_system_reset_status_flags. To check for a specific status, compare the
 * return value with enumerators in the @ref _asmc_system_reset_status_flags.
 * For example, to check whether the reset is caused by POR:
 * @code
 *     if (kASMC_PowerOnResetFlag & ASMC_GetSystemResetStatusFlags(ASMC))
 *     {
 *         ...
 *     }
 * @endcode
 *
 * @param base ASMC peripheral base address.
 * @return ASMC system reset status flags. See "_asmc_system_reset_status_flags".
 */
static inline uint32_t ASMC_GetSystemResetStatusFlags(ASMC_Type *base)
{
    return base->SRS;
}

/*!
 * @brief Configures all power mode protection settings.
 *
 * This function configures the power mode protection settings for
 * supported power modes in the specified chip family. The available power modes
 * are defined in the smc_power_mode_protection_t. This should be done at an early
 * system level initialization stage. See the reference manual for details.
 * This register can only write once after the power reset.
 *
 * The allowed modes are passed as bit map, for example, to allow LLS and VLLS,
 * use ASMC_SetPowerModeProtection(kASMC_AllowPowerModeVlls | kASMC_AllowPowerModeVlps).
 * To allow all modes, use ASMC_SetPowerModeProtection(kASMC_AllowPowerModeAll).
 *
 * @param base ASMC peripheral base address.
 * @param allowedModes Bitmap of the allowed power modes. See "asmc_power_mode_protection_t".
 */
static inline void ASMC_SetPowerModeProtection(ASMC_Type *base, uint8_t allowedModes)
{
    base->PMPROT = (uint32_t)(allowedModes);
}

/*!
 * @brief Gets the current power mode status.
 *
 * This function returns the current power mode stat. Once application
 * switches the power mode, it should always check the stat to check whether it
 * runs into the specified mode or not. An application  should  check
 * this mode before switching to a different mode. The system  requires that
 * only certain modes can switch to other specific modes. See the
 * reference manual for details and the asmc_power_state_t for information about
 * the power stat.
 *
 * @param base ASMC peripheral base address.
 * @return Current power mode status.
 */
static inline asmc_power_state_t ASMC_GetPowerModeState(ASMC_Type *base)
{
    return (asmc_power_state_t)(base->PMSTAT);
}

/*!
 * @brief Prepare to enter stop modes
 *
 * This function should be called before entering STOP/VLPS/LLS/VLLS modes.
 */
static inline void ASMC_PreEnterStopModes(void)
{
    __disable_irq();
    __ISB();
}

/*!
 * @brief Recovering after wake up from stop modes
 *
 * This function should be called after wake up from STOP/VLPS/LLS/VLLS modes.
 * It is used together with @ref ASMC_PreEnterStopModes.
 */
static inline void ASMC_PostExitStopModes(void)
{
    __enable_irq();
    __ISB();
}

/*!
 * @brief Prepare to enter wait modes
 *
 * This function should be called before entering WAIT/VLPW modes..
 */
static inline void ASMC_PreEnterWaitModes(void)
{
    __disable_irq();
    __ISB();
}

/*!
 * @brief Recovering after wake up from stop modes
 *
 * This function should be called after wake up from WAIT/VLPW modes.
 * It is used together with @ref ASMC_PreEnterWaitModes.
 */
static inline void ASMC_PostExitWaitModes(void)
{
    __enable_irq();
    __ISB();
}

/*!
 * @brief Configure the system to RUN power mode.
 *
 * @param base ASMC peripheral base address.
 * @return ASMC configuration error code.
 */
status_t ASMC_SetPowerModeRun(ASMC_Type *base);

#if (defined(FSL_FEATURE_ASMC_HAS_HIGH_SPEED_RUN_MODE) && FSL_FEATURE_ASMC_HAS_HIGH_SPEED_RUN_MODE)
/*!
 * @brief Configure the system to HSRUN power mode.
 *
 * @param base ASMC peripheral base address.
 * @return ASMC configuration error code.
 */
status_t ASMC_SetPowerModeHsrun(ASMC_Type *base);
#endif /* FSL_FEATURE_ASMC_HAS_HIGH_SPEED_RUN_MODE */

/*!
 * @brief Configure the system to WAIT power mode.
 *
 * @param base ASMC peripheral base address.
 * @return ASMC configuration error code.
 */
status_t ASMC_SetPowerModeWait(ASMC_Type *base);

/*!
 * @brief Configure the system to Stop power mode.
 *
 * @param base ASMC peripheral base address.
 * @param  option Partial Stop mode option.
 * @return ASMC configuration error code.
 */
status_t ASMC_SetPowerModeStop(ASMC_Type *base, asmc_partial_stop_option_t option);

/*!
 * @brief Configure the system to VLPR power mode.
 *
 * @param base ASMC peripheral base address.
 * @return ASMC configuration error code.
 */
status_t ASMC_SetPowerModeVlpr(ASMC_Type *base);

/*!
 * @brief Configure the system to VLPW power mode.
 *
 * @param base ASMC peripheral base address.
 * @return ASMC configuration error code.
 */
status_t ASMC_SetPowerModeVlpw(ASMC_Type *base);

/*!
 * @brief Configure the system to VLPS power mode.
 *
 * @param base ASMC peripheral base address.
 * @return ASMC configuration error code.
 */
status_t ASMC_SetPowerModeVlps(ASMC_Type *base);

/*!
 * @brief Configure the system to LLS power mode.
 *
 * @param base ASMC peripheral base address.
 * @return ASMC configuration error code.
 */
status_t ASMC_SetPowerModeLls(ASMC_Type *base);

/*!
 * @brief Configure the system to VLLS power mode.
 *
 * @param base ASMC peripheral base address.
 * @return ASMC configuration error code.
 */
status_t ASMC_SetPowerModeVlls(ASMC_Type *base);

/*@}*/

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @}*/

#endif /* _FSL_ASMC_H_ */
