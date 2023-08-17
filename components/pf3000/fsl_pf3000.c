/*
 * Copyright 2016 Freescale Semiconductor, Inc.
 * Copyright 2016 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_pf3000.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* CONCTL bit-field. */
#define PF3000_COIN_CTRL_ENABLE_MASK (0x08U)
#define PF3000_COIN_CTRL_VOLT_MASK   (0x07U)
#define PF3000_COIN_CTRL_VOLT_SHIFT  (0U)
#define PF3000_COIN_CTRL_VOLT(x)     (((uint8_t)((uint8_t)(x) << PF3000_COIN_CTRL_VOLT_SHIFT)) & PF3000_COIN_CTRL_VOLT_MASK)
/* PWRCTL bit-field. */
#define PF3000_PWR_CTRL_REGSCCP_ENABLE_MASK (0x80U)
#define PF3000_PWR_CTRL_STANDBYINV_MASK     (0x40U)
#define PF3000_PWR_CTRL_STBYDLY_MASK        (0x30U)
#define PF3000_PWR_CTRL_STBYDLY_SHIFT       (4U)
#define PF3000_PWR_CTRL_STBYDLY(x) \
    (((uint8_t)((uint8_t)(x) << PF3000_PWR_CTRL_STBYDLY_SHIFT)) & PF3000_PWR_CTRL_STBYDLY_MASK)
#define PF3000_PWR_CTRL_PWRONDBNC_MASK  (0x0CU)
#define PF3000_PWR_CTRL_PWRONDBNC_SHIFT (2U)
#define PF3000_PWR_CTRL_PWRONDBNC(x) \
    (((uint8_t)((uint8_t)(x) << PF3000_PWR_CTRL_PWRONDBNC_SHIFT)) & PF3000_PWR_CTRL_PWRONDBNC_MASK)
#define PF3000_PWR_CTRL_PWRONRSTEN_MASK (0x02U)
#define PF3000_PWR_CTRL_RESTARTEN_MASK  (0x01U)
/* SW1XVOLT, SW1XSTBY, SW1XOFF bit-field. */
#define PF3000_SW1X_VOLT_CTRL_MASK  (0x1FU)
#define PF3000_SW1X_VOLT_CTRL_SHIFT (0U)
#define PF3000_SW1X_VOLT_CTRL(x)    (((uint8_t)((uint8_t)(x) << PF3000_SW1X_VOLT_CTRL_SHIFT)) & PF3000_SW1X_VOLT_CTRL_MASK)
/* SW2VOLT, SW2STBY, SW2OFF bit-field. */
#define PF3000_SW2_VOLT_CTRL_MASK  (0x07U)
#define PF3000_SW2_VOLT_CTRL_SHIFT (0U)
#define PF3000_SW2_VOLT_CTRL(x)    (((uint8_t)((uint8_t)(x) << PF3000_SW2_VOLT_CTRL_SHIFT)) & PF3000_SW2_VOLT_CTRL_MASK)
/* SW3VOLT, SW3STBY, SW3OFF bit-field. */
#define PF3000_SW3_VOLT_CTRL_MASK  (0x0FU)
#define PF3000_SW3_VOLT_CTRL_SHIFT (0U)
#define PF3000_SW3_VOLT_CTRL(x)    (((uint8_t)((uint8_t)(x) << PF3000_SW3_VOLT_CTRL_SHIFT)) & PF3000_SW3_VOLT_CTRL_MASK)
/* SW MODE bit-field. */
#define PF3000_SW_MODE_OFF_MASK       (0x20U)
#define PF3000_SW_MODE_SELECTOR_MASK  (0x0FU)
#define PF3000_SW_MODE_SELECTOR_SHIFT (0U)
#define PF3000_SW_MODE_SELECTOR(x) \
    (((uint8_t)((uint8_t)(x) << PF3000_SW_MODE_SELECTOR_SHIFT)) & PF3000_SW_MODE_SELECTOR_MASK)
/* SW CONFIG bit-field. */
#define PF3000_SW_CTRL_DVSSPEED_MASK   (0x40U)
#define PF3000_SW_CTRL_PHASE_MASK      (0x30U)
#define PF3000_SW_CTRL_PHASE_SHIFT     (4U)
#define PF3000_SW_CTRL_PHASE(x)        (((uint8_t)((uint8_t)(x) << PF3000_SW_CTRL_PHASE_SHIFT)) & PF3000_SW_CTRL_PHASE_MASK)
#define PF3000_SW_CTRL_FREQUENCY_MASK  (0x0CU)
#define PF3000_SW_CTRL_FREQUENCY_SHIFT (2U)
#define PF3000_SW_CTRL_FREQUENCY(x) \
    (((uint8_t)((uint8_t)(x) << PF3000_SW_CTRL_FREQUENCY_SHIFT)) & PF3000_SW_CTRL_FREQUENCY_MASK)
#define PF3000_SW_CTRL_CURRENT_LIMIT_MASK (0x01U)
/* SW_BOOST_CTRL bit-field. */
#define PF3000_SW_BST_CTRL_STANDBY_MODE_MASK  (0x60U)
#define PF3000_SW_BST_CTRL_STANDBY_MODE_SHIFT (5U)
#define PF3000_SW_BST_CTRL_STANDBY_MODE(x) \
    (((uint8_t)((uint8_t)(x) << PF3000_SW_BST_CTRL_STANDBY_MODE_SHIFT)) & PF3000_SW_BST_CTRL_STANDBY_MODE_MASK)
#define PF3000_SW_BST_CTRL_NORMAL_MODE_MASK  (0x0CU)
#define PF3000_SW_BST_CTRL_NORMAL_MODE_SHIFT (2U)
#define PF3000_SW_BST_CTRL_NORMAL_MODE(x) \
    (((uint8_t)((uint8_t)(x) << PF3000_SW_BST_CTRL_NORMAL_MODE_SHIFT)) & PF3000_SW_BST_CTRL_NORMAL_MODE_MASK)
#define PF3000_SW_BST_CTRL_VOLT_MASK  (0x03U)
#define PF3000_SW_BST_CTRL_VOLT_SHIFT (0U)
#define PF3000_SW_BST_CTRL_VOLT(x) \
    (((uint8_t)((uint8_t)(x) << PF3000_SW_BST_CTRL_VOLT_SHIFT)) & PF3000_SW_BST_CTRL_VOLT_MASK)
/* VREFDDRCTL bit-field. */
#define PF3000_VREFDDR_SUPPLY_ENABLE_MASK (0x01U)
/* VSNVSCTL bit-field. */
#define PF3000_VSNVS_VOLT_CTRL_MASK  (0x07U)
#define PF3000_VSNVS_VOLT_CTRL_SHIFT (0U)
#define PF3000_VSNVS_VOLT_CTRL(x) \
    (((uint8_t)((uint8_t)(x) << PF3000_VSNVS_VOLT_CTRL_SHIFT)) & PF3000_VSNVS_VOLT_CTRL_MASK)
