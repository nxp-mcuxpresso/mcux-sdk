/*
 * Copyright 2021 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_pcm186x.h"

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
status_t PCM186x_WriteReg(pcm186x_handle_t *handle, uint8_t reg, uint8_t val)
{
    assert(handle->config != NULL);

    return CODEC_I2C_Send(handle->i2cHandle, handle->config->slaveAddress, reg, 1U, &val, 1U);
}

status_t PCM186x_ReadReg(pcm186x_handle_t *handle, uint8_t reg, uint8_t *val)
{
    assert(handle->config != NULL);

    return CODEC_I2C_Receive(handle->i2cHandle, handle->config->slaveAddress, reg, 1U, val, 1U);
}

status_t PCM186x_ModifyReg(pcm186x_handle_t *handle, uint8_t reg, uint8_t mask, uint8_t val)
{
    uint8_t old, new;

    assert(handle->config != NULL);

    if (PCM186x_ReadReg(handle, reg, &old) != kStatus_Success) {
        return kStatus_Fail;
    }

    new = (old & (~mask)) | (val & mask);

    return PCM186x_WriteReg(handle, reg, new);
}


static status_t dac_pcm186x_set_gpio_val(pcm186x_handle_t *handle, int gpio_nr, int val)
{
    status_t ret = kStatus_Success;

    switch (gpio_nr) {
        case 0:
            /* Set muxmode to gpio */
            ret = PCM186x_ModifyReg(handle,
                    PCM186X_GPIO1_0_CTRL,
                    PCM186X_GPIO0_FUNC,
                    0);
            if (ret != kStatus_Success) goto end;

            /* Set gpio as output */
            ret = PCM186x_ModifyReg(handle,
                    PCM186X_GPIO1_0_DIR_CTRL,
                    PCM186X_GPIO0_DIR,
                    0);
            if (ret != kStatus_Success) goto end;

            break;
        case 1:
            /* Set muxmode to gpio */
            ret = PCM186x_ModifyReg(handle,
                    PCM186X_GPIO1_0_CTRL,
                    PCM186X_GPIO1_FUNC,
                    0);
            if (ret != kStatus_Success) goto end;

            /* Set gpio as output */
            ret = PCM186x_ModifyReg(handle,
                    PCM186X_GPIO1_0_DIR_CTRL,
                    PCM186X_GPIO1_DIR,
                    4 << 4);
            if (ret != kStatus_Success) goto end;

            break;
       case 2:
            /* Set muxmode to gpio */
            ret = PCM186x_ModifyReg(handle,
                    PCM186X_GPIO3_2_CTRL,
                    PCM186X_GPIO2_FUNC,
                    0);
            if (ret != kStatus_Success) goto end;

            /* Set gpio as output */
            ret = PCM186x_ModifyReg(handle,
                    PCM186X_GPIO3_2_DIR_CTRL,
                    PCM186X_GPIO2_DIR,
                    4);
            if (ret != kStatus_Success) goto end;

            break;
        case 3:
            /* Set muxmode to gpio */
            ret = PCM186x_ModifyReg(handle,
                    PCM186X_GPIO3_2_CTRL,
                    PCM186X_GPIO3_FUNC,
                    0);
            if (ret != kStatus_Success) goto end;

            /* Set gpio as output */
            ret = PCM186x_ModifyReg(handle,
                    PCM186X_GPIO3_2_DIR_CTRL,
                    PCM186X_GPIO3_DIR,
                    4 << 4);
            if (ret != kStatus_Success) goto end;

            break;
        default:
            ret = kStatus_InvalidArgument;
            goto end;
    }

    /* Set / clear gpio */
    ret = PCM186x_ModifyReg(handle,
            PCM186X_GPIO_IN_OUT,
            1 << (gpio_nr + 4),
            val ? 1 << (gpio_nr + 4) : 0);

end:
    return ret;
}

static status_t dac_pcm186x_set_gpio(pcm186x_handle_t *handle, int gpio_nr)
{
    return dac_pcm186x_set_gpio_val(handle, gpio_nr, 1);
}

