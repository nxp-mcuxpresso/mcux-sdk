/*
** ###################################################################
**     Processors:          MIMX8UD7CVP08_dsp0
**                          MIMX8UD7DVK08_dsp0
**                          MIMX8UD7DVP08_dsp0
**
**     Compiler:            Xtensa Compiler
**     Reference manual:    IMX8ULPRM, Rev. D, December. 2022
**     Version:             rev. 5.0, 2023-04-27
**     Build:               b230927
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2023 NXP
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2020-05-25)
**         Initial version.
**     - rev. 2.0 (2020-09-18)
**         Base on rev A RM
**     - rev. 3.0 (2021-01-20)
**         Base on rev A.1 RM
**     - rev. 4.0 (2021-07-05)
**         Base on rev B RM
**     - rev. 5.0 (2023-04-27)
**         Base on rev D RM
**
** ###################################################################
*/

/*!
 * @file MIMX8UD7_dsp0
 * @version 1.0
 * @date 270923
 * @brief Device specific configuration file for MIMX8UD7 (implementation file)
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
static uint32_t getPll0Freq(void)
{
    uint32_t freq;
    uint32_t mult;
    uint8_t pll0Multi[] = {0U, 15U, 16U, 20U, 22U, 25U, 30U, 0U};

    if ((CGC_RTD->PLL0CFG & CGC_PLL0CFG_SOURCE_MASK) != 0UL) /* If use FRO24M */
    {
        freq = CLK_FRO_192MHZ / 8U;
    }
    else /* Use System OSC. */
    {
        freq = CLK_XTAL_OSC_CLK;
    }

    mult = ((CGC_RTD->PLL0CFG & CGC_PLL0CFG_MULT_MASK) >> CGC_PLL0CFG_MULT_SHIFT);
    freq *= pll0Multi[mult]; /* Multiplier. */


    return freq;
}

void SystemInit(void)
{
    SystemInitHook();
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate(void)
{
    uint32_t fracValue;
    uint32_t CGCOUTClock;
    /* Identify current system clock source. */
    switch (CGC_RTD->FUSIONCLK & CGC_FUSIONCLK_SCS_MASK)
    {
        case CGC_FUSIONCLK_SCS(0):
            /* FRO clock */
            CGCOUTClock = CLK_FRO_192MHZ;
            break;
        case CGC_FUSIONCLK_SCS(1):
            /* PLL0 PFD0 */
            CGCOUTClock = getPll0Freq();
            fracValue   = (CGC_RTD->PLL0PFDCFG & CGC_PLL0PFDCFG_PFD0_MASK) >> CGC_PLL0PFDCFG_PFD0_SHIFT;
            CGCOUTClock = (uint32_t)(((uint64_t)CGCOUTClock * 18U) / fracValue);
            break;
        case CGC_FUSIONCLK_SCS(2):
            /* PLL0 PFD1 */
            CGCOUTClock = getPll0Freq();
            fracValue   = (CGC_RTD->PLL0PFDCFG & CGC_PLL0PFDCFG_PFD1_MASK) >> CGC_PLL0PFDCFG_PFD1_SHIFT;
            CGCOUTClock = (uint32_t)(((uint64_t)CGCOUTClock * 18U) / fracValue);
            break;
        case CGC_FUSIONCLK_SCS(3):
            /* SOSC */
            CGCOUTClock = CLK_XTAL_OSC_CLK;
            break;
        case CGC_FUSIONCLK_SCS(4):
            /* RTC32K */
            CGCOUTClock = CLK_RTC_32K_CLK;
            break;
        case CGC_FUSIONCLK_SCS(5):
            /* LVDS */
            CGCOUTClock = CLK_LVDS_CLK;
            break;
        case CGC_FUSIONCLK_SCS(6):
            /* PLL0 */
            CGCOUTClock = getPll0Freq();
            break;
        default:
            CGCOUTClock = 0U;
            break;
    }
    /* Divide the CGC output clock to get the Fusion Core clock. */
    CGCOUTClock /= ((CGC_RTD->FUSIONCLK & CGC_FUSIONCLK_DIVCORE_MASK) >> CGC_FUSIONCLK_DIVCORE_SHIFT) + 1U;
    /* Update System Core Clock. */
    SystemCoreClock = CGCOUTClock;
}

/* ----------------------------------------------------------------------------
   -- SystemInitHook()
   ---------------------------------------------------------------------------- */

__attribute__((weak)) void SystemInitHook(void)
{
    /* Void implementation of the weak function. */
}
