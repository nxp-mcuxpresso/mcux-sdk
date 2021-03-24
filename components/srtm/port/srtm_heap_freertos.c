/*
 * Copyright 2017, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <FreeRTOS.h>

#include "srtm_heap.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SRTM_HEAP_STAT_COUNT_MASK (0x3FU)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
#ifdef SRTM_DEBUG_MESSAGE_FUNC
static uint32_t count;
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
void *SRTM_Heap_Malloc(uint32_t size)
{
#ifdef SRTM_DEBUG_MESSAGE_FUNC
    size_t freeSize, minFreeSize;

    if (((++count) & SRTM_HEAP_STAT_COUNT_MASK) == 0U)
    {
        freeSize    = xPortGetFreeHeapSize();
        minFreeSize = xPortGetMinimumEverFreeHeapSize();
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "#### Heap free space 0x%x, min 0x%x ####\r\n", freeSize,
                           minFreeSize);
    }
#endif
    return pvPortMalloc(size);
}

void SRTM_Heap_Free(void *buf)
{
    vPortFree(buf);
}
