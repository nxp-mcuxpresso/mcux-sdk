/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2020, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_SPM_H_
#define FSL_SPM_H_

#include "fsl_common.h"

/*! @addtogroup spm */
/*! @{ */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief SPM driver version */
#define FSL_SPM_DRIVER_VERSION (MAKE_VERSION(2, 3, 0)) /*!< Version 2.3.0. */

/*! @} */

/*!
 * @brief IP version ID definition.
 */
typedef struct _spm_version_id
{
    uint16_t feature; /*!< Feature set number.           */
    uint8_t minor;    /*!< Minor version number.         */
    uint8_t major;    /*!< Major version number.         */
} spm_version_id_t;

/*!
 * @brief Status of last MCU STOP Mode Power Configuration.
 */
typedef enum _spm_mcu_low_power_mode_status
{
    kSPM_McuLowPowerModeReserved = 0U,        /*!< Reserved. */
    kSPM_McuLowPowerModeSTOP     = 1U,        /*!< Last Low Power mode is STOP. */
    kSPM_McuLowPowerModeVLPS     = (1U << 1), /*!< Last Low Power mode is VLPS. */
    kSPM_McuLowPowerModeLLS      = (1U << 2), /*!< Last Low Power mode is LLS. */
    kSPM_McuLowPowerModeVLLS23   = (1U << 3), /*!< Last Low Power mode is VLLS23. */
    kSPM_McuLowPowerModeVLLS01   = (1U << 4), /*!< Last Low Power mode is VLLS01. */
} spm_mcu_low_power_mode_status_t;

/*!
 * @brief define the mask code for LDO regulators.
 *
 * These mask can be combined with 'or' as a parameter to any function.
 */
enum _spm_ldo_regulator
{
    kSPM_CoreLdo = 1U,        /*!< Mask code for CORE LDO. */
    kSPM_AuxLdo  = (1U << 1), /*!< Mask code for AUX LDO.  */
    kSPM_DcdcLdo = (1U << 2), /*!< Mask code for DCDC LDO. */
};

/*!
 * @brief Keep the regulator status information.
 */
typedef struct _spm_regulator_status
{
    spm_mcu_low_power_mode_status_t mcuLowPowerModeStatus; /*!< Status of last MCU STOP Mode Power Configuration. */
    bool isDcdcLdoOn;                                      /*!< DCDC LDO regulator enabled. */
    bool isAuxLdoOn;                                       /*!< Aux LDO regulator enabled. */
    bool isCoreLdoOn;                                      /*!< Core LDO regulator enabled. */
} spm_regulator_status_t;

/*!
 * @brief Configure the CORE LDO in run modes.
 */
enum _spm_core_ldo_run_mode_config
{
    kSPM_CoreLdoRunModeEnableRtcPowerMonitor =
        SPM_CORERCNFG_RTCVDDMEN_MASK, /*!< RTC power monitor enabled in run modes. */
    kSPM_CoreLdoRunModeEnableUsbPowerMonitor =
        SPM_CORERCNFG_USBVDDMEN_MASK, /*!< USB power monitor enabled in run modes. */
    kSPM_CoreLdoRunModeEnableVddioPowerMonitor =
        SPM_CORERCNFG_VDDIOVDDMEN_MASK, /*!< VDDIO power monitor enabled in run modes. */
};

/*!
 * @brief Configure the CORE LDO in low power modes.
 */
enum _spm_core_ldo_low_power_mode_config
{
    kSPM_CoreLdoLowPowerModeEnableRtcPowerMonitor =
        SPM_CORELPCNFG_RTCVDDMEN_MASK, /*!< RTC power monitor enabled in LP modes. */
    kSPM_CoreLdoLowPowerModeEnableUsbPowerMonitor =
        SPM_CORELPCNFG_USBVDDMEN_MASK, /*!< USB power monitor enabled in LP modes. */
    kSPM_CoreLdoLowPowerModeEnableVddioPowerMonitor =
        SPM_CORELPCNFG_VDDIOVDDMEN_MASK, /*!< VDDIO power monitor enabled in LP modes. */
    kSPM_CoreLdoLowPowerModeEnableAllReference =
        SPM_CORELPCNFG_ALLREFEN_MASK,                                        /*!< Enable all reference (bandgap, WELL
                                                                                  BIAS, 1k clk and LP 25na) in VLLS0/1. */
    kSPM_CoreLdoLowPowerModeEnableHighDrive = SPM_CORELPCNFG_LPHIDRIVE_MASK, /*!< Enable high driver in low power. */
    kSPM_CoreLdoLowPowerModeEnableLVD =
        SPM_CORELPCNFG_LVDEN_MASK, /*!< Enable level voltage detect in low power modes. */
    kSPM_CoreLdoLowPowerModeEnablePOR = SPM_CORELPCNFG_POREN_MASK, /*!< POR brownout remains enabled in VLLS0/1 mode. */
    kSPM_CoreLdoLowPowerModeEnableLPO = SPM_CORELPCNFG_LPOEN_MASK, /*!< LPO remains enabled in VLLS0/1 modes. */
    kSPM_CoreLdoLowPowerModeEnableBandgapBufferHightDrive =
        SPM_CORELPCNFG_BGBDS_MASK, /*!< Enable the high drive for Bandgap Buffer. */
    kSPM_CoreLdoLowPowerModeEnableBandgapBuffer = SPM_CORELPCNFG_BGBEN_MASK, /*!< Enable Bandgap Buffer. */
    kSPM_CoreLdoLowPowerModeEnableBandgapInVLPx =
        SPM_CORELPCNFG_BGEN_MASK, /*!< Enable Bandgap in STOP/VLPx/LLS and VLLSx mode. */
    kSPM_CoreLdoLowPowerModeRemainInHighPower =
        SPM_CORELPCNFG_LPSEL_MASK, /*!< Core LDO remains in high power state in VLP/Stop modes. */
};

