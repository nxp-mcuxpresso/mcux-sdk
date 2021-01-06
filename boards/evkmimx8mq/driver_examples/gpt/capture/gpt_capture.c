/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_gpt.h"

#include "fsl_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_GPT_IRQn GPT1_IRQn
#define DEMO_GPT_BASE GPT1
/* GPT channel used for input capture */
#define BOARD_GPT_INPUT_CAPTURE_CHANNEL kGPT_InputCapture_Channel1
/* Interrupt to enable and flag to read; depends on the GPT channel used */
#define EXAMPLE_GPT_CAPTURE_IRQHandler     GPT1_IRQHandler
#define BOARD_GPT_CHANNEL_INTERRUPT_ENABLE kGPT_InputCapture1InterruptEnable
#define BOARD_GPT_CHANNEL_FLAG             kGPT_InputCapture1Flag

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

volatile bool gptIsrFlag = false;

/*******************************************************************************
 * Code
 ******************************************************************************/
void EXAMPLE_GPT_CAPTURE_IRQHandler(void)
{
    /* Clear interrupt flag.*/
    GPT_ClearStatusFlags(DEMO_GPT_BASE, BOARD_GPT_CHANNEL_FLAG);

    gptIsrFlag = true;
    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F, Cortex-M7, Cortex-M7F Store immediate overlapping
      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U || __CORTEX_M == 7U)
    __DSB();
#endif
}

/*!
 * @brief Main function
 */
int main(void)
{
    uint32_t captureVal = 0;
    gpt_config_t gptConfig;

    /* Board pin, clock, debug console init */
    /* Board specific RDC settings */
    BOARD_RdcInit();

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    BOARD_InitMemory();

    /* Print a note to terminal */
    PRINTF("\r\nGPT input capture example\r\n");
    PRINTF("\r\nOnce the input signal is received the input capture value is printed\r\n");

    GPT_GetDefaultConfig(&gptConfig);

    /* Initialize GPT module */
    GPT_Init(DEMO_GPT_BASE, &gptConfig);

    /* Setup input capture on a gpt channel */
    GPT_SetInputOperationMode(DEMO_GPT_BASE, BOARD_GPT_INPUT_CAPTURE_CHANNEL, kGPT_InputOperation_RiseEdge);

    /* Enable GPT Input Capture1 interrupt */
    GPT_EnableInterrupts(DEMO_GPT_BASE, BOARD_GPT_CHANNEL_INTERRUPT_ENABLE);

    /* Enable at the Interrupt */
    EnableIRQ(DEMO_GPT_IRQn);

    /* Start Timer */
    GPT_StartTimer(DEMO_GPT_BASE);

    while (true)
    {
        /* Check whether occur interupt */
        if (true == gptIsrFlag)
        {
            captureVal = GPT_GetInputCaptureValue(DEMO_GPT_BASE, BOARD_GPT_INPUT_CAPTURE_CHANNEL);
            PRINTF("\r\n Capture value =%x\r\n", captureVal);
            gptIsrFlag = false;
        }
        else
        {
            __WFI();
        }
    }
}
