/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __MFLASH_DRV_H__
#define __MFLASH_DRV_H__

#include "mflash_common.h"

#define MFLASH_SECTOR_SIZE (4096U)

#define MFLASH_PAGE_SIZE (256U)

#define MFLASH_BASE_ADDRESS (XSPI0_AMBA_BASE)

#define MFLASH_FLASH_SIZE (64UL * 1024UL * 1024UL)

#endif
