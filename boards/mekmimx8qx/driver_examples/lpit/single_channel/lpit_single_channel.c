/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#include "fsl_lpit.h"

#include "fsl_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define LPIT_SOURCECLOCK CLOCK_GetIpFreq(kCLOCK_M4_0_Lpit)
#define LED_INIT()
#define LED_TOGGLE()
#define DEMO_LPIT_BASE       (CM4__LPIT)
#define DEMO_LPIT_IRQn       (M4_LPIT_IRQn)
#define DEMO_LPIT_IRQHandler M4_LPIT_IRQHandler

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

volatile bool lpitIsrFlag = false;

/*******************************************************************************
 * Code
 ******************************************************************************/
void DEMO_LPIT_IRQHandler(void)
{
    /* Clear interrupt flag.*/
    LPIT_ClearStatusFlags(DEMO_LPIT_BASE, kLPIT_Channel0TimerFlag);
    lpitIsrFlag = true;
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
    sc_ipc_t ipc;

    ipc = BOARD_InitRpc();
    BOARD_InitPins(ipc);
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    BOARD_InitMemory();

    /* Power on Local LPIT for M4 Core0. */
    if (sc_pm_set_resource_power_mode(ipc, SC_R_M4_0_PIT, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
        PRINTF("Error: sc_pm_set_resource_power_mode SC_R_M4_0_PIT failed\r\n");

    /* Clock on Local LPIT for M4 Core0. */
    if (CLOCK_SetIpFreq(kCLOCK_M4_0_Lpit, SC_66MHZ) == 0)
        PRINTF("Error: CLOCK_SetIpFreq kCLOCK_M4_0_Lpit to 66mhz failed\r\n");
    if (!CLOCK_EnableClockExt(kCLOCK_M4_0_Lpit, 0))
        PRINTF("Error: sc_pm_clock_enable SC_R_M4_0_PIT failed\r\n");

    /* Resource Manager */

    /* Initialize and enable LED */
    LED_INIT();

    /*
     * lpitConfig.enableRunInDebug = false;
     * lpitConfig.enableRunInDoze = false;
     */
    LPIT_GetDefaultConfig(&lpitConfig);

    /* Init lpit module */
    LPIT_Init(DEMO_LPIT_BASE, &lpitConfig);

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

    /* Enable timer interrupts for channel 0 */
    LPIT_EnableInterrupts(DEMO_LPIT_BASE, kLPIT_Channel0TimerInterruptEnable);

    /* Enable at the NVIC */
    EnableIRQ(DEMO_LPIT_IRQn);

    /* Start channel 0 */
    PRINTF("\r\nStarting channel No.0 ...");
    LPIT_StartTimer(DEMO_LPIT_BASE, kLPIT_Chnl_0);

    while (true)
    {
        /* Check whether occur interupt and toggle LED */
        if (true == lpitIsrFlag)
        {
            PRINTF("\r\n Channel No.0 interrupt is occurred !");
            LED_TOGGLE();
            lpitIsrFlag = false;
        }
    }
}
