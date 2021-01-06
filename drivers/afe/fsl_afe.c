/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_afe.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.afe"
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to AFE bases for each instance. */
static AFE_Type *const s_AFEBases[] = AFE_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to AFE clocks for each instance. */
static const clock_ip_name_t s_AFEClocks[] = AFE_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 *******************************************************************************/
static uint32_t AFE_GetInstance(AFE_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_AFEBases); instance++)
    {
        if (s_AFEBases[instance] == base)
        {
            break;
        }
    }
    assert(instance < ARRAY_SIZE(s_AFEBases));

    return instance;
}

/*!
 * brief Initialization for the AFE module.
 *
 * This function configures the AFE module for the configuration
 * which are shared by all channels.
 *
 * param base AFE peripheral base address.
 * param config Pointer to structure of "afe_config_t".
 *
 */
void AFE_Init(AFE_Type *base, const afe_config_t *config)
{
    assert(config != NULL);

    uint32_t regData = 0U;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable clock gate */
    CLOCK_EnableClock(s_AFEClocks[AFE_GetInstance(base)]);
#endif                                                            /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    regData = base->CKR & ~(AFE_CKR_CLS_MASK | AFE_CKR_DIV_MASK); /* Clear old clock select, divider value */
    regData |= AFE_CKR_CLS(config->clockSource) | AFE_CKR_DIV(config->clockDivider);
    base->CKR = regData;

    /* Clear old startup time, result format, low power mode value */
    regData = base->CR & ~(AFE_CR_STRTUP_CNT_MASK | AFE_CR_RESULT_FORMAT_MASK | AFE_CR_RST_B_MASK | AFE_CR_LPM_EN_MASK);
    /* Set new startup time, result format, low power mode value */
    regData |= AFE_CR_STRTUP_CNT((uint8_t)config->startupCount) | AFE_CR_RESULT_FORMAT(config->resultFormat) |
               AFE_CR_LPM_EN(config->enableLowPower);
    /* Write value to CR register */
    base->CR = regData;

    AFE_Enable(base, true); /* Enable the AFE after the initialization. */
}

/*!
 * brief De-Initialization for the AFE module.
 *
 * This function disables clock.
 *
 * param  base AFE peripheral base address.
 */
