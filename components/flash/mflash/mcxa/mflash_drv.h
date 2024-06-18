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
#define MFLASH_SECTOR_SIZE (8192U)
#endif

#ifndef MFLASH_PAGE_SIZE
#define MFLASH_PAGE_SIZE (128U)
#endif

#ifndef MFLASH_PHRASE_SIZE
#define MFLASH_PHRASE_SIZE (16U)
#endif

#ifndef MFLASH_BASE_ADDRESS
#define MFLASH_BASE_ADDRESS (0U)
#endif

#define MFLASH_PAGE_INTEGRITY_CHECKS (1U)

#define mflash_drv_is_phrase_aligned(x) (((x) % (MFLASH_PHRASE_SIZE)) == 0U)

/*! @brief Writes single phrase */
int32_t mflash_drv_phrase_program(uint32_t page_addr, uint32_t *data);

static inline int32_t mflash_drv_is_readable(uint32_t addr)
{
    return kStatus_Success;
}

#endif