#define PF3000_VSNVS_VOLT_CTRL_VALUE (0x06U)
/* VLDO CTL bit-field. */
#define PF3000_LDO_OFF_MODE_MASK       (0x80U)
#define PF3000_LDO_LOW_POWER_MODE_MASK (0x40U)
#define PF3000_LDO_STANDBY_ON_OFF_MASK (0x20U)
#define PF3000_LDO_ENABLE_MASK         (0x10U)
#define PF3000_LDO_VOLT_CTRL_MASK      (0x0FU)
#define PF3000_LDO_VOLT_CTRL_SHIFT     (0U)
#define PF3000_LDO_VOLT_CTRL(x)        (((uint8_t)((uint8_t)(x) << PF3000_LDO_VOLT_CTRL_SHIFT)) & PF3000_LDO_VOLT_CTRL_MASK)
/* VCC_SDCTL bit-field. */
#define PF3000_VCC_SD_VOLT_CTRL_MASK  (0x03U)
#define PF3000_VCC_SD_VOLT_CTRL_SHIFT (0U)
#define PF3000_VCC_SD_VOLT_CTRL(x) \
    (((uint8_t)((uint8_t)(x) << PF3000_VCC_SD_VOLT_CTRL_SHIFT)) & PF3000_VCC_SD_VOLT_CTRL_MASK)
/* V33 bit-field. */
#define PF3000_V33_VOLT_CTRL_MASK  (0x03U)
#define PF3000_V33_VOLT_CTRL_SHIFT (0U)
#define PF3000_V33_VOLT_CTRL(x)    (((uint8_t)((uint8_t)(x) << PF3000_V33_VOLT_CTRL_SHIFT)) & PF3000_V33_VOLT_CTRL_MASK)
/* Page Selection bit-field. */
#define PF3000_PAGE_SELECTION_MASK  (0x0FU)
#define PF3000_PAGE_SELECTION_SHIFT (0U)
#define PF3000_PAGE_SELECTION(x)    (((uint8_t)((uint8_t)(x) << PF3000_PAGE_SELECTION_SHIFT)) & PF3000_PAGE_SELECTION_MASK)

/* Regulator Voltage Control Helper Macros. */
#define PF3000_SW1A_SET_POINT_MAX_NUM      (31U)
#define PF3000_SW1A_OUTPUT_LIMIT_LOW_DVS   (700000U)
#define PF3000_SW1A_OUTPUT_STEP_DVS        (25000U)
#define PF3000_SW1B_SET_POINT_MAX_NUM      (31U)
#define PF3000_SW1B_OUTPUT_LIMIT_LOW_DVS   (700000U)
#define PF3000_SW1B_OUTPUT_STEP_DVS        (25000U)
#define PF3000_SW2_SET_POINT_MAX_NUM       (7U)
#define PF3000_SW2_OUTPUT_LIMIT_LOW_DVS    (1500000U)
#define PF3000_SW2_OUTPUT_STEP_DVS         (50000U)
#define PF3000_SW3_SET_POINT_MAX_NUM       (15U)
#define PF3000_SW3_OUTPUT_LIMIT_LOW_DVS    (900000U)
#define PF3000_SW3_OUTPUT_STEP_DVS         (50000U)
#define PF3000_SW_BST_SET_POINT_MAX_NUM    (3U)
#define PF3000_SW_BST_OUTPUT_LIMIT_LOW_DVS (5000000U)
#define PF3000_SW_BST_OUTPUT_STEP_DVS      (50000U)
#define PF3000_LDOX_SET_POINT_MAX_NUM      (15U)
#define PF3000_LDOX_OUTPUT_LIMIT_LOW_DVS   (1800000U)
#define PF3000_LDOX_OUTPUT_STEP_DVS        (100000U)
#define PF3000_LDOY_SET_POINT_MAX_NUM      (15U)
#define PF3000_LDOY_OUTPUT_LIMIT_LOW_DVS   (800000U)
#define PF3000_LDOY_OUTPUT_STEP_DVS        (50000U)
#define PF3000_VCC_SD_SET_POINT_MAX_NUM    (3U)
#define PF3000_VCC_SD_OUTPUT_LIMIT_LOW_DVS (2850000U)
#define PF3000_VCC_SD_OUTPUT_STEP_DVS      (150000U)
#define PF3000_V33_SET_POINT_MAX_NUM       (3U)
#define PF3000_V33_OUTPUT_LIMIT_LOW_DVS    (2850000U)
#define PF3000_V33_OUTPUT_STEP_DVS         (150000U)
#define PF3000_VSNVS_OUTPUT_VOLTAGE        (3000000U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static const uint8_t regulatorCtrlRegTab[] = {
    PF3000_SW1A_CONF,  PF3000_SW1B_CONF,  PF3000_SW2_CONF,    PF3000_SW3_CONF,   PF3000_SWBST_CTRL,
    PF3000_VLDO1_CTRL, PF3000_VLDO2_CTRL, PF3000_VLDO3_CTRL,  PF3000_VLDO4_CTRL, PF3000_VCC_SD_CTRL,
    PF3000_V33_CTRL,   PF3000_VSNVS_CTRL, PF3000_VREFDDR_CTRL};

static const uint8_t switchVoltRegTab[][3] = {
    {PF3000_SW1A_VOLT, PF3000_SW1A_STBY, PF3000_SW1A_OFF},
    {PF3000_SW1B_VOLT, PF3000_SW1B_STBY, PF3000_SW1B_OFF},
    {PF3000_SW2_VOLT, PF3000_SW2_STBY, PF3000_SW2_OFF},
    {PF3000_SW3_VOLT, PF3000_SW3_STBY, PF3000_SW3_OFF},
};

/*******************************************************************************
 * Code
 ******************************************************************************/
static bool PF3000_ReadOtp(pf3000_handle_t *handle, uint8_t page, uint8_t reg, uint8_t *val)
{
    bool result = false;

    assert(handle);
    assert(val);
    assert((page == 0x01U) || (page == 0x02U));

    result = PF3000_WriteReg(handle, PF3000_PAGE_REGISTER, PF3000_PAGE_SELECTION(page));
    if (true == result)
    {
        result = PF3000_ReadReg(handle, reg, val);
    }

    return result;
}

