/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_CACHE_H_
#define FSL_CACHE_H_

#include "fsl_common.h"

/*!
 * @addtogroup cache_lpcac
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief cache driver version 2.1.1. */
#define FSL_CACHE_DRIVER_VERSION (MAKE_VERSION(2, 1, 1))
/*! @} */
/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name cache control for the L1 low power cache controller
 *@{
 */

/*!
 * @brief Enables the processor code bus cache.
 *
 */
static inline void L1CACHE_EnableCodeCache(void)
{
    MCM->CPCR2 &= ~MCM_CPCR2_DCBC_MASK;
}

/*!
 * @brief Disables the processor code bus cache.
 *
 */
static inline void L1CACHE_DisableCodeCache(void)
{
    MCM->CPCR2 |= MCM_CPCR2_DCBC_MASK;
}

/*!
 * @brief Invalidates the processor code bus cache.
 *
 */
static inline void L1CACHE_InvalidateCodeCache(void)
{
    MCM->CPCR2 |= MCM_CPCR2_CCBC_MASK;
}

/*! @} */

/*!
 * @name The unified L1 cache controller
 *  The LPCAC is write-through design, so there is no cache maintain by range
 *  control operation. So all cache maintain by range unified functions
 *  are directly call the cache maintain all functions since they have the same effect.
 *@{
 */

/*!
 * @brief Invalidates L1 instrument cache by range.
 *
 * @param address  The start address of the memory to be invalidated.
 * @param size_byte  The memory size.
 */
void L1CACHE_InvalidateICacheByRange(uint32_t address, uint32_t size_byte);

/*!
 * @brief Invalidates L1 data cache by range.
 *
 * @param address  The start address of the memory to be invalidated.
 * @param size_byte  The memory size.
 */
static inline void L1CACHE_InvalidateDCacheByRange(uint32_t address, uint32_t size_byte)
{
    L1CACHE_InvalidateICacheByRange(address, size_byte);
}

/*!
 * @brief Cleans L1 data cache by range.
 *
 * The cache is write through mode, so there is nothing to do with
 * the cache flush/clean operation.
 *
 * @param address  The start address of the memory to be cleaned.
 * @param size_byte  The memory size.
 */
static inline void L1CACHE_CleanDCacheByRange(uint32_t address, uint32_t size_byte)
{
}

/*!
 * @brief Cleans and Invalidates L1 data cache by range.
 *
 * @param address  The start address of the memory to be clean and invalidated.
 * @param size_byte  The memory size.
 */
static inline void L1CACHE_CleanInvalidateDCacheByRange(uint32_t address, uint32_t size_byte)
{
    L1CACHE_InvalidateDCacheByRange(address, size_byte);
}

/*! @} */

/*!
 * @name Unified Cache Control for caches in all levels
 *@{
 */

/*!
 * @brief Invalidates instruction cache by range.
 *
 * @param address The physical address.
 * @param size_byte size of the memory to be invalidated.
 */
static inline void ICACHE_InvalidateByRange(uint32_t address, uint32_t size_byte)
{
    L1CACHE_InvalidateICacheByRange(address, size_byte);
}

/*!
 * @brief Invalidates data cache by range.
 *
 * @param address The physical address.
 * @param size_byte size of the memory to be invalidated.
 */
static inline void DCACHE_InvalidateByRange(uint32_t address, uint32_t size_byte)
{
    L1CACHE_InvalidateDCacheByRange(address, size_byte);
}

/*!
 * @brief Clean data cache by range.
 *
 * @param address The physical address.
 * @param size_byte size of the memory to be cleaned.
 */
static inline void DCACHE_CleanByRange(uint32_t address, uint32_t size_byte)
{
    L1CACHE_CleanDCacheByRange(address, size_byte);
}

/*!
 * @brief Cleans and Invalidates data cache by range.
 *
 * @param address The physical address.
 * @param size_byte size of the memory to be Cleaned and Invalidated.
 */
static inline void DCACHE_CleanInvalidateByRange(uint32_t address, uint32_t size_byte)
{
    L1CACHE_CleanInvalidateDCacheByRange(address, size_byte);
}

/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_CACHE_H_*/
