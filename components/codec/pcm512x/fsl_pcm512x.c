/*
 * Copyright 2021-2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_pcm512x.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
status_t PCM512x_WriteReg(pcm512x_handle_t *handle, uint8_t reg, uint8_t val)
{
    assert(handle->config != NULL);

    return CODEC_I2C_Send(handle->i2cHandle, handle->config->slaveAddress, reg, 1U, &val, 1U);
}

status_t PCM512x_ReadReg(pcm512x_handle_t *handle, uint8_t reg, uint8_t *val)
{
    assert(handle->config != NULL);

    return CODEC_I2C_Receive(handle->i2cHandle, handle->config->slaveAddress, reg, 1U, val, 1U);
}

status_t PCM512x_ModifyReg(pcm512x_handle_t *handle, uint8_t reg, uint8_t mask, uint8_t val)
{
    uint8_t old, new;

    assert(handle->config != NULL);

    if (PCM512x_ReadReg(handle, reg, &old) != kStatus_Success) {
        return kStatus_Fail;
    }

    new = (old & (~mask)) | (val & mask);

    return PCM512x_WriteReg(handle, reg, new);
}


static status_t dac_pcm512x_set_gpio_val(pcm512x_handle_t *handle, int gpio_nr, int val)
{
    status_t ret = kStatus_Success;
    uint8_t gpio_bit = 1 << (gpio_nr - 1);
    uint8_t gpio_output_reg;

    switch (gpio_nr) {
        case 3:
            gpio_output_reg = PCM512x_GPIO_OUTPUT_3;
            break;
        case 4:
            gpio_output_reg = PCM512x_GPIO_OUTPUT_4;
            break;
        case 6:
            gpio_output_reg = PCM512x_GPIO_OUTPUT_6;
            break;
        default:
            ret = kStatus_InvalidArgument;
            goto end;
    }

    /* Enable gpio */
    ret = PCM512x_ModifyReg(handle, PCM512x_GPIO_EN, gpio_bit, gpio_bit);
    if (ret != kStatus_Success) goto end;

    /* Set pinmux to gpio */
    ret = PCM512x_ModifyReg(handle, gpio_output_reg, 0xf, 2);
    if (ret != kStatus_Success) goto end;

    /* Set gpio value */
    ret = PCM512x_ModifyReg(handle, PCM512x_GPIO_CONTROL_1, gpio_bit, val ? gpio_bit : 0);
    if (ret != kStatus_Success) goto end;

end:
    return ret;
}

static status_t dac_pcm512x_set_gpio(pcm512x_handle_t *handle, int gpio_nr)
{
    return dac_pcm512x_set_gpio_val(handle, gpio_nr, 1);
}

static status_t dac_pcm512x_clear_gpio(pcm512x_handle_t *handle, int gpio_nr)
{
    return dac_pcm512x_set_gpio_val(handle, gpio_nr, 0);
}

#define CLK_48000 (48000 * 512)
#define CLK_44100 (44100 * 512)

static int dac_pcm512x_get_dac_rate(int sample_rate)
{
    int dr;

    switch (sample_rate) {
        case kPCM512x_AudioSampleRate44100Hz:
        case kPCM512x_AudioSampleRate88200Hz:
        case kPCM512x_AudioSampleRate176400Hz:
            dr = 5644800;
            break;
        case kPCM512x_AudioSampleRate48KHz:
        case kPCM512x_AudioSampleRate96KHz:
        case kPCM512x_AudioSampleRate192KHz:
            dr = 6144000;
            break;
        default:
            dr = -1;
            break;
    }

    return dr;
}

static uint8_t dac_pcm512x_get_dac_div(int sample_rate)
{
    int dd;
    int u, d;

    switch (sample_rate) {
        case kPCM512x_AudioSampleRate44100Hz:
        case kPCM512x_AudioSampleRate88200Hz:
        case kPCM512x_AudioSampleRate176400Hz:
            u = CLK_44100;
            break;
        case kPCM512x_AudioSampleRate48KHz:
        case kPCM512x_AudioSampleRate96KHz:
        case kPCM512x_AudioSampleRate192KHz:
            u = CLK_48000;
            break;
        default:
            dd = -1;
            goto end;
    };

    d = dac_pcm512x_get_dac_rate(sample_rate);
    dd = (u + d / 2) / d;

end:
    return dd;
}

