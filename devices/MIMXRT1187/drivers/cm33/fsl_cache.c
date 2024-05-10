/*
 * Copyright 2022 - 2023 NXP
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
#define FSL_COMPONENT_ID "platform.drivers.cache_xcache"
#endif

#if (FSL_FEATURE_SOC_XCACHE_COUNT > 0)
/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Array of XCACHE peripheral base address. */
static XCACHE_Type *const s_xcachectrlBases[] = XCACHE_BASE_PTRS;

/* Array of XCACHE physical memory base address. */
static uint32_t const s_xcachePhymemBases[] = XCACHE_PHYMEM_BASES;
/* Array of XCACHE physical memory size. */
static uint32_t const s_xcachePhymemSizes[] = XCACHE_PHYMEM_SIZES;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
#ifdef XCACHE_CLOCKS
/* Array of XCACHE clock name. */
static const clock_ip_name_t s_xcacheClocks[] = XCACHE_CLOCKS;
#endif
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * brief Returns an instance number given physical memory address.
 *
 * param address The physical memory address.
 * return XCACHE instance number starting from 0.
 */
uint32_t XCACHE_GetInstanceByAddr(uint32_t address)
{
    uint32_t i;

    for (i = 0; i < ARRAY_SIZE(s_xcachectrlBases); i++)
    {
        if ((address >= s_xcachePhymemBases[i]) &&
            (address < (s_xcachePhymemBases[i] + s_xcachePhymemSizes[i] - 0x01U)))
        {
            break;
        }
    }

    return i;
}

/*!
 * brief Enables the cache.
 *
 */
void XCACHE_EnableCache(XCACHE_Type *base)
{
    /* Return if XCACHE is already enabled */
    if ((base->CCR & XCACHE_CCR_ENCACHE_MASK) == 0x00U)
    {
        /* First, invalidate the entire cache. */
        XCACHE_InvalidateCache(base);

        /* Now enable the cache. */
        base->CCR |= XCACHE_CCR_ENCACHE_MASK;
    }
}

/*!
 * brief Disables the cache.
 *
 */
void XCACHE_DisableCache(XCACHE_Type *base)
{
    if (XCACHE_CCR_ENCACHE_MASK == (XCACHE_CCR_ENCACHE_MASK & base->CCR))
    {
        /* First, push any modified contents. */
        XCACHE_CleanCache(base);

        /* Now disable the cache. */
        base->CCR &= ~XCACHE_CCR_ENCACHE_MASK;
    }
}

/*!
 * brief Invalidates the cache.
 *
 */
void XCACHE_InvalidateCache(XCACHE_Type *base)
{
    /* Invalidate all lines in both ways and initiate the cache command. */
    base->CCR |= XCACHE_CCR_INVW0_MASK | XCACHE_CCR_INVW1_MASK | XCACHE_CCR_GO_MASK;

    /* Wait until the cache command completes. */
    while ((base->CCR & XCACHE_CCR_GO_MASK) != 0x00U)
    {
    }

    /* As a precaution clear the bits to avoid inadvertently re-running this command. */
    base->CCR &= ~(XCACHE_CCR_INVW0_MASK | XCACHE_CCR_INVW1_MASK);
}

/*!
 * brief Invalidates cache by range.
 *
 * param address The physical address of cache.
 * param size_byte size of the memory to be invalidated, should be larger than 0,
 * better to align to size of cache line.
 * note Address and size should be aligned to "L1CODCACHE_LINESIZE_BYTE".
 * The startAddr here will be forced to align to XCACHE_LINESIZE_BYTE if
 * startAddr is not aligned. For the size_byte, application should make sure the
 * alignment or make sure the right operation order if the size_byte is not aligned.
 */
