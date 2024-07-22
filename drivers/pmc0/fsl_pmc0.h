/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_PMC0_H_
#define FSL_PMC0_H_

#include "fsl_common.h"

/*! @addtogroup pmc0 */
/*! @{ */

/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.pmc0"
#endif

/*! @name Driver version */
/*! @{ */
/*! @brief PMC 0 driver version */
#define FSL_PMC0_DRIVER_VERSION (MAKE_VERSION(2, 1, 1)
/*! @} */

/*!
 * @brief MAX valid values of Core Regulator Voltage Level
 */
#define CORE_REGULATOR_VOLT_LEVEL_MAX 50U

/*!
 * @brief High Voltage Detect Monitor Select
 */
typedef enum _pmc0_high_volt_detect_monitor_select
{
    kPMC0_HighVoltDetectLowPowerMonitor  = 0U, /*!< LP monitor is selected. */
    kPMC0_HighVoltDetectHighPowerMonitor = 1U  /*!< HP monitor is selected. */
} pmc0_high_volt_detect_monitor_select_t;

/*!
 * @brief Low Voltage Detect Monitor Select
 */
typedef enum _pmc0_low_volt_detect_monitor_select
{
    kPMC0_LowVoltDetectLowPowerMonitor  = 0U, /*!< LP monitor is selected. */
    kPMC0_LowVoltDetectHighPowerMonitor = 1U  /*!< HP monitor is selected. */
} pmc0_low_volt_detect_monitor_select_t;

/*!
 * @brief Core Regulator Select
 */
typedef enum _pmc0_core_regulator_select
{
    kPMC0_CoreLowPowerRegulator  = 0U, /*!< Core LP regulator is selected. */
    kPMC0_CoreHighPowerRegulator = 1U  /*!< Core HP regulator is selected. */
} pmc0_core_regulator_select_t;

/*!
 * @brief Array Regulator Select
 */
typedef enum _pmc0_array_regulator_select
{
    kPMC0_ArrayLowPowerRegulator  = 0U, /*!< Array LP regulator is selected. */
    kPMC0_ArrayHighPowerRegulator = 1U  /*!< Array HP regulator is selected. */
} pmc0_array_regulator_select_t;

/*!
 * @brief VLLS mode array Regulator Select
 */
typedef enum _pmc0_vlls_array_regulator_select
{
    kPMC0_VllsArrayRegulatorOff = 0U, /*!< Array regulator is selected OFF. This is selectable only for VLLS mode. */
    kPMC0_VllsArrayLowPowerRegulator  = 2U, /*!< Array LP regulator is selected. */
    kPMC0_VllsArrayHighPowerRegulator = 3U  /*!< Array HP regulator is selected. */
} pmc0_vlls_array_regulator_select_t;

/*!
 * @brief FBB P-Well voltage level select
 */
typedef enum _pmc0_fbb_p_well_voltage_level_select
{
    kPMC0_FbbPWellNoBiasCondition     = 0U, /*!< No BIAS condition is selected. */
    kPMC0_FbbPWellVoltageLevelAt50Mv  = 1U, /*!< Voltage level at 50mV is selected. */
    kPMC0_FbbPWellVoltageLevelAt150Mv = 2U, /*!< Voltage level at 150mV is selected. */
    kPMC0_FbbPWellVoltageLevelAt100Mv = 3U, /*!< Voltage level at 100mV is selected. */
    kPMC0_FbbPWellVoltageLevelAt350Mv = 4U, /*!< Voltage level at 350mV is selected. */
    kPMC0_FbbPWellVoltageLevelAt300Mv = 5U, /*!< Voltage level at 300mV is selected. */
    kPMC0_FbbPWellVoltageLevelAt200Mv = 6U, /*!< Voltage level at 200mV is selected. */
    kPMC0_FbbPWellVoltageLevelAt250Mv = 7U, /*!< Voltage level at 250mV is selected. */
} pmc0_fbb_p_well_voltage_level_select_t;

/*!
 * @brief FBB N-Well voltage level select
 */
typedef enum _pmc0_fbb_n_well_voltage_level_select
{
    kPMC0_FbbNWellNoBiasCondition          = 0U, /*!< No BIAS condition is selected. */
    kPMC0_FbbNWellVoltageLevelAtMinus50Mv  = 1U, /*!< Voltage level at -50mV is selected. */
    kPMC0_FbbNWellVoltageLevelAtMinus150Mv = 2U, /*!< Voltage level at -150mV is selected. */
    kPMC0_FbbNWellVoltageLevelAtMinus100Mv = 3U, /*!< Voltage level at -100mV is selected. */
    kPMC0_FbbNWellVoltageLevelAtMinus350Mv = 4U, /*!< Voltage level at -350mV is selected. */
    kPMC0_FbbNWellVoltageLevelAtMinus300Mv = 5U, /*!< Voltage level at -300mV is selected. */
    kPMC0_FbbNWellVoltageLevelAtMinus200Mv = 6U, /*!< Voltage level at -200mV is selected. */
    kPMC0_FbbNWellVoltageLevelAtMinus250Mv = 7U, /*!< Voltage level at -250mV is selected. */
} pmc0_fbb_n_well_voltage_level_select_t;

