/*
 * Copyright 2019 - 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**
 * @file lpc55s16.h
 * @brief The lpc55s16.h file defines GPIO pin mappings for LPCXpresso55S16 board
*/

#ifndef LPC55S16_H_
#define LPC55S16_H_

#include "pin_mux.h"
#include "fsl_power.h"
#include "RTE_Device.h"
#include "gpio_driver.h"
#include "clock_config.h"

#define PORT0 0
#define PORT1 1

// I2C4 Pin Handles
extern gpioHandleKSDK_t D14;
extern gpioHandleKSDK_t D15;

// SPI7 Handles
extern gpioHandleKSDK_t D11;
extern gpioHandleKSDK_t D12;
extern gpioHandleKSDK_t D13;
extern gpioHandleKSDK_t D10;

// UART0 Handle
extern gpioHandleKSDK_t D0;
extern gpioHandleKSDK_t D1;

extern gpioHandleKSDK_t D2;

// LPCXpresso54114 Internal Peripheral Pin Definitions
extern gpioHandleKSDK_t RED_LED;
extern gpioHandleKSDK_t GREEN_LED;
extern gpioHandleKSDK_t BLUE_LED;

// I2C_S1: Pin mapping and driver information for default I2C brought to shield
#define I2C_S1_SCL_PIN      D15
#define I2C_S1_SDA_PIN      D14
#define I2C_S1_DRIVER       Driver_I2C4
#define I2C_S1_DEVICE_INDEX I2C4_INDEX
#define I2C_S1_SIGNAL_EVENT I2C4_SignalEvent_t

// SPI_S: Pin mapping and driver information default SPI brought to shield
#define SPI_S_DRIVER       Driver_SPI8
#define SPI_S_BAUDRATE     500000U ///< Transfer baudrate - 500k
#define SPI_S_DEVICE_INDEX SPI8_INDEX
#define SPI_S_SIGNAL_EVENT SPI8_SignalEvent_t

// UART: Driver information for default UART to communicate with HOST PC.
#define HOST_S_DRIVER       Driver_USART0
#define HOST_S_SIGNAL_EVENT HOST_SignalEvent_t
#define HOST_B_DRIVER       Driver_USART1
#define HOST_B_SIGNAL_EVENT HOST_SignalEvent_t

/* @brief  Ask use input to resume after specified samples have been processed. */
#define ASK_USER_TO_RESUME(x)                                                          \
    static bool askResume            = true;                                           \
    static uint16_t samplesToProcess = x - 1;                                          \
    if (askResume && !samplesToProcess--)                                              \
    {                                                                                  \
        PRINTF("\r\n Specified samples processed, press any key to continue... \r\n"); \
        GETCHAR();                                                                     \
        askResume = false;                                                             \
    }

/* @brief dummy arguement to Power Mode Wait Wrapper. */
#define SMC NULL

/* @brief Kinetis style Wrapper API for Power Mode Wait (Wait for Interrupt). */
status_t SMC_SetPowerModeWait(void *arg);
/* @brief Kinetis style Wrapper API for Power Mode VLPR (Wait for Interrupt). */
status_t SMC_SetPowerModeVlpr(void *arg);
/* @brief Kinetis style Wrapper API for handling all Clock related configurations. */
void BOARD_BootClockRUN(void);
#endif /* LPC55S69_CM4_H_ */
