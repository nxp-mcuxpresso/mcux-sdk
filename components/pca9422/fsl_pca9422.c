/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_pca9422.h"
#include "fsl_power.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#if defined(FSL_DEBUG_PMIC_DRIVER) && (FSL_DEBUG_PMIC_DRIVER != 0U)
#include "fsl_debug_console.h"
#define LOG_INFO PRINTF
#else
#define LOG_INFO(...)
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static uint64_t pca9422_ffs(uint64_t word);

#define MASK2SHIFT(_mask) pca9422_ffs(_mask)
/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint64_t pca9422_ffs(uint64_t word)
{
    uint32_t num = 0U;

    if ((word & 0xffffffffU) == 0U)
    {
        num += 32U;
        word >>= 32U;
    }
    if ((word & 0xffffU) == 0U)
    {
        num += 16U;
        word >>= 16U;
    }
    if ((word & 0xffU) == 0U)
    {
        num += 8U;
        word >>= 8U;
    }
    if ((word & 0xfU) == 0U)
    {
        num += 4U;
        word >>= 4U;
    }
    if ((word & 0x3U) == 0U)
    {
        num += 2U;
        word >>= 2U;
    }
    if ((word & 0x1U) == 0U)
    {
        num += 1U;
    }
    return (uint64_t)num;
}

void PCA9422_GetChargerDefaultConfig(pca9422_charger_config_t *config)
{
    assert(config);

    /* Set callback function to NULL Pointer. */
    config->I2C_SendFunc    = NULL;
    config->I2C_ReceiveFunc = NULL;

    /* Precharge current set to 20% of fast charge current. */
    config->prechgI = kPCA9422_PrechgI20percent;
    /* Current step is 2.5mA. */
    config->chgIStep = kPCA9422_ChgIStep2p5mA;
    /* Top-off current is 2.5% of fast charge current. */
    config->topoffI = kPCA9422_TopoffI2p5percent;
    /* Fast charge current is 100mA. */
    config->fastI = 100U;
    /* VBAT regulation voltage is 4200mV. */
    config->vbatReg = 4200U;
    /* Recharge voltage threshold is [VBAT_REG - 100mV]. */
    config->rechgVolt = kPCA9422_RechargeTh100mV;
    /* Precharge timer is 30minutes. */
    config->prechgTime = kPCA9422_PrechgTimer30min;
    /* Fast charge timer is 3hours. */
    config->fastchgTime = kPCA9422_FastchgTimer3h;
    /* Top-off timer is 5minutes. */
    config->topoffTime = kPCA9422_TopoffTimer5min;
    /* Warm(40C) voltage threshold is 32.63% of VL. */
    config->warmVolt = kPCA9422_Vwarm45C32p63percent;
    /* Warm Plus(50C) voltage threshold is 29.07% of VL. */
    config->warmPlusVolt = kPCA9422_Vwarm50C29p07percent;
    /* Hot(60C) voltage threshold is 22.94% of VL. */
    config->hotVolt = kPCA9422_Vhot60C22p94percent;
    /* Cool(10C) voltage threshold is 64.82% of VL. */
    config->coolVolt = kPCA9422_Vcool10C64p82percent;
    /* Cold(0C) voltage threshold is 74.18% of VL. */
    config->coldVolt = kPCA9422_Vcold0C74p18percent;
    /* New VBAT_REG voltage at WARM(40C) stays VBAT_REG. */
    config->warmVbatReg = kPCA9422_NewVbat45C_StayVbatReg;
    /* New VBAT_REG voltage at WARM_PLUS(50C) stays VBAT_REG. */
    config->warmPlusVbatReg = kPCA9422_NewVbat50C_StayVbatReg;
    /* New I_VBAT current at COOL(10C) stays I_FAST_CHG. */
    config->coldIVbat = kPCA9422_NewIVbat10C_StayIFastchg;
    /* New I_VBAT current at WARM(45C) stays I_FAST_CHG. */
    config->warmIVbat = kPCA9422_NewIVbat45C_StayIFastchg;
    /* New I_VBAT current at WARM_PLUS(50C) stays I_FAST_CHG. */
    config->warmPlusIVbat = kPCA9422_NewIVbat50C_StayIFastchg;
    /* AICL threshold on CHGIN is 4.5V. */
    config->aiclV = kPCA9422_AICLV4p5V;
    /* Input current limit on CHGIN is 470mA. */
    config->icl = kPCA9422_ChgInIlim_470mA;
    /* VSYS regulation voltage is 4550mV. */
    config->vsysReg = 4550U;
    /* AMUX wait time */
    config->amuxWaitTime = kPCA9422_AMUXAutoOffWait_256us;
    /* AMUX mode */
    config->amuxMode = kPCA9422_AMUXModeManual;
    /* VBAT/VSYS channel scale factor */
    config->amuxVbatGain = kPCA9422_AMUXVbatVsysGain_1dvd3;
    /* THERM and THERM_BIAS channels scale factor */
    config->amuxThermGain = kPCA9422_AMUXThermGain_1;
    /* AMUX channel */
    config->amuxChannel = kPCA9422_AMUXChannel_Off;
    /* I2C slave address. */
    config->slaveAddress = PCA9422_DEFAULT_I2C_ADDR;
}

void PCA9422_InitCharger(pca9422_handle_t *handle, const pca9422_charger_config_t *config)
{
    uint8_t chgCntl[11], chgInCntl[4], regVal;
    bool result;

    assert(handle);
    assert(config);

    /* Initialize Callback functions. */
    handle->I2C_SendFunc    = config->I2C_SendFunc;
    handle->I2C_ReceiveFunc = config->I2C_ReceiveFunc;
    /* Set Slave Address. */
    handle->slaveAddress = config->slaveAddress;

    /* Initialize Charger control registers */
    chgCntl[0] = PCA9422_CHARGER_LOCK_UNLOCK;
    chgCntl[1] = (uint8_t)(PCA9422_CHARGER_CNTL_1_AUTOSTOP_CHG_EN | PCA9422_CHARGER_CNTL_1_CHARGER_EN |
                           (uint8_t)config->warmPlusVolt | (uint8_t)config->prechgI | (uint8_t)config->chgIStep);
    chgCntl[2] = (uint8_t)(PCA9422_VBAT_REG(config->vbatReg));
    chgCntl[3] = (uint8_t)PCA9422_I_FAST_CHG_DFT;
    chgCntl[4] = (uint8_t)((uint8_t)config->rechgVolt | (uint8_t)config->topoffI | (uint8_t)config->prechgTime);
    chgCntl[5] = (uint8_t)PCA9422_CHARGER_CNTL_5_DFT;
    chgCntl[6] = (uint8_t)((uint8_t)config->hotVolt | (uint8_t)config->warmVolt | (uint8_t)config->coolVolt |
                           (uint8_t)config->coldVolt);
    chgCntl[7] = (uint8_t)(PCA9422_CHARGER_CNTL_7_CHG_DISABLE_AT_COLD_HOT_EN | (uint8_t)config->fastchgTime |
                           (uint8_t)config->coldIVbat | (uint8_t)config->warmVbatReg);
    chgCntl[8] = (uint8_t)(config->topoffTime);
    chgCntl[9] =
        (uint8_t)((uint8_t)config->warmPlusVbatReg | (uint8_t)config->warmPlusIVbat | (uint8_t)config->warmIVbat);
    chgCntl[10] = (uint8_t)((uint8_t)config->amuxWaitTime | (uint8_t)config->amuxMode | (uint8_t)config->amuxVbatGain |
                            (uint8_t)config->amuxThermGain | (uint8_t)config->amuxChannel);

    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, chgCntl, sizeof(chgCntl));
    regVal = PCA9422_CHARGER_LOCK_LOCK;
    result = result ? PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U) : result;
    if (!result)
    {
        assert(false);
    }

    chgInCntl[0] = (uint8_t)PCA9422_CHGIN_CNTL_O_CHGIN_PD_EN;
    chgInCntl[1] = (uint8_t)((uint8_t)config->aiclV | PCa9422_CHGIN_CNTL_1_AICL_EN);
    chgInCntl[2] = (uint8_t)(config->icl);
    chgInCntl[3] = (uint8_t)(PCA9422_VSYS_REG(config->vsysReg) << MASK2SHIFT(PCA9422_CHGIN_CNTL_3_VSYS_REG));
    result       = PCA9422_WriteRegs(handle, PCA9422_CHGIN_CNTL_0, chgInCntl, sizeof(chgInCntl));
    if (!result)
    {
        assert(false);
    }
}

bool PCA9422_SetPreChargeCurrent(pca9422_handle_t *handle, uint8_t iPrechg)
{
    uint8_t regVal;
    bool result = true;

    /* Write CHARGER_LOCK bit */
    regVal = PCA9422_CHARGER_LOCK_UNLOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);
    if (result == false)
    {
        goto error;
    }

    /* Set precharge current */
    regVal = iPrechg;
    result = PCA9422_ModifyReg(handle, PCA9422_CHG_CNTL1, PCA9422_CHARGER_CNTL_1_PRECHG_CURRENT, regVal);
    if (result == false)
    {
        goto error;
    }

    /* Write CHARGER_LOCK bit */
    regVal = PCA9422_CHARGER_LOCK_LOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);

error:
    return result;
}

uint8_t PCA9422_GetPreChargeCurrent(pca9422_handle_t *handle)
{
    uint8_t regVal;
    uint8_t iPrechg;
    bool result = true;

    /* Write CHARGER_LOCK bit */
    regVal = PCA9422_CHARGER_LOCK_UNLOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);
    if (!result)
    {
        LOG_INFO("Error in I2C operation in %s.", __func__);
    }

    /* Read CHG_CNTL_1 */
    result = PCA9422_ReadRegs(handle, PCA9422_CHG_CNTL1, &regVal, 1U);
    if (!result)
    {
        LOG_INFO("Error in I2C operation in %s.", __func__);
    }
    iPrechg = (regVal & PCA9422_CHARGER_CNTL_1_PRECHG_CURRENT);

    /* Write CHARGER_LOCK bit */
    regVal = PCA9422_CHARGER_LOCK_LOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);
    if (!result)
    {
        LOG_INFO("Error in I2C operation in %s.", __func__);
    }

    return iPrechg;
}

bool PCA9422_SetTopoffCurrent(pca9422_handle_t *handle, uint8_t iTopoff)
{
    uint8_t regVal;
    bool result = true;

    /* Write CHARGER_LOCK bit */
    regVal = PCA9422_CHARGER_LOCK_UNLOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);
    if (result == false)
    {
        goto error;
    }

    /* Set topoff current */
    regVal = iTopoff;
    result = PCA9422_ModifyReg(handle, PCA9422_CHG_CNTL4, PCA9422_CHARGER_CNTL_4_TOPOFF_CURRENT, regVal);
    if (result == false)
    {
        goto error;
    }

    /* Write CHARGER_LOCK bit */
    regVal = PCA9422_CHARGER_LOCK_LOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);

error:
    return result;
}

uint8_t PCA9422_GetTopoffCurrent(pca9422_handle_t *handle)
{
    uint8_t regVal;
    uint8_t iTopoff = 0U;
    bool result;

    /* Write CHARGER_LOCK bit */
    regVal = PCA9422_CHARGER_LOCK_UNLOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);
    if (result == true)
    {
        /* Read CHG_CNTL_4 */
        result  = PCA9422_ReadRegs(handle, PCA9422_CHG_CNTL4, &regVal, 1U);
        iTopoff = (regVal & PCA9422_CHARGER_CNTL_4_TOPOFF_CURRENT);
    }
    if (result == true)
    {
        /* Write CHARGER_LOCK bit */
        regVal = PCA9422_CHARGER_LOCK_LOCK;
        result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);
    }
    assert(result == true);

    return iTopoff;
}

bool PCA9422_SetFastChargeCurrent(pca9422_handle_t *handle, uint16_t iFast)
{
    uint8_t currStep;
    uint8_t regVal;
    bool result;

    /* Write CHARGER_LOCK bit */
    regVal = PCA9422_CHARGER_LOCK_UNLOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);
    if (result == false)
    {
        goto error;
    }

    /* Check charging current */
    if (iFast > 320U * 10U)
    {
        /* Set current step to 5mA */
        regVal = (uint8_t)kPCA9422_ChgIStep5p0mA;
    }
    else
    {
        /* Set current step to 2.5mA */
        regVal = (uint8_t)kPCA9422_ChgIStep2p5mA;
    }
    result = PCA9422_ModifyReg(handle, PCA9422_CHG_CNTL1, PCA9422_CHARGER_CNTL_1_CHG_CURRENT_STEP, regVal);
    if (result == false)
    {
        goto error;
    }
    /* Get current step */
    currStep = (regVal == (uint8_t)kPCA9422_ChgIStep5p0mA) ? 50U : 25U;
    regVal   = (uint8_t)((iFast - currStep) / currStep);

    /* Set I_FAST_CHG */
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL3, &regVal, 1U);
    if (result == false)
    {
        goto error;
    }

    /* Write CHARGER_LOCK bit */
    regVal = PCA9422_CHARGER_LOCK_LOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);

error:
    return result;
}

uint16_t PCA9422_GetFastChargeCurrent(pca9422_handle_t *handle)
{
    uint8_t currStep;
    uint8_t regVal;
    uint16_t iFastReg;
    bool result = true;

    /* Write CHARGER_LOCK bit */
    regVal = PCA9422_CHARGER_LOCK_UNLOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);
    if (!result)
    {
        LOG_INFO("Error in I2C operation in %s.", __func__);
    }

    /* Get current step */
    /* Read CHG_CNTL_1 */
    result = PCA9422_ReadRegs(handle, PCA9422_CHG_CNTL1, &regVal, 1U);
    if (!result)
    {
        LOG_INFO("Error in I2C operation in %s.", __func__);
    }
    currStep = ((regVal & PCA9422_CHARGER_CNTL_1_CHG_CURRENT_STEP) != 0U) ? 50U : 25U;

    /* Read CHG_CNTL_3 */
    result = PCA9422_ReadRegs(handle, PCA9422_CHG_CNTL3, &regVal, 1U);
    if (!result)
    {
        LOG_INFO("Error in I2C operation in %s.", __func__);
    }
    iFastReg = (uint16_t)regVal * currStep + (uint16_t)currStep;

    /* Write CHARGER_LOCK bit */
    regVal = PCA9422_CHARGER_LOCK_LOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);
    if (!result)
    {
        LOG_INFO("Error in I2C operation in %s\r\n", __func__);
    }

    return iFastReg;
}

uint16_t PCA9422_GetChargeCurrent(pca9422_handle_t *handle)
{
    uint8_t chgSts[4];
    uint8_t regVal, regBit = 0U;
    uint16_t iCharge;
    uint8_t preChgCurr[2] = {10U, 20U};            /* 10%, 20% */
    uint8_t topOffCurr[4] = {25U, 50U, 75U, 100U}; /* 2.5%, 5.0%, 7.5%, 10.0% */
    uint8_t thermCurr[4]  = {100U, 75U, 50U, 25U}; /* 1.0, 0.75, 0.5, 0.25 */
    float tempVal;
    bool result;

    /* Read CHARGER_0_STS ~ CHARGER_3_STS */
    result = PCA9422_ReadRegs(handle, PCA9422_CHARGER_0_STS, chgSts, 4U);
    assert(result);

    /* Write CHARGER_LOCK bit */
    regVal = PCA9422_CHARGER_LOCK_UNLOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);
    assert(result);

    /* Get fast charge current */
    iCharge = PCA9422_GetFastChargeCurrent(handle) / 10U;

    /* Check Charge state first */
    /* Check CHARGER_0_STS */
    if ((chgSts[0] & PCA9422_INT_CHARGER_0_CHG_QUAL_OK) != 0U)
    {
        /* Qualification process for charging passed */
        /* Charging */
        if ((chgSts[0] & PCA9422_INT_CHARGER_0_FAST_CHARGE) != 0U)
        {
            /* Keep iCharge */
        }
        else if ((chgSts[0] & PCA9422_INT_CHARGER_0_CV_MODE) != 0U)
        {
            /* Keep iCharge */
        }
        else if ((chgSts[0] & PCA9422_INT_CHARGER_0_TOPOFF) != 0U)
        {
            /* Read topoff current */
            /* Read CHG_CNTL_4 */
            result = PCA9422_ReadRegs(handle, PCA9422_CHG_CNTL4, &regVal, 1U);
            assert(result);
            regBit =
                (regVal & PCA9422_CHARGER_CNTL_4_TOPOFF_CURRENT) >> MASK2SHIFT(PCA9422_CHARGER_CNTL_4_TOPOFF_CURRENT);
            tempVal = (float)iCharge * (float)topOffCurr[regBit] / 10.0f / 100.0f;
            iCharge = (uint16_t)tempVal;
        }
        else if ((chgSts[0] & PCA9422_INT_CHARGER_0_PRECHARGE) != 0U)
        {
            /* Read precharge current */
            /* Read CHG_CNTL_1 */
            result = PCA9422_ReadRegs(handle, PCA9422_CHG_CNTL1, &regVal, 1U);
            assert(result);
            regBit =
                (regVal & PCA9422_CHARGER_CNTL_1_PRECHG_CURRENT) >> MASK2SHIFT(PCA9422_CHARGER_CNTL_1_PRECHG_CURRENT);
            tempVal = (float)iCharge * (float)preChgCurr[regBit] / 100.0f;
            iCharge = (uint16_t)tempVal;
        }
        else
        {
            /* iCharge */
            iCharge = 0U;
        }
    }
    else
    {
        iCharge = 0U;
    }

    /* Check whether JEITA function is enabled or not */
    /* Read CHG_CNTL_5 */
    result = PCA9422_ReadRegs(handle, PCA9422_CHG_CNTL5, &regVal, 1U);
    assert(result);
    /* Check THERM_NTC_EN bit */
    if (((regVal & PCA9422_CHARGER_CNTL_5_THERM_NTC_EN) != 0U) && (iCharge != 0U))
    {
        /* Use JEITA function */
        /* Check JEITA interrupt happens */
        if ((chgSts[1] & PCA9422_INT_CHARGER_1_THERM_HOT) != 0U)
        {
            iCharge = 0U;
        }
        else if ((chgSts[1] & PCA9422_INT_CHARGER_1_THERM_WARM_PLUS) != 0U)
        {
            /* NEW_I_VBAT_AT_50C */
            /* Read CHG_CNTL_9 */
            result = PCA9422_ReadRegs(handle, PCA9422_CHG_CNTL9, &regVal, 1U);
            assert(result);
            regBit = (regVal & PCA9422_CHARGER_CNTL_9_NEW_I_VBAT_AT_50C) >>
                     MASK2SHIFT(PCA9422_CHARGER_CNTL_9_NEW_I_VBAT_AT_50C);
            tempVal = (float)iCharge * (float)thermCurr[regBit] / 100.0f;
            iCharge = (uint16_t)tempVal;
        }
        else if ((chgSts[1] & PCA9422_INT_CHARGER_1_THERM_WARM) != 0U)
        {
            /* NEW_I_VBAT_AT_45C */
            /* Read CHG_CNTL_9 */
            result = PCA9422_ReadRegs(handle, PCA9422_CHG_CNTL9, &regVal, 1U);
            assert(result);
            regBit = (regVal & PCA9422_CHARGER_CNTL_9_NEW_I_VBAT_AT_45C) >>
                     MASK2SHIFT(PCA9422_CHARGER_CNTL_9_NEW_I_VBAT_AT_45C);
            tempVal = (float)iCharge * (float)thermCurr[regBit] / 100.0f;
            iCharge = (uint16_t)tempVal;
        }
        else if ((chgSts[1] & PCA9422_INT_CHARGER_1_THERM_COOL) != 0U)
        {
            /* NEW_I_VBAT_AT_10C */
            /* Read CHG_CNTL_7 */
            result = PCA9422_ReadRegs(handle, PCA9422_CHG_CNTL7, &regVal, 1U);
            assert(result);
            regBit = (regVal & PCA9422_CHARGER_CNTL_7_NEW_I_VBAT_AT_10C) >>
                     MASK2SHIFT(PCA9422_CHARGER_CNTL_7_NEW_I_VBAT_AT_10C);
            tempVal = (float)iCharge * (float)thermCurr[regBit] / 100.0f;
            iCharge = (uint16_t)tempVal;
        }
        else if ((chgSts[1] & PCA9422_INT_CHARGER_1_THERM_COLD) != 0U)
        {
            iCharge = 0U;
        }
        else if ((chgSts[1] & PCA9422_INT_CHARGER_1_VBAT_OVP) != 0U)
        {
            iCharge = 0U;
        }
        else if ((chgSts[1] & PCA9422_INT_CHARGER_1_NO_BATTERY) != 0U)
        {
            iCharge = 0U;
        }
        else
        {
            /* PCA9422_INT_CHARGER_1_VBAT_OVP - Keep iCharge */
        }
    }

    /* Write CHARGER_LOCK bit */
    regVal = PCA9422_CHARGER_LOCK_LOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);
    assert(result);

    return (result ? iCharge : 0U);
}

