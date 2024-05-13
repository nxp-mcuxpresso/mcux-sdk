/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_clock.h"
#include "fsl_pmu.h"
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.clock"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* To make full use of CM7 hardware FPU, use double instead of uint64_t in clock driver to
achieve better performance, it is depend on the IDE Floating point settings, if double precision is selected
in IDE, clock_64b_t will switch to double type automatically. only support IAR and MDK here */
#if __FPU_USED

#if (defined(__ICCARM__))

#if (__ARMVFP__ >= __ARMFPV5__) && \
    (__ARM_FP == 0xE) /*0xe implies support for half, single and double precision operations*/
typedef double clock_64b_t;
#else
typedef uint64_t clock_64b_t;
#endif

#elif (defined(__GNUC__))

#if (__ARM_FP == 0xE) /*0xe implies support for half, single and double precision operations*/
typedef double clock_64b_t;
#else
typedef uint64_t clock_64b_t;
#endif

#elif defined(__CC_ARM) || defined(__ARMCC_VERSION)

#if defined __TARGET_FPU_FPV5_D16
typedef double clock_64b_t;
#else
typedef uint64_t clock_64b_t;
#endif

#else
typedef uint64_t clock_64b_t;
#endif

#else
typedef uint64_t clock_64b_t;
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void ANATOP_PllSetPower(PLL_Type *base, bool enable);
static void ANATOP_PllBypass(PLL_Type *base, bool bypass);
static void ANATOP_PllEnablePllReg(PLL_Type *base, bool enable);
static void ANATOP_PllHoldRingOff(PLL_Type *base, bool off);
static void ANATOP_PllToggleHoldRingOff(PLL_Type *base, uint32_t delay_us);
static void ANATOP_PllEnableClk(PLL_Type *base, bool enable);
static void ANATOP_PllConfigure(
    PLL_Type *base, uint8_t div, uint32_t numer, uint8_t post_div, uint32_t denom, const clock_pll_ss_config_t *ss);
static void ANATOP_AudioPllGate(bool enable);
static void ANATOP_AudioPllSwEnClk(bool enable);
static void ANATOP_SysPll1Gate(bool enable);
static void ANATOP_SysPll1Div2En(bool enable);
static void ANATOP_SysPll1Div5En(bool enable);
static void ANATOP_SysPll1SwEnClk(bool enable);
static void ANATOP_SysPll1WaitStable(void);
static void ANATOP_PllEnableSs(PLL_Type *base, bool enable);
#ifndef GET_FREQ_FROM_OBS
static uint32_t CLOCK_GetAudioPllFreq(void);
#endif
/*******************************************************************************
 * Code
 ******************************************************************************/

#define ARM_PLL_DIV_SEL_MIN 104
#define ARM_PLL_DIV_SEL_MAX 208

