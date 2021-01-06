/*
 * Copyright 2015, Freescale Semiconductor, Inc.
 * Copyright 2016 - 2019 , NXP
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

#define SCG_SIRC_LOW_RANGE_FREQ 4000000U   /* Slow IRC low range clock frequency. */
#define SCG_SIRC_HIGH_RANGE_FREQ 16000000U /* Slow IRC high range clock frequency.   */

#define SCG_FIRC_FREQ0 48000000U /* Fast IRC trimed clock frequency(48MHz). */
#define SCG_FIRC_FREQ1 52000000U /* Fast IRC trimed clock frequency(52MHz). */
#define SCG_FIRC_FREQ2 56000000U /* Fast IRC trimed clock frequency(56MHz). */
#define SCG_FIRC_FREQ3 60000000U /* Fast IRC trimed clock frequency(60MHz). */

/*
 * System PLL base divider value, it is the PLL reference clock divider
 * value when SCG_SPLLCFG[PREDIV]=0.
 */
#define SCG_SPLL_PREDIV_BASE_VALUE 1U

/*
 * System PLL base multiplier value, it is the PLL multiplier value
 * when SCG_SPLLCFG[MULT]=0.
 */
#define SCG_SPLL_MULT_BASE_VALUE 0U

/*
 * Auxiliary PLL base divider value, it is the PLL reference clock divider
 * value when SCG_APLLCFG[PREDIV]=0.
 */
#define SCG_APLL_PREDIV_BASE_VALUE 1U

/*
 * Auxiliary PLL base multiplier value, it is the PLL multiplier value
 * when SCG_APLLCFG[MULT]=0.
 */
#define SCG_APLL_MULT_BASE_VALUE 0U

/*
 * Auxiliary PLL post divider 1 value
 * value when SCG_APLLCFG[PLLPOSTDIV1]=0.
 */
#define SCG_APLL_POSTDIV1_BASE_VALUE 1U

/*
 * Auxiliary PLL post divider 2 value
 * value when SCG_APLLCFG[PLLPOSTDIV2]=0.
 */
#define SCG_APLL_POSTDIV2_BASE_VALUE 1U

#define SCG_CSR_SCS_VAL ((SCG->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT)
#define SCG_SOSCDIV_SOSCDIV1_VAL ((SCG->SOSCDIV & SCG_SOSCDIV_SOSCDIV1_MASK) >> SCG_SOSCDIV_SOSCDIV1_SHIFT)
#define SCG_SOSCDIV_SOSCDIV2_VAL ((SCG->SOSCDIV & SCG_SOSCDIV_SOSCDIV2_MASK) >> SCG_SOSCDIV_SOSCDIV2_SHIFT)
#define SCG_SOSCDIV_SOSCDIV3_VAL ((SCG->SOSCDIV & SCG_SOSCDIV_SOSCDIV3_MASK) >> SCG_SOSCDIV_SOSCDIV3_SHIFT)
#define SCG_SIRCDIV_SIRCDIV1_VAL ((SCG->SIRCDIV & SCG_SIRCDIV_SIRCDIV1_MASK) >> SCG_SIRCDIV_SIRCDIV1_SHIFT)
#define SCG_SIRCDIV_SIRCDIV2_VAL ((SCG->SIRCDIV & SCG_SIRCDIV_SIRCDIV2_MASK) >> SCG_SIRCDIV_SIRCDIV2_SHIFT)
#define SCG_SIRCDIV_SIRCDIV3_VAL ((SCG->SIRCDIV & SCG_SIRCDIV_SIRCDIV3_MASK) >> SCG_SIRCDIV_SIRCDIV3_SHIFT)
#define SCG_FIRCDIV_FIRCDIV1_VAL ((SCG->FIRCDIV & SCG_FIRCDIV_FIRCDIV1_MASK) >> SCG_FIRCDIV_FIRCDIV1_SHIFT)
#define SCG_FIRCDIV_FIRCDIV2_VAL ((SCG->FIRCDIV & SCG_FIRCDIV_FIRCDIV2_MASK) >> SCG_FIRCDIV_FIRCDIV2_SHIFT)
#define SCG_FIRCDIV_FIRCDIV3_VAL ((SCG->FIRCDIV & SCG_FIRCDIV_FIRCDIV3_MASK) >> SCG_FIRCDIV_FIRCDIV3_SHIFT)

#define SCG_SPLLDIV_SPLLDIV1_VAL ((SCG->SPLLDIV & SCG_SPLLDIV_SPLLDIV1_MASK) >> SCG_SPLLDIV_SPLLDIV1_SHIFT)
#define SCG_SPLLDIV_SPLLDIV2_VAL ((SCG->SPLLDIV & SCG_SPLLDIV_SPLLDIV2_MASK) >> SCG_SPLLDIV_SPLLDIV2_SHIFT)
#define SCG_SPLLDIV_SPLLDIV3_VAL ((SCG->SPLLDIV & SCG_SPLLDIV_SPLLDIV3_MASK) >> SCG_SPLLDIV_SPLLDIV3_SHIFT)

#define SCG_SIRCCFG_RANGE_VAL ((SCG->SIRCCFG & SCG_SIRCCFG_RANGE_MASK) >> SCG_SIRCCFG_RANGE_SHIFT)
#define SCG_FIRCCFG_RANGE_VAL ((SCG->FIRCCFG & SCG_FIRCCFG_RANGE_MASK) >> SCG_FIRCCFG_RANGE_SHIFT)

#define SCG_SPLLCFG_PREDIV_VAL ((SCG->SPLLCFG & SCG_SPLLCFG_PREDIV_MASK) >> SCG_SPLLCFG_PREDIV_SHIFT)
#define SCG_SPLLCFG_MULT_VAL ((SCG->SPLLCFG & SCG_SPLLCFG_MULT_MASK) >> SCG_SPLLCFG_MULT_SHIFT)
#define SCG_SPLLPFD_PFD_MAX_VAL (SCG_SPLLPFD_PFD0_MASK >> SCG_SPLLPFD_PFD0_SHIFT)

#define SCG_APLLCFG_PREDIV_VAL ((SCG->APLLCFG & SCG_APLLCFG_PREDIV_MASK) >> SCG_APLLCFG_PREDIV_SHIFT)
#define SCG_APLLCFG_MULT_VAL ((SCG->APLLCFG & SCG_APLLCFG_MULT_MASK) >> SCG_APLLCFG_MULT_SHIFT)
#define SCG_APLLNUM_NUM_VAL (((uint64_t)SCG->APLLNUM & SCG_APLLNUM_NUM_MASK) >> SCG_APLLNUM_NUM_SHIFT)
#define SCG_APLLDENOM_DENOM_VAL ((SCG->APLLDENOM & SCG_APLLDENOM_DENOM_MASK) >> SCG_APLLDENOM_DENOM_SHIFT)
#define SCG_APLLPFD_PFD_MAX_VAL (SCG_APLLPFD_PFD0_MASK >> SCG_SPLLPFD_PFD0_SHIFT)
#define SCG_APLLCFG_POSTDIV1_VAL ((SCG->APLLCFG & SCG_APLLCFG_PLLPOSTDIV1_MASK) >> SCG_APLLCFG_PLLPOSTDIV1_SHIFT)
#define SCG_APLLCFG_POSTDIV2_VAL ((SCG->APLLCFG & SCG_APLLCFG_PLLPOSTDIV2_MASK) >> SCG_APLLCFG_PLLPOSTDIV2_SHIFT)
#define SCG_APLLDIV_APLLDIV1_VAL ((SCG->APLLDIV & SCG_APLLDIV_APLLDIV1_MASK) >> SCG_APLLDIV_APLLDIV1_SHIFT)
#define SCG_APLLDIV_APLLDIV2_VAL ((SCG->APLLDIV & SCG_APLLDIV_APLLDIV2_MASK) >> SCG_APLLDIV_APLLDIV2_SHIFT)
#define SCG_APLLDIV_APLLDIV3_VAL ((SCG->APLLDIV & SCG_APLLDIV_APLLDIV3_MASK) >> SCG_APLLDIV_APLLDIV3_SHIFT)

