/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_sdioslv_sdu.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.sdu"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static inline status_t SDIOSLV_GetScratchRegisterAddr(sdioslv_func_t fun_num,
                                                      sdioslv_scratch_group_t group,
                                                      sdioslv_scratch_offset_t offset,
                                                      uint32_t *reg_addr);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Public Functions
 ******************************************************************************/

/*!
 * @brief Signals the following 4 events to the host
 *
 * * SDU_FN_CARD_C2H_INTEVENT0_CIS_CARD_RDY_MASK (Firmware sets this bit after CIS table is initialized)
 * * SDU_FN_CARD_C2H_INTEVENT0_IO_READY_MASK (Firmware)
 * * SDU_FN_CARD_C2H_INTEVENT0_Q0_DNLD_CARD_RDY_MASK (Firmware sets this bit when ready to receive data.)
 * * SDU_FN_CARD_C2H_INTEVENT0_Q0_UPLD_CARD_RDY_MASK (Firmware sets this bit when ready to transmit data.)
 * * SDU_FN_CARD_C2H_INTEVENT0_CMD_PORT_DNLD_RDY_MASK
 * * SDU_FN_CARD_C2H_INTEVENT0_CMD_PORT_UPLD_RDY_MASK
 *
 * @param base SDIO base pointer
 * @return mask of events to signal to host
 */
static inline void SDIOSLV_SetIntEvent(SDU_FN_CARD_Type *base, uint8_t mask)
{
     uint8_t temp = (uint8_t)(base->C2H_INTEVENT0 & ~(SDU_FN_CARD_C2H_INTEVENT0_IO_READY_MASK
                                           | SDU_FN_CARD_C2H_INTEVENT0_CIS_CARD_RDY_MASK
                                           | SDU_FN_CARD_C2H_INTEVENT0_Q0_UPLD_CARD_RDY_MASK
                                           | SDU_FN_CARD_C2H_INTEVENT0_Q0_DNLD_CARD_RDY_MASK
                                           | SDU_FN_CARD_C2H_INTEVENT0_CMD_PORT_DNLD_RDY_MASK
                                           | SDU_FN_CARD_C2H_INTEVENT0_CMD_PORT_UPLD_RDY_MASK));

    // INTEVENT0 is the poll register of the driver
    base->C2H_INTEVENT0 = temp | mask;
}

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief SDIOSLV Init0.
 *
 * Call this API to Init SDIOSLV phase0.
 *
 * @param void None.
 * @retval void None.
 */
void SDIOSLV_Init0(void)
{
    CLKCTL0->PSCCTL0_SET  = CLKCTL0_PSCCTL0_SET_SDIO(1);
    RSTCTL0->PRSTCTL0_CLR = RSTCTL0_PRSTCTL0_CLR_SDIO(1);
    CLKCTL0->PSCCTL1_SET  = CLKCTL0_PSCCTL1_SET_SDIO_SLV(1);
    RSTCTL0->PRSTCTL1_CLR = RSTCTL0_PRSTCTL1_CLR_SDIO_SLV(1);

    set_iomux(20, 15);

    // via Abhijit
    rmw2(&MCI_IO_MUX->FSEL, MCI_IO_MUX_FSEL_SEL_SDIO_MASK, MCI_IO_MUX_FSEL_SEL_SDIO_SHIFT, 1U);

    // 0 means we don't use standard defns (i.e. wireless). If you use standard defs
    // then you need to comply totally with the standard (Microsoft et al). Left at
    // 0, our driver performs the function.
    rmwb(sdu_fbr_fnN_fn_code(1U), sdu_fbr_fnN_fn_code_code_HI, sdu_fbr_fnN_fn_code_code_LO, 0U);

    rmwb(sdu_fbr_fnN_fn_code(2U), sdu_fbr_fnN_fn_code_code_HI, sdu_fbr_fnN_fn_code_code_LO, 0U);

    rmwb(sdu_fbr_fnN_fn_code(3U), sdu_fbr_fnN_fn_code_code_HI, sdu_fbr_fnN_fn_code_code_LO, 0U);
}

/*!
 * @brief SDIOSLV Init1.
 *
 * Call this API to Init SDIOSLV phase1.
 *
 * @param base FN FSR pointer.
 * @param config Configure for SDIO Slave.
 * @retval #kStatus_Success command is ready to be sent to host driver.
 * @retval #kStatus_InvalidArgument Invalid argument.
 */
