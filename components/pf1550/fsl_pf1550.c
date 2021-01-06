/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_pf1550.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* INT_CATEGORY bit-field. */
#define PF1550_INT_CATEGORY_CHG_INT_MASK   (0x01U)
#define PF1550_INT_CATEGORY_SW1_INT_MASK   (0x02U)
#define PF1550_INT_CATEGORY_SW2_INT_MASK   (0x04U)
#define PF1550_INT_CATEGORY_SW3_INT_MASK   (0x08U)
#define PF1550_INT_CATEGORY_LDO_INT_MASK   (0x10U)
#define PF1550_INT_CATEGORY_ONKEY_INT_MASK (0x20U)
#define PF1550_INT_CATEGORY_TEMP_INT_MASK  (0x40U)
#define PF1550_INT_CATEGORY_MISC_INT_MASK  (0x80U)
/* REGULATOR_CTRL bit-field. */
#define PF1550_REGULATOR_CTRL_EN_MASK       (0x01U)
#define PF1550_REGULATOR_CTRL_STBY_EN_MASK  (0x02U)
#define PF1550_REGULATOR_CTRL_OMODE_MASK    (0x04U)
#define PF1550_REGULATOR_CTRL_SYSON_EN_MASK (0x07U)
/* SW_CTRL bit-field. */
#define PF1550_SW_CTRL_LPWR_MASK      (0x08U)
#define PF1550_SW_CTRL_DVSSPEED_MASK  (0x10U)
#define PF1550_SW_CTRL_DVSSPEED_SHIFT (4U)
#define PF1550_SW_CTRL_DVSSPEED(x) \
    (((uint8_t)((uint8_t)(x) << PF1550_SW_CTRL_DVSSPEED_SHIFT)) & PF1550_SW_CTRL_DVSSPEED_MASK)
#define PF1550_SW_CTRL_FPWM_IN_DVS_MASK (0x20U)
#define PF1550_SW_CTRL_FPWM_MASK        (0x40U)
#define PF1550_SW_CTRL_RDIS_EN_MASK     (0x80U)
/* LDO_CTRL bit-field. */
#define PF1550_LDO_CTRL_LPWR_MASK  (0x08U)
#define PF1550_LDO_CTRL_LS_EN_MASK (0x10U)
/* COINCELL bit-field. */
#define PF1550_COINCELL_CONTROL_COINCHEN_MASK (0x10U)
/* VSNVS_CTRL bit-field. */
#define PF1550_VSNVS_CTRL_LIBGDIS_MASK (0x20U)
/* PWRCTRL0 bit-field. */
#define PF1550_PWRCTRL0_STANDBYDLY_MASK  (0x03U)
#define PF1550_PWRCTRL0_STANDBYINV_MASK  (0x04U)
#define PF1550_PWRCTRL0_STANDBYINV_SHIFT (2U)
#define PF1550_PWRCTRL0_STANDBYINV(x) \
    (((uint8_t)((uint8_t)(x) << PF1550_PWRCTRL0_STANDBYINV_SHIFT)) & PF1550_PWRCTRL0_STANDBYINV_MASK)
#define PF1550_PWRCTRL0_POR_DLY_MASK  (0x38U)
#define PF1550_PWRCTRL0_POR_DLY_SHIFT (3U)
#define PF1550_PWRCTRL0_POR_DLY(x) \
    (((uint8_t)((uint8_t)(x) << PF1550_PWRCTRL0_POR_DLY_SHIFT)) & PF1550_PWRCTRL0_POR_DLY_MASK)
#define PF1550_PWRCTRL0_TGRESET_MASK  (0xC0U)
#define PF1550_PWRCTRL0_TGRESET_SHIFT (6U)
#define PF1550_PWRCTRL0_TGRESET(x) \
    (((uint8_t)((uint8_t)(x) << PF1550_PWRCTRL0_TGRESET_SHIFT)) & PF1550_PWRCTRL0_TGRESET_MASK)
/* PWRCTRL1 bit-field. */
#define PF1550_PWRCTRL1_PWRONDBNC_MASK  (0x03U)
#define PF1550_PWRCTRL1_PWRONRSTEN_MASK (0x10U)
#define PF1550_PWRCTRL1_RESTARTEN_MASK  (0x20U)
#define PF1550_PWRCTRL1_ONKEYDBNC_MASK  (0x0CU)
#define PF1550_PWRCTRL1_ONKEYDBNC_SHIFT (2U)
#define PF1550_PWRCTRL1_ONKEYDBNC(x) \
    (((uint8_t)((uint8_t)(x) << PF1550_PWRCTRL1_ONKEYDBNC_SHIFT)) & PF1550_PWRCTRL1_ONKEYDBNC_MASK)
#define PF1550_PWRCTRL1_REGSCPEN_MASK     (0x40U)
#define PF1550_PWRCTRL1_ONKEY_RST_EN_MASK (0x80U)
/* PWRCTRL2 bit-field. */
#define PF1550_PWRCTRL2_UVDET_MASK (0x03U)
/* OTP_SW1_SW2 bit-field. */
#define PF1550_OTP_SW1_SW2_OTP_SW1_DVS_ENB_MASK (0x02U)
/* OTP_SW2_SW3 bit-field. */
#define PF1550_OTP_SW2_SW3_OTP_SW2_DVS_ENB_MASK (0x08U)