static int dac_pcm512x_get_idac(int sample_rate, uint8_t dsp_div)
{
    int idac;
    int u;

    switch (sample_rate) {
        case kPCM512x_AudioSampleRate44100Hz:
        case kPCM512x_AudioSampleRate88200Hz:
        case kPCM512x_AudioSampleRate176400Hz:
            u = CLK_44100;
            break;
        case kPCM512x_AudioSampleRate48KHz:
        case kPCM512x_AudioSampleRate96KHz:
        case kPCM512x_AudioSampleRate192KHz:
            u = CLK_48000;
            break;
        default:
            idac = -1;
            goto end;
    }

    idac = u / (sample_rate * dsp_div);

end:
    return idac;
}

static uint8_t dac_pcm512x_get_bclk_div(int sample_rate, uint8_t lrclk_div)
{
    uint8_t bclk_div;
    int u;

    switch (sample_rate) {
        case kPCM512x_AudioSampleRate44100Hz:
        case kPCM512x_AudioSampleRate88200Hz:
        case kPCM512x_AudioSampleRate176400Hz:
            u = CLK_44100;
            break;
        case kPCM512x_AudioSampleRate48KHz:
        case kPCM512x_AudioSampleRate96KHz:
        case kPCM512x_AudioSampleRate192KHz:
            u = CLK_48000;
            break;
        default:
            bclk_div = 0;
            goto end;
    }

    bclk_div = (uint8_t )(u / (sample_rate * lrclk_div));

end:
    return bclk_div;
}

static uint8_t dac_pcm512x_get_fssp(int sample_rate)
{
    uint8_t fssp;

    switch (sample_rate) {
        case kPCM512x_AudioSampleRate44100Hz:
        case kPCM512x_AudioSampleRate48KHz:
            fssp = PCM512x_FSSP_48KHZ;
            break;
        case kPCM512x_AudioSampleRate88200Hz:
        case kPCM512x_AudioSampleRate96KHz:
            fssp = PCM512x_FSSP_96KHZ;
            break;
        case kPCM512x_AudioSampleRate176400Hz:
        case kPCM512x_AudioSampleRate192KHz:
            fssp = PCM512x_FSSP_192KHZ;
            break;
        default:
            fssp = 0;
            goto end;
    }

end:
    return fssp;
}