void CLOCK_InitArmPll(const clock_arm_pll_config_t *config)
{
    assert((config->loopDivider <= (uint32_t)ARM_PLL_DIV_SEL_MAX) &&
           (config->loopDivider >= (uint32_t)ARM_PLL_DIV_SEL_MIN));

    uint32_t reg;

    if (((ANADIG_PLL->ARM_PLL_CTRL & ANADIG_PLL_ARM_PLL_CTRL_POWERUP_MASK) != 0UL) &&
        ((ANADIG_PLL->ARM_PLL_CTRL & ANADIG_PLL_ARM_PLL_CTRL_DIV_SELECT_MASK) ==
         ANADIG_PLL_ARM_PLL_CTRL_DIV_SELECT(config->loopDivider)) &&
        ((ANADIG_PLL->ARM_PLL_CTRL & ANADIG_PLL_ARM_PLL_CTRL_POST_DIV_SEL_MASK) ==
         ANADIG_PLL_ARM_PLL_CTRL_POST_DIV_SEL(config->postDivider)))
    {
        /* no need to reconfigure the PLL if all the configuration is the same */
        if ((ANADIG_PLL->ARM_PLL_CTRL & ANADIG_PLL_ARM_PLL_CTRL_ENABLE_CLK_MASK) == 0UL)
        {
            ANADIG_PLL->ARM_PLL_CTRL |= ANADIG_PLL_ARM_PLL_CTRL_ENABLE_CLK_MASK;
        }
        if ((ANADIG_PLL->ARM_PLL_CTRL & ANADIG_PLL_ARM_PLL_CTRL_ARM_PLL_GATE_MASK) != 0UL)
        {
            ANADIG_PLL->ARM_PLL_CTRL &= ~ANADIG_PLL_ARM_PLL_CTRL_ARM_PLL_GATE_MASK;
        }
        return;
    }

    PMU_StaticEnablePllLdo(ANADIG_PMU);

    reg = ANADIG_PLL->ARM_PLL_CTRL & (~ANADIG_PLL_ARM_PLL_CTRL_ARM_PLL_STABLE_MASK);
    if ((reg & (ANADIG_PLL_ARM_PLL_CTRL_POWERUP_MASK | ANADIG_PLL_ARM_PLL_CTRL_ENABLE_CLK_MASK)) != 0UL)
    {
        /* Power down the PLL. */
        reg &= ~(ANADIG_PLL_ARM_PLL_CTRL_POWERUP_MASK | ANADIG_PLL_ARM_PLL_CTRL_ENABLE_CLK_MASK);
        reg |= ANADIG_PLL_ARM_PLL_CTRL_ARM_PLL_GATE_MASK;
        ANADIG_PLL->ARM_PLL_CTRL = reg;
    }

    /* Set the configuration. */
    reg &= ~(ANADIG_PLL_ARM_PLL_CTRL_DIV_SELECT_MASK | ANADIG_PLL_ARM_PLL_CTRL_POST_DIV_SEL_MASK);
    reg |= (ANADIG_PLL_ARM_PLL_CTRL_DIV_SELECT(config->loopDivider) |
            ANADIG_PLL_ARM_PLL_CTRL_POST_DIV_SEL(config->postDivider)) |
           ANADIG_PLL_ARM_PLL_CTRL_ARM_PLL_GATE_MASK | ANADIG_PLL_ARM_PLL_CTRL_POWERUP_MASK;
    ANADIG_PLL->ARM_PLL_CTRL = reg;
    __DSB();
    __ISB();
    SDK_DelayAtLeastUs(30, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

    /* Wait for the PLL stable, */
    while (0U == (ANADIG_PLL->ARM_PLL_CTRL & ANADIG_PLL_ARM_PLL_CTRL_ARM_PLL_STABLE_MASK))
    {
    }

    /* Enable and ungate the clock. */
    reg |= ANADIG_PLL_ARM_PLL_CTRL_ENABLE_CLK_MASK;
    reg &= ~ANADIG_PLL_ARM_PLL_CTRL_ARM_PLL_GATE_MASK;
    ANADIG_PLL->ARM_PLL_CTRL = reg;
}

void CLOCK_DeinitArmPll(void)
{
    uint32_t reg = ANADIG_PLL->ARM_PLL_CTRL & (~ANADIG_PLL_ARM_PLL_CTRL_ARM_PLL_STABLE_MASK);

    reg &= ~(ANADIG_PLL_ARM_PLL_CTRL_POWERUP_MASK | ANADIG_PLL_ARM_PLL_CTRL_ENABLE_CLK_MASK);
    reg |= ANADIG_PLL_ARM_PLL_CTRL_ARM_PLL_GATE_MASK;
    ANADIG_PLL->ARM_PLL_CTRL = reg;
}

void CLOCK_CalcPllSpreadSpectrum(uint32_t factor, uint32_t range, uint32_t mod, clock_pll_ss_config_t *ss)
{
    assert(ss != NULL);

    ss->stop = (uint16_t)(factor * range / XTAL_FREQ);
    ss->step = (uint16_t)((mod << 1UL) * (uint32_t)(ss->stop) / XTAL_FREQ);
}

/* 528PLL */
void CLOCK_InitSysPll2(const clock_sys_pll2_config_t *config)
{
    uint32_t reg;

    if ((ANADIG_PLL->SYS_PLL2_CTRL & ANADIG_PLL_SYS_PLL2_CTRL_POWERUP_MASK) != 0UL)
    {
        if ((config == NULL) ||
            ((0UL == (ANADIG_PLL->SYS_PLL2_SS & ANADIG_PLL_SYS_PLL2_SS_ENABLE_MASK)) && (!config->ssEnable)) ||
            ((ANADIG_PLL_SYS_PLL2_SS_ENABLE(config->ssEnable) | ANADIG_PLL_SYS_PLL2_SS_STOP(config->ss->stop) |
              ANADIG_PLL_SYS_PLL2_SS_STEP(config->ss->step)) == ANADIG_PLL->SYS_PLL2_SS))
        {
            /* no need to reconfigure the PLL if all the configuration is the same */
            if (0UL == (ANADIG_PLL->SYS_PLL2_CTRL & ANADIG_PLL_SYS_PLL2_CTRL_ENABLE_CLK_MASK))
            {
                ANADIG_PLL->SYS_PLL2_CTRL |= ANADIG_PLL_SYS_PLL2_CTRL_ENABLE_CLK_MASK;
            }

            if ((ANADIG_PLL->SYS_PLL2_CTRL & ANADIG_PLL_SYS_PLL2_CTRL_SYS_PLL2_GATE_MASK) != 0UL)
            {
                ANADIG_PLL->SYS_PLL2_CTRL &= ~ANADIG_PLL_SYS_PLL2_CTRL_SYS_PLL2_GATE_MASK;
            }
            return;
        }
    }

    PMU_StaticEnablePllLdo(ANADIG_PMU);
    /* Gate all PFDs */
    ANADIG_PLL->SYS_PLL2_PFD |=
        ANADIG_PLL_SYS_PLL2_PFD_PFD0_DIV1_CLKGATE(1) | ANADIG_PLL_SYS_PLL2_PFD_PFD1_DIV1_CLKGATE(1) |
        ANADIG_PLL_SYS_PLL2_PFD_PFD2_DIV1_CLKGATE(1) | ANADIG_PLL_SYS_PLL2_PFD_PFD3_DIV1_CLKGATE(1);

    reg = ANADIG_PLL->SYS_PLL2_CTRL;
    if ((reg & (ANADIG_PLL_SYS_PLL2_CTRL_POWERUP_MASK | ANADIG_PLL_SYS_PLL2_CTRL_ENABLE_CLK_MASK)) != 0UL)
    {
        /* Power down the PLL. */
        reg &= ~(ANADIG_PLL_SYS_PLL2_CTRL_POWERUP_MASK | ANADIG_PLL_SYS_PLL2_CTRL_ENABLE_CLK_MASK);
        reg |= ANADIG_PLL_SYS_PLL2_CTRL_SYS_PLL2_GATE_MASK;
        ANADIG_PLL->SYS_PLL2_CTRL = reg;
    }

    /* Config PLL */
    if ((config != NULL) && (config->ssEnable) && (config->ss != NULL))
    {
        ANADIG_PLL->SYS_PLL2_MFD = ANADIG_PLL_SYS_PLL2_MFD_MFD(config->mfd);
        ANADIG_PLL->SYS_PLL2_SS  = (ANADIG_PLL_SYS_PLL2_SS_ENABLE_MASK | ANADIG_PLL_SYS_PLL2_SS_STOP(config->ss->stop) |
                                   ANADIG_PLL_SYS_PLL2_SS_STEP(config->ss->step));
    }

    /* REG_EN = 1, GATE = 1, DIV_SEL = 0, POWERUP = 0 */
    reg                       = ANADIG_PLL_SYS_PLL2_CTRL_PLL_REG_EN(1) | ANADIG_PLL_SYS_PLL2_CTRL_SYS_PLL2_GATE(1);
    ANADIG_PLL->SYS_PLL2_CTRL = reg;
    /* Wait until LDO is stable */
    SDK_DelayAtLeastUs(30, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

    /* REG_EN = 1, GATE = 1, DIV_SEL = 0, POWERUP = 1, HOLDRING_OFF = 1 */
    reg |= ANADIG_PLL_SYS_PLL2_CTRL_POWERUP(1) | ANADIG_PLL_SYS_PLL2_CTRL_HOLD_RING_OFF_MASK;
    ANADIG_PLL->SYS_PLL2_CTRL = reg;
    SDK_DelayAtLeastUs(250, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

    /* REG_EN = 1, GATE = 1, DIV_SEL = 0, POWERUP = 1, HOLDRING_OFF = 0 */
    reg &= ~ANADIG_PLL_SYS_PLL2_CTRL_HOLD_RING_OFF_MASK;
    ANADIG_PLL->SYS_PLL2_CTRL = reg;
    /* Wait for PLL stable */
    while (ANADIG_PLL_SYS_PLL2_CTRL_SYS_PLL2_STABLE_MASK !=
           (ANADIG_PLL->SYS_PLL2_CTRL & ANADIG_PLL_SYS_PLL2_CTRL_SYS_PLL2_STABLE_MASK))
    {
    }

    /* REG_EN = 1, GATE = 1, DIV_SEL = 0, POWERUP = 1, HOLDRING_OFF = 0, CLK = 1*/
    reg |= ANADIG_PLL_SYS_PLL2_CTRL_ENABLE_CLK_MASK;
    ANADIG_PLL->SYS_PLL2_CTRL = reg;

    /* REG_EN = 1, GATE = 0, DIV_SEL = 0, POWERUP = 1, HOLDRING_OFF = 0, CLK = 1*/
    reg &= ~ANADIG_PLL_SYS_PLL2_CTRL_SYS_PLL2_GATE_MASK;
    ANADIG_PLL->SYS_PLL2_CTRL = reg;
    ANADIG_PLL->SYS_PLL2_PFD &=
        ~(ANADIG_PLL_SYS_PLL2_PFD_PFD0_DIV1_CLKGATE(1) | ANADIG_PLL_SYS_PLL2_PFD_PFD1_DIV1_CLKGATE(1) |
          ANADIG_PLL_SYS_PLL2_PFD_PFD2_DIV1_CLKGATE(1) | ANADIG_PLL_SYS_PLL2_PFD_PFD3_DIV1_CLKGATE(1));
}

void CLOCK_DeinitSysPll2(void)
{
    ANADIG_PLL->SYS_PLL2_PFD |=
        ANADIG_PLL_SYS_PLL2_PFD_PFD0_DIV1_CLKGATE(1) | ANADIG_PLL_SYS_PLL2_PFD_PFD1_DIV1_CLKGATE(1) |
        ANADIG_PLL_SYS_PLL2_PFD_PFD2_DIV1_CLKGATE(1) | ANADIG_PLL_SYS_PLL2_PFD_PFD3_DIV1_CLKGATE(1);

    ANADIG_PLL->SYS_PLL2_CTRL |= ANADIG_PLL_SYS_PLL2_CTRL_SYS_PLL2_GATE_MASK;
    ANADIG_PLL->SYS_PLL2_CTRL &= ~(ANADIG_PLL_SYS_PLL2_CTRL_ENABLE_CLK_MASK | ANADIG_PLL_SYS_PLL2_CTRL_POWERUP_MASK |
                                   ANADIG_PLL_SYS_PLL2_CTRL_PLL_REG_EN_MASK);

    ANADIG_PLL->SYS_PLL2_SS &= ~ANADIG_PLL_SYS_PLL2_SS_ENABLE_MASK;
}

/*!
 * brief Check if Sys PLL2 PFD is enabled
 *
 * param pfd PFD control name
 * return PFD bypass status.
 *         - true: power on.
 *         - false: power off.
 * note Only useful in software control mode.
 */
bool CLOCK_IsSysPll2PfdEnabled(clock_pfd_t pfd)
{
    return ((ANADIG_PLL->SYS_PLL2_PFD & (uint32_t)ANADIG_PLL_SYS_PLL2_PFD_PFD0_DIV1_CLKGATE_MASK
                                            << (8UL * (uint8_t)pfd)) == 0U);
}

#define PFD_FRAC_MIN 12U
#define PFD_FRAC_MAX 35U
void CLOCK_InitPfd(clock_pll_t pll, clock_pfd_t pfd, uint8_t frac)
{
    volatile uint32_t *pfdCtrl = NULL, *pfdUpdate = NULL, stable;
    uint32_t regFracVal;
    bool pfdGated;

    assert(frac <= (uint8_t)PFD_FRAC_MAX);
    assert(frac >= (uint8_t)PFD_FRAC_MIN);

    switch (pll)
    {
        case kCLOCK_PllSys2:
            pfdCtrl   = &ANADIG_PLL->SYS_PLL2_PFD;
            pfdUpdate = &ANADIG_PLL->SYS_PLL2_UPDATE;
            break;
        case kCLOCK_PllSys3:
            pfdCtrl   = &ANADIG_PLL->SYS_PLL3_PFD;
            pfdUpdate = &ANADIG_PLL->SYS_PLL3_UPDATE;
            break;
        default:
            /* Wrong input parameter pll. */
            assert(false);
            break;
    }
    regFracVal = ((*pfdCtrl) & ((uint32_t)ANADIG_PLL_SYS_PLL2_PFD_PFD0_FRAC_MASK << (8UL * (uint32_t)pfd))) >>
                 (8UL * (uint32_t)pfd);
    pfdGated =
        (bool)(((*pfdCtrl) & ((uint32_t)ANADIG_PLL_SYS_PLL2_PFD_PFD0_DIV1_CLKGATE_MASK << (8UL * (uint32_t)pfd))) >>
               (8UL >> (uint32_t)pfd));
    if ((regFracVal == (uint32_t)frac) && (!pfdGated))
    {
        return;
    }

    stable = *pfdCtrl & ((uint32_t)ANADIG_PLL_SYS_PLL2_PFD_PFD0_STABLE_MASK << (8UL * (uint32_t)pfd));
    *pfdCtrl |= ((uint32_t)ANADIG_PLL_SYS_PLL2_PFD_PFD0_DIV1_CLKGATE_MASK << (8UL * (uint32_t)pfd));

    /* all pfds support to be updated on-the-fly after corresponding PLL is stable */
    *pfdCtrl &= ~((uint32_t)ANADIG_PLL_SYS_PLL2_PFD_PFD0_FRAC_MASK << (8UL * (uint32_t)pfd));
    *pfdCtrl |= (ANADIG_PLL_SYS_PLL2_PFD_PFD0_FRAC(frac) << (8UL * (uint32_t)pfd));

    *pfdUpdate ^= ((uint32_t)ANADIG_PLL_SYS_PLL2_UPDATE_PFD0_UPDATE_MASK << (uint32_t)pfd);
    *pfdCtrl &= ~((uint32_t)ANADIG_PLL_SYS_PLL2_PFD_PFD0_DIV1_CLKGATE_MASK << (8UL * (uint32_t)pfd));

    /* Wait for stablizing */
    while (stable == (*pfdCtrl & ((uint32_t)ANADIG_PLL_SYS_PLL2_PFD_PFD0_STABLE_MASK << (8UL * (uint32_t)pfd))))
    {
    }
}

/*!
 * brief De-initialize selected PLL PFD.
 *
 * param pll Which PLL of targeting PFD to be operated.
 * param pfd Which PFD clock to enable.
 */
void CLOCK_DeinitPfd(clock_pll_t pll, clock_pfd_t pfd)
{
    volatile uint32_t *pfdCtrl = NULL;

    switch (pll)
    {
        case kCLOCK_PllSys2:
        {
            pfdCtrl = &ANADIG_PLL->SYS_PLL2_PFD;
            break;
        }
        case kCLOCK_PllSys3:
        {
            pfdCtrl = &ANADIG_PLL->SYS_PLL3_PFD;
            break;
        }
        default:
        {
            /* Wrong input parameter pll. */
            assert(false);
            break;
        }
    }

    /* Clock gate the selected pfd. */
    *pfdCtrl |= ((uint32_t)ANADIG_PLL_SYS_PLL2_PFD_PFD0_DIV1_CLKGATE_MASK << (8UL * (uint32_t)pfd));
}

#ifndef GET_FREQ_FROM_OBS
uint32_t CLOCK_GetPfdFreq(clock_pll_t pll, clock_pfd_t pfd)
{
    uint32_t pllFreq = 0UL, frac = 0UL;
    assert((pll == kCLOCK_PllSys2) || (pll == kCLOCK_PllSys3));

    switch (pll)
    {
        case kCLOCK_PllSys2:
            frac    = (ANADIG_PLL->SYS_PLL2_PFD &
                    ((uint32_t)ANADIG_PLL_SYS_PLL2_PFD_PFD0_FRAC_MASK << (8UL * (uint32_t)pfd)));
            pllFreq = (uint32_t)PLL_SYS2_528_FREQ;
            break;
        case kCLOCK_PllSys3:
            frac    = (ANADIG_PLL->SYS_PLL3_PFD &
                    ((uint32_t)ANADIG_PLL_SYS_PLL3_PFD_PFD0_FRAC_MASK << (8UL * (uint32_t)pfd)));
            pllFreq = (uint32_t)PLL_SYS3_480_FREQ;
            break;
        default:
            /* Wrong input parameter pll. */
            assert(false);
            break;
    }

    frac = frac >> (8UL * (uint32_t)pfd);
    assert(frac >= (uint32_t)PFD_FRAC_MIN);
    assert(frac <= (uint32_t)PFD_FRAC_MAX);

    return ((frac != 0UL) ? ((uint32_t)(((double)pllFreq) * (double)18UL / (double)frac)) : 0UL);
}
#else
uint32_t CLOCK_GetPfdFreq(clock_pll_t pll, clock_pfd_t pfd)
{
    uint32_t freq = 0;
    assert((pll == kCLOCK_PllSys2) || (pll == kCLOCK_PllSys3));

    switch (pll)
    {
        case kCLOCK_PllSys2:
            /* SYS_PLL2_PFD0 OBS index starts from CCM_OBS_PLL_528_PFD0 */
            freq = CLOCK_GetFreqFromObs(0, pfd + CCM_OBS_PLL_528_PFD0);
            break;
        case kCLOCK_PllSys3:
            /* SYS_PLL3_PFD0 OBS index starts from CCM_OBS_PLL_480_PFD0 */
            freq = CLOCK_GetFreqFromObs(0, pfd + CCM_OBS_PLL_480_PFD0);
            break;
        default:
            assert(false);
    }
    return freq;
}
#endif

/* 480PLL */
void CLOCK_InitSysPll3(void)
{
    uint32_t reg;

    if (0UL != (ANADIG_PLL->SYS_PLL3_CTRL & ANADIG_PLL_SYS_PLL3_CTRL_POWERUP_MASK))
    {
        /* no need to reconfigure the PLL if all the configuration is the same */
        if (0UL == (ANADIG_PLL->SYS_PLL3_CTRL & ANADIG_PLL_SYS_PLL3_CTRL_ENABLE_CLK_MASK))
        {
            ANADIG_PLL->SYS_PLL3_CTRL |= ANADIG_PLL_SYS_PLL3_CTRL_ENABLE_CLK_MASK;
        }

        if (0UL != (ANADIG_PLL->SYS_PLL3_CTRL & ANADIG_PLL_SYS_PLL3_CTRL_SYS_PLL3_GATE_MASK))
        {
            ANADIG_PLL->SYS_PLL3_CTRL &= ~ANADIG_PLL_SYS_PLL3_CTRL_SYS_PLL3_GATE_MASK;
        }
        return;
    }

    PMU_StaticEnablePllLdo(ANADIG_PMU);

    /* Gate all PFDs */
    ANADIG_PLL->SYS_PLL3_PFD |=
        ANADIG_PLL_SYS_PLL3_PFD_PFD0_DIV1_CLKGATE(1) | ANADIG_PLL_SYS_PLL3_PFD_PFD1_DIV1_CLKGATE(1) |
        ANADIG_PLL_SYS_PLL3_PFD_PFD2_DIV1_CLKGATE(1) | ANADIG_PLL_SYS_PLL3_PFD_PFD3_DIV1_CLKGATE(1);
    /*
     * 1. configure PLL registres
     * 2. Enable internal LDO
     * 3. Wati LDO stable
     * 4. Power up PLL, assert hold_ring_off (only needed for avpll)
     * 5. At half lock time, de-asserted hold_ring_off (only needed for avpll)
     * 6. Wait PLL lock
     * 7. Enable clock output, release pfd_gate
     */
    reg                       = ANADIG_PLL_SYS_PLL3_CTRL_PLL_REG_EN(1) | ANADIG_PLL_SYS_PLL3_CTRL_SYS_PLL3_GATE(1);
    ANADIG_PLL->SYS_PLL3_CTRL = reg;
    SDK_DelayAtLeastUs(30, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

    reg |= ANADIG_PLL_SYS_PLL3_CTRL_POWERUP(1) | ANADIG_PLL_SYS_PLL3_CTRL_HOLD_RING_OFF_MASK;
    ANADIG_PLL->SYS_PLL3_CTRL = reg;
    SDK_DelayAtLeastUs(30, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

    reg &= ~ANADIG_PLL_SYS_PLL3_CTRL_HOLD_RING_OFF_MASK;
    ANADIG_PLL->SYS_PLL3_CTRL = reg;

    /* Wait for PLL stable */
    while (ANADIG_PLL_SYS_PLL3_CTRL_SYS_PLL3_STABLE_MASK !=
           (ANADIG_PLL->SYS_PLL3_CTRL & ANADIG_PLL_SYS_PLL3_CTRL_SYS_PLL3_STABLE_MASK))
    {
    }

    reg |= ANADIG_PLL_SYS_PLL3_CTRL_ENABLE_CLK(1) | ANADIG_PLL_SYS_PLL3_CTRL_SYS_PLL3_DIV2(1);
    ANADIG_PLL->SYS_PLL3_CTRL = reg;

    reg &= ~ANADIG_PLL_SYS_PLL3_CTRL_SYS_PLL3_GATE_MASK;
    ANADIG_PLL->SYS_PLL3_CTRL = reg;
}

void CLOCK_DeinitSysPll3(void)
{
    ANADIG_PLL->SYS_PLL3_PFD |=
        ANADIG_PLL_SYS_PLL3_PFD_PFD0_DIV1_CLKGATE(1) | ANADIG_PLL_SYS_PLL3_PFD_PFD1_DIV1_CLKGATE(1) |
        ANADIG_PLL_SYS_PLL3_PFD_PFD2_DIV1_CLKGATE(1) | ANADIG_PLL_SYS_PLL3_PFD_PFD3_DIV1_CLKGATE(1);

    ANADIG_PLL->SYS_PLL3_CTRL |= ANADIG_PLL_SYS_PLL3_CTRL_SYS_PLL3_GATE_MASK;
    ANADIG_PLL->SYS_PLL3_CTRL &= ~(ANADIG_PLL_SYS_PLL3_CTRL_ENABLE_CLK_MASK | ANADIG_PLL_SYS_PLL3_CTRL_POWERUP_MASK |
                                   ANADIG_PLL_SYS_PLL3_CTRL_PLL_REG_EN_MASK);
}

/*!
 * brief Check if Sys PLL3 PFD is enabled
 *
 * param pfd PFD control name
 * return PFD bypass status.
 *         - true: power on.
 *         - false: power off.
 * note Only useful in software control mode.
 */
bool CLOCK_IsSysPll3PfdEnabled(clock_pfd_t pfd)
{
    return ((ANADIG_PLL->SYS_PLL3_PFD & (uint32_t)ANADIG_PLL_SYS_PLL3_PFD_PFD0_DIV1_CLKGATE_MASK
                                            << (8UL * (uint8_t)pfd)) == 0U);
}

void CLOCK_SetPllBypass(clock_pll_t pll, bool bypass)
{
    switch (pll)
    {
        case kCLOCK_PllArm:
            ANADIG_PLL->ARM_PLL_CTRL = bypass ? (ANADIG_PLL->ARM_PLL_CTRL | ANADIG_PLL_ARM_PLL_CTRL_BYPASS_MASK) :
                                                (ANADIG_PLL->ARM_PLL_CTRL & ~ANADIG_PLL_ARM_PLL_CTRL_BYPASS_MASK);
            break;
        case kCLOCK_PllSys1:
            ANATOP_PllBypass(ETHERNET_PLL, bypass);
            break;
        case kCLOCK_PllSys2:
            ANADIG_PLL->SYS_PLL2_CTRL = bypass ? (ANADIG_PLL->SYS_PLL2_CTRL | ANADIG_PLL_SYS_PLL2_CTRL_BYPASS_MASK) :
                                                 (ANADIG_PLL->SYS_PLL2_CTRL & ~ANADIG_PLL_SYS_PLL2_CTRL_BYPASS_MASK);
            break;
        case kCLOCK_PllSys3:
            ANADIG_PLL->SYS_PLL3_CTRL = bypass ? (ANADIG_PLL->SYS_PLL3_CTRL | ANADIG_PLL_SYS_PLL3_CTRL_BYPASS_MASK) :
                                                 (ANADIG_PLL->SYS_PLL3_CTRL & ~ANADIG_PLL_SYS_PLL3_CTRL_BYPASS_MASK);
            break;
        case kCLOCK_PllAudio:
            ANATOP_PllBypass(AUDIO_PLL, bypass);
            break;
        default:
            assert(false);
            break;
    }
}

static void ANATOP_PllSetPower(PLL_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL0.SET = PLL_CTRL0_POWERUP_MASK | PLL_CTRL0_HOLD_RING_OFF_MASK;
    }
    else
    {
        base->CTRL0.CLR = PLL_CTRL0_POWERUP_MASK;
    }
}

static void ANATOP_PllBypass(PLL_Type *base, bool bypass)
{
    if (bypass)
    {
        base->CTRL0.SET = PLL_CTRL0_BYPASS_MASK;
    }
    else
    {
        base->CTRL0.CLR = PLL_CTRL0_BYPASS_MASK;
    }
}

static void ANATOP_PllEnablePllReg(PLL_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL0.SET = PLL_CTRL0_PLL_REG_EN_MASK;
    }
    else
    {
        base->CTRL0.CLR = PLL_CTRL0_PLL_REG_EN_MASK;
    }
}

static void ANATOP_PllHoldRingOff(PLL_Type *base, bool off)
{
    if (off)
    {
        base->CTRL0.SET = PLL_CTRL0_HOLD_RING_OFF_MASK;
    }
    else
    {
        base->CTRL0.CLR = PLL_CTRL0_HOLD_RING_OFF_MASK;
    }
}

static void ANATOP_PllToggleHoldRingOff(PLL_Type *base, uint32_t delay_us)
{
    ANATOP_PllHoldRingOff(base, true);
    SDK_DelayAtLeastUs(delay_us, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    ANATOP_PllHoldRingOff(base, false);
}

static void ANATOP_PllEnableSs(PLL_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL0.SET = PLL_CTRL0_ENABLE_MASK;
    }
    else
    {
        base->CTRL0.CLR = PLL_CTRL0_ENABLE_MASK;
    }
}

static void ANATOP_PllEnableClk(PLL_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL0.SET = PLL_CTRL0_ENABLE_MASK;
    }
    else
    {
        base->CTRL0.CLR = PLL_CTRL0_ENABLE_MASK;
    }
}

static void ANATOP_PllConfigure(
    PLL_Type *base, uint8_t div, uint32_t numer, uint8_t post_div, uint32_t denom, const clock_pll_ss_config_t *ss)
{
    if (base != ETHERNET_PLL)
    {
        ANATOP_PllSetPower(base, false);
    }
    if (ss != NULL)
    {
        base->SPREAD_SPECTRUM.RW =
            PLL_SPREAD_SPECTRUM_STEP(ss->step) | PLL_SPREAD_SPECTRUM_STOP(ss->stop) | PLL_SPREAD_SPECTRUM_ENABLE_MASK;
    }
    base->NUMERATOR.RW   = numer;
    base->DENOMINATOR.RW = denom;
    base->CTRL0.CLR      = PLL_CTRL0_DIV_SELECT_MASK;
    base->CTRL0.SET      = PLL_CTRL0_DIV_SELECT(div);
    if (base != ETHERNET_PLL)
    {
        base->CTRL0.CLR = PLL_CTRL0_POST_DIV_SEL_MASK;
        base->CTRL0.SET = PLL_CTRL0_POST_DIV_SEL(post_div);
    }
    ANATOP_PllEnablePllReg(base, true);
    SDK_DelayAtLeastUs(100, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    ANATOP_PllSetPower(base, true);
}

static void ANATOP_AudioPllGate(bool enable)
{
    if (!enable)
    {
        ANADIG_PLL->PLL_AUDIO_CTRL &= ~ANADIG_PLL_PLL_AUDIO_CTRL_PLL_AUDIO_GATE_MASK;
    }
    else
    {
        ANADIG_PLL->PLL_AUDIO_CTRL |= ANADIG_PLL_PLL_AUDIO_CTRL_PLL_AUDIO_GATE_MASK;
    }
}

static void ANATOP_AudioPllSwEnClk(bool enable)
{
    if (!enable)
    {
        ANADIG_PLL->PLL_AUDIO_CTRL &= ~ANADIG_PLL_PLL_AUDIO_CTRL_ENABLE_CLK_MASK;
    }
    else
    {
        ANADIG_PLL->PLL_AUDIO_CTRL |= ANADIG_PLL_PLL_AUDIO_CTRL_ENABLE_CLK_MASK;
    }
}

status_t CLOCK_InitAudioPllWithFreq(uint32_t freqInMhz, bool ssEnable, uint32_t ssRange, uint32_t ssMod)
{
    clock_audio_pll_config_t config = {0};
    config.ssEnable                 = ssEnable;

    if (kStatus_Success == CLOCK_CalcAudioPllFreq(&config, freqInMhz))
    {
        if (config.ssEnable)
        {
            clock_pll_ss_config_t ss = {0};
            CLOCK_CalcPllSpreadSpectrum(config.denominator, ssRange, ssMod, &ss);
            config.ss = &ss;
        }
        CLOCK_InitAudioPll(&config);
        return kStatus_Success;
    }
    return kStatus_Fail;
}

void CLOCK_InitAudioPll(const clock_audio_pll_config_t *config)
{
    uint32_t reg;
    bool pllStable = false;

    PMU_StaticEnablePllLdo(ANADIG_PMU);

    reg = ANADIG_PLL->PLL_AUDIO_CTRL;
    if ((reg & (ANADIG_PLL_PLL_AUDIO_CTRL_PLL_AUDIO_STABLE_MASK | ANADIG_PLL_PLL_AUDIO_CTRL_ENABLE_CLK_MASK)) ==
        (ANADIG_PLL_PLL_AUDIO_CTRL_PLL_AUDIO_STABLE_MASK | ANADIG_PLL_PLL_AUDIO_CTRL_ENABLE_CLK_MASK))
    {
        pllStable = true;
    }
    /* bypass pll */
    ANATOP_PllBypass(AUDIO_PLL, true);

    if (pllStable)
    {
        /* sw enable clock */
        ANATOP_AudioPllSwEnClk(false);
        /* gate clock */
        ANATOP_AudioPllGate(true);
        ANATOP_PllEnableClk(AUDIO_PLL, false);
        ANATOP_PllSetPower(AUDIO_PLL, false);
        ANATOP_PllEnablePllReg(AUDIO_PLL, false);
    }

    ANATOP_AudioPllSwEnClk(true);
    /* configure pll */
    ANATOP_PllConfigure(AUDIO_PLL, config->loopDivider, config->numerator, config->postDivider, config->denominator,
                        (config->ssEnable && (config->ss != NULL)) ? config->ss : NULL);

    /* toggle hold ring off */
    ANATOP_PllToggleHoldRingOff(AUDIO_PLL, 225);

    /* wait pll stable */
    do
    {
        reg = ANADIG_PLL->PLL_AUDIO_CTRL;
    } while ((reg & ANADIG_PLL_PLL_AUDIO_CTRL_PLL_AUDIO_STABLE_MASK) !=
             ANADIG_PLL_PLL_AUDIO_CTRL_PLL_AUDIO_STABLE_MASK); /* wait for PLL locked */

    /* enabled clock */
    ANATOP_PllEnableClk(AUDIO_PLL, true);

    /* ungate clock */
    ANATOP_AudioPllGate(false);

    ANATOP_PllBypass(AUDIO_PLL, false);
}

void CLOCK_DeinitAudioPll(void)
{
    ANATOP_AudioPllSwEnClk(false);
    ANATOP_AudioPllGate(true);
    ANATOP_PllEnableClk(AUDIO_PLL, false);
    ANATOP_PllSetPower(AUDIO_PLL, false);
    ANATOP_PllEnableSs(AUDIO_PLL, false);
    ANATOP_PllEnablePllReg(AUDIO_PLL, false);
}

status_t CLOCK_CalcArmPllFreq(clock_arm_pll_config_t *config, uint32_t freqInMhz)
{
    assert(config != NULL);
    uint32_t refFreq = (XTAL_FREQ / 1000000UL) * 104UL; /* MHz */
    assert((freqInMhz <= refFreq) && (freqInMhz >= 156UL));

    /*
     * ARM_PLL  (156Mhz - 2496Mhz configureable )
     * freqInMhz = osc_freq * loopDivider / (2 * postDivider)
     *   - loopDivider:  104 - 208
     *   - postDivider:  0 - 3
     *   postDivider:
     *     0 - divide by 2; 1 - divide by 4; 2 - divide by 8; 3 - divide by 1
     */

    if (freqInMhz >= refFreq)
    {
        config->postDivider = kCLOCK_PllPostDiv1;
        config->loopDivider = 208;
    }
    else if (freqInMhz >= (refFreq >> 1))
    {
        config->postDivider = kCLOCK_PllPostDiv1;
        config->loopDivider = freqInMhz / 12UL;
    }
    else if (freqInMhz >= (refFreq >> 2))
    {
        config->postDivider = kCLOCK_PllPostDiv2;
        config->loopDivider = freqInMhz / 6UL;
    }
    else if (freqInMhz >= (refFreq >> 3))
    {
        config->postDivider = kCLOCK_PllPostDiv4;
        config->loopDivider = freqInMhz / 3UL;
    }
    else if (freqInMhz > (refFreq >> 4))
    {
        config->postDivider = kCLOCK_PllPostDiv8;
        config->loopDivider = 2UL * freqInMhz / 3UL;
    }
    else
    {
        config->postDivider = kCLOCK_PllPostDiv8;
        config->loopDivider = 104;
    }
    return kStatus_Success;
}

status_t CLOCK_InitArmPllWithFreq(uint32_t freqInMhz)
{
    clock_arm_pll_config_t config;
    if (kStatus_Success == CLOCK_CalcArmPllFreq(&config, freqInMhz))
    {
        CLOCK_InitArmPll(&config);
        return kStatus_Success;
    }
    return kStatus_Fail;
}

status_t CLOCK_CalcAudioPllFreq(clock_audio_pll_config_t *config, uint32_t freqInMhz)
{
    assert(config != NULL);

    uint32_t refFreq = (XTAL_FREQ / 1000000UL) * 54UL; /* MHz */

    assert((freqInMhz <= refFreq) && (freqInMhz > 20UL));

    /*
     * AUDIO_PLL  (20.3125MHZ--- 1300MHZ configureable )
     * freqInMhz = osc_freq * (loopDivider + numerator / (2^28 - 1) ) / 2^postDivider
     *   - loopDivider:  27---54
     *   - postDivider: 0---5
     *   - numerator is a signed number, 30 bit,  numer[29] is the sign bit, such as +1--->0x00000001; -1---> 0x20000001
     * such as: div_sel = 27, numer = 0x026EEEEF, post_div =0, fref = 24.0MHZ, output_fre =24.0*(27 + 40824559/(2^28 -
     * 1))/2^0 = 651.65M such as: div_sel = 33, numer = 0x0F0AAAAA, post_div =0, fref = 19.2MHZ, output_fre =19.2*(33 +
     * 252357290/(2^28 - 1))/2^0= 651.65M
     */

    config->denominator = 0x0FFFFFFF;

    if (freqInMhz >= refFreq)
    {
        config->postDivider = 0;
        config->loopDivider = 54;
        config->numerator   = 0;
    }
    else if (freqInMhz >= (refFreq >> 1))
    {
        config->postDivider = 0;
        config->loopDivider = (uint8_t)(freqInMhz / 24UL);
        config->numerator   = (config->denominator / 24UL) * (freqInMhz % 24UL);
    }
    else if (freqInMhz >= (refFreq >> 2))
    {
        config->postDivider = 1;
        config->loopDivider = (uint8_t)(freqInMhz / 12UL);
        config->numerator   = (config->denominator / 12UL) * (freqInMhz % 12UL);
    }
    else if (freqInMhz >= (refFreq >> 3))
    {
        config->postDivider = 2;
        config->loopDivider = (uint8_t)(freqInMhz / 6UL);
        config->numerator   = (config->denominator / 6UL) * (freqInMhz % 6UL);
    }
    else if (freqInMhz >= (refFreq >> 4))
    {
        config->postDivider = 3;
        config->loopDivider = (uint8_t)(freqInMhz / 3UL);
        config->numerator   = (config->denominator / 3UL) * (freqInMhz % 3UL);
    }
    else if (freqInMhz >= (refFreq >> 5))
    {
        config->postDivider = 4;
        config->loopDivider = (uint8_t)(freqInMhz * 2UL / 3UL);
        config->numerator   = (config->denominator * 2UL / 3UL) * (freqInMhz * 2UL % 3UL);
    }
    else if (freqInMhz > (refFreq >> 6))
    {
        config->postDivider = 5;
        config->loopDivider = (uint8_t)(freqInMhz * 4UL / 3UL);
        config->numerator   = (config->denominator * 4UL / 3UL) * (freqInMhz * 4UL % 3UL);
    }
    else
    {
        return kStatus_Fail;
    }
    return kStatus_Success;
}

static void ANATOP_SysPll1Gate(bool enable)
{
    if (!enable)
    {
        ANADIG_PLL->SYS_PLL1_CTRL &= ~ANADIG_PLL_SYS_PLL1_CTRL_SYS_PLL1_GATE_MASK;
    }
    else
    {
        ANADIG_PLL->SYS_PLL1_CTRL |= ANADIG_PLL_SYS_PLL1_CTRL_SYS_PLL1_GATE_MASK;
    }
}

static void ANATOP_SysPll1Div2En(bool enable)
{
    if (!enable)
    {
        ANADIG_PLL->SYS_PLL1_CTRL &= ~ANADIG_PLL_SYS_PLL1_CTRL_SYS_PLL1_DIV2_MASK;
    }
    else
    {
        ANADIG_PLL->SYS_PLL1_CTRL |= ANADIG_PLL_SYS_PLL1_CTRL_SYS_PLL1_DIV2_MASK;
    }
}

static void ANATOP_SysPll1Div5En(bool enable)
{
    if (!enable)
    {
        ANADIG_PLL->SYS_PLL1_CTRL &= ~ANADIG_PLL_SYS_PLL1_CTRL_SYS_PLL1_DIV5_MASK;
    }
    else
    {
        ANADIG_PLL->SYS_PLL1_CTRL |= ANADIG_PLL_SYS_PLL1_CTRL_SYS_PLL1_DIV5_MASK;
    }
}

static void ANATOP_SysPll1SwEnClk(bool enable)
{
    if (!enable)
    {
        ANADIG_PLL->SYS_PLL1_CTRL &= ~ANADIG_PLL_SYS_PLL1_CTRL_ENABLE_CLK_MASK;
    }
    else
    {
        ANADIG_PLL->SYS_PLL1_CTRL |= ANADIG_PLL_SYS_PLL1_CTRL_ENABLE_CLK_MASK;
    }
}

static void ANATOP_SysPll1WaitStable(void)
{
    uint32_t reg;
    do
    {
        reg = ANADIG_PLL->SYS_PLL1_CTRL;
    } while ((reg & ANADIG_PLL_SYS_PLL1_CTRL_SYS_PLL1_STABLE_MASK) !=
             ANADIG_PLL_SYS_PLL1_CTRL_SYS_PLL1_STABLE_MASK); /* wait for PLL locked */
}

/* 1GPLL */
void CLOCK_InitSysPll1(const clock_sys_pll1_config_t *config)
{
    uint8_t div;
    uint32_t numerator, denominator;

    PMU_StaticEnablePllLdo(ANADIG_PMU);
    /* bypass pll */
    ANATOP_PllBypass(ETHERNET_PLL, true);

    /* sw enable clock */
    ANATOP_SysPll1SwEnClk(true);

    denominator = 0x0FFFFFFF;
    div         = 41U;
    numerator   = 178956970UL;

    /* configure pll */
    ANATOP_PllConfigure(ETHERNET_PLL, div, numerator, 0U, denominator,
                        (config->ssEnable && (config->ss != NULL)) ? config->ss : NULL);

    /* toggle hold ring off */
    ANATOP_PllToggleHoldRingOff(ETHERNET_PLL, 225);

    /* wait pll stable */
    ANATOP_SysPll1WaitStable();

    /* enabled clock */
    ANATOP_PllEnableClk(ETHERNET_PLL, true);

    /* ungate clock */
    ANATOP_SysPll1Gate(false);

    ANATOP_SysPll1Div2En(config->pllDiv2En);
    ANATOP_SysPll1Div5En(config->pllDiv5En);

    /* bypass pll */
    ANATOP_PllBypass(ETHERNET_PLL, false);
}

void CLOCK_DeinitSysPll1(void)
{
    ANATOP_SysPll1SwEnClk(false);
    ANATOP_SysPll1Div2En(false);
    ANATOP_SysPll1Div5En(false);
    ANATOP_SysPll1Gate(true);
    ANATOP_PllEnableClk(ETHERNET_PLL, false);
    ANATOP_PllSetPower(ETHERNET_PLL, false);
    ANATOP_PllEnableSs(ETHERNET_PLL, false);
    ANATOP_PllEnablePllReg(ETHERNET_PLL, false);
}

void CLOCK_OSC_EnableOsc24M(void)
{
    if (0UL == (ANADIG_OSC->OSC_24M_CTRL & ANADIG_OSC_OSC_24M_CTRL_OSC_EN_MASK))
    {
        ANADIG_OSC->OSC_24M_CTRL |= ANADIG_OSC_OSC_24M_CTRL_OSC_EN_MASK;
        while (ANADIG_OSC_OSC_24M_CTRL_OSC_24M_STABLE_MASK !=
               (ANADIG_OSC->OSC_24M_CTRL & ANADIG_OSC_OSC_24M_CTRL_OSC_24M_STABLE_MASK))
        {
        }
    }
}

/*!
 * brief Set the work mode of 24MHz crystal oscillator, the available modes are high gian mode, low power mode, and
 * bypass mode.
 *
 * param workMode The work mode of 24MHz crystal oscillator, please refer to @ref clock_24MOsc_mode_t for details.
 */
void CLOCK_OSC_SetOsc24MWorkMode(clock_24MOsc_mode_t workMode)
{
    uint32_t tmp32;

    tmp32 = ANADIG_OSC->OSC_24M_CTRL;
    tmp32 &= ~(ANADIG_OSC_OSC_24M_CTRL_LP_EN_MASK | ANADIG_OSC_OSC_24M_CTRL_BYPASS_EN_MASK);
    tmp32 |= (((uint32_t)workMode << ANADIG_OSC_OSC_24M_CTRL_BYPASS_EN_SHIFT) &
              (ANADIG_OSC_OSC_24M_CTRL_LP_EN_MASK | ANADIG_OSC_OSC_24M_CTRL_BYPASS_EN_MASK));
    ANADIG_OSC->OSC_24M_CTRL = tmp32;
}

/*!
 * brief Set the divide value for ref_clk to generate slow clock.
 *
 * note slow_clk = ref_clk / (divValue + 1), and the recommand divide value is 24.
 *
 * param divValue The divide value to be set, the available range is 0~63.
 */
void CLOCK_OSC_SetOscRc400MRefClkDiv(uint8_t divValue)
{
    OSC_RC_400M->CTRL0.RW =
        (OSC_RC_400M->CTRL0.RW & ~OSC_RC_400M_CTRL0_REF_CLK_DIV_MASK) | OSC_RC_400M_CTRL0_REF_CLK_DIV(divValue);
}

/*!
 * brief Set the target count for the fast clock.
 *
 * param targetCount The desired target for the fast clock, should be the number of clock cycles of the fast_clk per
 * divided ref_clk.
 */
void CLOCK_OSC_SetOscRc400MFastClkCount(uint16_t targetCount)
{
    OSC_RC_400M->CTRL1.RW =
        (OSC_RC_400M->CTRL1.RW & ~OSC_RC_400M_CTRL1_TARGET_COUNT_MASK) | OSC_RC_400M_CTRL1_TARGET_COUNT(targetCount);
}

/*!
 * brief Set the negative and positive hysteresis value for the tuned clock.
 *
 * note The hysteresis value should be set after the clock is tuned.
 *
 * param negHysteresis The negative hysteresis value for the turned clock, this value in number of clock cycles of the
 * fast clock
 * param posHysteresis The positive hysteresis value for the turned clock, this value in number of clock cycles of the
 * fast clock
 */
void CLOCK_OSC_SetOscRc400MHysteresisValue(uint8_t negHysteresis, uint8_t posHysteresis)
{
    OSC_RC_400M->CTRL1.RW =
        (OSC_RC_400M->CTRL1.RW & ~(OSC_RC_400M_CTRL1_HYST_PLUS_MASK | OSC_RC_400M_CTRL1_HYST_MINUS_MASK)) |
        OSC_RC_400M_CTRL1_HYST_PLUS(posHysteresis) | OSC_RC_400M_CTRL1_HYST_MINUS(negHysteresis);
}

/*!
 * brief Bypass/un-bypass the tune logic
 *
 * param enableBypass Used to control whether to bypass the turn logic.
 *        - \b true Bypass the tune logic and use the programmed oscillator frequency to run the oscillator.
 *                  Function CLOCK_OSC_SetOscRc400MTuneValue() can be used to set oscillator frequency.
 *        - \b false Use the output of tune logic to run the oscillator.
 */
void CLOCK_OSC_BypassOscRc400MTuneLogic(bool enableBypass)
{
    if (enableBypass)
    {
        OSC_RC_400M->CTRL2.SET = OSC_RC_400M_CTRL2_TUNE_BYP_MASK;
    }
    else
    {
        OSC_RC_400M->CTRL2.CLR = OSC_RC_400M_CTRL2_TUNE_BYP_MASK;
    }
}

/*!
 * brief Start/Stop the tune logic.
 *
 * param enable Used to start or stop the tune logic.
 *          - \b true Start tuning
 *          - \b false Stop tuning and reset the tuning logic.
 */
void CLOCK_OSC_EnableOscRc400MTuneLogic(bool enable)
{
    if (enable)
    {
        OSC_RC_400M->CTRL2.SET = OSC_RC_400M_CTRL2_TUNE_START_MASK;
    }
    else
    {
        OSC_RC_400M->CTRL2.CLR = OSC_RC_400M_CTRL2_TUNE_START_MASK;
    }
}

/*!
 * brief Freeze/Unfreeze the tuning value.
 *
 * param enableFreeze Used to control whether to freeze the tune value.
 *          - \b true Freeze the tune at the current tuned value and the oscillator runs at tje frozen tune value.
 *          - \b false Unfreezes and continues the tune operation.
 */
void CLOCK_OSC_FreezeOscRc400MTuneValue(bool enableFreeze)
{
    if (enableFreeze)
    {
        OSC_RC_400M->CTRL2.SET = OSC_RC_400M_CTRL2_TUNE_EN_MASK;
    }
    else
    {
        OSC_RC_400M->CTRL2.CLR = OSC_RC_400M_CTRL2_TUNE_EN_MASK;
    }
}

/*!
 * @brief Set the 400MHz RC oscillator tune value when the tune logic is disabled.
 *
 * @param tuneValue The tune value to determine the frequency of Oscillator.
 */
void CLOCK_OSC_SetOscRc400MTuneValue(uint8_t tuneValue)
{
    OSC_RC_400M->CTRL2.RW =
        (OSC_RC_400M->CTRL2.RW & ~OSC_RC_400M_CTRL2_OSC_TUNE_VAL_MASK) | OSC_RC_400M_CTRL2_OSC_TUNE_VAL(tuneValue);
}

/*!
 * brief Set the behavior of the 1MHz output clock, such as disable the 1MHz clock output,
 * enable the free-running 1MHz clock output, enable the locked 1MHz clock output.
 *
 * note The 1MHz clock is divided from 400M RC Oscillator.
 *
 * param behavior The behavior of 1MHz output clock, please refer to clock_1MHzOut_behavior_t for details.
 */
void CLOCK_OSC_Set1MHzOutputBehavior(clock_1MHzOut_behavior_t behavior)
{
    uint32_t tmp32;

    tmp32 = OSC_RC_400M->CTRL3.RW;
    tmp32 &= ~(OSC_RC_400M_CTRL3_EN_1M_CLK_MASK | OSC_RC_400M_CTRL3_MUX_1M_CLK_MASK);

    if (behavior == kCLOCK_1MHzOutDisable)
    {
        tmp32 |= OSC_RC_400M_CTRL3_EN_1M_CLK_MASK;
    }
    else
    {
        if (behavior == kCLOCK_1MHzOutEnableLocked1Mhz)
        {
            tmp32 |= OSC_RC_400M_CTRL3_MUX_1M_CLK_MASK;
        }
    }
    OSC_RC_400M->CTRL3.RW = tmp32;
}

/*!
 * brief Set the count for the locked 1MHz clock out.
 *
 * param count Used to set the desired target for the locked 1MHz clock out, the value in number of clock cycles of the
 * osc_out_400M per divided ref_clk.
 */
void CLOCK_OSC_SetLocked1MHzCount(uint16_t count)
{
    uint32_t tmp32;
    uint16_t targetCount;
    uint16_t hystMinus;
    uint16_t diffCount;

    tmp32       = OSC_RC_400M->CTRL1.RW;
    targetCount = (uint16_t)((tmp32 & OSC_RC_400M_CTRL1_TARGET_COUNT_MASK) >> OSC_RC_400M_CTRL1_TARGET_COUNT_SHIFT);
    hystMinus   = (uint16_t)((tmp32 & OSC_RC_400M_CTRL1_HYST_MINUS_MASK) >> OSC_RC_400M_CTRL1_HYST_MINUS_SHIFT);
    diffCount   = targetCount - hystMinus - count;

    /* The count for the locked 1MHz clock should be 4 to 8 counts less than CTRL[TARGET_COUNT] - CTRL1[HYST_MINUS]. */
    if ((diffCount >= 4U) && (diffCount <= 8U))
    {
        tmp32                 = (tmp32 & ~OSC_RC_400M_CTRL3_COUNT_1M_CLK_MASK) | OSC_RC_400M_CTRL3_COUNT_1M_CLK(count);
        OSC_RC_400M->CTRL3.RW = tmp32;
    }
}

/*!
 * brief Check the error flag for locked 1MHz clock out.
 *
 * return The error flag for locked 1MHz clock out.
 *      - \b true The count value has been reached within one diviced ref clock period
 *      - \b false No effect.
 */
bool CLOCK_OSC_CheckLocked1MHzErrorFlag(void)
{
    return ((OSC_RC_400M->STAT0.RW & OSC_RC_400M_STAT0_CLK1M_ERR_MASK) == OSC_RC_400M_STAT0_CLK1M_ERR_MASK);
}

/*!
 * brief Clear the error flag for locked 1MHz clock out.
 */
void CLOCK_OSC_ClearLocked1MHzErrorFlag(void)
{
    OSC_RC_400M->CTRL3.SET = OSC_RC_400M_CTRL3_CLR_ERR_MASK;
}

/*!
 * brief Get current count for the fast clock during the tune process.
 *
 * return The current count for the fast clock.
 */
uint16_t CLOCK_OSC_GetCurrentOscRc400MFastClockCount(void)
{
    return (uint16_t)((OSC_RC_400M->STAT1.RW & OSC_RC_400M_STAT1_CURR_COUNT_VAL_MASK) >>
                      OSC_RC_400M_STAT1_CURR_COUNT_VAL_SHIFT);
}

/*!
 * brief Get current tune value used by oscillator during tune process.
 *
 * return The current tune value.
 */
uint8_t CLOCK_OSC_GetCurrentOscRc400MTuneValue(void)
{
    return (uint8_t)((OSC_RC_400M->STAT2.RW & OSC_RC_400M_STAT2_CURR_OSC_TUNE_VAL_MASK) >>
                     OSC_RC_400M_STAT2_CURR_OSC_TUNE_VAL_SHIFT);
}

#ifndef GET_FREQ_FROM_OBS
static uint32_t CLOCK_GetAudioPllFreq(void)
{
    uint32_t freq = 0;
    uint32_t div;
    uint32_t post_div;
    double tmpDouble;
    double denom;
    double numer;

    div      = (AUDIO_PLL->CTRL0.RW & PLL_CTRL0_DIV_SELECT_MASK) >> PLL_CTRL0_DIV_SELECT_SHIFT;
    post_div = (AUDIO_PLL->CTRL0.RW & PLL_CTRL0_POST_DIV_SEL_MASK) >> PLL_CTRL0_POST_DIV_SEL_SHIFT;
    denom    = (double)(AUDIO_PLL->DENOMINATOR.RW);
    numer    = (double)(AUDIO_PLL->NUMERATOR.RW);

    tmpDouble = ((double)XTAL_FREQ * ((double)div + (numer / denom)) / (double)(uint32_t)(1UL << post_div));
    freq      = (uint32_t)tmpDouble;

    return freq;
}
#endif

uint32_t CLOCK_GetPllFreq(clock_pll_t pll)
{
    uint32_t freq = 0;
#ifndef GET_FREQ_FROM_OBS
    uint32_t divSelect, postDiv;
#endif

    switch (pll)
    {
        case kCLOCK_PllArm:
#ifndef GET_FREQ_FROM_OBS
            divSelect = (ANADIG_PLL->ARM_PLL_CTRL & ANADIG_PLL_ARM_PLL_CTRL_DIV_SELECT_MASK) >>
                        ANADIG_PLL_ARM_PLL_CTRL_DIV_SELECT_SHIFT;
            postDiv = (ANADIG_PLL->ARM_PLL_CTRL & ANADIG_PLL_ARM_PLL_CTRL_POST_DIV_SEL_MASK) >>
                      ANADIG_PLL_ARM_PLL_CTRL_POST_DIV_SEL_SHIFT;
            postDiv = (1UL << (postDiv + 1UL));
            freq    = XTAL_FREQ / (2UL * postDiv);
            freq *= divSelect;
#else
            freq = CLOCK_GetFreqFromObs(0, CCM_OBS_PLL_ARM_OUT);
#endif
            break;
        case kCLOCK_PllSys1:
#ifndef GET_FREQ_FROM_OBS
            freq = PLL_SYS1_1G_FREQ;
#else
            freq = CLOCK_GetFreqFromObs(0, CCM_OBS_PLL_1G_OUT);
#endif
            break;
        case kCLOCK_PllSys2:
#ifndef GET_FREQ_FROM_OBS
            freq = PLL_SYS2_528_FREQ;
#else
            freq = CLOCK_GetFreqFromObs(0, CCM_OBS_PLL_528_OUT);
#endif
            break;
        case kCLOCK_PllSys3:
#ifndef GET_FREQ_FROM_OBS
            freq = PLL_SYS3_480_FREQ;
#else
            freq = CLOCK_GetFreqFromObs(0, CCM_OBS_PLL_480_OUT);
#endif
            break;
        case kCLOCK_PllAudio:
#ifndef GET_FREQ_FROM_OBS
            freq = CLOCK_GetAudioPllFreq();
#else
            freq = CLOCK_GetFreqFromObs(0, CCM_OBS_PLL_AUDIO_OUT);
#endif
            break;
        default:
            /* Wrong input parameter pll. */
            assert(false);
            break;
    }
    return freq;
}

uint32_t CLOCK_GetFreq(clock_name_t name)
{
    uint32_t freq = 0;
    switch (name)
    {
        case kCLOCK_OscRc24M:
#ifndef GET_FREQ_FROM_OBS
            freq = 24000000U;
#else
            freq = CLOCK_GetFreqFromObs(0, CCM_OBS_OSC_RC_24M);
#endif
            break;
        case kCLOCK_OscRc400M:
#ifndef GET_FREQ_FROM_OBS
            freq = 400000000U;
#else
            freq = CLOCK_GetFreqFromObs(0, CCM_OBS_OSC_RC_400M);
#endif
            break;
        case kCLOCK_Osc24MOut:
        case kCLOCK_Osc24M:
#ifndef GET_FREQ_FROM_OBS
            freq = 24000000U;
#else
            freq = CLOCK_GetFreqFromObs(0, CCM_OBS_OSC_24M_OUT);
#endif
            break;
        case kCLOCK_ArmPllOut:
        case kCLOCK_ArmPll:
            freq = CLOCK_GetPllFreq(kCLOCK_PllArm);
            break;
        case kCLOCK_SysPll2:
        case kCLOCK_SysPll2Out:
            freq = CLOCK_GetPllFreq(kCLOCK_PllSys2);
            break;
        case kCLOCK_SysPll2Pfd0:
            freq = CLOCK_GetPfdFreq(kCLOCK_PllSys2, kCLOCK_Pfd0);
            break;
        case kCLOCK_SysPll2Pfd1:
            freq = CLOCK_GetPfdFreq(kCLOCK_PllSys2, kCLOCK_Pfd1);
            break;
        case kCLOCK_SysPll2Pfd2:
            freq = CLOCK_GetPfdFreq(kCLOCK_PllSys2, kCLOCK_Pfd2);
            break;
        case kCLOCK_SysPll2Pfd3:
            freq = CLOCK_GetPfdFreq(kCLOCK_PllSys2, kCLOCK_Pfd3);
            break;
        case kCLOCK_SysPll3Out:
        case kCLOCK_SysPll3:
            freq = CLOCK_GetPllFreq(kCLOCK_PllSys3);
            break;
        case kCLOCK_SysPll3Div2:
            freq = (CLOCK_GetPllFreq(kCLOCK_PllSys3) / 2UL);
            break;
        case kCLOCK_SysPll3Pfd0:
            freq = CLOCK_GetPfdFreq(kCLOCK_PllSys3, kCLOCK_Pfd0);
            break;
        case kCLOCK_SysPll3Pfd1:
            freq = CLOCK_GetPfdFreq(kCLOCK_PllSys3, kCLOCK_Pfd1);
            break;
        case kCLOCK_SysPll3Pfd2:
            freq = CLOCK_GetPfdFreq(kCLOCK_PllSys3, kCLOCK_Pfd2);
            break;
        case kCLOCK_SysPll3Pfd3:
            freq = CLOCK_GetPfdFreq(kCLOCK_PllSys3, kCLOCK_Pfd3);
            break;
        case kCLOCK_SysPll1:
        case kCLOCK_SysPll1Out:
            freq = CLOCK_GetPllFreq(kCLOCK_PllSys1);
            break;
        case kCLOCK_SysPll1Div2:
            freq = CLOCK_GetPllFreq(kCLOCK_PllSys1) / 2UL;
            break;
        case kCLOCK_SysPll1Div5:
            freq = CLOCK_GetPllFreq(kCLOCK_PllSys1) / 5UL;
            break;
        case kCLOCK_AudioPll:
        case kCLOCK_AudioPllOut:
            freq = CLOCK_GetPllFreq(kCLOCK_PllAudio);
            break;
        case kCLOCK_CpuClk:
        case kCLOCK_CoreSysClk:
            freq = CLOCK_GetCpuClkFreq();
            break;
        default:
            /* Wrong input parameter name. */
            assert(false);
            break;
    }
    assert(freq != 0UL);
    return freq;
}

/*!
 * @brief Get the CCM CPU/core/system frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetM7Freq(void)
{
    uint32_t freq = 0, mux;
    mux           = CLOCK_GetRootClockMux(kCLOCK_Root_M7);

    switch (s_clockSourceName[kCLOCK_Root_M7][mux])
    {
        case kCLOCK_OscRc24M:
#ifndef GET_FREQ_FROM_OBS
            freq = 24000000U;
#else
            freq = CLOCK_GetFreqFromObs(0, CCM_OBS_OSC_RC_24M);
#endif
            break;
        case kCLOCK_OscRc400M:
#ifndef GET_FREQ_FROM_OBS
            freq = 400000000U;
#else
            freq = CLOCK_GetFreqFromObs(0, CCM_OBS_OSC_RC_400M);
#endif
            break;
        case kCLOCK_ArmPllOut:
            freq = CLOCK_GetPllFreq(kCLOCK_PllArm);
            break;
        case kCLOCK_SysPll3Out:
            freq = CLOCK_GetPllFreq(kCLOCK_PllSys3);
            break;
        default:
            /* Wrong input parameter name. */
            assert(false);
            break;
    }
    freq = freq / (CLOCK_GetRootClockDiv(kCLOCK_Root_M7));
    assert(freq);
    return freq;
}

/*!
 * @brief Get the CCM CPU/core/system frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetM33Freq(void)
{
    uint32_t freq = 0, mux;
    mux           = CLOCK_GetRootClockMux(kCLOCK_Root_M33);

    switch (s_clockSourceName[kCLOCK_Root_M33][mux])
    {
        case kCLOCK_OscRc24M:
#ifndef GET_FREQ_FROM_OBS
            freq = 24000000U;
#else
            freq = CLOCK_GetFreqFromObs(0, CCM_OBS_OSC_RC_24M);
#endif
            break;
        case kCLOCK_OscRc400M:
#ifndef GET_FREQ_FROM_OBS
            freq = 400000000U;
#else
            freq = CLOCK_GetFreqFromObs(0, CCM_OBS_OSC_RC_400M);
#endif
            break;
        case kCLOCK_ArmPllOut:
            freq = CLOCK_GetPllFreq(kCLOCK_PllArm);
            break;
        case kCLOCK_SysPll3Out:
            freq = CLOCK_GetPllFreq(kCLOCK_PllSys3);
            break;
        default:
            /* Wrong input parameter name. */
            assert(false);
            break;
    }
    freq = freq / (CLOCK_GetRootClockDiv(kCLOCK_Root_M33));
    assert(freq);
    return freq;
}

