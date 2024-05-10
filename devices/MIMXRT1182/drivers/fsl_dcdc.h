/*
 * Copyright 2021-2022 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __FSL_DCDC_H__
#define __FSL_DCDC_H__

#include "fsl_common.h"

/*!
 * @addtogroup dcdc_soc
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief DCDC driver version. */
#define FSL_DCDC_DRIVER_VERSION (MAKE_VERSION(2, 0, 1)) /*!< Version 2.0.1. */

/*! @brief The array of VDD1P0 target voltage. */
#define VDD1P0_TARGET_VOLTAGE                                                                                         \
    {                                                                                                                 \
        600, 625, 650, 675, 700, 725, 750, 775, 800, 825, 850, 875, 900, 925, 950, 975, 1000, 1025, 1050, 1075, 1100, \
            1125, 1150, 1175, 1200, 1225, 1250, 1275, 1300, 1325, 1350, 1375                                          \
    }

/*! @brief The array of VDD1P8 target voltage. */
#define VDD1P8_TARGET_VOLTAGE                                                                                       \
    {                                                                                                               \
        1500, 1525, 1550, 1575, 1600, 1625, 1650, 1675, 1700, 1725, 1750, 1775, 1800, 1825, 1850, 1875, 1900, 1925, \
            1950, 1975, 2000, 2025, 2050, 2075, 2100, 2125, 2150, 2175, 2200, 2225, 2250, 2275                      \
    }

/*!
 * @brief The enumeration of DCDC status flags.
 */
enum _dcdc_status_flags
{
    kDCDC_AlreadySettledStatusFlag = DCDC_REG0_STS_DC_OK_MASK, /*!< Indicate DCDC status.
                                                            1'b1: DCDC already settled
                                                            1'b0: DCDC is settling. */
};

/*!
 * @brief CORE slice.
 */
typedef enum _dcdc_core_slice
{
    kDCDC_CORE0 = 0x0U, /*!< CORE slice 0. */
    kDCDC_CORE1 = 0x1U, /*!< CORE slice 1. */
} dcdc_core_slice_t;

/*!
 * @brief DCDC control mode, including software control mode and GPC control mode.
 */
typedef enum _dcdc_control_mode
{
    kDCDC_SoftwareControl = 0U, /*!< Controlled by software. */
    kDCDC_GPCControl      = 1U, /*!< Controlled by GPC. */
} dcdc_control_mode_t;

/*!
 * @brief DCDC trim input mode, including sample trim input and hold trim input.
 */
typedef enum _dcdc_trim_input_mode
{
    kDCDC_SampleTrimInput = 0U, /*!< Sample trim input. */
    kDCDC_HoldTrimInput   = 1U, /*!< Hold trim input. */
} dcdc_trim_input_mode_t;

/*!
 * @brief The enumeration VDD1P0's target voltage value.
 */
