/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOARD_XTAL0_CLK_HZ 32768U

#define LED_INIT()   LED_RED_INIT(LOGIC_LED_OFF)
#define LED_TOGGLE() LED_RED_TOGGLE()
#define MAX_STEP_NUM 13

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void BOARD_InitOsc0(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

void BOARD_InitOsc0(void)
{
    const osc_config_t oscConfig = {.freq        = BOARD_XTAL0_CLK_HZ,
                                    .capLoad     = 0U,
                                    .workMode    = kOSC_ModeOscLowPower,
                                    .oscerConfig = {
                                        .enableMode = kOSC_ErClkEnable,
#if (defined(FSL_FEATURE_OSC_HAS_EXT_REF_CLOCK_DIVIDER) && FSL_FEATURE_OSC_HAS_EXT_REF_CLOCK_DIVIDER)
                                        .erclkDiv = 0U,
#endif
                                    }};

    CLOCK_InitOsc0(&oscConfig);

    /* Passing the XTAL0 frequency to clock driver. */
    CLOCK_SetXtal0Freq(BOARD_XTAL0_CLK_HZ);
}

/*!
 * @brief Main function
 */
int main(void)
{
    uint32_t volatile i = 0U;
    uint8_t curStep     = 1U;

    /* MCG_Lite configuration for HIRC mode. */
    mcglite_config_t mcgliteConfigHirc;
    mcgliteConfigHirc.outSrc                  = kMCGLITE_ClkSrcHirc;
    mcgliteConfigHirc.irclkEnableMode         = kMCGLITE_IrclkEnable;
    mcgliteConfigHirc.ircs                    = kMCGLITE_Lirc2M;
    mcgliteConfigHirc.fcrdiv                  = kMCGLITE_LircDivBy1;
    mcgliteConfigHirc.lircDiv2                = kMCGLITE_LircDivBy2;
    mcgliteConfigHirc.hircEnableInNotHircMode = false;

    /* MCG_Lite configuration for LIRC2M mode. */
    mcglite_config_t mcgliteConfigLirc2M;
    mcgliteConfigLirc2M.outSrc                  = kMCGLITE_ClkSrcLirc;
    mcgliteConfigLirc2M.irclkEnableMode         = 0U;
    mcgliteConfigLirc2M.ircs                    = kMCGLITE_Lirc2M;
    mcgliteConfigLirc2M.fcrdiv                  = kMCGLITE_LircDivBy1;
    mcgliteConfigLirc2M.lircDiv2                = kMCGLITE_LircDivBy2;
    mcgliteConfigLirc2M.hircEnableInNotHircMode = true;

    /* MCG_Lite configuration for EXT mode. */
    mcglite_config_t mcgliteConfigExt;
    mcgliteConfigExt.outSrc                  = kMCGLITE_ClkSrcExt;
    mcgliteConfigExt.irclkEnableMode         = 0U;
    mcgliteConfigExt.ircs                    = kMCGLITE_Lirc8M;
    mcgliteConfigExt.fcrdiv                  = kMCGLITE_LircDivBy2;
    mcgliteConfigExt.lircDiv2                = kMCGLITE_LircDivBy4;
    mcgliteConfigExt.hircEnableInNotHircMode = false;

    /* MCG_Lite configuration for LIRC8M mode. */
    mcglite_config_t mcgliteConfigLirc8M;
    mcgliteConfigLirc8M.outSrc                  = kMCGLITE_ClkSrcLirc;
    mcgliteConfigLirc8M.irclkEnableMode         = 0U;
    mcgliteConfigLirc8M.ircs                    = kMCGLITE_Lirc8M;
    mcgliteConfigLirc8M.fcrdiv                  = kMCGLITE_LircDivBy2;
    mcgliteConfigLirc8M.lircDiv2                = kMCGLITE_LircDivBy4;
    mcgliteConfigLirc8M.hircEnableInNotHircMode = false;

    /* Init hardware */
    BOARD_InitPins();
    BOARD_InitOsc0();
    /* Init using Led in Demo app */
    LED_INIT();

    while (curStep < MAX_STEP_NUM)
    {
        switch (curStep)
        {
            case 1U:
            case 4U:
            case 8U:
                /* Set to HIRC mode */
                CLOCK_SetMcgliteConfig(&mcgliteConfigHirc);
                break;
            case 2U:
            case 7U:
            case 11U:
                /* Set LIRC2M mode */
                CLOCK_SetMcgliteConfig(&mcgliteConfigLirc2M);
                break;
            case 3U:
            case 6U:
            case 9U:
                /* Set EXT mode */
                CLOCK_SetMcgliteConfig(&mcgliteConfigExt);
                break;
            case 5U:
            case 10U:
            case 12U:
                /* Set LIRC8M mode */
                CLOCK_SetMcgliteConfig(&mcgliteConfigLirc8M);
                break;
            default:
                /* Should never reach here */
                break;
        }

        curStep++;

        i = 0x400;
        while (i--)
        {
        }
    }

    /* LED blinks. */
    while (1)
    {
        i = 0x40000;
        while (i--)
        {
        }
        LED_TOGGLE();
    }
}
