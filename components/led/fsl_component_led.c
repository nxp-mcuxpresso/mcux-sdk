/*
 * Copyright 2018 - 2019 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_adapter_gpio.h"
#include "fsl_component_timer_manager.h"

#include "fsl_component_led.h"
#if (defined(LED_DIMMING_ENABLEMENT) && (LED_DIMMING_ENABLEMENT > 0U))
#include "fsl_adapter_pwm.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#if defined(OSA_USED)
#include "fsl_os_abstraction.h"
#if (defined(USE_RTOS) && (USE_RTOS > 0U))
#define LED_ENTER_CRITICAL() \
    OSA_SR_ALLOC();          \
    OSA_ENTER_CRITICAL()
#define LED_EXIT_CRITICAL() OSA_EXIT_CRITICAL()
#else
#define LED_ENTER_CRITICAL()
#define LED_EXIT_CRITICAL()
#endif
#else
#define LED_ENTER_CRITICAL() uint32_t regPrimask = DisableGlobalIRQ();
#define LED_EXIT_CRITICAL()  EnableGlobalIRQ(regPrimask);
#endif

/* LED control type enumeration */
typedef enum _led_control_type
{
    kLED_TurnOffOn = 0x01U, /*!< Turn Off or on*/
    kLED_Flash,             /*!< Flash */
#if (defined(LED_COLOR_WHEEL_ENABLEMENT) && (LED_COLOR_WHEEL_ENABLEMENT > 0U))
    kLED_TricolorCycleFlash, /*!< Tricolor Cycle Flash */
    kLED_CycleFlash,         /*!< Cycle Flash */
#endif                       /* (defined(LED_COLOR_WHEEL_ENABLEMENT) && (LED_COLOR_WHEEL_ENABLEMENT > 0U)) */
    kLED_Dimming,            /*!< Dimming */
} led_control_type_t;

/* LED Dimming state structure when dimming is enabled */
typedef struct _led_dimming
{
    uint8_t increasement;
    uint8_t powerDelta[sizeof(led_config_t) / sizeof(led_pin_config_t)];
} led_dimming_t;

/*! @brief The pin config struct of LED */
typedef struct _led_pin
{
    union
    {
        struct
        {
            uint16_t type : 2U;          /*!< LED type, 1 - RGB, 2 - Monochrome */
            uint16_t dimmingEnable : 1U; /*!< dimming enable, 0 - disable, 1 - enable */
            uint16_t : 13U;
        } config;
        struct
        {
            uint16_t : 3U;
            uint16_t port : 4U;            /*!< GPIO Port */
            uint16_t pin : 5U;             /*!< GPIO Pin */
            uint16_t pinStateDefault : 1U; /*!< GPIO Pin voltage when LED is off (0 - low level, 1 - high level)*/
            uint16_t : 3U;
        } gpio;
        struct
        {
            uint16_t : 3U;
            uint16_t instance : 4U;        /*!< PWM instance of the pin */
            uint16_t channel : 5U;         /*!< PWM channel of the pin */
            uint16_t pinStateDefault : 1U; /*!< The Pin voltage when LED is off (0 - low level, 1 - high level)*/
            uint16_t : 3U;
        } dimming;
    };
} led_pin_t;

/* LED state structure */
typedef struct _led_state
{
    struct _led_state *next;
    uint32_t gpioHandle[sizeof(led_config_t) / sizeof(led_pin_config_t)]
                       [((HAL_GPIO_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t))];
    volatile uint32_t expiryPeriodCount;
#if (defined(LED_DIMMING_ENABLEMENT) && (LED_DIMMING_ENABLEMENT > 0U))
    uint32_t pwmHandle[sizeof(led_config_t) / sizeof(led_pin_config_t)]
                      [((HAL_PWM_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t))];
#endif
    uint32_t flashCycle;
    led_color_t settingColor;
    led_color_t currentColor;
    led_color_t nextColor;
#if (defined(LED_USE_CONFIGURE_STRUCTURE) && (LED_USE_CONFIGURE_STRUCTURE > 0U))
    led_config_t *pinsConfig;
#else
    led_pin_t pins[sizeof(led_config_t) / sizeof(led_pin_config_t)];
#endif
    uint16_t flashPeriod;
#if (defined(LED_DIMMING_ENABLEMENT) && (LED_DIMMING_ENABLEMENT > 0U))
    led_dimming_t dimming;
#endif
    struct
    {
        uint16_t controlType : 4U;
#if (defined(LED_COLOR_WHEEL_ENABLEMENT) && (LED_COLOR_WHEEL_ENABLEMENT > 0U))
        uint16_t flashCount : 3U;
#endif
        uint16_t : 1U;
        uint16_t flashDuty : 7U;
        uint16_t : 1U;
    };
} led_state_t;

