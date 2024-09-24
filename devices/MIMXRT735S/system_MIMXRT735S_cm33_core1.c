/*
** ###################################################################
**     Processors:          MIMXRT735SGAWAR_cm33_core1
**                          MIMXRT735SGFOA_cm33_core1
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
 * @file MIMXRT735S_cm33_core1
 * @version 1.0
 * @date 2024-05-28
 * @brief Device specific configuration file for MIMXRT735S_cm33_core1
 *  (implementation file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"

/* TBD. */

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

    SYSCON1->DSPSTALL |= SYSCON1_DSPSTALL_DSPSTALL_MASK;
    SLEEPCON1->SHARED_MASK0_SET = 0xFF007FU; /* Mask all the shared modules. */

    SystemInitHook();
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */
static uint32_t getFro2MaxFreq(void)
{
    return CLK_FRO2_CLK;
}

static uint32_t getFro1MaxFreq(void)
{
    return CLK_FRO1_MAX_CLK;
}

static uint32_t getFro1Div3Freq(void)
{
    return getFro1MaxFreq() / 3U;
}

static uint32_t getFro2Div3Freq(void)
{
    return getFro2MaxFreq() / 3U;
}

static uint32_t getLpOscFreq(void)
{
    return CLK_LPOSC_1MHZ;
}

static uint32_t getBaseClkSense(void)
{
    uint32_t freq = 0U;

    switch (CLKCTL3->SENSEBASECLKSEL & CLKCTL3_SENSEBASECLKSEL_SEL_MASK)
    {
        case CLKCTL3_SENSEBASECLKSEL_SEL(0):
            freq = getFro1Div3Freq();
            break;
        case CLKCTL3_SENSEBASECLKSEL_SEL(1):
            freq = getFro1MaxFreq();
            break;
        case CLKCTL3_SENSEBASECLKSEL_SEL(2):
            freq = getFro2Div3Freq();
            break;
        case CLKCTL3_SENSEBASECLKSEL_SEL(3):
            freq = getLpOscFreq();
            break;
        default:
            freq = 0U;
            break;
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

static uint32_t getAudioPllPfd3Freq(void)
{
    uint32_t freq = getAudioPllFreq();

    if (((CLKCTL2->AUDIOPLL0CTL0) & CLKCTL2_AUDIOPLL0CTL0_BYPASS_MASK) == 0UL)
    {
        freq =
            (uint32_t)((uint64_t)freq * 18U /
                       ((CLKCTL2->AUDIOPLL0PFD & CLKCTL2_AUDIOPLL0PFD_PFD3_MASK) >> CLKCTL2_AUDIOPLL0PFD_PFD3_SHIFT));
    }
    return freq;
}

void SystemCoreClockUpdate(void)
{
    uint32_t freq = 0U;

    switch ((CLKCTL3->MAINCLKSEL) & CLKCTL3_MAINCLKSEL_SEL_MASK)
    {
        case CLKCTL3_MAINCLKSEL_SEL(0):
            freq = getBaseClkSense();
            break;

        case CLKCTL3_MAINCLKSEL_SEL(1):
            freq = getFro2MaxFreq();
            break;

        case CLKCTL3_MAINCLKSEL_SEL(2):
            freq = getAudioPllPfd3Freq();
            break;

        case CLKCTL3_MAINCLKSEL_SEL(3):
            freq = getFro1MaxFreq();
            break;

        default:
            freq = 0U;
            break;
    }

    SystemCoreClock = freq / ((CLKCTL3->SENSEMAINCLKDIV & CLKCTL3_SENSEMAINCLKDIV_DIV_MASK) + 1U);
}

/* ----------------------------------------------------------------------------
   -- SystemInitHook()
   ---------------------------------------------------------------------------- */

__attribute__((weak)) void SystemInitHook(void)
{
    /* Void implementation of the weak function. */
}