/* Regulator Control Helper Macros. */
#define PF1550_SWX_SET_POINT_NUM        (64U)
#define PF1550_SWX_OUTPUT_LIMIT_LOW_DVS (600000U)
#define PF1550_SWX_OUTPUT_STEP_DVS      (12500U)
#define PF1550_SWY_SET_POINT_NUM        (16U)
#define PF1550_SWY_OUTPUT_LIMIT_LOW     (1800000U)
#define PF1550_SWY_OUTPUT_STEP          (100000U)
#define PF1550_LDOX_SET_POINT_NUM       (16U)
#define PF1550_LDOX_OUTPUT_LIMIT_LOW    (1800000U)
#define PF1550_LDOX_OUTPUT_STEP         (100000U)
#define PF1550_LDOY_SET_POINT_NUM       (32U)
#define PF1550_LDOY_SET_POINT_LOW_NUM   (16U)
#define PF1550_LDOY_OUTPUT_LIMIT_LOW    (750000U)
#define PF1550_LDOY_OUTPUT_STEP_LOW     (50000U)
#define PF1550_LDOY_OUTPUT_LIMIT_MID    (1800000U)
#define PF1550_LDOY_OUTPUT_STEP_HIGH    (100000U)
#define PF1550_VSNVS_OUTPUT_VOLTAGE     (3300000U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static const uint8_t powerDownRegTab[] = {
    PF1550_SW1_PWRDN_SEQ,
    PF1550_SW2_PWRDN_SEQ,
    PF1550_SW3_PWRDN_SEQ,
    PF1550_LDO1_PWRDN_SEQ,
    PF1550_LDO2_PWRDN_SEQ,
    PF1550_LDO3_PWRDN_SEQ,
    0x0,
    PF1550_VREFDDR_PWRDN_SEQ,
};
static const uint8_t regulatorCtrlRegTab[] = {
    PF1550_SW1_CTRL,  PF1550_SW2_CTRL,  PF1550_SW3_CTRL,   PF1550_LDO1_CTRL,
    PF1550_LDO2_CTRL, PF1550_LDO3_CTRL, PF1550_VSNVS_CTRL, PF1550_VREFDDR_CTRL,
};
static const uint8_t regulatorVoltRegTab[] = {
    PF1550_SW1_VOLT, PF1550_SW2_VOLT, PF1550_SW3_VOLT, PF1550_LDO1_VOLT, PF1550_LDO2_VOLT, PF1550_LDO3_VOLT, 0x0, 0x0,
};
static const uint32_t regulatorSwVoltSetPonitTab[] = {
    1100000U, 1200000U, 1350000U, 1500000U, 1800000U, 2500000U, 3000000U, 3300000U,
};

/*******************************************************************************
 * Code
 ******************************************************************************/

static bool PF1550_ReadOtp(pf1550_handle_t *handle, uint8_t reg, uint8_t *val)
{
    bool result = false;

    assert(handle);
    assert(val);

    result = PF1550_WriteReg(handle, PF1550_KEY1, 0x15);
    if (true == result)
    {
        result = PF1550_WriteReg(handle, PF1550_CHGR_KEY2, 0x50);
        if (true == result)
        {
            result = PF1550_WriteReg(handle, PF1550_KEY3, 0xAB);
            if (true == result)
            {
                result = PF1550_WriteReg(handle, PF1550_FMRADDR, reg);
                if (true == result)
                {
                    result = PF1550_ReadReg(handle, PF1550_FMRDATA, val);
                }
            }
        }
    }

    return result;
}

static uint8_t PF1550_GetRegulatorSetPoint(pf1550_handle_t *handle, pf1550_module_t module, uint32_t voltage)
{
    uint8_t regulatorSetPoint = 0U;
    uint32_t index;

    assert(handle);
    assert((kPF1550_ModuleSwitch1 == module) || (kPF1550_ModuleSwitch2 == module) ||
           (kPF1550_ModuleSwitch3 == module) || (kPF1550_ModuleLdo1 == module) || (kPF1550_ModuleLdo2 == module) ||
           (kPF1550_ModuleLdo3 == module));

    switch (module)
    {
        /* Process Switch X. */
        case kPF1550_ModuleSwitch1:
        case kPF1550_ModuleSwitch2:
            /* Find the first Vset_point >= voltage */
            for (index = 0U; index < PF1550_SWX_SET_POINT_NUM; index++)
            {
                if ((PF1550_SWX_OUTPUT_LIMIT_LOW_DVS + (PF1550_SWX_OUTPUT_STEP_DVS * index)) >= voltage)
                {
                    regulatorSetPoint = (uint8_t)index;
                    break;
                }
            }
            /* Not found, Desired voltage is beyond upper limit. */
            if (PF1550_SWX_SET_POINT_NUM == index)
            {
                /* Use Vset_point_max as actual Voutput. */
                regulatorSetPoint = PF1550_SWX_SET_POINT_NUM - 1U;
            }
            break;

        /* Process Switch Y. */
        case kPF1550_ModuleSwitch3:
            for (index = 0U; index < PF1550_SWY_SET_POINT_NUM; index++)
            {
                if ((PF1550_SWY_OUTPUT_LIMIT_LOW + (PF1550_SWY_OUTPUT_STEP * index)) >= voltage)
                {
                    regulatorSetPoint = (uint8_t)index;
                    break;
                }
            }
            /* Desired voltage is beyond upper limit. */
            if (PF1550_SWY_SET_POINT_NUM == index)
            {
                regulatorSetPoint = PF1550_SWY_SET_POINT_NUM - 1U;
            }
            break;

        /* Process LDO X. */
        case kPF1550_ModuleLdo2:
            for (index = 0U; index < PF1550_LDOX_SET_POINT_NUM; index++)
            {
                if ((PF1550_LDOX_OUTPUT_LIMIT_LOW + (PF1550_LDOX_OUTPUT_STEP * index)) >= voltage)
                {
                    regulatorSetPoint = (uint8_t)index;
                    break;
                }
            }
            /* Desired voltage is beyond upper limit. */
            if (PF1550_LDOX_SET_POINT_NUM == index)
            {
                regulatorSetPoint = PF1550_LDOX_SET_POINT_NUM - 1U;
            }
            break;

        /* Process LDO Y. */
        case kPF1550_ModuleLdo1:
        case kPF1550_ModuleLdo3:
            for (index = 0U; index < PF1550_LDOY_SET_POINT_NUM; index++)
            {
                if (((index < PF1550_LDOY_SET_POINT_LOW_NUM) &&
                     ((PF1550_LDOY_OUTPUT_LIMIT_LOW + (PF1550_LDOY_OUTPUT_STEP_LOW * index)) >= voltage)) ||
                    ((index >= PF1550_LDOY_SET_POINT_LOW_NUM) &&
                     ((PF1550_LDOY_OUTPUT_LIMIT_MID +
                       (PF1550_LDOY_OUTPUT_STEP_HIGH * (index - PF1550_LDOY_SET_POINT_LOW_NUM))) >= voltage)))
                {
                    regulatorSetPoint = (uint8_t)index;
                    break;
                }
            }
            /* Desired voltage is byond upper limit. */
            if (PF1550_LDOY_SET_POINT_NUM == index)
            {
                regulatorSetPoint = PF1550_LDOY_SET_POINT_NUM - 1U;
            }
            break;

        default:
            assert(false);
            break;
    }

    return regulatorSetPoint;
}

