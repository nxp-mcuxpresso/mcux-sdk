/*--------------------------------------------------------------------------*/
/* Copyright 2022-2024 NXP                                                  */
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
 * @file  mcuxClOsccaSm2_Internal_Types.h
 * @brief Internal type definitions for the mcuxClOsccaSm2 component
 */

#ifndef MCUXCLOSCCASM2_INTERNAL_TYPES_H_
#define MCUXCLOSCCASM2_INTERNAL_TYPES_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClOscca_Types.h>
#include <mcuxClOsccaSm2_Types.h>
#include <mcuxClOsccaSm2_Constants.h>
#include <internal/mcuxClOsccaSm2_Internal_PkcWaLayout.h>
#include <mcuxClOsccaSm3_Constants.h>
#include <internal/mcuxClOsccaSm3_Internal.h>
#include <internal/mcuxClHash_Internal_Memory.h>
#include <internal/mcuxClHash_Internal.h>
#include <mcuxClCrc.h>

/***********************************************************
 *  MACROS
 **********************************************************/
/**
 * @defgroup mcuxClOsccaSm2_Internal_Macros mcuxClOsccaSm2_Internal_Macros
 * @brief Defines all internal macros of @ref mcuxClOsccaSm2
 * @ingroup mcuxClOsccaSm2
 * @{
 */

#define MCUXCLOSCCASM2_SET_ENC_DEC_CTX_CRC(pCtx, pLen) \
   do{\
      MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClCrc_computeCRC16((uint8_t*)&(pCtx)->crc + sizeof(uint16_t),                     \
                                                    (uint32_t)offsetof(mcuxClOsccaSm2_Internal_EncDecCtx_t, tZeroOrNot) + sizeof(uint16_t) + (uint32_t)(pLen)    \
                                                    - (offsetof(mcuxClOsccaSm2_Internal_EncDecCtx_t, crc) + sizeof(uint16_t))));  \
      (pCtx)->crc = (uint16_t)retValTemp;  \
   }while(false)

#define MCUXCLOSCCASM2_ENCRYPT                  0xA5A5U
#define MCUXCLOSCCASM2_DECRYPT                  0x5A5AU
#define MCUXCLOSCCASM2_EXITCLEAR_3MAXPARAMS     0x3u
#define MCUXCLOSCCASM2_EXITCLEAR_2MAXPARAMS     0x2u
#define MCUXCLOSCCASM2_T_ZERO                   0xA5A5U
#define MCUXCLOSCCASM2_T_NOT_ZERO               0x5A5AU

/***********************************************************
 *  MACROS RELATED TO INTERANAL FUNCTION STATUS
 **********************************************************/
/**
 * @defgroup MCUXCLOSCCASM2_STATUS_ MCUXCLOSCCASM2_STATUS_
 * @brief Return code definitions
 * @ingroup mcuxClOsccaSm2_Macros
 * @{
 */

#define MCUXCLOSCCASM2_STATUS_INVERT_PRIVATE_KEY_OK       ((mcuxClOsccaSm2_Status_t) 0x4D6AU) /**< @brief Invert-private-key successful */
#define MCUXCLOSCCASM2_STATUS_COMPUTE_PREHASH_OK          ((mcuxClOsccaSm2_Status_t) 0x4D6CU) /**< @brief Pre-hash computation successful */
#define MCUXCLOSCCASM2_STATUS_ENCRYPT_OK                  ((mcuxClOsccaSm2_Status_t) 0x4DA9U) /**< @brief Encryption successful */
#define MCUXCLOSCCASM2_STATUS_DECRYPT_OK                  ((mcuxClOsccaSm2_Status_t) 0x4D96U) /**< @brief Decryption successful */
#define MCUXCLOSCCASM2_STATUS_KEYEXCHANGE_OK              ((mcuxClOsccaSm2_Status_t) 0x4D65U) /**< @brief Key exchange successful */
#define MCUXCLOSCCASM2_STATUS_ENCRYPT_INVALID_PARAMS      ((mcuxClOsccaSm2_Status_t) 0xB247U) /**< @brief The input parameters are invalid */
#define MCUXCLOSCCASM2_STATUS_KEYEXCHANGE_NOK             ((mcuxClOsccaSm2_Status_t) 0xB274U) /**< @brief Key exchange failed */
#define MCUXCLOSCCASM2_STATUS_KEYEXCHANGE_INVALID_PARAMS  ((mcuxClOsccaSm2_Status_t) 0xB287U) /**< @brief The input parameters are invalid */
#define MCUXCLOSCCASM2_STATUS_DECRYPT_NOK                 ((mcuxClOsccaSm2_Status_t) 0xB28BU) /**< @brief Decryption failed due to bad input */

