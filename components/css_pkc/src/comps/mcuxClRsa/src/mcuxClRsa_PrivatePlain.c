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

/** @file  mcuxClRsa_PrivatePlain.c
 *  @brief mcuxClRsa: implementation of RSA private plain key operation
 */

#include <stdint.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClPkc.h>
#include <mcuxClMath.h>
#include <mcuxClMemory.h>
#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClPkc_ImportExport.h>

#include <mcuxClRsa.h>

#include <internal/mcuxClRsa_Internal_PkcDefs.h>
#include <internal/mcuxClRsa_Internal_Functions.h>
#include <internal/mcuxClRsa_Internal_Types.h>
#include <internal/mcuxClRsa_Internal_Macros.h>
#include <internal/mcuxClRsa_Internal_MemoryConsumption.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_privatePlain)
mcuxClRsa_Status_Protected_t mcuxClRsa_privatePlain(
  mcuxClSession_Handle_t      pSession,
  const mcuxClRsa_Key * const pKey,
  const uint8_t * const      pInput,
  uint8_t * const            pOutput)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_privatePlain);

  if(MCUXCLRSA_KEY_PRIVATEPLAIN != pKey->keytype)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_privatePlain, MCUXCLRSA_STATUS_INVALID_INPUT);
  }

  if(NULL == pKey->pMod1->pKeyEntryData)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_privatePlain, MCUXCLRSA_STATUS_INVALID_INPUT);
  }

  const uint8_t* const pExp = pKey->pExp1->pKeyEntryData;
  if(NULL == pExp)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_privatePlain, MCUXCLRSA_STATUS_INVALID_INPUT);
  }

  const uint32_t byteLenN = pKey->pMod1->keyEntryLength;
  const uint32_t byteLenD = pKey->pExp1->keyEntryLength;

  if(0U == (pKey->pMod1->pKeyEntryData[byteLenN - 1U] & 0x01U))
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_privatePlain, MCUXCLRSA_STATUS_INVALID_INPUT);
  }

  if((byteLenN < 64U) || (byteLenN > 512U) )
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_privatePlain, MCUXCLRSA_STATUS_INVALID_INPUT);
  }

  const uint32_t operandSize = MCUXCLPKC_ROUNDUP_SIZE(byteLenN);
  const uint16_t bufferSizeX = (uint16_t)operandSize;
  const uint16_t bufferSizeR = (uint16_t)operandSize + MCUXCLPKC_WORDSIZE;
  const uint16_t bufferSizeN = (uint16_t)operandSize + MCUXCLPKC_WORDSIZE;
  const uint16_t bufferSizeT0 = (uint16_t)operandSize + MCUXCLPKC_WORDSIZE;
  const uint16_t bufferSizeT1 = (uint16_t)operandSize + MCUXCLPKC_WORDSIZE;
  const uint16_t bufferSizeT2 = (uint16_t)operandSize + MCUXCLPKC_WORDSIZE;
  const uint16_t bufferSizeT3 = (uint16_t)operandSize;
  const uint16_t bufferSizeTE = (uint16_t)5u*MCUXCLPKC_WORDSIZE;

  uint8_t *pPkcWorkarea = (uint8_t *) (& pSession->pkcWa.buffer[pSession->pkcWa.used]);
  const uint16_t bufferSizeTotal = bufferSizeX + bufferSizeR + bufferSizeN + bufferSizeT0 + bufferSizeT1 + bufferSizeT2 + bufferSizeT3 + bufferSizeTE;

  uint16_t * pOperands = (uint16_t *)&pSession->cpuWa.buffer[pSession->cpuWa.used];
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_X] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_R] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea + bufferSizeX);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_N] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea + bufferSizeX + bufferSizeR + MCUXCLPKC_WORDSIZE );
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_T0] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea + bufferSizeX + bufferSizeR + bufferSizeN);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_T1] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea + bufferSizeX + bufferSizeR + bufferSizeN + bufferSizeT0);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_T2] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea + bufferSizeX + bufferSizeR + bufferSizeN + bufferSizeT0 + bufferSizeT1);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_T3] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea + bufferSizeX + bufferSizeR + bufferSizeN + bufferSizeT0 + bufferSizeT1 + bufferSizeT2);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_TE] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea + bufferSizeX + bufferSizeR + bufferSizeN + bufferSizeT0 + bufferSizeT1 + bufferSizeT2 + bufferSizeT3);

  MCUXCLPKC_SETUPTRT(pOperands);

  MCUX_CSSL_FP_FUNCTION_CALL(memset_result, mcuxClMemory_set(pPkcWorkarea + byteLenN, 0x00U, bufferSizeTotal - byteLenN, bufferSizeTotal - byteLenN));
  if(0u != memset_result)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_privatePlain, MCUXCLRSA_STATUS_ERROR);
  }

  uint32_t * pExpTemp = (uint32_t *)pOperands + MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE((MCUXCLRSA_INTERNAL_PRIVPLAIN_UPTRT_SIZE * sizeof(uint16_t)))/sizeof(uint32_t);

  MCUXCLPKC_PS1_SETLENGTH(0u, operandSize);
  MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_N, pKey->pMod1->pKeyEntryData, byteLenN);

  MCUXCLPKC_FP_CALC_OP1_CMP(MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_X, MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_N);
  MCUXCLPKC_WAITFORFINISH();

  uint32_t carryFlag = MCUXCLPKC_GETCARRY();

  if(MCUXCLPKC_FLAG_CARRY != carryFlag)
  {

    MCUXCLPKC_PS1_SETLENGTH(0u, bufferSizeTotal);
    MCUXCLPKC_FP_CALC_OP1_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_X, 0u);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_privatePlain, MCUXCLRSA_STATUS_INVALID_INPUT,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CONST);
  }

  MCUXCLPKC_FP_CALC_OP1_SUB_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_T2, MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_X, 1u);
  MCUXCLPKC_WAITFORFINISH();

  carryFlag = MCUXCLPKC_GETCARRY();
  uint32_t zeroFlag = MCUXCLPKC_GETZERO();

  if((MCUXCLPKC_FLAG_CARRY == carryFlag) || (MCUXCLPKC_FLAG_ZERO == zeroFlag))
  {
    MCUXCLPKC_FP_EXPORTBIGENDIANFROMPKC(pOutput, MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_X, byteLenN);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_privatePlain, MCUXCLRSA_INTERNAL_STATUS_KEYOP_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
        MCUXCLPKC_FP_CALLED_CALC_OP1_SUB_CONST,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ExportBigEndianFromPkc));
  }

  MCUXCLMATH_FP_NDASH(MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_N, MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_T0);

  MCUXCLPKC_PS1_SETLENGTH(operandSize, operandSize);
  MCUXCLMATH_FP_SHIFTMODULUS(MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_T3, MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_N);
  MCUXCLMATH_FP_QSQUARED(MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_R , MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_T3,
      MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_N, MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_T0);

  MCUXCLPKC_FP_CALC_MC1_MM(MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_T2 , MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_X ,
      MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_R , MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_N);

  MCUXCLPKC_WAITFORFINISH();

  MCUXCLMATH_FP_SECMODEXP(pExp,
                         pExpTemp,
                         byteLenD,
                         MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_R,
                         MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_T2,
                         MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_N,
                         MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_TE,
                         MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_T0,
                         MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_T1,
                         MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_X,
                         MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_T3);

  MCUXCLPKC_FP_CALC_MC1_MR(MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_T0, MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_R,
      MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_N);

  MCUXCLPKC_FP_CALC_MC1_MS(MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_X, MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_T0,
      MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_N, MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_N);
  MCUXCLPKC_WAITFORFINISH();

  MCUXCLPKC_FP_EXPORTBIGENDIANFROMPKC(pOutput, MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_X, byteLenN);

  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_privatePlain, MCUXCLRSA_INTERNAL_STATUS_KEYOP_OK,
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
      MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
      MCUXCLPKC_FP_CALLED_CALC_OP1_SUB_CONST,
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_NDash),
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ShiftModulus),
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_QSquared),
      MCUXCLPKC_FP_CALLED_CALC_MC1_MM,
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_SecModExp),
      MCUXCLPKC_FP_CALLED_CALC_MC1_MR,
      MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ExportBigEndianFromPkc));

}
