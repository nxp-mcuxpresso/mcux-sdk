/*
 * Copyright 2020, 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_clock.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.clock"
#endif

#define CGC_SOSCDIV_DIV1_VAL(reg)                                       \
    (((((reg)&CGC_SOSCDIV_DIV1_MASK) >> CGC_SOSCDIV_DIV1_SHIFT) + 1U) * \
     ((((reg)&CGC_SOSCDIV_DIV1HALT_MASK) >> CGC_SOSCDIV_DIV1HALT_SHIFT) ^ 1U))
#define CGC_SOSCDIV_DIV2_VAL(reg)                                       \
    (((((reg)&CGC_SOSCDIV_DIV2_MASK) >> CGC_SOSCDIV_DIV2_SHIFT) + 1U) * \
     ((((reg)&CGC_SOSCDIV_DIV2HALT_MASK) >> CGC_SOSCDIV_DIV2HALT_SHIFT) ^ 1U))
#define CGC_SOSCDIV_DIV3_VAL(reg)                                       \
    (((((reg)&CGC_SOSCDIV_DIV3_MASK) >> CGC_SOSCDIV_DIV3_SHIFT) + 1U) * \
     ((((reg)&CGC_SOSCDIV_DIV3HALT_MASK) >> CGC_SOSCDIV_DIV3HALT_SHIFT) ^ 1U))
#define CGC_FRODIV_DIV1_VAL(reg)                                      \
    (((((reg)&CGC_FRODIV_DIV1_MASK) >> CGC_FRODIV_DIV1_SHIFT) + 1U) * \
     ((((reg)&CGC_FRODIV_DIV1HALT_MASK) >> CGC_FRODIV_DIV1HALT_SHIFT) ^ 1U))
#define CGC_FRODIV_DIV2_VAL(reg)                                      \
    (((((reg)&CGC_FRODIV_DIV2_MASK) >> CGC_FRODIV_DIV2_SHIFT) + 1U) * \
     ((((reg)&CGC_FRODIV_DIV2HALT_MASK) >> CGC_FRODIV_DIV2HALT_SHIFT) ^ 1U))
#define CGC_FRODIV_DIV3_VAL(reg)                                      \
    (((((reg)&CGC_FRODIV_DIV3_MASK) >> CGC_FRODIV_DIV3_SHIFT) + 1U) * \
     ((((reg)&CGC_FRODIV_DIV3HALT_MASK) >> CGC_FRODIV_DIV3HALT_SHIFT) ^ 1U))

#define CGC_PLL0DIV_VCO_DIV1_VAL                                                                 \
    ((((CGC_RTD->PLL0DIV_VCO & CGC_PLL0DIV_VCO_DIV1_MASK) >> CGC_PLL0DIV_VCO_DIV1_SHIFT) + 1U) * \
     (((CGC_RTD->PLL0DIV_VCO & CGC_PLL0DIV_VCO_DIV1HALT_MASK) >> CGC_PLL0DIV_VCO_DIV1HALT_SHIFT) ^ 1U))
#define CGC_PLL0DIV_PFD1_DIV_VAL                                                                       \
    ((((CGC_RTD->PLL0DIV_PFD_0 & CGC_PLL0DIV_PFD_0_DIV1_MASK) >> CGC_PLL0DIV_PFD_0_DIV1_SHIFT) + 1U) * \
     (((CGC_RTD->PLL0DIV_PFD_0 & CGC_PLL0DIV_PFD_0_DIV1HALT_MASK) >> CGC_PLL0DIV_PFD_0_DIV1HALT_SHIFT) ^ 1U))
#define CGC_PLL0DIV_PFD2_DIV_VAL                                                                       \
    ((((CGC_RTD->PLL0DIV_PFD_0 & CGC_PLL0DIV_PFD_0_DIV2_MASK) >> CGC_PLL0DIV_PFD_0_DIV2_SHIFT) + 1U) * \
     (((CGC_RTD->PLL0DIV_PFD_0 & CGC_PLL0DIV_PFD_0_DIV2HALT_MASK) >> CGC_PLL0DIV_PFD_0_DIV2HALT_SHIFT) ^ 1U))

#define CGC_PLL1DIV_VCO_DIV1_VAL                                                                 \
    ((((CGC_RTD->PLL1DIV_VCO & CGC_PLL1DIV_VCO_DIV1_MASK) >> CGC_PLL1DIV_VCO_DIV1_SHIFT) + 1U) * \
     (((CGC_RTD->PLL1DIV_VCO & CGC_PLL1DIV_VCO_DIV1HALT_MASK) >> CGC_PLL1DIV_VCO_DIV1HALT_SHIFT) ^ 1U))
#define CGC_PLL1DIV_PFD1_DIV_VAL                                                                       \
    ((((CGC_RTD->PLL1DIV_PFD_0 & CGC_PLL1DIV_PFD_0_DIV1_MASK) >> CGC_PLL1DIV_PFD_0_DIV1_SHIFT) + 1U) * \
     (((CGC_RTD->PLL1DIV_PFD_0 & CGC_PLL1DIV_PFD_0_DIV1HALT_MASK) >> CGC_PLL1DIV_PFD_0_DIV1HALT_SHIFT) ^ 1U))
#define CGC_PLL1DIV_PFD2_DIV_VAL                                                                       \
    ((((CGC_RTD->PLL1DIV_PFD_0 & CGC_PLL1DIV_PFD_0_DIV2_MASK) >> CGC_PLL1DIV_PFD_0_DIV2_SHIFT) + 1U) * \
     (((CGC_RTD->PLL1DIV_PFD_0 & CGC_PLL1DIV_PFD_0_DIV2HALT_MASK) >> CGC_PLL1DIV_PFD_0_DIV2HALT_SHIFT) ^ 1U))

#define CGC_AD_PLL3DIV_VCO_DIV1_VAL                                                                   \
    ((((CGC_AD->PLL3DIV_VCO & CGC_AD_PLL3DIV_VCO_DIV1_MASK) >> CGC_AD_PLL3DIV_VCO_DIV1_SHIFT) + 1U) * \
     (((CGC_AD->PLL3DIV_VCO & CGC_AD_PLL3DIV_VCO_DIV1HALT_MASK) >> CGC_AD_PLL3DIV_VCO_DIV1HALT_SHIFT) ^ 1U))
#define CGC_AD_PLL3DIV_PFD0_DIV1_VAL                                                                        \
    ((((CGC_AD->PLL3DIV_PFD_0 & CGC_AD_PLL3DIV_PFD_0_DIV1_MASK) >> CGC_AD_PLL3DIV_PFD_0_DIV1_SHIFT) + 1U) * \
     (((CGC_AD->PLL3DIV_PFD_0 & CGC_AD_PLL3DIV_PFD_0_DIV1HALT_MASK) >> CGC_AD_PLL3DIV_PFD_0_DIV1HALT_SHIFT) ^ 1U))
#define CGC_AD_PLL3DIV_PFD0_DIV2_VAL                                                                        \
    ((((CGC_AD->PLL3DIV_PFD_0 & CGC_AD_PLL3DIV_PFD_0_DIV2_MASK) >> CGC_AD_PLL3DIV_PFD_0_DIV2_SHIFT) + 1U) * \
     (((CGC_AD->PLL3DIV_PFD_0 & CGC_AD_PLL3DIV_PFD_0_DIV2HALT_MASK) >> CGC_AD_PLL3DIV_PFD_0_DIV2HALT_SHIFT) ^ 1U))
#define CGC_AD_PLL3DIV_PFD1_DIV1_VAL                                                                        \
    ((((CGC_AD->PLL3DIV_PFD_0 & CGC_AD_PLL3DIV_PFD_0_DIV3_MASK) >> CGC_AD_PLL3DIV_PFD_0_DIV3_SHIFT) + 1U) * \
     (((CGC_AD->PLL3DIV_PFD_0 & CGC_AD_PLL3DIV_PFD_0_DIV3HALT_MASK) >> CGC_AD_PLL3DIV_PFD_0_DIV3HALT_SHIFT) ^ 1U))
#define CGC_AD_PLL3DIV_PFD1_DIV2_VAL                                                                        \
    ((((CGC_AD->PLL3DIV_PFD_0 & CGC_AD_PLL3DIV_PFD_0_DIV4_MASK) >> CGC_AD_PLL3DIV_PFD_0_DIV4_SHIFT) + 1U) * \
     (((CGC_AD->PLL3DIV_PFD_0 & CGC_AD_PLL3DIV_PFD_0_DIV4HALT_MASK) >> CGC_AD_PLL3DIV_PFD_0_DIV4HALT_SHIFT) ^ 1U))
#define CGC_AD_PLL3DIV_PFD2_DIV1_VAL                                                                        \
    ((((CGC_AD->PLL3DIV_PFD_1 & CGC_AD_PLL3DIV_PFD_1_DIV1_MASK) >> CGC_AD_PLL3DIV_PFD_1_DIV1_SHIFT) + 1U) * \
     (((CGC_AD->PLL3DIV_PFD_1 & CGC_AD_PLL3DIV_PFD_1_DIV1HALT_MASK) >> CGC_AD_PLL3DIV_PFD_1_DIV1HALT_SHIFT) ^ 1U))
#define CGC_AD_PLL3DIV_PFD2_DIV2_VAL                                                                        \
    ((((CGC_AD->PLL3DIV_PFD_1 & CGC_AD_PLL3DIV_PFD_1_DIV2_MASK) >> CGC_AD_PLL3DIV_PFD_1_DIV2_SHIFT) + 1U) * \
     (((CGC_AD->PLL3DIV_PFD_1 & CGC_AD_PLL3DIV_PFD_1_DIV2HALT_MASK) >> CGC_AD_PLL3DIV_PFD_1_DIV2HALT_SHIFT) ^ 1U))
#define CGC_AD_PLL3DIV_PFD3_DIV1_VAL                                                                        \
    ((((CGC_AD->PLL3DIV_PFD_1 & CGC_AD_PLL3DIV_PFD_1_DIV3_MASK) >> CGC_AD_PLL3DIV_PFD_1_DIV3_SHIFT) + 1U) * \
     (((CGC_AD->PLL3DIV_PFD_1 & CGC_AD_PLL3DIV_PFD_1_DIV3HALT_MASK) >> CGC_AD_PLL3DIV_PFD_1_DIV3HALT_SHIFT) ^ 1U))
#define CGC_AD_PLL3DIV_PFD3_DIV2_VAL                                                                        \
    ((((CGC_AD->PLL3DIV_PFD_1 & CGC_AD_PLL3DIV_PFD_1_DIV4_MASK) >> CGC_AD_PLL3DIV_PFD_1_DIV4_SHIFT) + 1U) * \
     (((CGC_AD->PLL3DIV_PFD_1 & CGC_AD_PLL3DIV_PFD_1_DIV4HALT_MASK) >> CGC_AD_PLL3DIV_PFD_1_DIV4HALT_SHIFT) ^ 1U))

#define CGC_LPAV_PLL4DIV_VCO_DIV1_VAL                                                                       \
    ((((CGC_LPAV->PLL4DIV_VCO & CGC_LPAV_PLL4DIV_VCO_DIV1_MASK) >> CGC_LPAV_PLL4DIV_VCO_DIV1_SHIFT) + 1U) * \
     (((CGC_LPAV->PLL4DIV_VCO & CGC_LPAV_PLL4DIV_VCO_DIV1HALT_MASK) >> CGC_LPAV_PLL4DIV_VCO_DIV1HALT_SHIFT) ^ 1U))
#define CGC_LPAV_PLL4DIV_PFD0_DIV1_VAL                                                                              \
    ((((CGC_LPAV->PLL4DIV_PFD_0 & CGC_LPAV_PLL4DIV_PFD_0_DIV1_MASK) >> CGC_LPAV_PLL4DIV_PFD_0_DIV1_SHIFT) + 1U) *   \
     (((CGC_LPAV->PLL4DIV_PFD_0 & CGC_LPAV_PLL4DIV_PFD_0_DIV1HALT_MASK) >> CGC_LPAV_PLL4DIV_PFD_0_DIV1HALT_SHIFT) ^ \
      1U))
#define CGC_LPAV_PLL4DIV_PFD0_DIV2_VAL                                                                              \
    ((((CGC_LPAV->PLL4DIV_PFD_0 & CGC_LPAV_PLL4DIV_PFD_0_DIV2_MASK) >> CGC_LPAV_PLL4DIV_PFD_0_DIV2_SHIFT) + 1U) *   \
     (((CGC_LPAV->PLL4DIV_PFD_0 & CGC_LPAV_PLL4DIV_PFD_0_DIV2HALT_MASK) >> CGC_LPAV_PLL4DIV_PFD_0_DIV2HALT_SHIFT) ^ \
      1U))
#define CGC_LPAV_PLL4DIV_PFD1_DIV1_VAL                                                                              \
    ((((CGC_LPAV->PLL4DIV_PFD_0 & CGC_LPAV_PLL4DIV_PFD_0_DIV3_MASK) >> CGC_LPAV_PLL4DIV_PFD_0_DIV3_SHIFT) + 1U) *   \
     (((CGC_LPAV->PLL4DIV_PFD_0 & CGC_LPAV_PLL4DIV_PFD_0_DIV3HALT_MASK) >> CGC_LPAV_PLL4DIV_PFD_0_DIV3HALT_SHIFT) ^ \
      1U))
#define CGC_LPAV_PLL4DIV_PFD1_DIV2_VAL                                                                              \
    ((((CGC_LPAV->PLL4DIV_PFD_0 & CGC_LPAV_PLL4DIV_PFD_0_DIV4_MASK) >> CGC_LPAV_PLL4DIV_PFD_0_DIV4_SHIFT) + 1U) *   \
     (((CGC_LPAV->PLL4DIV_PFD_0 & CGC_LPAV_PLL4DIV_PFD_0_DIV4HALT_MASK) >> CGC_LPAV_PLL4DIV_PFD_0_DIV4HALT_SHIFT) ^ \
      1U))
#define CGC_LPAV_PLL4DIV_PFD2_DIV1_VAL                                                                              \
    ((((CGC_LPAV->PLL4DIV_PFD_1 & CGC_LPAV_PLL4DIV_PFD_1_DIV1_MASK) >> CGC_LPAV_PLL4DIV_PFD_1_DIV1_SHIFT) + 1U) *   \
     (((CGC_LPAV->PLL4DIV_PFD_1 & CGC_LPAV_PLL4DIV_PFD_1_DIV1HALT_MASK) >> CGC_LPAV_PLL4DIV_PFD_1_DIV1HALT_SHIFT) ^ \
      1U))
#define CGC_LPAV_PLL4DIV_PFD2_DIV2_VAL                                                                              \
    ((((CGC_LPAV->PLL4DIV_PFD_1 & CGC_LPAV_PLL4DIV_PFD_1_DIV2_MASK) >> CGC_LPAV_PLL4DIV_PFD_1_DIV2_SHIFT) + 1U) *   \
     (((CGC_LPAV->PLL4DIV_PFD_1 & CGC_LPAV_PLL4DIV_PFD_1_DIV2HALT_MASK) >> CGC_LPAV_PLL4DIV_PFD_1_DIV2HALT_SHIFT) ^ \
      1U))
#define CGC_LPAV_PLL4DIV_PFD3_DIV1_VAL                                                                              \
    ((((CGC_LPAV->PLL4DIV_PFD_1 & CGC_LPAV_PLL4DIV_PFD_1_DIV3_MASK) >> CGC_LPAV_PLL4DIV_PFD_1_DIV3_SHIFT) + 1U) *   \
     (((CGC_LPAV->PLL4DIV_PFD_1 & CGC_LPAV_PLL4DIV_PFD_1_DIV3HALT_MASK) >> CGC_LPAV_PLL4DIV_PFD_1_DIV3HALT_SHIFT) ^ \
      1U))
#define CGC_LPAV_PLL4DIV_PFD3_DIV2_VAL                                                                              \
    ((((CGC_LPAV->PLL4DIV_PFD_1 & CGC_LPAV_PLL4DIV_PFD_1_DIV4_MASK) >> CGC_LPAV_PLL4DIV_PFD_1_DIV4_SHIFT) + 1U) *   \
     (((CGC_LPAV->PLL4DIV_PFD_1 & CGC_LPAV_PLL4DIV_PFD_1_DIV4HALT_MASK) >> CGC_LPAV_PLL4DIV_PFD_1_DIV4HALT_SHIFT) ^ \
      1U))

#define CGC_PLLPFD_PFD_MAX_VAL (CGC_PLL0PFDCFG_PFD0_MASK >> CGC_PLL0PFDCFG_PFD0_SHIFT)

#define CGC_PLL1NUM_NUM_VAL        (uint32_t)((CGC_RTD->PLL1NUM & CGC_PLL1NUM_NUM_MASK) >> CGC_PLL1NUM_NUM_SHIFT)
#define CGC_PLL1DENOM_DENOM_VAL    ((CGC_RTD->PLL1DENOM & CGC_PLL1DENOM_DENOM_MASK) >> CGC_PLL1DENOM_DENOM_SHIFT)
#define CGC_AD_PLL3NUM_NUM_VAL     (uint32_t)((CGC_AD->PLL3NUM & CGC_AD_PLL3NUM_NUM_MASK) >> CGC_AD_PLL3NUM_NUM_SHIFT)
#define CGC_AD_PLL3DENOM_DENOM_VAL ((CGC_AD->PLL3DENOM & CGC_AD_PLL3DENOM_DENOM_MASK) >> CGC_AD_PLL3DENOM_DENOM_SHIFT)
#define CGC_LPAV_PLL4NUM_NUM_VAL \
    (uint32_t)((CGC_LPAV->PLL4NUM & CGC_LPAV_PLL4NUM_NUM_MASK) >> CGC_LPAV_PLL4NUM_NUM_SHIFT)
#define CGC_LPAV_PLL4DENOM_DENOM_VAL \
    ((CGC_LPAV->PLL4DENOM & CGC_LPAV_PLL4DENOM_DENOM_MASK) >> CGC_LPAV_PLL4DENOM_DENOM_SHIFT)

#define CGC_PLL0CFG_MULT_VAL      ((CGC_RTD->PLL0CFG & CGC_PLL0CFG_MULT_MASK) >> CGC_PLL0CFG_MULT_SHIFT)
#define CGC_PLL1CFG_MULT_VAL      ((CGC_RTD->PLL1CFG & CGC_PLL1CFG_MULT_MASK) >> CGC_PLL1CFG_MULT_SHIFT)
#define CGC_AD_PLL3CFG_MULT_VAL   ((CGC_AD->PLL3CFG & CGC_AD_PLL3CFG_MULT_MASK) >> CGC_AD_PLL3CFG_MULT_SHIFT)
#define CGC_LPAV_PLL4CFG_MULT_VAL ((CGC_LPAV->PLL4CFG & CGC_LPAV_PLL4CFG_MULT_MASK) >> CGC_LPAV_PLL4CFG_MULT_SHIFT)
/*
 * Constant used to calcul PLL PFD clock frequency
 * PFD Clock Frequency = PLL output frequency * 18/frac value
 */
#define PFD_FREQ_CALCUL_CONSTANT 18U

/*! @brief Get PCC PCS value for enum value defined by clock_ip_src_t. */
#define CLOCK_IP_SRC_PCC_PCS(src) (((uint32_t)(src)) & (PCC_CLKCFG_PCS_MASK >> PCC_CLKCFG_PCS_SHIFT))

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* PLL0 multiplier array */
static const uint8_t s_pll0Multi[] = {0U, 15U, 16U, 20U, 22U, 25U, 30U, 0U};
/* External XTAL (OSC) clock frequency. */
volatile uint32_t g_xtal0Freq;
/* External XTAL32K clock frequency. */
volatile uint32_t g_xtal32Freq;
/* External LVDS pad clock frequency. */
volatile uint32_t g_lvdsFreq;
/* External MCLK pad clock frequency. */
volatile uint32_t g_mclkFreq[4];
/* RX_BCLK pad clock frequency. */
volatile uint32_t g_rxBclkFreq[8];
/* TX_BCLK pad clock frequency. */
volatile uint32_t g_txBclkFreq[8];
/*! Recovered SPDIF_RX clock frequency. */
volatile uint32_t g_spdifRxFreq;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get the common PLL0 frequency for both RAW PLL0 output and PLL0 PFD output.
 *
 * The "raw" PLL0 output is the clkout of PLL0.
 * The "common" PLL0 frequency is the common part for both RAW PLL0 and PLL0 PFD output.
 * That is the frequency calculated based on the clock source which passes through MULT.
 * "Common" PLL0 Frequency = Reference Frequency * MULT
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
static uint32_t CLOCK_GetPll0CommonFreq(void);

/*!
 * @brief Get the common PLL1 frequency for both RAW PLL1 output and PLL1 PFD output.
 *
 * The "raw" PLL1 output is the clkout of PLL1.
 * The "common" PLL1 frequency is the common part for both RAW PLL1 and PLL1 PFD output.
 * That is the frequency calculated based on the clock source which passes through MULT.
 * "Common" PLL1 Frequency = Reference Frequency * MULT
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
static uint32_t CLOCK_GetPll1CommonFreq(void);

/*!
 * @brief Get the common PLL3 frequency for both RAW PLL3 output and PLL3 PFD output.
 *
 * The "raw" PLL3 output is the clkout of PLL3.
 * The "common" PLL3 frequency is the common part for both RAW PLL3 and PLL3 PFD output.
 * That is the frequency calculated based on the clock source which passes through MULT.
 * "Common" PLL3 Frequency = Reference Frequency * MULT
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
static uint32_t CLOCK_GetPll3CommonFreq(void);

/*!
 * @brief Get the common PLL4 frequency for both RAW PLL4 output and PLL4 PFD output.
 *
 * The "raw" PLL4 output is the clkout of PLL4.
 * The "common" PLL4 frequency is the common part for both RAW PLL4 and PLL4 PFD output.
 * That is the frequency calculated based on the clock source which passes through MULT.
 * "Common" PLL4 Frequency = Reference Frequency * MULT
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
static uint32_t CLOCK_GetPll4CommonFreq(void);

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t CLOCK_GetPccInstance(clock_ip_name_t name)
{
    uint32_t i;

    switch ((uint32_t)name & 0x2FFFF000U)
    {
        case (PCC0_BASE & 0x2FFFF000U):
            i = 0;
            break;
        case (PCC1_BASE & 0x2FFFF000U):
            i = 1;
            break;
        case (PCC2_BASE & 0x2FFFF000U):
            i = 2;
            break;
        case (PCC3_BASE & 0x2FFFF000U):
            i = 3;
            break;
        case (PCC4_BASE & 0x2FFFF000U):
            i = 4;
            break;
        case (PCC5_BASE & 0x2FFFF000U):
            i = 5;
            break;
        default:
            assert(false);
            i = 0;
            break;
    }

    return i;
}

static uint32_t CLOCK_GetMclkFreq(uint32_t index)
{
    assert(g_mclkFreq[index] > 0U); /* Must be set via CLOCK_SetMclkFreq() */

    return g_mclkFreq[index];
}

