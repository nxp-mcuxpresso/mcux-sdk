/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file gpio_driver.h
 * @brief The gpio_driver.h file containes the Generic Irq implmentation for the gpio.
*/

#ifndef __DRIVER_GPIO_H__
#define __DRIVER_GPIO_H__

#include "Driver_Common.h"
#include "Driver_GPIO.h"
#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_port.h"

/**
\brief GPIO PORT NAMES.
*/
typedef enum port_number
{
    PORTA_NUM = 0,
    PORTB_NUM = 1,
    PORTC_NUM = 2,
    PORTD_NUM = 3,
    PORTE_NUM = 4,
    TOTAL_NUMBER_PORT
} port_number_t;

/*!
 * @brief The GPIO Configuration KSDK.
 */
typedef struct gpioConfigKSDK
{
    gpio_pin_config_t pinConfig;     /*!< General pin charactertics.*/
    port_pin_config_t portPinConfig; /*!< port pin configuration.*/
    port_interrupt_t interruptMode;  /*!< Interrupt mode for a pin.*/
} gpioConfigKSDK_t;

/*!
 * @brief The GPIO pin handle for KSDK.
 */
typedef struct gpioHandleKSDK
{
    GPIO_Type *base;           /*!< Base address of the GPIO Port.*/
    PORT_Type *portBase;       /*!< Base address of the GPIO Port.*/
    uint32_t pinNumber;        /*!< pin number start from 0 -31.*/
    uint32_t mask;             /*!< mask value for a pin.*/
    IRQn_Type irq;             /*!< IRQ Number for the port.*/
    clock_ip_name_t clockName; /*!< Clock Name for the port.*/
    port_number_t portNumber;  /*!< Port Number for the port.*/
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
#define MAKE_GPIO_HANDLE(PortName, Base, PortBase, PinNumber, Irq, ClockName, PortNumber) \
    static gpioHandleKSDK_t PortName##PinNumber = {.base = Base,                          \
                                                   .portBase = PortBase,                  \
                                                   .pinNumber = PinNumber,                \
                                                   .mask = 1 << (PinNumber),              \
                                                   .irq = Irq,                            \
                                                   .clockName = ClockName,                \
                                                   .portNumber = PortNumber};

#define GPIO_PIN_ID(PortName, PinNumber) &(PortName##PinNumber)
extern GENERIC_DRIVER_GPIO Driver_GPIO_KSDK;

#endif // __DRIVER_GPIO_H__
