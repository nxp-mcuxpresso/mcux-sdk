/*
 * Copyright 2021-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_clock.h"

/*
 * $Coverage Justification Reference$
 *
 * $Justification clock_c_ref_1$
 * The platform can select only four clock sources.
 *
 * $Justification clock_c_ref_2$
 * After the board starts, the SIRC clock source is always enable and valid.
 *
 * $Justification clock_c_ref_3$
 * During the init FIRC process, the De-init Firc is first performed.
 * In this process, the successful De-init will Write One to clear the
 * FIRCERR bit of the FIRCCSR register.And trim, has only two modes to
 * choose from, and the setting trim mode is always successful.
 *
 * $Justification clock_c_ref_4$
 * After the board starts, the FRO192M output clock is always valid.
 *
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.clock"
#endif

/*! @brief Slow IRC clock frequency. */
#define SCG_SIRC_FREQ 6000000U
/*! @brief Get the RANGE value of the Fast IRC. */
#define SCG_FIRCCFG_RANGE_VAL ((CLOCK_REG(&SCG0->FIRCCFG) & SCG_FIRCCFG_RANGE_MASK) >> SCG_FIRCCFG_RANGE_SHIFT)
/*! @brief Get the value of each field in MRCC register. */
#define MRCC_MUX_VAL(reg) (((reg)&MRCC_MUX_MASK) >> MRCC_MUX_SHIFT)
/*! @brief Get the POSTDIV_SEL value of the FRO192M. */
#define FRO192M_FROCCSR_POSTDIV_SEL_VAL \
    ((CLOCK_REG(&FRO192M0->FROCCSR) & FRO192M_FROCCSR_POSTDIV_SEL_MASK) >> FRO192M_FROCCSR_POSTDIV_SEL_SHIFT)

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief External XTAL0 (OSC0) clock frequency. */
volatile uint32_t g_xtal0Freq;
/*! @brief External XTAL32K clock frequency. */
volatile uint32_t g_xtal32Freq;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

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
    return CLOCK_GetSysClkFreq(kSCG_SysClkBus);
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
        case kCLOCK_SlowClk:
            freq = CLOCK_GetSysClkFreq(kSCG_SysClkSlow);
            break;
        /* Original clock source. */
        case kCLOCK_SysClk:
        case kCLOCK_ScgSysOscClk:
            freq = CLOCK_GetSysOscFreq();
            break;
        case kCLOCK_ScgSircClk:
            freq = CLOCK_GetSircFreq();
            break;
        case kCLOCK_ScgFircClk:
            freq = CLOCK_GetFircFreq();
            break;
        case kCLOCK_RtcOscClk:
            freq = CLOCK_GetRtcOscFreq();
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
 * This function gets the IP module's functional clock frequency based on MRCC
 * registers. It is only used for the IP modules which could select clock source
 * by MRCC[MUX].
 *
 * param name Which peripheral to get, see \ref clock_ip_name_t.
 * return Clock frequency value in Hz
 */
