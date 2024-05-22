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

/**
 * @file  mcuxClEcc_EdDSA_Internal_Hash.h
 * @brief internal header for abstracting hash calls in mcuxClEcc EdDSA
 */


#ifndef MCUXCLECC_EDDSA_INTERNAL_HASH_H_
#define MCUXCLECC_EDDSA_INTERNAL_HASH_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClHash_Types.h>
#include <mcuxClHash_Functions.h>
#include <mcuxClHash_Constants.h>

#include <internal/mcuxClSession_Internal.h>


/******************************************************************************/
/* Macro to compute private key hash and store it in PKC workarea.            */
/* Since the parameter b of both Ed25519 and Ed448 is a multiple of 8,        */
/* byte length of private key hash (= 2b/8) can be derived from               */
/* byte length of private key (= b/8).                                        */
/******************************************************************************/
#define MCUXCLECC_FP_EDDSA_KEYGEN_HASH_PRIVKEY(pSession, hashAlg, pPrivKey, pPrivKeyHash, privKeyLen)  \
    do{                                                                \
        uint32_t outLength = 0u;                                       \
        MCUXCLPKC_WAITFORFINISH();                                      \
        MCUX_CSSL_FP_FUNCTION_CALL(retHash,                             \
            mcuxClHash_compute(pSession,                                \
                              hashAlg,                                 \
                              (mcuxCl_InputBuffer_t) (pPrivKey),        \
                              privKeyLen,                              \
                              (mcuxCl_Buffer_t) (pPrivKeyHash),         \
                              &outLength) );                           \
        if (MCUXCLHASH_STATUS_OK != retHash)                            \
        {                                                              \
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_GenerateKeyPair,  \
                                      MCUXCLECC_STATUS_FAULT_ATTACK);   \
        }                                                              \
MCUX_CSSL_ANALYSIS_START_SUPPRESS_BOOLEAN_TYPE_FOR_CONDITIONAL_EXPRESSION() \
    } while(false)                                                          \
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_BOOLEAN_TYPE_FOR_CONDITIONAL_EXPRESSION()


#define MCUXCLECC_FP_CALLED_EDDSA_KEYGEN_HASH_PRIVKEY  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_compute)


/******************************************************************************/
/* Macros to compute the hash H(prefix || (h_b,...,h_{2b-1}) || m') using     */
/*   - the hash function algoSecHash to hash the blocks containing the secret */
/*     (h_b,\dots,h_{2b-1}), and                                              */
/*   - the hash function algoHash to hash the remaining part of the input     */
/* Since the parameter b of both Ed25519 and Ed448 is a multiple of 8,        */
/* byte length of hash (= 2b/8) can be derived from                           */
/* byte length of (h_b,...,h_{2b-1}) (= b/8).                                 */
/******************************************************************************/
#define MCUXCLECC_FP_EDDSA_SIGN_CALC_SCALAR(pSession, pCtx, algoHash, algoSecHash, pHashPrefix, hashPrefixLen, pPrivKeyHalfHash, privKeyHalfHashLength, pIn, inSize, pOutput) \
    do{                                                                     \
        uint32_t outLength = 0u;                                            \
                                                                            \
        (void) (algoHash); /* TODO: Use algoHash for blocks with not sensitive data (CLNS-7002) */ \
                                                                            \
        /* Initialize the hash context */                                   \
        MCUX_CSSL_FP_FUNCTION_CALL(retInitHash,                              \
            mcuxClHash_init(pSession,                                        \
                           pCtx,                                            \
                           algoSecHash) );                                  \
        if (MCUXCLHASH_STATUS_OK != retInitHash)                             \
        {                                                                   \
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_GenerateSignature,     \
                                      MCUXCLECC_STATUS_FAULT_ATTACK);        \
        }                                                                   \
                                                                            \
        /* Update hash context with prefix */                               \
        MCUX_CSSL_FP_FUNCTION_CALL(retProcess1Hash,                          \
            mcuxClHash_process(pSession,                                     \
                              pCtx,                                         \
                              (mcuxCl_InputBuffer_t) (pHashPrefix),          \
                              hashPrefixLen) );                             \
        if (MCUXCLHASH_STATUS_OK != retProcess1Hash)                         \
        {                                                                   \
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_GenerateSignature,     \
                                      MCUXCLECC_STATUS_FAULT_ATTACK);        \
        }                                                                   \
                                                                            \
        /* Update hash context with (h_b,...,h_{2b-1}) */                   \
        MCUX_CSSL_FP_FUNCTION_CALL(retProcess2Hash,                          \
            mcuxClHash_process(pSession,                                     \
                              pCtx,                                         \
                              (mcuxCl_InputBuffer_t) (pPrivKeyHalfHash),     \
                              privKeyHalfHashLength) );                     \
        if (MCUXCLHASH_STATUS_OK != retProcess2Hash)                         \
        {                                                                   \
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_GenerateSignature,     \
                                      MCUXCLECC_STATUS_FAULT_ATTACK);        \
        }                                                                   \
                                                                            \
        /* Update hash context with m' */                                   \
        MCUX_CSSL_FP_FUNCTION_CALL(retProcess3Hash,                          \
            mcuxClHash_process(pSession,                                     \
                              pCtx,                                         \
                              (mcuxCl_InputBuffer_t) (pIn),                  \
                              inSize) );                                    \
        if (MCUXCLHASH_STATUS_OK != retProcess3Hash)                         \
        {                                                                   \
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_GenerateSignature,     \
                                      MCUXCLECC_STATUS_FAULT_ATTACK);        \
        }                                                                   \
                                                                            \
        /* Finalize hash computation */                                     \
        MCUXCLPKC_WAITFORFINISH();                                           \
        MCUX_CSSL_FP_FUNCTION_CALL(retFinishHash,                            \
            mcuxClHash_finish(pSession,                                      \
                              pCtx,                                         \
                              pOutput,                                      \
                              &outLength) );                                \
        if (MCUXCLHASH_STATUS_OK != retFinishHash)                           \
        {                                                                   \
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_GenerateSignature,     \
                                      MCUXCLECC_STATUS_FAULT_ATTACK);        \
        }                                                                   \