uint16_t PCA9422_GetVBATRegulation(pca9422_handle_t *handle)
{
    uint8_t chgSts[4];
    uint8_t regVal = 0U;
    uint8_t regBit = 0U;
    uint16_t vFloat;
    uint8_t newVbatOffset[4] = {0U, 100U, 150U, 200U}; /* 0, 100mV, 150mV, 200mV */
    bool result              = true;

    /* Write CHARGER_LOCK bit to UNLOCK */
    regVal = PCA9422_CHARGER_LOCK_UNLOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);
    if (result == false)
    {
        vFloat = 0U;
        goto error;
    }

    /* Read CHG_CNTL_2 */
    result = PCA9422_ReadRegs(handle, PCA9422_CHG_CNTL2, &regVal, 1U);
    if (result == false)
    {
        vFloat = 0U;
        goto error;
    }
    /* Convert reg value to vFloat */
    vFloat = (uint16_t)regVal * PCA9422_VBAT_REG_STEP + PCA9422_VBAT_REG_MIN;

    /* Check JEITA condition */
    /* Read CHARGER_0_STS ~ CHARGER_3_STS */
    result = PCA9422_ReadRegs(handle, PCA9422_CHARGER_0_STS, chgSts, 4U);
    if (result == false)
    {
        vFloat = 0U;
        goto error;
    }

    /* Check whether JEITA function is enabled or not */
    /* Read CHG_CNTL_5 */
    result = PCA9422_ReadRegs(handle, PCA9422_CHG_CNTL5, &regVal, 1U);
    if (result == false)
    {
        vFloat = 0U;
        goto error;
    }
    /* Check THERM_NTC_EN bit */
    if ((regVal & PCA9422_CHARGER_CNTL_5_THERM_NTC_EN) != 0U)
    {
        /* Use JEITA function */
        /* Check JEITA interrupt happens */
        if ((chgSts[1] & PCA9422_INT_CHARGER_1_THERM_WARM_PLUS) != 0U)
        {
            /* NEW_VBAT_AT_50C */
            /* Read CHG_CNTL_9 */
            result = PCA9422_ReadRegs(handle, PCA9422_CHG_CNTL9, &regVal, 1U);
            if (result == false)
            {
                vFloat = 0U;
                goto error;
            }
            regBit =
                (regVal & PCA9422_CHARGER_CNTL_9_NEW_VBAT_AT_50C) >> MASK2SHIFT(PCA9422_CHARGER_CNTL_9_NEW_VBAT_AT_50C);
            vFloat = vFloat - newVbatOffset[regBit];
        }
        else if ((chgSts[1] & PCA9422_INT_CHARGER_1_THERM_WARM) != 0U)
        {
            /* NEW_VBAT_AT_45C */
            /* Read CHG_CNTL_7 */
            result = PCA9422_ReadRegs(handle, PCA9422_CHG_CNTL7, &regVal, 1U);
            if (result == false)
            {
                vFloat = 0U;
                goto error;
            }
            regBit =
                (regVal & PCA9422_CHARGER_CNTL_7_NEW_VBAT_AT_45C) >> MASK2SHIFT(PCA9422_CHARGER_CNTL_7_NEW_VBAT_AT_45C);
            vFloat = vFloat - newVbatOffset[regBit];
        }
        else
        {
            /* No Charge or Keep Vreg */
        }
    }

    /* Write CHARGER_LOCK bit to LOCK */
    regVal = PCA9422_CHARGER_LOCK_LOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);
    if (result == false)
    {
        vFloat = 0U;
    }

error:
    return vFloat;
}

bool PCA9422_SetVBATRegulation(pca9422_handle_t *handle, uint16_t vFloat)
{
    uint8_t regVal = 0U;
    uint16_t vSys  = 0U;
    bool result    = true;

    /* Check maximum VFLOAT */
    if (vFloat > PCA9422_VBAT_REG_MAX)
    {
        vFloat = PCA9422_VBAT_REG_MAX;
    }
    /* First, set new VSYS_REG */
    vSys = vFloat + PCA9422_VBAT_CLAMP_OFFSET;
    if (vSys < PCA9422_VSYS_REG_MIN)
    {
        vSys = PCA9422_VSYS_REG_MIN;
    }
    /* Convert vSys to reg value */
    regVal = (uint8_t)PCA9422_VSYS_REG(vSys);
    result = PCA9422_ModifyRegReadback(handle, PCA9422_CHGIN_CNTL_3, PCA9422_CHGIN_CNTL_3_VSYS_REG,
                                       regVal << MASK2SHIFT(PCA9422_CHGIN_CNTL_3_VSYS_REG));
    if (result == false)
    {
        goto error;
    }

    /* Write CHARGER_LOCK bit to UNLOCK */
    regVal = PCA9422_CHARGER_LOCK_UNLOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);
    if (result == false)
    {
        goto error;
    }

    /* Convert vFloat to reg value */
    regVal = (uint8_t)PCA9422_VBAT_REG(vFloat);
    result = PCA9422_WriteRegsReadback(handle, PCA9422_CHG_CNTL2, &regVal);
    if (result == false)
    {
        goto error;
    }

    /* Write CHARGER_LOCK bit to LOCK */
    regVal = PCA9422_CHARGER_LOCK_LOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);

error:
    return result;
}

bool PCA9422_SetRechargeThreshold(pca9422_handle_t *handle, uint8_t rechgTh)
{
    uint8_t regVal;
    bool result = true;

    /* Write CHARGER_LOCK bit */
    regVal = PCA9422_CHARGER_LOCK_UNLOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);
    if (result == false)
    {
        goto error;
    }

    /* Set recharge threshold */
    regVal = rechgTh;
    result = PCA9422_ModifyReg(handle, PCA9422_CHG_CNTL4, PCA9422_CHARGER_CNTL_4_RECHARGE_TH, regVal);
    if (result == false)
    {
        goto error;
    }

    /* Write CHARGER_LOCK bit */
    regVal = PCA9422_CHARGER_LOCK_LOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);

error:
    return result;
}

bool PCA9422_SetPrechargeTimer(pca9422_handle_t *handle, uint8_t tPrechg)
{
    uint8_t regVal;
    bool result = true;

    /* Write CHARGER_LOCK bit */
    regVal = PCA9422_CHARGER_LOCK_UNLOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);
    if (result == false)
    {
        goto error;
    }

    /* Set precharge timer */
    regVal = tPrechg;
    result = PCA9422_ModifyReg(handle, PCA9422_CHG_CNTL4, PCA9422_CHARGER_CNTL_4_PRE_CHG_TIMER, regVal);
    if (result == false)
    {
        goto error;
    }

    /* Write CHARGER_LOCK bit */
    regVal = PCA9422_CHARGER_LOCK_LOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);

error:
    return result;
}

bool PCA9422_SetFastchargeTimer(pca9422_handle_t *handle, uint8_t tFastchg)
{
    uint8_t regVal;
    bool result = true;

    /* Write CHARGER_LOCK bit */
    regVal = PCA9422_CHARGER_LOCK_UNLOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);
    if (result == false)
    {
        goto error;
    }

    /* Set fast charge timer */
    regVal = tFastchg;
    result = PCA9422_ModifyReg(handle, PCA9422_CHG_CNTL7, PCA9422_CHARGER_CNTL_7_FAST_CHG_TIMER, regVal);
    if (result == false)
    {
        goto error;
    }

    /* Write CHARGER_LOCK bit */
    regVal = PCA9422_CHARGER_LOCK_LOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);

error:
    return result;
}

bool PCA9422_SetTopoffTimer(pca9422_handle_t *handle, uint8_t tTopoff)
{
    uint8_t regVal;
    bool result = true;

    /* Write CHARGER_LOCK bit */
    regVal = PCA9422_CHARGER_LOCK_UNLOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);
    if (result == false)
    {
        goto error;
    }

    /* Set fast charge timer */
    regVal = tTopoff;
    result = PCA9422_ModifyReg(handle, PCA9422_CHG_CNTL8, PCA9422_CHARGER_CNTL_8_TOP_OFF_TIMER, regVal);
    if (result == false)
    {
        goto error;
    }

    /* Write CHARGER_LOCK bit */
    regVal = PCA9422_CHARGER_LOCK_LOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);

error:
    return result;
}

uint8_t PCA9422_GetChargeState(pca9422_handle_t *handle)
{
    uint8_t chgSts = 0U;
    uint8_t regVal[4];

    /* Read CHARGER_0_STS ~ CHARGER_3_STS */
    (void)PCA9422_ReadRegs(handle, PCA9422_CHARGER_0_STS, regVal, 4U);

    /* Check CHARGER_0_STS */
    if ((regVal[0] & PCA9422_INT_CHARGER_0_CHG_QUAL_OK) != 0U)
    {
        /* Qualification process for charging passed */
        /* Charging */
        if (((regVal[0] & PCA9422_INT_CHARGER_0_CV_MODE) != 0U) || ((regVal[0] & PCA9422_INT_CHARGER_0_TOPOFF) != 0U))
        {
            chgSts = 0x03U; /* CV mode - CV or TOPOFF */
        }
        else if (((regVal[0] & PCA9422_INT_CHARGER_0_FAST_CHARGE) != 0U) ||
                 ((regVal[0] & PCA9422_INT_CHARGER_0_PRECHARGE) != 0U))
        {
            chgSts = 0x01U; /* CC mode - FAST CHARGE or PRE-CHARGE */
        }
        else
        {
            chgSts = 0x00U; /* Not charging */
        }

        /* Check CHARGER_2_STS */
        if ((regVal[2] & PCA9422_INT_CHARGER_2_CHARGE_DONE) != 0U)
        {
            chgSts = 0x04U;
        }
    }
    else
    {
        /* Any charge fault condition happens or No charge */
        chgSts = 0x00U;
    }

    return chgSts;
}

void PCA9422_SelectAMUXChannel(pca9422_handle_t *handle, pca9422_amux_channel_t amuxCh)
{
    uint8_t regVal;

    /* Write CHARGER_LOCK bit */
    regVal = PCA9422_CHARGER_LOCK_UNLOCK;
    (void)PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);

    (void)PCA9422_ModifyReg(handle, PCA9422_CHG_CNTL10, PCA9422_CHARGER_CNTL_10_AMUX_CHANNEL, (uint8_t)amuxCh);

    /* Write CHARGER_LOCK bit */
    regVal = PCA9422_CHARGER_LOCK_LOCK;
    (void)PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);
}

void PCA9422_SetAMUXMode(pca9422_handle_t *handle, pca9422_amux_mode_t mode)
{
    uint8_t regVal;
    bool result = true;

    /* Write CHARGER_LOCK bit */
    regVal = PCA9422_CHARGER_LOCK_UNLOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);
    if (!result)
    {
        LOG_INFO("I2C operation error in %s\r\n", __func__);
    }

    result = PCA9422_ModifyReg(handle, PCA9422_CHG_CNTL10, PCA9422_CHARGER_CNTL_10_AMUX_MODE, (uint8_t)mode);
    if (!result)
    {
        LOG_INFO("I2C operation error in %s\r\n", __func__);
    }

    /* Write CHARGER_LOCK bit */
    regVal = PCA9422_CHARGER_LOCK_LOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);
    if (!result)
    {
        LOG_INFO("I2C operation error in %s\r\n", __func__);
    }
}

pca9422_amux_mode_t PCA9422_GetAMUXMode(pca9422_handle_t *handle)
{
    bool result;
    uint8_t regVal;

    /* Write CHARGER_LOCK bit */
    regVal = PCA9422_CHARGER_LOCK_UNLOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);
    if (!result)
    {
        assert(false);
    }

    result = PCA9422_ReadRegs(handle, PCA9422_CHG_CNTL10, &regVal, 1U);
    if (!result)
    {
        assert(false);
    }

    /* Write CHARGER_LOCK bit */
    regVal = PCA9422_CHARGER_LOCK_LOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);

    if (!result)
    {
        assert(false);
    }

    regVal = regVal & PCA9422_CHARGER_CNTL_10_AMUX_MODE;
    return (pca9422_amux_mode_t)regVal;
}

bool PCA9422_SetAMUXConfig(pca9422_handle_t *handle, pca9422_amux_config_t config)
{
    bool result;
    uint8_t regVal;

    /* Write CHARGER_LOCK bit */
    regVal = PCA9422_CHARGER_LOCK_UNLOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);
    if (!result)
    {
        return result;
    }

    regVal = (uint8_t)(config.waitTime | config.amuxMode | config.vbatGain | config.thermGain | config.amuxChannel);
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL10, &regVal, 1U);
    if (!result)
    {
        return result;
    }

    /* Write CHARGER_LOCK bit */
    regVal = PCA9422_CHARGER_LOCK_LOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);

    return result;
}

float PCA9422_GetAMUXScaleFactor(pca9422_handle_t *handle, pca9422_amux_channel_t channel)
{
    float scaleFactor;
    uint8_t regVal;

    switch (channel)
    {
        case kPCA9422_AMUXChannel_Off:
            scaleFactor = 0.0f;
            break;
        case kPCA9422_AMUXChannel_Vbat:
        case kPCA9422_AMUXChannel_Vsys:
            /* Get scale factor */
            (void)PCA9422_ReadRegs(handle, PCA9422_CHG_CNTL10, &regVal, 1U);
            scaleFactor = ((regVal & PCA9422_CHARGER_CNTL_10_AMUX_VBAT_VSYS_GAIN) != 0U) ? 4.0f : 3.0f;
            break;
        case kPCA9422_AMUXChannel_Therm:
        case kPCA9422_AMUXChannel_ThermBias:
            /* Get scale factor */
            (void)PCA9422_ReadRegs(handle, PCA9422_CHG_CNTL10, &regVal, 1U);
            scaleFactor = ((regVal & PCA9422_CHARGER_CNTL_10_AMUX_THERM_GAIN) != 0U) ? 1.5f : 1.0f;
            break;
        case kPCA9422_AMUXChannel_Vin:
            scaleFactor = 4.0f;
            break;
        default:
            scaleFactor = 0.0f;
            break;
    }
    return scaleFactor;
}

bool PCA9422_SetEnableCharge(pca9422_handle_t *handle, bool enable)
{
    uint8_t regVal = 0U;
    bool result;

    /* Write CHARGER_LOCK bit to UNLOCK */
    regVal = PCA9422_CHARGER_LOCK_UNLOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);
    if (result == false)
    {
        goto error;
    }

    if (enable == true)
    {
        /* Read USB_SUSPEND bit first */
        result = PCA9422_ReadRegs(handle, PCA9422_CHG_CNTL9, &regVal, 1U);
        if (result && ((regVal & PCA9422_CHARGER_CNTL_9_USB_SUSPEND) != 0U))
        {
            /* Disable suspend Mode first */
            regVal = 0U;
            result = PCA9422_ModifyRegReadback(handle, PCA9422_CHG_CNTL9, PCA9422_CHARGER_CNTL_9_USB_SUSPEND, regVal);
            if (result == false)
            {
                goto error;
            }
        }
    }

    regVal = (enable == true) ? PCA9422_CHARGER_CNTL_1_CHARGER_EN : 0U;
    result = PCA9422_ModifyRegReadback(handle, PCA9422_CHG_CNTL1, PCA9422_CHARGER_CNTL_1_CHARGER_EN, regVal);
    if (result == false)
    {
        goto error;
    }

    /* Write CHARGER_LOCK bit to LOCK */
    regVal = PCA9422_CHARGER_LOCK_LOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);

error:
    return result;
}

