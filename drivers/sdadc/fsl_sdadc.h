/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_SDADC_H_
#define FSL_SDADC_H_

#include "fsl_common.h"

/*!
 * @addtogroup sdadc
 * @{
 */

/******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @name Driver version */
/*!
 * @{
 */
/*! @brief SDADC driver version 2.0.0. */
#define FSL_SDADC_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*!
 * @}
 */

/*! @brief Macros are used to configure decimator volume. */
#define SDADC_DECIMATOR_VOL_CTRL_P_MASK(offset)  (SDADC_DECIMATOR_CTL_2_VOL_CTRL_P_0_MASK << offset)
#define SDADC_DECIMATOR_VOL_CTRL_P_SHIFT(offset) (SDADC_DECIMATOR_CTL_2_VOL_CTRL_P_0_SHIFT + offset)
#define SDADC_DECIMATOR_VOL_CTRL_P(volume, offset)                                    \
    (((uint32_t)(((uint32_t)(volume)) << SDADC_DECIMATOR_VOL_CTRL_P_SHIFT(offset))) & \
     SDADC_DECIMATOR_VOL_CTRL_P_MASK(offset))
#define SDADC_DECIMATOR_VOL_CTRL_N_MASK(offset)  (SDADC_DECIMATOR_CTL_2_VOL_CTRL_N_0_MASK << offset)
#define SDADC_DECIMATOR_VOL_CTRL_N_SHIFT(offset) (SDADC_DECIMATOR_CTL_2_VOL_CTRL_N_0_SHIFT + offset)
#define SDADC_DECIMATOR_VOL_CTRL_N(volume, offset)                                    \
    (((uint32_t)(((uint32_t)(volume)) << SDADC_DECIMATOR_VOL_CTRL_N_SHIFT(offset))) & \
     SDADC_DECIMATOR_VOL_CTRL_N_MASK(offset))

/*! @brief Macros are used to configure decimator sample rate. */
#define SDADC_DECIMATOR_SET_SPEED_P_MASK(offset)  (SDADC_DECIMATOR_CTL_4_SET_SPEED_P_0_MASK << (offset * 4U))
#define SDADC_DECIMATOR_SET_SPEED_P_SHIFT(offset) (SDADC_DECIMATOR_CTL_4_SET_SPEED_P_0_SHIFT + (offset * 4U))
#define SDADC_DECIMATOR_SET_SPEED_P(rate, offset)                                    \
    (((uint32_t)(((uint32_t)(rate)) << SDADC_DECIMATOR_SET_SPEED_P_SHIFT(offset))) & \
     SDADC_DECIMATOR_SET_SPEED_P_MASK(offset))
#define SDADC_DECIMATOR_SET_SPEED_N_MASK(offset)  (SDADC_DECIMATOR_CTL_4_SET_SPEED_N_0_MASK << (offset * 4U))
#define SDADC_DECIMATOR_SET_SPEED_N_SHIFT(offset) (SDADC_DECIMATOR_CTL_4_SET_SPEED_N_0_SHIFT + (offset * 4U))
#define SDADC_DECIMATOR_SET_SPEED_N(rate, offset)                                    \
    (((uint32_t)(((uint32_t)(rate)) << SDADC_DECIMATOR_SET_SPEED_N_SHIFT(offset))) & \
     SDADC_DECIMATOR_SET_SPEED_N_MASK(offset))

/*! @brief Macros are used to configure the dither amplitude. */
#define SDADC_ADC_CTL_2_SET_DITHER_MASK(offset)  (SDADC_ADC_CTL_2_SET_DITHER3_MASK << ((3U - offset) * 4U))
#define SDADC_ADC_CTL_2_SET_DITHER_SHIFT(offset) (SDADC_ADC_CTL_2_SET_DITHER3_SHIFT + ((3U - offset) * 4U))
#define SDADC_ADC_CTL_2_SET_DITHER(val, offset)                                    \
    (((uint32_t)(((uint32_t)(val)) << SDADC_ADC_CTL_2_SET_DITHER_SHIFT(offset))) & \
     SDADC_ADC_CTL_2_SET_DITHER_MASK(offset))

/*! @brief Macros are used to configure FIFO watermark. */
#define SDADC_FIFO_WATERMARK_CTL_P_MASK(offset)  (SDADC_FIFO_WATERMARK_CTL_WATERMARK_0_P_MASK << (offset * 8U))
#define SDADC_FIFO_WATERMARK_CTL_P_SHIFT(offset) (SDADC_FIFO_WATERMARK_CTL_WATERMARK_0_P_SHIFT + (offset * 8U))
#define SDADC_FIFO_WATERMARK_CTL_P(watermark, offset)                                    \
    (((uint32_t)(((uint32_t)(watermark)) << SDADC_FIFO_WATERMARK_CTL_P_SHIFT(offset))) & \
     SDADC_FIFO_WATERMARK_CTL_P_MASK(offset))
#define SDADC_FIFO_WATERMARK_CTL_N_MASK(offset)  (SDADC_FIFO_WATERMARK_CTL_WATERMARK_0_N_MASK << (offset * 8U))
#define SDADC_FIFO_WATERMARK_CTL_N_SHIFT(offset) (SDADC_FIFO_WATERMARK_CTL_WATERMARK_0_N_SHIFT + (offset * 8U))
#define SDADC_FIFO_WATERMARK_CTL_N(watermark, offset)                                    \
    (((uint32_t)(((uint32_t)(watermark)) << SDADC_FIFO_WATERMARK_CTL_N_SHIFT(offset))) & \
     SDADC_FIFO_WATERMARK_CTL_N_MASK(offset))

/*! @brief Macros are used for FIFO operations. */
#define SDADC_FIFO_WATERMARK_STATUS_MASK  0xFFU
#define SDADC_FIFO_WATERMARK_STATUS_SHIFT SDADC_FIFO_WATERMARK_ERROR_ST_WM_0_P_ST_SHIFT
#define SDADC_FIFO_FULL_INT_STATUS_MASK   0xFF00U
#define SDADC_FIFO_FULL_INT_STATUS_SHIFT  SDADC_FIFO_WATERMARK_ERROR_ST_ERR_0_P_SHIFT
#define SDADC_FIFO_MASK                   SDADC_FIFO_0_P_FIFO_0_P_MASK
#define SDADC_FIFO_SHIFT                  SDADC_FIFO_0_P_FIFO_0_P_SHIFT
#define SDADC_FIFO_ENTRIES_AVAIL_MASK     SDADC_FIFO_ENTRIES_AVAIL_0_FIFO_0_P_AVAIL_MASK
#define SDADC_FIFO_DEPTH                  (16U)
#define SDADC_FIFO_WIDTH                  (4U)

/*!
 * @brief This enumeration provides the mask for the SDADC channel P-Side and N-Side FIFO full interrupt enable/disable.
 */
enum _sdadc_fifo_int_enable
{
    kSDADC_Channel0_PSide_FifoFullIntEnable = SDADC_FIFO_WATERMARK_ERROR_CTL_ERR_0_P_EN_MASK,
    kSDADC_Channel0_NSide_FifoFullIntEnable = SDADC_FIFO_WATERMARK_ERROR_CTL_ERR_0_N_EN_MASK,
    kSDADC_Channel1_PSide_FifoFullIntEnable = SDADC_FIFO_WATERMARK_ERROR_CTL_ERR_1_P_EN_MASK,
    kSDADC_Channel1_NSide_FifoFullIntEnable = SDADC_FIFO_WATERMARK_ERROR_CTL_ERR_1_N_EN_MASK,
    kSDADC_Channel2_PSide_FifoFullIntEnable = SDADC_FIFO_WATERMARK_ERROR_CTL_ERR_2_P_EN_MASK,
    kSDADC_Channel2_NSide_FifoFullIntEnable = SDADC_FIFO_WATERMARK_ERROR_CTL_ERR_2_N_EN_MASK,
    kSDADC_Channel3_PSide_FifoFullIntEnable = SDADC_FIFO_WATERMARK_ERROR_CTL_ERR_3_P_EN_MASK,
    kSDADC_Channel3_NSide_FifoFullIntEnable = SDADC_FIFO_WATERMARK_ERROR_CTL_ERR_3_N_EN_MASK,
};

