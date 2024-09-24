/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_clock.h"
#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.clock"
#endif

#define FRO0_DEFAULT_CLOCK_FREQ 300000000U
#define FRO1_MAX_CLOCK_FREQ     192000000U
#define FRO2_DEFAULT_CLOCK_FREQ 196000000U

#define FRO_MIN_CLOCK_FREQ 150000000U
#define FRO_MAX_CLOCK_FREQ 300000000U

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if defined(FSL_CLOCK_DRIVER_COMPUTE)
/* Array of LPUART peripheral base address. */
static FRO_Type *const s_froBases[]   = FRO_BASE_PTRS;
volatile uint32_t g_senseAudioClkFreq = 0U;
#endif

/* External XTAL (OSC) clock frequency. */
volatile uint32_t g_xtalFreq = 24000000U;
/* External CLK_IN pin clock frequency. */
volatile uint32_t g_clkinFreq = 0U;
/* External MCLK IN clock frequency. */
volatile uint32_t g_mclkFreq = 0U;
/* External 32 kHz input clock  pin clock frequency. */
volatile uint32_t g_32kClkinFreq = 0U;

/*******************************************************************************
 * Code
 ******************************************************************************/
void CLOCK_EnableClock(clock_ip_name_t clk)
{
    uint32_t index   = CLK_GATE_ABSTRACT_REG_OFFSET(clk);
    uint32_t bitMask = 1UL << CLK_GATE_ABSTRACT_BITS_SHIFT(clk);

    switch (index)
    {
#if defined(FSL_CLOCK_DRIVER_COMPUTE) || defined(FSL_CLOCK_DRIVER_MEDIA)
        case CLK_CTL0_PSCCTL0:
            CLKCTL0->PSCCTL0_SET = bitMask;
            while ((CLKCTL0->PSCCTL0 & bitMask) == 0U)
            {
            }
            break;
        case CLK_CTL0_PSCCTL1:
            CLKCTL0->PSCCTL1_SET = bitMask;
            while ((CLKCTL0->PSCCTL1 & bitMask) == 0U)
            {
            }
            break;
        case CLK_CTL0_PSCCTL2:
            CLKCTL0->PSCCTL2_SET = bitMask;
            while ((CLKCTL0->PSCCTL2 & bitMask) == 0U)
            {
            }
            break;
        case CLK_CTL0_PSCCTL3:
            CLKCTL0->PSCCTL3_SET = bitMask;
            while ((CLKCTL0->PSCCTL3 & bitMask) == 0U)
            {
            }
            break;
        case CLK_CTL0_PSCCTL4:
            CLKCTL0->PSCCTL4_SET = bitMask;
            while ((CLKCTL0->PSCCTL4 & bitMask) == 0U)
            {
            }
            break;
        case CLK_CTL0_PSCCTL5:
            CLKCTL0->PSCCTL5_SET = bitMask;
            while ((CLKCTL0->PSCCTL5 & bitMask) == 0U)
            {
            }
            break;
        case CLK_CTL3_PSCCTL0:
            CLKCTL3->PSCCTL0_COMP_SET = bitMask;
            while ((CLKCTL3->PSCCTL0_COMP & bitMask) == 0U)
            {
            }
            break;
        case CLK_CTL4_PSCCTL0:
            CLKCTL4->PSCCTL0_MEDIA_SET = bitMask;
            while ((CLKCTL4->PSCCTL0_MEDIA & bitMask) == 0U)
            {
            }
            break;
        case CLK_CTL4_PSCCTL1:
            CLKCTL4->PSCCTL1_MEDIA_SET = bitMask;
            while ((CLKCTL4->PSCCTL1_MEDIA & bitMask) == 0U)
            {
            }
            break;
        case SYSCON0_SEC_CLK_CTRL:
            SYSCON0->SEC_CLK_CTRL_SET = bitMask;
            while ((SYSCON0->SEC_CLK_CTRL & bitMask) == 0U)
            {
            }
            break;
        case CLKCTL0_ONE_SRC_CLKSLICE_ENABLE:
            CLKCTL0->ONE_SRC_CLKSLICE_ENABLE |= bitMask;
            while ((CLKCTL0->ONE_SRC_CLKSLICE_ENABLE & bitMask) == 0U)
            {
            }
            break;
        case CLKCTL3_ONE_SRC_CLKSLICE_ENABLE:
            CLKCTL3->ONE_SRC_CLKSLICE_ENABLE_COMP |= bitMask;
            while ((CLKCTL3->ONE_SRC_CLKSLICE_ENABLE_COMP & bitMask) == 0U)
            {
            }
            break;
        case CLKCTL4_ONE_SRC_CLKSLICE_ENABLE:
            CLKCTL4->ONE_SRC_CLKSLICE_ENABLE |= bitMask;
            while ((CLKCTL4->ONE_SRC_CLKSLICE_ENABLE & bitMask) == 0U)
            {
            }
            break;
#else  /* Sense domain */
        case CLK_CTL1_PSCCTL0:
            CLKCTL1->PSCCTL0_SET = bitMask;
            while ((CLKCTL1->PSCCTL0 & bitMask) == 0U)
            {
            }
            break;
        case CLK_CTL1_PSCCTL1:
            CLKCTL1->PSCCTL1_SET = bitMask;
            while ((CLKCTL1->PSCCTL1 & bitMask) == 0U)
            {
            }
            break;
        case CLK_CTL3_PSCCTL0:
            CLKCTL3->PSCCTL0_SENS_SET = bitMask;
            while ((CLKCTL3->PSCCTL0_SENS & bitMask) == 0U)
            {
            }
            break;
        case CLK_CTL4_PSCCTL0:
            CLKCTL4->PSCCTL0_SENS_SET = bitMask;
            while ((CLKCTL4->PSCCTL0_SENS & bitMask) == 0U)
            {
            }
            break;
        case CLK_CTL4_PSCCTL1:
            CLKCTL4->PSCCTL1_SENS_SET = bitMask;
            while ((CLKCTL4->PSCCTL1_SENS & bitMask) == 0U)
            {
            }
            break;
        case CLKCTL3_ONE_SRC_CLKSLICE_ENABLE:
            CLKCTL3->ONE_SRC_CLKSLICE_ENABLE_SENSE |= bitMask;
            while ((CLKCTL3->ONE_SRC_CLKSLICE_ENABLE_SENSE & bitMask) == 0U)
            {
            }
            break;
        case CLKCTL4_ONE_SRC_CLKSLICE_ENABLE:
            CLKCTL4->ONE_SRC_CLKSLICE_ENABLE_SENSE |= bitMask;
            while ((CLKCTL4->ONE_SRC_CLKSLICE_ENABLE_SENSE & bitMask) == 0U)
            {
            }
            break;
#endif /* FSL_CLOCK_DRIVER_COMPUTE */
        case CLK_CTL2_PSCCTL0:
            CLKCTL2->PSCCTL0_SET = bitMask;
            while ((CLKCTL2->PSCCTL0 & bitMask) == 0U)
            {
            }
            break;
        case SYSCON3_SEC_CLK_CTRL:
            SYSCON3->SEC_CLK_CTRL_SET = bitMask;
            while ((SYSCON3->SEC_CLK_CTRL & bitMask) == 0U)
            {
            }
            break;
        default:
            /* Should not go here. */
            assert(false);
            break;
    }
}

void CLOCK_DisableClock(clock_ip_name_t clk)
{
    uint32_t index = CLK_GATE_ABSTRACT_REG_OFFSET(clk);
    switch (index)
    {
#if defined(FSL_CLOCK_DRIVER_COMPUTE) || defined(FSL_CLOCK_DRIVER_MEDIA)
        case CLK_CTL0_PSCCTL0:
            CLKCTL0->PSCCTL0_CLR = (1UL << CLK_GATE_ABSTRACT_BITS_SHIFT(clk));
            break;
        case CLK_CTL0_PSCCTL1:
            CLKCTL0->PSCCTL1_CLR = (1UL << CLK_GATE_ABSTRACT_BITS_SHIFT(clk));
            break;
        case CLK_CTL0_PSCCTL2:
            CLKCTL0->PSCCTL2_CLR = (1UL << CLK_GATE_ABSTRACT_BITS_SHIFT(clk));
            break;
        case CLK_CTL0_PSCCTL3:
            CLKCTL0->PSCCTL3_CLR = (1UL << CLK_GATE_ABSTRACT_BITS_SHIFT(clk));
            break;
        case CLK_CTL0_PSCCTL4:
            CLKCTL0->PSCCTL4_CLR = (1UL << CLK_GATE_ABSTRACT_BITS_SHIFT(clk));
            break;
        case CLK_CTL0_PSCCTL5:
            CLKCTL0->PSCCTL5_CLR = (1UL << CLK_GATE_ABSTRACT_BITS_SHIFT(clk));
            break;
        case CLK_CTL3_PSCCTL0:
            CLKCTL3->PSCCTL0_COMP_CLR = (1UL << CLK_GATE_ABSTRACT_BITS_SHIFT(clk));
            break;
        case CLK_CTL4_PSCCTL0:
            CLKCTL4->PSCCTL0_MEDIA_CLR = (1UL << CLK_GATE_ABSTRACT_BITS_SHIFT(clk));
            break;
        case CLK_CTL4_PSCCTL1:
            CLKCTL4->PSCCTL1_MEDIA_CLR = (1UL << CLK_GATE_ABSTRACT_BITS_SHIFT(clk));
            break;
        case SYSCON0_SEC_CLK_CTRL:
            SYSCON0->SEC_CLK_CTRL_CLR = (1UL << CLK_GATE_ABSTRACT_BITS_SHIFT(clk));
            break;
        case CLKCTL0_ONE_SRC_CLKSLICE_ENABLE:
            CLKCTL0->ONE_SRC_CLKSLICE_ENABLE &= ~(1UL << CLK_GATE_ABSTRACT_BITS_SHIFT(clk));
            break;
        case CLKCTL3_ONE_SRC_CLKSLICE_ENABLE:
            CLKCTL3->ONE_SRC_CLKSLICE_ENABLE_COMP &= ~(1UL << CLK_GATE_ABSTRACT_BITS_SHIFT(clk));
            break;
        case CLKCTL4_ONE_SRC_CLKSLICE_ENABLE:
            CLKCTL4->ONE_SRC_CLKSLICE_ENABLE &= ~(1UL << CLK_GATE_ABSTRACT_BITS_SHIFT(clk));
            break;
#else
        case CLK_CTL1_PSCCTL0:
            CLKCTL1->PSCCTL0_CLR = (1UL << CLK_GATE_ABSTRACT_BITS_SHIFT(clk));
            break;
        case CLK_CTL1_PSCCTL1:
            CLKCTL1->PSCCTL1_CLR = (1UL << CLK_GATE_ABSTRACT_BITS_SHIFT(clk));
            break;
        case CLK_CTL3_PSCCTL0:
            CLKCTL3->PSCCTL0_SENS_CLR = (1UL << CLK_GATE_ABSTRACT_BITS_SHIFT(clk));
            break;
        case CLK_CTL4_PSCCTL0:
            CLKCTL4->PSCCTL0_SENS_CLR = (1UL << CLK_GATE_ABSTRACT_BITS_SHIFT(clk));
            break;
        case CLK_CTL4_PSCCTL1:
            CLKCTL4->PSCCTL1_SENS_CLR = (1UL << CLK_GATE_ABSTRACT_BITS_SHIFT(clk));
            break;
        case CLKCTL3_ONE_SRC_CLKSLICE_ENABLE:
            CLKCTL3->ONE_SRC_CLKSLICE_ENABLE_SENSE &= ~(1UL << CLK_GATE_ABSTRACT_BITS_SHIFT(clk));
            break;
        case CLKCTL4_ONE_SRC_CLKSLICE_ENABLE:
            CLKCTL4->ONE_SRC_CLKSLICE_ENABLE_SENSE &= ~(1UL << CLK_GATE_ABSTRACT_BITS_SHIFT(clk));
            break;
#endif
        case CLK_CTL2_PSCCTL0:
            CLKCTL2->PSCCTL0_CLR = (1UL << CLK_GATE_ABSTRACT_BITS_SHIFT(clk));
            break;
        case SYSCON3_SEC_CLK_CTRL:
            SYSCON3->SEC_CLK_CTRL_CLR = (1UL << CLK_GATE_ABSTRACT_BITS_SHIFT(clk));
            break;
        default:
            /* Should not go here. */
            assert(false);
            break;
    }
}

/* Clock Selection for IP */
/**
 * brief   Configure the clock selection muxes.
 * param   connection : Clock to be configured.
 * return  Nothing
 */
void CLOCK_AttachClk(clock_attach_id_t connection)
{
    volatile uint32_t *pClkSel;

    switch (((uint32_t)connection) & 0xE0000000U)
    {
        case CLKCTL4_INDEX:
            pClkSel = CLKCTL_TUPLE_REG(CLKCTL4, connection);
            break;
        case CLKCTL3_INDEX:
            pClkSel = CLKCTL_TUPLE_REG(CLKCTL3, connection);
            break;
        case CLKCTL2_INDEX:
            pClkSel = CLKCTL_TUPLE_REG(CLKCTL2, connection);
            break;
#if defined(FSL_CLOCK_DRIVER_SENSE)
        case CLKCTL1_INDEX:
            pClkSel = CLKCTL_TUPLE_REG(CLKCTL1, connection);
            break;
#else
        case CLKCTL0_INDEX:
            pClkSel = CLKCTL_TUPLE_REG(CLKCTL0, connection);
            break;
#endif
        default:
            pClkSel = NULL;
            break;
    }

    if (pClkSel != NULL)
    {
        if (((uint32_t)connection & CLK_MUX_DISABLE_OUTPUT_MASK) != 0U) /* For muxes with SEL_EN bit*/
        {
            *pClkSel = (*pClkSel & 0xFFFFFF8UL) | CLKCTL_TUPLE_SEL(connection);
        }
        else
        {
            *pClkSel = (*pClkSel & 0xFFFFFFCUL) | CLKCTL_TUPLE_SEL(connection) | 0x4U;
        }
    }
    else
    {
        /* Unreachable */
        assert(false);
    }
}

/* Set IP Clock divider */
/**
 * brief   Setup peripheral clock dividers.
 * param   div_name    : Clock divider name
 * param   divider     : Value to be divided. Divided clock frequency = Undivided clock frequency / divider.
 * return  Nothing
 */
void CLOCK_SetClkDiv(clock_div_name_t div_name, uint32_t divider)
{
    volatile uint32_t *pClkDiv = NULL;

    switch (((uint32_t)div_name) & 0xE0000000U)
    {
        case CLKCTL4_INDEX:
            pClkDiv = CLKCTL_TUPLE_REG(CLKCTL4, div_name);
            break;
        case CLKCTL3_INDEX:
            pClkDiv = CLKCTL_TUPLE_REG(CLKCTL3, div_name);
            break;
        case CLKCTL2_INDEX:
            pClkDiv = CLKCTL_TUPLE_REG(CLKCTL2, div_name);
            break;
#if defined(FSL_CLOCK_DRIVER_SENSE)
        case CLKCTL1_INDEX:
            pClkDiv = CLKCTL_TUPLE_REG(CLKCTL1, div_name);
            break;
#else
        case CLKCTL0_INDEX:
            pClkDiv = CLKCTL_TUPLE_REG(CLKCTL0, div_name);
            break;
#endif
        default:
            /* Should not go here. */
            assert(false);
            break;
    }

        /* Reset the divider counter */
#if defined(FSL_CLOCK_DRIVER_SENSE)
    if (div_name != kCLOCK_DivSenseMainClk)
#endif
#if defined(FSL_CLOCK_DRIVER_COMPUTE)
    if ((div_name != kCLOCK_DivCmptMainClk) && (div_name != kCLOCK_DivSenseMainClk))
#endif
    {
        *pClkDiv |= 1UL << 29U;
    }

    if (divider == 0U) /*!<  halt */
    {
        *pClkDiv |= 1UL << 30U;
    }
    else
    {
        *pClkDiv = divider - 1U;

        while (((*pClkDiv) & 0x80000000U) != 0U)
        {
        }
    }
}