bool PCA9422_SetUSBSuspendMode(pca9422_handle_t *handle, bool enable)
{
    uint8_t regVal = 0U;
    bool result;

    /* Write CHARGER_LOCK bit to UNLOCK */
    regVal = PCA9422_CHARGER_LOCK_UNLOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);
    if (result == false)
    {
        goto error;
    }

    regVal = (enable == true) ? PCA9422_CHARGER_CNTL_9_USB_SUSPEND : 0U;
    result = PCA9422_ModifyRegReadback(handle, PCA9422_CHG_CNTL9, PCA9422_CHARGER_CNTL_9_USB_SUSPEND, regVal);
    if (result == false)
    {
        goto error;
    }

    /* Write CHARGER_LOCK bit to LOCK */
    regVal = PCA9422_CHARGER_LOCK_LOCK;
    result = PCA9422_WriteRegs(handle, PCA9422_CHG_CNTL0, &regVal, 1U);

error:
    return result;
}

/*!
 * @name Regulator Functions
 * @{
 */
void PCA9422_GetDefaultBuckConfig(pca9422_buck_config_t *buckCfg)
{
    /* Buck1/2/3 default configuration */
    /* BUCK1 default configuration */
    buckCfg[0].dvsUpStep    = 0U; /* 6.25mV */
    buckCfg[0].dvsDnStep    = 0U; /* 6.25mV */
    buckCfg[0].dvsCtrl      = (uint8_t)kPCA9422_DVS0thrI2CInActiveAndSleep;
    buckCfg[0].rampSpeed    = kPCA9422_BxRamp_25mVp2us;
    buckCfg[0].lpMode       = kPCA9422_BxLPmodeNormal;
    buckCfg[0].activeDischg = kPCA9422_BxADEnabled;
    buckCfg[0].fpwmEn       = kPCA9422_BxAutoPFMandPWM;
    buckCfg[0].enMode       = kPCA9422_EnmodeOnAll;
    buckCfg[0].dvsVout[0]   = 1000000U; /* 1.0V */
    buckCfg[0].dvsVout[1]   = 1000000U; /* 1.0V */
    buckCfg[0].dvsVout[2]   = 1000000U; /* 1.0V */
    buckCfg[0].dvsVout[3]   = 1000000U; /* 1.0V */
    buckCfg[0].dvsVout[4]   = 1000000U; /* 1.0V */
    buckCfg[0].dvsVout[5]   = 1000000U; /* 1.0V */
    buckCfg[0].dvsVout[6]   = 1000000U; /* 1.0V */
    buckCfg[0].dvsVout[7]   = 1000000U; /* 1.0V */
    buckCfg[0].stbyVout     = 1000000U; /* 1.0V */
    buckCfg[0].maxVout      = 1200000U; /* 1.2V */
    buckCfg[0].sleepVout    = 400000U;  /* 0.4V */

    /* BUCK2 default configuration */
    buckCfg[1].dvsUpStep    = 0U; /* 25mV */
    buckCfg[1].dvsDnStep    = 0U; /* 25mV */
    buckCfg[1].dvsCtrl      = (uint8_t)kPCA9422_DVS0thrI2CInActiveAndSleep;
    buckCfg[1].rampSpeed    = kPCA9422_BxRamp_25mVp2us;
    buckCfg[1].lpMode       = kPCA9422_BxLPmodeNormal;
    buckCfg[1].activeDischg = kPCA9422_BxADEnabled;
    buckCfg[1].fpwmEn       = kPCA9422_BxAutoPFMandPWM;
    buckCfg[1].enMode       = kPCA9422_EnmodeOnAll;
    buckCfg[1].dvsVout[0]   = 1100000U; /* 1.1V */
    buckCfg[1].dvsVout[1]   = 1000000U; /* 1.0V */
    buckCfg[1].dvsVout[2]   = 1000000U; /* 1.0V */
    buckCfg[1].dvsVout[3]   = 1000000U; /* 1.0V */
    buckCfg[1].dvsVout[4]   = 1000000U; /* 1.0V */
    buckCfg[1].dvsVout[5]   = 1000000U; /* 1.0V */
    buckCfg[1].dvsVout[6]   = 1000000U; /* 1.0V */
    buckCfg[1].dvsVout[7]   = 1000000U; /* 1.0V */
    buckCfg[1].stbyVout     = 1000000U; /* 1.0V */
    buckCfg[1].maxVout      = 1400000U; /* 1.4V */
    buckCfg[1].sleepVout    = 400000U;  /* 0.4V */

    /* BUCK3 default configuration */
    buckCfg[2].dvsUpStep    = 0U; /* 25mV */
    buckCfg[2].dvsDnStep    = 0U; /* 25mV */
    buckCfg[2].dvsCtrl      = (uint8_t)kPCA9422_DVS0thrI2CInActiveAndSleep;
    buckCfg[2].rampSpeed    = kPCA9422_BxRamp_25mVp2us;
    buckCfg[2].lpMode       = kPCA9422_BxLPmodeNormal;
    buckCfg[2].activeDischg = kPCA9422_BxADEnabled;
    buckCfg[2].fpwmEn       = kPCA9422_BxAutoPFMandPWM;
    buckCfg[2].enMode       = kPCA9422_EnmodeOnAll;
    buckCfg[2].dvsVout[0]   = 1000000U; /* 1.0V */
    buckCfg[2].dvsVout[1]   = 1000000U; /* 1.0V */
    buckCfg[2].dvsVout[2]   = 1000000U; /* 1.0V */
    buckCfg[2].dvsVout[3]   = 1000000U; /* 1.0V */
    buckCfg[2].dvsVout[4]   = 1000000U; /* 1.0V */
    buckCfg[2].dvsVout[5]   = 1000000U; /* 1.0V */
    buckCfg[2].dvsVout[6]   = 1000000U; /* 1.0V */
    buckCfg[2].dvsVout[7]   = 1000000U; /* 1.0V */
    buckCfg[2].stbyVout     = 1000000U; /* 1.0V */
    buckCfg[2].maxVout      = 1200000U; /* 1.2V */
    buckCfg[2].sleepVout    = 400000U;  /* 0.4V */
}

void PCA9422_GetDefaultLDO234Config(pca9422_ldo234_config_t *ldoCfg)
{
    /* LDO2/3/4 default configuration */
    /* LDO2 default configuration */
    ldoCfg[0].cSel         = kPCA9422_LDO23AutoCoutDetection;
    ldoCfg[0].llSel        = kPCA9422_LDO23LLSel15mOhm;
    ldoCfg[0].lpMode       = kPCA9422_LDO23LPmodeNormal;
    ldoCfg[0].enMode       = kPCA9422_EnmodeOnAll;
    ldoCfg[0].ldoMode      = kPCA9422_LDO23LDOMode;
    ldoCfg[0].activeDischg = true;
    ldoCfg[0].vout         = 1800000U; /* 1.8V */
    ldoCfg[0].stbyVout     = 1800000U; /* 1.8V */
    ldoCfg[0].sleepVout    = 1800000U; /* 1.8V */

    /* LDO3 default configuration */
    ldoCfg[1].cSel         = kPCA9422_LDO23AutoCoutDetection;
    ldoCfg[1].llSel        = kPCA9422_LDO23LLSel15mOhm;
    ldoCfg[1].lpMode       = kPCA9422_LDO23LPmodeNormal;
    ldoCfg[1].enMode       = kPCA9422_EnmodeOnAll;
    ldoCfg[1].ldoMode      = kPCA9422_LDO23LDOMode;
    ldoCfg[1].activeDischg = true;
    ldoCfg[1].vout         = 1200000U; /* 1.2V */
    ldoCfg[1].stbyVout     = 1200000U; /* 1.2V */
    ldoCfg[1].sleepVout    = 1200000U; /* 1.2V */

    /* LDO4 default configuration */
    ldoCfg[2].activeDischg = true;
    ldoCfg[2].enMode       = kPCA9422_EnmodeOnAll;
    ldoCfg[2].vout         = 3300000U; /* 3.3V */
    ldoCfg[2].stbyVout     = 3300000U; /* 3.3V */
    ldoCfg[2].sleepVout    = 3000000U; /* 3.0V */
}

void PCA9422_GetDefaultLDO1Config(pca9422_ldo1_config_t *ldo1Cfg)
{
    /* LDO1 default configuration */
    ldo1Cfg->activeDischg = true;
    ldo1Cfg->enMode       = true;     /* Always ON */
    ldo1Cfg->vout         = 1800000U; /* 1.8V */
}

void PCA9422_GetDefaultBBConfig(pca9422_bb_config_t *bbCfg)
{
    bbCfg->fpwmEn     = kPCA9422_BBAutoPFMandPWM;
    bbCfg->ocCtrl     = kPCA9422_BBNotTurnOff;
    bbCfg->softStdn   = kPCA9422_BBRampDownDisabled;
    bbCfg->passiveDis = kPCA9422_BBPassiveDsgEnabled;
    bbCfg->enInRun    = kPCA9422_BBOnInRunState;
    bbCfg->bbMode     = kPCA9422_BBOPmodeAuto;
    bbCfg->enMode     = kPCA9422_BBEnmodeOnAll;
    bbCfg->lpMode     = kPCA9422_BBLPmodeNormal;

    bbCfg->vout      = 1800000U; /* 1.8V */
    bbCfg->stdyVout  = 1800000U; /* 1.8V */
    bbCfg->maxVout   = 5000000U; /* 5.0V */
    bbCfg->minVout   = 1800000U; /* 1.8V */
    bbCfg->sleepVout = 1800000U; /* 1.8V */
}

void PCA9422_GetRegulatorDefaultConfig(pca9422_regulator_config_t *RegConfig)
{
    pca9422_buck_config_t buck[3];  /* buck1/2/3 */
    pca9422_ldo234_config_t ldo[3]; /* ldo2/3/4 */
    pca9422_ldo1_config_t ldo1;     /* ldo1 */
    pca9422_bb_config_t buckBoost;  /* buck-boost */

    /* Buck1/2/3 default configuration */
    PCA9422_GetDefaultBuckConfig(buck);

    /* LDO2/3/4 default configuration */
    PCA9422_GetDefaultLDO234Config(ldo);

    /* LDO1 default configuration */
    PCA9422_GetDefaultLDO1Config(&ldo1);

    /* Buck-Boost default configuration */
    PCA9422_GetDefaultBBConfig(&buckBoost);

    RegConfig->I2C_SendFunc    = NULL;
    RegConfig->I2C_ReceiveFunc = NULL;
    RegConfig->standbyCtrl     = kPCA9422_StandbyCtrlPins;
    RegConfig->standbyCfg      = kPCA9422_StandbyCfgStandby;
    RegConfig->dvsCtrl2En      = kPCA9422_DVSCtrl2PinIgnore;
    RegConfig->vsysUvlo        = kPCA9422_VsysUVLOSel2p7V;
    RegConfig->smartMode       = kPCA9422_SmartModeDisabled;
    RegConfig->buck[0]         = buck[0];
    RegConfig->buck[1]         = buck[1];
    RegConfig->buck[2]         = buck[2];
    RegConfig->ldo[0]          = ldo[0];
    RegConfig->ldo[1]          = ldo[1];
    RegConfig->ldo[2]          = ldo[2];
    RegConfig->ldo1            = ldo1;
    RegConfig->buckBoost       = buckBoost;
    RegConfig->slaveAddress    = PCA9422_DEFAULT_I2C_ADDR;
}

void PCA9422_InitRegulator(pca9422_handle_t *handle, const pca9422_regulator_config_t *config)
{
    uint8_t regVal, regAddr;
    uint8_t bxDVS[8];
    bool result;
    uint32_t i;

    assert(handle);
    assert(config);

    /* Initialize Callback functions. */
    handle->I2C_SendFunc    = config->I2C_SendFunc;
    handle->I2C_ReceiveFunc = config->I2C_ReceiveFunc;
    /* Set Slave Address. */
    handle->slaveAddress = config->slaveAddress;

    /* INT1_MASK */
    regVal  = 0xFFU;
    regAddr = PCA9422_INT1_MASK;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* RESET_CTRL */
    regVal  = 0x00U;
    regAddr = PCA9422_RESET_CTRL;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* PWR_SEQ_CTRL */
    regVal  = 0x06U;
    regAddr = PCA9422_PWR_SEQ_CTRL;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* SYS_CFG1 */
    regVal  = (uint8_t)config->standbyCtrl | (uint8_t)config->standbyCfg | (uint8_t)config->dvsCtrl2En;
    regAddr = PCA9422_SYS_CFG1;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* SYS_CFG2 */
    regVal  = (uint8_t)kPCA9422_PowerSaveNormal | (uint8_t)kPCA9422_GPIOPullupLDO1 | (uint8_t)config->vsysUvlo;
    regAddr = PCA9422_SYS_CFG2;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* BUCK123_DVS_CFG1 */
    regVal =
        (uint8_t)((config->buck[0].dvsUpStep << 7U) | (config->buck[0].dvsDnStep << 6U) |
                  (config->buck[1].dvsUpStep << 5U) | (config->buck[1].dvsDnStep << 4U) | (uint8_t)(config->smartMode));
    regAddr = PCA9422_BUCK123_DVS_CFG1;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* BUCK123_DVS_CFG2 */
    regVal =
        (uint8_t)((config->buck[0].dvsCtrl << 6U) | (config->buck[1].dvsCtrl << 4U) | (config->buck[2].dvsCtrl << 2U) |
                  (config->buck[2].dvsUpStep << 1U) | (config->buck[2].dvsDnStep << 0U));
    regAddr = PCA9422_BUCK123_DVS_CFG2;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* BUCK1CTRL */
    regVal = (uint8_t)(config->buck[0].rampSpeed) | (uint8_t)(config->buck[0].lpMode) |
             (uint8_t)(config->buck[0].activeDischg) | (uint8_t)(config->buck[0].fpwmEn) |
             (uint8_t)(config->buck[0].enMode);
    regAddr = PCA9422_BUCK1CTRL;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* BUCK2CTRL */
    regVal = (uint8_t)(config->buck[1].rampSpeed) | (uint8_t)(config->buck[1].lpMode) |
             (uint8_t)(config->buck[1].activeDischg) | (uint8_t)(config->buck[1].fpwmEn) |
             (uint8_t)(config->buck[1].enMode);
    regAddr = PCA9422_BUCK2CTRL;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* BUCK3CTRL */
    regVal = (uint8_t)(config->buck[2].rampSpeed) | (uint8_t)(config->buck[2].lpMode) |
             (uint8_t)(config->buck[2].activeDischg) | (uint8_t)(uint8_t)(config->buck[2].fpwmEn) |
             (uint8_t)(config->buck[2].enMode);
    regAddr = PCA9422_BUCK3CTRL;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* BUCK1OUT_DVS */
    for (i = 0U; i < 8U; i++)
    {
        bxDVS[i] = (uint8_t)PCA9422_BUCK1_OUT_VAL(config->buck[0].dvsVout[i]);
    }
    regAddr = PCA9422_BUCK1OUT_DVS0;
    result  = PCA9422_WriteRegs(handle, regAddr, bxDVS, 8U);
    if (result == false)
    {
        goto out;
    }
    /* BUCK2OUT_DVS */
    for (i = 0U; i < 8U; i++)
    {
        bxDVS[i] = (uint8_t)PCA9422_BUCK2_OUT_VAL(config->buck[1].dvsVout[i]);
    }
    regAddr = PCA9422_BUCK2OUT_DVS0;
    result  = PCA9422_WriteRegs(handle, regAddr, bxDVS, 8U);
    if (result == false)
    {
        goto out;
    }
    /* BUCK3OUT_DVS */
    for (i = 0U; i < 8U; i++)
    {
        bxDVS[i] = (uint8_t)PCA9422_BUCK3_OUT_VAL(config->buck[2].dvsVout[i]);
    }
    regAddr = PCA9422_BUCK3OUT_DVS0;
    result  = PCA9422_WriteRegs(handle, regAddr, bxDVS, 8U);
    if (result == false)
    {
        goto out;
    }
    /* REG_LOCK - UNLOCK KEY */
    regVal  = (uint8_t)kPCA9422_RegLockUnlockKey;
    regAddr = PCA9422_REG_LOCK;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* BUCK1OUT_STBY */
    regVal  = (uint8_t)PCA9422_BUCK1_OUT_VAL(config->buck[0].stbyVout);
    regAddr = PCA9422_BUCK1OUT_STBY;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* PCA9422_BUCK1OUT_MAX_LIMIT */
    regVal  = (uint8_t)PCA9422_BUCK1_OUT_VAL(config->buck[0].maxVout);
    regAddr = PCA9422_BUCK1OUT_MAX_LIMIT;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* BUCK1OUT_SLEEP */
    regVal  = (uint8_t)PCA9422_BUCK1_OUT_VAL(config->buck[0].sleepVout);
    regAddr = PCA9422_BUCK1OUT_SLEEP;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* BUCK2OUT_STBY */
    regVal  = (uint8_t)PCA9422_BUCK2_OUT_VAL(config->buck[1].stbyVout);
    regAddr = PCA9422_BUCK2OUT_STBY;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* BUCK2OUT_MAX_LIMIT */
    regVal  = (uint8_t)PCA9422_BUCK2_OUT_VAL(config->buck[1].maxVout);
    regAddr = PCA9422_BUCK2OUT_MAX_LIMIT;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* BUCK2OUT_SLEEP */
    regVal  = (uint8_t)PCA9422_BUCK2_OUT_VAL(config->buck[1].sleepVout);
    regAddr = PCA9422_BUCK2OUT_SLEEP;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* BUCK3OUT_STBY */
    regVal  = (uint8_t)PCA9422_BUCK3_OUT_VAL(config->buck[2].stbyVout);
    regAddr = PCA9422_BUCK3OUT_STBY;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* BUCK3OUT_MAX_LIMIT */
    regVal  = (uint8_t)PCA9422_BUCK3_OUT_VAL(config->buck[2].maxVout);
    regAddr = PCA9422_BUCK3OUT_MAX_LIMIT;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* BUCK3OUT_SLEEP */
    regVal  = (uint8_t)PCA9422_BUCK3_OUT_VAL(config->buck[2].sleepVout);
    regAddr = PCA9422_BUCK3OUT_SLEEP;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* LDO2_CFG */
    regVal = (uint8_t)config->ldo[0].cSel | (uint8_t)config->ldo[0].llSel | (uint8_t)config->ldo[0].lpMode |
             (uint8_t)config->ldo[0].enMode;
    regAddr = PCA9422_LDO2_CFG;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* LDO2_OUT */
    regVal =((uint8_t)config->ldo[0].activeDischg << 7U) | (uint8_t)PCA9422_LDO23_OUT_VAL(config->ldo[0].vout);
    regAddr = PCA9422_LDO2_OUT;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* LDO2_OUT_STBY */
    regVal  = (uint8_t)PCA9422_LDO23_OUT_VAL(config->ldo[0].stbyVout);
    regAddr = PCA9422_LDO2_OUT_STBY;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* LDO2_OUT_SLEEP */
    regVal  = (uint8_t)PCA9422_LDO23_OUT_VAL(config->ldo[0].sleepVout);
    regAddr = PCA9422_LDO2_OUT_SLEEP;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* LDO3_CFG */
    regVal = (uint8_t)config->ldo[1].cSel | (uint8_t)config->ldo[1].llSel | (uint8_t)config->ldo[1].lpMode |
             (uint8_t)config->ldo[1].enMode;
    regAddr = PCA9422_LDO3_CFG;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* LDO3_OUT */
    regVal  = (uint8_t)(((uint32_t)config->ldo[1].activeDischg << 7UL) | PCA9422_LDO23_OUT_VAL(config->ldo[1].vout));
    regAddr = PCA9422_LDO3_OUT;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* LDO3_OUT_STBY */
    regVal  = (uint8_t)PCA9422_LDO23_OUT_VAL(config->ldo[1].stbyVout);
    regAddr = PCA9422_LDO3_OUT_STBY;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* LDO3_OUT_SLEEP */
    regVal  = (uint8_t)PCA9422_LDO23_OUT_VAL(config->ldo[1].sleepVout);
    regAddr = PCA9422_LDO3_OUT_SLEEP;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* LDO23_CFG */
    regVal  = ((uint8_t)(config->ldo[0].ldoMode) << 6U) | ((uint8_t)(config->ldo[1].ldoMode) << 7U);
    regAddr = PCA9422_LDO23_CFG;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* LDO4_CFG */
    regVal  = ((uint8_t)config->ldo[2].activeDischg << 4U) | ((uint8_t)(config->ldo[2].enMode));
    regAddr = PCA9422_LDO4_CFG;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* LDO4_OUT */
    regVal  = (uint8_t)PCA9422_LDO4_OUT_VAL(config->ldo[2].vout);
    regAddr = PCA9422_LDO4_OUT;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* LDO4_OUT_STBY */
    regVal  = (uint8_t)PCA9422_LDO4_OUT_VAL(config->ldo[2].stbyVout);
    regAddr = PCA9422_LDO4_OUT_STBY;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* LDO4_OUT_SLEEP */
    regVal  = (uint8_t)PCA9422_LDO4_OUT_VAL(config->ldo[2].sleepVout);
    regAddr = PCA9422_LDO4_OUT_SLEEP;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* LDO1_CFG1 */
    regVal  = (uint8_t)(((uint32_t)config->ldo1.activeDischg << 7UL) | PCA9422_LDO1_OUT_VAL(config->ldo1.vout));
    regAddr = PCA9422_LDO1_CFG1;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* LDO1_CFG2 */
    regVal  = (uint8_t)config->ldo1.enMode;
    regAddr = PCA9422_LDO1_CFG2;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* SW4_BB_CFG1 */
    regVal = (uint8_t)config->buckBoost.fpwmEn | (uint8_t)config->buckBoost.ocCtrl |
             (uint8_t)config->buckBoost.softStdn | (uint8_t)config->buckBoost.passiveDis;
    regAddr = PCA9422_SW4_BB_CFG1;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* SW4_BB_CFG2 */
    regVal = (uint8_t)config->buckBoost.enInRun | (uint8_t)config->buckBoost.bbMode |
             (uint8_t)config->buckBoost.enMode | (uint8_t)config->buckBoost.lpMode;
    regAddr = PCA9422_SW4_BB_CFG2;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* SW4_BB_CFG3 - BB_VOUT */
    regVal  = (uint8_t)PCA9422_BB_OUT_VAL(config->buckBoost.vout);
    regAddr = PCA9422_SW4_BB_CFG3;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* SW4_BB_CFG4 - BB_VOUT_STBY */
    regVal  = (uint8_t)PCA9422_BB_OUT_VAL(config->buckBoost.stdyVout);
    regAddr = PCA9422_SW4_BB_CFG4;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* SW4_BB_MAX_LIMIT */
    regVal  = (uint8_t)PCA9422_BB_OUT_VAL(config->buckBoost.maxVout);
    regAddr = PCA9422_SW4_BB_MAX_LIMIT;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* SW4_BB_MIN_LIMIT */
    regVal  = (uint8_t)PCA9422_BB_OUT_VAL(config->buckBoost.minVout);
    regAddr = PCA9422_SW4_BB_MIN_LIMIT;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* SW4_BB_VOUT_SLEEP */
    regVal  = (uint8_t)PCA9422_BB_OUT_VAL(config->buckBoost.sleepVout);
    regAddr = PCA9422_SW4_BB_VOUT_SLEEP;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    /* REG_LOCK - LOCK KEY */
    regVal  = (uint8_t)kPCA9422_RegLockLockKey;
    regAddr = PCA9422_REG_LOCK;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }
    return;

