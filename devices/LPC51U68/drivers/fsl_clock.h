/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016 - 2019, 2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_CLOCK_H_
#define _FSL_CLOCK_H_

#include "fsl_common.h"

/*! @addtogroup clock */
/*! @{ */

/*! @file */

/*******************************************************************************
 * Definitions
 *****************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief CLOCK driver version 2.4.2. */
#define FSL_CLOCK_DRIVER_VERSION (MAKE_VERSION(2, 4, 2))
/*@}*/

/* Definition for delay API in clock driver, users can redefine it to the real application. */
#ifndef SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY
#define SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY (150000000UL)
#endif

/*!
 * @brief User-defined the size of cache for CLOCK_PllGetConfig() function.
 *
 * Once define this MACRO to be non-zero value, CLOCK_PllGetConfig() function
 * would cache the recent calulation and accelerate the execution to get the
 * right settings.
 */
#ifndef CLOCK_USR_CFG_PLL_CONFIG_CACHE_COUNT
#define CLOCK_USR_CFG_PLL_CONFIG_CACHE_COUNT 2U
#endif

/*! @brief Clock ip name array for FLEXCOMM. */
#define FLEXCOMM_CLOCKS                                                                                             \
    {                                                                                                               \
        kCLOCK_FlexComm0, kCLOCK_FlexComm1, kCLOCK_FlexComm2, kCLOCK_FlexComm3, kCLOCK_FlexComm4, kCLOCK_FlexComm5, \
            kCLOCK_FlexComm6, kCLOCK_FlexComm7                                                                      \
    }
/*! @brief Clock ip name array for LPUART. */
#define LPUART_CLOCKS                                                                                         \
    {                                                                                                         \
        kCLOCK_MinUart0, kCLOCK_MinUart1, kCLOCK_MinUart2, kCLOCK_MinUart3, kCLOCK_MinUart4, kCLOCK_MinUart5, \
            kCLOCK_MinUart6, kCLOCK_MinUart7                                                                  \
    }

/*! @brief Clock ip name array for BI2C. */
#define BI2C_CLOCKS                                                                                                    \
    {                                                                                                                  \
        kCLOCK_BI2c0, kCLOCK_BI2c1, kCLOCK_BI2c2, kCLOCK_BI2c3, kCLOCK_BI2c4, kCLOCK_BI2c5, kCLOCK_BI2c6, kCLOCK_BI2c7 \
    }
/*! @brief Clock ip name array for LSPI. */
#define LPSI_CLOCKS                                                                                                    \
    {                                                                                                                  \
        kCLOCK_LSpi0, kCLOCK_LSpi1, kCLOCK_LSpi2, kCLOCK_LSpi3, kCLOCK_LSpi4, kCLOCK_LSpi5, kCLOCK_LSpi6, kCLOCK_LSpi7 \
    }
/*! @brief Clock ip name array for FLEXI2S. */
#define FLEXI2S_CLOCKS                                                                                        \
    {                                                                                                         \
        kCLOCK_FlexI2s0, kCLOCK_FlexI2s1, kCLOCK_FlexI2s2, kCLOCK_FlexI2s3, kCLOCK_FlexI2s4, kCLOCK_FlexI2s5, \
            kCLOCK_FlexI2s6, kCLOCK_FlexI2s7                                                                  \
    }
/*! @brief Clock ip name array for UTICK. */
#define UTICK_CLOCKS \
    {                \
        kCLOCK_Utick \
    }
/*! @brief Clock ip name array for DMA. */
#define DMA_CLOCKS \
    {              \
        kCLOCK_Dma \
    }
/*! @brief Clock ip name array for CT32B. */
#define CTIMER_CLOCKS                                                    \
    {                                                                    \
        kCLOCK_Ctimer0, kCLOCK_Ctimer1, kCLOCK_IpInvalid, kCLOCK_Ctimer3 \
    }

/*! @brief Clock ip name array for GPIO. */
#define GPIO_CLOCKS                \
    {                              \
        kCLOCK_Gpio0, kCLOCK_Gpio1 \
    }
/*! @brief Clock ip name array for ADC. */
#define ADC_CLOCKS  \
    {               \
        kCLOCK_Adc0 \
    }
/*! @brief Clock ip name array for MRT. */
#define MRT_CLOCKS \
    {              \
        kCLOCK_Mrt \
    }
/*! @brief Clock ip name array for MRT. */
#define SCT_CLOCKS  \
    {               \
        kCLOCK_Sct0 \
    }
/*! @brief Clock ip name array for RTC. */
#define RTC_CLOCKS \
    {              \
        kCLOCK_Rtc \
    }
/*! @brief Clock ip name array for WWDT. */
#define WWDT_CLOCKS \
    {               \
        kCLOCK_Wwdt \
    }
/*! @brief Clock ip name array for CRC. */
#define CRC_CLOCKS \
    {              \
        kCLOCK_Crc \
    }
/*! @brief Clock ip name array for USBD. */
#define USBD_CLOCKS  \
    {                \
        kCLOCK_Usbd0 \
    }

/*! @brief Clock ip name array for GINT. GINT0 & GINT1 share same slot */
#define GINT_CLOCKS              \
    {                            \
        kCLOCK_Gint, kCLOCK_Gint \
    }

/*! @brief Clock gate name used for CLOCK_EnableClock/CLOCK_DisableClock. */
/*------------------------------------------------------------------------------
 clock_ip_name_t definition:
------------------------------------------------------------------------------*/

#define CLK_GATE_REG_OFFSET_SHIFT 8U
#define CLK_GATE_REG_OFFSET_MASK  0xFFFFFF00U
#define CLK_GATE_BIT_SHIFT_SHIFT  0U
#define CLK_GATE_BIT_SHIFT_MASK   0x000000FFU

#define CLK_GATE_DEFINE(reg_offset, bit_shift)                                  \
    ((((reg_offset) << CLK_GATE_REG_OFFSET_SHIFT) & CLK_GATE_REG_OFFSET_MASK) | \
     (((bit_shift) << CLK_GATE_BIT_SHIFT_SHIFT) & CLK_GATE_BIT_SHIFT_MASK))

#define CLK_GATE_ABSTRACT_REG_OFFSET(x) (((uint32_t)(x)&CLK_GATE_REG_OFFSET_MASK) >> CLK_GATE_REG_OFFSET_SHIFT)
#define CLK_GATE_ABSTRACT_BITS_SHIFT(x) (((uint32_t)(x)&CLK_GATE_BIT_SHIFT_MASK) >> CLK_GATE_BIT_SHIFT_SHIFT)

#define AHB_CLK_CTRL0   0
#define AHB_CLK_CTRL1   1
#define ASYNC_CLK_CTRL0 2