/*!
 * @brief Low-voltage Detect Voltage Select
 */
typedef enum _spm_low_volt_detect_volt_select
{
    kSPM_LowVoltDetectLowTrip  = 0U, /*!< Low-trip point selected (VLVD = VLVDL )*/
    kSPM_LowVoltDetectHighTrip = 1U  /*!< High-trip point selected (VLVD = VLVDH )*/
} spm_low_volt_detect_volt_select_t;

/*!
 * @brief Low-voltage Detect Configuration Structure.
 *
 * This structure reuses the configuration structure from legacy PMC module.
 */
typedef struct _spm_low_volt_detect_config
{
    /* VDD voltage detection. */
    bool enableIntOnVddLowVolt;   /*!< Enable interrupt when VDD Low-voltage detect. */
    bool enableResetOnVddLowVolt; /*!< Enable forcing an MCU reset when VDD Low-voltage detect. */
    spm_low_volt_detect_volt_select_t vddLowVoltDetectSelect; /*!< Low-voltage detect trip point voltage selection. */

    /* CORE voltage detection. */
    bool enableIntOnCoreLowVolt;   /*!< Enable interrupt when Core Low-voltage detect. */
    bool enableResetOnCoreLowVolt; /*!< Enable forcing an MCU reset when Core Low-voltage detect. */
} spm_low_volt_detect_config_t;

/*!
 * @brief Low-voltage Warning Voltage Select.
 */
typedef enum _spm_low_volt_warning_volt_select
{
    kSPM_LowVoltWarningLowTrip  = 0U, /*!< Low-trip point selected (VLVW = VLVW1)*/
    kSPM_LowVoltWarningMID1Trip = 1U, /*!< Mid1-trip point selected (VLVW = VLVW2)*/
    kSPM_LowVoltWarningMID2Trip = 2U, /*!< Mid2-trip point selected (VLVW = VLVW3)*/
    kSPM_LowVoltWarningHighTrip = 3U  /*!< High-trip point selected (VLVW = VLVW4)*/
} spm_low_volt_warning_volt_select_t;

/*!
 * @brief Low-voltage Warning Configuration Structure
 */
typedef struct _spm_low_volt_warning_config
{
    bool enableIntOnVddLowVolt;                                /*!< Enable interrupt when low-voltage warning*/
    spm_low_volt_warning_volt_select_t vddLowVoltDetectSelect; /*!< Low-voltage warning trip point voltage selection*/
} spm_low_volt_warning_config_t;

/*!
 * @brief High-voltage Detect Voltage Select.
 */
typedef enum _spm_high_volt_detect_volt_select
{
    kSPM_HighVoltDetectLowTrip  = 0U, /*!< Low-trip point selected (VHVD = VHVDL )*/
    kSPM_HighVoltDetectHighTrip = 1U  /*!< High-trip point selected (VHVD = VHVDH )*/
} spm_high_volt_detect_volt_select_t;

/*!
 * @brief High-voltage Detect Configuration Structure.
 *
 * This structure reuses the configuration structure from legacy PMC module.
 */
typedef struct _spm_high_volt_detect_config
{
    bool enableIntOnVddHighVolt;                                /*!< Enable interrupt when high-voltage detect*/
    bool enableResetOnVddHighVolt;                              /*!< Enable system reset when high-voltage detect*/
    spm_high_volt_detect_volt_select_t vddHighVoltDetectSelect; /*!< High-voltage detect trip point voltage selection*/
} spm_high_volt_detect_config_t;

/*!
 * @brief Defines the AUX LDO low power behiavior when in low power modes.
 */
typedef enum _spm_aux_ldo_low_power_mode
{
    kSPM_AuxLdoEnterLowPowerInLowPowerModes = 0U, /*!< AUX LDO regulator enters low power state in VLP/Stop modes. */
    kSPM_AuxLdoRemainInHighPowerInLowPowerModes =
        1U, /*!< AUX LDO regulator remains in high power state in VLP/Stop modes. */
} spm_aux_ldo_low_power_mode_t;

