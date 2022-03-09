/*
 * Copyright 2019-2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* Multicore packed image loader implementation */

#include <string.h>

#include "fsl_common.h"
#include "fsl_mpi_loader.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*****************************************************
 * TZM preset size definition for different devices. *
 *****************************************************/
#define MPI_TZM_PRESET_SIZE_RT5XX (1140U)
#define MPI_TZM_PRESET_SIZE_RT6XX (1052U)

#define MPI_ASSERT(x)    \
    do                   \
    {                    \
        if (!(x))        \
        {                \
            while (true) \
            {            \
            }            \
        }                \
    } while (false)

#if defined(MIMXRT595S_cm33_SERIES)
#define MPI_TZM_PRESET_SIZE MPI_TZM_PRESET_SIZE_RT5XX
#define MPI_ADDRESS_MASK    (0xEFFFFFFFU) /* Bit28 is secure address indicator */
#define MPI_MEMCPY          (void)memcpy
#define MPI_MEMCLR          (void)memset

#elif defined(MIMXRT685S_cm33_SERIES)
#define MPI_TZM_PRESET_SIZE MPI_TZM_PRESET_SIZE_RT6XX
#define MPI_ADDRESS_MASK    (0xEFFFFFFFU) /* Bit28 is secure address indicator */
#define MPI_MEMCPY          MPI_WordCopy
#define MPI_MEMCLR          MPI_WordSet

#else
#error "Device not supported by Multicore Packed Image Loader!"
#endif

/*********************************
 * Image type fields definition. *
 *********************************/
#define MPI_TYPE_IMAGE_BASE_SHIFT              (0U)
#define MPI_TYPE_IMAGE_BASE_MASK               (0xFFU << (MPI_TYPE_IMAGE_BASE_SHIFT))
#define MPI_TYPE_IMAGE_BASE_PLAIN_SIGNED       (1U << (MPI_TYPE_IMAGE_BASE_SHIFT))
#define MPI_TYPE_IMAGE_BASE_PLAIN_UNSIGNED     (2U << (MPI_TYPE_IMAGE_BASE_SHIFT))
#define MPI_TYPE_IMAGE_BASE_ENCRYPTED_SIGNED   (3U << (MPI_TYPE_IMAGE_BASE_SHIFT))
#define MPI_TYPE_IMAGE_BASE_XIP_PLAIN_SIGNED   (4U << (MPI_TYPE_IMAGE_BASE_SHIFT))
#define MPI_TYPE_IMAGE_BASE_XIP_PLAIN_UNSIGNED (5U << (MPI_TYPE_IMAGE_BASE_SHIFT))

#define MPI_TYPE_MULTICORE_PACKED_SHIFT (11U)
#define MPI_TYPE_MULTICORE_PACKED_MASK  (1UL << (MPI_TYPE_MULTICORE_PACKED_SHIFT))

#define MPI_TYPE_TZM_SHIFT (13U)
#define MPI_TYPE_TZM_MASK  (3UL << (MPI_TYPE_TZM_SHIFT))
/* Trustzone enabled secure image. */
#define MPI_TYPE_TZM_SECURE (0UL << MPI_TYPE_TZM_SHIFT)
/* Trustzone enabled secure image with preset values. */
#define MPI_TYPE_TZM_SECURE_PRESET (1UL << MPI_TYPE_TZM_SHIFT)
/* Trustzone disabled non-secure image entry. */
#define MPI_TYPE_TZM_NONSECURE (2UL << MPI_TYPE_TZM_SHIFT)

/********************************
 * Relocation table definition. *
 ********************************/
#define MPI_RELOC_MARKER           (0x4C54424CU)
#define MPI_RELOC_FLAG_LTI_LOAD    (1U << 0)
#define MPI_RELOC_FLAG_LTI_INIT    (1U << 1)
#define MPI_RELOC_FLAG_LTI_OVERLAP (1U << 2)

typedef struct
{
    uint32_t srcAddr;
    uint32_t destAddr;
    uint32_t segmentSize;
    uint32_t flags;
} mpi_reloc_entry_t;

