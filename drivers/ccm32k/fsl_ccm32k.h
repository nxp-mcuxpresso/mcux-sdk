/*
 * Copyright 2020-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_CCM32K_H_
#define FSL_CCM32K_H_

#include "fsl_common.h"

/*!
 * @addtogroup ccm32k
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief CCM32K driver version 2.2.0. */
#define FSL_CCM32K_DRIVER_VERSION (MAKE_VERSION(2, 2, 0))
/*! @} */

#define CCM32K_OSC32K_CTRL_OSC_MODE_MASK  (0x3U)
#define CCM32K_OSC32K_CTRL_OSC_MODE_SHIFT (0U)
#define CCM32K_OSC32K_CTRL_OSC_MODE(x) \
    (((uint32_t)(((uint32_t)(x)) << CCM32K_OSC32K_CTRL_OSC_MODE_SHIFT)) & CCM32K_OSC32K_CTRL_OSC_MODE_MASK)

/*!
 * @brief The enumerator of internal capacitance of OSC's XTAL pin.
 */
typedef enum _ccm32k_osc_xtal_cap
{
    kCCM32K_OscXtal0pFCap  = 0x0U, /*!< The internal capacitance for XTAL pin is 0pF. */
    kCCM32K_OscXtal2pFCap  = 0x1U, /*!< The internal capacitance for XTAL pin is 2pF. */
    kCCM32K_OscXtal4pFCap  = 0x2U, /*!< The internal capacitance for XTAL pin is 4pF. */
    kCCM32K_OscXtal6pFCap  = 0x3U, /*!< The internal capacitance for XTAL pin is 6pF. */
    kCCM32K_OscXtal8pFCap  = 0x4U, /*!< The internal capacitance for XTAL pin is 8pF. */
    kCCM32K_OscXtal10pFCap = 0x5U, /*!< The internal capacitance for XTAL pin is 10pF. */
    kCCM32K_OscXtal12pFCap = 0x6U, /*!< The internal capacitance for XTAL pin is 12pF. */
    kCCM32K_OscXtal14pFCap = 0x7U, /*!< The internal capacitance for XTAL pin is 14pF. */
    kCCM32K_OscXtal16pFCap = 0x8U, /*!< The internal capacitance for XTAL pin is 16pF. */
    kCCM32K_OscXtal18pFCap = 0x9U, /*!< The internal capacitance for XTAL pin is 18pF. */
    kCCM32K_OscXtal20pFCap = 0xAU, /*!< The internal capacitance for XTAL pin is 20pF. */
    kCCM32K_OscXtal22pFCap = 0xBU, /*!< The internal capacitance for XTAL pin is 22pF. */
    kCCM32K_OscXtal24pFCap = 0xCU, /*!< The internal capacitance for XTAL pin is 24pF. */
    kCCM32K_OscXtal26pFCap = 0xDU, /*!< The internal capacitance for XTAL pin is 26pF. */
    kCCM32K_OscXtal28pFCap = 0xEU, /*!< The internal capacitance for XTAL pin is 28pF. */
    kCCM32K_OscXtal30pFCap = 0xFU, /*!< The internal capacitance for XTAL pin is 30pF. */
} ccm32k_osc_xtal_cap_t;

/*!
 * @brief The enumerator of internal capacitance of OSC's EXTAL pin.
 */
