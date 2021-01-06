/*
 * Copyright 2017-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_clock.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.clock"
#endif
#define SYSPLL_MIN_INPUT_FREQ_HZ  (10000000U)  /*!<  Minimum PLL input rate */
#define SYSPLL_MAX_INPUT_FREQ_HZ  (25000000U)  /*!<  Maximum PLL input rate */
#define SYSPLL_MAX_OUTPUT_FREQ_HZ (100000000U) /*!< Maximum PLL output rate */
#define SYSPLL_MIN_FCCO_FREQ_HZ   (156000000U) /*!< Maximum FCCO output rate */
#define SYSPLL_MAX_FCCO_FREQ_HZ   (320000000U) /*!< Maximum FCCO output rate */
#define SYSOSC_BOUNDARY_FREQ_HZ   (15000000U)  /*!< boundary frequency value */

/* External clock rate.
 * Either external clk in rate or system oscillator frequency.
 */
uint32_t g_Ext_Clk_Freq = 0U;
uint32_t g_Wdt_Osc_Freq = 0U;

/** Sys pll freq.*/
uint32_t g_Sys_Pll_Freq = 0U;
/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*
 * @brief   select post divider for system pll according to the target frequency.
 * @param   outFreq: Value to be output
 * @return  post divider
 */
static uint32_t findSyestemPllPsel(uint32_t outFreq);

/*
 * @brief Update clock source.
 * @param base clock register base address.
 * @param mask clock source update enable bit mask value.
 */
static void CLOCK_UpdateClkSrc(volatile uint32_t *base, uint32_t mask);

/*******************************************************************************
 * Code
 ******************************************************************************/
static void CLOCK_UpdateClkSrc(volatile uint32_t *base, uint32_t mask)
{
    assert(base);

    *base &= ~mask;
    *base |= mask;
    while ((*base & mask) == 0U)
    {
    }
}

/*! brief  Return Frequency of IRC
 *  return Frequency of IRC
 */
uint32_t CLOCK_GetIrcFreq(void)
{
    return 12000000U;
}

/*! brief  Return Frequency of SYSOSC
 *  return Frequency of SYSOSC
 */
uint32_t CLOCK_GetSysOscFreq(void)
{
    uint32_t freq = 0U;
    if ((SYSCON->PDRUNCFG & SYSCON_PDRUNCFG_SYSOSC_PD_MASK) == 0U)
    {
        freq = CLOCK_GetExtClkFreq();
    }
    return freq;
}

/*! brief  Return Frequency of Main Clock.
 *  return Frequency of Main Clock.
 */
uint32_t CLOCK_GetMainClkFreq(void)
{
    uint32_t freq = 0U;

    switch (SYSCON->MAINCLKSEL)
    {
        case 0U:
            freq = CLOCK_GetIrcFreq();
            break;

        case 1U:
            freq = CLOCK_GetSystemPLLInClockRate();
            break;

        case 2U:
            freq = CLOCK_GetWdtOscFreq();
            break;

        case 3U:
            freq = CLOCK_GetSystemPLLFreq();
            break;
        default:
            assert(false);
            break;
    }

    return freq;
}

/*! brief  Return Frequency of ClockOut
 *  return Frequency of ClockOut
 */
uint32_t CLOCK_GetClockOutClkFreq(void)
{
    uint32_t div = SYSCON->CLKOUTDIV & 0xffU, freq = 0U;

    switch (SYSCON->CLKOUTSEL)
    {
        case 0U:
            freq = CLOCK_GetIrcFreq();
            break;

        case 1U:
            freq = CLOCK_GetSysOscFreq();
            break;

        case 2U:
            freq = CLOCK_GetWdtOscFreq();
            break;

        case 3U:
            freq = CLOCK_GetMainClkFreq();
            break;

        default:
            assert(false);
            break;
    }

    return div == 0U ? 0U : (freq / div);
}

/*! brief  Return Frequency of UART
 *  return Frequency of UART
 */
uint32_t CLOCK_GetUartClkFreq(void)
{
    uint32_t freq    = CLOCK_GetMainClkFreq();
    uint32_t uartDiv = SYSCON->UARTCLKDIV & 0xffU;

    return uartDiv == 0U ? 0U :
                           (uint32_t)((uint64_t)(freq << 8U) /
                                      (uartDiv * (256U + ((SYSCON->UARTFRGMULT) & SYSCON_UARTFRGMULT_MULT_MASK))));
}

