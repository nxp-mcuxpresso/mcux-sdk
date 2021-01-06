/*
** ###################################################################
**     Processors:          MIMX8MD6CVAHZ
**                          MIMX8MD6DVAJZ
**
**     Compilers:           Keil ARM C/C++ Compiler
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**
**     Reference manual:    IMX8MDQLQRM, Rev. 0, Jan. 2018
**     Version:             rev. 4.0, 2018-01-26
**     Build:               b180903
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2018 NXP
**     All rights reserved.
**
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2017-01-10)
**         Initial version.
**     - rev. 2.0 (2017-04-27)
**         Rev.B Header EAR1
**     - rev. 3.0 (2017-07-19)
**         Rev.C Header EAR2
**     - rev. 4.0 (2018-01-26)
**         Rev.D Header RFP
**
** ###################################################################
*/

/*!
 * @file MIMX8MD6_cm4
 * @version 4.0
 * @date 2018-01-26
 * @brief Device specific configuration file for MIMX8MD6_cm4 (implementation
 *        file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include "fsl_device_registers.h"

/*!
 * @brief CCM reg macros to extract corresponding registers bit field.
 */
#define CCM_BIT_FIELD_VAL(val, mask, shift) (((val)&mask) >> shift)

/*!
 * @brief CCM reg macros to get corresponding registers values.
 */
#define CCM_ANALOG_REG_VAL(base, off) (*((volatile uint32_t *)((uint32_t)(base) + (off))))

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
uint32_t GetFracPllFreq(const volatile uint32_t *base);
uint32_t GetSSCGPllFreq(const volatile uint32_t *base);

uint32_t GetFracPllFreq(const volatile uint32_t *base)
{
    uint32_t fracCfg0   = CCM_ANALOG_REG_VAL(base, 0U);
    uint32_t fracCfg1   = CCM_ANALOG_REG_VAL(base, 4U);
    uint32_t refClkFreq = 0U;
    uint64_t fracClk    = 0U;

    uint8_t refSel   = (uint8_t)CCM_BIT_FIELD_VAL(fracCfg0, CCM_ANALOG_AUDIO_PLL1_CFG0_PLL_REFCLK_SEL_MASK,
                                                CCM_ANALOG_AUDIO_PLL1_CFG0_PLL_REFCLK_SEL_SHIFT);
    uint8_t refDiv   = (uint8_t)CCM_BIT_FIELD_VAL(fracCfg0, CCM_ANALOG_AUDIO_PLL1_CFG0_PLL_REFCLK_DIV_VAL_MASK,
                                                CCM_ANALOG_AUDIO_PLL1_CFG0_PLL_REFCLK_DIV_VAL_SHIFT);
    uint8_t outDiv   = (uint8_t)CCM_BIT_FIELD_VAL(fracCfg0, CCM_ANALOG_AUDIO_PLL1_CFG0_PLL_OUTPUT_DIV_VAL_MASK,
                                                CCM_ANALOG_AUDIO_PLL1_CFG0_PLL_OUTPUT_DIV_VAL_SHIFT);
    uint32_t fracDiv = CCM_BIT_FIELD_VAL(fracCfg1, CCM_ANALOG_AUDIO_PLL1_CFG1_PLL_FRAC_DIV_CTL_MASK,
                                         CCM_ANALOG_AUDIO_PLL1_CFG1_PLL_FRAC_DIV_CTL_SHIFT);
    uint8_t intDiv   = (uint8_t)CCM_BIT_FIELD_VAL(fracCfg1, CCM_ANALOG_AUDIO_PLL1_CFG1_PLL_INT_DIV_CTL_MASK,
                                                CCM_ANALOG_AUDIO_PLL1_CFG1_PLL_INT_DIV_CTL_SHIFT);

    if (refSel == 0U) /* OSC 25M Clock */
    {
        refClkFreq = CPU_XTAL_SOSC_CLK_25MHZ;
    }
    else if ((refSel == 1U) || /* OSC 27M Clock */
             (refSel == 2U))   /* HDMI_PYH 27M Clock */
    {
        refClkFreq = CPU_XTAL_SOSC_CLK_27MHZ;
    }
    else
    {
        refClkFreq = CLK_P_N_FREQ; /* CLK_P_N Clock, please note that the value is 0hz by default, it could be set at
                                      system_MIMX8MQx_cm4.h :88 */
    }
    refClkFreq /= (uint32_t)refDiv + 1U;
    fracClk = (uint64_t)refClkFreq * 8U * (1U + intDiv) + (((uint64_t)refClkFreq * 8U * fracDiv) >> 24U);

    return (uint32_t)(fracClk / (((uint64_t)outDiv + 1U) * 2U));
}

