/*
 * Copyright 2021 ~ 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_PF5020_H_
#define _FSL_PF5020_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define PF5020_DEVICE_ID       0x00U
#define PF5020_REV_ID          0x01U
#define PF5020_EMREV           0x02U
#define PF5020_PROG_ID         0x03U
#define PF5020_INT_STATUS1     0x04U
#define PF5020_INT_MASK1       0x05U
#define PF5020_INT_SENSE1      0x06U
#define PF5020_INT_STATUS2     0x07U
#define PF5020_INT_MASK2       0x08U
#define PF5020_INT_SENSE2      0x09U
#define PF5020_SW_MODE_INT     0x0AU
#define PF5020_SW_MODE_MASK    0x0BU
#define PF5020_SW_ILIM_INT     0x0CU
#define PF5020_SW_ILIM_MASK    0x0DU
#define PF5020_SW_ILIM_SENSE   0x0EU
#define PF5020_LDO_ILIM_INT    0x0FU
#define PF5020_LDO_ILIM_MASK   0x10U
#define PF5020_LDO_ILIM_SENSE  0x11U
#define PF5020_SW_UV_INT       0x12U
#define PF5020_SW_UV_MASK      0x13U
#define PF5020_SW_UV_SENSE     0x14U
#define PF5020_SW_OV_INT       0x15U
#define PF5020_SW_OV_MASK      0x16U
#define PF5020_SW_OV_SENSE     0x17U
#define PF5020_LDO_UV_INT      0x18U
#define PF5020_LDO_UV_MASK     0x19U
#define PF5020_LDO_UV_SENSE    0x1AU
#define PF5020_LDO_OV_INT      0x1BU
#define PF5020_LDO_OV_MASK     0x1CU
#define PF5020_LDO_OV_SENSE    0x1DU
#define PF5020_PWRON_INT       0x1EU
#define PF5020_PWRON_MASK      0x1FU
#define PF5020_PWRON_SENSE     0x20U
#define PF5020_EN_SENSE        0x21U
#define PF5020_SYS_INT         0x22U
#define PF5020_HARDFAULT_FLAGS 0x23U

#define PF5020_ABIST_PGOOD_MON 0x25U
#define PF5020_ABIST_OV1       0x26U
#define PF5020_ABIST_OV2       0x27U
#define PF5020_ABIST_UV1       0x28U
#define PF5020_ABIST_UV2       0x29U
#define PF5020_TEST_FLAGS      0x2AU
#define PF5020_ABIST_RUN       0x2BU

#define PF5020_RANDOM_GEN 0x2DU
#define PF5020_RANDOM_CHK 0x2EU
#define PF5020_VMONEN1    0x2FU
#define PF5020_VMONEN2    0x30U
#define PF5020_CTRL1      0x31U
#define PF5020_CTRL2      0x32U
#define PF5020_CTRL3      0x33U
#define PF5020_PWRUP_CTRL 0x34U

#define PF5020_RESETBMCU_PWRUP 0x36U
#define PF5020_PGOOD_PWRUP     0x37U
#define PF5020_PWRDN_DLY1      0x38U
#define PF5020_PWRDN_DLY2      0x39U
#define PF5020_FREQ_CTRL       0x3AU

#define PF5020_PWRON         0x3CU
#define PF5020_WD_CONFIG     0x3DU
#define PF5020_WD_CLEAR      0x3EU
#define PF5020_WD_EXPIRE     0x3FU
#define PF5020_WD_COUNTER    0x40U
#define PF5020_FAULT_COUNTER 0x41U
#define PF5020_FSAFE_COUNTER 0x42U
#define PF5020_FAULT_TIMERS  0x43U
#define PF5020_AMUX          0x44U

#define PF5020_SW_RAMP       0x46U
#define PF5020_SW1_CONFIG1   0x47U
#define PF5020_SW1_CONFIG2   0x48U
#define PF5020_SW1_PWRUP     0x49U
#define PF5020_SW1_MODE      0x4AU
#define PF5020_SW1_RUN_VOLT  0x4BU
#define PF5020_SW1_STBY_VOLT 0x4CU

#define PF5020_SW2_CONFIG1   0x4FU
#define PF5020_SW2_CONFIG2   0x50U
#define PF5020_SW2_PWRUP     0x51U
#define PF5020_SW2_MODE1     0x52U
#define PF5020_SW2_RUN_VOLT  0x53U
#define PF5020_SW2_STBY_VOLT 0x54U

#define PF5020_SWND1_CONFIG1  0x67U
#define PF5020_SWND1_CONFIG2  0x68U
#define PF5020_SWND1_PWRUP    0x69U
#define PF5020_SWND1_MODE1    0x6AU
#define PF5020_SWND1_RUN_VOLT 0x6BU

#define PF5020_LDO1_CONFIG1   0x6EU
#define PF5020_LDO1_CONFIG2   0x6FU
#define PF5020_LDO1_PWRUP     0x70U
#define PF5020_LDO1_RUN_VOLT  0x71U
#define PF5020_LDO1_STBY_VOLT 0x72U

#define PF5020_VSNVS_CONFIG1 0x75U

#define PF5020_PAGE_SELECT 0x77U

#define PF5020_INT_MASK_ARRAY                                                                            \
    {                                                                                                    \
        PF5020_INT_MASK1, PF5020_INT_MASK2, PF5020_SW_MODE_MASK, PF5020_SW_ILIM_MASK, PF5020_SW_UV_MASK, \
            PF5020_SW_OV_MASK, PF5020_PWRON_MASK                                                         \
    }
#define PF5020_INT_LATCH_ARRAY                                                                            \
    {                                                                                                     \
        PF5020_INT_STATUS1, PF5020_INT_STATUS2, PF5020_SW_MODE_INT, PF5020_SW_ILIM_INT, PF5020_SW_UV_INT, \
            PF5020_SW_OV_INT, PF5020_PWRON_INT                                                            \
    }

#define PF5020_SEQ_REG_ARRAY                                                                                \
    {                                                                                                       \
        PF5020_RESETBMCU_PWRUP, PF5020_PGOOD_PWRUP, PF5020_SW1_PWRUP, PF5020_SW2_PWRUP, PF5020_SWND1_PWRUP, \
            PF5020_LDO1_PWRUP                                                                               \
    }

/*!
 * @brief The enumeration of internal high speed clock frequency.
 */
typedef enum _pf5020_high_speed_clk_freq
{
    kPF5020_HighSpeedClkFreq20MHz = 0x0U, /*!< High speed clock frequency is 20MHz,
                                              switching regulator frequency is 2.5MHz. */
    kPF5020_HighSpeedClkFreq21MHz = 0x1U, /*!< High speed clock frequency is 21MHz,
                                              switching regulator frequency is 2.625MHz. */
    kPF5020_HighSpeedClkFreq22MHz = 0x2U, /*!< High speed clock frequency is 22MHz,
                                              switching regulator frequency is 2.750MHz. */
    kPF5020_HighSpeedClkFreq23MHz = 0x3U, /*!< High speed clock frequency is 23MHz,
                                              switching regulator frequency is 2.875MHz. */
    kPF5020_HighSpeedClkFreq24MHz = 0x4U, /*!< High speed clock frequency is 24MHz,
                                              switching regulator frequency is 3.0MHz. */
    kPF5020_HighSpeedClkFreq16MHz = 0x9U, /*!< High speed clock frequency is 16MHz,
                                              switching regulator frequency is 2.0MHz. */
    kPF5020_HighSpeedClkFreq17MHz = 0xAU, /*!< High speed clock frequency is 17MHz,
                                              switching regulator frequency is 2.125MHz. */
    kPF5020_HighSpeedClkFreq18MHz = 0xBU, /*!< High speed clock frequency is 18MHz,
                                              switching regulator frequency is 2.25MHz. */
    kPF5020_HighSpeedClkFreq19MHz = 0xCU, /*!< High speed clock frequency is 19MHz,
                                              switching regulator frequency is 2.375MHz. */
} pf5020_high_speed_clk_freq_t;

/*!
 * @brief The enumeration of internal high speed clock frequency range.
 *
 */
typedef enum _pf5020_high_speed_clk_ss_range
{
    kPF5020_HighSpeedClkSSRange0 = 0U, /*!< The maximum clock frequency range is +5%/-5%. */
    kPF5020_HighSpeedClkSSRange1 = 1U, /*!< The maximum clock frequency range is +10%/-10%.  */
} pf5020_high_speed_clk_ss_range_t;