uint32_t CLOCK_GetIpFreq(clock_ip_name_t name)
{
    if (kCLOCK_NOGATE == name)
    {
        return 0U;
    }

    uint32_t reg = CLOCK_REG(name);
    uint32_t freq;

    assert(reg & MRCC_PR_MASK);

    switch (name)
    {
        case kCLOCK_Lpi2c0:
        case kCLOCK_Lpi2c1:
        case kCLOCK_I3c0:
        case kCLOCK_Lpspi0:
        case kCLOCK_Lpspi1:
        case kCLOCK_Lpit0:
        case kCLOCK_Lpadc0:
        case kCLOCK_Flexio0:
            switch (MRCC_MUX_VAL(reg))
            {
                case (uint32_t)kCLOCK_IpSrcFro6M:
                    freq = CLOCK_GetSircFreq() / (((reg & MRCC_DIV_MASK) >> MRCC_DIV_SHIFT) + 1U);
                    break;
                case (uint32_t)kCLOCK_IpSrcFro192M:
                    freq = CLOCK_GetFircFreq() / (((reg & MRCC_DIV_MASK) >> MRCC_DIV_SHIFT) + 1U);
                    break;
                case (uint32_t)kCLOCK_IpSrcSoscClk:
                    freq = CLOCK_GetSysOscFreq() / (((reg & MRCC_DIV_MASK) >> MRCC_DIV_SHIFT) + 1U);
                    break;
                default:
                    freq = 0U;
                    break;
            }
            break;
        case kCLOCK_Lpuart0:
        case kCLOCK_Lpuart1:
        case kCLOCK_Tpm0:
        case kCLOCK_Tpm1:
            switch (MRCC_MUX_VAL(reg))
            {
                case (uint32_t)kCLOCK_IpSrcFro6M:
                    freq = CLOCK_GetSircFreq() / (((reg & MRCC_DIV_MASK) >> MRCC_DIV_SHIFT) + 1U);
                    break;
                case (uint32_t)kCLOCK_IpSrcFro192M:
                    freq = CLOCK_GetFircFreq() / (((reg & MRCC_DIV_MASK) >> MRCC_DIV_SHIFT) + 1U);
                    break;
                case (uint32_t)kCLOCK_IpSrcSoscClk:
                    freq = CLOCK_GetSysOscFreq() / (((reg & MRCC_DIV_MASK) >> MRCC_DIV_SHIFT) + 1U);
                    break;
                case (uint32_t)kCLOCK_IpSrc32kClk:
                    freq = CLOCK_GetRtcOscFreq() / (((reg & MRCC_DIV_MASK) >> MRCC_DIV_SHIFT) + 1U);
                    break;
                default:
                    freq = 0U;
                    break;
            }
            break;
        case kCLOCK_Can0:
            switch (MRCC_MUX_VAL(reg))
            {
                case (uint32_t)kCLOCK_IpSrcFro192M:
                    freq = CLOCK_GetFircFreq() / (((reg & MRCC_DIV_MASK) >> MRCC_DIV_SHIFT) + 1U);
                    break;
                case (uint32_t)kCLOCK_IpSrcSoscClk:
                    freq = CLOCK_GetSysOscFreq() / (((reg & MRCC_DIV_MASK) >> MRCC_DIV_SHIFT) + 1U);
                    break;
                default:
                    freq = 0U;
                    break;
            }
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
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

    /*
     * $Branch Coverage Justification$
     * ((sysClkConfig.src) != (kSCG_SysClkSrcSysOsc || kSCG_SysClkSrcSirc ||
     *   kSCG_SysClkSrcFirc || kSCG_SysClkSrcRosc)) not covered.
     * $ref clock_c_ref_1$.
     */
    switch ((scg_sys_clk_src_t)sysClkConfig.src)
    {
        case kSCG_SysClkSrcSysOsc:
            freq = CLOCK_GetSysOscFreq();
            break;
        case kSCG_SysClkSrcSirc:
            freq = CLOCK_GetSircFreq();
            break;
        case kSCG_SysClkSrcFirc:
            freq = CLOCK_GetFircFreq();
            break;
        case kSCG_SysClkSrcRosc:
            freq = CLOCK_GetRtcOscFreq();
            break;
        default:
            freq = 24000000U;
            break;
    }

    freq /= (sysClkConfig.divCore + 1U); /* Divided by the DIVCORE firstly. */

    switch (type)
    {
        case kSCG_SysClkSlow:
            freq /= (sysClkConfig.divSlow + 1U);
            break;
        case kSCG_SysClkBus:
            freq /= (sysClkConfig.divBus + 1U);
            break;
        case kSCG_SysClkPlatform:
        case kSCG_SysClkCore:
            break;
        default:
            assert(false);
            break;
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

    CLOCK_REG(&SCG0->SOSCCSR) = (uint32_t)config->enableMode | SCG_SOSCCSR_SOSCEN_MASK;

    CLOCK_SetSysOscMonitorMode(config->monitorMode);

    /* Wait for SOSC clock to be valid. */
    while ((CLOCK_REG(&SCG0->SOSCCSR) & SCG_SOSCCSR_SOSCVLD_MASK) != SCG_SOSCCSR_SOSCVLD_MASK)
    {
    }

    return (status_t)kStatus_Success;
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
    uint32_t reg = CLOCK_REG(&SCG0->SOSCCSR);

    /* If clock is used by system, return error. */
    if ((reg & SCG_SOSCCSR_SOSCSEL_MASK) == SCG_SOSCCSR_SOSCSEL_MASK)
    {
        return (status_t)kStatus_SCG_Busy;
    }

    /* If configure register is locked, return error. */
    if ((reg & SCG_SOSCCSR_LK_MASK) == SCG_SOSCCSR_LK_MASK)
    {
        return (status_t)kStatus_ReadOnly;
    }

    CLOCK_REG(&SCG0->SOSCCSR) = SCG_SOSCCSR_SOSCERR_MASK;

    return (status_t)kStatus_Success;
}

/*!
 * brief Gets the SCG system oscillator clock frequency (SOSC).
 *
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetSysOscFreq(void)
{
    if ((CLOCK_REG(&SCG0->SOSCCSR) & SCG_SOSCCSR_SOSCVLD_MASK) ==
        SCG_SOSCCSR_SOSCVLD_MASK) /* System OSC clock is valid. */
    {
        /* Please call CLOCK_SetXtal0Freq base on board setting before using OSC0 clock. */
        assert(g_xtal0Freq);
        return g_xtal0Freq;
    }
    else
    {
        return 0U;
    }
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

    CLOCK_REG(&SCG0->SIRCCSR) = (uint32_t)config->enableMode;

    /* Wait for SIRC clock to be valid. */

    /*
     * $Branch Coverage Justification$
     * (CLOCK_REG(&SCG0->SIRCCSR) & SCG_SIRCCSR_SIRCVLD_MASK) != SCG_SIRCCSR_SIRCVLD_MASK
     * not covered.
     * $ref clock_c_ref_2$.
     */
    while ((CLOCK_REG(&SCG0->SIRCCSR) & SCG_SIRCCSR_SIRCVLD_MASK) != SCG_SIRCCSR_SIRCVLD_MASK)
    {
    }

    return (status_t)kStatus_Success;
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
    uint32_t reg = CLOCK_REG(&SCG0->SIRCCSR);

    /* If clock is used by system, return error. */
    if ((reg & SCG_SIRCCSR_SIRCSEL_MASK) == SCG_SIRCCSR_SIRCSEL_MASK)
    {
        return (status_t)kStatus_SCG_Busy;
    }

    /* If configure register is locked, return error. */
    if ((reg & SCG_SIRCCSR_LK_MASK) == SCG_SIRCCSR_LK_MASK)
    {
        return (status_t)kStatus_ReadOnly;
    }

    CLOCK_REG(&SCG0->SIRCCSR) = 0U;

    return (status_t)kStatus_Success;
}

/*!
 * brief Gets the SCG SIRC clock frequency.
 *
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetSircFreq(void)
{
    /*
     * $Branch Coverage Justification$
     * (CLOCK_REG(&SCG0->SIRCCSR) & SCG_SIRCCSR_SIRCVLD_MASK) != SCG_SIRCCSR_SIRCVLD_MASK
     * not covered.
     * $ref clock_c_ref_2$.
     */
    if ((CLOCK_REG(&SCG0->SIRCCSR) & SCG_SIRCCSR_SIRCVLD_MASK) == SCG_SIRCCSR_SIRCVLD_MASK) /* SIRC is valid. */
    {
        return SCG_SIRC_FREQ;
    }
    else
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

    CLOCK_REG(&SCG0->FIRCCFG) = SCG_FIRCCFG_RANGE(config->range);

    if (config->trimConfig != NULL)
    {
        CLOCK_REG(&SCG0->FIRCTCFG) =
            SCG_FIRCTCFG_TRIMDIV(config->trimConfig->trimDiv) | SCG_FIRCTCFG_TRIMSRC(config->trimConfig->trimSrc);

        if (kSCG_FircTrimNonUpdate == config->trimConfig->trimMode)
        {
            CLOCK_REG(&SCG0->FIRCSTAT) = SCG_FIRCSTAT_TRIMFINE(config->trimConfig->trimFine);
        }

        /* Set trim mode. */
        CLOCK_REG(&SCG0->FIRCCSR) = (uint32_t)config->trimConfig->trimMode;

        /*
         * $Branch Coverage Justification$
         * (CLOCK_REG(&SCG0->FIRCCSR) & SCG_FIRCCSR_FIRCERR_MASK) == SCG_FIRCCSR_FIRCERR_MASK
         * not covered.
         * $ref clock_c_ref_3$.
         */
        if ((CLOCK_REG(&SCG0->FIRCCSR) & SCG_FIRCCSR_FIRCERR_MASK) == SCG_FIRCCSR_FIRCERR_MASK)
        {
            return (status_t)kStatus_Fail;
        }
    }

    CLOCK_REG(&SCG0->FIRCCSR) |= (SCG_FIRCCSR_FIRCEN_MASK | (uint32_t)config->enableMode);

    /* Wait for FIRC clock to be valid. */
    while ((CLOCK_REG(&SCG0->FIRCCSR) & SCG_FIRCCSR_FIRCVLD_MASK) != SCG_FIRCCSR_FIRCVLD_MASK)
    {
    }

    return (status_t)kStatus_Success;
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
    uint32_t reg = CLOCK_REG(&SCG0->FIRCCSR);

    /* If clock is used by system, return error. */
    if ((reg & SCG_FIRCCSR_FIRCSEL_MASK) == SCG_FIRCCSR_FIRCSEL_MASK)
    {
        return (status_t)kStatus_SCG_Busy;
    }

    /* If configure register is locked, return error. */
    if ((reg & SCG_FIRCCSR_LK_MASK) == SCG_FIRCCSR_LK_MASK)
    {
        return (status_t)kStatus_ReadOnly;
    }

    CLOCK_REG(&SCG0->FIRCCSR) = SCG_FIRCCSR_FIRCERR_MASK;

    return (status_t)kStatus_Success;
}

