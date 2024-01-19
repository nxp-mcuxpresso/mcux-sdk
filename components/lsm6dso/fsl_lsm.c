/*
 * Copyright 2021-2023 NXP
 *
 * SPDX-License-Identifier : BSD-3-Clause
 */
#include "fsl_lsm.h"

/******************************************************************************
 * Code
 ******************************************************************************/
status_t LSM_Init(lsm_handle_t *handle, const lsm_config_t *config)
{
    assert(handle);
    assert(config);
    uint8_t val = 0;
    lsm_ctrl3_c_t ctrl3_c = {0};

    /* Initialize the I2C access function. */
    handle->I2C_SendFunc    = config->I2C_SendFunc;
    handle->I2C_ReceiveFunc = config->I2C_ReceiveFunc;
    /* Set Slave Address. */
    handle->slaveAddress = config->slaveAddress;

    if (LSM_ReadReg(handle, LSM_WHO_AM_I_REG, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    if (val != LSM_WHO_AM_I_REG_WHO_AM_I)
    {
        return kStatus_Fail;
    }
    /* reset sensor */
    if (LSM_ReadReg(handle, LSM_CTRL3_C_REG, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    val |= 0x01U;
    if (LSM_WriteReg(handle, LSM_CTRL3_C_REG, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    /*
     * Setup interrupt output pins activation level(low/high)
     * H_LACTIVE(1 bit, in 5th bit):
     *   0 - interrupt output pins active high
     *   1 - interrupt output pins active low
     */
    if (LSM_ReadReg(handle, LSM_CTRL3_C_REG, (uint8_t *)&ctrl3_c) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    if (config->int_active_level == LSM_INT_ACTIVE_HIGH)
    {
        ctrl3_c.h_lactive = 1;
    }

    if (LSM_WriteReg(handle, LSM_CTRL3_C_REG, (uint8_t *)&ctrl3_c) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    /* enable data available */
    if (LSM_ReadReg(handle, LSM_CTRL4_C_REG, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    val |= 0x08U;
    if (LSM_WriteReg(handle, LSM_CTRL4_C_REG, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }

#if LSM_SUPPORT_PEDOMETER
    /* Enable function configuration access(FUNC_CFG_ACCESS) */
    if (LSM_SetMemBank(handle, LSM_EMBEDDED_FUNC_BANK) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    /* Select write operation mode(PAGE_WRITE)  */
    val = LSM_PAGE_RW_REG_PAGE_WRITE(0x01U);
    if (LSM_WriteReg(handle, LSM_PAGE_RW_REG, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    /* Select page 1(PAGE_SEL3~PAGE_SEL0 = 0b0001) */
    if (LSM_ReadReg(handle, LSM_PAGE_SEL_REG, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    val |= LSM_PAGE_SEL_REG_PAGE_SEL(0x01U);
    if (LSM_WriteReg(handle, LSM_PAGE_SEL_REG, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    /* Set page address as 0x0(PAGE_ADDR7~PAGE_ADDR0=0b1000 0011, PEDO_CMD_REG) */
    val = LSM_PEDO_CMD_REG;
    if (LSM_WriteReg(handle, LSM_PAGE_ADDR_REG, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    /* Set page value as 0x04(PAGE_VALUE7~PAGE_VALUE0=0b0000 0100, FP_REJECTION_EN = 1) */
    val = LSM_PEDO_CMD_REG_FP_REJECTION_EN(0x01U);
    if (LSM_WriteReg(handle, LSM_PAGE_VALUE_REG, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    /* Disable write operation mode(PAGE_WRITE = 0b0, PAGE_READ = 0b0) */
    val = LSM_PAGE_RW_REG_PAGE_WRITE(0x00U);
    if (LSM_WriteReg(handle, LSM_PAGE_RW_REG, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    /* Enable step counter module(PEDO_EN = 0b1) */
    val = LSM_EMB_FUNC_EN_A_REG_PEDO_EN(0x01U);
    if (LSM_WriteReg(handle, LSM_EMB_FUNC_EN_A_REG, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    /* Enable pedometer advanced feature(PEDO_ADV_EN = 0b1) */
    val = LSM_EMB_FUNC_EN_B_REG_PEDO_ADV_EN(0x01U);
    if (LSM_WriteReg(handle, LSM_EMB_FUNC_EN_B_REG, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    /* Drive step detector interrupt to INT1 pin(INT1_STEP_DETECTOR = 0b1) */
    val = LSM_EMB_FUNC_INT1_REG_INT1_STEP_DETECTOR(0x01U);
    if (LSM_WriteReg(handle, LSM_EMB_FUNC_INT1_REG, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    /* Disable function configuration access(FUNC_CFG_ACCESS) */
    if (LSM_SetMemBank(handle, LSM_USER_BANK) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    /* Enable interrupt route of embedded function(INT1_EMB_FUNC) */
    val = LSM_MD1_CFG_REG_INT1_EMB_FUNC(0x01U);
    if (LSM_WriteReg(handle, LSM_MD1_CFG_REG, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    /* Start accelerator(CTRL1_XL[ODR_XL3~ODR_XL0] = 0b0010, CTRL1_XL[FS1_XL] = 0b1) */
    val = LSM_CTRL1_XL_REG_ODR_XL(0x02U) | LSM_CTRL1_XL_REG_FS_XL(0X02U);
    if (LSM_WriteReg(handle, LSM_CTRL1_XL_REG, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
#endif
#if LSM_SUPPORT_TILT
    /* Enable function configuration access(FUNC_CFG_ACCESS) */
    if (LSM_SetMemBank(handle, LSM_EMBEDDED_FUNC_BANK) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    /* Enable tilt(EMB_FUNC_EN_A[TILT_EN] = 0b1) */
    if (LSM_ReadReg(handle, LSM_EMB_FUNC_EN_A_REG, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    val |= LSM_EMB_FUNC_EN_A_REG_TILT_EN(0x01U);
    if (LSM_WriteReg(handle, LSM_EMB_FUNC_EN_A_REG, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    /* Route tilt interrupt to INT1 pin(EMB_FUNC_INT1[INT1_TILT] = 0b1) */
    if (LSM_ReadReg(handle, LSM_EMB_FUNC_INT1_REG, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    val |= LSM_EMB_FUNC_INT1_REG_INT1_TILT(0x01U);
    if (LSM_WriteReg(handle, LSM_EMB_FUNC_INT1_REG, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    /* Enable LIR (PAGE_RW[EMC_FUNC_LIR] = 0b1) */
    if (LSM_ReadReg(handle, LSM_PAGE_RW_REG, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    val |= LSM_PAGE_RW_REG_EMB_FUNC_LIR(0x01U);
    if (LSM_WriteReg(handle, LSM_PAGE_RW_REG, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    /* Disable function configuration access(FUNC_CFG_ACCESS) */
    if (LSM_SetMemBank(handle, LSM_USER_BANK) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    /* Enable INT1(MD1_CFG[INT1_EMB_FUNC] = 0b1) */
    if (LSM_ReadReg(handle, LSM_MD1_CFG_REG, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    val |= LSM_MD1_CFG_REG_INT1_EMB_FUNC(0x01U);
    if (LSM_WriteReg(handle, LSM_MD1_CFG_REG, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    /* (CTRL1_XL[ODR_XL3~ODR_XL0] = 0b0010) */
    if (LSM_ReadReg(handle, LSM_CTRL1_XL_REG, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    val |= LSM_CTRL1_XL_REG_ODR_XL(0x02U);
    if (LSM_WriteReg(handle, LSM_CTRL1_XL_REG, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
#endif

    return kStatus_Success;
}

status_t LSM_GetVal(
    lsm_handle_t *handle, uint8_t reg, uint8_t *val, lsm_reg_access_t enter_bank, lsm_reg_access_t exit_bank)
{
    status_t ret;

    ret = LSM_SetMemBank(handle, enter_bank);
    if (ret == kStatus_Success)
    {
        ret = LSM_ReadReg(handle, reg, val);
    }

    if (ret == kStatus_Success)
    {
        ret = LSM_SetMemBank(handle, exit_bank);
    }

    return ret;
}

status_t LSM_SetVal(
    lsm_handle_t *handle, uint8_t reg, uint8_t val, lsm_reg_access_t enter_bank, lsm_reg_access_t exit_bank)
{
    status_t ret;

    ret = LSM_SetMemBank(handle, enter_bank);
    if (ret == kStatus_Success)
    {
        ret = LSM_WriteReg(handle, reg, &val);
    }

    if (ret == kStatus_Success)
    {
        ret = LSM_SetMemBank(handle, exit_bank);
    }

    return ret;
}

status_t LSM_GetPedometerCnt(lsm_handle_t *handle, uint16_t *stepCount)
{
    uint8_t tmp[2] = {0};

    if (LSM_GetVal(handle, LSM_STEP_COUNTER_L_REG, &tmp[0], LSM_EMBEDDED_FUNC_BANK, LSM_USER_BANK) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    if (LSM_GetVal(handle, LSM_STEP_COUNTER_H_REG, &tmp[1], LSM_EMBEDDED_FUNC_BANK, LSM_USER_BANK) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    *stepCount = (((uint16_t)tmp[1] << 8U) | tmp[0]);

    return kStatus_Success;
}

status_t LSM_ReadReg(lsm_handle_t *handle, uint8_t reg, uint8_t *val)
{
    status_t status = kStatus_Fail;
    assert(val);

    if (NULL == handle->I2C_ReceiveFunc)
    {
        return status;
    }

    status = handle->I2C_ReceiveFunc(handle->slaveAddress, reg, 1, val, 1, 0);

    return status;
}

status_t LSM_WriteReg(lsm_handle_t *handle, uint8_t reg, uint8_t *val)
{
    status_t status = kStatus_Fail;

    if (NULL == handle->I2C_SendFunc)
    {
        return status;
    }

    status = handle->I2C_SendFunc(handle->slaveAddress, reg, 1, *val, 0);

    return status;
}

status_t LSM_SetMemBank(lsm_handle_t *handle, lsm_reg_access_t bank)
{
    status_t status = kStatus_Fail;
    lsm_func_cfg_access_t val;

    assert(handle);

    status = LSM_ReadReg(handle, LSM_FUNC_CFG_ACCESS_REG, (uint8_t *)&val);
    if (status == kStatus_Success)
    {
        val.reg_access = (uint8_t)bank;
        status         = LSM_WriteReg(handle, LSM_FUNC_CFG_ACCESS_REG, (uint8_t *)&val);
    }

    return status;
}

status_t LSM_GetMemBank(lsm_handle_t *handle, lsm_reg_access_t *bank)
{
    status_t status = kStatus_Fail;
    lsm_func_cfg_access_t val;
    lsm_reg_access_t reg_access;

    assert(handle);

    status     = LSM_ReadReg(handle, LSM_FUNC_CFG_ACCESS_REG, (uint8_t *)&val);
    reg_access = (lsm_reg_access_t)val.reg_access;
    switch (reg_access)
    {
        case LSM_USER_BANK:
            *bank = LSM_USER_BANK;
            break;

        case LSM_SENSOR_HUB_BANK:
            *bank = LSM_SENSOR_HUB_BANK;
            break;

        case LSM_EMBEDDED_FUNC_BANK:
            *bank = LSM_EMBEDDED_FUNC_BANK;
            break;

        default:
            *bank = LSM_USER_BANK;
            break;
    }

    return status;
}
