/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef RISCV_INTERRUPT_H_
#define RISCV_INTERRUPT_H_

/*!
 * @ingroup RISCV_CoreFunc
 * @defgroup RISCV_CoreInt Definition For Interrupts
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @name Interrupts
 * @{
 */
#define RV_INT_U_SOFTWARE 0U  /*!< User software interrupt */
#define RV_INT_S_SOFTWARE 1U  /*!< Supervisor software interrupt */
#define RV_INT_H_SOFTWARE 2U  /*!< Reserved for HyperVisor mode */
#define RV_INT_M_SOFTWARE 3U  /*!< Machine software interrupt */
#define RV_INT_U_TIMER    4U  /*!< User timer interrupt */
#define RV_INT_S_TIMER    5U  /*!< Supervisor timer interrupt */
#define RV_INT_H_TIMER    6U  /*!< Reserved for HyperVisor mode */
#define RV_INT_M_TIMER    7U  /*!< Machine timer interrupt */
#define RV_INT_U_EXT      8U  /*!< User external interrupt */
#define RV_INT_S_EXT      9U  /*!< Supervisor external interrupt */
#define RV_INT_H_EXT      10U /*!< Reserved for Hypervisor mode */
#define RV_INT_M_EXT      11U /*!< Machine external interrupt */

/*!
 * @}
 */

/*!
 * @name Fault exceptions
 * @{
 */

#define RV_EXC_MISALIGNED_FETCH    0U   /*!< misaligned fetch */
#define RV_EXC_FETCH_ACCESS        1U   /*!< fetch access */
#define RV_EXC_ILLLEGAL_INS        2U   /*!< illegal instructions */
#define RV_EXC_BREAKPOINT          3U   /*!< Breakpoint */
#define RV_EXC_MISALIGNED_LOAD     4U   /*!< misaligned load */
#define RV_EXC_LOAD_ACCESS         5U   /*!< load access fault */
#define RV_EXC_MISALIGNED_STORE    6U   /*!< misaligned store */
#define RV_EXC_STORE_ACCESS        7U   /*!< sotre access fault */
#define RV_EXC_U_ECALL             8U   /*!< environment call from U-mode */
#define RV_EXC_S_ECALL             9U   /*!< environment call from S-mode */
#define RV_EXC_H_ECALL             10U  /*!< environment call from Hyper-mode*/
#define RV_EXC_M_ECALL             11U  /*!< environment call from machine */
#define RV_EXC_FETCH_PAGE_FAULT    12U  /*!< instruction page fault */
#define RV_EXC_LOAD_PAGE_FAULT     13U  /*!< load page fault */
#define RV_EXC_STORE_PAGE_FAULT    15U  /*!< store/AMO page fault */

/*!
 * @}
 */

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

/*!
 * @}
 */ /* End of group RISCV_CoreInt */

#endif /* RISCV_INTERRUPT_H_ */