out:
    LOG_INFO("Error I2C data write[0x%2X]\r\n", regAddr);
    return;
}

void PCA9422_GetDefaultPowerModeConfig(pca9422_modecfg_t *config)
{
    /* SW1 output set to 1.0V. */
    config->sw1OutVolt = 1000000U;
    /* SW2 output set to 1.1V. */
    config->sw2OutVolt = 1100000U;
    /* SW3 output set to 1.0V. */
    config->sw3OutVolt = 1000000U;
    /* SW4 output set to 1.8V. */
    config->sw4OutVolt = 1800000U;
    /* LDO1 output set to 1.8V. */
    config->ldo1OutVolt = 1800000U;
    /* LDO2 output set to 1.8V. */
    config->ldo2OutVolt = 1800000U;
    /* LDO3 output set to 1.2V. */
    config->ldo3OutVolt = 1200000U;
    /* LDO4 output set to 3.3V. */
    config->ldo4OutVolt = 3300000U;
}

void PCA9422_GetDefaultEnModeConfig(pca9422_enmodecfg_t *enModeCfg)
{
    /* Enable mode is always ON in all regulators */
    enModeCfg->sw1OutEnMode  = kPCA9422_EnmodeOnAll;
    enModeCfg->sw2OutEnMode  = kPCA9422_EnmodeOnAll;
    enModeCfg->sw3OutEnMode  = kPCA9422_EnmodeOnAll;
    enModeCfg->sw4OutEnMode  = kPCA9422_EnmodeOnAll;
    enModeCfg->ldo1OutEnMode = kPCA9422_EnmodeOnAll;
    enModeCfg->ldo2OutEnMode = kPCA9422_EnmodeOnAll;
    enModeCfg->ldo3OutEnMode = kPCA9422_EnmodeOnAll;
    enModeCfg->ldo4OutEnMode = kPCA9422_EnmodeOnAll;
}

void PCA9422_GetDefaultRegEnableConfig(pca9422_regulatoren_t *regEnCfg)
{
    /* All regulators enable in RUN state. */
    regEnCfg->sw1Enable  = true;
    regEnCfg->sw2Enable  = true;
    regEnCfg->sw3Enable  = true;
    regEnCfg->sw4Enable  = true;
    regEnCfg->ldo1Enable = true;
    regEnCfg->ldo2Enable = true;
    regEnCfg->ldo3Enable = true;
    regEnCfg->ldo4Enable = true;
}

void PCA9422_GetLDO1EnMode(pca9422_handle_t *handle, bool *enmode)
{
    bool result;
    uint8_t regVal;

    result = PCA9422_ReadRegs(handle, PCA9422_LDO1_CFG2, &regVal, 1U);
    if (result == false)
    {
        LOG_INFO("Error I2C data Read[0x4A]\r\n");
    }
    else
    {
        *enmode = ((regVal & PCA9422_LDO1_CFG2_L1_ENMODE) != 0U) ? true : false;
    }
}

void PCA9422_SetLDO1EnMode(pca9422_handle_t *handle, bool enmode)
{
    bool result;

    result = PCA9422_ModifyReg(handle, PCA9422_LDO1_CFG2, PCA9422_LDO1_CFG2_L1_ENMODE, (uint8_t)enmode);
    if (result == false)
    {
        LOG_INFO("Error I2C data write[0x4A]\r\n");
    }
}

void PCA9422_GetRegulatorEnMode(pca9422_handle_t *handle, pca9422_regulator_t reg, pca9422_enmode_t *enmode)
{
    uint8_t regVal, regAddr;
    bool result, ldo1EnMode = false;

    switch (reg)
    {
        case kPCA9422_RegulatorSwitch1:
            /* Read BUCK1CTRL */
            regAddr = PCA9422_BUCK1CTRL;
            result  = PCA9422_ReadRegs(handle, regAddr, &regVal, 1U);
            if (result == false)
            {
                goto out;
            }
            regVal  = regVal & PCA9422_BUCKXCTRL_BX_ENMODE;
            *enmode = (pca9422_enmode_t)regVal;
            break;
        case kPCA9422_RegulatorSwitch2:
            /* Read BUCK2CTRL */
            regAddr = PCA9422_BUCK2CTRL;
            result  = PCA9422_ReadRegs(handle, regAddr, &regVal, 1U);
            if (result == false)
            {
                goto out;
            }
            regVal  = regVal & PCA9422_BUCKXCTRL_BX_ENMODE;
            *enmode = (pca9422_enmode_t)regVal;
            break;
        case kPCA9422_RegulatorSwitch3:
            /* Read BUCK3CTRL */
            regAddr = PCA9422_BUCK3CTRL;
            result  = PCA9422_ReadRegs(handle, regAddr, &regVal, 1U);
            if (result == false)
            {
                goto out;
            }
            regVal  = regVal & PCA9422_BUCKXCTRL_BX_ENMODE;
            *enmode = (pca9422_enmode_t)regVal;
            break;
        case kPCA9422_RegulatorSwitch4:
            /* Read SW4_BB_CFG2 */
            regAddr = PCA9422_SW4_BB_CFG2;
            result  = PCA9422_ReadRegs(handle, regAddr, &regVal, 1U);
            if (result == false)
            {
                goto out;
            }
            regVal  = (regVal & PCA9422_SW4_BB_CFG2_BB_ENMODE) >> 2U;
            *enmode = (pca9422_enmode_t)(regVal);
            break;
        case kPCA9422_RegulatorLdo1:
            /* LDO1 ENMODE just has always on or off.
             * If it is always on mode, enmode will set kPCA9422_EnmodeOnAll
             * and if it is off, enmode will set kPCA9422_EnmodeOnActive */
            PCA9422_GetLDO1EnMode(handle, &ldo1EnMode);
            *enmode = ldo1EnMode ? kPCA9422_EnmodeOnAll : kPCA9422_EnmodeOnActive;
            break;
        case kPCA9422_RegulatorLdo2:
            /* Read LDO2_CFG */
            regAddr = PCA9422_LDO2_CFG;
            result  = PCA9422_ReadRegs(handle, regAddr, &regVal, 1U);
            if (result == false)
            {
                goto out;
            }
            regVal  = regVal & PCA9422_LDO2_CFG_L2_ENMODE;
            *enmode = (pca9422_enmode_t)regVal;
            break;
        case kPCA9422_RegulatorLdo3:
            /* Read LDO3_CFG */
            regAddr = PCA9422_LDO3_CFG;
            result  = PCA9422_ReadRegs(handle, regAddr, &regVal, 1U);
            if (result == false)
            {
                goto out;
            }
            regVal  = regVal & PCA9422_LDO3_CFG_L3_ENMODE;
            *enmode = (pca9422_enmode_t)regVal;
            break;
        case kPCA9422_RegulatorLdo4:
            /* Read LDO4_CFG */
            regAddr = PCA9422_LDO4_CFG;
            result  = PCA9422_ReadRegs(handle, regAddr, &regVal, 1U);
            if (result == false)
            {
                goto out;
            }
            regVal  = regVal & PCA9422_LDO4_CFG_L4_ENMODE;
            *enmode = (pca9422_enmode_t)regVal;
            break;
        default:
            LOG_INFO("Error Invalid regulator\r\n");
            *enmode = (pca9422_enmode_t)kPCA9422_EnmodeOnAll;
            break;
    }
    return;

out:
    LOG_INFO("Error I2C data read[0x%2X]\r\n", regAddr);
    return;
}

void PCA9422_SetRegulatorEnMode(pca9422_handle_t *handle, pca9422_regulator_t reg, pca9422_enmode_t enmode)
{
    uint8_t regVal, regAddr, regMask;
    bool result, ldo1EnMode;

    switch (reg)
    {
        case kPCA9422_RegulatorSwitch1:
            /* Write BUCK1CTRL */
            regAddr = PCA9422_BUCK1CTRL;
            regVal  = (uint8_t)enmode;
            regMask = PCA9422_BUCKXCTRL_BX_ENMODE;
            break;
        case kPCA9422_RegulatorSwitch2:
            /* Write BUCK2CTRL */
            regAddr = PCA9422_BUCK2CTRL;
            regVal  = (uint8_t)enmode;
            regMask = PCA9422_BUCKXCTRL_BX_ENMODE;
            break;
        case kPCA9422_RegulatorSwitch3:
            /* Write BUCK3CTRL */
            regAddr = PCA9422_BUCK3CTRL;
            regVal  = (uint8_t)enmode;
            regMask = PCA9422_BUCKXCTRL_BX_ENMODE;
            break;
        case kPCA9422_RegulatorSwitch4:
            /* Write SW4_BB_CFG2 */
            regAddr = PCA9422_SW4_BB_CFG2;
            regVal  = (uint8_t)enmode << 2U;
            regMask = PCA9422_SW4_BB_CFG2_BB_ENMODE;
            break;
        case kPCA9422_RegulatorLdo1:
            /* Set LDO1 with PCA9422_SeLDO1EnMode function */
            ldo1EnMode = (enmode == kPCA9422_EnmodeOnAll) ? true : false;
            PCA9422_SetLDO1EnMode(handle, ldo1EnMode);
            regAddr = 0xFF;
            break;
        case kPCA9422_RegulatorLdo2:
            /* Write LDO2_CFG */
            regAddr = PCA9422_LDO2_CFG;
            regVal  = (uint8_t)enmode;
            regMask = PCA9422_LDO2_CFG_L2_ENMODE;
            break;
        case kPCA9422_RegulatorLdo3:
            /* Write LDO3_CFG */
            regAddr = PCA9422_LDO3_CFG;
            regVal  = (uint8_t)enmode;
            regMask = PCA9422_LDO3_CFG_L3_ENMODE;
            break;
        case kPCA9422_RegulatorLdo4:
            /* Write LDO4_CFG */
            regAddr = PCA9422_LDO4_CFG;
            regVal  = (uint8_t)enmode;
            regMask = PCA9422_LDO4_CFG_L4_ENMODE;
            break;
        default:
            LOG_INFO("Error Invalid regulator\r\n");
            regAddr = 0xFFU;
            break;
    }

    if (regAddr != 0xFFU)
    {
        result = PCA9422_ModifyReg(handle, regAddr, regMask, regVal);
        if (result == false)
        {
            LOG_INFO("Error I2C data write[0x%2X]\r\n", regAddr);
        }
    }
}

void PCA9422_GetRegulatorLPMode(pca9422_handle_t *handle, pca9422_regulator_t reg, pca9422_reg_lpmode_t *lpmode)
{
    uint8_t regVal, regAddr;
    bool result;

    switch (reg)
    {
        case kPCA9422_RegulatorSwitch1:
            /* Read BUCK1CTRL */
            regAddr = PCA9422_BUCK1CTRL;
            result  = PCA9422_ReadRegs(handle, regAddr, &regVal, 1U);
            if (result == false)
            {
                goto out;
            }
            regVal  = (regVal & PCA9422_BUCKXCTRL_BX_LPMODE) >> 4U;
            *lpmode = (pca9422_reg_lpmode_t)regVal;
            break;
        case kPCA9422_RegulatorSwitch2:
            /* Read BUCK2CTRL */
            regAddr = PCA9422_BUCK2CTRL;
            result  = PCA9422_ReadRegs(handle, regAddr, &regVal, 1U);
            if (result == false)
            {
                goto out;
            }
            regVal  = (regVal & PCA9422_BUCKXCTRL_BX_LPMODE) >> 4U;
            *lpmode = (pca9422_reg_lpmode_t)regVal;
            break;
        case kPCA9422_RegulatorSwitch3:
            /* Read BUCK3CTRL */
            regAddr = PCA9422_BUCK3CTRL;
            result  = PCA9422_ReadRegs(handle, regAddr, &regVal, 1U);
            if (result == false)
            {
                goto out;
            }
            regVal  = (regVal & PCA9422_BUCKXCTRL_BX_LPMODE) >> 4U;
            *lpmode = (pca9422_reg_lpmode_t)regVal;
            break;
        case kPCA9422_RegulatorSwitch4:
            /* Read SW4_BB_CFG2 */
            regAddr = PCA9422_SW4_BB_CFG2;
            result  = PCA9422_ReadRegs(handle, regAddr, &regVal, 1U);
            if (result == false)
            {
                goto out;
            }
            regVal  = regVal & PCA9422_SW4_BB_CFG2_BB_LPMODE;
            *lpmode = (pca9422_reg_lpmode_t)regVal;
            break;
        case kPCA9422_RegulatorLdo1:
            /* There is no low power mode */
            *lpmode = (pca9422_reg_lpmode_t)kPCA9422_LPmodeNormal;
            LOG_INFO("Error LDO1 doesn't support LP mode\r\n");
            break;
        case kPCA9422_RegulatorLdo2:
            /* Read LDO2_CFG */
            regAddr = PCA9422_LDO2_CFG;
            result  = PCA9422_ReadRegs(handle, regAddr, &regVal, 1U);
            if (result == false)
            {
                goto out;
            }
            regVal  = regVal & PCA9422_LDO2_CFG_L2_LPMODE;
            *lpmode = (pca9422_reg_lpmode_t)regVal;
            if (regVal == (uint8_t)kPCA9422_LDO23LPmodeAtRunState)
            {
                *lpmode = (pca9422_reg_lpmode_t)kPCA9422_LPmodeForcedLPM;
            }
            else if (regVal == (uint8_t)kPCA9422_LDO23LPmodeAtStandbyDPStandby)
            {
                *lpmode = (pca9422_reg_lpmode_t)kPCA9422_LPmodeAtStandbyDPStandby;
            }
            else if (regVal == (uint8_t)kPCA9422_LDO23LPmodeAtDPStandby)
            {
                *lpmode = (pca9422_reg_lpmode_t)kPCA9422_LPpmodeAtDPstandby;
            }
            else
            {
                *lpmode = (pca9422_reg_lpmode_t)kPCA9422_LPmodeNormal;
            }
            break;
        case kPCA9422_RegulatorLdo3:
            /* Read LDO3_CFG */
            regAddr = PCA9422_LDO3_CFG;
            result  = PCA9422_ReadRegs(handle, regAddr, &regVal, 1U);
            if (result == false)
            {
                goto out;
            }
            regVal  = regVal & PCA9422_LDO3_CFG_L3_LPMODE;
            *lpmode = (pca9422_reg_lpmode_t)regVal;
            if (regVal == (uint8_t)kPCA9422_LDO23LPmodeAtRunState)
            {
                *lpmode = (pca9422_reg_lpmode_t)kPCA9422_LPmodeForcedLPM;
            }
            else if (regVal == (uint8_t)kPCA9422_LDO23LPmodeAtStandbyDPStandby)
            {
                *lpmode = (pca9422_reg_lpmode_t)kPCA9422_LPmodeAtStandbyDPStandby;
            }
            else if (regVal == (uint8_t)kPCA9422_LDO23LPmodeAtDPStandby)
            {
                *lpmode = (pca9422_reg_lpmode_t)kPCA9422_LPpmodeAtDPstandby;
            }
            else
            {
                *lpmode = (pca9422_reg_lpmode_t)kPCA9422_LPmodeNormal;
            }
            break;
        case kPCA9422_RegulatorLdo4:
            /* There is no low power mode */
            *lpmode = (pca9422_reg_lpmode_t)kPCA9422_LPmodeNormal;
            LOG_INFO("Error LDO4 doesn't support LP mode\r\n");
            break;
        default:
            LOG_INFO("Error Invalid regulator\r\n");
            *lpmode = (pca9422_reg_lpmode_t)kPCA9422_LPmodeNormal;
            break;
    }
    return;

out:
    LOG_INFO("Error I2C data read[0x%2X]\r\n", regAddr);
    return;
}

