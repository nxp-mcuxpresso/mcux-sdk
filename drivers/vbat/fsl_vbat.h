/*
 * Copyright 2021 ~ 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_VBAT_H_
#define FSL_VBAT_H_

#include "fsl_common.h"

/*!
 * @addtogroup vbat
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief VBAT driver version 2.1.0. */
#define FSL_VBAT_DRIVER_VERSION (MAKE_VERSION(2, 1, 0))
/*! @} */

/*!
 * @brief The enumeration of VBAT module status.
 */
enum
{
    kStatus_VBAT_Fro16kNotEnabled =
        MAKE_STATUS(kStatusGroup_VBAT, 0), /*!< Internal 16kHz free running oscillator not enabled. */
    kStatus_VBAT_BandgapNotEnabled = MAKE_STATUS(kStatusGroup_VBAT, 1), /*!< Bandgap not enabled. */
};

/*!
 * @brief The enumeration of VBAT status flags.
 *
 * @anchor vbat_status_flag_t
 */
enum _vbat_status_flag
{
    kVBAT_StatusFlagPORDetect     = VBAT_STATUSA_POR_DET_MASK,     /*!< VBAT domain has been reset */
    kVBAT_StatusFlagWakeupPin     = VBAT_STATUSA_WAKEUP_FLAG_MASK, /*!< A falling edge is detected on the wakeup pin. */
    kVBAT_StatusFlagBandgapTimer0 = VBAT_STATUSA_TIMER0_FLAG_MASK, /*!< Bandgap Timer0 period reached. */
    kVBAT_StatusFlagBandgapTimer1 = VBAT_STATUSA_TIMER1_FLAG_MASK, /*!< Bandgap Timer1 period reached. */
    kVBAT_StatusFlagLdoReady      = VBAT_STATUSA_LDO_RDY_MASK,     /*!< LDO is enabled and ready. */
};

/*!
 * @brief The enumeration of VBAT interrupt enable.
 *
 * @anchor vbat_interrupt_enable_t
 */
enum _vbat_interrupt_enable
{
    kVBAT_InterruptEnablePORDetect = VBAT_IRQENA_POR_DET_MASK,         /*!< Enable POR detect interrupt. */
    kVBAT_InterruptEnableWakeupPin = VBAT_IRQENA_WAKEUP_FLAG_MASK,     /*!< Enable the interrupt when a falling edge is
                                                                           detected on the wakeup pin. */
    kVBAT_InterruptEnableBandgapTimer0 = VBAT_IRQENA_TIMER0_FLAG_MASK, /*!< Enable the interrupt if Bandgap
                                                                           Timer0 period reached. */
    kVBAT_InterruptEnableBandgapTimer1 = VBAT_IRQENA_TIMER1_FLAG_MASK, /*!< Enable the interrupt if Bandgap
                                                                           Timer1 period reached. */
    kVBAT_InterruptEnableLdoReady = VBAT_IRQENA_LDO_RDY_MASK,          /*!< Enable LDO ready interrupt. */

    kVBAT_AllInterruptsEnable =
        (VBAT_IRQENA_POR_DET_MASK | VBAT_IRQENA_WAKEUP_FLAG_MASK | VBAT_IRQENA_TIMER0_FLAG_MASK |
         VBAT_IRQENA_TIMER1_FLAG_MASK | VBAT_IRQENA_LDO_RDY_MASK), /*!< Enable all interrupts. */
};

/*!
 * @brief The enumeration of VBAT wakeup enable.
 *
 * @anchor vbat_wakeup_enable_t
 */
enum _vbat_wakeup_enable
{
    kVBAT_WakeupEnablePORDetect = VBAT_WAKENA_POR_DET_MASK,         /*!< Enable POR detect wakeup. */
    kVBAT_WakeupEnableWakeupPin = VBAT_WAKENA_WAKEUP_FLAG_MASK,     /*!< Enable wakeup feature when a falling edge is
                                                                        detected on the wakeup pin. */
    kVBAT_WakeupEnableBandgapTimer0 = VBAT_WAKENA_TIMER0_FLAG_MASK, /*!< Enable wakeup feature when bandgap
                                                                        timer0 period reached. */
    kVBAT_WakeupEnableBandgapTimer1 = VBAT_WAKENA_TIMER1_FLAG_MASK, /*!< Enable wakeup feature when bandgap
                                                                        timer1 period reached. */
    kVBAT_WakeupEnableLdoReady = VBAT_WAKENA_LDO_RDY_MASK,          /*!< Enable wakeup when LDO ready. */