static uint32_t CLOCK_GetSaiRxBclkFreq(uint32_t instance)
{
    assert(g_rxBclkFreq[instance] > 0U); /* Must be set via CLOCK_SetRxBclkFreq() */

    return g_rxBclkFreq[instance];
}

static uint32_t CLOCK_GetSaiTxBclkFreq(uint32_t instance)
{
    assert(g_txBclkFreq[instance] > 0U); /* Must be set via CLOCK_SetTxBclkFreq() */

    return g_txBclkFreq[instance];
}

static uint32_t CLOCK_GetSpdifRxFreq(void)
{
    assert(g_spdifRxFreq > 0U); /* Must be set via CLOCK_SetSpdifRxFreq() */

    return g_spdifRxFreq;
}

/*!
 * @brief Set the clock source for specific IP module.
 *
 * Set the clock source for specific IP, not all modules need to set the
 * clock source, should only use this function for the modules need source
 * setting.
 *
 * @param name Which peripheral to check, see \ref clock_ip_name_t.
 * @param src Clock source to set.
 */
void CLOCK_SetIpSrc(clock_ip_name_t name, clock_ip_src_t src)
{
    uint32_t reg;

    if (((uint32_t)name & IP_NAME_NON_PCC_FLAG_MASK) == 0UL)
    {
        /* PCC register */
        reg = PCC_REG(name);

        assert((reg & PCC_CLKCFG_PR_MASK) != 0UL);
        assert(0UL == (reg & PCC_CLKCFG_INUSE_MASK)); /* Should not change if clock has been enabled by other core. */

        if (((uint32_t)name & PCC_PCS_AVAIL_MASK) != 0UL)
        {
            /* Clear PCS */
            reg &= ~PCC_CLKCFG_PCS_MASK;
            switch (name)
            {
                case kCLOCK_Tpm2:
                    assert(CLOCK_IP_SOURCE_NON_PCC_INDEX_VAL(src) == 4U);
                    if (((uint32_t)src & 0x10U) == 0U)
                    {
                        /* Audio clock source */
                        CGC_RTD->TPM3_2CLK =
                            (CGC_RTD->TPM3_2CLK & ~CGC_TPM3_2CLK_TPM2CLK_MASK) | CGC_TPM3_2CLK_TPM2CLK(src);
                    }
                    else
                    {
                        /* PCC Async clock source */
                        CGC_RTD->TPM3_2CLK =
                            (CGC_RTD->TPM3_2CLK & ~CGC_TPM3_2CLK_TPM2CLK_MASK) | CGC_TPM3_2CLK_TPM2CLK(2U);
                        reg |= PCC_CLKCFG_PCS(src);
                    }
                    break;
                case kCLOCK_Tpm3:
                    assert(CLOCK_IP_SOURCE_NON_PCC_INDEX_VAL(src) == 5U);
                    if (((uint32_t)src & 0x10U) == 0U)
                    {
                        /* Audio clock source */
                        CGC_RTD->TPM3_2CLK =
                            (CGC_RTD->TPM3_2CLK & ~CGC_TPM3_2CLK_TPM3CLK_MASK) | CGC_TPM3_2CLK_TPM3CLK(src);
                    }
                    else
                    {
                        /* PCC Async clock source */
                        CGC_RTD->TPM3_2CLK =
                            (CGC_RTD->TPM3_2CLK & ~CGC_TPM3_2CLK_TPM3CLK_MASK) | CGC_TPM3_2CLK_TPM3CLK(3U);
                        reg |= PCC_CLKCFG_PCS(src);
                    }
                    break;
                case kCLOCK_Tpm6:
                    assert(CLOCK_IP_SOURCE_NON_PCC_INDEX_VAL(src) == 7U);
                    if (((uint32_t)src & 0x10U) == 0U)
                    {
                        /* Audio clock source */
                        CGC_AD->TPM6_7CLK =
                            (CGC_AD->TPM6_7CLK & ~CGC_AD_TPM6_7CLK_TPM6CLK_MASK) | CGC_AD_TPM6_7CLK_TPM6CLK(src);
                    }
                    else
                    {
                        /* PCC Async clock source */
                        CGC_AD->TPM6_7CLK =
                            (CGC_AD->TPM6_7CLK & ~CGC_AD_TPM6_7CLK_TPM6CLK_MASK) | CGC_AD_TPM6_7CLK_TPM6CLK(3U);
                        reg |= PCC_CLKCFG_PCS(src);
                    }
                    break;
                case kCLOCK_Tpm7:
                    assert(CLOCK_IP_SOURCE_NON_PCC_INDEX_VAL(src) == 7U);
                    if (((uint32_t)src & 0x10U) == 0U)
                    {
                        /* Audio clock source */
                        CGC_AD->TPM6_7CLK =
                            (CGC_AD->TPM6_7CLK & ~CGC_AD_TPM6_7CLK_TPM7CLK_MASK) | CGC_AD_TPM6_7CLK_TPM7CLK(src);
                    }
                    else
                    {
                        /* PCC Async clock source */
                        CGC_AD->TPM6_7CLK =
                            (CGC_AD->TPM6_7CLK & ~CGC_AD_TPM6_7CLK_TPM7CLK_MASK) | CGC_AD_TPM6_7CLK_TPM7CLK(3U);
                        reg |= PCC_CLKCFG_PCS(src);
                    }
                    break;
                case kCLOCK_Tpm8:
                    assert(CLOCK_IP_SOURCE_NON_PCC_INDEX_VAL(src) == 9U);
                    if (((uint32_t)src & 0x10U) == 0U)
                    {
                        /* Audio clock source */
                        CGC_LPAV->TPM8CLK =
                            (CGC_LPAV->TPM8CLK & ~CGC_LPAV_TPM8CLK_TPM8CLK_MASK) | CGC_LPAV_TPM8CLK_TPM8CLK(src);
                    }
                    else
                    {
                        /* PCC Async clock source */
                        CGC_LPAV->TPM8CLK =
                            (CGC_LPAV->TPM8CLK & ~CGC_LPAV_TPM8CLK_TPM8CLK_MASK) | CGC_LPAV_TPM8CLK_TPM8CLK(5U);
                        reg |= PCC_CLKCFG_PCS(src);
                    }
                    break;
                default:
                    assert((uint32_t)CLOCK_IP_SOURCE_PCC_INDEX_VAL(src) == CLOCK_GetPccInstance(name));
                    reg |= PCC_CLKCFG_PCS(src);
                    break;
            }

            /*
             * If clock is already enabled, first disable it, then set the clock
             * source and re-enable it.
             */
            PCC_REG(name) = reg & ~PCC_CLKCFG_CGC_MASK;
            PCC_REG(name) = reg;
        }
        else
        {
            switch (name)
            {
                case kCLOCK_Sai0:
                    /* Audio clock source */
                    assert(CLOCK_IP_SOURCE_NON_PCC_INDEX_VAL(src) == 1U);
                    CGC_RTD->SAI3_0_CLK =
                        (CGC_RTD->SAI3_0_CLK & ~CGC_SAI3_0_CLK_SAI0CLK_MASK) | CGC_SAI3_0_CLK_SAI0CLK(src);
                    break;
                case kCLOCK_Sai1:
                    /* Audio clock source */
                    assert(CLOCK_IP_SOURCE_NON_PCC_INDEX_VAL(src) == 1U);
                    CGC_RTD->SAI3_0_CLK =
                        (CGC_RTD->SAI3_0_CLK & ~CGC_SAI3_0_CLK_SAI1CLK_MASK) | CGC_SAI3_0_CLK_SAI1CLK(src);
                    break;
                case kCLOCK_Sai2:
                    /* Audio clock source */
                    assert(CLOCK_IP_SOURCE_NON_PCC_INDEX_VAL(src) == 2U);
                    CGC_RTD->SAI3_0_CLK =
                        (CGC_RTD->SAI3_0_CLK & ~CGC_SAI3_0_CLK_SAI2CLK_MASK) | CGC_SAI3_0_CLK_SAI2CLK(src);
                    break;
                case kCLOCK_Sai3:
                    /* Audio clock source */
                    assert(CLOCK_IP_SOURCE_NON_PCC_INDEX_VAL(src) == 2U);
                    CGC_RTD->SAI3_0_CLK =
                        (CGC_RTD->SAI3_0_CLK & ~CGC_SAI3_0_CLK_SAI3CLK_MASK) | CGC_SAI3_0_CLK_SAI3CLK(src);
                    break;
                case kCLOCK_Sai4:
                    /* Audio clock source */
                    assert(CLOCK_IP_SOURCE_NON_PCC_INDEX_VAL(src) == 6U);
                    CGC_AD->SAI5_4_CLK =
                        (CGC_AD->SAI5_4_CLK & ~CGC_AD_SAI5_4_CLK_SAI4CLK_MASK) | CGC_AD_SAI5_4_CLK_SAI4CLK(src);
                    break;
                case kCLOCK_Sai5:
                    /* Audio clock source */
                    assert(CLOCK_IP_SOURCE_NON_PCC_INDEX_VAL(src) == 6U);
                    CGC_AD->SAI5_4_CLK =
                        (CGC_AD->SAI5_4_CLK & ~CGC_AD_SAI5_4_CLK_SAI5CLK_MASK) | CGC_AD_SAI5_4_CLK_SAI5CLK(src);
                    break;
                case kCLOCK_Sai6:
                    /* Audio clock source */
                    assert(CLOCK_IP_SOURCE_NON_PCC_INDEX_VAL(src) == 8U);
                    CGC_LPAV->SAI7_6_CLK =
                        (CGC_LPAV->SAI7_6_CLK & ~CGC_LPAV_SAI7_6_CLK_SAI6CLK_MASK) | CGC_LPAV_SAI7_6_CLK_SAI6CLK(src);
                    break;
                case kCLOCK_Sai7:
                    /* Audio clock source */
                    assert(CLOCK_IP_SOURCE_NON_PCC_INDEX_VAL(src) == 8U);
                    CGC_LPAV->SAI7_6_CLK =
                        (CGC_LPAV->SAI7_6_CLK & ~CGC_LPAV_SAI7_6_CLK_SAI7CLK_MASK) | CGC_LPAV_SAI7_6_CLK_SAI7CLK(src);
                    break;

                case kCLOCK_Spdif:
                    /* Audio clock source */
                    assert(CLOCK_IP_SOURCE_NON_PCC_INDEX_VAL(src) == 8U);
                    CGC_LPAV->SPDIFCLK = CGC_LPAV_SPDIFCLK_SPDIFCLK(src);
                    break;
                case kCLOCK_Micfil:
                    assert(CLOCK_IP_SOURCE_NON_PCC_INDEX_VAL(src) == 3U);
                    CGC_RTD->EMICFIL = CGC_EMICFIL_MICFILCLK(src);
                    break;
                default:
                    assert(false);
                    break;
            }
        }
    }
    else
    {
        /* Non-PCC register */
        if (name == kCLOCK_Mqs0)
        {
            assert(CLOCK_IP_SOURCE_NON_PCC_INDEX_VAL(src) == 1U);
            CGC_RTD->MQS0CLK = CGC_MQS0CLK_MQS0CLK(src);
        }
        else if (name == kCLOCK_Mqs1)
        {
            assert(CLOCK_IP_SOURCE_NON_PCC_INDEX_VAL(src) == 6U);
            CGC_AD->MQS1CLK = CGC_AD_MQS1CLK_MQS1CLK(src);
        }
        else
        {
            assert(false);
        }
    }
}

/*!
 * @brief Set the clock source and divider for specific IP module.
 *
 * Set the clock source and divider for specific IP, not all modules need to
 * set the clock source and divider, should only use this function for the
 * modules need source and divider setting.
 *
 * Divider output clock = Divider input clock x [(fracValue+1)/(divValue+1)]).
 *
 * @param name Which peripheral to check, see \ref clock_ip_name_t.
 * @param src Clock source to set.
 * @param divValue  The divider value.
 * @param fracValue The fraction multiply value.
 */
void CLOCK_SetIpSrcDiv(clock_ip_name_t name, clock_ip_src_t src, uint8_t divValue, uint8_t fracValue)
{
    uint32_t reg = PCC_REG(name);

    assert(((uint32_t)name & IP_NAME_NON_PCC_FLAG_MASK) == 0UL);
    assert((reg & PCC_CLKCFG_PR_MASK) != 0UL);
    assert(((uint32_t)name & (PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK)) ==
           (PCC_PCS_AVAIL_MASK | PCC_PCD_FRAC_AVAIL_MASK));
    assert(0UL == (reg & PCC_CLKCFG_INUSE_MASK)); /* Should not change if clock has been enabled by other core. */
    assert(CLOCK_IP_SOURCE_PCC_INDEX_VAL(src) == CLOCK_GetPccInstance(name));

    reg = (reg & ~(PCC_CLKCFG_PCS_MASK | PCC_CLKCFG_FRAC_MASK | PCC_CLKCFG_PCD_MASK)) | PCC_CLKCFG_PCS(src) |
          PCC_CLKCFG_PCD(divValue) | PCC_CLKCFG_FRAC(fracValue);

    /*
     * If clock is already enabled, first disable it, then set the clock
     * source and re-enable it.
     */
    PCC_REG(name) = reg & ~PCC_CLKCFG_CGC_MASK;
    PCC_REG(name) = reg;
}

/*!
 * brief Get the external LVDS pad clock frequency (LVDS).
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetLvdsClkFreq(void)
{
    assert(g_lvdsFreq);
    return g_lvdsFreq;
}

/*!
 * brief Get the CM33 slow clock frequency.
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetCm33SlowClkFreq(void)
{
    return CLOCK_GetCm33SysClkFreq(kCGC_SysClkSlow);
}

/*!
 * brief Get the CM33 bus clock frequency.
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetCm33BusClkFreq(void)
{
    return CLOCK_GetCm33SysClkFreq(kCGC_SysClkBus);
}

/*!
 * brief Get the CM33 core/platform clock frequency.
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetCm33CorePlatClkFreq(void)
{
    return CLOCK_GetCm33SysClkFreq(kCGC_SysClkCorePlat);
}

/*!
 * brief Get the Fusion DSP slow clock frequency.
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetFusionDspSlowClkFreq(void)
{
    return CLOCK_GetFusionDspSysClkFreq(kCGC_SysClkSlow);
}

/*!
 * brief Get the Fusion DSP bus clock frequency.
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetFusionDspBusClkFreq(void)
{
    return CLOCK_GetFusionDspSysClkFreq(kCGC_SysClkBus);
}

/*!
 * brief Get the Fusion DSP core/platform clock frequency.
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetFusionDspCorePlatClkFreq(void)
{
    return CLOCK_GetFusionDspSysClkFreq(kCGC_SysClkCorePlat);
}

/*!
 * @brief Gets the CGC XBAR bus clock frequency in AD.
 *
 * This function gets the CGC XBAR bus clock frequency.
 *
 * @return  Clock frequency.
 */
