/*
 * Copyright 2022-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_WM8962_H_
#define _FSL_WM8962_H_

#include "fsl_codec_i2c.h"
#include "fsl_common.h"

/*!
 * @addtogroup wm8962
 * @ingroup codec
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @name Driver version */
/*! @{ */
/*! @brief CLOCK driver version 2.1.3 */
#define FSL_WM8962_DRIVER_VERSION (MAKE_VERSION(2, 2, 0))
/*! @} */

/*! @brief wm8962 handle size */
#ifndef WM8962_I2C_HANDLER_SIZE
#define WM8962_I2C_HANDLER_SIZE CODEC_I2C_MASTER_HANDLER_SIZE
#endif

#define DEBUG_WM8962_REGISTER 0
#if DEBUG_WM8962_REGISTER
#include "fsl_debug_console.h"
#endif

#define DEBUG_WM8962_MODULE_NUM 11

/*! @brief Define the register address of WM8962. */
#define WM8962_LINVOL  0x0U
#define WM8962_RINVOL  0x1U
#define WM8962_LOUT1   0x2U
#define WM8962_ROUT1   0x3U
#define WM8962_CLOCK1  0x4U
#define WM8962_DACCTL1 0x5U
#define WM8962_DACCTL2 0x6U
#define WM8962_IFACE0  0x7U
#define WM8962_IFACE1  0x9U
#define WM8962_CLOCK2  0x8U
#define WM8962_IFACE2  0xEU
#define WM8962_LDAC    0xaU
#define WM8962_RDAC    0xbU

#define WM8962_RESET         0xfU
#define WM8962_3D            0x10U
#define WM8962_ALC1          0x11U
#define WM8962_ALC2          0x12U
#define WM8962_ALC3          0x13U
#define WM8962_NOISEG        0x14U
#define WM8962_LADC          0x15U
#define WM8962_RADC          0x16U
#define WM8962_ADDCTL1       0x17U
#define WM8962_ADDCTL2       0x18U
#define WM8962_POWER1        0x19U
#define WM8962_POWER2        0x1aU
#define WM8962_ADDCTL3       0x1bU
#define WM8962_APOP1         0x1cU
#define WM8962_APOP2         0x1dU
#define WM8962_INPUT_MIXER_1 0x1FU

#define WM8962_LINPATH  0x20U
#define WM8962_RINPATH  0x21U
#define WM8962_INPUTMIX 0x22U

#define WM8962_LEFT_INPUT_PGA  0x25U
#define WM8962_RIGHT_INPUT_PGA 0x26U
#define WM8962_MONOMIX2        0x27U
#define WM8962_LOUT2           0x28U
#define WM8962_ROUT2           0x29U
#define WM8962_TEMP            0x2FU
#define WM8962_ADDCTL4         0x30U
#define WM8962_CLASSD1         0x31U

#define WM8962_CLASSD3       0x33U
#define WM8962_PLL1          0x34U
#define WM8962_PLL2          0x35U
#define WM8962_PLL3          0x36U
#define WM8962_PLL4          0x37U
#define WM8962_CLK4          0x38U
#define WM8962_DC_SERVO_0    0x3CU
#define WM8962_DC_SERVO_1    0x3DU
#define WM8962_ANALOG_HP_0   0x45U
#define WM8962_CHARGE_PUMP_1 0x48U

#define WM8962_LEFT_HEADPHONE_MIXER         0x64U
#define WM8962_RIGHT_HEADPHONE_MIXER        0x65U
#define WM8962_LEFT_HEADPHONE_MIXER_VOLUME  0x66U
#define WM8962_RIGHT_HEADPHONE_MIXER_VOLUME 0x67U

#define WM8962_LEFT_SPEAKER_MIXER         0x69U
#define WM8962_RIGHT_SPEAKER_MIXER        0x6AU
#define WM8962_LEFT_SPEAKER_MIXER_VOLUME  0x6BU
#define WM8962_RIGHT_SPEAKER_MIXER_VOLUME 0x6CU

