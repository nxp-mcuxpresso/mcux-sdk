/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_common.h"
#include "fsl_power.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if defined(PMC0)                               /* Only PMC0 can power down DCDC, LDO. */
static power_vdd_src_t s_vddnSrc = kVddSrc_PMC; /* VDDN supply source, DCDC or PMIC. */
static power_vdd_src_t s_vdd1Src = kVddSrc_PMC;
static power_vdd_src_t s_vdd2Src = kVddSrc_PMC;

AT_QUICKACCESS_SECTION_DATA(static uint32_t lpReqConfig[5]);
AT_QUICKACCESS_SECTION_DATA(static bool xspiCacheEnabled);
#else
AT_QUICKACCESS_SECTION_DATA(static uint32_t lpReqConfig[4]);
#endif /* PMC0 */
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.power"
#endif
#define MEGA (1000000U)

#if defined(PMC0)
#define PMC      PMC0
#define SLEEPCON SLEEPCON0
#elif defined(PMC1)
#define PMC      PMC1
#define SLEEPCON SLEEPCON1
#else
#error "Unsupported header file"
#endif

#define PMC_PDRCFG_REG(x)         (*((volatile uint32_t *)((uint32_t)(&(PMC->PDRUNCFG0)) + ((x - 1U) << 2U))))
#define SLEEPCON_PDRCFGSET_REG(x) (*((volatile uint32_t *)((uint32_t)(&(SLEEPCON->RUNCFG_SET)) + ((x) << 2U))))
#define SLEEPCON_PDRCFGCLR_REG(x) (*((volatile uint32_t *)((uint32_t)(&(SLEEPCON->RUNCFG_CLR)) + ((x) << 2U))))

#define PMC_REG(off) (*((volatile uint32_t *)(void *)PMC + (off) / 4U))

#define LP_CTRL_REG(offset)        (*((volatile uint32_t *)((uint32_t)(&(SLEEPCON->SHA_MED_CCTRL0)) + ((offset) << 2U))))
#define LP_STATE_REG(offset)       (*((volatile uint32_t *)((uint32_t)(&(SLEEPCON->SHA_MED_CSTAT0)) + ((offset) << 2U))))
#define POWER_LP_REQ_TIMEOUT_COUNT (400U)

/* Get AFBB bits mask from body bias domain _body_bias_domain */
#define POWER_AFBB_BITS_MASK(x) (((x)&0x20000000u) << 2U | (((x)&0x05400000u) << 1U))

/* Each loop has 4 instructions.*/
#define US2LOOP(clk, x) ((clk / MEGA * x) >> 2U)

/* Calcuate the voltage in uV for given LVD register value. */
#define POWER_CALCULATE_LVD_VOLT_FROM_VALUE(x) (500000U + 10000U * (x))

#if defined(PMC0)
/* SLEEPCON SLEEPCFG0 */
#define SCFG0_DEEP_SLEEP                                                                                             \
    (SLEEPCON0_SLEEPCFG_COMP_MAINCLK_SHUTOFF_MASK | SLEEPCON0_SLEEPCFG_SENSEP_MAINCLK_SHUTOFF_MASK |                 \
     SLEEPCON0_SLEEPCFG_SENSES_MAINCLK_SHUTOFF_MASK | SLEEPCON0_SLEEPCFG_RAM0_CLK_SHUTOFF_MASK |                     \
     SLEEPCON0_SLEEPCFG_RAM1_CLK_SHUTOFF_MASK | SLEEPCON0_SLEEPCFG_COMN_MAINCLK_SHUTOFF_MASK |                       \
     SLEEPCON0_SLEEPCFG_MEDIA_MAINCLK_SHUTOFF_MASK | SLEEPCON0_SLEEPCFG_XTAL_PD_MASK |                               \
     SLEEPCON0_SLEEPCFG_FRO0_PD_MASK | SLEEPCON0_SLEEPCFG_FRO1_PD_MASK | SLEEPCON0_SLEEPCFG_FRO2_PD_MASK |           \
     SLEEPCON0_SLEEPCFG_LPOSC_PD_MASK | SLEEPCON0_SLEEPCFG_PLLANA_PD_MASK | SLEEPCON0_SLEEPCFG_PLLLDO_PD_MASK |      \
     SLEEPCON0_SLEEPCFG_AUDPLLANA_PD_MASK | SLEEPCON0_SLEEPCFG_AUDPLLLDO_PD_MASK | SLEEPCON0_SLEEPCFG_ADC0_PD_MASK | \
     SLEEPCON0_SLEEPCFG_FRO0_GATE_MASK | SLEEPCON0_SLEEPCFG_FRO2_GATE_MASK)

#define POWER_IS_XIP_XSPI0()                                                                  \
    ((((uint32_t)POWER_ApplyPD >= 0x28000000U) && ((uint32_t)POWER_ApplyPD < 0x30000000U)) || \
     (((uint32_t)POWER_ApplyPD >= 0x38000000U) && ((uint32_t)POWER_ApplyPD < 0x40000000U)))
#define POWER_IS_XIP_XSPI1()                                                                  \
    ((((uint32_t)POWER_ApplyPD >= 0x08000000U) && ((uint32_t)POWER_ApplyPD < 0x10000000U)) || \
     (((uint32_t)POWER_ApplyPD >= 0x18000000U) && ((uint32_t)POWER_ApplyPD < 0x20000000U)))

/* Mask used for low power request - ack handshake for modules with DMA HWWake function. */
#define PRIVATE_TCTRL_HWWAKE_MODULE_MASK0 (0x3FFFU) /* LP_FLEXCOMM0-13 Bus Low power request. */
#define PRIVATE_TSTAT_HWWAKE_MODULE_MASK0 (0x3FFFU)
#define PRIVATE_TCTRL_HWWAKE_MODULE_MASK1                                                  \
    (SLEEPCON0_PRIVATE_TCTRL2_SAI0_LPREQ_MASK | SLEEPCON0_PRIVATE_TCTRL2_SAI1_LPREQ_MASK | \
     SLEEPCON0_PRIVATE_TCTRL2_SAI2_LPREQ_MASK) /* SAI0-2 */
#define PRIVATE_TSTAT_HWWAKE_MODULE_MASK1                                                        \
    (SLEEPCON0_PRIVATE_TSTAT1_SAI0_LPACCEPT_MASK | SLEEPCON0_PRIVATE_TSTAT1_SAI1_LPACCEPT_MASK | \
     SLEEPCON0_PRIVATE_TSTAT1_SAI2_LPACCEPT_MASK)
#define PRIVATE_CONTROLLER_HWWAKE_MODULE_MASK \
    (SLEEPCON0_PRIVATE_CCTRL0_EDMA0_STOP_MASK | SLEEPCON0_PRIVATE_CCTRL0_EDMA1_STOP_MASK) /* DMA1, DMA0 */
#define SHA_MEDSEN_TSTAT_HWWAKE_MODULE_MASK                                                                 \
    (SLEEPCON0_SHA_MEDSEN_TSTAT0_FLEXIO_B_LPACCEPT_MASK | SLEEPCON0_SHA_MEDSEN_TSTAT0_MICFIL_STOPPED_MASK | \
     SLEEPCON0_SHA_MEDSEN_TSTAT0_LPSPI14_B_LPACCEPT_MASK | SLEEPCON0_SHA_MEDSEN_TSTAT0_LPSPI16_B_LPACCEPT_MASK)
#else

#define SCFG0_DEEP_SLEEP                                                                                            \
    (SLEEPCON1_SLEEPCFG_SENSEP_MAINCLK_SHUTOFF_MASK | SLEEPCON1_SLEEPCFG_SENSES_MAINCLK_SHUTOFF_MASK |              \
     SLEEPCON1_SLEEPCFG_RAM0_CLK_SHUTOFF_MASK | SLEEPCON1_SLEEPCFG_RAM1_CLK_SHUTOFF_MASK |                          \
     SLEEPCON1_SLEEPCFG_COMN_MAINCLK_SHUTOFF_MASK | SLEEPCON1_SLEEPCFG_MEDIA_MAINCLK_SHUTOFF_MASK |                 \
     SLEEPCON1_SLEEPCFG_XTAL_PD_MASK | SLEEPCON1_SLEEPCFG_FRO2_PD_MASK | SLEEPCON1_SLEEPCFG_LPOSC_PD_MASK |         \
     SLEEPCON1_SLEEPCFG_PLLANA_PD_MASK | SLEEPCON1_SLEEPCFG_PLLLDO_PD_MASK | SLEEPCON1_SLEEPCFG_AUDPLLANA_PD_MASK | \
     SLEEPCON1_SLEEPCFG_AUDPLLLDO_PD_MASK | SLEEPCON1_SLEEPCFG_ADC0_PD_MASK | SLEEPCON1_SLEEPCFG_FRO2_GATE_MASK)

/* Mask used for low power request - ack handshake for modules with DMA HWWake function. */
#define PRIVATE_TCTRL_HWWAKE_MODULE_MASK0                                                                          \
    (SLEEPCON1_PRIVATE_TCTRL0_LP_FLEXCOMM17__B_LPREQ_MASK | SLEEPCON1_PRIVATE_TCTRL0_LP_FLEXCOMM18__B_LPREQ_MASK | \
     SLEEPCON1_PRIVATE_TCTRL0_LP_FLEXCOMM19__B_LPREQ_MASK | SLEEPCON1_PRIVATE_TCTRL0_LP_FLEXCOMM20__B_LPREQ_MASK | \
     SLEEPCON1_PRIVATE_TCTRL0_SAI3_LPREQ_MASK)
#define PRIVATE_TSTAT_HWWAKE_MODULE_MASK0                                                                              \
    (SLEEPCON1_PRIVATE_TSTAT0_LP_FLEXCOMM17_B_LPACCEPT_MASK | SLEEPCON1_PRIVATE_TSTAT0_LP_FLEXCOMM18_B_LPACCEPT_MASK | \
     SLEEPCON1_PRIVATE_TSTAT0_LP_FLEXCOMM19_B_LPACCEPT_MASK | SLEEPCON1_PRIVATE_TSTAT0_LP_FLEXCOMM20_B_LPACCEPT_MASK | \
     SLEEPCON1_PRIVATE_TSTAT0_SAI3_LPACCEPT_MASK)
