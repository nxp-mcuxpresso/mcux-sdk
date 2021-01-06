/*
 * Copyright 2018 - 2019 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_device_registers.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_adapter_gpio.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#if defined(__GNUC__)
#define HAL_GPIO_CLZ(x) __builtin_clz(x)
#elif defined(__ICCARM__)
#define HAL_GPIO_CLZ(x) __CLZ(x)
#elif defined(__CC_ARM) || defined(__ARMCC_VERSION)
#define HAL_GPIO_CLZ(x) __builtin_clz(x)
#else
#error The tool-chain is not supported.
#endif
#define HAL_GPIO_BSR(x) (31U - (uint8_t)HAL_GPIO_CLZ(x))

/*! @brief The pin config struct of gpio adapter. */

typedef struct _hal_gpio_pin
{
    uint16_t port : 3U;
    uint16_t reserved : 1U;
    uint16_t pin : 5U;
    uint16_t direction : 1U;
    uint16_t trigger : 3U;
    uint16_t reserved2 : 3U;
} hal_gpio_pin_t;

typedef struct _hal_gpio_state
{
    struct _hal_gpio_state *next;
    hal_gpio_callback_t callback;
    void *callbackParam;
    hal_gpio_direction_t direction;
    uint8_t level;
    uint8_t port;
    uint8_t pin : 5U;
    uint8_t trigger : 3U;
} hal_gpio_state_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

static GPIO_Type *const s_GpioPort[] = GPIO_BASE_PTRS;
static hal_gpio_state_t *s_GpioHead;

/*******************************************************************************
 * Code
 ******************************************************************************/

static void HAL_GpioInterruptHandle(uint8_t port)
{
    hal_gpio_state_t *head = s_GpioHead;
    uint32_t pinInterruptSetFlag;
    uint8_t pin;

    while (NULL != head)
    {
        if (head->port == port)
        {
            break;
        }
        head = head->next;
    }

    if (NULL == head)
    {
        return;
    }

    head = s_GpioHead;

#if (defined(FSL_FEATURE_PORT_HAS_NO_INTERRUPT) && FSL_FEATURE_PORT_HAS_NO_INTERRUPT)
    pinInterruptSetFlag = GPIO_GpioGetInterruptFlags(s_GpioPort[port]);
    /* Clear external interrupt flag. */
    GPIO_GpioClearInterruptFlags(s_GpioPort[port], pinInterruptSetFlag);
#else
    pinInterruptSetFlag = GPIO_PortGetInterruptFlags(s_GpioPort[port]);
    /* Clear external interrupt flag. */
    GPIO_PortClearInterruptFlags(s_GpioPort[port], pinInterruptSetFlag);
#endif
    if (0U != pinInterruptSetFlag)
    {
        pin = HAL_GPIO_BSR(pinInterruptSetFlag);
        while (NULL != head)
        {
            if ((pin == head->pin) && (port == head->port))
            {
                if (NULL != head->callback)
                {
                    head->callback(head->callbackParam);
                }
                pinInterruptSetFlag &= ~(0x01UL << pin);
                if (0U == pinInterruptSetFlag)
                {
                    break;
                }
                pin = HAL_GPIO_BSR(pinInterruptSetFlag);
            }
            head = head->next;
        }
    }
}

#if (defined(HAL_GPIO_CONFLICT_CHECK_ENABLE) && (HAL_GPIO_CONFLICT_CHECK_ENABLE > 0U))
static hal_gpio_status_t HAL_GpioConflictSearch(hal_gpio_state_t *head, uint8_t port, uint8_t pin)
{
    while (NULL != head)
    {
        if ((head->port == port) && (head->pin == pin))
        {
            return kStatus_HAL_GpioPinConflict;
        }
        head = head->next;
    }
    return kStatus_HAL_GpioSuccess;
}
#endif /* HAL_GPIO_CONFLICT_CHECK_ENABLE */