/*!
 * @brief This enumeration provides the mask for the SDADC channel P-Side and N-Side FIFO watermark enable/disable.
 */
enum _sdadc_fifo_watermark_enable
{
    kSDADC_Channel0_PSide_FifoWatermarkEnable = SDADC_FIFO_WATERMARK_ERROR_CTL_WM_0_P_EN_MASK,
    kSDADC_Channel0_NSide_FifoWatermarkEnable = SDADC_FIFO_WATERMARK_ERROR_CTL_WM_0_N_EN_MASK,
    kSDADC_Channel1_PSide_FifoWatermarkEnable = SDADC_FIFO_WATERMARK_ERROR_CTL_WM_1_P_EN_MASK,
    kSDADC_Channel1_NSide_FifoWatermarkEnable = SDADC_FIFO_WATERMARK_ERROR_CTL_WM_1_N_EN_MASK,
    kSDADC_Channel2_PSide_FifoWatermarkEnable = SDADC_FIFO_WATERMARK_ERROR_CTL_WM_2_P_EN_MASK,
    kSDADC_Channel2_NSide_FifoWatermarkEnable = SDADC_FIFO_WATERMARK_ERROR_CTL_WM_2_N_EN_MASK,
    kSDADC_Channel3_PSide_FifoWatermarkEnable = SDADC_FIFO_WATERMARK_ERROR_CTL_WM_3_P_EN_MASK,
    kSDADC_Channel3_NSide_FifoWatermarkEnable = SDADC_FIFO_WATERMARK_ERROR_CTL_WM_3_N_EN_MASK,
};

/*!
 * @brief This enumeration provides the mask for the SDADC channel P-Side and N-Side FIFO full interrupt status flag.
 */
enum _sdadc_fifo_int_status_flag
{
    kSDADC_Channel0_PSide_FifoFullIntStatusFlag = SDADC_FIFO_WATERMARK_ERROR_ST_ERR_0_P_MASK,
    kSDADC_Channel0_NSide_FifoFullIntStatusFlag = SDADC_FIFO_WATERMARK_ERROR_ST_ERR_0_N_MASK,
    kSDADC_Channel1_PSide_FifoFullIntStatusFlag = SDADC_FIFO_WATERMARK_ERROR_ST_ERR_1_P_MASK,
    kSDADC_Channel1_NSide_FifoFullIntStatusFlag = SDADC_FIFO_WATERMARK_ERROR_ST_ERR_1_N_MASK,
    kSDADC_Channel2_PSide_FifoFullIntStatusFlag = SDADC_FIFO_WATERMARK_ERROR_ST_ERR_2_P_MASK,
    kSDADC_Channel2_NSide_FifoFullIntStatusFlag = SDADC_FIFO_WATERMARK_ERROR_ST_ERR_2_N_MASK,
    kSDADC_Channel3_PSide_FifoFullIntStatusFlag = SDADC_FIFO_WATERMARK_ERROR_ST_ERR_3_P_MASK,
    kSDADC_Channel3_NSide_FifoFullIntStatusFlag = SDADC_FIFO_WATERMARK_ERROR_ST_ERR_3_N_MASK,
};

/*!
 * @brief This enumeration provides the mask for the SDADC channel P-Side and N-Side FIFO watermark status flag.
 */
enum _sdadc_fifo_watermark_status_flag
{
    kSDADC_Channel0_PSide_FifoWatermarkStatusFlag = SDADC_FIFO_WATERMARK_ERROR_ST_WM_0_P_ST_MASK,
    kSDADC_Channel0_NSide_FifoWatermarkStatusFlag = SDADC_FIFO_WATERMARK_ERROR_ST_WM_0_N_ST_MASK,
    kSDADC_Channel1_PSide_FifoWatermarkStatusFlag = SDADC_FIFO_WATERMARK_ERROR_ST_WM_1_P_ST_MASK,
    kSDADC_Channel1_NSide_FifoWatermarkStatusFlag = SDADC_FIFO_WATERMARK_ERROR_ST_WM_1_N_ST_MASK,
    kSDADC_Channel2_PSide_FifoWatermarkStatusFlag = SDADC_FIFO_WATERMARK_ERROR_ST_WM_2_P_ST_MASK,
    kSDADC_Channel2_NSide_FifoWatermarkStatusFlag = SDADC_FIFO_WATERMARK_ERROR_ST_WM_2_N_ST_MASK,
    kSDADC_Channel3_PSide_FifoWatermarkStatusFlag = SDADC_FIFO_WATERMARK_ERROR_ST_WM_3_P_ST_MASK,
    kSDADC_Channel3_NSide_FifoWatermarkStatusFlag = SDADC_FIFO_WATERMARK_ERROR_ST_WM_3_N_ST_MASK,
};

/*!
 * @brief This enumeration provides the selection of the SDADC channel mode.
 */
typedef enum _sdadc_channel_mode
{
    kSDADC_SingleEnd_Mode    = 0U, /*!< Single-end mode. */
    kSDADC_Differential_Mode = 1U, /*!< Differential mode. */
} sdadc_channel_mode_t;

/*!
 * @brief This enumeration provides the selection of the SDADC channel number.
 */
typedef enum _sdadc_channel_number
{
    kSDADC_Channel0 = 0U, /*!< SDADC channel 0. */
    kSDADC_Channel1 = 1U, /*!< SDADC channel 1. */
    kSDADC_Channel2 = 2U, /*!< SDADC channel 2. */
    kSDADC_Channel3 = 3U, /*!< SDADC channel 3. */
} sdadc_channel_number_t;

/*!
 * @brief This enumeration provides the selection of the SDADC channel type.
 */
typedef enum _sdadc_channel_type
{
    kSDADC_Channel_NSide_Type     = 0x01U, /*!< N-side selected. */
    kSDADC_Channel_PSide_Type     = 0x10U, /*!< P-side selected. */
    kSDADC_Channel_NandPSide_Type = 0x11U, /*!< N- and P-side selected. */
} sdadc_channel_type_t;

/*!
 * @brief This enumeration provides the selection of the SDADC decimator sample rate.
 */
typedef enum _sdadc_decimator_sample_rate
{
    kSDADC_DecimatorSampleRate48kHz = 0x0U, /*!< 48kHz decimator sample rate. */
    kSDADC_DecimatorSampleRate32kHz = 0x1U, /*!< 32kHz decimator sample rate. */
    kSDADC_DecimatorSampleRate16kHz = 0x2U, /*!< 16kHz decimator sample rate. */
} sdadc_decimator_sample_rate_t;

/*!
 * @brief This enumeration provides the selection of the SDADC LDO drive capability.
 */
typedef enum _sdadc_ldo_drive_capability
{
    kSDADC_LdoLowPower  = 0x0U, /*!< To drive 1 single-end mode or 1 differential mode SDADC. */
    kSDADC_LdoHighPower = 0x1U, /*!< To drive more than 1 SDADC */
} sdadc_ldo_drive_capability_t;

/*!
 * @brief This enumeration provides the selection of the SDADC reference mode.
 *
 * @details The SDADC reference module has four modes, these modes are controlled via REF_CTL register
 * 'fast_ref_enable' and 'pwr_fast_ref_enable' bitfields.
 *      1.Retain mode: pwr_fast_ref_enable = 0b, fast_ref_enable = 0b.
 *      2.Low noise mode: pwr_fast_ref_enable = 0b, fast_ref_enable = 1b.
 *      3.Low power mode: pwr_fast_ref_enable = 1b, fast_ref_enable = 0b.
 *      4.Fast charge mode: pwr_fast_ref_enable = 1b, fast_ref_enable = 1b.
 */
