/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_sema42.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"

#include "fsl_lpuart.h"
#include "main/imx8qx_pads.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define APP_SEMA42           CM4__SEMA42
#define APP_SEMA42_GATE      0
#define APP_CORTEX_M_DID     3
#define APP_CORTEX_A_DID     0
#define APP_SEMA42_GATE_ADDR 0x371b0003 /* Remote address of the SEMA42 gate. */


/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void APP_InitDomainConfig(void);
void APP_DeinitDomainConfig(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

void APP_InitDomainConfig(void)
{
    /*
     * Domain Configuration and resources assignment is done in SCFW before the core starts up.
     * For this example, The M4 core and used resources/pads/memory regions are assigned to new Partition(The
     * Partition/Domain ID is APP_CORTEX_M_DID).
     */
}

void APP_DeinitDomainConfig(void)
{
}
/*!
 * @brief Main function
 */
int main(void)
{
    /* Init board hardware.*/
    sc_ipc_t ipc;

    ipc = BOARD_InitRpc();
    BOARD_InitPins(ipc);
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    BOARD_InitMemory();

    /* Power on Peripherals. */
    if (sc_pm_set_resource_power_mode(ipc, SC_R_M4_0_SEMA42, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to power on SEMA42\r\n");
    }

    PRINTF("\r\n");
    PRINTF("**************************************************************\r\n");
    PRINTF("* Please make sure the uboot is started now.                 *\r\n");
    PRINTF("* Use the following commands in uboot for SEMA42 gate access *\r\n");
    PRINTF("* - md.b 0x%08x 1 : Get SEMA42 gate status.              *\r\n", APP_SEMA42_GATE_ADDR);
    PRINTF("*   - 0 - Unlocked;                                          *\r\n");
    PRINTF("*   - %d - Locked by Cortex-A;                                *\r\n", APP_CORTEX_A_DID + 1);
    PRINTF("*   - %d - Locked by Cortex-M;                                *\r\n", APP_CORTEX_M_DID + 1);
    PRINTF("* - mw.b 0x%08x %d 1 : Lock the SEMA42 gate.              *\r\n", APP_SEMA42_GATE_ADDR,
           APP_CORTEX_A_DID + 1);
    PRINTF("* - mw.b 0x%08x 0 1 : Unlock the SEMA42 gate.            *\r\n", APP_SEMA42_GATE_ADDR);
    PRINTF("**************************************************************\r\n\r\n");

    PRINTF("Press anykey to start the example...\r\n");

    GETCHAR();

    PRINTF("\r\nSEMA42 example started!\r\n");

    APP_InitDomainConfig();

    /* SEMA42 init */
    SEMA42_Init(APP_SEMA42);
    /* Reset the sema42 gate */
    SEMA42_ResetAllGates(APP_SEMA42);

    /*
     * Part 1. Cortex-M locks the SEMA42 gate, Cortex-A checks the status in uboot.
     */
    PRINTF("\r\nNow the SEMA42 gate is unlocked, checking status in uboot returns 0.\r\n");
    PRINTF("Press anykey to lock the SEMA42 gate...\r\n");

    GETCHAR();
    SEMA42_Lock(APP_SEMA42, APP_SEMA42_GATE, APP_CORTEX_M_DID);

    PRINTF("\r\nNow the SEMA42 gate is locked, checking status in uboot returns %d.\r\n", APP_CORTEX_M_DID + 1);
    PRINTF("Lock or unlock the SEMA42 gate in uboot, the status does not change.\r\n");

    PRINTF("\r\nPress anykey to unlock the SEMA42 gate...\r\n");

    GETCHAR();
    SEMA42_Unlock(APP_SEMA42, APP_SEMA42_GATE);

    PRINTF("\r\nNow the SEMA42 gate is unlocked, checking status in uboot returns 0.\r\n");

    /*
     * Part 2. Cortex-A locks the SEMA42 gate in uboot, Cortex-M checks the status.
     */
    do
    {
        SEMA42_Unlock(APP_SEMA42, APP_SEMA42_GATE);

        PRINTF("\r\nLock the SEMA42 gate in uboot, after locked, then press anykey...\r\n");

        GETCHAR();

    } while (kStatus_SEMA42_Busy != SEMA42_TryLock(APP_SEMA42, APP_SEMA42_GATE, APP_CORTEX_M_DID));

    PRINTF("\r\nCortex-A has locked the SEMA42 gate in uboot, Cortex-M could not lock.\r\n");

    /*
     * Part 3. Reset the SEMA42 gate.
     */
    PRINTF("\r\nPress anykey to reset the SEMA42 gate...\r\n");

    GETCHAR();

    SEMA42_ResetGate(APP_SEMA42, APP_SEMA42_GATE);

    if (kSEMA42_Unlocked != SEMA42_GetGateStatus(APP_SEMA42, APP_SEMA42_GATE))
    {
        PRINTF("\r\nSEMA42 gate reset error.\r\n");

        APP_DeinitDomainConfig();
        while (1)
        {
        }
    }

    PRINTF("\r\nNow the SEMA42 gate is unlocked, checking status in uboot returns 0.\r\n");

    PRINTF("\r\nPress anykey to finish the example...\r\n");

    GETCHAR();

    APP_DeinitDomainConfig();

    PRINTF("\r\nSEMA42 uboot example successed.\r\n");

    while (1)
    {
    }
}
