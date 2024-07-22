/*
 * Copyright 2021 ~ 2022, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_pf5020.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define PF5020_REGULATOR_PG_EN_MASK  (0x1U)
#define PF5020_REGULATOR_PG_EN_SHIFT (0U)
#define PF5020_REGULATOR_PG_EN(x) \
    (((uint8_t)(((uint8_t)(x)) << PF5020_REGULATOR_PG_EN_SHIFT)) & PF5020_REGULATOR_PG_EN_MASK)

#define PF5020_REGULATOR_WDBYPASS_MASK  (0x2U)
#define PF5020_REGULATOR_WDBYPASS_SHIFT (1U)
#define PF5020_REGULATOR_WDBYPASS(x) \
    (((uint8_t)(((uint8_t)(x)) << PF5020_REGULATOR_WDBYPASS_SHIFT)) & PF5020_REGULATOR_WDBYPASS_MASK)

#define PF5020_REGULATOR_ILIM_BYPASS_MASK  (0x20U)
#define PF5020_REGULATOR_ILIM_BYPASS_SHIFT (5U)
#define PF5020_REGULATOR_ILIM_BYPASS(x) \
    (((uint8_t)(((uint8_t)(x)) << PF5020_REGULATOR_ILIM_BYPASS_SHIFT)) & PF5020_REGULATOR_ILIM_BYPASS_MASK)

#define PF5020_REGULATOR_OV_BYPASS_MASK  (0x40U)
#define PF5020_REGULATOR_OV_BYPASS_SHIFT (6U)
#define PF5020_REGULATOR_OV_BYPASS(x) \
    (((uint8_t)(((uint8_t)(x)) << PF5020_REGULATOR_OV_BYPASS_SHIFT)) & PF5020_REGULATOR_OV_BYPASS_MASK)

#define PF5020_REGULATOR_UV_BYPASS_MASK  (0x80U)
#define PF5020_REGULATOR_UV_BYPASS_SHIFT (7U)
#define PF5020_REGULATOR_UV_BYPASS(x) \
    (((uint8_t)(((uint8_t)(x)) << PF5020_REGULATOR_UV_BYPASS_SHIFT)) & PF5020_REGULATOR_UV_BYPASS_MASK)

#define PF5020_REGULATOR_FLT_REN_MASK  (0x80U)
#define PF5020_REGULATOR_FLT_REN_SHIFT (7U)
#define PF5020_REGULATOR_FLT_REN(x) \
    (((uint8_t)(((uint8_t)(x)) << PF5020_REGULATOR_FLT_REN_SHIFT)) & PF5020_REGULATOR_FLT_REN_MASK)

#define PF5020_BUCK_REGULATOR_RUN_MODE_MASK  (0x3U)
#define PF5020_BUCK_REGULATOR_RUN_MODE_SHIFT (0U)
#define PF5020_BUCK_REGULATOR_RUN_MODE(x) \
    (((uint8_t)(((uint8_t)(x)) << PF5020_BUCK_REGULATOR_RUN_MODE_SHIFT)) & PF5020_BUCK_REGULATOR_RUN_MODE_MASK)

#define PF5020_BUCK_REGULATOR_STANDBY_MODE_MASK  (0xCU)
#define PF5020_BUCK_REGULATOR_STANDBY_MODE_SHIFT (2U)
#define PF5020_BUCK_REGULATOR_STANDBY_MODE(x) \
    (((uint8_t)(((uint8_t)(x)) << PF5020_BUCK_REGULATOR_STANDBY_MODE_SHIFT)) & PF5020_BUCK_REGULATOR_STANDBY_MODE_MASK)

#define PF5020_BUCK_REGULATOR_ILIM_MASK  (0x18U)
#define PF5020_BUCK_REGULATOR_ILIM_SHIFT (3U)
#define PF5020_BUCK_REGULATOR_ILIM(x) \
    (((uint8_t)(((uint8_t)(x)) << PF5020_BUCK_REGULATOR_ILIM_SHIFT)) & PF5020_BUCK_REGULATOR_ILIM_MASK)

#define PF5020_BUCK_REGULATOR_PDGPR_MASK  (0x30U)
#define PF5020_BUCK_REGULATOR_PDGPR_SHIFT (4U)
#define PF5020_BUCK_REGULATOR_PDGPR(x) \
    (((uint8_t)(((uint8_t)(x)) << PF5020_BUCK_REGULATOR_PDGPR_SHIFT)) & PF5020_BUCK_REGULATOR_PDGPR_MASK)

#define PF5020_BUCK_REGULATOR_PHASE_MASK  (0x7U)
#define PF5020_BUCK_REGULATOR_PHASE_SHIFT (0U)
#define PF5020_BUCK_REGULATOR_PHASE(x) \
    (((uint8_t)(((uint8_t)(x)) << PF5020_BUCK_REGULATOR_PHASE_SHIFT)) & PF5020_BUCK_REGULATOR_PHASE_MASK)

#define PF5020_SW2_CONFIG2_VTTEN_MASK  (0x40U)
#define PF5020_SW2_CONFIG2_VTTEN_SHIFT (6U)
#define PF5020_SW2_CONFIG2_VTTEN(x) \
    (((uint8_t)(((uint8_t)(x)) << PF5020_SW2_CONFIG2_VTTEN_SHIFT)) & PF5020_SW2_CONFIG2_VTTEN_MASK)

#define PF5020_LDO1_CONFIG2_STBY_EN_MASK  (0x1U)
#define PF5020_LDO1_CONFIG2_STBY_EN_SHIFT (0U)
#define PF5020_LDO1_CONFIG2_STBY_EN(x) \
    (((uint8_t)(((uint8_t)(x)) << PF5020_LDO1_CONFIG2_STBY_EN_SHIFT)) & PF5020_LDO1_CONFIG2_STBY_EN_MASK)

#define PF5020_LDO1_CONFIG2_RUN_EN_MASK  (0x2U)
#define PF5020_LDO1_CONFIG2_RUN_EN_SHIFT (1U)
#define PF5020_LDO1_CONFIG2_RUN_EN(x) \
    (((uint8_t)(((uint8_t)(x)) << PF5020_LDO1_CONFIG2_RUN_EN_SHIFT)) & PF5020_LDO1_CONFIG2_RUN_EN_MASK)

#define PF5020_LDO1_CONFIG2_LDO1_PDGRP_MASK  (0x60U)
#define PF5020_LDO1_CONFIG2_LDO1_PDGRP_SHIFT (5U)
#define PF5020_LDO1_CONFIG2_LDO1_PDGRP(x) \
    (((uint8_t)(((uint8_t)(x)) << PF5020_LDO1_CONFIG2_LDO1_PDGRP_SHIFT)) & PF5020_LDO1_CONFIG2_LDO1_PDGRP_MASK)

#define PF5020_CTRL1_WD_STBY_EN_MASK  (0x4U)
#define PF5020_CTRL1_WD_STBY_EN_SHIFT (2U)
#define PF5020_CTRL1_WD_STBY_EN(x) \
    (((uint8_t)(((uint8_t)(x)) << PF5020_CTRL1_WD_STBY_EN_SHIFT)) & PF5020_CTRL1_WD_STBY_EN_MASK)

#define PF5020_CTRL1_WD_EN_MASK  (0x8U)
#define PF5020_CTRL1_WD_EN_SHIFT (3U)
#define PF5020_CTRL1_WD_EN(x)    (((uint8_t)(((uint8_t)(x)) << PF5020_CTRL1_WD_EN_SHIFT)) & PF5020_CTRL1_WD_EN_MASK)

#define PF5020_CTRL1_TMP_MON_EN_MASK  (0x10U)
#define PF5020_CTRL1_TMP_MON_EN_SHIFT (4U)
#define PF5020_CTRL1_TMP_MON_EN(x) \
    (((uint8_t)(((uint8_t)(x)) << PF5020_CTRL1_TMP_MON_EN_SHIFT)) & PF5020_CTRL1_TMP_MON_EN_MASK)

#define PF5020_CTRL2_TMP_MON_AON_MASK  (0x10U)
#define PF5020_CTRL2_TMP_MON_AON_SHIFT (4U)
#define PF5020_CTRL2_TMP_MON_AON(x) \
    (((uint8_t)(((uint8_t)(x)) << PF5020_CTRL2_TMP_MON_AON_SHIFT)) & PF5020_CTRL2_TMP_MON_AON_MASK)

#define PF5020_CTRL3_PMIC_OFF_MASK  (0x2U)
#define PF5020_CTRL3_PMIC_OFF_SHIFT (1U)
#define PF5020_CTRL3_PMIC_OFF(x) \
    (((uint8_t)(((uint8_t)(x)) << PF5020_CTRL3_PMIC_OFF_SHIFT)) & PF5020_CTRL3_PMIC_OFF_MASK)

#define PF5020_CTRL3_UV_DB_MASK  (0x30U)
#define PF5020_CTRL3_UV_DB_SHIFT (4U)
#define PF5020_CTRL3_UV_DB(x)    (((uint8_t)(((uint8_t)(x)) << PF5020_CTRL3_UV_DB_SHIFT)) & PF5020_CTRL3_UV_DB_MASK)

#define PF5020_CTRL3_OV_DB_MASK  (0xC0U)
#define PF5020_CTRL3_OV_DB_SHIFT (6U)
#define PF5020_CTRL3_OV_DB(x)    (((uint8_t)(((uint8_t)(x)) << PF5020_CTRL3_OV_DB_SHIFT)) & PF5020_CTRL3_OV_DB_MASK)

#define PF5020_AMUX_AMUX_SEL_MASK  (0x1FU)
#define PF5020_AMUX_MAUX_SEL_SHIFT (0U)
#define PF5020_AMUX_MAUX_SEL(x)    (((uint8_t)(((uint8_t)(x)) << PF5020_AMUX_MAUX_SEL_SHIFT)) & PF5020_AMUX_AMUX_SEL_MASK)

#define PF5020_AMUX_AMUX_EN_MASK  (0x20U)
#define PF5020_AMUX_AMUX_EN_SHIFT (5U)
#define PF5020_AMUX_AMUX_EN(x)    (((uint8_t)(((uint8_t)(x)) << PF5020_AMUX_AMUX_EN_SHIFT)) & PF5020_AMUX_AMUX_EN_MASK)

#define PF5020_VMONEN1_SW1VMON_EN_MASK  (0x1U)
#define PF5020_VMONEN1_SW1VMON_EN_SHIFT (0U)
#define PF5020_VMONEN1_SW1VMON_EN(x) \
    (((uint8_t)(((uint8_t)(x)) << PF5020_VMONEN1_SW1VMON_EN_SHIFT)) & PF5020_VMONEN1_SW1VMON_EN_MASK)

#define PF5020_VMONEN1_SW2VMON_EN_MASK  (0x2U)
#define PF5020_VMONEN1_SW2VMON_EN_SHIFT (1U)
#define PF5020_VMONEN1_SW2VMON_EN(x) \
    (((uint8_t)(((uint8_t)(x)) << PF5020_VMONEN1_SW2VMON_EN_SHIFT)) & PF5020_VMONEN1_SW2VMON_EN_MASK)

#define PF5020_VMONEN1_SWND1VMON_EN_MASK  (0x40U)
#define PF5020_VMONEN1_SWND1VMON_EN_SHIFT (6U)
#define PF5020_VMONEN1_SWND1VMON_EN(x) \
    (((uint8_t)(((uint8_t)(x)) << PF5020_VMONEN1_SWND1VMON_EN_SHIFT)) & PF5020_VMONEN1_SWND1VMON_EN_MASK)

#define PF5020_VMONEN2_LDO1VMON_EN_MASK  (0x1U)
#define PF5020_VMONEN2_LDO1VMON_EN_SHIFT (0U)
#define PF5020_VMONEN2_LDO1VMON_EN(x) \
    (((uint8_t)(((uint8_t)(x)) << PF5020_VMONEN2_LDO1VMON_EN_SHIFT)) & PF5020_VMONEN2_LDO1VMON_EN_MASK)

#define PF5020_PWRUP_CTRL_RESETBMCU_PDGRP_MASK  (0xCU)
#define PF5020_PWRUP_CTRL_RESETBMCU_PDGRP_SHIFT (2U)
#define PF5020_PWRUP_CTRL_RESETBMCU_PDGRP(x) \
    (((uint8_t)(((uint8_t)(x)) << PF5020_PWRUP_CTRL_RESETBMCU_PDGRP_SHIFT)) & PF5020_PWRUP_CTRL_RESETBMCU_PDGRP_MASK)

#define PF5020_PWRUP_CTRL_PGOOD_PDGRP_MASK  (0x30U)
#define PF5020_PWRUP_CTRL_PGOOD_PDGRP_SHIFT (4U)
#define PF5020_PWRUP_CTRL_PGOOD_PDGRP(x) \
    (((uint8_t)(((uint8_t)(x)) << PF5020_PWRUP_CTRL_PGOOD_PDGRP_SHIFT)) & PF5020_PWRUP_CTRL_PGOOD_PDGRP_MASK)

#define PF5020_PWRUP_CTRL_PWRDWN_MODE_MASK  (0x40U)
#define PF5020_PWRUP_CTRL_PWRDWN_MODE_SHIFT (6U)
#define PF5020_PWRUP_CTRL_PWRDWN_MODE(x) \
    (((uint8_t)(((uint8_t)(x)) << PF5020_PWRUP_CTRL_PWRDWN_MODE_SHIFT)) & PF5020_PWRUP_CTRL_PWRDWN_MODE_MASK)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static status_t PF5020_SetRegulatorCommonConfig(pf5020_handle_t *handle,
                                                pf5020_regulator_name_t regulatorName,
                                                bool enableUVBypass,
                                                bool enableOVBypass,
                                                bool enableWatchdogBypass,
                                                bool enablePGMonitor,
                                                bool faultReEnabled,
                                                bool enableILIMBypass);

static status_t PF5020_MaskInterrupts(pf5020_handle_t *handle, uint64_t interruptMask, bool enableMask);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
static status_t PF5020_SetRegulatorCommonConfig(pf5020_handle_t *handle,
                                                pf5020_regulator_name_t regulatorName,
                                                bool enableUVBypass,
                                                bool enableOVBypass,
                                                bool enableWatchdogBypass,
                                                bool enablePGMonitor,
                                                bool faultReEnabled,
                                                bool enableILIMBypass)
{
    assert(handle);

    uint8_t regAddrShift;
    uint8_t tmp8;
    status_t status = kStatus_Success;

    /* Calculate register address shift based on regulator name. */
    if (regulatorName == kPF5020_RegulatorLdo1)
    {
        regAddrShift = ((uint8_t)regulatorName - 1U) * 8U + 7U;
    }
    else
    {
        regAddrShift = (uint8_t)regulatorName * 8U;
    }

    tmp8 = PF5020_REGULATOR_PG_EN(enablePGMonitor) | PF5020_REGULATOR_WDBYPASS(enableWatchdogBypass) |
           PF5020_REGULATOR_ILIM_BYPASS(enableILIMBypass) | PF5020_REGULATOR_OV_BYPASS(enableOVBypass) |
           PF5020_REGULATOR_UV_BYPASS(enableUVBypass);

    status = PF5020_ModifyReg(handle, PF5020_SW2_CONFIG1 + regAddrShift, 0xE3U, tmp8);

    if (status == kStatus_Success)
    {
        status = PF5020_ModifyReg(handle, PF5020_SW1_CONFIG2 + regAddrShift, 0x80U,
                                  PF5020_REGULATOR_FLT_REN(faultReEnabled));
    }

    return status;
}

