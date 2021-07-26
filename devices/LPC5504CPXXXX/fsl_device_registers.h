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
#if (defined(CPU_LPC5504JHI48CPXXXX))

#define LPC5504CPXXXX_SERIES
/* define LPC5504_SERIES to reuse code for LPC5504 */
#define LPC5504_SERIES

/* CMSIS-style register definitions */
#include "LPC5504CPXXXX.h"
/* CPU specific feature definitions */
#include "LPC5504CPXXXX_features.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
