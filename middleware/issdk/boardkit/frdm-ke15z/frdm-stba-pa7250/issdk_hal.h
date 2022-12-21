/*
 * Copyright 2019 NXP
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

#include "fsl_lpspi_cmsis.h"
#include "fsl_lpi2c_cmsis.h"
#include "fsl_lpuart_cmsis.h"

#include "frdm_ke15z.h"              //Include appropriate MCU board header file
#include "frdm-stba-pa7250_shield.h" //Include appropriate sensor shield board header file

#endif // __ISSDK_HAL_H__
