/*
 * Copyright 2020-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_ccm32k.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.ccm32k"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Enable/Disable 32kHz free-running oscillator.
 *
 * note There is a start up time before clocks are output from the FRO.
 *
 * @code
 *          CCM32K_Enable32kFro(base, true);        //Enable FRO analog oscillator.
 *          CCM32K_DisableCLKOutToPeripherals(base, mask); //Disable clock out.
 *          CCM32K_SelectClockSource(base, kCCM32K_ClockSourceSelectFro32k); //Select FRO32k as clock source.
 *          while(CCM32K_GetStatus(base) != kCCM32K_32kFroActiveStatusFlag); //Check FOR32k is active and in used.
 *          CCM32K_EnableCLKOutToPeripherals(base, mask); //Enable clock out if needed.
 * @endcode
 *
 * param base CCM32K peripheral base address.
 * param enable   Boolean value to enable or disable the 32kHz free-running oscillator.
 *                  true    --    Enable 32kHz free-running oscillator.
 *                  false   --    Disable 32kHz free-running oscillator.
 */
void CCM32K_Enable32kFro(CCM32K_Type *base, bool enable)
{
    if (enable)
    {
        if ((base->FRO32K_CTRL & CCM32K_FRO32K_CTRL_FRO_EN_MASK) != 0UL)
        {
            return;
        }

        base->FRO32K_CTRL |= CCM32K_FRO32K_CTRL_FRO_EN_MASK;
    }
    else
    {
        base->FRO32K_CTRL &= ~CCM32K_FRO32K_CTRL_FRO_EN_MASK;
    }
}

/*!
 * brief Set the frequency trim value of 32kHz free-running oscillator by software.
 *
 * param base CCM32K peripheral base address.
 * param trimValue The frequency trim value.
 */
void CCM32K_Set32kFroTrimValue(CCM32K_Type *base, uint16_t trimValue)
{
    uint32_t tmp32;
    bool froEnabled;

    froEnabled = ((base->FRO32K_CTRL & CCM32K_FRO32K_CTRL_FRO_EN_MASK) != 0UL) ? true : false;
    if (froEnabled)
    {
        /* If the free-running oscillator is enabled, disable it temporarily. */
        CCM32K_Enable32kFro(base, false);
    }

    tmp32 = base->FRO32K_TRIM;
    tmp32 &= ~CCM32K_FRO32K_TRIM_FREQ_TRIM_MASK;
    tmp32 |= CCM32K_FRO32K_TRIM_FREQ_TRIM(trimValue);
    base->FRO32K_TRIM = tmp32;

    if (froEnabled)
    {
        /* If the free-running oscillator is enabled previously, remember to enable it again. */
        CCM32K_Enable32kFro(base, true);
    }
}

/*!
 * brief Config 32k Crystal Oscillator.
 *
 * note When the mode selected as \ref kCCM32K_Disable32kHzCrystalOsc or \ref kCCM32K_Bypass32kHzCrystalOsc
 *       the parameter config is useless, so it can be set as "NULL".
 *
 *  @code
 *   CCM32K_Set32kOscConfig(base, kCCM32K_Enable32kHzCrystalOsc, config); //Enable OSC32k and set config.
 *   while((CCM32K_GetStatus(base) & kCCM32K_32kOscReadyStatusFlag) == 0UL); //Check if OSC32K is stable.
 *   CCM32K_DisableCLKOutToPeripherals(base, mask); //Disable clock out.
 *   CCM32K_SelectClockSource(base, kCCM32K_ClockSourceSelectOsc32k); //Select OSC32k as clock source.
 *   while((CCM32K_GetStatus(base) & kCCM32K_32kOscActiveStatusFlag) == 0UL); //Check if OSC32K is used as clock source.
 *   CCM32K_EnableCLKOutToPeripherals(base, mask); //Enable clock out.
 *  @endcode
 *
 * param base CCM32K peripheral base address.
 * param mode The mode of 32k crystal oscillator.
 * param config The pointer to the structure \ref ccm32k_osc_config_t.
 */
