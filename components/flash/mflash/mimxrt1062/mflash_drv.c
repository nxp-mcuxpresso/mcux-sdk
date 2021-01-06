/*
 * Copyright 2018-2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdbool.h>

#include "mflash_drv.h"

#include "fsl_flexspi.h"
#include "fsl_cache.h"
#include "pin_mux.h"

#define NOR_CMD_LUT_SEQ_IDX_READ_NORMAL        2
#define NOR_CMD_LUT_SEQ_IDX_READ_FAST          1
#define NOR_CMD_LUT_SEQ_IDX_READ_FAST_QUAD     0 // set it to index0 to align with xip settings
#define NOR_CMD_LUT_SEQ_IDX_READSTATUS         3
#define NOR_CMD_LUT_SEQ_IDX_WRITEENABLE        4
#define NOR_CMD_LUT_SEQ_IDX_ERASESECTOR        5
#define NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_SINGLE 6
#define NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_QUAD   7
#define NOR_CMD_LUT_SEQ_IDX_READID             8
#define NOR_CMD_LUT_SEQ_IDX_WRITESTATUSREG     9
#define NOR_CMD_LUT_SEQ_IDX_ENTERQPI           10
#define NOR_CMD_LUT_SEQ_IDX_EXITQPI            11
#define NOR_CMD_LUT_SEQ_IDX_READSTATUSREG      12

#define CUSTOM_LUT_LENGTH        60
#define FLASH_BUSY_STATUS_POL    1
#define FLASH_BUSY_STATUS_OFFSET 0

#define FLASH_SIZE 0x8000

flexspi_device_config_t deviceconfig = {
    .flexspiRootClk       = 100000000,
    .flashSize            = FLASH_SIZE,
    .CSIntervalUnit       = kFLEXSPI_CsIntervalUnit1SckCycle,
    .CSInterval           = 2,
    .CSHoldTime           = 3,
    .CSSetupTime          = 3,
    .dataValidTime        = 0,
    .columnspace          = 0,
    .enableWordAddress    = 0,
    .AWRSeqIndex          = 0,
    .AWRSeqNumber         = 0,
    .ARDSeqIndex          = NOR_CMD_LUT_SEQ_IDX_READ_FAST_QUAD,
    .ARDSeqNumber         = 1,
    .AHBWriteWaitUnit     = kFLEXSPI_AhbWriteWaitUnit2AhbCycle,
    .AHBWriteWaitInterval = 0,
};

static uint32_t customLUT[CUSTOM_LUT_LENGTH] = {
    /* Normal read mode -SDR */
    [4 * NOR_CMD_LUT_SEQ_IDX_READ_NORMAL] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x03, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, 0x18),
    [4 * NOR_CMD_LUT_SEQ_IDX_READ_NORMAL + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_SDR, kFLEXSPI_1PAD, 0x04, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),

    /* Fast read mode - SDR */
    [4 * NOR_CMD_LUT_SEQ_IDX_READ_FAST] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x0B, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, 0x18),
    [4 * NOR_CMD_LUT_SEQ_IDX_READ_FAST + 1] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_DUMMY_SDR, kFLEXSPI_1PAD, 0x08, kFLEXSPI_Command_READ_SDR, kFLEXSPI_1PAD, 0x04),

    /* Fast read quad mode - SDR */
    [4 * NOR_CMD_LUT_SEQ_IDX_READ_FAST_QUAD] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0xEB, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_4PAD, 0x18),
    [4 * NOR_CMD_LUT_SEQ_IDX_READ_FAST_QUAD + 1] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_DUMMY_SDR, kFLEXSPI_4PAD, 0x06, kFLEXSPI_Command_READ_SDR, kFLEXSPI_4PAD, 0x04),

    /* Read extend parameters */
    [4 * NOR_CMD_LUT_SEQ_IDX_READSTATUS] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x81, kFLEXSPI_Command_READ_SDR, kFLEXSPI_1PAD, 0x04),

    /* Write Enable */
    [4 * NOR_CMD_LUT_SEQ_IDX_WRITEENABLE] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x06, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),

    /* Erase Sector  */
    [4 * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0xD7, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, 0x18),

    /* Page Program - single mode */
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_SINGLE] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x02, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, 0x18),
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_SINGLE + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_1PAD, 0x04, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),

    /* Page Program - quad mode */
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_QUAD] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x32, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, 0x18),
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_QUAD + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_4PAD, 0x04, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),

    /* Read ID */
    [4 * NOR_CMD_LUT_SEQ_IDX_READID] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0xAB, kFLEXSPI_Command_DUMMY_SDR, kFLEXSPI_1PAD, 0x18),
    [4 * NOR_CMD_LUT_SEQ_IDX_READID + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_SDR, kFLEXSPI_1PAD, 0x04, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),

    /* Enable Quad mode */
    [4 * NOR_CMD_LUT_SEQ_IDX_WRITESTATUSREG] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x01, kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_1PAD, 0x04),

    /* Enter QPI mode */
    [4 * NOR_CMD_LUT_SEQ_IDX_ENTERQPI] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x35, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),

    /* Exit QPI mode */
    [4 * NOR_CMD_LUT_SEQ_IDX_EXITQPI] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_4PAD, 0xF5, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),

    /* Read status register */
    [4 * NOR_CMD_LUT_SEQ_IDX_READSTATUSREG] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x05, kFLEXSPI_Command_READ_SDR, kFLEXSPI_1PAD, 0x04),
};