static uint8_t PF3000_GetRegulatorSetPoint(pf3000_handle_t *handle, pf3000_module_t module, uint32_t voltage)
{
    uint8_t regulatorSetPoint = 0U;
    uint32_t index;

    assert(handle);
    assert((kPF3000_ModuleSwitch1A == module) || (kPF3000_ModuleSwitch1B == module) ||
           (kPF3000_ModuleSwitch2 == module) || (kPF3000_ModuleSwitch3 == module) ||
           (kPF3000_ModuleSwitchBoost == module) || (kPF3000_ModuleLdo1 == module) || (kPF3000_ModuleLdo2 == module) ||
           (kPF3000_ModuleLdo3 == module) || (kPF3000_ModuleLdo4 == module) || (kPF3000_ModuleVcc_sd == module) ||
           (kPF3000_ModuleV33 == module));

    switch (module)
    {
        /* Process Switch 1A. */
        case kPF3000_ModuleSwitch1A:
        /* Process Switch 1B. */
        case kPF3000_ModuleSwitch1B:
            if ((handle->switch1Mode == kPF3000_SW1SinglePhase) ||
                ((handle->switch1Mode == kPF3000_SW1IndependentMode) && (module == kPF3000_ModuleSwitch1A)))
            {
                /* Find the first Vset_point <= voltage */
                if (3300000U <= voltage)
                {
                    index = PF3000_SW1A_SET_POINT_MAX_NUM;
                }
                else if (1800000U <= voltage)
                {
                    index = PF3000_SW1A_SET_POINT_MAX_NUM - 1U;
                }
                else
                {
                    for (index = PF3000_SW1A_SET_POINT_MAX_NUM - 2U; index > 0U; index--)
                    {
                        if ((PF3000_SW1A_OUTPUT_LIMIT_LOW_DVS + (PF3000_SW1A_OUTPUT_STEP_DVS * index)) <= voltage)
                        {
                            break;
                        }
                    }
                }
            }
            else if ((handle->switch1Mode == kPF3000_SW1IndependentMode) && (module == kPF3000_ModuleSwitch1B))
            {
                /* Find the first Vset_point >= voltage */
                for (index = PF3000_SW1B_SET_POINT_MAX_NUM; index > 0U; index--)
                {
                    if ((PF3000_SW1B_OUTPUT_LIMIT_LOW_DVS + (PF3000_SW1B_OUTPUT_STEP_DVS * index)) <= voltage)
                    {
                        break;
                    }
                }
            }
            else
            {
                ;
            }
            break;

        /* Process Switch 2. */
        case kPF3000_ModuleSwitch2:
            /* OTP_SW2_HI= 0, SW2 is in low output voltage range */
            if (handle->switch2Range == kPF3000_SW2LowVoltRange)
            {
                for (index = PF3000_SW2_SET_POINT_MAX_NUM; index > 0U; index--)
                {
                    if ((PF3000_SW2_OUTPUT_LIMIT_LOW_DVS + (PF3000_SW2_OUTPUT_STEP_DVS * index)) <= voltage)
                    {
                        break;
                    }
                }
            }
            /* OTP_SW2_HI= 1, SW2 is in high output voltage range */
            else
            {
                if (3300000 <= voltage)
                {
                    index = 0x7U;
                }
                else if (3200000 <= voltage)
                {
                    index = 0x6U;
                }
                else if (3150000 <= voltage)
                {
                    index = 0x5U;
                }
                else if (3100000 <= voltage)
                {
                    index = 0x4U;
                }
                else if (3000000 <= voltage)
                {
                    index = 0x3U;
                }
                else if (2850000 <= voltage)
                {
                    index = 0x2U;
                }
                else if (2800000 <= voltage)
                {
                    index = 0x1U;
                }
                else
                {
                    index = 0x0U;
                }
            }
            break;

        /* Process Switch 3. */
        case kPF3000_ModuleSwitch3:
            for (index = PF3000_SW3_SET_POINT_MAX_NUM; index > 0U; index--)
            {
                if ((PF3000_SW3_OUTPUT_LIMIT_LOW_DVS + (PF3000_SW3_OUTPUT_STEP_DVS * index)) <= voltage)
                {
                    break;
                }
            }
            break;

        /* Process Switch Boost. */
        case kPF3000_ModuleSwitchBoost:
            for (index = PF3000_SW_BST_SET_POINT_MAX_NUM; index > 0U; index--)
            {
                if ((PF3000_SW_BST_OUTPUT_LIMIT_LOW_DVS + (PF3000_SW_BST_OUTPUT_STEP_DVS * index)) <= voltage)
                {
                    break;
                }
            }
            break;

        /* Process LDO X, including LDO1, LDO3, LDO4. */
        case kPF3000_ModuleLdo1:
        case kPF3000_ModuleLdo3:
        case kPF3000_ModuleLdo4:
            for (index = PF3000_LDOX_SET_POINT_MAX_NUM; index > 0U; index--)
            {
                if ((PF3000_LDOX_OUTPUT_LIMIT_LOW_DVS + (PF3000_LDOX_OUTPUT_STEP_DVS * index)) <= voltage)
                {
                    break;
                }
            }
            break;

        /* Process LDO Y, including LDO2. */
        case kPF3000_ModuleLdo2:
            for (index = PF3000_LDOY_SET_POINT_MAX_NUM; index > 0U; index--)
            {
                if ((PF3000_LDOY_OUTPUT_LIMIT_LOW_DVS + (PF3000_LDOY_OUTPUT_STEP_DVS * index)) <= voltage)
                {
                    break;
                }
            }
            break;

        /* Process Vcc_sd. */
        case kPF3000_ModuleVcc_sd:
            /* VSD_VSEL= 0. */
            if (handle->vccsdVsel == 0U)
            {
                for (index = PF3000_VCC_SD_SET_POINT_MAX_NUM; index > 0U; index--)
                {
                    if ((PF3000_VCC_SD_OUTPUT_LIMIT_LOW_DVS + (PF3000_VCC_SD_OUTPUT_STEP_DVS * index)) <= voltage)
                    {
                        break;
                    }
                }
            }
            /* VSD_VSEL= 1. */
            else
            {
                if (1850000U <= voltage)
                {
                    index = 0x3U;
                }
                else
                {
                    index = 0x0U;
                }
            }
            break;

        /* Process Vcc_sd. */
        case kPF3000_ModuleV33:
            for (index = PF3000_V33_SET_POINT_MAX_NUM; index > 0U; index--)
            {
                if ((PF3000_V33_OUTPUT_LIMIT_LOW_DVS + (PF3000_V33_OUTPUT_STEP_DVS * index)) <= voltage)
                {
                    break;
                }
            }
            break;

        default:
            index = 0U;
            break;
    }

    /* Assin index to  regulatorSetPoint*/
    regulatorSetPoint = index;

    return regulatorSetPoint;
}