/*! brief  Return Frequency of UART0
 *  return Frequency of UART0
 */
uint32_t CLOCK_GetUart0ClkFreq(void)
{
    return CLOCK_GetUartClkFreq();
}

/*! brief  Return Frequency of UART1
 *  return Frequency of UART1
 */
uint32_t CLOCK_GetUart1ClkFreq(void)
{
    return CLOCK_GetUartClkFreq();
}

/*! brief  Return Frequency of UART2
 *  return Frequency of UART2
 */
uint32_t CLOCK_GetUart2ClkFreq(void)
{
    return CLOCK_GetUartClkFreq();
}

/*! brief	Return Frequency of selected clock
 *  return	Frequency of selected clock
 */
uint32_t CLOCK_GetFreq(clock_name_t clockName)
{
    uint32_t freq;

    switch (clockName)
    {
        case kCLOCK_CoreSysClk:
            freq = CLOCK_GetCoreSysClkFreq();
            break;
        case kCLOCK_MainClk:
            freq = CLOCK_GetMainClkFreq();
            break;
        case kCLOCK_Irc:
            freq = CLOCK_GetIrcFreq();
            break;
        case kCLOCK_ExtClk:
            freq = CLOCK_GetExtClkFreq();
            break;
        case kCLOCK_WdtOsc:
            freq = CLOCK_GetWdtOscFreq();
            break;
        case kCLOCK_PllOut:
            freq = CLOCK_GetSystemPLLFreq();
            break;

        default:
            freq = 0U;
            break;
    }

    return freq;
}

/*! brief  Return System PLL input clock rate
 *  return System PLL input clock rate
 */
uint32_t CLOCK_GetSystemPLLInClockRate(void)
{
    uint32_t freq = 0U;

    switch ((SYSCON->SYSPLLCLKSEL & SYSCON_SYSPLLCLKSEL_SEL_MASK))
    {
        /* source from external clock in */
        case 0x00U:
            freq = CLOCK_GetIrcFreq();
            break;
        /* source from the IRC clock */
        case 0x01U:
            freq = CLOCK_GetSysOscFreq();
            break;
        /* source from external clock clock */
        case 0x03U:
            freq = CLOCK_GetExtClkFreq();
            break;

        default:
            assert(false);
            break;
    }

    return freq;
}

static uint32_t findSyestemPllPsel(uint32_t outFreq)
{
    uint32_t pSel = 0U;

    if (outFreq > (SYSPLL_MIN_FCCO_FREQ_HZ >> 1U))
    {
        pSel = 0U;
    }
    else if (outFreq > (SYSPLL_MIN_FCCO_FREQ_HZ >> 2U))
    {
        pSel = 1U;
    }
    else if (outFreq > (SYSPLL_MIN_FCCO_FREQ_HZ >> 3U))
    {
        pSel = 2U;
    }
    else
    {
        pSel = 3U;
    }

    return pSel;
}

/*! brief  System PLL initialize.
 *  param config System PLL configurations.
 */
