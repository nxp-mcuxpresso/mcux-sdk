/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "board.h"

#include "fsl_lpit.h"

#include "fsl_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_LPIT_BASE       LPIT0
#define DEMO_LPIT_IRQn       LPIT0_IRQn
#define DEMO_LPIT_IRQHandler LPIT0_IRQHandler
/* Get source clock for LPIT driver */
#define LPIT_SOURCECLOCK CLOCK_GetFreq(kCLOCK_ScgSircAsyncDiv2Clk)
#define LED_INIT()       LED_RED1_INIT(LOGIC_LED_OFF)
#define LED_TOGGLE()     LED_RED1_TOGGLE()
#define DEMO_MAX_CHAINED_COUNTS (5U)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

volatile bool lpitIsrFlag0 = false;
volatile bool lpitIsrFlag1 = false;
#if (defined(FSL_FEATURE_LPIT_TIMER_COUNT) && (FSL_FEATURE_LPIT_TIMER_COUNT >= 3U))
volatile bool lpitIsrFlag2 = false;
#endif
#if (defined(FSL_FEATURE_LPIT_TIMER_COUNT) && (FSL_FEATURE_LPIT_TIMER_COUNT >= 4U))
volatile bool lpitIsrFlag3 = false;
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
void DEMO_LPIT_IRQHandler(void)
{
    uint32_t tempFlag = LPIT_GetStatusFlags(DEMO_LPIT_BASE);

    if (0U != (tempFlag & kLPIT_Channel0TimerFlag))
    {
        /* Clear interrupt flag.*/
        LPIT_ClearStatusFlags(DEMO_LPIT_BASE, kLPIT_Channel0TimerFlag);
        lpitIsrFlag0 = true;
    }

    if (0U != (tempFlag & kLPIT_Channel1TimerFlag))
    {
        /* Clear interrupt flag.*/
        LPIT_ClearStatusFlags(DEMO_LPIT_BASE, kLPIT_Channel1TimerFlag);
        lpitIsrFlag1 = true;
    }

#if (defined(FSL_FEATURE_LPIT_TIMER_COUNT) && (FSL_FEATURE_LPIT_TIMER_COUNT >= 3U))
    if (0U != (tempFlag & kLPIT_Channel2TimerFlag))
    {
        /* Clear interrupt flag.*/
        LPIT_ClearStatusFlags(DEMO_LPIT_BASE, kLPIT_Channel2TimerFlag);
        lpitIsrFlag2 = true;
    }
#endif
#if (defined(FSL_FEATURE_LPIT_TIMER_COUNT) && (FSL_FEATURE_LPIT_TIMER_COUNT >= 4U))
    if (0U != (tempFlag & kLPIT_Channel3TimerFlag))
    {
        /* Clear interrupt flag.*/
        LPIT_ClearStatusFlags(DEMO_LPIT_BASE, kLPIT_Channel3TimerFlag);
        lpitIsrFlag3 = true;
    }
#endif
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Main function
 */
int main(void)
{
    /* Structure of initialize LPIT */
    lpit_config_t lpitConfig;
    lpit_chnl_params_t lpitChannelConfig;

    /* Board pin, clock, debug console init */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Set the source for the LPIT module */
    CLOCK_SetIpSrc(kCLOCK_Lpit0, kCLOCK_IpSrcSircAsync);

    /* Initialize and enable LED */
    LED_INIT();

    /*
     * lpitConfig.enableRunInDebug = false;
     * lpitConfig.enableRunInDoze = false;
     */
    LPIT_GetDefaultConfig(&lpitConfig);

    /* Init lpit module */
    LPIT_Init(DEMO_LPIT_BASE, &lpitConfig);

    /* SETUP 0: Configure Channel 0. */
    lpitChannelConfig.chainChannel          = false;
    lpitChannelConfig.enableReloadOnTrigger = false;
    lpitChannelConfig.enableStartOnTrigger  = false;
    lpitChannelConfig.enableStopOnTimeout   = false;
    lpitChannelConfig.timerMode             = kLPIT_PeriodicCounter;
    /* Set default values for the trigger source */
    lpitChannelConfig.triggerSelect = kLPIT_Trigger_TimerChn0;
    lpitChannelConfig.triggerSource = kLPIT_TriggerSource_External;

    /* Init lpit channel 0 */
    LPIT_SetupChannel(DEMO_LPIT_BASE, kLPIT_Chnl_0, &lpitChannelConfig);

    /* Set timer period for channel 0 */
    LPIT_SetTimerPeriod(DEMO_LPIT_BASE, kLPIT_Chnl_0, USEC_TO_COUNT(1000000U, LPIT_SOURCECLOCK));

    /* SETUP 1: Configure Channel 1. */
    lpitChannelConfig.chainChannel = true;

    /* Init lpit channel 0 */
    LPIT_SetupChannel(DEMO_LPIT_BASE, kLPIT_Chnl_1, &lpitChannelConfig);

    /* Set timer period for channel 0 */
    LPIT_SetTimerPeriod(DEMO_LPIT_BASE, kLPIT_Chnl_1, DEMO_MAX_CHAINED_COUNTS);

#if (defined(FSL_FEATURE_LPIT_TIMER_COUNT) && (FSL_FEATURE_LPIT_TIMER_COUNT >= 3U))
    /* SETUP 2: Configure Channel 2. */
    lpitChannelConfig.chainChannel = true;

    /* Init lpit channel 0 */
    LPIT_SetupChannel(DEMO_LPIT_BASE, kLPIT_Chnl_2, &lpitChannelConfig);

    /* Set timer period for channel 0 */
    LPIT_SetTimerPeriod(DEMO_LPIT_BASE, kLPIT_Chnl_2, DEMO_MAX_CHAINED_COUNTS);
#endif

#if (defined(FSL_FEATURE_LPIT_TIMER_COUNT) && (FSL_FEATURE_LPIT_TIMER_COUNT >= 4U))
    /* SETUP 3: Configure Channel 3. */
    lpitChannelConfig.chainChannel = true;

    /* Init lpit channel 0 */
    LPIT_SetupChannel(DEMO_LPIT_BASE, kLPIT_Chnl_3, &lpitChannelConfig);

    /* Set timer period for channel 0 */
    LPIT_SetTimerPeriod(DEMO_LPIT_BASE, kLPIT_Chnl_3, DEMO_MAX_CHAINED_COUNTS);
#endif

    /* Enable timer interrupts for channel 0 and 1. */
    LPIT_EnableInterrupts(DEMO_LPIT_BASE, kLPIT_Channel0TimerInterruptEnable | kLPIT_Channel1TimerInterruptEnable);
#if (defined(FSL_FEATURE_LPIT_TIMER_COUNT) && (FSL_FEATURE_LPIT_TIMER_COUNT >= 3U))
    /* Enable timer interrupts for channel 2. */
    LPIT_EnableInterrupts(DEMO_LPIT_BASE, kLPIT_Channel2TimerInterruptEnable);
#endif
#if (defined(FSL_FEATURE_LPIT_TIMER_COUNT) && (FSL_FEATURE_LPIT_TIMER_COUNT >= 4U))
    /* Enable timer interrupts for channel 3. */
    LPIT_EnableInterrupts(DEMO_LPIT_BASE, kLPIT_Channel3TimerInterruptEnable);
#endif

    /* Enable at the NVIC */
    EnableIRQ(DEMO_LPIT_IRQn);

    /* Start channel 0 */
    PRINTF("\r\nStarting channel No.0 ...");
    LPIT_StartTimer(DEMO_LPIT_BASE, kLPIT_Chnl_0);

    /* Start channel 1 */
    PRINTF("\r\nStarting channel No.1 ...");
    LPIT_StartTimer(DEMO_LPIT_BASE, kLPIT_Chnl_1);

#if (defined(FSL_FEATURE_LPIT_TIMER_COUNT) && (FSL_FEATURE_LPIT_TIMER_COUNT >= 3U))
    /* Start channel 2 */
    PRINTF("\r\nStarting channel No.2 ...");
    LPIT_StartTimer(DEMO_LPIT_BASE, kLPIT_Chnl_2);
#endif
#if (defined(FSL_FEATURE_LPIT_TIMER_COUNT) && (FSL_FEATURE_LPIT_TIMER_COUNT >= 4U))
    /* Start channel 3 */
    PRINTF("\r\nStarting channel No.3 ...\r\n");
    LPIT_StartTimer(DEMO_LPIT_BASE, kLPIT_Chnl_3);
#endif

    while (true)
    {
        /* Check whether occur interupt. */
        if (true == lpitIsrFlag0)
        {
            PRINTF("\r\n Channel No.0 interrupt is occurred !");
            LED_TOGGLE();
            lpitIsrFlag0 = false;
        }

        if (true == lpitIsrFlag1)
        {
            PRINTF("\r\n\r\n Channel No.1 Chained with Channel No.0 interrupt is occurred !\r\n");
            lpitIsrFlag1 = false;
        }

#if (defined(FSL_FEATURE_LPIT_TIMER_COUNT) && (FSL_FEATURE_LPIT_TIMER_COUNT >= 3U))
        if (true == lpitIsrFlag2)
        {
            PRINTF("\r\n\r\n Channel No.2 Chained with Channel No.1 interrupt is occurred !\r\n");
            lpitIsrFlag2 = false;
        }
#endif
#if (defined(FSL_FEATURE_LPIT_TIMER_COUNT) && (FSL_FEATURE_LPIT_TIMER_COUNT >= 4U))
        if (true == lpitIsrFlag3)
        {
            PRINTF("\r\n\r\n Channel No.3 Chained with Channel No.2 interrupt is occurred !\r\n");
            lpitIsrFlag3 = false;
        }
#endif
    }
}