typedef struct _led_list
{
    led_state_t *ledState;
    volatile uint32_t periodCount;
    TIMER_MANAGER_HANDLE_DEFINE(timerHandle);
} led_list_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static led_list_t s_ledList;

/*******************************************************************************
 * Code
 ******************************************************************************/
#if defined(__IAR_SYSTEMS_ICC__)
#pragma inline   = never
#pragma optimize = no_inline
#elif defined(__GNUC__)
#endif

static led_status_t LED_SetStatus(led_state_t *ledState, led_color_t color, uint32_t threshold)
{
#if (defined(LED_USE_CONFIGURE_STRUCTURE) && (LED_USE_CONFIGURE_STRUCTURE > 0U))
    led_pin_config_t *ledRgbPin;
#else
    led_pin_t *ledRgbPin;
#endif
    led_status_t status = kStatus_LED_Success;
    led_color_t colorSet;
    uint8_t count = 1;

    ledState->expiryPeriodCount = s_ledList.periodCount + threshold;

#if (defined(LED_USE_CONFIGURE_STRUCTURE) && (LED_USE_CONFIGURE_STRUCTURE > 0U))
    ledRgbPin = (led_pin_config_t *)(void *)&ledState->pinsConfig->ledRgb;
#else
    ledRgbPin = (led_pin_t *)ledState->pins;
#endif

#if (defined(LED_USE_CONFIGURE_STRUCTURE) && (LED_USE_CONFIGURE_STRUCTURE > 0U))
    if (kLED_TypeRgb == ledState->pinsConfig->type)
#else
    if ((uint16_t)kLED_TypeRgb == ledRgbPin->config.type)
#endif
    {
        count = sizeof(led_config_t) / sizeof(led_pin_config_t);
    }

    for (uint8_t i = 0; i < count; i++)
    {
        colorSet = ((color >> (i * 8U)) & (0xFFU));
#if (defined(LED_DIMMING_ENABLEMENT) && (LED_DIMMING_ENABLEMENT > 0U))
#if (defined(LED_USE_CONFIGURE_STRUCTURE) && (LED_USE_CONFIGURE_STRUCTURE > 0U))
        if (0U != ledRgbPin[i].dimmingEnable)
#else
        if (0U != ledRgbPin[i].config.dimmingEnable)
#endif
        {
            (void)HAL_PwmUpdateDutycycle(ledState->pwmHandle[i], (uint8_t)ledRgbPin[i].dimming.channel,
                                         kHAL_EdgeAlignedPwm, (uint8_t)(colorSet * 100U / 255U));
        }
        else
#endif
        {
#if (defined(LED_USE_CONFIGURE_STRUCTURE) && (LED_USE_CONFIGURE_STRUCTURE > 0U))
            (void)HAL_GpioSetOutput(ledState->gpioHandle[i], (colorSet != 0U) ?
                                                                 (1U - (uint8_t)ledRgbPin[i].gpio.level) :
                                                                 (uint8_t)ledRgbPin[i].gpio.level);
#else
            (void)HAL_GpioSetOutput(ledState->gpioHandle[i], (colorSet != 0U) ?
                                                                 (1U - (uint8_t)ledRgbPin[i].gpio.pinStateDefault) :
                                                                 (uint8_t)ledRgbPin[i].gpio.pinStateDefault);
#endif
        }
    }

    return status;
}

