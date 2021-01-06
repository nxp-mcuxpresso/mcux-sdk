/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016 - 2017 , NXP
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

#define SCG_SIRC_LOW_RANGE_FREQ 2000000U  /* Slow IRC low range clock frequency. */
#define SCG_SIRC_HIGH_RANGE_FREQ 8000000U /* Slow IRC high range clock frequency.   */

#define SCG_FIRC_FREQ0 48000000U /* Fast IRC trimed clock frequency(48MHz). */
#define SCG_FIRC_FREQ1 52000000U /* Fast IRC trimed clock frequency(52MHz). */
#define SCG_FIRC_FREQ2 56000000U /* Fast IRC trimed clock frequency(56MHz). */
#define SCG_FIRC_FREQ3 60000000U /* Fast IRC trimed clock frequency(60MHz). */

#define SCG_LPFLL_FREQ0 48000000U  /* LPFLL trimed clock frequency(48MHz). */
#define SCG_LPFLL_FREQ1 72000000U  /* LPFLL trimed clock frequency(72MHz). */
#define SCG_LPFLL_FREQ2 96000000U  /* LPFLL trimed clock frequency(96MHz). */
#define SCG_LPFLL_FREQ3 120000000U /* LPFLL trimed clock frequency(120MHz). */

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

#define SCG_LPFLLDIV_LPFLLDIV1_VAL ((SCG->LPFLLDIV & SCG_LPFLLDIV_LPFLLDIV1_MASK) >> SCG_LPFLLDIV_LPFLLDIV1_SHIFT)
#define SCG_LPFLLDIV_LPFLLDIV2_VAL ((SCG->LPFLLDIV & SCG_LPFLLDIV_LPFLLDIV2_MASK) >> SCG_LPFLLDIV_LPFLLDIV2_SHIFT)
#define SCG_LPFLLDIV_LPFLLDIV3_VAL ((SCG->LPFLLDIV & SCG_LPFLLDIV_LPFLLDIV3_MASK) >> SCG_LPFLLDIV_LPFLLDIV3_SHIFT)

#define SCG_SIRCCFG_RANGE_VAL ((SCG->SIRCCFG & SCG_SIRCCFG_RANGE_MASK) >> SCG_SIRCCFG_RANGE_SHIFT)
#define SCG_FIRCCFG_RANGE_VAL ((SCG->FIRCCFG & SCG_FIRCCFG_RANGE_MASK) >> SCG_FIRCCFG_RANGE_SHIFT)

#define SCG_LPFLLCFG_FSEL_VAL ((SCG->LPFLLCFG & SCG_LPFLLCFG_FSEL_MASK) >> SCG_LPFLLCFG_FSEL_SHIFT)

/* Get the value of each field in PCC register. */
#define PCC_PCS_VAL(reg) (((reg)&PCC_CLKCFG_PCS_MASK) >> PCC_CLKCFG_PCS_SHIFT)
#define PCC_FRAC_VAL(reg) (((reg)&PCC_CLKCFG_FRAC_MASK) >> PCC_CLKCFG_FRAC_SHIFT)
#define PCC_PCD_VAL(reg) (((reg)&PCC_CLKCFG_PCD_MASK) >> PCC_CLKCFG_PCD_SHIFT)

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* External XTAL0 (OSC0) clock frequency. */
volatile uint32_t g_xtal0Freq;
/* External XTAL32K clock frequency. */
volatile uint32_t g_xtal32Freq;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

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
 * brief Get the flash clock frequency.
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetFlashClkFreq(void)
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
    return CLOCK_GetSysClkFreq(kSCG_SysClkSlow);
}

/*!
 * brief Get the platform clock frequency.
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetPlatClkFreq(void)
{
    return CLOCK_GetSysClkFreq(kSCG_SysClkCore);
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
 * brief Get the external clock frequency (EXTCLK).
 *
 * return Clock frequency in Hz.
 */
