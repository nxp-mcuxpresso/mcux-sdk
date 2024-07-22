/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_ADP5585_H_
#define _FSL_ADP5585_H_

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
 * @addtogroup adp5585
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Define the Register Memory Map of ADP5585. */
#define ADP5585_GPO_DATA_OUT_A   (0x23U)
#define ADP5585_GPO_DATA_OUT_B   (0x24U)
#define ADP5585_GPIO_DIRECTION_A (0x27U)
#define ADP5585_GPIO_DIRECTION_B (0x28U)

/*! @brief ADP5585 IO direction. */
typedef enum _adp5585_dir
{
    kADP5585_Input = 0U, /*!< Set pin as input. */
    kADP5585_Output,     /*!< Set pin as output. */
} adp5585_dir_t;

/*! @brief ADP5585 I2C receive function. */
typedef status_t (*adp5585_i2c_receive_func_t)(uint8_t deviceAddress,
                                               uint32_t subAddress,
                                               uint8_t subaddressSize,
                                               uint8_t *rxBuff,
                                               uint8_t rxBuffSize,
                                               uint32_t flags);

/*! @brief ADP5585 I2C send function. */
typedef status_t (*adp5585_i2c_send_func_t)(uint8_t deviceAddress,
                                            uint32_t subAddress,
                                            uint8_t subaddressSize,
                                            const uint8_t *txBuff,
                                            uint8_t txBuffSize,
                                            uint32_t flags);

/*! @brief ADP5585 configure structure.*/
typedef struct _adp5585_config
{
    uint8_t i2cAddr;                            /*!< I2C address. */
    adp5585_i2c_send_func_t I2C_SendFunc;       /*!< Function to send I2C data. */
    adp5585_i2c_receive_func_t I2C_ReceiveFunc; /*!< Function to receive I2C data. */
} adp5585_config_t;

/*! @brief ADP5585 driver handle. */
typedef struct _adp5585_handle
{
    uint8_t i2cAddr;                            /*!< I2C address. */
    adp5585_i2c_send_func_t I2C_SendFunc;       /*!< Function to send I2C data. */
    adp5585_i2c_receive_func_t I2C_ReceiveFunc; /*!< Function to receive I2C data. */
} adp5585_handle_t;

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
 * @brief Initializes the ADP5585 driver handle.
 *
 * @param handle Pointer to the ADP5585 handle.
 * @param config Pointer to the ADP5585 configuration structure.
 */
void ADP5585_Init(adp5585_handle_t *handle, const adp5585_config_t *config);

/*!
 * @brief Set ADP5585 pins direction.
 *
 * This function sets multiple pins direction, the pins to modify are passed in
 * as a bit OR'ed value.
 *
 * For example, the following code set pin2 and pin3 to output:
 *
 * @code
   ADP5585_SetDirection(handle, (1<<2) | (1<<3), pkADP5585_Output);
   @endcode
 *
 * @param handle Pointer to the ADP5585 handle.
 * @param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * @param dir Pin direction.
 * @return Return @ref kStatus_Success if successed, otherwise returns error code.
 */
status_t ADP5585_SetDirection(adp5585_handle_t *handle, uint16_t pins, adp5585_dir_t dir);

/*!
 * @brief Set ADP5585 pins output value to 1.
 *
 * This function changes multiple pins, the pins to modify are passed in as
 * a bit OR'ed value.
 *
 * For example, the following code set pin2 and pin3 output value to 1.
 *
 * @code
   ADP5585_SetPins(handle, (1<<2) | (1<<3));
   @endcode
 *
 * @param handle Pointer to the ADP5585 handle.
 * @param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * @return Return @ref kStatus_Success if successed, otherwise returns error code.
 */
status_t ADP5585_SetPins(adp5585_handle_t *handle, uint16_t pins);

/*!
 * @brief Set ADP5585 pins output value to 0.
 *
 * This function changes multiple pins, the pins to modify are passed in as
 * a bit OR'ed value.
 *
 * For example, the following code set pin2 and pin3 output value to 0.
 *
 * @code
   ADP5585_ClearPins(handle, (1<<2) | (1<<3));
   @endcode
 *
 * @param handle Pointer to the ADP5585 handle.
 * @param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * @return Return @ref kStatus_Success if successed, otherwise returns error code.
 */
status_t ADP5585_ClearPins(adp5585_handle_t *handle, uint16_t pins);

/*!
 * @brief Toggle ADP5585 pins output value.
 *
 * This function changes multiple pins, the pins to modify are passed in as
 * a bit OR'ed value.
 *
 * For example, the following code toggle pin2 and pin3 output value.
 *
 * @code
   ADP5585_ClearPins(handle, (1<<2) | (1<<3));
   @endcode
 *
 * @param handle Pointer to the ADP5585 handle.
 * @param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * @return Return @ref kStatus_Success if successed, otherwise returns error code.
 */
status_t ADP5585_TogglePins(adp5585_handle_t *handle, uint16_t pins);

/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_ADP5585_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
