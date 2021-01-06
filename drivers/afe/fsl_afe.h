/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_AFE_H_
#define _FSL_AFE_H_

#include "fsl_common.h"

/*!
 * @addtogroup afe
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
#define FSL_AFE_DRIVER_VERSION (MAKE_VERSION(2, 0, 2)) /*!< Version 2.0.2. */
/*@}*/

/*!
 * @brief Defines the type of status flags.
 */
enum _afe_channel_status_flag
{
    kAFE_Channel0OverflowFlag = AFE_SR_OVR0_MASK, /*!< Channel 0 previous conversion result has not been read and new
                                                     data has already arrived. */
    kAFE_Channel1OverflowFlag = AFE_SR_OVR1_MASK, /*!< Channel 1 previous conversion result has not been read and new
                                                     data has already arrived. */
    kAFE_Channel2OverflowFlag = AFE_SR_OVR2_MASK, /*!< Channel 2 previous conversion result has not been read and new
                                                     data has already arrived. */
    kAFE_Channel0ReadyFlag              = AFE_SR_RDY0_MASK, /*!< Channel 0 is ready to conversion. */
    kAFE_Channel1ReadyFlag              = AFE_SR_RDY1_MASK, /*!< Channel 1 is ready to conversion. */
    kAFE_Channel2ReadyFlag              = AFE_SR_RDY2_MASK, /*!< Channel 2 is ready to conversion. */
    kAFE_Channel0ConversionCompleteFlag = AFE_SR_COC0_MASK, /*!< Channel 0 conversion is complete. */
    kAFE_Channel1ConversionCompleteFlag = AFE_SR_COC1_MASK, /*!< Channel 1 conversion is complete. */
    kAFE_Channel2ConversionCompleteFlag = AFE_SR_COC2_MASK, /*!< Channel 2 conversion is complete. */
#if defined(FSL_FEATURE_AFE_HAS_FOUR_CHANNELS) && FSL_FEATURE_AFE_HAS_FOUR_CHANNELS
    kAFE_Channel3OverflowFlag = AFE_SR_OVR3_MASK, /*!< Channel 3 previous conversion result has not been read and new
                                                     data has already arrived. */
    kAFE_Channel3ReadyFlag              = AFE_SR_RDY3_MASK, /*!< Channel 3 is ready to conversion. */
    kAFE_Channel3ConversionCompleteFlag = AFE_SR_COC3_MASK  /*!< Channel 3 conversion is complete. */
#endif                                                      /* FSL_FEATURE_AFE_HAS_FOUR_CHANNELS */
};

/*!
 * @brief Defines AFE interrupt enable.
 */
enum
{
    kAFE_Channel0InterruptEnable = AFE_DI_INTEN0_MASK, /*!< Channel 0 Interrupt. */
    kAFE_Channel1InterruptEnable = AFE_DI_INTEN1_MASK, /*!< Channel 1 Interrupt. */
    kAFE_Channel2InterruptEnable = AFE_DI_INTEN2_MASK, /*!< Channel 2 Interrupt. */
#if defined(FSL_FEATURE_AFE_HAS_FOUR_CHANNELS) && FSL_FEATURE_AFE_HAS_FOUR_CHANNELS
    kAFE_Channel3InterruptEnable = AFE_DI_INTEN3_MASK /*!< Channel 3 Interrupt. */
#endif                                                /* FSL_FEATURE_AFE_HAS_FOUR_CHANNELS */
};

/*!
 * @brief Defines AFE DMA enable.
 */
enum
{
    kAFE_Channel0DMAEnable = AFE_DI_DMAEN0_MASK, /*!< Channel 0 DMA. */
    kAFE_Channel1DMAEnable = AFE_DI_DMAEN1_MASK, /*!< Channel 1 DMA. */
    kAFE_Channel2DMAEnable = AFE_DI_DMAEN2_MASK, /*!< Channel 2 DMA. */
#if defined(FSL_FEATURE_AFE_HAS_FOUR_CHANNELS) && FSL_FEATURE_AFE_HAS_FOUR_CHANNELS
    kAFE_Channel3DMAEnable = AFE_DI_DMAEN3_MASK /*!< Channel 3 DMA */
#endif                                          /* FSL_FEATURE_AFE_HAS_FOUR_CHANNELS */
};