status_t SDIOSLV_Init1(SDU_FN_CARD_Type *base, sdio_slave_config_t *config)
{
    uint8_t reg;

    if ((config->cmd_tx_format > 2U) || (config->cmd_rd_format > 1U))
    {
        return (status_t)kStatus_Fail;
    }

    if ((config->data_tx_format > 2U) || (config->data_rd_format > 2U))
    {
        return (status_t)kStatus_Fail;
    }

    if (config->cis_table_callback == NULL)
    {
        return (status_t)kStatus_Fail;
    }

    // Enable CMD5 R4 FN bypass and configure with only 1 FN
    // Otherwise FN number would only be set when bootstrap is SDIO_BOOT_MODE
    reg = SDU_FN0_CARD->CARD_CTRL5;
    reg &= ~(uint8_t)(SDU_FN0_CARD_CARD_CTRL5_CMD5_R4_FN_BYPASS_EN_MASK | SDU_FN0_CARD_CARD_CTRL5_CMD5_R4_FN_BYPASS_VAL_MASK);
    reg |= SDU_FN0_CARD_CARD_CTRL5_CMD5_R4_FN_BYPASS_VAL(1U);
    reg |= (uint8_t)(1U << SDU_FN0_CARD_CARD_CTRL5_CMD5_R4_FN_BYPASS_EN_SHIFT);
    SDU_FN0_CARD->CARD_CTRL5 = reg;

    REG32(&base->PKT_RD_BITMAP0) = 0U;
    REG32(&base->PKT_WR_BITMAP0) = 0U;
    base->FN_CARD_INTMASK = (uint8_t)config->cpu_num;

    // Enable Interrupts
    base->CARD_INTMASK0 = SDU_FN_CARD_CARD_INTSTATUS0_Q0_DNLD_CARD_INT_MASK
                        | SDU_FN_CARD_CARD_INTSTATUS0_Q0_UPLD_CARD_INT_MASK
                        | SDU_FN_CARD_CARD_INTSTATUS0_ABORT_CARD_INT_MASK
                        | SDU_FN_CARD_CARD_INTSTATUS0_HOST_PWR_UP_INT_MASK;
    base->CARD_INTMASK1 = SDU_FN_CARD_CARD_INTSTATUS1_CMD_PORT_UPLD_CARD_INT_MASK
                        | SDU_FN_CARD_CARD_INTSTATUS1_CMD_PORT_DNLD_CARD_INT_MASK;

    // Cargo cult: Toggle INTSTATUS0_Q0_DNLD_CARD_INT_MASK, taken from SDK driver
    REG8(&base->CARD_INTSTATUS0) = SDU_FN_CARD_CARD_INTSTATUS0_Q0_DNLD_CARD_INT_MASK;
    REG8(&base->CARD_INTSTATUS0) = 0U;

    // Default setting ISR bit clear after read
    base->CARD_INTRSR0 = SDU_FN_CARD_CARD_INTSTATUS0_Q0_DNLD_CARD_INT_MASK
                       | SDU_FN_CARD_CARD_INTSTATUS0_Q0_UPLD_CARD_INT_MASK;
    base->CARD_INTRSR1 = SDU_FN_CARD_CARD_INTSTATUS1_CMD_PORT_DNLD_CARD_INT_MASK
                       | SDU_FN_CARD_CARD_INTSTATUS1_CMD_PORT_UPLD_CARD_INT_MASK;

    // Settings for 6.2.3 Command Port Mode
    base->CMD_PORT_CONFIG_0 = (config->cmd_tx_format << SDU_FN_CARD_CMD_PORT_CONFIG_0_CMD_PORT_TX_LEN_FORMAT_SHIFT)
                            | (config->cmd_rd_format << SDU_FN_CARD_CMD_PORT_CONFIG_0_CMD_PORT_RD_LEN_EN_SHIFT);

    base->CARD_CONFIG2_0 = SDU_FN_CARD_CARD_CONFIG2_0_FORCE_ASYNC_4BIT_INT_EN_MASK;

    // Settings for 6.2.2 Normal Mode
    base->CARD_CONFIG2_1 = SDU_FN_CARD_CARD_CONFIG2_1_CMD53_NEW_MODE_MASK
                         | (config->data_tx_format << SDU_FN_CARD_CARD_CONFIG2_1_CMD53_TX_LEN_FORMAT_SHIFT)
                         | (config->data_rd_format << SDU_FN_CARD_CARD_CONFIG2_1_CMD53_RD_LEN_FORMAT_SHIFT);

    // Callback code to populate CIS table
    config->cis_table_callback(SDU_FN0_CARD_BASE);

    // 0 means we don't use standard defns (i.e. wireless). If you use standard defs
    // then you need to comply totally with the standard (Microsoft et al). Left at
    // 0, our driver performs the function.
    SDU_FBR_CARD->FN_CODE &= ~(uint8_t)(SDU_FBR_CARD_FN_CODE_CODE_MASK);
    SDU_FBR_CARD->FN_CODE |= SDU_FBR_CARD_FN_CODE_CODE(0x0U);

    // Indicate to host IO_READY and that the CIS table is initialized

    SDIOSLV_SetIntEvent(base, SDU_FN_CARD_C2H_INTEVENT0_IO_READY_MASK
                            | SDU_FN_CARD_C2H_INTEVENT0_CIS_CARD_RDY_MASK);

    // If this is set to 1, IO_READY and CARD_READY status will be 0.
    SDU_FN0_CARD->DEV_SLEEP = SDU_FN0_CARD_DEV_SLEEP_DEV_SLEEP(0U);

    return (status_t)kStatus_Success;
}