MCUX_CSSL_ANALYSIS_START_SUPPRESS_BOOLEAN_TYPE_FOR_CONDITIONAL_EXPRESSION() \
    } while(false)                                                          \
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_BOOLEAN_TYPE_FOR_CONDITIONAL_EXPRESSION()

#define MCUXCLECC_FP_CALLED_EDDSA_SIGN_CALC_SCALAR   \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_init),    \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process), \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process), \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process), \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_finish)


/******************************************************************************/
/* Macro to compute input hash and store it in PKC workarea.                  */
/* Since the parameter b of both Ed25519 and Ed448 is a multiple of 8,        */
/* byte length of hash (= 2b/8) can be derived from                           */
/* byte length of encoded public key (= b/8).                                 */
/******************************************************************************/
#define MCUXCLECC_FP_EDDSA_SIGN_VERIFY_CALC_HASH(pSession, pCtx, hashAlg, pHashPrefix, hashPrefixLen, pSignatureR, signatureRLen, pPubKey, pubKeyLen, pIn, inSize, pOutput) \
    do{                                                                     \
        uint32_t outLength = 0u;                                            \
                                                                            \
        /* Initialize the hash context */                                   \
        MCUX_CSSL_FP_FUNCTION_CALL(retInitHash,                              \
            mcuxClHash_init(pSession,                                        \
                            pCtx,                                           \
                            hashAlg) );                                     \
        if (MCUXCLHASH_STATUS_OK != retInitHash)                             \
        {                                                                   \
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_CalcHashModN,          \
                                      MCUXCLECC_STATUS_FAULT_ATTACK);        \
        }                                                                   \
                                                                            \
        /* Update hash context with prefix */                               \
        MCUX_CSSL_FP_FUNCTION_CALL(retProcess1Hash,                          \
            mcuxClHash_process(pSession,                                     \
                            pCtx,                                           \
                            (mcuxCl_InputBuffer_t) (pHashPrefix),            \
                            hashPrefixLen) );                               \
        if (MCUXCLHASH_STATUS_OK != retProcess1Hash)                         \
        {                                                                   \
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_CalcHashModN,          \
                                    MCUXCLECC_STATUS_FAULT_ATTACK);          \
        }                                                                   \
                                                                            \
        /* Update hash context with Renc */                                 \
        MCUX_CSSL_FP_FUNCTION_CALL(retProcess2Hash,                          \
            mcuxClHash_process(pSession,                                     \
                              pCtx,                                         \
                              (mcuxCl_InputBuffer_t) (pSignatureR),          \
                              signatureRLen) );                             \
        if (MCUXCLHASH_STATUS_OK != retProcess2Hash)                         \
        {                                                                   \
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_CalcHashModN,          \
                                      MCUXCLECC_STATUS_FAULT_ATTACK);        \
        }                                                                   \
                                                                            \
        /* Update hash context with Qenc */                                 \
        MCUX_CSSL_FP_FUNCTION_CALL(retProcess3Hash,                          \
            mcuxClHash_process(pSession,                                     \
                              pCtx,                                         \
                              (mcuxCl_InputBuffer_t) (pPubKey),              \
                              pubKeyLen) );                                 \
        if (MCUXCLHASH_STATUS_OK != retProcess3Hash)                         \
        {                                                                   \
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_CalcHashModN,          \
                                      MCUXCLECC_STATUS_FAULT_ATTACK);        \
        }                                                                   \
                                                                            \
        /* Update hash context with m' */                                   \
        MCUX_CSSL_FP_FUNCTION_CALL(retProcess4Hash,                          \
            mcuxClHash_process(pSession,                                     \
                              pCtx,                                         \
                              (mcuxCl_InputBuffer_t) (pIn),                  \
                              inSize) );                                    \
        if (MCUXCLHASH_STATUS_OK != retProcess4Hash)                         \
        {                                                                   \
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_CalcHashModN,          \
                                      MCUXCLECC_STATUS_FAULT_ATTACK);        \
        }                                                                   \
                                                                            \
        MCUXCLPKC_WAITFORFINISH();                                           \
        /* Finalize hash computation */                                     \
        MCUX_CSSL_FP_FUNCTION_CALL(retFinishHash,                            \
            mcuxClHash_finish(pSession,                                      \
                              pCtx,                                         \
                              (mcuxCl_Buffer_t) pOutput,                     \
                              &outLength) );                                \
        if (MCUXCLHASH_STATUS_OK != retFinishHash)                           \
        {                                                                   \
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_CalcHashModN,          \
                                      MCUXCLECC_STATUS_FAULT_ATTACK);        \
        }                                                                   \
    } while(false)

#define MCUXCLECC_FP_CALLED_EDDSA_SIGN_VERIFY_CALC_HASH                  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_init),                        \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process),                     \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process),                     \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process),                     \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process),                     \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_finish)

#endif /* MCUXCLECC_EDDSA_INTERNAL_HASH_H_ */
