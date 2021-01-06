/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include "clock_config.h"
#include "fsl_common.h"
#include "fsl_gpio.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief The board name */
#define BOARD_NAME "LPCXPRESSO804"

#define BOARD_EXTCLKINRATE (0)

/*! @brief The UART to use for debug messages. */
#define BOARD_DEBUG_USART_TYPE       kSerialPort_Uart
#define BOARD_DEBUG_USART_BASEADDR   (uint32_t) USART0
#define BOARD_DEBUG_USART_INSTANCE   0U
#define BOARD_DEBUG_USART_CLK_FREQ   CLOCK_GetMainClkFreq()
#define BOARD_DEBUG_USART_CLK_ATTACH kUART0_Clk_From_MainClk
#define BOARD_DEBUG_USART_RST        kUART0_RST_N_SHIFT_RSTn
#define BOARD_USART_IRQ              USART0_IRQn
#define BOARD_USART_IRQ_HANDLER      USART0_IRQHandler

#ifndef BOARD_DEBUG_USART_BAUDRATE
#define BOARD_DEBUG_USART_BAUDRATE 9600
#endif /* BOARD_DEBUG_USART_BAUDRATE */

/*! @brief Board led mapping */
#define LOGIC_LED_ON  0U
#define LOGIC_LED_OFF 1U

/* LED_GREEN */
#ifndef BOARD_LED_GREEN_GPIO
#define BOARD_LED_GREEN_GPIO GPIO
#endif
#define BOARD_LED_GREEN_GPIO_PORT 0U
#ifndef BOARD_LED_GREEN_GPIO_PIN
#define BOARD_LED_GREEN_GPIO_PIN 12U
#endif

#define LED_GREEN_INIT(output)                                                              \
    GPIO_PortInit(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PORT);                         \
    GPIO_PinInit(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PORT, BOARD_LED_GREEN_GPIO_PIN, \
                 &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)}); /*!< Enable target LED_GREEN */
#define LED_GREEN_ON()                                                                       \
    GPIO_PortClear(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PORT,                          \
                   1U << BOARD_LED_GREEN_GPIO_PIN) /*!< Turn on target LED_GREEN \ \ \ \ \ \ \
                                                    */
#define LED_GREEN_OFF()                                                                     \
    GPIO_PortSet(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PORT,                           \
                 1U << BOARD_LED_GREEN_GPIO_PIN) /*!< Turn off target LED_GREEN \ \ \ \ \ \ \
                                                  */
#define LED_GREEN_TOGGLE()                                           \
    GPIO_PortToggle(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PORT, \
                    1U << BOARD_LED_GREEN_GPIO_PIN) /*!< Toggle on target LED_GREEN */

/* LED_BLUE */
#ifndef BOARD_LED_BLUE_GPIO
#define BOARD_LED_BLUE_GPIO GPIO
#endif
#define BOARD_LED_BLUE_GPIO_PORT 0U
#ifndef BOARD_LED_BLUE_GPIO_PIN
#define BOARD_LED_BLUE_GPIO_PIN 11U
#endif

#ifndef BOARD_S1_GPIO
#define BOARD_S1_GPIO GPIO
#endif
#define BOARD_S1_GPIO_PORT 0U
#ifndef BOARD_S1_GPIO_PIN
#define BOARD_S1_GPIO_PIN 13U
#endif
#define BOARD_S1_NAME        "S1"
#define BOARD_S1_IRQ         PIN_INT0_IRQn
#define BOARD_S1_IRQ_HANDLER PIN_INT0_IRQHandler

#define LED_BLUE_INIT(output)                                                            \
    GPIO_PortInit(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PORT);                        \
    GPIO_PinInit(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PORT, BOARD_LED_BLUE_GPIO_PIN, \
                 &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)}); /*!< Enable target LED_GREEN */
#define LED_BLUE_ON()                                                                      \
    GPIO_PortClear(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PORT,                          \
                   1U << BOARD_LED_BLUE_GPIO_PIN) /*!< Turn on target LED_BLUE \ \ \ \ \ \ \
                                                   */
#define LED_BLUE_OFF()                                                                    \
    GPIO_PortSet(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PORT,                           \
                 1U << BOARD_LED_BLUE_GPIO_PIN) /*!< Turn off target LED_BLUE \ \ \ \ \ \ \
                                                 */
#define LED_BLUE_TOGGLE()                                          \
    GPIO_PortToggle(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PORT, \
                    1U << BOARD_LED_BLUE_GPIO_PIN) /*!< Toggle on target LED_BLUE */

/* LED_RED */
#ifndef BOARD_LED_RED_GPIO
#define BOARD_LED_RED_GPIO GPIO
#endif
#define BOARD_LED_RED_GPIO_PORT 0U
#ifndef BOARD_LED_RED_GPIO_PIN
#define BOARD_LED_RED_GPIO_PIN 13U
#endif

#define LED_RED_INIT(output)                                                          \
    GPIO_PortInit(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PORT);                       \
    GPIO_PinInit(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PORT, BOARD_LED_RED_GPIO_PIN, \
                 &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)}); /*!< Enable target LED_GREEN */
#define LED_RED_ON()                                                                     \
    GPIO_PortClear(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PORT,                          \
                   1U << BOARD_LED_RED_GPIO_PIN) /*!< Turn on target LED_RED \ \ \ \ \ \ \
                                                  */
#define LED_RED_OFF()                                                                   \
    GPIO_PortSet(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PORT,                           \
                 1U << BOARD_LED_RED_GPIO_PIN) /*!< Turn off target LED_RED \ \ \ \ \ \ \
                                                */
#define LED_RED_TOGGLE()                                         \
    GPIO_PortToggle(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PORT, \
                    1U << BOARD_LED_RED_GPIO_PIN) /*!< Toggle on target LED_RED */

#ifndef BOARD_SW1_GPIO
#define BOARD_SW1_GPIO GPIO
#endif
#define BOARD_SW1_GPIO_PORT 0U
#ifndef BOARD_SW1_GPIO_PIN
#define BOARD_SW1_GPIO_PIN 13U
#endif
#define BOARD_SW1_NAME        "SW1"
#define BOARD_SW1_IRQ         PIN_INT0_IRQn
#define BOARD_SW1_IRQ_HANDLER PIN_INT0_IRQHandler

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * API
 ******************************************************************************/

status_t BOARD_InitDebugConsole(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
