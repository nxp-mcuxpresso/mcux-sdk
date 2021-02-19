/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include "clock_config.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief The board name */
#define BOARD_NAME "FRDM-K32L3A6"

/* The UART to use for debug messages. */
#define BOARD_DEBUG_UART_TYPE     kSerialPort_Uart
#define BOARD_DEBUG_UART_BAUDRATE 115200U
#define BOARD_DEBUG_UART_BASEADDR (uint32_t) LPUART0
#define BOARD_DEBUG_UART_INSTANCE 0U
#define BOARD_DEBUG_UART_CLK_FREQ CLOCK_GetIpFreq(kCLOCK_Lpuart0)
#define BOARD_UART_IRQ            LPUART0_IRQn
#define BOARD_UART_IRQ_HANDLER    LPUART0_IRQHandler

/* @Brief Board accelerator sensor configuration */
#define BOARD_ACCEL_I2C_BASEADDR   LPI2C3
#define BOARD_ACCEL_I2C_CLOCK_FREQ (CLOCK_GetIpFreq(kCLOCK_Lpi2c3))

/* Definitions for eRPC MU transport layer */
#if defined(FSL_FEATURE_MU_SIDE_A)
#define MU_BASE        MUA
#define MU_IRQ         MUA_IRQn
#define MU_IRQ_HANDLER MUA_IRQHandler
#endif
#if defined(FSL_FEATURE_MU_SIDE_B)
#define MU_BASE        MUB
#define MU_IRQ         MUB_IRQn
#define MU_IRQ_HANDLER MUB_IRQHandler
#endif
#define MU_IRQ_PRIORITY (2)

/*! @brief Define the port interrupt number for the board switches */
#ifndef BOARD_SW2_GPIO
#define BOARD_SW2_GPIO GPIOA
#endif
#ifndef BOARD_SW2_PORT
#define BOARD_SW2_PORT PORTA
#endif
#ifndef BOARD_SW2_GPIO_PIN
#define BOARD_SW2_GPIO_PIN 0U
#endif
#define BOARD_SW2_IRQ         PORTA_IRQn
#define BOARD_SW2_IRQ_HANDLER PORTA_IRQHandler
#define BOARD_SW2_NAME        "SW2"

/* Board led color mapping */
#ifndef BOARD_LED_RED_GPIO
#define BOARD_LED_RED_GPIO GPIOA
#endif
#ifndef BOARD_LED_RED_GPIO_PIN
#define BOARD_LED_RED_GPIO_PIN 24U
#endif

/*! @brief The TPM channel used for board */
#define BOARD_TPM_CHANNEL 0U

#define LOGIC_LED_ON  1U
#define LOGIC_LED_OFF 0U
#ifndef BOARD_LED1_GPIO
#define BOARD_LED1_GPIO GPIOA
#endif
#ifndef BOARD_LED1_GPIO_PIN
#define BOARD_LED1_GPIO_PIN 24U
#endif
#ifndef BOARD_LED2_GPIO
#define BOARD_LED2_GPIO GPIOA
#endif
#ifndef BOARD_LED2_GPIO_PIN
#define BOARD_LED2_GPIO_PIN 23U
#endif
#ifndef BOARD_LED3_GPIO
#define BOARD_LED3_GPIO GPIOA
#endif
#ifndef BOARD_LED3_GPIO_PIN
#define BOARD_LED3_GPIO_PIN 22U
#endif

#ifndef BOARD_LED4_GPIO
#define BOARD_LED4_GPIO GPIOE
#endif
#ifndef BOARD_LED4_GPIO_PIN
#define BOARD_LED4_GPIO_PIN 0U
#endif

#define LED1_INIT(output)                                        \
    GPIO_PinWrite(BOARD_LED1_GPIO, BOARD_LED1_GPIO_PIN, output); \
    BOARD_LED1_GPIO->PDDR |= (1U << BOARD_LED1_GPIO_PIN)                          /*!< Enable target LED1 */
#define LED1_ON()     GPIO_PortSet(BOARD_LED1_GPIO, 1U << BOARD_LED1_GPIO_PIN)    /*!< Turn on target LED1 */
#define LED1_OFF()    GPIO_PortClear(BOARD_LED1_GPIO, 1U << BOARD_LED1_GPIO_PIN)  /*!< Turn off target LED1 */
#define LED1_TOGGLE() GPIO_PortToggle(BOARD_LED1_GPIO, 1U << BOARD_LED1_GPIO_PIN) /*!< Toggle on target LED1 */

