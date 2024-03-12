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
 * @file mcuxClSession_Internal_EntryExit_RegularReturn.h
 */


#ifndef MCUXCLSESSION_INTERNAL_ENTRYEXIT_REGULARRETURN_H_
#define MCUXCLSESSION_INTERNAL_ENTRYEXIT_REGULARRETURN_H_

#include <mcuxClCore_Platform.h>
#include <mcuxCsslDataIntegrity.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClSession_Types.h>

/**
 * \def MCUXCLSESSION_ENTRY_IMPLn
 * \brief Enter a CL API function
 *
 * This macro is the implementation macro of MCUXCLSESSION_ENTRY, with more than 4 arguments.
 * It sets up the correct FP value, and backs up the current DI value.
 *
 * \param session       Handle for the current CL session (unused).
 * \param functionID    Flow Protection identifier of the function that has just been entered.
 * \param diBackupValue Fresh variable name to back up the current DI value.
 * \param faultStatus   Fault status value for the current API (unused).
 * \param expectations  One or more (comma separated) declarations of expected code
 *                      flow behavior.
 */
#define MCUXCLSESSION_ENTRY_IMPLn(session, functionID, diBackupValue, faultStatus, ...) \
      MCUX_CSSL_FP_FUNCTION_ENTRY(functionID, __VA_ARGS__); \
      /* Back up the current DI value */ \
      MCUX_CSSL_DI_INIT(diBackupValue);

/**
 * \def MCUXCLSESSION_ENTRY_IMPL4
 * \brief Enter a CL API function
 *
 * This macro is the implementation macro of MCUXCLSESSION_ENTRY, with exactly 4 arguments.
 * It is a wrapper around MCUXCLSESSION_ENTRY_IMPLn.
 *
 * \param session       Handle for the current CL session (unused).
 * \param functionID    Flow Protection identifier of the function that has just been entered.
 * \param diBackupValue Fresh variable name to back up the current DI value.
 * \param faultStatus   Fault status value for the current API (unused).
 */
#define MCUXCLSESSION_ENTRY_IMPL4(session, functionID, diBackupValue, faultStatus) \
      MCUXCLSESSION_ENTRY_IMPLn(session, functionID, diBackupValue, faultStatus, 0u)

/**
 * \def MCUXCLSESSION_EXIT_IMPLn
 * \brief Exit a CL API function
 *
 * This macro is the implementation macro of MCUXCLSESSION_EXIT, with more than 5 arguments.
 * It checks the DI value against the reference value, and exits with Fault Attack if there is a mismatch.
 * It checks the FP value, and exits with Fault Attack if there is a mismatch.
 *
 * \param session      Handle for the current CL session (unused).
 * \param functionID   Flow Protection identifier of the function that has just been entered.
 * \param diRefValue   DI reference value.
 * \param returnStatus Status that should be returned to the caller in the absence of fault attack.
 * \param faultStatus  Fault status value for the current API.
 * \param expectations One or more (comma separated) declarations of expected code
 *                     flow behavior.
 */
#define MCUXCLSESSION_EXIT_IMPLn(session, functionID, diRefValue, returnStatus, faultStatus, ...) \
      /* Check DI value, and exit with faultStatus if the comparison fails. */ \
      MCUX_CSSL_DI_CHECK_EXIT(functionID, diRefValue, faultStatus); \
      /* Exit CL API function */ \
      MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(functionID, returnStatus, faultStatus, __VA_ARGS__);

/**
 * \def MCUXCLSESSION_EXIT_IMPL5
 * \brief Exit a CL API function
 *
 * This macro is the implementation macro of MCUXCLSESSION_EXIT, with exactly 5 arguments.
 * It is a wrapper around MCUXCLSESSION_EXIT_IMPLn.
 *
 * \param session      Handle for the current CL session (unused).
 * \param functionID   Flow Protection identifier of the function that has just been entered.
 * \param diRefValue   DI reference value.
 * \param returnStatus Status that should be returned to the caller in the absence of fault attack.
 * \param faultStatus  Fault status value for the current API.
 */
#define MCUXCLSESSION_EXIT_IMPL5(session, functionID, diRefValue, returnStatus, faultStatus) \
      MCUXCLSESSION_EXIT_IMPLn(session, functionID, diRefValue, returnStatus, faultStatus, 0u)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLSESSION_INTERNAL_ENTRYEXIT_REGULARRETURN_H_ */
