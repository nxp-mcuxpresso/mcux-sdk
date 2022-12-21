/*
 * Copyright 2018-2019 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "fsl_common.h"
#if (defined(COMMON_TASK_ENABLE) && (COMMON_TASK_ENABLE == 0U))
#include "fsl_component_common_task.h"
#endif /* COMMON_TASK_ENABLE */
#include "fsl_adapter_gpio.h"
/*!
 * @addtogroup Button
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Definition of feature 'one click' enable macro. */
#ifndef BUTTON_EVENT_ONECLICK_ENABLE
#define BUTTON_EVENT_ONECLICK_ENABLE (1)
#endif
/*! @brief Definition of feature 'double click' enable macro. */
#ifndef BUTTON_EVENT_DOUBLECLICK_ENABLE
#define BUTTON_EVENT_DOUBLECLICK_ENABLE (1)
#endif
/*! @brief Definition of feature 'short press' enable macro. */
#ifndef BUTTON_EVENT_SHORTPRESS_ENABLE
#define BUTTON_EVENT_SHORTPRESS_ENABLE (1)
#endif
/*! @brief Definition of feature 'long press' enable macro. */
#ifndef BUTTON_EVENT_LONGPRESS_ENABLE
#define BUTTON_EVENT_LONGPRESS_ENABLE (1)
#endif

/*! @brief Definition of all buttons enter/exit lowpower handle macro. */
#define BUTTON_ALL_ENTER_EXIT_LOWPOWER_HANDLE ((uint32_t *)0xffffffffU) /* MISRA C-2012 Rule 11.6 */

/*! @brief Definition of button handle size as HAL_GPIO_HANDLE_SIZE + button dedicated size. */
#define BUTTON_HANDLE_SIZE (16U + 24U)

/*! @brief The handle of button */
typedef void *button_handle_t;

/*!
 * @brief Defines the button handle
 *
 * This macro is used to define a 4 byte aligned button handle.
 * Then use "(button_handle_t)name" to get the button handle.
 *
 * The macro should be global and could be optional. You could also define button handle by yourself.
 *
 * This is an example,
 * @code
 * BUTTON_HANDLE_DEFINE(buttonHandle);
 * @endcode
 *
 * @param name The name string of the button handle.
 */
#define BUTTON_HANDLE_DEFINE(name) uint32_t name[((BUTTON_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t))]

/*!
 * @brief Defines the button handle array
 *
 * This macro is used to define a 4 byte aligned button handle array.
 * Then use "(button_handle_t)name[0]" to get the first button handle.
 *
 * The macro should be global and could be optional. You could also define these button handle by yourself.
 *
 * This is an example,
 * @code
 * BUTTON_HANDLE_DEFINE(buttonHandleArray, 1);
 * @endcode
 *
 * @param name The name string of the button handle array.
 * @param count The amount of button handle.
 */
#define BUTTON_HANDLE_ARRAY_DEFINE(name, count) \
    uint32_t name[count][((BUTTON_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t))]

/*! @brief Definition of button timer interval,unit is ms. */
#define BUTTON_TIMER_INTERVAL (25U)

/*! @brief Definition of button short press threshold,unit is ms. */
#ifndef BUTTON_SHORT_PRESS_THRESHOLD
#define BUTTON_SHORT_PRESS_THRESHOLD (200U)
#endif

/*! @brief Definition of button long press threshold,unit is ms. */
#ifndef BUTTON_LONG_PRESS_THRESHOLD
#define BUTTON_LONG_PRESS_THRESHOLD (500U)
#endif

/*! @brief Definition of button double click threshold,unit is ms. */
#define BUTTON_DOUBLE_CLICK_THRESHOLD (200U)

/*! @brief Definition to determine whether use common task. */
#ifndef BUTTON_USE_COMMON_TASK
#define BUTTON_USE_COMMON_TASK (0U)
#if (defined(COMMON_TASK_ENABLE) && (COMMON_TASK_ENABLE == 0U))
#undef BUTTON_USE_COMMON_TASK
#define BUTTON_USE_COMMON_TASK (0U)
#endif
#endif

