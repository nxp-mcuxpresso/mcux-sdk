/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_SYSCTR_H_
#define FSL_SYSCTR_H_

#include "fsl_common.h"

/*!
 * @addtogroup sysctr
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @name Driver version */
/*! @{ */
/*! @brief System Counter driver version. */
#define FSL_SYSCTR_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*! @{ */

/*! @brief System Counter clock source selection. */
typedef enum _sysctr_clock_source
{
    kSYSCTR_BaseFrequency = 0U,     /*!< 24MHz base clock from crystal oscillator is used as the clock. */
    kSYSCTR_AlternateFrequency      /*!< 32kHz alternate slow clock from crystal oscillator is used as the clock. */
} sysctr_clock_source_t;

/*! @brief System Counter compare frame selection. */
typedef enum _sysctr_compare_frame
{
    kSYSCTR_CompareFrame_0 = 0U,        /*!< Select compare frame 0. */
    kSYSCTR_CompareFrame_1              /*!< Select compare frame 1. */
} sysctr_compare_frame_t;

/*! @brief System Counter frequency modes table selection. */
typedef enum _sysctr_frequency_modes_table
{
    kSYSCTR_FrequencyModesTable_0 = 0U,     /*!< Select frequency modes table 0. */
    kSYSCTR_FrequencyModesTable_1,          /*!< Select frequency modes table 1. */
    kSYSCTR_FrequencyModesTable_2           /*!< Select frequency modes table 2. */
} sysctr_frequency_modes_table_t;

/*! @brief List of System Counter interrupt options. */
typedef enum _sysctr_interrupt_enable
{
    kSYSCTR_Compare0InterruptEnable = SYS_CTR_COMPARE_CMPCR0_IMASK_MASK,            /*!< Compare frame 0 interrupt. */
    kSYSCTR_Compare1InterruptEnable = SYS_CTR_COMPARE_CMPCR1_IMASK_MASK << 16U      /*!< Compare frame 1 interrupt. */
} sysctr_interrupt_enable_t;

/*! @brief List of System Counter status flags. */
typedef enum _sysctr_status_flags
{
    kSYSCTR_Compare0Flag = SYS_CTR_COMPARE_CMPCR0_ISTAT_MASK,               /*!< Compare frame 0 compare flag. */
    kSYSCTR_Compare1Flag = SYS_CTR_COMPARE_CMPCR1_ISTAT_MASK << 16U         /*!< Compare frame 1 compare flag. */
} sysctr_status_flags_t;

/*!
 * @brief System Counter config structure
 *
 * This structure holds the configuration settings for the System Counter peripheral.
 * To initialize this structure to reasonable defaults, call the PWM_GetDefaultConfig()
 * function and pass a pointer to your config structure instance.
 */
typedef struct _sysctr_config
{
    bool enableDebugHalt;                       /*!< true: Debug input causes the System Counter to halt;
                                                     false: Debug input is ignored */
    bool enableHardwareFrequencyChange;         /*!< true: Hardware changes frequency automatically when entering
                                                           or exiting low power mode;
                                                     false: Frequency changes are fully under software control */
} sysctr_config_t;

/*!
 * @brief System Counter status flags.
 *
 * This provides constants for the System Counter status flags for use in the System Counter functions.
 * The system counter status flags provide information concerning the clock frequency and debug state.
 */
enum _sysctr_flags
{
    kSYSCTR_DebugHalt = SYS_CTR_CONTROL_CNTSR_DBGH_MASK,
    kSYSCTR_FrequencyChangeAck_0 = SYS_CTR_CONTROL_CNTSR_FCA0_MASK,
    kSYSCTR_FrequencyChangeAck_1 = SYS_CTR_CONTROL_CNTSR_FCA1_MASK
};

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Initializes a System Counter instance.
 *
 * This function initializes the System Counter module with user-defined settings.
 * This example shows how to set up the sysctr_config_t parameters and how to call
 * the SYSCTR_Init function by passing in these parameters. Default clock source
 * is 24MHz base clock from crystal oscillator.
 * @code
 *   sysctr_config_t sysctrConfig;
 *   sysctrConfig.enableDebugHalt               = false;
 *   sysctrConfig.enableHardwareFrequencyChange = false;
 *   SYSCTR_Init(SYS_CTR_CONTROL, SYS_CTR_COMPARE, &sysctr_config_t);
 * @endcode
 *
 * @param ctrlBase System Counter peripheral control model base address.
 * @param cmpBase  System Counter peripheral compare model base address.
 * @param pConfig  Configuration pointer to user's System Counter config structure.
 */
void SYSCTR_Init(SYS_CTR_CONTROL_Type *ctrlBase, SYS_CTR_COMPARE_Type *cmpBase, const sysctr_config_t *pConfig);

/*!
 * @brief De-initializes a System Counter instance.
 *
 * This function disables the System Counter module clock and sets all register values
 * to the reset value.
 *
 * @param ctrlBase System Counter peripheral control model base address.
 * @param cmpBase  System Counter peripheral compare model base address.
 */
void SYSCTR_Deinit(SYS_CTR_CONTROL_Type *ctrlBase, SYS_CTR_COMPARE_Type *cmpBase);

/*!
 * @brief Fill in the System Counter config struct with the default settings.
 *
 * The default values are:
 * @code
 *   config->enableDebugHalt = false;
 *   config->enableHardwareFrequencyChange = false;
 * @endcode
 * 
 * @param pConfig Configuration pointer to user's System Counter config structure.
 */
void SYSCTR_GetDefaultConfig(sysctr_config_t *pConfig);

/*! @}*/

/*!
 * @name Interrupts Interface
 * @{
 */

