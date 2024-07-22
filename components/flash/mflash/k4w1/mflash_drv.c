/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <string.h>

#include "mflash_drv.h"
#include "fsl_flash.h"
#include "fsl_mcm.h"
#include "pin_mux.h"

static flash_config_t s_flashDriver = {0};

static uint32_t pflashBlock0Base = 0;
static uint32_t pflashBlock0Size = 0;
static uint32_t pflashSectorSize = 0;
static uint32_t pflashBlockCount = 0;
static uint32_t pflashTotalSize  = 0;

/* API - initialize 'mflash' */
int32_t mflash_drv_init(void)
{
    status_t result;

    (void)memset(&s_flashDriver, 0, sizeof(flash_config_t));

    result = FLASH_Init(&s_flashDriver);
    if (result != kStatus_Success)
    {
        return result;
    }

#if defined(SMSCM_CACHE_CLEAR_MASK) && SMSCM_CACHE_CLEAR_MASK
    /* disable flash cache/Prefetch */
    FLASH_CACHE_Disable();
#endif /* SMSCM_CACHE_CLEAR_MASK */

    result = FLASH_GetProperty(&s_flashDriver, kFLASH_PropertyPflash0BlockBaseAddr, &pflashBlock0Base);
    if (result != kStatus_Success)
    {
        return result;
    }

    result = FLASH_GetProperty(&s_flashDriver, kFLASH_PropertyPflash0BlockSize, &pflashBlock0Size);
    if (result != kStatus_Success)
    {
        return result;
    }

    result = FLASH_GetProperty(&s_flashDriver, kFLASH_PropertyPflash0SectorSize, &pflashSectorSize);
    if (result != kStatus_Success)
    {
        return result;
    }

    result = FLASH_GetProperty(&s_flashDriver, kFLASH_PropertyPflash0BlockCount, &pflashBlockCount);
    if (result != kStatus_Success)
    {
        return result;
    }

    result = FLASH_GetProperty(&s_flashDriver, kFLASH_PropertyPflash0TotalSize, &pflashTotalSize);

    return result;
}

/* API - Erase single sector */
int32_t mflash_drv_sector_erase(uint32_t sector_addr)
{
    uint32_t primask = 0;
    int32_t ret      = kStatus_Fail;

    primask = DisableGlobalIRQ();

    flash_cache_speculation_control(true, FLASH);

    ret = FLASH_Erase(&s_flashDriver, FLASH, sector_addr, MFLASH_SECTOR_SIZE, (uint32_t)kFLASH_ApiEraseKey);

    /* Clear code bus cache */
    MCM_ClearCodeBusCache(MCM);

    flash_cache_speculation_control(false, FLASH);

    EnableGlobalIRQ(primask);

    return ret;
}

/* API - Page program */
int32_t mflash_drv_page_program(uint32_t page_addr, uint32_t *data)
{
    uint32_t primask = 0;
    int32_t ret      = kStatus_Fail;

    primask = DisableGlobalIRQ();

    flash_cache_speculation_control(true, FLASH);

    ret = FLASH_ProgramPage(&s_flashDriver, FLASH, page_addr, (uint8_t *)data, MFLASH_PAGE_SIZE);

    /* Clear code bus cache */
    MCM_ClearCodeBusCache(MCM);

    flash_cache_speculation_control(false, FLASH);

    EnableGlobalIRQ(primask);

    return ret;
}

/* API - Read data */
int32_t mflash_drv_read(uint32_t addr, uint32_t *buffer, uint32_t len)
{
    (void)memcpy((void *)buffer, (void *)(uint32_t *)addr, len);

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