#define WM8962_FLL_CTRL_1   0x9BU
#define WM8962_FLL_CTRL_2   0x9CU
#define WM8962_FLL_CTRL_3   0x9DU
#define WM8962_FLL_CTRL_6   0xA0U
#define WM8962_FLL_CTRL_7   0xA1U
#define WM8962_FLL_CTRL_8   0xA2U
#define WM8962_INT_STATUS_2 0x231U
/*! @brief Cache register number */
#define WM8962_CACHEREGNUM 56U

/*! @brief WM8962 CLOCK2 bits */
#define WM8962_CLOCK2_BCLK_DIV_MASK 0xFU

/*! @brief WM8962_IFACE0 FORMAT bits */
#define WM8962_IFACE0_FORMAT_MASK  0x13U
#define WM8962_IFACE0_FORMAT_SHIFT 0x00U
#define WM8962_IFACE0_FORMAT_RJ    0x00U
#define WM8962_IFACE0_FORMAT_LJ    0x01U
#define WM8962_IFACE0_FORMAT_I2S   0x02U
#define WM8962_IFACE0_FORMAT_DSP   0x03U
#define WM8962_IFACE0_FORMAT(x)    (((x) << WM8962_IFACE1_FORMAT_SHIFT) & WM8962_IFACE1_FORMAT_MASK)

/*! @brief WM8962_IFACE0 WL bits */
#define WM8962_IFACE0_WL_MASK   0x0CU
#define WM8962_IFACE0_WL_SHIFT  0x02U
#define WM8962_IFACE0_WL_16BITS 0x00U
#define WM8962_IFACE0_WL_20BITS 0x01U
#define WM8962_IFACE0_WL_24BITS 0x02U
#define WM8962_IFACE0_WL_32BITS 0x03U
#define WM8962_IFACE0_WL(x)     (((x) << WM8962_IFACE0_WL_SHIFT) & WM8962_IFACE0_WL_MASK)

/*! @brief WM8962_IFACE1 LRP bit */
#define WM8962_IFACE1_LRP_MASK         0x10U
#define WM8962_IFACE1_LRP_SHIFT        0x04U
#define WM8962_IFACE1_LRCLK_NORMAL_POL 0x00U
#define WM8962_IFACE1_LRCLK_INVERT_POL 0x01U
#define WM8962_IFACE1_DSP_MODEA        0x00U
#define WM8962_IFACE1_DSP_MODEB        0x01U
#define WM8962_IFACE1_LRP(x)           (((x) << WM8962_IFACE1_LRP_SHIFT) & WM8962_IFACE1_LRP_MASK)

/*! @brief WM8962_IFACE1 DLRSWAP bit */
#define WM8962_IFACE1_DLRSWAP_MASK  0x20U
#define WM8962_IFACE1_DLRSWAP_SHIFT 0x05U
#define WM8962_IFACE1_DACCH_NORMAL  0x00U
#define WM8962_IFACE1_DACCH_SWAP    0x01U
#define WM8962_IFACE1_DLRSWAP(x)    (((x) << WM8962_IFACE1_DLRSWAP_SHIFT) & WM8962_IFACE1_DLRSWAP_MASK)

/*! @brief WM8962_IFACE1 MS bit */
#define WM8962_IFACE1_MS_MASK  0x40U
#define WM8962_IFACE1_MS_SHIFT 0x06U
#define WM8962_IFACE1_SLAVE    0x00U
#define WM8962_IFACE1_MASTER   0x01U
#define WM8962_IFACE1_MS(x)    (((x) << WM8962_IFACE1_MS_SHIFT) & WM8962_IFACE1_MS_MASK)

/*! @brief WM8962_IFACE1 BCLKINV bit */
#define WM8962_IFACE1_BCLKINV_MASK   0x80U
#define WM8962_IFACE1_BCLKINV_SHIFT  0x07U
#define WM8962_IFACE1_BCLK_NONINVERT 0x00U
#define WM8962_IFACE1_BCLK_INVERT    0x01U
#define WM8962_IFACE1_BCLKINV(x)     (((x) << WM8962_IFACE1_BCLKINV_SHIFT) & WM8962_IFACE1_BCLKINV_MASK)

