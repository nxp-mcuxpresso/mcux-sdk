/*
 * Copyright 2017-2020, NXP
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
#define FSL_COMPONENT_ID "platform.drivers.gpc_2"
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * brief GPC init function.
 *
 * param base GPC peripheral base address.
 * param powerUpSlot power up slot number.
 * param powerDownSlot power down slot number.
 */
void GPC_Init(GPC_Type *base, uint32_t powerUpSlot, uint32_t powerDownSlot)
{
    assert(powerUpSlot < GPC_PCG_TIME_SLOT_TOTAL_NUMBER);
    assert(powerDownSlot < GPC_PCG_TIME_SLOT_TOTAL_NUMBER);

    /* Disable all interrupt */
    base->GPC_IMR[0U] = GPC_IMR_IMR1_MASK;
    base->GPC_IMR[1U] = GPC_IMR_IMR2_MASK;
    base->GPC_IMR[2U] = GPC_IMR_IMR3_MASK;
    base->GPC_IMR[3U] = GPC_IMR_IMR4_MASK;
#if (defined(GPC_IMR_M7_COUNT) && (GPC_IMR_M7_COUNT == 5U))
    base->GPC_IMR[4U] = GPC_IMR_IMR5_MASK;
#endif /* GPC_IMR_M7_COUNT */

    /* Not mask power down request */
    base->MISC |= GPC_MISC_PDN_REQ_MASK_MASK;
    /* Select virtual PGC ack */
    base->GPC_PGC_ACK_SEL |= (uint32_t)kGPC_VirtualPGCPowerUpAck | (uint32_t)kGPC_VirtualPGCPowerDownAck;
    /* Slot configurations */
#if !(defined(GPC_SLT_CFG_PU1_COUNT) && GPC_SLT_CFG_PU1_COUNT)
    base->SLT_CFG_PU[powerDownSlot] |= GPC_SLT_CFG_PU_PDN_SLOT_CONTROL_MASK;
    base->SLT_CFG_PU[powerUpSlot] |= GPC_SLT_CFG_PU_PUP_SLOT_CONTROL_MASK;
#else
    base->SLTn_CFG_PU[powerDownSlot].SLT_CFG_PU1 |= GPC_SLT_CFG_PU_PDN_SLOT_CONTROL_MASK;
    base->SLTn_CFG_PU[powerUpSlot].SLT_CFG_PU1 |= GPC_SLT_CFG_PU_PUP_SLOT_CONTROL_MASK;
#endif /* GPC_SLT_CFG_PU1_COUNT */

#if defined(FSL_FEATURE_GPC_HAS_PGC_MF) && FSL_FEATURE_GPC_HAS_PGC_MF
    base->SLT_CFG_PU[powerDownSlot] |= GPC_SLT_CFG_PU_MF_PDN_SLOT_CONTROL_MASK;
    base->SLT_CFG_PU[powerUpSlot] |= GPC_SLT_CFG_PU_MF_PUP_SLOT_CONTROL_MASK;
    /* Mapping PGC power up/down slot to fastmix/megamix PGC power up/down slow */
    base->PGC_CPU_0_1_MAPPING = GPC_PGC_CPU_0_1_MAPPING_MF_DOMAIN_MASK;
#endif /* FSL_FEATURE_GPC_HAS_PGC_MF */
}

/*!
 * brief Enable the IRQ.
 *
 * param base GPC peripheral base address.
 * param irqId ID number of IRQ to be enabled, available range is 0-127,reference SOC headerfile IRQn_Type.
 */
void GPC_EnableIRQ(GPC_Type *base, uint32_t irqId)
{
    uint32_t irqRegNum      = irqId / 32U;
    uint32_t irqRegShiftNum = irqId % 32U;

    assert(irqRegNum < GPC_IMR_COUNT);

    base->GPC_IMR[irqRegNum] &= ~(1UL << irqRegShiftNum);
}

/*!
 * brief Disable the IRQ.
 *
 * param base GPC peripheral base address.
 * param irqId ID number of IRQ to be disabled, available range is 0-127,reference SOC headerfile IRQn_Type.
 */
void GPC_DisableIRQ(GPC_Type *base, uint32_t irqId)
{
    uint32_t irqRegNum      = irqId / 32U;
    uint32_t irqRegShiftNum = irqId % 32U;

    assert(irqRegNum < GPC_IMR_COUNT);

    base->GPC_IMR[irqRegNum] |= (1UL << irqRegShiftNum);
}

