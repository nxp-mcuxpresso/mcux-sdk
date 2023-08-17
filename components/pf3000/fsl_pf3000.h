/*
 * Copyright 2016 Freescale Semiconductor, Inc.
 * Copyright 2016 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_PF3000_H_
#define _FSL_PF3000_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief PF3000 Default I2C address. */
#define PF3000_DEFAULT_I2C_ADDR 0x08U

/*! @brief Define the PMIC Register Memory Map of PF3000. */
/*! Functional page. */
#define PF3000_DEVICE_ID     0x00U
#define PF3000_SILICON_REV   0x03U
#define PF3000_FAB_ID        0x04U
#define PF3000_SW_INT_STAT0  0x05U
#define PF3000_SW_INT_MASK0  0x06U
#define PF3000_SW_INT_SENSE0 0x07U
#define PF3000_SW_INT_STAT1  0x08U
#define PF3000_SW_INT_MASK1  0x09U
#define PF3000_SW_INT_SENSE1 0x0AU
#define PF3000_SW_INT_STAT3  0x0EU
#define PF3000_SW_INT_MASK3  0x0FU
#define PF3000_SW_INT_SENSE3 0x10U
#define PF3000_SW_INT_STAT4  0x11U
#define PF3000_SW_INT_MASK4  0x12U
#define PF3000_SW_INT_SENSE4 0x13U
#define PF3000_COIN_CTRL     0x1AU
#define PF3000_PWR_CTRL      0x1BU
#define PF3000_MEMA          0x1CU
#define PF3000_MEMB          0x1DU
#define PF3000_MEMC          0x1EU
#define PF3000_MEMD          0x1FU
#define PF3000_SW1A_VOLT     0x20U
#define PF3000_SW1A_STBY     0x21U
#define PF3000_SW1A_OFF      0x22U
#define PF3000_SW1A_MODE     0x23U
#define PF3000_SW1A_CONF     0x24U
#define PF3000_SW1B_VOLT     0x2EU
#define PF3000_SW1B_STBY     0x2FU
#define PF3000_SW1B_OFF      0x30U
#define PF3000_SW1B_MODE     0x31U
#define PF3000_SW1B_CONF     0x32U
#define PF3000_SW2_VOLT      0x35U
#define PF3000_SW2_STBY      0x36U
#define PF3000_SW2_OFF       0x37U
#define PF3000_SW2_MODE      0x38U
#define PF3000_SW2_CONF      0x39U
#define PF3000_SW3_VOLT      0x3CU
#define PF3000_SW3_STBY      0x3DU
#define PF3000_SW3_OFF       0x3EU
#define PF3000_SW3_MODE      0x3FU
#define PF3000_SW3_CONF      0x40U
#define PF3000_SWBST_CTRL    0x66U
#define PF3000_LDOG_CTRL     0x69U
#define PF3000_VREFDDR_CTRL  0x6AU
#define PF3000_VSNVS_CTRL    0x6BU
#define PF3000_VLDO1_CTRL    0x6CU
#define PF3000_VLDO2_CTRL    0x6DU
#define PF3000_VCC_SD_CTRL   0x6EU
#define PF3000_V33_CTRL      0x6FU
#define PF3000_VLDO3_CTRL    0x70U
#define PF3000_VLDO4_CTRL    0x71U
#define PF3000_PAGE_REGISTER 0x7FU

/*! Extended page 1. (Only list some registers) */
#define PF3000_OTP_SW1x_CONFIG 0xA2U
#define PF3000_OTP_SW2_VOLT    0xACU

/*! @brief PF3000 Operating Status definition. */
typedef enum _pf3000_operating_status
{
    kPF3000_OperatingStatusSystemOn = 0x0U, /* Indicates the state machine is in On Status. */
    kPF3000_OperatingStatusStandby  = 0x1U, /* Indicates the state machine is in Standby Status. */
    kPF3000_OperatingStatusOff      = 0x2U, /* Indicates the state machine is in Off Status. */
    kPF3000_OperatingStatusSleep    = 0x3U, /* Indicates the state machine is in Sleep Status. */
    kPF3000_OperatingStatusCoinCell = 0x4U, /* Indicates the state machine is in Coin Cell Status. */
} pf3000_operating_status_t;