static void LED_TimerEvent(void *param)
{
    led_state_t *ledState = (led_state_t *)s_ledList.ledState;
    uint32_t threshold    = 0;
    led_color_t color;
#if (defined(LED_DIMMING_ENABLEMENT) && (LED_DIMMING_ENABLEMENT > 0U))
    uint16_t power[sizeof(led_config_t) / sizeof(led_pin_config_t)];
    uint8_t count = sizeof(led_config_t) / sizeof(led_pin_config_t);
#endif

    s_ledList.periodCount += LED_TIMER_INTERVAL;

    while (NULL != ledState)
    {
        if (s_ledList.periodCount >= ledState->expiryPeriodCount)
        {
            switch (ledState->controlType)
            {
                case (uint16_t)kLED_Flash: /*!< Flash */
#if (defined(LED_COLOR_WHEEL_ENABLEMENT) && (LED_COLOR_WHEEL_ENABLEMENT > 0U))
                case (uint16_t)kLED_TricolorCycleFlash: /*!< Tricolor Cycle Flash */
                case (uint16_t)kLED_CycleFlash:         /*!< Cycle Flash */
#endif /* (defined(LED_COLOR_WHEEL_ENABLEMENT) && (LED_COLOR_WHEEL_ENABLEMENT > 0U)) */
                    if (LED_FLASH_CYCLE_FOREVER != ledState->flashCycle)
                    {
                        if ((0U != ledState->flashCycle))
                        {
                            if (((led_color_t)kLED_Black == ledState->currentColor) || (100U == ledState->flashDuty))
                            {
                                ledState->flashCycle--;
                            }
                        }
                    }
                    if (0U != ledState->flashCycle)
                    {
                        if ((100U > ledState->flashDuty))
                        {
                            color                  = ledState->nextColor;
                            ledState->nextColor    = ledState->currentColor;
                            ledState->currentColor = color;
                        }

                        if (((led_color_t)kLED_Black == ledState->currentColor))
                        {
                            threshold = (uint32_t)ledState->flashPeriod * (100U - (uint32_t)ledState->flashDuty) / 100U;
                        }
                        else
                        {
#if (defined(LED_COLOR_WHEEL_ENABLEMENT) && (LED_COLOR_WHEEL_ENABLEMENT > 0U))
                            ledState->flashCount++;
                            if ((uint16_t)kLED_TricolorCycleFlash == ledState->controlType)
                            {
                                ledState->currentColor = (led_color_t)(0xFFUL << ((ledState->flashCount % 3U) * 8U));
                            }
                            else if ((uint16_t)kLED_CycleFlash == ledState->controlType)
                            {
                                color = 0;
                                if (0U == ((ledState->flashCount) & 0x07U))
                                {
                                    (ledState->flashCount)++;
                                }
                                if (0U != ((ledState->flashCount) & 0x04U))
                                {
                                    color = (led_color_t)0xFF0000;
                                }
                                if (0U != ((ledState->flashCount) & 0x02U))
                                {
                                    color |= (led_color_t)0xFF00;
                                }
                                if (0U != ((ledState->flashCount) & 0x01U))
                                {
                                    color |= (led_color_t)0xFF;
                                }
                                ledState->currentColor = color;
                            }
                            else
                            {
                                /*Misra Rule 15.7*/
                            }
#endif /* (defined(LED_COLOR_WHEEL_ENABLEMENT) && (LED_COLOR_WHEEL_ENABLEMENT > 0U)) */
                            threshold = (uint32_t)ledState->flashPeriod * (uint32_t)(ledState->flashDuty) / 100U;
                        }

                        (void)LED_SetStatus(ledState, ledState->currentColor, threshold);
                    }
                    break;
#if (defined(LED_DIMMING_ENABLEMENT) && (LED_DIMMING_ENABLEMENT > 0U))
                case (uint16_t)kLED_Dimming: /*!< Dimming */
                    for (uint8_t i = 0; i < count; i++)
                    {
                        uint8_t value = (uint8_t)((ledState->currentColor >> (8U * i)) & 0xFFU);
                        if (0U != ledState->dimming.increasement)
                        {
                            if ((value + ledState->dimming.powerDelta[i]) < 0xFFU)
                            {
                                power[i] = (uint16_t)value + (uint16_t)ledState->dimming.powerDelta[i];
                            }
                            else
                            {
                                power[i] = 0xFFU;
                            }
                        }
                        else
                        {
                            if (value > ledState->dimming.powerDelta[i])
                            {
                                power[i] = (uint16_t)value - (uint16_t)ledState->dimming.powerDelta[i];
                            }
                            else
                            {
                                power[i] = 0;
                            }
                        }

#if (defined(LED_USE_CONFIGURE_STRUCTURE) && (LED_USE_CONFIGURE_STRUCTURE > 0U))
                        if (kLED_TypeMonochrome == ledState->pinsConfig->type)
#else
                        if ((uint16_t)kLED_TypeMonochrome == ledState->pins[0].config.type)
#endif
                        {
                            break;
                        }
                    }
                    ledState->currentColor = LED_MAKE_COLOR(power[0], power[1], power[2]);
                    (void)LED_SetStatus(ledState, ledState->currentColor, ledState->flashPeriod);
                    break;
#endif
                default:
                    /* MISRA Rule 16.4*/
                    break;
            }
        }
        ledState = ledState->next;
    }
}