void CLOCK_SetClockSourceControlMode(clock_name_t name, clock_control_mode_t controlMode)
{
    switch (name)
    {
        case kCLOCK_OscRc24M:
            ANADIG_OSC->OSC_RC24M_CTRL =
                (ANADIG_OSC->OSC_RC24M_CTRL & ~(ANADIG_OSC_OSC_RC24M_CTRL_RC_24M_CONTROL_MODE_MASK)) |
                ANADIG_OSC_OSC_RC24M_CTRL_RC_24M_CONTROL_MODE(controlMode);
            break;
        case kCLOCK_OscRc400M:
            ANADIG_OSC->OSC_400M_CTRL1 =
                (ANADIG_OSC->OSC_400M_CTRL1 & (~ANADIG_OSC_OSC_400M_CTRL1_RC_400M_CONTROL_MODE_MASK)) |
                ANADIG_OSC_OSC_400M_CTRL1_RC_400M_CONTROL_MODE(controlMode);
            break;
        case kCLOCK_Osc24MOut:
        case kCLOCK_Osc24M:
            ANADIG_OSC->OSC_24M_CTRL =
                (ANADIG_OSC->OSC_24M_CTRL & ~(ANADIG_OSC_OSC_24M_CTRL_OSC_24M_CONTROL_MODE_MASK)) |
                ANADIG_OSC_OSC_24M_CTRL_OSC_24M_CONTROL_MODE(controlMode);
            break;
        case kCLOCK_ArmPllOut:
        case kCLOCK_ArmPll:
            ANADIG_PLL->ARM_PLL_CTRL =
                (ANADIG_PLL->ARM_PLL_CTRL & ~(ANADIG_PLL_ARM_PLL_CTRL_ARM_PLL_CONTROL_MODE_MASK)) |
                ANADIG_PLL_ARM_PLL_CTRL_ARM_PLL_CONTROL_MODE(controlMode);
            break;
        case kCLOCK_SysPll2:
        case kCLOCK_SysPll2Out:
            ANADIG_PLL->SYS_PLL2_CTRL =
                (ANADIG_PLL->SYS_PLL2_CTRL & ~(ANADIG_PLL_SYS_PLL2_CTRL_SYS_PLL2_CONTROL_MODE_MASK)) |
                ANADIG_PLL_SYS_PLL2_CTRL_SYS_PLL2_CONTROL_MODE(controlMode);
            break;
        case kCLOCK_SysPll2Pfd0:
            ANADIG_PLL->SYS_PLL2_UPDATE =
                (ANADIG_PLL->SYS_PLL2_UPDATE & ~(ANADIG_PLL_SYS_PLL2_UPDATE_PFD0_CONTROL_MODE_MASK)) |
                ANADIG_PLL_SYS_PLL2_UPDATE_PFD0_CONTROL_MODE(controlMode);
            break;
        case kCLOCK_SysPll2Pfd1:
            ANADIG_PLL->SYS_PLL2_UPDATE =
                (ANADIG_PLL->SYS_PLL2_UPDATE & ~(ANADIG_PLL_SYS_PLL2_UPDATE_PFD1_CONTROL_MODE_MASK)) |
                ANADIG_PLL_SYS_PLL2_UPDATE_PFD1_CONTROL_MODE(controlMode);
            break;
        case kCLOCK_SysPll2Pfd2:
            ANADIG_PLL->SYS_PLL2_UPDATE =
                (ANADIG_PLL->SYS_PLL2_UPDATE & ~(ANADIG_PLL_SYS_PLL2_UPDATE_PFD2_CONTROL_MODE_MASK)) |
                ANADIG_PLL_SYS_PLL2_UPDATE_PFD2_CONTROL_MODE(controlMode);
            break;
        case kCLOCK_SysPll2Pfd3:
            ANADIG_PLL->SYS_PLL2_UPDATE =
                (ANADIG_PLL->SYS_PLL2_UPDATE & ~(ANADIG_PLL_SYS_PLL2_UPDATE_PFD3_CONTROL_MODE_MASK)) |
                ANADIG_PLL_SYS_PLL2_UPDATE_PFD3_CONTROL_MODE(controlMode);
            break;
        case kCLOCK_SysPll3Out:
        case kCLOCK_SysPll3:
            ANADIG_PLL->SYS_PLL3_CTRL =
                (ANADIG_PLL->SYS_PLL3_CTRL & ~(ANADIG_PLL_SYS_PLL3_CTRL_SYS_PLL3_CONTROL_MODE_MASK)) |
                ANADIG_PLL_SYS_PLL3_CTRL_SYS_PLL3_CONTROL_MODE(controlMode);
            break;
        case kCLOCK_SysPll3Div2:
            ANADIG_PLL->SYS_PLL3_CTRL =
                (ANADIG_PLL->SYS_PLL3_CTRL & ~(ANADIG_PLL_SYS_PLL3_CTRL_SYS_PLL3_DIV2_CONTROL_MODE_MASK)) |
                ANADIG_PLL_SYS_PLL3_CTRL_SYS_PLL3_DIV2_CONTROL_MODE(controlMode);
            break;
        case kCLOCK_SysPll3Pfd0:
            ANADIG_PLL->SYS_PLL3_UPDATE =
                (ANADIG_PLL->SYS_PLL3_UPDATE & ~(ANADIG_PLL_SYS_PLL3_UPDATE_PFD0_CONTROL_MODE_MASK)) |
                ANADIG_PLL_SYS_PLL3_UPDATE_PFD0_CONTROL_MODE(controlMode);
            break;
        case kCLOCK_SysPll3Pfd1:
            ANADIG_PLL->SYS_PLL3_UPDATE =
                (ANADIG_PLL->SYS_PLL3_UPDATE & ~(ANADIG_PLL_SYS_PLL3_UPDATE_PFD1_CONTROL_MODE_MASK)) |
                ANADIG_PLL_SYS_PLL3_UPDATE_PFD1_CONTROL_MODE(controlMode);
            break;
        case kCLOCK_SysPll3Pfd2:
            ANADIG_PLL->SYS_PLL3_UPDATE =
                (ANADIG_PLL->SYS_PLL3_UPDATE & ~(ANADIG_PLL_SYS_PLL3_UPDATE_PFD2_CONTROL_MODE_MASK)) |
                ANADIG_PLL_SYS_PLL3_UPDATE_PFD2_CONTROL_MODE(controlMode);
            break;
        case kCLOCK_SysPll3Pfd3:
            ANADIG_PLL->SYS_PLL3_UPDATE =
                (ANADIG_PLL->SYS_PLL3_UPDATE & ~(ANADIG_PLL_SYS_PLL3_UPDATE_PFD3_CONTROL_MODE_MASK)) |
                ANADIG_PLL_SYS_PLL3_UPDATE_PFD3_CONTROL_MODE(controlMode);
            break;
        case kCLOCK_SysPll1:
        case kCLOCK_SysPll1Out:
            ANADIG_PLL->SYS_PLL1_CTRL =
                (ANADIG_PLL->SYS_PLL1_CTRL & ~(ANADIG_PLL_SYS_PLL1_CTRL_SYS_PLL1_CONTROL_MODE_MASK)) |
                ANADIG_PLL_SYS_PLL1_CTRL_SYS_PLL1_CONTROL_MODE(controlMode);
            break;
        case kCLOCK_SysPll1Div2:
            ANADIG_PLL->SYS_PLL1_CTRL =
                (ANADIG_PLL->SYS_PLL1_CTRL & ~(ANADIG_PLL_SYS_PLL1_CTRL_SYS_PLL1_DIV2_CONTROL_MODE_MASK)) |
                ANADIG_PLL_SYS_PLL1_CTRL_SYS_PLL1_DIV2_CONTROL_MODE(controlMode);
            break;
        case kCLOCK_SysPll1Div5:
            ANADIG_PLL->SYS_PLL1_CTRL =
                (ANADIG_PLL->SYS_PLL1_CTRL & ~(ANADIG_PLL_SYS_PLL1_CTRL_SYS_PLL1_DIV5_CONTROL_MODE_MASK)) |
                ANADIG_PLL_SYS_PLL1_CTRL_SYS_PLL1_DIV5_CONTROL_MODE(controlMode);
            break;
        case kCLOCK_AudioPll:
        case kCLOCK_AudioPllOut:
            ANADIG_PLL->PLL_AUDIO_CTRL =
                (ANADIG_PLL->PLL_AUDIO_CTRL & ~(ANADIG_PLL_PLL_AUDIO_CTRL_PLL_AUDIO_CONTROL_MODE_MASK)) |
                ANADIG_PLL_PLL_AUDIO_CTRL_PLL_AUDIO_CONTROL_MODE(controlMode);
            break;
        default:
            /* Wrong input parameter name. */
            assert(false);
            break;
    }
}

