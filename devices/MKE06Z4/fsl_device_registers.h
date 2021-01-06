/*
 * Copyright 2014-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
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
#if (defined(CPU_MKE06Z128VLD4) || defined(CPU_MKE06Z128VLH4) || defined(CPU_MKE06Z128VLK4) || \
    defined(CPU_MKE06Z128VQH4) || defined(CPU_MKE06Z64VLD4) || defined(CPU_MKE06Z64VLH4) || \
    defined(CPU_MKE06Z64VLK4) || defined(CPU_MKE06Z64VQH4))

#define KE06Z4_SERIES

/* CMSIS-style register definitions */
#include "MKE06Z4.h"
/* CPU specific feature definitions */
#include "MKE06Z4_features.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