status_t PCM512x_SetFormat(pcm512x_handle_t *handle, uint32_t mclk, uint32_t sampleRate, uint32_t bitWidth)
{
    status_t ret = kStatus_Success;
    uint8_t alen, lrclk_div, bclk_div, dsp_div, dac_div, ncp_div, osr_div, fssp;
    int dac_rate, idac;

    if ((sampleRate != kPCM512x_AudioSampleRate44100Hz) &&
        (sampleRate != kPCM512x_AudioSampleRate88200Hz) &&
        (sampleRate != kPCM512x_AudioSampleRate176400Hz) &&
        (sampleRate != kPCM512x_AudioSampleRate48KHz) &&
        (sampleRate != kPCM512x_AudioSampleRate96KHz) &&
        (sampleRate != kPCM512x_AudioSampleRate192KHz)) {
        ret = kStatus_InvalidArgument;
        goto end;
    }

    /* Turn DAC on */
    ret = PCM512x_ModifyReg(handle,
            PCM512x_POWER,
            PCM512x_RQPD,
            0);

    /* Enable 44.1kHz or 48kHz oscillator depending on sampling rate */
    if (sampleRate % 8000) {
        /* Enable 44.1kHz oscillator on Hifiberry card */
        ret = dac_pcm512x_set_gpio(handle, handle->config->gpio_osc44);
        /* Clear 48kHz oscillator on Hifiberry card */
        ret = dac_pcm512x_clear_gpio(handle, handle->config->gpio_osc48);
    }
    else {
        /* Enable 48kHz oscillator on Hifiberry card */
        ret = dac_pcm512x_set_gpio(handle, handle->config->gpio_osc48);
        /* Clear 44.1kHz oscillator on Hifiberry card */
        ret = dac_pcm512x_clear_gpio(handle, handle->config->gpio_osc44);
    }
    if (ret != kStatus_Success) goto end;

    switch (bitWidth) {
        case kPCM512x_AudioBitWidth16bit:
            alen = PCM512x_ALEN_16;
            break;
        case kPCM512x_AudioBitWidth24bit:
            alen = PCM512x_ALEN_24;
            break;
        case kPCM512x_AudioBitWidth32bit:
            alen = PCM512x_ALEN_32;
            break;
        default:
            ret = kStatus_InvalidArgument;
            goto end;
    }

    ret = PCM512x_ModifyReg(handle,
            PCM512x_I2S_1,
            PCM512x_ALEN,
            alen);

    ret = PCM512x_ModifyReg(handle,
            PCM512x_ERROR_DETECT,
            PCM512x_IDFS | PCM512x_IDBK | PCM512x_IDSK | PCM512x_IDCH
            | PCM512x_IDCM | PCM512x_DCAS | PCM512x_IPLK,
            PCM512x_IDFS | PCM512x_IDBK | PCM512x_IDSK | PCM512x_IDCH
            | PCM512x_DCAS | PCM512x_IPLK);
    if (ret != kStatus_Success) goto end;

    ret = PCM512x_ModifyReg(handle,
            PCM512x_PLL_EN,
            PCM512x_PLLE,
            0);
    if (ret != kStatus_Success) goto end;

    ret= PCM512x_ModifyReg(handle,
            PCM512x_DAC_REF,
            PCM512x_SDAC,
            PCM512x_SDAC_SCK);
    if (ret != kStatus_Success) goto end;

    dsp_div = 1; /* mclk < 50Mhz, so no need to divide DSP clk */
    ret = PCM512x_WriteReg(handle, PCM512x_DSP_CLKDIV, dsp_div - 1);
    if (ret != kStatus_Success) goto end;

    dac_rate = dac_pcm512x_get_dac_rate(sampleRate);
    dac_div = dac_pcm512x_get_dac_div(sampleRate);
    ret = PCM512x_WriteReg(handle, PCM512x_DAC_CLKDIV, dac_div - 1);
    if (ret != kStatus_Success) goto end;

    ncp_div = (uint8_t)((dac_rate + 768000) / 1536000);
    ret = PCM512x_WriteReg(handle, PCM512x_NCP_CLKDIV, ncp_div - 1);
    if (ret != kStatus_Success) goto end;

    osr_div = (uint8_t)(dac_rate / (sampleRate * 16));
    ret = PCM512x_WriteReg(handle, PCM512x_OSR_CLKDIV, osr_div - 1);
    if (ret != kStatus_Success) goto end;

    lrclk_div = bitWidth * 2;
    bclk_div = dac_pcm512x_get_bclk_div(sampleRate, lrclk_div);
    ret = PCM512x_WriteReg(handle, PCM512x_MASTER_CLKDIV_1, bclk_div - 1);
    if (ret != kStatus_Success) goto end;
    ret = PCM512x_WriteReg(handle, PCM512x_MASTER_CLKDIV_2, lrclk_div - 1);
    if (ret != kStatus_Success) goto end;

    idac = dac_pcm512x_get_idac(sampleRate, dsp_div);
    ret = PCM512x_WriteReg(handle, PCM512x_IDAC_1, idac >> 8);
    if (ret != kStatus_Success) goto end;
    ret = PCM512x_WriteReg(handle, PCM512x_IDAC_2, idac & 0xff);
    if (ret != kStatus_Success) goto end;

    fssp = dac_pcm512x_get_fssp(sampleRate);
    ret = PCM512x_ModifyReg(handle,
            PCM512x_FS_SPEED_MODE,
            PCM512x_FSSP,
            fssp);
    if (ret != kStatus_Success) goto end;

    ret = PCM512x_ModifyReg(handle,
            PCM512x_BCLK_LRCLK_CFG,
            PCM512x_BCKP | PCM512x_BCKO | PCM512x_LRKO,
            PCM512x_BCKO | PCM512x_LRKO);
    if (ret != kStatus_Success) goto end;

    ret = PCM512x_ModifyReg(handle,
            PCM512x_MASTER_MODE,
            PCM512x_RLRK | PCM512x_RBCK,
            PCM512x_RLRK | PCM512x_RBCK);
    if (ret != kStatus_Success) goto end;

    ret = PCM512x_ModifyReg(handle,
            PCM512x_SYNCHRONIZE,
            PCM512x_RQSY,
            PCM512x_RQSY_HALT);
    if (ret != kStatus_Success) goto end;

    ret = PCM512x_ModifyReg(handle,
            PCM512x_SYNCHRONIZE,
            PCM512x_RQSY,
            PCM512x_RQSY_RESUME);
    if (ret != kStatus_Success) goto end;

    /* Normal operation mode */
    ret = PCM512x_ModifyReg(handle,
            PCM512x_POWER,
            PCM512x_RQST,
            0);
    if (ret != kStatus_Success) goto end;

    /* Unmute codec */
    ret = PCM512x_SetMute(handle, false);
    if (ret != kStatus_Success) goto end;

end:
    return ret;
}

