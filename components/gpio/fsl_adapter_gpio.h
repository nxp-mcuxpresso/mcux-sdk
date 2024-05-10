/*
 * Copyright 2018-2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __HAL_GPIO_H__
#define __HAL_GPIO_H__

#include "fsl_common.h"
#if defined(SDK_OS_FREE_RTOS)
#include "FreeRTOS.h"
#endif

/*!
 * @addtogroup GPIO_Adapter
 * @{
 */

/*******************************************************************************
 * Public macro
 ******************************************************************************/
/*! @name Driver version */
/*@{*/
#define FSL_GPIO_ADAPTER_VERSION (MAKE_VERSION(1, 0, 1)) /*!< Version 1.0.1. */
                                                         /*@}*/

/*! @brief Definition of GPIO conflict check Enable. */
#ifndef HAL_GPIO_CONFLICT_CHECK_ENABLE
#define HAL_GPIO_CONFLICT_CHECK_ENABLE (1)
#endif

/*! @brief Definition of GPIO adapter handle size. */
#define HAL_GPIO_HANDLE_SIZE (16U)

/*!
 * @brief Defines the gpio handle
 *
 * This macro is used to define a 4 byte aligned gpio handle.
 * Then use "(hal_gpio_handle_t)name" to get the gpio handle.
 *
 * The macro should be global and could be optional. You could also define gpio handle by yourself.
 *
 * This is an example,
 * @code
 * GPIO_HANDLE_DEFINE(gpioHandle);
 * @endcode
 *
 * @param name The name string of the gpio handle.
 */
#define GPIO_HANDLE_DEFINE(name) uint32_t name[((HAL_GPIO_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t))]

/*! @brief Definition of GPIO adapter isr priority. */
#ifndef HAL_GPIO_ISR_PRIORITY
#if defined(__GIC_PRIO_BITS)
#define HAL_GPIO_ISR_PRIORITY (25U)
#else
#if defined(configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY)
#define HAL_GPIO_ISR_PRIORITY (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY)
#else
/* The default value 3 is used to support different ARM Core, such as CM0P, CM4, CM7, and CM33, etc.
 * The minimum number of priority bits implemented in the NVIC is 2 on these SOCs. The value of mininum
 * priority is 3 (2^2 - 1). So, the default value is 3.
 */
#define HAL_GPIO_ISR_PRIORITY (3U)
#endif /* defined(configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY) */
#endif /* defined(__GIC_PRIO_BITS) */
#endif /* HAL_GPIO_ISR_PRIORITY */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief The handle of GPIO adapter. */
typedef void *hal_gpio_handle_t;

/*! @brief The callback function of GPIO adapter. */
typedef void (*hal_gpio_callback_t)(void *param);

/*! @brief The interrupt trigger of GPIO adapter. */
typedef enum _hal_gpio_interrupt_trigger
{
    kHAL_GpioInterruptDisable     = 0x0U, /*!< Interrupt disable. */
    kHAL_GpioInterruptLogicZero   = 0x1U, /*!< Interrupt when logic zero. */
    kHAL_GpioInterruptRisingEdge  = 0x2U, /*!< Interrupt on rising edge. */
    kHAL_GpioInterruptFallingEdge = 0x3U, /*!< Interrupt on falling edge. */
    kHAL_GpioInterruptEitherEdge  = 0x4U, /*!< Interrupt on either edge. */
    kHAL_GpioInterruptLogicOne    = 0x5U, /*!< Interrupt when logic one. */
} hal_gpio_interrupt_trigger_t;

/*! @brief The status of GPIO adapter. */
typedef enum _hal_gpio_status
{
    kStatus_HAL_GpioSuccess     = kStatus_Success,                       /*!< Success */
    kStatus_HAL_GpioError       = MAKE_STATUS(kStatusGroup_HAL_GPIO, 1), /*!< Failed */
    kStatus_HAL_GpioLackSource  = MAKE_STATUS(kStatusGroup_HAL_GPIO, 2), /*!< Lack of sources */
    kStatus_HAL_GpioPinConflict = MAKE_STATUS(kStatusGroup_HAL_GPIO, 3), /*!< PIN conflict */
} hal_gpio_status_t;

