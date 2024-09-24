/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef RISCV_XZEZHV_H_
#define RISCV_XZEZHV_H_

#include "riscv_types.h"

/*!
 * @ingroup RISCV_CoreCustomExt
 * @defgroup RISCV_CoreCustomExtXzezhv EZH-V Extension (Xzezhv)
 * @details EZH-V Extension 0.1 supported.
 */

/*!
 * @ingroup RISCV_CoreCustomExtXzezhv
 * @defgroup RISCV_CoreCustomExtXzezhvInst EZH-V instructions
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define CSR_EZ_MISC     (2104U)

/*!
 * @brief Increment if Signed Less Than, Else Decrement (idlt) Encoding
 *        if (rs1 < rs2) rd++ else rd--
 *        All comparators are signed.

 * @param rd     the destination register address, this parameter must be volatile
 * @param rs1    the 1st source register address
 * @param rs2    the 2nd source register address
 *
 * @return the result
 */
#define XZEZHV_Idlt(rd, rs1, rs2)               \
({                                              \
    int32_t __rs1 = (int32_t)(rs1);             \
    int32_t __rs2 = (int32_t)(rs2);             \
    int32_t __dst = (int32_t)(rd);              \
    asm volatile ("idlt %0, %2, %3"             \
        :"=r"(__dst) : "r"(__rs1), "r"(__rs2)   \
            : "memory");                        \
    __dst;                                      \
})

/*!
 * @brief Increment if Unsigned Less Than, Else Decrement (idltu) Encoding
 *        if (rs1 < rs2) rd++ else rd--
 *        All comparators are unsigned.
 *
 * @param rd     the destination, this parameter must be volatile
 * @param rs1    the 1st source register
 * @param rs2    the 2nd source register
 *
 * @return
 * */
#define XZEZHV_Idltu(rd, rs1, rs2)              \
({                                              \
    uint32_t __dst = (uint32_t)(rd)             \
    int32_t __rs1 = (int32_t)(rs1);             \
    int32_t __rs2 = (int32_t)(rs2);             \
    asm volatile ("idltu %0, %1, %2"            \
        :"=r"(__dst) : "r"(__rs1), "r"(__rs2)   \
            : "memory");                        \
    __dst;                                      \
})


/*!
 * @brief Shift Left Logical Immediate and OR (slloi) Encoding
 *        rd = (rs1 << imm) | rd
 *
 * @param rd    the destination, this parameter should be volatile
 * @param rs1 source register
 * @param imm    immediate
 *
 * @return the result of @return the result of (rs1 << imm) | rd
 * */
#define XZEZHV_Slloi(rd, rs1, imm)               \
({                                               \
    uint_xlen_t __dst = (uint_xlen_t)(rd);       \
    asm volatile ("slloi %0, %1, " #imm          \
            : "=r"(rd) : "r"(rs1)                \
            : "memory");                         \
    __dst;                                       \
})


/*!
 * @brief Shift Left Logical Immediate and AND (sllai) Encoding
 *        rd = (rs1 << imm) & rd
 *
 * @param rd     the destion register, this should be volatile
 * @param rs1    the 1st source register
 * @param imm    immediate
 *
 * @return the result of (rs1 << imm) & rd
 * */
#define XZEZHV_Sllai(rd, rs1, imm)              \
({                                              \
    uint_xlen_t __dst = (uint_xlen_t)(rd);      \
    asm volatile ("sllai %0, %1, " #imm         \
            : "=r"(rd) : "r"(rs1)               \
            : "memory");                        \
    __dst;                                      \
})

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief read gpio ez_misc register CSR#2104
 *
 * @return the register value of misc register
 */
static inline uint32_t EZHV_ReadMiscReg(void)
{
    return (uint32_t)csr_read(CSR_EZ_MISC);
}

/*!
 * @brief write ez_misc register CSR#2104
 *
 * @param heartbeat register value to write
 */
static inline void EZHV_WriteMiscReg(uint16_t heartbeat)
{
    csr_write(CSR_EZ_MISC, heartbeat);
}

#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif
