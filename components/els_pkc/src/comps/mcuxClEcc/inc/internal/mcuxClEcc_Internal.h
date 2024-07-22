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
 * @file  mcuxClEcc_Internal.h
 * @brief internal header of mcuxClEcc functionalities
 */


#ifndef MCUXCLECC_INTERNAL_H_
#define MCUXCLECC_INTERNAL_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClSession.h>
#include <mcuxClCore_Macros.h>
#include <mcuxClBuffer.h>
#include <mcuxClEcc_Types.h>

#include <internal/mcuxClEcc_Internal_UPTRT_access.h>
#include <internal/mcuxClEcc_Internal_PkcWaLayout.h>

#ifdef __cplusplus
extern "C" {
#endif


/**********************************************************/
/*                                                        */
/* Internal return codes of mcuxClEcc                      */
/*                                                        */
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
/*                                                        */
/* Definition of CPU workarea layout of ECC APIs          */
/*                                                        */
/**********************************************************/

MCUX_CSSL_ANALYSIS_START_SUPPRESS_FLEXIBLE_ARRAY("Due to project requirements ECC component needs to handle different usecases. In order to preserve memory flexible array is used. It is user responsibility to provide sufficient memory area using provided macros for each usecase.")
typedef struct
{
    uint32_t wordNumCpuWa;  /* number of words (uint32_t) used in CPU workarea */
    uint32_t wordNumPkcWa;  /* number of words (uint32_t) used in PKC workarea */
    mcuxClPkc_State_t pkcStateBackup;
    uint32_t pOperands32[];
} mcuxClEcc_CpuWa_t;
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_FLEXIBLE_ARRAY()


/**********************************************************/
/*                                                        */
/* Definition of generic ECC domain parameters            */
/*                                                        */
/**********************************************************/

typedef struct mcuxClEcc_CommonDomainParams mcuxClEcc_CommonDomainParams_t;


/**
 * The scalar multiplication function declaration
 * and structure containing the function pointer and its associated flow protection ID.
 */
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClEcc_ScalarMultFunction_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) (*mcuxClEcc_ScalarMultFunction_t)(
    mcuxClSession_Handle_t pSession,                ///< Handle for the current CL session
    mcuxClEcc_CommonDomainParams_t *pDomainParams,  ///< Pointer to ECC domain parameters structure
    uint8_t iScalar,                               ///< Pointer table index of scalar buffer in PKC RAM
    uint32_t scalarBitLength,                      ///< Bit length of the scalar
    uint32_t options                               ///< Parameter to pass options
    ));
typedef struct
{
    mcuxClEcc_ScalarMultFunction_t pScalarMultFct;   ///< scalar multiplication function pointer
    uint32_t scalarMultFct_FP_FuncId;               ///< FP ID of the function
} mcuxClEcc_ScalarMultFunction_FP_t;

/**
 * Common part of domain parameter structure, shared by all ECC functions.
 */
struct mcuxClEcc_CommonDomainParams
{
    uint16_t byteLenP;       ///< byte length of prime p
    uint16_t byteLenN;       ///< byte length of base point order n
    uint8_t *pFullModulusP;  ///< pointer to p'||p (in little endian format)
    uint8_t *pFullModulusN;  ///< pointer to n'||n (in little endian format)
    uint8_t *pR2P;           ///< pointer to Montgomery parameter R^2 mod p (in little endian format)
    uint8_t *pR2N;           ///< pointer to Montgomery parameter R^2 mod n (in little endian format)
    uint8_t *pCurveParam1;   ///< Pointer to first curve parameter (a for Weierstrass and twisted Edwards curves and A for Montgomery curves)
    uint8_t *pCurveParam2;   ///< Pointer to second curve parameter (b for Weierstrass curves, d for twisted Edwards curves and B for Montgomery curves)
    uint8_t *pGx;            ///< Pointer to x-coordinate Gx of base point G
    uint8_t *pGy;            ///< Pointer to y-coordinate Gy of base point G
    uint8_t *pPrecPoints;    ///< Pointer to pre-computed points for fixed base point scalar multiplication (2^(byteLenN * 4) * G for Weierstrass curves, used in ECDSA signature verification; reserved for other curves)
    uint8_t *pLadderConst;   ///< Pointer to pre-computed Montgomery ladder constant (in little endian format, used for Montgomery and Twisted Edwards curves)
    const mcuxClEcc_ScalarMultFunction_FP_t *pSecFixScalarMultFctFP;    ///< Pointer to secure scalar multiplication function and FP ID that shall be used to perform a scalar multiplication lambda*G for secret scalar lambda in {1,...,n-1} and base point G
    const mcuxClEcc_ScalarMultFunction_FP_t *pSecVarScalarMultFctFP;    ///< Pointer to secure scalar multiplication function and FP ID that shall be used to perform a scalar multiplication lambad*P for secret scalar lambda in {1,...,n-1} and arbitrary point P on the curve
    const mcuxClEcc_ScalarMultFunction_FP_t *pPlainFixScalarMultFctFP;  ///< Pointer to plain scalar multiplication function and FP ID that shall be used to perform a scalar multiplication lambda*G for non-secret scalar lambda in {1,...,n-1} and base point G
    const mcuxClEcc_ScalarMultFunction_FP_t *pPlainVarScalarMultFctFP;  ///< Pointer to plain scalar multiplication function and FP ID that shall be used to perform a scalar multiplication lambda*G for non-secret scalar lambda in {1,...,n-1} and arbitrary point P on the curve
};


