/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_PCA6416A_H_
#define _FSL_PCA6416A_H_

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
 * @addtogroup pca6416a
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Define the Register Memory Map of PCA6416A. */
#define PCA6416A_INPUT_PORT_0   (0x00U)
#define PCA6416A_INPUT_PORT_1   (0x01U)
#define PCA6416A_OUTPUT_PORT_0  (0x02U)
#define PCA6416A_OUTPUT_PORT_1  (0x03U)
#define PCA6416A_POL_INV_PORT_0 (0x04U)
#define PCA6416A_POL_INV_PORT_1 (0x05U)
#define PCA6416A_CFG_PORT_0     (0x06U)
#define PCA6416A_CFG_PORT_1     (0x07U)

/*! @brief PCA6416A IO direction. */
typedef enum _pca6416a_dir
{
    kPCA6416A_Input = 0U, /*!< Set pin as input. */
    kPCA6416A_Output,     /*!< Set pin as output. */
} pca6416a_dir_t;

/*! @brief PCA6416A I2C receive function. */
typedef status_t (*pca6416a_i2c_receive_func_t)(uint8_t deviceAddress,
                                                uint32_t subAddress,
                                                uint8_t subaddressSize,
                                                uint8_t *rxBuff,
                                                uint8_t rxBuffSize,
                                                uint32_t flags);

/*! @brief PCA6416A I2C send function. */
typedef status_t (*pca6416a_i2c_send_func_t)(uint8_t deviceAddress,
                                             uint32_t subAddress,
                                             uint8_t subaddressSize,
                                             const uint8_t *txBuff,
                                             uint8_t txBuffSize,
                                             uint32_t flags);

/*! @brief PCA6416A configure structure.*/
typedef struct _pca6416a_config
{
    uint8_t i2cAddr;                             /*!< I2C address. */
    pca6416a_i2c_send_func_t I2C_SendFunc;       /*!< Function to send I2C data. */
    pca6416a_i2c_receive_func_t I2C_ReceiveFunc; /*!< Function to receive I2C data. */
} pca6416a_config_t;

/*! @brief PCA6416A driver handle. */
typedef struct _pca6416a_handle
{
    uint8_t i2cAddr;                             /*!< I2C address. */
    pca6416a_i2c_send_func_t I2C_SendFunc;       /*!< Function to send I2C data. */
    pca6416a_i2c_receive_func_t I2C_ReceiveFunc; /*!< Function to receive I2C data. */
} pca6416a_handle_t;

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
 * @brief Initializes the PCA6416A driver handle.
 *
 * @param handle Pointer to the PCA6416A handle.
 * @param config Pointer to the PCA6416A configuration structure.
 */
void PCA6416A_Init(pca6416a_handle_t *handle, const pca6416a_config_t *config);

/*!
 * @brief Set PCA6416A pins direction.
 *
 * This function sets multiple pins direction, the pins to modify are passed in
 * as a bit OR'ed value.
 *
 * For example, the following code set pin2 and pin3 to output:
 *
 * @code
   PCA6416A_SetDirection(handle, (1<<2) | (1<<3), pkPCA6416A_Output);
   @endcode
 *
 * @param handle Pointer to the PCA6416A handle.
 * @param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * @param dir Pin direction.
 * @return Return @ref kStatus_Success if successed, otherwise returns error code.
 */
status_t PCA6416A_SetDirection(pca6416a_handle_t *handle, uint16_t pins, pca6416a_dir_t dir);

/*!
 * @brief Inverse PCA6416A pins polarity.
 *
 * This function changes multiple pins polarity, the pins to modify are passed in
 * as a bit OR'ed value.
 *
 * For example, the following code set pin2 and pin3 to NOT inverse:
 *
 * @code
   PCA6416A_InversePolarity(handle, (1<<2) | (1<<3), false);
   @endcode
 *
 * @param handle Pointer to the PCA6416A handle.
 * @param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * @param inverse Use true to inverse, false to not inverse.
 * @return Return @ref kStatus_Success if successed, otherwise returns error code.
 */
status_t PCA6416A_InversePolarity(pca6416a_handle_t *handle, uint16_t pins, bool inverse);

/*!
 * @brief Read PCA6416A pins value.
 *
 * @param handle Pointer to the PCA6416A handle.
 * @param pinsValue Variable to save the read out pin values.
 * @return Return @ref kStatus_Success if successed, otherwise returns error code.
 */
status_t PCA6416A_ReadPins(pca6416a_handle_t *handle, uint16_t *pinsValue);

/*!
 * @brief Set PCA6416A pins output value to 1.
 *
 * This function changes multiple pins, the pins to modify are passed in as
 * a bit OR'ed value.
 *
 * For example, the following code set pin2 and pin3 output value to 1.
 *
 * @code
   PCA6416A_SetPins(handle, (1<<2) | (1<<3));
   @endcode
 *
 * @param handle Pointer to the PCA6416A handle.
 * @param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * @return Return @ref kStatus_Success if successed, otherwise returns error code.
 */
status_t PCA6416A_SetPins(pca6416a_handle_t *handle, uint16_t pins);

/*!
 * @brief Set PCA6416A pins output value to 0.
 *
 * This function changes multiple pins, the pins to modify are passed in as
 * a bit OR'ed value.
 *
 * For example, the following code set pin2 and pin3 output value to 0.
 *
 * @code
   PCA6416A_ClearPins(handle, (1<<2) | (1<<3));
   @endcode
 *
 * @param handle Pointer to the PCA6416A handle.
 * @param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * @return Return @ref kStatus_Success if successed, otherwise returns error code.
 */
status_t PCA6416A_ClearPins(pca6416a_handle_t *handle, uint16_t pins);

/*!
 * @brief Toggle PCA6416A pins output value.
 *
 * This function changes multiple pins, the pins to modify are passed in as
 * a bit OR'ed value.
 *
 * For example, the following code toggle pin2 and pin3 output value.
 *
 * @code
   PCA6416A_ClearPins(handle, (1<<2) | (1<<3));
   @endcode
 *
 * @param handle Pointer to the PCA6416A handle.
 * @param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * @return Return @ref kStatus_Success if successed, otherwise returns error code.
 */
status_t PCA6416A_TogglePins(pca6416a_handle_t *handle, uint16_t pins);

/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_PCA6416A_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
