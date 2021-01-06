/*
 * Copyright 2018-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_AK4497_H_
#define _FSL_AK4497_H_

#include "fsl_common.h"
#include "fsl_codec_i2c.h"
/*!
 * @addtogroup ak4497
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @name Driver version */
/*@{*/
/*! @brief CLOCK driver version 2.1.2 */
#define FSL_AK4497_DRIVER_VERSION (MAKE_VERSION(2, 1, 2))
/*@}*/

/*! @brief ak4497 handle size */
#ifndef AK4497_I2C_HANDLER_SIZE
#define AK4497_I2C_HANDLER_SIZE CODEC_I2C_MASTER_HANDLER_SIZE
#endif

/*! @brief define the registers offset of AK4497. */
#define AK4497_CONTROL1     (0x00U)
#define AK4497_CONTROL2     (0x01U)
#define AK4497_CONTROL3     (0x02U)
#define AK4497_LCHATT       (0x03U)
#define AK4497_RCHATT       (0x04U)
#define AK4497_CONTROL4     (0x05U)
#define AK4497_DSD1         (0x06U)
#define AK4497_CONTROL5     (0x07U)
#define AK4497_SOUNDCONTROL (0x08U)
#define AK4497_DSD2         (0x09U)
#define AK4497_CONTROL7     (0x0AU)
#define AK4497_CONTROL8     (0x0BU)
#define AK4497_DFSREAD      (0x15U)
/*! @brief define BIT info of AK4497. */
#define AK4497_CONTROL1_RSTN_MASK  (0x1U)
#define AK4497_CONTROL1_RSTN_SHIFT (0U)
#define AK4497_CONTROL1_DIF0_MASK  (0x2U)
#define AK4497_CONTROL1_DIF0_SHIFT (1U)
#define AK4497_CONTROL1_DIF1_MASK  (0x4U)
#define AK4497_CONTROL1_DIF1_SHIFT (2U)
#define AK4497_CONTROL1_DIF2_MASK  (0x8U)
#define AK4497_CONTROL1_DIF2_SHIFT (3U)
#define AK4497_CONTROL1_AFSD_MASK  (0x10U)
#define AK4497_CONTROL1_AFSD_SHIFT (4U)
#define AK4497_CONTROL1_ECS_MASK   (0x20U)
#define AK4497_CONTROL1_ECS_SHIFT  (5U)
#define AK4497_CONTROL1_EXDF_MASK  (0x40U)
#define AK4497_CONTROL1_EXDF_SHIFT (6U)
#define AK4497_CONTROL1_ACKS_MASK  (0x80U)
#define AK4497_CONTROL1_ACKS_SHIFT (7U)

#define AK4497_CONTROL2_SMUTE_MASK  (0x1U)
#define AK4497_CONTROL2_SMUTE_SHIFT (0U)
#define AK4497_CONTROL2_DEM0_MASK   (0x2U)
#define AK4497_CONTROL2_DEM0_SHIFT  (1U)
#define AK4497_CONTROL2_DEM1_MASK   (0x4U)
#define AK4497_CONTROL2_DEM1_SHIFT  (2U)
#define AK4497_CONTROL2_DFS0_MASK   (0x8U)
#define AK4497_CONTROL2_DFS0_SHIFT  (3U)
#define AK4497_CONTROL2_DFS1_MASK   (0x10U)
#define AK4497_CONTROL2_DFS1_SHIFT  (4U)
#define AK4497_CONTROL2_SD_MASK     (0x20U)
#define AK4497_CONTROL2_SD_SHIFT    (5U)
#define AK4497_CONTROL2_DZFM_MASK   (0x40U)
#define AK4497_CONTROL2_DZFM_SHIFT  (6U)
#define AK4497_CONTROL2_DZFE_MASK   (0x80U)
#define AK4497_CONTROL2_DZFE_SHIFT  (7U)

#define AK4497_CONTROL3_SLOW_MASK   (0x1U)
#define AK4497_CONTROL3_SLOW_SHIFT  (0U)
#define AK4497_CONTROL3_SELLR_MASK  (0x2U)
#define AK4497_CONTROL3_SELLR_SHIFT (1U)
#define AK4497_CONTROL3_DZFB_MASK   (0x4U)
#define AK4497_CONTROL3_DZFB_SHIFT  (2U)
#define AK4497_CONTROL3_MONO_MASK   (0x8U)
#define AK4497_CONTROL3_MONO_SHIFT  (3U)
#define AK4497_CONTROL3_DCKB_MASK   (0x10U)
#define AK4497_CONTROL3_DCKB_SHIFT  (4U)
#define AK4497_CONTROL3_DCKS_MASK   (0x20U)
#define AK4497_CONTROL3_DCKS_SHIFT  (5U)
#define AK4497_CONTROL3_DP_MASK     (0x80U)
#define AK4497_CONTROL3_DP_SHIFT    (7U)

