/*
** ###################################################################
**     Processors:          K32L2A41VLH1A
**                          K32L2A41VLL1A
**
**     Compilers:           Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**                          MCUXpresso Compiler
**
**     Reference manual:    K32L2AxRM, Rev. 1, 12/2019
**     Version:             rev. 1.0, 2019-10-30
**     Build:               b201013
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
**     - rev. 1.0 (2019-10-30)
**         Initial version.
**
** ###################################################################
*/

/*!
 * @file K32L2A41A
 * @version 1.0
 * @date 2019-10-30
 * @brief Device specific configuration file for K32L2A41A (implementation file)
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

void SystemInit(void)
{
#if (DISABLE_WDOG)
    if ((WDOG0->CS & WDOG_CS_CMD32EN_MASK) != 0U)
    {
        WDOG0->CNT = WDOG_UPDATE_KEY;
    }
    else
    {
        WDOG0->CNT = WDOG_UPDATE_KEY & 0xFFFFU;
        WDOG0->CNT = (WDOG_UPDATE_KEY >> 16U) & 0xFFFFU;
    }
    WDOG0->TOVAL = 0xFFFFU;
    WDOG0->CS    = (uint32_t)((WDOG0->CS) & ~WDOG_CS_EN_MASK) | WDOG_CS_UPDATE_MASK;
#endif /* (DISABLE_WDOG) */

    SystemInitHook();
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate(void)
{
    uint32_t SCGOUTClock; /* Variable to store output clock frequency of the SCG module */
    uint16_t Divider, prediv, multi;
    Divider = (uint16_t)(((SCG->CSR & SCG_CSR_DIVCORE_MASK) >> SCG_CSR_DIVCORE_SHIFT) + 1U);

    switch ((SCG->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT)
    {
        case 0x1:
            /* System OSC */
            SCGOUTClock = CPU_XTAL_CLK_HZ;
            break;
        case 0x2:
            /* Slow IRC */
            SCGOUTClock =
                ((((SCG->SIRCCFG & SCG_SIRCCFG_RANGE_MASK) >> SCG_SIRCCFG_RANGE_SHIFT) != 0U) ? 8000000U : 2000000U);
            break;
        case 0x3:
            /* Fast IRC */
            SCGOUTClock = 48000000U + ((SCG->FIRCCFG & SCG_FIRCCFG_RANGE_MASK) >> SCG_FIRCCFG_RANGE_SHIFT) * 4000000U;
            break;
        case 0x6:
            /* System PLL */
            if (((SCG->SPLLCFG & SCG_SPLLCFG_SOURCE_MASK) >> SCG_SPLLCFG_SOURCE_SHIFT) != 0U)
            {
                SCGOUTClock =
                    48000000U + ((SCG->FIRCCFG & SCG_FIRCCFG_RANGE_MASK) >> SCG_FIRCCFG_RANGE_SHIFT) * 4000000U;
            }
            else
            {
                SCGOUTClock = CPU_XTAL_CLK_HZ;
            }
            prediv      = (uint16_t)(((SCG->SPLLCFG & SCG_SPLLCFG_PREDIV_MASK) >> SCG_SPLLCFG_PREDIV_SHIFT) + 1U);
            multi       = (uint16_t)(((SCG->SPLLCFG & SCG_SPLLCFG_MULT_MASK) >> SCG_SPLLCFG_MULT_SHIFT) + 16U);
            SCGOUTClock = SCGOUTClock * multi / (prediv * 2U);
            break;
        default:
            SCGOUTClock = 0U;
            break;
    }
    SystemCoreClock = (SCGOUTClock / Divider);
}

/* ----------------------------------------------------------------------------
   -- SystemInitHook()
   ---------------------------------------------------------------------------- */

__attribute__((weak)) void SystemInitHook(void)
{
    /* Void implementation of the weak function. */
}
