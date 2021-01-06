/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_msmc.h"
#include "clock_config.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*
 * SYSOSC clock ROM setting.
 * SYSOSC clock         : 24MHz
 * SOSCDIV1_CLK output  : 0MHz (async platform clock)
 * SOSCDIV2_CLK output  : 0MHz (async bus clock)
 * SOSCDIV3_CLK output  : 0MHz (async slow clock)
 */
const scg_sosc_config_t g_scgSysOscConfig = {.freq        = BOARD_XTAL0_CLK_HZ,
                                             .enableMode  = kSCG_SysOscEnable,
                                             .monitorMode = kSCG_SysOscMonitorDisable,
                                             .div1        = kSCG_AsyncClkDisable,
                                             .div2        = kSCG_AsyncClkDisable,
                                             .div3        = kSCG_AsyncClkDisable,
                                             .workMode    = kSCG_SysOscModeOscLowPower};

/*
 * SIRC clock ROM setting.
 * SIRC clock           : 16MHz
 * SIRCDIV1_CLK output  : 0MHz  (async platform clock)
 * SIRCDIV2_CLK output  : 0MHz  (async bus clock)
 * SIRCDIV3_CLK output  : 0MHz  (async slow clock)
 */
const scg_sirc_config_t g_scgSircConfig = {.enableMode = kSCG_SircEnable | kSCG_SircEnableInLowPower,
                                           .div1       = kSCG_AsyncClkDisable,
                                           .div2       = kSCG_AsyncClkDisable,
                                           .div3       = kSCG_AsyncClkDisable,
                                           .range      = kSCG_SircRangeHigh};

/*
 * FIRC clock ROM setting.
 * FIRC clock           : 48MHz
 * FIRCDIV1_CLK output  : 0MHz (async platform clock)
 * FIRCDIV2_CLK output  : 0MHz (async bus clock)
 * FIRCDIV3_CLK output  : 0MHz (async slow clock)
 */
const scg_firc_config_t g_scgFircConfig = {.enableMode = kSCG_FircEnable,
                                           .div1       = kSCG_AsyncClkDisable,
                                           .div2       = kSCG_AsyncClkDisable,
                                           .div3       = kSCG_AsyncClkDisable,
                                           .range      = kSCG_FircRange48M,
                                           .trimConfig = NULL};

/*
 * SYSPLL clock setting.
 * SYSPLL clock PFD0      : 480 * 18 / 15 = 576MHz
 * SYSPLLDIV1_CLK output  : 0MHz (async platform clock)
 * SYSPLLDIV2_CLK output  : 0MHz (async bus clock)
 * SYSPLLDIV3_CLK output  : 0MHz (async slow clock)
 * PLL main clock as sync system clock
 */
const scg_spll_config_t g_scgSysPllConfig = {.enableMode    = kSCG_SysPllEnable,
                                             .div1          = kSCG_AsyncClkDisable,
                                             .div2          = kSCG_AsyncClkDisable,
                                             .div3          = kSCG_AsyncClkDisable,
                                             .src           = kSCG_SysPllSrcSysOsc,
                                             .isPfdSelected = true,
                                             .prediv        = 0U,
                                             .pfdClkout     = kSCG_SysPllPfd0Clk,
                                             .mult          = 3U}; /* x20 */

/*
 * AUXPLL clock setting.
 * AUXPLL clock           : 540.672MHz / 44 = 12.288MHz
 * AUXPLLDIV1_CLK output  : 12.288MHz (async platform clock)
 * AUXPLLDIV2_CLK output  : 12.288MHz (async bus clock)
 * AUXPLLDIV3_CLK output  : 0MHz     (async slow clock)
 */
