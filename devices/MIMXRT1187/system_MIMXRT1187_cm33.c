/*
** ###################################################################
**     Processors:          MIMXRT1187AVM8B_cm33
**                          MIMXRT1187CVM8B_cm33
**                          MIMXRT1187XVM8B_cm33
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
 * @file MIMXRT1187_cm33
 * @version 1.0
 * @date 2023-12-13
 * @brief Device specific configuration file for MIMXRT1187_cm33 (implementation file)
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

    if ((XCACHE_PC->CCR & XCACHE_CCR_ENCACHE_MASK) == 0U) /* set XCACHE if not configured */
    {
        /* set command to invalidate all ways and write GO bit to initiate command */
        XCACHE_PC->CCR = XCACHE_CCR_INVW1_MASK | XCACHE_CCR_INVW0_MASK;
        XCACHE_PC->CCR |= XCACHE_CCR_GO_MASK;
        /* Wait until the command completes */
        while ((XCACHE_PC->CCR & XCACHE_CCR_GO_MASK) != 0U)
        {
        }
        /* Enable cache */
        XCACHE_PC->CCR = XCACHE_CCR_ENCACHE_MASK;

        __ISB();
        __DSB();
    }

    /* Enable entry to thread mode when divide by zero */
    SCB->CCR |= SCB_CCR_DIV_0_TRP_Msk;
    __DSB();
    __ISB();

    BOARD_InitHook();

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

/* ----------------------------------------------------------------------------
   -- BOARD_InitHook()
   ---------------------------------------------------------------------------- */
__attribute__((weak)) void BOARD_InitHook(void)
{
    /* Void implementation of the weak function. */
}

/* ----------------------------------------------------------------------------
   -- InitCM7DMA()
   The function is used to clear a region of memory of size 128KB to zero
   ---------------------------------------------------------------------------- */
static void InitCM7DMA(uint32_t targetAddr)
{
    DMA4->TCD[0].SADDR          = 0x20484000;
    DMA4->TCD[0].DADDR          = targetAddr;
    DMA4->TCD[0].NBYTES_MLOFFNO = 0x20000;
    DMA4->TCD[0].CITER_ELINKNO  = 0x1;
    DMA4->TCD[0].BITER_ELINKNO  = 0x1;
    DMA4->TCD[0].ATTR           = 0x303;
    DMA4->TCD[0].SOFF           = 0;
    DMA4->TCD[0].DOFF           = 0x8;
    DMA4->TCD[0].CH_CSR         = 0x7;
    DMA4->TCD[0].CSR            = 0x8;
    DMA4->TCD[0].CSR            = 0x9;

    DMA4->TCD[0].CH_CSR = 0x40000006;

    while ((DMA4->TCD[0].CH_CSR & DMA4_CH_CSR_DONE_MASK) == 0UL)
    {
    }

    DMA4->TCD[0].CH_CSR = (1UL << DMA4_CH_CSR_DONE_SHIFT);
}

/* ----------------------------------------------------------------------------
   -- Prepare_CM7()
   The function prepares CM7, gives init VTOR, release it and clear its TCM memory
   to avoid any ECC error
   ---------------------------------------------------------------------------- */
void Prepare_CM7(uint32_t m7_vtor)
{
    PHY_LDO->CTRL0.RW =
        PHY_LDO_CTRL0_LINREG_OUTPUT_TRG(0x10) | PHY_LDO_CTRL0_LINREG_ILIMIT_EN_MASK | PHY_LDO_CTRL0_LINREG_EN_MASK;
    ANADIG_PLL->ARM_PLL_CTRL = ANADIG_PLL_ARM_PLL_CTRL_ARM_PLL_GATE_MASK | ANADIG_PLL_ARM_PLL_CTRL_POWERUP_MASK |
                               ANADIG_PLL_ARM_PLL_CTRL_DIV_SELECT(0x84);
    ANADIG_PLL->ARM_PLL_CTRL = ANADIG_PLL_ARM_PLL_CTRL_ENABLE_CLK_MASK | ANADIG_PLL_ARM_PLL_CTRL_POWERUP_MASK |
                               ANADIG_PLL_ARM_PLL_CTRL_DIV_SELECT(0x84);

#if !(defined(BOARD_USE_EXT_PMIC) && BOARD_USE_EXT_PMIC)
    DCDC->REG3 = DCDC_REG3_REG_FBK_SEL(2) | DCDC_REG3_DISABLE_IDLE_SKIP_MASK | DCDC_REG3_DISABLE_PULSE_SKIP_MASK;
#endif

    // give init VTOR and release CM7
    BLK_CTRL_S_AONMIX->M7_CFG = (BLK_CTRL_S_AONMIX->M7_CFG & (~BLK_CTRL_S_AONMIX_M7_CFG_INITVTOR_MASK)) |
                                BLK_CTRL_S_AONMIX_M7_CFG_INITVTOR(m7_vtor >> 7);
    SRC_GENERAL_REG->SCR = SRC_GENERAL_SCR_BT_RELEASE_M7_MASK;

    // Clear CM7 TCM
    InitCM7DMA(0x303C0000);
    InitCM7DMA(0x303E0000);
    InitCM7DMA(0x30400000);
    InitCM7DMA(0x30420000);
}
