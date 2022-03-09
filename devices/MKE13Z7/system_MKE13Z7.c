/*
** ###################################################################
**     Processors:          MKE13Z128VLF7
**                          MKE13Z128VLH7
**                          MKE13Z128VLL7
**                          MKE13Z256VLF7
**                          MKE13Z256VLH7
**                          MKE13Z256VLL7
**
**     Compilers:           Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**                          MCUXpresso Compiler
**
**     Reference manual:    KE1xZP100M72SF1RM, Rev. 1, Jun. 2021
**     Version:             rev. 3.0, 2021-10-08
**     Build:               b211108
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2021 NXP
**     All rights reserved.
**
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2020-12-10)
**         Initial version.
**     - rev. 2.0 (2021-06-25)
**         Based on Rev.1 RM.
**     - rev. 3.0 (2021-10-08)
**         Add 48LQFP parts.
**
** ###################################################################
*/

/*!
 * @file MKE13Z7
 * @version 3.0
 * @date 2021-10-08
 * @brief Device specific configuration file for MKE13Z7 (implementation file)
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

#if (DISABLE_WDOG)
  if ((WDOG->CS & WDOG_CS_CMD32EN_MASK) != 0U)
  {
      WDOG->CNT = WDOG_UPDATE_KEY;
  }
  else
  {
      WDOG->CNT = WDOG_UPDATE_KEY & 0xFFFFU;
      WDOG->CNT = (WDOG_UPDATE_KEY >> 16U) & 0xFFFFU;
  }
  WDOG->TOVAL = 0xFFFFU;
  WDOG->CS = (uint32_t) ((WDOG->CS) & ~WDOG_CS_EN_MASK) | WDOG_CS_UPDATE_MASK;
#endif /* (DISABLE_WDOG) */

  SystemInitHook();
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate (void) {

  uint32_t SCGOUTClock;                                 /* Variable to store output clock frequency of the SCG module */
  uint16_t Divider;
  Divider = (uint16_t)(((SCG->CSR & SCG_CSR_DIVCORE_MASK) >> SCG_CSR_DIVCORE_SHIFT) + 1U);

  switch ((SCG->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT) {
    case 0x1:
      /* System OSC */
      SCGOUTClock = CPU_XTAL_CLK_HZ;
      break;
    case 0x2:
      /* Slow IRC */
      SCGOUTClock = ((((SCG->SIRCCFG & SCG_SIRCCFG_RANGE_MASK) >> SCG_SIRCCFG_RANGE_SHIFT) != 0U) ? 8000000U : 2000000U);
      break;
    case 0x3:
      /* Fast IRC */
      SCGOUTClock = 48000000U + ((SCG->FIRCCFG & SCG_FIRCCFG_RANGE_MASK) >> SCG_FIRCCFG_RANGE_SHIFT) * 4000000U;
      break;
    case 0x5:
      /* Low Power FLL */
      SCGOUTClock = 48000000U + ((SCG->LPFLLCFG & SCG_LPFLLCFG_FSEL_MASK) >> SCG_LPFLLCFG_FSEL_SHIFT) * 24000000U;
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

__attribute__ ((weak)) void SystemInitHook (void) {
  /* Void implementation of the weak function. */
}