/*! @brief Definition of button task priority. */
#ifndef BUTTON_TASK_PRIORITY
#define BUTTON_TASK_PRIORITY (7U)
#endif

/*! @brief Definition of button task stack size. */
#ifndef BUTTON_TASK_STACK_SIZE
#define BUTTON_TASK_STACK_SIZE (1000U)
#endif

/*! @brief Definition of button event. */
#define BUTTON_EVENT_BUTTON (1U)

/*! @brief The status type of button */
typedef enum _button_status
{
    kStatus_BUTTON_Success    = kStatus_Success,                     /*!< Success */
    kStatus_BUTTON_Error      = MAKE_STATUS(kStatusGroup_BUTTON, 1), /*!< Failed */
    kStatus_BUTTON_LackSource = MAKE_STATUS(kStatusGroup_BUTTON, 2), /*!< Lack of sources */
} button_status_t;

/*! @brief The event type of button */
typedef enum _button_event
{
    kBUTTON_EventOneClick = 0x01U, /*!< One click with short time, the duration of key down and key up is less than
                                      #BUTTON_SHORT_PRESS_THRESHOLD. */
    kBUTTON_EventDoubleClick,      /*!< Double click with short time, the duration of key down and key up is less than
                                      #BUTTON_SHORT_PRESS_THRESHOLD.      And the duration of the two button actions does not
                                      exceed #BUTTON_DOUBLE_CLICK_THRESHOLD. */
    kBUTTON_EventShortPress,       /*!< Press with short time, the duration of key down and key up is no less than
                                      #BUTTON_SHORT_PRESS_THRESHOLD       and less than #BUTTON_LONG_PRESS_THRESHOLD. */
    kBUTTON_EventLongPress,        /*!< Press with long time, the duration of key down and key up is no less than
                                      #BUTTON_LONG_PRESS_THRESHOLD. */
    kBUTTON_EventError,            /*!< Error event if the button actions cannot be identified. */
} button_event_t;

/*! @brief The callback message struct of button */
typedef struct _button_callback_message_struct
{
    button_event_t event;
} button_callback_message_t;

/*! @brief The callback function of button */
typedef button_status_t (*button_callback_t)(void *buttonHandle,
                                             button_callback_message_t *message,
                                             void *callbackParam);

/*! @brief The button gpio config structure */
typedef struct _button_gpio_config
{
    hal_gpio_direction_t direction; /*!< GPIO Pin direction (0 - In, 1 - Out)*/
    uint8_t pinStateDefault;        /*!< GPIO Pin voltage when button is not pressed (0 - low level, 1 - high level)*/
    uint8_t port;                   /*!< GPIO Port */
    uint8_t pin;                    /*!< GPIO Pin */
} button_gpio_config_t;