#define AK4497_CONTROL4_SSLOW_MASK  (0x1U)
#define AK4497_CONTROL4_SSLOW_SHIFT (0U)
#define AK4497_CONTROL4_DFS2_MASK   (0x2U)
#define AK4497_CONTROL4_DFS2_SHIFT  (1U)
#define AK4497_CONTROL4_INVR_MASK   (0x40U)
#define AK4497_CONTROL4_INVR_SHIFT  (6U)
#define AK4497_CONTROL4_INVL_MASK   (0x80U)
#define AK4497_CONTROL4_INVL_SHIFT  (7U)

#define AK4497_DSD1_DSDSEL0_MASK  (0x1U)
#define AK4497_DSD1_DSDSEL0_SHIFT (0U)
#define AK4497_DSD1_DSDD_MASK     (0x2U)
#define AK4497_DSD1_DSDD_SHIFT    (1U)
#define AK4497_DSD1_DMRE_MASK     (0x8U)
#define AK4497_DSD1_DMRE_SHIFT    (3U)
#define AK4497_DSD1_DMC_MASK      (0x10U)
#define AK4497_DSD1_DMC_SHIFT     (4U)
#define AK4497_DSD1_DMR_MASK      (0x20U)
#define AK4497_DSD1_DMR_SHIFT     (5U)
#define AK4497_DSD1_DML_MASK      (0x40U)
#define AK4497_DSD1_DML_SHIFT     (6U)
#define AK4497_DSD1_DDM_MASK      (0x80U)
#define AK4497_DSD1_DDM_SHIFT     (7U)

#define AK4497_CONTROL5_SYNCE_MASK  (0x1U)
#define AK4497_CONTROL5_SYNCE_SHIFT (0U)
#define AK4497_CONTROL5_GC0_MASK    (0x2U)
#define AK4497_CONTROL5_GC0_SHIFT   (1U)
#define AK4497_CONTROL5_GC1_MASK    (0x4U)
#define AK4497_CONTROL5_GC1_SHIFT   (2U)
#define AK4497_CONTROL5_GC2_MASK    (0x8U)
#define AK4497_CONTROL5_GC2_SHIFT   (3U)

#define AK4497_SOUNDCONTROL_SC0_MASK    (0x1U)
#define AK4497_SOUNDCONTROL_SC0_SHIFT   (0U)
#define AK4497_SOUNDCONTROL_SC1_MASK    (0x2U)
#define AK4497_SOUNDCONTROL_SC1_SHIFT   (1U)
#define AK4497_SOUNDCONTROL_SC2_MASK    (0x4U)
#define AK4497_SOUNDCONTROL_SC2_SHIFT   (2U)
#define AK4497_SOUNDCONTROL_HLOAD_MASK  (0x8U)
#define AK4497_SOUNDCONTROL_HLOAD_SHIFT (3U)

#define AK4497_DSD2_DSDSEL1_MASK  (0x1U)
#define AK4497_DSD2_DSDSEL1_SHIFT (0U)
#define AK4497_DSD2_DSDF_MASK     (0x2U)
#define AK4497_DSD2_DSDF_SHIFT    (1U)
#define AK4497_DSD2_DSDPATH_MASK  (0x4U)
#define AK4497_DSD2_DSDPATH_SHIFT (2U)

#define AK4497_CONTROL7_PW_MASK    (0x4U)
#define AK4497_CONTROL7_PW_SHIFT   (2U)
#define AK4497_CONTROL7_SDS2_MASK  (0x10U)
#define AK4497_CONTROL7_SDS2_SHIFT (4U)
#define AK4497_CONTROL7_SDS1_MASK  (0x20U)
#define AK4497_CONTROL7_SDS1_SHIFT (5U)
#define AK4497_CONTROL7_TDM0_MASK  (0x40U)
#define AK4497_CONTROL7_TDM0_SHIFT (6U)
#define AK4497_CONTROL7_TDM1_MASK  (0x80U)
#define AK4497_CONTROL7_TDM1_SHIFT (7U)

