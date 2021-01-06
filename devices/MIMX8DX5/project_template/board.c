/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2017-2018 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_gpio.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
static sc_ipc_t ipcHandle; /* ipc handle */

/*******************************************************************************
 * Code
 ******************************************************************************/
sc_ipc_t BOARD_InitRpc(void)
{
    /* Initialize the IPC channel to communicate with SCFW */
    SystemInitScfwIpc();

    ipcHandle = SystemGetScfwIpcHandle();
    if (ipcHandle)
    {
        CLOCK_Init(ipcHandle);
    }
    return ipcHandle;
}

sc_ipc_t BOARD_GetRpcHandle(void)
{
    return ipcHandle;
}

/*
 * Pre Configuration of some pins
 *  - Some physical pins default map to the same functionality and has priority, avoid such conflict
 *    at the beginning.
 */
void BOARD_InitPinsPre(void)
{
    sc_err_t err = SC_ERR_NONE;

    err = sc_pad_set_mux(ipcHandle, SC_P_USB_SS3_TC0, 3U, SC_PAD_CONFIG_NORMAL, SC_PAD_ISO_OFF);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    err = sc_pad_set_mux(ipcHandle, SC_P_USB_SS3_TC1, 3U, SC_PAD_CONFIG_NORMAL, SC_PAD_ISO_OFF);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    err = sc_pad_set_mux(ipcHandle, SC_P_USB_SS3_TC2, 3U, SC_PAD_CONFIG_NORMAL, SC_PAD_ISO_OFF);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    err = sc_pad_set_mux(ipcHandle, SC_P_USB_SS3_TC3, 3U, SC_PAD_CONFIG_NORMAL, SC_PAD_ISO_OFF);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }
}

/* Initialize debug console. */
void BOARD_InitDebugConsole(void)
{
    uint32_t freq = SC_133MHZ;

    /* Power on Local LPUART for M4 Core0. */
    sc_pm_set_resource_power_mode(ipcHandle, SC_R_M4_0_UART, SC_PM_PW_MODE_ON);
    /* Enable clock of Local LPUART for M4 Core0. */
    CLOCK_EnableClockExt(kCLOCK_M4_0_Lpuart, 0);
    /* Set clock Frequncy of Local LPUART for M4 Core0. */
    freq = CLOCK_SetIpFreq(kCLOCK_M4_0_Lpuart, freq);

    /* Initialize Debug Console using local LPUART for M4 Core0. */
    DbgConsole_Init(BOARD_DEBUG_UART_BASEADDR, BOARD_DEBUG_UART_BAUDRATE, BOARD_DEBUG_UART_TYPE, freq);
}

