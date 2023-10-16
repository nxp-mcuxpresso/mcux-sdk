/*
** ###################################################################
**     Processor:           MIMX8QM6AVUFF_dsp
**     Compiler:            Xtensa Compiler
**     Reference manual:    IMX8QMRM, Rev. E, Jun. 2018
**     Version:             rev. 4.0, 2018-08-30
**     Build:               b231013
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
**     - rev. 1.0 (2016-06-02)
**         Initial version.
**     - rev. 2.0 (2017-05-04)
**         RevA Header ER
**     - rev. 3.0 (2018-01-29)
**         RevB Header ER
**     - rev. 4.0 (2018-08-30)
**         RevC Header EAR
**
** ###################################################################
*/

/*!
 * @file MIMX8QM6_dsp
 * @version 4.0
 * @date 2018-08-30
 * @brief Device specific configuration file for MIMX8QM6_dsp (implementation
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
/* i.MX8QM systemInit */
  SystemInitHook();
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate (void) {
/* i.MX8QM systemCoreClockUpdate */
}

/* ----------------------------------------------------------------------------
   -- SystemInitHook()
   ---------------------------------------------------------------------------- */

__attribute__ ((weak)) void SystemInitHook (void) {
  /* Void implementation of the weak function. */
}
