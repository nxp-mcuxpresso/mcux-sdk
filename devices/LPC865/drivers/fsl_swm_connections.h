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
    kSWM_PortPin_P0_0  = 0U,  /*!< port_pin number P0_0. */
    kSWM_PortPin_P0_1  = 1U,  /*!< port_pin number P0_1. */
    kSWM_PortPin_P0_2  = 2U,  /*!< port_pin number P0_2. */
    kSWM_PortPin_P0_3  = 3U,  /*!< port_pin number P0_3. */
    kSWM_PortPin_P0_4  = 4U,  /*!< port_pin number P0_4. */
    kSWM_PortPin_P0_5  = 5U,  /*!< port_pin number P0_5. */
    kSWM_PortPin_P0_6  = 6U,  /*!< port_pin number P0_6. */
    kSWM_PortPin_P0_7  = 7U,  /*!< port_pin number P0_7. */
    kSWM_PortPin_P0_8  = 8U,  /*!< port_pin number P0_8. */
    kSWM_PortPin_P0_9  = 9U,  /*!< port_pin number P0_9. */
    kSWM_PortPin_P0_10 = 10U, /*!< port_pin number P0_10. */
    kSWM_PortPin_P0_11 = 11U, /*!< port_pin number P0_11. */
    kSWM_PortPin_P0_12 = 12U, /*!< port_pin number P0_12. */
    kSWM_PortPin_P0_13 = 13U, /*!< port_pin number P0_13. */
    kSWM_PortPin_P0_14 = 14U, /*!< port_pin number P0_14. */
    kSWM_PortPin_P0_15 = 15U, /*!< port_pin number P0_15. */
    kSWM_PortPin_P0_16 = 16U, /*!< port_pin number P0_16. */
    kSWM_PortPin_P0_17 = 17U, /*!< port_pin number P0_17. */
    kSWM_PortPin_P0_18 = 18U, /*!< port_pin number P0_18. */
    kSWM_PortPin_P0_19 = 19U, /*!< port_pin number P0_19. */
    kSWM_PortPin_P0_20 = 20U, /*!< port_pin number P0_20. */
    kSWM_PortPin_P0_21 = 21U, /*!< port_pin number P0_21. */
    kSWM_PortPin_P0_22 = 22U, /*!< port_pin number P0_22. */
    kSWM_PortPin_P0_23 = 23U, /*!< port_pin number P0_23. */
    kSWM_PortPin_P0_24 = 24U, /*!< port_pin number P0_24. */
    kSWM_PortPin_P0_25 = 25U, /*!< port_pin number P0_25. */
    kSWM_PortPin_P0_26 = 26U, /*!< port_pin number P0_26. */
    kSWM_PortPin_P0_27 = 27U, /*!< port_pin number P0_27. */
    kSWM_PortPin_P0_28 = 28U, /*!< port_pin number P0_28. */
    kSWM_PortPin_P0_29 = 29U, /*!< port_pin number P0_29. */
    kSWM_PortPin_P0_30 = 30U, /*!< port_pin number P0_30. */
    kSWM_PortPin_P0_31 = 31U, /*!< port_pin number P0_31. */

    kSWM_PortPin_P1_0  = 32U,  /*!< port_pin number P1_0. */
    kSWM_PortPin_P1_1  = 33U,  /*!< port_pin number P1_1. */
    kSWM_PortPin_P1_2  = 34U,  /*!< port_pin number P1_2. */
    kSWM_PortPin_P1_3  = 35U,  /*!< port_pin number P1_3. */
    kSWM_PortPin_P1_4  = 36U,  /*!< port_pin number P1_4. */
    kSWM_PortPin_P1_5  = 37U,  /*!< port_pin number P1_5. */
    kSWM_PortPin_P1_6  = 38U,  /*!< port_pin number P1_6. */
    kSWM_PortPin_P1_7  = 39U,  /*!< port_pin number P1_7. */
    kSWM_PortPin_P1_8  = 40U,  /*!< port_pin number P1_8. */
    kSWM_PortPin_P1_9  = 41U,  /*!< port_pin number P1_9. */
    kSWM_PortPin_P1_10 = 42U,  /*!< port_pin number P1_10. */
    kSWM_PortPin_P1_11 = 43U,  /*!< port_pin number P1_11. */
    kSWM_PortPin_P1_12 = 44U,  /*!< port_pin number P1_12. */
    kSWM_PortPin_P1_13 = 45U,  /*!< port_pin number P1_13. */
    kSWM_PortPin_P1_14 = 46U,  /*!< port_pin number P1_14. */
    kSWM_PortPin_P1_15 = 47U,  /*!< port_pin number P1_15. */
    kSWM_PortPin_P1_16 = 48U,  /*!< port_pin number P1_16. */
    kSWM_PortPin_P1_17 = 49U,  /*!< port_pin number P1_17. */
    kSWM_PortPin_P1_18 = 50U,  /*!< port_pin number P1_18. */
    kSWM_PortPin_P1_19 = 51U,  /*!< port_pin number P1_19. */
    kSWM_PortPin_P1_20 = 52U,  /*!< port_pin number P1_20. */
    kSWM_PortPin_P1_21 = 53U,  /*!< port_pin number P1_21. */
    kSWM_PortPin_Reset = 0xffU /*!< port_pin reset number. */
} swm_port_pin_type_t;

