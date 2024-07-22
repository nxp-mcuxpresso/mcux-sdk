/*
 * Copyright 2019-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_SPC_H_
#define FSL_SPC_H_
#include "fsl_common.h"

/*!
 * @addtogroup spc
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define SPC_EVD_CFG_REG_EVDISO_SHIFT   0UL
#define SPC_EVD_CFG_REG_EVDLPISO_SHIFT 8UL
#define SPC_EVD_CFG_REG_EVDSTAT_SHIFT  16UL

#define SPC_EVD_CFG_REG_EVDISO(x)   ((uint32_t)(x) << SPC_EVD_CFG_REG_EVDISO_SHIFT)
#define SPC_EVD_CFG_REG_EVDLPISO(x) ((uint32_t)(x) << SPC_EVD_CFG_REG_EVDLPISO_SHIFT)
#define SPC_EVD_CFG_REG_EVDSTAT(x)  ((uint32_t)(x) << SPC_EVD_CFG_REG_EVDSTAT_SHIFT)

/*! @name Driver version */
/*! @{ */
/*! @brief SPC driver version 2.4.0. */
#define FSL_SPC_DRIVER_VERSION (MAKE_VERSION(2, 4, 0))
/*! @} */

/*!
 * @brief SPC status enumeration.
 */
enum
{
    kStatus_SPC_Busy =
        MAKE_STATUS(kStatusGroup_SPC, 0U), /*!< The SPC instance is busy executing any type of power mode transition. */
    kStatus_SPC_DCDCLowDriveStrengthIgnore =
        MAKE_STATUS(kStatusGroup_SPC, 1U), /*!< DCDC Low drive strength setting be ignored for LVD/HVD enabled. */
    kStatus_SPC_DCDCPulseRefreshModeIgnore = MAKE_STATUS(
        kStatusGroup_SPC, 2U), /*!< DCDC Pulse Refresh Mode drive strength setting be ignored for LVD/HVD enabled. */
    kStatus_SPC_SYSLDOOverDriveVoltageFail = MAKE_STATUS(
        kStatusGroup_SPC, 3U), /*!< SYS LDO regulate to Over drive voltage failed for SYS LDO HVD must be disabled. */
    kStatus_SPC_SYSLDOLowDriveStrengthIgnore = MAKE_STATUS(
        kStatusGroup_SPC, 4U), /*!< SYS LDO Low driver strength setting be ignored for LDO LVD/HVD enabled. */
    kStatus_SPC_CORELDOLowDriveStrengthIgnore = MAKE_STATUS(
        kStatusGroup_SPC, 5U), /*!< CORE LDO Low driver strength setting be ignored for LDO LVD/HVD enabled. */
    kStatus_SPC_CORELDOVoltageWrong   = MAKE_STATUS(kStatusGroup_SPC, 7U), /*!< Core LDO voltage is wrong. */
    kStatus_SPC_CORELDOVoltageSetFail = MAKE_STATUS(kStatusGroup_SPC, 8U), /*!< Core LDO voltage set fail. */
    kStatus_SPC_BandgapModeWrong      = MAKE_STATUS(kStatusGroup_SPC, 6U), /*!< Selected Bandgap Mode wrong. */
};

/*!
 * @brief Voltage Detect Status Flags.
 */
enum _spc_voltage_detect_flags
{
    kSPC_IOVDDHighVoltageDetectFlag     = SPC_VD_STAT_IOVDD_HVDF_MASK,   /*!< IO VDD High-Voltage detect flag. */
    kSPC_SystemVDDHighVoltageDetectFlag = SPC_VD_STAT_SYSVDD_HVDF_MASK,  /*!< System VDD High-Voltage detect flag. */
    kSPC_CoreVDDHighVoltageDetectFlag   = SPC_VD_STAT_COREVDD_HVDF_MASK, /*!< Core VDD High-Voltage detect flag. */
    kSPC_IOVDDLowVoltageDetectFlag      = SPC_VD_STAT_IOVDD_LVDF_MASK,   /*!< IO VDD Low-Voltage detect flag. */
    kSPC_SystemVDDLowVoltageDetectFlag  = SPC_VD_STAT_SYSVDD_LVDF_MASK,  /*!< System VDD Low-Voltage detect flag. */
    kSPC_CoreVDDLowVoltageDetectFlag    = SPC_VD_STAT_COREVDD_LVDF_MASK, /*!< Core VDD Low-Voltage detect flag. */
};

/*!
 * @brief SPC power domain isolation status.
 */
enum _spc_power_domains
{
    kSPC_MAINPowerDomainRetain = 1UL << 16U, /*!< Peripherals and IO pads retain in MAIN Power Domain. */
    kSPC_WAKEPowerDomainRetain = 1UL << 17U, /*!< Peripherals and IO pads retain in WAKE Power Domain. */
#if defined(FSL_FEATURE_SPC_HAS_2P4G_POWER_DOMAIN) && FSL_FEATURE_SPC_HAS_2P4G_POWER_DOMAIN
    kSPC_2P4GPowerDoaminRetain = 1UL << 18U, /*!< Peripherals and IO pads retion in 2.4G Power Domain. */
#endif                                       /* FSL_FEATURE_SPC_HAS_2P4G_POWER_DOMAIN */
};

/*!
 * @brief The enumeration of spc power domain, the connected power domain is chip specfic, please refer to chip's RM
 * for details.
 */
typedef enum _spc_power_domain_id
{
    kSPC_PowerDomain0 = 0U, /*!< Power domain0, the connected power domain is chip specific. */
    kSPC_PowerDomain1 = 1U, /*!< Power domain1, the connected power domain is chip specific. */
    kSPC_PowerDomain2 = 2U, /*!< Power domain2, the connected power domain is chip specific. */
} spc_power_domain_id_t;

/*!
 * @brief The enumeration of Power domain's low power mode.
 */
typedef enum _spc_power_domain_low_power_mode
{
    kSPC_SleepWithSYSClockRunning     = 0U, /*!< Power domain request SLEEP mode with SYS clock running. */
    kSPC_SleepWithSysClockOff         = 1U, /*!< Power domain request SLEEP mode with SYS clock off. */
    kSPC_DeepSleepSysClockOff         = 2U, /*!< Power domain request DEEP SLEEP mode with SYS clock off. */
    kSPC_PowerDownWithSysClockOff     = 4U, /*!< Power domain request POWER DOWN mode with SYS clock off. */
    kSPC_DeepPowerDownWithSysClockOff = 8U, /*!< Power domain request DEEP POWER DOWN mode with SYS clock off. */
} spc_power_domain_low_power_mode_t;

/*!
 * @brief SPC low power request output pin polarity.
 */
typedef enum _spc_lowPower_request_pin_polarity
{
    kSPC_HighTruePolarity = 0x0U, /*!< Control the High Polarity of the Low Power Reqest Pin. */
    kSPC_LowTruePolarity  = 0x1U, /*!< Control the Low Polarity of the Low Power Reqest Pin. */
} spc_lowpower_request_pin_polarity_t;

/*!
 * @brief SPC low power request output override.
 */
typedef enum _spc_lowPower_request_output_override
{
    kSPC_LowPowerRequestNotForced  = 0x0U, /*!< Not Forced. */
    kSPC_LowPowerRequestReserved   = 0x1U, /*!< Reserved. */
    kSPC_LowPowerRequestForcedLow  = 0x2U, /*!< Forced Low (Ignore LowPower request output polarity setting.) */
    kSPC_LowPowerRequestForcedHigh = 0x3U, /*!< Forced High (Ignore LowPower request output polarity setting.) */
} spc_lowpower_request_output_override_t;

/*!
 * @brief SPC Bandgap mode enumeration in Active mode or Low Power mode.
 */
typedef enum _spc_bandgap_mode
{
    kSPC_BandgapDisabled              = 0x0U, /*!< Bandgap disabled. */
    kSPC_BandgapEnabledBufferDisabled = 0x1U, /*!< Bandgap enabled with Buffer disabled. */
    kSPC_BandgapEnabledBufferEnabled  = 0x2U, /*!< Bandgap enabled with Buffer enabled. */
    kSPC_BandgapReserved              = 0x3U, /*!< Reserved.  */
} spc_bandgap_mode_t;

/*!
 * @brief DCDC regulator voltage level enumeration in Active mode or Low Power Mode.
 */
typedef enum _spc_dcdc_voltage_level
{
#if (defined(FSL_FEATURE_SPC_DCDC_VOLTAGE_LEVEL_DECREASE) && FSL_FEATURE_SPC_DCDC_VOLTAGE_LEVEL_DECREASE)
    kSPC_DCDC_SafeModeVoltage = 0x0U, /*!< DCDC VDD Regulator regulate to Safe-Mode Voltage. */
    kSPC_DCDC_NormalVoltage   = 0x1U, /*!< DCDC VDD Regulator regulate to Normal Voltage. */
    kSPC_DCDC_MidVoltage      = 0x2U, /*!< DCDC VDD Regulator regulate to Mid Voltage. */
    kSPC_DCDC_LowUnderVoltage = 0x3U, /*!< DCDC VDD Regulator regulate to Low Under Voltage. */
#else
    kSPC_DCDC_LowUnderVoltage      = 0x0U, /*!< DCDC VDD Regulator regulate to Low Under Voltage. */
    kSPC_DCDC_MidVoltage           = 0x1U, /*!< DCDC VDD Regulator regulate to Mid Voltage. */
    kSPC_DCDC_NormalVoltage        = 0x2U, /*!< DCDC VDD Regulator regulate to Normal Voltage. */
    kSPC_DCDC_SafeModeVoltage      = 0x3U, /*!< DCDC VDD Regulator regulate to Safe-Mode Voltage. */
#endif /* FSL_FEATURE_SPC_DCDC_VOLTAGE_LEVEL_DECREASE */
} spc_dcdc_voltage_level_t;