typedef enum _dcdc_1P0_target_vol
{
    kDCDC_1P0Target0P6V = 0U, /*!< The target voltage value of VDD1P0 is 0.6V. */
    kDCDC_1P0Target0P625V,    /*!< The target voltage value of VDD1P0 is 0.625V. */
    kDCDC_1P0Target0P65V,     /*!< The target voltage value of VDD1P0 is 0.65V. */
    kDCDC_1P0Target0P675V,    /*!< The target voltage value of VDD1P0 is 0.675V. */

    kDCDC_1P0Target0P7V,   /*!< The target voltage value of VDD1P0 is 0.7V. */
    kDCDC_1P0Target0P725V, /*!< The target voltage value of VDD1P0 is 0.725V. */
    kDCDC_1P0Target0P75V,  /*!< The target voltage value of VDD1P0 is 0.75V. */
    kDCDC_1P0Target0P775V, /*!< The target voltage value of VDD1P0 is 0.775V. */

    kDCDC_1P0Target0P8V,   /*!< The target voltage value of VDD1P0 is 0.8V. */
    kDCDC_1P0Target0P825V, /*!< The target voltage value of VDD1P0 is 0.825V. */
    kDCDC_1P0Target0P85V,  /*!< The target voltage value of VDD1P0 is 0.85V. */
    kDCDC_1P0Target0P875V, /*!< The target voltage value of VDD1P0 is 0.875V. */

    kDCDC_1P0Target0P9V,   /*!< The target voltage value of VDD1P0 is 0.9V. */
    kDCDC_1P0Target0P925V, /*!< The target voltage value of VDD1P0 is 0.925V. */
    kDCDC_1P0Target0P95V,  /*!< The target voltage value of VDD1P0 is 0.95V. */
    kDCDC_1P0Target0P975V, /*!< The target voltage value of VDD1P0 is 0.975V. */

    kDCDC_1P0Target1P0V,   /*!< The target voltage value of VDD1P0 is 1.0V. */
    kDCDC_1P0Target1P025V, /*!< The target voltage value of VDD1P0 is 1.025V. */
    kDCDC_1P0Target1P05V,  /*!< The target voltage value of VDD1P0 is 1.05V. */
    kDCDC_1P0Target1P075V, /*!< The target voltage value of VDD1P0 is 1.075V. */

    kDCDC_1P0Target1P1V,   /*!< The target voltage value of VDD1P0 is 1.1V. */
    kDCDC_1P0Target1P125V, /*!< The target voltage value of VDD1P0 is 1.125V. */
    kDCDC_1P0Target1P15V,  /*!< The target voltage value of VDD1P0 is 1.15V. */
    kDCDC_1P0Target1P175V, /*!< The target voltage value of VDD1P0 is 1.175V. */

    kDCDC_1P0Target1P2V,   /*!< The target voltage value of VDD1P0 is 1.2V. */
    kDCDC_1P0Target1P225V, /*!< The target voltage value of VDD1P0 is 1.225V. */
    kDCDC_1P0Target1P25V,  /*!< The target voltage value of VDD1P0 is 1.25V. */
    kDCDC_1P0Target1P275V, /*!< The target voltage value of VDD1P0 is 1.275V. */

    kDCDC_1P0Target1P3V,           /*!< The target voltage value of VDD1P0 is 1.3V. */
    kDCDC_1P0Target1P325V,         /*!< The target voltage value of VDD1P0 is 1.325V. */
    kDCDC_1P0Target1P35V,          /*!< The target voltage value of VDD1P0 is 1.35V. */
    kDCDC_1P0Target1P375V = 0x1FU, /*!< The target voltage value of VDD1P0 is 1.375V. */
} dcdc_1P0_target_vol_t;

/*!
 * @brief The enumeration VDD1P8's target voltage value.
 */
