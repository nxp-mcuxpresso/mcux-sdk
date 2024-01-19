/*
 * Copyright 2022-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_wm8962.h"

/*******************************************************************************
 * Definitations
 ******************************************************************************/
#define WM8962_CHECK_RET(x, status)  \
    (status) = (x);                  \
    if ((status) != kStatus_Success) \
    {                                \
        return (status);             \
    }
/*! @brief WM8962 max clock */
#define WM8962_MAX_DSP_CLOCK (24576000U)
#define WM8962_MAX_SYS_CLOCK (12288000U)
/*! @brief WM8962 f2 better performance range */
#define WM8962_FLL_VCO_MIN_FREQ 90000000U
#define WM8962_FLL_VCO_MAX_FREQ 100000000U
#define WM8962_FLL_LOCK_TIMEOUT 10000000U
/*! @brief WM8962 FLLN range */
#define WM8962_FLL_N_MIN_VALUE              6U
#define WM8962_FLL_N_MAX_VALUE              12U
#define WM8962_FLL_MAX_REFERENCE_CLOCK      (13500000U)
#define WM8962_SWAP_UINT16_BYTE_SEQUENCE(x) ((((x)&0x00ffU) << 8U) | (((x)&0xff00U) >> 8U))
/*! @brief WM8962 default sequence */
typedef enum _wm8962_sequence_id
{
    kWM8962_SequenceDACToHeadphonePowerUp = 0x80U, /*!< dac to headphone power up sequence */
    kWM8962_SequenceAnalogueInputPowerUp  = 0x92U, /*!< Analogue input power up sequence */
    kWM8962_SequenceChipPowerDown         = 0x9BU, /*!< Chip power down sequence */
    kWM8962_SequenceSpeakerSleep          = 0xE4U, /*!< Speaker sleep sequence */
    kWM8962_SequenceSpeakerWake           = 0xE8U, /*!< speaker wake sequence */
} wm8962_sequence_id_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static status_t WM8962_StartSequence(wm8962_handle_t *handle, wm8962_sequence_id_t id);
/*******************************************************************************
 * Variables
 ******************************************************************************/
/*******************************************************************************
 * Code
 ******************************************************************************/
