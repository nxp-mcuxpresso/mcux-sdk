/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
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
#define BOARD_NAME "LPCXPRESSO54S018"

#define BOARD_EXTCLKINRATE (0)

/*! @brief The UART to use for debug messages. */
/* TODO: rename UART to USART */
#define BOARD_DEBUG_UART_TYPE       kSerialPort_Uart
#define BOARD_DEBUG_UART_BASEADDR   (uint32_t) USART0
#define BOARD_DEBUG_UART_INSTANCE   0U
#define BOARD_DEBUG_UART_CLK_FREQ   CLOCK_GetFlexCommClkFreq(0U)
#define BOARD_DEBUG_UART_CLK_ATTACH kFRO12M_to_FLEXCOMM0
#define BOARD_DEBUG_UART_RST        kFC0_RST_SHIFT_RSTn
#define BOARD_UART_IRQ_HANDLER      FLEXCOMM0_IRQHandler
#define BOARD_UART_IRQ              FLEXCOMM0_IRQn
/* TODO: obsolete */
#define BOARD_DEBUG_SPI_CLK_FREQ 12000000

#define BOARD_ACCEL_I2C_BASEADDR   I2C2
#define BOARD_ACCEL_I2C_CLOCK_FREQ 12000000

#define BOARD_CODEC_I2C_BASEADDR   I2C2
#define BOARD_CODEC_I2C_INSTANCE   2U
#define BOARD_CODEC_I2C_CLOCK_FREQ 12000000

#ifndef BOARD_DEBUG_UART_BAUDRATE
#define BOARD_DEBUG_UART_BAUDRATE 115200
#endif /* BOARD_DEBUG_UART_BAUDRATE */

/*! @brief The ENET PHY address. */
#define BOARD_ENET0_PHY_ADDRESS (0x00U) /* Phy address of enet port 0. */

#ifndef BOARD_LED1_GPIO
#define BOARD_LED1_GPIO GPIO
#endif
#define BOARD_LED1_GPIO_PORT 3U
#ifndef BOARD_LED1_GPIO_PIN
#define BOARD_LED1_GPIO_PIN 14U
#endif
#ifndef BOARD_LED2_GPIO
#define BOARD_LED2_GPIO GPIO
#endif
#define BOARD_LED2_GPIO_PORT 3U
#ifndef BOARD_LED2_GPIO_PIN
#define BOARD_LED2_GPIO_PIN 3U
#endif
#ifndef BOARD_LED3_GPIO
#define BOARD_LED3_GPIO GPIO
#endif
#define BOARD_LED3_GPIO_PORT 2U
#ifndef BOARD_LED3_GPIO_PIN
#define BOARD_LED3_GPIO_PIN 2U
#endif

#ifndef BOARD_SW1_GPIO
#define BOARD_SW1_GPIO GPIO
#endif
#define BOARD_SW1_GPIO_PORT 0U
#ifndef BOARD_SW1_GPIO_PIN
#define BOARD_SW1_GPIO_PIN 4U
#endif
#define BOARD_SW1_NAME        "SW1"
#define BOARD_SW3_IRQ         PIN_INT0_IRQn
#define BOARD_SW3_IRQ_HANDLER PIN_INT0_IRQHandler

#ifndef BOARD_SW2_GPIO
#define BOARD_SW2_GPIO GPIO
#endif
#define BOARD_SW2_GPIO_PORT 0U
#ifndef BOARD_SW2_GPIO_PIN
#define BOARD_SW2_GPIO_PIN 6U
#endif
#define BOARD_SW2_NAME        "SW2"
#define BOARD_SW2_IRQ         PIN_INT0_IRQn
#define BOARD_SW2_IRQ_HANDLER PIN_INT0_IRQHandler

#ifndef BOARD_SW3_GPIO
#define BOARD_SW3_GPIO GPIO
#endif
#define BOARD_SW3_GPIO_PORT 0U
#ifndef BOARD_SW3_GPIO_PIN
#define BOARD_SW3_GPIO_PIN 5U
#endif
#define BOARD_SW3_NAME              "SW3"
#define BOARD_SW3_IRQ               PIN_INT0_IRQn
#define BOARD_SW3_IRQ_HANDLER       PIN_INT0_IRQHandler
#define BOARD_SW3_GPIO_PININT_INDEX 0