/*! @brief PF3000 Sub-Module definition. */
typedef enum _pf3000_module
{
    kPF3000_ModuleSwitch1A    = 0x0U, /* Switch1A Sub-Module Identifier. */
    kPF3000_ModuleSwitch1B    = 0x1U, /* Switch1B Sub-Module Identifier. */
    kPF3000_ModuleSwitch2     = 0x2U, /* Switch2 Sub-Module Identifier. */
    kPF3000_ModuleSwitch3     = 0x3U, /* Switch3 Sub-Module Identifier. */
    kPF3000_ModuleSwitchBoost = 0x4U, /* SwitchBoost Sub-Module Identifier. */
    kPF3000_ModuleLdo1        = 0x5U, /* LDO1 Sub-Module Identifier. */
    kPF3000_ModuleLdo2        = 0x6U, /* LDO2 Sub-Module Identifier. */
    kPF3000_ModuleLdo3        = 0x7U, /* LDO3 Sub-Module Identifier. */
    kPF3000_ModuleLdo4        = 0x8U, /* LDO4 Sub-Module Identifier. */
    kPF3000_ModuleVcc_sd      = 0x9U, /* VCC_SD Sub-Module Identifier. */
    kPF3000_ModuleV33         = 0xaU, /* V33 Sub-Module Identifier. */
    kPF3000_ModuleVsnvs       = 0xbU, /* VSNVS Sub-Module Identifier. */
    kPF3000_ModuleVrefDdr     = 0xcU, /* VREFDDR Sub-Module Identifier. */
} pf3000_module_t;

/*! @brief PF3000 Interrupt Source definition. */
enum _pf3000_interrupt_source
{
    kPF3000_IntSrcPwrOn      = 0x1U,  /* Power on. */
    kPF3000_IntSrcLowVoltage = 0x2U,  /* Low-voltage. */
    kPF3000_IntSrcTherm110   = 0x4U,  /* Die temperature crosses 110C interrupt source. */
    kPF3000_IntSrcTherm120   = 0x8U,  /* Die temperature crosses 120C interrupt source. */
    kPF3000_IntSrcTherm125   = 0x10U, /* Die temperature crosses 125C interrupt source. */
    kPF3000_IntSrcTherm130   = 0x20U, /* Die temperature crosses 130C interrupt source. */

    kPF3000_IntSrcSw1aCurrentLimit = 0x1U << 8U,  /* Switch1A current limit interrupt source. */
    kPF3000_IntSrcSw1bCurrentLimit = 0x2U << 8U,  /* Switch1B current limit interrupt source. */
    kPF3000_IntSrcSw2CurrentLimit  = 0x8U << 8U,  /* Switch2  current limit interrupt source. */
    kPF3000_IntSrcSw3CurrentLimit  = 0x10U << 8U, /* Switch3  current limit interrupt source. */

    kPF3000_IntSrcSwBstCurrentLimit = 0x1U << 16U,  /* Switch Boost  current limit interrupt source. */
    kPF3000_IntSrcVpwrVoltageLimit  = 0x4U << 16U,  /* VPWR overvoltage interrupt source. */
    kPF3000_IntSrcOtpAutoFuseDone   = 0x40U << 16U, /* OTP auto fuse blow interrupt source. */
    kPF3000_IntSrcOtpError          = 0x80U << 16U, /* OTP error interrupt source. */

    kPF3000_IntSrcLdo1CurrentLimit   = 0x1U << 24U,  /* LDO1 current limit interrupt source. */
    kPF3000_IntSrcLdo2CurrentLimit   = 0x2U << 24U,  /* LDO2 current limit interrupt source. */
    kPF3000_IntSrcVcc_sdCurrentLimit = 0x4U << 24U,  /* VCC_SD current limit interrupt source. */
    kPF3000_IntSrcV33CurrentLimit    = 0x8U << 24U,  /* V33 current limit interrupt source. */
    kPF3000_IntSrcLdo3CurrentLimit   = 0x10U << 24U, /* LDO3 current limit interrupt source. */
    kPF3000_IntSrcLdo4CurrentLimit   = 0x20U << 24U, /* LDO4 current limit interrupt source. */
};

