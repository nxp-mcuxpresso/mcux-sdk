/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include "clock_config.h"
#include "fsl_common.h"
#include "fsl_rgpio.h"
#include "fsl_clock.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief The board name */
#define BOARD_NAME "MIMXRT1180-EVK"
#ifndef DEBUG_CONSOLE_UART_INDEX
#define DEBUG_CONSOLE_UART_INDEX 1
#endif

/* The UART to use for debug messages. */
#define BOARD_DEBUG_UART_CLK_FREQ BOARD_DebugConsoleSrcFreq()
#define BOARD_DEBUG_UART_TYPE     kSerialPort_Uart
#ifndef BOARD_DEBUG_UART_CLK_ROOT
#define BOARD_DEBUG_UART_CLK_ROOT kCLOCK_Root_Lpuart0102
#endif
#ifndef BOARD_DEBUG_UART_BASEADDR
#define BOARD_DEBUG_UART_BASEADDR (uint32_t) LPUART1
#endif
#ifndef BOARD_DEBUG_UART_INSTANCE
#define BOARD_DEBUG_UART_INSTANCE 1U
#endif
#ifndef BOARD_UART_IRQ
#define BOARD_UART_IRQ LPUART1_IRQn
#endif
#ifndef BOARD_UART_IRQ_HANDLER
#define BOARD_UART_IRQ_HANDLER LPUART1_IRQHandler
#endif
#ifndef BOARD_DEBUG_UART_BAUDRATE
#define BOARD_DEBUG_UART_BAUDRATE (115200U)
#endif

/* Definitions for eRPC MU transport layer */
#if defined(FSL_FEATURE_MU_SIDE_A)
#define MU_BASE        MU1_MUA
#define MU_IRQ         MU1_IRQn
#define MU_IRQ_HANDLER MU1_IRQHandler
#endif
#if defined(FSL_FEATURE_MU_SIDE_B)
#define MU_BASE        MU1_MUB
#define MU_IRQ         MU1_IRQn
#define MU_IRQ_HANDLER MU1_IRQHandler
#endif
#define MU_IRQ_PRIORITY (2)

/*! @brief The USER_LED used for board */
#define LOGIC_LED_ON  (1U)
#define LOGIC_LED_OFF (0U)
#ifndef BOARD_USER_LED_GPIO
#define BOARD_USER_LED_GPIO RGPIO4
#endif
#ifndef BOARD_USER_LED_GPIO_PIN
#define BOARD_USER_LED_GPIO_PIN (27U)
#endif

#define USER_LED_INIT(output)                                             \
    RGPIO_PinWrite(BOARD_USER_LED_GPIO, BOARD_USER_LED_GPIO_PIN, output); \
    BOARD_USER_LED_GPIO->PDDR |= (1U << BOARD_USER_LED_GPIO_PIN)                        /*!< Enable target USER_LED */
#define USER_LED_OFF() \
    RGPIO_PortClear(BOARD_USER_LED_GPIO, 1U << BOARD_USER_LED_GPIO_PIN)                 /*!< Turn off target USER_LED */
#define USER_LED_ON() RGPIO_PortSet(BOARD_USER_LED_GPIO, 1U << BOARD_USER_LED_GPIO_PIN) /*!<Turn on target USER_LED*/
#define USER_LED_TOGGLE() \
    RGPIO_PortToggle(BOARD_USER_LED_GPIO, 1u << BOARD_USER_LED_GPIO_PIN)                /*!< Toggle target USER_LED */

/*! @brief Define the port interrupt number for the board switches */
#ifndef BOARD_USER_BUTTON_GPIO
#define BOARD_USER_BUTTON_GPIO RGPIO1
#endif
#ifndef BOARD_USER_BUTTON_GPIO_PIN
#define BOARD_USER_BUTTON_GPIO_PIN (4U)
#endif
#define BOARD_USER_BUTTON_IRQ         GPIO1_0_IRQn
#define BOARD_USER_BUTTON_IRQ_HANDLER GPIO1_0_IRQHandler
#define BOARD_USER_BUTTON_NAME        "SW8"

