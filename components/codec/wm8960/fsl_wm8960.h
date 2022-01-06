/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_WM8960_H_
#define _FSL_WM8960_H_

#include "fsl_codec_i2c.h"
#include "fsl_common.h"

/*!
 * @addtogroup wm8960
 * @ingroup codec
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @name Driver version */
/*@{*/
/*! @brief CLOCK driver version 2.2.0 */
#define FSL_WM8960_DRIVER_VERSION (MAKE_VERSION(2, 2, 0))
/*@}*/

/*! @brief wm8960 handle size */
#ifndef WM8960_I2C_HANDLER_SIZE
#define WM8960_I2C_HANDLER_SIZE CODEC_I2C_MASTER_HANDLER_SIZE
#endif

/*! @brief Define the register address of WM8960. */
#define WM8960_LINVOL  0x0U
#define WM8960_RINVOL  0x1U
#define WM8960_LOUT1   0x2U
#define WM8960_ROUT1   0x3U
#define WM8960_CLOCK1  0x4U
#define WM8960_DACCTL1 0x5U
#define WM8960_DACCTL2 0x6U
#define WM8960_IFACE1  0x7U
#define WM8960_CLOCK2  0x8U
#define WM8960_IFACE2  0x9U
#define WM8960_LDAC    0xaU
#define WM8960_RDAC    0xbU

#define WM8960_RESET   0xfU
#define WM8960_3D      0x10U
#define WM8960_ALC1    0x11U
#define WM8960_ALC2    0x12U
#define WM8960_ALC3    0x13U
#define WM8960_NOISEG  0x14U
#define WM8960_LADC    0x15U
#define WM8960_RADC    0x16U
#define WM8960_ADDCTL1 0x17U
#define WM8960_ADDCTL2 0x18U
#define WM8960_POWER1  0x19U
#define WM8960_POWER2  0x1aU
#define WM8960_ADDCTL3 0x1bU
#define WM8960_APOP1   0x1cU
#define WM8960_APOP2   0x1dU

#define WM8960_LINPATH 0x20U
#define WM8960_RINPATH 0x21U
#define WM8960_LOUTMIX 0x22U

#define WM8960_ROUTMIX  0x25U
#define WM8960_MONOMIX1 0x26U
#define WM8960_MONOMIX2 0x27U
#define WM8960_LOUT2    0x28U
#define WM8960_ROUT2    0x29U
#define WM8960_MONO     0x2aU
#define WM8960_INBMIX1  0x2bU
#define WM8960_INBMIX2  0x2cU
#define WM8960_BYPASS1  0x2dU
#define WM8960_BYPASS2  0x2eU
#define WM8960_POWER3   0x2fU
#define WM8960_ADDCTL4  0x30U
#define WM8960_CLASSD1  0x31U

#define WM8960_CLASSD3 0x33U
#define WM8960_PLL1    0x34U
#define WM8960_PLL2    0x35U
#define WM8960_PLL3    0x36U
#define WM8960_PLL4    0x37U

/*! @brief Cache register number */
#define WM8960_CACHEREGNUM 56U

/*! @brief WM8960 CLOCK2 bits */
#define WM8960_CLOCK2_BCLK_DIV_MASK 0xFU

/*! @brief WM8960_IFACE1 FORMAT bits */
#define WM8960_IFACE1_FORMAT_MASK  0x03U
#define WM8960_IFACE1_FORMAT_SHIFT 0x00U
#define WM8960_IFACE1_FORMAT_RJ    0x00U
#define WM8960_IFACE1_FORMAT_LJ    0x01U
#define WM8960_IFACE1_FORMAT_I2S   0x02U
#define WM8960_IFACE1_FORMAT_DSP   0x03U
#define WM8960_IFACE1_FORMAT(x)    (((x) << WM8960_IFACE1_FORMAT_SHIFT) & WM8960_IFACE1_FORMAT_MASK)

/*! @brief WM8960_IFACE1 WL bits */
#define WM8960_IFACE1_WL_MASK   0x0CU
#define WM8960_IFACE1_WL_SHIFT  0x02U
#define WM8960_IFACE1_WL_16BITS 0x00U
#define WM8960_IFACE1_WL_20BITS 0x01U
#define WM8960_IFACE1_WL_24BITS 0x02U
#define WM8960_IFACE1_WL_32BITS 0x03U
#define WM8960_IFACE1_WL(x)     (((x) << WM8960_IFACE1_WL_SHIFT) & WM8960_IFACE1_WL_MASK)

