/*
 * Copyright 2017-2021 NXP
 * All rights reserved.
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
/*! @brief CLOCK driver version 2.4.3. */
#define FSL_CLOCK_DRIVER_VERSION (MAKE_VERSION(2, 4, 3))
/*@}*/

/* Definition for delay API in clock driver, users can redefine it to the real application. */
#ifndef SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY
#define SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY (30000000UL)
#endif

/*! @brief watchdog oscilltor clock frequency.
 *
 * This variable is used to store the watchdog oscillator frequency which is
 * set by CLOCK_InitWdtOsc, and it is returned by CLOCK_GetWdtOscFreq.
 */
extern uint32_t g_Wdt_Osc_Freq;

/*! @brief external clock frequency.
 *
 * This variable is used to store the external clock frequency which is include
 * external oscillator clock and external clk in clock frequency value, it is
 * set by CLOCK_InitExtClkin when CLK IN is used as external clock or by CLOCK_InitSysOsc
 * when external oscillator is used as external clock ,and it is returned by
 * CLOCK_GetExtClkFreq.
 */
extern uint32_t g_Ext_Clk_Freq;

extern uint32_t g_Sys_Pll_Freq;

/*! @brief Clock ip name array for ADC. */
#define ADC_CLOCKS  \
    {               \
        kCLOCK_Adc, \
    }
/*! @brief Clock ip name array for ACMP. */
#define ACMP_CLOCKS  \
    {                \
        kCLOCK_Acmp, \
    }
/*! @brief Clock ip name array for SWM. */
#define SWM_CLOCKS  \
    {               \
        kCLOCK_Swm, \
    }
/*! @brief Clock ip name array for ROM. */
#define ROM_CLOCKS  \
    {               \
        kCLOCK_Rom, \
    }
/*! @brief Clock ip name array for SRAM. */
#define SRAM_CLOCKS    \
    {                  \
        kCLOCK_Ram0_1, \
    }
/*! @brief Clock ip name array for IOCON. */
#define IOCON_CLOCKS  \
    {                 \
        kCLOCK_Iocon, \
    }
/*! @brief Clock ip name array for GPIO. */
#define GPIO_CLOCKS   \
    {                 \
        kCLOCK_Gpio0, \
    }
/*! @brief Clock ip name array for GPIO_INT. */
#define GPIO_INT_CLOCKS \
    {                   \
        kCLOCK_GpioInt, \
    }
/*! @brief Clock ip name array for DMA. */
#define DMA_CLOCKS  \
    {               \
        kCLOCK_Dma, \
    }
/*! @brief Clock ip name array for CRC. */
#define CRC_CLOCKS  \
    {               \
        kCLOCK_Crc, \
    }
/*! @brief Clock ip name array for WWDT. */
#define WWDT_CLOCKS  \
    {                \
        kCLOCK_Wwdt, \
    }
/*! @brief Clock ip name array for SCT0. */
#define SCT_CLOCKS  \
    {               \
        kCLOCK_Sct, \
    }
/*! @brief Clock ip name array for I2C. */
#define I2C_CLOCKS                             \
    {                                          \
        kCLOCK_I2c1, kCLOCK_I2c2, kCLOCK_I2c3, \
    }
/*! @brief Clock ip name array for I2C. */
#define USART_CLOCKS                              \
    {                                             \
        kCLOCK_Uart0, kCLOCK_Uart1, kCLOCK_Uart2, \
    }
/*! @brief Clock ip name array for SPI. */
#define SPI_CLOCKS                \
    {                             \
        kCLOCK_Spi0, kCLOCK_Spi1, \
    }
/*! @brief Clock ip name array for MTB. */
#define MTB_CLOCKS  \
    {               \
        kCLOCK_Mtb, \
    }
/*! @brief Clock ip name array for MRT. */
#define MRT_CLOCKS  \
    {               \
        kCLOCK_Mrt, \
    }
