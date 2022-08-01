/*
 * Copyright 2020-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_audiomix.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.audiomix"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * brief audiomix attach clock.
 *
 * param base audiomix base address.
 * param id attach clock id.
 */
void AUDIOMIX_AttachClk(AUDIOMIX_Type *base, audiomix_attch_clk_t id)
{
    /* extract offset, mask, value */
    uint32_t offset             = GET_AUDIOMIX_ATTACH_ID_OFFSET(id);
    uint32_t mask               = GET_AUDIOMIX_ATTACH_ID_MASK(id);
    uint32_t value              = GET_AUDIOMIX_ATTACH_ID_value(id);
    volatile uint32_t *baseAddr = (volatile uint32_t *)((uintptr_t)base + offset);
    /* load to register */
    *baseAddr = (*baseAddr & ~mask) | value;
}

/*!
 * brief Initializes the SAI PLL.
 * note This function can't detect whether the AUDIO PLL has been enabled and
 * used by some IPs.
 *
 * param config Pointer to the configuration structure(see ref ccm_analog_frac_pll_config_t enumeration).
 *
 */
void AUDIOMIX_InitAudioPll(AUDIOMIX_Type *base, const ccm_analog_frac_pll_config_t *config)
{
    assert(config != NULL);

    uint32_t fracCfg1 = base->SAI_PLL_FDIV_CTL0;
    uint32_t fracCfg2 = base->SAI_PLL_FDIV_CTL1;

    /* PLL power down and no bypass */
    base->SAI_PLL_GNRL_CTL =
        base->SAI_PLL_GNRL_CTL & (~(AUDIOMIX_SAI_PLL_GNRL_CTL_RESETB_MASK | AUDIOMIX_SAI_PLL_GNRL_CTL_BYPASS_MASK));
    base->SAI_PLL_FDIV_CTL0 =
        (fracCfg1 & (~(AUDIOMIX_SAI_PLL_FDIV_CTL0_MAIN_DIV_MASK | AUDIOMIX_SAI_PLL_FDIV_CTL0_PRE_DIV_MASK |
                       AUDIOMIX_SAI_PLL_FDIV_CTL0_POST_DIV_MASK))) |
        AUDIOMIX_SAI_PLL_FDIV_CTL0_MAIN_DIV(config->mainDiv) | AUDIOMIX_SAI_PLL_FDIV_CTL0_PRE_DIV(config->preDiv) |
        AUDIOMIX_SAI_PLL_FDIV_CTL0_POST_DIV(config->postDiv);

    base->SAI_PLL_FDIV_CTL1 =
        (fracCfg2 & (~(AUDIOMIX_SAI_PLL_FDIV_CTL1_DSM_MASK))) | AUDIOMIX_SAI_PLL_FDIV_CTL1_DSM(config->dsm);

    base->SAI_PLL_GNRL_CTL |=
        AUDIOMIX_SAI_PLL_GNRL_CTL_RESETB_MASK | AUDIOMIX_SAI_PLL_GNRL_CTL_CKE_MASK; /* Enable and power up PLL clock. */

    /* Wait for PLL to be locked. */
    while ((base->SAI_PLL_GNRL_CTL & AUDIOMIX_SAI_PLL_GNRL_CTL_LOCK_MASK) == 0U)
    {
    }
}

/*!
 * brief De-initialize the SAI PLL.
 */
void AUDIOMIX_DeinitAudioPll1(AUDIOMIX_Type *base)
{
    base->SAI_PLL_GNRL_CTL &= ~AUDIOMIX_SAI_PLL_GNRL_CTL_RESETB_MASK;
}

/*!
 * brief Get the sai PLL output freq.
 *
 * retval sai pll output freq.
 */
uint32_t AUDIOMIX_GetAudioPllFreq(AUDIOMIX_Type *base)
{
    uint32_t fracCfg1 = base->SAI_PLL_FDIV_CTL0;
    uint32_t fracCfg2 = base->SAI_PLL_FDIV_CTL1;
    uint64_t fracClk  = 0U;
    /* get reference clock freq */
    uint32_t refClkFreq =
        (base->SAI_PLL_GNRL_CTL & AUDIOMIX_SAI_PLL_GNRL_CTL_REF_CLK_SEL_MASK) != 0U ? CLKPAD_FREQ : OSC24M_CLK_FREQ;
    /* main divider */
    uint32_t mainDiv =
        (fracCfg1 & AUDIOMIX_SAI_PLL_FDIV_CTL0_MAIN_DIV_MASK) >> AUDIOMIX_SAI_PLL_FDIV_CTL0_MAIN_DIV_SHIFT;
    /* pre divider */
    uint32_t preDiv = (fracCfg1 & AUDIOMIX_SAI_PLL_FDIV_CTL0_PRE_DIV_MASK) >> AUDIOMIX_SAI_PLL_FDIV_CTL0_PRE_DIV_SHIFT;
    /* post divider */
    uint32_t postDiv =
        ((fracCfg1 & AUDIOMIX_SAI_PLL_FDIV_CTL0_POST_DIV_MASK) >> AUDIOMIX_SAI_PLL_FDIV_CTL0_POST_DIV_SHIFT);
    uint32_t dsm = (fracCfg2 & AUDIOMIX_SAI_PLL_FDIV_CTL1_DSM_MASK) >> AUDIOMIX_SAI_PLL_FDIV_CTL1_DSM_SHIFT;

    /* calculate the audio pll frequ */
    fracClk = (uint64_t)refClkFreq * ((uint64_t)mainDiv * 65536UL + dsm) / (65536UL * preDiv * (1UL << postDiv));

    return (uint32_t)fracClk;
}
