/*
 * Copyright 2021-2023 NXP
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

#define FSL_MEM_M33_SECURE_ADDRESS_OFFSET 0x10000000U
#define ADDRESS_NOT_AVAILABLE 0xFFFFFFFFU

typedef enum _mem_direction
{
    kMEMORY_Local2DMA = 0,
    kMEMORY_DMA2Local,
} mem_direction_t;

typedef enum _addr_type
{
    kCore_CM7_ITCM_START = 0,
    kCore_CM7_ITCM_START_ALIAS,
    kCore_CM7_ITCM_END,
    kCore_CM7_ITCM_END_ALIAS,
    kCore_CM7_DTCM_START,
    kCore_CM7_DTCM_START_ALIAS,
    kCore_CM7_DTCM_END,
    kCore_CM7_DTCM_END_ALIAS,
    kCore_CM33_CTCM_START,
    kCore_CM33_CTCM_START_ALIAS,
    kCore_CM33_CTCM_END,
    kCore_CM33_CTCM_END_ALIAS,
    kCore_CM33_STCM_START,
    kCore_CM33_STCM_START_ALIAS,
    kCore_CM33_STCM_END,
    kCore_CM33_STCM_END_ALIAS
} addr_type_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif
/*!
 * @brief Get Memory Boundary Address
 *
 * This function translate CM33/CM7 TCM address between Core View and ALIAS System View
 * CM33 and CM7 TCM Address are determined by M33_CFG[TCM_SIZE] and M7_CFG[TCM_SIZE]
 * 
 * | M7[TCM_SIZE] | ITCM START/ALIAS        | ITCM END/ALIAS          | DTCM START/ALIAS        | DTCM END/ALIAS          | Size    |
 * |--------------|-------------------------|-------------------------|-------------------------|-------------------------|---------|
 * | 000          | 0x0000_0000/0x203C_0000 | 0x0004_0000/0x2040_0000 | 0x2000_0000/0x2040_0000 | 0x2004_0000/0x2044_0000 | 256/256 |
 * | 001          | 0x0000_0000/0x2038_0000 | 0x0008_0000/0x2040_0000 | NA                      | NA                      | 512/0   |
 * | 010          | NA                      | NA                      | 0x2000_0000/0x2040_0000 | 0x2008_0000/0x2048_0000 | 0/512   |
 * | 100          | 0x0000_0000/0x203E_0000 | 0x0002_0000/0x2040_0000 | 0x2000_0000/0x2040_0000 | 0x2006_0000/0x2046_0000 | 128/384 |
 * | 101          | 0x0000_0000/0x203A_0000 | 0x0006_0000/0x2040_0000 | 0x2000_0000/0x2040_0000 | 0x2002_0000/0x2042_0000 | 384/128 |
 *
 * | M33[TCM_SIZE] | CTCM START/ALIAS        | CTCM END/ALIAS          | STCM START/ALIAS        | STCM END/ALIAS          | Size    |
 * |---------------|-------------------------|-------------------------|-------------------------|-------------------------|---------|
 * | 00            | 0x0FFE_0000/0x201E_0000 | 0x1000_0000/0x2020_0000 | 0x2000_0000/0x2020_0000 | 0x2002_0000/0x2022_0000 | 128/128 |
 * | 01            | 0x0FFC_0000/0x201C_0000 | 0x1000_0000/0x2020_0000 | NA                      | NA                      | 256/0   |
 * | 10            | NA                      | NA                      | 0x2000_0000/0x2020_0000 | 0x2004_0000/0x2024_0000 | 0/256   |
 * @param type address boundary to be retrieved.
 */

