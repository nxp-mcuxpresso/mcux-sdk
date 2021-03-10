/*
 * Copyright  2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * fsl_tfa9xxx.c
 *
 *   General platform specific integration of tfa2_core code.
 */

#include "fsl_tfa9xxx.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define TFA9XXX_ROUND_DOWN(a, n)    (((a) / (n)) * (n))
#define TFA9XXX_I2C_MAX_DATA_LENGTH 256

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

status_t TFA9XXX_CreatePlatform(tfa9xxx_handle_t *handle, void *tfa_container_bin);
status_t TFA9XXX_PreStartConfigure(tfa9xxx_handle_t *handle);
void *TFA9XXX_GetI2CClient(nxpTfaContainer_t *cnt, uint8_t slaveAddress);
int TFA9XXX_DspExecuteCommand(
    struct tfa2_device *tfa, const char *cmd_buf, size_t cmd_len, char *res_buf, size_t res_len);
/*******************************************************************************
 * Variables
 ******************************************************************************/

/* tfa9xxx_device_t list */
static tfa9xxx_device_t s_devs[TFA9XXX_DEV_NUM];

/* profile index in container header file for the TFA to start */
static uint8_t s_TFA9XXX_start_profile = 0;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Initialize the TFA, put the TFA to operating state, allocate memory side.
 *
 * @param handle TFA9XXX handle structure.
 * @param tfa9xxxConfig TFA9XXX configuration structure.
 * @return status_t Returns kStatus_Success if success, otherwise returns error code.
 */
status_t TFA9XXX_Init(tfa9xxx_handle_t *handle, tfa9xxx_config_t *tfa9xxxConfig)
{
    status_t rc;
    tfa9xxx_config_t *config = tfa9xxxConfig;
    handle->config           = config;

    TFA9XXX_Printf("==========================================================\n", __FUNCTION__);
    TFA9XXX_Printf("%s: TFA initialization starting...\n", __FUNCTION__);

    /* i2c bus initialization */
    if (CODEC_I2C_Init(&(handle->i2cHandle), config->i2cConfig.codecI2CInstance, TFA9XXX_I2C_BAUDRATE,
                       config->i2cConfig.codecI2CSourceClock) != kStatus_HAL_I2cSuccess)
    {
        return kStatus_Fail;
    }

    /*
     * instantiate and probe the device(s)
     */
    rc = TFA9XXX_CreatePlatform(handle, config->tfaContainer);
    if (rc != kStatus_Success)
    {
        TFA9XXX_Printf("%s: TFA create platform failed:\n", __FUNCTION__);
        return rc;
    }

    /* Reset TFA */
    rc = TFA9XXX_Reset(handle);
    if (rc != kStatus_Success)
    {
        TFA9XXX_Printf("%s: TFA reset failed:\n", __FUNCTION__);
        return rc;
    }

    /* Set calibration value */
    rc = TFA9XXX_PreStartConfigure(handle);
    if (rc != kStatus_Success)
    {
        TFA9XXX_Printf("%s: TFA pre-start configure failed:\n", __FUNCTION__);
        return rc;
    }

    /* Reset TFA */
    rc = TFA9XXX_Reset(handle);
    if (rc != kStatus_Success)
    {
        TFA9XXX_Printf("%s: TFA reset failed:\n", __FUNCTION__);
        return rc;
    }

    rc = TFA9XXX_Start(handle);
    if (rc != kStatus_Success)
    {
        TFA9XXX_Printf("%s: TFA start failed:\n", __FUNCTION__);
        return rc;
    }

    rc = TFA9XXX_SetMute(handle, false);
    if (rc != kStatus_Success)
    {
        TFA9XXX_Printf("%s: TFA set mute failed:\n", __FUNCTION__);
        return rc;
    }

    TFA9XXX_Printf("%s: TFA initialized successfully.\n", __FUNCTION__);
    TFA9XXX_Printf("==========================================================\n", __FUNCTION__);
    return rc;
}

/*!
 * @brief Deinitialize the TFA, put the TFA to powerdown state.
 *
 * @param handle The TFA codec handle.
 * @return status_t Returns kStatus_Success if success, otherwise returns error code.
 */
