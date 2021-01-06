/*
 * Copyright  2017-2019 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_cs42888.h"
/*******************************************************************************
 * Definitations
 ******************************************************************************/
#define CLOCK_RATE_IN_RANGE(x, min, max) (((x) > (min)) && ((x) < (max)))
/*! @brief CS42888 ms counter*/
#ifndef CS42888_MS_COUNTER
#define CS42888_MS_COUNTER 200000U /* 1ms under 200MHZ core clock */
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Set CS42888 reset function.
 *
 * @param handle CS42888 handle structure.
 * @param codecReset reset pin control function pointer.
 */
static void CS42888_Reset(cs42888_handle_t *handle, cs42888_reset codecReset);

/*!
 *@brief cs42888 ms delay function.
 *
 * @param ms ms to delay.
 */
static void CS42888_DelayMs(uint32_t ms);
/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
static void CS42888_DelayMs(uint32_t ms)
{
    uint32_t i = 0U, j = 0U;

    for (i = 0U; i < ms; i++)
    {
        for (j = 0U; j < CS42888_MS_COUNTER; j++)
        {
            __NOP();
        }
    }
}
status_t CS42888_Init(cs42888_handle_t *handle, cs42888_config_t *config)
{
    assert(handle != NULL);
    assert(config != NULL);

    uint8_t i            = 0;
    status_t errorStatus = kStatus_Success;

    handle->config = config;

    /* i2c bus initialization */
    errorStatus = CODEC_I2C_Init(handle->i2cHandle, config->i2cConfig.codecI2CInstance, CS42888_I2C_BITRATE,
                                 config->i2cConfig.codecI2CSourceClock);
    if (errorStatus != (status_t)kStatus_HAL_I2cSuccess)
    {
        return errorStatus;
    }

    /* reset codec firstly */
    CS42888_Reset(handle, ((cs42888_config_t *)config)->reset);

    errorStatus = CS42888_WriteReg(handle, CS42888_POWER_CONTROL, 0x7F);
    if (errorStatus != kStatus_Success)
    {
        return errorStatus;
    }

    if (!config->master)
    {
        /* set as slave */
        errorStatus = CS42888_SelectFunctionalMode(handle, kCS42888_ModeSlave, kCS42888_ModeSlave);
        if (errorStatus != kStatus_Success)
        {
            return errorStatus;
        }
    }
    else
    {
        /* set as master */
        errorStatus = CS42888_SelectFunctionalMode(handle, config->ADCMode, config->DACMode);
        if (errorStatus != kStatus_Success)
        {
            return errorStatus;
        }
    }

    /* set protocol */
    errorStatus = CS42888_SetProtocol(handle, config->bus, config->format.bitWidth);
    if (errorStatus != kStatus_Success)
    {
        return errorStatus;
    }
    /* set data format */
    errorStatus =
        CS42888_ConfigDataFormat(handle, config->format.mclk_HZ, config->format.sampleRate, config->format.bitWidth);
    if (errorStatus != kStatus_Success)
    {
        return errorStatus;
    }
    /*Mute all DACs*/
    errorStatus = CS42888_WriteReg(handle, CS42888_CHANNEL_MUTE, 0xFF);
    if (errorStatus != kStatus_Success)
    {
        return errorStatus;
    }
    /*Set PDN as 0*/
    errorStatus = CS42888_WriteReg(handle, CS42888_POWER_CONTROL, 0x0);
    if (errorStatus != kStatus_Success)
    {
        return errorStatus;
    }
    errorStatus = CS42888_WriteReg(handle, CS42888_TRANSITION_CONTROL, 0x10);
    if (errorStatus != kStatus_Success)
    {
        return errorStatus;
    }
    /* Configure the codec AIN volume to 8db */
    for (i = 1; i <= 4U; i++)
    {
        errorStatus = CS42888_SetAINVolume(handle, i, 16);
        if (errorStatus != kStatus_Success)
        {
            return errorStatus;
        }
    }

    /*Delay and unmute*/
    return CS42888_WriteReg(handle, CS42888_CHANNEL_MUTE, 0x0);
}

status_t CS42888_SelectFunctionalMode(cs42888_handle_t *handle, cs42888_func_mode adcMode, cs42888_func_mode dacMode)
{
    if (CS42888_ModifyReg(handle, CS42888_FUNCTIONAL_MODE, CS42888_FUNCTIONAL_MODE_DAC_FM_MASK,
                          CS42888_FUNCTIONAL_MODE_DAC_FM(dacMode)) == kStatus_Success)
    {
        return CS42888_ModifyReg(handle, CS42888_FUNCTIONAL_MODE, CS42888_FUNCTIONAL_MODE_ADC_FM_MASK,
                                 CS42888_FUNCTIONAL_MODE_ADC_FM(adcMode));
    }

    return kStatus_Fail;
}

