/*
 * Copyright 2017-2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdbool.h>

#include "mflash_drv.h"

#include "fsl_flexspi.h"
#include "fsl_cache.h"
#include "pin_mux.h"

#define HYPERFLASH_CMD_LUT_SEQ_IDX_READDATA    0
#define HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEDATA   1
#define HYPERFLASH_CMD_LUT_SEQ_IDX_READSTATUS  2
#define HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEENABLE 4
#define HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR 6
#define HYPERFLASH_CMD_LUT_SEQ_IDX_PAGEPROGRAM 10
#define CUSTOM_LUT_LENGTH                      48

#define FLASH_SIZE 0x10000

flexspi_device_config_t deviceconfig = {
    .flexspiRootClk       = 42000000, /* 42MHZ SPI serial clock */
    .isSck2Enabled        = false,
    .flashSize            = FLASH_SIZE,
    .CSIntervalUnit       = kFLEXSPI_CsIntervalUnit1SckCycle,
    .CSInterval           = 2,
    .CSHoldTime           = 0,
    .CSSetupTime          = 3,
    .dataValidTime        = 1,
    .columnspace          = 3,
    .enableWordAddress    = true,
    .AWRSeqIndex          = HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEDATA,
    .AWRSeqNumber         = 1,
    .ARDSeqIndex          = HYPERFLASH_CMD_LUT_SEQ_IDX_READDATA,
    .ARDSeqNumber         = 1,
    .AHBWriteWaitUnit     = kFLEXSPI_AhbWriteWaitUnit2AhbCycle,
    .AHBWriteWaitInterval = 20,
};

static uint32_t customLUT[CUSTOM_LUT_LENGTH] = {
    /* Read Data */
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_READDATA] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xA0, kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x18),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_READDATA + 1] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_CADDR_DDR, kFLEXSPI_8PAD, 0x10, kFLEXSPI_Command_READ_DDR, kFLEXSPI_8PAD, 0x04),

    /* Write Data */
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEDATA] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x20, kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x18),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEDATA + 1] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_CADDR_DDR, kFLEXSPI_8PAD, 0x10, kFLEXSPI_Command_WRITE_DDR, kFLEXSPI_8PAD, 0x02),
    /* Read Status */
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_READSTATUS] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_READSTATUS + 1] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xAA), // ADDR 0x555
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_READSTATUS + 2] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x05),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_READSTATUS + 3] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x70), // DATA 0x70
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_READSTATUS + 4] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xA0, kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x18),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_READSTATUS + 5] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_CADDR_DDR, kFLEXSPI_8PAD, 0x10, kFLEXSPI_Command_DUMMY_RWDS_DDR, kFLEXSPI_8PAD, 0x0B),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_READSTATUS + 6] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_DDR, kFLEXSPI_8PAD, 0x04, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0x0),

    /* Write Enable */
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEENABLE] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEENABLE + 1] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xAA), // ADDR 0x555
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEENABLE + 2] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x05),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEENABLE + 3] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xAA), // DATA 0xAA
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEENABLE + 4] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEENABLE + 5] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x55),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEENABLE + 6] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x02),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEENABLE + 7] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x55),

    /* Erase Sector  */
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR + 1] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xAA), // ADDR 0x555
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR + 2] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x05),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR + 3] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x80), // DATA 0x80
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR + 4] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR + 5] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xAA),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR + 6] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x05),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR + 7] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xAA), // ADDR 0x555
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR + 8] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR + 9] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x55),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR + 10] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x02),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR + 11] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x55),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR + 12] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x18),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR + 13] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_CADDR_DDR, kFLEXSPI_8PAD, 0x10, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR + 14] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x30, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0x00),

    /* program page */
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_PAGEPROGRAM] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_PAGEPROGRAM + 1] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xAA), // ADDR 0x555
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_PAGEPROGRAM + 2] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x05),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_PAGEPROGRAM + 3] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xA0), // DATA 0xA0
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_PAGEPROGRAM + 4] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x18),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_PAGEPROGRAM + 5] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_CADDR_DDR, kFLEXSPI_8PAD, 0x10, kFLEXSPI_Command_WRITE_DDR, kFLEXSPI_8PAD, 0x80),
};

