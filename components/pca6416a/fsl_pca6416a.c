/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_pca6416a.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

typedef enum _pca6416a_reg_ops
{
    kPCA6416A_SetRegBits = 0,
    kPCA6416A_ClearRegBits,
    kPCA6416A_ToggleRegBits,
} pca6416a_reg_ops_t;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*! @brief Read port registers value. */
static status_t PCA6416A_ReadPort(pca6416a_handle_t *handle, uint8_t startReg, uint16_t *value)
{
    return handle->I2C_ReceiveFunc(handle->i2cAddr, startReg, 1U, (uint8_t *)value, 2U, 0U);
}

/*! @brief Write port registers value. */
static status_t PCA6416A_WritePort(pca6416a_handle_t *handle, uint8_t startReg, uint16_t value)
{
    return handle->I2C_SendFunc(handle->i2cAddr, startReg, 1U, (uint8_t *)&value, 2U, 0U);
}

/*! @brief Modify PCA6416A port register bits. */
static status_t PCA6416A_ModifyPortRegBits(pca6416a_handle_t *handle,
                                           uint8_t startReg,
                                           uint16_t bits,
                                           pca6416a_reg_ops_t ops)
{
    uint16_t regValue;
    status_t status;

    status = PCA6416A_ReadPort(handle, startReg, &regValue);

    if (kStatus_Success == status)
    {
        if (kPCA6416A_SetRegBits == ops)
        {
            regValue |= bits;
        }
        else if (kPCA6416A_ClearRegBits == ops)
        {
            regValue &= ~bits;
        }
        else if (kPCA6416A_ToggleRegBits == ops)
        {
            regValue ^= bits;
        }
        else
        {
            /* Add for MISRA 15.7 */
        }

        status = PCA6416A_WritePort(handle, startReg, regValue);
    }

    return status;
}

/*
 * brief Initializes the PCA6416A driver handle.
 *
 * param handle Pointer to the PCA6416A handle.
 * param config Pointer to the PCA6416A configuration structure.
 */
void PCA6416A_Init(pca6416a_handle_t *handle, const pca6416a_config_t *config)
{
    assert(NULL != handle);
    assert(NULL != config);

    handle->i2cAddr         = config->i2cAddr;
    handle->I2C_SendFunc    = config->I2C_SendFunc;
    handle->I2C_ReceiveFunc = config->I2C_ReceiveFunc;
}

/*
 * brief Set PCA6416A pins direction.
 *
 * This function sets multiple pins direction, the pins to modify are passed in
 * as a bit OR'ed value.
 *
 * For example, the following code set pin2 and pin3 to output:
 *
 * code
   PCA6416A_SetDirection(handle, (1<<2) | (1<<3), pkPCA6416A_Output);
   endcode
 *
 * param handle Pointer to the PCA6416A handle.
 * param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * param dir Pin direction.
 * return Return ref kStatus_Success if successed, otherwise returns error code.
 */
status_t PCA6416A_SetDirection(pca6416a_handle_t *handle, uint16_t pins, pca6416a_dir_t dir)
{
    return PCA6416A_ModifyPortRegBits(handle, PCA6416A_CFG_PORT_0, pins,
                                      (kPCA6416A_Input == dir) ? kPCA6416A_SetRegBits : kPCA6416A_ClearRegBits);
}

/*
 * brief Inverse PCA6416A pins polarity.
 *
 * This function changes multiple pins polarity, the pins to modify are passed in
 * as a bit OR'ed value.
 *
 * For example, the following code set pin2 and pin3 to NOT inverse:
 *
 * code
   PCA6416A_InversePolarity(handle, (1<<2) | (1<<3), false);
   endcode
 *
 * param handle Pointer to the PCA6416A handle.
 * param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * param inverse Use true to inverse, false to not inverse.
 * return Return ref kStatus_Success if successed, otherwise returns error code.
 */
status_t PCA6416A_InversePolarity(pca6416a_handle_t *handle, uint16_t pins, bool inverse)
{
    return PCA6416A_ModifyPortRegBits(handle, PCA6416A_POL_INV_PORT_0, pins,
                                      inverse ? kPCA6416A_SetRegBits : kPCA6416A_ClearRegBits);
}

/*
 * brief Read PCA6416A pins value.
 *
 * param handle Pointer to the PCA6416A handle.
 * param pinsValue Variable to save the read out pin values.
 * return Return ref kStatus_Success if successed, otherwise returns error code.
 */
status_t PCA6416A_ReadPins(pca6416a_handle_t *handle, uint16_t *pinsValue)
{
    return PCA6416A_ReadPort(handle, PCA6416A_INPUT_PORT_0, pinsValue);
}

/*
 * brief Set PCA6416A pins output value to 1.
 *
 * This function changes multiple pins, the pins to modify are passed in as
 * a bit OR'ed value.
 *
 * For example, the following code set pin2 and pin3 output value to 1.
 *
 * code
   PCA6416A_SetPins(handle, (1<<2) | (1<<3));
   endcode
 *
 * param handle Pointer to the PCA6416A handle.
 * param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * return Return ref kStatus_Success if successed, otherwise returns error code.
 */
status_t PCA6416A_SetPins(pca6416a_handle_t *handle, uint16_t pins)
{
    return PCA6416A_ModifyPortRegBits(handle, PCA6416A_OUTPUT_PORT_0, pins, kPCA6416A_SetRegBits);
}

/*
 * brief Set PCA6416A pins output value to 0.
 *
 * This function changes multiple pins, the pins to modify are passed in as
 * a bit OR'ed value.
 *
 * For example, the following code set pin2 and pin3 output value to 0.
 *
 * code
   PCA6416A_ClearPins(handle, (1<<2) | (1<<3));
   endcode
 *
 * param handle Pointer to the PCA6416A handle.
 * param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * return Return ref kStatus_Success if successed, otherwise returns error code.
 */
status_t PCA6416A_ClearPins(pca6416a_handle_t *handle, uint16_t pins)
{
    return PCA6416A_ModifyPortRegBits(handle, PCA6416A_OUTPUT_PORT_0, pins, kPCA6416A_ClearRegBits);
}

/*
 * brief Toggle PCA6416A pins output value.
 *
 * This function changes multiple pins, the pins to modify are passed in as
 * a bit OR'ed value.
 *
 * For example, the following code toggle pin2 and pin3 output value.
 *
 * code
   PCA6416A_ClearPins(handle, (1<<2) | (1<<3));
   endcode
 *
 * param handle Pointer to the PCA6416A handle.
 * param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * return Return ref kStatus_Success if successed, otherwise returns error code.
 */
status_t PCA6416A_TogglePins(pca6416a_handle_t *handle, uint16_t pins)
{
    return PCA6416A_ModifyPortRegBits(handle, PCA6416A_OUTPUT_PORT_0, pins, kPCA6416A_ToggleRegBits);
}