#define AK4497_CONTROL8_TSET_MASK    (0x1U)
#define AK4497_CONTROL8_TSET_SHIFT   (0U)
#define AK4497_CONTROL8_DCHAIN_MASK  (0x2U)
#define AK4497_CONTROL8_DCHAIN_SHIFT (1U)
#define AK4497_CONTROL8_SDS0_MASK    (0x10U)
#define AK4497_CONTROL8_SDS0_SHIFT   (4U)
#define AK4497_CONTROL8_ATS0_MASK    (0x40U)
#define AK4497_CONTROL8_ATS0_SHIFT   (6U)
#define AK4497_CONTROL8_ATS1_MASK    (0x80U)
#define AK4497_CONTROL8_ATS1_SHIFT   (7U)

/*! @brief AK4497 I2C address. */
#define AK4497_I2C_ADDR (0x11U)
/*! @brief AK4497 i2c baudrate */
#define AK4497_I2C_BITRATE (100000U)
/*! @brief The AK4497 playback mode */
typedef enum _ak4497_mode
{
    kAK4497_PcmMode  = 0x0,
    kAK4497_DsdMode  = 0x1,
    kAK4497_ExdfMode = 0x2,
} ak4497_mode_t;

/*! @brief The Data selection of L-channel and R-channel for DSD mode, defined by SELLR bit */
typedef enum _ak4497_data_channel_mode
{
    kAK4497_NormalMode   = 0x0, /*!< L-channel output L-channel data, R-channel output R-channel data. */
    kAK4497_ExchangeMode = 0x1, /*!< L-channel output R-channel data, R-channel output L-channel data. */
} ak4497_data_channel_mode_t;

/*! @brief The data path select for DSD mode */
typedef enum _ak4497_dsd_input_path
{
    kAK4497_Path0 = 0x0, /*!< Pin 16,17,19 used. */
    kAK4497_Path1 = 0x1, /*!< Pin 3,4,5 used. */
} ak4497_dsd_input_path_t;

/*! @brief The MCLK select for DSD mode, defined by DCKS bit */
typedef enum _ak4497_dsd_mclk
{
    kAK4497_mclk512fs = 0x0, /*!< MCLK equals 512fs. */
    kAK4497_mclk768fs = 0x1, /*!< MCLK equals 768fs. */
} ak4497_dsd_mclk_t;

/*! @brief The DCLK select for DSD mode, defined by DSDSEL[1:0] */
typedef enum _ak4497_dsd_dclk
{
    kAK4497_dclk64fs  = 0x0, /*!< DCLK equals 64fs. */
    kAK4497_dclk128fs = 0x1, /*!< DCLK equals 128fs. */
    kAK4497_dclk256fs = 0x2, /*!< DCLK equals 256fs. */
    kAK4497_dclk512fs = 0x3, /*!< DCLK equals 512fs. */
} ak4497_dsd_dclk_t;

/*! @brief DSD playback path */
typedef enum _ak4497_dsd_playback_path
{
    kAK4497_NormalPath   = 0x0, /*!< Normal path mode. */
    kAK4497_VolumeBypass = 0x1, /*!< Volume Bypass mode. */
} ak4497_dsd_playback_path_t;

/*! @brief DSD mute flag */
typedef enum _ak4497_dsd_data_mute
{
    kAK4497_DsdMuteDisable = 0x0,
    kAK4497_DsdMuteEnable  = 0x1,
} ak4497_dsd_data_mute_t;

/*! @brief DSD bclk polarity */
typedef enum _ak4497_dsd_dclk_polarity
{
    kAK4497_FallingEdge = 0x0, /*!< DSD data is output from DCLK falling edge. */
    kAK4497_RisingEdge  = 0x1, /*!< DSD data is output from DCLK rising edge. */
} ak4497_dsd_dclk_polarity_t;
/*! @brief The sampling frequency mode for PCM and EXDF mode, defined by CR01[AFSD], CR00[ACKS]*/
typedef enum _ak4497_pcm_samplefreqmode
{
    kAK4497_ManualSettingMode = 0x0, /*!< Manual setting mode */
    kAK4497_AutoSettingMode   = 0x1, /*!< Auto setting mode */
    kAK4497_FsAutoDetectMode  = 0x2, /*!< Auto detect mode */
} ak4497_pcm_samplefreqmode_t;
/*! @brief The sampling speed select, defined by DFS[2:0]*/
typedef enum _ak4497_pcm_samplefreqselect
{
    kAK4497_NormalSpeed = 0x0, /*!< 8kHZ ~ 54kHZ */
    kAK4497_DoubleSpeed = 0x1, /*!< 54kHZ ~ 108kHZ */
    kAK4497_QuadSpeed   = 0x2, /*!< 120kHZ ~ 216kHZ, note that value 3 also stands for Quad Speed Mode */
    kAK4497_OctSpeed    = 0x4, /*!< 384kHZ, note that value 6 also stands for Oct Speed Mode */
    kAK4497_HexSpeed    = 0x5, /*!< 768kHZ, note that value 7 also stands for Hex Speed Mode */
} ak4497_pcm_samplefreqselect_t;

