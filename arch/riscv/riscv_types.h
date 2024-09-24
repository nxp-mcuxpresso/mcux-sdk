/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef RISCV_TYPES_H_
#define RISCV_TYPES_H_

#include <stdint.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#ifndef __riscv_xlen
#define __riscv_xlen 32
#endif

#if __riscv_xlen == 64
typedef uint64_t uint_xlen_t;
typedef int64_t int_xlen_t;
#elif __riscv_xlen == 32
typedef uint32_t uint_xlen_t;
typedef int32_t int_xlen_t;
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/

#endif /* RISCV_TYPES_H_ */