void CLOCK_InitSystemPll(const clock_sys_pll_t *config)
{
    assert(config->targetFreq <= SYSPLL_MAX_OUTPUT_FREQ_HZ);

    uint32_t mSel = 0U, pSel = 0U, inputFreq = 0U;
    uint32_t syspllclkseltmp;
    /* Power off PLL during setup changes */
    SYSCON->PDRUNCFG |= SYSCON_PDRUNCFG_SYSPLL_PD_MASK;

    /*set system pll clock source select register */
    syspllclkseltmp = (SYSCON->SYSPLLCLKSEL & (~SYSCON_SYSPLLCLKSEL_SEL_MASK)) | (uint32_t)config->src;
    SYSCON->SYSPLLCLKSEL |= syspllclkseltmp;
    /* system pll clock source update */
    CLOCK_UpdateClkSrc((volatile uint32_t *)(&(SYSCON->SYSPLLCLKUEN)), SYSCON_SYSPLLCLKSEL_SEL_MASK);

    inputFreq = CLOCK_GetSystemPLLInClockRate();
    assert(inputFreq != 0U);

    /* calucate the feedback divider value and post divider value*/
    mSel = config->targetFreq / inputFreq;
    pSel = findSyestemPllPsel(config->targetFreq);

    /* configure PSEL and MSEL */
    SYSCON->SYSPLLCTRL = (SYSCON->SYSPLLCTRL & (~(SYSCON_SYSPLLCTRL_MSEL_MASK | SYSCON_SYSPLLCTRL_PSEL_MASK))) |
                         SYSCON_SYSPLLCTRL_MSEL(mSel - 1U) | SYSCON_SYSPLLCTRL_PSEL(pSel);

    /* Power up PLL after setup changes */
    SYSCON->PDRUNCFG &= ~SYSCON_PDRUNCFG_SYSPLL_PD_MASK;

    /* wait pll lock */
    while ((SYSCON->SYSPLLSTAT & SYSCON_SYSPLLSTAT_LOCK_MASK) == 0U)
    {
    }

    g_Sys_Pll_Freq = inputFreq * mSel;
}

/*! brief  Init external CLK IN, select the CLKIN as the external clock source.
 * param clkInFreq external clock in frequency.
 */
void CLOCK_InitExtClkin(uint32_t clkInFreq)
{
    /* remove the pull up and pull down resistors in the IOCON */
    IOCON->PIO[IOCON_INDEX_PIO0_1] &= ~IOCON_PIO_MODE_MASK;
    /* enable the 1 bit functions for CLKIN */
    SWM0->PINENABLE0 &= ~SWM_PINENABLE0_CLKIN_MASK;
    /* record the external clock rate */
    g_Ext_Clk_Freq = clkInFreq;
}

/*! brief  XTALIN init function
 *  system oscillator is bypassed, sys_osc_clk is fed driectly from the XTALIN.
 *  param xtalInFreq XTALIN frequency value
 *  return Frequency of PLL
 */
