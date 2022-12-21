/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include "clock_config.h"
#include "fsl_gpio.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief The board name */
#define BOARD_NAME "FRDM-K22F"

/*! @brief The UART to use for debug messages. */
#define BOARD_USE_UART
#define BOARD_DEBUG_UART_TYPE DEBUG_CONSOLE_DEVICE_TYPE_UART
#define BOARD_DEBUG_UART_BASEADDR (uint32_t) UART1
#define BOARD_DEBUG_UART_CLKSRC SYS_CLK
#define BOARD_DEBUG_UART_CLK_FREQ CLOCK_GetCoreSysClkFreq()
#define BOARD_UART_IRQ UART1_RX_TX_IRQn
#define BOARD_UART_IRQ_HANDLER UART1_RX_TX_IRQHandler

#ifndef BOARD_DEBUG_UART_BAUDRATE
#define BOARD_DEBUG_UART_BAUDRATE 115200
#endif /* BOARD_DEBUG_UART_BAUDRATE */

/*! @brief The bubble level demo information */
#define BOARD_FXOS8700_ADDR 0x1C
#define BOARD_ACCEL_ADDR BOARD_FXOS8700_ADDR
#define BOARD_ACCEL_BAUDRATE 100
#define BOARD_ACCEL_I2C_BASEADDR I2C0

/*! @brief The i2c instance used for i2c connection by default */
#define BOARD_I2C_BASEADDR I2C0

/*! @brief The CMP instance/channel used for board. */
#define BOARD_CMP_BASEADDR CMP0
#define BOARD_CMP_CHANNEL 0U

/*! @brief The rtc instance used for board. */
#define BOARD_RTC_FUNC_BASEADDR RTC

/*! @brief Define the port interrupt number for the board switches */
#define BOARD_SW3_GPIO GPIOB
#define BOARD_SW3_PORT PORTB
#define BOARD_SW3_GPIO_PIN 17
#define BOARD_SW3_IRQ PORTB_IRQn
#define BOARD_SW3_IRQ_HANDLER PORTB_IRQHandler
#define BOARD_SW3_NAME "SW3"

#define BOARD_SW2_GPIO GPIOC
#define BOARD_SW2_PORT PORTC
#define BOARD_SW2_GPIO_PIN 1
#define BOARD_SW2_IRQ PORTC_IRQn
#define BOARD_SW2_IRQ_HANDLER PORTC_IRQHandler
#define BOARD_SW2_NAME "SW2"

/* Board led color mapping */
#define LOGIC_LED_ON 0U
#define LOGIC_LED_OFF 1U
#define BOARD_LED_RED_GPIO GPIOA
#define BOARD_LED_RED_GPIO_PORT PORTA
#define BOARD_LED_RED_GPIO_PIN 1U
#define BOARD_LED_GREEN_GPIO GPIOA
#define BOARD_LED_GREEN_GPIO_PORT PORTA
#define BOARD_LED_GREEN_GPIO_PIN 2U
#define BOARD_LED_BLUE_GPIO GPIOD
#define BOARD_LED_BLUE_GPIO_PORT PORTD
#define BOARD_LED_BLUE_GPIO_PIN 5U

#define LED_RED_INIT(output)                                                 \
    GPIO_WritePinOutput(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, output); \
    BOARD_LED_RED_GPIO->PDDR |= (1U << BOARD_LED_RED_GPIO_PIN) /*!< Enable target LED_RED */
#define LED_RED_ON() \
    GPIO_ClearPinsOutput(BOARD_LED_RED_GPIO, 1U << BOARD_LED_RED_GPIO_PIN) /*!< Turn on target LED_RED */
#define LED_RED_OFF() \
    GPIO_SetPinsOutput(BOARD_LED_RED_GPIO, 1U << BOARD_LED_RED_GPIO_PIN) /*!< Turn off target LED_RED */
#define LED_RED_TOGGLE() \
    GPIO_TogglePinsOutput(BOARD_LED_RED_GPIO, 1U << BOARD_LED_RED_GPIO_PIN) /*!< Toggle on target LED_RED */

#define LED_GREEN_INIT(output)                                                   \
    GPIO_WritePinOutput(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, output); \
    BOARD_LED_GREEN_GPIO->PDDR |= (1U << BOARD_LED_GREEN_GPIO_PIN) /*!< Enable target LED_GREEN */
#define LED_GREEN_ON() \
    GPIO_ClearPinsOutput(BOARD_LED_GREEN_GPIO, 1U << BOARD_LED_GREEN_GPIO_PIN) /*!< Turn on target LED_GREEN */
#define LED_GREEN_OFF() \
    GPIO_SetPinsOutput(BOARD_LED_GREEN_GPIO, 1U << BOARD_LED_GREEN_GPIO_PIN) /*!< Turn off target LED_GREEN */
#define LED_GREEN_TOGGLE() \
    GPIO_TogglePinsOutput(BOARD_LED_GREEN_GPIO, 1U << BOARD_LED_GREEN_GPIO_PIN) /*!< Toggle on target LED_GREEN */

#define LED_BLUE_INIT(output)                                                  \
    GPIO_WritePinOutput(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, output); \
    BOARD_LED_BLUE_GPIO->PDDR |= (1U << BOARD_LED_BLUE_GPIO_PIN) /*!< Enable target LED_BLUE */
#define LED_BLUE_ON() \
    GPIO_ClearPinsOutput(BOARD_LED_BLUE_GPIO, 1U << BOARD_LED_BLUE_GPIO_PIN) /*!< Turn on target LED_BLUE */
#define LED_BLUE_OFF() \
    GPIO_SetPinsOutput(BOARD_LED_BLUE_GPIO, 1U << BOARD_LED_BLUE_GPIO_PIN) /*!< Turn off target LED_BLUE */
#define LED_BLUE_TOGGLE() \
    GPIO_TogglePinsOutput(BOARD_LED_BLUE_GPIO, 1U << BOARD_LED_BLUE_GPIO_PIN) /*!< Toggle on target LED_BLUE */

/* ERPC DSPI configuration */
#define ERPC_BOARD_DSPI_BASEADDR SPI0
#define ERPC_BOARD_DSPI_BAUDRATE 500000U
#define ERPC_BOARD_DSPI_CLKSRC DSPI0_CLK_SRC
#define ERPC_BOARD_DSPI_CLK_FREQ CLOCK_GetFreq(DSPI0_CLK_SRC)
#define ERPC_BOARD_DSPI_INT_GPIO GPIOB
#define ERPC_BOARD_DSPI_INT_PORT PORTB
#define ERPC_BOARD_DSPI_INT_PIN 2U
#define ERPC_BOARD_DSPI_INT_PIN_IRQ PORTB_IRQn
#define ERPC_BOARD_DSPI_INT_PIN_IRQ_HANDLER PORTB_IRQHandler

/* @brief The SDSPI disk PHY configuration. */
#define BOARD_SDSPI_SPI_BASE SPI0_BASE /*!< SPI base address for SDSPI */
#define BOARD_SDSPI_CD_GPIO_BASE GPIOB /*!< Port related to card detect pin for SDSPI */
#define BOARD_SDSPI_CD_PIN 16U         /*!< Card detect pin for SDSPI */
#define BOARD_SDSPI_CD_LOGIC_RISING    /*!< Logic of card detect pin for SDSPI */

/* DAC base address */
#define BOARD_DAC_BASEADDR DAC0

/* Board accelerometer driver */
#define BOARD_ACCEL_FXOS

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * API
 ******************************************************************************/

void BOARD_InitDebugConsole(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
