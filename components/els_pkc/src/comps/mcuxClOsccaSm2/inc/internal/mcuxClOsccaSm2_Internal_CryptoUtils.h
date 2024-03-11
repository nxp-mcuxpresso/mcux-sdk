/*--------------------------------------------------------------------------*/
/* Copyright 2018-2023 NXP                                                  */
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
 * @file  mcuxClOsccaSm2_Internal_CryptoUtils.h
 * @brief mcuxClOsccaSm2: internal implementation of SM2 Ctypyo Utils function
 */


#ifndef MCUXCLOSCCASM2_INTERNAL_CRYPTOUTILS_H_
#define MCUXCLOSCCASM2_INTERNAL_CRYPTOUTILS_H_

#include <mcuxClOsccaSm2_Types.h>
#include <mcuxClSession_Types.h>
#include <internal/mcuxClOsccaSm2_Internal_Types.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClOscca_FunctionIdentifiers.h>


MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSm2_KDF)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_KDF(mcuxClSession_Handle_t session, mcuxClOsccaSm2_KDF_Param_t *pKDFParam);
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSm2_SecondPartOfInitPhase)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_SecondPartOfInitPhase(
        mcuxClSession_Handle_t session,
        uint32_t primeLength,
        uint8_t const*pX2, mcuxClOsccaSm2_Internal_EncDecCtx_t *pCtx);
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSm2_EncDec_UpdatePhase)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_EncDec_UpdatePhase(
        mcuxClSession_Handle_t session,
        mcuxClOsccaSm2_EncDec_Common_Param_t *pParams,
        uint32_t functionCode);
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSm2_ValidateEncDecCtx)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_ValidateEncDecCtx(
        mcuxClOsccaSm2_Internal_EncDecCtx_t *pCtx,
        uint32_t pLen);

#endif /* MCUXCLOSCCASM2_INTERNAL_CRYPTOUTILS_H_ */
