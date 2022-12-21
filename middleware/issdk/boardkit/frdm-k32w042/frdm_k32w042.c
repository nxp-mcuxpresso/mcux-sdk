/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file frdm_k32w042.c
 * @brief The frdm_k32w042.c file defines GPIO pins and I2C CMSIS utilities for FRDM-K64F board.
 */

#include "frdm_k32w042.h"

// I2C20 Pin Handles
gpioHandleKSDK_t D15 = {.base = GPIOC,
                        .portBase = PORTC,
                        .pinNumber = 10,
                        .mask = 1 << (10),
                        .irq = PORTC_IRQn,
                        .clockName = kCLOCK_PortC,
                        .portNumber = PORTC_NUM};
gpioHandleKSDK_t D14 = {.base = GPIOC,
                        .portBase = PORTC,
                        .pinNumber = 9,
                        .mask = 1 << (9),
                        .irq = PORTC_IRQn,
                        .clockName = kCLOCK_PortC,
                        .portNumber = PORTC_NUM};

// I2C3 Pin Handles
gpioHandleKSDK_t A5 = {.base = GPIOE,
                       .portBase = PORTE,
                       .pinNumber = 3,
                       .mask = 1 << (3),
                       .irq = PORTE_IRQn,
                       .clockName = kCLOCK_PortE,
                       .portNumber = PORTE_NUM};
gpioHandleKSDK_t A4 = {.base = GPIOE,
                       .portBase = PORTE,
                       .pinNumber = 2,
                       .mask = 1 << (2),
                       .irq = PORTE_IRQn,
                       .clockName = kCLOCK_PortE,
                       .portNumber = PORTE_NUM};

// SPI0 Pin Handles
gpioHandleKSDK_t D13 = {.base = GPIOB,
                        .portBase = PORTB,
                        .pinNumber = 4,
                        .mask = 1 << (4),
                        .irq = PORTB_IRQn,
                        .clockName = kCLOCK_PortB,
                        .portNumber = PORTB_NUM};
gpioHandleKSDK_t D12 = {.base = GPIOB,
                        .portBase = PORTB,
                        .pinNumber = 7,
                        .mask = 1 << (7),
                        .irq = PORTB_IRQn,
                        .clockName = kCLOCK_PortB,
                        .portNumber = PORTB_NUM};
gpioHandleKSDK_t D11 = {.base = GPIOB,
                        .portBase = PORTB,
                        .pinNumber = 5,
                        .mask = 1 << (5),
                        .irq = PORTB_IRQn,
                        .clockName = kCLOCK_PortB,
                        .portNumber = PORTB_NUM};

// UART1 Handle
gpioHandleKSDK_t D0 = {.base = GPIOA,
                       .portBase = PORTA,
                       .pinNumber = 25,
                       .mask = 1 << (25),
                       .irq = PORTA_IRQn,
                       .clockName = kCLOCK_PortA,
                       .portNumber = PORTA_NUM};
gpioHandleKSDK_t D1 = {.base = GPIOA,
                       .portBase = PORTA,
                       .pinNumber = 26,
                       .mask = 1 << (26),
                       .irq = PORTA_IRQn,
                       .clockName = kCLOCK_PortA,
                       .portNumber = PORTA_NUM};

// K3S Arduino Connector Pin Defintion
gpioHandleKSDK_t A0 = {.base = GPIOC,
                       .portBase = PORTC,
                       .pinNumber = 11,
                       .mask = 1 << (11),
                       .irq = PORTC_IRQn,
                       .clockName = kCLOCK_PortC,
                       .portNumber = PORTC_NUM};
gpioHandleKSDK_t A1 = {.base = GPIOC,
                       .portBase = PORTC,
                       .pinNumber = 12,
                       .mask = 1 << (12),
                       .irq = PORTC_IRQn,
                       .clockName = kCLOCK_PortC,
                       .portNumber = PORTC_NUM};
gpioHandleKSDK_t A2 = {.base = GPIOB,
                       .portBase = PORTB,
                       .pinNumber = 9,
                       .mask = 1 << (9),
                       .irq = PORTB_IRQn,
                       .clockName = kCLOCK_PortB,
                       .portNumber = PORTB_NUM};
gpioHandleKSDK_t A3 = {.base = GPIOE,
                       .portBase = PORTE,
                       .pinNumber = 4,
                       .mask = 1 << (4),
                       .irq = PORTE_IRQn,
                       .clockName = kCLOCK_PortE,
                       .portNumber = PORTE_NUM};
gpioHandleKSDK_t D2 = {.base = GPIOA,
                       .portBase = PORTA,
                       .pinNumber = 27,
                       .mask = 1 << (27),
                       .irq = PORTA_IRQn,
                       .clockName = kCLOCK_PortA,
                       .portNumber = PORTA_NUM};
gpioHandleKSDK_t D3 = {.base = GPIOB,
                       .portBase = PORTB,
                       .pinNumber = 13,
                       .mask = 1 << (13),
                       .irq = PORTB_IRQn,
                       .clockName = kCLOCK_PortB,
                       .portNumber = PORTB_NUM};
