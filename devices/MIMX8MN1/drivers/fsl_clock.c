/*
 * Copyright 2018-2021 NXP
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

#define FracPLL_GNRL_CTL_Offset  (0U)
#define FracPLL_FDIV_CTL0_Offset (4U)
#define FracPLL_FDIV_CTL1_Offset (8U)

#define IntegerPLL_GNRL_CTL_Offset (0U)
#define IntegerPLL_DIV_CTL_Offset  (4U)
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
    uint32_t temp;

    switch (clockName)
    {
        case kCLOCK_CoreM7Clk:
            freq = CLOCK_GetCoreM7Freq();
            break;
        case kCLOCK_AxiClk:
            freq = CLOCK_GetAxiFreq();
            break;
        case kCLOCK_AhbClk:
            freq = CLOCK_GetAhbFreq();
            break;
        case kCLOCK_IpgClk:
        {
            temp = CLOCK_GetAhbFreq();
            freq = temp / CLOCK_GetRootPostDivider(kCLOCK_RootIpg);
            break;
        }
        case kCLOCK_EnetIpgClk:
            freq = CLOCK_GetEnetAxiFreq();
            break;
        case kCLOCK_Osc24MClk:
            freq = OSC24M_CLK_FREQ;
            break;
        case kCLOCK_ArmPllClk:
            freq = CLOCK_GetPllFreq(kCLOCK_ArmPllCtrl);
            break;
        case kCLOCK_DramPllClk:
            freq = CLOCK_GetPllFreq(kCLOCK_DramPllCtrl);
            break;
        case kCLOCK_SysPll1Clk:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll1Ctrl);
            break;
        case kCLOCK_SysPll1Div2Clk:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll1Ctrl) / 2U;
            break;
        case kCLOCK_SysPll1Div3Clk:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll1Ctrl) / 3U;
            break;
        case kCLOCK_SysPll1Div4Clk:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll1Ctrl) / 4U;
            break;
        case kCLOCK_SysPll1Div5Clk:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll1Ctrl) / 5U;
            break;
        case kCLOCK_SysPll1Div6Clk:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll1Ctrl) / 6U;
            break;
        case kCLOCK_SysPll1Div8Clk:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll1Ctrl) / 8U;
            break;
        case kCLOCK_SysPll1Div10Clk:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll1Ctrl) / 10U;
            break;
        case kCLOCK_SysPll1Div20Clk:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll1Ctrl) / 20U;
            break;
        case kCLOCK_SysPll2Clk:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll2Ctrl);
            break;
        case kCLOCK_SysPll2Div2Clk:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll2Ctrl) / 2U;
            break;
        case kCLOCK_SysPll2Div3Clk:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll2Ctrl) / 3U;
            break;
        case kCLOCK_SysPll2Div4Clk:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll2Ctrl) / 4U;
            break;
        case kCLOCK_SysPll2Div5Clk:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll2Ctrl) / 5U;
            break;
        case kCLOCK_SysPll2Div6Clk:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll2Ctrl) / 6U;
            break;
        case kCLOCK_SysPll2Div8Clk:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll2Ctrl) / 8U;
            break;
        case kCLOCK_SysPll2Div10Clk:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll2Ctrl) / 10U;
            break;
        case kCLOCK_SysPll2Div20Clk:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll2Ctrl) / 20U;
            break;
        case kCLOCK_SysPll3Clk:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll3Ctrl);
            break;
        case kCLOCK_AudioPll1Clk:
            freq = CLOCK_GetPllFreq(kCLOCK_AudioPll1Ctrl);
            break;
        case kCLOCK_AudioPll2Clk:
            freq = CLOCK_GetPllFreq(kCLOCK_AudioPll2Ctrl);
            break;
        case kCLOCK_VideoPll1Clk:
            freq = CLOCK_GetPllFreq(kCLOCK_VideoPll1Ctrl);
            break;
        case kCLOCK_ExtClk1:
        case kCLOCK_ExtClk2:
        case kCLOCK_ExtClk3:
        case kCLOCK_ExtClk4:
            freq = CLKPAD_FREQ;
            break;
        default:
            freq = 0U;
            break;
    }
    return freq;
}

/*!
 * brief Gets the frequency of selected clock root.
 *
 * param clockRoot The clock root used to get the frequency, please refer to @ref clock_root_t.
 * return The frequency of selected clock root.
 */
