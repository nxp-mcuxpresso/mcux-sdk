/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file frdm_kl27z.c
 * @brief The frdm_kl27z.c file defines GPIO pins for FRDM-KL27Z board
 */

#include "frdm_kl27z.h"

// I2C1 Pin Handles
gpioHandleKSDK_t D15 = {.base = GPIOD,
                        .portBase = PORTD,
                        .pinNumber = 7,
                        .mask = 1 << (7),
                        .irq = PORTB_PORTC_PORTD_PORTE_IRQn,
                        .clockName = kCLOCK_PortD,
                        .portNumber = PORTD_NUM};
gpioHandleKSDK_t D14 = {.base = GPIOD,
                        .portBase = PORTD,
                        .pinNumber = 6,
                        .mask = 1 << (6),
                        .irq = PORTB_PORTC_PORTD_PORTE_IRQn,
                        .clockName = kCLOCK_PortD,
                        .portNumber = PORTD_NUM};

// I2C0 Handle
gpioHandleKSDK_t A5 = {.base = GPIOB,
                       .portBase = PORTB,
                       .pinNumber = 0,
                       .mask = 1 << (0),
                       .irq = PORTB_PORTC_PORTD_PORTE_IRQn,
                       .clockName = kCLOCK_PortB,
                       .portNumber = PORTB_NUM};
gpioHandleKSDK_t A4 = {.base = GPIOB,
                       .portBase = PORTB,
                       .pinNumber = 1,
                       .mask = 1 << (1),
                       .irq = PORTB_PORTC_PORTD_PORTE_IRQn,
                       .clockName = kCLOCK_PortB,
                       .portNumber = PORTB_NUM};

// SPI1 Handle
gpioHandleKSDK_t D13 = {.base = GPIOC,
                        .portBase = PORTC,
                        .pinNumber = 5,
                        .mask = 1 << (5),
                        .irq = PORTB_PORTC_PORTD_PORTE_IRQn,
                        .clockName = kCLOCK_PortC,
                        .portNumber = PORTC_NUM};
gpioHandleKSDK_t D11 = {.base = GPIOC,
                        .portBase = PORTC,
                        .pinNumber = 6,
                        .mask = 1 << (6),
                        .irq = PORTB_PORTC_PORTD_PORTE_IRQn,
                        .clockName = kCLOCK_PortC,
                        .portNumber = PORTC_NUM};
gpioHandleKSDK_t D12 = {.base = GPIOC,
                        .portBase = PORTC,
                        .pinNumber = 7,
                        .mask = 1 << (7),
                        .irq = PORTB_PORTC_PORTD_PORTE_IRQn,
                        .clockName = kCLOCK_PortC,
                        .portNumber = PORTC_NUM};

// LPUART0 Handle
gpioHandleKSDK_t D0 = {.base = GPIOA,
                       .portBase = PORTA,
                       .pinNumber = 1,
                       .mask = 1 << (1),
                       .irq = PORTA_IRQn,
                       .clockName = kCLOCK_PortA,
                       .portNumber = PORTA_NUM};
gpioHandleKSDK_t D1 = {.base = GPIOA,
                       .portBase = PORTA,
                       .pinNumber = 2,
                       .mask = 1 << (2),
                       .irq = PORTA_IRQn,
                       .clockName = kCLOCK_PortA,
                       .portNumber = PORTA_NUM};

// FRDM-KL27Z Arduino Connector Pin Defintion
gpioHandleKSDK_t A0 = {.base = GPIOE,
                       .portBase = PORTE,
                       .pinNumber = 16,
                       .mask = 1 << (16),
                       .irq = PORTB_PORTC_PORTD_PORTE_IRQn,
                       .clockName = kCLOCK_PortE,
                       .portNumber = PORTE_NUM};
gpioHandleKSDK_t A1 = {.base = GPIOC,
                       .portBase = PORTC,
                       .pinNumber = 0,
                       .mask = 1 << (0),
                       .irq = PORTB_PORTC_PORTD_PORTE_IRQn,
                       .clockName = kCLOCK_PortC,
                       .portNumber = PORTC_NUM};
gpioHandleKSDK_t A2 = {.base = GPIOE,
                       .portBase = PORTE,
                       .pinNumber = 20,
                       .mask = 1 << (20),
                       .irq = PORTB_PORTC_PORTD_PORTE_IRQn,
                       .clockName = kCLOCK_PortE,
                       .portNumber = PORTE_NUM};
gpioHandleKSDK_t A3 = {.base = GPIOE,
                       .portBase = PORTE,
                       .pinNumber = 21,
                       .mask = 1 << (21),
                       .irq = PORTB_PORTC_PORTD_PORTE_IRQn,
                       .clockName = kCLOCK_PortE,
                       .portNumber = PORTE_NUM};
gpioHandleKSDK_t D2 = {.base = GPIOA,
                       .portBase = PORTA,
                       .pinNumber = 12,
                       .mask = 1 << (12),
                       .irq = PORTA_IRQn,
                       .clockName = kCLOCK_PortA,
                       .portNumber = PORTA_NUM};
