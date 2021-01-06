/*
 * Copyright 2017 - 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_common.h"
#include "fsl_clock.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.clock"
#endif
/*! @brief SSCG PLL FLITER range value */
#define SSCG_PLL1_FILTER_RANGE (35000000U)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
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
        case kCLOCK_CoreM4Clk:
            freq = CLOCK_GetCoreM4Freq();
            break;
        case kCLOCK_AxiClk:
            freq = CLOCK_GetAxiFreq();
            break;
        case kCLOCK_AhbClk:
            freq = CLOCK_GetAhbFreq();
            break;
        case kCLOCK_IpgClk:
            freq = CLOCK_GetAhbFreq();
            break;
        default:
            freq = 0U;
            break;
    }
    return freq;
}

/*!
 * brief Get the CCM Cortex M4 core frequency.
 *
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetCoreM4Freq(void)
{
    uint32_t freq;
    uint32_t pre  = CLOCK_GetRootPreDivider(kCLOCK_RootM4);
    uint32_t post = CLOCK_GetRootPostDivider(kCLOCK_RootM4);

    switch (CLOCK_GetRootMux(kCLOCK_RootM4))
    {
        case (uint32_t)kCLOCK_M4RootmuxOsc25m:
            freq = OSC25M_CLK_FREQ;
            break;
        case (uint32_t)kCLOCK_M4RootmuxSysPll2Div5:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll2Ctrl) / 5U;
            break;
        case (uint32_t)kCLOCK_M4RootmuxSysPll2Div4:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll2Ctrl) / 4U;
            break;
        case (uint32_t)kCLOCK_M4RootmuxSysPll1Div3:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll1Ctrl) / 3U;
            break;
        case (uint32_t)kCLOCK_M4RootmuxSysPll1:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll1Ctrl);
            break;
        case (uint32_t)kCLOCK_M4RootmuxAudioPll1:
            freq = CLOCK_GetPllFreq(kCLOCK_AudioPll1Ctrl);
            break;
        case (uint32_t)kCLOCK_M4RootmuxVideoPll1:
            freq = CLOCK_GetPllFreq(kCLOCK_VideoPll1Ctrl);
            break;
        case (uint32_t)kCLOCK_M4RootmuxSysPll3:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll3Ctrl);
            break;
        default:
            freq = 0U;
            break;
    }

    return freq / pre / post;
}

/*!
 * brief Get the CCM Axi bus frequency.
 *
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetAxiFreq(void)
{
    uint32_t freq;
    uint32_t pre  = CLOCK_GetRootPreDivider(kCLOCK_RootAxi);
    uint32_t post = CLOCK_GetRootPostDivider(kCLOCK_RootAxi);

    switch (CLOCK_GetRootMux(kCLOCK_RootAxi))
    {
        case (uint32_t)kCLOCK_AxiRootmuxOsc25m:
            freq = OSC25M_CLK_FREQ;
            break;
        case (uint32_t)kCLOCK_AxiRootmuxSysPll2Div3:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll2Ctrl) / 3U;
            break;
        case (uint32_t)kCLOCK_AxiRootmuxSysPll2Div4:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll2Ctrl) / 4U;
            break;
        case (uint32_t)kCLOCK_AxiRootmuxSysPll2:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll2Ctrl);
            break;
        case (uint32_t)kCLOCK_AxiRootmuxAudioPll1:
            freq = CLOCK_GetPllFreq(kCLOCK_AudioPll1Ctrl);
            break;
        case (uint32_t)kCLOCK_AxiRootmuxVideoPll1:
            freq = CLOCK_GetPllFreq(kCLOCK_VideoPll1Ctrl);
            break;
        case (uint32_t)kCLOCK_AxiRootmuxSysPll1Div8:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll1Ctrl) / 8U;
            break;
        case (uint32_t)kCLOCK_AxiRootmuxSysPll1:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll1Ctrl);
            break;
        default:
            freq = 0U;
            break;
    }

    return freq / pre / post;
}

/*!
 * brief Get the CCM Ahb bus frequency.
 *
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetAhbFreq(void)
{
    uint32_t freq;
    uint32_t pre  = CLOCK_GetRootPreDivider(kCLOCK_RootAhb);
    uint32_t post = CLOCK_GetRootPostDivider(kCLOCK_RootAhb);

    switch (CLOCK_GetRootMux(kCLOCK_RootAhb))
    {
        case (uint32_t)kCLOCK_AhbRootmuxOsc25m:
            freq = OSC25M_CLK_FREQ;
            break;
        case (uint32_t)kCLOCK_AhbRootmuxSysPll1Div6:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll1Ctrl) / 6U;
            break;
        case (uint32_t)kCLOCK_AhbRootmuxSysPll1Div2:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll1Ctrl) / 2U;
            break;
        case (uint32_t)kCLOCK_AhbRootmuxSysPll1:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll1Ctrl);
            break;
        case (uint32_t)kCLOCK_AhbRootmuxSysPll2Div8:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll2Ctrl) / 8U;
            break;
        case (uint32_t)kCLOCK_AhbRootmuxSysPll3:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll3Ctrl);
            break;
        case (uint32_t)kCLOCK_AhbRootmuxAudioPll1:
            freq = CLOCK_GetPllFreq(kCLOCK_AudioPll1Ctrl);
            break;
        case (uint32_t)kCLOCK_AhbRootmuxVideoPll1:
            freq = CLOCK_GetPllFreq(kCLOCK_VideoPll1Ctrl);
            break;
        default:
            freq = 0U;
            break;
    }

    return freq / pre / post;
}

/*!
 * brief Gets PLL reference clock frequency.
 *
 * param type fractional pll type.

 * return  Clock frequency
 */