typedef enum _ccm32k_osc_extal_cap
{
    kCCM32K_OscExtal0pFCap  = 0x0U, /*!< The internal capacitance for EXTAL pin is 0pF. */
    kCCM32K_OscExtal2pFCap  = 0x1U, /*!< The internal capacitance for EXTAL pin is 2pF. */
    kCCM32K_OscExtal4pFCap  = 0x2U, /*!< The internal capacitance for EXTAL pin is 4pF. */
    kCCM32K_OscExtal6pFCap  = 0x3U, /*!< The internal capacitance for EXTAL pin is 6pF. */
    kCCM32K_OscExtal8pFCap  = 0x4U, /*!< The internal capacitance for EXTAL pin is 8pF. */
    kCCM32K_OscExtal10pFCap = 0x5U, /*!< The internal capacitance for EXTAL pin is 10pF. */
    kCCM32K_OscExtal12pFCap = 0x6U, /*!< The internal capacitance for EXTAL pin is 12pF. */
    kCCM32K_OscExtal14pFCap = 0x7U, /*!< The internal capacitance for EXTAL pin is 14pF. */
    kCCM32K_OscExtal16pFCap = 0x8U, /*!< The internal capacitance for EXTAL pin is 16pF. */
    kCCM32K_OscExtal18pFCap = 0x9U, /*!< The internal capacitance for EXTAL pin is 18pF. */
    kCCM32K_OscExtal20pFCap = 0xAU, /*!< The internal capacitance for EXTAL pin is 20pF. */
    kCCM32K_OscExtal22pFCap = 0xBU, /*!< The internal capacitance for EXTAL pin is 22pF. */
    kCCM32K_OscExtal24pFCap = 0xCU, /*!< The internal capacitance for EXTAL pin is 24pF. */
    kCCM32K_OscExtal26pFCap = 0xDU, /*!< The internal capacitance for EXTAL pin is 26pF. */
    kCCM32K_OscExtal28pFCap = 0xEU, /*!< The internal capacitance for EXTAL pin is 28pF. */
    kCCM32K_OscExtal30pFCap = 0xFU, /*!< The internal capacitance for EXTAL pin is 30pF. */
} ccm32k_osc_extal_cap_t;

#if (defined(FSL_FEATURE_CCM32K_HAS_FINE_AMP_GAIN) && FSL_FEATURE_CCM32K_HAS_FINE_AMP_GAIN)
/*!
 * @brief The enumerator of osc amplifier gain fine adjustment.
 * Changes the oscillator amplitude by modifying the automatic gain control (AGC).
 */
typedef enum _ccm32k_osc_fine_adjustment_value
{
    kCCM32K_OscFineAdjustmentRange0 = 0U,
} ccm32k_osc_fine_adjustment_value_t;
#endif /* FSL_FEATURE_CCM32K_HAS_FINE_AMP_GAIN */

/*!
 * @brief The enumerator of osc amplifier coarse fine adjustment.
 * Tunes the internal transconductance (gm) by increasing the current.
 */
typedef enum _ccm32k_osc_coarse_adjustment_value
{
    kCCM32K_OscCoarseAdjustmentRange0 = 0U,
    kCCM32K_OscCoarseAdjustmentRange1 = 1U,
    kCCM32K_OscCoarseAdjustmentRange2 = 2U,
    kCCM32K_OscCoarseAdjustmentRange3 = 3U
} ccm32k_osc_coarse_adjustment_value_t;

/*!
 * @brief The enumerator of 32kHz oscillator.
 */
typedef enum _ccm32k_osc_mode
{
    kCCM32K_Disable32kHzCrystalOsc = 0x0U, /*!< Disable 32kHz Crystal Oscillator. */
    kCCM32K_Enable32kHzCrystalOsc  = 0x1U, /*!< Enable 32kHz Crystal Oscillator.  */
    kCCM32K_Bypass32kHzCrystalOsc  = 0x3U, /*!< Bypass 32kHz Crystal Oscillator,
                                             use the 32kHz Oscillator or external 32kHz clock. */
} ccm32k_osc_mode_t;

/*!
 * @brief The enumerator of CCM32K status flag.
 */
enum
{
    kCCM32K_32kOscReadyStatusFlag = CCM32K_STATUS_OSC32K_RDY_MASK,     /*!< Indicates the 32kHz crystal
                                                                            oscillator is stable. */
    kCCM32K_32kOscActiveStatusFlag = CCM32K_STATUS_OSC32K_ACTIVE_MASK, /*!< Indicates the 32kHz crystal
                                                                        oscillator is active and in use. */
    kCCM32K_32kFroActiveStatusFlag = CCM32K_STATUS_FRO32K_ACTIVE_MASK, /*!< Indicates the 32kHz free running
                                                                        oscillator is active and in use.  */
#if (defined(FSL_FEATURE_CCM32K_HAS_CGC32K) && FSL_FEATURE_CCM32K_HAS_CGC32K)
    kCCM32K_ClockDetectStatusFlag = CCM32K_STATUS_CLOCK_DET_MASK, /*!< Indicates the clock monitor has
                                                                      detected an error. */
#endif                                                            /* FSL_FEATURE_CCM32K_HAS_CGC32K */
};

