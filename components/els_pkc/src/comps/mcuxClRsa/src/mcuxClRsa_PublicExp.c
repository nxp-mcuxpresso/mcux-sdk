/*--------------------------------------------------------------------------*/
/* Copyright 2023-2024 NXP                                                  */
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

/** @file  mcuxClRsa_publicExp.c
 *  @brief mcuxClRsa: implementation of RSA Public expo with N blinded
 */

#include <stdint.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#include <mcuxClPkc.h>
#include <mcuxClMath.h>
#include <mcuxClRandom.h>

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

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_publicExp)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t) mcuxClRsa_publicExp(
  mcuxClSession_Handle_t      pSession,
  uint32_t iR_iX_iN_iT1,
  uint32_t iT2_iT3_iT4,
  uint32_t byteLenExp,
  const uint8_t* const pExp)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_publicExp);

  uint8_t iT1 = (uint8_t)(iR_iX_iN_iT1 & 0xFFu);
  uint8_t iN = (uint8_t)((iR_iX_iN_iT1 >> 8) & 0xFFu);
  uint8_t iX = (uint8_t)((iR_iX_iN_iT1 >> 16) & 0xFFu);
  uint8_t iR = (uint8_t)((iR_iX_iN_iT1 >> 24) & 0xFFu);
  uint8_t iRnd = (uint8_t)(iT2_iT3_iT4 & 0xFFu);
  uint8_t iT3 = (uint8_t)((iT2_iT3_iT4 >> 8) & 0xFFu);
  uint8_t iT2 = (uint8_t)((iT2_iT3_iT4 >> 16) & 0xFFu);

  const uint16_t *pUptrt = MCUXCLPKC_GETUPTRT();
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_CASTING("operand buffer is always word aligned in PKC workarea.")
  uint32_t *pBlind = (uint32_t *)MCUXCLPKC_OFFSET2PTR(pUptrt[iRnd]);
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_CASTING()
  uint32_t operandSize = MCUXCLPKC_PS1_GETOPLEN();
  const uint32_t blindAlignLen = MCUXCLRSA_ALIGN_TO_PKC_WORDSIZE(MCUXCLRSA_INTERNAL_MOD_BLINDING_SIZE);
  const uint32_t blindOperandSize = operandSize + blindAlignLen;
  uint32_t ps1LenBackup = MCUXCLPKC_PS1_GETLENGTH_REG();

  /* Generate random number used for blinding */
  MCUXCLBUFFER_INIT(pBufBlind, NULL, (uint8_t *) pBlind, MCUXCLRSA_INTERNAL_MOD_BLINDING_SIZE);
  MCUX_CSSL_FP_FUNCTION_CALL(ret_Random_ncGenerate1, mcuxClRandom_ncGenerate(pSession, pBufBlind, MCUXCLRSA_INTERNAL_MOD_BLINDING_SIZE));
  if (MCUXCLRANDOM_STATUS_OK != ret_Random_ncGenerate1)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_publicExp, MCUXCLRSA_STATUS_ERROR,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate));
  }
  /* Make it odd */
  pBlind[0] |= 0x1u;

  /* Blind modulus n */
  MCUXCLPKC_FP_CALC_OP1_MUL( iN/* n_b */, iRnd/* blind */, iN/* n */);

  /************************************************************************************************/
  /* Prepare Montgomery parameters and convert parameters to Montgomery representation.           */
  /************************************************************************************************/

  /* Calculate Ndash of N */
  MCUXCLPKC_WAITFORREADY();
  MCUXCLPKC_PS1_SETLENGTH(blindOperandSize, blindOperandSize);
  MCUXCLMATH_FP_NDASH(iN, iT3);

  /* Calculate QSquared */
  MCUXCLMATH_FP_SHIFTMODULUS(iT3, iN); //shift modulus
  MCUXCLMATH_FP_QSQUARED(iT1/* QSquared */, iT3, iN, iT2);

  /* Convert input to Montgomery representation i.e. M*QSquared mod N */
  MCUXCLPKC_FP_CALC_MC1_MM(iT3/* Mm */, iX/* M */, iT1/* QSquared */, iN);

  /************************************************************************************************/
  /* Call mcuxClMath_ModExp_SqrMultL2R                                                             */
  /* Return checking is unnecessary, because it always returns OK.                                */
  /************************************************************************************************/

  //mcuxClMath_ModExp_SqrMultL2R(pExp, byteLenExp, iR_iX_iN_iT);
  //T2 -> size lenN + PKC wordsize
  //T1 -> size lenX
  //N -> size lenN + PKC word in front of the modulus buffer for NDash
  //R -> size lenN + PKC wordsize
  MCUXCLMATH_FP_MODEXP_SQRMULTL2R(pExp, byteLenExp, iT2, iT3, iN, iT1);

  MCUXCLPKC_WAITFORFINISH();

  /************************************************************************************************/
  /* Convert result back to normal representation and store result in pOutput.                    */
  /************************************************************************************************/
  MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClRsa_RemoveBlinding(
    MCUXCLPKC_PACKARGS4(iR/* R */,
                       iT2/* Rb */,
                       iN/* Nb */,
                       iRnd/* b */),
    MCUXCLPKC_PACKARGS2(iT1,
                       iT3),
    blindOperandSize,
    blindAlignLen));

  MCUXCLPKC_WAITFORFINISH();

  /* Restore the PS1 len */
  MCUXCLPKC_PS1_SETLENGTH_REG(ps1LenBackup);
  /************************************************************************************************/
  /* Function exit                                                                                */
  /************************************************************************************************/

  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_publicExp, MCUXCLRSA_STATUS_INTERNAL_KEYOP_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
        MCUXCLPKC_FP_CALLED_CALC_OP1_MUL,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_NDash),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ShiftModulus),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_QSquared),
        MCUXCLPKC_FP_CALLED_CALC_MC1_MM,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModExp_SqrMultL2R),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_RemoveBlinding)
        );
}
