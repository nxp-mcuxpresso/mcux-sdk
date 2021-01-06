/*
 * Copyright 2018-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_ak4497.h"

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
static void Delay(void)
{
    uint32_t i;
    for (i = 0; i < 1000U; i++)
    {
        __NOP();
    }
}

void AK4497_DefaultConfig(ak4497_config_t *config)
{
    config->ak4497Mode      = kAK4497_PcmMode;
    config->dataChannelMode = kAK4497_NormalMode;
    /* PCM mode setting. */
    config->pcmConfig.pcmSampleFreqMode = kAK4497_AutoSettingMode;
    config->pcmConfig.pcmSdataFormat    = kAK4497_32BitI2S;
    config->pcmConfig.pcmTdmMode        = kAK4497_Normal;
    config->pcmConfig.pcmSdsSlot        = kAK4497_L1R1;
    /* DSD mode setting. */
    config->dsdConfig.dsdMclk         = kAK4497_mclk512fs;
    config->dsdConfig.dsdPath         = kAK4497_Path1;
    config->dsdConfig.dsdPlaybackPath = kAK4497_NormalPath;
    config->dsdConfig.dsdDataMute     = kAK4497_DsdMuteDisable;
    config->dsdConfig.dsdDclkPolarity = kAK4497_FallingEdge;
}

