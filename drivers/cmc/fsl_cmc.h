/*
 * Copyright 2019 ~ 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_CMC_H_
#define FSL_CMC_H_
#include "fsl_common.h"

/*!
 * @addtogroup cmc
 * @{
 */
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @name Driver version */
/*! @{ */
/*! @brief CMC driver version 2.3.1. */
#define FSL_CMC_DRIVER_VERSION (MAKE_VERSION(2, 3, 1))
/*! @} */

#if defined(CMC_BLR_LOCK_MASK)
#define CMC_BLR_LOCK0_MASK  CMC_BLR_LOCK_MASK
#define CMC_BLR_LOCK0_SHIFT CMC_BLR_LOCK_SHIFT
#define CMC_BLR_LOCK0       CMC_BLR_LOCK
#endif /* defined(CMC_BLR_LOCK_MASK) */

#define CMC_BLR_LOCK_FIELD_WIDTH      (3UL)
#define CMC_BLR_LOCK_IDX_MASK(index)  ((uint32_t)CMC_BLR_LOCK0_MASK << (CMC_BLR_LOCK_FIELD_WIDTH * (uint32_t)(index)))
#define CMC_BLR_LOCK_IDX_SHIFT(index) (CMC_BLR_LOCK_FIELD_WIDTH * (uint32_t)(index))
#define CMC_BLR_LOCK_IDX(index, value) \
    (((uint32_t)(((uint32_t)(value)) << CMC_BLR_LOCK_IDX_SHIFT(index))) & CMC_BLR_LOCK_IDX_MASK(index))

/*!
 * @brief CMC power mode Protection enumeration.
 */
enum _cmc_power_mode_protection
{
    kCMC_AllowSleepMode         = 0x1UL, /*!< Allow Sleep mode. */
    kCMC_AllowDeepSleepMode     = 0x2UL, /*!< Allow Deep Sleep mode. */
    kCMC_AllowPowerDownMode     = 0x4UL, /*!< Allow Power Down mode. */
    kCMC_AllowDeepPowerDownMode = 0x8UL, /*!< Allow Deep Power Down mode. */
    kCMC_AllowAllLowPowerModes  = 0xFUL, /*!< Allow all low power modes. */
};

/*!
 * @brief Wake up sources from the previous low power mode entry.
 */
enum _cmc_wakeup_sources
{
    kCMC_WakeupFromResetInterruptOrPowerDown =
        CMC_CKSTAT_WAKEUP(1U << 0U), /*!< Wakeup source is reset interrupt, or wake up from [Deep] Power Down. */
    kCMC_WakeupFromDebugReuqest = CMC_CKSTAT_WAKEUP(1U << 1U), /*!< Wakeup source is debug request. */
    kCMC_WakeupFromInterrupt    = CMC_CKSTAT_WAKEUP(1U << 2U), /*!< Wakeup source is interrupt. */
    kCMC_WakeupFromDMAWakeup    = CMC_CKSTAT_WAKEUP(1U << 3U), /*!< Wakeup source is DMA Wakeup. */
    kCMC_WakeupFromWUURequest   = CMC_CKSTAT_WAKEUP(1U << 4U), /*!< Wakeup source is WUU request. */
    kCMC_WakeupFromBusMaster    = CMC_CKSTAT_WAKEUP(1U << 5U), /*!< Wakeup source is Bus master. */
};

/*!
 * @brief System Reset Interrupt enable enumeration.
 */
enum _cmc_system_reset_interrupt_enable
{
    kCMC_PinResetInterruptEnable = CMC_SRIE_PIN_MASK, /*!< Pin Reset interrupt enable. */
    kCMC_DAPResetInterruptEnable = CMC_SRIE_DAP_MASK, /*!< DAP Reset interrupt enable. */
    kCMC_LowPowerAcknowledgeTimeoutResetInterruptEnable =
        CMC_SRIE_LPACK_MASK, /*!< Low Power Acknowledge Timeout Reset interrupt enable. */
    kCMC_Watchdog0ResetInterruptEnable = CMC_SRIE_WDOG0_MASK,  /*!< Watchdog 0 Reset interrupt enable. */
    kCMC_SoftwareResetInterruptEnable  = CMC_SRIE_SW_MASK,     /*!< Software Reset interrupt enable. */
    kCMC_LockupResetInterruptEnable    = CMC_SRIE_LOCKUP_MASK, /*!< Lockup Reset interrupt enable. */
    kCMC_Watchdog1ResetInterruptEnable = CMC_SRIE_WDOG1_MASK,  /*!< Watchdog 1 Reset interrupt enable*/
};

