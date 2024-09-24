/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef RISCV_XZBRANCH_H_
#define RISCV_XZBRANCH_H_

#include "riscv_asm.h"

/*!
 * @ingroup RISCV_CoreCustomExt
 * @defgroup RISCV_CoreCustomExtXzbranch Branch Extension (Xzbranch)
 * @details Branch Extension 0.1 supported.
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! Counter CSR */
#define CSR_CTR 2064U

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
 * @brief Read branch counter register ctr CSR#2064
 *
 * @return The value of the ctr register
 */
static inline uint32_t XZBRANCHL_ReadCtr(void)
{
    return (uint32_t)csr_read(CSR_CTR);
}

/*!
 * @brief Write branch counter register ctr CSR#2064
 *
 * @param cnt value to write into the ctr register
 */
static inline void XZBRANCHL_WriteCtr(uint32_t cnt)
{
    csr_write(CSR_CTR, cnt);
}

/*!
 * @brief Swap the cnt value
 *
 * @param newCnt New value swapped into the ctr register
 *
 * @return the previous cnt value of the ctr register
 */
static inline uint32_t XZBRANCHL_SwapCtr(uint32_t newCnt)
{
    return (uint32_t)csr_swap(CSR_CTR, newCnt);
}

/*!
 * @brief Accelerate short backward branch loops, providing code size and performance improvements
 *
 * This function works based on the CSR ctr value, but behavior is:
 *
 * ctr = ctr - 1
 * if (ctr != 0)
 *     PC = PC + { {24{1'b1}}, imm[1:0], imm[2], imm[6:3], 1'b0 }
 * else
 *     PC = PC + 2
 *
 * @param imm Must be negative even immediate, range from -256 to -2;
 */
#define XZBRANCHL_Cbdnez(imm) \
({ \
    asm volatile ("c.bdnez " #imm \
        :::"memory"); \
})

#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* RISCV_XZBRANCH_H_ */
