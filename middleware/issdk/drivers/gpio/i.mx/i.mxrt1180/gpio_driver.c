/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
* @file gpio_driver.c
* @brief The gpio_driver.c file contains Generic API Adaption to i.MXRT1180 SDK 2.x GPIO Driver.
*/
#if 1
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
static gpioIsrObj_t isrObj[TOTAL_NUMBER_PORT][GPIO_NUMBER_OF_PIN];
static gpioConfigiMXSDK_t gpioConfigDefault = {
    .pinConfig = {kRGPIO_DigitalInput, 0}, .interruptMode = kRGPIO_InterruptRisingEdge};

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

    pGpioConfig->pinConfig.pinDirection = dir == GPIO_DIRECTION_IN ? kRGPIO_DigitalInput : kRGPIO_DigitalOutput;
    /* Set the pin information */
    RGPIO_PinInit(pinHandle->base, pinHandle->pinNumber, &pGpioConfig->pinConfig);

    /* Isr is installed */
    if (aIsrHandler)
    {
        RGPIO_SetPinInterruptConfig(pinHandle->base, pinHandle->pinNumber, kRGPIO_InterruptOutput0, pGpioConfig->interruptMode);
        /* Enable the IRQ */
        EnableIRQ(pinHandle->irq);
        isrObj[pinHandle->portNumber][pinHandle->pinNumber].isrHandle = aIsrHandler;
        isrObj[pinHandle->portNumber][pinHandle->pinNumber].pUserData = apUserData;
        /* Enable GPIO pin interrupt */
        //RGPIO_PortEnableInterrupts(pinHandle->base, pinHandle->mask);
    }
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
    RGPIO_PinWrite(pinHandle->base, pinHandle->pinNumber, PIN_SET);
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
    RGPIO_PinWrite(pinHandle->base, pinHandle->pinNumber, PIN_CLR);
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

/***********************************************************************
 *
 * Function Name : imxsdk_gpio_write_pin
 * Description   : Set output level of individual GPIO pin to desired value, ie 1 or 0.
 *
 ***************************************************************************/
void imxsdk_gpio_write_pin(pinID_t aPinId, uint8_t aValue)
{
    gpioHandleiMXSDK_t *pinHandle = (gpioHandleiMXSDK_t *)aPinId;
    RGPIO_WritePinOutput(pinHandle->base, pinHandle->pinNumber, aValue);
}

/***********************************************************************
 *
 * Function Name : imxsdk_gpio_read_pin
 * Description   : Read current input value of individual GPIO pin.
 *
 ***************************************************************************/
uint32_t imxsdk_gpio_read_pin(pinID_t aPinId)
{
    gpioHandleiMXSDK_t *pinHandle = (gpioHandleiMXSDK_t *)aPinId;
    return RGPIO_ReadPinInput(pinHandle->base, pinHandle->pinNumber);
}

/***********************************************************************
 *
 * Function Name : imxsdk_gpio_handle_interrupt
 * Description   : handle the gpio interrupt in a pin.
 *
 ***************************************************************************/
void imxsdk_gpio_handle_interrupt(RGPIO_Type *apBase, port_number_t gpioPortNumber)
{
    uint32_t isfr = RGPIO_GetPinsInterruptFlags(apBase, kRGPIO_InterruptOutput0);

    /* Parse through all the pending interrupt for a PORT */
    for (uint8_t i = 0; i < GPIO_NUMBER_OF_PIN; i++)
    {
        if (isfr & (1 << i))
        {
            gpio_isr_handler_t handle = isrObj[gpioPortNumber][i].isrHandle;
            if (handle == NULL)
            {
                continue;
            }
            /* Call user defined handler */
            handle(isrObj[gpioPortNumber][i].pUserData);
            RGPIO_ClearPinsInterruptFlags(apBase, kRGPIO_InterruptOutput0, (1 << i));
        }
    }
}

GENERIC_DRIVER_GPIO Driver_GPIO_KSDK = {
    imxsdk_gpio_get_version, imxsdk_gpio_pin_init,  imxsdk_gpio_set_pin,  imxsdk_gpio_clr_pin,
    imxsdk_gpio_toggle_pin ,imxsdk_gpio_write_pin, imxsdk_gpio_read_pin
};
#endif