/*!
 * @brief The enumeration of VSNVS LDO output voltage, 0 means turn off VSNVS LDO.
 */
typedef enum _pf5020_vsnvs_ldo_output_voltage
{
    kPF5020_VsnvsLdoOff = 0U,   /*!< Turn off VSNVS LDO. */
    kPF5020_VsnvsLdoOutput1P8V, /*!< Vsnvs LDO output 1.8V. */
    kPF5020_VsnsLdoOutput3P0V,  /*!< Vsnvs LDO output 3.0V. */
    kPF5020_VsnsLdoOutput3P3V,  /*!< Vsnvs LDO output 3.3V. */
} pf5020_vsnvs_ldo_output_voltage_t;

/*!
 * @brief The enumeration of PF5020 internal regulators.
 */
typedef enum _pf5020_regulator_name
{
    kPF5020_BuckRegulatorSw1   = 0x0U, /*!< Type1 Buck Regulator SW1. */
    kPF5020_BuckRegulatorSw2   = 0x1U, /*!< Type1 Buck Regulator SW2. */
    kPF5020_BuckRegulatorSwnd1 = 0x4U, /*!< Type2 Buck Regulator SWND1. */
    kPF5020_RegulatorLdo1      = 0x5U, /*!< Linear Regulator LDO1. */
} pf5020_regulator_name_t;

/*!
 * @brief The power down ramp and DVS rate during system on of type1 buck regulator.
 */
typedef enum _pf5020_type1_buck_regulator_dvs_ramp
{
    kPF5020_DVSRamp0 = 0x0U, /*!< Type1 Buck regulator DVS ramp0. */
    kPF5020_DVSRamp1 = 0x1U, /*!< Type1 Buck regulator DVS ramp1. */
    kPF5020_DVSRamp2 = 0x2U, /*!< Type1 Buck regulator DVS ramp2. */
    kPF5020_DVSRamp3 = 0x3U, /*!< Type1 Buck regulator DVS ramp3. */
} pf5020_type1_buck_regulator_dvs_ramp_t;

/*!
 * @brief The enumeration of all buck regulators'(SW1, SW2, SWND1) operate modes.
 */
typedef enum _pf5020_buck_regulator_operate_mode
{
    kPF5020_BuckRegulatorOff = 0x0U,   /*!< Turn off buck regulator. */
    kPF5020_BuckRegulatorPWMMode,      /*!< Set buck regulator as PWM mode. */
    kPF5020_BuckRegulatorPFMMode,      /*!< Set buck regulator as PFM mode. */
    kPF5020_BuckRegulatorAutoSkipMode, /*!< Set buck regulator as Auto skip mode. */
} pf5020_buck_regulator_operate_mode_t;

/*!
 * @brief The enumeration of all buck regulators'(SW1, SW2, SWND1) phase shift values.
 */
typedef enum _pf5020_buck_regulator_phase_shift
{
    kPF5020_BuckRegulatorPhaseShift45  = 0x0U, /*!< Phase shift 45 degrees. */
    kPF5020_BuckRegulatorPhaseShift90  = 0x1U, /*!< Phase shift 90 degrees. */
    kPF5020_BuckRegulatorPhaseShift135 = 0x2U, /*!< Phase shift 135 degrees. */
    kPF5020_BuckRegulatorPhaseShift180 = 0x3U, /*!< Phase shift 180 degrees. */
    kPF5020_BuckRegulatorPhaseShift225 = 0x4U, /*!< Phase shift 225 degrees. */
    kPF5020_BuckRegulatorPhaseShift270 = 0x5U, /*!< Phase shift 270 degrees. */
    kPF5020_BuckRegulatorPhaseShift315 = 0x6U, /*!< Phase shift 315 degrees. */
    kPF5020_BuckRegulatorPhaseShift0   = 0x7U, /*!< Phase shift 0 degrees. */
} pf5020_buck_regulator_phase_shift_t;

/*!
 * @brief The enumeration of all buck regulators'(SW1, SW2, SWND1) current limitation value.
 */
typedef enum _pf5020_buck_regulator_current_limit
{
    kPF5020_BuckRegulatorCurrentLimitBypass = 0x4U, /*!< Current limit fault bypassed. */
    kPF5020_BuckRegulatorCurrentLimit0      = 0x0U, /*!< Current limit protection enabled and current limit is 2.1A. */
    kPF5020_BuckRegulatorCurrentLimit1      = 0x1U, /*!< Current limit protection enabled and current limit is 2.6A. */
    kPF5020_BuckRegulatorCurrentLimit2      = 0x2U, /*!< Current limit protection enabled and current limit is 3.0A. */
    kPF5020_BuckRegulatorCurrentLimit3      = 0x3U, /*!< Current limit protection enabled and current limit is 4.5A. */
} pf5020_buck_regulator_current_limit_t;

/*!
 * @brief The enumeration of SWND1 buck regulator output voltage.
 */
typedef enum _pf5020_swnd1_output_voltage
{
    kPF5020_Swnd1Output1V = 0x0U, /*!< SWND1 output 1.0V during run state and standby state. */
    kPF5020_Swnd1Output1P1V,      /*!< SWND1 output 1.1V during run state and standby state. */
    kPF5020_Swnd1Output1P2V,      /*!< SWND1 output 1.2V during run state and standby state. */
    kPF5020_Swnd1Output1P25V,     /*!< SWND1 output 1.25V during run state and standby state. */
    kPF5020_Swnd1Output1P3V,      /*!< SWND1 output 1.3V during run state and standby state. */
    kPF5020_Swnd1Output1P35V,     /*!< SWND1 output 1.35V during run state and standby state. */
    kPF5020_Swnd1Output1P5V,      /*!< SWND1 output 1.5V during run state and standby state. */
    kPF5020_Swnd1Output1P6V,      /*!< SWND1 output 1.6V during run state and standby state. */
    kPF5020_Swnd1Output1P8V,      /*!< SWND1 output 1.8V during run state and standby state. */
    kPF5020_Swnd1Output1P85V,     /*!< SWND1 output 1.85V during run state and standby state. */

    kPF5020_Swnd1Output2P0V,      /*!< SWND1 output 2.0V during run state and standby state. */
    kPF5020_Swnd1Output2P1V,      /*!< SWND1 output 2.1V during run state and standby state. */
    kPF5020_Swnd1Output2P15V,     /*!< SWND1 output 2.15V during run state and standby state. */
    kPF5020_Swnd1Output2P25V,     /*!< SWND1 output 2.25V during run state and standby state. */
    kPF5020_Swnd1Output2P3V,      /*!< SWND1 output 2.3V during run state and standby state. */
    kPF5020_Swnd1Output2P4V,      /*!< SWND1 output 2.4V during run state and standby state. */
    kPF5020_Swnd1Output2P5V,      /*!< SWND1 output 2.5V during run state and standby state. */
    kPF5020_Swnd1Output2P8V,      /*!< SWND1 output 2.8V during run state and standby state. */

    kPF5020_Swnd1Output3P15V,     /*!< SWND1 output 3.15V during run state and standby state. */
    kPF5020_Swnd1Output3P20V,     /*!< SWND1 output 3.20V during run state and standby state. */
    kPF5020_Swnd1Output3P25V,     /*!< SWND1 output 3.25V during run state and standby state. */
    kPF5020_Swnd1Output3P30V,     /*!< SWND1 output 3.30V during run state and standby state. */
    kPF5020_Swnd1Output3P35V,     /*!< SWND1 output 3.3V during run state and standby state. */
    kPF5020_Swnd1Output3P40V,     /*!< SWND1 output 3.40V during run state and standby state. */
    kPF5020_Swnd1Output3P50V,     /*!< SWND1 output 3.50V during run state and standby state. */
    kPF5020_Swnd1Output3P80V,     /*!< SWND1 output 3.80V during run state and standby state. */

    kPF5020_Swnd1Output4P0V,      /*!< SWND1 output 4.0V during run state and standby state. */
    kPF5020_Swnd1Output4P1V,      /*!< SWND1 output 4.1V during run state and standby state. */
} pf5020_swnd1_output_voltage_t;

/*!
 * @brief The enumeration of LDO1 output voltage.
 */
