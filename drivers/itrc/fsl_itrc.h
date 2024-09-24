/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_ITRC_H_
#define FSL_ITRC_H_

#include "fsl_common.h"

/*!
 * @addtogroup ITRC
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief Defines ITRC driver version 2.4.0.
 *
 * Change log:
 * - Version 2.4.0
 *   - Rework the input signal definition for better flexibility
 * - Version 2.3.0
 *   - Update names of kITRC_SwEvent1/2 to kITRC_SwEvent0/1 to align with RM
 * - Version 2.2.0
 *   - Update driver to new version and input events
 * - Version 2.1.0
 *   - Make SYSCON glitch platform dependent
 * - Version 2.0.0
 *   - initial version
 */
#define FSL_ITRC_DRIVER_VERSION (MAKE_VERSION(2, 4, 0))
/*! @} */

typedef enum _itrc_input_signals
{
#ifdef ITRC_OUT_SEL_IN0_SELn_MASK
    kITRC_In0 = 0U,
#endif
#ifdef ITRC_OUT_SEL_IN1_SELn_MASK
    kITRC_In1 = 1U,
#endif
#ifdef ITRC_OUT_SEL_IN2_SELn_MASK
    kITRC_In2 = 2U,
#endif
#ifdef ITRC_OUT_SEL_IN3_SELn_MASK
    kITRC_In3 = 3U,
#endif
#ifdef ITRC_OUT_SEL_IN4_SELn_MASK
    kITRC_In4 = 4U,
#endif
#ifdef ITRC_OUT_SEL_IN5_SELn_MASK
    kITRC_In5 = 5U,
#endif
#ifdef ITRC_OUT_SEL_IN6_SELn_MASK
    kITRC_In6 = 6U,
#endif
#ifdef ITRC_OUT_SEL_IN7_SELn_MASK
    kITRC_In7 = 7U,
#endif
#ifdef ITRC_OUT_SEL_IN8_SELn_MASK
    kITRC_In8 = 8U,
#endif
#ifdef ITRC_OUT_SEL_IN9_SELn_MASK
    kITRC_In9 = 9U,
#endif
#ifdef ITRC_OUT_SEL_IN10_SELn_MASK
    kITRC_In10 = 10U,
#endif
#ifdef ITRC_OUT_SEL_IN11_SELn_MASK
    kITRC_In11 = 11U,
#endif
#ifdef ITRC_OUT_SEL_IN12_SELn_MASK
    kITRC_In12 = 12U,
#endif
#ifdef ITRC_OUT_SEL_IN13_SELn_MASK
    kITRC_In13 = 13U,
#endif
#ifdef ITRC_OUT_SEL_IN14_SELn_MASK
    kITRC_In14 = 14U,
#endif
#ifdef ITRC_OUT_SEL_IN15_SELn_MASK
    kITRC_In15 = 15U,
#endif
#ifdef ITRC_OUT_SEL_1_IN16_SELn_MASK
    kITRC_In16 = 16U,
#endif
#ifdef ITRC_OUT_SEL_1_IN17_SELn_MASK
    kITRC_In17 = 17U,
#endif
#ifdef ITRC_OUT_SEL_1_IN18_SELn_MASK
    kITRC_In18 = 18U,
#endif
#ifdef ITRC_OUT_SEL_1_IN19_SELn_MASK
    kITRC_In19 = 19U,
#endif
#ifdef ITRC_OUT_SEL_1_IN20_SELn_MASK
    kITRC_In20 = 20U,
#endif
#ifdef ITRC_OUT_SEL_1_IN21_SELn_MASK
    kITRC_In21 = 21U,
#endif
#ifdef ITRC_OUT_SEL_1_IN22_SELn_MASK
    kITRC_In22 = 22U,
#endif
#ifdef ITRC_OUT_SEL_1_IN23_SELn_MASK
    kITRC_In23 = 23U,
#endif
#ifdef ITRC_OUT_SEL_1_IN24_SELn_MASK
    kITRC_In24 = 24U,
#endif
#ifdef ITRC_OUT_SEL_1_IN25_SELn_MASK
    kITRC_In25 = 25U,
#endif
#ifdef ITRC_OUT_SEL_1_IN26_SELn_MASK
    kITRC_In26 = 26U,
#endif
#ifdef ITRC_OUT_SEL_1_IN27_SELn_MASK
    kITRC_In27 = 27U,
#endif
#ifdef ITRC_OUT_SEL_1_IN28_SELn_MASK
    kITRC_In28 = 28U,
#endif
#ifdef ITRC_OUT_SEL_1_IN29_SELn_MASK
    kITRC_In29 = 29U,
#endif
#ifdef ITRC_OUT_SEL_1_IN30_SELn_MASK
    kITRC_In30 = 30U,
#endif
#ifdef ITRC_OUT_SEL_1_IN31_SELn_MASK
    kITRC_In31 = 31U,
#endif
#ifdef ITRC_OUT_SEL_2_IN32_SELn_MASK
    kITRC_In32 = 32U,
#endif
#ifdef ITRC_OUT_SEL_2_IN33_SELn_MASK
    kITRC_In33 = 33U,
#endif
#ifdef ITRC_OUT_SEL_2_IN34_SELn_MASK
    kITRC_In34 = 34U,
#endif
#ifdef ITRC_OUT_SEL_2_IN35_SELn_MASK
    kITRC_In35 = 35U,
#endif
#ifdef ITRC_OUT_SEL_2_IN36_SELn_MASK
    kITRC_In36 = 36U,
#endif
#ifdef ITRC_OUT_SEL_2_IN37_SELn_MASK
    kITRC_In37 = 37U,
#endif
#ifdef ITRC_OUT_SEL_2_IN38_SELn_MASK
    kITRC_In38 = 38U,
#endif
#ifdef ITRC_OUT_SEL_2_IN39_SELn_MASK
    kITRC_In39 = 39U,
#endif
#ifdef ITRC_OUT_SEL_2_IN40_SELn_MASK
    kITRC_In40 = 40U,
#endif
#ifdef ITRC_OUT_SEL_2_IN41_SELn_MASK
    kITRC_In41 = 41U,
#endif
#ifdef ITRC_OUT_SEL_2_IN42_SELn_MASK
    kITRC_In42 = 42U,
#endif
#ifdef ITRC_OUT_SEL_2_IN43_SELn_MASK
    kITRC_In43 = 43U,
#endif
#ifdef ITRC_OUT_SEL_2_IN44_SELn_MASK
    kITRC_In44 = 44U,
#endif
#ifdef ITRC_OUT_SEL_2_IN45_SELn_MASK
    kITRC_In45 = 45U,
#endif
#ifdef ITRC_OUT_SEL_2_IN46_SELn_MASK
    kITRC_In46 = 46U,
#endif
#ifdef ITRC_OUT_SEL_2_IN47_SELn_MASK
    kITRC_In47 = 47U,
#endif
} itrc_input_signals_t;

