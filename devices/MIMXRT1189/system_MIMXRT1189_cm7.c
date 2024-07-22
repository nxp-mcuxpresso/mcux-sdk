/*
** ###################################################################
**     Processors:          MIMXRT1189CVM8B_cm7
**                          MIMXRT1189XVM8B_cm7
**
**     Compilers:           GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**                          MCUXpresso Compiler
**
**     Reference manual:    IMXRT1180RM, Rev 2, 12/2022
**     Version:             rev. 0.1, 2021-03-09
**     Build:               b231213
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
**     - rev. 0.1 (2021-03-09)
**         Initial version.
**
** ###################################################################
*/

/*!
 * @file MIMXRT1189_cm7
 * @version 1.0
 * @date 2023-12-13
 * @brief Device specific configuration file for MIMXRT1189_cm7 (implementation
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

void SystemInit(void)
{
#if ((__FPU_PRESENT == 1) && (__FPU_USED == 1))
    SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2)); /* set CP10, CP11 Full Access */
#endif                                                 /* ((__FPU_PRESENT == 1) && (__FPU_USED == 1)) */

#if defined(__MCUXPRESSO)
    extern uint32_t g_pfnVectors[]; // Vector table defined in startup code
    SCB->VTOR = (uint32_t)g_pfnVectors;
#endif

    /* Watchdog disable */

#if (DISABLE_WDOG)
    if ((RTWDOG1->CS & RTWDOG_CS_CMD32EN_MASK) != 0U)
    {
        RTWDOG1->CNT = 0xD928C520U; /* 0xD928C520U is the update key */
    }
    else
    {
        RTWDOG1->CNT = 0xC520U;
        RTWDOG1->CNT = 0xD928U;
    }
    RTWDOG1->TOVAL = 0xFFFF;
    RTWDOG1->CS    = (uint32_t)((RTWDOG1->CS) & ~RTWDOG_CS_EN_MASK) | RTWDOG_CS_UPDATE_MASK;

    if ((RTWDOG2->CS & RTWDOG_CS_CMD32EN_MASK) != 0U)
    {
        RTWDOG2->CNT = 0xD928C520U; /* 0xD928C520U is the update key */
    }
    else
    {
        RTWDOG2->CNT = 0xC520U;
        RTWDOG2->CNT = 0xD928U;
    }
    RTWDOG2->TOVAL = 0xFFFF;
    RTWDOG2->CS    = (uint32_t)((RTWDOG2->CS) & ~RTWDOG_CS_EN_MASK) | RTWDOG_CS_UPDATE_MASK;

    if ((RTWDOG3->CS & RTWDOG_CS_CMD32EN_MASK) != 0U)
    {
        RTWDOG3->CNT = 0xD928C520U; /* 0xD928C520U is the update key */
    }
    else
    {
        RTWDOG3->CNT = 0xC520U;
        RTWDOG3->CNT = 0xD928U;
    }
    RTWDOG3->TOVAL = 0xFFFF;
    RTWDOG3->CS    = (uint32_t)((RTWDOG3->CS) & ~RTWDOG_CS_EN_MASK) | RTWDOG_CS_UPDATE_MASK;

    if ((RTWDOG4->CS & RTWDOG_CS_CMD32EN_MASK) != 0U)
    {
        RTWDOG4->CNT = 0xD928C520U; /* 0xD928C520U is the update key */
    }
    else
    {
        RTWDOG4->CNT = 0xC520U;
        RTWDOG4->CNT = 0xD928U;
    }
    RTWDOG4->TOVAL = 0xFFFF;
    RTWDOG4->CS    = (uint32_t)((RTWDOG4->CS) & ~RTWDOG_CS_EN_MASK) | RTWDOG_CS_UPDATE_MASK;

    if ((RTWDOG5->CS & RTWDOG_CS_CMD32EN_MASK) != 0U)
    {
        RTWDOG5->CNT = 0xD928C520U; /* 0xD928C520U is the update key */
    }
    else
    {
        RTWDOG5->CNT = 0xC520U;
        RTWDOG5->CNT = 0xD928U;
    }
    RTWDOG5->TOVAL = 0xFFFF;
    RTWDOG5->CS    = (uint32_t)((RTWDOG5->CS) & ~RTWDOG_CS_EN_MASK) | RTWDOG_CS_UPDATE_MASK;

#endif /* (DISABLE_WDOG) */

    /* Disable Systick which might be enabled by bootrom */
    if ((SysTick->CTRL & SysTick_CTRL_ENABLE_Msk) != 0U)
    {
        SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    }

    /* Enable instruction cache */
    if (SCB_CCR_IC_Msk != (SCB_CCR_IC_Msk & SCB->CCR))
    {
        SCB_EnableICache();
    }

    /* Enable entry to thread mode when divide by zero */
    SCB->CCR |= SCB_CCR_DIV_0_TRP_Msk;
    __DSB();
    __ISB();

    /*
     * Workaround for mcux cm7 standalone project debug.
     * To debug cm7 standalone project in mcux, it use cm33 script to kick-off
     * cm7 core, Some early MCUX version, say 11.8.0, the eDMA4 error flag is set
     * after the kick-off script executed, so as a workaround, clear the
     * eDMA4 error flag at the beginning.
     * note: it is supposed no side effect for latest mcux version.
     */
#if (defined(__MCUXPRESSO) && !(defined(__MULTICORE_M7SLAVE) || defined(MULTICORE_APP)))
    DMA4->TCD[0].CH_ES = DMA_CH_ES_ERR_MASK;
#endif

    SystemInitHook();
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate(void)
{
    /* The functionaliy has been implemented in clock_config.c */
}

/* ----------------------------------------------------------------------------
   -- SystemInitHook()
   ---------------------------------------------------------------------------- */

__attribute__((weak)) void SystemInitHook(void)
{
    /* Void implementation of the weak function. */
}

