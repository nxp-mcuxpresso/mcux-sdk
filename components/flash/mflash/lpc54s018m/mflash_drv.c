/*
 * Copyright 2017-2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdbool.h>

#include "mflash_drv.h"

#include "fsl_spifi.h"
#include "pin_mux.h"

/* Command ID */
#define COMMAND_NUM    (6)
#define READ           (0)
#define PROGRAM_PAGE   (1)
#define GET_STATUS     (2)
#define ERASE_SECTOR   (3)
#define WRITE_ENABLE   (4)
#define WRITE_REGISTER (5)

/* Commands definition, taken from SPIFI demo */
static spifi_command_t command[COMMAND_NUM] = {
    /* read */
    {MFLASH_PAGE_SIZE, false, kSPIFI_DataInput, 1, kSPIFI_CommandAllSerial, kSPIFI_CommandOpcodeAddrThreeBytes, 0x0B},
    /* program */
    {MFLASH_PAGE_SIZE, false, kSPIFI_DataOutput, 0, kSPIFI_CommandAllSerial, kSPIFI_CommandOpcodeAddrThreeBytes, 0x2},
    /* status */
    {1, false, kSPIFI_DataInput, 0, kSPIFI_CommandAllSerial, kSPIFI_CommandOpcodeOnly, 0x05},
    /* erase */
    {0, false, kSPIFI_DataOutput, 0, kSPIFI_CommandAllSerial, kSPIFI_CommandOpcodeAddrThreeBytes, 0x20},
    /* write enable */
    {0, false, kSPIFI_DataOutput, 0, kSPIFI_CommandAllSerial, kSPIFI_CommandOpcodeOnly, 0x06},
    /* write register */
    {4, false, kSPIFI_DataOutput, 0, kSPIFI_CommandAllSerial, kSPIFI_CommandOpcodeOnly, 0x01}};

/* Wait until command finishes */
static inline void mflash_drv_check_if_finish(void)
{
    uint8_t val = 0;
    do
    {
        SPIFI_SetCommand(MFLASH_SPIFI, &command[GET_STATUS]);
        while ((MFLASH_SPIFI->STAT & SPIFI_STAT_INTRQ_MASK) == 0U)
        {
        }
        val = SPIFI_ReadDataByte(MFLASH_SPIFI);
    } while (val & 0x1);
}

static void mflash_drv_read_mode(void)
{
    /* Switch back to read mode */
    SPIFI_ResetCommand(MFLASH_SPIFI);
    SPIFI_SetMemoryCommand(MFLASH_SPIFI, &command[READ]);
}

/* Initialize SPIFI & flash peripheral,
 * cannot be invoked directly, requires calling wrapper in non XIP memory */
static int32_t mflash_drv_init_internal(void)
{
    /* NOTE: Multithread access is not supported for SRAM target.
     *       XIP target MUST be protected by disabling global interrupts
     *       since all ISR (and API that is used inside) is placed at XIP.
     *       It is necessary to place at least "mflash_drv_drv.o", "fsl_spifi.o" to SRAM */
    /* disable interrupts when running from XIP
     * TODO: store/restore previous PRIMASK on stack to avoid
     * failure in case of nested critical sections !! */
    uint32_t primask = __get_PRIMASK();

    __asm("cpsid i");

    spifi_config_t config = {0};

#ifndef XIP_IMAGE
    uint32_t sourceClockFreq;
#if 0 /* Pinmuxing shall be initialized during board startup */
    BOARD_InitSPIFI();
#endif
    /* Reset peripheral */
    RESET_PeripheralReset(kSPIFI_RST_SHIFT_RSTn);
    /* Set SPIFI clock source */
    CLOCK_AttachClk(kFRO_HF_to_SPIFI_CLK);
    sourceClockFreq = CLOCK_GetSpifiClkFreq();
    /* Set the clock divider */
    CLOCK_SetClkDiv(kCLOCK_DivSpifiClk, sourceClockFreq / MFLASH_BAUDRATE, false);
    /* Enable SPIFI clock */
    CLOCK_EnableClock(kCLOCK_Spifi);
#endif

    SPIFI_GetDefaultConfig(&config);
    config.dualMode = kSPIFI_DualMode;
#ifdef XIP_IMAGE
    config.disablePrefetch     = false; // true;
    config.disableCachePrefech = false; // true;
#else
    config.disablePrefetch     = false; // true;
    config.disableCachePrefech = false; // true;
#endif

    /* Reset the Command register */
    SPIFI_ResetCommand(MFLASH_SPIFI);

    /* Set time delay parameter */
    MFLASH_SPIFI->CTRL = SPIFI_CTRL_TIMEOUT(config.timeout) | SPIFI_CTRL_CSHIGH(config.csHighTime) |
                         SPIFI_CTRL_D_PRFTCH_DIS(config.disablePrefetch) | SPIFI_CTRL_MODE3(config.spiMode) |
                         SPIFI_CTRL_PRFTCH_DIS(config.disableCachePrefech) | SPIFI_CTRL_DUAL(config.dualMode) |
                         SPIFI_CTRL_RFCLK(config.isReadFullClockCycle) | SPIFI_CTRL_FBCLK(config.isFeedbackClock);

    mflash_drv_read_mode();

    if (primask == 0)
    {
        __asm("cpsie i");
    }

    return kStatus_Success;
}