/*! @brief SWM movable selection */
typedef enum _swm_select_movable_t
{
    kSWM_USART0_TXD  = 0U, /*!< Movable function as USART0_TXD. */
    kSWM_USART0_RXD  = 1U, /*!< Movable function as USART0_RXD. */
    kSWM_USART0_RTS  = 2U, /*!< Movable function as USART0_RTS. */
    kSWM_USART0_CTS  = 3U, /*!< Movable function as USART0_CTS. */
    kSWM_USART0_SCLK = 4U, /*!< Movable function as USART0_SCLK. */

    kSWM_USART1_TXD  = 5U, /*!< Movable function as USART1_TXD. */
    kSWM_USART1_RXD  = 6U, /*!< Movable function as USART1_RXD. */
    kSWM_USART1_RTS  = 7U, /*!< Movable function as USART1_RTS. */
    kSWM_USART1_CTS  = 8U, /*!< Movable function as USART1_CTS. */
    kSWM_USART1_SCLK = 9U, /*!< Movable function as USART1_SCLK. */

    kSWM_USART2_TXD  = 10U, /*!< Movable function as USART2_TXD. */
    kSWM_USART2_RXD  = 11U, /*!< Movable function as USART2_RXD. */
    kSWM_USART2_RTS  = 12U, /*!< Movable function as USART2_RTS. */
    kSWM_USART2_CTS  = 13U, /*!< Movable function as USART2_CTS. */
    kSWM_USART2_SCLK = 14U, /*!< Movable function as USART2_SCLK. */

    kSWM_SPI0_SCK   = 15U, /*!< Movable function as SPI0_SCK. */
    kSWM_SPI0_MOSI  = 16U, /*!< Movable function as SPI0_MOSI. */
    kSWM_SPI0_MISO  = 17U, /*!< Movable function as SPI0_MISO. */
    kSWM_SPI0_SSEL0 = 18U, /*!< Movable function as SPI0_SSEL0. */
    kSWM_SPI0_SSEL1 = 19U, /*!< Movable function as SPI0_SSEL1. */
    kSWM_SPI0_SSEL2 = 20U, /*!< Movable function as SPI0_SSEL2. */
    kSWM_SPI0_SSEL3 = 21U, /*!< Movable function as SPI0_SSEL3. */

    kSWM_SPI1_SCK   = 22U, /*!< Movable function as SPI1_SCK. */
    kSWM_SPI1_MOSI  = 23U, /*!< Movable function as SPI1_MOSI. */
    kSWM_SPI1_MISO  = 24U, /*!< Movable function as SPI1_MISO. */
    kSWM_SPI1_SSEL0 = 25U, /*!< Movable function as SPI1_SSEL0. */
    kSWM_SPI1_SSEL1 = 26U, /*!< Movable function as SPI1_SSEL1. */

    kSWM_I2C0_SDA = 27U, /*!< Movable function as I2C0_SDA. */
    kSWM_I2C0_SCL = 28U, /*!< Movable function as I2C0_SCL. */
    kSWM_I3C0_SDA = 29U, /*!< Movable function as I3C0_SDA. */
    kSWM_I3C0_SCL = 30U, /*!< Movable function as I3C0_SCL. */
    kSWM_I3C0_PUR = 31U, /*!< Movable function as I3C0_PUR. */

    kSWM_ACMP_O        = 32U, /*!< Movable function as COMP0_OUT. */
    kSWM_CLKOUT        = 33U, /*!< Movable function as CLKOUT. */
    kSWM_GPIO_INT_BMAT = 34U, /*!< Movable function as GPIO_INT_BMAT. */

    kSWM_MOVABLE_NUM_FUNCS = 35U, /*!< Movable function number. */
} swm_select_movable_t;

