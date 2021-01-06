/*
 * Copyright 2018-2019 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_adapter_gpio.h"
#include "fsl_component_timer_manager.h"

#include "fsl_component_button.h"
/*
 * The OSA_USED macro can only be defined when the OSA component is used.
 * If the source code of the OSA component does not exist, the OSA_USED cannot be defined.
 * OR, If OSA component is not added into project event the OSA source code exists, the OSA_USED
 * also cannot be defined.
 * The source code path of the OSA component is <MCUXpresso_SDK>/components/osa.
 *
 */
#if defined(OSA_USED)
#include "fsl_os_abstraction.h"
#if (defined(BUTTON_USE_COMMON_TASK) && (BUTTON_USE_COMMON_TASK > 0U))
#include "fsl_component_common_task.h"
#endif
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#if defined(OSA_USED)
#include "fsl_os_abstraction.h"
#if (defined(USE_RTOS) && (USE_RTOS > 0U))
#define BUTTON_SR_ALLOC()       OSA_SR_ALLOC()
#define BUTTON_ENTER_CRITICAL() OSA_ENTER_CRITICAL();
#define BUTTON_EXIT_CRITICAL()  OSA_EXIT_CRITICAL()
#else
#define BUTTON_SR_ALLOC()
#define BUTTON_ENTER_CRITICAL()
#define BUTTON_EXIT_CRITICAL()
#endif
#else
#define BUTTON_SR_ALLOC()       uint32_t buttonPrimask;
#define BUTTON_ENTER_CRITICAL() buttonPrimask = DisableGlobalIRQ();
#define BUTTON_EXIT_CRITICAL()  EnableGlobalIRQ(buttonPrimask);
#endif

typedef enum _button_press_status
{
    kStatus_BUTTON_PressIdle          = 0U, /*!< Idle */
    kStatus_BUTTON_Pressed            = 1U, /*!< Pressed */
    kStatus_BUTTON_PressDoubleStart   = 2U, /*!< Start double click */
    kStatus_BUTTON_PressDoublePressed = 3U, /*!< Second press for double click */
} button_press_status_t;

typedef struct _button_state
{
    struct _button_state *next;
    button_callback_t callback;
    void *callbackParam;
    GPIO_HANDLE_DEFINE(gpioHandle);
    volatile uint32_t pushPeriodCount;
    volatile uint32_t pushPeriodCountLast;
    uint8_t pinStateDefault;
    uint8_t port;
    uint8_t pin;
    struct
    {
        volatile uint8_t pressed : 3U;
        volatile uint8_t msg : 5U;
    } state;
} button_state_t;

typedef struct _button_list
{
    volatile uint32_t periodCount;
    TIMER_MANAGER_HANDLE_DEFINE(timerHandle);
#if defined(OSA_USED)

#if (defined(BUTTON_USE_COMMON_TASK) && (BUTTON_USE_COMMON_TASK > 0U))
    common_task_message_t commonTaskMsg;
#else
    OSA_EVENT_HANDLE_DEFINE(eventHandle);
    OSA_TASK_HANDLE_DEFINE(taskHandle);
#endif

#endif
    button_state_t *button;
    volatile uint8_t timerOpenedNesting;
    volatile uint8_t activeButtonCount;
} button_list_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static void BUTTON_Task(void *param);

/*******************************************************************************
 * Variables
 ******************************************************************************/

static button_list_t s_buttonList;

#if defined(OSA_USED)
#if (defined(BUTTON_USE_COMMON_TASK) && (BUTTON_USE_COMMON_TASK > 0U))
#else
/*
 * \brief Defines the button task's stack
 */
static OSA_TASK_DEFINE(BUTTON_Task, BUTTON_TASK_PRIORITY, 1, BUTTON_TASK_STACK_SIZE, false);
#endif
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

