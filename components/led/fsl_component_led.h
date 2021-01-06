/*
 * Copyright 2018-2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __LED_H__
#define __LED_H__

#include "fsl_common.h"
#include "fsl_adapter_gpio.h"
/*!
 * @addtogroup LED
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Definition to determine whether enable dimming. */
#ifndef LED_DIMMING_ENABLEMENT
#define LED_DIMMING_ENABLEMENT (0U) /*!< Enable or disable the dimming feature */
#endif

/*! @brief Definition to determine whether enable color wheel. */
#ifndef LED_COLOR_WHEEL_ENABLEMENT
#define LED_COLOR_WHEEL_ENABLEMENT (0U) /*!< Enable or disable the color wheel feature */
#endif

/*! @brief Definition to determine whether use confgure structure. */
#ifndef LED_USE_CONFIGURE_STRUCTURE
#define LED_USE_CONFIGURE_STRUCTURE (1U) /*!< Enable or disable the confgure structure pointer */
#endif
/*! @brief The handle of LED */
typedef void *led_handle_t;

/*! @brief Definition of LED handle size. */
#if (defined(LED_DIMMING_ENABLEMENT) && (LED_DIMMING_ENABLEMENT > 0U))
/* HAL_GPIO_HANDLE_SIZE * 3 + HAL_PWM_HANDLE_SIZE *3 + LED dedicated size */
#define LED_HANDLE_SIZE ((16U * 3U) + (8U * 3U) + 40U)
#else
#if (defined(LED_USE_CONFIGURE_STRUCTURE) && (LED_USE_CONFIGURE_STRUCTURE > 0U))
/* HAL_GPIO_HANDLE_SIZE * 3 + LED dedicated size */
#define LED_HANDLE_SIZE ((16U * 3U) + 32U)
#else
/* HAL_GPIO_HANDLE_SIZE * 3 + LED dedicated size */
#define LED_HANDLE_SIZE ((16U * 3U) + 36U)
#endif
#endif

/*!
 * @brief Defines the led handle
 *
 * This macro is used to define a 4 byte aligned led handle.
 * Then use "(led_handle_t)name" to get the led handle.
 *
 * The macro should be global and could be optional. You could also define led handle by yourself.
 *
 * This is an example,
 * @code
 * LED_HANDLE_DEFINE(ledHandle);
 * @endcode
 *
 * @param name The name string of the led handle.
 */
#define LED_HANDLE_DEFINE(name) uint32_t name[((LED_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t))]

/*!
 * @brief Defines the led handle array
 *
 * This macro is used to define a 4 byte aligned led handle array.
 * Then use "(led_handle_t)name[0]" to get the first led handle.
 *
 * The macro should be global and could be optional. You could also define these led handle by yourself.
 *
 * This is an example,
 * @code
 * LED_HANDLE_ARRAY_DEFINE(ledHandleArray,1);
 * @endcode
 *
 * @param name The name string of the led handle array.
 * @param count The amount of led handle.
 */
#define LED_HANDLE_ARRAY_DEFINE(name, count) \
    uint32_t name[count][((LED_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t))]

/*! @brief Definition of LED timer interval,unit is ms. */
#define LED_TIMER_INTERVAL (100U)

/*! @brief Definition of LED dimming update interval,unit is ms. */
#define LED_DIMMING_UPDATE_INTERVAL (100U)

/*! @brief Definition of LED flash cycle forever. */
#define LED_FLASH_CYCLE_FOREVER (0xFFFFFFFFU)

/*! @brief Definition of LED blip interval,unit is ms. */
#define LED_BLIP_INTERVAL (250U)

/*! @brief The status type of LED */
typedef enum _led_status
{
    kStatus_LED_Success          = kStatus_Success,                  /*!< Success */
    kStatus_LED_Error            = MAKE_STATUS(kStatusGroup_LED, 1), /*!< Failed */
    kStatus_LED_InvalidParameter = MAKE_STATUS(kStatusGroup_LED, 2), /*!< Invalid parameter*/
} led_status_t;

/*! @brief The flash type of LED */
typedef enum _led_flash_type
{
    kLED_FlashOneColor = 0x00U, /*!< Fast with one color */
#if (defined(LED_COLOR_WHEEL_ENABLEMENT) && (LED_COLOR_WHEEL_ENABLEMENT > 0U))
    kLED_FlashColorWheel, /*!< Fast with color wheel */
#endif                    /* (defined(LED_COLOR_WHEEL_ENABLEMENT) && (LED_COLOR_WHEEL_ENABLEMENT > 0U)) */
} led_flash_type_t;