/*!
 * @brief Selects the soft start duration delay for the IO 1.8 full power regulator.
 */
typedef enum _spm_aux_ldo_io_soft_start_duration
{
    kSPM_AuxLdoSoftStartDuration110us = 0U, /*!< 110 us. */
    kSPM_AuxLdoSoftStartDuration95us  = 1U, /*!< 95 us. */
    kSPM_AuxLdoSoftStartDuration60us  = 2U, /*!< 60 us. */
    kSPM_AuxLdoSoftStartDuration48us  = 3U, /*!< 48 us. */
    kSPM_AuxLdoSoftStartDuration38us  = 4U, /*!< 38 us. */
    kSPM_AuxLdoSoftStartDuration30us  = 5U, /*!< 30 us. */
    kSPM_AuxLdoSoftStartDuration24us  = 6U, /*!< 24 us. */
    kSPM_AuxLdoSoftStartDuration17us  = 7U, /*!< 17 us. */
} spm_aux_ldo_io_soft_start_duration_t;

/*!
 * @brief IO Regulator Voltage Select.
 */
typedef enum _spm_aux_io_regulator_volt_select
{
    kSPM_AuxIoRegulatorVoltLevel1p8 = 0U, /*!< Regulate to 1.8V. */
    kSPM_AuxIoRegulatorVoltLevel1p5 = 1U, /*!< Regulate to 1.5V. */
} spm_aux_io_regulator_volt_select_t;

/*!
 * @brief Aux LDO configuration structure.
 */
typedef struct _spm_aux_ldo_config
{
    spm_aux_ldo_low_power_mode_t lowPowerMode; /*!< AUX LDO low power behaviour when in low power modes. */
    spm_aux_ldo_io_soft_start_duration_t
        ioSoftStartDuration; /*!< Selects the soft start duration delay for the IO 1.8 full power regulator. */
    spm_aux_io_regulator_volt_select_t ioRegulatorVolt; /*!< IO Regulator Voltage Select. */
} spm_aux_ldo_config_t;

/*!
 * @brief Configuration for setting DCDC integrator value.
 */
typedef struct _spm_dcdc_integrator_value_config
{
    double vddCoreValue; /*!< VDD_CORE output voltage value. */
    double vBatValue;    /*!< Battery input voltage value, or the Vdd_dcdcin voltage value. */
} spm_dcdc_integrator_config_t;

/*!
 * @brief Defines the selection of DCDC vbat voltage divider for ADC measure.
 */
typedef enum _spm_dcdc_vbat_adc_divider
{
    kSPM_DcdcVbatAdcOff      = 0U, /*!< OFF. */
    kSPM_DcdcVbatAdcDivider1 = 1U, /*!< VBAT. */
    kSPM_DcdcVbatAdcDivider2 = 2U, /*!< VBAT /2. */
    kSPM_DcdcVbatAdcDivider4 = 3U, /*!< VBAT /4. */
} spm_dcdc_vbat_adc_divider_t;

/*!
 * @brief Defines the selection of low power request pin out pin polarity.
 */
typedef enum _spm_low_power_req_out_pin_pol
{
    kSPM_LowPowerReqOutPinHighTruePol = 0U, /*!< High true polarity. */
    kSPM_LowPowerReqOutPinLowTruePol  = 1U, /*!< Low true polarity. */
} spm_low_power_req_out_pin_pol_t;

/*!
 * @brief Configuration structure of low power request out pin.
 */
typedef struct _spm_low_power_req_out_pin_config
{
    spm_low_power_req_out_pin_pol_t pinOutPol; /*!< ow power request pin out pin polarity. */
    bool pinOutEnable;                         /*!< Low Power request output pin is enabled or not. */
} spm_low_power_req_out_pin_config_t;

/*!
 * @brief Defines the selection of DCDC driver strength.
 *
 * The more FETs are enabled, the more drive strength DCDC would provide.
 */
typedef enum _spm_dcdc_drive_strength
{
    kSPM_DcdcDriveStrengthWithNormal                   = 0U,  /*!< No additional FET setting. */
    kSPM_DcdcDriveStrengthWithHalfFETs                 = 0x4, /*!< Half FETs. */
    kSPM_DcdcDriveStrengthWithDoubleFETs               = 0x2, /*!< Double FETs. */
    kSPM_DcdcDriveStrengthWithExtraDoubleFETs          = 0x1, /*!< Extra Double FETs. */
    kSPM_DcdcDriveStrengthWithHalfAndDoubleFETs        = 0x6, /*!< Half + Double FETs. */
    kSPM_DcdcDriveStrengthWithHalfAndExtraDoubleFETs   = 0x5, /*!< Half + Extra Double FETs. */
    kSPM_DcdcDriveStrengthWithDoubleAndExtraDoubleFETs = 0x3, /*!< Double + Extra Double FETs. */
    kSPM_DcdcDriveStrengthWithAllFETs                  = 7U,  /*!< Half + Double + Extra Double FETs. */
} spm_dcdc_drive_strength_t;

