/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
* @file gpio_driver.c
* @brief The gpio_driver.c file contains Generic API Adaption to SDK 2.0 GPIO Driver.
*        The type and variable names have been kept aligned to Kinetis family for compatibility of examples.
*/

#include "gpio_driver.h"

/*******************************************************************************
* Definitions
******************************************************************************/
#define GPIO_DRV_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(2, 2) /* driver version */
#define GINT_COUNT (sizeof(gintBases) / sizeof(void *))       /* Number of GINTs*/
#define GINT_NUMBER_OF_PIN 32                                 /* Each Port has 32 Pins */

/*******************************************************************************
* Prototypes
******************************************************************************/
GINT_Type *const gintBases[] = GINT_BASE_PTRS;
#if defined(GINT0)
extern void PORT0_IRQHandler(void);
#endif
#if defined(GINT1)
extern void PORT1_IRQHandler(void);
#endif
#if defined(GINT2)
extern void PORT2_IRQHandler(void);
#endif
#if defined(GINT3)
extern void PORT3_IRQHandler(void);
#endif
#if defined(GINT4)
extern void PORT4_IRQHandler(void);
#endif
#if defined(GINT5)
extern void PORT5_IRQHandler(void);
#endif
#if defined(GINT6)
extern void PORT6_IRQHandler(void);
#endif
#if defined(GINT7)
extern void PORT7_IRQHandler(void);
#endif

/*******************************************************************************
* Variables
******************************************************************************/

/* Driver Version */
static const GENERIC_DRIVER_VERSION DriverVersion = {GPIO_API_VERSION, GPIO_DRV_VERSION};
/* ISR handler array for each gpio pin in the system */
static gpioIsrObj_t isrObj[GINT_COUNT][GINT_NUMBER_OF_PIN];
/* GPIO Pin characteristic */
static gpioConfigKSDK_t gpioConfigDefault = {
    .pinConfig = {kGPIO_DigitalInput, 0}, .interruptMode = kGINT_TrigEdge, .interruptPolarity = kGINT_InterruptLogic_1,
};
/* GINT base specific ISR callback list */
static gint_cb_t gintIsrCb[GINT_COUNT] = {
#if defined(GINT0)
    PORT0_IRQHandler,
#endif
#if defined(GINT1)
    PORT1_IRQHandler,
#endif
#if defined(GINT2)
    PORT2_IRQHandler,
#endif
#if defined(GINT3)
    PORT3_IRQHandler,
#endif
#if defined(GINT4)
    PORT4_IRQHandler,
#endif
#if defined(GINT5)
    PORT5_IRQHandler,
#endif
#if defined(GINT6)
    PORT6_IRQHandler,
#endif
#if defined(GINT7)
    PORT7_IRQHandler,
#endif
};

/*******************************************************************************
 * Code
 ******************************************************************************/

/***********************************************************************
 *
 * Function Name : ksdk_gpio_get_version
 * Description   : get the driver version.
 *
 ***************************************************************************/
GENERIC_DRIVER_VERSION ksdk_gpio_get_version(void)
{
    return DriverVersion;
}

/***********************************************************************
 *
 * Function Name : ksdk_gpio_pin_init
 * Description   : Initialize particular GPIO pin used by board.
 *
 ***************************************************************************/
void ksdk_gpio_pin_init(
    pinID_t aPinId, gpio_direction_t dir, void *apPinConfig, gpio_isr_handler_t aIsrHandler, void *apUserData)
{
    uint32_t polarityMask, enableMask;

    gpioConfigKSDK_t *pGpioConfig;
    gpioHandleKSDK_t *pinHandle = (gpioHandleKSDK_t *)aPinId;
    if (NULL == apPinConfig)
    {
        pGpioConfig = &gpioConfigDefault;
    }
    else
    {
        pGpioConfig = (gpioConfigKSDK_t *)apPinConfig;
    }

    // Configure as GPIO
    CLOCK_EnableClock(pinHandle->clockName);
    pGpioConfig->pinConfig.pinDirection = (dir == GPIO_DIRECTION_IN) ? kGPIO_DigitalInput : kGPIO_DigitalOutput;
    GPIO_PinInit(pinHandle->base, pinHandle->portNumber, pinHandle->pinNumber, &pGpioConfig->pinConfig);

    // Configure is GINT if ISR requested (There should be as many GINTs as there are GPIO Ports).
    if (aIsrHandler && pinHandle->portNumber < GINT_COUNT)
    {
        /* Initialize GINT device for the associated Port */
        GINT_Init(gintBases[pinHandle->portNumber]);

        // Enable the IRQ
        isrObj[pinHandle->portNumber][pinHandle->pinNumber].isrHandle = aIsrHandler;
        isrObj[pinHandle->portNumber][pinHandle->pinNumber].pUserData = apUserData;

        /* Setup GINT trigger mode and "OR" mode */
        GINT_SetCtrl(gintBases[pinHandle->portNumber], kGINT_CombineOr, pGpioConfig->interruptMode,
                     gintIsrCb[pinHandle->portNumber]);

        /* Get current pins & polarity for GINT */
        GINT_GetConfigPins(gintBases[pinHandle->portNumber], pinHandle->portNumber, &polarityMask, &enableMask);

        /* Update Polarity for this PIN */
        if (pGpioConfig->interruptPolarity == kGINT_InterruptLogic_1)
        {
            polarityMask |= pinHandle->mask; /* Logic 1 for : Level High or Rising Edge  */
        }
        else
        {
            polarityMask &= ~(pinHandle->mask); /* Logic 0 for : Level Low or Falling Edge */
        }
        enableMask |= pinHandle->mask;

        /* Select pins & polarity for GINT */
        GINT_ConfigPins(gintBases[pinHandle->portNumber], pinHandle->portNumber, polarityMask, enableMask);

        /* Enable callbacks for GINT */
        GINT_EnableCallback(gintBases[pinHandle->portNumber]);
    }
}