/*!
 * @brief The enumerator of module state.
 */
typedef enum _ccm32k_state
{
    kCCM32K_Both32kFro32kOscDisabled =
        0x0U, /*!< Indicates both 32kHz free running oscillator and 32kHz crystal oscillator are disabled. */
    kCCM32K_Only32kFroEnabled       = 0x1U, /*!< Indicates only 32kHz free running oscillator is enabled. */
    kCCM32K_Only32kOscEnabled       = 0x2U, /*!< Indicates only 32kHz crystal oscillator is enabled. */
    kCCM32K_Both32kFro32kOscEnabled = ((uint8_t)kCCM32K_Only32kFroEnabled | (uint8_t)kCCM32K_Only32kOscEnabled),
    /*!< Indicates both 32kHz free running oscillator and 32kHz crystal oscillator are enabled. */
} ccm32k_state_t;

/*!
 * @brief The enumerator of clock source.
 */
typedef enum _ccm32k_clock_source
{
    kCCM32K_ClockSourceNone   = 0x0U, /*!< None clock source. */
    kCCM32K_ClockSource32kFro = 0x1U, /*!< 32kHz free running oscillator is the clock source. */
    kCCM32K_ClockSource32kOsc = 0x2U, /*!< 32kHz crystal oscillator is the clock source. */
} ccm32k_clock_source_t;

#if (defined(FSL_FEATURE_CCM32K_HAS_CLKMON_CTRL) && FSL_FEATURE_CCM32K_HAS_CLKMON_CTRL)
/*!
 * @brief Clock monitor frequency trim values.
 */
typedef enum _ccm32k_clock_monitor_freq_trim_value
{
    kCCM32K_ClockMonitor2CycleAssert = 0x0U, /*!< Clock monitor asserts 2 cycle after
                                                 expected edge (assert after 10 cycles with no edge). */
    kCCM32K_ClockMonitor4CycleAssert,        /*!< Clock monitor asserts 4 cycle after
                                                 expected edge (assert after 12 cycles with no edge). */
    kCCM32K_ClockMonitor6CycleAssert,        /*!< Clock monitor asserts 6 cycle after
                                                 expected edge (assert after 14 cycles with no edge). */
    kCCM32K_ClockMonitor8CycleAssert,        /*!< Clock monitor asserts 8 cycle after
                                                 expected edge (assert after 16 cycles with no edge). */
} ccm32k_clock_monitor_freq_trim_value_t;

/*!
 * @brief Clock monitor divide trim values.
 */
typedef enum _ccm32k_clock_monitor_divide_trim_value
{
    kCCM32K_ClockMonitor_1kHzFro32k_1kHzOsc32k = 0x0U, /*!< Clock monitor operates at 1 kHz
                                                           for both FRO32K and OSC32K. */
    kCCM32K_ClockMonitor_64HzFro32k_1kHzOsc32k = 0x1U, /*!< Clock monitor operates at 64 Hz for FRO32K and
                                                           clock monitor operates at 1 kHz for OSC32K. */
    kCCM32K_ClockMonitor_1KHzFro32k_64HzOsc32k = 0x2U, /*!< Clock monitor operates at 1K Hz for FRO32K and
                                                           clock monitor operates at 64 Hz for OSC32K. */
    kCCM32K_ClockMonitor_64HzFro32k_64HzOsc32k = 0x3U, /*!< Clock monitor operates at 64 Hz for FRO32K and
                                                           clock monitor operates at 64 Hz for OSC32K. */
} ccm32k_clock_monitor_divide_trim_value_t;

