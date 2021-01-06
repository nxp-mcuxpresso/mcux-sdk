/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_rnga.h"
#include "fsl_debug_console.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define RNGA_EXAMPLE_RANDOM_NUMBER 10

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Test rnga.
 * @details Generate random numbers and print them to terminal.
 */

int main(void)
{
    uint32_t i;
    status_t status;
    uint32_t data[RNGA_EXAMPLE_RANDOM_NUMBER];

    /* Init hardware*/
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("RNGA Peripheral Driver Example\r\n");

    /* Init RNGA */
    RNGA_Init(RNG);

    while (1)
    {
        PRINTF("Generate %d random numbers: \r\n", RNGA_EXAMPLE_RANDOM_NUMBER);

        /* Get Random data*/
        status = RNGA_GetRandomData(RNG, data, sizeof(data));
        if (status == kStatus_Success)
        {
            /* Print data*/
            for (i = 0; i < RNGA_EXAMPLE_RANDOM_NUMBER; i++)
            {
                PRINTF("Random[%d] = 0x%X\r\n", i, data[i]);
            }
        }
        else
        {
            PRINTF("RNGA failed!\r\n");
        }

        /* Print a note.*/
        PRINTF("\r\n Press any key to continue... \r\n");
        GETCHAR();
    }
}
