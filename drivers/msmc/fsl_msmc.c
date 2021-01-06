/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_msmc.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.msmc"
#endif

/*!
 * brief Configure the system to RUN power mode.
 *
 * param base SMC peripheral base address.
 * return SMC configuration error code.
 */
status_t SMC_SetPowerModeRun(SMC_Type *base)
{
    uint32_t reg;

    reg = base->PMCTRL;
    /* configure Normal RUN mode */
    reg &= ~SMC_PMCTRL_RUNM_MASK;
    reg |= ((uint32_t)kSMC_RunNormal << SMC_PMCTRL_RUNM_SHIFT);
    base->PMCTRL = reg;

    return kStatus_Success;
}

/*!
 * brief Configure the system to HSRUN power mode.
 *
 * param base SMC peripheral base address.
 * return SMC configuration error code.
 */
status_t SMC_SetPowerModeHsrun(SMC_Type *base)
{
    uint32_t reg;

    reg = base->PMCTRL;
    /* configure High Speed RUN mode */
    reg &= ~SMC_PMCTRL_RUNM_MASK;
    reg |= ((uint32_t)kSMC_Hsrun << SMC_PMCTRL_RUNM_SHIFT);
    base->PMCTRL = reg;

    return kStatus_Success;
}

/*!
 * brief Configure the system to WAIT power mode.
 *
 * param base SMC peripheral base address.
 * return SMC configuration error code.
 */
status_t SMC_SetPowerModeWait(SMC_Type *base)
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
 * param base SMC peripheral base address.
 * param  option Partial Stop mode option.
 * return SMC configuration error code.
 */
status_t SMC_SetPowerModeStop(SMC_Type *base, smc_partial_stop_option_t option)
{
    status_t status;
    uint32_t reg;

    /* configure the Partial Stop mode in Normal Stop mode */
    reg = base->PMCTRL;
    reg &= ~(SMC_PMCTRL_PSTOPO_MASK | SMC_PMCTRL_STOPM_MASK);
    reg |= ((uint32_t)option << SMC_PMCTRL_PSTOPO_SHIFT) | ((uint32_t)kSMC_StopNormal << SMC_PMCTRL_STOPM_SHIFT);
    base->PMCTRL = reg;

    /* Set the SLEEPDEEP bit to enable deep sleep mode (stop mode) */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* read back to make sure the configuration valid before entering stop mode */
    (void)base->PMCTRL;
    __DSB();
    __WFI();
    __ISB();

#if (defined(FSL_FEATURE_SMC_HAS_PMCTRL_STOPA) && FSL_FEATURE_SMC_HAS_PMCTRL_STOPA)
    /* check whether the power mode enter Stop mode succeed */
    if (0U != (base->PMCTRL & SMC_PMCTRL_STOPA_MASK))
    {
        status = kStatus_SMC_StopAbort;
    }
    else
    {
        status = kStatus_Success;
    }
#else
    status = kStatus_Success;
#endif /* FSL_FEATURE_SMC_HAS_PMCTRL_STOPA */

    return status;
}

/*!
 * brief Configure the system to VLPR power mode.
 *
 * param base SMC peripheral base address.
 * return SMC configuration error code.
 */
status_t SMC_SetPowerModeVlpr(SMC_Type *base)
{
    uint32_t reg;

    reg = base->PMCTRL;
    /* configure VLPR mode */
    reg &= ~SMC_PMCTRL_RUNM_MASK;
    reg |= ((uint32_t)kSMC_RunVlpr << SMC_PMCTRL_RUNM_SHIFT);
    base->PMCTRL = reg;

    return kStatus_Success;
}

/*!
 * brief Configure the system to VLPW power mode.
 *
 * param base SMC peripheral base address.
 * return SMC configuration error code.
 */
status_t SMC_SetPowerModeVlpw(SMC_Type *base)
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
 * param base SMC peripheral base address.
 * return SMC configuration error code.
 */
status_t SMC_SetPowerModeVlps(SMC_Type *base)
{
    uint32_t reg;
    status_t status;

    /* configure VLPS mode */
    reg = base->PMCTRL;
    reg &= ~SMC_PMCTRL_STOPM_MASK;
    reg |= ((uint32_t)kSMC_StopVlps << SMC_PMCTRL_STOPM_SHIFT);
    base->PMCTRL = reg;

    /* Set the SLEEPDEEP bit to enable deep sleep mode */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* read back to make sure the configuration valid before enter stop mode */
    (void)base->PMCTRL;
    __DSB();
    __WFI();
    __ISB();

#if (defined(FSL_FEATURE_SMC_HAS_PMCTRL_STOPA) && FSL_FEATURE_SMC_HAS_PMCTRL_STOPA)
    /* check whether the power mode enter Stop mode succeed */
    if (0U != (base->PMCTRL & SMC_PMCTRL_STOPA_MASK))
    {
        status = kStatus_SMC_StopAbort;
    }
    else
    {
        status = kStatus_Success;
    }
#else
    status = kStatus_Success;
#endif /* FSL_FEATURE_SMC_HAS_PMCTRL_STOPA */

    return status;
}

/*!
 * brief Configure the system to LLS power mode.
 *
 * param base SMC peripheral base address.
 * return SMC configuration error code.
 */
