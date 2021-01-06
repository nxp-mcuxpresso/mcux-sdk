/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_asrc.h"
#include "fsl_asrc_firmware.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.easrc"
#endif

/*******************************************************************************
 * Definitations
 ******************************************************************************/
/*! @brief asrc sample rate ratio format */
typedef enum _asrc_samplerate_ratio_format
{
    kASRC_SampleRateRatio5Int39Frac = 32,  /*!< sample rate ratio 5 integer bits and 39 fractional bits */
    kASRC_SampleRateRatio6Int38Frac = 64,  /*!< sample rate ratio 6 integer bits and 38 fractional bits */
    kASRC_SampleRateRatio7Int37Frac = 128, /*!< sample rate ratio 7 integer bits and 37 fractional bits */
} asrc_samplerate_ratio_format_t;

/*! @brief ASRC support maximum channel number */
#define ASRC_SUPPORT_MAXIMUM_CHANNEL_NUMBER 32U
/*! @brief ASRC support maximum channel number of one context process pipe line */
#define ASRC_SUPPORT_CONTEXT_PROCESSOR_MAXIMUM_CHANNEL_NUMBER 8U
/*! @brief ASRC support maximum channel number of context */
#define ASRC_SUPPORT_MAXIMUM_CONTEXT_PROCESSOR_NUMBER 4U

/*! @brief ASRC macro to get register field value*/
#define ASRC_GET_SLOT0_CONTEXT_INDEX(context)                                            \
    ((base->PROC_CTRL_SLOT0_R0[context] & ASRC_PROC_CTRL_SLOT0_R0_SLOT0_CTX_NUM_MASK) >> \
     ASRC_PROC_CTRL_SLOT0_R0_SLOT0_CTX_NUM_SHIFT)
#define ASRC_GET_SLOT0_CHANNEL_NUMBER(context)                                          \
    ((base->PROC_CTRL_SLOT0_R0[context] & ASRC_PROC_CTRL_SLOT0_R0_SLOT0_NUM_CH_MASK) >> \
     ASRC_PROC_CTRL_SLOT0_R0_SLOT0_NUM_CH_SHIFT)
#define ASRC_GET_SLOT1_CONTEXT_INDEX(context)                                            \
    ((base->PROC_CTRL_SLOT1_R0[context] & ASRC_PROC_CTRL_SLOT1_R0_SLOT1_CTX_NUM_MASK) >> \
     ASRC_PROC_CTRL_SLOT1_R0_SLOT1_CTX_NUM_SHIFT)
#define ASRC_GET_SLOT1_CHANNEL_NUMBER(context)                                          \
    ((base->PROC_CTRL_SLOT1_R0[context] & ASRC_PROC_CTRL_SLOT1_R0_SLOT1_NUM_CH_MASK) >> \
     ASRC_PROC_CTRL_SLOT1_R0_SLOT1_NUM_CH_SHIFT)
#define ASRC_IS_CONTEXT_ENABLED(index) ((base->CTX_CTRL[index] & ASRC_CTX_CTRL_RUN_EN_MASK) != 0U)
#define ASRC_IS_SLOT0_ENABLED(context) \
    ((base->PROC_CTRL_SLOT0_R0[context] & ASRC_PROC_CTRL_SLOT0_R0_SLOT0_EN_MASK) != 0U)
#define ASRC_IS_SLOT1_ENABLED(context) \
    ((base->PROC_CTRL_SLOT1_R0[context] & ASRC_PROC_CTRL_SLOT1_R0_SLOT1_EN_MASK) != 0U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief ASRC get greatest common divisor between the input and output sample rate.
 *
 * @param inputSampleRate input sample rate.
 * @param outputSampleRate output sample rate.
 * @retval GCD between the input and output sample rate.
 */
static uint32_t ASRC_GetSampleRateGCD(uint32_t inputSampleRate, uint32_t outputSampleRate);

/*!
 * @brief ASRC get avalible context slot channel.
 *
 * @param base ASRC base address.
 * @param contextProcessor context processor number.
 * @param slot0UsedChannel slot0 used channel number.
 * @param slot1UsedChannel slot1 used channel number.
 */
static void ASRC_GetAvalibleContextSlot(ASRC_Type *base,
                                        uint32_t contextProcessor,
                                        uint32_t *slot0UsedChannel,
                                        uint32_t *slot1UsedChannel);

/*!
 * @brief ASRC enable context slot.
 *
 * @param base ASRC base address.
 * @param contextProcessor context processor number.
 * @param slot slot number.
 * @param channelNums channel number
 * @param startChannel start channel number runing on this slot.
 * @param context context number runing on this slot.
 */
static void ASRC_EnableContextSlot(ASRC_Type *base,
                                   uint32_t contextProcessor,
                                   uint32_t slot,
                                   uint32_t channelNums,
                                   uint32_t startChannel,
                                   asrc_context_t runingContext);

/*!
 * @brief ASRC config the sample rate ratio.
 *
 * @param base ASRC base address.
 * @param context context number.
 * @param inputSampleRate input sample rate.
 * @param outputSampleRate output sample rate.
 * @param format sample rate ratio format.
 * @retval kStatus_Success, else configure failed.
 */
static status_t ASRC_SetSampleRateRatioConfig(ASRC_Type *base,
                                              asrc_context_t context,
                                              uint32_t inputSampleRate,
                                              uint32_t outputSampleRate,
                                              asrc_samplerate_ratio_format_t format);

/*!
 * @brief ASRC load prefilter configuration.
 *
 * @param config prefliter pointer.
 * @param inputSampleRate input sample rate.
 * @param outputSampleRate output sample rate.
 * @retval kStatus_Success, else configure failed.
 */
static status_t ASRC_GetPrefiterConfig(asrc_context_prefilter_config_t *config,
                                       uint32_t inputSampleRate,
                                       uint32_t outputSampleRate);

/*!
 * @brief ASRC load resample configuration.
 *
 * @param config resamplefilter pointer.
 * @param interpolationTap resampler taps
 * @retval kStatus_Success, else configure failed.
 */
static status_t ASRC_GetResamplerConfig(asrc_context_resampler_config_t *config,
                                        asrc_resampler_taps_t interpolationTap);

/*!
 * @brief ASRC reset prefilter coeff memory pointer reset.
 *
 * @param base ASRC base address.
 * @param context context number.
 */
static void ASRC_SetPrefilterCoeffMemReset(ASRC_Type *base, asrc_context_t context);

/*!
 * @brief ASRC set prefilter configuration.
 *
 * @param base ASRC base address.
 * @param context context number.
 * @param config prefilter configuration.
 * @param filter fliter configuration load from firmware.
 * @retval kStatus_Success, else configure failed.
 */
static status_t ASRC_SetPrefilterConfig(ASRC_Type *base,
                                        asrc_context_t context,
                                        asrc_context_prefilter_config_t *config);

/*!
 * @brief ASRC set resampler configuration.
 *
 * @param base ASRC base address.
 * @param context context number.
 * @param config resampler configuration.
 * @param filter fliter configuration load from firmware.
 * @retval kStatus_Success, else configure failed.
 */
static status_t ASRC_SetResamplerConfig(ASRC_Type *base,
                                        asrc_context_t context,
                                        asrc_context_resampler_config_t *config);

/*!
 * @brief ASRC set slot config.
 *
 * @param base ASRC base address.
 * @param context context number.
 * @param requestChannel request channel number need to run on this slot.
 * @param filter fliter configuration load from firmware.
 * @retval kStatus_Success, else configure failed.
 */
static status_t ASRC_SetSlotConfig(ASRC_Type *base,
                                   asrc_context_t context,
                                   uint32_t requestChannel,
                                   asrc_context_prefilter_config_t *config);

/*!
 * @brief ASRC set context processor config.
 *
 * @param base ASRC base address.
 * @param context context number.
 * @param config context configuration.
 * @retval kStatus_Success, else configure failed.
 */
static status_t ASRC_SetContextProcessorConfig(ASRC_Type *base, asrc_context_t context, asrc_context_config_t *config);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Base pointer array */
static ASRC_Type *const s_asrcBases[] = ASRC_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/* Clock name array */
static const clock_ip_name_t s_asrcClock[] = ASRC_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
/*! @brief ASRC filter firmware table */
static const uint32_t s_asrcFirmware[] = ASRC_FILTER_FIRMWARE;
/*******************************************************************************
 * Code
 ******************************************************************************/
uint32_t ASRC_GetInstance(ASRC_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_asrcBases); instance++)
    {
        if (s_asrcBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_asrcBases));

    return instance;
}