/*! @brief The direction of GPIO adapter. */
typedef enum _hal_gpio_direction
{
    kHAL_GpioDirectionIn = 0x00U, /*!< Out */
    kHAL_GpioDirectionOut,        /*!< In */
} hal_gpio_direction_t;

/*! @brief The pin config struct of GPIO adapter. */
typedef struct _hal_gpio_pin_config
{
    hal_gpio_direction_t direction;
    uint8_t level;
    uint8_t port;
    uint8_t pin;
} hal_gpio_pin_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Initializes static variable located in .bss section.
 *
 * This function is used to initialize variable located in .bss section.
 * Usually users don't need to call this API.
 * It's just used in the case GPIO adapter is used before .bss section is automatically cleaned up by IDE.
 * Example below shows how to use this API.
 *  @code
 *   HAL_GpioPreInit();
 *   GPIO_HANDLE_DEFINE(g_GpioHandle);
 *   hal_gpio_pin_config_t config;
 *   config.direction = kHAL_GpioDirectionOut;
 *   config.port = 0;
 *   config.pin = 0;
 *   config.level = 0;
 *   HAL_GpioInit((hal_gpio_handle_t)g_GpioHandle, &config);
 *  @endcode
 */
void HAL_GpioPreInit(void);

/*!
 * @brief Initializes an GPIO instance with the GPIO handle and the user configuration structure.
 *
 * This function configures the GPIO module with user-defined settings. The user can configure the configuration
 * structure. The parameter gpioHandle is a pointer to point to a memory space of size #HAL_GPIO_HANDLE_SIZE allocated
 * by the caller. Example below shows how to use this API to configure the GPIO.
 *  @code
 *   GPIO_HANDLE_DEFINE(g_GpioHandle);
 *   hal_gpio_pin_config_t config;
 *   config.direction = kHAL_GpioDirectionOut;
 *   config.port = 0;
 *   config.pin = 0;
 *   config.level = 0;
 *   HAL_GpioInit((hal_gpio_handle_t)g_GpioHandle, &config);
 *  @endcode
 *
 * @param gpioHandle GPIO handle pointer.
 * The handle should be 4 byte aligned, because unaligned access doesn't be supported on some devices.
 * You can define the handle in the following two ways:
 * #GPIO_HANDLE_DEFINE(gpioHandle);
 * or
 * uint32_t gpioHandle[((HAL_GPIO_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t))];
 * @param pinConfig Pointer to user-defined configuration structure.
 * @retval kStatus_HAL_GpioError An error occurred while initializing the GPIO.
 * @retval kStatus_HAL_GpioPinConflict The pair of the pin and port passed by pinConfig is initialized.
 * @retval kStatus_HAL_GpioSuccess GPIO initialization succeed
 */
hal_gpio_status_t HAL_GpioInit(hal_gpio_handle_t gpioHandle, hal_gpio_pin_config_t *pinConfig);

/*!
 * @brief Deinitializes a GPIO instance.
 *
 * This function disables the trigger mode.
 *
 * @param gpioHandle GPIO handle pointer.
 * The handle should be 4 byte aligned, because unaligned access doesn't be supported on some devices.
 * @retval kStatus_HAL_GpioSuccess GPIO de-initialization succeed
 */
hal_gpio_status_t HAL_GpioDeinit(hal_gpio_handle_t gpioHandle);

/*!
 * @brief Gets the pin voltage.
 *
 * This function gets the pin voltage. 0 - low level voltage, 1 - high level voltage.
 *
 * @param gpioHandle GPIO handle pointer.
 * The handle should be 4 byte aligned, because unaligned access doesn't be supported on some devices.
 * @param pinState A pointer to save the pin state.
 * @retval kStatus_HAL_GpioSuccess Get successfully.
 */
hal_gpio_status_t HAL_GpioGetInput(hal_gpio_handle_t gpioHandle, uint8_t *pinState);

/*!
 * @brief Sets the pin voltage.
 *
 * This function sets the pin voltage. 0 - low level voltage, 1 - high level voltage.
 *
 * @param gpioHandle GPIO handle pointer.
 * The handle should be 4 byte aligned, because unaligned access doesn't be supported on some devices.
 * @param pinState Pin state.
 * @retval kStatus_HAL_GpioSuccess Set successfully.
 */
