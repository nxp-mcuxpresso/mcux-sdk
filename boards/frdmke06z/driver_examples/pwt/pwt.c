/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_pwt.h"

#include "fsl_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Interrupt number for the PWT instance used */
#define PWT_INTERRUPT_NUMBER PWT_IRQn
#define PWT_EXAMPLE_HANDLER  PWT_IRQHandler

/* Get source clock for PWT driver */
#define PWT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_TimerClk)


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

volatile bool busyWait;
volatile bool overflowFlag;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief ISR for PWT interrupt
 *
 * This function changes the state of busyWait.
 */
void PWT_EXAMPLE_HANDLER(void)
{
    if (PWT_GetStatusFlags(PWT) & kPWT_PulseWidthValidFlag)
    {
        /*
         * Disable PWT pulse ready interrupt, ;
         * we do not want to clear the PWTRDY status bit before reading the data
         */
        PWT_DisableInterrupts(PWT, kPWT_PulseWidthReadyInterruptEnable);
        busyWait = false;
    }

    if (PWT_GetStatusFlags(PWT) & kPWT_CounterOverflowFlag)
    {
        /* Clear overflow flag */
        PWT_ClearStatusFlags(PWT, kPWT_CounterOverflowFlag);
        overflowFlag = true;
    }
    __DSB();
}

/*!
 * @brief Main function
 */
int main(void)
{
    pwt_config_t pwtConfig;
    uint16_t pulseWidth = 0;

    /* Board pin, clock, debug console init */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\nPWT example: input signal whose pulse width needs to be measured\r\n");

    /* Init PWT */
    PWT_GetDefaultConfig(&pwtConfig);
    PWT_Init(PWT, &pwtConfig);

    /* Enable at the NVIC */
    EnableIRQ(PWT_INTERRUPT_NUMBER);

    /* Enable Module Interrupt  */
    PWT_EnableInterrupts(PWT, kPWT_ModuleInterruptEnable);
    /* Start the PWT counter */
    PWT_StartTimer(PWT);

    /* This loop will set the print the pulse width */
    while (1)
    {
        busyWait     = true;
        overflowFlag = false;

        /* Enable PWT pulse ready interrupt */
        PWT_EnableInterrupts(PWT, kPWT_PulseWidthReadyInterruptEnable);

        /* Wait till ready interrupt occurs */
        while (busyWait)
        {
        }
        if (overflowFlag)
        {
            PRINTF("\r\nPWT overflow occurs\r\n");
        }
        else
        {
            pulseWidth = PWT_ReadPositivePulseWidth(PWT);
            pulseWidth = COUNT_TO_USEC(pulseWidth, PWT_SOURCE_CLOCK);
            PRINTF("\r\nPositive pulse width=%d usec\r\n", pulseWidth);

            pulseWidth = PWT_ReadNegativePulseWidth(PWT);
            pulseWidth = COUNT_TO_USEC(pulseWidth, PWT_SOURCE_CLOCK);
            PRINTF("\r\nNegative pulse width=%d usec\r\n", pulseWidth);
        }
        /* Clear pulse ready flag */
        PWT_ClearStatusFlags(PWT, kPWT_PulseWidthValidFlag);
    }
}