/*! @brief Clock gate name used for CLOCK_EnableClock/CLOCK_DisableClock. */
typedef enum _clock_ip_name
{
    kCLOCK_IpInvalid = 0U,                                /*!< Invalid Ip Name. */
    kCLOCK_Rom       = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 1), /*!< Clock gate name: Rom. */

    kCLOCK_Flash = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 7), /*!< Clock gate name: Flash. */

    kCLOCK_Fmc = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 8), /*!< Clock gate name: Fmc. */

    kCLOCK_InputMux = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 11), /*!< Clock gate name: InputMux. */

    kCLOCK_Iocon = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 13), /*!< Clock gate name: Iocon. */

    kCLOCK_Gpio0 = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 14), /*!< Clock gate name: Gpio0. */

    kCLOCK_Gpio1 = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 15), /*!< Clock gate name: Gpio1. */

    kCLOCK_Pint = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 18), /*!< Clock gate name: Pint. */

    kCLOCK_Gint = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 19), /*!< Clock gate name: Gint,
                                                        GPIO_GLOBALINT0 and GPIO_GLOBALINT1 share the same slot  */
    kCLOCK_Dma = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 20),  /*!< Clock gate name: Dma. */

    kCLOCK_Crc = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 21), /*!< Clock gate name: Crc. */

    kCLOCK_Wwdt = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 22), /*!< Clock gate name: Wwdt. */

    kCLOCK_Rtc = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 23), /*!< Clock gate name: Rtc. */

    kCLOCK_Adc0 = CLK_GATE_DEFINE(AHB_CLK_CTRL0, 27), /*!< Clock gate name: Adc0. */

    kCLOCK_Mrt = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 0), /*!< Clock gate name: Mrt. */

    kCLOCK_Sct0 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 2), /*!< Clock gate name: Sct0. */

    kCLOCK_Utick = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 10), /*!< Clock gate name: Utick. */

    kCLOCK_FlexComm0 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 11), /*!< Clock gate name: FlexComm0. */

    kCLOCK_FlexComm1 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 12), /*!< Clock gate name: FlexComm1. */

    kCLOCK_FlexComm2 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 13), /*!< Clock gate name: FlexComm2. */

    kCLOCK_FlexComm3 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 14), /*!< Clock gate name: FlexComm3. */

    kCLOCK_FlexComm4 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 15), /*!< Clock gate name: FlexComm4. */

    kCLOCK_FlexComm5 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 16), /*!< Clock gate name: FlexComm5. */

    kCLOCK_FlexComm6 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 17), /*!< Clock gate name: FlexComm6. */

    kCLOCK_FlexComm7 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 18), /*!< Clock gate name: FlexComm7. */

    kCLOCK_MinUart0 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 11), /*!< Clock gate name: MinUart0. */

    kCLOCK_MinUart1 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 12), /*!< Clock gate name: MinUart1. */

    kCLOCK_MinUart2 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 13), /*!< Clock gate name: MinUart2. */

    kCLOCK_MinUart3 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 14), /*!< Clock gate name: MinUart3. */

    kCLOCK_MinUart4 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 15), /*!< Clock gate name: MinUart4. */

    kCLOCK_MinUart5 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 16), /*!< Clock gate name: MinUart5. */

    kCLOCK_MinUart6 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 17), /*!< Clock gate name: MinUart6. */

    kCLOCK_MinUart7 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 18), /*!< Clock gate name: MinUart7. */

    kCLOCK_LSpi0 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 11), /*!< Clock gate name: LSpi0. */

    kCLOCK_LSpi1 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 12), /*!< Clock gate name: LSpi1. */

    kCLOCK_LSpi2 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 13), /*!< Clock gate name: LSpi2. */

    kCLOCK_LSpi3 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 14), /*!< Clock gate name: LSpi3. */

    kCLOCK_LSpi4 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 15), /*!< Clock gate name: LSpi4. */

    kCLOCK_LSpi5 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 16), /*!< Clock gate name: LSpi5. */

    kCLOCK_LSpi6 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 17), /*!< Clock gate name: LSpi6. */

    kCLOCK_LSpi7 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 18), /*!< Clock gate name: LSpi7. */

    kCLOCK_BI2c0 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 11), /*!< Clock gate name: BI2c0. */

    kCLOCK_BI2c1 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 12), /*!< Clock gate name: BI2c1. */

    kCLOCK_BI2c2 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 13), /*!< Clock gate name: BI2c2. */

    kCLOCK_BI2c3 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 14), /*!< Clock gate name: BI2c3. */

    kCLOCK_BI2c4 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 15), /*!< Clock gate name: BI2c4. */

    kCLOCK_BI2c5 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 16), /*!< Clock gate name: BI2c5. */

    kCLOCK_BI2c6 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 17), /*!< Clock gate name: BI2c6. */

    kCLOCK_BI2c7 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 18), /*!< Clock gate name: BI2c7. */

    kCLOCK_FlexI2s0 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 11), /*!< Clock gate name: FlexI2s0. */

    kCLOCK_FlexI2s1 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 12), /*!< Clock gate name: FlexI2s1. */

    kCLOCK_FlexI2s2 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 13), /*!< Clock gate name: FlexI2s2. */

    kCLOCK_FlexI2s3 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 14), /*!< Clock gate name: FlexI2s3. */

    kCLOCK_FlexI2s4 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 15), /*!< Clock gate name: FlexI2s4. */

    kCLOCK_FlexI2s5 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 16), /*!< Clock gate name: FlexI2s5. */

    kCLOCK_FlexI2s6 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 17), /*!< Clock gate name: FlexI2s6. */

    kCLOCK_FlexI2s7 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 18), /*!< Clock gate name: FlexI2s7. */

    kCLOCK_Ct32b2 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 22), /*!< Clock gate name: Ct32b2. */

    kCLOCK_Usbd0 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 25), /*!< Clock gate name: Usbd0. */

    kCLOCK_Ctimer0 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 26), /*!< Clock gate name: Ctimer0. */

    kCLOCK_Ctimer1 = CLK_GATE_DEFINE(AHB_CLK_CTRL1, 27), /*!< Clock gate name: Ctimer1. */

    kCLOCK_Ctimer3 = CLK_GATE_DEFINE(ASYNC_CLK_CTRL0, 13), /*!< Clock gate name: Ctimer3. */

} clock_ip_name_t;

