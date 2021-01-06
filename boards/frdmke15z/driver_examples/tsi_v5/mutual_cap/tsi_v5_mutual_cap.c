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
#define PAD_TSI_MUTUAL_CAP_1_NAME "KEY3"

/* IRQ related redefinitions for specific SOC */
#define TSI0_IRQHandler TSI_IRQHandler
#define TSI0_IRQn       TSI_IRQn

/* Define the delta value to indicate a touch event */
#define TOUCH_DELTA_VALUE 100U

/* TSI indication led of electrode 1 */
#define LED1_INIT()   LED_GREEN1_INIT(LOGIC_LED_OFF)
#define LED1_TOGGLE() LED_GREEN1_TOGGLE()
#define LED2_INIT()   LED_RED1_INIT(LOGIC_LED_OFF)

/* Get source clock for LPTMR driver */
#define LPTMR_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_LpoClk)
/* Define LPTMR microseconds count value */
#define LPTMR_USEC_COUNT (220000U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* The array stores the un-touched sample counter for mutual-cap pad */
uint16_t mutualCalibratedData[1] = {0U}; /* This example demo only 1 mutual-cap pad usage */
/* Array of TSI peripheral base address. */
static TSI_Type *const s_tsiBases[] = TSI_BASE_PTRS;

/*******************************************************************************
 * Code
 ******************************************************************************/
