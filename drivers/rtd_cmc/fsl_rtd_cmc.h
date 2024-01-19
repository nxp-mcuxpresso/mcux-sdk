/*
 * Copyright 2021-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_RTD_CMC_H_
#define FSL_RTD_CMC_H_

#include "fsl_common.h"

/*!
 * @addtogroup rtd_cmc
 * @{
 */
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @name Driver version */
/*! @{ */
/*! @brief RTD_CMC driver version 2.0.2. */
#define FSL_RTD_CMC_DRIVER_VERSION (MAKE_VERSION(2, 0, 2))
/*! @} */

/*!
 * @brief RTD_CMC power mode Protection enumeration.
 */
enum _rtd_cmc_power_mode_protection
{
    kRTDCMC_AllowSleepMode         = CMC_RTD_PMPROT_AS_MASK,   /*!< Allow Sleep mode. */
    kRTDCMC_AllowDeepSleepMode     = CMC_RTD_PMPROT_ADS_MASK,  /*!< Allow Deep Sleep mode. */
    kRTDCMC_AllowPowerDownMode     = CMC_RTD_PMPROT_APD_MASK,  /*!< Allow Power Down mode. */
    kRTDCMC_AllowDeepPowerDownMode = CMC_RTD_PMPROT_ADPD_MASK, /*!< Allow Deep Power Down mode. */
    kRTDCMC_AllowHoldMode          = CMC_RTD_PMPROT_AHLD_MASK, /*!< Allow Hold mode. */
    kRTDCMC_AllowAllLowPowerModes =
        (kRTDCMC_AllowSleepMode | kRTDCMC_AllowDeepSleepMode | kRTDCMC_AllowPowerDownMode |
         kRTDCMC_AllowDeepPowerDownMode | kRTDCMC_AllowHoldMode), /*!< Allow all low power modes. */
};

/*!
 * @brief Wake up sources from the previous low power mode entry.
 */
enum _rtd_cmc_wakeup_sources
{
    kRTDCMC_WakeupFromResetInterruptOrPowerDown =
        CMC_CKSTAT_WAKEUP(1U << 0U), /*!< Wakeup source is reset interrupt, or wake up from [Deep] Power Down. */
    kRTDCMC_WakeupFromDebugReuqest = CMC_CKSTAT_WAKEUP(1U << 1U), /*!< Wakeup source is debug request. */
    kRTDCMC_WakeupFromInterrupt    = CMC_CKSTAT_WAKEUP(1U << 2U), /*!< Wakeup source is interrupt. */
    kRTDCMC_WakeupFromDMAWakeup    = CMC_CKSTAT_WAKEUP(1U << 3U), /*!< Wakeup source is DMA Wakeup. */
    kRTDCMC_WakeupFromWUURequest   = CMC_CKSTAT_WAKEUP(1U << 4U), /*!< Wakeup source is WUU request. */
};

/*!
 * @brief System Reset Interrupt enable enumeration.
 */
enum _rtd_cmc_system_reset_interrupt_enable
{
    kRTDCMC_InSystemProgrammingAccessPortResetInterruptEnable =
        CMC_SRIE_ISP_AP_MASK,                                                     /*!< ISP_AP Reset interrupt enable. */
    kRTDCMC_LowPowerAcknowledgeTimeoutResetInterruptEnable = CMC_SRIE_LPACK_MASK, /*!< Low Power Acknowledge Timeout
                                                                                    Reset interrupt enable. */
    kRTDCMC_Watchdog0ResetInterruptEnable         = CMC_SRIE_WDOG0_MASK,  /*!< Watchdog 0 Reset interrupt enable. */
    kRTDCMC_SoftwareResetInterruptEnable          = CMC_SRIE_SW_MASK,     /*!< Software Reset interrupt enable. */
    kRTDCMC_LockupResetInterruptEnable            = CMC_SRIE_LOCKUP_MASK, /*!< Lockup Reset interrupt enable. */
    kRTDCMC_AppDomainMuSystemResetInterruptEnable = CMC_SRIE_AD_MU_MASK,  /* Application Domain MU System Reset
                                                                             interrupt enable. */
    kRTDCMC_Watchdog1ResetInterruptEnable = CMC_SRIE_WDOG_S_RTD_MASK,     /*!< Watchdog 1 Reset interrupt enable. */
    kRTDCMC_Watchdog5ResetInterruptEnable = CMC_SRIE_WDOG_HIFI4_MASK,     /*!< Watchdog 5 Reset interrupt enable. */
    kRTDCMC_Watchdog2ResetInterruptEnable = CMC_SRIE_WDOG_FUSION_MASK,    /*!< Watchdog 2 Reset interrupt enable. */
};