/*!
 * @brief SDIOSLV send command.
 *
 * Call this API to send command to host driver.
 * The callback is always invoked from theinterrupt context.
 *
 * @param regmap FN FSR pointer.
 * @param data_addr Data Address.
 * @param data_len Data Length.
 * @retval #kStatus_Success command is ready to be sent to host driver.
 * @retval #kStatus_InvalidArgument Invalid argument.
 */
status_t SDIOSLV_SendCmdNonBlocking(sdioslv_sdu_regmap_t *regmap, uint8_t *data_addr, uint16_t data_len)
{
    sdioslv_sdu_regmap_t *sdu_fsr = NULL;

    if ((regmap == NULL) || (data_addr == NULL) || (data_len == 0U))
    {
        return (status_t)kStatus_InvalidArgument;
    }

    sdu_fsr                    = regmap;
    sdu_fsr->CmdPortSqReadBase = (uint32_t)data_addr;
    sdu_fsr->CmdPortRdLen      = data_len;
    sdu_fsr->CardToHostEvent   = (uint16_t)SDIO_CCR_CS_CmdUpLdRdy;
    return (status_t)kStatus_Success;
}

/*!
 * @brief SDIOSLV provide command buffer.
 *
 * Call this API to provide receive command buffer to SDU driver.
 *
 * @param regmap FN FSR pointer.
 * @param data_addr Data Address.
 * @param data_len Data Length.
 * @retval #kStatus_Success buffer refill sucessfully.
 * @retval #kStatus_Fail fail to refill buffer.
 */
status_t SDIOSLV_RefillCmdBuffer(sdioslv_sdu_regmap_t *regmap, uint8_t *data_addr)
{
    sdioslv_sdu_regmap_t *sdu_fsr = NULL;

    if ((regmap == NULL) || (data_addr == NULL))
    {
        return kStatus_Fail;
    }

    sdu_fsr                     = regmap;
    sdu_fsr->CmdPortSqWriteBase = (uint32_t)data_addr;
    sdu_fsr->CardToHostEvent    = (uint16_t)SDIO_CCR_CS_CmdDnLdRdy;
    return kStatus_Success;
}

/*!
 * @brief SDIOSLV send data transfer.
 *
 * Call this API to send data to host driver.
 * The callback is always invoked from theinterrupt context.
 *
 * @param regmap FN FSR pointer.
 * @param port Data Port.
 * @param data_addr Data Address.
 * @param data_len Data Length.
 * @retval #kStatus_Success buffer is added to data slot with problem.
 * @retval #kStatus_InvalidArgument Invalid argument.
 * @retval #kStatus_SDIOSLV_SendFull all data slots are occupied, application
 */
