/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_sysctr.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.sysctr"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Reset the System Counter Instance.
 *
 * Restores the System Counter to reset state. Notice that this function will set all
 * registers to reset state except Counter Count Value register and Compare Count Value
 * register. System Counter module can not work after calling this API.
 *
 * @param base System Counter peripheral base address.
 */
static void SYSCTR_Reset(SYS_CTR_CONTROL_Type *ctrlBase, SYS_CTR_COMPARE_Type *cmpBase);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * brief Reset the System Counter Instance.
 *
 * Restores the System Counter to reset state. Notice that this function will set all
 * registers to reset state. System Counter module can not work after calling this API.
 *
 * param base System Counter peripheral base address.
 */
static void SYSCTR_Reset(SYS_CTR_CONTROL_Type *ctrlBase, SYS_CTR_COMPARE_Type *cmpBase)
{
    ctrlBase->CNTCR = SYS_CTR_CONTROL_CNTCR_EN(0) | SYS_CTR_CONTROL_CNTCR_HDBG(0) |
                      SYS_CTR_CONTROL_CNTCR_FCR0(1) | SYS_CTR_CONTROL_CNTCR_FCR1(0);

    while((ctrlBase->CNTSR & SYS_CTR_CONTROL_CNTSR_FCA1_MASK) != 0)
    {
    }

    ctrlBase->CNTCV0 = 0;
    ctrlBase->CNTCV1 = 0;
    cmpBase->CMPCVL0 = 0;
    cmpBase->CMPCVH0 = 0;
    cmpBase->CMPCVL1 = 0;
    cmpBase->CMPCVH1 = 0;

    ctrlBase->CNTCR2 = SYS_CTR_CONTROL_CNTCR2_HWFC_EN(0);

    cmpBase->CMPCR0 = SYS_CTR_COMPARE_CMPCR0_EN(0) | SYS_CTR_COMPARE_CMPCR0_IMASK(0);
    cmpBase->CMPCR1 = SYS_CTR_COMPARE_CMPCR1_EN(0) | SYS_CTR_COMPARE_CMPCR1_IMASK(0);
}

/*!
 * brief Initializes a System Counter instance.
 *
 * This function initializes the System Counter module with user-defined settings.
 * This example shows how to set up the sysctr_config_t parameters and how to call
 * the SYSCTR_Init function by passing in these parameters. Default clock source
 * is 24MHz base clock from crystal oscillator.
 * code
 *   sysctr_config_t sysctrConfig;
 *   sysctrConfig.enableDebugHalt               = false;
 *   sysctrConfig.enableHardwareFrequencyChange = false;
 *   SYSCTR_Init(SYS_CTR_CONTROL, SYS_CTR_COMPARE, &sysctr_config_t);
 * endcode
 *
 * param ctrlBase System Counter peripheral control model base address.
 * param cmpBase  System Counter peripheral compare model base address.
 * param pConfig  Configuration pointer to user's System Counter config structure.
 */
void SYSCTR_Init(SYS_CTR_CONTROL_Type *ctrlBase, SYS_CTR_COMPARE_Type *cmpBase, const sysctr_config_t *pConfig)
{
    assert(pConfig != NULL);

    uint32_t reg;

    (void)CLOCK_EnableClock(kCLOCK_Syscount);

    SYSCTR_Reset(ctrlBase, cmpBase);

    reg = ctrlBase->CNTCR;

    reg = pConfig->enableDebugHalt ? (reg | SYS_CTR_CONTROL_CNTCR_HDBG_MASK) :
                                     (reg & ~SYS_CTR_CONTROL_CNTCR_HDBG_MASK);

    ctrlBase->CNTCR = reg;

    reg = ctrlBase->CNTCR2;
                   
    reg = pConfig->enableHardwareFrequencyChange ? (reg | SYS_CTR_CONTROL_CNTCR2_HWFC_EN_MASK) :
                                                   (reg & ~SYS_CTR_CONTROL_CNTCR2_HWFC_EN_MASK);

    ctrlBase->CNTCR2 = reg;
}

/*!
 * brief De-initializes a System Counter instance.
 *
 * This function disables the System Counter module clock and sets all register values
 * to the reset value.
 *
 * param ctrlBase System Counter peripheral control model base address.
 * param cmpBase  System Counter peripheral compare model base address.
 */
void SYSCTR_Deinit(SYS_CTR_CONTROL_Type *ctrlBase, SYS_CTR_COMPARE_Type *cmpBase)
{
    SYSCTR_Reset(ctrlBase, cmpBase);

    (void)CLOCK_DisableClock(kCLOCK_Syscount);
}

/*!
 * brief Fill in the System Counter config struct with the default settings.
 *
 * The default values are:
 * code
 *   config->enableDebugHalt = false;
 *   config->enableHardwareFrequencyChange = false;
 * endcode
 * 
 * param pConfig Configuration pointer to user's System Counter config structure.
 */