/*! @brief Clock ip name array for WKT. */
#define WKT_CLOCKS  \
    {               \
        kCLOCK_Wkt, \
    }

/*! @brief Internal used Clock definition only. */
#define CLK_GATE_DEFINE(reg, bit)  ((((reg)&0xFFU) << 8U) | ((bit)&0xFFU))
#define CLK_GATE_GET_REG(x)        (((x) >> 8U) & 0xFFU)
#define CLK_GATE_GET_BITS_SHIFT(x) ((uint32_t)(x)&0xFFU)
/* clock mux register definition */
#define CLK_MUX_DEFINE(reg, mux)             (((offsetof(SYSCON_Type, reg) & 0xFFU) << 8U) | ((mux)&0xFFU))
#define CLK_MUX_GET_REG(x)                   ((volatile uint32_t *)(((uint32_t)(SYSCON)) + (((uint32_t)(x) >> 8U) & 0xFFU)))
#define CLK_MUX_GET_MUX(x)                   ((uint32_t)(x)&0xFFU)
#define CLK_MAIN_CLK_MUX_DEFINE(preMux, mux) ((preMux) << 8U | (mux))
#define CLK_MAIN_CLK_MUX_GET_PRE_MUX(x)      ((((uint32_t)(x)) >> 8U) & 0xFFU)
#define CLK_MAIN_CLK_MUX_GET_MUX(x)          (((uint32_t)(x)) & 0xFFU)
/* clock divider register definition */
#define CLK_DIV_DEFINE(reg) (((uint32_t)offsetof(SYSCON_Type, reg)) & 0xFFFU)
#define CLK_DIV_GET_REG(x)  *((volatile uint32_t *)(((uint32_t)(SYSCON)) + ((uint32_t)(x)&0xFFFU)))
/* watch dog oscillator definition */
#define CLK_WDT_OSC_DEFINE(freq, regValue) (((freq)&0xFFFFFFU) | (((regValue)&0xFFU) << 24U))
#define CLK_WDT_OSC_GET_FREQ(x)            (((uint32_t)(x)) & 0xFFFFFFU)
#define CLK_WDT_OSC_GET_REG(x)             (((uint32_t)(x) >> 24U) & 0xFFU)
/* register offset */
#define SYS_AHB_CLK_CTRL (0U)
/*! @brief Clock gate name used for CLOCK_EnableClock/CLOCK_DisableClock. */
typedef enum _clock_ip_name
{
    kCLOCK_Sys      = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL, 0U),  /*!< Clock gate name: Sys. */
    kCLOCK_Rom      = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL, 1U),  /*!< Clock gate name: Rom. */
    kCLOCK_Ram0_1   = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL, 2U),  /*!< Clock gate name: Ram0_1. */
    kCLOCK_Flashreg = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL, 3U),  /*!< Clock gate name: Flashreg. */
    kCLOCK_Flash    = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL, 4U),  /*!< Clock gate name: Flash. */
    kCLOCK_I2c0     = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL, 5U),  /*!< Clock gate name: I2c0. */
    kCLOCK_Gpio0    = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL, 6U),  /*!< Clock gate name: Gpio0. */
    kCLOCK_Swm      = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL, 7U),  /*!< Clock gate name: Swm. */
    kCLOCK_Sct      = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL, 8U),  /*!< Clock gate name: Sct. */
    kCLOCK_Wkt      = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL, 9U),  /*!< Clock gate name: Wkt. */
    kCLOCK_Mrt      = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL, 10U), /*!< Clock gate name: Mrt. */
    kCLOCK_Spi0     = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL, 11U), /*!< Clock gate name: Spi0. */
    kCLOCK_Spi1     = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL, 12U), /*!< Clock gate name: Spi1. */
    kCLOCK_Crc      = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL, 13U), /*!< Clock gate name: Crc. */
    kCLOCK_Uart0    = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL, 14U), /*!< Clock gate name: Uart0. */
    kCLOCK_Uart1    = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL, 15U), /*!< Clock gate name: Uart1. */
    kCLOCK_Uart2    = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL, 16U), /*!< Clock gate name: Uart2. */
    kCLOCK_Wwdt     = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL, 17U), /*!< Clock gate name: Wwdt. */
    kCLOCK_Iocon    = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL, 18U), /*!< Clock gate name: Iocon. */
    kCLOCK_Acmp     = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL, 19U), /*!< Clock gate name: Acmp. */
    kCLOCK_I2c1     = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL, 21U), /*!< Clock gate name: I2c1. */
    kCLOCK_I2c2     = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL, 22U), /*!< Clock gate name: I2c2. */
    kCLOCK_I2c3     = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL, 23U), /*!< Clock gate name: I2c3. */
    kCLOCK_Adc      = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL, 24U), /*!< Clock gate name: Adc. */
    kCLOCK_Mtb      = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL, 26U), /*!< Clock gate name: Mtb. */
    kCLOCK_Dma      = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL, 29U), /*!< Clock gate name: Dma. */
} clock_ip_name_t;