/*! @brief The button config structure */
typedef struct _button_config
{
    button_gpio_config_t gpio;
} button_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @name Initialization
 * @{
 */

/*!
 * @brief Initializes a button with the button handle and the user configuration structure.
 *
 * This function configures the button with user-defined settings. The user can configure the configuration
 * structure. The parameter buttonHandle is a pointer to point to a memory space of size #BUTTON_HANDLE_SIZE allocated
 * by the caller.
 *
 * Example below shows how to use this API to configure the button.
 * For one button,
 *  @code
 *   static BUTTON_HANDLE_DEFINE(s_buttonHandle);
 *   button_config_t buttonConfig;
 *   buttonConfig.gpio.port = 0;
 *   buttonConfig.gpio.pin = 1;
 *   buttonConfig.gpio.pinStateDefault = 0;
 *   BUTTON_Init((button_handle_t)s_buttonHandle, &buttonConfig);
 *  @endcode
 * For multiple buttons,
 *  @code
 *   static BUTTON_HANDLE_ARRAY_DEFINE(s_buttonArrayHandle, count);
 *   button_config_t buttonArrayConfig[count];
 *   for(uint8_t i = 0U; i < count; i++)
 *   {
 *       buttonArrayConfig[i].gpio.port = 0;
 *       buttonArrayConfig[i].gpio.pin = 1;
 *       buttonArrayConfig[i].gpio.pinStateDefault = 0;
 *       BUTTON_Init((button_handle_t)s_buttonArrayHandle[i], &buttonArrayConfig[i]);
 *   }
 *  @endcode
 *
 * @param buttonHandle Pointer to point to a memory space of size #BUTTON_HANDLE_SIZE allocated by the caller.
 * The handle should be 4 byte aligned, because unaligned access doesn't be supported on some devices.
 * You can define one handle in the following two ways:
 * #BUTTON_HANDLE_DEFINE(buttonHandle);
 * or
 * uint32_t buttonHandle[((BUTTON_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t))];
 * You can define multiple handles in the following way:
 * #BUTTON_HANDLE_ARRAY_DEFINE(buttonHandleArray, count);
 * @param buttonConfig Pointer to user-defined configuration structure.
 * @return Indicates whether initialization was successful or not.
 * @retval kStatus_BUTTON_Error An error occurred.
 * @retval kStatus_BUTTON_Success Button initialization succeed.
 */
button_status_t BUTTON_Init(button_handle_t buttonHandle, button_config_t *buttonConfig);

/*! @}*/

/*!
 * @name Install callback
 * @{
 */

/*!
 * @brief Installs a callback and callback parameter.
 *
 * This function is used to install the callback and callback parameter for button module.
 * Once the button is pressed, the button driver will identify the behavior and notify the
 * upper layer with the button event by the installed callback function. Currently, the Button
 * supports the three types of event, click, double click and long press. Detail information refer
 * to #button_event_t.
 *
 * @param buttonHandle Button handle pointer.
 * @param callback The callback function.
 * @param callbackParam The parameter of the callback function.
 * @return Indicates whether callback install was successful or not.
 * @retval kStatus_BUTTON_Success Successfully install the callback.
 */
button_status_t BUTTON_InstallCallback(button_handle_t buttonHandle, button_callback_t callback, void *callbackParam);

/*! @}*/

/*!
 * @brief Deinitializes a button instance.
 *
 * This function deinitializes the button instance.
 *
 * @param buttonHandle button handle pointer.
 * @retval kStatus_BUTTON_Success button de-initialization succeed.
 */
button_status_t BUTTON_Deinit(button_handle_t buttonHandle);

/*!
 * @brief Get button pin input.
 *
 * This function is used for get the button pin input.
 *
 * @param buttonHandle button handle pointer.
 * @param pinState a pointer to save the pin state.
 * @retval kStatus_BUTTON_Error An error occurred.
 * @retval kStatus_BUTTON_Success Set successfully.
 */
button_status_t BUTTON_GetInput(button_handle_t buttonHandle, uint8_t *pinState);

/*!
 * @brief Enables or disables the button wake-up feature.
 *
 * This function enables or disables the button wake-up feature.
 *
 * @param buttonHandle button handle pointer.
 * @param enable enable or disable (0 - disable, 1 - enable).
 * @retval kStatus_BUTTON_Error An error occurred.
 * @retval kStatus_BUTTON_Success Set successfully.
 */
button_status_t BUTTON_WakeUpSetting(button_handle_t buttonHandle, uint8_t enable);

/*!
 * @brief Prepares to enter low power consumption.
 *
 * This function is used to prepare to enter low power consumption.
 *
 * @param buttonHandle button handle pointer.
 * @retval kStatus_BUTTON_Success Successful operation.
 */
button_status_t BUTTON_EnterLowpower(button_handle_t buttonHandle);

/*!
 * @brief Restores from low power consumption.
 *
 * This function is used to restore from low power consumption.
 *
 * @param buttonHandle button handle pointer.
 * @retval kStatus_BUTTON_Success Successful operation.
 */
button_status_t BUTTON_ExitLowpower(button_handle_t buttonHandle);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @}*/

#endif /* __BUTTON_H__ */
