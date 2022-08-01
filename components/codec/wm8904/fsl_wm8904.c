/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_wm8904.h"
#if WM8904_DEBUG_REGISTER
#include "fsl_debug_console.h"
#endif
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief wm8904 volume mapping */
#define WM8904_SWAP_UINT16_BYTE_SEQUENCE(x) ((((x) & 0x00ffU) << 8U) | (((x) & 0xff00U) >> 8U))
#define WM8904_MAP_SAMPLERATE(x)          \
    ((x) == kWM8904_SampleRate8kHz ?      \
         8000U :                          \
         (x) == kWM8904_SampleRate12kHz ? \
         12000U :                         \
         (x) == kWM8904_SampleRate16kHz ? \
         16000U :                         \
         (x) == kWM8904_SampleRate24kHz ? \
         24000U :                         \
         (x) == kWM8904_SampleRate32kHz ? \
         32000U :                         \
         (x) == kWM8904_SampleRate48kHz ? \
         48000U :                         \
         (x) == kWM8904_SampleRate11025Hz ? 11025U : (x) == kWM8904_SampleRate22050Hz ? 22050U : 44100U)
#define WM8904_MAP_BITWIDTH(x) \
    ((x) == kWM8904_BitWidth16 ? 16 : (x) == kWM8904_BitWidth20 ? 20 : (x) == kWM8904_BitWidth24 ? 24 : 32)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief WM8904 update format.
 *
 * @param handle WM8904 handle structure.
 * @param fsRatio fs ratio.
 * @param sampleRate sample rate.
 * @param bitWidth bit width.
 * @return kStatus_Success, else failed.
 */
static status_t WM8904_UpdateFormat(wm8904_handle_t *handle,
                                    wm8904_fs_ratio_t fsRatio,
                                    wm8904_sample_rate_t sampleRate,
                                    wm8904_bit_width_t bitWidth);

/*!
 * @brief WM8904 wait on write sequencer.
 *
 * @param handle WM8904 handle structure.
 * @return kStatus_Success, else failed.
 */
static status_t WM8904_WaitOnWriteSequencer(wm8904_handle_t *handle);
/*******************************************************************************
 * Variables
 ******************************************************************************/
#if WM8904_DEBUG_REGISTER
/*! @brief register definition */
static const uint8_t allRegisters[] = {
    0x00, 0x04, 0x05, 0x06, 0x07, 0x0A, 0x0C, 0x0E, 0x0F, 0x12, 0x14, 0x15, 0x16, 0x18, 0x19, 0x1A, 0x1B,
    0x1E, 0x1F, 0x20, 0x21, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x39,
    0x3A, 0x3B, 0x3C, 0x3D, 0x43, 0x44, 0x45, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x5A, 0x5E, 0x62,
    0x68, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7E, 0x7F,
    0x80, 0x81, 0x82, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93,
    0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0xC6, 0xF7, 0xF8};
#endif
/*******************************************************************************
 * Code
 ******************************************************************************/
static status_t WM8904_UpdateFormat(wm8904_handle_t *handle,
                                    wm8904_fs_ratio_t fsRatio,
                                    wm8904_sample_rate_t sampleRate,
                                    wm8904_bit_width_t bitWidth)
{
    status_t result = kStatus_Success;

    /* Disable SYSCLK */
    result = WM8904_WriteRegister(handle, WM8904_CLK_RATES_2, 0x00);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* Set Clock ratio and sample rate */
    result = WM8904_WriteRegister(handle, WM8904_CLK_RATES_1,
                                  (uint16_t)(((uint16_t)(fsRatio) << 10U) | (uint16_t)(sampleRate)));
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* Set bit resolution */
    result = WM8904_ModifyRegister(handle, WM8904_AUDIO_IF_1, (0x000CU), ((uint16_t)(bitWidth) << 2U));
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* Enable SYSCLK */
    result = WM8904_WriteRegister(handle, WM8904_CLK_RATES_2, 0x1007);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    return kStatus_WM8904_Success;
}

static status_t WM8904_WaitOnWriteSequencer(wm8904_handle_t *handle)
{
    status_t result = kStatus_Success;
    uint16_t value;

    do
    {
        result = WM8904_ReadRegister(handle, WM8904_WRT_SEQUENCER_4, &value);
    } while ((result == kStatus_WM8904_Success) && ((value & 1U) != 0U));

    return result;
}

/*!
 * brief WM8904 write register.
 *
 * param handle WM8904 handle structure.
 * param reg register address.
 * param value value to write.
 * return kStatus_Success, else failed.
 */
status_t WM8904_WriteRegister(wm8904_handle_t *handle, uint8_t reg, uint16_t value)
{
    assert(handle->config != NULL);
    assert(handle->config->slaveAddress != 0U);

    uint16_t writeValue = (uint16_t)WM8904_SWAP_UINT16_BYTE_SEQUENCE(value);

    return CODEC_I2C_Send(handle->i2cHandle, handle->config->slaveAddress, reg, 1U, (uint8_t *)&writeValue, 2U);
}

/*!
 * brief WM8904 write register.
 *
 * param handle WM8904 handle structure.
 * param reg register address.
 * param value value to read.
 * return kStatus_Success, else failed.
 */
status_t WM8904_ReadRegister(wm8904_handle_t *handle, uint8_t reg, uint16_t *value)
{
    assert(handle->config != NULL);
    assert(handle->config->slaveAddress != 0U);

    status_t retval    = 0;
    uint16_t readValue = 0U;

    retval = CODEC_I2C_Receive(handle->i2cHandle, handle->config->slaveAddress, (uint32_t)reg, 1U,
                               (uint8_t *)&readValue, 2U);

    *value = (uint16_t)WM8904_SWAP_UINT16_BYTE_SEQUENCE(readValue);

    return retval;
}

/*!
 * brief WM8904 modify register.
 *
 * param handle WM8904 handle structure.
 * param reg register address.
 * oaram mask register bits mask.
 * param value value to write.
 * return kStatus_Success, else failed.
 */
