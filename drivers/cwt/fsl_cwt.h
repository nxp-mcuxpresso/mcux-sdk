/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_CWT_H_
#define _FSL_CWT_H_

#include "fsl_common.h"

/*!
 * @addtogroup cwt
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief Defines CWT driver version 2.0.2.
 *
 * Change log:
 * - Version 2.0.2
 *   - Fix MISRA-2012 issues
 * - Version 2.0.1
 *   - Fix doxygen issues
 * - Version 2.0.0
 *   - initial version
 */
#define FSL_CWT_DRIVER_VERSION (MAKE_VERSION(2, 0, 2))
/*@}*/

typedef struct
{
    uint8_t lock : 2;
    uint8_t timeout : 3;
    uint8_t miscompare : 3;
    uint8_t sequence : 3;
    uint8_t control : 3;
    uint8_t state : 3;
    uint8_t address : 3;
    uint8_t reserved : 8;
    uint8_t irq_pause : 2;
    uint8_t debug_halt : 2;
} cwt_config_t;

enum __cdog_debug_Action_ctrl_enum
{
    kCDOG_DebugHaltCtrl_Run   = 0x1,
    kCDOG_DebugHaltCtrl_Pause = 0x2,
};

enum __cdog_irq_pause_ctrl_enum
{
    kCDOG_IrqPauseCtrl_Run   = 0x1,
    kCDOG_IrqPauseCtrl_Pause = 0x2,
};

enum __cdog_fault_ctrl_enum
{
    kCDOG_FaultCtrl_EnableReset     = 0x1U,
    kCDOG_FaultCtrl_EnableInterrupt = 0x2U,
    kCDOG_FaultCtrl_NoAction        = 0x4U,
};

enum __code_lock_ctrl_enum
{
    kCDOG_LockCtrl_Lock   = 0x1,
    kCDOG_LockCtrl_Unlock = 0x2,
};

typedef uint32_t secure_counter_t;

#define SC_ADD(add)                          \
    do                                       \
    {                                        \
        CDOG->ADD = (secure_counter_t)(add); \
    } while (0)

#define SC_ADD1                              \
    do                                       \
    {                                        \
        CDOG->ADD1 = (secure_counter_t)0x1U; \
    } while (0)

#define SC_ADD16                              \
    do                                        \
    {                                         \
        CDOG->ADD16 = (secure_counter_t)0x1U; \
    } while (0)

#define SC_ADD256                              \
    do                                         \
    {                                          \
        CDOG->ADD256 = (secure_counter_t)0x1U; \
    } while (0)

#define SC_SUB(sub)                          \
    do                                       \
    {                                        \
        CDOG->SUB = (secure_counter_t)(sub); \
    } while (0)

#define SC_SUB1                              \
    do                                       \
    {                                        \
        CDOG->SUB1 = (secure_counter_t)0x1U; \
    } while (0)

#define SC_SUB16                              \
    do                                        \
    {                                         \
        CDOG->SUB16 = (secure_counter_t)0x1U; \
    } while (0)

#define SC_SUB256                              \
    do                                         \
    {                                          \
        CDOG->SUB256 = (secure_counter_t)0x1U; \
    } while (0)

#define SC_CHECK(val)                          \
    do                                         \
    {                                          \
        CDOG->RESTART = (secure_counter_t)val; \
    } while (0)

/*******************************************************************************
 * API
 *******************************************************************************/