/*! @brief WM8962_IFACE1 ALRSWAP bit */
#define WM8962_IFACE1_ALRSWAP_MASK  0x100U
#define WM8962_IFACE1_ALRSWAP_SHIFT 0x08U
#define WM8962_IFACE1_ADCCH_NORMAL  0x00U
#define WM8962_IFACE1_ADCCH_SWAP    0x01U
#define WM8962_IFACE1_ALRSWAP(x)    (((x) << WM8962_IFACE1_ALRSWAP_SHIFT) & WM8962_IFACE1_ALRSWAP_MASK)

/*! @brief WM8962_POWER1 */
#define WM8962_POWER1_VREF_MASK  0x40U
#define WM8962_POWER1_VREF_SHIFT 0x06U

#define WM8962_POWER1_AINL_MASK  0x20U
#define WM8962_POWER1_AINL_SHIFT 0x05U

#define WM8962_POWER1_AINR_MASK  0x10U
#define WM8962_POWER1_AINR_SHIFT 0x04U

#define WM8962_POWER1_ADCL_MASK  0x08U
#define WM8962_POWER1_ADCL_SHIFT 0x03U

#define WM8962_POWER1_ADCR_MASK  0x4U
#define WM8962_POWER1_ADCR_SHIFT 0x02U

#define WM8962_POWER1_MICB_MASK  0x02U
#define WM8962_POWER1_MICB_SHIFT 0x01U

#define WM8962_POWER1_DIGENB_MASK  0x01U
#define WM8962_POWER1_DIGENB_SHIFT 0x00U

/*! @brief WM8962_POWER2 */
#define WM8962_POWER2_DACL_MASK  0x100U
#define WM8962_POWER2_DACL_SHIFT 0x08U

#define WM8962_POWER2_DACR_MASK  0x80U
#define WM8962_POWER2_DACR_SHIFT 0x07U

#define WM8962_POWER2_LOUT1_MASK  0x40U
#define WM8962_POWER2_LOUT1_SHIFT 0x06U

#define WM8962_POWER2_ROUT1_MASK  0x20U
#define WM8962_POWER2_ROUT1_SHIFT 0x05U

#define WM8962_POWER2_SPKL_MASK  0x10U
#define WM8962_POWER2_SPKL_SHIFT 0x04U

#define WM8962_POWER2_SPKR_MASK  0x08U
#define WM8962_POWER2_SPKR_SHIFT 0x03U

#define WM8962_POWER3_LMIC_MASK   0x20U
#define WM8962_POWER3_LMIC_SHIFT  0x05U
#define WM8962_POWER3_RMIC_MASK   0x10U
#define WM8962_POWER3_RMIC_SHIFT  0x04U
#define WM8962_POWER3_LOMIX_MASK  0x08U
#define WM8962_POWER3_LOMIX_SHIFT 0x03U
#define WM8962_POWER3_ROMIX_MASK  0x04U
#define WM8962_POWER3_ROMIX_SHIFT 0x02U
/*! @brief WM8962 I2C address. */
#define WM8962_I2C_ADDR (0x34 >> 1U)
/*! @brief WM8962 I2C baudrate */
#define WM8962_I2C_BAUDRATE (100000U)
/*! @brief WM8962 maximum volume value */
#define WM8962_ADC_MAX_VOLUME_vALUE       0xFFU
#define WM8962_DAC_MAX_VOLUME_vALUE       0xFFU
#define WM8962_HEADPHONE_MAX_VOLUME_vALUE 0x7FU
#define WM8962_HEADPHONE_MIN_VOLUME_vALUE 0x2FU
#define WM8962_LINEIN_MAX_VOLUME_vALUE    0x3FU
#define WM8962_SPEAKER_MAX_VOLUME_vALUE   0x7FU
#define WM8962_SPEAKER_MIN_VOLUME_vALUE   0x2FU

/*! @brief wm8962 input mixer source.
 * @anchor wm8962_input_mixer_source_t
 */