static uint32_t PF3000_GetRegulatorOutputVolt(pf3000_handle_t *handle, pf3000_module_t module, uint8_t voltRegContent)
{
    uint32_t voltage = 0U;

    assert(handle);
    assert((kPF3000_ModuleSwitch1A == module) || (kPF3000_ModuleSwitch1B == module) ||
           (kPF3000_ModuleSwitch2 == module) || (kPF3000_ModuleSwitch3 == module) ||
           (kPF3000_ModuleSwitchBoost == module) || (kPF3000_ModuleLdo1 == module) || (kPF3000_ModuleLdo2 == module) ||
           (kPF3000_ModuleLdo3 == module) || (kPF3000_ModuleLdo4 == module) || (kPF3000_ModuleVcc_sd == module) ||
           (kPF3000_ModuleV33 == module) || (kPF3000_ModuleVsnvs == module));

    switch (module)
    {
        /* Process Switch 1A. */
        case kPF3000_ModuleSwitch1A:
        /* Process Switch 1B. */
        case kPF3000_ModuleSwitch1B:
            if ((handle->switch1Mode == kPF3000_SW1SinglePhase) ||
                ((handle->switch1Mode == kPF3000_SW1IndependentMode) && (module == kPF3000_ModuleSwitch1A)))
            {
                if (voltRegContent <= (PF3000_SW1A_SET_POINT_MAX_NUM - 2))
                {
                    voltage = PF3000_SW1A_OUTPUT_LIMIT_LOW_DVS + PF3000_SW1A_OUTPUT_STEP_DVS * voltRegContent;
                }
                else if (voltRegContent == (PF3000_SW1A_SET_POINT_MAX_NUM - 1))
                {
                    voltage = 1800000U;
                }
                else if (voltRegContent == (PF3000_SW1A_SET_POINT_MAX_NUM))
                {
                    voltage = 3300000U;
                }
                else
                {
                    ;
                }
            }
            else if ((handle->switch1Mode == kPF3000_SW1IndependentMode) && (module == kPF3000_ModuleSwitch1B))
            {
                voltage = PF3000_SW1B_OUTPUT_LIMIT_LOW_DVS + PF3000_SW1B_OUTPUT_STEP_DVS * voltRegContent;
            }
            else
            {
                ;
            }
            break;

        /* Process Switch 2. */
        case kPF3000_ModuleSwitch2:
            /* OTP_SW2_HI= 0, SW2 is in low output voltage range */
            if (handle->switch2Range == kPF3000_SW2LowVoltRange)
            {
                voltage = PF3000_SW3_OUTPUT_LIMIT_LOW_DVS + PF3000_SW3_OUTPUT_STEP_DVS * voltRegContent;
            }
            /* OTP_SW2_HI= 1, SW2 is in high output voltage range */
            else
            {
                switch (voltRegContent)
                {
                    case 0x0U:
                        voltage = 2500000U;
                        break;
                    case 0x1U:
                        voltage = 2800000U;
                        break;
                    case 0x2U:
                        voltage = 2850000U;
                        break;
                    case 0x3U:
                        voltage = 3000000U;
                        break;
                    case 0x4U:
                        voltage = 3100000U;
                        break;
                    case 0x5U:
                        voltage = 3150000U;
                        break;
                    case 0x6U:
                        voltage = 3200000U;
                        break;
                    case 0x7U:
                        voltage = 3300000U;
                        break;
                    default:
                        voltage = 0U;
                        break;
                }
            }
            break;

        /* Process Switch 3. */
        case kPF3000_ModuleSwitch3:
            voltage = PF3000_SW3_OUTPUT_LIMIT_LOW_DVS + PF3000_SW3_OUTPUT_STEP_DVS * voltRegContent;
            break;

        /* Process Switch Boost. */
        case kPF3000_ModuleSwitchBoost:
            voltage = PF3000_SW_BST_OUTPUT_LIMIT_LOW_DVS + PF3000_SW_BST_OUTPUT_STEP_DVS * voltRegContent;
            break;

        /* Process LDO X, including LDO1, LDO3, LDO4. */
        case kPF3000_ModuleLdo1:
        case kPF3000_ModuleLdo3:
        case kPF3000_ModuleLdo4:
            voltage = PF3000_LDOX_OUTPUT_LIMIT_LOW_DVS + PF3000_LDOX_OUTPUT_STEP_DVS * voltRegContent;
            break;

        /* Process LDO Y, including LDO2. */
        case kPF3000_ModuleLdo2:
            voltage = PF3000_LDOY_OUTPUT_LIMIT_LOW_DVS + PF3000_LDOY_OUTPUT_STEP_DVS * voltRegContent;
            break;

        /* Process Vcc_sd. */
        case kPF3000_ModuleVcc_sd:
            /* VSD_VSEL= 0. */
            if (handle->vccsdVsel == 0U)
            {
                voltage = PF3000_VCC_SD_OUTPUT_LIMIT_LOW_DVS + PF3000_VCC_SD_OUTPUT_STEP_DVS * voltRegContent;
            }
            /* VSD_VSEL= 1. */
            else
            {
                if (voltRegContent == 3U)
                {
                    voltage = 1850000U;
                }
                else
                {
                    voltage = 1800000U;
                }
            }
            break;

        /* Process Vcc_sd. */
        case kPF3000_ModuleV33:
            voltage = PF3000_V33_OUTPUT_LIMIT_LOW_DVS + PF3000_V33_OUTPUT_STEP_DVS * voltRegContent;
            break;

        /* Process Vsnvs. It's fixed in 3.0V, can't be changed. */
        case kPF3000_ModuleVsnvs:
            assert(voltRegContent == PF3000_VSNVS_VOLT_CTRL_VALUE);
            voltage = PF3000_VSNVS_OUTPUT_VOLTAGE;
            break;

        default:
            break;
    }

    return voltage;
}

void PF3000_GetDefaultConfig(pf3000_config_t *config)
{
    assert(config);

    /* Set callback function to NULL Pointer. */
    config->I2C_SendFunc    = NULL;
    config->I2C_ReceiveFunc = NULL;

    /* Set Default Slave Address. */
    config->slaveAddress = PF3000_DEFAULT_I2C_ADDR;
    /* Short-circuit protection enabled. */
    config->enableRegSCP = true;
    /* VSD_VSEL. */
    config->vccsdVsel = 0U;
}