uint32_t CLOCK_GetPllRefClkFreq(clock_pll_ctrl_t ctrl)
{
    uint32_t refClkFreq = 0U;
    uint8_t clkSel      = 0U;

    if (ctrl <= kCLOCK_ArmPllCtrl)
    {
        clkSel = (uint8_t)CCM_BIT_FIELD_EXTRACTION(CCM_ANALOG_TUPLE_REG(CCM_ANALOG, ctrl),
                                                   CCM_ANALOG_AUDIO_PLL1_CFG0_PLL_REFCLK_SEL_MASK,
                                                   CCM_ANALOG_AUDIO_PLL1_CFG0_PLL_REFCLK_SEL_SHIFT);
    }
    else
    {
        clkSel = (uint8_t)(CCM_ANALOG_TUPLE_REG(CCM_ANALOG, ctrl) & CCM_ANALOG_SYS_PLL1_CFG0_PLL_REFCLK_SEL_MASK);
    }

    switch (clkSel)
    {
        case (uint8_t)kANALOG_PllRefOsc25M:
            refClkFreq = OSC25M_CLK_FREQ /
                         (CCM_BIT_FIELD_EXTRACTION(XTALOSC->OSC25M_CTL_CFG, XTALOSC_OSC25M_CTL_CFG_OSC_DIV_MASK,
                                                   XTALOSC_OSC25M_CTL_CFG_OSC_DIV_SHIFT) +
                          1U);
            break;

        case (uint8_t)kANALOG_PllRefOsc27M:
            refClkFreq = OSC27M_CLK_FREQ /
                         (CCM_BIT_FIELD_EXTRACTION(XTALOSC->OSC27M_CTL_CFG, XTALOSC_OSC27M_CTL_CFG_OSC_DIV_MASK,
                                                   XTALOSC_OSC27M_CTL_CFG_OSC_DIV_SHIFT) +
                          1U);
            break;

        case (uint8_t)kANALOG_PllRefOscHdmiPhy27M:
            refClkFreq = HDMI_PHY_27M_FREQ;
            break;

        case (uint8_t)kANALOG_PllRefClkPN:
            refClkFreq = CLKPN_FREQ;
            break;
        default:
            refClkFreq = 0U;
            break;
    }

    return refClkFreq;
}

/*!
 * brief Gets PLL clock frequency.
 *
 * param type fractional pll type.

 * return  Clock frequency
 */
uint32_t CLOCK_GetPllFreq(clock_pll_ctrl_t pll)
{
    uint32_t pllFreq    = 0U;
    uint32_t pllRefFreq = 0U;
    bool sscgPll1Bypass = false;
    bool sscgPll2Bypass = false;
    bool fracPllBypass  = false;

    pllRefFreq = CLOCK_GetPllRefClkFreq(pll);

    switch (pll)
    {
        /* SSCG PLL frequency */
        case kCLOCK_SystemPll1Ctrl:
            sscgPll1Bypass = CLOCK_IsPllBypassed(CCM_ANALOG, kCLOCK_SysPll1InternalPll1BypassCtrl);
            sscgPll2Bypass = CLOCK_IsPllBypassed(CCM_ANALOG, kCLOCK_SysPll1InternalPll2BypassCtrl);
            break;
        case kCLOCK_SystemPll2Ctrl:
            sscgPll1Bypass = CLOCK_IsPllBypassed(CCM_ANALOG, kCLOCK_SysPll2InternalPll1BypassCtrl);
            sscgPll2Bypass = CLOCK_IsPllBypassed(CCM_ANALOG, kCLOCK_SysPll2InternalPll2BypassCtrl);
            break;
        case kCLOCK_SystemPll3Ctrl:
            sscgPll1Bypass = CLOCK_IsPllBypassed(CCM_ANALOG, kCLOCK_SysPll3InternalPll1BypassCtrl);
            sscgPll2Bypass = CLOCK_IsPllBypassed(CCM_ANALOG, kCLOCK_SysPll3InternalPll2BypassCtrl);
            break;
        case kCLOCK_VideoPll2Ctrl:
            sscgPll1Bypass = CLOCK_IsPllBypassed(CCM_ANALOG, kCLOCK_VideoPll2InternalPll1BypassCtrl);
            sscgPll2Bypass = CLOCK_IsPllBypassed(CCM_ANALOG, kCLOCK_VideoPll2InternalPll2BypassCtrl);
            break;
        case kCLOCK_DramPllCtrl:
            sscgPll1Bypass = CLOCK_IsPllBypassed(CCM_ANALOG, kCLOCK_DramPllInternalPll1BypassCtrl);
            sscgPll2Bypass = CLOCK_IsPllBypassed(CCM_ANALOG, kCLOCK_DramPllInternalPll2BypassCtrl);
            break;
        case kCLOCK_AudioPll1Ctrl:
            fracPllBypass = CLOCK_IsPllBypassed(CCM_ANALOG, kCLOCK_AudioPll1BypassCtrl);
            break;
        case kCLOCK_AudioPll2Ctrl:
            fracPllBypass = CLOCK_IsPllBypassed(CCM_ANALOG, kCLOCK_AudioPll2BypassCtrl);
            break;
        case kCLOCK_VideoPll1Ctrl:
            fracPllBypass = CLOCK_IsPllBypassed(CCM_ANALOG, kCLOCK_VideoPll1BypassCtrl);
            break;
        case kCLOCK_GpuPllCtrl:
            fracPllBypass = CLOCK_IsPllBypassed(CCM_ANALOG, kCLOCK_GpuPLLPwrBypassCtrl);
            break;
        case kCLOCK_VpuPllCtrl:
            fracPllBypass = CLOCK_IsPllBypassed(CCM_ANALOG, kCLOCK_VpuPllPwrBypassCtrl);
            break;
        case kCLOCK_ArmPllCtrl:
            fracPllBypass = CLOCK_IsPllBypassed(CCM_ANALOG, kCLOCK_ArmPllPwrBypassCtrl);
            break;
        default:
            fracPllBypass = false;
            break;
    }
    if (pll <= kCLOCK_ArmPllCtrl)
    {
        if (fracPllBypass)
        {
            pllFreq = pllRefFreq;
        }
        else
        {
            pllFreq = CLOCK_GetFracPllFreq(CCM_ANALOG, pll, pllRefFreq);
        }
    }
    else
    {
        if (sscgPll2Bypass)
        {
            /* if PLL2 is bypass, return reference clock directly */
            pllFreq = pllRefFreq;
        }
        else
        {
            pllFreq = CLOCK_GetSSCGPllFreq(CCM_ANALOG, pll, pllRefFreq, sscgPll1Bypass);
        }
    }

    return pllFreq;
}

