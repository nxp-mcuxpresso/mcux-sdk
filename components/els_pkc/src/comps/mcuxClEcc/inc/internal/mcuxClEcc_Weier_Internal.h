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
 * @file  mcuxClEcc_Weier_Internal.h
 * @brief internal header for short Weierstrass curves
 */


#ifndef MCUXCLECC_WEIER_INTERNAL_H_
#define MCUXCLECC_WEIER_INTERNAL_H_


#include <stdbool.h>
#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClMemory.h>
#include <mcuxClKey_Types.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClSession.h>
#include <mcuxClEcc_Types.h>

#include <internal/mcuxClEcc_Internal.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Domain parameter structure for ECC functions based on Weierstrass functions.
 */
struct mcuxClEcc_Weier_DomainParams
{
    mcuxClEcc_CommonDomainParams_t common;  ///< structure containing pointers and lengths for common ECC parameters (see Common ECC Domain parameters)
};



/**********************************************************/
/* Internal return codes of mcuxClEcc                      */
/**********************************************************/

#define MCUXCLECC_INTSTATUS_POINTCHECK_NOT_OK        ((mcuxClEcc_Status_t) 0x55AAE817u)

/* Rule of ECC return codes:
 * All return codes are of the format: 0x55XXYYTT
 * API         : XX = 55
 * Internal    : XX = AA
 * HammingWeight(YY) = HammingWeight(TT) = 4, according to coding guidelines
 * YY needs to be a balanced byte, and TT = ~YY
 *
 * General  OK  : YYTT = 5555
 * Fault Attack : YYTT = F00F
 */


/**********************************************************/
/** PKC workarea memory layout for Weierstrass functions. */
/**********************************************************/
#define WEIER_VX0  ECC_V0
#define WEIER_VY0  ECC_V1
#define WEIER_VZ0  ECC_V2
#define WEIER_VZ   ECC_V3

#define WEIER_VX1  ECC_V4
#define WEIER_VY1  ECC_V5
#define WEIER_VT2  ECC_V6
#define WEIER_VT3  ECC_V7

#define WEIER_VX2  ECC_V8
#define WEIER_VY2  ECC_V9
#define WEIER_VZ2  ECC_VA
#define WEIER_VT   ECC_VB

#define WEIER_A    ECC_CP0
#define WEIER_B    ECC_CP1

#define WEIER_XA  ECC_COORD00
#define WEIER_YA  ECC_COORD01
#define WEIER_ZA  ECC_COORD02
#define WEIER_Z   ECC_COORD03
#define WEIER_X0  ECC_COORD04
#define WEIER_Y0  ECC_COORD05
#define WEIER_X1  ECC_COORD06
#define WEIER_Y1  ECC_COORD07
#define WEIER_X2  ECC_COORD08
#define WEIER_Y2  ECC_COORD09
#define WEIER_X3  ECC_COORD10
#define WEIER_Y3  ECC_COORD11

#define ECC_KEYGEN_NO_OF_VIRTUALS     ECC_NO_OF_VIRTUALS
#define ECC_KEYGEN_NO_OF_BUFFERS      (WEIER_Y1 + 1u - ECC_KEYGEN_NO_OF_VIRTUALS)

#define ECC_SIGN_NO_OF_VIRTUALS       ECC_NO_OF_VIRTUALS
#define ECC_SIGN_NO_OF_BUFFERS        (WEIER_Y1 + 1u - ECC_SIGN_NO_OF_VIRTUALS)

#define ECC_VERIFY_NO_OF_VIRTUALS     ECC_NO_OF_VIRTUALS
#define ECC_VERIFY_NO_OF_BUFFERS      (WEIER_Y3 + 1u - ECC_VERIFY_NO_OF_VIRTUALS)

#define ECC_POINTMULT_NO_OF_VIRTUALS  ECC_NO_OF_VIRTUALS
#define ECC_POINTMULT_NO_OF_BUFFERS   (WEIER_Y1 + 1u - ECC_POINTMULT_NO_OF_VIRTUALS)

