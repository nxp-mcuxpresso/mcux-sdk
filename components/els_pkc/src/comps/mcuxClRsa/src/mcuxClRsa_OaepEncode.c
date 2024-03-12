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

/** @file  mcuxClRsa_OaepEncode.c
 *  @brief mcuxClRsa: function, which is called to execute RSAES-OAEP-ENCRYPT
 */

#include <stdint.h>
#include <mcuxClToolchain.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#include <mcuxClPkc_Types.h>
#include <mcuxClMemory.h>
#include <mcuxClHash.h>
#include <mcuxClRandom.h>
#include <mcuxClBuffer.h>

#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClHash_Internal.h>
#include <internal/mcuxClBuffer_Internal.h>
#include <internal/mcuxClRsa_Internal_MemoryConsumption.h>
#include <mcuxClRsa.h>
#include <internal/mcuxClRsa_Internal_Types.h>
#include <internal/mcuxClRsa_Internal_Functions.h>
#include <internal/mcuxClRsa_Internal_Macros.h>
#include <internal/mcuxClRsa_Internal_Functions.h>
#include <internal/mcuxClRsa_Internal_PkcTypes.h>
#include <internal/mcuxClBuffer_Internal.h>


/*
* Implementation of OAEP encoding according to PKCS#1v2.2
*/

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_oaepEncode, mcuxClRsa_PadVerModeEngine_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t) mcuxClRsa_oaepEncode(
  mcuxClSession_Handle_t       pSession,
  mcuxCl_InputBuffer_t         pInput,
  const uint32_t              inputLength,
  uint8_t *                   pVerificationInput UNUSED_PARAM,
  mcuxClHash_Algo_t            pHashAlgo,
  mcuxCl_InputBuffer_t         pLabel,
  const uint32_t              saltlabelLength,
  const uint32_t              keyBitLength,
  const uint32_t              options UNUSED_PARAM,
  mcuxCl_Buffer_t              pOutput,
  uint32_t * const            pOutLength UNUSED_PARAM
)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_oaepEncode);
  /* Extract plain pointer from buffer type (this buffer has been created in internal memory by the calling function, for compatibility purposes) */
  uint8_t *pOutputPointer = MCUXCLBUFFER_GET(pOutput);

  /*
  1a.If the length of L is greater than the input limitation
    for the hash function, output "label too long" and stop.
    <No real need to do this check, saltlabelLength is uint32_t, so the same as the input length for mcuxClHash_compute>
  */

  /*
  1b. If mLen > k - 2hLen - 2, output "message too long" and
    stop.
  */
  uint32_t keyByteLength = keyBitLength / 8u;
  if ( inputLength > (keyByteLength - (2u * pHashAlgo->hashSize) - 2u) )
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_oaepEncode, MCUXCLRSA_STATUS_INVALID_INPUT);
  }

  /*
  2a. If the label L is not provided, let L be the empty string.
    Let lHash = Hash(pLabel), an octet string of length hLen.
  */
  uint32_t hashOutputSize = 0u;
  uint32_t psLen = keyByteLength - inputLength - (pHashAlgo->hashSize * 2u) - 2u;
  uint32_t dbLen = pHashAlgo->hashSize + 1u + inputLength + psLen;

  const uint32_t pkcWaSizeWord = MCUXCLRSA_INTERNAL_OAEPENCODE_WAPKC_SIZE_WO_MGF1(keyByteLength) / sizeof(uint32_t);
  uint8_t *pPkcWorkarea = (uint8_t *) mcuxClSession_allocateWords_pkcWa(pSession, pkcWaSizeWord);
  if (NULL == pPkcWorkarea)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_oaepEncode, MCUXCLRSA_STATUS_FAULT_ATTACK);
  }

  uint32_t usedPkcWorkarea = 0;
  uint8_t *db = &pPkcWorkarea[usedPkcWorkarea];
  usedPkcWorkarea += MCUXCLRSA_ALIGN_TO_PKC_WORDSIZE(dbLen);

  MCUXCLBUFFER_INIT(dbBuf, pSession, db, pHashAlgo->hashSize);
  MCUX_CSSL_FP_FUNCTION_CALL(hash_result,
      mcuxClHash_compute(pSession, pHashAlgo, pLabel, saltlabelLength, dbBuf, &hashOutputSize) );

  if(MCUXCLHASH_STATUS_OK != hash_result)
  {
    mcuxClSession_freeWords_pkcWa(pSession, pkcWaSizeWord);
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_oaepEncode, MCUXCLRSA_STATUS_ERROR);
  }

  /*
  2b. Generate a padding string PS consisting of k - mLen -
    2hLen - 2 zero octets. The length of PS may be zero.
  */

  MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClMemory_set( &db[pHashAlgo->hashSize], 0x00u, psLen, psLen));

  /*
  3c. DB = lHash || PS || 0x01 || M.
  */
  db[pHashAlgo->hashSize + psLen] = 0x01;
  //TODO CLNS-6350 or CLNS-4506: secure (robust) copy shall be used when available
  MCUX_CSSL_FP_FUNCTION_CALL(read_result, mcuxClBuffer_read(pInput, 0u, &db[pHashAlgo->hashSize + psLen + 1u], inputLength));
  if(MCUXCLBUFFER_STATUS_OK != read_result)
  {
      mcuxClSession_freeWords_pkcWa(pSession, pkcWaSizeWord);
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_oaepEncode, read_result,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_compute),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read));
  }