typedef enum _sdadc_ref_mode
{
    kSDADC_RefRetainMode     = 0x0U, /*!< Reference in retain mode. */
    kSDADC_RefLowNoiseMode   = 0x1U, /*!< Reference in low noise mode. */
    kSDADC_RefLowPowerMode   = 0x2U, /*!< Reference in low power mode. */
    kSDADC_RefFastChargeMode = 0x3U, /*!< Reference in fast charge mode. */
} sdadc_ref_mode_t;

/*!
 * @brief This enumeration provides the selection of the SDADC FIFO write or/and read operation.
 */
typedef enum _sdadc_fifo_reset_operation
{
    kSDADC_FifoWriteReset        = 0x1U, /*!< FIFO write reset. */
    kSDADC_FifoReadReset         = 0x2U, /*!< FIFO read reset. */
    kSDADC_FifoWriteAndReadReset = 0x3U, /*!< FIFO write and read reset. */
} sdadc_fifo_reset_operation_t;

/*!
 * @brief This structure is used to configure the decimator volume (gain).
 *
 * @note The gain setting is not applicable for the channel N-Side when executing the differential mode. For the
 * specific gain setting value please refer to the reference manual.
 */
typedef struct _sdadc_volume
{
    uint8_t pSideVolume; /*!< Sets the gain for the P-Side decimator. */
    uint8_t nSideVolume; /*!< Sets the gain for the N-Side decimator. */
} sdadc_volume_control_t;

/*!
 * @brief This structure is used to configure the decimator sample rate.
 */
typedef struct _sdadc_sample_rate
{
    sdadc_decimator_sample_rate_t pSideSampleRate; /*!< Sets the P-Side decimator sample rate. */
    sdadc_decimator_sample_rate_t nSideSampleRate; /*!< Sets the N-Side decimator sample rate. */
} sdadc_sample_rate_t;

/*!
 * @brief This structure is used to configure the FIFO watermark.
 *
 * @note In the differential mode, the bitstream is converted to 24bit data (FIFO_x_P[23:0]) by P-Side decimator,
 * the output of N-Side decimator (FIFO_x_N[23:0]) is not valid.
 */
typedef struct _sdadc_watermark
{
    uint8_t pSideWatermark; /*!< Sets the channel N-Side FIFO watermark. */
    uint8_t nSideWatermark; /*!< Sets the channel P-Side FIFO watermark. */
} sdadc_watermark_t;

/*!
 * @brief This structure is used to configure the SDADC channels.
 */
typedef struct _sdadc_channel_config
{
    sdadc_channel_mode_t mode;      /*!< Sets channel mode. */
    sdadc_channel_number_t number;  /*!< Sets channel number. */
    sdadc_channel_type_t type;      /*!< Sets channel type. */

    sdadc_volume_control_t volume;  /*!< Sets N- and P-side decimator volume. */
    sdadc_sample_rate_t samplerate; /*!< Sets N- and P-side decimator samplerate. */
    sdadc_watermark_t watermark;    /*!< Sets N- and P-side FIFO watermark. */

    bool enableDacCompensation;     /*!< Decides whether to enable the compensation feature for the ADCp[3:0] or/and
                                    ADCn[3:0] in the single-end mode, is used to avoid large data-dependent ripple
                                    on LDO output which will impact the ADC performance. */
    bool enableDCLoop;              /*!< In some cases of the single-end mode, the microphone output is connected
                                    directly to ADC input without the coupling capacitor, DC Loop is activated to
                                    regulate input common-mode voltage of the ADCp[3:0] or/and ADCn[3:0]. In the
                                    single-end mode, there is the possibility to connect MEMS or JFET microphone
                                    directly to the input (DC-coupled). In this configuration, DC Loop mode needs
                                    to be activated to establish the correct common mode input voltage level at
                                    the input pin. The DC Loop function should disabled in the differential mode. */
    bool enableDcFilter;            /*!< Decides whether to enable the decimator DC Filter to remove DC components.*/
    bool enablePolarityInvert; /*!< Decides whether to enable the polarity invert function, for example: if the input to
                               ADC is a pure sinus signal, then if the polarity invert is enabled, the decimation output
                               will be a sinus signal 180 out of phase with the input. */
} sdadc_channel_config_t;

/*!
 * @brief This structure is used to configure the SDADC module.
 */
typedef struct _sdadc_config
{
    uint8_t channelCount;                  /*!< Indicates how many channels to execute the conversion. */
    sdadc_channel_config_t *channelConfig; /*!< SDADC channels configuration. */
} sdadc_config_t;

/*!
 * @brief This structure is used to construct channel groups.
 */
typedef struct _sdadc_channel_group
{
    sdadc_channel_number_t number; /*!< Channel number. */
    sdadc_channel_type_t type;     /*!< Channel type. */
} sdadc_channel_group;

/******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name SDADC initialization and de-initialization.
 * @{
 */
/*!
 * @brief This function is used to get available predefined configurations for the SDADC initialization.
 *
 * @param config Pointer to the SDADC configuration structure, please refer to @ref sdadc_config_t for details.
 */
void SDADC_GetDefaultConfig(sdadc_config_t *config);

/*!
 * @brief This function is used to initialize the SDADC.
 *
 * @param base SDADC peripheral base address.
 * @param config Pointer to the SDADC configuration structure, please refer to @ref sdadc_config_t for details.
 */
void SDADC_Init(SDADC_Type *base, const sdadc_config_t *config);

/*!
 * @brief This function is used to de-initialize the SDADC.
 *
 * @param base SDADC peripheral base address.
 * @param config Pointer to the SDADC configuration structure, please refer to @ref sdadc_config_t for details.
 */
void SDADC_Deinit(SDADC_Type *base, const sdadc_config_t *config);
/*!
 * @}
 */

/*!
 * @name SDADC channel modulator, reference, and LDO configuration.
 * @{
 */
/*!
 * @brief This function is used to power up the SDADC in the initialization state.
 *
 * @param base SDADC peripheral base address.
 * @param config Pointer to the SDADC configuration structure, please refer to @ref sdadc_config_t for details.
 * @param clock Core clock frequency with Hz.
 */
void SDADC_DoInitPowerUp(SDADC_Type *base, sdadc_config_t *config, uint32_t clock);

/*!
 * @brief This function is used to enable or disable SDADC specific channel's P-Side or/and N-Side sigma-delta
 * modulator power.
 *
 * @param base SDADC peripheral base address.
 * @param number channel number, refer @ref sdadc_channel_number_t for details.
 * @param type channel type, refer @ref sdadc_channel_type_t for details.
 * @param enable Decides whether to enable or disable.
 * - @b true Enable
 * - @b false Disable
 */