uint32_t CLOCK_GetClockRootFreq(clock_root_t clockRoot)
{
    static const clock_name_t clockRootSourceArray[][8]          = CLOCK_ROOT_SOURCE;
    static const clock_root_control_t clockRootControlArray[]    = CLOCK_ROOT_CONTROL_TUPLE;

    clock_root_control_t clockRootControl                        = clockRootControlArray[(uint8_t)clockRoot];

    uint32_t freq = 0U;
    uint32_t pre  = CLOCK_GetRootPreDivider(clockRootControl);
    uint32_t post = CLOCK_GetRootPostDivider(clockRootControl);
    uint32_t mux = CLOCK_GetRootMux(clockRootControl);

    clock_name_t clockSourceName;

    clockSourceName = clockRootSourceArray[(uint8_t)clockRoot][mux];

    assert(clockSourceName != kCLOCK_NoneName);

    freq = CLOCK_GetFreq(clockSourceName);

    if (clockRoot == kCLOCK_IpgClkRoot)
    {
        freq /= CLOCK_GetRootPostDivider(kCLOCK_RootIpg);
    }
    if (clockRoot == kCLOCK_AudioIpgClkRoot)
    {
        freq /= CLOCK_GetRootPostDivider(kCLOCK_RootAudioIpg);
    }

    return freq / pre / post;
}