/*!
 * @brief RBB P-Well voltage level select
 */
typedef enum _pmc0_rbb_p_well_voltage_level_select
{
    kPMC0_RBBPWellVoltageLevelAtMinus0_5V = 0U, /*!< Voltage level at -0.5V is selected. */
    kPMC0_RBBPWellVoltageLevelAtMinus0_6V = 1U, /*!< Voltage level at -0.6V is selected. */
    kPMC0_RBBPWellVoltageLevelAtMinus0_7V = 2U, /*!< Voltage level at -0.7V is selected. */
    kPMC0_RBBPWellVoltageLevelAtMinus0_8V = 3U, /*!< Voltage level at -0.8V is selected. */
    kPMC0_RBBPWellVoltageLevelAtMinus0_9V = 4U, /*!< Voltage level at -0.9V is selected. */
    kPMC0_RBBPWellVoltageLevelAtMinus1_0V = 5U, /*!< Voltage level at -1.0V is selected. */
    kPMC0_RBBPWellVoltageLevelAtMinus1_1V = 6U, /*!< Voltage level at -1.1V is selected. */
    kPMC0_RBBPWellVoltageLevelAtMinus1_2V = 7U, /*!< Voltage level at -1.2V is selected. */
    kPMC0_RBBPWellVoltageLevelAtMinus1_3V = 8U, /*!< Voltage level at -1.3V is selected. */
} pmc0_rbb_p_well_voltage_level_select_t;

/*!
 * @brief RBB N-Well voltage level select
 */
typedef enum _pmc0_rbb_n_well_voltage_level_select
{
    kPMC0_RBBNWellVoltageLevelAt0_5V = 0U, /*!< Voltage level at 0.5V is selected. */
    kPMC0_RBBNWellVoltageLevelAt0_6V = 1U, /*!< Voltage level at 0.6V is selected. */
    kPMC0_RBBNWellVoltageLevelAt0_7V = 2U, /*!< Voltage level at 0.7V is selected. */
    kPMC0_RBBNWellVoltageLevelAt0_8V = 3U, /*!< Voltage level at 0.8V is selected. */
    kPMC0_RBBNWellVoltageLevelAt0_9V = 4U, /*!< Voltage level at 0.9V is selected. */
    kPMC0_RBBNWellVoltageLevelAt1_0V = 5U, /*!< Voltage level at 1.0V is selected. */
    kPMC0_RBBNWellVoltageLevelAt1_1V = 6U, /*!< Voltage level at 1.1V is selected. */
    kPMC0_RBBNWellVoltageLevelAt1_2V = 7U, /*!< Voltage level at 1.2V is selected. */
    kPMC0_RBBNWellVoltageLevelAt1_3V = 8U, /*!< Voltage level at 1.3V is selected. */
} pmc0_rbb_n_well_voltage_level_select_t;

/*!
 * @brief PMC 0 status flags
 */
enum _pmc0_status_flags
{
    kPMC0_LowVoltDetectEventFlag =
        PMC0_STATUS_LVDF_MASK, /*!< 1.2V Low-Voltage Detector Flag, sets when low-voltage event was detected. */
    kPMC0_LowVoltDetectValueFlag = PMC0_STATUS_LVDV_MASK, /*!< 1.2V Low-Voltage Detector Value, sets when current
                                                                value of the 1.2V LVD monitor output is 1. */
    kPMC0_HighVoltDetectEventFlag =
        PMC0_STATUS_HVDF_MASK, /*!< 1.8V High-Voltage Detector Flag, sets when high-voltage event was detected. */
    kPMC0_HighVoltDetectValueFlag = PMC0_STATUS_HVDV_MASK, /*!< 1.8V High-Voltage Detector Value, sets when current
                                                                 value of the 1.8V HVD monitor output is 1. */
    kPMC0_CoreRegulatorVoltLevelFlag = PMC0_STATUS_COREVLF_MASK, /*!< Core Regulator Voltage Level Flag, sets when core
                                                                    regulator voltage level is changing (not stable). */
    kPMC0_SramFlag =
        PMC0_STATUS_SRAMF_MASK,    /*!< SRAM Flag, sets when a change mode request is being processed in the SRAMs. */
    kPMC0_PMC1VoltageSourceFlag =
        PMC0_STATUS_PMC1VSRC_MASK, /*!< This flag indicates what is the voltage source selected to supply the PMC 1
                                        and where the sense point of the PMC 1's LVD/HVD is placed. '0' means internal
                                        LDO supplies the PMC 1. '1' means external PMIC supplies the PMC 1. */
};

/*!
 * @brief PMC 0 power mode status flags.
 */
enum _pmc0_power_mode_status_flags
{
    kPMC0_HSRUNModeStatusFlags = 0U, /*!< The PMC 0 is in HSRUN mode. */
    kPMC0_RUNModeStatusFlags   = 1U, /*!< The PMC 0 is in RUN mode. */
    kPMC0_STOPModeStatusFlags  = 2U, /*!< The PMC 0 is in STOP mode. */
    kPMC0_VLPRModeStatusFlags  = 3U, /*!< The PMC 0 is in VLPR mode. */
    kPMC0_VLPSModeStatusFlags  = 4U, /*!< The PMC 0 is in VLPS mode. */
    kPMC0_LLSModeStatusFlags   = 5U, /*!< The PMC 0 is in LLSM mode. */
    kPMC0_VLLSModeStatusFlags  = 6U, /*!< The PMC 0 is in VLLS mode. */
};