/*! @brief Clock name used to get clock frequency. */
typedef enum _clock_name
{
    kCLOCK_CoreSysClk, /*!< Cpu/AHB/AHB matrix/Memories,etc */
    kCLOCK_MainClk,    /*!< Main clock */
    kCLOCK_SysOsc,     /*!< Crystal Oscillator */
    kCLOCK_Irc,        /*!< IRC12M */
    kCLOCK_ExtClk,     /*!< External Clock */
    kCLOCK_PllOut,     /*!< PLL Output */
    kCLOCK_Pllin,      /*!< PLL Input */
    kCLOCK_WdtOsc,     /*!< Watchdog Oscillator */
} clock_name_t;

/*! @brief Clock Mux Switches
 *CLK_MUX_DEFINE(reg, mux)
 *reg is used to define the mux register
 *mux is used to define the mux value
 *
 */
typedef enum _clock_select
{

    kSYSPLL_From_Irc = CLK_MUX_DEFINE(SYSPLLCLKSEL, 0U), /*!< Mux SYSPLL from Irc. */

    kSYSPLL_From_SysOsc = CLK_MUX_DEFINE(SYSPLLCLKSEL, 1U), /*!< Mux SYSPLL from SysOsc. */

    kSYSPLL_From_ExtClk = CLK_MUX_DEFINE(SYSPLLCLKSEL, 3U), /*!< Mux SYSPLL from ExtClk. */

    kMAINCLK_From_Irc = CLK_MUX_DEFINE(MAINCLKSEL, 0U), /*!< Mux MAINCLK from Irc. */

    kMAINCLK_From_SysPllIn = CLK_MUX_DEFINE(MAINCLKSEL, 1U), /*!< Mux MAINCLK from SysPllIn. */

    kMAINCLK_From_WdtOsc = CLK_MUX_DEFINE(MAINCLKSEL, 2U), /*!< Mux MAINCLK from WdtOsc. */

    kMAINCLK_From_SysPll = CLK_MUX_DEFINE(MAINCLKSEL, 3U), /*!< Mux MAINCLK from SysPll. */

    kCLKOUT_From_Irc = CLK_MUX_DEFINE(CLKOUTSEL, 0U), /*!< Mux CLKOUT from Irc. */

    kCLKOUT_From_SysOsc = CLK_MUX_DEFINE(CLKOUTSEL, 1U), /*!< Mux CLKOUT from SysOsc. */

    kCLKOUT_From_WdtOsc = CLK_MUX_DEFINE(CLKOUTSEL, 2U), /*!< Mux CLKOUT from WdtOsc. */

    kCLKOUT_From_MainClk = CLK_MUX_DEFINE(CLKOUTSEL, 3U) /*!< Mux clock out from Main clock. */
} clock_select_t;

