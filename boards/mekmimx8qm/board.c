/*
 * Copyright 2017-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_gpio.h"
#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
#include "fsl_lpi2c.h"
#endif /* SDK_I2C_BASED_COMPONENT_USED */
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

    /*
     * Current core reports it is done to SCFW when early boot mode is enabled.
     * This mode is used to minimize the time from POR to M4 execution for some specific fast-boot use-cases.
     * Please refer to Boot Flow chapter of System Controller Firmware Porting Guide document for more information.
     */
    if (sc_misc_boot_done(ipcHandle, BOARD_M4_CPU_RSRC) != SC_ERR_NONE)
    {
        assert(0);
    }
    return ipcHandle;
}

/* Initialize debug console. */
void BOARD_InitDebugConsole(void)
{
    uint32_t freq = SC_24MHZ;

    /* Power on Local LPUART for M4. */
    sc_pm_set_resource_power_mode(ipcHandle, BOARD_DEBUG_UART_SC_RSRC, SC_PM_PW_MODE_ON);
    /* Enable clock of Local LPUART for M4. */
    CLOCK_EnableClockExt(BOARD_DEBUG_UART_CLKSRC, 0);
    /* Set clock Frequncy of Local LPUART for M4. */
    freq = CLOCK_SetIpFreq(BOARD_DEBUG_UART_CLKSRC, freq);

    /* Initialize Debug Console using local LPUART for M4. */
    DbgConsole_Init(BOARD_DEBUG_UART_INSTANCE, BOARD_DEBUG_UART_BAUDRATE, BOARD_DEBUG_UART_TYPE, freq);
}

/* Initialize MPU, configure non-cacheable memory */
void BOARD_InitMemory(void)
{
#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
    extern uint32_t Load$$LR$$LR_cache_region$$Base[];
    extern uint32_t Image$$ARM_LIB_STACK$$ZI$$Limit[];
    uint32_t cacheStart = (uint32_t)Load$$LR$$LR_cache_region$$Base;
    uint32_t size       = (cacheStart < 0x20000000U) ? (0) : ((uint32_t)Image$$ARM_LIB_STACK$$ZI$$Limit - cacheStart);
#else
    extern uint32_t __CACHE_REGION_START[];
    extern uint32_t __CACHE_REGION_SIZE[];
    uint32_t cacheStart = (uint32_t)__CACHE_REGION_START;
    uint32_t size       = (uint32_t)__CACHE_REGION_SIZE;
#endif
    uint32_t i = 0;
    /* Make sure outstanding transfers are done. */
    __DMB();
    /* Disable the MPU. */
    MPU->CTRL = 0;

    /*
       The ARMv7-M default address map define the address space 0x20000000 to 0x3FFFFFFF as SRAM with Normal type, but
       there the address
       space 0x28000000 ~ 0x3FFFFFFF has been physically mapped to smart subsystems, so there need change the default
       memory attributes.
       Since the base address of MPU region should be multiples of region size, to make it simple, the MPU region 0 set
       the all 512M of SRAM space
       with device attributes, then disable subregion 0 and 1 (address space 0x20000000 ~ 0x27FFFFFF) to use the
       background memory attributes.
    */

    /* Select Region 0 and set its base address to the M4 code bus start address. */
    MPU->RBAR = (0x20000000U & MPU_RBAR_ADDR_Msk) | MPU_RBAR_VALID_Msk | (0 << MPU_RBAR_REGION_Pos);

    /* Region 0 setting:
     * 1) Disable Instruction Access;
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
       Non-cacheable area is provided in DDR memory, the DDR region 2MB - 128MB totally 126MB is revserved for CM4
       cores.
       You can put global or static uninitialized variables in NonCacheable section(initialized variables in
       NonCacheable.init section)
       to make them uncacheable. Since the base address of MPU region should be multiples of region size, to make it
       simple,
       the MPU region 1 set the address space 0x80000000 ~ 0xFFFFFFFF to be non-cacheable(disable sub-region 6,7 to use
       the background memory
       attributes for address space 0xE0000000 ~ 0xFFFFFFFF). Then MPU region 2 set the text and data section to be
       cacheable if the program running
       on DDR. The cacheable area base address should be multiples of its size in linker file, they can be modified per
       your needs.
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

#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
void BOARD_LPI2C_Init(LPI2C_Type *base, uint32_t clkSrc_Hz)
{
    lpi2c_master_config_t lpi2cConfig = {0};

    /*
     * lpi2cConfig.debugEnable = false;
     * lpi2cConfig.ignoreAck = false;
     * lpi2cConfig.pinConfig = kLPI2C_2PinOpenDrain;
     * lpi2cConfig.baudRate_Hz = 100000U;
     * lpi2cConfig.busIdleTimeout_ns = 0;
     * lpi2cConfig.pinLowTimeout_ns = 0;
     * lpi2cConfig.sdaGlitchFilterWidth_ns = 0;
     * lpi2cConfig.sclGlitchFilterWidth_ns = 0;
     */
    LPI2C_MasterGetDefaultConfig(&lpi2cConfig);
    LPI2C_MasterInit(base, &lpi2cConfig, clkSrc_Hz);
}

