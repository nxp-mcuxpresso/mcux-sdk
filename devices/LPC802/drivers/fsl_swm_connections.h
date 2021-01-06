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
    kSWM_PortPin_P0_17 = 16U, /*!< port_pin number P0_17. */
    kSWM_PortPin_Reset = 0xffU /*!< port_pin reset number. */
} swm_port_pin_type_t;

/*! @brief SWM movable selection */
typedef enum _swm_select_movable_t
{
    kSWM_USART0_TXD = 0U,  /*!< Movable function as USART0_TXD. */
    kSWM_USART0_RXD = 1U,  /*!< Movable function as USART0_RXD. */
    kSWM_USART0_RTS = 2U,  /*!< Movable function as USART0_RTS. */
    kSWM_USART0_CTS = 3U,  /*!< Movable function as USART0_CTS. */
    kSWM_USART0_SCLK = 4U, /*!< Movable function as USART0_SCLK. */

    kSWM_USART1_TXD = 5U,  /*!< Movable function as USART1_TXD. */
    kSWM_USART1_RXD = 6U,  /*!< Movable function as USART1_RXD. */
    kSWM_USART1_SCLK = 7U, /*!< Movable function as USART1_SCLK. */

    kSWM_SPI0_SCK = 8U,   /*!< Movable function as SPI0_SCK. */
    kSWM_SPI0_MOSI = 9U,  /*!< Movable function as SPI0_MOSI. */
    kSWM_SPI0_MISO = 10U,  /*!< Movable function as SPI0_MISO. */
    kSWM_SPI0_SSEL0 = 11U, /*!< Movable function as SPI0_SSEL0. */
    kSWM_SPI0_SSEL1 = 12U, /*!< Movable function as SPI0_SSEL1. */
    
    kSWM_T0_CAP_CHN0 = 13U, /*!< Movable function as Timer Capture Channel 0. */
    kSWM_T0_CAP_CHN1 = 14U, /*!< Movable function as Timer Capture Channel 1. */
    kSWM_T0_CAP_CHN2 = 15U, /*!< Movable function as Timer Capture Channel 2. */
    kSWM_T0_MAT_CHN0 = 16U, /*!< Movable function as Timer Match Channel 0. */
    kSWM_T0_MAT_CHN1 = 17U, /*!< Movable function as Timer Match Channel 1. */
    kSWM_T0_MAT_CHN2 = 18U, /*!< Movable function as Timer Match Channel 2. */
    kSWM_T0_MAT_CHN3 = 19U, /*!< Movable function as Timer Match Channel 3. */
    
    kSWM_I2C0_SDA = 20U, /*!< Movable function as I2C1_SDA. */
    kSWM_I2C0_SCL = 21U, /*!< Movable function as I2C1_SCL. */

    kSWM_ACMP_OUT = 22U,      /*!< Movable function as ACMP_OUT. */
    kSWM_CLKOUT = 23U,        /*!< Movable function as CLKOUT. */
    kSWM_GPIO_INT_BMAT = 24U, /*!< Movable function as GPIO_INT_BMAT. */
    
    kSWM_LVLSHFT_IN0 = 25U,  /*!< Movable function as LVLSHFT_IN0. */
    kSWM_LVLSHFT_IN1 = 26U,  /*!< Movable function as LVLSHFT_IN1. */
    kSWM_LVLSHFT_OUT0 = 27U, /*!< Movable function as LVLSHFT_OUT0. */
    kSWM_LVLSHFT_OUT1 = 28U, /*!< Movable function as LVLSHFT_OUT1. */

    kSWM_MOVABLE_NUM_FUNCS = 29U, /*!< Movable function number. */
} swm_select_movable_t;

/*! @brief SWM fixed pin selection */
typedef enum _swm_select_fixed_pin_t
{
    kSWM_ACMP_INPUT1 = SWM_PINENABLE0_ACMP_I1_MASK, /*!< Fixed-pin function as ACMP_INPUT1. */
    kSWM_ACMP_INPUT2 = SWM_PINENABLE0_ACMP_I2_MASK, /*!< Fixed-pin function as ACMP_INPUT2. */
    kSWM_ACMP_INPUT3 = SWM_PINENABLE0_ACMP_I3_MASK, /*!< Fixed-pin function as ACMP_INPUT3. */
    kSWM_ACMP_INPUT4 = SWM_PINENABLE0_ACMP_I4_MASK, /*!< Fixed-pin function as ACMP_INPUT4. */
    kSWM_SWCLK = SWM_PINENABLE0_SWCLK_MASK,         /*!< Fixed-pin function as SWCLK. */
    kSWM_SWDIO = SWM_PINENABLE0_SWDIO_MASK,         /*!< Fixed-pin function as SWDIO. */
    kSWM_RESETN = SWM_PINENABLE0_RESETN_MASK,       /*!< Fixed-pin function as RESETN. */
    kSWM_CLKIN = SWM_PINENABLE0_CLKIN_MASK,         /*!< Fixed-pin function as CLKIN. */
    kSWM_WKCLKIN = SWM_PINENABLE0_WKCLKIN_MASK,     /*!< Fixed-pin function as CLKIN. */
    kSWM_VDDCMP = SWM_PINENABLE0_VDDCMP_MASK,       /*!< Fixed-pin function as VDDCMP. */
    kSWM_ADC_CHN0 = SWM_PINENABLE0_ADC_0_MASK,      /*!< Fixed-pin function as ADC_CHN0. */
    kSWM_ADC_CHN1 = SWM_PINENABLE0_ADC_1_MASK,      /*!< Fixed-pin function as ADC_CHN1. */
    kSWM_ADC_CHN2 = SWM_PINENABLE0_ADC_2_MASK,      /*!< Fixed-pin function as ADC_CHN2. */
    kSWM_ADC_CHN3 = SWM_PINENABLE0_ADC_3_MASK,      /*!< Fixed-pin function as ADC_CHN3. */
    kSWM_ADC_CHN4 = SWM_PINENABLE0_ADC_4_MASK,      /*!< Fixed-pin function as ADC_CHN4. */
    kSWM_ADC_CHN5 = SWM_PINENABLE0_ADC_5_MASK,      /*!< Fixed-pin function as ADC_CHN5. */
    kSWM_ADC_CHN6 = SWM_PINENABLE0_ADC_6_MASK,      /*!< Fixed-pin function as ADC_CHN6. */
    kSWM_ADC_CHN7 = SWM_PINENABLE0_ADC_7_MASK,      /*!< Fixed-pin function as ADC_CHN7. */
    kSWM_ADC_CHN8 = SWM_PINENABLE0_ADC_8_MASK,      /*!< Fixed-pin function as ADC_CHN8. */
    kSWM_ADC_CHN9 = SWM_PINENABLE0_ADC_9_MASK,      /*!< Fixed-pin function as ADC_CHN9. */
    kSWM_ADC_CHN10 = SWM_PINENABLE0_ADC_10_MASK,    /*!< Fixed-pin function as ADC_CHN10. */
    kSWM_ADC_CHN11 = SWM_PINENABLE0_ADC_11_MASK,    /*!< Fixed-pin function as ADC_CHN11. */

    kSWM_FIXEDPIN_NUM_FUNCS = 0x200001U, /*!< Fixed-pin function number. */
} swm_select_fixed_pin_t;

/*@}*/

/*@}*/

#endif /* _FSL_SWM_CONNECTIONS_ */
