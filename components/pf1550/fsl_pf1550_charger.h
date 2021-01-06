/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_PF1550_CHARGER_H_
#define _FSL_PF1550_CHARGER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>

#include "fsl_pf1550.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief PF1550 Charger Interrupt Source definition. */
enum _pf1550_charger_interrupt_source
{
    kPF1550_IntSrcChargerSupMod     = 0x01U, /* Supplement mode interrupt source. */
    kPF1550_IntSrcChargerBatt2SysOc = 0x02U, /* VBATT to VSYS Overcurrent interrupt source. */
    kPF1550_IntSrcChargerBatt       = 0x04U, /* Battery interrupt source. */
    kPF1550_IntSrcChargerChg        = 0x08U, /* Charger interrupt source. */
    kPF1550_IntSrcChargerVbus       = 0x20U, /* VBUS interrupt source. */
    kPF1550_IntSrcChargerVbusDpm    = 0x40U, /* VBUS_DPM interrupt source. */
    kPF1550_IntSrcChargerThm        = 0x80U, /* THM interrupt source. */
};

/*! @brief PF1550 Charger Working Mode definition. */
enum _pf1550_charger_mode
{
    kPF1550_ChargerModePreChg       = 0x00000000U, /* Charger is in precharge mode. */
    kPF1550_ChargerModeFastChgCc    = 0x00000100U, /* Charger is in fast-charge constant current mode. */
    kPF1550_ChargerModeFastChgCv    = 0x00000200U, /* Charger is in fast-charge constant voltage mode. */
    kPF1550_ChargerModeEndOfChg     = 0x00000300U, /* Charger is in end-of-charge mode. */
    kPF1550_ChargerModeDone         = 0x00000400U, /* Charger is in done mode. */
    kPF1550_ChargerModeTimerFault   = 0x00000600U, /* Charger is in timer fault mode. */
    kPF1550_ChargerModeThermSuspend = 0x00000700U, /* Charger is in thermistor suspend mode. */
    kPF1550_ChargerModeOff          = 0x00000800U, /* Charger is off, input invalid and/or charger is disabled. */
    kPF1550_ChargerModeBatOv        = 0x00000900U, /* Battery over-voltage condition. */
    kPF1550_ChargerModeOffOt        = 0x00000A00U, /* Charger is off and the junction temperature is > TJSHDN. */
    kPF1550_ChargerModeOffLinearOn  = 0x00000C00U, /* Charger block is in Linear only mode, not charging. */
};

/*! @brief PF1550 Battery Working Mode definition. */
enum _pf1550_battery_mode
{
    kPF1550_BattModeNoValidVbus          = 0x00000000U, /* No valid VBUS input. */
    kPF1550_BattModeVbattLessThanVpre    = 0x00010000U, /* VBATT < VPRECHG.LB. */
    kPF1550_BattModeTimerFault           = 0x00020000U, /* Charger is in timer fault mode. */
    kPF1550_BattModeVbattGreaterThanVpre = 0x00040000U, /* VPRECHG.LB < VBATT. */
    kPF1550_BattModeOv =
        0x00050000U, /* the battery voltage is greater than the battery overvoltage flag threshold (VBATOV). */
    kPF1550_BattModeNoBatt = 0x00060000U, /* Battery not detected with a valid input and after VSYS wake-up. */
};

/*! @brief PF1550 Charger Status definition. */
enum _pf1550_charger_status
{
    kPF1550_ChargerStatusVbusUvlo   = 0x00000004U, /* VBUS_LIN < VBUS_LIN_UVLO or VBUS is detached. */
    kPF1550_ChargerStatusVbusIn2Sys = 0x00000008U, /* VBUS_LIN < VBATT + VIN2SYS. */
    kPF1550_ChargerStatusVbusOvlo   = 0x00000010U, /* VBUS_LIN > VBUS_LIN_OVLO. */
    kPF1550_ChargerStatusVbusValid =
        0x00000020U, /* VBUS_LIN > VBUS_LIN_UVLO, VBUS_LIN > VBAT + VIN2SYS and VBUS_LIN < VBUS_LIN_OVLO. */
    kPF1550_ChargerStatusVbusDpm     = 0x00000080U, /* VBUS_LIN DPM threshold has been triggered. */
    kPF1550_ChargerStatusChargerMode = 0x00000F00U, /* Charger working mode mask. */
    kPF1550_ChargerStatusWdogTimeout = 0x00002000U, /* Watch dog timer is expired. */
    kPF1550_ChargerStatusThm         = 0x00004000U, /* Thermistor temperature is < Cool, or > Warm threshold. */
    kPF1550_ChargerStatusTreg =
        0x00008000U, /* The junction temperature is greater than the threshold set by REGTEMP. */
    kPF1550_ChargerStatusBattMode = 0x00070000U, /* Battery working mode mask. */
    kPF1550_ChargerStatusBattOc   = 0x00200000U, /* VBATT to VSYS overcurrent fault. */
};