/*!
 * @brief CMC System Reset Interrupt Status flag.
 */
enum _cmc_system_reset_interrupt_flag
{
    kCMC_PinResetInterruptFlag = CMC_SRIF_PIN_MASK, /*!< Pin Reset interrupt flag. */
    kCMC_DAPResetInterruptFlag = CMC_SRIF_DAP_MASK, /*!< DAP Reset interrupt flag. */
    kCMC_LowPowerAcknowledgeTimeoutResetFlag =
        CMC_SRIF_LPACK_MASK,                                /*!< Low Power Acknowledge Timeout Reset interrupt flag.  */
    kCMC_Watchdog0ResetInterruptFlag = CMC_SRIF_WDOG0_MASK, /*!< Watchdog 0 Reset interrupt flag. */
    kCMC_SoftwareResetInterruptFlag  = CMC_SRIF_SW_MASK,    /*!< Software Reset interrupt flag. */
    kCMC_LockupResetInterruptFlag    = CMC_SRIF_LOCKUP_MASK, /*!< Lock up Reset interrupt flag. */
    kCMC_Watchdog1ResetInterruptFlag = CMC_SRIF_WDOG1_MASK,  /*!< Watchdog 1 Reset interrupt flag. */
};

/*!
 * @brief CMC System SRAM arrays low power mode enable enumeration.
 */
enum _cmc_system_sram_arrays
{
    kCMC_SRAMBank0 = 1U << 0U, /*!< Power off SRAM Bank0,
                               please refer to chip's RM for the corresponding SRAM array. */
    kCMC_SRAMBank1 = 1U << 1U, /*!< Power off SRAM Bank1,
                               please refer to chip's RM for the corresponding SRAM array. */
    kCMC_SRAMBank2 = 1U << 2U, /*!< Power off SRAM Bank2,
                               please refer to chip's RM for the corresponding SRAM array. */
    kCMC_SRAMBank3 = 1U << 3U, /*!< Power off SRAM Bank3,
                               please refer to chip's RM for the corresponding SRAM array. */
    kCMC_SRAMBank4 = 1U << 4U, /*!< Power off SRAM Bank4,
                               please refer to chip's RM for the corresponding SRAM array. */
    kCMC_SRAMBank5 = 1U << 5U, /*!< Power off SRAM Bank5,
                               please refer to chip's RM for the corresponding SRAM array. */
    kCMC_SRAMBank6 = 1U << 6U, /*!< Power off SRAM Bank6,
                               please refer to chip's RM for the corresponding SRAM array. */
    kCMC_SRAMBank7 = 1U << 7U, /*!< Power off SRAM Bank7,
                               please refer to chip's RM for the corresponding SRAM array. */
};

/*!
 * @brief System reset sources enumeration.
 */