/*! @brief SWM fixed pin selection */
typedef enum _swm_select_fixed_pin_t
{
    kSWM_ACMP_INPUT1 = SWM_PINENABLE0_ACMP_I1_MASK, /*!< Fixed-pin function as ACMP_INPUT1. */
    kSWM_ACMP_INPUT2 = SWM_PINENABLE0_ACMP_I2_MASK, /*!< Fixed-pin function as ACMP_INPUT2. */
    kSWM_ACMP_INPUT3 = SWM_PINENABLE0_ACMP_I3_MASK, /*!< Fixed-pin function as ACMP_INPUT3. */
    kSWM_ACMP_INPUT4 = SWM_PINENABLE0_ACMP_I4_MASK, /*!< Fixed-pin function as ACMP_INPUT4. */
    kSWM_ACMP_INPUT5 = SWM_PINENABLE0_ACMP_I5_MASK, /*!< Fixed-pin function as ACMP_INPUT5. */
    kSWM_SWCLK       = SWM_PINENABLE0_SWCLK_MASK,   /*!< Fixed-pin function as SWCLK. */
    kSWM_SWDIO       = SWM_PINENABLE0_SWDIO_MASK,   /*!< Fixed-pin function as SWDIO. */
    kSWM_RESETN      = SWM_PINENABLE0_RESETN_MASK,  /*!< Fixed-pin function as RESETN. */
    kSWM_CLKIN       = SWM_PINENABLE0_CLKIN_MASK,   /*!< Fixed-pin function as CLKIN. */
    kSWM_CMPVREF     = SWM_PINENABLE0_CMPVREF_MASK, /*!< Fixed-pin function as CMPVREF. */
    kSWM_XTALIN      = SWM_PINENABLE0_XTALIN_MASK,  /*!< Fixed-pin function as XTALIN. */
    kSWM_XTALOUT     = SWM_PINENABLE0_XTALOUT_MASK, /*!< Fixed-pin function as XTALOUT. */
    kSWM_ADC_CHN0    = SWM_PINENABLE0_ADC_0_MASK,   /*!< Fixed-pin function as ADC_CHN0. */
    kSWM_ADC_CHN1    = SWM_PINENABLE0_ADC_1_MASK,   /*!< Fixed-pin function as ADC_CHN1. */
    kSWM_ADC_CHN2    = SWM_PINENABLE0_ADC_2_MASK,   /*!< Fixed-pin function as ADC_CHN2. */
    kSWM_ADC_CHN3    = SWM_PINENABLE0_ADC_3_MASK,   /*!< Fixed-pin function as ADC_CHN3. */
    kSWM_ADC_CHN4    = SWM_PINENABLE0_ADC_4_MASK,   /*!< Fixed-pin function as ADC_CHN4. */
    kSWM_ADC_CHN5    = SWM_PINENABLE0_ADC_5_MASK,   /*!< Fixed-pin function as ADC_CHN5. */
    kSWM_ADC_CHN6    = SWM_PINENABLE0_ADC_6_MASK,   /*!< Fixed-pin function as ADC_CHN6. */
    kSWM_ADC_CHN7    = SWM_PINENABLE0_ADC_7_MASK,   /*!< Fixed-pin function as ADC_CHN7. */
    kSWM_ADC_CHN8    = SWM_PINENABLE0_ADC_8_MASK,   /*!< Fixed-pin function as ADC_CHN8. */
    kSWM_ADC_CHN9    = SWM_PINENABLE0_ADC_9_MASK,   /*!< Fixed-pin function as ADC_CHN9. */
    kSWM_ADC_CHN10   = SWM_PINENABLE0_ADC_10_MASK,  /*!< Fixed-pin function as ADC_CHN10. */
    kSWM_ADC_CHN11   = SWM_PINENABLE0_ADC_11_MASK,  /*!< Fixed-pin function as ADC_CHN11. */

    kSWM_FIXEDPIN_NUM_FUNCS = (int)0x80000041U, /*!< Fixed-pin function number. */
} swm_select_fixed_pin_t;