/*! @brief PF1550 Charger Operation definition. */
typedef enum _pf1550_charger_operation
{
    kPF1550_ChargerOperation_ChargerOffLinearOff = 0x0U, /* Charger = off, linear = off. The BATFET switch is on
                                                           to allow the battery to support the system. */
    kPF1550_ChargerOperation_ChargerOffLinearOn =
        0x1U,                                          /* Charger = off, linear = on, When there is a valid input,
                                                         the linear regulator regulates the system voltage to be VCHGCV. */
    kPF1550_ChargerOperation_ChargerOnLinearOn = 0x2U, /* Charger = on, linear = on. When there is a valid input,
                                                         the battery is charging. VSYS is the larger of VMINSYS
                                                         and ~ VBATT + IBAT * RBATFET. */
} pf1550_charger_operation_t;

/*! @brief PF1550 Thermaistor Configuration definition. */
typedef enum _pf1550_thermal_mode
{
    kPF1550_ThermalMode_0 = 0x0U, /* Thermistor not in control of charger. */
    kPF1550_ThermalMode_1 = 0x1U, /* Thermistor control in charger. */
    kPF1550_ThermalMode_2 = 0x2U, /* JEITA 1 settings: Change both current and voltage. */
    kPF1550_ThermalMode_3 = 0x3U, /* JEITA 2 settings; Change current only. */
} pf1550_thermal_mode_t;

/*! @brief PF1550 LED Indicator work mode definition. */
typedef enum _pf1550_led_mode
{
    kPF1550_LedMode_0 = 0x0U, /* LED on during charging; flashing during charger fault; off in DONE state. */
    kPF1550_LedMode_1 = 0x1U, /* LED flashing during charging; on during charger fault; off in DONE state. */
} pf1550_led_mode_t;

/*! @brief PF1550 Charger Attribute definition. */
typedef struct _pf1550_charger_attribute
{
    uint32_t fastChargeCurrent_mA;           /* Fast Charge Current in mA. */
    uint32_t fastChargeVoltage_uV;           /* Set Fast Charge Voltage in uV. */
    uint32_t preChargeTime_min;              /* Precharge Timer timeout value in minute. */
    uint32_t fastChargeTime_hr;              /* Fast-charge Timer timeout value in hour. */
    uint32_t endOfChargeTime_min;            /* End-of-charge timer timeout value in minute. */
    uint32_t endOfChargeCurrentThreshold_mA; /* End-of-charge current in mA. */
    uint32_t restartVoltageThreshold_uV;     /* Charger restart threshold in uV. */
    uint32_t miniSystemVoltage_uV;           /* Minimum system regulation voltage in uV. */
} pf1550_charger_attribute_t;

/*! @brief PF1550 BATT to VSYS FET Attribute definition. */
typedef struct _pf1550_batFET_attribute
{
    uint32_t overcurrentThreshold_mA;    /* VBATT to VSYS FET overcurrent Threshold in mA. */
    bool overcurrentProtectEnable;       /* BATFET battery overcurrent limit protection. */
    bool overcurrentProtectEnableNoVbus; /* BATFET battery overcurrent protection when no VBUS is present. */
    bool overvoltageFaultProtectEnable;  /* BATFET control during battery overvoltage. */
    bool watchDogFaultProtectEnable;     /* BATFET control during watchdog fault. */
    bool thermalFaultProtectEnable;      /* BATFET control during thermistor fault (< Cold or > Hot). */
    bool thermalShutdownProtectEnable;   /* BATFET control during thermal shutdown. */
    bool timerFaultProtectEnable;        /* BATFET control during charger timer fault. */
} pf1550_batFET_attribute_t;