typedef enum _dcdc_1P8_target_vol
{
    kDCDC_1P8Target1P5V = 0U, /*!< The target voltage value of VDD1P8 is 1.5V. */
    kDCDC_1P8Target1P525V,    /*!< The target voltage value of VDD1P8 is 1.525V. */
    kDCDC_1P8Target1P55V,     /*!< The target voltage value of VDD1P8 is 1.55V. */
    kDCDC_1P8Target1P575V,    /*!< The target voltage value of VDD1P8 is 1.575V. */

    kDCDC_1P8Target1P6V,   /*!< The target voltage value of VDD1P8 is 1.6V. */
    kDCDC_1P8Target1P625V, /*!< The target voltage value of VDD1P8 is 1.625V. */
    kDCDC_1P8Target1P65V,  /*!< The target voltage value of VDD1P8 is 1.65V. */
    kDCDC_1P8Target1P675V, /*!< The target voltage value of VDD1P8 is 1.675V. */

    kDCDC_1P8Target1P7V,   /*!< The target voltage value of VDD1P8 is 1.7V. */
    kDCDC_1P8Target1P725V, /*!< The target voltage value of VDD1P8 is 1.725V. */
    kDCDC_1P8Target1P75V,  /*!< The target voltage value of VDD1P8 is 1.75V. */
    kDCDC_1P8Target1P775V, /*!< The target voltage value of VDD1P8 is 1.775V. */

    kDCDC_1P8Target1P8V,   /*!< The target voltage value of VDD1P8 is 1.8V. */
    kDCDC_1P8Target1P825V, /*!< The target voltage value of VDD1P8 is 1.825V. */
    kDCDC_1P8Target1P85V,  /*!< The target voltage value of VDD1P8 is 1.85V. */
    kDCDC_1P8Target1P875V, /*!< The target voltage value of VDD1P8 is 1.875V. */

    kDCDC_1P8Target1P9V,   /*!< The target voltage value of VDD1P8 is 1.9V. */
    kDCDC_1P8Target1P925V, /*!< The target voltage value of VDD1P8 is 1.925V. */
    kDCDC_1P8Target1P95V,  /*!< The target voltage value of VDD1P8 is 1.95V. */
    kDCDC_1P8Target1P975V, /*!< The target voltage value of VDD1P8 is 1.975V. */

    kDCDC_1P8Target2P0V,   /*!< The target voltage value of VDD1P8 is 2.0V. */
    kDCDC_1P8Target2P025V, /*!< The target voltage value of VDD1P8 is 2.025V. */
    kDCDC_1P8Target2P05V,  /*!< The target voltage value of VDD1P8 is 2.05V. */
    kDCDC_1P8Target2P075V, /*!< The target voltage value of VDD1P8 is 2.075V. */

    kDCDC_1P8Target2P1V,   /*!< The target voltage value of VDD1P8 is 2.1V. */
    kDCDC_1P8Target2P125V, /*!< The target voltage value of VDD1P8 is 2.125V. */
    kDCDC_1P8Target2P15V,  /*!< The target voltage value of VDD1P8 is 2.15V. */
    kDCDC_1P8Target2P175V, /*!< The target voltage value of VDD1P8 is 2.175V. */

    kDCDC_1P8Target2P2V,           /*!< The target voltage value of VDD1P8 is 2.2V. */
    kDCDC_1P8Target2P225V,         /*!< The target voltage value of VDD1P8 is 2.225V. */
    kDCDC_1P8Target2P25V,          /*!< The target voltage value of VDD1P8 is 2.25V. */
    kDCDC_1P8Target2P275V = 0x1FU, /*!< The target voltage value of VDD1P8 is 2.275V. */
} dcdc_1P8_target_vol_t;

/*!
 * @brief The current bias of low power comparator.
 */
typedef enum _dcdc_comparator_current_bias
{
    kDCDC_ComparatorCurrentBias50nA  = 0U, /*!< The current bias of low power comparator is 50nA. */
    kDCDC_ComparatorCurrentBias100nA = 1U, /*!< The current bias of low power comparator is 100nA. */
    kDCDC_ComparatorCurrentBias200nA = 2U, /*!< The current bias of low power comparator is 200nA. */
    kDCDC_ComparatorCurrentBias400nA = 3U, /*!< The current bias of low power comparator is 400nA. */
} dcdc_comparator_current_bias_t;

/*!
 * @brief The threshold if peak current detection.
 */
typedef enum _dcdc_peak_current_threshold
{
    kDCDC_PeakCurrentRunMode250mALPMode1P5A = 0U, /*!< Over peak current threshold in low power mode is 250mA,
                                                      in run mode is 1.5A */
    kDCDC_PeakCurrentRunMode200mALPMode1P5A,      /*!< Over peak current threshold in low power mode is 200mA,
                                                           in run mode is 1.5A */
    kDCDC_PeakCurrentRunMode250mALPMode2A,        /*!< Over peak current threshold in low power mode is 250mA,
                                                             in run mode is 2A */
    kDCDC_PeakCurrentRunMode200mALPMode2A,        /*!< Over peak current threshold in low power mode is 200mA,
                                                             in run mode is 2A */
} dcdc_peak_current_threshold_t;

/*!
 * @brief Oscillator clock option.
 */
typedef enum _dcdc_clock_source
{
    kDCDC_ClockAutoSwitch  = 0U, /*!< Automatic clock switch from internal oscillator to external clock. */
    kDCDC_ClockInternalOsc = 1U, /*!< Use internal oscillator. */
    kDCDC_ClockExternalOsc = 2U, /*!< Use external 24M crystal oscillator. */
} dcdc_clock_source_t;

/*!
 * @brief Voltage output option.
 */
typedef enum _dcdc_voltage_output_sel
{
    kDCDC_VoltageOutput1P8 = 0U, /*!< 1.8V output. */
    kDCDC_VoltageOutput1P0 = 1U, /*!< 1.0V output. */
} dcdc_voltage_output_sel_t;

/*!
 * @brief Configuration for DCDC.
 */