/*!
 * brief Get the CCM Cortex M7 core frequency.
 *
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetCoreM7Freq(void)
{
    uint32_t freq;
    uint32_t pre  = CLOCK_GetRootPreDivider(kCLOCK_RootM7);
    uint32_t post = CLOCK_GetRootPostDivider(kCLOCK_RootM7);

    switch (CLOCK_GetRootMux(kCLOCK_RootM7))
    {
        case (uint32_t)kCLOCK_M7RootmuxOsc24M:
            freq = OSC24M_CLK_FREQ;
            break;
        case (uint32_t)kCLOCK_M7RootmuxSysPll2Div5:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll2Ctrl) / 5U;
            break;
        case (uint32_t)kCLOCK_M7RootmuxSysPll2Div4:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll2Ctrl) / 4U;
            break;
        case (uint32_t)kCLOCK_M7RootmuxSysPll1Div3:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll1Ctrl) / 3U;
            break;
        case (uint32_t)kCLOCK_M7RootmuxSysPll1:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll1Ctrl);
            break;
        case (uint32_t)kCLOCK_M7RootmuxAudioPll1:
            freq = CLOCK_GetPllFreq(kCLOCK_AudioPll1Ctrl);
            break;
        case (uint32_t)kCLOCK_M7RootmuxVideoPll1:
            freq = CLOCK_GetPllFreq(kCLOCK_VideoPll1Ctrl);
            break;
        case (uint32_t)kCLOCK_M7RootmuxSysPll3:
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
        case (uint32_t)kCLOCK_AxiRootmuxOsc24M:
            freq = OSC24M_CLK_FREQ;
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
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll1Ctrl) / 8UL;
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
        case (uint32_t)kCLOCK_AhbRootmuxOsc24M:
            freq = OSC24M_CLK_FREQ;
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
 * brief Get the CCM Enet AXI bus frequency.
 *
 * return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetEnetAxiFreq(void)
{
    uint32_t freq;
    uint32_t pre  = CLOCK_GetRootPreDivider(kCLOCK_RootEnetAxi);
    uint32_t post = CLOCK_GetRootPostDivider(kCLOCK_RootEnetAxi);

    switch (CLOCK_GetRootMux(kCLOCK_RootEnetAxi))
    {
        case (uint32_t)kCLOCK_EnetAxiRootmuxOsc24M:
            freq = OSC24M_CLK_FREQ;
            break;
        case (uint32_t)kCLOCK_EnetAxiRootmuxSysPll1Div3:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll1Ctrl) / 3U;
            break;
        case (uint32_t)kCLOCK_EnetAxiRootmuxSysPll1:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll1Ctrl);
            break;
        case (uint32_t)kCLOCK_EnetAxiRootmuxSysPll2Div4:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll2Ctrl) / 4U;
            break;
        case (uint32_t)kCLOCK_EnetAxiRootmuxSysPll2Div5:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll2Ctrl) / 5U;
            break;
        case (uint32_t)kCLOCK_EnetAxiRootmuxAudioPll1:
            freq = CLOCK_GetPllFreq(kCLOCK_AudioPll1Ctrl);
            break;
        case (uint32_t)kCLOCK_EnetAxiRootmuxVideoPll1:
            freq = CLOCK_GetPllFreq(kCLOCK_VideoPll1Ctrl);
            break;
        case (uint32_t)kCLOCK_EnetAxiRootmuxSysPll3:
            freq = CLOCK_GetPllFreq(kCLOCK_SystemPll3Ctrl);
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

    if (ctrl < kCLOCK_ArmPllCtrl)
    {
        clkSel =
            (uint8_t)((CCM_ANALOG_TUPLE_REG(CCM_ANALOG, ctrl) & CCM_ANALOG_AUDIO_PLL1_GEN_CTRL_PLL_REF_CLK_SEL_MASK));
    }
    else
    {
        clkSel = (uint8_t)(CCM_ANALOG_TUPLE_REG(CCM_ANALOG, ctrl) & CCM_ANALOG_SYS_PLL1_GEN_CTRL_PLL_REF_CLK_SEL_MASK);
    }

    switch (clkSel)
    {
        case kANALOG_PllRefOsc24M:
            refClkFreq = OSC24M_CLK_FREQ;
            break;

        case kANALOG_PllPadClk:
            /* The value of PAD CLK need user to define according to the actual condition. */
            refClkFreq = CLKPAD_FREQ;
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
    uint32_t pllFreq       = 0U;
    uint32_t pllRefFreq    = 0U;
    bool intergerPllBypass = false;
    bool fracPllBypass     = false;

    pllRefFreq = CLOCK_GetPllRefClkFreq(pll);

    switch (pll)
    {
        /* Integer PLL frequency */
        case kCLOCK_ArmPllCtrl:
            intergerPllBypass = CLOCK_IsPllBypassed(CCM_ANALOG, kCLOCK_ArmPllPwrBypassCtrl);
            break;
        case kCLOCK_SystemPll1Ctrl:
            intergerPllBypass = CLOCK_IsPllBypassed(CCM_ANALOG, kCLOCK_SysPll1InternalPll1BypassCtrl);
            break;
        case kCLOCK_SystemPll2Ctrl:
            intergerPllBypass = CLOCK_IsPllBypassed(CCM_ANALOG, kCLOCK_SysPll2InternalPll1BypassCtrl);
            break;
        case kCLOCK_SystemPll3Ctrl:
            intergerPllBypass = CLOCK_IsPllBypassed(CCM_ANALOG, kCLOCK_SysPll3InternalPll1BypassCtrl);
            break;
        /* Fractional PLL frequency */
        case kCLOCK_AudioPll1Ctrl:
            fracPllBypass = CLOCK_IsPllBypassed(CCM_ANALOG, kCLOCK_AudioPll1BypassCtrl);
            break;
        case kCLOCK_AudioPll2Ctrl:
            fracPllBypass = CLOCK_IsPllBypassed(CCM_ANALOG, kCLOCK_AudioPll2BypassCtrl);
            break;
        case kCLOCK_VideoPll1Ctrl:
            fracPllBypass = CLOCK_IsPllBypassed(CCM_ANALOG, kCLOCK_VideoPll1BypassCtrl);
            break;
        case kCLOCK_DramPllCtrl:
            fracPllBypass = CLOCK_IsPllBypassed(CCM_ANALOG, kCLOCK_DramPllInternalPll1BypassCtrl);
            break;
        default:
            fracPllBypass = false;
            break;
    }
    if (pll < kCLOCK_ArmPllCtrl)
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
        if (intergerPllBypass)
        {
            /* if PLL is bypass, return reference clock directly */
            pllFreq = pllRefFreq;
        }
        else
        {
            pllFreq = CLOCK_GetIntegerPllFreq(CCM_ANALOG, pll, pllRefFreq, false);
        }
    }

    return (uint32_t)pllFreq;
}

/*!
 * brief Initializes the ANALOG ARM PLL.
 *
 * param config Pointer to the configuration structure(see ref ccm_analog_integer_pll_config_t enumeration).
 *
 * note This function can't detect whether the Arm PLL has been enabled and
 * used by some IPs.
 */
