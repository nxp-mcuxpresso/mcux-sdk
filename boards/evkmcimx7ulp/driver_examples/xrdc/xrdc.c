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

#include "fsl_wdog32.h"
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

/* The memory for MRC, here use the SRAM1 address. */
#define MEM_REGION_SIZE  kXRDC_MemSize128K
#define MEM_REGION_START 0x2F020000U

#define APP_DOMAIN_ID 1
/*
 * A7 domain ID set to 0, for other masters not set domain ID, the default
 * domain ID is 0.
 */
#define A7_DOMAIN_ID 0


void APP_SetXrdcConfig(void)
{
    uint32_t i;
    xrdc_periph_access_config_t periConfig;
    xrdc_processor_domain_assignment_t domainConfig;
    xrdc_non_processor_domain_assignment_t nonProcDomainConfig;
    xrdc_mem_access_config_t memConfig;

    const xrdc_periph_t periphAccessible[] = {kXRDC_PeriphLpuart0, kXRDC_PeriphXrdc0, kXRDC_PeriphXrdc1,
                                              kXRDC_PeriphXrdc2, kXRDC_PeriphXrdc3};

    /* All peripherals set to accessible for A7. */
    const xrdc_periph_t periphAccessibleA7[] = {
        kXRDC_PeriphEdma0,      kXRDC_PeriphEdma0_tcd,    kXRDC_PeriphRgpio0,     kXRDC_PeriphXrdc0,
        kXRDC_PeriphXrdc1,      kXRDC_PeriphXrdc2,        kXRDC_PeriphXrdc3,      kXRDC_PeriphSema42_0,
        kXRDC_PeriphDmamux0,    kXRDC_PeriphLlwu,         kXRDC_PeriphMu_A,       kXRDC_PeriphTrgmux0,
        kXRDC_PeriphWdog0,      kXRDC_PeriphPcc0,         kXRDC_PeriphScg0,       kXRDC_PeriphCrc,
        kXRDC_PeriphLtc,        kXRDC_PeriphTrng,         kXRDC_PeriphLpit0,      kXRDC_PeriphLptmr0,
        kXRDC_PeriphLptmr1,     kXRDC_PeriphTpm0,         kXRDC_PeriphTpm1,       kXRDC_PeriphFlexio0,
        kXRDC_PeriphLpi2c0,     kXRDC_PeriphLpi2c1,       kXRDC_PeriphLpi2c2,     kXRDC_PeriphLpi2c3,
        kXRDC_PeriphSai0,       kXRDC_PeriphLpspi0,       kXRDC_PeriphLpspi1,     kXRDC_PeriphLpuart0,
        kXRDC_PeriphLpuart1,    kXRDC_PeriphIomuxc0,      kXRDC_PeriphPctlA,      kXRDC_PeriphPctlB,
        kXRDC_PeriphAdc0,       kXRDC_PeriphCmp0,         kXRDC_PeriphCmp1,       kXRDC_PeriphDac0,
        kXRDC_PeriphDac1,       kXRDC_PeriphRomc0,        kXRDC_PeriphDaprom,     kXRDC_PeriphFunnel,
        kXRDC_PeriphEtf,        kXRDC_PeriphTpiu,         kXRDC_PeriphEtr,        kXRDC_PeriphCti,
        kXRDC_PeriphSwo,        kXRDC_PeriphTimestampGen, kXRDC_PeriphA7_apb_rom, kXRDC_PeriphA7_apb_cpu_dbg,
        kXRDC_PeriphA7_apb_pmu, kXRDC_PeriphA7_apb_cti,   kXRDC_PeriphA7_apb_etm, kXRDC_PeriphEwm,
        kXRDC_PeriphPmc0,       kXRDC_PeriphSim,          kXRDC_PeriphCmc0,       kXRDC_PeriphQspi,
        kXRDC_PeriphOcotp_ctrl, kXRDC_PeriphTpm2,         kXRDC_PeriphTpm3,       kXRDC_PeriphSai1,
        kXRDC_PeriphLpuart2,    kXRDC_PeriphLpuart3,      kXRDC_PeriphAdc1,       kXRDC_PeriphPcc1,
        kXRDC_PeriphEdma1,      kXRDC_PeriphEdma1_tcd,    kXRDC_PeriphRgpio1,     kXRDC_PeriphFlexbus,
        kXRDC_PeriphSema42_1,   kXRDC_PeriphDmamux1,      kXRDC_PeriphMu_B,       kXRDC_PeriphSnvs,
        kXRDC_PeriphCaam,       kXRDC_PeriphTpm4,         kXRDC_PeriphTpm5,       kXRDC_PeriphLpit1,
        kXRDC_PeriphLpspi2,     kXRDC_PeriphLpspi3,       kXRDC_PeriphLpi2c4,     kXRDC_PeriphLpi2c5,
        kXRDC_PeriphLpuart4,    kXRDC_PeriphLpuart5,      kXRDC_PeriphFlexio1,    kXRDC_PeriphUsb0,
        kXRDC_PeriphUsb1,       kXRDC_PeriphUsbPhy,       kXRDC_PeriphUsb_pl301,  kXRDC_PeriphUsdhc0,
        kXRDC_PeriphUsdhc1,     kXRDC_PeriphTrgmux1,      kXRDC_PeriphWdog1,      kXRDC_PeriphScg1,
        kXRDC_PeriphPcc2,       kXRDC_PeriphPmc1,         kXRDC_PeriphCmc1,       kXRDC_PeriphWdog2,
        kXRDC_PeriphRomc1,      kXRDC_PeriphTpm6,         kXRDC_PeriphTpm7,       kXRDC_PeriphLpi2c6,
        kXRDC_PeriphLpi2c7,     kXRDC_PeriphLpuart6,      kXRDC_PeriphLpuart7,    kXRDC_PeriphViu,
        kXRDC_PeriphDsi,        kXRDC_PeriphLcdif,        kXRDC_PeriphMmdc,       kXRDC_PeriphIomuxc1,
        kXRDC_PeriphIomuxc_ddr, kXRDC_PeriphPctlC,        kXRDC_PeriphPctlD,      kXRDC_PeriphPctlE,
        kXRDC_PeriphPctlF,      kXRDC_PeriphPcc3,
    };

    /*
     * Wait for MMDC clock be enable by UBOOT before configure XRDC memory region controller (MRC) 6, otherwise M4 will
     * break down during set the MRC 6 related MRGD registers value.
     */
    while (!(PCC3->PCC_MMDC & PCC_CLKCFG_INUSE_MASK))
    {
    }

    XRDC_Init(XRDC);

    /*
     * Configure the access policy for A7, otherwise A7 will break down during
     * the XRDC enabled.
     */
    XRDC_GetDefaultProcessorDomainAssignment(&domainConfig);
    domainConfig.domainId = A7_DOMAIN_ID;
    XRDC_SetProcessorDomainAssignment(XRDC, kXRDC_MasterCA7, 0, &domainConfig);

    /* Set A7 peripheral policy. */
    XRDC_GetPeriphAccessDefaultConfig(&periConfig);
    periConfig.policy[A7_DOMAIN_ID] = kXRDC_AccessPolicyAll;

    for (i = 0; i < ARRAY_SIZE(periphAccessibleA7); i++)
    {
        periConfig.periph = periphAccessibleA7[i];
        XRDC_SetPeriphAccessConfig(XRDC, &periConfig);
    }

    /* ==== Set A7 memory policy. ==== */
    XRDC_GetMemAccessDefaultConfig(&memConfig);

    /* Cortex-M TCM. 0x1FFFD000 to 0x2000FFFF. */
    memConfig.mem                  = kXRDC_MemMrc0_0;
    memConfig.baseAddress          = 0x1FFD0000;
    memConfig.size                 = kXRDC_MemSize64K;
    memConfig.policy[A7_DOMAIN_ID] = kXRDC_AccessPolicyAll;
    XRDC_SetMemAccessConfig(XRDC, &memConfig);
    memConfig.mem                  = kXRDC_MemMrc0_1;
    memConfig.baseAddress          = 0x1FFE0000;
    memConfig.size                 = kXRDC_MemSize128K;
    memConfig.policy[A7_DOMAIN_ID] = kXRDC_AccessPolicyAll;
    XRDC_SetMemAccessConfig(XRDC, &memConfig);
    memConfig.mem                  = kXRDC_MemMrc0_2;
    memConfig.baseAddress          = 0x20000000;
    memConfig.size                 = kXRDC_MemSize64K;
    memConfig.policy[A7_DOMAIN_ID] = kXRDC_AccessPolicyAll;
    XRDC_SetMemAccessConfig(XRDC, &memConfig);

    /* QSPI flash. 0xC0000000 to 0xCFFFFFFF */
    memConfig.mem                  = kXRDC_MemMrc1_0;
    memConfig.baseAddress          = 0xC0000000U;
    memConfig.size                 = kXRDC_MemSize256M;
    memConfig.policy[A7_DOMAIN_ID] = kXRDC_AccessPolicyAll;
    XRDC_SetMemAccessConfig(XRDC, &memConfig);

    /* SRAM0. 0x2F000000 to 0x2F001FFF. */
    memConfig.mem                  = kXRDC_MemMrc2_0;
    memConfig.baseAddress          = 0x2F000000;
    memConfig.size                 = kXRDC_MemSize128K;
    memConfig.policy[A7_DOMAIN_ID] = kXRDC_AccessPolicyAll;
    XRDC_SetMemAccessConfig(XRDC, &memConfig);

    /* srcRAM. 0x26000000 to 0x26007FFF. */
    memConfig.mem                  = kXRDC_MemMrc3_0;
    memConfig.baseAddress          = 0x2F000000;
    memConfig.size                 = kXRDC_MemSize32K;
    memConfig.policy[A7_DOMAIN_ID] = kXRDC_AccessPolicyAll;
    XRDC_SetMemAccessConfig(XRDC, &memConfig);

    /* FlexBus. 0xB0000000 to 0xBFFFFFFF. */
    memConfig.mem                  = kXRDC_MemMrc4_0;
    memConfig.baseAddress          = 0xB0000000;
    memConfig.size                 = kXRDC_MemSize256M;
    memConfig.policy[A7_DOMAIN_ID] = kXRDC_AccessPolicyAll;
    XRDC_SetMemAccessConfig(XRDC, &memConfig);

    /* SRAM1. 0x2F020000 to 0x2F03FFFF. */
    memConfig.mem                  = kXRDC_MemMrc5_0;
    memConfig.baseAddress          = 0x2F020000;
    memConfig.size                 = kXRDC_MemSize128K;
    memConfig.policy[A7_DOMAIN_ID] = kXRDC_AccessPolicyAll;
    XRDC_SetMemAccessConfig(XRDC, &memConfig);

    /* DDR. 0x60000000 to 0x9FFFFFFF. */
    memConfig.mem                  = kXRDC_MemMrc6_0;
    memConfig.baseAddress          = 0x60000000U;
    memConfig.size                 = kXRDC_MemSize512M;
    memConfig.policy[A7_DOMAIN_ID] = kXRDC_AccessPolicyAll;
    XRDC_SetMemAccessConfig(XRDC, &memConfig);
    memConfig.mem                  = kXRDC_MemMrc6_1;
    memConfig.baseAddress          = 0x80000000U;
    memConfig.size                 = kXRDC_MemSize512M;
    memConfig.policy[A7_DOMAIN_ID] = kXRDC_AccessPolicyAll;
    XRDC_SetMemAccessConfig(XRDC, &memConfig);

    /* Configure the domain ID for M4. */
    XRDC_GetDefaultProcessorDomainAssignment(&domainConfig);
    domainConfig.domainId = APP_DOMAIN_ID;
    XRDC_SetProcessorDomainAssignment(XRDC, kXRDC_MasterCM4Code, 0, &domainConfig);
    XRDC_SetProcessorDomainAssignment(XRDC, kXRDC_MasterCM4System, 0, &domainConfig);

    /*
     * Configure the domain ID for master AXBS to NIC1, this path is used by
     * CM4 to access SRAM1
     */
    XRDC_GetDefaultNonProcessorDomainAssignment(&nonProcDomainConfig);
    nonProcDomainConfig.domainId = APP_DOMAIN_ID;
    XRDC_SetNonProcessorDomainAssignment(XRDC, kXRDC_MasterAxbs2NIC1, 0, &nonProcDomainConfig);

    /*
     * Configure the peripheral policy.
     */
    XRDC_GetPeriphAccessDefaultConfig(&periConfig);
    periConfig.policy[APP_DOMAIN_ID] = kXRDC_AccessPolicyAll;
    periConfig.policy[A7_DOMAIN_ID]  = kXRDC_AccessPolicyAll;

    for (i = 0; i < ARRAY_SIZE(periphAccessible); i++)
    {
        periConfig.periph = periphAccessible[i];
        XRDC_SetPeriphAccessConfig(XRDC, &periConfig);
    }

    /*
     * Configure the memory policy.
     * TCM is always accessible for CM4, so don't need to set memory policy.
     * Enable M4 access policy to QuadSPI aliasing memory.
     */
    memConfig.mem                   = kXRDC_MemMrc1_1;
    memConfig.baseAddress           = 0x4000000U;
    memConfig.size                  = kXRDC_MemSize8M;
    memConfig.policy[APP_DOMAIN_ID] = kXRDC_AccessPolicyAll;
    XRDC_SetMemAccessConfig(XRDC, &memConfig);
}

