/*
 * Copyright 2017, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SRTM_HEAP_H__
#define __SRTM_HEAP_H__

#include <srtm_defs.h>

/*!
 * @addtogroup srtm
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Allocate a block of memory from heap.
 *
 * @param size bytes to allocate.
 *
 * @return allocated buffer address.
 */
void *SRTM_Heap_Malloc(uint32_t size);

/*!
 * @brief Free the allocated memory.
 *
 * @param buf the address of the allocated buffer
 */
void SRTM_Heap_Free(void *buf);

#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* __SRTM_HEAP_H__ */