/*! @brief PF3000 Off Mode definition. */
typedef enum _pf3000_switch_off_mode
{
    kPF3000_OffModeAfterTurnOff   = 0x0U, /* OFF mode entered after a turn-off event. */
    kPF3000_SleepModeAfterTurnOff = 0x1U, /* Sleep mode entered after a turn-off event. */
} pf3000_off_mode_t;

/*! @brief PF3000 Switch Mode Control . */
typedef enum _pf3000_switch_mode
{
    kPF3000_SwitchModeOffOff = 0x0U, /* Off in normal mode, Off in Standby mode. */
    kPF3000_SwitchModePwmOff = 0x1U, /* PWM in normal mode, Off in Standby mode. */
    kPF3000_SwitchModePfmOff = 0x3U, /* PFM in normal mode, Off in Standby mode. */
    kPF3000_SwitchModeApsOff = 0x4U, /* APS in normal mode, Off in Standby mode. */
    kPF3000_SwitchModePwmPwm = 0x5U, /* PWM in normal mode, PWM in Standby mode. */
    kPF3000_SwitchModePwmAps = 0x6U, /* PWM in normal mode, APS in Standby mode. */
    kPF3000_SwitchModeApsAps = 0x8U, /* APS in normal mode, APS in Standby mode. */
    kPF3000_SwitchModeApsPfm = 0xCU, /* APS in normal mode, PFM in Standby mode. */
    kPF3000_SwitchModePwmPfm = 0xDU, /* PWM in normal mode, PFM in Standby mode. */
} pf3000_switch_mode_t;

/*! @brief PF3000 Switch DVS Speed Attribute definition. */
typedef enum _pf3000_switch_dvs_speed
{
    kPF3000_SwitchDvsSpeed_25mVPer2us = 0x0U, /* Switch DVS rate at 25mV/2us. */
    kPF3000_SwitchDvsSpeed_25mVPer4us = 0x1U, /* Switch DVS rate at 25mV/4us. */
} pf3000_switch_dvs_speed_t;

/*! @brief PF3000 Switch Phase Clock definition. */
typedef enum _pf3000_switch_phase_clock
{
    kPF3000_SwitchPhaseClock_0   = 0x0U, /* Switch phase clock 0 degree. */
    kPF3000_SwitchPhaseClock_90  = 0x1U, /* Switch phase clock 90 degree. */
    kPF3000_SwitchPhaseClock_180 = 0x2U, /* Switch phase clock 180 degree. */
    kPF3000_SwitchPhaseClock_270 = 0x3U, /* Switch phase clock 270 degree. */
} pf3000_switch_phase_clock_t;

/*! @brief PF3000 Switch Frequency definition. */
typedef enum _pf3000_switch_frequency
{
    kPF3000_SwitchFrequency_1M = 0x0U, /* Switch Frequency 1MHz. */
    kPF3000_SwitchFrequency_2M = 0x1U, /* Switch Frequency 2MHz. */
    kPF3000_SwitchFrequency_4M = 0x2U, /* Switch Frequency 4MHz. */
} pf3000_switch_phase_frequency_t;

/*! @brief PF3000 Switch Current Limit Attribute definition. */
typedef enum _pf3000_switch_current_limit
{
    kPF3000_SwitchCurrentLimit_2A75 = 0x0U, /* Switch Current Limit: Typical current limit of 2.75A. */
    kPF3000_SwitchCurrentLimit_2A   = 0x1U, /* Switch Current Limit: Typical current limit of 2A. */
} pf3000_switch_current_limit_t;

/*! @brief PF3000 Switch Attribute Structure definition. */
typedef struct _pf3000_switch_attribute
{
    pf3000_off_mode_t offMode;                  /* Switch Off Mode Selection. */
    pf3000_switch_mode_t mode;                  /* Switch Mode Selection. */
    pf3000_switch_dvs_speed_t dvsSpeed;         /* Switch DVS Speed Selection. */
    pf3000_switch_phase_clock_t phaseClock;     /* Switch Phase Clock Selection. */
    pf3000_switch_phase_frequency_t frequency;  /* Switch Phase Frequency Selection. */
    pf3000_switch_current_limit_t currentLimit; /* Switch Current Limit Selection. */
} pf3000_switch_attribute_t;