/*! @brief The color struct of LED */
typedef uint32_t led_color_t;

/*! @brief Definition to set LED color. */
#define LED_MAKE_COLOR(r, g, b) ((led_color_t)((((led_color_t)b) << 16) | (((led_color_t)g) << 8) | ((led_color_t)r)))

/*! @brief The color type of LED */
enum _led_color
{
    kLED_Black      = LED_MAKE_COLOR(0, 0, 0),       /*!< Black */
    kLED_Red        = LED_MAKE_COLOR(255, 0, 0),     /*!< Red */
    kLED_Green      = LED_MAKE_COLOR(0, 255, 0),     /*!< Green */
    kLED_Yellow     = LED_MAKE_COLOR(255, 255, 0),   /*!< Yellow */
    kLED_Blue       = LED_MAKE_COLOR(0, 0, 255),     /*!< Blue */
    kLED_Pink       = LED_MAKE_COLOR(255, 0, 255),   /*!< Pink */
    kLED_Aquamarine = LED_MAKE_COLOR(0, 255, 255),   /*!< Aquamarine */
    kLED_White      = LED_MAKE_COLOR(255, 255, 255), /*!< White */
};

#if defined(__CC_ARM)
#pragma anon_unions
#endif
/*! @brief The pin config struct of LED */
typedef struct _led_pin_config
{
    uint8_t dimmingEnable; /*!< dimming enable, 0 - disable, 1 - enable */
    union
    {
#if (defined(LED_USE_CONFIGURE_STRUCTURE) && (LED_USE_CONFIGURE_STRUCTURE > 0U))
        hal_gpio_pin_config_t gpio;
#else
        struct
        {
            uint8_t port;            /*!< GPIO Port */
            uint8_t pin;             /*!< GPIO Pin */
            uint8_t pinStateDefault; /*!< GPIO Pin voltage when LED is off (0 - low level, 1 - high level)*/
        } gpio;
#endif
        struct
        {
            uint32_t sourceClock;    /*!< The clock source of the PWM module */
            uint8_t instance;        /*!< PWM instance of the pin */
            uint8_t channel;         /*!< PWM channel of the pin */
            uint8_t pinStateDefault; /*!< The Pin voltage when LED is off (0 - low level, 1 - high level)*/
        } dimming;
    };
} led_pin_config_t;

/*! @brief The pin config struct of rgb LED */
typedef struct _led_rgb_config
{
    led_pin_config_t redPin;   /*!< Red pin setting */
    led_pin_config_t greenPin; /*!< Green pin setting */
    led_pin_config_t bluePin;  /*!< Blue pin setting */
} led_rgb_config_t;

/*! @brief The pin config struct of monochrome LED */
typedef struct _led_monochrome_config
{
    led_pin_config_t monochromePin; /*!< Monochrome pin setting */
} led_monochrome_config_t;

/*! @brief The type of LED */
typedef enum _led_type
{
    kLED_TypeRgb        = 0x01U, /*!< RGB LED */
    kLED_TypeMonochrome = 0x02U, /*!< Monochrome LED */
} led_type_t;

/*! @brief The config struct of LED */
typedef struct _led_config
{
    led_type_t type;
    union
    {
        led_rgb_config_t ledRgb;               /*!< RGB setting */
        led_monochrome_config_t ledMonochrome; /*!< Monochrome setting */
    };
} led_config_t;

/*! @brief The flash config struct of LED */
typedef struct _led_flash_config
{
    uint32_t times;             /*!< Flash times, LED_FLASH_CYCLE_FOREVER for forever */
    uint16_t period;            /*!< Flash period, unit is ms */
    led_flash_type_t flashType; /*!< Flash type, one color or color wheel. Refer to #led_flash_type_t */
    uint8_t duty;               /*!< Duty of the LED on for one period (duration = duty * period / 100). */
} led_flash_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* _cplusplus */

