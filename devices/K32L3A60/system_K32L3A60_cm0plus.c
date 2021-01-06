/*
** ###################################################################
**     Processor:           K32L3A60VPJ1A_cm0plus
**     Compilers:           GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**                          MCUXpresso Compiler
**
**     Reference manual:    K32L3ARM, Rev. 0 , 05/2019
**     Version:             rev. 1.0, 2019-04-22
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
**     - rev. 1.0 (2019-04-22)
**         Initial version.
**
** ###################################################################
*/

/*!
 * @file K32L3A60_cm0plus
 * @version 1.0
 * @date 2019-04-22
 * @brief Device specific configuration file for K32L3A60_cm0plus
 *        (implementation file)
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
  if ((WDOG1->CS & WDOG_CS_CMD32EN_MASK) != 0U)
  {
      WDOG1->CNT = 0xD928C520U;
  }
  else
  {
      WDOG1->CNT = 0xC520U;
      WDOG1->CNT = 0xD928U;
  }
  WDOG1->TOVAL = 0xFFFFU;
  WDOG1->CS = (uint32_t) ((WDOG1->CS) & ~WDOG_CS_EN_MASK) | WDOG_CS_UPDATE_MASK;
#endif /* (DISABLE_WDOG) */

/* Boot ROM on K32_L3 does not properly restore the registers (LPTMR0->CSR, LPTMR0->PSR, SCB->AIRCR) upon exiting. This can cause
 * an unrecoverable hard fault when SVC calls are executed. SVC calls are needed by operating systems when starting tasks.
 * Add following codes to the end of the SystemInit function which is called before any application is started. This operation
 * will be done only when current core is boot core. */
  if (((FTFE->FOPT3 & 0x40U) >> 6U) == 0U)
  {
    if (LPTMR0->CSR != 0U)
    {
        LPTMR0->CSR = 0;
    }
    if (LPTMR0->PSR != 0U)
    {
        LPTMR0->PSR = 0;
    }
  }

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
