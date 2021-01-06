/*
 * Copyright 2014-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
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
#if (defined(CPU_MCIMX7U5CVP06) || defined(CPU_MCIMX7U5DVK07) || defined(CPU_MCIMX7U5DVP07) || \
     defined(CPU_MCIMX7U5CVP05) || defined(CPU_MCIMX7U5DVK08) || defined(CPU_MCIMX7U5DVP08))

#define MCIMX7U5_cm4_SERIES

/* CMSIS-style register definitions */
#include "MCIMX7U5_cm4.h"
/* CPU specific feature definitions */
#include "MCIMX7U5_cm4_features.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