void XCACHE_InvalidateCacheByRange(uint32_t address, uint32_t size_byte)
{
    if (size_byte > 0UL)
    {
        uint32_t endAddr = address + size_byte - 0x01U;
        uint32_t pccReg  = 0;
        /* Align address to cache line size. */
        uint32_t startAddr = address & ~((uint32_t)XCACHE_LINESIZE_BYTE - 1U);
        uint32_t instance  = XCACHE_GetInstanceByAddr(address);
        uint32_t endLim;
        XCACHE_Type *base;

        if (instance >= ARRAY_SIZE(s_xcachectrlBases))
        {
            return;
        }
        base    = s_xcachectrlBases[instance];
        endLim  = s_xcachePhymemBases[instance] + s_xcachePhymemSizes[instance] - 0x01U;
        endAddr = endAddr > endLim ? endLim : endAddr;

        /* Set the invalidate by line command and use the physical address. */
        pccReg     = (base->CLCR & ~XCACHE_CLCR_LCMD_MASK) | XCACHE_CLCR_LCMD(1) | XCACHE_CLCR_LADSEL_MASK;
        base->CLCR = pccReg;

        while (startAddr < endAddr)
        {
            /* Set the address and initiate the command. */
            base->CSAR = (startAddr & XCACHE_CSAR_PHYADDR_MASK) | XCACHE_CSAR_LGO_MASK;

            /* Wait until the cache command completes. */
            while ((base->CSAR & XCACHE_CSAR_LGO_MASK) != 0x00U)
            {
            }
            startAddr += (uint32_t)XCACHE_LINESIZE_BYTE;
        }
    }
}

/*!
 * brief Cleans the cache.
 *
 */
void XCACHE_CleanCache(XCACHE_Type *base)
{
    /* Enable the to push all modified lines. */
    base->CCR |= XCACHE_CCR_PUSHW0_MASK | XCACHE_CCR_PUSHW1_MASK | XCACHE_CCR_GO_MASK;

    /* Wait until the cache command completes. */
    while ((base->CCR & XCACHE_CCR_GO_MASK) != 0x00U)
    {
    }

    /* As a precaution clear the bits to avoid inadvertently re-running this command. */
    base->CCR &= ~(XCACHE_CCR_PUSHW0_MASK | XCACHE_CCR_PUSHW1_MASK);
}

/*!
 * brief Cleans cache by range.
 *
 * param address The physical address of cache.
 * param size_byte size of the memory to be cleaned, should be larger than 0,
 * better to align to size of cache line.
 * note Address and size should be aligned to "XCACHE_LINESIZE_BYTE".
 * The startAddr here will be forced to align to XCACHE_LINESIZE_BYTE if
 * startAddr is not aligned. For the size_byte, application should make sure the
 * alignment or make sure the right operation order if the size_byte is not aligned.
 */
void XCACHE_CleanCacheByRange(uint32_t address, uint32_t size_byte)
{
    if (size_byte > 0UL)
    {
        uint32_t endAddr = address + size_byte - 0x01U;
        uint32_t pccReg  = 0;
        /* Align address to cache line size. */
        uint32_t startAddr = address & ~((uint32_t)XCACHE_LINESIZE_BYTE - 1U);
        uint32_t instance  = XCACHE_GetInstanceByAddr(address);
        uint32_t endLim;
        XCACHE_Type *base;

        if (instance >= ARRAY_SIZE(s_xcachectrlBases))
        {
            return;
        }
        base    = s_xcachectrlBases[instance];
        endLim  = s_xcachePhymemBases[instance] + s_xcachePhymemSizes[instance] - 0x01U;
        endAddr = endAddr > endLim ? endLim : endAddr;

        /* Set the push by line command. */
        pccReg     = (base->CLCR & ~XCACHE_CLCR_LCMD_MASK) | XCACHE_CLCR_LCMD(2) | XCACHE_CLCR_LADSEL_MASK;
        base->CLCR = pccReg;

        while (startAddr < endAddr)
        {
            /* Set the address and initiate the command. */
            base->CSAR = (startAddr & XCACHE_CSAR_PHYADDR_MASK) | XCACHE_CSAR_LGO_MASK;

            /* Wait until the cache command completes. */
            while ((base->CSAR & XCACHE_CSAR_LGO_MASK) != 0x00U)
            {
            }
            startAddr += (uint32_t)XCACHE_LINESIZE_BYTE;
        }
    }
}

