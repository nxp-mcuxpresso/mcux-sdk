/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "clock_config.h"
#include "board.h"
#include "fsl_upower.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*
 * SYSOSC clock setting.
 * SYSOSC clock         : 24MHz
 */
const cgc_sosc_config_t g_cgcSysOscConfig = {.freq        = BOARD_XTAL0_CLK_HZ,
                                             .enableMode  = 0, /* Disabled in Deep Sleep/Power down */
                                             .monitorMode = kCGC_SysOscMonitorDisable,
                                             .workMode    = kCGC_SysOscModeOscLowPower};

/*
 * FRO clock setting.
 * FRO clock            : 192MHz
 */
const cgc_fro_config_t g_cgcFroConfig = {.enableMode = kCGC_FroEnableInDeepSleep};

/*
 * PLL0 clock setting.
 * PLL0 clock VCO       : 24 * 20 = 480MHz
 * PLL0 VCODIV output   : 0MHz
 * PLL0 PFD1DIV output  : 0MHz
 * PLL0 PFD2DIV output  : 0MHz
 */
const cgc_pll0_config_t g_cgcPll0Config = {.enableMode = kCGC_PllEnable,
                                           .div1 = 0U,
                                           .pfd1Div = 0U,
                                           .pfd2Div = 0U,
                                           .src = kCGC_PllSrcSysOsc,
                                           .mult = kCGC_Pll0Mult20
                                          }; /* x20 */

/*
 * PLL1 clock setting.
 * PLL1 clock VCO       : 24 * 22.528 = 540.672MHz
 * PLL1 VCODIV output   : 0MHz
 * PLL1 PFD1DIV output  : 0MHz
 * PLL1 PFD2DIV output  : 540.672 / 44 = 12.288MHz
 */
const cgc_pll1_config_t g_cgcPll1Config = {.enableMode = kCGC_PllEnable,
                                           .div1 = 0U,
                                           .pfd1Div = 0U,
                                           .pfd2Div = 44U,
                                           .src = kCGC_PllSrcSysOsc,
                                           .mult = kCGC_Pll1Mult22,
                                           .num = 528000U,
                                           .denom = 1000000U};

/*
 * Select FRO as system clock source, before configuring other clock sources.
 * Clock source   : FRO
 * Core clock     : 192MHz
 * Bus clock      : 96MHz
 * Slow clock     : 24MHz
 */
const cgc_rtd_sys_clk_config_t g_sysClkConfigFroSource = {
    .divCore = 0, /* Core clock divider. */
    .divBus  = 1, /* Bus clock divider. */
    .divSlow = 3, /* Slow clock divider. */
    .src     = kCGC_RtdSysClkSrcFro, /* System clock source. */
    .locked  = 0, /* Register not locked. */
};

/*
 * System clock source and divider in Normal RUN mode.
 *
 * Clock source   : PLL0 main clock 480MHz.
 * Core clock     : 160MHz
 * Bus clock      : 80MHz
 * Slow clock     : 20MHz
 */
const cgc_rtd_sys_clk_config_t g_sysClkConfigRun = {
    .divCore = 2,   /* Core clock divider. */
    .divBus  = 1,   /* Bus clock divider. */
    .divSlow = 7,   /* Slow clock divider. */
    .src     = kCGC_RtdSysClkSrcPll0, /* PLL0 main clock source. */
    .locked  = 0, /* Register not locked. */
};

/*******************************************************************************
 * Code
 ******************************************************************************/
static void BOARD_InitClock(void)
{
    CLOCK_InitFro(&g_cgcFroConfig);

    if (!CLOCK_IsSysOscValid())
    {
        CLOCK_InitSysOsc(&g_cgcSysOscConfig);
    }

    CLOCK_SetXtal0Freq(BOARD_XTAL0_CLK_HZ);

    /* Then set SOSC, FRO DIV needed by application */
    CLOCK_SetRtdSysOscAsyncClkDiv(kCGC_AsyncDiv1Clk, 1);
    CLOCK_SetRtdSysOscAsyncClkDiv(kCGC_AsyncDiv2Clk, 1);
    CLOCK_SetRtdSysOscAsyncClkDiv(kCGC_AsyncDiv3Clk, 0);

    CLOCK_SetRtdFroAsyncClkDiv(kCGC_AsyncDiv1Clk, 1);
    CLOCK_SetRtdFroAsyncClkDiv(kCGC_AsyncDiv2Clk, 1);
    CLOCK_SetRtdFroAsyncClkDiv(kCGC_AsyncDiv3Clk, 0);

    /* RTC OSC clock is enabled by default, initalize g_xtal32Freq */
    CLOCK_SetXtal32Freq(CLK_RTC_32K_CLK);
}

/*
 * Clock in RUN mode:
 * SYSOSC  : Enable
 * FRO    : Enable
 * FIRC    : Enable
 * PLL0  : Enable
 * AUXPLL  : Enable
 */
void BOARD_BootClockRUN(void)
{
    UPOWER_Init(NULL);
    BOARD_InitClock();

    /* Call function BOARD_FlexspiClockSafeConfig() to move FlexSPI clock to a stable clock source to avoid
       instruction/data fetch issue when updating PLL and Main clock if XIP(execute code on FLEXSPI memory). */
    BOARD_FlexspiClockSafeConfig();

    CLOCK_SetCm33SysClkConfig(&g_sysClkConfigFroSource);

    /* Set voltage for RTD sysclk from FRO(192MHz) to PLL(240MHz) */
    UPOWER_SetVoltageForFreq(RTD_DOMAIN, CLOCK_GetFroFreq() / 1000U, 240000U);

    /* Initialize PLL0 480MHz */
    CLOCK_InitPll0(&g_cgcPll0Config);

    /* Enable Pll0 Pfd1 576MHz */
    CLOCK_EnablePll0PfdClkout(kCGC_PllPfd1Clk, 15U);
    /* Enable Pll0 Pfd2 480MHz */
    CLOCK_EnablePll0PfdClkout(kCGC_PllPfd2Clk, 18U);
    /* Enable Pll0 Pfd3 392MHz */
    CLOCK_EnablePll0PfdClkout(kCGC_PllPfd3Clk, 22U);

    /* Initialize PLL1 */
    CLOCK_InitPll1(&g_cgcPll1Config);
    /* Enable Pll1 Pfd2 540.672MHz */
    CLOCK_EnablePll1PfdClkout(kCGC_PllPfd2Clk, 18U);

    CLOCK_SetCm33SysClkConfig(&g_sysClkConfigRun);

    /* Call function BOARD_SetFlexspiClock() to set user configured clock source/divider for FlexSPI. */
    BOARD_SetFlexspiClock(FLEXSPI0, 5U, 1U, 0U); /* CM33_PLATCLK / 2 = 120MHz */

    SystemCoreClockUpdate();
}