void PF3000_Init(pf3000_handle_t *handle, const pf3000_config_t *config)
{
    uint8_t temp;
    uint8_t regValue;

    assert(handle);
    assert(config);

    /* Initialize Callback functions. */
    handle->I2C_SendFunc    = config->I2C_SendFunc;
    handle->I2C_ReceiveFunc = config->I2C_ReceiveFunc;
    /* Set Slave Address. */
    handle->slaveAddress = config->slaveAddress;

    /* Modify Switch Mode Register Value. */
    temp = (config->enableRegSCP ? PF3000_PWR_CTRL_REGSCCP_ENABLE_MASK : 0U);

    PF3000_ModifyReg(handle, PF3000_PWR_CTRL, PF3000_PWR_CTRL_REGSCCP_ENABLE_MASK, temp);

    /* VSD_VSEL. */
    handle->vccsdVsel = config->vccsdVsel;

    /* Read the register value of OTP SW1x CONFIG */
    PF3000_ReadOtp(handle, 0x01U, PF3000_OTP_SW1x_CONFIG, &regValue);
    /* SW1A SW1B mode selection. */
    handle->switch1Mode = (pf3000_switch1_mode_t)((regValue & 0x0CU) >> 2U);

    assert((handle->switch1Mode == kPF3000_SW1SinglePhase) || (handle->switch1Mode == kPF3000_SW1IndependentMode));

    /* Read the register value of OTP SW2 VOLT */
    PF3000_ReadOtp(handle, 0x01U, PF3000_OTP_SW2_VOLT, &regValue);
    /* SW2 voltage range. */
    handle->switch2Range = (regValue & 0x08U) ? (kPF3000_SW2HighVoltRange) : (kPF3000_SW2LowVoltRange);
}

bool PF3000_WriteReg(pf3000_handle_t *handle, uint8_t reg, uint8_t val)
{
    assert(handle);
    assert(handle->I2C_SendFunc);

    return handle->I2C_SendFunc(handle->slaveAddress, reg, 1U, &val, 1U);
}

bool PF3000_ReadReg(pf3000_handle_t *handle, uint8_t reg, uint8_t *val)
{
    assert(handle);
    assert(handle->I2C_ReceiveFunc);
    assert(val);

    return handle->I2C_ReceiveFunc(handle->slaveAddress, reg, 1U, val, 1U);
}

bool PF3000_ModifyReg(pf3000_handle_t *handle, uint8_t reg, uint8_t mask, uint8_t val)
{
    bool result = false;
    uint8_t regValue;

    assert(handle);

    /* Read back the register content. */
    result = PF3000_ReadReg(handle, reg, &regValue);
    if (true == result)
    {
        /* Modify the bit-fields you want to change. */
        regValue &= (uint8_t)~mask;
        regValue |= val;

        /* Write back the content to the registers. */
        result = PF3000_WriteReg(handle, reg, regValue);
    }

    return result;
}

bool PF3000_DumpReg(pf3000_handle_t *handle, uint8_t page, uint8_t reg, uint8_t *buffer, uint8_t size)
{
    bool result = true;
    uint8_t i;

    assert(handle);
    assert(buffer);
    assert((page == 0x00U) || (page == 0x01U) || (page == 0x02U));

    PF3000_WriteReg(handle, PF3000_PAGE_REGISTER, PF3000_PAGE_SELECTION(page));

    /* It seems that PF3000 only supports single-byte I2C transactions
       for read and write. */
    for (i = 0; i < size; i++)
    {
        if (false == PF3000_ReadReg(handle, reg++, buffer++))
        {
            result = false;
        }
    }

    return result;
}

void PF3000_EnableInterrupts(pf3000_handle_t *handle, uint32_t source)
{
    assert(handle);

    /* Enable INTSTAT0 interrupts. */
    PF3000_ModifyReg(handle, PF3000_SW_INT_MASK0, (source & 0xFFU), 0x0U);
    /* Enable INTSTAT1 interrupts. */
    PF3000_ModifyReg(handle, PF3000_SW_INT_MASK1, ((source & 0xFF00U) >> 8U), 0x0U);
    /* Enable INTSTAT3 interrupts. */
    PF3000_ModifyReg(handle, PF3000_SW_INT_MASK3, ((source & 0xFF0000U) >> 16U), 0x0U);
    /* Enable INTSTAT4 interrupts. */
    PF3000_ModifyReg(handle, PF3000_SW_INT_MASK4, ((source & 0xFF000000U) >> 24), 0x0U);
}

void PF3000_DisableInterrupts(pf3000_handle_t *handle, uint32_t source)
{
    assert(handle);

    /* Enable INTSTAT0 interrupts. */
    PF3000_ModifyReg(handle, PF3000_SW_INT_MASK0, 0x0U, (source & 0xFFU));
    /* Enable INTSTAT1 interrupts. */
    PF3000_ModifyReg(handle, PF3000_SW_INT_MASK1, 0x0U, ((source & 0xFF00U) >> 8U));
    /* Enable INTSTAT3 interrupts. */
    PF3000_ModifyReg(handle, PF3000_SW_INT_MASK3, 0x0U, ((source & 0xFF0000U) >> 16U));
    /* Enable INTSTAT4 interrupts. */
    PF3000_ModifyReg(handle, PF3000_SW_INT_MASK4, 0x0U, ((source & 0xFF000000U) >> 24));
}

uint32_t PF3000_GetInterruptStatus(pf3000_handle_t *handle)
{
    uint32_t status = 0x0U;
    uint8_t temp;

    assert(handle);

    /* Get INTSTAT0 interrupts flag. */
    PF3000_ReadReg(handle, PF3000_SW_INT_STAT0, &temp);
    status = temp;

    /* Get INTSTAT1 interrupts flag. */
    PF3000_ReadReg(handle, PF3000_SW_INT_STAT1, &temp);
    status |= (uint32_t)((uint32_t)temp << 8U);

    /* Get INTSTAT3 interrupts flag. */
    PF3000_ReadReg(handle, PF3000_SW_INT_STAT3, &temp);
    status |= (uint32_t)((uint32_t)temp << 16U);

    /* Get INTSTAT4 interrupts flag. */
    PF3000_ReadReg(handle, PF3000_SW_INT_STAT4, &temp);
    status |= (uint32_t)((uint32_t)temp << 24U);

    return status;
}

void PF3000_ClearInterruptStatus(pf3000_handle_t *handle, uint32_t source)
{
    assert(handle);

    /* Clear INTSTAT0 interrupts flag. */
    PF3000_WriteReg(handle, PF3000_SW_INT_STAT0, (source & 0xFFU));
    /* Clear INTSTAT1 interrupts flag. */
    PF3000_WriteReg(handle, PF3000_SW_INT_STAT1, ((source & 0xFF00U) >> 8U));
    /* Clear INTSTAT3 interrupts flag. */
    PF3000_WriteReg(handle, PF3000_SW_INT_STAT3, ((source & 0xFF0000U) >> 16U));
    /* Clear INTSTAT4 interrupts flag. */
    PF3000_WriteReg(handle, PF3000_SW_INT_STAT4, ((source & 0xFF000000U) >> 24U));
}