/*!
 * @brief Defines AFE channel trigger flag.
 */
enum
{
    kAFE_Channel0Trigger = AFE_CR_SOFT_TRG0_MASK, /*!< Channel 0 software trigger. */
    kAFE_Channel1Trigger = AFE_CR_SOFT_TRG1_MASK, /*!< Channel 1 software trigger. */
    kAFE_Channel2Trigger = AFE_CR_SOFT_TRG2_MASK, /*!< Channel 2 software trigger. */
#if defined(FSL_FEATURE_AFE_HAS_FOUR_CHANNELS) && FSL_FEATURE_AFE_HAS_FOUR_CHANNELS
    kAFE_Channel3Trigger = AFE_CR_SOFT_TRG3_MASK /*!< Channel 3 software trigger. */
#endif                                           /* FSL_FEATURE_AFE_HAS_FOUR_CHANNELS */
};

/*!
 * @brief AFE OSR modes.
 */
typedef enum _afe_decimator_oversampling_ratio
{
    kAFE_DecimatorOversampleRatio64   = 0U, /*!< Decimator over sample ratio is 64. */
    kAFE_DecimatorOversampleRatio128  = 1U, /*!< Decimator over sample ratio is 128. */
    kAFE_DecimatorOversampleRatio256  = 2U, /*!< Decimator over sample ratio is 256. */
    kAFE_DecimatorOversampleRatio512  = 3U, /*!< Decimator over sample ratio is 512. */
    kAFE_DecimatorOversampleRatio1024 = 4U, /*!< Decimator over sample ratio is 1024. */
    kAFE_DecimatorOversampleRatio2048 = 5U, /*!< Decimator over sample ratio is 2048. */
} afe_decimator_oversample_ratio_t;

/*!
 * @brief Defines the AFE result format modes.
 */
typedef enum _afe_result_format
{
    kAFE_ResultFormatLeft  = 0U, /*!< Left justified result format. */
    kAFE_ResultFormatRight = 1U, /*!< Right justified result format. */
} afe_result_format_t;

/*!
 * @brief Defines the AFE clock divider modes.
 */
typedef enum _afe_clock_divider
{
    kAFE_ClockDivider1   = 0U, /*!< Clock divided by 1. */
    kAFE_ClockDivider2   = 1U, /*!< Clock divided by 2. */
    kAFE_ClockDivider4   = 2U, /*!< Clock divided by 4. */
    kAFE_ClockDivider8   = 3U, /*!< Clock divided by 8. */
    kAFE_ClockDivider16  = 4U, /*!< Clock divided by 16. */
    kAFE_ClockDivider32  = 5U, /*!< Clock divided by 32. */
    kAFE_ClockDivider64  = 6U, /*!< Clock divided by 64. */
    kAFE_ClockDivider128 = 7U, /*!< Clock divided by 128. */
    kAFE_ClockDivider256 = 8U, /*!< Clock divided by 256. */
} afe_clock_divider_t;

/*!
 * @brief Defines the AFE clock source modes.
 */
typedef enum _afe_clock_source
{
    kAFE_ClockSource0 = 0U, /*!< Modulator clock source 0. */
    kAFE_ClockSource1 = 1U, /*!< Modulator clock source 1. */
    kAFE_ClockSource2 = 2U, /*!< Modulator clock source 2. */
    kAFE_ClockSource3 = 3U, /*!< Modulator clock source 3. */
} afe_clock_source_t;

/*!
 * @brief Defines the PGA's values.
 */