/*!
 * brief Initializes the ANALOG ARM PLL.
 *
 * param config Pointer to the configuration structure(see ref ccm_analog_frac_pll_config_t enumeration).
 *
 * note This function can't detect whether the Arm PLL has been enabled and
 * used by some IPs.
 */
void CLOCK_InitArmPll(const ccm_analog_frac_pll_config_t *config)
{
    assert(config != NULL);

    /* Disable PLL bypass */
    CLOCK_SetPllBypass(CCM_ANALOG, kCLOCK_ArmPllPwrBypassCtrl, false);
    /* Fractional pll configuration */
    CLOCK_InitFracPll(CCM_ANALOG, config, kCLOCK_ArmPllCtrl);
    /* Enable and power up PLL clock. */
    CLOCK_EnableAnalogClock(CCM_ANALOG, kCLOCK_ArmPllClke);

    /* Wait for PLL to be locked. */
    while (!CLOCK_IsPllLocked(CCM_ANALOG, kCLOCK_ArmPllCtrl))
    {
    }
}

/*!
 * brief De-initialize the ARM PLL.
 */
void CLOCK_DeinitArmPll(void)
{
    CLOCK_PowerDownPll(CCM_ANALOG, kCLOCK_ArmPllCtrl);
}

/*!
 * brief Initializes the ANALOG AUDIO PLL1.
 *
 * param config Pointer to the configuration structure(see ref ccm_analog_frac_pll_config_t enumeration).
 *
 * note This function can't detect whether the AUDIO PLL has been enabled and
 * used by some IPs.
 */
void CLOCK_InitAudioPll1(const ccm_analog_frac_pll_config_t *config)
{
    assert(config != NULL);

    /* Disable PLL bypass */
    CLOCK_SetPllBypass(CCM_ANALOG, kCLOCK_AudioPll1BypassCtrl, false);
    /* Fractional pll configuration */
    CLOCK_InitFracPll(CCM_ANALOG, config, kCLOCK_AudioPll1Ctrl);
    /* Enable and power up PLL clock. */
    CLOCK_EnableAnalogClock(CCM_ANALOG, kCLOCK_AudioPll1Clke);

    /* Wait for PLL to be locked. */
    while (!CLOCK_IsPllLocked(CCM_ANALOG, kCLOCK_AudioPll1Ctrl))
    {
    }
}

/*!
 * brief De-initialize the Audio PLL1.
 */
void CLOCK_DeinitAudioPll1(void)
{
    CLOCK_PowerDownPll(CCM_ANALOG, kCLOCK_AudioPll1Ctrl);
}

/*!
 * brief Initializes the ANALOG AUDIO PLL2.
 *
 * param config Pointer to the configuration structure(see ref ccm_analog_frac_pll_config_t enumeration).
 *
 * note This function can't detect whether the AUDIO PLL has been enabled and
 * used by some IPs.
 */
void CLOCK_InitAudioPll2(const ccm_analog_frac_pll_config_t *config)
{
    assert(config != NULL);

    /* Disable PLL bypass */
    CLOCK_SetPllBypass(CCM_ANALOG, kCLOCK_AudioPll2BypassCtrl, false);
    /* Fractional pll configuration */
    CLOCK_InitFracPll(CCM_ANALOG, config, kCLOCK_AudioPll2Ctrl);
    /* Enable and power up PLL clock. */
    CLOCK_EnableAnalogClock(CCM_ANALOG, kCLOCK_AudioPll2Clke);

    /* Wait for PLL to be locked. */
    while (!CLOCK_IsPllLocked(CCM_ANALOG, kCLOCK_AudioPll2Ctrl))
    {
    }
}

/*!
 * brief De-initialize the Audio PLL2.
 */
void CLOCK_DeinitAudioPll2(void)
{
    CLOCK_PowerDownPll(CCM_ANALOG, kCLOCK_AudioPll2Ctrl);
}

/*!
 * brief Initializes the ANALOG VIDEO PLL1.
 *
 * param config Pointer to the configuration structure(see ref ccm_analog_frac_pll_config_t enumeration).
 *
 */
