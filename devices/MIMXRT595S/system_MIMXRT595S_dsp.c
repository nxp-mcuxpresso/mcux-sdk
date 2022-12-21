/*
** ###################################################################
**     Processors:          MIMXRT595SFAWC_dsp
**                          MIMXRT595SFFOC_dsp
**
**     Compiler:            XCC Compiler
**     Reference manual:    iMXRT500RM Rev.0, 01/2021
**     Version:             rev. 5.0, 2020-08-27
**     Build:               b220711
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2022 NXP
**     All rights reserved.
**
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2019-04-19)
**         Initial version.
**     - rev. 2.0 (2019-07-22)
**         Base on rev 0.7 RM.
**     - rev. 3.0 (2020-03-16)
**         Base on Rev.A RM.
**     - rev. 4.0 (2020-05-18)
**         Base on Rev.B RM.
**     - rev. 5.0 (2020-08-27)
**         Base on Rev.C RM.
**
** ###################################################################
*/

/*!
 * @file MIMXRT595S
 * @version 1.0
 * @date 110722
 * @brief Device specific configuration file for MIMXRT595S (implementation file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include "fsl_device_registers.h"

static uint32_t getSpllFreq(void)
{
    uint32_t freq    = 0U;
    uint64_t freqTmp = 0U;

    switch ((CLKCTL0->SYSPLL0CLKSEL) & CLKCTL0_SYSPLL0CLKSEL_SEL_MASK)
    {
        case CLKCTL0_SYSPLL0CLKSEL_SEL(0): /* FRO_DIV8 clock */
            freq = CLK_FRO_DIV8_CLK;
            break;
        case CLKCTL0_SYSPLL0CLKSEL_SEL(1): /* OSC clock */
            freq = CLK_OSC_CLK;
            break;
        default:
            freq = 0U;
            break;
    }

    if (((CLKCTL0->SYSPLL0CTL0) & CLKCTL0_SYSPLL0CTL0_BYPASS_MASK) == 0U)
    {
        /* PLL output frequency = Fref * (DIV_SELECT + NUM/DENOM). */
        freqTmp = ((uint64_t)freq * ((uint64_t)(CLKCTL0->SYSPLL0NUM))) / ((uint64_t)(CLKCTL0->SYSPLL0DENOM));
        freq *= ((CLKCTL0->SYSPLL0CTL0) & CLKCTL0_SYSPLL0CTL0_MULT_MASK) >> CLKCTL0_SYSPLL0CTL0_MULT_SHIFT;
        freq += (uint32_t)freqTmp;
    }

    return freq;
}

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

void SystemCoreClockUpdate(void)
{
    /* iMXRT5xx systemCoreClockUpdate */
    uint32_t freq = 0U;

    switch ((CLKCTL1->DSPCPUCLKSELB) & CLKCTL1_DSPCPUCLKSELB_SEL_MASK)
    {
        case CLKCTL1_DSPCPUCLKSELB_SEL(0): /* DSPCPUCLKSELA clock */
            switch ((CLKCTL1->DSPCPUCLKSELA) & CLKCTL1_DSPCPUCLKSELA_SEL_MASK)
            {
                case CLKCTL1_DSPCPUCLKSELA_SEL(0): /* FRO clock */
                    freq = CLK_FRO_CLK;
                    break;
                case CLKCTL1_DSPCPUCLKSELA_SEL(1): /* OSC_CLK clock */
                    freq = CLK_OSC_CLK;
                    break;
                case CLKCTL1_DSPCPUCLKSELA_SEL(2): /* Low Power Oscillator Clock (1m_lposc) */
                    freq = CLK_LPOSC_1MHZ;
                    break;
                default:
                    freq = 0U;
                    break;
            }
            break;
        case CLKCTL1_DSPCPUCLKSELB_SEL(1): /* Main System PLL clock */
            freq = getSpllFreq();
            if (((CLKCTL0->SYSPLL0CTL0) & CLKCTL0_SYSPLL0CTL0_BYPASS_MASK) == 0U)
            {
                freq =
                    (uint32_t)((uint64_t)freq * 18U /
                               ((CLKCTL0->SYSPLL0PFD & CLKCTL0_SYSPLL0PFD_PFD0_MASK) >> CLKCTL0_SYSPLL0PFD_PFD0_SHIFT));
            }
            freq = freq / ((CLKCTL0->MAINPLLCLKDIV & CLKCTL0_MAINPLLCLKDIV_DIV_MASK) + 1U);
            break;
        case CLKCTL1_DSPCPUCLKSELB_SEL(2): /* DSP PLL clock */
            freq = getSpllFreq();
            if (((CLKCTL0->SYSPLL0CTL0) & CLKCTL0_SYSPLL0CTL0_BYPASS_MASK) == 0U)
            {
                freq =
                    (uint32_t)((uint64_t)freq * 18U /
                               ((CLKCTL0->SYSPLL0PFD & CLKCTL0_SYSPLL0PFD_PFD1_MASK) >> CLKCTL0_SYSPLL0PFD_PFD1_SHIFT));
            }
            freq = freq / ((CLKCTL0->DSPPLLCLKDIV & CLKCTL0_DSPPLLCLKDIV_DIV_MASK) + 1U);
            break;
        case CLKCTL1_DSPCPUCLKSELB_SEL(3): /* RTC 32KHz clock */
            freq = CLK_RTC_32K_CLK;
            break;
        default:
            freq = 0U;
            break;
    }

    SystemCoreClock = freq / ((CLKCTL1->DSPCPUCLKDIV & 0xFFU) + 1U);
}

/* ----------------------------------------------------------------------------
   -- SystemInitHook()
   ---------------------------------------------------------------------------- */

__attribute__((weak)) void SystemInitHook(void)
{
    /* Void implementation of the weak function. */
}
