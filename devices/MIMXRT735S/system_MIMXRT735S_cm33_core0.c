/*
** ###################################################################
**     Processors:          MIMXRT735SGAWAR_cm33_core0
**                          MIMXRT735SGFOA_cm33_core0
**
**     Compilers:           GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**                          MCUXpresso Compiler
**
**     Reference manual:    iMXRT700RM Rev.2 DraftA, 05/2024
**     Version:             rev. 2.0, 2024-05-28
**     Build:               b240528
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2024 NXP
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2022-09-15)
**         Initial version.
**     - rev. 2.0 (2024-05-28)
**         Rev2 DraftA.
**
** ###################################################################
*/

/*!
 * @file MIMXRT735S_cm33_core0
 * @version 1.0
 * @date 2024-05-28
 * @brief Device specific configuration file for MIMXRT735S_cm33_core0
 *  (implementation file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"

/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */

uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;

/* ----------------------------------------------------------------------------
   -- SystemInit()
   ---------------------------------------------------------------------------- */

__attribute__((weak)) void SystemInit(void)
{
#if ((__FPU_PRESENT == 1) && (__FPU_USED == 1))
    SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2));    /* set CP10, CP11 Full Access in Secure mode */
#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
    SCB_NS->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2)); /* set CP10, CP11 Full Access in Non-secure mode */
#endif                                                    /* (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
#endif                                                    /* ((__FPU_PRESENT == 1) && (__FPU_USED == 1)) */

    SCB->CPACR |= ((3UL << 0 * 2) | (3UL << 1 * 2)); /* set CP0, CP1 Full Access in Secure mode (enable PowerQuad) */

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
    SCB_NS->CPACR |=
        ((3UL << 0 * 2) | (3UL << 1 * 2));    /* set CP0, CP1 Full Access in Non-secure mode (enable PowerQuad) */
#endif                                        /* (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

    SCB->NSACR |= ((3UL << 0) | (3UL << 10)); /* enable CP0, CP1, CP10, CP11 Non-secure Access */

    SYSCON0->DSPSTALL = SYSCON0_DSPSTALL_DSPSTALL_MASK;

    if ((XCACHE1->CCR & XCACHE_CCR_ENCACHE_MASK) == 0U) /* set XCACHE if not configured for code bus.*/
    {
        /* set command to invalidate all ways and write GO bit to initiate command */
        XCACHE1->CCR = XCACHE_CCR_INVW1_MASK | XCACHE_CCR_INVW0_MASK;
        XCACHE1->CCR |= XCACHE_CCR_GO_MASK;
        /* Wait until the command completes */
        while ((XCACHE1->CCR & XCACHE_CCR_GO_MASK) != 0U)
        {
        }
        /* Enable cache */
        XCACHE1->CCR = XCACHE_CCR_ENCACHE_MASK;

        __ISB();
        __DSB();
    }

#if STARTUP_XSPI0_CACHE_POLICY
    if ((CACHE64_CTRL0->CCR & CACHE64_CTRL_CCR_ENCACHE_MASK) == 0U)
    {
        /* Enable XSPI0 caches */
        CACHE64_POLSEL0->REG0_TOP = 0x07FFFC00UL;
        CACHE64_POLSEL0->POLSEL   = STARTUP_XSPI0_CACHE_POLICY;
        /* First, invalidate the entire cache. */
        CACHE64_CTRL0->CCR = CACHE64_CTRL_CCR_INVW0_MASK | CACHE64_CTRL_CCR_INVW1_MASK;
        CACHE64_CTRL0->CCR |= CACHE64_CTRL_CCR_GO_MASK;
        while ((CACHE64_CTRL0->CCR & CACHE64_CTRL_CCR_GO_MASK) != 0U)
        {
        }
        CACHE64_CTRL0->CCR = CACHE64_CTRL_CCR_ENCACHE_MASK;

        __ISB();
        __DSB();
    }
#endif

#if STARTUP_XSPI1_CACHE_POLICY
    if ((CACHE64_CTRL1->CCR & CACHE64_CTRL_CCR_ENCACHE_MASK) == 0U)
    {
        /* Enable XSPI0 caches */
        CACHE64_POLSEL1->REG0_TOP = 0x07FFFC00UL;
        CACHE64_POLSEL1->POLSEL   = STARTUP_XSPI1_CACHE_POLICY;
        /* First, invalidate the entire cache. */
        CACHE64_CTRL1->CCR = CACHE64_CTRL_CCR_INVW0_MASK | CACHE64_CTRL_CCR_INVW1_MASK;
        CACHE64_CTRL1->CCR |= CACHE64_CTRL_CCR_GO_MASK;
        while ((CACHE64_CTRL1->CCR & CACHE64_CTRL_CCR_GO_MASK) != 0U)
        {
        }
        CACHE64_CTRL1->CCR = CACHE64_CTRL_CCR_ENCACHE_MASK;

        __ISB();
        __DSB();
    }
#endif

    SystemInitHook();
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

static uint32_t getFro0MaxFreq(void)
{
    return CLK_FRO0_CLK;
}

static uint32_t getFro1MaxFreq(void)
{
    return CLK_FRO1_MAX_CLK;
}

static uint32_t getFro1Div3Freq(void)
{
    return getFro1MaxFreq() / 3U;
}

static uint32_t getFro0Div3Freq(void)
{
    return getFro0MaxFreq() / 3U;
}

static uint32_t getLpOscFreq(void)
{
    return CLK_LPOSC_1MHZ;
}

