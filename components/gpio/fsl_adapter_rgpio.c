/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_rgpio.h"
#include "fsl_adapter_gpio.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "component.rgpio_adapter"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief The pin config struct of gpio adapter. */
typedef struct _hal_gpio_pin
{
    uint16_t port : 3U;
    uint16_t pin : 5U;
    uint16_t direction : 1U;
    uint16_t trigger : 4U;
    uint16_t reserved : 3U;
} hal_gpio_pin_t;

/*! @brief The gpio config struct of gpio adapter. */
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
static RGPIO_Type *const s_rgpioBases[] = RGPIO_BASE_PTRS;
#ifdef RGPIO_IRQS
static IRQn_Type Rgpio_IRQn[] = RGPIO_IRQS;
#else
static IRQn_Type Rgpio_IRQn[] = {NotAvail_IRQn, GPIO1_0_IRQn, GPIO2_0_IRQn, GPIO3_0_IRQn,
                                 GPIO4_IRQn,    GPIO5_IRQn,   GPIO6_IRQn};
#endif
/*******************************************************************************
 * Code
 ******************************************************************************/

static void HAL_GpioInterruptHandle(uint32_t intNum)
{
    hal_gpio_state_t *head = s_GpioHead;
    uint32_t portIntFlags  = 0U;

    /* rgpio instantiates from the array 1st member. */
    if (Rgpio_IRQn[0] != NotAvail_IRQn)
    {
        intNum = intNum - 1U;
    }

    while (NULL != head)
    {
        portIntFlags =
            RGPIO_GetPinsInterruptFlags(s_rgpioBases[intNum], (rgpio_interrupt_sel_t)kRGPIO_InterruptOutput0);
        if (0U != (portIntFlags & (1UL << head->pin.pin)))
        {
            if (NULL != head->callback)
            {
                head->callback(head->callbackParam);
            }
            RGPIO_ClearPinsInterruptFlags(s_rgpioBases[intNum], (rgpio_interrupt_sel_t)kRGPIO_InterruptOutput0,
                                          portIntFlags);
        }

        head = head->next;
    }
}

/*!
 * @brief Interrupt service fuction of switch.
 */
#if (FSL_FEATURE_SOC_RGPIO_COUNT > 0U)
void GPIO1_0_IRQHandler(void);
void GPIO1_0_IRQHandler(void)
{
    HAL_GpioInterruptHandle(1);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if (FSL_FEATURE_SOC_RGPIO_COUNT > 1U)
void GPIO2_0_IRQHandler(void);
void GPIO2_0_IRQHandler(void)
{
    HAL_GpioInterruptHandle(2);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if (FSL_FEATURE_SOC_RGPIO_COUNT > 2U)
void GPIO3_0_IRQHandler(void);
void GPIO3_0_IRQHandler(void)
{
    HAL_GpioInterruptHandle(3);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if (FSL_FEATURE_SOC_RGPIO_COUNT > 3U)
void GPIO4_IRQHandler(void);
void GPIO4_IRQHandler(void)
{
    HAL_GpioInterruptHandle(4);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if (FSL_FEATURE_SOC_RGPIO_COUNT > 4U)
void GPIO5_IRQHandler(void);
void GPIO5_IRQHandler(void)
{
    HAL_GpioInterruptHandle(5);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if (FSL_FEATURE_SOC_RGPIO_COUNT > 5U)
void GPIO6_IRQHandler(void);
void GPIO6_IRQHandler(void)
{
    HAL_GpioInterruptHandle(6);
    SDK_ISR_EXIT_BARRIER;
}
#endif

static hal_gpio_status_t HAL_GpioConflictSearch(hal_gpio_state_t *head, uint8_t gpio_port, uint8_t pin)
{
    while (NULL != head)
    {
        if ((head->pin.port == gpio_port) && (head->pin.pin == pin))
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
    s_GpioHead = NULL;
}

hal_gpio_status_t HAL_GpioInit(hal_gpio_handle_t gpioHandle, hal_gpio_pin_config_t *pinConfig)
{
    hal_gpio_state_t *gpioState;
    hal_gpio_status_t status         = kStatus_HAL_GpioSuccess;
    rgpio_pin_config_t gpioPinConfig = {kRGPIO_DigitalInput, 0};

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
        gpioPinConfig.pinDirection = kRGPIO_DigitalOutput;
        gpioPinConfig.outputLogic  = pinConfig->level;
    }
    else
    {
        gpioPinConfig.pinDirection = kRGPIO_DigitalInput;
    }

    RGPIO_PinInit(s_rgpioBases[gpioState->pin.port], gpioState->pin.pin, &gpioPinConfig);

    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioDeinit(hal_gpio_handle_t gpioHandle)
{
    hal_gpio_state_t *gpioState;

    assert(gpioHandle);

    gpioState = (hal_gpio_state_t *)gpioHandle;

    (void)HAL_GpioRemoveItem(&s_GpioHead, gpioState);
    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioGetInput(hal_gpio_handle_t gpioHandle, uint8_t *pinState)
{
    hal_gpio_state_t *gpioStateHandle;

    assert(gpioHandle);

    gpioStateHandle = (hal_gpio_state_t *)gpioHandle;

    *pinState = (uint8_t)RGPIO_PinRead(s_rgpioBases[gpioStateHandle->pin.port], gpioStateHandle->pin.pin);
    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioSetOutput(hal_gpio_handle_t gpioHandle, uint8_t pinState)
{
    hal_gpio_state_t *gpioStateHandle;

    assert(gpioHandle);

    gpioStateHandle = (hal_gpio_state_t *)gpioHandle;

    RGPIO_PinWrite(s_rgpioBases[gpioStateHandle->pin.port], gpioStateHandle->pin.pin, (0U != pinState) ? 1U : 0U);
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
    rgpio_interrupt_config_t triggerConfig = kRGPIO_InterruptOrDMADisabled;

    assert(gpioHandle);

    gpioStateHandle = (hal_gpio_state_t *)gpioHandle;

    assert((uint16_t)kHAL_GpioDirectionOut != gpioStateHandle->pin.direction);

    switch (gpioTrigger)
    {
        case kHAL_GpioInterruptLogicZero:
            triggerConfig = kRGPIO_InterruptLogicZero;
            break;
        case kHAL_GpioInterruptLogicOne:
            triggerConfig = kRGPIO_InterruptLogicOne;
            break;
        case kHAL_GpioInterruptRisingEdge:
            triggerConfig = kRGPIO_InterruptRisingEdge;
            break;
        case kHAL_GpioInterruptFallingEdge:
            triggerConfig = kRGPIO_InterruptFallingEdge;
            break;
        case kHAL_GpioInterruptEitherEdge:
            triggerConfig = kRGPIO_InterruptEitherEdge;
            break;
        case kHAL_GpioInterruptDisable:
        default:
            triggerConfig = kRGPIO_InterruptOrDMADisabled;
            break;
    }

    gpioStateHandle->pin.trigger = (uint16_t)gpioTrigger;
    /* Set trigger interrupt */
    RGPIO_SetPinInterruptConfig(s_rgpioBases[gpioStateHandle->pin.port], gpioStateHandle->pin.pin,
                                kRGPIO_InterruptOutput0, triggerConfig);
    if (kRGPIO_InterruptOrDMADisabled != triggerConfig)
    {
    	NVIC_SetPriority(Rgpio_IRQn[gpioStateHandle->pin.port], HAL_GPIO_ISR_PRIORITY);
    	NVIC_EnableIRQ(Rgpio_IRQn[gpioStateHandle->pin.port]);
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