#ifndef BOARD_SW4_GPIO
#define BOARD_SW4_GPIO GPIO
#endif
#ifndef BOARD_SW4_GPIO_PORT
#define BOARD_SW4_GPIO_PORT 0U
#endif
#ifndef BOARD_SW4_GPIO_PIN
#define BOARD_SW4_GPIO_PIN 4U
#endif
#define BOARD_SW4_NAME              "SW4"
#define BOARD_SW4_IRQ               PIN_INT0_IRQn
#define BOARD_SW4_IRQ_HANDLER       PIN_INT0_IRQHandler
#define BOARD_SW4_GPIO_PININT_INDEX 0

#ifndef BOARD_SW5_GPIO
#define BOARD_SW5_GPIO GPIO
#endif
#ifndef BOARD_SW5_GPIO_PORT
#define BOARD_SW5_GPIO_PORT 1U
#endif
#ifndef BOARD_SW5_GPIO_PIN
#define BOARD_SW5_GPIO_PIN 1U
#endif
#define BOARD_SW5_NAME              "SW5"
#define BOARD_SW5_IRQ               PIN_INT1_IRQn
#define BOARD_SW5_IRQ_HANDLER       PIN_INT1_IRQHandler
#define BOARD_SW5_GPIO_PININT_INDEX 0

#define BOARD_ARDUINO_INT_IRQ   (GINT0_IRQn)
#define BOARD_ARDUINO_I2C_IRQ   (FLEXCOMM2_IRQn)
#define BOARD_ARDUINO_I2C_INDEX (2)

/* Board led color mapping */
#define LOGIC_LED_ON  0U
#define LOGIC_LED_OFF 1U

#define LED1_INIT(output)                                                    \
    GPIO_PinInit(BOARD_LED1_GPIO, BOARD_LED1_GPIO_PORT, BOARD_LED1_GPIO_PIN, \
                 &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)}) /*!< Enable target LED1 */
#define LED1_ON() \
    GPIO_PortClear(BOARD_LED1_GPIO, BOARD_LED1_GPIO_PORT, 1U << BOARD_LED1_GPIO_PIN) /*!< Turn on target LED1 */
#define LED1_OFF() \
    GPIO_PortSet(BOARD_LED1_GPIO, BOARD_LED1_GPIO_PORT, 1U << BOARD_LED1_GPIO_PIN) /*!< Turn off target LED1 */
#define LED1_TOGGLE() \
    GPIO_PortToggle(BOARD_LED1_GPIO, BOARD_LED1_GPIO_PORT, 1U << BOARD_LED1_GPIO_PIN) /*!< Toggle on target LED1 */
#define LED2_INIT(output)                                                    \
    GPIO_PinInit(BOARD_LED2_GPIO, BOARD_LED2_GPIO_PORT, BOARD_LED2_GPIO_PIN, \
                 &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)}) /*!< Enable target LED2 */
#define LED2_ON() \
    GPIO_PortClear(BOARD_LED2_GPIO, BOARD_LED2_GPIO_PORT, 1U << BOARD_LED2_GPIO_PIN) /*!< Turn on target LED2 */
#define LED2_OFF() \
    GPIO_PortSet(BOARD_LED2_GPIO, BOARD_LED2_GPIO_PORT, 1U << BOARD_LED2_GPIO_PIN) /*!< Turn off target LED2 */
#define LED2_TOGGLE() \
    GPIO_PortToggle(BOARD_LED2_GPIO, BOARD_LED2_GPIO_PORT, 1U << BOARD_LED2_GPIO_PIN) /*!< Toggle on target LED2 */

#define LED3_INIT(output)                                                    \
    GPIO_PinInit(BOARD_LED3_GPIO, BOARD_LED3_GPIO_PORT, BOARD_LED3_GPIO_PIN, \
                 &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)}) /*!< Enable target LED3 */
#define LED3_ON() \
    GPIO_PortClear(BOARD_LED3_GPIO, BOARD_LED3_GPIO_PORT, 1U << BOARD_LED3_GPIO_PIN) /*!< Turn on target LED3 */
#define LED3_OFF() \
    GPIO_PortSet(BOARD_LED3_GPIO, BOARD_LED3_GPIO_PORT, 1U << BOARD_LED3_GPIO_PIN) /*!< Turn off target LED3 */
