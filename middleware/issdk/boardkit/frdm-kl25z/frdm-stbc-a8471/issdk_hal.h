/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file issdk_hal.h
 * @brief Wrapper for Hardware Abstraction Layer (HAL)

    This file simply provides one level of indirection for the developer
    to select the particular Hardware Abstraction Layer they would like to use.
*/

#ifndef __ISSDK_HAL_H__
#define __ISSDK_HAL_H__

#include "fsl_lpsci_cmsis.h"
#include "fsl_i2c_cmsis.h"
#include "fsl_spi_cmsis.h"

#include "frdm_kl25z.h"             //Include appropriate MCU board header file
#include "frdm_stbc_a8471_shield.h" //Include appropriate sensor shield board header file

#endif // __ISSDK_HAL_H__
