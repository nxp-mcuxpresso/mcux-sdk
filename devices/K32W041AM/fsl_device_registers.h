/*
 * Copyright 2014-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef __FSL_DEVICE_REGISTERS_H__
#define __FSL_DEVICE_REGISTERS_H__

/*
 * Include the cpu specific register header files.
 *
 * The CPU macro should be declared in the project or makefile.
 */
#if (defined(CPU_K32W041AMK) || defined(CPU_K32W041AMY) || defined(CPU_K32W041AMZ))

#define K32W041AM_SERIES

/* CMSIS-style register definitions */
#include "K32W041AM.h"
/* CPU specific feature definitions */
#include "K32W041AM_features.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