#define ECC_GENERATEDOMAINPARAMS_NO_OF_VIRTUALS  ECC_NO_OF_VIRTUALS
#define ECC_GENERATEDOMAINPARAMS_NO_OF_BUFFERS   (WEIER_Y0 + 1u - ECC_GENERATEDOMAINPARAMS_NO_OF_VIRTUALS)




/**********************************************************/
/* Helper macros of import/export with flow protection    */
/**********************************************************/

/** Helper macro to call #mcuxClMemory_copy for importing data to PKC workarea with flow protection. */
#define MCUXCLECC_FP_IMPORT_TO_PKC_BUFFER(pOffsetTable, iTarget, pSource, byteLen)  \
    MCUXCLECC_FP_MEMORY_COPY(MCUXCLPKC_OFFSET2PTR((pOffsetTable)[iTarget]), pSource, byteLen)

#define MCUXCLECC_FP_CALLED_MEMORY_COPY  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)
#define MCUXCLECC_FP_CALLED_IMPORT_TO_PKC_BUFFER  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)


/**********************************************************/
/* Internal function declaration                          */
/**********************************************************/

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_Weier_SetupEnvironment)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_Weier_SetupEnvironment(
        mcuxClSession_Handle_t pSession,
        const mcuxClEcc_DomainParam_t *pWeierDomainParams,
        uint8_t noOfBuffers
        );

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_WeierECC_SetupEnvironment)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_WeierECC_SetupEnvironment(
        mcuxClSession_Handle_t pSession,
        mcuxClEcc_Weier_DomainParams_t *pWeierDomainParams,
        uint8_t noOfBuffers
        );



/**********************************************************/
/* Internal function declaration - point check            */
/**********************************************************/
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_PointCheckAffineNR)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_PointCheckAffineNR(void);


/**********************************************************/
/* Internal function declaration - point arithmetic       */
/**********************************************************/
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_RepeatPointDouble)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClEcc_RepeatPointDouble(uint32_t iteration);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_PointFullAdd)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_PointFullAdd(void);

/**********************************************************/
/* Internal function declaration - point multiplication   */
/**********************************************************/
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_Int_PointMult)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClEcc_Int_PointMult(uint8_t iScalar, uint32_t scalarBitLength);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_SecurePointMult)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_SecurePointMult(mcuxClSession_Handle_t pSession,
                                                                       uint8_t iScalar,
                                                                       uint32_t scalarBitLength);


/**********************************************************/
/* Internal function declaration - key generation         */
/**********************************************************/
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_Int_CoreKeyGen)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_Int_CoreKeyGen(mcuxClSession_Handle_t pSession,
                                                                      uint32_t nByteLength);

/**
 * @brief Function implementing WeierECC key pair generation.
 * @api
 *
 * This function generates an ECC key pair for usage within WeierECC protocols such as ECDSA and ECDH.
 *
 * @param      pSession             Handle for the current CL session.
 * @param[in]  generation           Key generation algorithm specifier.
 * @param[out] privKey              Key handle for the generated private key.
 * @param[out] pubKey               Key handle for the generated public key.
 *
 * @return status
 * @retval #MCUXCLECC_STATUS_OK              if private key and public key are generated successfully;
 * @retval #MCUXCLECC_STATUS_INVALID_PARAMS  if parameters are invalid;
 * @retval #MCUXCLECC_STATUS_RNG_ERROR       if random number (DRBG / PRNG) error (unexpected behavior);
 * @retval #MCUXCLECC_STATUS_FAULT_ATTACK    if fault attack (unexpected behavior) is detected.
 *
 * @attention This function uses DRBG and PRNG. Caller needs to check if DRBG and PRNG are ready.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_WeierECC_GenerateKeyPair, mcuxClKey_KeyGenFct_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClEcc_WeierECC_GenerateKeyPair(
    mcuxClSession_Handle_t pSession,
    mcuxClKey_Generation_t generation,
    mcuxClKey_Handle_t privKey,
    mcuxClKey_Handle_t pubKey
    );



/**********************************************************/
/* Internal function declaration - key agreement          */
/**********************************************************/




#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLECC_WEIER_INTERNAL_H_ */
