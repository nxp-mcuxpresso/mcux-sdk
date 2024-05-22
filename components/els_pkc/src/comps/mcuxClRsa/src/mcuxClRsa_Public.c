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

/** @file  mcuxClRsa_Public.c
 *  @brief mcuxClRsa: implementation of RSA Public function
 */

#include <stdint.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#include <mcuxClPkc.h>
#include <mcuxClMath.h>

#include <mcuxClRsa.h>

#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClPkc_Macros.h>
#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClPkc_ImportExport.h>
#include <internal/mcuxClRsa_Internal_PkcDefs.h>
#include <internal/mcuxClRsa_Internal_Functions.h>
#include <internal/mcuxClRsa_Internal_Types.h>
#include <internal/mcuxClRsa_Internal_Macros.h>
#include <internal/mcuxClRsa_Internal_MemoryConsumption.h>
#include <internal/mcuxClRsa_Internal_PkcTypes.h>
#include <internal/mcuxClRsa_Public_FUP.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_public, mcuxClRsa_PublicExpEngine_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t) mcuxClRsa_public(
  mcuxClSession_Handle_t      pSession,
  const mcuxClRsa_Key * const pKey,
  mcuxCl_InputBuffer_t        pInput,
  mcuxCl_Buffer_t             pOutput)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_public);

  /************************************************************************************************/
  /* Check the key type and key data;                                                             */
  /* if they are incorrect, MCUXCLRSA_STATUS_INVALID_INPUT is returned                             */
  /************************************************************************************************/
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


  /************************************************************************************************/
  /* Check that modulus is odd and that 64 < pKey->pMod1->keyEntryLength < 512 or 1024;           */
  /* otherwise return MCUXCLRSA_STATUS_INVALID_INPUT.                                              */
  /************************************************************************************************/
  const uint32_t byteLenN = pKey->pMod1->keyEntryLength;

  if((byteLenN < 64U) || (byteLenN > MCUXCLRSA_MAX_MODLEN) )
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_public, MCUXCLRSA_STATUS_INVALID_INPUT);
  }

  if(0U == (pKey->pMod1->pKeyEntryData[byteLenN - 1U] & 0x01U))
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_public, MCUXCLRSA_STATUS_INVALID_INPUT);
  }

  /************************************************************************************************/
  /* Initialization                                                                               */
  /************************************************************************************************/

  /* Prepare buffers in PKC workarea and clear PKC workarea */
  const uint32_t operandSize = MCUXCLRSA_PKC_ROUNDUP_SIZE(byteLenN);
  const uint16_t bufferSizeX = (uint16_t)operandSize;
  const uint16_t bufferSizeR = (uint16_t)operandSize + MCUXCLRSA_PKC_WORDSIZE;
  const uint16_t bufferSizeN = (uint16_t)operandSize + MCUXCLRSA_PKC_WORDSIZE; // PKC word in front of the modulus buffer for NDash
  const uint16_t bufferSizeT1 = (uint16_t)operandSize + MCUXCLRSA_PKC_WORDSIZE;
  const uint16_t bufferSizeT2 = (uint16_t)operandSize + MCUXCLRSA_PKC_WORDSIZE;

  /* Setup session. */
  const uint16_t bufferSizeTotal = bufferSizeX + bufferSizeN + bufferSizeR + bufferSizeT1 + bufferSizeT2;
  const uint32_t pkcWaSizeWord = (uint32_t) bufferSizeTotal / (sizeof(uint32_t));
  uint8_t *pPkcWorkarea = (uint8_t *) mcuxClSession_allocateWords_pkcWa(pSession, pkcWaSizeWord);
  if (NULL == pPkcWorkarea)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_public, MCUXCLRSA_STATUS_FAULT_ATTACK);
  }

  /* Setup UPTR table. */
  const uint32_t cpuWaSizeWord = (((sizeof(uint16_t)) * MCUXCLRSA_INTERNAL_PUBLIC_UPTRT_SIZE) + (sizeof(uint32_t)) - 1u) / (sizeof(uint32_t));
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("16-bit UPTRT table is assigned in CPU workarea")
  uint16_t *pOperands = (uint16_t *) mcuxClSession_allocateWords_cpuWa(pSession, cpuWaSizeWord);
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()
  if (NULL == pOperands)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_public, MCUXCLRSA_STATUS_FAULT_ATTACK);
  }

  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_X] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_R] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea + bufferSizeX);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_N] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea + bufferSizeX + bufferSizeR + MCUXCLRSA_PKC_WORDSIZE /* for NDash stored in the PKC word in front of the modulus */);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T1] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea + bufferSizeX + bufferSizeR + bufferSizeN);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T2] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea + bufferSizeX + bufferSizeR + bufferSizeN + bufferSizeT1);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_OUTPUT] = MCUXCLPKC_PTR2OFFSET(pOutput);

  /* Set UPTRT table */
  MCUXCLPKC_SETUPTRT(pOperands);

  /* Clear PKC workarea after the input, which is located at the beginning of the workarea and has a size of byteLenN */
  MCUXCLMEMORY_FP_MEMORY_SET(pPkcWorkarea + byteLenN, 0x00U, bufferSizeTotal - byteLenN);

  /************************************************************************************************/
  /* Copy (with reverse order) input and key material to respective buffers in PKC workarea      */
  /************************************************************************************************/

  /* Import N. */
  MCUXCLPKC_PS1_SETLENGTH(0u, operandSize);
  MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_N, pKey->pMod1->pKeyEntryData, byteLenN);
  /* Import input. */
  MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_X, pInput, byteLenN);

  /************************************************************************************************/
  /* Check that pInput < pKey->pMod1;  otherwise return MCUXCLRSA_STATUS_INVALID_INPUT             */
  /************************************************************************************************/
  MCUXCLPKC_FP_CALC_OP1_CMP(MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_X, MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_N);
  MCUXCLPKC_WAITFORFINISH();
  uint32_t carryFlag = MCUXCLPKC_GETCARRY();

  if(1U != carryFlag)
  {
    /* Clear PKC workarea. */
    MCUXCLPKC_PS1_SETLENGTH(0u, bufferSizeTotal);
    MCUXCLPKC_FP_CALC_OP1_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_X, 0u);

    MCUXCLPKC_WAITFORFINISH();
    mcuxClSession_freeWords_pkcWa(pSession, pkcWaSizeWord);
    mcuxClSession_freeWords_cpuWa(pSession, cpuWaSizeWord);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_public, MCUXCLRSA_STATUS_INVALID_INPUT,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CONST);
  }

  /* Compare input to 0. Note that in order to do that in one operation, result has to be written to a temporary buffer */
  MCUXCLPKC_FP_CALC_OP1_SUB_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T2, MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_X, 1U);
  MCUXCLPKC_WAITFORFINISH();

  carryFlag = MCUXCLPKC_GETCARRY();

  /* CARRY=1 ==> input=0, return input */
  if(MCUXCLPKC_FLAG_CARRY == carryFlag)
  {
    MCUXCLPKC_FP_CALC_OP1_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_OUTPUT, 0u);

    MCUXCLPKC_WAITFORFINISH();
    mcuxClSession_freeWords_pkcWa(pSession, pkcWaSizeWord);
    mcuxClSession_freeWords_cpuWa(pSession, cpuWaSizeWord);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_public, MCUXCLRSA_STATUS_INTERNAL_KEYOP_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
        MCUXCLPKC_FP_CALLED_CALC_OP1_SUB_CONST,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CONST);
  }

  /************************************************************************************************/
  /* Prepare Montgomery parameters and convert parameters to Montgomery representation.           */
  /************************************************************************************************/

  /* Calculate Ndash of N */
  MCUXCLMATH_FP_NDASH(MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_N, MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T1);

  /* Calculate QSquared */
  MCUXCLPKC_PS1_SETLENGTH(operandSize, operandSize);
  MCUXCLMATH_FP_SHIFTMODULUS(MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T1, MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_N); //shift modulus
  MCUXCLMATH_FP_QSQUARED(MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_R /* QSquared */, MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T1,
      MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_N, MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T2);

  /* Convert input to Montgomery representation i.e. M*QSquared mod N */
  MCUXCLPKC_FP_CALC_MC1_MM(MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T1 /* Mm */, MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_X /* M */,
      MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_R /* QSquared */, MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_N);

  /************************************************************************************************/
  /* Call mcuxClMath_ModExp_SqrMultL2R                                                             */
  /* Return checking is unnecessary, because it always returns OK.                                */
  /************************************************************************************************/

  //mcuxClMath_ModExp_SqrMultL2R(pExp, byteLenExp, iR_iX_iN_iT);
  //R -> size lenN + PKC wordsize
  //X -> size lenX
  //N -> size lenN + PKC word in front of the modulus buffer for NDash
  //T -> size lenN + PKC wordsize
  uint32_t byteLenExp = pKey->pExp1->keyEntryLength;
  MCUXCLMATH_FP_MODEXP_SQRMULTL2R(pExp, byteLenExp, MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T2, MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T1,
      MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_N, MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_R);

  /* Montgomery reduction and normalize the result */ 
  MCUXCLPKC_FP_CALCFUP(mcuxClRsa_Public_ReductionME_FUP,
          mcuxClRsa_Public_ReductionME_FUP_LEN);
  MCUXCLPKC_WAITFORFINISH();

  /************************************************************************************************/
  /* Function exit                                                                                */
  /************************************************************************************************/

  mcuxClSession_freeWords_pkcWa(pSession, pkcWaSizeWord);
  mcuxClSession_freeWords_cpuWa(pSession, cpuWaSizeWord);

  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_public, MCUXCLRSA_STATUS_INTERNAL_KEYOP_OK,
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
        MCUXCLPKC_FP_CALLED_CALC_OP1_SUB_CONST,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_NDash),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ShiftModulus),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_QSquared),
        MCUXCLPKC_FP_CALLED_CALC_MC1_MM,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModExp_SqrMultL2R),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)
        );
}
