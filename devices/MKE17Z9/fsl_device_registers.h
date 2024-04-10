/*
 * Copyright 2014-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2023 NXP
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
#if (defined(CPU_MKE17Z512VLH9) || defined(CPU_MKE17Z512VLL9))

#define KE17Z9_SERIES

/* CMSIS-style register definitions */
#include "MKE17Z9.h"
/* CPU specific feature definitions */
#include "MKE17Z9_features.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
