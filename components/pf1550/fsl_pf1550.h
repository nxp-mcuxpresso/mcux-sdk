/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_PF1550_H_
#define _FSL_PF1550_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief PF1550 Default I2C address. */
#define PF1550_DEFAULT_I2C_ADDR 0x08U

/*! @brief Define the Register Memory Map of PF1550. */
/*! PMIC Register Memory Map. */
#define PF1550_DEVICE_ID         0x00U
#define PF1550_OTP_FLAVOR        0x01U
#define PF1550_SILICON_REV       0x02U
#define PF1550_INT_CATEGORY      0x06U
#define PF1550_SW_INT_STAT0      0x08U
#define PF1550_SW_INT_MASK0      0x09U
#define PF1550_SW_INT_SENSE0     0x0AU
#define PF1550_SW_INT_STAT1      0x0BU
#define PF1550_SW_INT_MASK1      0x0CU
#define PF1550_SW_INT_SENSE1     0x0DU
#define PF1550_SW_INT_STAT2      0x0EU
#define PF1550_SW_INT_MASK2      0x0FU
#define PF1550_SW_INT_SENSE2     0x10U
#define PF1550_LDO_INT_STAT0     0x18U
#define PF1550_LDO_INT_MASK0     0x19U
#define PF1550_LDO_INT_SENSE0    0x1AU
#define PF1550_TEMP_INT_STAT0    0x20U
#define PF1550_TEMP_INT_MASK0    0x21U
#define PF1550_TEMP_INT_SENSE0   0x22U
#define PF1550_ONKEY_INT_STAT0   0x24U
#define PF1550_ONKEY_INT_MASK0   0x25U
#define PF1550_ONKEY_INT_SENSE0  0x26U
#define PF1550_MISC_INT_STAT0    0x28U
#define PF1550_MISC_INT_MASK0    0x29U
#define PF1550_MISC_INT_SENSE0   0x2AU
#define PF1550_COINCELL_CONTROL  0x30U
#define PF1550_SW1_VOLT          0x32U
#define PF1550_SW1_STBY_VOLT     0x33U
#define PF1550_SW1_SLP_VOLT      0x34U
#define PF1550_SW1_CTRL          0x35U
#define PF1550_SW1_CTRL1         0x36U
#define PF1550_SW2_VOLT          0x38U
#define PF1550_SW2_STBY_VOLT     0x39U
#define PF1550_SW2_SLP_VOLT      0x3AU
#define PF1550_SW2_CTRL          0x3BU
#define PF1550_SW2_CTRL1         0x3CU
#define PF1550_SW3_VOLT          0x3EU
#define PF1550_SW3_STBY_VOLT     0x3FU
#define PF1550_SW3_SLP_VOLT      0x40U
#define PF1550_SW3_CTRL          0x41U
#define PF1550_SW3_CTRL1         0x42U
#define PF1550_VSNVS_CTRL        0x48U
#define PF1550_VREFDDR_CTRL      0x4AU
#define PF1550_LDO1_VOLT         0x4CU
#define PF1550_LDO1_CTRL         0x4DU
#define PF1550_LDO2_VOLT         0x4FU
#define PF1550_LDO2_CTRL         0x50U
#define PF1550_LDO3_VOLT         0x52U
#define PF1550_LDO3_CTRL         0x53U
#define PF1550_PWRCTRL0          0x58U
#define PF1550_PWRCTRL1          0x59U
#define PF1550_PWRCTRL2          0x5AU
#define PF1550_PWRCTRL3          0x5BU
#define PF1550_SW1_PWRDN_SEQ     0x5FU
#define PF1550_SW2_PWRDN_SEQ     0x60U
#define PF1550_SW3_PWRDN_SEQ     0x61U
#define PF1550_LDO1_PWRDN_SEQ    0x62U
#define PF1550_LDO2_PWRDN_SEQ    0x63U
#define PF1550_LDO3_PWRDN_SEQ    0x64U
#define PF1550_VREFDDR_PWRDN_SEQ 0x65U
#define PF1550_STATE_INFO        0x67U
#define PF1550_I2C_ADDR          0x68U
#define PF1550_IO_DRV0           0x69U
#define PF1550_IO_DRV1           0x6AU
#define PF1550_RC_16MHZ          0x6BU
#define PF1550_KEY1              0x6FU
/*! Charger Register Memory Map. */
#define PF1550_CHG_INT           0x80U
#define PF1550_CHG_INT_MASK      0x82U
#define PF1550_CHG_INT_OK        0x84U
#define PF1550_VBUS_SNS          0x86U
#define PF1550_CHG_SNS           0x87U
#define PF1550_BATT_SNS          0x88U
#define PF1550_CHG_OPER          0x89U
#define PF1550_CHG_TMR           0x8AU
#define PF1550_CHG_EOC_CNFG      0x8DU
#define PF1550_CHG_CURR_CNFG     0x8EU
#define PF1550_BATT_REG          0x8FU
#define PF1550_BATFET_CNFG       0x91U
#define PF1550_THM_REG_CNFG      0x92U
#define PF1550_VBUS_INLIM_CNFG   0x94U
#define PF1550_VBUS_LIN_DPM      0x95U
#define PF1550_USB_PHY_LDO_CNFG  0x96U
#define PF1550_DBNC_DELAY_TIME   0x98U
#define PF1550_CHG_INT_CNFG      0x99U
#define PF1550_THM_ADJ_SETTING   0x9AU
#define PF1550_VBUS2SYS_CNFG     0x9BU
#define PF1550_LED_PWM           0x9CU
#define PF1550_FAULT_BATFET_CNFG 0x9DU
#define PF1550_LED_CNFG          0x9EU
#define PF1550_CHGR_KEY2         0x9FU
/*! Test Register Memory Map. */
#define PF1550_KEY3    0xDFU
#define PF1550_FMRADDR 0xC4U
#define PF1550_FMRDATA 0xC5U
/*! OTP Register Memory Map. */
#define PF1550_OTP_SW1_SW2 0x1EU
#define PF1550_OTP_SW2_SW3 0x1FU

