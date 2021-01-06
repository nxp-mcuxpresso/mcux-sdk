/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "clock_config.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Fractional PLLs: Fout = ((mainDiv+dsm/65536) * refSel) / (preDiv * 2^ postDiv) */
/* AUDIO PLL1 configuration */
const ccm_analog_frac_pll_config_t g_audioPll1Config = {
    .refSel = kANALOG_PllRefOsc24M, /*!< PLL reference OSC24M */
    .mainDiv = 655U,
    .dsm = 23593U,
    .preDiv = 5U,
    .postDiv = 2U, /*!< AUDIO PLL1 frequency  = 786432000HZ */
};

/* AUDIO PLL2 configuration */
const ccm_analog_frac_pll_config_t g_audioPll2Config = {
    .refSel = kANALOG_PllRefOsc24M, /*!< PLL reference OSC24M */
    .mainDiv = 301U,
    .dsm = 3670U,
    .preDiv = 5U,
    .postDiv = 1U, /*!< AUDIO PLL2 frequency  = 722534399HZ */
};

/* Integer PLLs: Fout = (mainDiv * refSel) / (preDiv * 2^ postDiv) */
/* SYSTEM PLL1 configuration */
const ccm_analog_integer_pll_config_t g_sysPll1Config = {
    .refSel = kANALOG_PllRefOsc24M, /*!< PLL reference OSC24M */
    .mainDiv = 400U,
    .preDiv = 3U,
    .postDiv = 2U, /*!< SYSTEM PLL1 frequency  = 800MHZ */
};

/* SYSTEM PLL2 configuration */
const ccm_analog_integer_pll_config_t g_sysPll2Config = {
    .refSel = kANALOG_PllRefOsc24M, /*!< PLL reference OSC24M */
    .mainDiv = 250U,
    .preDiv = 3U,
    .postDiv = 1U, /*!< SYSTEM PLL2 frequency  = 1000MHZ */
};

/* SYSTEM PLL3 configuration */
const ccm_analog_integer_pll_config_t g_sysPll3Config = {
    .refSel = kANALOG_PllRefOsc24M, /*!< PLL reference OSC24M */
    .mainDiv = 250,
    .preDiv = 2U,
    .postDiv = 2U, /*!< SYSTEM PLL3 frequency  = 750MHZ */
};

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
void BOARD_BootClockRUN(void)
{
    /* * The following steps just show how to configure the PLL clock sources using the clock driver on M4 core side .
     * Please note that the ROM has already configured the SYSTEM PLL1 to 800Mhz when power up the SOC, meanwhile A core
     * would enable the Div output for SYSTEM PLL1 & PLL2 by U-Boot.
     * Therefore, there is no need to configure the system PLL again on M4 side, otherwise it would have a risk to make
     * the SOC hang.
     */

    /* switch AHB NOC root to 24M first in order to configure the SYSTEM PLL1. */
    CLOCK_SetRootMux(kCLOCK_RootAhb, kCLOCK_AhbRootmuxOsc24M);
    //    CLOCK_SetRootMux(kCLOCK_RootNoc, kCLOCK_NocRootmuxOsc24M);
    /* switch AXI M4 root to 24M first in order to configure the SYSTEM PLL2. */
    //    CLOCK_SetRootMux(kCLOCK_RootAxi, kCLOCK_AxiRootmuxOsc24M);
    CLOCK_SetRootMux(kCLOCK_RootM4, kCLOCK_M4RootmuxOsc24M);

    //    CLOCK_InitSysPll1(&g_sysPll1Config); /* init SYSTEM PLL1 run at 800MHZ */
    //    CLOCK_InitSysPll2(&g_sysPll2Config); /* init SYSTEM PLL2 run at 1000MHZ */
    //    CLOCK_InitSysPll3(&g_sysPll3Config); /* init SYSTEM PLL3 run at 750MHZ */

    CLOCK_InitAudioPll1(&g_audioPll1Config); /* init AUDIO PLL1 run at 786432000HZ */
    CLOCK_InitAudioPll2(&g_audioPll2Config); /* init AUDIO PLL2 run at 722534399HZ */

    CLOCK_SetRootDivider(kCLOCK_RootM4, 1U, 2U);
    CLOCK_SetRootMux(kCLOCK_RootM4, kCLOCK_M4RootmuxSysPll1); /* switch cortex-m4 to SYSTEM PLL1 */

    //    CLOCK_SetRootMux(kCLOCK_RootNoc, kCLOCK_NocRootmuxSysPll1); /* change back to SYSTEM PLL1*/

    CLOCK_SetRootDivider(kCLOCK_RootAhb, 1U, 1U);
    CLOCK_SetRootMux(kCLOCK_RootAhb, kCLOCK_AhbRootmuxSysPll1Div6); /* switch AHB to SYSTEM PLL1 DIV6 = 133MHZ */

    CLOCK_SetRootDivider(kCLOCK_RootAudioAhb, 1U, 2U);                    /* Set root clock to 800MHZ/ 2= 400MHZ */
    CLOCK_SetRootMux(kCLOCK_RootAudioAhb, kCLOCK_AudioAhbRootmuxSysPll1); /* switch AUDIO AHB to SYSTEM PLL1 */

    //    CLOCK_SetRootDivider(kCLOCK_RootAxi, 1U, 2);
    //    CLOCK_SetRootMux(kCLOCK_RootAxi, kCLOCK_AxiRootmuxSysPll1); /* switch AXI to SYSTEM PLL1 800MHZ */

    CLOCK_SetRootMux(kCLOCK_RootUart4, kCLOCK_UartRootmuxSysPll1Div10); /* Set UART source to SysPLL1 Div10 80MHZ */
    CLOCK_SetRootDivider(kCLOCK_RootUart4, 1U, 1U);                     /* Set root clock to 80MHZ/ 1= 80MHZ */

    CLOCK_EnableClock(kCLOCK_Rdc); /* Enable RDC clock */
    /* The purpose to enable the following modules clock is to make sure the M4 core could work normally when A53 core
     * enters the low power status.*/
    CLOCK_EnableClock(kCLOCK_Sim_display);
    CLOCK_EnableClock(kCLOCK_Sim_m);
    CLOCK_EnableClock(kCLOCK_Sim_main);
    CLOCK_EnableClock(kCLOCK_Sim_s);
    CLOCK_EnableClock(kCLOCK_Sim_wakeup);
    CLOCK_EnableClock(kCLOCK_Debug);
    CLOCK_EnableClock(kCLOCK_Dram);
    CLOCK_EnableClock(kCLOCK_Sec_Debug);

    /* Update core clock */
    SystemCoreClockUpdate();
}
