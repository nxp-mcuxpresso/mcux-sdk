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
#if (defined(CPU_MKE13Z128VLF7) || defined(CPU_MKE13Z128VLH7) || defined(CPU_MKE13Z128VLL7) || \
    defined(CPU_MKE13Z256VLF7) || defined(CPU_MKE13Z256VLH7) || defined(CPU_MKE13Z256VLL7))

#define KE13Z7_SERIES

/* CMSIS-style register definitions */
#include "MKE13Z7.h"
/* CPU specific feature definitions */
#include "MKE13Z7_features.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
