/*
** ###################################################################
**     Processors:          MIMXRT798SGAWAR_hifi1
**                          MIMXRT798SGFOA_hifi1
**
**     Compiler:            Xtensa Compiler
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
 * @file MIMXRT798S
 * @version 1.0
 * @date 2024-05-28
 * @brief Device specific configuration file for MIMXRT798S
 *  (implementation file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
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

    switch (CLKCTL1->SENSEBASECLKSEL & CLKCTL1_SENSEBASECLKSEL_SEL_MASK)
    {
        case CLKCTL1_SENSEBASECLKSEL_SEL(0):
            freq = getFro1Div3Freq();
            break;
        case CLKCTL1_SENSEBASECLKSEL_SEL(1):
            freq = getFro1MaxFreq();
            break;
        case CLKCTL1_SENSEBASECLKSEL_SEL(2):
            freq = getFro2Div3Freq();
            break;
        case CLKCTL1_SENSEBASECLKSEL_SEL(3):
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

    switch ((CLKCTL1->SENSEDSPCPUCLKSEL) & CLKCTL1_SENSEDSPCPUCLKSEL_SEL_MASK)
    {
        case CLKCTL1_SENSEDSPCPUCLKSEL_SEL(0):
            freq = getBaseClkSense();
            break;

        case CLKCTL1_SENSEDSPCPUCLKSEL_SEL(1):
            freq = getFro2MaxFreq();
            break;

        case CLKCTL1_SENSEDSPCPUCLKSEL_SEL(2):
            freq = getAudioPllPfd1Freq();
            break;

        case CLKCTL1_SENSEDSPCPUCLKSEL_SEL(3):
            freq = getFro1MaxFreq();
            break;

        default:
            freq = 0U;
            break;
    }

    SystemCoreClock = freq / ((CLKCTL1->SENSEDSPCPUCLKDIV & CLKCTL1_SENSEDSPCPUCLKDIV_DIV_MASK) + 1U);
}

/* ----------------------------------------------------------------------------
   -- SystemInitHook()
   ---------------------------------------------------------------------------- */

__attribute__((weak)) void SystemInitHook(void)
{
    /* Void implementation of the weak function. */
}