status_t SMC_SetPowerModeLls(SMC_Type *base)
{
    uint32_t reg;
    status_t status;

    /* configure to LLS mode */
    reg = base->PMCTRL;
    reg &= ~SMC_PMCTRL_STOPM_MASK;
    reg |= ((uint32_t)kSMC_StopLls << SMC_PMCTRL_STOPM_SHIFT);
    base->PMCTRL = reg;

    /* Set the SLEEPDEEP bit to enable deep sleep mode */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* read back to make sure the configuration valid before entering stop mode */
    (void)base->PMCTRL;
    __DSB();
    __WFI();
    __ISB();

#if (defined(FSL_FEATURE_SMC_HAS_PMCTRL_STOPA) && FSL_FEATURE_SMC_HAS_PMCTRL_STOPA)
    /* check whether the power mode enter Stop mode succeed */
    if (0U != (base->PMCTRL & SMC_PMCTRL_STOPA_MASK))
    {
        status = kStatus_SMC_StopAbort;
    }
    else
    {
        status = kStatus_Success;
    }
#else
    status = kStatus_Success;
#endif /* FSL_FEATURE_SMC_HAS_PMCTRL_STOPA */

    return status;
}

#if (defined(FSL_FEATURE_SMC_HAS_SUB_STOP_MODE) && FSL_FEATURE_SMC_HAS_SUB_STOP_MODE)

#if (defined(FSL_FEATURE_SMC_HAS_STOP_SUBMODE0) && FSL_FEATURE_SMC_HAS_STOP_SUBMODE0)
/*!
 * brief Configure the system to VLLS0 power mode.
 *
 * param base SMC peripheral base address.
 * return SMC configuration error code.
 */
status_t SMC_SetPowerModeVlls0(SMC_Type *base)
{
    uint32_t reg;

    /* configure to VLLS mode */
    reg = base->PMCTRL;
    reg &= ~SMC_PMCTRL_STOPM_MASK;
    reg |= ((uint32_t)kSMC_StopVlls0 << SMC_PMCTRL_STOPM_SHIFT);
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
#endif /* FSL_FEATURE_SMC_HAS_STOP_SUBMODE0 */

#if (defined(FSL_FEATURE_SMC_HAS_STOP_SUBMODE2) && FSL_FEATURE_SMC_HAS_STOP_SUBMODE2)
/*!
 * brief Configure the system to VLLS2 power mode.
 *
 * param base SMC peripheral base address.
 * return SMC configuration error code.
 */
status_t SMC_SetPowerModeVlls2(SMC_Type *base)
{
    uint32_t reg;

    /* configure to VLLS mode */
    reg = base->PMCTRL;
    reg &= ~SMC_PMCTRL_STOPM_MASK;
    reg |= ((uint32_t)kSMC_StopVlls2 << SMC_PMCTRL_STOPM_SHIFT);
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
#endif /* FSL_FEATURE_SMC_HAS_STOP_SUBMODE0 */

#else /* FSL_FEATURE_SMC_HAS_SUB_STOP_MODE */
/*!
 * brief Configure the system to VLLS power mode.
 *
 * param base SMC peripheral base address.
 * return SMC configuration error code.
 */
status_t SMC_SetPowerModeVlls(SMC_Type *base)
{
    uint32_t reg;
    status_t status;

    /* configure to VLLS mode */
    reg = base->PMCTRL;
    reg &= ~SMC_PMCTRL_STOPM_MASK;
    reg |= ((uint32_t)kSMC_StopVlls << SMC_PMCTRL_STOPM_SHIFT);
    base->PMCTRL = reg;

    /* Set the SLEEPDEEP bit to enable deep sleep mode */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* read back to make sure the configuration valid before enter stop mode */
    (void)base->PMCTRL;
    __DSB();
    __WFI();
    __ISB();

#if (defined(FSL_FEATURE_SMC_HAS_PMCTRL_STOPA) && FSL_FEATURE_SMC_HAS_PMCTRL_STOPA)
    /* check whether the power mode enter Stop mode succeed */
    if (0U != (base->PMCTRL & SMC_PMCTRL_STOPA_MASK))
    {
        status = kStatus_SMC_StopAbort;
    }
    else
    {
        status = kStatus_Success;
    }
#else
    status = kStatus_Success;
#endif /* FSL_FEATURE_SMC_HAS_PMCTRL_STOPA */

    return status;
}
#endif /* FSL_FEATURE_SMC_HAS_SUB_STOP_MODE */

/*!
 * brief Configures the reset pin filter.
 *
 * This function sets the reset pin filter including the enablement/disablement and filter width.
 *
 * param base SMC peripheral base address.
 * param config Pointer to the configuration structure.
 */
void SMC_ConfigureResetPinFilter(SMC_Type *base, const smc_reset_pin_filter_config_t *config)
{
    assert(NULL != config);

    uint32_t reg;

    reg = SMC_RPC_FILTCFG(config->slowClockFilterCount) | SMC_RPC_FILTEN(config->enableFilter);
#if (defined(FSL_FEATURE_SMC_HAS_RPC_LPOFEN) && FSL_FEATURE_SMC_HAS_RPC_LPOFEN)
    if (config->enableLpoFilter)
    {
        reg |= SMC_RPC_LPOFEN_MASK;
    }
#endif /* FSL_FEATURE_SMC_HAS_RPC_LPOFEN */

    base->RPC = reg;
}
