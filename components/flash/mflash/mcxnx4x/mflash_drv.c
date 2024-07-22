/*
 * Copyright 2017-2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <string.h>

#include "mflash_drv.h"
#include "fsl_flash.h"
#include "pin_mux.h"

static flash_config_t g_flash_instance = {0};

static uint32_t g_pflashBlockBase  = 0;
static uint32_t g_pflashTotalSize  = 0;
static uint32_t g_pflashSectorSize = 0;
static uint32_t g_pflashPageSize   = 0;

/* API - initialize 'mflash' */
int32_t mflash_drv_init(void)
{
    status_t result;

    result = FLASH_Init(&g_flash_instance);
    if (result != kStatus_Success)
        return result;

    result = FLASH_GetProperty(&g_flash_instance, kFLASH_PropertyPflashBlockBaseAddr, &g_pflashBlockBase);
    if (result != kStatus_Success)
        return result;

    result = FLASH_GetProperty(&g_flash_instance, kFLASH_PropertyPflashSectorSize, &g_pflashSectorSize);
    if (result != kStatus_Success)
        return result;

    result = FLASH_GetProperty(&g_flash_instance, kFLASH_PropertyPflashTotalSize, &g_pflashTotalSize);
    if (result != kStatus_Success)
        return result;

    result = FLASH_GetProperty(&g_flash_instance, kFLASH_PropertyPflashPageSize, &g_pflashPageSize);

    return result;
}

/* API - Erase single sector */
int32_t mflash_drv_sector_erase(uint32_t sector_addr)
{
    if (0 == mflash_drv_is_sector_aligned(sector_addr))
        return kStatus_InvalidArgument;

    return FLASH_Erase(&g_flash_instance, sector_addr, MFLASH_SECTOR_SIZE, kFLASH_ApiEraseKey);
}

/* API - Page program */
int32_t mflash_drv_page_program(uint32_t page_addr, uint32_t *data)
{
    if (0 == mflash_drv_is_page_aligned(page_addr))
        return kStatus_InvalidArgument;

    return FLASH_Program(&g_flash_instance, page_addr, (uint8_t *)data, MFLASH_PAGE_SIZE);
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
    /* FLASH is directly mapped in the address space */
    return (void *)(addr);
}

/* API - Get pointer to FLASH region */
uint32_t mflash_drv_log2phys(void *ptr, uint32_t len)
{
    /* FLASH is directly mapped in the address space */
    return ((uint32_t)ptr);
}
