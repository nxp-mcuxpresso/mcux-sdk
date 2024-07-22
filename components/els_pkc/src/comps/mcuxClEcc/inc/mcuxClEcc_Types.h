/*--------------------------------------------------------------------------*/
/* Copyright 2020-2023 NXP                                                  */
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
 * @brief Type definitions and descriptors of mcuxClEcc component
 */


#ifndef MCUXCLECC_TYPES_H_
#define MCUXCLECC_TYPES_H_


#include <mcuxClCore_Platform.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClEcc_Constants.h>
#include <mcuxCsslAnalysis.h>
#include <mcuxClBuffer.h>


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup mcuxClEcc_Types mcuxClEcc_Types
 * @brief Defines all types of @ref mcuxClEcc
 * @ingroup mcuxClEcc
 * @{
 */

/**
 * @brief Type for mcuxClEcc component return codes.
 */
typedef uint32_t mcuxClEcc_Status_t;

/**
 * @brief Deprecated type for mcuxClEcc component return codes.
 */
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_Status_Protected_t;


/** Type for MontDH domain parameters */
typedef struct mcuxClEcc_MontDH_DomainParams mcuxClEcc_MontDH_DomainParams_t;


/** Type for EdDSA domain parameters */
typedef struct mcuxClEcc_EdDSA_DomainParams mcuxClEcc_EdDSA_DomainParams_t;

/**
 * @brief Forward declaration for EdDSA GenerateKeyPair variant structure
 */
struct mcuxClEcc_EdDSA_GenerateKeyPairDescriptor;

/**
 * @brief EdDSA GenerateKeyPair variant descriptor type
 */
typedef struct mcuxClEcc_EdDSA_GenerateKeyPairDescriptor mcuxClEcc_EdDSA_GenerateKeyPairDescriptor_t;

/**
 * @brief Forward declaration for EdDSA SignatureProtocol variant structure
 */
struct mcuxClEcc_EdDSA_SignatureProtocolDescriptor;

/**
 * @brief EdDSA SignatureProtocol variant descriptor type
 */
typedef struct mcuxClEcc_EdDSA_SignatureProtocolDescriptor mcuxClEcc_EdDSA_SignatureProtocolDescriptor_t;


/** Type for Weierstrass ECC domain parameters */
typedef struct mcuxClEcc_Weier_DomainParams mcuxClEcc_Weier_DomainParams_t;


/**
 * @brief Forward declaration for ECDSA SignatureProtocol variant structure
 */
struct mcuxClEcc_ECDSA_SignatureProtocolDescriptor;

/**
 * @brief ECDSA SignatureProtocol variant descriptor type
 */
typedef struct mcuxClEcc_ECDSA_SignatureProtocolDescriptor  mcuxClEcc_ECDSA_SignatureProtocolDescriptor_t;

/**********************************************************/
/* Parameter structure of mcuxClEcc APIs                   */
/**********************************************************/

/** Parameter structure of elliptic curve of the form, y^2 = x^3 + a*x + b modulo prime p.
 *  Each curve parameter is stored as a Big-endian octet string with exact byte length specified.
 *  For a small parameter, padding zero(s) is placed in the beginning of the octet string.
 *  This structure contains InputBuffers for the octet strings and the lengths.
 */
typedef struct
{
    mcuxCl_InputBuffer_t pA;  ///< [in] InputBuffer for octet string of curve parameter a (< p), of which the length is byteLenP.
    mcuxCl_InputBuffer_t pB;  ///< [in] InputBuffer for octet string of curve parameter b (< p), of which the length is byteLenP.
    mcuxCl_InputBuffer_t pP;  ///< [in] InputBuffer for octet string of prime modulus p, of which the length is byteLenP.
                             ///<      The leading byte of this octet string shall be nonzero (i.e., != 0x00).
    mcuxCl_InputBuffer_t pG;  ///< [in] InputBuffer for octet string of base point G. Each coordinate is an octet string of the length byteLenP.
                             ///<      The string of x coordinate is followed by the string of y coordinate.
    mcuxCl_InputBuffer_t pN;  ///< [in] InputBuffer for octet string of base point order n, of which the length is byteLenN.
                             ///<      The leading byte of this octet string shall be nonzero (i.e., != 0x00).
    uint32_t misc;  ///< [in] packed lengths, via #mcuxClEcc_DomainParam_misc_Pack:
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
    mcuxClEcc_DomainParam_t curveParam;  ///< [in] structure of InputBuffers for curve parameters and length of parameters.
    uint8_t * pPrivateKey;  ///< [out] pointer to memory area, where the private key will be exported if KeyGen is executed successfully.
                            ///<       It will be stored as a Big-endian octet string of the exact length curveParam.byteLenN.
    uint8_t * pPublicKey;   ///< [out] pointer to memory area, where the public key will be exported if KeyGen is executed successfully.
                            ///<       It will be stored in the same format as the base point G.
    uint32_t optLen;  ///< [in] packed options (reserved):
                      ///< bits 0~31: reserved.  **CAUTION** always set optLen = 0.
} mcuxClEcc_KeyGen_Param_t;


/** Parameter structure for function #mcuxClEcc_Sign. */
typedef struct
{
    mcuxClEcc_DomainParam_t curveParam;  ///< [in] structure of InputBuffers for curve parameters and length of parameters.
    mcuxCl_InputBuffer_t pHash;        ///< [in] InputBuffer for string of message digest (hash), of which the length is byteLenHash (in optLen).
    const uint8_t *     pPrivateKey;  ///< [in] pointer to octet string of private key, which is of the same format as base point order n.
    mcuxCl_Buffer_t      pSignature;   ///< [out] Buffer for memory area in which signature R and S will be exported if signature is generated successfully.
                                      ///<       They will be stored as Big-endian octet strings of the exact length curveParam.byteLenN.
                                      ///<       The string of R is followed by the string of S.
    uint32_t        optLen;       ///< [in] packed options (reserved) and lengths:
                                  ///<      bits 0~7: byteLenHash: length of the string of message digest;
                                  ///<      bits 8~31: reserved.
    const mcuxClEcc_ECDSA_SignatureProtocolDescriptor_t *pMode;  ///< [in] pointer to ECDSA protocol descriptor.
} mcuxClEcc_Sign_Param_t;

/** mcuxClEcc macros and defines to pack or access components of optLen parameter of #mcuxClEcc_Sign_Param_t */
#define mcuxClEcc_Sign_Param_optLen_Pack(byteLenHash)  ((uint32_t) (byteLenHash) & 0xFFu)    ///< Helper macro to pack optLen parameter of #mcuxClEcc_Sign_Param_t
#define mcuxClEcc_Sign_Param_optLen_byteLenHash_offset  0                                    ///< Offset of byteLenHash in packed optLen parameter of #mcuxClEcc_Sign_Param_t
#define mcuxClEcc_Sign_Param_optLen_byteLenHash_mask    ((uint32_t) 0x000000FFu)             ///< Mask to extract byteLenHash from packed optLen parameter of #mcuxClEcc_Sign_Param_t

/** Parameter structure for function #mcuxClEcc_Verify. */
typedef struct
{
    mcuxClEcc_DomainParam_t curveParam;  ///< [in] structure of InputBuffers for curve parameters and length of parameters.
    mcuxCl_InputBuffer_t pPrecG;      ///< [in] InputBuffer for octet string of pre-computed point of base point G, which is of the same format as base point G.
                                     ///<      It is calculated as (2 ^ (nByteLength * 4)) * G.
    mcuxCl_InputBuffer_t pHash;       ///< [in] InputBuffer for string of message digest (hash), of which the length is byteLenHash (in optLen).
    mcuxCl_InputBuffer_t pSignature;  ///< [in] InputBuffer for to octet string of signature R and S. Each of R and S is a Big-endian octet string of the exact length curveParam.byteLenN.
                                     ///<      The string of R is followed by the string of S.
    const uint8_t * pPublicKey;  ///< [in] pointer to octet string of public key, which is of the same format as base point G.
    mcuxCl_Buffer_t      pOutputR;    ///< [out] Buffer for memory area in which signature R calculated by verify function will be exported if signature is valid.
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
    mcuxClEcc_DomainParam_t curveParam;  ///< [in] structure of InputBuffers for curve parameters and length of parameters.
    mcuxCl_InputBuffer_t pScalar;  ///< [in] InputBuffer for octet string of scalar d, which is of the same format as base point order n.
    mcuxCl_InputBuffer_t pPoint;   ///< [in] InputBuffer for octet string of EC point Q, which is of the same format as base point G.
    mcuxCl_Buffer_t      pResult;  ///< [out] Buffer for memory area, where the result R = dQ will be exported if PointMult is executed successfully.
                              ///<       It will be stored in the same format as the base point G.
    uint32_t  optLen;         ///< [in] packed options (reserved):
                              ///< bits 0~31: reserved.  **CAUTION** always set optLen = 0.
} mcuxClEcc_PointMult_Param_t;


/**
 * @}
 */ /* mcuxClEcc_Types */


/**********************************************************/
/* Descriptors of mcuxClEcc APIs                           */
/**********************************************************/
/**
 * @defgroup mcuxClEcc_Descriptors mcuxClEcc_Descriptors
 * @brief Defines descriptors of @ref mcuxClEcc
 * @ingroup mcuxClEcc
 * @{
 */


/** @addtogroup mcuxClEcc_EdDsaDescriptors
 * mcuxClEcc definitions of EdDSA variant descriptors
 * @{ */


/**********************************************************/
/* Key pair generation descriptors                        */
/**********************************************************/

/* EdDSA key pair generation descriptor to be used when the private key shall be generated by the
 * EdDSA key pair generation function */
extern const mcuxClEcc_EdDSA_GenerateKeyPairDescriptor_t mcuxClEcc_EdDsa_GeneratePrivKeyDescriptor;


/**********************************************************/
/* Signature ProtocolDescriptors and ModeDescriptors      */
/**********************************************************/


/**
 * \brief Ed25519 signature protocol descriptor
 *
 * NOTE: To be able to perform an Ed25519 signature generation using this mode, the private key handle must be properly linked to a key handle
 *       for the associated public key using the function mcuxClKey_linkKeyPair. This is necessary to make the public key accessible during an
 *       Ed25519 signature generation. If this is not satisfied the Ed25519 signature generation will fail.
 *       If the key pair has been generated using the mcuxClKey_generate_keypair function, this linking step is already
 *       performed by mcuxClKey_generate_keypair.
 */
extern const mcuxClEcc_EdDSA_SignatureProtocolDescriptor_t mcuxClEcc_EdDsa_Ed25519ProtocolDescriptor;


/** @} */  /* mcuxClEcc_EdDsaDescriptors */



/** @addtogroup mcuxClEcc_ECDSADescriptors
 * mcuxClEcc definitions of ECDSA variant descriptors
 * @{ */


/* Standard ECDSA (according to FIPS 186-5) signature protocol descriptor */
extern const mcuxClEcc_ECDSA_SignatureProtocolDescriptor_t mcuxClEcc_ECDSA_ProtocolDescriptor;


/** @} */  /* mcuxClEcc_ECDSADescriptors */

/**
 * @}
 */ /* mcuxClEcc_Descriptors */

/**
 * @defgroup mcuxClEcc_DomainParamsDescriptor mcuxClEcc_DomainParamsDescriptor
 * @brief Definitions of domain parameters variant descriptors
 * @ingroup mcuxClEcc_Descriptors
 * @{
 */

/* secp160k1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_secp160k1;

/* secp192k1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_secp192k1;

/* sec224k1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_secp224k1;

/* secp256k1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_secp256k1;

/* secp192r1 (nistp192r1, ansix9p192r1) domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_secp192r1;
#define mcuxClEcc_Weier_DomainParams_NIST_P192 mcuxClEcc_Weier_DomainParams_secp192r1
#define mcuxClEcc_Weier_DomainParams_ansix9p192r1 mcuxClEcc_Weier_DomainParams_secp192r1

/* secp224r1 (nistp224r1, ansix9p224r1) domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_secp224r1;
#define mcuxClEcc_Weier_DomainParams_NIST_P224 mcuxClEcc_Weier_DomainParams_secp224r1
#define mcuxClEcc_Weier_DomainParams_ansix9p224r1 mcuxClEcc_Weier_DomainParams_secp224r1

/* secp256r1 (nistp256r1, ansix9p256r1) domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_secp256r1;
#define mcuxClEcc_Weier_DomainParams_NIST_P256 mcuxClEcc_Weier_DomainParams_secp256r1
#define mcuxClEcc_Weier_DomainParams_ansix9p256r1 mcuxClEcc_Weier_DomainParams_secp256r1

/* secp384r1 (nistp384r1, ansix9p384r1) domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_secp384r1;
#define mcuxClEcc_Weier_DomainParams_NIST_P384 mcuxClEcc_Weier_DomainParams_secp384r1
#define mcuxClEcc_Weier_DomainParams_ansix9p384r1 mcuxClEcc_Weier_DomainParams_secp384r1

/* secp521r1 (nistp521r1, ansix9p521r1) domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_secp521r1;
#define mcuxClEcc_Weier_DomainParams_NIST_P521 mcuxClEcc_Weier_DomainParams_secp521r1
#define mcuxClEcc_Weier_DomainParams_ansix9p521r1 mcuxClEcc_Weier_DomainParams_secp521r1

/* brainpoolP160r1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_brainpoolP160r1;

/* brainpoolP192r1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_brainpoolP192r1;

/* brainpoolP224r1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_brainpoolP224r1;

/* brainpoolP256r1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_brainpoolP256r1;

/* brainpoolP320r1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_brainpoolP320r1;

/* brainpoolP384r1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_brainpoolP384r1;

/* brainpoolP512r1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_brainpoolP512r1;

/* brainpoolP160t1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_brainpoolP160t1;

/* brainpoolP192t1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_brainpoolP192t1;

/* brainpoolP224t1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_brainpoolP224t1;

/* brainpoolP256t1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_brainpoolP256t1;

/* brainpoolP320t1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_brainpoolP320t1;

/* brainpoolP384t1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_brainpoolP384t1;

/* brainpoolP512t1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_brainpoolP512t1;


/* Ed25519 domain parameters */
extern const mcuxClEcc_EdDSA_DomainParams_t mcuxClEcc_EdDSA_DomainParams_Ed25519;

/**
 * @}
 */ /* mcuxClEcc_DomainParamsDescriptor */



/**
 * @defgroup mcuxClEcc_ArithmeticOperation mcuxClEcc_ArithmeticOperation
 * @brief Definionts of variant descriptors for arithmetic operations of @ref mcuxClEcc
 * @ingroup mcuxClEcc_Descriptors
 * @{
 */








/** @} */ /* mcuxClEcc_ArithmeticOperation */


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLECC_TYPES_H_ */