uint32_t CLOCK_GetXbarBusClkFreq(void)
{
    uint32_t freq;
    uint32_t nicClk      = CGC_AD->NICCLK;
    uint32_t xbarClk     = CGC_AD->XBARCLK;
    uint32_t scs         = (nicClk & CGC_AD_NICCLK_SCS_MASK) >> CGC_AD_NICCLK_SCS_SHIFT;
    uint32_t divNicPlat  = (nicClk & CGC_AD_NICCLK_NIC_AD_DIVPLAT_MASK) >> CGC_AD_NICCLK_NIC_AD_DIVPLAT_SHIFT;
    uint32_t divXbarPlat = (xbarClk & CGC_AD_XBARCLK_XBAR_AD_DIVPLAT_MASK) >> CGC_AD_XBARCLK_XBAR_AD_DIVPLAT_SHIFT;
    uint32_t divXbarBus  = (xbarClk & CGC_AD_XBARCLK_XBAR_DIVBUS_MASK) >> CGC_AD_XBARCLK_XBAR_DIVBUS_SHIFT;

    switch (scs)
    {
        case (uint32_t)kCGC_NicSysClkSrcFro:
            freq = CLOCK_GetFroFreq();
            break;
        case (uint32_t)kCGC_NicSysClkSrcPll3Pfd0:
            freq = CLOCK_GetPll3PfdFreq(kCGC_PllPfd0Clk);
            break;
        case (uint32_t)kCGC_NicSysClkSrcSysOsc:
            freq = CLOCK_GetSysOscFreq();
            break;
        case (uint32_t)kCGC_NicSysClkSrcLvds:
            freq = CLOCK_GetLvdsClkFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    freq /= (divNicPlat + 1U) * (divXbarPlat + 1U) * (divXbarBus + 1U);

    return freq;
}

/*!
 * @brief Gets the CGC HIFI DSP system clock frequency in LPAV.
 *
 * This function gets the CGC HIFI DSP system clock frequency. These clocks are used for
 * core, platform domains.
 *
 * @param type     Which type of clock to get.
 * @return  Clock frequency.
 */
uint32_t CLOCK_GetHifiDspSysClkFreq(cgc_sys_clk_t type)
{
    uint32_t freq;
    uint32_t sysClkConfig              = 0U;
    cgc_hifi_sys_clk_config_t *pConfig = NULL;

    (void)memcpy((void *)&sysClkConfig, (void *)(uint8_t *)(uint32_t)(&CGC_LPAV->HIFICLK), sizeof(sysClkConfig));
    pConfig = (cgc_hifi_sys_clk_config_t *)(uint32_t)&sysClkConfig;
    switch (pConfig->src)
    {
        case (uint32_t)kCGC_HifiSysClkSrcFro:
            freq = CLOCK_GetFroFreq();
            break;
        case (uint32_t)kCGC_HifiSysClkSrcPll4:
            freq = CLOCK_GetPll4Freq();
            break;
        case (uint32_t)kCGC_HifiSysClkSrcPll4Pfd0:
            freq = CLOCK_GetPll4PfdFreq(kCGC_PllPfd0Clk);
            break;
        case (uint32_t)kCGC_HifiSysClkSrcSysOsc:
            freq = CLOCK_GetSysOscFreq();
            break;
        case (uint32_t)kCGC_HifiSysClkSrcLvds:
            freq = CLOCK_GetLvdsClkFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    freq /= (pConfig->divCore + 1U);

    if (kCGC_SysClkNicHifi == type)
    {
        freq /= (pConfig->divPlat + 1U);
    }
    else
    {
        assert(kCGC_SysClkHifi4 == type);
    }

    return freq;
}

/*!
 * @brief Gets the CGC NIC LPAV system clock frequency in LPAV.
 *
 * This function gets the CGC NIC LPAV system clock frequency. These clocks are used for
 * AXI, AHB, Bus domains.
 *
 * @param type     Which type of clock to get.
 * @return  Clock frequency.
 */
uint32_t CLOCK_GetLpavSysClkFreq(cgc_sys_clk_t type)
{
    uint32_t freq;
    uint32_t sysClkConfig              = 0U;
    cgc_lpav_sys_clk_config_t *pConfig = NULL;

    (void)memcpy((void *)&sysClkConfig, (void *)(uint8_t *)(uint32_t)(&CGC_LPAV->NICLPAVCLK), sizeof(sysClkConfig));
    pConfig = (cgc_lpav_sys_clk_config_t *)(uint32_t)&sysClkConfig;

    switch (pConfig->src)
    {
        case (uint32_t)kCGC_LpavSysClkSrcFro:
            freq = CLOCK_GetFroFreq();
            break;
        case (uint32_t)kCGC_LpavSysClkSrcPll4Pfd1:
            freq = CLOCK_GetPll4PfdFreq(kCGC_PllPfd1Clk);
            break;
        case (uint32_t)kCGC_LpavSysClkSrcSysOsc:
            freq = CLOCK_GetSysOscFreq();
            break;
        case (uint32_t)kCGC_LpavSysClkSrcLvds:
            freq = CLOCK_GetLvdsClkFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    freq /= (pConfig->divAxi + 1U);

    if (kCGC_SysClkLpavAhb == type)
    {
        freq /= (pConfig->divAhb + 1U);
    }
    else if (kCGC_SysClkLpavBus == type)
    {
        freq /= (pConfig->divBus + 1U);
    }
    else
    {
        assert(kCGC_SysClkLpavAxi == type);
    }

    return freq;
}

/*!
 * @brief Gets the CGC DDR clock frequency in LPAV.
 *
 * This function gets the CGC DDR clock frequency.
 *
 * @return  Clock frequency.
 */
uint32_t CLOCK_GetDdrClkFreq(void)
{
    uint32_t freq;
    uint32_t sysClkConfig             = 0U;
    cgc_ddr_sys_clk_config_t *pConfig = NULL;

    (void)memcpy((void *)&sysClkConfig, (void *)(uint8_t *)(uint32_t)(&CGC_LPAV->DDRCLK), sizeof(sysClkConfig));
    pConfig = (cgc_ddr_sys_clk_config_t *)(uint32_t)&sysClkConfig;

    /* TODO: 2 cascaded switches */
    switch (pConfig->src)
    {
        case (uint32_t)kCGC_DdrSysClkSrcFro:
            freq = CLOCK_GetFroFreq();
            break;
        case (uint32_t)kCGC_DdrSysClkSrcPll4Pfd1:
            freq = CLOCK_GetPll4PfdFreq(kCGC_PllPfd1Clk);
            break;
        case (uint32_t)kCGC_DdrSysClkSrcSysOsc:
            freq = CLOCK_GetSysOscFreq();
            break;
        case (uint32_t)kCGC_DdrSysClkSrcLvds:
            freq = CLOCK_GetLvdsClkFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    freq /= (pConfig->divDdr + 1U);

    return freq;
}

/*!
 * brief Gets the clock frequency for a specific clock name.
 *
 * This function checks the current clock configurations and then calculates
 * the clock frequency for a specific clock name defined in clock_name_t.
 *
 * param clockName Clock names defined in clock_name_t
 * return Clock frequency value in hertz
 */
uint32_t CLOCK_GetFreq(clock_name_t clockName)
{
    uint32_t freq;

    switch (clockName)
    {
        case kCLOCK_Cm33CorePlatClk:
            freq = CLOCK_GetCm33SysClkFreq(kCGC_SysClkCorePlat);
            break;
        case kCLOCK_Cm33BusClk:
            freq = CLOCK_GetCm33SysClkFreq(kCGC_SysClkBus);
            break;
        case kCLOCK_Cm33SlowClk:
            freq = CLOCK_GetCm33SysClkFreq(kCGC_SysClkSlow);
            break;
        case kCLOCK_FusionDspCorePlatClk:
            freq = CLOCK_GetFusionDspSysClkFreq(kCGC_SysClkCorePlat);
            break;
        case kCLOCK_FusionDspBusClk:
            freq = CLOCK_GetFusionDspSysClkFreq(kCGC_SysClkBus);
            break;
        case kCLOCK_FusionDspSlowClk:
            freq = CLOCK_GetFusionDspSysClkFreq(kCGC_SysClkSlow);
            break;

        case kCLOCK_XbarBusClk:
            freq = CLOCK_GetXbarBusClkFreq();
            break;

        case kCLOCK_HifiDspClk:
            freq = CLOCK_GetHifiDspSysClkFreq(kCGC_SysClkHifi4);
            break;
        case kCLOCK_HifiNicPlatClk:
            freq = CLOCK_GetHifiDspSysClkFreq(kCGC_SysClkNicHifi);
            break;
        case kCLOCK_NicLpavAxiClk:
            freq = CLOCK_GetLpavSysClkFreq(kCGC_SysClkLpavAxi);
            break;
        case kCLOCK_NicLpavAhbClk:
            freq = CLOCK_GetLpavSysClkFreq(kCGC_SysClkLpavAhb);
            break;
        case kCLOCK_NicLpavBusClk:
            freq = CLOCK_GetLpavSysClkFreq(kCGC_SysClkLpavBus);
            break;
        case kCLOCK_DdrClk:
            freq = CLOCK_GetDdrClkFreq();
            break;

        case kCLOCK_SysOscClk:
            freq = CLOCK_GetSysOscFreq();
            break;
        case kCLOCK_FroClk:
            freq = CLOCK_GetFroFreq();
            break;
        case kCLOCK_LpOscClk:
            freq = CLOCK_GetLpOscFreq();
            break;
        case kCLOCK_RtcOscClk:
            freq = CLOCK_GetRtcOscFreq();
            break;
        case kCLOCK_LvdsClk:
            freq = CLOCK_GetLvdsClkFreq();
            break;

        case kCLOCK_RtdSysOscDiv1Clk:
            freq = CLOCK_GetRtdSysOscAsyncFreq(kCGC_AsyncDiv1Clk);
            break;
        case kCLOCK_RtdSysOscDiv2Clk:
            freq = CLOCK_GetRtdSysOscAsyncFreq(kCGC_AsyncDiv2Clk);
            break;
        case kCLOCK_RtdSysOscDiv3Clk:
            freq = CLOCK_GetRtdSysOscAsyncFreq(kCGC_AsyncDiv3Clk);
            break;

        case kCLOCK_RtdFroDiv1Clk:
            freq = CLOCK_GetRtdFroAsyncFreq(kCGC_AsyncDiv1Clk);
            break;
        case kCLOCK_RtdFroDiv2Clk:
            freq = CLOCK_GetRtdFroAsyncFreq(kCGC_AsyncDiv2Clk);
            break;
        case kCLOCK_RtdFroDiv3Clk:
            freq = CLOCK_GetRtdFroAsyncFreq(kCGC_AsyncDiv3Clk);
            break;

        case kCLOCK_AdSysOscDiv1Clk:
            freq = CLOCK_GetAdSysOscAsyncFreq(kCGC_AsyncDiv1Clk);
            break;
        case kCLOCK_AdSysOscDiv2Clk:
            freq = CLOCK_GetAdSysOscAsyncFreq(kCGC_AsyncDiv2Clk);
            break;
        case kCLOCK_AdSysOscDiv3Clk:
            freq = CLOCK_GetAdSysOscAsyncFreq(kCGC_AsyncDiv3Clk);
            break;

        case kCLOCK_AdFroDiv1Clk:
            freq = CLOCK_GetAdFroAsyncFreq(kCGC_AsyncDiv1Clk);
            break;
        case kCLOCK_AdFroDiv2Clk:
            freq = CLOCK_GetAdFroAsyncFreq(kCGC_AsyncDiv2Clk);
            break;
        case kCLOCK_AdFroDiv3Clk:
            freq = CLOCK_GetAdFroAsyncFreq(kCGC_AsyncDiv3Clk);
            break;

        case kCLOCK_LpavSysOscDiv1Clk:
            freq = CLOCK_GetLpavSysOscAsyncFreq(kCGC_AsyncDiv1Clk);
            break;
        case kCLOCK_LpavSysOscDiv2Clk:
            freq = CLOCK_GetLpavSysOscAsyncFreq(kCGC_AsyncDiv2Clk);
            break;
        case kCLOCK_LpavSysOscDiv3Clk:
            freq = CLOCK_GetLpavSysOscAsyncFreq(kCGC_AsyncDiv3Clk);
            break;

        case kCLOCK_LpavFroDiv1Clk:
            freq = CLOCK_GetLpavFroAsyncFreq(kCGC_AsyncDiv1Clk);
            break;
        case kCLOCK_LpavFroDiv2Clk:
            freq = CLOCK_GetLpavFroAsyncFreq(kCGC_AsyncDiv2Clk);
            break;
        case kCLOCK_LpavFroDiv3Clk:
            freq = CLOCK_GetLpavFroAsyncFreq(kCGC_AsyncDiv3Clk);
            break;

        case kCLOCK_Pll0Clk:
            freq = CLOCK_GetPll0Freq();
            break;
        case kCLOCK_Pll1Clk:
            freq = CLOCK_GetPll1Freq();
            break;
        case kCLOCK_Pll3Clk:
            freq = CLOCK_GetPll3Freq();
            break;
        case kCLOCK_Pll4Clk:
            freq = CLOCK_GetPll4Freq();
            break;

        case kCLOCK_Pll0Pfd0Clk:
            freq = CLOCK_GetPll0PfdFreq(kCGC_PllPfd0Clk);
            break;
        case kCLOCK_Pll0Pfd1Clk:
            freq = CLOCK_GetPll0PfdFreq(kCGC_PllPfd1Clk);
            break;
        case kCLOCK_Pll0Pfd2Clk:
            freq = CLOCK_GetPll0PfdFreq(kCGC_PllPfd2Clk);
            break;
        case kCLOCK_Pll0Pfd3Clk:
            freq = CLOCK_GetPll0PfdFreq(kCGC_PllPfd3Clk);
            break;

        case kCLOCK_Pll1Pfd0Clk:
            freq = CLOCK_GetPll1PfdFreq(kCGC_PllPfd0Clk);
            break;
        case kCLOCK_Pll1Pfd1Clk:
            freq = CLOCK_GetPll1PfdFreq(kCGC_PllPfd1Clk);
            break;
        case kCLOCK_Pll1Pfd2Clk:
            freq = CLOCK_GetPll1PfdFreq(kCGC_PllPfd2Clk);
            break;
        case kCLOCK_Pll1Pfd3Clk:
            freq = CLOCK_GetPll1PfdFreq(kCGC_PllPfd3Clk);
            break;

        case kCLOCK_Pll3Pfd0Clk:
            freq = CLOCK_GetPll3PfdFreq(kCGC_PllPfd0Clk);
            break;
        case kCLOCK_Pll3Pfd1Clk:
            freq = CLOCK_GetPll3PfdFreq(kCGC_PllPfd1Clk);
            break;
        case kCLOCK_Pll3Pfd2Clk:
            freq = CLOCK_GetPll3PfdFreq(kCGC_PllPfd2Clk);
            break;
        case kCLOCK_Pll3Pfd3Clk:
            freq = CLOCK_GetPll3PfdFreq(kCGC_PllPfd3Clk);
            break;

        case kCLOCK_Pll4Pfd0Clk:
            freq = CLOCK_GetPll4PfdFreq(kCGC_PllPfd0Clk);
            break;
        case kCLOCK_Pll4Pfd1Clk:
            freq = CLOCK_GetPll4PfdFreq(kCGC_PllPfd1Clk);
            break;
        case kCLOCK_Pll4Pfd2Clk:
            freq = CLOCK_GetPll4PfdFreq(kCGC_PllPfd2Clk);
            break;
        case kCLOCK_Pll4Pfd3Clk:
            freq = CLOCK_GetPll4PfdFreq(kCGC_PllPfd3Clk);
            break;

        case kCLOCK_Pll0VcoDivClk:
            freq = CLOCK_GetPll0AsyncFreq(kCGC_AsyncVcoClk);
            break;
        case kCLOCK_Pll0Pfd1DivClk:
            freq = CLOCK_GetPll0AsyncFreq(kCGC_AsyncPfd1Div1Clk);
            break;
        case kCLOCK_Pll0Pfd2DivClk:
            freq = CLOCK_GetPll0AsyncFreq(kCGC_AsyncPfd2Div1Clk);
            break;

        case kCLOCK_Pll1VcoDivClk:
            freq = CLOCK_GetPll1AsyncFreq(kCGC_AsyncVcoClk);
            break;
        case kCLOCK_Pll1Pfd1DivClk:
            freq = CLOCK_GetPll1AsyncFreq(kCGC_AsyncPfd1Div1Clk);
            break;
        case kCLOCK_Pll1Pfd2DivClk:
            freq = CLOCK_GetPll1AsyncFreq(kCGC_AsyncPfd2Div1Clk);
            break;

        case kCLOCK_Pll3VcoDivClk:
            freq = CLOCK_GetPll3AsyncFreq(kCGC_AsyncVcoClk);
            break;
        case kCLOCK_Pll3Pfd0Div1Clk:
            freq = CLOCK_GetPll3AsyncFreq(kCGC_AsyncPfd0Div1Clk);
            break;
        case kCLOCK_Pll3Pfd0Div2Clk:
            freq = CLOCK_GetPll3AsyncFreq(kCGC_AsyncPfd0Div2Clk);
            break;
        case kCLOCK_Pll3Pfd1Div1Clk:
            freq = CLOCK_GetPll3AsyncFreq(kCGC_AsyncPfd1Div1Clk);
            break;
        case kCLOCK_Pll3Pfd1Div2Clk:
            freq = CLOCK_GetPll3AsyncFreq(kCGC_AsyncPfd1Div2Clk);
            break;
        case kCLOCK_Pll3Pfd2Div1Clk:
            freq = CLOCK_GetPll3AsyncFreq(kCGC_AsyncPfd2Div1Clk);
            break;
        case kCLOCK_Pll3Pfd2Div2Clk:
            freq = CLOCK_GetPll3AsyncFreq(kCGC_AsyncPfd2Div2Clk);
            break;
        case kCLOCK_Pll3Pfd3Div1Clk:
            freq = CLOCK_GetPll3AsyncFreq(kCGC_AsyncPfd3Div1Clk);
            break;
        case kCLOCK_Pll3Pfd3Div2Clk:
            freq = CLOCK_GetPll3AsyncFreq(kCGC_AsyncPfd3Div2Clk);
            break;

        case kCLOCK_Pll4VcoDivClk:
            freq = CLOCK_GetPll4AsyncFreq(kCGC_AsyncVcoClk);
            break;
        case kCLOCK_Pll4Pfd0Div1Clk:
            freq = CLOCK_GetPll4AsyncFreq(kCGC_AsyncPfd0Div1Clk);
            break;
        case kCLOCK_Pll4Pfd0Div2Clk:
            freq = CLOCK_GetPll4AsyncFreq(kCGC_AsyncPfd0Div2Clk);
            break;
        case kCLOCK_Pll4Pfd1Div1Clk:
            freq = CLOCK_GetPll4AsyncFreq(kCGC_AsyncPfd1Div1Clk);
            break;
        case kCLOCK_Pll4Pfd1Div2Clk:
            freq = CLOCK_GetPll4AsyncFreq(kCGC_AsyncPfd1Div2Clk);
            break;
        case kCLOCK_Pll4Pfd2Div1Clk:
            freq = CLOCK_GetPll4AsyncFreq(kCGC_AsyncPfd2Div1Clk);
            break;
        case kCLOCK_Pll4Pfd2Div2Clk:
            freq = CLOCK_GetPll4AsyncFreq(kCGC_AsyncPfd2Div2Clk);
            break;
        case kCLOCK_Pll4Pfd3Div1Clk:
            freq = CLOCK_GetPll4AsyncFreq(kCGC_AsyncPfd3Div1Clk);
            break;
        case kCLOCK_Pll4Pfd3Div2Clk:
            freq = CLOCK_GetPll4AsyncFreq(kCGC_AsyncPfd3Div2Clk);
            break;
        default:
            freq = 0U;
            break;
    }
    return freq;
}

static uint32_t CLOCK_GetPcc0PlatFreq(uint32_t pcs)
{
    uint32_t freq;

    switch (pcs)
    {
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc0PlatIpSrcSysOscDiv1):
            freq = CLOCK_GetRtdSysOscAsyncFreq(kCGC_AsyncDiv1Clk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc0PlatIpSrcFroDiv1):
            freq = CLOCK_GetRtdFroAsyncFreq(kCGC_AsyncDiv1Clk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc0PlatIpSrcCm33Plat):
            freq = CLOCK_GetCm33CorePlatClkFreq();
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc0PlatIpSrcFro):
            freq = CLOCK_GetFroFreq();
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc0PlatIpSrcPll0Pfd3):
            freq = CLOCK_GetPll0PfdFreq(kCGC_PllPfd3Clk);
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

static uint32_t CLOCK_GetPcc0BusFreq(uint32_t pcs)
{
    uint32_t freq;

    switch (pcs)
    {
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc0BusIpSrcLpo):
            freq = CLOCK_GetLpOscFreq();
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc0BusIpSrcSysOscDiv2):
            freq = CLOCK_GetRtdSysOscAsyncFreq(kCGC_AsyncDiv2Clk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc0BusIpSrcFroDiv2):
            freq = CLOCK_GetRtdFroAsyncFreq(kCGC_AsyncDiv2Clk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc0BusIpSrcCm33Bus):
            freq = CLOCK_GetCm33BusClkFreq();
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc0BusIpSrcPll1Pfd1Div):
            freq = CLOCK_GetPll1AsyncFreq(kCGC_AsyncPfd1Div1Clk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc0BusIpSrcPll0Pfd2Div):
            freq = CLOCK_GetPll0AsyncFreq(kCGC_AsyncPfd2Div1Clk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc0BusIpSrcPll0Pfd1Div):
            freq = CLOCK_GetPll0AsyncFreq(kCGC_AsyncPfd1Div1Clk);
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

static uint32_t CLOCK_GetPcc1PlatFreq(uint32_t pcs)
{
    return CLOCK_GetPcc0PlatFreq(pcs);
}

static uint32_t CLOCK_GetPcc1BusFreq(uint32_t pcs)
{
    uint32_t freq;

    if (pcs == (uint32_t)kCLOCK_Pcc1BusIpSrcPll1VcoDiv)
    {
        freq = CLOCK_GetPll1AsyncFreq(kCGC_AsyncVcoClk);
    }
    else
    {
        freq = CLOCK_GetPcc0BusFreq(pcs);
    }

    return freq;
}

static uint32_t CLOCK_GetPcc2BusFreq(uint32_t pcs)
{
    uint32_t freq;

    switch (pcs)
    {
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc2BusIpSrcLpo):
            freq = CLOCK_GetLpOscFreq();
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc2BusIpSrcSysOscDiv3):
            freq = CLOCK_GetRtdSysOscAsyncFreq(kCGC_AsyncDiv3Clk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc2BusIpSrcFroDiv3):
            freq = CLOCK_GetRtdFroAsyncFreq(kCGC_AsyncDiv3Clk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc2BusIpSrcFusionDspBus):
            freq = CLOCK_GetFusionDspBusClkFreq();
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc2BusIpSrcPll1VcoDiv):
            freq = CLOCK_GetPll1AsyncFreq(kCGC_AsyncVcoClk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc2BusIpSrcPll0Pfd2Div):
            freq = CLOCK_GetPll0AsyncFreq(kCGC_AsyncPfd2Div1Clk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc2BusIpSrcPll0Pfd1Div):
            freq = CLOCK_GetPll0AsyncFreq(kCGC_AsyncPfd1Div1Clk);
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

static uint32_t CLOCK_GetPcc3BusFreq(uint32_t pcs)
{
    uint32_t freq;

    switch (pcs)
    {
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc3BusIpSrcLpo):
            freq = CLOCK_GetLpOscFreq();
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc3BusIpSrcSysOscDiv2):
            freq = CLOCK_GetAdSysOscAsyncFreq(kCGC_AsyncDiv2Clk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc3BusIpSrcFroDiv2):
            freq = CLOCK_GetAdFroAsyncFreq(kCGC_AsyncDiv2Clk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc3BusIpSrcXbarBus):
            freq = CLOCK_GetXbarBusClkFreq();
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc3BusIpSrcPll3Pfd1Div1):
            freq = CLOCK_GetPll3AsyncFreq(kCGC_AsyncPfd1Div1Clk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc3BusIpSrcPll3Pfd0Div2):
            freq = CLOCK_GetPll3AsyncFreq(kCGC_AsyncPfd0Div2Clk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc3BusIpSrcPll3Pfd0Div1):
            freq = CLOCK_GetPll3AsyncFreq(kCGC_AsyncPfd0Div1Clk);
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

static uint32_t CLOCK_GetPcc4PlatFreq(uint32_t pcs)
{
    uint32_t freq;

    switch (pcs)
    {
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc4PlatIpSrcSysOscDiv1):
            freq = CLOCK_GetAdSysOscAsyncFreq(kCGC_AsyncDiv1Clk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc4PlatIpSrcFroDiv1):
            freq = CLOCK_GetAdFroAsyncFreq(kCGC_AsyncDiv1Clk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc4PlatIpSrcPll3Pfd3Div2):
            freq = CLOCK_GetPll3AsyncFreq(kCGC_AsyncPfd3Div2Clk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc4PlatIpSrcPll3Pfd3Div1):
            freq = CLOCK_GetPll3AsyncFreq(kCGC_AsyncPfd3Div1Clk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc4PlatIpSrcPll3Pfd2Div2):
            freq = CLOCK_GetPll3AsyncFreq(kCGC_AsyncPfd2Div2Clk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc4PlatIpSrcPll3Pfd2Div1):
            freq = CLOCK_GetPll3AsyncFreq(kCGC_AsyncPfd2Div1Clk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc4PlatIpSrcPll3Pfd1Div2):
            freq = CLOCK_GetPll3AsyncFreq(kCGC_AsyncPfd1Div2Clk);
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

static uint32_t CLOCK_GetPcc4BusFreq(uint32_t pcs)
{
    uint32_t freq;

    switch (pcs)
    {
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc4BusIpSrcLpo):
            freq = CLOCK_GetLpOscFreq();
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc4BusIpSrcSysOscDiv2):
            freq = CLOCK_GetAdSysOscAsyncFreq(kCGC_AsyncDiv2Clk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc4BusIpSrcFroDiv2):
            freq = CLOCK_GetAdFroAsyncFreq(kCGC_AsyncDiv2Clk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc4BusIpSrcXbarBus):
            freq = CLOCK_GetXbarBusClkFreq();
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc4BusIpSrcPll3VcoDiv):
            freq = CLOCK_GetPll3AsyncFreq(kCGC_AsyncVcoClk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc4BusIpSrcPll3Pfd0Div1):
            freq = CLOCK_GetPll3AsyncFreq(kCGC_AsyncPfd0Div1Clk);
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

static uint32_t CLOCK_GetPcc5PlatFreq(uint32_t pcs)
{
    uint32_t freq;

    switch (pcs)
    {
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc5PlatIpSrcPll4Pfd3Div2):
            freq = CLOCK_GetPll4AsyncFreq(kCGC_AsyncPfd3Div2Clk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc5PlatIpSrcPll4Pfd2Div2):
            freq = CLOCK_GetPll4AsyncFreq(kCGC_AsyncPfd2Div2Clk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc5PlatIpSrcPll4Pfd2Div1):
            freq = CLOCK_GetPll4AsyncFreq(kCGC_AsyncPfd2Div1Clk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc5PlatIpSrcPll4Pfd1Div2):
            freq = CLOCK_GetPll4AsyncFreq(kCGC_AsyncPfd1Div2Clk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc5PlatIpSrcPll4Pfd1Div1):
            freq = CLOCK_GetPll4AsyncFreq(kCGC_AsyncPfd1Div1Clk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc5PlatIpSrcPll4Pfd0Div2):
            freq = CLOCK_GetPll4AsyncFreq(kCGC_AsyncPfd0Div2Clk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc5PlatIpSrcPll4Pfd0Div1):
            freq = CLOCK_GetPll4AsyncFreq(kCGC_AsyncPfd0Div1Clk);
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

static uint32_t CLOCK_GetPcc5BusFreq(uint32_t pcs)
{
    uint32_t freq;

    switch (pcs)
    {
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc5BusIpSrcLpo):
            freq = CLOCK_GetLpOscFreq();
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc5BusIpSrcSysOscDiv2):
            freq = CLOCK_GetLpavSysOscAsyncFreq(kCGC_AsyncDiv2Clk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc5BusIpSrcFroDiv2):
            freq = CLOCK_GetLpavFroAsyncFreq(kCGC_AsyncDiv2Clk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc5BusIpSrcLpavBus):
            freq = CLOCK_GetLpavSysClkFreq(kCGC_SysClkLpavBus);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc5BusIpSrcPll4VcoDiv):
            freq = CLOCK_GetPll4AsyncFreq(kCGC_AsyncVcoClk);
            break;
        case CLOCK_IP_SRC_PCC_PCS(kCLOCK_Pcc5BusIpSrcPll4Pfd3Div1):
            freq = CLOCK_GetPll4AsyncFreq(kCGC_AsyncPfd3Div1Clk);
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