/*!
 * @brief PMC 0 HSRUN mode configuration.
 */
typedef struct _pmc0_hsrun_mode_config
{
    uint32_t : 16;                       /*!< Reserved. */
    uint32_t coreRegulatorVoltLevel : 6; /*!< Core Regulator Voltage Level. */
    uint32_t : 2;                        /*!< Reserved. */
    uint32_t enableForwardBias : 1;      /*!< Enable forward bias. */
    uint32_t : 7;                        /*!< Reserved. */
} pmc0_hsrun_mode_config_t;

/*!
 * @brief PMC 0 RUN mode configuration.
 */
typedef struct _pmc0_run_mode_config
{
    uint32_t : 16;                       /*!< Reserved. */
    uint32_t coreRegulatorVoltLevel : 6; /*!< Core Regulator Voltage Level. */
    uint32_t : 10;                       /*!< Reserved. */
} pmc0_run_mode_config_t;

/*!
 * @brief PMC 0 VLPR mode configuration.
 */
typedef struct _pmc0_vlpr_mode_config
{
    uint32_t arrayRegulatorSelect : 1;   /*!< Array Regulator Select. @ref pmc0_array_regulator_select_t*/
    uint32_t : 1;                        /*!< Reserved. */
    uint32_t coreRegulatorSelect : 1;    /*!< Core Regulator Select. @ref pmc0_core_regulator_select_t*/
    uint32_t : 1;                        /*!< Reserved. */
    uint32_t lvdMonitorSelect : 1;       /*!< 1.2V LVD Monitor Select. @ref pmc0_low_volt_detect_monitor_select_t */
    uint32_t hvdMonitorSelect : 1;       /*!< 1.2V HVD Monitor Select. @ref pmc0_high_volt_detect_monitor_select_t */
    uint32_t : 1;                        /*!< Reserved. */
    uint32_t enableForceHpBandgap : 1;   /*!< Enable force HP band-gap. */
    uint32_t : 8;                        /*!< Reserved. */
    uint32_t coreRegulatorVoltLevel : 6; /*!< Core Regulator Voltage Level. */
    uint32_t : 6;                        /*!< Reserved. */
    uint32_t enableReverseBackBias : 1;  /*!< Enable reverse back bias. */
    uint32_t : 3;                        /*!< Reserved. */
} pmc0_vlpr_mode_config_t;

/*!
 * @brief PMC 0 STOP mode configuration.
 */
typedef struct _pmc0_stop_mode_config
{
    uint32_t : 16;                       /*!< Reserved. */
    uint32_t coreRegulatorVoltLevel : 6; /*!< Core Regulator Voltage Level. */
    uint32_t : 10;                       /*!< Reserved. */
} pmc0_stop_mode_config_t;

/*!
 * @brief PMC 0 VLPS mode configuration.
 */
typedef struct _pmc0_vlps_mode_config
{
    uint32_t arrayRegulatorSelect : 1;   /*!< Array Regulator Select. @ref pmc0_array_regulator_select_t*/
    uint32_t : 1;                        /*!< Reserved. */
    uint32_t coreRegulatorSelect : 1;    /*!< Core Regulator Select. @ref pmc0_core_regulator_select_t*/
    uint32_t : 1;                        /*!< Reserved. */
    uint32_t lvdMonitorSelect : 1;       /*!< 1.2V LVD Monitor Select. @ref pmc0_low_volt_detect_monitor_select_t */
    uint32_t hvdMonitorSelect : 1;       /*!< 1.2V HVD Monitor Select. @ref pmc0_high_volt_detect_monitor_select_t */
    uint32_t : 1;                        /*!< Reserved. */
    uint32_t enableForceHpBandgap : 1;   /*!< Enable force HP band-gap. */
    uint32_t : 8;                        /*!< Reserved. */
    uint32_t coreRegulatorVoltLevel : 6; /*!< Core Regulator Voltage Level. */
    uint32_t : 6;                        /*!< Reserved. */
    uint32_t enableReverseBackBias : 1;  /*!< Enable reverse back bias. */
    uint32_t : 3;                        /*!< Reserved. */
} pmc0_vlps_mode_config_t;

/*!
 * @brief PMC 0 LLS mode configuration.
 */