static uint32_t getBaseClkCmpt(void)
{
    uint32_t freq = 0U;

    switch (CLKCTL0->CMPTBASECLKSEL & CLKCTL0_CMPTBASECLKSEL_SEL_MASK)
    {
        case CLKCTL0_CMPTBASECLKSEL_SEL(0):
            freq = getFro1Div3Freq();
            break;
        case CLKCTL0_CMPTBASECLKSEL_SEL(1):
            freq = getFro1MaxFreq();
            break;
        case CLKCTL0_CMPTBASECLKSEL_SEL(2):
            freq = getFro0Div3Freq();
            break;
        case CLKCTL0_CMPTBASECLKSEL_SEL(3):
            freq = getLpOscFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

static uint32_t getMainPllFreq(void)
{
    uint32_t freq = 0U;
    uint64_t freqTmp;

    switch ((CLKCTL2->MAINPLL0CLKSEL) & CLKCTL2_MAINPLL0CLKSEL_SEL_MASK)
    {
        case CLKCTL2_MAINPLL0CLKSEL_SEL(0):
            freq = getFro1MaxFreq() / 8U;
            break;
        case CLKCTL2_MAINPLL0CLKSEL_SEL(1):
            freq = CLK_OSC_CLK;
            break;
        default:
            freq = 0U;
            break;
    }

    if (((CLKCTL2->MAINPLL0CTL0) & CLKCTL2_MAINPLL0CTL0_BYPASS_MASK) == 0U)
    {
        /* PLL output frequency = Fref * (DIV_SELECT + NUM/DENOM). */
        freqTmp = ((uint64_t)freq * ((uint64_t)(CLKCTL2->MAINPLL0NUM))) / ((uint64_t)(CLKCTL2->MAINPLL0DENOM));
        freq *= ((CLKCTL2->MAINPLL0CTL0) & CLKCTL2_MAINPLL0CTL0_MULT_MASK) >> CLKCTL2_MAINPLL0CTL0_MULT_SHIFT;
        freq += (uint32_t)freqTmp;
    }
    return freq;
}

static uint32_t getMainPllPfd0Freq(void)
{
    uint32_t freq = getMainPllFreq();

    if (((CLKCTL2->MAINPLL0CTL0) & CLKCTL2_MAINPLL0CTL0_BYPASS_MASK) == 0U)
    {
        freq = (uint32_t)((uint64_t)freq * 18U /
                          ((CLKCTL2->MAINPLL0PFD & CLKCTL2_MAINPLL0PFD_PFD0_MASK) >> CLKCTL2_MAINPLL0PFD_PFD0_SHIFT));
    }
    return freq;
}

static uint32_t getAudioPllFreq(void)
{
    uint32_t freq = 0U;
    uint64_t freqTmp;

    switch ((CLKCTL2->AUDIOPLL0CLKSEL) & CLKCTL2_AUDIOPLL0CLKSEL_SEL_MASK)
    {
        case CLKCTL2_AUDIOPLL0CLKSEL_SEL(0):
            freq = getFro1MaxFreq() / 8U;
            break;
        case CLKCTL2_AUDIOPLL0CLKSEL_SEL(1):
            freq = CLK_OSC_CLK;
            break;
        default:
            freq = 0U;
            break;
    }

    if (((CLKCTL2->AUDIOPLL0CTL0) & CLKCTL2_AUDIOPLL0CTL0_BYPASS_MASK) == 0UL)
    {
        /* PLL output frequency = Fref * (DIV_SELECT + NUM/DENOM). */
        freqTmp = ((uint64_t)freq * ((uint64_t)(CLKCTL2->AUDIOPLL0NUM))) / ((uint64_t)(CLKCTL2->AUDIOPLL0DENOM));
        freq *= ((CLKCTL2->AUDIOPLL0CTL0) & CLKCTL2_AUDIOPLL0CTL0_MULT_MASK) >> CLKCTL2_AUDIOPLL0CTL0_MULT_SHIFT;
        freq += (uint32_t)freqTmp;
    }
    return freq;
}

static uint32_t getAudioPllPfd1Freq(void)
{
    uint32_t freq = getAudioPllFreq();

    if (((CLKCTL2->AUDIOPLL0CTL0) & CLKCTL2_AUDIOPLL0CTL0_BYPASS_MASK) == 0UL)
    {
        freq =
            (uint32_t)((uint64_t)freq * 18U /
                       ((CLKCTL2->AUDIOPLL0PFD & CLKCTL2_AUDIOPLL0PFD_PFD1_MASK) >> CLKCTL2_AUDIOPLL0PFD_PFD1_SHIFT));
    }
    return freq;
}

void SystemCoreClockUpdate(void)
{
    uint32_t freq = 0U;

    switch (CLKCTL0->MAINCLKSEL & CLKCTL0_MAINCLKSEL_SEL_MASK)
    {
        case CLKCTL0_MAINCLKSEL_SEL(0):
            freq = getBaseClkCmpt();
            break;

        case CLKCTL0_MAINCLKSEL_SEL(1):
            freq = getMainPllPfd0Freq();
            break;

        case CLKCTL0_MAINCLKSEL_SEL(2):
            freq = getFro0MaxFreq();
            break;

        case CLKCTL0_MAINCLKSEL_SEL(3):
            freq = getAudioPllPfd1Freq();
            break;

        default:
            freq = 0U;
            break;
    }

    SystemCoreClock = freq / ((CLKCTL0->MAINCLKDIV & CLKCTL0_MAINCLKDIV_DIV_MASK) + 1U);
}

/* ----------------------------------------------------------------------------
   -- SystemInitHook()
   ---------------------------------------------------------------------------- */

__attribute__((weak)) void SystemInitHook(void)
{
    /* Void implementation of the weak function. */
}