/*!
 * @brief Enables the selected System Counter interrupts
 *
 * @param base System Counter peripheral compare model base address.
 * @param mask The interrupts to enable. This is a logical OR of members of the
 *             enumeration ::sysctr_interrupt_enable_t.
 */
static inline void SYSCTR_EnableInterrupts(SYS_CTR_COMPARE_Type *base, uint32_t mask)
{
    base->CMPCR0 &= ~(mask & SYS_CTR_COMPARE_CMPCR0_IMASK_MASK);
    base->CMPCR1 &= ~((mask >> 16U) & SYS_CTR_COMPARE_CMPCR1_IMASK_MASK);
}

/*!
 * @brief Disable the selected System Counter interrupts
 *
 * @param base System Counter peripheral compare model base address.
 * @param mask The interrupts to disable. This is a logical OR of members of the
 *             enumeration ::sysctr_interrupt_enable_t.
 */
static inline void SYSCTR_DisableInterrupts(SYS_CTR_COMPARE_Type *base, uint32_t mask)
{
    base->CMPCR0 |= mask & SYS_CTR_COMPARE_CMPCR0_IMASK_MASK;
    base->CMPCR1 |= ((mask >> 16U) & SYS_CTR_COMPARE_CMPCR1_IMASK_MASK);
}

/*! @}*/

/*!
 * @name Status Interface
 * @{
 */

/*!
 * @brief Get System Counter status flags
 *
 * @param base System Counter peripheral compare model base address.
 *
 * @return The status flags. This is the logical OR of members of the
 *         enumeration ::sysctr_status_flags_t.
 */
static inline uint32_t SYSCTR_GetStatusFlags(SYS_CTR_COMPARE_Type *base)
{
    uint32_t statusFlags;

    statusFlags = base->CMPCR0 & SYS_CTR_COMPARE_CMPCR0_ISTAT_MASK;
    statusFlags |= ((base->CMPCR1 & SYS_CTR_COMPARE_CMPCR1_ISTAT_MASK) << 16U);

    return statusFlags;
}

/*! @}*/

/*!
 * @name Counter Start and Stop
 * @{
 */

/*!
 * @brief Enables the System Counter counting.
 *
 * @param base System Counter peripheral control model base address.
 */
static inline void SYSCTR_StartCounter(SYS_CTR_CONTROL_Type *base)
{
    base->CNTCR |= SYS_CTR_CONTROL_CNTCR_EN_MASK;
}

/*!
 * @brief Disables the System Counter counting.
 *
 * @param base System Counter peripheral control model base address.
 */
static inline void SYSCTR_StopCounter(SYS_CTR_CONTROL_Type *base)
{
    base->CNTCR &= ~SYS_CTR_CONTROL_CNTCR_EN_MASK;
}

/*! @}*/

/*!
 * @brief Set System Counter count value.
 *
 * User can set System Counter initial count value before starting counter.
 * Be cautious that user must set count value while operating on the base frequency only.
 * Set count value while running on the alternate frequency may have unpredictable results.
 *
 * @param base  System Counter peripheral control model base address.
 * @param value System Counter count value.
 */
static inline void SYSCTR_SetCounterlValue(SYS_CTR_CONTROL_Type *base, uint64_t value)
{
    assert((base->CNTSR & SYS_CTR_CONTROL_CNTSR_FCA1_MASK) == 0);

    base->CNTCV0 = (uint32_t)(value & SYS_CTR_CONTROL_CNTCV0_CNTCV0_MASK); 
    base->CNTCV1 = (uint32_t)((value >> 32U) & SYS_CTR_CONTROL_CNTCV1_CNTCV1_MASK);
}

/*!
 * @brief Get System Counter current count value.
 *
 * @param base System Counter peripheral read model base address.
 * 
 * @return System Counter current count value.
 */
static inline uint64_t SYSCTR_GetCounterlValue(SYS_CTR_READ_Type *base)
{
    uint64_t value;

    value = base->CNTCV0;
    value |= ((uint64_t)base->CNTCV1 << 32U);

    return value;
}

/*!
 * @brief Set System Counter clock source.
 * 
 * @param base                  System Counter peripheral control model base address.
 * @param sysctr_clock_source_t System Counter clock source.
 */
void SYSCTR_SetCounterClockSource(SYS_CTR_CONTROL_Type *base, sysctr_clock_source_t clockSource);

/*!
 * @brief Enable or disable compare function of specific compare frame.
 * 
 * @param base     System Counter peripheral control model base address.
 * @param cmpFrame System Counter compare frame selection.
 * @param enable   true: Enable compare function; false: Disable compare function
 */
void SYSCTR_EnableCompare(SYS_CTR_COMPARE_Type *base, sysctr_compare_frame_t cmpFrame, bool enable);

/*!
 * @brief Set System Counter compare value of specific compare frame.
 *
 * Be cautious that user must set compare value while operating on the base frequency only.
 * Set compare value while running on the alternate frequency may have unpredictable results.
 *
 * @param ctrlBase System Counter peripheral control model base address.
 * @param cmpBase  System Counter peripheral compare model base address.
 * @param cmpFrame System Counter compare frame selection.
 * @param value    System Counter compare value.
 */
void SYSCTR_SetCompareValue(SYS_CTR_CONTROL_Type *ctrlBase,
                            SYS_CTR_COMPARE_Type *cmpBase,
                            sysctr_compare_frame_t cmpFrame,
                            uint64_t value);

/*!
 * @brief Get specific Frequency Modes Table value.
 * 
 * @param base  System Counter peripheral control model base address.
 * @param index Frequency Modes Table index.
 * 
 * @return Frequency modes table value.
 */
uint32_t SYSCTR_GetFrequencyModesTableValue(SYS_CTR_CONTROL_Type *base, sysctr_frequency_modes_table_t index);


#if defined(__cplusplus)
}
#endif

#endif