#define PRIVATE_CONTROLLER_HWWAKE_MODULE_MASK \
    (SLEEPCON1_PRIVATE_CCTRL0_EDMA3_STOP_MASK | SLEEPCON1_PRIVATE_CCTRL0_EDMA2_STOP_MASK) /* DMA3, DMA2 */
#define SHA_MEDSEN_TSTAT_HWWAKE_MODULE_MASK \
    (SLEEPCON1_SHA_MEDSEN_TSTAT0_FLEXIO_B_LPACCEPT_MASK | SLEEPCON1_SHA_MEDSEN_TSTAT0_MICFIL_STOP_MASK)
#endif
/* PMC PDSLEEPCFG0. Note, when V2COM_DSR other VDD2 and VDDN switches should be off.   */
#define PCFG0_DEEP_SLEEP                                                                             \
    (PMC_PDSLEEPCFG0_V2DSP_PD_MASK | PMC_PDSLEEPCFG0_V2MIPI_PD_MASK | PMC_PDSLEEPCFG0_DCDC_LP_MASK | \
     PMC_PDSLEEPCFG0_V2NMED_DSR_MASK | PMC_PDSLEEPCFG0_VNCOM_DSR_MASK)
#define PCFG0_DSR                                                                                         \
    (PMC_PDSLEEPCFG0_V2COMP_DSR_MASK | PMC_PDSLEEPCFG0_V2NMED_DSR_MASK | PMC_PDSLEEPCFG0_V2COM_DSR_MASK | \
     PMC_PDSLEEPCFG0_VNCOM_DSR_MASK)
#define PCFG1_DEEP_SLEEP                                                                              \
    (PMC_PDSLEEPCFG1_TEMP_PD_MASK | PMC_PDSLEEPCFG1_PMCREF_LP_MASK | PMC_PDSLEEPCFG1_HVD1V8_PD_MASK | \
     PMC_PDSLEEPCFG1_POR1_LP_MASK | PMC_PDSLEEPCFG1_LVD1_LP_MASK | PMC_PDSLEEPCFG1_HVD1_PD_MASK |     \
     PMC_PDSLEEPCFG1_AGDET1_PD_MASK | PMC_PDSLEEPCFG1_POR2_LP_MASK | PMC_PDSLEEPCFG1_LVD2_LP_MASK |   \
     PMC_PDSLEEPCFG1_HVD2_PD_MASK | PMC_PDSLEEPCFG1_AGDET2_PD_MASK | PMC_PDSLEEPCFG1_PORN_LP_MASK |   \
     PMC_PDSLEEPCFG1_LVDN_LP_MASK | PMC_PDSLEEPCFG1_HVDN_PD_MASK | PMC_PDSLEEPCFG1_OTP_PD_MASK |      \
     PMC_PDSLEEPCFG1_ROM_PD_MASK | PMC_PDSLEEPCFG1_SRAMSLEEP_MASK)
#define PCFG2_DEEP_SLEEP (0xFFFFFFFFU)
#define PCFG3_DEEP_SLEEP (0xFFFFFFFFU)
#define PCFG4_DEEP_SLEEP (0xFFFFFFFFU)
#define PCFG5_DEEP_SLEEP (0xFFFFFFFFU)

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief API to enable PDRUNCFG bit in the SLEEPCON and PMC. Note that enabling the bit powers down the peripheral
 *
 * @param en    peripheral for which to enable the PDRUNCFG bit
 * @return none
 */
void POWER_EnablePD(pd_bit_t en)
{
    assert(en != kPDRUNCFG_ForceUnsigned);

    if (GET_PD_REG_FROM_BITS(en) != 0U) /* PMC PDRUNCFG */
    {
        PMC_PDRCFG_REG(GET_PD_REG_FROM_BITS(en)) |= (1UL << (((uint32_t)en) & 0xFFU));
    }
    else /* SLEEPCON_RUNCFG */
    {
        SLEEPCON_PDRCFGSET_REG(GET_PD_REG_FROM_BITS(en)) = (1UL << (((uint32_t)en) & 0xFFU));
    }
}

/*!
 * @brief API to disable PDRUNCFG bit in the Sysctl0. Note that disabling the bit powers up the peripheral
 *
 * @param en    peripheral for which to disable the PDRUNCFG bit
 * @return none
 */
void POWER_DisablePD(pd_bit_t en)
{
    assert(en != kPDRUNCFG_ForceUnsigned);

    if (GET_PD_REG_FROM_BITS(en) != 0U) /* PMC PDRUNCFG */
    {
        PMC_PDRCFG_REG(GET_PD_REG_FROM_BITS(en)) &= ~(1UL << (((uint32_t)en) & 0xFFU));
    }
    else /* SLEEPCON_RUNCFG */
    {
        SLEEPCON_PDRCFGCLR_REG(GET_PD_REG_FROM_BITS(en)) = (1UL << (((uint32_t)en) & 0xFFU));
    }
}

/* Low power request and wait ACK. */
status_t POWER_ModuleEnterLPRequest(lp_bit_t en)
{
    uint32_t timeout = POWER_LP_REQ_TIMEOUT_COUNT;
    /* Assert low power request. */
    LP_CTRL_REG(GET_LP_CTRL_REG_FROM_BITS(en)) |= 1UL << (GET_LP_CTRL_BIT_FROM_BITS(en));

    /* Wait ACK. */
    while ((LP_STATE_REG(GET_LP_STATE_REG_FROM_BITS(en)) & (1UL << (GET_LP_STATE_BIT_FROM_BITS(en)))) == 0U)
    {
        timeout--;

        if (timeout == 0U)
        {
            return kStatus_Timeout;
        }
    }

    return kStatus_Success;
}

void POWER_ModuleExitLPRequest(lp_bit_t en)
{
    /* Clear low power request. */
    LP_CTRL_REG(GET_LP_CTRL_REG_FROM_BITS(en)) &= ~(1UL << (GET_LP_CTRL_BIT_FROM_BITS(en)));
}

/**
 * @brief  API to apply updated PMC PDRUNCFG bits in the Sysctl0.
 */
void POWER_ApplyPD(void)
{
    /* Cannot set APPLYCFG when BUSY is 1 */
    while ((PMC->STATUS & PMC_STATUS_BUSY_MASK) != 0U)
    {
    }
    PMC->CTRL |= PMC_CTRL_APPLYCFG_MASK;
    /* Wait all PMC finite state machines finished. */
    while ((PMC->STATUS & PMC_STATUS_BUSY_MASK) != 0U)
    {
    }
}

void POWER_SetPmicMode(uint32_t mode, pmic_mode_reg_t reg)
{
    __disable_irq();

    PMC_REG((uint32_t)reg) =
        (PMC_REG((uint32_t)reg) & ~PMC_PDSLEEPCFG0_PMICMODE_MASK) | (mode << PMC_PDSLEEPCFG0_PMICMODE_SHIFT);

    __enable_irq();
}

uint32_t POWER_GetPmicMode(pmic_mode_reg_t reg)
{
    uint32_t mode = (uint32_t)reg;

    return ((PMC_REG(mode) & PMC_PDSLEEPCFG0_PMICMODE_MASK) >> PMC_PDSLEEPCFG0_PMICMODE_SHIFT);
}

/**
 * @brief   Clears the PMC event flags state.
 * @param   statusMask : A bitmask of event flags that are to be cleared.
 */
void POWER_ClearEventFlags(uint32_t statusMask)
{
    PMC->FLAGS = statusMask;
}

/**
 * @brief   Get the PMC event flags state.
 * @return  PMC FLAGS register value
 */
uint32_t POWER_GetEventFlags(void)
{
    return PMC->FLAGS;
}

/**
 * @brief   Enable the PMC reset requests.
 * @param   resetMask : A bitmask of of resets to enable.
 */
void POWER_EnableResets(uint32_t resetMask)
{
    PMC->CTRL |= resetMask;
}

/**
 * @brief   Disable the PMC reset requests.
 * @param   resetMask : A bitmask of of resets to disable.
 */
void POWER_DisableResets(uint32_t resetMask)
{
    PMC->CTRL &= ~resetMask;
}

/**
 * @brief   Enable the PMC interrupt requests.
 * @param   interruptMask : A bitmask of of interrupts to enable.
 */
void POWER_EnableInterrupts(uint32_t interruptMask)
{
    PMC->INTRCTRL |= interruptMask;
}

void POWER_EnableDMAHWWake(uint32_t sources)
{
    SLEEPCON->HW_WAKE_SET = sources;
}

void POWER_DisableDMAHWWake(uint32_t sources)
{
    SLEEPCON->HW_WAKE_CLR = sources;
}

/**
 * @brief   Disable the PMC interrupt requests.
 * @param   interruptMask : A bitmask of of interrupts to disable.
 */
void POWER_DisableInterrupts(uint32_t interruptMask)
{
    PMC->INTRCTRL &= ~interruptMask;
}

void EnableDeepSleepIRQ(IRQn_Type interrupt)
{
    uint32_t intNumber = (uint32_t)interrupt;

#if defined(PMC0)
    if (intNumber >= 128U)
    {
        /* enable interrupt wake up in the WAKEUPEN4 register */
        SLEEPCON->WAKEUPEN4_SET = 1UL << (intNumber - 128U);
    }
    else if (intNumber >= 96U)
    {
        SLEEPCON->WAKEUPEN3_SET = 1UL << (intNumber - 96U);
    }
    else if (intNumber >= 64U)
#else  /* For sense domain */
    if (intNumber >= 64U)
#endif /* PMC0 */
    {
        SLEEPCON->WAKEUPEN2_SET = 1UL << (intNumber - 64U);
    }
    else if (intNumber >= 32U)
    {
        SLEEPCON->WAKEUPEN1_SET = 1UL << (intNumber - 32U);
    }
    else
    {
        SLEEPCON->WAKEUPEN0_SET = 1UL << intNumber;
    }
    /* also enable interrupt at NVIC */
    (void)EnableIRQ(interrupt);
}

void DisableDeepSleepIRQ(IRQn_Type interrupt)
{
    uint32_t intNumber = (uint32_t)interrupt;

    /* also disable interrupt at NVIC */
    (void)DisableIRQ(interrupt);

#if defined(PMC0)
    if (intNumber >= 128U)
    {
        /* enable interrupt wake up in the WAKEUPEN4 register */
        SLEEPCON->WAKEUPEN4_CLR = 1UL << (intNumber - 128U);
    }
    else if (intNumber >= 96U)
    {
        SLEEPCON->WAKEUPEN3_CLR = 1UL << (intNumber - 96U);
    }
    else if (intNumber >= 64U)
#else
    if (intNumber >= 64U)
#endif /* PMC0 */
    {
        SLEEPCON->WAKEUPEN2_CLR = 1UL << (intNumber - 64U);
    }
    else if (intNumber >= 32U)
    {
        SLEEPCON->WAKEUPEN1_CLR = 1UL << (intNumber - 32U);
    }
    else
    {
        SLEEPCON->WAKEUPEN0_CLR = 1UL << intNumber;
    }
}

