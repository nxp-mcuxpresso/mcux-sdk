/*--------------------------------------------------------------------------*/
/* Copyright 2023 NXP                                                       */
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

/** @file  mcuxClRsa_RemoveBlinding.c
 *  @brief mcuxClRsa: function, which is called to remove modulus blinding
 */

#include <stdint.h>
#include <mcuxClToolchain.h>

#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClPkc.h>
#include <mcuxClMath_Functions.h>
#include <internal/mcuxClPkc_Macros.h>
#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClRsa_Internal_PkcDefs.h>
#include <internal/mcuxClRsa_Internal_Types.h>
#include <internal/mcuxClRsa_Internal_Functions.h>
#include <internal/mcuxClRsa_RemoveBlinding_FUP.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_RemoveBlinding)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClRsa_RemoveBlinding(uint32_t iR_iX_iNb_iB,
  uint16_t iT2_iT1,
  uint32_t nbPkcByteLength,
  uint32_t bPkcByteLength)
{

  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_RemoveBlinding);

  /* Prepare local UPTRT. */
  uint16_t pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_REMOVEBLINDING_UPTRT_SIZE];
  const uint16_t *backupPtrUptrt;
  /* mcuxClMath_InitLocalUptrt always returns _OK. */
  MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClMath_InitLocalUptrt(iR_iX_iNb_iB, (uint32_t) iT2_iT1, pOperands, 6u, &backupPtrUptrt));
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_REMOVEBLINDING_ZERO] = 0x0u;

  /* Call the FUP program to convert result of the exponentiation to normal representation modulo Nb */
  MCUXCLPKC_FP_CALCFUP(mcuxClRsa_RemoveBlinding_FUP,
    mcuxClRsa_RemoveBlinding_FUP_LEN);
  
  /* Calculate R=T1/b */
  MCUXCLMATH_FP_EXACTDIVIDE(MCUXCLRSA_INTERNAL_UPTRTINDEX_REMOVEBLINDING_R,
    MCUXCLRSA_INTERNAL_UPTRTINDEX_REMOVEBLINDING_T1,
    MCUXCLRSA_INTERNAL_UPTRTINDEX_REMOVEBLINDING_B,
    MCUXCLRSA_INTERNAL_UPTRTINDEX_REMOVEBLINDING_T2,
    nbPkcByteLength,
    bPkcByteLength);

  /* Restore pUptrt. */
  MCUXCLPKC_WAITFORREADY();
  MCUXCLPKC_SETUPTRT(backupPtrUptrt);

  MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClRsa_RemoveBlinding,
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_InitLocalUptrt),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ExactDivide));
}
