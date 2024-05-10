/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_gpc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.gpc_3"
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief GPC submodule step registers offset */
static uint32_t const s_cmRegOffset[] = GPC_CM_STEP_REG_OFFSET;

static uint32_t const s_ssRegOffset[] = GPC_SS_STEP_REG_OFFSET;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*
 * brief Assign domain id for each cpu slice.
 *
 * This function assign the domain id for cpu slice. If there are multiple domains, use:
 * code
 *    domainMap = kGPC_Domain0 | kGPC_kGPC_Domain1 | ... | kGPC_kGPC_Domain15;
 * encode
 *
 * param slice GPC CPU slice number.
 * param domainMap Number of the domain. Refer to "_gpc_domain_map".
 */
void GPC_AssignCpuDomain(gpc_cpu_slice_t cpu, uint32_t domainMap)
{
    /* Ensure the allowed domain id is in the accessible range (0-15). */
    domainMap = domainMap & 0xFFFFUL;

    switch (cpu)
    {
        case kGPC_CPU0:
            GPC_GLOBAL->GPC_CPU0_DOMAIN = domainMap;
            break;
        case kGPC_CPU1:
            GPC_GLOBAL->GPC_CPU1_DOMAIN = domainMap;
            break;
        default:
            assert(false);
            break;
    }
}

/*!
 * brief Enable IRQ wakeup request.
 *
 * This function enables the IRQ request which can wakeup the CPU platform.
 *
 * param slice GPC CPU slice number.
 * param irqId ID of the IRQ, accessible range is 0-255.
 * param enable Enable the IRQ request or not.
 */
void GPC_CM_EnableIrqWakeup(gpc_cpu_slice_t slice, uint32_t irqId, bool enable)
{
    assert(irqId < (GPC_CPU_CTRL_CM_IRQ_WAKEUP_MASK_COUNT2 * 32UL));

    uint32_t irqGroup = irqId / 32UL;
    uint32_t irqMask  = irqId % 32UL;

    if (true == enable)
    {
        GPC_CPU_CTRL->AUTHEN[slice].CM_IRQ_WAKEUP_MASK[irqGroup] &= ~(1UL << irqMask);
    }
    else
    {
        GPC_CPU_CTRL->AUTHEN[slice].CM_IRQ_WAKEUP_MASK[irqGroup] |= (1UL << irqMask);
    }
}

/*!
 * brief Get the status of the IRQ wakeup request.
 *
 * param slice GPC CPU slice number.
 * param irqId ID of the IRQ, accessible range is 0-255.
 * return Indicate the IRQ request is asserted or not.
 */
bool GPC_CM_GetIrqWakeupStatus(gpc_cpu_slice_t slice, uint32_t irqId)
{
    assert(irqId < (GPC_CPU_CTRL_CM_IRQ_WAKEUP_MASK_COUNT2 * 32UL));

    uint32_t irqGroup = irqId / 32UL;
    uint32_t irqMask  = irqId % 32UL;
    bool irqStatus    = false;

    irqStatus =
        (((GPC_CPU_CTRL->AUTHEN[slice].CM_IRQ_WAKEUP_STAT[irqGroup] >> irqMask) & 0x1UL) == 0x1UL) ? true : false;
    return irqStatus;
}

/*!
 * brief Config the cpu mode transition step.
 *
 * param slice GPC CPU slice number.
 * param step step type, refer to "gpc_cm_tran_step_t".
 * param enable Used to control the transition step.
 *            - \b true This step is enabled.
 *            - \b false This step is disabled, GPC will skip this step and not send any request.
 */
void GPC_CM_EnableCpuModeTransitionStep(gpc_cpu_slice_t slice, gpc_cm_tran_step_t step, bool enable)
{
    if (!((step >= kGPC_CM_SleepSYS) && (step <= kGPC_CM_WakeupSYS)))
    {
        uint32_t tmp32 = *(uint32_t *)((uint32_t)(&GPC_CPU_CTRL->AUTHEN[slice]) + s_cmRegOffset[step]);

        if (enable)
        {
            tmp32 &= ~GPC_CPU_CTRL_CM_SLEEP_SSAR_CTRL_DISABLE_MASK;
        }
        else
        {
            tmp32 |= GPC_CPU_CTRL_CM_SLEEP_SSAR_CTRL_DISABLE_MASK;
        }
        *(uint32_t *)((uint32_t)(&GPC_CPU_CTRL->AUTHEN[slice]) + s_cmRegOffset[step]) = tmp32;
    }
}