/*!
 * @brief DCDC flags.
 */
enum _spm_dcdc_flags
{
    kSPM_DcdcStableOKFlag = (int)SPM_DCDCSC_DCDC_STS_DC_OK_MASK, /*!< Status flag to indicate DCDC lock. */
    kSPM_DcdcClockFaultFlag =
        SPM_DCDCSC_CLKFLT_FAULT_MASK, /*!< Asserts if DCDC detect a clk fault. Will cause a system lvd reset to assert.
                                       */
};

/*!
 * @brief Loop control configuration.
 */
typedef struct _spm_dcdc_loop_control_config
{
    bool enableCommonHysteresis; /*!< Enable hysteresis in switching converter differential mode analog comparators.
                                      This feature improves transient supply ripple and efficiency. */
    bool enableDifferentialHysteresis; /*!< Enable hysteresis in switching converter common mode analog comparators.
                                            This feature improves transient supply ripple and efficiency. */
    bool invertHysteresisSign;         /*!< Invert the sign of the hysteresis in DC-DC analog comparators.
                                            Should be enabled when in Pulsed mode. */
} spm_dcdc_loop_control_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*! @name System Power Manager. */
/*! @{ */

/*!
 * @brief Gets the SPM version ID.
 *
 * This function gets the SPM version ID, including major version number,
 * minor version number, and a feature specification number.
 *
 * @param base SPM peripheral base address.
 * @param versionId     Pointer to version ID structure.
 */
static inline void SPM_GetVersionId(SPM_Type *base, spm_version_id_t *versionId)
{
    *((uint32_t *)(uint32_t)versionId) = base->VERID;
}

/*!
 * @brief Gets the regulators Status.
 *
 * @param base SPM peripheral base address.
 * @param info Pointer to status structure, see to #spm_regulator_status_t.
 */
void SPM_GetRegulatorStatus(SPM_Type *base, spm_regulator_status_t *info);

/*!
 * @brief Controls which regulators are enabled in RUN and HSRUN modes.
 *
 * This function controls which regulator (CORE LDO, AUX LDO, and DCDC) are enabled in RUN and HSRUN
 * modes. It sets the SPM_RCTRL register.
 * Note that the RCTRL bits are reset solely on a POR/LVD only event.
 *
 * @param base SPM peripheral base address.
 * @param enable Enable or disable the LDOs list in ldoMask.
 * @param ldoMask Mask value of LDO list. See to #_spm_ldo_regulator.
 */
static inline void SPM_EnableRegulatorInRunMode(SPM_Type *base, bool enable, uint32_t ldoMask)
{
    if (true == enable)
    {
        base->RCTRL |= SPM_RCTRL_REGSEL(ldoMask);
    }
    else
    {
        base->RCTRL &= ~SPM_RCTRL_REGSEL(ldoMask);
    }
}

/*!
 * @brief Controls which regulators are enabled in low power modes.
 *
 * This function controls which regulator (CORE LDO, AUX LDO, and DCDC) are enabled in low power
 * modes. It sets the SPM_LPCTRL register.
 * Note that the SPM_LPCTRL bits are reset solely on a POR/LVD only event.
 *
 * @param base SPM peripheral base address.
 * @param enable Enable or disable the LDOs list in ldoMask.
 * @param ldoMask Mask value of LDO list.
 */
static inline void SPM_EnableRegulatorInLowPowerMode(SPM_Type *base, bool enable, uint32_t ldoMask)
{
    if (true == enable)
    {
        base->LPCTRL |= SPM_LPCTRL_REGSEL(ldoMask);
    }
    else
    {
        base->LPCTRL &= ~SPM_LPCTRL_REGSEL(ldoMask);
    }
}

/*!
 * @brief Configures the CORE LDO working in run modes.
 *
 * @param base SPM peripheral base address.
 * @param configMask Mask value of configuration items. See to #_spm_core_ldo_run_mode_config.
 */
static inline void SPM_SetCoreLdoRunModeConfig(SPM_Type *base, uint32_t configMask)
{
    base->CORERCNFG = configMask;
}

/*!
 * @brief Configures the CORE LDO working in low power modes.
 *
 * @param base SPM peripheral base address.
 * @param configMask Mask value of configuration items. See to #_spm_core_ldo_low_power_mode_config.
 */
static inline void SPM_SetCoreLdoLowPowerModeConfig(SPM_Type *base, uint32_t configMask)
{
    base->CORELPCNFG = configMask;
}

/*!
 * @brief Check if the CORE LDO is in run regulation.
 *
 * @param base SPM peripheral base address.
 * @retval true  Regulator is in run regulation.
 * @retval false Regulator is in stop regulation or in transition to/from it.
 */
