/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board.h"
#include "fsl_cache.h"
#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
#include "fsl_lpi2c.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/* Initialize debug console. */
void BOARD_InitDebugConsole(void)
{
    /* clang-format off */
    const clock_root_config_t uartClkCfg = {
        .clockOff = false,
	.mux = 0, // 24MHz oscillator source
	.div = 1
    };
    /* clang-format on */

    CLOCK_SetRootClock(BOARD_DEBUG_UART_CLOCK_ROOT, &uartClkCfg);
    DbgConsole_Init(BOARD_DEBUG_UART_INSTANCE, BOARD_DEBUG_UART_BAUDRATE, BOARD_DEBUG_UART_TYPE,
                    BOARD_DEBUG_UART_CLK_FREQ);
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

status_t BOARD_LPI2C_Send(LPI2C_Type *base,
                          uint8_t deviceAddress,
                          uint32_t subAddress,
                          uint8_t subAddressSize,
                          uint8_t *txBuff,
                          uint8_t txBuffSize,
                          uint32_t flags)
{
    lpi2c_master_transfer_t xfer;

    xfer.flags          = flags;
    xfer.slaveAddress   = deviceAddress;
    xfer.direction      = kLPI2C_Write;
    xfer.subaddress     = subAddress;
    xfer.subaddressSize = subAddressSize;
    xfer.data           = txBuff;
    xfer.dataSize       = txBuffSize;

    return LPI2C_MasterTransferBlocking(base, &xfer);
}

status_t BOARD_LPI2C_Receive(LPI2C_Type *base,
                             uint8_t deviceAddress,
                             uint32_t subAddress,
                             uint8_t subAddressSize,
                             uint8_t *rxBuff,
                             uint8_t rxBuffSize,
                             uint32_t flags)
{
    lpi2c_master_transfer_t xfer;

    xfer.flags          = flags;
    xfer.slaveAddress   = deviceAddress;
    xfer.direction      = kLPI2C_Read;
    xfer.subaddress     = subAddress;
    xfer.subaddressSize = subAddressSize;
    xfer.data           = rxBuff;
    xfer.dataSize       = rxBuffSize;

    return LPI2C_MasterTransferBlocking(base, &xfer);
}

#if defined(BOARD_USE_ADP5585) && BOARD_USE_ADP5585
void BOARD_ADP5585_I2C_Init(void)
{
    BOARD_LPI2C_Init(BOARD_ADP5585_I2C, BOARD_ADP5585_I2C_CLOCK_FREQ);
}

status_t BOARD_ADP5585_I2C_Send(uint8_t deviceAddress,
                                uint32_t subAddress,
                                uint8_t subAddressSize,
                                const uint8_t *txBuff,
                                uint8_t txBuffSize,
                                uint32_t flags)
{
    return BOARD_LPI2C_Send(BOARD_ADP5585_I2C, deviceAddress, subAddress, subAddressSize, (uint8_t *)txBuff, txBuffSize,
                            flags);
}

status_t BOARD_ADP5585_I2C_Receive(uint8_t deviceAddress,
                                   uint32_t subAddress,
                                   uint8_t subAddressSize,
                                   uint8_t *rxBuff,
                                   uint8_t rxBuffSize,
                                   uint32_t flags)
{
    return BOARD_LPI2C_Receive(BOARD_ADP5585_I2C, deviceAddress, subAddress, subAddressSize, rxBuff, rxBuffSize, flags);
}

void BOARD_InitADP5585(adp5585_handle_t *handle)
{
    BOARD_ADP5585_I2C_Init();

    static const adp5585_config_t config = {
        .i2cAddr         = BOARD_ADP5585_I2C_ADDR,
        .I2C_SendFunc    = BOARD_ADP5585_I2C_Send,
        .I2C_ReceiveFunc = BOARD_ADP5585_I2C_Receive,
    };

    ADP5585_Init(handle, &config);
}

#endif /* BOARD_USE_ADP5585. */

#if defined(BOARD_USE_PCAL6524) && BOARD_USE_PCAL6524
void BOARD_PCAL6524_I2C_Init(void)
{
    BOARD_LPI2C_Init(BOARD_PCAL6524_I2C, BOARD_PCAL6524_I2C_CLOCK_FREQ);
}

status_t BOARD_PCAL6524_I2C_Send(uint8_t deviceAddress,
                                 uint32_t subAddress,
                                 uint8_t subAddressSize,
                                 const uint8_t *txBuff,
                                 uint8_t txBuffSize,
                                 uint32_t flags)
{
    return BOARD_LPI2C_Send(BOARD_PCAL6524_I2C, deviceAddress, subAddress, subAddressSize, (uint8_t *)txBuff,
                            txBuffSize, flags);
}

status_t BOARD_PCAL6524_I2C_Receive(uint8_t deviceAddress,
                                    uint32_t subAddress,
                                    uint8_t subAddressSize,
                                    uint8_t *rxBuff,
                                    uint8_t rxBuffSize,
                                    uint32_t flags)
{
    return BOARD_LPI2C_Receive(BOARD_PCAL6524_I2C, deviceAddress, subAddress, subAddressSize, rxBuff, rxBuffSize,
                               flags);
}

void BOARD_InitPCAL6524(pcal6524_handle_t *handle)
{
    BOARD_PCAL6524_I2C_Init();

    static const pcal6524_config_t config = {
        .i2cAddr         = BOARD_PCAL6524_I2C_ADDR,
        .I2C_SendFunc    = BOARD_PCAL6524_I2C_Send,
        .I2C_ReceiveFunc = BOARD_PCAL6524_I2C_Receive,
    };

    PCAL6524_Init(handle, &config);
}

#endif /* BOARD_USE_PCAL6524. */

#endif

void BOARD_ConfigMPU(void)
{
    uint8_t attr;

    /* Disable code cache(ICache) and system cache(DCache) */
    XCACHE_DisableCache(LPCAC_PC);
    XCACHE_DisableCache(LPCAC_PS);

    /* NOTE: All TCRAM is non-cacheable regardless of MPU setting. */

    /*
     * default cache policy(default memory access behavior) after enable mpu on cortex-m33(according to RM of
     * cortex-m33): 0x00000000-0x1FFFFFFF Normal memory, Non-shareable, Write-Through, not Write Allocate
     * 0x20000000-0x3FFFFFFF Normal memory, Non-shareable, Write-Back, Write Allocate
     * 0x40000000-0x5FFFFFFF Device, Shareable
     * 0x60000000-0x7FFFFFFF Normal memory, Non-shareable, Write-Back, Write Allocate
     * 0x80000000-0x9FFFFFFF Normal memory, Non-shareable, Write-Through, not Write Allocate
     * 0xA0000000-0xDFFFFFFF Device, Shareable
     * 0xE0000000-0xE003FFFF Device, Shareable
     * 0xE0040000-0xE0043FFF Device, Shareable
     * 0xE0044000-0xE00EFFFF Device, Shareable
     * 0xF0000000-0xFFFFFFFF Device, Shareable
     */
    /* Disable MPU */
    ARM_MPU_Disable();

    /* Attr0: Device-nGnRnE */
    ARM_MPU_SetMemAttr(0U, ARM_MPU_ATTR(ARM_MPU_ATTR_DEVICE, ARM_MPU_ATTR_DEVICE));

    /* Attr1: Normal memory, Outer non-cacheable, Inner non-cacheable */
    ARM_MPU_SetMemAttr(1U, ARM_MPU_ATTR(ARM_MPU_ATTR_NON_CACHEABLE, ARM_MPU_ATTR_NON_CACHEABLE));

    /* Attr2: Normal memory, Inner write-through transient, read allocate. Inner write-through transient, read allocate
     */
    attr = ARM_MPU_ATTR_MEMORY_(0U, 0U, 1U, 0U);
    ARM_MPU_SetMemAttr(2U, ARM_MPU_ATTR(attr, attr));

    /* Attr3: Normal memory, Outer write-back transient, read/write allocate. Inner write-back transient, read/write
     * allocate */
    attr = ARM_MPU_ATTR_MEMORY_(0U, 1U, 1U, 1U);
    ARM_MPU_SetMemAttr(3U, ARM_MPU_ATTR(attr, attr));

    /*
     * Change macro definitions as follows when choose cache policy as non-cacheable:
     * #define DDR_NONCACHEABLE (1U)
     * #define DDR_WRITE_THROUGH (0U)
     * #define DDR_WRITE_BACK (0U)
     *
     *
     * Change macro definitions as follows when choose cache policy as Write-Through:
     * #define DDR_NONCACHEABLE (0U)
     * #define DDR_WRITE_THROUGH (1U)
     * #define DDR_WRITE_BACK (0U)
     *
     *
     * Change macro definitions as follows when choose cache policy as Write-Back:
     * #define DDR_NONCACHEABLE (0U)
     * #define DDR_WRITE_THROUGH (0U)
     * #define DDR_WRITE_BACK (1U)
     */
#define DDR_NONCACHEABLE  (1U)
#define DDR_WRITE_THROUGH (0U)
#define DDR_WRITE_BACK    (0U)
#if DDR_NONCACHEABLE
    /* NOTE: DDR is used as shared memory for A/M core communication, set it to non-cacheable. */
    /* Region 0: [0x80000000, 0xDFFFFFFF](DRAM), outer shareable, read/write, any privileged, executable. Attr 1
     * (non-cacheable). */
    ARM_MPU_SetRegion(0U, ARM_MPU_RBAR(0x80000000, ARM_MPU_SH_OUTER, 0U, 1U, 0U), ARM_MPU_RLAR(0xDFFFFFFF, 1U));
#elif DDR_WRITE_THROUGH
    /* Region 0: [0x80000000, 0xDFFFFFFF](DRAM), outer shareable, read/write, any privileged, executable. Attr 2
     * (Normal memory, Inner write-through transient, read allocate. Inner write-through transient, read allocate). */
    ARM_MPU_SetRegion(0U, ARM_MPU_RBAR(0x80000000, ARM_MPU_SH_OUTER, 0U, 1U, 0U), ARM_MPU_RLAR(0xDFFFFFFF, 2U));
#elif DDR_WRITE_BACK
    /* Region 0: [0x80000000, 0xDFFFFFFF](DRAM), outer shareable, read/write, any privileged, executable. Attr 3
     * (Normal memory, Outer write-back transient, read/write allocate. Inner write-back transient, read/write
     * allocate). */
    ARM_MPU_SetRegion(0U, ARM_MPU_RBAR(0x80000000, ARM_MPU_SH_OUTER, 0U, 1U, 0U), ARM_MPU_RLAR(0xDFFFFFFF, 3U));
#endif

    /* Enable MPU(use default memory map when access the memory within region) */
    ARM_MPU_Enable(MPU_CTRL_PRIVDEFENA_Msk);

    /* Enable ICache and DCache */
    XCACHE_EnableCache(LPCAC_PC);
    XCACHE_EnableCache(LPCAC_PS);
    /* flush pipeline */
    __DSB();
    __ISB();
}
