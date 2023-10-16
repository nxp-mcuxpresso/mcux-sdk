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
#if (defined(CPU_MIMX8QM6AVUFF_cm4_core0))

#define MIMX8QM6_cm4_core0_SERIES

/* CMSIS-style register definitions */
#include "MIMX8QM6_cm4_core0.h"
/* CPU specific feature definitions */
#include "MIMX8QM6_cm4_core0_features.h"

#elif(defined(CPU_MIMX8QM6AVUFF_cm4_core1))

#define MIMX8QM6_cm4_core1_SERIES

/* CMSIS-style register definitions */
#include "MIMX8QM6_cm4_core1.h"
/* CPU specific feature definitions */
#include "MIMX8QM6_cm4_core1_features.h"

#elif(defined(CPU_MIMX8QM6AVUFF_ca53))

#define MIMX8QM6_ca53_SERIES

/* CMSIS-style register definitions */
#include "MIMX8QM6_ca53.h"

/* CPU specific feature definitions */
#include "MIMX8QM6_ca53_features.h"

#elif(defined(CPU_MIMX8QM6AVUFF_dsp))

#define MIMX8QM6_dsp_SERIES

/* CMSIS-style register definitions */
#include "MIMX8QM6_dsp.h"

/* CPU specific feature definitions */
#include "MIMX8QM6_dsp_features.h"

#else
#error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
