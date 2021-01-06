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
#if (defined(CPU_MKE04Z128VLD4) || defined(CPU_MKE04Z128VLH4) || defined(CPU_MKE04Z128VLK4) || \
    defined(CPU_MKE04Z128VQH4) || defined(CPU_MKE04Z64VLD4) || defined(CPU_MKE04Z64VLH4) || \
    defined(CPU_MKE04Z64VLK4) || defined(CPU_MKE04Z64VQH4))

#define KE04Z1284_SERIES

/* CMSIS-style register definitions */
#include "MKE04Z1284.h"
/* CPU specific feature definitions */
#include "MKE04Z1284_features.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
