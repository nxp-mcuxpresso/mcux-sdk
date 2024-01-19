/*
** ###################################################################
**     Processors:          MIMX8UD7CVP08_cm33
**                          MIMX8UD7DVK08_cm33
**                          MIMX8UD7DVP08_cm33
**
**     Compilers:           GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**
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
 * @file MIMX8UD7_cm33
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
#include "fsl_cache.h"

#define SYSTEM_IS_XIP_FLEXSPI()                                                                               \
    ((((uint32_t)SystemCoreClockUpdate >= 0x04000000U) && ((uint32_t)SystemCoreClockUpdate < 0x0C000000U)) || \
     (((uint32_t)SystemCoreClockUpdate >= 0x14000000U) && ((uint32_t)SystemCoreClockUpdate < 0x1C000000U)))

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

static uint32_t getPll1Freq(void)
{
    uint32_t freq, mult;
    uint64_t freqTmp;
    uint32_t pllnum, plldenom;

    if ((CGC_RTD->PLL1CFG & CGC_PLL1CFG_SOURCE_MASK) != 0UL) /* If use FRO24M */
    {
        freq = CLK_FRO_192MHZ / 8U;
    }
    else /* Use System OSC. */
    {
        freq = CLK_XTAL_OSC_CLK;
    }

    pllnum   = (CGC_RTD->PLL1NUM & CGC_PLL1NUM_NUM_MASK) >> CGC_PLL1NUM_NUM_SHIFT;
    plldenom = (CGC_RTD->PLL1DENOM & CGC_PLL1DENOM_DENOM_MASK) >> CGC_PLL1DENOM_DENOM_SHIFT;
    freqTmp  = (uint64_t)freq * (uint64_t)pllnum / (uint64_t)plldenom;
    mult     = (CGC_RTD->PLL1CFG & CGC_PLL1CFG_MULT_MASK) >> CGC_PLL1CFG_MULT_SHIFT;
    freq     = freq * mult + (uint32_t)freqTmp;

    return freq;
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
    SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));    /* set CP10, CP11 Full Access in Secure mode */
    #if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
    SCB_NS->CPACR |= ((3UL << 10*2) | (3UL << 11*2));    /* set CP10, CP11 Full Access in Non-secure mode */
    #endif /* (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
#endif /* ((__FPU_PRESENT == 1) && (__FPU_USED == 1)) */

    SCB->CPACR |= ((3UL << 0*2) | (3UL << 1*2));    /* set CP0, CP1 Full Access in Secure mode (enable PowerQuad) */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
    SCB_NS->CPACR |= ((3UL << 0*2) | (3UL << 1*2));    /* set CP0, CP1 Full Access in Non-secure mode (enable PowerQuad) */
#endif /* (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

    SCB->NSACR |= ((3UL << 0) | (3UL << 10));   /* enable CP0, CP1, CP10, CP11 Non-secure Access */

    CACHE64_EnableCache(CACHE64_CTRL0); /* enable code bus cache(I-Cache) */

    SystemInitHook();
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate(void)
{
    /* i.MX8ULP SystemCoreClockUpdate */
    uint32_t fracValue;
    uint32_t CGCOUTClock;
    /* Identify current system clock source. */
    switch (CGC_RTD->CM33CLK & CGC_CM33CLK_SCS_MASK)
    {
        case CGC_CM33CLK_SCS(0):
            /* FRO clock */
            CGCOUTClock = CLK_FRO_192MHZ;
            break;
        case CGC_CM33CLK_SCS(1):
            /* PLL0 PFD0 */
            CGCOUTClock = getPll0Freq();
            fracValue   = (CGC_RTD->PLL0PFDCFG & CGC_PLL0PFDCFG_PFD0_MASK) >> CGC_PLL0PFDCFG_PFD0_SHIFT;
            CGCOUTClock = (uint32_t)(((uint64_t)CGCOUTClock * 18U) / fracValue);
            break;
        case CGC_CM33CLK_SCS(2):
            /* PLL1 PFD0 */
            CGCOUTClock = getPll1Freq();
            fracValue   = (CGC_RTD->PLL1PFDCFG & CGC_PLL1PFDCFG_PFD0_MASK) >> CGC_PLL1PFDCFG_PFD0_SHIFT;
            CGCOUTClock = (uint32_t)(((uint64_t)CGCOUTClock * 18U) / fracValue);
            break;
        case CGC_CM33CLK_SCS(3):
            /* OSCCLK */
            CGCOUTClock = CLK_XTAL_OSC_CLK;
            break;
        case CGC_CM33CLK_SCS(4):
            /* RTC32K */
            CGCOUTClock = CLK_RTC_32K_CLK;
            break;
        case CGC_CM33CLK_SCS(5):
            /* LVDS */
            CGCOUTClock = CLK_LVDS_CLK;
            break;
        case CGC_CM33CLK_SCS(6):
            /* PLL0 */
            CGCOUTClock = getPll0Freq();
            break;
        default:
            CGCOUTClock = 0U;
            break;
    }
    /* Divide the SCG output clock to get the M33 Core clock. */
    CGCOUTClock /= ((CGC_RTD->CM33CLK & CGC_CM33CLK_DIVCORE_MASK) >> CGC_CM33CLK_DIVCORE_SHIFT) + 1U;
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
