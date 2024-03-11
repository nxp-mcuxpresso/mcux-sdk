/*--------------------------------------------------------------------------*/
/* Copyright 2020-2024 NXP                                                  */
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
 * @file  mcuxClEcc_Functions.h
 * @brief Top level APIs of mcuxClEcc component
 */


#ifndef MCUXCLECC_FUNCTIONS_H_
#define MCUXCLECC_FUNCTIONS_H_


#include <stdint.h>
#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClSession.h>
#include <mcuxClBuffer.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxCsslAnalysis.h>
#ifdef MCUXCL_FEATURE_ECC_ECDSA_DETERMINISTIC
#include <mcuxClMac.h>
#endif /* MCUXCL_FEATURE_ECC_ECDSA_DETERMINISTIC */

#include <mcuxClEcc_Types.h>

#include <mcuxClKey.h>


#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************/
/* Public APIs of mcuxClEcc                                */
/**********************************************************/
/**
 * @defgroup mcuxClEcc_Functions mcuxClEcc_Functions
 * @brief Defines all functions of @ref mcuxClEcc
 * @ingroup mcuxClEcc
 * @{
 */


/** implements ECDSA key generation.
 * @retval #MCUXCLECC_STATUS_OK                     if private key and public key are generated successfully;
 * @retval #MCUXCLECC_STATUS_INVALID_PARAMS         if parameters are invalid;
 * @retval #MCUXCLECC_STATUS_RNG_ERROR              if random number (DRBG / PRNG) error (unexpected behavior);
 * @retval #MCUXCLECC_STATUS_FAULT_ATTACK           if fault attack (unexpected behavior) is detected.
 * @attention This function uses DRBG and PRNG. Caller needs to check if DRBG and PRNG are ready.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_KeyGen)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_KeyGen(
    mcuxClSession_Handle_t pSession,         ///< [in] Handle for the current CL session.
    const mcuxClEcc_KeyGen_Param_t * pParam  ///< [in] pointer to ECDSA Key Generation parameter structure.
    );


/** implements ECDSA signature generation.
 * @retval #MCUXCLECC_STATUS_OK                   if signature is generated successfully;
 * @retval #MCUXCLECC_STATUS_INVALID_PARAMS       if parameters are invalid;
 * @retval #MCUXCLECC_STATUS_RNG_ERROR            if random number (DRBG / PRNG) error (unexpected behavior);
 * @retval #MCUXCLECC_STATUS_FAULT_ATTACK         if fault attack (unexpected behavior) is detected.
 * @attention This function uses DRBG and PRNG. Caller needs to check if DRBG and PRNG are ready.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_Sign)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_Sign(
    mcuxClSession_Handle_t pSession,       ///< [in] Handle for the current CL session.
    const mcuxClEcc_Sign_Param_t * pParam  ///< [in] pointer to ECDSA Sign parameter structure.
    );


/** implements ECDSA signature verification.
 * @retval #MCUXCLECC_STATUS_OK                     if ECDSA Signature is valid;
 * @retval #MCUXCLECC_STATUS_INVALID_SIGNATURE      if ECDSA Signature is invalid;
 * @retval #MCUXCLECC_STATUS_INVALID_PARAMS         if parameters are invalid;
 * @retval #MCUXCLECC_STATUS_FAULT_ATTACK           if fault attack (unexpected behavior) is detected.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_Verify)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_Verify(
    mcuxClSession_Handle_t pSession,         ///< [in] Handle for the current CL session.
    const mcuxClEcc_Verify_Param_t * pParam  ///< [in] pointer to ECDSA Verify parameter structure.
    );


/**
 * @brief implements ECC point multiplication.
 *
 * This API performs elliptic curve point multiplication on the given elliptic curve in short Weierstrass form.
 * This API does not check if the curve parameters and the given point are valid or not.
 * Invalid curve parameters or point might cause the return of #MCUXCLECC_STATUS_INVALID_PARAMS,
 * invalid result, and unexpected behavior (e.g., the return of #MCUXCLECC_STATUS_FAULT_ATTACK).
 *
 * @param[in] pSession  Handle for the current CL session.
 * @param[in] pParam    pointer to ECC point multiplication parameter structure.
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>pParam.curveParam.pG</dt>
 *       <dd> the base point is not used in this API. This pointer can be left unspecified. </dd>
 *   </dl></dd>
 * </dl>
 *
 *
 * @return A code-flow protected error code (see @ref MCUXCLECC_STATUS_)
 * @retval #MCUXCLECC_STATUS_OK                        if point multiplication is calculated successfully, and the result is not the neutral point;
 * @retval #MCUXCLECC_STATUS_INVALID_PARAMS            if parameters are invalid;
 * @retval #MCUXCLECC_STATUS_NEUTRAL_POINT             if result is the neutral point;
 * @retval #MCUXCLECC_STATUS_FAULT_ATTACK              if fault attack (unexpected behavior) is detected.
 *
 * @attention This function uses PRNG. Caller needs to check if PRNG is ready.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_PointMult)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_PointMult(
    mcuxClSession_Handle_t pSession,
    const mcuxClEcc_PointMult_Param_t * pParam
    );


/**
 * @brief implements ECC key pair generation step for a MontDH key agreement according to rfc7748.
 *
 * This function performs elliptic curve key generation of the private key and calculates corresponding public key for MontDH key agreement
 * as specified in rfc7748.
 * This API does not check if the curve parameters are correct.
 * This API might return MCUXCLECC_STATUS_RNG_ERROR when RNG behave in unexpected way
 * Unexpected behavior will return MCUXCLECC_STATUS_FAULT_ATTACK.
 *
 * @param[in] pSession          #mcuxClSession_Descriptor structure
 * @param[out] privKey          private key handling structure
 * @param[out] pubKey           public key handling structure
 *
 *
 * @return A code-flow protected error code (see @ref MCUXCLECC_STATUS_ and @ref MCUXCLECC_MONTDH_STATUS_)
 * @retval #MCUXCLECC_STATUS_OK                if key generation correctly calculate private and public keys, public key does not belong to the small subgroup.
 * @retval #MCUXCLECC_STATUS_RNG_ERROR         if RNG return an error.
 * @retval #MCUXCLECC_STATUS_FAULT_ATTACK      if fault attack (unexpected behavior) is detected.
 *
 * @attention This function uses PRNG. Caller needs to check if PRNG is ready.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_MontDH_GenerateKeyPair)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_MontDH_GenerateKeyPair(
    mcuxClSession_Handle_t pSession,
    mcuxClKey_Handle_t privKey,
    mcuxClKey_Handle_t pubKey
    );

/**
 * @brief Implements the MontDH key agreement according to rfc7748.
 *
 * This function performs a MontDH key agreement to compute a shared secret between two parties using according to Curve25519 or Curve448 as specified in rfc7748.
 * This API does not check if the curve parameters are correct.
 * This API might return MCUXCLECC_STATUS_RNG_ERROR when RNG behave in unexpected way
 * This API might return MCUXCLECC_STATUS_ERROR_SMALL_SUBGROUP if generated public key lies in the small subgroup
 * Unexpected behavior will return MCUXCLECC_STATUS_FAULT_ATTACK.
 *
 * @param[in] pSession     Handle for the current CL session.
 * @param[in] key          private key handling structure
 * @param[in] otherKey     public key handling structure
 * @param[out] pOut        buffer for shared secret of length MCUXCLECC_MONTDH_CURVE25519/448_SIZE_SHAREDSECRET
 * @param[out] pOutLength  shared secret length
 *
 *
 * @return A code-flow protected error code (see @ref MCUXCLECC_STATUS_ and @ref MCUXCLECC_MONTDH_STATUS_)
 * @retval #MCUXCLECC_STATUS_OK                         if key generation correctly calculate private and public keys, public key does not belong to the small subgroup.
 * @retval #MCUXCLECC_STATUS_RNG_ERROR                  if RNG return an error.
 * @retval #MCUXCLECC_STATUS_ERROR_SMALL_SUBGROUP       if calculated public key lies in small subgroup.
 * @retval #MCUXCLECC_STATUS_FAULT_ATTACK               if fault attack (unexpected behavior) is detected.
 *
 * @attention This function uses PRNG. Caller needs to check if PRNG is ready.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_MontDH_KeyAgreement)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_MontDH_KeyAgreement(
    mcuxClSession_Handle_t pSession,
    mcuxClKey_Handle_t key,
    mcuxClKey_Handle_t otherKey,
    uint8_t * pOut,
    uint32_t * const pOutLength
    );


MCUX_CSSL_ANALYSIS_START_SUPPRESS_TEXT_IN_COMMENTS("Links are allowed in comments.")
/**
 * @brief This function implements the EdDSA key pair generation for Ed25519 and Ed448 as specified in rfc8032
 *  (see Sections 5.1.5 and 5.2.5 of https://datatracker.ietf.org/doc/html/rfc8032).
 *  For an M byte private key d, which is either generated internally at random or passed as input,
 *  this function calculates the private key hash H(d)=(h0,...,h{2b-1}) and deduces and returns
 *  - the secret integer s
 *  - the second half (hb,...,h{2b-1}) of the private key hash
 *  - the public key Qenc=(s*G)enc where G is the base point.
 *
 * This API does not check if the curve parameters are correct.
 * This API might return MCUXCLECC_STATUS_RNG_ERROR when RNG behave in unexpected way
 * Unexpected behavior will return MCUXCLECC_STATUS_FAULT_ATTACK.
 *
 *
 * @param[in]     pSession              Handle for the current CL session
 * @param[in]     mode                  Mode descriptor specifying the EdDSA GenerateKeyPair variant
 * @param[in/out] privKey               Key handle for the private key.
 * @param[in/out] pubKey                Key handle for the public key.
 *
 * @return A code-flow protected error code (see @ref MCUXCLECC_STATUS_)
 * @retval #MCUXCLECC_STATUS_OK           private key data and public key have been generated successfully
 * @retval #MCUXCLECC_STATUS_RNG_ERROR    random number generation (DRBG / PRNG) error (unexpected behavior)
 * @retval #MCUXCLECC_STATUS_FAULT_ATTACK fault attack (unexpected behavior) is detected
 */
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TEXT_IN_COMMENTS()
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_EdDSA_GenerateKeyPair)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_EdDSA_GenerateKeyPair(
    mcuxClSession_Handle_t pSession,
    const mcuxClEcc_EdDSA_GenerateKeyPairDescriptor_t *mode,
    mcuxClKey_Handle_t privKey,
    mcuxClKey_Handle_t pubKey
    );

