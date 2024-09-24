/*
** ###################################################################
**     Processors:          MIMXRT798SGAWAR_ezhv
**                          MIMXRT798SGFOA_ezhv
**
**     Compilers:           LLVM
**
**     Reference manual:    iMXRT700RM Rev.1, 06/2023
**     Version:             rev. 1.0, 2022-08-01
**     Build:               b231008
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2023 NXP
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2022-08-01)
**         Initial version.
**
** ###################################################################
*/

/*!
 * @file MIMXRT798S_ezhv
 * @version 1.0
 * @date 2022-08-01
 * @brief Device specific configuration file for MIMXRT798S_ezhv
 *        (implementation file)
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"

/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */

uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;

/* ----------------------------------------------------------------------------
   -- SystemInit()
   ---------------------------------------------------------------------------- */

__attribute__((weak)) void SystemInit(void)
{
    SystemInitHook();
}

/* ----------------------------------------------------------------------------
   -- SystemInitHook()
   ---------------------------------------------------------------------------- */

__attribute__((weak)) void SystemInitHook(void)
{
    /* Void implementation of the weak function. */
}