typedef enum _pf5020_ldo1_output_voltage
{
    kPF5020_Ldo1Output1P5V = 0x0U, /*!< LDO1 output 1.5V. */
    kPF5020_Ldo1Output1P6V,        /*!< LDO1 output 1.6V */
    kPF5020_Ldo1Output1P8V,        /*!< LDO1 output 1.8V */
    kPF5020_Ldo1Output1P85V,       /*!< LDO1 output 1.85V */
    kPF5020_Ldo1Output2P15V,       /*!< LDO1 output 2.15V */
    kPF5020_Ldo1Output2P5V,        /*!< LDO1 output 2.5V */
    kPF5020_Ldo1Output2P8V,        /*!< LDO1 output 2.8V */
    kPF5020_Ldo1Output3P0V,        /*!< LDO1 output 3.0V */
    kPF5020_Ldo1Output3P1V,        /*!< LDO1 output 3.1V */
    kPF5020_Ldo1Output3P15V,       /*!< LDO1 output 3.15V */
    kPF5020_Ldo1Output3P2V,        /*!< LDO1 output 3.2V */
    kPF5020_Ldo1Output3P3V,        /*!< LDO1 output 3.3V */
    kPF5020_Ldo1Output3P35V,       /*!< LDO1 output 3.35V */
    kPF5020_Ldo1Output4P0V,        /*!< LDO1 output 4.0V */
    kPF5020_Ldo1Output4P9V,        /*!< LDO1 output 4.9V */
    kPF5020_Ldo1Output5P0V,        /*!< LDO1 output 5.0V */
} pf5020_ldo1_output_voltage_t;

/*!
 * @brief The enumeration of UV debounce time.
 */
typedef enum _pf5020_uv_debounce_time
{
    kPF5020_UVDebounceTime5us = 0x0U, /*!< UV debounce time will be set as 5us. */
    kPF5020_UVDebounceTime15us,       /*!< UV debounce time will be set as 15us. */
    kPF5020_UVDebounceTime30us,       /*!< UV debounce time will be set as 30us. */
    kPF5020_UVDebounceTime40us,       /*!< UV debounce time will be set as 40us. */
} pf5020_uv_debounce_time_t;

/*!
 * @brief The enumeration of OV debounce time.
 */
typedef enum _pf5020_ov_debounce_time
{
    kPF5020_OVDebounceTime30us = 0x0U, /*!< OV debounce time will be set as 30us. */
    kPF5020_OVDebounceTime50us,        /*!< OV debounce time will be set as 50us. */
    kPF5020_OVDebounceTime80us,        /*!< OV debounce time will be set as 80us. */
    kPF5020_OVDebounceTime125us,       /*!< OV debounce time will be set as 125us. */
} pf5020_ov_debounce_time_t;

/*!
 * @brief The enumeration of different reset behaviors triggered by WDI pin.
 */
typedef enum _pf5020_wdi_mode
{
    kPF5020_WDIPerformSoftWDReset = 0U, /*!< A WDI pin assert performs a hard WD reset. */
    kPF5020_WDIPerformHardWDReset = 1U, /*!< A WDI pin assert performs a soft WD reset.  */
} pf5020_wdi_mode_t;

/*!
 * @brief The enumeration of temperature sensor's operate mode.
 */
typedef enum _pf5020_temp_sensor_operate_mode
{
    kPF5020_TempSensorSampleMode = 0U,   /*!< Temperature sensor operates in sampling mode to
                                               reduce current consumption. */
    kPF5020_TempSensorAlwaysOnMode = 1U, /*!<  Temperatue sensor operates in Always on mode. */
} pf5020_temp_sensor_operate_mode_t;

/*!
 * @brief The enumeration of AMUX selection.
 */
typedef enum _pf5020_amux_selection
{
    kPF5020_AmuxSelDisable = 0x0U, /*!< AMUX selection disabled, internal signal dividing ratio N/A. */
    kPF5020_AmuxSelTempIc  = 0x7U, /*!< AMUX selection TEMP_IC, internal signal dividing ratio 1. */
} pf5020_amux_selection_t;

/*!
 * @brief The enumeration of interupts that PF5020 support, the member of this enumeration can be used to enable/disable
 * interrupts or get interrupt status flags.
 */
typedef enum _pf5020_interrupts
{
    kPF5020_IntStatus1_VinOVLOInterrupt = 0x1ULL,  /*!< Used to enable/disable Int Status1 Vin OVLO interrupt. */
    kPF5020_IntStatus1_PgoodInterrupt   = 0x2ULL,  /*!< Used to enable/disable Int Status1 PGOOD interrupt. */
    kPF5020_IntStatus1_PwrdnInterrupt   = 0x8ULL,  /*!< Used to enable/disable Int Status1 PWRDN interrupt. */
    kPF5020_IntStatus1_PwrupInterrupt   = 0x10ULL, /*!< Used to enable/disable Int Status1 PWRUP interrupt. */
    kPF5020_IntStatus1_CrcInterrupt     = 0x20ULL, /*!< Used to enable/disable Int Status1 CRC interrupt. */
    kPF5020_IntStatus1_FreqRdyInterrupt = 0x40ULL, /*!< Used to enable/disable Int Status1 frequency ready interrupt. */
    kPF5020_IntStatus1_SdwnInterrupt    = 0x80ULL, /*!< Used to enable/disable Int Status1 SDWN interrupt. */

    kPF5020_IntStatus2_Therm80Interrupt = (0x1ULL << 8ULL),   /*!< Used to enable/disable Int
                                                                  Status2 therm 80 interrupt. */
    kPF5020_IntStatus2_Therm95Interrupt = (0x2ULL << 8ULL),   /*!< Used to enable/disable Int
                                                                  Status2 therm 95 interrupt. */
    kPF5020_IntStatus2_Therm110Interrupt = (0x4ULL << 8ULL),  /*!< Used to enable/disable Int
                                                                 Status2 therm 110 interrupt. */
    kPF5020_IntStatus2_Therm125Interrupt = (0x8ULL << 8ULL),  /*!< Used to enable/disable Int
                                                                 Status2 therm 125 interrupt. */
    kPF5020_IntStatus2_Therm140Interrupt = (0x10ULL << 8ULL), /*!< Used to enable/disable Int
                                                                Status2 therm 140 interrupt. */
    kPF5020_IntStatus2_Therm155Interrupt = (0x20ULL << 8ULL), /*!< Used to enable/disable Int
                                                                Status2 therm 155 interrupt. */
    kPF5020_IntStatus2_FsyncFltInterrupt = (0x40ULL << 8ULL), /*!< Used to enable/disable Int
                                                                Status2 Fsync filter interrupt. */
    kPF5020_IntStatus2_WdiInterrupt = (0x80ULL << 8ULL),      /*!< Used to enable/disable Int Status2 WDI interrupt. */

    kPF5020_SwMode_Sw1ModeInterrupt   = (0x1ULL << 16ULL),    /*!< Used to enable/disable SW1 mode interrupt. */
    kPF5020_SwMode_Sw2ModeInterrupt   = (0x2ULL << 16ULL),    /*!< Used to enable/disable SW2 interrupt. */
    kPF5020_SwMode_Swnd1ModeInterrupt = (0x40ULL << 16ULL),   /*!< Used to enable/disable SWND1 interrupt. */

    kPF5020_ILIM_Sw1IlimInterrupt   = (0x1ULL << 24ULL),      /*!< Used to enable/disable SW1 ILIM interrupt. */
    kPF5020_ILIM_Sw2IlimInterrupt   = (0x2ULL << 24ULL),      /*!< Used to enable/disable SW2 ILIM interrupt. */
    kPF5020_ILIM_Swnd1IlimInterrupt = (0x40ULL << 24ULL),     /*!< Used to enable/disable SWND1 ILIM interrupt. */

    kPF5020_ILIM_Ldo1IlimInterrupt = (0x80ULL << 24ULL),      /*!< Used to enable/disable LDO1 ILIM interrupt. */

    kPF5020_UV_Sw1UvInterrupt   = (0x1ULL << 32ULL),          /*!< Used to enable/disable SW1 UV interrupt. */
    kPF5020_UV_Sw2UvInterrupt   = (0x2ULL << 32ULL),          /*!< Used to enable/disable SW2 UV interrupt. */
    kPF5020_UV_Swnd1UvInterrupt = (0x40ULL << 32ULL),         /*!< Used to enable/disable SWND1 UV interrupt. */

    kPF5020_UV_Ldo1UvInterrupt = (0x80ULL << 32ULL),          /*!< Used to enable/disable SW1 LDO1 interrupt. */

    kPF5020_OV_Sw1OvInterrupt   = (0x1ULL << 40ULL),          /*!< Used to enable/disable SW1 OV interrupt. */
    kPF5020_OV_Sw2OvInterrupt   = (0x2ULL << 40ULL),          /*!< Used to enable/disable SW2 OV interrupt. */
    kPF5020_OV_Swnd1OvInterrupt = (0x40ULL << 40ULL),         /*!< Used to enable/disable SWND1 OV interrupt. */

    kPF5020_OV_Ldo1OvInterrupt = (0x80ULL << 40ULL),          /*!< Used to enable/disable LDO1 OV interrupt. */

    kPF5020_Pwron_PushInterrupt  = (0x1ULL << 48ULL),         /*!< Used to enable/disable PWRON Push interrupt. */
    kPF5020_Pwron_RelInterrupt   = (0x2ULL << 48ULL),         /*!< Used to enable/disable PWRON REL interrupt. */
    kPF5020_Pwron_1sInterrupt    = (0x4ULL << 48ULL),         /*!< Used to enable/disable PWRON 1s interrupt. */
    kPF5020_Pwron_2sInterrupt    = (0x8ULL << 48ULL),         /*!< Used to enable/disable PWRON 2s interrupt. */
    kPF5020_Pwron_3sInterrupt    = (0x10ULL << 48ULL),        /*!< Used to enable/disable PWRON 3s interrupt. */
    kPF5020_Pwron_4sInterrupt    = (0x20ULL << 48ULL),        /*!< Used to enable/disable PWRON 4s interrupt. */
    kPF5020_Pwron_8sInterrupt    = (0x40ULL << 48ULL),        /*!< Used to enable/disable PWRON 8s interrupt. */
    kPF5020_Pwron_BgmonInterrupt = (0x80ULL << 48ULL),        /*!< Used to enable/disable PWRON BGMON interrupt. */

    kPF5020_AllInterrupts = 0xFFC3C3C343FFFBULL,              /*!< All interrupts. */
} pf5020_interrupt_t;