MCUX_CSSL_ANALYSIS_START_SUPPRESS_TEXT_IN_COMMENTS("Links are allowed in comments.")
/**
 * @brief This function implements the EdDSA signature generation for Ed25519 and Ed448 as specified in rfc8032 (see Sections 5.1.6 and 5.2.6 of https://datatracker.ietf.org/doc/html/rfc8032).
 *  For given hash prefix prefix (either dom2(x, y) or dom4(x, y) according to the chosen EdDSA variant; see Sections 5.1 and 5.2 of https://datatracker.ietf.org/doc/html/rfc8032),
 *  a message digest m', i.e. either the message itself for PureEdDSA or the message hash for HashEdDSA (see Section 4 of https://datatracker.ietf.org/doc/html/rfc8032),
 *  the signing keys s and (hb,...,h{2b-1}) derived from the private key d (see mcuxClEcc_EdDSA_GenerateKeyPair)
 *  and a public key Qenc, this function calculates an EdDSA signature (Renc,S), where Renc and S are given by
 *
 *      - Renc = (r*G)enc
 *      - S = r+H(prefix||Renc||Qenc||m')*s mod n
 *
 * where the secret scalar r is given by r=H(prefix||(hb,...,h{2b-1})||m') and G is the base point.
 *
 * This API does not check if the curve parameters are correct.
 * This API might return MCUXCLECC_STATUS_RNG_ERROR when RNG behave in unexpected way
 * Unexpected behavior will return MCUXCLECC_STATUS_FAULT_ATTACK.
 *
 *
 * @param[in]  pSession       Handle for the current CL session
 * @param[in]  key            Key handle for private key related data which a.o. references the secret signing keys s and (hb,...,h{2b-1}) as well as the public key Qenc.
 * @param[in]  mode           Mode descriptor specifying the EdDSA variant
 * @param[in]  pIn            Buffer for message digest m'
 * @param[in]  inSize         Size of message digest m'
 * @param[out] pSignature     Buffer for where the signature (Renc,S) will be stored
 * @param[out] pSignatureSize Will be set to the number of bytes of data that have been written to the pSignature buffer
 *
 * @return A code-flow protected error code (see @ref MCUXCLECC_STATUS_)
 * @retval #MCUXCLECC_STATUS_OK            signature generation was successful
 * @retval #MCUXCLECC_STATUS_RNG_ERROR     random number generation (DRBG / PRNG) error (unexpected behavior)
 * @retval #MCUXCLECC_STATUS_FAULT_ATTACK  fault attack (unexpected behavior) is detected
 */
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TEXT_IN_COMMENTS()
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_EdDSA_GenerateSignature)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_EdDSA_GenerateSignature(
    mcuxClSession_Handle_t pSession,
    mcuxClKey_Handle_t key,
    const mcuxClEcc_EdDSA_SignatureProtocolDescriptor_t *mode,
    mcuxCl_InputBuffer_t pIn,
    uint32_t inSize,
    mcuxCl_Buffer_t pSignature,
    uint32_t * const pSignatureSize
    );