typedef struct _pmc0_lls_mode_config
{
    uint32_t arrayRegulatorSelect : 1;   /*!< Array Regulator Select. @ref pmc0_array_regulator_select_t*/
    uint32_t : 1;                        /*!< Reserved. */
    uint32_t coreRegulatorSelect : 1;    /*!< Core Regulator Select. @ref pmc0_core_regulator_select_t*/
    uint32_t : 1;                        /*!< Reserved. */
    uint32_t lvdMonitorSelect : 1;       /*!< 1.2V LVD Monitor Select. @ref pmc0_low_volt_detect_monitor_select_t */
    uint32_t hvdMonitorSelect : 1;       /*!< 1.2V HVD Monitor Select. @ref pmc0_high_volt_detect_monitor_select_t */
    uint32_t : 1;                        /*!< Reserved. */
    uint32_t enableForceHpBandgap : 1;   /*!< Enable force HP band-gap. */
    uint32_t : 8;                        /*!< Reserved. */
    uint32_t coreRegulatorVoltLevel : 6; /*!< Core Regulator Voltage Level. */
    uint32_t : 6;                        /*!< Reserved. */
    uint32_t enableReverseBackBias : 1;  /*!< Enable reverse back bias. */
    uint32_t : 3;                        /*!< Reserved. */
} pmc0_lls_mode_config_t;

/*!
 * @brief PMC 0 VLLS mode configuration.
 */
typedef struct _pmc0_vlls_mode_config
{
    uint32_t arrayRegulatorSelect : 2; /*!< Array Regulator Select. @ref pmc0_vlls_array_regulator_select_t */
    uint32_t : 2;                      /*!< Reserved. */
    uint32_t lvdMonitorSelect : 1;     /*!< 1.2V LVD Monitor Select. @ref pmc0_low_volt_detect_monitor_select_t */
    uint32_t hvdMonitorSelect : 1;     /*!< 1.2V HVD Monitor Select. @ref pmc0_high_volt_detect_monitor_select_t */
    uint32_t : 1;                      /*!< Reserved. */
    uint32_t enableForceHpBandgap : 1; /*!< Enable force HP band-gap. */
    uint32_t : 24;                     /*!< Reserved. */
} pmc0_vlls_mode_config_t;

/*!
 * @brief PMC 0 bias configuration.
 */
typedef struct _pmc0_bias_config
{
    uint32_t RBBNWellVoltageLevelSelect : 4;
    uint32_t : 4;                            /*!< Reserved. */
    uint32_t RBBPWellVoltageLevelSelect : 4; /*!< Select PMC0 RBB P-Well voltage level. @ref
                                                pmc0_rbb_p_well_voltage_level_select_t */
    uint32_t : 3;                            /*!< Reserved. */
    uint32_t DisableRBBPullDown : 1; /*!< Disable RBB pull-down. '1' means to disable pull-down. '0' means to enable
                                        pull-down.*/
    uint32_t FBBNWellVoltageLevelSelect : 4; /*!< Select PMC0 FBB N-Well voltage level. @ref
                                                pmc0_fbb_n_well_voltage_level_select_t */
    uint32_t : 4;                            /*!< Reserved. */
    uint32_t FBBPWellVoltageLevelSelect : 4; /*!< Select PMC0 FBB P-Well voltage level. @ref
                                                pmc0_fbb_p_well_voltage_level_select_t */
    uint32_t : 4;                            /*!< Reserved. */
} pmc0_bias_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*! @name Power Management Controller Control APIs*/
/*! @{ */

/*!
 * @brief Configure the HSRUN power mode.
 *
 * This function configures the HSRUN power mode, including the core regulator
 * voltage Level setting, enable forward bias or not.
 *
 * @param config  Low-Voltage detect configuration structure.
 */
static inline void PMC0_ConfigureHsrunMode(const pmc0_hsrun_mode_config_t *config)
{
    /*
     * The valid values of Core Regulator Voltage Level are between 0 and 50.
     * These values correspond to a valid range of 0.596V to 1.138V with resolution of 10.83mV.
     * The reset value correspond to 0.9V.
     */
    assert(config);
    assert(config->coreRegulatorVoltLevel <= CORE_REGULATOR_VOLT_LEVEL_MAX);

    /* Wait until COREVLF is cleared. */
    while ((PMC0->STATUS & PMC0_STATUS_COREVLF_MASK) == PMC0_STATUS_COREVLF_MASK)
    {
    }

    PMC0->HSRUN = (*((const uint32_t *)((const void *)config))) & (PMC0_HSRUN_COREREGVL_MASK | PMC0_HSRUN_FBBEN_MASK);

    /* Wait until COREVLF is cleared. */
    while ((PMC0->STATUS & PMC0_STATUS_COREVLF_MASK) == PMC0_STATUS_COREVLF_MASK)
    {
    }
}

/*!
 * @brief Configure the RUN power mode.
 *
 * This function configures the RUN power mode, including the core regulator
 * voltage Level setting.
 *
 * @param config  Low-Voltage detect configuration structure.
 */
static inline void PMC0_ConfigureRunMode(const pmc0_run_mode_config_t *config)
{
    /*
     * The valid values of Core Regulator Voltage Level are between 0 and 50.
     * These values correspond to a valid range of 0.596V to 1.138V with resolution of 10.83mV.
     * The reset value correspond to 0.9V.
     */
    assert(config);
    assert(config->coreRegulatorVoltLevel <= CORE_REGULATOR_VOLT_LEVEL_MAX);

    /* Wait until COREVLF is cleared. */
    while ((PMC0->STATUS & PMC0_STATUS_COREVLF_MASK) == PMC0_STATUS_COREVLF_MASK)
    {
    }

    PMC0->RUN = (*((const uint32_t *)((const void *)config))) & PMC0_RUN_COREREGVL_MASK;

    /* Wait until COREVLF is cleared. */
    while ((PMC0->STATUS & PMC0_STATUS_COREVLF_MASK) == PMC0_STATUS_COREVLF_MASK)
    {
    }
}