gpioHandleKSDK_t D3 = {.base = GPIOE,
                       .portBase = PORTE,
                       .pinNumber = 25,
                       .mask = 1 << (25),
                       .irq = PORTB_PORTC_PORTD_PORTE_IRQn,
                       .clockName = kCLOCK_PortE,
                       .portNumber = PORTE_NUM};
gpioHandleKSDK_t D4 = {.base = GPIOA,
                       .portBase = PORTA,
                       .pinNumber = 13,
                       .mask = 1 << (13),
                       .irq = PORTA_IRQn,
                       .clockName = kCLOCK_PortA,
                       .portNumber = PORTA_NUM};
gpioHandleKSDK_t D5 = {.base = GPIOE,
                       .portBase = PORTE,
                       .pinNumber = 24,
                       .mask = 1 << (24),
                       .irq = PORTB_PORTC_PORTD_PORTE_IRQn,
                       .clockName = kCLOCK_PortE,
                       .portNumber = PORTE_NUM};
gpioHandleKSDK_t D6 = {.base = GPIOC,
                       .portBase = PORTC,
                       .pinNumber = 9,
                       .mask = 1 << (9),
                       .irq = PORTB_PORTC_PORTD_PORTE_IRQn,
                       .clockName = kCLOCK_PortC,
                       .portNumber = PORTC_NUM};
gpioHandleKSDK_t D7 = {.base = GPIOC,
                       .portBase = PORTC,
                       .pinNumber = 8,
                       .mask = 1 << (8),
                       .irq = PORTB_PORTC_PORTD_PORTE_IRQn,
                       .clockName = kCLOCK_PortC,
                       .portNumber = PORTC_NUM};
gpioHandleKSDK_t D8 = {.base = GPIOE,
                       .portBase = PORTE,
                       .pinNumber = 31,
                       .mask = 1 << (30),
                       .irq = PORTB_PORTC_PORTD_PORTE_IRQn,
                       .clockName = kCLOCK_PortE,
                       .portNumber = PORTE_NUM};
gpioHandleKSDK_t D9 = {.base = GPIOA,
                       .portBase = PORTA,
                       .pinNumber = 5,
                       .mask = 1 << (5),
                       .irq = PORTA_IRQn,
                       .clockName = kCLOCK_PortA,
                       .portNumber = PORTA_NUM};
gpioHandleKSDK_t D10 = {.base = GPIOC,
                        .portBase = PORTC,
                        .pinNumber = 4,
                        .mask = 1 << (4),
                        .irq = PORTB_PORTC_PORTD_PORTE_IRQn,
                        .clockName = kCLOCK_PortC,
                        .portNumber = PORTC_NUM};

// FRDM-KL27Z Internal Peripheral Pin Definitions
gpioHandleKSDK_t RED_LED = {.base = GPIOB,
                            .portBase = PORTB,
                            .pinNumber = 18,
                            .mask = 1 << (18),
                            .irq = PORTB_PORTC_PORTD_PORTE_IRQn,
                            .clockName = kCLOCK_PortB,
                            .portNumber = PORTB_NUM};
gpioHandleKSDK_t GREEN_LED = {.base = GPIOB,
                              .portBase = PORTB,
                              .pinNumber = 19,
                              .mask = 1 << (19),
                              .irq = PORTB_PORTC_PORTD_PORTE_IRQn,
                              .clockName = kCLOCK_PortB,
                              .portNumber = PORTB_NUM};
gpioHandleKSDK_t BLUE_LED = {.base = GPIOA,
                             .portBase = PORTA,
                             .pinNumber = 13,
                             .mask = 1 << (13),
                             .irq = PORTA_IRQn,
                             .clockName = kCLOCK_PortA,
                             .portNumber = PORTA_NUM};

// FRDM-KL27Z I2C Inertial Sensor Pin Definitions
gpioHandleKSDK_t INT1 = {.base = GPIOC,
                         .portBase = PORTC,
                         .pinNumber = 3,
                         .mask = 1 << (3),
                         .irq = PORTB_PORTC_PORTD_PORTE_IRQn,
                         .clockName = kCLOCK_PortC,
                         .portNumber = PORTC_NUM};
gpioHandleKSDK_t INT2 = {.base = GPIOC,
                         .portBase = PORTC,
                         .pinNumber = 2,
                         .mask = 1 << (2),
                         .irq = PORTB_PORTC_PORTD_PORTE_IRQn,
                         .clockName = kCLOCK_PortC,
                         .portNumber = PORTC_NUM};

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by fsl_uart_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t LPUART0_GetFreq(void)
{
    CLOCK_SetLpuart0Clock(1);
    return CLOCK_GetPeriphClkFreq();
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
    CLOCK_SetLpuart1Clock(1);
    return CLOCK_GetPeriphClkFreq();
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
 *  @details     The Clock Frequecny computation API required by fsl_spi_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t SPI0_GetFreq(void)
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
uint32_t SPI1_GetFreq(void)
{
    return CLOCK_GetBusClkFreq();
}
