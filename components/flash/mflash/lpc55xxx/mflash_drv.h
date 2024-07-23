/*
 * Copyright 2017-2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __MFLASH_DRV_H__
#define __MFLASH_DRV_H__

#include "mflash_common.h"

/* Flash constants */

/*
 * The value is not sector size as reported by FLASH_GetProperty() in mflash_drv_init().
 * this platform can erase/program the flash memory by smaller block (actually page size).
 */
#ifndef MFLASH_SECTOR_SIZE
#define MFLASH_SECTOR_SIZE (512U)
#endif

#ifndef MFLASH_PAGE_SIZE
#define MFLASH_PAGE_SIZE (512U)
#endif

#ifndef MFLASH_BASE_ADDRESS
#define MFLASH_BASE_ADDRESS (0U)
#endif

#define MFLASH_PAGE_INTEGRITY_CHECKS (1)

int32_t mflash_drv_is_readable(uint32_t addr);

#endif