status_t TFA9XXX_Deinit(tfa9xxx_handle_t *handle)
{
    status_t rc;
    if (!handle)
    {
        TFA9XXX_Printf("%s: TFA codec handle is NULL\n", __FUNCTION__);
        return kStatus_InvalidArgument;
    }

    rc = TFA9XXX_Reset(handle);
    if (rc != kStatus_Success)
        TFA9XXX_Printf("%s: TFA reset failed:\n", __FUNCTION__);

    return rc;
}

/*!
 * @brief Start the TFA.
 *
 * Start device will initialize if the device is in cold state
 * if already warm then only clocks will be started.
 *
 * This function has dependency on internal structure, it has to be called after TFA9XXX_CreatePlatform();
 *
 * @param handle The TFA codec handle.
 * @return status_t Returns kStatus_Success if success, otherwise returns error code.
 */
status_t TFA9XXX_Start(tfa9xxx_handle_t *handle)
{
    status_t rc;
    if (!handle)
    {
        TFA9XXX_Printf("%s: TFA codec handle is NULL\n", __FUNCTION__);
        return kStatus_InvalidArgument;
    }

    rc = tfa2_dev_start(&s_devs[handle->config->deviceIndex], s_TFA9XXX_start_profile, 0);

    return TFA9XXX_ConvertErrorCode(rc);
}

/*!
 * @brief Stop the TFA
 *
 * stop will put the TFA in powerdown/standby mode, the next time TFA start will be a warm start.
 *
 * This function has dependency on internal structure, it has to be called after TFA9XXX_CreatePlatform();
 *
 * @param handle The TFA codec handle.
 * @return status_t Returns kStatus_Success if success, otherwise returns error code.
 */
status_t TFA9XXX_Stop(tfa9xxx_handle_t *handle)
{
    status_t rc;
    if (!handle)
    {
        TFA9XXX_Printf("%s: TFA codec handle is NULL\n", __FUNCTION__);
        return kStatus_InvalidArgument;
    }

    rc = tfa2_dev_stop(&s_devs[handle->config->deviceIndex]);

    return TFA9XXX_ConvertErrorCode(rc);
}

/*!
 * @brief Reset the TFA
 *
 * Reset will put the in powerdown/standby mode, the next time TFA start will be a cold start.
 *
 * This function has dependency on internal structure, it has to be called after TFA9XXX_CreatePlatform();
 *
 * @param handle The TFA codec handle.
 * @return status_t Returns kStatus_Success if success, otherwise returns error code.
 */
status_t TFA9XXX_Reset(tfa9xxx_handle_t *handle)
{
    status_t rc;
    if (!handle)
    {
        TFA9XXX_Printf("%s: TFA codec handle is NULL\n", __FUNCTION__);
        return kStatus_InvalidArgument;
    }

    rc = tfa2_dev_set_state(&s_devs[handle->config->deviceIndex], TFA_STATE_RESET);

    return TFA9XXX_ConvertErrorCode(rc);
}

/*!
 * @brief Mute/Unmute the TFA
 *
 * This function has dependency on internal structure, it has to be called after TFA9XXX_CreatePlatform();
 *
 * @param handle TFA9XXX handle structure.
 * @param isMute true is mute, false is unmute..
 * @return status_t Returns kStatus_Success if success, otherwise returns error code.
 */
status_t TFA9XXX_SetMute(tfa9xxx_handle_t *handle, bool isMute)
{
    status_t rc;
    if (!handle)
    {
        TFA9XXX_Printf("%s: TFA codec handle is NULL\n", __FUNCTION__);
        return kStatus_InvalidArgument;
    }

    rc = tfa2_dev_mute(&s_devs[handle->config->deviceIndex], isMute);

    return TFA9XXX_ConvertErrorCode(rc);
}

/******************************device object creation ***********************/

/*!
 * @brief Create the platform that TFA relies on.
 *
 * this needs to be called once after powerup.
 * audio clocking is not required here, but may be running.
 *
 * @param handle The TFA codec handle.
 * @param tfa_container_bin The container bin contains the settings and binary files that are needed by TFA.
 *
 * @return status_t Returns kStatus_Success if success, otherwise returns error code.
 */
