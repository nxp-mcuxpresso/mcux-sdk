/*
** ###################################################################
**     Processor:           MIMX8QX6AVLFZ_dsp
**     Compiler:            Xtensa Compiler
**     Reference manual:    IMX8DQXPRM, Rev. E, 6/2019
**     Version:             rev. 4.0, 2020-06-19
**     Build:               b231016
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
**     - rev. 2.0 (2017-08-23)
**         RevA Header EAR
**     - rev. 3.0 (2018-08-22)
**         RevB Header EAR
**     - rev. 4.0 (2020-06-19)
**         RevC Header RFP
**
** ###################################################################
*/

/*!
 * @file MIMX8QX6_dsp
 * @version 4.0
 * @date 2020-06-19
 * @brief Device specific configuration file for MIMX8QX6_dsp (implementation
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
/* i.MX8QX systemInit */
  SystemInitHook();
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate (void) {
/* i.MX8QX systemCoreClockUpdate */
}

/* ----------------------------------------------------------------------------
   -- SystemInitHook()
   ---------------------------------------------------------------------------- */

__attribute__ ((weak)) void SystemInitHook (void) {
  /* Void implementation of the weak function. */
}
