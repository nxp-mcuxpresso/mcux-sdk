/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_xrdc.h"
#include "fsl_debug_console.h"

#include "fsl_lptmr.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void APP_SetXrdcConfig(void);
void APP_CheckAndResolvePeriphAccessError(xrdc_error_t *error);
void APP_CheckAndResolveMemoryAccessError(xrdc_error_t *error);
void APP_SetPeriphUnaccessible(void);
void APP_SetMemoryUnaccessible(void);
void APP_TouchPeriph(void);
void APP_TouchMemory(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile bool g_hardfaultFlag = false;
/*******************************************************************************
 * Code
 ******************************************************************************/

/* The memory for MRC test, here use the SRAM0 address. */
#define MEM_REGION_START 0x08000000U
#define MEM_REGION_END   0x08003FFFU

#define APP_DOMAIN_ID 1


void APP_SetXrdcConfig(void)
{
    uint32_t i;
    xrdc_periph_access_config_t periConfig;
    xrdc_processor_domain_assignment_t domainConfig;
    xrdc_mem_access_config_t memConfig;

    const xrdc_periph_t periphAccessible[] = {kXRDC_PeriphLpuart3};

    XRDC_Init(XRDC);
    XRDC_SetGlobalValid(XRDC, false);

    /* Configure the domain ID for current core. */
    XRDC_GetDefaultProcessorDomainAssignment(&domainConfig);
    domainConfig.domainId = APP_DOMAIN_ID;
    /*
     * Current core might have many masters to access the memory and peripherals.
     * In the example, all masters are set with the same domain configuration.
     */
    XRDC_SetProcessorDomainAssignment(XRDC, kXRDC_MasterCM0P, 0, &domainConfig);

    /*
     * Configure the peripheral policy.
     */
    XRDC_GetPeriphAccessDefaultConfig(&periConfig);
    periConfig.policy[APP_DOMAIN_ID] = kXRDC_AccessPolicyAll;

    for (i = 0; i < ARRAY_SIZE(periphAccessible); i++)
    {
        periConfig.periph = periphAccessible[i];
        XRDC_SetPeriphAccessConfig(XRDC, &periConfig);
    }

    /*
     * Configure the memory policy.
     */
    /* SRAM */
    XRDC_GetMemAccessDefaultConfig(&memConfig);
    memConfig.mem                   = kXRDC_MemMrc1_0;
    memConfig.baseAddress           = 0x09000000;
    memConfig.endAddress            = 0x0901FFFF;
    memConfig.policy[APP_DOMAIN_ID] = kXRDC_AccessFlagsAlt1;
    memConfig.accset1               = (0x07U << 0U) | (0x07U << 3U) | (0x07U << 6U) | (0x07U << 9U);
    XRDC_SetMemAccessConfig(XRDC, &memConfig);

    /* Flash memory */
    memConfig.mem         = kXRDC_MemMrc1_1;
    memConfig.baseAddress = 0x01000000;
    memConfig.endAddress  = 0x0103FFFF;
    XRDC_SetMemAccessConfig(XRDC, &memConfig);
}

void APP_CheckAndResolvePeriphAccessError(xrdc_error_t *error)
{
    /* LPTMR2 is assigned to AIPS1, so it is controlled by PDAC1. */
    if (error->controller == kXRDC_PeriphController1)
    {
        PRINTF("Violent access at address: 0x%8X\r\n", error->address);

        xrdc_periph_access_config_t periConfig;
        XRDC_GetPeriphAccessDefaultConfig(&periConfig);
        periConfig.periph                = kXRDC_PeriphLptmr2;
        periConfig.policy[APP_DOMAIN_ID] = kXRDC_AccessPolicyAll;
        XRDC_SetPeriphAccessConfig(XRDC, &periConfig);
    }
}

void APP_CheckAndResolveMemoryAccessError(xrdc_error_t *error)
{
    if (error->controller == kXRDC_MemController0)
    {
        PRINTF("Violent access at address: 0x%8X\r\n", error->address);

        xrdc_mem_access_config_t memConfig;
        XRDC_GetMemAccessDefaultConfig(&memConfig);
        memConfig.mem                   = kXRDC_MemMrc0_2;
        memConfig.baseAddress           = MEM_REGION_START;
        memConfig.endAddress            = MEM_REGION_END;
        memConfig.policy[APP_DOMAIN_ID] = kXRDC_AccessFlagsAlt7;
        XRDC_SetMemAccessConfig(XRDC, &memConfig);
    }
}

void APP_SetPeriphUnaccessible(void)
{
    xrdc_periph_access_config_t periConfig;

    XRDC_GetPeriphAccessDefaultConfig(&periConfig);
    periConfig.periph                = kXRDC_PeriphLptmr2;
    periConfig.policy[APP_DOMAIN_ID] = kXRDC_AccessPolicyNone;
    XRDC_SetPeriphAccessConfig(XRDC, &periConfig);
}

void APP_SetMemoryUnaccessible(void)
{
    xrdc_mem_access_config_t memConfig;

    XRDC_GetMemAccessDefaultConfig(&memConfig);
    memConfig.mem                   = kXRDC_MemMrc0_2;
    memConfig.baseAddress           = MEM_REGION_START;
    memConfig.endAddress            = MEM_REGION_END;
    memConfig.policy[APP_DOMAIN_ID] = kXRDC_AccessFlagsNone;
    XRDC_SetMemAccessConfig(XRDC, &memConfig);
}

void APP_TouchPeriph(void)
{
    lptmr_config_t config;

    LPTMR_GetDefaultConfig(&config);

    LPTMR_Init(LPTMR2, &config);
}

void APP_TouchMemory(void)
{
    /* Touch the memory. */
    (*(volatile uint32_t *)MEM_REGION_START)++;
}

/*!
 * @brief HardFault_Handler
 */
void HardFault_Handler(void)
{
    xrdc_error_t error;

    while (kStatus_Success == XRDC_GetAndClearFirstDomainError(XRDC, &error))
    {
        APP_CheckAndResolveMemoryAccessError(&error);
        APP_CheckAndResolvePeriphAccessError(&error);
        g_hardfaultFlag = true;
    }
    __DSB();
}

/*!
 * @brief Main function
 */
int main(void)
{
    /* Init board hardware.*/
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Print the initial banner */
    PRINTF("XRDC example start\r\n");

    /* Init the XRDC configuration, set the domain ID and access policy. */
    APP_SetXrdcConfig();

    /* Set XRDC global valid */
    XRDC_SetGlobalValid(XRDC, true);

    /* Set the unaccessible peripheral. */
    PRINTF("Set the peripheral not accessiable\r\n");
    APP_SetPeriphUnaccessible();

    /* Touch the peripheral, there will be hardfault. */
    g_hardfaultFlag = false;

    APP_TouchPeriph();

    /* Wait for the hardfault occurs. */
    while (!g_hardfaultFlag)
    {
    }
    PRINTF("The peripheral is accessiable now\r\n");

    /* Set the unaccessible memory region. */
    PRINTF("Set the memory not accessiable\r\n");
    APP_SetMemoryUnaccessible();

    /* Touch the memory, there will be hardfault. */
    g_hardfaultFlag = false;

    APP_TouchMemory();

    /* Wait for the hardfault occurs. */
    while (!g_hardfaultFlag)
    {
    }

    PRINTF("The memory is accessiable now\r\n");

    /* XRDC is global invalid */
    XRDC_SetGlobalValid(XRDC, false);

    PRINTF("XRDC example Success\r\n");

    while (1)
    {
    }
}
