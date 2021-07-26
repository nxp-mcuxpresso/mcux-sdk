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
#if (defined(CPU_LPC5502JHI48CPXXXX))

#define LPC5502CPXXXX_SERIES
/* define LPC5502_SERIES to reuse code for LPC5502 */
#define LPC5502_SERIES

/* CMSIS-style register definitions */
#include "LPC5502CPXXXX.h"
/* CPU specific feature definitions */
#include "LPC5502CPXXXX_features.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