/*!
 * @brief The enumeration of sequence time base.
 */
typedef enum _pf5020_sequencer_time_base
{
    kPF5020_TimeBase30us  = 0x0U, /*!< Sequencer time base is 30us. */
    kPF5020_TimeBase120us = 0x1U, /*!< Sequencer time base is 120us. */
    kPF5020_TimeBase250us = 0x2U, /*!< Sequencer time base is 250us. */
    kPF5020_TimeBase500us = 0x3U, /*!< Sequencer time base is 500us. */
} pf5020_sequencer_time_base_t;

/*!
 * @brief The enumeration of power down mode, including sequential mode and group mode.
 */
typedef enum _pf5020_power_down_mode
{
    kPF5020_PowerDownSequentialMode = 0U, /*!< Use the same sequence slot value as the power up sequence to power
                                              down in reverse order. */
    kPF5020_PowerDownGroupMode = 1U,      /*!< Power down in groups, all regulators assigned to the same group are
                                              disabled at the same time when the corresponding group is due to be
                                              disabled. */
} pf5020_power_down_mode_t;

/*!
 * @brief The enumeration of power down group, group 4 being the lowest hierarchy and
 * group 1 the highest hierarchy group.
 */
typedef enum _pf5020_power_down_group
{
    kPF5020_PowerDownGroup4 = 0x0U, /*!< Power down group4. */
    kPF5020_PowerDownGroup3,        /*!< Power down group3. */
    kPF5020_PowerDownGroup2,        /*!< Power down group2. */
    kPF5020_PowerDownGroup1,        /*!< Power down group1. */
} pf5020_power_down_group_t;

/*!
 * @brief The enumeration of power down delay.
 */
typedef enum _pf5020_power_down_delay
{
    kPF5020_PowerDownDelay120us  = 0x0, /*!< Power down delay 120us. */
    kPF5020_PowerDownDelay250us  = 0x1, /*!< Power down delay 250us. */
    kPF5020_PowerDownDelay500us  = 0x2, /*!< Power down delay 500us. */
    kPF5020_PowerDownDelay1000us = 0x3, /*!< Power down delay 1000us. */
} pf5020_power_down_delay_t;

/*!
 * @brief The enumeration of delay after RESETBMCU is asserted.
 */
typedef enum _pf5020_resetBMCU_delay
{
    kPF5020_ResetBMcuDelayOff = 0x0U, /*!< RESETBMCU no delay. */
    kPF5020_ResetBMcuDelay10us,       /*!< RESETBMCU delay 10 us. */
    kPF5020_ResetBMcuDelay100us,      /*!< RESETBMCU delay 100 us. */
    kPF5020_ResetBMcuDelay500us,      /*!< RESETBMCU delay 500 us. */
} pf5020_resetBMCU_delay_t;

/*!
 * @brief Internal high speed clock configuration.
 */
typedef struct _pf5020_high_speed_clk_config
{
    pf5020_high_speed_clk_freq_t clkFreq;     /*!< The frequency of internal high speed clock,
                                                  please refer to @ref pf5020_high_speed_clk_freq_t for details. */
    bool enableSS;                            /*!< Enable/disable spread-spectrum,
                                                  - \b true Enable spread-spectrum;
                                                  - \b false Disable spread-spectrum. */
    pf5020_high_speed_clk_ss_range_t ssRange; /*!< The range of internal high speed clock,
                                                  please refer to @ref pf5020_high_speed_clk_ss_range_t. */
} pf5020_high_speed_clk_config_t;

/*!
 * @brief Type1 buck regulator SW1 global configuration, including run/standby operate mode, run/standby voltage value.
 */
typedef struct _pf5020_sw1_regulator_config
{
    pf5020_type1_buck_regulator_dvs_ramp_t sw1DvsRamp; /*!< SW1 DVS Ramp, please refer to
                                                           @ref pf5020_type1_buck_regulator_dvs_ramp_t
                                                           for details. */

    uint8_t sw1RunOutputVolt;                          /*!< The output voltage during RUN state, the step is 6.25mV,
                                                        0: 0.4V, 177: 1.8V, 178 to 255 reserved. */
    pf5020_buck_regulator_operate_mode_t sw1RunOperateMode; /*!< SW1 operate mode in run state, please refer to
                                                            @ref pf5020_buck_regulator_operate_mode_t for details. */

    uint8_t sw1StandbyOutputVolt; /*!< The output voltage during standby state, the step is 6.25mV,
                                   0: 0.4V, 177: 1.8V, 178 to 255 reserved. */
    pf5020_buck_regulator_operate_mode_t sw1StandbyOperateMode; /*!< SW1 operate mode in standby mode. */

    pf5020_buck_regulator_phase_shift_t sw1PhaseShift;          /*!< SW1 buck regulator phase shift value, please refer
                                                                    to @ref pf5020_buck_regulator_phase_shift_t for details. */

    pf5020_buck_regulator_current_limit_t sw1CurrentLimit;      /*!< SW1 buck regulator current limitation value, please
                                                                    refer to @ref pf5020_buck_regulator_current_limit_t
                                                                    for details. */
    bool sw1EnableUVBypass;                                     /*!< Used to control whether bypass UV monitor for SW1,
                                                                    - \b true Bypass UV monitor for SW1.
                                                                    - \b false Don't bypass UV monitor for SW1. */
    bool sw1EnableOVBypass;                                     /*!< Used to control whether bypass OV monitor for SW1,
                                                                    - \b true Bypass OV monitor for SW1.
                                                                    - \b false Don't bypass OV monitor for SW1. */
    bool sw1FaultReEnabled;       /*!< Used to control whether return to sw1 regulator previous state
                                  if fault condition is cleared.
                                  - \b true  SW1 regulator remains disabled after the fault condition is cleared
                                              or no longer present.
                                  - \b false SW1 regulator returns to its previous state if fault condition is cleared. */

    bool sw1EnablePGMonitor;      /*!< Enable/disable SW1 regulator PG monitor. */

    bool sw1EnableWatchdogBypass; /*!< Enable/disable watchdog bypass,
                                      - \b true The watchdog bypass is enabled and the output of the SW1 regulator
                                                  is not affected by the soft WD reset, keeping its current
                                                  configuration.
                                      - \b false The watchdog bypass is disabled and the output of the SW1
                                                  regulator is returned to its default OTP value during the
                                                  soft WD reset. */
} pf5020_sw1_regulator_config_t;

