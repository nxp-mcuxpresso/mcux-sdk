/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * How to setup clock using clock driver functions:
 *
 * 1. CLOCK_SetSimSafeDivs, to make sure core clock, bus clock, flexbus clock
 *    and flash clock are in allowed range during clock mode switch.
 *
 * 2. Call CLOCK_Osc0Init to setup OSC clock, if it is used in target mode.
 *
 * 3. Set MCG configuration, MCG includes three parts: FLL clock, PLL clock and
 *    internal reference clock(MCGIRCLK). Follow the steps to setup:
 *
 *    1). Call CLOCK_BootToXxxMode to set MCG to target mode.
 *
 *    2). If target mode is FBI/BLPI/PBI mode, the MCGIRCLK has been configured
 *        correctly. For other modes, need to call CLOCK_SetInternalRefClkConfig
 *        explicitly to setup MCGIRCLK.
 *
 *    3). Don't need to configure FLL explicitly, because if target mode is FLL
 *        mode, then FLL has been configured by the function CLOCK_BootToXxxMode,
 *        if the target mode is not FLL mode, the FLL is disabled.
 *
 *    4). If target mode is PEE/PBE/PEI/PBI mode, then the related PLL has been
 *        setup by CLOCK_BootToXxxMode. In FBE/FBI/FEE/FBE mode, the PLL could
 *        be enabled independently, call CLOCK_EnablePll0 explicitly in this case.
 *
 * 4. Call CLOCK_SetSimConfig to set the clock configuration in SIM.
 */

/* TEXT BELOW IS USED AS SETTING FOR THE CLOCKS TOOL *****************************
!!ClocksProfile
product: Clocks v1.0
processor: MKV58F1M0xxx24
package_id: MKV58F1M0VLQ24
mcu_data: ksdk2_0
processor_version: 1.1.0
board: TWR-KV58F220M
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE CLOCKS TOOL **/

#include "fsl_smc.h"
#include "clock_config.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MCG_PLL_DISABLE 0U             /*!< MCGPLLCLK disabled */
#define OSC_CAP0P 0U                   /*!< Oscillator 0pF capacitor load */
#define SIM_OSC32KSEL_LPO_CLK 3U       /*!< OSC32KSEL select: LPO clock */
#define SIM_PLLFLLSEL_MCGFLLCLK_CLK 0U /*!< PLLFLL select: MCGFLLCLK clock */
#define SIM_PLLFLLSEL_MCGPLLCLK_CLK 1U /*!< PLLFLL select: MCGPLLCLK clock */

#define SIM_CLKDIV1_RUN_MODE_MAX_CORE_DIV 1U /*!< SIM CLKDIV1 maximum run mode core/system divider configurations */
#define SIM_CLKDIV1_RUN_MODE_MAX_FAST_PERIPHERAL_DIV 3U /*!< SIM CLKDIV1 maximum run mode bus divider configuration */
#define SIM_CLKDIV1_RUN_MODE_MAX_FLEXBUS_DIV 3U   /*!< SIM CLKDIV1 maximum run mode flexbus divider configurations */
#define SIM_CLKDIV1_RUN_MODE_MAX_BUS_FLASH_DIV 9U /*!< SIM CLKDIV1 maximum run mode flash divider configurations */

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
 * Function Name : CLOCK_CONFIG_SetSimSafeDivs
 * Description   : This function sets the system clock dividers in SIM to safe
 * value.
 *
 *END**************************************************************************/
