/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Direction type  */
typedef enum _pin_mux_direction
{
    kPIN_MUX_DirectionInput = 0U,        /* Input direction */
    kPIN_MUX_DirectionOutput = 1U,       /* Output direction */
    kPIN_MUX_DirectionInputOrOutput = 2U /* Input or output direction */
} pin_mux_direction_t;

/*!
 * @addtogroup pin_mux
 * @{
 */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/* FC0_RXD_SDA_MOSI (number 31), U18[4]/TO_MUX_P0_0-ISP_RX */
#define BOARD_DEBUG_UART_RX_PERIPHERAL FLEXCOMM0              /*!< Device name: FLEXCOMM0 */
#define BOARD_DEBUG_UART_RX_SIGNAL RXD_SDA_MOSI               /*!< FLEXCOMM0 signal: RXD_SDA_MOSI */
#define BOARD_DEBUG_UART_RX_PIN_NAME FC0_RXD_SDA_MOSI         /*!< Pin name */
#define BOARD_DEBUG_UART_RX_LABEL "U18[4]/TO_MUX_P0_0-ISP_RX" /*!< Label */
#define BOARD_DEBUG_UART_RX_NAME "DEBUG_UART_RX"              /*!< Identifier name */

/* FC0_TXD_SCL_MISO (number 32), U6[4]/U22[3]/P0_1-ISP_TX */
#define BOARD_DEBUG_UART_TX_PERIPHERAL FLEXCOMM0             /*!< Device name: FLEXCOMM0 */
#define BOARD_DEBUG_UART_TX_SIGNAL TXD_SCL_MISO              /*!< FLEXCOMM0 signal: TXD_SCL_MISO */
#define BOARD_DEBUG_UART_TX_PIN_NAME FC0_TXD_SCL_MISO        /*!< Pin name */
#define BOARD_DEBUG_UART_TX_LABEL "U6[4]/U22[3]/P0_1-ISP_TX" /*!< Label */
#define BOARD_DEBUG_UART_TX_NAME "DEBUG_UART_TX"             /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void); /* Function assigned for the Core #0 (ARM Cortex-M4) */

/* FC0_RXD_SDA_MOSI (number 31), U18[4]/TO_MUX_P0_0-ISP_RX */
#define BOARD_DEBUG_UART_RX_PERIPHERAL FLEXCOMM0              /*!< Device name: FLEXCOMM0 */
#define BOARD_DEBUG_UART_RX_SIGNAL RXD_SDA_MOSI               /*!< FLEXCOMM0 signal: RXD_SDA_MOSI */
#define BOARD_DEBUG_UART_RX_PIN_NAME FC0_RXD_SDA_MOSI         /*!< Pin name */
#define BOARD_DEBUG_UART_RX_LABEL "U18[4]/TO_MUX_P0_0-ISP_RX" /*!< Label */
#define BOARD_DEBUG_UART_RX_NAME "DEBUG_UART_RX"              /*!< Identifier name */

/* FC0_TXD_SCL_MISO (number 32), U6[4]/U22[3]/P0_1-ISP_TX */
#define BOARD_DEBUG_UART_TX_PERIPHERAL FLEXCOMM0             /*!< Device name: FLEXCOMM0 */
#define BOARD_DEBUG_UART_TX_SIGNAL TXD_SCL_MISO              /*!< FLEXCOMM0 signal: TXD_SCL_MISO */
#define BOARD_DEBUG_UART_TX_PIN_NAME FC0_TXD_SCL_MISO        /*!< Pin name */
#define BOARD_DEBUG_UART_TX_LABEL "U6[4]/U22[3]/P0_1-ISP_TX" /*!< Label */
#define BOARD_DEBUG_UART_TX_NAME "DEBUG_UART_TX"             /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void USART0_InitPins(void); /* Function assigned for the Core #0 (ARM Cortex-M4) */

/* PIO0_0 (number 31), U18[4]/TO_MUX_P0_0-ISP_RX */
#define USART0_DEINITPINS_DEBUG_UART_RX_GPIO GPIO                         /*!< GPIO device name: GPIO */
#define USART0_DEINITPINS_DEBUG_UART_RX_PORT 0U                           /*!< PORT device index: 0 */
#define USART0_DEINITPINS_DEBUG_UART_RX_GPIO_PIN 0U                       /*!< PIO0 pin index: 0 */
#define USART0_DEINITPINS_DEBUG_UART_RX_PIN_NAME PIO0_0                   /*!< Pin name */
#define USART0_DEINITPINS_DEBUG_UART_RX_LABEL "U18[4]/TO_MUX_P0_0-ISP_RX" /*!< Label */
#define USART0_DEINITPINS_DEBUG_UART_RX_NAME "DEBUG_UART_RX"              /*!< Identifier name */

