/*
 * Copyright 2014-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
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
#if (defined(CPU_LPC802M001JDH16) || defined(CPU_LPC802M001JDH20) || defined(CPU_LPC802M001JHI33) || \
    defined(CPU_LPC802M011JDH20) || defined(CPU_LPC802UK))

#define LPC802_SERIES

/* CMSIS-style register definitions */
#include "LPC802.h"
/* CPU specific feature definitions */
#include "LPC802_features.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