static void BUTTON_NotificationUpdate(button_state_t *buttonState, button_event_t event)
{
    buttonState->state.pressed = (uint8_t)kStatus_BUTTON_PressIdle;
    buttonState->state.msg     = (uint8_t)event;
#if defined(OSA_USED)

#if (defined(BUTTON_USE_COMMON_TASK) && (BUTTON_USE_COMMON_TASK > 0U))
    s_buttonList.commonTaskMsg.callback      = BUTTON_Task;
    s_buttonList.commonTaskMsg.callbackParam = buttonState;
    (void)COMMON_TASK_post_message(&s_buttonList.commonTaskMsg);
#else
    (void)OSA_EventSet((osa_event_handle_t)s_buttonList.eventHandle, BUTTON_EVENT_BUTTON);
#endif

#else
    BUTTON_Task(&s_buttonList);
#endif
}

static void BUTTON_Event(void *param)
{
    button_state_t *buttonState = (button_state_t *)param;
    uint8_t pinState            = 0U;

    assert(param);

    (void)HAL_GpioGetInput(buttonState->gpioHandle, &pinState);
    pinState = (0U != pinState) ? 1U : 0U;
    if (((uint8_t)kStatus_BUTTON_PressIdle == buttonState->state.pressed) ||
        ((uint8_t)kStatus_BUTTON_PressDoubleStart == buttonState->state.pressed))
    {
        if (buttonState->pinStateDefault != pinState)
        {
            buttonState->state.pressed++;
            buttonState->pushPeriodCount = s_buttonList.periodCount;

            /* Start timer for interval scan button state. */
            if (0U == s_buttonList.activeButtonCount)
            {
                (void)TM_Start(s_buttonList.timerHandle, (uint8_t)kTimerModeIntervalTimer, BUTTON_TIMER_INTERVAL);
            }
            s_buttonList.activeButtonCount++;
        }
    }
    else
    {
        if (buttonState->pinStateDefault == pinState)
        {
            if ((BUTTON_DOUBLE_CLICK_THRESHOLD + buttonState->pushPeriodCountLast) >= buttonState->pushPeriodCount)
            {
                if ((s_buttonList.periodCount - buttonState->pushPeriodCount) < BUTTON_SHORT_PRESS_THRESHOLD)
                {
#if (defined(BUTTON_EVENT_DOUBLECLICK_ENABLE) && BUTTON_EVENT_DOUBLECLICK_ENABLE > 0U)
                    BUTTON_NotificationUpdate(buttonState, kBUTTON_EventDoubleClick);
#endif /* BUTTON_EVENT_DOUBLECLICK_ENABLE */
                }
                else
                {
                    BUTTON_NotificationUpdate(buttonState, kBUTTON_EventError);
                }
            }
            else
            {
                if ((s_buttonList.periodCount - buttonState->pushPeriodCount) < BUTTON_SHORT_PRESS_THRESHOLD)
                {
                    buttonState->pushPeriodCountLast = s_buttonList.periodCount;
                    buttonState->state.pressed       = (uint8_t)kStatus_BUTTON_PressDoubleStart;
                }
#if (defined(BUTTON_EVENT_SHORTPRESS_ENABLE) && BUTTON_EVENT_SHORTPRESS_ENABLE > 0U)
                else if ((s_buttonList.periodCount - buttonState->pushPeriodCount) < BUTTON_LONG_PRESS_THRESHOLD)
                {
                    BUTTON_NotificationUpdate(buttonState, kBUTTON_EventShortPress);
                }
#endif /* BUTTON_EVENT_SHORTPRESS_ENABLE */
#if (defined(BUTTON_EVENT_LONGPRESS_ENABLE) && BUTTON_EVENT_LONGPRESS_ENABLE > 0U)
                else
                {
                    BUTTON_NotificationUpdate(buttonState, kBUTTON_EventLongPress);
                }
#else
                else
                {
                    BUTTON_NotificationUpdate(buttonState, kBUTTON_EventError);
                }
#endif /* BUTTON_EVENT_LONGPRESS_ENABLE */
            }
        }
    }
}