led_status_t LED_Init(led_handle_t ledHandle, led_config_t *ledConfig)
{
    led_state_t *ledState;
    led_pin_config_t *ledRgbConfigPin;
#if (defined(LED_USE_CONFIGURE_STRUCTURE) && (LED_USE_CONFIGURE_STRUCTURE > 0U))
#else
    hal_gpio_pin_config_t controlPin;
#endif
    uint32_t count = 1;
    uint32_t regPrimask;
    int i;
#if (defined(LED_DIMMING_ENABLEMENT) && (LED_DIMMING_ENABLEMENT > 0U))
    /* The configure parameters check only work on debug mode in order to reduce code size. */
#ifdef NDEBUG
#else  /* NDEBUG */
    uint8_t rgbFlag = 0;
    uint8_t rgbDimmingFlag = 0;
#endif /* NDEBUG */
#endif

    assert((NULL != ledHandle) && (NULL != ledConfig));
    assert(LED_HANDLE_SIZE >= sizeof(led_state_t));

    if (kLED_TypeRgb == ledConfig->type)
    {
        count = sizeof(led_config_t) / sizeof(led_pin_config_t);
    }

    ledState = (led_state_t *)ledHandle;

    (void)memset(ledHandle, 0, sizeof(led_state_t));

    regPrimask = DisableGlobalIRQ();
    if (NULL == s_ledList.ledState)
    {
        do
        {
            timer_status_t tmState;
            tmState = TM_Open((timer_handle_t)s_ledList.timerHandle);
            assert(kStatus_TimerSuccess == tmState);

            tmState = TM_InstallCallback(s_ledList.timerHandle, LED_TimerEvent, &s_ledList);
            assert(kStatus_TimerSuccess == tmState);

            tmState = TM_Start(s_ledList.timerHandle, (uint8_t)kTimerModeIntervalTimer, LED_TIMER_INTERVAL);
            assert(kStatus_TimerSuccess == tmState);
            (void)tmState;

            s_ledList.ledState = ledState;
        } while (false);
    }
    else
    {
        ledState->next     = s_ledList.ledState;
        s_ledList.ledState = ledState;
    }
    EnableGlobalIRQ(regPrimask);

    assert(s_ledList.ledState);
    ledState->settingColor = (led_color_t)kLED_White;
    ledRgbConfigPin        = (led_pin_config_t *)(void *)&ledConfig->ledRgb;

#if (defined(LED_USE_CONFIGURE_STRUCTURE) && (LED_USE_CONFIGURE_STRUCTURE > 0U))
    ledState->pinsConfig = ledConfig;
#else
    controlPin.direction = kHAL_GpioDirectionOut;
#endif
#if (defined(LED_DIMMING_ENABLEMENT) && (LED_DIMMING_ENABLEMENT > 0U))
    /* The configure parameters check only work on debug mode in order to reduce code size. */
#ifdef NDEBUG
#else  /* NDEBUG */
    for (i = 0; i < (int)count; i++)
    {
        if (0U != ledRgbConfigPin[i].dimmingEnable)
        {
            rgbDimmingFlag = 1;
        }
        else
        {
            rgbFlag = 1;
        }
    }
    assert(!((0U != rgbDimmingFlag) && (0U != rgbFlag)));
#endif /* NDEBUG */
#endif
    for (i = 0; i < (int)count; i++)
    {
#if (defined(LED_USE_CONFIGURE_STRUCTURE) && (LED_USE_CONFIGURE_STRUCTURE > 0U))
#else
        ledState->pins[i].config.type = (uint16_t)ledConfig->type;
#endif
#if (defined(LED_DIMMING_ENABLEMENT) && (LED_DIMMING_ENABLEMENT > 0U))
        if (0U != ledRgbConfigPin[i].dimmingEnable)
        {
            hal_pwm_setup_config_t setupConfig;
#if (defined(LED_USE_CONFIGURE_STRUCTURE) && (LED_USE_CONFIGURE_STRUCTURE > 0U))
#else
            ledState->pins[i].config.dimmingEnable = ledRgbConfigPin[i].dimmingEnable;
            ledState->pins[i].dimming.instance = ledRgbConfigPin[i].dimming.instance;
            ledState->pins[i].dimming.channel = ledRgbConfigPin[i].dimming.channel;
            ledState->pins[i].dimming.pinStateDefault = ledRgbConfigPin[i].dimming.pinStateDefault;
#endif
            (void)HAL_PwmInit((hal_pwm_handle_t)ledState->pwmHandle[i], ledRgbConfigPin[i].dimming.instance,
                              ledRgbConfigPin[i].dimming.sourceClock);
            setupConfig.dutyCyclePercent = 0;
            setupConfig.level            = (0U != ledRgbConfigPin[i].dimming.pinStateDefault) ?
                                    (hal_pwm_level_select_t)kHAL_PwmLowTrue :
                                    (hal_pwm_level_select_t)kHAL_PwmHighTrue;
            setupConfig.mode       = kHAL_EdgeAlignedPwm;
            setupConfig.pwmFreq_Hz = 1000U;
            (void)HAL_PwmSetupPwm(ledState->pwmHandle[i], ledRgbConfigPin[i].dimming.channel, &setupConfig);
        }
        else
#endif
        {
#if (defined(LED_USE_CONFIGURE_STRUCTURE) && (LED_USE_CONFIGURE_STRUCTURE > 0U))
#else
            ledState->pins[i].gpio.port            = ledRgbConfigPin[i].gpio.port;
            ledState->pins[i].gpio.pin             = ledRgbConfigPin[i].gpio.pin;
            ledState->pins[i].gpio.pinStateDefault = ledRgbConfigPin[i].gpio.pinStateDefault;
            controlPin.port                        = ledRgbConfigPin[i].gpio.port;
            controlPin.pin                         = ledRgbConfigPin[i].gpio.pin;
            controlPin.level                       = ledRgbConfigPin[i].gpio.pinStateDefault;
#endif

#if (defined(LED_USE_CONFIGURE_STRUCTURE) && (LED_USE_CONFIGURE_STRUCTURE > 0U))
            if (kStatus_HAL_GpioSuccess != HAL_GpioInit((hal_gpio_handle_t)ledState->gpioHandle[i],
                                                        (hal_gpio_pin_config_t *)&ledRgbConfigPin[i].gpio))
#else
            if (kStatus_HAL_GpioSuccess != HAL_GpioInit((hal_gpio_handle_t)ledState->gpioHandle[i], &controlPin))
#endif
            {
                return kStatus_LED_Error;
            }
        }
    }

    return LED_TurnOnOff(ledState, 0);
}