status_t AK4497_Init(ak4497_handle_t *handle, ak4497_config_t *config)
{
    assert(handle != NULL);
    assert(config != NULL);
    status_t ret = kStatus_Success;

    handle->config = config;

    /* i2c bus initialization */
    if (CODEC_I2C_Init(handle->i2cHandle, config->i2cConfig.codecI2CInstance, AK4497_I2C_BITRATE,
                       config->i2cConfig.codecI2CSourceClock) != (status_t)kStatus_HAL_I2cSuccess)
    {
        return kStatus_Fail;
    }

    ret = AK4497_ModifyReg(handle, AK4497_CONTROL2, AK4497_CONTROL2_SMUTE_MASK,
                           1U << AK4497_CONTROL2_SMUTE_SHIFT); /* Soft ware mute */

    ret = AK4497_ModifyReg(handle, AK4497_CONTROL1,
                           AK4497_CONTROL1_DIF0_MASK | AK4497_CONTROL1_DIF1_MASK | AK4497_CONTROL1_DIF2_MASK,
                           (uint8_t)config->pcmConfig.pcmSdataFormat << AK4497_CONTROL1_DIF0_SHIFT);
    ret = AK4497_ModifyReg(handle, AK4497_CONTROL3, AK4497_CONTROL3_SELLR_MASK,
                           (uint8_t)config->dataChannelMode << AK4497_CONTROL3_SELLR_SHIFT);
    if (config->ak4497Mode == kAK4497_PcmMode) /* PCM mode*/
    {
        if (config->pcmConfig.pcmSampleFreqMode != kAK4497_ManualSettingMode)
        {
            if (config->pcmConfig.pcmSampleFreqMode == kAK4497_AutoSettingMode)
            {
                ret = AK4497_ModifyReg(handle, AK4497_CONTROL1, AK4497_CONTROL1_AFSD_MASK,
                                       0U << AK4497_CONTROL1_AFSD_SHIFT); /*Auto setting mode*/
                ret = AK4497_ModifyReg(handle, AK4497_CONTROL1, AK4497_CONTROL1_ACKS_MASK,
                                       1U << AK4497_CONTROL1_ACKS_SHIFT);
            }
            else
            {
                ret = AK4497_ModifyReg(handle, AK4497_CONTROL1, AK4497_CONTROL1_AFSD_MASK,
                                       1U << AK4497_CONTROL1_AFSD_SHIFT); /* Auto Detect mode*/
                ret = AK4497_ModifyReg(handle, AK4497_CONTROL1, AK4497_CONTROL1_ACKS_MASK,
                                       0U << AK4497_CONTROL1_ACKS_SHIFT);
            }
        }
        ret = AK4497_ModifyReg(handle, AK4497_CONTROL7, AK4497_CONTROL7_TDM0_MASK | AK4497_CONTROL7_TDM1_MASK,
                               (uint8_t)config->pcmConfig.pcmTdmMode << AK4497_CONTROL7_TDM0_SHIFT);
        ret = AK4497_ModifyReg(handle, AK4497_CONTROL8, AK4497_CONTROL8_SDS0_MASK,
                               ((uint8_t)config->pcmConfig.pcmSdsSlot & 0x1U) << AK4497_CONTROL8_SDS0_SHIFT);
        ret = AK4497_ModifyReg(handle, AK4497_CONTROL7, AK4497_CONTROL7_SDS1_MASK,
                               (((uint8_t)config->pcmConfig.pcmSdsSlot & 0x2U) >> 1U) << AK4497_CONTROL7_SDS1_SHIFT);
        ret = AK4497_ModifyReg(handle, AK4497_CONTROL7, AK4497_CONTROL7_SDS2_MASK,
                               (((uint8_t)config->pcmConfig.pcmSdsSlot & 0x4U) >> 2U) << AK4497_CONTROL7_SDS2_SHIFT);
    }

    else if (config->ak4497Mode == kAK4497_DsdMode) /*DSD mode*/
    {
        ret = AK4497_ModifyReg(handle, AK4497_CONTROL1, AK4497_CONTROL1_EXDF_MASK, 0U << AK4497_CONTROL1_EXDF_SHIFT);
        ret = AK4497_ModifyReg(handle, AK4497_CONTROL3, AK4497_CONTROL3_DP_MASK, 1U << AK4497_CONTROL3_DP_SHIFT);
        ret = AK4497_ModifyReg(handle, AK4497_CONTROL3, AK4497_CONTROL3_DCKS_MASK,
                               (uint8_t)config->dsdConfig.dsdMclk << AK4497_CONTROL3_DCKS_SHIFT);
        ret = AK4497_ModifyReg(handle, AK4497_DSD2, AK4497_DSD2_DSDPATH_MASK,
                               (uint8_t)config->dsdConfig.dsdPath << AK4497_DSD2_DSDPATH_SHIFT);
        ret = AK4497_ModifyReg(handle, AK4497_DSD1, AK4497_DSD1_DSDD_MASK,
                               (uint8_t)config->dsdConfig.dsdPlaybackPath << AK4497_DSD1_DSDD_SHIFT);
        ret = AK4497_ModifyReg(handle, AK4497_DSD1, AK4497_DSD1_DDM_MASK,
                               (uint8_t)config->dsdConfig.dsdDataMute << AK4497_DSD1_DDM_SHIFT);
        ret = AK4497_ModifyReg(handle, AK4497_CONTROL3, AK4497_CONTROL3_DCKB_MASK,
                               (uint8_t)config->dsdConfig.dsdDclkPolarity << AK4497_CONTROL3_DCKB_SHIFT);
    }
    else /* EXDF mode*/
    {
        ret = AK4497_ModifyReg(handle, AK4497_CONTROL1, AK4497_CONTROL1_EXDF_MASK, 1U << AK4497_CONTROL1_EXDF_SHIFT);
        ret = AK4497_ModifyReg(handle, AK4497_CONTROL3, AK4497_CONTROL3_DP_MASK, 0U << AK4497_CONTROL3_DP_SHIFT);
    }

    ret = AK4497_ModifyReg(handle, AK4497_CONTROL2, AK4497_CONTROL2_SMUTE_MASK,
                           0U << AK4497_CONTROL2_SMUTE_SHIFT); /* Normal Operation */

    ret = AK4497_ModifyReg(handle, AK4497_CONTROL1, AK4497_CONTROL1_RSTN_MASK,
                           0U << AK4497_CONTROL1_RSTN_SHIFT); /* Rest the ak4497 */
    Delay(); /* Need to wait to ensure the ak4497 has updated the above registers. */
    ret = AK4497_ModifyReg(handle, AK4497_CONTROL1, AK4497_CONTROL1_RSTN_MASK,
                           1U << AK4497_CONTROL1_RSTN_SHIFT); /* Normal Operation */
    Delay();

    return ret;
}

