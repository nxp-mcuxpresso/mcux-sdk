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

/** @file  mcuxClRsa_pkcs1v15Encode_encrypt.c
 *  @brief mcuxClRsa: function, which is called to execute EME-PKCS1-v1_5
 *  encoding method used for RSAES-PKCS1-V1_5-ENCRYPT encryption operation
 */

#include <stdint.h>
#include <mcuxClToolchain.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#include <mcuxClMemory.h>
#include <mcuxClRandom.h>
#include <mcuxClBuffer.h>
#include <internal/mcuxClBuffer_Internal.h>

#include <mcuxClRsa.h>
#include <internal/mcuxClRsa_Internal_Types.h>
#include <internal/mcuxClRsa_Internal_Functions.h>
#include <internal/mcuxClBuffer_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_pkcs1v15Encode_encrypt, mcuxClRsa_PadVerModeEngine_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t) mcuxClRsa_pkcs1v15Encode_encrypt(
  mcuxClSession_Handle_t       pSession,
  mcuxCl_InputBuffer_t         pInput,
  const uint32_t              inputLength,
  uint8_t *                   pVerificationInput UNUSED_PARAM,
  mcuxClHash_Algo_t            pHashAlgo UNUSED_PARAM,
  mcuxCl_InputBuffer_t         pLabel UNUSED_PARAM,
  const uint32_t              saltlabelLength UNUSED_PARAM,
  const uint32_t              keyBitLength,
  const uint32_t              options UNUSED_PARAM,
  mcuxCl_Buffer_t              pOutput,
  uint32_t * const            pOutLength UNUSED_PARAM)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_pkcs1v15Encode_encrypt);

  /***********************************************************/
  /* Length checking: If inputLength > keyLen - 11, return   */
  /* MCUXCLRSA_STATUS_INVALID_INPUT.                          */
  /***********************************************************/
  const uint32_t keyLen = keyBitLength / 8u; //key bit length is always multiple of 8 bits
  if(inputLength > (keyLen - 11u))
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pkcs1v15Encode_encrypt, MCUXCLRSA_STATUS_INVALID_INPUT);
  }

  /******************************************************************/
  /* Generate an octet string PS of length keyLen - inputLength - 3 */
  /* consisting of pseudo-randomly generated nonzero octets.        */
  /*******************************************************************/

  /* Length of the PS. */
  const uint32_t psLen = keyLen - inputLength - 3u;
  /* Extract plain pointer from buffer type (this buffer has been created in internal memory by the calling function, for compatibility purposes) */
  uint8_t *pEM = MCUXCLBUFFER_GET(pOutput);
  uint8_t *pPS = pEM + 2u;

  MCUXCLBUFFER_INIT(pBufPs, NULL, pPS, psLen);
  MCUX_CSSL_FP_FUNCTION_CALL(ret_Prng_GetRandom1, mcuxClRandom_ncGenerate(pSession, pBufPs, psLen));
  if(MCUXCLRANDOM_STATUS_OK != ret_Prng_GetRandom1)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pkcs1v15Encode_encrypt, MCUXCLRSA_STATUS_ERROR);
  }

  /* Ensuring that all octets are non-zero */
  uint32_t i = 0;
  MCUX_CSSL_FP_COUNTER_STMT(uint32_t cntPrngGetRandom = 0u);
  while(i < psLen)
  {
    /* If there is zero octet generate new one */
    while(0u == pPS[i])
    {
      MCUXCLBUFFER_SET(pBufPs, pPS + i, psLen);
      MCUX_CSSL_FP_FUNCTION_CALL(ret_Prng_GetRandom2, mcuxClRandom_ncGenerate(pSession, pBufPs, 1u));
      MCUX_CSSL_FP_COUNTER_STMT(++cntPrngGetRandom);
      if(MCUXCLRANDOM_STATUS_OK != ret_Prng_GetRandom2)
      {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pkcs1v15Encode_encrypt, MCUXCLRSA_STATUS_ERROR);
      }
    }
    ++i;
  }

  /************************************************************/
  /* Concatenate PS, the message M, and other padding to form */
  /* an encoded message EM of length keyLen octets as         */
  /* EM = 0x00 || 0x02 || PS || 0x00 || M                     */
  /************************************************************/

  pEM[0] = 0x0u;
  pEM[1] = 0x02u;
  pEM[2u + psLen] = 0x0u;
  uint8_t *pM = pEM + 2u + psLen + 1u;

  /* Concatenate message */
  /* TODO Shall be replaced under CLNS-6350 or CLNS-4506: secure (robust) copy shall be used when available */
  MCUX_CSSL_FP_FUNCTION_CALL(read_result, mcuxClBuffer_read(pInput, 0u, (uint8_t *) pM,  inputLength));
  if(MCUXCLBUFFER_STATUS_OK != read_result)
  {
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pkcs1v15Encode_encrypt, read_result,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
        (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate) * cntPrngGetRandom),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read));
  }

  /************************************************************************************************/
  /* Function exit                                                                                */
  /************************************************************************************************/

  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pkcs1v15Encode_encrypt, MCUXCLRSA_STATUS_INTERNAL_ENCODE_OK,
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
    (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate) * cntPrngGetRandom),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read));
}