led_status_t LED_Deinit(led_handle_t ledHandle)
{
    led_state_t *ledState;
    led_state_t *ledStatePre;
    uint32_t regPrimask;
#if (defined(LED_DIMMING_ENABLEMENT) && (LED_DIMMING_ENABLEMENT > 0U))
#if (defined(LED_USE_CONFIGURE_STRUCTURE) && (LED_USE_CONFIGURE_STRUCTURE > 0U))
    led_pin_config_t *ledRgbPin;
#else
    led_pin_t *ledRgbPin;
#endif
#endif

    assert(ledHandle);

    ledState = (led_state_t *)ledHandle;

    regPrimask  = DisableGlobalIRQ();
    ledStatePre = s_ledList.ledState;
    if (ledStatePre != ledState)
    {
        while ((NULL != ledStatePre) && (ledStatePre->next != ledState))
        {
            ledStatePre = ledStatePre->next;
        }
        if (NULL != ledStatePre)
        {
            ledStatePre->next = ledState->next;
        }
    }
    else
    {
        s_ledList.ledState = ledState->next;
    }

    if (NULL == s_ledList.ledState)
    {
        (void)TM_Close(s_ledList.timerHandle);
    }
    EnableGlobalIRQ(regPrimask);

#if (defined(LED_DIMMING_ENABLEMENT) && (LED_DIMMING_ENABLEMENT > 0U))
#if (defined(LED_USE_CONFIGURE_STRUCTURE) && (LED_USE_CONFIGURE_STRUCTURE > 0U))
    ledRgbPin = (led_pin_config_t *)(void *)&ledState->pinsConfig->ledRgb;
#else
    ledRgbPin = (led_pin_t *)(ledState->pins);
#endif
#endif
    for (uint32_t i = 0; i < (sizeof(led_config_t) / sizeof(led_pin_config_t)); i++)
    {
#if (defined(LED_DIMMING_ENABLEMENT) && (LED_DIMMING_ENABLEMENT > 0U))
#if (defined(LED_USE_CONFIGURE_STRUCTURE) && (LED_USE_CONFIGURE_STRUCTURE > 0U))
        if (0U != ledRgbPin[i].dimmingEnable)
#else
        if (0u != ledRgbPin[i].config.dimmingEnable)
#endif
        {
            HAL_PwmDeinit(ledState->pwmHandle[i]);
        }
        else
#endif
        {
            (void)HAL_GpioDeinit(ledState->gpioHandle[i]);
        }
#if (defined(LED_USE_CONFIGURE_STRUCTURE) && (LED_USE_CONFIGURE_STRUCTURE > 0U))
        if (kLED_TypeRgb != ledState->pinsConfig->type)
#else
        if (((uint16_t)kLED_TypeRgb != ledState->pins[i].config.type))
#endif
        {
            break;
        }
    }

    return kStatus_LED_Success;
}