MCUX_CSSL_ANALYSIS_START_SUPPRESS_TEXT_IN_COMMENTS("Links are allowed in comments.")
/**
 * @brief This function implements the EdDSA signature verification for Ed25519 and Ed448 as specified in rfc8032 (see Sections 5.1.7 and 5.2.7 of https://datatracker.ietf.org/doc/html/rfc8032).
 *  For given hash prefix prefix (either dom2(x, y) or dom4(x, y) according to the chosen EdDSA variant; see Sections 5.1 and 5.2 of https://datatracker.ietf.org/doc/html/rfc8032),
 *  a message digest m', i.e. either the message itself for PureEdDSA or the message hash for HashEdDSA (see Section 4 of https://datatracker.ietf.org/doc/html/rfc8032),
 *  and a public key Qenc, this function:
 *     - verifies the public key Qenc
 *     - verifies that the signature component S satisfies S in [0,n-1]
 *     - verifies if the following signature equation holds:
 *          * h*S*G=h*R+h*H(prefix||Renc||Qenc||m')*Q
 *
 * This API does not check if the curve parameters are correct.
 * This API might return MCUXCLECC_STATUS_RNG_ERROR when RNG behave in unexpected way
 * Unexpected behavior will return MCUXCLECC_STATUS_FAULT_ATTACK.
 *
 *
 * @param[in]  session         Handle for the current CL session
 * @param[in]  key             Key handle for public key Qenc
 * @param[in]  mode            Mode descriptor specifying the EdDSA variant
 * @param[in]  pIn             Buffer for message digest m'
 * @param[in]  inSize          Size of message digest m'
 * @param[in]  pSignature      Buffer for signature (Renc,S)
 * @param[in]  signatureSize   Number of bytes of data in the pSignature buffer
 *
 * @return A code-flow protected error code (see @ref MCUXCLECC_STATUS_)
 * @retval #MCUXCLECC_STATUS_OK                signature verification passed
 * @retval #MCUXCLECC_STATUS_INVALID_SIGNATURE EdDSA signature is invalid
 * @retval #MCUXCLECC_STATUS_INVALID_PARAMS    input parameters are invalid
 * @retval #MCUXCLECC_STATUS_FAULT_ATTACK      fault attack (unexpected behavior) is detected
 */
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TEXT_IN_COMMENTS()
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_EdDSA_VerifySignature)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_EdDSA_VerifySignature(
    mcuxClSession_Handle_t session,
    mcuxClKey_Handle_t key,
    const mcuxClEcc_EdDSA_SignatureProtocolDescriptor_t *mode,
    mcuxCl_InputBuffer_t pIn,
    uint32_t inSize,
    mcuxCl_InputBuffer_t pSignature,
    uint32_t signatureSize
    );