/*
 * Constant used to calcul PLL PFD clock frequency
 * PFD Clock Frequency = PLL output frequency * 18/frac value
 */
#define PFD_FREQ_CALCUL_CONSTANT 18U

/*! @brief Bitfield values for general PCC registers. */
#define PCC_PCS_VAL(reg) (((reg)&PCC_CLKCFG_PCS_MASK) >> PCC_CLKCFG_PCS_SHIFT)
#define PCC_FRAC_VAL(reg) (((reg)&PCC_CLKCFG_FRAC_MASK) >> PCC_CLKCFG_FRAC_SHIFT)
#define PCC_PCD_VAL(reg) (((reg)&PCC_CLKCFG_PCD_MASK) >> PCC_CLKCFG_PCD_SHIFT)

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* System PLL multiplier array */
static const uint8_t s_spllMulti[] = {0U, 15U, 16U, 20U, 22U, 25U, 30U, 0U};

/* External XTAL0 (OSC0) clock frequency. */
volatile uint32_t g_xtal0Freq;
/* External XTAL32K clock frequency. */
volatile uint32_t g_xtal32Freq;
/* External LVDS pad clock frequency. */
volatile uint32_t g_lvdsFreq;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get the common Auxiliary PLL frequency for both RAW APLL output and APLL PFD output.
 *
 * The "raw" APLL output is the clkout divided by postdiv1-2 of APLL.
 * The "common" Auxiliary PLL frequency is the common part for both RAW APLL and APLL PFD output.
 * That is the frequency calculated based on the clock source which passes through POSTDIV & MULT.
 * "Common" APLL Frequency = Divided Reference Frequency * MULT
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
static uint32_t CLOCK_GetAuxPllCommonFreq(void);

/*!
 * @brief Get the common System PLL frequency for both RAW SPLL output and SPLL PFD output.
 *
 * The "raw" SPLL output is the clkout divided by postdiv1-2 of SAPLL.
 * The "common" System PLL frequency is the common part for both RAW SPLL and SPLL PFD output.
 * That is the frequency calculated based on the clock source which passes through POSTDIV & MULT.
 * "Common" SPLL Frequency = Divided Reference Frequency * MULT
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
static uint32_t CLOCK_GetSysPllCommonFreq(void);

/*******************************************************************************
 * Code
 ******************************************************************************/

/* Function Name : CLOCK_GetErClkFreq */
/*!
 * brief Get the external reference clock frequency (ERCLK).
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetErClkFreq(void)
{
    uint32_t freq;

    if ((SCG->SOSCCSR & SCG_SOSCCSR_SOSCEN_MASK) != 0UL)
    {
        /* Please call CLOCK_SetXtal0Freq base on board setting before using OSC0 clock. */
        assert(g_xtal0Freq);
        freq = g_xtal0Freq;
    }
    else
    {
        freq = 0U;
    }

    return freq;
}

/*!
 * brief Get the OSC 32K clock frequency (OSC32KCLK).
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetOsc32kClkFreq(void)
{
    assert(g_xtal32Freq);
    return g_xtal32Freq;
}

/*!
 * brief Get the external LVDS pad clock frequency (LVDS).
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetLvdsClkFreq(void)
{
    assert(g_lvdsFreq);
    return g_lvdsFreq;
}

/*!
 * brief Get the slow clock frequency.
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetSlowClkFreq(void)
{
    return CLOCK_GetSysClkFreq(kSCG_SysClkSlow);
}

/*!
 * brief Get the bus clock frequency.
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetBusClkFreq(void)
{
    return CLOCK_GetSysClkFreq(kSCG_SysClkBus);
}

/*!
 * brief Get the external clock frequency.
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetExtClkFreq(void)
{
    return CLOCK_GetSysClkFreq(kSCG_SysClkExt);
}

/*!
 * brief Get the platform clock frequency.
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetPlatClkFreq(void)
{
    return CLOCK_GetSysClkFreq(kSCG_SysClkPlat);
}

/*!
 * brief Get the core clock or system clock frequency.
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetCoreSysClkFreq(void)
{
    return CLOCK_GetSysClkFreq(kSCG_SysClkCore);
}

/*!
 * brief Gets the clock frequency for a specific clock name.
 *
 * This function checks the current clock configurations and then calculates
 * the clock frequency for a specific clock name defined in clock_name_t.
 *
 * param clockName Clock names defined in clock_name_t
 * return Clock frequency value in hertz
 */