/*! @brief Clock divider
 */
typedef enum _clock_divider
{

    kCLOCK_DivUsartClk = CLK_DIV_DEFINE(UARTCLKDIV), /*!< Usart Clock Divider. */

    kCLOCK_DivClkOut = CLK_DIV_DEFINE(CLKOUTDIV), /*!< Clk Out Divider. */

    kCLOCK_DivUartFrg = CLK_DIV_DEFINE(UARTFRGDIV), /*!< Uart Frg Divider. */

    kCLOCK_IOCONCLKDiv6 = CLK_DIV_DEFINE(IOCONCLKDIV6), /*!< IOCON Clock Div6 Divider. */

    kCLOCK_IOCONCLKDiv5 = CLK_DIV_DEFINE(IOCONCLKDIV5), /*!< IOCON Clock Div5 Divider. */

    kCLOCK_IOCONCLKDiv4 = CLK_DIV_DEFINE(IOCONCLKDIV4), /*!< IOCON Clock Div4 Divider. */

    kCLOCK_IOCONCLKDiv3 = CLK_DIV_DEFINE(IOCONCLKDIV3), /*!< IOCON Clock Div3 Divider. */

    kCLOCK_IOCONCLKDiv2 = CLK_DIV_DEFINE(IOCONCLKDIV2), /*!< IOCON Clock Div2 Divider. */

    kCLOCK_IOCONCLKDiv1 = CLK_DIV_DEFINE(IOCONCLKDIV1), /*!< IOCON Clock Div1 Divider. */

    kCLOCK_IOCONCLKDiv0 = CLK_DIV_DEFINE(IOCONCLKDIV0), /*!< IOCON Clock Div0 Divider. */

} clock_divider_t;

/*! @brief watch dog analog output frequency */
typedef enum _clock_wdt_analog_freq
{
    kCLOCK_WdtAnaFreq0HZ = CLK_WDT_OSC_DEFINE(0U, 0U), /*!< Watch dog analog output frequency is 0HZ. */

    kCLOCK_WdtAnaFreq600KHZ = CLK_WDT_OSC_DEFINE(600000U, 1U), /*!< Watch dog analog output frequency is 600KHZ. */

    kCLOCK_WdtAnaFreq1050KHZ = CLK_WDT_OSC_DEFINE(1050000U, 2u), /*!< Watch dog analog output frequency is 1050KHZ. */

    kCLOCK_WdtAnaFreq1400KHZ = CLK_WDT_OSC_DEFINE(1400000U, 3U), /*!< Watch dog analog output frequency is 1400KHZ. */

    kCLOCK_WdtAnaFreq1750KHZ = CLK_WDT_OSC_DEFINE(1750000U, 4U), /*!< Watch dog analog output frequency is 1750KHZ. */

    kCLOCK_WdtAnaFreq2100KHZ = CLK_WDT_OSC_DEFINE(2100000U, 5U), /*!< Watch dog analog output frequency is 2100KHZ. */

    kCLOCK_WdtAnaFreq2400KHZ = CLK_WDT_OSC_DEFINE(2400000U, 6U), /*!< Watch dog analog output frequency is 2400KHZ. */

    kCLOCK_WdtAnaFreq2700KHZ = CLK_WDT_OSC_DEFINE(2700000U, 7U), /*!< Watch dog analog output frequency is 2700KHZ. */

    kCLOCK_WdtAnaFreq3000KHZ = CLK_WDT_OSC_DEFINE(3000000U, 8U), /*!< Watch dog analog output frequency is 3000KHZ. */

    kCLOCK_WdtAnaFreq3250KHZ = CLK_WDT_OSC_DEFINE(3250000U, 9U), /*!< Watch dog analog output frequency is 3250KHZ. */

    kCLOCK_WdtAnaFreq3500KHZ = CLK_WDT_OSC_DEFINE(3500000U, 10U), /*!< Watch dog analog output frequency is 3500KHZ. */

    kCLOCK_WdtAnaFreq3750KHZ = CLK_WDT_OSC_DEFINE(3750000U, 11U), /*!< Watch dog analog output frequency is 3750KHZ. */

    kCLOCK_WdtAnaFreq4000KHZ = CLK_WDT_OSC_DEFINE(4000000U, 12U), /*!< Watch dog analog output frequency is 4000KHZ. */

    kCLOCK_WdtAnaFreq4200KHZ = CLK_WDT_OSC_DEFINE(4200000U, 13U), /*!< Watch dog analog output frequency is 4200KHZ. */

    kCLOCK_WdtAnaFreq4400KHZ = CLK_WDT_OSC_DEFINE(4400000U, 14U), /*!< Watch dog analog output frequency is 4400KHZ. */

    kCLOCK_WdtAnaFreq4600KHZ = CLK_WDT_OSC_DEFINE(4600000U, 15U), /*!< Watch dog analog output frequency is 4600KHZ. */

} clock_wdt_analog_freq_t;