uint32_t CLOCK_GetExtClkFreq(void)
{
    return CLOCK_GetSysClkFreq(kSCG_SysClkExt);
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
        /* System layer clock. */
        case kCLOCK_CoreSysClk:
        case kCLOCK_PlatClk:
            freq = CLOCK_GetSysClkFreq(kSCG_SysClkCore);
            break;
        case kCLOCK_BusClk:
            freq = CLOCK_GetSysClkFreq(kSCG_SysClkBus);
            break;
        case kCLOCK_FlashClk:
            freq = CLOCK_GetSysClkFreq(kSCG_SysClkSlow);
            break;
        case kCLOCK_ExtClk:
            freq = CLOCK_GetSysClkFreq(kSCG_SysClkExt);
            break;
        case kCLOCK_ScgSircClk:
            freq = CLOCK_GetSircFreq();
            break;
        case kCLOCK_ScgFircClk:
            freq = CLOCK_GetFircFreq();
            break;
        case kCLOCK_ScgLpFllClk:
            freq = CLOCK_GetLpFllFreq();
            break;

        /* SIRC div clock. */
        case kCLOCK_ScgSircAsyncDiv1Clk:
            freq = CLOCK_GetSircAsyncFreq(kSCG_AsyncDiv1Clk);
            break;
        case kCLOCK_ScgSircAsyncDiv2Clk:
            freq = CLOCK_GetSircAsyncFreq(kSCG_AsyncDiv2Clk);
            break;
        case kCLOCK_ScgSircAsyncDiv3Clk:
            freq = CLOCK_GetSircAsyncFreq(kSCG_AsyncDiv3Clk);
            break;

        /* FIRC div clock. */
        case kCLOCK_ScgFircAsyncDiv1Clk:
            freq = CLOCK_GetFircAsyncFreq(kSCG_AsyncDiv1Clk);
            break;
        case kCLOCK_ScgFircAsyncDiv2Clk:
            freq = CLOCK_GetFircAsyncFreq(kSCG_AsyncDiv2Clk);
            break;
        case kCLOCK_ScgFircAsyncDiv3Clk:
            freq = CLOCK_GetFircAsyncFreq(kSCG_AsyncDiv3Clk);
            break;

        /* LPFLL div clock. */
        case kCLOCK_ScgSysLpFllAsyncDiv1Clk:
            freq = CLOCK_GetLpFllAsyncFreq(kSCG_AsyncDiv1Clk);
            break;
        case kCLOCK_ScgSysLpFllAsyncDiv2Clk:
            freq = CLOCK_GetLpFllAsyncFreq(kSCG_AsyncDiv2Clk);
            break;
        case kCLOCK_ScgSysLpFllAsyncDiv3Clk:
            freq = CLOCK_GetLpFllAsyncFreq(kSCG_AsyncDiv3Clk);
            break;

        /* Other clocks. */
        case kCLOCK_LpoClk:
            freq = CLOCK_GetLpoClkFreq();
            break;
        case kCLOCK_Osc32kClk:
            freq = CLOCK_GetOsc32kClkFreq();
            break;
        default:
            freq = 0U;
            break;
    }
    return freq;
}

/*!
 * brief Gets the functional clock frequency for a specific IP module.
 *
 * This function gets the IP module's functional clock frequency based on PCC
 * registers. It is only used for the IP modules which could select clock source
 * by PCC[PCS].
 *
 * param name Which peripheral to get, see \ref clock_ip_name_t.
 * return Clock frequency value in Hz
 */
uint32_t CLOCK_GetIpFreq(clock_ip_name_t name)
{
    uint32_t reg = (*(volatile uint32_t *)(uint32_t)name);

    scg_async_clk_t asycClk;
    uint32_t freq;

    assert(reg & PCC_CLKCFG_PR_MASK);

    switch (name)
    {
        case kCLOCK_Lpit0:
        case kCLOCK_Lpit1:
            asycClk = kSCG_AsyncDiv3Clk;
            break;
        case kCLOCK_Sdhc0:
        case kCLOCK_Usb0:
            asycClk = kSCG_AsyncDiv1Clk;
            break;
        default:
            asycClk = kSCG_AsyncDiv2Clk;
            break;
    }

    switch (PCC_PCS_VAL(reg))
    {
        case (uint8_t)kCLOCK_IpSrcSircAsync:
            freq = CLOCK_GetSircAsyncFreq(asycClk);
            break;
        case (uint8_t)kCLOCK_IpSrcFircAsync:
            freq = CLOCK_GetFircAsyncFreq(asycClk);
            break;
        case (uint8_t)kCLOCK_IpSrcLpFllAsync:
            freq = CLOCK_GetLpFllAsyncFreq(asycClk);
            break;
        default: /* kCLOCK_IpSrcNoneOrExt. */
            freq = 0U;
            break;
    }

    if (0U != (reg & (PCC_CLKCFG_PCD_MASK | PCC_CLKCFG_FRAC_MASK)))
    {
        return freq * (PCC_FRAC_VAL(reg) + 1U) / (PCC_PCD_VAL(reg) + 1U);
    }
    else
    {
        return freq;
    }
}