static status_t flexspi_nor_wait_bus_busy(FLEXSPI_Type *base)
{
    /* Wait status ready. */
    bool isBusy;
    uint32_t readValue;
    status_t status;
    flexspi_transfer_t flashXfer;

    flashXfer.deviceAddress = 0;
    flashXfer.port          = kFLEXSPI_PortA1;
    flashXfer.cmdType       = kFLEXSPI_Read;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_READSTATUSREG;
    flashXfer.data          = &readValue;
    flashXfer.dataSize      = 1;

    do
    {
        status = FLEXSPI_TransferBlocking(base, &flashXfer);

        if (status != kStatus_Success)
        {
            return status;
        }
        if (FLASH_BUSY_STATUS_POL)
        {
            if (readValue & (1U << FLASH_BUSY_STATUS_OFFSET))
            {
                isBusy = true;
            }
            else
            {
                isBusy = false;
            }
        }
        else
        {
            if (readValue & (1U << FLASH_BUSY_STATUS_OFFSET))
            {
                isBusy = false;
            }
            else
            {
                isBusy = true;
            }
        }

    } while (isBusy);

    return status;
}

static status_t flexspi_nor_write_enable(FLEXSPI_Type *base, uint32_t address)
{
    flexspi_transfer_t flashXfer;
    status_t status;

    /* Write neable */
    flashXfer.deviceAddress = address;
    flashXfer.port          = kFLEXSPI_PortA1;
    flashXfer.cmdType       = kFLEXSPI_Command;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_WRITEENABLE;

    status = FLEXSPI_TransferBlocking(base, &flashXfer);

    return status;
}