/*! @brief PF3000 Switch Boost mode definition. */
typedef enum _pf3000_switch_boost_mode
{
    kPF3000_SwitchBoostModeOff  = 0x0U, /* Switch Boost is in Off mode. */
    kPF3000_SwitchBoostModePfm  = 0x1U, /* Switch Boost is in PFM mode. */
    kPF3000_SwitchBoostModeAuto = 0x2U, /* Switch Boost is in AUTO mode. */
    kPF3000_SwitchBoostModeAps  = 0x3U, /* Switch Boost is in APS mode. */
} pf3000_switch_boost_mode_t;

/*! @brief PF3000 Switch Boost Attribute Structure definition. */
typedef struct _pf3000_switch_boost_attribute
{
    pf3000_switch_boost_mode_t standbyMode; /* LDO Off Mode Selection. */
    pf3000_switch_boost_mode_t normalMode;  /* LDO Standby Enable. */
} pf3000_switch_boost_attribute_t;

/*! @brief PF3000 LDO standby mode enable. */
typedef enum _pf3000_ldo_standby_on_off
{
    kPF3000_LdoOnDuringStandby  = 0x0U, /* LDO is ON during standby mode. */
    kPF3000_LdoOffDuringStandby = 0x1U, /* LDO is OFF during standby mode. */
} pf3000_ldo_standby_on_off_t;

/*! @brief PF3000 LDO Attribute Structure definition. */
typedef struct _pf3000_ldo_attribute
{
    pf3000_off_mode_t offMode;                /* LDO Off Mode Selection. */
    bool enableLowPower;                      /* LDO Low Power enable. */
    pf3000_ldo_standby_on_off_t standbyOnOff; /* LDO Standby Enable. */
} pf3000_ldo_attribute_t;

/*! @brief PF3000 Coin Cell Charging Voltage Attribute definition. */
typedef enum _pf3000_coin_cell_charging_voltage
{
    kPF3000_CoinCellChargingVoltage_2V5 = 0x0U, /* Coin cell charger charging voltage 2.5V. */
    kPF3000_CoinCellChargingVoltage_2V7 = 0x1U, /* Coin cell charger charging voltage 2.7V. */
    kPF3000_CoinCellChargingVoltage_2V8 = 0x2U, /* Coin cell charger charging voltage 2.8V. */
    kPF3000_CoinCellChargingVoltage_2V9 = 0x3U, /* Coin cell charger charging voltage 2.9V. */
    kPF3000_CoinCellChargingVoltage_3V0 = 0x4U, /* Coin cell charger charging voltage 3.0V. */
    kPF3000_CoinCellChargingVoltage_3V1 = 0x5U, /* Coin cell charger charging voltage 3.1V. */
    kPF3000_CoinCellChargingVoltage_3V2 = 0x6U, /* Coin cell charger charging voltage 3.2V. */
    kPF3000_CoinCellChargingVoltage_3V3 = 0x7U, /* Coin cell charger charging voltage 3.3V. */
} pf3000_coin_cell_charging_voltage_t;

/*! @brief PF3000 Coin Cell Attribute Structure definition. */
typedef struct _pf3000_coin_cell_attribute
{
    bool enableCoinCellCharger;                                  /* Enable Coin Cell Charger. */
    pf3000_coin_cell_charging_voltage_t coinCellChargingVoltage; /* Vsnvs Coin Cell Charging Voltage Selection. */
} pf3000_coin_cell_attribute_t;

/*! @brief PF3000 Standby Active Polarity definition. */
typedef enum _pf3000_standby_polarity
{
    kPF3000_StandbyPolActiveHigh = 0x0U, /* Standby pin input active high. */
    kPF3000_StandbyPolActiveLow  = 0x1U, /* Standby pin input active low. */
} pf3000_standby_polarity_t;