static void BUTTON_Task(void *param)
{
#if defined(OSA_USED)

#if (defined(BUTTON_USE_COMMON_TASK) && (BUTTON_USE_COMMON_TASK > 0U))
#else
    osa_event_flags_t ev = 0;

    do
    {
        if (KOSA_StatusSuccess ==
            OSA_EventWait((osa_event_handle_t)s_buttonList.eventHandle, osaEventFlagsAll_c, 0U, osaWaitForever_c, &ev))
        {
#endif

#endif
    button_state_t *buttonState = s_buttonList.button;
    BUTTON_SR_ALLOC();

    BUTTON_ENTER_CRITICAL();
    while (NULL != buttonState)
    {
        if (0U != buttonState->state.msg)
        {
            button_callback_message_t msg;
            BUTTON_EXIT_CRITICAL();
            msg.event = (button_event_t)buttonState->state.msg;
            (void)buttonState->callback(buttonState, &msg, buttonState->callbackParam);
            buttonState->state.msg = 0U;
            BUTTON_ENTER_CRITICAL();

            /* Stop timer for efficiency */
            s_buttonList.activeButtonCount--;
            if (0U == s_buttonList.activeButtonCount)
            {
                (void)TM_Stop(s_buttonList.timerHandle);
            }
        }
        buttonState = buttonState->next;
    }
    BUTTON_EXIT_CRITICAL();
#if defined(OSA_USED)

#if (defined(BUTTON_USE_COMMON_TASK) && (BUTTON_USE_COMMON_TASK > 0U))
#else
        }
    } while (0U != gUseRtos_c);
#endif

#endif
}

static void BUTTON_TimerEvent(void *param)
{
#if (defined(BUTTON_EVENT_ONECLICK_ENABLE) && BUTTON_EVENT_ONECLICK_ENABLE > 0U)
    button_state_t *buttonState;
    BUTTON_SR_ALLOC();
#endif /* BUTTON_EVENT_ONECLICK_ENABLE */

    s_buttonList.periodCount += BUTTON_TIMER_INTERVAL;

#if (defined(BUTTON_EVENT_ONECLICK_ENABLE) && BUTTON_EVENT_ONECLICK_ENABLE > 0U)
    BUTTON_ENTER_CRITICAL();
    buttonState = s_buttonList.button;
    while (NULL != buttonState)
    {
        /*
         * The code block is used to indentify the button event is one click or double click.
         * If the flag pending is set and the button is not pressed, check the user activity is timeout or not.
         * If is times out, notify the upper layer it is kBUTTON_EventOneClick.
         * Otherwise, check the status next time.
         */
        if ((uint8_t)kStatus_BUTTON_PressDoubleStart == buttonState->state.pressed)
        {
            if ((BUTTON_DOUBLE_CLICK_THRESHOLD + buttonState->pushPeriodCountLast) < s_buttonList.periodCount)
            {
                BUTTON_NotificationUpdate(buttonState, kBUTTON_EventOneClick);
                buttonState->pushPeriodCountLast = 0U;
            }
        }
        buttonState = buttonState->next;
    }
    BUTTON_EXIT_CRITICAL();
#endif /* BUTTON_EVENT_ONECLICK_ENABLE */
}

static void BUTTON_OpenTimer(void)
{
    BUTTON_SR_ALLOC();
    uint8_t initTimer = 0U;

    BUTTON_ENTER_CRITICAL();
    initTimer = (uint8_t)(!(bool)s_buttonList.timerOpenedNesting);
    s_buttonList.timerOpenedNesting++;
    BUTTON_EXIT_CRITICAL();

    if (0U != initTimer)
    {
        timer_status_t timerStatus;
        timerStatus = TM_Open((timer_handle_t)s_buttonList.timerHandle);
        assert(kStatus_TimerSuccess == timerStatus);

        timerStatus = TM_InstallCallback(s_buttonList.timerHandle, BUTTON_TimerEvent, &s_buttonList);
        assert(kStatus_TimerSuccess == timerStatus);

        (void)timerStatus;
    }
}

