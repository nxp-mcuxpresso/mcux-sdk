/*
 * Copyright 2021-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _MMU_H_
#define _MMU_H_

#include "fsl_device_registers.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/* symbols defined in linker script: */
extern uintptr_t __text[];
extern uintptr_t __etext[];
extern uintptr_t __data_start__[];
extern uintptr_t __data_end__[];
extern uintptr_t __stacks_limit__[];
extern uintptr_t __stacks_top__[];
extern uintptr_t __noncachedata_start__[];
extern uintptr_t __noncachedata_end__[];
extern uintptr_t __ocramtext_start__[];
extern uintptr_t __ocramtext_end__[];
extern uintptr_t __ocramdata_start__[];
extern uintptr_t __ocramdata_end__[];
extern uintptr_t __itcm_start__[];
extern uintptr_t __itcm_end__[];
extern uintptr_t __dtcm_start__[];
extern uintptr_t __dtcm_end__[];

/*******************************************************************************
 * API
 ******************************************************************************/
void MMU_init(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _MMU_H_ */