static uint32_t PF1550_GetRegulatorOutputVolt(pf1550_handle_t *handle, pf1550_module_t module, uint8_t voltRegContent)
{
    uint32_t voltage;

    assert(handle);
    assert((kPF1550_ModuleSwitch1 == module) || (kPF1550_ModuleSwitch2 == module) ||
           (kPF1550_ModuleSwitch3 == module) || (kPF1550_ModuleLdo1 == module) || (kPF1550_ModuleLdo2 == module) ||
           (kPF1550_ModuleLdo3 == module));

    switch (module)
    {
        /* Process Switch X. */
        case kPF1550_ModuleSwitch1:
        case kPF1550_ModuleSwitch2:
            /* Get Set Point when Switch DVS feature is enabled. */
            if (true == PF1550_IsRegulatorSupportDvs(handle, module))
            {
                voltage = PF1550_SWX_OUTPUT_LIMIT_LOW_DVS + (uint32_t)PF1550_SWX_OUTPUT_STEP_DVS * voltRegContent;
            }
            /* Get Set Point when Switch DVS feature is disable. */
            else
            {
                if (sizeof(regulatorSwVoltSetPonitTab) / sizeof(regulatorSwVoltSetPonitTab[0]) <= voltRegContent)
                {
                    voltage = regulatorSwVoltSetPonitTab[(sizeof(regulatorSwVoltSetPonitTab) /
                                                          sizeof(regulatorSwVoltSetPonitTab[0])) -
                                                         1U];
                }
                else
                {
                    voltage = regulatorSwVoltSetPonitTab[voltRegContent];
                }
            }
            break;

        /* Process Switch Y. */
        case kPF1550_ModuleSwitch3:
            voltage = PF1550_SWY_OUTPUT_LIMIT_LOW + (PF1550_SWY_OUTPUT_STEP * voltRegContent);
            break;

        /* Process LDO X. */
        case kPF1550_ModuleLdo2:
            voltage = PF1550_LDOX_OUTPUT_LIMIT_LOW + (PF1550_LDOX_OUTPUT_STEP * voltRegContent);
            break;

        /* Process LDO Y. */
        case kPF1550_ModuleLdo1:
        case kPF1550_ModuleLdo3:
            if (PF1550_LDOY_SET_POINT_LOW_NUM <= voltRegContent)
            {
                voltage = PF1550_LDOY_OUTPUT_LIMIT_MID +
                          (PF1550_LDOY_OUTPUT_STEP_HIGH * ((uint32_t)voltRegContent - PF1550_LDOY_SET_POINT_LOW_NUM));
            }
            else
            {
                voltage = PF1550_LDOY_OUTPUT_LIMIT_LOW + (PF1550_LDOY_OUTPUT_STEP_LOW * (uint32_t)voltRegContent);
            }
            break;

        default:
            voltage = 0U;
            break;
    }

    return voltage;
}

void PF1550_GetDefaultConfig(pf1550_config_t *config)
{
    assert(config);

    /* Set callback function to NULL Pointer. */
    config->I2C_SendFunc    = NULL;
    config->I2C_ReceiveFunc = NULL;

    /* Under-Voltage interrupt will assert when Vsys rising voltage cross 3.0V
     * or Vsys rising voltage cross 2.9V. */
    config->threshold = kPF1550_UnderVoltDetThres_Rising3V0Falling2V9;
    /* PF1550 reset MCU 2ms later after last regulator power up. */
    config->delay = kPF1550_PowerUpDelay_2ms;
    /* PF1550 will not disable LDO when Current Limit Fault occur. */
    config->shutDownLdoInCurrentFault = false;
    /* Set Default Slave Address. */
    config->slaveAddress = PF1550_DEFAULT_I2C_ADDR;
}

void PF1550_Init(pf1550_handle_t *handle, const pf1550_config_t *config)
{
    assert(handle);
    assert(config);

    /* Initialize Callback functions. */
    handle->I2C_SendFunc    = config->I2C_SendFunc;
    handle->I2C_ReceiveFunc = config->I2C_ReceiveFunc;
    /* Set Slave Address. */
    handle->slaveAddress = config->slaveAddress;

    /* Set Vsys Under-Voltage Detection Threshold. */
    (void)PF1550_ModifyReg(handle, PF1550_PWRCTRL2, PF1550_PWRCTRL2_UVDET_MASK, (uint8_t)(config->threshold));
    /* Set Power Up Delay Time. */
    (void)PF1550_ModifyReg(handle, PF1550_PWRCTRL0, PF1550_PWRCTRL0_POR_DLY_MASK,
                           PF1550_PWRCTRL0_POR_DLY(config->delay));
    /* Shuts down LDO if it enters a current limit fault. */
    (void)PF1550_ModifyReg(handle, PF1550_PWRCTRL1, PF1550_PWRCTRL1_REGSCPEN_MASK,
                           config->shutDownLdoInCurrentFault ? PF1550_PWRCTRL1_REGSCPEN_MASK : 0x0U);
}

bool PF1550_WriteReg(pf1550_handle_t *handle, uint8_t reg, uint8_t val)
{
    assert(handle);
    assert(handle->I2C_SendFunc);

    return (kStatus_Success == handle->I2C_SendFunc(handle->slaveAddress, reg, 1U, &val, 1U)) ? true : false;
}