/*! @brief PF1550 Operating Status definition. */
typedef enum _pf1550_operating_status
{
    kPF1550_OperatingStatusCoreOff     = 0x1U, /* Indicates the state machine is in CoreOff Status. */
    kPF1550_OperatingStatusShipMode    = 0x2U, /* Indicates the state machine is in ShipMode Status. */
    kPF1550_OperatingStatusRegsDisable = 0x3U, /* Indicates the state machine is in RegsDisable Status. */
    kPF1550_OperatingStatusRun         = 0x4U, /* Indicates the state machine is in Run Status. */
    kPF1550_OperatingStatusStandby     = 0x5U, /* Indicates the state machine is in Standby Status. */
    kPF1550_OperatingStatusSleep       = 0x6U, /* Indicates the state machine is in Sleep Status. */
    kPF1550_OperatingStatusSystemOn    = 0x7U, /* Indicates the state machine is in any of the
                                                  SystemOn Status including Run, Standby, Sleep
                                                  and Low-Power. */
    kPF1550_OperatingStatusSystemOff = 0x8U,   /* Indicates the state machine is in any of the
                                                  SystemOff Status including RegsDisable, CoreOff
                                                  and ShipMode. */
} pf1550_operating_status_t;

/*! @brief PF1550 Sub-Module definition. */
typedef enum _pf1550_module
{
    kPF1550_ModuleSwitch1 = 0x0U, /* Switch1 Sub-Module Identifier. */
    kPF1550_ModuleSwitch2 = 0x1U, /* Switch2 Sub-Module Identifier. */
    kPF1550_ModuleSwitch3 = 0x2U, /* Switch3 Sub-Module Identifier. */
    kPF1550_ModuleLdo1    = 0x3U, /* LDO1 Sub-Module Identifier. */
    kPF1550_ModuleLdo2    = 0x4U, /* LDO2 Sub-Module Identifier. */
    kPF1550_ModuleLdo3    = 0x5U, /* LDO3 Sub-Module Identifier. */
    kPF1550_ModuleVsnvs   = 0x6U, /* VSNVS Sub-Module Identifier. */
    kPF1550_ModuleVrefDdr = 0x7U, /* Vref DDR Sub-Module Identifier. */
} pf1550_module_t;

/*! @brief PF1550 Interrupt Category definition. */
typedef enum _pf1550_interrupt_category
{
    kPF1550_IntCategoryCharger = 0x01U, /* Any of the Charger interrupt status bit is set. */
    kPF1550_IntCategorySwitch  = 0x0EU, /* Any of the Switch interrupt status bit is set. */
    kPF1550_IntCategoryLdo     = 0x10U, /* Any of the LDO interrupt status bit is set. */
    kPF1550_IntCategoryOnkey   = 0x20U, /* Any of the ONKEY interrupt status bit is set. */
    kPF1550_IntCategoryTemp    = 0x40U, /* Any of the PMIC junction temperature
                                           interrupt status bit is set. */
    kPF1550_IntCategoryMisc = 0x80U,    /* Any of the interrupts not covered by the above
                                           mentioned categories status bit is set. */
} pf1550_interrupt_category_t;

/*! @brief PF1550 Switch Interrupt Source definition. */
enum _pf1550_switch_interrupt_source
{
    kPF1550_IntSrcSw1LowSideCurrentLimit  = 0x1U,        /* Switch1 Low side current limit interrupt source. */
    kPF1550_IntSrcSw2LowSideCurrentLimit  = 0x2U,        /* Switch2 Low side current limit interrupt source. */
    kPF1550_IntSrcSw3LowSideCurrentLimit  = 0x4U,        /* Switch3 Low side current limit interrupt source. */
    kPF1550_IntSrcSw1HighSideCurrentLimit = 0x1U << 8U,  /* Switch1 High side current limit interrupt source. */
    kPF1550_IntSrcSw2HighSideCurrentLimit = 0x2U << 8U,  /* Switch2 High side current limit interrupt source. */
    kPF1550_IntSrcSw3HighSideCurrentLimit = 0x4U << 8U,  /* Switch3 High side current limit interrupt source. */
    kPF1550_IntSrcSw1DvsDone              = 0x1U << 16U, /* Switch1 DVS Complete interrupt source. */
    kPF1550_IntSrcSw2DvsDone              = 0x2U << 16U, /* Switch2 DVS Complete interrupt source. */
};

/*! @brief PF1550 LDO Interrupt Source definition. */
enum _pf1550_ldo_interrupt_source
{
    kPF1550_IntSrcLdo1CurrentLimit = 0x1U, /* LDO1 current limit interrupt source. */
    kPF1550_IntSrcLdo2CurrentLimit = 0x2U, /* LDO2 current limit interrupt source. */
    kPF1550_IntSrcLdo3CurrentLimit = 0x4U, /* LDO3 current limit interrupt source. */
};

/*! @brief PF1550 Die Temperature Interrupt Source definition. */
enum _pf1550_temp_interrupt_source
{
    kPF1550_IntSrcTemp_110C = 0x1U, /* Die temperature crosses 110C interrupt source. */
    kPF1550_IntSrcTemp_125C = 0x4U, /* Die temperature crosses 125C interrupt source. */
};