static status_t WM8962_StartSequence(wm8962_handle_t *handle, wm8962_sequence_id_t id)
{
    uint32_t delayUs      = 93000U;
    uint16_t sequenceStat = 0U;
    status_t ret          = kStatus_Success;

    switch (id)
    {
        case kWM8962_SequenceDACToHeadphonePowerUp:
            delayUs = 93000U;
            break;
        case kWM8962_SequenceAnalogueInputPowerUp:
            delayUs = 75000U;
            break;
        case kWM8962_SequenceChipPowerDown:
            delayUs = 32000U;
            break;
        case kWM8962_SequenceSpeakerSleep:
            delayUs = 2000U;
            break;
        case kWM8962_SequenceSpeakerWake:
            delayUs = 2000U;
            break;
        default:
            delayUs = 93000U;
            break;
    }

    WM8962_CHECK_RET(WM8962_WriteReg(handle, 0x57, 0x20U), ret);
    WM8962_CHECK_RET(WM8962_WriteReg(handle, 0x5A, (uint16_t)id), ret);
    while (delayUs != 0U)
    {
        WM8962_CHECK_RET(WM8962_ReadReg(handle, 0x5D, &sequenceStat), ret);
        if ((sequenceStat & 1U) == 0U)
        {
            break;
        }
        SDK_DelayAtLeastUs(1000U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
        delayUs -= 1000U;
    }

    return (sequenceStat & 1U) == 0U ? kStatus_Success : kStatus_Fail;
}

static uint32_t WM8962_GCD_FLL(uint32_t a, uint32_t b)
{
    uint32_t value = 0U;

    while (b != 0U)
    {
        value = a % b;

        a = b;
        b = value;
    }

    return a;
}

static status_t WM8962_GetClockDivider(uint32_t inputClock, uint32_t maxClock, uint16_t *divider)
{
    if ((inputClock >> 2U) > maxClock)
    {
        return kStatus_InvalidArgument;
    }
    else
    {
        /* fll reference clock divider */
        if (inputClock > maxClock)
        {
            if ((inputClock >> 1U) > maxClock)
            {
                *divider = 2U;
            }
            else
            {
                *divider = 1U;
            }
        }
        else
        {
            *divider = 0U;
        }
    }

    return kStatus_Success;
}

static status_t WM8962_SetInternalFllConfig(wm8962_handle_t *handle, const wm8962_fll_clk_config_t *fllConfig)
{
    assert(fllConfig->fllReferenceClockFreq != 0U);

    status_t ret    = kStatus_Success;
    uint16_t refDiv = 0U, fllLock = 0U;
    uint32_t refClock = fllConfig->fllReferenceClockFreq, fllRatio = 0U, outClk = fllConfig->fllOutputFreq,
             fllOutDiv = 0U, fVCO = 0U;
    uint32_t fllGCD = 0U, fllTheta = 0U, fllLambda = 0U, nDivider = 0U, delayUs = WM8962_FLL_LOCK_TIMEOUT;

    WM8962_CHECK_RET(WM8962_ModifyReg(handle, WM8962_FLL_CTRL_1, 1U, 0U), ret);
    WM8962_CHECK_RET(WM8962_GetClockDivider(fllConfig->fllReferenceClockFreq, WM8962_FLL_MAX_REFERENCE_CLOCK, &refDiv),
                     ret);

    refClock = fllConfig->fllReferenceClockFreq / (uint32_t)(1UL << (refDiv & 3U));

    if (refClock > 1000000U)
    {
        fllRatio = 0U;
    }
    else if (refClock > 256000U)
    {
        fllRatio = 1U;
    }
    else if (refClock > 128000U)
    {
        fllRatio = 2U;
    }
    else if (refClock > 64000U)
    {
        fllRatio = 3U;
    }
    else
    {
        fllRatio = 4U;
    }

    if ((outClk < 2083300U) && ((outClk > 1875000U)))
    {
        fllOutDiv = 0x2FU;
    }
    else if ((outClk < 3125000U) && ((outClk > 2812500U)))
    {
        fllOutDiv = 0x1FU;
    }
    else if ((outClk < 4166700U) && ((outClk > 3750000U)))
    {
        fllOutDiv = 0x17U;
    }
    else if ((outClk < 6250000U) && ((outClk > 5625000U)))
    {
        fllOutDiv = 0xFU;
    }
    else if ((outClk < 12500000U) && ((outClk > 11250000U)))
    {
        fllOutDiv = 7U;
    }
    else if ((outClk < 20000000U) && ((outClk > 18000000U)))
    {
        fllOutDiv = 4U;
    }
    else if ((outClk < 25000000U) && ((outClk > 22500000U)))
    {
        fllOutDiv = 3U;
    }
    else if ((outClk < 50000000U) && ((outClk > 40000000U)))
    {
        fllOutDiv = 1U;
    }
    else
    {
        return kStatus_InvalidArgument;
    }

    fVCO     = (fllOutDiv + 1U) * outClk;
    nDivider = fVCO / ((uint32_t)(1UL << fllRatio) * refClock);

    fllGCD = WM8962_GCD_FLL((uint32_t)(1UL << fllRatio) * refClock, fVCO);

    fllTheta  = (fVCO - nDivider * (uint32_t)(1UL << fllRatio) * refClock) / fllGCD;
    fllLambda = ((uint32_t)(1UL << fllRatio) * refClock) / fllGCD;

    /* FLL configurations */
    WM8962_CHECK_RET(WM8962_ModifyReg(handle, WM8962_FLL_CTRL_2, 0x1FBU, (uint16_t)(refDiv | (fllOutDiv << 3U))), ret);
    WM8962_CHECK_RET(WM8962_ModifyReg(handle, WM8962_FLL_CTRL_3, 7U, (uint16_t)fllRatio), ret);
    WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_FLL_CTRL_6, (uint16_t)fllTheta), ret);
    WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_FLL_CTRL_7, (uint16_t)fllLambda), ret);
    WM8962_CHECK_RET(WM8962_ModifyReg(handle, WM8962_FLL_CTRL_8, 0x3FFU, (uint16_t)nDivider), ret);
    WM8962_CHECK_RET(
        WM8962_ModifyReg(handle, WM8962_FLL_CTRL_1, 0x65U,
                         (uint16_t)((fllConfig->fllClockSource == kWM8962_FLLClkSourceMCLK ? 0x0UL : 0x20UL) | 0x5UL)),
        ret);

    /* Polling FLL lock status */
    while (delayUs != 0U)
    {
        WM8962_CHECK_RET(WM8962_ReadReg(handle, WM8962_INT_STATUS_2, &fllLock), ret);
        if ((fllLock & 0x20U) == 0x20U)
        {
            break;
        }
        SDK_DelayAtLeastUs(1000U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
        delayUs -= 1000U;
    }
    ret = ((fllLock & 0x20U) == 0x20U) ? kStatus_Success : kStatus_Fail;

    return ret;
}

