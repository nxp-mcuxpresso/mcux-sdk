/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file frdm_k64f.c
 * @brief The frdm_k64f.c file defines GPIO pins and I2C CMSIS utilities for FRDM-K64F board.
 */

#include "frdm_k64f.h"

// I2C0 Pin Handles
gpioHandleKSDK_t D15 = {.base = GPIOE,
                        .portBase = PORTE,
                        .pinNumber = 24,
                        .mask = 1 << (24),
                        .irq = PORTE_IRQn,
                        .clockName = kCLOCK_PortE,
                        .portNumber = PORTE_NUM};
gpioHandleKSDK_t D14 = {.base = GPIOE,
                        .portBase = PORTE,
                        .pinNumber = 25,
                        .mask = 1 << (25),
                        .irq = PORTE_IRQn,
                        .clockName = kCLOCK_PortE,
                        .portNumber = PORTE_NUM};

// I2C1 Handle
gpioHandleKSDK_t A5 = {.base = GPIOC,
                       .portBase = PORTC,
                       .pinNumber = 10,
                       .mask = 1 << (10),
                       .irq = PORTC_IRQn,
                       .clockName = kCLOCK_PortC,
                       .portNumber = PORTC_NUM};
gpioHandleKSDK_t A4 = {.base = GPIOC,
                       .portBase = PORTC,
                       .pinNumber = 11,
                       .mask = 1 << (11),
                       .irq = PORTC_IRQn,
                       .clockName = kCLOCK_PortC,
                       .portNumber = PORTC_NUM};

// SPI0 Handle
gpioHandleKSDK_t D13 = {.base = GPIOD,
                        .portBase = PORTD,
                        .pinNumber = 1,
                        .mask = 1 << (1),
                        .irq = PORTD_IRQn,
                        .clockName = kCLOCK_PortD,
                        .portNumber = PORTD_NUM};
gpioHandleKSDK_t D11 = {.base = GPIOD,
                        .portBase = PORTD,
                        .pinNumber = 2,
                        .mask = 1 << (2),
                        .irq = PORTD_IRQn,
                        .clockName = kCLOCK_PortD,
                        .portNumber = PORTD_NUM};
gpioHandleKSDK_t D12 = {.base = GPIOD,
                        .portBase = PORTD,
                        .pinNumber = 3,
                        .mask = 1 << (3),
                        .irq = PORTD_IRQn,
                        .clockName = kCLOCK_PortD,
                        .portNumber = PORTD_NUM};

// UART3 Handle
gpioHandleKSDK_t D0 = {.base = GPIOC,
                       .portBase = PORTC,
                       .pinNumber = 16,
                       .mask = 1 << (16),
                       .irq = PORTC_IRQn,
                       .clockName = kCLOCK_PortC,
                       .portNumber = PORTC_NUM};
gpioHandleKSDK_t D1 = {.base = GPIOC,
                       .portBase = PORTC,
                       .pinNumber = 17,
                       .mask = 1 << (17),
                       .irq = PORTC_IRQn,
                       .clockName = kCLOCK_PortC,
                       .portNumber = PORTC_NUM};

// FRDM-K64F Arduino Connector Pin Defintion
gpioHandleKSDK_t A0 = {.base = GPIOB,
                       .portBase = PORTB,
                       .pinNumber = 2,
                       .mask = 1 << (2),
                       .irq = PORTB_IRQn,
                       .clockName = kCLOCK_PortB,
                       .portNumber = PORTB_NUM};
gpioHandleKSDK_t A1 = {.base = GPIOB,
                       .portBase = PORTB,
                       .pinNumber = 3,
                       .mask = 1 << (3),
                       .irq = PORTB_IRQn,
                       .clockName = kCLOCK_PortB,
                       .portNumber = PORTB_NUM};
gpioHandleKSDK_t A2 = {.base = GPIOB,
                       .portBase = PORTB,
                       .pinNumber = 10,
                       .mask = 1 << (10),
                       .irq = PORTB_IRQn,
                       .clockName = kCLOCK_PortB,
                       .portNumber = PORTB_NUM};
gpioHandleKSDK_t A3 = {.base = GPIOB,
                       .portBase = PORTB,
                       .pinNumber = 11,
                       .mask = 1 << (11),
                       .irq = PORTB_IRQn,
                       .clockName = kCLOCK_PortB,
                       .portNumber = PORTB_NUM};
gpioHandleKSDK_t D2 = {.base = GPIOB,
                       .portBase = PORTB,
                       .pinNumber = 9,
                       .mask = 1 << (9),
                       .irq = PORTB_IRQn,
                       .clockName = kCLOCK_PortB,
                       .portNumber = PORTB_NUM};
gpioHandleKSDK_t D3 = {.base = GPIOA,
                       .portBase = PORTA,
                       .pinNumber = 1,
                       .mask = 1 << (1),
                       .irq = PORTA_IRQn,
                       .clockName = kCLOCK_PortA,
                       .portNumber = PORTA_NUM};
gpioHandleKSDK_t D4 = {.base = GPIOB,
                       .portBase = PORTB,
                       .pinNumber = 23,
                       .mask = 1 << (23),
                       .irq = PORTB_IRQn,
                       .clockName = kCLOCK_PortB,
                       .portNumber = PORTB_NUM};