static uint32_t ASRC_GetSampleRateGCD(uint32_t inputSampleRate, uint32_t outputSampleRate)
{
    uint32_t temp = 0U, gcd = inputSampleRate;

    while (outputSampleRate != 0U)
    {
        temp             = outputSampleRate;
        outputSampleRate = gcd % outputSampleRate;
        gcd              = temp;
    }

    return gcd;
}

static void ASRC_GetAvalibleContextSlot(ASRC_Type *base,
                                        uint32_t contextProcessor,
                                        uint32_t *slot0UsedChannel,
                                        uint32_t *slot1UsedChannel)
{
    uint32_t contextIndex = 0U;

    /* looking for avalible context processor */
    if (ASRC_IS_SLOT0_ENABLED(contextProcessor))
    {
        contextIndex = ASRC_GET_SLOT0_CONTEXT_INDEX(contextProcessor);
        if (ASRC_IS_CONTEXT_ENABLED(contextIndex))
        {
            *slot0UsedChannel = ASRC_GET_SLOT0_CHANNEL_NUMBER(contextProcessor);
        }
    }

    if (ASRC_IS_SLOT1_ENABLED(contextProcessor))
    {
        contextIndex = ASRC_GET_SLOT1_CONTEXT_INDEX(contextProcessor);
        if (ASRC_IS_CONTEXT_ENABLED(contextIndex))
        {
            *slot1UsedChannel = ASRC_GET_SLOT1_CHANNEL_NUMBER(contextProcessor);
        }
    }
}

static void ASRC_EnableContextSlot(ASRC_Type *base,
                                   uint32_t contextProcessor,
                                   uint32_t slot,
                                   uint32_t channelNums,
                                   uint32_t startChannel,
                                   asrc_context_t runingContext)
{
    assert(channelNums <= ASRC_SUPPORT_MAXIMUM_CHANNEL_NUMBER);

    if (slot == 0U)
    {
        base->PROC_CTRL_SLOT0_R0[contextProcessor] =
            ASRC_PROC_CTRL_SLOT0_R0_SLOT0_EN_MASK | ASRC_PROC_CTRL_SLOT0_R0_SLOT0_CTX_NUM(runingContext) |
            ASRC_PROC_CTRL_SLOT0_R0_SLOT0_NUM_CH(channelNums - 1U) |
            ASRC_PROC_CTRL_SLOT0_R0_SLOT0_MIN_CH(startChannel) |
            ASRC_PROC_CTRL_SLOT0_R0_SLOT0_MAX_CH(startChannel + channelNums - 1U);
    }
    else
    {
        base->PROC_CTRL_SLOT1_R0[contextProcessor] =
            ASRC_PROC_CTRL_SLOT1_R0_SLOT1_EN_MASK | ASRC_PROC_CTRL_SLOT1_R0_SLOT1_CTX_NUM(runingContext) |
            ASRC_PROC_CTRL_SLOT1_R0_SLOT1_NUM_CH(channelNums - 1U) |
            ASRC_PROC_CTRL_SLOT1_R0_SLOT1_MIN_CH(startChannel) |
            ASRC_PROC_CTRL_SLOT1_R0_SLOT1_MAX_CH(startChannel + channelNums - 1U);
    }
}

static status_t ASRC_SetSampleRateRatioConfig(ASRC_Type *base,
                                              asrc_context_t context,
                                              uint32_t inputSampleRate,
                                              uint32_t outputSampleRate,
                                              asrc_samplerate_ratio_format_t format)
{
    uint64_t ratio    = 0U;
    uint32_t fracBits = 0U;

    uint32_t gcd     = ASRC_GetSampleRateGCD(inputSampleRate, outputSampleRate);
    uint32_t inRate  = inputSampleRate / gcd;
    uint32_t outRate = outputSampleRate / gcd;

    if (format == kASRC_SampleRateRatio5Int39Frac)
    {
        fracBits = 39U;
    }
    else if (format == kASRC_SampleRateRatio6Int38Frac)
    {
        fracBits = 38U;
    }
    else
    {
        fracBits = 37U;
    }

    ratio = ((uint64_t)inRate << fracBits) / outRate;

    base->RS_RATIO_LOW[context].RS_RATIO_LOW  = (uint32_t)ratio & 0xFFFFFFFFU;
    base->RS_RATIO_LOW[context].RS_RATIO_HIGH = ((uint32_t)(ratio >> 32U)) & 0xFFFFFFFFU;

    return kStatus_Success;
}

