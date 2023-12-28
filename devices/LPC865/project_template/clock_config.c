/*
 * Copyright 2023 NXP
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
product: Clocks v12.0
processor: LPC865
package_id: LPC865M201JBD64
mcu_data: ksdk2_0
processor_version: 0.14.4
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
- {id: FROHF_clock.outFreq, value: 60 MHz}
- {id: System_clock.outFreq, value: 30 MHz}
- {id: WKT_clock.outFreq, value: 30 MHz}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/*******************************************************************************
 * Variables for BOARD_BootClockRUN configuration
 ******************************************************************************/
/*******************************************************************************
 * Code for BOARD_BootClockRUN configuration
 ******************************************************************************/
void BOARD_BootClockRUN(void)
{
    /*!< Set up the clock sources */
    /*!< Set up FRO */
    POWER_DisablePD(kPDRUNCFG_PD_FRO_OUT);                      /*!< Ensure FRO is on  */
    POWER_DisablePD(kPDRUNCFG_PD_FRO);                          /*!< Ensure FRO is on  */
    CLOCK_SetFroOscFreq(kCLOCK_FroOscOut60M);                   /*!< Set up FRO freq */
    CLOCK_SetFroOutClkSrc(kCLOCK_FroSrcFroOscDiv);              /*!< Set FRO clock source */
    CLOCK_Select(kFRG0_Clk_From_Fro);                           /*!< select fro for frg0 */
    CLOCK_SetFRG0ClkFreq(30000000U);                            /*!< select frg0 freq */
    CLOCK_Select(kFRG1_Clk_From_Fro);                           /*!< select fro for frg1 */
    CLOCK_SetFRG1ClkFreq(30000000U);                            /*!< select frg1 freq */
    CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcFro);                  /*!< select fro for main clock */
    CLOCK_Select(kCLKOUT_From_Fro);                             /*!< select FRO for CLKOUT */
    CLOCK_Select(kADC_Clk_From_Fro);                            /*!< select FRO for ADC */
    CLOCK_Select(kWKT_Clk_From_Fro);                            /*!< select FRO for WKT */
    CLOCK_SetCoreSysClkDiv(1U);
    /*!< Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKRUN_CORE_CLOCK;
}

