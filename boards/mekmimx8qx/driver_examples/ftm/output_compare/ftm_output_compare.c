/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_ftm.h"

#include "fsl_common.h"
#include "fsl_irqsteer.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* The Flextimer base address/channel used for board */
#define BOARD_FTM_BASEADDR    ADMA__FTM0
#define BOARD_FTM_OUT_CHANNEL kFTM_Chnl_2

/* System clock source for FTM driver is bus clock fixed to 160M, if user
   selects external clock source, then CLOCK_SetIpFreq(kCLOCK_DMA_Ftm0, xxx)
   could be used to change the external clock rate. */
#define FTM_SOURCE_CLOCK (160000000U))

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

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
    ftm_config_t ftmInfo;
    uint32_t compareValue = 0x1000;

    /* Board pin, clock, debug console init */
    sc_ipc_t ipc;

    ipc = BOARD_InitRpc();
    BOARD_InitPins(ipc);
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    BOARD_InitMemory();

    /* Power on FTM */
    if (sc_pm_set_resource_power_mode(ipc, SC_R_FTM_0, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
        PRINTF("Error: sc_pm_set_resource_power_mode SC_R_FTM_0 failed\r\n");

    if (sc_pm_set_resource_power_mode(ipc, SC_R_IRQSTR_M4_0, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to power on IRQSTR\r\n");
    }
    /* Enable interrupt in irqsteer */
    IRQSTEER_Init(IRQSTEER);
    IRQSTEER_EnableInterrupt(IRQSTEER, ADMA_FTM0_INT_IRQn);

    /* Print a note to terminal */
    PRINTF("\r\nFTM example for output compare\r\n");
    PRINTF("\r\nYou will see the output signal toggle");
    PRINTF("\r\nProbe the signal using an oscilloscope");

    FTM_GetDefaultConfig(&ftmInfo);

#if defined(FTM_PRESCALER_VALUE)
    /* Set divider to FTM_PRESCALER_VALUE instead of default 1 to be the led toggling visible */
    ftmInfo.prescale = FTM_PRESCALER_VALUE;
#endif

    /* Initialize FTM module */
    FTM_Init(BOARD_FTM_BASEADDR, &ftmInfo);

    /* Setup the output compare mode to toggle output on a match */
    FTM_SetupOutputCompare(BOARD_FTM_BASEADDR, BOARD_FTM_OUT_CHANNEL, kFTM_ToggleOnMatch, compareValue);

    /* Set the timer to be in free-running mode */
    BOARD_FTM_BASEADDR->MOD = 0xFFFF;

    /* Update the buffered registers */
    FTM_SetSoftwareTrigger(BOARD_FTM_BASEADDR, true);

    FTM_StartTimer(BOARD_FTM_BASEADDR, kFTM_SystemClock);
    while (1)
    {
    };
}