/*! @brief PF3000 Standby Delay Time definition. */
typedef enum _pf3000_standby_delay
{
    kPF3000_StandbyDelay_None         = 0x0U, /* No additional delay. */
    kPF3000_StandbyDelay_1x32kHzCycle = 0x1U, /* 1 x 32kHz cycle additional delay. */
    kPF3000_StandbyDelay_2x32kHzCycle = 0x2U, /* 2 x 32kHz cycle additional delay. */
    kPF3000_StandbyDelay_3x32kHzCycle = 0x3U, /* 3 x 32kHz cycle additional delay. */
} pf3000_standby_delay_t;

/*! @brief PF3000 Standby Pad Attribute Structure definition. */
typedef struct _pf3000_standby_attribute
{
    pf3000_standby_polarity_t standbyPolarity; /* Standby Active Polarity Selection. */
    pf3000_standby_delay_t standbyDelay;       /* Select delay of Standby pin (after synchronization). */
} pf3000_standby_attribute_t;

/*! @brief PF3000 Power On Pad Debounce Time definition. */
typedef enum _pf3000_power_on_debounce
{
    kPF3000_PowerOnDebounce_TurnOn0msFall31ms25Rise31ms25 = 0x0U,      /* Power On Pad Debounce: 0ms turn on;
                                                                          31.25ms falling edge; 31.25ms rising edge. */
    kPF3000_PowerOnDebounce_TurnOn31ms25msFall31ms25Rise31ms25 = 0x1U, /* Power On Pad Debounce: 31.25ms turn on;
                                                                        31.25ms falling edge; 31.25ms rising edge. */
    kPF3000_PowerOnDebounce_TurnOn125msFall125ms25Rise31ms25 = 0x2U,   /* Power On Pad Debounce: 125ms turn on;
                                                                          125ms falling edge; 31.25ms rising edge. */
    kPF3000_PowerOnDebounce_TurnOn750msFall750ms25Rise31ms25 = 0x3U,   /* Power On Pad Debounce: 750ms turn on;
                                                                          750ms falling edge; 31.25ms rising edge. */
} pf3000_power_on_debounce_t;

/*! @brief PF3000 PWRON Pad Attribute Structure definition. */
typedef struct _pf3000_power_on_attribute
{
    pf3000_power_on_debounce_t debounce; /* Power On Pad Debounce Time Selection. */
    bool longPressAllowOffMode;          /* Allow OFF mode after PWRON held low for 4 seconds. */
    bool longPressRestart;               /* Enables restart of system when PWRON held low for 4 seconds. */
} pf3000_power_on_attribute_t;

/*! @brief PF3000 SW1A SW1B mode selection. */
typedef enum _pf3000_switch1_mode
{
    kPF3000_SW1SinglePhase     = 0x0U, /* Switch 1 A/B Single Phase. */
    kPF3000_SW1IndependentMode = 0x3U, /* Switch 1A and 1B Independent mode */
} pf3000_switch1_mode_t;

/*! @brief PF3000 SW2 voltage range. */
typedef enum _pf3000_switch2_range
{
    kPF3000_SW2LowVoltRange  = 0x0U, /* Switch 1 A/B Single Phase. */
    kPF3000_SW2HighVoltRange = 0x1U, /* Switch 1A and 1B Independent mode */
} pf3000_switch2_range_t;

/*! @brief PF3000 Handle definition. */
typedef struct _pf3000_handle
{
    /* Pointer to the user-defined I2C Send Data function. */
    bool (*I2C_SendFunc)(
        uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *txBuff, uint8_t txBuffSize);
    /* Pointer to the user-defined I2C Receive Data function. */
    bool (*I2C_ReceiveFunc)(
        uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);
    /* The I2C Slave Address Read From OTP. */
    uint8_t slaveAddress;
    /* VSD_VSEL. */
    bool vccsdVsel;
    /* SW1A SW1B mode selection. */
    pf3000_switch1_mode_t switch1Mode;
    /* SW2 voltage range. */
    pf3000_switch2_range_t switch2Range;
} pf3000_handle_t;