static inline bool SPM_GetCoreLdoInRunRegulationFlag(SPM_Type *base)
{
    return (SPM_CORESC_REGONS_MASK == (SPM_CORESC_REGONS_MASK & base->CORESC));
}

/*!
 * @brief Force the Core LDO to an offset voltage level.
 *
 * @note Please make sure Core LDO Aux LDO and DCDC regulator both have been enabled before invoking
 *       this function.
 *
 * @param base SPM peripheral base address.
 * @param enable Enable/Disable Core Ldo voltage offset.
 *                  true    -   Apply Core LDO offset.
 *                  false   -   Don't apply Core LDO offset.
 */
static inline void SPM_ForceCoreLdoOffset(SPM_Type *base, bool enable)
{
    if (enable)
    {
        base->CORESC |= SPM_CORESC_VSEL_OFFSET_MASK;
    }
    else
    {
        base->CORESC &= ~SPM_CORESC_VSEL_OFFSET_MASK;
    }
}

/*!
 * @brief Gets the acknowledge Peripherals and I/O pads isolation flag.
 *
 * This function  reads the Acknowledge Isolation setting that indicates
 * whether certain peripherals and the I/O pads are in a latched state as
 * a result of having been in the VLLS mode.
 *
 * @param base SPM peripheral base address.
 * @return ACK isolation
 *               0 - Peripherals and I/O pads are in a normal run state.
 *               1 - Certain peripherals and I/O pads are in an isolated and
 *                   latched state.
 */
static inline bool SPM_GetPeriphIOIsolationFlag(SPM_Type *base)
{
    return (SPM_CORESC_ACKISO_MASK == (base->CORESC & SPM_CORESC_ACKISO_MASK));
}

/*!
 * @brief Acknowledges the isolation flag to Peripherals and I/O pads.
 *
 * This function  clears the ACK Isolation flag. Writing one to this setting
 * when it is set releases the I/O pads and certain peripherals to their normal
 * run mode state.
 *
 * @param base SPM peripheral base address.
 */
static inline void SPM_ClearPeriphIOIsolationFlag(SPM_Type *base)
{
    base->CORESC |= SPM_CORESC_ACKISO_MASK;
}

/*! @} */

/*! @name VDD Low voltage detection APIs*/
/*! @{ */

/*!
 * @brief Configures the low-voltage detect setting.
 *
 * This function configures the low-voltage detect setting, including the trip
 * point voltage setting, enables or disables the interrupt, enables or disables the system reset.
 *
 * @param base SPM peripheral base address.
 * @param config Pointer to low-voltage detect configuration structure, see to #spm_low_volt_detect_config_t.
 */
void SPM_SetLowVoltDetectConfig(SPM_Type *base, const spm_low_volt_detect_config_t *config);

/*!
 * @brief Gets VDD Low-voltage Detect Flag status.
 *
 * @param base SPM peripheral base address.
 * @return Current low-voltage detect flag
 *                - true: Low-voltage detected
 *                - false: Low-voltage not detected
 */
static inline bool SPM_GetVddLowVoltDetectFlag(SPM_Type *base)
{
    return (SPM_LVDSC1_VDD_LVDF_MASK == (base->LVDSC1 & SPM_LVDSC1_VDD_LVDF_MASK));
}

/*!
 * @brief Acknowledges clearing the Low-voltage Detect flag.
 *
 * This function acknowledges the low-voltage detection errors.
 *
 * @param base SPM peripheral base address.
 */
static inline void SPM_ClearVddLowVoltDetectFlag(SPM_Type *base)
{
    base->LVDSC1 |= SPM_LVDSC1_VDD_LVDACK_MASK; /* W1C. */
}

/*! @} */

/*! @name CORE LDO Low voltage detection APIs */
/*! @{ */

/*!
 * @brief Gets the COREVdds Low-voltage Detect Flag status.
 *
 * This function  reads the current LVDF status. If it returns 1, a low-voltage event is detected.
 *
 * @param base SPM peripheral base address.
 * @return Current low-voltage detect flag
 *                - true: Low-voltage detected
 *                - false: Low-voltage not detected
 */
static inline bool SPM_GetCoreLowVoltDetectFlag(SPM_Type *base)
{
    return (SPM_LVDSC1_COREVDD_LVDF_MASK == (base->LVDSC1 & SPM_LVDSC1_COREVDD_LVDF_MASK));
}

/*!
 * @brief Acknowledges clearing the CORE VDD Low-voltage Detect flag.
 *
 * This function acknowledges the CORE VDD low-voltage detection errors.
 *
 * @param base SPM peripheral base address.
 */
static inline void SPM_ClearCoreLowVoltDetectFlag(SPM_Type *base)
{
    base->LVDSC1 |= SPM_LVDSC1_COREVDD_LVDACK_MASK; /* W1C. */
}

