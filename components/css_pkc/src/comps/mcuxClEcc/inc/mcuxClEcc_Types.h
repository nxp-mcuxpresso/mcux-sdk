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
 * @file  mcuxClEcc_Types.h
 * @brief Type definitions of mcuxClEcc component
 */


#ifndef MCUXCLECC_TYPES_H_
#define MCUXCLECC_TYPES_H_


#include <stdint.h>


/**********************************************************/
/* Return codes of mcuxClEcc                               */
/**********************************************************/
/**
 * @defgroup mcuxClEcc_Macros mcuxClEcc_Macros
 * @brief Defines all macros of @ref mcuxClEcc
 * @ingroup mcuxClEcc
 * @{
 */

/** Type for mcuxClEcc component return codes. */
typedef uint32_t mcuxClEcc_Status_t;

/** Type for mcuxClEcc component return codes. */
typedef uint64_t mcuxClEcc_Status_Protected_t;

/** Type for mcuxClEcc Mont domainParameters type */
typedef struct mcuxClEcc_Mont_DomainParams_t mcuxClEcc_Mont_DomainParams_t;

/** @addtogroup MCUXCLECC_STATUS_
 * mcuxClEcc return code definitions
 * @{ */
#define MCUXCLECC_STATUS_OK                        ((mcuxClEcc_Status_t) 0x55555555u)  ///< Operation was successful.
#define MCUXCLECC_STATUS_KEYGEN_OK                 ((mcuxClEcc_Status_t) 0x55553CC3u)  ///< ECDSA private key and public key are generated successfully.
#define MCUXCLECC_STATUS_KEYGEN_INVALID_PARAMS     ((mcuxClEcc_Status_t) 0x55551DE2u)  ///< Parameter(s) is invalid.
#define MCUXCLECC_STATUS_KEYGEN_RNG_ERROR          ((mcuxClEcc_Status_t) 0x555527D8u)  ///< Random number (DRBG / PRNG) error (unexpected behavior).
#define MCUXCLECC_STATUS_SIGN_OK                   ((mcuxClEcc_Status_t) 0x55555AA5u)  ///< ECDSA signature is generated successfully.
#define MCUXCLECC_STATUS_SIGN_INVALID_PARAMS       ((mcuxClEcc_Status_t) 0x55551EE1u)  ///< Parameter(s) is invalid.
#define MCUXCLECC_STATUS_SIGN_RNG_ERROR            ((mcuxClEcc_Status_t) 0x55552DD2u)  ///< Random number (DRBG / PRNG) error (unexpected behavior).
#if 0
#define MCUXCLECC_STATUS_CALCPP_OK                 ((mcuxClEcc_Status_t) 0x555539C6u)  ///< Pre-computed point is calculated successfully.
#define MCUXCLECC_STATUS_CALCPP_INVALID_PARAMS     ((mcuxClEcc_Status_t) 0x55551BE4u)  ///< Parameter(s) is invalid.
#endif
#define MCUXCLECC_STATUS_VERIFY_OK                 ((mcuxClEcc_Status_t) 0x55556996u)  ///< ECDSA Signature is valid.
#define MCUXCLECC_STATUS_VERIFY_NOT_OK             ((mcuxClEcc_Status_t) 0x555517E8u)  ///< ECDSA Signature is invalid.
#define MCUXCLECC_STATUS_VERIFY_INVALID_PARAMS     ((mcuxClEcc_Status_t) 0x55552BD4u)  ///< Parameter(s) is invalid.
#define MCUXCLECC_STATUS_POINTMULT_OK              ((mcuxClEcc_Status_t) 0x55553AC5u)  ///< Point multiplication is calculated successfully, and the result is not the neutral point;
#define MCUXCLECC_STATUS_POINTMULT_INVALID_PARAMS  ((mcuxClEcc_Status_t) 0x55554BB4u)  ///< Parameter(s) is invalid.
#define MCUXCLECC_STATUS_POINTMULT_NEUTRAL_POINT   ((mcuxClEcc_Status_t) 0x55558778u)  ///< The result of point multiplication is the neutral point.
#define MCUXCLECC_STATUS_POINTMULT_RNG_ERROR       ((mcuxClEcc_Status_t) 0x55552ED1u)  ///< Random number (DRBG / PRNG) error (unexpected behavior).
#define MCUXCLECC_STATUS_FAULT_ATTACK              ((mcuxClEcc_Status_t) 0x5555F00Fu)  ///< Fault attack (unexpected behavior) is detected.
/** @} */