status_t AK4497_SetEncoding(ak4497_handle_t *handle, uint8_t format)
{
    ak4497_config_t *config = (ak4497_config_t *)handle->config;
    status_t ret            = kStatus_Success;

    if (format == (uint8_t)kAK4497_DsdMode)
    {
        ret = AK4497_ModifyReg(handle, AK4497_CONTROL1, AK4497_CONTROL1_EXDF_MASK, 0U << AK4497_CONTROL1_EXDF_SHIFT);
        ret = AK4497_ModifyReg(handle, AK4497_CONTROL3, AK4497_CONTROL3_DP_MASK, 1U << AK4497_CONTROL3_DP_SHIFT);
        ret = AK4497_ModifyReg(handle, AK4497_CONTROL3, AK4497_CONTROL3_DCKS_MASK,
                               (uint8_t)config->dsdConfig.dsdMclk << AK4497_CONTROL3_DCKS_SHIFT);
        ret = AK4497_ModifyReg(handle, AK4497_DSD2, AK4497_DSD2_DSDPATH_MASK,
                               (uint8_t)config->dsdConfig.dsdPath << AK4497_DSD2_DSDPATH_SHIFT);
        ret = AK4497_ModifyReg(handle, AK4497_DSD1, AK4497_DSD1_DSDD_MASK,
                               (uint8_t)config->dsdConfig.dsdPlaybackPath << AK4497_DSD1_DSDD_SHIFT);
        ret = AK4497_ModifyReg(handle, AK4497_DSD1, AK4497_DSD1_DDM_MASK,
                               (uint8_t)config->dsdConfig.dsdDataMute << AK4497_DSD1_DDM_SHIFT);
        ret = AK4497_ModifyReg(handle, AK4497_CONTROL3, AK4497_CONTROL3_DCKB_MASK,
                               (uint8_t)config->dsdConfig.dsdDclkPolarity << AK4497_CONTROL3_DCKB_SHIFT);
        config->ak4497Mode = kAK4497_DsdMode;
    }

    if (format == (uint8_t)kAK4497_PcmMode)
    {
        ret = AK4497_ModifyReg(handle, AK4497_CONTROL7, AK4497_CONTROL7_TDM0_MASK | AK4497_CONTROL7_TDM1_MASK,
                               (uint8_t)config->pcmConfig.pcmTdmMode << AK4497_CONTROL7_TDM0_SHIFT);
        ret = AK4497_ModifyReg(handle, AK4497_CONTROL8, AK4497_CONTROL8_SDS0_MASK,
                               ((uint8_t)config->pcmConfig.pcmSdsSlot & 0x1U) << AK4497_CONTROL8_SDS0_SHIFT);
        ret = AK4497_ModifyReg(handle, AK4497_CONTROL7, AK4497_CONTROL7_SDS1_MASK,
                               (((uint8_t)config->pcmConfig.pcmSdsSlot & 0x2U) >> 1U) << AK4497_CONTROL7_SDS1_SHIFT);
        ret = AK4497_ModifyReg(handle, AK4497_CONTROL7, AK4497_CONTROL7_SDS2_MASK,
                               (((uint8_t)config->pcmConfig.pcmSdsSlot & 0x4U) >> 2U) << AK4497_CONTROL7_SDS2_SHIFT);
        ret = AK4497_ModifyReg(handle, AK4497_CONTROL1, AK4497_CONTROL1_EXDF_MASK, 0U << AK4497_CONTROL1_EXDF_SHIFT);
        ret = AK4497_ModifyReg(handle, AK4497_CONTROL3, AK4497_CONTROL3_DP_MASK, 0U << AK4497_CONTROL3_DP_SHIFT);

        config->ak4497Mode = kAK4497_PcmMode;
    }

    return ret;
}