static inline void SDADC_ControlModulatorPowerEnable(SDADC_Type *base,
                                                     sdadc_channel_number_t number,
                                                     sdadc_channel_type_t type,
                                                     bool enable)
{
    if (enable)
    {
        if (type == kSDADC_Channel_PSide_Type)
        {
            base->ADC_CTL_0 |= (0x1U << (number + SDADC_ADC_CTL_0_ADCP_POWER_ENABLE_SHIFT));
        }
        else if (type == kSDADC_Channel_NSide_Type)
        {
            base->ADC_CTL_0 |= (0x1U << (number + SDADC_ADC_CTL_0_ADCN_POWER_ENABLE_SHIFT));
        }
        else
        {
            base->ADC_CTL_0 |= ((0x1U << (number + SDADC_ADC_CTL_0_ADCP_POWER_ENABLE_SHIFT)) |
                                (0x1U << (number + SDADC_ADC_CTL_0_ADCN_POWER_ENABLE_SHIFT)));
        }
    }
    else
    {
        if (type == kSDADC_Channel_PSide_Type)
        {
            base->ADC_CTL_0 &= ~(0x1U << (number + SDADC_ADC_CTL_0_ADCP_POWER_ENABLE_SHIFT));
        }
        else if (type == kSDADC_Channel_NSide_Type)
        {
            base->ADC_CTL_0 &= ~(0x1U << (number + SDADC_ADC_CTL_0_ADCN_POWER_ENABLE_SHIFT));
        }
        else
        {
            base->ADC_CTL_0 &= ~((0x1U << (number + SDADC_ADC_CTL_0_ADCP_POWER_ENABLE_SHIFT)) |
                                 (0x1U << (number + SDADC_ADC_CTL_0_ADCN_POWER_ENABLE_SHIFT)));
        }
    }
}

/*!
 * @brief This function is used to enable or disable the reference power.
 *
 * @param base SDADC peripheral base address.
 * @param enable Indicates enable or disable the reference power.
 * - @b true Enable
 * - @b false Disable
 */
static inline void SDADC_ControlReferencePowerEnable(SDADC_Type *base, bool enable)
{
    if (enable)
    {
        base->REF_CTL |= SDADC_REF_CTL_REF_POWER_ENABLE_MASK;
    }
    else
    {
        base->REF_CTL &= ~SDADC_REF_CTL_REF_POWER_ENABLE_MASK;
    }
}

/*!
 * @brief This function is used to configure the reference mode.
 *
 * @note Setting the reference to fast charge mode is mainly used during startup where fast startup
 * is required, the current consumption in this mode is the largest, so, it is recommended to switch
 * to other modes to minimize current consumption. If the ADC works on the single-end mode, recommend
 * switching to the low-noise mode, if the ADC works on the differential mode, recommend switching to
 * the retain mode.
 *
 * @param base SDADC peripheral base address.
 * @param referenceMode Reference mode to be configured, see @ref sdadc_ref_mode_t for details.
 */
static inline void SDADC_ConfigureReferenceMode(SDADC_Type *base, sdadc_ref_mode_t referenceMode)
{
    base->REF_CTL =
        ((base->REF_CTL & (~(SDADC_REF_CTL_FAST_REF_ENABLE_MASK | SDADC_REF_CTL_PWR_FAST_REF_ENABLE_MASK))) |
         ((((referenceMode & 0x2U) != 0UL) ? SDADC_REF_CTL_PWR_FAST_REF_ENABLE_MASK : 0U) |
          (((referenceMode & 0x1U) != 0UL) ? SDADC_REF_CTL_FAST_REF_ENABLE_MASK : 0U)));
}

/*!
 * @brief This function is used to enable or disable the LDO power.
 *
 * @param base SDADC peripheral base address.
 * @param enable Indicates enable or disable the LDO power.
 * - @b true Enable
 * - @b false Disable
 */
static inline void SDADC_ControlLdoPowerEnable(SDADC_Type *base, bool enable)
{
    if (enable)
    {
        base->LDO_CTL |= SDADC_LDO_CTL_LDO_POWER_ENABLE_MASK;
    }
    else
    {
        base->LDO_CTL &= ~SDADC_LDO_CTL_LDO_POWER_ENABLE_MASK;
    }
}

/*!
 * @brief This function is used to configure the drive capability.
 *
 * @param base SDADC peripheral base address.
 * @param capability SDADC LDO drive capability to be set, see @ref sdadc_ldo_drive_capability_t for details.
 */
static inline void SDADC_ConfigureLdoDriveCapability(SDADC_Type *base, sdadc_ldo_drive_capability_t capability)
{
    base->LDO_CTL = ((base->LDO_CTL & (~SDADC_LDO_CTL_LDO_SETTING_MASK)) | (SDADC_LDO_CTL_LDO_SETTING(capability)));
}
/*!
 * @}
 */

/*!
 * @name SDADC channel mode, DAC compensation, modulator DC Loop, decimator DC Filter configuration.
 * @{
 */
/*!
 * @brief This function is used to configure the channel mode.
 *
 * @param base SDADC peripheral base address.
 * @param number channel number, refer @ref sdadc_channel_number_t for details.
 * @param mode channel mode, refer @ref sdadc_channel_mode_t for details.
 */
static inline void SDADC_ConfigureChannelMode(SDADC_Type *base,
                                              sdadc_channel_number_t number,
                                              sdadc_channel_mode_t mode)
{
    if (kSDADC_SingleEnd_Mode == mode)
    {
        base->ADC_CTL_1 &= ~(0x01U << (SDADC_ADC_CTL_1_DIFF_ENABLE_SHIFT + number));
    }
    else
    {
        base->ADC_CTL_1 |= (0x01U << (SDADC_ADC_CTL_1_DIFF_ENABLE_SHIFT + number));
    }
}

/*!
 * @brief This function is used to enable or disable the DAC compensation function.
 *
 * @param base SDADC peripheral base address.
 * @param number channel number, refer @ref sdadc_channel_number_t for details.
 * @param type channel type, refer @ref sdadc_channel_type_t for details.
 * @param enable Decides whether to enable or disable.
 * - @b true Enable
 * - @b false Disable
 */
static inline void SDADC_ControlDacCompensationEnable(SDADC_Type *base,
                                                      sdadc_channel_number_t number,
                                                      sdadc_channel_type_t type,
                                                      bool enable)
{
    if (enable)
    {
        if (type == kSDADC_Channel_PSide_Type)
        {
            base->ADC_CTL_0 |= (0x1U << (number + SDADC_ADC_CTL_0_COMP_ADCP_ENABLE_SHIFT));
        }
        else if (type == kSDADC_Channel_NSide_Type)
        {
            base->ADC_CTL_0 |= (0x1U << (number + SDADC_ADC_CTL_0_COMP_ADCN_ENABLE_SHIFT));
        }
        else
        {
            base->ADC_CTL_0 |= ((0x1U << (number + SDADC_ADC_CTL_0_COMP_ADCP_ENABLE_SHIFT)) |
                                (0x1U << (number + SDADC_ADC_CTL_0_COMP_ADCN_ENABLE_SHIFT)));
        }
    }
    else
    {
        if (type == kSDADC_Channel_PSide_Type)
        {
            base->ADC_CTL_0 &= ~(0x1U << (number + SDADC_ADC_CTL_0_COMP_ADCP_ENABLE_SHIFT));
        }
        else if (type == kSDADC_Channel_NSide_Type)
        {
            base->ADC_CTL_0 &= ~(0x1U << (number + SDADC_ADC_CTL_0_COMP_ADCN_ENABLE_SHIFT));
        }
        else
        {
            base->ADC_CTL_0 &= ~((0x1U << (number + SDADC_ADC_CTL_0_COMP_ADCP_ENABLE_SHIFT)) |
                                 (0x1U << (number + SDADC_ADC_CTL_0_COMP_ADCN_ENABLE_SHIFT)));
        }
    }
}

/*!
 * @brief This function is used to enable or disable the modulator DC Loop function.
 *
 * @param base SDADC peripheral base address.
 * @param number channel number, refer @ref sdadc_channel_number_t for details.
 * @param type channel type, refer @ref sdadc_channel_type_t for details.
 * @param enable Decides whether to enable or disable.
 * - @b true Enable
 * - @b false Disable
 */
