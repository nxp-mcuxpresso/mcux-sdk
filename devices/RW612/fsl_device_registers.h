/*
 * Copyright 2014-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2022 NXP
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
#if (defined(CPU_RW612ETA1I) || defined(CPU_RW612HNA1I) || defined(CPU_RW612UKA1I))

#define RW612_SERIES

/* CMSIS-style register definitions */
#include "RW612.h"
/* CPU specific feature definitions */
#include "RW612_features.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
