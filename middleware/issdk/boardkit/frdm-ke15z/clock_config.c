/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
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

/* TEXT BELOW IS USED AS SETTING FOR THE CLOCKS TOOL *****************************
!!ClocksProfile
product: Clocks v1.0
processor: MKE15Z256xxx7
package_id: MKE15Z256VLL7
mcu_data: ksdk2_0
processor_version: 1.1.0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE CLOCKS TOOL **/

#include "fsl_smc.h"
#include "clock_config.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

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
         .divSlow = kSCG_SysClkDivBy4, /* Slow clock divider */
         .divCore = kSCG_SysClkDivBy1, /* Core clock divider */
         .src = kSCG_SysClkSrcSirc     /* System clock source */
    };
    /* Init Sirc. */
    CLOCK_InitSirc(&scgSircConfig);
    /* Change to use SIRC as system clock source to prepare to change FIRCCFG register. */
    CLOCK_SetRunModeSysClkConfig(&sysClkSafeConfigSource);
    /* Wait for clock source switch finished. */
    do
    {
         CLOCK_GetCurSysClkConfig(&curConfig);
    } while (curConfig.src != sysClkSafeConfigSource.src);

    /* Init Firc. */
    CLOCK_InitFirc(fircConfig);
    /* Change back to use FIRC as system clock source in order to configure SIRC if needed. */
    sysClkSafeConfigSource.src = kSCG_SysClkSrcFirc;
    CLOCK_SetRunModeSysClkConfig(&sysClkSafeConfigSource);
    /* Wait for clock source switch finished. */
    do
    {
         CLOCK_GetCurSysClkConfig(&curConfig);
    } while (curConfig.src != sysClkSafeConfigSource.src);
}

/*******************************************************************************
 ********************** Configuration BOARD_BootClockRUN ***********************
 ******************************************************************************/
/* TEXT BELOW IS USED AS SETTING FOR THE CLOCKS TOOL *****************************
!!Configuration
name: BOARD_BootClockRUN
outputs:
- {id: Bus_clock.outFreq, value: 24 MHz}
- {id: Core_clock.outFreq, value: 72 MHz}
- {id: FIRCDIV2_CLK.outFreq, value: 48 MHz}
- {id: FLLDIV2_CLK.outFreq, value: 36 MHz}
- {id: Flash_clock.outFreq, value: 24 MHz}
- {id: LPO1KCLK.outFreq, value: 1 kHz}
- {id: LPO_clock.outFreq, value: 128 kHz}
- {id: SIRCDIV2_CLK.outFreq, value: 4 MHz}
- {id: SIRC_CLK.outFreq, value: 8 MHz}
- {id: SOSCDIV2_CLK.outFreq, value: 8 MHz}
- {id: SOSC_CLK.outFreq, value: 8 MHz}
- {id: System_clock.outFreq, value: 72 MHz}
settings:
- {id: SCGMode, value: LPFLL}
- {id: OSC32_CR_ROSCE_CFG, value: Enabled}
- {id: SCG.DIVCORE.scale, value: '1', locked: true}
- {id: SCG.DIVSLOW.scale, value: '3', locked: true}
- {id: SCG.FIRCDIV2.scale, value: '1'}
- {id: SCG.LPFLLDIV2.scale, value: '2'}
- {id: SCG.LPFLL_mul.scale, value: '36', locked: true}
- {id: SCG.SCSSEL.sel, value: SCG.LPFLL}
- {id: SCG.SIRCDIV2.scale, value: '2'}
- {id: SCG.SOSCDIV2.scale, value: '1'}
- {id: SCG.TRIMDIV.scale, value: '4'}
- {id: SCG_LPFLLCSR_LPFLLEN_CFG, value: Enabled}
- {id: SCG_SIRCCSR_SIRCLPEN_CFG, value: Disabled}
- {id: SCG_SOSCCFG_OSC_MODE_CFG, value: ModeOscLowPower}
- {id: SCG_SOSCCFG_RANGE_CFG, value: Medium}
- {id: SCG_SOSCCSR_SOSCEN_CFG, value: Enabled}
- {id: SCG_SOSCCSR_SOSCLPEN_CFG, value: Enabled}
sources:
- {id: SCG.SOSC.outFreq, value: 8 MHz, enabled: true}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE CLOCKS TOOL **/

/*******************************************************************************
 * Variables for BOARD_BootClockRUN configuration
 ******************************************************************************/
const scg_sys_clk_config_t g_sysClkConfig_BOARD_BootClockRUN =
    {
        .divSlow = kSCG_SysClkDivBy3,             /* Slow Clock Divider: divided by 3 */
        .divCore = kSCG_SysClkDivBy1,             /* Core Clock Divider: divided by 1 */
        .src = kSCG_SysClkSrcLpFll,               /* Low power FLL is selected as System Clock Source */
    };
