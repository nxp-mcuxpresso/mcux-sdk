/*
 * Copyright 2018,2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "clock_config.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
void BOARD_BootClockRUN(void)
{
	/* Initialize UART clock to 24MHz */
	CLOCK_DisableClock(kCLOCK_Uart4);
	CLOCK_SetRootMux(kCLOCK_RootUart4, kCLOCK_UartRootmuxOsc24M);
	CLOCK_SetRootDivider(kCLOCK_RootUart4, 1U, 1U);
	CLOCK_EnableClock(kCLOCK_Uart4);
}