static status_t dac_pcm186x_clear_gpio(pcm186x_handle_t *handle, int gpio_nr)
{
    return dac_pcm186x_set_gpio_val(handle, gpio_nr, 0);
}

status_t PCM186x_SetFormat(pcm186x_handle_t *handle, uint32_t mclk, uint32_t sampleRate, uint32_t bitWidth)
{
    status_t ret = kStatus_Success;
    uint8_t fmt, wlen;

    fmt = PCM186X_FMT_I2S;

    switch (bitWidth) {
        case kPCM186x_AudioBitWidth16bit:
            wlen = PCM186X_WLEN_16;
            break;
        case kPCM186x_AudioBitWidth24bit:
            wlen = PCM186X_WLEN_24;
            break;
        case kPCM186x_AudioBitWidth32bit:
            wlen = PCM186X_WLEN_32;
            break;
        default:
            ret = kStatus_InvalidArgument;
            goto end;
    }

    /* Set slave mode */
    ret = PCM186x_ModifyReg(handle,
            PCM186X_CLK_CTRL,
            PCM186X_MST_MODE,
            0);
    if (ret != kStatus_Success) goto end;

    /* TODO: probably useless as we are not in DSP format */
    ret = PCM186x_WriteReg(handle, PCM186X_TDM_TX_OFFSET, 0);
    if (ret != kStatus_Success) goto end;

    /* Set format */
    ret = PCM186x_ModifyReg(handle,
            PCM186X_PCM_CFG,
            PCM186X_FMT,
            fmt);
    if (ret != kStatus_Success) goto end;

    /* Set word length */
    ret = PCM186x_ModifyReg(handle,
            PCM186X_PCM_CFG,
            PCM186X_RX_WLEN | PCM186X_TX_WLEN,
            (wlen << 6) | (wlen << 2));
    if (ret != kStatus_Success) goto end;

    /* Power up analog */
    ret = PCM186x_ModifyReg(handle,
            PCM186X_POWER_CTRL,
            PCM186X_PWRDN,
            0);

end:
    return ret;
}

status_t PCM186x_Init(pcm186x_handle_t *handle, const pcm186x_config_t *config)
{
    status_t ret = kStatus_Success;

    handle->config  = config;

    /* i2c bus initialization */
    if (CODEC_I2C_Init(handle->i2cHandle, config->i2cConfig.codecI2CInstance, PCM186X_I2C_BAUDRATE,
                       config->i2cConfig.codecI2CSourceClock) != (status_t)kStatus_HAL_I2cSuccess)
    {
        return kStatus_Fail;
    }

    /* Reset ADC */
    ret = PCM186x_WriteReg(handle, PCM186X_REG_00, PCM186X_RESET);
    if (ret != kStatus_Success) goto end;

    /* Turn PCM1863 LED GPIO ON */
    ret = dac_pcm186x_set_gpio(handle, config->gpio_led);

end:
    return ret;
}

status_t PCM186x_Deinit(pcm186x_handle_t *handle)
{
    status_t ret;

    /* Reinit I2C in case it has been stopped by concurrent codec driver */
    if (CODEC_I2C_Init(handle->i2cHandle, handle->config->i2cConfig.codecI2CInstance, PCM186X_I2C_BAUDRATE,
                handle->config->i2cConfig.codecI2CSourceClock) != (status_t)kStatus_HAL_I2cSuccess)
        return kStatus_Fail;

    /* Power down analog */
    ret = PCM186x_ModifyReg(handle,
            PCM186X_POWER_CTRL,
            PCM186X_PWRDN,
            1);
    if (ret != kStatus_Success) goto end;

    /* Turn PCM1863 LED GPIO OFF */
    ret = dac_pcm186x_clear_gpio(handle, handle->config->gpio_led);
    if (ret != kStatus_Success) goto end;

    ret = CODEC_I2C_Deinit(handle->i2cHandle);

end:
    return ret;
}
