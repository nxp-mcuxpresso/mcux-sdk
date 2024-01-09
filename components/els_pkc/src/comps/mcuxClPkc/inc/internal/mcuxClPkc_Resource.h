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
 * @file  mcuxClPkc_Resource.h
 * @brief Macros for requesting/releasing PKC
 */


#ifndef MCUXCLPKC_RESOURCE_H_
#define MCUXCLPKC_RESOURCE_H_

#include <mcuxClCore_Platform.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslAnalysis.h>
#include <mcuxClSession.h>
#include <mcuxClPkc_Types.h>
#include <mcuxClPkc_Functions.h>


#ifdef __cplusplus
extern "C" {
#endif

/** Macro to only initialize PKC (for platforms not supporting requesting resource) */
#define MCUXCLPKC_FP_REQUEST_INITIALIZE(session, pPkcStateBackup, callerName, errorReturnCode) \
            MCUXCLPKC_FP_INITIALIZE(pPkcStateBackup)

/** Macro to only deinitialize PKC (for platforms not supporting releasing resource) */
#define MCUXCLPKC_FP_DEINITIALIZE_RELEASE(session, pPkcStateBackup, callerName, errorReturnCode) \
            MCUXCLPKC_FP_DEINITIALIZE(pPkcStateBackup)

#define MCUXCLPKC_FP_CALLED_REQUEST_INITIALIZE  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Initialize)
#define MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize)


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLPKC_RESOURCE_H_ */
