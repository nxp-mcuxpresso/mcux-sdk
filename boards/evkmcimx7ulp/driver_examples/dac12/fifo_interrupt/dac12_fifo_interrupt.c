/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_dac12.h"

#include "fsl_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_DAC12_BASE         DAC0
#define DEMO_DAC12_IRQ_ID       DAC0_IRQn
#define DEMO_DAC12_HANDLER_FUNC DAC0_IRQHandler

#define DEMO_DAC_VALUE_ARRAY_SIZE 32U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void BOARD_InitDebugConsole(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile uint32_t g_DacIndex         = 0U;
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
    uint32_t mDacIndex = 0;
    dac12_config_t dacConfigStruct;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    EnableIRQ(DEMO_DAC12_IRQ_ID); /* Enable interrupt in NVIC. */

    /* Configure the DAC. */
    /*
     * dacConfigStruct.fifoWatermarkLevel = 4U;
     * dacConfigStruct.fifoWorkMode = kDAC12_FIFODisabled;
     * dacConfigStruct.referenceVoltageSource = kDAC12_ReferenceVoltageSourceAlt1;
     * dacConfigStruct.fifoTriggerMode = kDAC12_FIFOTriggerByHardwareMode;
     * dacConfigStruct.referenceCurrentSource = kDAC12_ReferenceCurrentSourceAlt0;
     * dacConfigStruct.speedMode = kDAC12_SpeedLowMode;
     * dacConfigStruct.enableAnalogBuffer = false;
     * dacConfigStruct.currentReferenceInternalTrimValue = 0x4;
     */
    DAC12_GetDefaultConfig(&dacConfigStruct);
    dacConfigStruct.fifoWorkMode = kDAC12_FIFOWorkAsNormalMode;
#if defined(DEMO_DAC12_VREF_SOURCE)
    dacConfigStruct.referenceVoltageSource = DEMO_DAC12_VREF_SOURCE;
#endif /* DEMO_DAC12_VREF_SOURCE */
    dacConfigStruct.fifoTriggerMode    = kDAC12_FIFOTriggerBySoftwareMode;
    dacConfigStruct.fifoWatermarkLevel = 4U; /* Watermark event would occur when remaining FIFO data is less than 4U. */
    DAC12_Init(DEMO_DAC12_BASE, &dacConfigStruct);
    DAC12_Enable(DEMO_DAC12_BASE, true); /* Enable output. */

    PRINTF("Press any key to trigger the DAC...\r\n");
    /* Enable DAC interrupts. */
    DAC12_EnableInterrupts(DEMO_DAC12_BASE, kDAC12_WatermarkInterruptEnable);

    while (1)
    {
        /* Trigger the buffer and move the pointer. */
        GETCHAR();

        DAC12_DoSoftwareTrigger(DEMO_DAC12_BASE);
        /* Wait  */
        while (!g_DacInterruptDone)
        {
        }
        g_DacInterruptDone = false;
        PRINTF("DAC next output: %d\r\n", g_DacValues[mDacIndex]);
        if (mDacIndex >= (DEMO_DAC_VALUE_ARRAY_SIZE - 1U))
        {
            mDacIndex = 0U;
        }
        else
        {
            mDacIndex++;
        }
    }
}

/*!
 * @brief IRQ function for DAC buffer interrupt
 */
void DEMO_DAC12_HANDLER_FUNC(void)
{
    uint32_t flags = DAC12_GetStatusFlags(DEMO_DAC12_BASE);

    if (0U != (kDAC12_WatermarkFlag & flags))
    {
        DAC12_SetData(DEMO_DAC12_BASE, g_DacValues[g_DacIndex]);
        if (g_DacIndex >= (DEMO_DAC_VALUE_ARRAY_SIZE - 1U))
        {
            g_DacIndex = 0U;
        }
        else
        {
            g_DacIndex++;
        }
    }
    g_DacInterruptDone = true;
    __DSB();
}
