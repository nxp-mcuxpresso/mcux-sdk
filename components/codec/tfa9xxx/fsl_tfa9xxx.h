/*
 * Copyright  2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * fsl_tfa9xxx.h
 *
 */

#ifndef FSL_TFA9XXX_H_
#define FSL_TFA9XXX_H_

#include "tfa2_container.h"
#include "tfa2_dev.h"
#include "fsl_common.h"
#include "fsl_codec_i2c.h"

/*!
 * @addtogroup tfa9xxx
 * @{
 */
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @name Driver version */
/*@{*/
/*! @brief TFA9XXX driver version 8.1.2. */
#define FSL_TFA9XXX_DRIVER_VERSION (MAKE_VERSION(8, 1, 2))
/*@}*/

/*! @brief tfa9xxx handle size */
#ifndef TFA9XXX_I2C_HANDLER_SIZE
#define TFA9XXX_I2C_HANDLER_SIZE (CODEC_I2C_MASTER_HANDLER_SIZE)
#endif

/*! @brief TFA9XXX_ I2C baudrate */
#define TFA9XXX_I2C_BAUDRATE        (400000U)
#define TFA9XXX_DEV_NUM             2 /* The total number of TFA device */
#define TFA9XXX_I2C_ADDR_0          0x34
#define TFA9XXX_I2C_ADDR_1          0x35
#define TFA9XXX_I2C_ADDR_2          0x36
#define TFA9XXX_I2C_ADDR_3          0x37
#define BOARD_I2C_TRANSFER_SIZE_MAX 255U

/*!
 * @brief The audio data transfer protocol choice.
 * TFA9XXX only supports I2S format.
 */
typedef enum _tfa9xxx_protocol
{
    kTFA9XXX_BusI2S = 0, /*!< I2S type */
} tfa9xxx_protocol_t;

/*! @brief audio sample rate definition, more sample rates can be supported in the future */
enum _tfa9xxx_sample_rate
{
    kTFA9XXX_AudioSampleRate48KHz = 48000U, /*!< Sample rate 48000 Hz */
};

/*! @brief audio bit width, more bit width can be supported in the future */
enum _tfa9xxx_audio_bit_width
{
    kTFA9XXX_AudioBitWidth16bit = 16U, /*!< audio bit width 16 */
};

/*! @brief play channel */
enum _tfa98xxx_play_channel
{
    kTFA9XXX_PlayChannelLeft0  = 1U, /*!< codec play channel left 0 */
    kTFA9XXX_PlayChannelRight0 = 2U, /*!< codec play channel right 0 */
};

/*! @brief tfa9xxx audio format */
typedef struct _tfa9xxx_audio_format
{
    enum _tfa9xxx_sample_rate sampleRate;   /*!< sample rate */
    enum _tfa9xxx_audio_bit_width bitWidth; /*!< bit width */
} tfa9xxx_audio_format_t;

/*! @brief tfa9xxx device */
typedef struct tfa2_device tfa9xxx_device_t;

/*! @brief Initialize structure of TFA9XXX */
typedef struct tfa9xxx_config
{
    tfa9xxx_protocol_t protocol;   /*!< Audio transfer protocol */
    tfa9xxx_audio_format_t format; /*!< Audio format */
    uint8_t slaveAddress;          /*!< tfa9xxx device address */
    codec_i2c_config_t i2cConfig;  /*!< i2c configuration */
    uint8_t *tfaContainer;         /*!< tfa container array */
    uint8_t deviceIndex;           /*!< tfa device index, starting from 0, up to TFA9XXX_DEV_NUM - 1 */
} tfa9xxx_config_t;

/*! @brief tfa9xxx codec handler
 * Application should allocate a buffer with TFA9XXX_HANDLE_SIZE for handle definition, such as
 * uint8_t tfa9xxxHandleBuffer[TFA9XXX_HANDLE_SIZE];
 * tfa9xxx_handle_t *tfa9xxxHandle = tfa9xxxHandleBuffer;
 */
typedef struct _tfa9xxx_handle
{
    tfa9xxx_config_t *config;                    /*!< tfa9xxx config pointer */
    uint8_t i2cHandle[TFA9XXX_I2C_HANDLER_SIZE]; /*!< i2c handle */
} tfa9xxx_handle_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initialize the TFA, put the TFA to operating state, allocate memory side.
 *
 * @param handle TFA9XXX handle structure.
 * @param tfa9xxxConfig TFA9XXX configuration structure.
 * @return status_t Returns kStatus_Success if success, otherwise returns error code.
 */
status_t TFA9XXX_Init(tfa9xxx_handle_t *handle, tfa9xxx_config_t *tfa9xxxConfig);

/*!
 * @brief Deinitialize the TFA, put the TFA to powerdown state.
 *
 * @param handle TFA9XXX handle structure.
 * @return status_t Returns kStatus_Success if success, otherwise returns error code.
 */
status_t TFA9XXX_Deinit(tfa9xxx_handle_t *handle);

/*!
 * @brief Mute/Unmute the TFA
 *
 * This function has dependency on internal structure, it has to be called after TFA9XXX_CreatePlatform();
 *
 * @param handle TFA9XXX handle structure.
 * @param isMute true is mute, false is unmute..
 * @return status_t Returns kStatus_Success if success, otherwise returns error code.
 */