bool PF1550_ReadReg(pf1550_handle_t *handle, uint8_t reg, uint8_t *val)
{
    assert(handle);
    assert(handle->I2C_ReceiveFunc);
    assert(val);

    return (kStatus_Success == handle->I2C_ReceiveFunc(handle->slaveAddress, reg, 1U, val, 1U)) ? true : false;
}

bool PF1550_ModifyReg(pf1550_handle_t *handle, uint8_t reg, uint8_t mask, uint8_t val)
{
    bool result      = false;
    uint8_t regValue = 0U;

    assert(handle);

    /* Read back the register content. */
    result = PF1550_ReadReg(handle, reg, &regValue);
    if (true == result)
    {
        /* Modify the bit-fields you want to change. */
        regValue &= (uint8_t)~mask;
        regValue |= val;

        /* Write back the content to the registers. */
        result = PF1550_WriteReg(handle, reg, regValue);
    }

    return result;
}

bool PF1550_DumpReg(pf1550_handle_t *handle, uint8_t reg, uint8_t *buffer, uint8_t size)
{
    bool result = true;
    uint8_t i;

    assert(handle);
    assert(buffer);

    /* It seems that PF1550 only supports single-byte I2C transactions
       for read and write. */
    for (i = 0; i < size; i++)
    {
        if (false == PF1550_ReadReg(handle, reg++, buffer++))
        {
            result = false;
        }
    }

    return result;
}

uint32_t PF1550_GetInterruptCategory(pf1550_handle_t *handle)
{
    uint8_t category = 0U;

    assert(handle);

    /* It seems that PF1550 only support  */
    (void)PF1550_ReadReg(handle, PF1550_INT_CATEGORY, &category);

    return category;
}

void PF1550_EnableInterrupts(pf1550_handle_t *handle, pf1550_interrupt_category_t category, uint32_t source)
{
    assert(handle);

    switch (category)
    {
        case kPF1550_IntCategoryCharger:
            /* Enable Charger interrupts. */
            (void)PF1550_ModifyReg(handle, PF1550_CHG_INT_MASK, (uint8_t)(source & 0xFFU), 0x0U);
            break;

        case kPF1550_IntCategorySwitch:
            /* Enable Switch low side current limit interrupts. */
            (void)PF1550_ModifyReg(handle, PF1550_SW_INT_MASK0, (uint8_t)(source & 0xFFU), 0x0U);
            /* Enable Switch high side current limit interrupts. */
            (void)PF1550_ModifyReg(handle, PF1550_SW_INT_MASK1, (uint8_t)((source & 0xFF00U) >> 8U), 0x0U);
            /* Enable Switch DVS complete interrupts. */
            (void)PF1550_ModifyReg(handle, PF1550_SW_INT_MASK2, (uint8_t)((source & 0xFF0000U) >> 16U), 0x0U);
            break;

        case kPF1550_IntCategoryLdo:
            /* Enable LDO current limit fault interrupts. */
            (void)PF1550_ModifyReg(handle, PF1550_LDO_INT_MASK0, (uint8_t)(source & 0xFFU), 0x0U);
            break;

        case kPF1550_IntCategoryOnkey:
            /* Enable ONKEY Press interrupts. */
            (void)PF1550_ModifyReg(handle, PF1550_ONKEY_INT_MASK0, (uint8_t)(source & 0xFFU), 0x0U);
            break;

        case kPF1550_IntCategoryTemp:
            /* Enable Die Temperature Cross interrupts. */
            (void)PF1550_ModifyReg(handle, PF1550_TEMP_INT_MASK0, (uint8_t)(source & 0xFFU), 0x0U);
            break;

        case kPF1550_IntCategoryMisc:
            /* Enable Misc. interrupts. */
            (void)PF1550_ModifyReg(handle, PF1550_MISC_INT_MASK0, (uint8_t)(source & 0xFFU), 0x0U);
            break;

        default:
            assert(false);
            break;
    }
}

void PF1550_DisableInterrupts(pf1550_handle_t *handle, pf1550_interrupt_category_t category, uint32_t source)
{
    assert(handle);

    switch (category)
    {
        case kPF1550_IntCategoryCharger:
            /* TODO: Add charger Interrupt Enable Logic here. */
            break;

        case kPF1550_IntCategorySwitch:
            /* Disable Switch low side current limit interrupts. */
            (void)PF1550_ModifyReg(handle, PF1550_SW_INT_MASK0, 0x0U, (uint8_t)(source & 0xFFU));
            /* Disable Switch high side current limit interrupts. */
            (void)PF1550_ModifyReg(handle, PF1550_SW_INT_MASK1, 0x0U, (uint8_t)((source & 0xFF00U) >> 8U));
            /* Disable Switch DVS complete interrupts. */
            (void)PF1550_ModifyReg(handle, PF1550_SW_INT_MASK2, 0x0U, (uint8_t)((source & 0xFF0000U) >> 16U));
            break;

        case kPF1550_IntCategoryLdo:
            /* Disable LDO current limit fault interrupts. */
            (void)PF1550_ModifyReg(handle, PF1550_LDO_INT_MASK0, 0x0U, (uint8_t)(source & 0xFFU));
            break;

        case kPF1550_IntCategoryOnkey:
            /* Disable ONKEY Press interrupts. */
            (void)PF1550_ModifyReg(handle, PF1550_ONKEY_INT_MASK0, 0x0U, (uint8_t)(source & 0xFFU));
            break;

        case kPF1550_IntCategoryTemp:
            /* Disable Die Temperature Cross interrupts. */
            (void)PF1550_ModifyReg(handle, PF1550_TEMP_INT_MASK0, 0x0U, (uint8_t)(source & 0xFFU));
            break;

        case kPF1550_IntCategoryMisc:
            /* Disable Misc. interrupts. */
            (void)PF1550_ModifyReg(handle, PF1550_MISC_INT_MASK0, 0x0U, (uint8_t)(source & 0xFFU));
            break;

        default:
            assert(false);
            break;
    }
}