uint32_t CLOCK_GetFreq(clock_name_t clockName)
{
    uint32_t freq;

    switch (clockName)
    {
        case kCLOCK_CoreSysClk:
            freq = CLOCK_GetSysClkFreq(kSCG_SysClkCore);
            break;
        case kCLOCK_PlatClk:
            freq = CLOCK_GetSysClkFreq(kSCG_SysClkPlat);
            break;
        case kCLOCK_ExtClk:
            freq = CLOCK_GetSysClkFreq(kSCG_SysClkExt);
            break;
        case kCLOCK_BusClk:
            freq = CLOCK_GetSysClkFreq(kSCG_SysClkBus);
            break;
        case kCLOCK_SlowClk:
            freq = CLOCK_GetSysClkFreq(kSCG_SysClkSlow);
            break;

        case kCLOCK_ScgSysOscClk:
            freq = CLOCK_GetSysOscFreq();
            break;
        case kCLOCK_ScgSircClk:
            freq = CLOCK_GetSircFreq();
            break;
        case kCLOCK_ScgFircClk:
            freq = CLOCK_GetFircFreq();
            break;
        case kCLOCK_ScgSysPllClk:
            freq = CLOCK_GetSysPllFreq();
            break;
        case kCLOCK_ScgAuxPllClk:
            freq = CLOCK_GetAuxPllFreq();
            break;

        case kCLOCK_ScgSysOscAsyncDiv1Clk:
            freq = CLOCK_GetSysOscAsyncFreq(kSCG_AsyncDiv1Clk);
            break;
        case kCLOCK_ScgSysOscAsyncDiv2Clk:
            freq = CLOCK_GetSysOscAsyncFreq(kSCG_AsyncDiv2Clk);
            break;
        case kCLOCK_ScgSysOscAsyncDiv3Clk:
            freq = CLOCK_GetSysOscAsyncFreq(kSCG_AsyncDiv3Clk);
            break;

        case kCLOCK_ScgSircAsyncDiv1Clk:
            freq = CLOCK_GetSircAsyncFreq(kSCG_AsyncDiv1Clk);
            break;
        case kCLOCK_ScgSircAsyncDiv2Clk:
            freq = CLOCK_GetSircAsyncFreq(kSCG_AsyncDiv2Clk);
            break;
        case kCLOCK_ScgSircAsyncDiv3Clk:
            freq = CLOCK_GetSircAsyncFreq(kSCG_AsyncDiv3Clk);
            break;

        case kCLOCK_ScgFircAsyncDiv1Clk:
            freq = CLOCK_GetFircAsyncFreq(kSCG_AsyncDiv1Clk);
            break;
        case kCLOCK_ScgFircAsyncDiv2Clk:
            freq = CLOCK_GetFircAsyncFreq(kSCG_AsyncDiv2Clk);
            break;
        case kCLOCK_ScgFircAsyncDiv3Clk:
            freq = CLOCK_GetFircAsyncFreq(kSCG_AsyncDiv3Clk);
            break;

        case kCLOCK_ScgSysPllPfd0Clk:
            freq = CLOCK_GetSysPllPfdFreq(kSCG_SysPllPfd0Clk);
            break;
        case kCLOCK_ScgSysPllPfd1Clk:
            freq = CLOCK_GetSysPllPfdFreq(kSCG_SysPllPfd1Clk);
            break;
        case kCLOCK_ScgSysPllPfd2Clk:
            freq = CLOCK_GetSysPllPfdFreq(kSCG_SysPllPfd2Clk);
            break;
        case kCLOCK_ScgSysPllPfd3Clk:
            freq = CLOCK_GetSysPllPfdFreq(kSCG_SysPllPfd3Clk);
            break;

        case kCLOCK_ScgAuxPllPfd0Clk:
            freq = CLOCK_GetAuxPllPfdFreq(kSCG_AuxPllPfd0Clk);
            break;
        case kCLOCK_ScgAuxPllPfd1Clk:
            freq = CLOCK_GetAuxPllPfdFreq(kSCG_AuxPllPfd1Clk);
            break;
        case kCLOCK_ScgAuxPllPfd2Clk:
            freq = CLOCK_GetAuxPllPfdFreq(kSCG_AuxPllPfd2Clk);
            break;
        case kCLOCK_ScgAuxPllPfd3Clk:
            freq = CLOCK_GetAuxPllPfdFreq(kSCG_AuxPllPfd3Clk);
            break;

        case kCLOCK_ScgSysPllAsyncDiv1Clk:
            freq = CLOCK_GetSysPllAsyncFreq(kSCG_AsyncDiv1Clk);
            break;
        case kCLOCK_ScgSysPllAsyncDiv2Clk:
            freq = CLOCK_GetSysPllAsyncFreq(kSCG_AsyncDiv2Clk);
            break;
        case kCLOCK_ScgSysPllAsyncDiv3Clk:
            freq = CLOCK_GetSysPllAsyncFreq(kSCG_AsyncDiv3Clk);
            break;

        case kCLOCK_ScgAuxPllAsyncDiv1Clk:
            freq = CLOCK_GetAuxPllAsyncFreq(kSCG_AsyncDiv1Clk);
            break;
        case kCLOCK_ScgAuxPllAsyncDiv2Clk:
            freq = CLOCK_GetAuxPllAsyncFreq(kSCG_AsyncDiv2Clk);
            break;
        case kCLOCK_ScgAuxPllAsyncDiv3Clk:
            freq = CLOCK_GetAuxPllAsyncFreq(kSCG_AsyncDiv3Clk);
            break;

        case kCLOCK_LpoClk:
            freq = LPO_CLK_FREQ;
            break;
        case kCLOCK_Osc32kClk:
            freq = CLOCK_GetOsc32kClkFreq();
            break;
        case kCLOCK_ErClk:
            freq = CLOCK_GetErClkFreq();
            break;
        case kCLOCK_LvdsClk:
            freq = CLOCK_GetLvdsClkFreq();
            break;
        default:
            freq = 0U;
            break;
    }
    return freq;
}

/* Function Name : CLOCK_GetIpFreq */
/*!
 * brief Gets the clock frequency for a specific IP module.
 *
 * This function gets the IP module clock frequency based on PCC registers. It is
 * only used for the IP modules which could select clock source by PCC[PCS].
 *
 * param name Which peripheral to get, see \ref clock_ip_name_t.
 * return Clock frequency value in hertz
 */
uint32_t CLOCK_GetIpFreq(clock_ip_name_t name)
{
    uint32_t reg = (*(volatile uint32_t *)(uint32_t)name);

    scg_async_clk_t asycClk;
    scg_sys_clk_t sysClk;
    uint32_t freq;

    assert(reg & PCC_CLKCFG_PR_MASK);

    if (kCLOCK_Tpiu == name)
    {
        freq = TPIU_CLK_FREQ;
    }
    else
    {
        /* QSPI uses SCG DIV1 clock, while the others use SCG DIV2 clock. */
        if (kCLOCK_Qspi == name)
        {
            sysClk  = kSCG_SysClkPlat;
            asycClk = kSCG_AsyncDiv1Clk;
        }
        else
        {
            sysClk  = kSCG_SysClkBus;
            asycClk = kSCG_AsyncDiv2Clk;
        }

        switch (PCC_PCS_VAL(reg))
        {
            case (uint32_t)kCLOCK_IpSrcNone:
                freq = 0U;
                break;
            case (uint32_t)kCLOCK_IpSrcPllPfdAsync:
                if (kCLOCK_Qspi == name)
                {
                    freq = CLOCK_GetSysPllPfdFreq(kSCG_SysPllPfd3Clk);
                }
                else
                {
                    freq = CLOCK_GetAuxPllPfdFreq(kSCG_AuxPllPfd0Clk);
                }
                break;
            case (uint32_t)kCLOCK_IpSrcSysPllAsync:
                if (kCLOCK_Qspi == name)
                {
                    freq = CLOCK_GetSysPllFreq();
                }
                else
                {
                    freq = CLOCK_GetSysPllAsyncFreq(asycClk);
                }
                break;
            case (uint32_t)kCLOCK_IpSrcSystem:
                freq = CLOCK_GetSysClkFreq(sysClk);
                break;
            case (uint32_t)kCLOCK_IpSrcRtcAuxPllAsync:
                if (kCLOCK_Qspi == name)
                {
                    freq = CLOCK_GetRtcOscFreq();
                }
                else
                {
                    freq = CLOCK_GetAuxPllFreq();
                }
                break;
            case (uint32_t)kCLOCK_IpSrcFircAsync:
                freq = CLOCK_GetFircAsyncFreq(asycClk);
                break;
            case (uint32_t)kCLOCK_IpSrcSircAsync:
                freq = CLOCK_GetSircAsyncFreq(asycClk);
                break;
            case (uint32_t)kCLOCK_IpSrcSysOscAsync:
                freq = CLOCK_GetSysOscAsyncFreq(asycClk);
                break;
            default:
                freq = 0U;
                break;
        }
    }

    if ((kCLOCK_Sai0 == name) || (kCLOCK_Sai1 == name))
    {
        if ((reg & (PCC1_PCC_SAI1_PCD_MASK)) != 0UL)
        {
            return freq * (((reg & PCC1_PCC_SAI1_PCD_MASK) >> PCC1_PCC_SAI1_PCD_SHIFT) + 1U);
        }
        else
        {
            return freq;
        }
    }
    else
    {
        if ((reg & (PCC_CLKCFG_PCD_MASK | PCC_CLKCFG_FRAC_MASK)) != 0UL)
        {
            return freq * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
        }
        else
        {
            return freq;
        }
    }
}

/*!
 * brief Gets the SCG system clock frequency.
 *
 * This function gets the SCG system clock frequency. These clocks are used for
 * core, platform, external, and bus clock domains.
 *
 * param type     Which type of clock to get, core clock or slow clock.
 * return  Clock frequency.
 */