static status_t WM8962_SetMasterClock(wm8962_handle_t *handle,
                                      uint32_t dspClock,
                                      uint32_t sampleRate,
                                      uint32_t bitWidth)
{
    uint32_t bitClockDivider = 0U, regDivider = 0U;
    status_t ret = kStatus_Success;

    bitClockDivider = dspClock / (sampleRate * bitWidth * 2U);

    switch (bitClockDivider)
    {
        case 1:
            regDivider = 0U;
            break;
        case 2:
            regDivider = 2U;
            break;
        case 3:
            regDivider = 3U;
            break;
        case 4:
            regDivider = 4U;
            break;
        case 6:
            regDivider = 6U;
            break;
        case 8:
            regDivider = 7U;
            break;
        case 12:
            regDivider = 9U;
            break;
        case 16:
            regDivider = 10U;
            break;
        case 24:
            regDivider = 11U;
            break;
        case 32:
            regDivider = 13U;
            break;

        default:
            ret = kStatus_InvalidArgument;
            break;
    }
    if (ret == kStatus_Success)
    {
        WM8962_CHECK_RET(WM8962_ModifyReg(handle, WM8962_CLOCK2, WM8962_CLOCK2_BCLK_DIV_MASK, (uint16_t)regDivider),
                         ret);
        WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_IFACE2, (uint16_t)(bitWidth * 2U)), ret);
    }

    return ret;
}

status_t WM8962_Init(wm8962_handle_t *handle, const wm8962_config_t *config)
{
    status_t ret = kStatus_Success;

    handle->config = config;
    uint32_t mclk = config->format.mclk_HZ, sysClk = 0U;
    uint16_t clockDiv = 0U;

    /* i2c bus initialization */
    if (CODEC_I2C_Init(handle->i2cHandle, config->i2cConfig.codecI2CInstance, WM8962_I2C_BAUDRATE,
                       config->i2cConfig.codecI2CSourceClock) != (status_t)kStatus_HAL_I2cSuccess)
    {
        return kStatus_Fail;
    }

    /* Reset the codec */
    WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_RESET, 0x6243U), ret);
    /* disable internal osc/FLL2/FLL3/FLL*/
    WM8962_CHECK_RET(WM8962_WriteReg(handle, 0x81U, 0), ret);
    WM8962_CHECK_RET(WM8962_ModifyReg(handle, WM8962_FLL_CTRL_1, 1U, 0U), ret);
    WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_CLOCK2, 0x9E4), ret);
    WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_POWER1, 0x1FE), ret);
    WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_POWER2, 0x1E0), ret);

    WM8962_CHECK_RET(WM8962_StartSequence(handle, kWM8962_SequenceDACToHeadphonePowerUp), ret);
    WM8962_CHECK_RET(WM8962_StartSequence(handle, kWM8962_SequenceAnalogueInputPowerUp), ret);
    WM8962_CHECK_RET(WM8962_StartSequence(handle, kWM8962_SequenceSpeakerWake), ret);

    /* master clock configuration if it is master */
    if (config->masterSlave && config->sysclkSource == kWM8962_SysClkSourceFLL)
    {
        /* Internal FLL config */
        WM8962_CHECK_RET(WM8962_SetInternalFllConfig(handle, &config->fllClock), ret);
        // WM8962_SetInternalFllConfig(handle, &config->fllClock);
        mclk = config->fllClock.fllOutputFreq;
        /* SYS clock source FLL */
        WM8962_CHECK_RET(WM8962_ModifyReg(handle, WM8962_CLOCK2, 0x20U, 0U), ret);
        WM8962_CHECK_RET(
            WM8962_ModifyReg(handle, WM8962_CLOCK2, (uint16_t)((3U << 9U) | 0x20U), (uint16_t)((1U << 9U) | 0x20U)),
            ret);
    }

    /* DSP clock divider, maximum 24.576MHZ */
    WM8962_CHECK_RET(WM8962_GetClockDivider(mclk, WM8962_MAX_DSP_CLOCK, &clockDiv), ret);
    WM8962_CHECK_RET(WM8962_ModifyReg(handle, WM8962_CLOCK1, 3U << 9U, (uint16_t)(clockDiv << 9U)), ret);
    if (config->masterSlave)
    {
        WM8962_CHECK_RET(WM8962_SetMasterClock(handle, mclk / (uint32_t)(1UL << clockDiv), config->format.sampleRate,
                                               config->format.bitWidth),
                         ret);
        WM8962_CHECK_RET(WM8962_ModifyReg(handle, WM8962_IFACE0, 1U << 6U, 1U << 6U), ret);
    }

    /* enable system clock */
    WM8962_CHECK_RET(WM8962_ModifyReg(handle, WM8962_CLOCK2, 0x20U, 0x20U), ret);

    /* sysclk clock divider, maximum 12.288MHZ */
    WM8962_CHECK_RET(WM8962_ReadReg(handle, WM8962_CLOCK1, &clockDiv), ret);
    sysClk = mclk / (1UL << (clockDiv & 3U));

    /* set data route */
    WM8962_CHECK_RET(WM8962_SetDataRoute(handle, &config->route), ret);
    /* set data protocol */
    WM8962_CHECK_RET(WM8962_SetProtocol(handle, config->bus), ret);
    /*
     * ADC volume, 0dB
     */
    WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_LADC, 0x1C0), ret);
    WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_RADC, 0x1C0), ret);
    /*
     * Digital DAC volume, -15.5dB
     */
    WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_LDAC, 0x1C0), ret);
    WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_RDAC, 0x1C0), ret);
    /* speaker volume 6dB */
    WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_LOUT2, 0x1ff), ret);
    WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_ROUT2, 0x1ff), ret);
    /* input PGA volume */
    WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_LINVOL, 0x13F), ret);
    WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_RINVOL, 0x13F), ret);
    /* Headphone volume */
    WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_LOUT1, 0x16B), ret);
    WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_ROUT1, 0x16B), ret);
    WM8962_CHECK_RET(WM8962_ConfigDataFormat(handle, sysClk, config->format.sampleRate, config->format.bitWidth), ret);

    return ret;
}

