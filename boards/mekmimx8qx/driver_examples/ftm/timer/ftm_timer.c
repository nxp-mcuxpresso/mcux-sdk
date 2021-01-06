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
#include "fsl_ftm.h"

#include "fsl_common.h"
#include "fsl_irqsteer.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* The Flextimer base address/channel used for board */
#define BOARD_FTM_BASEADDR ADMA__FTM0

/* Interrupt number and interrupt handler for the FTM base address used */
#define BOARD_FTM_IRQ_NUM IRQSTEER_4_IRQn
#define BOARD_FTM_HANDLER ADMA_FTM0_INT_IRQHandler

/* System clock source for FTM driver is bus clock fixed to 160M, if user
   selects external clock source, then CLOCK_SetIpFreq(kCLOCK_DMA_Ftm0, xxx)
   could be used to change the external clock rate. */
#define FTM_SOURCE_CLOCK (160000000 / 4)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile bool ftmIsrFlag           = false;
volatile uint32_t milisecondCounts = 0U;

/*******************************************************************************
 * Code
 ******************************************************************************/
int main(void)
{
    uint32_t cnt;
    uint32_t loop       = 2U;
    uint32_t secondLoop = 1000U;
    const char *signals = "-|";
    ftm_config_t ftmInfo;

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
    PRINTF("\r\nFTM example to simulate a timer\r\n");
    PRINTF("\r\nYou will see a \"-\" or \"|\" in terminal every 1 second:\r\n");

    FTM_GetDefaultConfig(&ftmInfo);

    /* Divide FTM clock by 4 */
    ftmInfo.prescale = kFTM_Prescale_Divide_4;

    /* Initialize FTM module */
    FTM_Init(BOARD_FTM_BASEADDR, &ftmInfo);

    /*
     * Set timer period.
     */
    FTM_SetTimerPeriod(BOARD_FTM_BASEADDR, USEC_TO_COUNT(1000U, FTM_SOURCE_CLOCK));

    FTM_EnableInterrupts(BOARD_FTM_BASEADDR, kFTM_TimeOverflowInterruptEnable);

    EnableIRQ(BOARD_FTM_IRQ_NUM);

    FTM_StartTimer(BOARD_FTM_BASEADDR, kFTM_SystemClock);

    cnt = 0;
    while (true)
    {
        if (ftmIsrFlag)
        {
            milisecondCounts++;
            ftmIsrFlag = false;
            if (milisecondCounts >= secondLoop)
            {
                PRINTF("%c", signals[cnt & 1]);
                cnt++;
                if (cnt >= loop)
                {
                    cnt = 0;
                }
                milisecondCounts = 0U;
            }
        }
        __WFI();
    }
}

void BOARD_FTM_HANDLER(void)
{
    /* Clear interrupt flag.*/
    FTM_ClearStatusFlags(BOARD_FTM_BASEADDR, kFTM_TimeOverflowFlag);
    ftmIsrFlag = true;
    __DSB();
}