static inline void SDADC_ControlModulatorDcLoopEnable(SDADC_Type *base,
                                                      sdadc_channel_number_t number,
                                                      sdadc_channel_type_t type,
                                                      bool enable)
{
    if (enable)
    {
        if (type == kSDADC_Channel_PSide_Type)
        {
            base->ADC_CTL_1 |= (0x1U << (number + SDADC_ADC_CTL_1_DCLOOP_P_ANA_ENABLE_SHIFT));
            base->DC_LOOP_CTL_0 |= (0x1U << (number + SDADC_DC_LOOP_CTL_0_DCLOOP_P_ENABLE_SHIFT));
        }
        else if (type == kSDADC_Channel_NSide_Type)
        {
            base->ADC_CTL_1 |= (0x1U << (number + SDADC_ADC_CTL_1_DCLOOP_N_ANA_ENABLE_SHIFT));
            base->DC_LOOP_CTL_0 |= (0x1U << (number + SDADC_DC_LOOP_CTL_0_DCLOOP_N_ENABLE_SHIFT));
        }
        else
        {
            base->ADC_CTL_1 |= ((0x1U << (number + SDADC_ADC_CTL_1_DCLOOP_P_ANA_ENABLE_SHIFT)) |
                                (0x1U << (number + SDADC_ADC_CTL_1_DCLOOP_N_ANA_ENABLE_SHIFT)));
            base->DC_LOOP_CTL_0 |= ((0x1U << (number + SDADC_DC_LOOP_CTL_0_DCLOOP_P_ENABLE_SHIFT)) |
                                    (0x1U << (number + SDADC_DC_LOOP_CTL_0_DCLOOP_N_ENABLE_SHIFT)));
        }
    }
    else
    {
        if (type == kSDADC_Channel_PSide_Type)
        {
            base->ADC_CTL_1 &= ~(0x1U << (number + SDADC_ADC_CTL_1_DCLOOP_P_ANA_ENABLE_SHIFT));
            base->DC_LOOP_CTL_0 &= ~(0x1U << (number + SDADC_DC_LOOP_CTL_0_DCLOOP_P_ENABLE_SHIFT));
        }
        else if (type == kSDADC_Channel_NSide_Type)
        {
            base->ADC_CTL_1 &= ~(0x1U << (number + SDADC_ADC_CTL_1_DCLOOP_N_ANA_ENABLE_SHIFT));
            base->DC_LOOP_CTL_0 &= ~(0x1U << (number + SDADC_DC_LOOP_CTL_0_DCLOOP_N_ENABLE_SHIFT));
        }
        else
        {
            base->ADC_CTL_1 &= ~((0x1U << (number + SDADC_ADC_CTL_1_DCLOOP_P_ANA_ENABLE_SHIFT)) |
                                 (0x1U << (number + SDADC_ADC_CTL_1_DCLOOP_N_ANA_ENABLE_SHIFT)));
            base->DC_LOOP_CTL_0 &= ~((0x1U << (number + SDADC_DC_LOOP_CTL_0_DCLOOP_P_ENABLE_SHIFT)) |
                                     (0x1U << (number + SDADC_DC_LOOP_CTL_0_DCLOOP_N_ENABLE_SHIFT)));
        }
    }
}

/*!
 * @brief This function is used to enable or disable the decimator DC Filter function.
 *
 * @param base SDADC peripheral base address.
 * @param number channel number, refer @ref sdadc_channel_number_t for details.
 * @param type channel type, refer @ref sdadc_channel_type_t for details.
 * @param enable Decides whether to enable or disable.
 * - @b true Enable
 * - @b false Disable
 */
static inline void SDADC_ControlDecimatorDcFilterEnable(SDADC_Type *base,
                                                        sdadc_channel_number_t number,
                                                        sdadc_channel_type_t type,
                                                        bool enable)
{
    if (enable)
    {
        if (type == kSDADC_Channel_PSide_Type)
        {
            base->DECIMATOR_CTL_0 |= (0x1U << (number + SDADC_DECIMATOR_CTL_0_DCFILTI_P_ENABLE_SHIFT));
        }
        else if (type == kSDADC_Channel_NSide_Type)
        {
            base->DECIMATOR_CTL_0 |= (0x1U << (number + SDADC_DECIMATOR_CTL_0_DCFILTI_N_ENABLE_SHIFT));
        }
        else
        {
            base->DECIMATOR_CTL_0 |= ((0x1U << (number + SDADC_DECIMATOR_CTL_0_DCFILTI_P_ENABLE_SHIFT)) |
                                      (0x1U << (number + SDADC_DECIMATOR_CTL_0_DCFILTI_N_ENABLE_SHIFT)));
        }
    }
    else
    {
        if (type == kSDADC_Channel_PSide_Type)
        {
            base->DECIMATOR_CTL_0 &= ~(0x1U << (number + SDADC_DECIMATOR_CTL_0_DCFILTI_P_ENABLE_SHIFT));
        }
        else if (type == kSDADC_Channel_NSide_Type)
        {
            base->DECIMATOR_CTL_0 &= ~(0x1U << (number + SDADC_DECIMATOR_CTL_0_DCFILTI_N_ENABLE_SHIFT));
        }
        else
        {
            base->DECIMATOR_CTL_0 &= ~((0x1U << (number + SDADC_DECIMATOR_CTL_0_DCFILTI_P_ENABLE_SHIFT)) |
                                       (0x1U << (number + SDADC_DECIMATOR_CTL_0_DCFILTI_N_ENABLE_SHIFT)));
        }
    }
}

/*!
 * @brief This function is used to enable or disable the decimator output invert.
 *
 * @param base SDADC peripheral base address.
 * @param number channel number, refer @ref sdadc_channel_number_t for details.
 * @param type channel type, refer @ref sdadc_channel_type_t for details.
 * @param enable Decides whether to enable or disable.
 * - @b true Enable
 * - @b false Disable
 */
static inline void SDADC_ControlDecimatorOutputInvertEnable(SDADC_Type *base,
                                                            sdadc_channel_number_t number,
                                                            sdadc_channel_type_t type,
                                                            bool enable)
{
    if (enable)
    {
        if (type == kSDADC_Channel_PSide_Type)
        {
            base->DECIMATOR_CTL_0 |= (0x1U << (number + SDADC_DECIMATOR_CTL_0_POL_INV_P_ENABLE_SHIFT));
        }
        else if (type == kSDADC_Channel_NSide_Type)
        {
            base->DECIMATOR_CTL_0 |= (0x1U << (number + SDADC_DECIMATOR_CTL_0_POL_INV_N_ENABLE_SHIFT));
        }
        else
        {
            base->DECIMATOR_CTL_0 |= ((0x1U << (number + SDADC_DECIMATOR_CTL_0_POL_INV_P_ENABLE_SHIFT)) |
                                      (0x1U << (number + SDADC_DECIMATOR_CTL_0_POL_INV_N_ENABLE_SHIFT)));
        }
    }
    else
    {
        if (type == kSDADC_Channel_PSide_Type)
        {
            base->DECIMATOR_CTL_0 &= ~(0x1U << (number + SDADC_DECIMATOR_CTL_0_POL_INV_P_ENABLE_SHIFT));
        }
        else if (type == kSDADC_Channel_NSide_Type)
        {
            base->DECIMATOR_CTL_0 &= ~(0x1U << (number + SDADC_DECIMATOR_CTL_0_POL_INV_N_ENABLE_SHIFT));
        }
        else
        {
            base->DECIMATOR_CTL_0 &= ~((0x1U << (number + SDADC_DECIMATOR_CTL_0_POL_INV_P_ENABLE_SHIFT)) |
                                       (0x1U << (number + SDADC_DECIMATOR_CTL_0_POL_INV_N_ENABLE_SHIFT)));
        }
    }
}

/*!
 * @brief This function is used to configure the decimator volume.
 *
 * @param base SDADC peripheral base address.
 * @param number channel number, refer @ref sdadc_channel_number_t for details.
 * @param type channel type, refer @ref sdadc_channel_type_t for details.
 * @param volume Volume level, see @ref sdadc_volume_control_t for details.
 */
