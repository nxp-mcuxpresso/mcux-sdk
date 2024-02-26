/*--------------------------------------------------------------------------*/
/* Copyright 2023 NXP                                                       */
/*                                                                          */
/* NXP Confidential. This software is owned or controlled by NXP and may    */
/* only be used strictly in accordance with the applicable license terms.   */
/* By expressly accepting such terms or by downloading, installing,         */
/* activating and/or otherwise using the software, you are agreeing that    */
/* you have read, and that you agree to comply with and are bound by, such  */
/* license terms. If you do not agree to be bound by the applicable license */
/* terms, then you may not retain, install, activate or otherwise use the   */
/* software.                                                                */
/*--------------------------------------------------------------------------*/

/**
 * @file  mcuxCsslDataIntegrity.h
 * @brief Provides the API for the CSSL data integrity mechanism.
 */

#ifndef MCUXCSSLDATAINTEGRITY_H_
#define MCUXCSSLDATAINTEGRITY_H_

/* Include the actual implementation of the data integrity mechanism. */
#include <mcuxCsslDataIntegrity_Impl.h>

/* Include the Secure Counter definitions */
#include <mcuxCsslSecureCounter.h>

/**
 * @addtogroup mcuxCsslAPI MCUX CSSL -- API
 *
 * @defgroup mcuxCsslDataIntegrity Data Integrity API
 * @brief Data integrity mechanism.
 * @ingroup mcuxCsslAPI
 */


/**
 * @defgroup diCore Data integrity core functionality
 * @brief Data integrity handling core functionality.
 * @ingroup mcuxCsslDataIntegrity
 */

/****************************************************************************/
/* Constants                                                                */
/****************************************************************************/

/**
 * @def MCUX_CSSL_DI_CHECK_PASSED
 * @brief Positive comparison result value.
 * @api
 * @ingroup diCore
 */
#define MCUX_CSSL_DI_CHECK_PASSED \
  MCUX_CSSL_DI_CHECK_PASSED_IMPL

/**
 * @def MCUX_CSSL_DI_CHECK_FAILED
 * @brief Negative comparison result value.
 * @api
 * @ingroup diCore
 */
#define MCUX_CSSL_DI_CHECK_FAILED \
  MCUX_CSSL_DI_CHECK_FAILED_IMPL

/**
 * @def MCUX_CSSL_DI_INIT_DEFAULT_VALUE
 * @brief Default value use for the initialization of the data integrity mechanism.
 * @api
 * @ingroup diCore
 */
#define MCUX_CSSL_DI_INIT_DEFAULT_VALUE \
  (0x96969696u)

/****************************************************************************/
/* Initialization                                                           */
/****************************************************************************/

/**
 * @def MCUX_CSSL_DI_ALLOC
 * @brief Allocation operation for the data integrity register.
 * @api
 * @ingroup diCore
 */
#define MCUX_CSSL_DI_ALLOC() \
  MCUX_CSSL_DI_ALLOC_IMPL()

/**
 * @def MCUX_CSSL_DI_INIT
 * @brief Initialization operation for the data integrity mechanism.
 * @api
 * @ingroup diCore
 *
 * @param value Value with which the data integrity register must be initialized.
 */
#define MCUX_CSSL_DI_INIT(value) \
  MCUX_CSSL_DI_INIT_IMPL(value)

/****************************************************************************/
/* Check                                                                    */
/****************************************************************************/

/**
 * @def MCUX_CSSL_DI_CHECK
 * @brief Comparison operation for the data integrity.
 * @api
 * @ingroup diCore
 *
 * @param reference Reference value to compare the data integrity value against.
 * @return          Either #MCUX_CSSL_DI_CHECK_PASSED, if the value matches, or
 *                  #MCUX_CSSL_DI_CHECK_FAILED if the value is different.
 */
#define MCUX_CSSL_DI_CHECK(reference) \
  MCUX_CSSL_DI_CHECK_IMPL(reference)

/****************************************************************************/
/* Updates                                                                  */
/****************************************************************************/

/**
 * @defgroup diUpdate Data integrity record
 * @brief Support for recording a value in the data integrity register
 * @ingroup mcuxCsslDataIntegrity
 */

/**
 * @def MCUX_CSSL_DI_RECORD
 * @brief Record the @p value for data integrity checking.
 * @api
 * @ingroup diUpdate
 *
 * @param identifier Identifier for the @p value that will be recorded.
 * @param value Value which needs to be recorded for the given @p identifier.
 */
#define MCUX_CSSL_DI_RECORD(identifier, value) \
  MCUX_CSSL_DI_RECORD_IMPL(identifier, value)

/**
 * @def MCUX_CSSL_DI_EXPUNGE
 * @brief Expunge the record for @p value.
 * @api
 * @ingroup diUpdate
 *
 * @param identifier Identifier for the @p value that will be expunged.
 * @param value Expected value that was recorded for the given @p identifier.
 */
#define MCUX_CSSL_DI_EXPUNGE(identifier, value) \
  MCUX_CSSL_DI_EXPUNGE_IMPL(identifier, value)

#endif /* MCUXCSSLDATAINTEGRITY_H_ */