void CLOCK_OSC_TrimOscRc400M(bool enable, bool bypass, uint16_t trim)
{
    if (enable)
    {
        OSC_RC_400M->CTRL2.CLR = OSC_RC_400M_CTRL2_OSC_TUNE_VAL_MASK | OSC_RC_400M_CTRL2_TUNE_BYP_MASK;
        OSC_RC_400M->CTRL2.SET = OSC_RC_400M_CTRL2_OSC_TUNE_VAL(trim) | OSC_RC_400M_CTRL2_TUNE_BYP(bypass);
    }
}

void CLOCK_OSC_EnableOscRc400M(void)
{
    ANADIG_OSC->OSC_400M_CTRL1 &= ~ANADIG_OSC_OSC_400M_CTRL1_PWD_MASK;
}

/* Note: If this function gets invoked in different core's application, user should use different obsIndex in case
 * register access conflicts. */
uint32_t CLOCK_GetFreqFromObs(uint8_t obsIndex, uint32_t obsSigIndex)
{
    CCM->OBSERVE[obsIndex].CONTROL     = CCM_OBSERVE_CONTROL_OFF_MASK;   /* turn off detect */
    CCM->OBSERVE[obsIndex].CONTROL_SET = CCM_OBSERVE_CONTROL_RESET_MASK; /* reset slice */
    CCM->OBSERVE[obsIndex].CONTROL_CLR = CCM_OBSERVE_CONTROL_RAW_MASK;   /* select raw obsSigIndex */
    CCM->OBSERVE[obsIndex].CONTROL &= ~CCM_OBSERVE_CONTROL_SELECT_MASK;  /* Select observed obsSigIndex */
    CCM->OBSERVE[obsIndex].CONTROL |=
        CCM_OBSERVE_CONTROL_SELECT(obsSigIndex) | CCM_OBSERVE_CONTROL_DIVIDE(CCM_OBS_DIV); /* turn on detection */
    CCM->OBSERVE[obsIndex].CONTROL_CLR =
        CCM_OBSERVE_CONTROL_RESET_MASK | CCM_OBSERVE_CONTROL_OFF_MASK; /* unreset and turn on detect */

    while (CCM->OBSERVE[obsIndex].FREQUENCY_CURRENT == 0UL)
    {
    }

    return (CCM->OBSERVE[obsIndex].FREQUENCY_CURRENT * ((uint32_t)CCM_OBS_DIV + 1UL));
}