void PCA9422_SetRegulatorLPMode(pca9422_handle_t *handle, pca9422_regulator_t reg, pca9422_reg_lpmode_t lpmode)
{
    uint8_t regVal, regAddr, regMask;
    bool result;

    switch (reg)
    {
        case kPCA9422_RegulatorSwitch1:
            /* Write BUCK1CTRL */
            regAddr = PCA9422_BUCK1CTRL;
            regVal  = (uint8_t)lpmode << 4U;
            regMask = PCA9422_BUCKXCTRL_BX_LPMODE;
            break;
        case kPCA9422_RegulatorSwitch2:
            /* Write BUCK2CTRL */
            regAddr = PCA9422_BUCK2CTRL;
            regVal  = (uint8_t)lpmode << 4U;
            regMask = PCA9422_BUCKXCTRL_BX_LPMODE;
            break;
        case kPCA9422_RegulatorSwitch3:
            /* Write BUCK3CTRL */
            regAddr = PCA9422_BUCK3CTRL;
            regVal  = (uint8_t)lpmode << 4U;
            regMask = PCA9422_BUCKXCTRL_BX_LPMODE;
            break;
        case kPCA9422_RegulatorSwitch4:
            /* Write SW4_BB_CFG2 */
            regAddr = PCA9422_SW4_BB_CFG2;
            regVal  = (uint8_t)lpmode;
            regMask = PCA9422_SW4_BB_CFG2_BB_LPMODE;
            break;
        case kPCA9422_RegulatorLdo1:
            /* There is no low power mode */
            LOG_INFO("Error LDO1 doesn't support LP mode\r\n");
            regAddr = 0xFFU;
            break;
        case kPCA9422_RegulatorLdo2:
            /* Write LDO2_CFG */
            regAddr = PCA9422_LDO2_CFG;
            if (lpmode == kPCA9422_LPmodeForcedLPM)
            {
                regVal = (uint8_t)kPCA9422_LDO23LPmodeAtRunState;
            }
            else if (lpmode == kPCA9422_LPmodeAtStandbyDPStandby)
            {
                regVal = (uint8_t)kPCA9422_LDO23LPmodeAtStandbyDPStandby;
            }
            else if (lpmode == kPCA9422_LPpmodeAtDPstandby)
            {
                regVal = (uint8_t)kPCA9422_LDO23LPmodeAtDPStandby;
            }
            else
            {
                regVal = (uint8_t)kPCA9422_LDO23LPmodeNormal;
            }
            regMask = PCA9422_LDO2_CFG_L2_LPMODE;
            break;
        case kPCA9422_RegulatorLdo3:
            /* Write LDO3_CFG */
            regAddr = PCA9422_LDO3_CFG;
            if (lpmode == kPCA9422_LPmodeForcedLPM)
            {
                regVal = (uint8_t)kPCA9422_LDO23LPmodeAtRunState;
            }
            else if (lpmode == kPCA9422_LPmodeAtStandbyDPStandby)
            {
                regVal = (uint8_t)kPCA9422_LDO23LPmodeAtStandbyDPStandby;
            }
            else if (lpmode == kPCA9422_LPpmodeAtDPstandby)
            {
                regVal = (uint8_t)kPCA9422_LDO23LPmodeAtDPStandby;
            }
            else
            {
                regVal = (uint8_t)kPCA9422_LDO23LPmodeNormal;
            }
            regMask = PCA9422_LDO3_CFG_L3_LPMODE;
            break;
        case kPCA9422_RegulatorLdo4:
            /* There is no low power mode */
            LOG_INFO("Error LDO4 doesn't support LP mode\r\n");
            regAddr = 0xFFU;
            break;
        default:
            LOG_INFO("Error Invalid regulator\r\n");
            regAddr = 0xFFU;
            break;
    }

    if (regAddr != 0xFFU)
    {
        result = PCA9422_ModifyReg(handle, regAddr, regMask, regVal);
        if (result == false)
        {
            LOG_INFO("Error I2C data write[0x%2X]\r\n", regAddr);
        }
    }
    return;
}

void PCA9422_SetRegulatorVoltage(pca9422_handle_t *handle, pca9422_regulator_t reg, pca9422_vout_t vout, uint32_t volt)
{
    uint8_t regVal, regAddr, regMask;
    bool result;

    /* REG_LOCK - UNLOCK KEY */
    regVal  = (uint8_t)kPCA9422_RegLockUnlockKey;
    regAddr = PCA9422_REG_LOCK;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }

    switch (reg)
    {
        case kPCA9422_RegulatorSwitch1:
            regVal  = (uint8_t)PCA9422_BUCK1_OUT_VAL(volt);
            regMask = PCA9422_BUCKXOUT_DVS0_BX_DVS0;
            /* Check VOUT type */
            switch (vout)
            {
                case kPCA9422_RegSleepVout:
                    regAddr = PCA9422_BUCK1OUT_SLEEP;
                    break;
                case kPCA9422_RegStandbyVout:
                    regAddr = PCA9422_BUCK1OUT_STBY;
                    break;
                case kPCA9422_SWMaxVout:
                    regAddr = PCA9422_BUCK1OUT_MAX_LIMIT;
                    break;
                case kPCA9422_SWDVS0Vout:
                    regAddr = PCA9422_BUCK1OUT_DVS0;
                    break;
                case kPCA9422_SWDVS1Vout:
                    regAddr = PCA9422_BUCK1OUT_DVS1;
                    break;
                case kPCA9422_SWDVS2Vout:
                    regAddr = PCA9422_BUCK1OUT_DVS2;
                    break;
                case kPCA9422_SWDVS3Vout:
                    regAddr = PCA9422_BUCK1OUT_DVS3;
                    break;
                case kPCA9422_SWDVS4Vout:
                    regAddr = PCA9422_BUCK1OUT_DVS4;
                    break;
                case kPCA9422_SWDVS5Vout:
                    regAddr = PCA9422_BUCK1OUT_DVS5;
                    break;
                case kPCA9422_SWDVS6Vout:
                    regAddr = PCA9422_BUCK1OUT_DVS6;
                    break;
                case kPCA9422_SWDVS7Vout:
                    regAddr = PCA9422_BUCK1OUT_DVS7;
                    break;
                default:
                    /* Not support */
                    regAddr = 0xFFU;
                    LOG_INFO("Error - SW1 doesn't support vout type(%d)\r\n", vout);
                    break;
            }
            break;

        case kPCA9422_RegulatorSwitch2:
            regVal  = (uint8_t)PCA9422_BUCK2_OUT_VAL(volt);
            regMask = PCA9422_BUCKXOUT_DVS0_BX_DVS0;
            /* Check VOUT type */
            switch (vout)
            {
                case kPCA9422_RegSleepVout:
                    regAddr = PCA9422_BUCK2OUT_SLEEP;
                    break;
                case kPCA9422_RegStandbyVout:
                    regAddr = PCA9422_BUCK2OUT_STBY;
                    break;
                case kPCA9422_SWMaxVout:
                    regAddr = PCA9422_BUCK2OUT_MAX_LIMIT;
                    break;
                case kPCA9422_SWDVS0Vout:
                    regAddr = PCA9422_BUCK2OUT_DVS0;
                    break;
                case kPCA9422_SWDVS1Vout:
                    regAddr = PCA9422_BUCK2OUT_DVS1;
                    break;
                case kPCA9422_SWDVS2Vout:
                    regAddr = PCA9422_BUCK2OUT_DVS2;
                    break;
                case kPCA9422_SWDVS3Vout:
                    regAddr = PCA9422_BUCK2OUT_DVS3;
                    break;
                case kPCA9422_SWDVS4Vout:
                    regAddr = PCA9422_BUCK2OUT_DVS4;
                    break;
                case kPCA9422_SWDVS5Vout:
                    regAddr = PCA9422_BUCK2OUT_DVS5;
                    break;
                case kPCA9422_SWDVS6Vout:
                    regAddr = PCA9422_BUCK2OUT_DVS6;
                    break;
                case kPCA9422_SWDVS7Vout:
                    regAddr = PCA9422_BUCK2OUT_DVS7;
                    break;
                default:
                    /* Not support */
                    regAddr = 0xFFU;
                    LOG_INFO("Error - SW2 doesn't support vout type(%d)\r\n", vout);
                    break;
            }
            break;

        case kPCA9422_RegulatorSwitch3:
            regVal  = (uint8_t)PCA9422_BUCK3_OUT_VAL(volt);
            regMask = PCA9422_BUCKXOUT_DVS0_BX_DVS0;
            /* Check VOUT type */
            switch (vout)
            {
                case kPCA9422_RegSleepVout:
                    regAddr = PCA9422_BUCK3OUT_SLEEP;
                    break;
                case kPCA9422_RegStandbyVout:
                    regAddr = PCA9422_BUCK3OUT_STBY;
                    break;
                case kPCA9422_SWMaxVout:
                    regAddr = PCA9422_BUCK3OUT_MAX_LIMIT;
                    break;
                case kPCA9422_SWDVS0Vout:
                    regAddr = PCA9422_BUCK3OUT_DVS0;
                    break;
                case kPCA9422_SWDVS1Vout:
                    regAddr = PCA9422_BUCK3OUT_DVS1;
                    break;
                case kPCA9422_SWDVS2Vout:
                    regAddr = PCA9422_BUCK3OUT_DVS2;
                    break;
                case kPCA9422_SWDVS3Vout:
                    regAddr = PCA9422_BUCK3OUT_DVS3;
                    break;
                case kPCA9422_SWDVS4Vout:
                    regAddr = PCA9422_BUCK3OUT_DVS4;
                    break;
                case kPCA9422_SWDVS5Vout:
                    regAddr = PCA9422_BUCK3OUT_DVS5;
                    break;
                case kPCA9422_SWDVS6Vout:
                    regAddr = PCA9422_BUCK3OUT_DVS6;
                    break;
                case kPCA9422_SWDVS7Vout:
                    regAddr = PCA9422_BUCK3OUT_DVS7;
                    break;
                default:
                    /* Not support */
                    regAddr = 0xFFU;
                    LOG_INFO("Error - SW3 doesn't support vout type(%d)\r\n", vout);
                    break;
            }
            break;
        case kPCA9422_RegulatorSwitch4:
            regVal  = (uint8_t)PCA9422_BB_OUT_VAL(volt);
            regMask = (uint8_t)PCA9422_SW4_BB_CFG3_BB_VOUT;
            /* Check VOUT type */
            switch (vout)
            {
                case kPCA9422_RegVout:
                    regAddr = PCA9422_SW4_BB_CFG3;
                    break;
                case kPCA9422_RegSleepVout:
                    regAddr = PCA9422_SW4_BB_VOUT_SLEEP;
                    break;
                case kPCA9422_RegStandbyVout:
                    regAddr = PCA9422_SW4_BB_CFG4;
                    break;
                case kPCA9422_SWMaxVout:
                    regAddr = PCA9422_SW4_BB_MAX_LIMIT;
                    break;
                case kPCA9422_BBMinVout:
                    regAddr = PCA9422_SW4_BB_MIN_LIMIT;
                    break;
                default:
                    /* Not support */
                    regAddr = 0xFFU;
                    LOG_INFO("Error - SW4 doesn't support vout type(%d)\r\n", vout);
                    break;
            }
            break;

        case kPCA9422_RegulatorLdo1:
            regVal  = (uint8_t)PCA9422_LDO1_OUT_VAL(volt);
            regMask = PCA9422_LDO1_CFG1_L1_OUT;
            switch (vout)
            {
                case kPCA9422_RegVout:
                    regAddr = PCA9422_LDO1_CFG1;
                    break;
                case kPCA9422_RegSleepVout:
                case kPCA9422_RegStandbyVout:
                    /* Not support */
                    regAddr = 0xFFU;
                    LOG_INFO("LDO1 doesn't support sleep/standby vout type(%d)\r\n", vout);
                    break;
                default:
                    /* Not support */
                    regAddr = 0xFFU;
                    LOG_INFO("Error - LDO1 doesn't support vout type(%d)\r\n", vout);
                    break;
            }
            break;

        case kPCA9422_RegulatorLdo2:
            regVal  = (uint8_t)PCA9422_LDO23_OUT_VAL(volt);
            regMask = PCA9422_LDO2_OUT_L2_OUT;
            switch (vout)
            {
                case kPCA9422_RegVout:
                    regAddr = PCA9422_LDO2_OUT;
                    break;
                case kPCA9422_RegSleepVout:
                    regAddr = PCA9422_LDO2_OUT_SLEEP;
                    break;
                case kPCA9422_RegStandbyVout:
                    regAddr = PCA9422_LDO2_OUT_STBY;
                    break;
                default:
                    /* Not support */
                    regAddr = 0xFFU;
                    LOG_INFO("Error - LDO2 doesn't support vout type(%d)\r\n", vout);
                    break;
            }
            break;

        case kPCA9422_RegulatorLdo3:
            regVal  = (uint8_t)PCA9422_LDO23_OUT_VAL(volt);
            regMask = PCA9422_LDO3_OUT_L3_OUT;
            switch (vout)
            {
                case kPCA9422_RegVout:
                    regAddr = PCA9422_LDO3_OUT;
                    break;
                case kPCA9422_RegSleepVout:
                    regAddr = PCA9422_LDO3_OUT_SLEEP;
                    break;
                case kPCA9422_RegStandbyVout:
                    regAddr = PCA9422_LDO3_OUT_STBY;
                    break;
                default:
                    /* Not support */
                    regAddr = 0xFFU;
                    LOG_INFO("Error - LDO3 doesn't support vout type(%d)\r\n", vout);
                    break;
            }
            break;
        case kPCA9422_RegulatorLdo4:
            regVal  = (uint8_t)PCA9422_LDO4_OUT_VAL(volt);
            regMask = PCA9422_LDO4_OUT_L4_OUT;
            switch (vout)
            {
                case kPCA9422_RegVout:
                    regAddr = PCA9422_LDO4_OUT;
                    break;
                case kPCA9422_RegSleepVout:
                    regAddr = PCA9422_LDO4_OUT_SLEEP;
                    break;
                case kPCA9422_RegStandbyVout:
                    regAddr = PCA9422_LDO4_OUT_STBY;
                    break;
                default:
                    /* Not support */
                    regAddr = 0xFFU;
                    LOG_INFO("Error - LDO4 doesn't support vout type(%d)\r\n", vout);
                    break;
            }
            break;
        default:
            regAddr = 0xFFU;
            LOG_INFO("Error Invalid regulator\r\n");
            break;
    }

    if (regAddr != 0xFFU)
    {
        result = PCA9422_ModifyReg(handle, regAddr, regMask, regVal);
        if (result == false)
        {
            goto out;
        }
        /* REG_LOCK - UNLOCK KEY */
        regVal  = (uint8_t)kPCA9422_RegLockUnlockKey;
        regAddr = PCA9422_REG_LOCK;
        result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
        if (result == false)
        {
            goto out;
        }
    }
    return;

out:
    LOG_INFO("Error I2C data write[0x%2X]\r\n", regAddr);
    return;
}