enum _cmc_system_reset_sources
{
    kCMC_WakeUpReset =
        CMC_SRS_WAKEUP_MASK,               /*!< The reset caused by a wakeup from Power Down or Deep Power Down mode. */
    kCMC_PORReset     = CMC_SRS_POR_MASK,  /*!< The reset caused by power on reset detection logic. */
    kCMC_LVDReset     = CMC_SRS_LVD_MASK,  /*!< The reset caused by a Low Voltage Detect. */
    kCMC_HVDReset     = CMC_SRS_HVD_MASK,  /*!< The reset caused by a High voltage Detect. */
    kCMC_WarmReset    = CMC_SRS_WARM_MASK, /*!< The last reset source is a warm reset source. */
    kCMC_FatalReset   = CMC_SRS_FATAL_MASK,  /*!< The last reset source is a fatal reset source. */
    kCMC_PinReset     = CMC_SRS_PIN_MASK,    /*!< The reset caused by the RESET_b pin. */
    kCMC_DAPReset     = CMC_SRS_DAP_MASK,    /*!< The reset caused by a reset request from the Debug Access port. */
    kCMC_ResetTimeout = CMC_SRS_RSTACK_MASK, /*!< The reset caused by a timeout or other error condition in the system
                                                reset generation. */
    kCMC_LowPowerAcknowledgeTimeoutReset =
        CMC_SRS_LPACK_MASK,           /*!< The reset caused by a timeout in low power mode entry logic. */
    kCMC_SCGReset = CMC_SRS_SCG_MASK, /*!< The reset caused by a loss of clock or loss of lock event in the SCG. */
    kCMC_Watchdog0Reset = CMC_SRS_WDOG0_MASK,  /*!< The reset caused by a WatchDog 0 timeout. */
    kCMC_SoftwareReset  = CMC_SRS_SW_MASK,     /*!< The reset caused by a software reset request. */
    kCMC_LockUoReset    = CMC_SRS_LOCKUP_MASK, /*!< The reset caused by the ARM core indication of a LOCKUP event. */
    kCMC_Watchdog1Reset = CMC_SRS_WDOG1_MASK,  /*!< The reset caused by a WatchDog 1 timeout. */
#if (defined(FSL_FEATURE_CMC_SRS_HAS_JTAG) && FSL_FEATURE_CMC_SRS_HAS_JTAG)
    kCMC_JTAGSystemReset = CMC_SRS_JTAG_MASK, /*!< The reset caused by a JTAG system reset request. */
#endif /* (defined(FSL_FEATURE_CMC_SRS_HAS_JTAG) && FSL_FEATURE_CMC_SRS_HAS_JTAG) */
    kCMC_SecurityViolationReset = CMC_SRS_SECVIO_MASK, /*!< The reset caused by a Security Violation logic. */
};

/*!
 * @brief Indicate the core clock was gated.
 */
typedef enum _cmc_core_clock_gate_status
{
    kCMC_CoreClockNotGated = 0U, /*!< Core clock not gated. */
    kCMC_CoreClockGated    = 1U  /*!< Core clock was gated due to low power mode entry. */
} cmc_core_clock_gate_status_t;

/*!
 * @brief CMC clock mode enumeration.
 */
typedef enum _cmc_clock_mode
{
    kCMC_GateNoneClock         = 0x00U, /*!< No clock gating. */
    kCMC_GateCoreClock         = 0x01U, /*!< Gate Core clock. */
    kCMC_GateCorePlatformClock = 0x03U, /*!< Gate Core clock and platform clock. */
    kCMC_GateAllSystemClocks = 0x07U, /*!< Gate all System clocks, without getting core entering into low power mode. */
    kCMC_GateAllSystemClocksEnterLowPowerMode =
        0x0FU /*!< Gate all System clocks, with core entering into low power mode. */
} cmc_clock_mode_t;

/*!
 * @brief CMC power mode enumeration.
 */
typedef enum _cmc_low_power_mode
{
    kCMC_ActiveMode    = 0x0U, /*!< Select Active mode. */
    kCMC_SleepMode     = 0x1U, /*!< Select Sleep mode when a core executes WFI or WFE instruction. */
    kCMC_DeepSleepMode = 0x3U, /*!< Select Deep Sleep mode when a core executes WFI or WFE instruction. */
    kCMC_PowerDownMode = 0x7U, /*!< Select Power Down mode when a core executes WFI or WFE instruction. */
    kCMC_DeepPowerDown = 0xFU, /*!< Select Deep Power Down mode when a core executes WFI or WFE instruction. */
} cmc_low_power_mode_t;

#if !(defined(FSL_FEATURE_CMC_HAS_NO_SRAMCTL_REGISTER) && FSL_FEATURE_CMC_HAS_NO_SRAMCTL_REGISTER)
/*!
 * @brief CMC SRAM Voltage Select Assist enumeration.
 */
typedef enum _cmc_sram_voltage_select_assist
{
    kCMC_VoltageSelectAssist0 = CMC_SRAMCTL_VSA(0x0U), /*!< SRAM configured for 0.9V operation. */
    kCMC_VoltageSelectAssist1 = CMC_SRAMCTL_VSA(0x1U), /*!< SRAM configured for 1.0V operation. */
    kCMC_VoltageSelectAssist2 = CMC_SRAMCTL_VSA(0x2U), /*!< SRAM configured for 1.1V operation. */
    kCMC_VoltageSelectAssist3 = CMC_SRAMCTL_VSA(0x3U), /*!< SRAM configured for 1.15V operation. */
} cmc_sram_voltage_select_assist_t;
#endif /* FSL_FEATURE_CMC_HAS_NO_SRAMCTL_REGISTER */