led_status_t LED_TurnOnOff(led_handle_t ledHandle, uint8_t turnOnOff)
{
    led_state_t *ledState;

    assert(ledHandle);

    ledState               = (led_state_t *)ledHandle;
    ledState->controlType  = (uint16_t)kLED_TurnOffOn;
    ledState->currentColor = (1U == turnOnOff) ? ledState->settingColor : (led_color_t)kLED_Black;
    (void)LED_SetStatus(ledState, ledState->currentColor, 0);
    return kStatus_LED_Success;
}

led_status_t LED_SetColor(led_handle_t ledHandle, led_color_t ledRgbColor)
{
    led_state_t *ledState;

    assert(ledHandle);

    ledState = (led_state_t *)ledHandle;
#if (defined(LED_USE_CONFIGURE_STRUCTURE) && (LED_USE_CONFIGURE_STRUCTURE > 0U))
    assert(kLED_TypeRgb == ledState->pinsConfig->type);
#else
    assert((uint16_t)kLED_TypeRgb == ledState->pins[0].config.type);
#endif

    ledState->settingColor = ledRgbColor;

    return kStatus_LED_Success;
}

led_status_t LED_Flash(led_handle_t ledHandle, led_flash_config_t *ledFlash)
{
    led_state_t *ledState;

    assert(ledHandle);
    assert(ledFlash);
    assert(ledFlash->times);
    assert(ledFlash->duty <= 100U);

    ledState = (led_state_t *)ledHandle;

    ledState->flashPeriod = ledFlash->period;
    ledState->flashDuty   = ledFlash->duty;

    ledState->currentColor = ledState->settingColor;
    ledState->flashCycle   = ledFlash->times;
    ledState->nextColor    = (led_color_t)kLED_Black;

#if (defined(LED_COLOR_WHEEL_ENABLEMENT) && (LED_COLOR_WHEEL_ENABLEMENT > 0U))
    if (kLED_FlashOneColor == ledFlash->flashType)
    {
        ledState->controlType = (uint16_t)kLED_Flash;
    }
    else
    {
#if (defined(LED_USE_CONFIGURE_STRUCTURE) && (LED_USE_CONFIGURE_STRUCTURE > 0U))
        assert(kLED_TypeRgb == ledState->pinsConfig->type);
#else
        assert((uint16_t)kLED_TypeRgb == ledState->pins[0].config.type);
#endif
        ledState->controlType = (uint16_t)kLED_CycleFlash;
    }
#else
    ledState->controlType = (uint16_t)kLED_Flash;
#endif /* (defined(LED_COLOR_WHEEL_ENABLEMENT) && (LED_COLOR_WHEEL_ENABLEMENT > 0U)) */
    (void)LED_SetStatus(ledState, ledState->currentColor,
                        ((uint32_t)ledState->flashPeriod * (uint32_t)ledState->flashDuty) / 100U);
    return kStatus_LED_Success;
}