/**********************************************************/
/* Internal return codes of mcuxClOsccaSm2                 */
/**********************************************************/

#define MCUXCLOSCCASM2_STATUS_ECCJACPOINT_EQUAL           ((mcuxClOsccaSm2_Status_t) 0x4D73U) /**< @brief EccJacPointCheck successful */
#define MCUXCLOSCCASM2_STATUS_ECCJACPOINT_NOT_EQUAL       ((mcuxClOsccaSm2_Status_t) 0xB23FU) /**< @brief EccJacPointCheck fail */
#define MCUXCLOSCCASM2_STATUS_ECCINIT_OK                  ((mcuxClOsccaSm2_Status_t) 0x4D78U) /**< @brief EccInit successful */
#define MCUXCLOSCCASM2_STATUS_ECCGENZ_OK                  ((mcuxClOsccaSm2_Status_t) 0x4D7AU) /**< @brief EccGenerateZ successful */
#define MCUXCLOSCCASM2_STATUS_ECCGENZ_FAIL                ((mcuxClOsccaSm2_Status_t) 0xB24EU) /**< @brief EccGenerateZ fail */
#define MCUXCLOSCCASM2_STATUS_ECCGENRAND_OK               ((mcuxClOsccaSm2_Status_t) 0x4D81U) /**< @brief EccGenRandomBytes successful */
#define MCUXCLOSCCASM2_STATUS_ECCGENRAND_FAIL             ((mcuxClOsccaSm2_Status_t) 0xB25AU) /**< @brief EccGenRandomBytes fail */
#define MCUXCLOSCCASM2_STATUS_SECOND_PART_INIT_OK         ((mcuxClOsccaSm2_Status_t) 0x4DAAU) /**< @brief SM2_SecondPartOfInitPhase successful*/
#define MCUXCLOSCCASM2_STATUS_ENCDEC_INTERNAL_FAIL        ((mcuxClOsccaSm2_Status_t) 0x4DB4U) /**< @brief SM2_EncDec_UpdatePhase or SM2_ValidateEncDecCtx or SM2_SecondPartOfInitPhase fail */
#define MCUXCLOSCCASM2_STATUS_ENCDEC_PHASE_OK             ((mcuxClOsccaSm2_Status_t) 0x4D55U) /**< @brief SM2_EncDec_UpdatePhase successful */
#define MCUXCLOSCCASM2_STATUS_VALIDATE_ENCDEC_CTX_OK      ((mcuxClOsccaSm2_Status_t) 0x4D4BU) /**< @brief SM2_ValidateEncDecCtx successful */
#define MCUXCLOSCCASM2_STATUS_KDF_OK                      ((mcuxClOsccaSm2_Status_t) 0x4DA9U) /**< @brief SM2_KDF successful*/
#define MCUXCLOSCCASM2_STATUS_KDF_FAIL                    ((mcuxClOsccaSm2_Status_t) 0xB2E4U) /**< @brief SM2_KDF fail*/
#define MCUXCLOSCCASM2_STATUS_POINTADD_OK                 ((mcuxClOsccaSm2_Status_t) 0x4DCAU) /**< @brief EccPointAddOrDouble successful*/
#define MCUXCLOSCCASM2_STATUS_POINTADD_INFINITE           ((mcuxClOsccaSm2_Status_t) 0xB235U) /**< @brief EccPointAddOrDouble Point Infinite*/
#define MCUXCLOSCCASM2_STATUS_POINTMULTSPLIT_OK           ((mcuxClOsccaSm2_Status_t) 0x4D19U) /**< @brief mcuxClOsccaSm2_EccPointMultSplitScalar successful*/
#define MCUXCLOSCCASM2_STATUS_POINTMULTSPLIT_FAIL         ((mcuxClOsccaSm2_Status_t) 0xB271U) /**< @brief mcuxClOsccaSm2_EccPointMultSplitScalar failed */
#define MCUXCLOSCCASM2_STATUS_SECUREPOINTMULT_OK          ((mcuxClOsccaSm2_Status_t) 0x4D37U) /**< @brief mcuxClOsccaSm2_EccSecurePointMult successful */
#define MCUXCLOSCCASM2_STATUS_SECUREPOINTMULT_FAIL        ((mcuxClOsccaSm2_Status_t) 0xB294U) /**< @brief mcuxClOsccaSm2_EccSecurePointMult failed */
#define MCUXCLOSCCASM2_STATUS_HANDLEKEYCONFIRMATION_OK    ((mcuxClOsccaSm2_Status_t) 0x4D3CU)  /**< @brief mcuxClOsccaSm2_ComputeKeyConfirmation successful */
#define MCUXCLOSCCASM2_STATUS_HANDLEKEYCONFIRMATION_FAIL  ((mcuxClOsccaSm2_Status_t) 0xB217U)  /**< @brief mcuxClOsccaSm2_ComputeKeyConfirmation failed */
#define MCUXCLOSCCASM2_STATUS_KEYEXCHANGE_INIT_OK         ((mcuxClOsccaSm2_Status_t) 0x4D3AU) /**< @brief mcuxClOsccaSm2_KeyExchange_Init successful */
#define MCUXCLOSCCASM2_STATUS_INTERNAL_ERROR              ((mcuxClOsccaSm2_Status_t) 0xB2E2U) /**< @brief SM2 internal error */
#define MCUXCLOSCCASM2_STATUS_INTERNAL_OK                 ((mcuxClOsccaSm2_Status_t) 0x4D5AU) /**< @brief mcuxClOsccaSm2_KeyExchange_Init successful */

