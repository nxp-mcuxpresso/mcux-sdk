/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021 NXP                                                  */
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

/** @file  mcuxClRsa_Public.c
 *  @brief mcuxClRsa: implementation of RSA Public function
 */

#include <stdint.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClPkc.h>
#include <mcuxClMath.h>
#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClPkc_ImportExport.h>

#include <mcuxClRsa.h>

#include <internal/mcuxClRsa_Internal_PkcDefs.h>
#include <internal/mcuxClRsa_Internal_Functions.h>
#include <internal/mcuxClRsa_Internal_Types.h>
#include <internal/mcuxClRsa_Internal_MemoryConsumption.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_public)
mcuxClRsa_Status_Protected_t mcuxClRsa_public(
  mcuxClSession_Handle_t      pSession,
  const mcuxClRsa_Key * const pKey,
  const uint8_t * const      pInput,
  uint8_t * const            pOutput)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_public);

  if(MCUXCLRSA_KEY_PUBLIC != pKey->keytype)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_public, MCUXCLRSA_STATUS_INVALID_INPUT);
  }

  if(NULL == pKey->pMod1->pKeyEntryData)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_public, MCUXCLRSA_STATUS_INVALID_INPUT);
  }

  const uint8_t* const pExp = pKey->pExp1->pKeyEntryData;
  if(NULL == pExp)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_public, MCUXCLRSA_STATUS_INVALID_INPUT);
  }

  const uint32_t byteLenN = pKey->pMod1->keyEntryLength;

  if(0U == (pKey->pMod1->pKeyEntryData[byteLenN - 1U] & 0x01U))
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_public, MCUXCLRSA_STATUS_INVALID_INPUT);
  }

  if((byteLenN < 64U) || (byteLenN > 512U) )
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_public, MCUXCLRSA_STATUS_INVALID_INPUT);
  }

  const uint32_t operandSize = MCUXCLPKC_ROUNDUP_SIZE(byteLenN);
  const uint16_t bufferSizeX = (uint16_t)operandSize;
  const uint16_t bufferSizeR = (uint16_t)operandSize + MCUXCLPKC_WORDSIZE;
  const uint16_t bufferSizeN = (uint16_t)operandSize + MCUXCLPKC_WORDSIZE;
  const uint16_t bufferSizeT1 = (uint16_t)operandSize + MCUXCLPKC_WORDSIZE;
  const uint16_t bufferSizeT2 = (uint16_t)operandSize + MCUXCLPKC_WORDSIZE;

  uint8_t *pPkcWorkarea = (uint8_t *) (& pSession->pkcWa.buffer[pSession->pkcWa.used]);
  const uint16_t bufferSizeTotal = bufferSizeX + bufferSizeN + bufferSizeR + bufferSizeT1 + bufferSizeT2;

  uint16_t * pOperands = (uint16_t *)&pSession->cpuWa.buffer[pSession->cpuWa.used];
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_X] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_R] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea + bufferSizeX);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_N] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea + bufferSizeX + bufferSizeR + MCUXCLPKC_WORDSIZE );
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T1] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea + bufferSizeX + bufferSizeR + bufferSizeN);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T2] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea + bufferSizeX + bufferSizeR + bufferSizeN + bufferSizeT1);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_OUTPUT] = MCUXCLPKC_PTR2OFFSET(pOutput);

  MCUXCLPKC_SETUPTRT(pOperands);

  MCUXCLPKC_PS1_SETLENGTH(0u, bufferSizeTotal);
  MCUXCLPKC_FP_CALC_OP1_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_X, 0u);

  MCUXCLPKC_PS1_SETLENGTH(0u, operandSize);
  MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_N, pKey->pMod1->pKeyEntryData, byteLenN);
  MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_X, pInput, byteLenN);

  MCUXCLPKC_FP_CALC_OP1_CMP(MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_X, MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_N);
  MCUXCLPKC_WAITFORFINISH();
  uint32_t carryFlag = MCUXCLPKC_GETCARRY();

  if(1U != carryFlag)
  {
      MCUXCLPKC_PS1_SETLENGTH(0u, bufferSizeTotal);
    MCUXCLPKC_FP_CALC_OP1_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_X, 0u);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_public, MCUXCLRSA_STATUS_INVALID_INPUT,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CONST);
  }

  MCUXCLPKC_FP_CALC_OP1_SUB_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T2, MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_X, 1U);
  MCUXCLPKC_WAITFORFINISH();

  carryFlag = MCUXCLPKC_GETCARRY();

  if(MCUXCLPKC_FLAG_CARRY == carryFlag)
  {
    MCUXCLPKC_FP_CALC_OP1_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_OUTPUT, 0u);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_public, MCUXCLRSA_INTERNAL_STATUS_KEYOP_OK,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
        MCUXCLPKC_FP_CALLED_CALC_OP1_SUB_CONST,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CONST);
  }

  MCUXCLMATH_FP_NDASH(MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_N, MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T1);

  MCUXCLPKC_PS1_SETLENGTH(operandSize, operandSize);
  MCUXCLMATH_FP_SHIFTMODULUS(MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T1, MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_N);
  MCUXCLMATH_FP_QSQUARED(MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_R , MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T1,
      MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_N, MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T2);

  MCUXCLPKC_FP_CALC_MC1_MM(MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T1 , MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_X ,
      MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_R , MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_N);

  uint32_t byteLenExp = pKey->pExp1->keyEntryLength;
  MCUXCLMATH_FP_MODEXP_SQRMULTL2R(pExp, byteLenExp, MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T2, MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T1,
      MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_N, MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_R);

  MCUXCLPKC_FP_CALC_MC1_MR(MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_R, MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T2,
      MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_N);
  MCUXCLPKC_FP_CALC_MC1_MS(MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_OUTPUT, MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_R,
      MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_N, MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_N);
  MCUXCLPKC_WAITFORFINISH();

  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_public, MCUXCLRSA_INTERNAL_STATUS_KEYOP_OK,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
        MCUXCLPKC_FP_CALLED_CALC_OP1_SUB_CONST,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_NDash),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ShiftModulus),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_QSquared),
        MCUXCLPKC_FP_CALLED_CALC_MC1_MM,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModExp_SqrMultL2R),
        MCUXCLPKC_FP_CALLED_CALC_MC1_MR,
        MCUXCLPKC_FP_CALLED_CALC_MC1_MS);
}
