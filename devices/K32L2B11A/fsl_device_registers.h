/*
 * Copyright 2014-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
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
#if (defined(CPU_K32L2B11VFM0A) || defined(CPU_K32L2B11VFT0A) || defined(CPU_K32L2B11VLH0A) || \
    defined(CPU_K32L2B11VMP0A))

#define K32L2B11A_SERIES

/* CMSIS-style register definitions */
#include "K32L2B11A.h"
/* CPU specific feature definitions */
#include "K32L2B11A_features.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