status_t flexspi_nor_enable_quad_mode(FLEXSPI_Type *base)
{
    flexspi_transfer_t flashXfer;
    status_t status;
    uint32_t writeValue = 0x40;

    /* Write neable */
    status = flexspi_nor_write_enable(base, 0);

    if (status != kStatus_Success)
    {
        return status;
    }

    /* Enable quad mode. */
    flashXfer.deviceAddress = 0;
    flashXfer.port          = kFLEXSPI_PortA1;
    flashXfer.cmdType       = kFLEXSPI_Write;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_WRITESTATUSREG;
    flashXfer.data          = &writeValue;
    flashXfer.dataSize      = 1;

    status = FLEXSPI_TransferBlocking(base, &flashXfer);
    if (status != kStatus_Success)
    {
        return status;
    }

    status = flexspi_nor_wait_bus_busy(base);

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
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_ERASESECTOR;
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
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_QUAD;
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

static status_t flexspi_nor_read_data(FLEXSPI_Type *base, uint32_t startAddress, uint32_t *buffer, uint32_t length)
{
    status_t status;
    flexspi_transfer_t flashXfer;
    uint32_t readAddress = startAddress;

    /* Read page. */
    flashXfer.deviceAddress = readAddress;
    flashXfer.port          = kFLEXSPI_PortA1;
    flashXfer.cmdType       = kFLEXSPI_Read;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_READ_FAST_QUAD;
    flashXfer.data          = buffer;
    flashXfer.dataSize      = length;

    status = FLEXSPI_TransferBlocking(base, &flashXfer);

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

    flexspi_config_t config;
    status_t status;

    /* Get FLEXSPI default settings and configure the flexspi. */
    FLEXSPI_GetDefaultConfig(&config);

    /* Set AHB buffer size for reading data through AHB bus. */
    config.ahbConfig.enableAHBPrefetch   = true;
    config.ahbConfig.enableAHBBufferable = true;
    config.ahbConfig.enableAHBCachable   = true;
    config.rxSampleClock                 = kFLEXSPI_ReadSampleClkLoopbackFromDqsPad;
    FLEXSPI_Init(MFLASH_FLEXSPI, &config);

    /* AHB Read Address option bit. This option bit is intend to remove AHB burst start address alignment limitation */
    MFLASH_FLEXSPI->AHBCR |= FLEXSPI_AHBCR_READADDROPT_MASK;

    /* Configure flash settings according to serial flash feature. */
    FLEXSPI_SetFlashConfig(MFLASH_FLEXSPI, &deviceconfig, kFLEXSPI_PortA1);

    /* Update LUT table. */
    FLEXSPI_UpdateLUT(MFLASH_FLEXSPI, 0, customLUT, CUSTOM_LUT_LENGTH);

    /* Enter quad mode. */
    status = flexspi_nor_enable_quad_mode(MFLASH_FLEXSPI);

    if (primask == 0)
    {
        __asm("cpsie i");
    }

    return status;
}

/* API - initialize 'mflash' */
int32_t mflash_drv_init(void)
{
    /* Necessary to have double wrapper call in non_xip memory */
    return mflash_drv_init_internal();
}

/* Internal - erase single sector */
static int32_t mflash_drv_sector_erase_internal(uint32_t sector_addr)
{
    status_t status;
    uint32_t primask = __get_PRIMASK();

    __asm("cpsid i");

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

/* Calling wrapper for 'mflash_drv_sector_erase_internal'.
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
    uint32_t primask = __get_PRIMASK();

    __asm("cpsid i");

    status_t status;
    status = flexspi_nor_flash_page_program(MFLASH_FLEXSPI, page_addr, data);

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

/* Internal - read data */
static int32_t mflash_drv_read_internal(uint32_t addr, uint32_t *buffer, uint32_t len)
{
    uint32_t primask = __get_PRIMASK();

    __asm("cpsid i");

    status_t status;
    status = flexspi_nor_read_data(MFLASH_FLEXSPI, addr, buffer, len);

    /* Do software reset. */
    FLEXSPI_SoftwareReset(MFLASH_FLEXSPI);

    if (primask == 0)
    {
        __asm("cpsie i");
    }

    /* Flush pipeline to allow pending interrupts take place
     * before starting next loop */
    __ISB();

    return status;
}

/* Calling wrapper for 'mflash_drv_read_internal'. */
int32_t mflash_drv_read(uint32_t addr, uint32_t *buffer, uint32_t len)
{
    /* Check alignment */
    if (((uint32_t)buffer % 4) || (len % 4))
        return kStatus_InvalidArgument;

    return mflash_drv_read_internal(addr, buffer, len);
}

/* Returns pointer (AHB address) to memory area where the specified region of FLASH is mapped, NULL on failure (could
 * not map continuous block) */
void *mflash_drv_phys2log(uint32_t addr, uint32_t len)
{
    /* take FLEXSPI remapping into account */
    uint32_t remap_offset = IOMUXC_GPR->GPR32 & 0xFFFFF000;
    uint32_t remap_start  = IOMUXC_GPR->GPR30 & 0xFFFFF000;
    uint32_t remap_end    = IOMUXC_GPR->GPR31 & 0xFFFFF000;

    /* calculate the bus address where the requested FLASH region is expected to be available */
    uint32_t bus_addr = addr + MFLASH_BASE_ADDRESS;

    if (remap_offset == 0 || (remap_end <= remap_start))
    {
        /* remapping is not active */
        return (void *)bus_addr;
    }

    if ((remap_start >= bus_addr + len) || (remap_end <= bus_addr))
    {
        /* remapping window does not collide with bus addresses normally assigned for requested range of FLASH */
        return (void *)bus_addr;
    }

    if ((remap_start + remap_offset <= bus_addr) && (remap_end + remap_offset >= bus_addr + len))
    {
        /* remapping window coveres the whole requested range of FLASH, return address adjusted by negative offset */
        return (void *)(bus_addr - remap_offset);
    }

    /* the bus address region normally assigned for requested range of FLASH is partially or completely shadowed by
     * remapping, fail */
    return NULL;
}

/* Returns address of physical memory where the area accessible by given pointer is actually stored, UINT32_MAX on
 * failure (could not map as continuous block) */
uint32_t mflash_drv_log2phys(void *ptr, uint32_t len)
{
    /* take FLEXSPI remapping into account */
    uint32_t remap_offset = IOMUXC_GPR->GPR32 & 0xFFFFF000;
    uint32_t remap_start  = IOMUXC_GPR->GPR30 & 0xFFFFF000;
    uint32_t remap_end    = IOMUXC_GPR->GPR31 & 0xFFFFF000;

    /* calculate the bus address where the requested FLASH region is expected to be available */
    uint32_t bus_addr = (uint32_t)ptr;

    if (bus_addr < MFLASH_BASE_ADDRESS)
    {
        /* the pointer points outside of the flash memory area */
        return UINT32_MAX;
    }

    if (remap_offset == 0 || (remap_end <= remap_start))
    {
        /* remapping is not active */
        return (bus_addr - MFLASH_BASE_ADDRESS);
    }

    if ((remap_start >= bus_addr + len) || (remap_end <= bus_addr))
    {
        /* remapping window does not affect the requested memory area */
        return (bus_addr - MFLASH_BASE_ADDRESS);
    }

    if ((remap_start <= bus_addr) && (remap_end >= bus_addr + len))
    {
        /* remapping window coveres the whole address range, return address adjusted by offset */
        return (bus_addr + remap_offset - MFLASH_BASE_ADDRESS);
    }

    /* the bus address region partially collides with the remapping window, hence the range is not mapped to continuous
     * block in the FLASH, fail */
    return UINT32_MAX;
}

/* Temporary sector shadow buffer. Use uint32_t type to force 4B alignment and
 * improve copy operation */
static uint32_t g_flashm_sector[MFLASH_SECTOR_SIZE / sizeof(uint32_t)];

/* Internal - write data of 'data_len' to single sector 'sector_addr', starting from 'sect_off' */
static int32_t mflash_drv_sector_update(uint32_t sector_addr, uint32_t sect_off, const uint8_t *data, uint32_t data_len)
{
    int sector_erase_req      = 0;
    uint32_t page_program_map = 0; /* Current implementation is limited to 32 pages per sector */

    /* Address not aligned to sector boundary */
    if (false == mflash_drv_is_sector_aligned(sector_addr))
        return -1;
    /* Offset + length exceeed sector size */
    if (sect_off + data_len > MFLASH_SECTOR_SIZE)
        return -1;

    if (0 != mflash_drv_read(sector_addr, &g_flashm_sector[0], sizeof(g_flashm_sector)))
    {
        return -2;
    }

    /* Diff the data to determine pages to be programed */
    for (uint32_t i = 0; i < data_len; i++)
    {
        uint8_t cur_value = ((uint8_t *)(g_flashm_sector))[sect_off + i];
        uint8_t new_value = data[i];

        if ((cur_value | new_value) != cur_value)
        {
            /* A bit needs to be flipped from 0 to 1, the whole sector has to be erased */
            sector_erase_req = 1;
            break;
        }

        if (cur_value != new_value)
        {
            /* There is a change, the page has to be programmed for sure */
            page_program_map |= 1 << ((sect_off + i) / MFLASH_PAGE_SIZE);
        }
    }

#if !defined(MFLASH_INC_WRITES) || !MFLASH_INC_WRITES
    /* Perform blank check page by page until decission for sector erase is made or we reach last page of the sector */
    for (int page_idx = 0; (0 == sector_erase_req) && page_idx < MFLASH_SECTOR_SIZE / MFLASH_PAGE_SIZE; page_idx++)
    {
        /* Check only pages which need to be programed */
        if (page_program_map & (1 << page_idx))
        {
            int page_word_start = page_idx * (MFLASH_PAGE_SIZE / sizeof(g_flashm_sector[0]));
            int page_word_end   = page_word_start + (MFLASH_PAGE_SIZE / sizeof(g_flashm_sector[0]));

            for (int i = page_word_start; i < page_word_end; i++)
            {
                if (g_flashm_sector[i] != 0xFFFFFFFF)
                {
                    /* Mark sector to be erased and quit */
                    sector_erase_req = 1;
                    break;
                }
            }
        }
    }
#endif

    /* Copy data to be programmed byte by byte to shadow buffer at proper position */
    for (uint32_t i = 0; i < data_len; i++)
    {
        ((uint8_t *)g_flashm_sector)[sect_off + i] = data[i];
    }

    /* If sector is to be erased, update page program map according to non-blank areas in the shadow buffer */
    if (0 != sector_erase_req)
    {
        for (int page_idx = 0; page_idx < MFLASH_SECTOR_SIZE / MFLASH_PAGE_SIZE; page_idx++)
        {
            int page_word_start = page_idx * (MFLASH_PAGE_SIZE / sizeof(g_flashm_sector[0]));
            int page_word_end   = page_word_start + (MFLASH_PAGE_SIZE / sizeof(g_flashm_sector[0]));

            for (int i = page_word_start; i < page_word_end; i++)
            {
                if (g_flashm_sector[i] != 0xFFFFFFFF)
                {
                    /* Mark the page for programming and go for next one */
                    page_program_map |= (1 << page_idx);
                    break;
                }
            }
        }
    }

    /* Erase the sector if required */
    if (0 != sector_erase_req)
    {
        if (0 != mflash_drv_sector_erase(sector_addr))
        {
            return -2;
        }
    }

    /* Program the required pages */
    for (int page_idx = 0; page_idx < MFLASH_SECTOR_SIZE / MFLASH_PAGE_SIZE; page_idx++)
    {
        if (page_program_map & (1 << page_idx))
        {
            if (0 !=
                mflash_drv_page_program(sector_addr + page_idx * MFLASH_PAGE_SIZE,
                                        g_flashm_sector + page_idx * (MFLASH_PAGE_SIZE / sizeof(g_flashm_sector[0]))))
            {
                return -3;
            }
        }
    }

    // mflash_drv_read_mode();
    return 0;
}

/* Write data to flash, cannot be invoked directly, requires calling wrapper in non XIP memory */
int32_t mflash_drv_write_internal(uint32_t addr, const uint8_t *data, uint32_t data_len)
{
    /* Interval <0, sector_size) */
    uint32_t to_write = 0;
    /* Interval (data_len, 0>  */
    uint32_t to_remain = data_len;
    /* Physical address in external FLASH device */

    int32_t result = 0;

    for (
        /* Calculate address of first sector */
        uint32_t sect_a = (addr / MFLASH_SECTOR_SIZE) * MFLASH_SECTOR_SIZE,
                 /* and first sector offset */
        sect_of = addr % MFLASH_SECTOR_SIZE,
                 /* and set first data offset to 0*/
        data_of = 0;
        /* Continue until sector address exceed target adddress + data_length */
        sect_a < addr + data_len;
        /* Move to next sector */
        sect_a += MFLASH_SECTOR_SIZE,
                 /* and move pointer to data */
        data_of += to_write)
    {
        /* If remaining data is exceed 'sector_size', write 'sector_size' length */
        if (to_remain > MFLASH_SECTOR_SIZE - sect_of)
        {
            to_write  = MFLASH_SECTOR_SIZE - sect_of;
            to_remain = to_remain - to_write;
        }
        /* else write remaining data length */
        else
        {
            to_write  = to_remain;
            to_remain = 0;
        }

        /* Write at 'sect_a' sector, starting at 'sect_of' using '&data[data_of]' of length 'to_write' */
        result = mflash_drv_sector_update(sect_a, sect_of, data + data_of, to_write);
        if (0 != result)
            return -1;
        /* Only first sector is allowed to have an offset */
        sect_of = 0;
    }

    return 0;
}

/* Calling wrapper for 'mflash_drv_write_internal'.
 * Write 'data' of 'data_len' to 'any_addr' - which doesn't have to be sector aligned.
 * NOTE: Don't try to store constant data that are located in XIP !!
 */
int32_t mflash_drv_write(uint32_t addr, const uint8_t *data, uint32_t data_len)
{
    volatile int32_t result;
    result = mflash_drv_write_internal(addr, data, data_len);
    return result;
}
