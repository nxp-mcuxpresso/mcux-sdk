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
processor: LPC824
package_id: LPC824M201JHI33
mcu_data: ksdk2_0
processor_version: 0.7.1
board: LPCXpresso824
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
    BOARD_BootClockIRC12M();
}

/*******************************************************************************
 ******************** Configuration BOARD_BootClockIRC12M **********************
 ******************************************************************************/
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockIRC12M
called_from_default_init: true
outputs:
- {id: ADC_clock.outFreq, value: 12 MHz}
- {id: I2C0_clock.outFreq, value: 12 MHz}
- {id: I2C1_clock.outFreq, value: 12 MHz}
- {id: I2C2_clock.outFreq, value: 12 MHz}
- {id: I2C3_clock.outFreq, value: 12 MHz}
- {id: LowPower_clock.outFreq, value: 10 kHz}
- {id: SPI0_clock.outFreq, value: 12 MHz}
- {id: SPI1_clock.outFreq, value: 12 MHz}
- {id: SYSPLL_clock.outFreq, value: 12 MHz}
- {id: System_clock.outFreq, value: 12 MHz}
- {id: divto750k_clock.outFreq, value: 750 kHz}
settings:
- {id: SYSCON.M_MULT.scale, value: '1', locked: true}
- {id: SYSCON.N_DIV.scale, value: '1', locked: true}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/*******************************************************************************
 * Variables for BOARD_BootClockIRC12M configuration
 ******************************************************************************/
/*******************************************************************************
 * Code for BOARD_BootClockIRC12M configuration
 ******************************************************************************/
void BOARD_BootClockIRC12M(void)
{
    /*!< Set up the clock sources */
    /*!< Set up IRC */
    POWER_DisablePD(kPDRUNCFG_PD_IRC_OUT); /*!< Ensure IRC OUT is on  */
    POWER_DisablePD(kPDRUNCFG_PD_IRC);     /*!< Ensure IRC is on  */
    POWER_DisablePD(kPDRUNCFG_PD_SYSOSC);  /*!< Ensure SYSOSC is on */
    CLOCK_Select(kSYSPLL_From_Irc);        /*!< set IRC to pll select */
    clock_sys_pll_t config;
    config.src        = kCLOCK_SysPllSrcIrc;   /*!< set pll src  */
    config.targetFreq = 12000000U;             /*!< set pll target freq */
    CLOCK_InitSystemPll(&config);              /*!< set parameters */
    CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcIrc); /*!< select irc for main clock */
    CLOCK_Select(kCLKOUT_From_Irc);            /*!< select IRC for CLKOUT */
    CLOCK_SetCoreSysClkDiv(1U);
    /*!< Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKIRC12M_CORE_CLOCK;
}

/*******************************************************************************
 ******************** Configuration BOARD_BootClockPll24M **********************
 ******************************************************************************/
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockPll24M
outputs:
- {id: ADC_clock.outFreq, value: 24 MHz}
- {id: I2C0_clock.outFreq, value: 24 MHz}
- {id: I2C1_clock.outFreq, value: 24 MHz}
- {id: I2C2_clock.outFreq, value: 24 MHz}
- {id: I2C3_clock.outFreq, value: 24 MHz}
- {id: LowPower_clock.outFreq, value: 10 kHz}
- {id: SPI0_clock.outFreq, value: 24 MHz}
- {id: SPI1_clock.outFreq, value: 24 MHz}
- {id: SYSPLL_clock.outFreq, value: 24 MHz}
- {id: System_clock.outFreq, value: 24 MHz}
- {id: divto750k_clock.outFreq, value: 750 kHz}
settings:
- {id: SYSCON.MAINCLKSEL.sel, value: SYSCON.PLL}
- {id: SYSCON.M_MULT.scale, value: '2', locked: true}
- {id: SYSCON.N_DIV.scale, value: '1', locked: true}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/*******************************************************************************
 * Variables for BOARD_BootClockPll24M configuration
 ******************************************************************************/
/*******************************************************************************
 * Code for BOARD_BootClockPll24M configuration
 ******************************************************************************/
void BOARD_BootClockPll24M(void)
{
    /*!< Set up the clock sources */
    /*!< Set up IRC */
    POWER_DisablePD(kPDRUNCFG_PD_IRC_OUT); /*!< Ensure IRC OUT is on  */
    POWER_DisablePD(kPDRUNCFG_PD_IRC);     /*!< Ensure IRC is on  */
    POWER_DisablePD(kPDRUNCFG_PD_SYSOSC);  /*!< Ensure SYSOSC is on */
    CLOCK_Select(kSYSPLL_From_Irc);        /*!< set IRC to pll select */
    clock_sys_pll_t config;
    config.src        = kCLOCK_SysPllSrcIrc;      /*!< set pll src  */
    config.targetFreq = 24000000U;                /*!< set pll target freq */
    CLOCK_InitSystemPll(&config);                 /*!< set parameters */
    CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcSysPll); /*!< select syspll for main clock */
    CLOCK_Select(kCLKOUT_From_Irc);               /*!< select IRC for CLKOUT */
    CLOCK_SetCoreSysClkDiv(1U);
    /*!< Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKPLL24M_CORE_CLOCK;
}