/*! @brief Clock name used to get clock frequency. */
typedef enum _clock_name
{
    kCLOCK_CoreSysClk,  /*!< Core/system clock  (aka MAIN_CLK)                       */
    kCLOCK_BusClk,      /*!< Bus clock (AHB clock)                                   */
    kCLOCK_ClockOut,    /*!< CLOCKOUT                                                */
    kCLOCK_FroHf,       /*!< FRO48/96                                                */
    kCLOCK_Fro12M,      /*!< FRO12M                                                  */
    kCLOCK_ExtClk,      /*!< External Clock                                          */
    kCLOCK_PllOut,      /*!< PLL Output                                              */
    kCLOCK_WdtOsc,      /*!< Watchdog Oscillator                                     */
    kCLOCK_Frg,         /*!< Frg Clock                                               */
    kCLOCK_AsyncApbClk, /*!< Async APB clock										 */
    kCLOCK_FlexI2S,     /*!< FlexI2S clock                                           */
} clock_name_t;

/**
 * @brief Clock source selections for the asynchronous APB clock.
 */
typedef enum _async_clock_src
{
    kCLOCK_AsyncMainClk = 0, /*!< Main System clock */
    kCLOCK_AsyncFro12Mhz,    /*!< 12MHz FRO */
} async_clock_src_t;

/*! @brief Clock Mux Switches
 *  The encoding is as follows each connection identified is 32bits wide while 24bits are valuable
 *  starting from LSB upwards
 *
 *  [4 bits for choice, 0 means invalid choice] [8 bits mux ID]*
 *
 */

#define CLK_ATTACH_ID(mux, sel, pos) ((((uint32_t)(mux) << 0U) | (((uint32_t)(sel) + 1U) & 0xFU) << 8U) << ((pos)*12U))
#define MUX_A(mux, sel)              CLK_ATTACH_ID((mux), (sel), 0U)
#define MUX_B(mux, sel, selector)    (CLK_ATTACH_ID((mux), (sel), 1U) | ((selector) << 24U))

#define GET_ID_ITEM(connection)      ((connection)&0xFFFU)
#define GET_ID_NEXT_ITEM(connection) ((connection) >> 12U)
#define GET_ID_ITEM_MUX(connection)  ((uint8_t)((connection)&0xFFU))
#define GET_ID_ITEM_SEL(connection)  ((uint8_t)(((connection)&0xF00U) >> 8U) - 1U)
#define GET_ID_SELECTOR(connection)  ((connection)&0xF000000U)

#define CM_MAINCLKSELA      0
#define CM_MAINCLKSELB      1
#define CM_CLKOUTCLKSELA    2
#define CM_CLKOUTCLKSELB    3
#define CM_SYSPLLCLKSEL     4
#define CM_USBPLLCLKSEL     5
#define CM_AUDPLLCLKSEL     6
#define CM_SCTPLLCLKSEL     7
#define CM_ADCASYNCCLKSEL   9
#define CM_USBCLKSEL        10
#define CM_USB1CLKSEL       11
#define CM_FXCOMCLKSEL0     12
#define CM_FXCOMCLKSEL1     13
#define CM_FXCOMCLKSEL2     14
#define CM_FXCOMCLKSEL3     15
#define CM_FXCOMCLKSEL4     16
#define CM_FXCOMCLKSEL5     17
#define CM_FXCOMCLKSEL6     18
#define CM_FXCOMCLKSEL7     19
#define CM_FXCOMCLKSEL8     20
#define CM_FXCOMCLKSEL9     21
#define CM_FXCOMCLKSEL10    22
#define CM_FXCOMCLKSEL11    23
#define CM_FXI2S0MCLKCLKSEL 24
#define CM_FXI2S1MCLKCLKSEL 25
#define CM_FRGCLKSEL        26

#define CM_ASYNCAPB 28U

/*!
 * @brief The enumerator of clock attach Id.
 */
