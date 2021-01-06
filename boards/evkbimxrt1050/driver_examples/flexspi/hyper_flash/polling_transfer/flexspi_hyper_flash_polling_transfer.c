/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_flexspi.h"
#include "app.h"
#include "fsl_debug_console.h"
#include "fsl_cache.h"

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
extern void flexspi_hyper_flash_init(void);
extern status_t flexspi_nor_flash_erase_sector(FLEXSPI_Type *base, uint32_t address);
extern status_t flexspi_nor_flash_page_program(FLEXSPI_Type *base, uint32_t address, const uint32_t *src);
extern status_t flexspi_nor_hyperflash_cfi(FLEXSPI_Type *base);
extern status_t flexspi_nor_flash_erase_chip(FLEXSPI_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/

static uint8_t s_hyperflash_program_buffer[FLASH_PAGE_SIZE];
static uint8_t s_hyperflash_read_buffer[FLASH_PAGE_SIZE];

/*******************************************************************************
 * Code
 ******************************************************************************/
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

const uint32_t customLUT[CUSTOM_LUT_LENGTH] = {
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
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x20, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEENABLE + 1] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xAA), // ADDR 0x555
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEENABLE + 2] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x05),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEENABLE + 3] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xAA), // DATA 0xAA
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEENABLE + 4] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x20, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00),
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

    /* program page with word program command sequence */
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_PAGEPROGRAM] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x20, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_PAGEPROGRAM + 1] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xAA), // ADDR 0x555
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_PAGEPROGRAM + 2] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x05),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_PAGEPROGRAM + 3] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xA0), // DATA 0xA0
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_PAGEPROGRAM + 4] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x20, kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x18),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_PAGEPROGRAM + 5] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_CADDR_DDR, kFLEXSPI_8PAD, 0x10, kFLEXSPI_Command_WRITE_DDR, kFLEXSPI_8PAD, 0x80),

    /* Erase chip */
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASECHIP] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASECHIP + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xAA),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASECHIP + 2] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x05),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASECHIP + 3] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x80),
    // 1
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASECHIP + 4] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASECHIP + 5] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xAA),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASECHIP + 6] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x05),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASECHIP + 7] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xAA),
    // 2
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASECHIP + 8] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASECHIP + 9] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x55),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASECHIP + 10] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x02),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASECHIP + 11] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x55),
    // 3
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASECHIP + 12] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASECHIP + 13] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xAA),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASECHIP + 14] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x05),
    [4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASECHIP + 15] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x10),
};