const scg_sosc_config_t g_scgSysOscConfig_BOARD_BootClockRUN =
    {
        .freq = 8000000U,                         /* System Oscillator frequency: 8000000Hz */
        .enableMode = kSCG_SysOscEnable | kSCG_SysOscEnableInLowPower,/* Enable System OSC clock, Enable System OSC in low power mode */
        .monitorMode = kSCG_SysOscMonitorDisable, /* Monitor disabled */
        .div2 = kSCG_AsyncClkDivBy1,              /* System OSC Clock Divider 2: divided by 1 */
        .workMode = kSCG_SysOscModeOscLowPower,   /* Oscillator low power */
    };
const scg_sirc_config_t g_scgSircConfig_BOARD_BootClockRUN =
    {
        .enableMode = kSCG_SircEnable,            /* Enable SIRC clock */
        .div2 = kSCG_AsyncClkDivBy2,              /* Slow IRC Clock Divider 2: divided by 2 */
        .range = kSCG_SircRangeHigh,              /* Slow IRC high range clock (8 MHz) */
    };
const scg_firc_config_t g_scgFircConfig_BOARD_BootClockRUN =
    {
        .enableMode = kSCG_FircEnable,            /* Enable FIRC clock */
        .div2 = kSCG_AsyncClkDivBy1,              /* Fast IRC Clock Divider 2: divided by 1 */
        .range = kSCG_FircRange48M,               /* Fast IRC is trimmed to 48MHz */
        .trimConfig = NULL,                       /* Fast IRC Trim disabled */
    };
const scg_lpfll_config_t g_scgLpFllConfig_BOARD_BootClockRUN =
    {
        .enableMode = kSCG_LpFllEnable,           /* Enable LPFLL clock */
        .div2 = kSCG_AsyncClkDivBy2,              /* Low Power FLL Clock Divider 2: divided by 2 */
        .range = kSCG_LpFllRange72M,              /* LPFLL is trimmed to 72MHz */
        .trimConfig = NULL,
    };
/*******************************************************************************
 * Code for BOARD_BootClockRUN configuration
 ******************************************************************************/
