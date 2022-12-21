/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file frdm_k32w042.h
 * @brief The frdm_k32w042.h file defines GPIO pin mappings for FRDM-K64F board
*/

#ifndef FRDM_K32W042_H_
#define FRDM_K32W042_H_

#include "pin_mux.h"
#include "fsl_msmc.h"
#include "RTE_Device.h"
#include "gpio_driver.h"
#include "K32W042S1M2_cm4.h"

// I2C0 Pin Handles
extern gpioHandleKSDK_t D15;
extern gpioHandleKSDK_t D14;

// I2C3 Handle
extern gpioHandleKSDK_t A5;
extern gpioHandleKSDK_t A4;

// SPI0 Handle
extern gpioHandleKSDK_t D13;
extern gpioHandleKSDK_t D11;
extern gpioHandleKSDK_t D12;

// UART1 Handle
extern gpioHandleKSDK_t D0;
extern gpioHandleKSDK_t D1;

// K3S Arduino Connector Pin Defintion
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

// K3S Internal Peripheral Pin Definitions
extern gpioHandleKSDK_t RED_LED;
extern gpioHandleKSDK_t GREEN_LED;
extern gpioHandleKSDK_t BLUE_LED;
extern gpioHandleKSDK_t INT1;
extern gpioHandleKSDK_t INT2;

// I2C_S1: Pin mapping and driver information for default I2C brought to shield
#define I2C_S1_SCL_PIN D15
#define I2C_S1_SDA_PIN D14
#define I2C_S1_DRIVER Driver_I2C0
#define I2C_S1_DEVICE_INDEX I2C0_INDEX
#define I2C_S1_SIGNAL_EVENT I2C0_SignalEvent_t

// I2C_S2: Pin mapping and driver information for other I2C brought to shield
#define I2C_S2_SCL_PIN A5
#define I2C_S2_SDA_PIN A4
#define I2C_S2_DRIVER Driver_I2C3
#define I2C_S2_DEVICE_INDEX I2C3_INDEX
#define I2C_S2_SIGNAL_EVENT I2C3_SignalEvent_t

// I2C_B: Pin mapping and driver information for I2C routed on base board
#define I2C_BB_SCL_PIN A5
#define I2C_BB_SDA_PIN A4
#define I2C_BB_DRIVER Driver_I2C3
#define I2C_BB_DEVICE_INDEX I2C3_INDEX
#define I2C_BB_SIGNAL_EVENT I2C3_SignalEvent_t

// SPIS: Pin mapping and driver information default SPI brought to shield
#define SPI_S_SCLK D13
#define SPI_S_MISO D12
#define SPI_S_MOSI D11
#define SPI_S_DRIVER Driver_SPI0
#define SPI_S_BAUDRATE 500000U ///< Transfer baudrate - 500k
#define SPI_S_DEVICE_INDEX SPI0_INDEX
#define SPI_S_SIGNAL_EVENT SPI0_SignalEvent_t

// UART: Driver information for default UART to communicate with HOST PC.
#define HOST_S_DRIVER Driver_USART0
#define HOST_S_SIGNAL_EVENT HOST_SignalEvent_t

// Bluetooth: Driver information for default UART to communicate with HOST PC.
#define HOST_B_DRIVER Driver_USART1
#define HOST_B_SIGNAL_EVENT HOST_SignalEvent_t

// On-Board FXOS8700 Sensor Information
#define FXOS8700_BB_I2C_ADDR 0x1E
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

// Miscellaneous Hardware Configuration Parameters
#define ADS_NVM_ADDR 0x000BF000 ///< start of the next to last 4K (sector size) of the 768K flash
#define FLASH_SECTOR_SIZE_PROPERTY kFLASH_PropertyPflashSectorSize

/* Compatability definitions for K32W042 */
#define SMC SMC0
#define I2C0 LPI2C0
#define I2C3 LPI2C3
#define I2C_Type LPI2C_Type
#define I2C_BASE_PTRS LPI2C_BASE_PTRS
#define SPI0 LPSPI0
#define SPI_Type LPSPI_Type
#define SPI_BASE_PTRS LPSPI_BASE_PTRS

#endif /* FRDM_K32W042_H_ */
