/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#include "fsl_qtmr.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define LED_INIT()   LED_RED_INIT(LOGIC_LED_ON)
#define LED_TOGGLE() LED_RED_TOGGLE()
#define BUS_CLK_FREQ CLOCK_GetFreq(kCLOCK_BusClk)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

volatile bool qtmrIsrFlag = false;

/*******************************************************************************
 * Code
 ******************************************************************************/

void TMR1_IRQHandler(void)
{
    /* Clear interrupt flag.*/
    QTMR_ClearStatusFlags(TMR1, kQTMR_CompareFlag);

    qtmrIsrFlag = true;
    SDK_ISR_EXIT_BARRIER;
}

void TMR0_IRQHandler(void)
{
    /* Clear interrupt flag.*/
    QTMR_ClearStatusFlags(TMR0, kQTMR_EdgeFlag);

    qtmrIsrFlag = true;
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Main function
 */
int main(void)
{
    uint8_t i = 0;
    qtmr_config_t qtmrConfig;

    /* Board pin, clock, debug console init */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Initialize and enable LED */
    LED_INIT();

    PRINTF("\r\n*********QUADTIMER EXAMPLE START*********");

    /*
     * qtmrConfig.debugMode = kQTMR_RunNormalInDebug;
     * qtmrConfig.enableExternalForce = false;
     * qtmrConfig.enableMasterMode = false;
     * qtmrConfig.faultFilterCount = 0;
     * qtmrConfig.faultFilterPeriod = 0;
     * qtmrConfig.primarySource = kQTMR_ClockDivide_2;
     * qtmrConfig.secondarySource = kQTMR_Counter0InputPin;
     */
    QTMR_GetDefaultConfig(&qtmrConfig);
    /* Use IP bus clock div by 128 */
    qtmrConfig.primarySource = kQTMR_ClockDivide_128;

    PRINTF("\r\n****Timer use-case, 1 second tick.****\n");
    QTMR_Init(TMR1, &qtmrConfig);

    /* Set timer period to be 200 millisecond */
    QTMR_SetTimerPeriod(TMR1, MSEC_TO_COUNT(200U, (BUS_CLK_FREQ / 128)));

    /* Enable timer compare interrupt */
    QTMR_EnableInterrupts(TMR1, kQTMR_CompareInterruptEnable);

    /* Enable at the NVIC */
    EnableIRQ(TMR1_IRQn);

    /* Start the timer to count on rising edge of the primary source clock */
    QTMR_StartTimer(TMR1, kQTMR_PriSrcRiseEdge);
    /* Blink the LED 10 times */
    for (i = 0; i < 20; i++)
    {
        /* Check whether occur interupt and toggle LED */
        while (!(qtmrIsrFlag))
        {
        }
        PRINTF("\r\n Timer interrupt has occurred !");
        LED_TOGGLE();
        qtmrIsrFlag = false;
    }
    QTMR_Deinit(TMR1);

    PRINTF("\r\n****Chain Timer use-case, 10 second tick.****\n");

    /* Init timer 0 to use the IP Bus clock div by 128 */
    qtmrConfig.primarySource = kQTMR_ClockDivide_128;
    QTMR_Init(TMR0, &qtmrConfig);

    /* Init time 1 to use output of timer 0 as we are chaining timer 0 and 1 */
    qtmrConfig.primarySource = kQTMR_ClockCounter0Output;
    QTMR_Init(TMR1, &qtmrConfig);

    /* Set timer 0 period to be 1 millisecond */
    QTMR_SetTimerPeriod(TMR0, MSEC_TO_COUNT(1U, (BUS_CLK_FREQ / 128)));

    /* Set timer 1 count which increases every millisecond, set compare event for 10 second */
    QTMR_SetTimerPeriod(TMR1, 10000);

    /* Enable timer 1 compare interrupt */
    QTMR_EnableInterrupts(TMR1, kQTMR_CompareInterruptEnable);

    /* Enable at the NVIC */
    EnableIRQ(TMR1_IRQn);

    /* Start Time 1 in cascase mode, chained to timer 0 as set earlier via the primary source selection */
    QTMR_StartTimer(TMR1, kQTMR_CascadeCount);

    /* Start the timer 0 to count on rising edge of the primary source clock */
    QTMR_StartTimer(TMR0, kQTMR_PriSrcRiseEdge);

    /* Blink the LED 5 times */
    for (i = 0; i < 5; i++)
    {
        /* Check whether occur interupt and toggle LED */
        while (!(qtmrIsrFlag))
        {
        }
        PRINTF("\r\n Timer interrupt has occurred !");
        LED_TOGGLE();
        qtmrIsrFlag = false;
    }
    QTMR_Deinit(TMR0);
    QTMR_Deinit(TMR1);

    PRINTF("\r\n****Input capture example.****\n");
    PRINTF("\r\n****Provide a signal input to the TMR0 pin****\n");

    /* Init timer 0 to use the IP Bus clock div by 8 */
    qtmrConfig.primarySource = kQTMR_ClockDivide_8;
    QTMR_Init(TMR0, &qtmrConfig);

    /* Setup the input capture */
    QTMR_SetupInputCapture(TMR0, kQTMR_Counter0InputPin, false, true, kQTMR_RisingEdge);

    /* Enable at the NVIC */
    EnableIRQ(TMR0_IRQn);

    QTMR_EnableInterrupts(TMR0, kQTMR_EdgeInterruptEnable);

    /* Start the timer 0 to count on rising edge of the primary source clock */
    QTMR_StartTimer(TMR0, kQTMR_PriSrcRiseEdge);

    /* Check whether occur interupt and toggle LED */
    while (!(qtmrIsrFlag))
    {
    }
    PRINTF("\r\nInput Captured value=%x\n", TMR0->CAPT);

    PRINTF("\r\n*********Make sure to connect a scope.*********\n");
    PRINTF("\r\n****A 50% duty cycle PWM wave is observed in the scope.****\n");

    qtmrConfig.primarySource = kQTMR_ClockDivide_8;
    QTMR_Init(TMR1, &qtmrConfig);

    /* Generate a 50Khz PWM signal with 50% dutycycle */
    QTMR_SetupPwm(TMR1, 50000, 50, false, BUS_CLK_FREQ / 8);
    /* Start the counter */
    QTMR_StartTimer(TMR1, kQTMR_PriSrcRiseEdge);

    PRINTF("\r\n*********QUADTIMER EXAMPLE END.*********");

    while (true)
    {
    };
}
