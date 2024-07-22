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

#ifndef MCUXCLRANDOMMODES_PRIVATE_HMACDRBG_H_
#define MCUXCLRANDOMMODES_PRIVATE_HMACDRBG_H_

#include <mcuxClConfig.h> // Exported features flags header

#include <mcuxClHashModes_Constants.h>
#include <mcuxClMac.h>
#include <internal/mcuxClRandom_Internal_Types.h>
#include <internal/mcuxClRandomModes_Private_Drbg.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MCUXCLRANDOMMODES_RESEED_INTERVAL_HMAC_DRBG (0x0001000000000000u) /* 2^48 */

/* Even though these structs use SHA2 output size defines, they are applicable for SHA3 as well */
typedef struct
{
    MCUXCLRANDOMMODES_CONTEXT_DRBG_ENTRIES
    uint32_t key[MCUXCLHASH_OUTPUT_SIZE_SHA_512];
    uint32_t hmacV[MCUXCLHASH_OUTPUT_SIZE_SHA_512];
} mcuxClRandomModes_Context_HmacDrbg_Sha512_t;

typedef struct
{
    MCUXCLRANDOMMODES_CONTEXT_DRBG_ENTRIES
    uint32_t key[MCUXCLHASH_OUTPUT_SIZE_SHA_384];
    uint32_t hmacV[MCUXCLHASH_OUTPUT_SIZE_SHA_384];
} mcuxClRandomModes_Context_HmacDrbg_Sha384_t;

/* Also serves SHA_512_256 as is has the same output size per definition */
typedef struct
{
    MCUXCLRANDOMMODES_CONTEXT_DRBG_ENTRIES
    uint32_t key[MCUXCLHASH_OUTPUT_SIZE_SHA_256];
    uint32_t hmacV[MCUXCLHASH_OUTPUT_SIZE_SHA_256];
} mcuxClRandomModes_Context_HmacDrbg_Sha256_t;

/* Also serves SHA_512_224 as is has the same output size per definition */
typedef struct
{
    MCUXCLRANDOMMODES_CONTEXT_DRBG_ENTRIES
    uint32_t key[MCUXCLHASH_OUTPUT_SIZE_SHA_224];
    uint32_t hmacV[MCUXCLHASH_OUTPUT_SIZE_SHA_224];
} mcuxClRandomModes_Context_HmacDrbg_Sha224_t;

typedef struct
{
    MCUXCLRANDOMMODES_CONTEXT_DRBG_ENTRIES
    uint32_t key[MCUXCLHASH_OUTPUT_SIZE_SHA_1];
    uint32_t hmacV[MCUXCLHASH_OUTPUT_SIZE_SHA_1];
} mcuxClRandomModes_Context_HmacDrbg_Sha1_t;

typedef struct
{
    MCUXCLRANDOMMODES_CONTEXT_DRBG_ENTRIES
    uint32_t state[2u * MCUXCLHASH_MAX_OUTPUT_SIZE];
} mcuxClRandomModes_Context_HmacDrbg_Generic_t;


/* Internal function prototypes */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRandomModes_HmacDrbg_instantiateAlgorithm, mcuxClRandomModes_instantiateAlgorithm_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_HmacDrbg_instantiateAlgorithm(
        mcuxClSession_Handle_t pSession,
        mcuxClRandom_Mode_t mode,
        mcuxClRandom_Context_t context,
        uint8_t *pEntropyInputAndNonce);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRandomModes_HmacDrbg_generateAlgorithm, mcuxClRandomModes_generateAlgorithm_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_HmacDrbg_generateAlgorithm(
        mcuxClSession_Handle_t pSession,
        mcuxClRandom_Mode_t mode,
        mcuxClRandom_Context_t context,
        mcuxCl_Buffer_t pOut,
        uint32_t outLength);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRandomModes_HmacDrbg_UpdateState)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_HmacDrbg_UpdateState(
        mcuxClSession_Handle_t session,
        mcuxClRandom_Mode_t mode,
        mcuxClRandom_Context_t context,
        uint8_t *pProvidedData,
        uint32_t providedDataSize);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRandomModes_HmacDrbg_generateOutput)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_HmacDrbg_generateOutput(
        mcuxClSession_Handle_t pSession,
        mcuxClRandom_Mode_t mode,
        mcuxClRandom_Context_t context,
        mcuxCl_Buffer_t pOut,
        uint32_t outLength
);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLRANDOMMODES_PRIVATE_HMACDRBG_H_ */