uint32_t GetSSCGPllFreq(const volatile uint32_t *base)
{
    uint32_t sscgCfg0       = CCM_ANALOG_REG_VAL(base, 0U);
    uint32_t sscgCfg1       = CCM_ANALOG_REG_VAL(base, 4U);
    uint32_t sscgCfg2       = CCM_ANALOG_REG_VAL(base, 8U);
    uint32_t refClkFreq     = 0U;
    uint64_t pll2InputClock = 0U;

    uint8_t pll1Bypass = (uint8_t)CCM_BIT_FIELD_VAL(sscgCfg0, CCM_ANALOG_SYS_PLL1_CFG0_PLL_BYPASS1_MASK,
                                                    CCM_ANALOG_SYS_PLL1_CFG0_PLL_BYPASS1_SHIFT);
    uint8_t refSel     = (uint8_t)CCM_BIT_FIELD_VAL(sscgCfg0, CCM_ANALOG_SYS_PLL1_CFG0_PLL_REFCLK_SEL_MASK,
                                                CCM_ANALOG_SYS_PLL1_CFG0_PLL_REFCLK_SEL_SHIFT);
    uint8_t refDiv1    = (uint8_t)CCM_BIT_FIELD_VAL(sscgCfg2, CCM_ANALOG_SYS_PLL1_CFG2_PLL_REF_DIVR1_MASK,
                                                 CCM_ANALOG_SYS_PLL1_CFG2_PLL_REF_DIVR1_SHIFT) +
                      1U;
    uint8_t refDiv2 = (uint8_t)CCM_BIT_FIELD_VAL(sscgCfg2, CCM_ANALOG_SYS_PLL1_CFG2_PLL_REF_DIVR2_MASK,
                                                 CCM_ANALOG_SYS_PLL1_CFG2_PLL_REF_DIVR2_SHIFT) +
                      1U;
    uint8_t divf1 = (uint8_t)CCM_BIT_FIELD_VAL(sscgCfg2, CCM_ANALOG_SYS_PLL1_CFG2_PLL_FEEDBACK_DIVF1_MASK,
                                               CCM_ANALOG_SYS_PLL1_CFG2_PLL_FEEDBACK_DIVF1_SHIFT) +
                    1U;
    uint8_t divf2 = (uint8_t)CCM_BIT_FIELD_VAL(sscgCfg2, CCM_ANALOG_SYS_PLL1_CFG2_PLL_FEEDBACK_DIVF2_MASK,
                                               CCM_ANALOG_SYS_PLL1_CFG2_PLL_FEEDBACK_DIVF2_SHIFT) +
                    1U;
    uint8_t outDiv = (uint8_t)CCM_BIT_FIELD_VAL(sscgCfg2, CCM_ANALOG_SYS_PLL1_CFG2_PLL_OUTPUT_DIV_VAL_MASK,
                                                CCM_ANALOG_SYS_PLL1_CFG2_PLL_OUTPUT_DIV_VAL_SHIFT) +
                     1U;

    if (refSel == 0U) /* OSC 25M Clock */
    {
        refClkFreq = CPU_XTAL_SOSC_CLK_25MHZ;
    }
    else if ((refSel == 1U) || /* OSC 27M Clock */
             (refSel == 2U))   /* HDMI_PYH 27M Clock */
    {
        refClkFreq = CPU_XTAL_SOSC_CLK_27MHZ;
    }
    else
    {
        refClkFreq = CLK_P_N_FREQ; /* CLK_P_N Clock, please note that the value is 0hz by default, it could be set at
                                      system_MIMX8MQx_cm4.h :88 */
    }

    refClkFreq /= refDiv1;

    if (pll1Bypass != 0U)
    {
        pll2InputClock = refClkFreq;
    }
    else if ((sscgCfg1 & CCM_ANALOG_SYS_PLL1_CFG1_PLL_SSE_MASK) != 0U)
    {
        pll2InputClock = (uint64_t)refClkFreq * 8U * divf1 / refDiv2;
    }
    else
    {
        pll2InputClock = (uint64_t)refClkFreq * 2U * divf1 / refDiv2;
    }

    return (uint32_t)(pll2InputClock * divf2 / outDiv);
}

/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */

uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;

/* ----------------------------------------------------------------------------
   -- SystemInit()
   ---------------------------------------------------------------------------- */