void CLOCK_InitVideoPll1(const ccm_analog_frac_pll_config_t *config)
{
    assert(config != NULL);

    /* Disable PLL bypass */
    CLOCK_SetPllBypass(CCM_ANALOG, kCLOCK_VideoPll1BypassCtrl, false);
    /* Fractional pll configuration */
    CLOCK_InitFracPll(CCM_ANALOG, config, kCLOCK_VideoPll1Ctrl);
    /* Enable and power up PLL clock. */
    CLOCK_EnableAnalogClock(CCM_ANALOG, kCLOCK_VideoPll1Clke);

    /* Wait for PLL to be locked. */
    while (!CLOCK_IsPllLocked(CCM_ANALOG, kCLOCK_VideoPll1Ctrl))
    {
    }
}

/*!
 * brief De-initialize the Video PLL1.
 */
void CLOCK_DeinitVideoPll1(void)
{
    CLOCK_PowerDownPll(CCM_ANALOG, kCLOCK_VideoPll1Ctrl);
}

/*!
 * brief Initializes the ANALOG SYS PLL1.
 *
 * param config Pointer to the configuration structure(see ref ccm_analog_sscg_pll_config_t enumeration).
 *
 * note This function can't detect whether the SYS PLL has been enabled and
 * used by some IPs.
 */
void CLOCK_InitSysPll1(const ccm_analog_sscg_pll_config_t *config)
{
    assert(config != NULL);

    /* SSCG PLL configuration */
    CLOCK_InitSSCGPll(CCM_ANALOG, config, kCLOCK_SystemPll1Ctrl);
    /* Disable PLL bypass */
    CLOCK_SetPllBypass(CCM_ANALOG, kCLOCK_SysPll1InternalPll1BypassCtrl, false);
    CLOCK_SetPllBypass(CCM_ANALOG, kCLOCK_SysPll1InternalPll2BypassCtrl, false);
    /* Enable and power up PLL clock. */
    CLOCK_EnableAnalogClock(CCM_ANALOG, kCLOCK_SystemPll1Clke);

    /* Wait for PLL to be locked. */
    while (!CLOCK_IsPllLocked(CCM_ANALOG, kCLOCK_SystemPll1Ctrl))
    {
    }
}

/*!
 * brief De-initialize the System PLL1.
 */
void CLOCK_DeinitSysPll1(void)
{
    CLOCK_PowerDownPll(CCM_ANALOG, kCLOCK_SystemPll1Ctrl);
}

/*!
 * brief Initializes the ANALOG SYS PLL2.
 *
 * param config Pointer to the configuration structure(see ref ccm_analog_sscg_pll_config_t enumeration).
 *
 * note This function can't detect whether the SYS PLL has been enabled and
 * used by some IPs.
 */
void CLOCK_InitSysPll2(const ccm_analog_sscg_pll_config_t *config)
{
    assert(config != NULL);

    /* SSCG PLL configuration */
    CLOCK_InitSSCGPll(CCM_ANALOG, config, kCLOCK_SystemPll2Ctrl);
    /* Disable PLL bypass */
    CLOCK_SetPllBypass(CCM_ANALOG, kCLOCK_SysPll2InternalPll1BypassCtrl, false);
    CLOCK_SetPllBypass(CCM_ANALOG, kCLOCK_SysPll2InternalPll2BypassCtrl, false);
    /* Enable and power up PLL clock. */
    CLOCK_EnableAnalogClock(CCM_ANALOG, kCLOCK_SystemPll2Clke);

    /* Wait for PLL to be locked. */
    while (!CLOCK_IsPllLocked(CCM_ANALOG, kCLOCK_SystemPll2Ctrl))
    {
    }
}

/*!
 * brief De-initialize the System PLL2.
 */
void CLOCK_DeinitSysPll2(void)
{
    CLOCK_PowerDownPll(CCM_ANALOG, kCLOCK_SystemPll2Ctrl);
}

/*!
 * brief Initializes the ANALOG SYS PLL3.
 *
 * param config Pointer to the configuration structure(see ref ccm_analog_sscg_pll_config_t enumeration).
 *
 * note This function can't detect whether the SYS PLL has been enabled and
 * used by some IPs.
 */
void CLOCK_InitSysPll3(const ccm_analog_sscg_pll_config_t *config)
{
    assert(config != NULL);

    /* SSCG PLL configuration */
    CLOCK_InitSSCGPll(CCM_ANALOG, config, kCLOCK_SystemPll3Ctrl);
    /* Disable PLL bypass */
    CLOCK_SetPllBypass(CCM_ANALOG, kCLOCK_SysPll3InternalPll1BypassCtrl, false);
    CLOCK_SetPllBypass(CCM_ANALOG, kCLOCK_SysPll3InternalPll2BypassCtrl, false);
    /* Enable and power up PLL clock. */
    CLOCK_EnableAnalogClock(CCM_ANALOG, kCLOCK_SystemPll3Clke);

    /* Wait for PLL to be locked. */
    while (!CLOCK_IsPllLocked(CCM_ANALOG, kCLOCK_SystemPll3Ctrl))
    {
    }
}

/*!
 * brief De-initialize the System PLL3.
 */
void CLOCK_DeinitSysPll3(void)
{
    CLOCK_PowerDownPll(CCM_ANALOG, kCLOCK_SystemPll3Ctrl);
}

/*!
 * brief Initializes the ANALOG DDR PLL.
 *
 * param config Pointer to the configuration structure(see ref ccm_analog_sscg_pll_config_t enumeration).
 *
 * note This function can't detect whether the DDR PLL has been enabled and
 * used by some IPs.
 */
