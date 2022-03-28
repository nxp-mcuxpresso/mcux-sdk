/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021 NXP                                                  */
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
#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClEcc_Types.h>

#include <mcuxClKey.h>


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
 * @retval #MCUXCLECC_STATUS_KEYGEN_OK              if private key and public key are generated successfully;
 * @retval #MCUXCLECC_STATUS_KEYGEN_INVALID_PARAMS  if parameter(s) is invalid;
 * @retval #MCUXCLECC_STATUS_KEYGEN_RNG_ERROR       if random number (DRBG / PRNG) error (unexpected behavior);
 * @retval #MCUXCLECC_STATUS_FAULT_ATTACK           if fault attack (unexpected behavior) is detected.
 * @attention This function uses DRBG and PRNG. Caller needs to check if DRBG and PRNG are ready.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_KeyGen)
mcuxClEcc_Status_Protected_t mcuxClEcc_KeyGen(
    mcuxClSession_Handle_t pSession,  ///< [in] pointer to #mcuxClSession_Descriptor.
    const mcuxClEcc_KeyGen_Param_t * pParam  ///< [in] pointer to ECDSA Key Generation parameter structure.
    );

/** implements ECDSA signature generation.
 * @retval #MCUXCLECC_STATUS_SIGN_OK              if signature is generated successfully;
 * @retval #MCUXCLECC_STATUS_SIGN_INVALID_PARAMS  if parameter(s) is invalid;
 * @retval #MCUXCLECC_STATUS_SIGN_RNG_ERROR       if random number (DRBG / PRNG) error (unexpected behavior);
 * @retval #MCUXCLECC_STATUS_FAULT_ATTACK         if fault attack (unexpected behavior) is detected.
 * @attention This function uses DRBG and PRNG. Caller needs to check if DRBG and PRNG are ready.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_Sign)
mcuxClEcc_Status_Protected_t mcuxClEcc_Sign(
    mcuxClSession_Handle_t pSession,  ///< [in] pointer to #mcuxClSession_Descriptor.
    const mcuxClEcc_Sign_Param_t * pParam  ///< [in] pointer to ECDSA Sign parameter structure.
    );

#if 0
/** implements EC pre-computed point calculation.
 * @retval #MCUXCLECC_STATUS_CALCPP_OK              if pre-computed point is calculated successfully;
 * @retval #MCUXCLECC_STATUS_CALCPP_INVALID_PARAMS  if parameter(s) is invalid;
 * @retval #MCUXCLECC_STATUS_FAULT_ATTACK           if fault attack (unexpected behavior) is detected.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_CalcPrecomputedPoint)
mcuxClEcc_Status_Protected_t mcuxClEcc_CalcPrecomputedPoint(
    uint8_t * pPkcWorkarea,  ///< [in] pointer to PKC workarea to be used in this function.
    const mcuxClEcc_CalcPrecomputedPoint_Param_t * pParam  ///< [in] pointer to EC Calculate Pre-computed Point parameter structure.
    );
#endif

/** implements ECDSA signature verification.
 * @retval #MCUXCLECC_STATUS_VERIFY_OK              if ECDSA Signature is valid;
 * @retval #MCUXCLECC_STATUS_VERIFY_NOT_OK          if ECDSA Signature is invalid;
 * @retval #MCUXCLECC_STATUS_VERIFY_INVALID_PARAMS  if parameter(s) is invalid;
 * @retval #MCUXCLECC_STATUS_FAULT_ATTACK           if fault attack (unexpected behavior) is detected.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_Verify)
mcuxClEcc_Status_Protected_t mcuxClEcc_Verify(
    mcuxClSession_Handle_t pSession,  ///< [in] pointer to #mcuxClSession_Descriptor.
    const mcuxClEcc_Verify_Param_t * pParam  ///< [in] pointer to ECDSA Verify parameter structure.
    );

/**
 * @brief implements ECC point multiplication.
 *
 * This API performs elliptic curve point multiplication on the given elliptic curve in short Weierstrass form.
 * This API does not check if the curve parameters and the given point are valid or not.
 * Invalid curve parameters or point might cause the return of #MCUXCLECC_STATUS_POINTMULT_INVALID_PARAMS,
 * invalid result, and unexpected behavior (e.g., the return of #MCUXCLECC_STATUS_FAULT_ATTACK).
 *
 * @param[in] pSession  pointer to #mcuxClSession_Descriptor.
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
 * @retval #MCUXCLECC_STATUS_POINTMULT_OK              if point multiplication is calculated successfully, and the result is not the neutral point;
 * @retval #MCUXCLECC_STATUS_POINTMULT_INVALID_PARAMS  if parameter(s) is invalid;
 * @retval #MCUXCLECC_STATUS_POINTMULT_NEUTRAL_POINT   if result is the neutral point;
 * @retval #MCUXCLECC_STATUS_FAULT_ATTACK              if fault attack (unexpected behavior) is detected.
 *
 * @attention This function uses PRNG. Caller needs to check if PRNG is ready.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_PointMult)
mcuxClEcc_Status_Protected_t mcuxClEcc_PointMult(
    mcuxClSession_Handle_t pSession,
    const mcuxClEcc_PointMult_Param_t * pParam
    );

/**
 * @brief implements ECC key pair generation step for a MontDh key agreement according to rfc7748.
 *
 * This API performs elliptic curve key generation of the private key and calculates corresponding public key for MontDh key agreement
 * This API does not check if the curve parameters are correct.
 * This API might return MCUXCLECC_STATUS_MONT_RNG_ERROR when RNG behave in unexpected way
 * Unexpected behavior will return MCUXCLECC_STATUS_FAULT_ATTACK.
 *
 * @param[in] session         #mcuxClSession_Descriptor structure
 * @param[in] type            type structure specifying requested key type to be generated. Also contains domain parameters
 * @param[in] protection      #mcuxClKey_Protection structure
 * @param[out] privKey        private key handling structure
 * @param[out] pPrivData      buffer for private key of the MCUXCLECC_MONT_CURVE25519_SIZE_PRIVATEKEY length
 * @param[out] pPrivDataSize  private key length
 * @param[out] pubKey         public key handling structure
 * @param[out] pPubData       buffer for public key x-coordinate of MCUXCLECC_MONT_CURVE25519_SIZE_PUBLICKEY length
 * @param[out] pPubDataSize   public key x-coordinate length
 *
 *
 * @return A code-flow protected error code (see @ref MCUXCLECC_STATUS_ and @ref MCUXCLECC_MONT_STATUS_)
 * @retval #MCUXCLECC_STATUS_MONT_DHKEYGENERATION_OK                      if key generation correctly calculate private and public keys, public key does not belong to the small subgroup.
 * @retval #MCUXCLECC_STATUS_MONT_RNG_ERROR                               if RNG return an error.
 * @retval #MCUXCLECC_STATUS_FAULT_ATTACK                                 if fault attack (unexpected behavior) is detected.
 *
 * @attention This function uses PRNG. Caller needs to check if PRNG is ready.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_Mont_DhKeyGeneration)
mcuxClEcc_Status_Protected_t mcuxClEcc_Mont_DhKeyGeneration(
            mcuxClSession_Handle_t session,
            mcuxClKey_Type_t type,
            mcuxClKey_Protection_t protection,
            mcuxClKey_Handle_t privKey,
            uint8_t * pPrivData,
            uint32_t * const pPrivDataSize,
            mcuxClKey_Handle_t pubKey,
            uint8_t * pPubData,
            uint32_t * const pPubDataSize
);


/**
 * @brief implements ECC key agreement according to rfc7748.
 *
 * This API performs elliptic curve key agreement to compute shared secret between two parties using the function X25519
 * This API does not check if the curve parameters are correct.
 * This API might return MCUXCLECC_STATUS_MONT_RNG_ERROR when RNG behave in unexpected way
 * This API might return MCUXCLECC_STATUS_MONT_DHKEYAGREEMENT_ERROR_SMALL_SUBGROUP if generated public key lies in the small subgroup
 * Unexpected behavior will return MCUXCLECC_STATUS_FAULT_ATTACK.
 *
 * @param[in] session    pointer to #mcuxClSession_Descriptor.
 * @param[in] key        private key handling structure
 * @param[in] otherKey   public key handling structure
 * @param[out] pOut      buffer for shared secret of length MCUXCLECC_MONT_CURVE25519_SIZE_SHAREDSECRET
 * @param[out] pOutSize  shared secret length
 *
 *
 * @return A code-flow protected error code (see @ref MCUXCLECC_STATUS_ and @ref MCUXCLECC_MONT_STATUS_)
 * @retval #MCUXCLECC_STATUS_MONT_DHKEYAGREEMENT_OK                      if key generation correctly calculate private and public keys, public key does not belong to the small subgroup.
 * @retval #MCUXCLECC_STATUS_MONT_RNG_ERROR                              if RNG return an error.
 * @retval #MCUXCLECC_STATUS_MONT_DHKEYAGREEMENT_ERROR_SMALL_SUBGROUP    if calculated public key lies in small subgroup.
 * @retval #MCUXCLECC_STATUS_FAULT_ATTACK                                if fault attack (unexpected behavior) is detected.
 *
 * @attention This function uses PRNG. Caller needs to check if PRNG is ready.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_Mont_DhKeyAgreement)
mcuxClEcc_Status_Protected_t mcuxClEcc_Mont_DhKeyAgreement(
                mcuxClSession_Handle_t session,
                mcuxClKey_Handle_t key,
                mcuxClKey_Handle_t otherKey,
                uint8_t * pOut,
                uint32_t * const pOutSize
);
/**
 * @}
 */ /* mcuxClEcc_Functions */


#endif /* MCUXCLECC_FUNCTIONS_H_ */