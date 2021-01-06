/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "fsl_pf1550_charger.h"

/*******************************************************************************
 * Code
 ******************************************************************************/

void PF1550_SetChargerOperation(pf1550_handle_t *handle, pf1550_charger_operation_t operation)
{
    assert(handle);

    /* Set Charger Operation Mode. */
    (void)PF1550_ModifyReg(handle, PF1550_CHG_OPER, 0x03U, (uint8_t)operation);
}

void PF1550_SetChargerAttibute(pf1550_handle_t *handle, const pf1550_charger_attribute_t *attribute)
{
    uint32_t temp;

    assert(handle);
    assert(attribute);

    /* Set Fast Charge Current. */
    temp = (attribute->fastChargeCurrent_mA > 1000U) ? 1000U : attribute->fastChargeCurrent_mA;
    temp = (attribute->fastChargeCurrent_mA < 100U) ? 100U : temp;
    temp = (temp - 100U) / 50U;
    (void)PF1550_ModifyReg(handle, PF1550_CHG_CURR_CNFG, 0x1FU, (uint8_t)temp);

    /* Set Fast Charge Voltage. */
    temp = (attribute->fastChargeVoltage_uV > 4440000U) ? 4440000U : attribute->fastChargeVoltage_uV;
    temp = (attribute->fastChargeVoltage_uV < 3500000U) ? 3500000U : temp;
    temp = (temp - 3340000U) / 20000U;
    (void)PF1550_ModifyReg(handle, PF1550_BATT_REG, 0x3FU, (uint8_t)temp);

    /* Set Precharge Timer timeout value. */
    (void)PF1550_ModifyReg(handle, PF1550_CHG_TMR, 0x80U, ((attribute->preChargeTime_min <= 30U) ? 0x0U : 0x80U));

    /* Set Fast-charge Timer timeout value. */
    temp = (attribute->fastChargeTime_hr > 14U) ? 14U : attribute->fastChargeTime_hr;
    temp = temp >> 1U;
    (void)PF1550_ModifyReg(handle, PF1550_CHG_TMR, 0x03U, (uint8_t)temp);

    /* Set End-of-charge timer timeout value. */
    temp = (attribute->endOfChargeTime_min > 70U) ? 70U : attribute->endOfChargeTime_min;
    temp = (temp / 10U) << 3U;
    (void)PF1550_ModifyReg(handle, PF1550_CHG_TMR, 0x38U, (uint8_t)temp);

    /* Set End-of-charge current. */
    if (attribute->endOfChargeCurrentThreshold_mA >= 50U)
    {
        temp = 4U << 4U;
    }
    else if (attribute->endOfChargeCurrentThreshold_mA >= 30U)
    {
        temp = 3U << 4U;
    }
    else if (attribute->endOfChargeCurrentThreshold_mA >= 20U)
    {
        temp = 2U << 4U;
    }
    else if (attribute->endOfChargeCurrentThreshold_mA >= 10U)
    {
        temp = 1U << 4U;
    }
    else
    {
        temp = 0U;
    }
    (void)PF1550_ModifyReg(handle, PF1550_CHG_EOC_CNFG, 0x70U, (uint8_t)temp);

    /* Set Charger restart threshold. */
    if (attribute->restartVoltageThreshold_uV == 0U)
    {
        temp = 3U;
    }
    else
    {
        temp = (attribute->restartVoltageThreshold_uV > 200000U) ? 200000U : attribute->restartVoltageThreshold_uV;
        temp = (attribute->restartVoltageThreshold_uV < 100000U) ? 100000U : temp;
        temp = (temp - 100000U) / 50000U;
    }
    (void)PF1550_ModifyReg(handle, PF1550_CHG_EOC_CNFG, 0x03U, (uint8_t)temp);

    /* Set Minimum system regulation voltage */
    temp = (attribute->miniSystemVoltage_uV > 4300000U) ? 4300000U : attribute->miniSystemVoltage_uV;
    if (temp <= 3500000U)
    {
        temp = 0x0U;
    }
    else if (temp <= 3700000U)
    {
        temp = 0x1U << 6U;
    }
    else
    {
        temp = 0x2U << 6U;
    }
    (void)PF1550_ModifyReg(handle, PF1550_BATT_REG, 0xC0U, (uint8_t)temp);

    /* Enable Charger Mode Transition interrupt and End-of-charge interrupt. */
    (void)PF1550_ModifyReg(handle, PF1550_CHG_INT_CNFG, 0x03U, 0x03U);
}

