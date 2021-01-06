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
#if (defined(CPU_MKV10Z128VFM7) || defined(CPU_MKV10Z128VLC7) || defined(CPU_MKV10Z128VLF7) || \
    defined(CPU_MKV10Z128VLH7) || defined(CPU_MKV10Z64VFM7) || defined(CPU_MKV10Z64VLC7) || \
    defined(CPU_MKV10Z64VLF7) || defined(CPU_MKV10Z64VLH7))

#define KV10Z1287_SERIES

/* CMSIS-style register definitions */
#include "MKV10Z1287.h"
/* CPU specific feature definitions */
#include "MKV10Z1287_features.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
