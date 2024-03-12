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
 * @file mcuxClSession_Internal_EntryExit.h
 */


#ifndef MCUXCLSESSION_INTERNAL_ENTRYEXIT_H_
#define MCUXCLSESSION_INTERNAL_ENTRYEXIT_H_

#include <mcuxClCore_Platform.h>
#include <mcuxCsslCPreProcessor.h>

#include <mcuxClSession_Types.h>

/* Include the selected implementation of the session entry/exit mechanism. */
/* Default implementation that supports DI/FP initialization and check */
#  include <internal/mcuxClSession_Internal_EntryExit_RegularReturn.h>


#ifdef __cplusplus
extern "C" {
#endif

/**
 * \def MCUXCLSESSION_ENTRY
 * \brief Enter a CL API function
 *
 * This macro shall be called when entering a CL API function.
 * It performs the necessary set up for the API call, including the preparation
 * of the data integrity and flow protection mechanisms.
 *
 * \param ...  The following parameters need to be passed (comma separated):
 *             - session:       Handle for the current CL session.
 *             - functionID:    Flow Protection identifier of the function that has just been entered.
 *             - diBackupValue: Fresh variable name to back up the current DI value.
 *             - faultStatus:   Fault status value for the current API.
 *             - expectations:  Zero or more (comma separated) declarations of expected code
 *                              flow behavior.
 */
#define MCUXCLSESSION_ENTRY(...) \
      MCUX_CSSL_CPP_OVERLOADED4(MCUXCLSESSION_ENTRY_IMPL, __VA_ARGS__)

/**
 * \def MCUXCLSESSION_EXIT
 * \brief Exit a CL API function
 *
 * This macro shall be called when exiting a CL API function.
 * It restores necessary parameters to allow nesting CL API calls, and verifies
 * the data integrity and flow protection values.
 *
 * \param ...  The following parameters need to be passed (comma separated):
 *             - session:      Handle for the current CL session.
 *             - functionID:   Flow Protection identifier of the function that has just been entered.
 *             - diRefValue:   DI reference value.
 *             - returnStatus: Status that should be returned to the caller in the absence of fault attack.
 *             - faultStatus:  Fault status value for the current API.
 *             - expectations: Zero or more (comma separated) declarations of expected code
 *                             flow behavior.
 */
#define MCUXCLSESSION_EXIT(...) \
      MCUX_CSSL_CPP_OVERLOADED5(MCUXCLSESSION_EXIT_IMPL, __VA_ARGS__)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLSESSION_INTERNAL_ENTRYEXIT_H_ */
