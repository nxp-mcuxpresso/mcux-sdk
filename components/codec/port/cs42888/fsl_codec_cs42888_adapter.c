/*
 * Copyright  2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_codec_cs42888_adapter.h"
#include "fsl_codec_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief CS42888 play capability*/
#define HAL_CS42888_PLAY_CAPABILITY                                                                          \
    kCODEC_SupportPlayChannelLeft0 | kCODEC_SupportPlayChannelRight0 | kCODEC_SupportPlayChannelLeft1 |      \
        kCODEC_SupportPlayChannelRight1 | kCODEC_SupportPlayChannelLeft2 | kCODEC_SupportPlayChannelRight2 | \
        kCODEC_SupportPlayChannelLeft3 | kCODEC_SupportPlayChannelRight3
#define HAL_CS42888_VOLUME_CAPABILITY                                                                        \
    kCODEC_SupportPlayChannelLeft0 | kCODEC_SupportPlayChannelRight0 | kCODEC_SupportPlayChannelLeft1 |      \
        kCODEC_SupportPlayChannelRight1 | kCODEC_SupportPlayChannelLeft2 | kCODEC_SupportPlayChannelRight2 | \
        kCODEC_SupportPlayChannelLeft3 | kCODEC_SupportPlayChannelRight3

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static const codec_capability_t s_cs42888_capability = {
    .codecPlayCapability   = HAL_CS42888_PLAY_CAPABILITY,
    .codecVolumeCapability = HAL_CS42888_VOLUME_CAPABILITY,
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
status_t HAL_CODEC_CS42888_Init(void *handle, void *config)
{
    assert((config != NULL) && (handle != NULL));

    status_t ret                = kStatus_Success;
    codec_config_t *codecConfig = (codec_config_t *)config;

    cs42888_config_t *devConfig = (cs42888_config_t *)(codecConfig->codecDevConfig);
    cs42888_handle_t *devHandle = (cs42888_handle_t *)((uint32_t)(((codec_handle_t *)handle)->codecDevHandle));

    /* load codec capability */
    ((codec_handle_t *)handle)->codecCapability = &s_cs42888_capability;
    /* codec device initialization */
    ret = CS42888_Init(devHandle, devConfig);

    if (ret != kStatus_Success)
    {
        return ret;
    }

    return kStatus_Success;
}

/*!
 * brief Codec de-initilization.
 *
 * param handle codec handle.
 * return kStatus_Success is success, else de-initial failed.
 */
status_t HAL_CODEC_CS42888_Deinit(void *handle)
{
    assert(handle != NULL);

    return CS42888_Deinit((cs42888_handle_t *)((uint32_t)(((codec_handle_t *)handle)->codecDevHandle)));
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
status_t HAL_CODEC_CS42888_SetFormat(void *handle, uint32_t mclk, uint32_t sampleRate, uint32_t bitWidth)
{
    assert(handle != NULL);

    return CS42888_ConfigDataFormat((cs42888_handle_t *)((uint32_t)(((codec_handle_t *)handle)->codecDevHandle)), mclk,
                                    sampleRate, bitWidth);
}

/*!
 * brief set audio codec module volume.
 *
 * param handle codec handle.
 * param channel audio codec play channel, can be a value or combine value of _codec_play_channel.
 * param volume volume value, support 0 ~ 100, 0 is mute, 100 is the maximum volume value.
 * return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_CS42888_SetVolume(void *handle, uint32_t playChannel, uint32_t volume)
{
    assert(handle != NULL);
    uint8_t i            = 0U;
    status_t ret         = kStatus_Success;
    uint8_t mappedVolume = 0;

    for (i = 0U; i < (uint8_t)kCS42888_AOUT8; i++)
    {
        if ((playChannel & (1UL << i)) == 0U)
        {
            continue;
        }

        if (volume == 0U)
        {
            ret = CS42888_SetChannelMute((cs42888_handle_t *)((uint32_t)(((codec_handle_t *)handle)->codecDevHandle)),
                                         (uint8_t)(i + 1U), true);
        }
        else
        {
            /* 1 is mapped t0 255, 100 is mapped to 0 */
            mappedVolume = (uint8_t)(CS42888_AOUT_MAX_VOLUME_VALUE -
                                     ((volume - 1U) * (CS42888_AOUT_MAX_VOLUME_VALUE + 3U)) / 100U);

            ret = CS42888_SetAOUTVolume((cs42888_handle_t *)((uint32_t)(((codec_handle_t *)handle)->codecDevHandle)),
                                        (uint8_t)(i + 1U), mappedVolume);
            /* unmute the channel */
            if (ret == kStatus_Success)
            {
                ret =
                    CS42888_SetChannelMute((cs42888_handle_t *)((uint32_t)(((codec_handle_t *)handle)->codecDevHandle)),
                                           (uint8_t)(i + 1U), false);
            }
        }

        if (ret != kStatus_Success)
        {
            return ret;
        }
    }

    return kStatus_Success;
}

/*!
 * brief set audio codec module mute.
 *
 * param handle codec handle.
 * param channel audio codec play channel, can be a value or combine value of _codec_play_channel.
 * param isMute true is mute, false is unmute.
 * return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_CS42888_SetMute(void *handle, uint32_t playChannel, bool isMute)
{
    assert(handle != NULL);
    uint8_t i    = 0U;
    status_t ret = kStatus_Success;

    for (i = 0U; i < (uint8_t)kCS42888_AOUT8; i++)
    {
        if ((playChannel & (1UL << i)) == 0U)
        {
            continue;
        }

        ret = CS42888_SetChannelMute((cs42888_handle_t *)((uint32_t)(((codec_handle_t *)handle)->codecDevHandle)),
                                     (uint8_t)(i + 1U), isMute);
        if (ret != kStatus_Success)
        {
            return ret;
        }
    }

    return kStatus_Success;
}

/*!
 * brief set audio codec module power.
 *
 * param handle codec handle.
 * param module audio codec module.
 * param powerOn true is power on, false is power down.
 * return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_CS42888_SetPower(void *handle, uint32_t module, bool powerOn)
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
status_t HAL_CODEC_CS42888_SetRecord(void *handle, uint32_t recordSource)
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
status_t HAL_CODEC_CS42888_SetRecordChannel(void *handle, uint32_t leftRecordChannel, uint32_t rightRecordChannel)
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
status_t HAL_CODEC_CS42888_SetPlay(void *handle, uint32_t playSource)
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
status_t HAL_CODEC_CS42888_ModuleControl(void *handle, uint32_t cmd, uint32_t data)
{
    return kStatus_CODEC_NotSupport;
}
