/*
 * Copyright  2019-2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_codec_adapter.h"
#include "fsl_codec_common.h"

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
/*!
 * brief Codec initilization.
 *
 * param handle codec handle.
 * param config codec configuration.
 * return kStatus_Success is success, else initial failed.
 */
status_t HAL_CODEC_Init(void *handle, void *config)
{
    assert((config != NULL) && (handle != NULL));

    codec_config_t *codecConfig = (codec_config_t *)config;
    status_t retVal             = kStatus_Success;

    switch (codecConfig->codecDevType)
    {
#ifdef CODEC_WM8904_ENABLE
        case kCODEC_WM8904:
            retVal = HAL_CODEC_WM8904_Init(handle, config);
            break;
#endif

#ifdef CODEC_WM8960_ENABLE
        case kCODEC_WM8960:
            retVal = HAL_CODEC_WM8960_Init(handle, config);
            break;
#endif

#ifdef CODEC_WM8962_ENABLE
        case kCODEC_WM8962:
            retVal = HAL_CODEC_WM8962_Init(handle, config);
            break;
#endif

#ifdef CODEC_WM8524_ENABLE
        case kCODEC_WM8524:
            retVal = HAL_CODEC_WM8524_Init(handle, config);
            break;
#endif

#ifdef CODEC_SGTL5000_ENABLE
        case kCODEC_SGTL5000:
            retVal = HAL_CODEC_SGTL5000_Init(handle, config);
            break;
#endif

#ifdef CODEC_DA7212_ENABLE
        case kCODEC_DA7212:
            retVal = HAL_CODEC_DA7212_Init(handle, config);
            break;
#endif

#ifdef CODEC_CS42888_ENABLE
        case kCODEC_CS42888:
            retVal = HAL_CODEC_CS42888_Init(handle, config);
            break;
#endif

#ifdef CODEC_CS42448_ENABLE
        case kCODEC_CS42448:
            retVal = HAL_CODEC_CS42448_Init(handle, config);
            break;
#endif

#ifdef CODEC_AK4497_ENABLE
        case kCODEC_AK4497:
            retVal = HAL_CODEC_AK4497_Init(handle, config);
            break;
#endif

#ifdef CODEC_AK4458_ENABLE
        case kCODEC_AK4458:
            retVal = HAL_CODEC_AK4458_Init(handle, config);
            break;
#endif

#ifdef CODEC_TFA9XXX_ENABLE
        case kCODEC_TFA9XXX:
            retVal = HAL_CODEC_TFA9XXX_Init(handle, config);
            break;
#endif

#ifdef CODEC_TFA9896_ENABLE
        case kCODEC_TFA9896:
            retVal = HAL_CODEC_TFA9896_Init(handle, config);
            break;
#endif
        default:
            retVal = kStatus_InvalidArgument;
            break;
    }

    return retVal;
}

/*!
 * brief Codec de-initilization.
 *
 * param handle codec handle.
 * return kStatus_Success is success, else de-initial failed.
 */