uint32_t PF1550_GetInterruptStatus(pf1550_handle_t *handle, pf1550_interrupt_category_t category)
{
    uint32_t status = 0x0U;
    uint8_t temp    = 0U;

    assert(handle);

    switch (category)
    {
        case kPF1550_IntCategoryCharger:
            /* Get Charger interrupt flags. */
            (void)PF1550_ReadReg(handle, PF1550_CHG_INT, &temp);
            status = temp;
            break;

        case kPF1550_IntCategorySwitch:
            /* Get Switch low side current limit interrupt flags. */
            (void)PF1550_ReadReg(handle, PF1550_SW_INT_STAT0, &temp);
            status = temp;

            /* Get Switch high side current limit interrupt flags. */
            (void)PF1550_ReadReg(handle, PF1550_SW_INT_STAT1, &temp);
            status |= (uint32_t)((uint32_t)temp << 8U);

            /* Get Switch DVS complete interrupt flags. */
            (void)PF1550_ReadReg(handle, PF1550_SW_INT_STAT2, &temp);
            status |= (uint32_t)((uint32_t)temp << 16U);
            break;

        case kPF1550_IntCategoryLdo:
            /* Get LDO current limit fault interrupt flags. */
            (void)PF1550_ReadReg(handle, PF1550_LDO_INT_STAT0, &temp);
            status = temp;
            break;

        case kPF1550_IntCategoryOnkey:
            /* Get ONKEY Press interrupt flags. */
            (void)PF1550_ReadReg(handle, PF1550_ONKEY_INT_STAT0, &temp);
            status = temp;
            break;

        case kPF1550_IntCategoryTemp:
            /* Get Die Temperature Cross interrupt flags. */
            (void)PF1550_ReadReg(handle, PF1550_TEMP_INT_STAT0, &temp);
            status = temp;
            break;

        case kPF1550_IntCategoryMisc:
            /* Get Misc. interrupt flags. */
            (void)PF1550_ReadReg(handle, PF1550_MISC_INT_STAT0, &temp);
            status = temp;
            break;

        default:
            assert(false);
            break;
    }

    return status;
}

void PF1550_ClearInterruptStatus(pf1550_handle_t *handle, pf1550_interrupt_category_t category, uint32_t source)
{
    assert(handle);

    /* interrupt status bits are w1c. */
    switch (category)
    {
        case kPF1550_IntCategoryCharger:
            /* Clear Charger interrupts. */
            (void)PF1550_WriteReg(handle, PF1550_CHG_INT, (uint8_t)(source & 0xFFU));
            break;

        case kPF1550_IntCategorySwitch:
            /* Clear Switch low side current limit interrupts. */
            (void)PF1550_WriteReg(handle, PF1550_SW_INT_STAT0, (uint8_t)(source & 0xFFU));
            /* Clear Switch high side current limit interrupts. */
            (void)PF1550_WriteReg(handle, PF1550_SW_INT_STAT1, (uint8_t)((source & 0xFF00U) >> 8U));
            /* Clear Switch DVS complete interrupts. */
            (void)PF1550_WriteReg(handle, PF1550_SW_INT_STAT2, (uint8_t)((source & 0xFF0000U) >> 16U));
            break;

        case kPF1550_IntCategoryLdo:
            /* Clear LDO current limit fault interrupts. */
            (void)PF1550_WriteReg(handle, PF1550_LDO_INT_STAT0, (uint8_t)(source & 0xFFU));
            break;

        case kPF1550_IntCategoryOnkey:
            /* Clear ONKEY Press interrupts. */
            (void)PF1550_WriteReg(handle, PF1550_ONKEY_INT_STAT0, (uint8_t)(source & 0xFFU));
            break;

        case kPF1550_IntCategoryTemp:
            /* Clear Die Temperature Cross interrupts. */
            (void)PF1550_WriteReg(handle, PF1550_TEMP_INT_STAT0, (uint8_t)(source & 0xFFU));
            break;

        case kPF1550_IntCategoryMisc:
            /* Clear Misc. interrupts. */
            (void)PF1550_WriteReg(handle, PF1550_MISC_INT_STAT0, (uint8_t)(source & 0xFFU));
            break;

        default:
            assert(false);
            break;
    }
}

void PF1550_EnableRegulator(pf1550_handle_t *handle,
                            pf1550_module_t module,
                            pf1550_operating_status_t status,
                            bool enable)
{
    uint8_t regulatorCtrlRegAddr;

    assert(handle);
    /* Regulators are only enabled in any of the System On Statues. */
    assert((kPF1550_OperatingStatusRun == status) || (kPF1550_OperatingStatusStandby == status) ||
           (kPF1550_OperatingStatusSleep == status) || (kPF1550_OperatingStatusSystemOn == status));

    /* There is no enable/disable switch for Vsnvs. */
    if (kPF1550_ModuleVsnvs == module)
    {
        return;
    }

    /* Get Regulator Control Register Address. */
    regulatorCtrlRegAddr = regulatorCtrlRegTab[module];

    switch (status)
    {
        case kPF1550_OperatingStatusRun:
            (void)PF1550_ModifyReg(handle, regulatorCtrlRegAddr, PF1550_REGULATOR_CTRL_EN_MASK,
                                   (enable ? PF1550_REGULATOR_CTRL_EN_MASK : 0x0U));
            break;

        case kPF1550_OperatingStatusStandby:
            (void)PF1550_ModifyReg(handle, regulatorCtrlRegAddr, PF1550_REGULATOR_CTRL_STBY_EN_MASK,
                                   (enable ? PF1550_REGULATOR_CTRL_STBY_EN_MASK : 0x0U));
            break;

        case kPF1550_OperatingStatusSleep:
            (void)PF1550_ModifyReg(handle, regulatorCtrlRegAddr, PF1550_REGULATOR_CTRL_OMODE_MASK,
                                   (enable ? PF1550_REGULATOR_CTRL_OMODE_MASK : 0x0U));
            break;

        case kPF1550_OperatingStatusSystemOn:
            (void)PF1550_ModifyReg(handle, regulatorCtrlRegAddr, PF1550_REGULATOR_CTRL_SYSON_EN_MASK,
                                   (enable ? PF1550_REGULATOR_CTRL_SYSON_EN_MASK : 0x0U));
            break;

        default:
            assert(false);
            break;
    }
}