/* PIO0_1 (number 32), U6[4]/U22[3]/P0_1-ISP_TX */
#define USART0_DEINITPINS_DEBUG_UART_TX_GPIO GPIO                        /*!< GPIO device name: GPIO */
#define USART0_DEINITPINS_DEBUG_UART_TX_PORT 0U                          /*!< PORT device index: 0 */
#define USART0_DEINITPINS_DEBUG_UART_TX_GPIO_PIN 1U                      /*!< PIO0 pin index: 1 */
#define USART0_DEINITPINS_DEBUG_UART_TX_PIN_NAME PIO0_1                  /*!< Pin name */
#define USART0_DEINITPINS_DEBUG_UART_TX_LABEL "U6[4]/U22[3]/P0_1-ISP_TX" /*!< Label */
#define USART0_DEINITPINS_DEBUG_UART_TX_NAME "DEBUG_UART_TX"             /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void USART0_DeinitPins(void); /* Function assigned for the Core #0 (ARM Cortex-M4) */

/* FC4_CTS_SDA_SSEL0 (number 4), J1[3]/JS5[1]/U10[5]/P0_26-FC4_SDAX */
#define I2C4_INITPINS_FC4_SDAX_PERIPHERAL FLEXCOMM4                       /*!< Device name: FLEXCOMM4 */
#define I2C4_INITPINS_FC4_SDAX_SIGNAL CTS_SDA_SSEL0                       /*!< FLEXCOMM4 signal: CTS_SDA_SSEL0 */
#define I2C4_INITPINS_FC4_SDAX_PIN_NAME FC4_CTS_SDA_SSEL0                 /*!< Pin name */
#define I2C4_INITPINS_FC4_SDAX_LABEL "J1[3]/JS5[1]/U10[5]/P0_26-FC4_SDAX" /*!< Label */
#define I2C4_INITPINS_FC4_SDAX_NAME "FC4_SDAX"                            /*!< Identifier name */

/* FC4_RTS_SCL_SSEL1 (number 3), J1[1]/JS4[1]/U10[7]/P0_25-FC4_SCLX */
#define I2C4_INITPINS_FC4_SCLX_PERIPHERAL FLEXCOMM4                       /*!< Device name: FLEXCOMM4 */
#define I2C4_INITPINS_FC4_SCLX_SIGNAL RTS_SCL_SSEL1                       /*!< FLEXCOMM4 signal: RTS_SCL_SSEL1 */
#define I2C4_INITPINS_FC4_SCLX_PIN_NAME FC4_RTS_SCL_SSEL1                 /*!< Pin name */
#define I2C4_INITPINS_FC4_SCLX_LABEL "J1[1]/JS4[1]/U10[7]/P0_25-FC4_SCLX" /*!< Label */
#define I2C4_INITPINS_FC4_SCLX_NAME "FC4_SCLX"                            /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void I2C4_InitPins(void); /* Function assigned for the Core #0 (ARM Cortex-M4) */

/* PIO0_26 (number 4), J1[3]/JS5[1]/U10[5]/P0_26-FC4_SDAX */
#define I2C4_DEINITPINS_FC4_SDAX_GPIO GPIO                                  /*!< GPIO device name: GPIO */
#define I2C4_DEINITPINS_FC4_SDAX_PORT 0U                                    /*!< PORT device index: 0 */
#define I2C4_DEINITPINS_FC4_SDAX_GPIO_PIN 26U                               /*!< PIO0 pin index: 26 */
#define I2C4_DEINITPINS_FC4_SDAX_PIN_NAME PIO0_26                           /*!< Pin name */
#define I2C4_DEINITPINS_FC4_SDAX_LABEL "J1[3]/JS5[1]/U10[5]/P0_26-FC4_SDAX" /*!< Label */
#define I2C4_DEINITPINS_FC4_SDAX_NAME "FC4_SDAX"                            /*!< Identifier name */

/* PIO0_25 (number 3), J1[1]/JS4[1]/U10[7]/P0_25-FC4_SCLX */
#define I2C4_DEINITPINS_FC4_SCLX_GPIO GPIO                                  /*!< GPIO device name: GPIO */
#define I2C4_DEINITPINS_FC4_SCLX_PORT 0U                                    /*!< PORT device index: 0 */
#define I2C4_DEINITPINS_FC4_SCLX_GPIO_PIN 25U                               /*!< PIO0 pin index: 25 */
#define I2C4_DEINITPINS_FC4_SCLX_PIN_NAME PIO0_25                           /*!< Pin name */
#define I2C4_DEINITPINS_FC4_SCLX_LABEL "J1[1]/JS4[1]/U10[7]/P0_25-FC4_SCLX" /*!< Label */
#define I2C4_DEINITPINS_FC4_SCLX_NAME "FC4_SCLX"                            /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void I2C4_DeinitPins(void); /* Function assigned for the Core #0 (ARM Cortex-M4) */