#if !(defined(MIMXRT1181_SERIES) || defined(MIMXRT1182_SERIES))
/*! brief Enable USB HS clock.
 *
 * This function only enables the access to USB HS prepheral, upper layer
 * should first call the ref CLOCK_EnableUsbhs0PhyPllClock to enable the PHY
 * clock to use USB HS.
 *
 * param src  USB HS does not care about the clock source, here must be ref kCLOCK_UsbSrcUnused.
 * param freq USB HS does not care about the clock source, so this parameter is ignored.
 * retval true The clock is set successfully.
 * retval false The clock source is invalid to get proper USB HS clock.
 */
bool CLOCK_EnableUsbhs0Clock(clock_usb_src_t src, uint32_t freq)
{
    return true;
}
/*! brief Enable USB HS PHY PLL clock.
 *
 * This function enables the internal 480MHz USB PHY PLL clock.
 *
 * param src  USB HS PHY PLL clock source.
 * param freq The frequency specified by src.
 * retval true The clock is set successfully.
 * retval false The clock source is invalid to get proper USB HS clock.
 */
bool CLOCK_EnableUsbhs0PhyPllClock(clock_usb_phy_src_t src, uint32_t freq)
{
    uint32_t phyPllDiv  = 0U;
    uint16_t multiplier = 0U;
    bool err            = false;
    CLOCK_EnableClock(kCLOCK_Usb);

    USBPHY1->CTRL_CLR = USBPHY_CTRL_SFTRST_MASK;

    USBPHY1->PLL_SIC_SET = (USBPHY_PLL_SIC_PLL_POWER(1) | USBPHY_PLL_SIC_PLL_REG_ENABLE_MASK);
    if ((480000000UL % freq) != 0UL)
    {
        return false;
    }
    multiplier = (uint16_t)(480000000UL / freq);

    switch (multiplier)
    {
        case 13:
        {
            phyPllDiv = USBPHY_PLL_SIC_PLL_DIV_SEL(0U);
            break;
        }
        case 15:
        {
            phyPllDiv = USBPHY_PLL_SIC_PLL_DIV_SEL(1U);
            break;
        }
        case 16:
        {
            phyPllDiv = USBPHY_PLL_SIC_PLL_DIV_SEL(2U);
            break;
        }
        case 20:
        {
            phyPllDiv = USBPHY_PLL_SIC_PLL_DIV_SEL(3U);
            break;
        }
        case 22:
        {
            phyPllDiv = USBPHY_PLL_SIC_PLL_DIV_SEL(4U);
            break;
        }
        case 25:
        {
            phyPllDiv = USBPHY_PLL_SIC_PLL_DIV_SEL(5U);
            break;
        }
        case 30:
        {
            phyPllDiv = USBPHY_PLL_SIC_PLL_DIV_SEL(6U);
            break;
        }
        case 240:
        {
            phyPllDiv = USBPHY_PLL_SIC_PLL_DIV_SEL(7U);
            break;
        }
        default:
        {
            err = true;
            break;
        }
    }

    if (err)
    {
        return false;
    }

    USBPHY1->PLL_SIC = (USBPHY1->PLL_SIC & ~(USBPHY_PLL_SIC_PLL_DIV_SEL_MASK)) | phyPllDiv;

    USBPHY1->PLL_SIC_CLR = USBPHY_PLL_SIC_PLL_BYPASS_MASK;
    USBPHY1->PLL_SIC_SET = (USBPHY_PLL_SIC_PLL_EN_USB_CLKS_MASK);

    USBPHY1->CTRL_CLR = USBPHY_CTRL_CLR_CLKGATE_MASK;

    while (0UL == (USBPHY1->PLL_SIC & USBPHY_PLL_SIC_PLL_LOCK_MASK))
    {
    }
    return true;
}
/*! brief Enable USB HS clock.
 *
 * This function only enables the access to USB HS prepheral, upper layer
 * should first call the ref CLOCK_EnableUsbhs0PhyPllClock to enable the PHY
 * clock to use USB HS.
 *
 * param src  USB HS does not care about the clock source, here must be ref kCLOCK_UsbSrcUnused.
 * param freq USB HS does not care about the clock source, so this parameter is ignored.
 * retval true The clock is set successfully.
 * retval false The clock source is invalid to get proper USB HS clock.
 */