typedef struct _dcdc_config
{
    dcdc_control_mode_t controlMode;      /*!< DCDC control mode. */
    dcdc_trim_input_mode_t trimInputMode; /*!< Hold trim input. */
} dcdc_config_t;

/*!
 * @brief Configuration for min power setting.
 */
typedef struct _dcdc_min_power_config
{
    bool enableUseHalfFreqForContinuous; /*!< Set DCDC clock to half frequency for the continuous mode. */
} dcdc_min_power_config_t;

/*!
 * @brief Configuration for DCDC detection.
 */
typedef struct _dcdc_detection_config
{
    bool enableXtalokDetection;               /*!< Enable xtalok detection circuit. */
    bool powerDownOverVoltageVdd1P8Detection; /*!< Power down over-voltage detection comparator for VDD1P8. */
    bool powerDownOverVoltageVdd1P0Detection; /*!< Power down over-voltage detection comparator for VDD1P0. */
    bool powerDownLowVoltageDetection;        /*!< Power down low-voltage detection comparator. */
    bool powerDownOverCurrentDetection;       /*!< Power down over-current detection. */
} dcdc_detection_config_t;

/*!
 * @brief Configuration for the loop control.
 */
typedef struct _dcdc_loop_control_config
{
    bool enableCommonHysteresis;         /*!< Enable hysteresis in switching converter common mode analog comparators.
                                              This feature will improve transient supply ripple and efficiency. */
    bool enableCommonThresholdDetection; /*!< Increase the threshold detection for common mode analog comparator. */
    bool enableDifferentialHysteresis;   /*!< Enable hysteresis in switching converter differential mode analog
                                              comparators. This feature will improve transient supply ripple and
                                              efficiency. */
    bool enableDifferentialThresholdDetection; /*!< Increase the threshold detection for differential mode analog
                                                    comparators. */
    bool enableInvertHysteresisSign;           /*!< Invert the sign of the hysteresis in DC-DC analog comparators. */
    bool enableRCThresholdDetection;           /*!< Increase the threshold detection for RC scale circuit. */
    uint32_t enableRCScaleCircuit;      /*!< Available range is 0~7. Enable analog circuit of DC-DC converter to respond
                                             faster under transient load conditions. */
    uint32_t complementFeedForwardStep; /*!< Available range is 0~7. Two's complement feed forward step in duty cycle in
                                           the switching DC-DC converter. Each time this field makes a transition from
                                           0x0, the loop filter of the DC-DC converter is stepped once by a value
                                           proportional to the change. This can be used to force a certain control loop
                                           behavior, such as improving response under known heavy load transients. */
    uint32_t controlParameterMagnitude; /*!< Available range is 0~15. Magnitude of proportional control parameter in the
                                           switching DC-DC converter control loop. */
    uint32_t integralProportionalRatio; /*!< Available range is 0~3.Ratio of integral control parameter to proportional
                                           control parameter in the switching DC-DC converter, and can be used to
                                           optimize efficiency and loop response. */
} dcdc_loop_control_config_t;

/*!
 * @brief Configuration for DCDC internal regulator.
 */