/* FC5_TXD_SCL_MISO (number 58), J1[11]/U5[2]/P0_18-FC5_TXD_SCL_MISO */
#define I2C5_INITPINS_SPI_FLASH_MISO_PERIPHERAL FLEXCOMM5                        /*!< Device name: FLEXCOMM5 */
#define I2C5_INITPINS_SPI_FLASH_MISO_SIGNAL TXD_SCL_MISO                         /*!< FLEXCOMM5 signal: TXD_SCL_MISO */
#define I2C5_INITPINS_SPI_FLASH_MISO_PIN_NAME FC5_TXD_SCL_MISO                   /*!< Pin name */
#define I2C5_INITPINS_SPI_FLASH_MISO_LABEL "J1[11]/U5[2]/P0_18-FC5_TXD_SCL_MISO" /*!< Label */
#define I2C5_INITPINS_SPI_FLASH_MISO_NAME "SPI_FLASH_MISO"                       /*!< Identifier name */

/* FC5_RXD_SDA_MOSI (number 60), J1[13]/U5[5]/P0_20-FC5_RXD_SDA_MOSI */
#define I2C5_INITPINS_SPI_FLASH_MOSI_PERIPHERAL FLEXCOMM5                        /*!< Device name: FLEXCOMM5 */
#define I2C5_INITPINS_SPI_FLASH_MOSI_SIGNAL RXD_SDA_MOSI                         /*!< FLEXCOMM5 signal: RXD_SDA_MOSI */
#define I2C5_INITPINS_SPI_FLASH_MOSI_PIN_NAME FC5_RXD_SDA_MOSI                   /*!< Pin name */
#define I2C5_INITPINS_SPI_FLASH_MOSI_LABEL "J1[13]/U5[5]/P0_20-FC5_RXD_SDA_MOSI" /*!< Label */
#define I2C5_INITPINS_SPI_FLASH_MOSI_NAME "SPI_FLASH_MOSI"                       /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void I2C5_InitPins(void); /* Function assigned for the Core #0 (ARM Cortex-M4) */

/* PIO0_20 (number 60), J1[13]/U5[5]/P0_20-FC5_RXD_SDA_MOSI */
#define I2C5_DEINITPINS_SPI_FLASH_MOSI_GPIO GPIO                                   /*!< GPIO device name: GPIO */
#define I2C5_DEINITPINS_SPI_FLASH_MOSI_PORT 0U                                     /*!< PORT device index: 0 */
#define I2C5_DEINITPINS_SPI_FLASH_MOSI_GPIO_PIN 20U                                /*!< PIO0 pin index: 20 */
#define I2C5_DEINITPINS_SPI_FLASH_MOSI_PIN_NAME PIO0_20                            /*!< Pin name */
#define I2C5_DEINITPINS_SPI_FLASH_MOSI_LABEL "J1[13]/U5[5]/P0_20-FC5_RXD_SDA_MOSI" /*!< Label */
#define I2C5_DEINITPINS_SPI_FLASH_MOSI_NAME "SPI_FLASH_MOSI"                       /*!< Identifier name */

/* PIO0_18 (number 58), J1[11]/U5[2]/P0_18-FC5_TXD_SCL_MISO */
#define I2C5_DEINITPINS_SPI_FLASH_MISO_GPIO GPIO                                   /*!< GPIO device name: GPIO */
#define I2C5_DEINITPINS_SPI_FLASH_MISO_PORT 0U                                     /*!< PORT device index: 0 */
#define I2C5_DEINITPINS_SPI_FLASH_MISO_GPIO_PIN 18U                                /*!< PIO0 pin index: 18 */
#define I2C5_DEINITPINS_SPI_FLASH_MISO_PIN_NAME PIO0_18                            /*!< Pin name */
#define I2C5_DEINITPINS_SPI_FLASH_MISO_LABEL "J1[11]/U5[2]/P0_18-FC5_TXD_SCL_MISO" /*!< Label */
#define I2C5_DEINITPINS_SPI_FLASH_MISO_NAME "SPI_FLASH_MISO"                       /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void I2C5_DeinitPins(void); /* Function assigned for the Core #0 (ARM Cortex-M4) */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void SPI3_InitPins(void); /* Function assigned for the Core #0 (ARM Cortex-M4) */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void SPI3_DeinitPins(void); /* Function assigned for the Core #0 (ARM Cortex-M4) */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void SPI5_InitPins(void); /* Function assigned for the Core #0 (ARM Cortex-M4) */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void SPI5_DeinitPins(void); /* Function assigned for the Core #0 (ARM Cortex-M4) */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
