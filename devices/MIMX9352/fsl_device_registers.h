/*
 * Copyright 2014-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2023 NXP
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
#if (defined(CPU_MIMX9352AVTXM_ca55) || defined(CPU_MIMX9352CVVXM_ca55) || defined(CPU_MIMX9352DVVXM_ca55) || \
     defined(CPU_MIMX9352XVVXM_ca55))

#define MIMX9352_ca55_SERIES

/* CMSIS-style register definitions */
#include "MIMX9352_ca55.h"
/* CPU specific feature definitions */
#include "MIMX9352_ca55_features.h"

#elif (defined(CPU_MIMX9352AVTXM_cm33) || defined(CPU_MIMX9352CVVXM_cm33) || defined(CPU_MIMX9352DVVXM_cm33) || \
     defined(CPU_MIMX9352XVVXM_cm33))


#define MIMX9352_cm33_SERIES

/* CMSIS-style register definitions */
#include "MIMX9352_cm33.h"
/* CPU specific feature definitions */
#include "MIMX9352_cm33_features.h"

#else
#error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
