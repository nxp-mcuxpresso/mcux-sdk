/*
** ###################################################################
**     Processors:          MIMX8MD7CVAHZ
**                          MIMX8MD7DVAJZ
**
**     Compilers:           Keil ARM C/C++ Compiler
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**
**     Reference manual:    IMX8MDQLQRM, Rev. 0, Jan. 2018
**     Version:             rev. 4.0, 2018-01-26
**     Build:               b180903
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
**     - rev. 1.0 (2017-01-10)
**         Initial version.
**     - rev. 2.0 (2017-04-27)
**         Rev.B Header EAR1
**     - rev. 3.0 (2017-07-19)
**         Rev.C Header EAR2
**     - rev. 4.0 (2018-01-26)
**         Rev.D Header RFP
**
** ###################################################################
*/

/*!
 * @file MIMX8MD7_cm4
 * @version 4.0
 * @date 2018-01-26
 * @brief Device specific configuration file for MIMX8MD7_cm4 (header file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#ifndef _SYSTEM_MIMX8MD7_cm4_H_
#define _SYSTEM_MIMX8MD7_cm4_H_                  /**< Symbol preventing repeated inclusion */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


/* i.MX8MQ Definitions */
#ifndef DISABLE_WDOG
  #define DISABLE_WDOG      1
#endif
/* Define clock source values */
#define CLK_P_N_FREQ                      0u                  /* The value could be changeD according to the  actual usage */
#define CPU_XTAL_SOSC_CLK_25MHZ           25000000u           /* Value of the external System Oscillator Clock(SOSC) frequency in Hz */
#define CPU_XTAL_SOSC_CLK_27MHZ           27000000u           /* Value of the external System Oscillator Clock(SOSC) frequency in Hz */
#define CPU_HDMI_PHY_CLK_27MHZ            27000000u           /* Value of the HDMI PHY 27M clock frequency in Hz*/
#define DEFAULT_SYSTEM_CLOCK              266666666u          /* Default System clock value */


/**
 * @brief System clock frequency (core clock)
 *
 * The system clock frequency supplied to the SysTick timer and the processor
 * core clock. This variable can be used by the user application to setup the
 * SysTick timer or configure other parameters. It may also be used by debugger to
 * query the frequency of the debug timer or configure the trace clock speed
 * SystemCoreClock is initialized with a correct predefined value.
 */
extern uint32_t SystemCoreClock;

/**
 * @brief Setup the microcontroller system.
 *
 * Typically this function configures the oscillator (PLL) that is part of the
 * microcontroller device. For systems with variable clock speed it also updates
 * the variable SystemCoreClock. SystemInit is called from startup_device file.
 */
void SystemInit (void);

/**
 * @brief Updates the SystemCoreClock variable.
 *
 * It must be called whenever the core clock is changed during program
 * execution. SystemCoreClockUpdate() evaluates the clock register settings and calculates
 * the current core clock.
 */
void SystemCoreClockUpdate (void);

/**
 * @brief SystemInit function hook.
 *
 * This weak function allows to call specific initialization code during the
 * SystemInit() execution.This can be used when an application specific code needs
 * to be called as close to the reset entry as possible (for example the Multicore
 * Manager MCMGR_EarlyInit() function call).
 * NOTE: No global r/w variables can be used in this hook function because the
 * initialization of these variables happens after this function.
 */
void SystemInitHook (void);

#ifdef __cplusplus
}
#endif

#endif  /* _SYSTEM_MIMX8MD7_cm4_H_ */