void TSI0_IRQHandler(void)
{
    if (TSI_GetRxMutualCapMeasuredChannel(s_tsiBases[0]) ==
        (tsi_mutual_rx_channel_t)(BOARD_TSI_MUTUAL_RX_ELECTRODE_1 - 6U))
    {
        if (TSI_GetCounter(s_tsiBases[0]) > (uint16_t)(mutualCalibratedData[0] + TOUCH_DELTA_VALUE))
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
    tsi_mutualCap_config_t tsiConfig_mutualCap;
    lptmr_config_t lptmrConfig;
    memset((void *)&lptmrConfig, 0, sizeof(lptmrConfig));

    /* Initialize standard SDK demo application pins */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* CLOCK_EnableClock(kCLOCK_Intmux0); */
    /* Init tsi Leds in Demo app */
    LED1_INIT();
    LED2_INIT();

    /* Configure LPTMR */
    LPTMR_GetDefaultConfig(&lptmrConfig);
    /* TSI default hardware configuration for normal mode */
    TSI_GetMutualCapModeDefaultConfig(&tsiConfig_mutualCap);

    /* Initialize the LPTMR */
    LPTMR_Init(LPTMR0, &lptmrConfig);
    /* Initialize the TSI */
    TSI_InitMutualCapMode(s_tsiBases[0], &tsiConfig_mutualCap);

    /* Set timer period */
    LPTMR_SetTimerPeriod(LPTMR0, USEC_TO_COUNT(LPTMR_USEC_COUNT, LPTMR_SOURCE_CLOCK));

    NVIC_EnableIRQ(TSI0_IRQn);
    TSI_EnableModule(s_tsiBases[0], true); /* Enable module */

    PRINTF("\r\nTSI_V5 Mutual-Cap mode Example Start!\r\n");
    /*********  CALIBRATION PROCESS ************/
    PRINTF("\r\nPlease do not touch pad %s when in calibration process!\r\n", PAD_TSI_MUTUAL_CAP_1_NAME);
    TSI_EnableHardwareTriggerScan(s_tsiBases[0], false); /* Enable software trigger scan */
    TSI_DisableInterrupts(s_tsiBases[0], kTSI_EndOfScanInterruptEnable);
    TSI_ClearStatusFlags(s_tsiBases[0], kTSI_EndOfScanFlag);
    /* Select one mutual-cap pad as detecting pad. */
    TSI_SetMutualCapTxChannel(s_tsiBases[0], (tsi_mutual_tx_channel_t)BOARD_TSI_MUTUAL_TX_ELECTRODE_1);
    TSI_SetMutualCapRxChannel(s_tsiBases[0], (tsi_mutual_rx_channel_t)(BOARD_TSI_MUTUAL_RX_ELECTRODE_1 - 6U));
    TSI_StartSoftwareTrigger(s_tsiBases[0]);
    while (!(TSI_GetStatusFlags(s_tsiBases[0]) & kTSI_EndOfScanFlag))
    {
    }
    mutualCalibratedData[0] = TSI_GetCounter(s_tsiBases[0]);
    PRINTF("Calibrated counters for mutual-cap pad %s is: %d \r\n", PAD_TSI_MUTUAL_CAP_1_NAME, mutualCalibratedData[0]);

    /********** SOFTWARE TRIGGER SCAN USING POLLING METHOD ********/
    PRINTF("\r\nNOW, comes to the software trigger scan using polling method!\r\n");
    TSI_EnableHardwareTriggerScan(s_tsiBases[0], false); /* Enable software trigger scan */
    TSI_DisableInterrupts(s_tsiBases[0], kTSI_EndOfScanInterruptEnable);
    TSI_ClearStatusFlags(s_tsiBases[0], kTSI_EndOfScanFlag);
    /* Select one mutual-cap pad as detecting pad. */
    TSI_SetMutualCapTxChannel(s_tsiBases[0], (tsi_mutual_tx_channel_t)BOARD_TSI_MUTUAL_TX_ELECTRODE_1);
    TSI_SetMutualCapRxChannel(s_tsiBases[0], (tsi_mutual_rx_channel_t)(BOARD_TSI_MUTUAL_RX_ELECTRODE_1 - 6U));
    TSI_StartSoftwareTrigger(s_tsiBases[0]);
    while (!(TSI_GetStatusFlags(s_tsiBases[0]) & kTSI_EndOfScanFlag))
    {
    }
    PRINTF("Mutual-cap pad %s Normal mode counter is: %d \r\n", PAD_TSI_MUTUAL_CAP_1_NAME,
           TSI_GetCounter(s_tsiBases[0]));
    TSI_ClearStatusFlags(s_tsiBases[0], kTSI_EndOfScanFlag);
    TSI_ClearStatusFlags(s_tsiBases[0], (uint32_t)kTSI_OutOfRangeFlag);

    /********** SOFTWARE TRIGGER SCAN USING INTERRUPT METHOD ********/
    PRINTF("\r\nNOW, comes to the software trigger scan using interrupt method!\r\n");
    TSI_EnableInterrupts(s_tsiBases[0], kTSI_GlobalInterruptEnable);
    TSI_EnableInterrupts(s_tsiBases[0], kTSI_EndOfScanInterruptEnable);
    TSI_ClearStatusFlags(s_tsiBases[0], kTSI_EndOfScanFlag);
    /* Select one mutual-cap pad as detecting pad. */
    TSI_SetMutualCapTxChannel(s_tsiBases[0], (tsi_mutual_tx_channel_t)BOARD_TSI_MUTUAL_TX_ELECTRODE_1);
    TSI_SetMutualCapRxChannel(s_tsiBases[0], (tsi_mutual_rx_channel_t)(BOARD_TSI_MUTUAL_RX_ELECTRODE_1 - 6U));
    TSI_StartSoftwareTrigger(s_tsiBases[0]);
    while (TSI_IsScanInProgress(s_tsiBases[0]))
    {
    }
    PRINTF("Mutual-cap pad %s Normal mode counter is: %d \r\n", PAD_TSI_MUTUAL_CAP_1_NAME,
           TSI_GetCounter(s_tsiBases[0]));

    /********** HARDWARE TRIGGER SCAN ********/
    PRINTF("\r\nNOW, comes to the hardware trigger scan method!\r\n");
    PRINTF("After running, touch pad %s each time, you will see LED toggles.\r\n", PAD_TSI_MUTUAL_CAP_1_NAME);
    TSI_EnableModule(s_tsiBases[0], false);
    TSI_EnableHardwareTriggerScan(s_tsiBases[0], true);
    TSI_EnableInterrupts(s_tsiBases[0], kTSI_GlobalInterruptEnable);
    TSI_EnableInterrupts(s_tsiBases[0], kTSI_EndOfScanInterruptEnable);
    TSI_ClearStatusFlags(s_tsiBases[0], kTSI_EndOfScanFlag);

    /* Select one mutual-cap pad as detecting pad. */
    TSI_SetMutualCapTxChannel(s_tsiBases[0], (tsi_mutual_tx_channel_t)BOARD_TSI_MUTUAL_TX_ELECTRODE_1);
    TSI_SetMutualCapRxChannel(s_tsiBases[0], (tsi_mutual_rx_channel_t)(BOARD_TSI_MUTUAL_RX_ELECTRODE_1 - 6U));
    TSI_EnableModule(s_tsiBases[0], true);
    TRGMUX_SetTriggerSource(TRGMUX0, kTRGMUX_Tsi, kTRGMUX_TriggerInput0, kTRGMUX_SourceLptmr0);
    LPTMR_StartTimer(LPTMR0); /* Start LPTMR triggering */

    while (1)
    {
    }
}