typedef enum _clock_attach_id
{

    kFRO12M_to_MAIN_CLK = MUX_A(CM_MAINCLKSELA, 0) | MUX_B(CM_MAINCLKSELB, 0, 0), /*!< Attach FRO12M to MAIN_CLK. */

    kEXT_CLK_to_MAIN_CLK = MUX_A(CM_MAINCLKSELA, 1) | MUX_B(CM_MAINCLKSELB, 0, 0), /*!< Attach EXT_CLK to MAIN_CLK. */

    kWDT_OSC_to_MAIN_CLK = MUX_A(CM_MAINCLKSELA, 2) | MUX_B(CM_MAINCLKSELB, 0, 0), /*!< Attach WDT_OSC to MAIN_CLK. */

    kFRO_HF_to_MAIN_CLK = MUX_A(CM_MAINCLKSELA, 3) | MUX_B(CM_MAINCLKSELB, 0, 0), /*!< Attach FRO_HF to MAIN_CLK. */

    kSYS_PLL_to_MAIN_CLK = MUX_A(CM_MAINCLKSELA, 0) | MUX_B(CM_MAINCLKSELB, 2, 0), /*!< Attach SYS_PLL to MAIN_CLK. */

    kOSC32K_to_MAIN_CLK = MUX_A(CM_MAINCLKSELA, 0) | MUX_B(CM_MAINCLKSELB, 3, 0), /*!< Attach OSC32K to MAIN_CLK. */

    kFRO12M_to_SYS_PLL = MUX_A(CM_SYSPLLCLKSEL, 0), /*!< Attach FRO12M to SYS_PLL. */

    kEXT_CLK_to_SYS_PLL = MUX_A(CM_SYSPLLCLKSEL, 1), /*!< Attach EXT_CLK to SYS_PLL. */

    kWDT_OSC_to_SYS_PLL = MUX_A(CM_SYSPLLCLKSEL, 2), /*!< Attach WDT_OSC to SYS_PLL. */

    kOSC32K_to_SYS_PLL = MUX_A(CM_SYSPLLCLKSEL, 3), /*!< Attach OSC32K to SYS_PLL. */

    kNONE_to_SYS_PLL = MUX_A(CM_SYSPLLCLKSEL, 7), /*!< Attach NONE to SYS_PLL. */

    kMAIN_CLK_to_ASYNC_APB = MUX_A(CM_ASYNCAPB, 0), /*!< Attach MAIN_CLK to ASYNC_APB. */

    kFRO12M_to_ASYNC_APB = MUX_A(CM_ASYNCAPB, 1), /*!< Attach FRO12M to ASYNC_APB. */

    kMAIN_CLK_to_ADC_CLK = MUX_A(CM_ADCASYNCCLKSEL, 0), /*!< Attach MAIN_CLK to ADC_CLK. */

    kSYS_PLL_to_ADC_CLK = MUX_A(CM_ADCASYNCCLKSEL, 1), /*!< Attach SYS_PLL to ADC_CLK. */

    kFRO_HF_to_ADC_CLK = MUX_A(CM_ADCASYNCCLKSEL, 2), /*!< Attach FRO_HF to ADC_CLK. */

    kNONE_to_ADC_CLK = MUX_A(CM_ADCASYNCCLKSEL, 7), /*!< Attach NONE to ADC_CLK. */

    kFRO12M_to_FLEXCOMM0 = MUX_A(CM_FXCOMCLKSEL0, 0), /*!< Attach FRO12M to FLEXCOMM0. */

    kFRO_HF_to_FLEXCOMM0 = MUX_A(CM_FXCOMCLKSEL0, 1), /*!< Attach FRO_HF to FLEXCOMM0. */

    kSYS_PLL_to_FLEXCOMM0 = MUX_A(CM_FXCOMCLKSEL0, 2), /*!< Attach SYS_PLL to FLEXCOMM0. */

    kMCLK_to_FLEXCOMM0 = MUX_A(CM_FXCOMCLKSEL0, 3), /*!< Attach MCLK to FLEXCOMM0. */

    kFRG_to_FLEXCOMM0 = MUX_A(CM_FXCOMCLKSEL0, 4), /*!< Attach FRG to FLEXCOMM0. */

    kNONE_to_FLEXCOMM0 = MUX_A(CM_FXCOMCLKSEL0, 7), /*!< Attach NONE to FLEXCOMM0. */

    kFRO12M_to_FLEXCOMM1 = MUX_A(CM_FXCOMCLKSEL1, 0), /*!< Attach FRO12M to FLEXCOMM1. */

    kFRO_HF_to_FLEXCOMM1 = MUX_A(CM_FXCOMCLKSEL1, 1), /*!< Attach FRO_HF to FLEXCOMM1. */

    kSYS_PLL_to_FLEXCOMM1 = MUX_A(CM_FXCOMCLKSEL1, 2), /*!< Attach SYS_PLL to FLEXCOMM1. */

    kMCLK_to_FLEXCOMM1 = MUX_A(CM_FXCOMCLKSEL1, 3), /*!< Attach MCLK to FLEXCOMM1. */

    kFRG_to_FLEXCOMM1 = MUX_A(CM_FXCOMCLKSEL1, 4), /*!< Attach FRG to FLEXCOMM1. */

    kNONE_to_FLEXCOMM1 = MUX_A(CM_FXCOMCLKSEL1, 7), /*!< Attach NONE to FLEXCOMM1. */

    kFRO12M_to_FLEXCOMM2 = MUX_A(CM_FXCOMCLKSEL2, 0), /*!< Attach FRO12M to FLEXCOMM2. */

    kFRO_HF_to_FLEXCOMM2 = MUX_A(CM_FXCOMCLKSEL2, 1), /*!< Attach FRO_HF to FLEXCOMM2. */

    kSYS_PLL_to_FLEXCOMM2 = MUX_A(CM_FXCOMCLKSEL2, 2), /*!< Attach SYS_PLL to FLEXCOMM2. */

    kMCLK_to_FLEXCOMM2 = MUX_A(CM_FXCOMCLKSEL2, 3), /*!< Attach MCLK to FLEXCOMM2. */

    kFRG_to_FLEXCOMM2 = MUX_A(CM_FXCOMCLKSEL2, 4), /*!< Attach FRG to FLEXCOMM2. */

    kNONE_to_FLEXCOMM2 = MUX_A(CM_FXCOMCLKSEL2, 7), /*!< Attach NONE to FLEXCOMM2. */

    kFRO12M_to_FLEXCOMM3 = MUX_A(CM_FXCOMCLKSEL3, 0), /*!< Attach FRO12M to FLEXCOMM3. */

    kFRO_HF_to_FLEXCOMM3 = MUX_A(CM_FXCOMCLKSEL3, 1), /*!< Attach FRO_HF to FLEXCOMM3. */

    kSYS_PLL_to_FLEXCOMM3 = MUX_A(CM_FXCOMCLKSEL3, 2), /*!< Attach SYS_PLL to FLEXCOMM3. */

    kMCLK_to_FLEXCOMM3 = MUX_A(CM_FXCOMCLKSEL3, 3), /*!< Attach MCLK to FLEXCOMM3. */

    kFRG_to_FLEXCOMM3 = MUX_A(CM_FXCOMCLKSEL3, 4), /*!< Attach FRG to FLEXCOMM3. */

    kNONE_to_FLEXCOMM3 = MUX_A(CM_FXCOMCLKSEL3, 7), /*!< Attach NONE to FLEXCOMM3. */

    kFRO12M_to_FLEXCOMM4 = MUX_A(CM_FXCOMCLKSEL4, 0), /*!< Attach FRO12M to FLEXCOMM4. */

    kFRO_HF_to_FLEXCOMM4 = MUX_A(CM_FXCOMCLKSEL4, 1), /*!< Attach FRO_HF to FLEXCOMM4. */

    kSYS_PLL_to_FLEXCOMM4 = MUX_A(CM_FXCOMCLKSEL4, 2), /*!< Attach SYS_PLL to FLEXCOMM4. */

    kMCLK_to_FLEXCOMM4 = MUX_A(CM_FXCOMCLKSEL4, 3), /*!< Attach MCLK to FLEXCOMM4. */

    kFRG_to_FLEXCOMM4 = MUX_A(CM_FXCOMCLKSEL4, 4), /*!< Attach FRG to FLEXCOMM4. */

    kNONE_to_FLEXCOMM4 = MUX_A(CM_FXCOMCLKSEL4, 7), /*!< Attach NONE to FLEXCOMM4. */

    kFRO12M_to_FLEXCOMM5 = MUX_A(CM_FXCOMCLKSEL5, 0), /*!< Attach FRO12M to FLEXCOMM5. */

    kFRO_HF_to_FLEXCOMM5 = MUX_A(CM_FXCOMCLKSEL5, 1), /*!< Attach FRO_HF to FLEXCOMM5. */

    kSYS_PLL_to_FLEXCOMM5 = MUX_A(CM_FXCOMCLKSEL5, 2), /*!< Attach SYS_PLL to FLEXCOMM5. */

    kMCLK_to_FLEXCOMM5 = MUX_A(CM_FXCOMCLKSEL5, 3), /*!< Attach MCLK to FLEXCOMM5. */

    kFRG_to_FLEXCOMM5 = MUX_A(CM_FXCOMCLKSEL5, 4), /*!< Attach FRG to FLEXCOMM5. */

    kNONE_to_FLEXCOMM5 = MUX_A(CM_FXCOMCLKSEL5, 7), /*!< Attach NONE to FLEXCOMM5. */

    kFRO12M_to_FLEXCOMM6 = MUX_A(CM_FXCOMCLKSEL6, 0), /*!< Attach FRO12M to FLEXCOMM6. */

    kFRO_HF_to_FLEXCOMM6 = MUX_A(CM_FXCOMCLKSEL6, 1), /*!< Attach FRO_HF to FLEXCOMM6. */

    kSYS_PLL_to_FLEXCOMM6 = MUX_A(CM_FXCOMCLKSEL6, 2), /*!< Attach SYS_PLL to FLEXCOMM6. */

    kMCLK_to_FLEXCOMM6 = MUX_A(CM_FXCOMCLKSEL6, 3), /*!< Attach MCLK to FLEXCOMM6. */

    kFRG_to_FLEXCOMM6 = MUX_A(CM_FXCOMCLKSEL6, 4), /*!< Attach FRG to FLEXCOMM6. */

    kNONE_to_FLEXCOMM6 = MUX_A(CM_FXCOMCLKSEL6, 7), /*!< Attach NONE to FLEXCOMM6. */

    kFRO12M_to_FLEXCOMM7 = MUX_A(CM_FXCOMCLKSEL7, 0), /*!< Attach FRO12M to FLEXCOMM7. */

    kFRO_HF_to_FLEXCOMM7 = MUX_A(CM_FXCOMCLKSEL7, 1), /*!< Attach FRO_HF to FLEXCOMM7. */

    kSYS_PLL_to_FLEXCOMM7 = MUX_A(CM_FXCOMCLKSEL7, 2), /*!< Attach SYS_PLL to FLEXCOMM7. */

    kMCLK_to_FLEXCOMM7 = MUX_A(CM_FXCOMCLKSEL7, 3), /*!< Attach MCLK to FLEXCOMM7. */

    kFRG_to_FLEXCOMM7 = MUX_A(CM_FXCOMCLKSEL7, 4), /*!< Attach FRG to FLEXCOMM7. */

    kNONE_to_FLEXCOMM7 = MUX_A(CM_FXCOMCLKSEL7, 7), /*!< Attach NONE to FLEXCOMM7. */

    kMAIN_CLK_to_FRG = MUX_A(CM_FRGCLKSEL, 0), /*!< Attach MAIN_CLK to FRG. */

    kSYS_PLL_to_FRG = MUX_A(CM_FRGCLKSEL, 1), /*!< Attach SYS_PLL to FRG. */

    kFRO12M_to_FRG = MUX_A(CM_FRGCLKSEL, 2), /*!< Attach FRO12M to FRG. */

    kFRO_HF_to_FRG = MUX_A(CM_FRGCLKSEL, 3), /*!< Attach FRO_HF to FRG. */

    kNONE_to_FRG = MUX_A(CM_FRGCLKSEL, 7), /*!< Attach NONE to FRG. */

    kFRO_HF_to_MCLK = MUX_A(CM_FXI2S0MCLKCLKSEL, 0), /*!< Attach FRO_HF to MCLK. */

    kSYS_PLL_to_MCLK = MUX_A(CM_FXI2S0MCLKCLKSEL, 1), /*!< Attach SYS_PLL to MCLK. */

    kMAIN_CLK_to_MCLK = MUX_A(CM_FXI2S0MCLKCLKSEL, 2), /*!< Attach MAIN_CLK to MCLK. */

    kNONE_to_MCLK = MUX_A(CM_FXI2S0MCLKCLKSEL, 7), /*!< Attach NONE to MCLK. */

    kFRO_HF_to_USB_CLK = MUX_A(CM_USBCLKSEL, 0), /*!< Attach FRO_HF to USB_CLK. */

    kSYS_PLL_to_USB_CLK = MUX_A(CM_USBCLKSEL, 1), /*!< Attach SYS_PLL to USB_CLK. */

    kMAIN_CLK_to_USB_CLK = MUX_A(CM_USBCLKSEL, 2), /*!< Attach MAIN_CLK to USB_CLK. */

    kNONE_to_USB_CLK = MUX_A(CM_USBCLKSEL, 7), /*!< Attach NONE to USB_CLK. */

    kMAIN_CLK_to_CLKOUT = MUX_A(CM_CLKOUTCLKSELA, 0), /*!< Attach MAIN_CLK to CLKOUT. */

    kEXT_CLK_to_CLKOUT = MUX_A(CM_CLKOUTCLKSELA, 1), /*!< Attach EXT_CLK to CLKOUT. */

    kWDT_OSC_to_CLKOUT = MUX_A(CM_CLKOUTCLKSELA, 2), /*!< Attach WDT_OSC to CLKOUT. */

    kFRO_HF_to_CLKOUT = MUX_A(CM_CLKOUTCLKSELA, 3), /*!< Attach FRO_HF to CLKOUT. */

    kSYS_PLL_to_CLKOUT = MUX_A(CM_CLKOUTCLKSELA, 4), /*!< Attach SYS_PLL to CLKOUT. */

    kFRO12M_to_CLKOUT = MUX_A(CM_CLKOUTCLKSELA, 5), /*!< Attach FRO12M to CLKOUT. */

    kOSC32K_to_CLKOUT = MUX_A(CM_CLKOUTCLKSELA, 6), /*!< Attach OSC32K to CLKOUT. */

    kNONE_to_CLKOUT = MUX_A(CM_CLKOUTCLKSELA, 7), /*!< Attach NONE to CLKOUT. */

    kNONE_to_NONE = (int)0x80000000U, /*!< Attach NONE to NONE. */

} clock_attach_id_t;