/*!
 * @brief Power switch domain out of reset interrupt enable enumeration.
 */
enum _rtd_cmc_power_switch_domain_out_of_reset_interrupt_enable
{
    kRTDCMC_FusionPSDomainOutOfResetInterruptEnable = CMC_RTD_PSDORIE_FUSION_MASK, /*!< Fusion power switch domain out
                                                                                        of reset interrupt enable. */
    kRTDCMC_FusionAlwaysOnPSDomainOutOfResetInterruptEnable = CMC_RTD_PSDORIE_FUSION_AO_MASK, /*!< Fusion always on
                                                                                                power switch domain out
                                                                                                of reset interrupt
                                                                                                enable. */
};

/*!
 * @brief CMC System Reset Interrupt Status flag.
 */
enum _rtd_cmc_system_reset_interrupt_flag
{
    kRTDCMC_InSystemProgrammingAccessPortResetDAPResetInterruptFlag =
        CMC_SRIF_ISP_AP_MASK, /*!< DAP Reset interrupt flag. */
    kRTDCMC_LowPowerAcknowledgeTimeoutResetFlag =
        CMC_SRIF_LPACK_MASK, /*!< Low Power Acknowledge Timeout Reset interrupt flag.  */
    kRTDCMC_Watchdog0ResetInterruptFlag         = CMC_SRIF_WDOG0_MASK,     /*!< Watchdog 0 Reset interrupt flag. */
    kRTDCMC_SoftwareResetInterruptFlag          = CMC_SRIF_SW_MASK,        /*!< Software Reset interrupt flag. */
    kRTDCMC_LockupResetInterruptFlag            = CMC_SRIF_LOCKUP_MASK,    /*!< Lock up Reset interrupt flag. */
    kRTDCMC_AppDomainMuSystemResetInterruptFlag = CMC_SRIF_AD_MU_MASK,     /*!< Application Domain MU System Reset
                                                                                interrupt flag. */
    kRTDCMC_WatchdogSResetInterruptFlag       = CMC_SRIF_WDOG_S_RTD_MASK,  /*!< Watchdog S Reset interrupt flag. */
    kRTDCMC_WatchdogHifi4ResetInterruptFlag   = CMC_SRIF_WDOG_HIFI4_MASK,  /*!< Watchdog Hifi4 Reset interrupt flag. */
    kRTDCMC_WatchdogFunsionResetInterruptFlag = CMC_SRIF_WDOG_FUSION_MASK, /*!< Watchdog Fusion Reset interrupt flag. */
};

/*!
 * @brief Power switch domain out of reset interrupt flags enumeration.
 */
enum _rtd_cmc_power_switch_domain_out_of_reset_interrupt_flag
{
    kRTDCMC_FusionPSDomainOutOfResetInterruptFlag = CMC_RTD_PSDORF_FUSION_MASK, /*!< Fusion power switch domain out of
                                                                                reset interrupt flag. */
    kRTDCMC_FusionAlwaysOnPSDomainOutOfResetInterruptFlag = CMC_RTD_PSDORF_FUSION_AO_MASK, /*!< Fusion always on power
                                                                                    switch domain out of reset
                                                                                    interrupt flag. */
};

/*!
 * @brief System reset sources enumeration.
 */
