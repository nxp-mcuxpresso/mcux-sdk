/*
** ###################################################################
**     Processor:           MIMXRT798SGFOA_ezhv
**     Compilers:           LLVM Compiler
**
**     Reference manual:    iMXRT700RM Rev.1, 08/2022
**     Version:             rev. 1.0, 2022-08-01
**     Build:               b221115
**
**     Copyright 2024 NXP
**     All rights reserved.
**
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
 * @brief Device specific configuration file for MIMXRT798S_ezhv (header
 *        file)
 */

#ifndef _SYSTEM_MIMXRT798S_ezhv_H_
#define _SYSTEM_MIMXRT798S_ezhv_H_         /**< Symbol preventing repeated inclusion */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define DEFAULT_SYSTEM_CLOCK 192000000u /* Default System clock value */
#ifndef CLK_XTAL_OSC_CLK
#define CLK_XTAL_OSC_CLK 24000000u      /* Default XTAL OSC clock, set to 0 when external CLKIN is used */
#endif
#ifndef CLK_EXT_CLKIN
#define CLK_EXT_CLKIN 0u /* Default external CLKIN pin clock, set to 0 when XTAL OSC is used */
#endif
#define CLK_OSC_CLK ((CLK_XTAL_OSC_CLK != 0U) ? CLK_XTAL_OSC_CLK : CLK_EXT_CLKIN)

#define CLK_RTC_32K_CLK      32768u     /* RTC oscillator 32 kHz (32k_clk) */
#define CLK_LPOSC_1MHZ       1000000u   /* Low power oscillator 1 MHz (1m_lposc) */
#define CLK_FRO0_DEFAULT_CLK 300000000u /* FRO0 default clock frequency (fro0_max) */
#define CLK_FRO1_MAX_CLK     192000000u /* FRO1 max clock frequency (fro1) */
#define CLK_FRO2_DEFAULT_CLK 196000000u /* FRO2 default clock frequency (fro2_max) */

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

#endif  /* _SYSTEM_MIMXRT798S_ezhv_H_ */