void PCA9422_GetRegulatorVoltage(pca9422_handle_t *handle, pca9422_regulator_t reg, pca9422_vout_t vout, uint32_t *volt)
{
    uint8_t regVal, regAddr, regMask = 0U;
    bool result = true;

    /* REG_LOCK - UNLOCK KEY */
    regVal  = (uint8_t)kPCA9422_RegLockUnlockKey;
    regAddr = PCA9422_REG_LOCK;
    result  = PCA9422_WriteRegs(handle, regAddr, &regVal, 1U);
    if (result == false)
    {
        goto out;
    }

    switch (reg)
    {
        case kPCA9422_RegulatorSwitch1:
            regMask = PCA9422_BUCKXOUT_DVS0_BX_DVS0;
            /* Check VOUT type */
            switch (vout)
            {
                case kPCA9422_RegSleepVout:
                    regAddr = PCA9422_BUCK1OUT_SLEEP;
                    break;
                case kPCA9422_RegStandbyVout:
                    regAddr = PCA9422_BUCK1OUT_STBY;
                    break;
                case kPCA9422_SWMaxVout:
                    regAddr = PCA9422_BUCK1OUT_MAX_LIMIT;
                    break;
                case kPCA9422_SWDVS0Vout:
                    regAddr = PCA9422_BUCK1OUT_DVS0;
                    break;
                case kPCA9422_SWDVS1Vout:
                    regAddr = PCA9422_BUCK1OUT_DVS1;
                    break;
                case kPCA9422_SWDVS2Vout:
                    regAddr = PCA9422_BUCK1OUT_DVS2;
                    break;
                case kPCA9422_SWDVS3Vout:
                    regAddr = PCA9422_BUCK1OUT_DVS3;
                    break;
                case kPCA9422_SWDVS4Vout:
                    regAddr = PCA9422_BUCK1OUT_DVS4;
                    break;
                case kPCA9422_SWDVS5Vout:
                    regAddr = PCA9422_BUCK1OUT_DVS5;
                    break;
                case kPCA9422_SWDVS6Vout:
                    regAddr = PCA9422_BUCK1OUT_DVS6;
                    break;
                case kPCA9422_SWDVS7Vout:
                    regAddr = PCA9422_BUCK1OUT_DVS7;
                    break;
                default:
                    /* Not support */
                    regAddr = 0xFFU;
                    LOG_INFO("Error - SW1 doesn't support vout type(%d)\r\n", vout);
                    break;
            }
            if (regAddr != 0xFFU)
            {
                result = PCA9422_ReadRegs(handle, regAddr, &regVal, 1U);
                if (result == false)
                    goto out;
                regVal = regVal & regMask;
                *volt  = PCA9422_BUCK1_OUT_VOLT(regVal);
            }
            else
            {
                *volt = 0U;
            }
            break;

        case kPCA9422_RegulatorSwitch2:
            regMask = PCA9422_BUCKXOUT_DVS0_BX_DVS0;
            /* Check VOUT type */
            switch (vout)
            {
                case kPCA9422_RegSleepVout:
                    regAddr = PCA9422_BUCK2OUT_SLEEP;
                    break;
                case kPCA9422_RegStandbyVout:
                    regAddr = PCA9422_BUCK2OUT_STBY;
                    break;
                case kPCA9422_SWMaxVout:
                    regAddr = PCA9422_BUCK2OUT_MAX_LIMIT;
                    break;
                case kPCA9422_SWDVS0Vout:
                    regAddr = PCA9422_BUCK2OUT_DVS0;
                    break;
                case kPCA9422_SWDVS1Vout:
                    regAddr = PCA9422_BUCK2OUT_DVS1;
                    break;
                case kPCA9422_SWDVS2Vout:
                    regAddr = PCA9422_BUCK2OUT_DVS2;
                    break;
                case kPCA9422_SWDVS3Vout:
                    regAddr = PCA9422_BUCK2OUT_DVS3;
                    break;
                case kPCA9422_SWDVS4Vout:
                    regAddr = PCA9422_BUCK2OUT_DVS4;
                    break;
                case kPCA9422_SWDVS5Vout:
                    regAddr = PCA9422_BUCK2OUT_DVS5;
                    break;
                case kPCA9422_SWDVS6Vout:
                    regAddr = PCA9422_BUCK2OUT_DVS6;
                    break;
                case kPCA9422_SWDVS7Vout:
                    regAddr = PCA9422_BUCK2OUT_DVS7;
                    break;
                default:
                    /* Not support */
                    regAddr = 0xFFU;
                    LOG_INFO("Error - SW2 doesn't support vout type(%d)\r\n", vout);
                    break;
            }
            if (regAddr != 0xFFU)
            {
                result = PCA9422_ReadRegs(handle, regAddr, &regVal, 1U);
                if (result == false)
                    goto out;
                regVal = regVal & regMask;
                *volt  = PCA9422_BUCK2_OUT_VOLT(regVal);
            }
            else
            {
                *volt = 0U;
            }
            break;

        case kPCA9422_RegulatorSwitch3:
            regMask = PCA9422_BUCKXOUT_DVS0_BX_DVS0;
            /* Check VOUT type */
            switch (vout)
            {
                case kPCA9422_RegSleepVout:
                    regAddr = PCA9422_BUCK3OUT_SLEEP;
                    break;
                case kPCA9422_RegStandbyVout:
                    regAddr = PCA9422_BUCK3OUT_STBY;
                    break;
                case kPCA9422_SWMaxVout:
                    regAddr = PCA9422_BUCK3OUT_MAX_LIMIT;
                    break;
                case kPCA9422_SWDVS0Vout:
                    regAddr = PCA9422_BUCK3OUT_DVS0;
                    break;
                case kPCA9422_SWDVS1Vout:
                    regAddr = PCA9422_BUCK3OUT_DVS1;
                    break;
                case kPCA9422_SWDVS2Vout:
                    regAddr = PCA9422_BUCK3OUT_DVS2;
                    break;
                case kPCA9422_SWDVS3Vout:
                    regAddr = PCA9422_BUCK3OUT_DVS3;
                    break;
                case kPCA9422_SWDVS4Vout:
                    regAddr = PCA9422_BUCK3OUT_DVS4;
                    break;
                case kPCA9422_SWDVS5Vout:
                    regAddr = PCA9422_BUCK3OUT_DVS5;
                    break;
                case kPCA9422_SWDVS6Vout:
                    regAddr = PCA9422_BUCK3OUT_DVS6;
                    break;
                case kPCA9422_SWDVS7Vout:
                    regAddr = PCA9422_BUCK3OUT_DVS7;
                    break;
                default:
                    /* Not support */
                    regAddr = 0xFFU;
                    LOG_INFO("Error - SW3 doesn't support vout type(%d)\r\n", vout);
                    break;
            }
            if (regAddr != 0xFFU)
            {
                result = PCA9422_ReadRegs(handle, regAddr, &regVal, 1U);
                if (result == false)
                    goto out;
                regVal = regVal & regMask;
                *volt  = PCA9422_BUCK3_OUT_VOLT(regVal);
            }
            else
            {
                *volt = 0U;
            }
            break;
        case kPCA9422_RegulatorSwitch4:
            regMask = (uint8_t)PCA9422_SW4_BB_CFG3_BB_VOUT;
            /* Check VOUT type */
            switch (vout)
            {
                case kPCA9422_RegVout:
                    regAddr = PCA9422_SW4_BB_CFG3;
                    break;
                case kPCA9422_RegSleepVout:
                    regAddr = PCA9422_SW4_BB_VOUT_SLEEP;
                    break;
                case kPCA9422_RegStandbyVout:
                    regAddr = PCA9422_SW4_BB_CFG4;
                    break;
                case kPCA9422_SWMaxVout:
                    regAddr = PCA9422_SW4_BB_MAX_LIMIT;
                    break;
                case kPCA9422_BBMinVout:
                    regAddr = PCA9422_SW4_BB_MIN_LIMIT;
                    break;
                default:
                    /* Not support */
                    regAddr = 0xFFU;
                    LOG_INFO("Error - SW4 doesn't support vout type(%d)\r\n", vout);
                    break;
            }
            if (regAddr != 0xFFU)
            {
                result = PCA9422_ReadRegs(handle, regAddr, &regVal, 1U);
                if (result == false)
                {
                    goto out;
                }
                regVal = regVal & regMask;
                *volt  = PCA9422_BB_OUT_VOLT((uint32_t)regVal);
            }
            else
            {
                *volt = 0U;
            }
            break;

        case kPCA9422_RegulatorLdo1:
            /* Always ON LDO */
            regMask = PCA9422_LDO1_CFG1_L1_OUT;
            switch (vout)
            {
                case kPCA9422_RegVout ... kPCA9422_RegStandbyVout:
                    regAddr = PCA9422_LDO1_CFG1;
                    break;
                default:
                    /* Not support */
                    regAddr = 0xFFU;
                    LOG_INFO("Error - LDO1 doesn't support vout type(%d)\r\n", vout);
                    break;
            }
            if (regAddr != 0xFFU)
            {
                result = PCA9422_ReadRegs(handle, regAddr, &regVal, 1U);
                if (result == false)
                {
                    goto out;
                }
                regVal = regVal & regMask;
                *volt  = (uint32_t)PCA9422_LDO1_OUT_VOLT(regVal);
            }
            else
            {
                *volt = 0U;
            }
            break;

        case kPCA9422_RegulatorLdo2:
            regMask = PCA9422_LDO2_OUT_L2_OUT;
            switch (vout)
            {
                case kPCA9422_RegVout:
                    regAddr = PCA9422_LDO2_OUT;
                    break;
                case kPCA9422_RegSleepVout:
                    regAddr = PCA9422_LDO2_OUT_SLEEP;
                    break;
                case kPCA9422_RegStandbyVout:
                    regAddr = PCA9422_LDO2_OUT_STBY;
                    break;
                default:
                    /* Not support */
                    regAddr = 0xFFU;
                    LOG_INFO("Error - LDO2 doesn't support vout type(%d)\r\n", vout);
                    break;
            }
            if (regAddr != 0xFFU)
            {
                result = PCA9422_ReadRegs(handle, regAddr, &regVal, 1U);
                if (result == false)
                {
                    goto out;
                }
                regVal = regVal & regMask;
                *volt  = (uint8_t)PCA9422_LDO23_OUT_VOLT(regVal);
            }
            else
            {
                *volt = 0U;
            }
            break;

        case kPCA9422_RegulatorLdo3:
            regMask = PCA9422_LDO3_OUT_L3_OUT;
            switch (vout)
            {
                case kPCA9422_RegVout:
                    regAddr = PCA9422_LDO3_OUT;
                    break;
                case kPCA9422_RegSleepVout:
                    regAddr = PCA9422_LDO3_OUT_SLEEP;
                    break;
                case kPCA9422_RegStandbyVout:
                    regAddr = PCA9422_LDO3_OUT_STBY;
                    break;
                default:
                    /* Not support */
                    regAddr = 0xFFU;
                    LOG_INFO("Error - LDO3 doesn't support vout type(%d)\r\n", vout);
                    break;
            }
            if (regAddr != 0xFFU)
            {
                result = PCA9422_ReadRegs(handle, regAddr, &regVal, 1U);
                if (result == false)
                {
                    goto out;
                }
                regVal = regVal & regMask;
                *volt  = (uint8_t)PCA9422_LDO23_OUT_VOLT(regVal);
            }
            else
            {
                *volt = 0U;
            }
            break;
        case kPCA9422_RegulatorLdo4:
            regMask = PCA9422_LDO4_OUT_L4_OUT;
            switch (vout)
            {
                case kPCA9422_RegVout:
                    regAddr = PCA9422_LDO4_OUT;
                    break;
                case kPCA9422_RegSleepVout:
                    regAddr = PCA9422_LDO4_OUT_SLEEP;
                    break;
                case kPCA9422_RegStandbyVout:
                    regAddr = PCA9422_LDO4_OUT_STBY;
                    break;
                default:
                    /* Not support */
                    regAddr = 0xFFU;
                    LOG_INFO("Error - LDO4 doesn't support vout type(%d)\r\n", vout);
                    break;
            }
            if (regAddr != 0xFFU)
            {
                result = PCA9422_ReadRegs(handle, regAddr, &regVal, 1U);
                if (result == false)
                {
                    goto out;
                }
                regVal = regVal & regMask;
                *volt  = PCA9422_LDO4_OUT_VOLT(regVal);
            }
            else
            {
                *volt = 0U;
            }
            break;

        default:
            *volt = 0U;
            LOG_INFO("Error Invalid regulator\r\n");
            break;
    }
    return;

out:
    LOG_INFO("Error I2C data write[0x%2X]\r\n", regAddr);
    *volt = 0U;
    return;
}

uint8_t PCA9422_GetRegulatorStatus(pca9422_handle_t *handle)
{
    bool result    = true;
    uint8_t status = 0U;

    /* powerGoodEnable must be configured to true, otherwise the status is always 0. */
    result = PCA9422_ReadRegs(handle, PCA9422_REG_STATUS, &status, 1U);
    if (!result)
    {
        assert(false);
    }

    return status;
}

void PCA9422_SwitchPowerMode(pca9422_handle_t *handle, pca9422_power_mode_t mode)
{
    uint32_t pinMode;
    uint8_t regVal;
    bool result;

    switch (mode)
    {
        case kPCA9422_ActiveModeDVS0:
        case kPCA9422_ActiveModeDVS1:
        case kPCA9422_ActiveModeDVS2:
        case kPCA9422_ActiveModeDVS3:
        case kPCA9422_ActiveModeDVS4:
        case kPCA9422_ActiveModeDVS5:
        case kPCA9422_ActiveModeDVS6:
        case kPCA9422_ActiveModeDVS7:
            pinMode = 0x00U;
            break;
        case kPCA9422_StandbyMode:
            pinMode = 0x02U;
            break;
        case kPCA9422_DPStandbyMode:
            pinMode = 0x03U;
            break;
        case kPCA9422_SleepMode:
            pinMode = 0x01U;
            break;
        default:
            pinMode = 0x00U;
            break;
    }
    /* Switch by Pins */
    POWER_SetPmicMode((uint32_t)pinMode, kCfg_Run);

    /* Read SYS_CFG1 */
    result = PCA9422_ReadRegs(handle, PCA9422_SYS_CFG1, &regVal, 1U);
    if (result == false)
    {
        LOG_INFO("Error I2C data Read[0x%2X]\r\n", PCA9422_SYS_CFG1);
    }

    if ((regVal & PCA9422_SYS_CFG1_STANDBY_CTRL) != 0U)
    {
        /* Standby/DPStandby mode controlled by STANDBY_CFG bit */
        if (mode == kPCA9422_StandbyMode)
        {
            regVal = (uint8_t)kPCA9422_StandbyCfgStandby;
            result = PCA9422_ModifyReg(handle, PCA9422_SYS_CFG1, PCA9422_SYS_CFG1_STANDBY_CFG, regVal);
        }
        else if (mode == kPCA9422_DPStandbyMode)
        {
            regVal = (uint8_t)kPCA9422_StandbyCfgDPStandby;
            result = PCA9422_ModifyReg(handle, PCA9422_SYS_CFG1, PCA9422_SYS_CFG1_STANDBY_CFG, regVal);
        }
        else
        {
            /* Intentional empty. */
        }

        if (!result)
        {
            LOG_INFO("Error I2C operation [0x%2X]\r\n", PCA9422_SYS_CFG1);
        }
    }
}

bool PCA9422_GetCurrentPowerMode(pca9422_handle_t *handle, pca9422_power_mode_t *mode)
{
    bool result    = true;
    uint8_t regVal = 0U;

    /* Read PWR_STATE */
    result = PCA9422_ReadRegs(handle, PCA9422_PWR_STATE, &regVal, 1U);
    regVal = regVal & PCA9422_PWR_STATE_PWR_MODE;
    *mode  = (pca9422_power_mode_t)regVal;

    return result;
}

void PCA9422_GetCurrentEnMode(pca9422_handle_t *handle, pca9422_enmodecfg_t *config)
{
    PCA9422_GetRegulatorEnMode(handle, kPCA9422_RegulatorSwitch1, &config->sw1OutEnMode);
    PCA9422_GetRegulatorEnMode(handle, kPCA9422_RegulatorSwitch2, &config->sw2OutEnMode);
    PCA9422_GetRegulatorEnMode(handle, kPCA9422_RegulatorSwitch3, &config->sw3OutEnMode);
    PCA9422_GetRegulatorEnMode(handle, kPCA9422_RegulatorSwitch4, &config->sw4OutEnMode);
    PCA9422_GetRegulatorEnMode(handle, kPCA9422_RegulatorLdo1, &config->ldo1OutEnMode);
    PCA9422_GetRegulatorEnMode(handle, kPCA9422_RegulatorLdo2, &config->ldo2OutEnMode);
    PCA9422_GetRegulatorEnMode(handle, kPCA9422_RegulatorLdo3, &config->ldo3OutEnMode);
    PCA9422_GetRegulatorEnMode(handle, kPCA9422_RegulatorLdo4, &config->ldo4OutEnMode);
}

bool PCA9422_GetStandbyControl(pca9422_handle_t *handle, pca9422_standby_ctrl_t *ctrl)
{
    bool result    = true;
    uint8_t regVal = 0U;

    /* Read SYS_CFG1 */
    result = PCA9422_ReadRegs(handle, PCA9422_SYS_CFG1, &regVal, 1U);
    regVal = regVal & PCA9422_SYS_CFG1_STANDBY_CTRL;
    *ctrl  = (pca9422_standby_ctrl_t)regVal;

    return result;
}

void PCA9422_SetBuckDVSControl(pca9422_handle_t *handle, pca9422_regulator_t reg, uint8_t dvsCtrl)
{
    uint8_t regVal, regAddr, regMask;
    bool result;

    regAddr = PCA9422_BUCK123_DVS_CFG2;
    switch (reg)
    {
        case kPCA9422_RegulatorSwitch1:
            regMask = PCA9422_BUCK123_DVS_CFG2_B1_DVS_CTRL;
            regVal  = (uint8_t)(dvsCtrl << MASK2SHIFT(PCA9422_BUCK123_DVS_CFG2_B1_DVS_CTRL));
            break;
        case kPCA9422_RegulatorSwitch2:
            regMask = PCA9422_BUCK123_DVS_CFG2_B2_DVS_CTRL;
            regVal  = (uint8_t)(dvsCtrl << MASK2SHIFT(PCA9422_BUCK123_DVS_CFG2_B2_DVS_CTRL));
            break;
        case kPCA9422_RegulatorSwitch3:
            regMask = PCA9422_BUCK123_DVS_CFG2_B3_DVS_CTRL;
            regVal  = (uint8_t)(dvsCtrl << MASK2SHIFT(PCA9422_BUCK123_DVS_CFG2_B3_DVS_CTRL));
            break;
        default:
            LOG_INFO("Error Invalid regulator\r\n");
            regAddr = 0xFFU;
            break;
    }

    if (regAddr != 0xFFU)
    {
        result = PCA9422_ModifyReg(handle, regAddr, regMask, regVal);
        if (result == false)
        {
            LOG_INFO("Error I2C data write[0x%2X]\r\n", regAddr);
        }
    }
    return;
}

