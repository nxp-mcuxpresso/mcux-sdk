/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*! \file frdm_k22f.h
    \brief The \b frdm_k22f.h file defines GPIO pins for FRDM-K22F board
*/

#ifndef FRDM_K22F_H_
#define FRDM_K22F_H_

#include "pin_mux.h"
#include "fsl_smc.h"
#include "MK22F51212.h"
#include "RTE_Device.h"
#include "gpio_driver.h"

// I2C0 Handle
extern gpioHandleKSDK_t A5;
extern gpioHandleKSDK_t A4;

// SPI1 Handle
extern gpioHandleKSDK_t D13;
extern gpioHandleKSDK_t D11;
extern gpioHandleKSDK_t D12;

// UART1 Handle
extern gpioHandleKSDK_t D14;
extern gpioHandleKSDK_t D15;

// FRDM-K22F Arduino Connector Pin Defintion
extern gpioHandleKSDK_t A0;
extern gpioHandleKSDK_t A1;
extern gpioHandleKSDK_t A2;
extern gpioHandleKSDK_t A3;
extern gpioHandleKSDK_t D0;
extern gpioHandleKSDK_t D1;
extern gpioHandleKSDK_t D2;
extern gpioHandleKSDK_t D3;
extern gpioHandleKSDK_t D4;
extern gpioHandleKSDK_t D5;
extern gpioHandleKSDK_t D6;
extern gpioHandleKSDK_t D7;
extern gpioHandleKSDK_t D8;
extern gpioHandleKSDK_t D9;
extern gpioHandleKSDK_t D10;

// FRDM-K22F RGB LED Pin Definitions
extern gpioHandleKSDK_t RED_LED;
extern gpioHandleKSDK_t GREEN_LED;
extern gpioHandleKSDK_t BLUE_LED;
extern gpioHandleKSDK_t INT1;
extern gpioHandleKSDK_t INT2;

// I2C_S1: Pin mapping and driver information for default I2C brought to shield
#define I2C_S1_SCL_PIN A5
#define I2C_S1_SDA_PIN A4
#define I2C_S1_DRIVER Driver_I2C0
#define I2C_S1_DEVICE_INDEX I2C0_INDEX
#define I2C_S1_SIGNAL_EVENT I2C0_SignalEvent_t

// I2C_S2: Pin mapping and driver information for alternate I2C bus on shield
// Note :  I2C1 cannot be used with UART1 (which is the TGT_MCU Debug UART).
#define I2C_S2_SCL_PIN D15
#define I2C_S2_SDA_PIN D14
#define I2C_S2_DRIVER Driver_I2C1
#define I2C_S2_DEVICE_INDEX I2C1_INDEX
#define I2C_S2_SIGNAL_EVENT I2C1_SignalEvent_t

// I2C_BB: PPin mapping and driver information for I2C routed on K22F base board
#define I2C_BB_SCL_PIN A5
#define I2C_BB_SDA_PIN A4
#define I2C_BB_DRIVER Driver_I2C0
#define I2C_BB_DEVICE_INDEX I2C0_INDEX
#define I2C_BB_SIGNAL_EVENT I2C0_SignalEvent_t

// SPIS: Pin mapping and driver information default SPI brought to shield
#define SPI_S_SCLK D13
#define SPI_S_MOSI D11
#define SPI_S_MISO D12
#define SPI_S_DRIVER Driver_SPI1
#define SPI_S_BAUDRATE 500000U ///< Transfer baudrate - 500k
#define SPI_S_DEVICE_INDEX SPI1_INDEX
#define SPI_S_SIGNAL_EVENT SPI1_SignalEvent_t

// UART: Driver information for default UART to communicate with HOST PC.
#define HOST_S_DRIVER Driver_USART1
#define HOST_S_SIGNAL_EVENT HOST_SignalEvent_t

// Bluetooth: Driver information for default UART to communicate with HOST PC.
#define HOST_B_DRIVER Driver_USART2
#define HOST_B_SIGNAL_EVENT HOST_SignalEvent_t

// On-Board FXOS8700 Sensor Information
#define FXOS8700_BB_I2C_ADDR 0x1C
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

/// @name Wired UART Parameters
/// Sensor Fusion aliases are defined in terms of specific hardware features
/// defined in MK22F51212.h.
///@{
#define WIRED_UART UART1                             ///< KSDK instance name for the debug UART
#define WIRED_UART_PORT_CLKEN kCLOCK_PortE           ///< KDSK handle for the pin port clock enable
#define WIRED_UART_PORT PORTE                        ///< KDSK handle for the pin port associated with this UART
#define WIRED_UART_RX_PIN 1U                         ///< The port number associated with RX
#define WIRED_UART_TX_PIN 0U                         ///< The port number associated with TX
#define WIRED_UART_MUX kPORT_MuxAlt3                 ///< KDSK pin mux selector
#ifndef USE_ORIENT_APP_CONTROL                       ///< If Using Orient App then use Host I/O
#define WIRED_UART_IRQHandler UART1_RX_TX_IRQHandler ///< KDSK-specified IRQ handler name
#endif
#define WIRED_UART_IRQn UART1_RX_TX_IRQn ///< The interrupt number associated with this IRQ
#define WIRED_UART_CLKSRC UART1_CLK_SRC  ///< KSDK instance name for the clock feeding this module
#define WIRED_UART_IRQn UART1_RX_TX_IRQn ///< KSDK interrupt vector number
///@}

/// @name Wireless UART Parameters
/// Sensor Fusion aliases are defined in terms of specific hardware features
/// defined in MK22F51212.h.
///@{
#define WIRELESS_UART UART2                             ///< KSDK instance name for the debug UART
#define WIRELESS_UART_PORT_CLKEN kCLOCK_PortD           ///< KDSK handle for the pin port clock enable
#define WIRELESS_UART_PORT PORTD                        ///< KDSK handle for the pin port associated with this UART
#define WIRELESS_UART_RX_PIN 2U                         ///< The port number associated with RX
#define WIRELESS_UART_TX_PIN 3U                         ///< The port number associated with TX
#define WIRELESS_UART_MUX kPORT_MuxAlt3                 ///< KDSK pin mux selector
#define WIRELESS_UART_IRQHandler UART2_RX_TX_IRQHandler ///< KDSK-specified IRQ handler name
#define WIRELESS_UART_IRQn UART2_RX_TX_IRQn             ///< The interrupt number associated with this IRQ
#define WIRELESS_UART_CLKSRC UART2_CLK_SRC              ///< KSDK instance name for the clock feeding this module
#define WIRELESS_UART_IRQn UART2_RX_TX_IRQn             ///< KSDK interrupt vector number
///@}

///@name Miscellaneous Hardware Configuration Parameters
///@{
#define THIS_BOARD 9                    ///< FRDM_K22F
#define CORE_SYSTICK_HZ 80000000        ///< core and systick clock rate (Hz)
#define CALIBRATION_NVM_ADDR 0x0007F800 ///< start of final 2K (sector size) of 512K flash
#define ADS_NVM_ADDR 0x0007F000         ///< start of the next to last 2K (sector size) of the 512K flash
#define FLASH_SECTOR_SIZE_PROPERTY kFLASH_PropertyPflashSectorSize
#define FLASH_ERASE_KEY kFLASH_ApiEraseKey

// offsets from start of NVM block for calibration coefficients
#define MAG_NVM_OFFSET 0     // 68 bytes used
#define GYRO_NVM_OFFSET 100  // 16 bytes used
#define ACCEL_NVM_OFFSET 140 // 88 bytes used
///@}

#endif /* FRDM_K22F_H_ */