enum
{
    kWM8962_InputMixerSourceInput2   = 4U, /*!< input mixer source input 2 */
    kWM8962_InputMixerSourceInput3   = 2U, /*!< input mixer source input 3 */
    kWM8962_InputMixerSourceInputPGA = 1U, /*!< input mixer source input PGA */
};

/*! @brief wm8962 output mixer source.
 * @anchor wm8962_output_mixer_source_t
 */
enum
{
    kWM8962_OutputMixerDisabled              = 0U,    /*!< output mixer disabled */
    kWM8962_OutputMixerSourceInput4Right     = 1U,    /*!< output mixer source input 4 left */
    kWM8962_OutputMixerSourceInput4Left      = 2U,    /*!< output mixer source input 4 right */
    kWM8962_OutputMixerSourceRightInputMixer = 4U,    /*!< output mixer source left input mixer */
    kWM8962_OutputMixerSourceLeftInputMixer  = 8U,    /*!< output mixer source right input mixer*/
    kWM8962_OutputMixerSourceRightDAC        = 0x10U, /*!< output mixer source left DAC */
    kWM8962_OutputMixerSourceLeftDAC         = 0x20U, /*!< output mixer source Right DAC */
};

/*! @brief Modules in WM8962 board. */
typedef enum _wm8962_module
{
    kWM8962_ModuleADC           = 0,  /*!< ADC module in WM8962 */
    kWM8962_ModuleDAC           = 1,  /*!< DAC module in WM8962 */
    kWM8962_ModuleMICB          = 4,  /*!< Mic bias */
    kWM8962_ModuleMIC           = 5,  /*!< Input Mic */
    kWM8962_ModuleLineIn        = 6,  /*!< Analog in PGA  */
    kWM8962_ModuleHeadphone     = 7,  /*!< Line out module */
    kWM8962_ModuleSpeaker       = 8,  /*!< Speaker module */
    kWM8962_ModuleHeaphoneMixer = 9,  /*!< Output mixer */
    kWM8962_ModuleSpeakerMixer  = 10, /*!< Output mixer */
} wm8962_module_t;

/*! @brief wm8962 play channel
 * @anchor _wm8962_play_channel
 */
enum
{
    kWM8962_HeadphoneLeft  = 1, /*!< wm8962 headphone left channel */
    kWM8962_HeadphoneRight = 2, /*!< wm8962 headphone right channel */
    kWM8962_SpeakerLeft    = 4, /*!< wm8962 speaker left channel */
    kWM8962_SpeakerRight   = 8, /*!< wm8962 speaker right channel */
};

/*!
 * @brief The audio data transfer protocol choice.
 * WM8962 only supports I2S format and PCM format.
 */
typedef enum _wm8962_protocol
{
    kWM8962_BusPCMA           = 4, /*!< PCMA mode */
    kWM8962_BusPCMB           = 3, /*!< PCMB mode */
    kWM8962_BusI2S            = 2, /*!< I2S type */
    kWM8962_BusLeftJustified  = 1, /*!< Left justified mode */
    kWM8962_BusRightJustified = 0, /*!< Right justified mode */
} wm8962_protocol_t;

/*! @brief wm8962 input source */
typedef enum _wm8962_input_pga_source
{
    kWM8962_InputPGASourceInput1 = 8, /*!< Input PGA source input1 */
    kWM8962_InputPGASourceInput2 = 4, /*!< Input PGA source input2 */
    kWM8962_InputPGASourceInput3 = 2, /*!< Input PGA source input3 */
    kWM8962_InputPGASourceInput4 = 1, /*!< Input PGA source input4 */
} wm8962_input_pga_source_t;

/*! @brief wm8962 input source */
typedef enum _wm8962_output_pga_source
{
    kWM8962_OutputPGASourceMixer = 0, /*!< Output PGA source mixer */
    kWM8962_OutputPGASourceDAC   = 1, /*!< Output PGA source DAC */
} wm8962_output_pga_source_t;

/*! @brief audio sample rate definition
 * @anchor _wm8962_sample_rate
 */
