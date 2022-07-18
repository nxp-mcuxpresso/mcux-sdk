/*
 * Copyright 2018-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_MEMORY_H_
#define _FSL_MEMORY_H_

#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.memory"
#endif

/*! @name Driver version */
/*@{*/
/*! @brief MEMORY driver version 2.0.1. */
#define FSL_MEMORY_DRIVER_VERSION (MAKE_VERSION(2, 0, 1))
/*@}*/

/* The CM4 subsystem local TCM start address, refer to Reference Manual for detailed information */
#define FSL_MEM_M4_TCM_BEGIN 0x1FFE0000U
/* The CM4 subsystem local TCM end address, refer to Reference Manual for detailed information */
#define FSL_MEM_M4_TCM_END 0x2001FFFFU

/* The CM4 subsystem local OCRAM start address, refer to Reference Manual for detailed information */
#define FSL_MEM_M4_OCRAM_BEGIN 0x20200000U
/* The CM4 subsystem local OCRAM end address, refer to Reference Manual for detailed information */
#define FSL_MEM_M4_OCRAM_END 0x2021FFFFU

/* The CM4 subsystem local OCRAMS start address, refer to Reference Manual for detailed information */
#define FSL_MEM_M4_OCRAMS_BEGIN 0x20180000U
/* The CM4 subsystem local OCRAMS end address, refer to Reference Manual for detailed information */
#define FSL_MEM_M4_OCRAMS_END 0x20187FFFU

/* System level TCM memory address = CM4 subsystem local TCM address - FSL_FEATURE_TCM_OFFSET */
#define FSL_MEM_M4_TCM_OFFSET 0x1F800000U
/* System level OCRAM memory address = CM4 subsystem local OCRAM address - FSL_MEM_M4_OCRAM_OFFSET */
#define FSL_MEM_M4_OCRAM_OFFSET 0x1F900000U
/* System level OCRAMS memory address = CM4 subsystem local OCRAMS address - FSL_MEM_M4_OCRAMS_OFFSET */
#define FSL_MEM_M4_OCRAMS_OFFSET 0x20000000U

typedef enum _mem_direction
{
    kMEMORY_Local2DMA = 0,
    kMEMORY_DMA2Local,
} mem_direction_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif
/*!
 * @brief Convert the memory map address.
 *
 * This function convert the address between system mapped address and native mapped address.
 * There maybe offset between subsystem native address and system address for some memory,
 * this funciton convert the address to different memory map.
 * @param addr address need to be converted.
 * @param direction convert direction.
 * @return the converted address
 */
static inline uintptr_t MEMORY_ConvertMemoryMapAddress(uintptr_t addr, mem_direction_t direction)
{
    uintptr_t dest;

    switch (direction)
    {
        case kMEMORY_Local2DMA:
        {
            if ((addr >= FSL_MEM_M4_TCM_BEGIN) && (addr <= FSL_MEM_M4_TCM_END))
            {
                dest = addr - FSL_MEM_M4_TCM_OFFSET;
            }
            else if ((addr >= FSL_MEM_M4_OCRAM_BEGIN) && (addr <= FSL_MEM_M4_OCRAM_END))
            {
                dest = addr - FSL_MEM_M4_OCRAM_OFFSET;
            }
            else if ((addr >= FSL_MEM_M4_OCRAMS_BEGIN) && (addr <= FSL_MEM_M4_OCRAMS_END))
            {
                dest = addr - FSL_MEM_M4_OCRAMS_OFFSET;
            }
            else
            {
                dest = addr;
            }
            break;
        }
        case kMEMORY_DMA2Local:
        {
            if ((addr >= (FSL_MEM_M4_TCM_BEGIN - FSL_MEM_M4_TCM_OFFSET)) &&
                (addr <= (FSL_MEM_M4_TCM_END - FSL_MEM_M4_TCM_OFFSET)))
            {
                dest = addr + FSL_MEM_M4_TCM_OFFSET;
            }
            else if ((addr >= (FSL_MEM_M4_OCRAM_BEGIN - FSL_MEM_M4_OCRAM_OFFSET)) &&
                     (addr <= (FSL_MEM_M4_OCRAM_END - FSL_MEM_M4_OCRAM_OFFSET)))
            {
                dest = addr + FSL_MEM_M4_OCRAM_OFFSET;
            }
            else if ((addr >= (FSL_MEM_M4_OCRAMS_BEGIN - FSL_MEM_M4_OCRAMS_OFFSET)) &&
                     (addr <= (FSL_MEM_M4_OCRAMS_END - FSL_MEM_M4_OCRAMS_OFFSET)))
            {
                dest = addr + FSL_MEM_M4_OCRAMS_OFFSET;
            }
            else
            {
                dest = addr;
            }
            break;
        }
        default:
            dest = addr;
            break;
    }

    return dest;
}
#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* _FSL_MEMORY_H_ */
