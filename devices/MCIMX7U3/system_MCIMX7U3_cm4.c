/*
** ###################################################################
**     Processors:          MCIMX7U3CVP06
**                          MCIMX7U3DVK07
**
**     Compilers:           GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**
**     Reference manual:    IMX7ULPRM, Rev. 0, Nov. 2018
**     Version:             rev. 7.0, 2018-11-05
**     Build:               b200408
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
**     - rev. 1.0 (2016-04-13)
**         Initial version.
**     - rev. 2.0 (2016-07-19)
**         RevC Header ER
**     - rev. 3.0 (2017-02-28)
**         RevD Header ER
**     - rev. 4.0 (2017-05-02)
**         RevE Header ER
**     - rev. 5.0 (2017-12-22)
**         RevA(B0) Header GA
**     - rev. 6.0 (2018-02-01)
**         RevB(B0) Header GA
**     - rev. 7.0 (2018-11-05)
**         RevA(B1) Header
**
** ###################################################################
*/

/*!
 * @file MCIMX7U3_cm4
 * @version 7.0
 * @date 2018-11-05
 * @brief Device specific configuration file for MCIMX7U3_cm4 (implementation
 *        file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include "fsl_device_registers.h"



typedef void (*WdogFuncPtr)(WDOG_Type *wdog);



/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */

uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;

/* ----------------------------------------------------------------------------
   -- SystemInit()
   ---------------------------------------------------------------------------- */

void SystemInit (void) {
#if ((__FPU_PRESENT == 1) && (__FPU_USED == 1))
  SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));    /* set CP10, CP11 Full Access */
#endif /* ((__FPU_PRESENT == 1) && (__FPU_USED == 1)) */


/* i.MX7ULP systemInit */
  WdogFuncPtr WdogDisable;
  uint16_t WdogDisable32[] = {
    0xF64D,   /* MOV R1, #0xD928  */
    0x1128,
    0xF24C,   /* MOV R2, #0xC520  */
    0x5220,
    0xEA4F,   /* LSL R1, R1, #16  */
    0x4101,
    0x4411,   /* ADD R1, R1, R2   */
    0x6041,   /* STR R1, [R0, #4] */
    0xF64F,   /* MOV R1, #0xFFFF  */
    0x71FF,
    0x6081,   /* STR R1, [R0, #8] */
    0x6801,   /* LDR R1, [R0, #0] */
    0xF031,   /* BICS R1, R1, #0x80 */
    0x0180,
    0xF051,   /* ORRS R1, R1, #0x20 */
    0x0120,
    0x6001,   /* STR R1, [R0]     */
    0x4770    /* BX  LR           */
  };
  uint16_t WdogDisable16[] = {
    0xF24C,   /* MOV R1, #0xC520  */
    0x5120,
    0x6041,   /* STR R1, [R0, #4] */
    0xF64D,   /* MOV R1, #0xD928  */
    0x1128,
    0x6041,   /* STR R1, [R0, #4] */
    0xF64F,   /* MOV R1, #0xFFFF  */
    0x71FF,
    0x6081,   /* STR R1, [R0, #8] */
    0x6801,   /* LDR R1, [R0, #0] */
    0xF031,   /* BICS R1, R1, #0x80 */
    0x0180,
    0xF051,   /* ORRS R1, R1, #0x20 */
    0x0120,
    0x6001,   /* STR R1, [R0]     */
    0x4770    /* BX  LR           */
  };
#if (DISABLE_WDOG)
  if ((WDOG0->CS & WDOG_CS_EN_MASK) != 0U)
  {
    /* WDOG has timing requirement to unlock the operation window.
       When running in QSPI flash, it's possible to violate that timing
       requirement. So we put the WDOG operation in RAM */
    /* Is WDOG 32bit access enabled? */
    if ((WDOG0->CS & WDOG_CS_CMD32EN_MASK) != 0U)
    {
      WdogDisable = (WdogFuncPtr)(((uint32_t)WdogDisable32) | 1U); /* thumb code */
    }
    else
    {
      WdogDisable = (WdogFuncPtr)(((uint32_t)WdogDisable16) | 1U); /* thumb code */
    }
    WdogDisable(WDOG0);
  }