status_t TFA9XXX_SetMute(tfa9xxx_handle_t *handle, bool isMute);

/*!
 * @brief Configure the TFA based on I2S format.
 * Assuming TFA_Init() is already called by calling CODEC_Init(), the TFA will be in operating state. So before calling
 * TFA_SetFormat(), the TFA needs to be in powerdown state by calling TFA_Stop().
 *
 * @param handle TFA9XXX handle structure.
 * @param mclk The mclk.
 * @param sampleRate The sample rate.
 * @param bitWidth The bit width.
 * @return Returns @ref kStatus_Success if success, otherwise returns error code.
 */
status_t TFA9XXX_ConfigDataFormat(tfa9xxx_handle_t *handle, uint32_t mclk, uint32_t sampleRate, uint32_t bitWidth);

/*!
 * @brief Set the volume level.
 *
 * This function has dependency on internal structure, it has to be called after TFA9XXX_CreatePlatform();
 *
 * @param handle TFA9XXX handle structure.
 * @param volume volume volume value, support 0 ~ 100, 0 is mute, 100 is the maximum volume value.
 * @return status_t Returns kStatus_Success if success, otherwise returns error code.
 */
status_t TFA9XXX_SetVolume(tfa9xxx_handle_t *handle, uint32_t volume);

/*!
 * @brief Set the audio channel for a speaker.
 * By default, I2S channel is configured by the `.tfaContainer` in `tfa9xxx_config_t`. So you don't need to call this
 * function. However, if required, calling this function allows overwriting I2S channel selection. This can be useful
 * when the tuning is done, and you simply want to change the I2S channel.
 *
 * This function has dependency on internal structure, it has to be called after TFA9XXX_CreatePlatform();
 *
 * @param handle TFA9XXX handle structure.
 * @param playChannel _codec_play_channel play channel, available values are kCODEC_PlayChannelSpeakerLeft,
 * kCODEC_PlayChannelSpeakerRight, kCODEC_PlayChannelSpeakerLeft | kCODEC_PlayChannelSpeakerRight.
 * @return status_t Returns kStatus_Success if success, otherwise returns error code.
 */
status_t TFA9XXX_SetPlayChannel(tfa9xxx_handle_t *handle, uint32_t playChannel);

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
status_t TFA9XXX_Start(tfa9xxx_handle_t *handle);

/*!
 * @brief Stop the TFA
 *
 * Stop will put the TFA in powerdown/standby mode, the next time TFA start will be a warm start.
 *
 * This function has dependency on internal structure, it has to be called after TFA9XXX_CreatePlatform();
 *
 * @param handle The TFA9XXX handle structure.
 * @return status_t Returns kStatus_Success if success, otherwise returns error code.
 */
status_t TFA9XXX_Stop(tfa9xxx_handle_t *handle);

/*!
 * @brief Reset the TFA
 *
 * Reset will put the in powerdown/standby mode, the next time TFA start will be a cold start.
 *
 * This function has dependency on internal structure, it has to be called after TFA9XXX_CreatePlatform();
 *
 * @param handle The TFA9XXX handle structure.
 * @return status_t Returns kStatus_Success if success, otherwise returns error code.
 */
status_t TFA9XXX_Reset(tfa9xxx_handle_t *handle);

/*!
 * @brief check if TFA is calibrated.
 *
 * This function has dependency on internal structure, it has to be called after TFA9XXX_CreatePlatform();
 *
 * @param handle The TFA9XXX handle structure.
 * @param isTFACalibrated This value stores if TFA is calibrated.
 * @return status_t Returns kStatus_Success if operation is successfully, otherwise returns error code..
 */
status_t TFA9XXX_CheckCalibrationStatus(tfa9xxx_handle_t *handle, bool *isTFACalibrated);

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
status_t TFA9XXX_CalibrateSpeakerBoost(tfa9xxx_handle_t *handle);

/*!
 * @brief Hardcode calibration value for DSP usage instead of triggering calibration.
 *
 * This function has dependency on internal structure, it has to be called after TFA9XXX_CreatePlatform();
 *
 * @param handle TFA9XXX handle structure.
 * @return status_t Returns kStatus_Success if success, otherwise returns error code.
 */
status_t TFA9XXX_HardcodeCalibrationValue(tfa9xxx_handle_t *handle);

/*!
 * @brief Get the status of a running TFA.
 *
 * This function has dependency on internal structure, it has to be called after TFA9XXX_CreatePlatform();
 *
 * @param handle The TFA9XXX handle structure.
 * @return status_t Returns kStatus_Success if success, otherwise returns error code.
 */
status_t TFA9XXX_GetStatus(tfa9xxx_handle_t *handle);

/*!
 * @brief Convert the return check value from TFA driver to predefined error code.
 *
 * @param rc Return check value from TFA driver.
 * @return status_t Returns kStatus_Success if success, otherwise returns error code.
 */
status_t TFA9XXX_ConvertErrorCode(int32_t rc);

#if defined(__cplusplus)
}
#endif

/*! @} */
#endif /* FSL_TFA9XXX_H_ */