static status_t PF5020_MaskInterrupts(pf5020_handle_t *handle, uint64_t interruptMask, bool enableMask)
{
    static const uint8_t maskRegArray[] = PF5020_INT_MASK_ARRAY;
    uint8_t maskReg;
    uint8_t regIndex;
    uint64_t tmp64;
    uint8_t maskRegValue;
    status_t status = kStatus_Success;

    for (regIndex = 0U; regIndex < 7U; regIndex++)
    {
        /* Get each interrupt mask register's value. */
        tmp64 = interruptMask & (0xFFULL << (regIndex * 8U));

        if (tmp64 != 0ULL)
        {
            if ((tmp64 & (uint64_t)kPF5020_ILIM_Ldo1IlimInterrupt) != 0ULL)
            {
                tmp64 &= (uint64_t)(~(uint64_t)kPF5020_ILIM_Ldo1IlimInterrupt);
                status = PF5020_WriteReg(handle, PF5020_LDO_ILIM_MASK, enableMask ? 0U : 1U);
            }
            if ((tmp64 & (uint64_t)kPF5020_UV_Ldo1UvInterrupt) != 0ULL)
            {
                tmp64 &= (uint64_t)(~(uint64_t)kPF5020_UV_Ldo1UvInterrupt);
                status = PF5020_WriteReg(handle, PF5020_LDO_UV_MASK, enableMask ? 0U : 1U);
            }

            if ((tmp64 & (uint64_t)kPF5020_OV_Ldo1OvInterrupt) != 0UL)
            {
                tmp64 &= (uint64_t)(~(uint64_t)kPF5020_OV_Ldo1OvInterrupt);
                status = PF5020_WriteReg(handle, PF5020_LDO_OV_MASK, enableMask ? 0U : 1U);
            }
            if (status == kStatus_Success)
            {
                maskRegValue = (uint8_t)((tmp64 >> (regIndex * 8U)) & 0xFFU);
                maskReg      = maskRegArray[regIndex];
                status = PF5020_ModifyReg(handle, maskReg, maskRegValue, enableMask ? (~maskRegValue) : maskRegValue);
            }
        }
    }

    return status;
}

/*!
 * brief Write to PF5020 register via I2C.
 *
 * param handle The pointer to pf5020_handle_t.
 * param regAddr The address of register to write.
 * param val The value to be write.
 *
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_WriteReg(pf5020_handle_t *handle, uint8_t regAddr, uint8_t val)
{
    assert(handle);
    assert(handle->I2C_SendFunc);

    return handle->I2C_SendFunc(handle->slaveAddress, regAddr, 1U, &val, 1U);
}

/*!
 * brief Read value from PF5020 register via I2C.
 *
 * param handle The pointer to pf5020_handle_t.
 * param regAddr The address of register to write.
 * param val Pointer store return value.
 *
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_ReadReg(pf5020_handle_t *handle, uint8_t regAddr, uint8_t *val)
{
    assert(handle);
    assert(handle->I2C_ReceiveFunc);

    return handle->I2C_ReceiveFunc(handle->slaveAddress, regAddr, 1U, val, 1U);
}

/*!
 * brief Read and modify the register value
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param regAddr The address of register.
 * param mask The mask of register bit to be modified.
 * param val The value to be set.
 *
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_ModifyReg(pf5020_handle_t *handle, uint8_t regAddr, uint8_t mask, uint8_t val)
{
    assert(handle);

    status_t status = kStatus_Success;
    uint8_t tmp8;

    status = PF5020_ReadReg(handle, regAddr, &tmp8);

    if (status == kStatus_Success)
    {
        tmp8 &= (uint8_t)~mask;
        tmp8 |= (val & mask);
        status = PF5020_WriteReg(handle, regAddr, tmp8);
    }

    return status;
}

/*!
 * brief Dump the value of continuous registers.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param regAddr The address of start register.
 * param buffer The buffer to store the dumped registers' value.
 * param length The length of the continuous registers to be dumped.
 *
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_DumpReg(pf5020_handle_t *handle, uint8_t regAddr, uint8_t *buffer, uint8_t length)
{
    assert(handle);
    assert(handle->I2C_ReceiveFunc);

    uint8_t i       = 0U;
    status_t status = kStatus_Success;

    for (i = 0U; i < length; i++)
    {
        status = PF5020_ReadReg(handle, regAddr++, buffer++);
        if (status != kStatus_Success)
        {
            /* In case of fail to read register. */
            break;
        }
    }

    return status;
}