gpioHandleKSDK_t D5 = {.base = GPIOA,
                       .portBase = PORTA,
                       .pinNumber = 2,
                       .mask = 1 << (2),
                       .irq = PORTA_IRQn,
                       .clockName = kCLOCK_PortA,
                       .portNumber = PORTA_NUM};
gpioHandleKSDK_t D6 = {.base = GPIOC,
                       .portBase = PORTC,
                       .pinNumber = 2,
                       .mask = 1 << (2),
                       .irq = PORTC_IRQn,
                       .clockName = kCLOCK_PortC,
                       .portNumber = PORTC_NUM};
gpioHandleKSDK_t D7 = {.base = GPIOC,
                       .portBase = PORTC,
                       .pinNumber = 3,
                       .mask = 1 << (3),
                       .irq = PORTC_IRQn,
                       .clockName = kCLOCK_PortC,
                       .portNumber = PORTC_NUM};
gpioHandleKSDK_t D8 = {.base = GPIOA,
                       .portBase = PORTA,
                       .pinNumber = 0,
                       .mask = 1 << (0),
                       .irq = PORTA_IRQn,
                       .clockName = kCLOCK_PortA,
                       .portNumber = PORTA_NUM};
gpioHandleKSDK_t D9 = {.base = GPIOC,
                       .portBase = PORTC,
                       .pinNumber = 4,
                       .mask = 1 << (4),
                       .irq = PORTC_IRQn,
                       .clockName = kCLOCK_PortC,
                       .portNumber = PORTC_NUM};
gpioHandleKSDK_t D10 = {.base = GPIOD,
                        .portBase = PORTD,
                        .pinNumber = 0,
                        .mask = 1 << (0),
                        .irq = PORTD_IRQn,
                        .clockName = kCLOCK_PortD,
                        .portNumber = PORTD_NUM};

// FRDM-K64F Internal Peripheral Pin Definitions
gpioHandleKSDK_t RED_LED = {.base = GPIOB,
                            .portBase = PORTB,
                            .pinNumber = 22,
                            .mask = 1 << (22),
                            .irq = PORTB_IRQn,
                            .clockName = kCLOCK_PortB,
                            .portNumber = PORTB_NUM};
gpioHandleKSDK_t GREEN_LED = {.base = GPIOE,
                              .portBase = PORTE,
                              .pinNumber = 26,
                              .mask = 1 << (26),
                              .irq = PORTE_IRQn,
                              .clockName = kCLOCK_PortE,
                              .portNumber = PORTE_NUM};
gpioHandleKSDK_t BLUE_LED = {.base = GPIOB,
                             .portBase = PORTB,
                             .pinNumber = 21,
                             .mask = 1 << (21),
                             .irq = PORTB_IRQn,
                             .clockName = kCLOCK_PortB,
                             .portNumber = PORTB_NUM};

// FRDM-K64F I2C Inertial Sensor Pin Definitions
gpioHandleKSDK_t INT1 = {.base = GPIOC,
                         .portBase = PORTC,
                         .pinNumber = 6,
                         .mask = 1 << (6),
                         .irq = PORTC_IRQn,
                         .clockName = kCLOCK_PortC,
                         .portNumber = PORTC_NUM};
gpioHandleKSDK_t INT2 = {.base = GPIOC,
                         .portBase = PORTC,
                         .pinNumber = 13,
                         .mask = 1 << (13),
                         .irq = PORTC_IRQn,
                         .clockName = kCLOCK_PortC,
                         .portNumber = PORTC_NUM};

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by fsl_uart_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t UART0_GetFreq(void)
{
    return CLOCK_GetFreq(UART0_CLK_SRC);
}

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by fsl_uart_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t UART1_GetFreq(void)
{
    return CLOCK_GetFreq(UART1_CLK_SRC);
}

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by fsl_uart_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t UART2_GetFreq(void)
{
    return CLOCK_GetFreq(UART2_CLK_SRC);
}

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by fsl_uart_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t UART3_GetFreq(void)
{
    return CLOCK_GetFreq(UART3_CLK_SRC);
}

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by fsl_uart_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t UART4_GetFreq(void)
{
    return CLOCK_GetFreq(UART4_CLK_SRC);
}

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by fsl_uart_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t UART5_GetFreq(void)
{
    return CLOCK_GetFreq(UART5_CLK_SRC);
}

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by fsl_i2c_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t I2C0_GetFreq(void)
{
    return CLOCK_GetFreq(I2C0_CLK_SRC);
}

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by fsl_i2c_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t I2C1_GetFreq(void)
{
    return CLOCK_GetFreq(I2C1_CLK_SRC);
}

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by fsl_i2c_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t I2C2_GetFreq(void)
{
    return CLOCK_GetFreq(I2C2_CLK_SRC);
}

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by fsl_spi_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t DSPI0_GetFreq(void)
{
    return CLOCK_GetBusClkFreq();
}

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by fsl_spi_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t DSPI1_GetFreq(void)
{
    return CLOCK_GetBusClkFreq();
}

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by fsl_spi_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t DSPI2_GetFreq(void)
{
    return CLOCK_GetBusClkFreq();
}