void CS42888_SetFuncMode(cs42888_handle_t *handle, cs42888_func_mode mode)
{
    (void)CS42888_ModifyReg(handle, CS42888_FUNCTIONAL_MODE, CS42888_FUNCTIONAL_MODE_DAC_FM_MASK,
                            CS42888_FUNCTIONAL_MODE_DAC_FM(mode));
    (void)CS42888_ModifyReg(handle, CS42888_FUNCTIONAL_MODE, CS42888_FUNCTIONAL_MODE_ADC_FM_MASK,
                            CS42888_FUNCTIONAL_MODE_ADC_FM(mode));
}

static void CS42888_Reset(cs42888_handle_t *handle, cs42888_reset codecReset)
{
    assert(codecReset != NULL);

    /* hold reset 0 */
    codecReset(false);
    /* delay 400ms */
    CS42888_DelayMs(400U);
    /* hold reset 0 */
    codecReset(true);
}

status_t CS42888_Deinit(cs42888_handle_t *handle)
{
    /* Disable all modules making CS42888 enter a low power mode */
    if (CS42888_WriteReg(handle, CS42888_FUNCTIONAL_MODE, 0U) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    return CODEC_I2C_Deinit(handle->i2cHandle);
}

status_t CS42888_SetProtocol(cs42888_handle_t *handle, cs42888_bus_t protocol, uint32_t bitWidth)
{
    uint8_t format       = 0U;
    status_t errorStatus = kStatus_Success;

    switch (protocol)
    {
        case kCS42888_BusLeftJustified:
            if (bitWidth <= 24U)
            {
                format = 0U;
            }
            else
            {
                errorStatus = kStatus_InvalidArgument;
            }
            break;

        case kCS42888_BusI2S:
            if (bitWidth <= 24U)
            {
                format = 0x09U;
            }
            else
            {
                errorStatus = kStatus_InvalidArgument;
            }
            break;

        case kCS42888_BusRightJustified:
            if (bitWidth == 24U)
            {
                format = 0x12U;
            }
            else if (bitWidth == 16U)
            {
                format = 0x1BU;
            }
            else
            {
                errorStatus = kStatus_InvalidArgument;
            }
            break;

        case kCS42888_BusOL1:
            if (bitWidth == 20U)
            {
                format = 0x24U;
            }
            else
            {
                errorStatus = kStatus_InvalidArgument;
            }
            break;

        case kCS42888_BusOL2:
            if (bitWidth == 24U)
            {
                format = 0x2DU;
            }
            else
            {
                errorStatus = kStatus_InvalidArgument;
            }
            break;

        case kCS42888_BusTDM:
            if (bitWidth == 24U)
            {
                format = 0x36U;
            }
            else
            {
                errorStatus = kStatus_InvalidArgument;
            }
            break;

        default:
            errorStatus = kStatus_InvalidArgument;
            break;
    }

    if (errorStatus == kStatus_Success)
    {
        errorStatus = CS42888_ModifyReg(handle, CS42888_INTERFACE_FORMATS, 0x3FU, format);
    }

    return errorStatus;
}

status_t CS42888_ConfigDataFormat(cs42888_handle_t *handle, uint32_t mclk, uint32_t sample_rate, uint32_t bits)
{
    status_t retval = kStatus_Success;

    uint8_t val    = 0;
    uint32_t ratio = mclk / sample_rate;

    if (CS42888_ReadReg(handle, CS42888_FUNCTIONAL_MODE, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    /* clear mfreq field */
    val &= (uint8_t)~0xEU;

    switch (ratio)
    {
        case 64:
            assert(CLOCK_RATE_IN_RANGE(sample_rate, 100000U, 200000U));
            assert(CLOCK_RATE_IN_RANGE(mclk, 1029000U, 12800000U));
            break;

        case 128:
            if (CLOCK_RATE_IN_RANGE(sample_rate, 100000U, 200000U) && CLOCK_RATE_IN_RANGE(mclk, 2048000U, 25600000U))
            {
                val |= 4U;
            }
            break;

        case 256:
            if (CLOCK_RATE_IN_RANGE(sample_rate, 50000U, 100000U) && CLOCK_RATE_IN_RANGE(mclk, 2048000U, 25600000U))
            {
                val |= 4U;
            }

            if (CLOCK_RATE_IN_RANGE(sample_rate, 100000U, 200000U) && CLOCK_RATE_IN_RANGE(mclk, 4096000U, 51200000U))
            {
                val |= 8U;
            }
            break;

        case 512:
            if (CLOCK_RATE_IN_RANGE(sample_rate, 4000U, 50000U) && CLOCK_RATE_IN_RANGE(mclk, 2048000U, 25600000U))
            {
                val |= 4U;
            }

            if (CLOCK_RATE_IN_RANGE(sample_rate, 50000U, 100000U) && CLOCK_RATE_IN_RANGE(mclk, 4096000U, 51200000U))
            {
                val |= 8U;
            }
            break;

        case 1024:
            assert(CLOCK_RATE_IN_RANGE(mclk, 4096000U, 51200000U));
            assert(CLOCK_RATE_IN_RANGE(sample_rate, 4000U, 50000U));
            val |= 8U;
            break;

        default:
            assert(false);
            break;
    }

    retval = CS42888_WriteReg(handle, CS42888_FUNCTIONAL_MODE, val);

    return retval;
}

status_t CS42888_SetModule(cs42888_handle_t *handle, cs42888_module_t module, bool isEnabled)
{
    status_t ret = kStatus_Success;
    uint8_t val  = 0;

    /* Read Power control register value */
    if (CS42888_ReadReg(handle, CS42888_POWER_CONTROL, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    if (isEnabled)
    {
        val |= (uint8_t)module;
    }
    else
    {
        val &= ~(uint8_t)module;
    }

    ret = CS42888_WriteReg(handle, CS42888_POWER_CONTROL, val);
    return ret;
}

status_t CS42888_SetAOUTVolume(cs42888_handle_t *handle, uint8_t channel, uint8_t volume)
{
    status_t ret = kStatus_Success;
    uint8_t reg  = CS42888_VOL_CONTROL_AOUT1 + (channel - 1U);

    if ((channel < 1U) || (channel > 8U))
    {
        ret = kStatus_Fail;
    }
    else
    {
        ret = CS42888_WriteReg(handle, reg, volume);
    }
    return ret;
}

status_t CS42888_SetAINVolume(cs42888_handle_t *handle, uint8_t channel, uint8_t volume)
{
    status_t ret = kStatus_Success;
    uint8_t reg  = CS42888_VOL_CONTROL_AIN1 + (channel - 1U);

    if ((channel < 1U) || (channel > 4U))
    {
        ret = kStatus_Fail;
    }
    else
    {
        ret = CS42888_WriteReg(handle, reg, volume);
    }
    return ret;
}

uint8_t CS42888_GetAOUTVolume(cs42888_handle_t *handle, uint8_t channel)
{
    uint8_t val = 0;
    uint8_t reg = CS42888_VOL_CONTROL_AOUT1 + (channel - 1U);
    if ((channel < 1U) || (channel > 8U))
    {
        val = 0;
    }
    else
    {
        (void)CS42888_ReadReg(handle, reg, &val);
    }
    return val;
}

uint8_t CS42888_GetAINVolume(cs42888_handle_t *handle, uint8_t channel)
{
    uint8_t val = 0;
    uint8_t reg = CS42888_VOL_CONTROL_AIN1 + (channel - 1U);
    if ((channel < 1U) || (channel > 4U))
    {
        val = 0;
    }
    else
    {
        (void)CS42888_ReadReg(handle, reg, &val);
    }
    return val;
}

status_t CS42888_SetMute(cs42888_handle_t *handle, uint8_t channelMask)
{
    status_t ret = kStatus_Success;

    ret = CS42888_WriteReg(handle, CS42888_CHANNEL_MUTE, channelMask);
    return ret;
}

status_t CS42888_SetChannelMute(cs42888_handle_t *handle, uint8_t channel, bool isMute)
{
    assert(channel >= (uint8_t)kCS42888_AOUT1);

    status_t ret = kStatus_Success;

    uint8_t val = 0U;

    ret = CS42888_ReadReg(handle, CS42888_CHANNEL_MUTE, &val);
    if (ret != kStatus_Success)
    {
        return ret;
    }

    if (isMute)
    {
        val |= 1U << (channel - 1U);
    }
    else
    {
        val &= ~(1U << (channel - 1u));
    }

    return CS42888_WriteReg(handle, CS42888_CHANNEL_MUTE, val);
    ;
}

status_t CS42888_WriteReg(cs42888_handle_t *handle, uint8_t reg, uint8_t val)
{
    assert(handle->config != NULL);

    return CODEC_I2C_Send(handle->i2cHandle, handle->config->slaveAddress, reg, 1U, &val, 1U);
}

status_t CS42888_ReadReg(cs42888_handle_t *handle, uint8_t reg, uint8_t *val)
{
    assert(handle->config != NULL);

    return CODEC_I2C_Receive(handle->i2cHandle, handle->config->slaveAddress, reg, 1U, val, 1U);
}

status_t CS42888_ModifyReg(cs42888_handle_t *handle, uint8_t reg, uint8_t mask, uint8_t val)
{
    uint8_t reg_val = 0;

    if (CS42888_ReadReg(handle, reg, &reg_val) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    reg_val &= (uint8_t)~mask;
    reg_val |= val;

    return CS42888_WriteReg(handle, reg, reg_val);
}
