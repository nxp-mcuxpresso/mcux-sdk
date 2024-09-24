/*
** ###################################################################
**     Processors:          MIMXRT735SGAWAR_cm33_core1
**                          MIMXRT735SGFOA_cm33_core1
**
**     Compilers:           GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**                          MCUXpresso Compiler
**
**     Reference manual:    iMXRT700RM Rev.2 DraftA, 05/2024
**     Version:             rev. 2.0, 2024-05-28
**     Build:               b240528
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
**     - rev. 1.0 (2022-09-15)
**         Initial version.
**     - rev. 2.0 (2024-05-28)
**         Rev2 DraftA.
**
** ###################################################################
*/

/*!
 * @file MIMXRT735S_cm33_core1
 * @version 1.0
 * @date 2024-05-28
 * @brief Device specific configuration file for MIMXRT735S_cm33_core1 (header file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#ifndef _SYSTEM_MIMXRT735S_cm33_core1_H_
#define _SYSTEM_MIMXRT735S_cm33_core1_H_ /**< Symbol preventing repeated inclusion */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define DEFAULT_SYSTEM_CLOCK 64000000u /* Default System clock value */
#ifndef CLK_XTAL_OSC_CLK
#define CLK_XTAL_OSC_CLK 24000000u     /* Default XTAL OSC clock, set to 0 when external CLKIN is used */
#endif
#ifndef CLK_EXT_CLKIN
#define CLK_EXT_CLKIN 0u /* Default external CLKIN pin clock, set to 0 when XTAL OSC is used */
#endif
#define CLK_OSC_CLK ((CLK_XTAL_OSC_CLK != 0U) ? CLK_XTAL_OSC_CLK : CLK_EXT_CLKIN)

#define CLK_RTC_32K_CLK      32768u     /* RTC oscillator 32 kHz (32k_clk) */
#define CLK_LPOSC_1MHZ       1000000u   /* Low power oscillator 1 MHz (1m_lposc) */
#define CLK_FRO1_MAX_CLK     192000000u /* FRO1 max clock frequency (fro1) */
#define CLK_FRO2_DEFAULT_CLK 196000000u /* FRO2 default clock frequency (fro2_max) */

#define FRO_TUNER_USED(base) ((base->TEXPCNT.RW & FRO_TEXPCNT_TEXPCNT_MASK) != 0u)
/* FRO frequency = TRIMCNT * (divided ref clock frequency) / REFCLKCNT. */
#define FRO_FREQ_GET_FROM_TUNER(base)                                                       \
    ((uint32_t)((uint64_t)(base->TRIMCNT.RW) *                                              \
                (uint64_t)(CLK_OSC_CLK / ((base->CNFG1.RW & FRO_CNFG1_REFDIV_MASK) + 1U)) / \
                ((base->CNFG1.RW & FRO_CNFG1_RFCLKCNT_MASK) >> FRO_CNFG1_RFCLKCNT_SHIFT)))
#define CLK_FRO2_CLK (FRO_TUNER_USED(FRO2) ? FRO_FREQ_GET_FROM_TUNER(FRO2) : CLK_FRO2_DEFAULT_CLK)

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
void SystemInit(void);

/**
 * @brief Updates the SystemCoreClock variable.
 *
 * It must be called whenever the core clock is changed during program
 * execution. SystemCoreClockUpdate() evaluates the clock register settings and calculates
 * the current core clock.
 */
void SystemCoreClockUpdate(void);

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
void SystemInitHook(void);

#ifdef __cplusplus
}
#endif

#endif /* _SYSTEM_MIMXRT735S_cm33_core1_H_ */