/*
d. Generate a random octet string seed of length hLen.
*/
  uint8_t *seed = &pPkcWorkarea[usedPkcWorkarea];
  usedPkcWorkarea += MCUXCLRSA_ALIGN_TO_PKC_WORDSIZE(pHashAlgo->hashSize);
  MCUXCLBUFFER_INIT(pBufSeed, NULL, seed, pHashAlgo->hashSize);
  MCUX_CSSL_FP_FUNCTION_CALL(ret_Random_ncGenerate, mcuxClRandom_ncGenerate(pSession, pBufSeed , pHashAlgo->hashSize));
  if(MCUXCLRANDOM_STATUS_OK != ret_Random_ncGenerate)
  {
    mcuxClSession_freeWords_pkcWa(pSession, pkcWaSizeWord);
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_oaepEncode, MCUXCLRSA_STATUS_ERROR);
  }

/*
e. Let dbMask = MGF(seed, k - hLen - 1).
*/
  uint8_t *dbMask = &pPkcWorkarea[usedPkcWorkarea];
  usedPkcWorkarea += MCUXCLRSA_ALIGN_TO_PKC_WORDSIZE(dbLen);
  MCUX_CSSL_FP_FUNCTION_CALL(retVal_mcuxClRsa_mgf1, mcuxClRsa_mgf1(pSession, pHashAlgo, seed, pHashAlgo->hashSize, dbLen, dbMask));
  if(MCUXCLRSA_STATUS_INTERNAL_MGF_OK != retVal_mcuxClRsa_mgf1)
  {
    mcuxClSession_freeWords_pkcWa(pSession, pkcWaSizeWord);
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_oaepEncode, MCUXCLRSA_STATUS_ERROR);
  }

/*
  f. Let maskedDB = DB \xor dbMask.
*/
  for(uint32_t i = 0u; i < dbLen ; i++)
  {
    /*maskedDB*/pOutputPointer[1u + pHashAlgo->hashSize+ i] = dbMask[i] ^ db[i];
  }

/*
g. Let seedMask = MGF(maskedDB, hLen).
h. Let maskedSeed = seed \xor seedMask.
i. Concatenate a single octet with hexadecimal value 0x00,
    maskedSeed, and maskedDB to form an encoded message EM of length k octets as
    EM = 0x00 || maskedSeed || maskedDB.
*/
  uint8_t *seedMask = &pPkcWorkarea[usedPkcWorkarea];
  usedPkcWorkarea += MCUXCLRSA_ALIGN_TO_PKC_WORDSIZE(pHashAlgo->hashSize);

  MCUX_CSSL_FP_FUNCTION_CALL(retVal_mcuxClRsa_mgf1_2, mcuxClRsa_mgf1(pSession, pHashAlgo, &pOutputPointer[1ULL + pHashAlgo->hashSize], dbLen, pHashAlgo->hashSize, seedMask));
  if(MCUXCLRSA_STATUS_INTERNAL_MGF_OK != retVal_mcuxClRsa_mgf1_2)
  {
    mcuxClSession_freeWords_pkcWa(pSession, pkcWaSizeWord);
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_oaepEncode, MCUXCLRSA_STATUS_ERROR);
  }

  for(uint32_t i = 0u; i < pHashAlgo->hashSize ; i++)
  {
    /*maskedSeed*/pOutputPointer[1u + i] = seedMask[i] ^ seed[i];
  }

  pOutputPointer[0] = 0x00u;
  mcuxClSession_freeWords_pkcWa(pSession, pkcWaSizeWord);
  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_oaepEncode, MCUXCLRSA_STATUS_INTERNAL_ENCODE_OK,
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_compute),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_mgf1),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_mgf1)
                            );
}
