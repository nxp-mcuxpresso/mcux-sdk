/*
 * Copyright 2020 NXP
 * All rights reserved.
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
#define BOARD_NAME "MIMXRT1024-EVK"

/* The UART to use for debug messages. */
#define BOARD_DEBUG_UART_TYPE     kSerialPort_Uart
#define BOARD_DEBUG_UART_BASEADDR (uint32_t) LPUART1
#define BOARD_DEBUG_UART_INSTANCE 1U

#define BOARD_DEBUG_UART_CLK_FREQ BOARD_DebugConsoleSrcFreq()

#define BOARD_UART_IRQ         LPUART1_IRQn
#define BOARD_UART_IRQ_HANDLER LPUART1_IRQHandler

#ifndef BOARD_DEBUG_UART_BAUDRATE
#define BOARD_DEBUG_UART_BAUDRATE (115200U)
#endif /* BOARD_DEBUG_UART_BAUDRATE */

/* @Brief Board accelerator sensor configuration */
#define BOARD_ACCEL_I2C_BASEADDR             LPI2C4
#define BOARD_ACCEL_I2C_CLOCK_SOURCE_SELECT  (0U)
#define BOARD_ACCEL_I2C_CLOCK_SOURCE_DIVIDER (5U)
#define BOARD_ACCEL_I2C_CLOCK_FREQ           (CLOCK_GetFreq(kCLOCK_Usb1PllClk) / 8 / (BOARD_ACCEL_I2C_CLOCK_SOURCE_DIVIDER + 1U))

#define BOARD_CODEC_I2C_BASEADDR             LPI2C1
#define BOARD_CODEC_I2C_INSTANCE             1U
#define BOARD_CODEC_I2C_CLOCK_SOURCE_SELECT  (0U)
#define BOARD_CODEC_I2C_CLOCK_SOURCE_DIVIDER (5U)
#define BOARD_CODEC_I2C_CLOCK_FREQ           (10000000U)

/*! @brief The USER_LED used for board */
#define LOGIC_LED_ON  (1U)
#define LOGIC_LED_OFF (0U)
#ifndef BOARD_USER_LED_GPIO
#define BOARD_USER_LED_GPIO GPIO1
#endif
#ifndef BOARD_USER_LED_GPIO_PIN
#define BOARD_USER_LED_GPIO_PIN (24U)
#endif

#define USER_LED_INIT(output)                                            \
    GPIO_PinWrite(BOARD_USER_LED_GPIO, BOARD_USER_LED_GPIO_PIN, output); \
    BOARD_USER_LED_GPIO->GDIR |= (1U << BOARD_USER_LED_GPIO_PIN) /*!< Enable target USER_LED */
#define USER_LED_OFF() \
    GPIO_PortClear(BOARD_USER_LED_GPIO, 1U << BOARD_USER_LED_GPIO_PIN)                 /*!< Turn off target USER_LED */
#define USER_LED_ON() GPIO_PortSet(BOARD_USER_LED_GPIO, 1U << BOARD_USER_LED_GPIO_PIN) /*!<Turn on target USER_LED*/
#define USER_LED_TOGGLE()                                       \
    GPIO_PinWrite(BOARD_USER_LED_GPIO, BOARD_USER_LED_GPIO_PIN, \
                  0x1 ^ GPIO_PinRead(BOARD_USER_LED_GPIO, BOARD_USER_LED_GPIO_PIN)) /*!< Toggle target USER_LED */

/*! @brief Define the port interrupt number for the board switches */
#ifndef BOARD_USER_BUTTON_GPIO
#define BOARD_USER_BUTTON_GPIO GPIO5
#endif
#ifndef BOARD_USER_BUTTON_GPIO_PIN
#define BOARD_USER_BUTTON_GPIO_PIN (0U)
#endif
#define BOARD_USER_BUTTON_IRQ         GPIO5_Combined_0_15_IRQn
#define BOARD_USER_BUTTON_IRQ_HANDLER GPIO5_Combined_0_15_IRQHandler
#define BOARD_USER_BUTTON_NAME        "SW4"

/*! @brief The board flash size */
#define BOARD_FLASH_SIZE (0x400000U)

/*! @brief The ENET PHY address. */
#define BOARD_ENET0_PHY_ADDRESS (0x02U) /* Phy address of enet port 0. */

/* USB PHY condfiguration */
#define BOARD_USB_PHY_D_CAL     (0x0CU)
#define BOARD_USB_PHY_TXCAL45DP (0x06U)
#define BOARD_USB_PHY_TXCAL45DM (0x06U)

#define BOARD_ARDUINO_INT_IRQ   (GPIO1_Combined_16_31_IRQn)
#define BOARD_ARDUINO_I2C_IRQ   (LPI2C4_IRQn)
#define BOARD_ARDUINO_I2C_INDEX (4)

/* Display. */
#define BOARD_LCD_DC_GPIO     GPIO1 /*! LCD data/command port */
#define BOARD_LCD_DC_GPIO_PIN 15U   /*! LCD data/command pin */

/* @Brief Board Bluetooth HCI UART configuration */
#define BOARD_BT_UART_BASEADDR    LPUART3
#define BOARD_BT_UART_CLK_FREQ    BOARD_DebugConsoleSrcFreq()
#define BOARD_BT_UART_IRQ         LPUART3_IRQn
#define BOARD_BT_UART_IRQ_HANDLER LPUART3_IRQHandler

/*! @brief board has sdcard */
#define BOARD_HAS_SDCARD (1U)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * API
 ******************************************************************************/
uint32_t BOARD_DebugConsoleSrcFreq(void);

void BOARD_InitDebugConsole(void);
void BOARD_ConfigMPU(void);
#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
void BOARD_InitDebugConsole(void);
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
void BOARD_Codec_I2C_Init(void);
status_t BOARD_Codec_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
status_t BOARD_Codec_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);
#endif /* SDK_I2C_BASED_COMPONENT_USED */
void BOARD_SD_Pin_Config(uint32_t speed, uint32_t strength);
void BOARD_MMC_Pin_Config(uint32_t speed, uint32_t strength);
#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