static inline uint32_t get_memory_address(addr_type_t type)
{
    uint32_t m7_ctcm_size_cfg = (BLK_CTRL_S_AONMIX->M7_CFG & BLK_CTRL_S_AONMIX_M7_CFG_TCM_SIZE_MASK) >> BLK_CTRL_S_AONMIX_M7_CFG_TCM_SIZE_SHIFT;
    uint32_t m33_ctcm_size_cfg = (BLK_CTRL_S_AONMIX->M33_CFG & BLK_CTRL_S_AONMIX_M33_CFG_TCM_SIZE_MASK) >> BLK_CTRL_S_AONMIX_M33_CFG_TCM_SIZE_SHIFT;
    uint32_t transAddr = ADDRESS_NOT_AVAILABLE;
    switch (type)
    {
        case kCore_CM7_ITCM_START:
            switch (m7_ctcm_size_cfg)
            {
                case 0U:
                case 1U:
                case 4U:
                case 5U:
                    transAddr = 0x0U;
                    break;
                default:
                    transAddr = ADDRESS_NOT_AVAILABLE;
                    break;
            }
            break;
        case kCore_CM7_ITCM_START_ALIAS:
            switch (m7_ctcm_size_cfg)
            {
                case 0U:
                    transAddr = 0x203C0000U;
                    break;
                case 1U:
                    transAddr = 0x20380000U;
                    break;
                case 4U:
                    transAddr = 0x203E0000U;
                    break;
                case 5U:
                    transAddr = 0x203A0000U;
                    break;
                default:
                    transAddr = ADDRESS_NOT_AVAILABLE;
                    break;
            }
            break;
        case kCore_CM7_ITCM_END:
            switch (m7_ctcm_size_cfg)
            {
                case 0U:
                    transAddr = 0x3FFFFU;
                    break;
                case 1U:
                    transAddr = 0x7FFFFU;
                    break;
                case 4U:
                    transAddr = 0x1FFFFU;
                    break;
                case 5U:
                    transAddr = 0x5FFFFU;
                    break;
                default:
                    transAddr = ADDRESS_NOT_AVAILABLE;
                    break;
            }
            break;
        case kCore_CM7_ITCM_END_ALIAS:
            switch (m7_ctcm_size_cfg)
            {
                case 0U:
                case 1U:
                case 4U:
                case 5U:
                    transAddr = 0x203FFFFFU;
                    break;
                default:
                    transAddr = ADDRESS_NOT_AVAILABLE;
                    break;
            }
            break;
        case kCore_CM7_DTCM_START:
            switch (m7_ctcm_size_cfg)
            {
                case 0U:
                case 2U:
                case 4U:
                case 5U:
                    transAddr = 0x20000000U;
                    break;
                default:
                    transAddr = ADDRESS_NOT_AVAILABLE;
                    break;
            }
            break;
        case kCore_CM7_DTCM_START_ALIAS:
            switch (m7_ctcm_size_cfg)
            {
                case 0U:
                case 2U:
                case 4U:
                case 5U:
                    transAddr = 0x20400000U;
                    break;
                default:
                    transAddr = ADDRESS_NOT_AVAILABLE;
                    break;
            }
            break;
        case kCore_CM7_DTCM_END:
            switch (m7_ctcm_size_cfg)
            {
                case 0U:
                    transAddr = 0x2003FFFFU;
                    break;
                case 2U:
                    transAddr = 0x2007FFFFU;
                    break;
                case 4U:
                    transAddr = 0x2005FFFFU;
                    break;
                case 5U:
                    transAddr = 0x2001FFFFU;
                    break;
                default:
                    transAddr = ADDRESS_NOT_AVAILABLE;
                    break;
            }
            break;
        case kCore_CM7_DTCM_END_ALIAS:
            switch (m7_ctcm_size_cfg)
            {
                case 0U:
                    transAddr = 0x2043FFFFU;
                    break;
                case 2U:
                    transAddr = 0x2047FFFFU;
                    break;
                case 4U:
                    transAddr = 0x2045FFFFU;
                    break;
                case 5U:
                    transAddr = 0x2041FFFFU;
                    break;
                default:
                    transAddr = ADDRESS_NOT_AVAILABLE;
                    break;
            }
            break;
        case kCore_CM33_CTCM_START:
            switch (m33_ctcm_size_cfg)
            {
                case 0U:
                    transAddr = 0xFFE0000U;
                    break;
                case 1U:
                    transAddr = 0xFFC0000U;
                    break;
                default:
                    transAddr = ADDRESS_NOT_AVAILABLE;
                    break;
            }
            break;
        case kCore_CM33_CTCM_START_ALIAS:
            switch (m33_ctcm_size_cfg)
            {
                case 0U:
                    transAddr = 0x201E0000U;
                    break;
                case 1U:
                    transAddr = 0x201C0000U;
                    break;
                default:
                    transAddr = ADDRESS_NOT_AVAILABLE;
                    break;
            }
            break;
        case kCore_CM33_CTCM_END:
            switch (m33_ctcm_size_cfg)
            {
                case 0U:
                case 1U:
                    transAddr = 0xFFFFFFFU;
                    break;
                default:
                    transAddr = ADDRESS_NOT_AVAILABLE;
                    break;
            }
            break;
        case kCore_CM33_CTCM_END_ALIAS:
            switch (m33_ctcm_size_cfg)
            {
                case 0U:
                case 1U:
                    transAddr = 0x201FFFFFU;
                    break;
                default:
                    transAddr = ADDRESS_NOT_AVAILABLE;
                    break;
            }
            break;
        case kCore_CM33_STCM_START:
            switch (m33_ctcm_size_cfg)
            {
                case 0U:
                case 2U:
                    transAddr = 0x20000000U;
                    break;
                default:
                    transAddr = ADDRESS_NOT_AVAILABLE;
                    break;
            }
            break;
        case kCore_CM33_STCM_START_ALIAS:
            switch (m33_ctcm_size_cfg)
            {
                case 0U:
                case 2U:
                    transAddr = 0x20200000U;
                    break;
                default:
                    transAddr = ADDRESS_NOT_AVAILABLE;
                    break;
            }
            break;
        case kCore_CM33_STCM_END:
            switch (m33_ctcm_size_cfg)
            {
                case 0U:
                    transAddr = 0x2001FFFFU;
                    break;
                case 2U:
                    transAddr = 0x2003FFFFU;
                    break;
                default:
                    transAddr = ADDRESS_NOT_AVAILABLE;
                    break;
            }
            break;
        case kCore_CM33_STCM_END_ALIAS:
            switch (m33_ctcm_size_cfg)
            {
                case 0U:
                    transAddr = 0x2021FFFF;
                    break;
                case 2U:
                    transAddr = 0x2023FFFF;
                    break;
                default:
                    transAddr = ADDRESS_NOT_AVAILABLE;
                    break;
            }
            break;
        default:
            transAddr = ADDRESS_NOT_AVAILABLE;
            break;
    }
    return transAddr;
}

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
#if (__CORTEX_M == 33U)
    uint32_t m33_code_tcm_offset = get_memory_address(kCore_CM33_CTCM_START_ALIAS) - get_memory_address(kCore_CM33_CTCM_START);
    uint32_t m33_stcm_offset = get_memory_address(kCore_CM33_STCM_START_ALIAS) - get_memory_address(kCore_CM33_STCM_START);
