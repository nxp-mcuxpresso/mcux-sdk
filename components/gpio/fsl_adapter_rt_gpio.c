/*
 * Copyright 2018 - 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_gpio.h"
#include "fsl_adapter_gpio.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief The pin config struct of gpio adapter. */
typedef struct _hal_gpio_pin
{
    uint16_t port : 3U;
    uint16_t pin : 5U;
    uint16_t direction : 1U;
    uint16_t trigger : 3U;
    uint16_t reserved : 4U;
} hal_gpio_pin_t;

typedef struct _hal_gpio_state
{
    struct _hal_gpio_state *next;
    hal_gpio_callback_t callback;
    void *callbackParam;
    hal_gpio_pin_t pin;
} hal_gpio_state_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static hal_gpio_state_t *s_GpioHead;
static uint32_t s_GPIO_PORT_initFlag = 0U;

#define SET_GPIO_PORT_INIT_FLAG(port)   (s_GPIO_PORT_initFlag |= 1UL << (port))
#define GET_GPIO_PORT_INIT_FLAG(port)   ((0U != (s_GPIO_PORT_initFlag & (1UL << (port)))) ? 1U : 0U)
#define CLEAR_GPIO_PORT_INIT_FLAG(port) (s_GPIO_PORT_initFlag &= ~(1UL << (port)))

/*******************************************************************************
 * Code
 ******************************************************************************/

static void HAL_GpioInterruptHandle(uint32_t intNum)
{
    hal_gpio_state_t *head = s_GpioHead;
    gpio_interrupt_config_t triggerConfig;
    uint32_t portIntFlags = 0U;
    uint8_t pinLevel;

    while (NULL != head)
    {
        portIntFlags = GPIO_PortGetInterruptStatus(GPIO, head->pin.port, intNum);
        if (0U != (portIntFlags & (1UL << head->pin.pin)))
        {
            if (NULL != head->callback)
            {
                head->callback(head->callbackParam);
            }
            GPIO_PinClearInterruptFlag(GPIO, head->pin.port, head->pin.pin, intNum);
            if ((uint16_t)kHAL_GpioInterruptEitherEdge == head->pin.trigger)
            {
                pinLevel           = (uint8_t)GPIO_PinRead(GPIO, head->pin.port, head->pin.pin);
                triggerConfig.mode = (uint8_t)kGPIO_PinIntEnableEdge;
                triggerConfig.polarity =
                    (0U != pinLevel) ? (uint8_t)kGPIO_PinIntEnableLowOrFall : (uint8_t)kGPIO_PinIntEnableHighOrRise;
                GPIO_SetPinInterruptConfig(GPIO, head->pin.port, head->pin.pin, &triggerConfig);
            }
        }

        head = head->next;
    }
}

/*!
 * @brief Interrupt service fuction of switch.
 */
void GPIO_INTA_DriverIRQHandler(void);
void GPIO_INTA_DriverIRQHandler(void)
{
    HAL_GpioInterruptHandle(0);
    SDK_ISR_EXIT_BARRIER;
}

void GPIO_INTB_DriverIRQHandler(void);
void GPIO_INTB_DriverIRQHandler(void)
{
    HAL_GpioInterruptHandle(1);
    SDK_ISR_EXIT_BARRIER;
}

static hal_gpio_status_t HAL_GpioConflictSearch(hal_gpio_state_t *head, uint8_t port, uint8_t pin)
{
    while (NULL != head)
    {
        if ((head->pin.port == port) && (head->pin.pin == pin))
        {
            return kStatus_HAL_GpioPinConflict;
        }
        head = head->next;
    }
    return kStatus_HAL_GpioSuccess;
}

static hal_gpio_status_t HAL_GpioAddItem(hal_gpio_state_t **head, hal_gpio_state_t *node)
{
    hal_gpio_state_t *p = *head;
    uint32_t regPrimask;

    regPrimask = DisableGlobalIRQ();

    if (NULL == p)
    {
        *head = node;
    }
    else
    {
        while (NULL != p->next)
        {
            if (p == node)
            {
                EnableGlobalIRQ(regPrimask);
                return kStatus_HAL_GpioPinConflict;
            }
            p = p->next;
        }

        p->next = node;
    }
    node->next = NULL;
    EnableGlobalIRQ(regPrimask);
    return kStatus_HAL_GpioSuccess;
}