void BOARD_LPI2C_Deinit(LPI2C_Type *base)
{
    LPI2C_MasterDeinit(base);
}

status_t BOARD_LPI2C_Send(LPI2C_Type *base,
                          uint8_t deviceAddress,
                          uint32_t subAddress,
                          uint8_t subAddressSize,
                          uint8_t *txBuff,
                          uint8_t txBuffSize)
{
    lpi2c_master_transfer_t xfer;

    xfer.flags          = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress   = deviceAddress;
    xfer.direction      = kLPI2C_Write;
    xfer.subaddress     = subAddress;
    xfer.subaddressSize = subAddressSize;
    xfer.data           = txBuff;
    xfer.dataSize       = txBuffSize;

    return LPI2C_MasterTransferBlocking(base, &xfer);
}

status_t BOARD_LPI2C_SendWithoutSubAddr(LPI2C_Type *base,
                                        uint32_t baudRate_Hz,
                                        uint8_t deviceAddress,
                                        uint8_t *txBuff,
                                        uint8_t txBuffSize,
                                        uint8_t needStop)
{
    status_t reVal;
    size_t txCount = 0xFFU;
    size_t txSize  = 0;
    /* 9 I2C SCLK cycles in us, get the next larger integer if can not be divided with no remainder to retain enough
     * time*/
    uint32_t delay = (9000000U + baudRate_Hz - 1U) / baudRate_Hz;

    /* Send master blocking data to slave. */
    reVal = LPI2C_MasterStart(base, deviceAddress, kLPI2C_Write);
    if (kStatus_Success == reVal)
    {
        /* Wait I2C master tx FIFO empty. */
        while (txCount)
        {
            LPI2C_MasterGetFifoCounts(base, NULL, &txCount);
        }
        /* Wait for 9 cycle to ensure the ack/nack cycle ends. */
        SDK_DelayAtLeastUs(delay, SystemCoreClock);
        /* Check communicate with slave successful or not */
        if (LPI2C_MasterGetStatusFlags(base) & kLPI2C_MasterNackDetectFlag)
        {
            return kStatus_LPI2C_Nak;
        }

        /* Check each response from slave. */
        for (txSize = 0; txSize < txBuffSize; txSize++)
        {
            reVal = LPI2C_MasterSend(base, &txBuff[txSize], 1);
            /* Wait tx FIFO empty. */
            LPI2C_MasterGetFifoCounts(base, NULL, &txCount);
            while (txCount)
            {
                LPI2C_MasterGetFifoCounts(base, NULL, &txCount);
            }
            /* Wait for 9 cycle to ensure the ack/nack cycle ends. */
            SDK_DelayAtLeastUs(delay, SystemCoreClock);
            /* Check communicate with slave successful or not */
            if (LPI2C_MasterGetStatusFlags(base) & kLPI2C_MasterNackDetectFlag)
            {
                return kStatus_LPI2C_Nak;
            }
        }

        if (reVal != kStatus_Success)
        {
            return reVal;
        }

        if (needStop)
        {
            reVal = LPI2C_MasterStop(base);
            if (reVal != kStatus_Success)
            {
                return reVal;
            }
        }
    }

    return reVal;
}