void CLOCK_InitArmPll(const ccm_analog_integer_pll_config_t *config)
{
    assert(config != NULL);

    /* Integer PLL configuration */
    CLOCK_InitIntegerPll(CCM_ANALOG, config, kCLOCK_ArmPllCtrl);
    /* Disable PLL bypass */
    CLOCK_SetPllBypass(CCM_ANALOG, kCLOCK_ArmPllPwrBypassCtrl, false);
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
 * param config Pointer to the configuration structure(see ref ccm_analog_integer_pll_config_t enumeration).
 *
 * note This function can't detect whether the SYS PLL has been enabled and
 * used by some IPs.
 */
void CLOCK_InitSysPll1(const ccm_analog_integer_pll_config_t *config)
{
    assert(config != NULL);

    /* Integer PLL configuration */
    CLOCK_InitIntegerPll(CCM_ANALOG, config, kCLOCK_SystemPll1Ctrl);
    /* Disable PLL bypass */
    CLOCK_SetPllBypass(CCM_ANALOG, kCLOCK_SysPll1InternalPll1BypassCtrl, false);
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
 * param config Pointer to the configuration structure(see ref ccm_analog_integer_pll_config_t enumeration).
 *
 * note This function can't detect whether the SYS PLL has been enabled and
 * used by some IPs.
 */
void CLOCK_InitSysPll2(const ccm_analog_integer_pll_config_t *config)
{
    assert(config != NULL);

    /* Integer PLL configuration */
    CLOCK_InitIntegerPll(CCM_ANALOG, config, kCLOCK_SystemPll2Ctrl);
    /* Disable PLL bypass */
    CLOCK_SetPllBypass(CCM_ANALOG, kCLOCK_SysPll2InternalPll1BypassCtrl, false);
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
 * param config Pointer to the configuration structure(see ref ccm_analog_integer_pll_config_t enumeration).
 *
 * note This function can't detect whether the SYS PLL has been enabled and
 * used by some IPs.
 */
void CLOCK_InitSysPll3(const ccm_analog_integer_pll_config_t *config)
{
    assert(config != NULL);

    /* Integer PLL configuration */
    CLOCK_InitIntegerPll(CCM_ANALOG, config, kCLOCK_SystemPll3Ctrl);
    /* Disable PLL bypass */
    CLOCK_SetPllBypass(CCM_ANALOG, kCLOCK_SysPll3InternalPll1BypassCtrl, false);
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
    assert((config->mainDiv >= 64U) && (config->mainDiv <= 1023U));
    assert((config->preDiv >= 1U) && (config->preDiv <= 63U));
    assert(config->postDiv <= 6U);

    assert(type < kCLOCK_ArmPllCtrl);

    uint32_t fracCfg0 = CCM_ANALOG_TUPLE_REG_OFF(base, type, FracPLL_GNRL_CTL_Offset) &
                        ~((uint32_t)1 << CCM_ANALOG_AUDIO_PLL1_GEN_CTRL_PLL_RST_SHIFT);
    uint32_t fracCfg1 = CCM_ANALOG_TUPLE_REG_OFF(base, type, FracPLL_FDIV_CTL0_Offset);
    uint32_t fracCfg2 = CCM_ANALOG_TUPLE_REG_OFF(base, type, FracPLL_FDIV_CTL1_Offset);

    /* power down the fractional PLL first */
    CCM_ANALOG_TUPLE_REG_OFF(base, type, FracPLL_GNRL_CTL_Offset) = fracCfg0;

    CCM_ANALOG_TUPLE_REG_OFF(base, type, FracPLL_FDIV_CTL0_Offset) =
        (fracCfg1 &
         (~(CCM_ANALOG_AUDIO_PLL1_FDIV_CTL0_PLL_MAIN_DIV_MASK | CCM_ANALOG_AUDIO_PLL1_FDIV_CTL0_PLL_PRE_DIV_MASK |
            CCM_ANALOG_AUDIO_PLL1_FDIV_CTL0_PLL_POST_DIV_MASK))) |
        CCM_ANALOG_AUDIO_PLL1_FDIV_CTL0_PLL_MAIN_DIV(config->mainDiv) |
        CCM_ANALOG_AUDIO_PLL1_FDIV_CTL0_PLL_PRE_DIV(config->preDiv) |
        CCM_ANALOG_AUDIO_PLL1_FDIV_CTL0_PLL_POST_DIV(config->postDiv);

    CCM_ANALOG_TUPLE_REG_OFF(base, type, FracPLL_FDIV_CTL1_Offset) =
        (fracCfg2 & (~(CCM_ANALOG_AUDIO_PLL1_FDIV_CTL1_PLL_DSM_MASK))) |
        CCM_ANALOG_AUDIO_PLL1_FDIV_CTL1_PLL_DSM(config->dsm);

    /* power up the fractional pll */
    CCM_ANALOG_TUPLE_REG_OFF(base, type, FracPLL_GNRL_CTL_Offset) |= CCM_ANALOG_AUDIO_PLL1_GEN_CTRL_PLL_RST_MASK;
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
    assert(type < kCLOCK_ArmPllCtrl);

    uint32_t fracCfg1 = CCM_ANALOG_TUPLE_REG_OFF(base, type, FracPLL_FDIV_CTL0_Offset);
    uint32_t fracCfg2 = CCM_ANALOG_TUPLE_REG_OFF(base, type, FracPLL_FDIV_CTL1_Offset);
    uint64_t fracClk  = 0U;

    uint32_t mainDiv = CCM_BIT_FIELD_EXTRACTION(fracCfg1, CCM_ANALOG_AUDIO_PLL1_FDIV_CTL0_PLL_MAIN_DIV_MASK,
                                                CCM_ANALOG_AUDIO_PLL1_FDIV_CTL0_PLL_MAIN_DIV_SHIFT);
    uint8_t preDiv   = (uint8_t)CCM_BIT_FIELD_EXTRACTION(fracCfg1, CCM_ANALOG_AUDIO_PLL1_FDIV_CTL0_PLL_PRE_DIV_MASK,
                                                       CCM_ANALOG_AUDIO_PLL1_FDIV_CTL0_PLL_PRE_DIV_SHIFT);
    uint8_t postDiv  = (uint8_t)CCM_BIT_FIELD_EXTRACTION(fracCfg1, CCM_ANALOG_AUDIO_PLL1_FDIV_CTL0_PLL_POST_DIV_MASK,
                                                        CCM_ANALOG_AUDIO_PLL1_FDIV_CTL0_PLL_POST_DIV_SHIFT);
    uint32_t dsm     = CCM_BIT_FIELD_EXTRACTION(fracCfg2, CCM_ANALOG_AUDIO_PLL1_FDIV_CTL1_PLL_DSM_MASK,
                                            CCM_ANALOG_AUDIO_PLL1_FDIV_CTL1_PLL_DSM_SHIFT);

    fracClk = (uint64_t)((uint64_t)refClkFreq * ((uint64_t)mainDiv * 65536ULL + dsm) /
                         (65536ULL * (uint32_t)preDiv * (1ULL << postDiv)));

    return (uint32_t)fracClk;
}

/*!
 * brief Initializes the ANALOG Integer PLL.
 *
 * param base CCM ANALOG base address
 * param config Pointer to the configuration structure(see ref ccm_analog_integer_pll_config_t enumeration).
 * param type integer pll type
 *
 */
void CLOCK_InitIntegerPll(CCM_ANALOG_Type *base, const ccm_analog_integer_pll_config_t *config, clock_pll_ctrl_t type)
{
    assert(config != NULL);
    assert((config->mainDiv >= 64U) && (config->mainDiv <= 1023U));
    assert((config->preDiv >= 1U) && (config->preDiv <= 63U));
    assert(config->postDiv <= 6U);

    assert(type >= kCLOCK_SystemPll1Ctrl);

    uint32_t integerCfg0 = CCM_ANALOG_TUPLE_REG_OFF(base, type, IntegerPLL_GNRL_CTL_Offset) &
                           ~((uint32_t)1 << CCM_ANALOG_SYS_PLL1_GEN_CTRL_PLL_RST_SHIFT);
    uint32_t integerCfg1 = CCM_ANALOG_TUPLE_REG_OFF(base, type, IntegerPLL_DIV_CTL_Offset);

    /* power down the Integer PLL first */
    CCM_ANALOG_TUPLE_REG_OFF(base, type, IntegerPLL_GNRL_CTL_Offset) = integerCfg0;

    /* pll mux configuration */
    CCM_ANALOG_TUPLE_REG_OFF(base, type, IntegerPLL_GNRL_CTL_Offset) =
        (integerCfg0 & (~CCM_ANALOG_SYS_PLL1_GEN_CTRL_PLL_REF_CLK_SEL_MASK)) | config->refSel;

    /* divider configuration */
    CCM_ANALOG_TUPLE_REG_OFF(base, type, IntegerPLL_DIV_CTL_Offset) =
        (integerCfg1 &
         (~(CCM_ANALOG_SYS_PLL1_FDIV_CTL0_PLL_MAIN_DIV_MASK | CCM_ANALOG_SYS_PLL1_FDIV_CTL0_PLL_PRE_DIV_MASK |
            CCM_ANALOG_SYS_PLL1_FDIV_CTL0_PLL_POST_DIV_MASK))) |
        CCM_ANALOG_SYS_PLL1_FDIV_CTL0_PLL_MAIN_DIV(config->mainDiv) |
        CCM_ANALOG_SYS_PLL1_FDIV_CTL0_PLL_PRE_DIV(config->preDiv) |
        CCM_ANALOG_SYS_PLL1_FDIV_CTL0_PLL_POST_DIV(config->postDiv);

    /* power up the Integer PLL */
    CCM_ANALOG_TUPLE_REG_OFF(base, type, IntegerPLL_GNRL_CTL_Offset) |= CCM_ANALOG_SYS_PLL1_GEN_CTRL_PLL_RST_MASK;
}

/*!
 * brief Get the ANALOG Integer PLL clock frequency.
 *
 * param base CCM ANALOG base address.
 * param type integer pll type
 * param pll1Bypass pll1 bypass flag
 *
 * return  Clock frequency
 */
uint32_t CLOCK_GetIntegerPllFreq(CCM_ANALOG_Type *base, clock_pll_ctrl_t type, uint32_t refClkFreq, bool pll1Bypass)
{
    assert(type >= kCLOCK_SystemPll1Ctrl);

    uint32_t integerCfg1 = CCM_ANALOG_TUPLE_REG_OFF(base, type, IntegerPLL_DIV_CTL_Offset);
    uint64_t pllOutClock = 0U;

    uint32_t mainDiv = CCM_BIT_FIELD_EXTRACTION(integerCfg1, CCM_ANALOG_SYS_PLL1_FDIV_CTL0_PLL_MAIN_DIV_MASK,
                                                CCM_ANALOG_SYS_PLL1_FDIV_CTL0_PLL_MAIN_DIV_SHIFT);
    uint8_t preDiv   = (uint8_t)CCM_BIT_FIELD_EXTRACTION(integerCfg1, CCM_ANALOG_SYS_PLL1_FDIV_CTL0_PLL_PRE_DIV_MASK,
                                                       CCM_ANALOG_SYS_PLL1_FDIV_CTL0_PLL_PRE_DIV_SHIFT);
    uint8_t postDiv  = (uint8_t)CCM_BIT_FIELD_EXTRACTION(integerCfg1, CCM_ANALOG_SYS_PLL1_FDIV_CTL0_PLL_POST_DIV_MASK,
                                                        CCM_ANALOG_SYS_PLL1_FDIV_CTL0_PLL_POST_DIV_SHIFT);

    if (pll1Bypass)
    {
        pllOutClock = refClkFreq;
    }

    else
    {
        pllOutClock = (uint64_t)refClkFreq * mainDiv / (((uint64_t)(1U) << postDiv) * preDiv);
    }

    return (uint32_t)pllOutClock;
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
    uint32_t ccgr = CCM_TUPLE_CCGR(ccmGate);

    CCM_REG_SET(ccgr) = (uintptr_t)kCLOCK_ClockNeededAll;
#if !(defined(NOT_CONFIG_CLK_ROOT) && NOT_CONFIG_CLK_ROOT)
    uint32_t rootClk = CCM_TUPLE_ROOT(ccmGate);
    /* if root clock is 0xFFFFU, then skip enable root clock */
    if (rootClk != 0xFFFFU)
    {
        CCM_REG_SET(rootClk) = CCM_TARGET_ROOT_SET_ENABLE_MASK;
    }
#endif
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
    uint32_t ccgr = CCM_TUPLE_CCGR(ccmGate);

    CCM_REG(ccgr) = (uintptr_t)kCLOCK_ClockNotNeeded;
#if !(defined(NOT_CONFIG_CLK_ROOT) && NOT_CONFIG_CLK_ROOT)
    uint32_t rootClk = CCM_TUPLE_ROOT(ccmGate);
    /* if root clock is 0xFFFFU, then skip disable root clock */
    if (rootClk != 0xFFFFU)
    {
        CCM_REG_CLR(rootClk) = CCM_TARGET_ROOT_CLR_ENABLE_MASK;
    }
#endif
}
