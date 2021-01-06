/*
 * Copyright 2018-2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __MFLASH_DRV_H__
#define __MFLASH_DRV_H__

#include "mflash_common.h"

/* Flash constants */
#ifndef MFLASH_SECTOR_SIZE
#define MFLASH_SECTOR_SIZE (0x1000)
#endif

#ifndef MFLASH_PAGE_SIZE
#define MFLASH_PAGE_SIZE (256)
#endif

#ifndef MFLASH_FLEXSPI
#define MFLASH_FLEXSPI (FLEXSPI)
#endif

#ifndef MFLASH_BASE_ADDRESS
#define MFLASH_BASE_ADDRESS (FlexSPI_AMBA_BASE)
#endif

/* Allow incremental writes without erase (enabled by default).
 * This method cannot be used in certain cases, e.g. when page checksums are used
 */
#ifndef MFLASH_INC_WRITE
#define MFLASH_INC_WRITE 1
#endif

/* API used by OTA applications */
int32_t mflash_drv_write(uint32_t addr, const uint8_t *data, uint32_t data_len);

#endif