typedef enum _itrc_lock
{
    kITRC_Unlock = 0U,
    kITRC_Lock   = 1U,
} itrc_lock_t;

typedef enum _itrc_enable
{
    kITRC_Enable  = 0U,
    kITRC_Disable = 1U,
} itrc_enable_t;

typedef enum _itrc_out_signals
{
    kITRC_Irq        = 0U,
    kITRC_ElsReset   = 1U,
    kITRC_PufZeroize = 2U,
    kITRC_RamZeroize = 3u,
    kITRC_ChipReset  = 4u,
    kITRC_TamperOut  = 5u,
    kITRC_TamperOut1 = 6u,
} itrc_out_signals_t;

/* Macros to avoid build failures because some platforms don't implement some IN signals */
#ifndef ITRC_STATUS_IN2_STATUS_MASK
#define ITRC_STATUS_IN2_STATUS_MASK (0u)
#endif

#ifndef ITRC_STATUS_IN3_STATUS_MASK
#define ITRC_STATUS_IN3_STATUS_MASK (0u)
#endif

#ifndef ITRC_STATUS_IN9_STATUS_MASK
#define ITRC_STATUS_IN9_STATUS_MASK (0u)
#endif

#ifndef ITRC_STATUS1_IN17_STATUS_MASK
#define ITRC_STATUS1_IN17_STATUS_MASK (0u)
#endif