void POWER_EnableLPRequestMask(uint32_t mask)
{
    SLEEPCON->SHARED_MASK0_SET |= mask;
}

void POWER_DisableLPRequestMask(uint32_t mask)
{
    SLEEPCON->SHARED_MASK0_CLR |= mask;
}

void POWER_EnterSleep(void)
{
    uint32_t pmsk;
    pmsk = __get_PRIMASK();
    __disable_irq();
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    __WFI();
    __set_PRIMASK(pmsk);
}

void POWER_EnableAutoWake(uint16_t ticks)
{
    PMC->WAKEUP = (PMC->WAKEUP & 0x3F000000U) | PMC_WAKEUP_WAKETIME(ticks); /* Don't clear the [WKSRCF] W1C bits! */
    PMC->INTRCTRL |= PMC_INTRCTRL_AUTOWKIE_MASK;
    EnableDeepSleepIRQ(PMC_IRQn);
}

void POWER_EnableRunAFBB(uint32_t mask)
{
    /* clear AFBBxxx_PD, set RBBxxx_PD. No AFBBSRAM1 bit. */
    PMC->PDRUNCFG0 &= ~POWER_AFBB_BITS_MASK(mask);
    PMC->PDRUNCFG0 |= mask;
}

void POWER_EnableRunRBB(uint32_t mask)
{
    PMC->PDRUNCFG0 &= ~mask; /* Clear RBB* bits, set AFBB* bits */
    PMC->PDRUNCFG0 |= POWER_AFBB_BITS_MASK(mask);
}

void POWER_EnableSleepRBB(uint32_t mask)
{
    /* Set AFBB bits, clear RBB bits. */
    PMC->PDSLEEPCFG0 &= ~mask;
    PMC->PDSLEEPCFG0 |= POWER_AFBB_BITS_MASK(mask);
}

void POWER_EnableRunNBB(uint32_t mask)
{
    /* Set AFBB and RBB bits. */
    PMC->PDRUNCFG0 |= mask | POWER_AFBB_BITS_MASK(mask);
}

void POWER_EnableSleepNBB(uint32_t mask)
{
    /* Set AFBB bits and RBB bits. */
    PMC->PDSLEEPCFG0 |= mask | POWER_AFBB_BITS_MASK(mask);
}

static uint32_t POWER_CalRegValueFromVolt(uint32_t volt, uint32_t base, uint32_t slope)
{
    uint32_t temp = 0U;
    temp          = volt - base - 1U; /* Rounding up.*/
    return (uint32_t)((temp + slope) / slope);
}

status_t POWER_ConfigRegulatorSetpoints(power_regulator_t regulator,
                                        const power_regulator_voltage_t *volt,
                                        const power_lvd_voltage_t *lvd)
{
    status_t ret = kStatus_Success;

#if defined(PMC0)
    if (regulator == kRegulator_DCDC) /* DCDC with 2 setpoints. */
    {
        if ((volt->DCDC.vsel1 < volt->DCDC.vsel0) || (lvd->VDDN.lvl1 < lvd->VDDN.lvl0) ||
            (volt->DCDC.vsel1 > 1150000U) || (volt->DCDC.vsel0 < 500000U))
        {
            ret = kStatus_InvalidArgument;
        }
        else
        {
            PMC->DCDCVSEL = PMC_DCDCVSEL_VSEL0(POWER_CalRegValueFromVolt(volt->DCDC.vsel0, 500000U, 6250U)) |
                            PMC_DCDCVSEL_VSEL1(POWER_CalRegValueFromVolt(volt->DCDC.vsel1, 500000U, 6250U));
            PMC->LVDVDDNCTRL = PMC_LVDVDDNCTRL_LVL0(POWER_CalRegValueFromVolt(lvd->VDDN.lvl0, 500000U, 10000U)) |
                               PMC_LVDVDDNCTRL_LVL1(POWER_CalRegValueFromVolt(lvd->VDDN.lvl1, 500000U, 10000U));
        }
    }
#else
    if (regulator != kRegulator_Vdd1LDO) /* Only VDD1 LDO configurable from Sense side. */
    {
        ret = kStatus_InvalidArgument;
    }
#endif   /* PMC0, only compute domain support DCDC, LDO VDD2 control. */
    else /* LDO with 4 setpoints. */
    {
        if ((volt->LDO.vsel3 < volt->LDO.vsel2) || (volt->LDO.vsel2 < volt->LDO.vsel1) ||
            (volt->LDO.vsel1 < volt->LDO.vsel0) || (lvd->VDD12.lvl3 < lvd->VDD12.lvl2) ||
            (lvd->VDD12.lvl2 < lvd->VDD12.lvl1) || (lvd->VDD12.lvl1 < lvd->VDD12.lvl0) ||
            (volt->LDO.vsel3 > 1150000U) || (volt->LDO.vsel0 < 450000U))
        {
            ret = kStatus_InvalidArgument;
        }
        else
        {
            PMC_REG(0x24U + 4U * ((uint32_t)regulator - 1U)) =
                PMC_LDOVDD1VSEL_VSEL0(POWER_CalRegValueFromVolt(volt->LDO.vsel0, 450000U, 12500U)) |
                PMC_LDOVDD1VSEL_VSEL1(POWER_CalRegValueFromVolt(volt->LDO.vsel1, 450000U, 12500U)) |
                PMC_LDOVDD1VSEL_VSEL2(POWER_CalRegValueFromVolt(volt->LDO.vsel2, 450000U, 12500U)) |
                PMC_LDOVDD1VSEL_VSEL3(POWER_CalRegValueFromVolt(volt->LDO.vsel3, 450000U, 12500U)); /* LDOVDDxVSEL */
            PMC_REG(0x30U + 4U * ((uint32_t)regulator - 1U)) =
                PMC_LVDVDD1CTRL_LVL0(POWER_CalRegValueFromVolt(lvd->VDD12.lvl0, 500000U, 10000U)) |
                PMC_LVDVDD1CTRL_LVL1(POWER_CalRegValueFromVolt(lvd->VDD12.lvl1, 500000U, 10000U)) |
                PMC_LVDVDD1CTRL_LVL2(POWER_CalRegValueFromVolt(lvd->VDD12.lvl2, 500000U, 10000U)) |
                PMC_LVDVDD1CTRL_LVL3(POWER_CalRegValueFromVolt(lvd->VDD12.lvl3, 500000U, 10000U)); /* LVDVDDxCTRL */
        }
    }

    return ret;
}

status_t POWER_ConfigLvdSetpoints(power_regulator_t regulator, const power_lvd_voltage_t *lvd)
{
    status_t ret = kStatus_Success;

#if defined(PMC0)
    if (regulator == kRegulator_DCDC) /* DCDC with 2 setpoints. */
    {
        if ((lvd->VDDN.lvl1 < lvd->VDDN.lvl0) || (lvd->VDDN.lvl0 < 500000U))
        {
            ret = kStatus_InvalidArgument;
        }
        else
        {
            PMC->LVDVDDNCTRL = PMC_LVDVDDNCTRL_LVL0(POWER_CalRegValueFromVolt(lvd->VDDN.lvl0, 500000U, 10000U)) |
                               PMC_LVDVDDNCTRL_LVL1(POWER_CalRegValueFromVolt(lvd->VDDN.lvl1, 500000U, 10000U));
        }
    }
#else
    if (regulator != kRegulator_Vdd1LDO) /* Only VDD1 LDO configurable from Sense side. */
    {
        ret = kStatus_InvalidArgument;
    }
#endif   /* PMC0, only compute domain support DCDC, LDO VDD2 control. */
    else /* LDO with 4 setpoints. */
    {
        if ((lvd->VDD12.lvl3 < lvd->VDD12.lvl2) || (lvd->VDD12.lvl2 < lvd->VDD12.lvl1) ||
            (lvd->VDD12.lvl1 < lvd->VDD12.lvl0) || (lvd->VDD12.lvl0 < 500000U))
        {
            ret = kStatus_InvalidArgument;
        }
        else
        {
            PMC_REG(0x30U + 4U * ((uint32_t)regulator - 1U)) =
                PMC_LVDVDD1CTRL_LVL0(POWER_CalRegValueFromVolt(lvd->VDD12.lvl0, 500000U, 10000U)) |
                PMC_LVDVDD1CTRL_LVL1(POWER_CalRegValueFromVolt(lvd->VDD12.lvl1, 500000U, 10000U)) |
                PMC_LVDVDD1CTRL_LVL2(POWER_CalRegValueFromVolt(lvd->VDD12.lvl2, 500000U, 10000U)) |
                PMC_LVDVDD1CTRL_LVL3(POWER_CalRegValueFromVolt(lvd->VDD12.lvl3, 500000U, 10000U)); /* LVDVDDxCTRL */
        }
    }

    return ret;
}

void POWER_GetLvdSetpoints(power_regulator_t regulator, power_lvd_voltage_t *lvd)
{
    uint32_t reg = 0U;

    (void)memset(lvd, 0, sizeof(power_lvd_voltage_t));

    if (regulator == kRegulator_DCDC) /* DCDC with 2 setpoints. */
    {
        reg = PMC->LVDVDDNCTRL;
        lvd->lvl[0] =
            POWER_CALCULATE_LVD_VOLT_FROM_VALUE((reg & PMC_LVDVDDNCTRL_LVL0_MASK) >> PMC_LVDVDDNCTRL_LVL0_SHIFT);
        lvd->lvl[1] =
            POWER_CALCULATE_LVD_VOLT_FROM_VALUE((reg & PMC_LVDVDDNCTRL_LVL1_MASK) >> PMC_LVDVDDNCTRL_LVL1_SHIFT);
    }
    else /* LDO with 4 setpoints. */
    {
        reg = PMC_REG(0x30U + 4U * ((uint32_t)regulator - 1U));

        lvd->VDD12.lvl0 =
            POWER_CALCULATE_LVD_VOLT_FROM_VALUE((reg & PMC_LVDVDD2CTRL_LVL0_MASK) >> PMC_LVDVDD2CTRL_LVL0_SHIFT);
        lvd->VDD12.lvl1 =
            POWER_CALCULATE_LVD_VOLT_FROM_VALUE((reg & PMC_LVDVDD2CTRL_LVL1_MASK) >> PMC_LVDVDD2CTRL_LVL1_SHIFT);
        lvd->VDD12.lvl2 =
            POWER_CALCULATE_LVD_VOLT_FROM_VALUE((reg & PMC_LVDVDD2CTRL_LVL2_MASK) >> PMC_LVDVDD2CTRL_LVL2_SHIFT);
        lvd->VDD12.lvl3 =
            POWER_CALCULATE_LVD_VOLT_FROM_VALUE((reg & PMC_LVDVDD2CTRL_LVL3_MASK) >> PMC_LVDVDD2CTRL_LVL3_SHIFT);
    }
}

