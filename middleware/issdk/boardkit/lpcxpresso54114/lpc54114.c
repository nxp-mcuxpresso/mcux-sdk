/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file lpc54114.c
 * @brief The lpc54114.c file defines GPIO pins and I2C CMSIS utilities for LPCXpresso54114 board.
 */

#include "lpc54114.h"

// I2C4 Pin Handles
gpioHandleKSDK_t D14 = {.base = GPIO,
                        .pinNumber = 26,
                        .mask = 1 << (26),
                        .clockName = kCLOCK_Gpio0,
                        .portNumber = kGINT_Port0};
gpioHandleKSDK_t D15 = {.base = GPIO,
                        .pinNumber = 25,
                        .mask = 1 << (25),
                        .clockName = kCLOCK_Gpio0,
                        .portNumber = kGINT_Port0};

// I2C5/SPI5 Handle
gpioHandleKSDK_t D11 = {.base = GPIO,
                        .pinNumber = 20,
                        .mask = 1 << (20),
                        .clockName = kCLOCK_Gpio0,
                        .portNumber = kGINT_Port0};
gpioHandleKSDK_t D12 = {.base = GPIO,
                        .pinNumber = 18,
                        .mask = 1 << (18),
                        .clockName = kCLOCK_Gpio0,
                        .portNumber = kGINT_Port0};
gpioHandleKSDK_t D13 = {.base = GPIO,
                        .pinNumber = 19,
                        .mask = 1 << (19),
                        .clockName = kCLOCK_Gpio0,
                        .portNumber = kGINT_Port0};

// UART0 Handle
gpioHandleKSDK_t D0 = {.base = GPIO,
                       .pinNumber = 8,
                       .mask = 1 << (8),
                       .clockName = kCLOCK_Gpio0,
                       .portNumber = kGINT_Port0};
gpioHandleKSDK_t D1 = {.base = GPIO,
                       .pinNumber = 9,
                       .mask = 1 << (9),
                       .clockName = kCLOCK_Gpio0,
                       .portNumber = kGINT_Port0};

// FRDM-K64F Arduino Connector Pin Defintion
gpioHandleKSDK_t A0 = {.base = GPIO,
                       .pinNumber = 30,
                       .mask = 1 << (30),
                       .clockName = kCLOCK_Gpio0,
                       .portNumber = kGINT_Port0};
gpioHandleKSDK_t A1; // No Connection
gpioHandleKSDK_t A2 = {.base = GPIO,
                       .pinNumber = 8,
                       .mask = 1 << (8),
                       .clockName = kCLOCK_Gpio1,
                       .portNumber = kGINT_Port1};
gpioHandleKSDK_t A3 = {.base = GPIO,
                       .pinNumber = 10,
                       .mask = 1 << (10),
                       .clockName = kCLOCK_Gpio1,
                       .portNumber = kGINT_Port1};
gpioHandleKSDK_t A4 = {.base = GPIO,
                       .pinNumber = 4,
                       .mask = 1 << (4),
                       .clockName = kCLOCK_Gpio1,
                       .portNumber = kGINT_Port1};
gpioHandleKSDK_t A5 = {.base = GPIO,
                       .pinNumber = 5,
                       .mask = 1 << (5),
                       .clockName = kCLOCK_Gpio1,
                       .portNumber = kGINT_Port1};

gpioHandleKSDK_t D2 = {.base = GPIO,
                       .pinNumber = 10,
                       .mask = 1 << (10),
                       .clockName = kCLOCK_Gpio0,
                       .portNumber = kGINT_Port0};
gpioHandleKSDK_t D3 = {.base = GPIO,
                       .pinNumber = 12,
                       .mask = 1 << (12),
                       .clockName = kCLOCK_Gpio1,
                       .portNumber = kGINT_Port1};
gpioHandleKSDK_t D4 = {.base = GPIO,
                       .pinNumber = 13,
                       .mask = 1 << (13),
                       .clockName = kCLOCK_Gpio1,
                       .portNumber = kGINT_Port1};
gpioHandleKSDK_t D5 = {.base = GPIO,
                       .pinNumber = 29,
                       .mask = 1 << (29),
                       .clockName = kCLOCK_Gpio0,
                       .portNumber = kGINT_Port0};
gpioHandleKSDK_t D6 = {.base = GPIO,
                       .pinNumber = 0,
                       .mask = 1 << (0),
                       .clockName = kCLOCK_Gpio1,
                       .portNumber = kGINT_Port1};
gpioHandleKSDK_t D7 = {.base = GPIO,
                       .pinNumber = 14,
                       .mask = 1 << (14),
                       .clockName = kCLOCK_Gpio1,
                       .portNumber = kGINT_Port1};
gpioHandleKSDK_t D8 = {.base = GPIO,
                       .pinNumber = 16,
                       .mask = 1 << (16),
                       .clockName = kCLOCK_Gpio1,
                       .portNumber = kGINT_Port1};
gpioHandleKSDK_t D9 = {.base = GPIO,
                       .pinNumber = 15,
                       .mask = 1 << (15),
                       .clockName = kCLOCK_Gpio1,
                       .portNumber = kGINT_Port1};
gpioHandleKSDK_t D10 = {.base = GPIO,
                        .pinNumber = 1,
                        .mask = 1 << (1),
                        .clockName = kCLOCK_Gpio1,
                        .portNumber = kGINT_Port1};

// FRDM-K64F Internal Peripheral Pin Definitions
gpioHandleKSDK_t RED_LED = {.base = GPIO,
                            .pinNumber = 29,
                            .mask = 1 << (29),
                            .clockName = kCLOCK_Gpio0,
                            .portNumber = kGINT_Port0};
gpioHandleKSDK_t GREEN_LED = {.base = GPIO,
                              .pinNumber = 10,
                              .mask = 1 << (10),
                              .clockName = kCLOCK_Gpio1,
                              .portNumber = kGINT_Port1};
gpioHandleKSDK_t BLUE_LED = {.base = GPIO,
                             .pinNumber = 9,
                             .mask = 1 << (9),
                             .clockName = kCLOCK_Gpio1,
                             .portNumber = kGINT_Port1};

/*!
 * @brief Configures the system to WAIT power mode.
 *        API name used from Kinetis family to maintain compatibility.
 *
 * @param Power peripheral base address (dummy).
 * @return Configuration error code.
 */
status_t SMC_SetPowerModeWait(void *arg)
{
    POWER_EnterSleep();

    return kStatus_Success;
}

/*!
 * @brief Configures the system to VLPR power mode.
 *        API name used from Kinetis family to maintain compatibility.
 *
 * @param Power peripheral base address (dummy).
 * @return Configuration error code.
 */
status_t SMC_SetPowerModeVlpr(void *arg)
{
    POWER_EnterSleep();

    return kStatus_Success;
}

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by fsl_uart_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t USART0_GetFreq(void)
{
    return CLOCK_GetFreq(kCLOCK_Flexcomm0);
}

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by fsl_i2c_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t I2C4_GetFreq(void)
{
    return CLOCK_GetFreq(kCLOCK_Fro12M);
}

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by fsl_i2c_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t I2C5_GetFreq(void)
{
    return CLOCK_GetFreq(kCLOCK_Fro12M);
}

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by fsl_spi_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t SPI3_GetFreq(void)
{
    return CLOCK_GetFreq(kCLOCK_Flexcomm3);
}

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by fsl_spi_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t SPI5_GetFreq(void)
{
    return CLOCK_GetFreq(kCLOCK_Flexcomm5);
}
