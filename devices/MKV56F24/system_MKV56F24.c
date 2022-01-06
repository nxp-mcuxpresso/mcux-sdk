/*
** ###################################################################
**     Processors:          MKV56F1M0VLL24
**                          MKV56F1M0VLQ24
**                          MKV56F1M0VMD24
**                          MKV56F512VLL24
**                          MKV56F512VLQ24
**                          MKV56F512VMD24
**
**     Compilers:           Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**                          MCUXpresso Compiler
**
**     Reference manual:    KV5XP144M240RM Rev. 3, 02/2016
**     Version:             rev. 0.3, 2016-02-29
**     Build:               b181105
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
**     - rev. 0.1 (2015-02-24)
**         Initial version.
**     - rev. 0.2 (2015-10-21)
**         UART0 - removed LON functionality.
**         FMC - corrected base address.
**     - rev. 0.3 (2016-02-29)
**         PORT - removed registers GICLR, GICHR.
**
** ###################################################################
*/

/*!
 * @file MKV56F24
 * @version 0.3
 * @date 2016-02-29
 * @brief Device specific configuration file for MKV56F24 (implementation file)
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

void SystemInit (void) {
#if ((__FPU_PRESENT == 1) && (__FPU_USED == 1))
  SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));    /* set CP10, CP11 Full Access */
#endif /* ((__FPU_PRESENT == 1) && (__FPU_USED == 1)) */

  /* Watchdog disable */

#if (DISABLE_WDOG)
  /* WDOG->UNLOCK: WDOGUNLOCK=0xC520 */
  WDOG->UNLOCK = WDOG_UNLOCK_WDOGUNLOCK(0xC520); /* Key 1 */
  /* WDOG->UNLOCK: WDOGUNLOCK=0xD928 */
  WDOG->UNLOCK = WDOG_UNLOCK_WDOGUNLOCK(0xD928); /* Key 2 */
  /* WDOG->STCTRLH: ?=0,DISTESTWDOG=0,BYTESEL=0,TESTSEL=0,TESTWDOG=0,?=0,?=1,WAITEN=1,STOPEN=1,DBGEN=0,ALLOWUPDATE=1,WINEN=0,IRQRSTEN=0,CLKSRC=1,WDOGEN=0 */
  WDOG->STCTRLH = WDOG_STCTRLH_BYTESEL(0x00) |
                 WDOG_STCTRLH_WAITEN_MASK |
                 WDOG_STCTRLH_STOPEN_MASK |
                 WDOG_STCTRLH_ALLOWUPDATE_MASK |
                 WDOG_STCTRLH_CLKSRC_MASK |
                 0x0100U;
#endif /* (DISABLE_WDOG) */

/* Enable instruction and data caches */
#if defined(__ICACHE_PRESENT) && __ICACHE_PRESENT
  SCB_EnableICache();
#endif
#if defined(__DCACHE_PRESENT) && __DCACHE_PRESENT
  SCB_EnableDCache();