/*!
 * @brief Configure the VLPR power mode.
 *
 * This function configures the VLPR power mode, including the core regulator
 * voltage Level setting, enable reverse back bias or not, turn on force HP
 * band-gap or not, select of HVD/LVD monitor and select of core/array regulator.
 *
 * @param config  Low-Voltage detect configuration structure.
 */
static inline void PMC0_ConfigureVlprMode(const pmc0_vlpr_mode_config_t *config)
{
    /*
     * The valid values of Core Regulator Voltage Level are between 0 and 50.
     * These values correspond to a valid range of 0.596V to 1.138V with resolution of 10.83mV.
     * The reset value correspond to 0.704V.
     */
    assert(config);
    assert(config->coreRegulatorVoltLevel <= CORE_REGULATOR_VOLT_LEVEL_MAX);

    PMC0->VLPR = (*((const uint32_t *)((const void *)config))) &
                 (PMC0_VLPR_ARRAYREG_MASK | PMC0_VLPR_COREREG_MASK | PMC0_VLPR_MONLVD_MASK | PMC0_VLPR_MONLVD_MASK |
                  PMC0_VLPR_FBGHP_MASK | PMC0_VLPR_COREREGVL_MASK | PMC0_VLPR_RBBEN_MASK);
}

/*!
 * @brief Configure the STOP power mode.
 *
 * This function configures the STOP power mode, including the core regulator
 * voltage Level setting.
 *
 * @param config  Low-Voltage detect configuration structure.
 */
static inline void PMC0_ConfigureStopMode(const pmc0_stop_mode_config_t *config)
{
    /*
     * The valid values of Core Regulator Voltage Level are between 0 and 50.
     * These values correspond to a valid range of 0.596V to 1.138V with resolution of 10.83mV.
     * The reset value correspond to 0.9V.
     */
    assert(config);
    assert(config->coreRegulatorVoltLevel <= CORE_REGULATOR_VOLT_LEVEL_MAX);

    PMC0->STOP = (*((const uint32_t *)((const void *)config))) & PMC0_STOP_COREREGVL_MASK;
}

/*!
 * @brief Configure the VLPS power mode.
 *
 * This function configures the VLPS power mode, including the core regulator
 * voltage Level setting, enable reverse back bias or not, turn on force HP
 * band-gap or not, select of HVD/LVD monitor and select of core/array regulator.
 *
 * @param config  Low-Voltage detect configuration structure.
 */
static inline void PMC0_ConfigureVlpsMode(const pmc0_vlps_mode_config_t *config)
{
    /*
     * The valid values of Core Regulator Voltage Level are between 0 and 50.
     * These values correspond to a valid range of 0.596V to 1.138V with resolution of 10.83mV.
     * The reset value correspond to 0.704V.
     */
    assert(config);
    assert(config->coreRegulatorVoltLevel <= CORE_REGULATOR_VOLT_LEVEL_MAX);

    PMC0->VLPS = (*((const uint32_t *)((const void *)config))) &
                 (PMC0_VLPS_ARRAYREG_MASK | PMC0_VLPS_COREREG_MASK | PMC0_VLPS_MONLVD_MASK | PMC0_VLPS_MONLVD_MASK |
                  PMC0_VLPS_FBGHP_MASK | PMC0_VLPS_COREREGVL_MASK | PMC0_VLPS_RBBEN_MASK);
}

/*!
 * @brief Configure the LLS power mode.
 *
 * This function configures the LLS power mode, including the core regulator
 * voltage Level setting, enable reverse back bias or not, turn on force HP
 * band-gap or not, select of HVD/LVD monitor and select of core/array regulator.
 *
 * @param config  Low-Voltage detect configuration structure.
 */
static inline void PMC0_ConfigureLlsMode(const pmc0_lls_mode_config_t *config)
{
    /*
     * The valid values of Core Regulator Voltage Level are between 0 and 50.
     * These values correspond to a valid range of 0.596V to 1.138V with resolution of 10.83mV.
     * The reset value correspond to 0.704V.
     */
    assert(config);
    assert(config->coreRegulatorVoltLevel <= CORE_REGULATOR_VOLT_LEVEL_MAX);

    PMC0->LLS = (*((const uint32_t *)((const void *)config))) &
                (PMC0_LLS_ARRAYREG_MASK | PMC0_LLS_COREREG_MASK | PMC0_LLS_MONLVD_MASK | PMC0_LLS_MONLVD_MASK |
                 PMC0_LLS_FBGHP_MASK | PMC0_LLS_COREREGVL_MASK | PMC0_LLS_RBBEN_MASK);
}