static inline void SDADC_ConfigureDecimatorVolume(SDADC_Type *base,
                                                  sdadc_channel_number_t number,
                                                  sdadc_channel_type_t type,
                                                  sdadc_volume_control_t volume)
{
    uint8_t registerOffset = number / 2U;
    uint8_t bitfieldOffset = number % 2U * 16U;

    if (type == kSDADC_Channel_PSide_Type)
    {
        (*((&(base->DECIMATOR_CTL_2)) + registerOffset)) =
            (((*((&(base->DECIMATOR_CTL_2)) + registerOffset)) & (~(SDADC_DECIMATOR_VOL_CTRL_P_MASK(bitfieldOffset)))) |
             SDADC_DECIMATOR_VOL_CTRL_P(volume.pSideVolume, bitfieldOffset));
    }
    else if (type == kSDADC_Channel_NSide_Type)
    {
        (*((&(base->DECIMATOR_CTL_2)) + registerOffset)) =
            (((*((&(base->DECIMATOR_CTL_2)) + registerOffset)) & (~(SDADC_DECIMATOR_VOL_CTRL_N_MASK(bitfieldOffset)))) |
             SDADC_DECIMATOR_VOL_CTRL_N(volume.nSideVolume, bitfieldOffset));
    }
    else
    {
        (*((&(base->DECIMATOR_CTL_2)) + registerOffset)) =
            (((*((&(base->DECIMATOR_CTL_2)) + registerOffset)) &
              (~(SDADC_DECIMATOR_VOL_CTRL_P_MASK(bitfieldOffset) | SDADC_DECIMATOR_VOL_CTRL_N_MASK(bitfieldOffset)))) |
             (SDADC_DECIMATOR_VOL_CTRL_P(volume.pSideVolume, bitfieldOffset) |
              SDADC_DECIMATOR_VOL_CTRL_N(volume.nSideVolume, bitfieldOffset)));
    }
}

/*!
 * @brief This function is used to configure the decimator sample rate.
 *
 * @param base SDADC peripheral base address.
 * @param number channel number, refer @ref sdadc_channel_number_t for details.
 * @param type channel type, refer @ref sdadc_channel_type_t for details.
 * @param sampleRate Sample rate, see @ref sdadc_sample_rate_t for details.
 */
static inline void SDADC_ConfigureDecimatorSampleRate(SDADC_Type *base,
                                                      sdadc_channel_number_t number,
                                                      sdadc_channel_type_t type,
                                                      sdadc_sample_rate_t sampleRate)
{
    if (type == kSDADC_Channel_PSide_Type)
    {
        base->DECIMATOR_CTL_4 = ((base->DECIMATOR_CTL_4 & (~SDADC_DECIMATOR_SET_SPEED_P_MASK(number))) |
                                 SDADC_DECIMATOR_SET_SPEED_P(sampleRate.pSideSampleRate, number));
    }
    else if (type == kSDADC_Channel_NSide_Type)
    {
        base->DECIMATOR_CTL_4 = ((base->DECIMATOR_CTL_4 & (~SDADC_DECIMATOR_SET_SPEED_N_MASK(number))) |
                                 SDADC_DECIMATOR_SET_SPEED_N(sampleRate.nSideSampleRate, number));
    }
    else
    {
        base->DECIMATOR_CTL_4 =
            ((base->DECIMATOR_CTL_4 &
              (~(SDADC_DECIMATOR_SET_SPEED_P_MASK(number) | SDADC_DECIMATOR_SET_SPEED_N_MASK(number)))) |
             (SDADC_DECIMATOR_SET_SPEED_P(sampleRate.pSideSampleRate, number) |
              SDADC_DECIMATOR_SET_SPEED_N(sampleRate.nSideSampleRate, number)));
    }
}

/*!
 * @brief This function is used to set the dither amplitude.
 *
 * @details In the ADC conversion process, adding dither can improve the ADC dynamic performance, but too large a dither
 * will cause the input signal to overflow, the user needs to set the appropriate dither amplitude according to their
 * own needs.
 *
 * @param base SDADC peripheral base address.
 * @param number channel number, refer @ref sdadc_channel_number_t for details.
 * @param ditherAmplitude The dither amplitude that will be introduced, the range is from 000b to 111b, 000b means
 * disable the dither.
 */
static inline void SDADC_ConfigureDitherAmplitude(SDADC_Type *base,
                                                  sdadc_channel_number_t number,
                                                  uint8_t ditherAmplitude)
{
    base->ADC_CTL_2 = ((base->ADC_CTL_2 & (~SDADC_ADC_CTL_2_SET_DITHER_MASK(number))) |
                       (SDADC_ADC_CTL_2_SET_DITHER(ditherAmplitude, number)));
}
/*!
 * @}
 */

/*!
 * @name SDADC modulator, decimator, and modulator DC Loop reset and release reset.
 * @{
 */
/*!
 * @brief This function is used to reset or release reset for the SDADC specific channel's P-Side or N-Side sigma-delta
 * modulator.
 *
 * @note Needs to be reset for at least 15us after start-up, and then release the reset.
 *
 * @param base SDADC peripheral base address.
 * @param number channel number, refer @ref sdadc_channel_number_t for details.
 * @param type channel type, refer @ref sdadc_channel_type_t for details.
 * @param reset Indicates reset or release reset for the sigma-delta modulator.
 * - @b true Reset
 * - @b false Release reset
 */
static inline void SDADC_ControlModulatorReset(SDADC_Type *base,
                                               sdadc_channel_number_t number,
                                               sdadc_channel_type_t type,
                                               bool reset)
{
    if (reset)
    {
        if (type == kSDADC_Channel_PSide_Type)
        {
            base->ADC_CTL_0 &= ~(0x1U << (number + SDADC_ADC_CTL_0_RST_AN_ADCP_SHIFT));
        }
        else if (type == kSDADC_Channel_NSide_Type)
        {
            base->ADC_CTL_0 &= ~(0x1U << (number + SDADC_ADC_CTL_0_RST_AN_ADCN_SHIFT));
        }
        else
        {
            base->ADC_CTL_0 &= ~((0x1U << (number + SDADC_ADC_CTL_0_RST_AN_ADCP_SHIFT)) |
                                 (0x1U << (number + SDADC_ADC_CTL_0_RST_AN_ADCN_SHIFT)));
        }
    }
    else
    {
        if (type == kSDADC_Channel_PSide_Type)
        {
            base->ADC_CTL_0 |= (0x1U << (number + SDADC_ADC_CTL_0_RST_AN_ADCP_SHIFT));
        }
        else if (type == kSDADC_Channel_NSide_Type)
        {
            base->ADC_CTL_0 |= (0x1U << (number + SDADC_ADC_CTL_0_RST_AN_ADCN_SHIFT));
        }
        else
        {
            base->ADC_CTL_0 |= ((0x1U << (number + SDADC_ADC_CTL_0_RST_AN_ADCP_SHIFT)) |
                                (0x1U << (number + SDADC_ADC_CTL_0_RST_AN_ADCN_SHIFT)));
        }
    }
}

/*!
 * @brief This function is used to reset or release reset for the SDADC channeln's P-Side or/and N-Side decimator.
 *
 * @param base SDADC peripheral base address.
 * @param number channel number, refer @ref sdadc_channel_number_t for details.
 * @param type channel type, refer @ref sdadc_channel_type_t for details.
 * @param reset Indicates reset or release reset for the decimator.
 * - @b true Reset
 * - @b false Release reset
 */
