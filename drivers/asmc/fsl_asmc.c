/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_asmc.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.asmc"
#endif

/*!
 * brief Configure the system to RUN power mode.
 *
 * param base ASMC peripheral base address.
 * return ASMC configuration error code.
 */
status_t ASMC_SetPowerModeRun(ASMC_Type *base)
{
    uint32_t reg;

    reg = base->PMCTRL;
    /* configure Normal RUN mode */
    reg &= ~ASMC_PMCTRL_RUNM_MASK;
    reg |= ((uint32_t)kASMC_RunNormal << ASMC_PMCTRL_RUNM_SHIFT);
    base->PMCTRL = reg;

    return kStatus_Success;
}

#if (defined(FSL_FEATURE_ASMC_HAS_HIGH_SPEED_RUN_MODE) && FSL_FEATURE_ASMC_HAS_HIGH_SPEED_RUN_MODE)
/*!
 * brief Configure the system to HSRUN power mode.
 *
 * param base ASMC peripheral base address.
 * return ASMC configuration error code.
 */
status_t ASMC_SetPowerModeHsrun(ASMC_Type *base)
{
    uint32_t reg;

    reg = base->PMCTRL;
    /* configure High Speed RUN mode */
    reg &= ~ASMC_PMCTRL_RUNM_MASK;
    reg |= (kASMC_Hsrun << ASMC_PMCTRL_RUNM_SHIFT);
    base->PMCTRL = reg;

    return kStatus_Success;
}
#endif /* FSL_FEATURE_ASMC_HAS_HIGH_SPEED_RUN_MODE */

/*!
 * brief Configure the system to WAIT power mode.
 *
 * param base ASMC peripheral base address.
 * return ASMC configuration error code.
 */
status_t ASMC_SetPowerModeWait(ASMC_Type *base)
{
    /* configure Normal Wait mode */
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    __DSB();
    __WFI();
    __ISB();

    return kStatus_Success;
}

/*!
 * brief Configure the system to Stop power mode.
 *
 * param base ASMC peripheral base address.
 * param  option Partial Stop mode option.
 * return ASMC configuration error code.
 */
status_t ASMC_SetPowerModeStop(ASMC_Type *base, asmc_partial_stop_option_t option)
{
    uint32_t reg;

    /* configure the Partial Stop mode in Normal Stop mode */
    reg = base->STOPCTRL;
    reg &= ~ASMC_STOPCTRL_PSTOPO_MASK;
    reg |= ((uint32_t)option << ASMC_STOPCTRL_PSTOPO_SHIFT);
    base->STOPCTRL = reg;

    /* configure Normal Stop mode */
    reg = base->PMCTRL;
    reg &= ~ASMC_PMCTRL_STOPM_MASK;
    reg |= ((uint32_t)kASMC_StopNormal << ASMC_PMCTRL_STOPM_SHIFT);
    base->PMCTRL = reg;

    /* Set the SLEEPDEEP bit to enable deep sleep mode (stop mode) */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* read back to make sure the configuration valid before entering stop mode */
    (void)base->PMCTRL;
    __DSB();
    __WFI();
    __ISB();

    return kStatus_Success;
}

/*!
 * brief Configure the system to VLPR power mode.
 *
 * param base ASMC peripheral base address.
 * return ASMC configuration error code.
 */
status_t ASMC_SetPowerModeVlpr(ASMC_Type *base)
{
    uint32_t reg;

    reg = base->PMCTRL;

    /* configure VLPR mode */
    reg &= ~ASMC_PMCTRL_RUNM_MASK;
    reg |= ((uint32_t)kASMC_RunVlpr << ASMC_PMCTRL_RUNM_SHIFT);
    base->PMCTRL = reg;

    return kStatus_Success;
}

/*!
 * brief Configure the system to VLPW power mode.
 *
 * param base ASMC peripheral base address.
 * return ASMC configuration error code.
 */
status_t ASMC_SetPowerModeVlpw(ASMC_Type *base)
{
    /* configure VLPW mode */
    /* Clear the SLEEPDEEP bit to disable deep sleep mode */
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    __DSB();
    __WFI();
    __ISB();

    return kStatus_Success;
}

/*!
 * brief Configure the system to VLPS power mode.
 *
 * param base ASMC peripheral base address.
 * return ASMC configuration error code.
 */
status_t ASMC_SetPowerModeVlps(ASMC_Type *base)
{
    uint32_t reg;

    /* configure VLPS mode */
    reg = base->PMCTRL;
    reg &= ~ASMC_PMCTRL_STOPM_MASK;
    reg |= ((uint32_t)kASMC_StopVlps << ASMC_PMCTRL_STOPM_SHIFT);
    base->PMCTRL = reg;

    /* Set the SLEEPDEEP bit to enable deep sleep mode */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* read back to make sure the configuration valid before enter stop mode */
    (void)base->PMCTRL;
    __DSB();
    __WFI();
    __ISB();

    return kStatus_Success;
}

/*!
 * brief Configure the system to LLS power mode.
 *
 * param base ASMC peripheral base address.
 * return ASMC configuration error code.
 */
status_t ASMC_SetPowerModeLls(ASMC_Type *base)
{
    uint32_t reg;

    /* configure to LLS mode */
    reg = base->PMCTRL;
    reg &= ~ASMC_PMCTRL_STOPM_MASK;
    reg |= ((uint32_t)kASMC_StopLls << ASMC_PMCTRL_STOPM_SHIFT);
    base->PMCTRL = reg;

    /* Set the SLEEPDEEP bit to enable deep sleep mode */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* read back to make sure the configuration valid before entering stop mode */
    (void)base->PMCTRL;
    __DSB();
    __WFI();
    __ISB();

    return kStatus_Success;
}

/*!
 * brief Configure the system to VLLS power mode.
 *
 * param base ASMC peripheral base address.
 * return ASMC configuration error code.
 */
status_t ASMC_SetPowerModeVlls(ASMC_Type *base)
{
    uint32_t reg;

    /* configure to VLLS mode */
    reg = base->PMCTRL;
    reg &= ~ASMC_PMCTRL_STOPM_MASK;
    reg |= ((uint32_t)kASMC_StopVlls << ASMC_PMCTRL_STOPM_SHIFT);
    base->PMCTRL = reg;

    /* Set the SLEEPDEEP bit to enable deep sleep mode */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* read back to make sure the configuration valid before enter stop mode */
    (void)base->PMCTRL;
    __DSB();
    __WFI();
    __ISB();

    return kStatus_Success;
}