status_t WM8904_ModifyRegister(wm8904_handle_t *handle, uint8_t reg, uint16_t mask, uint16_t value)
{
    status_t result = kStatus_Success;
    uint16_t regValue;

    result = WM8904_ReadRegister(handle, reg, &regValue);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    regValue &= (uint16_t)~mask;
    regValue |= value;

    return WM8904_WriteRegister(handle, reg, regValue);
}

/*!
 * brief Initializes WM8904.
 *
 * param handle WM8904 handle structure.
 * param codec_config WM8904 configuration structure.
 */
status_t WM8904_Init(wm8904_handle_t *handle, wm8904_config_t *wm8904Config)
{
    assert(handle != NULL);
    assert(wm8904Config != NULL);

    status_t result         = kStatus_Success;
    uint32_t sysclk         = 0U;
    wm8904_config_t *config = wm8904Config;
    handle->config          = config;

    /* i2c bus initialization */
    result = CODEC_I2C_Init(handle->i2cHandle, wm8904Config->i2cConfig.codecI2CInstance, WM8904_I2C_BITRATE,
                            wm8904Config->i2cConfig.codecI2CSourceClock);
    if (result != (status_t)kStatus_HAL_I2cSuccess)
    {
        return kStatus_WM8904_Fail;
    }

    /* reset */
    result = WM8904_WriteRegister(handle, WM8904_RESET, 0x0000);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* MCLK_INV=0, SYSCLK_SRC=0, TOCLK_RATE=0, OPCLK_ENA=1,
     * CLK_SYS_ENA=1, CLK_DSP_ENA=1, TOCLK_ENA=1 */
    result = WM8904_WriteRegister(handle, WM8904_CLK_RATES_2, 0x000F);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* WSEQ_ENA=1, WSEQ_WRITE_INDEX=0_0000 */
    result = WM8904_WriteRegister(handle, WM8904_WRT_SEQUENCER_0, 0x0100);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* WSEQ_ABORT=0, WSEQ_START=1, WSEQ_START_INDEX=00_0000 */
    result = WM8904_WriteRegister(handle, WM8904_WRT_SEQUENCER_3, 0x0100);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    result = WM8904_WaitOnWriteSequencer(handle);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* TOCLK_RATE_DIV16=0, TOCLK_RATE_x4=1, SR_MODE=0, MCLK_DIV=1
     * (Required for MMCs: SGY, KRT see erratum CE000546) */
    result = WM8904_WriteRegister(handle, WM8904_CLK_RATES_0, 0xA45F);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* INL_ENA=1, INR ENA=1 */
    result = WM8904_WriteRegister(handle, WM8904_POWER_MGMT_0, 0x0003);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* HPL_PGA_ENA=1, HPR_PGA_ENA=1 */
    result = WM8904_WriteRegister(handle, WM8904_POWER_MGMT_2, 0x0003);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* DACL_ENA=1, DACR_ENA=1, ADCL_ENA=1, ADCR_ENA=1 */
    result = WM8904_WriteRegister(handle, WM8904_POWER_MGMT_6, 0x000F);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* ADC_OSR128=1 */
    result = WM8904_WriteRegister(handle, WM8904_ANALOG_ADC_0, 0x0001);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* DACL_DATINV=0, DACR_DATINV=0, DAC_BOOST=00, LOOPBACK=0, AIFADCL_SRC=0,
     * AIFADCR_SRC=1, AIFDACL_SRC=0, AIFDACR_SRC=1, ADC_COMP=0, ADC_COMPMODE=0,
     * DAC_COMP=0, DAC_COMPMODE=0 */
    result = WM8904_WriteRegister(handle, WM8904_AUDIO_IF_0, 0x0050);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* DAC_MONO=0, DAC_SB_FILT-0, DAC_MUTERATE=0, DAC_UNMUTE RAMP=0,
     * DAC_OSR128=1, DAC_MUTE=0, DEEMPH=0 (none) */
    result = WM8904_WriteRegister(handle, WM8904_DAC_DIG_1, 0x0040);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* LINMUTE=0, LIN_VOL=0_0101 */
    result = WM8904_WriteRegister(handle, WM8904_ANALOG_LEFT_IN_0, 0x0005);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* RINMUTE=0, RIN VOL=0_0101 LINEOUTL RMV SHORT-1, LINEOUTL ENA_OUTP=1,
     * LINEOUTL_ENA_DLY=1, LINEOUTL_ENA=1, LINEOUTR_RMV_SHORT-1,
     * LINEOUTR_ENA_OUTP=1 */
    result = WM8904_WriteRegister(handle, WM8904_ANALOG_RIGHT_IN_0, 0x0005);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* HPOUTL_MUTE=0, HPOUT_VU=0, HPOUTLZC=0, HPOUTL_VOL=10_1101 */
    result = WM8904_WriteRegister(handle, WM8904_ANALOG_OUT1_LEFT, 0x00AD);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* HPOUTR_MUTE=0, HPOUT_VU=0, HPOUTRZC=0, HPOUTR_VOL=10_1101 */
    result = WM8904_WriteRegister(handle, WM8904_ANALOG_OUT1_RIGHT, 0x00AD);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* Enable DC servos for headphone out */
    result = WM8904_WriteRegister(handle, WM8904_DC_SERVO_0, 0x0003);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* HPL_RMV_SHORT=1, HPL_ENA_OUTP=1, HPL_ENA_DLY=1, HPL_ENA=1,
     * HPR_RMV_SHORT=1, HPR_ENA_OUTP=1, HPR_ENA_DLY=1, HPR_ENA=1 */
    result = WM8904_WriteRegister(handle, WM8904_ANALOG_HP_0, 0x00FF);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* CP_DYN_PWR=1 */
    result = WM8904_WriteRegister(handle, WM8904_CLS_W_0, 0x0001);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* CP_ENA=1 */
    result = WM8904_WriteRegister(handle, WM8904_CHRG_PUMP_0, 0x0001);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* set audio format */
    result = WM8904_SetProtocol(handle, config->protocol);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    if (config->sysClkSource == kWM8904_SysClkSourceFLL)
    {
        result = WM8904_SetFLLConfig(handle, config->fll);
        if (result != kStatus_WM8904_Success)
        {
            return result;
        }
        sysclk = config->fll->outputClock_HZ;
    }
    else
    {
        sysclk = config->mclk_HZ;
    }

    result = WM8904_CheckAudioFormat(handle, &config->format, sysclk);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    result =
        WM8904_ModifyRegister(handle, WM8904_CLK_RATES_2, (uint16_t)(1UL << 14U), (uint16_t)(config->sysClkSource));
    if (kStatus_WM8904_Success != result)
    {
        return result;
    }

    if (config->master)
    {
        result = WM8904_SetMasterClock(handle, sysclk, (uint32_t)(WM8904_MAP_SAMPLERATE(config->format.sampleRate)),
                                       (uint32_t)(WM8904_MAP_BITWIDTH(config->format.bitWidth)));
        if (result != kStatus_WM8904_Success)
        {
            return result;
        }
    }
    else
    {
        /* BCLK/LRCLK default direction input */
        result = WM8904_ModifyRegister(handle, WM8904_AUDIO_IF_1, 1U << 6U, 0U);
        if (kStatus_WM8904_Success != result)
        {
            return result;
        }

        result = WM8904_ModifyRegister(handle, WM8904_AUDIO_IF_3, (uint16_t)(1UL << 11U), 0U);
        if (kStatus_WM8904_Success != result)
        {
            return result;
        }
    }

    /* set record source and channel */
    result = WM8904_SetRecord(handle, config->recordSource);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }
    result = WM8904_SetRecordChannel(handle, config->recordChannelLeft, config->recordChannelRight);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }
    /* set play source */
    result = WM8904_SetPlay(handle, config->playSource);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    return result;
}