/*!
 * brief Get default initialize configuration.
 *
 * code
 *   config->I2C_SendFunc = NULL;
 *   config->I2C_ReceiveFunc = NULL;
 *   config->slaveAddress = 0x08U;
 * endcode
 * param config The pointer to pf5020_config_t structure.
 */
void PF5020_GetDefaultConfig(pf5020_config_t *config)
{
    assert(config);

    config->I2C_SendFunc    = NULL;
    config->I2C_ReceiveFunc = NULL;
    /* In default, the slave address of PF5020 is 0x08. */
    config->slaveAddress = 0x08U;
}

/*!
 * brief Initialize runtime handle.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param config The pointer to pf5020_config_t structure.
 */
void PF5020_CreateHandle(pf5020_handle_t *handle, const pf5020_config_t *config)
{
    assert(handle);
    assert(config);

    handle->I2C_SendFunc    = config->I2C_SendFunc;
    handle->I2C_ReceiveFunc = config->I2C_ReceiveFunc;
    handle->slaveAddress    = config->slaveAddress;
}

/*!
 * brief Set power up sequencer time base.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param timeBase The time base value to set, please refer pf5020_sequencer_time_base_t for details.
 *
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SetSequencerTimeBase(pf5020_handle_t *handle, pf5020_sequencer_time_base_t timeBase)
{
    assert(handle);

    return PF5020_ModifyReg(handle, PF5020_PWRUP_CTRL, 0x3U, (uint8_t)timeBase & 0x3U);
}

/*!
 * brief Set power up sequence, when transitioning from standby state to run state, the power up sequencer is activated
 * only if any of the regulators is re-enabled during this transition.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param powerUpSeq The pointer to pf5020_power_up_sequence_t structure.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SetPowerUpSequence(pf5020_handle_t *handle, pf5020_power_up_sequence_t *powerUpSeq)
{
    assert(handle);
    assert(powerUpSeq);

    static const uint8_t seqReqArray[] = PF5020_SEQ_REG_ARRAY;
    uint8_t tmp8;
    uint8_t i;
    status_t status;

    for (i = 0U; i < 6U; i++)
    {
        status = PF5020_ReadReg(handle, seqReqArray[i], &tmp8);
        /* if the sequence order to set is same as register value, it is no need to set register again. */
        if ((tmp8 != *((uint8_t *)powerUpSeq + i)) && (status == kStatus_Success))
        {
            status = PF5020_WriteReg(handle, seqReqArray[i], *((uint8_t *)powerUpSeq + i));
        }

        if (status != kStatus_Success)
        {
            break;
        }
    }

    return status;
}

/*!
 * brief Set power down mode, sequential mode or group mode.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param powerDownMode The power down mode to set, please refer to pf5020_power_down_mode_t.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SetPowerDownMode(pf5020_handle_t *handle, pf5020_power_down_mode_t powerDownMode)
{
    assert(handle);

    return PF5020_ModifyReg(handle, PF5020_PWRUP_CTRL, PF5020_PWRUP_CTRL_PWRDWN_MODE_MASK,
                            PF5020_PWRUP_CTRL_PWRDWN_MODE(powerDownMode));
}

/*!
 * brief Set power down groups that each internal module placed to.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param groupConfig Pointer to the pf5020_power_down_group_config_t structure.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SetPowerDownGroups(pf5020_handle_t *handle, const pf5020_power_down_group_config_t *groupConfig)
{
    assert(handle);
    assert(groupConfig);

    status_t status;

    status = PF5020_ModifyReg(handle, PF5020_PWRUP_CTRL,
                              PF5020_PWRUP_CTRL_PGOOD_PDGRP_MASK | PF5020_PWRUP_CTRL_RESETBMCU_PDGRP_MASK,
                              PF5020_PWRUP_CTRL_RESETBMCU_PDGRP(groupConfig->resetBMCUGroup) |
                                  PF5020_PWRUP_CTRL_PGOOD_PDGRP(groupConfig->pGoodGroup));

    if (status == kStatus_Success)
    {
        status = PF5020_ModifyReg(handle, PF5020_SW1_MODE, PF5020_BUCK_REGULATOR_PDGPR_MASK,
                                  PF5020_BUCK_REGULATOR_PDGPR(groupConfig->sw1Group));
    }
    if (status == kStatus_Success)
    {
        status = PF5020_ModifyReg(handle, PF5020_SW2_MODE1, PF5020_BUCK_REGULATOR_PDGPR_MASK,
                                  PF5020_BUCK_REGULATOR_PDGPR(groupConfig->sw2Group));
    }
    if (status == kStatus_Success)
    {
        status = PF5020_ModifyReg(handle, PF5020_SWND1_MODE1, PF5020_BUCK_REGULATOR_PDGPR_MASK,
                                  PF5020_BUCK_REGULATOR_PDGPR(groupConfig->swnd1Group));
    }
    if (status == kStatus_Success)
    {
        status = PF5020_ModifyReg(handle, PF5020_LDO1_CONFIG2, PF5020_LDO1_CONFIG2_LDO1_PDGRP_MASK,
                                  PF5020_LDO1_CONFIG2_LDO1_PDGRP(groupConfig->ldo1Group));
    }

    return status;
}

/*!
 * brief Set selected power down group's delay.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param group The selected power down group, please refer to pf5020_power_down_group_t for details.
 * param delay The delay value to be set, please refer to pf5020_power_down_delay_t for details.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SetPowerDownGroupDelay(pf5020_handle_t *handle,
                                       pf5020_power_down_group_t group,
                                       pf5020_power_down_delay_t delay)
{
    assert(handle);

    return PF5020_ModifyReg(handle, PF5020_PWRDN_DLY1, (0x3U << (2U * (3U - (uint8_t)group))),
                            (uint8_t)delay << (2U * (3U - (uint8_t)group)));
}

/*!
 * brief Set delay to disable the regulators after RESETBMCU is asserted.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param delay The delay value, please refer to pf5020_resetBMCU_delay_t.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SetResetBMcuPinDelay(pf5020_handle_t *handle, pf5020_resetBMCU_delay_t delay)
{
    assert(handle);

    return PF5020_WriteReg(handle, PF5020_PWRDN_DLY2, (uint8_t)delay);
}

/*!
 * brief Turn off PF5020 PMIC.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_TurnOffPMIC(pf5020_handle_t *handle)
{
    assert(handle);

    return PF5020_ModifyReg(handle, PF5020_CTRL3, PF5020_CTRL3_PMIC_OFF_MASK, PF5020_CTRL3_PMIC_OFF_MASK);
}

/*!
 * brief Configure internal high speed clock.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param config The pointer to pf5020_high_speed_clk_config_t structure.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_CLK_ConfigHighSpeedClock(pf5020_handle_t *handle, const pf5020_high_speed_clk_config_t *config)
{
    assert(handle);
    assert(config);

    uint8_t tmp8;

    tmp8 = ((uint8_t)(config->clkFreq) | ((uint8_t)(config->enableSS) << 5U) | ((uint8_t)(config->ssRange) << 4U));
    return PF5020_ModifyReg(handle, PF5020_FREQ_CTRL, 0x3FU, tmp8);
}

/*!
 * brief Enable/disable clock sync out.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param enable Used to enable/disable sync output.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_CLK_EnableSyncOut(pf5020_handle_t *handle, bool enable)
{
    return PF5020_ModifyReg(handle, PF5020_FREQ_CTRL, 0x80U, enable ? 0x80U : 0U);
}

/*!
 * brief Set VSNS LDO output voltage.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param voltage The output voltage of VSNVS, please refer to pf5020_vsnvs_ldo_output_voltage_t.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SetVsnvsLdoOutputVoltage(pf5020_handle_t *handle, pf5020_vsnvs_ldo_output_voltage_t voltage)
{
    assert(handle);

    return PF5020_WriteReg(handle, PF5020_VSNVS_CONFIG1, (uint8_t)voltage);
}

/* SW1 Buck Regulator Control APIs. */
/*!
 * brief Set SW1 Buck regulator global configuration.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param config The pointer to pf5020_sw1_regulator_config_t structure.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW1_SetGlobalConfig(pf5020_handle_t *handle, const pf5020_sw1_regulator_config_t *config)
{
    assert(handle);
    assert(config);

    status_t status;
    uint8_t value         = 0U;
    uint8_t mask          = 0U;
    bool enableILIMBypass = true;

    /* Set SW1 DVS Ramp. */
    status = PF5020_ModifyReg(handle, PF5020_SW_RAMP, 0x7U, (uint8_t)(config->sw1DvsRamp));

    if (status == kStatus_Success)
    {
        /* Set SW1 output voltage in run state. */
        status = PF5020_WriteReg(handle, PF5020_SW1_RUN_VOLT, config->sw1RunOutputVolt);
    }
    if (status == kStatus_Success)
    {
        /* Set SW1 output voltage in standby state. */
        status = PF5020_WriteReg(handle, PF5020_SW1_STBY_VOLT, config->sw1StandbyOutputVolt);
    }

    if (status == kStatus_Success)
    {
        /* Update operate mode in run/standby state. */
        status = PF5020_ModifyReg(handle, PF5020_SW1_MODE,
                                  PF5020_BUCK_REGULATOR_RUN_MODE_MASK | PF5020_BUCK_REGULATOR_STANDBY_MODE_MASK,
                                  PF5020_BUCK_REGULATOR_RUN_MODE(config->sw1RunOperateMode) |
                                      PF5020_BUCK_REGULATOR_STANDBY_MODE(config->sw1StandbyOperateMode));
    }
    if (status == kStatus_Success)
    {
        if (config->sw1CurrentLimit != kPF5020_BuckRegulatorCurrentLimitBypass)
        {
            enableILIMBypass = false;
            value |= PF5020_BUCK_REGULATOR_ILIM(config->sw1CurrentLimit);
            mask |= PF5020_BUCK_REGULATOR_ILIM_MASK;
        }

        status = PF5020_SetRegulatorCommonConfig(
            handle, kPF5020_BuckRegulatorSw1, config->sw1EnableUVBypass, config->sw1EnableOVBypass,
            config->sw1EnableWatchdogBypass, config->sw1EnablePGMonitor, config->sw1FaultReEnabled, enableILIMBypass);

        if (status == kStatus_Success)
        {
            value |= PF5020_BUCK_REGULATOR_PHASE(config->sw1PhaseShift);
            mask |= PF5020_BUCK_REGULATOR_PHASE_MASK;
            /* Set SW1 Config2 register, this register can be used to set current limitation value and phase shift.  */
            status = PF5020_ModifyReg(handle, PF5020_SW1_CONFIG2, mask, value);
        }
    }

    return status;
}