/*! @brief PF3000 Configuration Structure definition. */
typedef struct _pf3000_config
{
    /* Pointer to the user-defined I2C Send Data function. */
    bool (*I2C_SendFunc)(
        uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *txBuff, uint8_t txBuffSize);
    /* Pointer to the user-defined I2C Receive Data function. */
    bool (*I2C_ReceiveFunc)(
        uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);

    /* The PF3000 I2C Slave Address. */
    uint8_t slaveAddress;
    /* Short-circuit protection enable. */
    bool enableRegSCP;
    /* VSD_VSEL. */
    bool vccsdVsel;
} pf3000_config_t;

/*!
 * @addtogroup pf3000
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
 * This function initializes the PF3000 configuration structure to default values. The default
 * values are as follows.
 * @code
 *   pf3000Config->I2C_SendFunc              = NULL;
 *   pf3000Config->I2C_ReceiveFunc           = NULL;
 *   pf3000Config->slaveAddress              = PF3000_DEFAULT_I2C_ADDR;
 *   pf3000Config->enableRegSCP              = true;
 *   pf3000Config->vccsdVsel                 = 0U;
 * @endcode
 * @param config Pointer to the PF3000 configuration structure.
 */
void PF3000_GetDefaultConfig(pf3000_config_t *config);

/*!
 * @brief Initializes a PF3000 instance.
 *
 * This function initializes the PF3000 module with user-defined settings.
 * This example shows how to set up the pf3000_config_t parameters and how
 * to call the PF3000_Init function by passing in these parameters.
 * @code
 *   pf3000_config_t pf3000Config;
 *   pf3000Config.I2C_SendFunc              = APP_I2C_SendFunc;
 *   pf3000Config.I2C_ReceiveFunc           = APP_I2C_ReceiveFunc;
 *   pf3000Config.slaveAddress              = PF3000_DEFAULT_I2C_ADDR;
 * @endcode
 *
 * @param handle PF3000 Handle.
 * @param config Pointer to the user-defined configuration structure.
 */
void PF3000_Init(pf3000_handle_t *handle, const pf3000_config_t *config);
/* @} */

/*!
 * @name Basic register access functions
 * @{
 */

/*!
 * @brief Write the value to register of PF3000.
 *
 * @param handle Pointer to a valid PF3000 instance structure.
 * @param reg variable store address of register.
 * @param val variable store value which is written to PF3000.
 * @return true if success or false if error.
 */
bool PF3000_WriteReg(pf3000_handle_t *handle, uint8_t reg, uint8_t val);

/*!
 * @brief Read the value of register in PF3000.
 *
 * @param handle Pointer to a valid PF3000 instance structure.
 * @param reg variable store address of register.
 * @param val pointer store return value.
 * @return true if success or false if error.
 */
bool PF3000_ReadReg(pf3000_handle_t *handle, uint8_t reg, uint8_t *val);

/*!
 * @brief Modify some bits in the register in PF3000.
 * @param handle Pointer to a valid PF3000 instance structure.
 * @param reg variable store address of register.
 * @param mask The mask code for the bits want to write. The bit you want to write should be 1.
 * @param val Value needs to write into the register.
 * @return true if success or false if error.
 */
bool PF3000_ModifyReg(pf3000_handle_t *handle, uint8_t reg, uint8_t mask, uint8_t val);

/*!
 * @brief Dump the register content in PF3000.
 * @param handle Pointer to a valid PF3000 instance structure.
 * @param page The page of the register in.
 * @param reg The address of the first register to dump.
 * @param buffer The buffer to store the dumped content.
 * @param size The count of registers to dump.
 * @return true if success or false if error.
 */
bool PF3000_DumpReg(pf3000_handle_t *handle, uint8_t page, uint8_t reg, uint8_t *buffer, uint8_t size);

/* @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enables PF3000 interrupts according to the provided interrupt source mask.
 *
 * This function enables the PF3000 interrupts according to the provided interrupt source.
 * The interrupt source mask is a logical OR of enumeration members:
 * see @ref _pf3000_interrupt_source all interrupt sources;
 *
 * @param handle Pointer to a valid PF3000 instance structure.
 * @param source Logic ORed interrupt sources of selected interrupt category to enable.
 */
