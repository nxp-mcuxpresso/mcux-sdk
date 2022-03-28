/*--------------------------------------------------------------------------*/
/* Copyright 2021 NXP                                                       */
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


#include <mcuxCsslFlowProtection.h>
#include <mcuxClKey.h>


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
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClKey_protect_fct_none)
mcuxClKey_Status_Protected_t mcuxClKey_protect_fct_none(
  mcuxClKey_Handle_t key
  );

/**
 * @brief ckdf key protection function
 *
 * @param[in]  key                 The key of type mcuxClKey_Handle_t
 *
 * @return status 
 * @retval MCUXCLKEY_STATUS_ERROR   On error
 * @retval MCUXCLKEY_STATUS_OK      On success
 * 
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClKey_protect_fct_ckdf)
mcuxClKey_Status_Protected_t mcuxClKey_protect_fct_ckdf(
  mcuxClKey_Handle_t key
  );

/**
 * @brief no flush key protection function
 *
 * @param[in]  key              The key of type mcuxClKey_Handle_t
 *
 * @return status 
 * @retval MCUXCLKEY_STATUS_OK   In any case
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClKey_flush_fct_none)
mcuxClKey_Status_Protected_t mcuxClKey_flush_fct_none(
  mcuxClKey_Handle_t key
  );

/**
 * @brief css flush key protection function
 *
 * @param[in]  key                 The key of type mcuxClKey_Handle_t
 *
 * @return status 
 * @retval MCUXCLKEY_STATUS_ERROR   On error
 * @retval MCUXCLKEY_STATUS_OK      On success
 * 
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClKey_flush_fct_css)
mcuxClKey_Status_Protected_t mcuxClKey_flush_fct_css(
  mcuxClKey_Handle_t key
  );

/**
 * @brief memory key protection function
 *
 * @param[in]  key                 The key of type mcuxClKey_Handle_t
 *
 * @return status 
 * @retval MCUXCLKEY_STATUS_ERROR   On error
 * @retval MCUXCLKEY_STATUS_OK      On success
 * 
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClKey_flush_fct_memory)
mcuxClKey_Status_Protected_t mcuxClKey_flush_fct_memory(
  mcuxClKey_Handle_t key
  );

#endif /* MCUXCLKEY_PROTECTION_INTERNAL_H_ */
