/*
 * Copyright 2014-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2023 NXP
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
#if (defined(CPU_MIMXRT1189CVM8B_cm7) || defined(CPU_MIMXRT1189XVM8B_cm7))

#define MIMXRT1189_cm7_SERIES

/* CMSIS-style register definitions */
#include "MIMXRT1189_cm7.h"
/* CPU specific feature definitions */
#include "MIMXRT1189_cm7_features.h"

#elif (defined(CPU_MIMXRT1189CVM8B_cm33) || defined(CPU_MIMXRT1189XVM8B_cm33))

#define MIMXRT1189_cm33_SERIES

/* CMSIS-style register definitions */
#include "MIMXRT1189_cm33.h"
/* CPU specific feature definitions */
#include "MIMXRT1189_cm33_features.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