status_t SDIOSLV_SendDataNonBlocking(sdioslv_sdu_regmap_t *regmap, sdioslv_port_t tx_port, uint8_t *data_addr, uint16_t data_len)
{
    sdioslv_sdu_regmap_t *sdu_fsr = NULL;

    if ((regmap == NULL) || (data_addr == NULL) || (data_len == 0U))
    {
        return (status_t)kStatus_InvalidArgument;
    }

    if ((uint8_t)tx_port >= (uint8_t)SDU_USED_PORT_NUM)
    {
        return (status_t)kStatus_SDIOSLV_SendFull;
    }

    sdu_fsr                  = regmap;
    sdu_fsr->RdIdx           = (uint8_t)tx_port;
    sdu_fsr->SqReadBase      = (uint32_t)data_addr;
    sdu_fsr->RdLen[tx_port]  = data_len;
    sdu_fsr->RdBitMap        = ((uint32_t)1U << (uint32_t)tx_port);
    sdu_fsr->CardToHostEvent = (uint16_t)SDIO_CCR_CS_UpLdRdy;
    return (status_t)kStatus_Success;
}

/*!
 * @brief SDIOSLV provide receive data buffer.
 *
 * Call this API to provide receive data buffer to SDU driver.
 *
 * @param regmap FN FSR pointer.
 * @param port Data Port.
 * @param data_addr Data Address.
 * @param data_len Data Length.
 * @retval #kStatus_Success refill buffer sucessfully.
 * @retval #kStatus_Fail fail to refill buffer.
 */
status_t SDIOSLV_RefillDataBuffer(sdioslv_sdu_regmap_t *regmap, sdioslv_port_t port, uint8_t *data_addr)
{
    sdioslv_sdu_regmap_t *sdu_fsr = NULL;

    if ((regmap == NULL) || (data_addr == NULL))
    {
        return kStatus_Fail;
    }

    if ((uint32_t)port >= (uint32_t)SDU_USED_PORT_NUM)
    {
        return kStatus_Fail;
    }

    sdu_fsr                  = regmap;
    sdu_fsr->WrIdx           = (uint8_t)port;
    sdu_fsr->SqWriteBase     = (uint32_t)data_addr;
    sdu_fsr->WrBitMap        = (uint32_t)((uint32_t)1U << (uint32_t)port);
    sdu_fsr->CardToHostEvent = (uint16_t)SDIO_CCR_CS_DnLdRdy;
    return kStatus_Success;
}

/*!
 * @brief Get SDIO bus speed selection.
 *
 * Call this API to get current bus speed selected for SDIO.
 *
 * @param void None.
 * @retval sdioslv_bus_speed_t Bus speed selected for SDIO.
 */
sdioslv_bus_speed_t SDIOSLV_GetBusSpeed(void)
{
    uint8_t reg_val = 0;

    reg_val = SDU_REGS8(SDIO_FUNC0_BSS);
    reg_val = (reg_val & (uint8_t)SDIO_FUNC0_BSS_MODE_MASK) >> SDIO_FUNC0_BSS_MODE_BIT;

    return (sdioslv_bus_speed_t)reg_val;
}

/*!
 * @brief Get SDIO the block size in FBR.
 *
 * For block mode, block size equals to block size in FBR.
 *
 * @param handle Created by SDIOSLV_CreateHanle().
 * @retval the block size in FBR.
 */
uint32_t SDIOSLV_GetBlockSize(uint8_t fn_num)
{
    uint32_t fun_num;
    uint32_t block_size = 0U;

    fun_num  = (uint32_t)(fn_num + 1U);
    block_size = SDU_REGS8(SDU_SDIO_CFG_BASE + 0x8U + (fun_num << 4U));
    block_size |= SDU_REGS8(SDU_SDIO_CFG_BASE + 0x9U + (((fun_num << 4U) & 0x01U) << 8U));

    if (block_size == 0U)
    {
        block_size = 512U;
    }

    return block_size;
}

/*!
 * @brief SDIOSLV read scratch register of SDU.
 *
 * Call this API to read scratch register of SDU (based on group and offset).
 *
 * @param fun_num Specify which function.
 * @param group Specify which scratch group.
 * @param offset Specify offset of the scratch group.
 * @param value Value read from the register.
 * @retval #kStatus_Success read sucessfully.
 * @retval #kStatus_Fail fail to read.
 */