/*! @brief WM8960_IFACE1 LRP bit */
#define WM8960_IFACE1_LRP_MASK         0x10U
#define WM8960_IFACE1_LRP_SHIFT        0x04U
#define WM8960_IFACE1_LRCLK_NORMAL_POL 0x00U
#define WM8960_IFACE1_LRCLK_INVERT_POL 0x01U
#define WM8960_IFACE1_DSP_MODEA        0x00U
#define WM8960_IFACE1_DSP_MODEB        0x01U
#define WM8960_IFACE1_LRP(x)           (((x) << WM8960_IFACE1_LRP_SHIFT) & WM8960_IFACE1_LRP_MASK)

/*! @brief WM8960_IFACE1 DLRSWAP bit */
#define WM8960_IFACE1_DLRSWAP_MASK  0x20U
#define WM8960_IFACE1_DLRSWAP_SHIFT 0x05U
#define WM8960_IFACE1_DACCH_NORMAL  0x00U
#define WM8960_IFACE1_DACCH_SWAP    0x01U
#define WM8960_IFACE1_DLRSWAP(x)    (((x) << WM8960_IFACE1_DLRSWAP_SHIFT) & WM8960_IFACE1_DLRSWAP_MASK)

/*! @brief WM8960_IFACE1 MS bit */
#define WM8960_IFACE1_MS_MASK  0x40U
#define WM8960_IFACE1_MS_SHIFT 0x06U
#define WM8960_IFACE1_SLAVE    0x00U
#define WM8960_IFACE1_MASTER   0x01U
#define WM8960_IFACE1_MS(x)    (((x) << WM8960_IFACE1_MS_SHIFT) & WM8960_IFACE1_MS_MASK)

/*! @brief WM8960_IFACE1 BCLKINV bit */
#define WM8960_IFACE1_BCLKINV_MASK   0x80U
#define WM8960_IFACE1_BCLKINV_SHIFT  0x07U
#define WM8960_IFACE1_BCLK_NONINVERT 0x00U
#define WM8960_IFACE1_BCLK_INVERT    0x01U
#define WM8960_IFACE1_BCLKINV(x)     (((x) << WM8960_IFACE1_BCLKINV_SHIFT) & WM8960_IFACE1_BCLKINV_MASK)

/*! @brief WM8960_IFACE1 ALRSWAP bit */
#define WM8960_IFACE1_ALRSWAP_MASK  0x100U
#define WM8960_IFACE1_ALRSWAP_SHIFT 0x08U
#define WM8960_IFACE1_ADCCH_NORMAL  0x00U
#define WM8960_IFACE1_ADCCH_SWAP    0x01U
#define WM8960_IFACE1_ALRSWAP(x)    (((x) << WM8960_IFACE1_ALRSWAP_SHIFT) & WM8960_IFACE1_ALRSWAP_MASK)

/*! @brief WM8960_POWER1 */
#define WM8960_POWER1_VREF_MASK  0x40U
#define WM8960_POWER1_VREF_SHIFT 0x06U

#define WM8960_POWER1_AINL_MASK  0x20U
#define WM8960_POWER1_AINL_SHIFT 0x05U

#define WM8960_POWER1_AINR_MASK  0x10U
#define WM8960_POWER1_AINR_SHIFT 0x04U

#define WM8960_POWER1_ADCL_MASK  0x08U
#define WM8960_POWER1_ADCL_SHIFT 0x03U

#define WM8960_POWER1_ADCR_MASK  0x0U
#define WM8960_POWER1_ADCR_SHIFT 0x02U

#define WM8960_POWER1_MICB_MASK  0x02U
#define WM8960_POWER1_MICB_SHIFT 0x01U

#define WM8960_POWER1_DIGENB_MASK  0x01U
#define WM8960_POWER1_DIGENB_SHIFT 0x00U

/*! @brief WM8960_POWER2 */
#define WM8960_POWER2_DACL_MASK  0x100U
#define WM8960_POWER2_DACL_SHIFT 0x08U

#define WM8960_POWER2_DACR_MASK  0x80U
#define WM8960_POWER2_DACR_SHIFT 0x07U

