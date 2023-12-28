/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * How to set up clock using clock driver functions:
 *
 * 1. Setup clock sources.
 *
 * 2. Set up all dividers.
 *
 * 3. Set up all selectors to provide selected clocks.
 */

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Clocks v12.0
processor: LPC865
package_id: LPC865M201JBD64
mcu_data: ksdk2_0
processor_version: 0.14.4
board: LPCXpresso860MAX
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

#include "fsl_power.h"
#include "fsl_clock.h"
#include "clock_config.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 ************************ BOARD_InitBootClocks function ************************
 ******************************************************************************/
void BOARD_InitBootClocks(void)
{
    BOARD_BootClockFRO60M();
}

/*******************************************************************************
 ******************** Configuration BOARD_BootClockFRO18M **********************
 ******************************************************************************/
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockFRO18M
outputs:
- {id: FROHF_clock.outFreq, value: 36 MHz}
- {id: System_clock.outFreq, value: 18 MHz}
- {id: WKT_clock.outFreq, value: 18 MHz}
settings:
- {id: SYSCON.ADCCLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.CLKOUTSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FRG0CLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FRG1CLKSEL.sel, value: NO_CLOCK}
sources:
- {id: SYSCON.fro_osc.outFreq, value: 36 MHz}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/*******************************************************************************
 * Variables for BOARD_BootClockFRO18M configuration
 ******************************************************************************/
/*******************************************************************************
 * Code for BOARD_BootClockFRO18M configuration
 ******************************************************************************/
void BOARD_BootClockFRO18M(void)
{
    /*!< Set up the clock sources */
    /*!< Set up FRO */
    POWER_DisablePD(kPDRUNCFG_PD_FRO_OUT);                      /*!< Ensure FRO is on  */
    POWER_DisablePD(kPDRUNCFG_PD_FRO);                          /*!< Ensure FRO is on  */
    CLOCK_SetFroOscFreq(kCLOCK_FroOscOut36M);                   /*!< Set up FRO freq */
    CLOCK_SetFroOutClkSrc(kCLOCK_FroSrcFroOscDiv);              /*!< Set FRO clock source */
    CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcFro);                  /*!< select fro for main clock */
    CLOCK_Select(kWKT_Clk_From_Fro);                            /*!< select FRO for WKT */
    CLOCK_SetCoreSysClkDiv(1U);
    /*!< Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKFRO18M_CORE_CLOCK;
}

/*******************************************************************************
 ******************** Configuration BOARD_BootClockFRO24M **********************
 ******************************************************************************/
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockFRO24M
outputs:
- {id: FROHF_clock.outFreq, value: 48 MHz}
- {id: System_clock.outFreq, value: 24 MHz}
- {id: WKT_clock.outFreq, value: 24 MHz}
settings:
- {id: SYSCON.ADCCLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.CLKOUTSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FRG0CLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FRG1CLKSEL.sel, value: NO_CLOCK}
sources:
- {id: SYSCON.fro_osc.outFreq, value: 48 MHz}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/*******************************************************************************
 * Variables for BOARD_BootClockFRO24M configuration
 ******************************************************************************/
/*******************************************************************************
 * Code for BOARD_BootClockFRO24M configuration
 ******************************************************************************/
void BOARD_BootClockFRO24M(void)
{
    /*!< Set up the clock sources */
    /*!< Set up FRO */
    POWER_DisablePD(kPDRUNCFG_PD_FRO_OUT);                      /*!< Ensure FRO is on  */
    POWER_DisablePD(kPDRUNCFG_PD_FRO);                          /*!< Ensure FRO is on  */
    CLOCK_SetFroOscFreq(kCLOCK_FroOscOut48M);                   /*!< Set up FRO freq */
    CLOCK_SetFroOutClkSrc(kCLOCK_FroSrcFroOscDiv);              /*!< Set FRO clock source */
    CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcFro);                  /*!< select fro for main clock */
    CLOCK_Select(kWKT_Clk_From_Fro);                            /*!< select FRO for WKT */
    CLOCK_SetCoreSysClkDiv(1U);
    /*!< Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKFRO24M_CORE_CLOCK;
}

/*******************************************************************************
 ******************** Configuration BOARD_BootClockFRO30M **********************
 ******************************************************************************/
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockFRO30M
outputs:
- {id: FROHF_clock.outFreq, value: 60 MHz}
- {id: System_clock.outFreq, value: 30 MHz}
- {id: WKT_clock.outFreq, value: 30 MHz}
settings:
- {id: SYSCON.ADCCLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.CLKOUTSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FRG0CLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FRG1CLKSEL.sel, value: NO_CLOCK}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/*******************************************************************************
 * Variables for BOARD_BootClockFRO30M configuration
 ******************************************************************************/
