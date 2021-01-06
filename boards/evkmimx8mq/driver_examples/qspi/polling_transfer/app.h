/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
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
#define EXAMPLE_QSPI QuadSPI
#define QSPI_CLK_FREQ                                                                      \
    CLOCK_GetPllFreq(kCLOCK_SystemPll1Ctrl) / (CLOCK_GetRootPreDivider(kCLOCK_RootQspi)) / \
        (CLOCK_GetRootPostDivider(kCLOCK_RootQspi)) / 8 /* SYSTEM PLL1 DIV8 */
#define FLASH_PAGE_SIZE        256U
#define FLASH_SECTORE_SIZE     0x10000
#define FLASH_SIZE             0x10000000U
#define QSPI_ERASE_ADDR_OFFSET 0x40000U
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