void CLOCK_InitDramPll(const ccm_analog_sscg_pll_config_t *config)
{
    assert(config != NULL);

    /* init SSCG pll */
    CLOCK_InitSSCGPll(CCM_ANALOG, config, kCLOCK_DramPllCtrl);
    /* Disable PLL bypass */
    CLOCK_SetPllBypass(CCM_ANALOG, kCLOCK_DramPllInternalPll1BypassCtrl, false);
    CLOCK_SetPllBypass(CCM_ANALOG, kCLOCK_DramPllInternalPll2BypassCtrl, false);
    /* Enable and power up PLL clock. */
    CLOCK_EnableAnalogClock(CCM_ANALOG, kCLOCK_DramPllClke);

    /* make sure DDR is release from reset, DDR1 should be assigned to special domain first */
    /* trigger the DDR1 power up */
    GPC->PU_PGC_SW_PUP_REQ |= GPC_PU_PGC_SW_PUP_REQ_DDR1_SW_PUP_REQ_MASK;
    /* release DDR1 from reset status */
    SRC->DDRC2_RCR = (SRC->DDRC2_RCR & (~(SRC_DDRC2_RCR_DDRC1_PHY_PWROKIN_MASK | SRC_DDRC2_RCR_DDRC1_PHY_RESET_MASK |
                                          SRC_DDRC2_RCR_DDRC2_CORE_RST_MASK | SRC_DDRC2_RCR_DDRC2_PRST_MASK))) |
                     SRC_DDRC2_RCR_DOM_EN_MASK | SRC_DDRC2_RCR_DOMAIN3_MASK | SRC_DDRC2_RCR_DOMAIN2_MASK |
                     SRC_DDRC2_RCR_DOMAIN1_MASK | SRC_DDRC2_RCR_DOMAIN0_MASK;

    while (!CLOCK_IsPllLocked(CCM_ANALOG, kCLOCK_DramPllCtrl))
    {
    }
}

/*!
 * brief De-initialize the Dram PLL.
 */
void CLOCK_DeinitDramPll(void)
{
    CLOCK_PowerDownPll(CCM_ANALOG, kCLOCK_DramPllCtrl);
}

/*!
 * brief Initializes the ANALOG VIDEO PLL2.
 *
 * param config Pointer to the configuration structure(see ref ccm_analog_sscg_pll_config_t enumeration).
 *
 * note This function can't detect whether the VIDEO PLL has been enabled and
 * used by some IPs.
 */
void CLOCK_InitVideoPll2(const ccm_analog_sscg_pll_config_t *config)
{
    assert(config != NULL);

    /* init SSCG pll */
    CLOCK_InitSSCGPll(CCM_ANALOG, config, kCLOCK_VideoPll2Ctrl);

    /* Disable PLL bypass */
    CLOCK_SetPllBypass(CCM_ANALOG, kCLOCK_VideoPll2InternalPll1BypassCtrl, false);
    CLOCK_SetPllBypass(CCM_ANALOG, kCLOCK_VideoPll2InternalPll2BypassCtrl, false);
    /* Enable and power up PLL clock. */
    CLOCK_EnableAnalogClock(CCM_ANALOG, kCLOCK_VideoPll2Clke);

    /* Wait for PLL to be locked. */
    while (!CLOCK_IsPllLocked(CCM_ANALOG, kCLOCK_VideoPll2Ctrl))
    {
    }
}

/*!
 * brief De-initialize the Video PLL2.
 */
void CLOCK_DeinitVideoPll2(void)
{
    CLOCK_PowerDownPll(CCM_ANALOG, kCLOCK_VideoPll2Ctrl);
}

/*!
 * brief Initializes the ANALOG Fractional PLL.
 *
 * param base CCM ANALOG base address.
 * param config Pointer to the configuration structure(see ref ccm_analog_frac_pll_config_t enumeration).
 * param type fractional pll type.
 *
 */
void CLOCK_InitFracPll(CCM_ANALOG_Type *base, const ccm_analog_frac_pll_config_t *config, clock_pll_ctrl_t type)
{
    assert(config != NULL);
    assert((config->refDiv != 0U) && (config->outDiv != 0U));
    assert((config->outDiv % 2U) == 0U);
    assert(type <= kCLOCK_ArmPllCtrl);

    uint32_t fracCfg0 = CCM_ANALOG_TUPLE_REG_OFF(base, type, 0U) | CCM_ANALOG_AUDIO_PLL1_CFG0_PLL_PD_MASK;
    uint32_t fracCfg1 = CCM_ANALOG_TUPLE_REG_OFF(base, type, 4U);

    /* power down the fractional PLL first */
    CCM_ANALOG_TUPLE_REG_OFF(base, type, 0U) = fracCfg0;

    CCM_ANALOG_TUPLE_REG_OFF(base, type, 0U) =
        (fracCfg0 &
         (~(CCM_ANALOG_AUDIO_PLL1_CFG0_PLL_OUTPUT_DIV_VAL_MASK | CCM_ANALOG_AUDIO_PLL1_CFG0_PLL_REFCLK_DIV_VAL_MASK |
            CCM_ANALOG_AUDIO_PLL1_CFG0_PLL_REFCLK_SEL_MASK | CCM_ANALOG_AUDIO_PLL1_CFG0_PLL_NEWDIV_VAL_MASK))) |
        (CCM_ANALOG_AUDIO_PLL1_CFG0_PLL_OUTPUT_DIV_VAL((uint32_t)(config->outDiv) / 2U - 1U)) |
        (CCM_ANALOG_AUDIO_PLL1_CFG0_PLL_REFCLK_DIV_VAL((uint32_t)(config->refDiv) - 1U)) |
        CCM_ANALOG_AUDIO_PLL1_CFG0_PLL_REFCLK_SEL(config->refSel);

    CCM_ANALOG_TUPLE_REG_OFF(base, type, 4U) =
        (fracCfg1 &
         (~(CCM_ANALOG_AUDIO_PLL1_CFG1_PLL_INT_DIV_CTL_MASK | CCM_ANALOG_AUDIO_PLL1_CFG1_PLL_FRAC_DIV_CTL_MASK))) |
        CCM_ANALOG_AUDIO_PLL1_CFG1_PLL_INT_DIV_CTL(config->intDiv) |
        CCM_ANALOG_AUDIO_PLL1_CFG1_PLL_FRAC_DIV_CTL(config->fractionDiv);

    /* NEW_DIV_VAL */
    CCM_ANALOG_TUPLE_REG_OFF(base, type, 0U) |= CCM_ANALOG_AUDIO_PLL1_CFG0_PLL_NEWDIV_VAL_MASK;

    /* power up the fractional pll */
    CCM_ANALOG_TUPLE_REG_OFF(base, type, 0U) &= ~CCM_ANALOG_AUDIO_PLL1_CFG0_PLL_PD_MASK;

    /* need to check NEW_DIV_ACK */
    while ((CCM_ANALOG_TUPLE_REG_OFF(base, type, 0U) & CCM_ANALOG_AUDIO_PLL1_CFG0_PLL_NEWDIV_ACK_MASK) == 0U)
    {
    }
}