/*! brief Enable USB FS clock.
 *
 * param src  USB FS clock source.
 * param freq The frequency specified by src.
 * retval true The clock is set successfully.
 * retval false The clock source is invalid to get proper USB FS clock.
 */
bool CLOCK_EnableUsbfs0Clock(clock_usb_src_t src, uint32_t freq)
{
    bool ret = true;

    CLOCK_SetIpSrc(kCLOCK_Usb0, kCLOCK_IpSrcFircAsync);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable clock gate. */
    CLOCK_EnableClock(kCLOCK_Usb0);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    USBVREG->CTRL |= USBVREG_CTRL_EN_MASK;
    USB0->CONTROL &= (uint8_t)(~USB_CONTROL_DPPULLUPNONOTG_MASK);

    if (kCLOCK_UsbSrcIrc48M == src)
    {
        USB0->CLK_RECOVER_IRC_EN = 0x03U;
        USB0->CLK_RECOVER_CTRL |= USB_CLK_RECOVER_CTRL_CLOCK_RECOVER_EN_MASK;
        USB0->CLK_RECOVER_INT_EN = 0x00U;
    }
    return ret;
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

    CLOCK_GetCurSysClkConfig(&sysClkConfig); /* Get the main clock for SoC platform. */

    switch (sysClkConfig.src)
    {
        case (uint8_t)kSCG_SysClkSrcSirc:
            freq = CLOCK_GetSircFreq();
            break;
        case (uint8_t)kSCG_SysClkSrcFirc:
            freq = CLOCK_GetFircFreq();
            break;
        case (uint8_t)kSCG_SysClkSrcRosc:
            freq = CLOCK_GetRtcOscFreq();
            break;
        case (uint8_t)kSCG_SysClkSrcLpFll:
            freq = CLOCK_GetLpFllFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    freq /= (sysClkConfig.divCore + 1U); /* divided by the DIVCORE firstly. */

    if (kSCG_SysClkSlow == type)
    {
        freq /= (sysClkConfig.divSlow + 1U);
    }
    else if (kSCG_SysClkBus == type)
    {
        freq /= (sysClkConfig.divBus + 1U);
    }
    else if (kSCG_SysClkExt == type)
    {
        freq /= (sysClkConfig.divExt + 1U);
    }
    else
    {
        /* Add comment to prevent the case of rule 15.7. */
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

    /* If clock is used by system, return error. */
    if ((reg & SCG_SIRCCSR_SIRCSEL_MASK) != 0UL)
    {
        return kStatus_SCG_Busy;
    }

    /* If configure register is locked, return error. */
    if ((reg & SCG_SIRCCSR_LK_MASK) != 0UL)
    {
        return kStatus_ReadOnly;
    }

    SCG->SIRCCSR = 0U;

    return kStatus_Success;
}

/*!
 * brief Gets the SCG SIRC clock frequency.
 *
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetSircFreq(void)
{
    static const uint32_t sircFreq[] = {SCG_SIRC_LOW_RANGE_FREQ, SCG_SIRC_HIGH_RANGE_FREQ};

    if ((SCG->SIRCCSR & SCG_SIRCCSR_SIRCVLD_MASK) != 0UL) /* SIRC is valid. */
    {
        return sircFreq[SCG_SIRCCFG_RANGE_VAL];
    }
    else
    {
        return 0U;
    }
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
    if (divider != 0U)
    {
        return sircFreq >> (divider - 1U);
    }
    else /* Output disabled. */
    {
        return 0U;
    }
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
        SCG->FIRCTCFG = SCG_FIRCTCFG_TRIMSRC(config->trimConfig->trimSrc);

        /* TODO: Write FIRCSTAT cause bus error: TKT266932. */
        if (kSCG_FircTrimNonUpdate == config->trimConfig->trimMode)
        {
            SCG->FIRCSTAT = SCG_FIRCSTAT_TRIMCOAR(config->trimConfig->trimCoar) |
                            SCG_FIRCSTAT_TRIMFINE(config->trimConfig->trimFine);
        }

        /* trim mode. */
        SCG->FIRCCSR = (uint32_t)(config->trimConfig->trimMode);

        if ((SCG->FIRCCSR & SCG_FIRCCSR_FIRCERR_MASK) != 0U)
        {
            return kStatus_Fail;
        }
    }

    /* Step 4. Enable clock. */
    SCG->FIRCCSR |= (SCG_FIRCCSR_FIRCEN_MASK | SCG_FIRCCSR_FIRCTREN_MASK | config->enableMode);

    /* Step 5. Wait for FIRC clock to be valid. */
    while (0U == (SCG->FIRCCSR & SCG_FIRCCSR_FIRCVLD_MASK))
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

    /* If clock is used by system, return error. */
    if ((reg & SCG_FIRCCSR_FIRCSEL_MASK) != 0UL)
    {
        return kStatus_SCG_Busy;
    }

    /* If configure register is locked, return error. */
    if ((reg & SCG_FIRCCSR_LK_MASK) != 0UL)
    {
        return kStatus_ReadOnly;
    }

    SCG->FIRCCSR = SCG_FIRCCSR_FIRCERR_MASK;

    return kStatus_Success;
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

    if ((SCG->FIRCCSR & SCG_FIRCCSR_FIRCVLD_MASK) != 0UL) /* FIRC is valid. */
    {
        return fircFreq[SCG_FIRCCFG_RANGE_VAL];
    }
    else
    {
        return 0U;
    }
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
        return fircFreq >> (divider - 1U);
    }
    else /* Output disabled. */
    {
        return 0U;
    }
}

