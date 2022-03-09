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
#define HAL_TFA9896_VOLUME_CAPABILITY kCODEC_SupportPlayChannelLeft0 | kCODEC_SupportPlayChannelRight0
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static const codec_capability_t s_tfa9896_capability = {
    .codecPlayCapability   = (uint32_t)HAL_TFA9896_PLAY_CAPABILITY,
    .codecVolumeCapability = (uint32_t)HAL_TFA9896_VOLUME_CAPABILITY,
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
    status_t ret                = kStatus_Success;

    tfa9896_config_t *devConfig = (tfa9896_config_t *)(codecConfig->codecDevConfig);
    tfa9896_handle_t *devHandle = (tfa9896_handle_t *)((uint32_t) & (((codec_handle_t *)handle)->codecDevHandle));
    ((codec_handle_t *)handle)->codecCapability = &s_tfa9896_capability;
    /* codec device initialization */
    ret = TFA9896_Init(devHandle, devConfig);
    if (ret != kStatus_TFA9896_Ok)
    {
        ret = kStatus_Fail;
    }

    return ret;
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
    uint8_t mappedVolume            = 0U;
    tfa9896_handle_t *tfa9896Handle = (tfa9896_handle_t *)((uint32_t) & (((codec_handle_t *)handle)->codecDevHandle));
    /* Set Volume 0(min) to 100 (max) */

    /* Example volume table for the TFA9896
     * Volume level index and corresponding VOL value(dec) from TFA9896 register 0x06
     * Vol_lvl  0    10   20   30   40   50   60   70   80   90   100(Maximum volume)
     * Volume   255  40   30   24   16   10   6    4    2    1    0  (zero attenuation )*/

    switch (volume / 10U)
    {
        case 0U:
            mappedVolume = 255U;
            break;
        case 1U:
            mappedVolume = 40U;
            break;
        case 2U:
            mappedVolume = 30U;
            break;
        case 3U:
            mappedVolume = 24U;
            break;
        case 4U:
            mappedVolume = 16U;
            break;
        case 5U:
            mappedVolume = 10U;
            break;
        case 6U:
            mappedVolume = 6U;
            break;
        case 7U:
            mappedVolume = 4U;
            break;
        case 8U:
            mappedVolume = 2U;
            break;
        case 9U:
            mappedVolume = 1U;
            break;
        case 10U:
            mappedVolume = 0U;
            break;
        default:
            ret = kStatus_InvalidArgument;
            break;
    }

    if (ret == kStatus_Success)
    {
        ret = TFA9896_SetVolume(tfa9896Handle, mappedVolume);
    }

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

    ret =
        TFA9896_SetMute((tfa9896_handle_t *)((uint32_t) & (((codec_handle_t *)handle)->codecDevHandle)), Mute_Digital);
    if (ret != kStatus_TFA9896_Ok)
    {
        ret = kStatus_Fail;
    }

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