/* API - initialize 'mflash' - calling wrapper */
int32_t mflash_drv_init(void)
{
    return mflash_drv_init_internal();
}

/* Erase single sector */
static int32_t mflash_drv_sector_erase_internal(uint32_t sector_addr)
{
    uint32_t primask = __get_PRIMASK();

    __asm("cpsid i");

    /* Reset the SPIFI to switch to command mode */
    SPIFI_ResetCommand(MFLASH_SPIFI);

    /* Write enable */
    SPIFI_SetCommand(MFLASH_SPIFI, &command[WRITE_ENABLE]);
    /* Set address */
    SPIFI_SetCommandAddress(MFLASH_SPIFI, sector_addr);
    /* Erase sector */
    SPIFI_SetCommand(MFLASH_SPIFI, &command[ERASE_SECTOR]);
    /* Check if finished */
    mflash_drv_check_if_finish();
    /* Switch to read mode to enable interrupts as soon ass possible */
    mflash_drv_read_mode();

    if (primask == 0)
    {
        __asm("cpsie i");
    }

    /* Flush pipeline to allow pending interrupts take place */
    __ISB();

    return kStatus_Success;
}

/* API - Erase single sector - calling wrapper */
int32_t mflash_drv_sector_erase(uint32_t sector_addr)
{
    return mflash_drv_sector_erase_internal(sector_addr);
}

/* Page program */
static int32_t mflash_drv_page_program_internal(uint32_t page_addr, const uint32_t *data)
{
    uint32_t primask = __get_PRIMASK();

    __asm("cpsid i");

    /* Program page */
    SPIFI_ResetCommand(MFLASH_SPIFI);
    SPIFI_SetCommand(MFLASH_SPIFI, &command[WRITE_ENABLE]);
    SPIFI_SetCommandAddress(MFLASH_SPIFI, page_addr);
    SPIFI_SetCommand(MFLASH_SPIFI, &command[PROGRAM_PAGE]);

    /* Store 4B in each loop. Sector has always 4B alignment and size multiple of 4 */
    for (uint32_t i = 0; i < MFLASH_PAGE_SIZE / sizeof(data[0]); i++)
    {
        SPIFI_WriteData(MFLASH_SPIFI, data[i]);
    }

    mflash_drv_check_if_finish();
    /* Switch to read mode to enable interrupts as soon ass possible */
    mflash_drv_read_mode();

    if (primask == 0)
    {
        __asm("cpsie i");
    }

    /* Flush pipeline to allow pending interrupts take place */
    __ISB();

    return kStatus_Success;
}

/* API - Page program - calling wrapper */
int32_t mflash_drv_page_program(uint32_t page_addr, uint32_t *data)
{
    return mflash_drv_page_program_internal(page_addr, data);
}

/* API - Read data */
int32_t mflash_drv_read(uint32_t addr, uint32_t *buffer, uint32_t len)
{
    void *ptr = mflash_drv_phys2log(addr, len);

    if (ptr == NULL)
    {
        return kStatus_InvalidArgument;
    }

    memcpy(buffer, ptr, len);
    return kStatus_Success;
}

/* API - Get pointer to FLASH region */
void *mflash_drv_phys2log(uint32_t addr, uint32_t len)
{
    uint32_t last_addr = addr + (len != 0 ? len - 1 : 0);

    if (last_addr > (FSL_FEATURE_SPIFI_END_ADDR - FSL_FEATURE_SPIFI_START_ADDR))
    {
        return NULL;
    }

    return (void *)(addr + FSL_FEATURE_SPIFI_START_ADDR);
}

/* API - Get pointer to FLASH region */
uint32_t mflash_drv_log2phys(void *ptr, uint32_t len)
{
    uint32_t log_addr = (uint32_t)ptr;

    if (log_addr < FSL_FEATURE_SPIFI_START_ADDR || log_addr > FSL_FEATURE_SPIFI_END_ADDR)
    {
        return MFLASH_INVALID_ADDRESS;
    }

    if (log_addr + len > FSL_FEATURE_SPIFI_END_ADDR + 1)
    {
        return MFLASH_INVALID_ADDRESS;
    }

    return (log_addr - FSL_FEATURE_SPIFI_START_ADDR);
}