/*!
 * @brief Configures the low-voltage warning setting.
 *
 * This function configures the low-voltage warning setting, including the trip
 * point voltage setting and enabling or disabling the interrupt.
 *
 * @param base SPM peripheral base address.
 * @param config Pointer to Low-voltage warning configuration structure, see to #spm_low_volt_warning_config_t.
 */
void SPM_SetLowVoltWarningConfig(SPM_Type *base, const spm_low_volt_warning_config_t *config);

/*!
 * @brief Gets Vdd Low-voltage Warning Flag status.
 *
 * This function polls the current LVWF status. When 1 is returned, it
 * indicates a low-voltage warning event. LVWF is set when V Supply transitions
 * below the trip point or after reset and V Supply is already below the V LVW.
 *
 * @param base SPM peripheral base address.
 * @return Current LVWF status
 *                  - true: Low-voltage Warning Flag is set.
 *                  - false: the  Low-voltage Warning does not happen.
 */
static inline bool SPM_GetVddLowVoltWarningFlag(SPM_Type *base)
{
    return (SPM_LVDSC2_VDD_LVWF_MASK == (base->LVDSC2 & SPM_LVDSC2_VDD_LVWF_MASK));
}

/*!
 * @brief Acknowledges the Low-voltage Warning flag.
 *
 * This function acknowledges the low voltage warning errors (write 1 to
 * clear LVWF).
 *
 * @param base SPM peripheral base address.
 */
static inline void SPM_ClearLowVoltWarningFlag(SPM_Type *base)
{
    base->LVDSC2 |= SPM_LVDSC2_VDD_LVWACK_MASK; /* W1C. */
}

/*! @} */

/*! @name VDD high voltage detection APIs. */
/*! @{ */

/*!
 * @brief Configures the high-voltage detect setting.
 *
 * This function configures the high-voltage detect setting, including the trip
 * point voltage setting, enabling or disabling the interrupt, enabling or disabling the system reset.
 *
 * @param base SPM peripheral base address.
 * @param config  High-voltage detect configuration structure, see to #spm_high_volt_detect_config_t.
 */
void SPM_SetHighVoltDetectConfig(SPM_Type *base, const spm_high_volt_detect_config_t *config);

/*!
 * @brief Gets the High-voltage Detect Flag status.
 *
 * This function  reads the current HVDF status. If it returns 1, a low
 * voltage event is detected.
 *
 * @param base SPM peripheral base address.
 * @return Current high-voltage detect flag
 *                - true: High-voltage detected
 *                - false: High-voltage not detected
 */
static inline bool SPM_GetHighVoltDetectFlag(SPM_Type *base)
{
    return (SPM_HVDSC1_VDD_HVDF_MASK == (base->HVDSC1 & SPM_HVDSC1_VDD_HVDF_MASK));
}

/*!
 * @brief Acknowledges clearing the High-voltage Detect flag.
 *
 * This function acknowledges the high-voltage detection errors (write 1 to
 * clear HVDF).
 *
 * @param base SPM peripheral base address.
 */
static inline void SPM_ClearHighVoltDetectFlag(SPM_Type *base)
{
    base->HVDSC1 |= SPM_HVDSC1_VDD_HVDACK_MASK; /* W1C. */
}

/*! @} */

/*! @name AUX LDO Low voltage detection APIs */
/*! @{ */

/*!
 * @brief Configures the AUX LDO.
 *
 * @param base SPM peripheral base address.
 * @param config Pointer to configuration structure, see to spm_rf_ldo_config_t.
 */
void SPM_SetAuxLdoConfig(SPM_Type *base, const spm_aux_ldo_config_t *config);

/*!
 * @brief Force auxiliary regulator voltage to an offset level.
 *
 * @note Please make sure DCDC has been enabled before involing this function.
 *
 * @param base SPM peripheral base address.
 * @param enable Enable/Disable AUX Ldo voltage offset.
 *                  true    -   Force auxiliary regulator voltage to an offset level.
 *                  false   -   Do not force auxiliary regulator voltage to an offset level.
 */
static inline void SPM_ForceAuxLdoOffset(SPM_Type *base, bool enable)
{
    if (enable)
    {
        base->AUXLDOSC |= SPM_AUXLDOSC_AUXREGVSEL_OFFSET_MASK;
    }
    else
    {
        base->AUXLDOSC &= ~SPM_AUXLDOSC_AUXREGVSEL_OFFSET_MASK;
    }
}

/*! @name DCDC Control APIs*/
/*! @{ */

/*!
 * @brief Sets DCDC battery monitor with its ADC value.
 *
 * For better accuracy, software would call this function to set the battery voltage value into DCDC
 * measured by ADC.
 *
 * @param base SPM peripheral base address.
 * @param batAdcVal ADC measured battery value with an 8mV LSB resolution.
 *              Value 0 would disable the battery monitor.
 */
void SPM_SetDcdcBattMonitor(SPM_Type *base, uint32_t batAdcVal);