status_t WM8962_Deinit(wm8962_handle_t *handle)
{
    status_t ret = kStatus_Success;

    /* power down */
    WM8962_CHECK_RET(WM8962_StartSequence(handle, kWM8962_SequenceChipPowerDown), ret);

    return ret;
}

status_t WM8962_SetProtocol(wm8962_handle_t *handle, wm8962_protocol_t protocol)
{
    status_t ret = kStatus_Success;

    if (protocol == kWM8962_BusPCMB)
    {
        WM8962_CHECK_RET(
            WM8962_ModifyReg(handle, WM8962_IFACE0, WM8962_IFACE0_FORMAT_MASK, ((uint16_t)protocol | 0x10U)), ret);
    }
    else if (protocol == kWM8962_BusPCMA)
    {
        WM8962_CHECK_RET(WM8962_ModifyReg(handle, WM8962_IFACE0, WM8962_IFACE0_FORMAT_MASK, ((uint16_t)protocol - 1U)),
                         ret);
    }
    else
    {
        WM8962_CHECK_RET(WM8962_ModifyReg(handle, WM8962_IFACE0, WM8962_IFACE0_FORMAT_MASK, (uint16_t)protocol), ret);
    }

    return ret;
}

status_t WM8962_SetModulePower(wm8962_handle_t *handle, wm8962_module_t module, bool isEnabled)
{
    status_t ret = kStatus_Success;

    switch (module)
    {
        case kWM8962_ModuleADC:
            WM8962_CHECK_RET(WM8962_ModifyReg(handle, WM8962_POWER1, WM8962_POWER1_ADCL_MASK,
                                              ((uint16_t)isEnabled << WM8962_POWER1_ADCL_SHIFT)),
                             ret);
            WM8962_CHECK_RET(WM8962_ModifyReg(handle, WM8962_POWER1, WM8962_POWER1_ADCR_MASK,
                                              ((uint16_t)isEnabled << WM8962_POWER1_ADCR_SHIFT)),
                             ret);
            break;
        case kWM8962_ModuleDAC:
            WM8962_CHECK_RET(WM8962_ModifyReg(handle, WM8962_POWER2, WM8962_POWER2_DACL_MASK,
                                              ((uint16_t)isEnabled << WM8962_POWER2_DACL_SHIFT)),
                             ret);
            WM8962_CHECK_RET(WM8962_ModifyReg(handle, WM8962_POWER2, WM8962_POWER2_DACR_MASK,
                                              ((uint16_t)isEnabled << WM8962_POWER2_DACR_SHIFT)),
                             ret);
            break;
        case kWM8962_ModuleLineIn:
            WM8962_CHECK_RET(WM8962_ModifyReg(handle, WM8962_POWER1, WM8962_POWER1_AINL_MASK,
                                              ((uint16_t)isEnabled << WM8962_POWER1_AINL_SHIFT)),
                             ret);
            WM8962_CHECK_RET(WM8962_ModifyReg(handle, WM8962_POWER1, WM8962_POWER1_AINR_MASK,
                                              ((uint16_t)isEnabled << WM8962_POWER1_AINR_SHIFT)),
                             ret);
            break;
        case kWM8962_ModuleHeadphone:
            WM8962_CHECK_RET(WM8962_ModifyReg(handle, WM8962_POWER2, WM8962_POWER2_LOUT1_MASK,
                                              ((uint16_t)isEnabled << WM8962_POWER2_LOUT1_SHIFT)),
                             ret);
            WM8962_CHECK_RET(WM8962_ModifyReg(handle, WM8962_POWER2, WM8962_POWER2_ROUT1_MASK,
                                              ((uint16_t)isEnabled << WM8962_POWER2_ROUT1_SHIFT)),
                             ret);
            break;
        case kWM8962_ModuleMICB:
            WM8962_CHECK_RET(WM8962_ModifyReg(handle, WM8962_POWER1, WM8962_POWER1_MICB_MASK,
                                              ((uint16_t)isEnabled << WM8962_POWER1_MICB_SHIFT)),
                             ret);
            break;
        case kWM8962_ModuleSpeaker:
            WM8962_CHECK_RET(WM8962_ModifyReg(handle, WM8962_POWER2, WM8962_POWER2_SPKL_MASK,
                                              ((uint16_t)isEnabled << WM8962_POWER2_SPKL_SHIFT)),
                             ret);
            WM8962_CHECK_RET(WM8962_ModifyReg(handle, WM8962_POWER2, WM8962_POWER2_SPKR_MASK,
                                              ((uint16_t)isEnabled << WM8962_POWER2_SPKR_SHIFT)),
                             ret);
            break;
        default:
            ret = kStatus_InvalidArgument;
            break;
    }

    return ret;
}

