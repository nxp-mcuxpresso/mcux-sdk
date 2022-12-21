/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file frdm_k64f.h
 * @brief The frdm_k64f.h file defines GPIO pin mappings for FRDM-K64F board
*/

#ifndef FRDM_K64F_H_
#define FRDM_K64F_H_

#include "pin_mux.h"
#include "fsl_smc.h"
#include "MK64F12.h"
#include "RTE_Device.h"
#include "gpio_driver.h"

// I2C0 Pin Handles
extern gpioHandleKSDK_t D15;
extern gpioHandleKSDK_t D14;

// I2C1 Handle
extern gpioHandleKSDK_t A5;
extern gpioHandleKSDK_t A4;

// SPI0 Handle
extern gpioHandleKSDK_t D13;
extern gpioHandleKSDK_t D11;
extern gpioHandleKSDK_t D12;

// UART3 Handle
extern gpioHandleKSDK_t D0;
extern gpioHandleKSDK_t D1;

// FRDM-K64F Arduino Connector Pin Defintion
extern gpioHandleKSDK_t A0;
extern gpioHandleKSDK_t A1;
extern gpioHandleKSDK_t A2;
extern gpioHandleKSDK_t A3;
extern gpioHandleKSDK_t D2;
extern gpioHandleKSDK_t D3;
extern gpioHandleKSDK_t D4;
extern gpioHandleKSDK_t D5;
extern gpioHandleKSDK_t D6;
extern gpioHandleKSDK_t D6;
extern gpioHandleKSDK_t D8;
extern gpioHandleKSDK_t D9;
extern gpioHandleKSDK_t D10;

// FRDM-K64F Internal Peripheral Pin Definitions
extern gpioHandleKSDK_t RED_LED;
extern gpioHandleKSDK_t GREEN_LED;
extern gpioHandleKSDK_t BLUE_LED;
extern gpioHandleKSDK_t INT1;
extern gpioHandleKSDK_t INT2;

// I2C_S1: Pin mapping and driver information for default I2C brought to shield
#define I2C_S1_SCL_PIN A5
#define I2C_S1_SDA_PIN A4
#define I2C_S1_DRIVER Driver_I2C1
#define I2C_S1_DEVICE_INDEX I2C1_INDEX
#define I2C_S1_SIGNAL_EVENT I2C1_SignalEvent_t

// I2C_S2: Pin mapping and driver information for alternate I2C bus on shield
#define I2C_S2_SCL_PIN D15
#define I2C_S2_SDA_PIN D14
#define I2C_S2_DRIVER Driver_I2C0
#define I2C_S2_DEVICE_INDEX I2C0_INDEX
#define I2C_S2_SIGNAL_EVENT I2C0_SignalEvent_t

// I2C_B: Pin mapping and driver information for I2C routed on K64F base board
#define I2C_BB_SCL_PIN D15
#define I2C_BB_SDA_PIN D14
#define I2C_BB_DRIVER Driver_I2C0
#define I2C_BB_DEVICE_INDEX I2C0_INDEX
#define I2C_BB_SIGNAL_EVENT I2C0_SignalEvent_t

// SPIS: Pin mapping and driver information default SPI brought to shield
#define SPI_S_SCLK D13
#define SPI_S_MOSI D11
#define SPI_S_MISO D12
#define SPI_S_DRIVER Driver_SPI0
#define SPI_S_BAUDRATE 500000U ///< Transfer baudrate - 500k
#define SPI_S_DEVICE_INDEX SPI0_INDEX
#define SPI_S_SIGNAL_EVENT SPI0_SignalEvent_t

// UART: Driver information for default UART to communicate with HOST PC.
#define HOST_S_DRIVER Driver_USART0
#define HOST_S_SIGNAL_EVENT HOST_SignalEvent_t

// Bluetooth: Driver information for default UART to communicate with HOST PC.
#define HOST_B_DRIVER Driver_USART3
#define HOST_B_SIGNAL_EVENT HOST_SignalEvent_t