/**********************************************************/
/*                                                        */
/* Miscellanious definitions                              */
/*                                                        */
/**********************************************************/

/**
 * Options to determine whether scalar multiplication input/output are in affine or projective format.
 */
#define MCUXCLECC_SCALARMULT_OPTION_PROJECTIVE_INPUT    (0x000000A5u)
#define MCUXCLECC_SCALARMULT_OPTION_AFFINE_INPUT        (0x0000005Au)
#define MCUXCLECC_SCALARMULT_OPTION_INPUT_MASK          (0x000000FFu)
#define MCUXCLECC_SCALARMULT_OPTION_PROJECTIVE_OUTPUT   (0x0000C300u)
#define MCUXCLECC_SCALARMULT_OPTION_AFFINE_OUTPUT       (0x00003C00u)
#define MCUXCLECC_SCALARMULT_OPTION_OUTPUT_MASK         (0x0000FF00u)

/**
 * Define specifying the size of the multiplicative scalar blinding bit size
 */
#define MCUXCLECC_SCALARBLINDING_BITSIZE (32u)
#define MCUXCLECC_SCALARBLINDING_BYTELEN (MCUXCLECC_SCALARBLINDING_BITSIZE / 8u)


#define MCUXCLECC_ALL_ONES_WORD (0xFFFFFFFFU)


/**********************************************************/
/*                                                        */
/* Internal function declarations                         */
/*                                                        */
/**********************************************************/

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_InterleaveScalar)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_InterleaveScalar(uint16_t iScalar, uint32_t scalarBitLength, uint32_t numberOfInterleavings);

/** Helper macro to call #mcuxClEcc_InterleaveScalar with flow protection. */
#define MCUXCLECC_FP_INTERLEAVESCALAR(iScalar, bitLenScalar, numberOfInterleavings)  \
    do{ \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClEcc_InterleaveScalar(iScalar, bitLenScalar, numberOfInterleavings));  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
    } while (false)


MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_InterleaveTwoScalars)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_InterleaveTwoScalars(uint16_t iScalar0_iScalar1, uint32_t scalarBitLength);

/** Helper macro to call #mcuxClEcc_InterleaveTwoScalars with flow protection. */
#define MCUXCLECC_FP_INTERLEAVETWOSCALARS(iS0_iS1, bitLenScalar)  \
    do{ \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClEcc_InterleaveTwoScalars(iS0_iS1, bitLenScalar));  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
    } while (false)


MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_GenerateMultiplicativeBlinding)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_GenerateMultiplicativeBlinding(
    mcuxClSession_Handle_t pSession,
    uint8_t scalarIndex
    );



MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_BlindedScalarMult)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_BlindedScalarMult(
    mcuxClSession_Handle_t pSession,
    mcuxClEcc_CommonDomainParams_t *pCommonDomainParams
    );



MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_SetupEnvironment)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_SetupEnvironment(
    mcuxClSession_Handle_t pSession,
    mcuxClEcc_CommonDomainParams_t *pCommonDomainParams,
    uint8_t noOfBuffers
    );

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_RecodeAndReorderScalar)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_RecodeAndReorderScalar(
    mcuxClSession_Handle_t pSession,
    uint8_t scalarIndex,
    uint8_t f,
    uint32_t scalarBitLength
    );

/** Helper macro to call #mcuxClEcc_RecodeAndReorderScalar with flow protection. */
#define MCUXCLECC_FP_RECODEANDREORDERSCALAR(scalarIndex, f, scalarBitLength)  \
    do{ \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClEcc_RecodeAndReorderScalar(pSession, scalarIndex, f, scalarBitLength));  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
    } while (false)



    #define MCUXCLECC_HANDLE_HW_UNAVAILABLE(retCodeReceived, callerName) do{} while(false)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLECC_INTERNAL_H_ */