static inline void SDADC_ControlDecimatorReset(SDADC_Type *base,
                                               sdadc_channel_number_t number,
                                               sdadc_channel_type_t type,
                                               bool reset)
{
    if (reset)
    {
        if (type == kSDADC_Channel_PSide_Type)
        {
            base->DECIMATOR_CTL_1 &= ~(0x1U << (number + SDADC_DECIMATOR_CTL_1_FUNC_LOCAL_RST_AN_DEC_P_SHIFT));
        }
        else if (type == kSDADC_Channel_NSide_Type)
        {
            base->DECIMATOR_CTL_1 &= ~(0x1U << (number + SDADC_DECIMATOR_CTL_1_FUNC_LOCAL_RST_AN_DEC_N_SHIFT));
        }
        else
        {
            base->DECIMATOR_CTL_1 &= ~((0x1U << (number + SDADC_DECIMATOR_CTL_1_FUNC_LOCAL_RST_AN_DEC_P_SHIFT)) |
                                       (0x1U << (number + SDADC_DECIMATOR_CTL_1_FUNC_LOCAL_RST_AN_DEC_N_SHIFT)));
        }
    }
    else
    {
        if (type == kSDADC_Channel_PSide_Type)
        {
            base->DECIMATOR_CTL_1 |= (0x1U << (number + SDADC_DECIMATOR_CTL_1_FUNC_LOCAL_RST_AN_DEC_P_SHIFT));
        }
        else if (type == kSDADC_Channel_NSide_Type)
        {
            base->DECIMATOR_CTL_1 |= (0x1U << (number + SDADC_DECIMATOR_CTL_1_FUNC_LOCAL_RST_AN_DEC_N_SHIFT));
        }
        else
        {
            base->DECIMATOR_CTL_1 |= ((0x1U << (number + SDADC_DECIMATOR_CTL_1_FUNC_LOCAL_RST_AN_DEC_P_SHIFT)) |
                                      (0x1U << (number + SDADC_DECIMATOR_CTL_1_FUNC_LOCAL_RST_AN_DEC_N_SHIFT)));
        }
    }
}

/*!
 * @brief This function is used to reset or release reset for the SDADC channeln's P-Side or/and N-Side madulator DC
 * Loop.
 *
 * @param base SDADC peripheral base address.
 * @param number channel number, refer @ref sdadc_channel_number_t for details.
 * @param type channel type, refer @ref sdadc_channel_type_t for details.
 * @param reset Indicates whether reset or release reset for the madulator DC Loop.
 * - @b true Reset
 * - @b false Release reset
 */
static inline void SDADC_ConfigureModulatorDcLoopReset(SDADC_Type *base,
                                                       sdadc_channel_number_t number,
                                                       sdadc_channel_type_t type,
                                                       bool reset)
{
    if (reset)
    {
        if (type == kSDADC_Channel_PSide_Type)
        {
            base->DC_LOOP_CTL_1 &= ~(0x1U << (number + SDADC_DC_LOOP_CTL_1_FUNC_LOCAL_RST_AN_DCLOOP_P_SHIFT));
        }
        else if (type == kSDADC_Channel_NSide_Type)
        {
            base->DC_LOOP_CTL_1 &= ~(0x1U << (number + SDADC_DC_LOOP_CTL_1_FUNC_LOCAL_RST_AN_DCLOOP_N_SHIFT));
        }
        else
        {
            base->DC_LOOP_CTL_1 &= ~((0x1U << (number + SDADC_DC_LOOP_CTL_1_FUNC_LOCAL_RST_AN_DCLOOP_P_SHIFT)) |
                                     (0x1U << (number + SDADC_DC_LOOP_CTL_1_FUNC_LOCAL_RST_AN_DCLOOP_N_SHIFT)));
        }
    }
    else
    {
        if (type == kSDADC_Channel_PSide_Type)
        {
            base->DC_LOOP_CTL_1 |= (0x1U << (number + SDADC_DC_LOOP_CTL_1_FUNC_LOCAL_RST_AN_DCLOOP_P_SHIFT));
        }
        else if (type == kSDADC_Channel_NSide_Type)
        {
            base->DC_LOOP_CTL_1 |= (0x1U << (number + SDADC_DC_LOOP_CTL_1_FUNC_LOCAL_RST_AN_DCLOOP_N_SHIFT));
        }
        else
        {
            base->DC_LOOP_CTL_1 |= ((0x1U << (number + SDADC_DC_LOOP_CTL_1_FUNC_LOCAL_RST_AN_DCLOOP_P_SHIFT)) |
                                    (0x1U << (number + SDADC_DC_LOOP_CTL_1_FUNC_LOCAL_RST_AN_DCLOOP_N_SHIFT)));
        }
    }
}
/*!
 * @}
 */

/*!
 * @name SDADC FIFO related operations.
 * @{
 */
/*!
 * @brief This function is used to enable or disable the global FIFO full interrupt.
 *
 * @param base SDADC peripheral base address.
 * @param enable Indicates whether enable or disable the global FIFO full interrupt.
 * - @b true Enable interrupt
 * - @b false Disable interrupt
 */
static inline void SDADC_ControlGlobalFifoIntEnable(SDADC_Type *base, bool enable)
{
    if (enable)
    {
        base->FIFO_INTERRUPT |= SDADC_FIFO_INTERRUPT_FIFO_INTERRUPT_EN_MASK;
    }
    else
    {
        base->FIFO_INTERRUPT &= ~SDADC_FIFO_INTERRUPT_FIFO_INTERRUPT_EN_MASK;
    }
}

/*!
 * @brief This function is used to check whether the FIFO full interrupt has occurred.
 *
 * @param base SDADC peripheral base address.
 *
 * @return The FIFO full interrupt status flag.
 * - @b true The FIFO full interrupt has occurred.
 * - @b false The FIFO full interrupt has not occurred.
 */
static inline bool SDADC_CheckGlobalFifoInterrupted(SDADC_Type *base)
{
    return (0UL != ((base->FIFO_INTERRUPT & SDADC_FIFO_INTERRUPT_FIFO_INTERRUPT_MASK) >>
                    SDADC_FIFO_INTERRUPT_FIFO_INTERRUPT_SHIFT));
}

/*!
 * @brief This function is used to clear the FIFO full interrupt status flag.
 *
 * @param base SDADC peripheral base address.
 */
static inline void SDADC_ClearGlobalFifoIntStatusFlag(SDADC_Type *base)
{
    base->FIFO_INTERRUPT |= SDADC_FIFO_INTERRUPT_FIFO_INTERRUPT_MASK;
}

/*!
 * @brief This function is used to enable or disable the FIFO full interrupt.
 *
 * @param base SDADC peripheral base address.
 * @param mask Mask value to enable or disable interrupt, please refer to @ref _sdadc_fifo_int_enable for details.
 * @param enable Indicates enable or disable the FIFO full interrupt.
 * - @b true Enable interrupt
 * - @b false Disable interrupt
 */
static inline void SDADC_ControlFifoIntEnable(SDADC_Type *base, uint32_t mask, bool enable)
{
    if (enable)
    {
        base->FIFO_WATERMARK_ERROR_CTL |= mask;
    }
    else
    {
        base->FIFO_WATERMARK_ERROR_CTL &= ~mask;
    }
}

/*!
 * @brief This function is used to enable or disable the FIFO watermark.
 *
 * @param base SDADC peripheral base address.
 * @param mask Mask value to enable or disable watermark, please refer to @ref _sdadc_fifo_watermark_enable for details.
 * @param enable Indicates enable or disable the FIFO watermark.
 * - @b true Enable watermark
 * - @b false Disable watermark
 */
static inline void SDADC_ControlFifoWatermarkEnable(SDADC_Type *base, uint32_t mask, bool enable)
{
    if (enable)
    {
        base->FIFO_WATERMARK_ERROR_CTL |= mask;
    }
    else
    {
        base->FIFO_WATERMARK_ERROR_CTL &= ~mask;
    }
}