/*! @brief Clock dividers. */
typedef enum _clock_div_name
{
    kCLOCK_DivSystickClk  = 0,  /*!< Systick clock divider. */
    kCLOCK_DivTraceClk    = 1,  /*!< Trace clock divider. */
    kCLOCK_DivAhbClk      = 32, /*!< Ahb clock divider. */
    kCLOCK_DivClkOut      = 33, /*!< Clock out divider. */
    kCLOCK_DivAdcAsyncClk = 37, /*!< Adc Async clock divider. */
    kCLOCK_DivUsbClk      = 38, /*!< Usb clock divier. */
    kCLOCK_DivFrg         = 40, /*!< Frg clock divider. */
    kCLOCK_DivFxI2s0MClk  = 43  /*!< FxI2S0 clock divider. */
} clock_div_name_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

static inline void CLOCK_EnableClock(clock_ip_name_t clk)
{
    uint32_t index = CLK_GATE_ABSTRACT_REG_OFFSET(clk);
    if (index < 2UL)
    {
        SYSCON->AHBCLKCTRLSET[index] = (1UL << CLK_GATE_ABSTRACT_BITS_SHIFT(clk));
    }
    else
    {
        ASYNC_SYSCON->ASYNCAPBCLKCTRLSET = (1UL << CLK_GATE_ABSTRACT_BITS_SHIFT(clk));
    }
}

