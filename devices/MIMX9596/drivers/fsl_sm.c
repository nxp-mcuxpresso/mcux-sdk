/*
 * Copyright 2023-2025 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "board.h"
#include "smt.h"
#include "fsl_sm.h"
#include "fsl_iomuxc.h"
#include "fsl_mu.h"
#include "fsl_lpuart.h"
#include "scmi_common.h"
#include "scmi_lmm.h"
#include "scmi_pinctrl.h"
#include "scmi_clock.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static MU_Type *const s_muBases[] = MU_BASE_PTRS;
static IRQn_Type const s_muIrqs[] = MU_IRQS;


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Initialize channel and MU interface for communication with SM.
 */
void SM_Init(void)
{
    MU_Type *base = s_muBases[SCMI_MU_SEL];
    IRQn_Type irq = s_muIrqs[SCMI_MU_SEL];

    /* Configure SMT */
    SMT_ChannelConfig(SCMI_A2P, SCMI_MU_SEL, SCMI_DBIR_A2P, SCMI_SMA_ADDR);
    SMT_ChannelConfig(SCMI_NOTIFY, SCMI_MU_SEL, SCMI_DBIR_NOTIFY, SCMI_SMA_ADDR);
    SMT_ChannelConfig(SCMI_P2A, SCMI_MU_SEL, SCMI_DBIR_P2A, SCMI_SMA_ADDR);

    /* Configure MU */
    MU_Init(base);
    NVIC_EnableIRQ(irq);

    MU_NOTIFY_GENINT_EN(base);
    MU_P2A_GENINT_EN(base);

    /* Enable notifications */
    SCMI_LmmNotify(SCMI_A2P, SCMI_LMID_A55, SCMI_LMM_NOTIFY_BOOT(1) | SCMI_LMM_NOTIFY_SHUTDOWN(1));
}

/*!
 * @brief Deinitialize MU interface.
 */
void SM_Deinit(void)
{
}

/*!
 * @brief  MU interrupt handler.
 */
void SM_Handler(void)
{
    MU_Type *base = s_muBases[SCMI_MU_SEL];
    uint32_t flags;

    /* Get interrupt status flags */
    flags = MU_GetStatusFlags(base);

    /* Clear interrupts */
    MU_ClearStatusFlags(base, flags);

    /* Notification pending? */
    if (flags & MU_NOTIFY_GENINT_FLAG)
    {
        uint32_t protocolId, messageId;

        /* Get pending info */
        if (SCMI_P2aPending(SCMI_NOTIFY, &protocolId, &messageId) == SCMI_ERR_SUCCESS)
        {
        }
    }

    /* P2A reverse call pending? */
    if (flags & MU_P2A_GENINT_FLAG)
    {
    }
}

/*!
 * @brief Sets the IOMUXC pin mux mode.
 * @note The first five parameters can be filled with the pin function ID macros.
 *
 * @param muxRegister    The pin mux register
 * @param muxMode        The pin mux mode
 * @param inputRegister  The select input register
 * @param inputDaisy     The input daisy
 * @param configRegister The config register
 * @param inputOn        The software input on
 */
void IOMUXC_SetPinMux_SM(uint32_t muxRegister,
                                    uint32_t muxMode,
                                    uint32_t inputRegister,
                                    uint32_t inputDaisy,
                                    uint32_t configRegister,
                                    uint32_t inputOnfield)
{
    scmi_pin_config_t configs[3];
    uint32_t numConfigs = 0;

    if (muxRegister)
    {
       configs[numConfigs].type = SCMI_PINCTRL_TYPE_MUX;
       configs[numConfigs].value = IOMUXC_PAD_MUX_MODE(muxMode)
           | IOMUXC_PAD_SION(inputOnfield);
       numConfigs++;
    }

    if (inputRegister & 0xFFFF)
    {
       configs[numConfigs].type = SCMI_PINCTRL_TYPE_DAISY_ID;
       configs[numConfigs].value = (inputRegister - SCMI_IOMUXC_DAISYREG_OFF) / 4;
       numConfigs++;
       configs[numConfigs].type = SCMI_PINCTRL_TYPE_DAISY_CFG;
       configs[numConfigs].value = inputDaisy;
       numConfigs++;
    }

    if (muxRegister || inputRegister)
    {
       uint32_t attributes = SCMI_PINCTRL_SET_ATTR_SELECTOR(SCMI_PINCTRL_SEL_PIN)
          | SCMI_PINCTRL_SET_ATTR_NUM_CONFIGS(numConfigs);

       SCMI_PinctrlConfigSet(SCMI_A2P, (muxRegister - SCMI_IOMUXC_BASE) / 4,
          attributes, configs);
    }
}

