/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file lpc54114.h
 * @brief The lpc54114.h file defines GPIO pin mappings for LPCXpresso54114 board
*/

#ifndef LPC54114_H_
#define LPC54114_H_

#include "pin_mux.h"
#include "fsl_power.h"
#include "RTE_Device.h"
#include "gpio_driver.h"

// I2C4 Pin Handles
extern gpioHandleKSDK_t D14;
extern gpioHandleKSDK_t D15;

// I2C5/SPI5 Handles
extern gpioHandleKSDK_t D11;
extern gpioHandleKSDK_t D12;
extern gpioHandleKSDK_t D13;

// UART0 Handle
extern gpioHandleKSDK_t D0;
extern gpioHandleKSDK_t D1;

// LPCXpresso54114 Arduino Connector Pin Defintion
extern gpioHandleKSDK_t A0;
extern gpioHandleKSDK_t A1;
extern gpioHandleKSDK_t A2;
extern gpioHandleKSDK_t A3;
extern gpioHandleKSDK_t A4;
extern gpioHandleKSDK_t A5;
extern gpioHandleKSDK_t D2;
extern gpioHandleKSDK_t D3;
extern gpioHandleKSDK_t D4;
extern gpioHandleKSDK_t D5;
extern gpioHandleKSDK_t D6;
extern gpioHandleKSDK_t D7;
extern gpioHandleKSDK_t D8;
extern gpioHandleKSDK_t D9;
extern gpioHandleKSDK_t D10;

// LPCXpresso54114 Internal Peripheral Pin Definitions
extern gpioHandleKSDK_t RED_LED;
extern gpioHandleKSDK_t GREEN_LED;
extern gpioHandleKSDK_t BLUE_LED;

// I2C_S1: Pin mapping and driver information for default I2C brought to shield
#define I2C_S1_SCL_PIN D15
#define I2C_S1_SDA_PIN D14
#define I2C_S1_DRIVER Driver_I2C4
#define I2C_S1_DEVICE_INDEX I2C4_INDEX
#define I2C_S1_SIGNAL_EVENT I2C4_SignalEvent_t

// I2C_S2: Pin mapping and driver information for alternate I2C bus on shield
#define I2C_S2_DRIVER Driver_I2C5
#define I2C_S2_DEVICE_INDEX I2C5_INDEX
#define I2C_S2_SIGNAL_EVENT I2C5_SignalEvent_t

// SPIS: Pin mapping and driver information default SPI brought to shield
#define SPI_S_DRIVER Driver_SPI5
#define SPI_S_BAUDRATE 500000U ///< Transfer baudrate - 500k
#define SPI_S_DEVICE_INDEX SPI5_INDEX
#define SPI_S_SIGNAL_EVENT SPI5_SignalEvent_t

// UART: Driver information for default UART to communicate with HOST PC.
#define HOST_S_DRIVER Driver_USART0
#define HOST_S_SIGNAL_EVENT HOST_SignalEvent_t
#define HOST_B_DRIVER Driver_USART1
#define HOST_B_SIGNAL_EVENT HOST_SignalEvent_t

#define WIRED_USART USART0
#define WIRED_USART_CLK_SRC kCLOCK_Flexcomm0
#define WIRED_USART_CLK_FREQ CLOCK_GetFreq(kCLOCK_Flexcomm0)
#define WIRED_USART_IRQHandler FLEXCOMM0_IRQHandler
#define WIRED_USART_IRQn FLEXCOMM0_IRQn

#define WIRELESS_USART USART1

// ADS_FLASH: The next to last sector of flash.
#define ADS_NVM_ADDR (FSL_FEATURE_SYSCON_FLASH_SIZE_BYTES - (2 * FSL_FEATURE_SYSCON_FLASH_SECTOR_SIZE_BYTES))

/* @brief  Ask use input to resume after specified samples have been processed. */
#define ASK_USER_TO_RESUME(x)                                                          \
    static bool askResume = true;                                                      \
    static uint16_t samplesToProcess = x - 1;                                          \
    if (askResume && !samplesToProcess--)                                              \
    {                                                                                  \
        PRINTF("\r\n Specified samples processed, press any key to continue... \r\n"); \
        GETCHAR();                                                                     \
        askResume = false;                                                             \
    }

/* @brief  Override Kinetis style Wrapper for handling all Clock related configurations. */
#ifdef BOARD_BootClockRUN
#undef BOARD_BootClockRUN
#define BOARD_BootClockRUN()                             \
    /* attach 12 MHz clock to FLEXCOMM0 (debug/UART0) */ \
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM0);               \
    /* attach 12 MHz clock to FLEXCOMM4 (I2C4) */        \
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM4);               \
    /* attach 12 MHz clock to FLEXCOMM4 (SPI5) */        \
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM5);               \
    /* Configure FROHF48M Clock */                       \
    BOARD_BootClockFROHF48M()
#endif

/* @brief dummy arguement to Power Mode Wait Wrapper. */
#define SMC NULL

/* @brief Kinetis style Wrapper API for Power Mode Wait (Wait for Interrupt). */
status_t SMC_SetPowerModeWait(void *);

/* @brief Kinetis style Wrapper API for Power Mode Wait (Vlpr for Interrupt). */
status_t SMC_SetPowerModeVlpr(void *);

///@name Miscellaneous Hardware Configuration Parameters
///@{
#define THIS_BOARD 16                   ///< LPC54114
#define CORE_SYSTICK_HZ 48000000        ///< core and systick clock rate (Hz)
#define CALIBRATION_NVM_ADDR 0x0003FF00 ///< start of final 256 bytes of 256K flash memory (LPC54114)
#define NVM_SECTOR_NUMBER 7             ///< Sector number in flash where we will store parameters
#define NVM_PAGE_NUMBER 1023            ///< Page number in flash where we will store parameters

// offsets from start of NVM block for calibration coefficients
#define MAG_NVM_OFFSET 0     // 68 bytes used
#define GYRO_NVM_OFFSET 100  // 16 bytes used
#define ACCEL_NVM_OFFSET 140 // 88 bytes used
///@}

#endif /* LPC54114_CM4_H_ */
