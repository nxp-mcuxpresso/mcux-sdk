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

#include "fsl_xrdc.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define APP_SEMA42           SEMA42_0
#define APP_SEMA42_GATE      0
#define APP_CORTEX_M_DID     2
#define APP_CORTEX_A_DID     1
#define APP_SEMA42_GATE_ADDR 0x4101b003 /* Address of the SEMA42 gate. */


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
    uint32_t i;
    xrdc_periph_access_config_t periConfig;
    xrdc_mem_access_config_t memConfig;
    xrdc_processor_domain_assignment_t domainConfig;
    xrdc_non_processor_domain_assignment_t nonProcDomainConfig;

    const xrdc_periph_t periphAccessible[] = {kXRDC_PeriphLpuart0, kXRDC_PeriphLpuart4, kXRDC_PeriphLpi2c3,
                                              kXRDC_PeriphXrdc0,   kXRDC_PeriphXrdc1,   kXRDC_PeriphXrdc2,
                                              kXRDC_PeriphXrdc3,   kXRDC_PeriphSema42_0};

    XRDC_Init(XRDC);
    XRDC_SetGlobalValid(XRDC, false);

    /* Configure the domain ID for Cortex-M. */
    XRDC_GetDefaultProcessorDomainAssignment(&domainConfig);
    domainConfig.domainId = APP_CORTEX_M_DID;
    XRDC_SetProcessorDomainAssignment(XRDC, kXRDC_MasterCM4Code, 0, &domainConfig);
    XRDC_SetProcessorDomainAssignment(XRDC, kXRDC_MasterCM4System, 0, &domainConfig);

    /* Configure the domain ID for Cortex-A. */
    domainConfig.domainId = APP_CORTEX_A_DID;
    XRDC_SetProcessorDomainAssignment(XRDC, kXRDC_MasterCA7, 0, &domainConfig);

    XRDC_GetDefaultNonProcessorDomainAssignment(&nonProcDomainConfig);
    nonProcDomainConfig.domainId = APP_CORTEX_A_DID;
    XRDC_SetNonProcessorDomainAssignment(XRDC, kXRDC_MasterSdhc0, 0, &nonProcDomainConfig);
    XRDC_SetNonProcessorDomainAssignment(XRDC, kXRDC_MasterSdhc1, 0, &nonProcDomainConfig);

    /*
     * Configure the peripheral policy.
     */
    XRDC_GetPeriphAccessDefaultConfig(&periConfig);
    periConfig.policy[APP_CORTEX_A_DID] = kXRDC_AccessPolicyAll;
    periConfig.policy[APP_CORTEX_M_DID] = kXRDC_AccessPolicyAll;

    for (i = 0; i < ARRAY_SIZE(periphAccessible); i++)
    {
        periConfig.periph = periphAccessible[i];
        XRDC_SetPeriphAccessConfig(XRDC, &periConfig);
    }

    /*
     * Configure the memory policy.
     */
    XRDC_GetMemAccessDefaultConfig(&memConfig);
    memConfig.policy[APP_CORTEX_A_DID] = kXRDC_AccessPolicyAll;
    memConfig.policy[APP_CORTEX_M_DID] = kXRDC_AccessPolicyAll;
    /* SRAM0. */
    memConfig.mem         = kXRDC_MemMrc2_0;
    memConfig.baseAddress = 0x2F000000U;
    memConfig.size        = kXRDC_MemSize128K;
    XRDC_SetMemAccessConfig(XRDC, &memConfig);

    /* SRAM1. */
    memConfig.mem         = kXRDC_MemMrc5_0;
    memConfig.baseAddress = 0x2F020000U;
    memConfig.size        = kXRDC_MemSize128K;
    XRDC_SetMemAccessConfig(XRDC, &memConfig);

    /* QSPI flash. */
    memConfig.mem         = kXRDC_MemMrc1_0;
    memConfig.baseAddress = 0xC0000000U;
    memConfig.size        = kXRDC_MemSize256M;
    XRDC_SetMemAccessConfig(XRDC, &memConfig);
    memConfig.mem         = kXRDC_MemMrc1_1;
    memConfig.baseAddress = 0x04000000U;
    memConfig.size        = kXRDC_MemSize64M;
    XRDC_SetMemAccessConfig(XRDC, &memConfig);
    memConfig.mem         = kXRDC_MemMrc1_2;
    memConfig.baseAddress = 0x08000000U;
    memConfig.size        = kXRDC_MemSize64M;
    XRDC_SetMemAccessConfig(XRDC, &memConfig);

    /* MMDC. */
    memConfig.mem         = kXRDC_MemMrc6_0;
    memConfig.baseAddress = 0x60000000U;
    memConfig.size        = kXRDC_MemSize512M;
    XRDC_SetMemAccessConfig(XRDC, &memConfig);
    memConfig.mem         = kXRDC_MemMrc6_1;
    memConfig.baseAddress = 0x80000000U;
    memConfig.size        = kXRDC_MemSize1G;
    XRDC_SetMemAccessConfig(XRDC, &memConfig);

    XRDC_SetGlobalValid(XRDC, true);
}

void APP_DeinitDomainConfig(void)
{
    XRDC_SetGlobalValid(XRDC, false);
}

/*!
 * @brief Main function
 */
int main(void)
{
    /* Init board hardware.*/
    BOARD_InitPins();
    BOARD_BootClockRUN();
    CLOCK_SetIpSrc(kCLOCK_Lpuart0, kCLOCK_IpSrcSysOscAsync);
    BOARD_InitDebugConsole();

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
