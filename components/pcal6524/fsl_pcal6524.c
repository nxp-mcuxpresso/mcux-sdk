/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_pcal6524.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

typedef enum _pcal6524_reg_ops
{
    kPCAL6524_SetRegBits = 0,
    kPCAL6524_ClearRegBits,
    kPCAL6524_ToggleRegBits,
} pcal6524_reg_ops_t;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*! @brief Read port registers value. */
static status_t PCAL6524_ReadPort(pcal6524_handle_t *handle, uint8_t startReg, uint32_t *value)
{
    return handle->I2C_ReceiveFunc(handle->i2cAddr, startReg, 1U, (uint8_t *)value, 3U, 0U);
}

/*! @brief Write port registers value. */
static status_t PCAL6524_WritePort(pcal6524_handle_t *handle, uint8_t startReg, uint32_t value)
{
    return handle->I2C_SendFunc(handle->i2cAddr, startReg, 1U, (uint8_t *)&value, 3U, 0U);
}

/*! @brief Modify PCAL6524 port register bits. */
static status_t PCAL6524_ModifyPortRegBits(pcal6524_handle_t *handle,
                                           uint8_t startReg,
                                           uint32_t bits,
                                           pcal6524_reg_ops_t ops)
{
    uint32_t regValue;
    status_t status;

    status = PCAL6524_ReadPort(handle, startReg, &regValue);

    if (kStatus_Success == status)
    {
        if (kPCAL6524_SetRegBits == ops)
        {
            regValue |= bits;
        }
        else if (kPCAL6524_ClearRegBits == ops)
        {
            regValue &= ~bits;
        }
        else if (kPCAL6524_ToggleRegBits == ops)
        {
            regValue ^= bits;
        }
        else
        {
            /* Add for MISRA 15.7 */
        }

        status = PCAL6524_WritePort(handle, startReg, regValue);
    }

    return status;
}

/*
 * brief Initializes the PCAL6524 driver handle.
 *
 * param handle Pointer to the PCAL6524 handle.
 * param config Pointer to the PCAL6524 configuration structure.
 */
void PCAL6524_Init(pcal6524_handle_t *handle, const pcal6524_config_t *config)
{
    assert(NULL != handle);
    assert(NULL != config);

    handle->i2cAddr         = config->i2cAddr;
    handle->I2C_SendFunc    = config->I2C_SendFunc;
    handle->I2C_ReceiveFunc = config->I2C_ReceiveFunc;
}

/*
 * brief Set PCAL6524 pins direction.
 *
 * This function sets multiple pins direction, the pins to modify are passed in
 * as a bit OR'ed value.
 *
 * For example, the following code set pin2 and pin3 to output:
 *
 * code
   PCAL6524_SetDirection(handle, (1<<2) | (1<<3), pkPCAL6524_Output);
   endcode
 *
 * param handle Pointer to the PCAL6524 handle.
 * param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * param dir Pin direction.
 * return Return ref kStatus_Success if successed, otherwise returns error code.
 */
status_t PCAL6524_SetDirection(pcal6524_handle_t *handle, uint32_t pins, pcal6524_dir_t dir)
{
    return PCAL6524_ModifyPortRegBits(handle, PCAL6524_CONFIG_PORT0, pins,
                                      (kPCAL6524_Output != dir) ? kPCAL6524_SetRegBits : kPCAL6524_ClearRegBits);
}

/*
 * brief Set PCAL6524 pins output value to 1.
 *
 * This function changes multiple pins, the pins to modify are passed in as
 * a bit OR'ed value.
 *
 * For example, the following code set pin2 and pin3 output value to 1.
 *
 * code
   PCAL6524_SetPins(handle, (1<<2) | (1<<3));
   endcode
 *
 * param handle Pointer to the PCAL6524 handle.
 * param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * return Return ref kStatus_Success if successed, otherwise returns error code.
 */
status_t PCAL6524_SetPins(pcal6524_handle_t *handle, uint32_t pins)
{
    return PCAL6524_ModifyPortRegBits(handle, PCAL6524_OUTPUT_PORT0, pins, kPCAL6524_SetRegBits);
}

/*
 * brief Set PCAL6524 pins output value to 0.
 *
 * This function changes multiple pins, the pins to modify are passed in as
 * a bit OR'ed value.
 *
 * For example, the following code set pin2 and pin3 output value to 0.
 *
 * code
   PCAL6524_ClearPins(handle, (1<<2) | (1<<3));
   endcode
 *
 * param handle Pointer to the PCAL6524 handle.
 * param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * return Return ref kStatus_Success if successed, otherwise returns error code.
 */
status_t PCAL6524_ClearPins(pcal6524_handle_t *handle, uint32_t pins)
{
    return PCAL6524_ModifyPortRegBits(handle, PCAL6524_OUTPUT_PORT0, pins, kPCAL6524_ClearRegBits);
}

/*
 * brief Toggle PCAL6524 pins output value.
 *
 * This function changes multiple pins, the pins to modify are passed in as
 * a bit OR'ed value.
 *
 * For example, the following code toggle pin2 and pin3 output value.
 *
 * code
   PCAL6524_TogglePins(handle, (1<<2) | (1<<3));
   endcode
 *
 * param handle Pointer to the PCAL6524 handle.
 * param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * return Return ref kStatus_Success if successed, otherwise returns error code.
 */
status_t PCAL6524_TogglePins(pcal6524_handle_t *handle, uint32_t pins)
{
    return PCAL6524_ModifyPortRegBits(handle, PCAL6524_OUTPUT_PORT0, pins, kPCAL6524_ToggleRegBits);
}
