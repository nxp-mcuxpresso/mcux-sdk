/*
 * Copyright 2017-2020, 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <string.h>

#include "mflash_drv.h"
#include "fsl_iap.h"
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
    if (result == kStatus_Success)
	{
        result = FLASH_GetProperty(&g_flash_instance, kFLASH_PropertyPflashBlockBaseAddr, &g_pflashBlockBase);
	}

    
    if (result == kStatus_Success)
	{
        result = FLASH_GetProperty(&g_flash_instance, kFLASH_PropertyPflashSectorSize, &g_pflashSectorSize);
	}

    
    if (result == kStatus_Success)
	{
        result = FLASH_GetProperty(&g_flash_instance, kFLASH_PropertyPflashTotalSize, &g_pflashTotalSize);
	}

    
    if (result == kStatus_Success)
	{
        result = FLASH_GetProperty(&g_flash_instance, kFLASH_PropertyPflashPageSize, &g_pflashPageSize);
	}

    return result;
}

/* API - Erase single sector */
int32_t mflash_drv_sector_erase(uint32_t sector_addr)
{
	status_t result;
    if (0 == mflash_drv_is_sector_aligned(sector_addr))
    {
        result = kStatus_InvalidArgument;		
    }
    else 
    {
        result = FLASH_Erase(&g_flash_instance, sector_addr, MFLASH_SECTOR_SIZE, (uint32_t)kFLASH_ApiEraseKey);
    }

    return result;
}

/* API - Page program */
int32_t mflash_drv_page_program(uint32_t page_addr, uint32_t *data)
{
    status_t result;
    if (0 == mflash_drv_is_page_aligned(page_addr))
    {
        result = kStatus_InvalidArgument;		
    }
    else 
    {
        result = FLASH_Program(&g_flash_instance, page_addr, (uint8_t *)data, MFLASH_PAGE_SIZE);
    }
	
    return result;
}

/* Internal - check FLASH status to avoid hardfault */
int32_t mflash_drv_is_readable(uint32_t addr)
{
#define FLASH_READMODE_ECC_MASK     (0x4U)
#define FLASH_READMODE_ECC_SHIFT    (2U)
#define FLASH_READMODE_ECC(x)       (((uint32_t)(((uint32_t)(x)) << FLASH_READMODE_ECC_SHIFT)) & FLASH_READMODE_ECC_MASK)
#define FLASH_READMODE_MARGIN_MASK  (0xC00U)
#define FLASH_READMODE_MARGIN_SHIFT (10U)
#define FLASH_READMODE_MARGIN(x) \
    (((uint32_t)(((uint32_t)(x)) << FLASH_READMODE_MARGIN_SHIFT)) & FLASH_READMODE_MARGIN_MASK)
#define FLASH_READMODE_DMACC_MASK  (0x8000U)
#define FLASH_READMODE_DMACC_SHIFT (15U)
#define FLASH_READMODE_DMACC(x) \
    (((uint32_t)(((uint32_t)(x)) << FLASH_READMODE_DMACC_SHIFT)) & FLASH_READMODE_DMACC_MASK)

    uint32_t result = 0, result_mask = 0;

    FLASH->INT_CLR_STATUS = FLASH_INT_CLR_STATUS_FAIL_MASK | FLASH_INT_CLR_STATUS_ERR_MASK |
                            FLASH_INT_CLR_STATUS_DONE_MASK | FLASH_INT_CLR_STATUS_ECC_ERR_MASK;
    FLASH->STARTA   = addr >> 4;
    FLASH->DATAW[0] = FLASH_READMODE_ECC(g_flash_instance.modeConfig.readSingleWord.readWithEccOff) |
                      FLASH_READMODE_MARGIN(g_flash_instance.modeConfig.readSingleWord.readMarginLevel) |
                      FLASH_READMODE_DMACC(g_flash_instance.modeConfig.readSingleWord.readDmaccWord);
    FLASH->CMD = 3;
    while ((FLASH->INT_STATUS & FLASH_INT_STATUS_DONE_MASK) == 0UL)
    {
		//Wait for STATUS DONE flag
    }
    result = FLASH->INT_STATUS;

    /* Report failure in case of errors */
    result_mask = FLASH_INT_STATUS_FAIL_MASK | FLASH_INT_STATUS_ERR_MASK | FLASH_INT_STATUS_ECC_ERR_MASK;

    return (result_mask & result) == 0UL ? kStatus_Success : kStatus_Fail;
}

/* API - Read data */
int32_t mflash_drv_read(uint32_t addr, uint32_t *buffer, uint32_t len)
{
	status_t result = kStatus_Fail;
    if (mflash_drv_is_readable(addr) == 0)
    {
		(void)memcpy((void *)buffer, (void *)addr, len);
        result = kStatus_Success;
    }

    return result;
}

/* API - Get pointer to FLASH region */
void *mflash_drv_phys2log(uint32_t addr, uint32_t len)
{
#if 0
    if (mflash_drv_is_readable(addr) != 0)
    {
        return NULL;
    }
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