/*!
 * @brief Type1 buck regulator SW2 global configuration, including run/standby operate mode, run/standby voltage value.
 */
typedef struct _pf5020_sw2_regulator_config
{
    pf5020_type1_buck_regulator_dvs_ramp_t sw2DvsRamp; /*!< SW2 DVS Ramp, please refer to
                                                           @ref pf5020_type1_buck_regulator_dvs_ramp_t
                                                           for details. */

    uint8_t sw2RunOutputVolt;                          /*!< The output voltage during RUN state, the step is 6.25mV,
                                                        0: 0.4V, 177: 1.8V, 178 to 255 reserved. */
    pf5020_buck_regulator_operate_mode_t
        sw2RunOperateMode;                             /*!< SW2 operate mode in run state, please refer to
                                                           @ref pf5020_buck_regulator_operate_mode_t for details. */

    uint8_t sw2StandbyOutputVolt;                      /*!< The output voltage during standby state, the step is 6.25mV,
                                                        0: 0.4V, 177: 1.8V, 178 to 255 reserved. */
    pf5020_buck_regulator_operate_mode_t sw2StandbyOperateMode; /*!< SW2 operate mode in standby mode. */

    pf5020_buck_regulator_phase_shift_t sw2PhaseShift;          /*!< SW2 buck regulator phase shift value, please refer
                                                                    to @ref pf5020_buck_regulator_phase_shift_t for details. */

    bool sw2EnableVTTOperation; /*!< Enable/disable VTT mode, VTT mode used to create VTT termination
                                    for DDR memories. */

    pf5020_buck_regulator_current_limit_t sw2CurrentLimit; /*!< SW2 buck regulator current limitation value, please
                                                                   refer to @ref pf5020_buck_regulator_current_limit_t
                                                                   for details. */
    bool sw2EnableUVBypass;                                /*!< Used to control whether bypass UV monitor for SW2,
                                                               - \b true Bypass UV monitor for SW2.
                                                               - \b false Don't bypass UV monitor for SW2. */
    bool sw2EnableOVBypass;                                /*!< Used to control whether bypass OV monitor for SW2,
                                                               - \b true Bypass OV monitor for SW2.
                                                               - \b false Don't bypass OV monitor for SW2. */
    bool sw2FaultReEnabled;       /*!< Used to control whether return to sw2 regulator previous state
                                      if fault condition is cleared.
                                  - \b true  SW2 regulator remains disabled after the fault condition is cleared
                                              or no longer present.
                                  - \b false SW2 regulator returns to its previous state if fault condition is cleared. */

    bool sw2EnablePGMonitor;      /*!< Enable/disable SW2 regulator PG monitor. */

    bool sw2EnableWatchdogBypass; /*!< Enable/disable watchdog bypass,
                                      - \b true The watchdog bypass is enabled and the output of the SW2 regulator
                                                  is not affected by the soft WD reset, keeping its current
                                                  configuration.
                                      - \b false The watchdog bypass is disabled and the output of the SW2
                                                  regulator is returned to its default OTP value during the
                                                  soft WD reset. */

} pf5020_sw2_regulator_config_t;

/*!
 * @brief Type2 buck regulator SWND1 global configuration, including run/standby operate mode, output voltage value.
 */
typedef struct _pf5020_swnd1_regulator_config
{
    pf5020_swnd1_output_voltage_t swnd1OutputVolt;                /*!< This member sets the output voltage during RUN
                                                                        and Standby state. */
    pf5020_buck_regulator_operate_mode_t swnd1RunOperateMode;     /*!< SWND1 operate mode in run state, please refer to
                                                                  @ref pf5020_buck_regulator_operate_mode_t for details. */
    pf5020_buck_regulator_operate_mode_t swnd1StandbyOperateMode; /*!< SWND1 operate mode in standby mode. */

    pf5020_buck_regulator_phase_shift_t swnd1PhaseShift;     /*!< SWND1 buck regulator phase shift value, please refer
                                                             to @ref pf5020_buck_regulator_phase_shift_t for details. */

    pf5020_buck_regulator_current_limit_t swnd1CurrentLimit; /*!< SWND1 buck regulator current limitation value, please
                                                                refer to @ref pf5020_buck_regulator_current_limit_t
                                                                for details. */
    bool swnd1EnableUVBypass;                                /*!< Used to control whether bypass UV monitor for SWND1,
                                                                 - \b true Bypass UV monitor for SWND1.
                                                                 - \b false Don't bypass UV monitor for SWND1. */
    bool swnd1EnableOVBypass;                                /*!< Used to control whether bypass OV monitor for SWND1,
                                                                 - \b true Bypass OV monitor for SWND1.
                                                                 - \b false Don't bypass OV monitor for SWND1. */
    bool swnd1FaultReEnabled;       /*!< Used to control whether return to swnd1 regulator previous state
                                      if fault condition is cleared.
                                  - \b true  SWND1 regulator remains disabled after the fault condition is cleared
                                              or no longer present.
                                  - \b false SWND1 regulator returns to its previous state if fault condition is cleared. */

    bool swnd1EnablePGMonitor;      /*!< Enable/disable SWND1 regulator PG monitor. */

    bool swnd1EnableWatchdogBypass; /*!< Enable/disable watchdog bypass,
                                      - \b true The watchdog bypass is enabled and the output of the SWND1 regulator
                                                  is not affected by the soft WD reset, keeping its current
                                                  configuration.
                                      - \b false The watchdog bypass is disabled and the output of the SWND1
                                                  regulator is returned to its default OTP value during the
                                                  soft WD reset. */
} pf5020_swnd1_regulator_config_t;

/*!
 * @brief Linear regulator LDO1 global configuration, including run/standby operate mode, output voltage value and so
 * on.
 */
typedef struct _pf5020_ldo1_regulator_config
{
    bool ldo1RunEnable;                                 /*!< Enable/disable LDO1 in run state,
                                                            - \b true Enable LDO1 in run state;
                                                            - \b false Disable LDO1 in run state. */
    pf5020_ldo1_output_voltage_t ldo1RunOutputVolt;     /*!< Used to set the output voltage of LDO1 in run state,
                                                            please refer to @ref pf5020_ldo1_output_voltage_t. */

    bool ldo1StandbyEnable;                             /*!< Enable/disable LDO1 in standby state,
                                                            - \b true Enable LDO1 in standby state;
                                                            - \b false Disable LDO1 in standby state. */
    pf5020_ldo1_output_voltage_t ldo1StandbyOutputVolt; /*!< Used to set the output voltage of LDO1 in standby state,
                                                        please refer to @ref pf5020_ldo1_output_voltage_t. */

    bool ldo1EnableUVBypass;                            /*!< Used to control whether bypass UV monitor for LDO1,
                                                            - \b true Bypass UV monitor for LDO1.
                                                            - \b false Don't bypass UV monitor for LDO1. */
    bool ldo1EnableOVBypass;                            /*!< Used to control whether bypass OV monitor for LDO1,
                                                            - \b true Bypass OV monitor for LDO1.
                                                            - \b false Don't bypass OV monitor for LDO1. */
    bool ldo1EnableILIMBypass;                          /*!< Used to control whether bypass ILIM monitor for LDO1,
                                                            - \b true Bypass ILIM monitor for LDO1.
                                                            - \b false Don't bypass ILIM monitor for LDO1. */

    bool ldo1FaultReEnabled;       /*!< Used to control whether return to ldo1 regulator previous state
                                      if fault condition is cleared.
                                  - \b true  LDO1 regulator remains disabled after the fault condition is cleared
                                              or no longer present.
                                  - \b false LDO1 regulator returns to its previous state if fault condition is
                                              cleared. */

    bool ldo1EnablePGMonitor;      /*!< Enable/disable LDO1 regulator PG monitor. */

    bool ldo1EnableWatchdogBypass; /*!< Enable/disable watchdog bypass,
                                      - \b true The watchdog bypass is enabled and the output of the LDO1 regulator
                                                  is not affected by the soft WD reset, keeping its current
                                                  configuration.
                                      - \b false The watchdog bypass is disabled and the output of the LDO1
                                                  regulator is returned to its default OTP value during the
                                                  soft WD reset. */
} pf5020_ldo1_regulator_config;

