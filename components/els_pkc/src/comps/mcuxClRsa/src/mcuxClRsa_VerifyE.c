/*--------------------------------------------------------------------------*/
/* Copyright 2021 NXP                                                       */
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

/** @file  mcuxClRsa_VerifyE.c
 *  @brief mcuxClRsa: function, which is called to check if E is FIPS compliant
 *  (i.e., is odd values in the range 2^16 < e < 2^256) and determines its
 *  length without leading zeros..
 */


#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClRsa.h>
#include <internal/mcuxClRsa_Internal_Functions.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_VerifyE)
mcuxClRsa_Status_Protected_t mcuxClRsa_VerifyE(mcuxClRsa_KeyEntry_t *pE, uint32_t *exactLength)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_VerifyE);

  mcuxClRsa_Status_t status = MCUXCLRSA_STATUS_INVALID_INPUT;

  /* Determine the exact length of e */
  uint32_t eLength = pE->keyEntryLength;
  while(eLength > 0u)
  {
     if(0u != pE->pKeyEntryData[pE->keyEntryLength - eLength])
     {
       break;
     }
     --eLength;
  }

  /* Check if it is the range 2^16 < e < 2^256 */
  if((eLength > 2u)  && (eLength < 33u))
  {
    /* Check if E is odd */
    if(0x1u == (pE->pKeyEntryData[pE->keyEntryLength - 1u] % 2u))
    {
      /* Set exact length of E */
      *exactLength = eLength;
      status = MCUXCLRSA_STATUS_KEYGENERATION_OK;
    }
  }

  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_VerifyE, status);
}
