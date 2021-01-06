/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_cache.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.cache_lpcac"
#endif

#define L1CACHE_CODEBUSADDR_BOUNDARY (0x1FFFFFFFU) /*!< The processor code bus address boundary. */

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * brief Invalidates L1 instrument cache by range.
 *
 * param address  The start address of the memory to be invalidated.
 * param size_byte  The memory size.
 */
void L1CACHE_InvalidateICacheByRange(uint32_t address, uint32_t size_byte)
{
    if (address <= L1CACHE_CODEBUSADDR_BOUNDARY)
    {
        L1CACHE_InvalidateCodeCache();
    }
}
