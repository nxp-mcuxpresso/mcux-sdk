/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _APP_H_
#define _APP_H_
/*${header:start}*/
#include "fsl_qspi.h"

/*${header:end}*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*${macro:start}*/
#define EXAMPLE_QSPI          QuadSPI0
#define QSPI_CLOCK_SOURCE     kCLOCK_McgPll0Clk
#define QSPI_CLK_FREQ         CLOCK_GetFreq(kCLOCK_McgPll0Clk)
#define FLASH_PAGE_SIZE       256U
#define FLASH_SECTORE_SIZE    4096U
#define FLASH_SIZE            0x00400000U
#define FLASH_ENABLE_QUAD_CMD 0x40U
/*${macro:end}*/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*${prototype:start}*/
extern uint32_t lut[FSL_FEATURE_QSPI_LUT_DEPTH];
extern qspi_flash_config_t single_config;

void BOARD_InitHardware(void);

/*${prototype:end}*/

#endif /* _APP_H_ */