/*!
 * brief Deinitializes the WM8904 codec.
 *
 * This function resets WM8904.
 *
 * param handle WM8904 handle structure.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_Deinit(wm8904_handle_t *handle)
{
    /* reset */
    if (WM8904_WriteRegister(handle, WM8904_RESET, 0x0000) == kStatus_WM8904_Success)
    {
        return CODEC_I2C_Deinit(handle->i2cHandle);
    }

    return kStatus_WM8904_Fail;
}

/*!
 * brief Fills the configuration structure with default values.
 *
 * The default values are:
 *
 *   master = false;
 *   protocol = kWM8904_ProtocolI2S;
 *   format.fsRatio = kWM8904_FsRatio64X;
 *   format.sampleRate = kWM8904_SampleRate48kHz;
 *   format.bitWidth = kWM8904_BitWidth16;
 *
 * param handle WM8904 handle structure to be filled with default values.
 */
void WM8904_GetDefaultConfig(wm8904_config_t *config)
{
    (void)memset(config, 0, sizeof(wm8904_config_t));

    config->master            = false;
    config->protocol          = kWM8904_ProtocolI2S;
    config->format.sampleRate = kWM8904_SampleRate48kHz;
    config->format.bitWidth   = kWM8904_BitWidth16;
}

/*!
 * brief Sets WM8904 as master or slave.
 * deprecated DO NOT USE THIS API ANYMORE. IT HAS BEEN SUPERCEDED BY @ref WM8904_SetMasterClock
 * param handle WM8904 handle structure.
 * param master true for master, false for slave.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_SetMasterSlave(wm8904_handle_t *handle, bool master)
{
    if (master)
    {
        /* only slave currently supported */
        return kStatus_WM8904_Fail;
    }

    return kStatus_WM8904_Success;
}

/*!
 * brief Sets WM8904 master clock configuration.
 *
 * param handle WM8904 handle structure.
 * param sysclk system clock rate.
 * param sampleRate sample rate
 * param bitWidth bit width
 *
 * return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_SetMasterClock(wm8904_handle_t *handle, uint32_t sysclk, uint32_t sampleRate, uint32_t bitWidth)
{
    uint32_t bclk           = sampleRate * bitWidth * 2U;
    uint32_t bclkDiv        = 0U;
    uint16_t audioInterface = 0U;
    status_t result         = kStatus_WM8904_Success;
    uint16_t sysclkDiv      = 0U;

    result = WM8904_ReadRegister(handle, WM8904_CLK_RATES_0, &sysclkDiv);
    sysclk = sysclk >> (sysclkDiv & 0x1U);

    if ((sysclk / bclk > 48U) || (bclk / sampleRate > 2047U) || (bclk / sampleRate < 8U))
    {
        return kStatus_InvalidArgument;
    }

    result = WM8904_ReadRegister(handle, WM8904_AUDIO_IF_2, &audioInterface);
    if (kStatus_WM8904_Success != result)
    {
        return result;
    }

    audioInterface &= ~(uint16_t)0x1FU;
    bclkDiv = (sysclk * 10U) / bclk;

    switch (bclkDiv)
    {
        case 10:
            audioInterface |= 0U;
            break;
        case 15:
            audioInterface |= 1U;
            break;
        case 20:
            audioInterface |= 2U;
            break;
        case 30:
            audioInterface |= 3U;
            break;
        case 40:
            audioInterface |= 4U;
            break;
        case 50:
            audioInterface |= 5U;
            break;
        case 55:
            audioInterface |= 6U;
            break;
        case 60:
            audioInterface |= 7U;
            break;
        case 80:
            audioInterface |= 8U;
            break;
        case 100:
            audioInterface |= 9U;
            break;
        case 110:
            audioInterface |= 10U;
            break;
        case 120:
            audioInterface |= 11U;
            break;
        case 160:
            audioInterface |= 12U;
            break;
        case 200:
            audioInterface |= 13U;
            break;
        case 220:
            audioInterface |= 14U;
            break;
        case 240:
            audioInterface |= 15U;
            break;
        case 250:
            audioInterface |= 16U;
            break;
        case 300:
            audioInterface |= 17U;
            break;
        case 320:
            audioInterface |= 18U;
            break;
        case 440:
            audioInterface |= 19U;
            break;
        case 480:
            audioInterface |= 20U;
            break;
        default:
            result = kStatus_InvalidArgument;
            break;
    }

    if (kStatus_WM8904_Success != result)
    {
        return result;
    }

    /* bclk divider */
    result = WM8904_WriteRegister(handle, WM8904_AUDIO_IF_2, audioInterface);
    if (kStatus_WM8904_Success != result)
    {
        return result;
    }
    /* bclk direction output */
    result = WM8904_ModifyRegister(handle, WM8904_AUDIO_IF_1, 1U << 6U, 1U << 6U);
    if (kStatus_WM8904_Success != result)
    {
        return result;
    }

    result = WM8904_ModifyRegister(handle, WM8904_GPIO_CONTROL_4, 0x8FU, 1U);
    if (kStatus_WM8904_Success != result)
    {
        return result;
    }
    /* LRCLK direction and divider */
    audioInterface = (uint16_t)((1UL << 11U) | (bclk / sampleRate));
    result         = WM8904_ModifyRegister(handle, WM8904_AUDIO_IF_3, 0xFFFU, audioInterface);
    if (kStatus_WM8904_Success != result)
    {
        return result;
    }

    return kStatus_WM8904_Success;
}

