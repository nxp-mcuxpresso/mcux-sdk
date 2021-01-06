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
#include "fsl_xbara.h"
#include "fsl_debug_console.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_XBARA_USER_CHANNEL_INPUT  kXBARA1_InputPitTrigger0
#define DEMO_XBARA_USER_CHANNEL_OUTPUT kXBARA1_OutputDmaChMuxReq30
#define BUS_CLK_FREQ                   CLOCK_GetFreq(kCLOCK_OscClk)
#define DEMO_XBARA_BASEADDR            XBARA1
#define DEMO_PIT_BASEADDR              PIT
#define DEMO_XBARA_IRQn                XBAR1_IRQ_0_1_IRQn
#define DEMO_XBARA_IRQHandler          XBAR1_IRQ_0_1_IRQHandler
#define PIT_CHANNEL                    kPIT_Chnl_0
#define PIT_PERIOD                     1000000U


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

volatile bool xbaraIsrFlag = false;

/*******************************************************************************
 * Code
 ******************************************************************************/
void DEMO_XBARA_IRQHandler(void)
{
    if (XBARA_GetStatusFlags(DEMO_XBARA_BASEADDR) & kXBARA_EdgeDetectionOut0)
    {
        /* Clear interrupt flag. */
        XBARA_ClearStatusFlags(DEMO_XBARA_BASEADDR, kXBARA_EdgeDetectionOut0);
        xbaraIsrFlag = true;
    }
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Main function
 */
int main(void)
{
    /* Structure of initialize XBARA. */
    xbara_control_config_t xbaraConfig;

    /* Structure of initialize PIT. */
    pit_config_t pitConfig;
    pitConfig.enableRunInDebug = false;

    /* Init board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\nXBARA Peripheral Driver Example.");

    /* Init pit module. */
    PIT_Init(DEMO_PIT_BASEADDR, &pitConfig);

    /* Set timer period for channels using. */
    PIT_SetTimerPeriod(DEMO_PIT_BASEADDR, PIT_CHANNEL, USEC_TO_COUNT(PIT_PERIOD, BUS_CLK_FREQ));

    /* Start channel using. */
    PIT_StartTimer(DEMO_PIT_BASEADDR, PIT_CHANNEL);

    /* Init xbara module. */
    XBARA_Init(DEMO_XBARA_BASEADDR);

    /* Configure the XBARA signal connections. */
    XBARA_SetSignalsConnection(DEMO_XBARA_BASEADDR, DEMO_XBARA_USER_CHANNEL_INPUT, DEMO_XBARA_USER_CHANNEL_OUTPUT);

    /* Configure the XBARA interrupt. */
    xbaraConfig.activeEdge  = kXBARA_EdgeRising;
    xbaraConfig.requestType = kXBARA_RequestInterruptEnalbe;
    XBARA_SetOutputSignalConfig(DEMO_XBARA_BASEADDR, DEMO_XBARA_USER_CHANNEL_OUTPUT, &xbaraConfig);

    /* Enable at the NVIC. */
    EnableIRQ(DEMO_XBARA_IRQn);

    while (true)
    {
        if (true == xbaraIsrFlag)
        {
            PRINTF("\r\nXBARA interrupt is occurred !");
            xbaraIsrFlag = false;
        }
    }
}