static uint32_t CLOCK_GetPccFreq(uint32_t pccInst, clock_ip_name_t name, uint32_t reg)
{
    uint32_t freq = 0U;

    switch (pccInst)
    {
        case 0:
        case 1:
            switch (name)
            {
                case kCLOCK_Wdog0:
                case kCLOCK_Wdog1:
                case kCLOCK_Lpit0:
                case kCLOCK_Flexio0:
                case kCLOCK_I3c0:
                case kCLOCK_Lpspi0:
                case kCLOCK_Lpspi1:
                case kCLOCK_Adc0:
                case kCLOCK_Adc1:
                case kCLOCK_Dac0:
                case kCLOCK_Dac1:
                case kCLOCK_SentinelLpuart:
                case kCLOCK_PowersysWdog:
                case kCLOCK_Tpm0:
                case kCLOCK_Tpm1:
                case kCLOCK_Lpi2c0:
                case kCLOCK_Lpi2c1:
                case kCLOCK_Lpuart0:
                case kCLOCK_Lpuart1:
                case kCLOCK_Flexcan:
                    freq = (pccInst == 0U) ? CLOCK_GetPcc0BusFreq(PCC_PCS_VAL(reg)) :
                                             CLOCK_GetPcc1BusFreq(PCC_PCS_VAL(reg));
                    break;
                case kCLOCK_Flexspi0:
                case kCLOCK_Flexspi1:
                case kCLOCK_Tpiu:
                case kCLOCK_Swo:
                    /* PCC0/PCC1 has same platform PCC selection. */
                    freq = CLOCK_GetPcc0PlatFreq(PCC_PCS_VAL(reg));
                    break;
                default:
                    assert(false);
                    break;
            }
            break;
        case 2:
            switch (name)
            {
                case kCLOCK_Wdog2:
                case kCLOCK_Tpm2:
                case kCLOCK_Tpm3:
                case kCLOCK_Lpi2c2:
                case kCLOCK_Lpi2c3:
                case kCLOCK_I3c1:
                case kCLOCK_Lpuart2:
                case kCLOCK_Lpuart3:
                case kCLOCK_Lpspi2:
                case kCLOCK_Lpspi3:
                    freq = CLOCK_GetPcc2BusFreq(PCC_PCS_VAL(reg));
                    break;
                default:
                    assert(false);
                    break;
            }
            break;
        case 3:
            switch (name)
            {
                case kCLOCK_Wdog3:
                case kCLOCK_Wdog4:
                case kCLOCK_Lpit1:
                case kCLOCK_Tpm4:
                case kCLOCK_Tpm5:
                case kCLOCK_Flexio1:
                case kCLOCK_I3c2:
                case kCLOCK_Lpi2c4:
                case kCLOCK_Lpi2c5:
                case kCLOCK_Lpuart4:
                case kCLOCK_Lpuart5:
                case kCLOCK_Lpspi4:
                case kCLOCK_Lpspi5:
                    freq = CLOCK_GetPcc3BusFreq(PCC_PCS_VAL(reg));
                    break;
                default:
                    assert(false);
                    break;
            }
            break;
        case 4:
            switch (name)
            {
                case kCLOCK_Tpm6:
                case kCLOCK_Tpm7:
                case kCLOCK_Lpi2c6:
                case kCLOCK_Lpi2c7:
                case kCLOCK_Lpuart6:
                case kCLOCK_Lpuart7:
                    freq = CLOCK_GetPcc4BusFreq(PCC_PCS_VAL(reg));
                    break;
                case kCLOCK_Flexspi2:
                case kCLOCK_Usdhc0:
                case kCLOCK_Usdhc1:
                case kCLOCK_Usdhc2:
                    freq = CLOCK_GetPcc4PlatFreq(PCC_PCS_VAL(reg));
                    break;
                default:
                    assert(false);
                    break;
            }
            break;
        case 5:
            switch (name)
            {
                case kCLOCK_Tpm8:
                case kCLOCK_Wdog5:
                    freq = CLOCK_GetPcc5BusFreq(PCC_PCS_VAL(reg));
                    break;
                case kCLOCK_Csi:
                case kCLOCK_Dsi:
                case kCLOCK_Epdc:
                case kCLOCK_Gpu2d:
                case kCLOCK_Gpu3d:
                case kCLOCK_Dcnano:
                case kCLOCK_CsiClkUi:
                case kCLOCK_CsiClkEsc:
                    freq = CLOCK_GetPcc5PlatFreq(PCC_PCS_VAL(reg));
                    break;
                default:
                    assert(false);
                    break;
            }
            break;
        default:
            assert(false); /* Not supported */
            break;
    }

    return freq * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
}

/* Function Name : CLOCK_GetIpFreq */
/*!
 * brief Gets the clock frequency for a specific IP module.
 *
 * This function gets the IP module clock frequency. It is only used for the IP
 * modules which could select clock source by CLOCK_SetIpSrc().
 *
 * param name Which peripheral to get, see \ref clock_ip_name_t.
 * return Clock frequency value in hertz
 */
uint32_t CLOCK_GetIpFreq(clock_ip_name_t name)
{
    uint32_t reg;
    uint32_t freq = 0U;
    uint32_t pccIns;

    if (((uint32_t)name & IP_NAME_NON_PCC_FLAG_MASK) == 0UL)
    {
        /* PCC register */
        reg = PCC_REG(name);

        assert((reg & PCC_CLKCFG_PR_MASK) != 0UL);

        if (((uint32_t)name & PCC_PCS_AVAIL_MASK) != 0UL)
        {
            switch (name)
            {
                /* Special case TPM2/3/6/7/8 */
                case kCLOCK_Tpm2:
                    freq = CLOCK_GetTpmClkFreq(2);
                    break;
                case kCLOCK_Tpm3:
                    freq = CLOCK_GetTpmClkFreq(3);
                    break;
                case kCLOCK_Tpm6:
                    freq = CLOCK_GetTpmClkFreq(6);
                    break;
                case kCLOCK_Tpm7:
                    freq = CLOCK_GetTpmClkFreq(7);
                    break;
                case kCLOCK_Tpm8:
                    freq = CLOCK_GetTpmClkFreq(8);
                    break;
                default:
                    pccIns = CLOCK_GetPccInstance(name);
                    freq   = CLOCK_GetPccFreq(pccIns, name, reg);
                    break;
            }
        }
        else /* No PCS */
        {
            switch (name)
            {
                case kCLOCK_Sai0:
                    freq = CLOCK_GetSaiFreq(0);
                    break;
                case kCLOCK_Sai1:
                    freq = CLOCK_GetSaiFreq(1);
                    break;
                case kCLOCK_Sai2:
                    freq = CLOCK_GetSaiFreq(2);
                    break;
                case kCLOCK_Sai3:
                    freq = CLOCK_GetSaiFreq(3);
                    break;
                case kCLOCK_Sai4:
                    freq = CLOCK_GetSaiFreq(4);
                    break;
                case kCLOCK_Sai5:
                    freq = CLOCK_GetSaiFreq(5);
                    break;
                case kCLOCK_Sai6:
                    freq = CLOCK_GetSaiFreq(6);
                    break;
                case kCLOCK_Sai7:
                    freq = CLOCK_GetSaiFreq(7);
                    break;

                case kCLOCK_Spdif:
                    freq = CLOCK_GetSpdifFreq();
                    break;
                case kCLOCK_Micfil:
                    freq = CLOCK_GetMicfilFreq();
                    break;
                case kCLOCK_Mrt:
                    freq = CLOCK_GetMrtFreq();
                    break;
                default:
                    assert(false);
                    freq = 0U;
                    break;
            }
        }
    }
    else /* Non-PCC IP */
    {
        if (name == kCLOCK_Mqs0)
        {
            freq = CLOCK_GetMqsFreq(0);
        }
        else if (name == kCLOCK_Mqs1)
        {
            freq = CLOCK_GetMqsFreq(1);
        }
        else
        {
            assert(false);
        }
    }

    return freq;
}

/*!
 * @brief Gets the CGC system clock frequency in RTD.
 *
 * This function gets the CGC system clock frequency. These clocks are used for
 * core, platform, bus and slow clock domains.
 *
 * @param config   Config value from CGC register.
 * @param type     Which type of clock to get.
 * @return  Clock frequency.
 */
uint32_t CLOCK_GetRtdSysClkFreq(uint32_t config, cgc_sys_clk_t type)
{
    uint32_t freq;
    cgc_rtd_sys_clk_config_t *pConfig = NULL;
    uint32_t sysClkConfig = 0U;

    (void)memcpy((void *)&sysClkConfig, (void *)&config, sizeof(config));
    pConfig = (cgc_rtd_sys_clk_config_t *)(uint32_t)&sysClkConfig;

    switch (pConfig->src)
    {
        case (uint32_t)kCGC_RtdSysClkSrcFro:
            freq = CLOCK_GetFroFreq();
            break;
        case (uint32_t)kCGC_RtdSysClkSrcPll0Pfd0:
            freq = CLOCK_GetPll0PfdFreq(kCGC_PllPfd0Clk);
            break;
        case (uint32_t)kCGC_RtdSysClkSrcPll1Pfd0:
            freq = CLOCK_GetPll1PfdFreq(kCGC_PllPfd0Clk);
            break;
        case (uint32_t)kCGC_RtdSysClkSrcSysOsc:
            freq = CLOCK_GetSysOscFreq();
            break;
        case (uint32_t)kCGC_RtdSysClkSrcRtcOsc:
            freq = CLOCK_GetRtcOscFreq();
            break;
        case (uint32_t)kCGC_RtdSysClkSrcLvds:
            freq = CLOCK_GetLvdsClkFreq();
            break;
        case (uint32_t)kCGC_RtdSysClkSrcPll0:
            freq = CLOCK_GetPll0Freq();
            break;
        default:
            freq = 0U;
            break;
    }

    freq /= (pConfig->divCore + 1U);

    if (kCGC_SysClkSlow == type)
    {
        freq /= (pConfig->divSlow + 1U);
    }
    else if (kCGC_SysClkBus == type)
    {
        freq /= (pConfig->divBus + 1U);
    }
    else
    {
        assert(kCGC_SysClkCorePlat == type);
    }

    return freq;
}

/*!
 * @brief Gets the CGC CM33 system clock frequency.
 *
 * This function gets the CGC CM33 system clock frequency. These clocks are used for
 * core, platform, bus and slow clock domains.
 *
 * @param type     Which type of clock to get.
 * @return  Clock frequency.
 */
uint32_t CLOCK_GetCm33SysClkFreq(cgc_sys_clk_t type)
{
    return CLOCK_GetRtdSysClkFreq(CGC_RTD->CM33CLK, type);
}

/*!
 * @brief Gets the CGC Fusion DSP system clock frequency.
 *
 * This function gets the CGC Fusion DSP system clock frequency. These clocks are used for
 * core, platform, bus and slow clock domains.
 *
 * @param type     Which type of clock to get.
 * @return  Clock frequency.
 */
uint32_t CLOCK_GetFusionDspSysClkFreq(cgc_sys_clk_t type)
{
    return CLOCK_GetRtdSysClkFreq(CGC_RTD->FUSIONCLK, type);
}

/*!
 * brief Initializes the CGC system OSC.
 *
 * This function enables the CGC system OSC clock according to the
 * configuration.
 *
 * param config   Pointer to the configuration structure.
 * retval kStatus_Success System OSC is initialized.
 * retval kStatus_CGC_Busy System OSC has been enabled and is used by the system clock.
 * retval kStatus_ReadOnly System OSC control register is locked.
 *
 * note This function can't detect whether the system OSC has been enabled and
 * used by an IP.
 */
status_t CLOCK_InitSysOsc(const cgc_sosc_config_t *config)
{
    status_t status;

    assert(config);

    /* De-init the SOSC first. */
    status = CLOCK_DeinitSysOsc();

    if (kStatus_Success != status)
    {
        return status;
    }

    /* Now start to set up OSC clock. */
    /* Step 1. Set OSC configuration. */
    CGC_RTD->SOSCCFG = (uint32_t)(config->workMode);

    /* Step 2. Enable clock. */
    CGC_RTD->SOSCCSR = (uint32_t)CGC_SOSCCSR_SOSCEN_MASK | (config->enableMode);

    /* Step 3. Wait for OSC clock to be valid. */
    while (0UL == (CGC_RTD->SOSCCSR & CGC_SOSCCSR_SOSCVLD_MASK))
    {
    }

    /* Step 4. Enabe monitor. */
    CGC_RTD->SOSCCSR |= (uint32_t)config->monitorMode;

    return kStatus_Success;
}

/*!
 * brief De-initializes the CGC system OSC.
 *
 * This function disables the CGC system OSC clock.
 *
 * retval kStatus_Success System OSC is deinitialized.
 * retval kStatus_CGC_Busy System OSC is used by the system clock.
 * retval kStatus_ReadOnly System OSC control register is locked.
 *
 * note This function can't detect whether the system OSC is used by an IP.
 */
status_t CLOCK_DeinitSysOsc(void)
{
    uint32_t reg = CGC_RTD->SOSCCSR;
    status_t status;

    /* If clock is used by system, return error. */
    if ((reg & CGC_SOSCCSR_SOSCSEL_MASK) != 0UL)
    {
        status = kStatus_CGC_Busy;
    }
    /* If configure register is locked, return error. */
    else if ((reg & CGC_SOSCCSR_LK_MASK) != 0UL)
    {
        status = kStatus_ReadOnly;
    }
    else
    {
        CGC_RTD->SOSCCSR = CGC_SOSCCSR_SOSCERR_MASK;
        status           = kStatus_Success;
    }

    return status;
}

static void CLOCK_SetSysOscAsyncClkDiv(volatile uint32_t *pReg, cgc_async_clk_t asyncClk, uint8_t divider)
{
    uint32_t reg = *pReg;

    switch (asyncClk)
    {
        case kCGC_AsyncDiv3Clk:
            reg = (reg & ~(CGC_SOSCDIV_DIV3_MASK | CGC_SOSCDIV_DIV3HALT_MASK)) |
                  (divider > 0U ? CGC_SOSCDIV_DIV3((uint32_t)divider - 1U) : CGC_SOSCDIV_DIV3HALT_MASK);
            break;
        case kCGC_AsyncDiv2Clk:
            reg = (reg & ~(CGC_SOSCDIV_DIV2_MASK | CGC_SOSCDIV_DIV2HALT_MASK)) |
                  (divider > 0U ? CGC_SOSCDIV_DIV2((uint32_t)divider - 1U) : CGC_SOSCDIV_DIV2HALT_MASK);
            break;
        case kCGC_AsyncDiv1Clk:
            reg = (reg & ~(CGC_SOSCDIV_DIV1_MASK | CGC_SOSCDIV_DIV1HALT_MASK)) |
                  (divider > 0U ? CGC_SOSCDIV_DIV1((uint32_t)divider - 1U) : CGC_SOSCDIV_DIV1HALT_MASK);
            break;
        default:
            assert(false);
            break;
    }

    *pReg = reg;
}

/*!
 * @brief Set the asynchronous clock divider in RTD.
 *
 * @param asyncClk Which asynchronous clock to configure.
 * @param divider The divider value to set. Disabled when divider == 0.
 *
 * @note There might be glitch when changing the asynchronous divider, so make sure
 * the asynchronous clock is not used while changing divider.
 */
void CLOCK_SetRtdSysOscAsyncClkDiv(cgc_async_clk_t asyncClk, uint8_t divider)
{
    CLOCK_SetSysOscAsyncClkDiv(&CGC_RTD->SOSCDIV, asyncClk, divider);
}

/*!
 * @brief Set the asynchronous clock divider in AD.
 *
 * @param asyncClk Which asynchronous clock to configure.
 * @param divider The divider value to set. Disabled when divider == 0.
 *
 * @note There might be glitch when changing the asynchronous divider, so make sure
 * the asynchronous clock is not used while changing divider.
 */
void CLOCK_SetAdSysOscAsyncClkDiv(cgc_async_clk_t asyncClk, uint8_t divider)
{
    CLOCK_SetSysOscAsyncClkDiv(&CGC_AD->SOSCDIV, asyncClk, divider);
}

/*!
 * @brief Set the asynchronous clock divider in LPAV.
 *
 * @param asyncClk Which asynchronous clock to configure.
 * @param divider The divider value to set. Disabled when divider == 0.
 *
 * @note There might be glitch when changing the asynchronous divider, so make sure
 * the asynchronous clock is not used while changing divider.
 */
void CLOCK_SetLpavSysOscAsyncClkDiv(cgc_async_clk_t asyncClk, uint8_t divider)
{
    CLOCK_SetSysOscAsyncClkDiv(&CGC_LPAV->SOSCDIV, asyncClk, divider);
}

/*!
 * brief Gets the CGC system OSC clock frequency (SYSOSC).
 *
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetSysOscFreq(void)
{
    uint32_t freq;

    if ((CGC_RTD->SOSCCSR & CGC_SOSCCSR_SOSCVLD_MASK) != 0UL) /* System OSC clock is valid. */
    {
        /* Please call CLOCK_SetXtal0Freq base on board setting before using OSC0 clock. */
        assert(g_xtal0Freq);
        freq = g_xtal0Freq;
    }
    else
    {
        freq = 0U;
    }

    return freq;
}

static uint32_t CLOCK_GetSysOscAsyncFreq(uint32_t reg, cgc_async_clk_t type)
{
    uint32_t oscFreq = CLOCK_GetSysOscFreq();
    uint32_t divider = 0U;
    uint32_t freq;

    /* Get divider. */
    if (oscFreq != 0UL)
    {
        switch (type)
        {
            case kCGC_AsyncDiv3Clk: /* DIV3_CLK. */
                divider = CGC_SOSCDIV_DIV3_VAL(reg);
                break;
            case kCGC_AsyncDiv2Clk: /* DIV2_CLK. */
                divider = CGC_SOSCDIV_DIV2_VAL(reg);
                break;
            case kCGC_AsyncDiv1Clk: /* DIV1_CLK. */
                divider = CGC_SOSCDIV_DIV1_VAL(reg);
                break;
            default:
                assert(false);
                divider = 0U;
                break;
        }
    }
    if (divider != 0UL)
    {
        freq = oscFreq / divider;
    }
    else /* Output disabled. */
    {
        freq = 0U;
    }

    return freq;
}

/*!
 * brief Gets the CGC asynchronous clock frequency from the system OSC in RTD.
 *
 * param type     The asynchronous clock type.
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetRtdSysOscAsyncFreq(cgc_async_clk_t type)
{
    return CLOCK_GetSysOscAsyncFreq(CGC_RTD->SOSCDIV, type);
}

/*!
 * @brief Gets the CGC asynchronous clock frequency from the system OSC in AD.
 *
 * @param type     The asynchronous clock type.
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetAdSysOscAsyncFreq(cgc_async_clk_t type)
{
    return CLOCK_GetSysOscAsyncFreq(CGC_AD->SOSCDIV, type);
}

/*!
 * @brief Gets the CGC asynchronous clock frequency from the system OSC in LPAV.
 *
 * @param type     The asynchronous clock type.
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetLpavSysOscAsyncFreq(cgc_async_clk_t type)
{
    return CLOCK_GetSysOscAsyncFreq(CGC_LPAV->SOSCDIV, type);
}

/*!
 * brief Initializes the CGC FRO clock.
 *
 * This function initializes the CGC FRO clock according to the
 * configuration.
 *
 * param config   Pointer to the configuration structure.
 * retval kStatus_Success FRO is initialized.
 * retval kStatus_CGC_Busy FRO has been enabled and is used by system clock.
 * retval kStatus_ReadOnly FRO control register is locked.
 *
 * note This function can't detect whether the FRO has been enabled and
 * used by an IP.
 */
status_t CLOCK_InitFro(const cgc_fro_config_t *config)
{
    status_t status;

    assert(config);

    /* De-init the FRO first. */
    status = CLOCK_DeinitFro();

    if (kStatus_Success != status)
    {
        return status;
    }

    /* Now start to set up FRO clock. */
    /* Step 1. Configure clock. */
    CGC_RTD->FROCSR = (uint32_t)config->enableMode;

    /* Step 2. Wait for FRO clock to be valid. */
    while (0UL == (CGC_RTD->FROCSR & CGC_FROCSR_FROVLD_MASK))
    {
    }

    return kStatus_Success;
}

/*!
 * brief De-initializes the CGC FRO.
 *
 * This function deinitializes the CGC FRO.
 *
 * retval kStatus_Success FRO is deinitialized.
 * retval kStatus_CGC_Busy FRO is used by system clock.
 * retval kStatus_ReadOnly FRO control register is locked.
 *
 * note This function can't detect whether the FRO is used by an IP.
 */
status_t CLOCK_DeinitFro(void)
{
    uint32_t reg = CGC_RTD->FROCSR;
    status_t status;

    /* If clock is used by system, return error. */
    if ((reg & CGC_FROCSR_FROSEL_MASK) != 0UL)
    {
        status = kStatus_CGC_Busy;
    }
    /* If configure register is locked, return error. */
    else if ((reg & CGC_FROCSR_LK_MASK) != 0UL)
    {
        status = kStatus_ReadOnly;
    }
    else
    {
        CGC_RTD->FROCSR = 0U;
        status          = kStatus_Success;
    }

    return status;
}

