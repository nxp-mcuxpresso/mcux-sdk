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
#if (defined(CPU_MK82FN256CAx15) || defined(CPU_MK82FN256VDC15) || defined(CPU_MK82FN256VLL15) || \
    defined(CPU_MK82FN256VLQ15))

#define K82F25615_SERIES

/* CMSIS-style register definitions */
#include "MK82F25615.h"
/* CPU specific feature definitions */
#include "MK82F25615_features.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