status_t TFA9XXX_CreatePlatform(tfa9xxx_handle_t *handle, void *tfa_container_bin)
{
    status_t rc;
    nxpTfaHeaderType_t type;
    struct nxpTfaContainer *cnt;

    tfa9xxx_device_t *tfa = &s_devs[handle->config->deviceIndex];

    /* verify if container file is valid */
    cnt  = (struct nxpTfaContainer *)tfa_container_bin;
    type = (nxpTfaHeaderType_t)HDR(cnt->id[0], cnt->id[1]);
    if (type != paramsHdr)
    { /* Load container file */
        TFA9XXX_Printf("%s: the container file is invalid\n", __FUNCTION__);
        return kStatus_InvalidArgument;
    }
    tfa->cnt = cnt;

    /* verify if slave address is valid */
    tfa->dev_idx = 0;
    tfa->i2c     = (struct i2c_client *)TFA9XXX_GetI2CClient(cnt, handle->config->slaveAddress);
    if (!tfa->i2c)
    {
        TFA9XXX_Printf("%s: Invalid slave address\n", __FUNCTION__);
        return kStatus_InvalidArgument;
    }
    tfa->i2c->hal = &(handle->i2cHandle);

    rc = tfa2_dev_probe(tfa);
    if (rc < 0)
    {
        TFA9XXX_Printf("%s: error probing device\n", __FUNCTION__);
        return TFA9XXX_ConvertErrorCode(rc);
    }
    if ((tfa->rev == 0x2a94) || (tfa->rev == 0x3a94))
    {
        /* bf_manstate overloads for TFA9894N2A0 and TFA9894N2A1*/
        tfa->bf_manstate = 0x1333;
    }
    tfa->dsp_execute = TFA9XXX_DspExecuteCommand;
    tfa->verbose     = 1U;

    return kStatus_Success;
}

/*!
 * @brief Configurate the TFA before starting by setting hardcoded calibration value for a new chip.
 *
 * This function has dependency on internal structure, it has to be called after TFA9XXX_CreatePlatform();
 *
 * @param handle The TFA codec handle.
 * @return status_t Returns kStatus_Success if success, otherwise returns error code.
 */
status_t TFA9XXX_PreStartConfigure(tfa9xxx_handle_t *handle)
{
    status_t rc;
    bool isTFACalibrated;
    tfa9xxx_device_t *tfa = &s_devs[handle->config->deviceIndex];

    rc = tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_PWDN, 0);
    if (rc < 0)
    {
        TFA9XXX_Printf("%s: Setting PWDN failed!\n", __FUNCTION__);
        return TFA9XXX_ConvertErrorCode(rc);
    }

    rc = tfa2_dev_clock_stable_wait(tfa);
    if (rc != kStatus_Success)
    {
        TFA9XXX_Printf("%s: TFA failed to power up.\n", __FUNCTION__);
        return rc;
    }

    rc = TFA9XXX_CheckCalibrationStatus(handle, &isTFACalibrated);
    if (rc != kStatus_Success)
    {
        TFA9XXX_Printf("%s: TFA check calibration status failed:\n", __FUNCTION__);
        return rc;
    }

    if (!isTFACalibrated)
    {
        TFA9XXX_Printf("%s: TFA is not calibrated, setting Calibration value...\n", __FUNCTION__);
        rc = TFA9XXX_HardcodeCalibrationValue(handle);
        if (rc != kStatus_Success)
        {
            TFA9XXX_Printf("%s: Setting Calibration value failed:\n", __FUNCTION__);
            return rc;
        }
    }
    else
    {
        TFA9XXX_Printf("%s: TFA is already calibrated, continue to start...\n", __FUNCTION__);
    }

    return rc;
}

/*!
 * @brief check if TFA is calibrated.
 *
 * This function has dependency on internal structure, it has to be called after TFA9XXX_CreatePlatform();
 *
 * @param handle The TFA codec handle.
 * @param isTFACalibrated This value stores if TFA is calibrated.
 * @return status_t Returns kStatus_Success if operation is successfully, otherwise returns error code..
 */