#define MCUXCLOSCCASM2_SWAP32(value)            (((value)>>24)&0xffu) | (((value)<<8)&0xff0000u) | (((value)>>8)&0xff00u) | (((value)<<24)&0xff000000u)

#define MCUXCLOSCCASM2_CRYPTO_UNCOMPRESSED      4U

/**********************************************************/
/* Parameter structure of internal mcuxClOsccaSm2 APIs     */
/**********************************************************/
/**
 * @defgroup mcuxClOsccaSm2_Internal_Types mcuxClOsccaSm2_Internal_Types
 * @brief Defines all internal types of @ref mcuxClOsccaSm2
 * @ingroup mcuxClOsccaSm2
 * @{
 */
struct mcuxClOsccaSm2_DomainParam
{
    uint8_t const *pA;         /**< @brief Pointer to curve parameter a, element of GF(p) */
    uint8_t const *pB;         /**< @brief Pointer to curve parameter b, element of GF(p) */
    mcuxClOscca_MPInt_t p;      /**< @brief Prime of the underlying field p */
    uint8_t const *pG;         /**< @brief Pointer to base point G */
    mcuxClOscca_MPInt_t n;      /**< @brief Base point order n */
};

/************************************************************************************/
/** @brief Structure of parameters for function ::mcuxClOsccaSm2_InvertPrivateKey    */
/************************************************************************************/
typedef struct mcuxClOsccaSm2_InvertPrivateKey_Param_t
{
    mcuxClOsccaSm2_DomainParam_t domainParameters;       /**< @brief Domain parameters. */
    uint8_t const *pPrivateKey;                         /**< @brief Pointer to private key d (input). */
    uint8_t *pPrivateKeyInverse;                        /**< @brief Pointer to (1+d)^-1 (output). */
} mcuxClOsccaSm2_InvertPrivateKey_Param_t;