static inline void CLOCK_DisableClock(clock_ip_name_t clk)
{
    uint32_t index = CLK_GATE_ABSTRACT_REG_OFFSET(clk);
    if (index < 2UL)
    {
        SYSCON->AHBCLKCTRLCLR[index] = (1UL << CLK_GATE_ABSTRACT_BITS_SHIFT(clk));
    }
    else
    {
        ASYNC_SYSCON->ASYNCAPBCLKCTRLCLR = (1UL << CLK_GATE_ABSTRACT_BITS_SHIFT(clk));
    }
}
/**
 * @brief FLASH Access time definitions
 */
typedef enum _clock_flashtim
{
    kCLOCK_Flash1Cycle = 0, /*!< Flash accesses use 1 CPU clock */
    kCLOCK_Flash2Cycle,     /*!< Flash accesses use 2 CPU clocks */
    kCLOCK_Flash3Cycle,     /*!< Flash accesses use 3 CPU clocks */
    kCLOCK_Flash4Cycle,     /*!< Flash accesses use 4 CPU clocks */
    kCLOCK_Flash5Cycle,     /*!< Flash accesses use 5 CPU clocks */
    kCLOCK_Flash6Cycle,     /*!< Flash accesses use 6 CPU clocks */
    kCLOCK_Flash7Cycle,     /*!< Flash accesses use 7 CPU clocks */
} clock_flashtim_t;

/**
 * @brief	Set FLASH memory access time in clocks
 * @param	clks	: Clock cycles for FLASH access
 * @return	Nothing
 */
static inline void CLOCK_SetFLASHAccessCycles(clock_flashtim_t clks)
{
    uint32_t tmp;

    tmp = SYSCON->FLASHCFG & ~(SYSCON_FLASHCFG_FLASHTIM_MASK);

    /* Don't alter lower bits */
    SYSCON->FLASHCFG = tmp | ((uint32_t)clks << SYSCON_FLASHCFG_FLASHTIM_SHIFT);
}

/**
 * @brief	Initialize the Core clock to given frequency (12, 48 or 96 MHz).
 * Turns on FRO and uses default CCO, if freq is 12000000, then high speed output is off, else high speed output is
 * enabled.
 * @param	iFreq	: Desired frequency (must be one of CLK_FRO_12MHZ or CLK_FRO_48MHZ or CLK_FRO_96MHZ)
 * @return	returns success or fail status.
 */
status_t CLOCK_SetupFROClocking(uint32_t iFreq);
/**
 * @brief	Configure the clock selection muxes.
 * @param	connection	: Clock to be configured.
 * @return	Nothing
 */
void CLOCK_AttachClk(clock_attach_id_t connection);
/**
 * @brief   Get the actual clock attach id.
 * This fuction uses the offset in input attach id, then it reads the actual source value in
 * the register and combine the offset to obtain an actual attach id.
 * @param   attachId  : Clock attach id to get.
 * @return  Clock source value.
 */
clock_attach_id_t CLOCK_GetClockAttachId(clock_attach_id_t attachId);
/**
 * @brief	Setup peripheral clock dividers.
 * @param	div_name	: Clock divider name
 * @param divided_by_value: Value to be divided
 * @param reset :  Whether to reset the divider counter.
 * @return	Nothing
 */
void CLOCK_SetClkDiv(clock_div_name_t div_name, uint32_t divided_by_value, bool reset);
/**
 * @brief	Set the flash wait states for the input freuqency.
 * @param	iFreq	: Input frequency
 * @return	Nothing
 */
void CLOCK_SetFLASHAccessCyclesForFreq(uint32_t iFreq);
/*! @brief	Return Frequency of selected clock
 *  @return	Frequency of selected clock
 */
uint32_t CLOCK_GetFreq(clock_name_t clockName);

/*! @brief	Return Input frequency for the Fractional baud rate generator
 *  @return	Input Frequency for FRG
 */
uint32_t CLOCK_GetFRGInputClock(void);

/*! @brief	Set output of the Fractional baud rate generator
 * @param	freq	: Desired output frequency
 * @return	Error Code 0 - fail 1 - success
 */
uint32_t CLOCK_SetFRGClock(uint32_t freq);

/*! @brief	Return Frequency of FRO 12MHz
 *  @return	Frequency of FRO 12MHz
 */
uint32_t CLOCK_GetFro12MFreq(void);
/*! @brief	Return Frequency of External Clock
 *  @return	Frequency of External Clock. If no external clock is used returns 0.
 */
uint32_t CLOCK_GetExtClkFreq(void);
/*! @brief	Return Frequency of Watchdog Oscillator
 *  @return	Frequency of Watchdog Oscillator
 */
uint32_t CLOCK_GetWdtOscFreq(void);
/*! @brief	Return Frequency of High-Freq output of FRO
 *  @return	Frequency of High-Freq output of FRO
 */
uint32_t CLOCK_GetFroHfFreq(void);
/*! @brief	Return Frequency of PLL
 *  @return	Frequency of PLL
 */
uint32_t CLOCK_GetPllOutFreq(void);
/*! @brief	Return Frequency of 32kHz osc
 *  @return	Frequency of 32kHz osc
 */
uint32_t CLOCK_GetOsc32KFreq(void);
/*! @brief	Return Frequency of Core System
 *  @return	Frequency of Core System
 */
uint32_t CLOCK_GetCoreSysClkFreq(void);
/*! @brief	Return Frequency of I2S MCLK Clock
 *  @return	Frequency of I2S MCLK Clock
 */
uint32_t CLOCK_GetI2SMClkFreq(void);
/*! @brief	Return Frequency of Flexcomm functional Clock
 *  @return	Frequency of Flexcomm functional Clock
 */
uint32_t CLOCK_GetFlexCommClkFreq(uint32_t id);
/*! brief	Return Frequency of Usb Clock
 *  return	Frequency of Usb Clock.
 */
uint32_t CLOCK_GetUsbClkFreq(void);
/*! @brief	Return Frequency of Adc Clock
 *  @return	Frequency of Adc Clock.
 */
uint32_t CLOCK_GetAdcClkFreq(void);
/*! @brief	Return Frequency of ClockOut
 *  @return	Frequency of ClockOut
 */
uint32_t CLOCK_GetClockOutClkFreq(void);
/*! @brief	Return Asynchronous APB Clock source
 *  @return	Asynchronous APB CLock source
 */
__STATIC_INLINE async_clock_src_t CLOCK_GetAsyncApbClkSrc(void)
{
    return (async_clock_src_t)(uint32_t)(ASYNC_SYSCON->ASYNCAPBCLKSELA & 0x3UL);
}
/*! @brief	Return Frequency of Asynchronous APB Clock
 *  @return	Frequency of Asynchronous APB Clock Clock
 */
uint32_t CLOCK_GetAsyncApbClkFreq(void);
/*! @brief	Return System PLL input clock rate
 *  @return	System PLL input clock rate
 */