/** @addtogroup MCUXCLECC_MONT_STATUS_
 * mcuxClEcc_Mont return code definitions
 * @{ */
#define MCUXCLECC_STATUS_MONT_DHKEYGENERATION_OK                  ((mcuxClEcc_Status_t) 0x555533CCu)  ///< MONTDH keys are generated successfully.

#define MCUXCLECC_STATUS_MONT_DHKEYAGREEMENT_OK                   ((mcuxClEcc_Status_t) 0x555535CAu)  ///< MONTDH shared secred computed successfully.
#define MCUXCLECC_STATUS_MONT_DHKEYAGREEMENT_ERROR_SMALL_SUBGROUP ((mcuxClEcc_Status_t) 0x55554DB2u)  ///< MONTDH public key lies in small subgroup.
#define MCUXCLECC_STATUS_MONT_RNG_ERROR                           ((mcuxClEcc_Status_t) 0x55551BE4u)  ///< Random number (DRBG / PRNG) error (unexpected behavior).

/** @} */

/** @addtogroup MCUXCLECC_MONT_CURVE25519_SIZE_
 * mcuxClEcc_Mont_size definitions for curve25519 input buffers
 * @{ */
#define MCUXCLECC_MONT_CURVE25519_SIZE_PRIVATEKEY        (32u)   ///< Byte length of a Curve25519 private key.
#define MCUXCLECC_MONT_CURVE25519_SIZE_PUBLICKEY         (32u)   ///< Byte length of a Curve25519 public key.
#define MCUXCLECC_MONT_CURVE25519_SIZE_SHAREDSECRET      (32u)   ///< Byte length of a Curve25519 shared secret.
#define MCUXCLECC_MONT_CURVE25519_SIZE_PRIMEP            (32u)   ///< Byte length of the underlying prime p used in Curve25519.
#define MCUXCLECC_MONT_CURVE25519_SIZE_BASEPOINTORDER    (32u)   ///< Byte length of the base point order n used in Curve25519.
/** @} */

/**
 * @}
 */ /* mcuxClEcc_Macros */


/**********************************************************/
/* Parameter structure of mcuxClEcc APIs                   */
/**********************************************************/
/**
 * @defgroup mcuxClEcc_Types mcuxClEcc_Types
 * @brief Defines all types of @ref mcuxClEcc
 * @ingroup mcuxClEcc
 * @{
 */

/** Parameter structure of elliptic curve of the form, y^2 = x^3 + a*x + b modulo prime p.
 *  Each curve parameter is stored as a Big-endian octet string with exact byte length specified.
 *  For a small parameter, padding zero(s) is placed in the beginning of the octet string.
 *  This structure contains pointers to the octet strings and the lengths.
 */
typedef struct
{
    const uint8_t *pA;  ///< [in] pointer to octet string of curve parameter a (< p), of which the length is byteLenP.
    const uint8_t *pB;  ///< [in] pointer to octet string of curve parameter b (< p), of which the length is byteLenP.
    const uint8_t *pP;  ///< [in] pointer to octet string of prime modulus p, of which the length is byteLenP.
                        ///<      The leading byte of this octet string shall be nonzero (i.e., != 0x00).
    const uint8_t *pG;  ///< [in] pointer to octet string of base point G. Each coordinate is an octet string of the length byteLenP.
                        ///<      The string of x coordinate is followed by the string of y coordinate.
    const uint8_t *pN;  ///< [in] pointer to octet string of base point order n, of which the length is byteLenN.
                        ///<      The leading byte of this octet string shall be nonzero (i.e., != 0x00).
    uint32_t misc;      ///< [in] packed lengths, via #mcuxClEcc_DomainParam_misc_Pack:
                        ///<      bits  0~ 7: byteLenP: length of the octet string of curve parameters a, b and p, and x and y coordinates of base point G;
                        ///<      bits  8~15: byteLenN: length of the octet string of curve parameter n;
                        ///<      bits 16~31: reserved.
} mcuxClEcc_DomainParam_t;