status_t AK4497_ConfigDataFormat(ak4497_handle_t *handle, uint32_t mclk, uint32_t sampleRate, uint32_t bitWidth)
{
    ak4497_pcm_samplefreqselect_t samplefreq;
    ak4497_dsd_dclk_t dsdsel;
    ak4497_pcm_sdata_format_t sdataFormat;
    ak4497_config_t *config = (ak4497_config_t *)handle->config;
    status_t ret            = kStatus_Success;

    if (config->ak4497Mode == kAK4497_DsdMode)
    {
        switch (sampleRate * bitWidth)
        {
            case 2048000U:
            case 2822400U:
            case 3072000U:
                dsdsel = kAK4497_dclk64fs;
                break;
            case 4096000U:
            case 5644800U:
            case 6144000U:
                dsdsel = kAK4497_dclk128fs;
                break;
            case 8192000U:
            case 11289600U:
            case 12288000U:
                dsdsel = kAK4497_dclk256fs;
                break;
            case 16284000U:
            case 22579200U:
            case 24576000U:
                dsdsel = kAK4497_dclk512fs;
                break;
            default:
                ret = kStatus_Fail;
                break;
        }

        if (ret != kStatus_Success)
        {
            return ret;
        }

        ret = AK4497_ModifyReg(handle, AK4497_DSD1, AK4497_DSD1_DSDSEL0_MASK,
                               ((uint8_t)dsdsel & 0x1U) << AK4497_DSD1_DSDSEL0_SHIFT); /* Set DSDSEL0 */
        ret = AK4497_ModifyReg(handle, AK4497_DSD2, AK4497_DSD2_DSDSEL1_MASK,
                               (((uint8_t)dsdsel & 0x2U) >> 1U) << AK4497_DSD2_DSDSEL1_SHIFT); /* Set DSDSEL1 */
    }
    else /* PCM mode */
    {
        switch (sampleRate)
        {
            case 8000U:
            case 11025U:
            case 16000U:
            case 22050U:
            case 32000U:
            case 44100U:
            case 48000U:
                samplefreq = kAK4497_NormalSpeed;
                break;
            case 88200U:
            case 96000U:
                samplefreq = kAK4497_DoubleSpeed;
                break;
            case 176400U:
            case 192000U:
                samplefreq = kAK4497_QuadSpeed;
                break;
            case 352800U:
            case 384000U:
                samplefreq = kAK4497_OctSpeed;
                break;
            case 705600U:
            case 768000U:
                samplefreq = kAK4497_HexSpeed;
                break;
            default:
                ret = kStatus_Fail;
                break;
        }

        if (ret != kStatus_Success)
        {
            return ret;
        }

        switch (bitWidth)
        {
            /* For PCM, only strero mode supported. */
            case 16U:
            case 24U:
                sdataFormat = kAK4497_16_24BitI2S;
                break;
            case 32U:
                sdataFormat = kAK4497_32BitI2S;
                break;
            default:
                ret = kStatus_Fail;
                break;
        }

        if (ret != kStatus_Success)
        {
            return ret;
        }

        ret = AK4497_ModifyReg(handle, AK4497_CONTROL2, AK4497_CONTROL2_DFS0_MASK | AK4497_CONTROL2_DFS1_MASK,
                               ((uint8_t)samplefreq & 0x3U) << AK4497_CONTROL2_DFS0_SHIFT); /* Set DFS[1:0] */
        ret = AK4497_ModifyReg(handle, AK4497_CONTROL4, AK4497_CONTROL4_DFS2_MASK | AK4497_CONTROL4_DFS2_MASK,
                               (((uint8_t)samplefreq & 0x4U) >> 2U) << AK4497_CONTROL4_DFS2_SHIFT); /* Set DFS[2] */
        ret = AK4497_ModifyReg(handle, AK4497_CONTROL1,
                               AK4497_CONTROL1_DIF0_MASK | AK4497_CONTROL1_DIF1_MASK | AK4497_CONTROL1_DIF2_MASK,
                               (uint8_t)sdataFormat << AK4497_CONTROL1_DIF0_SHIFT);
    }

    ret = AK4497_ModifyReg(handle, AK4497_CONTROL1, AK4497_CONTROL1_RSTN_MASK,
                           0U << AK4497_CONTROL1_RSTN_SHIFT); /* Rest the ak4497 */

    Delay();

    ret = AK4497_ModifyReg(handle, AK4497_CONTROL1, AK4497_CONTROL1_RSTN_MASK,
                           1U << AK4497_CONTROL1_RSTN_SHIFT); /* Normal Operation */
    Delay();

    return ret;
}