/*
 * brief Request the chip into system sleep mode.
 *
 * param slice GPC CPU slice number.
 * param mode CPU mode. Refer to "gpc_cpu_mode_t".
 */
void GPC_CM_RequestSystemSleepMode(gpc_cpu_slice_t slice, const gpc_cpu_mode_t mode)
{
    assert(mode != kGPC_RunMode);

    switch (mode)
    {
        case kGPC_WaitMode:
            GPC_CPU_CTRL->AUTHEN[slice].CM_SYS_SLEEP_CTRL |= GPC_CPU_CTRL_CM_SYS_SLEEP_CTRL_SS_WAIT_MASK;
            break;
        case kGPC_StopMode:
            GPC_CPU_CTRL->AUTHEN[slice].CM_SYS_SLEEP_CTRL |= GPC_CPU_CTRL_CM_SYS_SLEEP_CTRL_SS_STOP_MASK;
            break;
        case kGPC_SuspendMode:
            GPC_CPU_CTRL->AUTHEN[slice].CM_SYS_SLEEP_CTRL |= GPC_CPU_CTRL_CM_SYS_SLEEP_CTRL_SS_SUSPEND_MASK;
            break;
        default:
            /* This branch should never be hit. */
            break;
    }
}

/*
 * brief Clear the system sleep mode request.
 *
 * param slice GPC CPU slice number.
 * param mode CPU mode. Refer to "gpc_cpu_mode_t".
 */
void GPC_CM_ClearSystemSleepModeRequest(gpc_cpu_slice_t slice, const gpc_cpu_mode_t mode)
{
    assert(mode != kGPC_RunMode);

    switch (mode)
    {
        case kGPC_WaitMode:
            GPC_CPU_CTRL->AUTHEN[slice].CM_SYS_SLEEP_CTRL &= ~GPC_CPU_CTRL_CM_SYS_SLEEP_CTRL_SS_WAIT_MASK;
            break;
        case kGPC_StopMode:
            GPC_CPU_CTRL->AUTHEN[slice].CM_SYS_SLEEP_CTRL &= ~GPC_CPU_CTRL_CM_SYS_SLEEP_CTRL_SS_STOP_MASK;
            break;
        case kGPC_SuspendMode:
            GPC_CPU_CTRL->AUTHEN[slice].CM_SYS_SLEEP_CTRL &= ~GPC_CPU_CTRL_CM_SYS_SLEEP_CTRL_SS_SUSPEND_MASK;
            break;
        default:
            /* This branch should never be hit. */
            break;
    }
}

/*!
 * brief Config the system sleep transition step.
 *
 * param base GPC system sleep controller base address.
 * param step step type, refer to "gpc_ss_tran_step_t".
 * param enable Used to control the transition step.
 *            - \b true This step is enabled.
 *            - \b false This step is disabled, GPC will skip this step and not send any request.
 */
void GPC_SS_EnableSystemSleepTransitionStep(GPC_SYS_SLEEP_CTRL_Type *base, gpc_ss_tran_step_t step, bool enable)
{
    uint32_t tmp32 = *(uint32_t *)((uint32_t)base + s_ssRegOffset[step]);

    if (enable)
    {
        tmp32 &= ~GPC_SYS_SLEEP_CTRL_SS_STEP0_IN_CTRL_DISABLE_MASK;
    }
    else
    {
        tmp32 |= GPC_SYS_SLEEP_CTRL_SS_STEP0_IN_CTRL_DISABLE_MASK;
    }
    *(uint32_t *)((uint32_t)base + s_ssRegOffset[step]) = tmp32;
}
