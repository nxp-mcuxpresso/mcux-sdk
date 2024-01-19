/*
 * Copyright 2021, NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_fusion.h"
#include "fsl_upower.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.fusion"
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Initializing Fusion core.
 *
 * Power up Fusion
 * Enable Fusion clocks
 * Enable SSRAM access
 * Clear reset
 */
void Fusion_Init(void)
{
    int status;

    SIM_SEC_Type *base = SIM_SEC;

    status = UPOWER_PowerOnSwitches(kUPOWER_PS_FUSION);
    if (status != 0)
    {
        assert(false);
    }

    base->SYSCTRL0 |= SIM_SEC_SYSCTRL0_FUSION_CLK_EN_MASK | SIM_SEC_SYSCTRL0_FUSION_PLAT_HCLK_EN_MASK;

    base->SSRAM_ACCESS_DISABLE &= ~SIM_SEC_SSRAM_ACCESS_DISABLE_SSRAM_DSP_ACCESS_DISABLE_MASK;

    base->SYSCTRL0 |= SIM_SEC_SYSCTRL0_FUSION_BCLK_EN_MASK | SIM_SEC_SYSCTRL0_FUSION_PBCLK_EN_MASK;

    base->SYSCTRL0 &= ~SIM_SEC_SYSCTRL0_FUSION_DSP_RST_MASK;
    base->SYSCTRL0 &= ~SIM_SEC_SYSCTRL0_FUSION_DSP_DBG_RST_MASK;
}

/*!
 * @brief Deinitializing Fusion core.
 *
 * Stop Fusion core
 * Disable Fusion clocks
 * Disable SSRAM access
 * Poweroff Fusion
 */
void Fusion_Deinit(void)
{
    int status;

    SIM_SEC_Type *base = SIM_SEC;

    Fusion_Stop();

    base->SYSCTRL0 |= SIM_SEC_SYSCTRL0_FUSION_DSP_DBG_RST_MASK;
    base->SYSCTRL0 |= SIM_SEC_SYSCTRL0_FUSION_DSP_RST_MASK;

    base->SYSCTRL0 &= ~(SIM_SEC_SYSCTRL0_FUSION_CLK_EN_MASK | SIM_SEC_SYSCTRL0_FUSION_PLAT_HCLK_EN_MASK);
    base->SYSCTRL0 &= ~(SIM_SEC_SYSCTRL0_FUSION_BCLK_EN_MASK | SIM_SEC_SYSCTRL0_FUSION_PBCLK_EN_MASK);

    base->SSRAM_ACCESS_DISABLE |= SIM_SEC_SSRAM_ACCESS_DISABLE_SSRAM_DSP_ACCESS_DISABLE_MASK;

    status = UPOWER_PowerOffSwitches(kUPOWER_PS_FUSION);
    if (status != 0)
    {
        assert(false);
    }
}

/*!
 * @brief Copy DSP image to destination address.
 *
 * Copy DSP image from source address to destination address with given size.
 *
 * @param dspCopyImage Structure contains information for DSP copy image to destination address.
 */
void DSP_CopyImage(dsp_copy_image_t *dspCopyImage)
{
    assert(dspCopyImage != NULL);
    assert(dspCopyImage->srcAddr != dspCopyImage->destAddr);

    uint32_t *srcAddr  = dspCopyImage->srcAddr;
    uint32_t *destAddr = dspCopyImage->destAddr;
    uint32_t size      = dspCopyImage->size;

    assert((size & 3U) == 0U);

    while (size > 0U)
    {
        *destAddr++ = *srcAddr++;
        size -= 4U;
    }
}