bool PF1550_IsRegulatorEnabled(pf1550_handle_t *handle, pf1550_module_t module, pf1550_operating_status_t status)
{
    bool result;
    uint8_t regulatorCtrlRegAddr;
    uint8_t regulatorCtrlRegContent = 0U;

    assert(handle);
    /* Regulators are only enabled in any of the System On Statues. */
    assert((kPF1550_OperatingStatusRun == status) || (kPF1550_OperatingStatusStandby == status) ||
           (kPF1550_OperatingStatusSleep == status) || (kPF1550_OperatingStatusSystemOn == status));

    /* There is no enable/disable switch for Vsnvs. */
    if (kPF1550_ModuleVsnvs == module)
    {
        result = true;
    }
    else
    {
        /* Get Regulator Control Register Content. */
        regulatorCtrlRegAddr = regulatorCtrlRegTab[module];
        (void)PF1550_ReadReg(handle, regulatorCtrlRegAddr, &regulatorCtrlRegContent);

        switch (status)
        {
            case kPF1550_OperatingStatusRun:
                result = ((regulatorCtrlRegContent & PF1550_REGULATOR_CTRL_EN_MASK) != 0U) ? true : false;
                break;

            case kPF1550_OperatingStatusStandby:
                result = ((regulatorCtrlRegContent & PF1550_REGULATOR_CTRL_STBY_EN_MASK) != 0U) ? true : false;
                break;

            case kPF1550_OperatingStatusSleep:
                result = ((regulatorCtrlRegContent & PF1550_REGULATOR_CTRL_OMODE_MASK) != 0U) ? true : false;
                break;

            case kPF1550_OperatingStatusSystemOn:
                result = ((regulatorCtrlRegContent & PF1550_REGULATOR_CTRL_SYSON_EN_MASK) ==
                          PF1550_REGULATOR_CTRL_SYSON_EN_MASK) ?
                             true :
                             false;
                break;

            default:
                result = false;
                break;
        }
    }

    return result;
}

void PF1550_SetRegulatorOutputVoltage(pf1550_handle_t *handle,
                                      pf1550_module_t module,
                                      pf1550_operating_status_t status,
                                      uint32_t voltage)
{
    uint8_t regulatorVoltRegAddr;
    uint8_t regulatorVoltRegContent;

    assert(handle);
    /* Regulators are only enabled in any of the System On Statues. */
    assert((kPF1550_OperatingStatusRun == status) || (kPF1550_OperatingStatusStandby == status) ||
           (kPF1550_OperatingStatusSleep == status) || (kPF1550_OperatingStatusSystemOn == status));

    /* Return directly if regulator does not support DVS feature. */
    if (PF1550_IsRegulatorSupportDvs(handle, module))
    {
        /* Get Regulator Output Set Point. */
        regulatorVoltRegAddr    = regulatorVoltRegTab[module];
        regulatorVoltRegContent = PF1550_GetRegulatorSetPoint(handle, module, voltage);

        /* There is only one regulator output voltage control register for LDO.
           So regulator output set for any operating status to LDO will affect
           all operating status. */
        if ((kPF1550_ModuleLdo1 == module) || (kPF1550_ModuleLdo2 == module) || (kPF1550_ModuleLdo3 == module))
        {
            (void)PF1550_WriteReg(handle, regulatorVoltRegAddr, regulatorVoltRegContent);
        }
        else
        {
            switch (status)
            {
                case kPF1550_OperatingStatusRun:
                    (void)PF1550_WriteReg(handle, regulatorVoltRegAddr, regulatorVoltRegContent);
                    break;

                case kPF1550_OperatingStatusStandby:
                    (void)PF1550_WriteReg(handle, regulatorVoltRegAddr + (PF1550_SW1_STBY_VOLT - PF1550_SW1_VOLT),
                                          regulatorVoltRegContent);
                    break;

                case kPF1550_OperatingStatusSleep:
                    (void)PF1550_WriteReg(handle, regulatorVoltRegAddr + (PF1550_SW1_SLP_VOLT - PF1550_SW1_VOLT),
                                          regulatorVoltRegContent);
                    break;

                case kPF1550_OperatingStatusSystemOn:
                    (void)PF1550_WriteReg(handle, regulatorVoltRegAddr, regulatorVoltRegContent);
                    (void)PF1550_WriteReg(handle, regulatorVoltRegAddr + (PF1550_SW1_STBY_VOLT - PF1550_SW1_VOLT),
                                          regulatorVoltRegContent);
                    (void)PF1550_WriteReg(handle, regulatorVoltRegAddr + (PF1550_SW1_SLP_VOLT - PF1550_SW1_VOLT),
                                          regulatorVoltRegContent);
                    break;

                default:
                    assert(false);
                    break;
            }
        }
    }
}