/*!
 * @brief Initializes a LED with the LED handle and the user configuration structure.
 *
 * This function configures the LED with user-defined settings. The user can configure the configuration
 * structure. The parameter ledHandle is a pointer to point to a memory space of size #LED_HANDLE_SIZE allocated by the
 * caller. The LED supports two types LED, RGB and monochrome. Please refer to #led_type_t. These two types can be set
 * by using #led_config_t. The LED also supports LED dimming mode.
 *
 * Example below shows how to use this API to configure the LED.
 * For monochrome LED,
 *  @code
 *   static LED_HANDLE_DEFINE(s_ledMonochromeHandle);
 *   led_config_t ledMonochromeConfig;
 *   ledMonochromeConfig.type = kLED_TypeMonochrome;
 *   ledMonochromeConfig.ledMonochrome.monochromePin.dimmingEnable = 0;
 *   ledMonochromeConfig.ledMonochrome.monochromePin.gpio.port = 0;
 *   ledMonochromeConfig.ledMonochrome.monochromePin.gpio.pin = 1;
 *   ledMonochromeConfig.ledMonochrome.monochromePin.gpio.pinStateDefault = 0;
 *   LED_Init((led_handle_t)s_ledMonochromeHandle, &ledMonochromeConfig);
 *  @endcode
 * For rgb LED,
 *  @code
 *   static LED_HANDLE_DEFINE(s_ledRgbHandle);
 *   led_config_t ledRgbConfig;
 *   ledRgbConfig.type = kLED_TypeRgb;
 *   ledRgbConfig.ledRgb.redPin.dimmingEnable = 0;
 *   ledRgbConfig.ledRgb.redPin.gpio.port = 0;
 *   ledRgbConfig.ledRgb.redPin.gpio.pin = 1;
 *   ledRgbConfig.ledRgb.redPin.gpio.pinStateDefault = 0;
 *   ledRgbConfig.ledRgb.greenPin.dimmingEnable = 0;
 *   ledRgbConfig.ledRgb.greenPin.gpio.port = 0;
 *   ledRgbConfig.ledRgb.greenPin.gpio.pin = 2;
 *   ledRgbConfig.ledRgb.greenPin.gpio.pinStateDefault = 0;
 *   ledRgbConfig.ledRgb.bluePin.dimmingEnable = 0;
 *   ledRgbConfig.ledRgb.bluePin.gpio.port = 0;
 *   ledRgbConfig.ledRgb.bluePin.gpio.pin = 3;
 *   ledRgbConfig.ledRgb.bluePin.gpio.pinStateDefault = 0;
 *   LED_Init((led_handle_t)s_ledRgbHandle, &ledRgbConfig);
 *  @endcode
 * For dimming monochrome LED,
 *  @code
 *   static LED_HANDLE_DEFINE(s_ledMonochromeHandle);
 *   led_config_t ledMonochromeConfig;
 *   ledMonochromeConfig.type = kLED_TypeMonochrome;
 *   ledMonochromeConfig.ledMonochrome.monochromePin.dimmingEnable = 1;
 *   ledMonochromeConfig.ledMonochrome.monochromePin.dimming.sourceClock = 48000000;
 *   ledMonochromeConfig.ledMonochrome.monochromePin.dimming.instance = 0;
 *   ledMonochromeConfig.ledMonochrome.monochromePin.dimming.channel = 1;
 *   ledMonochromeConfig.ledMonochrome.monochromePin.dimming.pinStateDefault = 0;
 *   LED_Init((led_handle_t)s_ledMonochromeHandle, &ledMonochromeConfig);
 *  @endcode
 * For multiple LEDs,
 *  @code
 *   static LED_HANDLE_ARRAY_DEFINE(s_ledArrayHandle, count);
 *   led_config_t ledArrayConfig[count];
 *   for(uint8_t i = 0; i < count; i++ )
 *   {
 *       ledArrayConfig[i].type = kLED_TypeMonochrome;
 *       ledArrayConfig[i].ledMonochrome.monochromePin.dimmingEnable = 1;
 *       ledArrayConfig[i].ledMonochrome.monochromePin.dimming.sourceClock = 48000000;
 *       ledArrayConfig[i].ledMonochrome.monochromePin.dimming.instance = 0;
 *       ledArrayConfig[i].ledMonochrome.monochromePin.dimming.channel = 1;
 *       ledArrayConfig[i].ledMonochrome.monochromePin.dimming.pinStateDefault = 0;
 *       LED_Init((led_handle_t)s_ledArrayHandle[i], &ledArrayConfig[i]);
 *   }
 *  @endcode
 *
 * @param ledHandle Pointer to point to a memory space of size #LED_HANDLE_SIZE allocated by the caller.
 * The handle should be 4 byte aligned, because unaligned access doesn't be supported on some devices.
 * You can define one handle in the following two ways:
 * #LED_HANDLE_DEFINE(ledHandle);
 * or
 * uint32_t ledHandle[((LED_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t))];
 * You can define multiple handles in the following way:
 * #LED_HANDLE_ARRAY_DEFINE(ledHandleArray, count);
 * @param  ledConfig Pointer to user-defined configuration structure.
 *         please note, if the LED_USE_CONFIGURE_STRUCTURE is set to 1, then user must use const buffer
 *         forledConfig, LED module will directly use the const buffer.
 * @retval kStatus_LED_Error An error occurred.
 * @retval kStatus_LED_Success LED initialization succeed.
 */