status_t TFA9XXX_CheckCalibrationStatus(tfa9xxx_handle_t *handle, bool *isTFACalibrated)
{
    status_t rc;

    if (!handle)
    {
        TFA9XXX_Printf("%s: TFA codec handle is NULL\n", __FUNCTION__);
        return kStatus_InvalidArgument;
    }

    tfa9xxx_device_t *tfa = &s_devs[handle->config->deviceIndex];

    /* open key2 */
    rc = tfa2_i2c_hap_key2(tfa->i2c, 0);
    if (rc < 0)
    {
        TFA9XXX_Printf("%s: open key2 failed!\n", __FUNCTION__);
        goto exit;
    }
    /* check MTPEX, trigger CMTPI inside */
    rc = tfa2_dev_mtp_get(tfa, TFA_MTP_EX);
    if (rc < 0)
    {
        TFA9XXX_Printf("%s: check tfa calibration failed, cannot read MTPEX!\n", __FUNCTION__);
        goto exit;
    }
    else
    {
        *isTFACalibrated = rc;
        rc               = kStatus_Success;
    }

exit:
    /* close key2 */
    rc = tfa2_i2c_hap_key2(tfa->i2c, 1);
    if (rc < 0)
    {
        TFA9XXX_Printf("%s: close key2 failed!\n", __FUNCTION__);
    }

    return TFA9XXX_ConvertErrorCode(rc);
}

/*!
 * @brief Start Speakerboost Calibration.
 *
 * The calibration will measure speaker impedance, and calculate the speaker impedance at 25 degree.
 * This value will be used to estimate the real-time temperature.
 *
 * This function has dependency on internal structure, it has to be called after TFA9XXX_CreatePlatform();
 *
 * @param handle The TFA codec handle.
 * @return status_t Returns kStatus_Success if success, otherwise returns error code.
 */
status_t TFA9XXX_CalibrateSpeakerBoost(tfa9xxx_handle_t *handle)
{
    status_t rc;

    if (!handle)
    {
        TFA9XXX_Printf("%s: TFA codec handle is NULL\n", __FUNCTION__);
        return kStatus_InvalidArgument;
    }

    tfa9xxx_device_t *tfa = &s_devs[handle->config->deviceIndex];

    rc = tfa2_dev_mtp_set(tfa, TFA_MTP_OTC, 1);
    if (rc < 0)
    {
        TFA9XXX_Printf("%s: writing of MTPOTC failed!\n", __FUNCTION__);
        return TFA9XXX_ConvertErrorCode(rc);
    }

    rc = tfa2_dev_mtp_set(tfa, TFA_MTP_EX, 0);
    if (rc < 0)
    {
        TFA9XXX_Printf("%s: MTP set failed!\n", __FUNCTION__);
        return TFA9XXX_ConvertErrorCode(rc);
    }

    rc = tfa2_sb_calibrate(tfa);
    if (rc < 0)
    {
        TFA9XXX_Printf("%s: SpeakerBoost Calibration failed!\n", __FUNCTION__);
    }

    return TFA9XXX_ConvertErrorCode(rc);
}

/*!
 * @brief Hardcode calibration value for DSP usage instead of triggering calibration.
 *
 * This function has dependency on internal structure, it has to be called after TFA9XXX_CreatePlatform();
 *
 * @param handle TFA9XXX handle structure.
 * @return status_t Returns kStatus_Success if success, otherwise returns error code.
 */
