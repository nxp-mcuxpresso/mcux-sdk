/*
 * Copyright 2018 NXP.
 * All rights reserved.
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
product: Clocks v4.1
processor: LPC804
package_id: LPC804M101JDH24
mcu_data: ksdk2_0
processor_version: 4.0.1
board: LPCXpresso804
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
/* System clock frequency. */
extern uint32_t SystemCoreClock;

/*******************************************************************************
 ************************ BOARD_InitBootClocks function ************************
 ******************************************************************************/
void BOARD_InitBootClocks(void)
{
    BOARD_BootClockFRO18M();
}

/*******************************************************************************
 ******************** Configuration BOARD_BootClockFRO18M **********************
 ******************************************************************************/
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockFRO18M
called_from_default_init: true
outputs:
- {id: CAPT_clock.outFreq, value: 4.5 MHz}
- {id: FROHF_clock.outFreq, value: 18 MHz}
- {id: System_clock.outFreq, value: 9 MHz}
sources:
- {id: SYSCON.fro_osc.outFreq, value: 18 MHz}
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
    POWER_DisablePD(kPDRUNCFG_PD_FRO_OUT);     /*!< Ensure FRO is on  */
    POWER_DisablePD(kPDRUNCFG_PD_FRO);         /*!< Ensure FRO is on  */
    CLOCK_SetFroOscFreq(kCLOCK_FroOscOut18M);  /*!< Set up FRO freq */
    CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcFro); /*!< select fro for main clock */
    CLOCK_Select(kFRG0_Clk_From_Fro);          /*!< select fro for frg0 */
    CLOCK_SetFRG0ClkFreq(9000000U);            /*!< select frg0 freq */
    CLOCK_Select(kCLKOUT_From_Fro);            /*!< select FRO for CLKOUT */
    CLOCK_Select(kCAPT_Clk_From_Fro_Div);      /*!< select FRO_DIV for CAPT */
    CLOCK_Select(kADC_Clk_From_Fro);           /*!< select FRO for ADC */
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
- {id: CAPT_clock.outFreq, value: 6 MHz}
- {id: FROHF_clock.outFreq, value: 24 MHz}
- {id: System_clock.outFreq, value: 12 MHz}
sources:
- {id: SYSCON.fro_osc.outFreq, value: 24 MHz}
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
    POWER_DisablePD(kPDRUNCFG_PD_FRO_OUT);     /*!< Ensure FRO is on  */
    POWER_DisablePD(kPDRUNCFG_PD_FRO);         /*!< Ensure FRO is on  */
    CLOCK_SetFroOscFreq(kCLOCK_FroOscOut24M);  /*!< Set up FRO freq */
    CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcFro); /*!< select fro for main clock */
    CLOCK_Select(kFRG0_Clk_From_Fro);          /*!< select fro for frg0 */
    CLOCK_SetFRG0ClkFreq(12000000U);           /*!< select frg0 freq */
    CLOCK_Select(kCLKOUT_From_Fro);            /*!< select FRO for CLKOUT */
    CLOCK_Select(kCAPT_Clk_From_Fro_Div);      /*!< select FRO_DIV for CAPT */
    CLOCK_Select(kADC_Clk_From_Fro);           /*!< select FRO for ADC */
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
- {id: CAPT_clock.outFreq, value: 7.5 MHz}
- {id: FROHF_clock.outFreq, value: 30 MHz}
- {id: System_clock.outFreq, value: 15 MHz}
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
    POWER_DisablePD(kPDRUNCFG_PD_FRO_OUT);     /*!< Ensure FRO is on  */
    POWER_DisablePD(kPDRUNCFG_PD_FRO);         /*!< Ensure FRO is on  */
    CLOCK_SetFroOscFreq(kCLOCK_FroOscOut30M);  /*!< Set up FRO freq */
    CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcFro); /*!< select fro for main clock */
    CLOCK_Select(kFRG0_Clk_From_Fro);          /*!< select fro for frg0 */
    CLOCK_SetFRG0ClkFreq(15000000U);           /*!< select frg0 freq */
    CLOCK_Select(kCLKOUT_From_Fro);            /*!< select FRO for CLKOUT */
    CLOCK_Select(kCAPT_Clk_From_Fro_Div);      /*!< select FRO_DIV for CAPT */
    CLOCK_Select(kADC_Clk_From_Fro);           /*!< select FRO for ADC */
    CLOCK_SetCoreSysClkDiv(1U);
    /*!< Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKFRO30M_CORE_CLOCK;
}
