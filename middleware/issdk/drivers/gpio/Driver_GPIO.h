/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __DRIVER_GPIO_H
#define __DRIVER_GPIO_H

#include "Driver_Common.h"

#define GPIO_API_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(2, 0) /* API version */

/**
 * @file Driver_GPIO.h
* @brief  The Driver_GPIO.h file contains the definitions for GPIO Driver direction.
*/

typedef enum gpio_direction_en
{
    GPIO_DIRECTION_IN = 0U,  /*!< IN. */
    GPIO_DIRECTION_OUT = 1U, /*!< OUT. */
} gpio_direction_t;

/**
\brief GPIO Driver direction.
*/
typedef void *pinID_t;

typedef ARM_DRIVER_VERSION GENERIC_DRIVER_VERSION;

typedef void (*gpio_isr_handler_t)(void *apUserData);
/**
\brief Access structure of the GPIO Driver.
*/
typedef struct GENERIC_DRIVER_GPIO
{
    GENERIC_DRIVER_VERSION (*GetVersion)(void); /*!< Pointer to get driver version.*/
    void (*pin_init)(pinID_t aPinId,
                     gpio_direction_t dir,
                     void *apPinConfig,
                     gpio_isr_handler_t aIsrHandler,
                     void *apUserData);                /*!< Pointer to Initialize gpio Interface.*/
    void (*set_pin)(pinID_t aPinId);                   /*!< Pointer to set the pin.*/
    void (*clr_pin)(pinID_t aPinId);                   /*!< Pointer to clear the pin.*/
    void (*toggle_pin)(pinID_t aPinId);                /*!< Pointer to toggle the pin.*/
    void (*write_pin)(pinID_t aPinId, uint8_t aValue); /*!<< read the pin value.*/
    uint32_t (*read_pin)(pinID_t aPinId);              /*!<< read the pin value.*/
} const GENERIC_DRIVER_GPIO;

#endif /* __DRIVER_GPIO_H */