static void CLOCK_SetFroAsyncClkDiv(volatile uint32_t *pReg, cgc_async_clk_t asyncClk, uint8_t divider)
{
    uint32_t reg = *pReg;

    switch (asyncClk)
    {
        case kCGC_AsyncDiv3Clk:
            reg = (reg & ~(CGC_FRODIV_DIV3_MASK | CGC_FRODIV_DIV3HALT_MASK)) |
                  (divider > 0U ? CGC_FRODIV_DIV3((uint32_t)divider - 1U) : CGC_FRODIV_DIV3HALT_MASK);
            break;
        case kCGC_AsyncDiv2Clk:
            reg = (reg & ~(CGC_FRODIV_DIV2_MASK | CGC_FRODIV_DIV2HALT_MASK)) |
                  (divider > 0U ? CGC_FRODIV_DIV2((uint32_t)divider - 1U) : CGC_FRODIV_DIV2HALT_MASK);
            break;
        case kCGC_AsyncDiv1Clk:
            reg = (reg & ~(CGC_FRODIV_DIV1_MASK | CGC_FRODIV_DIV1HALT_MASK)) |
                  (divider > 0U ? CGC_FRODIV_DIV1((uint32_t)divider - 1U) : CGC_FRODIV_DIV1HALT_MASK);
            break;
        default:
            assert(false);
            break;
    }

    *pReg = reg;
}

/*!
 * @brief Set the asynchronous clock divider in RTD.
 *
 * @param asyncClk Which asynchronous clock to configure.
 * @param divider The divider value to set. Disabled when divider == 0.
 *
 * @note There might be glitch when changing the asynchronous divider, so make sure
 * the asynchronous clock is not used while changing divider.
 */
void CLOCK_SetRtdFroAsyncClkDiv(cgc_async_clk_t asyncClk, uint8_t divider)
{
    CLOCK_SetFroAsyncClkDiv(&CGC_RTD->FRODIV, asyncClk, divider);
}

/*!
 * @brief Set the asynchronous clock divider in AD.
 *
 * @param asyncClk Which asynchronous clock to configure.
 * @param divider The divider value to set. Disabled when divider == 0.
 *
 * @note There might be glitch when changing the asynchronous divider, so make sure
 * the asynchronous clock is not used while changing divider.
 */
void CLOCK_SetAdFroAsyncClkDiv(cgc_async_clk_t asyncClk, uint8_t divider)
{
    CLOCK_SetFroAsyncClkDiv(&CGC_AD->FRODIV, asyncClk, divider);
}

/*!
 * @brief Set the asynchronous clock divider in LPAV.
 *
 * @param asyncClk Which asynchronous clock to configure.
 * @param divider The divider value to set. Disabled when divider == 0.
 *
 * @note There might be glitch when changing the asynchronous divider, so make sure
 * the asynchronous clock is not used while changing divider.
 */
void CLOCK_SetLpavFroAsyncClkDiv(cgc_async_clk_t asyncClk, uint8_t divider)
{
    CLOCK_SetFroAsyncClkDiv(&CGC_LPAV->FRODIV, asyncClk, divider);
}

/*! @brief  Enable/Disable FRO tuning.
 *   On enable, the function will wait until FRO is close to the target frequency.
 */
void CLOCK_EnableFroTuning(bool enable)
{
    uint32_t xtalFreq   = CLOCK_GetSysOscFreq();
    uint64_t targetFreq = CLK_FRO_192MHZ / 4U;
    uint32_t expected, up, low;
    uint32_t captured, trim;

    assert(xtalFreq);
    assert(targetFreq > xtalFreq);

    if (enable)
    {
        expected = (uint32_t)((targetFreq * (2047U * 2U + 1U) / xtalFreq + 6U) / 2U);
        up       = (uint32_t)(targetFreq * 2047U * 100085U / xtalFreq / 100000U + 2U);
        low      = (uint32_t)((targetFreq * 2048U * 99915U + (uint64_t)xtalFreq * 100000U) / xtalFreq / 100000U + 3U);

        /* Start tuning */
        CGC_RTD->FROCTRL = CGC_FROCTRL_EXP_COUNT(expected) | CGC_FROCTRL_THRESH_RANGE_UP(up - expected) |
                           CGC_FROCTRL_THRESH_RANGE_LOW(expected - low) | CGC_FROCTRL_ENA_TUNE_MASK;

        while (true)
        {
            while ((CGC_RTD->FROCAPVAL & CGC_FROCAPVAL_DATA_VALID_MASK) == 0UL)
            {
            }

            captured = CGC_RTD->FROCAPVAL & CGC_FROCAPVAL_CAPVAL_MASK;
            trim     = CGC_RTD->FRORDTRIM;
            /* Clear FRO_CAPVAL VALID flag */
            CGC_RTD->FRORDTRIM = trim;
            /* Reach the frequency range, then return. */
            if ((captured <= up) && (captured >= low))
            {
                break;
            }
        }
    }
    else
    {
        CGC_RTD->FROCTRL &= ~CGC_FROCTRL_ENA_TUNE_MASK;
    }
}

/*!
 * brief Gets the CGC FRO clock frequency.
 *
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetFroFreq(void)
{
    uint32_t freq;

    if ((CGC_RTD->FROCSR & CGC_FROCSR_FROVLD_MASK) != 0UL) /* FRO is valid. */
    {
        freq = CLK_FRO_192MHZ;
    }
    else
    {
        freq = 0U;
    }

    return freq;
}

static uint32_t CLOCK_GetFroAsyncFreq(uint32_t reg, cgc_async_clk_t type)
{
    uint32_t froFreq = CLOCK_GetFroFreq();
    uint32_t divider = 0U;
    uint32_t freq;

    /* Get divider. */
    if (froFreq != 0UL)
    {
        switch (type)
        {
            case kCGC_AsyncDiv3Clk: /* DIV3_CLK. */
                divider = CGC_FRODIV_DIV3_VAL(reg);
                break;
            case kCGC_AsyncDiv2Clk: /* DIV2_CLK. */
                divider = CGC_FRODIV_DIV2_VAL(reg);
                break;
            case kCGC_AsyncDiv1Clk: /* DIV2_CLK. */
                divider = CGC_FRODIV_DIV1_VAL(reg);
                break;
            default:
                divider = 0U;
                break;
        }
    }
    if (divider != 0UL)
    {
        freq = froFreq / divider;
    }
    else /* Output disabled. */
    {
        freq = 0U;
    }

    return freq;
}

/*!
 * brief Gets the CGC asynchronous clock frequency from the FRO in RTD.
 *
 * param type     The asynchronous clock type.
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetRtdFroAsyncFreq(cgc_async_clk_t type)
{
    return CLOCK_GetFroAsyncFreq(CGC_RTD->FRODIV, type);
}

/*!
 * brief Gets the CGC asynchronous clock frequency from the FRO in AD.
 *
 * param type     The asynchronous clock type.
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetAdFroAsyncFreq(cgc_async_clk_t type)
{
    return CLOCK_GetFroAsyncFreq(CGC_AD->FRODIV, type);
}

/*!
 * brief Gets the CGC asynchronous clock frequency from the FRO in LPAV.
 *
 * param type     The asynchronous clock type.
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetLpavFroAsyncFreq(cgc_async_clk_t type)
{
    return CLOCK_GetFroAsyncFreq(CGC_LPAV->FRODIV, type);
}

/*!
 * @brief Initializes the CGC LPOSC clock.
 *
 * This function initializes the CGC LPOSC clock according to the
 * configuration.
 *
 * @param config   Pointer to the configuration structure.
 * @retval kStatus_Success LPOSC is initialized.
 * @retval kStatus_ReadOnly FRO control register is locked.
 *
 * @note This function can't detect whether the LPOSC has been enabled and
 * used by an IP.
 */
status_t CLOCK_InitLposc(const cgc_lposc_config_t *config)
{
    status_t status;

    assert(config);

    /* De-init the FRO first. */
    status = CLOCK_DeinitLposc();

    if (kStatus_Success != status)
    {
        return status;
    }

    /* Now start to set up LPOSC clock. */
    /* Step 1. Configure clock. */
    CGC_RTD->LPOSCCSR = CGC_LPOSCCSR_LPOSCEN_MASK | config->enableMode;

    /* Step 2. Wait for FRO clock to be valid. */
    while (0UL == (CGC_RTD->LPOSCCSR & CGC_LPOSCCSR_LPOSCVLD_MASK))
    {
    }

    return kStatus_Success;
}

/*!
 * @brief De-initializes the CGC LPOSC.
 *
 * This function deinitializes the CGC LPOSC.
 *
 * @retval kStatus_Success LPOSC is deinitialized.
 * @retval kStatus_ReadOnly LPOSC control register is locked.
 *
 * @note This function can't detect whether the LPOSC is used by an IP.
 */
status_t CLOCK_DeinitLposc(void)
{
    uint32_t reg = CGC_RTD->LPOSCCSR;
    status_t status;

    /* If configure register is locked, return error. */
    if ((reg & CGC_LPOSCCSR_LK_MASK) != 0UL)
    {
        status = kStatus_ReadOnly;
    }
    else
    {
        CGC_RTD->LPOSCCSR = 0U;
        status            = kStatus_Success;
    }

    return status;
}

/*!
 * @brief Gets the CGC LPOSC clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetLpOscFreq(void)
{
    uint32_t freq;

    if ((CGC_RTD->LPOSCCSR & CGC_LPOSCCSR_LPOSCVLD_MASK) != 0UL) /* LPOSC is valid. */
    {
        freq = CLK_LPOSC_1MHZ;
    }
    else
    {
        freq = 0U;
    }

    return freq;
}

/*!
 * brief Gets the CGC RTC OSC clock frequency.
 *
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetRtcOscFreq(void)
{
    uint32_t freq;

    if ((CGC_RTD->ROSCCTRL & CGC_ROSCCTRL_ROSCVLD_MASK) != 0UL) /* RTC OSC clock is valid. */
    {
        /* Please call CLOCK_SetXtal32Freq base on board setting before using RTC OSC clock. */
        assert(g_xtal32Freq);
        freq = g_xtal32Freq;
    }
    else
    {
        freq = 0U;
    }

    return freq;
}

/*!
 * @brief Sets the RTC OSC monitor mode.
 *
 * This function sets the RTC OSC monitor mode. The mode can be disabled.
 * It can generate an interrupt when the error is disabled, or reset when the error is detected.
 *
 * @param mode Monitor mode to set.
 */
void CLOCK_SetRtcOscMonitorMode(cgc_rosc_monitor_mode_t mode)
{
    uint32_t reg = CGC_RTD->ROSCCTRL;

    reg &= ~(CGC_ROSCCTRL_ROSCCM_MASK | CGC_ROSCCTRL_ROSCCMRE_MASK);

    reg |= (uint32_t)mode;

    CGC_RTD->ROSCCTRL = reg;
}

/*!
 * @brief Initializes the CGC PLL0.
 *
 * This function enables the CGC PLL0 clock according to the
 * configuration. The PLL0 can use the OSC or FRO as
 * the clock source. Ensure that the source clock is valid before
 * calling this function.
 *
 * Example code for initializing PLL0 clock output:
 * @code
 * const cgc_pll0_config_t g_cgcPll0Config = {.enableMode = kCGC_PllEnable,
 *                                            .div1 = 1U,
 *                                            .pfd1Div = 2U,
 *                                            .pfd2Div = 0U,
 *                                            .src = kCGC_PllSrcSysOsc,
 *                                            .mult = kCGC_Pll0Mult20};
 * CLOCK_InitPll0(&g_cgcPll0Config);
 * @endcode
 *
 * @param config   Pointer to the configuration structure.
 * @retval kStatus_Success PLL0 is initialized.
 * @retval kStatus_CGC_Busy PLL0 has been enabled and is used by the system clock.
 * @retval kStatus_ReadOnly PLL0 control register is locked.
 *
 * @note This function can't detect whether the PLL0 has been enabled and
 * used by an IP.
 */
status_t CLOCK_InitPll0(const cgc_pll0_config_t *config)
{
    status_t status;

    assert(config);

    /* De-init the PLL0 first. */
    status = CLOCK_DeinitPll0();

    if (kStatus_Success != status)
    {
        return status;
    }

    /* Now start to set up PLL clock. */
    /* Step 1. Setup dividers. */
    CGC_RTD->PLL0DIV_VCO =
        config->div1 > 0U ? CGC_PLL0DIV_VCO_DIV1((uint32_t)config->div1 - 1U) : (uint32_t)CGC_PLL0DIV_VCO_DIV1HALT_MASK;
    CGC_RTD->PLL0DIV_PFD_0 = (config->pfd1Div > 0U ? CGC_PLL0DIV_PFD_0_DIV1((uint32_t)config->pfd1Div - 1U) :
                                                     (uint32_t)CGC_PLL0DIV_PFD_0_DIV1HALT_MASK) |
                             (config->pfd2Div > 0U ? CGC_PLL0DIV_PFD_0_DIV2((uint32_t)config->pfd2Div - 1U) :
                                                     (uint32_t)CGC_PLL0DIV_PFD_0_DIV2HALT_MASK);

    /* Step 2. Set PLL configuration. */
    CGC_RTD->PLL0CFG = CGC_PLL0CFG_SOURCE(config->src) | CGC_PLL0CFG_MULT(config->mult);

    /* Step 3. Enable clock. */
    CGC_RTD->PLL0CSR = (uint32_t)CGC_PLL0CSR_PLL0EN_MASK | config->enableMode;

    /* Step 4. Wait for PLL clock to be valid. */
    while (0UL == (CGC_RTD->PLL0CSR & CGC_PLL0CSR_PLLVLD_MASK))
    {
    }

    return kStatus_Success;
}

/*!
 * brief De-initializes the CGC system PLL.
 *
 * This function disables the CGC system PLL.
 *
 * retval kStatus_Success system PLL is deinitialized.
 * retval kStatus_CGC_Busy system PLL is used by the system clock.
 * retval kStatus_ReadOnly PLL0 control register is locked.
 *
 * note This function can't detect whether the system PLL is used by an IP.
 */
status_t CLOCK_DeinitPll0(void)
{
    uint32_t reg = CGC_RTD->PLL0CSR;
    status_t status;

    /* If clock is used by system, return error. */
    if ((reg & CGC_PLL0CSR_PLLSEL_MASK) != 0UL)
    {
        status = kStatus_CGC_Busy;
    }
    /* If configure register is locked, return error. */
    else if ((reg & CGC_PLL0CSR_LK_MASK) != 0UL)
    {
        status = kStatus_ReadOnly;
    }
    else
    {
        CGC_RTD->PLL0CSR = 0;
        status           = kStatus_Success;
    }

    return status;
}

/*!
 * @brief Set the asynchronous clock divider.
 *
 * @param asyncClk Which asynchronous clock to configure.
 * @param divider The divider value to set. Disabled when divider == 0.
 *
 * @note There might be glitch when changing the asynchronous divider, so make sure
 * the asynchronous clock is not used while changing divider.
 */
void CLOCK_SetPll0AsyncClkDiv(cgc_async_clk_t asyncClk, uint8_t divider)
{
    uint32_t reg;

    switch (asyncClk)
    {
        case kCGC_AsyncVcoClk:
            reg = CGC_RTD->PLL0DIV_VCO;
            reg =
                (reg & ~(CGC_PLL0DIV_VCO_DIV1_MASK | CGC_PLL0DIV_VCO_DIV1HALT_MASK)) |
                (divider > 0U ? CGC_PLL0DIV_VCO_DIV1((uint32_t)divider - 1U) : (uint32_t)CGC_PLL0DIV_VCO_DIV1HALT_MASK);
            CGC_RTD->PLL0DIV_VCO = reg;
            break;
        case kCGC_AsyncPfd1Div1Clk:
            reg = CGC_RTD->PLL0DIV_PFD_0;
            reg = (reg & ~(CGC_PLL0DIV_PFD_0_DIV1_MASK | CGC_PLL0DIV_PFD_0_DIV1HALT_MASK)) |
                  (divider > 0U ? CGC_PLL0DIV_PFD_0_DIV1((uint32_t)divider - 1U) :
                                  (uint32_t)CGC_PLL0DIV_PFD_0_DIV1HALT_MASK);
            CGC_RTD->PLL0DIV_PFD_0 = reg;
            break;
        case kCGC_AsyncPfd2Div1Clk:
            reg = CGC_RTD->PLL0DIV_PFD_0;
            reg = (reg & ~(CGC_PLL0DIV_PFD_0_DIV2_MASK | CGC_PLL0DIV_PFD_0_DIV2HALT_MASK)) |
                  (divider > 0U ? CGC_PLL0DIV_PFD_0_DIV2((uint32_t)divider - 1U) :
                                  (uint32_t)CGC_PLL0DIV_PFD_0_DIV2HALT_MASK);
            CGC_RTD->PLL0DIV_PFD_0 = reg;
            break;
        default:
            assert(false);
            break;
    }
}

static uint32_t CLOCK_GetPll0CommonFreq(void)
{
    uint32_t freq = 0U;

    if ((CGC_RTD->PLL0CFG & CGC_PLL0CFG_SOURCE_MASK) != 0UL) /* If use FRO24M */
    {
        freq = CLOCK_GetFroFreq() / 8U;
    }
    else /* Use System OSC. */
    {
        freq = CLOCK_GetSysOscFreq();
    }

    if (freq != 0UL) /* If source is valid. */
    {
        freq *= s_pll0Multi[CGC_PLL0CFG_MULT_VAL]; /* Multiplier. */
    }

    return freq;
}

/*!
 * brief Gets the CGC system PLL clock frequency.
 *
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetPll0Freq(void)
{
    uint32_t freq;

    if ((CGC_RTD->PLL0CSR & CGC_PLL0CSR_PLLVLD_MASK) != 0UL) /* PLL0 is valid. */
    {
        freq = CLOCK_GetPll0CommonFreq();
    }
    else
    {
        freq = 0U;
    }

    return freq;
}

/*!
 * brief Gets the CGC asynchronous clock frequency from PLL0.
 *
 * param type     The asynchronous clock type.
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetPll0AsyncFreq(cgc_async_clk_t type)
{
    uint32_t pllFreq;
    uint32_t divider;
    uint32_t freq;

    switch (type)
    {
        case kCGC_AsyncVcoClk: /* PLL0 VCO. */
            pllFreq = CLOCK_GetPll0Freq();
            divider = CGC_PLL0DIV_VCO_DIV1_VAL;
            break;
        case kCGC_AsyncPfd1Div1Clk: /* PLL0 PFD1 DIV. */
            pllFreq = CLOCK_GetPll0PfdFreq(kCGC_PllPfd1Clk);
            divider = CGC_PLL0DIV_PFD1_DIV_VAL;
            break;
        case kCGC_AsyncPfd2Div1Clk: /* PLL0 PFD2 DIV. */
            pllFreq = CLOCK_GetPll0PfdFreq(kCGC_PllPfd2Clk);
            divider = CGC_PLL0DIV_PFD2_DIV_VAL;
            break;
        default:
            divider = 0U;
            assert(false);
            break;
    }

    if (divider != 0UL)
    {
        freq = pllFreq / divider;
    }
    else /* Output disabled. */
    {
        freq = 0U;
    }

    return freq;
}

/*!
 * @brief Gets the CGC PLL0 PFD clock frequency.
 *
 * @param pfdClkout     The selected PFD clock out. See "cgc_pll_pfd_clkout_t".
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetPll0PfdFreq(cgc_pll_pfd_clkout_t pfdClkout)
{
    uint32_t freq      = 0U;
    uint32_t fracValue = 0U;

    if ((CGC_RTD->PLL0PFDCFG & CGC_PLLPFD_PFD_VALID_MASK(pfdClkout)) != 0UL) /* PLL0 PFD is valid. */
    {
        if (0UL == (CGC_RTD->PLL0PFDCFG & CGC_PLLPFD_PFD_CLKGATE_MASK(pfdClkout)))
        {
            fracValue = (CGC_RTD->PLL0PFDCFG & CGC_PLLPFD_PFD_MASK(pfdClkout)) >> (uint32_t)pfdClkout;

            if (fracValue != 0UL)
            {
                freq = CLOCK_GetPll0CommonFreq();
                freq = (uint32_t)((uint64_t)freq * PFD_FREQ_CALCUL_CONSTANT /
                                  fracValue); /* PFD Clock Frequency = PLL output frequency * 18 / frac value. */
            }
            else
            {
            }
        }
        else
        {
        }
    }
    else
    {
    }

    return freq;
}

/*!
 * @brief Enables the CGC PLL0 Fractional Divide (PFD) clock out with configurations.
 *
 * PLL Frequency = Fref * MULT
 * PFD Clock Frequency = PLL output frequency * 18/frac value
 *
 * @code
 * Example code for configuring PLL0 PFD0 clock output:
 * const cgc_pll0_config_t g_cgcPll0Config = {.enableMode = kCGC_PllEnable,
 *                                           .div1 = 1U,
 *                                           .pfd1Div = 2U,
 *                                           .pfd2Div = 0U,
 *                                           .src = kCGC_PllSrcSysOsc,
 *                                           .mult = kCGC_Pll0Mult20};
 * CLOCK_InitPll0(&g_cgcPll0Config);
 * CLOCK_EnablePll0PfdClkout(kCGC_PllPfd0Clk, 15U);
 * @endcode
 *
 * @param pfdClkout  PLL0 PFD clock out select.
 * @param fracValue  Fractional Divider value. Recommended to be kept between 12-35 for all PFDs.
 */
void CLOCK_EnablePll0PfdClkout(cgc_pll_pfd_clkout_t pfdClkout, uint8_t fracValue)
{
    /*
     * Input fractional divider value should have a maximum size of 6 bits (64U).
     * Note: It is recommended that PFD settings are kept between 12-35 for all PFDs.
     */
    assert(fracValue);
    assert(fracValue < CGC_PLLPFD_PFD_MAX_VAL);

    /* Step 1. Gate PFD clock. */
    CGC_RTD->PLL0PFDCFG |= CGC_PLLPFD_PFD_CLKGATE_MASK(pfdClkout);

    /* Step 2. Program the new PFD value. */
    CGC_RTD->PLL0PFDCFG =
        (CGC_RTD->PLL0PFDCFG & ~CGC_PLLPFD_PFD_MASK(pfdClkout)) | CGC_PLLPFD_PFD_VAL(pfdClkout, fracValue);

    /* Step 3. Ungate PFD clock. */
    CGC_RTD->PLL0PFDCFG &= ~CGC_PLLPFD_PFD_CLKGATE_MASK(pfdClkout);

    /* Step 4. Wait for PFD clock to be stable. */
    while (0UL == (CGC_RTD->PLL0PFDCFG & CGC_PLLPFD_PFD_VALID_MASK(pfdClkout)))
    {
    }
}

