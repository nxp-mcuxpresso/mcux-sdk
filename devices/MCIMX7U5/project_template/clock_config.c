/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_msmc.h"
#include "clock_config.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* System clock frequency. */
extern uint32_t SystemCoreClock;

/*******************************************************************************
 ************************ BOARD_InitBootClocks function ************************
 ******************************************************************************/
void BOARD_InitBootClocks(void)
{
    BOARD_BootClockRUN();
}
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
 * SYSPLL clock PFD0      : 480 * 18 / 22 = 392MHz
 * SYSPLLDIV1_CLK output  : 392MHz (async platform clock)
 * SYSPLLDIV2_CLK output  : 196MHz (async bus clock)
 * SYSPLLDIV3_CLK output  : 0MHz   (async slow clock)
 * PFD0 selected for sync system clock
 */
const scg_spll_config_t g_scgSysPllConfig = {.enableMode    = kSCG_SysPllEnable,
                                             .div1          = kSCG_AsyncClkDivBy1,
                                             .div2          = kSCG_AsyncClkDivBy2,
                                             .div3          = kSCG_AsyncClkDisable,
                                             .src           = kSCG_SysPllSrcSysOsc,
                                             .isPfdSelected = true,
                                             .prediv        = 0U,
                                             .pfdClkout     = kSCG_SysPllPfd0Clk,
                                             .mult          = 3U}; /* x20 */

/*
 * AUXPLL clock setting.
 * AUXPLL clock           : 540.672MHz / 88 = 6.144MHz
 * AUXPLLDIV1_CLK output  : 6.144MHz (async platform clock)
 * AUXPLLDIV2_CLK output  : 6.144MHz (async bus clock)
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
                                             .pllPostdiv2   = kSCG_SysClkDivBy8,
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
 * Clock source   : SYSPLL PFD0 392MHz
 * Core clock     : 98MHz
 * Platform clock : 98MHz
 * Bus clock      : 49MHz
 * Slow clock     : 24.5MHz
 */
const scg_sys_clk_config_t g_sysClkConfigNormalRun = {
    .divCore = kSCG_SysClkDivBy4,   /* Core clock divider. */
    .divPlat = kSCG_SysClkDivBy1,   /* Platform clock divider. */
    .divBus  = kSCG_SysClkDivBy2,   /* Bus clock divider. */
    .divSlow = kSCG_SysClkDivBy4,   /* Slow clock divider. */
    .src     = kSCG_SysClkSrcSysPll /* System clock source. */
};

/*
 * System clock source and divider in HSRUN mode.
 * Clock source   : SYSPLL PFD0 392MHz
 * Core clock     : 196MHz
 * Platform clock : 196MHz
 * Bus clock      : 98MHz
 * Slow clock     : 49MHz
 */