/*!
 * @brief Internal watchdog timer configuration, including timer duration, cyclic counter max value and so on.
 */
typedef struct _pf5020_wdog_internal_timer_config
{
    bool enable;                  /*!< Enable/disable the internal watchdog timer operation. */
    bool enableStandby;           /*!< Enable/disable the internal watchdog timer operation during standby. */
    uint8_t timerDuration;        /*!< The internal watchdog timer expire duration value, ranges from 0 to 15,
                                       the actual expire time = 2 ^ timerDuration.  */
    uint8_t cyclicCounterMaxVale; /*!< The max value of watchdog cyclic counter, and the cyclic counter is used
                                         to ensure no cyclic watchdog condition occurs. */
} pf5020_wdog_internal_timer_config_t;

/*!
 * @brief PF5020 power up sequence configuration.
 */
typedef struct _pf5020_power_up_sequence
{
    uint8_t resetBMCUSeq; /*!< The sequence slot of RESETBMCU pin in power up sequence, sequence code 0 indicates that
                              the RESETBMCU is not part of the power up sequence. */
    uint8_t pGoodSeq;     /*!< The sequence slot of PGOOD pin in power up sequence, sequence code 0 indicates that
                              the PGOOD is not part of the power up sequence. */
    uint8_t sw1Seq;       /*!< The sequence slot of SW1 regulator in power up sequence, sequence code 0 indicates that
                              the SW1 regulator is not part of the power up sequence. */
    uint8_t sw2Seq;       /*!< The sequence slot of SW2 regulator in power up sequence, sequence code 0 indicates that
                              the SW2 regulator is not part of the power up sequence. */
    uint8_t swnd1Seq;     /*!< The sequence slot of SWND1 regulator in power up sequence, sequence code 0 indicates that
                              the SWND1 regulator is not part of the power up sequence. */
    uint8_t ldo1Seq;      /*!< The sequence slot of LDO in power up sequence, sequence code 0 indicates that
                              the LDO is not part of the power up sequence. */
} pf5020_power_up_sequence_t;

/*!
 * @brief PF5020 power down group configuration.
 */
typedef struct _pf5020_power_down_group_config
{
    pf5020_power_down_group_t resetBMCUGroup; /*!< The power down group of RESETBMCU pin. */
    pf5020_power_down_group_t pGoodGroup;     /*!< The power down group of PGOOD pin. */
    pf5020_power_down_group_t sw1Group;       /*!< The power down group of SW1 regulator. */
    pf5020_power_down_group_t sw2Group;       /*!< The power down group of SW2 regulator. */
    pf5020_power_down_group_t swnd1Group;     /*!< The power down group of SWND1 regulator. */
    pf5020_power_down_group_t ldo1Group;      /*!< The power down group of LDO1. */
} pf5020_power_down_group_config_t;

/*!
 * @brief PF5020 runtime handle, including send function, receive function and slave address.
 */
typedef struct _pf5020_handle
{
    status_t (*I2C_SendFunc)(uint8_t deviceAddress,
                             uint32_t subAddress,
                             uint8_t subAddressSize,
                             uint8_t *txBuff,
                             uint8_t txBuffSize); /*!< Pointer to I2C send function. */
    status_t (*I2C_ReceiveFunc)(uint8_t deviceAddress,
                                uint32_t subAddress,
                                uint8_t subAddressSize,
                                uint8_t *rxBuff,
                                uint8_t rxBuffSize); /*!< Pointer to I2C receive function. */
    uint8_t slaveAddress;                            /*!< device slave address. */
} pf5020_handle_t;

/*!
 * @brief PF5020 initialize configuration.
 */
typedef struct _pf5020_config
{
    status_t (*I2C_SendFunc)(uint8_t deviceAddress,
                             uint32_t subAddress,
                             uint8_t subAddressSize,
                             uint8_t *txBuff,
                             uint8_t txBuffSize); /*!< Pointer to I2C send function. */
    status_t (*I2C_ReceiveFunc)(uint8_t deviceAddress,
                                uint32_t subAddress,
                                uint8_t subAddressSize,
                                uint8_t *rxBuff,
                                uint8_t rxBuffSize); /*!< Pointer to I2C receive function. */
    uint8_t slaveAddress;                            /*!< device slave address. */
} pf5020_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

/*! @name Basic Interfaces
 * @{
 */

/*!
 * @brief Write to PF5020 register via I2C.
 *
 * @param handle The pointer to @ref pf5020_handle_t.
 * @param regAddr The address of register to write.
 * @param val The value to be write.
 *
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_WriteReg(pf5020_handle_t *handle, uint8_t regAddr, uint8_t val);

/*!
 * @brief Read value from PF5020 register via I2C.
 *
 * @param handle The pointer to @ref pf5020_handle_t.
 * @param regAddr The address of register to write.
 * @param val Pointer store return value.
 *
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_ReadReg(pf5020_handle_t *handle, uint8_t regAddr, uint8_t *val);

/*!
 * @brief Read and modify the register value
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param regAddr The address of register.
 * @param mask The mask of register bit to be modified.
 * @param val The value to be set.
 *
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_ModifyReg(pf5020_handle_t *handle, uint8_t regAddr, uint8_t mask, uint8_t val);

/*!
 * @brief Dump the value of continuous registers.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param regAddr The address of start register.
 * @param buffer The buffer to store the dumped registers' value.
 * @param length The length of the continuous registers to be dumped.
 *
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_DumpReg(pf5020_handle_t *handle, uint8_t regAddr, uint8_t *buffer, uint8_t length);

/*!
 * @brief Get default initialize configuration.
 *
 * @code
 *   config->I2C_SendFunc = NULL;
 *   config->I2C_ReceiveFunc = NULL;
 *   config->slaveAddress = 0x08U;
 * @endcode
 * @param config The pointer to @ref pf5020_config_t structure.
 */
void PF5020_GetDefaultConfig(pf5020_config_t *config);

/*!
 * @brief Initialize runtime handle.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param config The pointer to @ref pf5020_config_t structure.
 */
void PF5020_CreateHandle(pf5020_handle_t *handle, const pf5020_config_t *config);

/*! @} */

/*! @name Power Up/Down Sequence Control API
 *@{
 */

/*!
 * @brief Set power up sequencer time base.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param timeBase The time base value to set, please refer @ref pf5020_sequencer_time_base_t for details.
 *
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SetSequencerTimeBase(pf5020_handle_t *handle, pf5020_sequencer_time_base_t timeBase);

/*!
 * @brief Set power up sequence, when transitioning from standby state to run state, the power up sequencer is activated
 * only if any of the regulators is re-enabled during this transition.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param powerUpSeq The pointer to @ref pf5020_power_up_sequence_t structure.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SetPowerUpSequence(pf5020_handle_t *handle, pf5020_power_up_sequence_t *powerUpSeq);

/*!
 * @brief Turn off PF5020 PMIC.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_TurnOffPMIC(pf5020_handle_t *handle);

/*!
 * @brief Set power down mode, sequential mode or group mode.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param powerDownMode The power down mode to set, please refer to @ref pf5020_power_down_mode_t.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SetPowerDownMode(pf5020_handle_t *handle, pf5020_power_down_mode_t powerDownMode);

/*!
 * @brief Set power down groups that each internal module placed to.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param groupConfig Pointer to the @ref pf5020_power_down_group_config_t structure.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SetPowerDownGroups(pf5020_handle_t *handle, const pf5020_power_down_group_config_t *groupConfig);

/*!
 * @brief Set selected power down group's delay.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param group The selected power down group, please refer to @ref pf5020_power_down_group_t for details.
 * @param delay The delay value to be set, please refer to @ref pf5020_power_down_delay_t for details.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SetPowerDownGroupDelay(pf5020_handle_t *handle,
                                       pf5020_power_down_group_t group,
                                       pf5020_power_down_delay_t delay);

/*!
 * @brief Set delay to disable the regulators after RESETBMCU is asserted.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param delay The delay value, please refer to @ref pf5020_resetBMCU_delay_t.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SetResetBMcuPinDelay(pf5020_handle_t *handle, pf5020_resetBMCU_delay_t delay);

/*! @} */

/*! @name Clock Management
 *@{
 */