enum
{
    kWM8962_AudioSampleRate8KHz    = 8000U,  /*!< Sample rate 8000 Hz */
    kWM8962_AudioSampleRate11025Hz = 11025U, /*!< Sample rate 11025 Hz */
    kWM8962_AudioSampleRate12KHz   = 12000U, /*!< Sample rate 12000 Hz */
    kWM8962_AudioSampleRate16KHz   = 16000U, /*!< Sample rate 16000 Hz */
    kWM8962_AudioSampleRate22050Hz = 22050U, /*!< Sample rate 22050 Hz */
    kWM8962_AudioSampleRate24KHz   = 24000U, /*!< Sample rate 24000 Hz */
    kWM8962_AudioSampleRate32KHz   = 32000U, /*!< Sample rate 32000 Hz */
    kWM8962_AudioSampleRate44100Hz = 44100U, /*!< Sample rate 44100 Hz */
    kWM8962_AudioSampleRate48KHz   = 48000U, /*!< Sample rate 48000 Hz */
    kWM8962_AudioSampleRate88200Hz = 88200U, /*!< Sample rate 88200 Hz */
    kWM8962_AudioSampleRate96KHz   = 96000U, /*!< Sample rate 96000 Hz */
};

/*! @brief audio bit width
 * @anchor _wm8962_audio_bit_width
 */
enum
{
    kWM8962_AudioBitWidth16bit = 16U, /*!< audio bit width 16 */
    kWM8962_AudioBitWidth20bit = 20U, /*!< audio bit width 20 */
    kWM8962_AudioBitWidth24bit = 24U, /*!< audio bit width 24 */
    kWM8962_AudioBitWidth32bit = 32U, /*!< audio bit width 32 */
};

/*! @brief wm8962 fll clock source */
typedef enum _wm8962_fllclk_source
{
    kWM8962_FLLClkSourceMCLK = 0U, /*!< FLL clock source from MCLK */
    kWM8962_FLLClkSourceBCLK = 1U, /*!< FLL clock source from BCLK */
} wm8962_fllclk_source_t;

/*! @brief wm8962 sysclk source */
typedef enum _wm8962_sysclk_source
{
    kWM8962_SysClkSourceMclk = 0U, /*!< sysclk source from external MCLK */
    kWM8962_SysClkSourceFLL  = 1U, /*!< sysclk source from internal FLL */
} wm8962_sysclk_source_t;

/*! @brief wm8962 audio format */
typedef struct _wm8962_audio_format
{
    uint32_t mclk_HZ;    /*!< master clock frequency */
    uint32_t sampleRate; /*!< sample rate */
    uint32_t bitWidth;   /*!< bit width */
} wm8962_audio_format_t;

/*! @brief wm8962 master system clock configuration */
typedef struct _wm8962_fll_clk_config
{
    wm8962_fllclk_source_t fllClockSource; /*!< fll clock source */
    uint32_t fllReferenceClockFreq;        /*!< external input frequency */
    uint32_t fllOutputFreq;                /*!< FLL output frequency value */
} wm8962_fll_clk_config_t;

/*!
 * @brief WM8962 data route configurations
 */
typedef struct _wm8962_route_config
{
    bool enableLoopBack; /*!< enable loopback: ADC->DAC directly*/

    /* adc input come from input mixer, input mixer source from: input PGA OR external input */
    wm8962_input_pga_source_t leftInputPGASource; /*!< Left input source for WM8962 */
    uint32_t leftInputMixerSource; /*!< left input MIXER source, combination value of wm8962_input_mixer_source_t */

    wm8962_input_pga_source_t rightInputPGASource; /*!< right input PGA source */
    uint32_t rightInputMixerSource; /*!< right input MIXER source, combination value of wm8962_input_mixer_source_t */

    /* headphone/speaker source from output PGA, output PGA source from mixer OR DAC */
    uint32_t
        leftSpeakerMixerSource; /*!< speaker left MIXER source, combination value of wm8962_output_mixer_source_t */
    wm8962_output_pga_source_t leftSpeakerPGASource; /*!< speaker left PGA source */

    uint32_t
        rightSpeakerMixerSource; /*!< speaker right MIXER source, combination value of wm8962_output_mixer_source_t */
    wm8962_output_pga_source_t rightSpeakerPGASource; /*!< speaker left PGA source */

    uint32_t
        leftHeadphoneMixerSource; /*!< headphone left MIXER source, combination value of wm8962_output_mixer_source_t */
    wm8962_output_pga_source_t leftHeadphonePGASource;  /*!< speaker left PGA source */

    uint32_t rightHeadphoneMixerSource;                 /*!< headphone left MIXER source, combination value of
                                                           wm8962_output_mixer_source_t */
    wm8962_output_pga_source_t rightHeadphonePGASource; /*!< speaker left PGA source */
} wm8962_route_config_t;

