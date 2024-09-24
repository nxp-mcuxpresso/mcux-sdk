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
#if (defined(CPU_MIMXRT758SGAWAR_cm33_core0) || defined(CPU_MIMXRT758SGFOA_cm33_core0))

#define MIMXRT758S_cm33_core0_SERIES

/* CMSIS-style register definitions */
#include "MIMXRT758S_cm33_core0.h"
/* CPU specific feature definitions */
#include "MIMXRT758S_cm33_core0_features.h"

#elif (defined(CPU_MIMXRT758SGAWAR_cm33_core1) || defined(CPU_MIMXRT758SGFOA_cm33_core1))

#define MIMXRT758S_cm33_core1_SERIES

/* CMSIS-style register definitions */
#include "MIMXRT758S_cm33_core1.h"
/* CPU specific feature definitions */
#include "MIMXRT758S_cm33_core1_features.h"

#elif (defined(CPU_MIMXRT758SGAWAR_hifi1) || defined(CPU_MIMXRT758SGFOA_hifi1))

#define MIMXRT758S_hifi1_SERIES

/* CMSIS-style register definitions */
#include "MIMXRT758S_hifi1.h"
/* CPU specific feature definitions */
#include "MIMXRT758S_hifi1_features.h"

#elif (defined(CPU_MIMXRT758SGAWAR_ezhv) || defined(CPU_MIMXRT758SGFOA_ezhv))

#define MIMXRT758S_ezhv_SERIES

/* CMSIS-style register definitions */
#include "MIMXRT758S_ezhv.h"
/* CPU specific feature definitions */
#include "MIMXRT758S_ezhv_features.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
