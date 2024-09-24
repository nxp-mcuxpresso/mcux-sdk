/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef CORE_RISCV_H_
#define CORE_RISCV_H_

#include "riscv_types.h"
#include "riscv_csr.h"
#include "riscv_asm.h"
#include "riscv_barrier.h"
#include "riscv_interrupt.h"

/*!
 * @defgroup RISCV_CoreFunc RISCV Core Functions
 */

/*!
 * @ingroup RISCV_CoreFunc
 * @defgroup RISCV_CoreBasicDef Basic Definition
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define RISCV_MAKE_VERSION(major, minor, bugfix) (((major)*65536L) + ((minor)*256L) + (bugfix))

/*! @brief RISCV Core driver version. */
#define RISCV_CORE_DRIVER_VERSION RISCV_MAKE_VERSION(1, 0, 0)

/* Macros used for regiser definition. */
#define     __I     volatile const       /*!< Defines 'read only' permissions */
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

/* following defines should be used for structure members */
#define     __IM     volatile const      /*!< Defines 'read only' structure member permissions */
#define     __OM     volatile            /*!< Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*!< Defines 'read / write' structure member permissions */

#define __STATIC_INLINE static inline
#define __ASM asm

/*!
 * @}
 */ /* End of group RISCV_CoreBasicDef */

/*!
 * @ingroup RISCV_CoreFunc
 * @defgroup RISCV_CoreCustomExt RISCV Custom Extensions
 */

#endif
