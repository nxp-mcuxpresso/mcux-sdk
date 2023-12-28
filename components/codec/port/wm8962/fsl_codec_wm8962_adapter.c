/*
 * Copyright  2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_codec_wm8962_adapter.h"
#include "fsl_codec_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief module capability definition */
#define HAL_WM8962_MODULE_CAPABILITY                                                                                   \
    (kCODEC_SupportModuleADC | kCODEC_SupportModuleDAC | kCODEC_SupportModuleHeadphone | kCODEC_SupportModuleSpeaker | \
     kCODEC_SupportModuleMic | kCODEC_SupportModuleMixer | kCODEC_SupportModuleMicbias | kCODEC_SupportModuleLinein)

#define HAL_WM8962_PLAY_CAPABILITY                                                                       \
    (kCODEC_SupportPlayChannelLeft0 | kCODEC_SupportPlayChannelRight0 | kCODEC_SupportPlayChannelLeft1 | \
     kCODEC_SupportPlayChannelRight1 | kCODEC_SupportPlaySourcePGA | kCODEC_SupportPlaySourceDAC |       \
     kCODEC_SupportPlaySourceInput)

#define HAL_WM8962_VOLUME_CAPABILITY                                                                     \
    (kCODEC_SupportPlayChannelLeft0 | kCODEC_SupportPlayChannelRight0 | kCODEC_SupportPlayChannelLeft1 | \
     kCODEC_SupportPlayChannelRight1 | kCODEC_VolumeDAC)

#define HAL_WM8962_RECORD_CAPABILITY                                                                    \
    (kCODEC_SupportPlayChannelLeft0 | kCODEC_SupportPlayChannelLeft1 | kCODEC_SupportPlayChannelLeft2 | \
     kCODEC_SupportPlayChannelRight0 | kCODEC_SupportPlayChannelRight1 | kCODEC_SupportPlayChannelRight2)

/*! @brief wm8962 map protocol */
#define HAL_WM8962_MAP_PROTOCOL(protocol)                                 \
    ((protocol) == kCODEC_BusI2S            ? kWM8962_BusI2S :            \
     (protocol) == kCODEC_BusLeftJustified  ? kWM8962_BusLeftJustified :  \
     (protocol) == kCODEC_BusRightJustified ? kWM8962_BusRightJustified : \
     (protocol) == kCODEC_BusPCMA           ? kWM8962_BusPCMA :           \
     (protocol) == kCODEC_BusPCMB           ? kWM8962_BusPCMB :           \
                                              kWM8962_BusI2S)

