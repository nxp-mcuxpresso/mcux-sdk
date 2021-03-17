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
#if (defined(CPU_MIMX8MM6CVTKZ) || defined(CPU_MIMX8MM6DVTLZ))
#if defined(CONFIG_ARM64)
#define __XCC__
#define __MPU_PRESENT                  1         /**< Defines if an MPU is present or not */
#define __GIC_PRESENT                  1
#define __GIC_PRIO_BITS                5         /**< Number of Bits used for Priority Levels */
#define __FPU_PRESENT                  1         /**< Defines if an FPU is present or not */
#define	GIC_DISTRIBUTOR_BASE	       0x38800000U
#define	GIC_REDISTRIBUTOR_BASE	       0x38880000U

#include "MIMX8MM6_ca53.h"
/* CPU specific feature definitions */
#include "MIMX8MM6_ca53_features.h"
#else

#define MIMX8MM6_cm4_SERIES

/* CMSIS-style register definitions */
#include "MIMX8MM6_cm4.h"
/* CPU specific feature definitions */
#include "MIMX8MM6_cm4_features.h"
#endif

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