#define WM8960_POWER2_LOUT1_MASK  0x40U
#define WM8960_POWER2_LOUT1_SHIFT 0x06U

#define WM8960_POWER2_ROUT1_MASK  0x20U
#define WM8960_POWER2_ROUT1_SHIFT 0x05U

#define WM8960_POWER2_SPKL_MASK  0x10U
#define WM8960_POWER2_SPKL_SHIFT 0x04U

#define WM8960_POWER2_SPKR_MASK  0x08U
#define WM8960_POWER2_SPKR_SHIFT 0x03U

#define WM8960_POWER3_LMIC_MASK   0x20U
#define WM8960_POWER3_LMIC_SHIFT  0x05U
#define WM8960_POWER3_RMIC_MASK   0x10U
#define WM8960_POWER3_RMIC_SHIFT  0x04U
#define WM8960_POWER3_LOMIX_MASK  0x08U
#define WM8960_POWER3_LOMIX_SHIFT 0x03U
#define WM8960_POWER3_ROMIX_MASK  0x04U
#define WM8960_POWER3_ROMIX_SHIFT 0x02U
/*! @brief WM8960 I2C address. */
#define WM8960_I2C_ADDR 0x1A
/*! @brief WM8960 I2C baudrate */
#define WM8960_I2C_BAUDRATE (100000U)
/*! @brief WM8960 maximum volume value */
#define WM8960_ADC_MAX_VOLUME_vALUE       0xFFU
#define WM8960_DAC_MAX_VOLUME_vALUE       0xFFU
#define WM8960_HEADPHONE_MAX_VOLUME_vALUE 0x7FU
#define WM8960_HEADPHONE_MIN_VOLUME_vALUE 0x30U
#define WM8960_LINEIN_MAX_VOLUME_vALUE    0x3FU
#define WM8960_SPEAKER_MAX_VOLUME_vALUE   0x7FU
#define WM8960_SPEAKER_MIN_VOLUME_vALUE   0x30U

/*! @brief Modules in WM8960 board. */
typedef enum _wm8960_module
{
    kWM8960_ModuleADC     = 0, /*!< ADC module in WM8960 */
    kWM8960_ModuleDAC     = 1, /*!< DAC module in WM8960 */
    kWM8960_ModuleVREF    = 2, /*!< VREF module */
    kWM8960_ModuleHP      = 3, /*!< Headphone */
    kWM8960_ModuleMICB    = 4, /*!< Mic bias */
    kWM8960_ModuleMIC     = 5, /*!< Input Mic */
    kWM8960_ModuleLineIn  = 6, /*!< Analog in PGA  */
    kWM8960_ModuleLineOut = 7, /*!< Line out module */
    kWM8960_ModuleSpeaker = 8, /*!< Speaker module */
    kWM8960_ModuleOMIX    = 9, /*!< Output mixer */
} wm8960_module_t;

/*! @brief wm8960 play channel
 * @anchor _wm8960_play_channel
 */
enum
{
    kWM8960_HeadphoneLeft  = 1, /*!< wm8960 headphone left channel */
    kWM8960_HeadphoneRight = 2, /*!< wm8960 headphone right channel */
    kWM8960_SpeakerLeft    = 4, /*!< wm8960 speaker left channel */
    kWM8960_SpeakerRight   = 8, /*!< wm8960 speaker right channel */
};

/*! @brief wm8960 play source */
typedef enum _wm8960_play_source
{
    kWM8960_PlaySourcePGA   = 1, /*!< wm8960 play source PGA */
    kWM8960_PlaySourceInput = 2, /*!< wm8960 play source Input */
    kWM8960_PlaySourceDAC   = 4, /*!< wm8960 play source DAC */
} wm8960_play_source_t;

/*!
 * @brief WM8960 data route.
 * Only provide some typical data route, not all route listed.
 * Note: Users cannot combine any routes, once a new route is set, the previous one would be replaced.
 */
typedef enum _wm8960_route
{
    kWM8960_RouteBypass            = 0, /*!< LINEIN->Headphone. */
    kWM8960_RoutePlayback          = 1, /*!<  I2SIN->DAC->Headphone. */
    kWM8960_RoutePlaybackandRecord = 2, /*!< I2SIN->DAC->Headphone, LINEIN->ADC->I2SOUT. */
    kWM8960_RouteRecord            = 5  /*!< LINEIN->ADC->I2SOUT. */
} wm8960_route_t;