/*! @brief wm8962 map module */
#define HAL_WM8962_MAP_MODULE(module)                                         \
    ((module) == (uint32_t)kCODEC_ModuleADC       ? kWM8962_ModuleADC :       \
     (module) == (uint32_t)kCODEC_ModuleDAC       ? kWM8962_ModuleDAC :       \
     (module) == (uint32_t)kCODEC_ModuleHeadphone ? kWM8962_ModuleHeadphone : \
     (module) == (uint32_t)kCODEC_ModuleMicbias   ? kWM8962_ModuleMICB :      \
     (module) == (uint32_t)kCODEC_ModuleMic       ? kWM8962_ModuleMIC :       \
     (module) == (uint32_t)kCODEC_ModuleLinein    ? kWM8962_ModuleLineIn :    \
     (module) == (uint32_t)kCODEC_ModuleSpeaker   ? kWM8962_ModuleSpeaker :   \
                                                    kWM8962_ModuleADC)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static const codec_capability_t s_wm8962_capability = {
    .codecPlayCapability   = HAL_WM8962_PLAY_CAPABILITY,
    .codecVolumeCapability = HAL_WM8962_VOLUME_CAPABILITY,
    .codecModuleCapability = HAL_WM8962_MODULE_CAPABILITY,
    .codecRecordCapability = HAL_WM8962_RECORD_CAPABILITY,
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
status_t HAL_CODEC_WM8962_Init(void *handle, void *config)
{
    assert((config != NULL) && (handle != NULL));

    codec_config_t *codecConfig = (codec_config_t *)config;

    wm8962_config_t *devConfig = (wm8962_config_t *)(codecConfig->codecDevConfig);
    wm8962_handle_t *devHandle = (wm8962_handle_t *)((uintptr_t)(((codec_handle_t *)handle)->codecDevHandle));

    ((codec_handle_t *)handle)->codecCapability = &s_wm8962_capability;

    /* codec device initialization */
    return WM8962_Init(devHandle, devConfig);
}

/*!
 * brief Codec de-initilization.
 *
 * param handle codec handle.
 * return kStatus_Success is success, else de-initial failed.
 */
status_t HAL_CODEC_WM8962_Deinit(void *handle)
{
    assert(handle != NULL);

    return WM8962_Deinit((wm8962_handle_t *)((uintptr_t)(((codec_handle_t *)handle)->codecDevHandle)));
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
status_t HAL_CODEC_WM8962_SetFormat(void *handle, uint32_t mclk, uint32_t sampleRate, uint32_t bitWidth)
{
    assert(handle != NULL);

    return WM8962_ConfigDataFormat((wm8962_handle_t *)((uintptr_t)(((codec_handle_t *)handle)->codecDevHandle)), mclk,
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
status_t HAL_CODEC_WM8962_SetVolume(void *handle, uint32_t playChannel, uint32_t volume)
{
    assert(handle != NULL);

    status_t retVal       = kStatus_Success;
    uint32_t mappedVolume = 0U;

    if (((playChannel & (uint32_t)kCODEC_VolumeHeadphoneLeft) != 0U) ||
        ((playChannel & (uint32_t)kCODEC_VolumeHeadphoneRight) != 0U))
    {
        /*
         * 0 is mute
         * 1 - 100 is mapped to 0x30 - 0x7F
         */
        mappedVolume = (volume * (WM8962_HEADPHONE_MAX_VOLUME_vALUE - WM8962_HEADPHONE_MIN_VOLUME_vALUE)) / 100U +
                       WM8962_HEADPHONE_MIN_VOLUME_vALUE;
        retVal = WM8962_SetModuleVolume((wm8962_handle_t *)((uintptr_t)(((codec_handle_t *)handle)->codecDevHandle)),
                                        kWM8962_ModuleHeadphone, mappedVolume);
    }

    if (((playChannel & (uint32_t)kCODEC_VolumeSpeakerLeft) != 0U) ||
        ((playChannel & (uint32_t)kCODEC_VolumeSpeakerRight) != 0U))
    {
        /*
         * 0 is mute
         * 1 - 100 is mapped to 0x30 - 0x7F
         */
        mappedVolume = (volume * (WM8962_HEADPHONE_MAX_VOLUME_vALUE - WM8962_HEADPHONE_MIN_VOLUME_vALUE)) / 100U +
                       WM8962_HEADPHONE_MIN_VOLUME_vALUE;
        retVal = WM8962_SetModuleVolume((wm8962_handle_t *)((uintptr_t)(((codec_handle_t *)handle)->codecDevHandle)),
                                        kWM8962_ModuleSpeaker, mappedVolume);
    }

    if ((playChannel & (uint32_t)kCODEC_VolumeDAC) != 0U)
    {
        /*
         * 0 is mute
         * 0 - 100 is mapped to 0x00 - 0xFF
         */
        mappedVolume = (volume * (WM8962_DAC_MAX_VOLUME_vALUE - 0U)) / 100U;

        retVal = WM8962_SetModuleVolume((wm8962_handle_t *)((uintptr_t)(((codec_handle_t *)handle)->codecDevHandle)),
                                        kWM8962_ModuleDAC, mappedVolume);
    }

    return retVal;
}

/*!
 * brief set audio codec module mute.
 *
 * param handle codec handle.
 * param channel audio codec play channel, can be a value or combine value of _codec_play_channel.
 * param isMute true is mute, false is unmute.
 * return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_WM8962_SetMute(void *handle, uint32_t playChannel, bool isMute)
{
    assert(handle != NULL);

    status_t retVal = kStatus_Success;

    if (((playChannel & (uint32_t)kWM8962_HeadphoneLeft) != 0U) ||
        ((playChannel & (uint32_t)kWM8962_HeadphoneRight) != 0U))
    {
        retVal = WM8962_SetModuleMute((wm8962_handle_t *)((uintptr_t)(((codec_handle_t *)handle)->codecDevHandle)),
                                      kWM8962_ModuleHeadphone, isMute);
    }

    if (((playChannel & (uint32_t)kWM8962_SpeakerLeft) != 0U) || ((playChannel & (uint32_t)kWM8962_SpeakerRight) != 0U))
    {
        retVal = WM8962_SetModuleMute((wm8962_handle_t *)((uintptr_t)(((codec_handle_t *)handle)->codecDevHandle)),
                                      kWM8962_ModuleSpeaker, isMute);
    }

    return retVal;
}

/*!
 * brief set audio codec module power.
 *
 * param handle codec handle.
 * param module audio codec module.
 * param powerOn true is power on, false is power down.
 * return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_WM8962_SetPower(void *handle, uint32_t module, bool powerOn)
{
    assert(handle != NULL);

    return WM8962_SetModulePower((wm8962_handle_t *)((uintptr_t)(((codec_handle_t *)handle)->codecDevHandle)),
                                 HAL_WM8962_MAP_MODULE(module), powerOn);
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
status_t HAL_CODEC_WM8962_SetRecordChannel(void *handle, uint32_t leftRecordChannel, uint32_t rightRecordChannel)
{
    return kStatus_CODEC_NotSupport;
}

/*!
 * brief codec set record source.
 *
 * param handle codec handle.
 * param source audio codec record source, can be a value or combine value of _codec_record_source.
 *
 * @return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_WM8962_SetRecord(void *handle, uint32_t recordSource)
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
status_t HAL_CODEC_WM8962_SetPlay(void *handle, uint32_t playSource)
{
    return kStatus_CODEC_NotSupport;
}

/*!
 * brief codec module control.
 *
 * param handle codec handle.
 * param cmd module control cmd, reference _codec_module_ctrl_cmd.
 * param moduleData value to write, when cmd is kCODEC_ModuleRecordSourceChannel, the data should be a value combine
 *  of channel and source, please reference macro CODEC_MODULE_RECORD_SOURCE_CHANNEL(source, LP, LN, RP, RN), reference
 *  codec specific driver for detail configurations.
 * return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_WM8962_ModuleControl(void *handle, uint32_t cmd, uint32_t moduleData)
{
    return kStatus_CODEC_NotSupport;
}