void POWER_SelectRunSetpoint(power_regulator_t regulator, uint32_t setpoint)
{
    if (regulator == kRegulator_DCDC)
    {
        assert(setpoint < 2U);
        PMC->PDRUNCFG0 &= ~PMC_PDRUNCFG0_DCDC_VSEL_MASK;
        PMC->PDRUNCFG0 |= PMC_PDRUNCFG0_DCDC_VSEL(setpoint);
    }
    else if (regulator == kRegulator_Vdd2LDO)
    {
        assert(setpoint < 4U);
        PMC->PDRUNCFG0 &= ~PMC_PDRUNCFG0_LDO2_VSEL_MASK;
        PMC->PDRUNCFG0 |= PMC_PDRUNCFG0_LDO2_VSEL(setpoint);
    }
    else
    {
        assert(setpoint < 4U);
        PMC->PDRUNCFG0 &= ~PMC_PDRUNCFG0_LDO1_VSEL_MASK;
        PMC->PDRUNCFG0 |= PMC_PDRUNCFG0_LDO1_VSEL(setpoint);
    }
}

void POWER_SelectSleepSetpoint(power_regulator_t regulator, uint32_t setpoint)
{
    if (regulator == kRegulator_DCDC)
    {
        assert(setpoint < 2U);
        PMC->PDSLEEPCFG0 &= ~PMC_PDSLEEPCFG0_DCDC_VSEL_MASK;
        PMC->PDSLEEPCFG0 |= PMC_PDSLEEPCFG0_DCDC_VSEL(setpoint);
    }
    else if (regulator == kRegulator_Vdd2LDO)
    {
        assert(setpoint < 4U);
        PMC->PDSLEEPCFG0 &= ~PMC_PDSLEEPCFG0_LDO2_VSEL_MASK;
        PMC->PDSLEEPCFG0 |= PMC_PDSLEEPCFG0_LDO2_VSEL(setpoint);
    }
    else
    {
        assert(setpoint < 4U);
        PMC->PDSLEEPCFG0 &= ~PMC_PDSLEEPCFG0_LDO1_VSEL_MASK;
        PMC->PDSLEEPCFG0 |= PMC_PDSLEEPCFG0_LDO1_VSEL(setpoint);
    }
}

void POWER_SetRunRegulatorMode(power_regulator_t regulator, uint32_t mode)
{
    if (regulator == kRegulator_DCDC)
    {
        PMC->PDRUNCFG0 &= ~PMC_PDRUNCFG0_DCDC_LP_MASK;
        PMC->PDRUNCFG0 |= PMC_PDRUNCFG0_DCDC_LP(mode);
    }
    else if (regulator == kRegulator_Vdd2LDO)
    {
        PMC->PDRUNCFG0 &= ~PMC_PDRUNCFG0_LDO2_MODE_MASK;
        PMC->PDRUNCFG0 |= PMC_PDRUNCFG0_LDO2_MODE(mode);
    }
    else
    {
        PMC->PDRUNCFG0 &= ~PMC_PDRUNCFG0_LDO1_MODE_MASK;
        PMC->PDRUNCFG0 |= PMC_PDRUNCFG0_LDO1_MODE(mode);
    }
}

void POWER_SetSleepRegulatorMode(power_regulator_t regulator, uint32_t mode)
{
    if (regulator == kRegulator_DCDC)
    {
        PMC->PDSLEEPCFG0 &= ~PMC_PDSLEEPCFG0_DCDC_LP_MASK;
        PMC->PDSLEEPCFG0 |= PMC_PDSLEEPCFG0_DCDC_LP(mode);
    }
    else if (regulator == kRegulator_Vdd2LDO)
    {
        PMC->PDSLEEPCFG0 &= ~PMC_PDSLEEPCFG0_LDO2_MODE_MASK;
        PMC->PDSLEEPCFG0 |= PMC_PDSLEEPCFG0_LDO2_MODE(mode);
    }
    else
    {
        PMC->PDSLEEPCFG0 &= ~PMC_PDSLEEPCFG0_LDO1_MODE_MASK;
        PMC->PDSLEEPCFG0 |= PMC_PDSLEEPCFG0_LDO1_MODE(mode);
    }
}

void POWER_ResetIOBank(uint32_t mask)
{
    uint32_t cfg = 0U;
    cfg          = PMC->PADCFG;

    cfg &= ~(PMC_PADCFG_ISOCTRL_MASK | PMC_PADCFG_RSTCTRL_MASK); /* Clear W1C bits. */
    PMC->PADCFG = cfg | (mask << PMC_PADCFG_RSTCTRL_SHIFT);
}

void POWER_IOBankIsolationHold(uint32_t mask)
{
    uint32_t cfg = 0U;
    cfg          = PMC->PADCFG;

    cfg &= ~(PMC_PADCFG_ISOCTRL_MASK | PMC_PADCFG_RSTCTRL_MASK); /* Clear W1C bits. */

    PMC->PADCFG = cfg | (mask << PMC_PADCFG_ISOHOLD_SHIFT);
}

void POWER_IOBankClearIsolationHold(uint32_t mask)
{
    PMC->PADCFG |= mask << PMC_PADCFG_ISOCTRL_SHIFT; /* W1C. */
}

#if defined(PMC0)
void POWER_ConfigRBBVolt(const power_rbb_voltage_t *config)
{
    PMC->BBCTRL = (*((const uint32_t *)(const void *)config)) &
                  (PMC_BBCTRL_RBB1LVL_MASK | PMC_BBCTRL_RBB2LVL_MASK | PMC_BBCTRL_RBBNLVL_MASK);
}

void POWER_SetVddnSupplySrc(power_vdd_src_t src)
{
    assert(src == kVddSrc_PMIC); /* The VDDN can't be supplied by DCDC due to ERRATA. */

    s_vddnSrc = src;
    if (s_vddnSrc == kVddSrc_PMIC) /* If powered by external PMIC, power down DCDC. */
    {
        PMC->POWERCFG |= PMC_POWERCFG_DCDCPD_MASK;
    }
}

void POWER_SetVdd1SupplySrc(power_vdd_src_t src)
{
    s_vdd1Src = src;
    if (src == kVddSrc_PMIC) /* If powered by external PMIC, power down LDO1. */
    {
        PMC->POWERCFG |= PMC_POWERCFG_LDO1PD_MASK;
    }
}

void POWER_SetVdd2SupplySrc(power_vdd_src_t src)
{
    s_vdd2Src = src;
    if (src == kVddSrc_PMIC) /* If powered by external PMIC, power down LDO2. */
    {
        PMC->POWERCFG |= PMC_POWERCFG_LDO2PD_MASK;
    }
}

void POWER_DisableRegulators(uint32_t mask)
{
    PMC->POWERCFG |= mask & 0xFF80U; /* Ignore FDSR related bits. */
}

void POWER_EnableSleepRegulators(uint32_t mask)
{
    PMC->POWERCFG |= mask & 0x7FU; /* Ignore all mode control bits. */
}

void POWER_DisableSleepRegulators(uint32_t mask)
{
    PMC->POWERCFG &= ~(mask & 0x7FU); /* Ignore all mode control bits. */
}

void POWER_SetPMICModeDelay(uint8_t value)
{
    PMC->POWERCFG &= ~PMC_POWERCFG_MODEDLY_MASK;
    PMC->POWERCFG |= PMC_POWERCFG_MODEDLY(value);
}

void POWER_SetPORVoltage(const power_por_voltage_t *porVolt)
{
    PMC->PORCTRL = (*((const uint32_t *)(const void *)porVolt));
}
#endif

#if defined(PMC0) /* Compute domain request enter deep sleep mode. */
AT_QUICKACCESS_SECTION_CODE(static void POWER_EnableXspiCache(CACHE64_CTRL_Type *cache))
{
    /* First, invalidate the entire cache. */
    cache->CCR |= CACHE64_CTRL_CCR_INVW0_MASK | CACHE64_CTRL_CCR_INVW1_MASK | CACHE64_CTRL_CCR_GO_MASK;
    while ((cache->CCR & CACHE64_CTRL_CCR_GO_MASK) != 0x00U)
    {
    }
    /* As a precaution clear the bits to avoid inadvertently re-running this command. */
    cache->CCR &= ~(CACHE64_CTRL_CCR_INVW0_MASK | CACHE64_CTRL_CCR_INVW1_MASK);
    /* Now enable the cache. */
    cache->CCR |= CACHE64_CTRL_CCR_ENCACHE_MASK;
}

AT_QUICKACCESS_SECTION_CODE(static void POWER_DisableXspiCache(CACHE64_CTRL_Type *cache))
{
    /* First, clean XSPI cache. */
    cache->CCR |= CACHE64_CTRL_CCR_PUSHW0_MASK | CACHE64_CTRL_CCR_PUSHW1_MASK | CACHE64_CTRL_CCR_GO_MASK;
    while ((cache->CCR & CACHE64_CTRL_CCR_GO_MASK) != 0x00U)
    {
    }
    /* As a precaution clear the bits to avoid inadvertently re-running this command. */
    cache->CCR &= ~(CACHE64_CTRL_CCR_PUSHW0_MASK | CACHE64_CTRL_CCR_PUSHW1_MASK);

    /* Now disable XSPI cache. */
    cache->CCR &= ~CACHE64_CTRL_CCR_ENCACHE_MASK;
}