static hal_gpio_status_t HAL_GpioRemoveItem(hal_gpio_state_t **head, hal_gpio_state_t *node)
{
    hal_gpio_state_t *p = *head;
    hal_gpio_state_t *q = NULL;
    uint32_t regPrimask;

    regPrimask = DisableGlobalIRQ();
    while (NULL != p)
    {
        if (p == node)
        {
            if (NULL == q)
            {
                *head = p->next;
            }
            else
            {
                q->next = p->next;
            }
            break;
        }
        else
        {
            q = p;
            p = p->next;
        }
    }
    EnableGlobalIRQ(regPrimask);
    return kStatus_HAL_GpioSuccess;
}

void HAL_GpioPreInit(void)
{
    s_GPIO_PORT_initFlag = 0U;
    s_GpioHead           = NULL;
}

hal_gpio_status_t HAL_GpioInit(hal_gpio_handle_t gpioHandle, hal_gpio_pin_config_t *pinConfig)
{
    hal_gpio_state_t *gpioState;
    hal_gpio_status_t status        = kStatus_HAL_GpioSuccess;
    gpio_pin_config_t gpioPinConfig = {kGPIO_DigitalInput, 0};
    uint32_t regPrimask;
    uint8_t portNeedInit = 0;

    assert(gpioHandle);
    assert(pinConfig);

    gpioState = (hal_gpio_state_t *)gpioHandle;

    /* Check if it is conflict */
    if ((NULL != s_GpioHead) &&
        (kStatus_HAL_GpioSuccess != HAL_GpioConflictSearch(s_GpioHead, pinConfig->port, pinConfig->pin)))
    {
        return kStatus_HAL_GpioPinConflict;
    }

    status = HAL_GpioAddItem(&s_GpioHead, gpioState);
    if (kStatus_HAL_GpioSuccess != status)
    {
        return status;
    }

    gpioState->pin.pin       = pinConfig->pin;
    gpioState->pin.port      = pinConfig->port;
    gpioState->pin.direction = (uint16_t)pinConfig->direction;
    gpioState->pin.trigger   = (uint16_t)kHAL_GpioInterruptDisable;

    if (kHAL_GpioDirectionOut == pinConfig->direction)
    {
        gpioPinConfig.pinDirection = kGPIO_DigitalOutput;
    }
    else
    {
        gpioPinConfig.pinDirection = kGPIO_DigitalInput;
    }
    gpioPinConfig.outputLogic = pinConfig->level;

    /* Critical protection */
    regPrimask = DisableGlobalIRQ();
    if (0U == GET_GPIO_PORT_INIT_FLAG(gpioState->pin.port))
    {
        SET_GPIO_PORT_INIT_FLAG(gpioState->pin.port);
        portNeedInit = 1U;
    }
    EnableGlobalIRQ(regPrimask);

    if (1U == portNeedInit)
    {
        GPIO_PortInit(GPIO, gpioState->pin.port);
    }

    GPIO_PinInit(GPIO, gpioState->pin.port, gpioState->pin.pin, &gpioPinConfig);

    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioDeinit(hal_gpio_handle_t gpioHandle)
{
    hal_gpio_state_t *gpioState;

    assert(gpioHandle);

    gpioState = (hal_gpio_state_t *)gpioHandle;

    if ((uint16_t)kHAL_GpioDirectionIn == gpioState->pin.direction)
    {
        GPIO_PinDisableInterrupt(GPIO, gpioState->pin.port, gpioState->pin.pin, 0);
    }

    (void)HAL_GpioRemoveItem(&s_GpioHead, gpioState);
    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioGetInput(hal_gpio_handle_t gpioHandle, uint8_t *pinState)
{
    hal_gpio_state_t *gpioStateHandle;

    assert(gpioHandle);

    gpioStateHandle = (hal_gpio_state_t *)gpioHandle;

    *pinState = (uint8_t)GPIO_PinRead(GPIO, gpioStateHandle->pin.port, gpioStateHandle->pin.pin);

    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioSetOutput(hal_gpio_handle_t gpioHandle, uint8_t pinState)
{
    hal_gpio_state_t *gpioStateHandle;

    assert(gpioHandle);

    gpioStateHandle = (hal_gpio_state_t *)gpioHandle;

    GPIO_PinWrite(GPIO, gpioStateHandle->pin.port, gpioStateHandle->pin.pin, (0U != pinState) ? 1U : 0U);

    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioInstallCallback(hal_gpio_handle_t gpioHandle,
                                          hal_gpio_callback_t callback,
                                          void *callbackParam)
{
    hal_gpio_state_t *gpioStateHandle;

    assert(gpioHandle);

    gpioStateHandle = (hal_gpio_state_t *)gpioHandle;

    gpioStateHandle->callbackParam = callbackParam;
    gpioStateHandle->callback      = callback;

    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioGetTriggerMode(hal_gpio_handle_t gpioHandle, hal_gpio_interrupt_trigger_t *gpioTrigger)
{
    hal_gpio_state_t *gpioStateHandle;

    assert(gpioHandle);

    gpioStateHandle = (hal_gpio_state_t *)gpioHandle;

    if ((uint16_t)kHAL_GpioDirectionOut == gpioStateHandle->pin.direction)
    {
        return kStatus_HAL_GpioError;
    }

    *gpioTrigger = (hal_gpio_interrupt_trigger_t)gpioStateHandle->pin.trigger;
    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioSetTriggerMode(hal_gpio_handle_t gpioHandle, hal_gpio_interrupt_trigger_t gpioTrigger)
{
    hal_gpio_state_t *gpioStateHandle;
    gpio_interrupt_config_t triggerConfig;
    uint32_t pinLevel     = 0U;
    uint8_t trigerDisable = 0U;

    assert(gpioHandle);

    gpioStateHandle = (hal_gpio_state_t *)gpioHandle;

    assert((uint16_t)kHAL_GpioDirectionOut != gpioStateHandle->pin.direction);

    switch (gpioTrigger)
    {
        case kHAL_GpioInterruptLogicZero:
            triggerConfig.mode     = (uint8_t)kGPIO_PinIntEnableLevel;
            triggerConfig.polarity = (uint8_t)kGPIO_PinIntEnableLowOrFall;
            break;
        case kHAL_GpioInterruptLogicOne:
            triggerConfig.mode     = (uint8_t)kGPIO_PinIntEnableLevel;
            triggerConfig.polarity = (uint8_t)kGPIO_PinIntEnableHighOrRise;
            break;
        case kHAL_GpioInterruptRisingEdge:
            triggerConfig.mode     = (uint8_t)kGPIO_PinIntEnableEdge;
            triggerConfig.polarity = (uint8_t)kGPIO_PinIntEnableHighOrRise;
            break;
        case kHAL_GpioInterruptFallingEdge:
            triggerConfig.mode     = (uint8_t)kGPIO_PinIntEnableEdge;
            triggerConfig.polarity = (uint8_t)kGPIO_PinIntEnableLowOrFall;
            break;
        case kHAL_GpioInterruptEitherEdge:
            /* Here will get pin's default level to decide which edge trigger for the first time */
            pinLevel           = GPIO_PinRead(GPIO, gpioStateHandle->pin.port, gpioStateHandle->pin.pin);
            triggerConfig.mode = (uint8_t)kGPIO_PinIntEnableEdge;
            triggerConfig.polarity =
                (0U != pinLevel) ? (uint8_t)kGPIO_PinIntEnableLowOrFall : (uint8_t)kGPIO_PinIntEnableHighOrRise;
            break;
        default:
            trigerDisable = 1U;
            break;
    }

    gpioStateHandle->pin.trigger = (uint16_t)gpioTrigger;

    /* Set trigger interrupt */
    if (1U != trigerDisable)
    {
        GPIO_SetPinInterruptConfig(GPIO, gpioStateHandle->pin.port, gpioStateHandle->pin.pin, &triggerConfig);
        GPIO_PinEnableInterrupt(GPIO, gpioStateHandle->pin.port, gpioStateHandle->pin.pin, 0);
        NVIC_EnableIRQ(GPIO_INTA_IRQn);
    }
    else
    {
        GPIO_PinDisableInterrupt(GPIO, gpioStateHandle->pin.port, gpioStateHandle->pin.pin, 0);
    }

    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioWakeUpSetting(hal_gpio_handle_t gpioHandle, uint8_t enable)
{
    hal_gpio_state_t *gpioStateHandle;
    assert(gpioHandle);

    gpioStateHandle = (hal_gpio_state_t *)gpioHandle;

    if ((uint16_t)kHAL_GpioDirectionOut == gpioStateHandle->pin.direction)
    {
        return kStatus_HAL_GpioError;
    }

    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioEnterLowpower(hal_gpio_handle_t gpioHandle)
{
    assert(gpioHandle);

    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioExitLowpower(hal_gpio_handle_t gpioHandle)
{
    assert(gpioHandle);

    return kStatus_HAL_GpioSuccess;
}