/**
 * @brief This function initializes an EdDSA mode descriptor for EdDSA key pair generation with private key input.
 *
 * @param[in]     pSession              Handle for the current CL session
 * @param[in/out] mode                  Pointer to mode descriptor to be initialized for EdDSA key pair generation with private key input
 * @param[in]     pPrivKey              Pointer to private key input
 *
 * @return A code-flow protected error code (see @ref MCUXCLECC_STATUS_)
 * @retval #MCUXCLECC_STATUS_OK           EdDSA mode descriptor has been initialized successfully
 * @retval #MCUXCLECC_STATUS_FAULT_ATTACK fault attack (unexpected behavior) is detected
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_EdDSA_InitPrivKeyInputMode)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_EdDSA_InitPrivKeyInputMode(
    mcuxClSession_Handle_t pSession,
    mcuxClEcc_EdDSA_GenerateKeyPairDescriptor_t *mode,
    const uint8_t *pPrivKey
    );

/**
 * @brief This function implements the protocol descriptor generation for Ed25519ctx, Ed25519ph, Ed448 and Ed448ph
 *
 * @param[in]  pSession             Handle for the current CL session
 * @param[in]  pDomainParams        Pointer to domain parameters of the used curve
 * @param[in]  pProtocolDescriptor  Protocol descriptor specifying the EdDSA variant
 * @param[in]  phflag               Option whether pre-hashing is enabled
 * @param[in]  pContext             User input context for the hash prefix
 * @param[in]  contextLen           Length of the context
 *
 * @return A code-flow protected error code (see @ref MCUXCLECC_STATUS_)
 * @retval #MCUXCLECC_STATUS_OK                EdDSA protocol descriptor generated successfully
 * @retval #MCUXCLECC_STATUS_FAULT_ATTACK      fault attack (unexpected behavior) is detected
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_EdDSA_GenerateProtocolDescriptor)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_EdDSA_GenerateProtocolDescriptor(
                                                    mcuxClSession_Handle_t pSession,
                                                    const mcuxClEcc_EdDSA_DomainParams_t *pDomainParams,
                                                    mcuxClEcc_EdDSA_SignatureProtocolDescriptor_t *pProtocolDescriptor,
                                                    uint32_t phflag,
                                                    mcuxCl_InputBuffer_t pContext,
                                                    uint32_t contextLen
                                                    );





#ifdef MCUXCL_FEATURE_ECC_ECDSA_DETERMINISTIC

/**
 * @brief Function to generate a deterministic ECDSA protocol descriptor.
 *
 * This function generates an ECDSA protocol descriptor to perform deterministic ECDSA signature generation
 * based on a given HMAC mode.
 *
 * @param[in]  pSession                               Handle for the current CL session.
 * @param[out] pDeterministicECDSAProtocolDescriptor  Pointer to output determinstic ECDSA protocol descriptor.
 * @param[in]  hmacMode                               pointer to HMAC mode.
 *
 *
 * @return A code-flow protected error code (see @ref MCUXCLECC_STATUS_)
 * @retval #MCUXCLECC_STATUS_OK              if the operation finished successfully.
 * @retval #MCUXCLECC_STATUS_INVALID_PARAMS  if the input parameters are invalid.
 * @retval #MCUXCLECC_STATUS_FAULT_ATTACK    if a fault attack (unexpected behavior) is detected.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_DeterministicECDSA_GenerateProtocolDescriptor)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_DeterministicECDSA_GenerateProtocolDescriptor(
    mcuxClSession_Handle_t session,
    mcuxClEcc_ECDSA_SignatureProtocolDescriptor_t * const pDeterministicECDSAProtocolDescriptor,
    mcuxClMac_Mode_t hmacMode
    );
#endif /* MCUXCL_FEATURE_ECC_ECDSA_DETERMINISTIC */


/**
 * @}
 */ /* mcuxClEcc_Functions */


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLECC_FUNCTIONS_H_ */