void AFE_Deinit(AFE_Type *base)
{
    AFE_Enable(base, false); /* Disable the AFE module. */
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable clock gate */
    CLOCK_DisableClock(s_AFEClocks[AFE_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Fills the user configure structure.
 *
 * This function fills the afe_config_t structure with default settings.
 * Defaut value are:
 * code
 * config->enableLowPower   = false;
 * config->resultFormat     = kAFE_ResultFormatRight;
 * config->clockDivider     = kAFE_ClockDivider2;
 * config->clockSource      = kAFE_ClockSource1;
 * config->startupCount     = 2U;
 * endcode
 *
 * param config Pointer to structure of "afe_config_t".
 */
void AFE_GetDefaultConfig(afe_config_t *config)
{
    assert(config != NULL);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    /* Fills the user configure structure. */
    config->enableLowPower = false;
    config->resultFormat   = kAFE_ResultFormatRight;
    config->clockDivider   = kAFE_ClockDivider2;
    config->clockSource    = kAFE_ClockSource1;
    /* Minimum value of startup time */
    config->startupCount = 2U;
}

/*!
 * brief Configure the selected AFE channel.
 *
 * This function configures the selected AFE channel.
 *
 * param base AFE peripheral base address.
 * param channel  AFE channel index.
 * param config Pointer to structure of "afe_channel_config_t".
 *
 */
void AFE_SetChannelConfig(AFE_Type *base, uint32_t channel, const afe_channel_config_t *config)
{
    assert(config != NULL);
    assert((uint8_t)channel < (uint8_t)FSL_FEATURE_AFE_CHANNEL_NUMBER);

    uint32_t regData = 0U;

    regData = base->CFR[channel];
    /* Enable decimation filter. */
    regData |= AFE_CFR_DEC_EN_MASK;
    /* If bypass mode is enabled.  */
    if (config->channelMode != kAFE_BypassDisable)
    {
        regData &= ~(AFE_CFR_DEC_CLK_EDGE_SEL_MASK | AFE_CFR_DEC_CLK_INP_SEL_MASK);
        regData |= (AFE_CFR_BYP_MODE_MASK | AFE_CFR_DEC_CLK_EDGE_SEL((((uint32_t)config->channelMode) >> 1UL) & 0x1UL) |
                    AFE_CFR_DEC_CLK_INP_SEL(((uint32_t)config->channelMode) & 0x1UL));
    }
    else
    {
        regData |= AFE_CFR_SD_MOD_EN_MASK;
        if (config->pgaGainSelect == kAFE_PgaDisable)
        {
            regData &= ~AFE_CFR_PGA_EN_MASK; /* PGA is disabled. */
        }
        else
        {
            /* Set PGA value*/
            regData &= ~AFE_CFR_PGA_GAIN_SEL_MASK;
            regData |= (AFE_CFR_PGA_EN_MASK | AFE_CFR_PGA_GAIN_SEL(config->pgaGainSelect));
        }
    }
    /* Clear old Decimator OverSample Ratio, Conversion Mode, Trigger Select value */
    regData &= ~(AFE_CFR_DEC_OSR_MASK | AFE_CFR_HW_TRG_MASK | AFE_CFR_CC_MASK);
    /* Set new Decimator OverSampling Ratio, Conversion Mode, Trigger Select value */
    regData |= AFE_CFR_DEC_OSR((uint32_t)config->decimatorOversampleRatio) |
               AFE_CFR_CC(config->enableContinuousConversion) | AFE_CFR_HW_TRG(config->enableHardwareTrigger);

    base->CFR[channel] = regData;
}

/*!
 * brief Fills the channel configuration structure.
 *
 * This function fills the afe_channel_config_t structure with default settings.
 * Default value are:
 * code
 * config->enableHardwareTrigger      = false;
 * config->enableContinuousConversion = false;
 * config->channelMode                = kAFE_Normal;
 * config->decimatorOversampleRatio   = kAFE_DecimatorOversampleRatio64;
 * config->pgaGainSelect              = kAFE_PgaGain1;
 * endcode
 *
 * param config Pointer to structure of "afe_channel_config_t".
 */
void AFE_GetDefaultChannelConfig(afe_channel_config_t *config)
{
    assert(config != NULL);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    /* Fills the channel configuration structure. */
    config->enableHardwareTrigger      = false;
    config->enableContinuousConversion = false;
    config->channelMode                = kAFE_BypassDisable;
    config->decimatorOversampleRatio   = kAFE_DecimatorOversampleRatio64;
    config->pgaGainSelect              = kAFE_PgaDisable;
}

/*!
 * brief Reads the raw conversion value.
 *
 * This function returns the raw conversion value of the selected channel.
 *
 * param base AFE peripheral base address.
 * param channel  AFE channel index.
 * return Conversion value.
 * note The returned value could be left or right adjusted according to the AFE module configuration.
 */
uint32_t AFE_GetChannelConversionValue(AFE_Type *base, uint32_t channel)
{
    assert((uint8_t)channel < (uint8_t)FSL_FEATURE_AFE_CHANNEL_NUMBER);

    return base->RR[channel];
}

/*!
 * brief Sets phase delays value.
 *
 * This function sets the phase delays for channels. This delay is inserted before
 * the trigger response of the decimation filters. The delay is used to provide
 * a phase compensation between AFE channels in step of prescaled modulator clock
 * periods.
 * param base AFE peripheral base address.
 * param channel  AFE channel index.
 * param value delay time value.
 */
void AFE_SetChannelPhaseDelayValue(AFE_Type *base, uint32_t channel, uint32_t value)
{
    assert((uint8_t)channel < (uint8_t)FSL_FEATURE_AFE_CHANNEL_NUMBER);

    /* Set delay value for this channel */
    base->DR[channel] = AFE_DR_DLY(value);
}

/*!
 * brief Enables/Disables AFE DMA.
 *
 * This function enables/disables one channel DMA request.
 *
 * param base AFE peripheral base address.
 * param mask  AFE channel dma mask.
 * param enable Pass true to enable interrupt, false to disable.
 *      The parameter can be combination of the following source if defined:
 *      arg kAFE_Channel0DMAEnable
 *      arg kAFE_Channel1DMAEnable
 *      arg kAFE_Channel2DMAEnable
 *      arg kAFE_Channel3DMAEnable
 */
void AFE_EnableChannelDMA(AFE_Type *base, uint32_t mask, bool enable)
{
    uint32_t regData = mask & ((uint32_t)kAFE_Channel0DMAEnable | (uint32_t)kAFE_Channel1DMAEnable |
                               (uint32_t)kAFE_Channel2DMAEnable | (uint32_t)kAFE_Channel3DMAEnable);

    if (enable)
    {
        base->DI |= regData;
    }
    else
    {
        base->DI &= ~regData;
    }
}
