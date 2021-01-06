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
#include "board.h"
#include "fsl_debug_console.h"

#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_xrdc.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define LED_INIT()          LED1_INIT(LOGIC_LED_ON)
#define APP_MU              MUA
#define APP_SEMA42          SEMA420
#define APP_CORE1_BOOT_MODE kMU_CoreBootFromDflashBase
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
void APP_InitDomain(void);
void APP_DeinitDomain(void);
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
void APP_InitDomain(void)
{
    /*
     * This function assigns core 0 (CM4) to domain 0, assigns core 1 (CM0+)
     * to domain 1. Then sets the necessary memory and peripheral permission.
     */

    uint32_t i;
    xrdc_periph_access_config_t periConfig;
    xrdc_processor_domain_assignment_t domainConfig;
    xrdc_mem_access_config_t memConfig;

    const xrdc_periph_t periphAccessible[] = {
        kXRDC_PeriphLpuart0, kXRDC_PeriphWdog0,   kXRDC_PeriphXrdcMgr, kXRDC_PeriphXrdcMdac, kXRDC_PeriphXrdcPac,
        kXRDC_PeriphXrdcMrc, kXRDC_PeriphSema420, kXRDC_PeriphSema421, kXRDC_PeriphWdog1,    kXRDC_PeriphPcc0,
        kXRDC_PeriphPcc1,    kXRDC_PeriphMua,     kXRDC_PeriphMub};

    XRDC_Init(XRDC);
    XRDC_SetGlobalValid(XRDC, false);

    /* Assign CM4 to domain 0. */
    XRDC_GetDefaultProcessorDomainAssignment(&domainConfig);
    domainConfig.domainId = 0;
    XRDC_SetProcessorDomainAssignment(XRDC, kXRDC_MasterCM4CodeBus, 0, &domainConfig);
    XRDC_SetProcessorDomainAssignment(XRDC, kXRDC_MasterCM4SystemBus, 0, &domainConfig);

    /* Assign CM0+ to domain 1. */
    domainConfig.domainId = 1;
    XRDC_SetProcessorDomainAssignment(XRDC, kXRDC_MasterCM0P, 0, &domainConfig);

    /*
     * Configure the peripheral policy.
     */
    XRDC_GetPeriphAccessDefaultConfig(&periConfig);
    /* Access permission for domain 0. */
    periConfig.policy[0] = kXRDC_AccessPolicyAll;
    /* Access permission for domain 1. */
    periConfig.policy[1] = kXRDC_AccessPolicyAll;

    for (i = 0; i < ARRAY_SIZE(periphAccessible); i++)
    {
        periConfig.periph = periphAccessible[i];
        XRDC_SetPeriphAccessConfig(XRDC, &periConfig);
    }

    /* Configure the memory policy. */
    XRDC_GetMemAccessDefaultConfig(&memConfig);
    /* CM4 flash is CM4 code region. */
    memConfig.mem         = kXRDC_MemMrc0_0;
    memConfig.baseAddress = 0x00000000U;
    memConfig.endAddress  = 0x000FFFFFU;
    memConfig.codeRegion  = kXRDC_MemCodeRegion1;
    memConfig.policy[0]   = kXRDC_AccessFlagsAlt4;
    memConfig.policy[1]   = kXRDC_AccessFlagsNone;
    XRDC_SetMemAccessConfig(XRDC, &memConfig);

    /* CM0+ flash is CM0+ code region. */
    memConfig.mem         = kXRDC_MemMrc1_0;
    memConfig.baseAddress = 0x01000000U;
    memConfig.endAddress  = 0x0103FFFFU;
    memConfig.codeRegion  = kXRDC_MemCodeRegion1;
    memConfig.policy[0]   = kXRDC_AccessFlagsNone;
    memConfig.policy[1]   = kXRDC_AccessFlagsAlt4;
    XRDC_SetMemAccessConfig(XRDC, &memConfig);

    /* CM4 ITCM SRAM, code might be placed here. */
    memConfig.mem         = kXRDC_MemMrc0_1;
    memConfig.baseAddress = 0x08000000U;
    memConfig.endAddress  = 0x0800FFFFU;
    memConfig.codeRegion  = kXRDC_MemCodeRegion1;
    memConfig.policy[0]   = kXRDC_AccessFlagsAlt4;
    memConfig.policy[1]   = kXRDC_AccessFlagsNone;
    XRDC_SetMemAccessConfig(XRDC, &memConfig);

    /* Boot ROM. */
    memConfig.mem         = kXRDC_MemMrc0_2;
    memConfig.baseAddress = 0x08800000U;
    memConfig.endAddress  = 0x0880BFFFU;
    memConfig.codeRegion  = kXRDC_MemCodeRegion1;
    memConfig.policy[0]   = kXRDC_AccessFlagsAlt4;
    memConfig.policy[1]   = kXRDC_AccessFlagsAlt4;
    XRDC_SetMemAccessConfig(XRDC, &memConfig);

    /* CM0+ TCM SRAM. */
    memConfig.mem         = kXRDC_MemMrc1_1;
    memConfig.baseAddress = 0x09000000U;
    memConfig.endAddress  = 0x0901FFFFU;
    memConfig.codeRegion  = kXRDC_MemCodeRegion1;
    memConfig.policy[0]   = kXRDC_AccessFlagsNone;
    memConfig.policy[1]   = kXRDC_AccessFlagsAlt4;
    XRDC_SetMemAccessConfig(XRDC, &memConfig);

    /* CM0+ CTI, for debugger. */
    memConfig.mem         = kXRDC_MemMrc1_2;
    memConfig.baseAddress = 0xF0006000U;
    memConfig.endAddress  = 0xF0006FFFU;
    memConfig.codeRegion  = kXRDC_MemCodeRegion0;
    memConfig.policy[0]   = kXRDC_AccessFlagsNone;
    memConfig.policy[1]   = kXRDC_AccessFlagsAlt4;
    XRDC_SetMemAccessConfig(XRDC, &memConfig);

    /* CM4 DTCM SRAM, data region. */
    memConfig.mem         = kXRDC_MemMrc0_3;
    memConfig.baseAddress = 0x20000000U;
    memConfig.endAddress  = 0x2001FFFFU;
    memConfig.codeRegion  = kXRDC_MemCodeRegion0;
    memConfig.policy[0]   = kXRDC_AccessFlagsAlt4;
    memConfig.policy[1]   = kXRDC_AccessFlagsNone;
    XRDC_SetMemAccessConfig(XRDC, &memConfig);

    memConfig.mem         = kXRDC_MemMrc0_4;
    memConfig.baseAddress = 0x20020000U;
    memConfig.endAddress  = 0x2003FFFFU;
    memConfig.codeRegion  = kXRDC_MemCodeRegion0;
    memConfig.policy[0]   = kXRDC_AccessFlagsAlt4;
    memConfig.policy[1]   = kXRDC_AccessFlagsNone;
    XRDC_SetMemAccessConfig(XRDC, &memConfig);

    XRDC_SetGlobalValid(XRDC, true);
}

void APP_DeinitDomain(void)
{
    XRDC_SetGlobalValid(XRDC, false);
}

static void BOARD_InitLedPin(void)
{
    const gpio_pin_config_t config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic  = 1,
    };

    GPIO_PinInit(BOARD_LED1_GPIO, BOARD_LED1_GPIO_PIN, &config);
}

/*!
 * @brief Main function
 */
int main(void)
{
    uint8_t domainId;
    /* Init board hardware.*/
    BOARD_InitPins_Core0();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    BOARD_InitLedPin();
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
