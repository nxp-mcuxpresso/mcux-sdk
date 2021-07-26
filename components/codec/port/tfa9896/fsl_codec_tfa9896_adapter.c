/*
 * Copyright  2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_codec_tfa9896_adapter.h"
#include "fsl_codec_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief TFA9896 play capability*/
#define HAL_TFA9896_PLAY_CAPABILITY \
    kCODEC_SupportModuleSpeaker | kCODEC_SupportPlayChannelLeft0 | kCODEC_SupportPlayChannelRight0

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static const codec_capability_t s_tfa9896_capability = {
    .codecPlayCapability = (uint32_t)HAL_TFA9896_PLAY_CAPABILITY,
};

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * brief Codec initilization.
 *
 * param handle codec handle.
 * param config codec configuration.
 * return kStatus_Success is success, else initial failed.
 */
status_t HAL_CODEC_TFA9896_Init(void *handle, void *config)
{
    assert((config != NULL) && (handle != NULL));

    codec_config_t *codecConfig = (codec_config_t *)config;
    tfa9896_config_t *devConfig = (tfa9896_config_t *)(codecConfig->codecDevConfig);
    tfa9896_handle_t *devHandle = (tfa9896_handle_t *)((uint32_t) & (((codec_handle_t *)handle)->codecDevHandle));
    ((codec_handle_t *)handle)->codecCapability = &s_tfa9896_capability;
    /* codec device initialization */
    return TFA9896_Init(devHandle, devConfig);
}

/*!
 * brief Codec de-initilization.
 *
 * param handle codec handle.
 * return kStatus_Success is success, else de-initial failed.
 */
status_t HAL_CODEC_TFA9896_Deinit(void *handle)
{
    assert(handle != NULL);

    return TFA9896_Deinit((tfa9896_handle_t *)((uint32_t) & (((codec_handle_t *)handle)->codecDevHandle)));
}

/*!
 * brief set audio data format.
 *
 * param handle codec handle.
 * param mclk master clock frequency in HZ.
 * param sampleRate sample rate in HZ.
 * param bitWidth bit width.
 * return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_TFA9896_SetFormat(void *handle, uint32_t mclk, uint32_t sampleRate, uint32_t bitWidth)
{
    assert(handle != NULL);

    return kStatus_CODEC_NotSupport;
}

/*!
 * brief set audio codec module volume.
 *
 * param handle codec handle.
 * param channel audio codec play channel, can be a value or combine value of _codec_play_channel.
 * param volume volume value, support 0 ~ 100, 0 is mute, 100 is the maximum volume value.
 * return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_TFA9896_SetVolume(void *handle, uint32_t playChannel, uint32_t volume)
{
    assert(handle != NULL);
    status_t ret                    = kStatus_Success;
    tfa9896_handle_t *tfa9896Handle = (tfa9896_handle_t *)((uint32_t) & (((codec_handle_t *)handle)->codecDevHandle));
    /* Set Volume 0(min) to 100 (max) */

    /* Example volume table for the TFA9896
     * Volume level index and corresponding VOL value(dec) from TFA9896 register 0x06
     * Vol_lvl  0    10   20   30   40   50   60   70   80   90   100(Maximum volume)
     * Volume   255  40   30   24   16   10   6    4    2    1    0  (zero attenuation )*/

    switch (volume / 10)
    {
        case 0:
            volume = 255;
            break;
        case 1:
            volume = 40;
            break;
        case 2:
            volume = 30;
            break;
        case 3:
            volume = 24;
            break;
        case 4:
            volume = 16;
            break;
        case 5:
            volume = 10;
            break;
        case 6:
            volume = 6;
            break;
        case 7:
            volume = 4;
            break;
        case 8:
            volume = 2;
            break;
        case 9:
            volume = 1;
            break;
        case 10:
            volume = 0;
            break;
    }
    ret = TFA9896_SetVolume(tfa9896Handle, volume);
    return ret;
}

/*!
 * brief set audio codec module mute.
 *
 * param handle codec handle.
 * param channel audio codec play channel, can be a value or combine value of _codec_play_channel.
 * param isMute true is mute, false is unmute.
 * return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_TFA9896_SetMute(void *handle, uint32_t playChannel, bool isMute)
{
    assert(handle != NULL);
    status_t ret = kStatus_Success;
    ret          = TFA9896_SetMute((tfa9896_handle_t *)((codec_handle_t *)handle), Mute_Digital);
    return ret;
}

/*!
 * brief set audio codec module power.
 *
 * param handle codec handle.
 * param module audio codec module.
 * param powerOn true is power on, false is power down.
 * return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_TFA9896_SetPower(void *handle, uint32_t module, bool powerOn)
{
    return kStatus_CODEC_NotSupport;
}

/*!
 * brief codec set record channel.
 *
 * param handle codec handle.
 * param leftRecordChannel audio codec record channel, reference _codec_record_channel, can be a value or combine value
 of member in _codec_record_channel.
 * param rightRecordChannel audio codec record channel, reference _codec_record_channel, can be a value combine of
 member in _codec_record_channel.

 * return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_TFA9896_SetRecordChannel(void *handle, uint32_t leftRecordChannel, uint32_t rightRecordChannel)
{
    return kStatus_CODEC_NotSupport;
}

/*!
 * brief codec set record source.
 *
 * param handle codec handle.
 * param source audio codec record source, can be a value or combine value of _codec_record_source.
 *
 * return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_TFA9896_SetRecord(void *handle, uint32_t recordSource)
{
    return kStatus_CODEC_NotSupport;
}

/*!
 * brief codec set play source.
 *
 * param handle codec handle.
 * param playSource audio codec play source, can be a value or combine value of _codec_play_source.
 *
 * return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_TFA9896_SetPlay(void *handle, uint32_t playSource)
{
    return kStatus_CODEC_NotSupport;
}

/*!
 * brief codec module control.
 *
 * param handle codec handle.
 * param cmd module control cmd, reference _codec_module_ctrl_cmd.
 * param data value to write, when cmd is kCODEC_ModuleRecordSourceChannel, the data should be a value combine
 *  of channel and source, please reference macro CODEC_MODULE_RECORD_SOURCE_CHANNEL(source, LP, LN, RP, RN), reference
 *  codec specific driver for detail configurations.
 * return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_TFA9896_ModuleControl(void *handle, uint32_t cmd, uint32_t data)
{
    return kStatus_CODEC_NotSupport;
}
