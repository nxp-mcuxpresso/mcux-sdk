/*
** ###################################################################
**     Processors:          MIMX8MM5CVTKZ
**                          MIMX8MM5DVTLZ
**
**     Compilers:           GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**
**     Reference manual:    MX8MMRM, Rev. 0, 02/2019
**     Version:             rev. 4.0, 2019-02-18
**     Build:               b190228
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2019 NXP
**     All rights reserved.
**
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2018-03-26)
**         Initial version.
**     - rev. 2.0 (2018-07-20)
**         Rev.A Header EAR
**     - rev. 3.0 (2018-10-24)
**         Rev.B Header PRC
**     - rev. 4.0 (2019-02-18)
**         Rev.0 Header RFP
**
** ###################################################################
*/

/*!
 * @file MIMX8MM5_cm4
 * @version 4.0
 * @date 2019-02-18
 * @brief Device specific configuration file for MIMX8MM5_cm4 (implementation
 *        file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include "fsl_device_registers.h"

/*!
 * @brief CCM reg macros to extract corresponding registers bit field.
 */
#define CCM_BIT_FIELD_VAL(val, mask, shift) (((val)&mask) >> shift)

/*!
 * @brief CCM reg macros to get corresponding registers values.
 */
#define CCM_ANALOG_REG_VAL(base, off) (*((volatile uint32_t *)((uint32_t)(base) + (off))))

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
uint32_t GetFracPllFreq(const volatile uint32_t *base);
uint32_t GetIntegerPllFreq(const volatile uint32_t *base);

uint32_t GetFracPllFreq(const volatile uint32_t *base)
{
    uint32_t fracCfg0   = CCM_ANALOG_REG_VAL(base, 0U);
    uint32_t fracCfg1   = CCM_ANALOG_REG_VAL(base, 4U);
    uint32_t fracCfg2   = CCM_ANALOG_REG_VAL(base, 8U);
    uint32_t refClkFreq = 0U;
    uint64_t fracClk    = 0U;

    uint8_t refSel   = (uint8_t)CCM_BIT_FIELD_VAL(fracCfg0, CCM_ANALOG_AUDIO_PLL1_GEN_CTRL_PLL_REF_CLK_SEL_MASK,
                                                CCM_ANALOG_AUDIO_PLL1_GEN_CTRL_PLL_REF_CLK_SEL_SHIFT);
    uint32_t mainDiv = CCM_BIT_FIELD_VAL(fracCfg1, CCM_ANALOG_AUDIO_PLL1_FDIV_CTL0_PLL_MAIN_DIV_MASK,
                                         CCM_ANALOG_AUDIO_PLL1_FDIV_CTL0_PLL_MAIN_DIV_SHIFT);
    uint8_t preDiv   = (uint8_t)CCM_BIT_FIELD_VAL(fracCfg1, CCM_ANALOG_AUDIO_PLL1_FDIV_CTL0_PLL_PRE_DIV_MASK,
                                                CCM_ANALOG_AUDIO_PLL1_FDIV_CTL0_PLL_PRE_DIV_SHIFT);
    uint8_t postDiv  = (uint8_t)CCM_BIT_FIELD_VAL(fracCfg1, CCM_ANALOG_AUDIO_PLL1_FDIV_CTL0_PLL_POST_DIV_MASK,
                                                 CCM_ANALOG_AUDIO_PLL1_FDIV_CTL0_PLL_POST_DIV_SHIFT);
    uint32_t dsm     = CCM_BIT_FIELD_VAL(fracCfg2, CCM_ANALOG_AUDIO_PLL1_FDIV_CTL1_PLL_DSM_MASK,
                                     CCM_ANALOG_AUDIO_PLL1_FDIV_CTL1_PLL_DSM_SHIFT);

    if (refSel == 0U) /* OSC 24M Clock */
    {
        refClkFreq = CPU_XTAL_SOSC_CLK_24MHZ;
    }
    else
    {
        refClkFreq = CLK_PAD_CLK; /* CLK_PAD_CLK Clock, please note that the value is 0hz by default, it could be set at
                                     system_MIMX8MMx_cm4.h :96 */
    }
    fracClk = (uint64_t)refClkFreq * ((uint64_t)mainDiv * 65536UL + (uint64_t)dsm) /
              ((uint64_t)65536UL * preDiv * (1UL << postDiv));

    return (uint32_t)fracClk;
}

