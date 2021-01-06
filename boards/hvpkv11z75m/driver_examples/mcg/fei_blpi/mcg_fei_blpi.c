/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "board.h"
#include "fsl_common.h"
#include "fsl_port.h"
#include "fsl_gpio.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define LED_INIT()    LED_RED_INIT(LOGIC_LED_ON)
#define LED_TOGGLE()  LED_RED_TOGGLE()
#define CORE_CLK_FREQ CLOCK_GetFreq(kCLOCK_CoreSysClk)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Delay function used to wait FLL stable.
 */
static void APP_FllStableDelay(void)
{
    volatile uint32_t i = 30000U;
    while (i--)
    {
        __NOP();
    }
}

/*!
 * @brief Example function to show how to change from FEI to BLPI mode.
 * MCG transition: FEI -> FBI -> BLPI
 */
void APP_ChangeFeiToBlpiExample(void)
{
    /* Change FEI -> FBI
     * It's transitional mode, don't need to wait for FLL stable,
     * so NULL is passed as variable here.
     */
    CLOCK_SetFbiMode(kMCG_Dmx32Default, kMCG_DrsLow, NULL);
    assert(kMCG_ModeFBI == CLOCK_GetMode());

    /* Change FBI -> BLPI */
    CLOCK_SetLowPowerEnable(true);
    assert(kMCG_ModeBLPI == CLOCK_GetMode());
}

/*!
 * @brief Example function to show how to change from BLPI to FEI mode.
 * MCG transition: BLPI -> FBI -> FEI
 */
void APP_ChangeBlpiToFeiExample(void)
{
    /* Change BLPI -> FBI */
    CLOCK_SetLowPowerEnable(false);
    assert(kMCG_ModeFBI == CLOCK_GetMode());

    /* Change FBI -> FEI */
    CLOCK_SetFeiMode(kMCG_Dmx32Default, kMCG_DrsLow, APP_FllStableDelay);
    assert(kMCG_ModeFEI == CLOCK_GetMode());
}

/*!
 * @brief Main function
 */
int main(void)
{
    volatile uint32_t i;
    uint32_t sysFreq;

    BOARD_InitPins();

    /* Set clock divider to safe value to switch mode */
    CLOCK_SetSimSafeDivs();

#if (defined(FSL_FEATURE_MCG_RESET_IS_BLPI) && FSL_FEATURE_MCG_RESET_IS_BLPI)
    /* Change clock BLPI -> FBI -> FEI */
    APP_ChangeBlpiToFeiExample();
    /* Change clock FEI -> FBI -> BLPI */
    APP_ChangeFeiToBlpiExample();
#else
    /* Change clock FEI -> FBI -> BLPI */
    APP_ChangeFeiToBlpiExample();
    /* Change clock BLPI -> FBI -> FEI */
    APP_ChangeBlpiToFeiExample();
#endif

    /* Get System clock to blink a LED */
    sysFreq = CORE_CLK_FREQ / 20U;
    /* Enable a LED */
    LED_INIT();
    /* Blink a LED */
    while (1)
    {
        for (i = 0; i < sysFreq; i++)
        {
            __NOP();
        }
        LED_TOGGLE();
    }
}