/*!
 * brief WM8904 set PLL configuration
 * This function will enable the GPIO1 FLL clock output function, so user can see
 * the generated fll output clock frequency from WM8904 GPIO1.
 *
 * param handle wm8904 handler pointer.
 * param config FLL configuration pointer.
 *
 */
status_t WM8904_SetFLLConfig(wm8904_handle_t *handle, wm8904_fll_config_t *config)
{
    assert(config != NULL);
    assert(handle != NULL);

    uint32_t referenceClock = config->refClock_HZ;
    uint32_t inputDivider   = 0U;
    uint32_t fvco = 0U, outputDiv = 0U, ratio = 0U;
    uint32_t n = 0U, k = 0U;

    /* it is recommended that the highest possible frequency - within the 13.5MHz limit - should be selected */
    if (referenceClock < 13500000U)
    {
        inputDivider = 0;
    }
    else if (referenceClock / 2U < 13500000U)
    {
        inputDivider = 1;
    }
    else if (referenceClock / 4U < 13500000U)
    {
        inputDivider = 2;
    }
    else
    {
        inputDivider = 3;
    }

    if (referenceClock / (1UL << inputDivider) > 13500000U)
    {
        return kStatus_InvalidArgument;
    }

    referenceClock = referenceClock / (1UL << inputDivider);

    for (outputDiv = 4U; outputDiv <= 64U; outputDiv++)
    {
        fvco = outputDiv * config->outputClock_HZ;
        if ((fvco >= 90000000U) && (fvco <= 100000000U))
        {
            break;
        }
    }

    if (referenceClock <= 64000U)
    {
        ratio = 4U;
    }
    else if (referenceClock <= 128000U)
    {
        ratio = 3U;
    }
    else if (referenceClock <= 256000U)
    {
        ratio = 2U;
    }
    else if (referenceClock <= 1000000U)
    {
        ratio = 1U;
    }
    else
    {
        ratio = 0U;
    }

    n = fvco / ((ratio + 1U) * referenceClock);
    k = (uint32_t)((uint64_t)fvco * 1000000U) / ((ratio + 1U) * referenceClock);
    if (n != 0U)
    {
        k = k - n * 1000000U;
    }
    k = (uint32_t)((uint64_t)k * 65536U) / 1000000U;

    /* configure WM8904  */
    if (WM8904_ModifyRegister(handle, WM8904_FLL_CONTROL_1, 7U, 4U) != kStatus_Success)
    {
        return kStatus_WM8904_Fail;
    }

    /* configure WM8904  */
    if (WM8904_ModifyRegister(handle, WM8904_FLL_CONTROL_2, 0x3F07U, (uint16_t)(((outputDiv - 1U) << 8U) | ratio)) !=
        kStatus_Success)
    {
        return kStatus_WM8904_Fail;
    }

    if (kStatus_WM8904_Success != WM8904_WriteRegister(handle, WM8904_FLL_CONTROL_3, (uint16_t)k))
    {
        return kStatus_WM8904_Fail;
    }

    if (WM8904_ModifyRegister(handle, WM8904_FLL_CONTROL_4, 0x7FE0U, (uint16_t)(n << 5U)) != kStatus_Success)
    {
        return kStatus_WM8904_Fail;
    }

    if (kStatus_WM8904_Success !=
        WM8904_WriteRegister(handle, WM8904_FLL_CONTROL_5, (uint16_t)((inputDivider << 3U) | (uint16_t)config->source)))
    {
        return kStatus_WM8904_Fail;
    }

    if (WM8904_ModifyRegister(handle, WM8904_FLL_CONTROL_1, 1U, 1) != kStatus_Success)
    {
        return kStatus_WM8904_Fail;
    }

    /* enable GPIO1 output fll output clock */
    if (kStatus_WM8904_Success != WM8904_WriteRegister(handle, 0x79U, (uint16_t)9U))
    {
        return kStatus_WM8904_Fail;
    }

    return kStatus_Success;
}