/*!
 * brief Gets the SCG FIRC clock frequency.
 *
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetFircFreq(void)
{
    static const uint32_t fircFreq[] = {48000000U, 64000000U, 96000000U, 192000000U};

    if ((CLOCK_REG(&SCG0->FIRCCSR) & SCG_FIRCCSR_FIRCVLD_MASK) == SCG_FIRCCSR_FIRCVLD_MASK) /* FIRC is valid. */
    {
        return fircFreq[SCG_FIRCCFG_RANGE_VAL];
    }
    else
    {
        return 0U;
    }
}

/*!
 * brief Initializes the SCG ROSC.
 *
 * This function enables the SCG ROSC clock according to the
 * configuration.
 *
 * param config   Pointer to the configuration structure.
 * retval kStatus_Success ROSC is initialized.
 * retval kStatus_SCG_Busy ROSC has been enabled and is used by the system clock.
 * retval kStatus_ReadOnly ROSC control register is locked.
 *
 * note This function can't detect whether the system OSC has been enabled and
 * used by an IP.
 */
status_t CLOCK_InitRosc(const scg_rosc_config_t *config)
{
    assert(config);
    status_t status;

    /* De-init the ROSC first. */
    status = CLOCK_DeinitRosc();

    if (kStatus_Success != status)
    {
        return status;
    }

    CLOCK_SetRoscMonitorMode(config->monitorMode);

    /* Wait for ROSC clock to be valid. */
    while ((CLOCK_REG(&SCG0->ROSCCSR) & SCG_ROSCCSR_ROSCVLD_MASK) != SCG_ROSCCSR_ROSCVLD_MASK)
    {
    }

    return (status_t)kStatus_Success;
}