/*! brief Disable USB HS PHY PLL clock.
 *
 * This function disables USB HS PHY PLL clock.
 */
void CLOCK_DisableUsbhs0PhyPllClock(void)
{
    USBPHY1->PLL_SIC_CLR = (USBPHY_PLL_SIC_PLL_EN_USB_CLKS_MASK);
    USBPHY1->CTRL |= USBPHY_CTRL_CLKGATE_MASK; /* Set to 1U to gate clocks */
}
bool CLOCK_EnableUsbhs1Clock(clock_usb_src_t src, uint32_t freq)
{
    return true;
}
bool CLOCK_EnableUsbhs1PhyPllClock(clock_usb_phy_src_t src, uint32_t freq)
{
    uint32_t phyPllDiv  = 0U;
    uint16_t multiplier = 0U;
    bool err            = false;
    CLOCK_EnableClock(kCLOCK_Usb);

    USBPHY2->CTRL_CLR = USBPHY_CTRL_SFTRST_MASK;

    USBPHY2->PLL_SIC_SET = (USBPHY_PLL_SIC_PLL_POWER(1) | USBPHY_PLL_SIC_PLL_REG_ENABLE_MASK);
    if ((480000000UL % freq) != 0UL)
    {
        return false;
    }
    multiplier = (uint16_t)(uint32_t)(480000000UL / freq);

    switch (multiplier)
    {
        case 13:
        {
            phyPllDiv = USBPHY_PLL_SIC_PLL_DIV_SEL(0U);
            break;
        }
        case 15:
        {
            phyPllDiv = USBPHY_PLL_SIC_PLL_DIV_SEL(1U);
            break;
        }
        case 16:
        {
            phyPllDiv = USBPHY_PLL_SIC_PLL_DIV_SEL(2U);
            break;
        }
        case 20:
        {
            phyPllDiv = USBPHY_PLL_SIC_PLL_DIV_SEL(3U);
            break;
        }
        case 22:
        {
            phyPllDiv = USBPHY_PLL_SIC_PLL_DIV_SEL(4U);
            break;
        }
        case 25:
        {
            phyPllDiv = USBPHY_PLL_SIC_PLL_DIV_SEL(5U);
            break;
        }
        case 30:
        {
            phyPllDiv = USBPHY_PLL_SIC_PLL_DIV_SEL(6U);
            break;
        }
        case 240:
        {
            phyPllDiv = USBPHY_PLL_SIC_PLL_DIV_SEL(7U);
            break;
        }
        default:
        {
            err = true;
            break;
        }
    }

    if (err)
    {
        return false;
    }
    USBPHY2->PLL_SIC = (USBPHY2->PLL_SIC & ~(USBPHY_PLL_SIC_PLL_DIV_SEL_MASK)) | phyPllDiv;

    USBPHY2->PLL_SIC_CLR = USBPHY_PLL_SIC_PLL_BYPASS_MASK;
    USBPHY2->PLL_SIC_SET = (USBPHY_PLL_SIC_PLL_EN_USB_CLKS_MASK);

    USBPHY2->CTRL_CLR = USBPHY_CTRL_CLR_CLKGATE_MASK;

    while (0UL == (USBPHY2->PLL_SIC & USBPHY_PLL_SIC_PLL_LOCK_MASK))
    {
    }
    return true;
}
/*! brief Disable USB HS PHY PLL clock.
 *
 * This function disables USB HS PHY PLL clock.
 */