uint32_t CLOCK_GetSysClkFreq(scg_sys_clk_t type)
{
    uint32_t freq;

    scg_sys_clk_config_t sysClkConfig;

    CLOCK_GetCurSysClkConfig(&sysClkConfig);

    switch (sysClkConfig.src)
    {
        case (uint32_t)kSCG_SysClkSrcSysOsc:
            freq = CLOCK_GetSysOscFreq();
            break;
        case (uint32_t)kSCG_SysClkSrcSirc:
            freq = CLOCK_GetSircFreq();
            break;
        case (uint32_t)kSCG_SysClkSrcFirc:
            freq = CLOCK_GetFircFreq();
            break;
        case (uint32_t)kSCG_SysClkSrcRosc:
            freq = CLOCK_GetRtcOscFreq();
            break;
        case (uint32_t)kSCG_SysClkSrcAuxPll:
            freq = CLOCK_GetAuxPllFreq();
            break;
        case (uint32_t)kSCG_SysClkSrcSysPll:
            freq = CLOCK_GetSysPllFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    freq /= (sysClkConfig.divCore + 1U);

    if (kSCG_SysClkSlow == type)
    {
        freq /= (sysClkConfig.divSlow + 1U);
    }
    else if (kSCG_SysClkPlat == type)
    {
        freq /= (sysClkConfig.divPlat + 1U);
    }
    else if (kSCG_SysClkBus == type)
    {
        freq /= (sysClkConfig.divBus + 1U);
    }
    /*    else if (kSCG_SysClkExt == type)
        {
            freq /= (sysClkConfig.divExt + 1U);
        } */
    else
    {
        /* Add comment to prevent the case of rule 15.7. */
    }

    return freq;
}

/*!
 * brief Initializes the SCG system OSC.
 *
 * This function enables the SCG system OSC clock according to the
 * configuration.
 *
 * param config   Pointer to the configuration structure.
 * retval kStatus_Success System OSC is initialized.
 * retval kStatus_SCG_Busy System OSC has been enabled and is used by the system clock.
 * retval kStatus_ReadOnly System OSC control register is locked.
 *
 * note This function can't detect whether the system OSC has been enabled and
 * used by an IP.
 */
status_t CLOCK_InitSysOsc(const scg_sosc_config_t *config)
{
    assert(config);
    status_t status;

    /* De-init the SOSC first. */
    status = CLOCK_DeinitSysOsc();

    if (kStatus_Success != status)
    {
        return status;
    }

    /* Now start to set up OSC clock. */
    /* Step 1. Setup dividers. */
    SCG->SOSCDIV =
        SCG_SOSCDIV_SOSCDIV1(config->div1) | SCG_SOSCDIV_SOSCDIV2(config->div2) | SCG_SOSCDIV_SOSCDIV3(config->div3);

    /* Step 2. Set OSC configuration. */
    SCG->SOSCCFG = (uint32_t)(config->workMode);

    /* Step 3. Enable clock. */
    SCG->SOSCCSR = (uint32_t)SCG_SOSCCSR_SOSCEN_MASK | (config->enableMode);

    /* Step 4. Wait for OSC clock to be valid. */
    while (0UL == (SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK))
    {
    }

    /* Step 5. Enabe monitor. */
    SCG->SOSCCSR |= (uint32_t)config->monitorMode;

    return kStatus_Success;
}

/*!
 * brief De-initializes the SCG system OSC.
 *
 * This function disables the SCG system OSC clock.
 *
 * retval kStatus_Success System OSC is deinitialized.
 * retval kStatus_SCG_Busy System OSC is used by the system clock.
 * retval kStatus_ReadOnly System OSC control register is locked.
 *
 * note This function can't detect whether the system OSC is used by an IP.
 */
status_t CLOCK_DeinitSysOsc(void)
{
    uint32_t reg = SCG->SOSCCSR;
    status_t status;

    /* If clock is used by system, return error. */
    if ((reg & SCG_SOSCCSR_SOSCSEL_MASK) != 0UL)
    {
        status = kStatus_SCG_Busy;
    }
    /* If configure register is locked, return error. */
    else if ((reg & SCG_SOSCCSR_LK_MASK) != 0UL)
    {
        status = kStatus_ReadOnly;
    }
    else
    {
        SCG->SOSCCSR = SCG_SOSCCSR_SOSCERR_MASK;
        status       = kStatus_Success;
    }

    return status;
}

/*!
 * brief Gets the SCG system OSC clock frequency (SYSOSC).
 *
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetSysOscFreq(void)
{
    uint32_t freq;

    if ((SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK) != 0UL) /* System OSC clock is valid. */
    {
        /* Please call CLOCK_SetXtal0Freq base on board setting before using OSC0 clock. */
        assert(g_xtal0Freq);
        freq = g_xtal0Freq;
    }
    else
    {
        freq = 0U;
    }

    return freq;
}

/*!
 * brief Gets the SCG asynchronous clock frequency from the system OSC.
 *
 * param type     The asynchronous clock type.
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetSysOscAsyncFreq(scg_async_clk_t type)
{
    uint32_t oscFreq = CLOCK_GetSysOscFreq();
    uint32_t divider = 0U;
    uint32_t freq;

    /* Get divider. */
    if (oscFreq != 0UL)
    {
        switch (type)
        {
            case kSCG_AsyncDiv3Clk: /* SOSCDIV3_CLK. */
                divider = SCG_SOSCDIV_SOSCDIV3_VAL;
                break;
            case kSCG_AsyncDiv2Clk: /* SOSCDIV2_CLK. */
                divider = SCG_SOSCDIV_SOSCDIV2_VAL;
                break;
            case kSCG_AsyncDiv1Clk: /* SOSCDIV1_CLK. */
                divider = SCG_SOSCDIV_SOSCDIV1_VAL;
                break;
            default:
                divider = 0U;
                break;
        }
    }
    if (divider != 0UL)
    {
        freq = oscFreq >> (divider - 1U);
    }
    else /* Output disabled. */
    {
        freq = 0U;
    }

    return freq;
}

/*!
 * brief Initializes the SCG slow IRC clock.
 *
 * This function enables the SCG slow IRC clock according to the
 * configuration.
 *
 * param config   Pointer to the configuration structure.
 * retval kStatus_Success SIRC is initialized.
 * retval kStatus_SCG_Busy SIRC has been enabled and is used by system clock.
 * retval kStatus_ReadOnly SIRC control register is locked.
 *
 * note This function can't detect whether the system OSC has been enabled and
 * used by an IP.
 */
status_t CLOCK_InitSirc(const scg_sirc_config_t *config)
{
    assert(config);

    status_t status;

    /* De-init the SIRC first. */
    status = CLOCK_DeinitSirc();

    if (kStatus_Success != status)
    {
        return status;
    }

    /* Now start to set up SIRC clock. */
    /* Step 1. Setup dividers. */
    SCG->SIRCDIV =
        SCG_SIRCDIV_SIRCDIV1(config->div1) | SCG_SIRCDIV_SIRCDIV2(config->div2) | SCG_SIRCDIV_SIRCDIV3(config->div3);

    /* Step 2. Set SIRC configuration. */
    SCG->SIRCCFG = SCG_SIRCCFG_RANGE(config->range);

    /* Step 3. Enable clock. */
    SCG->SIRCCSR = SCG_SIRCCSR_SIRCEN_MASK | config->enableMode;

    /* Step 4. Wait for SIRC clock to be valid. */
    while (0UL == (SCG->SIRCCSR & SCG_SIRCCSR_SIRCVLD_MASK))
    {
    }

    return kStatus_Success;
}

/*!
 * brief De-initializes the SCG slow IRC.
 *
 * This function disables the SCG slow IRC.
 *
 * retval kStatus_Success SIRC is deinitialized.
 * retval kStatus_SCG_Busy SIRC is used by system clock.
 * retval kStatus_ReadOnly SIRC control register is locked.
 *
 * note This function can't detect whether the SIRC is used by an IP.
 */