/*!
 * @brief The audio data transfer protocol choice.
 * WM8960 only supports I2S format and PCM format.
 */
typedef enum _wm8960_protocol
{
    kWM8960_BusI2S            = 2,           /*!< I2S type */
    kWM8960_BusLeftJustified  = 1,           /*!< Left justified mode */
    kWM8960_BusRightJustified = 0,           /*!< Right justified mode */
    kWM8960_BusPCMA           = 3,           /*!< PCM A mode */
    kWM8960_BusPCMB           = 3 | (1 << 4) /*!< PCM B mode */
} wm8960_protocol_t;

/*! @brief wm8960 input source */
typedef enum _wm8960_input
{
    kWM8960_InputClosed                = 0, /*!< Input device is closed */
    kWM8960_InputSingleEndedMic        = 1, /*!< Input as single ended mic, only use L/RINPUT1 */
    kWM8960_InputDifferentialMicInput2 = 2, /*!< Input as differential mic, use L/RINPUT1 and L/RINPUT2 */
    kWM8960_InputDifferentialMicInput3 = 3, /*!< Input as differential mic, use L/RINPUT1 and L/RINPUT3*/
    kWM8960_InputLineINPUT2            = 4, /*!< Input as line input, only use L/RINPUT2 */
    kWM8960_InputLineINPUT3            = 5  /*!< Input as line input, only use L/RINPUT3 */
} wm8960_input_t;

/*! @brief audio sample rate definition
 * @anchor _wm8960_sample_rate
 */
enum
{
    kWM8960_AudioSampleRate8KHz    = 8000U,   /*!< Sample rate 8000 Hz */
    kWM8960_AudioSampleRate11025Hz = 11025U,  /*!< Sample rate 11025 Hz */
    kWM8960_AudioSampleRate12KHz   = 12000U,  /*!< Sample rate 12000 Hz */
    kWM8960_AudioSampleRate16KHz   = 16000U,  /*!< Sample rate 16000 Hz */
    kWM8960_AudioSampleRate22050Hz = 22050U,  /*!< Sample rate 22050 Hz */
    kWM8960_AudioSampleRate24KHz   = 24000U,  /*!< Sample rate 24000 Hz */
    kWM8960_AudioSampleRate32KHz   = 32000U,  /*!< Sample rate 32000 Hz */
    kWM8960_AudioSampleRate44100Hz = 44100U,  /*!< Sample rate 44100 Hz */
    kWM8960_AudioSampleRate48KHz   = 48000U,  /*!< Sample rate 48000 Hz */
    kWM8960_AudioSampleRate96KHz   = 96000U,  /*!< Sample rate 96000 Hz */
    kWM8960_AudioSampleRate192KHz  = 192000U, /*!< Sample rate 192000 Hz */
    kWM8960_AudioSampleRate384KHz  = 384000U, /*!< Sample rate 384000 Hz */
};

/*! @brief audio bit width
 * @anchor _wm8960_audio_bit_width
 */
enum
{
    kWM8960_AudioBitWidth16bit = 16U, /*!< audio bit width 16 */
    kWM8960_AudioBitWidth20bit = 20U, /*!< audio bit width 20 */
    kWM8960_AudioBitWidth24bit = 24U, /*!< audio bit width 24 */
    kWM8960_AudioBitWidth32bit = 32U, /*!< audio bit width 32 */
};

/*! @brief wm8960 sysclk source */
typedef enum _wm8960_sysclk_source
{
    kWM8960_SysClkSourceMclk        = 0U, /*!< sysclk source from external MCLK */
    kWM8960_SysClkSourceInternalPLL = 1U, /*!< sysclk source from internal PLL */
} wm8960_sysclk_source_t;

/*! @brief wm8960 audio format */
typedef struct _wm8960_audio_format
{
    uint32_t mclk_HZ;    /*!< master clock frequency */
    uint32_t sampleRate; /*!< sample rate */
    uint32_t bitWidth;   /*!< bit width */
} wm8960_audio_format_t;

/*! @brief wm8960 master system clock configuration */
typedef struct _wm8960_master_sysclk_config
{
    wm8960_sysclk_source_t sysclkSource; /*!< sysclk source */
    uint32_t sysclkFreq;                 /*!< PLL output frequency value */
} wm8960_master_sysclk_config_t;

