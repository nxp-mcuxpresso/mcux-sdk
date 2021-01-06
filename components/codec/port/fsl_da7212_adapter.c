/*
 * Copyright  2019 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_da7212_adapter.h"
#include "fsl_codec_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief module capability definition */
#define HAL_DA7212_MODULE_CAPABILITY \
    kCODEC_SupportModuleADC | kCODEC_SupportModuleDAC | kCODEC_SupportModuleHeadphone | kCODEC_SupportModuleSpeaker
#define HAL_DA7212_PLAY_CAPABILITY                                                                      \
    kCODEC_SupportPlayChannelLeft0 | kCODEC_SupportPlayChannelRight0 | kCODEC_SupportPlayChannelLeft1 | \
        kCODEC_SupportPlayChannelRight1
#define HAL_DA7212_RECORD_CAPABILITY                                                   \
    kCODEC_SupportRecordSourceDifferentialMic | kCODEC_SupportRecordSourceDigitalMic | \
        kCODEC_SupportRecordSourceSingleEndMic | kCODEC_SupportRecordSourceLineInput

/*! @brief DA7212 map module */
#define HAL_DA7212_MAP_PROTOCOL(protocol)                                   \
    (protocol == kCODEC_BusI2S ?                                            \
         kDA7212_BusI2S :                                                   \
         protocol == kCODEC_BusLeftJustified ?                              \
         kDA7212_BusLeftJustified :                                         \
         protocol == kCODEC_BusRightJustified ? kDA7212_BusRightJustified : \
                                                protocol == kCODEC_BusPCMA ? kDA7212_BusDSPMode : kDA7212_BusI2S)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static const codec_capability_t s_da7212_capability = {
    .codecPlayCapability   = HAL_DA7212_PLAY_CAPABILITY,
    .codecModuleCapability = HAL_DA7212_MODULE_CAPABILITY,
    .codecRecordCapability = HAL_DA7212_RECORD_CAPABILITY,
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
status_t HAL_CODEC_DA7212_Init(void *handle, void *config)
{
    assert((config != NULL) && (handle != NULL));

    codec_config_t *codecConfig = (codec_config_t *)config;

    da7212_config_t *devConfig = (da7212_config_t *)(codecConfig->codecDevConfig);
    da7212_handle_t *devHandle = (da7212_handle_t *)((uint32_t)(((codec_handle_t *)handle)->codecDevHandle));

    ((codec_handle_t *)handle)->codecCapability = &s_da7212_capability;

    /* codec device initialization */
    return DA7212_Init(devHandle, devConfig);
}

/*!
 * brief Codec de-initilization.
 *
 * param handle codec handle.
 * return kStatus_Success is success, else de-initial failed.
 */
status_t HAL_CODEC_DA7212_Deinit(void *handle)
{
    assert(handle != NULL);

    return DA7212_Deinit((da7212_handle_t *)((uint32_t)(((codec_handle_t *)handle)->codecDevHandle)));
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
status_t HAL_CODEC_DA7212_SetFormat(void *handle, uint32_t mclk, uint32_t sampleRate, uint32_t bitWidth)
{
    assert(handle != NULL);

    return DA7212_ConfigAudioFormat((da7212_handle_t *)((uint32_t)(((codec_handle_t *)handle)->codecDevHandle)), mclk,
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
status_t HAL_CODEC_DA7212_SetVolume(void *handle, uint32_t playChannel, uint32_t volume)
{
    assert(handle != NULL);

    uint32_t mappedVolume = 0;
    status_t ret          = kStatus_Success;

    if (volume == 0U)
    {
        return DA7212_SetChannelMute((da7212_handle_t *)((uint32_t)(((codec_handle_t *)handle)->codecDevHandle)),
                                     playChannel, true);
    }

    mappedVolume = ((volume - 1U) * (DA7212_HEADPHONE_MAX_VOLUME_VALUE + 1U)) / 100U;

    ret = DA7212_SetChannelVolume((da7212_handle_t *)((uint32_t)(((codec_handle_t *)handle)->codecDevHandle)),
                                  playChannel, mappedVolume);

    if (ret == kStatus_Success)
    {
        ret = DA7212_SetChannelMute((da7212_handle_t *)((uint32_t)(((codec_handle_t *)handle)->codecDevHandle)),
                                    playChannel, false);
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
status_t HAL_CODEC_DA7212_SetMute(void *handle, uint32_t playChannel, bool isMute)
{
    assert(handle != NULL);

    return DA7212_SetChannelMute((da7212_handle_t *)((uint32_t)(((codec_handle_t *)handle)->codecDevHandle)),
                                 playChannel, isMute);
}

/*!
 * brief set audio codec module power.
 *
 * param handle codec handle.
 * param module audio codec module.
 * param powerOn true is power on, false is power down.
 * return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_DA7212_SetPower(void *handle, uint32_t module, bool powerOn)
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
status_t HAL_CODEC_DA7212_SetRecord(void *handle, uint32_t recordSource)
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
status_t HAL_CODEC_DA7212_SetRecordChannel(void *handle, uint32_t leftRecordChannel, uint32_t rightRecordChannel)
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
status_t HAL_CODEC_DA7212_SetPlay(void *handle, uint32_t playSource)
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
status_t HAL_CODEC_DA7212_ModuleControl(void *handle, uint32_t cmd, uint32_t data)
{
    return kStatus_CODEC_NotSupport;
}