/*!
 * brief Get the IRQ/Event flag.
 *
 * param base GPC peripheral base address.
 * param irqId ID number of IRQ to be enabled, available range is 0-127,reference SOC headerfile IRQn_Type.
 * return Indicated IRQ/Event is asserted or not.
 */
bool GPC_GetIRQStatusFlag(GPC_Type *base, uint32_t irqId)
{
    uint32_t isrRegNum      = irqId / 32U;
    uint32_t isrRegShiftNum = irqId % 32U;
    uint32_t ret;

    assert(isrRegNum < GPC_IMR_COUNT);

    ret = base->GPC_ISR[isrRegNum] & (1UL << isrRegShiftNum);

    return (1UL << isrRegShiftNum) == ret;
}

/*!
 * brief Enter WAIT mode.
 *
 * param base GPC peripheral base address.
 * param config lpm mode configurations.
 */
void GPC_EnterWaitMode(GPC_Type *base, gpc_lpm_config_t *config)
{
    uint32_t lpcr  = (base->GPC_LPCR) & (~GPC_LPCR_LPM0_MASK);
    uint32_t slpcr = base->SLPCR;

    if (config != NULL)
    {
        lpcr &= ~(GPC_LPCR_CPU_CLK_ON_LPM_MASK | GPC_LPCR_EN_PUP_MASK | GPC_LPCR_EN_PDN_MASK);
        lpcr |= (config->enCpuClk ? (uint32_t)GPC_LPCR_CPU_CLK_ON_LPM_MASK : 0UL) |
                (config->enVirtualPGCPowerup ? (uint32_t)GPC_LPCR_EN_PUP_MASK : 0UL) |
                (config->enVirtualPGCPowerdown ? (uint32_t)GPC_LPCR_EN_PDN_MASK : 0UL) |
                (config->enWfiMask ? (uint32_t)GPC_LPCR_MASK_WFI_MASK : 0UL) |
                (config->enDsmMask ? (uint32_t)GPC_LPCR_MASK_DSM_TRIGGER_MASK : 0UL);
        slpcr &= ~GPC_SLPCR_EN_FASTWUP_WAIT_MODE_MASK;
        slpcr |= config->enFastWakeUp ? GPC_SLPCR_EN_FASTWUP_WAIT_MODE_MASK : 0U;
    }

    base->SLPCR = slpcr;
    /* WAIT mode */
    base->GPC_LPCR = lpcr | (uint32_t)kGPC_WaitMode;
}

/*!
 * brief Enter STOP mode.
 *
 * param base GPC peripheral base address.
 * param config lpm mode configurations.
 */
void GPC_EnterStopMode(GPC_Type *base, gpc_lpm_config_t *config)
{
    uint32_t lpcr  = (base->GPC_LPCR) & (~GPC_LPCR_LPM0_MASK);
    uint32_t slpcr = base->SLPCR;

    if (config != NULL)
    {
        lpcr &= ~(GPC_LPCR_CPU_CLK_ON_LPM_MASK | GPC_LPCR_EN_PUP_MASK | GPC_LPCR_EN_PDN_MASK);
        lpcr |= (config->enCpuClk ? (uint32_t)GPC_LPCR_CPU_CLK_ON_LPM_MASK : 0UL) |
                (config->enVirtualPGCPowerup ? (uint32_t)GPC_LPCR_EN_PUP_MASK : 0UL) |
                (config->enVirtualPGCPowerdown ? (uint32_t)GPC_LPCR_EN_PDN_MASK : 0UL) |
                (config->enWfiMask ? (uint32_t)GPC_LPCR_MASK_WFI_MASK : 0UL) |
                (config->enDsmMask ? (uint32_t)GPC_LPCR_MASK_DSM_TRIGGER_MASK : 0UL);
        slpcr &= ~GPC_SLPCR_EN_FASTWUP_STOP_MODE_MASK;
        slpcr |= config->enFastWakeUp ? GPC_SLPCR_EN_FASTWUP_STOP_MODE_MASK : 0U;
    }

    base->SLPCR = slpcr;
    /* STOP mode */
    base->GPC_LPCR = lpcr | (uint32_t)kGPC_StopMode;
}