status_t AK4497_SetVolume(ak4497_handle_t *handle, uint8_t value)
{
    status_t retval = kStatus_Success;
    /*
     * 255 levels, 0.5dB setp + mute (value = 0)
     */
    retval = AK4497_WriteReg(handle, AK4497_LCHATT, value);
    retval = AK4497_WriteReg(handle, AK4497_RCHATT, value);

    return retval;
}

status_t AK4497_GetVolume(ak4497_handle_t *handle, uint8_t *value)
{
    status_t retval = kStatus_Success;
    /*
     * 255 levels, 0.5dB setp + mute (value = 0);
     * R-channel volume regarded the same as the L-channel, here just read the L-channel value.
     */
    retval = AK4497_ReadReg(handle, AK4497_LCHATT, value);

    return retval;
}

status_t AK4497_Deinit(ak4497_handle_t *handle)
{
    status_t ret = kStatus_Success;

    ret = AK4497_ModifyReg(handle, AK4497_CONTROL2, AK4497_CONTROL2_SMUTE_MASK,
                           1U << AK4497_CONTROL2_SMUTE_SHIFT); /* Soft ware mute */

    ret = CODEC_I2C_Deinit(handle->i2cHandle);

    return ret;
}

status_t AK4497_ModuleControl(ak4497_handle_t *handle, ak4497_module_ctrl_cmd_t cmd, uint32_t data)
{
    status_t ret = kStatus_Success;

    if (cmd == kAK4497_ModuleSwitchI2SInInterface)
    {
        ret = AK4497_SetEncoding(handle, (uint8_t)data);
    }
    else
    {
        ret = kStatus_InvalidArgument;
    }

    return ret;
}

status_t AK4497_WriteReg(ak4497_handle_t *handle, uint8_t reg, uint8_t val)
{
    assert(handle->config != NULL);
    assert(handle->config->slaveAddress != 0U);

    Delay(); /* Ensure the Codec I2C bus free before writing the slave. */

    return CODEC_I2C_Send(handle->i2cHandle, handle->config->slaveAddress, reg, 1U, (uint8_t *)&val, 1U);
}

status_t AK4497_ReadReg(ak4497_handle_t *handle, uint8_t reg, uint8_t *val)
{
    assert(handle->config != NULL);
    assert(handle->config->slaveAddress != 0U);

    Delay(); /* Ensure the Codec I2C bus free before reading the slave. */

    return CODEC_I2C_Receive(handle->i2cHandle, handle->config->slaveAddress, reg, 1U, val, 1U);
}

status_t AK4497_ModifyReg(ak4497_handle_t *handle, uint8_t reg, uint8_t mask, uint8_t val)
{
    status_t retval = kStatus_Success;
    uint8_t reg_val = 0;
    retval          = AK4497_ReadReg(handle, reg, &reg_val);
    if (retval != kStatus_Success)
    {
        return kStatus_Fail;
    }
    reg_val &= (uint8_t)~mask;
    reg_val |= val;
    retval = AK4497_WriteReg(handle, reg, reg_val);
    if (retval != kStatus_Success)
    {
        return kStatus_Fail;
    }
    return kStatus_Success;
}