/***********************************************************************
 *
 * Function Name : ksdk_gpio_set_pin
 * Description   : Set output level of individual GPIO pin to logic 1.
 *
 ***************************************************************************/
void ksdk_gpio_set_pin(pinID_t aPinId)
{
    gpioHandleKSDK_t *pinHandle = (gpioHandleKSDK_t *)aPinId;
    GPIO_PortSet(pinHandle->base, pinHandle->portNumber, pinHandle->mask);
}

/***********************************************************************
 *
 * Function Name : ksdk_gpio_clr_pin
 * Description   : Set output level of individual GPIO pin to logic 0..
 *
 ***************************************************************************/
void ksdk_gpio_clr_pin(pinID_t aPinId)
{
    gpioHandleKSDK_t *pinHandle = (gpioHandleKSDK_t *)aPinId;
    GPIO_PortClear(pinHandle->base, pinHandle->portNumber, pinHandle->mask);
}

/***********************************************************************
 *
 * Function Name : ksdk_gpio_toggle_pin
 * Description   : toggle the currrent output logic of individual GPIO pin.
 *
 ***************************************************************************/
void ksdk_gpio_toggle_pin(pinID_t aPinId)
{
    gpioHandleKSDK_t *pinHandle = (gpioHandleKSDK_t *)aPinId;
    GPIO_PortToggle(pinHandle->base, pinHandle->portNumber, pinHandle->mask);
}

/***********************************************************************
 *
 * Function Name : ksdk_gpio_write_pin
 * Description   : Set output level of individual GPIO pin to desired value, ie 1 or 0.
 *
 ***************************************************************************/
void ksdk_gpio_write_pin(pinID_t aPinId, uint8_t aValue)
{
    gpioHandleKSDK_t *pinHandle = (gpioHandleKSDK_t *)aPinId;
    GPIO_PinWrite(pinHandle->base, pinHandle->portNumber, pinHandle->pinNumber, aValue);
}

/***********************************************************************
 *
 * Function Name : ksdk_gpio_read_pin
 * Description   : Read current input value of individual GPIO pin.
 *
 ***************************************************************************/
uint32_t ksdk_gpio_read_pin(pinID_t aPinId)
{
    gpioHandleKSDK_t *pinHandle = (gpioHandleKSDK_t *)aPinId;
    return GPIO_PinRead(pinHandle->base, pinHandle->portNumber, pinHandle->pinNumber);
}

/***********************************************************************
 *
 * Function Name : ksdk_gpio_handle_interrupt
 * Description   : handle the gint interrupt of a port.
 *
 ***************************************************************************/
void issdk_gpio_handle_interrupt(GINT_Type *apBase, gint_port_t aPortNumber)
{
    uint32_t enableMask, polarityMask;

    GINT_GetConfigPins(apBase, aPortNumber, &polarityMask, &enableMask);
    // parse through all the pending interrupt for a PORT
    for (uint8_t i = 0; i < GINT_NUMBER_OF_PIN; i++)
    {
        if (enableMask & (1 << i))
        {
            gpio_isr_handler_t handle = isrObj[aPortNumber][i].isrHandle;
            if (handle == NULL)
            {
                continue;
            }
            // call user defined handler
            handle(isrObj[aPortNumber][i].pUserData);
        }
    }
}

GENERIC_DRIVER_GPIO Driver_GPIO_KSDK = {
    ksdk_gpio_get_version, ksdk_gpio_pin_init,  ksdk_gpio_set_pin,  ksdk_gpio_clr_pin,
    ksdk_gpio_toggle_pin,  ksdk_gpio_write_pin, ksdk_gpio_read_pin,
};