uint32_t GetIntegerPllFreq(const volatile uint32_t *base)
{
    uint32_t integerCfg0 = CCM_ANALOG_REG_VAL(base, 0U);
    uint32_t integerCfg1 = CCM_ANALOG_REG_VAL(base, 4U);
    uint32_t refClkFreq  = 0U;
    uint64_t pllOutClock = 0U;

    uint8_t pllBypass = (uint8_t)CCM_BIT_FIELD_VAL(integerCfg0, CCM_ANALOG_SYS_PLL1_GEN_CTRL_PLL_BYPASS_MASK,
                                                   CCM_ANALOG_SYS_PLL1_GEN_CTRL_PLL_BYPASS_SHIFT);
    uint8_t refSel    = (uint8_t)CCM_BIT_FIELD_VAL(integerCfg0, CCM_ANALOG_SYS_PLL1_GEN_CTRL_PLL_REF_CLK_SEL_MASK,
                                                CCM_ANALOG_SYS_PLL1_GEN_CTRL_PLL_REF_CLK_SEL_SHIFT);
    uint32_t mainDiv  = CCM_BIT_FIELD_VAL(integerCfg1, CCM_ANALOG_SYS_PLL1_FDIV_CTL0_PLL_MAIN_DIV_MASK,
                                         CCM_ANALOG_SYS_PLL1_FDIV_CTL0_PLL_MAIN_DIV_SHIFT);
    uint8_t preDiv    = (uint8_t)CCM_BIT_FIELD_VAL(integerCfg1, CCM_ANALOG_SYS_PLL1_FDIV_CTL0_PLL_PRE_DIV_MASK,
                                                CCM_ANALOG_SYS_PLL1_FDIV_CTL0_PLL_PRE_DIV_SHIFT);
    uint8_t postDiv   = (uint8_t)CCM_BIT_FIELD_VAL(integerCfg1, CCM_ANALOG_SYS_PLL1_FDIV_CTL0_PLL_POST_DIV_MASK,
                                                 CCM_ANALOG_SYS_PLL1_FDIV_CTL0_PLL_POST_DIV_SHIFT);

    if (refSel == 0U) /* OSC 24M Clock */
    {
        refClkFreq = CPU_XTAL_SOSC_CLK_24MHZ;
    }
    else
    {
        refClkFreq = CLK_PAD_CLK; /* CLK_PAD_CLK Clock, please note that the value is 0hz by default, it could be set at
                                     system_MIMX8MMx_cm4.h :96 */
    }

    if (pllBypass != 0U)
    {
        pllOutClock = refClkFreq;
    }

    else
    {
        pllOutClock = (uint64_t)refClkFreq * mainDiv / (((uint64_t)(1U) << postDiv) * preDiv);
    }

    return (uint32_t)pllOutClock;
}

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

    /* Initialize Cache */
    /* Enable Code Bus Cache */
    /* set command to invalidate all ways, and write GO bit to initiate command */
    LMEM->PCCCR |= LMEM_PCCCR_INVW1_MASK | LMEM_PCCCR_INVW0_MASK;
    LMEM->PCCCR |= LMEM_PCCCR_GO_MASK;
    /* Wait until the command completes */
    while ((LMEM->PCCCR & LMEM_PCCCR_GO_MASK) != 0U)
    {
    }
    /* Enable cache, enable write buffer */
    LMEM->PCCCR |= (LMEM_PCCCR_ENWRBUF_MASK | LMEM_PCCCR_ENCACHE_MASK);

    /* Enable System Bus Cache */
    /* set command to invalidate all ways, and write GO bit to initiate command */
    LMEM->PSCCR |= LMEM_PSCCR_INVW1_MASK | LMEM_PSCCR_INVW0_MASK;
    LMEM->PSCCR |= LMEM_PSCCR_GO_MASK;
    /* Wait until the command completes */
    while ((LMEM->PSCCR & LMEM_PSCCR_GO_MASK) != 0U)
    {
    }
    /* Enable cache, enable write buffer */
    LMEM->PSCCR |= (LMEM_PSCCR_ENWRBUF_MASK | LMEM_PSCCR_ENCACHE_MASK);

    __ISB();
    __DSB();

    SystemInitHook();
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate(void)
{
    volatile uint32_t *M4_ClockRoot = (volatile uint32_t *)(&(CCM)->ROOT[1].TARGET_ROOT);
    uint32_t pre  = ((*M4_ClockRoot & CCM_TARGET_ROOT_PRE_PODF_MASK) >> CCM_TARGET_ROOT_PRE_PODF_SHIFT) + 1U;
    uint32_t post = ((*M4_ClockRoot & CCM_TARGET_ROOT_POST_PODF_MASK) >> CCM_TARGET_ROOT_POST_PODF_SHIFT) + 1U;

    uint32_t freq = 0U;

    switch ((*M4_ClockRoot & CCM_TARGET_ROOT_MUX_MASK) >> CCM_TARGET_ROOT_MUX_SHIFT)
    {
        case 0U: /* OSC 24M Clock */
            freq = CPU_XTAL_SOSC_CLK_24MHZ;
            break;
        case 1U:                                                             /* System PLL2 DIV5 */
            freq = GetIntegerPllFreq(&(CCM_ANALOG->SYS_PLL2_GEN_CTRL)) / 5U; /* Get System PLL2 DIV5 freq */
            break;
        case 2U:                                                             /* System PLL2 DIV4 */
            freq = GetIntegerPllFreq(&(CCM_ANALOG->SYS_PLL2_GEN_CTRL)) / 4U; /* Get System PLL2 DIV4 freq */
            break;
        case 3U:                                                             /* System PLL1 DIV3 */
            freq = GetIntegerPllFreq(&(CCM_ANALOG->SYS_PLL1_GEN_CTRL)) / 3U; /* Get System PLL1 DIV3 freq */
            break;
        case 4U:                                                        /* System PLL1 */
            freq = GetIntegerPllFreq(&(CCM_ANALOG->SYS_PLL1_GEN_CTRL)); /* Get System PLL1 freq */
            break;
        case 5U:                                                       /* AUDIO PLL1 */
            freq = GetFracPllFreq(&(CCM_ANALOG->AUDIO_PLL1_GEN_CTRL)); /* Get AUDIO PLL1 freq */
            break;
        case 6U:                                                       /* VIDEO PLL1 */
            freq = GetFracPllFreq(&(CCM_ANALOG->VIDEO_PLL1_GEN_CTRL)); /* Get VIDEO PLL1 freq */
            break;
        case 7U:                                                        /* System PLL3 */
            freq = GetIntegerPllFreq(&(CCM_ANALOG->SYS_PLL3_GEN_CTRL)); /* Get System PLL3 freq */
            break;
        default:
            freq = CPU_XTAL_SOSC_CLK_24MHZ;
            break;
    }

    SystemCoreClock = freq / pre / post;
}

/* ----------------------------------------------------------------------------
   -- SystemInitHook()
   ---------------------------------------------------------------------------- */

__attribute__((weak)) void SystemInitHook(void)
{
    /* Void implementation of the weak function. */
}