/*******************************************************************************
 * Code for BOARD_BootClockFRO30M configuration
 ******************************************************************************/
void BOARD_BootClockFRO30M(void)
{
    /*!< Set up the clock sources */
    /*!< Set up FRO */
    POWER_DisablePD(kPDRUNCFG_PD_FRO_OUT);                      /*!< Ensure FRO is on  */
    POWER_DisablePD(kPDRUNCFG_PD_FRO);                          /*!< Ensure FRO is on  */
    CLOCK_SetFroOscFreq(kCLOCK_FroOscOut60M);                   /*!< Set up FRO freq */
    CLOCK_SetFroOutClkSrc(kCLOCK_FroSrcFroOscDiv);              /*!< Set FRO clock source */
    CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcFro);                  /*!< select fro for main clock */
    CLOCK_Select(kWKT_Clk_From_Fro);                            /*!< select FRO for WKT */
    CLOCK_SetCoreSysClkDiv(1U);
    /*!< Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKFRO30M_CORE_CLOCK;
}

/*******************************************************************************
 ******************** Configuration BOARD_BootClockFRO36M **********************
 ******************************************************************************/
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockFRO36M
outputs:
- {id: FROHF_clock.outFreq, value: 36 MHz}
- {id: System_clock.outFreq, value: 36 MHz}
- {id: WKT_clock.outFreq, value: 36 MHz}
settings:
- {id: SYSCON.ADCCLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.CLKOUTSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FRG0CLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FRG1CLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FRO_DIRECT.sel, value: SYSCON.fro_osc}
sources:
- {id: SYSCON.fro_osc.outFreq, value: 36 MHz}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/*******************************************************************************
 * Variables for BOARD_BootClockFRO36M configuration
 ******************************************************************************/
/*******************************************************************************
 * Code for BOARD_BootClockFRO36M configuration
 ******************************************************************************/
void BOARD_BootClockFRO36M(void)
{
    /*!< Set up the clock sources */
    /*!< Set up FRO */
    POWER_DisablePD(kPDRUNCFG_PD_FRO_OUT);                      /*!< Ensure FRO is on  */
    POWER_DisablePD(kPDRUNCFG_PD_FRO);                          /*!< Ensure FRO is on  */
    CLOCK_SetFroOscFreq(kCLOCK_FroOscOut36M);                   /*!< Set up FRO freq */
    CLOCK_SetFroOutClkSrc(kCLOCK_FroSrcFroOsc);                 /*!< Set FRO clock source */
    CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcFro);                  /*!< select fro for main clock */
    CLOCK_Select(kWKT_Clk_From_Fro);                            /*!< select FRO for WKT */
    CLOCK_SetCoreSysClkDiv(1U);
    /*!< Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKFRO36M_CORE_CLOCK;
}

/*******************************************************************************
 ******************** Configuration BOARD_BootClockFRO48M **********************
 ******************************************************************************/
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockFRO48M
outputs:
- {id: FROHF_clock.outFreq, value: 48 MHz}
- {id: System_clock.outFreq, value: 48 MHz}
- {id: WKT_clock.outFreq, value: 48 MHz}
settings:
- {id: SYSCON.ADCCLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.CLKOUTSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FRG0CLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FRG1CLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FRO_DIRECT.sel, value: SYSCON.fro_osc}
sources:
- {id: SYSCON.fro_osc.outFreq, value: 48 MHz}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/*******************************************************************************
 * Variables for BOARD_BootClockFRO48M configuration
 ******************************************************************************/
/*******************************************************************************
 * Code for BOARD_BootClockFRO48M configuration
 ******************************************************************************/