uint32_t CLOCK_GetSystemPLLInClockRate(void);

/*! @brief	Return System PLL output clock rate
 *  @param	recompute	: Forces a PLL rate recomputation if true
 *  @return	System PLL output clock rate
 *  @note	The PLL rate is cached in the driver in a variable as
 *  the rate computation function can take some time to perform. It
 *  is recommended to use 'false' with the 'recompute' parameter.
 */
uint32_t CLOCK_GetSystemPLLOutClockRate(bool recompute);

/*! @brief	Enables and disables PLL bypass mode
 *  @brief	bypass	: true to bypass PLL (PLL output = PLL input, false to disable bypass
 *  @return	System PLL output clock rate
 */
__STATIC_INLINE void CLOCK_SetBypassPLL(bool bypass)
{
    if (bypass)
    {
        SYSCON->SYSPLLCTRL |= (1UL << SYSCON_SYSPLLCTRL_BYPASS_SHIFT);
    }
    else
    {
        SYSCON->SYSPLLCTRL &= ~(1UL << SYSCON_SYSPLLCTRL_BYPASS_SHIFT);
    }
}

/*! @brief	Check if PLL is locked or not
 *  @return	true if the PLL is locked, false if not locked
 */
__STATIC_INLINE bool CLOCK_IsSystemPLLLocked(void)
{
    return (bool)((SYSCON->SYSPLLSTAT & SYSCON_SYSPLLSTAT_LOCK_MASK) != 0UL);
}

/*! @brief Store the current PLL rate
 *  @param	rate: Current rate of the PLL
 *  @return	Nothing
 **/
void CLOCK_SetStoredPLLClockRate(uint32_t rate);

/*! @brief PLL configuration structure flags for 'flags' field
 * These flags control how the PLL configuration function sets up the PLL setup structure.<br>
 *
 * When the PLL_CONFIGFLAG_USEINRATE flag is selected, the 'InputRate' field in the
 * configuration structure must be assigned with the expected PLL frequency. If the
 * PLL_CONFIGFLAG_USEINRATE is not used, 'InputRate' is ignored in the configuration
 * function and the driver will determine the PLL rate from the currently selected
 * PLL source. This flag might be used to configure the PLL input clock more accurately
 * when using the WDT oscillator or a more dyanmic CLKIN source.<br>
 *
 * When the PLL_CONFIGFLAG_FORCENOFRACT flag is selected, the PLL hardware for the
 * automatic bandwidth selection, Spread Spectrum (SS) support, and fractional M-divider
 * are not used.<br>
 */
#define PLL_CONFIGFLAG_USEINRATE (1U << 0U) /*!< Flag to use InputRate in PLL configuration structure for setup */
#define PLL_CONFIGFLAG_FORCENOFRACT                                                                                   \
    (1U << 2U) /*!< Force non-fractional output mode, PLL output will not use the fractional, automatic bandwidth, or \
                  SS hardware */

/*! @brief PLL Spread Spectrum (SS) Programmable modulation frequency
 * See (MF) field in the SYSPLLSSCTRL1 register in the UM.
 */
typedef enum _ss_progmodfm
{
    kSS_MF_512 = (0 << 20), /*!< Nss = 512 (fm ? 3.9 - 7.8 kHz) */
    kSS_MF_384 = (1 << 20), /*!< Nss ?= 384 (fm ? 5.2 - 10.4 kHz) */
    kSS_MF_256 = (2 << 20), /*!< Nss = 256 (fm ? 7.8 - 15.6 kHz) */
    kSS_MF_128 = (3 << 20), /*!< Nss = 128 (fm ? 15.6 - 31.3 kHz) */
    kSS_MF_64  = (4 << 20), /*!< Nss = 64 (fm ? 32.3 - 64.5 kHz) */
    kSS_MF_32  = (5 << 20), /*!< Nss = 32 (fm ? 62.5- 125 kHz) */
    kSS_MF_24  = (6 << 20), /*!< Nss ?= 24 (fm ? 83.3- 166.6 kHz) */
    kSS_MF_16  = (7 << 20)  /*!< Nss = 16 (fm ? 125- 250 kHz) */
} ss_progmodfm_t;

/*! @brief PLL Spread Spectrum (SS) Programmable frequency modulation depth
 * See (MR) field in the SYSPLLSSCTRL1 register in the UM.
 */
typedef enum _ss_progmoddp
{
    kSS_MR_K0   = (0 << 23), /*!< k = 0 (no spread spectrum) */
    kSS_MR_K1   = (1 << 23), /*!< k = 1 */
    kSS_MR_K1_5 = (2 << 23), /*!< k = 1.5 */
    kSS_MR_K2   = (3 << 23), /*!< k = 2 */
    kSS_MR_K3   = (4 << 23), /*!< k = 3 */
    kSS_MR_K4   = (5 << 23), /*!< k = 4 */
    kSS_MR_K6   = (6 << 23), /*!< k = 6 */
    kSS_MR_K8   = (7 << 23)  /*!< k = 8 */
} ss_progmoddp_t;

/*! @brief PLL Spread Spectrum (SS) Modulation waveform control
 * See (MC) field in the SYSPLLSSCTRL1 register in the UM.<br>
 * Compensation for low pass filtering of the PLL to get a triangular
 * modulation at the output of the PLL, giving a flat frequency spectrum.
 */
typedef enum _ss_modwvctrl
{
    kSS_MC_NOC  = (0 << 26), /*!< no compensation */
    kSS_MC_RECC = (2 << 26), /*!< recommended setting */
    kSS_MC_MAXC = (3 << 26), /*!< max. compensation */
} ss_modwvctrl_t;

/*! @brief PLL configuration structure
 *
 * This structure can be used to configure the settings for a PLL
 * setup structure. Fill in the desired configuration for the PLL
 * and call the PLL setup function to fill in a PLL setup structure.
 */
typedef struct _pll_config
{
    uint32_t desiredRate; /*!< Desired PLL rate in Hz */
    uint32_t inputRate;   /*!< PLL input clock in Hz, only used if PLL_CONFIGFLAG_USEINRATE flag is set */
    uint32_t flags;       /*!< PLL configuration flags, Or'ed value of PLL_CONFIGFLAG_* definitions */
    ss_progmodfm_t ss_mf; /*!< SS Programmable modulation frequency, only applicable when not using
                             PLL_CONFIGFLAG_FORCENOFRACT flag */
    ss_progmoddp_t ss_mr; /*!< SS Programmable frequency modulation depth, only applicable when not using
                             PLL_CONFIGFLAG_FORCENOFRACT flag */
    ss_modwvctrl_t
        ss_mc; /*!< SS Modulation waveform control, only applicable when not using PLL_CONFIGFLAG_FORCENOFRACT flag */
    bool mfDither; /*!< false for fixed modulation frequency or true for dithering, only applicable when not using
                      PLL_CONFIGFLAG_FORCENOFRACT flag */

} pll_config_t;