static status_t flexspi_nor_wait_bus_busy(FLEXSPI_Type *base)
{
    /* Wait status ready. */
    bool isBusy;
    uint32_t readValue = 0;
    status_t status;
    flexspi_transfer_t flashXfer;

    flashXfer.deviceAddress = 0;
    flashXfer.port          = kFLEXSPI_PortA1;
    flashXfer.cmdType       = kFLEXSPI_Read;
    flashXfer.SeqNumber     = 2;
    flashXfer.seqIndex      = HYPERFLASH_CMD_LUT_SEQ_IDX_READSTATUS;
    flashXfer.data          = &readValue;
    flashXfer.dataSize      = 2;

    do
    {
        status = FLEXSPI_TransferBlocking(base, &flashXfer);

        if (status != kStatus_Success)
        {
            return status;
        }
        if (readValue & 0x8000)
        {
            isBusy = false;
        }
        else
        {
            isBusy = true;
        }

        if (readValue & 0x3200)
        {
            status = kStatus_Fail;
            break;
        }

    } while (isBusy);

    return status;
}

static status_t flexspi_nor_write_enable(FLEXSPI_Type *base, uint32_t baseAddr)
{
    flexspi_transfer_t flashXfer;
    status_t status;

    /* Write neable */
    flashXfer.deviceAddress = baseAddr;
    flashXfer.port          = kFLEXSPI_PortA1;
    flashXfer.cmdType       = kFLEXSPI_Command;
    flashXfer.SeqNumber     = 2;
    flashXfer.seqIndex      = HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEENABLE;

    status = FLEXSPI_TransferBlocking(base, &flashXfer);

    return status;
}

static status_t flexspi_nor_flash_sector_erase(FLEXSPI_Type *base, uint32_t address)
{
    status_t status;
    flexspi_transfer_t flashXfer;

    /* Write enable */
    status = flexspi_nor_write_enable(base, address);

    if (status != kStatus_Success)
    {
        return status;
    }

    flashXfer.deviceAddress = address;
    flashXfer.port          = kFLEXSPI_PortA1;
    flashXfer.cmdType       = kFLEXSPI_Command;
    flashXfer.SeqNumber     = 4;
    flashXfer.seqIndex      = HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR;
    status                  = FLEXSPI_TransferBlocking(base, &flashXfer);

    if (status != kStatus_Success)
    {
        return status;
    }

    status = flexspi_nor_wait_bus_busy(base);

    return status;
}

static status_t flexspi_nor_flash_page_program(FLEXSPI_Type *base, uint32_t address, const uint32_t *src)
{
    status_t status;
    flexspi_transfer_t flashXfer;

    /* Write enable */
    status = flexspi_nor_write_enable(base, address);

    if (status != kStatus_Success)
    {
        return status;
    }

    /* Prepare page program command */
    flashXfer.deviceAddress = address;
    flashXfer.port          = kFLEXSPI_PortA1;
    flashXfer.cmdType       = kFLEXSPI_Write;
    flashXfer.SeqNumber     = 2;
    flashXfer.seqIndex      = HYPERFLASH_CMD_LUT_SEQ_IDX_PAGEPROGRAM;
    flashXfer.data          = (uint32_t *)src;
    flashXfer.dataSize      = MFLASH_PAGE_SIZE;
    status                  = FLEXSPI_TransferBlocking(base, &flashXfer);

    if (status != kStatus_Success)
    {
        return status;
    }

    status = flexspi_nor_wait_bus_busy(base);

    return status;
}

/* Initialize flash peripheral,
 * cannot be invoked directly, requires calling wrapper in non XIP memory */