void BOARD_BootClockFRO48M(void)
{
    /*!< Set up the clock sources */
    /*!< Set up FRO */
    POWER_DisablePD(kPDRUNCFG_PD_FRO_OUT);                      /*!< Ensure FRO is on  */
    POWER_DisablePD(kPDRUNCFG_PD_FRO);                          /*!< Ensure FRO is on  */
    CLOCK_SetFroOscFreq(kCLOCK_FroOscOut48M);                   /*!< Set up FRO freq */
    CLOCK_SetFroOutClkSrc(kCLOCK_FroSrcFroOsc);                 /*!< Set FRO clock source */
    CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcFro);                  /*!< select fro for main clock */
    CLOCK_Select(kWKT_Clk_From_Fro);                            /*!< select FRO for WKT */
    CLOCK_SetCoreSysClkDiv(1U);
    /*!< Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKFRO48M_CORE_CLOCK;
}

/*******************************************************************************
 ******************** Configuration BOARD_BootClockFRO60M **********************
 ******************************************************************************/
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockFRO60M
called_from_default_init: true
outputs:
- {id: FROHF_clock.outFreq, value: 60 MHz}
- {id: System_clock.outFreq, value: 60 MHz}
- {id: WKT_clock.outFreq, value: 60 MHz}
settings:
- {id: SYSCON.ADCCLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.CLKOUTSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FRG0CLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FRG0_DIV.scale, value: '320'}
- {id: SYSCON.FRG1CLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FRG1_DIV.scale, value: '320'}
- {id: SYSCON.FRO_DIRECT.sel, value: SYSCON.fro_osc}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/*******************************************************************************
 * Variables for BOARD_BootClockFRO60M configuration
 ******************************************************************************/
/*******************************************************************************
 * Code for BOARD_BootClockFRO60M configuration
 ******************************************************************************/
void BOARD_BootClockFRO60M(void)
{
    /*!< Set up the clock sources */
    /*!< Set up FRO */
    POWER_DisablePD(kPDRUNCFG_PD_FRO_OUT);                      /*!< Ensure FRO is on  */
    POWER_DisablePD(kPDRUNCFG_PD_FRO);                          /*!< Ensure FRO is on  */
    CLOCK_SetFroOscFreq(kCLOCK_FroOscOut60M);                   /*!< Set up FRO freq */
    CLOCK_SetFroOutClkSrc(kCLOCK_FroSrcFroOsc);                 /*!< Set FRO clock source */
    CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcFro);                  /*!< select fro for main clock */
    CLOCK_Select(kWKT_Clk_From_Fro);                            /*!< select FRO for WKT */
    CLOCK_SetCoreSysClkDiv(1U);
    /*!< Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKFRO60M_CORE_CLOCK;
}

/*******************************************************************************
 ******************** Configuration BOARD_BootClockPll48M **********************
 ******************************************************************************/
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockPll48M
outputs:
- {id: FROHF_clock.outFreq, value: 48 MHz}
- {id: SYSPLL_clock.outFreq, value: 48 MHz}
- {id: System_clock.outFreq, value: 48 MHz}
- {id: WKT_clock.outFreq, value: 24 MHz}
settings:
- {id: SYSCON.ADCCLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.CLKOUTSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FRG0CLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FRG1CLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.MAINCLKPLLSEL.sel, value: SYSCON.PLL}
- {id: SYSCON.M_MULT.scale, value: '2'}
- {id: SYSCON_PDRUNCFG0_PDEN_PLL_CFG, value: Power_up}
sources:
- {id: SYSCON.fro_osc.outFreq, value: 48 MHz}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/*******************************************************************************
 * Variables for BOARD_BootClockPll48M configuration
 ******************************************************************************/
/*******************************************************************************
 * Code for BOARD_BootClockPll48M configuration
 ******************************************************************************/
void BOARD_BootClockPll48M(void)
{
    /*!< Set up the clock sources */
    /*!< Set up FRO */
    POWER_DisablePD(kPDRUNCFG_PD_FRO_OUT);                      /*!< Ensure FRO is on  */
    POWER_DisablePD(kPDRUNCFG_PD_FRO);                          /*!< Ensure FRO is on  */
    CLOCK_SetFroOscFreq(kCLOCK_FroOscOut48M);                   /*!< Set up FRO freq */
    CLOCK_SetFroOutClkSrc(kCLOCK_FroSrcFroOscDiv);              /*!< Set FRO clock source */
    clock_sys_pll_t config;
    config.src = kCLOCK_SysPllSrcFRO;                           /*!< select FRO for SYSPLL */
    config.targetFreq = 48000000U;                              /*!< set pll target freq */
    CLOCK_InitSystemPll(&config);                               /*!< set parameters */
    CLOCK_SetClkDivider(kCLOCK_DivPllClk, 1U);                  /*!< set SYSPLL div */
    CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcSysPll);               /*!< select syspll for main clock */
    CLOCK_Select(kWKT_Clk_From_Fro);                            /*!< select FRO for WKT */
    CLOCK_SetCoreSysClkDiv(1U);
    /*!< Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKPLL48M_CORE_CLOCK;
}