void CLOCK_DisableUsbhs1PhyPllClock(void)
{
    USBPHY2->PLL_SIC_CLR = (USBPHY_PLL_SIC_PLL_EN_USB_CLKS_MASK);
    USBPHY2->CTRL |= USBPHY_CTRL_CLKGATE_MASK; /* Set to 1U to gate clocks */
}
#endif

void CLOCK_OSCPLL_ControlByCpuLowPowerMode(clock_name_t name, uint32_t domainMap, clock_level_t level)
{
    uint32_t domainIndex            = 0UL;
    uint32_t tmp32                  = 0UL;
    uint32_t regIndex               = 0UL;
    volatile uint32_t *ptrMemLpmReg = NULL;

    /* Set control mode to unassigned mode. */
    CCM->OSCPLL[name].AUTHEN &= ~(CCM_OSCPLL_AUTHEN_AUTO_CTRL_MASK | CCM_OSCPLL_AUTHEN_CPULPM_MODE_MASK);

    /* Change clock depend level for each domain in unassigned mode. */
    domainMap &= 0xFFFFU;
    ptrMemLpmReg = &(CCM->OSCPLL[name].LPM0);
    for (regIndex = 0UL; regIndex < 2UL; regIndex++)
    {
        ptrMemLpmReg += regIndex;
        tmp32 = *ptrMemLpmReg;
        for (domainIndex = 0UL; domainIndex < 8UL; domainIndex++)
        {
            if (0UL != (domainMap & (1UL << ((regIndex * 8UL) + domainIndex))))
            {
                tmp32 &= ~((uint32_t)CCM_OSCPLL_LPM0_LPM_SETTING_D0_MASK << (domainIndex * 4U));
                tmp32 |= ((uint32_t)CCM_OSCPLL_LPM0_LPM_SETTING_D0(level) << (domainIndex * 4U));
            }
        }
        *ptrMemLpmReg = tmp32;
    }

    /* Set control mode to CPU low power mode. */
    CCM->OSCPLL[name].AUTHEN |= CCM_OSCPLL_AUTHEN_CPULPM_MODE_MASK;
}