gpioHandleKSDK_t D4 = {.base = GPIOB,
                       .portBase = PORTB,
                       .pinNumber = 14,
                       .mask = 1 << (14),
                       .irq = PORTB_IRQn,
                       .clockName = kCLOCK_PortB,
                       .portNumber = PORTB_NUM};
gpioHandleKSDK_t D5 = {.base = GPIOA,
                       .portBase = PORTA,
                       .pinNumber = 30,
                       .mask = 1 << (30),
                       .irq = PORTA_IRQn,
                       .clockName = kCLOCK_PortA,
                       .portNumber = PORTA_NUM};
gpioHandleKSDK_t D6 = {.base = GPIOA,
                       .portBase = PORTA,
                       .pinNumber = 31,
                       .irq = PORTA_IRQn,
                       .clockName = kCLOCK_PortA,
                       .portNumber = PORTA_NUM};
gpioHandleKSDK_t D7 = {.base = GPIOB,
                       .portBase = PORTB,
                       .pinNumber = 1,
                       .mask = 1 << (1),
                       .irq = PORTB_IRQn,
                       .clockName = kCLOCK_PortB,
                       .portNumber = PORTB_NUM};
gpioHandleKSDK_t D8 = {.base = GPIOB,
                       .portBase = PORTB,
                       .pinNumber = 2,
                       .mask = 1 << (2),
                       .irq = PORTB_IRQn,
                       .clockName = kCLOCK_PortB,
                       .portNumber = PORTB_NUM};
gpioHandleKSDK_t D9 = {.base = GPIOB,
                       .portBase = PORTB,
                       .pinNumber = 3,
                       .mask = 1 << (3),
                       .irq = PORTB_IRQn,
                       .clockName = kCLOCK_PortB,
                       .portNumber = PORTB_NUM};
gpioHandleKSDK_t D10 = {.base = GPIOB,
                        .portBase = PORTB,
                        .pinNumber = 6,
                        .mask = 1 << (6),
                        .irq = PORTB_IRQn,
                        .clockName = kCLOCK_PortB,
                        .portNumber = PORTB_NUM};

// K3S Internal Peripheral Pin Definitions
gpioHandleKSDK_t RED_LED = {.base = GPIOA,
                            .portBase = PORTA,
                            .pinNumber = 24,
                            .mask = 1 << (24),
                            .irq = PORTA_IRQn,
                            .clockName = kCLOCK_PortA,
                            .portNumber = PORTA_NUM};
gpioHandleKSDK_t GREEN_LED = {.base = GPIOA,
                              .portBase = PORTA,
                              .pinNumber = 23,
                              .mask = 1 << (23),
                              .irq = PORTA_IRQn,
                              .clockName = kCLOCK_PortA,
                              .portNumber = PORTA_NUM};
gpioHandleKSDK_t BLUE_LED = {.base = GPIOA,
                             .portBase = PORTA,
                             .pinNumber = 22,
                             .mask = 1 << (22),
                             .irq = PORTA_IRQn,
                             .clockName = kCLOCK_PortA,
                             .portNumber = PORTA_NUM};

// K3S I2C Inertial Sensor Pin Definitions
gpioHandleKSDK_t INT1 = {.base = GPIOE,
                         .portBase = PORTE,
                         .pinNumber = 1,
                         .mask = 1 << (1),
                         .irq = PORTE_IRQn,
                         .clockName = kCLOCK_PortE,
                         .portNumber = PORTE_NUM};
gpioHandleKSDK_t INT2 = {.base = GPIOE,
                         .portBase = PORTE,
                         .pinNumber = 22,
                         .mask = 1 << (22),
                         .irq = PORTE_IRQn,
                         .clockName = kCLOCK_PortE,
                         .portNumber = PORTE_NUM};

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by fsl_uart_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t LPUART0_GetFreq(void)
{
    CLOCK_SetIpSrc(kCLOCK_Lpuart0, kCLOCK_IpSrcFircAsync);
    return CLOCK_GetIpFreq(kCLOCK_Lpuart0);
}

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by fsl_uart_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t LPUART1_GetFreq(void)
{
    CLOCK_SetIpSrc(kCLOCK_Lpuart1, kCLOCK_IpSrcFircAsync);
    return CLOCK_GetIpFreq(kCLOCK_Lpuart1);
}

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by fsl_i2c_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t LPI2C0_GetFreq(void)
{
    CLOCK_SetIpSrc(kCLOCK_Lpi2c0, kCLOCK_IpSrcFircAsync);
    return CLOCK_GetIpFreq(kCLOCK_Lpi2c0);
}

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by fsl_i2c_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t LPI2C3_GetFreq(void)
{
    CLOCK_SetIpSrc(kCLOCK_Lpi2c3, kCLOCK_IpSrcFircAsync);
    return CLOCK_GetIpFreq(kCLOCK_Lpi2c3);
}

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by fsl_spi_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t LPSPI0_GetFreq(void)
{
    CLOCK_SetIpSrc(kCLOCK_Lpspi0, kCLOCK_IpSrcFircAsync);
    return CLOCK_GetIpFreq(kCLOCK_Lpspi0);
}