status_t TFA9XXX_HardcodeCalibrationValue(tfa9xxx_handle_t *handle)
{
    status_t rc;
    uint16_t mtp_data_pre[16];
    uint8_t i;

    if (!handle)
    {
        TFA9XXX_Printf("%s: TFA codec handle is NULL\n", __FUNCTION__);
        return kStatus_InvalidArgument;
    }

    tfa9xxx_device_t *tfa = &s_devs[handle->config->deviceIndex];

    /* open key2 */
    tfa2_i2c_hap_key2(tfa->i2c, 0);

    /* open mtp */
    rc = tfa2_dev_mtp_set(tfa, TFA_MTP_OPEN, 1);
    if (rc < 0)
    {
        TFA9XXX_Printf("%s: writing of OPENMTP failed!\n", __FUNCTION__);
        goto exit;
    }

    // store original MTP data from  0xf0 ~ 0xff:
    rc = tfa2_i2c_write_bf(tfa->i2c, TFA9XXX_BF_CMTPI, 1);
    if (rc < 0)
    {
        TFA9XXX_Printf("%s: writing CMTPI failed!\n", __FUNCTION__);
        goto exit;
    }

    for (i = 0; i < 16U; i++)
    {
        rc = tfa2_i2c_read_reg(tfa->i2c, 0xF0U + i);
        if (rc < 0)
            goto exit;
        mtp_data_pre[i] = rc;
    }

    /* open MTP already called inside */
    rc = tfa2_dev_mtp_set(tfa, TFA_MTP_EX, 1);
    if (rc < 0)
    {
        TFA9XXX_Printf("%s: writing of MTPEX failed!\n", __FUNCTION__);
        goto exit;
    }
    rc = tfa2_dev_mtp_set(tfa, TFA_MTP_OTC, 1);
    if (rc < 0)
    {
        TFA9XXX_Printf("%s: writing of MTPOTC failed!\n", __FUNCTION__);
        goto exit;
    }
    /* hardcode 8 ohm (8*1024 = 8192 = 0x2000) */
    rc = tfa2_dev_mtp_set(tfa, TFA_MTP_R25C, 0x2000U);
    if (rc < 0)
    {
        TFA9XXX_Printf("%s: writing of R25C failed!\n", __FUNCTION__);
        goto exit;
    }

    for (i = 0; i < 16U; i++)
    {
        rc = tfa2_i2c_read_reg(tfa->i2c, 0xF0U + i);
        if (rc < 0)
            goto exit;
        if (i == 0)
        {
            if (rc != (mtp_data_pre[i] | 0x3U))
            {
                TFA9XXX_Printf("%s: !Unexpected MTP data change!\n", __FUNCTION__);
                goto exit;
            }
        }
        else if (i == 5U)
        {
            if (rc != 0x2000U)
            {
                TFA9XXX_Printf("%s: !Unexpected MTP data change!\n", __FUNCTION__);
                goto exit;
            }
        }
        else
        {
            if (rc != mtp_data_pre[i])
            {
                TFA9XXX_Printf("%s: !Unexpected MTP data change!\n", __FUNCTION__);
                goto exit;
            }
        }
    }

exit:
    /* close key2 */
    tfa2_i2c_hap_key2(tfa->i2c, 1);

    /* close mtp */
    rc = tfa2_dev_mtp_set(tfa, TFA_MTP_OPEN, 0);
    if (rc < 0)
    {
        TFA9XXX_Printf("%s: writing of OPENMTP failed!\n", __FUNCTION__);
    }

    return TFA9XXX_ConvertErrorCode(rc);
}

/*!
 * @brief Configure the TFA based on I2S format.
 * Assuming TFA_Init() is already called by calling CODEC_Init(), the TFA will be in operating state. So before calling
 * TFA_SetFormat(), the TFA needs to be in powerdown state by calling TFA_Stop().
 *
 * @param handle TFA codec handle.
 * @param mclk TFA by default uses BCK as external reference clock, mclk settings will be ignored here.
 * @param sampleRate The sample rates supported are 48000Hz, 44100Hz, 32000Hz and 16000Hz. By default, 48000Hz is used.
 * @param bitWidth The bit width.
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA9XXX_ConfigDataFormat(tfa9xxx_handle_t *handle, uint32_t mclk, uint32_t sampleRate, uint32_t bitWidth)
{
    if (!handle)
    {
        TFA9XXX_Printf("%s: TFA codec handle is NULL\n", __FUNCTION__);
        return kStatus_InvalidArgument;
    }

    TFA9XXX_Printf("Function %s not supported yet\n", __FUNCTION__);
    return kStatus_Success;
}

/*!
 * @brief Set the volume level.
 *
 * This function has dependency on internal structure, it has to be called after TFA9XXX_CreatePlatform();
 *
 * @param handle TFA codec handle.
 * @param volume volume value, support 0 ~ 100, 0 is mute, 100 is the maximum volume value.
 * @return status_t Returns kStatus_Success if success, otherwise returns error code.
 */