#ifndef ITRC_STATUS1_IN19_STATUS_MASK
#define ITRC_STATUS1_IN19_STATUS_MASK (0u)
#endif

#ifndef ITRC_STATUS1_IN24_21_STATUS_MASK
#define ITRC_STATUS1_IN24_21_STATUS_MASK (0u)
#endif

#ifndef ITRC_STATUS1_IN32_25_STATUS_MASK
#define ITRC_STATUS1_IN32_25_STATUS_MASK (0u)
#endif

#ifndef ITRC_STATUS1_IN46_STATUS_MASK
#define ITRC_STATUS1_IN46_STATUS_MASK (0u)
#endif

/* Inputs 0 to 15 events mask */
#define IN_0_15_EVENTS_MASK                                                                      \
    (ITRC_STATUS_IN0_STATUS_MASK | ITRC_STATUS_IN1_STATUS_MASK | ITRC_STATUS_IN2_STATUS_MASK |   \
     ITRC_STATUS_IN3_STATUS_MASK | ITRC_STATUS_IN4_STATUS_MASK | ITRC_STATUS_IN5_STATUS_MASK |   \
     ITRC_STATUS_IN6_STATUS_MASK | ITRC_STATUS_IN7_STATUS_MASK | ITRC_STATUS_IN8_STATUS_MASK |   \
     ITRC_STATUS_IN9_STATUS_MASK | ITRC_STATUS_IN10_STATUS_MASK | ITRC_STATUS_IN14_STATUS_MASK | \
     ITRC_STATUS_IN15_STATUS_MASK)

/* Inputs 15 to 47 events mask */
#if defined(ITRC_STATUS1_IN16_STATUS_MASK) && defined(ITRC_STATUS1_IN47_STATUS)
#define IN_16_47_EVENTS_MASK                                                                            \
    (ITRC_STATUS1_IN16_STATUS_MASK | ITRC_STATUS1_IN17_STATUS_MASK | ITRC_STATUS1_IN18_STATUS_MASK |    \
     ITRC_STATUS1_IN19_STATUS_MASK | ITRC_STATUS1_IN20_STATUS_MASK | ITRC_STATUS1_IN24_21_STATUS_MASK | \
     ITRC_STATUS1_IN32_25_STATUS_MASK | ITRC_STATUS1_IN33_STATUS_MASK | ITRC_STATUS1_IN34_STATUS_MASK | \
     ITRC_STATUS1_IN35_STATUS_MASK | ITRC_STATUS1_IN36_STATUS_MASK | ITRC_STATUS1_IN37_STATUS_MASK |    \
     ITRC_STATUS1_IN46_STATUS_MASK | ITRC_STATUS1_IN47_STATUS_MASK)
#endif /* ITRC_STATUS1_IN16_STATUS_MASK && ITRC_STATUS1_IN47_STATUS */

/* Output actions mask */
#if defined(ITRC_STATUS_OUT6_STATUS)
#define OUT_ACTIONS_MASK                                                                          \
    (ITRC_STATUS_OUT0_STATUS_MASK | ITRC_STATUS_OUT1_STATUS_MASK | ITRC_STATUS_OUT2_STATUS_MASK | \
     ITRC_STATUS_OUT3_STATUS_MASK | ITRC_STATUS_OUT4_STATUS_MASK | ITRC_STATUS_OUT5_STATUS_MASK | \
     ITRC_STATUS_OUT6_STATUS_MASK)
#else
#define OUT_ACTIONS_MASK                                                                          \
    (ITRC_STATUS_OUT0_STATUS_MASK | ITRC_STATUS_OUT1_STATUS_MASK | ITRC_STATUS_OUT2_STATUS_MASK | \
     ITRC_STATUS_OUT3_STATUS_MASK | ITRC_STATUS_OUT4_STATUS_MASK | ITRC_STATUS_OUT5_STATUS_MASK)
#endif /* ITRC_STATUS_OUT6_STATUS */

#define ITRC_OUT_COUNT (7u)
#ifndef ITRC
#define ITRC ITRC0
#endif