/*!
 * brief Gets the ANALOG Fractional PLL clock frequency.
 *
 * param base CCM_ANALOG base pointer.
 * param type fractional pll type.
 * param fractional pll reference clock frequency
 *
 * return  Clock frequency
 */
uint32_t CLOCK_GetFracPllFreq(CCM_ANALOG_Type *base, clock_pll_ctrl_t type, uint32_t refClkFreq)
{
    assert(type <= kCLOCK_ArmPllCtrl);

    uint32_t fracCfg0 = CCM_ANALOG_TUPLE_REG_OFF(base, type, 0U);
    uint32_t fracCfg1 = CCM_ANALOG_TUPLE_REG_OFF(base, type, 4U);
    uint64_t fracClk  = 0U;

    uint8_t refDiv   = (uint8_t)CCM_BIT_FIELD_EXTRACTION(fracCfg0, CCM_ANALOG_AUDIO_PLL1_CFG0_PLL_REFCLK_DIV_VAL_MASK,
                                                       CCM_ANALOG_AUDIO_PLL1_CFG0_PLL_REFCLK_DIV_VAL_SHIFT);
    uint8_t outDiv   = (uint8_t)CCM_BIT_FIELD_EXTRACTION(fracCfg0, CCM_ANALOG_AUDIO_PLL1_CFG0_PLL_OUTPUT_DIV_VAL_MASK,
                                                       CCM_ANALOG_AUDIO_PLL1_CFG0_PLL_OUTPUT_DIV_VAL_SHIFT);
    uint32_t fracDiv = CCM_BIT_FIELD_EXTRACTION(fracCfg1, CCM_ANALOG_AUDIO_PLL1_CFG1_PLL_FRAC_DIV_CTL_MASK,
                                                CCM_ANALOG_AUDIO_PLL1_CFG1_PLL_FRAC_DIV_CTL_SHIFT);
    uint8_t intDiv   = (uint8_t)CCM_BIT_FIELD_EXTRACTION(fracCfg1, CCM_ANALOG_AUDIO_PLL1_CFG1_PLL_INT_DIV_CTL_MASK,
                                                       CCM_ANALOG_AUDIO_PLL1_CFG1_PLL_INT_DIV_CTL_SHIFT);

    refClkFreq /= (uint32_t)refDiv + 1UL;
    fracClk = (uint64_t)refClkFreq * 8U * (1U + intDiv) + (((uint64_t)refClkFreq * 8U * fracDiv) >> 24U);

    return (uint32_t)(fracClk / (((uint64_t)outDiv + 1U) * 2U));
}

/*!
 * brief Initializes the ANALOG SSCG PLL.
 *
 * param base CCM ANALOG base address
 * param config Pointer to the configuration structure(see ref ccm_analog_sscg_pll_config_t enumeration).
 * param type sscg pll type
 *
 */