/*! @brief SWM flextimer pin function */
typedef enum _swm_flextimer_pin_func_t
{
    kSWM_FTM0_EXTCLK = 0,  /*!< Flextimer function as FTM0_EXTCLK. */
    kSWM_FTM0_CH0    = 1,  /*!< Flextimer function as FTM0_CH0. */
    kSWM_FTM0_CH1    = 2,  /*!< Flextimer function as FTM0_CH1. */
    kSWM_FTM0_CH2    = 3,  /*!< Flextimer function as FTM0_CH2. */
    kSWM_FTM0_CH3    = 4,  /*!< Flextimer function as FTM0_CH3. */
    kSWM_FTM0_CH4    = 5,  /*!< Flextimer function as FTM0_CH4. */
    kSWM_FTM0_CH5    = 6,  /*!< Flextimer function as FTM0_CH5. */
    kSWM_FTM0_FAULT0 = 7,  /*!< Flextimer function as FTM0_FAULT0. */
    kSWM_FTM0_FAULT1 = 8,  /*!< Flextimer function as FTM0_FAULT1. */
    kSWM_FTM0_FAULT2 = 9,  /*!< Flextimer function as FTM0_FAULT2. */
    kSWM_FTM0_FAULT3 = 10, /*!< Flextimer function as FTM0_FAULT3. */
    kSWM_FTM1_EXTCLK = 11, /*!< Flextimer function as FTM1_EXTCLK. */
    kSWM_FTM1_CH0    = 12, /*!< Flextimer function as FTM1_CH0. */
    kSWM_FTM1_CH1    = 13, /*!< Flextimer function as FTM1_CH1. */
    kSWM_FTM1_CH2    = 14, /*!< Flextimer function as FTM1_CH2. */
    kSWM_FTM1_CH3    = 15, /*!< Flextimer function as FTM1_CH3. */
    kSWM_FTM1_QD_PHA = 16, /*!< Flextimer function as FTM1_QD_PHA. */
    kSWM_FTM1_QD_PHB = 17, /*!< Flextimer function as FTM1_QD_PHB. */

    kSWM_FTM_NUM_FUNCS = 18, /*!< Flextimer function function number. */
} swm_flextimer_pin_func_t;

/*! @brief SWM flextimer pin selection */
typedef enum _swm_select_flextimer_pin_sel_t
{
    kSWM_FTM_Selection0 = 0, /*!< Flextimer pin selection0. */
    kSWM_FTM_Selection1 = 1, /*!< Flextimer pin selection1. */
    kSWM_FTM_Selection2 = 2, /*!< Flextimer pin selection2. */
    kSWM_FTM_Selection3 = 3, /*!< Flextimer pin selection3, which is not connected by default on LPC86x. */
} swm_flextimer_pin_sel_t;

/*@}*/

/*@}*/

#endif /* _FSL_SWM_CONNECTIONS_ */