AT_QUICKACCESS_SECTION_CODE(static void deinitXSPI(XSPI_Type *base, CACHE64_CTRL_Type *cache))
{
    xspiCacheEnabled = false;
    base->MCR &= ~XSPI_MCR_MDIS_MASK;

    /* Wait until XSPI is not busy */
    while ((base->SR & XSPI_SR_BUSY_MASK) != 0U)
    {
    }

    if ((cache->CCR & CACHE64_CTRL_CCR_ENCACHE_MASK) != 0x00U)
    {
        xspiCacheEnabled = true;
        POWER_DisableXspiCache(cache);
    }

    /* Disable module. */
    base->MCR |= XSPI_MCR_MDIS_MASK;
}

AT_QUICKACCESS_SECTION_CODE(static void initXSPI(XSPI_Type *base, CACHE64_CTRL_Type *cache))
{
    /* Disable XSPI module */
    base->MCR |= XSPI_MCR_MDIS_MASK;
    base->MCR |= XSPI_MCR_IPS_TG_RST_MASK;

    base->MCR &= ~XSPI_MCR_MDIS_MASK;

    base->MCR |= XSPI_MCR_SWRSTSD_MASK | XSPI_MCR_SWRSTHD_MASK;
    for (uint32_t i = 0U; i < 6U; i++)
    {
        __NOP();
    }
    base->MCR |= XSPI_MCR_MDIS_MASK;
    base->MCR &= ~(XSPI_MCR_SWRSTSD_MASK | XSPI_MCR_SWRSTHD_MASK);
    for (uint32_t i = 0U; i < 6U; i++)
    {
        __NOP();
    }
    base->MCR &= ~XSPI_MCR_MDIS_MASK;

    base->MCR |= XSPI_MCR_MDIS_MASK;

    /* Clear AHB buffer. */
    base->SPTRCLR |= XSPI_SPTRCLR_ABRT_CLR_MASK;
    while ((base->SPTRCLR & XSPI_SPTRCLR_ABRT_CLR_MASK) != 0UL)
    {
    }

    /* Clear AHB access sequence pointer. */
    base->SPTRCLR |= XSPI_SPTRCLR_BFPTRC_MASK;

    /* Enable XSPI module */
    base->MCR &= ~XSPI_MCR_MDIS_MASK;

    if (xspiCacheEnabled)
    {
        POWER_EnableXspiCache(cache);
    }

    __DSB();
    __ISB();
}

AT_QUICKACCESS_SECTION_CODE(static void deinitXip(void))
{
    if (POWER_IS_XIP_XSPI0())
    {
        /* Enable XSPI clock again */
        CLKCTL0->PSCCTL1_SET = CLKCTL0_PSCCTL1_SET_XSPI0_MASK;
        /* Disable XSPI module */
        deinitXSPI(XSPI0, CACHE64_CTRL0);
        CLKCTL0->PSCCTL1_CLR = CLKCTL0_PSCCTL1_SET_XSPI0_MASK;
    }
    else if (POWER_IS_XIP_XSPI1())
    {
        /* Enable XSPI clock again */
        CLKCTL0->PSCCTL1_SET = CLKCTL0_PSCCTL1_SET_XSPI1_MASK;
        /* Disable XSPI module */
        deinitXSPI(XSPI1, CACHE64_CTRL1);
        CLKCTL0->PSCCTL1_CLR = CLKCTL0_PSCCTL1_SET_XSPI1_MASK;
    }
    else
    {
        /* Do nothing */
    }
}

AT_QUICKACCESS_SECTION_CODE(static void initXip(void))
{
    if (POWER_IS_XIP_XSPI0())
    {
        /* Enable XSPI clock again */
        CLKCTL0->PSCCTL1_SET = CLKCTL0_PSCCTL1_SET_XSPI0_MASK;
        /* Re-enable XSPI module */
        initXSPI(XSPI0, CACHE64_CTRL0);
    }
    else if (POWER_IS_XIP_XSPI1())
    {
        /* Enable XSPI clock again */
        CLKCTL0->PSCCTL1_SET = CLKCTL0_PSCCTL1_SET_XSPI1_MASK;
        /* Re-enable XSPI module */
        initXSPI(XSPI1, CACHE64_CTRL1);
    }
    else
    {
        /* Do nothing */
    }
}

/* Need do low power request-ack for all the modules capable of DMA HW Wake function if the DMA_HWWake is used. */
AT_QUICKACCESS_SECTION_CODE(static void POWER_DMA_HWWake_LPRequest(void))
{
    uint32_t lpReqClockCfg, lpReqResetCfg;

    if (SLEEPCON0->HW_WAKE != 0U) /* Only assert the LP Requet when DMA HW_WAKE enabled. */
    {
        lpReqClockCfg  = CLKCTL0->PSCCTL1;
        lpReqResetCfg  = RSTCTL0->PRSTCTL2;
        lpReqConfig[0] = SLEEPCON0->PRIVATE_CCTRL0;
        lpReqConfig[1] = SLEEPCON0->SHA_MED_TCTRL0;
        lpReqConfig[2] = SLEEPCON0->SHA_SEN_TCTRL0;
        lpReqConfig[3] = SLEEPCON0->PRIVATE_TCTRL0;
        lpReqConfig[4] = SLEEPCON0->PRIVATE_TCTRL2;

        CLKCTL0->PSCCTL1_SET =
            CLKCTL0_PSCCTL1_EDMA0_MASK |
            CLKCTL0_PSCCTL1_EDMA1_MASK; /* DMA clock need to be enabled to finishe low power handshake. */
        RSTCTL0->PRSTCTL2_CLR =
            RSTCTL0_PRSTCTL2_EDMA0_MASK |
            RSTCTL0_PRSTCTL2_EDMA1_MASK; /* DMA reset need to be cleared to finishe low power handshake. */

        SLEEPCON0->PRIVATE_CCTRL0 |= PRIVATE_CONTROLLER_HWWAKE_MODULE_MASK;
        SLEEPCON0->SHA_MED_TCTRL0 |= SLEEPCON0_SHA_MED_TCTRL0_FLEXIO_B_LPREQ_MASK |
                                     SLEEPCON0_SHA_MED_TCTRL0_LPSPI16_B_LPREQ_MASK |
                                     SLEEPCON0_SHA_MED_TCTRL0_LPSPI14_B_LPREQ_MASK; /* FLEXIO, LPSPI Bus*/
        SLEEPCON0->SHA_SEN_TCTRL0 |= SLEEPCON0_SHA_SEN_TCTRL0_MICFIL_STOP_MASK;     /* MICFIL */
        SLEEPCON0->PRIVATE_TCTRL0 |= PRIVATE_TCTRL_HWWAKE_MODULE_MASK0;             /* LP_FLEXCOMM */
        SLEEPCON0->PRIVATE_TCTRL2 |= PRIVATE_TCTRL_HWWAKE_MODULE_MASK1;             /* SAI */

        while ((SLEEPCON0->PRIVATE_CSTAT0 & PRIVATE_CONTROLLER_HWWAKE_MODULE_MASK) !=
               PRIVATE_CONTROLLER_HWWAKE_MODULE_MASK)
        {
        }
        while ((SLEEPCON0->SHA_MEDSEN_TSTAT0 & SHA_MEDSEN_TSTAT_HWWAKE_MODULE_MASK) !=
               SHA_MEDSEN_TSTAT_HWWAKE_MODULE_MASK)
        {
        }
        while ((SLEEPCON0->PRIVATE_TSTAT0 & PRIVATE_TSTAT_HWWAKE_MODULE_MASK0) != PRIVATE_TSTAT_HWWAKE_MODULE_MASK0)
        {
        }
        while ((SLEEPCON0->PRIVATE_TSTAT1 & PRIVATE_TSTAT_HWWAKE_MODULE_MASK1) != PRIVATE_TSTAT_HWWAKE_MODULE_MASK1)
        {
        }

        CLKCTL0->PSCCTL1  = lpReqClockCfg;
        RSTCTL0->PRSTCTL2 = lpReqResetCfg;
    }
}

AT_QUICKACCESS_SECTION_CODE(static void POWER_DMA_HWWake_LPRestore(void))
{
    if (SLEEPCON0->HW_WAKE != 0U) /* DMA HW_WAKE enabled. */
    {
        /* restore the configuration */
        SLEEPCON0->PRIVATE_CCTRL0 = lpReqConfig[0];
        SLEEPCON0->SHA_MED_TCTRL0 = lpReqConfig[1];
        SLEEPCON0->SHA_SEN_TCTRL0 = lpReqConfig[2];
        SLEEPCON0->PRIVATE_TCTRL0 = lpReqConfig[3];
        SLEEPCON0->PRIVATE_TCTRL2 = lpReqConfig[4];
    }
}

AT_QUICKACCESS_SECTION_CODE(static void POWER_DisableCache(XCACHE_Type *base))
{
    /* First, push any modified contents. */
    base->CCR |= XCACHE_CCR_PUSHW0_MASK | XCACHE_CCR_PUSHW1_MASK | XCACHE_CCR_GO_MASK;

    /* Wait until the cache command completes. */
    while ((base->CCR & XCACHE_CCR_GO_MASK) != 0x00U)
    {
    }

    /* As a precaution clear the bits to avoid inadvertently re-running this command. */
    base->CCR &= ~(XCACHE_CCR_PUSHW0_MASK | XCACHE_CCR_PUSHW1_MASK);

    /* Now disable the cache. */
    base->CCR &= ~XCACHE_CCR_ENCACHE_MASK;
}

AT_QUICKACCESS_SECTION_CODE(static void POWER_EnableCache(XCACHE_Type *base))
{
    /* Invalidate all lines in both ways and initiate the cache command. */
    base->CCR |= XCACHE_CCR_INVW0_MASK | XCACHE_CCR_INVW1_MASK | XCACHE_CCR_GO_MASK;

    /* Wait until the cache command completes. */
    while ((base->CCR & XCACHE_CCR_GO_MASK) != 0x00U)
    {
    }

    /* Now enable the cache. */
    base->CCR |= XCACHE_CCR_ENCACHE_MASK;
    __ISB();
    __DSB();
}

/** @brief This API configure the SLEEPCON SLEEPCFG and PMC_PDSLEEPCFG registers.
 *
 * @param exclude_from_pd the bits mask need to be cleared for the registers.
 */