/*! @brief PF1550 ONKEY Interrupt Source definition. */
enum _pf1550_onkey_interrupt_source
{
    kPF1550_IntSrcOnkeyPush     = 0x01U, /* A push of the ONKEY button interrupt source. */
    kPF1550_IntSrcOnkeyPress_1s = 0x02U, /* After ONKEY pressed for >1s interrupt source. */
    kPF1550_IntSrcOnkeyPress_2s = 0x04U, /* After ONKEY pressed for >2s interrupt source. */
    kPF1550_IntSrcOnkeyPress_3s = 0x08U, /* After ONKEY pressed for >3s interrupt source. */
    kPF1550_IntSrcOnkeyPress_4s = 0x10U, /* After ONKEY pressed for >4s interrupt source. */
    kPF1550_IntSrcOnkeyPress_8s = 0x20U, /* After ONKEY pressed for >8s interrupt source. */
};

/*! @brief PF1550 Misc. Interrupt Source definition. */
enum _pf1550_misc_interrupt_source
{
    kPF1550_IntSrcMiscPowerUp = 0x01U,    /* Completion of transition from STANDBY to RUN
                                             and from SLEEP to RUN interrupt source. */
    kPF1550_IntSrcMiscPowerDown = 0x02U,  /* Completion of transition from RUN to STANDBY
                                             and from RUN to SLEEP interrupt source. */
    kPF1550_IntSrcMiscPowerOn = 0x04U,    /* Power on button event interrupt source
                                             (keep same function as PF3000/PF0100). */
    kPF1550_IntSrcMiscLowSysWarn = 0x08U, /* LOW_SYS_WARN threshold crossed interrupt source. */
    kPF1550_IntSrcMiscOverLoad   = 0x10U, /* SYS_OVLO threshold crossed interrupt source. */
};

/*! @brief PF1550 Undervoltage Detection Threshold definition. */
typedef enum _pf1550_undervoltage_detect_threshold
{
    kPF1550_UnderVoltDetThres_Rising2V65Falling2V55 =
        0x0U, /* Undervoltage Detection Threshold: Rising 2.65V; Falling 2.55V. */
    kPF1550_UnderVoltDetThres_Rising2V8Falling2V7 =
        0x1U, /* Undervoltage Detection Threshold: Rising 2.8V; Falling 2.7V. */
    kPF1550_UnderVoltDetThres_Rising3V0Falling2V9 =
        0x2U, /* Undervoltage Detection Threshold: Rising 3.0V; Falling 2.9V. */
    kPF1550_UnderVoltDetThres_Rising3V1Falling3V0 =
        0x3U, /* Undervoltage Detection Threshold: Rising 3.1V; Falling 3.0V. */
} pf1550_undervoltage_detect_threshold_t;

/*! @brief PF1550 Low Vsys Warning Threshold definition. */
typedef enum _pf1550_low_vsys_warning_threshold
{
    kPF1550_LowVsysWarnThres_Rising3V3Falling3V1 = 0x0U, /* Low Vsys Warning Threshold: Rising 3.3V; Falling 3.1V. */
    kPF1550_LowVsysWarnThres_Rising3V5Falling3V3 = 0x1U, /* Low Vsys Warning Threshold: Rising 3.5V; Falling 3.3V. */
    kPF1550_LowVsysWarnThres_Rising3V7Falling3V5 = 0x2U, /* Low Vsys Warning Threshold: Rising 3.7V; Falling 3.5V. */
    kPF1550_LowVsysWarnThres_Rising3V9Falling3V7 = 0x3U, /* Low Vsys Warning Threshold: Rising 3.9V; Falling 3.7V. */
} pf1550_low_vsys_warning_threshold_t;

/*! @brief PF1550 ONKEY Push Reset Time definition. */
typedef enum _pf1550_onkey_push_reset_time
{
    kPF1550_OnkeyPushResetTime_4s  = 0x0U, /* Push ONKEY 4s for a global reset. */
    kPF1550_OnkeyPushResetTime_8s  = 0x1U, /* Push ONKEY 8s for a global reset. */
    kPF1550_OnkeyPushResetTime_12s = 0x2U, /* Push ONKEY 12s for a global reset. */
    kPF1550_OnkeyPushResetTime_16s = 0x3U, /* Push ONKEY 16s for a global reset. */
} pf1550_onkey_push_reset_time_t;

/*! @brief PF1550 ONKEY Push Debounce Time definition. */
typedef enum _pf1550_onkey_debounce
{
    kPF1550_OnkeyDebounce_Falling31ms25Rising31ms25 =
        0x0U, /* ONKEY Push Debounce: 31.25ms falling edge; 31.25ms rising edge. */
    kPF1550_OnkeyDebounce_Falling125msRising31ms25 =
        0x2U, /* ONKEY Push Debounce: 125ms falling edge; 31.25ms rising edge. */
    kPF1550_OnkeyDebounce_Falling750msRising31ms25 =
        0x3U, /* ONKEY Push Debounce: 750ms falling edge; 31.25ms rising edge. */
} pf1550_onkey_debounce_t;

/*! @brief PF1550 Standby Delay Time definition. */
typedef enum _pf1550_standby_delay
{
    kPF1550_StandbyDelay_None         = 0x0U, /* No additional delay. */
    kPF1550_StandbyDelay_1x32kHzCycle = 0x1U, /* 1 x 32kHz cycle additional delay. */
    kPF1550_StandbyDelay_2x32kHzCycle = 0x2U, /* 2 x 32kHz cycle additional delay. */
    kPF1550_StandbyDelay_3x32kHzCycle = 0x3U, /* 3 x 32kHz cycle additional delay. */
} pf1550_standby_delay_t;