/*! @brief Initialize structure of WM8960 */
typedef struct wm8960_config
{
    wm8960_route_t route;                      /*!< Audio data route.*/
    wm8960_protocol_t bus;                     /*!< Audio transfer protocol */
    wm8960_audio_format_t format;              /*!< Audio format */
    bool master_slave;                         /*!< Master or slave. */
    wm8960_master_sysclk_config_t masterClock; /*!< master clock configurations */
    bool enableSpeaker;                        /*!< True means enable class D speaker as output, false means no */
    wm8960_input_t leftInputSource;            /*!< Left input source for WM8960 */
    wm8960_input_t rightInputSource;           /*!< Right input source for wm8960 */
    wm8960_play_source_t playSource;           /*!< play source */
    uint8_t slaveAddress;                      /*!< wm8960 device address */
    codec_i2c_config_t i2cConfig;              /*!< i2c configuration */
} wm8960_config_t;

/*! @brief wm8960 codec handler
 */
typedef struct _wm8960_handle
{
    const wm8960_config_t *config;              /*!< wm8904 config pointer */
    uint8_t i2cHandle[WM8960_I2C_HANDLER_SIZE]; /*!< i2c handle */
} wm8960_handle_t;
/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief WM8960 initialize function.
 *
 * The second parameter is NULL to WM8960 in this version. If users want
 * to change the settings, they have to use wm8960_write_reg() or wm8960_modify_reg()
 * to set the register value of WM8960.
 * Note: If the codec_config is NULL, it would initialize WM8960 using default settings.
 * The default setting:
 * codec_config->route = kWM8960_RoutePlaybackandRecord
 * codec_config->bus = kWM8960_BusI2S
 * codec_config->master = slave
 *
 * @param handle WM8960 handle structure.
 * @param config WM8960 configuration structure.
 */
status_t WM8960_Init(wm8960_handle_t *handle, const wm8960_config_t *config);

/*!
 * @brief Deinit the WM8960 codec.
 *
 * This function close all modules in WM8960 to save power.
 *
 * @param handle WM8960 handle structure pointer.
 */
status_t WM8960_Deinit(wm8960_handle_t *handle);

/*!
 * @brief Set audio data route in WM8960.
 *
 * This function would set the data route according to route. The route cannot be combined,
 * as all route would enable different modules.
 * Note: If a new route is set, the previous route would not work.
 *
 * @param handle WM8960 handle structure.
 * @param route Audio data route in WM8960.
 */
status_t WM8960_SetDataRoute(wm8960_handle_t *handle, wm8960_route_t route);

/*!
 * @brief Set left audio input source in WM8960.
 *
 * @param handle WM8960 handle structure.
 * @param input Audio input source.
 */
status_t WM8960_SetLeftInput(wm8960_handle_t *handle, wm8960_input_t input);

/*!
 * @brief Set right audio input source in WM8960.
 *
 * @param handle WM8960 handle structure.
 * @param input Audio input source.
 */
status_t WM8960_SetRightInput(wm8960_handle_t *handle, wm8960_input_t input);

/*!
 * @brief Set the audio transfer protocol.
 *
 * WM8960 only supports I2S, left justified, right justified, PCM A, PCM B format.
 *
 * @param handle WM8960 handle structure.
 * @param protocol Audio data transfer protocol.
 */
status_t WM8960_SetProtocol(wm8960_handle_t *handle, wm8960_protocol_t protocol);

/*!
 * @brief Set WM8960 as master or slave.
 *
 * @param handle WM8960 handle structure.
 * @param master 1 represent master, 0 represent slave.
 */
void WM8960_SetMasterSlave(wm8960_handle_t *handle, bool master);

/*!
 * @brief Set the volume of different modules in WM8960.
 *
 * This function would set the volume of WM8960 modules. Uses need to appoint the module.
 * The function assume that left channel and right channel has the same volume.
 *
 * Module:kWM8960_ModuleADC, volume range value: 0 is mute, 1-255 is -97db to 30db
 * Module:kWM8960_ModuleDAC, volume range value: 0 is mute, 1-255 is -127db to 0db
 * Module:kWM8960_ModuleHP, volume range value: 0 - 2F is mute, 0x30 - 0x7F is -73db to 6db
 * Module:kWM8960_ModuleLineIn, volume range value: 0 - 0x3F is -17.25db to 30db
 * Module:kWM8960_ModuleSpeaker, volume range value: 0 - 2F is mute, 0x30 - 0x7F is -73db to 6db
 *
 *
 * @param handle WM8960 handle structure.
 * @param module Module to set volume, it can be ADC, DAC, Headphone and so on.
 * @param volume Volume value need to be set.
 */
