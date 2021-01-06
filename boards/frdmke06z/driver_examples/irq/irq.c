/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdlib.h>
#include "fsl_debug_console.h"
#include "fsl_irq.h"

#include "fsl_common.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile bool g_keypress = false;

/*******************************************************************************
 * Code
 ******************************************************************************/

void IRQ_IRQHandler(void)
{
    if (IRQ_GetIRQFlag(IRQ))
    {
        /* Clear IRQ Flag. */
        IRQ_ClearIRQFlag(IRQ);
        g_keypress = true;
    }
    SDK_ISR_EXIT_BARRIER;
}

int main(void)
{
    irq_config_t irqConfig;

    /* Configure the PTA5 pin not as /RESET */
    SIM->SOPT0 &= ~SIM_SOPT0_RSTPE_MASK;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\n IRQ Driver Example Start.\r\n");

    irqConfig.enablePullDevice = true;
    irqConfig.edgeSelect       = kIRQ_FallingEdgeorLowlevel; /* Falling edge.*/
    irqConfig.detectMode       = kIRQ_DetectOnEdgesOnly;
    IRQ_Init(IRQ, &irqConfig);
    IRQ_EnableInterrupt(IRQ, true);
    EnableIRQ(IRQ_IRQn);

    while (1)
    {
        if (g_keypress)
        {
            PRINTF("\r\n The IRQ interrupt has happened!\r\n");
            break;
        }
    }

    /* Deinitialize the module. */
    IRQ_Deinit(IRQ);

    PRINTF("\r\n IRQ Driver Example End.\r\n");

    while (1)
    {
    }
}
