/*
 * Copyright 2017-2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <string.h>

#include "mflash_drv.h"
#include "fsl_romapi.h"
#include "pin_mux.h"

static flash_config_t g_flash_instance;

static uint32_t pflashBlockBase;
static uint32_t pflashTotalSize;
static uint32_t pflashSectorSize;
static uint32_t pflashPageSize;

/* API - initialize 'mflash' */
int32_t mflash_drv_init(void)
{
    status_t result;

    result = FLASH_API->flash_init(&g_flash_instance);
    if (result != kStatus_Success)
    {
        return result;
    }

    result = FLASH_API->flash_get_property(&g_flash_instance, kFLASH_PropertyPflashBlockBaseAddr, &pflashBlockBase);
    if (result != kStatus_Success)
    {
        return result;
    }

    result = FLASH_API->flash_get_property(&g_flash_instance, kFLASH_PropertyPflashSectorSize, &pflashSectorSize);
    if (result != kStatus_Success)
    {
        return result;
    }

    result = FLASH_API->flash_get_property(&g_flash_instance, kFLASH_PropertyPflashTotalSize, &pflashTotalSize);
    if (result != kStatus_Success)
    {
        return result;
    }

    result = FLASH_API->flash_get_property(&g_flash_instance, kFLASH_PropertyPflashPageSize, &pflashPageSize);
    if (result != kStatus_Success)
    {
        return result;
    }

    if ((pflashSectorSize != MFLASH_SECTOR_SIZE) || (pflashPageSize != MFLASH_PAGE_SIZE))
    {
        return kStatus_Fail;
    }

    return kStatus_Success;
}

/* API - Erase single sector */
int32_t mflash_drv_sector_erase(uint32_t sector_addr)
{
    if (false == mflash_drv_is_sector_aligned(sector_addr))
    {
        return kStatus_InvalidArgument;
    }
    else
    {
        return FLASH_API->flash_erase_sector(&g_flash_instance, sector_addr, MFLASH_SECTOR_SIZE, kFLASH_ApiEraseKey);
    }
}

/* API - Page program */
int32_t mflash_drv_page_program(uint32_t page_addr, uint32_t *data)
{
    if (false == mflash_drv_is_page_aligned(page_addr))
    {
        return kStatus_InvalidArgument;
    }
    else
    {
        return FLASH_API->flash_program_page(&g_flash_instance, page_addr, (uint8_t *)data, MFLASH_PAGE_SIZE);
    }
}

/* API - Phrase program */
int32_t mflash_drv_phrase_program(uint32_t page_addr, uint32_t *data)
{
    if (false == mflash_drv_is_phrase_aligned(page_addr))
    {
        return kStatus_InvalidArgument;
    }
    else
    {
        return FLASH_API->flash_program_phrase(&g_flash_instance, page_addr, (uint8_t *)data, MFLASH_PHRASE_SIZE);
    }
}

/* API - Read data */
int32_t mflash_drv_read(uint32_t addr, uint32_t *buffer, uint32_t len)
{
    (void)memcpy(buffer, (void *)addr, len);
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