void CLOCK_LPCG_ControlByCpuLowPowerMode(clock_lpcg_t name, uint32_t domainMap, clock_level_t level)
{
    uint32_t domainIndex            = 0UL;
    uint32_t tmp32                  = 0UL;
    uint32_t regIndex               = 0UL;
    volatile uint32_t *ptrMemLpmReg = NULL;

    /* Set control mode to unassigned mode. */
    CCM->LPCG[name].AUTHEN &= ~CCM_LPCG_AUTHEN_CPULPM_MODE_MASK;

    /* Change clock depend level for each domain in unassigned mode. */
    domainMap &= 0xFFFFU;
    ptrMemLpmReg = &(CCM->LPCG[name].LPM0);
    for (regIndex = 0UL; regIndex < 2UL; regIndex++)
    {
        ptrMemLpmReg += regIndex;
        tmp32 = *ptrMemLpmReg;
        for (domainIndex = 0UL; domainIndex < 8UL; domainIndex++)
        {
            if (0UL != (domainMap & (1UL << ((regIndex * 8UL) + domainIndex))))
            {
                tmp32 &= ~((uint32_t)CCM_LPCG_LPM0_LPM_SETTING_D0_MASK << (domainIndex * 4U));
                tmp32 |= ((uint32_t)CCM_LPCG_LPM0_LPM_SETTING_D0(level) << (domainIndex * 4U));
            }
        }
        *ptrMemLpmReg = tmp32;
    }

    /* Set control mode to CPU low power mode. */
    CCM->LPCG[name].AUTHEN |= CCM_LPCG_AUTHEN_CPULPM_MODE_MASK;
}