static status_t ASRC_GetPrefiterConfig(asrc_context_prefilter_config_t *config,
                                       uint32_t inputSampleRate,
                                       uint32_t outputSampleRate)
{
    assert(config != NULL);

    uint32_t gcd           = ASRC_GetSampleRateGCD(inputSampleRate, outputSampleRate);
    uint32_t inSampleRate  = inputSampleRate / gcd;
    uint32_t outSampleRate = outputSampleRate / gcd;
    uint32_t i = 0U, offset = 0U;
    const uint32_t *firmware = s_asrcFirmware;

    /* while performing a up-conversion, the prefilter should be bypassed */
    if (inputSampleRate <= outputSampleRate)
    {
        return kStatus_Success;
    }

    offset = (ASRC_FILTER_INTERPOLATION_FIRMWARE_LEN + 5U) * ASRC_FILTER_INTERPOLATION_FILTER_NUM;

    /* load interpolation filter */
    for (i = 0U; i < ASRC_FILTER_PREFILTER_FILTER_NUM; i++)
    {
        if (firmware[offset] != ASRC_FILTER_FIRMWARE_HEAD)
        {
            return kStatus_InvalidArgument;
        }

        if ((firmware[offset + ASRC_FILTER_PREFILTER_IN_SAMPLE_RATE_INDEX] == inSampleRate) &&
            ((firmware[offset + ASRC_FILTER_PREFILTER_OUT_SAMPLE_RATE_INDEX] == outSampleRate)))
        {
            config->filterSt1Taps      = firmware[offset + ASRC_FILTER_PREFILTER_STAGE_1_TAPS_INDEX];
            config->filterSt2Taps      = firmware[offset + ASRC_FILTER_PREFILTER_STAGE_2_TAPS_INDEX];
            config->filterSt1Exp       = firmware[offset + ASRC_FILTER_PREFILTER_STAGE_1_EXPANSION_FACTOR_INDEX];
            config->filterCoeffAddress = &firmware[offset + ASRC_FILTER_PREFILTER_STAGE_1_DATA_INDEX];
            break;
        }
        offset += ASRC_FILTER_PREFILTER_FIRMWARE_LEN + ASRC_FILTER_PREFILTER_STAGE_1_DATA_INDEX;
    }

    /* check if the interpolation filter firmware is founded */
    if (config->filterCoeffAddress == NULL)
    {
        return kStatus_InvalidArgument;
    }

    return kStatus_Success;
}

static status_t ASRC_GetResamplerConfig(asrc_context_resampler_config_t *config, asrc_resampler_taps_t interpolationTap)
{
    assert(config != NULL);

    uint32_t i = 0U, offset = 0U;
    const uint32_t *firmware = s_asrcFirmware;

    /* load prefilter firmware */
    for (i = 0U; i < ASRC_FILTER_INTERPOLATION_FILTER_NUM; i++)
    {
        if (firmware[offset] != ASRC_FILTER_FIRMWARE_HEAD)
        {
            return kStatus_InvalidArgument;
        }

        if (firmware[offset + ASRC_FILTER_INTERPOLATION_TAP_INDEX] == ((uint32_t)interpolationTap + 1U))
        {
            config->filterPhases = firmware[offset + ASRC_FILTER_INTERPOLATION_PHASE_INDEX];
            config->filterCenterTap =
                ((uint64_t)firmware[offset + 1U + ASRC_FILTER_INTERPOLATION_CENTER_TAP_INDEX] << 32U) +
                firmware[offset + ASRC_FILTER_INTERPOLATION_CENTER_TAP_INDEX];
            config->filterCoeffAddress = &firmware[offset + +1U + ASRC_FILTER_INTERPOLATION_DATA_INDEX];
            break;
        }
        offset += ASRC_FILTER_INTERPOLATION_FIRMWARE_LEN + ASRC_FILTER_INTERPOLATION_DATA_INDEX + 1U;
    }

    /* check if the interpolation filter firmware is founded */
    if (config->filterCoeffAddress == NULL)
    {
        return kStatus_InvalidArgument;
    }

    return kStatus_Success;
}

static void ASRC_SetPrefilterCoeffMemReset(ASRC_Type *base, asrc_context_t context)
{
    base->CTX_CTRL_EXT1[context] &= ~ASRC_CTX_CTRL_EXT1_PF_COEFF_MEM_RST_MASK;
    base->CTX_CTRL_EXT1[context] |= ASRC_CTX_CTRL_EXT1_PF_COEFF_MEM_RST_MASK;
    base->CTX_CTRL_EXT1[context] &= ~ASRC_CTX_CTRL_EXT1_PF_COEFF_MEM_RST_MASK;
}