const scg_apll_config_t g_scgAuxPllConfig = {.enableMode    = kSCG_AuxPllEnable,
                                             .div1          = kSCG_AsyncClkDivBy1,
                                             .div2          = kSCG_AsyncClkDivBy1,
                                             .div3          = kSCG_AsyncClkDisable,
                                             .src           = kSCG_AuxPllSrcSysOsc,
                                             .isPfdSelected = false,
                                             .prediv        = 0U,
                                             .pfdClkout     = kSCG_AuxPllPfd0Clk,
                                             .mult          = 22U,
                                             .pllPostdiv1   = kSCG_SysClkDivBy11,
                                             .pllPostdiv2   = kSCG_SysClkDivBy4,
                                             .num           = 528000U,
                                             .denom         = 1000000U}; /* 24 x 22.528 = 540.672MHz */

/*
 * Select SIRC as system clock source, before configuring other clock sources.
 * Clock source   : SIRC
 * Core clock     : 16MHz
 * Platform clock : 16MHz
 * Bus clock      : 16MHz
 * Slow clock     : 8MHz
 */
const scg_sys_clk_config_t g_sysClkConfigSircSource = {
    .divCore = kSCG_SysClkDivBy1, /* Core clock divider. */
    .divPlat = kSCG_SysClkDivBy1, /* Platform clock divider. */
    .divBus  = kSCG_SysClkDivBy1, /* Bus clock divider. */
    .divSlow = kSCG_SysClkDivBy2, /* Slow clock divider. */
    .src     = kSCG_SysClkSrcSirc /* System clock source. */
};

/*
 * System clock source and divider in Normal RUN mode.
 *
 * Clock source   : SYSPLL main clock 576MHz
 * Core clock     : 115.2MHz
 * Platform clock : 115.2MHz
 * Bus clock      : 57.6MHz
 * Slow clock     : 19.2MHz
 */
const scg_sys_clk_config_t g_sysClkConfigNormalRun = {
    .divCore = kSCG_SysClkDivBy5,   /* Core clock divider. */
    .divPlat = kSCG_SysClkDivBy1,   /* Platform clock divider. */
    .divBus  = kSCG_SysClkDivBy2,   /* Bus clock divider. */
    .divSlow = kSCG_SysClkDivBy6,   /* Slow clock divider. */
    .src     = kSCG_SysClkSrcSysPll /* System clock source. */
};

/*
 * System clock source and divider for RUN mode, it is used to prepare for switch to HSRUN mode，to make sure HSRUN
 * switch frequency range
 * is not bigger than x2.
 * Clock source   : SYSPLL main clock 576MHz
 * Core clock     : 96MHz
 * Platform clock : 192MHz
 * Bus clock      : 48MHz
 * Slow clock     : 24MHz
 */
const scg_sys_clk_config_t g_sysClkConfigRunToHsrun = {
    .divCore = kSCG_SysClkDivBy6,   /* Core clock divider. */
    .divPlat = kSCG_SysClkDivBy1,   /* Platform clock divider. */
    .divBus  = kSCG_SysClkDivBy4,   /* Bus clock divider. */
    .divSlow = kSCG_SysClkDivBy8,   /* Slow clock divider. */
    .src     = kSCG_SysClkSrcSysPll /* System clock source. */
};

/*
 * System clock source and divider in HSRUN mode.
 * Clock source   : SYSPLL main clock 576MHz
 * Core clock     : 192MHz
 * Platform clock : 192MHz
 * Bus clock      : 96MHz
 * Slow clock     : 24MHz
 */
const scg_sys_clk_config_t g_sysClkConfigHsrun = {
    .divCore = kSCG_SysClkDivBy3,   /* Core clock divider. */
    .divPlat = kSCG_SysClkDivBy1,   /* Platform clock divider. */
    .divBus  = kSCG_SysClkDivBy2,   /* Bus clock divider. */
    .divSlow = kSCG_SysClkDivBy8,   /* Slow clock divider. */
    .src     = kSCG_SysClkSrcSysPll /* System clock source. */
};

/*
 * System clock source and divider in VLPR mode.
 * Clock source   : SIRC
 * Core clock     : 16MHz
 * Platform clock : 16MHz
 * Bus clock      : 16MHz
 * Slow clock     : 8MHz
 */
