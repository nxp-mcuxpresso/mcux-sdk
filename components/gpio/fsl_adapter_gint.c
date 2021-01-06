/*
 * Copyright 2018 - 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_gint.h"
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
    hal_gpio_callback_t callback;
    hal_gpio_pin_t pin;
    int8_t gintInstance;
    int8_t gintInitialized;
} hal_gpio_state_t;

/* MISRA C-2012 Rule 11.1 */
typedef union _gint_callback_conv
{
    gint_cb_t gint_callback;
    hal_gpio_callback_t gpio_callback;
} gint_callback_conv_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

static uint8_t s_GINT_initialized = 0;
static uint8_t s_GINT_usedFlag    = 0;

#define SET_GINT_USED_FLAG(x)   (s_GINT_usedFlag |= 1U << (x))
#define GET_GINT_USED_FLAG(x)   ((0U != (s_GINT_usedFlag & (1U << (x)))) ? 1U : 0U)
#define CLEAR_GINT_USED_FLAG(x) (s_GINT_usedFlag &= ~(1U << (x)))

/*******************************************************************************
 * Code
 ******************************************************************************/
void HAL_GpioPreInit(void)
{
    s_GINT_initialized = 0U;
    s_GINT_usedFlag    = 0U;
}

hal_gpio_status_t HAL_GpioInit(hal_gpio_handle_t gpioHandle, hal_gpio_pin_config_t *pinConfig)
{
    hal_gpio_state_t *gpioStateHandle;

    assert(gpioHandle);
    assert(pinConfig);

    gpioStateHandle = (hal_gpio_state_t *)gpioHandle;

    gpioStateHandle->gintInitialized = 0;

    /* Check if the direction is vaild! */
    if (kHAL_GpioDirectionOut == pinConfig->direction)
    {
        return kStatus_HAL_GpioError;
    }

    /* Get first unused instance */
    gpioStateHandle->gintInstance = -1;
    for (int8_t i = 0; i < FSL_FEATURE_SOC_GINT_COUNT; i++)
    {
        if (0U == GET_GINT_USED_FLAG((uint32_t)i))
        {
            gpioStateHandle->gintInstance = i;
            SET_GINT_USED_FLAG((uint8_t)i);
            break;
        }
    }
    if (-1 == gpioStateHandle->gintInstance)
    {
        return kStatus_HAL_GpioError;
    }

    /* Check if the port is vaild! */
#if defined(FSL_FEATURE_GINT_PORT_COUNT)
    if (pinConfig->port >= FSL_FEATURE_GINT_PORT_COUNT)
    {
        return kStatus_HAL_GpioError;
    }
#else
    if (pinConfig->port >= 2U)
    {
        return kStatus_HAL_GpioError;
    }
#endif

    gpioStateHandle->pin.pin       = pinConfig->pin;
    gpioStateHandle->pin.port      = pinConfig->port;
    gpioStateHandle->pin.direction = (uint16_t)pinConfig->direction;

    gpioStateHandle->gintInitialized = 1;

    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioDeinit(hal_gpio_handle_t gpioHandle)
{
    hal_gpio_state_t *gpioStateHandle;
    GINT_Type *gintList[] = GINT_BASE_PTRS;

    assert(gpioHandle);

    gpioStateHandle = (hal_gpio_state_t *)gpioHandle;

    /* Disable callBack */
    GINT_DisableCallback(gintList[gpioStateHandle->gintInstance]);
    /* Disbale mask */
    GINT_ConfigPins(gintList[gpioStateHandle->gintInstance], (gint_port_t)gpioStateHandle->pin.port, 0, 0);
    /* Relase the instance */
    CLEAR_GINT_USED_FLAG((uint8_t)gpioStateHandle->gintInstance);

    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioInstallCallback(hal_gpio_handle_t gpioHandle,
                                          hal_gpio_callback_t callback,
                                          void *callbackParam)
{
    hal_gpio_state_t *gpioStateHandle;
    GINT_Type *gintList[] = GINT_BASE_PTRS;

    assert(gpioHandle);
    assert(callback);

    gpioStateHandle = (hal_gpio_state_t *)gpioHandle;

    assert(0 != gpioStateHandle->gintInitialized);

    gpioStateHandle->callback = callback;

    GINT_EnableCallback(gintList[gpioStateHandle->gintInstance]);
    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioGetTriggerMode(hal_gpio_handle_t gpioHandle, hal_gpio_interrupt_trigger_t *gpioTrigger)
{
    hal_gpio_state_t *gpioStateHandle;

    assert(gpioHandle);
    assert(gpioTrigger);

    gpioStateHandle = (hal_gpio_state_t *)gpioHandle;

    *gpioTrigger = (hal_gpio_interrupt_trigger_t)gpioStateHandle->pin.trigger;

    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioSetTriggerMode(hal_gpio_handle_t gpioHandle, hal_gpio_interrupt_trigger_t gpioTrigger)
{
    hal_gpio_state_t *gpioStateHandle;
    GINT_Type *gintList[] = GINT_BASE_PTRS;
    gint_trig_t triggerType;
    uint32_t polarityMask;
    uint32_t enableMask;
    gint_callback_conv_t gintCallbackConv;

    assert(gpioHandle);

    gpioStateHandle = (hal_gpio_state_t *)gpioHandle;

    assert(0 != gpioStateHandle->gintInitialized);
    assert((uint16_t)kHAL_GpioDirectionOut != gpioStateHandle->pin.direction);

    switch (gpioTrigger)
    {
        case kHAL_GpioInterruptLogicZero:
            triggerType  = kGINT_TrigLevel;
            polarityMask = ~((uint32_t)1U << gpioStateHandle->pin.pin);
            enableMask   = ((uint32_t)1U << gpioStateHandle->pin.pin);
            break;
        case kHAL_GpioInterruptLogicOne:
            triggerType  = kGINT_TrigLevel;
            polarityMask = ((uint32_t)1U << gpioStateHandle->pin.pin);
            enableMask   = ((uint32_t)1U << gpioStateHandle->pin.pin);
            break;
        case kHAL_GpioInterruptRisingEdge:
            triggerType  = kGINT_TrigEdge;
            polarityMask = ((uint32_t)1U << gpioStateHandle->pin.pin);
            enableMask   = ((uint32_t)1U << gpioStateHandle->pin.pin);
            break;
        case kHAL_GpioInterruptFallingEdge:
            triggerType  = kGINT_TrigEdge;
            polarityMask = ~((uint32_t)1U << gpioStateHandle->pin.pin);
            enableMask   = ((uint32_t)1U << gpioStateHandle->pin.pin);
            break;
        default:
            enableMask = 0U;
            break;
    }

    /* Not vaild trigger type */
    if (0U == enableMask)
    {
        return kStatus_HAL_GpioError;
    }

    gpioStateHandle->pin.trigger = (uint16_t)gpioTrigger;

    /* Initialize PINT, GINTn share the same reset slot! */
    if (0U == s_GINT_initialized)
    {
        s_GINT_initialized = 1U;
        GINT_Init(gintList[gpioStateHandle->gintInstance]);
    }

    /* Set trigger type to GINT */
    gintCallbackConv.gpio_callback = gpioStateHandle->callback;
    GINT_SetCtrl(gintList[gpioStateHandle->gintInstance], kGINT_CombineOr, triggerType, gintCallbackConv.gint_callback);
    GINT_ConfigPins(gintList[gpioStateHandle->gintInstance], (gint_port_t)gpioStateHandle->pin.port, polarityMask,
                    enableMask);

    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioWakeUpSetting(hal_gpio_handle_t gpioHandle, uint8_t enable)
{
#if (defined(FSL_FEATURE_SOC_SYSCON_COUNT) && (FSL_FEATURE_SOC_SYSCON_COUNT > 0)) && \
    (!(defined(FSL_FEATURE_SYSCON_STARTER_DISCONTINUOUS) && FSL_FEATURE_SYSCON_STARTER_DISCONTINUOUS))

    hal_gpio_state_t *gpioStateHandle;
    IRQn_Type gintIRQ[] = GINT_IRQS;

    assert(gpioHandle);

    gpioStateHandle = (hal_gpio_state_t *)gpioHandle;

    assert(0 != gpioStateHandle->gintInitialized);
    assert((uint16_t)kHAL_GpioDirectionOut != gpioStateHandle->pin.direction);

    if (enable)
    {
        EnableDeepSleepIRQ(gintIRQ[gpioStateHandle->gintInstance]);
    }
    else
    {
        DisableDeepSleepIRQ(gintIRQ[gpioStateHandle->gintInstance]);
    }

    return kStatus_HAL_GpioSuccess;
#else
    assert(gpioHandle);

    (void)gpioHandle;
    (void)enable;

    return kStatus_HAL_GpioError;
#endif
}

hal_gpio_status_t HAL_GpioGetInput(hal_gpio_handle_t gpioHandle, uint8_t *pinState)
{
    assert(gpioHandle);

    /* MISRA C-2012 Rule 8.6 */

    return kStatus_HAL_GpioError;
}

hal_gpio_status_t HAL_GpioSetOutput(hal_gpio_handle_t gpioHandle, uint8_t pinState)
{
    assert(gpioHandle);

    /* MISRA C-2012 Rule 8.6 */

    return kStatus_HAL_GpioError;
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

/*******************************************************************************
 * Code
 ******************************************************************************/

/* The code below is reserved!*/

#if 0
static void HAL_GpioInterruptCallback(void)
{
    hal_gpio_state_t *head = s_GpioHead;
    uint32_t polarityMask, enableMask, pinMask;
    uint8_t pinState;
    GPIO_Type *gpioList[]           = GPIO_BASE_PTRS;

    /* Check which pin is actived */
    while (head)
    {
        GINT_GetConfigPins(GINT0, head->pin.port, &polarityMask, &enableMask);
        pinMask = 1 << head->pin.pin;
        if (0 != (enableMask & pinMask))
        {
            //HAL_GpioGetInput(head, &pinState);
            //pinState = GPIO_PinRead(gpioList[0], head->pin.port, head->pin.pin);
            pinState = (GPIO_PinRead(gpioList[0], head->pin.port, head->pin.pin) ? 1 : 0);
            if((polarityMask & pinMask) == (pinState << head->pin.pin))
            {
                if ((NULL != head->callback))
                {
                    head->callback(NULL);
                }
            }
        }
        head = head->next;
    }
}

static hal_gpio_status_t HAL_GpioConflictSearch(hal_gpio_state_t *head, uint8_t port, uint8_t pin)
{
    while (head)
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
        while (p->next)
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
    while (p)
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

hal_gpio_status_t HAL_GpioInit(hal_gpio_handle_t gpioHandle, hal_gpio_pin_config_t *pinConfig)
{
    hal_gpio_state_t *gpioState;
    GPIO_Type *gpioList[]           = GPIO_BASE_PTRS;
    hal_gpio_status_t status        = kStatus_HAL_GpioSuccess;
    gpio_pin_config_t gpioPinconfig = {
        kGPIO_DigitalInput,
        0,
    };

    assert(gpioHandle);
    assert(pinConfig);

    if (HAL_GPIO_HANDLE_SIZE < sizeof(hal_gpio_state_t))
    {
        return kStatus_HAL_GpioError;
    }

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

    gpioState->pin.pin       = pinConfig->pin;
    gpioState->pin.port      = pinConfig->port;
    gpioState->pin.direction = pinConfig->direction;

    if (kHAL_GpioDirectionOut == pinConfig->direction)
    {
        gpioPinconfig.pinDirection = kGPIO_DigitalOutput;
    }
    else
    {
        gpioPinconfig.pinDirection = kGPIO_DigitalInput;
    }
    GPIO_PortInit(gpioList[0], pinConfig->port);
    GPIO_PinInit(gpioList[0], pinConfig->port, pinConfig->pin, &gpioPinconfig);

    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioDeinit(hal_gpio_handle_t gpioHandle)
{
    hal_gpio_state_t *gpioStateHandle;
    uint32_t polarityMask;
    uint32_t enableMask;

    assert(gpioHandle);

    gpioStateHandle = (hal_gpio_state_t *)gpioHandle;

    // Disable pin GINT
    GINT_GetConfigPins(GINT0, gpioStateHandle->pin.port, &polarityMask, &enableMask);
    enableMask &= ~(1 << gpioStateHandle->pin.pin);
    GINT_ConfigPins(GINT0, gpioStateHandle->pin.port, polarityMask, enableMask);

    if (NULL == gpioStateHandle->next)
    {
        GINT_DisableCallback(GINT0);
        /* Enable callbacks for GINT */
        if (s_GpioPintInitialized)
        {
            s_GpioPintInitialized = 0;
            /* Initialize GINT */
            GINT_Deinit(GINT0);
        }
    }

    HAL_GpioRemoveItem(&s_GpioHead, gpioStateHandle);
    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioGetInput(hal_gpio_handle_t gpioHandle, uint8_t *pinState)
{
    hal_gpio_state_t *gpioStateHandle;
    GPIO_Type *gpioList[] = GPIO_BASE_PTRS;

    assert(gpioHandle);

    gpioStateHandle = (hal_gpio_state_t *)gpioHandle;

    *pinState = ((GPIO_PinRead(gpioList[0], gpioStateHandle->pin.port, gpioStateHandle->pin.pin)) ? 1 : 0);
    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioSetOutput(hal_gpio_handle_t gpioHandle, uint8_t pinState)
{
    hal_gpio_state_t *gpioStateHandle;
    GPIO_Type *gpioList[] = GPIO_BASE_PTRS;

    assert(gpioHandle);

    gpioStateHandle = (hal_gpio_state_t *)gpioHandle;

    GPIO_PinWrite(gpioList[0], gpioStateHandle->pin.port, gpioStateHandle->pin.pin, (pinState) ? 1 : 0);
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

    if (!s_GpioPintInitialized)
    {
        GINT_EnableCallback(GINT0);
    }
    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioGetTriggerMode(hal_gpio_handle_t gpioHandle, hal_gpio_interrupt_trigger_t *gpioTrigger)
{
    hal_gpio_state_t *gpioStateHandle;

    assert(gpioHandle);

    gpioStateHandle = (hal_gpio_state_t *)gpioHandle;

    if (kHAL_GpioDirectionOut == gpioStateHandle->pin.direction)
    {
        return kStatus_HAL_GpioError;
    }

    *gpioTrigger = (hal_gpio_interrupt_trigger_t)gpioStateHandle->pin.trigger;
    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioSetTriggerMode(hal_gpio_handle_t gpioHandle, hal_gpio_interrupt_trigger_t gpioTrigger)
{
    hal_gpio_state_t *gpioStateHandle;
    gint_trig_t triggerType;
    uint32_t polarityMask;
    uint32_t enableMask;

    assert(gpioHandle);

    gpioStateHandle = (hal_gpio_state_t *)gpioHandle;

    if (kHAL_GpioDirectionOut == gpioStateHandle->pin.direction)
    {
        return kStatus_HAL_GpioError;
    }

    GINT_GetConfigPins(GINT0, gpioStateHandle->pin.port, &polarityMask, &enableMask);
    switch (gpioTrigger)
    {
        case kHAL_GpioInterruptLogicZero:
            triggerType = kGINT_TrigLevel;
            polarityMask &= ~(1 << gpioStateHandle->pin.pin);
            enableMask |= (1 << gpioStateHandle->pin.pin);
            break;
        case kHAL_GpioInterruptLogicOne:
            triggerType = kGINT_TrigLevel;
            polarityMask |= (1 << gpioStateHandle->pin.pin);
            enableMask |= (1 << gpioStateHandle->pin.pin);
            break;
        case kHAL_GpioInterruptRisingEdge:
            triggerType = kGINT_TrigEdge;
            polarityMask |= (1 << gpioStateHandle->pin.pin);
            enableMask |= (1 << gpioStateHandle->pin.pin);
            break;
        case kHAL_GpioInterruptFallingEdge:
            triggerType = kGINT_TrigEdge;
            polarityMask &= ~(1 << gpioStateHandle->pin.pin);
            enableMask |= (1 << gpioStateHandle->pin.pin);
            break;
        case kHAL_GpioInterruptEitherEdge:
            /* Not support! */
            return kStatus_HAL_GpioError;
        default:
            /* Not support! */
            return kStatus_HAL_GpioError;
    }

    gpioStateHandle->pin.trigger = (uint16_t)gpioTrigger;

    /* Enable callbacks for GINT */
    if (!s_GpioPintInitialized)
    {
        s_GpioPintInitialized = 1;
        /* Initialize PINT */
        GINT_Init(GINT0);
    }
    /* Set trigger type to GINT */
    GINT_SetCtrl(GINT0, kGINT_CombineOr, triggerType, HAL_GpioInterruptCallback);
    GINT_ConfigPins(GINT0, gpioStateHandle->pin.port, polarityMask, enableMask);

    return kStatus_HAL_GpioSuccess;
}

hal_gpio_status_t HAL_GpioWakeUpSetting(hal_gpio_handle_t gpioHandle, uint8_t enable)
{
    hal_gpio_state_t *gpioStateHandle;
    IRQn_Type gintIRQ[] = GINT_IRQS;
    assert(gpioHandle);

    gpioStateHandle = (hal_gpio_state_t *)gpioHandle;

    if (kHAL_GpioDirectionOut == gpioStateHandle->pin.direction)
    {
        return kStatus_HAL_GpioError;
    }
    if (enable)
    {
        EnableDeepSleepIRQ(gintIRQ[0]);
    }
    else
    {
        DisableDeepSleepIRQ(gintIRQ[0]);
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
#endif