led_status_t LED_Blip(led_handle_t ledHandle)
{
    led_flash_config_t ledFlash;

    ledFlash.duty      = 50;
    ledFlash.flashType = kLED_FlashOneColor;
    ledFlash.period    = LED_BLIP_INTERVAL;
    ledFlash.times     = 1;
    return LED_Flash(ledHandle, &ledFlash);
}

led_status_t LED_Dimming(led_handle_t ledHandle, uint16_t dimmingPeriod, uint8_t increasement)
{
#if (defined(LED_DIMMING_ENABLEMENT) && (LED_DIMMING_ENABLEMENT > 0U))
    led_state_t *ledState;
    uint16_t power[sizeof(led_config_t) / sizeof(led_pin_config_t)];
    uint8_t value;
    uint8_t count = sizeof(led_config_t) / sizeof(led_pin_config_t);

    assert(ledHandle);
    assert(dimmingPeriod);

    ledState = (led_state_t *)ledHandle;

#if (defined(LED_USE_CONFIGURE_STRUCTURE) && (LED_USE_CONFIGURE_STRUCTURE > 0U))
    assert(ledState->pinsConfig->ledRgb.redPin.dimmingEnable);
#else
    assert(ledState->pins[0].config.dimmingEnable);
#endif

    LED_ENTER_CRITICAL();

    ledState->controlType          = (uint16_t)kLED_Dimming;
    ledState->flashPeriod          = LED_DIMMING_UPDATE_INTERVAL;
    ledState->flashDuty            = 100U;
    ledState->dimming.increasement = increasement;

#if (defined(LED_USE_CONFIGURE_STRUCTURE) && (LED_USE_CONFIGURE_STRUCTURE > 0U))
    if (kLED_TypeRgb == ledState->pinsConfig->type)
#else
    if ((uint16_t)kLED_TypeRgb == ledState->pins[0].config.type)
#endif
    {
        ledState->currentColor = ledState->settingColor;
    }

    for (uint8_t i = 0U; i < count; i++)
    {
        ledState->dimming.powerDelta[i] = 0U;
    }

    for (uint8_t i = 0U; i < count; i++)
    {
        value = (uint8_t)((ledState->currentColor >> (8U * (i))) & 0xFFU);
        if (0U != ledState->dimming.increasement)
        {
            ledState->dimming.powerDelta[i] =
                (uint8_t)(((uint16_t)0xFF - value) * LED_DIMMING_UPDATE_INTERVAL / (dimmingPeriod));
            if ((value + ledState->dimming.powerDelta[i]) < 0xFFU)
            {
                power[i] = (uint16_t)value + ledState->dimming.powerDelta[i];
            }
            else
            {
                power[i] = 0xFFU;
            }
        }
        else
        {
            ledState->dimming.powerDelta[i] =
                (uint8_t)((uint16_t)(value)*LED_DIMMING_UPDATE_INTERVAL / (dimmingPeriod));
            if (value > ledState->dimming.powerDelta[i])
            {
                power[i] = (uint16_t)value - (uint16_t)ledState->dimming.powerDelta[i];
            }
            else
            {
                power[i] = 0U;
            }
        }
#if (defined(LED_USE_CONFIGURE_STRUCTURE) && (LED_USE_CONFIGURE_STRUCTURE > 0U))
        if (kLED_TypeMonochrome == ledState->pinsConfig->type)
#else
        if ((uint16_t)kLED_TypeMonochrome == ledState->pins[0].config.type)
#endif
        {
            break;
        }
    }

    ledState->currentColor = LED_MAKE_COLOR(power[0], power[1], power[2]);
    ledState->flashCycle   = LED_FLASH_CYCLE_FOREVER;
    LED_EXIT_CRITICAL();
    (void)LED_SetStatus(ledState, ledState->currentColor, ledState->flashPeriod);

    return kStatus_LED_Success;
#else
    return kStatus_LED_Error;
#endif
}

