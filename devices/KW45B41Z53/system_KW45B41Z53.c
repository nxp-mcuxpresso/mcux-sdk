/*
** ###################################################################
**     Processors:          KW45B41Z53AFPA
**                          KW45B41Z53AFTA
**
**     Compilers:           GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**                          MCUXpresso Compiler
**
**     Reference manual:    Rev. 6, 05/22/2022
**     Version:             rev. 1.0, 2023-09-05
**     Build:               b240227
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
**     - rev. 1.0 (2020-05-12)
**         Initial version.
**
** ###################################################################
*/

/*!
 * @file KW45B41Z53
 * @version 1.0
 * @date 2020-05-12
 * @brief Device specific configuration file for KW45B41Z53 (implementation file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include "fsl_device_registers.h"

#if defined(USE_SMU2_AS_SYSTEM_MEMORY)
#define SMU2_CM33_BASE_ADDR     0x489C0000ULL
#define SMU2_CM33_END_ADDR      0x489CA000ULL
#define SMU2_MAIR_IDX           1
#endif

#if defined(USE_PB_RAM_AS_SYSTEM_MEMORY)
#define PB_RAM_CM33_BASE_ADDR   0x48A08000ULL
#define PB_RAM_CM33_END_ADDR    0x48A0A000ULL
#define PB_RAM_MAIR_IDX         2
#endif

/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */

uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;

/* ----------------------------------------------------------------------------
   -- SystemInit()
   ---------------------------------------------------------------------------- */

__attribute__ ((weak)) void SystemInit (void) {
#if ((__FPU_PRESENT == 1) && (__FPU_USED == 1))
  SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));    /* set CP10, CP11 Full Access in Secure mode */
  #if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  SCB_NS->CPACR |= ((3UL << 10*2) | (3UL << 11*2));    /* set CP10, CP11 Full Access in Non-secure mode */
  #endif /* (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
#endif /* ((__FPU_PRESENT == 1) && (__FPU_USED == 1)) */

#if (DISABLE_WDOG)
  while ((WDOG0->CS & WDOG_CS_RCS_MASK) != WDOG_CS_RCS_MASK)
  {
  }

  if ((WDOG0->CS & WDOG_CS_CMD32EN_MASK) != 0U)
  {
      WDOG0->CNT = 0xD928C520U;
  }
  else
  {
      WDOG0->CNT = 0xC520U;
      WDOG0->CNT = 0xD928U;
  }

  while ((WDOG0->CS & WDOG_CS_ULK_MASK) != WDOG_CS_ULK_MASK)
  {
  }

  WDOG0->TOVAL = 0xFFFF;
  WDOG0->CS = (uint32_t) ((WDOG0->CS) & ~WDOG_CS_EN_MASK) | WDOG_CS_UPDATE_MASK;

  while ((WDOG0->CS & WDOG_CS_RCS_MASK) != WDOG_CS_RCS_MASK)
  {
  }
#endif /* (DISABLE_WDOG) */

#if defined(__MCUXPRESSO)
    extern void(*const g_pfnVectors[]) (void);
    SCB->VTOR = (uint32_t) &g_pfnVectors;
#endif

#if defined(USE_SMU2_AS_SYSTEM_MEMORY)
    /* The SMU2 memory area in the default system memory map is configured as
     * "device memory". This means that any unaligned access will fault, when
     * driven from the CM33 core. Since we want to be able to use this as an
     * extension to the system SRAM, remap it here as "memory"
     * This is done by adding an entry to the MPU. This is done in 2 steps, as
     * seen below. The 3rd step is to actually enable the MPU.
     *
     * Step 1: Add an entry in the MPU by setting the MPU_RNR register to select
     *         the position in the table, then by writing the MPU_RLAR &
     *         MPU_RBAR registers. For the RLAR, also set the Enable bit and the
     *         corresponding index in the MPU_MAIR0/1 registers.
     */
    ARM_MPU_SetRegionEx(MPU, SMU2_MAIR_IDX,
                        SMU2_CM33_BASE_ADDR,
                        SMU2_CM33_END_ADDR |
                        (MPU_RLAR_EN_Msk << MPU_RLAR_EN_Pos) |
                            (SMU2_MAIR_IDX << MPU_RLAR_AttrIndx_Pos));
    /*
     * Step 2: Set the attributes in the corresponding index in the MPU_MAIR
     * registers (the index is the same index used when adding the entry in the
     * MPU via the MPU_RNR register.
     */
    ARM_MPU_SetMemAttrEx(MPU,
                         SMU2_MAIR_IDX,
                         ARM_MPU_ATTR(ARM_MPU_ATTR_NON_CACHEABLE,
                                      ARM_MPU_ATTR_NON_CACHEABLE));
#endif

#if defined(USE_PB_RAM_AS_SYSTEM_MEMORY)
    /* See Step 1 from USE_SMU2_AS_SYSTEM_MEMORY */
    ARM_MPU_SetRegionEx(MPU, PB_RAM_MAIR_IDX,
                        PB_RAM_CM33_BASE_ADDR,
                        PB_RAM_CM33_END_ADDR |
                        (MPU_RLAR_EN_Msk << MPU_RLAR_EN_Pos) |
                            (PB_RAM_MAIR_IDX << MPU_RLAR_AttrIndx_Pos));
    /* See Step 2 from USE_SMU2_AS_SYSTEM_MEMORY */
    ARM_MPU_SetMemAttrEx(MPU,
                         PB_RAM_MAIR_IDX,
                         ARM_MPU_ATTR(ARM_MPU_ATTR_NON_CACHEABLE,
                                      ARM_MPU_ATTR_NON_CACHEABLE));
#endif
#if defined(USE_SMU2_AS_SYSTEM_MEMORY) || \
    defined(USE_PB_RAM_AS_SYSTEM_MEMORY)
    /*
     * Step 3: Enable the MPU, and also enable default memory map for the
     *         privileged software. This is needed due to 2 reasons:
     *         1. we run as privileged software (TZ secure mode)
     *         2. we don't "rewrite" set all the necessary memory zones in the
     *            MPU; this means that once MPU is enabled, not even the
     *            code area will be available to the core, leading to the core
     *            hanging (no response to the read requests)
     *
     */
    ARM_MPU_Enable(MPU_CTRL_PRIVDEFENA_Msk);
#endif
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