static int32_t mflash_drv_init_internal(void)
{
    /* NOTE: Multithread access is not supported for SRAM target.
     *       XIP target MUST be protected by disabling global interrupts
     *       since all ISR (and API that is used inside) is placed at XIP.
     *       It is necessary to place at least "mflash_drv.o", "fsl_flexspi.o" to SRAM */
    /* disable interrupts when running from XIP */
    uint32_t primask = __get_PRIMASK();
    __asm("cpsid i");

    /* Wait for bus to be idle before changing flash configuration. */
    while (false == FLEXSPI_GetBusIdleStatus(MFLASH_FLEXSPI))
    {
    }

#ifndef XIP_EXTERNAL_FLASH
    flexspi_config_t config;
    /* Get FLEXSPI default settings and configure the flexspi. */
    FLEXSPI_GetDefaultConfig(&config);

    /* Set AHB buffer size for reading data through AHB bus. */
    config.ahbConfig.enableAHBPrefetch   = true;
    config.ahbConfig.enableAHBBufferable = true;
    config.ahbConfig.enableAHBCachable   = true;
    /* enable diff clock and DQS */
    config.enableSckBDiffOpt = true;
    config.rxSampleClock     = kFLEXSPI_ReadSampleClkExternalInputFromDqsPad;
#if !(defined(FSL_FEATURE_FLEXSPI_HAS_NO_MCR0_COMBINATIONEN) && FSL_FEATURE_FLEXSPI_HAS_NO_MCR0_COMBINATIONEN)
    config.enableCombination = true;
#endif
    FLEXSPI_Init(MFLASH_FLEXSPI, &config);

    /* AHB Read Address option bit. This option bit is intend to remove AHB burst start address alignment limitation */
    MFLASH_FLEXSPI->AHBCR |= FLEXSPI_AHBCR_READADDROPT_MASK;

    /* Configure flash settings according to serial flash feature. */
    FLEXSPI_SetFlashConfig(MFLASH_FLEXSPI, &deviceconfig, kFLEXSPI_PortA1);
#endif

    /* Update LUT table. */
    FLEXSPI_UpdateLUT(MFLASH_FLEXSPI, 0, customLUT, CUSTOM_LUT_LENGTH);

    /* Do software reset. */
    FLEXSPI_SoftwareReset(MFLASH_FLEXSPI);

    if (primask == 0)
    {
        __asm("cpsie i");
    }

    return kStatus_Success;
}

/* API - initialize 'mflash' */
int32_t mflash_drv_init(void)
{
    volatile int32_t result;
    /* Necessary to have double wrapper call in non_xip memory */
    result = mflash_drv_init_internal();

    return result;
}

/* Internal - erase single sector */
static int32_t mflash_drv_sector_erase_internal(uint32_t sector_addr)
{
    uint32_t primask = __get_PRIMASK();

    __asm("cpsid i");

    status_t status;
    status = flexspi_nor_flash_sector_erase(MFLASH_FLEXSPI, sector_addr);

    /* Do software reset. */
    FLEXSPI_SoftwareReset(MFLASH_FLEXSPI);

    DCACHE_InvalidateByRange(MFLASH_BASE_ADDRESS + sector_addr, MFLASH_SECTOR_SIZE);

    if (primask == 0)
    {
        __asm("cpsie i");
    }

    /* Flush pipeline to allow pending interrupts take place
     * before starting next loop */
    __ISB();

    return status;
}

/* Calling wrapper for 'mflash_drv_erase_sector_internal'.
 * Erase one sector starting at 'sector_addr' - must be sector aligned.
 */
int32_t mflash_drv_sector_erase(uint32_t sector_addr)
{
    if (0 == mflash_drv_is_sector_aligned(sector_addr))
        return kStatus_InvalidArgument;

    return mflash_drv_sector_erase_internal(sector_addr);
}