/*! @brief Initialize structure of WM8962 */
typedef struct wm8962_config
{
    wm8962_route_config_t route;         /*!< Audio data route.*/

    wm8962_protocol_t bus;               /*!< Audio transfer protocol */
    wm8962_audio_format_t format;        /*!< Audio format */

    bool masterSlave;                    /*!< Master or slave. true: master mode, false: slave mode */
    wm8962_sysclk_source_t sysclkSource; /*!< sysclk source */
    wm8962_fll_clk_config_t fllClock;    /*!< FLL clock configurations, shall be configured when masterSlave is true */

    uint8_t slaveAddress;                /*!< wm8962 device address */
    codec_i2c_config_t i2cConfig;        /*!< i2c configuration */
} wm8962_config_t;

/*! @brief wm8962 codec handler
 */
typedef struct _wm8962_handle
{
    const wm8962_config_t *config;              /*!< wm8904 config pointer */
    uint16_t volume[DEBUG_WM8962_MODULE_NUM];   /*!< Audio volume value */
    uint8_t i2cHandle[WM8962_I2C_HANDLER_SIZE]; /*!< i2c handle */
} wm8962_handle_t;
/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief WM8962 initialize function.
 *
 * The second parameter is NULL to WM8962 in this version. If users want
 * to change the settings, they have to use wm8962_write_reg() or wm8962_modify_reg()
 * to set the register value of WM8962.
 * Note: If the codec_config is NULL, it would initialize WM8962 using default settings.
 * The default setting:
 * codec_config->route = kWM8962_RoutePlaybackandRecord
 * codec_config->bus = kWM8962_BusI2S
 * codec_config->master = slave
 *
 * @param handle WM8962 handle structure.
 * @param config WM8962 configuration structure.
 */
status_t WM8962_Init(wm8962_handle_t *handle, const wm8962_config_t *config);

/*!
 * @brief Deinit the WM8962 codec.
 *
 * This function close all modules in WM8962 to save power.
 *
 * @param handle WM8962 handle structure pointer.
 */
status_t WM8962_Deinit(wm8962_handle_t *handle);

/*!
 * @brief Set audio data route in WM8962.
 *
 * This function would set the data route according to route. The route cannot be combined,
 * as all route would enable different modules.
 * Note: If a new route is set, the previous route would not work.
 *
 * @param handle WM8962 handle structure.
 * @param route Audio data route in WM8962.
 */
status_t WM8962_SetDataRoute(wm8962_handle_t *handle, const wm8962_route_config_t *route);

/*!
 * @brief Set the audio transfer protocol.
 *
 * WM8960 only supports I2S, left justified, right justified, PCM A, PCM B format.
 *
 * @param handle WM8960 handle structure.
 * @param protocol Audio data transfer protocol.
 */
status_t WM8962_SetProtocol(wm8962_handle_t *handle, wm8962_protocol_t protocol);

