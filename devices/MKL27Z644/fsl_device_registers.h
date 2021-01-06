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
#if (defined(CPU_MKL27Z32VDA4) || defined(CPU_MKL27Z32VFM4) || defined(CPU_MKL27Z32VFT4) || \
    defined(CPU_MKL27Z32VLH4) || defined(CPU_MKL27Z32VMP4) || defined(CPU_MKL27Z64VDA4) || \
    defined(CPU_MKL27Z64VFM4) || defined(CPU_MKL27Z64VFT4) || defined(CPU_MKL27Z64VLH4) || \
    defined(CPU_MKL27Z64VMP4))

#define KL27Z644_SERIES

/* CMSIS-style register definitions */
#include "MKL27Z644.h"
/* CPU specific feature definitions */
#include "MKL27Z644_features.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