/*!
 * @brief Sets the IOMUXC pin configuration.
 * @note The previous five parameters can be filled with the pin function ID macros.
 *
 * @param muxRegister    The pin mux register
 * @param muxMode        The pin mux mode
 * @param inputRegister  The select input register
 * @param inputDaisy     The input daisy
 * @param configRegister The config register
 * @param configValue    The pin config value
 */
void IOMUXC_SetPinConfig_SM(uint32_t muxRegister,
                                       uint32_t muxMode,
                                       uint32_t inputRegister,
                                       uint32_t inputDaisy,
                                       uint32_t configRegister,
                                       uint32_t configValue)
{
    if (configRegister)
    {
        uint32_t attributes = SCMI_PINCTRL_SET_ATTR_SELECTOR(SCMI_PINCTRL_SEL_PIN) |
            SCMI_PINCTRL_SET_ATTR_NUM_CONFIGS(1);
        scmi_pin_config_t configs;

        configs.type = SCMI_PINCTRL_TYPE_CONFIG;
        configs.value = configValue;

        SCMI_PinctrlConfigSet(SCMI_A2P, (configRegister - SCMI_IOMUXC_CFGREG_OFF) / 4,
                attributes, &configs);
    }
}

/*!
 * @brief Configure Root Clock
 *
 * @param root Which root clock node to set, see \ref clock_root_t.
 * @param config root clock config, see \ref clock_root_config_t
 */
void CLOCK_SetRootClock_SM(clock_root_t root, const clock_root_config_t *config)
{
    uint32_t numClocks = CLOCK_NUM_SRC + root ; 
    uint32_t flags     = SCMI_CLOCK_RATE_FLAGS_ROUND(SCMI_CLOCK_ROUND_AUTO);
    scmi_clock_rate_t rate = {0, 0};
    uint32_t pclkid = 0; /* parent clock id */
    uint64_t srcRate, rootRate;
    int32_t status = -1;

    if (config->div == 0)
        return;
    
    status = SCMI_ClockParentGet(SCMI_A2P, numClocks, &pclkid);
    if (status != 0)
        return;

    status = SCMI_ClockRateGet(SCMI_A2P, pclkid, &rate);
    if (status != 0)
        return;


    srcRate = rate.upper; 
    srcRate = (srcRate << 32);
    srcRate |= rate.lower;

    rootRate = srcRate / config->div;

    rate.lower = rootRate & 0xffffffff;
    rate.upper = (rootRate >> 32) & 0xffffffff;

    status = SCMI_ClockRateSet(SCMI_A2P, numClocks, flags, rate);
    if (status != 0)
        return;
    status = SCMI_ClockConfigSet(SCMI_A2P, numClocks, SCMI_CLOCK_CONFIG_SET_ENABLE(1U), 0U);
    if (status != 0)
        return;

    return ;
}

uint32_t CLOCK_GetIpFreq_SM(clock_root_t name)
{
    uint32_t numClocks = CLOCK_NUM_SRC + name ; 
    uint32_t pclkid = 0; /* parent clock id */
    scmi_clock_rate_t rate = {0, 0};
    int32_t status = 0;

    status = SCMI_ClockParentGet(SCMI_A2P, numClocks, &pclkid);
    if (status != 0)
        return 0;
    
    status = SCMI_ClockRateGet(SCMI_A2P, pclkid, &rate);
    if (status != 0)
        return 0;

    return rate.lower;
}