/*!
 * @brief Initializes the CGC PLL1.
 *
 * This function enables the CGC PLL1 clock according to the
 * configuration. The PLL1 can use the system OSC or FRO as
 * the clock source. Ensure that the source clock is valid before
 * calling this function.
 *
 * Example code for initializing PLL1 clock output:
 * @code
 * const cgc_pll1_config_t g_cgcPll1Config = {.enableMode = kCGC_PllEnable,
 *                                            .div1 = 0U,
 *                                            .pfd1Div = 0U,
 *                                            .pfd2Div = 0U,
 *                                            .src = kCGC_PllSrcFro24M,
 *                                            .mult = kCGC_Pll1Mult22,
 *                                            .num = 578,
 *                                            .denom = 1000};
 * CLOCK_InitPll1(&g_cgcPll1Config);
 * @endcode
 *
 * @param config   Pointer to the configuration structure.
 * @retval kStatus_Success PLL1 is initialized.
 * @retval kStatus_CGC_Busy PLL1 has been enabled and is used by the system clock.
 * @retval kStatus_ReadOnly PLL1 control register is locked.
 *
 * @note This function can't detect whether the PLL1 has been enabled and
 * is used by an IP.
 */
status_t CLOCK_InitPll1(const cgc_pll1_config_t *config)
{
    status_t status;

    assert(config);

    /* De-init the PLL1 first. */
    status = CLOCK_DeinitPll1();
    if (kStatus_Success != status)
    {
        return status;
    }

    /* Now start to set up PLL clock. */
    /* Step 1. Setup dividers. */
    CGC_RTD->PLL1DIV_VCO =
        (config->div1 > 0U ? CGC_PLL1DIV_VCO_DIV1((uint32_t)config->div1 - 1U) : CGC_PLL1DIV_VCO_DIV1HALT_MASK);
    CGC_RTD->PLL1DIV_PFD_0 = (config->pfd1Div > 0U ? CGC_PLL1DIV_PFD_0_DIV1((uint32_t)config->pfd1Div - 1U) :
                                                     (uint32_t)CGC_PLL1DIV_PFD_0_DIV1HALT_MASK) |
                             (config->pfd2Div > 0U ? CGC_PLL1DIV_PFD_0_DIV2((uint32_t)config->pfd2Div - 1U) :
                                                     (uint32_t)CGC_PLL1DIV_PFD_0_DIV2HALT_MASK);

    /* Step 2. Set PLL configuration. */
    CGC_RTD->PLL1CFG = CGC_PLL1CFG_SOURCE(config->src) | CGC_PLL1CFG_MULT(config->mult);

    /* Step 3. Set Numerator and Denominator. */
    CGC_RTD->PLL1DENOM = config->denom;
    CGC_RTD->PLL1NUM   = config->num;

    /* Step 4. Enable clock. */
    CGC_RTD->PLL1CSR = (uint32_t)CGC_PLL1CSR_PLLEN_MASK | config->enableMode;

    /* Step 5. Wait for PLL clock to be valid. */
    while (0UL == (CGC_RTD->PLL1CSR & CGC_PLL1CSR_PLLVLD_MASK))
    {
    }

    return kStatus_Success;
}

/*!
 * @brief De-initializes the CGC PLL1.
 *
 * This function disables the CGC PLL1.
 *
 * @retval kStatus_Success PLL1 is deinitialized.
 * @retval kStatus_CGC_Busy PLL1 is used by the system clock.
 * @retval kStatus_ReadOnly PLL1 control register is locked.
 *
 * @note This function can't detect whether the PLL1 is used by an IP.
 */
status_t CLOCK_DeinitPll1(void)
{
    uint32_t reg = CGC_RTD->PLL1CSR;
    status_t status;

    /* If clock is used by system, return error. */
    if ((reg & CGC_PLL1CSR_PLLSEL_MASK) != 0UL)
    {
        status = kStatus_CGC_Busy;
    }
    /* If configure register is locked, return error. */
    else if ((reg & CGC_PLL1CSR_LK_MASK) != 0UL)
    {
        status = kStatus_ReadOnly;
    }
    else
    {
        /* Deinit and clear the error. */
        CGC_RTD->PLL1CSR = 0;
        status           = kStatus_Success;
    }

    return status;
}

/*!
 * @brief Set the asynchronous clock divider.
 *
 * @param asyncClk Which asynchronous clock to configure.
 * @param divider The divider value to set. Disabled when divider == 0.
 *
 * @note There might be glitch when changing the asynchronous divider, so make sure
 * the asynchronous clock is not used while changing divider.
 */
void CLOCK_SetPll1AsyncClkDiv(cgc_async_clk_t asyncClk, uint8_t divider)
{
    uint32_t reg;

    switch (asyncClk)
    {
        case kCGC_AsyncVcoClk:
            reg = CGC_RTD->PLL1DIV_VCO;
            reg =
                (reg & ~(CGC_PLL1DIV_VCO_DIV1_MASK | CGC_PLL1DIV_VCO_DIV1HALT_MASK)) |
                (divider > 0U ? CGC_PLL1DIV_VCO_DIV1((uint32_t)divider - 1U) : (uint32_t)CGC_PLL1DIV_VCO_DIV1HALT_MASK);
            CGC_RTD->PLL1DIV_VCO = reg;
            break;
        case kCGC_AsyncPfd1Div1Clk:
            reg = CGC_RTD->PLL1DIV_PFD_0;
            reg = (reg & ~(CGC_PLL1DIV_PFD_0_DIV1_MASK | CGC_PLL1DIV_PFD_0_DIV1HALT_MASK)) |
                  (divider > 0U ? CGC_PLL1DIV_PFD_0_DIV1((uint32_t)divider - 1U) :
                                  (uint32_t)CGC_PLL1DIV_PFD_0_DIV1HALT_MASK);
            CGC_RTD->PLL1DIV_PFD_0 = reg;
            break;
        case kCGC_AsyncPfd2Div1Clk:
            reg = CGC_RTD->PLL1DIV_PFD_0;
            reg = (reg & ~(CGC_PLL1DIV_PFD_0_DIV2_MASK | CGC_PLL1DIV_PFD_0_DIV2HALT_MASK)) |
                  (divider > 0U ? CGC_PLL1DIV_PFD_0_DIV2((uint32_t)divider - 1U) :
                                  (uint32_t)CGC_PLL1DIV_PFD_0_DIV2HALT_MASK);
            CGC_RTD->PLL1DIV_PFD_0 = reg;
            break;
        default:
            assert(false);
            break;
    }
}

static uint32_t CLOCK_GetPll1CommonFreq(void)
{
    uint32_t freq = 0U;
    uint64_t freqTmp;
    uint64_t pllnumTmp;

    if ((CGC_RTD->PLL1CFG & CGC_PLL1CFG_SOURCE_MASK) != 0UL) /* If use FRO24M */
    {
        freq = CLOCK_GetFroFreq() / 8U;
    }
    else /* Use System OSC. */
    {
        freq = CLOCK_GetSysOscFreq();
    }

    if (freq != 0UL) /* If source is valid. */
    {
        pllnumTmp = (uint64_t)CGC_PLL1NUM_NUM_VAL;
        freqTmp   = (uint64_t)freq * pllnumTmp / CGC_PLL1DENOM_DENOM_VAL;
        freq      = freq * CGC_PLL1CFG_MULT_VAL + (uint32_t)freqTmp;
    }

    return freq;
}

/*!
 * brief Gets CGC PLL1 clock frequency.
 *
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetPll1Freq(void)
{
    uint32_t freq;

    if ((CGC_RTD->PLL1CSR & CGC_PLL1CSR_PLLVLD_MASK) != 0UL) /* PLL1 is valid. */
    {
        freq = CLOCK_GetPll1CommonFreq();
    }
    else
    {
        freq = 0U;
    }

    return freq;
}

/*!
 * brief Gets the CGC asynchronous clock frequency from PLL1.
 *
 * param type     The asynchronous clock type.
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetPll1AsyncFreq(cgc_async_clk_t type)
{
    uint32_t pllFreq;
    uint32_t divider;
    uint32_t freq;

    switch (type)
    {
        case kCGC_AsyncVcoClk: /* PLL1 VCO. */
            pllFreq = CLOCK_GetPll1Freq();
            divider = CGC_PLL1DIV_VCO_DIV1_VAL;
            break;
        case kCGC_AsyncPfd1Div1Clk: /* PLL1 PFD1 DIV. */
            pllFreq = CLOCK_GetPll1PfdFreq(kCGC_PllPfd1Clk);
            divider = CGC_PLL1DIV_PFD1_DIV_VAL;
            break;
        case kCGC_AsyncPfd2Div1Clk: /* PLL1 PFD2 DIV. */
            pllFreq = CLOCK_GetPll1PfdFreq(kCGC_PllPfd2Clk);
            divider = CGC_PLL1DIV_PFD2_DIV_VAL;
            break;
        default:
            divider = 0U;
            assert(false);
            break;
    }

    if (divider != 0UL)
    {
        freq = pllFreq / divider;
    }
    else /* Output disabled. */
    {
        freq = 0U;
    }

    return freq;
}

/*!
 * brief Gets the CGC PLL1 PFD clock frequency.
 *
 * param pfdClkout     The selected PFD clocks out. See "cgc_pll_pfd_clkout_t".
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetPll1PfdFreq(cgc_pll_pfd_clkout_t pfdClkout)
{
    uint32_t freq      = 0U;
    uint32_t fracValue = 0U;

    if ((CGC_RTD->PLL1PFDCFG & CGC_PLLPFD_PFD_VALID_MASK(pfdClkout)) != 0UL) /* PLL1 PFD is valid. */
    {
        if (0UL == (CGC_RTD->PLL1PFDCFG & CGC_PLLPFD_PFD_CLKGATE_MASK(pfdClkout)))
        {
            fracValue = (CGC_RTD->PLL1PFDCFG & CGC_PLLPFD_PFD_MASK(pfdClkout)) >> (uint32_t)pfdClkout;

            if (fracValue != 0UL)
            {
                freq = CLOCK_GetPll1CommonFreq();
                freq = (uint32_t)((uint64_t)freq * PFD_FREQ_CALCUL_CONSTANT /
                                  fracValue); /* PFD Clock Frequency = PLL output frequency * 18 / frac value. */
            }
            else
            {
            }
        }
        else
        {
        }
    }
    else
    {
    }

    return freq;
}

/*!
 * @brief Enables the CGC PLL1 Fractional Divide (PFD) clock out with configurations.
 *
 * PLL1 Frequency = Fref * (MULT + NUM/DENOM)
 * PFD Clock Frequency = PLL output frequency * 18/frac value
 *
 * Example code for configuring PLL1 as PLL1 PFD clock output:
 * @code
 * const cgc_pll1_config_t g_cgcPll1Config = {.enableMode = kCGC_PllEnable,
 *                                            .div1 = 0U,
 *                                            .pfd1Div = 0U,
 *                                            .pfd2Div = 0U,
 *                                            .src = kCGC_PllSrcFro24M,
 *                                            .mult = kCGC_Pll1Mult22,
 *                                            .num = 578,
 *                                            .denom = 1000};
 * CLOCK_InitPll1(&g_cgcPll1Config);
 * CLOCK_EnablePll1PfdClkout(kCGC_PllPfd0Clk, 15U);
 * @endcode
 *
 * @param pfdClkout  PLL1 PFD clock out select.
 * @param fracValue  Fractional Divider value. Recommended to be kept between 12-35 for all PFDs.
 */
void CLOCK_EnablePll1PfdClkout(cgc_pll_pfd_clkout_t pfdClkout, uint8_t fracValue)
{
    /*
     * Input fractional divider value should have a maximum size of 6 bits (64U).
     * Note: It is recommended that PFD settings are kept between 12-35 for all PFDs.
     */
    assert(fracValue);
    assert(fracValue < CGC_PLLPFD_PFD_MAX_VAL);

    /* Step 1. Gate PFD clock. */
    CGC_RTD->PLL1PFDCFG |= CGC_PLLPFD_PFD_CLKGATE_MASK(pfdClkout);

    /* Step 2. Program the new PFD value. */
    CGC_RTD->PLL1PFDCFG =
        (CGC_RTD->PLL1PFDCFG & ~CGC_PLLPFD_PFD_MASK(pfdClkout)) | CGC_PLLPFD_PFD_VAL(pfdClkout, fracValue);

    /* Step 3. Ungate PFD clock. */
    CGC_RTD->PLL1PFDCFG &= ~CGC_PLLPFD_PFD_CLKGATE_MASK(pfdClkout);

    /* Step 4. Wait for PFD clock to be stable. */
    while (0UL == (CGC_RTD->PLL1PFDCFG & CGC_PLLPFD_PFD_VALID_MASK(pfdClkout)))
    {
    }
}

static uint32_t CLOCK_GetPll3CommonFreq(void)
{
    uint32_t freq = 0U;
    uint64_t freqTmp;
    uint64_t pllnumTmp;

    if ((CGC_AD->PLL3CFG & CGC_AD_PLL3CFG_SOURCE_MASK) != 0UL) /* If use FRO24M */
    {
        freq = CLOCK_GetFroFreq() / 8U;
    }
    else /* Use System OSC. */
    {
        freq = CLOCK_GetSysOscFreq();
    }

    if (freq != 0UL) /* If source is valid. */
    {
        pllnumTmp = (uint64_t)CGC_AD_PLL3NUM_NUM_VAL;
        freqTmp   = (uint64_t)freq * pllnumTmp / CGC_AD_PLL3DENOM_DENOM_VAL;
        freq      = freq * CGC_AD_PLL3CFG_MULT_VAL + (uint32_t)freqTmp;
    }

    return freq;
}

/*!
 * brief Gets CGC PLL3 clock frequency.
 *
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetPll3Freq(void)
{
    uint32_t freq;

    if ((CGC_AD->PLL3CSR & CGC_AD_PLL3CSR_PLLVLD_MASK) != 0UL) /* PLL3 is valid. */
    {
        freq = CLOCK_GetPll3CommonFreq();
    }
    else
    {
        freq = 0U;
    }

    return freq;
}

/*!
 * brief Gets the CGC asynchronous clock frequency from PLL3.
 *
 * param type     The asynchronous clock type.
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetPll3AsyncFreq(cgc_async_clk_t type)
{
    uint32_t pllFreq;
    uint32_t divider;
    uint32_t freq;

    switch (type)
    {
        case kCGC_AsyncVcoClk: /* PLL3 VCO. */
            pllFreq = CLOCK_GetPll3Freq();
            divider = CGC_AD_PLL3DIV_VCO_DIV1_VAL;
            break;
        case kCGC_AsyncPfd0Div1Clk: /* PLL3 PFD0 DIV1. */
            pllFreq = CLOCK_GetPll3PfdFreq(kCGC_PllPfd0Clk);
            divider = CGC_AD_PLL3DIV_PFD0_DIV1_VAL;
            break;
        case kCGC_AsyncPfd0Div2Clk: /* PLL3 PFD0 DIV2. */
            pllFreq = CLOCK_GetPll3PfdFreq(kCGC_PllPfd0Clk);
            divider = CGC_AD_PLL3DIV_PFD0_DIV2_VAL;
            break;
        case kCGC_AsyncPfd1Div1Clk: /* PLL3 PFD1 DIV1. */
            pllFreq = CLOCK_GetPll3PfdFreq(kCGC_PllPfd1Clk);
            divider = CGC_AD_PLL3DIV_PFD1_DIV1_VAL;
            break;
        case kCGC_AsyncPfd1Div2Clk: /* PLL3 PFD1 DIV2. */
            pllFreq = CLOCK_GetPll3PfdFreq(kCGC_PllPfd1Clk);
            divider = CGC_AD_PLL3DIV_PFD1_DIV2_VAL;
            break;
        case kCGC_AsyncPfd2Div1Clk: /* PLL3 PFD2 DIV1. */
            pllFreq = CLOCK_GetPll3PfdFreq(kCGC_PllPfd2Clk);
            divider = CGC_AD_PLL3DIV_PFD2_DIV1_VAL;
            break;
        case kCGC_AsyncPfd2Div2Clk: /* PLL3 PFD2 DIV2. */
            pllFreq = CLOCK_GetPll3PfdFreq(kCGC_PllPfd2Clk);
            divider = CGC_AD_PLL3DIV_PFD2_DIV2_VAL;
            break;
        case kCGC_AsyncPfd3Div1Clk: /* PLL3 PFD3 DIV1. */
            pllFreq = CLOCK_GetPll3PfdFreq(kCGC_PllPfd3Clk);
            divider = CGC_AD_PLL3DIV_PFD3_DIV1_VAL;
            break;
        case kCGC_AsyncPfd3Div2Clk: /* PLL3 PFD3 DIV2. */
            pllFreq = CLOCK_GetPll3PfdFreq(kCGC_PllPfd3Clk);
            divider = CGC_AD_PLL3DIV_PFD3_DIV2_VAL;
            break;
        default:
            divider = 0U;
            assert(false);
            break;
    }

    if (divider != 0UL)
    {
        freq = pllFreq / divider;
    }
    else /* Output disabled. */
    {
        freq = 0U;
    }

    return freq;
}

/*!
 * brief Gets the CGC PLL3 PFD clock frequency.
 *
 * param pfdClkout     The selected PFD clocks out. See "cgc_pll_pfd_clkout_t".
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetPll3PfdFreq(cgc_pll_pfd_clkout_t pfdClkout)
{
    uint32_t freq      = 0U;
    uint32_t fracValue = 0U;

    if ((CGC_AD->PLL3PFDCFG & CGC_PLLPFD_PFD_VALID_MASK(pfdClkout)) != 0UL) /* PLL3 PFD is valid. */
    {
        if (0UL == (CGC_AD->PLL3PFDCFG & CGC_PLLPFD_PFD_CLKGATE_MASK(pfdClkout)))
        {
            fracValue = (CGC_AD->PLL3PFDCFG & CGC_PLLPFD_PFD_MASK(pfdClkout)) >> (uint32_t)pfdClkout;

            if (fracValue != 0UL)
            {
                freq = CLOCK_GetPll3CommonFreq();
                freq = (uint32_t)((uint64_t)freq * PFD_FREQ_CALCUL_CONSTANT /
                                  fracValue); /* PFD Clock Frequency = PLL output frequency * 18 / frac value. */
            }
            else
            {
            }
        }
        else
        {
        }
    }
    else
    {
    }

    return freq;
}

/*!
 * @brief Initializes the CGC PLL4.
 *
 * This function enables the CGC PLL4 clock according to the
 * configuration. The PLL4 can use the system OSC or FRO as
 * the clock source. Ensure that the source clock is valid before
 * calling this function.
 *
 * Example code for initializing PLL4 clock output:
 * @code
 * const cgc_pll4_config_t g_cgcPll4Config = {.enableMode = kCGC_PllEnable,
 *                                            .div1 = 0U,
 *                                            .pfd0Div1 = 0U,
 *                                            .pfd0Div2 = 0U,
 *                                            .pfd1Div1 = 0U,
 *                                            .pfd1Div2 = 0U,
 *                                            .pfd2Div1 = 0U,
 *                                            .pfd2Div2 = 0U,
 *                                            .pfd3Div1 = 0U,
 *                                            .pfd3Div2 = 0U,
 *                                            .src = kCGC_PllSrcFro24M,
 *                                            .mult = kCGC_Pll4Mult22,
 *                                            .num = 578,
 *                                            .denom = 1000};
 * CLOCK_InitPll4(&g_cgcPll4Config);
 * @endcode
 *
 * @param config   Pointer to the configuration structure.
 * @retval kStatus_Success PLL4 is initialized.
 * @retval kStatus_CGC_Busy PLL4 has been enabled and is used by the system clock.
 * @retval kStatus_ReadOnly PLL4 control register is locked.
 *
 * @note This function can't detect whether the PLL4 has been enabled and
 * is used by an IP.
 */
status_t CLOCK_InitPll4(const cgc_pll4_config_t *config)
{
    status_t status;

    assert(config);

    /* De-init the PLL4 first. */
    status = CLOCK_DeinitPll4();
    if (kStatus_Success != status)
    {
        return status;
    }

    /* Now start to set up PLL clock. */
    /* Step 1. Setup dividers. */
    CGC_LPAV->PLL4DIV_VCO   = (config->div1 > 0U ? CGC_LPAV_PLL4DIV_VCO_DIV1((uint32_t)config->div1 - 1U) :
                                                 (uint32_t)CGC_LPAV_PLL4DIV_VCO_DIV1HALT_MASK);
    CGC_LPAV->PLL4DIV_PFD_0 = (config->pfd0Div1 > 0U ? CGC_LPAV_PLL4DIV_PFD_0_DIV1((uint32_t)config->pfd0Div1 - 1U) :
                                                       (uint32_t)CGC_LPAV_PLL4DIV_PFD_0_DIV1HALT_MASK) |
                              (config->pfd0Div2 > 0U ? CGC_LPAV_PLL4DIV_PFD_0_DIV2((uint32_t)config->pfd0Div2 - 1U) :
                                                       (uint32_t)CGC_LPAV_PLL4DIV_PFD_0_DIV2HALT_MASK) |
                              (config->pfd1Div1 > 0U ? CGC_LPAV_PLL4DIV_PFD_0_DIV3((uint32_t)config->pfd1Div1 - 1U) :
                                                       (uint32_t)CGC_LPAV_PLL4DIV_PFD_0_DIV3HALT_MASK) |
                              (config->pfd1Div2 > 0U ? CGC_LPAV_PLL4DIV_PFD_0_DIV4((uint32_t)config->pfd1Div2 - 1U) :
                                                       (uint32_t)CGC_LPAV_PLL4DIV_PFD_0_DIV4HALT_MASK);
    CGC_LPAV->PLL4DIV_PFD_1 = (config->pfd2Div1 > 0U ? CGC_LPAV_PLL4DIV_PFD_1_DIV1((uint32_t)config->pfd2Div1 - 1U) :
                                                       (uint32_t)CGC_LPAV_PLL4DIV_PFD_1_DIV1HALT_MASK) |
                              (config->pfd2Div2 > 0U ? CGC_LPAV_PLL4DIV_PFD_1_DIV2((uint32_t)config->pfd2Div2 - 1U) :
                                                       (uint32_t)CGC_LPAV_PLL4DIV_PFD_1_DIV2HALT_MASK) |
                              (config->pfd3Div1 > 0U ? CGC_LPAV_PLL4DIV_PFD_1_DIV3((uint32_t)config->pfd3Div1 - 1U) :
                                                       (uint32_t)CGC_LPAV_PLL4DIV_PFD_1_DIV3HALT_MASK) |
                              (config->pfd3Div2 > 0U ? CGC_LPAV_PLL4DIV_PFD_1_DIV4((uint32_t)config->pfd3Div2 - 1U) :
                                                       (uint32_t)CGC_LPAV_PLL4DIV_PFD_1_DIV4HALT_MASK);

    /* Step 2. Set PLL configuration. */
    CGC_LPAV->PLL4CFG = CGC_LPAV_PLL4CFG_SOURCE(config->src) | CGC_LPAV_PLL4CFG_MULT(config->mult);

    /* Step 3. Set Numerator and Denominator. */
    CGC_LPAV->PLL4DENOM = config->denom;
    CGC_LPAV->PLL4NUM   = config->num;

    /* Step 4. Enable clock. */
    CGC_LPAV->PLL4CSR = (uint32_t)CGC_LPAV_PLL4CSR_PLLEN_MASK | config->enableMode;

    /* Step 5. Wait for PLL clock to be valid. */
    while (0UL == (CGC_LPAV->PLL4CSR & CGC_LPAV_PLL4CSR_PLLVLD_MASK))
    {
    }

    return kStatus_Success;
}

