/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
 
/*
 * How to setup clock using clock driver functions:
 *
 * 1. Call CLOCK_InitXXX() to configure corresponding SCG clock source.
 *    Note: The clock could not be set when it is being used as system clock.
 *    In default out of reset, the CPU is clocked from FIRC(IRC48M),
 *    so before setting FIRC, change to use another avaliable clock source.
 *
 * 2. Call CLOCK_SetXtal0Freq() to set XTAL0 frequency based on board settings.
 *
 * 3. Call CLOCK_SetXxxModeSysClkConfig() to set SCG mode for Xxx run mode.
 *    Wait until the system clock source is changed to target source.
 *
 * 4. If power mode change is needed, call SMC_SetPowerModeProtection() to allow
 *    corresponding power mode and SMC_SetPowerModeXxx() to change to Xxx mode.
 *    Supported run mode and clock restrictions could be found in Reference Manual.
 */

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Clocks v3.0
processor: K32W042S1M2xxx
package_id: K32W042S1M2VPJ
mcu_data: ksdk2_0
processor_version: 0.0.0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

#include "clock_config.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SCG_LPFLL_DISABLE 0U /*!< LPFLL clock disabled */

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* System clock frequency. */
extern uint32_t SystemCoreClock;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_CONFIG_FircSafeConfig
 * Description   : This function is used to safely configure FIRC clock.
 *                 In default out of reset, the CPU is clocked from FIRC(IRC48M).
 *                 Before setting FIRC, change to use SIRC as system clock,
 *                 then configure FIRC. After FIRC is set, change back to use FIRC
 *                 in case SIRC need to be configured.
 * Param fircConfig  : FIRC configuration.
 *
 *END**************************************************************************/
static void CLOCK_CONFIG_FircSafeConfig(const scg_firc_config_t *fircConfig)
{
    scg_sys_clk_config_t curConfig;
    const scg_sirc_config_t scgSircConfig = {.enableMode = kSCG_SircEnable,
                                             .div1 = kSCG_AsyncClkDisable,
                                             .div2 = kSCG_AsyncClkDivBy2,
                                             .range = kSCG_SircRangeHigh};
    scg_sys_clk_config_t sysClkSafeConfigSource = {
        .divSlow = kSCG_SysClkDivBy4, /* Slow clock divider. */
        .divCore = kSCG_SysClkDivBy1, /* Core clock divider. */
        .src = kSCG_SysClkSrcSirc     /* System clock source. */
    };
    /* Init Sirc */
    CLOCK_InitSirc(&scgSircConfig);
    /* Change to use SIRC as system clock source to prepare to change FIRCCFG register */
    CLOCK_SetRunModeSysClkConfig(&sysClkSafeConfigSource);
    /* Wait for clock source switch finished */
    do
    {
        CLOCK_GetCurSysClkConfig(&curConfig);
    } while (curConfig.src != sysClkSafeConfigSource.src);

    /* Init Firc */
    CLOCK_InitFirc(fircConfig);
    /* Change back to use FIRC as system clock source in order to configure SIRC if needed */
    sysClkSafeConfigSource.src = kSCG_SysClkSrcFirc;
    CLOCK_SetRunModeSysClkConfig(&sysClkSafeConfigSource);
    /* Wait for clock source switch finished */
    do
    {
        CLOCK_GetCurSysClkConfig(&curConfig);
    } while (curConfig.src != sysClkSafeConfigSource.src);
}

/*******************************************************************************
 ************************ BOARD_InitBootClocks function ************************
 ******************************************************************************/
void BOARD_InitBootClocks(void)
{
    BOARD_BootClockRUN();
}

/*******************************************************************************
 ********************** Configuration BOARD_BootClockRUN ***********************
 ******************************************************************************/
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockRUN
called_from_default_init: true
outputs:
- {id: Bus_clock.outFreq, value: 48 MHz}
- {id: Core_clock.outFreq, value: 48 MHz}
- {id: FIRCDIV2_CLK.outFreq, value: 48 MHz}
- {id: LPO_CLK.outFreq, value: 1 kHz}
- {id: PCC0.PCC_LPUART0_CLK.outFreq, value: 48 MHz}
- {id: Platform_clock.outFreq, value: 48 MHz}
- {id: Slow_clock.outFreq, value: 24 MHz}
- {id: System_clock.outFreq, value: 48 MHz}
settings:
- {id: PCC0.PCC_LPUART0_SEL.sel, value: SCG.FIRCDIV2_CLK}
- {id: SCG.FIRCDIV2.scale, value: '1', locked: true}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/*******************************************************************************
 * Variables for BOARD_BootClockRUN configuration
 ******************************************************************************/