/** mcuxClEcc macros and defines to pack or access components of misc parameter of #mcuxClEcc_DomainParam_t */
#define mcuxClEcc_DomainParam_misc_Pack(byteLenN, byteLenP)  MCUXCLPKC_PACKARGS4(0u, 0u, (uint8_t) byteLenN, (uint8_t) byteLenP)  ///< Helper macro to pack misc parameter of #mcuxClEcc_DomainParam_t
#define mcuxClEcc_DomainParam_misc_byteLenP_offset  0                            ///< Offset of byteLenP in packed misc parameter of #mcuxClEcc_DomainParam_t
#define mcuxClEcc_DomainParam_misc_byteLenP_mask    ((uint32_t) 0x000000FFu)     ///< Mask to extract byteLenP from packed misc parameter of #mcuxClEcc_DomainParam_t
#define mcuxClEcc_DomainParam_misc_byteLenN_offset  8                            ///< Offset of byteLenN in packed misc parameter of #mcuxClEcc_DomainParam_t
#define mcuxClEcc_DomainParam_misc_byteLenN_mask    ((uint32_t) 0x0000FF00u)     ///< Mask to extract byteLenN from packed misc parameter of #mcuxClEcc_DomainParam_t

/** Parameter structure for function #mcuxClEcc_KeyGen. */
typedef struct
{
    mcuxClEcc_DomainParam_t curveParam;  ///< [in] structure of pointers to curve parameters and length of parameters.
    uint8_t * pPrivateKey;  ///< [out] pointer to memory area, where the private key will be exported if KeyGen is executed successfully.
                            ///<       It will be stored as a Big-endian octet string of the exact length curveParam.byteLenN.
    uint8_t * pPublicKey;   ///< [out] pointer to memory area, where the public key will be exported if KeyGen is executed successfully.
                            ///<       It will be stored in the same format as the base point G.
    uint32_t  optLen;       ///< [in] packed options (reserved):
                            ///< bits 0~31: reserved.  **CAUTION** always set optLen = 0.
} mcuxClEcc_KeyGen_Param_t;

/** Parameter structure for function #mcuxClEcc_Sign. */
typedef struct
{
    mcuxClEcc_DomainParam_t curveParam;  ///< [in] structure of pointers to curve parameters and length of parameters.
    const uint8_t * pHash;        ///< [in] pointer to string of message digest (hash), of which the length is byteLenHash (in optLen).
    const uint8_t * pPrivateKey;  ///< [in] pointer to octet string of private key, which is of the same format as base point order n.
    uint8_t *       pSignature;   ///< [out] pointer to memory area in which signature R and S will be exported if signature is generated successfully.
                                  ///<       They will be stored as Big-endian octet strings of the exact length curveParam.byteLenN.
                                  ///<       The string of R is followed by the string of S.
    uint32_t        optLen;       ///< [in] packed options (reserved) and lengths:
                                  ///<      bits 0~7: byteLenHash: length of the string of message digest;
                                  ///<      bits 8~31: reserved.
} mcuxClEcc_Sign_Param_t;

/** mcuxClEcc macros and defines to pack or access components of optLen parameter of #mcuxClEcc_Sign_Param_t */
#define mcuxClEcc_Sign_Param_optLen_Pack(byteLenHash)  ((uint32_t) (byteLenHash) & 0xFFu)    ///< Helper macro to pack optLen parameter of #mcuxClEcc_Sign_Param_t
#define mcuxClEcc_Sign_Param_optLen_byteLenHash_offset  0                                    ///< Offset of byteLenHash in packed optLen parameter of #mcuxClEcc_Sign_Param_t
#define mcuxClEcc_Sign_Param_optLen_byteLenHash_mask    ((uint32_t) 0x000000FFu)             ///< Mask to extract byteLenHash from packed optLen parameter of #mcuxClEcc_Sign_Param_t

