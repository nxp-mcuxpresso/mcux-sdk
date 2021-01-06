/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "clock_config.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* OSC 27M configuration */
const osc_config_t g_osc27MConfig = {
    .oscMode = kOSC_OscMode, .oscDiv = 1U,
};

/* OSC 25M configuration */
const osc_config_t g_osc25MConfig = {
    .oscMode = kOSC_OscMode, .oscDiv = 1U,
};

/* AUDIO PLL1 configuration */
const ccm_analog_frac_pll_config_t g_audioPll1Config = {
    .refSel = kANALOG_PllRefOsc25M, /*!< PLL reference OSC25M */
    .refDiv = 5U,                   /*!< PLL input = 25 / 5 = 5M */
    .fractionDiv = 0U,
    .intDiv = 64U, /*!< Integer and fractional Divider output  = 5 * (1 + 64) * 8 = 2600MHZ */
    .outDiv = 4U,  /*!< Pll out frequency  = 2600 / 4 = 650MHZ */
};

/* AUDIO PLL2 configuration */
const ccm_analog_frac_pll_config_t g_audioPll2Config = {
    .refSel = kANALOG_PllRefOsc25M, /*!< PLL reference OSC25M */
    .refDiv = 5U,                   /*!< PLL input = 25 / 5 = 5M */
    .fractionDiv = 0U,
    .intDiv = 64U, /*!< Integer and fractional Divider output  = 5 * (1 + 64) * 8 = 2600MHZ */
    .outDiv = 4U,  /*!< Pll out frequency  = 2600 / 4 = 650MHZ */
};

/* VIDEO PLL1 configuration */
const ccm_analog_frac_pll_config_t g_videoPll1Config = {
    .refSel = kANALOG_PllRefOsc25M, /*!< PLL reference OSC25M */
    .refDiv = 5U,                   /*!< PLL input = 25 / 5 = 5M */
    .fractionDiv = 0U,
    .intDiv = 64U, /*!< Integer and fractional Divider output  = 5 * (1 + 64) * 8 = 2600MHZ */
    .outDiv = 4U,  /*!< Pll out frequency  = 2600 / 4 = 650MHZ */
};

/* SYSTEM PLL1 configuration */
const ccm_analog_sscg_pll_config_t g_sysPll1Config = {
    .refSel = kANALOG_PllRefOsc25M, /*!< PLL reference OSC25M */
    .refDiv1 = 1U,                  /*!< PLL1 input = 25 / 1 = 25MHZ */
    .loopDivider1 = 32U,            /*!< PLL1 output  = 25 * 32 * 2 = 1600MHZ */
    .refDiv2 = 24U,                 /*!< PLL2 input  = 1600 / 24 = 66.66MHZ */
    .loopDivider2 = 12U,            /*!< PLL2 output  = 12 * 66.66 * 2 = 1600MHZ */
    .outDiv = 1U,                   /*!< PLL output = 1600 / 2 / 1 = 800MHZ */
};

/* SYSTEM PLL2 configuration */
const ccm_analog_sscg_pll_config_t g_sysPll2Config = {
    .refSel = kANALOG_PllRefOsc25M, /*!< PLL reference OSC25M */
    .refDiv1 = 1U,                  /*!< PLL1 input = 25 / 1 = 25MHZ */
    .loopDivider1 = 32U,            /*!< PLL1 output  = 25 * 32 * 2 = 1600MHZ */
    .refDiv2 = 16U,                 /*!< PLL2 input  = 1600 / 16 = 100MHZ */
    .loopDivider2 = 10U,            /*!< PLL2 output  = 10 * 100 * 2 = 2000MHZ */
    .outDiv = 1U,                   /*!< PLL output = 2000 / 2 / 1 = 1000MHZ */
};

