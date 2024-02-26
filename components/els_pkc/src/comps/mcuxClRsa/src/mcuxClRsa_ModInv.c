/*--------------------------------------------------------------------------*/
/* Copyright 2021, 2023 NXP                                                 */
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

/** @file  mcuxClRsa_ModInv.c
 *  @brief mcuxClRsa: function, which is called to compute modular inversion X^(-1) mod N
 *
 *  The implementation assumes that:
 *  - N is congruent 2 mod 4
 *  - size of X <= OPLEN = operandSize
 *  - content of N will be destroyed
 */

#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#include <mcuxClMath_Functions.h>
#include <internal/mcuxClPkc_Operations.h>

#include <mcuxClRsa.h>
#include <internal/mcuxClRsa_Internal_Functions.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_ModInv)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClRsa_ModInv(uint32_t iR_iX_iN_iT)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_ModInv);

  /* Get iR, iX, iN, and iT indices */
  uint32_t uptrtIndexR = (iR_iX_iN_iT >> 24) & 0xFFu;
  uint32_t uptrtIndexX = (iR_iX_iN_iT >> 16) & 0xFFu;
  uint32_t uptrtIndexN = (iR_iX_iN_iT >> 8) & 0xFFu;
  uint32_t uptrtIndexT = (iR_iX_iN_iT) & 0xFFu;

  /*
   * 1. Compute odd part of the N
   *    Nodd = N >> 1
   * Nodd should be placed in N buffer (there is one PKC word is reserved before N for NDash computed in step 2)
   */
  MCUXCLPKC_FP_CALC_OP1_SHR(uptrtIndexN, uptrtIndexN, 1);

  /*
   * 2. Calculate NDash of Nodd
   *
   * Used functions: mcuxClMath_NDash
   */
  MCUXCLMATH_FP_NDASH(uptrtIndexN, uptrtIndexT);

  /*
   * 3. Preform modular inversion of the odd part of the N
   *    Yodd = X^(-1) mod Nodd
   */
  MCUXCLMATH_FP_MODINV(uptrtIndexR, uptrtIndexX, uptrtIndexN, uptrtIndexT);

  /*
   * 4. Compute R = X^(-1) mod * N = (1 - Yodd mod 2) * Nodd + Yodd
   * Check the LSbit of Yodd:
   * if LSbit(Yodd) == 1 -> (1 - Yodd mod 2) = 0
   *   R = Yodd
   * else LSbit(Yodd) == 0 -> (1 - Yodd mod 2) = 1 ->
   *   R = Nodd + Yodd
   */
  const uint16_t *pUptrt = MCUXCLPKC_GETUPTRT();
  uint8_t *Yodd = (uint8_t *) MCUXCLPKC_OFFSET2PTR(pUptrt[uptrtIndexR]);
  MCUXCLPKC_WAITFORFINISH();
  const uint8_t lsbYodd = (Yodd[0] & 0x01u);
  if(0u == lsbYodd)
  {
    MCUXCLPKC_FP_CALC_OP1_ADD(uptrtIndexR, uptrtIndexR, uptrtIndexN);
  }

  MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClRsa_ModInv,
                            MCUXCLPKC_FP_CALLED_CALC_OP1_SHR,
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_NDash),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv),
                            ((lsbYodd == 0u) ? MCUXCLPKC_FP_CALLED_CALC_OP1_ADD : 0u));
}
