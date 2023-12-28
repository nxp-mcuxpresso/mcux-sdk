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
#if (defined(CPU_LPC865M201JBD64) || defined(CPU_LPC865M201JHI33) || defined(CPU_LPC865M201JHI48))

#define LPC865_SERIES

/* CMSIS-style register definitions */
#include "LPC865.h"
/* CPU specific feature definitions */
#include "LPC865_features.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