void PF3000_SetRegulatorOutputVoltage(pf3000_handle_t *handle,
                                      pf3000_module_t module,
                                      pf3000_operating_status_t status,
                                      uint32_t voltage)
{
    uint8_t regulatorVoltRegAddr;
    uint8_t regulatorVoltRegContent;
    uint8_t regulatorVoltRegMask;

    assert(handle);
    assert((kPF3000_ModuleSwitch1A == module) || (kPF3000_ModuleSwitch1B == module) ||
           (kPF3000_ModuleSwitch2 == module) || (kPF3000_ModuleSwitch3 == module) ||
           (kPF3000_ModuleSwitchBoost == module) || (kPF3000_ModuleLdo1 == module) || (kPF3000_ModuleLdo2 == module) ||
           (kPF3000_ModuleLdo3 == module) || (kPF3000_ModuleLdo4 == module) || (kPF3000_ModuleVcc_sd == module) ||
           (kPF3000_ModuleV33 == module));

    assert((kPF3000_OperatingStatusSystemOn == status) || (kPF3000_OperatingStatusStandby == status) ||
           (kPF3000_OperatingStatusOff == status));

    /* Get Register Value. */
    regulatorVoltRegContent = PF3000_GetRegulatorSetPoint(handle, module, voltage);

    switch (module)
    {
        /* Process SW1A, SW1B. */
        case kPF3000_ModuleSwitch1A:
        case kPF3000_ModuleSwitch1B:
            regulatorVoltRegAddr    = switchVoltRegTab[module][status];
            regulatorVoltRegContent = PF3000_SW1X_VOLT_CTRL(regulatorVoltRegContent);
            regulatorVoltRegMask    = PF3000_SW1X_VOLT_CTRL_MASK;
            break;

        /* Process SW2. */
        case kPF3000_ModuleSwitch2:
            regulatorVoltRegAddr    = switchVoltRegTab[module][status];
            regulatorVoltRegContent = PF3000_SW2_VOLT_CTRL(regulatorVoltRegContent);
            regulatorVoltRegMask    = PF3000_SW2_VOLT_CTRL_MASK;
            break;

        /* Process SW3. */
        case kPF3000_ModuleSwitch3:
            regulatorVoltRegAddr    = switchVoltRegTab[module][status];
            regulatorVoltRegContent = PF3000_SW3_VOLT_CTRL(regulatorVoltRegContent);
            regulatorVoltRegMask    = PF3000_SW3_VOLT_CTRL_MASK;
            break;

        /* Process Switch Boost. */
        case kPF3000_ModuleSwitchBoost:
            regulatorVoltRegAddr    = PF3000_SWBST_CTRL;
            regulatorVoltRegContent = PF3000_SW_BST_CTRL_VOLT(regulatorVoltRegContent);
            regulatorVoltRegMask    = PF3000_SW_BST_CTRL_VOLT_MASK;
            break;

        /* Process LDO1, LDO2, LDO3, LDO4. */
        case kPF3000_ModuleLdo1:
        case kPF3000_ModuleLdo2:
        case kPF3000_ModuleLdo3:
        case kPF3000_ModuleLdo4:
            regulatorVoltRegAddr    = regulatorCtrlRegTab[module];
            regulatorVoltRegContent = PF3000_LDO_VOLT_CTRL(regulatorVoltRegContent);
            regulatorVoltRegMask    = PF3000_LDO_VOLT_CTRL_MASK;
            break;

        /* Process Vcc_sd. */
        case kPF3000_ModuleVcc_sd:
            regulatorVoltRegAddr    = regulatorCtrlRegTab[module];
            regulatorVoltRegContent = PF3000_VCC_SD_VOLT_CTRL(regulatorVoltRegContent);
            regulatorVoltRegMask    = PF3000_VCC_SD_VOLT_CTRL_MASK;
            break;

        /* Process V33. */
        case kPF3000_ModuleV33:
            regulatorVoltRegAddr    = regulatorCtrlRegTab[module];
            regulatorVoltRegContent = PF3000_V33_VOLT_CTRL(regulatorVoltRegContent);
            regulatorVoltRegMask    = PF3000_V33_VOLT_CTRL_MASK;
            break;

        default:
            regulatorVoltRegAddr = 0x00U;
            regulatorVoltRegMask = 0x00U;
            break;
    }

    /* Modify corresponding registers. */
    PF3000_ModifyReg(handle, regulatorVoltRegAddr, regulatorVoltRegMask, regulatorVoltRegContent);
}

uint32_t PF3000_GetRegulatorOutputVoltage(pf3000_handle_t *handle,
                                          pf3000_module_t module,
                                          pf3000_operating_status_t status)
{
    uint8_t regulatorVoltRegAddr;
    uint8_t regulatorVoltRegContent;
    uint8_t regulatorVoltRegMask;
    uint32_t voltage = 0U;

    assert(handle);
    assert((kPF3000_ModuleSwitch1A == module) || (kPF3000_ModuleSwitch1B == module) ||
           (kPF3000_ModuleSwitch2 == module) || (kPF3000_ModuleSwitch3 == module) ||
           (kPF3000_ModuleSwitchBoost == module) || (kPF3000_ModuleLdo1 == module) || (kPF3000_ModuleLdo2 == module) ||
           (kPF3000_ModuleLdo3 == module) || (kPF3000_ModuleLdo4 == module) || (kPF3000_ModuleVcc_sd == module) ||
           (kPF3000_ModuleV33 == module) || (kPF3000_ModuleVsnvs == module));

    assert((kPF3000_OperatingStatusSystemOn == status) || (kPF3000_OperatingStatusStandby == status) ||
           (kPF3000_OperatingStatusOff == status));

    switch (module)
    {
        /* Process SW1A, SW1B. */
        case kPF3000_ModuleSwitch1A:
        case kPF3000_ModuleSwitch1B:
            regulatorVoltRegAddr = switchVoltRegTab[module][status];
            regulatorVoltRegMask = PF3000_SW1X_VOLT_CTRL_MASK;
            break;

        /* Process SW2. */
        case kPF3000_ModuleSwitch2:
            regulatorVoltRegAddr = switchVoltRegTab[module][status];
            regulatorVoltRegMask = PF3000_SW2_VOLT_CTRL_MASK;
            break;

        /* Process SW3. */
        case kPF3000_ModuleSwitch3:
            regulatorVoltRegAddr = switchVoltRegTab[module][status];
            regulatorVoltRegMask = PF3000_SW3_VOLT_CTRL_MASK;
            break;

        /* Process Switch Boost. */
        case kPF3000_ModuleSwitchBoost:
            regulatorVoltRegAddr = regulatorCtrlRegTab[module];
            regulatorVoltRegMask = PF3000_SW_BST_CTRL_VOLT_MASK;
            break;

        /* Process LDO1, LDO2, LDO3, LDO4. */
        case kPF3000_ModuleLdo1:
        case kPF3000_ModuleLdo2:
        case kPF3000_ModuleLdo3:
        case kPF3000_ModuleLdo4:
            regulatorVoltRegAddr = regulatorCtrlRegTab[module];
            regulatorVoltRegMask = PF3000_LDO_VOLT_CTRL_MASK;
            break;

        /* Process Vcc_sd. */
        case kPF3000_ModuleVcc_sd:
            regulatorVoltRegAddr = regulatorCtrlRegTab[module];
            regulatorVoltRegMask = PF3000_VCC_SD_VOLT_CTRL_MASK;
            break;

        /* Process V33. */
        case kPF3000_ModuleV33:
            regulatorVoltRegAddr = regulatorCtrlRegTab[module];
            regulatorVoltRegMask = PF3000_V33_VOLT_CTRL_MASK;
            break;

        /* Process Vsnvs. */
        case kPF3000_ModuleVsnvs:
            regulatorVoltRegAddr = regulatorCtrlRegTab[module];
            regulatorVoltRegMask = PF3000_VSNVS_VOLT_CTRL_MASK;
            break;

        default:
            regulatorVoltRegAddr = 0x00U;
            regulatorVoltRegMask = 0x00U;
            break;
    }

    /* Get Register Value. */
    PF3000_ReadReg(handle, regulatorVoltRegAddr, &regulatorVoltRegContent);
    /* Modify Register Value. */
    regulatorVoltRegContent = regulatorVoltRegContent & regulatorVoltRegMask;
    /* Get LDO Voltage Control Value. */
    voltage = PF3000_GetRegulatorOutputVolt(handle, module, regulatorVoltRegContent);

    return voltage;
}