uint32_t PF1550_GetRegulatorOutputVoltage(pf1550_handle_t *handle,
                                          pf1550_module_t module,
                                          pf1550_operating_status_t status)
{
    uint8_t regulatorVoltRegAddr;
    uint8_t regulatorVoltRegContent = 0U;
    uint32_t voltage                = 0U;

    assert(handle);
    /* Regulators are only enabled in any of the System On Statues. */
    assert((kPF1550_OperatingStatusRun == status) || (kPF1550_OperatingStatusStandby == status) ||
           (kPF1550_OperatingStatusSleep == status) || (kPF1550_OperatingStatusSystemOn == status));

    switch (module)
    {
        /* Get LDO output voltage. */
        case kPF1550_ModuleLdo1:
        case kPF1550_ModuleLdo2:
        case kPF1550_ModuleLdo3:
            /* Get Regulator Voltage Regulator. */
            regulatorVoltRegAddr = regulatorVoltRegTab[module];
            (void)PF1550_ReadReg(handle, regulatorVoltRegAddr, &regulatorVoltRegContent);
            voltage = PF1550_GetRegulatorOutputVolt(handle, module, regulatorVoltRegContent);
            break;

        /* Get Switch output voltage by operating status. */
        case kPF1550_ModuleSwitch1:
        case kPF1550_ModuleSwitch2:
        case kPF1550_ModuleSwitch3:
            /* Get Regulator Voltage Regulator. */
            regulatorVoltRegAddr = regulatorVoltRegTab[module];
            switch (status)
            {
                case kPF1550_OperatingStatusRun:
                    (void)PF1550_ReadReg(handle, regulatorVoltRegAddr, &regulatorVoltRegContent);
                    voltage = PF1550_GetRegulatorOutputVolt(handle, module, regulatorVoltRegContent);
                    break;

                case kPF1550_OperatingStatusStandby:
                    (void)PF1550_ReadReg(handle, regulatorVoltRegAddr + (PF1550_SW1_STBY_VOLT - PF1550_SW1_VOLT),
                                         &regulatorVoltRegContent);
                    voltage = PF1550_GetRegulatorOutputVolt(handle, module, regulatorVoltRegContent);
                    break;

                case kPF1550_OperatingStatusSleep:
                    (void)PF1550_ReadReg(handle, regulatorVoltRegAddr + (PF1550_SW1_SLP_VOLT - PF1550_SW1_VOLT),
                                         &regulatorVoltRegContent);
                    voltage = PF1550_GetRegulatorOutputVolt(handle, module, regulatorVoltRegContent);
                    break;

                default:
                    voltage = 0U;
                    break;
            }
            break;

        case kPF1550_ModuleVsnvs:
            voltage = PF1550_VSNVS_OUTPUT_VOLTAGE;
            break;

        /* Vref DDR = Vref DDR In / 2. */
        case kPF1550_ModuleVrefDdr:
        default:
            voltage = 0U;
            break;
    }

    return voltage;
}

void PF1550_SetSwitchAttribute(pf1550_handle_t *handle,
                               pf1550_module_t module,
                               const pf1550_switch_attribute_t *attribute)
{
    uint8_t regulatorCtrlRegAddr;
    uint8_t temp;

    assert(handle);
    assert(attribute);
    assert((kPF1550_ModuleSwitch1 == module) || (kPF1550_ModuleSwitch2 == module) || (kPF1550_ModuleSwitch3 == module));

    /* Set Regulator Control Register. */
    regulatorCtrlRegAddr = regulatorCtrlRegTab[module];
    temp                 = ((attribute->enableLowPowerMode ? PF1550_SW_CTRL_LPWR_MASK : 0U) |
            (attribute->enableForcedPwm ? PF1550_SW_CTRL_FPWM_MASK : 0U) |
            (attribute->enableDischargeResistor ? PF1550_SW_CTRL_RDIS_EN_MASK : 0U));
    if (PF1550_IsRegulatorSupportDvs(handle, module))
    {
        temp |= (PF1550_SW_CTRL_DVSSPEED(attribute->dvsSpeed) |
                 (attribute->enableForcedPwmInDvs ? PF1550_SW_CTRL_FPWM_IN_DVS_MASK : 0U));
    }
    (void)PF1550_ModifyReg(handle, regulatorCtrlRegAddr,
                           PF1550_SW_CTRL_RDIS_EN_MASK | PF1550_SW_CTRL_FPWM_MASK | PF1550_SW_CTRL_FPWM_IN_DVS_MASK |
                               PF1550_SW_CTRL_DVSSPEED_MASK | PF1550_SW_CTRL_LPWR_MASK,
                           temp);

    /* Set Power Down Control Register. */
    (void)PF1550_WriteReg(handle, powerDownRegTab[module], (uint8_t)attribute->powerDownSequence);

    switch (module)
    {
        case kPF1550_ModuleSwitch1:
            (void)PF1550_WriteReg(handle, PF1550_SW1_CTRL1, (uint8_t)attribute->currentLimit);
            break;

        case kPF1550_ModuleSwitch2:
            (void)PF1550_WriteReg(handle, PF1550_SW2_CTRL1, (uint8_t)attribute->currentLimit);
            break;

        case kPF1550_ModuleSwitch3:
            (void)PF1550_WriteReg(handle, PF1550_SW3_CTRL1, (uint8_t)attribute->currentLimit);
            break;

        default:
            assert(false);
            break;
    }
}

void PF1550_SetLdoAttribute(pf1550_handle_t *handle, pf1550_module_t module, const pf1550_ldo_attribute_t *attribute)
{
    assert(handle);
    assert(attribute);
    assert((kPF1550_ModuleLdo1 == module) || (kPF1550_ModuleLdo2 == module) || (kPF1550_ModuleLdo3 == module));

    /* Set Power Down Control Register. */
    (void)PF1550_WriteReg(handle, powerDownRegTab[module], (uint8_t)attribute->powerDownSequence);

    /* Set LDO to load switch mode. */
    switch (module)
    {
        case kPF1550_ModuleLdo1:
            (void)PF1550_ModifyReg(handle, PF1550_LDO1_CTRL, PF1550_LDO_CTRL_LPWR_MASK | PF1550_LDO_CTRL_LS_EN_MASK,
                                   (attribute->enableLowPowerMode ? PF1550_LDO_CTRL_LPWR_MASK : 0U) |
                                       (attribute->enableLoadSwitch ? PF1550_LDO_CTRL_LS_EN_MASK : 0U));
            break;

        case kPF1550_ModuleLdo2:
            /* LDO2 does not support Load Switch Mode. */
            (void)PF1550_ModifyReg(handle, PF1550_LDO2_CTRL, PF1550_LDO_CTRL_LPWR_MASK,
                                   (attribute->enableLowPowerMode ? PF1550_LDO_CTRL_LPWR_MASK : 0U));
            break;

        case kPF1550_ModuleLdo3:
            (void)PF1550_ModifyReg(handle, PF1550_LDO3_CTRL, PF1550_LDO_CTRL_LPWR_MASK | PF1550_LDO_CTRL_LS_EN_MASK,
                                   (attribute->enableLowPowerMode ? PF1550_LDO_CTRL_LPWR_MASK : 0U) |
                                       (attribute->enableLoadSwitch ? PF1550_LDO_CTRL_LS_EN_MASK : 0U));
            break;

        default:
            assert(false);
            break;
    }
}