/*!
 * brief Gets the SCG RTC OSC clock frequency.
 *
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetRtcOscFreq(void)
{
    if ((SCG->ROSCCSR & SCG_ROSCCSR_ROSCVLD_MASK) != 0UL) /* RTC OSC clock is valid. */
    {
        /* Please call CLOCK_SetXtal32Freq base on board setting before using RTC OSC clock. */
        assert(g_xtal32Freq);
        return g_xtal32Freq;
    }
    else
    {
        return 0U;
    }
}

/*!
 * brief Initializes the SCG LPFLL clock.
 *
 * This function enables the SCG LPFLL clock according to the configuration.
 *
 * param config   Pointer to the configuration structure.
 * retval kStatus_Success LPFLL is initialized.
 * retval kStatus_SCG_Busy LPFLL has been enabled and is used by the system clock.
 * retval kStatus_ReadOnly LPFLL control register is locked.
 *
 * note This function can't detect whether the LPFLL has been enabled and
 * used by an IP.
 */
status_t CLOCK_InitLpFll(const scg_lpfll_config_t *config)
{
    assert(config);

    status_t status;

    /* De-init the LPFLL first. */
    status = CLOCK_DeinitLpFll();

    if (kStatus_Success != status)
    {
        return status;
    }

    /* Now start to set up LPFLL clock. */
    /* Step 1. Setup dividers. */
    SCG->LPFLLDIV = SCG_LPFLLDIV_LPFLLDIV1(config->div1) | SCG_LPFLLDIV_LPFLLDIV2(config->div2) |
                    SCG_LPFLLDIV_LPFLLDIV3(config->div3);

    /* Step 2. Set LPFLL configuration. */
    SCG->LPFLLCFG = SCG_LPFLLCFG_FSEL(config->range);

    /* Step 3. Set trimming configuration. */
    if ((config->trimConfig) != NULL)
    {
        SCG->LPFLLTCFG = SCG_LPFLLTCFG_TRIMDIV(config->trimConfig->trimDiv) |
                         SCG_LPFLLTCFG_TRIMSRC(config->trimConfig->trimSrc) |
                         SCG_LPFLLTCFG_LOCKW2LSB(config->trimConfig->lockMode);

        if (kSCG_LpFllTrimNonUpdate == config->trimConfig->trimMode)
        {
            SCG->LPFLLSTAT = config->trimConfig->trimValue;
        }

        /* Trim mode. */
        SCG->LPFLLCSR = (uint32_t)(config->trimConfig->trimMode);

        if ((SCG->LPFLLCSR & SCG_LPFLLCSR_LPFLLERR_MASK) != 0UL)
        {
            return kStatus_Fail;
        }
    }

    /* Step 4. Enable clock. */
    SCG->LPFLLCSR |= ((uint32_t)SCG_LPFLLCSR_LPFLLEN_MASK | (uint32_t)config->enableMode);

    /* Step 5. Wait for LPFLL clock to be valid. */
    while (0UL == (SCG->LPFLLCSR & SCG_LPFLLCSR_LPFLLVLD_MASK))
    {
    }

    /* Step 6. Wait for LPFLL trim lock. */
    if ((config->trimConfig != NULL) && (kSCG_LpFllTrimUpdate == config->trimConfig->trimMode))
    {
        while (0UL == (SCG->LPFLLCSR & SCG_LPFLLCSR_LPFLLTRMLOCK_MASK))
        {
        }
    }

    return kStatus_Success;
}