led_status_t LED_EnterLowpower(led_handle_t ledHandle)
{
#if 0
    led_state_t* ledState;
    led_pin_config_t* ledRgbPin;
    led_status_t status;
    int count;

    assert(ledHandle);

    ledState = (led_state_t*)ledHandle;

    ledRgbPin = (led_pin_config_t*)&ledState->config.ledRgb;
    if (kLED_TypeRgb == ledState->config.type)
    {
        count = sizeof(led_config_t) / sizeof(led_pin_config_t);
    }
    else
    {
        count = 1;
    }

    for (int i = 0;i < count; i++)
    {
#if (defined(LED_DIMMING_ENABLEMENT) && (LED_DIMMING_ENABLEMENT > 0U))
        if (ledRgbPin[i].dimmingEnable)
        {
            HAL_PwmEnterLowpower(ledRgbPin[i].dimming.instance, ledRgbPin[i].dimming.channel);
        }
        else
#endif
        {
            HAL_GpioEnterLowpower(ledState->gpioHandle[i]);
        }
    }
#endif
    return kStatus_LED_Success;
}

led_status_t LED_ExitLowpower(led_handle_t ledHandle)
{
#if 0
    led_state_t* ledState;
    led_pin_config_t* ledRgbPin;
    led_status_t status;
    int count;

    assert(ledHandle);

    ledState = (led_state_t*)ledHandle;

    ledRgbPin = (led_pin_config_t*)&ledState->config.ledRgb;
    if (kLED_TypeRgb == ledState->config.type)
    {
        count = sizeof(led_config_t) / sizeof(led_pin_config_t);
    }
    else
    {
        count = 1;
    }

    for (int i = 0;i < count; i++)
    {
#if (defined(LED_DIMMING_ENABLEMENT) && (LED_DIMMING_ENABLEMENT > 0U))
        if (ledRgbPin[i].dimmingEnable)
        {
            HAL_PwmExitLowpower(ledRgbPin[i].dimming.instance, ledRgbPin[i].dimming.channel);
        }
        else
#endif
        {
            HAL_GpioExitLowpower(ledState->gpioHandle[i]);
        }
    }
#endif
    return kStatus_LED_Success;
}
