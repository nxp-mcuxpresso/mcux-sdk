/*--------------------------------------------------------------------------*/
/* Copyright 2021-2023 NXP                                                  */
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

/** @file  mcuxClKey_Protection_Internal.h
 *  @brief Internal header of mcuxClKey_Protection
 */

#ifndef MCUXCLKEY_PROTECTION_INTERNAL_H_
#define MCUXCLKEY_PROTECTION_INTERNAL_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClKey_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************
 * INTERNAL FUNCTIONS
 **********************************************/
/*! @brief Internal functions for the key component  */

/**
 * @brief no key protection function
 *
 * @param[in]  key              The key of type mcuxClKey_Handle_t
 *
 * @return status
 * @retval MCUXCLKEY_STATUS_ERROR   On error
 * @retval MCUXCLKEY_STATUS_OK      On success
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClKey_protect_fct_none, mcuxClKey_LoadFuncPtr_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_protect_fct_none(
  mcuxClKey_Handle_t key
  );

/**
 * @brief ckdf key protection function
 *
 * @param[in]  key                 The key of type mcuxClKey_Handle_t
 *
 * The key properties must be set before calling this function
 * by calling @ref mcuxClKey_setKeyproperties
 *
 * @return status
 * @retval MCUXCLKEY_STATUS_ERROR   On error
 * @retval MCUXCLKEY_STATUS_OK      On success
 *
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClKey_protect_fct_ckdf, mcuxClKey_LoadFuncPtr_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_protect_fct_ckdf(
  mcuxClKey_Handle_t key
  );



#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLKEY_PROTECTION_INTERNAL_H_ */