/*******************************************************************************
 * API
 *******************************************************************************/

extern void ITRC0_DriverIRQHandler(void);

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @name ITRC Functional Operation
 * @{
 */

/*!
 * @brief Set ITRC Action to Event
 *
 * This function sets input Event signal to corresponding output Action response signal.
 *
 * @param base ITRC peripheral base address
 * @param out ITRC OUT signal action
 * @param in ITRC IN signal event
 * @param lock if set locks INx_SEL configuration. This can be cleared only by PMC Core reset.
 * @param enable if set input Event will be selected for output Action, otherwise disable (if not already locked).
 * @return kStatus_Success if success, kStatus_InvalidArgument otherwise
 */
status_t ITRC_SetActionToEvent(
    ITRC_Type *base, itrc_out_signals_t out, itrc_input_signals_t in, itrc_lock_t lock, itrc_enable_t enable);

/*!
 * @brief Trigger ITRC SW Event 0
 *
 * This funciton set SW_EVENT0 register with value !=0 which triggers ITRC SW Event 0.
 *
 * @param base ITRC peripheral base address
 */
void ITRC_SetSWEvent0(ITRC_Type *base);

/*!
 * @brief Trigger ITRC SW Event 1
 *
 * This funciton set SW_EVENT1 register with value !=0 which triggers ITRC SW Event 1.
 *
 * @param base ITRC peripheral base address
 */
void ITRC_SetSWEvent1(ITRC_Type *base);

/*!
 * @brief Get ITRC Status
 *
 * This function returns ITRC register status.
 *
 * @param base ITRC peripheral base address
 * @return Value of ITRC STATUS register
 */
uint32_t ITRC_GetStatus(ITRC_Type *base);

/*!
 * @brief Clear ITRC status
 *
 * This function clears corresponding ITRC event or action in STATUS register.
 *
 * @param base ITRC peripheral base address
 * @param word 32bit word represent corresponding event/action in STATUS register to be cleared (see
 * ITRC_STATUS_INx/OUTx_STATUS)
 * @return kStatus_Success if success, kStatus_InvalidArgument otherwise
 */
status_t ITRC_ClearStatus(ITRC_Type *base, uint32_t word);

#if defined(ITRC_STATUS1_IN16_STATUS_MASK)
/*!
 * @brief Get ITRC Status 1
 *
 * This function returns ITRC STATUS1 register value.
 *
 * @param base ITRC peripheral base address
 * @return Value of ITRC STATUS1 register
 */
uint32_t ITRC_GetStatus1(ITRC_Type *base);

/*!
 * brief Clear ITRC status 1
 *
 * This function clears corresponding ITRC event or action in STATUS1 register.
 *
 * param base ITRC peripheral base address
 * param word 32bit word represent corresponding event/action in STATUS1 register to be cleared (see
 * ITRC_STATUS_INx/OUTx_STATUS)
 * return kStatus_Success if success, kStatus_InvalidArgument otherwise
 */
status_t ITRC_ClearStatus1(ITRC_Type *base, uint32_t word);
#endif /* defined(ITRC_STATUS1_IN16_STATUS_MASK) */

/*!
 * @brief Clear All ITRC status
 *
 * This function clears all event and action status.
 *
 * @param base ITRC peripheral base address
 * @return kStatus_Success if success
 */
status_t ITRC_ClearAllStatus(ITRC_Type *base);

/*!
 * @brief Initialize ITRC
 *
 * This function initializes ITRC by enabling IRQ.
 *
 * @param base ITRC peripheral base address
 * @param conf ITRC configuration structure
 * @return Status of the init operation
 */
status_t ITRC_Init(ITRC_Type *base);

/*!
 * @brief Deinitialize ITRC
 *
 * This function deinitializes ITRC by disabling IRQ.
 *
 * @param base ITRC peripheral base address
 */
void ITRC_Deinit(ITRC_Type *base);

/*! @}*/

#if defined(__cplusplus)
}
#endif   /* __cplusplus */

/*! @}*/ /* end of group itrc */

#endif   /* FSL_ITRC_H_ */