/*! @brief PLL clock definition.*/
typedef enum _clock_sys_pll_src
{
    kCLOCK_SysPllSrcIrc    = 0U, /*!< system pll source from FRO */
    kCLOCK_SysPllSrcSysosc = 1U, /*!< system pll source from system osc */
    kCLOCK_SysPllSrcExtClk = 3U, /*!< system pll source from ext clkin */
} clock_sys_pll_src;

/*! @brief Main clock source definition */
typedef enum _clock_main_clk_src
{
    kCLOCK_MainClkSrcIrc      = CLK_MAIN_CLK_MUX_DEFINE(0U, 0U), /*!< main clock source from FRO */
    kCLOCK_MainClkSrcSysPllin = CLK_MAIN_CLK_MUX_DEFINE(1U, 0U), /*!< main clock source from pll input */
    kCLOCK_MainClkSrcWdtOsc   = CLK_MAIN_CLK_MUX_DEFINE(2U, 0U), /*!< main clock source from watchdog oscillator */
    kCLOCK_MainClkSrcSysPll   = CLK_MAIN_CLK_MUX_DEFINE(3U, 0U), /*!< main clock source from system pll */
} clock_main_clk_src_t;

/*! @brief PLL configuration structure */
typedef struct _clock_sys_pll
{
    uint32_t targetFreq;   /*!< System pll fclk output frequency, the output frequency should be lower than 100MHZ*/
    clock_sys_pll_src src; /*!< System pll clock source */
} clock_sys_pll_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @name Clock gate, mux, and divider.
 * @{
 */

/*
 *! @brief enable ip clock.
 *
 * @param clk clock ip definition.
 */
static inline void CLOCK_EnableClock(clock_ip_name_t clk)
{
    SYSCON->SYSAHBCLKCTRL |= 1UL << CLK_GATE_GET_BITS_SHIFT(clk);
}

/*
 *!@brief disable ip clock.
 *
 * @param clk clock ip definition.
 */
static inline void CLOCK_DisableClock(clock_ip_name_t clk)
{
    SYSCON->SYSAHBCLKCTRL &= ~(1UL << CLK_GATE_GET_BITS_SHIFT(clk));
}

/*
 *! @brief	Configure the clock selection muxes.
 * @param	mux	: Clock to be configured.
 * @return	Nothing
 */
static inline void CLOCK_Select(clock_select_t sel)
{
    *(CLK_MUX_GET_REG(sel)) = CLK_MUX_GET_MUX(sel);
}

/*
 *! @brief	Setup peripheral clock dividers.
 * @param	name	: Clock divider name
 * @param   value: Value to be divided
 * @return	Nothing
 */
static inline void CLOCK_SetClkDivider(clock_divider_t name, uint32_t value)
{
    CLK_DIV_GET_REG(name) = value & 0xFFU;
}

/*
 *! @brief  Get peripheral clock dividers.
 * @param   name    : Clock divider name
 * @return  clock divider value
 */
static inline uint32_t CLOCK_GetClkDivider(clock_divider_t name)
{
    return CLK_DIV_GET_REG(name) & 0xFFU;
}

/*
 *! @brief   Setup Core clock dividers.
 * Be careful about the core divider value, due to core/system frequency should be lower than 30MHZ.
 * @param   value: Value to be divided
 * @return  Nothing
 */
static inline void CLOCK_SetCoreSysClkDiv(uint32_t value)
{
    assert(value != 0U);

    SYSCON->SYSAHBCLKDIV = (SYSCON->SYSAHBCLKDIV & (~SYSCON_SYSAHBCLKDIV_DIV_MASK)) | SYSCON_SYSAHBCLKDIV_DIV(value);
}

/*! @brief  Set main clock reference source.
 * @param src, reference clock_main_clk_src_t to set the main clock source.
 */
void CLOCK_SetMainClkSrc(clock_main_clk_src_t src);

/*
 *! @brief	Set Fractional generator 0 multiplier value.
 * @param	mul	: FRG0 multiplier value.
 * @return	Nothing
 */
static inline void CLOCK_SetFRGClkMul(uint32_t mul)
{
    SYSCON->UARTFRGDIV  = SYSCON_UARTFRGDIV_DIV_MASK;
    SYSCON->UARTFRGMULT = SYSCON_UARTFRGMULT_MULT(mul);
}
/* @} */

/*!
 * @name Get frequency
 * @{
 */

/*! @brief  Return Frequency of Main Clock.
 *  @return Frequency of Main Clock.
 */
uint32_t CLOCK_GetMainClkFreq(void);

/*! @brief  Return Frequency of core.
 *  @return Frequency of core.
 */
static inline uint32_t CLOCK_GetCoreSysClkFreq(void)
{
    return CLOCK_GetMainClkFreq() / (SYSCON->SYSAHBCLKDIV & 0xffU);
}

/*! @brief  Return Frequency of ClockOut
 *  @return Frequency of ClockOut
 */
uint32_t CLOCK_GetClockOutClkFreq(void);

/*! @brief  Return Frequency of IRC
 *  @return Frequency of IRC
 */
uint32_t CLOCK_GetIrcFreq(void);

/*! @brief  Return Frequency of SYSOSC
 *  @return Frequency of SYSOSC
 */
uint32_t CLOCK_GetSysOscFreq(void);

/*! @brief  Get UART0 frequency
 * @retval UART0 frequency value.
 */
uint32_t CLOCK_GetUartClkFreq(void);

/*! @brief  Get UART0 frequency
 * @retval UART0 frequency value.
 */
uint32_t CLOCK_GetUart0ClkFreq(void);

/*! @brief  Get UART1 frequency
 * @retval UART1 frequency value.
 */
uint32_t CLOCK_GetUart1ClkFreq(void);

/*! @brief  Get UART2 frequency
 * @retval UART2 frequency value.
 */
uint32_t CLOCK_GetUart2ClkFreq(void);

/*! @brief	Return Frequency of selected clock
 *  @return	Frequency of selected clock
 */
uint32_t CLOCK_GetFreq(clock_name_t clockName);

/*! @brief  Return System PLL input clock rate
 *  @return System PLL input clock rate
 */
uint32_t CLOCK_GetSystemPLLInClockRate(void);

/*! @brief  Return Frequency of System PLL
 *  @return Frequency of PLL
 */
static inline uint32_t CLOCK_GetSystemPLLFreq(void)
{
    return CLOCK_GetSystemPLLInClockRate() * ((SYSCON->SYSPLLCTRL & SYSCON_SYSPLLCTRL_MSEL_MASK) + 1U);
}

/*! @brief  Get watch dog OSC frequency
 * @retval watch dog OSC frequency value.
 */
static inline uint32_t CLOCK_GetWdtOscFreq(void)
{
    return g_Wdt_Osc_Freq;
}

/*! @brief  Get external clock frequency
 * @retval external clock frequency value.
 */
static inline uint32_t CLOCK_GetExtClkFreq(void)
{
    return g_Ext_Clk_Freq;
}
/* @} */

/*!
 * @name PLL operations
 * @{
 */

/*! @brief  System PLL initialize.
 *  @param config System PLL configurations.
 */
void CLOCK_InitSystemPll(const clock_sys_pll_t *config);

/*! @brief  System PLL Deinitialize.*/
static inline void CLOCK_DenitSystemPll(void)
{
    /* Power off PLL */
    SYSCON->PDRUNCFG |= SYSCON_PDRUNCFG_SYSPLL_PD_MASK;
}

/* @} */

/*!
 * @name External/internal oscillator clock operations
 * @{
 */

/*! @brief  Init external CLK IN, select the CLKIN as the external clock source.
 * @param clkInFreq external clock in frequency.
 */
void CLOCK_InitExtClkin(uint32_t clkInFreq);

/*! @brief	Init SYS OSC
 * @param oscFreq oscillator frequency value.
 */
void CLOCK_InitSysOsc(uint32_t oscFreq);

/*! @brief  XTALIN init function
 *  system oscillator is bypassed, sys_osc_clk is fed driectly from the XTALIN.
 *  @param xtalInFreq XTALIN frequency value
 *  @return Frequency of PLL
 */
void CLOCK_InitXtalin(uint32_t xtalInFreq);

/*! @brief  Deinit SYS OSC
 * @param config oscillator configuration.
 */
static inline void CLOCK_DeinitSysOsc(void)
{
    /* Deinit system osc power */
    SYSCON->PDRUNCFG |= SYSCON_PDRUNCFG_SYSOSC_PD_MASK;
}

/*! @brief  Init watch dog OSC
 * Any setting of the FREQSEL bits will yield a Fclkana value within 40% of the
 * listed frequency value. The watchdog oscillator is the clock source with the lowest power
 * consumption. If accurate timing is required, use the FRO or system oscillator.
 * The frequency of the watchdog oscillator is undefined after reset. The watchdog
 * oscillator frequency must be programmed by writing to the WDTOSCCTRL register before
 * using the watchdog oscillator.
 * Watchdog osc output frequency = wdtOscFreq / wdtOscDiv, should in range 9.3KHZ to 2.3MHZ.
 * @param wdtOscFreq watch dog analog part output frequency, reference _wdt_analog_output_freq.
 * @param wdtOscDiv watch dog analog part output frequency divider, shoule be a value >= 2U and multiple of 2
 */
void CLOCK_InitWdtOsc(clock_wdt_analog_freq_t wdtOscFreq, uint32_t wdtOscDiv);

/*! @brief  Deinit watch dog OSC
 * @param config oscillator configuration.
 */
static inline void CLOCK_DeinitWdtOsc(void)
{
    SYSCON->PDRUNCFG |= SYSCON_PDRUNCFG_WDTOSC_PD_MASK;
}

/*! @brief  Set UARTFRG
 * @param target UART clock src.
 */
bool CLOCK_SetUARTFRGClkFreq(uint32_t freq);

/*! @brief  updates the clock source of the CLKOUT
 */
void CLOCK_UpdateClkOUTsrc(void);

/*! @brief  Set UARTFRGMULT
 * @deprecated Do not use this function. Refer to CLOCK_SetFRGClkMul().
 * @param UARTFRGMULT.
 */
static inline void CLOCK_SetUARTFRGMULT(uint32_t mul)
{
    SYSCON->UARTFRGMULT = SYSCON_UARTFRGMULT_MULT(mul);
}

/* @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /* _FSL_CLOCK_H_ */