/*! @brief The audio data interface modes, defined by DIF[2:0]*/
typedef enum _ak4497_pcm_sdata_format
{
    kAK4497_16BitLSB    = 0x0, /*!< 16-bit LSB justified */
    kAK4497_20BitLSB    = 0x1, /*!< 20-bit LSB justified */
    kAK4497_24BitMSB    = 0x2, /*!< 24-bit MSB justified */
    kAK4497_16_24BitI2S = 0x3, /*!< 16 and 24-bit I2S compatible */
    kAK4497_24BitLSB    = 0x4, /*!< 24-bit LSB justified */
    kAK4497_32BitLSB    = 0x5, /*!< 32-bit LSB justified */
    kAK4497_32BitMSB    = 0x6, /*!< 32-bit MSB justified */
    kAK4497_32BitI2S    = 0x7, /*!< 32-bit I2S compatible */
} ak4497_pcm_sdata_format_t;

/*! @brief The TDM mode select, defined by TDM[1:0]*/
typedef enum _ak4497_pcm_tdm_mode
{
    kAK4497_Normal = 0x0, /*!< Normal mode */
    kAK4497_TDM128 = 0x1, /*!< BCLK is fixed to 128fs */
    kAK4497_TDM256 = 0x2, /*!< BCLK is fixed to 256fs */
    kAK4497_TDM512 = 0x3, /*!< BCLK is fixed to 512fs */
} ak4497_pcm_tdm_mode_t;

/*! @brief The audio data slot selection, defined by SDS[2:0]*/
typedef enum _ak4497_pcm_sds_select
{
    kAK4497_L1R1 = 0x0,
    kAK4497_L2R2 = 0x1,
    kAK4497_L3R3 = 0x2,
    kAK4497_L4R4 = 0x3,
    kAK4497_L5R5 = 0x4,
    kAK4497_L6R6 = 0x5,
    kAK4497_L7R7 = 0x6,
    kAK4497_L8R8 = 0x7,
} ak4497_pcm_sds_select_t;

/*! @brief audio codec module control cmd */
typedef enum _ak4497_module_ctrl_cmd
{
    kAK4497_ModuleSwitchI2SInInterface = 0U, /*!< module digital interface siwtch. */
} ak4497_module_ctrl_cmd_t;

/*! @brief audio codec module digital interface
 * @anchor _ak4497_module_ctrl_i2s_in_interface
 */
enum
{
    kAK4497_ModuleI2SInInterfacePCM = 0U, /*!< Pcm interface*/
    kAK4497_ModuleI2SInInterfaceDSD = 1U, /*!< DSD interface */
};

/*! @brief Initialize DSD mode structure of AK4497 */
typedef struct _ak4497_dsd_config
{
    ak4497_dsd_input_path_t dsdPath;
    ak4497_dsd_mclk_t dsdMclk;
    ak4497_dsd_playback_path_t dsdPlaybackPath;
    ak4497_dsd_data_mute_t dsdDataMute;
    ak4497_dsd_dclk_polarity_t dsdDclkPolarity;
} ak4497_dsd_config_t;

/*! @brief Initialize PCM mode structure of AK4497 */
typedef struct _ak4497_pcm_config
{
    ak4497_pcm_samplefreqmode_t pcmSampleFreqMode;
    ak4497_pcm_sdata_format_t pcmSdataFormat;
    ak4497_pcm_tdm_mode_t pcmTdmMode;
    ak4497_pcm_sds_select_t pcmSdsSlot;
} ak4497_pcm_config_t;

