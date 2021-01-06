/*
 * Copyright  2017 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_SWM_CONNECTIONS_
#define _FSL_SWM_CONNECTIONS_

#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.swm_connections"
#endif

/*!
 * @addtogroup swm
 * @{
 */

/*!
 * @name swm connections
 * @{
 */

/*! @brief SWM port_pin number */
typedef enum _swm_port_pin_type_t
{
    kSWM_PortPin_P0_0 = 0U,   /*!< port_pin number P0_0. */
    kSWM_PortPin_P0_1 = 1U,   /*!< port_pin number P0_1. */
    kSWM_PortPin_P0_2 = 2U,   /*!< port_pin number P0_2. */
    kSWM_PortPin_P0_3 = 3U,   /*!< port_pin number P0_3. */
    kSWM_PortPin_P0_4 = 4U,   /*!< port_pin number P0_4. */
    kSWM_PortPin_P0_5 = 5U,   /*!< port_pin number P0_5. */
    kSWM_PortPin_P0_6 = 6U,   /*!< port_pin number P0_6. */
    kSWM_PortPin_P0_7 = 7U,   /*!< port_pin number P0_7. */
    kSWM_PortPin_P0_8 = 8U,   /*!< port_pin number P0_8. */
    kSWM_PortPin_P0_9 = 9U,   /*!< port_pin number P0_9. */
    kSWM_PortPin_P0_10 = 10U, /*!< port_pin number P0_10. */
    kSWM_PortPin_P0_11 = 11U, /*!< port_pin number P0_11. */
    kSWM_PortPin_P0_12 = 12U, /*!< port_pin number P0_12. */
    kSWM_PortPin_P0_13 = 13U, /*!< port_pin number P0_13. */
    kSWM_PortPin_P0_14 = 14U, /*!< port_pin number P0_14. */
    kSWM_PortPin_P0_15 = 15U, /*!< port_pin number P0_15. */
    kSWM_PortPin_P0_16 = 16U, /*!< port_pin number P0_16. */
    kSWM_PortPin_P0_17 = 17U, /*!< port_pin number P0_17. */
    kSWM_PortPin_Reset = 0xffU /*!< port_pin reset number. */
} swm_port_pin_type_t;

/*! @brief SWM movable selection */
typedef enum _swm_select_movable_t
{
    kSWM_USART0_TXD = 0U, /*!< Movable function as USART0_TXD. */
    kSWM_USART0_RXD = 1U, /*!< Movable function as USART0_RXD. */
    kSWM_USART0_RTS = 2U, /*!< Movable function as USART0_RTS. */
    kSWM_USART0_CTS = 3U, /*!< Movable function as USART0_CTS. */

    kSWM_USART0_SCLK = 4U, /*!< Movable function as USART0_SCLK. */
    kSWM_USART1_TXD = 5U,  /*!< Movable function as USART1_TXD. */
    kSWM_USART1_RXD = 6U,  /*!< Movable function as USART1_RXD. */
    kSWM_USART1_RTS = 7U,  /*!< Movable function as USART1_RTS. */

    kSWM_USART1_CTS = 8U,  /*!< Movable function as USART1_CTS. */
    kSWM_USART1_SCLK = 9U, /*!< Movable function as USART1_SCLK. */
    kSWM_USART2_TXD = 10U, /*!< Movable function as USART2_TXD. */
    kSWM_USART2_RXD = 11U, /*!< Movable function as USART2_RXD. */

    kSWM_USART2_RTS = 12U,  /*!< Movable function as USART2_RTS. */
    kSWM_USART2_CTS = 13U,  /*!< Movable function as USART2_CTS. */
    kSWM_USART2_SCLK = 14U, /*!< Movable function as USART2_SCLK. */
    kSWM_SPI0_SCK = 15U,    /*!< Movable function as SPI0_SCK. */

    kSWM_SPI0_MOSI = 16U, /*!< Movable function as SPI0_MOSI. */
    kSWM_SPI0_MISO = 17U, /*!< Movable function as SPI0_MISO. */
    kSWM_SPI0_SSEL = 18U, /*!< Movable function as SPI0_SSEL0. */
    kSWM_SPI1_SCK = 19U,  /*!< Movable function as SPI1_SCK. */

    kSWM_SPI1_MOSI = 20U, /*!< Movable function as SPI1_MOSI. */
    kSWM_SPI1_MISO = 21U, /*!< Movable function as SPI1_MISO. */
    kSWM_SPI1_SSEL = 22U, /*!< Movable function as SPI1_SSEL0. */
    kSWM_CTIN_0 = 23U,    /*!< Movable function as CTIN_0. */

    kSWM_CTIN_1 = 24U,  /*!< Movable function as CTIN_1. */
    kSWM_CTIN_2 = 25U,  /*!< Movable function as CTIN_2. */
    kSWM_CTIN_3 = 26U,  /*!< Movable function as CTIN_3. */
    kSWM_CTOUT_0 = 27U, /*!< Movable function as CTOUT_0. */

    kSWM_CTOUT_1 = 28U, /*!< Movable function as CTOUT_1. */
    kSWM_CTOUT_2 = 29U, /*!< Movable function as CTOUT_2. */
    kSWM_CTOUT_3 = 30U, /*!< Movable function as CTOUT_3. */
    kSWM_I2C_SDA = 31U, /*!< Movable function as I2C_SDA. */

    kSWM_I2C_SCL = 32U,       /*!< Movable function as I2C_SCL. */
    kSWM_ACMP_OUT = 33U,      /*!< Movable function as ACMP_OUT. */
    kSWM_CLKOUT = 34U,        /*!< Movable function as CLKOUT. */
    kSWM_GPIO_INT_BMAT = 35U, /*!< Movable function as GPIO_INT_BMAT. */

    kSWM_MOVABLE_NUM_FUNCS = 36U, /*!< Movable function number. */
} swm_select_movable_t;

/*! @brief SWM fixed pin selection */
typedef enum _swm_select_fixed_pin_t
{
    kSWM_ACMP_INPUT1 = SWM_PINENABLE0_ACMP_I1_MASK, /*!< Fixed-pin function as ACMP_INPUT1. */
    kSWM_ACMP_INPUT2 = SWM_PINENABLE0_ACMP_I2_MASK, /*!< Fixed-pin function as ACMP_INPUT2. */
    kSWM_SWCLK = SWM_PINENABLE0_SWCLK_MASK,         /*!< Fixed-pin function as SWCLK. */
    kSWM_SWDIO = SWM_PINENABLE0_SWDIO_MASK,         /*!< Fixed-pin function as SWDIO. */
    kSWM_XTALIN = SWM_PINENABLE0_XTALIN_MASK,       /*!< Fixed-pin function as XTALIN. */
    kSWM_XTALOUT = SWM_PINENABLE0_XTALOUT_MASK,     /*!< Fixed-pin function as XTALOUT. */
    kSWM_RESETN = SWM_PINENABLE0_RESETN_MASK,       /*!< Fixed-pin function as RESETN. */
    kSWM_CLKIN = SWM_PINENABLE0_CLKIN_MASK,         /*!< Fixed-pin function as CLKIN. */
    kSWM_VDDCMP = SWM_PINENABLE0_VDDCMP_MASK,       /*!< Fixed-pin function as VDDCMP. */

    kSWM_FIXEDPIN_NUM_FUNCS = (int)0x80000101U, /*!< Fixed-pin function number. */
} swm_select_fixed_pin_t;

/*@}*/

/*@}*/

#endif /* _FSL_INPUTMUX_CONNECTIONS_ */
