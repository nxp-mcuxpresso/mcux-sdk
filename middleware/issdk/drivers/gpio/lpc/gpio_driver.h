/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file gpio_driver.h
 * @brief The gpio_driver.h file containes the Generic Irq implmentation for the gpio.
 *        The type and variable names have been kept aligned to Kinetis family for compatibility of examples.
*/

#ifndef __DRIVER_GPIO_H__
#define __DRIVER_GPIO_H__

#include "Driver_Common.h"
#include "Driver_GPIO.h"
#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_gint.h"

typedef enum _gint_interrupt
{
    kGINT_InterruptLogic_0 = 0x0U, /*!< Interrupt on Logic 0 (Falling Edge or Level Low). */
    kGINT_InterruptLogic_1 = 0x1U, /*!< Interrupt on Logic 1 (Rising Edge or Level High). */
} gint_interrupt_t;

/*!
 * @brief The GPIO Configuration KSDK.
 */
typedef struct gpioConfigKSDK
{
    gpio_pin_config_t pinConfig;         /*!< General pin charactertics.*/
    gint_trig_t       interruptMode;     /*!< Interrupt mode for a pin.*/
    gint_interrupt_t  interruptPolarity; /*!< Interrupt Polarity 0/1 for a pin.*/
} gpioConfigKSDK_t;

/*!
 * @brief The GPIO pin handle for KSDK.
 */
typedef struct gpioHandleKSDK
{
    GPIO_Type *base;           /*!< Base address of the GPIO Port.*/
    uint32_t pinNumber;        /*!< pin number start from 0 -31.*/
    uint32_t mask;             /*!< mask value for a pin.*/
    clock_ip_name_t clockName; /*!< Clock Name for the port.*/
    gint_port_t portNumber;    /*!< Port Number for the port.*/
} gpioHandleKSDK_t;

/*!
 * @brief The gpio isr object.
 */
typedef struct gpioIsrObj
{
    void *pUserData;              /*!< Pointer to a UserData.*/
    gpio_isr_handler_t isrHandle; /*!< pointer to isrHandle.*/
} gpioIsrObj_t;

/*!
 * @brief Macro to create a Gpio handle
 */
#define MAKE_GPIO_HANDLE(PortName, Base, PinNumber, ClockName, PortNumber)   \
    static gpioHandleKSDK_t PortName##PinNumber = {.base = Base,             \
                                                   .pinNumber = PinNumber,   \
                                                   .mask = 1 << (PinNumber), \
                                                   .clockName = ClockName,   \
                                                   .portNumber = PortNumber};

#define GPIO_PIN_ID(PortName, PinNumber) &(PortName##PinNumber)
extern GENERIC_DRIVER_GPIO Driver_GPIO_KSDK;

#endif // __DRIVER_GPIO_H__
