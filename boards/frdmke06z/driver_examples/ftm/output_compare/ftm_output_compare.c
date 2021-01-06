/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_ftm.h"

#include "fsl_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* The Flextimer base address/channel used for board */
#define BOARD_FTM_BASEADDR    FTM2
#define BOARD_FTM_OUT_CHANNEL kFTM_Chnl_0

/* Get source clock for FTM driver */
#define FTM_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_TimerClk)

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
 * @brief Main function
 */
int main(void)
{
    ftm_config_t ftmInfo;
    uint32_t compareValue = 0x1000;

    /* Board pin, clock, debug console init */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Print a note to terminal */
    PRINTF("\r\nFTM example for output compare\r\n");
    PRINTF("\r\nYou will see the output signal toggle");
    PRINTF("\r\nProbe the signal using an oscilloscope");

    FTM_GetDefaultConfig(&ftmInfo);

#if defined(FTM_PRESCALER_VALUE)
    /* Set divider to FTM_PRESCALER_VALUE instead of default 1 to be the led toggling visible */
    ftmInfo.prescale = FTM_PRESCALER_VALUE;
#endif

    /* Initialize FTM module */
    FTM_Init(BOARD_FTM_BASEADDR, &ftmInfo);

    /* Setup the output compare mode to toggle output on a match */
    FTM_SetupOutputCompare(BOARD_FTM_BASEADDR, BOARD_FTM_OUT_CHANNEL, kFTM_ToggleOnMatch, compareValue);

    /* Set the timer to be in free-running mode */
    BOARD_FTM_BASEADDR->MOD = 0xFFFF;

    /* Update the buffered registers */
    FTM_SetSoftwareTrigger(BOARD_FTM_BASEADDR, true);

    FTM_StartTimer(BOARD_FTM_BASEADDR, kFTM_SystemClock);
    while (1)
    {
    };
}