/*!
 * brief Sets the audio data transfer protocol.
 *
 * param handle WM8904 handle structure.
 * param protocol Audio transfer protocol.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_SetProtocol(wm8904_handle_t *handle, wm8904_protocol_t protocol)
{
    return WM8904_ModifyRegister(handle, WM8904_AUDIO_IF_1, (0x0003U | (1U << 4U)), (uint16_t)protocol);
}

/*!
 * brief Select LRC polarity.
 *
 * param handle WM8904 handle structure.
 * param polarity LRC clock polarity.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_SelectLRCPolarity(wm8904_handle_t *handle, uint32_t polarity)
{
    return WM8904_ModifyRegister(handle, WM8904_AUDIO_IF_1, 0x0010U, (uint16_t)polarity);
}

/*!
 * brief Enable WM8904 DAC time slot.
 *
 * param handle WM8904 handle structure.
 * param timeslot timeslot number.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_EnableDACTDMMode(wm8904_handle_t *handle, wm8904_timeslot_t timeSlot)
{
    return WM8904_ModifyRegister(handle, WM8904_AUDIO_IF_1, ((uint16_t)3U << 12U),
                                 (((uint16_t)1U << 13U) | ((uint16_t)timeSlot << 12U)));
}

/*!
 * brief Enable WM8904 ADC time slot.
 *
 * param handle WM8904 handle structure.
 * param timeslot timeslot number.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_EnableADCTDMMode(wm8904_handle_t *handle, wm8904_timeslot_t timeSlot)
{
    return WM8904_ModifyRegister(handle, WM8904_AUDIO_IF_1, ((uint16_t)3U << 10U),
                                 (((uint16_t)1U << 11U) | ((uint16_t)timeSlot << 10U)));
}

/*!
 * brief check and update the audio data format.
 * This api is used check the fsRatio setting based on the mclk and sample rate, if fsRatio setting
 * is not correct, it will correct it according to mclk and sample rate.
 * param handle WM8904 handle structure.
 * param format audio data format
 * param mclkFreq mclk frequency
 *
 * return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_CheckAudioFormat(wm8904_handle_t *handle, wm8904_audio_format_t *format, uint32_t mclkFreq)
{
    assert((handle != NULL) && (format != NULL));

    status_t result                    = kStatus_Success;
    uint16_t mclkDiv                   = 0U;
    uint32_t sampleRate                = 0U;
    uint32_t fsRatio                   = 0U;
    wm8904_sample_rate_t regSamplerate = format->sampleRate;
    status_t error                     = kStatus_WM8904_Success;

    result = WM8904_ReadRegister(handle, WM8904_CLK_RATES_0, &mclkDiv);
    if (kStatus_WM8904_Success != result)
    {
        return result;
    }

    switch (format->sampleRate)
    {
        case kWM8904_SampleRate8kHz:
            sampleRate = 8000;
            break;
        case kWM8904_SampleRate11025Hz:
            sampleRate    = 11025;
            regSamplerate = kWM8904_SampleRate12kHz;
            break;
        case kWM8904_SampleRate12kHz:
            sampleRate = 12000;
            break;
        case kWM8904_SampleRate16kHz:
            sampleRate = 16000;
            break;
        case kWM8904_SampleRate22050Hz:
            sampleRate    = 22050;
            regSamplerate = kWM8904_SampleRate24kHz;
            break;
        case kWM8904_SampleRate24kHz:
            sampleRate = 24000;
            break;
        case kWM8904_SampleRate32kHz:
            sampleRate = 32000;
            break;
        case kWM8904_SampleRate44100Hz:
            sampleRate    = 44100;
            regSamplerate = kWM8904_SampleRate48kHz;
            break;
        case kWM8904_SampleRate48kHz:
            sampleRate = 48000;
            break;
        default:
            error = kStatus_WM8904_Fail;
            break;
    }

    if (error != kStatus_WM8904_Success)
    {
        return error;
    }

    fsRatio = (mclkFreq >> (mclkDiv & 0x1U)) / sampleRate;

    switch (fsRatio)
    {
        case 64:
            format->fsRatio = kWM8904_FsRatio64X;
            break;
        case 128:
            format->fsRatio = kWM8904_FsRatio128X;
            break;
        case 192:
            format->fsRatio = kWM8904_FsRatio192X;
            break;
        case 256:
            format->fsRatio = kWM8904_FsRatio256X;
            break;
        case 384:
            format->fsRatio = kWM8904_FsRatio384X;
            break;
        case 512:
            format->fsRatio = kWM8904_FsRatio512X;
            break;
        case 768:
            format->fsRatio = kWM8904_FsRatio768X;
            break;
        case 1024:
            format->fsRatio = kWM8904_FsRatio1024X;
            break;
        case 1408:
            format->fsRatio = kWM8904_FsRatio1408X;
            break;
        case 1536:
            format->fsRatio = kWM8904_FsRatio1536X;
            break;
        default:
            error = kStatus_WM8904_Fail;
            break;
    }

    if (error != kStatus_WM8904_Success)
    {
        return error;
    }

    return WM8904_UpdateFormat(handle, format->fsRatio, regSamplerate, format->bitWidth);
}

/*!
 * brief Sets the audio data format.
 *
 * param handle WM8904 handle structure.
 * param sysclk external input clock frequency used as WM8904 system clock.
 * param sampleRate Sample rate frequency in Hz.
 * param bitWidth Audio data bit width.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_SetAudioFormat(wm8904_handle_t *handle, uint32_t sysclk, uint32_t sampleRate, uint32_t bitWidth)
{
    uint32_t ratio                     = 0;
    status_t error                     = kStatus_WM8904_Success;
    wm8904_bit_width_t regBitWidth     = kWM8904_BitWidth32;
    wm8904_sample_rate_t regSamplerate = kWM8904_SampleRate48kHz;
    wm8904_fs_ratio_t regFsRatio       = kWM8904_FsRatio1536X;
    uint16_t tempReg                   = 0U;

    error = WM8904_ReadRegister(handle, WM8904_CLK_RATES_0, &tempReg);
    if (error != kStatus_WM8904_Success)
    {
        return error;
    }

    switch (sampleRate)
    {
        case 8000:
            regSamplerate = kWM8904_SampleRate8kHz;
            break;
        case 11025:
            regSamplerate = kWM8904_SampleRate12kHz;
            break;
        case 12000:
            regSamplerate = kWM8904_SampleRate12kHz;
            break;
        case 16000:
            regSamplerate = kWM8904_SampleRate16kHz;
            break;
        case 22050:
            regSamplerate = kWM8904_SampleRate24kHz;
            break;
        case 24000:
            regSamplerate = kWM8904_SampleRate24kHz;
            break;
        case 32000:
            regSamplerate = kWM8904_SampleRate32kHz;
            break;
        case 44100:
            regSamplerate = kWM8904_SampleRate48kHz;
            break;
        case 48000:
            regSamplerate = kWM8904_SampleRate48kHz;
            break;
        default:
            error = kStatus_WM8904_Fail;
            break;
    }

    if (error != kStatus_WM8904_Success)
    {
        return error;
    }

    switch (bitWidth)
    {
        case 16:
            regBitWidth = kWM8904_BitWidth16;
            break;
        case 20:
            regBitWidth = kWM8904_BitWidth20;
            break;
        case 24:
            regBitWidth = kWM8904_BitWidth24;
            break;
        case 32:
            regBitWidth = kWM8904_BitWidth32;
            break;
        default:
            error = kStatus_WM8904_Fail;
            break;
    }

    if (error != kStatus_WM8904_Success)
    {
        return error;
    }

    ratio = (sysclk >> (tempReg & 0x1U)) / sampleRate;

    switch (ratio)
    {
        case 64:
            regFsRatio = kWM8904_FsRatio64X;
            break;
        case 128:
            regFsRatio = kWM8904_FsRatio128X;
            break;
        case 192:
            regFsRatio = kWM8904_FsRatio192X;
            break;
        case 256:
            regFsRatio = kWM8904_FsRatio256X;
            break;
        case 384:
            regFsRatio = kWM8904_FsRatio384X;
            break;
        case 512:
            regFsRatio = kWM8904_FsRatio512X;
            break;
        case 768:
            regFsRatio = kWM8904_FsRatio768X;
            break;
        case 1024:
            regFsRatio = kWM8904_FsRatio1024X;
            break;
        case 1408:
            regFsRatio = kWM8904_FsRatio1408X;
            break;
        case 1536:
            regFsRatio = kWM8904_FsRatio1536X;
            break;
        default:
            error = kStatus_WM8904_Fail;
            break;
    }

    if (error == kStatus_WM8904_Success)
    {
        if (kStatus_WM8904_Success == WM8904_UpdateFormat(handle, regFsRatio, regSamplerate, regBitWidth))
        {
            /* check codec in master or not */
            error = WM8904_ReadRegister(handle, WM8904_AUDIO_IF_1, &tempReg);
            if (kStatus_WM8904_Success == error)
            {
                if ((tempReg & (1UL << 6U)) != 0U)
                {
                    error = WM8904_SetMasterClock(handle, sysclk, sampleRate, bitWidth);
                }
            }
        }
    }

    return error;
}

