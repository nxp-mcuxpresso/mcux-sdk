/*
 * Copyright 2018 NXP
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
/*! @brief IMEMORY driver version 2.0.0. */
#define FSL_MEMORY_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

/* The CM7 subsystem local ITCM start address, refer to Reference Manual for detailed information */
#define FSL_MEM_M7_ITCM_BEGIN 0x00000000U
/* The CM7 subsystem local ITCM end address, refer to Reference Manual for detailed information */
#define FSL_MEM_M7_ITCM_END 0x0001FFFFU

/* The CM7 subsystem local DTCM start address, refer to Reference Manual for detailed information */
#define FSL_MEM_M7_DTCM_BEGIN 0x20000000U
/* The CM7 subsystem local DTCM end address, refer to Reference Manual for detailed information */
#define FSL_MEM_M7_DTCM_END 0x2001FFFFU

/* The CM7 subsystem local OCRAM start address, refer to Reference Manual for detailed information */
#define FSL_MEM_M7_OCRAM_BEGIN 0x20200000U
/* The CM7 subsystem local OCRAM end address, refer to Reference Manual for detailed information */
#define FSL_MEM_M7_OCRAM_END 0x2021FFFFU

/* The CM7 subsystem local OCRAMS start address, refer to Reference Manual for detailed information */
#define FSL_MEM_M7_OCRAMS_BEGIN 0x20180000U
/* The CM7 subsystem local OCRAMS end address, refer to Reference Manual for detailed information */
#define FSL_MEM_M7_OCRAMS_END 0x20187FFFU

/* System level ITCM memory address = CM7 subsystem local ITCM address + FSL_FEATURE_ITCM_OFFSET */
#define FSL_MEM_M7_ITCM_OFFSET (0x7E0000U)
/* System level DTCM memory address = CM7 subsystem local DTCM address - FSL_FEATURE_DTCM_OFFSET */
#define FSL_MEM_M7_DTCM_OFFSET 0x1F800000U
/* System level OCRAM memory address = CM7 subsystem local OCRAM address - FSL_MEM_M7_OCRAM_OFFSET */
#define FSL_MEM_M7_OCRAM_OFFSET 0x1F900000U
/* System level OCRAMS memory address = CM7 subsystem local OCRAMS address - FSL_MEM_M7_OCRAMS_OFFSET */
#define FSL_MEM_M7_OCRAMS_OFFSET 0x20000000U

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
static inline uint32_t MEMORY_ConvertMemoryMapAddress(uint32_t addr, mem_direction_t direction)
{
    uint32_t dest;

    switch (direction)
    {
        case kMEMORY_Local2DMA:
        {
            if ((addr <= FSL_MEM_M7_ITCM_END))
            {
                dest = addr + FSL_MEM_M7_ITCM_OFFSET;
            }
            else if ((addr >= FSL_MEM_M7_DTCM_BEGIN) && (addr <= FSL_MEM_M7_DTCM_END))
            {
                dest = addr - FSL_MEM_M7_DTCM_OFFSET;
            }
            else if ((addr >= FSL_MEM_M7_OCRAM_BEGIN) && (addr <= FSL_MEM_M7_OCRAM_END))
            {
                dest = addr - FSL_MEM_M7_OCRAM_OFFSET;
            }
            else if ((addr >= FSL_MEM_M7_OCRAMS_BEGIN) && (addr <= FSL_MEM_M7_OCRAMS_END))
            {
                dest = addr - FSL_MEM_M7_OCRAMS_OFFSET;
            }
            else
            {
                dest = addr;
            }
            break;
        }
        case kMEMORY_DMA2Local:
        {
            if ((addr >= (FSL_MEM_M7_ITCM_BEGIN + FSL_MEM_M7_ITCM_OFFSET)) &&
                (addr <= (FSL_MEM_M7_ITCM_END + FSL_MEM_M7_ITCM_OFFSET)))
            {
                dest = addr - FSL_MEM_M7_ITCM_OFFSET;
            }
            else if ((addr >= (FSL_MEM_M7_DTCM_BEGIN - FSL_MEM_M7_DTCM_OFFSET)) &&
                     (addr <= (FSL_MEM_M7_DTCM_END - FSL_MEM_M7_DTCM_OFFSET)))
            {
                dest = addr + FSL_MEM_M7_DTCM_OFFSET;
            }
            else if ((addr >= (FSL_MEM_M7_OCRAM_BEGIN - FSL_MEM_M7_OCRAM_OFFSET)) &&
                     (addr <= (FSL_MEM_M7_OCRAM_END - FSL_MEM_M7_OCRAM_OFFSET)))
            {
                dest = addr + FSL_MEM_M7_OCRAM_OFFSET;
            }
            else if ((addr >= (FSL_MEM_M7_OCRAMS_BEGIN - FSL_MEM_M7_OCRAMS_OFFSET)) &&
                     (addr <= (FSL_MEM_M7_OCRAMS_END - FSL_MEM_M7_OCRAMS_OFFSET)))
            {
                dest = addr + FSL_MEM_M7_OCRAMS_OFFSET;
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