/************************************************************************************/
/** @brief Structure of parameters for function ::mcuxClOsccaSm2_ComputePrehash      */
/************************************************************************************/
typedef struct mcuxClOsccaSm2_ComputePrehash_Param_t
{
    mcuxClOsccaSm2_DomainParam_t domainParameters;       /**< @brief Domain parameters. */
    uint8_t const *pIdentifier;                         /**< @brief Pointer to the identifier of the signer. */
    uint16_t identifierLength;                          /**< @brief Length of the identifier of the signer in bytes */
    uint8_t const *pPublicKey;                          /**< @brief Pointer to public key of the signer. */
    uint8_t *pPrehash;                                  /**< @brief Computed prehash value (Za) by SM3 (256bits). */
} mcuxClOsccaSm2_ComputePrehash_Param_t;

/************************************************************************************/
/** @brief Forward declarations or full declarations                                */
/************************************************************************************/
typedef struct mcuxClOsccaSm2_EncDecCtx_t mcuxClOsccaSm2_EncDecCtx_t;

/************************************************************************************/
/** @brief Structure of parameters for function ::mcuxClOsccaSm2_Encrypt             */
/************************************************************************************/
typedef struct mcuxClOsccaSm2_Encrypt_Param_t
{
    mcuxClOsccaSm2_DomainParam_t domainParameters;       /**< @brief Domain parameters. */
    mcuxClOsccaSm2_EncDecCtx_t *pEncDecCtx;              /**< @brief Pointer to context. The context has to be
                                                              allocated by the caller with size
                                                              MCUXCLOSCCASM2_ENC_DEC_CTX_SIZE */
    uint8_t const *pPublicKey;                          /**< @brief Pointer to public key. */
    mcuxCl_InputBuffer_t pInput;                         /**< @brief Pointer to buffer holding plaintext. */
    mcuxCl_Buffer_t pC1;                                 /**< @brief Pointer to the buffer to store C1 if INIT is chosen. */
    mcuxCl_Buffer_t pOutput;                             /**< @brief Pointer to the buffer to store part of C2 corresponding
                                                              to passed pInput if UPDATE is chosen. */
    mcuxCl_Buffer_t pC3;                                 /**< @brief Pointer to the buffer of C3 if FINALIZE is chosen. */
    uint16_t inputLength;                               /**< @brief Length of passed part of plaintext */
    uint16_t options;                                   /**< @brief Two bytes to pass further options to this function:
                                                              - bits 0-3: rfu
                                                              - bit 4:
                                                                - 0   INIT phase will not be performed
                                                                - 1   INIT phase will be performed
                                                                      (C1 is returned via pC1)
                                                              - bit 5:
                                                                - 0   UPDATE phase will not be performed
                                                                - 1   UPDATE phase will be performed
                                                                      (The ciphertext part corresponding to the passed
                                                                      plaintext is returned via pOutput)
                                                              - bit 6:
                                                                - 0   FINALIZE phase will not be performed
                                                                - 1   FINALIZE phase will be performed
                                                                      (C3 is returned via pC3)
                                                              - other bits: rfu */
} mcuxClOsccaSm2_Encrypt_Param_t;

/************************************************************************************/
/** @brief Structure of parameters for function ::mcuxClOsccaSm2_Decrypt             */
/************************************************************************************/
typedef struct mcuxClOsccaSm2_Decrypt_Param_t
{
    mcuxClOsccaSm2_DomainParam_t domainParameters;  /**< @brief Domain parameters */
    mcuxClOsccaSm2_EncDecCtx_t *pEncDecCtx;         /**< @brief Pointer to context. The context has to be allocated
                                                              by the caller with MCUXCLOSCCASM2_ENC_DEC_CTX_SIZE size*/
    uint8_t const *pPrivateKey;                    /**< @brief Pointer to private key. */
    uint8_t const *pC1;                            /**< @brief Pointer to the buffer containing C1, and
                                                              has to be passed, if INIT is chosen. */
    mcuxCl_InputBuffer_t pInput;                    /**< @brief Pointer to the buffer containing C2' = m ^ t', and
                                                              has to be passed, if UPDATE is chosen. */
    uint8_t const *pC3;                            /**< @brief Pointer to the buffer containing C3, and
                                                              has to be passed, if FINALIZE is chosen. */
    mcuxCl_Buffer_t pOutput;                        /**< @brief Pointer to the output buffer if UPDATE is chosen. */
    uint16_t inputLength;                          /**< @brief Length of passed ciphertext chunk. */
    uint16_t options;                              /**< @brief Two bytes to pass further options to this function:
                                                              - bits 0-3: rfu
                                                              - bit 4:
                                                                - 0   INIT phase will not be performed
                                                                - 1   INIT phase will be performed
                                                              - bit 5:
                                                                - 0   UPDATE phase will not be performed
                                                                - 1   UPDATE phase will be performed
                                                              - bit 6:
                                                                - 0   FINALIZE phase will not be performed
                                                                - 1   FINALIZE phase will be performed
                                                              - other bits: rfu */
}mcuxClOsccaSm2_Decrypt_Param_t;

