/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef RISCV_XZBF_H_
#define RISCV_XZBF_H_

#include "riscv_types.h"


/*!
 * @ingroup RISCV_CoreCustomExt
 * @defgroup RISCV_CoreCustomExtXzbf Bit Field Extension (Xzbf)
 * @details Bit Field Extension 0.1 supported.
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Extract the specified bit field of the source data, then return
 *        the unsigned extension result
 *
   @verbatim
   result = zext(src[min(bfw+bfe,31):bfe])
   @endverbatim
 *
 * @param src Containing bit field to extract
 * @param bfw Bit field width minus one, must be immediate, range from 31 to 0
 * @param bfe Bit field end location, must be immediate, range from 31 to 0
 *
 * @return The extracted and unsigned extended result
 */
#define XZBF_Bfextiu(src, bfw, bfe)                                     \
({                                                                      \
    uint_xlen_t __rs1 = (uint_xlen_t)(src);                             \
    uint_xlen_t __dst;                                                  \
    asm volatile ("bfextiu %0, %1, " __ASM_STR(bfw) ", " __ASM_STR(bfe) \
            : "=r"(__dst) : "r"(__rs1)                                  \
            : "memory" );                                               \
    __dst;                                                              \
})

/*!
 * @brief Extract the specified bit field of the source data, then return
 *        the signed extension result
 *
   @verbatim
   result = sext(src[min(bfw+bfe,31):bfe])
   @endverbatim
 *
 * @param src Containing bit field to extract
 * @param bfw Bit field widht minus one, must be immediate, range from 31 to 0
 * @param bfe Bit field end location, must be immediate, range from 31 to 0
 *
 * @return The extracted and signed extended result
 */
#define XZBF_Bfexti(src, bfw, bfe)                         \
({                                                         \
    uint_xlen_t __rs1 = (uint_xlen_t)(src);                \
    int_xlen_t __dst;                                      \
    asm volatile ("bfexti %0, %1, " __ASM_STR(bfw) ", " __ASM_STR(bfe)         \
            : "=r"(__dst) : "r"(__rs1)                     \
            : "memory" );                                  \
    __dst;                                                 \
})

/*!
 * @brief Extract the specified bit field of the source data, then return
 *        the unsigned extension result
 *
   @verbatim
   result = zext(src[min(bfwBfe[9:5]+bfwBfe[4:0],31):bfwBfe[4:0]])
   @endverbatim
 *
 * @param src containing bit field to extract
 * @param bfwBfe bfwBfe[9:5] is bit field width minus one, bfwBfe[4:0] is bit field end location
 *
 * @return The extracted and unsigned extended result
 */
static inline uint32_t XZBF_Bfextu(uint32_t src, uint32_t bfwBfe)
{
   uint32_t dst;
   asm volatile ("bfextu %0, %1, %2"
            : "=r"(dst) : "r"(src), "r"(bfwBfe)
            : "memory" );
   return dst;
}

/*!
 * @brief Extract the specified bit field of the source data, then return
 *        the signed extension result
 *
   @verbatim
   result = sext(src[min(bfwBfe[9:5]+bfwBfe[4:0],31):bfwBfe[4:0]])
   @endverbatim
 *
 * @param src Containing bit field to extract
 * @param bfwBfe bfwBfe[9:5] is bit field width minus one, bfwBfe[4:0] is bit field end location
 *
 * @return The extracted and signed extended result
 */
#define XZBF_Bfext(src, bfwBfe)                            \
({                                                         \
    uint_xlen_t __rs1 = (uint_xlen_t)(src);                \
    uint_xlen_t __rs2 = (uint_xlen_t)(bfwBfe);             \
    int_xlen_t __dst;                                      \
    asm volatile ("bfext %0, %1, %2"                       \
            : "=r"(__dst) : "r"(__rs1), "r"(__rs2)         \
            : "memory" );                                  \
    __dst;                                                 \
})

/*!
 * @brief Bit field insert immediate, extract from src, then insert into dst
 *
   @verbatim
   shifted_src[31:0] = src << bfe
   mask[31:0] = ~(32'hffff_ffff << (bfw+1)) << bfe
   dst[31:0] = shifted_src[31:0] & mask[31:0] | rd[31:0] & ~mask[31:0]
   @endverbatim
 *
 * @param dst Destination to be inserted
 * @param src Containing bit field to extract
 * @param bfw Bit field width minus one, must be immediate, range from 31 to 0
 * @param bfe Bit field end location, must be immediate, range from 31 to 0
 *
 * @return The inserted result
 */
#define XZBF_Bfinsi(dst, src, bfw, bfe)                   \
({                                                        \
    uint_xlen_t __rs1 = (uint_xlen_t)(src);               \
    uint_xlen_t __dst = (uint_xlen_t)(dst);               \
    asm volatile ("bfinsi %0, %1, " __ASM_STR(bfw) ", " __ASM_STR(bfe)        \
            ::"r"(__dst), "r"(__rs1)                      \
            : "memory" );                                 \
    __dst;                                                \
})

