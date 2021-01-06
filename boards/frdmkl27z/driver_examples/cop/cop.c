/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_cop.h"
#include "fsl_rcm.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


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
    cop_config_t configCop;

    /* Init hardware */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /*
     * configCop.enableWindowMode = false;
     * configCop.timeoutMode = kCOP_LongTimeoutMode;
     * configCop.enableStop = false;
     * configCop.enableDebug = false;
     * configCop.clockSource = kCOP_LpoClock;
     * configCop.timeoutCycles = kCOP_2Power10CyclesOr2Power18Cycles;
     */
    COP_GetDefaultConfig(&configCop);
#if FSL_FEATURE_COP_HAS_LONGTIME_MODE
    configCop.timeoutMode = kCOP_ShortTimeoutMode;
#endif

    /* Check if WDOG reset occurred */
    if (RCM_GetPreviousResetSources(RCM) & kRCM_SourceWdog)
    {
        PRINTF("Reset due to COP timeout\r\n");
        COP_Disable(SIM);
        PRINTF("COP example ends!\r\n");
    }
    else
    {
        /* If WDOG reset is not occurred, enables COP */
        PRINTF("\r\nCOP example start!\r\n");
        COP_Init(SIM, &configCop);
        /* Refresh COP 10 times and then wait for timeout reset */
        for (uint32_t loopCount = 0U; loopCount < 10U; loopCount++)
        {
            COP_Refresh(SIM);
            PRINTF("COP refresh %d time\r\n", loopCount + 1U);
        }

        PRINTF("COP will timeout and chip will be reset\r\n");
    }
    while (1)
    {
    }
}
