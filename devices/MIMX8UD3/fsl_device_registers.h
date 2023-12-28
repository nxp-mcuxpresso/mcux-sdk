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
#if (defined(CPU_MIMX8UD3CVP08_cm33) || defined(CPU_MIMX8UD3DVK08_cm33) || defined(CPU_MIMX8UD3DVP08_cm33))

#define MIMX8UD3_cm33_SERIES

/* CMSIS-style register definitions */
#include "MIMX8UD3_cm33.h"
/* CPU specific feature definitions */
#include "MIMX8UD3_cm33_features.h"

#elif (defined(CPU_MIMX8UD3CVP08_dsp0) || defined(CPU_MIMX8UD3DVK08_dsp0) || defined(CPU_MIMX8UD3DVP08_dsp0))

#define MIMX8UD3_dsp0_SERIES

/* CMSIS-style register definitions */
#include "MIMX8UD3_dsp0.h"
/* CPU specific feature definitions */
#include "MIMX8UD3_dsp0_features.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
