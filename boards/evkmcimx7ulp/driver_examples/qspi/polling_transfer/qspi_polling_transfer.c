/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "app.h"
#include "pin_mux.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_qspi.h"

#include "fsl_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DUMMY_MASTER (0xE)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
extern void qspi_nor_flash_init(QuadSPI_Type *base);
#if defined(FLASH_ENABLE_QUAD_CMD)
extern void enable_quad_mode(void);
#endif
#if defined(FLASH_ENABLE_OCTAL_CMD)
extern void enable_octal_mode(void);
#endif
extern void erase_sector(uint32_t addr);
extern void erase_all(void);
extern void program_page(uint32_t dest_addr, uint32_t *src_addr);
extern void BOARD_SetQspiClock(QuadSPI_Type *qspi, uint32_t qspiClockSrc, uint32_t divider);
/*******************************************************************************
 * Variables
 ******************************************************************************/
static uint32_t buff[64]; /* Test data */
#if !defined(FSL_FEATURE_QSPI_CLOCK_CONTROL_EXTERNAL) || (!FSL_FEATURE_QSPI_CLOCK_CONTROL_EXTERNAL)
static bool isDivNeedRestore = false;
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
uint32_t lut[FSL_FEATURE_QSPI_LUT_DEPTH] =
    {/* Seq0 :Quad Read */
     /* CMD:        0xEB - Quad Read, Single pad */
     /* ADDR:       0x18 - 24bit address, Quad pads */
     /* DUMMY:      0x06 - 6 clock cyles, Quad pads */
     /* READ:       0x80 - Read 128 bytes, Quad pads */
     /* JUMP_ON_CS: 0 */
     [0] = 0x0A1804EB,
     [1] = 0x1E800E06,
     [2] = 0x2400,

     /* Seq1: Write Enable */
     /* CMD:      0x06 - Write Enable, Single pad */
     [4] = 0x406,

     /* Seq2: Erase All */
     /* CMD:    0x60 - Erase All chip, Single pad */
     [8] = 0x460,

     /* Seq3: Read Status */
     /* CMD:    0x05 - Read Status, single pad */
     /* READ:   0x01 - Read 1 byte */
     [12] = 0x1c010405,

     /* Seq4: Page Program */
     /* CMD:    0x02 - Page Program, Single pad */
     /* ADDR:   0x18 - 24bit address, Single pad */
     /* WRITE:  0x80 - Write 128 bytes at one pass, Single pad */
     [16] = 0x08180402,
     [17] = 0x2080,

     /* Seq5: Write Register */
     /* CMD:    0x01 - Write Status Register, single pad */
     /* WRITE:  0x01 - Write 1 byte of data, single pad */
     [20] = 0x20010401,

     /* Seq6: Read Config Register */
     /* CMD:  0x05 - Read Config register, single pad */
     /* READ: 0x01 - Read 1 byte */
     [24] = 0x1c010405,

     /* Seq7: Erase Sector */
     /* CMD:  0x20 - Sector Erase, single pad */
     /* ADDR: 0x18 - 24 bit address, single pad */
     [28] = 0x08180420,

     /* Seq8: Dummy */
     /* CMD:    0xFF - Dummy command, used to force SPI flash to exit continuous read mode */
     [32] = 0x4FF,

     /* Seq9: Fast Single read */
     /* CMD:        0x0B - Fast Read, Single Pad */
     /* ADDR:       0x18 - 24bit address, Single Pad */
     /* DUMMY:      0x08 - 8 clock cyles, Single Pad */
     /* READ:       0x80 - Read 128 bytes, Single Pad */
     /* JUMP_ON_CS: 0 */
     [36] = 0x0818040B,
     [37] = 0x1C800C08,
     [38] = 0x2400,

     /* Seq10: Fast Dual read */
     /* CMD:        0x3B - Dual Read, Single Pad */
     /* ADDR:       0x18 - 24bit address, Single Pad */
     /* DUMMY:      0x08 - 8 clock cyles, Single Pad */
     /* READ:       0x80 - Read 128 bytes, Dual pads */
     /* JUMP_ON_CS: 0 */
     [40] = 0x0818043B,
     [41] = 0x1D800C08,
     [42] = 0x2400,

     /* Match MISRA rule */
     [63] = 0};

qspi_flash_config_t single_config = {.flashA1Size = FLASH_SIZE, /* 4MB */
                                     .flashA2Size = 0,
#if defined(FSL_FEATURE_QSPI_SUPPORT_PARALLEL_MODE) && (FSL_FEATURE_QSPI_SUPPORT_PARALLEL_MODE)
                                     .flashB1Size = FLASH_SIZE,
                                     .flashB2Size = 0,
#endif
#if !defined(FSL_FEATURE_QSPI_HAS_NO_TDH) || (!FSL_FEATURE_QSPI_HAS_NO_TDH)
                                     .dataHoldTime = 0,
#endif
                                     .CSHoldTime        = 0,
                                     .CSSetupTime       = 0,
                                     .cloumnspace       = 0,
                                     .dataLearnValue    = 0,
                                     .endian            = kQSPI_64LittleEndian,
                                     .enableWordAddress = false};