/*!
 * brief De-initializes the SCG ROSC.
 *
 * This function disables the SCG ROSC clock.
 *
 * retval kStatus_Success System OSC is deinitialized.
 * retval kStatus_SCG_Busy System OSC is used by the system clock.
 * retval kStatus_ReadOnly System OSC control register is locked.
 *
 * note This function can't detect whether the ROSC is used by an IP.
 */
status_t CLOCK_DeinitRosc(void)
{
    uint32_t reg = CLOCK_REG(&SCG0->ROSCCSR);

    /* If clock is used by system, return error. */
    if ((reg & SCG_ROSCCSR_ROSCSEL_MASK) == SCG_ROSCCSR_ROSCSEL_MASK)
    {
        return (status_t)kStatus_SCG_Busy;
    }

    /* If configure register is locked, return error. */
    if ((reg & SCG_ROSCCSR_LK_MASK) == SCG_ROSCCSR_LK_MASK)
    {
        return (status_t)kStatus_ReadOnly;
    }

    CLOCK_REG(&SCG0->ROSCCSR) = SCG_ROSCCSR_ROSCERR_MASK;

    return (status_t)kStatus_Success;
}

/*!
 * @brief Gets the SCG RTC OSC clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetRtcOscFreq(void)
{
    if ((CLOCK_REG(&SCG0->ROSCCSR) & SCG_ROSCCSR_ROSCVLD_MASK) ==
        SCG_ROSCCSR_ROSCVLD_MASK) /* RTC OSC clock is valid. */
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
 * @brief Initializes the FRO192M clock for the Radio Mode Controller.
 *
 * This function configure the RF FRO192M clock according to the configuration.
 *
 * @param config   Pointer to the configuration structure.
 * @retval kStatus_Success RF FRO192M is configured.
 */