hal_gpio_status_t HAL_GpioSetOutput(hal_gpio_handle_t gpioHandle, uint8_t pinState);

/*!
 * @brief Gets the pin interrupt trigger mode.
 *
 * This function gets the pin interrupt trigger mode. The trigger mode please refer to
 * #hal_gpio_interrupt_trigger_t.
 *
 * @param gpioHandle GPIO handle pointer.
 * The handle should be 4 byte aligned, because unaligned access doesn't be supported on some devices.
 * @param gpioTrigger A pointer to save the pin trigger mode value.
 * @retval kStatus_HAL_GpioSuccess Get successfully.
 * @retval kStatus_HAL_GpioError The pin is the ouput setting.
 */
hal_gpio_status_t HAL_GpioGetTriggerMode(hal_gpio_handle_t gpioHandle, hal_gpio_interrupt_trigger_t *gpioTrigger);

/*!
 * @brief Sets the pin interrupt trigger mode.
 *
 * This function sets the pin interrupt trigger mode. The trigger mode please refer to
 * #hal_gpio_interrupt_trigger_t.
 *
 * @param gpioHandle GPIO handle pointer.
 * The handle should be 4 byte aligned, because unaligned access doesn't be supported on some devices.
 * @param gpioTrigger The pin trigger mode value.
 * @retval kStatus_HAL_GpioSuccess Set successfully.
 * @retval kStatus_HAL_GpioError The pin is the ouput setting.
 */
hal_gpio_status_t HAL_GpioSetTriggerMode(hal_gpio_handle_t gpioHandle, hal_gpio_interrupt_trigger_t gpioTrigger);

/*!
 * @brief Installs a callback and callback parameter.
 *
 * This function is used to install the callback and callback parameter for GPIO module.
 * When the pin state interrupt happened, the driver will notify the upper layer by the installed callback
 * function. After the callback called, the GPIO pin state can be got by calling function #HAL_GpioGetInput.
 *
 * @param gpioHandle GPIO handle pointer.
 * The handle should be 4 byte aligned, because unaligned access doesn't be supported on some devices.
 * @param callback The callback function.
 * @param callbackParam The parameter of the callback function.
 * @retval kStatus_HAL_GpioSuccess Successfully install the callback.
 */
hal_gpio_status_t HAL_GpioInstallCallback(hal_gpio_handle_t gpioHandle,
                                          hal_gpio_callback_t callback,
                                          void *callbackParam);

/*!
 * @brief Enables or disables the GPIO wake-up feature.
 *
 * This function enables or disables the GPIO wake-up feature.
 *
 * @param gpioHandle GPIO handle pointer.
 * The handle should be 4 byte aligned, because unaligned access doesn't be supported on some devices.
 * @param enable enable or disable (0 - disable, 1 - enable).
 * @retval kStatus_HAL_GpioError An error occurred.
 * @retval kStatus_HAL_GpioSuccess Set successfully.
 */
hal_gpio_status_t HAL_GpioWakeUpSetting(hal_gpio_handle_t gpioHandle, uint8_t enable);

/*!
 * @brief Prepares to enter low power consumption.
 *
 * This function is used to prepare to enter low power consumption.
 *
 * @param gpioHandle GPIO handle pointer.
 * The handle should be 4 byte aligned, because unaligned access doesn't be supported on some devices.
 * @retval kStatus_HAL_GpioSuccess Successful operation.
 */
hal_gpio_status_t HAL_GpioEnterLowpower(hal_gpio_handle_t gpioHandle);

/*!
 * @brief Restores from low power consumption.
 *
 * This function is used to restore from low power consumption.
 *
 * @param gpioHandle GPIO handle pointer.
 * The handle should be 4 byte aligned, because unaligned access doesn't be supported on some devices.
 * @retval kStatus_HAL_GpioSuccess Successful operation.
 */
hal_gpio_status_t HAL_GpioExitLowpower(hal_gpio_handle_t gpioHandle);

#if defined(__cplusplus)
}
#endif /* __cplusplus */
/*! @}*/
#endif /* __HAL_GPIO_H__ */