/*!
 * @brief Sets DCDC VBAT voltage divider.
 *
 * The divided VBAT output is input to an ADC channel which allows the battery voltage to be measured.
 *
 * @param base SPM peripheral base address.
 * @param divider Setting divider, see to #spm_dcdc_vbat_adc_divider_t.
 */
static inline void SPM_SetDcdcVbatAdcMeasure(SPM_Type *base, spm_dcdc_vbat_adc_divider_t divider)
{
    base->DCDCSC = (base->DCDCSC & ~SPM_DCDCSC_DCDC_VBAT_DIV_CTRL_MASK) | SPM_DCDCSC_DCDC_VBAT_DIV_CTRL(divider);
}

/*!
 * @brief Power down output range comparator.
 *
 * @param base SPM peripheral base address.
 * @param enable Power down the CMP or not.
 */
static inline void SPM_EnablePowerDownCmpOffset(SPM_Type *base, bool enable)
{
    if (true == enable)
    {
        base->DCDCSC |= SPM_DCDCSC_PWD_CMP_OFFSET_MASK;
    }
    else
    {
        base->DCDCSC &= ~SPM_DCDCSC_PWD_CMP_OFFSET_MASK;
    }
}

/*!
 * @brief Get the status flags of DCDC module.
 *
 * @param base SPM peripheral base address.
 * @return Mask value of flags. See to #_spm_dcdc_flags.
 */
static inline uint32_t SPM_GetDcdcStatusFlags(SPM_Type *base)
{
    return (base->DCDCSC & (SPM_DCDCSC_DCDC_STS_DC_OK_MASK | SPM_DCDCSC_CLKFLT_FAULT_MASK));
}

/*!
 * @brief Set DCDC loop control config.
 *
 * @param base SPM peripheral base address.
 * @param config The Pointer to the structure @ref spm_dcdc_loop_control_config_t.
 */
void SPM_SetDcdcLoopControlConfig(SPM_Type *base, const spm_dcdc_loop_control_config_t *config);

/*!
 * @brief Disable stepping for VDD1P8 and VDD1P2.
 *
 * Must lock the step for VDD1P8 and VDD1P2 before enteing low power modes.
 *
 * @param base SPM peripheral base address.
 * @param enable Enable the lock or not to VDDx stepping.
 */
static inline void SPM_EnableVddxStepLock(SPM_Type *base, bool enable)
{
    if (true == enable)
    {
        base->DCDCC3 |= (SPM_DCDCC3_DCDC_VDD1P8CTRL_DISABLE_STEP_MASK | SPM_DCDCC3_DCDC_VDD1P2CTRL_DISABLE_STEP_MASK);
    }
    else
    {
        base->DCDCC3 &= ~(SPM_DCDCC3_DCDC_VDD1P8CTRL_DISABLE_STEP_MASK | SPM_DCDCC3_DCDC_VDD1P2CTRL_DISABLE_STEP_MASK);
    }
}

/*!
 * @brief Set the DCDC drive strength.
 *
 * Do set the DCDC drive strength according to actuall loading.
 * The related register bits are:
 * - DCDCC3[DCDC_MINPWR_HALF_FETS]
 * - DCDCC3[DCDC_MINPWR_DOUBLE_FETS]
 * - DCDCC3[DCDC_MINPWR_EXTRA_DOUBLE_FETS]
 * The more FETs are enabled, the more drive strength DCDC would provide.
 *
 * @param base SPM peripheral base address.
 * @param strength Selection of setting, see to #spm_dcdc_drive_strength_t
 */
static inline void SPM_SetDcdcDriveStrength(SPM_Type *base, spm_dcdc_drive_strength_t strength)
{
    base->DCDCC3 = (base->DCDCC3 & ~0xE000000U) | ((uint32_t)(strength) << 25);
}

/*!
 * @brief Split the frequency of DCDC's clock to min the power of DCDC.
 *
 * @note The function can only be invoked in continous mode.
 *
 * @param base SPM peripheral base address.
 * @param enable Split the DCDC clock frequency.
 *                  true    -   Set DCDC clock to half frequency for the continous mode.
 *                  false   -   Do not set DCDC clock to half frequency for the continous mode.
 */
static inline void SPM_SplitDcdcClockFreq(SPM_Type *base, bool enable)
{
    if (enable)
    {
        base->DCDCC3 |= SPM_DCDCC3_DCDC_MINPWR_DC_HALFCLK_MASK;
    }
    else
    {
        base->DCDCC3 &= ~SPM_DCDCC3_DCDC_MINPWR_DC_HALFCLK_MASK;
    }
}

/*!
 * @brief Bypasses the ADC measure value
 *
 * Forces DCDC to bypass the adc measuring state and loads the user-defined value in this function.
 *
 * @param base SPM peripheral base address.
 * @param enable Enable the bypass or not.
 * @param value User-setting value to be available instead of ADC measured value.
 */
void SPM_BypassDcdcBattMonitor(SPM_Type *base, bool enable, uint32_t value);