/*!
 * @brief Configure the VLLS power mode.
 *
 * This function configures the VLLS power mode, including turn on force HP
 * band-gap or not, select of HVD/LVD monitor and select of core/array regulator.
 *
 * The select of array regulator is different from the other mode configurations.
 * PMC 0 VLLS config has three array regulator select options where the others have only the latter two,
 * see @ref pmc0_vlls_array_regulator_select_t.
 * Three array regulator select options in PMC 0 VLLS config are shown below:
 * - Regulator is off (diffrentiator)
 * - LP Regulator is on
 * - HP Regulator is on
 *
 * @param config  Low-Voltage detect configuration structure.
 */
static inline void PMC0_ConfigureVllsMode(const pmc0_vlls_mode_config_t *config)
{
    assert(config);

    PMC0->VLLS = (*((const uint32_t *)((const void *)config))) &
                 (PMC0_VLLS_ARRAYREG_MASK | PMC0_VLLS_MONLVD_MASK | PMC0_VLLS_MONLVD_MASK | PMC0_VLLS_FBGHP_MASK);
}

/*!
 * @brief Get current power mode of PMC 0.
 *
 * @code
 *      if(kPMC0_HSRUNModeStatusFlags == PMC0_GetPMC0PowerModeStatusFlags(void))
 *      {
 *           ...
 *      }
 * @endcode
 *
 * @return PMC 0 current power mode status flags in the _pmc0_power_mode_status_flags.
 *
 */
static inline uint32_t PMC0_GetPMC0PowerModeStatusFlags(void)
{
    return (PMC0->PM_STAT & PMC0_PM_STAT_PMC0CURRPM_MASK) >> PMC0_PM_STAT_PMC0CURRPM_SHIFT;
}

/*!
 * @brief Get the status of PMC 0 power mode transition.
 *
 * @return If return 'true', which means PMC 0 is in a power mode transition.
 *         If return 'false', which means PMC 0 is not in a power mode transition.
 */
