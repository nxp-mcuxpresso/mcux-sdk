/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_mmdvsq.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_MMDVSQ_BASE MMDVSQ

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
    uint16_t sqrtresult;  /* square root result */
    int32_t divideresult; /* divide result */
    uint32_t rcndval;     /* radicand value */
    int32_t dendval;      /* dividend value */
    int32_t dsorval;      /* divisor value */

    /* Initialize standard SDK demo application pins */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    /* Print the initial banner */
    PRINTF("\r\nStart MMDVSQ Example\r\n");
    PRINTF("\r\nCalculation square root, please enter radicand\r\n");
    /* Import radicand value */
    SCANF("%d", &rcndval);
    /* Check BUSY bit before Calculation begin. */
    while ((kMMDVSQ_BusySquareRoot == MMDVSQ_GetExecutionStatus(DEMO_MMDVSQ_BASE)) ||
           (kMMDVSQ_BusyDivide == MMDVSQ_GetExecutionStatus(DEMO_MMDVSQ_BASE)))
    {
    }
    /* Calculation square root */
    sqrtresult = MMDVSQ_Sqrt(DEMO_MMDVSQ_BASE, rcndval);
    PRINTF("\r\nSquare root of %d is %d\r\n", rcndval, sqrtresult);

    PRINTF("\r\nCalculation division to get remainder and quotient");
    PRINTF("\r\nEnter dividend and divisor\r\n");
    /* Import dividend value and divisor value */
    SCANF("%d, %d", &dendval, &dsorval);
    /* Check BUSY bit before Calculation begin. */
    while ((kMMDVSQ_BusySquareRoot == MMDVSQ_GetExecutionStatus(DEMO_MMDVSQ_BASE)) ||
           (kMMDVSQ_BusyDivide == MMDVSQ_GetExecutionStatus(DEMO_MMDVSQ_BASE)))
    {
    }
    /* Calculation Remainder */
    divideresult = MMDVSQ_GetDivideRemainder(DEMO_MMDVSQ_BASE, dendval, dsorval, false);
    PRINTF("\r\nRemainder of %d and %d is %d\r\n", dendval, dsorval, divideresult);
    /* Check BUSY bit before Calculation begin. */
    while ((kMMDVSQ_BusySquareRoot == MMDVSQ_GetExecutionStatus(DEMO_MMDVSQ_BASE)) ||
           (kMMDVSQ_BusyDivide == MMDVSQ_GetExecutionStatus(DEMO_MMDVSQ_BASE)))
    {
    }
    /* Calculation nQuotient */
    divideresult = MMDVSQ_GetDivideQuotient(DEMO_MMDVSQ_BASE, dendval, dsorval, false);
    PRINTF("\r\nQuotient of %d and %d is %d\r\n", dendval, dsorval, divideresult);

    while (1)
    {
    }
}
