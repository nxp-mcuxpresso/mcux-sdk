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
#if (defined(CPU_MIMX8MQ7CVAHZ) || defined(CPU_MIMX8MQ7DVAJZ))

#define MIMX8MQ7_cm4_SERIES

/* Add global project definitions */
#if defined(CMSIS_RTE_PROJECT)
#include "RTE_Components.h"
#endif
/* CMSIS-style register definitions */
#include "MIMX8MQ7_cm4.h"
/* CPU specific feature definitions */
#include "MIMX8MQ7_cm4_features.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