enum _rtd_cmc_system_reset_sources
{
    kRTDCMC_WakeUpReset =
        CMC_SRS_WAKEUP_MASK, /*!< The reset caused by a wakeup from Power Down or Deep Power Down mode. */
    kRTDCMC_PORReset    = CMC_SRS_POR_MASK,     /*!< The reset caused by power on reset detection logic. */
    kRTDCMC_HLVDReset   = CMC_SRS_HLVD_MASK,    /*!< The reset caused by a High or Low Voltage Detect. */
    kRTDCMC_WarmReset   = CMC_SRS_WARM_MASK,    /*!< The last reset source is a warm reset source. */
    kRTDCMC_FatalReset  = CMC_SRS_FATAL_MASK,   /*!< The last reset source is a fatal reset source. */
    kRTDCMC_PinReset    = CMC_SRS_PIN_MASK,     /*!< The reset caused by the RESET_b pin. */
    kRTDCMC_ISP_APReset = CMC_SRS_ISP_AP_MASK,  /*!< The reset caused by a reset request from
                                                  in-system programming access port. */
    kRTDCMC_ResetTimeout = CMC_SRS_RSTACK_MASK, /*!< The reset caused by a timeout or other error condition in the
                                                system reset generation. */
    kRTDCMC_LowPowerAcknowledgeTimeoutReset =
        CMC_SRS_LPACK_MASK, /*!< The reset caused by a timeout in low power mode entry logic. */
    kRTDCMC_RtdCgcLocReset = CMC_SRS_RTD_CGC_LOC_MASK, /*!< The reset caused by real time domain clock generation and
                                                        control loss-of-clock reset. */
    kRTDCMC_Watchdog0Reset = CMC_SRS_WDOG0_MASK,       /*!< The reset caused by a WatchDog 0 timeout. */
    kRTDCMC_SoftwareReset  = CMC_SRS_SW_MASK,          /*!< The reset caused by a software reset request. */
    kRTDCMC_LockUpReset    = CMC_SRS_LOCKUP_MASK, /*!< The reset caused by the ARM core indication of a LOCKUP event. */
    kRTDCMC_AdMuReset      = CMC_SRS_AD_MU_MASK,  /*!< The reset caused by application domain MU system. */
    kRTDCMC_RtdCgcLosReset = CMC_SRS_RTD_CGC_LOS_MASK,         /*!< The reset caused by RTD clock generation
                                                               and control loss of sync. */
    kRTDCMC_LpavCgcLosReset = CMC_SRS_LPAV_CGC_LOS_MASK,       /*!< The reset caused by LPAV clock generation
                                                              and control loss of sync. */
    kRTDCMC_uPowerReset            = CMC_SRS_UPOWER_MASK,      /*!< The reset caused by uPOWER WDOG System. */
    kRTDCMC_VbatReset              = CMC_SRS_VBAT_MASK,        /*!< The reset caused by VBAT system reset. */
    kRTDCMC_WatchdogSReset         = CMC_SRS_WDOG_S_RTD_MASK,  /*!< The reset caused by a WatchDog_S RTD timeout. */
    kRTDCMC_WatchdogHifi4Reset     = CMC_SRS_WDOG_HIFI4_MASK,  /*!< The reset caused from the WDOG_HIFI4 timeout. */
    kRTDCMC_WatchdogFusionReset    = CMC_SRS_WDOG_FUSION_MASK, /*!< The reset caused from the WDOG_FUSION timeout. */
    kRTDCMC_JTAGSystemReset        = CMC_SRS_JTAG_MASK,        /*!< The reset caused by a JTAG system reset request. */
    kRTDCMC_SentinelLifeCycleReset = CMC_SRS_SLB_MASK,         /*!< The reset caused by sentinel detecting
                                                               an unexpected lifecycle coding. */
    kRTDCMC_SentinelReset           = CMC_SRS_SRR_MASK,        /*!< The reset caused by sentinel reset request. */
    kRTDCMC_SentinelSystemFailReset = CMC_SRS_SSF_MASK, /*!< The reset caused by a sentinel system fail condition. */
};

/*!
 * @brief Indicate the core clock was gated.
 */
typedef enum _rtd_cmc_core_clock_gate_status
{
    kRTDCMC_CoreClockNotGated = 0U, /*!< Core clock not gated. */
    kRTDCMC_CoreClockGated    = 1U  /*!< Core clock was gated due to low power mode entry. */
} cmc_core_clock_gate_status_t;