status_t BOARD_LPI2C_Receive(LPI2C_Type *base,
                             uint8_t deviceAddress,
                             uint32_t subAddress,
                             uint8_t subAddressSize,
                             uint8_t *rxBuff,
                             uint8_t rxBuffSize)
{
    lpi2c_master_transfer_t xfer;

    xfer.flags          = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress   = deviceAddress;
    xfer.direction      = kLPI2C_Read;
    xfer.subaddress     = subAddress;
    xfer.subaddressSize = subAddressSize;
    xfer.data           = rxBuff;
    xfer.dataSize       = rxBuffSize;

    return LPI2C_MasterTransferBlocking(base, &xfer);
}

status_t BOARD_LPI2C_ReceiveWithoutSubAddr(
    LPI2C_Type *base, uint32_t baudRate_Hz, uint8_t deviceAddress, uint8_t *rxBuff, uint8_t rxBuffSize, uint8_t flags)
{
    status_t reVal;
    size_t txCount = 0xFFU;
    /* 9 I2C SCLK cycles in us, get the next larger integer if can not be divided with no remainder to retain enough
     * time*/
    uint32_t delay = (9000000U + baudRate_Hz - 1U) / baudRate_Hz;

    reVal = LPI2C_MasterStart(base, deviceAddress, kLPI2C_Read);
    if (kStatus_Success == reVal)
    {
        /* Wait I2C master tx FIFO empty. */
        while (txCount)
        {
            LPI2C_MasterGetFifoCounts(base, NULL, &txCount);
        }
        /* Wait for 9 cycle to ensure the ack/nack cycle ends. */
        SDK_DelayAtLeastUs(delay, SystemCoreClock);
        /* Check communicate with slave successful or not. */
        if (LPI2C_MasterGetStatusFlags(base) & kLPI2C_MasterNackDetectFlag)
        {
            return kStatus_LPI2C_Nak;
        }

        reVal = LPI2C_MasterReceive(base, rxBuff, rxBuffSize);
        if (reVal != kStatus_Success)
        {
            return reVal;
        }

        reVal = LPI2C_MasterStop(base);
        if (reVal != kStatus_Success)
        {
            return reVal;
        }
    }
    return reVal;
}

status_t BOARD_LPI2C_SendSCCB(LPI2C_Type *base,
                              uint8_t deviceAddress,
                              uint32_t subAddress,
                              uint8_t subAddressSize,
                              uint8_t *txBuff,
                              uint8_t txBuffSize)
{
    lpi2c_master_transfer_t xfer;

    xfer.flags          = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress   = deviceAddress;
    xfer.direction      = kLPI2C_Write;
    xfer.subaddress     = subAddress;
    xfer.subaddressSize = subAddressSize;
    xfer.data           = txBuff;
    xfer.dataSize       = txBuffSize;

    return LPI2C_MasterTransferBlocking(base, &xfer);
}

status_t BOARD_LPI2C_ReceiveSCCB(LPI2C_Type *base,
                                 uint8_t deviceAddress,
                                 uint32_t subAddress,
                                 uint8_t subAddressSize,
                                 uint8_t *rxBuff,
                                 uint8_t rxBuffSize)
{
    status_t status;
    lpi2c_master_transfer_t xfer;

    xfer.flags          = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress   = deviceAddress;
    xfer.direction      = kLPI2C_Write;
    xfer.subaddress     = subAddress;
    xfer.subaddressSize = subAddressSize;
    xfer.data           = NULL;
    xfer.dataSize       = 0;

    status = LPI2C_MasterTransferBlocking(base, &xfer);

    if (kStatus_Success == status)
    {
        xfer.subaddressSize = 0;
        xfer.direction      = kLPI2C_Read;
        xfer.data           = rxBuff;
        xfer.dataSize       = rxBuffSize;

        status = LPI2C_MasterTransferBlocking(base, &xfer);
    }

    return status;
}

void BOARD_Display0_I2C_Init(void)
{
    uint32_t lpi2cClkFreq_Hz = SC_24MHZ;
    sc_err_t err             = SC_ERR_NONE;
    sc_ipc_t ipc             = SystemGetScfwIpcHandle();

    err = sc_pm_set_resource_power_mode(ipc, SC_R_MIPI_0_I2C_0, SC_PM_PW_MODE_ON);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }
    err = sc_pm_set_clock_rate(ipc, SC_R_MIPI_0_I2C_0, SC_PM_CLK_PER, &lpi2cClkFreq_Hz);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }
    BOARD_LPI2C_Init(BOARD_DISPLAY0_I2C_BASEADDR, lpi2cClkFreq_Hz);
}