/*! @brief PF1550 Standby Pad Active Polarity definition. */
typedef enum _pf1550_standby_polarity
{
    kPF1550_StandbyPolActiveHigh = 0x0U, /* Standby pin input active high. */
    kPF1550_StandbyPolActiveLow  = 0x1U, /* Standby pin input active low. */
} pf1550_standby_polarity_t;

/*! @brief PF1550 Power Up Delay Time definition. */
typedef enum _pf1550_power_up_delay
{
    kPF1550_PowerUpDelay_2ms    = 0x0U, /* RESETBMCU goes high 2ms after last regulator. */
    kPF1550_PowerUpDelay_4ms    = 0x2U, /* RESETBMCU goes high 4ms after last regulator. */
    kPF1550_PowerUpDelay_8ms    = 0x3U, /* RESETBMCU goes high 8ms after last regulator. */
    kPF1550_PowerUpDelay_16ms   = 0x4U, /* RESETBMCU goes high 16ms after last regulator. */
    kPF1550_PowerUpDelay_128ms  = 0x5U, /* RESETBMCU goes high 128ms after last regulator. */
    kPF1550_PowerUpDelay_256ms  = 0x6U, /* RESETBMCU goes high 256ms after last regulator. */
    kPF1550_PowerUpDelay_1024ms = 0x7U, /* RESETBMCU goes high 1024ms after last regulator. */
} pf1550_power_up_delay_t;

/*! @brief PF1550 Power On Pad Debounce Time definition. */
typedef enum _pf1550_power_on_debounce
{
    kPF1550_PowerOnDebounce_Fall31ms25Rise31ms25 =
        0x0U, /* Power On Pad Debounce: 31.25ms falling edge; 31.25ms rising edge. */
    kPF1550_PowerOnDebounce_Fall125msRise31ms25 =
        0x2U, /* Power On Pad Debounce: 125ms falling edge; 31.25ms rising edge. */
    kPF1550_PowerOnDebounce_Fall750msRise31ms25 =
        0x3U, /* Power On Pad Debounce: 750ms falling edge; 31.25ms rising edge. */
} pf1550_power_on_debounce_t;

/*! @brief PF1550 Regulator Power Down Sequence Attribute definition. */
typedef enum _pf1550_regulator_power_down_sequence
{
    kPF1550_RegulatorPowerDownSeqOpt0 = 0x0U, /* Regulator Power Down Sequence Attribute: Option 0. */
    kPF1550_RegulatorPowerDownSeqOpt1 = 0x1U, /* Regulator Power Down Sequence Attribute: Option 1. */
    kPF1550_RegulatorPowerDownSeqOpt2 = 0x2U, /* Regulator Power Down Sequence Attribute: Option 2. */
    kPF1550_RegulatorPowerDownSeqOpt3 = 0x3U, /* Regulator Power Down Sequence Attribute: Option 3. */
    kPF1550_RegulatorPowerDownSeqOpt4 = 0x4U, /* Regulator Power Down Sequence Attribute: Option 4. */
    kPF1550_RegulatorPowerDownSeqOpt5 = 0x5U, /* Regulator Power Down Sequence Attribute: Option 5. */
    kPF1550_RegulatorPowerDownSeqOpt6 = 0x6U, /* Regulator Power Down Sequence Attribute: Option 6. */
    kPF1550_RegulatorPowerDownSeqOpt7 = 0x7U, /* Regulator Power Down Sequence Attribute: Option 7. */
} pf1550_regulator_power_down_sequence_t;

/*! @brief PF1550 Switch DVS Speed Attribute definition. */
typedef enum _pf1550_switch_dvs_speed
{
    kPF1550_SwitchDvsSpeed_12mV5Per2us = 0x0U, /* Switch DVS rate at 12.5mV/2us. */
    kPF1550_SwitchDvsSpeed_12mV5Per4us = 0x1U, /* Switch DVS rate at 12.5mV/4us. */
} pf1550_switch_dvs_speed_t;

/*! @brief PF1550 Switch Current Limit Attribute definition. */
typedef enum _pf1550_switch_current_limit
{
    kPF1550_SwitchCurrentLimit_1A  = 0x0U, /* Switch Current Limit: Typical current limit of 1.0A. */
    kPF1550_SwitchCurrentLimit_1A5 = 0x1U, /* Switch Current Limit: Typical current limit of 1.5A. */
    kPF1550_SwitchCurrentLimit_2A  = 0x2U, /* Switch Current Limit: Typical current limit of 2.0A. */
} pf1550_switch_current_limit_t;

/*! @brief PF1550 Vsnvs Coin Cell Charging Voltage Attribute definition. */
typedef enum _pf1550_coin_cell_charging_voltage
{
    kPF1550_CoinCellChargingVoltage_1V8 = 0x0U, /* Coin cell charger charging voltage 1.8V. */
    kPF1550_CoinCellChargingVoltage_1V9 = 0x1U, /* Coin cell charger charging voltage 1.9V. */
    kPF1550_CoinCellChargingVoltage_2V  = 0x2U, /* Coin cell charger charging voltage 2.0V. */
    kPF1550_CoinCellChargingVoltage_2V1 = 0x3U, /* Coin cell charger charging voltage 2.1V. */
    kPF1550_CoinCellChargingVoltage_2V2 = 0x4U, /* Coin cell charger charging voltage 2.2V. */
    kPF1550_CoinCellChargingVoltage_2V3 = 0x5U, /* Coin cell charger charging voltage 2.3V. */
    kPF1550_CoinCellChargingVoltage_2V4 = 0x6U, /* Coin cell charger charging voltage 2.4V. */
    kPF1550_CoinCellChargingVoltage_2V5 = 0x7U, /* Coin cell charger charging voltage 2.5V. */
    kPF1550_CoinCellChargingVoltage_2V6 = 0x8U, /* Coin cell charger charging voltage 2.6V. */
    kPF1550_CoinCellChargingVoltage_2V7 = 0x9U, /* Coin cell charger charging voltage 2.7V. */
    kPF1550_CoinCellChargingVoltage_2V8 = 0xAU, /* Coin cell charger charging voltage 2.8V. */
    kPF1550_CoinCellChargingVoltage_2V9 = 0xBU, /* Coin cell charger charging voltage 2.9V. */
    kPF1550_CoinCellChargingVoltage_3V  = 0xCU, /* Coin cell charger charging voltage 3.0V. */
    kPF1550_CoinCellChargingVoltage_3V1 = 0xDU, /* Coin cell charger charging voltage 3.1V. */
    kPF1550_CoinCellChargingVoltage_3V2 = 0xEU, /* Coin cell charger charging voltage 3.2V. */
    kPF1550_CoinCellChargingVoltage_3V3 = 0xFU, /* Coin cell charger charging voltage 3.3V. */
} pf1550_coin_cell_charging_voltage_t;