/* Internal - write single page */
static int32_t mflash_drv_page_program_internal(uint32_t page_addr, uint32_t *data)
{
    status_t status;

    uint32_t freq_orig;
    uint32_t div_orig;
    uint32_t div_restore = 0;

    uint32_t primask = __get_PRIMASK();
    __asm("cpsid i");

    /* CLOCK_GetClockRootFreq may be executed from FLASH, called here, avoid calling it later on */
    freq_orig = CLOCK_GetClockRootFreq(kCLOCK_FlexspiClkRoot);
    if (freq_orig > 100000000)
    {
        /* It is necessary to slow down the clock below 50 MHz DDR for programming operation */
        uint32_t div_prog;
        uint32_t freq_prog;
        uint32_t freq_in;

        div_orig    = CLOCK_GetDiv(kCLOCK_FlexspiDiv); /* Backup currect div setting */
        freq_in     = freq_orig * (div_orig + 1);      /* Calculate input clock */
        div_prog    = (freq_in - 1) / 100000000;       /* Calculate divider to get below 50 MHz DDR */
        freq_prog   = freq_in / (div_prog + 1);        /* Calculate frequency used during programming */
        div_restore = 1;                               /* Set this to restore to original clock settings afterwards */

        /* Wait for bus to be idle before changing flash configuration. */
        while (!FLEXSPI_GetBusIdleStatus(MFLASH_FLEXSPI))
        {
        }
        FLEXSPI_Enable(MFLASH_FLEXSPI, false);
        CLOCK_DisableClock(kCLOCK_FlexSpi);
        CLOCK_SetDiv(kCLOCK_FlexspiDiv, div_prog);
        CLOCK_EnableClock(kCLOCK_FlexSpi);
        FLEXSPI_Enable(MFLASH_FLEXSPI, true);

        /* Do software reset. */
        FLEXSPI_SoftwareReset(MFLASH_FLEXSPI);

        /* Set frequency in device config */
        deviceconfig.flexspiRootClk = freq_prog;

        /* Update DLL value depending on flexspi root clock. */
        FLEXSPI_UpdateDllValue(MFLASH_FLEXSPI, &deviceconfig, kFLEXSPI_PortA1);

        /* Do software reset. */
        FLEXSPI_SoftwareReset(MFLASH_FLEXSPI);
    }

    status = flexspi_nor_flash_page_program(MFLASH_FLEXSPI, page_addr, data);

    if (div_restore != 0)
    {
        /* Wait for bus to be idle before changing flash configuration. */
        while (!FLEXSPI_GetBusIdleStatus(MFLASH_FLEXSPI))
        {
        }
        FLEXSPI_Enable(MFLASH_FLEXSPI, false);
        CLOCK_DisableClock(kCLOCK_FlexSpi);
        CLOCK_SetDiv(kCLOCK_FlexspiDiv, div_orig);
        CLOCK_EnableClock(kCLOCK_FlexSpi);
        FLEXSPI_Enable(MFLASH_FLEXSPI, true);

        /* Do software reset. */
        FLEXSPI_SoftwareReset(MFLASH_FLEXSPI);

        /* Restore frequency in deviceconfig to original value */
        deviceconfig.flexspiRootClk = freq_orig;

        /* Update DLL value depending on flexspi root clock. */
        FLEXSPI_UpdateDllValue(MFLASH_FLEXSPI, &deviceconfig, kFLEXSPI_PortA1);
    }

    /* Do software reset. */
    FLEXSPI_SoftwareReset(MFLASH_FLEXSPI);

    DCACHE_InvalidateByRange(MFLASH_BASE_ADDRESS + page_addr, MFLASH_PAGE_SIZE);

    if (primask == 0)
    {
        __asm("cpsie i");
    }

    /* Flush pipeline to allow pending interrupts take place
     * before starting next loop */
    __ISB();

    return status;
}

/* Calling wrapper for 'mflash_drv_page_program_internal'.
 * Write 'data' to 'page_addr' - must be page aligned.
 * NOTE: Don't try to store constant data that are located in XIP !!
 */
int32_t mflash_drv_page_program(uint32_t page_addr, uint32_t *data)
{
    if (0 == mflash_drv_is_page_aligned(page_addr))
        return kStatus_InvalidArgument;

    return mflash_drv_page_program_internal(page_addr, data);
}

/* API - Read data */
int32_t mflash_drv_read(uint32_t addr, uint32_t *buffer, uint32_t len)
{
    memcpy(buffer, (void *)(addr + MFLASH_BASE_ADDRESS), len);
    return kStatus_Success;
}

/* API - Get pointer to FLASH region */
void *mflash_drv_phys2log(uint32_t addr, uint32_t len)
{
    return (void *)(addr + MFLASH_BASE_ADDRESS);
}

/* API - Get pointer to FLASH region */
uint32_t mflash_drv_log2phys(void *ptr, uint32_t len)
{
    if ((uint32_t)ptr < MFLASH_BASE_ADDRESS)
        return kStatus_InvalidArgument;

    return ((uint32_t)ptr - MFLASH_BASE_ADDRESS);
}