AT_QUICKACCESS_SECTION_CODE(static void POWER_EnterLowPower_FullConfig(const uint32_t exclude_from_pd[7],
                                                                       power_mode_cfg_t mode,
                                                                       uint32_t pmic_mode_pins))
{
    uint32_t pmc_ctrl;
    uint32_t pmicMode;
    uint32_t pdsleepcfg0;
    bool cacheEnabled[2];
    bool backupCache[2];

    uint32_t pmsk = __get_PRIMASK();

    __disable_irq();

    /* Body bias is configured through other APIs before the API call. */

    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    if (mode == kPower_DeepSleep)
    {
        /* The DMA HWWake function requires all the ACK of modules supporting HWWake, do handshake for those modules. */
        POWER_DMA_HWWake_LPRequest();
    }

    /* Power on mask bit correspond modules during Deep Sleep mode. */
    SLEEPCON->SLEEPCFG = (SCFG0_DEEP_SLEEP & ~exclude_from_pd[0]) | (SLEEPCON->RUNCFG & ~exclude_from_pd[0]);

    if ((exclude_from_pd[0] & SLEEPCON0_SLEEPCFG_FRO0_PD_MASK) == 0U) /* Power down FRO0, need wait FRO0 power down. */
    {
        SLEEPCON->PWRDOWN_WAIT &= ~SLEEPCON0_PWRDOWN_WAIT_IGN_FRO0PDR_MASK;
    }
    if ((exclude_from_pd[0] & SLEEPCON0_SLEEPCFG_FRO1_PD_MASK) ==
        0U) /* When keeping power on, the PWRDOWN_WAIT is not used. */
    {
        SLEEPCON->PWRDOWN_WAIT &= ~SLEEPCON0_PWRDOWN_WAIT_IGN_FRO1PDR_MASK;
    }

    pdsleepcfg0    = PMC->PDSLEEPCFG0 & (~PCFG0_DEEP_SLEEP);
    backupCache[0] = false;
    backupCache[1] = false;

    switch (mode)
    {
        case kPower_DeepSleep:
            if ((exclude_from_pd[5] & PMC_PDSLEEPCFG4_CPU0_CCACHE_MASK) == 0U)
            {
                backupCache[1] = true;
            }
            if ((exclude_from_pd[5] & PMC_PDSLEEPCFG4_CPU0_SCACHE_MASK) == 0U)
            {
                backupCache[0] = true;
            }

            /* Keep *BB, LDOVSEL, DCDV VSEL bits not changed. Clear DPD, FDPD, FDSR, V2COMP_DSR, V2COM_DSR(When
             * V2COM_DSR set all other VDD2 need to be off), PMICMODE bits. */
            pdsleepcfg0 &=
                ~(PMC_PDSLEEPCFG0_FDSR_MASK | PMC_PDSLEEPCFG0_V2COMP_DSR_MASK | PMC_PDSLEEPCFG0_V2COM_DSR_MASK |
                  PMC_PDSLEEPCFG0_DPD_MASK | PMC_PDSLEEPCFG0_FDPD_MASK | PMC_PDSLEEPCFG0_PMICMODE_MASK);
            PMC->PDSLEEPCFG0 = pdsleepcfg0 | (PCFG0_DEEP_SLEEP & ~exclude_from_pd[1]);
            /* V2NMED_DSR should be set if VNCOM_DSR is set. */
            if ((PMC->PDSLEEPCFG0 & PMC_PDSLEEPCFG0_VNCOM_DSR_MASK) != 0U)
            {
                assert((exclude_from_pd[1] & PMC_PDSLEEPCFG0_V2NMED_DSR_MASK) == 0U);
            }
            break;

        case kPower_DeepSleepRetention:
            backupCache[0] = true;
            backupCache[1] = true;
            /* Keep *BB, LDOVSEL, DCDV VSEL bits not changed. Clear DPD, FDPD, PMICMODE bits. Always set
             * V2COMP_DSR(Compute DSR) and V2DSP_PD(When VDD2_COMP off, VDD2_DSP need to be off).*/
            pdsleepcfg0 &= ~(PMC_PDSLEEPCFG0_DPD_MASK | PMC_PDSLEEPCFG0_FDPD_MASK | PMC_PDSLEEPCFG0_PMICMODE_MASK);
            PMC->PDSLEEPCFG0 = pdsleepcfg0 |
                               ((PCFG0_DEEP_SLEEP | PCFG0_DSR | PMC_PDSLEEPCFG0_FDSR_MASK) & ~exclude_from_pd[1]) |
                               PMC_PDSLEEPCFG0_V2COMP_DSR_MASK | PMC_PDSLEEPCFG0_V2DSP_PD_MASK;
            /* Check DSR combination. If request V2COM_DSR,all other DSR bits should be set */
            if ((PMC->PDSLEEPCFG0 & PMC_PDSLEEPCFG0_V2COM_DSR_MASK) != 0U)
            {
                assert((exclude_from_pd[1] & (PMC_PDSLEEPCFG0_V2COMP_DSR_MASK | PMC_PDSLEEPCFG0_V2NMED_DSR_MASK |
                                              PMC_PDSLEEPCFG0_VNCOM_DSR_MASK)) == 0U);
            }
            else if ((PMC->PDSLEEPCFG0 & PMC_PDSLEEPCFG0_VNCOM_DSR_MASK) !=
                     0U) /* V2NMED_DSR should be set if VNCOM_DSR is set. */
            {
                assert((exclude_from_pd[1] & PMC_PDSLEEPCFG0_V2NMED_DSR_MASK) == 0U);
            }
            else
            {
                /* Empty. */
            }
            break;

        case kPower_DeepPowerDown:
            /* Incase the CPU is in DSR mode. */
            backupCache[0] = true;
            backupCache[1] = true;
            /* Keep *BB, LDOVSEL, DCDV VSEL bits not changed. Clear PMICMODE bits.*/
            pdsleepcfg0 &= ~(PMC_PDSLEEPCFG0_PMICMODE_MASK | PMC_PDSLEEPCFG0_FDSR_MASK);
            PMC->PDSLEEPCFG0 =
                pdsleepcfg0 | ((PCFG0_DEEP_SLEEP | PCFG0_DSR) & ~exclude_from_pd[1]) | PMC_PDSLEEPCFG0_DPD_MASK;
            break;

        case kPower_FullDeepPowerDown:
            /* Incase the CPU is in DSR mode. */
            backupCache[0] = true;
            backupCache[1] = true;
            /* Keep *BB, LDOVSEL, DCDV VSEL bits not changed. Clear PMICMODE bits.*/
            pdsleepcfg0 &= ~(PMC_PDSLEEPCFG0_PMICMODE_MASK | PMC_PDSLEEPCFG0_FDSR_MASK);
            PMC->PDSLEEPCFG0 =
                pdsleepcfg0 | ((PCFG0_DEEP_SLEEP | PCFG0_DSR) & ~exclude_from_pd[1]) | PMC_PDSLEEPCFG0_FDPD_MASK;
            break;

        default:
            /* Added comments to prevent the violation of MISRA C-2012 rule. */
            break;
    }

    pmicMode = (exclude_from_pd[1] & PMC_PDSLEEPCFG0_PMICMODE_MASK) >> PMC_PDSLEEPCFG0_PMICMODE_SHIFT;
    if (pmicMode == 0U) /* Use default PMIC Mode configuration. */
    {
        /* Set PMIC mode pin as pre-defined. */
        PMC->PDSLEEPCFG0 |= PMC_PDSLEEPCFG0_PMICMODE(pmic_mode_pins);
    }
    else /* User defined PMIC mode. */
    {
        PMC->PDSLEEPCFG0 |= pmicMode << PMC_PDSLEEPCFG0_PMICMODE_SHIFT;
    }

    /* Regulator related configuration. */
    PMC->PDSLEEPCFG0 &= ~PMC_PDSLEEPCFG0_LDO1_VSEL_MASK; /* Select lowest LDOVDD1 voltage for aggregation. */
    if (s_vdd1Src == kVddSrc_PMIC)
    {
        PMC->PDSLEEPCFG0 &= ~PMC_PDSLEEPCFG0_LDO1_MODE_MASK; /* Bypass mode. */
    }
    else
    {
        PMC->PDSLEEPCFG0 |= PMC_PDSLEEPCFG0_LDO1_MODE_MASK; /* Low power mode. */
    }
    if (s_vdd2Src == kVddSrc_PMIC)
    {
        PMC->PDSLEEPCFG0 &= ~PMC_PDSLEEPCFG0_LDO2_MODE_MASK; /* Bypass mode. */
    }
    else
    {
        PMC->PDSLEEPCFG0 |= PMC_PDSLEEPCFG0_LDO2_MODE_MASK; /* Low power mode. */
    }

    PMC->PDSLEEPCFG1 = (PCFG1_DEEP_SLEEP & ~exclude_from_pd[2]) | (PMC->PDRUNCFG1 & ~exclude_from_pd[2]);

    /* When either PLL, FRO, TEMPERATURE, POR, LVD, HVD enabled, the PMCREF_LP should be cleared. */
    if (((exclude_from_pd[0] &
          (SLEEPCON0_SLEEPCFG_FRO0_PD_MASK | SLEEPCON0_SLEEPCFG_FRO1_PD_MASK | SLEEPCON0_SLEEPCFG_FRO2_PD_MASK |
           SLEEPCON0_SLEEPCFG_AUDPLLANA_PD_MASK | SLEEPCON0_SLEEPCFG_AUDPLLLDO_PD_MASK |
           SLEEPCON0_SLEEPCFG_PLLANA_PD_MASK | SLEEPCON0_SLEEPCFG_PLLLDO_PD_MASK)) != 0U) ||
        ((exclude_from_pd[2] &
          (PMC_PDSLEEPCFG1_HVDN_PD_MASK | PMC_PDSLEEPCFG1_LVDN_LP_MASK | PMC_PDSLEEPCFG1_PORN_LP_MASK |
           PMC_PDSLEEPCFG1_HVD2_PD_MASK | PMC_PDSLEEPCFG1_LVD2_LP_MASK | PMC_PDSLEEPCFG1_POR2_LP_MASK |
           PMC_PDSLEEPCFG1_HVD1_PD_MASK | PMC_PDSLEEPCFG1_LVD1_LP_MASK | PMC_PDSLEEPCFG1_POR1_LP_MASK)) != 0U))
    {
        PMC->PDSLEEPCFG1 &= ~PMC_PDSLEEPCFG1_PMCREF_LP_MASK;
    }

    PMC->PDSLEEPCFG2 = (PCFG2_DEEP_SLEEP & ~exclude_from_pd[3]) | (PMC->PDRUNCFG2 & ~exclude_from_pd[3]);
    PMC->PDSLEEPCFG3 = (PCFG3_DEEP_SLEEP & ~exclude_from_pd[4]) | (PMC->PDRUNCFG3 & ~exclude_from_pd[4]);
    PMC->PDSLEEPCFG4 = (PCFG4_DEEP_SLEEP & ~exclude_from_pd[5]) | (PMC->PDRUNCFG4 & ~exclude_from_pd[5]);
    PMC->PDSLEEPCFG5 = (PCFG5_DEEP_SLEEP & ~exclude_from_pd[6]) | (PMC->PDRUNCFG5 & ~exclude_from_pd[6]);

    /* Stall Hifi4 if power down VDD2_DSP*/
    if ((PMC->PDSLEEPCFG0 & PMC_PDSLEEPCFG0_V2DSP_PD_MASK) != 0U)
    {
        SYSCON0->DSPSTALL = SYSCON0_DSPSTALL_DSPSTALL_MASK;
    }

    /* Set PMC_CTRL[APPLYCFG]. */
    while ((PMC->STATUS & PMC_STATUS_BUSY_MASK) != 0U) /* Cannot set APPLYCFG when ACTIVEFSM is 1 */
    {
    }
    PMC->CTRL |= PMC_CTRL_APPLYCFG_MASK;
    while ((PMC->STATUS & PMC_STATUS_BUSY_MASK) != 0U) /* Wait all PMC finite state machines finished. */
    {
    }

    /* Clear all event flags before enter deep sleep */
    PMC->FLAGS    = PMC->FLAGS;
    PMC->PWRFLAGS = PMC->PWRFLAGS;

    /* Disable LVD core reset. */
    pmc_ctrl  = PMC->CTRL;
    PMC->CTRL = pmc_ctrl & ~(PMC_CTRL_LVDNRE_MASK | PMC_CTRL_LVD2RE_MASK | PMC_CTRL_LVD1RE_MASK |
                             PMC_CTRL_AGDET2RE_MASK | PMC_CTRL_AGDET1RE_MASK);

    /* Deinit XSPI interface in case XIP */
    deinitXip();

    if (backupCache[1]) /* Xcache is not retented in DSR mode. */
    {
        cacheEnabled[1] = ((XCACHE1->CCR & XCACHE_CCR_ENCACHE_MASK) == 0U) ? false : true;

        if (cacheEnabled[1])
        {
            POWER_DisableCache(XCACHE1);
        }
    }
    if (backupCache[0]) /* Xcache is not retented in DSR mode. */
    {
        cacheEnabled[0] = ((XCACHE0->CCR & XCACHE_CCR_ENCACHE_MASK) == 0U) ? false : true;

        if (cacheEnabled[0])
        {
            POWER_DisableCache(XCACHE0);
        }
    }

    /* If the first one to Deep Sleep, ignore the Ignores power-down ready signal from LPOSC, FRO2. */
    if ((PMC->STATUS & PMC_STATUS_DSSENS_MASK) == 0U)
    {
        SLEEPCON->PWRDOWN_WAIT |= SLEEPCON0_PWRDOWN_WAIT_IGN_FRO2PDR_MASK | SLEEPCON0_PWRDOWN_WAIT_IGN_LPOSCPDR_MASK;
    }

    /* Enter deep sleep mode */
    __WFI();

    if (mode == kPower_DeepSleep)
    {
        POWER_DMA_HWWake_LPRestore();
    }

    if (backupCache[1])
    {
        if (cacheEnabled[1])
        {
            POWER_EnableCache(XCACHE1);
        }
    }
    if (backupCache[0])
    {
        if (cacheEnabled[0])
        {
            POWER_EnableCache(XCACHE0);
        }
    }

    /* Init XSPI in case XIP */
    initXip();

    /* Restore PMC LVD core reset and OTP switch setting */
    PMC->CTRL = pmc_ctrl;

    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    __set_PRIMASK(pmsk);
}

