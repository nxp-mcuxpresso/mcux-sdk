/*
** ###################################################################
**     Processors:          MIMX9596AVTXN_ca55
**                          MIMX9596AVZXN_ca55
**                          MIMX9596DVTXQ_ca55
**                          MIMX9596DVYXQ_ca55
**                          MIMX9596DVZXQ_ca55
**                          MIMX9596XVTXL_ca55
**
**     Compilers:           GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**
**     Reference manual:    iMX95RM rev1 draftM
**     Version:             rev. 1.0, 2023-01-10
**     Build:               b240402
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
**     - rev. 1.0 (2023-01-10)
**         Initial version.
**
** ###################################################################
*/

/*!
 * @file MIMX9596_ca55
 * @version 1.0
 * @date 2023-01-10
 * @brief Device specific configuration file for MIMX9596_ca55 (implementation
 *        file)
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
  __ASM volatile("mov x0, #(3 << 20) \n\t"
                 "msr cpacr_el1, x0");
#endif /* ((__FPU_PRESENT == 1) && (__FPU_USED == 1)) */


  SystemInitHook();

  ARM_TIMER_GetFreq(&SystemCoreClock);
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate (void) {


}

/* ----------------------------------------------------------------------------
   -- SystemInitHook()
   ---------------------------------------------------------------------------- */

__attribute__ ((weak)) void SystemInitHook (void) {
  /* Void implementation of the weak function. */
}