/* Use QSPI polling way to program serial flash */
void qspi_polling(void)
{
    uint32_t i    = 0;
    uint32_t err  = 0;
    uint32_t addr = 0;
#if !defined(QSPI_ERASE_ADDR_OFFSET)
    addr = FSL_FEATURE_QSPI_AMBA_BASE;
#else
    addr = FSL_FEATURE_QSPI_AMBA_BASE + QSPI_ERASE_ADDR_OFFSET;
#endif
    erase_sector(addr);
    PRINTF("Erase finished!\r\n");

#if !defined(FSL_FEATURE_QSPI_CLOCK_CONTROL_EXTERNAL) || (!FSL_FEATURE_QSPI_CLOCK_CONTROL_EXTERNAL)
    /* Reduce frequency while clock divder is less than 2 */
    uint8_t qspiClockDiv = ((EXAMPLE_QSPI->MCR & QuadSPI_MCR_SCLKCFG_MASK) >> QuadSPI_MCR_SCLKCFG_SHIFT) + 1U;
    if (qspiClockDiv == 1U)
    {
        /* Reduce the frequency */
        isDivNeedRestore = true;
        QSPI_Enable(EXAMPLE_QSPI, false);
        EXAMPLE_QSPI->MCR &= ~QuadSPI_MCR_SCLKCFG_MASK;
        EXAMPLE_QSPI->MCR |= QuadSPI_MCR_SCLKCFG(1U);
        QSPI_Enable(EXAMPLE_QSPI, true);
    }
#endif

#if defined(FSL_SDK_DRIVER_QUICK_ACCESS_ENABLE)
    BOARD_SetQspiClock(EXAMPLE_QSPI, CLKCTL0_OSPIFCLKSEL_SEL(0), 10);
#endif

    /* Program pages in a sector */
    for (i = 0; i < FLASH_SECTORE_SIZE / FLASH_PAGE_SIZE; i++)
    {
        program_page(addr + i * FLASH_PAGE_SIZE, buff);
    }
    PRINTF("Program data finished!\r\n");

#if !defined(FSL_FEATURE_QSPI_CLOCK_CONTROL_EXTERNAL) || (!FSL_FEATURE_QSPI_CLOCK_CONTROL_EXTERNAL)
    /* Restore the frequency if needed */
    if (isDivNeedRestore)
    {
        QSPI_Enable(EXAMPLE_QSPI, false);
        EXAMPLE_QSPI->MCR &= ~QuadSPI_MCR_SCLKCFG_MASK;
        EXAMPLE_QSPI->MCR |= QuadSPI_MCR_SCLKCFG(0U);
        QSPI_Enable(EXAMPLE_QSPI, true);
    }
#endif

#if defined(FLASH_NEED_DQS)
#if defined(FSL_SDK_DRIVER_QUICK_ACCESS_ENABLE)
    BOARD_SetQspiClock(EXAMPLE_QSPI, CLKCTL0_OSPIFCLKSEL_SEL(0), 2);
#else
    /* Re-configure QSPI Serial clock frequency in order to acheive high performance. */
    QSPI_ClockUpdate(EXAMPLE_QSPI);
#endif
#endif

    for (i = 0; i < FLASH_SECTORE_SIZE / 4; i++)
    {
        if (((uint32_t *)addr)[i] != buff[i % 64])
        {
            PRINTF("The data in %d is wrong!!\r\n", i);
            PRINTF("The flash value in %d is %d\r\n", i, ((uint32_t *)addr)[i]);
            err++;
        }
    }
    if (err == 0)
    {
        PRINTF("Program through QSPI polling succeed!\r\n");
    }
}

int main(void)
{
    uint32_t i = 0;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    CLOCK_SetIpSrcDiv(kCLOCK_Qspi, kCLOCK_IpSrcSystem, 3, 0);

    /*Enable QSPI clock */
    PRINTF("QSPI example started!\r\n");

    /* Copy the LUT table */
    memcpy(single_config.lookuptable, lut, sizeof(lut));

    qspi_nor_flash_init(EXAMPLE_QSPI);

    /*Initialize data buffer */
    for (i = 0; i < 64; i++)
    {
        buff[i] = i;
    }

#if defined(FLASH_ENABLE_QUAD_CMD)
    /* Enable Quad mode for the flash */
    enable_quad_mode();
#endif

#if defined(FLASH_ENABLE_OCTAL_CMD)
    enable_ddr_mode();
    /* Enable Octal mode for the flash */
    enable_octal_mode();
#endif

    /* Use polling to program flash. */
    qspi_polling();

    while (1)
    {
    }
}