const scg_sys_clk_config_t g_sysClkConfigVlpr = {
    .divCore = kSCG_SysClkDivBy1, /* Core clock divider. */
    .divPlat = kSCG_SysClkDivBy1, /* Platform clock divider. */
    .divBus  = kSCG_SysClkDivBy1, /* Bus clock divider. */
    .divSlow = kSCG_SysClkDivBy2, /* Slow clock divider. */
    .src     = kSCG_SysClkSrcSirc /* System clock source. */
};

/*******************************************************************************
 * Code
 ******************************************************************************/
AT_QUICKACCESS_SECTION_CODE(void BOARD_SetRunMode(
    SCG_Type *scg, uint32_t scgRunConfig, QuadSPI_Type *qspi, clock_ip_name_t qspiClock, uint32_t qspiClockConfig))
{
    int32_t i;

    if (qspi)
    {
        volatile uint32_t *pcc = (volatile uint32_t *)qspiClock;

        /* Wait until QSPI is not busy */
        while (qspi->SR & QuadSPI_SR_BUSY_MASK)
        {
        }

        /* Disable module */
        qspi->MCR |= QuadSPI_MCR_MDIS_MASK;

        *pcc = 0; /* Disable clock before changing clock source */

        /* Update system clock. */
        scg->RCCR = scgRunConfig;

        /* Wait for clock source switch finished. */
        while ((scg->CSR & SCG_CSR_SCS_MASK) != (scgRunConfig & SCG_CSR_SCS_MASK))
        {
        }

        /* Configure QSPI clock again. */
        *pcc = qspiClockConfig;
        /* Re-enable QSPI module */
        qspi->MCR &= ~QuadSPI_MCR_MDIS_MASK;
        /* Reset QSPI module */
        qspi->MCR |= QuadSPI_MCR_SWRSTHD_MASK | QuadSPI_MCR_SWRSTSD_MASK;
        /* Wait enough cycles until the ahb domain and serial flash domain are reset */
        for (i = 0; i < 200; i++)
        {
            qspi->SR;
        }
        /* Clear the reset bits. */
        qspi->MCR &= ~(QuadSPI_MCR_SWRSTHD_MASK | QuadSPI_MCR_SWRSTSD_MASK);
    }
    else
    {
        scg->RCCR = scgRunConfig;

        /* Wait for clock source switch finished. */
        while ((scg->CSR & SCG_CSR_SCS_MASK) != (scgRunConfig & SCG_CSR_SCS_MASK))
        {
        }
    }
}

bool BOARD_IsRunOnQSPI(void)
{
    if (((uint32_t)BOARD_BootClockRUN >= 0x04000000U) && ((uint32_t)BOARD_BootClockRUN < 0x0C000000U))
    {
        return true;
    }
    return false;
}

static void BOARD_InitClock(void)
{
    /* First initialize same clock settings as ROM does. It's necessary for debugging
       in case ROM doesn't initialize well. */
    if (!CLOCK_IsSircValid())
    {
        CLOCK_InitSirc(&g_scgSircConfig);
    }

    if (!CLOCK_IsFircValid())
    {
        CLOCK_InitFirc(&g_scgFircConfig);
    }

    if (!CLOCK_IsSysOscValid())
    {
        CLOCK_InitSysOsc(&g_scgSysOscConfig);
    }

    CLOCK_SetXtal0Freq(BOARD_XTAL0_CLK_HZ);

    /* SOSC, FIRC and SIRC needed by Cortex-A core when M4 runs into VLPR or STOP */
    SCG0->SOSCCSR |= SCG_SOSCCSR_SOSCLPEN_MASK | SCG_SOSCCSR_SOSCSTEN_MASK;
    SCG0->FIRCCSR |= SCG_FIRCCSR_FIRCLPEN_MASK | SCG_FIRCCSR_FIRCSTEN_MASK;
    SCG0->SIRCCSR |= SCG_SIRCCSR_SIRCLPEN_MASK | SCG_SIRCCSR_SIRCSTEN_MASK;

    /* Then set SOSC, FIRC and SIRC DIV needed by application */
    CLOCK_SetSysOscAsyncClkDiv(kSCG_AsyncDiv1Clk, kSCG_AsyncClkDivBy1);
    CLOCK_SetSysOscAsyncClkDiv(kSCG_AsyncDiv2Clk, kSCG_AsyncClkDivBy1);

    CLOCK_SetFircAsyncClkDiv(kSCG_AsyncDiv1Clk, kSCG_AsyncClkDivBy1);
    CLOCK_SetFircAsyncClkDiv(kSCG_AsyncDiv2Clk, kSCG_AsyncClkDivBy1);

    CLOCK_SetSircAsyncClkDiv(kSCG_AsyncDiv1Clk, kSCG_AsyncClkDivBy1);
    CLOCK_SetSircAsyncClkDiv(kSCG_AsyncDiv2Clk, kSCG_AsyncClkDivBy1);
}