status_t WM8962_SetDataRoute(wm8962_handle_t *handle, const wm8962_route_config_t *route)
{
    status_t ret = kStatus_Success;

    /* Input PGA source */
    WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_LEFT_INPUT_PGA, (0x10U | (uint16_t)route->leftInputPGASource)),
                     ret);
    WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_RIGHT_INPUT_PGA, (0x10U | (uint16_t)route->rightInputPGASource)),
                     ret);

    /* Input MIXER source */
    WM8962_CHECK_RET(
        WM8962_WriteReg(handle, WM8962_INPUTMIX,
                        (uint16_t)(((route->leftInputMixerSource & 7U) << 3U) | (route->rightInputMixerSource & 7U))),
        ret);

    /* Output MIXER source */

    if (route->leftSpeakerPGASource == kWM8962_OutputPGASourceMixer)
    {
        WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_LEFT_SPEAKER_MIXER, (uint16_t)route->leftSpeakerMixerSource),
                         ret);
    }
    else
    {
        WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_LEFT_SPEAKER_MIXER, 0U), ret);
    }

    if (route->rightSpeakerPGASource == kWM8962_OutputPGASourceMixer)
    {
        WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_RIGHT_SPEAKER_MIXER, (uint16_t)route->rightSpeakerMixerSource),
                         ret);
    }
    else
    {
        WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_RIGHT_SPEAKER_MIXER, 0U), ret);
    }

    if (route->leftHeadphonePGASource == kWM8962_OutputPGASourceMixer)
    {
        WM8962_CHECK_RET(
            WM8962_WriteReg(handle, WM8962_LEFT_HEADPHONE_MIXER, (uint16_t)route->leftHeadphoneMixerSource), ret);
    }
    else
    {
        WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_LEFT_HEADPHONE_MIXER, 0U), ret);
    }

    if (route->rightHeadphonePGASource == kWM8962_OutputPGASourceMixer)
    {
        WM8962_CHECK_RET(
            WM8962_WriteReg(handle, WM8962_RIGHT_HEADPHONE_MIXER, (uint16_t)route->rightHeadphoneMixerSource), ret);
    }
    else
    {
        WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_RIGHT_HEADPHONE_MIXER, 0U), ret);
    }

    WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_INPUT_MIXER_1, 3U), ret);

    return ret;
}