#endif

  SystemInitHook();
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate (void) {


  uint32_t MCGOUTClock;                                                        /* Variable to store output clock frequency of the MCG module */
  uint16_t Divider;

  if ((MCG->C1 & MCG_C1_CLKS_MASK) == 0x0u) {
    /* Output of FLL or PLL is selected */
    if ((MCG->C6 & MCG_C6_PLLS_MASK) == 0x0U) {
      /* FLL is selected */
      if ((MCG->C1 & MCG_C1_IREFS_MASK) == 0x0U) {
        /* External reference clock is selected */
        MCGOUTClock = CPU_XTAL_CLK_HZ;                                         /* System oscillator drives MCG clock */
        if ((MCG->C2 & MCG_C2_RANGE_MASK) != 0x0U) {
          switch (MCG->C1 & MCG_C1_FRDIV_MASK) {
          case (uint8_t)MCG_C1_FRDIV(0x07):
            Divider = 1536;
            break;
          case (uint8_t)MCG_C1_FRDIV(0x06):
            Divider = 1280;
            break;
          default:
            Divider = (uint16_t)(32U << ((MCG->C1 & MCG_C1_FRDIV_MASK) >> MCG_C1_FRDIV_SHIFT));
            break;
          }
        } else {/* ((MCG->C2 & MCG_C2_RANGE_MASK) != 0x0U) */
          Divider = (uint16_t)(1U << ((MCG->C1 & MCG_C1_FRDIV_MASK) >> MCG_C1_FRDIV_SHIFT));
        }
        MCGOUTClock = (MCGOUTClock / Divider);                                 /* Calculate the divided FLL reference clock */
      } else { /* (!((MCG->C1 & MCG_C1_IREFS_MASK) == 0x0U)) */
        MCGOUTClock = CPU_INT_SLOW_CLK_HZ;                                     /* The slow internal reference clock is selected */
      } /* (!((MCG->C1 & MCG_C1_IREFS_MASK) == 0x0U)) */
      /* Select correct multiplier to calculate the MCG output clock  */
      switch (MCG->C4 & (MCG_C4_DMX32_MASK | MCG_C4_DRST_DRS_MASK)) {
        case 0x0u:
          MCGOUTClock *= 640U;
          break;
        case 0x20u:
          MCGOUTClock *= 1280U;
          break;
        case 0x40u:
          MCGOUTClock *= 1920U;
          break;
        case 0x60u:
          MCGOUTClock *= 2560U;
          break;
        case 0x80u:
          MCGOUTClock *= 732U;
          break;
        case 0xA0u:
          MCGOUTClock *= 1464U;
          break;
        case 0xC0u:
          MCGOUTClock *= 2197U;
          break;
        case 0xE0u:
          MCGOUTClock *= 2929U;
          break;
        default:
          MCGOUTClock *= 640U;
          break;
      }
    } else { /* (!((MCG->C6 & MCG_C6_PLLS_MASK) == 0x0U)) */
      /* PLL is selected */
      Divider = (1U + (MCG->C5 & MCG_C5_PRDIV_MASK));
      MCGOUTClock = (uint32_t)(CPU_XTAL_CLK_HZ / Divider);                     /* Calculate the PLL reference clock */
      Divider = ((MCG->C6 & MCG_C6_VDIV_MASK) + 16U);
      MCGOUTClock = ((MCGOUTClock * Divider) >> 1U);                           /* Calculate the MCG output clock = VCO/2; VCO = (MCGOUTClock * Divider) */
    } /* (!((MCG->C6 & MCG_C6_PLLS_MASK) == 0x0U)) */
  } else if ((MCG->C1 & MCG_C1_CLKS_MASK) == 0x40u) {
    /* Internal reference clock is selected */
    if ((MCG->C2 & MCG_C2_IRCS_MASK) == 0x0U) {
      MCGOUTClock = CPU_INT_SLOW_CLK_HZ;                                       /* Slow internal reference clock selected */
    } else { /* (!((MCG->C2 & MCG_C2_IRCS_MASK) == 0x0U)) */
      MCGOUTClock = CPU_INT_FAST_CLK_HZ / (1 << ((MCG->SC & MCG_SC_FCRDIV_MASK) >> MCG_SC_FCRDIV_SHIFT));  /* Fast internal reference clock selected */
    } /* (!((MCG->C2 & MCG_C2_IRCS_MASK) == 0x0U)) */
  } else if ((MCG->C1 & MCG_C1_CLKS_MASK) == 0x80U) {
    /* External reference clock is selected */
    MCGOUTClock = CPU_XTAL_CLK_HZ;                                           /* System oscillator drives MCG clock */
  } else { /* (!((MCG->C1 & MCG_C1_CLKS_MASK) == 0x80U)) */
    /* Reserved value */
    return;
  } /* (!((MCG->C1 & MCG_C1_CLKS_MASK) == 0x80U)) */
  SystemCoreClock = (MCGOUTClock / (1U + ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK) >> SIM_CLKDIV1_OUTDIV1_SHIFT)));

}

/* ----------------------------------------------------------------------------
   -- SystemInitHook()
   ---------------------------------------------------------------------------- */

__attribute__ ((weak)) void SystemInitHook (void) {
  /* Void implementation of the weak function. */
}