#if !(defined(FSL_FEATURE_CMC_HAS_NO_SRAMCTL_REGISTER) && FSL_FEATURE_CMC_HAS_NO_SRAMCTL_REGISTER)
/*!
 * @brief CMC SRAM Voltage Select Margin enumeration.
 */
typedef enum _cmc_sram_voltage_select_margin
{
    kCMC_VoltageSelectMargin0 = CMC_SRAMCTL_VSM(0x0U), /*!< SRAM configured for 0.9V operation. */
    kCMC_VoltageSelectMargin1 = CMC_SRAMCTL_VSM(0x1U), /*!< SRAM configured for 1.0V operation. */
    kCMC_VoltageSelectMargin2 = CMC_SRAMCTL_VSM(0x2U), /*!< SRAM configured for 1.1V operation. */
    kCMC_VoltageSelectMargin3 = CMC_SRAMCTL_VSM(0x3U), /*!< SRAM configured for 1.15V operation. */
} cmc_sram_voltage_select_margin_t;
#endif /* FSL_FEATURE_CMC_HAS_NO_SRAMCTL_REGISTER */

/*!
 * @brief CMC reset pin configuration.
 */
typedef struct _cmc_reset_pin_config
{
    bool lowpowerFilterEnable; /*!< Low Power Filter enable. */
    bool resetFilterEnable;    /*!< Reset Filter enable.  */
    uint8_t resetFilterWidth;  /*!< Width of the Reset Filter. */
} cmc_reset_pin_config_t;

#if !(defined(FSL_FEATURE_CMC_HAS_NO_SRAMCTL_REGISTER) && FSL_FEATURE_CMC_HAS_NO_SRAMCTL_REGISTER)
/*!
 * @brief System arrays voltage configuration.
 */
typedef struct _cmc_sram_voltage_config
{
    cmc_sram_voltage_select_margin_t margin; /*!< Voltage Select Margin. */
    cmc_sram_voltage_select_assist_t assist; /*!< Voltage Select Assist. */
} cmc_sram_voltage_config;
#endif /* FSL_FEATURE_CMC_HAS_NO_SRAMCTL_REGISTER */

/*!
 * @brief power mode configuration for each power domain.
 */
typedef struct _cmc_power_domain_config
{
    cmc_clock_mode_t clock_mode;      /*!< Clock mode for each power domain. */
    cmc_low_power_mode_t main_domain; /*!< The low power mode of the MAIN power domain. */
    cmc_low_power_mode_t wake_domain; /*!< The low power mode of the WAKE power domain. */
} cmc_power_domain_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @name CLOCK mode configuration.
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
void CMC_SetClockMode(CMC_Type *base, cmc_clock_mode_t mode);

/*!
 * @brief Locks the clock mode setting.
 *
 * After invoking this function, any clock mode setting will be blocked.
 *
 * @param base CMC peripheral base address.
 */
static inline void CMC_LockClockModeSetting(CMC_Type *base)
{
    base->CKCTRL |= CMC_CKCTRL_LOCK_MASK;
}

/*! @} */

/*!
 * @name Gets/Clears the Clock Mode, the wake up source, the Reset source.
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
static inline cmc_core_clock_gate_status_t CMC_GetCoreClockGatedStatus(CMC_Type *base)
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
static inline void CMC_ClearCoreClockGatedStatus(CMC_Type *base)
{
    base->CKSTAT |= CMC_CKSTAT_VALID_MASK;
}

/*!
 * @brief Gets the Wakeup Source.
 *
 * This function gets the Wakeup sources from the previous low power mode entry.
 *
 * @param base CMC peripheral base address.
 * @return The Wakeup sources from the previous low power mode entry. See @ref _cmc_wakeup_sources for details.
 */
static inline uint8_t CMC_GetWakeupSource(CMC_Type *base)
{
    return ((uint8_t)((base->CKSTAT & CMC_CKSTAT_WAKEUP_MASK) >> CMC_CKSTAT_WAKEUP_SHIFT));
}

