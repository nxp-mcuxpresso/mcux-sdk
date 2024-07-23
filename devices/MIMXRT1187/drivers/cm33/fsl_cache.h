/*
 * Copyright 2022 - 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_CACHE_H_
#define FSL_CACHE_H_

#include "fsl_common.h"

/*!
 * @addtogroup xcache
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief cache driver version. */
#define FSL_CACHE_DRIVER_VERSION (MAKE_VERSION(2, 0, 1))
/*! @} */

/*! @brief cache line size. */
#define XCACHE_LINESIZE_BYTE (FSL_FEATURE_XCACHE_LINESIZE_BYTE)

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name cache control for XCACHE
 *@{
 */

/*!
 * brief Returns an instance number given physical memory address.
 *
 * param address The physical memory address.
 * @return XCACHE instance number starting from 0.
 */
uint32_t XCACHE_GetInstanceByAddr(uint32_t address);

/*!
 * @brief Enables the cache.
 *
 * @param base XCACHE peripheral base address.
 *
 */
void XCACHE_EnableCache(XCACHE_Type *base);

/*!
 * @brief Disables the cache.
 *
 * @param base XCACHE peripheral base address.
 *
 */
void XCACHE_DisableCache(XCACHE_Type *base);

/*!
 * @brief Invalidates the cache.
 *
 * @param base XCACHE peripheral base address.
 *
 */
void XCACHE_InvalidateCache(XCACHE_Type *base);

/*!
 * @brief Invalidates cache by range.
 *
 * @param address The physical address of cache.
 * @param size_byte size of the memory to be invalidated, should be larger than 0, better to align with cache line size.
 * @note Address and size should be aligned to "XCACHE_LINESIZE_BYTE".
 * The startAddr here will be forced to align to XCACHE_LINESIZE_BYTE if
 * startAddr is not aligned. For the size_byte, application should make sure the
 * alignment or make sure the right operation order if the size_byte is not aligned.
 */
void XCACHE_InvalidateCacheByRange(uint32_t address, uint32_t size_byte);

/*!
 * @brief Cleans the cache.
 *
 * @param base XCACHE peripheral base address.
 *
 */
void XCACHE_CleanCache(XCACHE_Type *base);

/*!
 * @brief Cleans cache by range.
 *
 * @param address The physical address of cache.
 * @param size_byte size of the memory to be cleaned, should be larger than 0, better to align with cache line size.
 * @note Address and size should be aligned to "XCACHE_LINESIZE_BYTE".
 * The startAddr here will be forced to align to XCACHE_LINESIZE_BYTE if
 * startAddr is not aligned. For the size_byte, application should make sure the
 * alignment or make sure the right operation order if the size_byte is not aligned.
 */
void XCACHE_CleanCacheByRange(uint32_t address, uint32_t size_byte);

/*!
 * @brief Cleans and invalidates the cache.
 *
 * @param base XCACHE peripheral base address.
 *
 */
void XCACHE_CleanInvalidateCache(XCACHE_Type *base);

/*!
 * @brief Cleans and invalidate cache by range.
 *
 * @param address The physical address of cache.
 * @param size_byte size of the memory to be Cleaned and Invalidated, should be larger than 0,
            better to align with cache line size.
 * @note Address and size should be aligned to "XCACHE_LINESIZE_BYTE".
 * The startAddr here will be forced to align to XCACHE_LINESIZE_BYTE if
 * startAddr is not aligned. For the size_byte, application should make sure the
 * alignment or make sure the right operation order if the size_byte is not aligned.
 */
void XCACHE_CleanInvalidateCacheByRange(uint32_t address, uint32_t size_byte);

#if !((defined(FSL_FEATURE_XCACHE_HAS_NO_WRITE_BUF)) && (FSL_FEATURE_XCACHE_HAS_NO_WRITE_BUF))
/*!
 * @brief Enables/disables the write buffer.
 *
 * @param base XCACHE peripheral base address.
 * @param enable The enable or disable flag.
 *       true  - enable the write buffer.
 *       false - disable the write buffer.
 */
void XCACHE_EnableWriteBuffer(XCACHE_Type *base, bool enable);
#endif

/*! @} */

/*!
 * @name Unified Cache Control for all caches
 *@{
 */

/*!
 * @brief Invalidates instruction cache by range.
 *
 * @param address The physical address.
 * @param size_byte size of the memory to be invalidated, should be larger than 0, better to align with cache line size.
 * @note Address and size should be aligned to XCACHE_LINESIZE_BYTE due to the cache operation unit
 * FSL_FEATURE_XCACHE_LINESIZE_BYTE. The startAddr here will be forced to align to the cache line
 * size if startAddr is not aligned. For the size_byte, application should make sure the
 * alignment or make sure the right operation order if the size_byte is not aligned.
 */
static inline void ICACHE_InvalidateByRange(uint32_t address, uint32_t size_byte)
{
    XCACHE_InvalidateCacheByRange(address, size_byte);
}

/*!
 * @brief Invalidates data cache by range.
 *
 * @param address The physical address.
 * @param size_byte size of the memory to be invalidated, should be larger than 0, better to align with cache line size.
 * @note Address and size should be aligned to XCACHE_LINESIZE_BYTE due to the cache operation unit
 * FSL_FEATURE_XCACHE_LINESIZE_BYTE. The startAddr here will be forced to align to the cache line
 * size if startAddr is not aligned. For the size_byte, application should make sure the
 * alignment or make sure the right operation order if the size_byte is not aligned.
 */
static inline void DCACHE_InvalidateByRange(uint32_t address, uint32_t size_byte)
{
    XCACHE_InvalidateCacheByRange(address, size_byte);
}

/*!
 * @brief Clean data cache by range.
 *
 * @param address The physical address.
 * @param size_byte size of the memory to be cleaned, should be larger than 0, better to align with cache line size.
 * @note Address and size should be aligned to XCACHE_LINESIZE_BYTE due to the cache operation unit
 * FSL_FEATURE_XCACHE_LINESIZE_BYTE. The startAddr here will be forced to align to the cache line
 * size if startAddr is not aligned. For the size_byte, application should make sure the
 * alignment or make sure the right operation order if the size_byte is not aligned.
 */
static inline void DCACHE_CleanByRange(uint32_t address, uint32_t size_byte)
{
    XCACHE_CleanCacheByRange(address, size_byte);
}

/*!
 * @brief Cleans and Invalidates data cache by range.
 *
 * @param address The physical address.
 * @param size_byte size of the memory to be Cleaned and Invalidated, should be larger than 0,
                better to align with cache line size.
 * @note Address and size should be aligned to XCACHE_LINESIZE_BYTE due to the cache operation unit
 * FSL_FEATURE_XCACHE_LINESIZE_BYTE. The startAddr here will be forced to align to the cache line
 * size if startAddr is not aligned. For the size_byte, application should make sure the
 * alignment or make sure the right operation order if the size_byte is not aligned.
 */
static inline void DCACHE_CleanInvalidateByRange(uint32_t address, uint32_t size_byte)
{
    XCACHE_CleanInvalidateCacheByRange(address, size_byte);
}

/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_CACHE_H_*/
