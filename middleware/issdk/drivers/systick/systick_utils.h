/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file systick_utils.h
 * @brief ARM Systick Utilities.

    This file provides systick based counts for the developer
    to get cycle counts for measuring time delays.
*/

#ifndef __SYSTICK_UTILS_H__
#define __SYSTICK_UTILS_H__

/*! @brief       Function to enable systicks framework.
 *  @details     This function initializes the CMSIS define ARM core specific systick implementation.
 *  @param[in]   void.
 *  @return      void.
 *  @constraints This should be the first function to be invoked before other Systick APIs.
 *  @reeentrant  Yes
 */
void BOARD_SystickEnable(void);

/*! @brief       Function to Record the Start systick.
 *  @details     This function records the current systick count for other APIs to compute difference.
 *  @param[in]   pStart Pointer to the variable to store the current/start systick.
 *  @return      void.
 *  @constraints None.
 *  @reeentrant  Yes
 */
void BOARD_SystickStart(int32_t *pStart);

/*! @brief       Function to compute the Elapsed systicks.
 *  @details     This function computes the elapsed ticks by getting the difference
 *               of the current tick to the one in the arguement.
 *  @param[in]   pStart Pointer to the variable contating the start systick.
 *  @return      int32_t The elapsed systicks.
 *  @constraints None.
 *  @reeentrant  Yes
 */
int32_t BOARD_SystickElapsedTicks(int32_t *pStart);

/*! @brief       Function to compute the Elapsed Time.
 *  @details     This function computes the elapsed Time in micro seconds by getting the difference
 *               of the current tick to the one in the arguement.
 *               It also updates the start tick to the current systick.
 *  @param[in]   pStart Pointer to the variable contating the start systick.
 *  @return      uint32_t The elapsed Time in micro seconds.
 *  @constraints None.
 *  @reeentrant  Yes
 */
uint32_t BOARD_SystickElapsedTime_us(int32_t *pStart);

/*! @brief       Function to insert delays.
 *  @details     This function blocks for the specified milli seconds by using the elapsed systicks
 *               to determine time delays.
 *  @param[in]   delay_ms The required time to block.
 *  @return      void.
 *  @constraints None.
 *  @reeentrant  Yes
 */
void BOARD_DELAY_ms(uint32_t delay_ms);

#endif // __SYSTICK_UTILS_H__
