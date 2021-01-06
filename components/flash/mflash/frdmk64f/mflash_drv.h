/*
 * Copyright 2017-2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __MFLASH_DRV_H__
#define __MFLASH_DRV_H__

#include "mflash_common.h"

/* Flash constants */
#ifndef MFLASH_SECTOR_SIZE
#define MFLASH_SECTOR_SIZE (4096)
#endif

/* Page is the same as sector on this platform */
#ifndef MFLASH_PAGE_SIZE
#define MFLASH_PAGE_SIZE (MFLASH_SECTOR_SIZE)
#endif

#endif