void PF3000_EnableInterrupts(pf3000_handle_t *handle, uint32_t source);

/*!
 * @brief Disable PF3000 interrupts according to the provided interrupt source mask.
 *
 * This function disables the PF3000 interrupts according to the provided interrupt source.
 * The interrupt source mask is a logical OR of enumeration members:
 * see @ref _pf3000_interrupt_source all interrupt sources;
 *
 * @param handle Pointer to a valid PF3000 instance structure.
 * @param source Logic ORed interrupt sources of selected interrupt category to disable.
 */
void PF3000_DisableInterrupts(pf3000_handle_t *handle, uint32_t source);

/*!
 * @brief Get interrupt flags of selected interrupt category.
 *
 * This function gets all interrupt flags of selected interrupt.
 * The flags are returned as the logical OR value of the corresponding interrupt source:
 * see @ref _pf3000_interrupt_source all interrupt sources;
 *
 * @param handle Pointer to a valid PF3000 instance structure.
 * @return status flags which are ORed by the enumerators in the corresponding interrupt source.
 */
uint32_t PF3000_GetInterruptStatus(pf3000_handle_t *handle);

/*!
 * @brief Clear interrupt flags of selected interrupt category.
 *
 * This function clears all interrupt flags of selected interrupt.
 * The interrupt source mask is a logical OR of enumeration members:
 * see @ref _pf3000_interrupt_source all interrupt sources;
 *
 * @param handle Pointer to a valid PF3000 instance structure.
 * @param source Logic ORed interrupt sources of selected interrupt category to clear.
 */
void PF3000_ClearInterruptStatus(pf3000_handle_t *handle, uint32_t source);
/* @} */

/*!
 * @name Regulator control functions
 * @{
 */

/*!
 * @brief Enable/Disable the output of selected regulator.
 *
 * This function is used to enable/disable the output of selected regulator
 * enumerated in @ref pf3000_module_t.
 * For PF3000, LDO1, LDO2, LDO3, LDO4, VCC_SD, V33 and VREFDDE can be enabled or disabled.
 *
 * @param handle Pointer to a valid PF3000 instance structure.
 * @param module Sub-modules in PF3000 device.
 * @param enable Set true to enable regulator, set false to disable regulator.
 */
void PF3000_EnableRegulator(pf3000_handle_t *handle, pf3000_module_t module, bool enable);
/*!
 * @brief Query the output state of selected regulator.
 *
 * This function is used to query the output state of selected regulator
 * enumerated in @ref pf3000_module_t.
 * For PF3000, LDO1, LDO2, LDO3, LDO4, VCC_SD, V33 and VREFDDE can queried.
 * For other regulators, they are always enabled.
 *
 * @param handle Pointer to a valid PF3000 instance structure.
 * @param module Sub-modules in PF3000 device.
 * @return true if regulator is enabled, false if regulator is disabled.
 */
bool PF3000_IsRegulatorEnabled(pf3000_handle_t *handle, pf3000_module_t module);
/*!
 * @brief Set the output voltage of selected regulator.
 *
 * This function is used to set the output voltage of selected regulator
 * enumerated in @ref pf3000_module_t under selected operating status
 * enumerated in @ref pf3000_operating_status_t. The output state of
 * the regulators will change automatically once the operating status
 * changed.
 * Note that, voltage of VSNVS and VREFDDR can't be set.
 * VSNVS is fixed in 3.0V, while VREFDDR is at one half the input voltage.
 * And
 *
 * @param handle Pointer to a valid PF3000 instance structure.
 * @param module Sub-modules in PF3000 device.
 * @param status The operating status of PF3000 to set.
 *        Note that, status is only useful for SW1A, SW1B, SW2 and SW3.
 *        For other regulator, status is not used.
 * @param voltage The output voltage in uV to set.
 */
void PF3000_SetRegulatorOutputVoltage(pf3000_handle_t *handle,
                                      pf3000_module_t module,
                                      pf3000_operating_status_t status,
                                      uint32_t voltage);
