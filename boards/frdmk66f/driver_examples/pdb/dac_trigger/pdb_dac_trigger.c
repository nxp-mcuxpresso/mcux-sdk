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
#include "fsl_pdb.h"
#include "fsl_dac.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_PDB_BASE               PDB0
#define DEMO_PDB_IRQ_ID             PDB0_IRQn
#define DEMO_PDB_IRQ_HANDLER        PDB0_IRQHandler
#define DEMO_PDB_DELAY_VALUE        1000U
#define DEMO_PDB_MODULUS_VALUE      1000U
#define DEMO_PDB_DAC_INTERVAL_VALUE 800U

#define DEMO_DAC_BASE             DAC0
#define DEMO_DAC_CHANNEL          kPDB_DACTriggerChannel0
#define DEMO_DAC_IRQ_ID           DAC0_IRQn
#define DEMO_DAC_IRQ_HANDLER      DAC0_IRQHandler
#define DEMO_DAC_USED_BUFFER_SIZE DAC_DATL_COUNT

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Initialize the DAC.
 */
static void DEMO_InitPDB_DAC(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile uint32_t g_PdbDelayInterruptCounter;
volatile uint32_t g_PdbDelayInterruptFlag;
#if defined(FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION) && FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION
volatile bool g_DacBufferWatermarkInterruptFlag;
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION */
volatile bool g_DacBufferReadPointerTopPositionInterruptFlag;
volatile bool g_DacBufferReadPointerBottomPositionInterruptFlag;

/*******************************************************************************
 * Code
 ******************************************************************************/
void static DEMO_InitPDB_DAC(void)
{
    dac_config_t dacConfigStruct;
    dac_buffer_config_t dacBufferConfigStruct;
    uint8_t index = 0U;
    uint16_t dacValue;
    uint32_t mask;

    /* Configure the DAC. */
    /*
     * dacConfigStruct.referenceVoltageSource = kDAC_ReferenceVoltageSourceVref2;
     * dacConfigStruct.enableLowPowerMode = false;
     */
    DAC_GetDefaultConfig(&dacConfigStruct);
    DAC_Init(DEMO_DAC_BASE, &dacConfigStruct);
    DAC_Enable(DEMO_DAC_BASE, true);

    /* Configure the DAC buffer. */
    DAC_GetDefaultBufferConfig(&dacBufferConfigStruct);
    dacBufferConfigStruct.triggerMode = kDAC_BufferTriggerByHardwareMode;
    DAC_SetBufferConfig(DEMO_DAC_BASE, &dacBufferConfigStruct);

    /* Make sure the read pointer to the start. */
    DAC_SetBufferReadPointer(DEMO_DAC_BASE, 0U);
    dacValue = 0U;
    for (index = 0U; index < DEMO_DAC_USED_BUFFER_SIZE; index++)
    {
        DAC_SetBufferValue(DEMO_DAC_BASE, index, dacValue);
        dacValue += (0xFFFU / DEMO_DAC_USED_BUFFER_SIZE);
    }
/* Clear flags. */
#if defined(FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION) && FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION
    g_DacBufferWatermarkInterruptFlag = false;
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION */
    g_DacBufferReadPointerTopPositionInterruptFlag    = false;
    g_DacBufferReadPointerBottomPositionInterruptFlag = false;

    /* Enable interrupts. */
    mask = 0U;
#if defined(FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION) && FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION
    mask |= kDAC_BufferWatermarkInterruptEnable;
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION */
    mask |= kDAC_BufferReadPointerTopInterruptEnable | kDAC_BufferReadPointerBottomInterruptEnable;
    DAC_EnableBuffer(DEMO_DAC_BASE, true);
    DAC_EnableBufferInterrupts(DEMO_DAC_BASE, mask);

    PRINTF("\r\nDAC Buffer Information\r\n");
    PRINTF("\t  Buffer index max  : %d\r\n", dacBufferConfigStruct.upperLimit);
#if defined(FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION) && FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION
    PRINTF("\t  Buffer watermark  : %d\r\n",
           dacBufferConfigStruct.upperLimit - (uint8_t)(dacBufferConfigStruct.watermark) - 1U);
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_SETECTION */
}

/*!
 * @brief ISR for PDB interrupt function
 */
void DEMO_PDB_IRQ_HANDLER(void)
{
    PDB_ClearStatusFlags(DEMO_PDB_BASE, kPDB_DelayEventFlag);
    g_PdbDelayInterruptCounter++;
    g_PdbDelayInterruptFlag = true;
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief ISR for DAC interrutp function
 */
void DEMO_DAC_IRQ_HANDLER(void)
{
    uint32_t flags = DAC_GetBufferStatusFlags(DEMO_DAC_BASE);

#if defined(FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION) && FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION
    if (kDAC_BufferWatermarkFlag == (kDAC_BufferWatermarkFlag & flags))
    {
        g_DacBufferWatermarkInterruptFlag = true;
    }
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION */
    if (kDAC_BufferReadPointerTopPositionFlag == (kDAC_BufferReadPointerTopPositionFlag & flags))
    {
        g_DacBufferReadPointerTopPositionInterruptFlag = true;
    }
    if (kDAC_BufferReadPointerBottomPositionFlag == (kDAC_BufferReadPointerBottomPositionFlag & flags))
    {
        g_DacBufferReadPointerBottomPositionInterruptFlag = true;
    }
    /* Clear flags. */
    DAC_ClearBufferStatusFlags(DEMO_DAC_BASE, flags);
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Main function
 */
int main(void)
{
    pdb_config_t pdbConfigStruct;
    pdb_dac_trigger_config_t pdbDacTriggerConfigStruct;
    uint8_t index = 0U;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    EnableIRQ(DEMO_PDB_IRQ_ID);
    EnableIRQ(DEMO_DAC_IRQ_ID);

    PRINTF("\r\nPDB DAC trigger Example.\r\n");

    /* Configure the PDB counter. */
    /*
     * pdbConfigStruct.loadValueMode = kPDB_LoadValueImmediately;
     * pdbConfigStruct.prescalerDivider = kPDB_PrescalerDivider1;
     * pdbConfigStruct.dividerMultiplicationFactor = kPDB_DividerMultiplicationFactor1;
     * pdbConfigStruct.triggerInputSource = kPDB_TriggerSoftware;
     * pdbConfigStruct.enableContinuousMode = false;
     */
    PDB_GetDefaultConfig(&pdbConfigStruct);
    PDB_Init(DEMO_PDB_BASE, &pdbConfigStruct);

    /* Configure the delay interrupt. */
    PDB_SetModulusValue(DEMO_PDB_BASE, DEMO_PDB_MODULUS_VALUE);
    PDB_SetCounterDelayValue(DEMO_PDB_BASE, DEMO_PDB_DELAY_VALUE);
    PDB_EnableInterrupts(DEMO_PDB_BASE, kPDB_DelayInterruptEnable);

    /* Configure the DAC trigger. */
    pdbDacTriggerConfigStruct.enableExternalTriggerInput = false;
    pdbDacTriggerConfigStruct.enableIntervalTrigger      = true;
    PDB_SetDACTriggerConfig(DEMO_PDB_BASE, DEMO_DAC_CHANNEL, &pdbDacTriggerConfigStruct);
    PDB_SetDACTriggerIntervalValue(DEMO_PDB_BASE, DEMO_DAC_CHANNEL, DEMO_PDB_DAC_INTERVAL_VALUE);

    PDB_DoLoadValues(DEMO_PDB_BASE);

    /* Configure the DAC. */
    DEMO_InitPDB_DAC();

    PRINTF("Type any key into terminal to trigger the DAC buffer through PDB ...\r\n");

    g_PdbDelayInterruptCounter = 0U;

    while (1)
    {
        if (0U == index)
        {
            PRINTF("\r\n");
        }
        PRINTF("DAC Buffer Index %2d: ", index);
#if defined(FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION) && FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION
        if (g_DacBufferWatermarkInterruptFlag)
        {
            PRINTF("WatermarkEvent \t");
            g_DacBufferWatermarkInterruptFlag = false;
        }
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION */
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

        /* Trigger the PDB and then trigger the buffer, move the pointer. */
        GETCHAR();
        g_PdbDelayInterruptFlag = false;
        PDB_DoSoftwareTrigger(DEMO_PDB_BASE);
        while (!g_PdbDelayInterruptFlag)
        {
        }
        index++;
        if (index >= DEMO_DAC_USED_BUFFER_SIZE)
        {
            index = 0U;
        }
    }
}