static void CLOCK_CONFIG_SetSimSafeDivs(void)
{
    SIM->CLKDIV1 = 0x01170000U;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_CONFIG_SetFllExtRefDiv
 * Description   : Configure FLL external reference divider (FRDIV).
 * Param frdiv   : The value to set FRDIV.
 *
 *END**************************************************************************/
static void CLOCK_CONFIG_SetFllExtRefDiv(uint8_t frdiv)
{
    MCG->C1 = ((MCG->C1 & ~MCG_C1_FRDIV_MASK) | MCG_C1_FRDIV(frdiv));
}

/*******************************************************************************
 ********************** Configuration BOARD_BootClockRUN ***********************
 ******************************************************************************/
/* TEXT BELOW IS USED AS SETTING FOR THE CLOCKS TOOL *****************************
!!Configuration
name: BOARD_BootClockRUN
outputs:
- {id: Bus_clock.outFreq, value: 72 MHz}
- {id: Core_clock.outFreq, value: 144 MHz}
- {id: ERCLK32K.outFreq, value: 1 kHz}
- {id: Flash_clock.outFreq, value: 14.4 MHz}
- {id: FlexBus_clock.outFreq, value: 36 MHz}
- {id: LPO_clock.outFreq, value: 1 kHz}
- {id: MCGFFCLK.outFreq, value: 1.5 MHz}
- {id: MCGIRCLK.outFreq, value: 32.768 kHz}
- {id: OSCERCLK.outFreq, value: 48 MHz}
- {id: OSCERCLK_UNDIV.outFreq, value: 48 MHz}
- {id: PLLFLLCLK.outFreq, value: 144 MHz}
- {id: System_clock.outFreq, value: 144 MHz}
settings:
- {id: MCGMode, value: PEE}
- {id: MCG.FCRDIV.scale, value: '1'}
- {id: MCG.FLL_mul.scale, value: '2560', locked: true}
- {id: MCG.FRDIV.scale, value: '32'}
- {id: MCG.IREFS.sel, value: MCG.FRDIV}
- {id: MCG.PLLS.sel, value: MCG.PLL_DIV2}
- {id: MCG.PRDIV.scale, value: '4', locked: true}
- {id: MCG.VDIV.scale, value: '24', locked: true}
- {id: MCG_C1_IRCLKEN_CFG, value: Enabled}
- {id: MCG_C2_RANGE0_CFG, value: Very_high}
- {id: MCG_C2_RANGE0_FRDIV_CFG, value: Very_high}
- {id: OSC_CR_ERCLKEN_CFG, value: Enabled}
- {id: OSC_CR_ERCLKEN_UNDIV_CFG, value: Enabled}
- {id: SIM.OSC32KSEL.sel, value: PMC.LPOCLK}
- {id: SIM.OUTDIV2.scale, value: '2', locked: true}
- {id: SIM.OUTDIV3.scale, value: '4', locked: true}
- {id: SIM.OUTDIV4.scale, value: '10', locked: true}
- {id: SIM.PLLFLLSEL.sel, value: MCG.MCGPLLCLK}
- {id: SIM.RMIICLKSEL.sel, value: SIM.ENET_1588_CLK_EXT}
- {id: SIM.TIMESRCSEL.sel, value: SIM.ENET_1588_CLK_EXT}
sources:
- {id: OSC.OSC.outFreq, value: 48 MHz, enabled: true}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE CLOCKS TOOL **/

/*******************************************************************************
 * Variables for BOARD_BootClockRUN configuration
 ******************************************************************************/
const mcg_config_t mcgConfig_BOARD_BootClockRUN = {
    .mcgMode         = kMCG_ModePEE,      /* PEE - PLL Engaged External */
    .irclkEnableMode = kMCG_IrclkEnable,  /* MCGIRCLK enabled, MCGIRCLK disabled in STOP mode */
    .ircs            = kMCG_IrcSlow,      /* Slow internal reference clock selected */
    .fcrdiv          = 0x0U,              /* Fast IRC divider: divided by 1 */
    .frdiv           = 0x0U,              /* FLL reference clock divider: divided by 32 */
    .drs             = kMCG_DrsHigh,      /* High frequency range */
    .dmx32           = kMCG_Dmx32Default, /* DCO has a default range of 25% */
    .pll0Config =
        {
            .enableMode = MCG_PLL_DISABLE, /* MCGPLLCLK disabled */
            .prdiv      = 0x3U,            /* PLL Reference divider: divided by 4 */
            .vdiv       = 0x8U,            /* VCO divider: multiplied by 24 */
        },
};
const sim_clock_config_t simConfig_BOARD_BootClockRUN = {
    .pllFllSel = SIM_PLLFLLSEL_MCGPLLCLK_CLK, /* PLLFLL select: MCGPLLCLK clock */
    .er32kSrc  = SIM_OSC32KSEL_LPO_CLK,       /* OSC32KSEL select: LPO clock */
    .clkdiv1   = 0x01150000U,                 /* SIM_CLKDIV1 - OUTDIV1: /1, OUTDIV2: /2, OUTDIV3: /2, OUTDIV4: /6 */
};
const osc_config_t oscConfig_BOARD_BootClockRUN = {
    .freq        = 50000000U,    /* Oscillator frequency: 48000000Hz */
    .capLoad     = (OSC_CAP0P),  /* Oscillator capacity load: 0pF */
    .workMode    = kOSC_ModeExt, /* Use external clock */
    .oscerConfig = {
        .enableMode =
            kOSC_ErClkEnable, /* Enable external reference clock, disable external reference clock in STOP mode */
        .erclkDiv = 0,        /* Divider for OSCERCLK: divided by 1 */
    }};

/*******************************************************************************
 * Code for BOARD_BootClockRUN configuration
 ******************************************************************************/
void BOARD_BootClockRUN(void)
{
    /* Set the system clock dividers in SIM to safe value. */
    CLOCK_CONFIG_SetSimSafeDivs();
    /* Initializes OSC0 according to board configuration. */
    CLOCK_InitOsc0(&oscConfig_BOARD_BootClockRUN);
    CLOCK_SetXtal0Freq(oscConfig_BOARD_BootClockRUN.freq);
    /* Configure FLL external reference divider (FRDIV). */
    CLOCK_CONFIG_SetFllExtRefDiv(mcgConfig_BOARD_BootClockRUN.frdiv);
    /* Set MCG to PEE mode. */
    CLOCK_BootToPeeMode(kMCG_OscselOsc, kMCG_PllClkSelPll0, &mcgConfig_BOARD_BootClockRUN.pll0Config);
    /* Configure the Internal Reference clock (MCGIRCLK). */
    CLOCK_SetInternalRefClkConfig(mcgConfig_BOARD_BootClockRUN.irclkEnableMode, mcgConfig_BOARD_BootClockRUN.ircs,
                                  mcgConfig_BOARD_BootClockRUN.fcrdiv);
    /* Set the clock configuration in SIM module. */
    CLOCK_SetSimConfig(&simConfig_BOARD_BootClockRUN);
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
- {id: Bus_clock.outFreq, value: 4 MHz}
- {id: Core_clock.outFreq, value: 4 MHz}
- {id: ERCLK32K.outFreq, value: 1 kHz}
- {id: Flash_clock.outFreq, value: 500 kHz}
- {id: FlexBus_clock.outFreq, value: 4 MHz}
- {id: LPO_clock.outFreq, value: 1 kHz}
- {id: MCGIRCLK.outFreq, value: 4 MHz}
- {id: System_clock.outFreq, value: 4 MHz, locked: true, accuracy: '0.001'}
settings:
- {id: MCGMode, value: BLPI}
- {id: powerMode, value: VLPR}
- {id: MCG.CLKS.sel, value: MCG.IRCS}
- {id: MCG.FCRDIV.scale, value: '1'}
- {id: MCG.FRDIV.scale, value: '32'}
- {id: MCG.IRCS.sel, value: MCG.FCRDIV}
- {id: MCG.PRDIV.scale, value: '4'}
- {id: MCG.VDIV.scale, value: '32'}
- {id: MCG_C1_IRCLKEN_CFG, value: Enabled}
- {id: MCG_C2_RANGE0_CFG, value: High}
- {id: MCG_C2_RANGE0_FRDIV_CFG, value: High}
- {id: OSC_CR_ERCLKEN_CFG, value: Enabled}
- {id: OSC_CR_ERCLKEN_UNDIV_CFG, value: Enabled}
- {id: SIM.OSC32KSEL.sel, value: PMC.LPOCLK}
- {id: SIM.OUTDIV4.scale, value: '8'}
- {id: SIM.TIMESRCSEL.sel, value: OSC.OSCERCLK}
- {id: SIM.TRACECLKSEL.sel, value: MCG.MCGOUTCLK}
sources:
- {id: OSC.OSC.outFreq, value: 50 MHz}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE CLOCKS TOOL **/

/*******************************************************************************
 * Variables for BOARD_BootClockVLPR configuration
 ******************************************************************************/
const mcg_config_t mcgConfig_BOARD_BootClockVLPR = {
    .mcgMode         = kMCG_ModeBLPI,     /* BLPI - Bypassed Low Power Internal */
    .irclkEnableMode = kMCG_IrclkEnable,  /* MCGIRCLK enabled, MCGIRCLK disabled in STOP mode */
    .ircs            = kMCG_IrcFast,      /* Fast internal reference clock selected */
    .fcrdiv          = 0x0U,              /* Fast IRC divider: divided by 1 */
    .frdiv           = 0x0U,              /* FLL reference clock divider: divided by 32 */
    .drs             = kMCG_DrsLow,       /* Low frequency range */
    .dmx32           = kMCG_Dmx32Default, /* DCO has a default range of 25% */
    .pll0Config =
        {
            .enableMode = MCG_PLL_DISABLE, /* MCGPLLCLK disabled */
            .prdiv      = 0x3U,            /* PLL Reference divider: divided by 4 */
            .vdiv       = 0x10U,           /* VCO divider: multiplied by 32 */
        },
};
const sim_clock_config_t simConfig_BOARD_BootClockVLPR = {
    .pllFllSel = SIM_PLLFLLSEL_MCGFLLCLK_CLK, /* PLLFLL select: MCGFLLCLK clock */
    .er32kSrc  = SIM_OSC32KSEL_LPO_CLK,       /* OSC32KSEL select: LPO clock */
    .clkdiv1   = 0x70000U,                    /* SIM_CLKDIV1 - OUTDIV1: /1, OUTDIV2: /1, OUTDIV3: /1, OUTDIV4: /8 */
};
const osc_config_t oscConfig_BOARD_BootClockVLPR = {
    .freq        = 0U,           /* Oscillator frequency: 0Hz */
    .capLoad     = (OSC_CAP0P),  /* Oscillator capacity load: 0pF */
    .workMode    = kOSC_ModeExt, /* Use external clock */
    .oscerConfig = {
        .enableMode =
            kOSC_ErClkEnable, /* Enable external reference clock, disable external reference clock in STOP mode */
        .erclkDiv = 0,        /* Divider for OSCERCLK: divided by 1 */
    }};

/*******************************************************************************
 * Code for BOARD_BootClockVLPR configuration
 ******************************************************************************/
void BOARD_BootClockVLPR(void)
{
    /* Set the system clock dividers in SIM to safe value. */
    CLOCK_CONFIG_SetSimSafeDivs();
    /* Set MCG to BLPI mode. */
    CLOCK_BootToBlpiMode(mcgConfig_BOARD_BootClockVLPR.fcrdiv, mcgConfig_BOARD_BootClockVLPR.ircs,
                         mcgConfig_BOARD_BootClockVLPR.irclkEnableMode);
    /* Set the clock configuration in SIM module. */
    CLOCK_SetSimConfig(&simConfig_BOARD_BootClockVLPR);
    /* Set VLPR power mode. */
    SMC_SetPowerModeProtection(SMC, kSMC_AllowPowerModeAll);
#if (defined(FSL_FEATURE_SMC_HAS_LPWUI) && FSL_FEATURE_SMC_HAS_LPWUI)
    SMC_SetPowerModeVlpr(SMC, false);
#else
    SMC_SetPowerModeVlpr(SMC);
#endif
    while (SMC_GetPowerModeState(SMC) != kSMC_PowerStateVlpr)
    {
    }
    /* Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKVLPR_CORE_CLOCK;
}

/*******************************************************************************
 ********************* Configuration BOARD_BootClockHSRUN **********************
 ******************************************************************************/
/* TEXT BELOW IS USED AS SETTING FOR THE CLOCKS TOOL *****************************
!!Configuration
name: BOARD_BootClockHSRUN
outputs:
- {id: Bus_clock.outFreq, value: 114 MHz}
- {id: Core_clock.outFreq, value: 228 MHz}
- {id: ERCLK32K.outFreq, value: 1 kHz}
- {id: Flash_clock.outFreq, value: 22.8 MHz}
- {id: FlexBus_clock.outFreq, value: 57 MHz}
- {id: LPO_clock.outFreq, value: 1 kHz}
- {id: MCGFFCLK.outFreq, value: 1.5 MHz}
- {id: MCGIRCLK.outFreq, value: 32.768 kHz}
- {id: OSCERCLK.outFreq, value: 48 MHz}
- {id: OSCERCLK_UNDIV.outFreq, value: 48 MHz}
- {id: PLLFLLCLK.outFreq, value: 228 MHz}
- {id: System_clock.outFreq, value: 228 MHz}
settings:
- {id: MCGMode, value: PEE}
- {id: powerMode, value: HSRUN}
- {id: MCG.FCRDIV.scale, value: '1', locked: true}
- {id: MCG.FRDIV.scale, value: '32'}
- {id: MCG.IREFS.sel, value: MCG.FRDIV}
- {id: MCG.PLLS.sel, value: MCG.PLL_DIV2}
- {id: MCG.PRDIV.scale, value: '4', locked: true}
- {id: MCG.VDIV.scale, value: '38', locked: true}
- {id: MCG_C1_IRCLKEN_CFG, value: Enabled}
- {id: MCG_C2_RANGE0_CFG, value: Very_high}
- {id: MCG_C2_RANGE0_FRDIV_CFG, value: Very_high}
- {id: OSC_CR_ERCLKEN_CFG, value: Enabled}
- {id: OSC_CR_ERCLKEN_UNDIV_CFG, value: Enabled}
- {id: SIM.OSC32KSEL.sel, value: PMC.LPOCLK}
- {id: SIM.OUTDIV2.scale, value: '2', locked: true}
- {id: SIM.OUTDIV3.scale, value: '4', locked: true}
- {id: SIM.OUTDIV4.scale, value: '10', locked: true}
- {id: SIM.PLLFLLSEL.sel, value: MCG.MCGPLLCLK}
sources:
- {id: OSC.OSC.outFreq, value: 48 MHz, enabled: true}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE CLOCKS TOOL **/

/*******************************************************************************
 * Variables for BOARD_BootClockHSRUN configuration
 ******************************************************************************/
const mcg_config_t mcgConfig_BOARD_BootClockHSRUN = {
    .mcgMode         = kMCG_ModePEE,      /* PEE - PLL Engaged External */
    .irclkEnableMode = kMCG_IrclkEnable,  /* MCGIRCLK enabled, MCGIRCLK disabled in STOP mode */
    .ircs            = kMCG_IrcSlow,      /* Slow internal reference clock selected */
    .fcrdiv          = 0x0U,              /* Fast IRC divider: divided by 1 */
    .frdiv           = 0x0U,              /* FLL reference clock divider: divided by 32 */
    .drs             = kMCG_DrsLow,       /* Low frequency range */
    .dmx32           = kMCG_Dmx32Default, /* DCO has a default range of 25% */
    .pll0Config =
        {
            .enableMode = MCG_PLL_DISABLE, /* MCGPLLCLK disabled */
            .prdiv      = 0x3U,            /* PLL Reference divider: divided by 4 */
            .vdiv       = 0x16U,           /* VCO divider: multiplied by 38 */
        },
};
const sim_clock_config_t simConfig_BOARD_BootClockHSRUN = {
    .pllFllSel = SIM_PLLFLLSEL_MCGPLLCLK_CLK, /* PLLFLL select: MCGPLLCLK clock */
    .er32kSrc  = SIM_OSC32KSEL_LPO_CLK,       /* OSC32KSEL select: LPO clock */
    .clkdiv1   = 0x1390000U,                  /* SIM_CLKDIV1 - OUTDIV1: /1, OUTDIV2: /2, OUTDIV3: /4, OUTDIV4: /10 */
};
const osc_config_t oscConfig_BOARD_BootClockHSRUN = {
    .freq        = 50000000U,    /* Oscillator frequency: 48000000Hz */
    .capLoad     = (OSC_CAP0P),  /* Oscillator capacity load: 0pF */
    .workMode    = kOSC_ModeExt, /* Use external clock */
    .oscerConfig = {
        .enableMode =
            kOSC_ErClkEnable, /* Enable external reference clock, disable external reference clock in STOP mode */
        .erclkDiv = 0,        /* Divider for OSCERCLK: divided by 1 */
    }};

/*******************************************************************************
 * Code for BOARD_BootClockHSRUN configuration
 ******************************************************************************/
void BOARD_BootClockHSRUN(void)
{
    /* In HSRUN mode, the maximum allowable change in frequency of the system/bus/core/flash is
     * restricted to x2, to follow this restriction, enter HSRUN mode should follow:
     * 1.set CLKDIV1 to safe divider value.
     * 2.set the PLL or FLL output target frequency for HSRUN mode.
     * 3.switch to HSRUN mode.
     * 4.switch to HSRUN mode target requency value.
     */

    /* Set the system clock dividers in SIM to safe value. */
    CLOCK_SetOutDiv(SIM_CLKDIV1_RUN_MODE_MAX_CORE_DIV, SIM_CLKDIV1_RUN_MODE_MAX_FAST_PERIPHERAL_DIV,
                    SIM_CLKDIV1_RUN_MODE_MAX_FLEXBUS_DIV, SIM_CLKDIV1_RUN_MODE_MAX_BUS_FLASH_DIV);

    /* Initializes OSC0 according to board configuration. */
    CLOCK_InitOsc0(&oscConfig_BOARD_BootClockHSRUN);
    CLOCK_SetXtal0Freq(oscConfig_BOARD_BootClockHSRUN.freq);
    /* Configure FLL external reference divider (FRDIV). */
    CLOCK_CONFIG_SetFllExtRefDiv(mcgConfig_BOARD_BootClockHSRUN.frdiv);
    /* Set MCG to PEE mode. */
    CLOCK_BootToPeeMode(kMCG_OscselOsc, kMCG_PllClkSelPll0, &mcgConfig_BOARD_BootClockHSRUN.pll0Config);
    /* Configure the Internal Reference clock (MCGIRCLK). */
    CLOCK_SetInternalRefClkConfig(mcgConfig_BOARD_BootClockHSRUN.irclkEnableMode, mcgConfig_BOARD_BootClockHSRUN.ircs,
                                  mcgConfig_BOARD_BootClockHSRUN.fcrdiv);

    /* Set HSRUN power mode */
    SMC_SetPowerModeProtection(SMC, kSMC_AllowPowerModeAll);
    SMC_SetPowerModeHsrun(SMC);
    while (SMC_GetPowerModeState(SMC) != kSMC_PowerStateHsrun)
    {
    }

    /* Set the clock configuration in SIM module. */
    CLOCK_SetSimConfig(&simConfig_BOARD_BootClockHSRUN);
    /* Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKHSRUN_CORE_CLOCK;
}