/*!
 * @brief Query the output voltage of selected regulator.
 *
 * This function is used to query the output voltage of selected regulator
 * enumerated in @ref pf3000_module_t under selected operating status
 * enumerated in @ref pf3000_operating_status_t.
 * Note that, voltage of VREFDDR can't be set. It's one half the input voltage.
 *
 * @param handle Pointer to a valid PF3000 instance structure.
 * @param module Sub-modules in PF3000 device.
 * @param status The operating status of PF3000 to set.
 *        Note that, status is only useful for SW1A, SW1B, SW2 and SW3.
 *        For other regulator, status is not used.
 * @return voltage The output voltage in uV of selected regulator.
 */
uint32_t PF3000_GetRegulatorOutputVoltage(pf3000_handle_t *handle,
                                          pf3000_module_t module,
                                          pf3000_operating_status_t status);
/*!
 * @brief Set the attributes of selected Buck Switch.
 *
 * This function is used to set the attributes of Buck Switch regulator.
 * All the available attributes for Switch are listed in
 * @ref pf3000_switch_attribute_t.
 *
 * @param handle Pointer to a valid PF3000 instance structure.
 * @param module Sub-modules in PF3000 device.
 * @param attribute Pointer to the Switch Attribute structure to set.
 */
void PF3000_SetSwitchAttribute(pf3000_handle_t *handle,
                               pf3000_module_t module,
                               const pf3000_switch_attribute_t *attribute);
/*!
 * @brief Set the attributes of Switch Boost.
 *
 * This function is used to set the attributes of Switch Boost regulator.
 * All the available attributes for Switch Boost are listed in
 * @ref pf3000_switch_boost_attribute_t.
 *
 * @param handle Pointer to a valid PF3000 instance structure.
 * @param attribute Pointer to the Switch Boost Attribute structure to set.
 */
void PF3000_SetSwitchBoostAttribute(pf3000_handle_t *handle, const pf3000_switch_boost_attribute_t *attribute);
/*!
 * @brief Set the attributes of selected LDO.
 *
 * This function is used to set the attributes of LDO regulator.
 * All the available attributes for LDO regulator are listed in
 * @ref pf3000_ldo_attribute_t.
 *
 * @param handle Pointer to a valid PF3000 instance structure.
 * @param module Sub-modules in PF3000 device.
 * @param attribute Pointer to the LDO Attribute structure to set.
 */
void PF3000_SetLdoAttribute(pf3000_handle_t *handle, pf3000_module_t module, const pf3000_ldo_attribute_t *attribute);
/*!
 * @brief Set the attributes of Coin Cell.
 *
 * This function is used to set the attributes of Coin Cell.
 * All the available attributes for Coin Cell are listed in
 * @ref pf3000_coin_cell_attribute_t.
 *
 * @param handle Pointer to a valid PF3000 instance structure.
 * @param attribute Pointer to the Coin Cell Attribute structure to set.
 */
void PF3000_SetCoinCellAttribute(pf3000_handle_t *handle, const pf3000_coin_cell_attribute_t *attribute);
/*!
 * @brief Set the attributes of Standby Pad.
 *
 * This function is used to set the attributes of Standby Pad.
 * All the available attributes for Standby Pad are listed in
 * @ref pf3000_standby_attribute_t.
 *
 * @param handle Pointer to a valid PF3000 instance structure.
 * @param attribute Pointer to the Standby Pad Attribute structure to set.
 */
void PF3000_SetStandbyPadAttribute(pf3000_handle_t *handle, const pf3000_standby_attribute_t *attribute);
/*!
 * @brief Set the attributes of PowerOn Pad.
 *
 * This function is used to set the attributes of PowerOn Pad.
 * All the available attributes for PowerOn Pad are listed in
 * @ref pf3000_power_on_attribute_t.
 *
 * @param handle Pointer to a valid PF3000 instance structure.
 * @param attribute Pointer to the PowerOn Pad Attribute structure to set.
 */
void PF3000_SetPwrOnPadAttibute(pf3000_handle_t *handle, const pf3000_power_on_attribute_t *attribute);
/* @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_PF3000_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