static hal_gpio_status_t HAL_GpioAddItem(hal_gpio_state_t **head, hal_gpio_state_t *node)
{
    hal_gpio_state_t *p = *head;
    hal_gpio_state_t *q = *head;
    uint32_t regPrimask;

    regPrimask = DisableGlobalIRQ();

    if (NULL == p)
    {
        *head = node;
    }
    else
    {
        while (NULL != p)
        {
            if (p == node)
            {
                EnableGlobalIRQ(regPrimask);
                return kStatus_HAL_GpioPinConflict;
            }
            q = p;
            p = p->next;
        }

        q->next = node;
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
    while (p != NULL)
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

#if (defined(FSL_FEATURE_PORT_HAS_NO_INTERRUPT) && FSL_FEATURE_PORT_HAS_NO_INTERRUPT)

#if (FSL_FEATURE_SOC_GPIO_COUNT > 0U)
void GPIOA_INT0_IRQHandler(void);
void GPIOA_INT0_IRQHandler(void)
{
    HAL_GpioInterruptHandle(0);
    SDK_ISR_EXIT_BARRIER;
}

void GPIOA_INT1_IRQHandler(void);
void GPIOA_INT1_IRQHandler(void)
{
    GPIOA_INT0_IRQHandler();
}
#endif

#if (FSL_FEATURE_SOC_GPIO_COUNT > 1U)
void GPIOB_INT0_IRQHandler(void);
void GPIOB_INT0_IRQHandler(void)
{
    HAL_GpioInterruptHandle(1);
    SDK_ISR_EXIT_BARRIER;
}
void GPIOB_INT1_IRQHandler(void);
void GPIOB_INT1_IRQHandler(void)
{
    GPIOB_INT0_IRQHandler();
}
#endif

#if (FSL_FEATURE_SOC_GPIO_COUNT > 2U)
void GPIOC_INT0_IRQHandler(void);
void GPIOC_INT0_IRQHandler(void)
{
    HAL_GpioInterruptHandle(2);
    SDK_ISR_EXIT_BARRIER;
}
void GPIOC_INT1_IRQHandler(void);
void GPIOC_INT1_IRQHandler(void)
{
    GPIOC_INT0_IRQHandler();
}
#endif

#if (FSL_FEATURE_SOC_GPIO_COUNT > 3U)
void GPIOD_INT0_IRQHandler(void);
void GPIOD_INT0_IRQHandler(void)
{
    HAL_GpioInterruptHandle(3);
    SDK_ISR_EXIT_BARRIER;
}
void GPIOD_INT1_IRQHandler(void);
void GPIOD_INT1_IRQHandler(void)
{
    GPIOD_INT0_IRQHandler();
}
#endif

#else

#if (FSL_FEATURE_SOC_GPIO_COUNT > 0U)
void PORTA_IRQHandler(void);
void PORTA_IRQHandler(void)
{
    HAL_GpioInterruptHandle(0);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if (FSL_FEATURE_SOC_GPIO_COUNT > 1U)
void PORTB_IRQHandler(void);
void PORTB_IRQHandler(void)
{
    HAL_GpioInterruptHandle(1);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if (FSL_FEATURE_SOC_GPIO_COUNT > 2U)
void PORTC_IRQHandler(void);
void PORTC_IRQHandler(void)
{
    HAL_GpioInterruptHandle(2);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if (FSL_FEATURE_SOC_GPIO_COUNT > 2U)
void PORTB_PORTC_IRQHandler(void);
void PORTB_PORTC_IRQHandler(void)
{
    HAL_GpioInterruptHandle(1);
    HAL_GpioInterruptHandle(2);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if (FSL_FEATURE_SOC_GPIO_COUNT > 4U)
void PORTB_PORTC_PORTD_PORTE_IRQHandler(void);
void PORTB_PORTC_PORTD_PORTE_IRQHandler(void)
{
    HAL_GpioInterruptHandle(1);
    HAL_GpioInterruptHandle(2);
    HAL_GpioInterruptHandle(3);
    HAL_GpioInterruptHandle(4);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if (FSL_FEATURE_SOC_GPIO_COUNT > 3U)
void PORTC_PORTD_IRQHandler(void);
void PORTC_PORTD_IRQHandler(void)
{
    HAL_GpioInterruptHandle(2);
    HAL_GpioInterruptHandle(3);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if (FSL_FEATURE_SOC_GPIO_COUNT > 3U)
void PORTD_IRQHandler(void);
void PORTD_IRQHandler(void)
{
    HAL_GpioInterruptHandle(3);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if (FSL_FEATURE_SOC_GPIO_COUNT > 4U)
void PORTE_IRQHandler(void);
void PORTE_IRQHandler(void)
{
    HAL_GpioInterruptHandle(4);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if (FSL_FEATURE_SOC_GPIO_COUNT > 5U)
void PORTF_IRQHandler(void);
void PORTF_IRQHandler(void)
{
    HAL_GpioInterruptHandle(5);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#endif

void HAL_GpioPreInit(void)
{
    s_GpioHead = NULL;
}

hal_gpio_status_t HAL_GpioInit(hal_gpio_handle_t gpioHandle, hal_gpio_pin_config_t *pinConfig)
{
    hal_gpio_state_t *gpioState;
    hal_gpio_status_t status;

    assert(gpioHandle);
    assert(pinConfig);
    assert(HAL_GPIO_HANDLE_SIZE >= sizeof(hal_gpio_state_t));

    gpioState = (hal_gpio_state_t *)gpioHandle;

#if (defined(HAL_GPIO_CONFLICT_CHECK_ENABLE) && (HAL_GPIO_CONFLICT_CHECK_ENABLE > 0U))
    if ((NULL != s_GpioHead) &&
        (kStatus_HAL_GpioSuccess != HAL_GpioConflictSearch(s_GpioHead, pinConfig->port, pinConfig->pin)))
    {
        return kStatus_HAL_GpioPinConflict;
    }
#endif /* HAL_GPIO_CONFLICT_CHECK_ENABLE */

    status = HAL_GpioAddItem(&s_GpioHead, gpioState);
    if (kStatus_HAL_GpioSuccess != status)
    {
        return status;
    }

    (void)memcpy((void *)&gpioState->direction, (void *)pinConfig, sizeof(hal_gpio_pin_config_t));

    GPIO_PinInit(s_GpioPort[pinConfig->port], pinConfig->pin, (const gpio_pin_config_t *)(void *)&pinConfig->direction);
    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioDeinit(hal_gpio_handle_t gpioHandle)
{
    hal_gpio_state_t *gpioState;

    assert(gpioHandle);

    gpioState = (hal_gpio_state_t *)gpioHandle;
    if (kHAL_GpioDirectionIn == gpioState->direction)
    {
        (void)HAL_GpioSetTriggerMode(gpioHandle, kHAL_GpioInterruptDisable);
    }
    (void)HAL_GpioRemoveItem(&s_GpioHead, gpioState);
    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioGetInput(hal_gpio_handle_t gpioHandle, uint8_t *pinState)
{
    hal_gpio_state_t *gpioState;

    assert(gpioHandle);
    assert(pinState);

    gpioState = (hal_gpio_state_t *)gpioHandle;

    *pinState = (GPIO_PinRead(s_GpioPort[gpioState->port], gpioState->pin) != 0U) ? 1U : 0U;
    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioSetOutput(hal_gpio_handle_t gpioHandle, uint8_t pinState)
{
    hal_gpio_state_t *gpioState;

    assert(gpioHandle);

    gpioState = (hal_gpio_state_t *)gpioHandle;

    GPIO_PinWrite(s_GpioPort[gpioState->port], gpioState->pin, (pinState != 0U) ? 1U : 0U);
    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioInstallCallback(hal_gpio_handle_t gpioHandle,
                                          hal_gpio_callback_t callback,
                                          void *callbackParam)
{
    hal_gpio_state_t *gpioState;

    assert(gpioHandle);

    gpioState = (hal_gpio_state_t *)gpioHandle;

    gpioState->callbackParam = callbackParam;
    gpioState->callback      = callback;

    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioGetTriggerMode(hal_gpio_handle_t gpioHandle, hal_gpio_interrupt_trigger_t *gpioTrigger)
{
    hal_gpio_state_t *gpioState;

    assert(gpioHandle);

    gpioState = (hal_gpio_state_t *)gpioHandle;

    if (kHAL_GpioDirectionOut == gpioState->direction)
    {
        return kStatus_HAL_GpioError;
    }

    *gpioTrigger = (hal_gpio_interrupt_trigger_t)gpioState->trigger;
    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioSetTriggerMode(hal_gpio_handle_t gpioHandle, hal_gpio_interrupt_trigger_t gpioTrigger)
{
    hal_gpio_state_t *gpioState;
#if (defined(FSL_FEATURE_PORT_HAS_NO_INTERRUPT) && FSL_FEATURE_PORT_HAS_NO_INTERRUPT)
    gpio_interrupt_config_t pinInt;
    static const IRQn_Type irqNo[] = GPIO_IRQS;
#else
    PORT_Type *portList[] = PORT_BASE_PTRS;
    static const IRQn_Type irqNo[] = PORT_IRQS;
    port_interrupt_t pinInt;
#endif

    assert(gpioHandle);

    gpioState = (hal_gpio_state_t *)gpioHandle;
    assert(kHAL_GpioDirectionOut != gpioState->direction);

    switch (gpioTrigger)
    {
        case kHAL_GpioInterruptLogicZero:
#if (defined(FSL_FEATURE_PORT_HAS_NO_INTERRUPT) && FSL_FEATURE_PORT_HAS_NO_INTERRUPT)
            pinInt = kGPIO_InterruptLogicZero;
#else
            pinInt = kPORT_InterruptLogicZero;
#endif
            break;
        case kHAL_GpioInterruptLogicOne:
#if (defined(FSL_FEATURE_PORT_HAS_NO_INTERRUPT) && FSL_FEATURE_PORT_HAS_NO_INTERRUPT)
            pinInt = kGPIO_InterruptLogicOne;
#else
            pinInt = kPORT_InterruptLogicOne;
#endif
            break;
        case kHAL_GpioInterruptRisingEdge:
#if (defined(FSL_FEATURE_PORT_HAS_NO_INTERRUPT) && FSL_FEATURE_PORT_HAS_NO_INTERRUPT)
            pinInt = kGPIO_InterruptRisingEdge;
#else
            pinInt = kPORT_InterruptRisingEdge;
#endif
            break;
        case kHAL_GpioInterruptFallingEdge:
#if (defined(FSL_FEATURE_PORT_HAS_NO_INTERRUPT) && FSL_FEATURE_PORT_HAS_NO_INTERRUPT)
            pinInt = kGPIO_InterruptFallingEdge;
#else
            pinInt = kPORT_InterruptFallingEdge;
#endif
            break;
        case kHAL_GpioInterruptEitherEdge:
#if (defined(FSL_FEATURE_PORT_HAS_NO_INTERRUPT) && FSL_FEATURE_PORT_HAS_NO_INTERRUPT)
            pinInt = kGPIO_InterruptEitherEdge;
#else
            pinInt = kPORT_InterruptEitherEdge;
#endif
            break;
        default:
#if (defined(FSL_FEATURE_PORT_HAS_NO_INTERRUPT) && FSL_FEATURE_PORT_HAS_NO_INTERRUPT)
            pinInt = kGPIO_InterruptStatusFlagDisabled;
#else
            pinInt = kPORT_InterruptOrDMADisabled;
#endif
            break;
    }

    gpioState->trigger = (uint8_t)gpioTrigger;

    /* initialize port interrupt */
#if (defined(FSL_FEATURE_PORT_HAS_NO_INTERRUPT) && FSL_FEATURE_PORT_HAS_NO_INTERRUPT)
    GPIO_SetPinInterruptConfig(s_GpioPort[gpioState->port], gpioState->pin, pinInt);
#else
    PORT_SetPinInterruptConfig(portList[gpioState->port], gpioState->pin, pinInt);
#endif
    NVIC_SetPriority(irqNo[gpioState->port], HAL_GPIO_ISR_PRIORITY);
    NVIC_EnableIRQ(irqNo[gpioState->port]);

    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioWakeUpSetting(hal_gpio_handle_t gpioHandle, uint8_t enable)
{
    hal_gpio_state_t *gpioState;

    assert(gpioHandle);

    gpioState = (hal_gpio_state_t *)gpioHandle;

    if (kHAL_GpioDirectionOut == gpioState->direction)
    {
        return kStatus_HAL_GpioError;
    }
    /* The wakeup feature of GPIO cannot be disabled. */
    if (0U == enable)
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
    hal_gpio_state_t *gpioState;
    gpio_pin_config_t gpioPinconfig = {
        kGPIO_DigitalInput,
        0,
    };

    assert(gpioHandle);

    gpioState                  = (hal_gpio_state_t *)gpioHandle;
    gpioPinconfig.pinDirection = kGPIO_DigitalInput;
    if (kHAL_GpioDirectionOut == gpioState->direction)
    {
        gpioPinconfig.pinDirection = kGPIO_DigitalOutput;
    }

    GPIO_PinInit(s_GpioPort[gpioState->port], gpioState->pin, &gpioPinconfig);
    (void)HAL_GpioSetTriggerMode(gpioHandle, (hal_gpio_interrupt_trigger_t)gpioState->trigger);
    return kStatus_HAL_GpioSuccess;
}
