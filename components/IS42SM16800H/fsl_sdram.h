/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_SDRAM_H_
#define _FSL_SDRAM_H_

#include "fsl_sdramc.h"

/*!
 * @addtogroup sdram_mt48lc4m16
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief SDRAM driver version. */
#define FSL_SDRAM_DRIVER_VERSION (MAKE_VERSION(2, 0, 1)) /*!< Version 2.0.1. */
/*! @brief Define the access value of the SDRAM location. */
#define SDRAM_COMMAND_ACCESSVALUE 0xaaU

/*! @brief Define the right address line for the mrs register setting. */
#define ADDR9  9U
#define ADDR10 10U
#define ADDR11 11U
#define ADDR12 12U
#define ADDR13 13U
#define ADDR14 14U
#define ADDR15 15U
#define ADDR16 16U
#define ADDR17 17U
#define ADDR18 18U
#define ADDR19 19U
#define ADDR20 20U
#define ADDR21 21U
#define ADDR22 22U
#define ADDR23 23U

/*! @brief Define the physical connection--16bit port 8 column. */
#define SDRAM_A0  ADDR16
#define SDRAM_A1  ADDR15
#define SDRAM_A2  ADDR14
#define SDRAM_A3  ADDR13
#define SDRAM_A4  ADDR12
#define SDRAM_A5  ADDR11
#define SDRAM_A6  ADDR10
#define SDRAM_A7  ADDR9
#define SDRAM_A8  ADDR17
#define SDRAM_A9  ADDR18
#define SDRAM_A10 ADDR19
#define SDRAM_A11 ADDR20
#define SDRAM_A12 ADDR21
#define SDRAM_A13 ADDR22
#define SDRAM_A14 ADDR23

#define BURSTLENGTH    0U
#define BURSTTYPE      0U
#define CASLATENCY     2U
#define OPMODE         0U
#define WRITEBURSTMODE 0U

/*! @brief SDRAM Mode register write burst mode setting. */
typedef enum _sdram_write_burst_mode
{
    kSDRAM_MrsWriteBurst = 0x0U, /*!< Write burst mode. */
    kSDRAM_MrsWriteSingle        /*!< Write single location mode.  */
} sdram_write_burst_mode_t;

/*! @brief SDRAM Mode register operation mode setting. */
typedef enum _sdram_operation_mode
{
    kSDRAM_MrsStandOperation = 0x0U, /*!< Standard operation mode. */
    kSDRAM_MrsAllOtherReserve        /*!< All other states reserved.  */
} sdram_operation_mode_t;

/*! @brief SDRAM Mode register CAS latency setting. */
typedef enum _sdram_cas_latency
{
    kSDRAM_MrsLatencyOne = 0x1U, /*!< Latency one. */
    kSDRAM_MrsLatencyTwo,        /*!< Latency two. */
    kSDRAM_MrsLatencyThree       /*!< Latency three. */
} sdram_cas_latency_t;

/*! @brief SDRAM Mode register burst type setting. */
typedef enum _sdram_burst_type
{
    kSDRAM_MrsSequential = 0x0U, /*!< Sequential. */
    kSDRAM_MrsInterleaved,       /*!< Interleaved. */
} sdram_burst_type_t;

/*! @brief SDRAM Mode register burst length setting. */
typedef enum _sdram_burst_len
{
    kSDRAM_MrsBurstLenOne     = 0x0U, /*!< 1. */
    kSDRAM_MrsBurstLenTwo     = 0x1U, /*!< 2. */
    kSDRAM_MrsBurstLenFour    = 0x2U, /*!< 4. */
    kSDRAM_MrsBurstLenEight   = 0x3U, /*!< 8. */
    kSDRAM_MrsBurstLenAllPage = 0x7U  /*!< Full page only for sequential burst type. */
} sdram_burst_len_t;
/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the SDRAM device.
 * The function is used to initialize the MT48LC4M16A2 SDRAM external memory.
 * @param base SDRAM controller peripheral base address.
 * @param address The address of the sdram.
 * @param busClock_Hz The bus clock frequency for SDRAM controller.
 * @return the execution result.
 *
 */
status_t SDRAM_Init(SDRAM_Type *base, uint32_t address, uint32_t busClock_Hz);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /*_FSL_SDRAM_H_*/
