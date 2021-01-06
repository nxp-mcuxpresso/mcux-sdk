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
 * @brief Example function to show how to change from PEI to BLPI mode.
 * MCG transition: PEI -> FBI -> BLPI
 */
void APP_ChangePeiToBlpiExample(void)
{
    /* Change PEI -> FBI */
    CLOCK_InternalModeToFbiModeQuick();
    assert(kMCG_ModeFBI == CLOCK_GetMode());

    /* Change FBI -> BLPI */
    CLOCK_SetLowPowerEnable(true);
    assert(kMCG_ModeBLPI == CLOCK_GetMode());
}

/*!
 * @brief Example function to show how to change from BLPI to PEI mode.
 * MCG transition: BLPI -> PBI -> PEI
 */
void APP_ChangeBlpiToPeiExample(void)
{
    /* Change BLPI -> PBI */
    CLOCK_SetPbiMode();
    assert(kMCG_ModePBI == CLOCK_GetMode());

    /* Change PBI -> PEI */
    CLOCK_SetPeiMode();
    assert(kMCG_ModePEI == CLOCK_GetMode());
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

    /* Change clock BLPI -> FBI -> PEI */
    APP_ChangeBlpiToPeiExample();
    /* Change clock PEI -> FBI -> BLPI */
    APP_ChangePeiToBlpiExample();

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
