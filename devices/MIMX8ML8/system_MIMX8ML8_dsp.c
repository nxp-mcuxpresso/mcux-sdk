/*
** ###################################################################
**     Processors:          MIMX8ML8CVNKZ_dsp
**                          MIMX8ML8DVNLZ_dsp
**
**     Compiler:            XCC Compiler
**     Reference manual:    IMX8MPRM, Rev.D, 12/2020
**     Version:             rev. 5.0, 2021-03-01
**     Build:               b230302
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2023 NXP
**     All rights reserved.
**
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2019-10-11)
**         Initial version.
**     - rev. 2.0 (2020-02-21)
**         Rev.B Header.
**     - rev. 3.0 (2020-06-22)
**         Rev.C Header.
**     - rev. 4.0 (2020-11-16)
**         Rev.D Header.
**     - rev. 5.0 (2021-03-01)
**         Rev.D Header Final.
**
** ###################################################################
*/

/*!
 * @file MIMX8ML8_dsp
 * @version 5.0
 * @date 2021-03-01
 * @brief Device specific configuration file for MIMX8ML8_dsp (implementation
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
  SystemInitHook();
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