/*!
 * @brief Gets the Clock mode.
 *
 * This function gets the clock mode of the previous low power mode entry.
 *
 * @param base CMC peripheral base address.
 * @return The Low Power status.
 */
static inline cmc_clock_mode_t CMC_GetClockMode(CMC_Type *base)
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
 * @return The most recent system reset status. See @ref _cmc_system_reset_sources for details.
 */
static inline uint32_t CMC_GetSystemResetStatus(CMC_Type *base)
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
 * @return System reset status that have not been cleared by software. See @ref _cmc_system_reset_sources for details.
 */
static inline uint32_t CMC_GetStickySystemResetStatus(CMC_Type *base)
{
    return base->SSRS;
}

/*!
 * @brief Clears the sticky system reset status flags.
 *
 * @param base CMC peripheral base address.
 * @param mask Bitmap of the sticky system reset status to be cleared.
 */
static inline void CMC_ClearStickySystemResetStatus(CMC_Type *base, uint32_t mask)
{
    base->SSRS = mask;
}

#if (defined(FSL_FEATURE_CMC_HAS_RSTCNT_REGISTER) && FSL_FEATURE_CMC_HAS_RSTCNT_REGISTER)
/*!
 * @brief Gets the number of reset sequences completed since the last WAKE Cold Reset.
 *
 * @param base CMC peripheral base address.
 * @return The number of reset sequences.
 */
static inline uint8_t CMC_GetResetCount(CMC_Type *base)
{
    return (uint8_t)(base->RSTCNT & CMC_RSTCNT_COUNT_MASK);
}
#endif /* FSL_FEATURE_CMC_HAS_RSTCNT_REGISTER */

/*! @} */

/*!
 * @name Power mode configuration.
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
 * Sleep and DeepSleep, use CMC_SetPowerModeProtection(CMC_base, kCMC_AllowSleepMode|kCMC_AllowDeepSleepMode).
 * To allow all low power modes, use CMC_SetPowerModeProtection(CMC_base, kCMC_AllowAllLowPowerModes).
 *
 * @param base CMC peripheral base address.
 * @param allowedModes Bitmaps of the allowed power modes. See @ref _cmc_power_mode_protection for details.
 */
void CMC_SetPowerModeProtection(CMC_Type *base, uint32_t allowedModes);

/*!
 * @brief Locks the power mode protection.
 *
 * This function locks the power mode protection. After invoking this function,
 * any power mode protection setting will be ignored.
 *
 * @param base CMC peripheral base address.
 */
static inline void CMC_LockPowerModeProtectionSetting(CMC_Type *base)
{
    base->PMPROT |= CMC_PMPROT_LOCK_MASK;
}

/*!
 * @brief Config the same lowPower mode for all power domain.
 *
 * This function configures the same low power mode for MAIN power domian and WAKE power domain.
 *
 * @param base CMC peripheral base address.
 * @param lowPowerMode The desired lowPower mode. See @ref cmc_low_power_mode_t for details.
 */
static inline void CMC_SetGlobalPowerMode(CMC_Type *base, cmc_low_power_mode_t lowPowerMode)
{
    base->GPMCTRL = CMC_GPMCTRL_LPMODE((uint8_t)lowPowerMode);
}

/*!
 * @brief Configures entry into low power mode for the MAIN Power domain.
 *
 * This function configures the low power mode for the MAIN power domian,
 * when the core executes WFI/WFE instruction. The available lowPower modes
 * are defined in the @ref cmc_low_power_mode_t.
 *
 * @param base CMC peripheral base address.
 * @param lowPowerMode The desired lowPower mode. See @ref cmc_low_power_mode_t for details.
 *
 */
static inline void CMC_SetMAINPowerMode(CMC_Type *base, cmc_low_power_mode_t lowPowerMode)
{
    base->PMCTRL[0] = CMC_PMCTRL_LPMODE((uint8_t)lowPowerMode);
}

/*!
 * @brief Gets the power mode of the MAIN Power domain.
 *
 * @param base CMC peripheral base address.
 * @return The power mode of MAIN Power domain. See @ref cmc_low_power_mode_t for details.
 */