void SYSCTR_GetDefaultConfig(sysctr_config_t *pConfig)
{
    pConfig->enableDebugHalt = false;
    pConfig->enableHardwareFrequencyChange = false;
}

/*!
 * brief Set System Counter clock source.
 * 
 * param base                  System Counter peripheral control model base address.
 * param sysctr_clock_source_t System Counter clock source.
 */
void SYSCTR_SetCounterClockSource(SYS_CTR_CONTROL_Type *base, sysctr_clock_source_t clockSource)
{
    uint32_t reg;

    if (clockSource == kSYSCTR_BaseFrequency)
    {
        reg = base->CNTCR;
        reg |= SYS_CTR_CONTROL_CNTCR_FCR0_MASK;
        reg &= ~SYS_CTR_CONTROL_CNTCR_FCR1_MASK;
        base->CNTCR = reg;
    }
    else
    {
        reg = base->CNTCR;
        reg &= ~SYS_CTR_CONTROL_CNTCR_FCR0_MASK;
        reg |= SYS_CTR_CONTROL_CNTCR_FCR1_MASK;
        base->CNTCR = reg;
    }
}

/*!
 * brief Enable or disable compare function of specific compare frame.
 * 
 * param base     System Counter peripheral control model base address.
 * param cmpFrame System Counter compare frame selection.
 * param enable   true: Enable compare function; false: Disable compare function
 */
void SYSCTR_EnableCompare(SYS_CTR_COMPARE_Type *base, sysctr_compare_frame_t cmpFrame, bool enable)
{
    uint32_t reg;

    if (cmpFrame == kSYSCTR_CompareFrame_0)
    {
        reg = base->CMPCR0;
        reg = enable ? (reg | SYS_CTR_COMPARE_CMPCR0_EN_MASK) :
                       (reg & ~SYS_CTR_COMPARE_CMPCR0_EN_MASK);
        base->CMPCR0 = reg;
    }
    else if (cmpFrame == kSYSCTR_CompareFrame_1)
    {
        reg = base->CMPCR1;
        reg = enable ? (reg | SYS_CTR_COMPARE_CMPCR1_EN_MASK) :
                       (reg & ~SYS_CTR_COMPARE_CMPCR1_EN_MASK);
        base->CMPCR1 = reg;
    }
    else
    {
        /* Intentional empty */
    }
}

/*!
 * brief Set System Counter compare value of specific compare frame.
 *
 * Be cautious that user must set compare value while operating on the base frequency only.
 * Set compare value while running on the alternate frequency may have unpredictable results.
 *
 * param ctrlBase System Counter peripheral control model base address.
 * param cmpBase  System Counter peripheral compare model base address.
 * param cmpFrame System Counter compare frame selection.
 * param value    System Counter compare value.
 */
void SYSCTR_SetCompareValue(SYS_CTR_CONTROL_Type *ctrlBase,
                            SYS_CTR_COMPARE_Type *cmpBase,
                            sysctr_compare_frame_t cmpFrame,
                            uint64_t value)
{
    assert((ctrlBase->CNTSR & SYS_CTR_CONTROL_CNTSR_FCA1_MASK) == 0);

    if (cmpFrame == kSYSCTR_CompareFrame_0)
    {
        cmpBase->CMPCVL0 = (uint32_t)(value & SYS_CTR_COMPARE_CMPCVL0_CMPCV0_MASK);
        cmpBase->CMPCVH0 = (uint32_t)((value >> 32U) & SYS_CTR_COMPARE_CMPCVH0_CMPCV1_MASK);
    }
    else if (cmpFrame == kSYSCTR_CompareFrame_1)
    {
        cmpBase->CMPCVL1 = (uint32_t)(value & SYS_CTR_COMPARE_CMPCVL1_CMPCV0_MASK);
        cmpBase->CMPCVH1 = (uint32_t)((value >> 32U) & SYS_CTR_COMPARE_CMPCVH1_CMPCV1_MASK);
    }
    else
    {
        /* Intentional empty */
    }
}

/*!
 * brief Get specific Frequency Modes Table value.
 * 
 * param base  System Counter peripheral control model base address.
 * param index Frequency Modes Table index.
 * 
 * return Frequency modes table value.
 */
uint32_t SYSCTR_GetFrequencyModesTableValue(SYS_CTR_CONTROL_Type *base, sysctr_frequency_modes_table_t index)
{
    uint32_t value = 0U;

    switch (index)
    {
        case kSYSCTR_FrequencyModesTable_0:
            value = base->CNTFID0;
            break;
        case kSYSCTR_FrequencyModesTable_1:
            value = base->CNTFID1;
            break;
        case kSYSCTR_FrequencyModesTable_2:
            value = base->CNTFID2;
            break;
        default:
            assert(false);
            break;
    }

    return value;
}