/* SYSTEM PLL3 configuration */
const ccm_analog_sscg_pll_config_t g_sysPll3Config = {
    .refSel = kANALOG_PllRefOsc25M, /*!< PLL reference OSC25M */
    .refDiv1 = 1U,                  /*!< PLL1 input = 25 / 1 = 25MHZ */
    .loopDivider1 = 32U,            /*!< PLL1 output  = 25 * 32 * 2 = 1600MHZ */
    .refDiv2 = 16U,                 /*!< PLL2 input  = 1600 / 16 = 100MHZ */
    .loopDivider2 = 10U,            /*!< PLL2 output  = 10 * 100 * 2 = 2000MHZ */
    .outDiv = 1U,                   /*!< PLL output = 2000 / 2 / 1 = 1000MHZ */
};

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
void BOARD_BootClockRUN(void)
{
    /* OSC configuration */
    CLOCK_InitOSC25M(&g_osc25MConfig);
    CLOCK_InitOSC27M(&g_osc27MConfig);

    /* The following steps just show how to configure the PLL clock sources using the clock driver on M4 core side .
     * Please note that the ROM has already configured the SYSTEM PLL1 to 800Mhz when power up the SOC, meanwhile A core
     * would also do configuration on the SYSTEM PLL1 to 800Mhz and SYSTEM PLL2 to 1000Mhz by U-Boot.*/

    /* switch AHB NOC root to 25M first in order to configure the SYSTEM PLL1. */
    CLOCK_SetRootMux(kCLOCK_RootAhb, kCLOCK_AhbRootmuxOsc25m);
    CLOCK_SetRootMux(kCLOCK_RootNoc, kCLOCK_NocRootmuxOsc25m);
    /* switch AXI M4 root to 25M first in order to configure the SYSTEM PLL2. */
    CLOCK_SetRootMux(kCLOCK_RootAxi, kCLOCK_AxiRootmuxOsc25m);
    CLOCK_SetRootMux(kCLOCK_RootM4, kCLOCK_M4RootmuxOsc25m);

    CLOCK_InitSysPll1(&g_sysPll1Config); /* init SYSTEM PLL1 run at 800MHZ */
    CLOCK_InitSysPll2(&g_sysPll2Config); /* init SYSTEM PLL2 run at 1000MHZ */
    CLOCK_InitSysPll3(&g_sysPll3Config); /* init SYSTEM PLL3 run at 1000MHZ */

    CLOCK_InitAudioPll1(&g_audioPll1Config); /* init AUDIO PLL1 run at 650MHZ */
    CLOCK_InitAudioPll2(&g_audioPll2Config); /* init AUDIO PLL2 run at 650MHZ */
    CLOCK_InitVideoPll1(&g_videoPll1Config); /* init VIDEO PLL1 run at 650MHZ */

    CLOCK_SetRootMux(kCLOCK_RootM4, kCLOCK_M4RootmuxSysPll1Div3); /* switch cortex-m4 to SYSTEM PLL1 DIV3 */
    CLOCK_SetRootMux(kCLOCK_RootNoc, kCLOCK_NocRootmuxSysPll1);   /* change back to SYSTEM PLL1*/

    CLOCK_SetRootDivider(kCLOCK_RootAhb, 1U, 1U);
    CLOCK_SetRootMux(kCLOCK_RootAhb, kCLOCK_AhbRootmuxSysPll1Div6); /* switch AHB to SYSTEM PLL1 DIV6 = 133MHZ */

    CLOCK_SetRootDivider(kCLOCK_RootAxi, 3U, 1U);
    CLOCK_SetRootMux(kCLOCK_RootAxi, kCLOCK_AxiRootmuxSysPll1); /* switch AXI to SYSTEM PLL1 = 266MHZ */

    CLOCK_SetRootMux(kCLOCK_RootUart2, kCLOCK_UartRootmuxSysPll1Div10); /* Set UART source to SysPLL1 Div10 80MHZ */
    CLOCK_SetRootDivider(kCLOCK_RootUart2, 1U, 1U);                     /* Set root clock to 80MHZ/ 1= 80MHZ */

    CLOCK_EnableClock(kCLOCK_Rdc); /* Enable RDC clock */

    /* The purpose to enable the following modules clock is to make sure the M4 core could work normally when A53 core
     * enters the low power status.*/
    // CLOCK_EnableClock(kCLOCK_Sim_m);
    // CLOCK_EnableClock(kCLOCK_Sim_main);
    // CLOCK_EnableClock(kCLOCK_Sim_s);
    // CLOCK_EnableClock(kCLOCK_Sim_wakeup);
    // CLOCK_EnableClock(kCLOCK_Debug);
    // CLOCK_EnableClock(kCLOCK_Dram);
    // CLOCK_EnableClock(kCLOCK_Sec_Debug);

    /* Disable unused PLL */
    CLOCK_DeinitSysPll3();
    CLOCK_DeinitVideoPll1();
    CLOCK_DeinitAudioPll1();
    CLOCK_DeinitAudioPll2();
    /* Update core clock */
    SystemCoreClockUpdate();
}