/*!
 * @brief Set the volume of different modules in WM8962.
 *
 * This function would set the volume of WM8962 modules. Uses need to appoint the module.
 * The function assume that left channel and right channel has the same volume.
 *
 * Module:kWM8962_ModuleADC, volume range value: 0 is mute, 1-255 is -97db to 30db
 * Module:kWM8962_ModuleDAC, volume range value: 0 is mute, 1-255 is -127db to 0db
 * Module:kWM8962_ModuleHP, volume range value: 0 - 2F is mute, 0x30 - 0x7F is -73db to 6db
 * Module:kWM8962_ModuleLineIn, volume range value: 0 - 0x3F is -17.25db to 30db
 * Module:kWM8962_ModuleSpeaker, volume range value: 0 - 2F is mute, 0x30 - 0x7F is -73db to 6db
 *
 *
 * @param handle WM8962 handle structure.
 * @param module Module to set volume, it can be ADC, DAC, Headphone and so on.
 * @param volume Volume value need to be set.
 */
status_t WM8962_SetModuleVolume(wm8962_handle_t *handle, wm8962_module_t module, uint32_t volume);

/*!
 * @brief Get the volume of different modules in WM8962.
 *
 * This function gets the volume of WM8962 modules. Uses need to appoint the module.
 * The function assume that left channel and right channel has the same volume.
 *
 * @param handle WM8962 handle structure.
 * @param module Module to set volume, it can be ADC, DAC, Headphone and so on.
 * @return Volume value of the module.
 */
uint32_t WM8962_GetModuleVolume(wm8962_handle_t *handle, wm8962_module_t module);

/*!
 * @brief Mute modules in WM8962.
 *
 * @param handle WM8962 handle structure.
 * @param module Modules need to be mute.
 * @param isEnabled Mute or unmute, 1 represent mute.
 */
status_t WM8962_SetModuleMute(wm8962_handle_t *handle, wm8962_module_t module, bool isEnabled);

/*!
 * @brief Enable/disable expected devices.
 *
 * @param handle WM8962 handle structure.
 * @param module Module expected to enable.
 * @param isEnabled Enable or disable moudles.
 */
status_t WM8962_SetModulePower(wm8962_handle_t *handle, wm8962_module_t module, bool isEnabled);

/*!
 * @brief Configure the data format of audio data.
 *
 * This function would configure the registers about the sample rate, bit depths.
 *
 * @param handle WM8962 handle structure pointer.
 * @param sysclk system clock of the codec which can be generated by MCLK or PLL output.
 * @param sample_rate Sample rate of audio file running in WM8962. WM8962 now
 * supports 8k, 11.025k, 12k, 16k, 22.05k, 24k, 32k, 44.1k, 48k and 96k sample rate.
 * @param bits Bit depth of audio file (WM8962 only supports 16bit, 20bit, 24bit
 * and 32 bit in HW).
 */
status_t WM8962_ConfigDataFormat(wm8962_handle_t *handle, uint32_t sysclk, uint32_t sample_rate, uint32_t bits);

/*!
 * @brief Write register to WM8962 using I2C.
 *
 * @param handle WM8962 handle structure.
 * @param reg The register address in WM8962.
 * @param val Value needs to write into the register.
 */
status_t WM8962_WriteReg(wm8962_handle_t *handle, uint16_t reg, uint16_t val);

/*!
 * @brief Read register from WM8962 using I2C.
 *
 * @param handle WM8962 handle structure.
 * @param reg The register address in WM8962.
 * @param val Value written to.
 */
status_t WM8962_ReadReg(wm8962_handle_t *handle, uint16_t reg, uint16_t *val);

/*!
 * @brief Modify some bits in the register using I2C.
 * @param handle WM8962 handle structure.
 * @param reg The register address in WM8962.
 * @param mask The mask code for the bits want to write. The bit you want to write should be 0.
 * @param val Value needs to write into the register.
 */
status_t WM8962_ModifyReg(wm8962_handle_t *handle, uint16_t reg, uint16_t mask, uint16_t val);

#if DEBUG_WM8962_REGISTER
/*!
 * @brief Dump all the wm8962 register.

 * @param handle WM8962 handle structure.
 * @param endAddress The end register address in WM8962.
 */
void WM8962_ReadAllReg(wm8962_handle_t *handle, uint32_t endAddress);
#endif
#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_WM8962_H_ */

/*******************************************************************************
 * API
 ******************************************************************************/