static inline bool PMC0_GetPMC0PowerTransitionStatus(void)
{
    if ((PMC0_PM_STAT_PMC0TRANPM_MASK & PMC0->PM_STAT) == PMC0_PM_STAT_PMC0TRANPM_MASK)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*!
 * @brief Get current power mode of PMC 1.
 *
 * @code
 *      if(kPMC0_HSRUNModeStatusFlags == PMC0_GetPMC1PowerModeStatusFlags(void))
 *      {
 *           ...
 *      }
 * @endcode
 *
 * @return PMC 1 current power mode status flags in the _pmc0_power_mode_status_flags.
 *
 */
static inline uint32_t PMC0_GetPMC1PowerModeStatusFlags(void)
{
    return (PMC0->PM_STAT & PMC0_PM_STAT_PMC1CURRPM_MASK) >> PMC0_PM_STAT_PMC1CURRPM_SHIFT;
}

/*!
 * @brief Get the status of PMC 1 power mode transition.
 *
 * @return If return 'true', which means PMC 1 is in a power mode transition.
 *         If return 'false', which means PMC 1 is not in a power mode transition.
 */
static inline bool PMC0_GetPMC1PowerTransitionStatus(void)
{
    if ((PMC0_PM_STAT_PMC1TRANPM_MASK & PMC0->PM_STAT) == PMC0_PM_STAT_PMC1TRANPM_MASK)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*!
 * @brief Gets PMC 0 status flags.
 *
 * This function gets all PMC 0 status flags. The flags are returned as the logical
 * OR value of the enumerators @ref _pmc0_status_flags. To check for a specific status,
 * compare the return value with enumerators in the @ref _pmc0_status_flags.
 * For example, to check whether core regulator voltage level is changing:
 * @code
 *     if (kPMC0_CoreRegulatorVoltLevelFlag & PMC0_GetStatusFlags(void))
 *     {
 *         ...
 *     }
 * @endcode
 *
 * @return PMC 0 status flags which are ORed by the enumerators in the _pmc0_status_flags.
 */
static inline uint32_t PMC0_GetStatusFlags(void)
{
    return PMC0->STATUS;
}

/*!
 * @brief Enables the 1.2V Low-Voltage Detector interrupt.
 *
 * This function enables the 1.2V Low-Voltage Detector interrupt.
 *
 */
static inline void PMC0_EnableLowVoltDetectInterrupt(void)
{
    PMC0->CTRL |= PMC0_CTRL_LVDIE_MASK;
}

/*!
 * @brief Disables the 1.2V Low-Voltage Detector interrupt.
 *
 * This function disables the 1.2V Low-Voltage Detector interrupt.
 *
 */
static inline void PMC0_DisableLowVoltDetectInterrupt(void)
{
    PMC0->CTRL &= ~PMC0_CTRL_LVDIE_MASK;
}

/*!
 * @brief Clears the 1.2V Low-Voltage Detector flag.
 *
 * This function enables the 1.2V Low-Voltage Detector flag.
 *
 */
static inline void PMC0_ClearLowVoltDetectFlag(void)
{
    PMC0->CTRL |= PMC0_CTRL_LVDACK_MASK;
}

/*!
 * @brief Enables the 1.8V High-Voltage Detector interrupt.
 *
 * This function enables the 1.8V High-Voltage Detector interrupt.
 *
 */
static inline void PMC0_EnableHighVoltDetectInterrupt(void)
{
    PMC0->CTRL |= PMC0_CTRL_HVDIE_MASK;
}

/*!
 * @brief Disables the 1.8V High-Voltage Detector interrupt.
 *
 * This function disables the 1.8V High-Voltage Detector interrupt.
 *
 */
static inline void PMC0_DisableHighVoltDetectInterrupt(void)
{
    PMC0->CTRL &= ~PMC0_CTRL_HVDIE_MASK;
}

/*!
 * @brief Clears the 1.8V High-Voltage Detector flag.
 *
 * This function enables the 1.8V High-Voltage Detector flag.
 *
 */
static inline void PMC0_ClearHighVoltDetectFlag(void)
{
    PMC0->CTRL |= PMC0_CTRL_HVDACK_MASK;
}

/*!
 * @brief Enables the 1.2V Low-Voltage Detector reset.
 *
 * This function enables 1.2V Low-Voltage Detector reset.
 *
 * @param enable Switcher of 1.2V Low-Voltage Detector reset feature. "true" means to enable, "false" means not.
 */
static inline void PMC0_EnableLowVoltDetectReset(bool enable)
{
    if (enable)
    {
        PMC0->CTRL |= PMC0_CTRL_LVDRE_MASK;
    }
    else
    {
        PMC0->CTRL &= ~PMC0_CTRL_LVDRE_MASK;
    }
}

/*!
 * @brief Enables the 1.8V High-Voltage Detector reset.
 *
 * This function enables 1.8V High-Voltage Detector reset.
 *
 * @param enable Switcher of 1.8V High-Voltage Detector reset feature. "true" means to enable, "false" means not.
 */
static inline void PMC0_EnableHighVoltDetectReset(bool enable)
{
    if (enable)
    {
        PMC0->CTRL |= PMC0_CTRL_HVDRE_MASK;
    }
    else
    {
        PMC0->CTRL &= ~PMC0_CTRL_HVDRE_MASK;
    }
}

/*!
 * @brief Releases/clears the isolation in the PADS.
 *
 * This function releases/clears the isolation in the PADS.
 *
 * The isolation in the pads only will be asserted during LLS/VLLS. On LLS exit, the isolation will
 * release automatically. ISOACK must be set after a VLLS to RUN mode transition has completed.
 *
 */
static inline void PMC0_ClearPadsIsolation(void)
{
    PMC0->CTRL |= PMC0_CTRL_ISOACK_MASK;
}

/*!
 * @brief Powers on PMC 1.
 *
 * This function powers on PMC 1.
 *
 * When this bit field is asserted the PMC 1 is powered on. This bit would take action only once.
 * This bit will be rearmed after a POR event only.
 * NOTE: USB PHY-related interrupt (NVIC/GIC) and wake-up channels (AWIC/WKPU) must be disabled before turning PMC1 on.
 *
 */
static inline void PMC0_PowerOnPmc1(void)
{
    PMC0->CTRL |= PMC0_CTRL_PMC1ON_MASK;
}

/*!
 * @brief Enables to wait LDO OK signal.
 *
 * This function enables to wait LDO OK signal.
 *
 * @param enable Switcher of wait LDO OK signal feature. "true" means to enable, "false" means not.
 */
static inline void PMC0_EnableWaitLdoOkSignal(bool enable)
{
    if (enable)
    {
        PMC0->CTRL &= ~PMC0_CTRL_LDOOKDIS_MASK;
    }
    else
    {
        PMC0->CTRL |= PMC0_CTRL_LDOOKDIS_MASK;
    }
}

/*!
 * @brief Enables PMC 1 LDO Regulator.
 *
 * This function enables PMC 1 LDO Regulator.
 *
 * @param enable Switcher of PMC 1 LDO Regulator. "true" means to enable, "false" means not.
 */
static inline void PMC0_EnablePmc1LdoRegulator(bool enable)
{
    if (enable)
    {
        PMC0->CTRL |= PMC0_CTRL_LDOEN_MASK;
    }
    else
    {
        PMC0->CTRL &= ~PMC0_CTRL_LDOEN_MASK;
    }
}

/*!
 * @brief Enable the PMC 1 RBB(reverse back bias) mode.
 *
 * This function enables PMC1 RBB mode. Since this circuit when enabled has current consumption.
 * It is recommended to use it just in high temperatures when the leakage reduction is much higher
 * than the current consumption.
 *
 * @param enable Switcher of PMC1 RBB mode. "true" means to enable, "false" means disable.
 */
static inline void PMC0_EnablePmc1RBBMode(bool enable)
{
    if (enable)
    {
        PMC0->ACTRL |= PMC0_ACTRL_SWRBBEN_MASK;
    }
    else
    {
        PMC0->ACTRL &= ~PMC0_ACTRL_SWRBBEN_MASK;
    }
}

/*!
 * @brief Configure the PMC 0 bias voltage level and enable/disable pull-down.
 *
 * This function change the RBB&FBB voltage level and RBB pull-down.
 *
 * @param config PMC 0 bias configuration structure.
 */
static inline void PMC0_SetBiasConfig(const pmc0_bias_config_t *config)
{
    assert(NULL != config);

    PMC0->BCTRL = (*((const uint32_t *)((const void *)config))) &
                  (PMC0_BCTRL_RBBNLEVEL_MASK | PMC0_BCTRL_RBBPLEVEL_MASK | PMC0_BCTRL_RBBPDDIS_MASK |
                   PMC0_BCTRL_FBBNLEVEL_MASK | PMC0_BCTRL_FBBPLEVEL_MASK);
}

/*!
 * @brief Configures PMC 0 SRAM bank power down.
 *
 * This function configures PMC 0 SRAM bank power down.
 *
 * The bit i controls the power mode of the PMC 0 SRAM bank i.
 * PMC0_SRAM_PD[i] = 1'b0 - PMC 0 SRAM bank i is not affected.
 * PMC0_SRAM_PD[i] = 1'b1 - PMC 0 SRAM bank i is in ASD or ARRAY_SHUTDOWN during all modes,
 * except VLLS. During VLLS is in POWER_DOWN mode.
 *
 * Example: Enable band 0 and 1 in ASD or ARRAY_SHUTDOWN during all modes except VLLS
 * @code
 *     PMC0_ConfigureSramBankPowerDown(0x3U);
 * @endcode
 *
 * @param bankMask The bands to enable. Logical OR of all bits of band index to enbale.
 */
static inline void PMC0_ConfigureSramBankPowerDown(uint32_t bankMask)
{
    /* Wait until SRAMF is cleared. */
    while ((PMC0->STATUS & PMC0_STATUS_SRAMF_MASK) == PMC0_STATUS_SRAMF_MASK)
    {
    }

    PMC0->SRAMCTRL_0 = PMC0_SRAMCTRL_0_SRAM_PD(bankMask);

    /* Wait until SRAMF is cleared. */
    while ((PMC0->STATUS & PMC0_STATUS_SRAMF_MASK) == PMC0_STATUS_SRAMF_MASK)
    {
    }
}

/*!
 * @brief Configures PMC 0 SRAM bank power down in stop modes.
 *
 * This function configures PMC 0 SRAM bank power down in stop modes.
 *
 * The bit i controls the PMC 0 SRAM bank i.
 * PMC0_SRAM_PDS[i] = 1'b0 - PMC 0 SRAM bank i is not affected.
 * PMC0_SRAM_PDS[i] = 1'b1 - PMC 0 SRAM bank i is in ASD or ARRAY_SHUTDOWN mode during
 * STOP, VLPS and LLS modes. During VLLS is in POWER_DOWN mode.
 *
 * Example: Enable band 0 and 1 in ASD or ARRAY_SHUTDOWN during STOP, VLPS and LLS modes
 * @code
 *     PMC0_ConfigureSramBankPowerDownStopMode(0x3U);
 * @endcode
 *
 * @param bankMask The bands to enable. Logical OR of all bits of band index to enbale.
 */
static inline void PMC0_ConfigureSramBankPowerDownStopMode(uint32_t bankMask)
{
    PMC0->SRAMCTRL_1 = PMC0_SRAMCTRL_1_SRAM_PDS(bankMask);
}

/*!
 * @brief Configures PMC 0 SRAM bank power down in Standby Mode.
 *
 * This function configures PMC 0 SRAM bank power down in Standby Mode.
 *
 * The bit i controls the PMC 0 SRAM bank i.
 * PMC0_SRAM_STDY[i] = 1'b0 - PMC 0 SRAM bank i is not affected.
 * PMC0_SRAM_STDY[i] = 1'b1 - PMC 0 SRAM bank i is in STANDBY mode during all modes (except VLLS and LLS).
 *
 * Example: Enable band 0 and 1 in STANDBY mode except VLLS and LLS
 * @code
 *     PMC0_ConfigureSramBankPowerDownStandbyMode(0x3U);
 * @endcode
 *
 * @param bankMask The bands to enable. Logical OR of all bits of band index to enbale.
 */
static inline void PMC0_ConfigureSramBankPowerDownStandbyMode(uint32_t bankMask)
{
    PMC0->SRAMCTRL_2 = PMC0_SRAMCTRL_2_SRAM_STDY(bankMask);
}

/*!
 * @brief Enable/disable internal temperature sensor.
 *
 * @param enable Used to enable/disable internal temperature sensor.
 *          - \b true Enable internal temperature sensor.
 *          - \b false Disable internal temperature sensor.
 */
static inline void PMC0_EnableTemperatureSensor(bool enable)
{
    if (enable)
    {
        PMC0->ACTRL |= PMC0_ACTRL_TSENSEN_MASK;
    }
    else
    {
        PMC0->ACTRL &= ~PMC0_ACTRL_TSENSEN_MASK;
    }
}

/*!
 * @brief Set temperature sensor mode.
 *
 * @param mode The temperature sensor mode to set.
 */
static inline void PMC0_SetTemperatureSensorMode(uint8_t mode)
{
    PMC0->ACTRL = (PMC0->ACTRL & ~PMC0_ACTRL_TSENSM_MASK) | PMC0_ACTRL_TSENSM(mode);
}

/*! @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* FSL_PMC_H_*/