uint32_t CLOCK_GetFreq(clock_name_t clockName)
{
    uint32_t freq = 0U;

    switch (clockName)
    {
        case kCLOCK_CoreSysClk:
#if defined(FSL_CLOCK_DRIVER_COMPUTE)
        case kCLOCK_BusClk:
            freq = CLOCK_GetComputeMainClkFreq();
            break;
        case kCLOCK_Vdd2ClockOutClk:
            freq = CLOCK_GetClockOutClkFreq();
            break;
        case kCLOCK_Wdt0Clk:
            freq = CLOCK_GetWdtClkFreq(0U);
            break;
        case kCLOCK_Wdt1Clk:
            freq = CLOCK_GetWdtClkFreq(1U);
            break;
        case kCLOCK_Xspi0Clk:
            freq = CLOCK_GetXspiClkFreq(0U);
            break;
        case kCLOCK_Xspi1Clk:
            freq = CLOCK_GetXspiClkFreq(1U);
            break;
        case kCLOCK_SctClk:
            freq = CLOCK_GetSctClkFreq();
            break;
        case kCLOCK_Hifi4CpuClk:
            freq = CLOCK_GetHifi4ClkFreq();
            break;
        case kCLOCK_LPFlexComm0Clk:
            freq = CLOCK_GetLPFlexCommClkFreq(0U);
            break;
        case kCLOCK_LPFlexComm1Clk:
            freq = CLOCK_GetLPFlexCommClkFreq(1U);
            break;
        case kCLOCK_LPFlexComm2Clk:
            freq = CLOCK_GetLPFlexCommClkFreq(2U);
            break;
        case kCLOCK_LPFlexComm3Clk:
            freq = CLOCK_GetLPFlexCommClkFreq(3U);
            break;
        case kCLOCK_LPFlexComm4Clk:
            freq = CLOCK_GetLPFlexCommClkFreq(4U);
            break;
        case kCLOCK_LPFlexComm5Clk:
            freq = CLOCK_GetLPFlexCommClkFreq(5U);
            break;
        case kCLOCK_LPFlexComm6Clk:
            freq = CLOCK_GetLPFlexCommClkFreq(6U);
            break;
        case kCLOCK_LPFlexComm7Clk:
            freq = CLOCK_GetLPFlexCommClkFreq(7U);
            break;
        case kCLOCK_LPFlexComm8Clk:
            freq = CLOCK_GetLPFlexCommClkFreq(8U);
            break;
        case kCLOCK_LPFlexComm9Clk:
            freq = CLOCK_GetLPFlexCommClkFreq(9U);
            break;
        case kCLOCK_LPFlexComm10Clk:
            freq = CLOCK_GetLPFlexCommClkFreq(10U);
            break;
        case kCLOCK_LPFlexComm11Clk:
            freq = CLOCK_GetLPFlexCommClkFreq(11U);
            break;
        case kCLOCK_LPFlexComm12Clk:
            freq = CLOCK_GetLPFlexCommClkFreq(12U);
            break;
        case kCLOCK_LPFlexComm13Clk:
            freq = CLOCK_GetLPFlexCommClkFreq(13U);
            break;
#else
        case kCLOCK_BusClk:
            freq = CLOCK_GetSenseMainClkFreq();
            break;
        case kCLOCK_Wdt2Clk:
            freq = CLOCK_GetWdtClkFreq(2U);
            break;
        case kCLOCK_Wdt3Clk:
            freq = CLOCK_GetWdtClkFreq(3U);
            break;
        case kCLOCK_Hifi1CpuClk:
            freq = CLOCK_GetHifi1ClkFreq();
            break;
        case kCLOCK_LPFlexComm17Clk:
            freq = CLOCK_GetLPFlexCommClkFreq(17U);
            break;
        case kCLOCK_LPFlexComm18Clk:
            freq = CLOCK_GetLPFlexCommClkFreq(18U);
            break;
        case kCLOCK_LPFlexComm19Clk:
            freq = CLOCK_GetLPFlexCommClkFreq(19U);
            break;
        case kCLOCK_LPFlexComm20Clk:
            freq = CLOCK_GetLPFlexCommClkFreq(20U);
            break;
#endif

        case kCLOCK_MclkClk:
            freq = CLOCK_GetMclkInClkFreq();
            break;
        case kCLOCK_Vdd1ClockOutClk:
            freq = CLOCK_GetVdd1ClockOutClkFreq();
            break;
        case kCLOCK_AdcClk:
            freq = CLOCK_GetAdcClkFreq();
            break;
        case kCLOCK_Xspi2Clk:
            freq = CLOCK_GetXspiClkFreq(2U);
            break;
        case kCLOCK_SystickClk:
            freq = CLOCK_GetSystickClkFreq();
            break;
        case kCLOCK_Sdio0Clk:
            freq = CLOCK_GetUsdhcClkFreq(0U);
            break;
        case kCLOCK_Sdio1Clk:
            freq = CLOCK_GetUsdhcClkFreq(1U);
            break;
        case kCLOCK_I3cClk:
            freq = CLOCK_GetI3cClkFreq();
            break;
        case kCLOCK_Usb0Clk:
            freq = CLOCK_GetMediaVddnClkFreq();
            break;
        case kCLOCK_Usb1Clk:
            freq = CLOCK_GetUsbClkFreq();
            break;
        case kCLOCK_PdmClk:
            freq = CLOCK_GetMicfilClkFreq();
            break;
        case kCLOCK_AcmpClk:
            freq = CLOCK_GetAcmpClkFreq();
            break;
        case kCLOCK_LPSpi14Clk:
            freq = CLOCK_GetLPSpiClkFreq(14U);
            break;
        case kCLOCK_LPSpi16Clk:
            freq = CLOCK_GetLPSpiClkFreq(16U);
            break;
        case kCLOCK_LPI2c15Clk:
            freq = CLOCK_GetLPI2cClkFreq(15U);
            break;
        case kCLOCK_FlexioClk:
            freq = CLOCK_GetFlexioClkFreq();
            break;
        case kCLOCK_VgpuClk:
            freq = CLOCK_GetVgpuClkFreq();
            break;
        case kCLOCK_LcdifClk:
            freq = CLOCK_GetLcdifClkFreq();
            break;
        case kCLOCK_MipiDphyClk:
            freq = CLOCK_GetMipiDphyClkFreq();
            break;
        case kCLOCK_MipiDphyEscRxClk:
            freq = CLOCK_GetMipiDphyEscRxClkFreq();
            break;
        case kCLOCK_MipiDphyEscTxClk:
            freq = CLOCK_GetMipiDphyEscTxClkFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

#if defined(FSL_CLOCK_DRIVER_COMPUTE)
/*!
 * brief Get the FRO instance from peripheral base address.
 *
 * param base FRO peripheral base address.
 * return FRO instance.
 */
static uint32_t CLOCK_FroGetInstance(FRO_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0U; instance < ARRAY_SIZE(s_froBases); instance++)
    {
        if (s_froBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_froBases));

    return instance;
}
#endif

static uint32_t CLOCK_CalFroFreq(FRO_Type *base)
{
    uint32_t freq    = 0U;
    bool enabled     = false;
    uint32_t refFreq = 0U;

#if defined(FSL_CLOCK_DRIVER_COMPUTE)
    assert(base != FRO1);
    enabled = ((SLEEPCON0->RUNCFG & ((uint32_t)SLEEPCON0_RUNCFG_FRO0_PD_MASK << CLOCK_FroGetInstance(base))) != 0U) ?
                  false :
                  true;
#else
    enabled = ((SLEEPCON1->RUNCFG & SLEEPCON1_RUNCFG_FRO2_PD_MASK) != 0U) ? false : true;
#endif
    refFreq = (g_xtalFreq != 0U) ? g_xtalFreq : g_clkinFreq;

    if ((base->CSR.RW & FRO_CSR_FROEN_MASK) != 0U || enabled)
    {
        if (base == FRO2)
        {
            if ((base->TEXPCNT.RW & FRO_TEXPCNT_TEXPCNT_MASK) != 0u)
            {
                freq = ((uint32_t)((uint64_t)(base->TRIMCNT.RW) *
                                   ((uint64_t)refFreq / (uint64_t)((base->CNFG1.RW & FRO_CNFG1_REFDIV_MASK) + 1UL)) /
                                   (uint64_t)((base->CNFG1.RW & FRO_CNFG1_RFCLKCNT_MASK) >> FRO_CNFG1_RFCLKCNT_SHIFT)));
            }
            else
            {
                freq = FRO2_DEFAULT_CLOCK_FREQ;
            }
        }
#if defined(FSL_CLOCK_DRIVER_COMPUTE)
        else
        {
            if ((base->TEXPCNT.RW & FRO_TEXPCNT_TEXPCNT_MASK) != 0u)
            {
                freq = ((uint32_t)((uint64_t)(base->TRIMCNT.RW) *
                                   ((uint64_t)refFreq / (uint64_t)((base->CNFG1.RW & FRO_CNFG1_REFDIV_MASK) + 1UL)) /
                                   (uint64_t)((base->CNFG1.RW & FRO_CNFG1_RFCLKCNT_MASK) >> FRO_CNFG1_RFCLKCNT_SHIFT)));
            }
            else
            {
                freq = FRO0_DEFAULT_CLOCK_FREQ;
            }
        }
#endif
    }
    else
    {
        freq = 0U; /* FRO is disabled. */
    }

    return freq;
}

uint32_t CLOCK_GetFroClkFreq(uint32_t id)
{
    uint32_t freq = 0U;

    switch (id)
    {
#if defined(FSL_CLOCK_DRIVER_COMPUTE)
        case 0U:
            freq = CLOCK_CalFroFreq(FRO0);
            break;
#endif
        case 1U:
            freq = FRO1_MAX_CLOCK_FREQ;
            break;
        case 2U:
            freq = CLOCK_CalFroFreq(FRO2);
            break;
        default:
            /* Added comments to prevent the violation of MISRA C-2012 rule. */
            break;
    }

    return freq;
}

uint32_t CLOCK_GetFroFlags(FRO_Type *base)
{
    uint32_t flags = 0U;

    flags = base->CSR.RW & (FRO_CSR_TUNE_ERR_MASK | FRO_CSR_LOL_ERR_MASK | FRO_CSR_TRUPREQ_MASK |
                            FRO_CSR_TUNEONCE_DONE_MASK | FRO_CSR_TRIM_LOCK_MASK);
    return flags;
}

void CLOCK_EnableFroClkOutput(FRO_Type *base, uint32_t divOutEnable)
{
    if (divOutEnable != 0U)
    {
        /* Wait clock ready. */
        if (base == FRO2)
        {
            while ((CLKCTL3->FRO2CLKSTATUS & CLKCTL3_FRO2CLKSTATUS_CLK_OK_MASK) == 0U)
            {
            }
        }
#if defined(FSL_CLOCK_DRIVER_COMPUTE)
        else if (base == FRO0)
        {
            while ((CLKCTL0->FRO01CLKSTATUS & CLKCTL0_FRO01CLKSTATUS_FRO0_CLK_OK_MASK) == 0U)
            {
            }
        }
        else
        {
            while ((CLKCTL0->FRO01CLKSTATUS & CLKCTL0_FRO01CLKSTATUS_FRO1_CLK_OK_MASK) == 0U)
            {
            }
        }
#else
        else
        {
            /* Intentional empty. */
        }
#endif /* FSL_CLOCK_DRIVER_COMPUTE */
    }
    else
    {
        /* Intentional empty. */
    }

    base->CSR.CLR = ((base->CSR.RW & FRO_CSR_CLKGATE_MASK) ^ divOutEnable) & FRO_CSR_CLKGATE_MASK;
    base->CSR.SET = divOutEnable;
}

status_t CLOCK_EnableFroAutoTuning(FRO_Type *base, const clock_fro_config_t *config, bool enable)
{
    uint32_t refFreq    = 0U;
    uint32_t tempCnt    = 0U;
    uint32_t trim1Delay = 0U;
    uint32_t trim2Delay = 0U;
    uint32_t freqkHZ    = 0U;
    status_t ret        = kStatus_Success;

    if (enable)
    {
        /* Check parameter. FRO1 192MHz, FRO0,2 150MHz ~ 300MHz*/
        if ((config->targetFreq < FRO_MIN_CLOCK_FREQ) || (config->targetFreq > FRO_MAX_CLOCK_FREQ) ||
            (config->refDiv == 0U))
        {
            ret = kStatus_InvalidArgument;
        }
#if defined(FSL_CLOCK_DRIVER_COMPUTE)
        else if ((base == FRO1) && (config->targetFreq != FRO1_MAX_CLOCK_FREQ))
        {
            ret = kStatus_InvalidArgument;
        }
#endif
        else
        {
            /* Do nothing. */
        }

        if (ret == kStatus_Success)
        {
            /* Both FRO_PD in SLEEPCON and FROEN can power up FRO, clear FROEN for only using FRO_PD to control it's
             * power. */
            base->CSR.CLR = FRO_CSR_FROEN_MASK | FRO_CSR_TREN_MASK | FRO_CSR_TRUPEN_MASK;

            refFreq = CLOCK_GetXtalInClkFreq() / (config->refDiv);
            freqkHZ = config->targetFreq / 1000U;

            tempCnt = (10U * refFreq + freqkHZ - 1U) /
                      freqkHZ; /* REFCLKCNT = 10000 * divided reference clock / FRO target frequency. */
            base->CNFG1.RW =
                config->enableInt | FRO_CNFG1_RFCLKCNT(tempCnt) | FRO_CNFG1_REFDIV((uint32_t)config->refDiv - 1UL);

            /* TEXPCNT */
            tempCnt          = (uint32_t)((uint64_t)config->targetFreq * tempCnt / refFreq);
            base->TEXPCNT.RW = FRO_TEXPCNT_TEXPCNT(tempCnt) | FRO_TEXPCNT_TEXPCNT_RANGE(config->range);

            trim1Delay     = refFreq / 1000000UL * (uint32_t)config->trim1DelayUs;
            trim2Delay     = refFreq / 1000000UL * (uint32_t)config->trim2DelayUs;
            base->CNFG2.RW = FRO_CNFG2_TRIM1_DELAY(trim1Delay == 0U ? 1U : trim1Delay) |
                             FRO_CNFG2_TRIM2_DELAY(trim2Delay == 0U ? 1U : trim2Delay);

            if (config->coarseTrimEn)
            {
                base->CSR.SET = FRO_CSR_COARSEN_MASK;
            }
            else
            {
                base->CSR.CLR = FRO_CSR_COARSEN_MASK;
            }
            /* Enable FRO close loop mode. */
            base->CSR.SET = FRO_CSR_TREN_MASK | FRO_CSR_TRUPEN_MASK;
        }
        else
        {
            /* Do nothing. */
        }

        return ret;
    }
    else
    {
        base->CSR.CLR = FRO_CSR_TREN_MASK | FRO_CSR_TRUPEN_MASK;
        ret           = kStatus_Success;
    }

    return ret;
}

void CLOCK_EnableFroClkFreq(FRO_Type *base, uint32_t targetFreq, uint32_t divOutEnable)
{
    const clock_fro_config_t froAutotrimCfg = {
        .targetFreq   = targetFreq,
        .range        = 50U, /* For about 0.5% deviation. */
        .trim1DelayUs = 15U,
        .trim2DelayUs = 150U,
        .refDiv       = 1U,
        .enableInt    = 0U,
        .coarseTrimEn = true,
    };
    (void)CLOCK_EnableFroClkFreqCloseLoop(base, &froAutotrimCfg, divOutEnable);
    (void)CLOCK_EnableFroAutoTuning(base, &froAutotrimCfg, false);
}

void CLOCK_ConfigFroTrim(FRO_Type *base, uint16_t trimVal)
{
    base->FROTRIM.RW = (base->FROTRIM.RW & ~(FRO_FROTRIM_COARSE_TRIM_MASK | FRO_FROTRIM_FINE_TRIM_MASK)) |
                       FRO_FROTRIM_COARSE_TRIM(((uint32_t)trimVal & 0xF80U) >> 0x7U) |
                       FRO_FROTRIM_FINE_TRIM((uint32_t)trimVal & 0x7FU);
}

status_t CLOCK_EnableFroClkFreqCloseLoop(FRO_Type *base, const clock_fro_config_t *config, uint32_t divOutEnable)
{
    status_t ret   = kStatus_Success;
    uint32_t flags = 0U;

    /*Power up FRO */
#if defined(FSL_CLOCK_DRIVER_COMPUTE)
    SLEEPCON0->RUNCFG_CLR = (uint32_t)SLEEPCON0_RUNCFG_FRO0_PD_MASK << CLOCK_FroGetInstance(base);
#else
    SLEEPCON1->RUNCFG_CLR = (uint32_t)SLEEPCON1_RUNCFG_FRO2_PD_MASK;
#endif

    /* Disable output before changeing frequency. */
    CLOCK_EnableFroClkOutput(base, 0U);
    ret = CLOCK_EnableFroAutoTuning(base, config, true);

    if (ret == kStatus_Success)
    {
        /* Polling wait tune finish. */
        do
        {
            flags = CLOCK_GetFroFlags(base);

        } while ((flags & FRO_CSR_TRIM_LOCK_MASK) == 0U);

        if ((flags & (FRO_CSR_TUNE_ERR_MASK | FRO_CSR_LOL_ERR_MASK)) != 0U)
        {
            ret = kStatus_Fail; /* Error occures. */
        }
        else
        {
            ret = kStatus_Success;
            /* Configure the FROTRIM with autotrim value. */
            CLOCK_ConfigFroTrim(base, (uint16_t)(base->AUTOTRIM.RW & FRO_AUTOTRIM_AUTOTRIM_MASK));
        }
    }

    /* Enable output */
    CLOCK_EnableFroClkOutput(base, divOutEnable);

    return ret;
}

void CLOCK_DisableFro(FRO_Type *base)
{
    CLOCK_EnableFroClkOutput(base, 0);
    base->CSR.CLR = FRO_CSR_FROEN_MASK | FRO_CSR_TREN_MASK | FRO_CSR_TRUPEN_MASK;

    /*Power down FRO */
#if defined(FSL_CLOCK_DRIVER_COMPUTE)
    SLEEPCON0->RUNCFG_SET = (uint32_t)SLEEPCON0_RUNCFG_FRO0_PD_MASK << CLOCK_FroGetInstance(base);
#else
    SLEEPCON1->RUNCFG_SET = SLEEPCON1_RUNCFG_FRO2_PD_MASK;
#endif
}

/* Initialize the SYSTEM PLL Clk */
/*! brief  Initialize the System PLL.
 *  param  config    : Configuration to set to PLL.
 */
void CLOCK_InitMainPll(const clock_main_pll_config_t *config)
{
    /* Power down MAINPLL before change fractional settings */
#if defined(FSL_CLOCK_DRIVER_COMPUTE)
    SLEEPCON0->RUNCFG_SET = SLEEPCON0_RUNCFG_PLLLDO_PD_MASK | SLEEPCON0_RUNCFG_PLLANA_PD_MASK;
#else
    SLEEPCON1->RUNCFG_SET = SLEEPCON1_RUNCFG_PLLLDO_PD_MASK | SLEEPCON1_RUNCFG_PLLANA_PD_MASK;
#endif

    CLKCTL2->MAINPLL0CLKSEL = (uint32_t)config->main_pll_src;
    CLKCTL2->MAINPLL0NUM    = config->numerator;
    CLKCTL2->MAINPLL0DENOM  = config->denominator;
    CLKCTL2->MAINPLL0CTL0   = (CLKCTL2->MAINPLL0CTL0 & ~CLKCTL2_MAINPLL0CTL0_MULT_MASK) |
                            CLKCTL2_MAINPLL0CTL0_MULT((uint32_t)(config->main_pll_mult));

    /* Clear System PLL reset*/
    CLKCTL2->MAINPLL0CTL0 &= ~CLKCTL2_MAINPLL0CTL0_RESET_MASK;
    /* Power up MAINPLL*/
#if defined(FSL_CLOCK_DRIVER_COMPUTE)
    SLEEPCON0->RUNCFG_CLR = SLEEPCON0_RUNCFG_PLLLDO_PD_MASK | SLEEPCON0_RUNCFG_PLLANA_PD_MASK;
#else
    SLEEPCON1->RUNCFG_CLR = SLEEPCON1_RUNCFG_PLLLDO_PD_MASK | SLEEPCON1_RUNCFG_PLLANA_PD_MASK;
#endif
    SDK_DelayAtLeastUs((CLKCTL2->MAINPLL0LOCKTIMEDIV2 & CLKCTL2_MAINPLL0LOCKTIMEDIV2_LOCKTIMEDIV2_MASK) / 2UL,
                       SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    /* Set System PLL HOLD_RING_OFF_ENA */
    CLKCTL2->MAINPLL0CTL0 |= CLKCTL2_MAINPLL0CTL0_HOLD_RING_OFF_ENA_MASK;
    SDK_DelayAtLeastUs((CLKCTL2->MAINPLL0LOCKTIMEDIV2 & CLKCTL2_MAINPLL0LOCKTIMEDIV2_LOCKTIMEDIV2_MASK) / 6UL,
                       SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    /* Clear System PLL HOLD_RING_OFF_ENA*/
    CLKCTL2->MAINPLL0CTL0 &= ~CLKCTL2_MAINPLL0CTL0_HOLD_RING_OFF_ENA_MASK;
    SDK_DelayAtLeastUs((CLKCTL2->MAINPLL0LOCKTIMEDIV2 & CLKCTL2_MAINPLL0LOCKTIMEDIV2_LOCKTIMEDIV2_MASK) / 3UL,
                       SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
}

/* Initialize the Main PLL PFD */
/*! brief Initialize the Main PLL PFD.
 *  param pfd    : Which PFD clock to enable.
 *  param divider    : The PFD divider value.
 *  note It is recommended that PFD settings are kept between 12-35.
 */
void CLOCK_InitMainPfd(clock_pfd_t pfd, uint8_t divider)
{
    uint32_t pfdIndex = (uint32_t)pfd;
    uint32_t syspfd;

    syspfd = CLKCTL2->MAINPLL0PFD &
             ~(((uint32_t)CLKCTL2_MAINPLL0PFD_PFD0_CLKGATE_MASK | (uint32_t)CLKCTL2_MAINPLL0PFD_PFD0_MASK)
               << (8UL * pfdIndex));

    /* Disable the clock output first. */
    CLKCTL2->MAINPLL0PFD = syspfd | ((uint32_t)CLKCTL2_MAINPLL0PFD_PFD0_CLKGATE_MASK << (8UL * pfdIndex));

    /* Set the new value and enable output. */
    CLKCTL2->MAINPLL0PFD = syspfd | (CLKCTL2_MAINPLL0PFD_PFD0(divider) << (8UL * pfdIndex));
    /* Wait for output becomes stable. */
    while ((CLKCTL2->MAINPLL0PFD & ((uint32_t)CLKCTL2_MAINPLL0PFD_PFD0_CLKRDY_MASK << (8UL * pfdIndex))) == 0UL)
    {
    }
    /* Clear ready status flag. */
    CLKCTL2->MAINPLL0PFD |= ((uint32_t)CLKCTL2_MAINPLL0PFD_PFD0_CLKRDY_MASK << (8UL * pfdIndex));
}
/* Initialize the Audio PLL Clk */
/*! brief  Initialize the audio PLL.
 *  param  config    : Configuration to set to PLL.
 */
void CLOCK_InitAudioPll(const clock_audio_pll_config_t *config)
{
#if defined(FSL_CLOCK_DRIVER_COMPUTE)
    /* Power down Audio PLL before change fractional settings */
    SLEEPCON0->RUNCFG_SET = SLEEPCON0_RUNCFG_AUDPLLLDO_PD_MASK | SLEEPCON0_RUNCFG_AUDPLLANA_PD_MASK;
#else
    SLEEPCON1->RUNCFG_SET = SLEEPCON1_RUNCFG_AUDPLLLDO_PD_MASK | SLEEPCON1_RUNCFG_AUDPLLANA_PD_MASK;
#endif

    CLKCTL2->AUDIOPLL0CLKSEL = (uint32_t)(config->audio_pll_src);
    CLKCTL2->AUDIOPLL0NUM    = config->numerator;
    CLKCTL2->AUDIOPLL0DENOM  = config->denominator;
    CLKCTL2->AUDIOPLL0CTL0   = (CLKCTL2->AUDIOPLL0CTL0 & ~CLKCTL2_AUDIOPLL0CTL0_MULT_MASK) |
                             CLKCTL2_AUDIOPLL0CTL0_MULT((uint32_t)(config->audio_pll_mult));

    /* Clear Audio PLL reset*/
    CLKCTL2->AUDIOPLL0CTL0 &= ~CLKCTL2_AUDIOPLL0CTL0_RESET_MASK;
    /* Power up Audio PLL*/
#if defined(FSL_CLOCK_DRIVER_COMPUTE)
    /* Power down Audio PLL before change fractional settings */
    SLEEPCON0->RUNCFG_CLR = SLEEPCON0_RUNCFG_AUDPLLLDO_PD_MASK | SLEEPCON0_RUNCFG_AUDPLLANA_PD_MASK;
#else
    SLEEPCON1->RUNCFG_CLR = SLEEPCON1_RUNCFG_AUDPLLLDO_PD_MASK | SLEEPCON1_RUNCFG_AUDPLLANA_PD_MASK;
#endif
    SDK_DelayAtLeastUs((CLKCTL2->AUDIOPLL0LOCKTIMEDIV2 & CLKCTL2_AUDIOPLL0LOCKTIMEDIV2_LOCKTIMEDIV2_MASK) / 2UL,
                       SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    /* Set Audio PLL HOLD_RING_OFF_ENA */
    CLKCTL2->AUDIOPLL0CTL0 |= CLKCTL2_AUDIOPLL0CTL0_HOLD_RING_OFF_ENA_MASK;
    SDK_DelayAtLeastUs((CLKCTL2->AUDIOPLL0LOCKTIMEDIV2 & CLKCTL2_AUDIOPLL0LOCKTIMEDIV2_LOCKTIMEDIV2_MASK) / 6UL,
                       SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    /* Clear Audio PLL HOLD_RING_OFF_ENA*/
    CLKCTL2->AUDIOPLL0CTL0 &= ~CLKCTL2_AUDIOPLL0CTL0_HOLD_RING_OFF_ENA_MASK;
    SDK_DelayAtLeastUs((CLKCTL2->AUDIOPLL0LOCKTIMEDIV2 & CLKCTL2_AUDIOPLL0LOCKTIMEDIV2_LOCKTIMEDIV2_MASK) / 3UL,
                       SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

    /* Each time after PLL power up, software needs to wait the whole PLL lock time the to enable VCO output .*/
    if (config->enableVcoOut)
    {
        CLKCTL2->AUDIOPLL0CTL0 |= CLKCTL2_AUDIOPLL0CTL0_VCO_OUT_ENABLE_MASK;
    }
    else
    {
        CLKCTL2->AUDIOPLL0CTL0 &= ~CLKCTL2_AUDIOPLL0CTL0_VCO_OUT_ENABLE_MASK;
    }
}

/* Initialize the Audio PLL PFD */
/*! brief Initialize the audio PLL PFD.
 *  param pfd    : Which PFD clock to enable.
 *  param divider    : The PFD divider value.
 *  note It is recommended that PFD settings are kept between 12-35.
 */
void CLOCK_InitAudioPfd(clock_pfd_t pfd, uint8_t divider)
{
    uint32_t pfdIndex = (uint32_t)pfd;
    uint32_t syspfd;

    syspfd = CLKCTL2->AUDIOPLL0PFD &
             ~(((uint32_t)CLKCTL2_AUDIOPLL0PFD_PFD0_CLKGATE_MASK | (uint32_t)CLKCTL2_AUDIOPLL0PFD_PFD0_MASK)
               << (8UL * pfdIndex));

    /* Disable the clock output first. */
    CLKCTL2->AUDIOPLL0PFD = syspfd | ((uint32_t)CLKCTL2_AUDIOPLL0PFD_PFD0_CLKGATE_MASK << (8UL * pfdIndex));

    /* Set the new value and enable output. */
    CLKCTL2->AUDIOPLL0PFD = syspfd | (CLKCTL2_AUDIOPLL0PFD_PFD0(divider) << (8UL * pfdIndex));
    /* Wait for output becomes stable. */
    while ((CLKCTL2->AUDIOPLL0PFD & ((uint32_t)CLKCTL2_AUDIOPLL0PFD_PFD0_CLKRDY_MASK << (8UL * pfdIndex))) == 0UL)
    {
    }
    /* Clear ready status flag. */
    CLKCTL2->AUDIOPLL0PFD |= ((uint32_t)CLKCTL2_AUDIOPLL0PFD_PFD0_CLKRDY_MASK << (8UL * pfdIndex));
}

/*! @brief  Enable/Disable sys osc clock from external crystal clock.
 *  @param  enable : true to enable system osc clock, false to bypass system osc.
 *  @param  enableLowPower : true to enable low power mode, false to enable high gain mode.
 *  @param  delay_us : Delay time after OSC power up.
 */
void CLOCK_EnableSysOscClk(bool enable, bool enableLowPower, uint32_t delay_us)
{
    uint32_t ctrl = enableLowPower ? CLKCTL2_SYSOSCCTL0_LP_ENABLE_MASK : 0U;

    if (enable)
    {
        CLKCTL2->SYSOSCCTL0   = ctrl;
        CLKCTL2->SYSOSCBYPASS = 0U;
        SDK_DelayAtLeastUs(delay_us, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    }
    else
    {
        CLKCTL2->SYSOSCCTL0 = ctrl | CLKCTL2_SYSOSCCTL0_BYPASS_ENABLE_MASK;
    }
}

void CLOCK_EnableOsc32K(clock_osc32k_config_t *config)
{
    uint32_t ctrl = OSC32KNP->CTRL;

    ctrl &= ~(OSC32KNP_CTRL_CAP_TRIM_MASK | OSC32KNP_CTRL_CLKMON_EN_MASK | OSC32KNP_CTRL_BYPASS_EN_MASK);
    OSC32KNP->CTRL = ctrl | OSC32KNP_CTRL_CAP_TRIM((uint32_t)config->cap) |
                     OSC32KNP_CTRL_CLKMON_EN((uint32_t)config->monitorEnable) |
                     OSC32KNP_CTRL_BYPASS_EN((uint32_t)config->bypass);

    if (config->lowPowerMode)
    {
        /* Disables the output of an oscillator on the channel before changing the OSC32KNP power mode of the channel.*/
        OSC32KNP->CTRL |= OSC32KNP_CTRL_OSC_DIS_MASK;
        /* Low power mode. */
        OSC32KNP->CTRL &= ~OSC32KNP_CTRL_MODE_MASK;
        /* Wait Self-Charge Oscillator stable. */
        while ((OSC32KNP->STAT & OSC32KNP_STAT_SCXO_STABLE_MASK) == 0U)
        {
        }
        OSC32KNP->CTRL &= ~OSC32KNP_CTRL_OSC_DIS_MASK;
    }
    else
    {
        if ((OSC32KNP->CTRL & OSC32KNP_CTRL_MODE_MASK) == 0U)
        {
            /* Can only change from high power mode to low power mode. */
            assert(false);
        }

        while ((OSC32KNP->STAT & OSC32KNP_STAT_TCXO_STABLE_MASK) == 0U)
        {
        }
    }
}

uint32_t CLOCK_GetOsc32KFreq(void)
{
    uint32_t freq = 0U;

    if ((OSC32KNP->CTRL & OSC32KNP_CTRL_OSC_DIS_MASK) == 0U)
    {
        freq = ((OSC32KNP->CTRL & OSC32KNP_CTRL_BYPASS_EN_MASK) != 0UL) ? g_32kClkinFreq : CLK_RTC_32K_CLK;
    }
    else /* OSC32KNP disabled. */
    {
        freq = 0U;
    }

    return freq;
}

uint32_t CLOCK_GetVddnComBaseClkFreq(void)
{
    uint32_t freq = 0U;

    switch (CLKCTL2->COMNBASECLKSEL & CLKCTL2_COMNBASECLKSEL_SEL_MASK)
    {
        case CLKCTL2_COMNBASECLKSEL_SEL(0U):
            freq = CLOCK_GetFroClkFreq(1U) / 3U;
            break;
        case CLKCTL2_COMNBASECLKSEL_SEL(1U):
            freq = CLOCK_GetFroClkFreq(1U);
            break;
        case CLKCTL2_COMNBASECLKSEL_SEL(2U):
            freq = CLOCK_GetFroClkFreq(0U) / 3U;
            break;
        case CLKCTL2_COMNBASECLKSEL_SEL(3U):
            freq = CLOCK_GetLpOscFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

#if defined(FSL_CLOCK_DRIVER_COMPUTE)
/*! @brief  Enable/Disable FRO clock output. */
void CLOCK_EnableFro0ClkForDomain(uint32_t domainEnable)
{
    if (domainEnable != 0U)
    {
        /* Wait FRO stable first in case FRO just get powered on. */
        while ((CLKCTL0->FRO01CLKSTATUS & CLKCTL0_FRO01CLKSTATUS_FRO0_CLK_OK_MASK) == 0U)
        {
        }
    }
    else
    {
        /* Do nothing */
    }
    CLKCTL0->FRO0MAXDOMAINEN = domainEnable & (uint32_t)kCLOCK_AllDomainEnable;
}

uint32_t CLOCK_GetComputeBaseClkFreq(void)
{
    uint32_t freq   = 0U;
    uint32_t clkSel = 0U;
    clkSel          = CLKCTL0->CMPTBASECLKSEL & CLKCTL0_CMPTBASECLKSEL_SEL_MASK;

    switch (clkSel)
    {
        case CLKCTL0_CMPTBASECLKSEL_SEL(0U):
            freq = CLOCK_GetFroClkFreq(1U) / 3U;
            break;
        case CLKCTL0_CMPTBASECLKSEL_SEL(1U):
            freq = CLOCK_GetFroClkFreq(1U);
            break;
        case CLKCTL0_CMPTBASECLKSEL_SEL(2U):
            freq = CLOCK_GetFroClkFreq(0U) / 3U;
            break;
        case CLKCTL0_CMPTBASECLKSEL_SEL(3U):
            freq = CLOCK_GetLpOscFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

uint32_t CLOCK_GetComputeDspBaseClkFreq(void)
{
    uint32_t freq   = 0U;
    uint32_t clkSel = 0U;
    clkSel          = CLKCTL0->DSPBASECLKSEL & CLKCTL0_DSPBASECLKSEL_SEL_MASK;

    switch (clkSel)
    {
        case CLKCTL0_CMPTBASECLKSEL_SEL(0U):
            freq = CLOCK_GetFroClkFreq(1U) / 3U;
            break;
        case CLKCTL0_CMPTBASECLKSEL_SEL(1U):
            freq = CLOCK_GetFroClkFreq(1U);
            break;
        case CLKCTL0_CMPTBASECLKSEL_SEL(2U):
            freq = CLOCK_GetFroClkFreq(0U) / 3U;
            break;
        case CLKCTL0_CMPTBASECLKSEL_SEL(3U):
            freq = CLOCK_GetLpOscFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

uint32_t CLOCK_GetVdd2ComBaseClkFreq(void)
{
    uint32_t freq = 0U;

    switch (CLKCTL0->VDD2COMBASECLKSEL & CLKCTL0_VDD2COMBASECLKSEL_SEL_MASK)
    {
        case CLKCTL0_VDD2COMBASECLKSEL_SEL(0U):
            freq = CLOCK_GetFroClkFreq(1U) / 3U;
            break;
        case CLKCTL0_VDD2COMBASECLKSEL_SEL(1U):
            freq = CLOCK_GetFroClkFreq(1U);
            break;
        case CLKCTL0_VDD2COMBASECLKSEL_SEL(2U):
            freq = CLOCK_GetFroClkFreq(0U) / 3U;
            break;
        case CLKCTL0_VDD2COMBASECLKSEL_SEL(3U):
            freq = CLOCK_GetLpOscFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

uint32_t CLOCK_GetComputeAudioClkFreq(void)
{
    uint32_t freq = 0U;

    switch (CLKCTL0->AUDIOVDD2CLKSEL & CLKCTL0_AUDIOVDD2CLKSEL_SEL_MASK)
    {
        case CLKCTL0_AUDIOVDD2CLKSEL_SEL(0U):
            freq = CLOCK_GetMclkInClkFreq();
            break;
        case CLKCTL0_AUDIOVDD2CLKSEL_SEL(1U):
            freq = CLOCK_GetXtalInClkFreq();
            break;
        case CLKCTL0_AUDIOVDD2CLKSEL_SEL(2U):
            freq = CLOCK_GetFroClkFreq(2U) / 8U;
            break;
        case CLKCTL0_AUDIOVDD2CLKSEL_SEL(3U):
            freq = CLOCK_GetAudioPfdFreq(kCLOCK_Pfd3);
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

uint32_t CLOCK_GetSenseAudioClkFreq(void)
{
    return g_senseAudioClkFreq;
}

/* Get FCCLK Clk frequency */
uint32_t CLOCK_GetFCClkFreq(uint32_t id)
{
    uint32_t freq   = 0U;
    uint32_t clkSel = 0U;
    uint32_t clkDiv = 0U;
    bool selEn      = false;

    assert(id <= 3U);

    clkSel = CLKCTL0->FLEXCOMM[id].FCCLKSEL & CLKCTL0_FCCLKSEL_SEL_MASK;
    selEn  = (CLKCTL0->FLEXCOMM[id].FCCLKSEL & CLKCTL0_FCCLKSEL_SEL_EN_MASK) == CLKCTL0_FCCLKSEL_SEL_EN_MASK;
    clkDiv = (CLKCTL0->FLEXCOMM[id].FCCLKDIV & CLKCTL0_FCCLKDIV_DIV_MASK) >> CLKCTL0_FCCLKDIV_DIV_SHIFT;

    if (selEn)
    {
        switch (clkSel)
        {
            case CLKCTL0_FCCLKSEL_SEL(0):
                freq = CLOCK_GetComputeBaseClkFreq();
                break;

            case CLKCTL0_FCCLKSEL_SEL(1):
                freq = CLOCK_GetFroClkFreq(0U);
                break;

            case CLKCTL0_FCCLKSEL_SEL(2):
                freq = CLOCK_GetMainPfdFreq(kCLOCK_Pfd3);
                break;

            case CLKCTL0_FCCLKSEL_SEL(3):
                freq = CLOCK_GetSysOscFreq();
                break;
            default:
                freq = 0U;
                break;
        }
    }
    else
    {
        freq = 0U;
    }

    return (freq / (clkDiv + 1U));
}

uint32_t CLOCK_GetComputeMainClkFreq(void)
{
    uint32_t freq = 0U;

    switch ((CLKCTL0->MAINCLKSEL) & CLKCTL0_MAINCLKSEL_SEL_MASK)
    {
        case CLKCTL0_MAINCLKSEL_SEL(0):
            freq = CLOCK_GetComputeBaseClkFreq();
            break;

        case CLKCTL0_MAINCLKSEL_SEL(1):
            freq = CLOCK_GetMainPfdFreq(kCLOCK_Pfd0);
            break;

        case CLKCTL0_MAINCLKSEL_SEL(2):
            freq = CLOCK_GetFroClkFreq(0U);
            break;

        case CLKCTL0_MAINCLKSEL_SEL(3):
            freq = CLOCK_GetAudioPfdFreq(kCLOCK_Pfd1);
            break;

        default:
            freq = 0U;
            break;
    }

    return freq / ((CLKCTL0->MAINCLKDIV & CLKCTL0_MAINCLKDIV_DIV_MASK) + 1U);
}

uint32_t CLOCK_GetHifi4ClkFreq(void)
{
    uint32_t freq = 0U;

    if ((CLKCTL0->DSPCPUCLKSEL & CLKCTL0_DSPCPUCLKSEL_SEL_EN_MASK) != 0U)
    {
        switch ((CLKCTL0->DSPCPUCLKSEL) & CLKCTL0_DSPCPUCLKSEL_SEL_MASK)
        {
            case CLKCTL0_DSPCPUCLKSEL_SEL(0):
                freq = CLOCK_GetComputeDspBaseClkFreq();
                break;

            case CLKCTL0_DSPCPUCLKSEL_SEL(1):
                freq = CLOCK_GetMainPfdFreq(kCLOCK_Pfd0);
                break;

            case CLKCTL0_DSPCPUCLKSEL_SEL(2):
                freq = CLOCK_GetFroClkFreq(0U);
                break;

            case CLKCTL0_DSPCPUCLKSEL_SEL(3):
                freq = CLOCK_GetMainPfdFreq(kCLOCK_Pfd1);
                break;

            default:
                freq = 0U;
                break;
        }
    }

    return freq / ((CLKCTL0->DSPCPUCLKDIV & CLKCTL0_DSPCPUCLKDIV_DIV_MASK) + 1U);
}

uint32_t CLOCK_GetSenseBaseClkFreq(void)
{
    uint32_t freq   = 0U;
    uint32_t clkSel = 0U;
    clkSel          = CLKCTL3->SENSEBASECLKSEL & CLKCTL3_SENSEBASECLKSEL_SEL_MASK;

    /* Read again to avoid glitch. */
    if (clkSel == (CLKCTL3->SENSEBASECLKSEL & CLKCTL3_SENSEBASECLKSEL_SEL_MASK))
    {
        switch (clkSel)
        {
            case CLKCTL3_SENSEBASECLKSEL_SEL(0U):
                freq = CLOCK_GetFroClkFreq(1U) / 3U;
                break;
            case CLKCTL3_SENSEBASECLKSEL_SEL(1U):
                freq = CLOCK_GetFroClkFreq(1U);
                break;
            case CLKCTL3_SENSEBASECLKSEL_SEL(2U):
                freq = CLOCK_GetFroClkFreq(2U) / 3U;
                break;
            case CLKCTL3_SENSEBASECLKSEL_SEL(3U):
                freq = CLOCK_GetLpOscFreq();
                break;
            default:
                freq = 0U;
                break;
        }
    }

    return freq;
}

#endif /* FSL_CLOCK_DRIVER_COMPUTE */

#if defined(FSL_CLOCK_DRIVER_SENSE)
/*! @brief  Get Sense base clock frequency. */
uint32_t CLOCK_GetSenseBaseClkFreq(void)
{
    uint32_t freq   = 0U;
    uint32_t clkSel = 0U;
    clkSel          = CLKCTL1->SENSEBASECLKSEL & CLKCTL1_SENSEBASECLKSEL_SEL_MASK;

    switch (clkSel)
    {
        case CLKCTL1_SENSEBASECLKSEL_SEL(0U):
            freq = CLOCK_GetFroClkFreq(1U) / 3U;
            break;
        case CLKCTL1_SENSEBASECLKSEL_SEL(1U):
            freq = CLOCK_GetFroClkFreq(1U);
            break;
        case CLKCTL1_SENSEBASECLKSEL_SEL(2U):
            freq = CLOCK_GetFroClkFreq(2U) / 3U;
            break;
        case CLKCTL1_SENSEBASECLKSEL_SEL(3U):
            freq = CLOCK_GetLpOscFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

uint32_t CLOCK_GetHifi1ClkFreq(void)
{
    uint32_t freq = 0U;

    if ((CLKCTL1->SENSEDSPCPUCLKSEL & CLKCTL1_SENSEDSPCPUCLKSEL_SEL_EN_MASK) != 0U)
    {
        switch ((CLKCTL1->SENSEDSPCPUCLKSEL) & CLKCTL1_SENSEDSPCPUCLKSEL_SEL_MASK)
        {
            case CLKCTL1_SENSEDSPCPUCLKSEL_SEL(0):
                freq = CLOCK_GetSenseBaseClkFreq();
                break;

            case CLKCTL1_SENSEDSPCPUCLKSEL_SEL(1):
                freq = CLOCK_GetFroClkFreq(2U);
                break;

            case CLKCTL1_SENSEDSPCPUCLKSEL_SEL(2):
                freq = CLOCK_GetAudioPfdFreq(kCLOCK_Pfd1);
                break;

            case CLKCTL1_SENSEDSPCPUCLKSEL_SEL(3):
                freq = CLOCK_GetFroClkFreq(1U);
                break;

            default:
                freq = 0U;
                break;
        }
    }

    return freq / ((CLKCTL1->SENSEDSPCPUCLKDIV & CLKCTL1_SENSEDSPCPUCLKDIV_DIV_MASK) + 1U);
}

uint32_t CLOCK_GetSenseAudioClkFreq(void)
{
    uint32_t freq = 0U;

    switch (CLKCTL1->AUDIOVDD1CLKSEL & CLKCTL1_AUDIOVDD1CLKSEL_SEL_MASK)
    {
        case CLKCTL1_AUDIOVDD1CLKSEL_SEL(0U):
            freq = CLOCK_GetMclkInClkFreq();
            break;
        case CLKCTL1_AUDIOVDD1CLKSEL_SEL(1U):
            freq = CLOCK_GetXtalInClkFreq();
            break;
        case CLKCTL1_AUDIOVDD1CLKSEL_SEL(2U):
            freq = CLOCK_GetFroClkFreq(2U) / 8U;
            break;
        case CLKCTL1_AUDIOVDD1CLKSEL_SEL(3U):
            freq = CLOCK_GetAudioPfdFreq(kCLOCK_Pfd3);
            break;
        default:
            freq = 0U;
            break;
    }

    return freq;
}

#endif /* FSL_CLOCK_DRIVER_SENSE */

uint32_t CLOCK_GetSenseMainClkFreq(void)
{
    uint32_t freq = 0U;

    switch ((CLKCTL3->MAINCLKSEL) & CLKCTL3_MAINCLKSEL_SEL_MASK)
    {
        case CLKCTL3_MAINCLKSEL_SEL(0):
            freq = CLOCK_GetSenseBaseClkFreq();
            break;

        case CLKCTL3_MAINCLKSEL_SEL(1):
            freq = CLOCK_GetFroClkFreq(2U);
            break;

        case CLKCTL3_MAINCLKSEL_SEL(2):
            freq = CLOCK_GetAudioPfdFreq(kCLOCK_Pfd3);
            break;

        case CLKCTL3_MAINCLKSEL_SEL(3):
            freq = CLOCK_GetFroClkFreq(1U);
            break;

        default:
            freq = 0U;
            break;
    }

    return freq / ((CLKCTL3->SENSEMAINCLKDIV & CLKCTL3_SENSEMAINCLKDIV_DIV_MASK) + 1U);
}

uint32_t CLOCK_GetVdd2MediaBaseClkFreq(void)
{
    uint32_t freq = 0U;

    switch ((CLKCTL4->MD2BASECLKSEL) & CLKCTL4_MD2BASECLKSEL_SEL_MASK)
    {
        case CLKCTL4_MD2BASECLKSEL_SEL(0):
            freq = CLOCK_GetFroClkFreq(1U) / 3U;
            break;

        case CLKCTL4_MD2BASECLKSEL_SEL(1):
            freq = CLOCK_GetFroClkFreq(1U);
            break;

        case CLKCTL4_MD2BASECLKSEL_SEL(2):
            freq = CLOCK_GetFroClkFreq(0U) / 3U;
            break;

        case CLKCTL4_MD2BASECLKSEL_SEL(3):
            freq = CLOCK_GetLpOscFreq();
            break;

        default:
            freq = 0U;
            break;
    }

    return freq;
}

uint32_t CLOCK_GetVddnMediaBaseClkFreq(void)
{
    uint32_t freq = 0U;

    switch ((CLKCTL4->MDNBASECLKSEL) & CLKCTL4_MDNBASECLKSEL_SEL_MASK)
    {
        case CLKCTL4_MDNBASECLKSEL_SEL(0):
            freq = CLOCK_GetFroClkFreq(1U) / 3U;
            break;

        case CLKCTL4_MDNBASECLKSEL_SEL(1):
            freq = CLOCK_GetFroClkFreq(1U);
            break;

        case CLKCTL4_MDNBASECLKSEL_SEL(2):
            freq = CLOCK_GetFroClkFreq(0U) / 3U;
            break;

        case CLKCTL4_MDNBASECLKSEL_SEL(3):
            freq = CLOCK_GetLpOscFreq();
            break;

        default:
            freq = 0U;
            break;
    }

    return freq;
}

uint32_t CLOCK_GetMediaMainClkFreq(void)
{
    uint32_t freq = 0U;

    switch ((CLKCTL4->MEDIAMAINCLKSEL) & CLKCTL4_MEDIAMAINCLKSEL_SEL_MASK)
    {
        case CLKCTL4_MEDIAMAINCLKSEL_SEL(0):
            freq = CLOCK_GetVdd2MediaBaseClkFreq();
            break;

        case CLKCTL4_MEDIAMAINCLKSEL_SEL(1):
            freq = CLOCK_GetMainPfdFreq(kCLOCK_Pfd0);
            break;

        case CLKCTL4_MEDIAMAINCLKSEL_SEL(2):
            freq = CLOCK_GetFroClkFreq(0U);
            break;

        case CLKCTL4_MEDIAMAINCLKSEL_SEL(3):
            freq = CLOCK_GetMainPfdFreq(kCLOCK_Pfd2);
            break;

        default:
            freq = 0U;
            break;
    }

    return freq / ((CLKCTL4->MEDIAMAINCLKDIV & CLKCTL4_MEDIAMAINCLKDIV_DIV_MASK) + 1U);
}

uint32_t CLOCK_GetMediaVddnClkFreq(void)
{
    uint32_t freq = 0U;

    switch ((CLKCTL4->MEDIAVDDNCLKSEL) & CLKCTL4_MEDIAVDDNCLKSEL_SEL_MASK)
    {
        case CLKCTL4_MEDIAVDDNCLKSEL_SEL(0):
            freq = CLOCK_GetVddnMediaBaseClkFreq();
            break;

        case CLKCTL4_MEDIAVDDNCLKSEL_SEL(1):
            freq = CLOCK_GetMainPfdFreq(kCLOCK_Pfd0);
            break;

        case CLKCTL4_MEDIAVDDNCLKSEL_SEL(2):
            freq = CLOCK_GetFroClkFreq(0U);
            break;

        case CLKCTL4_MEDIAVDDNCLKSEL_SEL(3):
            freq = CLOCK_GetMainPfdFreq(kCLOCK_Pfd2);
            break;

        default:
            freq = 0U;
            break;
    }

    return freq / ((CLKCTL4->MEDIAVDDNCLKDIV & CLKCTL4_MEDIAVDDNCLKDIV_DIV_MASK) + 1U);
}

/*! @brief  Enable/Disable FRO2 clock output. */
void CLOCK_EnableFro2ClkForDomain(uint32_t domainEnable)
{
    if (domainEnable != 0U)
    {
        /* Wait FRO stable first in case FRO just get powered on. */
        while ((CLKCTL3->FRO2CLKSTATUS & CLKCTL3_FRO2CLKSTATUS_CLK_OK_MASK) == 0U)
        {
        }
    }
    else
    {
        /* Do nothing */
    }
    CLKCTL3->FRO2MAXDOMAINEN = domainEnable & (uint32_t)kCLOCK_AllDomainEnable;
}

void CLOCK_EnableMainPllPfdClkForDomain(clock_pfd_t pfd, uint32_t domainEnable)
{
    uint32_t pfdIndex = (uint32_t)pfd;
    uint32_t pfdValue;

    pfdValue = CLKCTL2->MAINPLL0PFDDOMAINEN & (~(0x7FUL << (8UL * pfdIndex)));

    CLKCTL2->MAINPLL0PFDDOMAINEN = pfdValue | ((domainEnable & (uint32_t)kCLOCK_AllDomainEnable) << (8UL * pfdIndex));
}

void CLOCK_EnableAudioPllPfdClkForDomain(clock_pfd_t pfd, uint32_t domainEnable)
{
    uint32_t pfdIndex = (uint32_t)pfd;
    uint32_t pfdValue;

    pfdValue = CLKCTL2->AUDIOPLL0PFDDOMAINEN & (~(0x7FUL << (8UL * pfdIndex)));

    CLKCTL2->AUDIOPLL0PFDDOMAINEN = pfdValue | ((domainEnable & (uint32_t)kCLOCK_AllDomainEnable) << (8UL * pfdIndex));
}

void CLOCK_EnableAudioPllVcoClkForDomain(uint32_t domainEnable)
{
    CLKCTL2->AUDIOPLL0VCODOMAINEN = domainEnable & (uint32_t)kCLOCK_AllDomainEnable;
}

/* Get LP_FLEXCOMM Clk */
/*! brief  Return Frequency of LP_Flexcomm functional Clock
 *  param   id    : flexcomm index to get frequency.
 *  return Frequency of Flexcomm functional Clock
 */
uint32_t CLOCK_GetLPFlexCommClkFreq(uint32_t id)
{
    uint32_t freq      = 0U;
    uint32_t fcFclkSel = 0U;
    uint32_t clkSel    = 0U;

#if defined(FSL_CLOCK_DRIVER_COMPUTE)
    assert(id <= 13U);

    fcFclkSel = CLKCTL0->FLEXCOMM[id].FCFCLKSEL;

    if ((fcFclkSel & CLKCTL0_FCFCLKSEL_SEL_EN_MASK) == CLKCTL0_FCFCLKSEL_SEL_EN_MASK)
    {
        clkSel = (fcFclkSel & CLKCTL0_FCFCLKSEL_SEL_MASK) >> CLKCTL0_FCFCLKSEL_SEL_SHIFT;
        freq   = CLOCK_GetFCClkFreq(clkSel);
    }
    else
    {
        freq = 0U;
    }
#else
    assert((id <= 20U) && (id >= 17U));

    fcFclkSel = CLKCTL1->FLEXCOMM[id - 17U].FCFCLKSEL;
    if ((fcFclkSel & CLKCTL1_FCFCLKSEL_SEL_EN_MASK) == CLKCTL1_FCFCLKSEL_SEL_EN_MASK)
    {
        clkSel = (fcFclkSel & CLKCTL1_FCFCLKSEL_SEL_MASK) >> CLKCTL1_FCFCLKSEL_SEL_SHIFT;
        switch (clkSel)
        {
            case 0U:
                freq = CLOCK_GetSenseBaseClkFreq() /
                       ((CLKCTL1->FLEXCOMM[id - 17U].FCFCLKDIV & CLKCTL1_FCFCLKDIV_DIV_MASK) + 1U);
                break;
            case 1U:
                freq = CLOCK_GetFroClkFreq(2U) /
                       ((CLKCTL1->FLEXCOMM[id - 17U].FCFCLKDIV & CLKCTL1_FCFCLKDIV_DIV_MASK) + 1U);
                break;
            case 2U:
                freq = CLOCK_GetFroClkFreq(1U) /
                       ((CLKCTL1->FLEXCOMM[id - 17U].FCFCLKDIV & CLKCTL1_FCFCLKDIV_DIV_MASK) + 1U);
                break;
            case 3U:
                freq = CLOCK_GetWakeClk32KFreq() /
                       ((CLKCTL1->FLEXCOMM[id - 17U].FCFCLKDIV & CLKCTL1_FCFCLKDIV_DIV_MASK) + 1U);
                break;
            default:
                freq = 0U;
                break;
        }
    }
    else
    {
        freq = 0U;
    }
#endif /* FSL_CLOCK_DRIVER_COMPUTE */
    return freq;
}

uint32_t CLOCK_GetMainPllFreq(void)
{
    uint32_t freq = 0U;
    uint64_t freqTmp;

    switch ((CLKCTL2->MAINPLL0CLKSEL) & CLKCTL2_MAINPLL0CLKSEL_SEL_MASK)
    {
        case CLKCTL2_MAINPLL0CLKSEL_SEL(0):
            freq = CLOCK_GetFroClkFreq(1U) / 8U;
            break;
        case CLKCTL2_MAINPLL0CLKSEL_SEL(1):
            freq = CLOCK_GetXtalInClkFreq();
            break;
        default:
            /* Added comments to prevent the violation of MISRA C-2012 rule. */
            break;
    }

    if (((CLKCTL2->MAINPLL0CTL0) & CLKCTL2_MAINPLL0CTL0_BYPASS_MASK) == 0U)
    {
        /* PLL output frequency = Fref * (DIV_SELECT + NUM/DENOM). */
        freqTmp = ((uint64_t)freq * ((uint64_t)(CLKCTL2->MAINPLL0NUM))) / ((uint64_t)(CLKCTL2->MAINPLL0DENOM));
        freq *= ((CLKCTL2->MAINPLL0CTL0) & CLKCTL2_MAINPLL0CTL0_MULT_MASK) >> CLKCTL2_MAINPLL0CTL0_MULT_SHIFT;
        freq += (uint32_t)freqTmp;
    }
    return freq;
}

uint32_t CLOCK_GetMainPfdFreq(clock_pfd_t pfd)
{
    uint32_t freq = CLOCK_GetMainPllFreq();

    if (((CLKCTL2->MAINPLL0CTL0) & CLKCTL2_MAINPLL0CTL0_BYPASS_MASK) == 0U)
    {
        switch (pfd)
        {
            case kCLOCK_Pfd0:
                freq = (uint32_t)((uint64_t)freq * 18ULL /
                                  ((CLKCTL2->MAINPLL0PFD & CLKCTL2_MAINPLL0PFD_PFD0_MASK) >>
                                   CLKCTL2_MAINPLL0PFD_PFD0_SHIFT));
                break;

            case kCLOCK_Pfd1:
                freq = (uint32_t)((uint64_t)freq * 18ULL /
                                  ((CLKCTL2->MAINPLL0PFD & CLKCTL2_MAINPLL0PFD_PFD1_MASK) >>
                                   CLKCTL2_MAINPLL0PFD_PFD1_SHIFT));
                break;

            case kCLOCK_Pfd2:
                freq = (uint32_t)((uint64_t)freq * 18ULL /
                                  ((CLKCTL2->MAINPLL0PFD & CLKCTL2_MAINPLL0PFD_PFD2_MASK) >>
                                   CLKCTL2_MAINPLL0PFD_PFD2_SHIFT));
                break;

            case kCLOCK_Pfd3:
                freq = (uint32_t)((uint64_t)freq * 18ULL /
                                  ((CLKCTL2->MAINPLL0PFD & CLKCTL2_MAINPLL0PFD_PFD3_MASK) >>
                                   CLKCTL2_MAINPLL0PFD_PFD3_SHIFT));
                break;

            default:
                freq = 0U;
                break;
        }
    }

    return freq;
}

uint32_t CLOCK_GetAudioPllFreq(void)
{
    uint32_t freq = 0U;
    uint64_t freqTmp;

    switch ((CLKCTL2->AUDIOPLL0CLKSEL) & CLKCTL2_AUDIOPLL0CLKSEL_SEL_MASK)
    {
        case CLKCTL2_AUDIOPLL0CLKSEL_SEL(0):
            freq = CLOCK_GetFroClkFreq(1U) / 8U;
            break;
        case CLKCTL2_AUDIOPLL0CLKSEL_SEL(1):
            freq = CLOCK_GetXtalInClkFreq();
            break;
        default:
            freq = 0U;
            break;
    }

    if (((CLKCTL2->AUDIOPLL0CTL0) & CLKCTL2_AUDIOPLL0CTL0_BYPASS_MASK) == 0UL)
    {
        /* PLL output frequency = Fref * (DIV_SELECT + NUM/DENOM). */
        freqTmp = ((uint64_t)freq * ((uint64_t)(CLKCTL2->AUDIOPLL0NUM))) / ((uint64_t)(CLKCTL2->AUDIOPLL0DENOM));
        freq *= ((CLKCTL2->AUDIOPLL0CTL0) & CLKCTL2_AUDIOPLL0CTL0_MULT_MASK) >> CLKCTL2_AUDIOPLL0CTL0_MULT_SHIFT;
        freq += (uint32_t)freqTmp;
    }
    return freq;
}

uint32_t CLOCK_GetAudioPfdFreq(clock_pfd_t pfd)
{
    uint32_t freq = CLOCK_GetAudioPllFreq();

    if (((CLKCTL2->AUDIOPLL0CTL0) & CLKCTL2_AUDIOPLL0CTL0_BYPASS_MASK) == 0UL)
    {
        switch (pfd)
        {
            case kCLOCK_Pfd0:
                freq = (uint32_t)((uint64_t)freq * 18ULL /
                                  ((CLKCTL2->AUDIOPLL0PFD & CLKCTL2_AUDIOPLL0PFD_PFD0_MASK) >>
                                   CLKCTL2_AUDIOPLL0PFD_PFD0_SHIFT));
                break;

            case kCLOCK_Pfd1:
                freq = (uint32_t)((uint64_t)freq * 18ULL /
                                  ((CLKCTL2->AUDIOPLL0PFD & CLKCTL2_AUDIOPLL0PFD_PFD1_MASK) >>
                                   CLKCTL2_AUDIOPLL0PFD_PFD1_SHIFT));
                break;

            case kCLOCK_Pfd2:
                freq = (uint32_t)((uint64_t)freq * 18ULL /
                                  ((CLKCTL2->AUDIOPLL0PFD & CLKCTL2_AUDIOPLL0PFD_PFD2_MASK) >>
                                   CLKCTL2_AUDIOPLL0PFD_PFD2_SHIFT));
                break;

            case kCLOCK_Pfd3:
                freq = (uint32_t)((uint64_t)freq * 18ULL /
                                  ((CLKCTL2->AUDIOPLL0PFD & CLKCTL2_AUDIOPLL0PFD_PFD3_MASK) >>
                                   CLKCTL2_AUDIOPLL0PFD_PFD3_SHIFT));
                break;

            default:
                freq = 0U;
                break;
        }
    }

    return freq;
}

uint32_t CLOCK_GetWakeClk32KFreq(void)
{
    uint32_t freq = 0U;
    switch (CLKCTL3->WAKE32KCLKSEL & CLKCTL3_WAKE32KCLKSEL_SEL_MASK)
    {
        case CLKCTL3_WAKE32KCLKSEL_SEL(0):
            freq = CLOCK_GetOsc32KFreq();
            break;
        case CLKCTL3_WAKE32KCLKSEL_SEL(1):
            freq = CLOCK_GetLpOscFreq();
            break;
        default:
            freq = 0U;
            break;
    }
    return freq / ((CLKCTL3->WAKE32KCLKDIV & CLKCTL3_WAKE32KCLKDIV_DIV_MASK) + 1U);
}

uint32_t CLOCK_GetXspiClkFreq(uint32_t id)
{
    uint32_t freq = 0U;

#if defined(FSL_CLOCK_DRIVER_COMPUTE)
    if (id == 0U)
    {
        if ((CLKCTL0->XSPI0FCLKSEL & CLKCTL0_XSPI0FCLKSEL_SEL_EN_MASK) != 0U)
        {
            switch (CLKCTL0->XSPI0FCLKSEL & CLKCTL0_XSPI0FCLKSEL_SEL_MASK)
            {
                case CLKCTL0_XSPI0FCLKSEL_SEL(0):
                    freq = CLOCK_GetVddnComBaseClkFreq();
                    break;
                case CLKCTL0_XSPI0FCLKSEL_SEL(1):
                    freq = CLOCK_GetAudioPfdFreq(kCLOCK_Pfd0);
                    break;
                case CLKCTL0_XSPI0FCLKSEL_SEL(2):
                    freq = CLOCK_GetFroClkFreq(0U);
                    break;
                case CLKCTL0_XSPI0FCLKSEL_SEL(3):
                    freq = CLOCK_GetMainPfdFreq(kCLOCK_Pfd1);
                    break;
                default:
                    /* Added comments to prevent the violation of MISRA C-2012 rule. */
                    break;
            }
            freq = freq / ((CLKCTL0->XSPI0FCLKDIV & CLKCTL0_XSPI0FCLKDIV_DIV_MASK) + 1U);
        }
        else
        {
            freq = 0U;
        }
    }
    else if (id == 1U)
    {
        if ((CLKCTL0->XSPI1FCLKSEL & CLKCTL0_XSPI1FCLKSEL_SEL_EN_MASK) != 0U)
        {
            switch (CLKCTL0->XSPI1FCLKSEL & CLKCTL0_XSPI1FCLKSEL_SEL_MASK)
            {
                case CLKCTL0_XSPI1FCLKSEL_SEL(0):
                    freq = CLOCK_GetVddnComBaseClkFreq();
                    break;
                case CLKCTL0_XSPI1FCLKSEL_SEL(1):
                    freq = CLOCK_GetAudioPfdFreq(kCLOCK_Pfd1);
                    break;
                case CLKCTL0_XSPI1FCLKSEL_SEL(2):
                    freq = CLOCK_GetFroClkFreq(0U);
                    break;
                case CLKCTL0_XSPI1FCLKSEL_SEL(3):
                    freq = CLOCK_GetMainPfdFreq(kCLOCK_Pfd2);
                    break;
                default:
                    /* Added comments to prevent the violation of MISRA C-2012 rule. */
                    break;
            }
            freq = freq / ((CLKCTL0->XSPI1FCLKDIV & CLKCTL0_XSPI1FCLKDIV_DIV_MASK) + 1U);
        }
        else
        {
            freq = 0U;
        }
    }
    else if (id == 2U)
#else
    if (id == 2U)
#endif /* FSL_CLOCK_DRIVER_COMPUTE */
    {
        if ((CLKCTL4->XSPI2FCLKSEL & CLKCTL4_XSPI2FCLKSEL_SEL_EN_MASK) != 0U)
        {
            switch (CLKCTL4->XSPI2FCLKSEL & CLKCTL4_XSPI2FCLKSEL_SEL_MASK)
            {
                case CLKCTL4_XSPI2FCLKSEL_SEL(0):
                    freq = CLOCK_GetVddnComBaseClkFreq();
                    break;
                case CLKCTL4_XSPI2FCLKSEL_SEL(1):
                    freq = CLOCK_GetAudioPfdFreq(kCLOCK_Pfd1);
                    break;
                case CLKCTL4_XSPI2FCLKSEL_SEL(2):
                    freq = CLOCK_GetFroClkFreq(0U);
                    break;
                case CLKCTL4_XSPI2FCLKSEL_SEL(3):
                    freq = CLOCK_GetMainPfdFreq(kCLOCK_Pfd3);
                    break;
                default:
                    freq = 0U;
                    break;
            }
            freq = freq / ((CLKCTL4->XSPI2FCLKDIV & CLKCTL4_XSPI2FCLKDIV_DIV_MASK) + 1U);
        }
        else
        {
            freq = 0U;
        }
    }
    else
    {
        freq = 0U;
    }

    return freq;
}

#if defined(FSL_CLOCK_DRIVER_COMPUTE)
uint32_t CLOCK_GetSctClkFreq(void)
{
    uint32_t freq = 0U;
    if ((CLKCTL0->SCTFCLKSEL & CLKCTL0_SCTFCLKSEL_SEL_EN_MASK) != 0U)
    {
        switch (CLKCTL0->SCTFCLKSEL & CLKCTL0_SCTFCLKSEL_SEL_MASK)
        {
            case CLKCTL0_SCTFCLKSEL_SEL(0):
                freq = CLOCK_GetComputeBaseClkFreq();
                break;
            case CLKCTL0_SCTFCLKSEL_SEL(1):
                freq = CLOCK_GetMainPfdFreq(kCLOCK_Pfd0);
                break;
            case CLKCTL0_SCTFCLKSEL_SEL(2):
                freq = CLOCK_GetFroClkFreq(0U);
                break;
            case CLKCTL0_SCTFCLKSEL_SEL(3):
                freq = CLOCK_GetFroClkFreq(0U) / 6U;
                break;
            default:
                freq = 0U;
                break;
        }
    }
    return freq / ((CLKCTL0->SCTFCLKDIV & CLKCTL0_SCTFCLKDIV_DIV_MASK) + 1U);
}

uint32_t CLOCK_GetUtickClkFreq(void)
{
    uint32_t freq = 0U;

    if ((CLKCTL0->UTICK0FCLKSEL & CLKCTL0_UTICK0FCLKSEL_SEL_EN_MASK) != 0U)
    {
        switch (CLKCTL0->UTICK0FCLKSEL & CLKCTL0_UTICK0FCLKSEL_SEL_MASK)
        {
            case CLKCTL0_UTICK0FCLKSEL_SEL(0):
                freq = CLOCK_GetComputeBaseClkFreq();
                break;
            case CLKCTL0_UTICK0FCLKSEL_SEL(1):
                freq = CLOCK_GetMainPfdFreq(kCLOCK_Pfd0);
                break;
            case CLKCTL0_UTICK0FCLKSEL_SEL(2):
                freq = CLOCK_GetFroClkFreq(0U);
                break;
            case CLKCTL0_UTICK0FCLKSEL_SEL(3):
                freq = CLOCK_GetFroClkFreq(1U) / 2U;
                break;
            default:
                freq = 0U;
                break;
        }
    }
    return freq / ((CLKCTL0->UTICK0FCLKDIV & CLKCTL0_UTICK0FCLKDIV_DIV_MASK) + 1U);
}

uint32_t CLOCK_GetWdtClkFreq(uint32_t id)
{
    uint32_t freq = 0U;

    if (id == 0U)
    {
        if ((CLKCTL0->WWDT0FCLKSEL & CLKCTL0_WWDT0FCLKSEL_SEL_EN_MASK) != 0U)
        {
            switch (CLKCTL0->WWDT0FCLKSEL & CLKCTL0_WWDT0FCLKSEL_SEL_MASK)
            {
                case CLKCTL0_WWDT0FCLKSEL_SEL(0):
                    freq = CLOCK_GetLpOscFreq();
                    break;
                default:
                    freq = 0U;
                    break;
            }
        }
    }
    else if (id == 1U)
    {
        if ((CLKCTL0->WWDT1FCLKSEL & CLKCTL0_WWDT1FCLKSEL_SEL_EN_MASK) != 0U)
        {
            switch (CLKCTL0->WWDT1FCLKSEL & CLKCTL0_WWDT1FCLKSEL_SEL_MASK)
            {
                case CLKCTL0_WWDT1FCLKSEL_SEL(0):
                    freq = CLOCK_GetLpOscFreq();
                    break;
                default:
                    freq = 0U;
                    break;
            }
        }
    }
    else
    {
        freq = 0U;
    }

    return freq;
}

uint32_t CLOCK_GetSystickClkFreq(void)
{
    uint32_t freq = 0U;

    if ((CLKCTL0->SYSTICKFCLKSEL & CLKCTL0_SYSTICKFCLKSEL_SEL_EN_MASK) != 0U)
    {
        switch (CLKCTL0->SYSTICKFCLKSEL & CLKCTL0_SYSTICKFCLKSEL_SEL_MASK)
        {
            case CLKCTL0_SYSTICKFCLKSEL_SEL(0):
                freq = CLOCK_GetComputeBaseClkFreq();
                break;
            case CLKCTL0_SYSTICKFCLKSEL_SEL(1):
                freq = CLOCK_GetLpOscFreq();
                break;
            case CLKCTL0_SYSTICKFCLKSEL_SEL(2):
                freq = CLOCK_GetWakeClk32KFreq();
                break;
            case CLKCTL0_SYSTICKFCLKSEL_SEL(3):
                freq = CLOCK_GetXtalInClkFreq();
                break;
            default:
                freq = 0U;
                break;
        }
    }
    return freq / ((CLKCTL0->SYSTICKFCLKDIV & CLKCTL0_SYSTICKFCLKDIV_DIV_MASK) + 1U);
}

uint32_t CLOCK_GetCTimerClkFreq(uint32_t id)
{
    uint32_t freq = 0U;

    if ((CLKCTL0->CTIMERFCLKSEL[id] & CLKCTL0_CTIMERFCLKSEL_SEL_EN_MASK) != 0U)
    {
        switch ((CLKCTL0->CTIMERFCLKSEL[id]) & CLKCTL0_CTIMERFCLKSEL_SEL_MASK)
        {
            case CLKCTL0_CTIMERFCLKSEL_SEL(0):
                freq = CLOCK_GetComputeBaseClkFreq();
                break;

            case CLKCTL0_CTIMERFCLKSEL_SEL(1):
                freq = CLOCK_GetComputeAudioClkFreq();
                break;

            case CLKCTL0_CTIMERFCLKSEL_SEL(2):
                freq = CLOCK_GetFroClkFreq(0U);
                break;

            case CLKCTL0_CTIMERFCLKSEL_SEL(3):
                freq = CLOCK_GetWakeClk32KFreq();
                break;

            default:
                freq = 0U;
                break;
        }
    }

    return freq / ((CLKCTL0->CTIMERCLKDIV[id] & CLKCTL0_CTIMERCLKDIV_DIV_MASK) + 1U);
}

uint32_t CLOCK_GetI3cClkFreq(void)
{
    uint32_t freq = 0U;

    if ((CLKCTL0->I3C01FCLKSEL & CLKCTL0_I3C01FCLKSEL_SEL_EN_MASK) != 0U)
    {
        switch ((CLKCTL0->I3C01FCLKSEL) & CLKCTL0_I3C01FCLKSEL_SEL_MASK)
        {
            case CLKCTL0_I3C01FCLKSEL_SEL(0):
                freq = CLOCK_GetComputeBaseClkFreq();
                break;

            case CLKCTL0_I3C01FCLKSEL_SEL(1):
                freq = CLOCK_GetFroClkFreq(0U);
                break;

            case CLKCTL0_I3C01FCLKSEL_SEL(2):
                freq = CLOCK_GetFroClkFreq(1U) / 8U;
                break;

            case CLKCTL0_I3C01FCLKSEL_SEL(3):
                freq = CLOCK_GetSysOscFreq();
                break;

            default:
                freq = 0U;
                break;
        }
    }

    return freq / ((CLKCTL0->I3C01FCLKDIV & CLKCTL0_I3C01FCLKDIV_DIV_MASK) + 1U);
}

uint32_t CLOCK_GetTrngClkFreq(void)
{
    uint32_t freq = 0U;

    if ((CLKCTL0->TRNGFCLKSEL & CLKCTL0_TRNGFCLKSEL_SEL_EN_MASK) != 0U)
    {
        switch ((CLKCTL0->TRNGFCLKSEL) & CLKCTL0_TRNGFCLKSEL_SEL_MASK)
        {
            case CLKCTL0_TRNGFCLKSEL_SEL(0):
                freq = CLOCK_GetComputeBaseClkFreq();
                break;

            case CLKCTL0_TRNGFCLKSEL_SEL(1):
                freq = CLOCK_GetFroClkFreq(1U) / 2U;
                break;

            case CLKCTL0_TRNGFCLKSEL_SEL(2):
                freq = CLOCK_GetFroClkFreq(1U) / 8U;
                break;

            case CLKCTL0_TRNGFCLKSEL_SEL(3):
                freq = CLOCK_GetFroClkFreq(1U) / 3U;
                break;

            default:
                freq = 0U;
                break;
        }
    }

    return freq / ((CLKCTL0->TRNGFCLKDIV & CLKCTL0_TRNGFCLKDIV_DIV_MASK) + 1U);
}

uint32_t CLOCK_GetTpiuClkFreq(void)
{
    uint32_t freq = 0U;

    if ((CLKCTL0->TPIUFCLKSEL & CLKCTL0_TPIUFCLKSEL_SEL_EN_MASK) != 0U)
    {
        switch ((CLKCTL0->TPIUFCLKSEL) & CLKCTL0_TPIUFCLKSEL_SEL_MASK)
        {
            case CLKCTL0_TPIUFCLKSEL_SEL(0):
                freq = CLOCK_GetComputeBaseClkFreq();
                break;

            case CLKCTL0_TPIUFCLKSEL_SEL(1):
                freq = CLOCK_GetMainPfdFreq(kCLOCK_Pfd0);
                break;

            case CLKCTL0_TPIUFCLKSEL_SEL(2):
                freq = CLOCK_GetFroClkFreq(0U);
                break;

            case CLKCTL0_TPIUFCLKSEL_SEL(3):
                freq = CLOCK_GetFroClkFreq(0U) / 6U;
                break;

            default:
                freq = 0U;
                break;
        }
    }

    return freq / ((CLKCTL0->TPIUCLKDIV & CLKCTL0_TPIUCLKDIV_DIV_MASK) + 1U);
}

uint32_t CLOCK_GetSaiClkFreq(void)
{
    uint32_t freq = 0U;

    if ((CLKCTL0->SAI012FCLKSEL & CLKCTL0_SAI012FCLKSEL_SEL_EN_MASK) != 0U)
    {
        switch ((CLKCTL0->SAI012FCLKSEL) & CLKCTL0_SAI012FCLKSEL_SEL_MASK)
        {
            case CLKCTL0_SAI012FCLKSEL_SEL(0):
                freq = CLOCK_GetComputeBaseClkFreq();
                break;

            case CLKCTL0_SAI012FCLKSEL_SEL(1):
                freq = CLOCK_GetFroClkFreq(2U) / 8U;
                break;

            case CLKCTL0_SAI012FCLKSEL_SEL(2):
                freq = CLOCK_GetFroClkFreq(0U);
                break;

            case CLKCTL0_SAI012FCLKSEL_SEL(3):
                freq = CLOCK_GetComputeAudioClkFreq();
                break;

            default:
                freq = 0U;
                break;
        }
    }

    return freq / ((CLKCTL0->SAI012CLKDIV & CLKCTL0_SAI012CLKDIV_DIV_MASK) + 1U);
}

uint32_t CLOCK_GetClockOutClkFreq(void)
{
    uint32_t freq = 0U;

    if ((CLKCTL0->CLKOUTCLKSEL & CLKCTL0_CLKOUTCLKSEL_SEL_EN_MASK) != 0U)
    {
        switch ((CLKCTL0->CLKOUTCLKSEL) & CLKCTL0_CLKOUTCLKSEL_SEL_MASK)
        {
            case CLKCTL0_CLKOUTCLKSEL_SEL(0):
                freq = CLOCK_GetVdd2ComBaseClkFreq();
                break;

            case CLKCTL0_CLKOUTCLKSEL_SEL(1):
                freq = CLOCK_GetMainPfdFreq(kCLOCK_Pfd0);
                break;

            case CLKCTL0_CLKOUTCLKSEL_SEL(2):
                freq = CLOCK_GetFroClkFreq(0U);
                break;

            case CLKCTL0_CLKOUTCLKSEL_SEL(3):
                freq = CLOCK_GetFroClkFreq(1U);
                break;

            default:
                freq = 0U;
                break;
        }
    }

    return freq / ((CLKCTL0->CLKOUTCLKDIV & CLKCTL0_CLKOUTCLKDIV_DIV_MASK) + 1U);
}
#else  /* Sense domain. */
uint32_t CLOCK_GetUtickClkFreq(void)
{
    uint32_t freq = 0U;

    if ((CLKCTL1->UTICK1FCLKSEL & CLKCTL1_UTICK1FCLKSEL_SEL_EN_MASK) != 0U)
    {
        switch (CLKCTL1->UTICK1FCLKSEL & CLKCTL1_UTICK1FCLKSEL_SEL_MASK)
        {
            case CLKCTL1_UTICK1FCLKSEL_SEL(0):
                freq = CLOCK_GetSenseBaseClkFreq();
                break;
            case CLKCTL1_UTICK1FCLKSEL_SEL(1):
                freq = CLOCK_GetLpOscFreq();
                break;
            case CLKCTL1_UTICK1FCLKSEL_SEL(2):
                freq = CLOCK_GetFroClkFreq(0U);
                break;
            case CLKCTL1_UTICK1FCLKSEL_SEL(3):
                freq = CLOCK_GetFroClkFreq(1U) / 2U;
                break;
            default:
                freq = 0U;
                break;
        }
    }
    return freq / ((CLKCTL1->UTICK1CLKDIV & CLKCTL1_UTICK1CLKDIV_DIV_MASK) + 1U);
}

uint32_t CLOCK_GetWdtClkFreq(uint32_t id)
{
    uint32_t freq = 0U;

    if (id == 2U)
    {
        if ((CLKCTL1->WWDT2FCLKSEL & CLKCTL1_WWDT2FCLKSEL_SEL_EN_MASK) != 0U)
        {
            switch (CLKCTL1->WWDT2FCLKSEL & CLKCTL1_WWDT2FCLKSEL_SEL_MASK)
            {
                case CLKCTL1_WWDT2FCLKSEL_SEL(0):
                    freq = CLOCK_GetLpOscFreq();
                    break;
                default:
                    freq = 0U;
                    break;
            }
        }
    }
    else if (id == 3U)
    {
        if ((CLKCTL1->WWDT3FCLKSEL & CLKCTL1_WWDT3FCLKSEL_SEL_EN_MASK) != 0U)
        {
            switch (CLKCTL1->WWDT3FCLKSEL & CLKCTL1_WWDT3FCLKSEL_SEL_MASK)
            {
                case CLKCTL1_WWDT3FCLKSEL_SEL(0):
                    freq = CLOCK_GetLpOscFreq();
                    break;
                default:
                    freq = 0U;
                    break;
            }
        }
    }

    else
    {
        freq = 0U;
    }

    return freq;
}

uint32_t CLOCK_GetSystickClkFreq(void)
{
    uint32_t freq = 0U;

    if ((CLKCTL1->SYSTICKFCLKSEL & CLKCTL1_SYSTICKFCLKSEL_SEL_EN_MASK) != 0U)
    {
        switch (CLKCTL1->SYSTICKFCLKSEL & CLKCTL1_SYSTICKFCLKSEL_SEL_MASK)
        {
            case CLKCTL1_SYSTICKFCLKSEL_SEL(0):
                freq = CLOCK_GetSenseBaseClkFreq();
                break;
            case CLKCTL1_SYSTICKFCLKSEL_SEL(1):
                freq = CLOCK_GetLpOscFreq();
                break;
            case CLKCTL1_SYSTICKFCLKSEL_SEL(2):
                freq = CLOCK_GetWakeClk32KFreq();
                break;
            case CLKCTL1_SYSTICKFCLKSEL_SEL(3):
                freq = CLOCK_GetXtalInClkFreq();
                break;
            default:
                freq = 0U;
                break;
        }
    }
    return freq / ((CLKCTL1->SYSTICKFCLKDIV & CLKCTL1_SYSTICKFCLKDIV_DIV_MASK) + 1U);
}

uint32_t CLOCK_GetCTimerClkFreq(uint32_t id)
{
    uint32_t freq = 0U;
    assert(id >= 5U);

    if ((CLKCTL1->CTIMERFCLKSEL[id - 5U] & CLKCTL1_CTIMERFCLKSEL_SEL_EN_MASK) != 0U)
    {
        switch ((CLKCTL1->CTIMERFCLKSEL[id - 5U]) & CLKCTL1_CTIMERFCLKSEL_SEL_MASK)
        {
            case CLKCTL1_CTIMERFCLKSEL_SEL(0):
                freq = CLOCK_GetSenseBaseClkFreq();
                break;

            case CLKCTL1_CTIMERFCLKSEL_SEL(1):
                freq = CLOCK_GetSenseAudioClkFreq();
                break;

            case CLKCTL1_CTIMERFCLKSEL_SEL(2):
                freq = CLOCK_GetFroClkFreq(2U);
                break;

            case CLKCTL1_CTIMERFCLKSEL_SEL(3):
                freq = CLOCK_GetWakeClk32KFreq();
                break;

            default:
                freq = 0U;
                break;
        }
        freq = freq / ((CLKCTL1->CTIMERCLKDIV[id - 5U] & CLKCTL1_CTIMERCLKDIV_DIV_MASK) + 1U);
    }

    return freq;
}

uint32_t CLOCK_GetI3cClkFreq(void)
{
    uint32_t freq = 0U;

    if ((CLKCTL1->I3C23FCLKSEL & CLKCTL1_I3C23FCLKSEL_SEL_EN_MASK) != 0U)
    {
        switch ((CLKCTL1->I3C23FCLKSEL) & CLKCTL1_I3C23FCLKSEL_SEL_MASK)
        {
            case CLKCTL1_I3C23FCLKSEL_SEL(0):
                freq = CLOCK_GetSenseBaseClkFreq();
                break;

            case CLKCTL1_I3C23FCLKSEL_SEL(1):
                freq = CLOCK_GetFroClkFreq(2U);
                break;

            case CLKCTL1_I3C23FCLKSEL_SEL(2):
                freq = CLOCK_GetFroClkFreq(1U) / 8U;
                break;

            case CLKCTL1_I3C23FCLKSEL_SEL(3):
                freq = CLOCK_GetXtalInClkFreq();
                break;

            default:
                freq = 0U;
                break;
        }
    }

    return freq / ((CLKCTL1->I3C23FCLKDIV & CLKCTL1_I3C23FCLKDIV_DIV_MASK) + 1U);
}

uint32_t CLOCK_GetSaiClkFreq(void)
{
    uint32_t freq = 0U;

    if ((CLKCTL1->SAI3FCLKSEL & CLKCTL1_SAI3FCLKSEL_SEL_EN_MASK) != 0U)
    {
        switch ((CLKCTL1->SAI3FCLKSEL) & CLKCTL1_SAI3FCLKSEL_SEL_MASK)
        {
            case CLKCTL1_SAI3FCLKSEL_SEL(0):
                freq = CLOCK_GetSenseBaseClkFreq();
                break;

            case CLKCTL1_SAI3FCLKSEL_SEL(1):
                freq = CLOCK_GetFroClkFreq(2U) / 8U;
                break;

            case CLKCTL1_SAI3FCLKSEL_SEL(2):
                freq = CLOCK_GetFroClkFreq(2U);
                break;

            case CLKCTL1_SAI3FCLKSEL_SEL(3):
                freq = CLOCK_GetSenseAudioClkFreq();
                break;

            default:
                freq = 0U;
                break;
        }
    }

    return freq / ((CLKCTL1->SAI3CLKDIV & CLKCTL1_SAI3CLKDIV_DIV_MASK) + 1U);
}

#endif /* FSL_CLOCK_DRIVER_COMPUTE */
uint32_t CLOCK_GetVdd1ClockOutClkFreq(void)
{
    uint32_t freq = 0U;

    if ((CLKCTL3->CLKOUTCLKSEL & CLKCTL3_CLKOUTCLKSEL_SEL_EN_MASK) != 0U)
    {
        switch ((CLKCTL3->CLKOUTCLKSEL) & CLKCTL3_CLKOUTCLKSEL_SEL_MASK)
        {
            case CLKCTL3_CLKOUTCLKSEL_SEL(0):
                freq = CLOCK_GetSenseBaseClkFreq();
                break;

            case CLKCTL3_CLKOUTCLKSEL_SEL(1):
                freq = CLOCK_GetMainPfdFreq(kCLOCK_Pfd0);
                break;

            case CLKCTL3_CLKOUTCLKSEL_SEL(2):
                freq = CLOCK_GetFroClkFreq(0U);
                break;

            case CLKCTL3_CLKOUTCLKSEL_SEL(3):
                freq = CLOCK_GetFroClkFreq(1U);
                break;

            default:
                freq = 0U;
                break;
        }
    }

    return freq / ((CLKCTL3->CLKOUTCLKDIV & CLKCTL3_CLKOUTCLKDIV_DIV_MASK) + 1U);
}

uint32_t CLOCK_GetAdcClkFreq(void)
{
    uint32_t freq = 0U;

    if ((CLKCTL3->SARADCFCLKSEL & CLKCTL3_SARADCFCLKSEL_SEL_EN_MASK) != 0U)
    {
        switch ((CLKCTL3->SARADCFCLKSEL) & CLKCTL3_SARADCFCLKSEL_SEL_MASK)
        {
            case CLKCTL3_SARADCFCLKSEL_SEL(0):
                freq = CLOCK_GetSenseBaseClkFreq();
                break;

            case CLKCTL3_SARADCFCLKSEL_SEL(1):
                freq = CLOCK_GetMainPfdFreq(kCLOCK_Pfd1);
                break;

            case CLKCTL3_SARADCFCLKSEL_SEL(2):
                freq = CLOCK_GetFroClkFreq(2U);
                break;

            case CLKCTL3_SARADCFCLKSEL_SEL(3):
                freq = CLOCK_GetXtalInClkFreq();
                break;

            default:
                freq = 0U;
                break;
        }
    }

    return freq / ((CLKCTL3->SARADCFCLKDIV & CLKCTL3_SARADCFCLKDIV_DIV_MASK) + 1U);
}

uint32_t CLOCK_GetAcmpClkFreq(void)
{
    return CLOCK_GetSenseMainClkFreq();
}

uint32_t CLOCK_GetUsbClkFreq(void)
{
    return CLOCK_GetMediaVddnClkFreq();
}

uint32_t CLOCK_GetSdAdcClkFreq(void)
{
    uint32_t freq = 0U;

    if ((CLKCTL3->SDADCFCLKSEL & CLKCTL3_SDADCFCLKSEL_SEL_EN_MASK) != 0U)
    {
        switch ((CLKCTL3->SDADCFCLKSEL) & CLKCTL3_SDADCFCLKSEL_SEL_MASK)
        {
            case CLKCTL3_SDADCFCLKSEL_SEL(0):
                freq = CLOCK_GetSenseBaseClkFreq();
                break;

            case CLKCTL3_SDADCFCLKSEL_SEL(1):
                freq = CLOCK_GetFroClkFreq(2) / 8U;
                break;

            case CLKCTL3_SDADCFCLKSEL_SEL(2):
                freq = CLOCK_GetAudioPllFreq();
                break;

            case CLKCTL3_SDADCFCLKSEL_SEL(3):
                freq = CLOCK_GetSenseAudioClkFreq();
                break;

            default:
                freq = 0U;
                break;
        }
    }

    return freq / ((CLKCTL3->SDADCFCLKDIV & CLKCTL3_SDADCFCLKDIV_DIV_MASK) + 1U);
}

uint32_t CLOCK_GetOSTimerClkFreq(void)
{
    uint32_t freq = 0U;

    if ((CLKCTL3->OSTIMERFCLKSEL & CLKCTL3_OSTIMERFCLKSEL_SEL_EN_MASK) != 0U)
    {
        switch ((CLKCTL3->OSTIMERFCLKSEL) & CLKCTL3_OSTIMERFCLKSEL_SEL_MASK)
        {
            case CLKCTL3_OSTIMERFCLKSEL_SEL(0):
                freq = CLOCK_GetSenseBaseClkFreq();
                break;

            case CLKCTL3_OSTIMERFCLKSEL_SEL(1):
                freq = CLOCK_GetWakeClk32KFreq();
                break;

            case CLKCTL3_OSTIMERFCLKSEL_SEL(2):
                freq = CLOCK_GetLpOscFreq();
                break;

            case CLKCTL3_OSTIMERFCLKSEL_SEL(3):
                freq = CLOCK_GetXtalInClkFreq();
                break;

            default:
                freq = 0U;
                break;
        }
    }

    return freq / ((CLKCTL3->OSTIMERFCLKDIV & CLKCTL3_OSTIMERFCLKDIV_DIV_MASK) + 1U);
}

uint32_t CLOCK_GetMicfilClkFreq(void)
{
    uint32_t freq = 0U;

    if ((CLKCTL3->MICFILFCLKSEL & CLKCTL3_MICFILFCLKSEL_SEL_EN_MASK) != 0U)
    {
        switch ((CLKCTL3->MICFILFCLKSEL) & CLKCTL3_MICFILFCLKSEL_SEL_MASK)
        {
            case CLKCTL3_MICFILFCLKSEL_SEL(0):
                freq = CLOCK_GetSenseBaseClkFreq();
                break;

            case CLKCTL3_MICFILFCLKSEL_SEL(1):
                freq = CLOCK_GetAudioPfdFreq(kCLOCK_Pfd3);
                break;

            case CLKCTL3_MICFILFCLKSEL_SEL(2):
                freq = CLOCK_GetFroClkFreq(2);
                break;

            case CLKCTL3_MICFILFCLKSEL_SEL(3):
                freq = CLOCK_GetSenseAudioClkFreq();
                break;

            default:
                freq = 0U;
                break;
        }
    }

    return freq / ((CLKCTL3->MICFILFCLKDIV & CLKCTL3_MICFILFCLKDIV_DIV_MASK) + 1U);
}

uint32_t CLOCK_GetFlexioClkFreq(void)
{
    uint32_t freq = 0U;

    if ((CLKCTL4->FLEXIOCLKSEL & CLKCTL4_FLEXIOCLKSEL_SEL_EN_MASK) != 0U)
    {
        switch ((CLKCTL4->FLEXIOCLKSEL) & CLKCTL4_FLEXIOCLKSEL_SEL_MASK)
        {
            case CLKCTL4_FLEXIOCLKSEL_SEL(0):
                freq = CLOCK_GetVdd2MediaBaseClkFreq();
                break;

            case CLKCTL4_FLEXIOCLKSEL_SEL(1):
                freq = CLOCK_GetFroClkFreq(0);
                break;

            case CLKCTL4_FLEXIOCLKSEL_SEL(2):
                freq = CLOCK_GetFroClkFreq(1);
                break;

            case CLKCTL4_FLEXIOCLKSEL_SEL(3):
                freq = CLOCK_GetMainPfdFreq(kCLOCK_Pfd3);
                break;

            default:
                freq = 0U;
                break;
        }
    }

    return freq / ((CLKCTL4->FLEXIOCLKDIV & CLKCTL4_FLEXIOCLKDIV_DIV_MASK) + 1U);
}

uint32_t CLOCK_GetLPSpiClkFreq(uint32_t id)
{
    uint32_t freq = 0U;

    if (id == 14U)
    {
        if ((CLKCTL4->LPSPI14CLKSEL & CLKCTL4_LPSPI14CLKSEL_SEL_EN_MASK) != 0U)
        {
            switch ((CLKCTL4->LPSPI14CLKSEL) & CLKCTL4_LPSPI14CLKSEL_SEL_MASK)
            {
                case CLKCTL4_LPSPI14CLKSEL_SEL(0):
                    freq = CLOCK_GetVdd2MediaBaseClkFreq();
                    break;

                case CLKCTL4_LPSPI14CLKSEL_SEL(1):
                    freq = CLOCK_GetFroClkFreq(0U);
                    break;

                case CLKCTL4_LPSPI14CLKSEL_SEL(2):
                    freq = CLOCK_GetMainPfdFreq(kCLOCK_Pfd0);
                    break;

                case CLKCTL4_LPSPI14CLKSEL_SEL(3):
                    freq = CLOCK_GetFroClkFreq(1U);
                    break;

                default:
                    freq = 0U;
                    break;
            }
        }

        freq = freq / ((CLKCTL4->LPSPI14CLKDIV & CLKCTL4_LPSPI14CLKDIV_DIV_MASK) + 1U);
    }
    else if (id == 16U)
    {
        if ((CLKCTL4->LPSPI16CLKSEL & CLKCTL4_LPSPI16CLKSEL_SEL_EN_MASK) != 0U)
        {
            switch ((CLKCTL4->LPSPI16CLKSEL) & CLKCTL4_LPSPI16CLKSEL_SEL_MASK)
            {
                case CLKCTL4_LPSPI16CLKSEL_SEL(0):
                    freq = CLOCK_GetVdd2MediaBaseClkFreq();
                    break;

                case CLKCTL4_LPSPI16CLKSEL_SEL(1):
                    freq = CLOCK_GetFroClkFreq(0U);
                    break;

                case CLKCTL4_LPSPI16CLKSEL_SEL(2):
                    freq = CLOCK_GetMainPfdFreq(kCLOCK_Pfd0);
                    break;

                case CLKCTL4_LPSPI16CLKSEL_SEL(3):
                    freq = CLOCK_GetFroClkFreq(1U);
                    break;

                default:
                    freq = 0U;
                    break;
            }
        }

        freq = freq / ((CLKCTL4->LPSPI16CLKDIV & CLKCTL4_LPSPI16CLKDIV_DIV_MASK) + 1U);
    }
    else
    {
        freq = CLOCK_GetLPFlexCommClkFreq(id);
    }

    return freq;
}

uint32_t CLOCK_GetLPI2cClkFreq(uint32_t id)
{
    uint32_t freq = 0U;

    if (id != 15U)
    {
        freq = CLOCK_GetLPFlexCommClkFreq(id);
    }
    else
    {
        if ((CLKCTL3->LPI2C15FCLKSEL & CLKCTL3_LPI2C15FCLKSEL_SEL_EN_MASK) != 0U)
        {
            switch ((CLKCTL3->LPI2C15FCLKSEL) & CLKCTL3_LPI2C15FCLKSEL_SEL_MASK)
            {
                case CLKCTL3_LPI2C15FCLKSEL_SEL(0):
                    freq = CLOCK_GetSenseBaseClkFreq();
                    break;

                case CLKCTL3_LPI2C15FCLKSEL_SEL(1):
                    freq = CLOCK_GetFroClkFreq(1U);
                    break;

                case CLKCTL3_LPI2C15FCLKSEL_SEL(2):
                    freq = CLOCK_GetFroClkFreq(1U) / 2U;
                    break;

                case CLKCTL3_LPI2C15FCLKSEL_SEL(3):
                    freq = CLOCK_GetFroClkFreq(2U);
                    break;

                default:
                    freq = 0U;
                    break;
            }
        }
        freq = freq / ((CLKCTL3->LPI2C15FCLKDIV & CLKCTL3_LPI2C15FCLKDIV_DIV_MASK) + 1U);
    }

    return freq;
}

uint32_t CLOCK_GetLcdifClkFreq(void)
{
    uint32_t freq = 0U;

    if ((CLKCTL4->LCDIFPIXELCLKSEL & CLKCTL4_LCDIFPIXELCLKSEL_SEL_EN_MASK) != 0U)
    {
        switch ((CLKCTL4->LCDIFPIXELCLKSEL) & CLKCTL4_LCDIFPIXELCLKSEL_SEL_MASK)
        {
            case CLKCTL4_LCDIFPIXELCLKSEL_SEL(0):
                freq = CLOCK_GetVdd2MediaBaseClkFreq();
                break;

            case CLKCTL4_LCDIFPIXELCLKSEL_SEL(1):
                freq = CLOCK_GetMainPfdFreq(kCLOCK_Pfd2);
                break;

            case CLKCTL4_LCDIFPIXELCLKSEL_SEL(2):
                freq = CLOCK_GetFroClkFreq(0U);
                break;

            case CLKCTL4_LCDIFPIXELCLKSEL_SEL(3):
                freq = CLOCK_GetAudioPfdFreq(kCLOCK_Pfd1);
                break;

            default:
                freq = 0U;
                break;
        }
    }

    return freq / ((CLKCTL4->LCDIFPIXELCLKDIV & CLKCTL4_LCDIFPIXELCLKDIV_DIV_MASK) + 1U);
}

uint32_t CLOCK_GetMipiDphyClkFreq(void)
{
    uint32_t freq = 0U;

    if ((CLKCTL4->DPHYCLKSEL & CLKCTL4_DPHYCLKSEL_SEL_EN_MASK) != 0U)
    {
        switch ((CLKCTL4->DPHYCLKSEL) & CLKCTL4_DPHYCLKSEL_SEL_MASK)
        {
            case CLKCTL4_DPHYCLKSEL_SEL(0):
                freq = CLOCK_GetVdd2MediaBaseClkFreq();
                break;

                /*Source select 1 is internal. */

            case CLKCTL4_DPHYCLKSEL_SEL(2):
                freq = CLOCK_GetFroClkFreq(0U);
                break;

            case CLKCTL4_DPHYCLKSEL_SEL(3):
                freq = CLOCK_GetAudioPfdFreq(kCLOCK_Pfd2);
                break;

            default:
                freq = 0U;
                break;
        }
    }

    return freq / ((CLKCTL4->DPHYCLKDIV & CLKCTL4_DPHYCLKDIV_DIV_MASK) + 1U);
}

uint32_t CLOCK_GetMipiDphyEscRxClkFreq(void)
{
    uint32_t freq = 0U;

    if ((CLKCTL4->DPHYESCCLKSEL & CLKCTL4_DPHYESCCLKSEL_SEL_EN_MASK) != 0U)
    {
        switch ((CLKCTL4->DPHYESCCLKSEL) & CLKCTL4_DPHYESCCLKSEL_SEL_MASK)
        {
            case CLKCTL4_DPHYESCCLKSEL_SEL(0):
                freq = CLOCK_GetVdd2MediaBaseClkFreq();
                break;

            case CLKCTL4_DPHYESCCLKSEL_SEL(1):
                freq = CLOCK_GetMainPfdFreq(kCLOCK_Pfd1);
                break;

            case CLKCTL4_DPHYESCCLKSEL_SEL(2):
                freq = CLOCK_GetFroClkFreq(0U);
                break;

            case CLKCTL4_DPHYESCCLKSEL_SEL(3):
                freq = CLOCK_GetAudioPfdFreq(kCLOCK_Pfd2);
                break;

            default:
                freq = 0U;
                break;
        }
    }

    return freq / ((CLKCTL4->DPHYESCRXCLKDIV & CLKCTL4_DPHYESCRXCLKDIV_DIV_MASK) + 1U);
}

uint32_t CLOCK_GetMipiDphyEscTxClkFreq(void)
{
    return CLOCK_GetMipiDphyEscRxClkFreq() / ((CLKCTL4->DPHYESCTXCLKDIV & CLKCTL4_DPHYESCTXCLKDIV_DIV_MASK) + 1U);
}

uint32_t CLOCK_GetUsdhcClkFreq(uint32_t id)
{
    uint32_t freq = 0U;

    if (id == 0U)
    {
        if ((CLKCTL4->SDIO0FCLKSEL & CLKCTL4_SDIO0FCLKSEL_SEL_EN_MASK) != 0U)
        {
            switch ((CLKCTL4->SDIO0FCLKSEL) & CLKCTL4_SDIO0FCLKSEL_SEL_MASK)
            {
                case CLKCTL4_SDIO0FCLKSEL_SEL(0):
                    freq = CLOCK_GetVddnMediaBaseClkFreq();
                    break;

                case CLKCTL4_SDIO0FCLKSEL_SEL(1):
                    freq = CLOCK_GetAudioPfdFreq(kCLOCK_Pfd0);
                    break;

                case CLKCTL4_SDIO0FCLKSEL_SEL(2):
                    freq = CLOCK_GetFroClkFreq(0U);
                    break;

                case CLKCTL4_SDIO0FCLKSEL_SEL(3):
                    freq = CLOCK_GetMainPfdFreq(kCLOCK_Pfd2);
                    break;

                default:
                    freq = 0U;
                    break;
            }
            freq = freq / ((CLKCTL4->SDIO0FCLKDIV & CLKCTL4_SDIO0FCLKDIV_DIV_MASK) + 1U);
        }
    }
    else if (id == 1U)
    {
        if ((CLKCTL4->SDIO1FCLKSEL & CLKCTL4_SDIO1FCLKSEL_SEL_EN_MASK) != 0U)
        {
            switch ((CLKCTL4->SDIO1FCLKSEL) & CLKCTL4_SDIO1FCLKSEL_SEL_MASK)
            {
                case CLKCTL4_SDIO1FCLKSEL_SEL(0):
                    freq = CLOCK_GetVddnMediaBaseClkFreq();
                    break;

                case CLKCTL4_SDIO1FCLKSEL_SEL(1):
                    freq = CLOCK_GetAudioPfdFreq(kCLOCK_Pfd0);
                    break;

                case CLKCTL4_SDIO1FCLKSEL_SEL(2):
                    freq = CLOCK_GetFroClkFreq(0U);
                    break;

                case CLKCTL4_SDIO1FCLKSEL_SEL(3):
                    freq = CLOCK_GetMainPfdFreq(kCLOCK_Pfd2);
                    break;

                default:
                    freq = 0U;
                    break;
            }
            freq = freq / ((CLKCTL4->SDIO1FCLKDIV & CLKCTL4_SDIO1FCLKDIV_DIV_MASK) + 1U);
        }
    }
    else
    {
        /* Nothing.*/
    }

    return freq;
}

uint32_t CLOCK_GetVgpuClkFreq(void)
{
    uint32_t freq = 0U;

    if ((CLKCTL4->VGPUCLKSEL & CLKCTL4_VGPUCLKSEL_SEL_EN_MASK) != 0U)
    {
        switch ((CLKCTL4->VGPUCLKSEL) & CLKCTL4_VGPUCLKSEL_SEL_MASK)
        {
            case CLKCTL4_VGPUCLKSEL_SEL(0):
                freq = CLOCK_GetVdd2MediaBaseClkFreq();
                break;

            case CLKCTL4_VGPUCLKSEL_SEL(1):
                freq = CLOCK_GetMainPfdFreq(kCLOCK_Pfd0);
                break;

            case CLKCTL4_VGPUCLKSEL_SEL(2):
                freq = CLOCK_GetFroClkFreq(0U);
                break;

            case CLKCTL4_VGPUCLKSEL_SEL(3):
                freq = CLOCK_GetMainPfdFreq(kCLOCK_Pfd2);
                break;

            default:
                freq = 0U;
                break;
        }
        freq = freq / ((CLKCTL4->VGPUCLKDIV & CLKCTL4_VGPUCLKDIV_DIV_MASK) + 1U);
    }
    return freq;
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
    bool retVal         = true;
    CLOCK_EnableClock(kCLOCK_Usb0);

    USBPHY->CTRL_CLR = USBPHY_CTRL_SFTRST_MASK;

    USBPHY->PLL_SIC_SET = (USBPHY_PLL_SIC_PLL_POWER(1) | USBPHY_PLL_SIC_PLL_REG_ENABLE_MASK);
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
            retVal = false;
            break;
        }
    }

    if (retVal)
    {
        USBPHY->PLL_SIC = (USBPHY->PLL_SIC & ~(USBPHY_PLL_SIC_PLL_DIV_SEL_MASK)) | phyPllDiv;

        USBPHY->PLL_SIC_CLR = USBPHY_PLL_SIC_PLL_BYPASS_MASK;
        USBPHY->PLL_SIC_SET = (USBPHY_PLL_SIC_PLL_EN_USB_CLKS_MASK);

        USBPHY->CTRL_CLR = USBPHY_CTRL_CLR_CLKGATE_MASK;

        while (0UL == (USBPHY->PLL_SIC & USBPHY_PLL_SIC_PLL_LOCK_MASK))
        {
        }
    }

    return true;
}

/*! brief Disable USB HS PHY PLL clock.
 *
 * This function disables USB HS PHY PLL clock.
 */
void CLOCK_DisableUsbhs0PhyPllClock(void)
{
    USBPHY->PLL_SIC_CLR = (USBPHY_PLL_SIC_PLL_EN_USB_CLKS_MASK);
    USBPHY->CTRL |= USBPHY_CTRL_CLKGATE_MASK; /* Set to 1U to gate clocks */
}