/* Power on base board*/
void BOARD_PowerOnBaseBoard(void)
{
    sc_err_t err = SC_ERR_NONE;
    gpio_pin_config_t pin_config;

    if (sc_pm_set_resource_power_mode(ipcHandle, SC_R_GPIO_5, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
    {
        assert(false);
    }

    if (!CLOCK_EnableClockExt(kCLOCK_LSIO_Gpio5, 0))
        assert(false);

    /*Configure BB_PWR_EN GPIO pin*/
    pin_config.direction = kGPIO_DigitalOutput;
    pin_config.outputLogic = 1U;
    pin_config.interruptMode = kGPIO_NoIntmode;

    err = sc_pad_set_mux(ipcHandle, SC_P_ENET0_REFCLK_125M_25M, 4U, SC_PAD_CONFIG_NORMAL, SC_PAD_ISO_OFF);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    GPIO_PinInit(BOARD_BASEBOARD_PWR_GPIO, BOARD_BASEBOARD_PWR_GPIO_PIN, &pin_config);
    GPIO_PinWrite(BOARD_BASEBOARD_PWR_GPIO, BOARD_BASEBOARD_PWR_GPIO_PIN, 1U);
}

/* Initialize MPU, configure non-cacheable memory */
void BOARD_InitMemory(void)
{
    extern uint32_t __CACHE_REGION_START[];
    extern uint32_t __CACHE_REGION_SIZE[];
    uint32_t cacheStart = (uint32_t)__CACHE_REGION_START;
    uint32_t size = (uint32_t)__CACHE_REGION_SIZE;
    uint32_t i = 0;
    /* Make sure outstanding transfers are done. */
    __DMB();
    /* Disable the MPU. */
    MPU->CTRL = 0;

    /* 
       The ARMv7-M default address map define the address space 0x20000000 to 0x3FFFFFFF as SRAM with Normal type, but there the address
       space 0x28000000 ~ 0x3FFFFFFF has been physically mapped to smart subsystems, so there need change the default memory attributes.
       Since the base address of MPU region should be multiples of region size, to make it simple, the MPU region 0 set the all 512M of SRAM space
       with device attributes, then disable subregion 0 and 1 (address space 0x20000000 ~ 0x27FFFFFF) to use the background memory attributes。
    */

    /* Select Region 0 and set its base address to the M4 code bus start address. */
    MPU->RBAR = (0x20000000U & MPU_RBAR_ADDR_Msk) | MPU_RBAR_VALID_Msk | (0 << MPU_RBAR_REGION_Pos);

    /* Region 0 setting:
    * 1) Enable Instruction Access;
    * 2) AP = 011b, full access;
    * 3) Non-shared device;
    * 4) Region Not Shared;
    * 5) Sub-Region 0,1 Disabled;
    * 6) MPU Protection Region size = 512M byte;
    * 7) Enable Region 0.
    */
    MPU->RASR = (0x1 << MPU_RASR_XN_Pos) | (0x3 << MPU_RASR_AP_Pos) | (0x2 << MPU_RASR_TEX_Pos) |
                (0x3 << MPU_RASR_SRD_Pos) | (28 << MPU_RASR_SIZE_Pos) | MPU_RASR_ENABLE_Msk;

    /* 
       Non-cacheable area is provided in DDR memory, the DDR region 2MB - 128MB totally 126MB is revserved for CM4 cores. 
       You can put global or static uninitialized variables in NonCacheable section(initialized variables in NonCacheable.init section)
       to make them uncacheable. Since the base address of MPU region should be multiples of region size, to make it simple, 
       the MPU region 1 set the address space 0x80000000 ~ 0xFFFFFFFF to be non-cacheable(disable sub-region 6,7 to use the background memory 
       attributes for address space 0xE0000000 ~ 0xFFFFFFFF). Then MPU region 2 set the text and data section to be cacheable if the program running
       on DDR. The cacheable area base address should be multiples of its size in linker file, they can be modified per your needs.
    */

    /* Select Region 1 and set its base address to the DDR start address. */
    MPU->RBAR = (0x80000000U & MPU_RBAR_ADDR_Msk) | MPU_RBAR_VALID_Msk | (1 << MPU_RBAR_REGION_Pos);

    /* Region 1 setting:
    * 1) Enable Instruction Access;
    * 2) AP = 011b, full access;
    * 3) Shared Device;
    * 4) Sub-Region 6,7 Disabled;
    * 5) MPU Protection Region size = 2048M byte;
    * 6) Enable Region 1.
    */
    MPU->RASR = (0x3 << MPU_RASR_AP_Pos) | (0x1 << MPU_RASR_B_Pos) | (0xC0 << MPU_RASR_SRD_Pos) |
                (30 << MPU_RASR_SIZE_Pos) | MPU_RASR_ENABLE_Msk;

    while ((size >> i) > 0x1U)
    {
        i++;
    }

    /* If run on DDR, configure text and data section to be cacheable */
    if (i != 0)
    {
        /* The MPU region size should be 2^N, 5<=N<=32, region base should be multiples of size. */
        assert((size & (size - 1)) == 0);
        assert(!(cacheStart % size));
        assert(size == (uint32_t)(1 << i));
        assert(i >= 5);

        /* Select Region 2 and set its base address to the cache able region start address. */
        MPU->RBAR = (cacheStart & MPU_RBAR_ADDR_Msk) | MPU_RBAR_VALID_Msk | (2 << MPU_RBAR_REGION_Pos);

        /* Region 2 setting:
        * 1) Enable Instruction Access;
        * 2) AP = 011b, full access;
        * 3) Outer and inner Cacheable, write and read allocate;
        * 4) Region Not Shared;
        * 5) All Sub-Region Enabled;
        * 6) MPU Protection Region size get from linker file;
        * 7) Enable Region 2.
        */
        MPU->RASR = (0x3 << MPU_RASR_AP_Pos) | (0x1 << MPU_RASR_TEX_Pos) | (0x1 << MPU_RASR_C_Pos) |
                    (0x1 << MPU_RASR_B_Pos) | ((i - 1) << MPU_RASR_SIZE_Pos) | MPU_RASR_ENABLE_Msk;
    }

    /* Enable Privileged default memory map and the MPU. */
    MPU->CTRL = MPU_CTRL_ENABLE_Msk | MPU_CTRL_PRIVDEFENA_Msk;
    /* Memory barriers to ensure subsequence data & instruction
    * transfers using updated MPU settings.
    */
    __DSB();
    __ISB();
}