void PCA9422_SetEnableRegulatorRunState(pca9422_handle_t *handle, pca9422_regulator_t reg, bool enable)
{
    uint8_t regVal, regAddr, regMask;
    bool result;

    switch (reg)
    {
        case kPCA9422_RegulatorSwitch1:
            regAddr = PCA9422_REGULATOR_EN;
            regVal  = (enable == true) ? PCA9422_REGULATOR_EN_B1_ENABLE : 0U;
            regMask = PCA9422_REGULATOR_EN_B1_ENABLE;
            break;
        case kPCA9422_RegulatorSwitch2:
            regAddr = PCA9422_REGULATOR_EN;
            regVal  = (enable == true) ? PCA9422_REGULATOR_EN_B2_ENABLE : 0U;
            regMask = PCA9422_REGULATOR_EN_B2_ENABLE;
            break;
        case kPCA9422_RegulatorSwitch3:
            regAddr = PCA9422_REGULATOR_EN;
            regVal  = (enable == true) ? PCA9422_REGULATOR_EN_B3_ENABLE : 0U;
            regMask = PCA9422_REGULATOR_EN_B3_ENABLE;
            break;
        case kPCA9422_RegulatorSwitch4:
            regAddr = PCA9422_SW4_BB_CFG2;
            regVal  = (enable == true) ? PCA9422_SW4_BB_CFG2_BB_ENABLE : 0U;
            regMask = PCA9422_SW4_BB_CFG2_BB_ENABLE;
            break;
        case kPCA9422_RegulatorLdo1:
            LOG_INFO("LDO1-Always ON LDO in Run state\r\n");
            regAddr = 0xFFU;
            break;
        case kPCA9422_RegulatorLdo2:
            regAddr = PCA9422_REGULATOR_EN;
            regVal  = (enable == true) ? PCA9422_REGULATOR_EN_L2_ENABLE : 0U;
            regMask = PCA9422_REGULATOR_EN_L2_ENABLE;
            break;
        case kPCA9422_RegulatorLdo3:
            regAddr = PCA9422_REGULATOR_EN;
            regVal  = (enable == true) ? PCA9422_REGULATOR_EN_L3_ENABLE : 0U;
            regMask = PCA9422_REGULATOR_EN_L3_ENABLE;
            break;
        case kPCA9422_RegulatorLdo4:
            regAddr = PCA9422_REGULATOR_EN;
            regVal  = (enable == true) ? PCA9422_REGULATOR_EN_L4_ENABLE : 0U;
            regMask = PCA9422_REGULATOR_EN_L4_ENABLE;
            break;
        default:
            LOG_INFO("Error Invalid regulator\r\n");
            regAddr = 0xFFU;
            break;
    }

    if (regAddr != 0xFFU)
    {
        result = PCA9422_ModifyReg(handle, regAddr, regMask, regVal);
        if (result == false)
        {
            LOG_INFO("Error I2C data write[0x%2X]\r\n", regAddr);
        }
    }
    return;
}

void PCA9422_GetEnableRegulatorRunState(pca9422_handle_t *handle, pca9422_regulator_t reg, bool *enable)
{
    uint8_t regVal, regAddr, regMask;
    bool result;

    switch (reg)
    {
        case kPCA9422_RegulatorSwitch1:
            regAddr = PCA9422_REGULATOR_EN;
            regMask = PCA9422_REGULATOR_EN_B1_ENABLE;
            break;
        case kPCA9422_RegulatorSwitch2:
            regAddr = PCA9422_REGULATOR_EN;
            regMask = PCA9422_REGULATOR_EN_B2_ENABLE;
            break;
        case kPCA9422_RegulatorSwitch3:
            regAddr = PCA9422_REGULATOR_EN;
            regMask = PCA9422_REGULATOR_EN_B3_ENABLE;
            break;
        case kPCA9422_RegulatorSwitch4:
            regAddr = PCA9422_SW4_BB_CFG2;
            regMask = PCA9422_SW4_BB_CFG2_BB_ENABLE;
            break;
        case kPCA9422_RegulatorLdo1:
            /* Always ON LDO in Run state */
            regAddr = 0xFFU;
            break;
        case kPCA9422_RegulatorLdo2:
            regAddr = PCA9422_REGULATOR_EN;
            regMask = PCA9422_REGULATOR_EN_L2_ENABLE;
            break;
        case kPCA9422_RegulatorLdo3:
            regAddr = PCA9422_REGULATOR_EN;
            regMask = PCA9422_REGULATOR_EN_L3_ENABLE;
            break;
        case kPCA9422_RegulatorLdo4:
            regAddr = PCA9422_REGULATOR_EN;
            regMask = PCA9422_REGULATOR_EN_L4_ENABLE;
            break;
        default:
            LOG_INFO("Error Invalid regulator\r\n");
            regAddr = 0xFFU;
            break;
    }

    if (regAddr != 0xFFU)
    {
        result = PCA9422_ReadRegs(handle, regAddr, &regVal, 1U);
        if (result == false)
        {
            LOG_INFO("Error I2C data read[0x%2X]\r\n", regAddr);
            *enable = false;
        }
        else
        {
            regVal  = (regVal & regMask);
            *enable = (regVal == regMask) ? true : false;
        }
    }
    else
    {
        if (reg == kPCA9422_RegulatorLdo1)
        {
            *enable = true;
        }
        else
        {
            *enable = false;
        }
    }

    return;
}

void PCA9422_ReadPowerModeConfigs(pca9422_handle_t *handle, pca9422_power_mode_t powerMode, pca9422_modecfg_t *configs)
{
    switch (powerMode)
    {
        case kPCA9422_ActiveModeDVS0:
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch1, kPCA9422_SWDVS0Vout, &configs->sw1OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch2, kPCA9422_SWDVS0Vout, &configs->sw2OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch3, kPCA9422_SWDVS0Vout, &configs->sw3OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch4, kPCA9422_RegVout, &configs->sw4OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo1, kPCA9422_RegVout, &configs->ldo1OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo2, kPCA9422_RegVout, &configs->ldo2OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo3, kPCA9422_RegVout, &configs->ldo3OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo4, kPCA9422_RegVout, &configs->ldo4OutVolt);
            break;
        case kPCA9422_ActiveModeDVS1:
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch1, kPCA9422_SWDVS1Vout, &configs->sw1OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch2, kPCA9422_SWDVS1Vout, &configs->sw2OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch3, kPCA9422_SWDVS1Vout, &configs->sw3OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch4, kPCA9422_RegVout, &configs->sw4OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo1, kPCA9422_RegVout, &configs->ldo1OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo2, kPCA9422_RegVout, &configs->ldo2OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo3, kPCA9422_RegVout, &configs->ldo3OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo4, kPCA9422_RegVout, &configs->ldo4OutVolt);
            break;
        case kPCA9422_ActiveModeDVS2:
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch1, kPCA9422_SWDVS2Vout, &configs->sw1OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch2, kPCA9422_SWDVS2Vout, &configs->sw2OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch3, kPCA9422_SWDVS2Vout, &configs->sw3OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch4, kPCA9422_RegVout, &configs->sw4OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo1, kPCA9422_RegVout, &configs->ldo1OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo2, kPCA9422_RegVout, &configs->ldo2OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo3, kPCA9422_RegVout, &configs->ldo3OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo4, kPCA9422_RegVout, &configs->ldo4OutVolt);
            break;
        case kPCA9422_ActiveModeDVS3:
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch1, kPCA9422_SWDVS3Vout, &configs->sw1OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch2, kPCA9422_SWDVS3Vout, &configs->sw2OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch3, kPCA9422_SWDVS3Vout, &configs->sw3OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch4, kPCA9422_RegVout, &configs->sw4OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo1, kPCA9422_RegVout, &configs->ldo1OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo2, kPCA9422_RegVout, &configs->ldo2OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo3, kPCA9422_RegVout, &configs->ldo3OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo4, kPCA9422_RegVout, &configs->ldo4OutVolt);
            break;
        case kPCA9422_ActiveModeDVS4:
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch1, kPCA9422_SWDVS4Vout, &configs->sw1OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch2, kPCA9422_SWDVS4Vout, &configs->sw2OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch3, kPCA9422_SWDVS4Vout, &configs->sw3OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch4, kPCA9422_RegVout, &configs->sw4OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo1, kPCA9422_RegVout, &configs->ldo1OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo2, kPCA9422_RegVout, &configs->ldo2OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo3, kPCA9422_RegVout, &configs->ldo3OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo4, kPCA9422_RegVout, &configs->ldo4OutVolt);
            break;
        case kPCA9422_ActiveModeDVS5:
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch1, kPCA9422_SWDVS5Vout, &configs->sw1OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch2, kPCA9422_SWDVS5Vout, &configs->sw2OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch3, kPCA9422_SWDVS5Vout, &configs->sw3OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch4, kPCA9422_RegVout, &configs->sw4OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo1, kPCA9422_RegVout, &configs->ldo1OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo2, kPCA9422_RegVout, &configs->ldo2OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo3, kPCA9422_RegVout, &configs->ldo3OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo4, kPCA9422_RegVout, &configs->ldo4OutVolt);
            break;
        case kPCA9422_ActiveModeDVS6:
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch1, kPCA9422_SWDVS6Vout, &configs->sw1OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch2, kPCA9422_SWDVS6Vout, &configs->sw2OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch3, kPCA9422_SWDVS6Vout, &configs->sw3OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch4, kPCA9422_RegVout, &configs->sw4OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo1, kPCA9422_RegVout, &configs->ldo1OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo2, kPCA9422_RegVout, &configs->ldo2OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo3, kPCA9422_RegVout, &configs->ldo3OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo4, kPCA9422_RegVout, &configs->ldo4OutVolt);
            break;
        case kPCA9422_ActiveModeDVS7:
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch1, kPCA9422_SWDVS7Vout, &configs->sw1OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch2, kPCA9422_SWDVS7Vout, &configs->sw2OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch3, kPCA9422_SWDVS7Vout, &configs->sw3OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch4, kPCA9422_RegVout, &configs->sw4OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo1, kPCA9422_RegVout, &configs->ldo1OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo2, kPCA9422_RegVout, &configs->ldo2OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo3, kPCA9422_RegVout, &configs->ldo3OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo4, kPCA9422_RegVout, &configs->ldo4OutVolt);
            break;

        case kPCA9422_StandbyMode:
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch1, kPCA9422_RegStandbyVout,
                                        &configs->sw1OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch2, kPCA9422_RegStandbyVout,
                                        &configs->sw2OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch3, kPCA9422_RegStandbyVout,
                                        &configs->sw3OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch4, kPCA9422_RegStandbyVout,
                                        &configs->sw4OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo1, kPCA9422_RegStandbyVout, &configs->ldo1OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo2, kPCA9422_RegStandbyVout, &configs->ldo2OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo3, kPCA9422_RegStandbyVout, &configs->ldo3OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo4, kPCA9422_RegStandbyVout, &configs->ldo4OutVolt);
            break;

        case kPCA9422_DPStandbyMode:
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch1, kPCA9422_RegStandbyVout,
                                        &configs->sw1OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch2, kPCA9422_RegStandbyVout,
                                        &configs->sw2OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch3, kPCA9422_RegStandbyVout,
                                        &configs->sw3OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch4, kPCA9422_RegStandbyVout,
                                        &configs->sw4OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo1, kPCA9422_RegStandbyVout, &configs->ldo1OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo2, kPCA9422_RegStandbyVout, &configs->ldo2OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo3, kPCA9422_RegStandbyVout, &configs->ldo3OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo4, kPCA9422_RegStandbyVout, &configs->ldo4OutVolt);
            break;

        case kPCA9422_SleepMode:
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch1, kPCA9422_RegSleepVout, &configs->sw1OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch2, kPCA9422_RegSleepVout, &configs->sw2OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch3, kPCA9422_RegSleepVout, &configs->sw3OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch4, kPCA9422_RegSleepVout, &configs->sw4OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo1, kPCA9422_RegSleepVout, &configs->ldo1OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo2, kPCA9422_RegSleepVout, &configs->ldo2OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo3, kPCA9422_RegSleepVout, &configs->ldo3OutVolt);
            PCA9422_GetRegulatorVoltage(handle, kPCA9422_RegulatorLdo4, kPCA9422_RegSleepVout, &configs->ldo4OutVolt);
            break;

        default:
            LOG_INFO("Error - Don't support power mode(%d)\r\n", powerMode);
            break;
    }
}

void PCA9422_WritePowerModeConfigs(pca9422_handle_t *handle, pca9422_power_mode_t powerMode, pca9422_modecfg_t configs)
{
    switch (powerMode)
    {
        case kPCA9422_ActiveModeDVS0:
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch1, kPCA9422_SWDVS0Vout, configs.sw1OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch2, kPCA9422_SWDVS0Vout, configs.sw2OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch3, kPCA9422_SWDVS0Vout, configs.sw3OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch4, kPCA9422_RegVout, configs.sw4OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo1, kPCA9422_RegVout, configs.ldo1OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo2, kPCA9422_RegVout, configs.ldo2OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo3, kPCA9422_RegVout, configs.ldo3OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo4, kPCA9422_RegVout, configs.ldo4OutVolt);
            break;
        case kPCA9422_ActiveModeDVS1:
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch1, kPCA9422_SWDVS1Vout, configs.sw1OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch2, kPCA9422_SWDVS1Vout, configs.sw2OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch3, kPCA9422_SWDVS1Vout, configs.sw3OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch4, kPCA9422_RegVout, configs.sw4OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo1, kPCA9422_RegVout, configs.ldo1OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo2, kPCA9422_RegVout, configs.ldo2OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo3, kPCA9422_RegVout, configs.ldo3OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo4, kPCA9422_RegVout, configs.ldo4OutVolt);
            break;
        case kPCA9422_ActiveModeDVS2:
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch1, kPCA9422_SWDVS2Vout, configs.sw1OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch2, kPCA9422_SWDVS2Vout, configs.sw2OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch3, kPCA9422_SWDVS2Vout, configs.sw3OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch4, kPCA9422_RegVout, configs.sw4OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo1, kPCA9422_RegVout, configs.ldo1OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo2, kPCA9422_RegVout, configs.ldo2OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo3, kPCA9422_RegVout, configs.ldo3OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo4, kPCA9422_RegVout, configs.ldo4OutVolt);
            break;
        case kPCA9422_ActiveModeDVS3:
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch1, kPCA9422_SWDVS3Vout, configs.sw1OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch2, kPCA9422_SWDVS3Vout, configs.sw2OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch3, kPCA9422_SWDVS3Vout, configs.sw3OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch4, kPCA9422_RegVout, configs.sw4OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo1, kPCA9422_RegVout, configs.ldo1OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo2, kPCA9422_RegVout, configs.ldo2OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo3, kPCA9422_RegVout, configs.ldo3OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo4, kPCA9422_RegVout, configs.ldo4OutVolt);
            break;
        case kPCA9422_ActiveModeDVS4:
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch1, kPCA9422_SWDVS4Vout, configs.sw1OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch2, kPCA9422_SWDVS4Vout, configs.sw2OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch3, kPCA9422_SWDVS4Vout, configs.sw3OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch4, kPCA9422_RegVout, configs.sw4OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo1, kPCA9422_RegVout, configs.ldo1OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo2, kPCA9422_RegVout, configs.ldo2OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo3, kPCA9422_RegVout, configs.ldo3OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo4, kPCA9422_RegVout, configs.ldo4OutVolt);
            break;
        case kPCA9422_ActiveModeDVS5:
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch1, kPCA9422_SWDVS5Vout, configs.sw1OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch2, kPCA9422_SWDVS5Vout, configs.sw2OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch3, kPCA9422_SWDVS5Vout, configs.sw3OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch4, kPCA9422_RegVout, configs.sw4OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo1, kPCA9422_RegVout, configs.ldo1OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo2, kPCA9422_RegVout, configs.ldo2OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo3, kPCA9422_RegVout, configs.ldo3OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo4, kPCA9422_RegVout, configs.ldo4OutVolt);
            break;
        case kPCA9422_ActiveModeDVS6:
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch1, kPCA9422_SWDVS6Vout, configs.sw1OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch2, kPCA9422_SWDVS6Vout, configs.sw2OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch3, kPCA9422_SWDVS6Vout, configs.sw3OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch4, kPCA9422_RegVout, configs.sw4OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo1, kPCA9422_RegVout, configs.ldo1OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo2, kPCA9422_RegVout, configs.ldo2OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo3, kPCA9422_RegVout, configs.ldo3OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo4, kPCA9422_RegVout, configs.ldo4OutVolt);
            break;
        case kPCA9422_ActiveModeDVS7:
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch1, kPCA9422_SWDVS7Vout, configs.sw1OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch2, kPCA9422_SWDVS7Vout, configs.sw2OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch3, kPCA9422_SWDVS7Vout, configs.sw3OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch4, kPCA9422_RegVout, configs.sw4OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo1, kPCA9422_RegVout, configs.ldo1OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo2, kPCA9422_RegVout, configs.ldo2OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo3, kPCA9422_RegVout, configs.ldo3OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo4, kPCA9422_RegVout, configs.ldo4OutVolt);
            break;

        case kPCA9422_StandbyMode:
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch1, kPCA9422_RegStandbyVout, configs.sw1OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch2, kPCA9422_RegStandbyVout, configs.sw2OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch3, kPCA9422_RegStandbyVout, configs.sw3OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch4, kPCA9422_RegStandbyVout, configs.sw4OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo1, kPCA9422_RegStandbyVout, configs.ldo1OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo2, kPCA9422_RegStandbyVout, configs.ldo2OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo3, kPCA9422_RegStandbyVout, configs.ldo3OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo4, kPCA9422_RegStandbyVout, configs.ldo4OutVolt);
            break;

        case kPCA9422_DPStandbyMode:
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch1, kPCA9422_RegStandbyVout, configs.sw1OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch2, kPCA9422_RegStandbyVout, configs.sw2OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch3, kPCA9422_RegStandbyVout, configs.sw3OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch4, kPCA9422_RegStandbyVout, configs.sw4OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo1, kPCA9422_RegStandbyVout, configs.ldo1OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo2, kPCA9422_RegStandbyVout, configs.ldo2OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo3, kPCA9422_RegStandbyVout, configs.ldo3OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo4, kPCA9422_RegStandbyVout, configs.ldo4OutVolt);
            break;

        case kPCA9422_SleepMode:
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch1, kPCA9422_RegSleepVout, configs.sw1OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch2, kPCA9422_RegSleepVout, configs.sw2OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch3, kPCA9422_RegSleepVout, configs.sw3OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorSwitch4, kPCA9422_RegSleepVout, configs.sw4OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo1, kPCA9422_RegSleepVout, configs.ldo1OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo2, kPCA9422_RegSleepVout, configs.ldo2OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo3, kPCA9422_RegSleepVout, configs.ldo3OutVolt);
            PCA9422_SetRegulatorVoltage(handle, kPCA9422_RegulatorLdo4, kPCA9422_RegSleepVout, configs.ldo4OutVolt);
            break;

        case kPCA9422_NoneMode:
            /* Skip this mode */
            LOG_INFO("Skip power mode(%d)\r\n", powerMode);
            break;

        default:
            LOG_INFO("Error - Don't support power mode(%d)\r\n", powerMode);
            break;
    }
}
/* @} */