/*!
 * brief Set DVS Ramp for SW1 buck regulator.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param dvsRamp The DVS ramp value to set, please refer to pf5020_type1_buck_regulator_dvs_ramp_t for details.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW1_SetDvsRamp(pf5020_handle_t *handle, pf5020_type1_buck_regulator_dvs_ramp_t dvsRamp)
{
    assert(handle);

    return PF5020_ModifyReg(handle, PF5020_SW_RAMP, 0x3U, (uint8_t)dvsRamp);
}

/*!
 * brief Set SW1 regulator's output voltage and operate mode in run state.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param runOutputVolt The output voltage of SW1 in run state.
 * param runOperateMode The operate mode of SW1 in run state.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW1_SetRunStateOption(pf5020_handle_t *handle,
                                      uint8_t runOutputVolt,
                                      pf5020_buck_regulator_operate_mode_t runOperateMode)
{
    assert(handle);

    uint8_t sw1RunMode;
    uint8_t sw1RunVolt;
    status_t status = kStatus_Success;

    (void)PF5020_ReadReg(handle, PF5020_SW1_MODE, &sw1RunMode);
    sw1RunMode &= PF5020_BUCK_REGULATOR_RUN_MODE_MASK;
    sw1RunMode = sw1RunMode >> PF5020_BUCK_REGULATOR_RUN_MODE_SHIFT;
    (void)PF5020_ReadReg(handle, PF5020_SW1_RUN_VOLT, &sw1RunVolt);

    if (sw1RunVolt != runOutputVolt)
    {
        status = PF5020_WriteReg(handle, PF5020_SW1_RUN_VOLT, runOutputVolt);
    }
    if ((sw1RunMode != (uint8_t)runOperateMode) && (status == kStatus_Success))
    {
        status = PF5020_ModifyReg(handle, PF5020_SW1_MODE, PF5020_BUCK_REGULATOR_RUN_MODE_MASK,
                                  PF5020_BUCK_REGULATOR_RUN_MODE(runOperateMode));
    }

    return status;
}

/*!
 * brief Set SW1 regulator's output voltage and operate mode in standby state.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param standbyOutputVolt The output voltage of SW1 in standby state.
 * param standbyOperateMode The operate mode of SW1 in standby state.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW1_SetStandbyStateOption(pf5020_handle_t *handle,
                                          uint8_t standbyOutputVolt,
                                          pf5020_buck_regulator_operate_mode_t standbyOperateMode)
{
    assert(handle);

    uint8_t sw1StandbyMode;
    uint8_t sw1StandbyVolt;
    status_t status = kStatus_Success;

    (void)PF5020_ReadReg(handle, PF5020_SW1_MODE, &sw1StandbyMode);
    sw1StandbyMode &= PF5020_BUCK_REGULATOR_STANDBY_MODE_MASK;
    sw1StandbyMode = sw1StandbyMode >> PF5020_BUCK_REGULATOR_STANDBY_MODE_SHIFT;

    (void)PF5020_ReadReg(handle, PF5020_SW1_STBY_VOLT, &sw1StandbyVolt);

    if (sw1StandbyVolt != standbyOutputVolt)
    {
        status = PF5020_WriteReg(handle, PF5020_SW1_STBY_VOLT, standbyOutputVolt);
    }

    if ((sw1StandbyMode != (uint8_t)standbyOperateMode) && (status == kStatus_Success))
    {
        status = PF5020_ModifyReg(handle, PF5020_SW1_MODE, PF5020_BUCK_REGULATOR_STANDBY_MODE_MASK,
                                  PF5020_BUCK_REGULATOR_STANDBY_MODE(standbyOperateMode));
    }

    return status;
}

/*!
 * brief Set SW1 regulator fault detection related options.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param currentLimit SW1 buck regulator current limitation value, please refer to
 *                      pf5020_buck_regulator_current_limit_t for details.
 * param enableUVBypass Enable/disable UV bypass.
 * param enableOVBypass Enable/disable OV bypass.
 * param faultReEnabled Used to control whether return to sw1 regulator previous state if fault condition is cleared.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW1_SetFaultDetection(pf5020_handle_t *handle,
                                      pf5020_buck_regulator_current_limit_t currentLimit,
                                      bool enableUVBypass,
                                      bool enableOVBypass,
                                      bool faultReEnabled)
{
    assert(handle);

    status_t status;
    bool enableILIMBypass   = false;
    uint8_t sw1Config2Mask  = 0U;
    uint8_t sw1Config2Value = 0U;

    if (currentLimit == kPF5020_BuckRegulatorCurrentLimitBypass)
    {
        enableILIMBypass = true;
    }
    else
    {
        sw1Config2Mask |= PF5020_BUCK_REGULATOR_ILIM_MASK;
        sw1Config2Value |= PF5020_BUCK_REGULATOR_ILIM(currentLimit);
    }

    sw1Config2Mask |= PF5020_REGULATOR_FLT_REN_MASK;
    sw1Config2Value |= PF5020_REGULATOR_FLT_REN(faultReEnabled);
    status = PF5020_ModifyReg(handle, PF5020_SW1_CONFIG2, sw1Config2Mask, sw1Config2Value);

    if (status == kStatus_Success)
    {
        status = PF5020_ModifyReg(
            handle, PF5020_SW1_CONFIG1,
            PF5020_REGULATOR_ILIM_BYPASS_MASK | PF5020_REGULATOR_OV_BYPASS_MASK | PF5020_REGULATOR_UV_BYPASS_MASK,
            PF5020_REGULATOR_ILIM_BYPASS(enableILIMBypass) | PF5020_REGULATOR_OV_BYPASS(enableOVBypass) |
                PF5020_REGULATOR_UV_BYPASS(enableUVBypass));
    }

    return status;
}

/*!
 * brief Set SW1 regulator phase shift value.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param phaseShift SW1 buck regulator phase shift value, please refer to pf5020_buck_regulator_phase_shift_t
 *                   for details.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW1_SetPhaseShift(pf5020_handle_t *handle, pf5020_buck_regulator_phase_shift_t phaseShift)
{
    assert(handle);

    status_t status = kStatus_Success;
    uint8_t sw1Phase;

    (void)PF5020_ReadReg(handle, PF5020_SW1_CONFIG2, &sw1Phase);
    sw1Phase &= PF5020_BUCK_REGULATOR_PHASE_MASK;
    sw1Phase = sw1Phase >> PF5020_BUCK_REGULATOR_PHASE_SHIFT;

    if (sw1Phase != (uint8_t)phaseShift)
    {
        status = PF5020_ModifyReg(handle, PF5020_SW1_CONFIG2, PF5020_BUCK_REGULATOR_PHASE_MASK,
                                  PF5020_BUCK_REGULATOR_PHASE(phaseShift));
    }

    return status;
}

/*!
 * brief Enable/disable PG monitor for SW1 regulator.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param enable Enable/disable PG monitor.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW1_EnablePGMonitor(pf5020_handle_t *handle, bool enable)
{
    assert(handle);

    return PF5020_ModifyReg(handle, PF5020_SW1_CONFIG1, PF5020_REGULATOR_PG_EN_MASK, PF5020_REGULATOR_PG_EN(enable));
}

/*!
 * brief Enable/disable watchdog bypass for SW1 regulator.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param enable Enable/disable watchdog bypass.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW1_EnableWatchDogBypass(pf5020_handle_t *handle, bool enable)
{
    assert(handle);

    return PF5020_ModifyReg(handle, PF5020_SW1_CONFIG1, PF5020_REGULATOR_WDBYPASS_MASK,
                            PF5020_REGULATOR_WDBYPASS(enable));
}

/*!
 * brief Set SW2 Buck regulator global configuration.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param config The pointer to pf5020_sw2_regulator_config_t structure.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW2_SetGlobalConfig(pf5020_handle_t *handle, const pf5020_sw2_regulator_config_t *config)
{
    assert(handle);
    assert(config);

    status_t status;
    uint8_t value         = 0U;
    uint8_t mask          = 0U;
    bool enableILIMBypass = true;

    /* Set SW2 DVS Ramp. */
    status = PF5020_ModifyReg(handle, PF5020_SW_RAMP, 0xCU, ((uint8_t)config->sw2DvsRamp) << 2U);

    if (status == kStatus_Success)
    {
        /* Set SW2 output voltage in run state. */
        status = PF5020_WriteReg(handle, PF5020_SW2_RUN_VOLT, config->sw2RunOutputVolt);
    }
    if (status == kStatus_Success)
    {
        /* Set SW2 output voltage in standby state. */
        status = PF5020_WriteReg(handle, PF5020_SW2_STBY_VOLT, config->sw2StandbyOutputVolt);
    }

    if (status == kStatus_Success)
    {
        /* Update SW2 operate mode in run/standby state. */
        status = PF5020_ModifyReg(handle, PF5020_SW2_MODE1,
                                  PF5020_BUCK_REGULATOR_RUN_MODE_MASK | PF5020_BUCK_REGULATOR_STANDBY_MODE_MASK,
                                  PF5020_BUCK_REGULATOR_RUN_MODE(config->sw2RunOperateMode) |
                                      PF5020_BUCK_REGULATOR_STANDBY_MODE(config->sw2StandbyOperateMode));
    }
    if (status == kStatus_Success)
    {
        if (config->sw2CurrentLimit != kPF5020_BuckRegulatorCurrentLimitBypass)
        {
            enableILIMBypass = false;
            value |= PF5020_BUCK_REGULATOR_ILIM(config->sw2CurrentLimit);
            mask |= PF5020_BUCK_REGULATOR_ILIM_MASK;
        }
        status = PF5020_SetRegulatorCommonConfig(
            handle, kPF5020_BuckRegulatorSw2, config->sw2EnableUVBypass, config->sw2EnableOVBypass,
            config->sw2EnableWatchdogBypass, config->sw2EnablePGMonitor, config->sw2FaultReEnabled, enableILIMBypass);

        if (status == kStatus_Success)
        {
            value |= PF5020_BUCK_REGULATOR_PHASE(config->sw2PhaseShift) |
                     PF5020_SW2_CONFIG2_VTTEN(config->sw2EnableVTTOperation);
            mask |= PF5020_BUCK_REGULATOR_PHASE_MASK | PF5020_SW2_CONFIG2_VTTEN_MASK;
            /* Update SW2 CONFIG2 register, this register can be used to set current limitation and phase shift. */
            status = PF5020_ModifyReg(handle, PF5020_SW2_CONFIG2, mask, value);
        }
    }

    return status;
}