uint32_t PF1550_GetChargerStatus(pf1550_handle_t *handle)
{
    uint32_t status;
    uint8_t temp = 0U;

    assert(handle);

    status = 0U;
    (void)PF1550_ReadReg(handle, PF1550_VBUS_SNS, &temp);
    status |= temp;
    (void)PF1550_ReadReg(handle, PF1550_CHG_SNS, &temp);
    status |= (uint32_t)temp << 8U;
    (void)PF1550_ReadReg(handle, PF1550_BATT_SNS, &temp);
    status |= (uint32_t)temp << 16U;

    return status;
}

void PF1550_SetChargerWdog(pf1550_handle_t *handle, uint32_t timeout_sec, bool enable)
{
    assert(handle);

    if (enable)
    {
        (void)PF1550_ModifyReg(handle, PF1550_BATFET_CNFG, 0x40U, ((timeout_sec <= 32U) ? 0x40U : 0x0U));
        (void)PF1550_ModifyReg(handle, PF1550_CHG_OPER, 0x04U, 0x4U);
    }
    else
    {
        (void)PF1550_ModifyReg(handle, PF1550_CHG_OPER, 0x04U, 0x0U);
    }
}

void PF1550_ServiceChargerWdog(pf1550_handle_t *handle)
{
    assert(handle);

    (void)PF1550_ModifyReg(handle, PF1550_BATFET_CNFG, 0x03U, 0x1U);
}

void PF1550_EnableBatFET(pf1550_handle_t *handle, bool enable)
{
    assert(handle);

    (void)PF1550_ModifyReg(handle, PF1550_CHG_OPER, 0x08U, (enable ? 0x0U : 0x8U));
}

void PF1550_SetBatFETAttibute(pf1550_handle_t *handle, const pf1550_batFET_attribute_t *attribute)
{
    uint32_t temp;

    assert(handle);
    assert(attribute);

    /* Set VBATT to VSYS FET overcurrent Threshold. */
    if (attribute->overcurrentThreshold_mA == 0U)
    {
        temp = 0x0U;
    }
    else if (attribute->overcurrentThreshold_mA >= 3200U)
    {
        temp = 0x3U;
    }
    else if (attribute->overcurrentThreshold_mA >= 2800U)
    {
        temp = 0x2U;
    }
    else
    {
        temp = 0x1U;
    }
    temp = temp << 4U;
    (void)PF1550_ModifyReg(handle, PF1550_BATFET_CNFG, 0x30U, (uint8_t)temp);

    /* Set BATFET battery overcurrent limit protection. */
    /* Set BATFET battery overcurrent protection when no VBUS is present. */
    temp = 0U;
    temp |= attribute->overcurrentProtectEnable ? 0x0U : 0x8U;
    temp |= attribute->overcurrentProtectEnableNoVbus ? 0x80U : 0x0U;
    (void)PF1550_ModifyReg(handle, PF1550_BATFET_CNFG, 0x88U, (uint8_t)temp);

    /* Set BATFET control during battery overvoltage. */
    /* Set BATFET control during watchdog fault. */
    /* Set BATFET control during thermistor fault (< Cold or > Hot). */
    /* Set BATFET control during thermal shutdown. */
    /* Set BATFET control during charger timer fault. */
    temp = 0U;
    temp |= attribute->overvoltageFaultProtectEnable ? 0x1U : 0x0U;
    temp |= attribute->watchDogFaultProtectEnable ? 0x2U : 0x0U;
    temp |= attribute->thermalFaultProtectEnable ? 0x4U : 0x0U;
    temp |= attribute->thermalShutdownProtectEnable ? 0x8U : 0x0U;
    temp |= attribute->timerFaultProtectEnable ? 0x10U : 0x0U;
    (void)PF1550_ModifyReg(handle, PF1550_FAULT_BATFET_CNFG, 0x1FU, (uint8_t)temp);
}