/*!
 * @brief This function is used to get the FIFO full interrupt status flags.
 *
 * @param base SDADC peripheral base address.
 *
 * @return Status flags of the FIFO full interrupt.
 */
static inline uint8_t SDADC_GetFifoIntStatusFlags(SDADC_Type *base)
{
    return (uint8_t)((base->FIFO_WATERMARK_ERROR_ST & SDADC_FIFO_FULL_INT_STATUS_MASK) >>
                     SDADC_FIFO_FULL_INT_STATUS_SHIFT);
}

/*!
 * @brief This function is used to get the FIFO watermark status flags.
 *
 * @param base SDADC peripheral base address.
 *
 * @return Status flags of the FIFO watermark.
 */
static inline uint8_t SDADC_GetFifoWatermarkStatusFlags(SDADC_Type *base)
{
    return (uint8_t)((base->FIFO_WATERMARK_ERROR_ST & SDADC_FIFO_WATERMARK_STATUS_MASK) >>
                     SDADC_FIFO_WATERMARK_STATUS_SHIFT);
}

/*!
 * @brief This function is used to configure FIFO watermark.
 *
 * @param base SDADC peripheral base address.
 * @param number channel number, refer @ref sdadc_channel_number_t for details.
 * @param type channel type, refer @ref sdadc_channel_type_t for details.
 * @param waterMark WaterMark value, see @ref sdadc_watermark_t for details.
 */
static inline void SDADC_ConfigureFifoWatermark(SDADC_Type *base,
                                                sdadc_channel_number_t number,
                                                sdadc_channel_type_t type,
                                                sdadc_watermark_t waterMark)
{
    if (type == kSDADC_Channel_PSide_Type)
    {
        base->FIFO_WATERMARK_CTL = ((base->FIFO_WATERMARK_CTL & (~SDADC_FIFO_WATERMARK_CTL_P_MASK(number))) |
                                    SDADC_FIFO_WATERMARK_CTL_P(waterMark.pSideWatermark, number));
    }
    else if (type == kSDADC_Channel_NSide_Type)
    {
        base->FIFO_WATERMARK_CTL = ((base->FIFO_WATERMARK_CTL & (~SDADC_FIFO_WATERMARK_CTL_N_MASK(number))) |
                                    SDADC_FIFO_WATERMARK_CTL_N(waterMark.nSideWatermark, number));
    }
    else
    {
        base->FIFO_WATERMARK_CTL =
            ((base->FIFO_WATERMARK_CTL &
              (~(SDADC_FIFO_WATERMARK_CTL_P_MASK(number) | SDADC_FIFO_WATERMARK_CTL_N_MASK(number)))) |
             (SDADC_FIFO_WATERMARK_CTL_P(waterMark.pSideWatermark, number) |
              SDADC_FIFO_WATERMARK_CTL_N(waterMark.nSideWatermark, number)));
    }
}

/*!
 * @brief This function is used to reset the specific channel side FIFO's read or/and write pointer.
 *
 * @param base SDADC peripheral base address.
 * @param number channel number, refer @ref sdadc_channel_number_t for details.
 * @param type channel type, refer @ref sdadc_channel_type_t for details.
 * @param operation Indicates which reset operation to do, refer @ref sdadc_fifo_reset_operation_t for details.
 */
static inline void SDADC_ControlFifoReadWriteReset(SDADC_Type *base,
                                                   sdadc_channel_number_t number,
                                                   sdadc_channel_type_t type,
                                                   sdadc_fifo_reset_operation_t operation)
{
    if (type == kSDADC_Channel_PSide_Type)
    {
        base->FIFO_WR_RD_CTL |= (operation << ((number * 4U) + SDADC_FIFO_WR_RD_CTL_WR_0_P_RST_SHIFT));
    }
    else if (type == kSDADC_Channel_NSide_Type)
    {
        base->FIFO_WR_RD_CTL |= (operation << ((number * 4U) + SDADC_FIFO_WR_RD_CTL_WR_0_N_RST_SHIFT));
    }
    else
    {
        base->FIFO_WR_RD_CTL |= ((operation << ((number * 4U) + SDADC_FIFO_WR_RD_CTL_WR_0_P_RST_SHIFT)) |
                                 (operation << ((number * 4U) + SDADC_FIFO_WR_RD_CTL_WR_0_N_RST_SHIFT)));
    }
}

/*!
 * @brief This function is used to get the specific channel side FIFO's available entries.
 *
 * @note In the differential mode, the bit stream is converted to 24bit data (FIFO_x_P[23:0]) by the P-Side decimator,
 * the output of N-Side decimator (FIFO_x_N[23:0]) is not valid.
 *
 * @param base SDADC peripheral base address.
 * @param number channel number, refer @ref sdadc_channel_number_t for details.
 * @param type channel type, refer @ref sdadc_channel_type_t for details.
 *
 * @return The available entries of the specified FIFO, note that only the lower 5 bits of the returned data are valid.
 */
static inline uint8_t SDADC_GetConvChannelFifoAvailableEntries(SDADC_Type *base,
                                                               sdadc_channel_number_t number,
                                                               sdadc_channel_type_t type)
{
    uint8_t registerOffset = number / 2U;
    uint8_t bitfieldOffset = number % 2U * 16U;
    uint8_t temp           = 0U;

    if (type == kSDADC_Channel_PSide_Type)
    {
        temp =
            (((*((&(base->FIFO_ENTRIES_AVAIL_0)) + registerOffset)) >> bitfieldOffset) & SDADC_FIFO_ENTRIES_AVAIL_MASK);
    }
    else if (type == kSDADC_Channel_NSide_Type)
    {
        temp = (((*((&(base->FIFO_ENTRIES_AVAIL_0)) + registerOffset)) >> (bitfieldOffset + 8U)) &
                SDADC_FIFO_ENTRIES_AVAIL_MASK);
    }

    return temp;
}

/*!
 * @brief This function is used to get the specific channel side FIFO's raw data.
 *
 * @note In the differential mode, the bit stream is converted to 24bit data (FIFO_x_P[23:0]) by the P-Side decimator,
 * the output of N-Side decimator (FIFO_x_N[23:0]) is not valid. So the type that needs to be passed in in differential
 * mode is @ref kSDADC_Channel_PSide_Type.
 *
 * @param base SDADC peripheral base address.
 * @param number channel number, refer @ref sdadc_channel_number_t for details.
 * @param type channel type, refer @ref sdadc_channel_type_t for details.
 *
 * @return The raw data of the specified FIFO.
 */
static inline uint32_t SDADC_GetConvChannelFifoRawData(SDADC_Type *base,
                                                       sdadc_channel_number_t number,
                                                       sdadc_channel_type_t type)
{
    uint8_t offset = 0U;

    if (type == kSDADC_Channel_PSide_Type)
    {
        offset = number * 2U;
    }
    else if (type == kSDADC_Channel_NSide_Type)
    {
        offset = number * 2U + 1U;
    }
    else
    {
        assert(false);
    }

    return (((*((&(base->FIFO_0_P)) + offset)) & SDADC_FIFO_MASK) >> SDADC_FIFO_SHIFT);
}

/*!
 * @brief This function is used to copy specific conversion channels' data from FIFO to buffer.
 *
 * @note This function will copy all 16 entries in the specified FIFO.
 *
 * @param base SDADC peripheral base address.
 * @param group Indicates which group of channels data to obtain.
 * @param count Indicates how many channels in the specified group.
 * @param buffer The buffer which stores conversion data.
 */
void SDADC_CopyConvChannelFifoToBuffer(SDADC_Type *base, sdadc_channel_group *group, uint8_t count, void *buffer);
/*!
 * @}
 */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */

#endif /* FSL_SDADC_H_ */