void CLOCK_InitSSCGPll(CCM_ANALOG_Type *base, const ccm_analog_sscg_pll_config_t *config, clock_pll_ctrl_t type)
{
    assert(config != NULL);
    assert(config->refDiv1 != 0U);
    assert(config->refDiv2 != 0U);
    assert(config->outDiv != 0U);
    assert(config->loopDivider1 != 0U);
    assert(config->loopDivider2 != 0U);
    assert(type >= kCLOCK_SystemPll1Ctrl);

    uint32_t sscgCfg0   = CCM_ANALOG_TUPLE_REG_OFF(base, type, 0U) | CCM_ANALOG_SYS_PLL1_CFG0_PLL_PD_MASK;
    uint32_t sscgCfg2   = CCM_ANALOG_TUPLE_REG_OFF(base, type, 8U);
    uint32_t pll1Filter = 0U;

    /* power down the SSCG PLL first */
    CCM_ANALOG_TUPLE_REG_OFF(base, type, 0U) = sscgCfg0;

    /* pll mux configuration */
    CCM_ANALOG_TUPLE_REG_OFF(base, type, 0U) =
        (sscgCfg0 & (~CCM_ANALOG_SYS_PLL1_CFG0_PLL_REFCLK_SEL_MASK)) | config->refSel;

    /* reserve CFG1, spread spectrum */

    /* match the PLL1 input clock range with PLL filter range */
    if ((CLOCK_GetPllRefClkFreq(type) / (config->refDiv1)) > SSCG_PLL1_FILTER_RANGE)
    {
        pll1Filter = 1U;
    }
    /* divider configuration */
    CCM_ANALOG_TUPLE_REG_OFF(base, type, 8U) =
        (sscgCfg2 &
         (~(CCM_ANALOG_SYS_PLL1_CFG2_PLL_OUTPUT_DIV_VAL_MASK | CCM_ANALOG_SYS_PLL1_CFG2_PLL_FEEDBACK_DIVF2_MASK |
            CCM_ANALOG_SYS_PLL1_CFG2_PLL_FEEDBACK_DIVF1_MASK | CCM_ANALOG_SYS_PLL1_CFG2_PLL_REF_DIVR2_MASK |
            CCM_ANALOG_SYS_PLL1_CFG2_PLL_REF_DIVR1_MASK))) |
        CCM_ANALOG_SYS_PLL1_CFG2_PLL_OUTPUT_DIV_VAL((uint32_t)(config->outDiv) - 1U) |
        CCM_ANALOG_SYS_PLL1_CFG2_PLL_FEEDBACK_DIVF2(config->loopDivider2 - 1U) |
        CCM_ANALOG_SYS_PLL1_CFG2_PLL_FEEDBACK_DIVF1(config->loopDivider1 - 1U) |
        CCM_ANALOG_SYS_PLL1_CFG2_PLL_REF_DIVR2((uint32_t)(config->refDiv2) - 1U) |
        CCM_ANALOG_SYS_PLL1_CFG2_PLL_REF_DIVR1((uint32_t)(config->refDiv1) - 1U) | pll1Filter;

    /* power up the SSCG PLL */
    CCM_ANALOG_TUPLE_REG_OFF(base, type, 0U) &= ~CCM_ANALOG_SYS_PLL1_CFG0_PLL_PD_MASK;
}

/*!
 * brief Get the ANALOG SSCG PLL clock frequency.
 *
 * param base CCM ANALOG base address.
 * param type sscg pll type
 * param pll1Bypass pll1 bypass flag
 *
 * return  Clock frequency
 */
uint32_t CLOCK_GetSSCGPllFreq(CCM_ANALOG_Type *base, clock_pll_ctrl_t type, uint32_t refClkFreq, bool pll1Bypass)
{
    assert(type >= kCLOCK_SystemPll1Ctrl);

    uint32_t sscgCfg1       = CCM_ANALOG_TUPLE_REG_OFF(base, type, 4U);
    uint32_t sscgCfg2       = CCM_ANALOG_TUPLE_REG_OFF(base, type, 8U);
    uint64_t pll2InputClock = 0U;

    uint8_t refDiv1 = (uint8_t)CCM_BIT_FIELD_EXTRACTION(sscgCfg2, CCM_ANALOG_SYS_PLL1_CFG2_PLL_REF_DIVR1_MASK,
                                                        CCM_ANALOG_SYS_PLL1_CFG2_PLL_REF_DIVR1_SHIFT) +
                      1U;
    uint8_t refDiv2 = (uint8_t)CCM_BIT_FIELD_EXTRACTION(sscgCfg2, CCM_ANALOG_SYS_PLL1_CFG2_PLL_REF_DIVR2_MASK,
                                                        CCM_ANALOG_SYS_PLL1_CFG2_PLL_REF_DIVR2_SHIFT) +
                      1U;
    uint8_t divf1 = (uint8_t)CCM_BIT_FIELD_EXTRACTION(sscgCfg2, CCM_ANALOG_SYS_PLL1_CFG2_PLL_FEEDBACK_DIVF1_MASK,
                                                      CCM_ANALOG_SYS_PLL1_CFG2_PLL_FEEDBACK_DIVF1_SHIFT) +
                    1U;
    uint8_t divf2 = (uint8_t)CCM_BIT_FIELD_EXTRACTION(sscgCfg2, CCM_ANALOG_SYS_PLL1_CFG2_PLL_FEEDBACK_DIVF2_MASK,
                                                      CCM_ANALOG_SYS_PLL1_CFG2_PLL_FEEDBACK_DIVF2_SHIFT) +
                    1U;
    uint8_t outDiv = (uint8_t)CCM_BIT_FIELD_EXTRACTION(sscgCfg2, CCM_ANALOG_SYS_PLL1_CFG2_PLL_OUTPUT_DIV_VAL_MASK,
                                                       CCM_ANALOG_SYS_PLL1_CFG2_PLL_OUTPUT_DIV_VAL_SHIFT) +
                     1U;

    refClkFreq /= refDiv1;

    if (pll1Bypass)
    {
        pll2InputClock = refClkFreq;
    }
    else if ((sscgCfg1 & CCM_ANALOG_SYS_PLL1_CFG1_PLL_SSE_MASK) != 0U)
    {
        pll2InputClock = (uint64_t)refClkFreq * 8U * divf1 / refDiv2;
    }
    else
    {
        pll2InputClock = (uint64_t)refClkFreq * 2U * divf1 / refDiv2;
    }

    return (uint32_t)(pll2InputClock * divf2 / outDiv);
}

/*!
 * brief Set root clock divider
 * Note: The PRE and POST dividers in this function are the actually divider, software will map it to register value
 *
 * param ccmRootClk Root control (see ref clock_root_control_t enumeration)
 * param pre Pre divider value (1-8)
 * param post Post divider value (1-64)
 */