/************************************************************************************/
/** @brief Structure of parameters for function ::mcuxClOsccaSm2_KeyExchange         */
/************************************************************************************/
typedef struct mcuxClOsccaSm2_KeyExchange_Param_t
{
    mcuxClOsccaSm2_DomainParam_t domainParameters;    /**< @brief Domain parameters */
    uint8_t const *pPreHashInfoInitiator;            /**< @brief Pointer to the identifier of the initiator,
                                                                i.e., Z_A. */
    uint8_t const *pPreHashInfoResponder;            /**< @brief Pointer to the identifier of the responder,
                                                                i.e., Z_B. */
    uint8_t const *pPrivateKey;                      /**< @brief Pointer to the private key of local party, i.e., d_A,
                                                                if called by initiator Alice or d_B,
                                                                if called by responder Bob, according to the role
                                                                specified by the options parameter. */
    uint8_t const *pPrivateEphemeralScalar;          /**< @brief Pointer to the private ephemeral key of local party,
                                                                i.e., r_A, if called by initiator Alice or r_B,
                                                                if called by responder Bob, according to the role
                                                                specified by the options parameter. */
    uint8_t const *pPublicEphemeralPoint;            /**< @brief Pointer to the public ephemeral key of local party
                                                                in the form of x||y, i.e., R_A, if called by initiator
                                                                Alice or R_B, if called by responder Bob, according to
                                                                the role specified by the options parameter. */
    uint8_t const *pPublicKeyParty2;                 /**< @brief Pointer to the public key of the external party
                                                                in the form of x||y, i.e., P_B, if called by initiator
                                                                Alice or P_A, if called by responder Bob, according to
                                                                the role specified by the options parameter. */
    uint8_t const *pPublicEphemeralPointParty2;      /**< @brief Pointer to the ephemeral public key of the external
                                                                party in the form of x||y, i.e., R_B, if called by
                                                                initiator Alice or R_A, if called by responder Bob,
                                                                according to the role specified by the options
                                                                parameter. */
    mcuxCl_Buffer_t pCommonSecret;                   /**< @brief Pointer to the computed shared secret. */
    uint32_t commonSecretLength;                     /**< @brief Byte length of the computed shared secret */
    mcuxCl_Buffer_t pConfirmationFromResponderToInitiator;
                                                     /**< @brief Pointer to the first key confirmation, i.e., S_1,
                                                                if called by initiator Alice or S_B, if called by
                                                                responder Bob, according to the role specified by
                                                                the options parameter. */
    mcuxCl_Buffer_t pConfirmationFromInitiatorToResponder;
                                                     /**< @brief Pointer to the second key confirmation, i.e., S_A,
                                                                if called by initiator Alice or S_2, if called by
                                                                responder Bob, according to the role specified by
                                                                the options parameter. */
    uint16_t options;                                /**< @brief Two bytes to pass further options for this function:
                                                                - bits 0-3: rfu
                                                                - bit 4-5:
                                                                  - 01: Role of local party is initiator, i.e., Alice
                                                                  - 10: Role of local party is responder, i.e., Bob
                                                                - bit 6-7:
                                                                  - 01: Key confirmation shall be computed
                                                                  - 10: Key confirmation is skipped
                                                                - other bits: rfu */
} mcuxClOsccaSm2_KeyExchange_Param_t;

/************************************************************************************/
/** @brief  Masks to set options in for the SM2 parameter structures                */
/************************************************************************************/
/** @brief Offset of bits from the 16-bit options containing information
           about chosen state to be performed */
#define MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_OFFSET         (4u)