static inline cmc_low_power_mode_t CMC_GetMAINPowerMode(CMC_Type *base)
{
    return (cmc_low_power_mode_t)(uint32_t)(base->PMCTRL[0] & CMC_PMCTRL_LPMODE_MASK);
}

/*!
 * @brief Configure entry into low power mode for the WAKE Power domain.
 *
 * This function configures the low power mode for the WAKE power domian,
 * when the core executes WFI/WFE instruction. The available lowPower mode
 * are defined in the @ref cmc_low_power_mode_t.
 *
 * @note The lowPower Mode for the WAKE domain must not be configured to a
 *       lower power mode than any other power domain.
 *
 * @param base CMC peripheral base address.
 * @param lowPowerMode The desired lowPower mode. See @ref cmc_low_power_mode_t for details.
 *
 */
static inline void CMC_SetWAKEPowerMode(CMC_Type *base, cmc_low_power_mode_t lowPowerMode)
{
    base->PMCTRL[1] = CMC_PMCTRL_LPMODE((uint8_t)lowPowerMode);
}

/*!
 * @brief Gets the power mode of the WAKE Power domain.
 *
 * @param base CMC peripheral base address.
 * @return The power mode of WAKE Power domain. See @ref cmc_low_power_mode_t for details.
 */
static inline cmc_low_power_mode_t CMC_GetWAKEPowerMode(CMC_Type *base)
{
    return (cmc_low_power_mode_t)(uint32_t)(base->PMCTRL[1] & CMC_PMCTRL_LPMODE_MASK);
}

/*! @} */

/*!
 * @name Reset Pin configuration.
 * @{
 */

/*!
 * @brief Configure reset pin.
 *
 * This function configures reset pin. When enabled, the low power filter is enabled in both
 * Active and Low power modes, the reset filter is only enabled in Active mode. When both filers
 * are enabled, they operate in series.
 *
 * @param base CMC peripheral base address.
 * @param config Pointer to the reset pin config structure.
 */
void CMC_ConfigResetPin(CMC_Type *base, const cmc_reset_pin_config_t *config);

/*! @} */

/*!
 * @name System Reset Interrupts.
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
 * @param mask System reset interrupts. See @ref _cmc_system_reset_interrupt_enable for details.
 *
 */
static inline void CMC_EnableSystemResetInterrupt(CMC_Type *base, uint32_t mask)
{
    base->SRIE |= mask;
}

/*!
 * @brief Disable system reset interrupts.
 *
 * This function disables the system reset interrupts.
 *
 * @param base CMC peripheral base address.
 * @param mask System reset interrupts. See @ref _cmc_system_reset_interrupt_enable for details.
 */
static inline void CMC_DisableSystemResetInterrupt(CMC_Type *base, uint32_t mask)
{
    base->SRIE &= (uint32_t)(~mask);
}

/*!
 * @brief Gets System Reset interrupt flags.
 *
 * This function returns the System reset interrupt flags.
 *
 * @param base CMC peripheral base address.
 * @return System reset interrupt flags. See @ref _cmc_system_reset_interrupt_flag for details.
 */
static inline uint32_t CMC_GetSystemResetInterruptFlags(CMC_Type *base)
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
 * @param mask System Reset interrupt flags. See @ref _cmc_system_reset_interrupt_flag for details.
 *
 */
static inline void CMC_ClearSystemResetInterruptFlags(CMC_Type *base, uint32_t mask)
{
    base->SRIF = mask;
}

/*! @} */

/*!
 * @name Non Maskable Pin interrupt.
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
static inline void CMC_EnableNonMaskablePinInterrupt(CMC_Type *base, bool enable)
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
 * @name Boot Configuration.
 * @{
 */

/*!
 * @brief Gets the logic state of the ISPMODE_n pin.
 *
 * This function returns the logic state of the ISPMODE_n pin
 * on the last negation of RESET_b pin.
 *
 * @param base CMC peripheral base address.
 * @return The logic state of the ISPMODE_n pin on the last negation of RESET_b pin.
 */
static inline uint8_t CMC_GetISPMODEPinLogic(CMC_Type *base)
{
    return (uint8_t)((base->MR[0] & CMC_MR_ISPMODE_n_MASK) >> CMC_MR_ISPMODE_n_SHIFT);
}

