/*
 * Copyright 2018 - 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_gpio.h"
#if (defined(FSL_FEATURE_SYSCON_HAS_PINT_SEL_REGISTER) && (FSL_FEATURE_SYSCON_HAS_PINT_SEL_REGISTER > 0U))
#include "fsl_syscon.h"
#else
#include "fsl_inputmux.h"
#endif
#include "fsl_pint.h"
#include "fsl_adapter_gpio.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#if (defined(FSL_FEATURE_SYSCON_HAS_PINT_SEL_REGISTER) && (FSL_FEATURE_SYSCON_HAS_PINT_SEL_REGISTER > 0U))
#define HAL_INPUTMUX_GpioPortPinToPintsel(port, pin) \
    ((uint32_t)(pin) + ((uint32_t)(port) << 5U) + ((uint32_t)PINTSEL_ID << SYSCON_SHIFT))
#else
#define HAL_INPUTMUX_GpioPortPinToPintsel(port, pin) \
    ((uint32_t)(pin) + ((uint32_t)(port) << 5U) + ((uint32_t)PINTSEL_PMUX_ID << PMUX_SHIFT))
#endif

/*! @brief The pin config struct of gpio adapter. */
typedef struct _hal_gpio_pin
{
    uint8_t port;
    uint8_t pin;
    struct
    {
        uint8_t direction : 1U;
        uint8_t trigger : 3U;
        uint8_t reserved : 4U;
    } pinSet;
    struct
    {
        uint8_t pintInitialized : 1U;
        uint8_t pintIndex : 4U;
        uint8_t reserved : 3U;
    } pint;
} hal_gpio_pin_t;

typedef struct _hal_gpio_state
{
    struct _hal_gpio_state *next;
    hal_gpio_callback_t callback;
    void *callbackParam;
    hal_gpio_pin_t pin;
} hal_gpio_state_t;

#define HAL_GPIO_INPUTMUX_PIN_FLAG(port, pin) (((port) << 5U) + (pin))
#define HAL_GPIO_INPUTMUX_GET_PIN(flag)       ((flag)&0x1FU)
#define HAL_GPIO_INPUTMUX_GET_PORT(flag)      ((flag) >> 5U)

#define HAL_GPIO_PORT_INIT_SET_FLAG(port) (s_GpioPortInitializedFlag |= ((uint32_t)1U << (port)))
#define HAL_GPIO_PORT_INIT_GET_FLAG(port) ((0U != (s_GpioPortInitializedFlag & ((uint32_t)1U << (port)))) ? 1U : 0U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static void HAL_GpioInterruptHandle(uint8_t port, uint8_t pin);

/*******************************************************************************
 * Variables
 ******************************************************************************/

static uint8_t s_GpioPintInitialized      = 0;
static uint32_t s_GpioPortInitializedFlag = 0;

static uint8_t s_GpioInputMux[(FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS + 7) / 8];
static uint8_t s_GpioInputMuxPin[FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS];

static hal_gpio_state_t *s_GpioHead;

static const IRQn_Type s_PintIRQ[]   = PINT_IRQS;
static GPIO_Type *const s_GpioList[] = GPIO_BASE_PTRS;
/*******************************************************************************
 * Code
 ******************************************************************************/

static void HAL_GpioInterruptCallback(pint_pin_int_t pintr, uint32_t pmatch_status)
{
    if (0U != (s_GpioInputMux[(uint8_t)pintr >> 3U] & (1U << ((uint8_t)pintr & 0x07U))))
    {
        HAL_GpioInterruptHandle(HAL_GPIO_INPUTMUX_GET_PORT(s_GpioInputMuxPin[pintr]),
                                HAL_GPIO_INPUTMUX_GET_PIN(s_GpioInputMuxPin[pintr]));
    }
}

static void HAL_GpioInterruptHandle(uint8_t port, uint8_t pin)
{
    hal_gpio_state_t *head = s_GpioHead;

    while (NULL != head)
    {
        if ((pin == head->pin.pin) && (port == head->pin.port))
        {
            if ((NULL != head->callback))
            {
                head->callback(head->callbackParam);
            }
        }
        head = head->next;
    }
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
    s_GpioPintInitialized     = 0U;
    s_GpioPortInitializedFlag = 0U;
    s_GpioHead                = NULL;
}