void APP_CheckAndResolvePeriphAccessError(xrdc_error_t *error)
{
    /* WDOG0 is assigned to AIPS0, so it is controlled by PDAC0. */
    if (error->controller == kXRDC_PeriphController0)
    {
        PRINTF("Violent access at address: 0x%8X\r\n", error->address);

        xrdc_periph_access_config_t periConfig;
        XRDC_GetPeriphAccessDefaultConfig(&periConfig);
        periConfig.periph                = kXRDC_PeriphWdog0;
        periConfig.policy[APP_DOMAIN_ID] = kXRDC_AccessPolicyAll;
        periConfig.policy[A7_DOMAIN_ID]  = kXRDC_AccessPolicyAll;
        XRDC_SetPeriphAccessConfig(XRDC, &periConfig);
    }
}

void APP_CheckAndResolveMemoryAccessError(xrdc_error_t *error)
{
    /* SRAM1 is assigned to MRC 5. */
    if (error->controller == kXRDC_MemController5)
    {
        PRINTF("Violent access at address: 0x%8X\r\n", error->address);

        xrdc_mem_access_config_t memConfig;
        XRDC_GetMemAccessDefaultConfig(&memConfig);
        memConfig.mem                   = kXRDC_MemMrc5_0;
        memConfig.baseAddress           = MEM_REGION_START;
        memConfig.size                  = MEM_REGION_SIZE;
        memConfig.policy[APP_DOMAIN_ID] = kXRDC_AccessPolicyAll;
        memConfig.policy[A7_DOMAIN_ID]  = kXRDC_AccessPolicyAll;
        XRDC_SetMemAccessConfig(XRDC, &memConfig);
    }
}