static status_t ASRC_SetPrefilterConfig(ASRC_Type *base,
                                        asrc_context_t context,
                                        asrc_context_prefilter_config_t *config)
{
    uint32_t contextReg          = base->CTX_CTRL_EXT1[context];
    const uint32_t *coeffPointer = config->filterCoeffAddress;
    uint32_t i = 0U, j = 0U;

    if (coeffPointer == NULL)
    {
        return kStatus_InvalidArgument;
    }

    contextReg &= ~(ASRC_CTX_CTRL_EXT1_PF_INIT_MODE_MASK | ASRC_CTX_CTRL_EXT1_PF_STOP_MODE_MASK |
                    ASRC_CTX_CTRL_EXT1_PF_EXPANSION_FACTOR_MASK | ASRC_CTX_CTRL_EXT1_PF_ST1_WB_FLOAT_MASK |
                    ASRC_CTX_CTRL_EXT1_PF_TWO_STAGE_EN_MASK);

    contextReg |= ASRC_CTX_CTRL_EXT1_PF_INIT_MODE(config->initMode) |
                  ASRC_CTX_CTRL_EXT1_PF_STOP_MODE(config->stopMode) |
                  ASRC_CTX_CTRL_EXT1_PF_EXPANSION_FACTOR(config->filterSt1Exp - 1U) |
                  ASRC_CTX_CTRL_EXT1_PF_ST1_WB_FLOAT(config->stage1Result) |
                  ASRC_CTX_CTRL_EXT1_PF_TWO_STAGE_EN(config->filterSt2Taps != 0U ? 1U : 0U);

    base->CTX_CTRL_EXT1[context] = contextReg;
    base->CTX_CTRL_EXT2[context] = ASRC_CTX_CTRL_EXT2_ST1_NUM_TAPS(config->filterSt1Taps - 1U) |
                                   ASRC_CTX_CTRL_EXT2_ST2_NUM_TAPS(config->filterSt2Taps - 1U);

    /* reset prefilter coefficient memory */
    ASRC_SetPrefilterCoeffMemReset(base, context);
    /* load stage1 */
    for (i = 0; i < ((config->filterSt1Taps + 1U) / 2U) * 2U; i++)
    {
        base->PRE_COEFF_FIFO[context] = coeffPointer[i];
    }

    /* reset prefilter coefficient memory */
    ASRC_SetPrefilterCoeffMemReset(base, context);
    /* load stage2 */
    if (config->filterSt2Taps != 0U)
    {
        base->CTX_CTRL_EXT1[context] |= ASRC_CTX_CTRL_EXT1_PF_COEFF_STAGE_WR_MASK;
        for (j = 0; j < ((config->filterSt2Taps + 1U) / 2U) * 2U; j++)
        {
            base->PRE_COEFF_FIFO[context] = coeffPointer[i + j];
        }
    }

    return kStatus_Success;
}

static status_t ASRC_SetResamplerConfig(ASRC_Type *base,
                                        asrc_context_t context,
                                        asrc_context_resampler_config_t *config)
{
    uint32_t contextReg          = base->CTX_CTRL_EXT1[context];
    uint32_t i                   = 0U;
    const uint32_t *coeffPointer = config->filterCoeffAddress;

    contextReg &= ~(ASRC_CTX_CTRL_EXT1_RS_INIT_MODE_MASK | ASRC_CTX_CTRL_EXT1_RS_STOP_MODE_MASK);
    contextReg |= ASRC_CTX_CTRL_EXT1_RS_INIT_MODE(config->initMode) | ASRC_CTX_CTRL_EXT1_RS_STOP_MODE(config->stopMode);
    base->CTX_CTRL_EXT1[context] = contextReg;

    /* center tap */
    base->RS_CT_LOW  = (uint32_t)config->filterCenterTap & 0xFFFFFFFFU;
    base->RS_CT_HIGH = (uint32_t)(config->filterCenterTap >> 32U) & 0xFFFFFFFFU;

    /* resampler taps */
    contextReg = base->CTX_RS_COEFF_CTRL;
    contextReg &= ~ASRC_CTX_RS_COEFF_CTRL_NUM_RES_TAPS_MASK;

    if (config->tap == kASRC_ResamplerTaps_32)
    {
        contextReg |= ASRC_CTX_RS_COEFF_CTRL_NUM_RES_TAPS(0);
    }
    else if (config->tap == kASRC_ResamplerTaps_64)
    {
        contextReg |= ASRC_CTX_RS_COEFF_CTRL_NUM_RES_TAPS(1);
    }
    else
    {
        contextReg |= ASRC_CTX_RS_COEFF_CTRL_NUM_RES_TAPS(2);
    }
    base->CTX_RS_COEFF_CTRL = contextReg;

    /* load coefficient */
    /* reset coefficient memory firstly */
    base->CTX_RS_COEFF_CTRL &= ~ASRC_CTX_RS_COEFF_CTRL_RS_COEFF_PTR_RST_MASK;
    base->CTX_RS_COEFF_CTRL |= ASRC_CTX_RS_COEFF_CTRL_RS_COEFF_PTR_RST_MASK;
    base->CTX_RS_COEFF_CTRL &= ~ASRC_CTX_RS_COEFF_CTRL_RS_COEFF_PTR_RST_MASK;

    for (i = 0U; i < ASRC_FILTER_INTERPOLATION_FIRMWARE_LEN; i++)
    {
        base->CTX_RS_COEFF_MEM = coeffPointer[i];
    }

    return kStatus_Success;
}