status_t WM8962_SetModuleVolume(wm8962_handle_t *handle, wm8962_module_t module, uint32_t volume)
{
    uint16_t vol = 0;
    status_t ret = kStatus_Success;
    switch (module)
    {
        case kWM8962_ModuleADC:
            if (volume > 255U)
            {
                ret = kStatus_InvalidArgument;
            }
            else
            {
                vol = (uint16_t)volume;
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_LADC, vol), ret);
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_RADC, vol), ret);
                /* Update volume */
                vol = (uint16_t)(0x100U | volume);
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_LADC, vol), ret);
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_RADC, vol), ret);
            }
            break;
        case kWM8962_ModuleDAC:
            if (volume > 255U)
            {
                ret = kStatus_InvalidArgument;
            }
            else
            {
                vol = (uint16_t)volume;
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_LDAC, vol), ret);
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_RDAC, vol), ret);
                vol = 0x100U | (uint16_t)volume;
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_LDAC, vol), ret);
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_RDAC, vol), ret);
            }
            break;
        case kWM8962_ModuleHeadphone:
            if (volume > 0x7FU)
            {
                ret = kStatus_InvalidArgument;
            }
            else
            {
                vol = (uint16_t)volume;
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_LOUT1, vol), ret);
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_ROUT1, vol), ret);
                vol = 0x100U | (uint16_t)volume;
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_LOUT1, vol), ret);
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_ROUT1, vol), ret);
            }
            break;
        case kWM8962_ModuleLineIn:
            if (volume > 0x3FU)
            {
                ret = kStatus_InvalidArgument;
            }
            else
            {
                vol = (uint16_t)volume;
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_LINVOL, vol), ret);
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_RINVOL, vol), ret);
                vol = 0x100U | (uint16_t)volume;
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_LINVOL, vol), ret);
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_RINVOL, vol), ret);
            }
            break;
        case kWM8962_ModuleSpeaker:
            if (volume > 0x7FU)
            {
                ret = kStatus_InvalidArgument;
            }
            else
            {
                vol = (uint16_t)volume;
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_LOUT2, vol), ret);
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_ROUT2, vol), ret);
                vol = 0x100U | (uint16_t)volume;
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_LOUT2, vol), ret);
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_ROUT2, vol), ret);
            }
            break;
        default:
            ret = kStatus_InvalidArgument;
            break;
    }
    return ret;
}

uint32_t WM8962_GetModuleVolume(wm8962_handle_t *handle, wm8962_module_t module)
{
    uint16_t vol = 0;

    switch (module)
    {
        case kWM8962_ModuleADC:
            (void)WM8962_ReadReg(handle, WM8962_LADC, &vol);
            vol &= 0xFFU;
            break;
        case kWM8962_ModuleDAC:
            (void)WM8962_ReadReg(handle, WM8962_LDAC, &vol);
            vol &= 0xFFU;
            break;
        case kWM8962_ModuleHeadphone:
            (void)WM8962_ReadReg(handle, WM8962_LOUT1, &vol);
            vol &= 0x7FU;
            break;
        default:
            vol = 0;
            break;
    }
    return vol;
}