status_t HAL_CODEC_Deinit(void *handle)
{
    assert(handle != NULL);
    status_t retVal = kStatus_Success;

    switch (((codec_handle_t *)handle)->codecConfig->codecDevType)
    {
#ifdef CODEC_WM8904_ENABLE
        case kCODEC_WM8904:
            retVal = HAL_CODEC_WM8904_Deinit(handle);
            break;
#endif

#ifdef CODEC_WM8960_ENABLE
        case kCODEC_WM8960:
            retVal = HAL_CODEC_WM8960_Deinit(handle);
            break;
#endif

#ifdef CODEC_WM8962_ENABLE
        case kCODEC_WM8962:
            retVal = HAL_CODEC_WM8962_Deinit(handle);
            break;
#endif

#ifdef CODEC_WM8524_ENABLE
        case kCODEC_WM8524:
            retVal = HAL_CODEC_WM8524_Deinit(handle);
            break;
#endif

#ifdef CODEC_SGTL5000_ENABLE
        case kCODEC_SGTL5000:
            retVal = HAL_CODEC_SGTL5000_Deinit(handle);
            break;
#endif

#ifdef CODEC_DA7212_ENABLE
        case kCODEC_DA7212:
            retVal = HAL_CODEC_DA7212_Deinit(handle);
            break;
#endif

#ifdef CODEC_CS42888_ENABLE
        case kCODEC_CS42888:
            retVal = HAL_CODEC_CS42888_Deinit(handle);
            break;
#endif

#ifdef CODEC_CS42448_ENABLE
        case kCODEC_CS42448:
            retVal = HAL_CODEC_CS42448_Deinit(handle);
            break;
#endif

#ifdef CODEC_AK4497_ENABLE
        case kCODEC_AK4497:
            retVal = HAL_CODEC_AK4497_Deinit(handle);
            break;
#endif

#ifdef CODEC_AK4458_ENABLE
        case kCODEC_AK4458:
            retVal = HAL_CODEC_AK4458_Deinit(handle);
            break;
#endif

#ifdef CODEC_TFA9XXX_ENABLE
        case kCODEC_TFA9XXX:
            retVal = HAL_CODEC_TFA9XXX_Deinit(handle);
            break;
#endif
        default:
            retVal = kStatus_InvalidArgument;
            break;
    }

    return retVal;
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
status_t HAL_CODEC_SetFormat(void *handle, uint32_t mclk, uint32_t sampleRate, uint32_t bitWidth)
{
    assert(handle != NULL);
    status_t retVal = kStatus_Success;

    switch (((codec_handle_t *)handle)->codecConfig->codecDevType)
    {
#ifdef CODEC_WM8904_ENABLE
        case kCODEC_WM8904:
            retVal = HAL_CODEC_WM8904_SetFormat(handle, mclk, sampleRate, bitWidth);
            break;
#endif

#ifdef CODEC_WM8960_ENABLE
        case kCODEC_WM8960:
            retVal = HAL_CODEC_WM8960_SetFormat(handle, mclk, sampleRate, bitWidth);
            break;
#endif

#ifdef CODEC_WM8962_ENABLE
        case kCODEC_WM8962:
            retVal = HAL_CODEC_WM8962_SetFormat(handle, mclk, sampleRate, bitWidth);
            break;
#endif

#ifdef CODEC_WM8524_ENABLE
        case kCODEC_WM8524:
            retVal = HAL_CODEC_WM8524_SetFormat(handle, mclk, sampleRate, bitWidth);
            break;
#endif

#ifdef CODEC_SGTL5000_ENABLE
        case kCODEC_SGTL5000:
            retVal = HAL_CODEC_SGTL5000_SetFormat(handle, mclk, sampleRate, bitWidth);
            break;
#endif

#ifdef CODEC_DA7212_ENABLE
        case kCODEC_DA7212:
            retVal = HAL_CODEC_DA7212_SetFormat(handle, mclk, sampleRate, bitWidth);
            break;
#endif

#ifdef CODEC_CS42888_ENABLE
        case kCODEC_CS42888:
            retVal = HAL_CODEC_CS42888_SetFormat(handle, mclk, sampleRate, bitWidth);
            break;
#endif

#ifdef CODEC_CS42448_ENABLE
        case kCODEC_CS42448:
            retVal = HAL_CODEC_CS42448_SetFormat(handle, mclk, sampleRate, bitWidth);
            break;
#endif

#ifdef CODEC_AK4497_ENABLE
        case kCODEC_AK4497:
            retVal = HAL_CODEC_AK4497_SetFormat(handle, mclk, sampleRate, bitWidth);
            break;
#endif

#ifdef CODEC_AK4458_ENABLE
        case kCODEC_AK4458:
            retVal = HAL_CODEC_AK4458_SetFormat(handle, mclk, sampleRate, bitWidth);
            break;
#endif

#ifdef CODEC_TFA9XXX_ENABLE
        case kCODEC_TFA9XXX:
            retVal = HAL_CODEC_TFA9XXX_SetFormat(handle, mclk, sampleRate, bitWidth);
            break;
#endif
        default:
            retVal = kStatus_InvalidArgument;
            break;
    }

    return retVal;
}

/*!
 * brief set audio codec module volume.
 *
 * param handle codec handle.
 * param channel audio codec play channel, can be a value or combine value of _codec_play_channel.
 * param volume volume value, support 0 ~ 100, 0 is mute, 100 is the maximum volume value.
 * return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_SetVolume(void *handle, uint32_t playChannel, uint32_t volume)
{
    assert(handle != NULL);
    status_t retVal = kStatus_Success;

    switch (((codec_handle_t *)handle)->codecConfig->codecDevType)
    {
#ifdef CODEC_WM8904_ENABLE
        case kCODEC_WM8904:
            retVal = HAL_CODEC_WM8904_SetVolume(handle, playChannel, volume);
            break;
#endif

#ifdef CODEC_WM8960_ENABLE
        case kCODEC_WM8960:
            retVal = HAL_CODEC_WM8960_SetVolume(handle, playChannel, volume);
            break;
#endif

#ifdef CODEC_WM8962_ENABLE
        case kCODEC_WM8962:
            retVal = HAL_CODEC_WM8962_SetVolume(handle, playChannel, volume);
            break;
#endif

#ifdef CODEC_WM8524_ENABLE
        case kCODEC_WM8524:
            retVal = HAL_CODEC_WM8524_SetVolume(handle, playChannel, volume);
            break;
#endif

#ifdef CODEC_SGTL5000_ENABLE
        case kCODEC_SGTL5000:
            retVal = HAL_CODEC_SGTL5000_SetVolume(handle, playChannel, volume);
            break;
#endif

#ifdef CODEC_DA7212_ENABLE
        case kCODEC_DA7212:
            retVal = HAL_CODEC_DA7212_SetVolume(handle, playChannel, volume);
            break;
#endif

#ifdef CODEC_CS42888_ENABLE
        case kCODEC_CS42888:
            retVal = HAL_CODEC_CS42888_SetVolume(handle, playChannel, volume);
            break;
#endif

#ifdef CODEC_CS42448_ENABLE
        case kCODEC_CS42448:
            retVal = HAL_CODEC_CS42448_SetVolume(handle, playChannel, volume);
            break;
#endif

#ifdef CODEC_AK4497_ENABLE
        case kCODEC_AK4497:
            retVal = HAL_CODEC_AK4497_SetVolume(handle, playChannel, volume);
            break;
#endif

#ifdef CODEC_AK4458_ENABLE
        case kCODEC_AK4458:
            retVal = HAL_CODEC_AK4458_SetVolume(handle, playChannel, volume);
            break;
#endif

#ifdef CODEC_TFA9XXX_ENABLE
        case kCODEC_TFA9XXX:
            retVal = HAL_CODEC_TFA9XXX_SetVolume(handle, playChannel, volume);
            break;
#endif
        default:
            retVal = kStatus_InvalidArgument;
            break;
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
status_t HAL_CODEC_SetMute(void *handle, uint32_t playChannel, bool isMute)
{
    assert(handle != NULL);
    status_t retVal = kStatus_Success;

    switch (((codec_handle_t *)handle)->codecConfig->codecDevType)
    {
#ifdef CODEC_WM8904_ENABLE
        case kCODEC_WM8904:
            retVal = HAL_CODEC_WM8904_SetMute(handle, playChannel, isMute);
            break;
#endif

#ifdef CODEC_WM8960_ENABLE
        case kCODEC_WM8960:
            retVal = HAL_CODEC_WM8960_SetMute(handle, playChannel, isMute);
            break;
#endif

#ifdef CODEC_WM8962_ENABLE
        case kCODEC_WM8962:
            retVal = HAL_CODEC_WM8962_SetMute(handle, playChannel, isMute);
            break;
#endif

#ifdef CODEC_WM8524_ENABLE
        case kCODEC_WM8524:
            retVal = HAL_CODEC_WM8524_SetMute(handle, playChannel, isMute);
            break;
#endif

#ifdef CODEC_SGTL5000_ENABLE
        case kCODEC_SGTL5000:
            retVal = HAL_CODEC_SGTL5000_SetMute(handle, playChannel, isMute);
            break;
#endif

#ifdef CODEC_DA7212_ENABLE
        case kCODEC_DA7212:
            retVal = HAL_CODEC_DA7212_SetMute(handle, playChannel, isMute);
            break;
#endif

#ifdef CODEC_CS42888_ENABLE
        case kCODEC_CS42888:
            retVal = HAL_CODEC_CS42888_SetMute(handle, playChannel, isMute);
            break;
#endif

#ifdef CODEC_CS42448_ENABLE
        case kCODEC_CS42448:
            retVal = HAL_CODEC_CS42448_SetMute(handle, playChannel, isMute);
            break;
#endif

#ifdef CODEC_AK4497_ENABLE
        case kCODEC_AK4497:
            retVal = HAL_CODEC_AK4497_SetMute(handle, playChannel, isMute);
            break;
#endif

#ifdef CODEC_AK4458_ENABLE
        case kCODEC_AK4458:
            retVal = HAL_CODEC_AK4458_SetMute(handle, playChannel, isMute);
            break;
#endif

#ifdef CODEC_TFA9XXX_ENABLE
        case kCODEC_TFA9XXX:
            retVal = HAL_CODEC_TFA9XXX_SetMute(handle, playChannel, isMute);
            break;
#endif
        default:
            retVal = kStatus_InvalidArgument;
            break;
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
status_t HAL_CODEC_SetPower(void *handle, uint32_t module, bool powerOn)
{
    assert(handle != NULL);
    status_t retVal = kStatus_Success;

    switch (((codec_handle_t *)handle)->codecConfig->codecDevType)
    {
#ifdef CODEC_WM8904_ENABLE
        case kCODEC_WM8904:
            retVal = HAL_CODEC_WM8904_SetPower(handle, module, powerOn);
            break;
#endif

#ifdef CODEC_WM8960_ENABLE
        case kCODEC_WM8960:
            retVal = HAL_CODEC_WM8960_SetPower(handle, module, powerOn);
            break;
#endif

#ifdef CODEC_WM8962_ENABLE
        case kCODEC_WM8962:
            retVal = HAL_CODEC_WM8962_SetPower(handle, module, powerOn);
            break;
#endif

#ifdef CODEC_WM8524_ENABLE
        case kCODEC_WM8524:
            retVal = HAL_CODEC_WM8524_SetPower(handle, module, powerOn);
            break;
#endif

#ifdef CODEC_SGTL5000_ENABLE
        case kCODEC_SGTL5000:
            retVal = HAL_CODEC_SGTL5000_SetPower(handle, module, powerOn);
            break;
#endif

#ifdef CODEC_DA7212_ENABLE
        case kCODEC_DA7212:
            retVal = HAL_CODEC_DA7212_SetPower(handle, module, powerOn);
            break;
#endif

#ifdef CODEC_CS42888_ENABLE
        case kCODEC_CS42888:
            retVal = HAL_CODEC_CS42888_SetPower(handle, module, powerOn);
            break;
#endif

#ifdef CODEC_CS42448_ENABLE
        case kCODEC_CS42448:
            retVal = HAL_CODEC_CS42448_SetPower(handle, module, powerOn);
            break;
#endif

#ifdef CODEC_AK4497_ENABLE
        case kCODEC_AK4497:
            retVal = HAL_CODEC_AK4497_SetPower(handle, module, powerOn);
            break;
#endif

#ifdef CODEC_AK4458_ENABLE
        case kCODEC_AK4458:
            retVal = HAL_CODEC_AK4458_SetPower(handle, module, powerOn);
            break;
#endif

#ifdef CODEC_TFA9XXX_ENABLE
        case kCODEC_TFA9XXX:
            retVal = HAL_CODEC_TFA9XXX_SetPower(handle, module, powerOn);
            break;
#endif
        default:
            retVal = kStatus_InvalidArgument;
            break;
    }

    return retVal;
}

/*!
 * brief codec set record source.
 *
 * param handle codec handle.
 * param source audio codec record source, can be a value or combine value of _codec_record_source.
 *
 * return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_SetRecord(void *handle, uint32_t recordSource)
{
    assert(handle != NULL);
    status_t retVal = kStatus_Success;

    switch (((codec_handle_t *)handle)->codecConfig->codecDevType)
    {
#ifdef CODEC_WM8904_ENABLE
        case kCODEC_WM8904:
            retVal = HAL_CODEC_WM8904_SetRecord(handle, recordSource);
            break;
#endif

#ifdef CODEC_WM8960_ENABLE
        case kCODEC_WM8960:
            retVal = HAL_CODEC_WM8960_SetRecord(handle, recordSource);
            break;
#endif

#ifdef CODEC_WM8962_ENABLE
        case kCODEC_WM8962:
            retVal = HAL_CODEC_WM8962_SetRecord(handle, recordSource);
            break;
#endif

#ifdef CODEC_WM8524_ENABLE
        case kCODEC_WM8524:
            retVal = HAL_CODEC_WM8524_SetRecord(handle, recordSource);
            break;
#endif

#ifdef CODEC_SGTL5000_ENABLE
        case kCODEC_SGTL5000:
            retVal = HAL_CODEC_SGTL5000_SetRecord(handle, recordSource);
            break;
#endif

#ifdef CODEC_DA7212_ENABLE
        case kCODEC_DA7212:
            retVal = HAL_CODEC_DA7212_SetRecord(handle, recordSource);
            break;
#endif

#ifdef CODEC_CS42888_ENABLE
        case kCODEC_CS42888:
            retVal = HAL_CODEC_CS42888_SetRecord(handle, recordSource);
            break;
#endif

#ifdef CODEC_CS42448_ENABLE
        case kCODEC_CS42448:
            retVal = HAL_CODEC_CS42448_SetRecord(handle, recordSource);
            break;
#endif

#ifdef CODEC_AK4497_ENABLE
        case kCODEC_AK4497:
            retVal = HAL_CODEC_AK4497_SetRecord(handle, recordSource);
            break;
#endif

#ifdef CODEC_AK4458_ENABLE
        case kCODEC_AK4458:
            retVal = HAL_CODEC_AK4458_SetRecord(handle, recordSource);
            break;
#endif

#ifdef CODEC_TFA9XXX_ENABLE
        case kCODEC_TFA9XXX:
            retVal = HAL_CODEC_TFA9XXX_SetRecord(handle, recordSource);
            break;
#endif
        default:
            retVal = kStatus_InvalidArgument;
            break;
    }

    return retVal;
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
status_t HAL_CODEC_SetRecordChannel(void *handle, uint32_t leftRecordChannel, uint32_t rightRecordChannel)
{
    assert(handle != NULL);
    status_t retVal = kStatus_Success;

    switch (((codec_handle_t *)handle)->codecConfig->codecDevType)
    {
#ifdef CODEC_WM8904_ENABLE
        case kCODEC_WM8904:
            retVal = HAL_CODEC_WM8904_SetRecordChannel(handle, leftRecordChannel, rightRecordChannel);
            break;
#endif

#ifdef CODEC_WM8960_ENABLE
        case kCODEC_WM8960:
            retVal = HAL_CODEC_WM8960_SetRecordChannel(handle, leftRecordChannel, rightRecordChannel);
            break;
#endif

#ifdef CODEC_WM8962_ENABLE
        case kCODEC_WM8962:
            retVal = HAL_CODEC_WM8962_SetRecordChannel(handle, leftRecordChannel, rightRecordChannel);
            break;
#endif

#ifdef CODEC_WM8524_ENABLE
        case kCODEC_WM8524:
            retVal = HAL_CODEC_WM8524_SetRecordChannel(handle, leftRecordChannel, rightRecordChannel);
            break;
#endif

#ifdef CODEC_SGTL5000_ENABLE
        case kCODEC_SGTL5000:
            retVal = HAL_CODEC_SGTL5000_SetRecordChannel(handle, leftRecordChannel, rightRecordChannel);
            break;
#endif

#ifdef CODEC_DA7212_ENABLE
        case kCODEC_DA7212:
            retVal = HAL_CODEC_DA7212_SetRecordChannel(handle, leftRecordChannel, rightRecordChannel);
            break;
#endif

#ifdef CODEC_CS42888_ENABLE
        case kCODEC_CS42888:
            retVal = HAL_CODEC_CS42888_SetRecordChannel(handle, leftRecordChannel, rightRecordChannel);
            break;
#endif

#ifdef CODEC_CS42448_ENABLE
        case kCODEC_CS42448:
            retVal = HAL_CODEC_CS42448_SetRecordChannel(handle, leftRecordChannel, rightRecordChannel);
            break;
#endif

#ifdef CODEC_AK4497_ENABLE
        case kCODEC_AK4497:
            retVal = HAL_CODEC_AK4497_SetRecordChannel(handle, leftRecordChannel, rightRecordChannel);
            break;
#endif

#ifdef CODEC_AK4458_ENABLE
        case kCODEC_AK4458:
            retVal = HAL_CODEC_AK4458_SetRecordChannel(handle, leftRecordChannel, rightRecordChannel);
            break;
#endif

#ifdef CODEC_TFA9XXX_ENABLE
        case kCODEC_TFA9XXX:
            retVal = HAL_CODEC_TFA9XXX_SetRecordChannel(handle, leftRecordChannel, rightRecordChannel);
            break;
#endif
        default:
            retVal = kStatus_InvalidArgument;
            break;
    }

    return retVal;
}

/*!
 * brief codec set play source.
 *
 * param handle codec handle.
 * param playSource audio codec play source, can be a value or combine value of _codec_play_source.
 *
 * return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_SetPlay(void *handle, uint32_t playSource)
{
    assert(handle != NULL);
    status_t retVal = kStatus_Success;

    switch (((codec_handle_t *)handle)->codecConfig->codecDevType)
    {
#ifdef CODEC_WM8904_ENABLE
        case kCODEC_WM8904:
            retVal = HAL_CODEC_WM8904_SetPlay(handle, playSource);
            break;
#endif

#ifdef CODEC_WM8960_ENABLE
        case kCODEC_WM8960:
            retVal = HAL_CODEC_WM8960_SetPlay(handle, playSource);
            break;
#endif

#ifdef CODEC_WM8962_ENABLE
        case kCODEC_WM8962:
            retVal = HAL_CODEC_WM8962_SetPlay(handle, playSource);
            break;
#endif

#ifdef CODEC_WM8524_ENABLE
        case kCODEC_WM8524:
            retVal = HAL_CODEC_WM8524_SetPlay(handle, playSource);
            break;
#endif

#ifdef CODEC_SGTL5000_ENABLE
        case kCODEC_SGTL5000:
            retVal = HAL_CODEC_SGTL5000_SetPlay(handle, playSource);
            break;
#endif

#ifdef CODEC_DA7212_ENABLE
        case kCODEC_DA7212:
            retVal = HAL_CODEC_DA7212_SetPlay(handle, playSource);
            break;
#endif

#ifdef CODEC_CS42888_ENABLE
        case kCODEC_CS42888:
            retVal = HAL_CODEC_CS42888_SetPlay(handle, playSource);
            break;
#endif

#ifdef CODEC_CS42448_ENABLE
        case kCODEC_CS42448:
            retVal = HAL_CODEC_CS42448_SetPlay(handle, playSource);
            break;
#endif

#ifdef CODEC_AK4497_ENABLE
        case kCODEC_AK4497:
            retVal = HAL_CODEC_AK4497_SetPlay(handle, playSource);
            break;
#endif

#ifdef CODEC_AK4458_ENABLE
        case kCODEC_AK4458:
            retVal = HAL_CODEC_AK4458_SetPlay(handle, playSource);
            break;
#endif

#ifdef CODEC_TFA9XXX_ENABLE
        case kCODEC_TFA9XXX:
            retVal = HAL_CODEC_TFA9XXX_SetPlay(handle, playSource);
            break;
#endif
        default:
            retVal = kStatus_InvalidArgument;
            break;
    }

    return retVal;
}

/*!
 * brief codec module control.
 *
 * This function is used for codec module control, support switch digital interface cmd, can be expand to support codec
 * module specific feature
 *
 * param handle codec handle.
 * param cmd module control cmd, reference _codec_module_ctrl_cmd.
 * param data value to write, when cmd is kCODEC_ModuleRecordSourceChannel, the data should be a value combine
 *  of channel and source, please reference macro CODEC_MODULE_RECORD_SOURCE_CHANNEL(source, LP, LN, RP, RN), reference
 *  codec specific driver for detail configurations.
 * return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_ModuleControl(void *handle, uint32_t cmd, uint32_t data)
{
    assert(handle != NULL);
    status_t retVal = kStatus_Success;

    switch (((codec_handle_t *)handle)->codecConfig->codecDevType)
    {
#ifdef CODEC_WM8904_ENABLE
        case kCODEC_WM8904:
            retVal = HAL_CODEC_WM8904_ModuleControl(handle, cmd, data);
            break;
#endif

#ifdef CODEC_WM8960_ENABLE
        case kCODEC_WM8960:
            retVal = HAL_CODEC_WM8960_ModuleControl(handle, cmd, data);
            break;
#endif

#ifdef CODEC_WM8962_ENABLE
        case kCODEC_WM8962:
            retVal = HAL_CODEC_WM8962_ModuleControl(handle, cmd, data);
            break;
#endif

#ifdef CODEC_WM8524_ENABLE
        case kCODEC_WM8524:
            retVal = HAL_CODEC_WM8524_ModuleControl(handle, cmd, data);
            break;
#endif

#ifdef CODEC_SGTL5000_ENABLE
        case kCODEC_SGTL5000:
            retVal = HAL_CODEC_SGTL5000_ModuleControl(handle, cmd, data);
            break;
#endif

#ifdef CODEC_DA7212_ENABLE
        case kCODEC_DA7212:
            retVal = HAL_CODEC_DA7212_ModuleControl(handle, cmd, data);
            break;
#endif

#ifdef CODEC_CS42888_ENABLE
        case kCODEC_CS42888:
            retVal = HAL_CODEC_CS42888_ModuleControl(handle, cmd, data);
            break;
#endif

#ifdef CODEC_CS42448_ENABLE
        case kCODEC_CS42448:
            retVal = HAL_CODEC_CS42448_ModuleControl(handle, cmd, data);
            break;
#endif

#ifdef CODEC_AK4497_ENABLE
        case kCODEC_AK4497:
            retVal = HAL_CODEC_AK4497_ModuleControl(handle, cmd, data);
            break;
#endif

#ifdef CODEC_AK4458_ENABLE
        case kCODEC_AK4458:
            retVal = HAL_CODEC_AK4458_ModuleControl(handle, cmd, data);
            break;
#endif

        default:
            retVal = kStatus_InvalidArgument;
            break;
    }

    return retVal;
}