void PCA9422_WriteEnModeConfig(pca9422_handle_t *handle, pca9422_enmodecfg_t config)
{
    /* Set Enmode */
    PCA9422_SetRegulatorEnMode(handle, kPCA9422_RegulatorSwitch1, config.sw1OutEnMode);
    PCA9422_SetRegulatorEnMode(handle, kPCA9422_RegulatorSwitch2, config.sw2OutEnMode);
    PCA9422_SetRegulatorEnMode(handle, kPCA9422_RegulatorSwitch3, config.sw3OutEnMode);
    PCA9422_SetRegulatorEnMode(handle, kPCA9422_RegulatorSwitch4, config.sw4OutEnMode);
    PCA9422_SetRegulatorEnMode(handle, kPCA9422_RegulatorLdo1, config.ldo1OutEnMode);
    PCA9422_SetRegulatorEnMode(handle, kPCA9422_RegulatorLdo2, config.ldo2OutEnMode);
    PCA9422_SetRegulatorEnMode(handle, kPCA9422_RegulatorLdo3, config.ldo3OutEnMode);
    PCA9422_SetRegulatorEnMode(handle, kPCA9422_RegulatorLdo4, config.ldo4OutEnMode);
}

void PCA9422_WriteRegEnableConfig(pca9422_handle_t *handle, pca9422_regulatoren_t config)
{
    /* Set Enable */
    PCA9422_SetEnableRegulatorRunState(handle, kPCA9422_RegulatorSwitch1, config.sw1Enable);
    PCA9422_SetEnableRegulatorRunState(handle, kPCA9422_RegulatorSwitch2, config.sw2Enable);
    PCA9422_SetEnableRegulatorRunState(handle, kPCA9422_RegulatorSwitch3, config.sw3Enable);
    PCA9422_SetEnableRegulatorRunState(handle, kPCA9422_RegulatorSwitch4, config.sw4Enable);
    PCA9422_SetEnableRegulatorRunState(handle, kPCA9422_RegulatorLdo1, config.ldo1Enable);
    PCA9422_SetEnableRegulatorRunState(handle, kPCA9422_RegulatorLdo2, config.ldo2Enable);
    PCA9422_SetEnableRegulatorRunState(handle, kPCA9422_RegulatorLdo3, config.ldo3Enable);
    PCA9422_SetEnableRegulatorRunState(handle, kPCA9422_RegulatorLdo4, config.ldo4Enable);
}

static bool PCA9422_EnableState(pca9422_power_mode_t powerMode, pca9422_enmode_t enmode)
{
    bool enable;

    switch (powerMode)
    {
        case kPCA9422_ActiveModeDVS0 ... kPCA9422_ActiveModeDVS7:
            enable = true;
            break;
        case kPCA9422_StandbyMode:
            enable = (enmode < kPCA9422_EnmodeOnActiveSleep) ? true : false;
            break;
        case kPCA9422_DPStandbyMode:
            enable = (enmode < kPCA9422_EnmodeOnActiveSleepStandby) ? true : false;
            break;
        case kPCA9422_SleepMode:
            enable = (enmode < kPCA9422_EnmodeOnActive) ? true : false;
            break;
        default:
            enable = false;
            break;
    }
    return enable;
}

void PCA9422_ReadEnableConfigs(pca9422_handle_t *handle, pca9422_power_mode_t powerMode, pca9422_enablecfg_t *config)
{
    pca9422_enmodecfg_t enmodeCfg;
    pca9422_regulatoren_t regenable;

    /* Read Enmode */
    PCA9422_GetCurrentEnMode(handle, &enmodeCfg);
    /* Read Regulator Enable */
    PCA9422_GetEnableRegulatorRunState(handle, kPCA9422_RegulatorSwitch1, &regenable.sw1Enable);
    PCA9422_GetEnableRegulatorRunState(handle, kPCA9422_RegulatorSwitch2, &regenable.sw2Enable);
    PCA9422_GetEnableRegulatorRunState(handle, kPCA9422_RegulatorSwitch3, &regenable.sw3Enable);
    PCA9422_GetEnableRegulatorRunState(handle, kPCA9422_RegulatorSwitch4, &regenable.sw4Enable);
    PCA9422_GetEnableRegulatorRunState(handle, kPCA9422_RegulatorLdo1, &regenable.ldo1Enable);
    PCA9422_GetEnableRegulatorRunState(handle, kPCA9422_RegulatorLdo2, &regenable.ldo2Enable);
    PCA9422_GetEnableRegulatorRunState(handle, kPCA9422_RegulatorLdo3, &regenable.ldo3Enable);
    PCA9422_GetEnableRegulatorRunState(handle, kPCA9422_RegulatorLdo4, &regenable.ldo4Enable);

    /* Check power mode */
    switch (powerMode)
    {
        case kPCA9422_ActiveModeDVS0 ... kPCA9422_ActiveModeDVS7:
            config->enableSw1Out  = regenable.sw1Enable ? true : false;
            config->enableSw2Out  = regenable.sw2Enable ? true : false;
            config->enableSw3Out  = regenable.sw3Enable ? true : false;
            config->enableSw4Out  = regenable.sw4Enable ? true : false;
            config->enableLdo1Out = regenable.ldo1Enable ? true : false;
            config->enableLdo2Out = regenable.ldo2Enable ? true : false;
            config->enableLdo3Out = regenable.ldo3Enable ? true : false;
            config->enableLdo4Out = regenable.ldo4Enable ? true : false;
            break;
        case kPCA9422_StandbyMode:
        case kPCA9422_DPStandbyMode:
        case kPCA9422_SleepMode:
            config->enableSw1Out = regenable.sw1Enable ? PCA9422_EnableState(powerMode, enmodeCfg.sw1OutEnMode) : false;
            config->enableSw2Out = regenable.sw2Enable ? PCA9422_EnableState(powerMode, enmodeCfg.sw2OutEnMode) : false;
            config->enableSw3Out = regenable.sw3Enable ? PCA9422_EnableState(powerMode, enmodeCfg.sw3OutEnMode) : false;
            config->enableSw4Out = regenable.sw4Enable ? PCA9422_EnableState(powerMode, enmodeCfg.sw4OutEnMode) : false;
            config->enableLdo1Out =
                regenable.ldo1Enable ? PCA9422_EnableState(powerMode, enmodeCfg.ldo1OutEnMode) : false;
            config->enableLdo2Out =
                regenable.ldo2Enable ? PCA9422_EnableState(powerMode, enmodeCfg.ldo2OutEnMode) : false;
            config->enableLdo3Out =
                regenable.ldo3Enable ? PCA9422_EnableState(powerMode, enmodeCfg.ldo3OutEnMode) : false;
            config->enableLdo4Out =
                regenable.ldo4Enable ? PCA9422_EnableState(powerMode, enmodeCfg.ldo4OutEnMode) : false;
            break;
        default:
            /* Not supported. */
            break;
    }
}

void PCA9422_FeedWatchDog(pca9422_handle_t *handle)
{
    uint8_t regValue = 1U;

    (void)PCA9422_WriteRegs(handle, PCA9422_TOP_CNTL4, &regValue, 1U);
}

void PCA9422_SetWatchDogTimer(pca9422_handle_t *handle, pca9422_wd_timer_t wd_timer)
{
    bool result;

    result = PCA9422_ModifyReg(handle, PCA9422_TOP_CNTL0, PCA9422_TOP_CNTL0_WD_TIMER, (uint8_t)wd_timer);
    if (result == false)
    {
        LOG_INFO("Error I2C data write[0x%x]\r\n", PCA9422_TOP_CNTL0);
    }
}

bool PCA9422_WriteRegsReadback(pca9422_handle_t *handle, uint8_t regBase, uint8_t *val)
{
    bool result;
    uint8_t regData;

    result = PCA9422_WriteRegs(handle, regBase, val, 1U);
    if (result == true)
    {
        /* Read back */
        result = PCA9422_ReadRegs(handle, regBase, &regData, 1U);
        if (result == true)
        {
            /* Compare data */
            if (regData != *val)
            {
                LOG_INFO("Error I2C data[0x%x] written(0x%x) vs read(0x%x)\r\n", regBase, *val, regData);
                result = false;
            }
        }
        else
        {
            LOG_INFO("Error I2C data read[0x%x]\r\n", regBase);
        }
    }
    else
    {
        LOG_INFO("Error I2C data write[0x%x]\r\n", regBase);
    }
    return result;
}

bool PCA9422_ModifyRegReadback(pca9422_handle_t *handle, uint8_t reg, uint8_t mask, uint8_t val)
{
    bool result;
    uint8_t regValue = 0U;

    assert(handle);

    /* Read back the register content. */
    result = PCA9422_ReadRegs(handle, reg, &regValue, 1U);
    if (result)
    {
        /* Modify the bit-fields you want to change. */
        regValue &= (uint8_t)~mask;
        regValue |= val;

        /* Write back the content to the registers. */
        result = PCA9422_WriteRegsReadback(handle, reg, &regValue);
    }

    return result;
}

bool PCA9422_WriteRegs(pca9422_handle_t *handle, uint8_t regBase, uint8_t *val, uint32_t size)
{
    assert(handle);
    assert(handle->I2C_SendFunc);
    assert(val);

    return (kStatus_Success == handle->I2C_SendFunc(handle->slaveAddress, regBase, 1U, val, size)) ? true : false;
}

bool PCA9422_ReadRegs(pca9422_handle_t *handle, uint8_t regBase, uint8_t *val, uint32_t size)
{
    assert(handle);
    assert(handle->I2C_ReceiveFunc);
    assert(val);

    return (kStatus_Success == handle->I2C_ReceiveFunc(handle->slaveAddress, regBase, 1U, val, size)) ? true : false;
}

bool PCA9422_ModifyReg(pca9422_handle_t *handle, uint8_t reg, uint8_t mask, uint8_t val)
{
    bool result;
    uint8_t regValue = 0U;

    assert(handle);

    /* Read back the register content. */
    result = PCA9422_ReadRegs(handle, reg, &regValue, 1U);
    if (result)
    {
        /* Modify the bit-fields you want to change. */
        regValue &= (uint8_t)~mask;
        regValue |= val;

        /* Write back the content to the registers. */
        result = PCA9422_WriteRegs(handle, reg, &regValue, 1U);
    }

    return result;
}

void PCA9422_EnableChargerInterrupts(pca9422_handle_t *handle, uint8_t *source)
{
    bool result;
    uint8_t maskVal[6];

    maskVal[0] = (uint8_t)(~(source[0] & 0xFFU)); /* INT_DEVICE_0_MASK */
    maskVal[1] = (uint8_t)(~(source[1] & 0xFFU)); /* INT_DEVICE_1_MASK */
    maskVal[2] = (uint8_t)(~(source[2] & 0xFFU)); /* INT_CHARGE_0_MASK */
    maskVal[3] = (uint8_t)(~(source[3] & 0xFFU)); /* INT_CHARGE_1_MASK */
    maskVal[4] = (uint8_t)(~(source[4] & 0xFFU)); /* INT_CHARGE_2_MASK */
    maskVal[5] = (uint8_t)(~(source[5] & 0xFFU)); /* INT_CHARGE_3_MASK */

    /* Write mask registers */
    result = PCA9422_WriteRegs(handle, PCA9422_INT_DEVICE_0_MASK, maskVal, sizeof(maskVal));
    if (!result)
    {
        LOG_INFO("Error I2C data write interrupt mask registers of charge\r\n");
    }
}

void PCA9422_DisableChargerInterrupts(pca9422_handle_t *handle, uint8_t *source)
{
    bool result;
    uint8_t maskVal[6] = {
        0,
    };

    (void)memcpy(source, maskVal, sizeof(maskVal));

    /* Write mask registers */
    result = PCA9422_WriteRegs(handle, PCA9422_INT_DEVICE_0_MASK, maskVal, sizeof(maskVal));
    if (!result)
    {
        LOG_INFO("Error I2C data write interrupt mask registers of charge\r\n");
    }
}

void PCA9422_GetChargerInterrupts(pca9422_handle_t *handle, uint8_t *source)
{
    bool result;

    /* Read interrupt registers */
    result = PCA9422_ReadRegs(handle, PCA9422_INT_DEVICE_0, source, 6U);
    if (!result)
    {
        LOG_INFO("Error I2C data read interrupt registers of charge\r\n");
    }
}

void PCA9422_GetChargerInterruptStatus(pca9422_handle_t *handle, uint8_t *status)
{
    bool result;

    /* Read interrupt status registers */
    result = PCA9422_ReadRegs(handle, PCA9422_DEVICE_0_STS, status, 6U);
    if (!result)
    {
        LOG_INFO("Error I2C data read interrupt status registers of charge\r\n");
    }
}

void PCA9422_EnableRegulatorInterrupt(pca9422_handle_t *handle, uint8_t *source)
{
    bool result;
    uint8_t maskVal;

    maskVal = (uint8_t)(~(*source & 0xFFU)); /* INT1_MASK */
    /* Write mask register */
    result = PCA9422_WriteRegs(handle, PCA9422_INT1_MASK, &maskVal, sizeof(maskVal));
    if (!result)
    {
        LOG_INFO("Error I2C data write interrupt mask register of regulator\r\n");
    }
}

void PCA9422_DisableRegulatorInterrupt(pca9422_handle_t *handle, uint8_t *source)
{
    bool result;
    uint8_t maskVal = {
        0,
    };

    (void)memcpy(source, &maskVal, sizeof(maskVal));
    /* Write mask register */
    result = PCA9422_WriteRegs(handle, PCA9422_INT1_MASK, &maskVal, sizeof(maskVal));
    if (!result)
    {
        LOG_INFO("Error I2C data write interrupt mask register of regulator\r\n");
    }
}

void PCA9422_GetRegulatorInterrupt(pca9422_handle_t *handle, uint8_t *source)
{
    bool result;

    /* Read interrupt register */
    result = PCA9422_ReadRegs(handle, PCA9422_INT1, source, 1U);
    if (!result)
    {
        LOG_INFO("Error I2C data read interrupt register of regulator\r\n");
    }
}

void PCA9422_GetRegulatorInterruptStatus(pca9422_handle_t *handle, uint8_t *status)
{
    bool result;

    /* Read interrupt status register */
    result = PCA9422_ReadRegs(handle, PCA9422_INT1_STATUS, status, 1U);
    if (!result)
    {
        LOG_INFO("Error I2C data read interrupt status register of regulator\r\n");
    }
}

void PCA9422_EnableSublevelInterrupts(pca9422_handle_t *handle, uint8_t *source)
{
    bool result;
    uint8_t maskVal[3];

    maskVal[0] = (uint8_t)(~(source[0] & 0xFFU)); /* SUB_INT0_MASK */
    maskVal[1] = (uint8_t)(~(source[1] & 0xFFU)); /* SUB_INT1_MASK */
    maskVal[2] = (uint8_t)(~(source[2] & 0xFFU)); /* SUB_INT2_MASK */

    /* Write mask registers */
    result = PCA9422_WriteRegs(handle, PCA9422_SUB_INT0_MASK, &maskVal[0], 1U);
    if (!result)
    {
        LOG_INFO("Error I2C data write interrupt mask registers of sub-level\r\n");
    }
    result = PCA9422_WriteRegs(handle, PCA9422_SUB_INT1_MASK, &maskVal[1], 1U);
    if (!result)
    {
        LOG_INFO("Error I2C data write interrupt mask registers of sub-level\r\n");
    }
    result = PCA9422_WriteRegs(handle, PCA9422_SUB_INT2_MASK, &maskVal[2], 1U);
    if (!result)
    {
        LOG_INFO("Error I2C data write interrupt mask registers of sub-level\r\n");
    }
}

void PCA9422_DisableSublevelInterrupts(pca9422_handle_t *handle, uint8_t *source)
{
    bool result;
    uint8_t maskVal[3] = {
        0,
    };

    (void)memcpy(source, maskVal, sizeof(maskVal));
    /* Write mask registers */
    result = PCA9422_WriteRegs(handle, PCA9422_SUB_INT0_MASK, &maskVal[0], 1U);
    if (!result)
    {
        LOG_INFO("Error I2C data write interrupt mask registers of sub-level\r\n");
    }
    result = PCA9422_WriteRegs(handle, PCA9422_SUB_INT1_MASK, &maskVal[1], 1U);
    if (!result)
    {
        LOG_INFO("Error I2C data write interrupt mask registers of sub-level\r\n");
    }
    result = PCA9422_WriteRegs(handle, PCA9422_SUB_INT2_MASK, &maskVal[2], 1U);
    if (!result)
    {
        LOG_INFO("Error I2C data write interrupt mask registers of sub-level\r\n");
    }
}

void PCA9422_GetSublevelInterrupts(pca9422_handle_t *handle, uint8_t *source)
{
    bool result;

    /* Read interrupt registers */
    result = PCA9422_ReadRegs(handle, PCA9422_SUB_INT0, &source[0], 1U);
    if (!result)
    {
        LOG_INFO("Error I2C data read interrupt registers of sub-level\r\n");
    }
    result = PCA9422_ReadRegs(handle, PCA9422_SUB_INT1, &source[1], 1U);
    if (!result)
    {
        LOG_INFO("Error I2C data read interrupt registers of sub-level\r\n");
    }
    result = PCA9422_ReadRegs(handle, PCA9422_SUB_INT2, &source[2], 1U);
    if (!result)
    {
        LOG_INFO("Error I2C data read interrupt registers of sub-level\r\n");
    }
}

void PCA9422_GetToplevelInterruptStatus(pca9422_handle_t *handle, uint8_t *status)
{
    bool result;

    /* Read interrupt registers */
    result = PCA9422_ReadRegs(handle, PCA9422_TOP_INT, status, 1U);
    if (!result)
    {
        LOG_INFO("Error I2C data read interrupt registers of top-level\r\n");
    }
}
/*******************************************************************************
 * EOF
 ******************************************************************************/