static void BUTTON_CloseTimer(void)
{
    BUTTON_SR_ALLOC();
    uint8_t deinitTimer = 0U;

    BUTTON_ENTER_CRITICAL();
    if (s_buttonList.timerOpenedNesting > 0U)
    {
        s_buttonList.timerOpenedNesting--;
        deinitTimer = (uint8_t)(!(bool)s_buttonList.timerOpenedNesting);
    }
    BUTTON_EXIT_CRITICAL();

    if (0U != deinitTimer)
    {
        timer_status_t timerStatus;
        timerStatus = TM_Close((timer_handle_t)s_buttonList.timerHandle);
        assert(kStatus_TimerSuccess == timerStatus);
        (void)timerStatus;
    }
}

button_status_t BUTTON_Init(button_handle_t buttonHandle, button_config_t *buttonConfig)
{
    button_state_t *buttonState;
    hal_gpio_status_t gpioStatus;
    BUTTON_SR_ALLOC();

    assert((NULL != buttonHandle) && (NULL != buttonConfig));
    assert(BUTTON_HANDLE_SIZE >= sizeof(button_state_t));

    buttonState = (button_state_t *)buttonHandle;

    (void)memset(buttonHandle, 0, sizeof(button_state_t));

    BUTTON_ENTER_CRITICAL();
    BUTTON_OpenTimer();
    if (NULL == s_buttonList.button)
    {
#if defined(OSA_USED)

#if (defined(BUTTON_USE_COMMON_TASK) && (BUTTON_USE_COMMON_TASK > 0U))
        (void)COMMON_TASK_init();
#else
        osa_status_t osaStatus;

        osaStatus = OSA_EventCreate((osa_event_handle_t)s_buttonList.eventHandle, 1U);
        assert(KOSA_StatusSuccess == osaStatus);

        osaStatus = OSA_TaskCreate((osa_task_handle_t)s_buttonList.taskHandle, OSA_TASK(BUTTON_Task), &s_buttonList);
        assert(KOSA_StatusSuccess == osaStatus);
        (void)osaStatus;
#endif

#endif
    }
    else
    {
        buttonState->next = s_buttonList.button;
    }
    s_buttonList.button = buttonState;
    /* Timer only works when button have activities, so s_buttonList.periodCount would be 0 for the first press and
       double click check case will be triggered. So we need set a start time for prevent this situation, a start time
       bigger than BUTTON_DOUBLE_CLICK_THRESHOLD is works. */
    s_buttonList.periodCount = BUTTON_DOUBLE_CLICK_THRESHOLD + BUTTON_TIMER_INTERVAL;
    BUTTON_EXIT_CRITICAL();

    (void)memcpy(&buttonState->pinStateDefault, &buttonConfig->gpio.pinStateDefault, 3U);
    gpioStatus = HAL_GpioInit(buttonState->gpioHandle, (hal_gpio_pin_config_t *)((void *)buttonConfig));

    assert(kStatus_HAL_GpioSuccess == gpioStatus);

    gpioStatus = HAL_GpioSetTriggerMode(buttonState->gpioHandle, kHAL_GpioInterruptEitherEdge);
    assert(kStatus_HAL_GpioSuccess == gpioStatus);
    (void)gpioStatus;

    return kStatus_BUTTON_Success;
}

button_status_t BUTTON_InstallCallback(button_handle_t buttonHandle, button_callback_t callback, void *callbackParam)
{
    button_state_t *buttonState;
    assert(buttonHandle);

    buttonState = (button_state_t *)buttonHandle;

    buttonState->callback      = callback;
    buttonState->callbackParam = callbackParam;

    (void)HAL_GpioInstallCallback(buttonState->gpioHandle, BUTTON_Event, buttonState);

    return kStatus_BUTTON_Success;
}