status_t CLOCK_DeinitSirc(void)
{
    uint32_t reg = SCG->SIRCCSR;
    status_t status;

    /* If clock is used by system, return error. */
    if ((reg & SCG_SIRCCSR_SIRCSEL_MASK) != 0UL)
    {
        status = kStatus_SCG_Busy;
    }
    /* If configure register is locked, return error. */
    else if ((reg & SCG_SIRCCSR_LK_MASK) != 0UL)
    {
        status = kStatus_ReadOnly;
    }
    else
    {
        SCG->SIRCCSR = 0U;
        status       = kStatus_Success;
    }

    return status;
}

/*!
 * brief Gets the SCG SIRC clock frequency.
 *
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetSircFreq(void)
{
    static const uint32_t sircFreq[] = {SCG_SIRC_LOW_RANGE_FREQ, SCG_SIRC_HIGH_RANGE_FREQ};
    uint32_t freq;

    if ((SCG->SIRCCSR & SCG_SIRCCSR_SIRCVLD_MASK) != 0UL) /* SIRC is valid. */
    {
        freq = sircFreq[SCG_SIRCCFG_RANGE_VAL];
    }
    else
    {
        freq = 0U;
    }

    return freq;
}

/*!
 * brief Gets the SCG asynchronous clock frequency from the SIRC.
 *
 * param type     The asynchronous clock type.
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetSircAsyncFreq(scg_async_clk_t type)
{
    uint32_t sircFreq = CLOCK_GetSircFreq();
    uint32_t divider  = 0U;
    uint32_t freq;

    /* Get divider. */
    if (sircFreq != 0UL)
    {
        switch (type)
        {
            case kSCG_AsyncDiv3Clk: /* SIRCDIV3_CLK. */
                divider = SCG_SIRCDIV_SIRCDIV3_VAL;
                break;
            case kSCG_AsyncDiv2Clk: /* SIRCDIV2_CLK. */
                divider = SCG_SIRCDIV_SIRCDIV2_VAL;
                break;
            case kSCG_AsyncDiv1Clk: /* SIRCDIV2_CLK. */
                divider = SCG_SIRCDIV_SIRCDIV1_VAL;
                break;
            default:
                divider = 0U;
                break;
        }
    }
    if (divider != 0UL)
    {
        freq = sircFreq >> (divider - 1U);
    }
    else /* Output disabled. */
    {
        freq = 0U;
    }

    return freq;
}

/*!
 * brief Initializes the SCG fast IRC clock.
 *
 * This function enables the SCG fast IRC clock according to the configuration.
 *
 * param config   Pointer to the configuration structure.
 * retval kStatus_Success FIRC is initialized.
 * retval kStatus_SCG_Busy FIRC has been enabled and is used by the system clock.
 * retval kStatus_ReadOnly FIRC control register is locked.
 *
 * note This function can't detect whether the FIRC has been enabled and
 * used by an IP.
 */
status_t CLOCK_InitFirc(const scg_firc_config_t *config)
{
    assert(config);

    status_t status;

    /* De-init the FIRC first. */
    status = CLOCK_DeinitFirc();

    if (kStatus_Success != status)
    {
        return status;
    }

    /* Now start to set up FIRC clock. */
    /* Step 1. Setup dividers. */
    SCG->FIRCDIV =
        SCG_FIRCDIV_FIRCDIV1(config->div1) | SCG_FIRCDIV_FIRCDIV2(config->div2) | SCG_FIRCDIV_FIRCDIV3(config->div3);

    /* Step 2. Set FIRC configuration. */
    SCG->FIRCCFG = SCG_FIRCCFG_RANGE(config->range);

    /* Step 3. Set trimming configuration. */
    if ((config->trimConfig) != NULL)
    {
        SCG->FIRCTCFG =
            SCG_FIRCTCFG_TRIMDIV(config->trimConfig->trimDiv) | SCG_FIRCTCFG_TRIMSRC(config->trimConfig->trimSrc);

        /* TODO: Write FIRCSTAT cause bus error: TKT266932. */
        if (kSCG_FircTrimNonUpdate == config->trimConfig->trimMode)
        {
            SCG->FIRCSTAT = SCG_FIRCSTAT_TRIMCOAR(config->trimConfig->trimCoar) |
                            SCG_FIRCSTAT_TRIMFINE(config->trimConfig->trimFine);
        }

        /* trim mode. */
        SCG->FIRCCSR = (uint32_t)(config->trimConfig->trimMode);

        if ((SCG->FIRCCSR & SCG_FIRCCSR_FIRCERR_MASK) != 0UL)
        {
            return kStatus_Fail;
        }
    }

    /* Step 4. Enable clock. */
    SCG->FIRCCSR |= (SCG_FIRCCSR_FIRCEN_MASK | config->enableMode);

    /* Step 5. Wait for FIRC clock to be valid. */
    while (0UL == (SCG->FIRCCSR & SCG_FIRCCSR_FIRCVLD_MASK))
    {
    }

    return kStatus_Success;
}

/*!
 * brief De-initializes the SCG fast IRC.
 *
 * This function disables the SCG fast IRC.
 *
 * retval kStatus_Success FIRC is deinitialized.
 * retval kStatus_SCG_Busy FIRC is used by the system clock.
 * retval kStatus_ReadOnly FIRC control register is locked.
 *
 * note This function can't detect whether the FIRC is used by an IP.
 */
status_t CLOCK_DeinitFirc(void)
{
    uint32_t reg = SCG->FIRCCSR;
    status_t status;

    /* If clock is used by system, return error. */
    if ((reg & SCG_FIRCCSR_FIRCSEL_MASK) != 0UL)
    {
        status = kStatus_SCG_Busy;
    }
    /* If configure register is locked, return error. */
    else if ((reg & SCG_FIRCCSR_LK_MASK) != 0UL)
    {
        status = kStatus_ReadOnly;
    }
    else
    {
        SCG->FIRCCSR = SCG_FIRCCSR_FIRCERR_MASK;
        status       = kStatus_Success;
    }

    return status;
}

/*!
 * brief Gets the SCG FIRC clock frequency.
 *
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetFircFreq(void)
{
    static const uint32_t fircFreq[] = {
        SCG_FIRC_FREQ0,
        SCG_FIRC_FREQ1,
        SCG_FIRC_FREQ2,
        SCG_FIRC_FREQ3,
    };
    uint32_t freq;

    if ((SCG->FIRCCSR & SCG_FIRCCSR_FIRCVLD_MASK) != 0UL) /* FIRC is valid. */
    {
        freq = fircFreq[SCG_FIRCCFG_RANGE_VAL];
    }
    else
    {
        freq = 0U;
    }

    return freq;
}

/*!
 * brief Gets the SCG asynchronous clock frequency from the FIRC.
 *
 * param type     The asynchronous clock type.
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetFircAsyncFreq(scg_async_clk_t type)
{
    uint32_t fircFreq = CLOCK_GetFircFreq();
    uint32_t divider  = 0U;
    uint32_t freq;

    /* Get divider. */
    if (fircFreq != 0UL)
    {
        switch (type)
        {
            case kSCG_AsyncDiv3Clk: /* FIRCDIV3_CLK. */
                divider = SCG_FIRCDIV_FIRCDIV3_VAL;
                break;
            case kSCG_AsyncDiv2Clk: /* FIRCDIV2_CLK. */
                divider = SCG_FIRCDIV_FIRCDIV2_VAL;
                break;
            case kSCG_AsyncDiv1Clk: /* FIRCDIV1_CLK. */
                divider = SCG_FIRCDIV_FIRCDIV1_VAL;
                break;
            default:
                divider = 0U;
                break;
        }
    }
    if (divider != 0UL)
    {
        freq = fircFreq >> (divider - 1U);
    }
    else /* Output disabled. */
    {
        freq = 0U;
    }

    return freq;
}