/*
 * Clock in VLPR mode:
 * SYSOSC  : Enable (shared by CA7)
 * SIRC    : Enable (shared by CA7)
 * FIRC    : Enable (shared by CA7)
 * SYSPLL  : Disable
 * AUXPLL  : Disable
 */
void BOARD_BootClockVLPR(void)
{
    uint32_t *config = (uint32_t *)(&g_sysClkConfigVlpr);
    scg_sys_clk_config_t curConfig;
    QuadSPI_Type *qspi = BOARD_IsRunOnQSPI() ? QuadSPI0 : NULL;

    BOARD_InitClock();

    /* Change to use SIRC as RUN system clock source */
    /* BOARD_SetRunMode is running in TCM to avoid clock change issue on QSPI memory */
    BOARD_SetRunMode(SCG0, *config, qspi, kCLOCK_Qspi,
                     PCC1_PCC_QSPI_OTFAD_CGC_MASK | PCC1_PCC_QSPI_OTFAD_PCS(2)); /* QSPI source: 16M SIRC Async */

    /* Change to use SIRC as VLPR system clock source */
    CLOCK_SetVlprModeSysClkConfig(&g_sysClkConfigVlpr);

    /* Switch running mode to VLPR */
    SMC_SetPowerModeProtection(MSMC0, kSMC_AllowPowerModeAll);
    SMC_SetPowerModeVlpr(MSMC0);
    while (SMC_GetPowerModeState(MSMC0) != kSMC_PowerStateVlpr)
    {
    }

    /* Wait for clock source switch finished. */
    do
    {
        CLOCK_GetCurSysClkConfig(&curConfig);
    } while (curConfig.src != g_sysClkConfigVlpr.src);

    CLOCK_DeinitSysPll();
    CLOCK_DeinitAuxPll();

    SystemCoreClockUpdate();
}

/*
 * Clock in RUN mode:
 * SYSOSC  : Enable
 * SIRC    : Enable
 * FIRC    : Enable
 * SYSPLL  : Enable
 * AUXPLL  : Enable
 */
void BOARD_BootClockRUN(void)
{
    uint32_t *config   = (uint32_t *)(&g_sysClkConfigVlpr);
    QuadSPI_Type *qspi = BOARD_IsRunOnQSPI() ? QuadSPI0 : NULL;

    BOARD_InitClock();

    /* Change to use SIRC as system clock source to prepare to initialize other clock sources */
    /* BOARD_SetRunMode is running in TCM to avoid clock change issue on QSPI memory */
    BOARD_SetRunMode(SCG0, *config, qspi, kCLOCK_Qspi,
                     PCC1_PCC_QSPI_OTFAD_CGC_MASK | PCC1_PCC_QSPI_OTFAD_PCS(2)); /* QSPI source: 16M SIRC Async */

    /* Initialize SysPll 480MHz */
    CLOCK_InitSysPll(&g_scgSysPllConfig);

    /* Enable SysPll Pfd0 576MHz */
    CLOCK_EnableSysPllPfdClkout(kSCG_SysPllPfd0Clk, 15U);
    /* Enable SysPll Pfd3 480MHz (same as SysPll main clock) */
    CLOCK_EnableSysPllPfdClkout(kSCG_SysPllPfd3Clk, 18U);

    /* Initialize AuxPll */
    CLOCK_InitAuxPll(&g_scgAuxPllConfig);
    /* Enable AuxPll Pfd0 540.672MHz (same as AuxPll before postdiv) */
    CLOCK_EnableAuxPllPfdClkout(kSCG_AuxPllPfd0Clk, 18U);

    config = (uint32_t *)(&g_sysClkConfigNormalRun);
    BOARD_SetRunMode(SCG0, *config, qspi, kCLOCK_Qspi,
                     PCC1_PCC_QSPI_OTFAD_CGC_MASK | PCC1_PCC_QSPI_OTFAD_PCS(3)); /* QSPI source: 48M FIRC Async */

    SystemCoreClockUpdate();
}

