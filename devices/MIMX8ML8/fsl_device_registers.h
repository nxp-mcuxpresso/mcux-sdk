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
#if (defined(CPU_MIMX8ML8CVNKZ_ca53) || defined(CPU_MIMX8ML8DVNLZ_ca53))

/* CMSIS-style register definitions */
#include "MIMX8ML8_ca53.h"
/* CPU specific feature definitions */
#include "MIMX8ML8_ca53_features.h"

#elif (defined(CPU_MIMX8ML8CVNKZ) || defined(CPU_MIMX8ML8DVNLZ))

#define MIMX8ML8_cm7_SERIES

/* CMSIS-style register definitions */
#include "MIMX8ML8_cm7.h"
/* CPU specific feature definitions */
#include "MIMX8ML8_cm7_features.h"

#elif (defined(CPU_MIMX8ML8CVNKZ_dsp) || defined(CPU_MIMX8ML8DVNLZ_dsp))

#define MIMX8ML8_dsp_SERIES

/* CMSIS-style register definitions */
#include "MIMX8ML8_dsp.h"
/* CPU specific feature definitions */
#include "MIMX8ML8_dsp_features.h"

#else
#error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