/*!
 * @brief De-initializes the CGC PLL4.
 *
 * This function disables the CGC PLL4.
 *
 * @retval kStatus_Success PLL4 is deinitialized.
 * @retval kStatus_CGC_Busy PLL4 is used by the system clock.
 * @retval kStatus_ReadOnly PLL4 control register is locked.
 *
 * @note This function can't detect whether the PLL4 is used by an IP.
 */
status_t CLOCK_DeinitPll4(void)
{
    uint32_t reg = CGC_LPAV->PLL4CSR;
    status_t status;

    /* If clock is used by system, return error. */
    if ((reg & CGC_LPAV_PLL4CSR_PLLSEL_MASK) != 0UL)
    {
        status = kStatus_CGC_Busy;
    }
    /* If configure register is locked, return error. */
    else if ((reg & CGC_LPAV_PLL4CSR_LK_MASK) != 0UL)
    {
        status = kStatus_ReadOnly;
    }
    else
    {
        /* Deinit and clear the error. */
        CGC_LPAV->PLL4CSR = 0;
        status            = kStatus_Success;
    }

    return status;
}

/*!
 * @brief Set the asynchronous clock divider.
 *
 * @param asyncClk Which asynchronous clock to configure.
 * @param divider The divider value to set. Disabled when divider == 0.
 *
 * @note There might be glitch when changing the asynchronous divider, so make sure
 * the asynchronous clock is not used while changing divider.
 */
void CLOCK_SetPll4AsyncClkDiv(cgc_async_clk_t asyncClk, uint8_t divider)
{
    uint32_t reg;

    switch (asyncClk)
    {
        case kCGC_AsyncVcoClk:
            reg = CGC_LPAV->PLL4DIV_VCO;
            reg =
                (reg & ~(CGC_LPAV_PLL4DIV_VCO_DIV1_MASK | CGC_LPAV_PLL4DIV_VCO_DIV1HALT_MASK)) |
                (divider > 0U ? CGC_LPAV_PLL4DIV_VCO_DIV1((uint32_t)divider - 1U) : CGC_LPAV_PLL4DIV_VCO_DIV1HALT_MASK);
            CGC_LPAV->PLL4DIV_VCO = reg;
            break;
        case kCGC_AsyncPfd0Div1Clk:
            reg = CGC_LPAV->PLL4DIV_PFD_0;
            reg = (reg & ~(CGC_LPAV_PLL4DIV_PFD_0_DIV1_MASK | CGC_LPAV_PLL4DIV_PFD_0_DIV1HALT_MASK)) |
                  (divider > 0U ? CGC_LPAV_PLL4DIV_PFD_0_DIV1((uint32_t)divider - 1U) :
                                  CGC_LPAV_PLL4DIV_PFD_0_DIV1HALT_MASK);
            CGC_LPAV->PLL4DIV_PFD_0 = reg;
            break;
        case kCGC_AsyncPfd0Div2Clk:
            reg = CGC_LPAV->PLL4DIV_PFD_0;
            reg = (reg & ~(CGC_LPAV_PLL4DIV_PFD_0_DIV2_MASK | CGC_LPAV_PLL4DIV_PFD_0_DIV2HALT_MASK)) |
                  (divider > 0U ? CGC_LPAV_PLL4DIV_PFD_0_DIV2((uint32_t)divider - 1U) :
                                  CGC_LPAV_PLL4DIV_PFD_0_DIV2HALT_MASK);
            CGC_LPAV->PLL4DIV_PFD_0 = reg;
            break;
        case kCGC_AsyncPfd1Div1Clk:
            reg = CGC_LPAV->PLL4DIV_PFD_0;
            reg = (reg & ~(CGC_LPAV_PLL4DIV_PFD_0_DIV3_MASK | CGC_LPAV_PLL4DIV_PFD_0_DIV3HALT_MASK)) |
                  (divider > 0U ? CGC_LPAV_PLL4DIV_PFD_0_DIV3((uint32_t)divider - 1U) :
                                  CGC_LPAV_PLL4DIV_PFD_0_DIV3HALT_MASK);
            CGC_LPAV->PLL4DIV_PFD_0 = reg;
            break;
        case kCGC_AsyncPfd1Div2Clk:
            reg = CGC_LPAV->PLL4DIV_PFD_0;
            reg = (reg & ~(CGC_LPAV_PLL4DIV_PFD_0_DIV4_MASK | CGC_LPAV_PLL4DIV_PFD_0_DIV4HALT_MASK)) |
                  (divider > 0U ? CGC_LPAV_PLL4DIV_PFD_0_DIV4((uint32_t)divider - 1U) :
                                  CGC_LPAV_PLL4DIV_PFD_0_DIV4HALT_MASK);
            CGC_LPAV->PLL4DIV_PFD_0 = reg;
            break;
        case kCGC_AsyncPfd2Div1Clk:
            reg = CGC_LPAV->PLL4DIV_PFD_1;
            reg = (reg & ~(CGC_LPAV_PLL4DIV_PFD_1_DIV1_MASK | CGC_LPAV_PLL4DIV_PFD_1_DIV1HALT_MASK)) |
                  (divider > 0U ? CGC_LPAV_PLL4DIV_PFD_1_DIV1((uint32_t)divider - 1U) :
                                  CGC_LPAV_PLL4DIV_PFD_1_DIV1HALT_MASK);
            CGC_LPAV->PLL4DIV_PFD_1 = reg;
            break;
        case kCGC_AsyncPfd2Div2Clk:
            reg = CGC_LPAV->PLL4DIV_PFD_1;
            reg = (reg & ~(CGC_LPAV_PLL4DIV_PFD_1_DIV2_MASK | CGC_LPAV_PLL4DIV_PFD_1_DIV2HALT_MASK)) |
                  (divider > 0U ? CGC_LPAV_PLL4DIV_PFD_1_DIV2((uint32_t)divider - 1U) :
                                  CGC_LPAV_PLL4DIV_PFD_1_DIV2HALT_MASK);
            CGC_LPAV->PLL4DIV_PFD_1 = reg;
            break;
        case kCGC_AsyncPfd3Div1Clk:
            reg = CGC_LPAV->PLL4DIV_PFD_1;
            reg = (reg & ~(CGC_LPAV_PLL4DIV_PFD_1_DIV3_MASK | CGC_LPAV_PLL4DIV_PFD_1_DIV3HALT_MASK)) |
                  (divider > 0U ? CGC_LPAV_PLL4DIV_PFD_1_DIV3((uint32_t)divider - 1U) :
                                  CGC_LPAV_PLL4DIV_PFD_1_DIV3HALT_MASK);
            CGC_LPAV->PLL4DIV_PFD_1 = reg;
            break;
        case kCGC_AsyncPfd3Div2Clk:
            reg = CGC_LPAV->PLL4DIV_PFD_1;
            reg = (reg & ~(CGC_LPAV_PLL4DIV_PFD_1_DIV4_MASK | CGC_LPAV_PLL4DIV_PFD_1_DIV4HALT_MASK)) |
                  (divider > 0U ? CGC_LPAV_PLL4DIV_PFD_1_DIV4((uint32_t)divider - 1U) :
                                  CGC_LPAV_PLL4DIV_PFD_1_DIV4HALT_MASK);
            CGC_LPAV->PLL4DIV_PFD_1 = reg;
            break;
        default:
            assert(false);
            break;
    }
}

static uint32_t CLOCK_GetPll4CommonFreq(void)
{
    uint32_t freq = 0U;
    uint64_t freqTmp;
    uint64_t pllnumTmp;

    if ((CGC_LPAV->PLL4CFG & CGC_LPAV_PLL4CFG_SOURCE_MASK) != 0UL) /* If use FRO24M */
    {
        freq = CLOCK_GetFroFreq() / 8U;
    }
    else /* Use System OSC. */
    {
        freq = CLOCK_GetSysOscFreq();
    }

    if (freq != 0UL) /* If source is valid. */
    {
        pllnumTmp = (uint64_t)CGC_LPAV_PLL4NUM_NUM_VAL;
        freqTmp   = (uint64_t)freq * pllnumTmp / CGC_LPAV_PLL4DENOM_DENOM_VAL;
        freq      = freq * CGC_LPAV_PLL4CFG_MULT_VAL + (uint32_t)freqTmp;
    }

    return freq;
}

/*!
 * brief Gets CGC PLL4 clock frequency.
 *
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetPll4Freq(void)
{
    uint32_t freq;

    if ((CGC_LPAV->PLL4CSR & CGC_LPAV_PLL4CSR_PLLVLD_MASK) != 0UL) /* PLL4 is valid. */
    {
        freq = CLOCK_GetPll4CommonFreq();
    }
    else
    {
        freq = 0U;
    }

    return freq;
}

/*!
 * brief Gets the CGC asynchronous clock frequency from PLL4.
 *
 * param type     The asynchronous clock type.
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetPll4AsyncFreq(cgc_async_clk_t type)
{
    uint32_t pllFreq;
    uint32_t divider;
    uint32_t freq;

    switch (type)
    {
        case kCGC_AsyncVcoClk: /* PLL4 VCO. */
            pllFreq = CLOCK_GetPll4Freq();
            divider = CGC_LPAV_PLL4DIV_VCO_DIV1_VAL;
            break;
        case kCGC_AsyncPfd0Div1Clk: /* PLL4 PFD0 DIV1. */
            pllFreq = CLOCK_GetPll4PfdFreq(kCGC_PllPfd0Clk);
            divider = CGC_LPAV_PLL4DIV_PFD0_DIV1_VAL;
            break;
        case kCGC_AsyncPfd0Div2Clk: /* PLL4 PFD0 DIV2. */
            pllFreq = CLOCK_GetPll4PfdFreq(kCGC_PllPfd0Clk);
            divider = CGC_LPAV_PLL4DIV_PFD0_DIV2_VAL;
            break;
        case kCGC_AsyncPfd1Div1Clk: /* PLL4 PFD1 DIV1. */
            pllFreq = CLOCK_GetPll4PfdFreq(kCGC_PllPfd1Clk);
            divider = CGC_LPAV_PLL4DIV_PFD1_DIV1_VAL;
            break;
        case kCGC_AsyncPfd1Div2Clk: /* PLL4 PFD1 DIV2. */
            pllFreq = CLOCK_GetPll4PfdFreq(kCGC_PllPfd1Clk);
            divider = CGC_LPAV_PLL4DIV_PFD1_DIV2_VAL;
            break;
        case kCGC_AsyncPfd2Div1Clk: /* PLL4 PFD2 DIV1. */
            pllFreq = CLOCK_GetPll4PfdFreq(kCGC_PllPfd2Clk);
            divider = CGC_LPAV_PLL4DIV_PFD2_DIV1_VAL;
            break;
        case kCGC_AsyncPfd2Div2Clk: /* PLL4 PFD2 DIV2. */
            pllFreq = CLOCK_GetPll4PfdFreq(kCGC_PllPfd2Clk);
            divider = CGC_LPAV_PLL4DIV_PFD2_DIV2_VAL;
            break;
        case kCGC_AsyncPfd3Div1Clk: /* PLL4 PFD3 DIV1. */
            pllFreq = CLOCK_GetPll4PfdFreq(kCGC_PllPfd3Clk);
            divider = CGC_LPAV_PLL4DIV_PFD3_DIV1_VAL;
            break;
        case kCGC_AsyncPfd3Div2Clk: /* PLL4 PFD3 DIV2. */
            pllFreq = CLOCK_GetPll4PfdFreq(kCGC_PllPfd3Clk);
            divider = CGC_LPAV_PLL4DIV_PFD3_DIV2_VAL;
            break;
        default:
            divider = 0U;
            assert(false);
            break;
    }

    if (divider != 0UL)
    {
        freq = pllFreq / divider;
    }
    else /* Output disabled. */
    {
        freq = 0U;
    }

    return freq;
}

/*!
 * brief Gets the CGC PLL4 PFD clock frequency.
 *
 * param pfdClkout     The selected PFD clocks out. See "cgc_pll_pfd_clkout_t".
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetPll4PfdFreq(cgc_pll_pfd_clkout_t pfdClkout)
{
    uint32_t freq      = 0U;
    uint32_t fracValue = 0U;

    if ((CGC_LPAV->PLL4PFDCFG & CGC_PLLPFD_PFD_VALID_MASK(pfdClkout)) != 0UL) /* PLL4 PFD is valid. */
    {
        if (0UL == (CGC_LPAV->PLL4PFDCFG & CGC_PLLPFD_PFD_CLKGATE_MASK(pfdClkout)))
        {
            fracValue = (CGC_LPAV->PLL4PFDCFG & CGC_PLLPFD_PFD_MASK(pfdClkout)) >> (uint32_t)pfdClkout;

            if (fracValue != 0UL)
            {
                freq = CLOCK_GetPll4CommonFreq();
                freq = (uint32_t)((uint64_t)freq * PFD_FREQ_CALCUL_CONSTANT /
                                  fracValue); /* PFD Clock Frequency = PLL output frequency * 18 / frac value. */
            }
            else
            {
            }
        }
        else
        {
        }
    }
    else
    {
    }

    return freq;
}

/*!
 * @brief Enables the CGC PLL4 Fractional Divide (PFD) clock out with configurations.
 *
 * PLL4 Frequency = Fref * (MULT + NUM/DENOM)
 * PFD Clock Frequency = PLL output frequency * 18/frac value
 *
 * Example code for configuring PLL4 as PLL4 PFD clock output:
 * @code
 * const cgc_pll4_config_t g_cgcPll4Config = {.enableMode = kCGC_PllEnable,
 *                                            .div1 = 0U,
 *                                            .pfd0Div1 = 0U,
 *                                            .pfd0Div2 = 0U,
 *                                            .pfd1Div1 = 0U,
 *                                            .pfd1Div2 = 0U,
 *                                            .pfd2Div1 = 0U,
 *                                            .pfd2Div2 = 0U,
 *                                            .pfd3Div1 = 0U,
 *                                            .pfd3Div2 = 0U,
 *                                            .src = kCGC_PllSrcFro24M,
 *                                            .mult = kCGC_Pll4Mult22,
 *                                            .num = 578,
 *                                            .denom = 1000};
 * CLOCK_InitPll4(&g_cgcPll4Config);
 * CLOCK_EnablePll4PfdClkout(kCGC_PllPfd0Clk, 15U);
 * @endcode
 *
 * @param pfdClkout  PLL4 PFD clock out select.
 * @param fracValue  Fractional Divider value. Recommended to be kept between 12-35 for all PFDs.
 */
void CLOCK_EnablePll4PfdClkout(cgc_pll_pfd_clkout_t pfdClkout, uint8_t fracValue)
{
    /*
     * Input fractional divider value should have a maximum size of 6 bits (64U).
     * Note: It is recommended that PFD settings are kept between 12-35 for all PFDs.
     */
    assert(fracValue);
    assert(fracValue < CGC_PLLPFD_PFD_MAX_VAL);

    /* Step 1. Gate PFD clock. */
    CGC_LPAV->PLL4PFDCFG |= CGC_PLLPFD_PFD_CLKGATE_MASK(pfdClkout);

    /* Step 2. Program the new PFD value. */
    CGC_LPAV->PLL4PFDCFG =
        (CGC_LPAV->PLL4PFDCFG & ~CGC_PLLPFD_PFD_MASK(pfdClkout)) | CGC_PLLPFD_PFD_VAL(pfdClkout, fracValue);

    /* Step 3. Ungate PFD clock. */
    CGC_LPAV->PLL4PFDCFG &= ~CGC_PLLPFD_PFD_CLKGATE_MASK(pfdClkout);

    /* Step 4. Wait for PFD clock to be stable. */
    while (0UL == (CGC_LPAV->PLL4PFDCFG & CGC_PLLPFD_PFD_VALID_MASK(pfdClkout)))
    {
    }
}

/*!
 * @brief Gets the WDOG clock frequency in RTD and LPAV.
 *
 * @param instance The WDOG instance (0-2, 5).
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetWdogClkFreq(uint32_t instance)
{
    uint32_t freq;
    uint32_t reg = 0U;

    switch (instance)
    {
        case 0:
            reg  = PCC_REG(kCLOCK_Wdog0);
            freq = CLOCK_GetPcc0BusFreq(PCC_PCS_VAL(reg));
            break;
        case 1:
            reg  = PCC_REG(kCLOCK_Wdog1);
            freq = CLOCK_GetPcc0BusFreq(PCC_PCS_VAL(reg));
            break;
        case 2:
            reg  = PCC_REG(kCLOCK_Wdog2);
            freq = CLOCK_GetPcc2BusFreq(PCC_PCS_VAL(reg));
            break;
        case 5:
            reg  = PCC_REG(kCLOCK_Wdog5);
            freq = CLOCK_GetPcc5BusFreq(PCC_PCS_VAL(reg));
            break;
        default:
            assert(false);
            freq = 0;
            break;
    }

    return freq * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
}

/*!
 * @brief Gets the FlexSPI clock frequency in RTD.
 *
 * @param instance The FlexSPI instance (0-1).
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetFlexspiClkFreq(uint32_t instance)
{
    uint32_t freq;
    uint32_t reg = 0U;

    switch (instance)
    {
        case 0:
            reg  = PCC_REG(kCLOCK_Flexspi0);
            freq = CLOCK_GetPcc0PlatFreq(PCC_PCS_VAL(reg));
            break;
        case 1:
            reg  = PCC_REG(kCLOCK_Flexspi1);
            freq = CLOCK_GetPcc0PlatFreq(PCC_PCS_VAL(reg));
            break;
        default:
            assert(false);
            freq = 0;
            break;
    }

    return freq * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
}

/*!
 * @brief Gets the LPIT clock frequency in RTD.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetLpitClkFreq(void)
{
    uint32_t freq;
    uint32_t reg;

    reg  = PCC_REG(kCLOCK_Lpit0);
    freq = CLOCK_GetPcc0BusFreq(PCC_PCS_VAL(reg));

    return freq * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
}

/*!
 * @brief Gets the FlexIO clock frequency in RTD.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetFlexioClkFreq(void)
{
    uint32_t freq;
    uint32_t reg;

    reg  = PCC_REG(kCLOCK_Flexio0);
    freq = CLOCK_GetPcc0BusFreq(PCC_PCS_VAL(reg));

    return freq * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
}

/*!
 * @brief Gets the I3C clock frequency in RTD and LPAV.
 *
 * @param instance The I3C instance (0-1).
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetI3cClkFreq(uint32_t instance)
{
    uint32_t freq;
    uint32_t reg = 0U;

    switch (instance)
    {
        case 0:
            reg  = PCC_REG(kCLOCK_I3c0);
            freq = CLOCK_GetPcc0BusFreq(PCC_PCS_VAL(reg));
            break;
        case 1:
            reg  = PCC_REG(kCLOCK_I3c1);
            freq = CLOCK_GetPcc2BusFreq(PCC_PCS_VAL(reg));
            break;
        default:
            assert(false);
            freq = 0;
            break;
    }

    return freq * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
}

/*!
 * @brief Gets the LPSPI clock frequency in RTD.
 *
 * @param instance The LPSPI instance (0-3).
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetLpspiClkFreq(uint32_t instance)
{
    uint32_t freq;
    uint32_t reg = 0U;

    switch (instance)
    {
        case 0:
            reg  = PCC_REG(kCLOCK_Lpspi0);
            freq = CLOCK_GetPcc0BusFreq(PCC_PCS_VAL(reg));
            break;
        case 1:
            reg  = PCC_REG(kCLOCK_Lpspi1);
            freq = CLOCK_GetPcc0BusFreq(PCC_PCS_VAL(reg));
            break;
        case 2:
            reg  = PCC_REG(kCLOCK_Lpspi2);
            freq = CLOCK_GetPcc2BusFreq(PCC_PCS_VAL(reg));
            break;
        case 3:
            reg  = PCC_REG(kCLOCK_Lpspi3);
            freq = CLOCK_GetPcc2BusFreq(PCC_PCS_VAL(reg));
            break;
        default:
            assert(false);
            freq = 0;
            break;
    }

    return freq * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
}

/*!
 * @brief Gets the ADC clock frequency.
 *
 * @param instance The ADC instance (0-1).
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetAdcClkFreq(uint32_t instance)
{
    uint32_t freq;
    uint32_t reg = 0U;

    switch (instance)
    {
        case 0:
            reg  = PCC_REG(kCLOCK_Adc0);
            freq = CLOCK_GetPcc0BusFreq(PCC_PCS_VAL(reg));
            break;
        case 1:
            reg  = PCC_REG(kCLOCK_Adc1);
            freq = CLOCK_GetPcc1BusFreq(PCC_PCS_VAL(reg));
            break;
        default:
            assert(false);
            freq = 0;
            break;
    }

    return freq * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
}

/*!
 * @brief Gets the DAC clock frequency.
 *
 * @param instance The DAC instance (0-1).
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetDacClkFreq(uint32_t instance)
{
    uint32_t freq;
    uint32_t reg = 0U;

    switch (instance)
    {
        case 0:
            reg  = PCC_REG(kCLOCK_Dac0);
            freq = CLOCK_GetPcc0BusFreq(PCC_PCS_VAL(reg));
            break;
        case 1:
            reg  = PCC_REG(kCLOCK_Dac1);
            freq = CLOCK_GetPcc0BusFreq(PCC_PCS_VAL(reg));
            break;
        default:
            assert(false);
            freq = 0;
            break;
    }

    return freq * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
}

/*!
 * @brief Gets the TPIU clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetTpiuClkFreq(void)
{
    uint32_t freq;
    uint32_t reg = PCC_REG(kCLOCK_Tpiu);

    freq = CLOCK_GetPcc0PlatFreq(PCC_PCS_VAL(reg));

    return freq * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
}

/*!
 * @brief Gets the SWO clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetSwoClkFreq(void)
{
    uint32_t freq;
    uint32_t reg = PCC_REG(kCLOCK_Swo);

    freq = CLOCK_GetPcc1PlatFreq(PCC_PCS_VAL(reg));

    return freq * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
}

static uint32_t CLOCK_GetTpm2ClkFreq(uint32_t pcs)
{
    uint32_t freq;
    uint32_t reg;

    switch (pcs)
    {
        case 0U:
            freq = CLOCK_GetPll1AsyncFreq(kCGC_AsyncPfd2Div1Clk);
            break;
        case 1U:
            freq = CLOCK_GetMclkFreq(1);
            break;
        default:
            reg = PCC_REG(kCLOCK_Tpm2);
            assert(pcs == 2U); /* Must be TPM2_PCC_ASYNC_CLK */
            freq = CLOCK_GetPcc2BusFreq(PCC_PCS_VAL(reg)) * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
            break;
    }

    return freq;
}

