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
/*! @brief Defines ITRC driver version 2.0.0.
 *
 * Change log:
 * - Version 2.0.0
 *   - Initial version.
 */
#define FSL_ITRC_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*! @} */

#define ITRC_INPUT_SIGNALS_NUM (22u)

/*! @brief ITRC input events. */
typedef uint32_t itrc_in_signals_t;
#define kITRC_CauTemeprature    0U
#define kITRC_PmipTemperature   1U
#define kITRC_VddCore           2U
#define kITRC_Vdd18             3u
#define kITRC_Vdd33             4u
#define kITRC_VddCoreGlitch     5u
#define kITRC_AnalogSensor      6u
#define kITRC_Ahb               7u
#define kITRC_Cwd               8u
#define kITRC_Css               9u
#define kITRC_Pkc               10u
#define kITRC_Otp               11u
#define kITRC_Prince            12u
#define kITRC_ClockGlitch       13u
#define kITRC_SecurityIP        14u
#define kITRC_Trng              15u
#define kITRC_PmipGlitch        16u
#define kITRC_PmipVddCoreGlitch 17u
#define kITRC_TcpuPll           18u
#define kITRC_T3Pll             19u
#define kITRC_SwEvent0          20u
#define kITRC_SwEvent1          21u

/*! @brief ITRC output actions. */
typedef uint32_t itrc_out_signals_t;
#define kITRC_Irq       16U
#define kITRC_ChipReset 17u

/*! @brief ITRC lock/unlock. */
typedef uint32_t itrc_lock_t;
#define  kITRC_Unlock 0U
#define  kITRC_Lock   1U

/*! @brief ITRC enable/disable. */
typedef uint32_t itrc_enable_t;
#define kITRC_Enable  0U
#define kITRC_Disable 1U

#define IN_STATUS0_EVENTS_MASK                                                                       \
    (ITRC_STATUS0_IN0_STATUS_MASK | ITRC_STATUS0_IN1_STATUS_MASK | ITRC_STATUS0_IN2_STATUS_MASK |    \
     ITRC_STATUS0_IN3_STATUS_MASK | ITRC_STATUS0_IN4_STATUS_MASK | ITRC_STATUS0_IN5_STATUS_MASK |    \
     ITRC_STATUS0_IN6_STATUS_MASK | ITRC_STATUS0_IN7_STATUS_MASK | ITRC_STATUS0_IN8_STATUS_MASK |    \
     ITRC_STATUS0_IN9_STATUS_MASK | ITRC_STATUS0_IN10_STATUS_MASK | ITRC_STATUS0_IN11_STATUS_MASK |  \
     ITRC_STATUS0_IN12_STATUS_MASK | ITRC_STATUS0_IN13_STATUS_MASK | ITRC_STATUS0_IN14_STATUS_MASK | \
     ITRC_STATUS0_IN15_STATUS_MASK)

#define IN_STATUS1_EVENTS_MASK                                                                       \
    (ITRC_STATUS1_IN16_STATUS_MASK | ITRC_STATUS1_IN17_STATUS_MASK | ITRC_STATUS1_IN18_STATUS_MASK | \
     ITRC_STATUS1_IN19_STATUS_MASK | ITRC_STATUS1_IN20_STATUS_MASK | ITRC_STATUS1_IN21_STATUS_MASK)

#define OUT_ACTIONS_MASK (ITRC_STATUS0_OUT0_STATUS_MASK | ITRC_STATUS0_OUT1_STATUS_MASK)

#ifndef ITRC
#define ITRC ITRC0
#endif

/*******************************************************************************
 * API
 *******************************************************************************/

extern void ITRC_DriverIRQHandler(void);

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
    ITRC_Type *base, itrc_out_signals_t out, itrc_in_signals_t in, itrc_lock_t lock, itrc_enable_t enable);

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
 * @brief Get ITRC input event status
 *
 * This function returns ITRC status corresponding to provided input event.
 *
 * @param base ITRC peripheral base address
 * @param event represents input event to get from STATUS register
 * (see ITRC_STATUS_INx)
 * @return boolean TRUE if corresponding event occured
 *                 FALSE otherwise
 */
bool ITRC_GetInEventStatus(ITRC_Type *base, itrc_in_signals_t event);

/*!
 * @brief Get ITRC output action status
 *
 * This function returns ITRC register output status.
 *
 * @param base ITRC peripheral base address
 * @param action represents output action to get from STATUS register
 * (see ITRC_STATUS_OUTx)
 * @return boolean TRUE if corresponding action occured
 *                 FALSE otherwise
 */
bool ITRC_GetOutActionStatus(ITRC_Type *base, itrc_out_signals_t action);

/*!
 * @brief Clear In ITRC status
 *
 * This function clears corresponding ITRC event or action in input STATUS register.
 *
 * @param base ITRC peripheral base address
 * @param event represents input event in STATUS register to be cleared
 *              (see ITRC_STATUS_INx)
 * @return kStatus_Success if success, kStatus_InvalidArgument otherwise
 */
status_t ITRC_ClearInEventStatus(ITRC_Type *base, itrc_in_signals_t event);

/*!
 * @brief Clear Out ITRC status
 *
 * This function clears corresponding ITRC event or action in output STATUS register.
 *
 * @param base ITRC peripheral base address
 * @param action represents output action in STATUS register to be cleared
 *               (see OUTx_STATUS)
 * @return kStatus_Success if success, kStatus_InvalidArgument otherwise
 */
status_t ITRC_ClearOutActionStatus(ITRC_Type *base, itrc_out_signals_t action);

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
#endif /* __cplusplus */

/*! @}*/ /* end of group itrc */

#endif /* FSL_ITRC_H_ */
