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
#if (defined(CPU_MK22FN1M0VLH12) || defined(CPU_MK22FN1M0VLK12) || defined(CPU_MK22FN1M0VLL12) || \
    defined(CPU_MK22FN1M0VLQ12) || defined(CPU_MK22FN1M0VMC12) || defined(CPU_MK22FN1M0VMD12) || \
    defined(CPU_MK22FX512VLH12) || defined(CPU_MK22FX512VLK12) || defined(CPU_MK22FX512VLL12) || \
    defined(CPU_MK22FX512VLQ12) || defined(CPU_MK22FX512VMC12) || defined(CPU_MK22FX512VMD12))

#define K22F12_SERIES

/* CMSIS-style register definitions */
#include "MK22F12.h"
/* CPU specific feature definitions */
#include "MK22F12_features.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
