/*--------------------------------------------------------------------------*/
/* Copyright 2020-2023 NXP                                                  */
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

/** @file  mcuxClRsa_NoVerify.c
 *  @brief mcuxClRsa: function, which is called in case of no verification
 */


#include <stdint.h>
#include <mcuxClToolchain.h>

#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClPkc.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClPkc_Macros.h>
#include <internal/mcuxClPkc_ImportExport.h>

#include <mcuxClRsa.h>
#include <internal/mcuxClRsa_Internal_Functions.h>
#include <internal/mcuxClRsa_Internal_Types.h>
#include <internal/mcuxClRsa_Internal_PkcDefs.h>
#include <internal/mcuxClRsa_Internal_PkcTypes.h>


/**********************************************************/
/* Specification of no-verify mode structure              */
/**********************************************************/
const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Verify_NoVerify =
{
  .EncodeVerify_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_noVerify),
  .pHashAlgo1 = NULL,
  .pHashAlgo2 = NULL,
  .pPaddingFunction = mcuxClRsa_noVerify
};


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_noVerify, mcuxClRsa_PadVerModeEngine_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t) mcuxClRsa_noVerify(
  mcuxClSession_Handle_t       pSession,
  mcuxCl_InputBuffer_t         pInput UNUSED_PARAM,
  const uint32_t              inputLength UNUSED_PARAM,
  mcuxCl_Buffer_t              pVerificationInput,
  mcuxClHash_Algo_t            pHashAlgo UNUSED_PARAM,
  const uint8_t *             pLabel UNUSED_PARAM,
  const uint32_t              saltlabelLength UNUSED_PARAM,
  const uint32_t              keyBitLength,
  const uint32_t              options UNUSED_PARAM,
  mcuxCl_Buffer_t              pOutput,
  uint32_t * const            pOutLength UNUSED_PARAM)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_noVerify);

  /* Setup UPTR table. */
  const uint32_t cpuWaSizeWord = (((sizeof(uint16_t)) * MCUXCLRSA_INTERNAL_NOVERIFY_UPTRT_SIZE) + (sizeof(uint32_t)) - 1u) / (sizeof(uint32_t));
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("16-bit UPTRT table is assigned in CPU workarea")
  uint16_t * pOperands = (uint16_t *) mcuxClSession_allocateWords_cpuWa(pSession, cpuWaSizeWord);
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()

  const uint32_t keyByteLength = keyBitLength / 8U; /* keyBitLength is a multiple of 8 */
  const uint32_t pkcWaSizeWord = MCUXCLRSA_PKC_ROUNDUP_SIZE(keyByteLength) / (sizeof(uint32_t));
  uint8_t *pPkcWa = (uint8_t *) mcuxClSession_allocateWords_pkcWa(pSession, pkcWaSizeWord);
  if ((NULL == pOperands) || (NULL == pPkcWa))
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_noVerify, MCUXCLRSA_STATUS_FAULT_ATTACK);
  }

  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_NOVERIFY_IN] = MCUXCLPKC_PTR2OFFSET(pVerificationInput);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_NOVERIFY_TMP] = MCUXCLPKC_PTR2OFFSET(pPkcWa);

  /* Set UPTRT table */
  MCUXCLPKC_SETUPTRT(pOperands);

  /* Export result of size BYTE_LENGTH(keyBitLength) from pInput to pOutput in reverse order. */
  const uint32_t ps1OpLen = MCUXCLRSA_PKC_ROUNDUP_SIZE(keyByteLength); /* PS1 length = key byte length rounded up to PKC word size */
  MCUXCLPKC_PS1_SETLENGTH(0u, ps1OpLen);
  MCUX_CSSL_FP_FUNCTION_CALL(ret_SecExport, mcuxClPkc_SecureExportBigEndianFromPkc(pSession,
                                                                                 (uint8_t * )pOutput,
                                                                                 MCUXCLPKC_PACKARGS2(MCUXCLRSA_INTERNAL_UPTRTINDEX_NOVERIFY_IN,
                                                                                                    MCUXCLRSA_INTERNAL_UPTRTINDEX_NOVERIFY_TMP),
                                                                                 keyByteLength));
  if (MCUXCLPKC_STATUS_OK != ret_SecExport)
  {
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_noVerify, MCUXCLRSA_STATUS_ERROR);
  }

  mcuxClSession_freeWords_pkcWa(pSession, pkcWaSizeWord);
  mcuxClSession_freeWords_cpuWa(pSession, cpuWaSizeWord);

  /* Return error code MCUXCLRSA_STATUS_VERIFYPRIMITIVE_OK. */
  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_noVerify, MCUXCLRSA_STATUS_VERIFYPRIMITIVE_OK,
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SecureExportBigEndianFromPkc));
}