#define LED3_TOGGLE() \
    GPIO_PortToggle(BOARD_LED3_GPIO, BOARD_LED3_GPIO_PORT, 1U << BOARD_LED3_GPIO_PIN) /*!< Toggle on target LED3 */

/*! @brief The WIFI-QCA shield pin. */
#define BOARD_INITGT202SHIELD_PWRON_GPIO      GPIO                /*!< GPIO device name: GPIO */
#define BOARD_INITGT202SHIELD_PWRON_PORT      4U                  /*!< PORT device index: 4 */
#define BOARD_INITGT202SHIELD_PWRON_GPIO_PIN  7U                  /*!< PIO4 pin index: 7 */
#define BOARD_INITGT202SHIELD_PWRON_PIN_NAME  PIO4_7              /*!< Pin name */
#define BOARD_INITGT202SHIELD_PWRON_LABEL     "PWRON"             /*!< Label */
#define BOARD_INITGT202SHIELD_PWRON_NAME      "PWRON"             /*!< Identifier name */
#define BOARD_INITGT202SHIELD_PWRON_DIRECTION kGPIO_DigitalOutput /*!< Direction */

#define BOARD_INITGT202SHIELD_IRQ_GPIO      GPIO               /*!< GPIO device name: GPIO */
#define BOARD_INITGT202SHIELD_IRQ_PORT      1U                 /*!< PORT device index: 1 */
#define BOARD_INITGT202SHIELD_IRQ_GPIO_PIN  22U                /*!< PIO1 pin index: 22 */
#define BOARD_INITGT202SHIELD_IRQ_PIN_NAME  PIO1_22            /*!< Pin name */
#define BOARD_INITGT202SHIELD_IRQ_LABEL     "IRQ"              /*!< Label */
#define BOARD_INITGT202SHIELD_IRQ_NAME      "IRQ"              /*!< Identifier name */
#define BOARD_INITGT202SHIELD_IRQ_DIRECTION kGPIO_DigitalInput /*!< Direction */

/* LCD panel. */
#define BOARD_LCD_BL_GPIO          3
#define BOARD_LCD_BL_PIN           31
#define BOARD_TOUCH_PANEL_RST_GPIO 2
#define BOARD_TOUCH_PANEL_RST_PIN  27

/* Serial MWM WIFI */
#define BOARD_SERIAL_MWM_PORT_CLK_FREQ CLOCK_GetFlexCommClkFreq(4)
#define BOARD_SERIAL_MWM_PORT          USART4
#define BOARD_SERIAL_MWM_PORT_IRQn     FLEXCOMM4_IRQn
#define BOARD_SERIAL_MWM_RST_GPIO      GPIO
#define BOARD_SERIAL_MWM_RST_PORT      1
#define BOARD_SERIAL_MWM_RST_PIN       0
#define BOARD_SERIAL_MWM_RST_WRITE(output) \
    GPIO_PinWrite(BOARD_SERIAL_MWM_RST_GPIO, BOARD_SERIAL_MWM_RST_PORT, BOARD_SERIAL_MWM_RST_PIN, output)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * API
 ******************************************************************************/

status_t BOARD_InitDebugConsole(void);
void BOARD_InitSDRAM(void);
#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
void BOARD_I2C_Init(I2C_Type *base, uint32_t clkSrc_Hz);
status_t BOARD_I2C_Send(I2C_Type *base,
                        uint8_t deviceAddress,
                        uint32_t subAddress,
                        uint8_t subaddressSize,
                        uint8_t *txBuff,
                        uint8_t txBuffSize);
status_t BOARD_I2C_Receive(I2C_Type *base,
                           uint8_t deviceAddress,
                           uint32_t subAddress,
                           uint8_t subaddressSize,
                           uint8_t *rxBuff,
                           uint8_t rxBuffSize);
void BOARD_Accel_I2C_Init(void);
status_t BOARD_Accel_I2C_Send(uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint32_t txBuff);
status_t BOARD_Accel_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);
void BOARD_Codec_I2C_Init(void);
status_t BOARD_Codec_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
status_t BOARD_Codec_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);
#endif /* SDK_I2C_BASED_COMPONENT_USED */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