static status_t ASRC_SetSlotConfig(ASRC_Type *base,
                                   asrc_context_t context,
                                   uint32_t requestChannel,
                                   asrc_context_prefilter_config_t *config)
{
    uint32_t avalibleSlot = 0U, avalibleContext = 0U, avalibleChannel = 0U, startChannel = 0U;
    uint32_t i                = 0U;
    uint32_t slot0UsedChannel = 0U, slot1UsedChannel = 0U;
    uint32_t stage1MemSize = 0U, stage1MemAddr = 0U, stage2MemSize = 0U, stage2MemAddr = 0U, stage1Exp = 0U;
    uint32_t leftChannel = requestChannel;

    for (i = 0U; i < ASRC_SUPPORT_MAXIMUM_CONTEXT_PROCESSOR_NUMBER; i++)
    {
        /* record start channel */
        startChannel += avalibleChannel;

        ASRC_GetAvalibleContextSlot(base, i, &slot0UsedChannel, &slot1UsedChannel);

        /* context is busy */
        if ((slot0UsedChannel != 0U) && ((slot1UsedChannel != 0U)))
        {
            continue;
        }
        /* context is idle */
        if ((slot0UsedChannel == 0U) && (slot1UsedChannel == 0U))
        {
            avalibleSlot    = 0U;
            avalibleChannel = ASRC_SUPPORT_MAXIMUM_CHANNEL_NUMBER;
            avalibleContext = i;
        }
        /* context slot 0 is busy, slot 1 is idle */
        else if (slot0UsedChannel != 0U)
        {
            avalibleSlot    = 1U;
            avalibleChannel = ASRC_SUPPORT_MAXIMUM_CHANNEL_NUMBER - slot0UsedChannel;
            avalibleContext = i;
        }
        /* context slot0 is idle, slot 1 is busy, ((slot0UsedChannel == 0U) && (slot1UsedChannel != 0U))*/
        else
        {
            avalibleSlot    = 0U;
            avalibleChannel = ASRC_SUPPORT_MAXIMUM_CHANNEL_NUMBER - slot1UsedChannel;
            avalibleContext = i;
        }

        avalibleChannel = avalibleChannel > leftChannel ? leftChannel : avalibleChannel;
        leftChannel -= avalibleChannel;
        /* enable the avalible slot */
        ASRC_EnableContextSlot(base, avalibleContext, avalibleSlot, avalibleChannel, startChannel, context);

        if (avalibleSlot == 0U)
        {
            if (config->filterSt2Taps != 0U)
            {
                stage1Exp     = (config->filterSt1Exp - 1U) * avalibleChannel;
                stage1MemSize = (config->filterSt1Taps - 1U) * config->filterSt1Exp * avalibleChannel + avalibleChannel;
                stage1MemAddr = 0U;
                stage2MemSize = avalibleChannel * config->filterSt2Taps;
                stage2MemAddr = stage1MemSize;
            }
            else
            {
                stage1MemSize = avalibleChannel * config->filterSt1Taps;
                stage1MemAddr = 0U;
            }

            base->PROC_CTRL_SLOT0_R1[avalibleContext] = stage1Exp;
            base->PROC_CTRL_SLOT0_R2[avalibleContext] = ASRC_PROC_CTRL_SLOT0_R2_SLOT0_ST1_ST_ADDR(stage1MemAddr) |
                                                        ASRC_PROC_CTRL_SLOT0_R2_SLOT0_ST1_MEM_ALLOC(stage1MemSize);
            base->PROC_CTRL_SLOT0_R3[avalibleContext] = ASRC_PROC_CTRL_SLOT0_R3_SLOT0_ST2_ST_ADDR(stage2MemAddr) |
                                                        ASRC_PROC_CTRL_SLOT0_R3_SLOT0_ST2_MEM_ALLOC(stage2MemSize);
        }
        else
        {
            if (config->filterSt2Taps != 0U)
            {
                stage1Exp     = (config->filterSt1Exp - 1U) * avalibleChannel;
                stage1MemSize = (config->filterSt1Taps - 1U) * config->filterSt1Exp * avalibleChannel + avalibleChannel;
                stage1MemAddr = 0x1800U - stage1MemSize;
                stage2MemSize = avalibleChannel * config->filterSt2Taps;
                stage2MemAddr = 0x1800U - stage1MemSize - stage2MemSize;
            }
            else
            {
                stage1MemSize = avalibleChannel * config->filterSt1Taps;
                stage1MemAddr = 0x1800U - stage1MemSize;
            }

            base->PROC_CTRL_SLOT1_R1[avalibleContext] = stage1Exp;
            base->PROC_CTRL_SLOT1_R2[avalibleContext] = ASRC_PROC_CTRL_SLOT1_R2_SLOT1_ST1_ST_ADDR(stage1MemAddr) |
                                                        ASRC_PROC_CTRL_SLOT1_R2_SLOT1_ST1_MEM_ALLOC(stage1MemSize);
            base->PROC_CTRL_SLOT1_R3[avalibleContext] = ASRC_PROC_CTRL_SLOT1_R3_SLOT1_ST2_ST_ADDR(stage2MemAddr) |
                                                        ASRC_PROC_CTRL_SLOT1_R3_SLOT1_ST2_MEM_ALLOC(stage2MemSize);
        }

        /* one context processor can satisfy the channel requirement*/
        if (leftChannel == 0U)
        {
            return kStatus_Success;
        }
        /* multiple slot across context processor is required */
        else
        {
            continue;
        }
    }

    return kStatus_Fail;
}

static status_t ASRC_SetContextProcessorConfig(ASRC_Type *base, asrc_context_t context, asrc_context_config_t *config)
{
    assert(config != NULL);

    /* bypass resampler */
    if (config->contextInput.sampleRate == config->contextOutput.sampleRate)
    {
        ASRC_EnableResamplerBypass(base, context, true);
    }
    else
    {
        /* ensure resampler is not bypassed */
        ASRC_EnableResamplerBypass(base, context, false);

        if (config->contextResampler.filterCoeffAddress == NULL)
        {
            if (ASRC_GetResamplerConfig(&config->contextResampler, config->contextResampler.tap) != kStatus_Success)
            {
                return kStatus_InvalidArgument;
            }
        }
        /* resampler configuration */
        if (ASRC_SetResamplerConfig(base, context, &config->contextResampler) != kStatus_Success)
        {
            return kStatus_ASRCResamplerConfigureFailed;
        }
    }

    /* up conversion should bypass the prefilter */
    if (config->contextInput.sampleRate <= config->contextOutput.sampleRate)
    {
        /* prefilter bypass mode */
        ASRC_EnablePreFilterBypass(base, context, true);
    }
    else
    {
        /* ensure prefilter not in bypass mode */
        ASRC_EnablePreFilterBypass(base, context, false);
        /* load default configuration if not assigned by application */
        if (config->contextPrefilter.filterCoeffAddress == NULL)
        {
            if (ASRC_GetPrefiterConfig(&config->contextPrefilter, config->contextInput.sampleRate,
                                       config->contextOutput.sampleRate) == kStatus_InvalidArgument)
            {
                return kStatus_InvalidArgument;
            }
        }
        if (ASRC_SetPrefilterConfig(base, context, &config->contextPrefilter) != kStatus_Success)
        {
            return kStatus_ASRCPrefilterConfigureFailed;
        }
    }

    /* set channel number in context */
    ASRC_SetContextChannelNumber(base, context, config->contextChannelNums);

    return ASRC_SetSlotConfig(base, context, config->contextChannelNums, &config->contextPrefilter);
}

/*!
 * brief Initializes the asrc peripheral.
 *
 * This API gates the asrc clock. The asrc module can't operate unless ASRC_Init is called to enable the clock.
 *
 * param base asrc base pointer.
 */