AT_QUICKACCESS_SECTION_CODE(void POWER_EnterDSR(const uint32_t exclude_from_pd[7]))
{
    POWER_EnterLowPower_FullConfig(exclude_from_pd, kPower_DeepSleepRetention, POWER_DEFAULT_PMICMODE_DSR);
}
#else
/* Need do low power request-ack for all the modules capable of DMA HW Wake function if the DMA_HWWake is used. */
AT_QUICKACCESS_SECTION_CODE(static void POWER_DMA_HWWake_LPRequest(void))
{
    uint32_t lpReqClockCfg, lpReqResetCfg;

    if (SLEEPCON1->HW_WAKE != 0U) /* Only assert the LP Requet when DMA HW_WAKE enabled. */
    {
        lpReqClockCfg  = CLKCTL1->PSCCTL1;
        lpReqResetCfg  = RSTCTL1->PRSTCTL0;
        lpReqConfig[0] = SLEEPCON1->PRIVATE_CCTRL0;
        lpReqConfig[1] = SLEEPCON1->SHA_MED_TCTRL0;
        lpReqConfig[2] = SLEEPCON1->SHA_SEN_TCTRL0;
        lpReqConfig[3] = SLEEPCON1->PRIVATE_TCTRL0;

        CLKCTL1->PSCCTL1_SET =
            CLKCTL1_PSCCTL1_EDMA2_MASK |
            CLKCTL1_PSCCTL1_EDMA3_MASK; /* DMA clock need to be enabled to finishe low power handshake. */
        RSTCTL1->PRSTCTL0_CLR =
            RSTCTL1_PRSTCTL0_EDMA2_MASK |
            RSTCTL1_PRSTCTL0_EDMA3_MASK; /* DMA reset need to be cleared to finishe low power handshake. */

        SLEEPCON1->PRIVATE_CCTRL0 |= PRIVATE_CONTROLLER_HWWAKE_MODULE_MASK;
        SLEEPCON1->SHA_MED_TCTRL0 |= SLEEPCON1_SHA_MED_TCTRL0_FLEXIO_B_LPREQ_MASK; /* FLEXIO Bus*/
        SLEEPCON1->SHA_SEN_TCTRL0 |= SLEEPCON1_SHA_SEN_TCTRL0_MICFIL_STOP_MASK;    /* MICFIL */
        SLEEPCON1->PRIVATE_TCTRL0 |= PRIVATE_TCTRL_HWWAKE_MODULE_MASK0;            /* SAI and LP_FLEXCOMM */

        while ((SLEEPCON1->PRIVATE_CSTAT0 & PRIVATE_CONTROLLER_HWWAKE_MODULE_MASK) !=
               PRIVATE_CONTROLLER_HWWAKE_MODULE_MASK)
        {
        }
        while ((SLEEPCON1->SHA_MEDSEN_TSTAT0 & SHA_MEDSEN_TSTAT_HWWAKE_MODULE_MASK) !=
               SHA_MEDSEN_TSTAT_HWWAKE_MODULE_MASK)
        {
        }
        while ((SLEEPCON1->PRIVATE_TSTAT0 & PRIVATE_TSTAT_HWWAKE_MODULE_MASK0) != PRIVATE_TSTAT_HWWAKE_MODULE_MASK0)
        {
        }
        CLKCTL1->PSCCTL1  = lpReqClockCfg;
        RSTCTL1->PRSTCTL0 = lpReqResetCfg;
    }
}

AT_QUICKACCESS_SECTION_CODE(static void POWER_DMA_HWWake_LPRestore(void))
{
    if (SLEEPCON1->HW_WAKE != 0U) /* DMA HW_WAKE enabled. */
    {
        /* restore the configuration */
        SLEEPCON1->PRIVATE_CCTRL0 = lpReqConfig[0];
        SLEEPCON1->SHA_MED_TCTRL0 = lpReqConfig[1];
        SLEEPCON1->SHA_SEN_TCTRL0 = lpReqConfig[2];
        SLEEPCON1->PRIVATE_TCTRL0 = lpReqConfig[3];
    }
}

/** @brief This API configure the SLEEPCON SLEEPCFG and PMC_PDSLEEPCFG registers.
 *
 * @param exclude_from_pd the bits mask need to be cleared for the registers.
 */