/*!
 * brief Gets the SCG RTC OSC clock frequency.
 *
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetRtcOscFreq(void)
{
    uint32_t freq;

    if ((SCG->ROSCCSR & SCG_ROSCCSR_ROSCVLD_MASK) != 0UL) /* RTC OSC clock is valid. */
    {
        /* Please call CLOCK_SetXtal32Freq base on board setting before using RTC OSC clock. */
        assert(g_xtal32Freq);
        freq = g_xtal32Freq;
    }
    else
    {
        freq = 0U;
    }

    return freq;
}

/*!
 * brief Initializes the SCG auxiliary PLL.
 *
 * This function enables the SCG auxiliary PLL clock according to the
 * configuration. The auxiliary PLL can use the system OSC or FIRC as
 * the clock source. Ensure that the source clock is valid before
 * calling this function.
 *
 * Example code for initializing APLL clock output:
 * code
 * const scg_apll_config_t g_scgAuxPllConfig = {.enableMode = kSCG_AuxPllEnable,
 *                                            .div1 = kSCG_AsyncClkDisable,
 *                                            .div2 = kSCG_AsyncClkDisable,
 *                                            .div3 = kSCG_AsyncClkDisable,
 *                                            .src = kSCG_SysPllSrcFirc,
 *                                            .isPfdSelected = false,
 *                                            .prediv = 5U,
 *                                            .pfdClkout = kSCG_AuxPllPfd0Clk,
 *                                            .mult = 20U,
 *                                            .pllPostdiv1 = kSCG_SysClkDivBy3,
 *                                            .pllPostdiv2 = kSCG_SysClkDivBy4,
 *                                            .num = 578,
 *                                            .denom = 1000};
 * CLOCK_InitAuxPll(&g_scgAuxPllConfig);
 * endcode
 *
 * param config   Pointer to the configuration structure.
 * retval kStatus_Success auxiliary PLL is initialized.
 * retval kStatus_SCG_Busy auxiliary PLL has been enabled and is used by the system clock.
 * retval kStatus_ReadOnly auxiliary PLL control register is locked.
 *
 * note This function can't detect whether the auxiliary PLL has been enabled and
 * is used by an IP.
 */
status_t CLOCK_InitAuxPll(const scg_apll_config_t *config)
{
    assert(config);
    /* For i.MX 7ULP, valid MULT values are 33, 27, 22, 20, 17, 16. */
    assert((33U == config->mult) || (27U == config->mult) || (22U == config->mult) || (20U == config->mult) ||
           (17U == config->mult) || (16U == config->mult));

    status_t status;

    /* De-init the APLL first. */
    status = CLOCK_DeinitAuxPll();

    if (kStatus_Success != status)
    {
        return status;
    }

    /* Now start to set up PLL clock. */
    /* Step 1. Setup dividers. */
    SCG->APLLDIV =
        SCG_APLLDIV_APLLDIV1(config->div1) | SCG_APLLDIV_APLLDIV2(config->div2) | SCG_APLLDIV_APLLDIV3(config->div3);

    /* Step 2. Set PLL configuration. */
    SCG->APLLCFG = SCG_APLLCFG_SOURCE(config->src) | SCG_APLLCFG_PREDIV(config->prediv) |
                   SCG_APLLCFG_MULT(config->mult) | SCG_APLLCFG_PLLS(config->isPfdSelected) |
                   SCG_APLLCFG_PFDSEL(((uint32_t)config->pfdClkout) >> 3U) |
                   SCG_APLLCFG_PLLPOSTDIV1(config->pllPostdiv1) | SCG_APLLCFG_PLLPOSTDIV2(config->pllPostdiv2);

    /* Step 3. Set Numerator and Denominator. */
    SCG->APLLDENOM = config->denom;
    SCG->APLLNUM   = config->num;

    /* Step 4. Enable clock. */
    SCG->APLLCSR = (uint32_t)SCG_APLLCSR_APLLEN_MASK | config->enableMode;

    /* Step 5. Wait for PLL clock to be valid. */
    while (0UL == (SCG->APLLCSR & SCG_APLLCSR_APLLVLD_MASK))
    {
    }

    return kStatus_Success;
}

/*!
 * brief De-initializes the SCG auxiliary PLL.
 *
 * This function disables the SCG auxiliary PLL.
 *
 * retval kStatus_Success auxiliary PLL is deinitialized.
 * retval kStatus_SCG_Busy auxiliary PLL is used by the system clock.
 * retval kStatus_ReadOnly auxiliary PLL control register is locked.
 *
 * note This function can't detect whether the auxiliary PLL is used by an IP.
 */
status_t CLOCK_DeinitAuxPll(void)
{
    uint32_t reg = SCG->APLLCSR;
    status_t status;

    /* If clock is used by system, return error. */
    if ((reg & SCG_APLLCSR_APLLSEL_MASK) != 0UL)
    {
        status = kStatus_SCG_Busy;
    }
    /* If configure register is locked, return error. */
    else if ((reg & SCG_APLLCSR_LK_MASK) != 0UL)
    {
        status = kStatus_ReadOnly;
    }
    else
    {
        /* Deinit and clear the error. */
        SCG->APLLCSR = 0;
        status       = kStatus_Success;
    }

    return status;
}

static uint32_t CLOCK_GetAuxPllCommonFreq(void)
{
    uint32_t freq = 0U;
    uint64_t freqTmp;
    uint64_t apllnumTmp;

    if ((SCG->APLLCFG & SCG_APLLCFG_SOURCE_MASK) != 0UL) /* If use FIRC */
    {
        freq = CLOCK_GetFircFreq();
    }
    else /* Use System OSC. */
    {
        freq = CLOCK_GetSysOscFreq();
    }

    if (freq != 0UL) /* If source is valid. */
    {
        freq /= (SCG_APLLCFG_PREDIV_VAL + SCG_APLL_PREDIV_BASE_VALUE); /* Pre-divider. */
        apllnumTmp = SCG_APLLNUM_NUM_VAL;
        freqTmp    = (uint64_t)freq * (apllnumTmp) / (SCG_APLLDENOM_DENOM_VAL);
        freq       = freq * (SCG_APLLCFG_MULT_VAL + SCG_APLL_MULT_BASE_VALUE) + (uint32_t)freqTmp;
    }

    return freq;
}

/*!
 * brief Gets the SCG auxiliary PLL clock frequency.
 *
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetAuxPllFreq(void)
{
    uint32_t freq;
    scg_apll_pfd_clkout_t pfdClkout;

    if ((SCG->APLLCFG & SCG_APLLCFG_PLLS_MASK) != 0UL)
    {
        /* pfdClkout is SCG_APLLCFG[PFDSEL] x 8. */
        pfdClkout = (scg_apll_pfd_clkout_t)(uint32_t)(
            ((SCG->APLLCFG & SCG_APLLCFG_PFDSEL_MASK) >> SCG_APLLCFG_PFDSEL_SHIFT) << 3U);
        freq = CLOCK_GetAuxPllPfdFreq(pfdClkout);
    }
    else
    {
        if ((SCG->APLLCSR & SCG_APLLCSR_APLLVLD_MASK) != 0UL) /* Auxiliary PLL is valid. */
        {
            freq = CLOCK_GetAuxPllCommonFreq();

            if (freq != 0UL)
            {
                freq /= (SCG_APLLCFG_POSTDIV1_VAL + SCG_APLL_POSTDIV1_BASE_VALUE); /* Post-divider 1. */
                freq /= (SCG_APLLCFG_POSTDIV2_VAL + SCG_APLL_POSTDIV2_BASE_VALUE); /* Post-divider 2. */
            }

            return freq;
        }
        else
        {
            return 0U;
        }
    }

    return freq;
}