typedef enum _afe_pga_gain
{
    kAFE_PgaDisable = 0U, /*!< PGA disabled. */
    kAFE_PgaGain1   = 1U, /*!< Input gained by 1. */
    kAFE_PgaGain2   = 2U, /*!< Input gained by 2. */
    kAFE_PgaGain4   = 3U, /*!< Input gained by 4. */
    kAFE_PgaGain8   = 4U, /*!< Input gained by 8. */
    kAFE_PgaGain16  = 5U, /*!< Input gained by 16. */
    kAFE_PgaGain32  = 6U, /*!< Input gained by 32. */
} afe_pga_gain_t;

/*!
 * @brief Defines the bypass modes.
 */
typedef enum _afe_bypass_mode
{
    kAFE_BypassInternalClockPositiveEdge = 0U, /*!< Bypassed channel mode - internal clock selected,
                                                positive edge for registering data by the decimation filter */
    kAFE_BypassExternalClockPositiveEdge = 1U, /*!< Bypassed channel mode - external clock selected,
                                                positive edge for registering data by the decimation filter */
    kAFE_BypassInternalClockNegativeEdge = 2U, /*!< Bypassed channel mode - internal clock selected,
                                                negative edge for registering data by the decimation filter */
    kAFE_BypassExternalClockNegativeEdge = 3U, /*!< Bypassed channel mode - external clock selected,
                                                negative edge for registering data by the decimation filter */
    kAFE_BypassDisable = 4U,                   /*!< Normal channel mode. */
} afe_bypass_mode_t;

/*!
 * @brief Defines the structure to initialize the AFE channel.
 *
 * This structure keeps the configuration for the AFE channel.
 */
typedef struct _afe_channel_config
{
    bool enableHardwareTrigger;      /*!< Enable triggering by hardware. */
    bool enableContinuousConversion; /*!< Enable continuous conversion mode. */
    afe_bypass_mode_t channelMode;   /*!< Select if channel is in bypassed mode. */
    afe_pga_gain_t pgaGainSelect;    /*!< Select the analog gain applied to the input signal. */
    afe_decimator_oversample_ratio_t decimatorOversampleRatio; /*!< Select the over sampling ration. */
} afe_channel_config_t;

/*!
 * @brief Defines the structure to initialize the AFE module.
 *
 * This structure keeps the configuration for the AFE module.
 */
