/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "board.h"
#include "fsl_pwt.h"

#include "fsl_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Interrupt number for the PWT instance used */
#define PWT_INTERRUPT_NUMBER PWT_LPTMR0_IRQn
#define PWT_EXAMPLE_HANDLER  PWT_LPTMR0_IRQHandler

/* Get source clock for PWT driver */
#define PWT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)

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
    uint8_t reg;

    /* Board pin, clock, debug console init */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Init PWT */
    PWT_GetDefaultConfig(&pwtConfig);
    pwtConfig.inputSelect = kPWT_InputPort_1;

    PRINTF("\r\nPWT example: input signal whose pulse width needs to be measured\r\n");

    /* Enable at the NVIC */
    EnableIRQ(PWT_INTERRUPT_NUMBER);

    PWT_Init(PWT, &pwtConfig);

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
            reg = ((PWT->CR) & (PWT_CR_LVL_MASK | PWT_CR_TGL_MASK)) >> PWT_CR_LVL_SHIFT;

            switch (reg)
            {
                case 0:
                    PRINTF("\r\nLow overflow (0 duty ratio), signal stayed low\r\n");
                    break;
                case 1:
                    PRINTF("\r\nHigh overflow (100% duty ratio), signal stayed high\r\n");
                    break;
                case 2:
                    PRINTF("\r\nToggled Low overflow\r\n");
                    break;
                default:
                    PRINTF("\r\nToggled High overflow\r\n");
                    break;
            }
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