/*!
 * brief Gets the SCG asynchronous clock frequency from the auxiliary PLL.
 *
 * param type     The asynchronous clock type.
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetAuxPllAsyncFreq(scg_async_clk_t type)
{
    uint32_t pllFreq = CLOCK_GetAuxPllFreq();
    uint32_t divider = 0U;
    uint32_t freq;

    /* Get divider. */
    if (pllFreq != 0UL)
    {
        switch (type)
        {
            case kSCG_AsyncDiv3Clk: /* APLLDIV3_CLK. */
                divider = SCG_APLLDIV_APLLDIV3_VAL;
                break;
            case kSCG_AsyncDiv2Clk: /* APLLDIV2_CLK. */
                divider = SCG_APLLDIV_APLLDIV2_VAL;
                break;
            case kSCG_AsyncDiv1Clk: /* APLLDIV1_CLK. */
                divider = SCG_APLLDIV_APLLDIV1_VAL;
                break;
            default:
                divider = 0U;
                break;
        }
    }
    if (divider != 0UL)
    {
        freq = pllFreq >> (divider - 1U);
    }
    else /* Output disabled. */
    {
        freq = 0U;
    }

    return freq;
}

/*!
 * brief Gets the SCG auxiliary PLL PFD clock frequency.
 *
 * param pfdClkout     The selected PFD clocks out. See "scg_apll_pfd_clkout_t".
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetAuxPllPfdFreq(scg_apll_pfd_clkout_t pfdClkout)
{
    uint32_t freq      = 0U;
    uint32_t fracValue = 0U;

    if ((SCG->APLLPFD & SCG_PLLPFD_PFD_VALID_MASK(pfdClkout)) != 0UL) /* Auxiliary PLL PFD is valid. */
    {
        if (0UL == (SCG->APLLPFD & SCG_PLLPFD_PFD_CLKGATE_MASK(pfdClkout)))
        {
            fracValue = (SCG->APLLPFD & SCG_PLLPFD_PFD_MASK(pfdClkout)) >> (uint32_t)pfdClkout;

            if (fracValue != 0UL)
            {
                freq = CLOCK_GetAuxPllCommonFreq();

                if (freq != 0UL) /* If source is valid. */
                {
                    freq = (uint32_t)((uint64_t)freq * PFD_FREQ_CALCUL_CONSTANT /
                                      fracValue); /* PFD Clock Frequency = PLL output frequency * 18 / frac value. */
                }
            }
        }
        else
        {
            freq = 0U;
        }

        return freq;
    }
    else
    {
        return 0U;
    }
}

/*!
 * brief Enables the SCG auxiliary PLL Fractional Divide (PFD) clock out with configurations.
 *
 * APLL Frequency = Fref * (MULT + NUM/DENOM)
 * PFD Clock Frequency = PLL output frequency * 18/frac value
 *
 * Example code for configuring APLL as APLL PFD clock output:
 * code
 * const scg_apll_config_t g_scgAuxPllConfig = {.enableMode = kSCG_AuxPllEnable,
 *                                              .div1 = kSCG_AsyncClkDisable,
 *                                              .div2 = kSCG_AsyncClkDisable,
 *                                              .div3 = kSCG_AsyncClkDisable,
 *                                              .src = kSCG_SysPllSrcFirc,
 *                                              .isPfdSelected = true,
 *                                              .prediv = 5U,
 *                                              .pfdClkout = kSCG_AuxPllPfd3Clk,
 *                                              .mult = 20U,
 *                                              .pllPostdiv1 = kSCG_SysClkDivBy1,
 *                                              .pllPostdiv2 = kSCG_SysClkDivBy1,
 *                                              .num = 578,
 *                                              .denom = 1000};
 * CLOCK_InitAuxPll(&g_scgAuxPllConfig);
 * CLOCK_EnableAuxPllPfdClkout(g_scgAuxPllConfig.pfdClkout, 15U);
 * endcode
 *
 * param pfdClkout  APLL PFD clock out select.
 * param fracValue  Fractional Divider value. Recommended to be kept between 12-35 for all PFDs.
 */
void CLOCK_EnableAuxPllPfdClkout(scg_apll_pfd_clkout_t pfdClkout, uint8_t fracValue)
{
    /*
     * Input fractional divider value should have a maximum size of 6 bits (64U).
     * Note: It is recommended that PFD settings are kept between 12-35 for all PFDs.
     */
    assert(fracValue);
    assert(fracValue < SCG_APLLPFD_PFD_MAX_VAL);

    /* Step 1. Ungate PFD clock. */
    SCG->APLLPFD &= ~SCG_PLLPFD_PFD_CLKGATE_MASK(pfdClkout);

    /* Step 2. Program the new PFD value. */
    SCG->APLLPFD = (SCG->APLLPFD & ~SCG_PLLPFD_PFD_MASK(pfdClkout)) | SCG_PLLPFD_PFD_VAL(pfdClkout, fracValue);

    /* Step 3. Wait for PFD clock to be stable. */
    while (0UL == (SCG->APLLPFD & SCG_PLLPFD_PFD_VALID_MASK(pfdClkout)))
    {
    }
}

/*!
 * brief Initializes the SCG system PLL.
 *
 * This function enables the SCG system PLL clock according to the
 * configuration. The system PLL can use the system OSC or FIRC as
 * the clock source. Ensure that the source clock is valid before
 * calling this function.
 *
 * Example code for initializing SPLL clock output:
 * code
 * const scg_spll_config_t g_scgSysPllConfig = {.enableMode = kSCG_SysPllEnable,
 *                                              .div1 = kSCG_AsyncClkDivBy1,
 *                                              .div2 = kSCG_AsyncClkDisable,
 *                                              .div3 = kSCG_AsyncClkDivBy2,
 *                                              .src = kSCG_SysPllSrcFirc,
 *                                              .isPfdSelected = false,
 *                                              .prediv = 0U,
 *                                              .pfdClkout = kSCG_SysPllPfd0Clk,
 *                                              .mult = 3U};
 * CLOCK_InitSysPll(&g_scgSysPllConfig);
 * endcode
 *
 * param config   Pointer to the configuration structure.
 * retval kStatus_Success System PLL is initialized.
 * retval kStatus_SCG_Busy System PLL has been enabled and is used by the system clock.
 * retval kStatus_ReadOnly System PLL control register is locked.
 *
 * note This function can't detect whether the system PLL has been enabled and
 * used by an IP.
 */
status_t CLOCK_InitSysPll(const scg_spll_config_t *config)
{
    assert(config);
    assert(config->mult < 7U);

    status_t status;

    /* De-init the SPLL first. */
    status = CLOCK_DeinitSysPll();

    if (kStatus_Success != status)
    {
        return status;
    }

    /* Now start to set up PLL clock. */
    /* Step 1. Setup dividers. */
    SCG->SPLLDIV =
        SCG_SPLLDIV_SPLLDIV1(config->div1) | SCG_SPLLDIV_SPLLDIV2(config->div2) | SCG_SPLLDIV_SPLLDIV3(config->div3);

    /* Step 2. Set PLL configuration. */
    SCG->SPLLCFG = SCG_SPLLCFG_SOURCE(config->src) | SCG_SPLLCFG_PREDIV(config->prediv) |
                   SCG_SPLLCFG_MULT(config->mult) | SCG_SPLLCFG_PLLS(config->isPfdSelected) |
                   SCG_SPLLCFG_PFDSEL(((uint32_t)config->pfdClkout >> 3U));

    /* Step 3. Enable clock. */
    SCG->SPLLCSR = (uint32_t)SCG_SPLLCSR_SPLLEN_MASK | config->enableMode;

    /* Step 4. Wait for PLL clock to be valid. */
    while (0UL == (SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK))
    {
    }

    return kStatus_Success;
}