/*!
 * brief Set DVS Ramp for SW2 buck regulator.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param dvsRamp The DVS ramp value to set, please refer to pf5020_type1_buck_regulator_dvs_ramp_t for details.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW2_SetDvsRamp(pf5020_handle_t *handle, pf5020_type1_buck_regulator_dvs_ramp_t dvsRamp)
{
    assert(handle);

    return PF5020_ModifyReg(handle, PF5020_SW_RAMP, 0xCU, ((uint8_t)dvsRamp << 2U));
}

/*!
 * brief Set SW2 regulator's output voltage and operate mode in run state.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param runOutputVolt The output voltage of SW2 in run state.
 * param runOperateMode The operate mode of SW2 in run state.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW2_SetRunStateOption(pf5020_handle_t *handle,
                                      uint8_t runOutputVolt,
                                      pf5020_buck_regulator_operate_mode_t runOperateMode)
{
    assert(handle);

    uint8_t sw2RunMode;
    uint8_t sw2RunVolt;
    status_t status = kStatus_Success;

    (void)PF5020_ReadReg(handle, PF5020_SW2_MODE1, &sw2RunMode);
    sw2RunMode &= PF5020_BUCK_REGULATOR_RUN_MODE_MASK;
    sw2RunMode = sw2RunMode >> PF5020_BUCK_REGULATOR_RUN_MODE_SHIFT;
    (void)PF5020_ReadReg(handle, PF5020_SW2_RUN_VOLT, &sw2RunVolt);

    if (sw2RunVolt != runOutputVolt)
    {
        status = PF5020_WriteReg(handle, PF5020_SW2_RUN_VOLT, runOutputVolt);
    }
    if ((sw2RunMode != (uint8_t)runOperateMode) && (status == kStatus_Success))
    {
        status = PF5020_ModifyReg(handle, PF5020_SW2_MODE1, PF5020_BUCK_REGULATOR_RUN_MODE_MASK,
                                  PF5020_BUCK_REGULATOR_RUN_MODE(runOperateMode));
    }

    return status;
}

/*!
 * brief Set SW2 regulator's output voltage and operate mode in standby state.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param standbyOutputVolt The output voltage of SW2 in standby state.
 * param standbyOperateMode The operate mode of SW2 in standby state.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW2_SetStandbyStateOption(pf5020_handle_t *handle,
                                          uint8_t standbyOutputVolt,
                                          pf5020_buck_regulator_operate_mode_t standbyOperateMode)
{
    assert(handle);

    uint8_t sw2StandbyMode;
    uint8_t sw2StandbyVolt;
    status_t status = kStatus_Success;

    (void)PF5020_ReadReg(handle, PF5020_SW2_MODE1, &sw2StandbyMode);
    sw2StandbyMode &= PF5020_BUCK_REGULATOR_STANDBY_MODE_MASK;
    sw2StandbyVolt = sw2StandbyMode >> PF5020_BUCK_REGULATOR_STANDBY_MODE_SHIFT;

    (void)PF5020_ReadReg(handle, PF5020_SW2_STBY_VOLT, &sw2StandbyVolt);

    if (sw2StandbyVolt != standbyOutputVolt)
    {
        status = PF5020_WriteReg(handle, PF5020_SW2_STBY_VOLT, standbyOutputVolt);
    }

    if ((sw2StandbyMode != (uint8_t)standbyOperateMode) && (status == kStatus_Success))
    {
        status = PF5020_ModifyReg(handle, PF5020_SW2_MODE1, PF5020_BUCK_REGULATOR_STANDBY_MODE_MASK,
                                  PF5020_BUCK_REGULATOR_STANDBY_MODE(standbyOperateMode));
    }

    return status;
}

/*!
 * brief Set SW2 regulator phase shift value.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param phaseShift SW2 buck regulator phase shift value, please refer to pf5020_buck_regulator_phase_shift_t
 *                   for details.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW2_SetPhaseShift(pf5020_handle_t *handle, pf5020_buck_regulator_phase_shift_t phaseShift)
{
    assert(handle);

    status_t status = kStatus_Success;
    uint8_t sw2Phase;

    (void)PF5020_ReadReg(handle, PF5020_SW2_CONFIG2, &sw2Phase);
    sw2Phase &= PF5020_BUCK_REGULATOR_PHASE_MASK;
    sw2Phase = sw2Phase >> PF5020_BUCK_REGULATOR_PHASE_SHIFT;

    if (sw2Phase != (uint8_t)phaseShift)
    {
        status = PF5020_ModifyReg(handle, PF5020_SW2_CONFIG2, PF5020_BUCK_REGULATOR_PHASE_MASK,
                                  PF5020_BUCK_REGULATOR_PHASE(phaseShift));
    }

    return status;
}

/*!
 * brief Enable/disable SW2 VTT operateion.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param enable Used to enable/disable VTT operation.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW2_EnableVTTOperation(pf5020_handle_t *handle, bool enable)
{
    return PF5020_ModifyReg(handle, PF5020_SW2_CONFIG2, PF5020_SW2_CONFIG2_VTTEN_MASK,
                            PF5020_SW2_CONFIG2_VTTEN(enable));
}

/*!
 * brief Set SW2 regulator fault detection related options.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param currentLimit SW2 buck regulator current limitation value, please refer to
 *                      pf5020_buck_regulator_current_limit_t for details.
 * param enableUVBypass Enable/disable UV bypass.
 * param enableOVBypass Enable/disable OV bypass.
 * param faultReEnabled Used to control whether return to sw1 regulator previous state if fault condition is cleared.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW2_SetFaultDetection(pf5020_handle_t *handle,
                                      pf5020_buck_regulator_current_limit_t currentLimit,
                                      bool enableUVBypass,
                                      bool enableOVBypass,
                                      bool faultReEnabled)
{
    assert(handle);

    status_t status;
    bool enableILIMBypass   = false;
    uint8_t sw2Config2Mask  = 0U;
    uint8_t sw2Config2Value = 0U;

    if (currentLimit == kPF5020_BuckRegulatorCurrentLimitBypass)
    {
        enableILIMBypass = true;
    }
    else
    {
        sw2Config2Mask |= PF5020_BUCK_REGULATOR_ILIM_MASK;
        sw2Config2Value |= PF5020_BUCK_REGULATOR_ILIM(currentLimit);
    }

    sw2Config2Mask |= PF5020_REGULATOR_FLT_REN_MASK;
    sw2Config2Value |= PF5020_REGULATOR_FLT_REN(faultReEnabled);
    status = PF5020_ModifyReg(handle, PF5020_SW1_CONFIG2, sw2Config2Mask, sw2Config2Value);

    if (status == kStatus_Success)
    {
        status = PF5020_ModifyReg(
            handle, PF5020_SW1_CONFIG1,
            PF5020_REGULATOR_ILIM_BYPASS_MASK | PF5020_REGULATOR_OV_BYPASS_MASK | PF5020_REGULATOR_UV_BYPASS_MASK,
            PF5020_REGULATOR_ILIM_BYPASS(enableILIMBypass) | PF5020_REGULATOR_OV_BYPASS(enableOVBypass) |
                PF5020_REGULATOR_UV_BYPASS(enableUVBypass));
    }

    return status;
}

/*!
 * brief Enable/disable PG monitor for SW2 regulator.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param enable Enable/disable PG monitor.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW2_EnablePGMonitor(pf5020_handle_t *handle, bool enable)
{
    return PF5020_ModifyReg(handle, PF5020_SW2_CONFIG1, PF5020_REGULATOR_PG_EN_MASK, PF5020_REGULATOR_PG_EN(enable));
}

/*!
 * brief Enable/disable watchdog bypass for SW2 regulator.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param enable Enable/disable watchdog bypass.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SW2_EnableWatchDogBypass(pf5020_handle_t *handle, bool enable)
{
    return PF5020_ModifyReg(handle, PF5020_SW2_CONFIG1, PF5020_REGULATOR_WDBYPASS_MASK,
                            PF5020_REGULATOR_WDBYPASS(enable));
}

/*!
 * brief Set SWND1 Buck regulator global configuration.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param config The pointer to pf5020_swnd1_regulator_config_t structure.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SWND1_SetGlobalConfig(pf5020_handle_t *handle, const pf5020_swnd1_regulator_config_t *config)
{
    assert(handle);
    assert(config);

    status_t status       = kStatus_Success;
    uint8_t value         = 0U;
    uint8_t mask          = 0U;
    bool enableILIMBypass = true;

    /* Set output voltage in run/standby state. */
    status = PF5020_WriteReg(handle, PF5020_SWND1_RUN_VOLT, (uint8_t)(config->swnd1OutputVolt));

    if (status == kStatus_Success)
    {
        /* Set SWND1 operate mode in run/standby state. */
        status = PF5020_ModifyReg(handle, PF5020_SWND1_MODE1,
                                  PF5020_BUCK_REGULATOR_RUN_MODE_MASK | PF5020_BUCK_REGULATOR_STANDBY_MODE_MASK,
                                  PF5020_BUCK_REGULATOR_RUN_MODE(config->swnd1RunOperateMode) |
                                      PF5020_BUCK_REGULATOR_STANDBY_MODE(config->swnd1StandbyOperateMode));
    }

    if (status == kStatus_Success)
    {
        if (config->swnd1CurrentLimit != kPF5020_BuckRegulatorCurrentLimitBypass)
        {
            enableILIMBypass = false;
            value |= PF5020_BUCK_REGULATOR_ILIM(config->swnd1CurrentLimit);
            mask |= PF5020_BUCK_REGULATOR_ILIM_MASK;
        }
        status = PF5020_SetRegulatorCommonConfig(handle, kPF5020_BuckRegulatorSwnd1, config->swnd1EnableUVBypass,
                                                 config->swnd1EnableOVBypass, config->swnd1EnableWatchdogBypass,
                                                 config->swnd1EnablePGMonitor, config->swnd1FaultReEnabled,
                                                 enableILIMBypass);

        if (status == kStatus_Success)
        {
            value |= PF5020_BUCK_REGULATOR_PHASE(config->swnd1PhaseShift);
            mask |= PF5020_BUCK_REGULATOR_PHASE_MASK;
            /* Update SWND1 CONFIG2 register, this register can be used to set current limitation and phase shift. */
            status = PF5020_ModifyReg(handle, PF5020_SWND1_CONFIG2, mask, value);
        }
    }

    return status;
}