const scg_sys_clk_config_t g_sysClkConfig_BOARD_BootClockRUN = {
    .divSlow = kSCG_SysClkDivBy2, /* Slow Clock Divider: divided by 2 */
    .divBus = kSCG_SysClkDivBy1,  /* Bus Clock Divider: divided by 1 */
    .divExt = kSCG_SysClkDivBy1,  /* External Clock Divider: divided by 1 */
    .divCore = kSCG_SysClkDivBy1, /* Core Clock Divider: divided by 1 */
    .src = kSCG_SysClkSrcFirc,    /* Fast IRC is selected as System Clock Source */
};
const scg_sosc_config_t g_scgSysOscConfig_BOARD_BootClockRUN = {
    .freq = 0U,                   /* System Oscillator frequency: 0Hz */
    .div1 = kSCG_AsyncClkDisable, /* System OSC Clock Divider 1: Clock output is disabled */
    .div2 = kSCG_AsyncClkDisable, /* System OSC Clock Divider 2: Clock output is disabled */
    .div3 = kSCG_AsyncClkDisable, /* System OSC Clock Divider 3: Clock output is disabled */
};
const scg_sirc_config_t g_scgSircConfig_BOARD_BootClockRUN = {
    .enableMode = kSCG_SircEnable | kSCG_SircEnableInLowPower, /* Enable SIRC clock, Enable SIRC in low power mode */
    .div1 = kSCG_AsyncClkDisable,                              /* Slow IRC Clock Divider 1: Clock output is disabled */
    .div2 = kSCG_AsyncClkDisable,                              /* Slow IRC Clock Divider 2: Clock output is disabled */
    .div3 = kSCG_AsyncClkDivBy1,                               /* Slow IRC Clock Divider 3: divided by 1 */
    .range = kSCG_SircRangeHigh,                               /* Slow IRC high range clock (8 MHz) */
};
const scg_firc_config_t g_scgFircConfig_BOARD_BootClockRUN = {
    .enableMode = kSCG_FircEnable, /* Enable FIRC clock */
    .div1 = kSCG_AsyncClkDivBy1,   /* Fast IRC Clock Divider 1: divided by 1  */
    .div2 = kSCG_AsyncClkDivBy1,   /* Fast IRC Clock Divider 2: divided by 1 */
    .div3 = kSCG_AsyncClkDivBy1,   /* Fast IRC Clock Divider 3: divided by 1 */
    .range = kSCG_FircRange48M,    /* Fast IRC is trimmed to 48MHz */
    .trimConfig = NULL,            /* Fast IRC Trim disabled */
};
const scg_lpfll_config_t g_scgLpFllConfig_BOARD_BootClockRUN = {
    .enableMode = kSCG_LpFllEnable, /* LPFLL clock disabled */
    .div1 = kSCG_AsyncClkDivBy1,    /* Low Power FLL Clock Divider 1: Clock output is disabled */
    .div2 = kSCG_AsyncClkDisable,   /* Low Power FLL Clock Divider 2: Clock output is disabled */
    .div3 = kSCG_AsyncClkDisable,   /* Low Power FLL Clock Divider 3: Clock output is disabled */
    .range = kSCG_LpFllRange72M,    /* LPFLL is trimmed to 48MHz */
    .trimConfig = NULL,
};
/*******************************************************************************
 * Code for BOARD_BootClockRUN configuration
 ******************************************************************************/
void BOARD_BootClockRUN(void)
{
    scg_sys_clk_config_t curConfig;

    /* Init FIRC */
    CLOCK_CONFIG_FircSafeConfig(&g_scgFircConfig_BOARD_BootClockRUN);
    /* Set SCG to FIRC mode. */
    CLOCK_SetRunModeSysClkConfig(&g_sysClkConfig_BOARD_BootClockRUN);
    /* Wait for clock source switch finished */
    do
    {
        CLOCK_GetCurSysClkConfig(&curConfig);
    } while (curConfig.src != g_sysClkConfig_BOARD_BootClockRUN.src);
    /* Init SIRC */
    CLOCK_InitSirc(&g_scgSircConfig_BOARD_BootClockRUN);
    /* Init LPFLL */
    CLOCK_InitLpFll(&g_scgLpFllConfig_BOARD_BootClockRUN);
    /* Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKRUN_CORE_CLOCK;
    /* Set PCC LPUART0 selection */
    CLOCK_SetIpSrc(kCLOCK_Lpuart0, kCLOCK_IpSrcFircAsync);
}