/*!
 * brief De-initializes the SCG LPFLL.
 *
 * This function disables the SCG LPFLL.
 *
 * retval kStatus_Success LPFLL is deinitialized.
 * retval kStatus_SCG_Busy LPFLL is used by the system clock.
 * retval kStatus_ReadOnly LPFLL control register is locked.
 *
 * note This function can't detect whether the LPFLL is used by an IP.
 */
status_t CLOCK_DeinitLpFll(void)
{
    uint32_t reg = SCG->LPFLLCSR;

    /* If clock is used by system, return error. */
    if ((reg & SCG_LPFLLCSR_LPFLLSEL_MASK) != 0UL)
    {
        return kStatus_SCG_Busy;
    }

    /* If configure register is locked, return error. */
    if ((reg & SCG_LPFLLCSR_LK_MASK) != 0UL)
    {
        return kStatus_ReadOnly;
    }

    SCG->LPFLLCSR = SCG_LPFLLCSR_LPFLLERR_MASK;

    return kStatus_Success;
}

/*!
 * brief Gets the SCG LPFLL clock frequency.
 *
 * return  Clock frequency in Hz; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetLpFllFreq(void)
{
    static const uint32_t lpfllFreq[] = {
        SCG_LPFLL_FREQ0,
        SCG_LPFLL_FREQ1,
        SCG_LPFLL_FREQ2,
        SCG_LPFLL_FREQ3,
    };

    if ((SCG->LPFLLCSR & SCG_LPFLLCSR_LPFLLVLD_MASK) != 0UL) /* LPFLL is valid. */
    {
        return lpfllFreq[SCG_LPFLLCFG_FSEL_VAL];
    }
    else
    {
        return 0U;
    }
}

/*!
 * brief Gets the SCG asynchronous clock frequency from the LPFLL.
 *
 * param type     The asynchronous clock type.
 * return  Clock frequency in Hz; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetLpFllAsyncFreq(scg_async_clk_t type)
{
    uint32_t lpfllFreq = CLOCK_GetLpFllFreq();
    uint32_t divider   = 0U;

    /* Get divider. */
    if (lpfllFreq != 0UL)
    {
        switch (type)
        {
            case kSCG_AsyncDiv2Clk: /* LPFLLDIV2_CLK. */
                divider = SCG_LPFLLDIV_LPFLLDIV2_VAL;
                break;
            case kSCG_AsyncDiv1Clk: /* LPFLLDIV1_CLK. */
                divider = SCG_LPFLLDIV_LPFLLDIV1_VAL;
                break;
            default:
                divider = 0U;
                break;
        }
    }
    if (divider != 0U)
    {
        return lpfllFreq >> (divider - 1U);
    }
    else /* Output disabled. */
    {
        return 0U;
    }
}
