/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_GDET_H_
#define FSL_GDET_H_

#include "fsl_common.h"

/*!
 * @addtogroup GDET
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief Defines GDET driver version 2.1.0.
 *
 * Change log:
 *
 * - Version 2.1.0
 *   - Update for multiple instances
 *   - Fix bug in isolation off API
 *   - Add enable and disable APIs
 *
 * - 2.0.1
 *   - Fix MISRA in GDET_ReconfigureVoltageMode()
 *
 * - Version 2.0.0
 *   - initial version
 */
#define FSL_GDET_DRIVER_VERSION (MAKE_VERSION(2, 1, 0))
/*! @} */

/*!
 * @brief GDET Core Voltage.
 *
 * These constants are used to define core voltage argument to be used with
 * GDET_ReconfigureVoltageMode(). Different SoC may support various volatages, refer to documentation.
 */

typedef uint32_t gdet_core_voltage_t;

#if !(defined(FSL_GDET_RANGE_START_1V) && (FSL_GDET_RANGE_START_1V > 0))
#define kGDET_0_9v ((gdet_core_voltage_t)0x0u) /*!< Voltage (0.9V) */
#define kGDET_1_0v ((gdet_core_voltage_t)0x1u) /*!< Voltage (1.0V) */
#define kGDET_1_1v ((gdet_core_voltage_t)0x2u) /*!< Voltage (1.1V) */
#else
#define kGDET_1_0v ((gdet_core_voltage_t)0x0u) /*!< Voltage (1.0V) */
#define kGDET_1_1v ((gdet_core_voltage_t)0x1u) /*!< Voltage (1.1V) */
#define kGDET_1_2v ((gdet_core_voltage_t)0x2u) /*!< Voltage (1.2V) */
#endif

/*******************************************************************************
 * API
 *******************************************************************************/

extern void GDET_DriverIRQHandler(void);

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @name GDET Functional Operation
 * @{
 */

/*!
 * @brief Initialize GDET
 *
 * This function initializes GDET block and setting.
 *
 * @param base GDET peripheral base address
 * @return Status of the init operation
 */
status_t GDET_Init(GDET_Type *base);

/*!
 * @brief Deinitialize GDET
 *
 * This function deinitializes GDET secure counter.
 *
 * @param base GDET peripheral base address
 */
void GDET_Deinit(GDET_Type *base);

/*!
 * @brief Enable GDET
 *
 * This function enables GDET and interrupts.
 *
 * @param base GDET peripheral base address
 * @return Status of the enable operation
 */
status_t GDET_Enable(GDET_Type *base);

/*!
 * @brief Disable GDET
 *
 * This function disables GDET and interrupts.
 *
 * @param base GDET peripheral base address
 * @return Status of the disable operation
 */
status_t GDET_Disable(GDET_Type *base);

/*!
 * @brief Turn on GDET isolation
 *
 * This function turns on isolation of GDET peripheral
 *
 * @param base GDET peripheral base address
 * @return Status of the operation
 */
status_t GDET_IsolateOn(GDET_Type *base);

/*!
 * @brief Turn off GDET isolation
 *
 * This function turns off isolation of GDET peripheral
 *
 * @param base GDET peripheral base address
 * @return Status of the operation
 */
status_t GDET_IsolateOff(GDET_Type *base);

/*!
 * @brief Change expected core voltage
 *
 * This function changes core voltage which Glitch detector expect.
 *
 * @param base GDET peripheral base address
 * @param voltage Expected core voltage
 * @return Status of the GDET reconfiguration operation
 */
status_t GDET_ReconfigureVoltageMode(GDET_Type *base, gdet_core_voltage_t voltage);

/*! @}*/

#if defined(__cplusplus)
}
#endif   /* __cplusplus */

/*! @}*/ /* end of group gdet */

#endif   /* FSL_GDET_H_ */