const scg_sys_clk_config_t g_sysClkConfigHsrun = {
    .divCore = kSCG_SysClkDivBy2,   /* Core clock divider. */
    .divPlat = kSCG_SysClkDivBy1,   /* Platform clock divider. */
    .divBus  = kSCG_SysClkDivBy2,   /* Bus clock divider. */
    .divSlow = kSCG_SysClkDivBy4,   /* Slow clock divider. */
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
typedef void (*BOARD_SetRunModeFunc)(
    SCG_Type *scg, uint32_t scgRunConfig, QuadSPI_Type *qspi, clock_ip_name_t qspiClock, uint32_t qspiClockConfig);
#if 0
void BOARD_SetRunMode(SCG_Type *scg, uint32_t scgRunConfig, QuadSPI_Type *qspi,
                      clock_ip_name_t qspiClock, uint32_t qspiClockConfig)
{
    int32_t i;

    scg->RCCR = scgRunConfig;

    /* Wait for clock source switch finished. */
    while ((scg->CSR & SCG_CSR_SCS_MASK) != (scgRunConfig & SCG_CSR_SCS_MASK))
    {
    }

    if (qspi)
    {
        volatile uint32_t *pcc = (volatile uint32_t *)qspiClock;

        /* Make sure QSPI clock is enabled */
        *pcc |= PCC1_PCC_QSPI_OTFAD_CGC_MASK;
        /* Wait until QSPI is not busy */
        while (qspi->SR & QuadSPI_SR_BUSY_MASK)
        {
        }
        /* Make sure module is enabled when reset */
        qspi->MCR &= ~QuadSPI_MCR_MDIS_MASK;
        qspi->MCR |= QuadSPI_MCR_SWRSTHD_MASK | QuadSPI_MCR_SWRSTSD_MASK;
        /* Wait enough cycles until the ahb domain and serial flash domain are reset */
        for (i = 0; i < 200; i++)
        {
            qspi->SR;
        }
        /* Disable module during the reset procedure */
        qspi->MCR |= QuadSPI_MCR_MDIS_MASK;
        /* Clear the reset bits. */
        qspi->MCR &= ~(QuadSPI_MCR_SWRSTHD_MASK | QuadSPI_MCR_SWRSTSD_MASK);

        *pcc = 0; /* Disable clock before changing clock source */
        *pcc = qspiClockConfig;
        /* Re-enable QSPI module */
        qspi->MCR &= ~QuadSPI_MCR_MDIS_MASK;
    }
}
#endif
/* The code array is built from above BOARD_SetRunMode() prototype */
uint16_t BOARD_SetRunModeCode[] = {
    0xb430,         /* push    {r4, r5} */
    0x6141,         /* str     r1, [r0, #20] */
    0xf001, 0x6570, /* and.w   r5, r1, #251658240    ; 0xf000000 */
    0x6904,         /* ldr     r4, [r0, #16] */
    0xf004, 0x6470, /* and.w   r4, r4, #251658240    ; 0xf000000 */
    0x42ac,         /* cmp     r4, r5 */
    0xd1fa,         /* bne.n   <BOARD_SetRunMode+0x8> */
    0xb322,         /* cbz     r2, <BOARD_SetRunMode+0x5e> */
    0x6818,         /* ldr     r0, [r3, #0] */
    0xf040, 0x4080, /* orr.w   r0, r0, #1073741824   ; 0x40000000 */
    0x6018,         /* str     r0, [r3, #0] */
    0xf8d2, 0x015c, /* ldr.w   r0, [r2, #348]    ; 0x15c */
    0x07c0,         /* lsls    r0, r0, #31 */
    0xd4fb,         /* bmi.n   <BOARD_SetRunMode+0x1c> */
    0x6810,         /* ldr     r0, [r2, #0] */
    0xf420, 0x4080, /* bic.w   r0, r0, #16384    ; 0x4000 */
    0x6010,         /* str     r0, [r2, #0] */
    0x6810,         /* ldr     r0, [r2, #0] */
    0xf040, 0x0003, /* orr.w   r0, r0, #3 */
    0x6010,         /* str     r0, [r2, #0] */
    0x20c8,         /* movs    r0, #200    ; 0xc8 */
    0xf8d2, 0x115c, /* ldr.w   r1, [r2, #348]    ; 0x15c */
    0x1e40,         /* subs    r0, r0, #1 */
    0xd1fb,         /* bne.n   <BOARD_SetRunMode+0x36> */
    0x6810,         /* ldr     r0, [r2, #0] */
    0xf440, 0x4080, /* orr.w   r0, r0, #16384    ; 0x4000 */
    0x6010,         /* str     r0, [r2, #0] */
    0x6810,         /* ldr     r0, [r2, #0] */
    0x0880,         /* lsrs    r0, r0, #2 */
    0x0080,         /* lsls    r0, r0, #2 */
    0x6010,         /* str     r0, [r2, #0] */
    0x2000,         /* movs    r0, #0 */
    0x6018,         /* str     r0, [r3, #0] */
    0x9802,         /* ldr     r0, [sp, #8] */
    0x6018,         /* str     r0, [r3, #0] */
    0x6810,         /* ldr     r0, [r2, #0] */
    0xf420, 0x4080, /* bic.w   r0, r0, #16384    ; 0x4000 */
    0x6010,         /* str     r0, [r2, #0] */
    0xbc30,         /* pop     {r4, r5} */
    0x4770,         /* bx      lr */
};

static bool BOARD_IsRunOnQSPI(void)
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
    SCG0->FIRCCSR |= SCG_FIRCCSR_FIRCSTEN_MASK;
    SCG0->SIRCCSR |= SCG_SIRCCSR_SIRCSTEN_MASK;

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
    scg_sys_clk_config_t curConfig;
    /* BOARD_SetRunMode is running in TCM to avoid clock change issue on QSPI memory */
    BOARD_SetRunModeFunc BOARD_SetRunMode =
        (BOARD_SetRunModeFunc)(((uint32_t)BOARD_SetRunModeCode) | 1U); /* Thumb code */
    QuadSPI_Type *qspi = BOARD_IsRunOnQSPI() ? QuadSPI0 : NULL;

    BOARD_InitClock();

    /* Change to use SIRC as RUN system clock source */
    BOARD_SetRunMode(SCG0, *((uint32_t *)(&g_sysClkConfigVlpr)), qspi, kCLOCK_Qspi,
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
    /* BOARD_SetRunMode is running in TCM to avoid clock change issue on QSPI memory */
    BOARD_SetRunModeFunc BOARD_SetRunMode =
        (BOARD_SetRunModeFunc)(((uint32_t)BOARD_SetRunModeCode) | 1U); /* Thumb code */
    QuadSPI_Type *qspi = BOARD_IsRunOnQSPI() ? QuadSPI0 : NULL;

    BOARD_InitClock();

    /* Change to use SIRC as system clock source to prepare to initialize other clock sources */
    BOARD_SetRunMode(SCG0, *((uint32_t *)(&g_sysClkConfigVlpr)), qspi, kCLOCK_Qspi,
                     PCC1_PCC_QSPI_OTFAD_CGC_MASK | PCC1_PCC_QSPI_OTFAD_PCS(2)); /* QSPI source: 16M SIRC Async */

    /* Initialize SysPll 480MHz */
    CLOCK_InitSysPll(&g_scgSysPllConfig);

    /* Enable SysPll Pfd0 392MHz */
    CLOCK_EnableSysPllPfdClkout(kSCG_SysPllPfd0Clk, 22U);
    /* Enable SysPll Pfd3 480MHz (same as SysPll main clock) */
    CLOCK_EnableSysPllPfdClkout(kSCG_SysPllPfd3Clk, 18U);

    /* Initialize AuxPll */
    CLOCK_InitAuxPll(&g_scgAuxPllConfig);
    /* Enable AuxPll Pfd0 540.672MHz (same as AuxPll before postdiv) */
    CLOCK_EnableAuxPllPfdClkout(kSCG_AuxPllPfd0Clk, 18U);

    BOARD_SetRunMode(SCG0, *((uint32_t *)(&g_sysClkConfigNormalRun)), qspi, kCLOCK_Qspi,
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
 */
void BOARD_BootClockHSRUN(void)
{
    scg_sys_clk_config_t curConfig;

    BOARD_BootClockRUN();

    /* Change to use SysPll Pfd0 as system clock source */
    CLOCK_SetHsrunModeSysClkConfig(&g_sysClkConfigHsrun);

    /* Switch running mode to HSRUN */
    SMC_SetPowerModeProtection(MSMC0, kSMC_AllowPowerModeAll);
    SMC_SetPowerModeHsrun(MSMC0);
    while (SMC_GetPowerModeState(MSMC0) != kSMC_PowerStateHsrun)
    {
    }

    /* Wait for clock source switch finished. */
    do
    {
        CLOCK_GetCurSysClkConfig(&curConfig);
    } while (curConfig.src != g_sysClkConfigHsrun.src);

    SystemCoreClockUpdate();
}