/*!
 * brief Set run/standby output voltage for SWND1 regulator.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param outputVolt The output voltage of SWND1 regulator in run/standby state,
 *                  please refer to pf5020_swnd1_output_voltage_t for details.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SWND1_SetOutputVoltage(pf5020_handle_t *handle, pf5020_swnd1_output_voltage_t outputVolt)
{
    assert(handle);

    uint8_t swnd1Volt;
    status_t status = kStatus_Success;

    (void)PF5020_ReadReg(handle, PF5020_SWND1_RUN_VOLT, &swnd1Volt);

    if (swnd1Volt != (uint8_t)outputVolt)
    {
        status = PF5020_WriteReg(handle, PF5020_SWND1_RUN_VOLT, (uint8_t)outputVolt);
    }

    return status;
}

/*!
 * brief Set SWND1 regulator's operate mode in run and standby state.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param runOperateMode The operate mode of SWND1 in run state, please refer to pf5020_buck_regulator_operate_mode_t.
 * param standbyOperateMode The operate mode of SWND1 in standby state, please refer to
 * pf5020_buck_regulator_operate_mode_t. retval #kStatus_Success The transaction was started successfully. retval
 * #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking transaction is already in
 * progress.
 */
status_t PF5020_SWND1_SetOperateMode(pf5020_handle_t *handle,
                                     pf5020_buck_regulator_operate_mode_t runOperateMode,
                                     pf5020_buck_regulator_operate_mode_t standbyOperateMode)
{
    assert(handle);

    uint8_t tmp8;
    uint8_t swnd1RunMode;
    uint8_t swnd1StandbyMode;
    status_t status;

    (void)PF5020_ReadReg(handle, PF5020_SWND1_MODE1, &tmp8);

    swnd1RunMode     = (tmp8 & PF5020_BUCK_REGULATOR_RUN_MODE_MASK);
    swnd1StandbyMode = ((tmp8 & PF5020_BUCK_REGULATOR_STANDBY_MODE_MASK) >> PF5020_BUCK_REGULATOR_STANDBY_MODE_SHIFT);

    if (swnd1RunMode != (uint8_t)runOperateMode)
    {
        tmp8 =
            ((tmp8 & (uint8_t)(~PF5020_BUCK_REGULATOR_RUN_MODE_MASK)) | PF5020_BUCK_REGULATOR_RUN_MODE(runOperateMode));
    }

    if (swnd1StandbyMode != (uint8_t)standbyOperateMode)
    {
        tmp8 = ((tmp8 & (uint8_t)(~PF5020_BUCK_REGULATOR_STANDBY_MODE_MASK)) |
                PF5020_BUCK_REGULATOR_STANDBY_MODE(standbyOperateMode));
    }

    status = PF5020_WriteReg(handle, PF5020_SWND1_MODE1, tmp8);

    return status;
}

/*!
 * brief Set SWND1 regulator phase shift value.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param phaseShift SWND1 buck regulator phase shift value, please refer to pf5020_buck_regulator_phase_shift_t
 *                   for details.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SWND1_SetPhaseShift(pf5020_handle_t *handle, pf5020_buck_regulator_phase_shift_t phaseShift)
{
    assert(handle);

    status_t status = kStatus_Success;
    uint8_t swnd1Phase;

    (void)PF5020_ReadReg(handle, PF5020_SWND1_CONFIG2, &swnd1Phase);
    swnd1Phase &= PF5020_BUCK_REGULATOR_PHASE_MASK;
    swnd1Phase = swnd1Phase >> PF5020_BUCK_REGULATOR_PHASE_SHIFT;

    if (swnd1Phase != (uint8_t)phaseShift)
    {
        status = PF5020_ModifyReg(handle, PF5020_SWND1_CONFIG2, PF5020_BUCK_REGULATOR_PHASE_MASK,
                                  PF5020_BUCK_REGULATOR_PHASE(phaseShift));
    }

    return status;
}

/*!
 * brief Set SWND1 regulator fault detection related options.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param currentLimit SWND1 buck regulator current limitation value, please refer to
 *                      pf5020_buck_regulator_current_limit_t for details.
 * param enableUVBypass Enable/disable UV bypass.
 * param enableOVBypass Enable/disable OV bypass.
 * param faultReEnabled Used to control whether return to sw1 regulator previous state if fault condition is cleared.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SWND1_SetFaultDetection(pf5020_handle_t *handle,
                                        pf5020_buck_regulator_current_limit_t currentLimit,
                                        bool enableUVBypass,
                                        bool enableOVBypass,
                                        bool faultReEnabled)
{
    assert(handle);

    status_t status;
    bool enableILIMBypass     = false;
    uint8_t swnd1Config2Mask  = 0U;
    uint8_t swnd1Config2Value = 0U;

    if (currentLimit == kPF5020_BuckRegulatorCurrentLimitBypass)
    {
        enableILIMBypass = true;
    }
    else
    {
        swnd1Config2Mask |= PF5020_BUCK_REGULATOR_ILIM_MASK;
        swnd1Config2Value |= PF5020_BUCK_REGULATOR_ILIM(currentLimit);
    }

    swnd1Config2Mask |= PF5020_REGULATOR_FLT_REN_MASK;
    swnd1Config2Value |= PF5020_REGULATOR_FLT_REN(faultReEnabled);
    status = PF5020_ModifyReg(handle, PF5020_SWND1_CONFIG2, swnd1Config2Mask, swnd1Config2Value);

    if (status == kStatus_Success)
    {
        status = PF5020_ModifyReg(
            handle, PF5020_SWND1_CONFIG1,
            PF5020_REGULATOR_ILIM_BYPASS_MASK | PF5020_REGULATOR_OV_BYPASS_MASK | PF5020_REGULATOR_UV_BYPASS_MASK,
            PF5020_REGULATOR_ILIM_BYPASS(enableILIMBypass) | PF5020_REGULATOR_OV_BYPASS(enableOVBypass) |
                PF5020_REGULATOR_UV_BYPASS(enableUVBypass));
    }

    return status;
}

/*!
 * brief Enable/disable PG monitor for SWND1 regulator.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param enable Enable/disable PG monitor.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SWND1_EnablePGMonitor(pf5020_handle_t *handle, bool enable)
{
    assert(handle);

    return PF5020_ModifyReg(handle, PF5020_SWND1_CONFIG1, PF5020_REGULATOR_PG_EN_MASK, PF5020_REGULATOR_PG_EN(enable));
}

/*!
 * brief Enable/disable watchdog bypass for SW1 regulator.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param enable Enable/disable watchdog bypass.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SWND1_EnableWatchDogBypass(pf5020_handle_t *handle, bool enable)
{
    assert(handle);

    return PF5020_ModifyReg(handle, PF5020_SWND1_CONFIG1, PF5020_REGULATOR_WDBYPASS_MASK,
                            PF5020_REGULATOR_WDBYPASS(enable));
}

/*!
 * brief Set LDO1 global configuration.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param config The pointer to pf5020_ldo1_regulator_config structure.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_LDO1_SetGlobalConfig(pf5020_handle_t *handle, const pf5020_ldo1_regulator_config *config)
{
    assert(handle);
    assert(config);

    status_t status = kStatus_Success;

    /* Set LDO1 output voltage in run state. */
    status = PF5020_WriteReg(handle, PF5020_LDO1_RUN_VOLT, (uint8_t)(config->ldo1RunOutputVolt));

    if (status == kStatus_Success)
    {
        /* Set LDO1 output voltage in standby state. */
        status = PF5020_WriteReg(handle, PF5020_LDO1_STBY_VOLT, (uint8_t)(config->ldo1StandbyOutputVolt));
    }

    if (status == kStatus_Success)
    {
        status = PF5020_ModifyReg(
            handle, PF5020_LDO1_CONFIG2, PF5020_LDO1_CONFIG2_RUN_EN_MASK | PF5020_LDO1_CONFIG2_STBY_EN_MASK,
            PF5020_LDO1_CONFIG2_STBY_EN(config->ldo1StandbyEnable) | PF5020_LDO1_CONFIG2_RUN_EN(config->ldo1RunEnable));
    }

    if (status == kStatus_Success)
    {
        status = PF5020_SetRegulatorCommonConfig(handle, kPF5020_RegulatorLdo1, config->ldo1EnableUVBypass,
                                                 config->ldo1EnableOVBypass, config->ldo1EnableWatchdogBypass,
                                                 config->ldo1EnablePGMonitor, config->ldo1FaultReEnabled,
                                                 config->ldo1EnableILIMBypass);
    }

    return status;
}

