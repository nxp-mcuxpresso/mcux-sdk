/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __FSL_ADAPTER_FLEXSPI_HYPER_FLASH_CONFIG_H__
#define __FSL_ADAPTER_FLEXSPI_HYPER_FLASH_CONFIG_H__

typedef enum
{
    kHAL_Flash_Flexspi_Clock_High166M, /* Flexspi clock 332M, DDR mode, internal clock 166M. */
    kHAL_Flash_Flexspi_Clock_Low42M,   /* Flexspi clock 83M, DDR mode, internal clock 42M. */
} flexspi_clock_t;

#endif
