/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_sema42.h"
#include "fsl_mu.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"

#include "fsl_lpuart.h"
#include "main/imx8qm_pads.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define APP_BOARD_HAS_LED 0 /* No LED connected to CM4 pads */

#define APP_MU     LSIO__MU7_A
#define APP_SEMA42 CM4_0__SEMA42

#define USE_STATIC_DOMAIN_ID 0
#define CORE0_BOOT_CORE1     0
/* Flag indicates Core Boot Up*/
#define BOOT_FLAG 0x01U
/* Flag indicates Core 0 has locked the sema42 gate. */
#define SEMA42_LOCK_FLAG 0x02U
/* Flag indicates Core 1 has locked the sema42 gate. */
#define SEMA42_CORE1_LOCK_FLAG 0x03U
/* The SEMA42 gate */
#define SEMA42_GATE 0U

/*
 * Use core 0 to boot core 1.
 * When set to 1, the core 0 assign domain ID for core 0 and core 1, then boot core 1.
 * When set to 0, core 0 and core 1 are boot up by uboot or other component, and
 * they assign their own domain ID seperately.
 */
#ifndef CORE0_BOOT_CORE1
#define CORE0_BOOT_CORE1 1
#endif

/*
 * Use static domain ID or dynamic domain ID.
 */
#ifndef USE_STATIC_DOMAIN_ID
#define USE_STATIC_DOMAIN_ID 1
#endif

/*
 * The board has LED to show the status.
 */
#ifndef APP_BOARD_HAS_LED
#define APP_BOARD_HAS_LED 1
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void APP_InitCore0Domain(void);
uint8_t APP_GetCore0DomainID(void);
#if USE_STATIC_DOMAIN_ID
uint8_t APP_GetCore0DomainID(void)
{
    return 0U;
}
#else
uint8_t APP_GetCore0DomainID(void);
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

uint8_t APP_GetCore0DomainID(void)
{
    return sc_rm_get_did(SystemGetScfwIpcHandle());
}

void APP_InitCore0Domain(void)
{
    /*
     * Domain Configuration and resources assignment is done in SCFW before the core starts up.
     * For this example, The M4 core and used resources/pads/memory regions are assigned to new Partition.
     */
}

/*!
 * @brief Main function
 */
int main(void)
{
    uint8_t domainId;
    /* Init board hardware.*/
    sc_ipc_t ipc;

    ipc = BOARD_InitRpc();

    BOARD_InitPins(ipc);
    BOARD_BootClockRUN();
    BOARD_InitMemory();
    BOARD_InitDebugConsole();

    if (sc_pm_set_resource_power_mode(ipc, SC_R_M4_0_SEMA42, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to power on sema42");
    }

    if (sc_pm_set_resource_power_mode(ipc, SC_R_MU_7A, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to power on MU");
    }

    /* Set M4 SEMA42 permissions for all other partitions */
    if (sc_rm_set_peripheral_permissions(ipc, SC_R_M4_0_SEMA42, SC_RM_PT_ALL, SC_RM_PERM_FULL) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to set SEMA42 permission\r\n");
    }
#if APP_BOARD_HAS_LED
    /* Initialize LED */
    LED_INIT();
#endif

    /* MUA init */
    MU_Init(APP_MU);

    /* Print the initial banner */
    PRINTF("\r\nSema42 example!\r\n");

    /* SEMA42 init */
    SEMA42_Init(APP_SEMA42);
    /* Reset the sema42 gate */
    SEMA42_ResetAllGates(APP_SEMA42);

#if CORE0_BOOT_CORE1
    APP_InitDomain();
    /* Boot Core 1. */
    MU_BootCoreB(APP_MU, APP_CORE1_BOOT_MODE);
#else
    APP_InitCore0Domain();
#endif

    MU_SetFlags(APP_MU, BOOT_FLAG);

    /* Wait Core 1 is Boot Up */
    while (BOOT_FLAG != MU_GetFlags(APP_MU))
    {
    }

    domainId = APP_GetCore0DomainID();

    /* Lock the sema42 gate. */
    SEMA42_Lock(APP_SEMA42, SEMA42_GATE, domainId);

    MU_SetFlags(APP_MU, SEMA42_LOCK_FLAG);

    /* Wait until user press any key */
#if APP_BOARD_HAS_LED
    PRINTF("Press any key to unlock semaphore and Core 1 will turn off the LED\r\n");
#else
    PRINTF("Press any key to unlock semaphore and Core 1 will lock it\r\n");
#endif
    GETCHAR();

    /* Unlock the sema42 gate. */
    SEMA42_Unlock(APP_SEMA42, SEMA42_GATE);

#if APP_BOARD_HAS_LED
    PRINTF("Now the LED should be turned off\r\n");
#else
    PRINTF("Wait for core 1 lock the semaphore\r\n");
#endif
    /* Wait for core 1 lock the sema */
    while (SEMA42_CORE1_LOCK_FLAG != MU_GetFlags(APP_MU))
    {
    }

#if CORE0_BOOT_CORE1
    APP_DeinitDomain();
#endif

    PRINTF("\r\nSema42 example succeed!\r\n");

    while (1)
    {
    }
}