/*
 * Clock in HSRUN mode:
 * SYSOSC  : Enable
 * SIRC    : Enable
 * FIRC    : Enable
 * SYSPLL  : Enable
 * AUXPLL  : Enable
 * NOTE: MAKE SURE PMC0 HSRUN VOLTAGE IS PROPERLY SET BEFORE CALLING THIS FUNCTION.
 */
void BOARD_BootClockHSRUN(void)
{
    /* In HSRUN mode, the maximum allowable change in frequency of the system/bus/core/flash is
     * restricted to x2, to follow this restriction, enter HSRUN mode should follow:
     * 1.set the run mode to a safe configurations.
     * 2.set the PLL or FLL output target frequency for HSRUN mode.
     * 3.switch RUN mode configuration.
     * 4.switch to HSRUN mode.
     * 5.switch to HSRUN mode target requency value.
     */

    scg_sys_clk_config_t curConfig;

    uint32_t *config   = (uint32_t *)(&g_sysClkConfigVlpr);
    QuadSPI_Type *qspi = BOARD_IsRunOnQSPI() ? QuadSPI0 : NULL;

    BOARD_InitClock();

    /* Change to use SIRC as system clock source to prepare to initialize other clock sources */
    /* BOARD_SetRunMode is running in TCM to avoid clock change issue on QSPI memory */
    BOARD_SetRunMode(SCG0, *config, qspi, kCLOCK_Qspi,
                     PCC1_PCC_QSPI_OTFAD_CGC_MASK | PCC1_PCC_QSPI_OTFAD_PCS(2)); /* QSPI source: 16M SIRC Async */

    /* Initialize SysPll 480MHz */
    CLOCK_InitSysPll(&g_scgSysPllConfig);

    /* Enable SysPll Pfd0 576MHz */
    CLOCK_EnableSysPllPfdClkout(kSCG_SysPllPfd0Clk, 15U);
    /* Enable SysPll Pfd3 480MHz (same as SysPll main clock) */
    CLOCK_EnableSysPllPfdClkout(kSCG_SysPllPfd3Clk, 18U);

    /* Initialize AuxPll */
    CLOCK_InitAuxPll(&g_scgAuxPllConfig);
    /* Enable AuxPll Pfd0 540.672MHz (same as AuxPll before postdiv) */
    CLOCK_EnableAuxPllPfdClkout(kSCG_AuxPllPfd0Clk, 18U);

    config = (uint32_t *)(&g_sysClkConfigRunToHsrun);

    BOARD_SetRunMode(SCG0, *config, qspi, kCLOCK_Qspi,
                     PCC1_PCC_QSPI_OTFAD_CGC_MASK | PCC1_PCC_QSPI_OTFAD_PCS(3)); /* QSPI source: 48M FIRC Async */

    /* Switch running mode to HSRUN */
    SMC_SetPowerModeProtection(MSMC0, kSMC_AllowPowerModeAll);
    SMC_SetPowerModeHsrun(MSMC0);
    while (SMC_GetPowerModeState(MSMC0) != kSMC_PowerStateHsrun)
    {
    }

    /* Change to use SysPll as system clock source */
    CLOCK_SetHsrunModeSysClkConfig(&g_sysClkConfigHsrun);
    /* Wait for clock source switch finished. */
    do
    {
        CLOCK_GetCurSysClkConfig(&curConfig);
    } while (curConfig.src != g_sysClkConfigHsrun.src);

    SystemCoreClockUpdate();
}
