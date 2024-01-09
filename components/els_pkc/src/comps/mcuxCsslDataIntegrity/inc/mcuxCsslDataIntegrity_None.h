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
 * \file  mcuxCsslDataIntegrity_None.h
 * \brief Implementation that disables the CSSL data integrity mechanism.
 */

#ifndef MCUXCSSLDATAINTEGRITY_NONE_H_
#define MCUXCSSLDATAINTEGRITY_NONE_H_

/**
 * \addtogroup mcuxCsslIMPL MCUX CSSL -- Implementations
 *
 * \defgroup mcuxCsslDataIntegrity_None Data Integrity: Disabled
 * \brief Disable the data integrity mechanism.
 * \ingroup mcuxCsslIMPL
 */


/**
 * \defgroup diNoneCore Data integrity core functionality
 * \brief Data integrity handling core functionality, when data integrity is disabled.
 * \ingroup mcuxCsslDataIntegrity_None
 */

/****************************************************************************/
/* Constants                                                                */
/****************************************************************************/

/**
 * \def MCUX_CSSL_DI_CHECK_PASSED_IMPL
 * \brief Positive comparison result value.
 * \ingroup diNoneCore
 */
#define MCUX_CSSL_DI_CHECK_PASSED_IMPL (MCUX_CSSL_SC_CHECK_PASSED)

/**
 * \def MCUX_CSSL_DI_CHECK_FAILED_IMPL
 * \brief Negative comparison result value.
 * \ingroup diNoneCore
 */
#define MCUX_CSSL_DI_CHECK_FAILED_IMPL (MCUX_CSSL_SC_CHECK_FAILED)

/****************************************************************************/
/* Initialization                                                           */
/****************************************************************************/

/**
 * \def MCUX_CSSL_DI_ALLOC_IMPL
 * \brief Allocation operation implementation for the data integrity.
 * \ingroup diNoneCore
 */
#define MCUX_CSSL_DI_ALLOC_IMPL() \
  /* intentionally empty */

/**
 * \def MCUX_CSSL_DI_INIT_IMPL
 * \brief Initialization operation implementation for the data integrity.
 * \ingroup diNoneCore
 *
 * \param value Value with which the data integrity must be initialized.
 */
#define MCUX_CSSL_DI_INIT_IMPL(value) \
  /* intentionally empty */

/****************************************************************************/
/* Check                                                                    */
/****************************************************************************/

/**
 * \def MCUX_CSSL_DI_CHECK_IMPL
 * \brief Comparison operation implementation for the data integrity.
 * \ingroup diNoneCore
 *
 * \param reference Reference value to compare the data integrity value against.
 * \return          Always #MCUX_CSSL_DI_CHECK_PASSED.
 */
#define MCUX_CSSL_DI_CHECK_IMPL(reference) \
  (MCUX_CSSL_DI_CHECK_PASSED_IMPL)

/****************************************************************************/
/* Updates                                                                  */
/****************************************************************************/

/**
 * \defgroup diNoneUpdate Data integrity record
 * \brief Support for recording a value in the data integrity register, when data integrity is disabled.
 * \ingroup mcuxCsslDataIntegrity_None
 */

/**
 * \def MCUX_CSSL_DI_RECORD_IMPL
 * \brief Implementation: Record the value for data integrity checking.
 * \ingroup diNoneUpdate
 *
 * \param identifier Identifier for the value that will be recorded.
 * \param value      Value which needs to be recorded for the given identifier.
 */
#define MCUX_CSSL_DI_RECORD_IMPL(identifier, value) \
  /* intentionally empty */

/**
 * \def MCUX_CSSL_DI_EXPUNGE_IMPL
 * \brief Implementation: Expunge the record for value.
 * \ingroup diNoneUpdate
 *
 * \param identifier Identifier for the value that will be expunged.
 * \param value      Expected value that was recorded for the given identifier.
 */
#define MCUX_CSSL_DI_EXPUNGE_IMPL(identifier, value) \
  /* intentionally empty */


#endif /* MCUXCSSLDATAINTEGRITY_NONE_H_ */