void BOARD_Display0_I2C_Deinit(void)
{
    sc_err_t err = SC_ERR_NONE;
    sc_ipc_t ipc = SystemGetScfwIpcHandle();

    BOARD_LPI2C_Deinit(BOARD_DISPLAY0_I2C_BASEADDR);

    err = sc_pm_set_resource_power_mode(ipc, SC_R_MIPI_0_I2C_0, SC_PM_PW_MODE_OFF);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }
}

void BOARD_Display1_I2C_Init(void)
{
    uint32_t lpi2cClkFreq_Hz = SC_24MHZ;
    sc_err_t err             = SC_ERR_NONE;
    sc_ipc_t ipc             = SystemGetScfwIpcHandle();

    err = sc_pm_set_resource_power_mode(ipc, SC_R_MIPI_1_I2C_0, SC_PM_PW_MODE_ON);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }
    err = sc_pm_set_clock_rate(ipc, SC_R_MIPI_1_I2C_0, SC_PM_CLK_PER, &lpi2cClkFreq_Hz);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }
    BOARD_LPI2C_Init(BOARD_DISPLAY1_I2C_BASEADDR, lpi2cClkFreq_Hz);
}

void BOARD_Display1_I2C_Deinit(void)
{
    sc_err_t err = SC_ERR_NONE;
    sc_ipc_t ipc = SystemGetScfwIpcHandle();

    BOARD_LPI2C_Deinit(BOARD_DISPLAY1_I2C_BASEADDR);

    err = sc_pm_set_resource_power_mode(ipc, SC_R_MIPI_1_I2C_0, SC_PM_PW_MODE_OFF);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }
}

void BOARD_Display2_I2C_Init(void)
{
    uint32_t lpi2cClkFreq_Hz = SC_24MHZ;
    sc_err_t err             = SC_ERR_NONE;
    sc_ipc_t ipc             = SystemGetScfwIpcHandle();

    err = sc_pm_set_resource_power_mode(ipc, SC_R_LVDS_0_I2C_0, SC_PM_PW_MODE_ON);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }
    err = sc_pm_set_clock_rate(ipc, SC_R_LVDS_0_I2C_0, SC_PM_CLK_PER, &lpi2cClkFreq_Hz);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    BOARD_LPI2C_Init(BOARD_DISPLAY2_I2C_BASEADDR, lpi2cClkFreq_Hz);
}

void BOARD_Display2_I2C_Deinit(void)
{
    sc_err_t err = SC_ERR_NONE;
    sc_ipc_t ipc = SystemGetScfwIpcHandle();

    BOARD_LPI2C_Deinit(BOARD_DISPLAY2_I2C_BASEADDR);

    err = sc_pm_set_resource_power_mode(ipc, SC_R_LVDS_0_I2C_0, SC_PM_PW_MODE_OFF);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }
}

void BOARD_Display3_I2C_Init(void)
{
    /* Display 2 & 3 uses the same I2C. */
    BOARD_Display2_I2C_Init();
}

void BOARD_Display3_I2C_Deinit(void)
{
    /* Display 2 & 3 uses the same I2C. */
    BOARD_Display2_I2C_Deinit();
}

void BOARD_Display4_I2C_Init(void)
{
    uint32_t lpi2cClkFreq_Hz = SC_24MHZ;
    sc_err_t err             = SC_ERR_NONE;
    sc_ipc_t ipc             = SystemGetScfwIpcHandle();

    err = sc_pm_set_resource_power_mode(ipc, SC_R_LVDS_1_I2C_0, SC_PM_PW_MODE_ON);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }
    err = sc_pm_set_clock_rate(ipc, SC_R_LVDS_1_I2C_0, SC_PM_CLK_PER, &lpi2cClkFreq_Hz);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }
    BOARD_LPI2C_Init(BOARD_DISPLAY4_I2C_BASEADDR, lpi2cClkFreq_Hz);
}

