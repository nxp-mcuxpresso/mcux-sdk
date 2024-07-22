/*--------------------------------------------------------------------------*/
/* Copyright 2022-2023 NXP                                                  */
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

/** @file  mcuxClSignature_sign.c
 *  @brief mcuxClSignature: implementation of mcuxClSignature_sign function
 */


#include <mcuxClSignature.h>

#include <mcuxCsslAnalysis.h>

#include <mcuxClEcc_Types.h>
#ifdef MCUXCL_FEATURE_SM2_SIGNATURE
#include <mcuxClOsccaSm2_Types.h>
#endif

#include <internal/mcuxClSession_Internal_EntryExit.h>
#include <internal/mcuxClSignature_Internal.h>

#ifdef MCUXCL_FEATURE_SIGNATURE_ONESHOT
#ifdef MCUXCL_FEATURE_SIGNATURE_SIGN
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClSignature_sign)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClSignature_Status_t) mcuxClSignature_sign(
  mcuxClSession_Handle_t session,
  mcuxClKey_Handle_t key,
  mcuxClSignature_Mode_t mode,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inSize,
  mcuxCl_Buffer_t pSignature,
  uint32_t * const pSignatureSize
)
{
  MCUXCLSESSION_ENTRY(session, mcuxClSignature_sign, diRefValue, MCUXCLSIGNATURE_STATUS_FAULT_ATTACK)

  MCUX_CSSL_FP_FUNCTION_CALL(sign_status, mode->pSignFct(
    /* mcuxClSession_Handle_t           session:          */  session,
    /* mcuxClKey_Handle_t               key:              */  key,
    /* mcuxClSignature_Mode_t           mode:             */  mode,
    /* mcuxCl_InputBuffer_t             pIn:              */  pIn,
    /* const uint32_t                  inSize:           */  inSize,
    /* mcuxCl_Buffer_t                  pSignature:       */  pSignature,
    /* uint32_t * const                pSignatureSize:   */  pSignatureSize));

  // TODO: Remove workaround (CLNS-8518)
  volatile mcuxClSignature_Status_t sign_result_tmp = MCUXCLSIGNATURE_STATUS_FAILURE;

  MCUX_CSSL_ANALYSIS_COVERITY_START_DEVIATE(MISRA_C_2012_Rule_14_3, "intentional, this 'false' is a temporary solution")
  if(
    MCUXCLECC_STATUS_OK == sign_status || 
#ifdef MCUXCL_FEATURE_SM2_SIGNATURE
    MCUXCLOSCCASM2_STATUS_OK == sign_status ||
#endif
    false) // This causes a MISRA violation Rule 14.3
  {
    sign_result_tmp = MCUXCLSIGNATURE_STATUS_OK;
  }
  MCUX_CSSL_ANALYSIS_COVERITY_STOP_DEVIATE(MISRA_C_2012_Rule_14_3)

  MCUXCLSESSION_EXIT(session,
      mcuxClSignature_sign,
      diRefValue,
      sign_result_tmp,
      MCUXCLSIGNATURE_STATUS_FAULT_ATTACK,
      mode->protection_token_sign)
}
#endif /* MCUXCL_FEATURE_SIGNATURE_SIGN */


#ifdef MCUXCL_FEATURE_SIGNATURE_VERIFY
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClSignature_verify)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClSignature_Status_t) mcuxClSignature_verify(
  mcuxClSession_Handle_t session,
  mcuxClKey_Handle_t key,
  mcuxClSignature_Mode_t mode,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inSize,
  mcuxCl_InputBuffer_t pSignature,
  uint32_t signatureSize
)
{
  MCUXCLSESSION_ENTRY(session, mcuxClSignature_verify, diRefValue, MCUXCLSIGNATURE_STATUS_FAULT_ATTACK)

  MCUX_CSSL_FP_FUNCTION_CALL(verify_status, mode->pVerifyFct(
    /* mcuxClSession_Handle_t           session:           */  session,
    /* mcuxClKey_Handle_t               key:               */  key,
    /* mcuxClSignature_Mode_t           mode:              */  mode,
    /* mcuxCl_InputBuffer_t             pIn:               */  pIn,
    /* uint32_t                        inSize:            */  inSize,
    /* mcuxCl_InputBuffer_t             pSignature:        */  pSignature,
    /* uint32_t                        signatureSize:     */  signatureSize));

  // TODO: Remove workaround (CLNS-8518)
  volatile mcuxClSignature_Status_t verify_result_tmp = MCUXCLSIGNATURE_STATUS_FAILURE;

  MCUX_CSSL_ANALYSIS_COVERITY_START_DEVIATE(MISRA_C_2012_Rule_14_3, "intentional, this 'false' is a temporary solution")
if(
    MCUXCLECC_STATUS_INVALID_SIGNATURE == verify_status || 
#ifdef MCUXCL_FEATURE_SM2_SIGNATURE
    MCUXCLOSCCASM2_STATUS_INVALID_SIGNATURE == verify_status ||
#endif
    false) // This causes a MISRA violation Rule 14.3
  {
    verify_result_tmp = MCUXCLSIGNATURE_STATUS_NOT_OK;
  }
else if(
    MCUXCLECC_STATUS_OK == verify_status || 
#ifdef MCUXCL_FEATURE_SM2_SIGNATURE
    MCUXCLOSCCASM2_STATUS_OK == verify_status ||
#endif
    false) // This causes a MISRA violation Rule 14.3
  {
    verify_result_tmp = MCUXCLSIGNATURE_STATUS_OK;
  }
  else
  {
      /* Intentionally left empty */
  }
  MCUX_CSSL_ANALYSIS_COVERITY_STOP_DEVIATE(MISRA_C_2012_Rule_14_3)

  MCUXCLSESSION_EXIT(session,
      mcuxClSignature_verify,
      diRefValue,
      verify_result_tmp,
      MCUXCLSIGNATURE_STATUS_FAULT_ATTACK,
      mode->protection_token_verify)

}
#endif /* MCUXCL_FEATURE_SIGNATURE_VERIFY */
#endif /* MCUXCL_FEATURE_SIGNATURE_ONESHOT */


#ifdef MCUXCL_FEATURE_SIGNATURE_SELFTEST
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClSignature_selftest)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClSignature_Status_t) mcuxClSignature_selftest(
  mcuxClSession_Handle_t session,
  mcuxClSignature_Mode_t mode,
  mcuxClSignature_Test_t test
)
{
  MCUXCLSESSION_ENTRY(session, mcuxClSignature_selftest, diRefValue, MCUXCLSIGNATURE_STATUS_FAULT_ATTACK)

  MCUX_CSSL_FP_FUNCTION_CALL(selftest_status, test->pSelfTestFct(
    /* mcuxClSession_Handle_t            session:             */  session,
    /* mcuxClSignature_Mode_t            mode:                */  mode));

  MCUXCLSESSION_EXIT(session,
      mcuxClSignature_selftest,
      diRefValue,
      selftest_status,
      MCUXCLSIGNATURE_STATUS_FAULT_ATTACK,
      test->protection_token_selftest)
}
#endif /* MCUXCL_FEATURE_SIGNATURE_SELFTEST */