/*! @brief The board flash size */
#define BOARD_FLASH_SIZE (0x1000000U)

/*! @brief The Ethernet PHY addresses. */
#define BOARD_EP0_PHY_ADDR       (0x03U)
#define BOARD_SWT_PORT0_PHY_ADDR (0x02U)
#define BOARD_SWT_PORT1_PHY_ADDR (0x05U)
#define BOARD_SWT_PORT2_PHY_ADDR (0x04U)
#define BOARD_SWT_PORT3_PHY_ADDR (0x07U)

/* USB PHY condfiguration */
#define BOARD_USB_PHY_D_CAL     (0x07U)
#define BOARD_USB_PHY_TXCAL45DP (0x06U)
#define BOARD_USB_PHY_TXCAL45DM (0x06U)

#define BOARD_ARDUINO_INT_IRQ   (GPIO1_INT3_IRQn)
#define BOARD_ARDUINO_I2C_IRQ   (LPI2C1_IRQn)
#define BOARD_ARDUINO_I2C_INDEX (1)

#define BOARD_HAS_SDCARD (1U)

/* @Brief Board accelerator sensor configuration */
#define BOARD_ACCEL_I2C_BASEADDR LPI2C2
/* Clock divider for LPI2C clock source */
#define BOARD_ACCEL_I2C_CLOCK_FREQ (CLOCK_GetRootClockFreq(kCLOCK_Root_Lpi2c0102))

#define BOARD_CODEC_I2C_BASEADDR             LPI2C2
#define BOARD_CODEC_I2C_INSTANCE             2U
#define BOARD_CODEC_I2C_CLOCK_SOURCE_SELECT  (0U)
#define BOARD_CODEC_I2C_CLOCK_SOURCE_DIVIDER (6U)
#define BOARD_CODEC_I2C_CLOCK_FREQ           (24000000U)

/* SD card detection method when using wifi module. */
#define BOARD_WIFI_SD_DETECT_TYPE kSDMMCHOST_DetectCardByHostDATA3

#define BOARD_BT_UART_INSTANCE 10
#define BOARD_BT_UART_BAUDRATE 3000000
#define BOARD_BT_UART_CLK_FREQ CLOCK_GetRootClockFreq(kCLOCK_Root_Lpuart0910);

/*! @brief The Ethernet port used by network examples, default use 1G port. */
/* Below comment is for test script to easily define which port to be used, please don't delete. */
/* @TEST_ANCHOR */
#ifndef BOARD_NETWORK_USE_100M_ENET_PORT
#define BOARD_NETWORK_USE_100M_ENET_PORT (0U)
#endif

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
status_t BOARD_LPI2C_SendSCCB(LPI2C_Type *base,
                              uint8_t deviceAddress,
                              uint32_t subAddress,
                              uint8_t subaddressSize,
                              uint8_t *txBuff,
                              uint8_t txBuffSize);
status_t BOARD_LPI2C_ReceiveSCCB(LPI2C_Type *base,
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
void BOARD_Camera_I2C_Init(void);
status_t BOARD_Camera_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
status_t BOARD_Camera_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);

status_t BOARD_Camera_I2C_SendSCCB(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
status_t BOARD_Camera_I2C_ReceiveSCCB(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);

void BOARD_MIPIPanelTouch_I2C_Init(void);
status_t BOARD_MIPIPanelTouch_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
status_t BOARD_MIPIPanelTouch_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);
#endif /* SDK_I2C_BASED_COMPONENT_USED */

void BOARD_SD_Pin_Config(uint32_t speed, uint32_t strength);
void BOARD_MMC_Pin_Config(uint32_t speed, uint32_t strength);

void BOARD_FlexspiClockSafeConfig(void);
AT_QUICKACCESS_SECTION_CODE(void BOARD_SetFlexspiClock(FLEXSPI_Type *base, uint8_t src, uint32_t divider));
AT_QUICKACCESS_SECTION_CODE(void BOARD_DeinitFlash(FLEXSPI_Type *base));
AT_QUICKACCESS_SECTION_CODE(void BOARD_InitFlash(FLEXSPI_Type *base));

void BOARD_NETC_Init(void);
#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