status_t TFA9XXX_SetVolume(tfa9xxx_handle_t *handle, uint32_t volume)
{
    status_t rc;
    static const uint16_t VolumeTable[15] = {0, 1, 2, 4, 6, 10, 16, 24, 30, 40, 50, 60, 80, 100, 255};
    uint8_t index                         = 14 - volume / (100 / 14);

    //    uint8_t tfaVolume;

    if (!handle)
    {
        TFA9XXX_Printf("%s: TFA codec handle is NULL\n", __FUNCTION__);
        return kStatus_InvalidArgument;
    }

    if (volume > 100)
    {
        TFA9XXX_Printf("%s: volume out of range, should be 0 ~ 100\n", __FUNCTION__);
        return kStatus_InvalidArgument;
    }

    //    tfaVolume = (100 - volume) * 0xff / 100;

    rc = tfa2_i2c_write_bf_volatile(s_devs[handle->config->deviceIndex].i2c, TFA9XXX_BF_VOL, VolumeTable[index]);
    if (rc < 0)
    {
        TFA9XXX_Printf("%s: Setting volume failed!\n", __FUNCTION__);
    }

    return TFA9XXX_ConvertErrorCode(rc);
}

/*!
 * @brief Set the audio channel for a speaker.
 * By default, I2S channel is configured by the `.tfaContainer` in `tfa9xxx_config_t`. So you don't need to call this
 * function. However, if required, calling this function allows overwriting I2S channel selection. This can be useful
 * when the tuning is done, and you simply want to change the I2S channel.
 *
 * This function has dependency on internal structure, it has to be called after TFA9XXX_CreatePlatform();
 *
 * @param handle TFA9XXX handle structure.
 * @param _codec_play_channel play channel, available values are kCODEC_PlayChannelLeft0, kCODEC_PlayChannelRight0,
 * kCODEC_PlayChannelLeft0 | kCODEC_PlayChannelRight0.
 * @return status_t Returns kStatus_Success if success, otherwise returns error code.
 */
status_t TFA9XXX_SetPlayChannel(tfa9xxx_handle_t *handle, uint32_t playChannel)
{
    status_t rc;
    uint8_t channelCode = 0x01U;

    tfa9xxx_device_t *tfa = &s_devs[handle->config->deviceIndex];

    rc = tfa2_i2c_read_bf(tfa->i2c, tfa->bf_manstate);
    if (rc < 0)
    {
        TFA9XXX_Printf("%s: reading TFA status failed!\n", __FUNCTION__);
        return kStatus_Success;
    }
    else if (rc < 6)
    {
        TFA9XXX_Printf("%s: TFA not ready for setting channel, skip!\n", __FUNCTION__);
        return kStatus_Success;
    }

    if (playChannel == kTFA9XXX_PlayChannelLeft0)
    {
        channelCode = 0x0fU;
    }
    else if (playChannel == kTFA9XXX_PlayChannelRight0)
    {
        channelCode = 0xf1U;
    }
    else if (playChannel == (kTFA9XXX_PlayChannelLeft0 | kTFA9XXX_PlayChannelRight0))
    {
        channelCode = 0x01U;
    }
    else
    {
        TFA9XXX_Printf("%s: play channel unsupported!\n", __FUNCTION__);
        return kStatus_InvalidArgument;
    }

    char SetInputSelector_msg[]      = {0x00U, 0x80U, 0x06U, 0xffU, 0xffU, channelCode,
                                   0xffU, 0xffU, 0x32U, 0x00U, 0x0fU, 0xffU};
    uint8_t SetInputSelector_msg_len = 12U;

    rc = tfa2_cnt_write_msg(tfa, SetInputSelector_msg_len, SetInputSelector_msg);
    if (rc < 0)
    {
        TFA9XXX_Printf("%s: Writing Input Selector message failed!\n", __FUNCTION__);
    }

    return TFA9XXX_ConvertErrorCode(rc);
}

/*!
 * @brief Get the status of a running TFA.
 *
 * This function has dependency on internal structure, it has to be called after TFA9XXX_CreatePlatform();
 *
 * @param handle TFA codec handle.
 * @return status_t Returns kStatus_Success if success, otherwise returns error code.
 */