void BOARD_Display4_I2C_Deinit(void)
{
    sc_err_t err = SC_ERR_NONE;
    sc_ipc_t ipc = SystemGetScfwIpcHandle();

    BOARD_LPI2C_Deinit(BOARD_DISPLAY4_I2C_BASEADDR);

    err = sc_pm_set_resource_power_mode(ipc, SC_R_LVDS_1_I2C_0, SC_PM_PW_MODE_OFF);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }
}

void BOARD_Display5_I2C_Init(void)
{
    /* Display 4 & 5 uses the same I2C. */
    BOARD_Display4_I2C_Init();
}

void BOARD_Display5_I2C_Deinit(void)
{
    /* Display 4 & 5 uses the same I2C. */
    BOARD_Display4_I2C_Deinit();
}

status_t BOARD_Display0_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize)
{
    return BOARD_LPI2C_Send(BOARD_DISPLAY0_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, (uint8_t *)txBuff,
                            txBuffSize);
}

status_t BOARD_Display0_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize)
{
    return BOARD_LPI2C_Receive(BOARD_DISPLAY0_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, rxBuff,
                               rxBuffSize);
}

status_t BOARD_Display1_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize)
{
    return BOARD_LPI2C_Send(BOARD_DISPLAY1_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, (uint8_t *)txBuff,
                            txBuffSize);
}

status_t BOARD_Display1_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize)
{
    return BOARD_LPI2C_Receive(BOARD_DISPLAY1_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, rxBuff,
                               rxBuffSize);
}

status_t BOARD_Display2_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize)
{
    return BOARD_LPI2C_Send(BOARD_DISPLAY2_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, (uint8_t *)txBuff,
                            txBuffSize);
}

status_t BOARD_Display2_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize)
{
    return BOARD_LPI2C_Receive(BOARD_DISPLAY2_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, rxBuff,
                               rxBuffSize);
}

status_t BOARD_Display3_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize)
{
    return BOARD_LPI2C_Send(BOARD_DISPLAY3_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, (uint8_t *)txBuff,
                            txBuffSize);
}

status_t BOARD_Display3_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize)
{
    return BOARD_LPI2C_Receive(BOARD_DISPLAY3_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, rxBuff,
                               rxBuffSize);
}

status_t BOARD_Display4_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize)
{
    return BOARD_LPI2C_Send(BOARD_DISPLAY4_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, (uint8_t *)txBuff,
                            txBuffSize);
}

status_t BOARD_Display4_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize)
{
    return BOARD_LPI2C_Receive(BOARD_DISPLAY4_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, rxBuff,
                               rxBuffSize);
}

status_t BOARD_Display5_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize)
{
    return BOARD_LPI2C_Send(BOARD_DISPLAY5_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, (uint8_t *)txBuff,
                            txBuffSize);
}

status_t BOARD_Display5_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize)
{
    return BOARD_LPI2C_Receive(BOARD_DISPLAY5_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, rxBuff,
                               rxBuffSize);
}

void BOARD_Camera0_I2C_Init(void)
{
    uint32_t lpi2cClkFreq_Hz = SC_24MHZ;
    sc_err_t err             = SC_ERR_NONE;
    sc_ipc_t ipc             = SystemGetScfwIpcHandle();

    err = sc_pm_set_resource_power_mode(ipc, BOARD_CAMERA0_I2C_RSRC, SC_PM_PW_MODE_ON);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    err = sc_pm_set_clock_rate(ipc, BOARD_CAMERA0_I2C_RSRC, SC_PM_CLK_PER, &lpi2cClkFreq_Hz);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    lpi2c_master_config_t lpi2cConfig = {0};
    /*
     * lpi2cConfig.debugEnable = false;
     * lpi2cConfig.ignoreAck = false;
     * lpi2cConfig.pinConfig = kLPI2C_2PinOpenDrain;
     * lpi2cConfig.baudRate_Hz = 100000U;
     * lpi2cConfig.busIdleTimeout_ns = 0;
     * lpi2cConfig.pinLowTimeout_ns = 0;
     * lpi2cConfig.sdaGlitchFilterWidth_ns = 0;
     * lpi2cConfig.sclGlitchFilterWidth_ns = 0;
     */
    LPI2C_MasterGetDefaultConfig(&lpi2cConfig);
    lpi2cConfig.baudRate_Hz = 400000U;
    LPI2C_MasterInit(BOARD_CAMERA0_I2C_BASEADDR, &lpi2cConfig, lpi2cClkFreq_Hz);
}

