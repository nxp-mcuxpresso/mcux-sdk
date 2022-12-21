/*
 * Copyright 2021-2022 NXP
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
#define BOARD_NAME "KW45B41Z-EVK"

/* The UART to use for debug messages. */
#define BOARD_USE_LPUART
#define BOARD_DEBUG_UART_TYPE     kSerialPort_Uart
#define BOARD_DEBUG_UART_BASEADDR (uint32_t) LPUART1
#define BOARD_DEBUG_UART_INSTANCE 1U
#define BOARD_DEBUG_UART_CLK_FREQ (CLOCK_GetFreq(kCLOCK_ScgSircClk))

#ifndef BOARD_DEBUG_UART_BAUDRATE
#define BOARD_DEBUG_UART_BAUDRATE (115200U)
#endif /* BOARD_DEBUG_UART_BAUDRATE */

/*! @brief The LPSPI channel used for the external NOR flash */
#define BOARD_EEPROM_LPSPI_BASEADDR  LPSPI1
#define BOARD_LPSPI_CLK_FREQ         16000000U
#define BOARD_LPSPI_MRCC_ADDRESS     kCLOCK_Lpspi1
#define BOARD_LPSPI_CLKSRC           kCLOCK_IpSrcFro192M
#define BOARD_LPSPI_PCS_FOR_INIT     kLPSPI_Pcs0
#define BOARD_LPSPI_PCS_FOR_TRANSFER kLPSPI_MasterPcs0
#define BOARD_LPSPI_MRCC_CLK_DIV     1U
#define BOARD_LPSPI_NOR_BAUDRATE     4000000U

/*! @brief The TPM channel used for board */
#define BOARD_TPM_CHANNEL 0U

#define LOGIC_LED_ON  1U
#define LOGIC_LED_OFF 0U

#ifndef BOARD_LED1_GPIO
#define BOARD_LED1_GPIO GPIOA
#endif
#ifndef BOARD_LED1_GPIO_PIN
#define BOARD_LED1_GPIO_PIN 19U
#endif

#ifndef BOARD_LED2_GPIO
#define BOARD_LED2_GPIO GPIOA
#endif
#ifndef BOARD_LED2_GPIO_PIN
#define BOARD_LED2_GPIO_PIN 20U
#endif

#ifndef BOARD_LED3_GPIO
#define BOARD_LED3_GPIO GPIOA
#endif
#ifndef BOARD_LED3_GPIO_PIN
#define BOARD_LED3_GPIO_PIN 21U
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
    BOARD_LED3_GPIO->PDDR |= (1U << BOARD_LED3_GPIO_PIN)                          /*!< Enable target LED3 */
#define LED3_ON()     GPIO_PortSet(BOARD_LED3_GPIO, 1U << BOARD_LED3_GPIO_PIN)    /*!< Turn on target LED3 */
#define LED3_OFF()    GPIO_PortClear(BOARD_LED3_GPIO, 1U << BOARD_LED3_GPIO_PIN)  /*!< Turn off target LED3 */
#define LED3_TOGGLE() GPIO_PortToggle(BOARD_LED3_GPIO, 1U << BOARD_LED3_GPIO_PIN) /*!< Toggle on target LED3 */

#define BOARD_SW2_NAME        "SW2"
#define BOARD_SW2_GPIO        GPIOD
#define BOARD_SW2_GPIO_PIN    1U
#define BOARD_SW2_IRQ         GPIOD_INT0_IRQn
#define BOARD_SW2_IRQ_HANDLER GPIOD_INT0_IRQHandler

#define BOARD_SW3_NAME        "SW3"
#define BOARD_SW3_GPIO        GPIOC
#define BOARD_SW3_GPIO_PIN    6U
#define BOARD_SW3_IRQ         GPIOC_INT0_IRQn
#define BOARD_SW3_IRQ_HANDLER GPIOC_INT0_IRQHandler

#define BOARD_SW4_NAME        "SW4"
#define BOARD_SW4_GPIO        GPIOA
#define BOARD_SW4_GPIO_PIN    4U
#define BOARD_SW4_IRQ         GPIOA_INT0_IRQn
#define BOARD_SW4_IRQ_HANDLER GPIOA_INT0_IRQHandler

#define BOARD_ACCEL_I2C_BASEADDR LPI2C1

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
