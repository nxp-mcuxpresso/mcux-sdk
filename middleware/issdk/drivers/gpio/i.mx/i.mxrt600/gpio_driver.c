/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
* @file gpio_driver.c
* @brief The gpio_driver.c file contains Generic API Adaption to i.MXRT1050 SDK 2.0 GPIO Driver.
*/

#include "gpio_driver.h"

/*******************************************************************************
* Definitions
******************************************************************************/
#define GPIO_DRV_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(2, 3) /* driver version */
// ISR handler array for each gpio pin in the system
#define GPIO_NUMBER_OF_PIN 0x20

/*******************************************************************************
* Variables
******************************************************************************/

/* Driver Version */
static const GENERIC_DRIVER_VERSION DriverVersion = {GPIO_API_VERSION, GPIO_DRV_VERSION};
//static gpioIsrObj_t isrObj[TOTAL_NUMBER_PORT][GPIO_NUMBER_OF_PIN];
static gpioConfigiMXSDK_t gpioConfigDefault = {
    .pinConfig = {kGPIO_DigitalInput, 0},
    .interruptMode = {kGPIO_PinIntEnableEdge, kGPIO_PinIntEnableLowOrFall}
};

/*******************************************************************************
 * Code
 ******************************************************************************/

/***********************************************************************
 *
 * Function Name : imxsdk_gpio_get_version
 * Description   : get the i.MXRT1050RT gpio driver version.
 *
 ***************************************************************************/
GENERIC_DRIVER_VERSION imxsdk_gpio_get_version(void)
{
    return DriverVersion;
}

/***********************************************************************
 *
 * Function Name : imxsdk_gpio_pin_init
 * Description   : Initialize particular GPIO pin used by board.
 *
 ***************************************************************************/
void imxsdk_gpio_pin_init(
    pinID_t aPinId, gpio_direction_t dir, void *apPinConfig, gpio_isr_handler_t aIsrHandler, void *apUserData)
{
    gpioConfigiMXSDK_t *pGpioConfig = (gpioConfigiMXSDK_t *)apPinConfig;
    gpioHandleiMXSDK_t *pinHandle = (gpioHandleiMXSDK_t *)aPinId;
    if (NULL == apPinConfig)
    {
        pGpioConfig = &gpioConfigDefault;
    }

    pGpioConfig->pinConfig.pinDirection = dir == GPIO_DIRECTION_IN ? kGPIO_DigitalInput : kGPIO_DigitalOutput;
    /* Set the pin information */
    GPIO_PinInit(pinHandle->base, pinHandle->portNumber, pinHandle->pinNumber, &pGpioConfig->pinConfig);

    /* Isr is installed */
//    if (aIsrHandler)
//    {
//        /* Enable the IRQ */
//        EnableIRQ(pinHandle->irq);
//        isrObj[pinHandle->portNumber][pinHandle->pinNumber].isrHandle = aIsrHandler;
//        isrObj[pinHandle->portNumber][pinHandle->pinNumber].pUserData = apUserData;
//        /* Enable GPIO pin interrupt */
//        GPIO_PortEnableInterrupts(pinHandle->base, pinHandle->portNumber, pinHandle->irq, pinHandle->mask);
//    }
}

/***********************************************************************
 *
 * Function Name : imxsdk_gpio_set_pin
 * Description   : Set output level of individual GPIO pin to logic 1.
 *
 ***************************************************************************/
void imxsdk_gpio_set_pin(pinID_t aPinId)
{
    gpioHandleiMXSDK_t *pinHandle = (gpioHandleiMXSDK_t *)aPinId;
    pinHandle->pinStatus = PIN_SET;
    GPIO_PinWrite(pinHandle->base, pinHandle->portNumber, pinHandle->pinNumber, PIN_SET);
}

/***********************************************************************
 *
 * Function Name : imxsdk_gpio_clr_pin
 * Description   : Set output level of individual GPIO pin to logic 0..
 *
 ***************************************************************************/
void imxsdk_gpio_clr_pin(pinID_t aPinId)
{
    gpioHandleiMXSDK_t *pinHandle = (gpioHandleiMXSDK_t *)aPinId;
    pinHandle->pinStatus = PIN_CLR;
    GPIO_PinWrite(pinHandle->base, pinHandle->portNumber, pinHandle->pinNumber, PIN_CLR);
}

/***********************************************************************
 *
 * Function Name : ksdk_gpio_toggle_pin
 * Description   : toggle the currrent output logic of individual GPIO pin.
 *
 ***************************************************************************/
void imxsdk_gpio_toggle_pin(pinID_t aPinId)
{
    gpioHandleiMXSDK_t *pinHandle = (gpioHandleiMXSDK_t *)aPinId;

    /* Check PIN Status and toggle */
    if (PIN_CLR == pinHandle->pinStatus)
    {
		imxsdk_gpio_set_pin(aPinId);
	}
    else if (PIN_SET == pinHandle->pinStatus)
	{
	    imxsdk_gpio_clr_pin(aPinId);
	}
}

GENERIC_DRIVER_GPIO Driver_GPIO_KSDK = {
    imxsdk_gpio_get_version, imxsdk_gpio_pin_init,  imxsdk_gpio_set_pin,
    imxsdk_gpio_clr_pin, imxsdk_gpio_toggle_pin
};