status_t WM8962_SetModuleMute(wm8962_handle_t *handle, wm8962_module_t module, bool isEnabled)
{
    uint16_t vol = 0;
    status_t ret = kStatus_Success;
    switch (module)
    {
        case kWM8962_ModuleADC:
            /*
             * Digital Mute
             */
            if (isEnabled)
            {
                WM8962_CHECK_RET(WM8962_ReadReg(handle, WM8962_LADC, &handle->volume[kWM8962_ModuleADC]), ret);
                WM8962_CHECK_RET(WM8962_ReadReg(handle, WM8962_RADC, &handle->volume[kWM8962_ModuleADC]), ret);
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_LADC, 0x100), ret);
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_RADC, 0x100), ret);
            }
            else
            {
                vol = 0x100U | (uint16_t)handle->volume[kWM8962_ModuleADC];
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_LADC, vol), ret);
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_RADC, vol), ret);
            }
            break;
        case kWM8962_ModuleDAC:
            /*
             * Digital mute
             */
            if (isEnabled)
            {
                WM8962_CHECK_RET(WM8962_ReadReg(handle, WM8962_LDAC, &handle->volume[kWM8962_ModuleDAC]), ret);
                WM8962_CHECK_RET(WM8962_ReadReg(handle, WM8962_RDAC, &handle->volume[kWM8962_ModuleDAC]), ret);
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_LDAC, 0x100), ret);
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_RDAC, 0x100), ret);
            }
            else
            {
                vol = 0x100U | (uint16_t)handle->volume[kWM8962_ModuleDAC];
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_LDAC, vol), ret);
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_RDAC, vol), ret);
            }
            break;
        case kWM8962_ModuleHeadphone:
            /*
             * Analog mute
             */
            if (isEnabled)
            {
                WM8962_CHECK_RET(WM8962_ReadReg(handle, WM8962_LOUT1, &handle->volume[kWM8962_ModuleHeadphone]), ret);
                WM8962_CHECK_RET(WM8962_ReadReg(handle, WM8962_ROUT1, &handle->volume[kWM8962_ModuleHeadphone]), ret);
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_LOUT1, 0x100), ret);
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_ROUT1, 0x100), ret);
            }
            else
            {
                vol = 0x100U | (uint16_t)handle->volume[kWM8962_ModuleHeadphone];
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_LOUT1, vol), ret);
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_ROUT1, vol), ret);
            }
            break;

        case kWM8962_ModuleSpeaker:
            if (isEnabled)
            {
                WM8962_CHECK_RET(WM8962_ReadReg(handle, WM8962_LOUT2, &handle->volume[kWM8962_ModuleSpeaker]), ret);
                WM8962_CHECK_RET(WM8962_ReadReg(handle, WM8962_ROUT2, &handle->volume[kWM8962_ModuleSpeaker]), ret);
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_LOUT2, 0x100), ret);
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_ROUT2, 0x100), ret);
            }
            else
            {
                vol = 0x100U | (uint16_t)handle->volume[kWM8962_ModuleSpeaker];
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_LOUT2, vol), ret);
                WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_ROUT2, vol), ret);
            }
            break;
        default:
            ret = kStatus_InvalidArgument;
            break;
    }
    return ret;
}

