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
 * @file  mcuxClEcc_EdDSA_Internal.h
 * @brief internal header of mcuxClEcc EdDSA functionalities
 */


#ifndef MCUXCLECC_EDDSA_INTERNAL_H_
#define MCUXCLECC_EDDSA_INTERNAL_H_


#include <mcuxClCore_Platform.h>
#include <mcuxClSession.h>
#include <mcuxClKey_Types.h>
#include <mcuxClBuffer.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClHash_Types.h>

#include <mcuxClEcc_Types.h>
#include <internal/mcuxClEcc_Internal.h>
#include <internal/mcuxClEcc_TwEd_Internal_PkcWaLayout.h>

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************/
/* Internal return codes for EdDSA functions              */
/**********************************************************/
// None


/**********************************************************/
/* Internal EdDSA types                                   */
/**********************************************************/

/**
 * Decode function pointer structure for EdDsa point decoding.
 */
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClEcc_EdDSA_DecodePointFunction_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) (*mcuxClEcc_EdDSA_DecodePointFunction_t)(mcuxClEcc_EdDSA_DomainParams_t *pDomainParams,
                                                                                              mcuxCl_InputBuffer_t pEncPoint));

/**
 * Domain parameter structure for EdDSA functions.
 */
struct mcuxClEcc_EdDSA_DomainParams
{
    mcuxClEcc_CommonDomainParams_t common;  ///< structure containing pointers and lengths for common ECC parameters (see Common ECC Domain parameters)
    uint16_t b;                            ///< Integer satisfying 2^(b-1) > p. EdDSA public keys have exactly b bits, and EdDSA signatures have exactly 2*b bits.
    uint16_t c;                            ///< cofactor exponent
    uint16_t t;                            ///< bit position of MSBit of decoded scalar
    uint8_t *pSqrtMinusOne;                ///< Pointer to a square root of -1 modulo p which is needed for point decoding in case p = 5 mod 8 (i.e. only needed for Ed25519, not for Ed448)
    mcuxClHash_Algo_t algoSecHash;          ///< Hash algorithm descriptor of the hash function H() to be used for hashing the private key hash (see Public and private keys)
    mcuxClHash_Algo_t algoHash;             ///< Hash algorithm descriptor of the hash function H() to be used for hashing the private key, public data and plaintext messages
    mcuxClEcc_EdDSA_DecodePointFunction_t pDecodePointFct; ///< Function to be used to decode a point
    uint32_t pDecodePoint_FP_FuncId;                      ///< ID of function to be used to decode a point
    const uint32_t *pDomPrefix;            ///< The prefix string for dom2 or dom4
    uint32_t domPrefixLen;                 ///< Length of the prefix string for dom2 or dom4 in bytes
};

/**
 * EdDSA GenerateKeyPair variant structure.
 */
struct mcuxClEcc_EdDSA_GenerateKeyPairDescriptor
{
    uint32_t options;              ///< option of GenerateKeyPair, see @ref MCUXCLECC_EDDSA_GENERATEKEYPAIR_OPTION_
    const uint8_t *pPrivKeyInput;  ///< Pointer to private key input; set to NULL, if MCUXCLECC_EDDSA_GENERATEKEYPAIR_OPTION_GENERATE is chosen
};

/**
 * EdDSA SignatureProtocol variant structure.
 */
struct mcuxClEcc_EdDSA_SignatureProtocolDescriptor
{
    uint32_t generateOption;      ///< option of signature generation
    uint32_t verifyOption;        ///< option of signature verification
    uint32_t phflag;              ///< option of pre-hashing
    const uint8_t *pHashPrefix;   ///< pointer to hash prefix
    uint32_t hashPrefixLen;       ///< size of hash prefix
};


/**********************************************************/
/* Internal EdDSA defines                                 */
/**********************************************************/

/**
 * Size of message digest for EdDSA 
 */
#define MCUXCLECC_EDDSA_MESSAGE_DIGEST_SIZE       (64u)

/**
 * Options for EdDSA key pair generation descriptors
 */
#define MCUXCLECC_EDDSA_PRIVKEY_INPUT     (0xA5A5A5A5U)  ///< the private key d is passed as input
#define MCUXCLECC_EDDSA_PRIVKEY_GENERATE  (0X5A5A5A5AU)  ///< the private key is generated internally


/* Virtual and real buffer amounts definition for EdDSA functions */
#define ECC_EDDSA_NO_OF_VIRTUALS  (ECC_NO_OF_VIRTUALS)
#define ECC_EDDSA_NO_OF_BUFFERS   (TWED_PP_T7 + 1u - ECC_EDDSA_NO_OF_VIRTUALS)


MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_EdDSA_SetupEnvironment)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_EdDSA_SetupEnvironment(
    mcuxClSession_Handle_t pSession,
    mcuxClEcc_EdDSA_DomainParams_t *pDomainParams,
    uint8_t noOfBuffers
    );

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_EdDSA_CalcHashModN)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_EdDSA_CalcHashModN(
    mcuxClSession_Handle_t pSession,
    mcuxClHash_Context_t pCtx,
    mcuxClEcc_EdDSA_DomainParams_t *pDomainParams,
    const uint8_t *pHashPrefix,
    uint32_t hashPrefixLen,
    mcuxCl_InputBuffer_t pSignatureR,
    const uint8_t *pPubKey,
    mcuxCl_InputBuffer_t pIn,
    uint32_t inSize
    );

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_EdDSA_GenerateHashPrefix)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_EdDSA_GenerateHashPrefix(
    const mcuxClEcc_EdDSA_DomainParams_t *pDomainParams,
    uint32_t phflag,
    mcuxCl_InputBuffer_t pContext,
    uint32_t contextLen,
    uint8_t *pHashPrefix
    );

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_EdDSA_PreHashMessage)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_EdDSA_PreHashMessage(
    mcuxClSession_Handle_t pSession,
    mcuxClEcc_EdDSA_DomainParams_t *pDomainParams,
    uint32_t phflag,
    mcuxCl_InputBuffer_t pIn,
    uint32_t inSize,
    const uint8_t **pMessage,
    uint32_t *messageSize
    );


/**********************************************************/
/* Declarations for internal Ed25519 EdDSA functions      */
/**********************************************************/

/**
 * Declaration of the point decoding function on Ed25519
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_EdDSA_DecodePoint_Ed25519, mcuxClEcc_EdDSA_DecodePointFunction_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_EdDSA_DecodePoint_Ed25519(
    mcuxClEcc_EdDSA_DomainParams_t *pDomainParams,
    mcuxCl_InputBuffer_t pEncPoint
    );


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLECC_EDDSA_INTERNAL_H_ */
