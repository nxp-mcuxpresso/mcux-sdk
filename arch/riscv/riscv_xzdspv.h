/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef RISCV_XZDSPV_H_
#define RISCV_XZDSPV_H_

#include <stdint.h>

/*!
 * @ingroup RISCV_CoreCustomExt
 * @defgroup RISCV_CoreCustomExtXzdspv DSP-V Extension (Xzdspv)
 * @details DSP-V Extension 0.1 supported.
 * @{
 */

/*!
 * @name DSPV CSR definition
 * @{
 */

/* AGU pointer address offset */
#define DSPV_AGU_ADDR_OFFSET   (4U)

#define CSR_DSPV_AGU_PTR0_PBASE (2112u)
#define CSR_DSPV_AGU_PTR0_STEP0 (2113u)
#define CSR_DSPV_AGU_PTR0_STEP1 (2114u)
#define CSR_DSPV_AGU_PTR0_INDEX (2115u)
#define CSR_DSPV_AGU_PTR0_INFO  (2144u)

#define CSR_DSPV_AGU_PTRn_PBASE(n) (CSR_DSPV_AGU_PTR0_PBASE + ((n) * DSPV_AGU_ADDR_OFFSET))
#define CSR_DSPV_AGU_PTRn_STEP0(n) (CSR_DSPV_AGU_PTR0_STEP0 + ((n) * DSPV_AGU_ADDR_OFFSET))
#define CSR_DSPV_AGU_PTRn_STEP1(n) (CSR_DSPV_AGU_PTR0_STEP1 + ((n) * DSPV_AGU_ADDR_OFFSET))
#define CSR_DSPV_AGU_PTRn_INDEX(n) (CSR_DSPV_AGU_PTR0_INDEX + ((n) * DSPV_AGU_ADDR_OFFSET))
#define CSR_DSPV_AGU_PTRn_INFO(n)  (CSR_DSPV_AGU_PTR0_INFO  + (n))

#define CSR_DSPV_HIST (2152u)
#define CSR_DSPV_MUX  (2153u)

/* Scaler. */
#define CSR_DSPV_SCALAR_SRC_LO  (2154u)
#define CSR_DSPV_SCALAR_SRC_HI  (2155u)
#define CSR_DSPV_SCALAR_DST_LO  (2156u)
#define CSR_DSPV_SCALAR_DST_HI  (2157u)

/* NCO */
#define CSR_DSPV_NCO_PHASE  (2158u)
#define CSR_DSPV_NCO_FREQ   (2159u)
#define CSR_DSPV_NCO_CONFIG (2160u)

#define CSR_DSPV_STAT   (2161u)
#define CSR_DSPV_CONFIG (2162u)

/* Cache */
#define CSR_DSPV_SC_CONTROL  (2163u)
#define CSR_DSPV_SC_HITS     (2164u)
#define CSR_DSPV_SC_STALLS   (2165u)

/* Scratch */
#define CSR_DSPV_SCRATCH_54  (2166u)
#define CSR_DSPV_SCRATCH_55  (2167u)
#define CSR_DSPV_SCRATCH_56  (2168u)
#define CSR_DSPV_SCRATCH_57  (2169u)
#define CSR_DSPV_SCRATCH_58  (2170u)
#define CSR_DSPV_SCRATCH_59  (2171u)
#define CSR_DSPV_SCRATCH_60  (2172u)
#define CSR_DSPV_SCRATCH_61  (2173u)
#define CSR_DSPV_SCRATCH_62  (2174u)
#define CSR_DSPV_SCRATCH_63  (2175u)

/*!
 * @}
 */

/*! @brief LIST of DSPV AGU */
typedef enum {
    kDSPV_AGU_P0 = 0, /*!< vcpu address generation unit pointer 0 */
    kDSPV_AGU_P1 = 1, /*!< vcpu address generation unit pointer 1 */
    kDSPV_AGU_P2 = 2, /*!< vcpu address generation unit pointer 2 */
    kDSPV_AGU_P3 = 3, /*!< vcpu address generation unit pointer 3 */
    kDSPV_AGU_P4 = 4, /*!< vcpu address generation unit pointer 4 */
    kDSPV_AGU_P5 = 5, /*!< vcpu address generation unit pointer 5 */
    kDSPV_AGU_P6 = 6, /*!< vcpu address generation unit pointer 6 */
    kDSPV_AGU_P7 = 7, /*!< vcpu address generation unit pointer 7 */
    kDSPV_AGU_Num,    /*!< Pointer number. */
} dspv_agu_point_t;

/*! @brief DSPV AGU pointer configuration
 *
 * This structure holds the configuration for AGU pointer
 */
typedef struct _dspv_agu_pointer
{
    uint32_t pbase; /*!< base address for a VCPU AGU pointer */
    int32_t step0;  /*!< the step for a VCPU AGU pointer*/
    int32_t step1;  /*!< the length/alternate step for a VCPU AGU pointer */
    int32_t index;  /*!< the index for VCPU instructions which use AGU */
    uint32_t info;  /*!< AGU pointer.info */
} dspv_agu_pointer_descriptor_t;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* RISCV_XZDSPV_H_ */
