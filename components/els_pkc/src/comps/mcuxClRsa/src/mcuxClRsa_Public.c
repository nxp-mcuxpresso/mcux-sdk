/*--------------------------------------------------------------------------*/
/* Copyright 2020-2024 NXP                                                  */
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

#include <internal/mcuxClBuffer_Internal.h>
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


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_public, mcuxClRsa_PublicExpEngine_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t) mcuxClRsa_public(
  mcuxClSession_Handle_t      pSession,
  const mcuxClRsa_Key * const pKey,
  mcuxCl_InputBuffer_t        pInput,
  uint8_t *                  pOutput)
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
  const uint32_t blindLen = MCUXCLRSA_INTERNAL_MOD_BLINDING_SIZE;  // length in bytes of the random value used for blinding
  const uint32_t blindAlignLen = MCUXCLRSA_ALIGN_TO_PKC_WORDSIZE(blindLen);
  const uint32_t operandSize = MCUXCLRSA_ALIGN_TO_PKC_WORDSIZE(byteLenN);
  const uint32_t blindOperandSize = operandSize + blindAlignLen;
  const uint32_t bufferSizeX = blindOperandSize;
  const uint32_t bufferSizeN = blindOperandSize + MCUXCLRSA_PKC_WORDSIZE; // PKC word in front of the modulus buffer for NDash
  const uint32_t bufferSizeT1 = blindOperandSize + MCUXCLRSA_PKC_WORDSIZE;
  const uint32_t bufferSizeT2 = blindOperandSize + MCUXCLRSA_PKC_WORDSIZE;
  const uint32_t bufferSizeT3 = blindOperandSize + MCUXCLRSA_PKC_WORDSIZE;
  const uint32_t bufferSizeRand = blindAlignLen;  // size of buffer for random multiplicative blinding

  /* Setup session. */
  const uint32_t bufferSizeTotal = bufferSizeX + bufferSizeN + bufferSizeT3 + bufferSizeT1 + bufferSizeT2 + bufferSizeRand;
  const uint32_t pkcWaSizeWord = bufferSizeTotal / (sizeof(uint32_t));
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
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_N] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea + bufferSizeX + MCUXCLRSA_PKC_WORDSIZE /* for NDash stored in the PKC word in front of the modulus */);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T1] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea + bufferSizeX + bufferSizeN);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T2] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea + bufferSizeX + bufferSizeN + bufferSizeT1);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T3] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea + bufferSizeX + bufferSizeN + bufferSizeT1 + bufferSizeT2);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_OUTPUT] = MCUXCLPKC_PTR2OFFSET(pOutput);
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_CASTING("pPkcWorkarea is word aligned in PKC workarea.")
  uint32_t *pBlind = ((uint32_t *)pPkcWorkarea + (bufferSizeX + bufferSizeT3 + bufferSizeN + bufferSizeT1 + bufferSizeT2)/sizeof(uint32_t));
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_CASTING()
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_RAND] = MCUXCLPKC_PTR2OFFSET((uint8_t *) pBlind);

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
  MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC_BUFFER(mcuxClRsa_public, MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_X, pInput, byteLenN);

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
        MCUXCLPKC_FP_CALLED_IMPORTBIGENDIANTOPKC_BUFFER,
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
        MCUXCLPKC_FP_CALLED_IMPORTBIGENDIANTOPKC_BUFFER,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
        MCUXCLPKC_FP_CALLED_CALC_OP1_SUB_CONST,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CONST);
  }


  MCUX_CSSL_FP_FUNCTION_CALL(retPublicExp, mcuxClRsa_publicExp(pSession,
    MCUXCLPKC_PACKARGS4(MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_OUTPUT,
                       MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_X,
                       MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_N,
                       MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T1),
    MCUXCLPKC_PACKARGS4(0, MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T3,
                       MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T2,
                       MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_RAND),
    pKey->pExp1->keyEntryLength,
    pExp));
  if (MCUXCLRSA_STATUS_INTERNAL_KEYOP_OK != retPublicExp)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_public, MCUXCLRSA_STATUS_ERROR,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
        MCUXCLPKC_FP_CALLED_IMPORTBIGENDIANTOPKC_BUFFER,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
        MCUXCLPKC_FP_CALLED_CALC_OP1_SUB_CONST,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_publicExp));

  }

  /************************************************************************************************/
  /* Function exit                                                                                */
  /************************************************************************************************/

  mcuxClSession_freeWords_pkcWa(pSession, pkcWaSizeWord);
  mcuxClSession_freeWords_cpuWa(pSession, cpuWaSizeWord);

  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_public, MCUXCLRSA_STATUS_INTERNAL_KEYOP_OK,
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
        MCUXCLPKC_FP_CALLED_IMPORTBIGENDIANTOPKC_BUFFER,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
        MCUXCLPKC_FP_CALLED_CALC_OP1_SUB_CONST,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_publicExp)
        );
}