/*!
 * @brief Clock monitor configuration structure.
 */
typedef struct _ccm32k_clock_monitor_config
{
    bool enableClockMonitor;                                  /*!< Used to enable/disable clock monitor. */
    ccm32k_clock_monitor_freq_trim_value_t freqTrimValue;     /*!< Clock minitor frequency trim value. */
    ccm32k_clock_monitor_divide_trim_value_t divideTrimValue; /*!< Clock minitor divide trim value. */
} ccm32k_clock_monitor_config_t;
#endif /* FSL_FEATURE_CCM32K_HAS_CLKMON_CTRL */

#if (defined(FSL_FEATURE_CCM32K_HAS_CGC32K) && FSL_FEATURE_CCM32K_HAS_CGC32K)
/*!
 * @brief CCM32K clock source enumeration.
 */
typedef enum _ccm32k_clock_source_select
{
    kCCM32K_ClockSourceSelectFro32k = 0x0U, /*!< FRO32K clock output is selected as clock source. */
    kCCM32K_ClockSourceSelectOsc32k,        /*!< OSC32K clock output is selected as clock source. */
} ccm32k_clock_source_select_t;

/*!
 * @brief 32kHz clock output peripheral bit map.
 */
typedef enum _ccm32k_clock_output_peripheral
{
    kCCM32K_ClockOutToRtc          = 1U << 0U, /*!< 32kHz clock output to RTC. */
    kCCM32K_ClockOutToRfmc         = 1U << 1U, /*!< 32kHz clock output to Rfmc. */
    kCCM32K_ClockOutToNbu          = 1U << 2U, /*!< 32kHz clock output to NBU. */
    kCCM32K_ClockOutToWuuRmcPortD  = 1U << 3U, /*!< 32kHz clock output to WUU/RMC/PORTD. */
    kCCM32K_ClockOutToOtherModules = 1U << 4U, /*!< 32kHz clock output to Other modules. */
} ccm32k_clock_output_peripheral_t;

#endif /* FSL_FEATURE_CCM32K_HAS_CGC32K */

/*!
 * @brief The structure of oscillator configuration.
 */