void CCM32K_Set32kOscConfig(CCM32K_Type *base, ccm32k_osc_mode_t mode, const ccm32k_osc_config_t *config)
{
    uint32_t tmp32;

    if (mode == kCCM32K_Disable32kHzCrystalOsc)
    {
        /* OSC32k should not be disabled if it is used as clock source of 32 kHz. */
        assert(CCM32K_GetClockSource(base) != kCCM32K_ClockSource32kOsc);
        base->OSC32K_CTRL &= ~(CCM32K_OSC32K_CTRL_OSC_MODE_MASK | CCM32K_OSC32K_CTRL_SOX_EN_MASK);
    }
    else if (mode == kCCM32K_Bypass32kHzCrystalOsc)
    {
        base->OSC32K_CTRL |= CCM32K_OSC32K_CTRL_OSC_MODE_MASK;
    }
    else
    {
        tmp32 = base->OSC32K_CTRL;

        /*
         * $Branch Coverage Justification$
         * (config == NULL) not covered. The conifg memory space value cannot set to null.
         */
        if (config != NULL)
        {
            if (config->enableInternalCapBank)
            {
                tmp32 &= ~(CCM32K_OSC32K_CTRL_EXTAL_CAP_SEL_MASK | CCM32K_OSC32K_CTRL_XTAL_CAP_SEL_MASK);
                tmp32 |= CCM32K_OSC32K_CTRL_EXTAL_CAP_SEL(config->extalCap) |
                         CCM32K_OSC32K_CTRL_XTAL_CAP_SEL(config->xtalCap);
                tmp32 |= CCM32K_OSC32K_CTRL_CAP_SEL_EN_MASK;
            }
            else
            {
                /* Disable the internal capacitance bank. */
                tmp32 &= ~CCM32K_OSC32K_CTRL_CAP_SEL_EN_MASK;
            }

            tmp32 &= ~(CCM32K_OSC32K_CTRL_COARSE_AMP_GAIN_MASK);
            tmp32 |= CCM32K_OSC32K_CTRL_COARSE_AMP_GAIN(config->coarseAdjustment);
#if (defined(FSL_FEATURE_CCM32K_HAS_FINE_AMP_GAIN) && FSL_FEATURE_CCM32K_HAS_FINE_AMP_GAIN)
            tmp32 &= ~(CCM32K_OSC32K_CTRL_FINE_AMP_GAIN_MASK);
            tmp32 |= CCM32K_OSC32K_CTRL_FINE_AMP_GAIN(config->fineAdjustment);
#endif /* FSL_FEATURE_CCM32K_HAS_FINE_AMP_GAIN */
        }

        tmp32 |= CCM32K_OSC32K_CTRL_OSC_MODE(mode) | CCM32K_OSC32K_CTRL_SOX_EN_MASK;
        base->OSC32K_CTRL = tmp32;
    }
}

#if (defined(FSL_FEATURE_CCM32K_HAS_CLKMON_CTRL) && FSL_FEATURE_CCM32K_HAS_CLKMON_CTRL)

/*!
 * brief Enable/disable clock monitor.
 *
 * param base CCM32K peripheral base address.
 * param enable Used to enable/disable clock monitor.
 *          - \b turn Enable clock monitor.
 *          - \b false Disable clock monitor.
 */
void CCM32K_EnableClockMonitor(CCM32K_Type *base, bool enable)
{
    if (enable)
    {
        /* To enable monitor, one of 32k Hz clock source must be enabled. */
        assert(CCM32K_GetClockSource(base) != kCCM32K_ClockSourceNone);
        base->CLKMON_CTRL |= CCM32K_CLKMON_CTRL_MON_EN_MASK;
    }
    else
    {
        base->CLKMON_CTRL &= ~CCM32K_CLKMON_CTRL_MON_EN_MASK;
    }
}

/*!
 * brief Config clock monitor one time, including frequency trim value, divide trim value.
 *
 * param base CCM32K peripheral base address.
 * param config Pointer to @ref ccm32k_clock_monitor_config_t structure.
 */
void CCM32K_SetClockMonitorConfig(CCM32K_Type *base, const ccm32k_clock_monitor_config_t *config)
{
    assert(config);

    if (config->enableClockMonitor)
    {
        CCM32K_EnableClockMonitor(base, false);
    }

    CCM32K_SetClockMonitorFreqTrimValue(base, config->freqTrimValue);
    CCM32K_SetClockMonitorDivideTrimValue(base, config->divideTrimValue);
    CCM32K_EnableClockMonitor(base, config->enableClockMonitor);
}
#endif /* FSL_FEATURE_CCM32K_HAS_CLKMON_CTRL */

/*!
 * brief Get current state.
 *
 * param base CCM32K peripheral base address.
 * return The CCM32K's current state, please refer to \ref ccm32k_state_t for details.
 */
ccm32k_state_t CCM32K_GetCurrentState(CCM32K_Type *base)
{
    uint8_t state = 0U;

    if ((base->FRO32K_CTRL & CCM32K_FRO32K_CTRL_FRO_EN_MASK) != 0UL)
    {
        state |= (uint8_t)kCCM32K_Only32kFroEnabled;
    }

    if ((base->OSC32K_CTRL & CCM32K_OSC32K_CTRL_OSC_EN_MASK) != 0UL)
    {
        state |= (uint8_t)kCCM32K_Only32kOscEnabled;
    }

    return (ccm32k_state_t)state;
}

/*!
 * brief Return current clock source.
 *
 * param base CCM32K peripheral base address.
 * retval kCCM32K_ClockSourceNone The none clock source is selected.
 * retval kCCM32K_ClockSource32kFro 32kHz free-running oscillator is selected as clock source.
 * retval kCCM32K_ClockSource32kOsc 32kHz crystal oscillator is selected as clock source..
 */
ccm32k_clock_source_t CCM32K_GetClockSource(CCM32K_Type *base)
{
    uint32_t statusFlag;
    ccm32k_clock_source_t clockSource = kCCM32K_ClockSourceNone;

    statusFlag = CCM32K_GetStatusFlag(base);

    if (statusFlag == ((uint32_t)kCCM32K_32kOscActiveStatusFlag | (uint32_t)kCCM32K_32kOscReadyStatusFlag))
    {
        clockSource = kCCM32K_ClockSource32kOsc;
    }
    else if ((statusFlag & (uint32_t)kCCM32K_32kFroActiveStatusFlag) != 0UL)
    {
        clockSource = kCCM32K_ClockSource32kFro;
    }
    /*
     * $Branch Coverage Justification$
     * (statusFlag != 0UL) not covered. All status are covered above.
     */
    else
    {
        clockSource = kCCM32K_ClockSourceNone;
    }

    return clockSource;
}
