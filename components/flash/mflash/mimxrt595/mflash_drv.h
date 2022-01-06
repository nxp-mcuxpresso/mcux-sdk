/*
 * Copyright 2017-2021 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __MFLASH_DRV_H__
#define __MFLASH_DRV_H__

#include "mflash_common.h"

/* Flash constants */
#ifndef MFLASH_SECTOR_SIZE
#define MFLASH_SECTOR_SIZE (4096U)
#endif

#ifndef MFLASH_PAGE_SIZE
#define MFLASH_PAGE_SIZE (256U)
#endif

/* Device specific settings */
#ifndef MFLASH_FLEXSPI
#define MFLASH_FLEXSPI (FLEXSPI0)
#endif
#ifndef MFLASH_FLEXSPI_ROOTCLK_HZ
#define MFLASH_FLEXSPI_ROOTCLK_HZ (198000000U)
#endif

#ifndef MFLASH_BASE_ADDRESS
#define MFLASH_BASE_ADDRESS (FlexSPI0_AMBA_BASE)
#endif

#define FLASH_SIZE 0x00010000U /* 64MB in KB unit */

#endif
