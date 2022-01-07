/*
 * Copyright 2021-2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_PCM512X_H_
#define _FSL_PCM512X_H_

#include "fsl_codec_i2c.h"
#include "fsl_common.h"

/*!
 * @addtogroup pcm512x
 * @ingroup codec
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @name Driver version */
/*@{*/
/*! @brief CLOCK driver version 2.2.0 */
#define FSL_PCM512X_DRIVER_VERSION (MAKE_VERSION(0, 1, 0))
/*@}*/

/*! @brief PCM512x handle size */
#ifndef PCM512X_I2C_HANDLER_SIZE
#define PCM512X_I2C_HANDLER_SIZE CODEC_I2C_MASTER_HANDLER_SIZE
#endif

/*! @brief Define the register addresses of PCM512x. */
#define PCM512x_RESET             (  1)
#define PCM512x_POWER             (  2)
#define PCM512x_MUTE              (  3)
#define PCM512x_PLL_EN            (  4)
#define PCM512x_GPIO_EN           (  8)
#define PCM512x_BCLK_LRCLK_CFG    (  9)
#define PCM512x_MASTER_MODE       ( 12)
#define PCM512x_DAC_REF           ( 14)
#define PCM512x_SYNCHRONIZE       ( 19)
#define PCM512x_DSP_CLKDIV        ( 27)
#define PCM512x_DAC_CLKDIV        ( 28)
#define PCM512x_NCP_CLKDIV        ( 29)
#define PCM512x_OSR_CLKDIV        ( 30)
#define PCM512x_MASTER_CLKDIV_1   ( 32)
#define PCM512x_MASTER_CLKDIV_2   ( 33)
#define PCM512x_FS_SPEED_MODE     ( 34)
#define PCM512x_IDAC_1            ( 35)
#define PCM512x_IDAC_2            ( 36)
#define PCM512x_ERROR_DETECT      ( 37)
#define PCM512x_I2S_1             ( 40)
#define PCM512x_GPIO_OUTPUT_3     ( 82)
#define PCM512x_GPIO_OUTPUT_4     ( 83)
#define PCM512x_GPIO_OUTPUT_6     ( 85)
#define PCM512x_GPIO_CONTROL_1    ( 86)
#define PCM512x_ANALOG_MUTE_DET   (108)

/*! @brief Page 0, Register 1 - reset */
#define PCM512x_RSTR (1 << 0)
#define PCM512x_RSTM (1 << 4)

/*! @brief Page 0, Register 2 - power */
#define PCM512x_RQPD       (1 << 0)
#define PCM512x_RQST       (1 << 4)

/*! @brief Page 0, Register 3 - mute */
#define PCM512x_RQMR (1 << 0)
#define PCM512x_RQML (1 << 4)

/*! @brief Page 0, Register 4 - PLL */
#define PCM512x_PLLE       (1 << 0)
#define PCM512x_PLCK       (1 << 4)

/*! @brief Page 0, Register 9 - BCK, LRCLK configuration */
#define PCM512x_BCKO       (1 << 4)
#define PCM512x_LRKO       (1 << 0)
#define PCM512x_BCKP       (1 << 5)

/*! @brief Page 0, Register 12 - Master mode BCK, LRCLK reset */
#define PCM512x_RLRK       (1 << 0)
#define PCM512x_RBCK       (1 << 1)

/*! @brief Page 0, Register 14 - DAC reference */
#define PCM512x_SDAC        (7 << 4)
#define PCM512x_SDAC_SCK    (3 << 4)

/*! @brief Page 0, Register 19 - synchronize */
#define PCM512x_RQSY        (1 << 0)
#define PCM512x_RQSY_RESUME (0 << 0)
#define PCM512x_RQSY_HALT   (1 << 0)

/*! @brief Page 0, Register 34 - fs speed mode */
#define PCM512x_FSSP        (3 << 0)
#define PCM512x_FSSP_48KHZ  (0 << 0)
#define PCM512x_FSSP_96KHZ  (1 << 0)
#define PCM512x_FSSP_192KHZ (2 << 0)
#define PCM512x_FSSP_384KHZ (3 << 0)

/*! @brief Page 0, Register 37 - Error detection */
#define PCM512x_IPLK (1 << 0)
#define PCM512x_DCAS (1 << 1)
#define PCM512x_IDCM (1 << 2)
#define PCM512x_IDCH (1 << 3)
#define PCM512x_IDSK (1 << 4)
#define PCM512x_IDBK (1 << 5)
#define PCM512x_IDFS (1 << 6)

/*! @brief Page 0, Register 40 - I2S configuration */
#define PCM512x_ALEN       (3 << 0)
#define PCM512x_ALEN_16    (0 << 0)
#define PCM512x_ALEN_20    (1 << 0)
#define PCM512x_ALEN_24    (2 << 0)
#define PCM512x_ALEN_32    (3 << 0)
#define PCM512x_AFMT       (3 << 4)

/*! @brief PCM512x I2C baudrate */
#define PCM512X_I2C_BAUDRATE (100000U)

/*! @brief audio sample rate definition
 * @anchor _pcm512x_sample_rate
 */