status_t CLOCK_InitRfFro192M(const fro192m_rf_clk_config_t *config)
{
    assert(config->range <= kFro192M_Range64M);
    assert(config->apb_rfcmc_div <= kFro192M_ClkDivBy8);

    CLOCK_REG(&FRO192M0->FROCCSR) = FRO192M_FROCCSR_POSTDIV_SEL(config->range);
    CLOCK_REG(&FRO192M0->FRODIV)  = FRO192M_FRODIV_FRODIV(config->apb_rfcmc_div);

    /* Wait for RF FRO192M clock to be valid. */

    /*
     * $Branch Coverage Justification$
     * (CLOCK_REG(&FRO192M0->FROCCSR) & FRO192M_FROCCSR_VALID_MASK) != FRO192M_FROCCSR_VALID_MASK
     * not covered.
     * $ref clock_c_ref_4$.
     */
    while ((CLOCK_REG(&FRO192M0->FROCCSR) & FRO192M_FROCCSR_VALID_MASK) != FRO192M_FROCCSR_VALID_MASK)
    {
    }

    return (status_t)kStatus_Success;
}

/*!
 * @brief Gets the FRO192M clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetRfFro192MFreq(void)
{
    static const uint32_t fro192mFreq[] = {16000000U, 24000000U, 32000000U, 48000000U, 64000000U};

    /*
     * $Branch Coverage Justification$
     * (CLOCK_REG(&FRO192M0->FROCCSR) & FRO192M_FROCCSR_VALID_MASK) != FRO192M_FROCCSR_VALID_MASK
     * not covered.
     * $ref clock_c_ref_4$.
     */
    if ((CLOCK_REG(&FRO192M0->FROCCSR) & FRO192M_FROCCSR_VALID_MASK) == FRO192M_FROCCSR_VALID_MASK)
    {
        return fro192mFreq[FRO192M_FROCCSR_POSTDIV_SEL_VAL];
    }
    else
    {
        return 0U;
    }
}