int main(void)
{
    uint32_t i = 0;
    status_t status;
    bool errorFlag = false;

    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("FLEXSPI hyperflash example started!\r\n");

    flexspi_hyper_flash_init();

    status = flexspi_nor_hyperflash_cfi(EXAMPLE_FLEXSPI);
    /* Get vendor ID. */
    if (status != kStatus_Success)
    {
        return status;
    }
    else
    {
        PRINTF("Found the HyperFlash by CFI\r\n");
    }

#if !(defined(XIP_EXTERNAL_FLASH))
    /* Erase whole chip . */
    PRINTF("Erasing whole chip over FlexSPI...\r\n");

    status = flexspi_nor_flash_erase_chip(EXAMPLE_FLEXSPI);
    if (status != kStatus_Success)
    {
        return status;
    }
    PRINTF("Erase finished !\r\n");
#endif

    for (uint32_t j = 0x00U; j < (((FLASH_SIZE * 1024U) / SECTOR_SIZE) - EXAMPLE_SECTOR); j++)
    {
        PRINTF("loop nummber: %d\r\n", j);

        /* Disable I cache to avoid cache pre-fatch instruction with branch prediction from flash
           and application operate flash synchronously in multi-tasks. */
#if defined(__ICACHE_PRESENT) && (__ICACHE_PRESENT == 1U)
        volatile bool ICacheEnableFlag = false;
        /* Disable I cache. */
        if (SCB_CCR_IC_Msk == (SCB_CCR_IC_Msk & SCB->CCR))
        {
            SCB_DisableICache();
            ICacheEnableFlag = true;
        }
#endif /* __ICACHE_PRESENT */
        /* Erase sector. */
        status = flexspi_nor_flash_erase_sector(EXAMPLE_FLEXSPI, (EXAMPLE_SECTOR + j) * SECTOR_SIZE);

#if defined(__ICACHE_PRESENT) && (__ICACHE_PRESENT == 1U)
        if (ICacheEnableFlag)
        {
            /* Enable I cache. */
            SCB_EnableICache();
            ICacheEnableFlag = false;
        }
#endif /* __ICACHE_PRESENT */

        if (status != kStatus_Success)
        {
            PRINTF("Erase sector failure !\r\n");
        }

        memset(s_hyperflash_program_buffer, 0xFF, sizeof(s_hyperflash_program_buffer));

#if defined(CACHE_MAINTAIN) && CACHE_MAINTAIN
        DCACHE_InvalidateByRange(EXAMPLE_FLEXSPI_AMBA_BASE + (EXAMPLE_SECTOR + j) * SECTOR_SIZE, FLASH_PAGE_SIZE);
#endif

        memcpy(s_hyperflash_read_buffer, (void *)(FlexSPI_AMBA_BASE + (EXAMPLE_SECTOR + j) * SECTOR_SIZE),
               sizeof(s_hyperflash_read_buffer));

        if (memcmp(s_hyperflash_program_buffer, s_hyperflash_read_buffer, sizeof(s_hyperflash_program_buffer)))
        {
            PRINTF("Erase data -  read out data value incorrect !\r\n ");
        }

        for (i = 0; i < sizeof(s_hyperflash_program_buffer); i++)
        {
            s_hyperflash_program_buffer[i] = i & 0xFFU;
        }

        for (uint32_t k = 0x00U; k < (SECTOR_SIZE / FLASH_PAGE_SIZE); k++)
        {
#if defined(__ICACHE_PRESENT) && (__ICACHE_PRESENT == 1U)
            /* Disable I cache. */
            if (SCB_CCR_IC_Msk == (SCB_CCR_IC_Msk & SCB->CCR))
            {
                SCB_DisableICache();
                ICacheEnableFlag = true;
            }
#endif /* __ICACHE_PRESENT */

            status = flexspi_nor_flash_page_program(EXAMPLE_FLEXSPI,
                                                    (EXAMPLE_SECTOR + j) * SECTOR_SIZE + k * FLASH_PAGE_SIZE,
                                                    (void *)s_hyperflash_program_buffer);

#if defined(__ICACHE_PRESENT) && (__ICACHE_PRESENT == 1U)
            if (ICacheEnableFlag)
            {
                /* Enable I cache. */
                SCB_EnableICache();
                ICacheEnableFlag = false;
            }
#endif /* __ICACHE_PRESENT */

            if (status != kStatus_Success)
            {
                PRINTF("Page program failure !\r\n");
            }

#if defined(CACHE_MAINTAIN) && CACHE_MAINTAIN
            DCACHE_InvalidateByRange(
                EXAMPLE_FLEXSPI_AMBA_BASE + (EXAMPLE_SECTOR + j) * SECTOR_SIZE + k * FLASH_PAGE_SIZE, FLASH_PAGE_SIZE);
#endif

            memcpy(s_hyperflash_read_buffer,
                   (void *)(FlexSPI_AMBA_BASE + (EXAMPLE_SECTOR + j) * SECTOR_SIZE + k * FLASH_PAGE_SIZE),
                   sizeof(s_hyperflash_read_buffer));

            if (memcmp(s_hyperflash_read_buffer, s_hyperflash_program_buffer, sizeof(s_hyperflash_program_buffer)) != 0)
            {
                errorFlag = true;
                PRINTF("Page read failure !\r\n");
            }
        }
    }

    if (errorFlag)
    {
        PRINTF("FLEXSPI hyperflash example failed. \r\n ");
    }
    else
    {
        PRINTF("FLEXSPI hyperflash example successfully. \r\n");
    }

    while (1)
    {
    }
}