led_status_t LED_Init(led_handle_t ledHandle, led_config_t *ledConfig);

/*!
 * @brief Deinitializes a LED instance.
 *
 * This function deinitializes the LED instance.
 *
 * @param ledHandle LED handle pointer.
 * @retval kStatus_LED_Success LED de-initialization succeed.
 */
led_status_t LED_Deinit(led_handle_t ledHandle);

/*!
 * @brief Sets the LED color.
 *
 * This function sets the LED color. The function only supports the RGB LED.
 * The default color is #kLED_White. Please refer to #LED_MAKE_COLOR(r,g,b).
 *
 * @param ledHandle LED handle pointer.
 * @param ledRgbColor LED color.
 * @retval kStatus_LED_Error An error occurred.
 * @retval kStatus_LED_Success Color setting succeed.
 */
led_status_t LED_SetColor(led_handle_t ledHandle, led_color_t ledRgbColor);

/*!
 * @brief Turns on or off the LED.
 *
 * This function turns on or off the led.
 *
 * @param ledHandle LED handle pointer.
 * @param turnOnOff Setting value, 1 - turns on, 0 - turns off.
 * @retval kStatus_LED_Error An error occurred.
 * @retval kStatus_LED_Success Successfully turn on or off the LED.
 */
led_status_t LED_TurnOnOff(led_handle_t ledHandle, uint8_t turnOnOff);

/*!
 * @brief Blips the LED.
 *
 * This function blips the led.
 *
 * @param ledHandle LED handle pointer.
 * @retval kStatus_LED_Error An error occurred.
 * @retval kStatus_LED_Success Successfully blip the LED.
 */
led_status_t LED_Blip(led_handle_t ledHandle);

/*!
 * @brief Flashes the LED.
 *
 * This function flashes the led. The flash configuration is passed by using #led_flash_config_t.
 *
 * @param ledHandle LED handle pointer.
 * @param ledFlash LED flash configuration.
 * @retval kStatus_LED_Error An error occurred.
 * @retval kStatus_LED_Success Successfully flash the LED.
 */
led_status_t LED_Flash(led_handle_t ledHandle, led_flash_config_t *ledFlash);

/*!
 * @brief Adjusts the brightness of the LED.
 *
 * This function adjust the brightness of the LED.
 *
 * @param ledHandle LED handle pointer.
 * @param dimmingPeriod The duration of the dimming (unit is ms).
 * @param increasement Brighten or dim (1 - brighten, 0 - dim).
 * @retval kStatus_LED_Error An error occurred.
 * @retval kStatus_LED_Success Successfully adjust the brightness of the LED.
 */
led_status_t LED_Dimming(led_handle_t ledHandle, uint16_t dimmingPeriod, uint8_t increasement);

/*!
 * @brief Prepares to enter low power consumption.
 *
 * This function is used to prepare to enter low power consumption.
 *
 * @param ledHandle LED handle pointer.
 * @retval kStatus_LED_Success Successful operation.
 */
led_status_t LED_EnterLowpower(led_handle_t ledHandle);

/*!
 * @brief Restores from low power consumption.
 *
 * This function is used to restore from low power consumption.
 *
 * @param ledHandle LED handle pointer.
 * @retval kStatus_LED_Success Successful operation.
 */
led_status_t LED_ExitLowpower(led_handle_t ledHandle);

#if defined(__cplusplus)
}
#endif
/*! @}*/
#endif /* __LED_H__ */
