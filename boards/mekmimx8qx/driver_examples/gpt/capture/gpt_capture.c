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
#include "fsl_irqsteer.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_GPT_IRQn LSIO_GPT0_INT_IRQn
#define DEMO_GPT_BASE LSIO__GPT0
/* GPT channel used for input capture */
#define BOARD_GPT_INPUT_CAPTURE_CHANNEL kGPT_InputCapture_Channel1
/* Interrupt to enable and flag to read; depends on the GPT channel used */
#define EXAMPLE_GPT_CAPTURE_IRQHandler     LSIO_GPT0_INT_IRQHandler
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
    sc_ipc_t ipc;
    ipc = BOARD_InitRpc();
    BOARD_InitPins(ipc);
    BOARD_BootClockRUN();
    BOARD_InitMemory();
    BOARD_InitDebugConsole();

    if (sc_pm_set_resource_power_mode(ipc, SC_R_GPT_0, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to power on SC_R_GPT_0\r\n");
    }
    if (sc_pm_set_resource_power_mode(ipc, SC_R_IRQSTR_M4_0, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to power on IRQSTR\r\n");
    }
    /* Enable IRQ STEER */
    IRQSTEER_Init(IRQSTEER);
    IRQSTEER_EnableInterrupt(IRQSTEER, LSIO_GPT0_INT_IRQn);
    /* Enable the NVIC */
    NVIC_EnableIRQ(IRQSTEER_1_IRQn);

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