/*! @brief Initialize structure of AK4497 */
typedef struct _ak4497_config
{
    ak4497_mode_t ak4497Mode;
    ak4497_data_channel_mode_t dataChannelMode;
    ak4497_pcm_config_t pcmConfig;
    ak4497_dsd_config_t dsdConfig;

    uint8_t slaveAddress;         /*!< code device slave address */
    codec_i2c_config_t i2cConfig; /*!< i2c bus configuration */
} ak4497_config_t;

/*! @brief ak4497 codec handler
 */
typedef struct _ak4497_handle
{
    ak4497_config_t *config;                    /*!< ak4497 config pointer */
    uint8_t i2cHandle[AK4497_I2C_HANDLER_SIZE]; /*!< i2c handle */
} ak4497_handle_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Default initializes AK4497.
 *
 * @param config AK4497 configure structure.
 */
void AK4497_DefaultConfig(ak4497_config_t *config);
/*!
 * @brief Initializes AK4497.
 *
 * @param handle AK4497 handle structure.
 * @param config AK4497 configure structure.
 */
status_t AK4497_Init(ak4497_handle_t *handle, ak4497_config_t *config);
/*!
 * @brief Set the codec PCM mode or DSD mode based on the format info
 *
 * This function would configure the codec playback mode.
 *
 * @param handle AK4497 handle structure pointer.
 * @param format info.
 */
status_t AK4497_SetEncoding(ak4497_handle_t *handle, uint8_t format);
/*!
 * @brief Configure the data format of audio data.
 *
 * This function would configure the registers about the sample rate, bit depths.
 *
 * @param handle AK4497 handle structure pointer.
 * @param mclk system clock of the codec which can be generated by MCLK or PLL output.
 * @param sampleRate Sample rate of audio file running in AK4497.
 * @param bitWidth Bit depth of audio file.
 */
status_t AK4497_ConfigDataFormat(ak4497_handle_t *handle, uint32_t mclk, uint32_t sampleRate, uint32_t bitWidth);

/*!
 * @brief Set the volume of different modules in AK4497.
 *
 * This function would set the volume of AK4497 modules. Users need to appoint the module.
 * The function assume that left channel and right channel has the same volume.
 *
 * @param handle AK4497 handle structure.
 * @param value Volume value need to be set.
 */
status_t AK4497_SetVolume(ak4497_handle_t *handle, uint8_t value);

/*!
 * @brief Get the volume of different modules in AK4497.
 *
 * This function gets the volume of AK4497. Users need to appoint the module.
 * The function assume that left channel and right channel has the same volume.
 *
 * @param handle AK4497 handle structure.
 * @param value volume value
 * @return value value of the module.
 */
status_t AK4497_GetVolume(ak4497_handle_t *handle, uint8_t *value);

/*!
 * @brief AK4497 codec module control.
 *
 * @param handle AK4497 handle structure pointer.
 * @param cmd module control command, support cmd kAK4497_ModuleSwitchDigitalInterface.
 * @param data control data, support data kCODEC_ModuleDigitalInterfacePCM/kCODEC_ModuleDigitalInterfaceDSD.
 */
status_t AK4497_ModuleControl(ak4497_handle_t *handle, ak4497_module_ctrl_cmd_t cmd, uint32_t data);

/*!
 * @brief Deinit the AK4497 codec.
 *
 * This function close all modules in AK4497 to save power.
 *
 * @param handle AK4497 handle structure pointer.
 */
status_t AK4497_Deinit(ak4497_handle_t *handle);
/*!
 * @brief Write register to AK4497 using I2C.
 *
 * @param handle AK4497 handle structure.
 * @param reg The register address in AK4497.
 * @param val Value needs to write into the register.
 */
status_t AK4497_WriteReg(ak4497_handle_t *handle, uint8_t reg, uint8_t val);

/*!
 * @brief Read register from AK4497 using I2C.
 * @param handle AK4497 handle structure.
 * @param reg The register address in AK4497.
 * @param val Value written to.
 */
status_t AK4497_ReadReg(ak4497_handle_t *handle, uint8_t reg, uint8_t *val);

/*!
 * @brief Modify some bits in the register using I2C.
 * @param handle AK4497 handle structure.
 * @param reg The register address in AK4497.
 * @param mask The mask code for the bits want to write. The bit you want to write should be 0.
 * @param val Value needs to write into the register.
 */
status_t AK4497_ModifyReg(ak4497_handle_t *handle, uint8_t reg, uint8_t mask, uint8_t val);

#if defined(__cplusplus)
}
#endif

/*! @} */
#endif /* _FSL_AK4497_H_ */