#endif /* (DISABLE_WDOG) */
  /* set command to invalidate all ways and write GO bit
     to initiate command */
  LMEM->PCCCR = LMEM_PCCCR_INVW1_MASK | LMEM_PCCCR_INVW0_MASK;
  LMEM->PCCCR |= LMEM_PCCCR_GO_MASK;
  /* Wait until the command completes */
  while ((LMEM->PCCCR & LMEM_PCCCR_GO_MASK) != 0U)
  {}
  /* Enable code bus cache, enable write buffer */
  LMEM->PCCCR = (LMEM_PCCCR_ENWRBUF_MASK | LMEM_PCCCR_ENCACHE_MASK);
  __ISB();
  __DSB();

  SystemInitHook();
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate (void) {


  /* i.MX7ULP systemCoreClockUpdate */
  uint8_t spllMulti[] = {0U, 15U, 16U, 20U, 22U, 25U, 30U, 0U};
  uint32_t SCGOUTClock, apllNum, apllDenom, apllTmp;
  /* Identify current system clock source. */
  switch (SCG0->CSR & SCG_CSR_SCS_MASK)
  {
    /* System OSC */
    case SCG_CSR_SCS(1):
      SCGOUTClock = CPU_XTAL_SOSC_CLK_HZ;
      break;
    /* Slow IRC */
    case SCG_CSR_SCS(2):
      SCGOUTClock = ((0u == (SCG0->SIRCCFG & SCG_SIRCCFG_RANGE_MASK)) ? 4000000u : 16000000u);
      break;
    /* Fast IRC */
    case SCG_CSR_SCS(3):
      SCGOUTClock = 48000000u + ((SCG0->FIRCCFG & SCG_FIRCCFG_RANGE_MASK) >> SCG_FIRCCFG_RANGE_SHIFT) * 4000000u;
      break;
    /* RTC OSC */
    case SCG_CSR_SCS(4):
      SCGOUTClock = 32768u;
      break;
    /* System PLL */
    case SCG_CSR_SCS(6):
      /* System clock from SPLL. */
      SCGOUTClock = (0u == (SCG0->SPLLCFG & SCG_SPLLCFG_SOURCE_MASK)) ? CPU_XTAL_SOSC_CLK_HZ :
                    (48000000u + ((SCG0->FIRCCFG & SCG_FIRCCFG_RANGE_MASK) >> SCG_FIRCCFG_RANGE_SHIFT) * 4000000u);
      SCGOUTClock /= ((SCG0->SPLLCFG & SCG_SPLLCFG_PREDIV_MASK) >> SCG_SPLLCFG_PREDIV_SHIFT) + 1u;
      SCGOUTClock *= spllMulti[((SCG0->SPLLCFG & SCG_SPLLCFG_MULT_MASK) >> SCG_SPLLCFG_MULT_SHIFT)];
      /* Is Core clock from PLL PFD? */
      if (0u != (SCG0->SPLLCFG & SCG_SPLLCFG_PLLS_MASK))
      {
        /* System clock from SPLL PFD. */
        switch (SCG0->SPLLCFG & SCG_SPLLCFG_PFDSEL_MASK)
        {
          case SCG_SPLLCFG_PFDSEL(0):
            SCGOUTClock = (uint32_t)(((uint64_t)SCGOUTClock * 18u) /
                                     ((SCG0->SPLLPFD & SCG_SPLLPFD_PFD0_MASK) >> SCG_SPLLPFD_PFD0_SHIFT));
            break;
          case SCG_SPLLCFG_PFDSEL(1):
            SCGOUTClock = (uint32_t)(((uint64_t)SCGOUTClock * 18u) /
                                     ((SCG0->SPLLPFD & SCG_SPLLPFD_PFD1_MASK) >> SCG_SPLLPFD_PFD1_SHIFT));
            break;
          case SCG_SPLLCFG_PFDSEL(2):
            SCGOUTClock = (uint32_t)(((uint64_t)SCGOUTClock * 18u) /
                                     ((SCG0->SPLLPFD & SCG_SPLLPFD_PFD2_MASK) >> SCG_SPLLPFD_PFD2_SHIFT));
            break;
          case SCG_SPLLCFG_PFDSEL(3):
            SCGOUTClock = (uint32_t)(((uint64_t)SCGOUTClock * 18u) /
                                     ((SCG0->SPLLPFD & SCG_SPLLPFD_PFD3_MASK) >> SCG_SPLLPFD_PFD3_SHIFT));
            break;
          default:
            SCGOUTClock = 0u;
            break;
        }
      }
      break;
    /* Auxiliary PLL */
    case SCG_CSR_SCS(5):
      /* System clock from APLL. */
      SCGOUTClock = (0u == (SCG0->APLLCFG & SCG_APLLCFG_SOURCE_MASK)) ? CPU_XTAL_SOSC_CLK_HZ :
                    (48000000u + ((SCG0->FIRCCFG & SCG_FIRCCFG_RANGE_MASK) >> SCG_FIRCCFG_RANGE_SHIFT) * 4000000u);
      SCGOUTClock /= ((SCG0->APLLCFG & SCG_APLLCFG_PREDIV_MASK) >> SCG_APLLCFG_PREDIV_SHIFT) + 1u;
      apllNum = SCG0->APLLNUM;
      apllDenom = SCG0->APLLDENOM;
      apllTmp = (uint32_t)((uint64_t)SCGOUTClock * ((uint64_t)apllNum) / ((uint64_t)apllDenom));
      SCGOUTClock = SCGOUTClock * ((SCG0->APLLCFG & SCG_APLLCFG_MULT_MASK) >> SCG_APLLCFG_MULT_SHIFT) + apllTmp;
      /* Is Core clock from PLL directly? */
      if (0u == (SCG0->APLLCFG & SCG_APLLCFG_PLLS_MASK))
      {
        /* System clock from APLL directly. */
        SCGOUTClock /= (((SCG0->APLLCFG & SCG_APLLCFG_PLLPOSTDIV1_MASK) >> SCG_APLLCFG_PLLPOSTDIV1_SHIFT) + 1u);
        SCGOUTClock /= (((SCG0->APLLCFG & SCG_APLLCFG_PLLPOSTDIV2_MASK) >> SCG_APLLCFG_PLLPOSTDIV2_SHIFT) + 1u);
      }
      else
      {
        /* System clock from APLL PFD. */
        switch (SCG0->APLLCFG & SCG_APLLCFG_PFDSEL_MASK)
        {
          case SCG_APLLCFG_PFDSEL(0):
            SCGOUTClock = (uint32_t)(((uint64_t)SCGOUTClock * 18u) /
                                     ((SCG0->APLLPFD & SCG_APLLPFD_PFD0_MASK) >> SCG_APLLPFD_PFD0_SHIFT));
            break;
          case SCG_APLLCFG_PFDSEL(1):
            SCGOUTClock = (uint32_t)(((uint64_t)SCGOUTClock * 18u) /
                                     ((SCG0->APLLPFD & SCG_APLLPFD_PFD1_MASK) >> SCG_APLLPFD_PFD1_SHIFT));
            break;
          case SCG_APLLCFG_PFDSEL(2):
            SCGOUTClock = (uint32_t)(((uint64_t)SCGOUTClock * 18u) /
                                     ((SCG0->APLLPFD & SCG_APLLPFD_PFD2_MASK) >> SCG_APLLPFD_PFD2_SHIFT));
            break;
          case SCG_APLLCFG_PFDSEL(3):
            SCGOUTClock = (uint32_t)(((uint64_t)SCGOUTClock * 18u) /
                                     ((SCG0->APLLPFD & SCG_APLLPFD_PFD3_MASK) >> SCG_APLLPFD_PFD3_SHIFT));
            break;
          default:
            SCGOUTClock = 0u;
            break;
        }
      }
      break;
    /* Can not identify core clock source. */
    default:
      SCGOUTClock = 0u;
      break;
  }
  /* Divide the SCG output clock to get the M4 Core clock. */
  SCGOUTClock /= ((SCG0->CSR & SCG_CSR_DIVCORE_MASK) >> SCG_CSR_DIVCORE_SHIFT) + 1u;
  /* Update System Core Clock. */
  SystemCoreClock = SCGOUTClock;

}

/* ----------------------------------------------------------------------------
   -- SystemInitHook()
   ---------------------------------------------------------------------------- */

__attribute__ ((weak)) void SystemInitHook (void) {
  /* Void implementation of the weak function. */
}
