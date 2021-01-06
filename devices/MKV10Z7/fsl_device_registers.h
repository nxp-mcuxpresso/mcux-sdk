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
#if (defined(CPU_MKV10Z16VFM7) || defined(CPU_MKV10Z16VLC7) || defined(CPU_MKV10Z16VLF7) || \
    defined(CPU_MKV10Z32VFM7) || defined(CPU_MKV10Z32VLC7) || defined(CPU_MKV10Z32VLF7))

#define KV10Z7_SERIES

/* CMSIS-style register definitions */
#include "MKV10Z7.h"
/* CPU specific feature definitions */
#include "MKV10Z7_features.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