void CLOCK_InitXtalin(uint32_t xtalInFreq)
{
    /* remove the pull up and pull down resistors in the IOCON */
    IOCON->PIO[IOCON_INDEX_PIO0_8] &= ~IOCON_PIO_MODE_MASK;
    /* enable the 1 bit functions for XTALIN and XTALOUT */
    SWM0->PINENABLE0 &= ~SWM_PINENABLE0_XTALIN_MASK;

    /* system osc configure */
    SYSCON->SYSOSCCTRL |= SYSCON_SYSOSCCTRL_BYPASS_MASK;
    /* enable system osc power first */
    SYSCON->PDRUNCFG &= ~SYSCON_PDRUNCFG_SYSOSC_PD_MASK;

    /* software delay 500USs */
    SDK_DelayAtLeastUs(500U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

    /* record the external clock rate */
    g_Ext_Clk_Freq = xtalInFreq;
}

/*! brief	Init SYS OSC
 * param oscFreq oscillator frequency value.
 */
void CLOCK_InitSysOsc(uint32_t oscFreq)
{
    uint32_t sysoscctrltmp;
    /* remove the pull up and pull down resistors in the IOCON */
    IOCON->PIO[IOCON_INDEX_PIO0_9] &= ~IOCON_PIO_MODE_MASK;
    IOCON->PIO[IOCON_INDEX_PIO0_8] &= ~IOCON_PIO_MODE_MASK;
    /* enable the 1 bit functions for XTALIN and XTALOUT */
    SWM0->PINENABLE0 &= ~(SWM_PINENABLE0_XTALIN_MASK | SWM_PINENABLE0_XTALOUT_MASK);

    /* system osc configure */
    sysoscctrltmp = (SYSCON->SYSOSCCTRL & (~(SYSCON_SYSOSCCTRL_BYPASS_MASK | SYSCON_SYSOSCCTRL_FREQ_RANGE_MASK))) |
                    (oscFreq > SYSOSC_BOUNDARY_FREQ_HZ ? SYSCON_SYSOSCCTRL_FREQ_RANGE_MASK : 0U);
    SYSCON->SYSOSCCTRL |= sysoscctrltmp;

    /* enable system osc power first */
    SYSCON->PDRUNCFG &= ~SYSCON_PDRUNCFG_SYSOSC_PD_MASK;

    /* software delay 500USs */
    SDK_DelayAtLeastUs(500U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

    /* record the external clock rate */
    g_Ext_Clk_Freq = oscFreq;
}

/*! brief  Init watch dog OSC
 * Any setting of the FREQSEL bits will yield a Fclkana value within 40% of the
 * listed frequency value. The watchdog oscillator is the clock source with the lowest power
 * consumption. If accurate timing is required, use the FRO or system oscillator.
 * The frequency of the watchdog oscillator is undefined after reset. The watchdog
 * oscillator frequency must be programmed by writing to the WDTOSCCTRL register before
 * using the watchdog oscillator.
 * Watchdog osc output frequency = wdtOscFreq / wdtOscDiv, should in range 9.3KHZ to 2.3MHZ.
 * param wdtOscFreq watch dog analog part output frequency, reference _wdt_analog_output_freq.
 * param wdtOscDiv watch dog analog part output frequency divider, shoule be a value >= 2U and multiple of 2
 */
void CLOCK_InitWdtOsc(clock_wdt_analog_freq_t wdtOscFreq, uint32_t wdtOscDiv)
{
    assert(wdtOscDiv >= 2U);

    uint32_t wdtOscCtrl = SYSCON->WDTOSCCTRL;

    wdtOscCtrl &= ~(SYSCON_WDTOSCCTRL_DIVSEL_MASK | SYSCON_WDTOSCCTRL_FREQSEL_MASK);

    wdtOscCtrl |=
        SYSCON_WDTOSCCTRL_DIVSEL((wdtOscDiv >> 1U) - 1U) | SYSCON_WDTOSCCTRL_FREQSEL(CLK_WDT_OSC_GET_REG(wdtOscFreq));

    SYSCON->WDTOSCCTRL = wdtOscCtrl;

    /* power up watchdog oscillator */
    SYSCON->PDRUNCFG &= ~SYSCON_PDRUNCFG_WDTOSC_PD_MASK;
    /* update watch dog oscillator value */
    g_Wdt_Osc_Freq = CLK_WDT_OSC_GET_FREQ(wdtOscFreq) / wdtOscDiv;
}

/*! brief  Set main clock reference source.
 * param src, reference clock_main_clk_src_t to set the main clock source.
 */
void CLOCK_SetMainClkSrc(clock_main_clk_src_t src)
{
    uint32_t mainMux = CLK_MAIN_CLK_MUX_GET_MUX(src), mainPreMux = CLK_MAIN_CLK_MUX_GET_PRE_MUX(src);

    if (((SYSCON->MAINCLKSEL & SYSCON_MAINCLKSEL_SEL_MASK) != mainPreMux) && (mainMux == 0U))
    {
        SYSCON->MAINCLKSEL = (SYSCON->MAINCLKSEL & (~SYSCON_MAINCLKSEL_SEL_MASK)) | SYSCON_MAINCLKSEL_SEL(mainPreMux);
        CLOCK_UpdateClkSrc((volatile uint32_t *)(&(SYSCON->MAINCLKUEN)), SYSCON_MAINCLKUEN_ENA_MASK);
    }
}

/*! brief  Set UARTFRG
 * param target UART clock src.
 */
bool CLOCK_SetUARTFRGClkFreq(uint32_t freq)
{
    uint32_t input = CLOCK_GetMainClkFreq();
    uint32_t mul;

    freq *= SYSCON->UARTCLKDIV;

    /* The given frequency should not be 0. */
    assert(0UL != freq);

    if ((freq > input) || (input / freq >= 2U))
    {
        return false;
    }

    mul = (uint32_t)(((uint64_t)((uint64_t)input - freq) << 8U) / ((uint64_t)freq));

    SYSCON->UARTFRGDIV  = SYSCON_UARTFRGDIV_DIV_MASK;
    SYSCON->UARTFRGMULT = SYSCON_UARTFRGMULT_MULT(mul);

    return true;
}

/*! brief  updates the clock source of the CLKOUT
 */
void CLOCK_UpdateClkOUTsrc(void)
{
    CLOCK_UpdateClkSrc((volatile uint32_t *)(&(SYSCON->CLKOUTUEN)), SYSCON_CLKOUTUEN_ENA_MASK);
}