/*!
 * brief Set LDO1 regulator's output voltage and operate mode in run state.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param runEnable Enable/disable LDO1 in run state.
 * param runOuputVolt The output voltage of LDO1 in run state, please refer to pf5020_ldo1_output_voltage_t.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_LDO1_SetRunStateOption(pf5020_handle_t *handle,
                                       bool runEnable,
                                       pf5020_ldo1_output_voltage_t runOuputVolt)
{
    assert(handle);

    status_t status;

    if (runEnable)
    {
        status = PF5020_WriteReg(handle, PF5020_LDO1_RUN_VOLT, (uint8_t)runOuputVolt);
    }
    else
    {
        status = PF5020_ModifyReg(handle, PF5020_LDO1_CONFIG2, PF5020_LDO1_CONFIG2_RUN_EN_MASK,
                                  PF5020_LDO1_CONFIG2_RUN_EN(runEnable));
    }

    return status;
}

/*!
 * brief Set LDO1 regulator's output voltage and operate mode in standby state.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param standbyEnable Enable/disable LDO1 in standby state.
 * param standbyOuputVolt The output voltage of LDO1 in standby state, please refer to pf5020_ldo1_output_voltage_t.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_LDO1_SetStandbyStateOption(pf5020_handle_t *handle,
                                           bool standbyEnable,
                                           pf5020_ldo1_output_voltage_t standbyOuputVolt)
{
    assert(handle);

    status_t status;

    if (standbyEnable)
    {
        status = PF5020_WriteReg(handle, PF5020_LDO1_STBY_VOLT, (uint8_t)standbyOuputVolt);
    }
    else
    {
        status = PF5020_ModifyReg(handle, PF5020_LDO1_CONFIG2, PF5020_LDO1_CONFIG2_STBY_EN_MASK,
                                  PF5020_LDO1_CONFIG2_STBY_EN(standbyEnable));
    }

    return status;
}

/*!
 * brief Set SWND1 regulator fault detection related options.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param enableILIMBypass Enable/disable ILIM bypass.
 * param enableUVBypass Enable/disable UV bypass.
 * param enableOVBypass Enable/disable OV bypass.
 * param faultReEnabled Used to control whether return to ldos1 regulator previous state if fault condition is cleared.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_LDO1_SetFaultDetection(
    pf5020_handle_t *handle, bool enableILIMBypass, bool enableUVBypass, bool enableOVBypass, bool faultReEnabled)
{
    assert(handle);

    status_t status;

    status = PF5020_ModifyReg(
        handle, PF5020_LDO1_CONFIG1,
        PF5020_REGULATOR_ILIM_BYPASS_MASK | PF5020_REGULATOR_OV_BYPASS_MASK | PF5020_REGULATOR_UV_BYPASS_MASK,
        PF5020_REGULATOR_ILIM_BYPASS(enableILIMBypass) | PF5020_REGULATOR_OV_BYPASS(enableOVBypass) |
            PF5020_REGULATOR_UV_BYPASS(enableUVBypass));

    if (status == kStatus_Success)
    {
        status = PF5020_ModifyReg(handle, PF5020_LDO1_CONFIG2, PF5020_REGULATOR_FLT_REN_MASK,
                                  PF5020_REGULATOR_FLT_REN(faultReEnabled));
    }

    return status;
}

/*!
 * brief Enable/disable PG monitor for LDO1 regulator.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param enable Enable/disable PG monitor.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_LDO1_EnablePGMonitor(pf5020_handle_t *handle, bool enable)
{
    assert(handle);

    return PF5020_ModifyReg(handle, PF5020_LDO1_CONFIG1, PF5020_REGULATOR_PG_EN_MASK, PF5020_REGULATOR_PG_EN(enable));
}

/*!
 * brief Enable/disable watchdog bypass for LDO1 regulator.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param enable Enable/disable watchdog bypass.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_LDO1_EnableWatchDogBypass(pf5020_handle_t *handle, bool enable)
{
    assert(handle);

    return PF5020_ModifyReg(handle, PF5020_LDO1_CONFIG1, PF5020_REGULATOR_WDBYPASS_MASK,
                            PF5020_REGULATOR_WDBYPASS(enable));
}

/*!
 * brief Set voltage monitor debounce time.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param uvDebounceTime UV monitor debounce time, please refer to pf5020_uv_debounce_time_t.
 * param ovDebounceTime OV monitor debounce time, please refer to pf5020_ov_debounce_time_t.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SetVoltageMonitorDebounceTime(pf5020_handle_t *handle,
                                              pf5020_uv_debounce_time_t uvDebounceTime,
                                              pf5020_ov_debounce_time_t ovDebounceTime)
{
    assert(handle);

    return PF5020_ModifyReg(handle, PF5020_CTRL3, PF5020_CTRL3_UV_DB_MASK | PF5020_CTRL3_OV_DB_MASK,
                            PF5020_CTRL3_UV_DB(uvDebounceTime) | PF5020_CTRL3_OV_DB(ovDebounceTime));
}

/*!
 * brief Enable/disable selected regulator's voltage monitor.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param name The regulator to be set.
 * param enable Enable/disable voltage monitor.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_EnableVoltageMonitor(pf5020_handle_t *handle, pf5020_regulator_name_t name, bool enable)
{
    assert(handle);

    status_t status = kStatus_Success;

    switch (name)
    {
        case kPF5020_BuckRegulatorSw1:
        {
            status = PF5020_ModifyReg(handle, PF5020_VMONEN1, PF5020_VMONEN1_SW1VMON_EN_MASK,
                                      PF5020_VMONEN1_SW1VMON_EN(enable));
            break;
        }
        case kPF5020_BuckRegulatorSw2:
        {
            status = PF5020_ModifyReg(handle, PF5020_VMONEN1, PF5020_VMONEN1_SW2VMON_EN_MASK,
                                      PF5020_VMONEN1_SW2VMON_EN(enable));
            break;
        }
        case kPF5020_BuckRegulatorSwnd1:
        {
            status = PF5020_ModifyReg(handle, PF5020_VMONEN1, PF5020_VMONEN1_SWND1VMON_EN_MASK,
                                      PF5020_VMONEN1_SWND1VMON_EN(enable));
            break;
        }
        case kPF5020_RegulatorLdo1:
        {
            status = PF5020_ModifyReg(handle, PF5020_VMONEN2, PF5020_VMONEN2_LDO1VMON_EN_MASK,
                                      PF5020_VMONEN2_LDO1VMON_EN(enable));
            break;
        }
        default:
        {
            assert(false);
            break;
        }
    }

    return status;
}

/*!
 * brief Set fault counter maximum value.
 *
 * param handle Pointer to the pf5020_handle_t structure.
 * param maxValue Ranges from 0 to 15.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SetFaultCounterMaxValue(pf5020_handle_t *handle, uint8_t maxValue)
{
    assert(handle);

    return PF5020_ModifyReg(handle, PF5020_FAULT_COUNTER, 0xF0U, ((maxValue << 4U) & 0xF0U));
}

/*!
 * brief Get fault counter current value.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
uint8_t PF5020_GetFaultCounterCurrentValue(pf5020_handle_t *handle)
{
    assert(handle);

    uint8_t tmp8;

    (void)PF5020_ReadReg(handle, PF5020_FAULT_COUNTER, &tmp8);
    tmp8 = tmp8 & 0x0FU;

    return tmp8;
}

/*!
 * brief Set the expire value of the fault timer, when a regulator experiences a fault event, a fault timer will start.
 *
 * param handle Pointer to the pf5020_handle_t structure.
 * param expireValue The expire value of fault timer, ranges from 0 to 11, the actual expire time = 2 ^ expireValue.
 *
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_SetFaultTimerExpireValue(pf5020_handle_t *handle, uint8_t expireValue)
{
    assert(handle);

    return PF5020_ModifyReg(handle, PF5020_FAULT_TIMERS, 0x0FU, (expireValue & 0x0FU));
}

/*!
 * brief Set reset behaviour asserted by WDI.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param wdiMode Used to control the WDI asserted performs a hard WD reset or soft WD reset.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_WDOG_SetWDIMode(pf5020_handle_t *handle, pf5020_wdi_mode_t wdiMode)
{
    assert(handle);

    return PF5020_ModifyReg(handle, PF5020_CTRL1, 0x20U, (((uint8_t)wdiMode << 5U) & 0x20U));
}

/*!
 * brief Enable/disable WDI watchdog event in standby state.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param enable Used to control whether generate a watchdog event in standby mode if the WDI is asserted.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_WDOG_EnableWDIStanby(pf5020_handle_t *handle, bool enable)
{
    assert(handle);

    return PF5020_ModifyReg(handle, PF5020_CTRL1, 0x2U, (((uint8_t)enable << 1U) & 0x2U));
}

/*!
 * brief Configure internal watchdog timer.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param config Pointer to pf5020_wdog_internal_timer_config_t structure.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_WDOG_ConfigInternalTimer(pf5020_handle_t *handle, const pf5020_wdog_internal_timer_config_t *config)
{
    assert(handle);
    assert(config);

    status_t status;

    status = PF5020_WriteReg(handle, PF5020_WD_CONFIG, config->timerDuration);

    if (status == kStatus_Success)
    {
        status = PF5020_ModifyReg(handle, PF5020_WD_EXPIRE, 0x70U, ((config->cyclicCounterMaxVale << 4U) & 0x70U));
    }

    if (status == kStatus_Success)
    {
        status = PF5020_ModifyReg(handle, PF5020_CTRL1, PF5020_CTRL1_WD_EN_MASK | PF5020_CTRL1_WD_STBY_EN_MASK,
                                  PF5020_CTRL1_WD_STBY_EN(config->enableStandby) | PF5020_CTRL1_WD_EN(config->enable));
    }

    return status;
}

/*!
 * brief Get cyclic counter current value.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * return Current cyclic counter value.
 */
