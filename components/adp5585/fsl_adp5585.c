/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_adp5585.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

typedef enum _adp5585_reg_ops
{
    kADP5585_SetRegBits = 0,
    kADP5585_ClearRegBits,
    kADP5585_ToggleRegBits,
} adp5585_reg_ops_t;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*! @brief Read port registers value. */
static status_t ADP5585_ReadPort(adp5585_handle_t *handle, uint8_t startReg, uint16_t *value)
{
    return handle->I2C_ReceiveFunc(handle->i2cAddr, startReg, 1U, (uint8_t *)value, 2U, 0U);
}

/*! @brief Write port registers value. */
static status_t ADP5585_WritePort(adp5585_handle_t *handle, uint8_t startReg, uint16_t value)
{
    return handle->I2C_SendFunc(handle->i2cAddr, startReg, 1U, (uint8_t *)&value, 2U, 0U);
}

/*! @brief Modify ADP5585 port register bits. */
static status_t ADP5585_ModifyPortRegBits(adp5585_handle_t *handle,
                                          uint8_t startReg,
                                          uint16_t bits,
                                          adp5585_reg_ops_t ops)
{
    uint16_t regValue;
    status_t status;

    status = ADP5585_ReadPort(handle, startReg, &regValue);

    if (kStatus_Success == status)
    {
        if (kADP5585_SetRegBits == ops)
        {
            regValue |= bits;
        }
        else if (kADP5585_ClearRegBits == ops)
        {
            regValue &= ~bits;
        }
        else if (kADP5585_ToggleRegBits == ops)
        {
            regValue ^= bits;
        }
        else
        {
            /* Add for MISRA 15.7 */
        }

        status = ADP5585_WritePort(handle, startReg, regValue);
    }

    return status;
}

/*
 * brief Initializes the ADP5585 driver handle.
 *
 * param handle Pointer to the ADP5585 handle.
 * param config Pointer to the ADP5585 configuration structure.
 */
void ADP5585_Init(adp5585_handle_t *handle, const adp5585_config_t *config)
{
    assert(NULL != handle);
    assert(NULL != config);

    handle->i2cAddr         = config->i2cAddr;
    handle->I2C_SendFunc    = config->I2C_SendFunc;
    handle->I2C_ReceiveFunc = config->I2C_ReceiveFunc;
}

/*
 * brief Set ADP5585 pins direction.
 *
 * This function sets multiple pins direction, the pins to modify are passed in
 * as a bit OR'ed value.
 *
 * For example, the following code set pin2 and pin3 to output:
 *
 * code
   ADP5585_SetDirection(handle, (1<<2) | (1<<3), pkADP5585_Output);
   endcode
 *
 * param handle Pointer to the ADP5585 handle.
 * param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * param dir Pin direction.
 * return Return ref kStatus_Success if successed, otherwise returns error code.
 */
status_t ADP5585_SetDirection(adp5585_handle_t *handle, uint16_t pins, adp5585_dir_t dir)
{
    return ADP5585_ModifyPortRegBits(handle, ADP5585_GPIO_DIRECTION_A, pins,
                                     (kADP5585_Output == dir) ? kADP5585_SetRegBits : kADP5585_ClearRegBits);
}

/*
 * brief Set ADP5585 pins output value to 1.
 *
 * This function changes multiple pins, the pins to modify are passed in as
 * a bit OR'ed value.
 *
 * For example, the following code set pin2 and pin3 output value to 1.
 *
 * code
   ADP5585_SetPins(handle, (1<<2) | (1<<3));
   endcode
 *
 * param handle Pointer to the ADP5585 handle.
 * param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * return Return ref kStatus_Success if successed, otherwise returns error code.
 */
status_t ADP5585_SetPins(adp5585_handle_t *handle, uint16_t pins)
{
    return ADP5585_ModifyPortRegBits(handle, ADP5585_GPO_DATA_OUT_A, pins, kADP5585_SetRegBits);
}

/*
 * brief Set ADP5585 pins output value to 0.
 *
 * This function changes multiple pins, the pins to modify are passed in as
 * a bit OR'ed value.
 *
 * For example, the following code set pin2 and pin3 output value to 0.
 *
 * code
   ADP5585_ClearPins(handle, (1<<2) | (1<<3));
   endcode
 *
 * param handle Pointer to the ADP5585 handle.
 * param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * return Return ref kStatus_Success if successed, otherwise returns error code.
 */
status_t ADP5585_ClearPins(adp5585_handle_t *handle, uint16_t pins)
{
    return ADP5585_ModifyPortRegBits(handle, ADP5585_GPO_DATA_OUT_A, pins, kADP5585_ClearRegBits);
}

/*
 * brief Toggle ADP5585 pins output value.
 *
 * This function changes multiple pins, the pins to modify are passed in as
 * a bit OR'ed value.
 *
 * For example, the following code toggle pin2 and pin3 output value.
 *
 * code
   ADP5585_TogglePins(handle, (1<<2) | (1<<3));
   endcode
 *
 * param handle Pointer to the ADP5585 handle.
 * param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * return Return ref kStatus_Success if successed, otherwise returns error code.
 */
status_t ADP5585_TogglePins(adp5585_handle_t *handle, uint16_t pins)
{
    return ADP5585_ModifyPortRegBits(handle, ADP5585_GPO_DATA_OUT_A, pins, kADP5585_ToggleRegBits);
}
