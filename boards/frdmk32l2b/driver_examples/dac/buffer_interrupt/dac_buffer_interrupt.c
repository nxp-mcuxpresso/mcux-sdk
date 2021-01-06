/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
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
#define DEMO_DAC_BASEADDR         DAC0
#define DEMO_DAC_IRQ_ID           DAC0_IRQn
#define DEMO_DAC_IRQ_HANDLER_FUNC DAC0_IRQHandler

#define DEMO_DAC_USED_BUFFER_SIZE DAC_DATL_COUNT

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if defined(FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION) && FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION
volatile bool g_DacBufferWatermarkInterruptFlag;
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION */
volatile bool g_DacBufferReadPointerTopPositionInterruptFlag;
volatile bool g_DacBufferReadPointerBottomPositionInterruptFlag;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief IRQ function for DAC buffer interrupt
 */
void DEMO_DAC_IRQ_HANDLER_FUNC(void)
{
    uint32_t flags = DAC_GetBufferStatusFlags(DEMO_DAC_BASEADDR);

#if defined(FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION) && FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION
    if (kDAC_BufferWatermarkFlag == (kDAC_BufferWatermarkFlag & flags))
    {
        g_DacBufferWatermarkInterruptFlag = true;
    }
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION */
    if (kDAC_BufferReadPointerTopPositionFlag == (kDAC_BufferReadPointerTopPositionFlag & flags))
    {
        g_DacBufferReadPointerTopPositionInterruptFlag = true;
    }
    if (kDAC_BufferReadPointerBottomPositionFlag == (kDAC_BufferReadPointerBottomPositionFlag & flags))
    {
        g_DacBufferReadPointerBottomPositionInterruptFlag = true;
    }
    DAC_ClearBufferStatusFlags(DEMO_DAC_BASEADDR, flags); /* Clear flags. */
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Main function
 */
int main(void)
{
    dac_config_t dacConfigStruct;
    dac_buffer_config_t dacBufferConfigStruct;
    uint8_t index;
    uint16_t dacValue;
    uint32_t mask;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    EnableIRQ(DEMO_DAC_IRQ_ID);

    PRINTF("\r\nDAC buffer interrupt Example.\r\n");

    /* Configure the DAC. */
    /*
     * dacConfigStruct.referenceVoltageSource = kDAC_ReferenceVoltageSourceVref2;
     * dacConfigStruct.enableLowPowerMode = false;
     */
    DAC_GetDefaultConfig(&dacConfigStruct);
    DAC_Init(DEMO_DAC_BASEADDR, &dacConfigStruct);
    DAC_Enable(DEMO_DAC_BASEADDR, true); /* Enable output. */

    /* Configure the DAC buffer. */
    DAC_GetDefaultBufferConfig(&dacBufferConfigStruct);
    DAC_SetBufferConfig(DEMO_DAC_BASEADDR, &dacBufferConfigStruct);
    DAC_SetBufferReadPointer(DEMO_DAC_BASEADDR, 0U); /* Make sure the read pointer to the start. */
    dacValue = 0U;
    for (index = 0U; index < DEMO_DAC_USED_BUFFER_SIZE; index++)
    {
        DAC_SetBufferValue(DEMO_DAC_BASEADDR, index, dacValue);
        dacValue += (0xFFFU / DEMO_DAC_USED_BUFFER_SIZE);
    }
/* Clear flags. */
#if defined(FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION) && FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION
    g_DacBufferWatermarkInterruptFlag = false;
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION */
    g_DacBufferReadPointerTopPositionInterruptFlag    = false;
    g_DacBufferReadPointerBottomPositionInterruptFlag = false;

    /* Enable interrupts. */
    mask = 0U;
#if defined(FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION) && FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION
    mask |= kDAC_BufferWatermarkInterruptEnable;
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION */
    mask |= kDAC_BufferReadPointerTopInterruptEnable | kDAC_BufferReadPointerBottomInterruptEnable;
    DAC_EnableBuffer(DEMO_DAC_BASEADDR, true);
    DAC_EnableBufferInterrupts(DEMO_DAC_BASEADDR, mask);

    PRINTF("\r\nDAC Buffer Information\r\n");
    PRINTF("\t  Buffer index max  : %d\r\n", dacBufferConfigStruct.upperLimit);
#if defined(FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION) && FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION
    PRINTF("\t  Buffer watermark  : %d\r\n",
           dacBufferConfigStruct.upperLimit - (uint8_t)(dacBufferConfigStruct.watermark) - 1U);
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION */
    PRINTF("Press any key in terminal to trigger the buffer ...\r\n");
    index = 0U;
    while (1)
    {
        if (0U == index)
        {
            PRINTF("\r\n");
        }
        PRINTF("Buffer Index %2d: ", index);
#if defined(FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION) && FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION
        if (g_DacBufferWatermarkInterruptFlag)
        {
            PRINTF("WatermarkEvent \t");
            g_DacBufferWatermarkInterruptFlag = false;
        }
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION */
        if (g_DacBufferReadPointerTopPositionInterruptFlag)
        {
            PRINTF("ReadPointerTopPositionEvent \t");
            g_DacBufferReadPointerTopPositionInterruptFlag = false;
        }
        if (g_DacBufferReadPointerBottomPositionInterruptFlag)
        {
            PRINTF("ReadPointerBottomPositionEvent \t");
            g_DacBufferReadPointerBottomPositionInterruptFlag = false;
        }
        PRINTF("\r\n");

        /* Trigger the buffer and move the pointer. */
        GETCHAR();
        DAC_DoSoftwareTriggerBuffer(DEMO_DAC_BASEADDR);
        index++;
        if (index >= DEMO_DAC_USED_BUFFER_SIZE)
        {
            index = 0U;
        }
    }
}