extern void CodeWDG_DriverIRQHandler(void);

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @name CWT Functional Operation
 * @{
 */

/*!
 * @brief Initialize CWT
 *
 * This function initializes CWT block and setting.
 *
 * @param base CWT peripheral base address
 * @param conf CWT configuration structure
 * @return Status of the init operation
 */
status_t CWT_Init(CDOG_Type *base, cwt_config_t *conf);

/*!
 * @brief Deinitialize CWT
 *
 * This function deinitializes CWT secure counter.
 *
 * @param base CWT peripheral base address
 */
void CWT_Deinit(CDOG_Type *base);

/*!
 * @brief Sets the default configuration of CWT
 *
 * This function initialize CWT config structure to default values.
 *
 * @param conf CWT configuration structure
 */
void CWT_GetDefaultConfig(cwt_config_t *conf);

/*!
 * @brief Stops secure counter and instruction timer
 *
 * This function stops instruction timer and secure counter.
 * This also change state od CWT to IDLE.
 *
 * @param base CWT peripheral base address
 * @param stop expected value which will be compared with value of secure counter
 */
void CWT_Stop(CDOG_Type *base, uint32_t stop);

/*!
 * @brief Sets secure counter and instruction timer values
 *
 * This function sets value in RELOAD and START registers
 * for instruction timer and secure counter
 *
 * @param base CWT peripheral base address
 * @param reload reload value
 * @param start start value
 */
void CWT_Start(CDOG_Type *base, uint32_t reload, uint32_t start);

/*!
 * @brief Checks secure counter.
 *
 * This function compares stop value in handler with secure counter value
 * by writting to RELOAD refister.
 *
 * @param base CWT peripheral base address
 * @param check expected (stop) value
 */
void CWT_Check(CDOG_Type *base, uint32_t check);

/*!
 * @brief Sets secure counter and instruction timer values
 *
 * This function sets value in STOP, RELOAD and START registers
 * for instruction timer and secure counter.
 *
 * @param base CWT peripheral base address
 * @param stop expected value which will be compared with value of secure counter
 * @param reload reload value for instruction timer
 * @param start start value for secure timer
 */
void CWT_Set(CDOG_Type *base, uint32_t stop, uint32_t reload, uint32_t start);

/*!
 * @brief Add value to secure counter
 *
 * This function add specified value to secure counter.
 *
 * @param base CWT peripheral base address.
 * @param add Value to be added.
 */
void CWT_Add(CDOG_Type *base, uint32_t add);

/*!
 * @brief Add 1 to secure counter
 *
 * This function add 1 to secure counter.
 *
 * @param base CWT peripheral base address.
 */
void CWT_Add1(CDOG_Type *base);

/*!
 * @brief Add 16 to secure counter
 *
 * This function add 16 to secure counter.
 *
 * @param base CWT peripheral base address.
 */
void CWT_Add16(CDOG_Type *base);

/*!
 * @brief Add 256 to secure counter
 *
 * This function add 256 to secure counter.
 *
 * @param base CWT peripheral base address.
 */
void CWT_Add256(CDOG_Type *base);

/*!
 * brief Substract value to secure counter
 *
 * This function substract specified value to secure counter.
 *
 * param base CWT peripheral base address.
 * param sub Value to be substracted.
 */
void CWT_Sub(CDOG_Type *base, uint32_t sub);

/*!
 * @brief Substract 1 from secure counter
 *
 * This function substract specified 1 from secure counter.
 *
 * @param base CWT peripheral base address.
 */
void CWT_Sub1(CDOG_Type *base);

/*!
 * @brief Substract 16 from secure counter
 *
 * This function substract specified 16 from secure counter.
 *
 * @param base CWT peripheral base address.
 */
void CWT_Sub16(CDOG_Type *base);

/*!
 * @brief Substract 256 from secure counter
 *
 * This function substract specified 256 from secure counter.
 *
 * @param base CWT peripheral base address.
 */
void CWT_Sub256(CDOG_Type *base);

/*!
 * @brief Set the CWT persistent word.
 *
 * @param base CWT peripheral base address.
 * @param value The value to be written.
 */
void CWT_WritePersistent(CDOG_Type *base, uint32_t value);

/*!
 * @brief Get the CWT persistent word.
 *
 * @param base CWT peripheral base address.
 * @return The persistent word.
 */
uint32_t CWT_ReadPersistent(CDOG_Type *base);

/*! @}*/

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @}*/ /* end of group cwt */

#endif /* _FSL_CWT_H_ */