/** @brief Option to call mcuxClOscca_SM2_Encrypt/Decryption initialize */
#define MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_INIT         (0x01u << MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_OFFSET)
/** @brief Option to call mcuxClOscca_SM2_Encrypt/Decryption update     */
#define MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_UPDATE       (0x02u << MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_OFFSET)
/** @brief Option to call mcuxClOscca_SM2_Encrypt/Decryption finalize   */
#define MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_FINALIZE     (0x04u << MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_OFFSET)
/** @brief Option to call mcuxClOscca_SM2_Encrypt/Decryption one-shot   */
#define MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_ONE_SHOT     (MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_INIT | \
                                                       MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_UPDATE | \
                                                       MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_FINALIZE)
/** @brief Mask of bits from the 16-bit options containing information
           about chosen state to be performed */
#define MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_MASK           (MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_ONE_SHOT)

/** @brief Option to specify the role in key exchange as initiator in mcuxClOscca_SM2_KeyExchange */
#define MCUXCLOSCCASM2_OPT_KEYEXCHANGE_ROLE_INITIATOR  (0x0010u)
/** @brief Option to specify the role in key exchange as responder in mcuxClOscca_SM2_KeyExchange */
#define MCUXCLOSCCASM2_OPT_KEYEXCHANGE_ROLE_RESPONDER  (0x0020u)

/** @brief Option to specify key confirmation that is computed in mcuxClOscca_SM2_KeyExchange       */
#define MCUXCLOSCCASM2_OPT_KEYEXCHANGE_KEYCONFIRMATION        (0x0040u)
/** @brief Option to specify key confirmation that isn't be computed in mcuxClOscca_SM2_KeyExchange */
#define MCUXCLOSCCASM2_OPT_KEYEXCHANGE_NO_KEYCONFIRMATION     (0x0080u)

/** @brief Offset of bits from the 16-bit options containing information about the role:
           Alice (Initiator) or Bob (Responder) */
#define MCUXCLOSCCASM2_OPT_KEYEXCHANGE_ROLE_OFFSET     (4)
/** @brief Mask of bits from the 16-bit options containing information about the role:
           Alice (Initiator) or Bob (Responder) */
#define MCUXCLOSCCASM2_OPT_KEYEXCHANGE_ROLE_MASK       (0x0030u)

/** @brief Offset of bits from the 16-bit options containing information
           whether key confirmation shall be computed or not */
#define MCUXCLOSCCASM2_OPT_KEYEXCHANGE_KEYCONFIRMATION_OFFSET (6)
/** @brief Mask of bits from the 16-bit options containing information
           whether key confirmation shall be computed or not */
#define MCUXCLOSCCASM2_OPT_KEYEXCHANGE_KEYCONFIRMATION_MASK   (0x00C0u)

/** @brief Mask of bits from the 16-bit options containing information
           about chosen phase to be performed in SM2 mcuxClOsccaSm2_Signature_Internal_Init function*/
#define MCUXCLOSCCASM2_SIGN_PHASE_INIT_MASK               (0x0030u)
/** @brief Mask of bits from the 16-bit options containing information
           about chosen phase to be performed in SM2 mcuxClOsccaSm2_Signature_Internal_Finish function*/
#define MCUXCLOSCCASM2_SIGN_PHASE_FINAL_MASK              (0x07C0u)

/** @brief Phase to call mcuxClOsccaSm2_Signature_Internal_Init initialize */
#define MCUXCLOSCCASM2_SIGN_PHASE_INIT               (0x0010u)
/** @brief Phase to call mcuxClOsccaSm2_Signature_Internal_Init Key generation */
#define MCUXCLOSCCASM2_SIGN_PHASE_KEYGENPROCESS      (0x0020u)
/** @brief Phase to call mcuxClOsccaSm2_Signature_Internal_Finish to do init */
#define MCUXCLOSCCASM2_SIGN_PHASE_FINAL_INIT         (0x0040u)
/** @brief Phase to call mcuxClOsccaSm2_Signature_Internal_Finish to check r>0 */
#define MCUXCLOSCCASM2_SIGN_PHASE_KEYCHECK_R         (0x0080u)
/** @brief Phase to call mcuxClOsccaSm2_Signature_Internal_Finish to check r + k > 0  */
#define MCUXCLOSCCASM2_SIGN_PHASE_KEYCHECK_RPLUSK    (0x0100u)
/** @brief Phase to call mcuxClOsccaSm2_Signature_Internal_Finish to compute s and check that s > 0 */
#define MCUXCLOSCCASM2_SIGN_PHASE_COMPUTE_S          (0x0200u)
/** @brief Phase to call mcuxClOsccaSm2_Signature_Internal_Finish to export result */
#define MCUXCLOSCCASM2_SIGN_PHASE_EXPORT             (0x0400u)
/** @} */