/*!
 * @brief Configure internal high speed clock.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param config The pointer to @ref pf5020_high_speed_clk_config_t structure.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_CLK_ConfigHighSpeedClock(pf5020_handle_t *handle, const pf5020_high_speed_clk_config_t *config);

/*!
 * @brief Enable/disable clock sync out.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param enable Used to enable/disable sync output.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_CLK_EnableSyncOut(pf5020_handle_t *handle, bool enable);

/*! @} */

/*! @name Converters Management
 * @{
 */

/*!
 * @brief Set VSNS LDO output voltage.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param voltage The output voltage of VSNVS, please refer to @ref pf5020_vsnvs_ldo_output_voltage_t.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SetVsnvsLdoOutputVoltage(pf5020_handle_t *handle, pf5020_vsnvs_ldo_output_voltage_t voltage);

/* SW1 Buck Regulator Control APIs. */
/*!
 * @brief Set SW1 Buck regulator global configuration.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param config The pointer to @ref pf5020_sw1_regulator_config_t structure.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW1_SetGlobalConfig(pf5020_handle_t *handle, const pf5020_sw1_regulator_config_t *config);

/*!
 * @brief Set DVS Ramp for SW1 buck regulator.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param dvsRamp The DVS ramp value to set, please refer to @ref pf5020_type1_buck_regulator_dvs_ramp_t for details.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW1_SetDvsRamp(pf5020_handle_t *handle, pf5020_type1_buck_regulator_dvs_ramp_t dvsRamp);

/*!
 * @brief Set SW1 regulator's output voltage and operate mode in run state.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param runOutputVolt The output voltage of SW1 in run state.
 * @param runOperateMode The operate mode of SW1 in run state.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW1_SetRunStateOption(pf5020_handle_t *handle,
                                      uint8_t runOutputVolt,
                                      pf5020_buck_regulator_operate_mode_t runOperateMode);

/*!
 * @brief Set SW1 regulator's output voltage and operate mode in standby state.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param standbyOutputVolt The output voltage of SW1 in standby state.
 * @param standbyOperateMode The operate mode of SW1 in standby state.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW1_SetStandbyStateOption(pf5020_handle_t *handle,
                                          uint8_t standbyOutputVolt,
                                          pf5020_buck_regulator_operate_mode_t standbyOperateMode);

/*!
 * @brief Set SW1 regulator fault detection related options.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param currentLimit SW1 buck regulator current limitation value, please refer to
 *                      @ref pf5020_buck_regulator_current_limit_t for details.
 * @param enableUVBypass Enable/disable UV bypass.
 * @param enableOVBypass Enable/disable OV bypass.
 * @param faultReEnabled Used to control whether return to sw1 regulator previous state if fault condition is cleared.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW1_SetFaultDetection(pf5020_handle_t *handle,
                                      pf5020_buck_regulator_current_limit_t currentLimit,
                                      bool enableUVBypass,
                                      bool enableOVBypass,
                                      bool faultReEnabled);

/*!
 * @brief Set SW1 regulator phase shift value.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param phaseShift SW1 buck regulator phase shift value, please refer to @ref pf5020_buck_regulator_phase_shift_t
 *                   for details.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW1_SetPhaseShift(pf5020_handle_t *handle, pf5020_buck_regulator_phase_shift_t phaseShift);

/*!
 * @brief Enable/disable PG monitor for SW1 regulator.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param enable Enable/disable PG monitor.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW1_EnablePGMonitor(pf5020_handle_t *handle, bool enable);

/*!
 * @brief Enable/disable watchdog bypass for SW1 regulator.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param enable Enable/disable watchdog bypass.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW1_EnableWatchDogBypass(pf5020_handle_t *handle, bool enable);

/* SW2 Buck Regulator Control APIs. */
/*!
 * @brief Set SW2 Buck regulator global configuration.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param config The pointer to @ref pf5020_sw2_regulator_config_t structure.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW2_SetGlobalConfig(pf5020_handle_t *handle, const pf5020_sw2_regulator_config_t *config);

/*!
 * @brief Set DVS Ramp for SW2 buck regulator.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param dvsRamp The DVS ramp value to set, please refer to @ref pf5020_type1_buck_regulator_dvs_ramp_t for details.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW2_SetDvsRamp(pf5020_handle_t *handle, pf5020_type1_buck_regulator_dvs_ramp_t dvsRamp);

/*!
 * @brief Set SW2 regulator's output voltage and operate mode in run state.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param runOutputVolt The output voltage of SW2 in run state.
 * @param runOperateMode The operate mode of SW2 in run state.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW2_SetRunStateOption(pf5020_handle_t *handle,
                                      uint8_t runOutputVolt,
                                      pf5020_buck_regulator_operate_mode_t runOperateMode);

/*!
 * @brief Set SW2 regulator's output voltage and operate mode in standby state.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param standbyOutputVolt The output voltage of SW2 in standby state.
 * @param standbyOperateMode The operate mode of SW2 in standby state.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW2_SetStandbyStateOption(pf5020_handle_t *handle,
                                          uint8_t standbyOutputVolt,
                                          pf5020_buck_regulator_operate_mode_t standbyOperateMode);

/*!
 * @brief Set SW2 regulator phase shift value.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param phaseShift SW2 buck regulator phase shift value, please refer to @ref pf5020_buck_regulator_phase_shift_t
 *                   for details.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW2_SetPhaseShift(pf5020_handle_t *handle, pf5020_buck_regulator_phase_shift_t phaseShift);

/*!
 * @brief Enable/disable SW2 VTT operateion.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param enable Used to enable/disable VTT operation.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW2_EnableVTTOperation(pf5020_handle_t *handle, bool enable);

/*!
 * @brief Set SW2 regulator fault detection related options.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param currentLimit SW2 buck regulator current limitation value, please refer to
 *                      @ref pf5020_buck_regulator_current_limit_t for details.
 * @param enableUVBypass Enable/disable UV bypass.
 * @param enableOVBypass Enable/disable OV bypass.
 * @param faultReEnabled Used to control whether return to sw1 regulator previous state if fault condition is cleared.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW2_SetFaultDetection(pf5020_handle_t *handle,
                                      pf5020_buck_regulator_current_limit_t currentLimit,
                                      bool enableUVBypass,
                                      bool enableOVBypass,
                                      bool faultReEnabled);

/*!
 * @brief Enable/disable PG monitor for SW2 regulator.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param enable Enable/disable PG monitor.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW2_EnablePGMonitor(pf5020_handle_t *handle, bool enable);

/*!
 * @brief Enable/disable watchdog bypass for SW2 regulator.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param enable Enable/disable watchdog bypass.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW2_EnableWatchDogBypass(pf5020_handle_t *handle, bool enable);

/* SWND1 Buck Regulator Control APIs. */
/*!
 * @brief Set SWND1 Buck regulator global configuration.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param config The pointer to @ref pf5020_swnd1_regulator_config_t structure.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SWND1_SetGlobalConfig(pf5020_handle_t *handle, const pf5020_swnd1_regulator_config_t *config);

/*!
 * @brief Set run/standby output voltage for SWND1 regulator.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param outputVolt The output voltage of SWND1 regulator in run/standby state,
 *                  please refer to @ref pf5020_swnd1_output_voltage_t for details.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SWND1_SetOutputVoltage(pf5020_handle_t *handle, pf5020_swnd1_output_voltage_t outputVolt);

/*!
 * @brief Set SWND1 regulator's operate mode in run and standby state.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param runOperateMode The operate mode of SWND1 in run state, please refer to @ref
 * pf5020_buck_regulator_operate_mode_t.
 * @param standbyOperateMode The operate mode of SWND1 in standby state, please refer to @ref
 * pf5020_buck_regulator_operate_mode_t.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SWND1_SetOperateMode(pf5020_handle_t *handle,
                                     pf5020_buck_regulator_operate_mode_t runOperateMode,
                                     pf5020_buck_regulator_operate_mode_t standbyOperateMode);

/*!
 * @brief Set SWND1 regulator phase shift value.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param phaseShift SWND1 buck regulator phase shift value, please refer to @ref pf5020_buck_regulator_phase_shift_t
 *                   for details.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SWND1_SetPhaseShift(pf5020_handle_t *handle, pf5020_buck_regulator_phase_shift_t phaseShift);

/*!
 * @brief Set SWND1 regulator fault detection related options.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param currentLimit SWND1 buck regulator current limitation value, please refer to
 *                      @ref pf5020_buck_regulator_current_limit_t for details.
 * @param enableUVBypass Enable/disable UV bypass.
 * @param enableOVBypass Enable/disable OV bypass.
 * @param faultReEnabled Used to control whether return to sw1 regulator previous state if fault condition is cleared.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SWND1_SetFaultDetection(pf5020_handle_t *handle,
                                        pf5020_buck_regulator_current_limit_t currentLimit,
                                        bool enableUVBypass,
                                        bool enableOVBypass,
                                        bool faultReEnabled);

/*!
 * @brief Enable/disable PG monitor for SWND1 regulator.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param enable Enable/disable PG monitor.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SWND1_EnablePGMonitor(pf5020_handle_t *handle, bool enable);

/*!
 * @brief Enable/disable watchdog bypass for SW1 regulator.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param enable Enable/disable watchdog bypass.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SWND1_EnableWatchDogBypass(pf5020_handle_t *handle, bool enable);

/* LDO1 Control APIs. */
/*!
 * @brief Set LDO1 global configuration.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param config The pointer to @ref pf5020_ldo1_regulator_config structure.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_LDO1_SetGlobalConfig(pf5020_handle_t *handle, const pf5020_ldo1_regulator_config *config);

/*!
 * @brief Set LDO1 regulator's output voltage and operate mode in run state.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param runEnable Enable/disable LDO1 in run state.
 * @param runOuputVolt The output voltage of LDO1 in run state, please refer to @ref pf5020_ldo1_output_voltage_t.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_LDO1_SetRunStateOption(pf5020_handle_t *handle,
                                       bool runEnable,
                                       pf5020_ldo1_output_voltage_t runOuputVolt);

/*!
 * @brief Set LDO1 regulator's output voltage and operate mode in standby state.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param standbyEnable Enable/disable LDO1 in standby state.
 * @param standbyOuputVolt The output voltage of LDO1 in standby state, please refer to @ref
 * pf5020_ldo1_output_voltage_t.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_LDO1_SetStandbyStateOption(pf5020_handle_t *handle,
                                           bool standbyEnable,
                                           pf5020_ldo1_output_voltage_t standbyOuputVolt);

/*!
 * @brief Set SWND1 regulator fault detection related options.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param enableILIMBypass Enable/disable ILIM bypass.
 * @param enableUVBypass Enable/disable UV bypass.
 * @param enableOVBypass Enable/disable OV bypass.
 * @param faultReEnabled Used to control whether return to ldos1 regulator previous state if fault condition is cleared.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_LDO1_SetFaultDetection(
    pf5020_handle_t *handle, bool enableILIMBypass, bool enableUVBypass, bool enableOVBypass, bool faultReEnabled);

/*!
 * @brief Enable/disable PG monitor for LDO1 regulator.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param enable Enable/disable PG monitor.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_LDO1_EnablePGMonitor(pf5020_handle_t *handle, bool enable);

/*!
 * @brief Enable/disable watchdog bypass for LDO1 regulator.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param enable Enable/disable watchdog bypass.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_LDO1_EnableWatchDogBypass(pf5020_handle_t *handle, bool enable);

/*! @} */