/*!
 * @brief To extract specified bit field of src, then insert into dst
 *
   @verbatim
   shifted_src[31:0] = src << bfe
   mask[31:0] = ~(32'hffff_ffff << (bfw+1)) << bfe
   dst[31:0] = shifted_src[31:0] & mask[31:0] | rd[31:0] & ~mask[31:0]
   @endverbatim
 *
 * @param dst Destination to be inserted
 * @param src Containing bit field to extract
 * @param bfwBfe bfwBfe[9:5] is bit field width minus one, bfwBfe[4:0] is bit field end location
 *
 * @return The inserted result
 */
static inline uint_xlen_t XZBF_Bfins(uint_xlen_t dst, uint_xlen_t src, uint_xlen_t bfwBfe)
{
    uint_xlen_t __dst = (uint_xlen_t)(dst);
    asm volatile("bfins %0, %1, %2"
            : :"r"(__dst), "r"(src), "r"(bfwBfe)
            : "memory" );
    return __dst;
}

/*!
 * @brief To set the specified bit field of source data, immediate
 *
   @verbatim
   msk[31:0] = ~(32'hffff_ffff << (bfw+1)) << bfe
   result[31:0] = src[31:0] | msk[31:0]
   @endverbatim
 *
 * @param src Containing bit field to extract
 * @param bfw Bit field width minus one, must be immediate, range from 31 to 0
 * @param bfe Bit field end location, must be immediate, range from 31 to 0
 *
 * @return Set the bit field of src and return the result
 */
#define XZBF_Bfseti(src, bfw, bfe)                        \
({                                                        \
    uint_xlen_t __rs1 = (uint_xlen_t)(src);               \
    uint_xlen_t __dst;                                    \
    asm volatile("bfseti %0, %1, " __ASM_STR(bfw) ", " __ASM_STR(bfe)         \
            : "=r"(__dst) : "r"(__rs1)                    \
            : "memory" );                                 \
    __dst;                                                \
})

/*!
 * @brief to set the specified bit field of source data
 *
   @verbatim
   bfe = bfwBfe[4:0]
   bfw = bfwBfe[9:5]
   msk[31:0] = ~(32'hffff_ffff << (bfw+1)) << bfe
   result[31:0] = src[31:0] | msk[31:0]
   @endverbatim
 *
 * @param src Containing bit field to extract
 * @param bfwBfe bfwBfe[9:5] is bit field width minus one, bfwBfe[4:0] is bit field end location
 *
 * @return Set the bit field of src and return the result
 */
#define XZBF_Bfset(src, bfwBfe)                           \
({                                                        \
    uint_xlen_t __rs1 = (uint_xlen_t)(src);               \
    uint_xlen_t __rs2 = (uint_xlen_t)(bfwBfe);            \
    uint_xlen_t __dst;                                    \
    asm volatile("bfset %0, %1, %2"                       \
            : "=r"(__dst) : "r"(__rs1), "r"(__rs2)        \
            : "memory" );                                 \
    __dst;                                                \
})

/*!
 * @brief Clear bit field of src immediate
 *
   @verbatim
   msk[31:0] = ~(32'hffff_ffff << (bfw+1)) << bfe
   rd[31:0] = rs1[31:0] & ~msk[31:0]
   @endverbatim
 *
 * @param src Containing bit field to extract
 * @param bfw Bit field width minus one, must be immediate, range from 31 to 0
 * @param bfe Bit field end location, must be immediate, range from 31 to 0
 *
 * @return Clear the bit field of src and return the result
 */
#define XZBF_Bfclri(src, bfw, bfe)                        \
({                                                        \
    uint_xlen_t __rs1 = (uint_xlen_t)(src);               \
    uint_xlen_t __dst;                                    \
    asm volatile("bfclri %0, %1, " __ASM_STR(bfw) ", " __ASM_STR(bfe)         \
            : "=r"(__dst) : "r"(__rs1)                    \
            : "memory" );                                 \
    __dst;                                                \
})

/*!
 * @brief clear the specified bit field of src
 *
   @verbatim
   bfe = bfwBfe[4:0]
   bfw = bfwBfe[9:5]
   msk[31:0] = ~(32'hffff_ffff << (bfw+1)) << bfe
   result[31:0] = src[31:0] & ~msk[31:0]
   @endverbatim
 *
 * @param src Containing bit field to extract
 * @param bfwBfe bfwBfe[9:5] is bit field width minus one, bfwBfe[4:0] is bit field end location
 *
 * @return Clear the bit field of src and return the result
 */
#define XZBF_Bfclr(src, bfwBfe)                           \
({                                                        \
    uint_xlen_t __rs1 = (uint_xlen_t)(src);               \
    uint_xlen_t __rs2 = (uint_xlen_t)(bfwBfe);            \
    uint_xlen_t __dst;                                    \
    asm volatile("bfclr %0, %1, %2"                       \
            : "=r"(__dst) : "r"(__rs1), "r"(__rs2)        \
            : "memory" );                                 \
    __dst;                                                \
})

#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* RISCV_XZBF_H_ */
