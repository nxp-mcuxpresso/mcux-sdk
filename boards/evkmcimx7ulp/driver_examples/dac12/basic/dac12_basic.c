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
#define DEMO_DAC12_BASE DAC0


/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void BOARD_InitDebugConsole(void);

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
    dac12_config_t dacConfigStruct;
    uint32_t dacValue;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\nDAC basic Example.\r\n");

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
    dacConfigStruct.fifoWatermarkLevel = 4U;
#if defined(DEMO_DAC12_VREF_SOURCE)
    dacConfigStruct.referenceVoltageSource = DEMO_DAC12_VREF_SOURCE;
#endif /* DEMO_DAC12_VREF_SOURCE */
    DAC12_Init(DEMO_DAC12_BASE, &dacConfigStruct);
    DAC12_Enable(DEMO_DAC12_BASE, true); /* Enable output. */
    /* The fifo is not enabled, so the read pointer can not move automatically. */

    while (1)
    {
        PRINTF("\r\nPlease input a value (0 - 4095) to output with DAC: ");
        SCANF("%d", &dacValue);
        PRINTF("\r\nInput value is %d\r\n", dacValue);
        if (dacValue > 0xFFFU)
        {
            PRINTF("Your value is output of range.\r\n");
            continue;
        }
        DAC12_SetData(DEMO_DAC12_BASE, dacValue);
        PRINTF("DAC out: %d\r\n", dacValue);
        /*
         * The value in the first item would be converted. User can measure the output voltage from DAC_OUTx pin.
         */
    }
}