enum
{
    kPCM512x_AudioSampleRate8KHz     = 8000U,    /*!< Sample rate 8000 Hz */
    kPCM512x_AudioSampleRate11025Hz  = 11025U,   /*!< Sample rate 11025 Hz */
    kPCM512x_AudioSampleRate12KHz    = 12000U,   /*!< Sample rate 12000 Hz */
    kPCM512x_AudioSampleRate16KHz    = 16000U,   /*!< Sample rate 16000 Hz */
    kPCM512x_AudioSampleRate22050Hz  = 22050U,   /*!< Sample rate 22050 Hz */
    kPCM512x_AudioSampleRate24KHz    = 24000U,   /*!< Sample rate 24000 Hz */
    kPCM512x_AudioSampleRate32KHz    = 32000U,   /*!< Sample rate 32000 Hz */
    kPCM512x_AudioSampleRate44100Hz  = 44100U,   /*!< Sample rate 44100 Hz */
    kPCM512x_AudioSampleRate48KHz    = 48000U,   /*!< Sample rate 48000 Hz */
    kPCM512x_AudioSampleRate88200Hz  = 88200U,   /*!< Sample rate 88200 Hz */
    kPCM512x_AudioSampleRate96KHz    = 96000U,   /*!< Sample rate 96000 Hz */
    kPCM512x_AudioSampleRate176400Hz = 176400U,  /*!< Sample rate 176400 Hz */
    kPCM512x_AudioSampleRate192KHz   = 192000U,  /*!< Sample rate 192000 Hz */
    kPCM512x_AudioSampleRate384KHz   = 384000U,  /*!< Sample rate 384000 Hz */
};

/*! @brief audio bit width
 * @anchor _pcm512x_audio_bit_width
 */
enum
{
    kPCM512x_AudioBitWidth16bit = 16U, /*!< audio bit width 16 */
    kPCM512x_AudioBitWidth20bit = 20U, /*!< audio bit width 20 */
    kPCM512x_AudioBitWidth24bit = 24U, /*!< audio bit width 24 */
    kPCM512x_AudioBitWidth32bit = 32U, /*!< audio bit width 32 */
};

/*! @brief PCM512x sysclk source */
typedef enum _pcm512x_sysclk_source
{
    kPCM512x_SysClkSourceMclk        = 0U, /*!< sysclk source from external MCLK */
    kPCM512x_SysClkSourceInternalPLL = 1U, /*!< sysclk source from internal PLL */
} pcm512x_sysclk_source_t;

/*! @brief PCM512x audio format */
typedef struct _pcm512x_audio_format
{
    uint32_t mclk_HZ;    /*!< master clock frequency */
    uint32_t sampleRate; /*!< sample rate */
    uint32_t bitWidth;   /*!< bit width */
} pcm512x_audio_format_t;

/*! @brief Initialize structure of PCM512x */
typedef struct pcm512x_config
{
    pcm512x_audio_format_t format;              /*!< Audio format */
    bool master_slave;                          /*!< Master or slave. */
    uint8_t slaveAddress;                       /*!< PCM512x device address */
    codec_i2c_config_t i2cConfig;               /*!< i2c configuration */
    uint8_t gpio_led;                           /*!< led gpio number */
    uint8_t gpio_osc44;                         /*!< oscillator 44.1 gpio number */
    uint8_t gpio_osc48;                         /*!< oscillator 48 gpio number */
} pcm512x_config_t;

/*! @brief PCM512x codec handler
 */
typedef struct _pcm512x_handle
{
    const pcm512x_config_t *config;              /*!< PCM512x config pointer */
    uint8_t i2cHandle[PCM512X_I2C_HANDLER_SIZE]; /*!< i2c handle */
} pcm512x_handle_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief PCM512x initialise function.
 *
 * @param handle PCM512x handle structure.
 * @param config PCM512x configuration structure.
 */
status_t PCM512x_Init(pcm512x_handle_t *handle, const pcm512x_config_t *config);

/*!
 * @brief Deinit the PCM512x codec.
 *
 * This function close all modules in PCM512x to save power.
 *
 * @param handle PCM512x handle structure pointer.
 */
status_t PCM512x_Deinit(pcm512x_handle_t *handle);

/*!
 * @brief Mute PCM512x.
 *
 * @param handle PCM512x handle structure.
 * @param isEnabled Mute or unmute, 1 represent mute.
 */
status_t PCM512x_SetMute(pcm512x_handle_t *handle, bool isEnabled);

/*!
 * @brief Configure the data format of audio data.
 *
 * This function would configure the registers about the sample rate, bit depths.
 *
 * @param handle PCM512x handle structure pointer.
 * @param sysclk system clock of the codec which can be generated by MCLK or PLL output.
 * @param sample_rate Sample rate of audio file running in PCM512x.
 * @param bits Bit depth of audio file.
 */
status_t PCM512x_SetFormat(pcm512x_handle_t *handle, uint32_t sysclk, uint32_t sample_rate, uint32_t bits);

/*!
 * @brief Write register to PCM512x using I2C.
 *
 * @param handle PCM512x handle structure.
 * @param reg The register address in PCM512x.
 * @param val Value needs to write into the register.
 */
status_t PCM512x_WriteReg(pcm512x_handle_t *handle, uint8_t reg, uint8_t val);

/*!
 * @brief Read register from PCM512x using I2C.
 * @param handle PCM512x handle structure.
 * @param reg The register address in PCM512x.
 * @param val Value written to.
 */
status_t PCM512x_ReadReg(pcm512x_handle_t *handle, uint8_t reg, uint8_t *val);

/*!
 * @brief Modify some bits in the register using I2C.
 * @param handle PCM512x handle structure.
 * @param reg The register address in PCM512x.
 * @param mask The mask code for the bits want to write. The bit you want to write should be 0.
 * @param val Value needs to write into the register.
 */
status_t PCM512x_ModifyReg(pcm512x_handle_t *handle, uint8_t reg, uint8_t mask, uint8_t val);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_PCM512X_H_ */

/*******************************************************************************
 * API
 ******************************************************************************/
