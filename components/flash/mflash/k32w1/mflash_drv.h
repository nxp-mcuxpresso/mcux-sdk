/*
 * Copyright 2022 NXP
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
#define MFLASH_SECTOR_SIZE (8192U)
#endif

#ifndef MFLASH_PAGE_SIZE
#define MFLASH_PAGE_SIZE (128U)
#endif

#endif