/*! @brief PF1550 Switch Attribute Structure definition. */
typedef struct _pf1550_switch_attribute
{
    pf1550_switch_dvs_speed_t dvsSpeed;                       /* Switch DVS Speed Selection. */
    pf1550_switch_current_limit_t currentLimit;               /* Switch Current Limit Selection. */
    pf1550_regulator_power_down_sequence_t powerDownSequence; /* The power down sequencer performs the functional
                                                                 opposite to the power up sequencer. */
    bool enableLowPowerMode;      /* Lets the buck enter low power mode during Standby and Sleep. */
    bool enableForcedPwm;         /* Forced in PWM mode irrespective of load current. */
    bool enableForcedPwmInDvs;    /* Forces to track the DVS reference while it is falling. */
    bool enableDischargeResistor; /* Enables discharge resistor on output when regulator disabled. */
} pf1550_switch_attribute_t;

/*! @brief PF1550 LDO Attribute Structure definition. */
typedef struct _pf1550_ldo_attribute
{
    pf1550_regulator_power_down_sequence_t powerDownSequence; /* The power down sequencer performs the functional
                                                                 opposite to the power up sequencer. */
    bool enableLowPowerMode; /* Lets LDO enter low power mode during Standby and Sleep. */
    bool enableLoadSwitch;   /* Set LDO to a load switch (fully on) mode.
                                Changing from true to false is not allowed. */
} pf1550_ldo_attribute_t;

/*! @brief PF1550 Vrefddr Attribute Structure definition. */
typedef struct _pf1550_vrefddr_attribute
{
    pf1550_regulator_power_down_sequence_t powerDownSequence; /* The power down sequencer performs the functional
                                                                 opposite to the power up sequencer. */
} pf1550_vrefddr_attribute_t;

/*! @brief PF1550 Vsnvs Attribute Structure definition. */
typedef struct _pf1550_vsnvs_attribute
{
    pf1550_coin_cell_charging_voltage_t coinCellChargingVoltage; /* Vsnvs Coin Cell Charging Voltage Selection. */
    bool enableLocalBandgapInCoinCellMode;                       /* Enable bandgap in coin cell mode. */
    bool enableCoinCellCharger;                                  /* Enable Coin Cell Charger. */
} pf1550_vsnvs_attribute_t;

/*! @brief PF1550 ONKEY Pad Attribute Structure definition. */
typedef struct _pf1550_onkey_attribute
{
    pf1550_onkey_debounce_t debounce;        /* ONKEY Push Debounce Time Selection. */
    pf1550_onkey_push_reset_time_t pushTime; /* ONKEY Push Reset Time Selection. */
    bool enableTurnOffSystemViaOnkey;        /* Enables turning off of system via ONKEY. */
} pf1550_onkey_attribute_t;

/*! @brief PF1550 PWRON Pad Attribute Structure definition. */
typedef struct _pf1550_power_on_attribute
{
    pf1550_power_on_debounce_t debounce;  /* Power On Pad Debounce Time Selection. */
    bool longPressGoToRegsDisableOrSleep; /* Enables going to REGS_DISABLE or Sleep mode when
                                             PWRON_CFG = 1. Refer to state machine for details. */
    bool longPressRestartToRunStauts;     /* Enables restart of system when PWRON push button is
                                             held low for 5 seconds. */
} pf1550_power_on_attribute_t;

/*! @brief PF1550 STANDBY Pad Attribute Structure definition. */
typedef struct _pf1550_standby_attribute
{
    pf1550_standby_delay_t standbyDelay;       /* Select delay of Standby pin (after synchronization). */
    pf1550_standby_polarity_t standbyPolarity; /* Standby Pad Active Polarity Selection. */
} pf1550_standby_attribute_t;