status_t WM8962_ConfigDataFormat(wm8962_handle_t *handle, uint32_t sysclk, uint32_t sample_rate, uint32_t bits)
{
    status_t retval = kStatus_Success;
    uint16_t val    = 0;
    uint32_t ratio  = sysclk / sample_rate;

    /*
     * Slave mode (MS = 0), LRP = 0, 32bit WL, left justified (FORMAT[1:0]=0b01)
     */
    switch (bits)
    {
        case 16:
            retval = WM8962_ModifyReg(handle, WM8962_IFACE0, WM8962_IFACE0_WL_MASK,
                                      WM8962_IFACE0_WL(WM8962_IFACE0_WL_16BITS));
            break;
        case 20:
            retval = WM8962_ModifyReg(handle, WM8962_IFACE0, WM8962_IFACE0_WL_MASK,
                                      WM8962_IFACE0_WL(WM8962_IFACE0_WL_20BITS));
            break;
        case 24:
            retval = WM8962_ModifyReg(handle, WM8962_IFACE0, WM8962_IFACE0_WL_MASK,
                                      WM8962_IFACE0_WL(WM8962_IFACE0_WL_24BITS));
            break;
        case 32:
            retval = WM8962_ModifyReg(handle, WM8962_IFACE0, WM8962_IFACE0_WL_MASK,
                                      WM8962_IFACE0_WL(WM8962_IFACE0_WL_32BITS));
            break;
        default:
            retval = kStatus_InvalidArgument;
            break;
    }

    if (kStatus_Success != retval)
    {
        return retval;
    }

    switch (sample_rate)
    {
        case kWM8962_AudioSampleRate8KHz:
            val = 0x15U;
            break;
        case kWM8962_AudioSampleRate11025Hz:
            val = 0x04U;
            break;
        case kWM8962_AudioSampleRate12KHz:
            val = 0x14U;
            break;
        case kWM8962_AudioSampleRate16KHz:
            val = 0x13U;
            break;
        case kWM8962_AudioSampleRate22050Hz:
            val = 0x02U;
            break;
        case kWM8962_AudioSampleRate24KHz:
            val = 0x12U;
            break;
        case kWM8962_AudioSampleRate32KHz:
            val = 0x11U;
            break;
        case kWM8962_AudioSampleRate44100Hz:
            val = 0x00U;
            break;
        case kWM8962_AudioSampleRate48KHz:
            val = 0x10U;
            break;
        case kWM8962_AudioSampleRate88200Hz:
            val = 0x06U;
            break;
        case kWM8962_AudioSampleRate96KHz:
            val = 0x16U;
            break;
        default:
            retval = kStatus_InvalidArgument;
            break;
    }

    if (kStatus_Success != retval)
    {
        return retval;
    }

    WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_ADDCTL3, val), retval);

    switch (ratio)
    {
        case 64:
            val = 0x00U;
            break;
        case 128:
            val = 0x02U;
            break;
        case 192:
            val = 0x04U;
            break;
        case 256:
            val = 0x06U;
            break;
        case 384:
            val = 0x08U;
            break;
        case 512:
            val = 0x0AU;
            break;
        case 768:
            val = 0x0CU;
            break;
        case 1024:
            val = 0x0EU;
            break;
        case 1536:
            val = 0x12U;
            break;
        case 3072:
            val = 0x14U;
            break;
        case 6144:
            val = 0x16U;
            break;
        default:
            retval = kStatus_InvalidArgument;
            break;
    }

    if (kStatus_Success != retval)
    {
        return retval;
    }

    WM8962_CHECK_RET(WM8962_WriteReg(handle, WM8962_CLK4, val), retval);

    return retval;
}

status_t WM8962_WriteReg(wm8962_handle_t *handle, uint16_t reg, uint16_t val)
{
    uint16_t buff = (uint16_t)(WM8962_SWAP_UINT16_BYTE_SEQUENCE(val) & 0xFFFFU);

    return CODEC_I2C_Send(handle->i2cHandle, handle->config->slaveAddress, reg, 2U, (uint8_t *)(uintptr_t)&buff, 2U);
}

status_t WM8962_ReadReg(wm8962_handle_t *handle, uint16_t reg, uint16_t *val)
{
    status_t retval    = 0;
    uint16_t readValue = 0U;

    retval = CODEC_I2C_Receive(handle->i2cHandle, handle->config->slaveAddress, reg, 2U, (uint8_t *)&readValue, 2U);
    if (retval == kStatus_Success)
    {
        *val = WM8962_SWAP_UINT16_BYTE_SEQUENCE(readValue);
    }
    return retval;
}

status_t WM8962_ModifyReg(wm8962_handle_t *handle, uint16_t reg, uint16_t mask, uint16_t val)
{
    status_t retval  = 0;
    uint16_t reg_val = 0;
    retval           = WM8962_ReadReg(handle, reg, &reg_val);
    if (retval != kStatus_Success)
    {
        return kStatus_Fail;
    }
    reg_val &= (uint16_t)~mask;
    reg_val |= val;
    retval = WM8962_WriteReg(handle, reg, reg_val);
    if (retval != kStatus_Success)
    {
        return kStatus_Fail;
    }
    return kStatus_Success;
}

#if DEBUG_WM8962_REGISTER
void WM8962_ReadAllReg(wm8962_handle_t *handle, uint32_t endAddress)
{
    status_t retval    = 0;
    uint16_t readValue = 0U, i = 0U;

    for (i = 0U; i < endAddress; i++)
    {
        retval = CODEC_I2C_Receive(handle->i2cHandle, handle->config->slaveAddress, i, 2U, (uint8_t *)&readValue, 2U);
        if (retval == kStatus_Success)
        {
            PRINTF("REG %x, value %x\r\n", i, WM8962_SWAP_UINT16_BYTE_SEQUENCE(readValue));
        }
        else
        {
            assert(false);
        }
    }
}
#endif