#if 0
/** Parameter structure for function #mcuxClEcc_CalcPrecomputedPoint. */
typedef struct
{
    mcuxClEcc_DomainParam_t curveParam;  ///< [in] structure of pointers to curve parameters and length of parameters.
    uint8_t * pPrecG;  ///< [out] pointer to memory area in which calculated pre-computed point of base point G will be exported.
                       ///<       It is calculated as (2 ^ (nByteLength * 4)) * G.
                       ///<       It will be stored in the same format as the base point G, of which the length is 2*curveParam.byteLenP.
} mcuxClEcc_CalcPrecomputedPoint_Param_t;
#endif

/** Parameter structure for function #mcuxClEcc_Verify. */
typedef struct
{
    mcuxClEcc_DomainParam_t curveParam;  ///< [in] structure of pointers to curve parameters and length of parameters.
    const uint8_t * pPrecG;      ///< [in] pointer to octet string of pre-computed point of base point G, which is of the same format as base point G.
                                 ///<      It is calculated as (2 ^ (nByteLength * 4)) * G.
    const uint8_t * pHash;       ///< [in] pointer to string of message digest (hash), of which the length is byteLenHash (in optLen).
    const uint8_t * pSignature;  ///< [in] pointer to octet string of signature R and S. Each of R and S is a Big-endian octet string of the exact length curveParam.byteLenN.
                                 ///<      The string of R is followed by the string of S.
    const uint8_t * pPublicKey;  ///< [in] pointer to octet string of public key, which is of the same format as base point G.
    uint8_t *       pOutputR;    ///< [out] pointer to memory area in which signature R calculated by verify function will be exported if signature is valid.
                                 ///<       It will be stored as a Big-endian octet string of the exact length curveParam.byteLenN.
    uint32_t        optLen;      ///< [in] packed options (reserved) and lengths:
                                 ///<      bits 0~7: byteLenHash: length of the string of message digest;
                                 ///<      bits 8~31: reserved.
} mcuxClEcc_Verify_Param_t;

/** mcuxClEcc macros and defines to pack or access components of optLen parameter of #mcuxClEcc_Verify_Param_t */
#define mcuxClEcc_Verify_Param_optLen_Pack(byteLenHash)  ((uint32_t) (byteLenHash) & 0xFFu)  ///< Helper macro to pack optLen parameter of #mcuxClEcc_Verify_Param_t
#define mcuxClEcc_Verify_Param_optLen_byteLenHash_offset  0                                  ///< Offset of byteLenHash in packed optLen parameter of #mcuxClEcc_Verify_Param_t
#define mcuxClEcc_Verify_Param_optLen_byteLenHash_mask    ((uint32_t) 0x000000FFu)           ///< Mask to extract byteLenHash from packed optLen parameter of #mcuxClEcc_Verify_Param_t

/** Parameter structure for function #mcuxClEcc_PointMult. */
typedef struct
{
    mcuxClEcc_DomainParam_t curveParam;  ///< [in] structure of pointers to curve parameters and length of parameters.
    const uint8_t * pScalar;  ///< [in] pointer to octet string of scalar d, which is of the same format as base point order n.
    const uint8_t * pPoint;   ///< [in] pointer to octet string of EC point Q, which is of the same format as base point G.
    uint8_t * pResult;        ///< [out] pointer to memory area, where the result R = dQ will be exported if PointMult is executed successfully.
                              ///<       It will be stored in the same format as the base point G.
    uint32_t  optLen;         ///< [in] packed options (reserved):
                              ///< bits 0~31: reserved.  **CAUTION** always set optLen = 0.
} mcuxClEcc_PointMult_Param_t;

/**
 * @}
 */ /* mcuxClEcc_Types */


#endif /* MCUXCLECC_TYPES_H_ */