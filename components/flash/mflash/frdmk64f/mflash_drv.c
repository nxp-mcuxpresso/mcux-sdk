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

/*! @brief Flash driver Structure */
static flash_config_t s_flashDriver;

/* API - initialize 'mflash' */
int32_t mflash_drv_init(void)
{
    int32_t result = 0;

    /* Clean up Flash driver Structure*/
    memset(&s_flashDriver, 0, sizeof(flash_config_t));

    /* Setup flash driver structure for device and initialize variables. */
    result = FLASH_Init(&s_flashDriver);
    return result;
}

/* API - Erase single sector */
int32_t mflash_drv_sector_erase(uint32_t sector_addr)
{
    int32_t result = 0;
    if (0 == mflash_drv_is_sector_aligned(sector_addr))
        return kStatus_InvalidArgument;

    result = FLASH_Erase(&s_flashDriver, sector_addr, MFLASH_SECTOR_SIZE, kFLASH_ApiEraseKey);
    return result;
}

/* Internal - write single sector */
static int32_t mflash_drv_sector_program(uint32_t sector_addr, uint32_t *sector_data, uint32_t sector_data_length)
{
    int32_t result = 0;
    if (0 == mflash_drv_is_sector_aligned(sector_addr))
        return kStatus_InvalidArgument;

    result = FLASH_Program(&s_flashDriver, (uint32_t)sector_addr, (uint8_t *)sector_data, sector_data_length);
    return result;
}

/* API - Calling wrapper, page is the same as sector on this platform */
int32_t mflash_drv_page_program(uint32_t page_addr, uint32_t *data)
{
    return mflash_drv_sector_program(page_addr, data, MFLASH_PAGE_SIZE);
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
