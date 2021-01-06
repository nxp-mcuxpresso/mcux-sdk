/*
 * Copyright 2020 NXP.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_


/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/

/* PTA17 (number AD19), I2C0_SDA */
/* Routed pin properties */
#define BOARD_I2C0_SDA_PERIPHERAL                                          FXIO0   /*!< Peripheral name */
#define BOARD_I2C0_SDA_SIGNAL                                             fxio_d   /*!< Signal name */
#define BOARD_I2C0_SDA_CHANNEL                                                 1   /*!< Signal channel */
#define BOARD_I2C0_SDA_PIN_NAME                                            PTA17   /*!< Routed pin name */
#define BOARD_I2C0_SDA_PIN_FUNCTION_ID                     IOMUXC_PTA17_FXIO0_D1   /*!< Pin function id */
#define BOARD_I2C0_SDA_LABEL                                          "I2C0_SDA"   /*!< Label */
#define BOARD_I2C0_SDA_NAME                                           "I2C0_SDA"   /*!< Identifier */

/* PTA16 (number AG18), I2C0_SCL */
/* Routed pin properties */
#define BOARD_I2C0_SCL_PERIPHERAL                                          FXIO0   /*!< Peripheral name */
#define BOARD_I2C0_SCL_SIGNAL                                             fxio_d   /*!< Signal name */
#define BOARD_I2C0_SCL_CHANNEL                                                 0   /*!< Signal channel */
#define BOARD_I2C0_SCL_PIN_NAME                                            PTA16   /*!< Routed pin name */
#define BOARD_I2C0_SCL_PIN_FUNCTION_ID                     IOMUXC_PTA16_FXIO0_D0   /*!< Pin function id */
#define BOARD_I2C0_SCL_LABEL                                          "I2C0_SCL"   /*!< Label */
#define BOARD_I2C0_SCL_NAME                                           "I2C0_SCL"   /*!< Identifier */

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif


/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);                                 /*!< Function assigned for the core: Cortex-M4[cm4] */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