/*! @brief PF1550 Power Path Attribute definition. */
typedef struct _pf1550_power_path_attribute
{
    uint32_t vbusCurrentLimit_mA;     /* Maximum Vbus input current limit in mA. */
    uint32_t vbusDpmVoltage_uV;       /* VBUS regulation voltage (DPM mode) in uV. */
    uint32_t vbusDpmStopThreshold_uV; /* Dynamic input power management panic stop threshold in uV. */
    uint32_t vbusOvDebounce_us;       /* VBUS overvoltage debounce delay in us. */
    uint32_t vbus2vsysDebounce_us;    /* VBUS to VSYS comparator debounce time in us. */
    uint32_t vbus2vsysThreashold_uV;  /* VBUS to VSYS comparator threshold setting in uV. */
    uint32_t usbPhyVoltage_uV;        /* USBPHY voltage in uV. */
    uint32_t vsysWakeupDelay_ms;      /* Vsys Wake-up delay in ms. */
    bool usbPhyDischargerEnbale;      /* Active discharger for USBPHY. */
    bool usbPhyLdoEnable;             /* USBPHY LDO enable. */
} pf1550_power_path_attribute_t;

/*! @brief PF1550 Thermal Attribute definition. */
typedef struct _pf1550_thermal_attribute
{
    pf1550_thermal_mode_t mode;        /* Thermistor Configuration. */
    int32_t junctionThermalSetPoint_C; /* Junction temperature thermal regulation loop set point in C. */
    int32_t thermalColdThreshold_C;    /* Thermistor cold temperature selection in C. */
    int32_t thermalCoolThreshold_C;    /* Thermistor cool threshold setting in C. */
    int32_t thermalWarmThreshold_C;    /* Thermistor warm threshold setting in C. */
    int32_t thermalHotThreshold_C;     /* Thermistor hot temperature selection in C. */
    uint32_t thermalVoltageAdjust_uV;  /* JEITA Thermistor battery termination voltage subtraction in uV. */
    uint32_t thermalCurrentAdjust_pct; /* JEITA Thermistor battery charging current setting (percentage of I_FC). */
    bool thermalFoldbackEnable;        /* Enable/disable thermal foldback current function. */
} pf1550_thermal_attribute_t;

/*! @brief PF1550 Charger LED Indicator Attribute definition. */
typedef struct _pf1550_led_attribute
{
    pf1550_led_mode_t mode;    /* Controls LED on/blinking mode. */
    uint32_t pwmDuty_pct;      /* LED PWM duty cycle setting in percentage. */
    uint32_t pwmFrequency_mHz; /* LED driver PWM frequency setting in mHz. */
    bool rampEnable;           /* Enable PWM ramp enable. */
    bool swCtrlEnable;         /* Enable software control of LED. */
} pf1550_led_attribute_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Charger control functions
 * @{
 */

void PF1550_SetChargerOperation(pf1550_handle_t *handle, pf1550_charger_operation_t operation);
void PF1550_SetChargerAttibute(pf1550_handle_t *handle, const pf1550_charger_attribute_t *attribute);
uint32_t PF1550_GetChargerStatus(pf1550_handle_t *handle);
void PF1550_SetChargerWdog(pf1550_handle_t *handle, uint32_t timeout_sec, bool enable);
void PF1550_ServiceChargerWdog(pf1550_handle_t *handle);
void PF1550_EnableBatFET(pf1550_handle_t *handle, bool enable);
void PF1550_SetBatFETAttibute(pf1550_handle_t *handle, const pf1550_batFET_attribute_t *attribute);
void PF1550_SetPowerPathAttibute(pf1550_handle_t *handle, const pf1550_power_path_attribute_t *attribute);
void PF1550_SetThermalAttibute(pf1550_handle_t *handle, const pf1550_thermal_attribute_t *attribute);
void PF1550_SetledOutput(pf1550_handle_t *handle, bool value);
void PF1550_SetLedAttibute(pf1550_handle_t *handle, const pf1550_led_attribute_t *attribute);

/* @} */

#if defined(__cplusplus)
}
#endif

#endif /* _FSL_PF1550_CHARGER_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