#define LED2_INIT(output)                                        \
    GPIO_PinWrite(BOARD_LED2_GPIO, BOARD_LED2_GPIO_PIN, output); \
    BOARD_LED2_GPIO->PDDR |= (1U << BOARD_LED2_GPIO_PIN)                          /*!< Enable target LED2 */
#define LED2_ON()     GPIO_PortSet(BOARD_LED2_GPIO, 1U << BOARD_LED2_GPIO_PIN)    /*!< Turn on target LED2 */
#define LED2_OFF()    GPIO_PortClear(BOARD_LED2_GPIO, 1U << BOARD_LED2_GPIO_PIN)  /*!< Turn off target LED2 */
#define LED2_TOGGLE() GPIO_PortToggle(BOARD_LED2_GPIO, 1U << BOARD_LED2_GPIO_PIN) /*!< Toggle on target LED2 */

#define LED3_INIT(output)                                        \
    GPIO_PinWrite(BOARD_LED3_GPIO, BOARD_LED3_GPIO_PIN, output); \
    BOARD_LED3_GPIO->PDDR |= (1U << BOARD_LED3_GPIO_PIN)                                /*!< Enable target LED3 */
#define LED3_ON()           GPIO_PortSet(BOARD_LED3_GPIO, 1U << BOARD_LED3_GPIO_PIN)    /*!< Turn on target LED3 */
#define LED3_OFF()          GPIO_PortClear(BOARD_LED3_GPIO, 1U << BOARD_LED3_GPIO_PIN)  /*!< Turn off target LED3 */
#define LED3_TOGGLE()       GPIO_PortToggle(BOARD_LED3_GPIO, 1U << BOARD_LED3_GPIO_PIN) /*!< Toggle on target LED3 */

#define LED4_INIT(output)                                        \
    GPIO_PinWrite(BOARD_LED4_GPIO, BOARD_LED4_GPIO_PIN, output); \
    BOARD_LED4_GPIO->PDDR |= (1U << BOARD_LED4_GPIO_PIN)
#define LED4_ON()           GPIO_PortSet(BOARD_LED4_GPIO, 1U << BOARD_LED4_GPIO_PIN)    /*!< Turn on target LED */
#define LED4_OFF()          GPIO_PortClear(BOARD_LED4_GPIO, 1U << BOARD_LED4_GPIO_PIN)  /*!< Turn off target LED */
#define LED4_TOGGLE()       GPIO_PortToggle(BOARD_LED4_GPIO, 1U << BOARD_LED4_GPIO_PIN) /*!< Toggle on target LED */

#define LLWU_SW_GPIO        BOARD_SW2_GPIO
#define LLWU_SW_PORT        BOARD_SW2_PORT
#define LLWU_SW_GPIO_PIN    BOARD_SW2_GPIO_PIN
#define LLWU_SW_IRQ         BOARD_SW2_IRQ
#define LLWU_SW_IRQ_HANDLER BOARD_SW2_IRQ_HANDLER
#define LLWU_SW_NAME        BOARD_SW2_NAME

#ifndef BOARD_SPI_FLASH_CS_GPIO
#define BOARD_SPI_FLASH_CS_GPIO GPIOB
#endif
#ifndef BOARD_SPI_FLASH_CS_GPIO_PIN
#define BOARD_SPI_FLASH_CS_GPIO_PIN 22U
#endif
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * API
 ******************************************************************************/

void BOARD_InitDebugConsole(void);
#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
void BOARD_LPI2C_Init(LPI2C_Type *base, uint32_t clkSrc_Hz);
status_t BOARD_LPI2C_Send(LPI2C_Type *base,
                          uint8_t deviceAddress,
                          uint32_t subAddress,
                          uint8_t subaddressSize,
                          uint8_t *txBuff,
                          uint8_t txBuffSize);
status_t BOARD_LPI2C_Receive(LPI2C_Type *base,
                             uint8_t deviceAddress,
                             uint32_t subAddress,
                             uint8_t subaddressSize,
                             uint8_t *rxBuff,
                             uint8_t rxBuffSize);
void BOARD_Accel_I2C_Init(void);
status_t BOARD_Accel_I2C_Send(uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint32_t txBuff);
status_t BOARD_Accel_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);
#endif /* SDK_I2C_BASED_COMPONENT_USED */
#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