    kVBAT_AllWakeupsEnable = (VBAT_WAKENA_POR_DET_MASK | VBAT_WAKENA_WAKEUP_FLAG_MASK | VBAT_WAKENA_TIMER0_FLAG_MASK |
                              VBAT_WAKENA_TIMER1_FLAG_MASK | VBAT_WAKENA_LDO_RDY_MASK), /*!< Enable all wakeup. */
};

/*!
 * @brief The enumeration of bandgap timer id, VBAT support two bandgap timers.
 *
 * @anchor vbat_bandgap_timer_id_t
 */
enum _vbat_bandgap_timer_id
{
    kVBAT_BandgapTimer0 = 1U << 0U, /*!< Bandgap Timer0. */
    kVBAT_BandgapTimer1 = 1U << 1U, /*!< Bandgap Timer1. */
};

/*!
 * @brief The enumeration of bandgap refresh period.
 */
typedef enum _vbat_bandgap_refresh_period
{
    kVBAT_BandgapRefresh7P8125ms = 0U, /*!< Bandgap refresh every 7.8125ms. */
    kVBAT_BandgapRefresh15P625ms = 1U, /*!< Bandgap refresh every 15.625ms. */
    kVBAT_BandgapRefresh31P25ms  = 2U, /*!< Bandgap refresh every 31.25ms. */
    kVBAT_BandgapRefresh62P5ms   = 3U, /*!< Bandgap refresh every 62.5ms. */
} vbat_bandgap_refresh_period_t;

/*!
 * @brief The enumeration of bandgap timer timeout period.
 */
typedef enum _vbat_bandgap_timer_timeout_period
{
    kVBAT_BangapTimerTimeout1s      = 0U, /*!< Bandgap timer timerout every 1s. */
    kVBAT_BangapTimerTimeout500ms   = 1U, /*!< Bandgap timer timerout every 500ms. */
    kVBAT_BangapTimerTimeout250ms   = 2U, /*!< Bandgap timer timerout every 250ms. */
    kVBAT_BangapTimerTimeout125ms   = 3U, /*!< Bandgap timer timerout every 125ms. */
    kVBAT_BangapTimerTimeout62P5ms  = 4U, /*!< Bandgap timer timerout every 62.5ms. */
    kVBAT_BangapTimerTimeout31P25ms = 5U, /*!< Bandgap timer timerout every 31.25ms. */
} vbat_bandgap_timer_timeout_period_t;

/*!
 * @brief The structure of internal 16kHz free running oscillator attributes.
 */