void BOARD_BootClockRUN(void)
{
    scg_sys_clk_config_t curConfig;

    /* Init SOSC according to board configuration. */
    CLOCK_InitSysOsc(&g_scgSysOscConfig_BOARD_BootClockRUN);
    /* Set the XTAL0 frequency based on board settings. */
    CLOCK_SetXtal0Freq(g_scgSysOscConfig_BOARD_BootClockRUN.freq);
    /* Init FIRC. */
    CLOCK_CONFIG_FircSafeConfig(&g_scgFircConfig_BOARD_BootClockRUN);
    /* Init SIRC. */
    CLOCK_InitSirc(&g_scgSircConfig_BOARD_BootClockRUN);
    /* Init LPFLL. */
    CLOCK_InitLpFll(&g_scgLpFllConfig_BOARD_BootClockRUN);
    /* Set SCG to LPFLL mode. */
    CLOCK_SetRunModeSysClkConfig(&g_sysClkConfig_BOARD_BootClockRUN);
    /* Wait for clock source switch finished. */
    do
    {
         CLOCK_GetCurSysClkConfig(&curConfig);
    } while (curConfig.src != g_sysClkConfig_BOARD_BootClockRUN.src);
    /* Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKRUN_CORE_CLOCK;
}

/*******************************************************************************
 ********************* Configuration BOARD_BootClockVLPR ***********************
 ******************************************************************************/
/* TEXT BELOW IS USED AS SETTING FOR THE CLOCKS TOOL *****************************
!!Configuration
name: BOARD_BootClockVLPR
outputs:
- {id: Bus_clock.outFreq, value: 1 MHz}
- {id: Core_clock.outFreq, value: 4 MHz}
- {id: Flash_clock.outFreq, value: 1 MHz}
- {id: LPO1KCLK.outFreq, value: 1 kHz}
- {id: LPO_clock.outFreq, value: 128 kHz}
- {id: SOSCDIV2_CLK.outFreq, value: 8 MHz}
- {id: SOSC_CLK.outFreq, value: 8 MHz}
- {id: System_clock.outFreq, value: 4 MHz}
settings:
- {id: SCGMode, value: SOSC}
- {id: powerMode, value: VLPR}
- {id: OSC32_CR_ROSCE_CFG, value: Enabled}
- {id: SCG.DIVCORE.scale, value: '2', locked: true}
- {id: SCG.DIVSLOW.scale, value: '4', locked: true}
- {id: SCG.FIRCDIV2.scale, value: '1'}
- {id: SCG.LPFLLDIV2.scale, value: '2'}
- {id: SCG.LPFLL_mul.scale, value: '36', locked: true}
- {id: SCG.SCSSEL.sel, value: SCG.SOSC}
- {id: SCG.SIRCDIV2.scale, value: '2'}
- {id: SCG.SOSCDIV2.scale, value: '1'}
- {id: SCG.TRIMDIV.scale, value: '4'}
- {id: 'SCG::RCCR[DIVSLOW].bitField', value: Divide-by-3}
- {id: SCG_LPFLLCSR_LPFLLEN_CFG, value: Enabled}
- {id: SCG_SIRCCSR_SIRCLPEN_CFG, value: Disabled}
- {id: SCG_SOSCCFG_OSC_MODE_CFG, value: ModeOscLowPower}
- {id: SCG_SOSCCFG_RANGE_CFG, value: Medium}
- {id: SCG_SOSCCSR_SOSCEN_CFG, value: Enabled}
- {id: SCG_SOSCCSR_SOSCLPEN_CFG, value: Enabled}
sources:
- {id: SCG.SOSC.outFreq, value: 8 MHz, enabled: true}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE CLOCKS TOOL **/

/*******************************************************************************
 * Variables for BOARD_BootClockVLPR configuration
 ******************************************************************************/
const scg_sys_clk_config_t g_sysClkConfig_BOARD_BootClockVLPR =
    {
        .divSlow = kSCG_SysClkDivBy4,             /* Slow Clock Divider: divided by 4 */
        .divCore = kSCG_SysClkDivBy2,             /* Core Clock Divider: divided by 2 */
        .src = kSCG_SysClkSrcSysOsc,              /* System OSC is selected as System Clock Source */
    };
const scg_sosc_config_t g_scgSysOscConfig_BOARD_BootClockVLPR =
    {
        .freq = 8000000U,                         /* System Oscillator frequency: 8000000Hz */
        .enableMode = kSCG_SysOscEnable | kSCG_SysOscEnableInLowPower,/* Enable System OSC clock, Enable System OSC in low power mode */
        .monitorMode = kSCG_SysOscMonitorDisable, /* Monitor disabled */
        .div2 = kSCG_AsyncClkDivBy1,              /* System OSC Clock Divider 2: divided by 1 */
        .workMode = kSCG_SysOscModeOscLowPower,   /* Oscillator low power */
    };
const scg_sirc_config_t g_scgSircConfig_BOARD_BootClockVLPR =
    {
        .enableMode = kSCG_SircEnable,            /* Enable SIRC clock */
        .div2 = kSCG_AsyncClkDivBy2,              /* Slow IRC Clock Divider 2: divided by 2 */
        .range = kSCG_SircRangeHigh,              /* Slow IRC high range clock (8 MHz) */
    };
const scg_firc_config_t g_scgFircConfig_BOARD_BootClockVLPR =
    {
        .enableMode = kSCG_FircEnable,            /* Enable FIRC clock */
        .div2 = kSCG_AsyncClkDivBy1,              /* Fast IRC Clock Divider 2: divided by 1 */
        .range = kSCG_FircRange48M,               /* Fast IRC is trimmed to 48MHz */
        .trimConfig = NULL,                       /* Fast IRC Trim disabled */
    };
const scg_lpfll_config_t g_scgLpFllConfig_BOARD_BootClockVLPR =
    {
        .enableMode = kSCG_LpFllEnable,           /* Enable LPFLL clock */
        .div2 = kSCG_AsyncClkDivBy2,              /* Low Power FLL Clock Divider 2: divided by 2 */
        .range = kSCG_LpFllRange72M,              /* LPFLL is trimmed to 72MHz */
        .trimConfig = NULL,
    };
/*******************************************************************************
 * Code for BOARD_BootClockVLPR configuration
 ******************************************************************************/
void BOARD_BootClockVLPR(void)
{
    /* Init SOSC according to board configuration. */
    CLOCK_InitSysOsc(&g_scgSysOscConfig_BOARD_BootClockVLPR);
    /* Set the XTAL0 frequency based on board settings. */
    CLOCK_SetXtal0Freq(g_scgSysOscConfig_BOARD_BootClockVLPR.freq);
    /* Set SCG to SOSC mode. */
    CLOCK_SetVlprModeSysClkConfig(&g_sysClkConfig_BOARD_BootClockVLPR);
    /* Allow SMC all power modes. */
    SMC_SetPowerModeProtection(SMC, kSMC_AllowPowerModeAll);
    /* Set VLPR power mode. */
    SMC_SetPowerModeVlpr(SMC);
    while (SMC_GetPowerModeState(SMC) != kSMC_PowerStateVlpr)
    {
    }
    /* Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKVLPR_CORE_CLOCK;
}

