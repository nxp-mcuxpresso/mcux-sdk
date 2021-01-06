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
    .refSel  = kANALOG_PllRefOsc24M, /*!< PLL reference OSC24M */
    .mainDiv = 262U,
    .dsm     = 9437U,
    .preDiv  = 2U,
    .postDiv = 3U, /*!< AUDIO PLL1 frequency  = 393215996HZ */
};

/* AUDIO PLL2 configuration */
const ccm_analog_frac_pll_config_t g_audioPll2Config = {
    .refSel  = kANALOG_PllRefOsc24M, /*!< PLL reference OSC24M */
    .mainDiv = 361U,
    .dsm     = 17511U,
    .preDiv  = 3U,
    .postDiv = 3U, /*!< AUDIO PLL2 frequency  = 361267197HZ */
};

/* Integer PLLs: Fout = (mainDiv * refSel) / (preDiv * 2^ postDiv) */
/* SYSTEM PLL1 configuration */
const ccm_analog_integer_pll_config_t g_sysPll1Config = {
    .refSel  = kANALOG_PllRefOsc24M, /*!< PLL reference OSC24M */
    .mainDiv = 400U,
    .preDiv  = 3U,
    .postDiv = 2U, /*!< SYSTEM PLL1 frequency  = 800MHZ */
};

/* SYSTEM PLL2 configuration */
const ccm_analog_integer_pll_config_t g_sysPll2Config = {
    .refSel  = kANALOG_PllRefOsc24M, /*!< PLL reference OSC24M */
    .mainDiv = 250U,
    .preDiv  = 3U,
    .postDiv = 1U, /*!< SYSTEM PLL2 frequency  = 1000MHZ */
};

/* SYSTEM PLL3 configuration */
const ccm_analog_integer_pll_config_t g_sysPll3Config = {
    .refSel  = kANALOG_PllRefOsc24M, /*!< PLL reference OSC24M */
    .mainDiv = 300,
    .preDiv  = 3U,
    .postDiv = 2U, /*!< SYSTEM PLL3 frequency  = 600MHZ */
};

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
void BOARD_BootClockRUN(void)
{
    /* * The following steps just show how to configure the PLL clock sources using the clock driver on M7 core side .
     * Please note that the ROM has already configured the SYSTEM PLL1 to 800Mhz when power up the SOC, meanwhile A core
     * would enable the Div output for SYSTEM PLL1 & PLL2 by U-Boot.
     * Therefore, there is no need to configure the system PLL again on M7 side, otherwise it would have a risk to make
     * the SOC hang.
     */

    /* switch AHB NOC root to 24M first in order to configure the SYSTEM PLL1. */
    CLOCK_SetRootMux(kCLOCK_RootAhb, kCLOCK_AhbRootmuxOsc24M);

    /* switch AXI M7 root to 24M first in order to configure the SYSTEM PLL3. */
    CLOCK_SetRootMux(kCLOCK_RootM7, kCLOCK_M7RootmuxOsc24M);

    /* Init Audio PLL1/Audio PLL2 */
    CLOCK_InitAudioPll1(&g_audioPll1Config); /* init AUDIO PLL1 run at 393215996HZ */
    CLOCK_InitAudioPll2(&g_audioPll2Config); /* init AUDIO PLL2 run at 361267197HZ */

    /* As ROM not enables PLL3 by default, enable PLL3 to 600M if A core not set it. */
    if (CLOCK_IsPllBypassed(CCM_ANALOG, kCLOCK_SysPll3InternalPll1BypassCtrl) == 1)
    {
        CLOCK_InitSysPll3(&g_sysPll3Config);
    }
    CLOCK_SetRootDivider(kCLOCK_RootM7, 1U, 1U);              /* Set M7 root clock freq to 600M / 1 = 600M */
    CLOCK_SetRootMux(kCLOCK_RootM7, kCLOCK_M7RootmuxSysPll3); /* switch cortex-m7 to SYSTEM PLL3 */

    CLOCK_SetRootDivider(kCLOCK_RootAhb, 1U, 1U);                   /* Set root clock freq to 133M / 1= 133MHZ */
    CLOCK_SetRootMux(kCLOCK_RootAhb, kCLOCK_AhbRootmuxSysPll1Div6); /* switch AHB to SYSTEM PLL1 DIV6 */

    CLOCK_SetRootDivider(kCLOCK_RootAudioAhb, 1U, 2U);                    /* Set root clock freq to 800MHZ/ 2= 400MHZ*/
    CLOCK_SetRootMux(kCLOCK_RootAudioAhb, kCLOCK_AudioAhbRootmuxSysPll1); /* switch AUDIO AHB to SYSTEM PLL1 */

    CLOCK_SetRootDivider(kCLOCK_RootUart4, 1U, 1U);                     /* Set root clock freq to 80MHZ/ 1= 80MHZ */
    CLOCK_SetRootMux(kCLOCK_RootUart4, kCLOCK_UartRootmuxSysPll1Div10); /* Set UART source to SysPLL1 Div10 80MHZ */

    CLOCK_EnableClock(kCLOCK_Rdc);   /* Enable RDC clock */
    CLOCK_EnableClock(kCLOCK_Ocram); /* Enable Ocram clock */

    /* The purpose to enable the following modules clock is to make sure the M7 core could work normally when A53 core
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