/*!
 * brief Cleans and invalidates the cache.
 *
 */
void XCACHE_CleanInvalidateCache(XCACHE_Type *base)
{
    /* Push and invalidate all. */
    base->CCR |= XCACHE_CCR_PUSHW0_MASK | XCACHE_CCR_PUSHW1_MASK | XCACHE_CCR_INVW0_MASK | XCACHE_CCR_INVW1_MASK |
                 XCACHE_CCR_GO_MASK;

    /* Wait until the cache command completes. */
    while ((base->CCR & XCACHE_CCR_GO_MASK) != 0x00U)
    {
    }

    /* As a precaution clear the bits to avoid inadvertently re-running this command. */
    base->CCR &= ~(XCACHE_CCR_PUSHW0_MASK | XCACHE_CCR_PUSHW1_MASK | XCACHE_CCR_INVW0_MASK | XCACHE_CCR_INVW1_MASK);
}

/*!
 * brief Cleans and invalidate cache by range.
 *
 * param address The physical address of cache.
 * param size_byte size of the memory to be Cleaned and Invalidated, should larger than 0,
 * better to align to size of cache line.
 * note Address and size should be aligned to "XCACHE_LINESIZE_BYTE".
 * The startAddr here will be forced to align to XCACHE_LINESIZE_BYTE if
 * startAddr is not aligned. For the size_byte, application should make sure the
 * alignment or make sure the right operation order if the size_byte is not aligned.
 */
void XCACHE_CleanInvalidateCacheByRange(uint32_t address, uint32_t size_byte)
{
    if (size_byte > 0UL)
    {
        uint32_t endAddr = address + size_byte - 0x01U;
        uint32_t pccReg  = 0;
        /* Align address to cache line size. */
        uint32_t startAddr = address & ~((uint32_t)XCACHE_LINESIZE_BYTE - 1U);
        uint32_t instance  = XCACHE_GetInstanceByAddr(address);
        uint32_t endLim;
        XCACHE_Type *base;

        if (instance >= ARRAY_SIZE(s_xcachectrlBases))
        {
            return;
        }
        base    = s_xcachectrlBases[instance];
        endLim  = s_xcachePhymemBases[instance] + s_xcachePhymemSizes[instance] - 0x01U;
        endAddr = endAddr > endLim ? endLim : endAddr;

        /* Set the push by line command. */
        pccReg     = (base->CLCR & ~XCACHE_CLCR_LCMD_MASK) | XCACHE_CLCR_LCMD(3) | XCACHE_CLCR_LADSEL_MASK;
        base->CLCR = pccReg;

        while (startAddr < endAddr)
        {
            /* Set the address and initiate the command. */
            base->CSAR = (startAddr & XCACHE_CSAR_PHYADDR_MASK) | XCACHE_CSAR_LGO_MASK;

            /* Wait until the cache command completes. */
            while ((base->CSAR & XCACHE_CSAR_LGO_MASK) != 0x00U)
            {
            }
            startAddr += (uint32_t)XCACHE_LINESIZE_BYTE;
        }
    }
}

#if !((defined(FSL_FEATURE_XCACHE_HAS_NO_WRITE_BUF)) && (FSL_FEATURE_XCACHE_HAS_NO_WRITE_BUF))
/*!
 * brief Enable the cache write buffer.
 *
 */
void XCACHE_EnableWriteBuffer(XCACHE_Type *base, bool enable)
{
    if (enable)
    {
        base->CCR |= XCACHE_CCR_ENWRBUF_MASK;
    }
    else
    {
        base->CCR &= ~XCACHE_CCR_ENWRBUF_MASK;
    }
}
#endif

#endif /* FSL_FEATURE_SOC_XCACHE_COUNT > 0 */
