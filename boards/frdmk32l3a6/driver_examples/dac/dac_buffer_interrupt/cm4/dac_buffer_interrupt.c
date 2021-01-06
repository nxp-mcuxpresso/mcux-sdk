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
#include "fsl_dac.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_DAC_BASEADDR         LPDAC0
#define DEMO_DAC_IRQ_ID           LPDAC0_IRQn
#define DEMO_DAC_IRQ_HANDLER_FUNC LPDAC0_IRQHandler
#define DEMO_DAC_VREF             kDAC_ReferenceVoltageSourceAlt2
#define DEMO_DAC_VALUE_ARRAY_SIZE 32U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile uint32_t g_DacInputIndex    = 0U;
volatile uint32_t g_DacOutputIndex   = 0U;
volatile uint32_t g_DacInterruptDone = false;
/* User-defined wave for DAC output. */
const uint32_t g_DacValues[DEMO_DAC_VALUE_ARRAY_SIZE] = {
    0U,   100,  200,  300,  400,  500,  600,  700,  800,  900,  1000, 1100, 1200, 1300, 1400, 1500,
    1600, 1700, 1800, 1900, 2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000, 3100};

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Main function
 */
int main(void)
{
    dac_config_t dacConfigStruct;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    EnableIRQ(DEMO_DAC_IRQ_ID); /* Enable interrupt in NVIC. */

    PRINTF("\r\nDAC buffer interrupt Example.\r\n");

    /* Configure the DAC. */
    DAC_GetDefaultConfig(&dacConfigStruct);
    dacConfigStruct.referenceVoltageSource = DEMO_DAC_VREF;
    dacConfigStruct.fifoTriggerMode        = kDAC_FIFOTriggerBySoftwareMode; /* Software trigger. */
    dacConfigStruct.fifoWorkMode           = kDAC_FIFOWorkAsNormalMode;      /* Normal FIFO mode. */
    dacConfigStruct.fifoWatermarkLevel     = 4U;                             /* Watermark. */
    DAC_Init(DEMO_DAC_BASEADDR, &dacConfigStruct);
    DAC_Enable(DEMO_DAC_BASEADDR, true); /* Enable output. */

    PRINTF("Press any key to trigger the DAC...\r\n");
    /* Enable DAC interrupts. */
    DAC_EnableInterrupts(DEMO_DAC_BASEADDR, kDAC_FIFOEmptyInterruptEnable);

    while (1)
    {
        /* Wait  */
        while (!g_DacInterruptDone)
        {
        }
        g_DacInterruptDone = false;

        /* Trigger the buffer and move the pointer. */
        GETCHAR();
        DAC_DoSoftwareTriggerFIFO(DEMO_DAC_BASEADDR);
        PRINTF("DAC next output: %d\r\n", g_DacValues[g_DacOutputIndex]);
        if (g_DacOutputIndex >= DEMO_DAC_VALUE_ARRAY_SIZE - 1U)
        {
            g_DacOutputIndex = 0U;
        }
        else
        {
            g_DacOutputIndex++;
        }
    }
}

/*!
 * @brief IRQ function for DAC buffer interrupt
 */
void DEMO_DAC_IRQ_HANDLER_FUNC(void)
{
    uint32_t flags = DAC_GetStatusFlags(DEMO_DAC_BASEADDR);

    if (0U != (kDAC_FIFOEmptyFlag & flags))
    {
        DAC_SetData(DEMO_DAC_BASEADDR, g_DacValues[g_DacInputIndex]);
        if (g_DacInputIndex >= (DEMO_DAC_VALUE_ARRAY_SIZE - 1U))
        {
            g_DacInputIndex = 0U;
        }
        else
        {
            g_DacInputIndex++;
        }
    }
    g_DacInterruptDone = true;
    SDK_ISR_EXIT_BARRIER;
}