typedef struct _vbat_fro16k_config
{
    bool enableFRO16k;       /*!< Enable/disable internal 16kHz free running oscillator. */
    bool enableFRO16kOutput; /*!< Enable/disable FRO 16k output clock to other modules. */
} vbat_fro16k_config_t;
/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name FRO16K Control Interfaces
 * @{
 */

/*!
 * @brief Configure internal 16kHz free running oscillator, including enabel FRO16k, gate FRO16k output.
 *
 * @param base VBAT peripheral base address.
 * @param config Pointer to @ref vbat_fro16k_config_t structure.
 */
void VBAT_ConfigFRO16k(VBAT_Type *base, const vbat_fro16k_config_t *config);

/*!
 * @brief Enable/disable internal 16kHz free running oscillator.
 *
 * @param base VBAT peripheral base address.
 * @param enable Used to enable/disable 16kHz FRO.
 *          - \b true Enable internal 16kHz free running oscillator.
 *          - \b false Disable internal 16kHz free running oscillator.
 */
static inline void VBAT_EnableFRO16k(VBAT_Type *base, bool enable)
{
    if (enable)
    {
        base->FROCTLA |= VBAT_FROCTLA_FRO_EN_MASK;
    }
    else
    {
        base->FROCTLA &= ~VBAT_FROCTLA_FRO_EN_MASK;
    }
}

/*!
 * @brief Check if internal 16kHz free running oscillator is enabled.
 *
 * @param base VBAT peripheral base address.
 *
 * @retval true The internal 16kHz Free running oscillator is enabled.
 * @retval false The internal 16kHz Free running oscillator is enabled.
 */
static inline bool VBAT_CheckFRO16kEnabled(VBAT_Type *base)
{
    return (bool)((base->FROCTLA & VBAT_FROCTLA_FRO_EN_MASK) == VBAT_FROCTLA_FRO_EN_MASK);
}

/*!
 * @brief Ungate/gate FRO 16kHz output clock to other modules.
 *
 * @param base VBAT peripheral base address.
 * @param unGateFRO16k Used to gate/ungate FRO 16kHz output.
 *              - \b true FRO 16kHz output clock to other modules is enabled.
 *              - \b false FRO 16kHz output clock to other modules is disabled.
 */
static inline void VBAT_UngateFRO16k(VBAT_Type *base, bool unGateFRO16k)
{
    if (unGateFRO16k)
    {
        base->FROCLKE |= VBAT_FROCLKE_CLKE_MASK;
    }
    else
    {
        base->FROCLKE &= ~VBAT_FROCLKE_CLKE_MASK;
    }
}

/*!
 * @brief Lock settings of internal 16kHz free running oscillator, please note that if locked 16kHz FRO's settings can
 * not be updated until the next POR.
 *
 * @note Please note that the operation to ungate/gate FRO 16kHz output clock can not be locked by this function.
 *
 * @param base VBAT peripheral base address.
 */
static inline void VBAT_LockFRO16kSettings(VBAT_Type *base)
{
    base->FROLCKA |= VBAT_FROLCKA_LOCK_MASK;
}

/*! @} */

/*!
 * @name RAM_LDO Control Interfaces
 * @{
 */

/*!
 * @brief Enable/disable Bandgap.
 *
 * @note The FRO16K must be enabled before enabling the bandgap.
 * @note This setting can be locked by VBAT_LockLdoRamSettings() function.
 *
 * @param base VBAT peripheral base address.
 * @param enable Used to enable/disable bandgap.
 *      - \b true Enable the bandgap.
 *      - \b false Disable the bandgap.
 *
 * @retval kStatus_Success Success to enable/disable the bandgap.
 * @retval kStatus_VBAT_Fro16kNotEnabled Fail to enable the bandgap due to FRO16k is not enabled previously.
 */
status_t VBAT_EnableBandgap(VBAT_Type *base, bool enable);

/*!
 * @brief Check if bandgap is enabled.
 *
 * @param base VBAT peripheral base address.
 *
 * @retval true The bandgap is enabled.
 * @retval false The bandgap is disabled.
 */
static inline bool VBAT_CheckBandgapEnabled(VBAT_Type *base)
{
    return (bool)((base->LDOCTLA & VBAT_LDOCTLA_BG_EN_MASK) == VBAT_LDOCTLA_BG_EN_MASK);
}

/*!
 * @brief Enable/disable bandgap low power refresh mode.
 *
 * @note This setting can be locked by VBAT_LockLdoRamSettings() function.
 *
 * @param base VBAT peripheral base address.
 * @param enableRefreshMode Used to enable/disable bandgap low power refresh mode.
 *          - \b true Enable bandgap low power refresh mode.
 *          - \b false Disable bandgap low power refresh mode.
 */
static inline void VBAT_EnableBandgapRefreshMode(VBAT_Type *base, bool enableRefreshMode)
{
    if (enableRefreshMode)
    {
        base->LDOCTLA |= VBAT_LDOCTLA_REFRESH_EN_MASK;
    }
    else
    {
        base->LDOCTLA &= ~VBAT_LDOCTLA_REFRESH_EN_MASK;
    }
}

/*!
 * @brief Enable/disable Backup RAM Regulator(RAM_LDO).
 *
 * @note This setting can be locked by VBAT_LockLdoRamSettings() function.
 *
 * @param base VBAT peripheral base address.
 * @param enable Used to enable/disable RAM_LDO.
 *          - \b true Enable backup SRAM regulator.
 *          - \b false Disable backup SRAM regulator.
 *
 * @retval kStatusSuccess Success to enable/disable backup SRAM regulator.
 * @retval kStatus_VBAT_Fro16kNotEnabled Fail to enable backup SRAM regulator due to FRO16k is not enabled previously.
 * @retval kStatus_VBAT_BandgapNotEnabled Fail to enable backup SRAM regulator due to the bandgap is not enabled
 * previously.
 */
status_t VBAT_EnableBackupSRAMRegulator(VBAT_Type *base, bool enable);

/*!
 * @brief Lock settings of RAM_LDO, please note that if locked then RAM_LDO's settings
 * can not be updated until the next POR.
 *
 * @param base VBAT peripheral base address.
 */
static inline void VBAT_LockLdoRamSettings(VBAT_Type *base)
{
    base->LDOLCKA |= VBAT_LDOLCKA_LOCK_MASK;
}

/*!
 * @brief Switch the SRAM to be powered by VBAT in software mode.
 *
 * @note This function can be used to switch the SRAM to the VBAT retention supply at any time, but please note that the
 * SRAM must not be accessed during this time and software must manually invoke VBAT_SwitchSRAMPowerBySocSupply() before
 * accessing the SRAM again.
 *
 * @param base VBAT peripheral base address.
 *
 * @retval kStatusSuccess Success to Switch SRAM powered by VBAT.
 * @retval kStatus_VBAT_Fro16kNotEnabled Fail to switch SRAM powered by VBAT due to FRO16K not enabled previously.
 */
status_t VBAT_SwitchSRAMPowerByVBAT(VBAT_Type *base);

/*!
 * @brief Switch the RAM to be powered by Soc Supply in software mode.
 *
 * @param base VBAT peripheral base address.
 */
static inline void VBAT_SwitchSRAMPowerBySocSupply(VBAT_Type *base)
{
    base->LDORAMC &= ~VBAT_LDORAMC_SWI_MASK;
    base->LDORAMC &= ~VBAT_LDORAMC_ISO_MASK;
}

/*!
 * @brief Enable/disable SRAM array remains powered from Soc power, when LDO_RAM is disabled.
 *
 * @param base VBAT peripheral base address.
 * @param enable Used to enable/disable SRAM array power retained.
 *          - \b true SRAM array is retained when powered from VDD_CORE.
 *          - \b false SRAM array is not retained when powered from VDD_CORE.
 */
static inline void VBAT_EnableSRAMArrayRetained(VBAT_Type *base, bool enable)
{
    if (enable)
    {
        base->LDORAMC &= ~VBAT_LDORAMC_RET_MASK;
    }
    else
    {
        base->LDORAMC |= VBAT_LDORAMC_RET_MASK;
    }
}

/*!
 * @brief Enable/disable SRAM isolation.
 *
 * @param base VBAT peripheral base address.
 * @param enable Used to enable/disable SRAM violation.
 *          - \b true SRAM will be isolated.
 *          - \b false SRAM state follows the SoC power modes.
 */
static inline void VBAT_EnableSRAMIsolation(VBAT_Type *base, bool enable)
{
    if (enable)
    {
        base->LDORAMC |= VBAT_LDORAMC_ISO_MASK;
    }
    else
    {
        base->LDORAMC &= ~VBAT_LDORAMC_ISO_MASK;
    }
}

/*! @} */

/*! @name Bandgap Timer Control Interfaces
 * @{
 */

/*!
 * @brief Enable/disable Bandgap timer.
 *
 * @note The bandgap timer is available when the bandgap is enabled and are clocked by the FRO16k.
 *
 * @param base VBAT peripheral base address.
 * @param enable Used to enable/disable bandgap timer.
 * @param timerIdMask The mask of bandgap timer Id, should be the OR'ed value of @ref vbat_bandgap_timer_id_t.
 *
 * @retval kStatus_Success Success to enable/disable selected bandgap timer.
 * @retval kStatus_VBAT_Fro16kNotEnabled Fail to enable/disable selected bandgap timer due to FRO16k not enabled
 * previously.
 * @retval kStatus_VBAT_BandgapNotEnabled Fail to enable/disable selected bandgap timer due to bandgap not enabled
 * previously.
 */
status_t VBAT_EnableBandgapTimer(VBAT_Type *base, bool enable, uint8_t timerIdMask);

/*!
 * @brief Set bandgap timer timeout value.
 *
 * @param base VBAT peripheral base address.
 * @param timeoutPeriod Bandgap timer timeout value, please refer to @ref vbat_bandgap_timer_timeout_period_t.
 * @param timerIdMask The mask of bandgap timer Id, should be the OR'ed value of @ref vbat_bandgap_timer_id_t.
 */
void VBAT_SetBandgapTimerTimeoutValue(VBAT_Type *base,
                                      vbat_bandgap_timer_timeout_period_t timeoutPeriod,
                                      uint8_t timerIdMask);

/*! @} */

/*! @name Status, Interrupt, Wakeup Control Interfaces
 * @{
 */

/*!
 * @brief Get VBAT status flags
 *
 * @param base VBAT peripheral base address.
 * @return The asserted status flags, should be the OR'ed value of @ref vbat_status_flag_t.
 */
static inline uint32_t VBAT_GetStatusFlags(VBAT_Type *base)
{
    return (uint32_t)(base->STATUSA);
}

/*!
 * @brief Clear VBAT status flags.
 *
 * @param base VBAT peripheral base address.
 * @param mask The mask of status flags to be cleared, should be the OR'ed value of @ref vbat_status_flag_t except
 *              @ref kVBAT_StatusFlagLdoReady.
 */
static inline void VBAT_ClearStatusFlags(VBAT_Type *base, uint32_t mask)
{
    base->STATUSA = mask;
}

/*!
 * @brief Enable interrupts for the VBAT module, such as POR detect interrupt, Wakeup Pin interrupt and so on.
 *
 * @param base VBAT peripheral base address.
 * @param mask The mask of interrupts to be enabled, should be the OR'ed value of @ref vbat_interrupt_enable_t.
 */
static inline void VBAT_EnableInterrupts(VBAT_Type *base, uint32_t mask)
{
    base->IRQENA |= mask;
}

/*!
 * @brief Disable interrupts for the VBAT module, such as POR detect interrupt, wakeup pin interrupt and so on.
 *
 * @param base VBAT peripheral base address.
 * @param mask The mask of interrupts to be disabled, should be the OR'ed value of @ref vbat_interrupt_enable_t.
 */
static inline void VBAT_DisableInterrupts(VBAT_Type *base, uint32_t mask)
{
    base->IRQENA &= ~mask;
}

/*!
 * @brief Enable wakeup for the VBAT module, such as POR detect wakeup, wakeup pin wakeup and so on.
 *
 * @param base VBAT peripheral base address.
 * @param mask The mask of enumerators in @ref vbat_wakeup_enable_t.
 */
static inline void VBAT_EnableWakeup(VBAT_Type *base, uint32_t mask)
{
    base->WAKENA |= mask;
}

/*!
 * @brief Disable wakeup for VBAT module, such as POR detect wakeup, wakeup pin wakeup and so on.
 *
 * @param base VBAT peripheral base address.
 * @param mask The mask of enumerators in @ref vbat_wakeup_enable_t.
 */
static inline void VBAT_DisableWakeup(VBAT_Type *base, uint32_t mask)
{
    base->WAKENA &= ~mask;
}

/*!
 * @brief Lock VBAT interrupt and wakeup settings, please note that if locked the interrupt and wakeup settings can not
 * be updated until the next POR.
 *
 * @param base VBAT peripheral base address.
 */
static inline void VBAT_LockInterruptWakeupSettings(VBAT_Type *base)
{
    base->LOCKA |= VBAT_LOCKA_LOCK_MASK;
}

/*! @} */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* FSL_VBAT_H__ */
