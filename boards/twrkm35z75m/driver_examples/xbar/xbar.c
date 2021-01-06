/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_pit.h"
#include "fsl_xbar.h"
#include "fsl_debug_console.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BUS_CLK_FREQ            CLOCK_GetFreq(kCLOCK_BusClk)
#define PIT_CHANNEL             kPIT_Chnl_0
#define PIT_PERIOD              1000000U
#define DEMO_PIT_BASEADDR       PIT0
#define DEMO_XBAR_BASEADDR      XBAR
#define DEMO_XBAR_INPUT_SIGNAL  kXBAR_InputPit0Tif0
#define DEMO_XBAR_OUTPUT_SIGNAL kXBAR_OutputXbDmaInt0
#define DEMO_XBAR_IRQn          XBAR_IRQn
#define DEMO_XBAR_IRQHandler    XBAR_IRQHandler

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

volatile bool xbarIsrFlag = false;

/*******************************************************************************
 * Code
 ******************************************************************************/
void DEMO_XBAR_IRQHandler(void)
{
    if (XBAR_GetStatusFlags(DEMO_XBAR_BASEADDR) & kXBAR_EdgeDetectionOut0)
    {
        /* Clear interrupt flag. */
        XBAR_ClearStatusFlags(DEMO_XBAR_BASEADDR, kXBAR_EdgeDetectionOut0);
        xbarIsrFlag = true;
    }
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Main function
 */
int main(void)
{
    /* Structure of initialize XBAR. */
    xbar_control_config_t xbaraConfig;

    /* Structure of initialize PIT. */
    pit_config_t pitConfig;
    pitConfig.enableRunInDebug = false;

    /* Init board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\nXBAR Peripheral Driver Example.");

    /* Init pit module. */
    PIT_Init(DEMO_PIT_BASEADDR, &pitConfig);

    /* Set timer period for channels using. */
    PIT_SetTimerPeriod(DEMO_PIT_BASEADDR, PIT_CHANNEL, USEC_TO_COUNT(PIT_PERIOD, BUS_CLK_FREQ));

    /* Start channel using. */
    PIT_StartTimer(DEMO_PIT_BASEADDR, PIT_CHANNEL);

    /* Init xbar module. */
    XBAR_Init(DEMO_XBAR_BASEADDR);

    /* Configure the XBAR signal connections. */
    XBAR_SetSignalsConnection(DEMO_XBAR_BASEADDR, DEMO_XBAR_INPUT_SIGNAL, DEMO_XBAR_OUTPUT_SIGNAL);

    /* Configure the XBAR interrupt. */
    xbaraConfig.activeEdge  = kXBAR_EdgeRising;
    xbaraConfig.requestType = kXBAR_RequestInterruptEnalbe;
    XBAR_SetOutputSignalConfig(DEMO_XBAR_BASEADDR, DEMO_XBAR_OUTPUT_SIGNAL, &xbaraConfig);

    /* Enable at the NVIC. */
    EnableIRQ(DEMO_XBAR_IRQn);

    while (true)
    {
        if (true == xbarIsrFlag)
        {
            PRINTF("\r\nXBAR interrupt is occurred !");
            xbarIsrFlag = false;
        }
    }
}
