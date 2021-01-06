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
#include "fsl_tstmr.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_TSTMR CM4__TSTMR

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
    uint64_t ts;

    /* Board pin, clock, debug console init */
    sc_ipc_t ipc;

    ipc = BOARD_InitRpc();
    BOARD_InitPins(ipc);
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    BOARD_InitMemory();

    ts = TSTMR_ReadTimeStamp(EXAMPLE_TSTMR);
    PRINTF("\r\n Timestamp1 = %x%x\r\n", (uint32_t)(ts >> 32), (uint32_t)ts);

    PRINTF("\r\n Test the delay function, delay for 1 second\r\n");

    ts = TSTMR_ReadTimeStamp(EXAMPLE_TSTMR);
    PRINTF("\r\n Start time = %x%x\r\n", (uint32_t)(ts >> 32), (uint32_t)ts);

    TSTMR_DelayUs(EXAMPLE_TSTMR, 1000000);

    ts = TSTMR_ReadTimeStamp(EXAMPLE_TSTMR);
    PRINTF("\r\n End time = %x%x\r\n", (uint32_t)(ts >> 32), (uint32_t)ts);
    while (1)
    {
    }
}