void CLOCK_SetRootDivider(clock_root_control_t ccmRootClk, uint32_t pre, uint32_t post)
{
    assert((pre <= 8U) && (pre != 0U));
    assert((post <= 64U) && (post != 0U));

    CCM_REG(ccmRootClk) = (CCM_REG(ccmRootClk) & (~(CCM_TARGET_ROOT_PRE_PODF_MASK | CCM_TARGET_ROOT_POST_PODF_MASK))) |
                          CCM_TARGET_ROOT_PRE_PODF(pre - 1U) | CCM_TARGET_ROOT_POST_PODF(post - 1U);
}

/*!
 * brief Update clock root in one step, for dynamical clock switching
 * Note: The PRE and POST dividers in this function are the actually divider, software will map it to register value
 *
 * param ccmRootClk Root control (see ref clock_root_control_t enumeration)
 * param root mux value (see ref _ccm_rootmux_xxx enumeration)
 * param pre Pre divider value (0-7, divider=n+1)
 * param post Post divider value (0-63, divider=n+1)
 */
void CLOCK_UpdateRoot(clock_root_control_t ccmRootClk, uint32_t mux, uint32_t pre, uint32_t post)
{
    assert((pre <= 8U) && (pre != 0U));
    assert((post <= 64U) && (post != 0U));

    CCM_REG(ccmRootClk) =
        (CCM_REG(ccmRootClk) &
         (~(CCM_TARGET_ROOT_MUX_MASK | CCM_TARGET_ROOT_PRE_PODF_MASK | CCM_TARGET_ROOT_POST_PODF_MASK))) |
        CCM_TARGET_ROOT_MUX(mux) | CCM_TARGET_ROOT_PRE_PODF(pre - 1U) | CCM_TARGET_ROOT_POST_PODF(post - 1U);
}

/*!
 * brief OSC25M init
 *
 * param config osc configuration
 */
void CLOCK_InitOSC25M(const osc_config_t *config)
{
    assert(config != NULL);
    assert(config->oscDiv != 0U);

    XTALOSC->OSC25M_CTL_CFG =
        (XTALOSC->OSC25M_CTL_CFG & (~(XTALOSC_OSC25M_CTL_CFG_OSC_DIV_MASK | XTALOSC_OSC25M_CTL_CFG_OSC_BYPSS_MASK))) |
        XTALOSC_OSC25M_CTL_CFG_OSC_DIV((uint32_t)(config->oscDiv) - 1U) |
        XTALOSC_OSC25M_CTL_CFG_OSC_BYPSS(config->oscMode);

    CLOCK_EnableAnalogClock(CCM_ANALOG, kCLOCK_OSC25MClke);
}

/*!
 * brief OSC25M deinit
 *
 */
void CLOCK_DeinitOSC25M(void)
{
    CLOCK_DisableAnalogClock(CCM_ANALOG, kCLOCK_OSC25MClke);
}

/*!
 * brief OSC27M init
 *
 */
void CLOCK_InitOSC27M(const osc_config_t *config)
{
    assert(config != NULL);
    assert(config->oscDiv != 0U);

    XTALOSC->OSC27M_CTL_CFG =
        (XTALOSC->OSC27M_CTL_CFG & (~(XTALOSC_OSC27M_CTL_CFG_OSC_DIV_MASK | XTALOSC_OSC27M_CTL_CFG_OSC_BYPSS_MASK))) |
        XTALOSC_OSC27M_CTL_CFG_OSC_DIV((uint32_t)(config->oscDiv) - 1U) |
        XTALOSC_OSC27M_CTL_CFG_OSC_BYPSS(config->oscMode);

    CLOCK_EnableAnalogClock(CCM_ANALOG, kCLOCK_OSC27MClke);
}

/*!
 * brief OSC27M deinit
 *
 * param config osc configuration
 */
void CLOCK_DeinitOSC27M(void)
{
    CLOCK_DisableAnalogClock(CCM_ANALOG, kCLOCK_OSC27MClke);
}

/*!
 * brief Enable CCGR clock gate and root clock gate for each module
 * User should set specific gate for each module according to the description
 * of the table of system clocks, gating and override in CCM chapter of
 * reference manual. Take care of that one module may need to set more than
 * one clock gate.
 *
 * param ccmGate Gate control for each module (see ref clock_ip_name_t enumeration).
 */
void CLOCK_EnableClock(clock_ip_name_t ccmGate)
{
    uint32_t ccgr    = CCM_TUPLE_CCGR(ccmGate);
    uint32_t rootClk = CCM_TUPLE_ROOT(ccmGate);

    CCM_REG_SET(ccgr) = (uint32_t)kCLOCK_ClockNeededAll;
    /* if root clock is 0xFFFFU, then skip enable root clock */
    if (rootClk != 0xFFFFU)
    {
        CCM_REG_SET(rootClk) = CCM_TARGET_ROOT_SET_ENABLE_MASK;
    }
}

/*!
 * brief Disable CCGR clock gate for the each module
 * User should set specific gate for each module according to the description
 * of the table of system clocks, gating and override in CCM chapter of
 * reference manual. Take care of that one module may need to set more than
 * one clock gate.
 *
 * param ccmGate Gate control for each module (see ref clock_ip_name_t enumeration).
 */
void CLOCK_DisableClock(clock_ip_name_t ccmGate)
{
    uint32_t ccgr    = CCM_TUPLE_CCGR(ccmGate);
    uint32_t rootClk = CCM_TUPLE_ROOT(ccmGate);

    CCM_REG(ccgr) = (uint32_t)kCLOCK_ClockNotNeeded;

    /* if root clock is 0xFFFFU, then skip disable root clock */
    if (rootClk != 0xFFFFU)
    {
        CCM_REG_CLR(rootClk) = CCM_TARGET_ROOT_CLR_ENABLE_MASK;
    }
}