void SystemInit(void)
{
#if ((__FPU_PRESENT == 1) && (__FPU_USED == 1))
    SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2)); /* set CP10, CP11 Full Access */
#endif                                                 /* ((__FPU_PRESENT == 1) && (__FPU_USED == 1)) */

    /* Initialize Cache */
    /* Enable Code Bus Cache */
    /* set command to invalidate all ways, and write GO bit to initiate command */
    LMEM->PCCCR |= LMEM_PCCCR_INVW1_MASK | LMEM_PCCCR_INVW0_MASK;
    LMEM->PCCCR |= LMEM_PCCCR_GO_MASK;
    /* Wait until the command completes */
    while ((LMEM->PCCCR & LMEM_PCCCR_GO_MASK) != 0U)
    {
    }
    /* Enable cache, enable write buffer */
    LMEM->PCCCR |= (LMEM_PCCCR_ENWRBUF_MASK | LMEM_PCCCR_ENCACHE_MASK);

    /* Enable System Bus Cache */
    /* set command to invalidate all ways, and write GO bit to initiate command */
    LMEM->PSCCR |= LMEM_PSCCR_INVW1_MASK | LMEM_PSCCR_INVW0_MASK;
    LMEM->PSCCR |= LMEM_PSCCR_GO_MASK;
    /* Wait until the command completes */
    while ((LMEM->PSCCR & LMEM_PSCCR_GO_MASK) != 0U)
    {
    }
    /* Enable cache, enable write buffer */
    LMEM->PSCCR |= (LMEM_PSCCR_ENWRBUF_MASK | LMEM_PSCCR_ENCACHE_MASK);

    __ISB();
    __DSB();

    SystemInitHook();
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate(void)
{
    volatile uint32_t *M4_ClockRoot = (volatile uint32_t *)(&(CCM)->ROOT[1].TARGET_ROOT);
    uint32_t pre  = ((*M4_ClockRoot & CCM_TARGET_ROOT_PRE_PODF_MASK) >> CCM_TARGET_ROOT_PRE_PODF_SHIFT) + 1U;
    uint32_t post = ((*M4_ClockRoot & CCM_TARGET_ROOT_POST_PODF_MASK) >> CCM_TARGET_ROOT_POST_PODF_SHIFT) + 1U;

    uint32_t freq = 0U;

    switch ((*M4_ClockRoot & CCM_TARGET_ROOT_MUX_MASK) >> CCM_TARGET_ROOT_MUX_SHIFT)
    {
        case 0U: /* OSC 25M Clock */
            freq = CPU_XTAL_SOSC_CLK_25MHZ;
            break;
        case 1U:                                                      /* System PLL2 DIV5 */
            freq = GetSSCGPllFreq(&(CCM_ANALOG->SYS_PLL2_CFG0)) / 5U; /* Get System PLL2 DIV5 freq */
            break;
        case 2U:                                                      /* System PLL2 DIV4 */
            freq = GetSSCGPllFreq(&(CCM_ANALOG->SYS_PLL2_CFG0)) / 4U; /* Get System PLL2 DIV4 freq */
            break;
        case 3U:                                                      /* System PLL1 DIV3 */
            freq = GetSSCGPllFreq(&(CCM_ANALOG->SYS_PLL1_CFG0)) / 3U; /* Get System PLL1 DIV3 freq */
            break;
        case 4U:                                                 /* System PLL1 */
            freq = GetSSCGPllFreq(&(CCM_ANALOG->SYS_PLL1_CFG0)); /* Get System PLL1 freq */
            break;
        case 5U:                                                   /* AUDIO PLL1 */
            freq = GetFracPllFreq(&(CCM_ANALOG->AUDIO_PLL1_CFG0)); /* Get AUDIO PLL1 freq */
            break;
        case 6U:                                                   /* VIDEO PLL1 */
            freq = GetFracPllFreq(&(CCM_ANALOG->VIDEO_PLL1_CFG0)); /* Get VIDEO PLL1 freq */
            break;
        case 7U:                                                 /* System PLL3 */
            freq = GetSSCGPllFreq(&(CCM_ANALOG->SYS_PLL3_CFG0)); /* Get System PLL3 freq */
            break;
        default:
            freq = CPU_XTAL_SOSC_CLK_25MHZ;
            break;
    }

    SystemCoreClock = freq / pre / post;
}

/* ----------------------------------------------------------------------------
   -- SystemInitHook()
   ---------------------------------------------------------------------------- */

__attribute__((weak)) void SystemInitHook(void)
{
    /* Void implementation of the weak function. */
}
