/*
 * Copyright  2018,2019 NXP
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
product: Clocks v7.0
processor: LPC804
package_id: LPC804M101JDH24
mcu_data: ksdk2_0
processor_version: 0.7.1
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
    BOARD_BootClockFRO30M();
}

/*******************************************************************************
 ******************** Configuration BOARD_BootClockFRO18M **********************
 ******************************************************************************/
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockFRO18M
outputs:
- {id: FROHF_clock.outFreq, value: 18 MHz}
- {id: LowPower_clock.outFreq, value: 1 MHz}
- {id: System_clock.outFreq, value: 9 MHz}
- {id: WWDT_clock.outFreq, value: 1 MHz}
- {id: divto750k_clock.outFreq, value: 750 kHz}
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
    POWER_DisablePD(kPDRUNCFG_PD_FRO_OUT);     /*!< Ensure FRO OUT is on  */
    POWER_DisablePD(kPDRUNCFG_PD_FRO);         /*!< Ensure FRO is on  */
    CLOCK_SetFroOscFreq(kCLOCK_FroOscOut18M);  /*!< Set up FRO freq */
    POWER_DisablePD(kPDRUNCFG_PD_LPOSC);       /*!< Ensure LPOSC is on */
    CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcFro); /*!< select fro for main clock */
    CLOCK_Select(kFRG0_Clk_From_Fro);          /*!< select fro for frg0 */
    CLOCK_SetFRG0ClkFreq(9000000U);            /*!< select frg0 freq */
    CLOCK_Select(kCLKOUT_From_Fro);            /*!< select FRO for CLKOUT */
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
- {id: FROHF_clock.outFreq, value: 24 MHz}
- {id: LowPower_clock.outFreq, value: 1 MHz}
- {id: System_clock.outFreq, value: 12 MHz}
- {id: WWDT_clock.outFreq, value: 1 MHz}
- {id: divto750k_clock.outFreq, value: 750 kHz}
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
    POWER_DisablePD(kPDRUNCFG_PD_FRO_OUT);     /*!< Ensure FRO OUT is on  */
    POWER_DisablePD(kPDRUNCFG_PD_FRO);         /*!< Ensure FRO is on  */
    CLOCK_SetFroOscFreq(kCLOCK_FroOscOut24M);  /*!< Set up FRO freq */
    POWER_DisablePD(kPDRUNCFG_PD_LPOSC);       /*!< Ensure LPOSC is on */
    CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcFro); /*!< select fro for main clock */
    CLOCK_Select(kFRG0_Clk_From_Fro);          /*!< select fro for frg0 */
    CLOCK_SetFRG0ClkFreq(12000000U);           /*!< select frg0 freq */
    CLOCK_Select(kCLKOUT_From_Fro);            /*!< select FRO for CLKOUT */
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
called_from_default_init: true
outputs:
- {id: FROHF_clock.outFreq, value: 30 MHz}
- {id: LowPower_clock.outFreq, value: 1 MHz}
- {id: System_clock.outFreq, value: 15 MHz}
- {id: WWDT_clock.outFreq, value: 1 MHz}
- {id: divto750k_clock.outFreq, value: 750 kHz}
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
    POWER_DisablePD(kPDRUNCFG_PD_FRO_OUT);     /*!< Ensure FRO OUT is on  */
    POWER_DisablePD(kPDRUNCFG_PD_FRO);         /*!< Ensure FRO is on  */
    CLOCK_SetFroOscFreq(kCLOCK_FroOscOut30M);  /*!< Set up FRO freq */
    POWER_DisablePD(kPDRUNCFG_PD_LPOSC);       /*!< Ensure LPOSC is on */
    CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcFro); /*!< select fro for main clock */
    CLOCK_Select(kFRG0_Clk_From_Fro);          /*!< select fro for frg0 */
    CLOCK_SetFRG0ClkFreq(15000000U);           /*!< select frg0 freq */
    CLOCK_Select(kCLKOUT_From_Fro);            /*!< select FRO for CLKOUT */
    CLOCK_Select(kADC_Clk_From_Fro);           /*!< select FRO for ADC */
    CLOCK_SetCoreSysClkDiv(1U);
    /*!< Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKFRO30M_CORE_CLOCK;
}