void PF1550_SetPowerPathAttibute(pf1550_handle_t *handle, const pf1550_power_path_attribute_t *attribute)
{
    uint32_t temp;

    assert(handle);
    assert(attribute);

    /* Set Maximum Vbus input current limit. */
    if (attribute->vbusCurrentLimit_mA >= 1500U)
    {
        temp = 20U;
    }
    else if (attribute->vbusCurrentLimit_mA >= 1000U)
    {
        temp = 19U;
    }
    else if (attribute->vbusCurrentLimit_mA >= 200U)
    {
        temp = (attribute->vbusCurrentLimit_mA + 900U) / 100U;
    }
    else if (attribute->vbusCurrentLimit_mA >= 100U)
    {
        temp = (attribute->vbusCurrentLimit_mA + 350U) / 50U;
    }
    else if (attribute->vbusCurrentLimit_mA >= 10U)
    {
        temp = (attribute->vbusCurrentLimit_mA - 10U) / 5U;
    }
    else
    {
        temp = 0U;
    }
    temp = temp << 3U;
    (void)PF1550_ModifyReg(handle, PF1550_VBUS_INLIM_CNFG, 0xF8U, (uint8_t)temp);

    /* Set VBUS regulation voltage (DPM mode) */
    temp = (attribute->vbusDpmVoltage_uV < 3900000U) ? 3900000U : attribute->vbusDpmVoltage_uV;
    temp = (attribute->vbusDpmVoltage_uV > 4600000U) ? 4600000U : temp;
    temp = (temp - 3900000U) / 100000U;
    (void)PF1550_ModifyReg(handle, PF1550_VBUS_LIN_DPM, 0x07U, (uint8_t)temp);

    /* Set Dynamic input power management panic stop threshold. */
    if (attribute->vbusDpmStopThreshold_uV < 250000U)
    {
        temp = 0U;
    }
    else
    {
        temp = 1U;
    }
    temp = temp << 5U;
    (void)PF1550_ModifyReg(handle, PF1550_VBUS_LIN_DPM, 0x20U, (uint8_t)temp);

    /* Set VBUS overvoltage debounce delay. */
    if (attribute->vbusOvDebounce_us < 1000U)
    {
        temp = 1U;
    }
    else if (attribute->vbusOvDebounce_us < 10000U)
    {
        temp = 2U;
    }
    else
    {
        temp = 3U;
    }
    (void)PF1550_ModifyReg(handle, PF1550_DBNC_DELAY_TIME, 0x03U, (uint8_t)temp);

    /* Set VBUS to VSYS comparator debounce time. */
    if (attribute->vbus2vsysDebounce_us < 1000U)
    {
        temp = 1U;
    }
    else if (attribute->vbus2vsysDebounce_us < 10000U)
    {
        temp = 2U;
    }
    else
    {
        temp = 3U;
    }
    (void)PF1550_ModifyReg(handle, PF1550_VBUS2SYS_CNFG, 0x03U, (uint8_t)temp);

    /* Set VBUS to VSYS comparator threshold setting. */
    if (attribute->vbus2vsysThreashold_uV < 175000U)
    {
        temp = 0U;
    }
    else
    {
        temp = 1U << 2U;
    }
    (void)PF1550_ModifyReg(handle, PF1550_VBUS2SYS_CNFG, 0x04U, (uint8_t)temp);

    /* Set USBPHY voltage. */
    if (attribute->usbPhyVoltage_uV < 4900000U)
    {
        temp = 0U;
    }
    else
    {
        temp = 1U << 1U;
    }
    (void)PF1550_ModifyReg(handle, PF1550_USB_PHY_LDO_CNFG, 0x02U, (uint8_t)temp);

    /* Set Vsys Wake-up delay. */
    if (attribute->vsysWakeupDelay_ms < 16U)
    {
        temp = 0U;
    }
    else if (attribute->vsysWakeupDelay_ms < 32U)
    {
        temp = 1U;
    }
    else if (attribute->vsysWakeupDelay_ms < 100U)
    {
        temp = 2U;
    }
    else
    {
        temp = 3U;
    }
    temp = temp << 4U;
    (void)PF1550_ModifyReg(handle, PF1550_DBNC_DELAY_TIME, 0x30U, (uint8_t)temp);

    /* Set Active discharger enable for USBPHY. */
    /* Set USBPHY LDO enable. */
    temp = attribute->usbPhyDischargerEnbale ? 0x1U : 0x0U;
    temp |= attribute->usbPhyLdoEnable ? 0x4U : 0x0U;
    (void)PF1550_ModifyReg(handle, PF1550_USB_PHY_LDO_CNFG, 0x05U, (uint8_t)temp);
}