typedef struct _ccm32k_osc_config
{
    bool enableInternalCapBank;      /*!< enable/disable the internal capacitance bank. */
    ccm32k_osc_xtal_cap_t xtalCap;   /*!< The internal capacitance for the OSC XTAL pin from the capacitor bank,
                                             only useful when the internal capacitance bank is enabled. */
    ccm32k_osc_extal_cap_t extalCap; /*!< The internal capacitance for the OSC EXTAL pin from the capacitor bank,
                                             only useful when the internal capacitance bank is enabled. */
#if (defined(FSL_FEATURE_CCM32K_HAS_FINE_AMP_GAIN) && FSL_FEATURE_CCM32K_HAS_FINE_AMP_GAIN)
    ccm32k_osc_fine_adjustment_value_t fineAdjustment; /*!< 32kHz crystal oscillator amplifier fine adjustment value. */
#endif                                                 /* FSL_FEATURE_CCM32K_HAS_FINE_AMP_GAIN */
    ccm32k_osc_coarse_adjustment_value_t
        coarseAdjustment; /*!< 32kHz crystal oscillator amplifier coarse adjustment value. */
} ccm32k_osc_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name 32kHz Free-running Oscillator Interfaces
 * @{
 */

/*!
 * @brief Enable/Disable 32kHz free-running oscillator.
 *
 * @note There is a start up time before clocks are output from the FRO.
 * @note To enable FRO32k and set it as 32kHz clock source please follow steps:
 *      @code
 *          CCM32K_Enable32kFro(base, true);        //Enable FRO analog oscillator.
 *          CCM32K_DisableCLKOutToPeripherals(base, mask); //Disable clock out.
 *          CCM32K_SelectClockSource(base, kCCM32K_ClockSourceSelectFro32k); //Select FRO32k as clock source.
 *          while(CCM32K_GetStatus(base) != kCCM32K_32kFroActiveStatusFlag); //Check FOR32k is active and in used.
 *          CCM32K_EnableCLKOutToPeripherals(base, mask); //Enable clock out if needed.
 *      @endcode
 *
 * @param base CCM32K peripheral base address.
 * @param enable   Boolean value to enable or disable the 32kHz free-running oscillator.
 *                  true    --    Enable 32kHz free-running oscillator.
 *                  false   --    Disable 32kHz free-running oscillator.
 */
void CCM32K_Enable32kFro(CCM32K_Type *base, bool enable);

/*!
 * @brief Lock all further write accesses to the FRO32K_CTRL register until a POR occurs.
 *
 * @param base CCM32K peripheral base address.
 */
static inline void CCM32K_Lock32kFroWriteAccess(CCM32K_Type *base)
{
    base->FRO32K_CTRL |= CCM32K_FRO32K_CTRL_LOCK_EN_MASK;
}

/*!
 * @brief Get frequency trim value of 32kHz free-running oscillator.
 *
 * @param base CCM32K peripheral base address.
 * @return The current trim value.
 */
static inline uint16_t CCM32K_Get32kFroTrimValue(CCM32K_Type *base)
{
    return ((uint16_t)(((base->FRO32K_TRIM) & CCM32K_FRO32K_TRIM_FREQ_TRIM_MASK) >>
                       (uint32_t)CCM32K_FRO32K_TRIM_FREQ_TRIM_SHIFT));
}

/*!
 * @brief Set the frequency trim value of 32kHz free-running oscillator by software.
 *
 * @note The frequency is decreased monotonically when the trimValue is changed progressively
 *       from 0x0U to 0x7FFU.
 *
 * @note If the FRO32 is enabled before invoking this function, then in this function the FRO32 will be disabled,
 *       after updating trim value the FRO32 will be re-enabled.
 *
 * @param base CCM32K peripheral base address.
 * @param trimValue The frequency trim value.
 */
void CCM32K_Set32kFroTrimValue(CCM32K_Type *base, uint16_t trimValue);

/*!
 * @brief Disable/Enable the function of setting 32kHz free-running oscillator trim value
 *        when IFR value gets loaded in the SOC.
 *
 * @param base CCM32K peripheral base address.
 * @param disable Boolean value to disable or enable IFR loading function.
 *                  true    --    Disable IFR loading function.
 *                  false   --    Enable IFR loading function.
 */
static inline void CCM32K_Disable32kFroIFRLoad(CCM32K_Type *base, bool disable)
{
    if (disable)
    {
        base->FRO32K_TRIM |= CCM32K_FRO32K_TRIM_IFR_DIS_MASK;
    }
    else
    {
        base->FRO32K_TRIM &= ~CCM32K_FRO32K_TRIM_IFR_DIS_MASK;
    }
}

/*!
 * @brief Lock all further write accesses to the FRO32K_TRIM register until a POR occurs.
 *
 * @param base CCM32K peripheral base address.
 */
static inline void CCM32K_Lock32kFroTrimWriteAccess(CCM32K_Type *base)
{
    base->FRO32K_TRIM |= CCM32K_FRO32K_TRIM_LOCK_EN_MASK;
}

/*! @} */

/*!
 * @name 32kHz Crystal Oscillator Interfaces
 * @{
 */

/*!
 * @brief Config 32k Crystal Oscillator.
 *
 * @note When the mode selected as \ref kCCM32K_Disable32kHzCrystalOsc or \ref kCCM32K_Bypass32kHzCrystalOsc
 *       the parameter config is useless, so it can be set as "NULL".
 *
 * @note To enable OSC32K and select it as clock source of 32kHz please follow steps:
 *  @code
 *   CCM32K_Set32kOscConfig(base, kCCM32K_Enable32kHzCrystalOsc, config); //Enable OSC32k and set config.
 *   while((CCM32K_GetStatus(base) & kCCM32K_32kOscReadyStatusFlag) == 0UL); //Check if OSC32K is stable.
 *   CCM32K_DisableCLKOutToPeripherals(base, mask); //Disable clock out.
 *   CCM32K_SelectClockSource(base, kCCM32K_ClockSourceSelectOsc32k); //Select OSC32k as clock source.
 *   while((CCM32K_GetStatus(base) & kCCM32K_32kOscActiveStatusFlag) == 0UL); //Check if OSC32K is used as clock source.
 *   CCM32K_EnableCLKOutToPeripherals(base, mask); //Enable clock out.
 *  @endcode
 *
 * @param base CCM32K peripheral base address.
 * @param mode The mode of 32k crystal oscillator.
 * @param config The pointer to the structure \ref ccm32k_osc_config_t.
 */
void CCM32K_Set32kOscConfig(CCM32K_Type *base, ccm32k_osc_mode_t mode, const ccm32k_osc_config_t *config);

/*!
 * @brief Lock all further write accesses to the OSC32K_CTRL register until a POR occurs.
 *
 * @param base CCM32K peripheral base address.
 */
static inline void CCM32K_Lock32kOscWriteAccess(CCM32K_Type *base)
{
    base->OSC32K_CTRL |= CCM32K_OSC32K_CTRL_LOCK_EN_MASK;
}

/*! @} */

#if (defined(FSL_FEATURE_CCM32K_HAS_CLKMON_CTRL) && FSL_FEATURE_CCM32K_HAS_CLKMON_CTRL)
/*!
 * @name Clock Monitor Control Interfaces
 * @{
 */

/*!
 * @brief Enable/disable clock monitor.
 *
 * @param base CCM32K peripheral base address.
 * @param enable Used to enable/disable clock monitor.
 *          - \b turn Enable clock monitor.
 *          - \b false Disable clock monitor.
 */
void CCM32K_EnableClockMonitor(CCM32K_Type *base, bool enable);

/*!
 * @brief Set clock monitor frequency trim value.
 *
 * @param base CCM32K peripheral base address.
 * @param trimValue Clock minitor frequency trim value, please refer to @ref ccm32k_clock_monitor_freq_trim_value_t.
 */
static inline void CCM32K_SetClockMonitorFreqTrimValue(CCM32K_Type *base,
                                                       ccm32k_clock_monitor_freq_trim_value_t trimValue)
{
    base->CLKMON_CTRL =
        (base->CLKMON_CTRL & ~CCM32K_CLKMON_CTRL_FREQ_TRIM_MASK) | CCM32K_CLKMON_CTRL_FREQ_TRIM(trimValue);
}

/*!
 * @brief Set clock monitor divide trim value.
 *
 * @param base CCM32K peripheral base address.
 * @param trimValue Clock minitor divide trim value, please refer to @ref ccm32k_clock_monitor_divide_trim_value_t.
 */
static inline void CCM32K_SetClockMonitorDivideTrimValue(CCM32K_Type *base,
                                                         ccm32k_clock_monitor_divide_trim_value_t trimValue)
{
    base->CLKMON_CTRL =
        (base->CLKMON_CTRL & ~CCM32K_CLKMON_CTRL_DIVIDE_TRIM_MASK) | CCM32K_CLKMON_CTRL_DIVIDE_TRIM(trimValue);
}

/*!
 * @brief Config clock monitor one time, including frequency trim value, divide trim value.
 *
 * @param base CCM32K peripheral base address.
 * @param config Pointer to @ref ccm32k_clock_monitor_config_t structure.
 */
void CCM32K_SetClockMonitorConfig(CCM32K_Type *base, const ccm32k_clock_monitor_config_t *config);

/*!
 * @brief Lock all further write accesses to the CLKMON_CTRL register until a POR occurs.
 *
 * @param base CCM32K peripheral base address.
 */
static inline void CCM32K_LockClockMonitorWriteAccess(CCM32K_Type *base)
{
    base->CLKMON_CTRL |= CCM32K_CLKMON_CTRL_LOCK_EN_MASK;
}

/*!
 * @}
 */
#endif /* FSL_FEATURE_CCM32K_HAS_CLKMON_CTRL */

#if (defined(FSL_FEATURE_CCM32K_HAS_CGC32K) && FSL_FEATURE_CCM32K_HAS_CGC32K)
/*!
 * @name Clock Gate Control Interfaces
 * @{
 */

/*!
 * @brief Enable 32kHz clock output to selected peripherals.
 *
 * @param base CCM32K peripheral base address.
 * @param peripheralMask The mask of peripherals to enable 32kHz clock output,
 *                       should be the OR'ed value of @ref ccm32k_clock_output_peripheral_t.
 */
static inline void CCM32K_EnableCLKOutToPeripherals(CCM32K_Type *base, uint8_t peripheralMask)
{
    base->CGC32K |= CCM32K_CGC32K_CLK_OE_32K(peripheralMask);
}

/*!
 * @brief Disable 32kHz clock output to selected peripherals.
 *
 * @param base CCM32K peripheral base address.
 * @param peripheralMask The mask of peripherals to disable 32kHz clock output,
 *                       should be the OR'ed value of @ref ccm32k_clock_output_peripheral_t.
 */
static inline void CCM32K_DisableCLKOutToPeripherals(CCM32K_Type *base, uint8_t peripheralMask)
{
    base->CGC32K &= ~CCM32K_CGC32K_CLK_OE_32K(peripheralMask);
}

/*!
 * @brief Select CCM32K module's clock source which will be provide to the device.
 *
 * @param base CCM32K peripheral base address.
 * @param clockSource Used to select clock source, please refer to @ref ccm32k_clock_source_select_t for details.
 */
static inline void CCM32K_SelectClockSource(CCM32K_Type *base, ccm32k_clock_source_select_t clockSource)
{
    /* To select OSC32K as clock source, OSC32k must be stable, to select FRO32K as clock source, it must be enabled. */
    assert(((clockSource == kCCM32K_ClockSourceSelectOsc32k) && \
            ((base->STATUS & CCM32K_STATUS_OSC32K_RDY_MASK) == 1UL)) \
            || ((clockSource == kCCM32K_ClockSourceSelectFro32k) && \
            ((base->FRO32K_CTRL & CCM32K_FRO32K_CTRL_FRO_EN_MASK) != 0UL)));

    base->CGC32K = (base->CGC32K & ~CCM32K_CGC32K_CLK_SEL_32K_MASK) | CCM32K_CGC32K_CLK_SEL_32K(clockSource);
}

/*!
 * @brief Lock all further write access to the CGC32K register until a POR occurs.
 *
 * @param base CCM32K peripheral base address.
 */
static inline void CCM32K_LockClockGateWriteAccess(CCM32K_Type *base)
{
    base->CGC32K |= CCM32K_CGC32K_LOCK_EN_MASK;
}
/*!
 * @}
 */
#endif /* FSL_FEATURE_CCM32K_HAS_CGC32K */

/*!
 * @name Status Interface
 * @{
 */

/*!
 * @brief Get the status flag.
 *
 * @param base CCM32K peripheral base address.
 * @return The status flag of the current node. The enumerator of status flags have been provided, please see the
 * Enumerations title for details.
 */
static inline uint32_t CCM32K_GetStatusFlag(CCM32K_Type *base)
{
    return base->STATUS;
}

/*! @} */

/*!
 * @name State/Clock Source Interfaces
 */
/*!
 * @brief Get current state.
 *
 * @param base CCM32K peripheral base address.
 * @return The CCM32K's current state, please refer to \ref ccm32k_state_t for details.
 */
ccm32k_state_t CCM32K_GetCurrentState(CCM32K_Type *base);

/*!
 * @brief Return current clock source.
 *
 * @param base CCM32K peripheral base address.
 * @retval kCCM32K_ClockSourceNone The none clock source is selected.
 * @retval kCCM32K_ClockSource32kFro 32kHz free-running oscillator is selected as clock source.
 * @retval kCCM32K_ClockSource32kOsc 32kHz crystal oscillator is selected as clock source..
 */
ccm32k_clock_source_t CCM32K_GetClockSource(CCM32K_Type *base);

/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* FSL_CCM32K_H_ */