typedef struct _dcdc_internal_regulator_config
{
    uint32_t feedbackPoint; /*!< Available range is 0~3. Select the feedback point of the internal regulator. */
} dcdc_internal_regulator_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @name Initialization and De-initialization Interfaces
 * @{
 */

/*!
 * @brief Initializes the basic resource of DCDC module, such as control mode, etc.
 *
 * @param base DCDC peripheral base address.
 * @param config Pointer to the @ref dcdc_config_t structure.
 */
void DCDC_Init(DCDC_Type *base, const dcdc_config_t *config);

/*!
 * @brief De-initializes the DCDC module.
 *
 * @param base DCDC peripheral base address.
 */
void DCDC_Deinit(DCDC_Type *base);

/*!
 * @brief Gets the default setting for DCDC, such as control mode, etc.
 *
 * This function initializes the user configuration structure to a default value. The default values are:
 * @code
 *   config->controlMode                    = kDCDC_StaticControl;
 *   config->trimInputMode                  = kDCDC_SampleTrimInput;
 *   config->enableDcdcTimeout              = false;
 *   config->enableSwitchingConverterOutput = false;
 * @endcode
 *
 * @param config Pointer to configuration structure. See to @ref dcdc_config_t.
 */
void DCDC_GetDefaultConfig(dcdc_config_t *config);

/*! @} */

/*!
 * @name Power Mode Related Interfaces
 * @{
 */

/*! @} */

/*!
 * @name Outputs' Target Voltage Related Interfaces
 * @{
 */

static inline void DCDC_SetVDD1P0LowPowerModeTargetVoltage(DCDC_Type *base,
                                                           dcdc_core_slice_t core,
                                                           dcdc_1P0_target_vol_t targetVoltage)
{
    base->REG3 &= ~DCDC_REG3_VDD1P0CTRL_DISABLE_STEP_MASK;

    if (core == kDCDC_CORE0)
    {
        base->TRG_SW_0 = ((base->TRG_SW_0) & (~DCDC_TRG_SW_0_VDD1P0CTRL_LP_TRG_MASK)) |
                         DCDC_TRG_SW_0_VDD1P0CTRL_LP_TRG(targetVoltage);
    }
    else if (core == kDCDC_CORE1)
    {
        base->TRG_SW_1 = ((base->TRG_SW_1) & (~DCDC_TRG_SW_1_VDD1P0CTRL_LP_TRG_MASK)) |
                         DCDC_TRG_SW_1_VDD1P0CTRL_LP_TRG(targetVoltage);
    }
    else
    {
        assert(0);
    }

    while (DCDC_REG0_STS_DC_OK_MASK != (DCDC_REG0_STS_DC_OK_MASK & base->REG0))
    {
    }
}

/*!
 * @brief Gets the target value of VDD1P0 in low power mode, the result takes "mV" as the unit.
 *
 * @param base DCDC peripheral base address.
 *
 * @return The VDD1P0's voltage value in low power mode and the unit is "mV".
 */
static inline uint16_t DCDC_GetVDD1P0LowPowerModeTargetVoltage(DCDC_Type *base)
{
    const uint16_t vdd1P0TargetVoltage[] = VDD1P0_TARGET_VOLTAGE;
    uint32_t voltageValue =
        (base->CURRENT_TRG & DCDC_CURRENT_TRG_VDD1P0CTRL_LP_TRG_MASK) >> DCDC_CURRENT_TRG_VDD1P0CTRL_LP_TRG_SHIFT;

    return vdd1P0TargetVoltage[voltageValue];
}

static inline void DCDC_EnableVDD1P0LowPowerMode(DCDC_Type *base, dcdc_core_slice_t core, bool enable)
{
    if (core == kDCDC_CORE0)
    {
        base->TRG_SW_0 = ((base->TRG_SW_0) & (~DCDC_TRG_SW_0_LP_EN_1P0_MASK)) | DCDC_TRG_SW_0_LP_EN_1P0(enable);
    }
    else if (core == kDCDC_CORE1)
    {
        base->TRG_SW_1 = ((base->TRG_SW_1) & (~DCDC_TRG_SW_1_LP_EN_1P0_MASK)) | DCDC_TRG_SW_1_LP_EN_1P0(enable);
    }
    else
    {
        assert(0);
    }
}

/*!
 * @brief Sets the target value(ranges from 0.6V to 1.375V) of VDD1P0 in buck mode, 25mV each step.
 *
 * @param base DCDC peripheral base address.
 * @param core Core for DCDC to control.
 * @param targetVoltage The target value of VDD1P0 in buck mode, see @ref dcdc_1P0_target_vol_t.
 */
static inline void DCDC_SetVDD1P0BuckModeTargetVoltage(DCDC_Type *base,
                                                       dcdc_core_slice_t core,
                                                       dcdc_1P0_target_vol_t targetVoltage)
{
    base->REG3 &= ~DCDC_REG3_VDD1P0CTRL_DISABLE_STEP_MASK;

    if (core == kDCDC_CORE0)
    {
        base->TRG_SW_0 =
            ((base->TRG_SW_0) & (~DCDC_TRG_SW_0_VDD1P0CTRL_TRG_MASK)) | DCDC_TRG_SW_0_VDD1P0CTRL_TRG(targetVoltage);
    }
    else if (core == kDCDC_CORE1)
    {
        base->TRG_SW_1 =
            ((base->TRG_SW_1) & (~DCDC_TRG_SW_1_VDD1P0CTRL_TRG_MASK)) | DCDC_TRG_SW_1_VDD1P0CTRL_TRG(targetVoltage);
    }
    else
    {
        assert(0);
    }

    while (DCDC_REG0_STS_DC_OK_MASK != (DCDC_REG0_STS_DC_OK_MASK & base->REG0))
    {
    }
}

/*!
 * @brief Gets the target value of VDD1P0 in buck mode, the result takes "mV" as the unit.
 *
 * @param base DCDC peripheral base address.
 *
 * @return The VDD1P0's voltage value in buck mode and the unit is "mV".
 */
static inline uint16_t DCDC_GetVDD1P0BuckModeTargetVoltage(DCDC_Type *base)
{
    const uint16_t vdd1P0TargetVoltage[] = VDD1P0_TARGET_VOLTAGE;
    uint32_t voltageValue =
        (base->CURRENT_TRG & DCDC_CURRENT_TRG_VDD1P0CTRL_TRG_MASK) >> DCDC_CURRENT_TRG_VDD1P0CTRL_TRG_SHIFT;

    return vdd1P0TargetVoltage[voltageValue];
}

static inline void DCDC_GPC_SetVDD1P0BuckModeTargetVoltage(DCDC_Type *base,
                                                           dcdc_core_slice_t core,
                                                           dcdc_1P0_target_vol_t targetVoltage)
{
    if (core == kDCDC_CORE0)
    {
        base->TRG_GPC_0 =
            ((base->TRG_GPC_0) & (~DCDC_TRG_GPC_0_VDD1P0CTRL_TRG_MASK)) | DCDC_TRG_GPC_0_VDD1P0CTRL_TRG(targetVoltage);
    }
    else if (core == kDCDC_CORE1)
    {
        base->TRG_GPC_1 =
            ((base->TRG_GPC_1) & (~DCDC_TRG_GPC_1_VDD1P0CTRL_TRG_MASK)) | DCDC_TRG_GPC_1_VDD1P0CTRL_TRG(targetVoltage);
    }
    else
    {
        assert(0);
    }
}

/*!
 * @brief Sets the target value(ranges from 0.625V to 1.4V) of VDD1P0 in low power mode, 25mV each step.
 *
 * @param base DCDC peripheral base address.
 * @param core Core for DCDC to control.
 * @param targetVoltage The target value of VDD1P0 in low power mode, see @ref dcdc_1P0_target_vol_t.
 */
static inline void DCDC_GPC_SetVDD1P0LowPowerModeTargetVoltage(DCDC_Type *base,
                                                               dcdc_core_slice_t core,
                                                               dcdc_1P0_target_vol_t targetVoltage)
{
    if (core == kDCDC_CORE0)
    {
        base->TRG_GPC_0 = ((base->TRG_GPC_0) & (~DCDC_TRG_GPC_0_VDD1P0CTRL_LP_TRG_MASK)) |
                          DCDC_TRG_GPC_0_VDD1P0CTRL_LP_TRG(targetVoltage);
    }
    else if (core == kDCDC_CORE1)
    {
        base->TRG_GPC_1 = ((base->TRG_GPC_1) & (~DCDC_TRG_GPC_1_VDD1P0CTRL_LP_TRG_MASK)) |
                          DCDC_TRG_GPC_1_VDD1P0CTRL_LP_TRG(targetVoltage);
    }
    else
    {
        assert(0);
    }
}

/*!
 * @brief Enable VDD1P0 in low power mode.
 *
 * @param base DCDC peripheral base address.
 * @param core Core for DCDC to control.
 * @param enable Enable the output or not.
 */
static inline void DCDC_GPC_EnableVDD1P0LowPowerMode(DCDC_Type *base, dcdc_core_slice_t core, bool enable)
{
    if (core == kDCDC_CORE0)
    {
        base->TRG_GPC_0 = ((base->TRG_GPC_0) & (~DCDC_TRG_GPC_0_LP_EN_1P0_MASK)) | DCDC_TRG_GPC_0_LP_EN_1P0(enable);
    }
    else if (core == kDCDC_CORE1)
    {
        base->TRG_GPC_1 = ((base->TRG_GPC_1) & (~DCDC_TRG_GPC_1_LP_EN_1P0_MASK)) | DCDC_TRG_GPC_1_LP_EN_1P0(enable);
    }
    else
    {
        assert(0);
    }
}

/*!
 * @brief Sets the target value(ranges from 1.5V to 2.275V) of VDD1P8, 25mV each step.
 *
 * @param base DCDC peripheral base address.
 * @param core Core for DCDC to control.
 * @param targetVoltage The target value of VDD1P8, see @ref dcdc_1P8_target_vol_t.
 */
static inline void DCDC_SetVDD1P8TargetVoltage(DCDC_Type *base,
                                               dcdc_core_slice_t core,
                                               dcdc_1P8_target_vol_t targetVoltage)
{
    if (core == kDCDC_CORE0)
    {
        base->TRG_SW_0 =
            ((base->TRG_SW_0) & (~DCDC_TRG_SW_0_VDD1P8CTRL_TRG_MASK)) | DCDC_TRG_SW_0_VDD1P8CTRL_TRG(targetVoltage);
    }
    else if (core == kDCDC_CORE1)
    {
        base->TRG_SW_1 =
            ((base->TRG_SW_1) & (~DCDC_TRG_SW_1_VDD1P8CTRL_TRG_MASK)) | DCDC_TRG_SW_1_VDD1P8CTRL_TRG(targetVoltage);
    }
    else
    {
        assert(0);
    }

    while (DCDC_REG0_STS_DC_OK_MASK != (DCDC_REG0_STS_DC_OK_MASK & base->REG0))
    {
    }
}

/*!
 * @brief Gets the target value of VDD1P8, the result takes "mV" as the unit.
 *
 * @param base DCDC peripheral base address.
 *
 * @return The VDD1P8's voltage value and the unit is "mV".
 */
static inline uint16_t DCDC_GetVDD1P8TargetVoltage(DCDC_Type *base)
{
    const uint16_t vdd1P8TargetVoltage[] = VDD1P8_TARGET_VOLTAGE;
    uint32_t voltageValue =
        (base->CURRENT_TRG & DCDC_CURRENT_TRG_VDD1P8CTRL_TRG_MASK) >> DCDC_CURRENT_TRG_VDD1P8CTRL_TRG_SHIFT;

    return vdd1P8TargetVoltage[voltageValue];
}

/*!
 * @brief Enables/Disables stepping for VDD1P0, before entering low power modes the stepping for VDD1P0 must be
 * disabled.
 *
 * @param base DCDC peripheral base address.
 * @param enable Used to control the behavior.
 *            - \b true Enables stepping for VDD1P0.
 *            - \b false Disables stepping for VDD1P0.
 */
static inline void DCDC_EnableVDD1P0TargetVoltageStepping(DCDC_Type *base, bool enable)
{
    if (enable)
    {
        base->REG3 &= ~DCDC_REG3_VDD1P0CTRL_DISABLE_STEP_MASK;
    }
    else
    {
        base->REG3 |= DCDC_REG3_VDD1P0CTRL_DISABLE_STEP_MASK;
    }
}

/*! @} */

/*!
 * @name Detection Related Inferfaces
 * @{
 */

/*!
 * @brief Gets the default setting for detection configuration.
 *
 * The default configuration are set according to responding registers' setting when powered on.
 * They are:
 * @code
 *   config->enableXtalokDetection = false;
 *   config->powerDownOverVoltageVdd1P8Detection = true;
 *   config->powerDownOverVoltageVdd1P0Detection = true;
 *   config->powerDownLowVoltageDetection  = false;
 *   config->powerDownOverCurrentDetection = true;
 *   config->powerDownPeakCurrentDetection = true;
 *   config->powerDownZeroCrossDetection   = true;
 *   config->OverCurrentThreshold          = kDCDC_OverCurrentThresholdAlt0;
 *   config->PeakCurrentThreshold          = kDCDC_PeakCurrentThresholdAlt0;
 * @endcode
 *
 * @param config Pointer to configuration structure. See to @ref dcdc_detection_config_t.
 */
void DCDC_GetDefaultDetectionConfig(dcdc_detection_config_t *config);

/*!
 * @brief Configures the DCDC detection.
 *
 * @param base DCDC peripheral base address.
 * @param config Pointer to configuration structure. See to @ref dcdc_detection_config_t.
 */
void DCDC_SetDetectionConfig(DCDC_Type *base, const dcdc_detection_config_t *config);

/*! @} */

/*!
 * @name DCDC Miscellaneous Inferfaces
 * @{
 */

/*!
 * @brief Configures the DCDC clock source.
 *
 * @param base DCDC peripheral base address.
 * @param clockSource Clock source for DCDC. See to @ref dcdc_clock_source_t.
 */
void DCDC_SetClockSource(DCDC_Type *base, dcdc_clock_source_t clockSource);

/*!
 * @brief Sets the bangap trim value(0~31) to trim bandgap voltage.
 *
 * @param base DCDC peripheral base address.
 * @param trimValue The bangap trim value. Available range is 0U-31U.
 */
static inline void DCDC_SetBandgapVoltageTrimValue(DCDC_Type *base, uint32_t trimValue)
{
    base->REG1 &= ~DCDC_REG1_VBG_TRIM_MASK;
    base->REG1 |= DCDC_REG1_VBG_TRIM(trimValue);
}

/*!
 * @brief Gets the default setting for loop control configuration.
 *
 * The default configuration are set according to responding registers' setting when powered on.
 * They are:
 * @code
 *   config->enableCommonHysteresis = false;
 *   config->enableCommonThresholdDetection = false;
 *   config->enableInvertHysteresisSign = false;
 *   config->enableRCThresholdDetection = false;
 *   config->enableRCScaleCircuit = 0U;
 *   config->complementFeedForwardStep = 0U;
 *   config->controlParameterMagnitude = 2U;
 *   config->integralProportionalRatio = 2U;
 * @endcode
 *
 * @param config Pointer to configuration structure. See to @ref dcdc_loop_control_config_t.
 */
void DCDC_GetDefaultLoopControlConfig(dcdc_loop_control_config_t *config);

/*!
 * @brief Configures the DCDC loop control.
 *
 * @param base DCDC peripheral base address.
 * @param config Pointer to configuration structure. See to @ref dcdc_loop_control_config_t.
 */
void DCDC_SetLoopControlConfig(DCDC_Type *base, const dcdc_loop_control_config_t *config);

/*!
 * @brief Configures the DCDC internal regulator.
 *
 * @param base DCDC peripheral base address.
 * @param config Pointer to configuration structure. See to @ref dcdc_internal_regulator_config_t.
 */
void DCDC_SetInternalRegulatorConfig(DCDC_Type *base, const dcdc_internal_regulator_config_t *config);

/*!
 * @brief Adjusts delay to reduce ground noise.
 *
 * @param base DCDC peripheral base address.
 * @param enable Enable the feature or not.
 */
static inline void DCDC_EnableAdjustDelay(DCDC_Type *base, bool enable)
{
    if (enable)
    {
        base->REG3 |= DCDC_REG3_MISC_DELAY_TIMING_MASK;
    }
    else
    {
        base->REG3 &= ~DCDC_REG3_MISC_DELAY_TIMING_MASK;
    }
}

/*! @} */

/*!
 * @name DCDC Status Related Interfaces
 * @{
 */

/*!
 * @brief Get DCDC status flags.
 *
 * @param base peripheral base address.
 * @return Mask of asserted status flags. See to @ref _dcdc_status_flags.
 */
static inline uint32_t DCDC_GetStatusFlags(DCDC_Type *base)
{
    return (base->REG0 & DCDC_REG0_STS_DC_OK_MASK);
}

/* @} */

/*!
 * @name Application Guideline Interfaces
 * @{
 */

/*!
 * @brief Boots DCDC into CCM(continous conduction mode).
 *
 * @code
 *  pwd_zcd=0x1;
 *  pwd_cmp_offset=0x0;
 *  dcdc_loopctrl_en_rcscale=0x3;
 * @endcode
 *
 * @param base DCDC peripheral base address.
 */
void DCDC_BootIntoCCM(DCDC_Type *base);

/*! @} */

/*!
 * @}
 */

#endif /* __FSL_DCDC_H__ */