/*!
 * @brief Configure the DCDC integrator value.
 *
 * Integrator value can be loaded in pulsed mode. Software can program this value according to
 * battery voltage and VDDCORE output target value before goes to the pulsed mode.
 *
 * @code
    spm_dcdc_integrator_config_t SpmDcdcIntegratorConfigStruct =
    {
        .vddCoreValue = 1.25f,
        .vBatValue    = 3.34f
    };
 * @endcode
 *
 * @param base SPM peripheral base address.
 * @param config Pointer to configuration structure, see to #spm_dcdc_integrator_config_t.
 *               Passing NULL would clear all user-defined setting and use hardware default setting.
 */
void SPM_SetDcdcIntegratorConfig(SPM_Type *base, const spm_dcdc_integrator_config_t *config);

/*!
 * @brief Bypass the ADC measure or not.
 *
 * @note If forced to bypass the ADC measure, please invoke SPM_SetDcdcIntegratorConfig()
 *       function to select the integrator value.
 *
 * @param base SPM peripheral base address.
 * @param bypass Bypass or not bypass the ADC measure
 *          true    -   Force DCDC to bypass the ADC measuring state.
 *          false   -   Don't force DCDC to bypass the ADC measuring state.
 */
static inline void SPC_BypassDcdcAdcMeasure(SPM_Type *base, bool bypass)
{
    if (bypass)
    {
        base->DCDCC3 |= SPM_DCDCC3_DCDC_BYPASS_ADC_MEAS_MASK;
    }
    else
    {
        base->DCDCC3 &= ~SPM_DCDCC3_DCDC_BYPASS_ADC_MEAS_MASK;
    }
}

/*!
 * @brief Sets the target value of VDD1P2 in buck HSRUN mode.
 *
 * Sets target value of VDD1P2 in buck HSRUN mode. 25 mV each step from 0x00 to 0x0F. This value is
 * automatically selected on entry into HSRUN. On exit from HSRUN, DCDC VDD1P2 trim values will
 * default back to values set by DCDC_VDD1P2CTRL_TRG_BUCK register, which is operated with the API of
 * SPM_SetDcdcVdd1p2ValueBuck().
 *
 * @param base SPM peripheral base address.
 * @param trimCode Setting value of VDD1P2 in buck HSRUN mode. Please refer to the reference mannual for details.
 */
static inline void SPM_SetDcdcVdd1p2ValueHsrun(SPM_Type *base, uint32_t trimCode)
{
    base->DCDCC6 = (base->DCDCC6 & ~SPM_DCDCC6_DCDC_HSVDD_TRIM_MASK) | SPM_DCDCC6_DCDC_HSVDD_TRIM(trimCode);
}

/*!
 * @brief Sets the target value of VDD1P2 in buck mode.
 *
 * Sets the target value of VDD1P2 in buck mode, 25 mV each step from 0x00 to 0x0F.
 *
 * @param base SPM peripheral base address.
 * @param trimCode Setting value of VDD1P2 in buck mode. Please refer to the reference mannual for details.
 */
static inline void SPM_SetDcdcVdd1p2ValueBuck(SPM_Type *base, uint32_t trimCode)
{
    base->DCDCC6 =
        (base->DCDCC6 & ~SPM_DCDCC6_DCDC_VDD1P2CTRL_TRG_BUCK_MASK) | SPM_DCDCC6_DCDC_VDD1P2CTRL_TRG_BUCK(trimCode);
}

/*!
 * @brief Sets the target value of VDD1P8.
 *
 * Sets the target value of VDD1P8 in buck mode, 25 mV each step from 0x00 to 0x3F.
 *
 * @param base SPM peripheral base address.
 * @param trimCode Setting the trimCode of VDD1P8 output. Please refer to the reference mannual for details.
 */
static inline void SPM_SetDcdcVdd1p8Value(SPM_Type *base, uint32_t trimCode)
{
    base->DCDCC6 = (base->DCDCC6 & ~SPM_DCDCC6_DCDC_VDD1P8CTRL_TRG_MASK) | SPM_DCDCC6_DCDC_VDD1P8CTRL_TRG(trimCode);
}

/*! @} */

/*! @name Misc */
/*! @{ */

/*!
 * brief Configures the low power requeset output pin.
 *
 * param base SPM peripheral base address.
 * param config Pointer to the configuration structure, see to #spm_low_power_req_out_pin_config_t.
 */
static inline void SPM_SetLowPowerReqOutPinConfig(SPM_Type *base, const spm_low_power_req_out_pin_config_t *config)
{
    assert(NULL != config);

    if (true == config->pinOutEnable)
    {
        base->LPREQPINCNTRL =
            SPM_LPREQPINCNTRL_POLARITY(config->pinOutPol) | SPM_LPREQPINCNTRL_LPREQOE_MASK; /* Enable the output. */
    }
    else
    {
        base->LPREQPINCNTRL = 0U;
    }
}

/*! @} */

/*! @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* FSL_SPM_H_*/