status_t TFA9XXX_GetStatus(tfa9xxx_handle_t *handle)
{
    status_t rc;
    if (!handle)
    {
        TFA9XXX_Printf("%s: TFA codec handle is NULL\n", __FUNCTION__);
        return kStatus_InvalidArgument;
    }

    rc = tfa2_dev_status(&s_devs[handle->config->deviceIndex]);

    return TFA9XXX_ConvertErrorCode(rc);
}

/*!
 * @brief Send command by i2c to TFA DSP to execute.
 *
 * Some long commands have to be chopped into little chunks to satisfy I2C limitation.
 *
 * @param tfa tfa device structure.
 * @param cmd_buf command buffer.
 * @param cmd_len command length.
 * @param res_buf result buffer.
 * @param res_len result length.
 * @return status_t Returns kStatus_Success if success, otherwise returns error code.
 */
int TFA9XXX_DspExecuteCommand(
    struct tfa2_device *tfa, const char *cmd_buf, size_t cmd_len, char *res_buf, size_t res_len)
{
    int rc = 0;
    uint32_t read_len;

    /* check write options */
    if (!cmd_len)
        return -EINVAL;

    if (res_len)
    {
        /* check read options */
        if (!res_buf)
            return -EINVAL;
        /* not 24bits aligned */
        if (res_len % 3)
            return -EFAULT;
    }

    /* if read is too big, do it afterwards in chunks */
    read_len = (res_len > TFA9XXX_I2C_MAX_DATA_LENGTH) ? 0 : res_len;

    /* if long message then send the payload in max sized chunks, fixup cmd_len */
    if (cmd_len > TFA9XXX_I2C_MAX_DATA_LENGTH)
    {
        /* handle write large messages */
        uint32_t chunk_size =
            TFA9XXX_ROUND_DOWN(TFA9XXX_I2C_MAX_DATA_LENGTH - 5 /*TODO dev->tfa->buffer_size*/, 3); /* XMEM word size */
        uint32_t xmem_offset = 2, remaining_bytes = cmd_len - 3; /* write all except the opcode/cmd_id */

        /* write in chunks */
        while ((rc == 0) && (remaining_bytes > 0))
        {
            if (remaining_bytes < chunk_size)
                chunk_size = remaining_bytes;
            /* else chunk_size remains at initialize value above */
            rc = tfa2_i2c_write_cf_mem24(tfa->i2c, xmem_offset, (uint8_t *)cmd_buf + xmem_offset * 3 - 3, chunk_size,
                                         TFA2_CF_MEM_XMEM);
            remaining_bytes -= chunk_size;
            xmem_offset += chunk_size / 3;
        }
        if (rc < 0)
            return rc;

        /* fake a 1 word cmd, the RPC payload is already there, only need the opcode now */
        cmd_len = 3;
    }
    /* and execute */
    rc = tfa2_i2c_dsp_execute(tfa, cmd_buf, cmd_len, res_buf, read_len);
    if (rc < 0)
        return rc;

    if (res_len > TFA9XXX_I2C_MAX_DATA_LENGTH)
    {
        /* handle write read messages */
        uint32_t chunk_size =
            TFA9XXX_ROUND_DOWN(TFA9XXX_I2C_MAX_DATA_LENGTH - 5 /*TODO dev->tfa->buffer_size*/, 3); /* XMEM word size */
        uint32_t xmem_offset = 0, remaining_bytes = res_len; /* write all except the opcode/cmd_id */

        /* write in chunks */
        while ((rc == 0) && (remaining_bytes > 0))
        {
            if (remaining_bytes < chunk_size)
                chunk_size = remaining_bytes;
            /* else chunk_size remains at initialize value above */
            rc = tfa2_i2c_read_cf_mem24(tfa->i2c, xmem_offset, (uint8_t *)res_buf + xmem_offset * 3, chunk_size,
                                        TFA2_CF_MEM_XMEM);
            remaining_bytes -= chunk_size;
            xmem_offset += chunk_size / 3;
        }
        if (rc < 0)
            return rc;
    }

    return rc;
}
