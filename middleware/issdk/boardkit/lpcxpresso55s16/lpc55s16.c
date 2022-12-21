/*
 * Copyright 2019 - 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file lpc55s16.c
 * @brief The lpc55s16.c file defines GPIO pins and I2C CMSIS utilities for LPCXpresso55s16 board.
 */

#include "lpc55s16.h"

// I2C4 Pin Handles
/* [PIO1_21] (coords: 30) configured as FC4_RXD_SDA_MOSI */
gpioHandleKSDK_t D14 = {.base = GPIO,
                        .pinNumber = 21,
                        .mask = 1 << (21),
                        .clockName = kCLOCK_Gpio1,
                        .portNumber = kGINT_Port1};
/* [PIO1_20] (coords: 4) configured as FC4_TXD_SCL_MISO */
gpioHandleKSDK_t D15 = {.base = GPIO,
                        .pinNumber = 20,
                        .mask = 1 << (20),
                        .clockName = kCLOCK_Gpio1,
                        .portNumber = kGINT_Port1};

// SPI7 Handle
/* [PIO0_20] (coords: 74) configured as SPI master-out/slave-in (MOSI) data */
gpioHandleKSDK_t D11 = {.base = GPIO,
                        .pinNumber = 26,
                        .mask = 1 << (26),
                        .clockName = kCLOCK_Gpio0,
                        .portNumber = kGINT_Port0};
/* [PIO0_19] (coords: 90) is configured as SPI master-in/slave-out (MISO) data */
gpioHandleKSDK_t D12 = {.base = GPIO,
                        .pinNumber = 3,
                        .mask = 1 << (3),
                        .clockName = kCLOCK_Gpio1,
                        .portNumber = kGINT_Port1};
/* [PIO0_21] (coords: 76) configured as SPI SCK */
gpioHandleKSDK_t D13 = {.base = GPIO,
                        .pinNumber = 2,
                        .mask = 1 << (2),
                        .clockName = kCLOCK_Gpio1,
                        .portNumber = kGINT_Port1};
/* [PIO0_21] (coords: 76) configured as SPI CS */
gpioHandleKSDK_t D10 = {.base = GPIO,
                        .pinNumber = 1,
                        .mask = 1 << (1),
                        .clockName = kCLOCK_Gpio1,
                        .portNumber = kGINT_Port1};

// UART0 Handle
/* [PIO0_29] (coords: 92) configured as USART RXD */
gpioHandleKSDK_t D0 = {.base = GPIO,
                       .pinNumber = 29,
                       .mask = 1 << (29),
                       .clockName = kCLOCK_Gpio0,
                       .portNumber = kGINT_Port0};
/* [PIO0_30] (coords: 94) configured as USART TXD */
gpioHandleKSDK_t D1 = {.base = GPIO,
                       .pinNumber = 30,
                       .mask = 1 << (30),
                       .clockName = kCLOCK_Gpio0,
                       .portNumber = kGINT_Port0};

// LPCXpresso55s69 Internal Peripheral Pin Definitions
gpioHandleKSDK_t RED_LED = {.base = GPIO,
                            .pinNumber = 4,
                            .mask = 1 << (4),
                            .clockName = kCLOCK_Gpio1,
                            .portNumber = kGINT_Port1};
gpioHandleKSDK_t GREEN_LED = {.base = GPIO,
                            .pinNumber = 7,
                            .mask = 1 << (7),
                            .clockName = kCLOCK_Gpio1,
                            .portNumber = kGINT_Port1};
gpioHandleKSDK_t BLUE_LED = {.base = GPIO,
                            .pinNumber = 6,
                            .mask = 1 << (6),
                            .clockName = kCLOCK_Gpio1,
                            .portNumber = kGINT_Port1};

/*!
 * @brief Kinetis style Wrapper API for handling all Clock related configurations.
 *
 * @param void
 * @return void
 */
void BOARD_BootClockRUN(void)
{
    /* attach 12 MHz clock to FLEXCOMM0 (debug/UART0) */
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM0);
    /* attach 12 MHz clock to FLEXCOMM4 (I2C4) */
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM4);
    /* attach 12 MHz clock to FLEXCOMM4 (SPI7) */
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM7);
    /* Configure FROHF96M Clock */
    BOARD_BootClockPLL150M();
}

/*!
 * @brief Configures the system to WAIT power mode.
 *        API name used from Kinetis family to maintain compatibility.
 *
 * @param Power peripheral base address (dummy).
 * @return Configuration error code.
 */
status_t SMC_SetPowerModeWait(void *arg)
{
    //POWER_EnterSleep();

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
    return CLOCK_GetFlexCommClkFreq(0U);
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
    return CLOCK_GetFlexCommClkFreq(4U);
}

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by fsl_spi_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t SPI8_GetFreq(void)
{
    return CLOCK_GetFlexCommClkFreq(8U);
}
