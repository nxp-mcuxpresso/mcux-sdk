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

/** @file  mcuxClRsa_pkcs1v15Decode_decrypt.c
 *  @brief mcuxClRsa: function, which is called to execute EME-PKCS1-v1_5
 *  decoding method used for RSAES-PKCS1-V1_5-DECRYPT decryption operation
 */

#include <mcuxClCore_Platform.h>
#include <mcuxClToolchain.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslDataIntegrity.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#include <mcuxClMemory.h>
#include <mcuxClRandom.h>
#include <mcuxClBuffer.h>

#include <mcuxClRsa.h>
#include <internal/mcuxClRsa_Internal_Types.h>
#include <internal/mcuxClRsa_Internal_Functions.h>

#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClBuffer_Internal.h>

/**
 * Definitions for constant values
 */
#define MCUXCLRSA_CHECK1_OK        (0x0001UL)
#define MCUXCLRSA_CHECK1_NOT_OK    (0x0004UL)
#define MCUXCLRSA_CHECK2_OK        (0x0010UL)
#define MCUXCLRSA_CHECK2_NOT_OK    (0x0040UL)
#define MCUXCLRSA_CHECK3_OK        (0x0100UL)
#define MCUXCLRSA_CHECK3_NOT_OK    (0x0400UL)
#define MCUXCLRSA_CHECK4_OK        (0x1000UL)
#define MCUXCLRSA_CHECK4_NOT_OK    (0x4000UL)

