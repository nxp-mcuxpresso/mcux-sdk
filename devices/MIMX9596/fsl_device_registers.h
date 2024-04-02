/*
 * Copyright 2014-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
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
#if (defined(CPU_MIMX9596AVTXN_ca55) || defined(CPU_MIMX9596AVZXN_ca55) || defined(CPU_MIMX9596DVTXQ_ca55) || \
    defined(CPU_MIMX9596DVYXQ_ca55) || defined(CPU_MIMX9596DVZXQ_ca55) || defined(CPU_MIMX9596XVTXL_ca55))

#define MIMX9596_ca55_SERIES

/* CMSIS-style register definitions */
#include "MIMX9596_ca55.h"
/* CPU specific feature definitions */
#include "MIMX9596_ca55_features.h"

#elif (defined(CPU_MIMX9596AVTXN_cm7) || defined(CPU_MIMX9596AVZXN_cm7) || defined(CPU_MIMX9596DVTXQ_cm7) || \
    defined(CPU_MIMX9596DVYXQ_cm7) || defined(CPU_MIMX9596DVZXQ_cm7) || defined(CPU_MIMX9596XVTXL_cm7))

#define MIMX9596_cm7_SERIES

/* CMSIS-style register definitions */
#include "MIMX9596_cm7.h"
/* CPU specific feature definitions */
#include "MIMX9596_cm7_features.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