/*! @name Fault Detection
 * @{
 */

/*!
 * @brief Set voltage monitor debounce time.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param uvDebounceTime UV monitor debounce time, please refer to @ref pf5020_uv_debounce_time_t.
 * @param ovDebounceTime OV monitor debounce time, please refer to @ref pf5020_ov_debounce_time_t.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SetVoltageMonitorDebounceTime(pf5020_handle_t *handle,
                                              pf5020_uv_debounce_time_t uvDebounceTime,
                                              pf5020_ov_debounce_time_t ovDebounceTime);

/*!
 * @brief Enable/disable selected regulator's voltage monitor.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param name The regulator to be set.
 * @param enable Enable/disable voltage monitor.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_EnableVoltageMonitor(pf5020_handle_t *handle, pf5020_regulator_name_t name, bool enable);

/*!
 * @brief Set fault counter maximum value.
 *
 * @param handle Pointer to the @ref pf5020_handle_t structure.
 * @param maxValue Ranges from 0 to 15.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SetFaultCounterMaxValue(pf5020_handle_t *handle, uint8_t maxValue);

/*!
 * @brief Get fault counter current value.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
uint8_t PF5020_GetFaultCounterCurrentValue(pf5020_handle_t *handle);

/*!
 * @brief Set the expire value of the fault timer, when a regulator experiences a fault event, a fault timer will start.
 *
 * @param handle Pointer to the @ref pf5020_handle_t structure.
 * @param expireValue The expire value of fault timer, ranges from 0 to 11, the actual expire time = 2 ^ expireValue.
 *
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SetFaultTimerExpireValue(pf5020_handle_t *handle, uint8_t expireValue);

/*! @} */

/*! @name Watchdog Management
 * @{
 */

/*!
 * @brief Set reset behaviour asserted by WDI.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param wdiMode Used to control the WDI asserted performs a hard WD reset or soft WD reset.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_WDOG_SetWDIMode(pf5020_handle_t *handle, pf5020_wdi_mode_t wdiMode);

/*!
 * @brief Enable/disable WDI watchdog event in standby state.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param enable Used to control whether generate a watchdog event in standby mode if the WDI is asserted.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_WDOG_EnableWDIStanby(pf5020_handle_t *handle, bool enable);

/*!
 * @brief Configure internal watchdog timer.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param config Pointer to @ref pf5020_wdog_internal_timer_config_t structure.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_WDOG_ConfigInternalTimer(pf5020_handle_t *handle, const pf5020_wdog_internal_timer_config_t *config);

/*!
 * @brief Get cyclic counter current value.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @return Current cyclic counter value.
 */
uint8_t PF5020_WDOG_GetCyclicCounterValue(pf5020_handle_t *handle);

/*!
 * @brief Refresh internal watchdog timer.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_WDOG_RefreshInternalTimer(pf5020_handle_t *handle);

/*!
 * @brief Set watchdog event counter maximum value.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param maxValue The maximum value of watchdog event counter.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_WDOG_SetWDEventCounterMaxValue(pf5020_handle_t *handle, uint8_t maxValue);

/*!
 * @brief Get watchdog event counter current value.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @return Watch dog event counter current value.
 */
uint8_t PF5020_WDOG_GetWDEventCounterCurrentValue(pf5020_handle_t *handle);

/*! @} */

/*! @name Temperature Sensor
 * @{
 */

/*!
 * @brief Configure internal thermal monitor.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param enable Enable/disable temperature sensor circuit.
 * @param mode Used to set temperature sensor operate mode, please refer to @ref pf5020_temp_sensor_operate_mode_t.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_TMP_SetThermalMonitorConfig(pf5020_handle_t *handle,
                                            bool enable,
                                            pf5020_temp_sensor_operate_mode_t mode);

/*! @} */

/*! @name Analog Multiplexer Control APIs
 * @{
 */

/*!
 * @brief Configure analog multiplexer.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param enable Enable/disable analog multiplexer.
 * @param amuxSel Used to select amux output, please refer to @ref pf5020_amux_selection_t
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_AMUX_SetAnalogMuxConfig(pf5020_handle_t *handle, bool enable, pf5020_amux_selection_t amuxSel);

/*! @} */

/*! @name Interrupt Control
 * @{
 */

/*!
 * @brief Enable interrupts.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param interruptMask The mask of interrupts to clear, should be the OR'ed value of @ref pf5020_interrupt_t.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_EnableInterrupts(pf5020_handle_t *handle, uint64_t interruptMask);

/*!
 * @brief Disable Interrupts.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param interruptMask The mask of interrupts to clear, should be the OR'ed value of @ref pf5020_interrupt_t.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_DisableInterrupts(pf5020_handle_t *handle, uint64_t interruptMask);

/*!
 * @brief Get latched interrupts.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param interrptLatched Pointer to store the latched interrupt value.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_GetInterruptLatchStatus(pf5020_handle_t *handle, uint64_t *interrptLatched);

/*!
 * @brief Clear latched interrupts.
 *
 * @param handle The pointer to @ref pf5020_handle_t structure.
 * @param interruptMask The mask of interrupts to clear, should be the OR'ed value of @ref pf5020_interrupt_t.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_ClearInterruptStatus(pf5020_handle_t *handle, uint64_t interruptMask);

/*! @} */

#endif /* _FSL_PF5020_H_ */
