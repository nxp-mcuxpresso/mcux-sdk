/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_tsi_v5.h"
#include "fsl_debug_console.h"
#include "fsl_lptmr.h"
#include "fsl_trgmux.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Available PAD names on board */
#define PAD_TSI_ELECTRODE_1_NAME "E1"

/* IRQ related redefinitions for specific SOC */
#define TSI0_IRQHandler TSI_IRQHandler
#define TSI0_IRQn       TSI_IRQn

/* Define the delta value to indicate a touch event */
#define TOUCH_DELTA_VALUE 100U

/* TSI indication led of electrode 1 */
#define LED1_INIT()   LED_GREEN1_INIT(LOGIC_LED_OFF)
#define LED1_TOGGLE() LED_GREEN1_TOGGLE()

/* Get source clock for LPTMR driver */
#define LPTMR_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_LpoClk)
/* Define LPTMR microseconds count value */
#define LPTMR_USEC_COUNT (260000U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
tsi_calibration_data_t buffer;
/* Array of TSI peripheral base address. */
static TSI_Type *const s_tsiBases[] = TSI_BASE_PTRS;

/*******************************************************************************
 * Code
 ******************************************************************************/
void TSI0_IRQHandler(void)
{
    if (TSI_GetSelfCapMeasuredChannel(s_tsiBases[0]) == BOARD_TSI_ELECTRODE_1)
    {
        if (TSI_GetCounter(s_tsiBases[0]) <
            (uint16_t)(buffer.calibratedData[BOARD_TSI_ELECTRODE_1] - TOUCH_DELTA_VALUE))
        {
            LED1_TOGGLE(); /* Toggle the touch event indicating LED */
        }
    }

    /* Clear endOfScan flag */
    TSI_ClearStatusFlags(s_tsiBases[0], kTSI_EndOfScanFlag);
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Main function
 */
int main(void)
{
    volatile uint32_t i = 0;
    tsi_selfCap_config_t tsiConfig_selfCap;
    lptmr_config_t lptmrConfig;
    memset((void *)&lptmrConfig, 0, sizeof(lptmrConfig));

    /* Initialize standard SDK demo application pins */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    /* Init tsi Leds in Demo app */
    LED1_INIT();

    /* Configure LPTMR */
    LPTMR_GetDefaultConfig(&lptmrConfig);
    /* TSI default hardware configuration for self-cap mode */
    TSI_GetSelfCapModeDefaultConfig(&tsiConfig_selfCap);

    /* Initialize the LPTMR */
    LPTMR_Init(LPTMR0, &lptmrConfig);
    /* Initialize the TSI */
    TSI_InitSelfCapMode(s_tsiBases[0], &tsiConfig_selfCap);
    /* Enable noise cancellation function */
    TSI_EnableNoiseCancellation(s_tsiBases[0], true);

    /* Set timer period */
    LPTMR_SetTimerPeriod(LPTMR0, USEC_TO_COUNT(LPTMR_USEC_COUNT, LPTMR_SOURCE_CLOCK));

    NVIC_EnableIRQ(TSI0_IRQn);
    TSI_EnableModule(s_tsiBases[0], true); /* Enable module */

    PRINTF("\r\nTSI_V5 Self-Cap mode Example Start!\r\n");
    /*********  CALIBRATION PROCESS ************/
    memset((void *)&buffer, 0, sizeof(buffer));
    TSI_SelfCapCalibrate(s_tsiBases[0], &buffer);
    /* Print calibrated counter values */
    for (i = 0U; i < FSL_FEATURE_TSI_CHANNEL_COUNT; i++)
    {
        PRINTF("Calibrated counters for channel %d is: %d \r\n", i, buffer.calibratedData[i]);
    }

    /********** SOFTWARE TRIGGER SCAN USING POLLING METHOD ********/
    PRINTF("\r\nNOW, comes to the software trigger scan using polling method!\r\n");
    TSI_EnableHardwareTriggerScan(s_tsiBases[0], false); /* Enable software trigger scan */
    TSI_DisableInterrupts(s_tsiBases[0], kTSI_EndOfScanInterruptEnable);
    TSI_ClearStatusFlags(s_tsiBases[0], kTSI_EndOfScanFlag);
    TSI_SetSelfCapMeasuredChannel(s_tsiBases[0], BOARD_TSI_ELECTRODE_1);
    TSI_StartSoftwareTrigger(s_tsiBases[0]);
    while (!(TSI_GetStatusFlags(s_tsiBases[0]) & kTSI_EndOfScanFlag))
    {
    }
    PRINTF("Channel %d Normal mode counter is: %d \r\n", BOARD_TSI_ELECTRODE_1, TSI_GetCounter(s_tsiBases[0]));

    TSI_ClearStatusFlags(s_tsiBases[0], kTSI_EndOfScanFlag);
    TSI_SetSelfCapMeasuredChannel(s_tsiBases[0], BOARD_TSI_ELECTRODE_2);
    TSI_StartSoftwareTrigger(s_tsiBases[0]);
    while (!(TSI_GetStatusFlags(s_tsiBases[0]) & kTSI_EndOfScanFlag))
    {
    }
    PRINTF("Channel %d Normal mode counter is: %d \r\n", BOARD_TSI_ELECTRODE_2, TSI_GetCounter(s_tsiBases[0]));
    TSI_ClearStatusFlags(s_tsiBases[0], kTSI_EndOfScanFlag | kTSI_OutOfRangeFlag);

    /********** SOFTWARE TRIGGER SCAN USING INTERRUPT METHOD ********/
    PRINTF("\r\nNOW, comes to the software trigger scan using interrupt method!\r\n");
    TSI_EnableInterrupts(s_tsiBases[0], kTSI_GlobalInterruptEnable);
    TSI_EnableInterrupts(s_tsiBases[0], kTSI_EndOfScanInterruptEnable);
    TSI_ClearStatusFlags(s_tsiBases[0], kTSI_EndOfScanFlag);
    TSI_SetSelfCapMeasuredChannel(s_tsiBases[0], BOARD_TSI_ELECTRODE_1);
    TSI_StartSoftwareTrigger(s_tsiBases[0]);
    while (TSI_IsScanInProgress(s_tsiBases[0]))
    {
    }
    PRINTF("Channel %d Normal mode counter is: %d \r\n", BOARD_TSI_ELECTRODE_1, TSI_GetCounter(s_tsiBases[0]));

    TSI_SetSelfCapMeasuredChannel(s_tsiBases[0], BOARD_TSI_ELECTRODE_2);
    TSI_StartSoftwareTrigger(s_tsiBases[0]);
    while (TSI_IsScanInProgress(s_tsiBases[0]))
    {
    }
    PRINTF("Channel %d Normal mode counter is: %d \r\n", BOARD_TSI_ELECTRODE_2, TSI_GetCounter(s_tsiBases[0]));

    /********** HARDWARE TRIGGER SCAN ********/
    PRINTF("\r\nNOW, comes to the hardware trigger scan method!\r\n");
    PRINTF("After running, touch pad %s each time, you will see LED toggles.\r\n", PAD_TSI_ELECTRODE_1_NAME);
    TSI_EnableModule(s_tsiBases[0], false);
    TSI_EnableHardwareTriggerScan(s_tsiBases[0], true);
    TSI_EnableInterrupts(s_tsiBases[0], kTSI_GlobalInterruptEnable);
    TSI_EnableInterrupts(s_tsiBases[0], kTSI_EndOfScanInterruptEnable);
    TSI_ClearStatusFlags(s_tsiBases[0], kTSI_EndOfScanFlag);

    TSI_SetSelfCapMeasuredChannel(s_tsiBases[0],
                                  BOARD_TSI_ELECTRODE_1); /* Select BOARD_TSI_ELECTRODE_1 as detecting electrode. */
    TSI_EnableModule(s_tsiBases[0], true);
    TRGMUX_SetTriggerSource(TRGMUX0, kTRGMUX_Tsi, kTRGMUX_TriggerInput0, kTRGMUX_SourceLptmr0);
    LPTMR_StartTimer(LPTMR0); /* Start LPTMR triggering */

    while (1)
    {
    }
}