void PF3000_EnableRegulator(pf3000_handle_t *handle, pf3000_module_t module, bool enable)
{
    uint8_t regulatorCtrlRegAddr;

    assert(handle);
    assert((kPF3000_ModuleSwitch1A == module) || (kPF3000_ModuleSwitch1B == module) ||
           (kPF3000_ModuleSwitch2 == module) || (kPF3000_ModuleSwitch3 == module) ||
           (kPF3000_ModuleSwitchBoost == module) || (kPF3000_ModuleLdo1 == module) || (kPF3000_ModuleLdo2 == module) ||
           (kPF3000_ModuleLdo3 == module) || (kPF3000_ModuleLdo4 == module) || (kPF3000_ModuleVcc_sd == module) ||
           (kPF3000_ModuleV33 == module) || (kPF3000_ModuleVsnvs == module) || (kPF3000_ModuleVrefDdr == module));

    switch (module)
    {
        case kPF3000_ModuleLdo1:
        case kPF3000_ModuleLdo2:
        case kPF3000_ModuleLdo3:
        case kPF3000_ModuleLdo4:
        case kPF3000_ModuleVcc_sd:
        case kPF3000_ModuleV33:
            /* Get LDO Control Register Address. */
            regulatorCtrlRegAddr = regulatorCtrlRegTab[module];
            /* Modify LDO Control Register Value. */
            PF3000_ModifyReg(handle, regulatorCtrlRegAddr, PF3000_LDO_ENABLE_MASK,
                             (enable ? PF3000_LDO_ENABLE_MASK : 0x0U));
            break;

        case kPF3000_ModuleVrefDdr:
            /* Modify Vrefddr Control Register Value. */
            PF3000_ModifyReg(handle, PF3000_VREFDDR_CTRL, PF3000_VREFDDR_SUPPLY_ENABLE_MASK,
                             (enable ? PF3000_VREFDDR_SUPPLY_ENABLE_MASK : 0x0U));
            break;

        case kPF3000_ModuleSwitch1A:
        case kPF3000_ModuleSwitch1B:
        case kPF3000_ModuleSwitch2:
        case kPF3000_ModuleSwitch3:
        case kPF3000_ModuleSwitchBoost:
        case kPF3000_ModuleVsnvs:
        default:
            break;
    }
}

bool PF3000_IsRegulatorEnabled(pf3000_handle_t *handle, pf3000_module_t module)
{
    bool result;
    uint8_t regulatorCtrlRegAddr;
    uint8_t regulatorCtrlRegContent;

    assert(handle);
    assert((kPF3000_ModuleSwitch1A == module) || (kPF3000_ModuleSwitch1B == module) ||
           (kPF3000_ModuleSwitch2 == module) || (kPF3000_ModuleSwitch3 == module) ||
           (kPF3000_ModuleSwitchBoost == module) || (kPF3000_ModuleLdo1 == module) || (kPF3000_ModuleLdo2 == module) ||
           (kPF3000_ModuleLdo3 == module) || (kPF3000_ModuleLdo4 == module) || (kPF3000_ModuleVcc_sd == module) ||
           (kPF3000_ModuleV33 == module) || (kPF3000_ModuleVsnvs == module) || (kPF3000_ModuleVrefDdr == module));

    switch (module)
    {
        case kPF3000_ModuleLdo1:
        case kPF3000_ModuleLdo2:
        case kPF3000_ModuleLdo3:
        case kPF3000_ModuleLdo4:
        case kPF3000_ModuleVcc_sd:
        case kPF3000_ModuleV33:
            /* Get LDO Control Register Content. */
            regulatorCtrlRegAddr = regulatorCtrlRegTab[module];
            /* Read LDO Control Register Value. */
            PF3000_ReadReg(handle, regulatorCtrlRegAddr, &regulatorCtrlRegContent);
            /* LDO enable judge */
            result = (regulatorCtrlRegContent & PF3000_LDO_ENABLE_MASK) ? true : false;
            break;

        case kPF3000_ModuleVrefDdr:
            /* Get Vrefddr Control Register Content. */
            regulatorCtrlRegAddr = regulatorCtrlRegTab[module];
            /* Read Vrefddr Control Register Value. */
            PF3000_ReadReg(handle, regulatorCtrlRegAddr, &regulatorCtrlRegContent);
            /* Vrefddr enable judge */
            result = (regulatorCtrlRegContent & PF3000_VREFDDR_SUPPLY_ENABLE_MASK) ? true : false;
            break;

        case kPF3000_ModuleSwitch1A:
        case kPF3000_ModuleSwitch1B:
        case kPF3000_ModuleSwitch2:
        case kPF3000_ModuleSwitch3:
        case kPF3000_ModuleSwitchBoost:
        case kPF3000_ModuleVsnvs:
            /* They are enabled by default */
            result = true;
            break;

        default:
            result = false;
            break;
    }

    return result;
}