typedef struct
{
    uint32_t marker; /* always set to 0x4C54424C */
    uint32_t version;
    uint32_t numberOfEntries;
    uint32_t entriesOff;
} mpi_reloc_table_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
#if defined(MIMXRT685S_cm33_SERIES)
static void MPI_WordCopy(void *dest, void *src, uint32_t size)
{
    uint32_t *s, *d;

    MPI_ASSERT(src != NULL && (((uint32_t)(uint32_t *)src & 3U) == 0U));
    MPI_ASSERT(dest != NULL && (((uint32_t)(uint32_t *)dest & 3U) == 0U));
    MPI_ASSERT((size & 3U) == 0U);

    s = (uint32_t *)src;
    d = (uint32_t *)dest;

    while (size > 0U)
    {
        *d++ = *s++;
        size -= 4U;
    }
}

static void MPI_WordSet(void *ptr, uint32_t value, uint32_t size)
{
    uint32_t *p;

    MPI_ASSERT(ptr != NULL && (((uint32_t)(uint32_t *)ptr & 3U) == 0U));
    MPI_ASSERT((size & 3U) == 0U);

    p = (uint32_t *)ptr;

    while (size > 0U)
    {
        *p++ = value;
        size -= 4U;
    }
}
#endif

static void MPI_Relocate(uint32_t *vect, mpi_reloc_entry_t *entry)
{
    uint32_t srcAddr;

    MPI_ASSERT(entry != NULL);

    srcAddr = ((uint32_t)vect) + entry->srcAddr;

    switch (entry->flags)
    {
        case MPI_RELOC_FLAG_LTI_LOAD:
            if ((srcAddr & MPI_ADDRESS_MASK) != (entry->destAddr & MPI_ADDRESS_MASK))
            {
                MPI_MEMCPY((void *)(uint32_t *)entry->destAddr, (void *)(uint32_t *)srcAddr, entry->segmentSize);
            }
            break;
        case MPI_RELOC_FLAG_LTI_INIT:
            MPI_MEMCLR((void *)(uint32_t *)entry->destAddr, 0, entry->segmentSize);
            break;
        case MPI_RELOC_FLAG_LTI_OVERLAP:
            /* Do nothing */
        default:
            /* Do nothing */
            break;
    }
}

static void MPI_HandleRelocTable(uint32_t *vect)
{
    uint32_t i;
    uint32_t imageLen;
    uint32_t imageType;
    uint32_t imageBase;
    uint32_t relocTabEnd;
    mpi_reloc_table_t *pRelocTab;
    mpi_reloc_entry_t *pRelocEntry;

    MPI_ASSERT(vect != NULL);

    imageLen  = vect[8];
    imageType = vect[9];

    if ((imageType & MPI_TYPE_MULTICORE_PACKED_MASK) != 0U)
    {
        /* Need to load other images. */
        imageBase = imageType & MPI_TYPE_IMAGE_BASE_MASK;
        if (imageBase == MPI_TYPE_IMAGE_BASE_PLAIN_SIGNED || imageBase == MPI_TYPE_IMAGE_BASE_ENCRYPTED_SIGNED ||
            imageBase == MPI_TYPE_IMAGE_BASE_XIP_PLAIN_SIGNED)
        {
            /* Offset 0x28 is certificate header offset. */
            relocTabEnd = vect[10];
        }
        else
        {
            /* Offset 0x28 is CRC. */
            relocTabEnd = imageLen;
            if ((imageType & MPI_TYPE_TZM_MASK) == MPI_TYPE_TZM_SECURE_PRESET)
            {
                /* Has TZM preset data, need to minus the size for relocation table pointer. */
                relocTabEnd -= MPI_TZM_PRESET_SIZE;
            }
        }
        pRelocTab = (mpi_reloc_table_t *)(((uint32_t)vect) + relocTabEnd) - 1;
        MPI_ASSERT(pRelocTab->marker == MPI_RELOC_MARKER);

        pRelocEntry = (mpi_reloc_entry_t *)(((uint32_t)vect) + pRelocTab->entriesOff);
        for (i = 0; i < pRelocTab->numberOfEntries; i++)
        {
            MPI_Relocate(vect, pRelocEntry + i);
        }
    }
}

/* Must finish loading before application .data, .bss get initialized. */
void MPI_LoadMultiImages(void)
{
    extern uint32_t __VECTOR_TABLE[];

    MPI_HandleRelocTable(__VECTOR_TABLE);
}