/*!
 * brief Sets the headphone output volume.
 *
 * The parameter should be from 0 to 63.
 * The resulting volume will be (parameter - 57 dB).
 * 0 for -57 dB, 57 for 0 dB, 63 for +6 dB etc.
 *
 * param handle WM8904 handle structure.
 * param volumeLeft Volume of the left channel.
 * param volumeRight Volume of the right channel.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_SetVolume(wm8904_handle_t *handle, uint16_t volumeLeft, uint16_t volumeRight)
{
    assert(volumeRight <= WM8904_MAP_HEADPHONE_LINEOUT_MAX_VOLUME);
    assert(volumeLeft <= WM8904_MAP_HEADPHONE_LINEOUT_MAX_VOLUME);

    status_t result = kStatus_Success;

    /* 0x1BF means unmute the OUT and reset the OUT volume update bit and volume range fields*/
    result = WM8904_ModifyRegister(handle, WM8904_ANALOG_OUT1_LEFT, 0x1BF, volumeLeft);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    result = WM8904_ModifyRegister(handle, WM8904_ANALOG_OUT1_RIGHT, 0x1BFU, ((uint16_t)volumeRight | 0x0080U));
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    return kStatus_WM8904_Success;
}

/*!
 * brief Sets the headphone output mute.
 *
 * param handle WM8904 handle structure.
 * param muteLeft true to mute left channel, false to unmute.
 * param muteRight true to mute right channel, false to unmute.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_SetMute(wm8904_handle_t *handle, bool muteLeft, bool muteRight)
{
    status_t result = kStatus_Success;
    uint16_t left   = (uint16_t)(muteLeft ? 0x0100U : 0x0000U);
    uint16_t right  = (uint16_t)(muteRight ? 0x0100U : 0x0000U);

    result = WM8904_ModifyRegister(handle, WM8904_ANALOG_OUT1_LEFT, 0x0100, left);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    result = WM8904_ModifyRegister(handle, WM8904_ANALOG_OUT1_RIGHT, 0x0180U, ((uint16_t)right | 0x0080U));
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    return kStatus_WM8904_Success;
}

#if WM8904_DEBUG_REGISTER
/*!
 * brief Reads content of all WM8904 registers and prints it to debug console.
 *
 * param handle WM8904 handle structure.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_PrintRegisters(wm8904_handle_t *handle)
{
    status_t result = kStatus_Success;
    uint16_t value;
    uint32_t i;

    for (i = 0; i < sizeof(allRegisters); i++)
    {
        result = WM8904_ReadRegister(handle, allRegisters[i], &value);
        if (result != kStatus_WM8904_Success)
        {
            PRINTF("\r\n");
            return result;
        }
        PRINTF("%s", ((i % 8) == 0) ? "\r\n" : "\t");
        PRINTF("%02X:%04X", allRegisters[i], value);
    }

    PRINTF("\r\n");
    return result;
}
#endif

/*!
 * brief Sets the channel output volume.
 *
 * The parameter should be from 0 to 63.
 * The resulting volume will be.
 * 0 for -57dB, 63 for 6DB.
 *
 * param handle codec handle structure.
 * param channel codec channel.
 * param volume volume value from 0 -63.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_SetChannelVolume(wm8904_handle_t *handle, uint32_t channel, uint32_t volume)
{
    assert(volume <= WM8904_MAP_HEADPHONE_LINEOUT_MAX_VOLUME);

    status_t ret = kStatus_Fail;

    /* headphone left channel
     *  0x1BF means unmute the OUT and reset the OUT volume update bit and volume range fields
     */
    if ((channel & (uint32_t)kWM8904_HeadphoneLeft) != 0U)
    {
        ret = WM8904_ModifyRegister(handle, WM8904_ANALOG_OUT1_LEFT, 0x1BFU, (uint16_t)volume | 0x80U);
    }
    /* headphone right channel */
    if ((channel & (uint32_t)kWM8904_HeadphoneRight) != 0U)
    {
        ret = WM8904_ModifyRegister(handle, WM8904_ANALOG_OUT1_RIGHT, 0x1BFU, ((uint16_t)volume | 0x80U));
    }
    /* line out left channel */
    if ((channel & (uint32_t)kWM8904_LineoutLeft) != 0U)
    {
        ret = WM8904_ModifyRegister(handle, WM8904_ANALOG_OUT2_LEFT, 0x1BFU, (uint16_t)volume | 0X80U);
    }
    /* line out right channel */
    if ((channel & (uint32_t)kWM8904_LineoutRight) != 0U)
    {
        ret = WM8904_ModifyRegister(handle, WM8904_ANALOG_OUT2_RIGHT, 0x1BFU, (uint16_t)volume | 0x80U);
    }

    return ret;
}

