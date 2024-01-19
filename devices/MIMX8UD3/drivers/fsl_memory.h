/*
 * Copyright 2021 NXP
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
/*! @brief MEMORY driver version 2.0.0. */
#define FSL_MEMORY_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

#if (defined(MIMX8UD7_dsp0_SERIES) || defined(MIMX8UD5_dsp0_SERIES) || defined(MIMX8UD3_dsp0_SERIES) || \
     defined(MIMX8US5_dsp0_SERIES) || defined(MIMX8US3_dsp0_SERIES))
/* The DSP subsystem dRAM start address, refer to Reference Manual for detailed information */
#define FSL_MEM_DSP_TCM_BEGIN 0x00800000U
/* The DSP subsystem dRAM end address, refer to Reference Manual for detailed information */
#define FSL_MEM_DSP_TCM_END 0x008BFFFFU

/* The SSRAM P0-P6 start address for RTD CM33 */
#define FSL_MEM_M33_SSRAM06_BEGIN 0x20000000U
/* The SSRAM P7 start address for RTD CM33 */
#define FSL_MEM_M33_SSRAM7_BEGIN 0x0FFC0000U
/* The SSRAM end address for RTD CM33 */
#define FSL_MEM_M33_SSRAM06_END 0x2007FFFFU
#define FSL_MEM_M33_SSRAM7_END  0x0FFFFFFFU

/* This offset allows the DSP SSRAM to be mapped to the M33 system address space, M33 address = DSP address + offset */
#define FSL_MEM_DSP_OFFSET(x) ((x >= 0x00880000U) ? 0x0F740000U : 0x1F800000U)
/* This offset allows the DSP SSRAM to be mapped to the DSP system address space, DSP address = M33 address - offset */
#define FSL_MEM_M33_OFFSET(x) ((x < 0x20000000U) ? 0x0F740000U : 0x1F800000U)
#else
#error "Device is not supported by this driver!"
#endif

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
            if ((addr >= FSL_MEM_DSP_TCM_BEGIN) && (addr <= FSL_MEM_DSP_TCM_END))
            {
                dest = addr + FSL_MEM_DSP_OFFSET(addr);
            }
            else
            {
                dest = addr;
            }
            break;
        }
        case kMEMORY_DMA2Local:
        {
            addr &= 0xEFFFFFFF; /* Convert to non-secure address. */
            if (((addr >= FSL_MEM_M33_SSRAM06_BEGIN) && (addr <= FSL_MEM_M33_SSRAM06_END)) ||
                ((addr >= FSL_MEM_M33_SSRAM7_BEGIN) && (addr <= FSL_MEM_M33_SSRAM7_END)))
            {
                dest = addr - FSL_MEM_M33_OFFSET(addr);
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