/*!
 * @brief CMC clock mode enumeration.
 */
typedef enum _rtd_cmc_clock_mode
{
    kRTDCMC_GateNoneClock         = 0x00U, /*!< No clock gating. */
    kRTDCMC_GateCoreClock         = 0x01U, /*!< Gate Core clock. */
    kRTDCMC_GateCorePlatformClock = 0x03U, /*!< Gate Core clock and platform clock. */
    kRTDCMC_GateAllSystemClocks =
        0x07U, /*!< Gate all System clocks, without getting core entering into low power mode. */
} cmc_clock_mode_t;

/*!
 * @brief CMC power mode enumeration.
 */
typedef enum _rtd_cmc_low_power_mode
{
    kRTDCMC_ActiveMode    = 0x0U,  /*!< Select Active mode. */
    kRTDCMC_SleepMode     = 0x1U,  /*!< Select Sleep mode when a core executes WFI or WFE instruction. */
    kRTDCMC_DeepSleepMode = 0x3U,  /*!< Select Deep Sleep mode when a core executes WFI or WFE instruction. */
    kRTDCMC_PowerDownMode = 0x7U,  /*!< Select Power Down mode when a core executes WFI or WFE instruction. */
    kRTDCMC_DeepPowerDown = 0xFU,  /*!< Select Deep Power Down mode when a core executes WFI or WFE instruction. */
    kRTDCMC_HoldMode      = 0x1FU, /*!< Select Hold mode */
} cmc_low_power_mode_t;