/*! @brief PF1550 Handle definition. */
typedef struct _pf1550_handle
{
    /* Pointer to the user-defined I2C Send Data function. */
    status_t (*I2C_SendFunc)(
        uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
    /* Pointer to the user-defined I2C Receive Data function. */
    status_t (*I2C_ReceiveFunc)(
        uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);
    /* The I2C Slave Address Read From OTP. */
    uint8_t slaveAddress;
} pf1550_handle_t;

/*! @brief PF1550 Configuration Structure definition. */
typedef struct _pf1550_config
{
    /* Pointer to the user-defined I2C Send Data function. */
    status_t (*I2C_SendFunc)(
        uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
    /* Pointer to the user-defined I2C Receive Data function. */
    status_t (*I2C_ReceiveFunc)(
        uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);
    /* Undervoltage Detection Threshold Selection. */
    pf1550_undervoltage_detect_threshold_t threshold;
    /* Power Up Delay Time Selection. */
    pf1550_power_up_delay_t delay;
    /* Shuts down LDO if it enters a current limit fault. Controls LDO1, LDO2 and LDO3. */
    bool shutDownLdoInCurrentFault;
    /* The PF1550 I2C Slave Address. */
    uint8_t slaveAddress;
} pf1550_config_t;

/*!
 * @addtogroup pf1550
 * @{
 */

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization function
 * @{
 */

/*!
 * @brief Gets the default configuration structure.
 *
 * This function initializes the PF1550 configuration structure to default values. The default
 * values are as follows.
 *   pf1550Config->I2C_SendFunc              = NULL;
 *   pf1550Config->I2C_ReceiveFunc           = NULL;
 *   pf1550Config->threshold                 = kPF1550_UnderVoltDetThres_Rising3V0Falling2V9;
 *   pf1550Config->delay                     = kPF1550_PowerUpDelay_2ms;
 *   pf1550Config->shutDownLdoInCurrentFault = false;
 *   pf1550Config->slaveAddress              = PF1550_DEFAULT_I2C_ADDR;
 *
 * @param config Pointer to the PF1550 configuration structure.
 */
void PF1550_GetDefaultConfig(pf1550_config_t *config);

/*!
 * @brief Initializes a PF1550 instance.
 *
 * This function initializes the PF1550 module with user-defined settings.
 * This example shows how to set up the pf1550_config_t parameters and how
 * to call the PF1550_Init function by passing in these parameters.
 * @code
 *   pf1550_config_t pf1550Config;
 *   pf1550Config.I2C_SendFunc              = APP_I2C_SendFunc;
 *   pf1550Config.I2C_ReceiveFunc           = APP_I2C_ReceiveFunc;
 *   pf1550Config.threshold                 = kPF1550_UnderVoltDetThres_Rising3V1Falling3V0;
 *   pf1550Config.delay                     = kPF1550_PowerUpDelay_1024ms;
 *   pf1550Config.shutDownLdoInCurrentFault = true;
 *   pf1550Config.slaveAddress              = PF1550_DEFAULT_I2C_ADDR;
 *   PF1550_Init(&pf1550Handle, &pf1550Config);
 * @endcode
 *
 * @param handle PF1550 Handle.
 * @param config Pointer to the user-defined configuration structure.
 */
void PF1550_Init(pf1550_handle_t *handle, const pf1550_config_t *config);
/* @} */

/*!
 * @name Basic register access functions
 * @{
 */

/*!
 * @brief Write the value to register of PF1550.
 *
 * @param handle Pointer to a valid PF1550 instance structure.
 * @param reg variable store address of register.
 * @param val variable store value which is written to PF1550.
 * @return true if success or false if error.
 */
bool PF1550_WriteReg(pf1550_handle_t *handle, uint8_t reg, uint8_t val);

/*!
 * @brief Read the value of register in PF1550.
 *
 * @param handle Pointer to a valid PF1550 instance structure.
 * @param reg variable store address of register.
 * @param val pointer store return value.
 * @return true if success or false if error.
 */
bool PF1550_ReadReg(pf1550_handle_t *handle, uint8_t reg, uint8_t *val);

/*!
 * @brief Modify some bits in the register in PF1550.
 * @param handle Pointer to a valid PF1550 instance structure.
 * @param reg variable store address of register.
 * @param mask The mask code for the bits want to write. The bit you want to write should be 1.
 * @param val Value needs to write into the register.
 * @return true if success or false if error.
 */
bool PF1550_ModifyReg(pf1550_handle_t *handle, uint8_t reg, uint8_t mask, uint8_t val);

/*!
 * @brief Dump the register content in PF1550.
 * @param handle Pointer to a valid PF1550 instance structure.
 * @param reg The address of the first register to dump.
 * @param buffer The buffer to store the dumped content.
 * @param size The count of registers to dump.
 * @return true if success or false if error.
 */
bool PF1550_DumpReg(pf1550_handle_t *handle, uint8_t reg, uint8_t *buffer, uint8_t size);

/* @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enables PF1550 interrupts according to the provided interrupt source mask.
 *
 * This function enables the PF1550 interrupts according to the provided interrupt category
 * and interrupt source.
 * The interrupt source category enumerate the available interrupt groups in category.
 * The interrupt source mask is a logical OR of enumeration members:
 * see @ref _pf1550_switch_interrupt_source for Switch interrupt sources;
 *     @ref _pf1550_ldo_interrupt_source for LDO interrupt sources;
 *     @ref _pf1550_temp_interrupt_source for Die Temperature interrupt sources;
 *     @ref _pf1550_onkey_interrupt_source for ONKEY interrupt sources;
 *     @ref _pf1550_misc_interrupt_source for Misc. interrupt sources.
 *
 * @param handle Pointer to a valid PF1550 instance structure.
 * @param category The interrupt category to set.
 * @param source Logic ORed interrupt sources of selected interrupt category to enable.
 */
void PF1550_EnableInterrupts(pf1550_handle_t *handle, pf1550_interrupt_category_t category, uint32_t source);

/*!
 * @brief Disable PF1550 interrupts according to the provided interrupt source mask.
 *
 * This function disables the PF1550 interrupts according to the provided interrupt category
 * and interrupt source.
 * The interrupt source category enumerate the available interrupt groups in category.
 * The interrupt source mask is a logical OR of enumeration members:
 * see @ref _pf1550_switch_interrupt_source for Switch interrupt sources;
 *     @ref _pf1550_ldo_interrupt_source for LDO interrupt sources;
 *     @ref _pf1550_temp_interrupt_source for Die Temperature interrupt sources;
 *     @ref _pf1550_onkey_interrupt_source for ONKEY interrupt sources;
 *     @ref _pf1550_misc_interrupt_source for Misc. interrupt sources.
 *
 * @param handle Pointer to a valid PF1550 instance structure.
 * @param category The interrupt category to set.
 * @param source Logic ORed interrupt sources of selected interrupt category to disable.
 */
void PF1550_DisableInterrupts(pf1550_handle_t *handle, pf1550_interrupt_category_t category, uint32_t source);

/*!
 * @brief Get Interrupt Category of PF1550.
 * This function is used to get the ORed Interrupt Category
 * that is asserted by hardware. Users can AND the return value with
 * Interrupt Category defined in @ pf1550_interrupt_category_t to check
 * which kinds of interrupt event is happened, after that user can get/clear
 * the interrupt status bits for the specified interrupt category, other than
 * check all the interrupt status.
 *
 * @param handle Pointer to a valid PF1550 instance structure.
 * @return ORed Interrupt Category combination.
 */
uint32_t PF1550_GetInterruptCategory(pf1550_handle_t *handle);

/*!
 * @brief Get interrupt flags of selected interrupt category.
 *
 * This function gets all interrupt flags of selected interrupt category.
 * The flags are returned as the logical OR value of the corresponding interrupt source:
 * see @ref _pf1550_switch_interrupt_source for Switch interrupt sources;
 *     @ref _pf1550_ldo_interrupt_source for LDO interrupt sources;
 *     @ref _pf1550_temp_interrupt_source for Die Temperature interrupt sources;
 *     @ref _pf1550_onkey_interrupt_source for ONKEY interrupt sources;
 *     @ref _pf1550_misc_interrupt_source for Misc. interrupt sources.
 *
 * @param handle Pointer to a valid PF1550 instance structure.
 * @param category The interrupt category that to query.
 * @return status flags which are ORed by the enumerators in the corresponding interrupt source.
 */
uint32_t PF1550_GetInterruptStatus(pf1550_handle_t *handle, pf1550_interrupt_category_t category);

/*!
 * @brief Clear interrupt flags of selected interrupt category.
 *
 * This function clears all interrupt flags of selected interrupt category.
 * The interrupt source category enumerate the available interrupt groups in category.
 * The interrupt source mask is a logical OR of enumeration members:
 * see @ref _pf1550_switch_interrupt_source for Switch interrupt sources;
 *     @ref _pf1550_ldo_interrupt_source for LDO interrupt sources;
 *     @ref _pf1550_temp_interrupt_source for Die Temperature interrupt sources;
 *     @ref _pf1550_onkey_interrupt_source for ONKEY interrupt sources;
 *     @ref _pf1550_misc_interrupt_source for Misc. interrupt sources.
 *
 * @param handle Pointer to a valid PF1550 instance structure.
 * @param category The interrupt category that set.
 * @param source Logic ORed interrupt sources of selected interrupt category to clear.
 */
void PF1550_ClearInterruptStatus(pf1550_handle_t *handle, pf1550_interrupt_category_t category, uint32_t source);
/* @} */

/*!
 * @name Regulator control functions
 * @{
 */

/*!
 * @brief Enable/Disable the output of selected regulator.
 *
 * This function is used to enable/disable the output of selected regulator
 * enumerated in @ref pf1550_module_t under selected operating status
 * enumerated in @ref pf1550_operating_status_t. The output state of
 * the regulators will change automatically once the operating status
 * changed.
 *
 * @param handle Pointer to a valid PF1550 instance structure.
 * @param module Sub-modules in PF1550 device.
 * @param status The operating status of PF1550 to set.
 * @param enable Set true to enable regulator, set false to disable regulator.
 */
void PF1550_EnableRegulator(pf1550_handle_t *handle,
                            pf1550_module_t module,
                            pf1550_operating_status_t status,
                            bool enable);

/*!
 * @brief Query the output state of selected regulator.
 *
 * This function is used to query the output state of selected regulator
 * enumerated in @ref pf1550_module_t under selected operating status
 * enumerated in @ref pf1550_operating_status_t. The output state of
 * the regulators will change automatically once the operating status
 * changed.
 *
 * @param handle Pointer to a valid PF1550 instance structure.
 * @param module Sub-modules in PF1550 device.
 * @param status The operating status of PF1550 to set.
 * @return true if regulator is enabled, false if regulator is disabled.
 */
bool PF1550_IsRegulatorEnabled(pf1550_handle_t *handle, pf1550_module_t module, pf1550_operating_status_t status);

/*!
 * @brief Set the output voltage of selected regulator.
 *
 * This function is used to set the output voltage of selected regulator
 * enumerated in @ref pf1550_module_t under selected operating status
 * enumerated in @ref pf1550_operating_status_t. The output state of
 * the regulators will change automatically once the operating status
 * changed. All the available output voltages are listed in
 * @ref pf1550_regulator_output_voltage_t.
 *
 * @param handle Pointer to a valid PF1550 instance structure.
 * @param module Sub-modules in PF1550 device.
 * @param status The operating status of PF1550 to set.
 * @param voltage The output voltage in uV to set.
 */
void PF1550_SetRegulatorOutputVoltage(pf1550_handle_t *handle,
                                      pf1550_module_t module,
                                      pf1550_operating_status_t status,
                                      uint32_t voltage);

/*!
 * @brief Query the output voltage of selected regulator.
 *
 * This function is used to query the output voltage of selected regulator
 * enumerated in @ref pf1550_module_t under selected operating status
 * enumerated in @ref pf1550_operating_status_t. The output state of
 * the regulators will change automatically once the operating status
 * changed. All the available output voltages are listed in
 * @ref pf1550_regulator_output_voltage_t.
 *
 * @param handle Pointer to a valid PF1550 instance structure.
 * @param module Sub-modules in PF1550 device.
 * @param status The operating status of PF1550 to set.
 * @return voltage The output voltage in uV of selected regulator.
 */
uint32_t PF1550_GetRegulatorOutputVoltage(pf1550_handle_t *handle,
                                          pf1550_module_t module,
                                          pf1550_operating_status_t status);

/*!
 * @brief Set the attributes of selected Buck Switch.
 *
 * This function is used to set the attributes of Buck Switch regulator.
 * All the available attributes for Switch are listed in
 * @ref pf1550_switch_attribute_t.
 *
 * @param handle Pointer to a valid PF1550 instance structure.
 * @param module Sub-modules in PF1550 device.
 * @param attribute Pointer to the Switch Attribute structure to set.
 */
void PF1550_SetSwitchAttribute(pf1550_handle_t *handle,
                               pf1550_module_t module,
                               const pf1550_switch_attribute_t *attribute);

/*!
 * @brief Set the attributes of selected LDO.
 *
 * This function is used to set the attributes of LDO regulator.
 * All the available attributes for Switch are listed in
 * @ref pf1550_ldo_attribute_t.
 *
 * @param handle Pointer to a valid PF1550 instance structure.
 * @param module Sub-modules in PF1550 device.
 * @param attribute Pointer to the LDO Attribute structure to set.
 */
void PF1550_SetLdoAttribute(pf1550_handle_t *handle, pf1550_module_t module, const pf1550_ldo_attribute_t *attribute);

/*!
 * @brief Set the attributes of Vref DDR.
 *
 * This function is used to set the attributes of Vref DDR regulator.
 * All the available attributes for Vref DDR are listed in
 * @ref pf1550_vrefddr_attribute_t.
 *
 * @param handle Pointer to a valid PF1550 instance structure.
 * @param module Sub-modules in PF1550 device.
 * @param attribute Pointer to the Vref DDR Attribute structure to set.
 */
void PF1550_SetVrefDdrAttribute(pf1550_handle_t *handle, const pf1550_vrefddr_attribute_t *attribute);

/*!
 * @brief Set the attributes of Vsnvs.
 *
 * This function is used to set the attributes of Vsnvs regulator.
 * All the available attributes for Vsnvs are listed in
 * @ref pf1550_vsnvs_attribute_t.
 *
 * @param handle Pointer to a valid PF1550 instance structure.
 * @param module Sub-modules in PF1550 device.
 * @param attribute Pointer to the Vsnvs Attribute structure to set.
 */
void PF1550_SetVsnvsAttribute(pf1550_handle_t *handle, const pf1550_vsnvs_attribute_t *attribute);
/* @} */

/*!
 * @name I/O Pad control functions
 * @{
 */

/*!
 * @brief Set the attributes of ONKEY Pad.
 *
 * This function is used to set the attributes of ONKEY Pad.
 * All the available attributes for ONKEY Pad are listed in
 * @ref pf1550_onkey_attribute_t.
 *
 * @param handle Pointer to a valid PF1550 instance structure.
 * @param module Sub-modules in PF1550 device.
 * @param attribute Pointer to the ONKEY Pad Attribute structure to set.
 */
void PF1550_SetOnKeyPadAttibute(pf1550_handle_t *handle, const pf1550_onkey_attribute_t *attribute);

/*!
 * @brief Set the attributes of PowerOn Pad.
 *
 * This function is used to set the attributes of PowerOn Pad.
 * All the available attributes for PowerOn Pad are listed in
 * @ref pf1550_power_on_attribute_t.
 *
 * @param handle Pointer to a valid PF1550 instance structure.
 * @param module Sub-modules in PF1550 device.
 * @param attribute Pointer to the PowerOn Pad Attribute structure to set.
 */
void PF1550_SetPwrOnPadAttibute(pf1550_handle_t *handle, const pf1550_power_on_attribute_t *attribute);

/*!
 * @brief Set the attributes of Standby Pad.
 *
 * This function is used to set the attributes of Standby Pad.
 * All the available attributes for Standby Pad are listed in
 * @ref pf1550_standby_attribute_t.
 *
 * @param handle Pointer to a valid PF1550 instance structure.
 * @param module Sub-modules in PF1550 device.
 * @param attribute Pointer to the Standby Pad Attribute structure to set.
 */
void PF1550_SetStandbyPadAttibute(pf1550_handle_t *handle, const pf1550_standby_attribute_t *attribute);
/* @} */

/*!
 * @name Misc. functions
 * @{
 */

/*!
 * @brief Query Current Operating Status of PF1550.
 *
 * This function is used to query the current operating status of PF1550.
 * All the available operating status for PF1550 are listed in
 * @ref pf1550_operating_status_t.
 *
 * @param handle Pointer to a valid PF1550 instance structure.
 * @return Current PF1550 operating status.
 */
pf1550_operating_status_t PF1550_GetOperatingStatus(pf1550_handle_t *handle);

/*!
 * @brief Query if regulator support dynamic voltage scaling.
 *
 * This function is used to query if the regulator support DVS feature.
 * User can only set the output voltage to the regulators that support
 * DVS feature, otherwise PF1550_SetRegulatorOutputVoltage() function will
 * return immediately.
 *
 * @param handle Pointer to a valid PF1550 instance structure.
 * @param module Sub-modules in PF1550 device.
 * @return true: regulator support DVS feature, false: regulator does not support DVS.
 */
bool PF1550_IsRegulatorSupportDvs(pf1550_handle_t *handle, pf1550_module_t module);
/* @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_PF1550_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