/*!
 * brief Sets the channel mute.
 *
 * param handle codec handle structure.
 * param channel codec module name.
 * param isMute true is mute, false unmute.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_SetChannelMute(wm8904_handle_t *handle, uint32_t channel, bool isMute)
{
    status_t ret      = kStatus_Fail;
    uint16_t regValue = 0U, regMask = 0U;

    regValue = isMute ? 0x180U : 0x80U;
    regMask  = 0x100U;

    /* headphone left channel */
    if ((channel & (uint32_t)kWM8904_HeadphoneLeft) != 0U)
    {
        ret = WM8904_ModifyRegister(handle, WM8904_ANALOG_OUT1_LEFT, regMask, regValue);
    }

    /* headphone right channel */
    if ((channel & (uint32_t)kWM8904_HeadphoneRight) != 0U)
    {
        ret = WM8904_ModifyRegister(handle, WM8904_ANALOG_OUT1_RIGHT, regMask, regValue);
    }

    /* line out left channel */
    if ((channel & (uint32_t)kWM8904_LineoutLeft) != 0U)
    {
        ret = WM8904_ModifyRegister(handle, WM8904_ANALOG_OUT2_LEFT, regMask, regValue);
    }

    /* line out right channel */
    if ((channel & (uint32_t)kWM8904_LineoutRight) != 0U)
    {
        ret = WM8904_ModifyRegister(handle, WM8904_ANALOG_OUT2_RIGHT, regMask, regValue);
    }

    return ret;
}

/*!
 * brief SET the DAC module volume.
 *
 * param handle WM8904 handle structure.
 * param volume volume to be configured.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise..
 */
status_t WM8904_SetDACVolume(wm8904_handle_t *handle, uint8_t volume)
{
    status_t error = kStatus_WM8904_Success;

    error = WM8904_WriteRegister(handle, WM8904_DAC_DIGITAL_VOLUME_LEFT, (uint16_t)(volume | 0x100UL));
    if (error == kStatus_WM8904_Success)
    {
        error = WM8904_WriteRegister(handle, WM8904_DAC_DIGITAL_VOLUME_RIGHT, (uint16_t)(volume | 0x100UL));
    }

    return error;
}

/*!
 * brief SET the module output power.
 *
 * param handle WM8904 handle structure.
 * param module wm8904 module.
 * param isEnabled, true is power on, false is power down.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise..
 */
status_t WM8904_SetModulePower(wm8904_handle_t *handle, wm8904_module_t module, bool isEnabled)
{
    uint8_t regAddr = 0, regBitMask = 0U, regValue = 0U;
    status_t error = kStatus_WM8904_Success;

    switch (module)
    {
        case kWM8904_ModuleADC:
            regAddr    = WM8904_POWER_MGMT_6;
            regBitMask = 3U;
            regValue   = isEnabled ? 3U : 0U;
            break;
        case kWM8904_ModuleDAC:
            regAddr    = WM8904_POWER_MGMT_6;
            regBitMask = 0xCU;
            regValue   = isEnabled ? 0xCU : 0U;

            break;
        case kWM8904_ModulePGA:
            regAddr    = WM8904_POWER_MGMT_0;
            regBitMask = 3U;
            regValue   = isEnabled ? 3U : 0U;

            break;
        case kWM8904_ModuleHeadphone:
            regAddr    = WM8904_POWER_MGMT_2;
            regBitMask = 3U;
            regValue   = isEnabled ? 3U : 0U;
            break;
        case kWM8904_ModuleLineout:
            regAddr    = WM8904_POWER_MGMT_3;
            regBitMask = 3U;
            regValue   = isEnabled ? 3U : 0U;
            break;
        default:
            error = kStatus_InvalidArgument;
            break;
    }

    if (error == kStatus_WM8904_Success)
    {
        error = WM8904_ModifyRegister(handle, regAddr, regBitMask, regValue);
    }

    return error;
}