hal_gpio_status_t HAL_GpioInit(hal_gpio_handle_t gpioHandle, hal_gpio_pin_config_t *pinConfig)
{
    hal_gpio_state_t *gpioState;
    hal_gpio_status_t status        = kStatus_HAL_GpioSuccess;
    gpio_pin_config_t gpioPinconfig = {
        kGPIO_DigitalInput,
        0U,
    };

    assert(gpioHandle);
    assert(pinConfig);
    assert(HAL_GPIO_HANDLE_SIZE >= sizeof(hal_gpio_state_t));

    gpioState = (hal_gpio_state_t *)gpioHandle;

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

    gpioState->pin.pin                  = pinConfig->pin;
    gpioState->pin.port                 = pinConfig->port;
    gpioState->pin.pinSet.direction     = (uint8_t)pinConfig->direction;
    gpioState->pin.pint.pintInitialized = 0U;

    if (kHAL_GpioDirectionOut == pinConfig->direction)
    {
        gpioPinconfig.pinDirection = kGPIO_DigitalOutput;
    }
    else
    {
        gpioPinconfig.pinDirection = kGPIO_DigitalInput;
    }
    if (0U == (uint32_t)HAL_GPIO_PORT_INIT_GET_FLAG(pinConfig->port))
    {
        HAL_GPIO_PORT_INIT_SET_FLAG(pinConfig->port);
        GPIO_PortInit(s_GpioList[0], pinConfig->port);
    }
    gpioPinconfig.outputLogic = pinConfig->level;
    GPIO_PinInit(s_GpioList[0], pinConfig->port, pinConfig->pin, &gpioPinconfig);

    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioDeinit(hal_gpio_handle_t gpioHandle)
{
    hal_gpio_state_t *gpioStateHandle;
    uint32_t i;
    uint32_t k;

    assert(gpioHandle);

    gpioStateHandle = (hal_gpio_state_t *)gpioHandle;

    if (0U != gpioStateHandle->pin.pint.pintInitialized)
    {
        /* Disable the pin's PINT callback */
        PINT_DisableCallbackByIndex(PINT, (pint_pin_int_t)gpioStateHandle->pin.pint.pintIndex);
    }

    for (k = 0U; k < (uint32_t)FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS; k++)
    {
        if (HAL_GPIO_INPUTMUX_PIN_FLAG(gpioStateHandle->pin.port, gpioStateHandle->pin.pin) == s_GpioInputMuxPin[k])
        {
            s_GpioInputMux[k >> 3U] &= ~(1U << (k & 0x07U));
            s_GpioInputMuxPin[k]                      = 0U;
            gpioStateHandle->pin.pint.pintInitialized = 0U;
            break;
        }
    }

    for (i = 0U; i < (uint32_t)FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS; i++)
    {
        if (0U != (s_GpioInputMux[i >> 3] & (1U << (i & 0x07U))))
        {
            break;
        }
    }

    if (i >= (uint32_t)FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS)
    {
        if (0U != s_GpioPintInitialized)
        {
            s_GpioPintInitialized = 0U;
            /* Deinitialize PINT */
            PINT_Deinit(PINT);
        }
    }

    (void)HAL_GpioRemoveItem(&s_GpioHead, gpioStateHandle);
    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioGetInput(hal_gpio_handle_t gpioHandle, uint8_t *pinState)
{
    hal_gpio_state_t *gpioStateHandle;

    assert(gpioHandle);

    gpioStateHandle = (hal_gpio_state_t *)gpioHandle;

    *pinState = ((0U != GPIO_PinRead(s_GpioList[0], gpioStateHandle->pin.port, gpioStateHandle->pin.pin)) ? 1U : 0U);
    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioSetOutput(hal_gpio_handle_t gpioHandle, uint8_t pinState)
{
    hal_gpio_state_t *gpioStateHandle;

    assert(gpioHandle);

    gpioStateHandle = (hal_gpio_state_t *)gpioHandle;

    GPIO_PinWrite(s_GpioList[0], gpioStateHandle->pin.port, gpioStateHandle->pin.pin, (0U != pinState) ? 1U : 0U);
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

    if ((uint8_t)kHAL_GpioDirectionOut == gpioStateHandle->pin.pinSet.direction)
    {
        return kStatus_HAL_GpioError;
    }

    *gpioTrigger = (hal_gpio_interrupt_trigger_t)gpioStateHandle->pin.pinSet.trigger;
    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioSetTriggerMode(hal_gpio_handle_t gpioHandle, hal_gpio_interrupt_trigger_t gpioTrigger)
{
    hal_gpio_state_t *gpioStateHandle;
    pint_pin_enable_t triggerType;
    uint32_t typeConvTemp; /* MISRA C-2012 Rule 10.8 */

    assert(gpioHandle);

    gpioStateHandle = (hal_gpio_state_t *)gpioHandle;

    if ((uint8_t)kHAL_GpioDirectionOut == gpioStateHandle->pin.pinSet.direction)
    {
        return kStatus_HAL_GpioError;
    }

    switch (gpioTrigger)
    {
        case kHAL_GpioInterruptLogicZero:
            triggerType = kPINT_PinIntEnableLowLevel;
            break;
        case kHAL_GpioInterruptLogicOne:
            triggerType = kPINT_PinIntEnableHighLevel;
            break;
        case kHAL_GpioInterruptRisingEdge:
            triggerType = kPINT_PinIntEnableRiseEdge;
            break;
        case kHAL_GpioInterruptFallingEdge:
            triggerType = kPINT_PinIntEnableFallEdge;
            break;
        case kHAL_GpioInterruptEitherEdge:
            triggerType = kPINT_PinIntEnableBothEdges;
            break;
        default:
            triggerType = kPINT_PinIntEnableNone;
            break;
    }

    gpioStateHandle->pin.pinSet.trigger = (uint8_t)gpioTrigger;

    /* Enable callbacks for PINT */
    if (0U == s_GpioPintInitialized)
    {
        s_GpioPintInitialized = 1U;
        /* Initialize PINT */
        PINT_Init(PINT);
    }

    /* initialize port interrupt */
    if (0U == gpioStateHandle->pin.pint.pintInitialized)
    {
        for (uint32_t inputMuxIndex = 0; inputMuxIndex < (uint32_t)FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS;
             inputMuxIndex++)
        {
            if (0U == (s_GpioInputMux[inputMuxIndex >> 3] & (1U << (inputMuxIndex & 0x07U))))
            {
                s_GpioInputMux[inputMuxIndex >> 3] |= 1U << (inputMuxIndex & 0x07U);
                gpioStateHandle->pin.pint.pintIndex       = (uint8_t)inputMuxIndex;
                gpioStateHandle->pin.pint.pintInitialized = 1U;
                break;
            }
        }
    }
    if (0U != gpioStateHandle->pin.pint.pintInitialized)
    {
        NVIC_SetPriority(s_PintIRQ[gpioStateHandle->pin.pint.pintIndex], HAL_GPIO_ISR_PRIORITY);
        s_GpioInputMuxPin[gpioStateHandle->pin.pint.pintIndex] =
            HAL_GPIO_INPUTMUX_PIN_FLAG(gpioStateHandle->pin.port, gpioStateHandle->pin.pin);
        /* Connect trigger sources to PINT */
#if (defined(FSL_FEATURE_SYSCON_HAS_PINT_SEL_REGISTER) && (FSL_FEATURE_SYSCON_HAS_PINT_SEL_REGISTER > 0U))
        typeConvTemp = HAL_INPUTMUX_GpioPortPinToPintsel(gpioStateHandle->pin.port, gpioStateHandle->pin.pin);
        SYSCON_AttachSignal(SYSCON, (uint32_t)gpioStateHandle->pin.pint.pintIndex, (syscon_connection_t)typeConvTemp);
#else
        INPUTMUX_Init(INPUTMUX);
        typeConvTemp = HAL_INPUTMUX_GpioPortPinToPintsel(gpioStateHandle->pin.port, gpioStateHandle->pin.pin);
        INPUTMUX_AttachSignal(INPUTMUX, (uint32_t)gpioStateHandle->pin.pint.pintIndex,
                              (inputmux_connection_t)typeConvTemp);
        /* Turnoff clock to inputmux to save power. Clock is only needed to make changes */
        INPUTMUX_Deinit(INPUTMUX);
#endif
        /* Setup Pin Interrupt 0 for rising edge */
        PINT_PinInterruptConfig(PINT, (pint_pin_int_t)gpioStateHandle->pin.pint.pintIndex, triggerType,
                                HAL_GpioInterruptCallback);
        /* Enable the pin's PINT call back */
        PINT_EnableCallbackByIndex(PINT, (pint_pin_int_t)gpioStateHandle->pin.pint.pintIndex);
    }
    else
    {
        return kStatus_HAL_GpioLackSource;
    }
    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioWakeUpSetting(hal_gpio_handle_t gpioHandle, uint8_t enable)
{
#if (defined(FSL_FEATURE_SOC_SYSCON_COUNT) && (FSL_FEATURE_SOC_SYSCON_COUNT > 0)) && \
    (!(defined(FSL_FEATURE_SYSCON_STARTER_DISCONTINUOUS) && FSL_FEATURE_SYSCON_STARTER_DISCONTINUOUS))

    hal_gpio_state_t *gpioStateHandle;
    assert(gpioHandle);

    gpioStateHandle = (hal_gpio_state_t *)gpioHandle;

    if ((uint8_t)kHAL_GpioDirectionOut == gpioStateHandle->pin.pinSet.direction)
    {
        return kStatus_HAL_GpioError;
    }

    if (0U != enable)
    {
        EnableDeepSleepIRQ(s_PintIRQ[gpioStateHandle->pin.pint.pintIndex]);
    }
    else
    {
        DisableDeepSleepIRQ(s_PintIRQ[gpioStateHandle->pin.pint.pintIndex]);
    }

    return kStatus_HAL_GpioSuccess;
#else
    assert(gpioHandle);

    (void)gpioHandle;
    (void)enable;

    return kStatus_HAL_GpioError;
#endif
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