/*! @brief PLL setup structure flags for 'flags' field
 * These flags control how the PLL setup function sets up the PLL
 */
#define PLL_SETUPFLAG_POWERUP         (1U << 0U) /*!< Setup will power on the PLL after setup */
#define PLL_SETUPFLAG_WAITLOCK        (1U << 1U) /*!< Setup will wait for PLL lock, implies the PLL will be pwoered on */
#define PLL_SETUPFLAG_ADGVOLT         (1U << 2U) /*!< Optimize system voltage for the new PLL rate */
#define PLL_SETUPFLAG_USEFEEDBACKDIV2 (1U << 3U) /*!< Use feedback divider by 2 in divider path */

/*! @brief PLL setup structure
 * This structure can be used to pre-build a PLL setup configuration
 * at run-time and quickly set the PLL to the configuration. It can be
 * populated with the PLL setup function. If powering up or waiting
 * for PLL lock, the PLL input clock source should be configured prior
 * to PLL setup.
 */
typedef struct _pll_setup
{
    uint32_t syspllctrl;      /*!< PLL control register SYSPLLCTRL */
    uint32_t syspllndec;      /*!< PLL NDEC register SYSPLLNDEC */
    uint32_t syspllpdec;      /*!< PLL PDEC register SYSPLLPDEC */
    uint32_t syspllssctrl[2]; /*!< PLL SSCTL registers SYSPLLSSCTRL */
    uint32_t pllRate;         /*!< Acutal PLL rate */
    uint32_t flags;           /*!< PLL setup flags, Or'ed value of PLL_SETUPFLAG_* definitions */
} pll_setup_t;

/*! @brief PLL status definitions
 */
typedef enum _pll_error
{
    kStatus_PLL_Success         = MAKE_STATUS(kStatusGroup_Generic, 0), /*!< PLL operation was successful */
    kStatus_PLL_OutputTooLow    = MAKE_STATUS(kStatusGroup_Generic, 1), /*!< PLL output rate request was too low */
    kStatus_PLL_OutputTooHigh   = MAKE_STATUS(kStatusGroup_Generic, 2), /*!< PLL output rate request was too high */
    kStatus_PLL_InputTooLow     = MAKE_STATUS(kStatusGroup_Generic, 3), /*!< PLL input rate is too low */
    kStatus_PLL_InputTooHigh    = MAKE_STATUS(kStatusGroup_Generic, 4), /*!< PLL input rate is too high */
    kStatus_PLL_OutsideIntLimit = MAKE_STATUS(kStatusGroup_Generic, 5)  /*!< Requested output rate isn't possible */
} pll_error_t;

/*! @brief USB clock source definition. */
typedef enum _clock_usb_src
{
    kCLOCK_UsbSrcFro       = (uint32_t)kCLOCK_FroHf,      /*!< Use FRO 96 or 48 MHz. */
    kCLOCK_UsbSrcSystemPll = (uint32_t)kCLOCK_PllOut,     /*!< Use System PLL output. */
    kCLOCK_UsbSrcMainClock = (uint32_t)kCLOCK_CoreSysClk, /*!< Use Main clock.    */
    kCLOCK_UsbSrcNone      = SYSCON_USBCLKSEL_SEL(
        7) /*!< Use None, this may be selected in order to reduce power when no output is needed. */
} clock_usb_src_t;

/*! @brief	Return System PLL output clock rate from setup structure
 *  @param	pSetup	: Pointer to a PLL setup structure
 *  @return	System PLL output clock rate calculated from the setup structure
 */
uint32_t CLOCK_GetSystemPLLOutFromSetup(pll_setup_t *pSetup);

/*! @brief	Set PLL output based on the passed PLL setup data
 *  @param	pControl	: Pointer to populated PLL control structure to generate setup with
 *  @param	pSetup		: Pointer to PLL setup structure to be filled
 *  @return	PLL_ERROR_SUCCESS on success, or PLL setup error code
 *  @note	Actual frequency for setup may vary from the desired frequency based on the
 *  accuracy of input clocks, rounding, non-fractional PLL mode, etc.
 */
pll_error_t CLOCK_SetupPLLData(pll_config_t *pControl, pll_setup_t *pSetup);

/*! @brief	Set PLL output from PLL setup structure (precise frequency)
 * @param	pSetup	: Pointer to populated PLL setup structure
 * @param flagcfg : Flag configuration for PLL config structure
 * @return	PLL_ERROR_SUCCESS on success, or PLL setup error code
 * @note	This function will power off the PLL, setup the PLL with the
 * new setup data, and then optionally powerup the PLL, wait for PLL lock,
 * and adjust system voltages to the new PLL rate. The function will not
 * alter any source clocks (ie, main systen clock) that may use the PLL,
 * so these should be setup prior to and after exiting the function.
 */
pll_error_t CLOCK_SetupSystemPLLPrec(pll_setup_t *pSetup, uint32_t flagcfg);

/**
 * @brief	Set PLL output from PLL setup structure (precise frequency)
 * @param	pSetup	: Pointer to populated PLL setup structure
 * @return	kStatus_PLL_Success on success, or PLL setup error code
 * @note	This function will power off the PLL, setup the PLL with the
 * new setup data, and then optionally powerup the PLL, wait for PLL lock,
 * and adjust system voltages to the new PLL rate. The function will not
 * alter any source clocks (ie, main systen clock) that may use the PLL,
 * so these should be setup prior to and after exiting the function.
 */
pll_error_t CLOCK_SetPLLFreq(const pll_setup_t *pSetup);

/*! @brief	Set PLL output based on the multiplier and input frequency
 * @param	multiply_by	: multiplier
 * @param	input_freq	: Clock input frequency of the PLL
 * @return	Nothing
 * @note	Unlike the Chip_Clock_SetupSystemPLLPrec() function, this
 * function does not disable or enable PLL power, wait for PLL lock,
 * or adjust system voltages. These must be done in the application.
 * The function will not alter any source clocks (ie, main systen clock)
 * that may use the PLL, so these should be setup prior to and after
 * exiting the function.
 */
void CLOCK_SetupSystemPLLMult(uint32_t multiply_by, uint32_t input_freq);

/*! @brief Disable USB FS clock.
 *
 * Disable USB FS clock.
 */
static inline void CLOCK_DisableUsbfs0Clock(void)
{
    CLOCK_DisableClock(kCLOCK_Usbd0);
}
bool CLOCK_EnableUsbfs0Clock(clock_usb_src_t src, uint32_t freq);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /* _FSL_CLOCK_H_ */
