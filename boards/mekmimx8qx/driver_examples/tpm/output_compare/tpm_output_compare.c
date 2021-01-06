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
#include "fsl_tpm.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* define instance */
#define DEMO_TPM_BASEADDR     CM4__TPM
#define BOARD_TPM_OUT_CHANNEL kTPM_Chnl_0

/* Get source clock for TPM driver */
#define TPM_SOURCE_CLOCK (CLOCK_GetIpFreq(kCLOCK_M4_0_Tpm))

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
    tpm_config_t tpmInfo;
    uint32_t compareValue = 0x1000;

    /* Board pin, clock, debug console init */
    sc_ipc_t ipc;

    ipc = BOARD_InitRpc();
    BOARD_InitPins(ipc);
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    BOARD_InitMemory();

    /* Power on Local TPM for M4. */
    if (sc_pm_set_resource_power_mode(ipc, SC_R_M4_0_TPM, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
        PRINTF("Error: sc_pm_set_resource_power_mode SC_R_M4_0_TPM failed\r\n");

    /* Resource Manager */

    /* Print a note to terminal */
    PRINTF("\r\nTPM example for output compare\r\n");
    PRINTF("\r\nYou will see the output signal toggle");
    PRINTF("\r\nProbe the signal using an oscilloscope");

    TPM_GetDefaultConfig(&tpmInfo);

#if defined(TPM_PRESCALER_VALUE)
    /* Set divider to TPM_PRESCALER_VALUE instead of default 1 to be the led toggling visible */
    tpmInfo.prescale = TPM_PRESCALER_VALUE;
#endif

    /* Initialize TPM module */
    TPM_Init(DEMO_TPM_BASEADDR, &tpmInfo);

    /* Setup the output compare mode to toggle output on a match */
    TPM_SetupOutputCompare(DEMO_TPM_BASEADDR, BOARD_TPM_OUT_CHANNEL, kTPM_ToggleOnMatch, compareValue);

    /* Set the timer to be in free-running mode */
    DEMO_TPM_BASEADDR->MOD = 0xFFFF;

    TPM_StartTimer(DEMO_TPM_BASEADDR, kTPM_SystemClock);
    while (1)
    {
    }
}