// On-Board FXOS8700 Sensor Information
#define FXOS8700_BB_I2C_ADDR 0x1D
#define FXOS8700_BB_INT1 INT1
#define FXOS8700_BB_INT2 INT2

/* @brief  Ask use input to resume after specified samples have been processed. */
#define ASK_USER_TO_RESUME(x)                                                          \
    static volatile bool askResume = true;                                             \
    static uint16_t samplesToProcess = x - 1;                                          \
    if (askResume && !samplesToProcess--)                                              \
    {                                                                                  \
        PRINTF("\r\n Specified samples processed, press any key to continue... \r\n"); \
        GETCHAR();                                                                     \
        askResume = false;                                                             \
    }

// Sensor Fusion Required Definitions
///@{
// Wired UART Parameters
#define WIRED_UART UART0                             ///< KSDK instance name for the debug UART
#define WIRED_UART_PORT_CLKEN kCLOCK_PortB           ///< KDSK handle for the pin port clock enable
#define WIRED_UART_PORT PORTB                        ///< KDSK handle for the pin port associated with this UART
#define WIRED_UART_RX_PIN 16U                        ///< The port number associated with RX
#define WIRED_UART_TX_PIN 17U                        ///< The port number associated with TX
#define WIRED_UART_MUX kPORT_MuxAlt3                 ///< KDSK pin mux selector
#ifndef USE_ORIENT_APP_CONTROL                       ///< If Using Orient App then use Host I/O
#define WIRED_UART_IRQHandler UART0_RX_TX_IRQHandler ///< KDSK-specified IRQ handler name
#endif
#define WIRED_UART_IRQn UART0_RX_TX_IRQn ///< The interrupt number associated with this IRQ
#define WIRED_UART_CLKSRC UART0_CLK_SRC  ///< KSDK instance name for the clock feeding this module
#define WIRED_UART_IRQn UART0_RX_TX_IRQn ///< KSDK interrupt vector number

// Wireless UART Parameters
#define WIRELESS_UART UART3                             ///< KSDK instance name for the debug UART
#define WIRELESS_UART_PORT_CLKEN kCLOCK_PortC           ///< KDSK handle for the pin port clock enable
#define WIRELESS_UART_PORT PORTC                        ///< KDSK handle for the pin port associated with this UART
#define WIRELESS_UART_RX_PIN 16U                        ///< The port number associated with RX
#define WIRELESS_UART_TX_PIN 17U                        ///< The port number associated with TX
#define WIRELESS_UART_MUX kPORT_MuxAlt3                 ///< KDSK pin mux selector
#define WIRELESS_UART_IRQHandler UART3_RX_TX_IRQHandler ///< KDSK-specified IRQ handler name
#define WIRELESS_UART_IRQn UART3_RX_TX_IRQn             ///< The interrupt number associated with this IRQ
#define WIRELESS_UART_CLKSRC UART3_CLK_SRC              ///< KSDK instance name for the clock feeding this module
#define WIRELESS_UART_IRQn UART3_RX_TX_IRQn             ///< KSDK interrupt vector number

// Miscellaneous Hardware Configuration Parameters
#define THIS_BOARD 5                    ///< FRDM_K64F
#define CORE_SYSTICK_HZ 120000000       ///< core and systick clock rate (Hz)
#define CALIBRATION_NVM_ADDR 0x000FF000 ///< start of final 4K (sector size) of 1M flash
#define ADS_NVM_ADDR 0x000FE000         ///< start of the next to last 4K (sector size) of the 1M flash
#define FLASH_SECTOR_SIZE_PROPERTY kFLASH_PropertyPflashSectorSize
#define FLASH_ERASE_KEY kFLASH_ApiEraseKey

// offsets from start of NVM block for calibration coefficients
#define MAG_NVM_OFFSET 0     // 68 bytes used
#define GYRO_NVM_OFFSET 100  // 16 bytes used
#define ACCEL_NVM_OFFSET 140 // 88 bytes used
///@}

#endif /* FRDM_K64F_H_ */