#define MCUXCLRSA_ALL_BITS_OK      (MCUXCLRSA_CHECK1_OK | MCUXCLRSA_CHECK2_OK | MCUXCLRSA_CHECK3_OK | MCUXCLRSA_CHECK4_OK)
#define MCUXCLRSA_MASK_CHECK_BITS  (~(MCUXCLRSA_CHECK1_OK | MCUXCLRSA_CHECK1_NOT_OK | MCUXCLRSA_CHECK2_OK | MCUXCLRSA_CHECK2_NOT_OK  \
                                  | MCUXCLRSA_CHECK3_OK | MCUXCLRSA_CHECK3_NOT_OK | MCUXCLRSA_CHECK4_OK | MCUXCLRSA_CHECK4_NOT_OK))


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_pkcs1v15Decode_decrypt, mcuxClRsa_PadVerModeEngine_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t) mcuxClRsa_pkcs1v15Decode_decrypt(
  mcuxClSession_Handle_t       pSession,
  mcuxCl_InputBuffer_t         pInput,
  const uint32_t              inputLength UNUSED_PARAM,
  uint8_t *                   pVerificationInput UNUSED_PARAM,
  mcuxClHash_Algo_t            pHashAlgo UNUSED_PARAM,
  mcuxCl_InputBuffer_t         pLabel UNUSED_PARAM,
  const uint32_t              saltlabelLength UNUSED_PARAM,
  const uint32_t              keyBitLength,
  const uint32_t              options UNUSED_PARAM,
  mcuxCl_Buffer_t              pOutput,
  uint32_t * const            pOutLength)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_pkcs1v15Decode_decrypt);

  /* Encoded message */
  /* Extract plain pointer from buffer type (this buffer has been created in internal memory by the calling function, for compatibility purposes) */
  const uint8_t *pEM = (const uint8_t *)MCUXCLBUFFER_GET(pInput);

  /* Size Encoded message */
  const uint32_t emLen = keyBitLength / 8u; //key bit length is always multiple of 8 bits

  /* Results accumulated of the four checks whether verification passed or failed */
  volatile uint32_t check = 0x0UL;

  /************************************************************************************************/
  /* Secure computation of PS length and value 0x00 location                                      */
  /************************************************************************************************/

  /* Generate a random byte not equal to 0x1 for XOR with the whole encoded message pEM */
  uint8_t rndByte = 0x1u;
  MCUXCLBUFFER_INIT(pBufRndByte, NULL, &rndByte, 1u);
  MCUX_CSSL_FP_FUNCTION_CALL(ret_Prng_GetRandom, mcuxClRandom_ncGenerate(pSession, pBufRndByte, 1u));
  rndByte |= 0x02u;
  if (MCUXCLRANDOM_STATUS_OK != ret_Prng_GetRandom)
  {
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pkcs1v15Decode_decrypt, MCUXCLRSA_STATUS_ERROR);
  }

  /* XOR the encoded message with the random byte and place it in the PKC RAM */
  uint8_t *pMaskedEMTemp = (uint8_t*)mcuxClSession_allocateWords_pkcWa(pSession, emLen / sizeof(uint32_t));
  if (NULL == pMaskedEMTemp)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pkcs1v15Decode_decrypt, MCUXCLRSA_STATUS_FAULT_ATTACK);
  }

  for(uint32_t i = 0u; i < emLen; ++i)
  {
    pMaskedEMTemp[i] = pEM[i] ^ rndByte;
  }

  const uint8_t* pMaskedEM = (const uint8_t*) pMaskedEMTemp;
  const uint8_t* pPS = pMaskedEM + 2u;
  uint8_t T[2] = {1u, 1u};
  uint32_t messageLen[2] = {0}; /* messageLen[0] - will contains length of message, messageLen[1] - will contains PS length + 1 */

  for(uint32_t i = 0u; i < (emLen - 2u); ++i)
  {
    uint8_t index = (T[1] != rndByte) ? 1u : 0u;
    messageLen[index] += 1u;
    T[index] = pPS[i * index];
  }

  /************************************************************************************************/
  /* There should be octet with hexadecimal value 0x00 to separate PS from M                      */
  /************************************************************************************************/

  uint32_t psLen = messageLen[1] - 1u;
  check |= (rndByte == pPS[psLen]) ? MCUXCLRSA_CHECK1_OK : MCUXCLRSA_CHECK1_NOT_OK;

  /************************************************************************************************/
  /* The length of PS should be at least eight octets                                             */
  /************************************************************************************************/

  check |= (7u < psLen) ? MCUXCLRSA_CHECK2_OK : MCUXCLRSA_CHECK2_NOT_OK;

  /************************************************************************************************/
  /* Check if the first octet of EM has hexadecimal value 0x00 (rndByte=0x00^rndByte)             */
  /************************************************************************************************/

  check |= (rndByte == pMaskedEM[0]) ? MCUXCLRSA_CHECK3_OK : MCUXCLRSA_CHECK3_NOT_OK;

  /************************************************************************************************/
  /* Check if the second octet of EM has hexadecimal value 0x02                                   */
  /************************************************************************************************/

  check |= ((0x2u^rndByte) == pMaskedEM[1]) ? MCUXCLRSA_CHECK4_OK : MCUXCLRSA_CHECK4_NOT_OK;

  /* Verify that all checks passed, and no failure */
  MCUX_CSSL_DI_RECORD(secCheck, check);
  if(0u != (MCUXCLRSA_MASK_CHECK_BITS & check))
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pkcs1v15Decode_decrypt, MCUXCLRSA_STATUS_FAULT_ATTACK);
  }
  else if(MCUXCLRSA_ALL_BITS_OK != check)
  {
    /* Free session area */
    mcuxClSession_freeWords_pkcWa(pSession, emLen / sizeof(uint32_t));

    MCUX_CSSL_DI_EXPUNGE(secCheck, check);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pkcs1v15Decode_decrypt, MCUXCLRSA_STATUS_INVALID_INPUT,
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate));
  }
  else
  {
    /* Empty else-statement */
  }


  /* Copy message to the output buffer */
  *pOutLength = messageLen[0];
  const uint8_t *pM = pEM + 2u + messageLen[1];

  /* TODO Shall be replaced under CLNS-6350 or CLNS-4506: secure (robust) copy shall be used when available */
  MCUX_CSSL_FP_FUNCTION_CALL(write_result, mcuxClBuffer_write(pOutput, 0u, pM, messageLen[0]));

  /* Free session area */
  mcuxClSession_freeWords_pkcWa(pSession, emLen / sizeof(uint32_t));
  if(MCUXCLBUFFER_STATUS_OK != write_result)
  {
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pkcs1v15Decode_decrypt, write_result,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_write));
  }

  /************************************************************************************************/
  /* Function exit                                                                                */
  /************************************************************************************************/

  MCUX_CSSL_DI_EXPUNGE(secCheck, MCUXCLRSA_ALL_BITS_OK);

  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pkcs1v15Decode_decrypt, MCUXCLRSA_STATUS_INTERNAL_ENCODE_OK,
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_write));
}