/***********************************************************
 *  TYPES RELATED TO INTERNAL EncDec FUNCTIONALITY
 **********************************************************/
typedef struct mcuxClOsccaSm2_KDF_Param_t
{
    uint32_t hashCtxBackup[(mcuxClOscca_alignSize(sizeof(mcuxClHash_ContextDescriptor_t)) + MCUXCLHASH_CONTEXT_MAX_ALIGNMENT_OFFSET + MCUXCLOSCCASM3_BLOCK_SIZE_SM3 + MCUXCLOSCCASM3_STATE_SIZE_SM3)/sizeof(uint32_t)];
    uint8_t tempHashState[MCUXCLOSCCASM3_OUTPUT_SIZE_SM3];
    mcuxCl_Buffer_t pKeyBuffer;
    uint8_t const *pX2;
    uint8_t const *pY2;
    uint8_t const *pZA;
    uint8_t const *pZB;
    mcuxClOsccaSm2_DomainParam_t domainParameters;
    uint32_t keyLength;
} mcuxClOsccaSm2_KDF_Param_t;

/* structure defined for access all necessary fields from both Encrypt Decrypt Param_t for Update phase.
 * Urgent: if API will change, make sure that this structure is aligned accordingly
 */
typedef struct mcuxClOsccaSm2_EncDec_Common_Param_t
{
    mcuxClOsccaSm2_DomainParam_t domainParameters;
    mcuxClOsccaSm2_EncDecCtx_t *pEncDecCtx;
} mcuxClOsccaSm2_EncDec_Common_Param_t;

typedef struct mcuxClOsccaSm2_Internal_EncDecCtx
{
  uint32_t hashCtxC3[(mcuxClOscca_alignSize(sizeof(mcuxClHash_ContextDescriptor_t)) + MCUXCLHASH_CONTEXT_MAX_ALIGNMENT_OFFSET + MCUXCLOSCCASM3_BLOCK_SIZE_SM3 + MCUXCLOSCCASM3_STATE_SIZE_SM3)/sizeof(uint32_t)];
  uint32_t hashCtxT[(mcuxClOscca_alignSize(sizeof(mcuxClHash_ContextDescriptor_t)) + MCUXCLHASH_CONTEXT_MAX_ALIGNMENT_OFFSET + MCUXCLOSCCASM3_BLOCK_SIZE_SM3 + MCUXCLOSCCASM3_STATE_SIZE_SM3)/sizeof(uint32_t)];
  uint16_t crc; // The CRC is generated over (kdfCache,y2]
  uint32_t kdfCache[MCUXCLOSCCASM3_OUTPUT_SIZE_SM3/sizeof(uint32_t)];
  uint32_t kdfMask[MCUXCLOSCCASM3_OUTPUT_SIZE_SM3/sizeof(uint32_t)];
  uint32_t kdfCounter;
  uint32_t unusedBytesInKdfCache;
  uint16_t tZeroOrNot;
  // The user has to pass longer memory region for the structure as y2 will be stored in memory right after this structure
}mcuxClOsccaSm2_Internal_EncDecCtx_t;

typedef struct mcuxClOsccaSm2_KeyExchg_WaCpu_t
{
    mcuxClOsccaSm2_KDF_Param_t KDFParam;
    uint8_t keyExchgBuf[MCUXCLOSCCASM3_OUTPUT_SIZE_SM3];
} mcuxClOsccaSm2_KeyExchg_WaCpu_t;

/**
 * @}
 */

#endif /* MCUXCLOSCCASM2_INTERNAL_TYPES_H_ */