status_t WM8960_SetVolume(wm8960_handle_t *handle, wm8960_module_t module, uint32_t volume);

/*!
 * @brief Get the volume of different modules in WM8960.
 *
 * This function gets the volume of WM8960 modules. Uses need to appoint the module.
 * The function assume that left channel and right channel has the same volume.
 *
 * @param handle WM8960 handle structure.
 * @param module Module to set volume, it can be ADC, DAC, Headphone and so on.
 * @return Volume value of the module.
 */
uint32_t WM8960_GetVolume(wm8960_handle_t *handle, wm8960_module_t module);

/*!
 * @brief Mute modules in WM8960.
 *
 * @param handle WM8960 handle structure.
 * @param module Modules need to be mute.
 * @param isEnabled Mute or unmute, 1 represent mute.
 */
status_t WM8960_SetMute(wm8960_handle_t *handle, wm8960_module_t module, bool isEnabled);

/*!
 * @brief Enable/disable expected devices.
 *
 * @param handle WM8960 handle structure.
 * @param module Module expected to enable.
 * @param isEnabled Enable or disable moudles.
 */
status_t WM8960_SetModule(wm8960_handle_t *handle, wm8960_module_t module, bool isEnabled);

/*!
 * @brief SET the WM8960 play source.
 *
 * @param handle WM8960 handle structure.
 * @param playSource play source , can be a value combine of kWM8960_ModuleHeadphoneSourcePGA,
 * kWM8960_ModuleHeadphoneSourceDAC, kWM8960_ModulePlaySourceInput, kWM8960_ModulePlayMonoRight,
 * kWM8960_ModulePlayMonoLeft.
 *
 * @return kStatus_WM8904_Success if successful, different code otherwise..
 */
status_t WM8960_SetPlay(wm8960_handle_t *handle, uint32_t playSource);

/*!
 * @brief Configure the data format of audio data.
 *
 * This function would configure the registers about the sample rate, bit depths.
 *
 * @param handle WM8960 handle structure pointer.
 * @param sysclk system clock of the codec which can be generated by MCLK or PLL output.
 * @param sample_rate Sample rate of audio file running in WM8960. WM8960 now
 * supports 8k, 11.025k, 12k, 16k, 22.05k, 24k, 32k, 44.1k, 48k and 96k sample rate.
 * @param bits Bit depth of audio file (WM8960 only supports 16bit, 20bit, 24bit
 * and 32 bit in HW).
 */
status_t WM8960_ConfigDataFormat(wm8960_handle_t *handle, uint32_t sysclk, uint32_t sample_rate, uint32_t bits);

/*!
 * @brief Enable/disable jack detect feature.
 *
 * @param handle WM8960 handle structure.
 * @param isEnabled Enable or disable moudles.
 */
status_t WM8960_SetJackDetect(wm8960_handle_t *handle, bool isEnabled);

/*!
 * @brief Write register to WM8960 using I2C.
 *
 * @param handle WM8960 handle structure.
 * @param reg The register address in WM8960.
 * @param val Value needs to write into the register.
 */
status_t WM8960_WriteReg(wm8960_handle_t *handle, uint8_t reg, uint16_t val);

/*!
 * @brief Read register from WM8960 using I2C.
 * @param reg The register address in WM8960.
 * @param val Value written to.
 */
status_t WM8960_ReadReg(uint8_t reg, uint16_t *val);

/*!
 * @brief Modify some bits in the register using I2C.
 * @param handle WM8960 handle structure.
 * @param reg The register address in WM8960.
 * @param mask The mask code for the bits want to write. The bit you want to write should be 0.
 * @param val Value needs to write into the register.
 */
status_t WM8960_ModifyReg(wm8960_handle_t *handle, uint8_t reg, uint16_t mask, uint16_t val);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_WM8960_H_ */

/*******************************************************************************
 * API
 ******************************************************************************/