void ASRC_Init(ASRC_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the asrc clock */
    CLOCK_EnableClock(s_asrcClock[ASRC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* disable ASRC module */
    base->CTX_CTRL[0U] = 0U;
    base->CTX_CTRL[1U] = 0U;
    base->CTX_CTRL[2U] = 0U;
    base->CTX_CTRL[3U] = 0U;

    base->CTX_OUT_CTRL[0U] = 0U;
    base->CTX_OUT_CTRL[1U] = 0U;
    base->CTX_OUT_CTRL[2U] = 0U;
    base->CTX_OUT_CTRL[3U] = 0U;

    /* disable all the interrupt */
    base->IRQ_CTRL  = 0U;
    base->IRQ_FLAGS = 0xFFFU;
}

/*!
 * brief De-initializes the ASRC peripheral.
 *
 * This API gates the ASRC clock and disable ASRC module. The ASRC module can't operate unless ASRC_Init
 *
 * param base ASRC base pointer.
 */
void ASRC_Deinit(ASRC_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_DisableClock(s_asrcClock[ASRC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief ASRC configure context input.
 *
 * param base ASRC base pointer.
 * param context index of asrc context, reference asrc_context_t.
 * param config ASRC context input configuration pointer.
 */
status_t ASRC_SetContextInputConfig(ASRC_Type *base, asrc_context_t context, asrc_context_input_config_t *config)
{
    assert(config != NULL);

    uint32_t contextReg = base->CTX_CTRL[context];

    contextReg &= ~(ASRC_CTX_CTRL_SIGN_IN_MASK | ASRC_CTX_CTRL_FLOAT_FMT_MASK | ASRC_CTX_CTRL_BITS_PER_SAMPLE_MASK |
                    ASRC_CTX_CTRL_BIT_REV_MASK | ASRC_CTX_CTRL_SAMPLE_POSITION_MASK | ASRC_CTX_CTRL_FIFO_WTMK_MASK);

    contextReg |= ASRC_CTX_CTRL_FIFO_WTMK(config->watermark);

    contextReg |= ASRC_CTX_CTRL_SIGN_IN(config->dataFormat.dataSign) |
                  ASRC_CTX_CTRL_FLOAT_FMT(config->dataFormat.dataType) |
                  ASRC_CTX_CTRL_BITS_PER_SAMPLE(config->dataFormat.dataWidth) |
                  ASRC_CTX_CTRL_BIT_REV(config->dataFormat.dataEndianness) |
                  ASRC_CTX_CTRL_SAMPLE_POSITION(config->dataFormat.dataPosition);

    base->CTX_CTRL[context] = contextReg;

    base->CTRL_IN_ACCESS[context] = ASRC_CTRL_IN_ACCESS_ACCESS_LENGTH(config->accessCtrl.accessLen) |
                                    ASRC_CTRL_IN_ACCESS_ITERATIONS(config->accessCtrl.accessIterations) |
                                    ASRC_CTRL_IN_ACCESS_GROUP_LENGTH(config->accessCtrl.accessGroupLen);

    return kStatus_Success;
}

/*!
 * brief ASRC configure context output.
 *
 * param base ASRC base pointer.
 * param context index of asrc context, reference asrc_context_t.
 * param config ASRC context output configuration pointer.
 */
status_t ASRC_SetContextOutputConfig(ASRC_Type *base, asrc_context_t context, asrc_context_output_config_t *config)
{
    assert(config != NULL);

    uint32_t contextReg     = base->CTX_OUT_CTRL[context];
    uint32_t samplePosition = config->dataFormat.dataPosition;

    contextReg &=
        ~(ASRC_CTX_OUT_CTRL_SIGN_OUT_MASK | ASRC_CTX_OUT_CTRL_FLOAT_FMT_MASK | ASRC_CTX_OUT_CTRL_IEC_V_DATA_MASK |
          ASRC_CTX_OUT_CTRL_DITHER_EN_MASK | ASRC_CTX_OUT_CTRL_BITS_PER_SAMPLE_MASK | ASRC_CTX_OUT_CTRL_BIT_REV_MASK |
          ASRC_CTX_OUT_CTRL_SAMPLE_POSITION_MASK | ASRC_CTX_OUT_CTRL_FIFO_WTMK_MASK);

    contextReg |= ASRC_CTX_OUT_CTRL_FIFO_WTMK(config->watermark);

    if (config->enableIEC60958)
    {
        if (config->dataFormat.dataWidth == kASRC_DataWidth16Bit)
        {
            samplePosition = 12U;
        }
        else if (config->dataFormat.dataWidth == kASRC_DataWidth24Bit)
        {
            samplePosition = 8U;
        }
        else if (config->dataFormat.dataWidth == kASRC_DataWidth32Bit)
        {
            samplePosition = 4U;
        }
        else
        {
            return kStatus_InvalidArgument;
        }

        contextReg |= ASRC_CTX_OUT_CTRL_IEC_V_DATA_MASK;
    }

    contextReg |= ASRC_CTX_OUT_CTRL_DITHER_EN(config->enableDither);

    contextReg |= ASRC_CTX_OUT_CTRL_SIGN_OUT(config->dataFormat.dataSign) |
                  ASRC_CTX_OUT_CTRL_FLOAT_FMT(config->dataFormat.dataType) |
                  ASRC_CTX_OUT_CTRL_BITS_PER_SAMPLE(config->dataFormat.dataWidth) |
                  ASRC_CTX_OUT_CTRL_BIT_REV(config->dataFormat.dataEndianness) |
                  ASRC_CTX_OUT_CTRL_SAMPLE_POSITION(samplePosition);

    base->CTX_OUT_CTRL[context] = contextReg;

    base->CTRL_OUT_ACCESS[context] = ASRC_CTRL_OUT_ACCESS_ACCESS_LENGTH(config->accessCtrl.accessLen) |
                                     ASRC_CTRL_OUT_ACCESS_ITERATIONS(config->accessCtrl.accessIterations) |
                                     ASRC_CTRL_OUT_ACCESS_GROUP_LENGTH(config->accessCtrl.accessGroupLen);

    return kStatus_Success;
}

/*!
 * brief ASRC get context default configuration.
 *
 * param config ASRC context configuration pointer.
 * param channels input audio data channel numbers.
 * param inSampleRate input sample rate.
 * param outSampleRate output sample rate.
 */
void ASRC_GetContextDefaultConfig(asrc_context_config_t *config,
                                  uint32_t channels,
                                  uint32_t inSampleRate,
                                  uint32_t outSampleRate)
{
    assert(config != NULL);

    (void)memset(config, 0, sizeof(asrc_context_config_t));

    config->contextChannelNums = (uint8_t)channels;

    /* input configuration */
    config->contextInput.sampleRate                  = inSampleRate;
    config->contextInput.watermark                   = FSL_ASRC_INPUT_FIFO_DEPTH / 2U;
    config->contextInput.accessCtrl.accessIterations = 1;
    config->contextInput.accessCtrl.accessGroupLen   = 2;
    config->contextInput.accessCtrl.accessLen        = 2;
    config->contextInput.dataFormat.dataPosition     = 0U;
    config->contextInput.dataFormat.dataEndianness   = kASRC_DataEndianLittle;
    config->contextInput.dataFormat.dataWidth        = kASRC_DataWidth16Bit;
    config->contextInput.dataFormat.dataType         = kASRC_DataTypeInteger;
    config->contextInput.dataFormat.dataSign         = kASRC_DataSigned;
    /* output configuration */
    config->contextOutput.sampleRate                  = outSampleRate;
    config->contextOutput.watermark                   = FSL_ASRC_OUTPUT_FIFO_DEPTH / 8U;
    config->contextOutput.accessCtrl.accessIterations = 1;
    config->contextOutput.accessCtrl.accessGroupLen   = 2;
    config->contextOutput.accessCtrl.accessLen        = 2;
    config->contextOutput.dataFormat.dataPosition     = 0;
    config->contextOutput.dataFormat.dataEndianness   = kASRC_DataEndianLittle;
    config->contextOutput.dataFormat.dataWidth        = kASRC_DataWidth16Bit;
    config->contextOutput.dataFormat.dataType         = kASRC_DataTypeInteger;
    config->contextOutput.dataFormat.dataSign         = kASRC_DataSigned;
    config->contextOutput.enableDither                = false;
    config->contextOutput.enableIEC60958              = false;
    /* prefilter configuration */
    config->contextPrefilter.initMode     = kASRC_SampleBufferFillZeroOnInit;
    config->contextPrefilter.stopMode     = kASRC_SampleBufferFillLastSampleOnStop;
    config->contextPrefilter.stage1Result = kASRC_PrefilterStage1ResultInt;
    /* resampler configuration */
    config->contextResampler.initMode = kASRC_SampleBufferFillZeroOnInit;
    config->contextResampler.stopMode = kASRC_SampleBufferFillLastSampleOnStop;
    config->contextResampler.tap      = kASRC_ResamplerTaps_32;
}

/*!
 * brief ASRC configure context.
 *
 * param base ASRC base pointer.
 * param context index of asrc context, reference asrc_context_t.
 * param config ASRC context configuration pointer.
 * retval kStatus_InvalidArgument invalid parameters.
 *        kStatus_ASRCConfigureFailed context configure failed.
 *        kStatus_Success context configure success.
 */
status_t ASRC_SetContextConfig(ASRC_Type *base, asrc_context_t context, asrc_context_config_t *config)
{
    assert(config != NULL);

    if (config->contextChannelNums > ASRC_SUPPORT_MAXIMUM_CHANNEL_NUMBER)
    {
        return kStatus_InvalidArgument;
    }

    if (((config->contextInput.sampleRate < (uint32_t)kASRC_SampleRate_8000) ||
         (config->contextInput.sampleRate > (uint32_t)kASRC_SampleRate_768000)) ||
        ((config->contextOutput.sampleRate < (uint32_t)kASRC_SampleRate_8000) ||
         (config->contextOutput.sampleRate > (uint32_t)kASRC_SampleRate_768000)))
    {
        return kStatus_InvalidArgument;
    }

    /* sampel ratio configure */
    if (ASRC_SetSampleRateRatioConfig(base, context, config->contextInput.sampleRate, config->contextOutput.sampleRate,
                                      (asrc_samplerate_ratio_format_t)config->contextResampler.tap) != kStatus_Success)
    {
        return kStatus_ASRCConfigureFailed;
    }

    /* configure context input */
    if (ASRC_SetContextInputConfig(base, context, &config->contextInput) != kStatus_Success)
    {
        return kStatus_ASRCConfigureFailed;
    }

    /* allocate context processor */
    if (ASRC_SetContextProcessorConfig(base, context, config) != kStatus_Success)
    {
        return kStatus_ASRCConfigureFailed;
    }

    /* configure context output */
    if (ASRC_SetContextOutputConfig(base, context, &config->contextOutput) != kStatus_Success)
    {
        return kStatus_ASRCConfigureFailed;
    }

    return kStatus_Success;
}

/*!
 * brief ASRC get output sample count.
 *
 * param inSampleRate output sample rate.
 * param inSamplesSize input sample rate.
 * param inWidth input samples buffer size, the size of buffer should be converted to align with 4 byte .
 * param outSampleRate input sample width.
 * param outWidth Output width.
 * retval output samples size.
 */
uint32_t ASRC_GetContextOutSampleSize(
    uint32_t inSampleRate, uint32_t inSamplesSize, uint32_t inWidth, uint32_t outSampleRate, uint32_t outWidth)
{
    uint32_t reminder = (((uint64_t)inSamplesSize / inWidth) * outSampleRate % inSampleRate) == 0U ? 0U : 1U;
    uint32_t quotient = (uint32_t)(((uint64_t)inSamplesSize / inWidth) * outSampleRate / inSampleRate);

    return (reminder + quotient) * outWidth;
}

/*!
 * brief Get the ASRC read fifo remained samples.
 * Since the DMA request will be triggered only when the sample group in read fifo is bigger then the watermark, so when
 * the data size cannot be divisible by the (watermark + 1), then part of sample will left in read fifo, application
 * should call this api to get the left samples.
 *
 * param base ASRC base pointer.
 * param context context id.
 * param outAddr address to receive remained sample in read fifo.
 * param outWidth output data width.
 * param sampleCount specify the read sample count.
 * retval sample counts actual read from output fifo.
 */
uint32_t ASRC_ReadFIFORemainedSample(
    ASRC_Type *base, asrc_context_t context, uint32_t *outAddr, uint32_t outWidth, uint32_t sampleCount)
{
    uint32_t remainSample = base->SAMPLE_FIFO_STATUS[context] & ASRC_SAMPLE_FIFO_STATUS_NUM_SAMPLE_GROUPS_OUT_MASK;
    uint32_t channel      = (base->CTX_CTRL[context] & ASRC_CTX_CTRL_NUM_CH_EN_MASK) + 1U;
    uint32_t i = 0U, sizeToRead = remainSample * channel;

    if (sizeToRead == 0U)
    {
        return 0U;
    }

    if (sampleCount < sizeToRead)
    {
        sizeToRead = sampleCount;
    }

    for (i = 0U; i < sizeToRead; i++)
    {
        *outAddr = ASRC_ReadContextFifo(base, context);
        outAddr  = (uint32_t *)((size_t)outAddr + outWidth);
    }

    return sizeToRead;
}

/*!
 * brief ASRC blocking convert audio sample rate.
 * This function depends on the configuration of input and output, so it should be called after the
 * ASRC_SetContextConfig. The data format it supports:
 * 1.16bit 16bit per sample in input buffer, input buffer size
 * should be calculate as: samples 2U output buffer size can be calculated by call function
 * ASRC_GetContextOutSampleSize, the parameter outWidth should be 2
 * 2.20bit 24bit per sample in input buffer, input buffer size should be calculate as: samples 3U output buffer size can
 * be calculated by call function ASRC_GetContextOutSampleSize, the outWidth should be 3. 3.24bit 24bit per sample in
 * input buffer, input buffer size should be calculate as: samples * 3U output buffer size can be calculated by call
 * function ASRC_GetContextOutSampleSize, the outWidth should be 3. 4.32bit 32bit per sample in input buffer, input
 * buffer size should be calculate as: samples * 4U output buffer size can be calculated by call function
 * ASRC_GetContextOutSampleSize, the outWidth should be 4.
 *
 * param base ASRC base pointer.
 * param context context id.
 * param xfer .xfer configuration.
 * retval kStatus_Success.
 */
status_t ASRC_TransferBlocking(ASRC_Type *base, asrc_context_t context, asrc_transfer_t *xfer)
{
    assert((xfer->inDataAddr != NULL) && (xfer->outDataAddr != NULL));
    assert(xfer->inDataSize % sizeof(uint32_t) == 0U);

    uint32_t inWatermarkSamples =
        (((base->CTX_CTRL[context] & ASRC_CTX_CTRL_FIFO_WTMK_MASK) >> ASRC_CTX_CTRL_FIFO_WTMK_SHIFT) + 1U) *
        ((base->CTX_CTRL[context] & ASRC_CTX_CTRL_NUM_CH_EN_MASK) + 1U);
    uint32_t outWatermarkSamples =
        (((base->CTX_OUT_CTRL[context] & ASRC_CTX_OUT_CTRL_FIFO_WTMK_MASK) >> ASRC_CTX_OUT_CTRL_FIFO_WTMK_SHIFT) + 1U) *
        ((base->CTX_CTRL[context] & ASRC_CTX_CTRL_NUM_CH_EN_MASK) + 1U);
    uint32_t inWidth =
        ((base->CTX_CTRL[context] & ASRC_CTX_CTRL_BITS_PER_SAMPLE_MASK) >> ASRC_CTX_CTRL_BITS_PER_SAMPLE_SHIFT);
    uint32_t outWidth = ((base->CTX_OUT_CTRL[context] & ASRC_CTX_OUT_CTRL_BITS_PER_SAMPLE_MASK) >>
                         ASRC_CTX_OUT_CTRL_BITS_PER_SAMPLE_SHIFT);
    uint32_t inMask =
        (inWidth == (uint32_t)kASRC_DataWidth32Bit ? 0xFFFFFFFFU :
                                                     inWidth == (uint32_t)kASRC_DataWidth24Bit ?
                                                     0xFFFFFFU :
                                                     inWidth == (uint32_t)kASRC_DataWidth20Bit ? 0xFFFFFU : 0xFFFFU);
    inWidth =
        (inWidth == (uint32_t)kASRC_DataWidth32Bit ?
             4U :
             inWidth == (uint32_t)kASRC_DataWidth24Bit ? 3U : inWidth == (uint32_t)kASRC_DataWidth20Bit ? 3U : 2U);
    outWidth =
        (outWidth == (uint32_t)kASRC_DataWidth32Bit ?
             4U :
             outWidth == (uint32_t)kASRC_DataWidth24Bit ? 3U : outWidth == (uint32_t)kASRC_DataWidth20Bit ? 3U : 2U);
    uint32_t inSamples     = xfer->inDataSize / inWidth;
    uint32_t outSamples    = xfer->outDataSize / outWidth;
    uint32_t *writePointer = xfer->inDataAddr;
    uint32_t *readPointer  = xfer->outDataAddr;

    uint32_t writtenSamples = 0U, readSamples = 0U, i = 0U, j = 0U;
    /* enable context run */
    ASRC_EnableContextRun(base, context, true);
    ASRC_EnableContextRunStop(base, context, false);

    while ((inSamples != 0U) || (outSamples != 0U))
    {
        if (inSamples != 0U)
        {
            if (inSamples < inWatermarkSamples)
            {
                writtenSamples = inSamples;
            }
            else
            {
                writtenSamples = inWatermarkSamples;
            }

            if ((ASRC_GetFifoStatus(base, context) & (uint32_t)kASRC_FifoStatusInputFifoWatermarkFlag) != 0U)
            {
                for (i = 0U; i < writtenSamples; i++)
                {
                    ASRC_WriteContextFifo(base, context, *writePointer & inMask);
                    writePointer = (uint32_t *)((size_t)writePointer + inWidth);
                }

                inSamples -= writtenSamples;
            }
        }

        if (outSamples <= outWatermarkSamples)
        {
            readSamples = ASRC_ReadFIFORemainedSample(base, context, readPointer, outWidth, outSamples);
            outSamples -= readSamples;
            continue;
        }
        else
        {
            readSamples = outWatermarkSamples;
        }

        if ((ASRC_GetFifoStatus(base, context) & (uint32_t)kASRC_FifoStatusOutputFifoWatermarkFlag) != 0U)
        {
            for (j = 0U; j < readSamples; j++)
            {
                *readPointer = ASRC_ReadContextFifo(base, context);
                readPointer  = (uint32_t *)((size_t)readPointer + outWidth);
            }
            outSamples -= readSamples;
        }
        else
        {
            /* flush all the samples out */
            if ((inSamples == 0U) && (outSamples > outWatermarkSamples))
            {
                ASRC_EnableContextRunStop(base, context, true);
            }
        }
    }

    /* disable context run */
    ASRC_EnableContextRun(base, context, false);
    ASRC_EnableContextRunStop(base, context, false);

    return kStatus_Success;
}