button_status_t BUTTON_Deinit(button_handle_t buttonHandle)
{
    button_state_t *buttonState;
    button_state_t *buttonStatePre;
    BUTTON_SR_ALLOC();

    assert(buttonHandle);

    buttonState = (button_state_t *)buttonHandle;

    BUTTON_ENTER_CRITICAL();
    buttonStatePre = s_buttonList.button;
    if (buttonStatePre != buttonState)
    {
        while ((NULL != buttonStatePre) && (buttonStatePre->next != buttonState))
        {
            buttonStatePre = buttonStatePre->next;
        }
        if (NULL != buttonStatePre)
        {
            buttonStatePre->next = buttonState->next;
        }
    }
    else
    {
        s_buttonList.button = buttonState->next;
    }

    if (NULL == s_buttonList.button)
    {
#if defined(OSA_USED)

#if (defined(BUTTON_USE_COMMON_TASK) && (BUTTON_USE_COMMON_TASK > 0U))

#else
        (void)OSA_TaskDestroy((osa_task_handle_t)s_buttonList.taskHandle);
        (void)OSA_EventDestroy((osa_event_handle_t)s_buttonList.eventHandle);
#endif

#endif
    }
    BUTTON_CloseTimer();
    BUTTON_EXIT_CRITICAL();

    (void)HAL_GpioDeinit(buttonState->gpioHandle);

    return kStatus_BUTTON_Success;
}

button_status_t BUTTON_GetInput(button_handle_t buttonHandle, uint8_t *pinState)
{
    button_state_t *buttonState;

    assert(buttonHandle);

    buttonState = (button_state_t *)buttonHandle;

    (void)HAL_GpioGetInput(buttonState->gpioHandle, pinState);

    return kStatus_BUTTON_Success;
}

button_status_t BUTTON_WakeUpSetting(button_handle_t buttonHandle, uint8_t enable)
{
    button_state_t *buttonState;
    hal_gpio_status_t status;

    assert(buttonHandle);

    buttonState = (button_state_t *)buttonHandle;

    status = HAL_GpioWakeUpSetting(buttonState->gpioHandle, enable);

    if (kStatus_HAL_GpioSuccess == status)
    {
        return kStatus_BUTTON_Success;
    }
    return kStatus_BUTTON_Error;
}

button_status_t BUTTON_EnterLowpower(button_handle_t buttonHandle)
{
    button_state_t *buttonState;
    hal_gpio_status_t status;
    /* MISRA C-2012 Rule 11.6 */
    uint32_t *pLowpowerHandle = BUTTON_ALL_ENTER_EXIT_LOWPOWER_HANDLE;

    assert(buttonHandle);

    if ((button_handle_t)pLowpowerHandle != buttonHandle)
    {
        buttonState = (button_state_t *)buttonHandle;
    }
    else
    {
        buttonState = s_buttonList.button;
    }

    while (NULL != buttonState)
    {
        status = HAL_GpioEnterLowpower(buttonState->gpioHandle);

        if (kStatus_HAL_GpioSuccess != status)
        {
            return kStatus_BUTTON_Error;
        }

        BUTTON_CloseTimer();

        if ((button_handle_t)pLowpowerHandle != buttonHandle)
        {
            break;
        }

        buttonState = buttonState->next;
    }

    return kStatus_BUTTON_Success;
}

button_status_t BUTTON_ExitLowpower(button_handle_t buttonHandle)
{
    button_state_t *buttonState;
    hal_gpio_status_t status;
    /* MISRA C-2012 Rule 11.6 */
    uint32_t *pLowpowerHandle = BUTTON_ALL_ENTER_EXIT_LOWPOWER_HANDLE;

    assert(buttonHandle);

    if ((button_handle_t)pLowpowerHandle != buttonHandle)
    {
        buttonState = (button_state_t *)buttonHandle;
    }
    else
    {
        buttonState = s_buttonList.button;
    }

    while (NULL != buttonState)
    {
        status = HAL_GpioExitLowpower(buttonState->gpioHandle);

        if (kStatus_HAL_GpioSuccess != status)
        {
            return kStatus_BUTTON_Error;
        }

        BUTTON_OpenTimer();

        BUTTON_Event(buttonState);

        if ((button_handle_t)pLowpowerHandle != buttonHandle)
        {
            break;
        }

        buttonState = buttonState->next;
    }

    return kStatus_BUTTON_Success;
}