typedef struct _afe_config
{
    bool enableLowPower;              /*!< Enable low power mode. */
    afe_result_format_t resultFormat; /*!< Select the result format. */
    afe_clock_divider_t clockDivider; /*!< Select the clock divider ration for the modulator clock. */
    afe_clock_source_t clockSource;   /*!< Select clock source for modulator clock. */
    uint8_t startupCount;             /*!< Select the start up delay of modulators. */
} afe_config_t;

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @name AFE Initialization
 * @{
 */

/*!
 * @brief Initialization for the AFE module.
 *
 * This function configures the AFE module for the configuration
 * which are shared by all channels.
 *
 * @param base AFE peripheral base address.
 * @param config Pointer to structure of "afe_config_t".
 *
 */
void AFE_Init(AFE_Type *base, const afe_config_t *config);

/*!
 * @brief De-Initialization for the AFE module.
 *
 * This function disables clock.
 *
 * @param  base AFE peripheral base address.
 */
void AFE_Deinit(AFE_Type *base);

/*!
 * @brief Fills the user configure structure.
 *
 * This function fills the afe_config_t structure with default settings.
 * Defaut value are:
 * @code
 * config->enableLowPower   = false;
 * config->resultFormat     = kAFE_ResultFormatRight;
 * config->clockDivider     = kAFE_ClockDivider2;
 * config->clockSource      = kAFE_ClockSource1;
 * config->startupCount     = 2U;
 * @endcode
 *
 * @param config Pointer to structure of "afe_config_t".
 */
void AFE_GetDefaultConfig(afe_config_t *config);

/*!
 * @brief Software reset the AFE module.
 *
 * This function is to reset all the ADCs, PGAs, decimation filters and clock configuration bits. When asserted as
 * "false", all ADCs, PGAs and decimation filters are disabled. Clock Configuration bits are reset. When asserted as
 * "true", all ADCs, PGAs and decimation filters are enabled.
 *
 * @param base AFE peripheral base address.
 * @param enable Assert the reset command.
 */
static inline void AFE_SoftwareReset(AFE_Type *base, bool enable)
{
    if (enable)
    {
        base->CR |= AFE_CR_RST_B_MASK;
    }
    else
    {
        base->CR &= ~AFE_CR_RST_B_MASK;
    }
}

/*!
 * @brief Enables all configured AFE channels.
 *
 * This function enables AFE and filter.
 *
 * @param base AFE peripheral base address.
 * @param enable Enable the AFE module or not.
 */
static inline void AFE_Enable(AFE_Type *base, bool enable)
{
    if (enable)
    {
        base->CR |= AFE_CR_MSTR_EN_MASK;
    }
    else
    {
        base->CR &= ~AFE_CR_MSTR_EN_MASK;
    }
}

/* @} */

/*!
 * @name AFE Conversion
 * @{
 */

/*!
 * @brief Configure the selected AFE channel.
 *
 * This function configures the selected AFE channel.
 *
 * @param base AFE peripheral base address.
 * @param channel  AFE channel index.
 * @param config Pointer to structure of "afe_channel_config_t".
 *
 */
void AFE_SetChannelConfig(AFE_Type *base, uint32_t channel, const afe_channel_config_t *config);

/*!
 * @brief Fills the channel configuration structure.
 *
 * This function fills the afe_channel_config_t structure with default settings.
 * Default value are:
 * @code
 * config->enableHardwareTrigger      = false;
 * config->enableContinuousConversion = false;
 * config->channelMode                = kAFE_Normal;
 * config->decimatorOversampleRatio   = kAFE_DecimatorOversampleRatio64;
 * config->pgaGainSelect              = kAFE_PgaGain1;
 * @endcode
 *
 * @param config Pointer to structure of "afe_channel_config_t".
 */
void AFE_GetDefaultChannelConfig(afe_channel_config_t *config);

/*!
 * @brief Reads the raw conversion value.
 *
 * This function returns the raw conversion value of the selected channel.
 *
 * @param base AFE peripheral base address.
 * @param channel  AFE channel index.
 * @return Conversion value.
 * @note The returned value could be left or right adjusted according to the AFE module configuration.
 */
uint32_t AFE_GetChannelConversionValue(AFE_Type *base, uint32_t channel);

/*!
 * @brief Triggers the AFE conversion by software.
 *
 * This function triggers the AFE conversion by executing a software command. It
 * starts the conversion on selected channels if the software trigger option is
 * selected for the channels.
 *
 * @param base AFE peripheral base address.
 * @param mask  AFE channel mask software trigger.
 *      The parameter can be combination of the following source if defined:
 *      @arg kAFE_Channel0Trigger
 *      @arg kAFE_Channel1Trigger
 *      @arg kAFE_Channel2Trigger
 *      @arg kAFE_Channel3Trigger
 */
static inline void AFE_DoSoftwareTriggerChannel(AFE_Type *base, uint32_t mask)
{
    base->CR |= mask & ((uint32_t)kAFE_Channel0Trigger | (uint32_t)kAFE_Channel1Trigger |
                        (uint32_t)kAFE_Channel2Trigger | (uint32_t)kAFE_Channel3Trigger);
}

/*!
 * @brief Gets the AFE status flag state.
 *
 * This function gets all AFE status.
 *
 * @param base AFE peripheral base address.
 * @return the mask of these status flag bits.
 */
static inline uint32_t AFE_GetChannelStatusFlags(AFE_Type *base)
{
    return base->SR;
}

/*!
 * @brief Sets phase delays value.
 *
 * This function sets the phase delays for channels. This delay is inserted before
 * the trigger response of the decimation filters. The delay is used to provide
 * a phase compensation between AFE channels in step of prescaled modulator clock
 * periods.
 * @param base AFE peripheral base address.
 * @param channel  AFE channel index.
 * @param value delay time value.
 */
void AFE_SetChannelPhaseDelayValue(AFE_Type *base, uint32_t channel, uint32_t value);

/*!
 * @brief Asserts the phase delay setting.
 *
 * This function should be called after all desired channel's
 * delay registers are loaded. Values in channel's delay registers are active
 * after calling this function and after the conversation starts.
 *
 * @param base AFE peripheral base address.
 */
static inline void AFE_SetChannelPhasetDelayOk(AFE_Type *base)
{
    base->CR |= AFE_CR_DLY_OK_MASK;
}

/*!
 * @brief Enables AFE interrupt.
 *
 * This function enables one channel interrupt.
 *
 * @param base AFE peripheral base address.
 * @param mask  AFE channel interrupt mask.
 *      The parameter can be combination of the following source if defined:
 *      @arg kAFE_Channel0InterruptEnable
 *      @arg kAFE_Channel1InterruptEnable
 *      @arg kAFE_Channel2InterruptEnable
 *      @arg kAFE_Channel3InterruptEnable
 */
static inline void AFE_EnableChannelInterrupts(AFE_Type *base, uint32_t mask)
{
    base->DI |= mask & ((uint32_t)kAFE_Channel0InterruptEnable | (uint32_t)kAFE_Channel1InterruptEnable |
                        (uint32_t)kAFE_Channel2InterruptEnable | (uint32_t)kAFE_Channel3InterruptEnable);
}

/*!
 * @brief Disables AFE interrupt.
 *
 * This function disables one channel interrupt.
 *
 * @param base AFE peripheral base address.
 * @param mask  AFE channel interrupt mask.
 *      The parameter can be combination of the following source if defined:
 *      @arg kAFE_Channel0InterruptEnable
 *      @arg kAFE_Channel1InterruptEnable
 *      @arg kAFE_Channel2InterruptEnable
 *      @arg kAFE_Channel3InterruptEnable
 */
static inline void AFE_DisableChannelInterrupts(AFE_Type *base, uint32_t mask)
{
    base->DI &= ~(mask & ((uint32_t)kAFE_Channel0InterruptEnable | (uint32_t)kAFE_Channel1InterruptEnable |
                          (uint32_t)kAFE_Channel2InterruptEnable | (uint32_t)kAFE_Channel3InterruptEnable));
}

/*!
 * @brief Returns mask of all enabled AFE interrupts.
 *
 * @param base AFE peripheral base address.
 * @return Return the mask of these interrupt enable/disable bits.
 */
static inline uint32_t AFE_GetEnabledChannelInterrupts(AFE_Type *base)
{
    return base->DI & ((uint32_t)kAFE_Channel0InterruptEnable | (uint32_t)kAFE_Channel1InterruptEnable |
                       (uint32_t)kAFE_Channel2InterruptEnable | (uint32_t)kAFE_Channel3InterruptEnable);
}

/*!
 * @brief Enables/Disables AFE DMA.
 *
 * This function enables/disables one channel DMA request.
 *
 * @param base AFE peripheral base address.
 * @param mask  AFE channel dma mask.
 * @param enable Pass true to enable interrupt, false to disable.
 *      The parameter can be combination of the following source if defined:
 *      @arg kAFE_Channel0DMAEnable
 *      @arg kAFE_Channel1DMAEnable
 *      @arg kAFE_Channel2DMAEnable
 *      @arg kAFE_Channel3DMAEnable
 */
void AFE_EnableChannelDMA(AFE_Type *base, uint32_t mask, bool enable);

/* @} */

#if defined(__cplusplus)
}
#endif
/*!
 * @}
 */
#endif /* _FSL_AFE_H_ */