void BOARD_Camera0_I2C_Deinit(void)
{
    sc_err_t err = SC_ERR_NONE;
    sc_ipc_t ipc = SystemGetScfwIpcHandle();

    BOARD_LPI2C_Deinit(BOARD_CAMERA0_I2C_BASEADDR);

    err = sc_pm_set_resource_power_mode(ipc, BOARD_CAMERA0_I2C_RSRC, SC_PM_PW_MODE_OFF);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }
}

void BOARD_Camera1_I2C_Init(void)
{
    uint32_t lpi2cClkFreq_Hz = SC_24MHZ;
    sc_err_t err             = SC_ERR_NONE;
    sc_ipc_t ipc             = SystemGetScfwIpcHandle();

    err = sc_pm_set_resource_power_mode(ipc, BOARD_CAMERA1_I2C_RSRC, SC_PM_PW_MODE_ON);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    err = sc_pm_set_clock_rate(ipc, BOARD_CAMERA1_I2C_RSRC, SC_PM_CLK_PER, &lpi2cClkFreq_Hz);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    lpi2c_master_config_t lpi2cConfig = {0};
    /*
     * lpi2cConfig.debugEnable = false;
     * lpi2cConfig.ignoreAck = false;
     * lpi2cConfig.pinConfig = kLPI2C_2PinOpenDrain;
     * lpi2cConfig.baudRate_Hz = 100000U;
     * lpi2cConfig.busIdleTimeout_ns = 0;
     * lpi2cConfig.pinLowTimeout_ns = 0;
     * lpi2cConfig.sdaGlitchFilterWidth_ns = 0;
     * lpi2cConfig.sclGlitchFilterWidth_ns = 0;
     */
    LPI2C_MasterGetDefaultConfig(&lpi2cConfig);
    lpi2cConfig.baudRate_Hz = 400000U;
    LPI2C_MasterInit(BOARD_CAMERA1_I2C_BASEADDR, &lpi2cConfig, lpi2cClkFreq_Hz);
}

void BOARD_Camera1_I2C_Deinit(void)
{
    sc_err_t err = SC_ERR_NONE;
    sc_ipc_t ipc = SystemGetScfwIpcHandle();

    BOARD_LPI2C_Deinit(BOARD_CAMERA1_I2C_BASEADDR);

    err = sc_pm_set_resource_power_mode(ipc, BOARD_CAMERA1_I2C_RSRC, SC_PM_PW_MODE_OFF);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }
}

status_t BOARD_Camera0_I2C_SendSCCB(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize)
{
    return BOARD_LPI2C_SendSCCB(BOARD_CAMERA0_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize,
                                (uint8_t *)txBuff, txBuffSize);
}

status_t BOARD_Camera0_I2C_ReceiveSCCB(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize)
{
    return BOARD_LPI2C_ReceiveSCCB(BOARD_CAMERA0_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, rxBuff,
                                   rxBuffSize);
}

status_t BOARD_Camera1_I2C_SendSCCB(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize)
{
    return BOARD_LPI2C_SendSCCB(BOARD_CAMERA1_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize,
                                (uint8_t *)txBuff, txBuffSize);
}

status_t BOARD_Camera1_I2C_ReceiveSCCB(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize)
{
    return BOARD_LPI2C_ReceiveSCCB(BOARD_CAMERA1_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, rxBuff,
                                   rxBuffSize);
}

void BOARD_Codec_I2C_Init(void)
{
    BOARD_LPI2C_Init(BOARD_CODEC_I2C_BASEADDR, BOARD_CODEC_I2C_CLOCK_FREQ);
}

status_t BOARD_Codec_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize)
{
    return BOARD_LPI2C_Send(BOARD_CODEC_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, (uint8_t *)txBuff,
                            txBuffSize);
}

status_t BOARD_Codec_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize)
{
    return BOARD_LPI2C_Receive(BOARD_CODEC_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, rxBuff, rxBuffSize);
}
#endif