#elif (__CORTEX_M == 7U)
    uint32_t m7_itcm_offset = get_memory_address(kCore_CM7_ITCM_START_ALIAS) - get_memory_address(kCore_CM7_ITCM_START);
    uint32_t m7_dtcm_offset = get_memory_address(kCore_CM7_DTCM_START_ALIAS) - get_memory_address(kCore_CM7_DTCM_START);
#endif

    switch (direction)
    {
        case kMEMORY_Local2DMA:
        {
#if (__CORTEX_M == 33U)
            if (((addr >= get_memory_address(kCore_CM33_CTCM_START)) && (addr <= get_memory_address(kCore_CM33_CTCM_END))) ||
                    ((addr >= (get_memory_address(kCore_CM33_CTCM_START) + FSL_MEM_M33_SECURE_ADDRESS_OFFSET)) &&
                     (addr <= (get_memory_address(kCore_CM33_CTCM_END) + FSL_MEM_M33_SECURE_ADDRESS_OFFSET))))
            {
                dest = addr + m33_code_tcm_offset;
            }
            else if (((addr >= get_memory_address(kCore_CM33_STCM_START)) && (addr <= get_memory_address(kCore_CM33_STCM_END))) ||
                    ((addr >= (get_memory_address(kCore_CM33_STCM_START) + FSL_MEM_M33_SECURE_ADDRESS_OFFSET)) &&
                     (addr <= (get_memory_address(kCore_CM33_STCM_END) + FSL_MEM_M33_SECURE_ADDRESS_OFFSET))))
            {
                dest = addr + m33_stcm_offset;
            }
#elif (__CORTEX_M == 7U)
            /*
             * For CM7, ITCM has valid memory 0, but for EDMA, 0 is also pointer NULL, which has specific
             * meaning. Considering we never use ITCM 0 as EDMA buffer, address translation for 0 is ignored
             */
            if ((addr > 0U) && (addr <= get_memory_address(kCore_CM7_ITCM_END)))
            {
                dest = addr + m7_itcm_offset;
            }
            else if ((addr >= get_memory_address(kCore_CM7_DTCM_START)) && (addr <= get_memory_address(kCore_CM7_DTCM_END)))
            {
                dest = addr + m7_dtcm_offset;
            }
#endif
            else
            {
                dest = addr;
            }
            break;
        }
        case kMEMORY_DMA2Local:
        {
#if (__CORTEX_M == 33U)
            if (((addr >= get_memory_address(kCore_CM33_CTCM_START_ALIAS)) && (addr <= get_memory_address(kCore_CM33_CTCM_END_ALIAS))) ||
                    ((addr >= (get_memory_address(kCore_CM33_CTCM_START_ALIAS) + FSL_MEM_M33_SECURE_ADDRESS_OFFSET)) &&
                     (addr <= (get_memory_address(kCore_CM33_CTCM_END_ALIAS) + FSL_MEM_M33_SECURE_ADDRESS_OFFSET))))
            {
                dest = addr - m33_code_tcm_offset;
            }
            else if (((addr >= get_memory_address(kCore_CM33_STCM_START_ALIAS)) && (addr <= get_memory_address(kCore_CM33_STCM_END_ALIAS))) ||
                    ((addr >= (get_memory_address(kCore_CM33_STCM_START_ALIAS) + FSL_MEM_M33_SECURE_ADDRESS_OFFSET)) &&
                     (addr <= (get_memory_address(kCore_CM33_STCM_END_ALIAS) + FSL_MEM_M33_SECURE_ADDRESS_OFFSET))))
            {
                dest = addr - m33_stcm_offset;
            }
#elif (__CORTEX_M == 7U)
            if ((addr >= get_memory_address(kCore_CM7_ITCM_START_ALIAS)) && (addr <= get_memory_address(kCore_CM7_ITCM_END_ALIAS)))
            {
                dest = addr - m7_itcm_offset;
            }
            else if ((addr >= get_memory_address(kCore_CM7_DTCM_START_ALIAS)) && (addr <= get_memory_address(kCore_CM7_DTCM_END_ALIAS)))
            {
                dest = addr - m7_dtcm_offset;
            }
#endif
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