uint8_t PF5020_WDOG_GetCyclicCounterValue(pf5020_handle_t *handle)
{
    assert(handle);

    uint8_t tmp8;

    (void)PF5020_ReadReg(handle, PF5020_WD_EXPIRE, &tmp8);
    tmp8 &= 0x7U;

    return tmp8;
}

/*!
 * brief Refresh internal watchdog timer.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_WDOG_RefreshInternalTimer(pf5020_handle_t *handle)
{
    assert(handle);

    return PF5020_WriteReg(handle, PF5020_WD_CLEAR, 0x1U);
}

/*!
 * brief Set watchdog event counter maximum value.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param maxValue The maximum value of watchdog event counter.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_WDOG_SetWDEventCounterMaxValue(pf5020_handle_t *handle, uint8_t maxValue)
{
    assert(handle);

    return PF5020_ModifyReg(handle, PF5020_WD_COUNTER, 0xF0U, ((maxValue << 4U) & 0xF0U));
}

/*!
 * brief Get watchdog event counter current value.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * return Watch dog event counter current value.
 */
uint8_t PF5020_WDOG_GetWDEventCounterCurrentValue(pf5020_handle_t *handle)
{
    assert(handle);

    uint8_t tmp8;

    (void)PF5020_ReadReg(handle, PF5020_WD_COUNTER, &tmp8);
    tmp8 &= 0xFU;

    return tmp8;
}

/*!
 * brief Configure internal thermal monitor.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param enable Enable/disable temperature sensor circuit.
 * param mode Used to set temperature sensor operate mode, please refer to pf5020_temp_sensor_operate_mode_t.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_TMP_SetThermalMonitorConfig(pf5020_handle_t *handle,
                                            bool enable,
                                            pf5020_temp_sensor_operate_mode_t mode)
{
    assert(handle);

    status_t status;

    status = PF5020_ModifyReg(handle, PF5020_CTRL1, PF5020_CTRL1_TMP_MON_EN_MASK, PF5020_CTRL1_TMP_MON_EN(enable));

    if (status == kStatus_Success)
    {
        status = PF5020_ModifyReg(handle, PF5020_CTRL2, PF5020_CTRL2_TMP_MON_AON_MASK, PF5020_CTRL2_TMP_MON_AON(mode));
    }

    return status;
}

/*!
 * brief Configure analog multiplexer.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param enable Enable/disable analog multiplexer.
 * param amuxSel Used to select amux output, please refer to pf5020_amux_selection_t
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_AMUX_SetAnalogMuxConfig(pf5020_handle_t *handle, bool enable, pf5020_amux_selection_t amuxSel)
{
    assert(handle);

    return PF5020_ModifyReg(handle, PF5020_AMUX, PF5020_AMUX_AMUX_SEL_MASK | PF5020_AMUX_AMUX_EN_MASK,
                            PF5020_AMUX_MAUX_SEL(amuxSel) | PF5020_AMUX_AMUX_EN(enable));
}

/*!
 * brief Enable interrupts.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param interruptMask The mask of interrupts to clear, should be the OR'ed value of pf5020_interrupt_t.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_EnableInterrupts(pf5020_handle_t *handle, uint64_t interruptMask)
{
    assert(handle);

    return PF5020_MaskInterrupts(handle, interruptMask, true);
}

/*!
 * brief Disable Interrupts.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param interruptMask The mask of interrupts to clear, should be the OR'ed value of pf5020_interrupt_t.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_DisableInterrupts(pf5020_handle_t *handle, uint64_t interruptMask)
{
    assert(handle);

    return PF5020_MaskInterrupts(handle, interruptMask, false);
}

/*!
 * brief Get latched interrupts.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param interrptLatched Pointer to store the latched interrupt value.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_GetInterruptLatchStatus(pf5020_handle_t *handle, uint64_t *interrptLatched)
{
    assert(handle);

    static const uint8_t latchRegArray[] = PF5020_INT_LATCH_ARRAY;
    uint8_t sysIntStatus;
    status_t status;
    uint8_t i;
    uint8_t tmp8;

    /* Get first level interrupt latch value, if the bit in SYS_INT register is set, it means related second level
     * interrupts are latched in second level interrupt register.
     */
    status = PF5020_ReadReg(handle, PF5020_SYS_INT, &sysIntStatus);

    if (status == kStatus_Success)
    {
        for (i = 0U; i < 7U; i++)
        {
            /* If first level interrupt is set, then read related second level interrupt latch register. */
            if ((sysIntStatus & (1U << i)) != 0U)
            {
                status = PF5020_ReadReg(handle, latchRegArray[i], &tmp8);
                *interrptLatched |= ((uint64_t)tmp8 << (i * 8U));

                if ((i == 3U) && (status == kStatus_Success))
                {
                    status = PF5020_ReadReg(handle, PF5020_LDO_ILIM_INT, &tmp8);
                    if ((status == kStatus_Success) && (tmp8 != 0U))
                    {
                        *interrptLatched |= (uint64_t)kPF5020_ILIM_Ldo1IlimInterrupt;
                    }
                }

                if ((i == 4U) && (status == kStatus_Success))
                {
                    status = PF5020_ReadReg(handle, PF5020_LDO_UV_INT, &tmp8);
                    if ((tmp8 != 0U) && (status == kStatus_Success))
                    {
                        *interrptLatched |= (uint64_t)kPF5020_UV_Ldo1UvInterrupt;
                    }
                }

                if ((i == 5U) && (status == kStatus_Success))
                {
                    status = PF5020_ReadReg(handle, PF5020_LDO_OV_INT, &tmp8);
                    if ((tmp8 != 0U) && (status == kStatus_Success))
                    {
                        *interrptLatched |= (uint64_t)kPF5020_OV_Ldo1OvInterrupt;
                    }
                }
            }
        }
    }

    return status;
}

/*!
 * brief Clear latched interrupts.
 *
 * param handle The pointer to pf5020_handle_t structure.
 * param interruptMask The mask of interrupts to clear, should be the OR'ed value of pf5020_interrupt_t.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t PF5020_ClearInterruptStatus(pf5020_handle_t *handle, uint64_t interruptMask)
{
    assert(handle);

    static const uint8_t latchRegArray[] = PF5020_INT_LATCH_ARRAY;
    status_t status;
    uint8_t sysIntStatus;
    uint8_t i;
    uint8_t tmp8;
    uint64_t tmp64;

    /* Read SYS_INT register, it provides information about the interrupt register that originated the interrupt event.
     */
    status = PF5020_ReadReg(handle, PF5020_SYS_INT, &sysIntStatus);

    for (i = 0U; i < 7U; i++)
    {
        if ((sysIntStatus & (1U << i)) != 0U)
        {
            tmp64 = interruptMask & (0xFFULL << (8ULL * i));
            if ((tmp64 & (uint64_t)kPF5020_ILIM_Ldo1IlimInterrupt) != 0ULL)
            {
                status = PF5020_WriteReg(handle, PF5020_LDO_ILIM_INT, 1U);
                tmp64 &= (uint64_t)(~(uint64_t)kPF5020_ILIM_Ldo1IlimInterrupt);
            }

            if ((tmp64 & (uint64_t)kPF5020_UV_Ldo1UvInterrupt) != 0ULL)
            {
                status = PF5020_WriteReg(handle, PF5020_LDO_UV_INT, 1U);
                tmp64 &= (uint64_t)(~(uint64_t)kPF5020_UV_Ldo1UvInterrupt);
            }

            if ((tmp64 & (uint64_t)kPF5020_OV_Ldo1OvInterrupt) != 0ULL)
            {
                status = PF5020_WriteReg(handle, PF5020_LDO_OV_INT, 1U);
                tmp64 &= (uint64_t)(~(uint64_t)kPF5020_OV_Ldo1OvInterrupt);
            }

            tmp8 = (uint8_t)(tmp64 >> (8ULL * i)) & (0xFFU);

            if (status == kStatus_Success)
            {
                status = PF5020_WriteReg(handle, latchRegArray[i], tmp8);
            }
        }
    }

    return status;
}