AT_QUICKACCESS_SECTION_CODE(void static POWER_EnterLowPower_FullConfig(const uint32_t exclude_from_pd[7],
                                                                       power_mode_cfg_t mode,
                                                                       uint32_t pmic_mode_pins))
{
    uint32_t pmicMode;
    uint32_t pdsleepcfg0;
    uint32_t pmc_ctrl;

    uint32_t pmsk = __get_PRIMASK();

    __disable_irq();

    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    if (mode == kPower_DeepSleep)
    {
        /* The DMA HWWake function requires all the ACK of modules supporting HWWake, do handshake for those modules. */
        POWER_DMA_HWWake_LPRequest();
    }

    /* Power on mask bit correspond modules during Deep Sleep mode. */
    SLEEPCON->SLEEPCFG = (SCFG0_DEEP_SLEEP & ~exclude_from_pd[0]) | (SLEEPCON->RUNCFG & ~exclude_from_pd[0]);

    if ((exclude_from_pd[0] & SLEEPCON1_SLEEPCFG_FRO2_PD_MASK) != 0U)
    {
        SLEEPCON->PWRDOWN_WAIT |= SLEEPCON1_PWRDOWN_WAIT_IGN_FRO2PDR_MASK;
    }

    pdsleepcfg0 = PMC->PDSLEEPCFG0 & (~PCFG0_DEEP_SLEEP);
    switch (mode)
    {
        case kPower_DeepSleep:
            /* Keep *BB, LDOVSEL, DCDV VSEL bits not changed. Clear DPD, FDPD, FDSR, PMICMODE bits.*/
            pdsleepcfg0 &= ~(PMC_PDSLEEPCFG0_FDSR_MASK | PMC_PDSLEEPCFG0_DPD_MASK | PMC_PDSLEEPCFG0_FDPD_MASK |
                             PMC_PDSLEEPCFG0_PMICMODE_MASK);
            PMC->PDSLEEPCFG0 = pdsleepcfg0 | ((PCFG0_DEEP_SLEEP | PCFG0_DSR) & ~exclude_from_pd[1]);

            break;

        case kPower_DeepSleepRetention:
            /* Keep *BB, LDOVSEL, DCDV VSEL bits not changed. Clear DPD, FDPD, *DSR, PMICMODE bits.*/
            pdsleepcfg0 &= ~(PMC_PDSLEEPCFG0_DPD_MASK | PMC_PDSLEEPCFG0_FDPD_MASK | PMC_PDSLEEPCFG0_PMICMODE_MASK);
            PMC->PDSLEEPCFG0 = pdsleepcfg0 | (PCFG0_DEEP_SLEEP & ~exclude_from_pd[1]) | PCFG0_DSR |
                               PMC_PDSLEEPCFG0_FDSR_MASK; /* All domain DSR. */
            break;

        case kPower_DeepPowerDown:
            /* Keep *BB, LDOVSEL, DCDV VSEL bits not changed. Clear PMICMODE bits.*/
            pdsleepcfg0 &= ~(PMC_PDSLEEPCFG0_PMICMODE_MASK | PMC_PDSLEEPCFG0_FDSR_MASK);
            PMC->PDSLEEPCFG0 =
                pdsleepcfg0 | ((PCFG0_DEEP_SLEEP | PCFG0_DSR) & ~exclude_from_pd[1]) | PMC_PDSLEEPCFG0_DPD_MASK;
            break;

        case kPower_FullDeepPowerDown:
            /* Keep *BB, LDOVSEL, DCDV VSEL bits not changed. Clear PMICMODE bits.*/
            pdsleepcfg0 &= ~(PMC_PDSLEEPCFG0_PMICMODE_MASK | PMC_PDSLEEPCFG0_FDSR_MASK);
            PMC->PDSLEEPCFG0 =
                pdsleepcfg0 | ((PCFG0_DEEP_SLEEP | PCFG0_DSR) & ~exclude_from_pd[1]) | PMC_PDSLEEPCFG0_FDPD_MASK;
            break;

        default:
            /* Added comments to prevent the violation of MISRA C-2012 rule. */
            break;
    }

    pmicMode = (exclude_from_pd[1] & PMC_PDSLEEPCFG0_PMICMODE_MASK) >> PMC_PDSLEEPCFG0_PMICMODE_SHIFT;
    if (pmicMode == 0U) /* Use default PMIC Mode configuration. */
    {
        /* Set PMIC mode pin as predefined. */
        PMC->PDSLEEPCFG0 |= PMC_PDSLEEPCFG0_PMICMODE(pmic_mode_pins);
    }
    else /* User defined PMIC mode. */
    {
        PMC->PDSLEEPCFG0 |= pmicMode << PMC_PDSLEEPCFG0_PMICMODE_SHIFT;
    }

    /* Regulator related configuration. */
    PMC->PDSLEEPCFG0 &= ~PMC_PDSLEEPCFG0_LDO2_VSEL_MASK;     /* Select lowest LDOVDD2 voltage for aggregation. */
    if ((PMC->POWERCFG & PMC_POWERCFG_LDO1PD_MASK) != 0U)    /* PMIC used.*/
    {
        PMC->PDSLEEPCFG0 &= ~PMC_PDSLEEPCFG0_LDO1_MODE_MASK; /* Bypass mode. */
    }
    else
    {
        PMC->PDSLEEPCFG0 |= PMC_PDSLEEPCFG0_LDO1_MODE_MASK; /* Low power mode. */
    }
    if ((PMC->POWERCFG & PMC_POWERCFG_LDO2PD_MASK) != 0U)
    {
        PMC->PDSLEEPCFG0 &= ~PMC_PDSLEEPCFG0_LDO2_MODE_MASK; /* Bypass mode. */
    }
    else
    {
        PMC->PDSLEEPCFG0 |= PMC_PDSLEEPCFG0_LDO2_MODE_MASK; /* Low power mode. */
    }

    PMC->PDSLEEPCFG1 = (PCFG1_DEEP_SLEEP & ~exclude_from_pd[2]) | (PMC->PDRUNCFG1 & ~exclude_from_pd[2]);

    /* When either PLL, FRO, TEMPERATURE, POR, LVD, HVD enabled, the PMCREF_LP should be cleared. */
    if (((exclude_from_pd[0] & (SLEEPCON1_SLEEPCFG_FRO2_PD_MASK | SLEEPCON1_SLEEPCFG_AUDPLLANA_PD_MASK |
                                SLEEPCON1_SLEEPCFG_AUDPLLLDO_PD_MASK | SLEEPCON1_SLEEPCFG_PLLANA_PD_MASK |
                                SLEEPCON1_SLEEPCFG_PLLLDO_PD_MASK)) != 0U) ||
        ((exclude_from_pd[2] &
          (PMC_PDSLEEPCFG1_HVDN_PD_MASK | PMC_PDSLEEPCFG1_LVDN_LP_MASK | PMC_PDSLEEPCFG1_PORN_LP_MASK |
           PMC_PDSLEEPCFG1_HVD2_PD_MASK | PMC_PDSLEEPCFG1_LVD2_LP_MASK | PMC_PDSLEEPCFG1_POR2_LP_MASK |
           PMC_PDSLEEPCFG1_HVD1_PD_MASK | PMC_PDSLEEPCFG1_LVD1_LP_MASK | PMC_PDSLEEPCFG1_POR1_LP_MASK)) != 0U))
    {
        PMC->PDSLEEPCFG1 &= ~PMC_PDSLEEPCFG1_PMCREF_LP_MASK;
    }

    PMC->PDSLEEPCFG2 = (PCFG2_DEEP_SLEEP & ~exclude_from_pd[3]) | (PMC->PDRUNCFG2 & ~exclude_from_pd[3]);
    PMC->PDSLEEPCFG3 = (PCFG3_DEEP_SLEEP & ~exclude_from_pd[4]) | (PMC->PDRUNCFG3 & ~exclude_from_pd[4]);
    PMC->PDSLEEPCFG4 = (PCFG4_DEEP_SLEEP & ~exclude_from_pd[5]) | (PMC->PDRUNCFG4 & ~exclude_from_pd[5]);
    PMC->PDSLEEPCFG5 = (PCFG5_DEEP_SLEEP & ~exclude_from_pd[6]) | (PMC->PDRUNCFG5 & ~exclude_from_pd[6]);

    /* Set PMC_CTRL[APPLYCFG]. */
    while ((PMC->STATUS & PMC_STATUS_BUSY_MASK) != 0U) /* Cannot set APPLYCFG when ACTIVEFSM is 1 */
    {
    }
    PMC->CTRL |= PMC_CTRL_APPLYCFG_MASK;
    while ((PMC->STATUS & PMC_STATUS_BUSY_MASK) != 0U) /* Wait all PMC finite state machines finished. */
    {
    }

    /* Clear all event flags before enter deep sleep */
    PMC->FLAGS    = PMC->FLAGS;
    PMC->PWRFLAGS = PMC->PWRFLAGS;

    /* Disable LVD core reset. */
    pmc_ctrl  = PMC->CTRL;
    PMC->CTRL = pmc_ctrl & ~(PMC_CTRL_LVDNRE_MASK | PMC_CTRL_LVD2RE_MASK | PMC_CTRL_LVD1RE_MASK |
                             PMC_CTRL_AGDET2RE_MASK | PMC_CTRL_AGDET1RE_MASK);

    /* If the first one to Deep Sleep, ignore the Ignores power-down ready signal from LPOSC, FRO2. */
    /* if ((PMC->STATUS & PMC_STATUS_DSCOMP_MASK) == 0U) Ignore FRO2, LPOSC power-down ready signal because sense don't
     * know if they are used by compute domain. */
    SLEEPCON->PWRDOWN_WAIT |= SLEEPCON1_PWRDOWN_WAIT_IGN_FRO2PDR_MASK | SLEEPCON1_PWRDOWN_WAIT_IGN_LPOSCPDR_MASK;

    /* Enter deep sleep mode */
    __WFI();

    if (mode == kPower_DeepSleep)
    {
        POWER_DMA_HWWake_LPRestore();
    }

    /* Restore PMC LVD core reset and OTP switch setting */
    PMC->CTRL = pmc_ctrl;

    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    __set_PRIMASK(pmsk);
}

AT_QUICKACCESS_SECTION_CODE(void POWER_RequestDSR(const uint32_t exclude_from_pd[7]))
{
    POWER_EnterLowPower_FullConfig(exclude_from_pd, kPower_DeepSleepRetention, POWER_DEFAULT_PMICMODE_DSR);
}
#endif

AT_QUICKACCESS_SECTION_CODE(void POWER_EnterDeepSleep(const uint32_t exclude_from_pd[7]))
{
    POWER_EnterLowPower_FullConfig(exclude_from_pd, kPower_DeepSleep, POWER_DEFAULT_PMICMODE_DS);
}

/**
 * @brief    PMC Deep Sleep Power Down function call
 * @return   nothing
 */
AT_QUICKACCESS_SECTION_CODE(void POWER_RequestDeepPowerDown(const uint32_t exclude_from_pd[7]))
{
    POWER_EnterLowPower_FullConfig(exclude_from_pd, kPower_DeepPowerDown, POWER_DEFAULT_PMICMODE_DPD);
}

AT_QUICKACCESS_SECTION_CODE(void POWER_RequestFullDeepPowerDown(const uint32_t exclude_from_pd[7]))
{
    POWER_EnterLowPower_FullConfig(exclude_from_pd, kPower_FullDeepPowerDown, POWER_DEFAULT_PMICMODE_FDPD);
}

/* Enter Power mode */
void POWER_EnterPowerMode(power_mode_cfg_t mode, const uint32_t exclude_from_pd[7])
{
    switch (mode)
    {
        case kPower_Sleep:
            POWER_EnterSleep();
            break;
        case kPower_DeepSleep:
            POWER_EnterDeepSleep(exclude_from_pd);
            break;
        case kPower_DeepSleepRetention:
#if defined(PMC0)
            POWER_EnterDSR(exclude_from_pd);
#else
            POWER_RequestDSR(exclude_from_pd);
#endif
            break;
        case kPower_DeepPowerDown:
            POWER_RequestDeepPowerDown(exclude_from_pd);
            break;
        case kPower_FullDeepPowerDown:
            POWER_RequestFullDeepPowerDown(exclude_from_pd);
            break;
        default:
            /* Invalide mode. */
            assert(false);
            break;
    }
}

/* Get power lib version */
uint32_t POWER_GetLibVersion(void)
{
    return (uint32_t)FSL_POWER_DRIVER_VERSION;
}
