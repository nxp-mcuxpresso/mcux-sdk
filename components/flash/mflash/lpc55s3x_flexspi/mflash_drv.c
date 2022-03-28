/*
 * Copyright 2017-2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <string.h>

#include "mflash_drv.h"
#include "fsl_flash.h"
#include "fsl_flexspi_nor_flash.h"
#include "pin_mux.h"

#define FLASH_BASE_ADDR 0x08000000

static flexspi_nor_config_t flashConfig;

/* API - initialize 'mflash' */
int32_t mflash_drv_init(void)
{
    status_t result;

    serial_nor_config_option_t option;
    option.option0.U = 0xc0000001U;
    option.option1.U = 0x00000000;

    result = FLEXSPI_NorFlash_GetConfig(0, &flashConfig, &option);
    if (result != kStatus_Success)
        return result;

    result = FLEXSPI_NorFlash_Init(0, &flashConfig);
    if (result != kStatus_Success)
        return result;

    return result;
}

/* API - Erase single sector */
int32_t mflash_drv_sector_erase(uint32_t sector_addr)
{
    assert(sector_addr >= FLASH_BASE_ADDR);
    if (0 == mflash_drv_is_sector_aligned(sector_addr))
        return kStatus_InvalidArgument;

    return FLEXSPI_NorFlash_Erase(0, (flexspi_nor_config_t *)&flashConfig, (sector_addr - FLASH_BASE_ADDR),
                                  flashConfig.sectorSize);
}

/* API - Page program */
int32_t mflash_drv_page_program(uint32_t page_addr, uint32_t *data)
{
    assert(page_addr >= FLASH_BASE_ADDR);
    if (0 == mflash_drv_is_page_aligned(page_addr))
        return kStatus_InvalidArgument;

    return FLEXSPI_NorFlash_ProgramPage(0, &flashConfig, (page_addr - FLASH_BASE_ADDR), (uint32_t *)data);
}

/* API - Read data */
int32_t mflash_drv_read(uint32_t addr, uint32_t *buffer, uint32_t len)
{
    memcpy(buffer, (void *)addr, len);

    return kStatus_Success;
}

/* API - Get pointer to FLASH region */
void *mflash_drv_phys2log(uint32_t addr, uint32_t len)
{
#if 0
    if (mflash_drv_is_readable(addr) != 0)
        return NULL;
#endif

    /* FLASH is directly mapped in the address space */
    return (void *)(addr);
}

/* API - Get pointer to FLASH region */
uint32_t mflash_drv_log2phys(void *ptr, uint32_t len)
{
    /* FLASH is directly mapped in the address space */
    return ((uint32_t)ptr);
}