static uint32_t CLOCK_GetTpm3ClkFreq(uint32_t pcs)
{
    uint32_t freq;
    uint32_t reg;

    switch (pcs)
    {
        case 0U:
            freq = CLOCK_GetPll1AsyncFreq(kCGC_AsyncPfd2Div1Clk);
            break;
        case 1U:
            freq = CLOCK_GetRtdAudClkFreq();
            break;
        case 2U:
            freq = CLOCK_GetLpavAudClkFreq();
            break;
        default:
            reg = PCC_REG(kCLOCK_Tpm3);
            assert(pcs == 3U); /* Must be TPM3_PCC_ASYNC_CLK */
            freq = CLOCK_GetPcc2BusFreq(PCC_PCS_VAL(reg)) * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
            break;
    }

    return freq;
}

static uint32_t CLOCK_GetTpm67ClkFreq(clock_ip_name_t name, uint32_t pcs)
{
    uint32_t freq;
    uint32_t reg;

    switch (pcs)
    {
        case 0U:
            freq = CLOCK_GetPll3AsyncFreq(kCGC_AsyncPfd1Div1Clk);
            break;
        case 1U:
            freq = CLOCK_GetAdAudClkFreq();
            break;
        case 2U:
            freq = CLOCK_GetLpavAudClkFreq();
            break;
        default:
            reg = PCC_REG(name);
            assert(pcs == 3U); /* Must be TPM67_PCC_ASYNC_CLK */
            freq = CLOCK_GetPcc4BusFreq(PCC_PCS_VAL(reg)) * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
            break;
    }

    return freq;
}

static uint32_t CLOCK_GetTpm8ClkFreq(uint32_t pcs)
{
    uint32_t freq;
    uint32_t reg;

    switch (pcs)
    {
        case 0U:
            freq = CLOCK_GetPll1AsyncFreq(kCGC_AsyncPfd2Div1Clk);
            break;
        case 1U:
            freq = CLOCK_GetPll3AsyncFreq(kCGC_AsyncPfd1Div1Clk);
            break;
        case 2U:
            freq = CLOCK_GetRtdAudClkFreq();
            break;
        case 3U:
            freq = CLOCK_GetAdAudClkFreq();
            break;
        case 4U:
            freq = CLOCK_GetLpavAudClkFreq();
            break;
        default:
            reg = PCC_REG(kCLOCK_Tpm8);
            assert(pcs == 5U); /* Must be TPM8_PCC_ASYNC_CLK */
            freq = CLOCK_GetPcc5BusFreq(PCC_PCS_VAL(reg)) * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
            break;
    }

    return freq;
}

/*!
 * @brief Gets the TPM clock frequency in RTD and LPAV.
 *
 * @param instance The TPM instance (0-8).
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetTpmClkFreq(uint32_t instance)
{
    uint32_t freq;
    uint32_t pcs;
    uint32_t reg;

    switch (instance)
    {
        case 0:
            reg  = PCC_REG(kCLOCK_Tpm0);
            freq = CLOCK_GetPcc1BusFreq(PCC_PCS_VAL(reg)) * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
            break;
        case 1:
            reg  = PCC_REG(kCLOCK_Tpm1);
            freq = CLOCK_GetPcc1BusFreq(PCC_PCS_VAL(reg)) * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
            break;
        case 2:
            pcs  = (CGC_RTD->TPM3_2CLK & CGC_TPM3_2CLK_TPM2CLK_MASK) >> CGC_TPM3_2CLK_TPM2CLK_SHIFT;
            freq = CLOCK_GetTpm2ClkFreq(pcs);
            break;
        case 3:
            pcs  = (CGC_RTD->TPM3_2CLK & CGC_TPM3_2CLK_TPM3CLK_MASK) >> CGC_TPM3_2CLK_TPM3CLK_SHIFT;
            freq = CLOCK_GetTpm3ClkFreq(pcs);
            break;
        case 4:
            reg  = PCC_REG(kCLOCK_Tpm4);
            freq = CLOCK_GetPcc3BusFreq(PCC_PCS_VAL(reg)) * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
            break;
        case 5:
            reg  = PCC_REG(kCLOCK_Tpm5);
            freq = CLOCK_GetPcc3BusFreq(PCC_PCS_VAL(reg)) * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
            break;
        case 6:
            pcs  = (CGC_AD->TPM6_7CLK & CGC_AD_TPM6_7CLK_TPM6CLK_MASK) >> CGC_AD_TPM6_7CLK_TPM6CLK_SHIFT;
            freq = CLOCK_GetTpm67ClkFreq(kCLOCK_Tpm6, pcs);
            break;
        case 7:
            pcs  = (CGC_AD->TPM6_7CLK & CGC_AD_TPM6_7CLK_TPM7CLK_MASK) >> CGC_AD_TPM6_7CLK_TPM7CLK_SHIFT;
            freq = CLOCK_GetTpm67ClkFreq(kCLOCK_Tpm7, pcs);
            break;
        case 8:
            pcs  = (CGC_LPAV->TPM8CLK & CGC_LPAV_TPM8CLK_TPM8CLK_MASK) >> CGC_LPAV_TPM8CLK_TPM8CLK_SHIFT;
            freq = CLOCK_GetTpm8ClkFreq(pcs);
            break;
        default:
            assert(false);
            freq = 0;
            break;
    }

    return freq;
}

/*!
 * @brief Gets the LPI2C clock frequency in RTD.
 *
 * @param instance The LPI2C instance (0-3).
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetLpi2cClkFreq(uint32_t instance)
{
    uint32_t freq;
    uint32_t reg = 0U;

    switch (instance)
    {
        case 0:
            reg  = PCC_REG(kCLOCK_Lpi2c0);
            freq = CLOCK_GetPcc1BusFreq(PCC_PCS_VAL(reg));
            break;
        case 1:
            reg  = PCC_REG(kCLOCK_Lpi2c1);
            freq = CLOCK_GetPcc1BusFreq(PCC_PCS_VAL(reg));
            break;
        case 2:
            reg  = PCC_REG(kCLOCK_Lpi2c2);
            freq = CLOCK_GetPcc2BusFreq(PCC_PCS_VAL(reg));
            break;
        case 3:
            reg  = PCC_REG(kCLOCK_Lpi2c3);
            freq = CLOCK_GetPcc2BusFreq(PCC_PCS_VAL(reg));
            break;
        default:
            assert(false);
            freq = 0;
            break;
    }

    return freq * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
}

/*!
 * @brief Gets the LPUART clock frequency in RTD.
 *
 * @param instance The LPUART instance (0-3).
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetLpuartClkFreq(uint32_t instance)
{
    uint32_t freq;
    uint32_t reg = 0U;

    switch (instance)
    {
        case 0:
            reg  = PCC_REG(kCLOCK_Lpuart0);
            freq = CLOCK_GetPcc1BusFreq(PCC_PCS_VAL(reg));
            break;
        case 1:
            reg  = PCC_REG(kCLOCK_Lpuart1);
            freq = CLOCK_GetPcc1BusFreq(PCC_PCS_VAL(reg));
            break;
        case 2:
            reg  = PCC_REG(kCLOCK_Lpuart2);
            freq = CLOCK_GetPcc2BusFreq(PCC_PCS_VAL(reg));
            break;
        case 3:
            reg  = PCC_REG(kCLOCK_Lpuart3);
            freq = CLOCK_GetPcc2BusFreq(PCC_PCS_VAL(reg));
            break;
        default:
            assert(false);
            freq = 0;
            break;
    }

    return freq * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
}

/*!
 * @brief Gets the FlexCAN clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetFlexcanClkFreq(void)
{
    uint32_t reg = PCC_REG(kCLOCK_Flexcan);
    return CLOCK_GetPcc1BusFreq(PCC_PCS_VAL(reg)) * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
}

/*!
 * @brief Gets the CSI clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetCsiClkFreq(void)
{
    uint32_t reg = PCC_REG(kCLOCK_Csi);
    return CLOCK_GetPcc5PlatFreq(PCC_PCS_VAL(reg)) * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
}

/*!
 * @brief Gets the DSI clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetDsiClkFreq(void)
{
    uint32_t reg = PCC_REG(kCLOCK_Dsi);
    return CLOCK_GetPcc5PlatFreq(PCC_PCS_VAL(reg)) * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
}

/*!
 * @brief Gets the EPDC clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetEpdcClkFreq(void)
{
    uint32_t reg = PCC_REG(kCLOCK_Epdc);
    return CLOCK_GetPcc5PlatFreq(PCC_PCS_VAL(reg)) * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
}

/*!
 * @brief Gets the GPU2D clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetGpu2dClkFreq(void)
{
    uint32_t reg = PCC_REG(kCLOCK_Gpu2d);
    return CLOCK_GetPcc5PlatFreq(PCC_PCS_VAL(reg)) * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
}

/*!
 * @brief Gets the GPU3D clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetGpu3dClkFreq(void)
{
    uint32_t reg = PCC_REG(kCLOCK_Gpu3d);
    return CLOCK_GetPcc5PlatFreq(PCC_PCS_VAL(reg)) * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
}

/*!
 * @brief Gets the DC Nano clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetDcnanoClkFreq(void)
{
    uint32_t reg = PCC_REG(kCLOCK_Dcnano);
    return CLOCK_GetPcc5PlatFreq(PCC_PCS_VAL(reg)) * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
}

/*!
 * @brief Gets the CSI clk_ui clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetCsiUiClkFreq(void)
{
    uint32_t reg = PCC_REG(kCLOCK_CsiClkUi);
    return CLOCK_GetPcc5PlatFreq(PCC_PCS_VAL(reg)) * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
}

/*!
 * @brief Gets the CSI clk_esc clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetCsiEscClkFreq(void)
{
    uint32_t reg = PCC_REG(kCLOCK_CsiClkEsc);
    return CLOCK_GetPcc5PlatFreq(PCC_PCS_VAL(reg)) * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
}

/* Get selected audio clock frequency for SAI0-1, MQS0. */
static uint32_t CLOCK_GetCm33SaiClkFreq(uint32_t src)
{
    uint32_t freq;

    switch (src)
    {
        case 0U:
            freq = CLOCK_GetPll1AsyncFreq(kCGC_AsyncPfd2Div1Clk);
            break;
        case 1U:
            freq = CLOCK_GetRtdAudClkFreq();
            break;
        case 2U:
            freq = CLOCK_GetLpavAudClkFreq();
            break;
        case 3U:
            freq = CLOCK_GetSysOscFreq();
            break;
        default:
            assert(false);
            freq = 0U;
            break;
    }

    return freq;
}

/* Get selected audio clock frequency for SAI2-3. */
static uint32_t CLOCK_GetFusionSaiClkFreq(uint32_t instance, uint32_t src)
{
    uint32_t freq;

    switch (src)
    {
        case 0U:
            freq = CLOCK_GetPll1AsyncFreq(kCGC_AsyncPfd2Div1Clk);
            break;
        case 1U:
            freq = CLOCK_GetMclkFreq(1);
            break;
        case 2U:
            freq = (instance == 2U) ? CLOCK_GetSaiRxBclkFreq(3) : CLOCK_GetSaiTxBclkFreq(2);
            break;
        case 3U:
            freq = CLOCK_GetSysOscFreq();
            break;
        default:
            assert(false);
            freq = 0U;
            break;
    }

    return freq;
}

/* Get selected audio clock frequency for SAI4-5, MQS1. */
static uint32_t CLOCK_GetAdSaiClkFreq(uint32_t src)
{
    uint32_t freq;

    switch (src)
    {
        case 0U:
            freq = CLOCK_GetPll3AsyncFreq(kCGC_AsyncPfd1Div1Clk);
            break;
        case 1U:
            freq = CLOCK_GetAdAudClkFreq();
            break;
        case 2U:
            freq = CLOCK_GetLpavAudClkFreq();
            break;
        case 3U:
            freq = CLOCK_GetSysOscFreq();
            break;
        default:
            assert(false);
            freq = 0U;
            break;
    }

    return freq;
}

/* Get selected audio clock frequency for SAI6-7, SPDIF. */
static uint32_t CLOCK_GetLpavSaiClkFreq(uint32_t src)
{
    uint32_t freq;

    switch (src)
    {
        case 0U:
            freq = CLOCK_GetPll1AsyncFreq(kCGC_AsyncPfd2Div1Clk);
            break;
        case 1U:
            freq = CLOCK_GetPll3AsyncFreq(kCGC_AsyncPfd1Div1Clk);
            break;
        case 2U:
            freq = CLOCK_GetRtdAudClkFreq();
            break;
        case 3U:
            freq = CLOCK_GetAdAudClkFreq();
            break;
        case 4U:
            freq = CLOCK_GetLpavAudClkFreq();
            break;
        case 5U:
            freq = CLOCK_GetSysOscFreq();
            break;
        default:
            assert(false);
            freq = 0U;
            break;
    }

    return freq;
}

/*!
 * @brief Gets the audio clock frequency in RTD.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetRtdAudClkFreq(void)
{
    uint32_t freq;

    switch (CGC_RTD->AUD_CLK0 & CGC_AUD_CLK0_AUD_CLK0_MASK)
    {
        case (uint32_t)kCGC_RtdAudClkSrcExtMclk0:
            freq = CLOCK_GetMclkFreq(0);
            break;
        case (uint32_t)kCGC_RtdAudClkSrcExtMclk1:
            freq = CLOCK_GetMclkFreq(1);
            break;
        case (uint32_t)kCGC_RtdAudClkSrcSai0RxBclk:
            freq = CLOCK_GetSaiRxBclkFreq(0);
            break;
        case (uint32_t)kCGC_RtdAudClkSrcSai0TxBclk:
            freq = CLOCK_GetSaiTxBclkFreq(0);
            break;
        case (uint32_t)kCGC_RtdAudClkSrcSai1RxBclk:
            freq = CLOCK_GetSaiRxBclkFreq(1);
            break;
        case (uint32_t)kCGC_RtdAudClkSrcSai1TxBclk:
            freq = CLOCK_GetSaiTxBclkFreq(1);
            break;
        case (uint32_t)kCGC_RtdAudClkSrcSai2RxBclk:
            freq = CLOCK_GetSaiRxBclkFreq(2);
            break;
        case (uint32_t)kCGC_RtdAudClkSrcSai2TxBclk:
            freq = CLOCK_GetSaiTxBclkFreq(2);
            break;
        case (uint32_t)kCGC_RtdAudClkSrcSai3RxBclk:
            freq = CLOCK_GetSaiRxBclkFreq(3);
            break;
        case (uint32_t)kCGC_RtdAudClkSrcSai3TxBclk:
            freq = CLOCK_GetSaiTxBclkFreq(3);
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

/*!
 * @brief Gets the audio clock frequency in AD.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetAdAudClkFreq(void)
{
    uint32_t freq;

    switch (CGC_AD->AUD_CLK1 & CGC_AD_AUD_CLK1_AUD_CLK1_MASK)
    {
        case (uint32_t)kCGC_AdAudClkSrcExtMclk2:
            freq = CLOCK_GetMclkFreq(2);
            break;
        case (uint32_t)kCGC_AdAudClkSrcSai4RxBclk:
            freq = CLOCK_GetSaiRxBclkFreq(4);
            break;
        case (uint32_t)kCGC_AdAudClkSrcSai4TxBclk:
            freq = CLOCK_GetSaiTxBclkFreq(4);
            break;
        case (uint32_t)kCGC_AdAudClkSrcSai5RxBclk:
            freq = CLOCK_GetSaiRxBclkFreq(5);
            break;
        case (uint32_t)kCGC_AdAudClkSrcSai5TxBclk:
            freq = CLOCK_GetSaiTxBclkFreq(5);
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

/*!
 * @brief Gets the audio clock frequency in LPAV.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetLpavAudClkFreq(void)
{
    uint32_t freq;

    switch (CGC_LPAV->AUD_CLK2 & CGC_LPAV_AUD_CLK2_AUD_CLK2_MASK)
    {
        case (uint32_t)kCGC_LpavAudClkSrcExtMclk3:
            freq = CLOCK_GetMclkFreq(3);
            break;
        case (uint32_t)kCGC_LpavAudClkSrcSai6RxBclk:
            freq = CLOCK_GetSaiRxBclkFreq(6);
            break;
        case (uint32_t)kCGC_LpavAudClkSrcSai6TxBclk:
            freq = CLOCK_GetSaiTxBclkFreq(6);
            break;
        case (uint32_t)kCGC_LpavAudClkSrcSai7RxBclk:
            freq = CLOCK_GetSaiRxBclkFreq(7);
            break;
        case (uint32_t)kCGC_LpavAudClkSrcSai7TxBclk:
            freq = CLOCK_GetSaiTxBclkFreq(7);
            break;
        case (uint32_t)kCGC_LpavAudClkSrcSpdifRx:
            freq = CLOCK_GetSpdifRxFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

/*!
 * @brief Gets the SAI clock frequency.
 *
 * @param instance The SAI instance (0-7).
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetSaiFreq(uint32_t instance)
{
    uint32_t src;
    uint32_t freq;

    if (instance <= 1U)
    {
        src  = (CGC_RTD->SAI3_0_CLK & ((uint32_t)CGC_SAI3_0_CLK_SAI0CLK_MASK << (8U * instance))) >> (8U * instance);
        freq = CLOCK_GetCm33SaiClkFreq(src);
    }
    else if (instance <= 3U)
    {
        src  = (CGC_RTD->SAI3_0_CLK & ((uint32_t)CGC_SAI3_0_CLK_SAI0CLK_MASK << (8U * instance))) >> (8U * instance);
        freq = CLOCK_GetFusionSaiClkFreq(instance, src);
    }
    else if (instance <= 5U)
    {
        instance -= 4U;
        src  = (CGC_AD->SAI5_4_CLK & ((uint32_t)CGC_AD_SAI5_4_CLK_SAI4CLK_MASK << (8U * instance))) >> (8U * instance);
        freq = CLOCK_GetAdSaiClkFreq(src);
    }
    else if (instance <= 7U)
    {
        instance -= 6U;
        src =
            (CGC_LPAV->SAI7_6_CLK & ((uint32_t)CGC_LPAV_SAI7_6_CLK_SAI6CLK_MASK << (8U * instance))) >> (8U * instance);
        freq = CLOCK_GetLpavSaiClkFreq(src);
    }
    else
    {
        freq = (uint32_t)0;
        assert(false);
    }

    return freq;
}

/*!
 * @brief Gets the SPDIF clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetSpdifFreq(void)
{
    return CLOCK_GetLpavSaiClkFreq(CGC_LPAV->SPDIFCLK & CGC_LPAV_SPDIFCLK_SPDIFCLK_MASK);
}

/*!
 * @brief Gets the MQS clock frequency.
 *
 * @param instance The MQS instance (0-1).
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetMqsFreq(uint32_t instance)
{
    uint32_t freq;

    if (instance == 0U)
    {
        freq = CLOCK_GetCm33SaiClkFreq(CGC_RTD->MQS0CLK & CGC_MQS0CLK_MQS0CLK_MASK);
    }
    else if (instance == 1U)
    {
        freq = CLOCK_GetAdSaiClkFreq(CGC_AD->MQS1CLK & CGC_AD_MQS1CLK_MQS1CLK_MASK);
    }
    else
    {
        assert(false);
        freq = 0U;
    }

    return freq;
}

/*!
 * @brief Gets the EMICFIL clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetMicfilFreq(void)
{
    uint32_t freq;

    switch (CGC_RTD->EMICFIL & CGC_EMICFIL_MICFILCLK_MASK)
    {
        case 0U:
            freq = CLOCK_GetPll1AsyncFreq(kCGC_AsyncPfd2Div1Clk);
            break;
        case 1U:
            freq = CLOCK_GetFroFreq() / 8U;
            break;
        case 2U:
            freq = CLOCK_GetSysOscFreq();
            break;
        case 3U:
            freq = CLOCK_GetMclkFreq(1);
            break;
        case 4U:
            freq = CLOCK_GetRtcOscFreq();
            break;
        case 5U:
            freq = CLOCK_GetLpOscFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

/*!
 * @brief Gets the MRT clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetMrtFreq(void)
{
    return CLOCK_GetFusionDspBusClkFreq();
}