status_t SDIOSLV_ReadScratchRegister(sdioslv_func_t fun_num,
                                     sdioslv_scratch_group_t group,
                                     sdioslv_scratch_offset_t offset,
                                     uint8_t *value)
{
    status_t ret;
    uint32_t reg_addr;

    ret = SDIOSLV_GetScratchRegisterAddr(fun_num, group, offset, &reg_addr);

    if (ret == kStatus_Success)
    {
        SDU_READ_REGS8(reg_addr, *value);
    }

    return ret;
}

/*!
 * @brief SDIOSLV write value to scratch register of SDU.
 *
 * Call this API to write value to scratch register of SDU (based on group and offset).
 *
 * @param fun_num Specify which function.
 * @param group Specify which scratch group.
 * @param offset Specify offset of the scratch group.
 * @param value Value write to the register.
 * @retval #kStatus_Success write sucessfully.
 * @retval #kStatus_Fail fail to write.
 */
status_t SDIOSLV_WriteScratchRegister(sdioslv_func_t fun_num,
                                      sdioslv_scratch_group_t group,
                                      sdioslv_scratch_offset_t offset,
                                      uint8_t value)
{
    status_t ret;
    uint32_t reg_addr;

    ret = SDIOSLV_GetScratchRegisterAddr(fun_num, group, offset, &reg_addr);

    if (ret == kStatus_Success)
    {
        SDU_WRITE_REGS8(reg_addr, value);
    }

    return ret;
}

/*******************************************************************************
 * Private Functions
 ******************************************************************************/

/*!
 * @brief SDIOSLV get scratch register address.
 *
 * @param fun_num Specify which function.
 * @param group Specify which scratch group.
 * @param offset Specify offset of the scratch group.
 * @param reg_addr Returned scratch register address.
 * @retval #kStatus_Success get scratch register address sucessfully.
 * @retval #kStatus_Fail fail to get scratch register address.
 */
static inline status_t SDIOSLV_GetScratchRegisterAddr(sdioslv_func_t fun_num,
                                                      sdioslv_scratch_group_t group,
                                                      sdioslv_scratch_offset_t offset,
                                                      uint32_t *reg_addr)
{
    status_t status = kStatus_Success;
    switch (group)
    {
        case kSDIOSLV_ScratchGroup0:
            if (offset == kSDIOSLV_ScratchOffset0)
            {
                *reg_addr = 0xD4U;
            }
            else if (offset == kSDIOSLV_ScratchOffset1)
            {
                *reg_addr = 0xD5U;
            }
            else
            {
                status = kStatus_Fail;
            }
            break;
        case kSDIOSLV_ScratchGroup1:
            if (offset == kSDIOSLV_ScratchOffset0)
            {
                *reg_addr = 0xB0U;
            }
            else if (offset == kSDIOSLV_ScratchOffset1)
            {
                *reg_addr = 0xB1U;
            }
            else
            {
                status = kStatus_Fail;
            }
            break;
        case kSDIOSLV_ScratchGroup2:
        case kSDIOSLV_ScratchGroup3:
        case kSDIOSLV_ScratchGroup4:
        case kSDIOSLV_ScratchGroup5:
        case kSDIOSLV_ScratchGroup6:
        case kSDIOSLV_ScratchGroup7:
            *reg_addr = (uint32_t)SDU_SCRATCH2_OFFSET0_ADDR + (uint32_t)(((uint32_t)group - 2U) * 4U) + (uint32_t)offset;
            break;
        default:
            status = kStatus_Fail;
            break;
    }

    if(status != kStatus_Success)
    {
        return status;
    }

    switch (fun_num)
    {
        case kSDIOSLV_FunctionNum1:
        case kSDIOSLV_FunctionNum2:
        case kSDIOSLV_FunctionNum3:
        case kSDIOSLV_FunctionNum4:
        case kSDIOSLV_FunctionNum5:
        case kSDIOSLV_FunctionNum6:
        case kSDIOSLV_FunctionNum7:
            *reg_addr |= ((uint32_t)fun_num << 8U);
            break;
        default:
            status = kStatus_Fail;
            break;
    }

    if(status != kStatus_Success)
    {
        return status;
    }

    *reg_addr += SDU_SDIO_CFG_BASE;

    return status;
}