/*!
 * @brief Clears ISPMODE_n pin state.
 *
 * @param base CMC peripheral base address.
 */
static inline void CMC_ClearISPMODEPinLogic(CMC_Type *base)
{
    base->MR[0] = CMC_MR_ISPMODE_n_MASK;
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
 */
static inline void CMC_ForceBootConfiguration(CMC_Type *base, bool assert)
{
    if (assert)
    {
        base->FM[0] |= CMC_FM_FORCECFG_MASK;
    }
    else
    {
        base->FM[0] &= ~CMC_FM_FORCECFG_MASK;
    }
}

/*! @} */

/*!
 * @name BootROM Status.
 * @{
 */

/*!
 * @brief Lock write operation to BootROM status register and BootROM Lock register.
 *
 * @note If locked, BootROM status register cannot be written.
 * @note Once locked, only cold reset can reset related register.
 *
 * @param base CMC peripheral base address.
 * @param index The index of BootROM status register, ranges from 0.
 */
static inline void CMC_LockWriteOperationToBootRomStatusReg(CMC_Type *base, uint8_t index)
{
    assert((uint32_t)index < CMC_BSR_COUNT);
    base->BLR = ((base->BLR & ~CMC_BLR_LOCK_IDX_MASK(index)) | CMC_BLR_LOCK_IDX(index, 0x5UL));
}

/*!
 * @brief Check if BootROM status register can be written.
 *
 * @param base CMC peripheral base address.
 * @param index The index of BootROM status register, ranges from 0.
 *
 * @retval true The selected BootRom status register is locked and cannot be written.
 * @retval false The selected BootRom Status register is unlocked and cannot be written.
 */
static inline bool CMC_CheckBootRomStatusRegWriteLocked(CMC_Type *base, uint8_t index)
{
    assert((uint32_t)index < CMC_BSR_COUNT);
    return ((base->BLR & CMC_BLR_LOCK_IDX_MASK(index)) == CMC_BLR_LOCK_IDX(index, 0x5UL));
}

/*!
 * @brief Gets the information written by the BootROM.
 *
 * @param base CMC peripheral base address.
 * @param index The index of BootROM status register, ranges from 0.
 *
 * @return The status information written by the BootROM.
 */
static inline uint32_t CMC_GetBootRomStatus(CMC_Type *base, uint8_t index)
{
    assert((uint32_t)index < CMC_BSR_COUNT);
    return base->BSR[index];
}

/*!
 * @brief Writes value to BootROM status register, in this way, BootROM status registers are used as general purpose
 * register.
 *
 * @note Value in BootROM status registers are reset in cold reset.
 *
 * @param base CMC peripheral base address.
 * @param index The index of BootROM status register, ranges from 0.
 * @param value Value to write.
 */
static inline void CMC_WriteBootRomStatusReg(CMC_Type *base, uint8_t index, uint32_t value)
{
    assert((uint32_t)index < CMC_BSR_COUNT);
    base->BSR[index] = value;
}

/*! @} */

/*!
 * @name System SRAM Configuration.
 * @{
 */

/*!
 * @brief Power off the selected system SRAM always.
 *
 * This function power off the selected system SRAM always. The SRAM arrays should
 * not be accessed while they are shut down. SRAM array contents are not retained
 * if they are powered off.
 *
 * @param base CMC peripheral base address.
 * @param mask Bitmap of the SRAM arrays to be powered off all modes.
 *             See @ref _cmc_system_sram_arrays for details.
 *             Check Reference Manual for the SRAM region and mask bit relationship.
 */
void CMC_PowerOffSRAMAllMode(CMC_Type *base, uint8_t mask);

/*!
 * @brief Power on SRAM during all mode.
 *
 * @param base CMC peripheral base address.
 * @param mask Bitmap of the SRAM arrays to be powered on all modes.
 *             See @ref _cmc_system_sram_arrays for details.
 *             Check Reference Manual for the SRAM region and mask bit relationship.
 */
static inline void CMC_PowerOnSRAMAllMode(CMC_Type *base, uint8_t mask)
{
    base->SRAMDIS[0] &= CMC_SRAMDIS_DIS((uint8_t)(~mask));
}

/*!
 * @brief Power off the selected system SRAM during low power mode only.
 *
 * This function power off the selected system SRAM only during low power mode.
 * SRAM array contents are not retained if they are power off.
 *
 * @param base CMC peripheral base address.
 * @param mask Bitmap of the SRAM arrays to be power off during low power mode only.
 *             See @ref _cmc_system_sram_arrays for details.
 *             Check Reference Manual for the SRAM region and mask bit relationship.
 */
void CMC_PowerOffSRAMLowPowerOnly(CMC_Type *base, uint8_t mask);

/*!
 * @brief Power on the selected system SRAM during low power mode only.
 *
 * This function power on the selected system SRAM. The SRAM arrray contents are
 * retained in low power modes.
 *
 * @param base CMC peripheral base address.
 * @param mask Bitmap of the SRAM arrays to be power on during low power mode only.
 *              See @ref _cmc_system_sram_arrays for details.
 *              Check Reference Manual for the SRAM region and mask bit relationship.
 */
static inline void CMC_PowerOnSRAMLowPowerOnly(CMC_Type *base, uint8_t mask)
{
    base->SRAMRET[0] &= CMC_SRAMRET_RET((uint8_t)(~mask));
}

#if !(defined(FSL_FEATURE_CMC_HAS_NO_SRAMCTL_REGISTER) && FSL_FEATURE_CMC_HAS_NO_SRAMCTL_REGISTER)
/*!
 * @brief Configures the SRAM timing for different voltage levels.
 *
 * This function configures the SRAM timing for different voltage levels,
 * when transitioning between two voltage levels, SRAM timing must be kept
 * at the lowest voltage level until the voltage is completed.
 *
 * @param base CMC peripheral base address.
 * @param config Pointer to cmc_sram_voltage_config structure.
 */
void CMC_ConfigSRAMVoltage(CMC_Type *base, const cmc_sram_voltage_config *config);
#endif /* FSL_FEATURE_CMC_HAS_NO_SRAMCTL_REGISTER */

/*! @} */

/*!
 * @name Flash Low Power Mode configuration.
 * @{
 */
/*!
 * @brief Configs the low power mode of the on-chip flash memory.
 *
 * This function configs the low power mode of the on-chip flash memory.
 *
 * @param base CMC peripheral base address.
 * @param wake true: Flash will exit low power state during the flash memory accesses.
 *             false: No effect.
 * @param doze true: Flash is disabled while core is sleeping
 *             false: No effect.
 * @param disable true: Flash memory is placed in low power state.
 *                false: No effect.
 */
void CMC_ConfigFlashMode(CMC_Type *base, bool wake, bool doze, bool disable);

/*! @} */

/*!
 * @name Debug Configuration.
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
static inline void CMC_EnableDebugOperation(CMC_Type *base, bool enable)
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

/*!
 * @name Low Power modes enter.
 * @{
 */
/*!
 * @brief Prepares to enter low power modes.
 *
 * This function should be called before entering low power modes.
 *
 */
void CMC_PreEnterLowPowerMode(void);

/*!
 * @brief Recovers after wake up from low power modes.
 *
 * This function should be called after wake up from low power modes.
 * This function should be used with CMC_PreEnterLowPowerMode()
 *
 */
void CMC_PostExitLowPowerMode(void);

/*!
 * @brief Configs the entry into the same low power mode for each power domains.
 *
 * This function provides the feature to entry into the same low power mode for each power
 * domains. Before invoking this function, please ensure the selected power mode have been allowed.
 *
 * @param base CMC peripheral base address.
 * @param lowPowerMode The low power mode to be entered. See @ref cmc_low_power_mode_t for the details.
 *
 */
void CMC_GlobalEnterLowPowerMode(CMC_Type *base, cmc_low_power_mode_t lowPowerMode);

/*!
 * @brief Configs the entry into different low power modes for each power domains.
 *
 * This function provides the feature to entry into different low power modes for
 * each power domains. Before invoking this function please ensure the selected
 * modes are allowed.
 *
 * @param base CMC peripheral base address.
 * @param config Pointer to the cmc_power_domain_config_t structure.
 */
void CMC_EnterLowPowerMode(CMC_Type *base, const cmc_power_domain_config_t *config);

/*! @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @}*/
#endif /* FSL_CMC_H_ */