status_t PCM512x_SetMute(pcm512x_handle_t *handle, bool isEnabled)
{
    status_t ret = kStatus_Success;

    if (isEnabled) {
        ret = PCM512x_ModifyReg(handle,
                PCM512x_MUTE,
                PCM512x_RQML | PCM512x_RQMR,
                PCM512x_RQML | PCM512x_RQMR);
    }
    else {
        ret = PCM512x_ModifyReg(handle,
                PCM512x_MUTE,
                PCM512x_RQML | PCM512x_RQMR,
                0);
    }

    return ret;
}

status_t PCM512x_Init(pcm512x_handle_t *handle, const pcm512x_config_t *config)
{
    status_t ret = kStatus_Success;

    handle->config  = config;

    /* i2c bus initialization */
    if (CODEC_I2C_Init(handle->i2cHandle, config->i2cConfig.codecI2CInstance, PCM512X_I2C_BAUDRATE,
                       config->i2cConfig.codecI2CSourceClock) != (status_t)kStatus_HAL_I2cSuccess)
    {
        return kStatus_Fail;
    }

    /* Mute codec */
    ret = PCM512x_SetMute(handle, true);
    if (ret != kStatus_Success) goto end;

    /* Reset codec */
    ret = PCM512x_WriteReg(handle,
            PCM512x_RESET,
            PCM512x_RSTM | PCM512x_RSTR);
    if (ret != kStatus_Success) goto end;
    ret = PCM512x_WriteReg(handle,
            PCM512x_RESET,
            0);
    if (ret != kStatus_Success) goto end;

    /* Default to standby mode */
    ret = PCM512x_ModifyReg(handle,
            PCM512x_POWER,
            PCM512x_RQST,
            PCM512x_RQST);
    if (ret != kStatus_Success) goto end;

    /* Turn PCM5122 LED GPIO ON */
    ret = dac_pcm512x_set_gpio(handle, config->gpio_led);

end:
    return ret;
}

status_t PCM512x_Deinit(pcm512x_handle_t *handle)
{
    status_t ret;

    /* Reinit I2C in case it has been stopped by concurrent codec driver */
    if (CODEC_I2C_Init(handle->i2cHandle, handle->config->i2cConfig.codecI2CInstance, PCM512X_I2C_BAUDRATE,
                       handle->config->i2cConfig.codecI2CSourceClock) != (status_t)kStatus_HAL_I2cSuccess)
        return kStatus_Fail;

    /* Mute codec */
    ret = PCM512x_SetMute(handle, true);
    if (ret != kStatus_Success) goto end;

    /* Turn PCM5122 LED GPIO OFF */
    ret = dac_pcm512x_clear_gpio(handle, handle->config->gpio_led);
    if (ret != kStatus_Success) goto end;

    ret = CODEC_I2C_Deinit(handle->i2cHandle);

end:
    return ret;
}