/*!
 * @brief DCDC regulator Drive Strength enumeration in Active mode or Low Power Mode.
 */
typedef enum _spc_dcdc_drive_strength
{
    kSPC_DCDC_PulseRefreshMode = 0x0U,    /*!< DCDC VDD Regulator Drive Strength set to Pulse Refresh Mode.
                                           *   This enum member is only useful for Low Power Mode config. */
    kSPC_DCDC_LowDriveStrength    = 0x1U, /*!< DCDC VDD regulator Drive Strength set to low. */
    kSPC_DCDC_NormalDriveStrength = 0x2U, /*!< DCDC VDD regulator Drive Strength set to Normal. */
    kSPC_DCDC_Reserved            = 0x3U, /*!< Reserved. */
} spc_dcdc_drive_strength_t;

/*!
 * @brief SYS LDO regulator voltage level enumeration in Active mode.
 */
typedef enum _spc_sys_ldo_voltage_level
{
    kSPC_SysLDO_NormalVoltage    = 0x0U, /*!< SYS LDO VDD Regulator regulate to Normal Voltage(1.8V). */
    kSPC_SysLDO_OverDriveVoltage = 0x1U, /*!< SYS LDO VDD Regulator regulate to Over Drive Voltage(2.5V). */
} spc_sys_ldo_voltage_level_t;

/*!
 * @brief SYS LDO regulator Drive Strength enumeration in Active mode or Low Power mode.
 */
typedef enum _spc_sys_ldo_drive_strength
{
    kSPC_SysLDO_LowDriveStrength    = 0x0U, /*!< SYS LDO VDD regulator Drive Strength set to low. */
    kSPC_SysLDO_NormalDriveStrength = 0x1U, /*!< SYS LDO VDD regulator Drive Strength set to Normal. */
} spc_sys_ldo_drive_strength_t;

/*!
 * @brief Core LDO regulator voltage level enumeration in Active mode or Low Power mode.
 */
typedef enum _spc_core_ldo_voltage_level
{
#if (defined(FSL_FEATURE_SPC_LDO_VOLTAGE_LEVEL_DECREASE) && FSL_FEATURE_SPC_LDO_VOLTAGE_LEVEL_DECREASE)
    kSPC_CoreLDO_NormalVoltage     = 0x0U, /*!< Core LDO VDD regulator regulate to Normal Voltage. */
    kSPC_CoreLDO_MidDriveVoltage   = 0x1U, /*!< Core LDO VDD regulator regulate to Mid Drive Voltage. */
    kSPC_CoreLDO_UnderDriveVoltage = 0x2U, /*!< Core LDO VDD regulator regulate to Under Drive Voltage. */
    kSPC_CoreLDO_SafeModeVoltage   = 0x3U, /*!< Core LDO VDD regulator regulate to Safe-Mode Voltage. */
#else
    kSPC_CoreLDO_UnderDriveVoltage = 0x0U, /*!< Core LDO VDD regulator regulate to Under Drive Voltage. */
    kSPC_CoreLDO_MidDriveVoltage   = 0x1U, /*!< Core LDO VDD regulator regulate to Mid Drive Voltage. */
    kSPC_CoreLDO_NormalVoltage     = 0x2U, /*!< Core LDO VDD regulator regulate to Normal Voltage. */
    kSPC_CoreLDO_SafeModeVoltage   = 0x3U, /*!< Core LDO VDD regulator regulate to Safe-Mode Voltages. */
#endif /* FSL_FEATURE_SPC_LDO_VOLTAGE_LEVEL_DECREASE */
} spc_core_ldo_voltage_level_t;

/*!
 * @brief CORE LDO VDD regulator Drive Strength enumeration in Low Power mode.
 */
typedef enum _spc_core_ldo_drive_strength
{
    kSPC_CoreLDO_LowDriveStrength    = 0x0U, /*!< Core LDO VDD regulator Drive Strength set to low. */
    kSPC_CoreLDO_NormalDriveStrength = 0x1U, /*!< Core LDO VDD regulator Drive Strength set to Normal. */
} spc_core_ldo_drive_strength_t;

/*!
 * @brief System/IO VDD Low-Voltage Level Select.
 */
typedef enum _spc_low_voltage_level_select
{
    kSPC_LowVoltageNormalLevel = 0x0U, /*!< Trip point set to Normal level. */
    kSPC_LowVoltageSafeLevel   = 0x1U, /*!< Trip point set to Safe level. */
} spc_low_voltage_level_select_t;

/*!
 * @brief SRAM operate voltage enumeration.
 */
typedef enum _spc_sram_operat_voltage
{
    kSPC_SRAM_OperatVoltage1P0V = 0x1U, /*!< SRAM operate voltage set to 1.0V. */
    kSPC_SRAM_OperatVoltage1P1V = 0x2U, /*!< SRAM operate voltage set to 1.1V. */
} spc_sram_operat_voltage_t;

/*!
 * @brief Low Power Request output pin configuration.
 */
typedef struct _spc_lowpower_request_config
{
    bool enable;                                     /*!< Low Power Request Output enable. */
    spc_lowpower_request_pin_polarity_t polarity;    /*!< Low Power Request Output pin polarity select. */
    spc_lowpower_request_output_override_t override; /*!< Low Power Request Output Override. */
} spc_lowpower_request_config_t;

#if defined(FSL_FEATURE_SPC_HAS_CFG_REGISTER) && FSL_FEATURE_SPC_HAS_CFG_REGISTER
/*!
 * @brief Integrated power switch configuration.
 * @note Legacy structure, will be removed.
 */
typedef struct _spc_intergrated_power_switch_config
{
    bool wakeup; /*!< Assert an output pin to un-gate the integrated power switch. */
    bool sleep;  /*!< Assert an output pin to power gate the intergrated power switch. */
} spc_intergrated_power_switch_config_t;
#endif /* FSL_FEATURE_SPC_HAS_CFG_REGISTER */

/*!
 * @brief Core LDO regulator options in Active mode.
 */
typedef struct _spc_active_mode_core_ldo_option
{
    spc_core_ldo_voltage_level_t CoreLDOVoltage; /*!< Core LDO Regulator Voltage Level selection in Active mode. */
#if defined(FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS) && FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS
    spc_core_ldo_drive_strength_t
        CoreLDODriveStrength; /*!< Core LDO Regulator Drive Strength selection in Active mode */
#endif                        /* FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS */
} spc_active_mode_core_ldo_option_t;

/*!
 * @brief System LDO regulator options in Active mode.
 */
typedef struct _spc_active_mode_sys_ldo_option
{
    spc_sys_ldo_voltage_level_t SysLDOVoltage; /*!< System LDO Regulator Voltage Level selection in Active mode. */
    spc_sys_ldo_drive_strength_t
        SysLDODriveStrength; /*!< System LDO Regulator Drive Strength selection in Active mode. */
} spc_active_mode_sys_ldo_option_t;

/*!
 * @brief DCDC regulator options in Active mode.
 */
typedef struct _spc_active_mode_dcdc_option
{
    spc_dcdc_voltage_level_t DCDCVoltage;        /*!< DCDC Regulator Voltage Level selection in Active mode. */
    spc_dcdc_drive_strength_t DCDCDriveStrength; /*!< DCDC VDD Regulator Drive Strength selection in Active mode. */
} spc_active_mode_dcdc_option_t;

/*!
 * @brief Core LDO regulator options in Low Power mode.
 */
typedef struct _spc_lowpower_mode_core_ldo_option
{
    spc_core_ldo_voltage_level_t CoreLDOVoltage; /*!< Core LDO Regulator Voltage Level selection in Low Power mode. */
    spc_core_ldo_drive_strength_t
        CoreLDODriveStrength; /*!< Core LDO Regulator Drive Strength selection in Low Power mode */
} spc_lowpower_mode_core_ldo_option_t;

/*!
 * @brief System LDO regulator options in Low Power mode.
 */
typedef struct _spc_lowpower_mode_sys_ldo_option
{
    spc_sys_ldo_drive_strength_t
        SysLDODriveStrength; /*!< System LDO Regulator Drive Strength selection in Low Power mode. */
} spc_lowpower_mode_sys_ldo_option_t;

/*!
 * @brief DCDC regulator options in Low Power mode.
 */
typedef struct _spc_lowpower_mode_dcdc_option
{
    spc_dcdc_voltage_level_t DCDCVoltage;        /*!< DCDC Regulator Voltage Level selection in Low Power mode. */
    spc_dcdc_drive_strength_t DCDCDriveStrength; /*!< DCDC VDD Regulator Drive Strength selection in Low Power mode. */
} spc_lowpower_mode_dcdc_option_t;

/*!
 * @brief CORE/SYS/IO VDD Voltage Detect options.
 */
typedef struct _spc_voltage_detect_option
{
    bool HVDInterruptEnable; /*!< CORE/SYS/IO VDD High Voltage Detect interrupt enable. */
    bool HVDResetEnable;     /*!< CORE/SYS/IO VDD High Voltage Detect reset enable. */
    bool LVDInterruptEnable; /*!< CORE/SYS/IO VDD Low Voltage Detect interrupt enable. */
    bool LVDResetEnable;     /*!< CORE/SYS/IO VDD Low Voltage Detect reset enable. */
} spc_voltage_detect_option_t;

