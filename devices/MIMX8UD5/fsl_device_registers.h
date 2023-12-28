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
#if (defined(CPU_MIMX8UD5CVP08_cm33) || defined(CPU_MIMX8UD5DVK08_cm33) || defined(CPU_MIMX8UD5DVP08_cm33))

#define MIMX8UD5_cm33_SERIES

/* CMSIS-style register definitions */
#include "MIMX8UD5_cm33.h"
/* CPU specific feature definitions */
#include "MIMX8UD5_cm33_features.h"

#elif (defined(CPU_MIMX8UD5CVP08_dsp0) || defined(CPU_MIMX8UD5DVK08_dsp0) || defined(CPU_MIMX8UD5DVP08_dsp0))

#define MIMX8UD5_dsp0_SERIES

/* CMSIS-style register definitions */
#include "MIMX8UD5_dsp0.h"
/* CPU specific feature definitions */
#include "MIMX8UD5_dsp0_features.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