void PF3000_SetSwitchAttribute(pf3000_handle_t *handle,
                               pf3000_module_t module,
                               const pf3000_switch_attribute_t *attribute)
{
    uint8_t switchModeRegAddr;
    uint8_t switchCtrlRegAddr;
    uint8_t temp;

    assert(handle);
    assert(attribute);
    assert((kPF3000_ModuleSwitch1A == module) || (kPF3000_ModuleSwitch1B == module) ||
           (kPF3000_ModuleSwitch2 == module) || (kPF3000_ModuleSwitch3 == module));

    /* Set Switch Mode Register. */
    switch (module)
    {
        case kPF3000_ModuleSwitch1A:
            switchModeRegAddr = PF3000_SW1A_MODE;
            break;

        case kPF3000_ModuleSwitch1B:
            switchModeRegAddr = PF3000_SW1B_MODE;
            break;

        case kPF3000_ModuleSwitch2:
            switchModeRegAddr = PF3000_SW2_MODE;
            break;

        case kPF3000_ModuleSwitch3:
            switchModeRegAddr = PF3000_SW3_MODE;
            break;

        default:
            switchModeRegAddr = 0x00U;
            break;
    }

    /* Modify Switch Mode Register Value. */
    temp = ((attribute->offMode ? PF3000_SW_MODE_OFF_MASK : 0U) | (PF3000_SW_MODE_SELECTOR(attribute->mode)));

    PF3000_ModifyReg(handle, switchModeRegAddr, PF3000_SW_MODE_OFF_MASK | PF3000_SW_MODE_SELECTOR_MASK, temp);

    /* Set Switch Control Register. */
    switchCtrlRegAddr = regulatorCtrlRegTab[module];

    /* Modify Switch Control Register Value. */
    temp = ((attribute->dvsSpeed ? PF3000_SW_CTRL_DVSSPEED_MASK : 0U) | (PF3000_SW_CTRL_PHASE(attribute->phaseClock)) |
            (PF3000_SW_CTRL_FREQUENCY(attribute->frequency)) |
            (attribute->currentLimit ? PF3000_SW_CTRL_CURRENT_LIMIT_MASK : 0U));

    PF3000_ModifyReg(handle, switchCtrlRegAddr,
                     PF3000_SW_CTRL_DVSSPEED_MASK | PF3000_SW_CTRL_PHASE_MASK | PF3000_SW_CTRL_FREQUENCY_MASK |
                         PF3000_SW_CTRL_CURRENT_LIMIT_MASK,
                     temp);
}

void PF3000_SetSwitchBoostAttribute(pf3000_handle_t *handle, const pf3000_switch_boost_attribute_t *attribute)
{
    uint8_t switchBoostCtrlRegAddr;
    uint8_t temp;

    assert(handle);
    assert(attribute);

    switchBoostCtrlRegAddr = regulatorCtrlRegTab[kPF3000_ModuleSwitchBoost];

    temp = (PF3000_SW_BST_CTRL_STANDBY_MODE(attribute->standbyMode) |
            PF3000_SW_BST_CTRL_NORMAL_MODE(attribute->normalMode));

    PF3000_ModifyReg(handle, switchBoostCtrlRegAddr,
                     PF3000_SW_BST_CTRL_STANDBY_MODE_MASK | PF3000_SW_BST_CTRL_NORMAL_MODE_MASK, temp);
}

void PF3000_SetLdoAttribute(pf3000_handle_t *handle, pf3000_module_t module, const pf3000_ldo_attribute_t *attribute)
{
    uint8_t ldoCtrlRegAddr;
    uint8_t temp;

    assert(handle);
    assert(attribute);
    assert((kPF3000_ModuleLdo1 == module) || (kPF3000_ModuleLdo2 == module) || (kPF3000_ModuleLdo3 == module) ||
           (kPF3000_ModuleLdo4 == module) || (kPF3000_ModuleVcc_sd == module) || (kPF3000_ModuleV33 == module));

    /* Set LDO to load switch mode. */
    ldoCtrlRegAddr = regulatorCtrlRegTab[module];

    temp = ((attribute->offMode ? PF3000_LDO_OFF_MODE_MASK : 0) |
            (attribute->enableLowPower ? PF3000_LDO_LOW_POWER_MODE_MASK : 0) |
            ((attribute->standbyOnOff == kPF3000_LdoOffDuringStandby) ? PF3000_LDO_STANDBY_ON_OFF_MASK : 0));

    PF3000_ModifyReg(handle, ldoCtrlRegAddr,
                     PF3000_LDO_OFF_MODE_MASK | PF3000_LDO_LOW_POWER_MODE_MASK | PF3000_LDO_STANDBY_ON_OFF_MASK, temp);
}

void PF3000_SetCoinCellAttribute(pf3000_handle_t *handle, const pf3000_coin_cell_attribute_t *attribute)
{
    uint8_t temp;

    assert(handle);
    assert(attribute);

    temp = ((attribute->enableCoinCellCharger ? PF3000_COIN_CTRL_ENABLE_MASK : 0) |
            PF3000_COIN_CTRL_VOLT(attribute->coinCellChargingVoltage));

    /* Set Coin Cell Control Register. */
    PF3000_ModifyReg(handle, PF3000_COIN_CTRL, PF3000_COIN_CTRL_ENABLE_MASK | PF3000_COIN_CTRL_VOLT_MASK, temp);
}

void PF3000_SetStandbyPadAttribute(pf3000_handle_t *handle, const pf3000_standby_attribute_t *attribute)
{
    uint8_t temp;

    assert(handle);
    assert(attribute);

    temp = ((attribute->standbyPolarity ? PF3000_PWR_CTRL_STANDBYINV_MASK : 0U) |
            PF3000_PWR_CTRL_STBYDLY(attribute->standbyDelay));

    /* Set Coin Cell Control Register. */
    PF3000_ModifyReg(handle, PF3000_PWR_CTRL, PF3000_PWR_CTRL_STANDBYINV_MASK | PF3000_PWR_CTRL_STBYDLY_MASK, temp);
}

void PF3000_SetPwrOnPadAttibute(pf3000_handle_t *handle, const pf3000_power_on_attribute_t *attribute)
{
    uint8_t temp;

    assert(handle);
    assert(attribute);

    temp = (PF3000_PWR_CTRL_PWRONDBNC(attribute->debounce) |
            (attribute->longPressAllowOffMode ? PF3000_PWR_CTRL_PWRONRSTEN_MASK : 0U) |
            (attribute->longPressRestart ? PF3000_PWR_CTRL_RESTARTEN_MASK : 0U));

    /* Set Coin Cell Control Register. */
    PF3000_ModifyReg(handle, PF3000_PWR_CTRL,
                     PF3000_PWR_CTRL_PWRONDBNC_MASK | PF3000_PWR_CTRL_PWRONRSTEN_MASK | PF3000_PWR_CTRL_RESTARTEN_MASK,
                     temp);
}
/*******************************************************************************
 * EOF
 ******************************************************************************/