/*!
 * @brief DCDC Burst configuration.
 */
typedef struct _spc_dcdc_burst_config
{
    bool sofwareBurstRequest;  /*!< Enable/Disable DCDC Software Burst Request. */
    bool externalBurstRequest; /*!< Enable/Disable DCDC External Burst Request. */
    bool stabilizeBurstFreq;   /*!< Enable/Disable DCDC frequency stabilization. */
    uint8_t freq;              /*!< The frequency of the current burst.  */
} spc_dcdc_burst_config_t;

/*!
 * @brief Core Voltage Detect configuration.
 */
typedef struct _spc_core_voltage_detect_config
{
    spc_voltage_detect_option_t option; /*!< Core VDD Voltage Detect option. */
} spc_core_voltage_detect_config_t;

/*!
 * @brief System Voltage Detect Configuration.
 */
typedef struct _spc_system_voltage_detect_config
{
    spc_voltage_detect_option_t option;   /*!< System VDD Voltage Detect option. */
    spc_low_voltage_level_select_t level; /*!< @deprecated, reserved for all devices, will removed in next release. */
} spc_system_voltage_detect_config_t;

/*!
 * @brief IO Voltage Detect Configuration.
 */
typedef struct _spc_io_voltage_detect_config
{
    spc_voltage_detect_option_t option;   /*!< IO VDD Voltage Detect option. */
    spc_low_voltage_level_select_t level; /*!< IO VDD Low-voltage level selection. */
} spc_io_voltage_detect_config_t;

/*!
 * @brief Active mode configuration.
 */
typedef struct _spc_active_mode_regulators_config
{
    spc_bandgap_mode_t bandgapMode;
    bool lpBuff;
    spc_active_mode_dcdc_option_t DCDCOption;
    spc_active_mode_sys_ldo_option_t SysLDOOption;
    spc_active_mode_core_ldo_option_t CoreLDOOption;
} spc_active_mode_regulators_config_t;

/*!
 * @brief Low Power Mode configuration.
 */
