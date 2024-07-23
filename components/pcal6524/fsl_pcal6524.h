/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_PCAL6524_H_
#define _FSL_PCAL6524_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "fsl_common.h"

/*
 * Change log:
 *
 *   1.0.0
 *     - Initial version
 */

/*!
 * @addtogroup pcal6524
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Define the Register Memory Map of PCAL6524. */
#define PCAL6524_OUTPUT_PORT0 (0x04U)
#define PCAL6524_OUTPUT_PORT1 (0x05U)
#define PCAL6524_OUTPUT_PORT2 (0x06U)
#define PCAL6524_CONFIG_PORT0 (0x0CU)
#define PCAL6524_CONFIG_PORT1 (0x0DU)
#define PCAL6524_CONFIG_PORT2 (0x0EU)

/*! @brief PCAL6524 IO direction. */
typedef enum _pcal6524_dir
{
    kPCAL6524_Input = 0U, /*!< Set pin as input. */
    kPCAL6524_Output,     /*!< Set pin as output. */
} pcal6524_dir_t;

/*! @brief PCAL6524 I2C receive function. */
typedef status_t (*pcal6524_i2c_receive_func_t)(uint8_t deviceAddress,
                                                uint32_t subAddress,
                                                uint8_t subaddressSize,
                                                uint8_t *rxBuff,
                                                uint8_t rxBuffSize,
                                                uint32_t flags);

/*! @brief PCAL6524 I2C send function. */
typedef status_t (*pcal6524_i2c_send_func_t)(uint8_t deviceAddress,
                                             uint32_t subAddress,
                                             uint8_t subaddressSize,
                                             const uint8_t *txBuff,
                                             uint8_t txBuffSize,
                                             uint32_t flags);

/*! @brief PCAL6524 configure structure.*/
typedef struct _pcal6524_config
{
    uint8_t i2cAddr;                             /*!< I2C address. */
    pcal6524_i2c_send_func_t I2C_SendFunc;       /*!< Function to send I2C data. */
    pcal6524_i2c_receive_func_t I2C_ReceiveFunc; /*!< Function to receive I2C data. */
} pcal6524_config_t;

/*! @brief PCAL6524 driver handle. */
typedef struct _pcal6524_handle
{
    uint8_t i2cAddr;                             /*!< I2C address. */
    pcal6524_i2c_send_func_t I2C_SendFunc;       /*!< Function to send I2C data. */
    pcal6524_i2c_receive_func_t I2C_ReceiveFunc; /*!< Function to receive I2C data. */
} pcal6524_handle_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and Control function
 * @{
 */

/*!
 * @brief Initializes the PCAL6524 driver handle.
 *
 * @param handle Pointer to the PCAL6524 handle.
 * @param config Pointer to the PCAL6524 configuration structure.
 */
void PCAL6524_Init(pcal6524_handle_t *handle, const pcal6524_config_t *config);

/*!
 * @brief Set PCAL6524 pins direction.
 *
 * This function sets multiple pins direction, the pins to modify are passed in
 * as a bit OR'ed value.
 *
 * For example, the following code set pin2 and pin3 to output:
 *
 * @code
   PCAL6524_SetDirection(handle, (1<<2) | (1<<3), pkPCAL6524_Output);
   @endcode
 *
 * @param handle Pointer to the PCAL6524 handle.
 * @param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * @param dir Pin direction.
 * @return Return @ref kStatus_Success if successed, otherwise returns error code.
 */
status_t PCAL6524_SetDirection(pcal6524_handle_t *handle, uint32_t pins, pcal6524_dir_t dir);

/*!
 * @brief Set PCAL6524 pins output value to 1.
 *
 * This function changes multiple pins, the pins to modify are passed in as
 * a bit OR'ed value.
 *
 * For example, the following code set pin2 and pin3 output value to 1.
 *
 * @code
   PCAL6524_SetPins(handle, (1<<2) | (1<<3));
   @endcode
 *
 * @param handle Pointer to the PCAL6524 handle.
 * @param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * @return Return @ref kStatus_Success if successed, otherwise returns error code.
 */
status_t PCAL6524_SetPins(pcal6524_handle_t *handle, uint32_t pins);

/*!
 * @brief Set PCAL6524 pins output value to 0.
 *
 * This function changes multiple pins, the pins to modify are passed in as
 * a bit OR'ed value.
 *
 * For example, the following code set pin2 and pin3 output value to 0.
 *
 * @code
   PCAL6524_ClearPins(handle, (1<<2) | (1<<3));
   @endcode
 *
 * @param handle Pointer to the PCAL6524 handle.
 * @param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * @return Return @ref kStatus_Success if successed, otherwise returns error code.
 */
status_t PCAL6524_ClearPins(pcal6524_handle_t *handle, uint32_t pins);

/*!
 * @brief Toggle PCAL6524 pins output value.
 *
 * This function changes multiple pins, the pins to modify are passed in as
 * a bit OR'ed value.
 *
 * For example, the following code toggle pin2 and pin3 output value.
 *
 * @code
   PCAL6524_ClearPins(handle, (1<<2) | (1<<3));
   @endcode
 *
 * @param handle Pointer to the PCAL6524 handle.
 * @param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * @return Return @ref kStatus_Success if successed, otherwise returns error code.
 */
status_t PCAL6524_TogglePins(pcal6524_handle_t *handle, uint32_t pins);

/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_PCAL6524_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
