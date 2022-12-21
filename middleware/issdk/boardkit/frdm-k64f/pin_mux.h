/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_


/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Direction type  */
typedef enum _pin_mux_direction
{
  kPIN_MUX_DirectionInput = 0U,         /* Input direction */
  kPIN_MUX_DirectionOutput = 1U,        /* Output direction */
  kPIN_MUX_DirectionInputOrOutput = 2U  /* Input or output direction */
} pin_mux_direction_t;

/*!
 * @addtogroup pin_mux
 * @{
 */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif


/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void UART0_InitPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void UART0_DeinitPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void UART1_InitPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void UART1_DeinitPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void UART2_InitPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void UART2_DeinitPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void UART3_InitPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void UART3_DeinitPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void UART4_InitPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void UART4_DeinitPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void I2C0_InitPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void I2C0_DeinitPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void I2C1_InitPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void I2C1_DeinitPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void I2C2_InitPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void I2C2_DeinitPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void DSPI0_InitPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void DSPI0_DeinitPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void DSPI1_InitPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void DSPI1_DeinitPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void DSPI2_InitPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void DSPI2_DeinitPins(void);
#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