void PF1550_SetThermalAttibute(pf1550_handle_t *handle, const pf1550_thermal_attribute_t *attribute)
{
    uint32_t temp;

    assert(handle);
    assert(attribute);

    /* Set Thermistor Configuration. */
    (void)PF1550_ModifyReg(handle, PF1550_THM_REG_CNFG, 0x03U, (uint8_t)attribute->mode);

    /* Set Junction temperature thermal regulation loop set point. */
    if (attribute->junctionThermalSetPoint_C < 95)
    {
        temp = 0U;
    }
    else if (attribute->junctionThermalSetPoint_C < 110)
    {
        temp = 1U;
    }
    else
    {
        temp = 2U;
    }
    temp = temp << 2U;
    (void)PF1550_ModifyReg(handle, PF1550_THM_REG_CNFG, 0x0CU, (uint8_t)temp);

    /* Set Thermistor cold temperature selection. */
    temp = (attribute->thermalColdThreshold_C <= -10) ? (1U << 4U) : 0U;
    (void)PF1550_ModifyReg(handle, PF1550_THM_REG_CNFG, 0x10U, (uint8_t)temp);

    /* Set Thermistor cool threshold setting. */
    temp = (attribute->thermalCoolThreshold_C <= 10) ? (1U << 1U) : 0U;
    (void)PF1550_ModifyReg(handle, PF1550_THM_ADJ_SETTING, 0x02U, (uint8_t)temp);

    /* Set Thermistor warm threshold setting. */
    temp = (attribute->thermalWarmThreshold_C < 50) ? 0U : 1U;
    (void)PF1550_ModifyReg(handle, PF1550_THM_ADJ_SETTING, 0x01U, (uint8_t)temp);

    /* Set Thermistor hot temperature selection. */
    temp = (attribute->thermalHotThreshold_C < 60) ? (1U << 5U) : 0U;
    (void)PF1550_ModifyReg(handle, PF1550_THM_REG_CNFG, 0x20U, (uint8_t)temp);

    /* Set JEITA Thermistor battery termination voltage subtraction. */
    if (attribute->thermalVoltageAdjust_uV >= 200000U)
    {
        temp = 3U;
    }
    else if (attribute->thermalVoltageAdjust_uV >= 160000U)
    {
        temp = 2U;
    }
    else if (attribute->thermalVoltageAdjust_uV >= 100000U)
    {
        temp = 1U;
    }
    else
    {
        temp = 0U;
    }
    temp = temp << 2U;
    (void)PF1550_ModifyReg(handle, PF1550_THM_ADJ_SETTING, 0x0CU, (uint8_t)temp);

    /* Set JEITA Thermistor battery charging current setting (percentage of I_FC). */
    if (attribute->thermalCurrentAdjust_pct >= 100U)
    {
        temp = 3U;
    }
    else if (attribute->thermalCurrentAdjust_pct >= 75U)
    {
        temp = 2U;
    }
    else if (attribute->thermalCurrentAdjust_pct >= 50U)
    {
        temp = 1U;
    }
    else
    {
        temp = 0U;
    }
    temp = temp << 4U;
    (void)PF1550_ModifyReg(handle, PF1550_THM_ADJ_SETTING, 0x30U, (uint8_t)temp);

    /* Enable/disable thermal foldback current function. */
    temp = attribute->thermalFoldbackEnable ? (1U << 7U) : 0U;
    (void)PF1550_ModifyReg(handle, PF1550_THM_REG_CNFG, 0x80U, (uint8_t)temp);
}

void PF1550_SetledOutput(pf1550_handle_t *handle, bool value)
{
    assert(handle);

    (void)PF1550_ModifyReg(handle, PF1550_LED_PWM, 0x80U, (value ? 0x80U : 0x0U));
}

void PF1550_SetLedAttibute(pf1550_handle_t *handle, const pf1550_led_attribute_t *attribute)
{
    uint32_t temp;

    assert(handle);
    assert(attribute);

    /* Set Controls LED on/blinking mode. */
    temp = (attribute->mode == kPF1550_LedMode_1) ? (1U << 4U) : 0x0U;
    (void)PF1550_ModifyReg(handle, PF1550_LED_CNFG, 0x10U, (uint8_t)temp);

    /* Set LED PWM duty cycle setting. */
    temp = (attribute->pwmDuty_pct > 100U) ? 100U : attribute->pwmDuty_pct;
    temp = (temp * 32U) / 100U;
    (void)PF1550_ModifyReg(handle, PF1550_LED_PWM, 0x3FU, (uint8_t)temp);

    /* Set LED driver PWM frequency setting. */
    if (attribute->pwmFrequency_mHz >= 256000U)
    {
        temp = 0U;
    }
    else if (attribute->pwmFrequency_mHz >= 8000U)
    {
        temp = 1U;
    }
    else if (attribute->pwmFrequency_mHz >= 1000U)
    {
        temp = 2U;
    }
    else
    {
        temp = 3U;
    }
    (void)PF1550_ModifyReg(handle, PF1550_LED_CNFG, 0x03U, (uint8_t)temp);

    /* Set Enable PWM ramp enable. */
    temp = attribute->rampEnable ? 0x40U : 0x0U;
    (void)PF1550_ModifyReg(handle, PF1550_LED_PWM, 0x40U, (uint8_t)temp);

    /* Set Enable software control of LED. */
    temp = attribute->swCtrlEnable ? 0x20U : 0x0U;
    (void)PF1550_ModifyReg(handle, PF1550_LED_CNFG, 0x20U, (uint8_t)temp);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
