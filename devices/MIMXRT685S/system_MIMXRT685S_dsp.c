/*
** ###################################################################
**     Processors:          MIMXRT685SFAWBR_dsp
**                          MIMXRT685SFFOB_dsp
**                          MIMXRT685SFVKB_dsp
**
**     Compiler:            XCC Compiler
**     Reference manual:    MIMXRT685 User manual Rev. 0.95 11 November 2019
**     Version:             rev. 2.0, 2019-11-12
**     Build:               b201016
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2020 NXP
**     All rights reserved.
**
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2018-06-19)
**         Initial version.
**     - rev. 2.0 (2019-11-12)
**         Base on rev 0.95 RM (B0 Header)
**
** ###################################################################
*/

/*!
 * @file MIMXRT685S
 * @version 1.0
 * @date 161020
 * @brief Device specific configuration file for MIMXRT685S (implementation file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include "fsl_device_registers.h"

/* Get OSC clock from SYSOSC_BYPASS */
static uint32_t getOscClk(void)
{
  return (CLKCTL0->SYSOSCBYPASS == 0U) ? CLK_XTAL_OSC_CLK : ((CLKCTL0->SYSOSCBYPASS == 1U) ? CLK_EXT_CLKIN : 0U);
}

/* Get FFRO clock from FFROCTL0 setting */
static uint32_t getFFroFreq(void)
{
  uint32_t freq = 0U;

  switch (CLKCTL0->FFROCTL0 & CLKCTL0_FFROCTL0_TRIM_RANGE_MASK)
  {
    case CLKCTL0_FFROCTL0_TRIM_RANGE(0):
      freq = CLK_FRO_48MHZ;
      break;
    case CLKCTL0_FFROCTL0_TRIM_RANGE(3):
      freq = CLK_FRO_60MHZ;
      break;
    default:
      freq = 0U;
      break;
  }
  return freq;
}

static uint32_t getSpllFreq(void)
{
  uint32_t freq = 0U;
  uint64_t freqTmp = 0U;

  switch ((CLKCTL0->SYSPLL0CLKSEL) & CLKCTL0_SYSPLL0CLKSEL_SEL_MASK)
  {
    case CLKCTL0_SYSPLL0CLKSEL_SEL(0): /* SFRO clock */
      freq = CLK_FRO_16MHZ;
      break;
    case CLKCTL0_SYSPLL0CLKSEL_SEL(1): /* OSC clock (clk_in) */
      freq = getOscClk();
      break;
    case CLKCTL0_SYSPLL0CLKSEL_SEL(2): /* FRO clock (48m_irc) divider by 2 */
      freq = getFFroFreq() / 2U;
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

__attribute__ ((weak)) void SystemInit (void) {
  SystemInitHook();
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate (void) {

  /* iMXRT6xx systemCoreClockUpdate */
  uint32_t freq = 0U;

  switch ((CLKCTL1->DSPCPUCLKSELB) & CLKCTL1_DSPCPUCLKSELB_SEL_MASK)
  {
    case CLKCTL1_DSPCPUCLKSELB_SEL(0): /* DSPCPUCLKSELA clock */
      switch ((CLKCTL1->DSPCPUCLKSELA) & CLKCTL1_DSPCPUCLKSELA_SEL_MASK)
      {
        case CLKCTL1_DSPCPUCLKSELA_SEL(0): /* FRO clock (48m_irc) divider by 4 */
          freq = getFFroFreq() / 4U;
          break;
        case CLKCTL1_DSPCPUCLKSELA_SEL(1): /* OSC clock (clk_in) */
          freq = getOscClk();
          break;
        case CLKCTL1_DSPCPUCLKSELA_SEL(2): /* Low Power Oscillator Clock (1m_lposc) */
          freq = CLK_LPOSC_1MHZ;
          break;
        case CLKCTL1_DSPCPUCLKSELA_SEL(3): /* SFRO clock */
          freq = CLK_FRO_16MHZ;
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
        freq = (uint32_t)((uint64_t)freq * 18U / ((CLKCTL0->SYSPLL0PFD & CLKCTL0_SYSPLL0PFD_PFD0_MASK) >>
                                      CLKCTL0_SYSPLL0PFD_PFD0_SHIFT));
      }
      freq = freq / ((CLKCTL0->MAINPLLCLKDIV & CLKCTL0_MAINPLLCLKDIV_DIV_MASK) + 1U);
      break;
    case CLKCTL1_DSPCPUCLKSELB_SEL(2): /* DSP PLL clock */
      freq = getSpllFreq();
      if (((CLKCTL0->SYSPLL0CTL0) & CLKCTL0_SYSPLL0CTL0_BYPASS_MASK) == 0U)
      {
        freq = (uint32_t)((uint64_t)freq * 18U / ((CLKCTL0->SYSPLL0PFD & CLKCTL0_SYSPLL0PFD_PFD1_MASK) >>
                                      CLKCTL0_SYSPLL0PFD_PFD1_SHIFT));
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

  SystemCoreClock = freq / ((CLKCTL1->DSPCPUCLKDIV & 0xffU) + 1U);
}

/* ----------------------------------------------------------------------------
   -- SystemInitHook()
   ---------------------------------------------------------------------------- */

__attribute__ ((weak)) void SystemInitHook (void) {
  /* Void implementation of the weak function. */
}