/*!
 * brief De-initializes the SCG system PLL.
 *
 * This function disables the SCG system PLL.
 *
 * retval kStatus_Success system PLL is deinitialized.
 * retval kStatus_SCG_Busy system PLL is used by the system clock.
 * retval kStatus_ReadOnly System PLL control register is locked.
 *
 * note This function can't detect whether the system PLL is used by an IP.
 */
status_t CLOCK_DeinitSysPll(void)
{
    uint32_t reg = SCG->SPLLCSR;
    status_t status;

    /* If clock is used by system, return error. */
    if ((reg & SCG_SPLLCSR_SPLLSEL_MASK) != 0UL)
    {
        status = kStatus_SCG_Busy;
    }
    /* If configure register is locked, return error. */
    else if ((reg & SCG_SPLLCSR_LK_MASK) != 0UL)
    {
        status = kStatus_ReadOnly;
    }
    else
    {
        /* Deinit and clear the error. */
        SCG->SPLLCSR = SCG_SPLLCSR_SPLLERR_MASK;
        status       = kStatus_Success;
    }

    return status;
}

static uint32_t CLOCK_GetSysPllCommonFreq(void)
{
    uint32_t freq = 0U;

    if ((SCG->SPLLCFG & SCG_SPLLCFG_SOURCE_MASK) != 0UL) /* If use FIRC */
    {
        freq = CLOCK_GetFircFreq();
    }
    else /* Use System OSC. */
    {
        freq = CLOCK_GetSysOscFreq();
    }

    if (freq != 0UL) /* If source is valid. */
    {
        freq /= (SCG_SPLLCFG_PREDIV_VAL + SCG_SPLL_PREDIV_BASE_VALUE); /* Pre-divider. */
        freq *= s_spllMulti[SCG_SPLLCFG_MULT_VAL];                     /* Multiplier. */
    }

    return freq;
}

/*!
 * brief Gets the SCG system PLL clock frequency.
 *
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetSysPllFreq(void)
{
    uint32_t freq;
    scg_spll_pfd_clkout_t pfdClkout;

    if ((SCG->SPLLCFG & SCG_SPLLCFG_PLLS_MASK) != 0UL)
    {
        /* pfdClkout is SCG_SPLLCFG[PFDSEL] x 8. */
        pfdClkout = (scg_spll_pfd_clkout_t)(uint32_t)(
            ((SCG->SPLLCFG & SCG_SPLLCFG_PFDSEL_MASK) >> SCG_SPLLCFG_PFDSEL_SHIFT) << 3U);
        freq = CLOCK_GetSysPllPfdFreq(pfdClkout);
    }
    else
    {
        if ((SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK) != 0UL) /* System PLL is valid. */
        {
            freq = CLOCK_GetSysPllCommonFreq();

            return freq;
        }
        else
        {
            return 0U;
        }
    }

    return freq;
}

/*!
 * brief Gets the SCG asynchronous clock frequency from the system PLL.
 *
 * param type     The asynchronous clock type.
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetSysPllAsyncFreq(scg_async_clk_t type)
{
    uint32_t pllFreq = CLOCK_GetSysPllFreq();
    uint32_t divider = 0U;
    uint32_t freq;

    /* Get divider. */
    if (pllFreq != 0UL)
    {
        switch (type)
        {
            case kSCG_AsyncDiv3Clk: /* SPLLDIV3_CLK. */
                divider = SCG_SPLLDIV_SPLLDIV3_VAL;
                break;
            case kSCG_AsyncDiv2Clk: /* SPLLDIV2_CLK. */
                divider = SCG_SPLLDIV_SPLLDIV2_VAL;
                break;
            case kSCG_AsyncDiv1Clk: /* SPLLDIV1_CLK. */
                divider = SCG_SPLLDIV_SPLLDIV1_VAL;
                break;
            default:
                divider = 0U;
                break;
        }
    }
    if (divider != 0UL)
    {
        freq = pllFreq >> (divider - 1U);
    }
    else /* Output disabled. */
    {
        freq = 0U;
    }

    return freq;
}

/*!
 * brief Gets the SCG system PLL PFD clock frequency.
 *
 * param pfdClkout     The selected PFD clock out. See "scg_spll_pfd_clkout_t".
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetSysPllPfdFreq(scg_spll_pfd_clkout_t pfdClkout)
{
    uint32_t freq      = 0U;
    uint32_t fracValue = 0U;

    if ((SCG->SPLLPFD & SCG_PLLPFD_PFD_VALID_MASK(pfdClkout)) != 0UL) /* System PLL PFD is valid. */
    {
        if (0UL == (SCG->SPLLPFD & SCG_PLLPFD_PFD_CLKGATE_MASK(pfdClkout)))
        {
            fracValue = (SCG->SPLLPFD & SCG_PLLPFD_PFD_MASK(pfdClkout)) >> (uint32_t)pfdClkout;

            if (fracValue != 0UL)
            {
                freq = CLOCK_GetSysPllCommonFreq();

                if (freq != 0UL) /* If source is valid. */
                {
                    freq = (uint32_t)((uint64_t)freq * PFD_FREQ_CALCUL_CONSTANT /
                                      fracValue); /* PFD Clock Frequency = PLL output frequency * 18 / frac value. */
                }
            }
        }
        else
        {
            freq = 0U;
        }

        return freq;
    }
    else
    {
        return 0U;
    }
}

/*!
 * brief Enables the SCG system PLL Fractional Divide (PFD) clock out with configurations.
 *
 * SPLL Frequency = Fref * (MULT + NUM/DENOM)
 * PFD Clock Frequency = PLL output frequency * 18/frac value
 *
 * code
 * Example code for configuring SPLL as SPLL PFD clock output:
 * const scg_spll_config_t g_scgSysPllConfig = {.enableMode = kSCG_SysPllEnable,
 *                                            .div1 = kSCG_AsyncClkDisable,
 *                                            .div2 = kSCG_AsyncClkDisable,
 *                                            .div3 = kSCG_AsyncClkDisable,
 *                                            .src = kSCG_SysPllSrcFirc,
 *                                            .isPfdSelected = true,
 *                                            .prediv = 5U,
 *                                            .pfdClkout = kSCG_AuxPllPfd3Clk,
 *                                            .mult = 20U};
 * CLOCK_InitSysPll(&g_scgSysPllConfig);
 * CLOCK_EnableSysPllPfdClkout(g_scgSysPllConfig.pfdClkout, 15U);
 * endcode
 *
 * param pfdClkout  SPLL PFD clock out select.
 * param fracValue  Fractional Divider value. Recommended to be kept between 12-35 for all PFDs.
 */
void CLOCK_EnableSysPllPfdClkout(scg_spll_pfd_clkout_t pfdClkout, uint8_t fracValue)
{
    /*
     * Input fractional divider value should have a maximum size of 6 bits (64U).
     * Note: It is recommended that PFD settings are kept between 12-35 for all PFDs.
     */
    assert(fracValue);
    assert(fracValue < SCG_SPLLPFD_PFD_MAX_VAL);

    /* Step 1. Ungate PFD clock. */
    SCG->SPLLPFD &= ~SCG_PLLPFD_PFD_CLKGATE_MASK(pfdClkout);

    /* Step 2. Program the new PFD value. */
    SCG->SPLLPFD = (SCG->SPLLPFD & ~SCG_PLLPFD_PFD_MASK(pfdClkout)) | SCG_PLLPFD_PFD_VAL(pfdClkout, fracValue);

    /* Step 3. Wait for PFD clock to be stable. */
    while (0UL == (SCG->SPLLPFD & SCG_PLLPFD_PFD_VALID_MASK(pfdClkout)))
    {
    }
}