typedef enum _rtd_cmc_power_switch_domain_name
{
    kRTDCMC_FusionAlwaysOnPowerSwitchDomain = 0x1U, /*!< Fusion always on power switch domain. */
    kRTDCMC_FusionPowerSwitchDomain         = 0x2U, /*!< Fusion power switch domain. */
    kRTDCMC_RealtimePowerDomain             = 0x4U, /*!< Realtime power switch domain */
} rtd_cmc_power_switch_domain_name_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*!
 * @name CLOCK Mode Configurations
 * @{
 */

/*!
 * @brief Sets clock mode.
 *
 * This function configs the amount of clock gating when the core asserts
 * Sleeping due to WFI, WFE or SLEEPONEXIT.
 *
 * @param base CMC peripheral base address.
 * @param mode System clock mode.
 */
void RTDCMC_SetClockMode(CMC_Type *base, cmc_clock_mode_t mode);

/*!
 * @brief Locks the clock mode setting.
 *
 * After invoking this function, any clock mode setting will be blocked.
 *
 * @param base CMC peripheral base address.
 */
static inline void RTDCMC_LockClockModeSetting(CMC_Type *base)
{
    base->CKCTRL |= CMC_CKCTRL_LOCK_MASK;
}

/*! @} */

/*!
 * @name Gets/Clears the Clock Mode, the wake up source, the Reset source
 * @{
 */

/*!
 * @brief Gets the core clock gated status.
 *
 * This function get the status to indicate whether the core clock is gated.
 * The core clock gated status can be cleared by software.
 *
 * @param base CMC peripheral base address.
 * @return The status to indicate whether the core clock is gated.
 */
static inline cmc_core_clock_gate_status_t RTDCMC_GetCoreClockGatedStatus(CMC_Type *base)
{
    return (cmc_core_clock_gate_status_t)(uint32_t)((base->CKSTAT & CMC_CKSTAT_VALID_MASK) >> CMC_CKSTAT_VALID_SHIFT);
}

/*!
 * @brief Clears the core clock gated status.
 *
 * This function clear clock status flag by software.
 *
 * @param base CMC peripheral base address.
 */
static inline void RTDCMC_ClearCoreClockGatedStatus(CMC_Type *base)
{
    base->CKSTAT |= CMC_CKSTAT_VALID_MASK;
}

/*!
 * @brief Gets the Wakeup Source.
 *
 * This function gets the Wakeup sources from the previous low power mode entry.
 *
 * @param base CMC peripheral base address.
 * @return The Wakeup sources from the previous low power mode entry. See @ref _rtd_cmc_wakeup_sources for details.
 */
static inline uint8_t RTDCMC_GetWakeupSource(CMC_Type *base)
{
    return (uint8_t)((base->CKSTAT & CMC_CKSTAT_WAKEUP_MASK) >> CMC_CKSTAT_WAKEUP_SHIFT);
}

/*!
 * @brief Gets the Clock mode.
 *
 * This function gets the clock mode of the previous low power mode entry.
 *
 * @param base CMC peripheral base address.
 * @return The Low Power status.
 */
static inline cmc_clock_mode_t RTDCMC_GetClockMode(CMC_Type *base)
{
    return (cmc_clock_mode_t)(uint32_t)((base->CKSTAT & CMC_CKSTAT_CKMODE_MASK) >> CMC_CKSTAT_CKMODE_SHIFT);
}

/*!
 * @brief Gets the System reset status.
 *
 * This function returns the system reset status. Those status
 * updates on every MAIN Warm Reset to indicate the type/source
 * of the most recent reset.
 *
 * @param base CMC peripheral base address.
 * @return The most recent system reset status. See @ref _rtd_cmc_system_reset_sources for details.
 */
static inline uint32_t RTDCMC_GetSystemResetStatus(CMC_Type *base)
{
    return base->SRS;
}

/*!
 * @brief Gets the sticky system reset status since the last WAKE Cold Reset.
 *
 * This function gets all source of system reset that have generated a
 * system reset since the last WAKE Cold Reset, and that have not been
 * cleared by software.
 *
 * @param base CMC peripheral base address.
 * @return System reset status that have not been cleared by software. See @ref _rtd_cmc_system_reset_sources for
 * details.
 */
static inline uint32_t RTDCMC_GetStickySystemResetStatus(CMC_Type *base)
{
    return base->SSRS;
}

/*!
 * @brief Clears the sticky system reset status flags.
 *
 * @param base CMC peripheral base address.
 * @param mask Bitmap of the sticky system reset status to be cleared.
 */
static inline void RTDCMC_ClearStickySystemResetStatus(CMC_Type *base, uint32_t mask)
{
    base->SSRS = mask;
}

/*! @} */

/*!
 * @name Power Mode Configuration
 * @{
 */

/*!
 * @brief Configures all power mode protection settings.
 *
 * This function configures the power mode protection settings for
 * supported power modes. This should be done before set the lowPower mode
 * for each power doamin.
 *
 * The allowed lowpower modes are passed as bit map. For example, to allow
 * Sleep and DeepSleep, use CMC_SetPowerModeProtection(CMC_base, kRTDCMC_AllowSleepMode|kRTDCMC_AllowDeepSleepMode).
 * To allow all low power modes, use CMC_SetPowerModeProtection(CMC_base, kRTDCMC_AllowAllLowPowerModes).
 *
 * @param base CMC peripheral base address.
 * @param allowedModes Bitmaps of the allowed power modes. See @ref _rtd_cmc_power_mode_protection for details.
 */
void RTDCMC_SetPowerModeProtection(CMC_Type *base, uint8_t allowedModes);

/*!
 * @brief Locks the power mode protection.
 *
 * This function locks the power mode protection. After invoking this function,
 * any power mode protection setting will be ignored.
 *
 * @param base CMC peripheral base address.
 */
static inline void RTDCMC_LockPowerModeProtectionSetting(CMC_Type *base)
{
    base->RTD_PMPROT |= CMC_RTD_PMPROT_AS_MASK | CMC_RTD_PMPROT_ADS_MASK | CMC_RTD_PMPROT_APD_MASK |
                        CMC_RTD_PMPROT_ADPD_MASK | CMC_RTD_PMPROT_AHLD_MASK;
}

/*!
 * @brief Enter into the selected low power mode, please make sure the selected power mode has been enabled in the
 * protection level.
 *
 * @param base CMC peripheral base address.
 * @param lowPowerMode The desired lowPower mode. See @ref cmc_low_power_mode_t for details.
 */
void RTDCMC_EnterLowPowerMode(CMC_Type *base, cmc_low_power_mode_t lowPowerMode);

/*! @} */

/*!
 * @name System Reset Interrupts
 * @{
 */

/*!
 * @brief Enable system reset interrupts.
 *
 * This function enables the system reset interrupts. The assertion of
 * non-fatal warm reset can be delayed for 258 cycles of the 32K_CLK clock
 * while an enabled interrupt is generated. Then Software can perform a graceful
 * shutdown or abort the non-fatal warm reset provided the pending reset source is cleared
 * by resetting the reset source and then clearing the pending flag.
 *
 * @param base CMC peripheral base address.
 * @param mask System reset interrupts. See @ref _rtd_cmc_system_reset_interrupt_enable for details.
 *
 */
static inline void RTDCMC_EnableSystemResetInterrupt(CMC_Type *base, uint32_t mask)
{
    base->SRIE |= mask;
}

/*!
 * @brief Disable system reset interrupts.
 *
 * This function disables the system reset interrupts.
 *
 * @param base CMC peripheral base address.
 * @param mask System reset interrupts. See @ref _rtd_cmc_system_reset_interrupt_enable for details.
 */
static inline void RTDCMC_DisableSystemResetInterrupt(CMC_Type *base, uint32_t mask)
{
    base->SRIE &= (uint32_t)(~mask);
}

/*!
 * @brief Gets System Reset interrupt flags.
 *
 * This function returns the System reset interrupt flags.
 *
 * @param base CMC peripheral base address.
 * @return System reset interrupt flags. See @ref _rtd_cmc_system_reset_interrupt_flag for details.
 */
static inline uint32_t RTDCMC_GetSystemResetInterruptFlags(CMC_Type *base)
{
    return base->SRIF;
}

/*!
 * @brief Clears System Reset interrupt flags.
 *
 * This function clears system reset interrupt flags. The pending reset source
 * can be cleared by resetting the source of the reset and then clearing the pending
 * flags.
 *
 * @param base CMC peripheral base address.
 * @param mask System Reset interrupt flags. See @ref _rtd_cmc_system_reset_interrupt_flag for details.
 *
 */
static inline void RTDCMC_ClearSystemResetInterruptFlags(CMC_Type *base, uint32_t mask)
{
    base->SRIF = mask;
}

/*! @} */

/*!
 * @name Power Switch Domain Interrupt
 * @{
 */

/*!
 * @brief Enable power switch domain out of reset interrupts.
 *
 * @param base CMC peripheral base address.
 * @param mask Power switch domain out of reset interrupt mask,
 *             should be the OR'ed value of @ref _rtd_cmc_power_switch_domain_out_of_reset_interrupt_enable.
 */
static inline void RTDCMC_EnablePowerSwitchDomainOutOfResetInterrupt(CMC_Type *base, uint32_t mask)
{
    base->RTD_PSDORIE |= mask;
}

/*!
 * @brief Disable power switch domain out of reset interrupts.
 *
 * @param base CMC peripheral base address.
 * @param mask Power switch domain out of reset interrupt mask,
 *             should be the OR'ed value of @ref _rtd_cmc_power_switch_domain_out_of_reset_interrupt_enable.
 */

static inline void RTDCMC_DisablePowerSwitchDomainOutOfResetInterrupt(CMC_Type *base, uint32_t mask)
{
    base->RTD_PSDORIE &= ~mask;
}

/*!
 * @brief Get power switch domain out of reset interrupt flags.
 *
 * @param base CMC peripheral base address.
 * @return Power switch domain out of reset interrupt flags,
 *          shall be the OR'ed value of  @ref _rtd_cmc_power_switch_domain_out_of_reset_interrupt_flag.
 */
static inline uint32_t RTDCMC_GetPowerSwitchDomainOutOfResetInterruptFlags(CMC_Type *base)
{
    return base->RTD_PSDORF;
}

/*!
 * @brief Clear power switch domain out of reset interrupt flags.
 *
 * @param base CMC peripheral base address.
 * @param mask The mask of power switch domain out of reset interrupt flags to clear.
 */
static inline void RTDCMC_ClearPowerSwitchDomainOutOfResetInterruptFlags(CMC_Type *base, uint32_t mask)
{
    base->RTD_PSDORF = mask;
}

/*! @} */

/*!
 * @name Real Time Domain Power Switch Domain Status API
 * @{
 */

/*!
 * @brief Check the status of selected power switch domain.
 *
 * @param base CMC peripheral base address.
 * @param domainName The selected domain name, please refer to @ref rtd_cmc_power_switch_domain_name_t.
 * @retval True The power switch domain is open.
 * @retval False The power switch domain is closed.
 */
static inline bool RTDCMC_CheckRealTimeDomainPowerSwitchDomainStatus(CMC_Type *base,
                                                                     rtd_cmc_power_switch_domain_name_t domainName)
{
    return ((base->RTD_PSDS & (uint32_t)domainName) == 0UL);
}

/*! @} */

/*!
 * @name Boot Configuration
 * @{
 */

/*!
 * @brief Gets the logic state of the BOOT_CONFIGn pin.
 *
 * This function returns the logic state of the BOOT_CONFIGn pin
 * on the last negation of RESET_b pin.
 *
 * @param base CMC peripheral base address.
 * @return The logic state of the BOOT_CONFIGn pin on the last negation of RESET_b pin.
 */
static inline uint8_t RTDCMC_GetBootConfigPinLogic(CMC_Type *base)
{
    return (uint8_t)((base->MR[0] & CMC_MR_BOOTCFG_MASK) >> CMC_MR_BOOTCFG_SHIFT);
}

/*!
 * @brief Clears Boot_CONFIG pin state.
 *
 * @param base CMC peripheral base address.
 */
static inline void RTDCMC_ClearBootConfig(CMC_Type *base)
{
    base->MR[0] = CMC_MR_BOOTCFG_MASK;
}

/*!
 * @brief Set the logic state of the BOOT_CONFIGn pin.
 *
 * This function force the logic state of the Boot_Confign pin to assert
 * on next system reset.
 *
 * @param base CMC peripheral base address.
 * @param assert Assert the corresponding pin or not.
 *               true   -   Assert corresponding pin on next system reset.
 *               false  -   No effect.
 * @param bitsMask The mask of the corresponding bits in the Mode register to assert or not on the next system reset.
 */
static inline void RTDCMC_ForceBootConfiguration(CMC_Type *base, bool assert, uint32_t bitsMask)
{
    if (assert)
    {
        base->FM[0] |= CMC_FM_FORCECFG(bitsMask);
    }
    else
    {
        base->FM[0] &= ~CMC_FM_FORCECFG(bitsMask);
    }
}

/*! @} */

/*!
 * @name Non Maskable Pin interrupt
 * @{
 */

/*!
 * @brief Enable/Disable Non maskable Pin interrupt.
 *
 * @param base CMC peripheral base address.
 * @param enable Enable or disable Non maskable pin interrupt.
 *          true    -   enable Non-maskable pin interrupt.
 *          false   -   disable Non-maskable pin interupt.
 */
static inline void RTDCMC_EnableNonMaskablePinInterrupt(CMC_Type *base, bool enable)
{
    if (enable)
    {
        base->CORECTL |= CMC_CORECTL_NPIE_MASK;
    }
    else
    {
        base->CORECTL &= ~CMC_CORECTL_NPIE_MASK;
    }
}

/*! @} */

/*!
 * @name Debug Configuration
 * @{
 */

/*!
 * @brief Enables/Disables debug Operation when the core sleep.
 *
 * This function configs what happens to debug when core sleeps.
 *
 * @param base CMC peripheral base address.
 * @param enable Enable or disable Debug when Core is sleeping.
 *          true    -   Debug remains enabled when the core is sleeping.
 *          false   -   Debug is disabled when the core is sleeping.
 */
static inline void RTDCMC_EnableDebugOperation(CMC_Type *base, bool enable)
{
    if (enable)
    {
        base->DBGCTL &= ~CMC_DBGCTL_SOD_MASK;
    }
    else
    {
        base->DBGCTL |= CMC_DBGCTL_SOD_MASK;
    }
}

/*! @} */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*! @}*/
#endif /* FSL_RTD_CMC_H_ */