/*!
 * brief SET the WM8904 record source.
 *
 * param handle WM8904 handle structure.
 * param recordSource record source , can be a value of kWM8904_ModuleRecordSourceDifferentialLine,
 * kWM8904_ModuleRecordSourceDifferentialMic, kWM8904_ModuleRecordSourceSingleEndMic,
 * kWM8904_ModuleRecordSourceDigitalMic.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_SetRecord(wm8904_handle_t *handle, uint32_t recordSource)
{
    uint8_t regLeftAddr = WM8904_ANALOG_LEFT_IN_1, regRightAddr = WM8904_ANALOG_RIGHT_IN_1;
    uint16_t regLeftValue = 0U, regRightValue = 0U, regBitMask = 0U;
    status_t error = kStatus_Success;

    switch (recordSource)
    {
        case kWM8904_RecordSourceDifferentialLine:
            regLeftValue  = 1U;
            regRightValue = 1U;
            regBitMask    = 0x3FU;
            break;
        case kWM8904_RecordSourceDifferentialMic:
            regLeftValue  = 2U;
            regRightValue = 2U;
            regBitMask    = 0x3FU;
            break;
        case kWM8904_RecordSourceLineInput:
            regLeftValue  = 0U;
            regRightValue = 0U;
            regBitMask    = 0x3FU;
            break;
        case kWM8904_RecordSourceDigitalMic:
            regLeftValue = ((uint16_t)1U << 12);
            regLeftAddr  = WM8904_DAC_DIG_0;
            regRightAddr = 0U;
            regBitMask   = ((uint16_t)1U << 12);
            break;

        default:
            error = kStatus_InvalidArgument;
            break;
    }

    if (error == kStatus_Success)
    {
        error = WM8904_ModifyRegister(handle, regLeftAddr, regBitMask, regLeftValue);
    }

    if ((error == kStatus_Success) && (regRightAddr != 0U))
    {
        error = WM8904_ModifyRegister(handle, regRightAddr, regBitMask, regRightValue);
    }

    return error;
}

/*!
 * brief SET the WM8904 record source.
 *
 * param handle WM8904 handle structure.
 * param leftRecordChannel channel number of left record channel when using differential source, channel number of
 * single end left channel when using single end source, channel number of digital mic when using digital mic source.
 * param rightRecordChannel channel number of right record channel when using differential source, channel number
 * of single end right channel when using single end source.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise..
 */
status_t WM8904_SetRecordChannel(wm8904_handle_t *handle, uint32_t leftRecordChannel, uint32_t rightRecordChannel)
{
    uint8_t regLeftAddr = WM8904_ANALOG_LEFT_IN_1, regRightAddr = WM8904_ANALOG_RIGHT_IN_1;
    uint16_t regLeftValue = 0U, regRightValue = 0U, regBitMask;
    status_t ret                = kStatus_Success;
    uint8_t leftPositiveChannel = 0U, leftNegativeChannel = 0U, rightPositiveChannel = 0U, rightNegativeChannel = 0U;

    if ((leftRecordChannel & (uint32_t)kWM8904_RecordChannelDifferentialPositive1) != 0U)
    {
        leftPositiveChannel = 0U;
    }
    else if ((leftRecordChannel & (uint32_t)kWM8904_RecordChannelDifferentialPositive2) != 0U)
    {
        leftPositiveChannel = 1U;
    }
    else
    {
        leftPositiveChannel = 2U;
    }

    if ((leftRecordChannel & (uint32_t)kWM8904_RecordChannelDifferentialNegative1) != 0U)
    {
        leftNegativeChannel = 0U;
    }
    else if ((leftRecordChannel & (uint32_t)kWM8904_RecordChannelDifferentialNegative2) != 0U)
    {
        leftNegativeChannel = 1U;
    }
    else if ((leftRecordChannel & (uint32_t)kWM8904_RecordChannelDifferentialNegative3) != 0U)
    {
        leftNegativeChannel = 2U;
    }
    else
    {
        leftNegativeChannel = leftPositiveChannel;
    }

    if ((rightRecordChannel & (uint32_t)kWM8904_RecordChannelDifferentialPositive1) != 0U)
    {
        rightPositiveChannel = 0U;
    }
    else if ((rightRecordChannel & (uint32_t)kWM8904_RecordChannelDifferentialPositive2) != 0U)
    {
        rightPositiveChannel = 1U;
    }
    else
    {
        rightPositiveChannel = 2U;
    }

    if ((rightRecordChannel & (uint32_t)kWM8904_RecordChannelDifferentialNegative1) != 0U)
    {
        rightNegativeChannel = 0U;
    }
    else if ((rightRecordChannel & (uint32_t)kWM8904_RecordChannelDifferentialNegative2) != 0U)
    {
        rightNegativeChannel = 1U;
    }
    else if ((rightRecordChannel & (uint32_t)kWM8904_RecordChannelDifferentialNegative3) != 0U)
    {
        rightNegativeChannel = 2U;
    }
    else
    {
        rightNegativeChannel = rightPositiveChannel;
    }

    regLeftValue  = (((uint16_t)leftNegativeChannel & 3U) << 4U) | (((uint16_t)leftPositiveChannel & 3U) << 2U);
    regRightValue = (((uint16_t)rightNegativeChannel & 3U) << 4U) | (((uint16_t)rightPositiveChannel & 3U) << 2U);
    regBitMask    = 0x3CU;

    ret = WM8904_ModifyRegister(handle, regLeftAddr, regBitMask, regLeftValue);

    if (ret == kStatus_Success)
    {
        return WM8904_ModifyRegister(handle, regRightAddr, regBitMask, regRightValue);
    }

    return kStatus_Success;
}

/*!
 * brief SET the WM8904 play source.
 *
 * param handle WM8904 handle structure.
 * param playSource play source , can be a value of kWM8904_PlaySourcePGA/kWM8904_PlaySourceDAC.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise..
 */
status_t WM8904_SetPlay(wm8904_handle_t *handle, uint32_t playSource)
{
    uint16_t regValue = 0U, regBitMask = 0xFU;

    /* source form PGA*/
    if (playSource == (uint32_t)kWM8904_PlaySourcePGA)
    {
        regValue |= (3U << 2U) | 3U;
    }
    /* source from DAC*/
    if (playSource == (uint32_t)kWM8904_PlaySourceDAC)
    {
        regValue &= (uint16_t) ~((3U << 2U) | 3U);
    }

    return WM8904_ModifyRegister(handle, WM8904_ANALOG_OUT12_ZC, regBitMask, regValue);
}