typedef struct _spc_lowpower_mode_regulators_config
{
    bool lpIREF;
    spc_bandgap_mode_t bandgapMode;
    bool lpBuff;
    bool CoreIVS;
    spc_lowpower_mode_dcdc_option_t DCDCOption;
    spc_lowpower_mode_sys_ldo_option_t SysLDOOption;
    spc_lowpower_mode_core_ldo_option_t CoreLDOOption;
} spc_lowpower_mode_regulators_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @name SPC Status
 * @{
 */
/*!
 * @brief Gets Isolation status for each power domains.
 *
 * This function gets the status which indicates whether certain
 * peripheral and the IO pads are in a latched state as a result
 * of having been in POWERDOWN mode.
 *
 * @param base SPC peripheral base address.
 * @return Current isolation status for each power domains. See @ref _spc_power_domains for details.
 */
uint8_t SPC_GetPeriphIOIsolationStatus(SPC_Type *base);

/*!
 * @brief Clears peripherals and I/O pads isolation flags for each power domains.
 *
 * This function clears peripherals and I/O pads isolation flags for each power domains.
 * After recovering from the POWERDOWN mode, user must invoke this function to release the
 * I/O pads and certain peripherals to their normal run mode state. Before invoking this
 * function, user must restore chip configuration in particular pin configuration for enabled
 * WUU wakeup pins.
 *
 * @param base SPC peripheral base address.
 */
static inline void SPC_ClearPeriphIOIsolationFlag(SPC_Type *base)
{
    base->SC |= SPC_SC_ISO_CLR_MASK;
}

/*!
 * @brief Gets SPC busy status flag.
 *
 * This function gets SPC busy status flag. When SPC executing any type of power mode
 * transition in ACTIVE mode or any of the SOC low power mode, the SPC busy status flag is set
 * and this function returns true. When changing CORE LDO voltage level and DCDC voltage level
 * in ACTIVE mode, the SPC busy status flag is set and this function return true.
 *
 * @param base SPC peripheral base address.
 * @return Ack busy flag.
 *          true    -   SPC is busy.
 *          false   -   SPC is not busy.
 */
static inline bool SPC_GetBusyStatusFlag(SPC_Type *base)
{
    return ((base->SC & SPC_SC_BUSY_MASK) != 0UL);
}

/*!
 * @brief Checks system low power request.
 *
 * @note Only when all power domains request low power mode entry, the result of this function is true. That means when
 * all power domains request low power mode entry, the SPC regulators will be controlled by LP_CFG register.
 *
 * @param base SPC peripheral base address.
 * @return The system low power request check result.
 *       - \b true All power domains have requested low power mode and SPC has entered a low power state and power mode
 *                 configuration are based on the LP_CFG configuration register.
 *       - \b false SPC in active mode and ACTIVE_CFG register control system power supply.
 */
static inline bool SPC_CheckLowPowerReqest(SPC_Type *base)
{
    return ((base->SC & SPC_SC_SPC_LP_REQ_MASK) == SPC_SC_SPC_LP_REQ_MASK);
}

/*!
 * @brief Clears system low power request, set SPC in active mode.
 *
 * @param base SPC peripheral base address.
 */
static inline void SPC_ClearLowPowerRequest(SPC_Type *base)
{
    base->SC |= SPC_SC_SPC_LP_REQ_MASK;
}

/*!
 * @brief Checks power switch state.
 *
 * @param base SPC peripheral base address.
 * @return The state(ON/OFF) of power switch.
 *          - \b true Indicates the power switch is ON.
 *          - \b false Indicates the power switch is OFF.
 */
static inline bool SPC_CheckPowerSwitchState(SPC_Type *base)
{
    return ((base->SC & SPC_SC_SWITCH_STATE_MASK) == SPC_SC_SWITCH_STATE_MASK);
}

/*!
 * @brief Gets selected power domain's requested low power mode.
 *
 * @param base SPC peripheral base address.
 * @param powerDomainId Power Domain Id, please refer to @ref spc_power_domain_id_t.
 *
 * @return The selected power domain's requested low power mode, please refer to @ref spc_power_domain_low_power_mode_t.
 */
spc_power_domain_low_power_mode_t SPC_GetPowerDomainLowPowerMode(SPC_Type *base, spc_power_domain_id_t powerDomainId);

/*!
 * @brief Checks power domain's low power request.
 *
 * @param base SPC peripheral base address.
 * @param powerDomainId Power Domain Id, please refer to @ref spc_power_domain_id_t.
 * @return The result of power domain's low power request.
 *            - \b true The selected power domain requests low power mode entry.
 *            - \b false The selected power domain does not request low power mode entry.
 */
static inline bool SPC_CheckPowerDomainLowPowerRequest(SPC_Type *base, spc_power_domain_id_t powerDomainId)
{
    return ((base->PD_STATUS[(uint8_t)powerDomainId] & SPC_PD_STATUS_PD_LP_REQ_MASK) == SPC_PD_STATUS_PD_LP_REQ_MASK);
}

/*!
 * @brief Clears selected power domain's low power request flag.
 *
 * @param base SPC peripheral base address.
 * @param powerDomainId Power Domain Id, please refer to @ref spc_power_domain_id_t.
 */
static inline void SPC_ClearPowerDomainLowPowerRequestFlag(SPC_Type *base, spc_power_domain_id_t powerDomainId)
{
    base->PD_STATUS[(uint8_t)powerDomainId] |= SPC_PD_STATUS_PD_LP_REQ_MASK;
}

/*! @} */

/*!
 * @name Low Power Request configuration.
 * @{
 */
/*!
 * @brief Configs Low power request output pin.
 *
 * This function config the low power request output pin
 *
 * @param base SPC peripheral base address.
 * @param config Pointer the @ref spc_lowpower_request_config_t structure.
 */
void SPC_SetLowPowerRequestConfig(SPC_Type *base, const spc_lowpower_request_config_t *config);

/*! @} */

/*!
 * @name Smart Power Switch Control Interfaces
 * @{
 */

/*!
 * @brief Gates/Un-gates power switch in software mode.
 *
 * @param base SPC peripheral base address.
 * @param gate Used to gate/ungate power switch
 *          - \b true The power switch will be gated.
 *          - \b false The power switch will be un-gated.
 */
static inline void SPC_SoftwareGatePowerSwitch(SPC_Type *base, bool gate)
{
    if (gate)
    {
        base->CFG &= ~SPC_CFG_INTG_PWSWTCH_WKUP_ACTIVE_EN_MASK;
        base->CFG |= SPC_CFG_INTG_PWSWTCH_SLEEP_ACTIVE_EN_MASK;
    }
    else
    {
        base->CFG &= ~SPC_CFG_INTG_PWSWTCH_SLEEP_ACTIVE_EN_MASK;
        base->CFG |= SPC_CFG_INTG_PWSWTCH_WKUP_ACTIVE_EN_MASK;
    }
}

/*!
 * @brief Gates power switch at low power modes entry, and un-gates power switch at low power mode wakeup.
 *
 * @param base SPC peripheral base address.
 */
static inline void SPC_PowerModeControlPowerSwitch(SPC_Type *base)
{
    base->CFG &= ~(SPC_CFG_INTG_PWSWTCH_WKUP_ACTIVE_EN_MASK | SPC_CFG_INTG_PWSWTCH_SLEEP_ACTIVE_EN_MASK);
    base->CFG |= (SPC_CFG_INTG_PWSWTCH_SLEEP_EN_MASK | SPC_CFG_INTG_PWSWTCH_WKUP_EN_MASK);
}

/*! @} */

/*!
 * @name Wake up configuration.
 * @{
 */
/*!
 * @brief Set the address of the function/image to be executed if chip wake from power down or deep power down mode.
 *
 * @note Data written by this function is used by BootROM to quickly retore ARM Core context,
 * or to switch execution to a defined address in Flash/SRAM on WakeUp.
 *
 * @note The first word must be SP, and the second word must be PC.
 *
 * @note Please remember to calculate the CRC value of the first 48 bytes of image/function and save the result to
 * REGFILE1->REG[0]. The BootROM will check this CRC value, if authenticated successfully then the image/function
 * will be executed.
 *
 * @param base SPC peripheral base address.
 * @param data The address of the function/image to be executed if wakeup from low power mode.
 */
static inline void SPC_SetWakeUpValue(SPC_Type *base, uint32_t data)
{
    base->WAKEUP = data;
}

/*!
 * @brief Gets back the WakeUp value.
 *
 * @param base SPC peripheral base address.
 * @return The WakeUp value.
 */
static inline uint32_t SPC_GetWakeUpValue(SPC_Type *base)
{
    return base->WAKEUP;
}

/*! @} */

/*!
 * @name Active Mode configuration.
 * @{
 */

/*!
 * @brief Gets CORE LDO VDD Regulator Voltage level.
 *
 * This function returns the voltage level of CORE LDO Regulator in Active mode.
 *
 * @param base SPC peripheral base address.
 * @return Voltage level of CORE LDO in type of @ref spc_core_ldo_voltage_level_t enumeration.
 */
static inline spc_core_ldo_voltage_level_t SPC_GetActiveModeCoreLDOVDDVoltageLevel(SPC_Type *base)
{
    return (spc_core_ldo_voltage_level_t)(uint32_t)((base->ACTIVE_CFG & SPC_ACTIVE_CFG_CORELDO_VDD_LVL_MASK) >>
                                                    SPC_ACTIVE_CFG_CORELDO_VDD_LVL_SHIFT);
}

/*!
 * @brief Gets the Bandgap mode in Active mode.
 *
 * @param base SPC peripheral base address.
 * @return Bandgap mode in the type of @ref spc_bandgap_mode_t enumeration.
 */
static inline spc_bandgap_mode_t SPC_GetActiveModeBandgapMode(SPC_Type *base)
{
    return (spc_bandgap_mode_t)(uint32_t)((base->ACTIVE_CFG & SPC_ACTIVE_CFG_BGMODE_MASK) >>
                                          SPC_ACTIVE_CFG_BGMODE_SHIFT);
}

/*!
 * @brief Gets all voltage detectors status in Active mode.
 *
 * @param base SPC peripheral base address.
 * @return All voltage detectors status in Active mode.
 */
static inline uint32_t SPC_GetActiveModeVoltageDetectStatus(SPC_Type *base)
{
    uint32_t state;
    state = base->ACTIVE_CFG &
            (SPC_ACTIVE_CFG_IO_HVDE_MASK | SPC_ACTIVE_CFG_IO_LVDE_MASK | SPC_ACTIVE_CFG_SYS_HVDE_MASK |
             SPC_ACTIVE_CFG_SYS_LVDE_MASK | SPC_ACTIVE_CFG_CORE_HVDE_MASK | SPC_ACTIVE_CFG_CORE_LVDE_MASK);
    return state;
}

#if defined(FSL_FEATURE_SPC_HAS_CFG_REGISTER) && FSL_FEATURE_SPC_HAS_CFG_REGISTER
/*!
 * @brief Configs Integrated power switch in active mode.
 *
 * @note Legacy API and will be removed.
 *
 * @param base SPC peripheral base address.
 * @param config Pointer to spc_intergrated_power_switch_config_t pointer.
 */
void SPC_SetActiveModeIntegratedPowerSwitchConfig(SPC_Type *base, const spc_intergrated_power_switch_config_t *config);
#endif /* FSL_FEATURE_SPC_HAS_CFG_REGISTER */

/*!
 * @brief Configs Bandgap mode in Active mode.
 *
 * @note In active mode, beacause CORELDO_VDD_DS is reserved and set to Normal, so it is impossible to
 * disable Bandgap in active mode
 *
 * @param base SPC peripheral base address.
 * @param mode The Bandgap mode be selected.
 *
 * @retval #kStatus_SPC_BandgapModeWrong The Bandgap can not be disabled in active mode.
 * @retval #kStatus_Success Config Bandgap mode in Active power mode successful.
 */
status_t SPC_SetActiveModeBandgapModeConfig(SPC_Type *base, spc_bandgap_mode_t mode);

/*!
 * @brief Enables/Disable the CMP Bandgap Buffer in Active mode.
 *
 * @param base SPC peripheral base address.
 * @param enable Enable/Disable CMP Bandgap buffer.
 *          true    -   Enable Buffer Stored Reference voltage to CMP.
 *          false   -   Disable Buffer Stored Reference voltage to CMP.
 */
static inline void SPC_EnableActiveModeCMPBandgapBuffer(SPC_Type *base, bool enable)
{
    if (enable)
    {
        base->ACTIVE_CFG |= SPC_ACTIVE_CFG_LPBUFF_EN_MASK;
    }
    else
    {
        base->ACTIVE_CFG &= ~SPC_ACTIVE_CFG_LPBUFF_EN_MASK;
    }
}

/*!
 * @brief Sets the delay when the regulators change voltage level in Active mode.
 *
 * @param base SPC peripheral base address.
 * @param delay The number of SPC timer clock cycles.
 */
static inline void SPC_SetActiveModeVoltageTrimDelay(SPC_Type *base, uint16_t delay)
{
    base->ACTIVE_VDELAY = SPC_ACTIVE_VDELAY_ACTIVE_VDELAY(delay);
}

/*!
 * @brief Configs regulators in Active mode.
 *
 * This function provides the method to config all on-chip regulators in active mode.
 *
 * @param base SPC peripheral base address.
 * @param config Pointer to spc_active_mode_regulators_config_t structure.
 * @retval #kStatus_Success Config regulators in Active power mode successful.
 * @retval #kStatus_SPC_BandgapModeWrong The bandgap mode setting in Active mode is wrong.
 * @retval #kStatus_SPC_Busy The SPC instance is busy to execute any type of power mode transition.
 * @retval #kStatus_SPC_CORELDOVoltageWrong The selected voltage level in active mode is not allowed.
 * @retval #kStatus_SPC_SYSLDOOverDriveVoltageFail Fail to regulator to Over Drive Voltage.
 * @retval #kStatus_SPC_SYSLDOLowDriveStrengthIgnore Set driver strength to Low will be ignored.
 * @retval #kStatus_SPC_DCDCLowDriveStrengthIgnore Set driver strength to Low will be ignored.
 */
status_t SPC_SetActiveModeRegulatorsConfig(SPC_Type *base, const spc_active_mode_regulators_config_t *config);

/*!
 * @brief Disable/Enable VDD Core Glitch Detect in Active mode.
 *
 * @note State of glitch detect disable feature will be ignored if bandgap is disabled and
 * glitch detect hardware will be forced to OFF state.
 *
 * @param base SPC peripheral base address.
 * @param disable Used to disable/enable VDD Core Glitch detect feature.
 *         - \b true Disable VDD Core Low Voltage detect;
 *         - \b false Enable VDD Core Low Voltage detect.
 */
static inline void SPC_DisableActiveModeVddCoreGlitchDetect(SPC_Type *base, bool disable)
{
    if (disable)
    {
        base->ACTIVE_CFG |= SPC_ACTIVE_CFG_GLITCH_DETECT_DISABLE_MASK;
    }
    else
    {
        base->ACTIVE_CFG &= ~SPC_ACTIVE_CFG_GLITCH_DETECT_DISABLE_MASK;
    }
}

/*! @} */

/*!
 * @name Low Power mode configuration.
 * @{
 */

#if defined(FSL_FEATURE_SPC_HAS_CFG_REGISTER) && FSL_FEATURE_SPC_HAS_CFG_REGISTER
/*!
 * @brief Configs Integrated power switch in Low Power mode.
 *
 * @note Legacy API, will be removed.
 *
 * @param base SPC peripheral base address.
 * @param config Pointer to spc_intergrated_power_switch_config_t pointer.
 */
void SPC_SetLowPowerModeIntegratedPowerSwitchConfig(SPC_Type *base,
                                                    const spc_intergrated_power_switch_config_t *config);
#endif /* FSL_FEATURE_SPC_HAS_CFG_REGISTER */

#if defined(FSL_FEATURE_SPC_HAS_WBIAS_EN) && FSL_FEATURE_SPC_HAS_WBIAS_EN
/*!
 * @brief Enables/Disables VDDC Well Bias in low power mode.
 *
 * @param base SPC peripheral base address.
 * @param enable Enable/Disable the VDDC Well Bias.
 *          true    -   Enable Vddc Well Bias.
 *          false   -   Disable Vddc Well Bias.
 */
static inline void SPC_EnableLowPowerModeVDDCWellBias(SPC_Type *base, bool enable)
{
    if (enable)
    {
        base->LP_CFG |= SPC_LP_CFG_WBIAS_EN_MASK;
    }
    else
    {
        base->LP_CFG &= ~SPC_LP_CFG_WBIAS_EN_MASK;
    }
}
#endif /* FSL_FEATURE_SPC_HAS_WBIAS_EN */

/*!
 * @brief Gets CORE LDO VDD Drive Strength for Low Power modes.
 *
 * @param base SPC peripheral base address.
 * @return The CORE LDO's VDD Drive Strength.
 */
static inline spc_core_ldo_drive_strength_t SPC_GetLowPowerCoreLDOVDDDriveStrength(SPC_Type *base)
{
    return (spc_core_ldo_drive_strength_t)(uint32_t)((base->LP_CFG & SPC_LP_CFG_CORELDO_VDD_DS_MASK) >>
                                                     SPC_LP_CFG_CORELDO_VDD_DS_SHIFT);
}

/*!
 * @brief Gets the CORE LDO VDD Regulator Voltage Level for Low Power modes.
 *
 * @param base SPC peripheral base address.
 * @return The CORE LDO VDD Regulator's voltage level.
 */
static inline spc_core_ldo_voltage_level_t SPC_GetLowPowerCoreLDOVDDVoltageLevel(SPC_Type *base)
{
    return ((spc_core_ldo_voltage_level_t)(uint32_t)((base->LP_CFG & SPC_LP_CFG_CORELDO_VDD_LVL_MASK) >>
                                                     SPC_LP_CFG_CORELDO_VDD_LVL_SHIFT));
}

/*!
 * @brief Gets the Bandgap mode in Low Power mode.
 *
 * @param base SPC peripheral base address.
 * @return Bandgap mode in the type of @ref spc_bandgap_mode_t enumeration.
 */
static inline spc_bandgap_mode_t SPC_GetLowPowerModeBandgapMode(SPC_Type *base)
{
    return (spc_bandgap_mode_t)(uint32_t)((base->LP_CFG & SPC_LP_CFG_BGMODE_MASK) >> SPC_LP_CFG_BGMODE_SHIFT);
}

/*!
 * @brief Gets the status of all voltage detectors in Low Power mode.
 *
 * @param base SPC peripheral base address.
 * @return The status of all voltage detectors in low power mode.
 */
static inline uint32_t SPC_GetLowPowerModeVoltageDetectStatus(SPC_Type *base)
{
    uint32_t state;
    state = base->LP_CFG & (SPC_LP_CFG_IO_HVDE_MASK | SPC_LP_CFG_IO_LVDE_MASK | SPC_LP_CFG_SYS_HVDE_MASK |
                            SPC_LP_CFG_SYS_LVDE_MASK | SPC_LP_CFG_CORE_HVDE_MASK | SPC_LP_CFG_CORE_LVDE_MASK);
    return state;
}

/*!
 * @brief Enables/Disables Low Power IREF in low power modes.
 *
 * This function enables/disables Low Power IREF. Low Power IREF can only get
 * disabled in Deep power down mode. In other low power modes, the Low Power IREF
 * is always enabled.
 *
 * @param base SPC peripheral base address.
 * @param enable Enable/Disable Low Power IREF.
 *          true    -   Enable Low Power IREF for Low Power modes.
 *          false   -   Disable Low Power IREF for Deep Power Down mode.
 */
static inline void SPC_EnableLowPowerModeLowPowerIREF(SPC_Type *base, bool enable)
{
    if (enable)
    {
        base->LP_CFG |= SPC_LP_CFG_LP_IREFEN_MASK;
    }
    else
    {
        base->LP_CFG &= ~SPC_LP_CFG_LP_IREFEN_MASK;
    }
}

/*!
 * @brief Configs Bandgap mode in Low Power mode.
 *
 * This function configs Bandgap mode in Low Power mode.
 * IF user want to disable Bandgap while keeping any of the Regulator in Normal Driver Strength
 * or if any of the High voltage detectors/Low voltage detectors are kept enabled, the Bandgap mode
 * will be set as Bandgap Enabled with Buffer Disabled.
 *
 * @note This API shall be invoked following set HVDs/LVDs and regulators' driver strength.
 *
 * @param base SPC peripheral base address.
 * @param mode The Bandgap mode be selected.
 * @retval #kStatus_SPC_BandgapModeWrong The bandgap mode setting in Low Power mode is wrong.
 * @retval #kStatus_Success Config Bandgap mode in Low Power power mode successful.
 */
status_t SPC_SetLowPowerModeBandgapmodeConfig(SPC_Type *base, spc_bandgap_mode_t mode);

/*!
 * @brief Enables/Disables CMP Bandgap Buffer.
 *
 * This function gates CMP bandgap buffer. CMP bandgap buffer is automatically disabled and turned off
 * in Deep Power Down mode.
 *
 * @param base SPC peripheral base address.
 * @param enable Enable/Disable CMP Bandgap buffer.
 *          true    -   Enable Buffer Stored Reference Voltage to CMP.
 *          false   -   Disable Buffer Stored Reference Voltage to CMP.
 */
static inline void SPC_EnableLowPowerModeCMPBandgapBufferMode(SPC_Type *base, bool enable)
{
    if (enable)
    {
        base->LP_CFG |= SPC_LP_CFG_LPBUFF_EN_MASK;
    }
    else
    {
        base->LP_CFG &= ~SPC_LP_CFG_LPBUFF_EN_MASK;
    }
}

/*!
 * @brief Enables/Disables CORE VDD IVS(Internal Voltage Scaling) in low power modes.
 *
 * This function gates CORE VDD IVS. When enabled, the IVS regulator will scale the
 * external input CORE VDD to a lower voltage level to reduce internal leakage.
 * IVS is invalid in Sleep or Deep power down mode.
 *
 * @param base SPC peripheral base address.
 * @param enable Enable/Disable IVS.
 *          true    -   enable CORE VDD IVS in Deep Sleep mode or Power Down mode.
 *          false   -   disable CORE VDD IVS in Deep Sleep mode or Power Down mode.
 */
static inline void SPC_EnableLowPowerModeCoreVDDInternalVoltageScaling(SPC_Type *base, bool enable)
{
    if (enable)
    {
        base->LP_CFG |= SPC_LP_CFG_COREVDD_IVS_EN_MASK;
    }
    else
    {
        base->LP_CFG &= ~SPC_LP_CFG_COREVDD_IVS_EN_MASK;
    }
}

/*!
 * @brief Sets the delay when exit the low power modes.
 *
 * @param base SPC peripheral base address.
 * @param delay The number of SPC timer clock cycles that the SPC waits on exit from low power modes.
 */
static inline void SPC_SetLowPowerWakeUpDelay(SPC_Type *base, uint16_t delay)
{
    base->LPWKUP_DELAY = SPC_LPWKUP_DELAY_LPWKUP_DELAY(delay);
}

/*!
 * @brief Configs regulators in Low Power mode.
 *
 * This function provides the method to config all on-chip regulators in Low Power mode.
 *
 * @param base SPC peripheral base address.
 * @param config Pointer to spc_lowpower_mode_regulators_config_t structure.
 * @retval #kStatus_Success Config regulators in Low power mode successful.
 * @retval #kStatus_SPC_BandgapModeWrong The bandgap mode setting in Low Power mode is wrong.
 * @retval #kStatus_SPC_Busy The SPC instance is busy to execute any type of power mode transition.
 * @retval #kStatus_SPC_CORELDOVoltageWrong The selected voltage level is wrong.
 * @retval #kStatus_SPC_CORELDOLowDriveStrengthIgnore Set driver strength to low will be ignored.
 * @retval #kStatus_SPC_CORELDOVoltageSetFail. Fail to change Core LDO voltage level.
 * @retval #kStatus_SPC_SYSLDOLowDriveStrengthIgnore Set driver strength to low will be ignored.
 * @retval #kStatus_SPC_DCDCPulseRefreshModeIgnore Set driver strength to Pulse Refresh mode will be ignored.
 * @retval #kStatus_SPC_DCDCLowDriveStrengthIgnore Set driver strength to Low Drive Strength will be ignored.
 */
status_t SPC_SetLowPowerModeRegulatorsConfig(SPC_Type *base, const spc_lowpower_mode_regulators_config_t *config);

/*!
 * @brief Disable/Enable VDD Core Glitch Detect in low power mode.
 *
 * @note State of glitch detect disable feature will be ignored if bandgap is disabled and
 * glitch detect hardware will be forced to OFF state.
 *
 * @param base SPC peripheral base address.
 * @param disable Used to disable/enable VDD Core Glitch detect feature.
 *         - \b true Disable VDD Core Low Voltage detect;
 *         - \b false Enable VDD Core Low Voltage detect.
 */
static inline void SPC_DisableLowPowerModeVddCoreGlitchDetect(SPC_Type *base, bool disable)
{
    if (disable)
    {
        base->LP_CFG |= SPC_LP_CFG_GLITCH_DETECT_DISABLE_MASK;
    }
    else
    {
        base->LP_CFG &= ~SPC_LP_CFG_GLITCH_DETECT_DISABLE_MASK;
    }
}

/*! @} */

/*!
 * @name Voltage Detect Status.
 * @{
 */
/*!
 * @brief Get Voltage Detect Status Flags.
 *
 * @param base SPC peripheral base address.
 * @return Voltage Detect Status Flags. See @ref _spc_voltage_detect_flags for details.
 */
static inline uint8_t SPC_GetVoltageDetectStatusFlag(SPC_Type *base)
{
    return (uint8_t)(base->VD_STAT);
}

/*!
 * @brief Clear Voltage Detect Status Flags.
 *
 * @param base SPC peripheral base address.
 * @param mask The mask of the voltage detect status flags. See @ref _spc_voltage_detect_flags for details.
 */
static inline void SPC_ClearVoltageDetectStatusFlag(SPC_Type *base, uint8_t mask)
{
    base->VD_STAT |= mask;
}

/*! @} */

/*!
 * @name Voltage Detect configuration for Core voltage domain.
 * @{
 */

/*!
 * @brief Configs CORE voltage detect options.
 *
 * This function config CORE voltage detect options.
 * @note: Setting both the voltage detect interrupt and reset
 *       enable will cause interrupt to be generated on exit from reset.
 *       If those conditioned is not desired, interrupt/reset so only one is enabled.
 *
 * @param base       SPC peripheral base address.
 * @param config     Pointer to spc_core_voltage_detect_config_t structure.
 */
void SPC_SetCoreVoltageDetectConfig(SPC_Type *base, const spc_core_voltage_detect_config_t *config);

/*!
 * @brief Locks Core voltage detect reset setting.
 *
 * This function locks core voltage detect reset setting. After invoking this function
 * any configuration of Core voltage detect reset will be ignored.
 *
 * @param base SPC peripheral base address.
 */
static inline void SPC_LockCoreVoltageDetectResetSetting(SPC_Type *base)
{
    base->VD_CORE_CFG |= SPC_VD_CORE_CFG_LOCK_MASK;
}

/*!
 * @brief Unlocks Core voltage detect reset setting.
 *
 * This function unlocks core voltage detect reset setting. If locks the Core
 * voltage detect reset setting, invoking this function to unlock.
 *
 * @param base SPC peripheral base address.
 */
static inline void SPC_UnlockCoreVoltageDetectResetSetting(SPC_Type *base)
{
    base->VD_CORE_CFG &= ~SPC_VD_CORE_CFG_LOCK_MASK;
}

/*!
 * @brief Enables/Disables the Core High Voltage Detector in Active mode.
 *
 * @note If the CORE_LDO high voltage detect is enabled in Active mode, please note that the bandgap must be enabled
 * and the drive strength of each regulator must not set to low.
 *
 * @param base SPC peripheral base address.
 * @param enable Enable/Disable Core HVD.
 *          true    -   Enable Core High voltage detector in active mode.
 *          false   -   Disable Core High voltage detector in active mode.
 *
 * @retval #kStatus_Success Enable/Disable Core High Voltage Detect successfully.
 */
status_t SPC_EnableActiveModeCoreHighVoltageDetect(SPC_Type *base, bool enable);

/*!
 * @brief Enables/Disables the Core Low Voltage Detector in Active mode.
 *
 * @note If the CORE_LDO low voltage detect is enabled in Active mode, please note that the bandgap must be enabled
 * and the drive strength of each regulator must not set to low.
 *
 * @param base SPC peripheral base address.
 * @param enable Enable/Disable Core LVD.
 *          true    -   Enable Core Low voltage detector in active mode.
 *          false   -   Disable Core Low voltage detector in active mode.
 *
 * @retval #kStatus_Success Enable/Disable Core Low Voltage Detect successfully.
 */
status_t SPC_EnableActiveModeCoreLowVoltageDetect(SPC_Type *base, bool enable);

/*!
 * @brief Enables/Disables the Core High Voltage Detector in Low Power mode.
 *
 * This function enables/disables the Core High Voltage Detector.
 * If enabled the Core High Voltage detector. The Bandgap mode in
 * low power mode must be programmed so that Bandgap is enabled.
 *
 * @note If the CORE_LDO high voltage detect is enabled in Low Power mode, please note that the bandgap must be enabled
 * and the drive strength of each regulator must not set to low in low power mode.
 *
 * @param base SPC peripheral base address.
 * @param enable Enable/Disable Core HVD.
 *          true    -   Enable Core High voltage detector in low power mode.
 *          false   -   Disable Core High voltage detector in low power mode.
 *
 * @retval #kStatus_Success Enable/Disable Core High Voltage Detect in low power mode successfully.
 */
status_t SPC_EnableLowPowerModeCoreHighVoltageDetect(SPC_Type *base, bool enable);

/*!
 * @brief Enables/Disables the Core Low Voltage Detector in Low Power mode.
 *
 * This function enables/disables the Core Low Voltage Detector.
 * If enabled the Core Low Voltage detector. The Bandgap mode in
 * low power mode must be programmed so that Bandgap is enabled.
 *
 * @note If the CORE_LDO low voltage detect is enabled in Low Power mode, please note that the bandgap must be enabled
 * and the drive strength of each regulator must not set to low in Low Power mode.
 *
 * @param base SPC peripheral base address.
 * @param enable Enable/Disable Core HVD.
 *          true    -   Enable Core Low voltage detector in low power mode.
 *          false   -   Disable Core Low voltage detector in low power mode.
 *
 * @retval #kStatus_Success Enable/Disable Core Low Voltage Detect in low power mode successfully.
 */
status_t SPC_EnableLowPowerModeCoreLowVoltageDetect(SPC_Type *base, bool enable);

/*! @} */

/*!
 * @name Voltage detect configuration for System Voltage domain.
 * @{
 */
/*!
 * @brief Set system VDD Low-voltage level selection.
 *
 * This function selects the system VDD low-voltage level. Changing system VDD low-voltage level
 * must be done after disabling the System VDD low voltage reset and interrupt.
 *
 * @deprecated In latest RM, reserved for all devices, will removed in next release.
 * 
 * @param base SPC peripheral base address.
 * @param level System VDD Low-Voltage level selection.
 */
void SPC_SetSystemVDDLowVoltageLevel(SPC_Type *base, spc_low_voltage_level_select_t level);

/*!
 * @brief Configs SYS voltage detect options.
 *
 * This function config SYS voltage detect options.
 * @note: Setting both the voltage detect interrupt and reset
 *       enable will cause interrupt to be generated on exit from reset.
 *       If those conditioned is not desired, interrupt/reset so only one is enabled.
 *
 * @param base       SPC peripheral base address.
 * @param config     Pointer to spc_system_voltage_detect_config_t structure.
 */
void SPC_SetSystemVoltageDetectConfig(SPC_Type *base, const spc_system_voltage_detect_config_t *config);

/*!
 * @brief Lock System voltage detect reset setting.
 *
 * This function locks system voltage detect reset setting. After invoking this function
 * any configuration of System Voltage detect reset will be ignored.
 *
 * @param base SPC peripheral base address.
 */
static inline void SPC_LockSystemVoltageDetectResetSetting(SPC_Type *base)
{
    base->VD_SYS_CFG |= SPC_VD_SYS_CFG_LOCK_MASK;
}

/*!
 * @brief Unlock System voltage detect reset setting.
 *
 * This function unlocks system voltage detect reset setting. If locks the System
 * voltage detect reset setting, invoking this function to unlock.
 *
 * @param base SPC peripheral base address.
 */
static inline void SPC_UnlockSystemVoltageDetectResetSetting(SPC_Type *base)
{
    base->VD_SYS_CFG &= ~SPC_VD_SYS_CFG_LOCK_MASK;
}

/*!
 * @brief Enables/Disables the System High Voltage Detector in Active mode.
 *
 * @note If the System_LDO high voltage detect is enabled in Active mode, please note that the bandgap must be enabled
 * and the drive strength of each regulator must not set to low in Active mode.
 *
 * @param base SPC peripheral base address.
 * @param enable Enable/Disable System HVD.
 *          true    -   Enable System High voltage detector in active mode.
 *          false   -   Disable System High voltage detector in active mode.
 *
 * @retval #kStatus_Success Enable/Disable System High Voltage Detect successfully.
 */
status_t SPC_EnableActiveModeSystemHighVoltageDetect(SPC_Type *base, bool enable);

/*!
 * @brief Enables/Disable the System Low Voltage Detector in Active mode.
 *
 * @note If the System_LDO low voltage detect is enabled in Active mode,
 * please note that the bandgap must be enabled and the drive strength of each
 * regulator must not set to low in Active mode.
 *
 * @param base SPC peripheral base address.
 * @param enable Enable/Disable System LVD.
 *          true    -   Enable System Low voltage detector in active mode.
 *          false   -   Disable System Low voltage detector in active mode.
 *
 * @retval #kStatus_Success Enable/Disable the System Low Voltage Detect successfully.
 */
status_t SPC_EnableActiveModeSystemLowVoltageDetect(SPC_Type *base, bool enable);

/*!
 * @brief Enables/Disables the System High Voltage Detector in Low Power mode.
 *
 * @note If the System_LDO high voltage detect is enabled in Low Power mode, please note
 * that the bandgap must be enabled and the drive strength of each regulator must
 * not set to low in Low Power  mode.
 *
 * @param base SPC peripheral base address.
 * @param enable Enable/Disable System HVD.
 *          true    -   Enable System High voltage detector in low power mode.
 *          false   -   Disable System High voltage detector in low power mode.
 *
 * @retval #kStatus_Success Enable/Disable System High Voltage Detect in low power mode successfully.
 */
status_t SPC_EnableLowPowerModeSystemHighVoltageDetect(SPC_Type *base, bool enable);

/*!
 * @brief Enables/Disables the System Low Voltage Detector in Low Power mode.
 *
 * @note If the System_LDO low voltage detect is enabled in Low Power mode,
 * please note that the bandgap must be enabled and the drive strength of each
 * regulator must not set to low in Low Power mode.
 *
 * @param base SPC peripheral base address.
 * @param enable Enable/Disable System HVD.
 *          true    -   Enable System Low voltage detector in low power mode.
 *          false   -   Disable System Low voltage detector in low power mode.
 *
 * @retval #kStatus_Success Enables System Low Voltage Detect in low power mode successfully.
 */
status_t SPC_EnableLowPowerModeSystemLowVoltageDetect(SPC_Type *base, bool enable);

/*! @} */

/*!
 * @name Voltage detect configuration for IO voltage domain.
 * @{
 */
/*!
 * @brief Set IO VDD Low-Voltage level selection.
 *
 * This function selects the IO VDD Low-voltage level. Changing IO VDD low-voltage level
 * must be done after disabling the IO VDD low voltage reset and interrupt.
 *
 * @param base SPC peripheral base address.
 * @param level IO VDD Low-voltage level selection.
 */
void SPC_SetIOVDDLowVoltageLevel(SPC_Type *base, spc_low_voltage_level_select_t level);

/*!
 * @brief Configs IO voltage detect options.
 *
 * This function config IO voltage detect options.
 * @note: Setting both the voltage detect interrupt and reset
 *       enable will cause interrupt to be generated on exit from reset.
 *       If those conditioned is not desired, interrupt/reset so only one is enabled.
 *
 * @param base       SPC peripheral base address.
 * @param config     Pointer to spc_voltage_detect_config_t structure.
 */
void SPC_SetIOVoltageDetectConfig(SPC_Type *base, const spc_io_voltage_detect_config_t *config);

/*!
 * @brief Lock IO Voltage detect reset setting.
 *
 * This function locks IO voltage detect reset setting. After invoking this function
 * any configuration of system voltage detect reset will be ignored.
 *
 * @param base SPC peripheral base address.
 */
static inline void SPC_LockIOVoltageDetectResetSetting(SPC_Type *base)
{
    base->VD_IO_CFG |= SPC_VD_IO_CFG_LOCK_MASK;
}

/*!
 * @brief Unlock IO voltage detect reset setting.
 *
 * This function unlocks IO voltage detect reset setting. If locks the IO
 * voltage detect reset setting, invoking this function to unlock.
 *
 * @param base SPC peripheral base address.
 */
static inline void SPC_UnlockIOVoltageDetectResetSetting(SPC_Type *base)
{
    base->VD_IO_CFG &= ~SPC_VD_IO_CFG_LOCK_MASK;
}

/*!
 * @brief Enables/Disables the IO High Voltage Detector in Active mode.
 *
 * @note If the IO high voltage detect is enabled in Active mode, please note that the bandgap must be enabled
 * and the drive strength of each regulator must not set to low in Active mode.
 *
 * @param base SPC peripheral base address.
 * @param enable Enable/Disable IO HVD.
 *          true    -   Enable IO High voltage detector in active mode.
 *          false   -   Disable IO High voltage detector in active mode.
 *
 * @retval #kStatus_Success Enable/Disable IO High Voltage Detect successfully.
 */
status_t SPC_EnableActiveModeIOHighVoltageDetect(SPC_Type *base, bool enable);

/*!
 * @brief Enables/Disables the IO Low Voltage Detector in Active mode.
 *
 * @note If the IO low voltage detect is enabled in Active mode, please note that the bandgap must be enabled
 * and the drive strength of each regulator must not set to low in Active mode.
 *
 * @param base SPC peripheral base address.
 * @param enable Enable/Disable IO LVD.
 *          true    -   Enable IO Low voltage detector in active mode.
 *          false   -   Disable IO Low voltage detector in active mode.
 *
 * @retval #kStatus_Success Enable IO Low Voltage Detect successfully.
 */
status_t SPC_EnableActiveModeIOLowVoltageDetect(SPC_Type *base, bool enable);

/*!
 * @brief Enables/Disables the IO High Voltage Detector in Low Power mode.
 *
 * @note If the IO high voltage detect is enabled in Low Power mode, please note that the bandgap must be enabled
 * and the drive strength of each regulator must not set to low in Low Power mode.
 *
 * @param base SPC peripheral base address.
 * @param enable Enable/Disable IO HVD.
 *          true    -   Enable IO High voltage detector in low power mode.
 *          false   -   Disable IO High voltage detector in low power mode.
 *
 * @retval #kStatus_Success Enable IO High Voltage Detect in low power mode successfully.
 */
status_t SPC_EnableLowPowerModeIOHighVoltageDetect(SPC_Type *base, bool enable);

/*!
 * @brief Enables/Disables the IO Low Voltage Detector in Low Power mode.
 *
 * @note If the IO low voltage detect is enabled in Low Power mode, please note that the bandgap must be enabled
 * and the drive strength of each regulator must not set to low in Low Power mode.
 *
 * @param base SPC peripheral base address.
 * @param enable Enable/Disable IO LVD.
 *          true    -   Enable IO Low voltage detector in low power mode.
 *          false   -   Disable IO Low voltage detector in low power mode.
 *
 * @retval #kStatus_Success Enable/Disable IO Low Voltage Detect in low power mode successfully.
 */
status_t SPC_EnableLowPowerModeIOLowVoltageDetect(SPC_Type *base, bool enable);

/*! @} */

/*!
 * @name External Voltage domains configuration.
 * @{
 */
/*!
 * @brief Configs external voltage domains
 *
 * This function configs external voltage domains isolation.
 *
 * @param base SPC peripheral base address.
 * @param lowPowerIsoMask The mask of external domains isolate enable during low power mode. Please read the Reference
 * Manual for the Bitmap.
 * @param IsoMask The mask of external domains isolate. Please read the Reference Manual for the Bitmap.
 */
void SPC_SetExternalVoltageDomainsConfig(SPC_Type *base, uint8_t lowPowerIsoMask, uint8_t IsoMask);

/*!
 * @brief Gets External Domains status.
 *
 * This function configs external voltage domains status.
 *
 * @param base SPC peripheral base address.
 * @return The status of each external domain.
 */
static inline uint8_t SPC_GetExternalDomainsStatus(SPC_Type *base)
{
    return (uint8_t)(base->EVD_CFG >> SPC_EVD_CFG_REG_EVDSTAT_SHIFT);
}

/*! @} */

/*!
 * @name Set CORE LDO Regulator.
 * @{
 */
/*!
 * @brief Enable/Disable Core LDO regulator.
 *
 * @note The CORE LDO enable bit is write-once.
 *
 * @param base SPC peripheral base address.
 * @param enable Enable/Disable CORE LDO Regulator.
 *          true   -   Enable CORE LDO Regulator.
 *          false  -   Disable CORE LDO Regulator.
 */
static inline void SPC_EnableCoreLDORegulator(SPC_Type *base, bool enable)
{
    if (enable)
    {
        base->CNTRL |= SPC_CNTRL_CORELDO_EN_MASK;
    }
    else
    {
        /*
         * $Branch Coverage Justification$
         * If CORE_LDO is disabled, all RAMs data will powered off.
         */
        base->CNTRL &= ~SPC_CNTRL_CORELDO_EN_MASK;
    }
}

/*!
 * @brief Enable/Disable the CORE LDO Regulator pull down in Deep Power Down.
 *
 * @note This function only useful when enabled the CORE LDO Regulator.
 *
 * @param base SPC peripheral base address.
 * @param pulldown Enable/Disable CORE LDO pulldown in Deep Power Down mode.
 *          true    -   CORE LDO Regulator will discharge in Deep Power Down mode.
 *          false   -   CORE LDO Regulator will not discharge in Deep Power Down mode.
 */
static inline void SPC_PullDownCoreLDORegulator(SPC_Type *base, bool pulldown)
{
    if (pulldown)
    {
        base->CORELDO_CFG &= ~SPC_CORELDO_CFG_DPDOWN_PULLDOWN_DISABLE_MASK;
    }
    else
    {
        base->CORELDO_CFG |= SPC_CORELDO_CFG_DPDOWN_PULLDOWN_DISABLE_MASK;
    }
}

/*!
 * @brief Configs Core LDO VDD Regulator in Active mode.
 *
 * @note If any voltage detect feature is enabled in Active mode, then CORE_LDO's drive strength must not set to low.
 *
 * @note Core VDD level for the Core LDO low power regulator can only be changed when CORELDO_VDD_DS is normal
 *
 * @param base SPC peripheral base address.
 * @param option Pointer to the spc_active_mode_core_ldo_option_t structure.
 *
 * @retval #kStatus_Success Config Core LDO regulator in Active power mode successful.
 * @retval #kStatus_SPC_Busy The SPC instance is busy to execute any type of power mode transition.
 * @retval #kStatus_SPC_CORELDOLowDriveStrengthIgnore If any voltage detect enabled, core_ldo's drive strength can not
 * set to low.
 * @retval #kStatus_SPC_CORELDOVoltageWrong The selected voltage level in active mode is not allowed.
 */
status_t SPC_SetActiveModeCoreLDORegulatorConfig(SPC_Type *base, const spc_active_mode_core_ldo_option_t *option);

/*!
 * @brief Configs CORE LDO Regulator in low power mode
 *
 * This function configs CORE LDO Regulator in Low Power mode.
 * If CORE LDO VDD Drive Strength is set to Normal, the CORE LDO VDD regulator voltage
 * level in Active mode must be equal to the voltage level in Low power mode. And the Bandgap
 * must be programmed to select bandgap enabled.
 * Core VDD voltage levels for the Core LDO low power regulator can only be changed when the CORE
 * LDO Drive Strength set as Normal.
 *
 * @param base SPC peripheral base address.
 * @param option Pointer to the spc_lowpower_mode_core_ldo_option_t structure.
 *
 * @retval #kStatus_Success Config Core LDO regulator in power mode successfully.
 * @retval #kStatus_SPC_Busy The SPC instance is busy to execute any type of power mode transition.
 * @retval #kStatus_SPC_CORELDOLowDriveStrengthIgnore Set driver strength to low will be ignored.
 * @retval #kStatus_SPC_CORELDOVoltageSetFail. Fail to change Core LDO voltage level.
 */
status_t SPC_SetLowPowerModeCoreLDORegulatorConfig(SPC_Type *base, const spc_lowpower_mode_core_ldo_option_t *option);

/*!
 * @name Set System LDO Regulator.
 * @{
 */
/*!
 * @brief Enable/Disable System LDO regulator.
 *
 * @note The SYSTEM LDO enable bit is write-once.
 *
 * @param base SPC peripheral base address.
 * @param enable Enable/Disable System LDO Regulator.
 *          true     -   Enable System LDO Regulator.
 *          false    -    Disable System LDO Regulator.
 */
static inline void SPC_EnableSystemLDORegulator(SPC_Type *base, bool enable)
{
    if (enable)
    {
        base->CNTRL |= SPC_CNTRL_SYSLDO_EN_MASK;
    }
    else
    {
        /*
         * $Branch Coverage Justification$
         * If SYSTEM_LDO is disabled, may cause some unexpected issues.
         */
        base->CNTRL &= ~SPC_CNTRL_SYSLDO_EN_MASK;
    }
}

/*!
 * @brief Enable/Disable current sink feature of System LDO Regulator.
 *
 * @param base SPC peripheral base address.
 * @param sink Enable/Disable current sink feature.
 *          true    -   Enable current sink feature of System LDO Regulator.
 *          false   -   Disable current sink feature of System LDO Regulator.
 */
static inline void SPC_EnableSystemLDOSinkFeature(SPC_Type *base, bool sink)
{
    if (sink)
    {
        base->SYSLDO_CFG |= SPC_SYSLDO_CFG_ISINKEN_MASK;
    }
    else
    {
        base->SYSLDO_CFG &= ~SPC_SYSLDO_CFG_ISINKEN_MASK;
    }
}

/*!
 * @brief Configs System LDO VDD Regulator in Active mode.
 *
 * This function configs System LDO VDD Regulator in Active mode.
 * If System LDO VDD Drive Strength is set to Normal, the Bandgap mode in Active mode must be programmed
 * to a value that enables the bandgap.
 * If any voltage detects are kept enabled, configuration to set System LDO VDD drive strength to low will
 * be ignored.
 * If select System LDO VDD Regulator voltage level to Over Drive Voltage, the Drive Strength of System LDO VDD
 * Regulator must be set to Normal otherwise the regulator Drive Strength will be forced to Normal.
 * If select System LDO VDD Regulator voltage level to Over Drive Voltage, the High voltage detect must be disabled.
 * Otherwise it will be fail to regulator to Over Drive Voltage.
 *
 * @param base SPC peripheral base address.
 * @param option Pointer to the spc_active_mode_sys_ldo_option_t structure.
 *
 * @retval #kStatus_Success Config System LDO regulator in Active power mode successful.
 * @retval #kStatus_SPC_Busy The SPC instance is busy to execute any type of power mode transition.
 * @retval #kStatus_SPC_SYSLDOOverDriveVoltageFail Fail to regulator to Over Drive Voltage.
 * @retval #kStatus_SPC_SYSLDOLowDriveStrengthIgnore Set driver strength to Low will be ignored.
 */
status_t SPC_SetActiveModeSystemLDORegulatorConfig(SPC_Type *base, const spc_active_mode_sys_ldo_option_t *option);

/*!
 * @brief Configs System LDO regulator in low power modes.
 *
 * This function configs System LDO regulator in low power modes.
 * If System LDO VDD Regulator Drive strength is set to normal, bandgap mode in low power
 * mode must be programmed to a value that enables the Bandgap.
 * If any High voltage detectors or Low Voltage detectors are kept enabled, configuration
 * to set System LDO Regulator drive strength as Low will be ignored.
 *
 * @param base SPC peripheral base address.
 * @param option Pointer to spc_lowpower_mode_sys_ldo_option_t structure.
 *
 * @retval #kStatus_Success Config System LDO regulator in Low Power Mode successfully.
 * @retval #kStatus_SPC_Busy The SPC instance is busy to execute any type of power mode transition.
 * @retval #kStatus_SPC_SYSLDOLowDriveStrengthIgnore Set driver strength to low will be ignored.
 */
status_t SPC_SetLowPowerModeSystemLDORegulatorConfig(SPC_Type *base, const spc_lowpower_mode_sys_ldo_option_t *option);

/*! @} */

/*!
 * @name Set DCDC Regulator.
 * @{
 */

/*!
 * @brief Enable/Disable DCDC Regulator.
 *
 * @note The DCDC enable bit is write-once.
 *
 * @param base SPC peripheral base address.
 * @param enable Enable/Disable DCDC Regulator.
 *          true    -   Enable DCDC Regulator.
 *          false   -   Disable DCDC Regulator.
 */
static inline void SPC_EnableDCDCRegulator(SPC_Type *base, bool enable)
{
    if (enable)
    {
        base->CNTRL |= SPC_CNTRL_DCDC_EN_MASK;
    }
    else
    {
        /*
         * $Branch Coverage Justification$
         * If DCDC is disabled, all RAMs data will powered off.
         */
        base->CNTRL &= ~SPC_CNTRL_DCDC_EN_MASK;
    }
}

/*!
 * @brief Config DCDC Burst options
 *
 * @param base SPC peripheral base address.
 * @param config Pointer to spc_dcdc_burst_config_t structure.
 */
void SPC_SetDCDCBurstConfig(SPC_Type *base, spc_dcdc_burst_config_t *config);

/*!
 * @brief Set the count value of the reference clock.
 *
 * This function set the count value of the reference clock to control the frequency
 * of dcdc refresh when dcdc is configured in Pulse Refresh mode.
 *
 * @param base SPC peripheral base address.
 * @param count The count value, 16 bit width.
 */
void SPC_SetDCDCRefreshCount(SPC_Type *base, uint16_t count);

/*!
 * @brief Configs DCDC VDD Regulator in Active mode.
 *
 * This function configs DCDC VDD Regulator in Active mode.
 * If DCDDC VDD Drive Strength is set to Normal, the Bandgap mode in Active mode must be programmed
 * to a value that enable the bandgap.
 * If any voltage detects are kept enabled, configuration to set DCDC VDD drive strength to low will
 * be ignored.
 * When switching DCDC from low drive strength to Normal driver strength, make sure the DCDC high VDD LVL
 * setting to the same level that was set prior to switching the DCDC to low drive strength.
 *
 * @param base SPC peripheral base address.
 * @param option Pointer to the spc_active_mode_dcdc_option_t structure.
 *
 * @retval #kStatus_Success Config DCDC regulator in Active power mode successful.
 * @retval #kStatus_SPC_Busy The SPC instance is busy to execute any type of power mode transition.
 * @retval #kStatus_SPC_DCDCLowDriveStrengthIgnore Set driver strength to Low will be ignored.
 */
status_t SPC_SetActiveModeDCDCRegulatorConfig(SPC_Type *base, const spc_active_mode_dcdc_option_t *option);

/*!
 * @brief Configs DCDC VDD Regulator in Low power modes.
 *
 * This function configs DCDC VDD Regulator in Low Power modes.
 * If DCDC VDD Drive Strength is set to Normal, the Bandgap mode in Low Power mode must be programmed
 * to a value that enables the Bandgap.
 * If any of voltage detectors are kept enabled, configuration to set DCDC VDD Drive Strength to Low or Pulse mode
 * will be ignored.
 * In Deep Power Down mode, DCDC regulator is always turned off.
 *
 * @param base SPC peripheral base address.
 * @param option Pointer to the spc_lowpower_mode_dcdc_option_t structure.
 *
 * @retval #kStatus_Success Config DCDC regulator in low power mode successfully.
 * @retval #kStatus_SPC_Busy The SPC instance is busy to execute any type of power mode transition.
 * @retval #kStatus_SPC_DCDCPulseRefreshModeIgnore Set driver strength to Pulse Refresh mode will be ignored.
 * @retval #kStatus_SPC_DCDCLowDriveStrengthIgnore Set driver strength to Low Drive Strength will be ignored.
 */
status_t SPC_SetLowPowerModeDCDCRegulatorConfig(SPC_Type *base, const spc_lowpower_mode_dcdc_option_t *option);

/*! @} */

/*!
 * @name SRAM Control Interfaces.
 * @{
 */

/*!
 * @brief Set the SRAM operate voltage level.
 *
 * @param base SPC peripheral base address.
 * @param voltage Target SRAM operate voltage level, please refer to @ref spc_sram_operat_voltage_t.
 */
void SPC_SetSRAMOperateVoltage(SPC_Type *base, spc_sram_operat_voltage_t voltage);

/*! @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /* FSL_SPC_H_ */