void APP_SetPeriphUnaccessible(void)
{
    xrdc_periph_access_config_t periConfig;

    XRDC_GetPeriphAccessDefaultConfig(&periConfig);
    periConfig.periph                = kXRDC_PeriphWdog0;
    periConfig.policy[APP_DOMAIN_ID] = kXRDC_AccessPolicyNone;
    periConfig.policy[A7_DOMAIN_ID]  = kXRDC_AccessPolicyAll;
    XRDC_SetPeriphAccessConfig(XRDC, &periConfig);
}

void APP_SetMemoryUnaccessible(void)
{
    xrdc_mem_access_config_t memConfig;

    XRDC_GetMemAccessDefaultConfig(&memConfig);
    memConfig.mem                   = kXRDC_MemMrc5_0;
    memConfig.baseAddress           = MEM_REGION_START;
    memConfig.size                  = MEM_REGION_SIZE;
    memConfig.policy[APP_DOMAIN_ID] = kXRDC_AccessPolicyNone;
    memConfig.policy[A7_DOMAIN_ID]  = kXRDC_AccessPolicyAll;
    XRDC_SetMemAccessConfig(XRDC, &memConfig);
}

void APP_TouchPeriph(void)
{
    wdog32_config_t config;
    WDOG32_GetDefaultConfig(&config);
    config.enableWdog32 = false;

    WDOG32_Init(WDOG0, &config);
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