void PF1550_SetVrefDdrAttribute(pf1550_handle_t *handle, const pf1550_vrefddr_attribute_t *attribute)
{
    assert(handle);
    assert(attribute);

    /* Set Power Down Control Register. */
    (void)PF1550_WriteReg(handle, powerDownRegTab[kPF1550_ModuleVrefDdr], (uint8_t)attribute->powerDownSequence);
}

void PF1550_SetVsnvsAttribute(pf1550_handle_t *handle, const pf1550_vsnvs_attribute_t *attribute)
{
    assert(handle);
    assert(attribute);

    /* Set Coin Cell Control Register. */
    (void)PF1550_WriteReg(handle, PF1550_COINCELL_CONTROL,
                          (uint8_t)attribute->coinCellChargingVoltage |
                              (attribute->enableCoinCellCharger ? PF1550_COINCELL_CONTROL_COINCHEN_MASK : 0U));

    /* Set Vsnvs Control Register. */
    (void)PF1550_ModifyReg(handle, PF1550_VSNVS_CTRL, PF1550_VSNVS_CTRL_LIBGDIS_MASK,
                           attribute->enableLocalBandgapInCoinCellMode ? PF1550_VSNVS_CTRL_LIBGDIS_MASK : 0U);
}

void PF1550_SetOnKeyPadAttibute(pf1550_handle_t *handle, const pf1550_onkey_attribute_t *attribute)
{
    assert(handle);
    assert(attribute);

    /* Set Power Control Register 1. */
    (void)PF1550_ModifyReg(handle, PF1550_PWRCTRL1, PF1550_PWRCTRL1_ONKEYDBNC_MASK | PF1550_PWRCTRL1_ONKEY_RST_EN_MASK,
                           (PF1550_PWRCTRL1_ONKEYDBNC(attribute->debounce) |
                            (attribute->enableTurnOffSystemViaOnkey ? PF1550_PWRCTRL1_ONKEY_RST_EN_MASK : 0U)));

    /* Set Power Control Register 0. */
    (void)PF1550_ModifyReg(handle, PF1550_PWRCTRL0, PF1550_PWRCTRL0_TGRESET_MASK,
                           (uint8_t)PF1550_PWRCTRL0_TGRESET(attribute->pushTime));
}

void PF1550_SetPwrOnPadAttibute(pf1550_handle_t *handle, const pf1550_power_on_attribute_t *attribute)
{
    assert(handle);
    assert(attribute);

    /* Set Power Control Register 1. */
    (void)PF1550_ModifyReg(
        handle, PF1550_PWRCTRL1,
        PF1550_PWRCTRL1_PWRONDBNC_MASK | PF1550_PWRCTRL1_PWRONRSTEN_MASK | PF1550_PWRCTRL1_RESTARTEN_MASK,
        ((uint8_t)attribute->debounce |
         (attribute->longPressGoToRegsDisableOrSleep ? PF1550_PWRCTRL1_PWRONRSTEN_MASK : 0U) |
         (attribute->longPressRestartToRunStauts ? PF1550_PWRCTRL1_RESTARTEN_MASK : 0U)));
}

void PF1550_SetStandbyPadAttibute(pf1550_handle_t *handle, const pf1550_standby_attribute_t *attribute)
{
    assert(handle);
    assert(attribute);

    /* Set Power Control Register 0. */
    (void)PF1550_ModifyReg(
        handle, PF1550_PWRCTRL0, PF1550_PWRCTRL0_STANDBYDLY_MASK | PF1550_PWRCTRL0_STANDBYINV_MASK,
        (uint8_t)attribute->standbyDelay | (uint8_t)PF1550_PWRCTRL0_STANDBYINV(attribute->standbyPolarity));
}

pf1550_operating_status_t PF1550_GetOperatingStatus(pf1550_handle_t *handle)
{
    uint8_t operatingStatus = 0U;

    assert(handle);

    (void)PF1550_ReadReg(handle, PF1550_STATE_INFO, &operatingStatus);

    return (pf1550_operating_status_t)((uint8_t)(operatingStatus & 0x7U));
}

bool PF1550_IsRegulatorSupportDvs(pf1550_handle_t *handle, pf1550_module_t module)
{
    uint8_t registerContent = 0U;
    bool result;

    assert(handle);

    switch (module)
    {
        /* Switch1 DVS is enabled/disabled in OPT Configuration. */
        case kPF1550_ModuleSwitch1:
            (void)PF1550_ReadOtp(handle, PF1550_OTP_SW1_SW2, &registerContent);
            result = ((PF1550_OTP_SW1_SW2_OTP_SW1_DVS_ENB_MASK & registerContent) != 0U) ? false : true;
            break;

        /* Switch2 DVS is enabled/disabled in OPT Configuration. */
        case kPF1550_ModuleSwitch2:
            (void)PF1550_ReadOtp(handle, PF1550_OTP_SW2_SW3, &registerContent);
            result = ((PF1550_OTP_SW2_SW3_OTP_SW2_DVS_ENB_MASK & registerContent) != 0U) ? false : true;
            break;

        /* LDOs always support DVS feature. */
        case kPF1550_ModuleLdo1:
        case kPF1550_ModuleLdo2:
        case kPF1550_ModuleLdo3:
            result = true;
            break;

        /* Switch3, Vsnvs and Vref DDR does not support DVS in all OPT Configuration. */
        case kPF1550_ModuleSwitch3:
        case kPF1550_ModuleVsnvs:
        case kPF1550_ModuleVrefDdr:
            result = false;
            break;

        default:
            result = false;
            break;
    }

    return result;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
