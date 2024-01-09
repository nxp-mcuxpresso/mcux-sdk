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
 * @file  mcuxClEcc_Internal.h
 * @brief internal header of mcuxClEcc functionalities
 */


#ifndef MCUXCLECC_INTERNAL_H_
#define MCUXCLECC_INTERNAL_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClSession.h>
#include <mcuxClCore_Buffer.h>
#include <mcuxClPkc_Functions.h>
#include <mcuxClEcc_Types.h>

#include <internal/mcuxClEcc_Internal_UPTRT_access.h>

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************/
/*                                                        */
/* Definition of generic CPU and PKC workarea layout      */
/*                                                        */
/**********************************************************/

/**
 * Generic ECC PKC workarea memory layout.
 */
#define ECC_P    0x00u
#define ECC_N    0x01u
#define ECC_ONE  0x02u
#define ECC_ZERO 0x03u

#define ECC_V0   0x04u
#define ECC_V1   0x05u
#define ECC_V2   0x06u
#define ECC_V3   0x07u
#define ECC_V4   0x08u
#define ECC_V5   0x09u
#define ECC_V6   0x0Au
#define ECC_V7   0x0Bu
#define ECC_V8   0x0Cu
#define ECC_V9   0x0Du
#define ECC_VA   0x0Eu
#define ECC_VB   0x0Fu

#define ECC_PS     0x10u
#define ECC_NS     0x11u
#define ECC_CP0    0x12u
#define ECC_CP1    0x13u
#define ECC_PFULL  0x14u
#define ECC_NFULL  0x15u
#define ECC_PQSQR  0x16u
#define ECC_NQSQR  0x17u

#define ECC_S0  0x18u
#define ECC_T0  0x19u
#define ECC_S1  0x1Au
#define ECC_T1  0x1Bu
#define ECC_S2  0x1Cu
#define ECC_T2  0x1Du
#define ECC_S3  0x1Eu
#define ECC_T3  0x1Fu

#define ECC_COORD00  0x20u
#define ECC_COORD01  0x21u
#define ECC_COORD02  0x22u
#define ECC_COORD03  0x23u
#define ECC_COORD04  0x24u
#define ECC_COORD05  0x25u
#define ECC_COORD06  0x26u
#define ECC_COORD07  0x27u
#define ECC_COORD08  0x28u
#define ECC_COORD09  0x29u
#define ECC_COORD10  0x2Au
#define ECC_COORD11  0x2Bu
#define ECC_COORD12  0x2Cu
#define ECC_COORD13  0x2Du
#define ECC_COORD14  0x2Eu
#define ECC_COORD15  0x2Fu
#define ECC_COORD16  0x30u
#define ECC_COORD17  0x31u
#define ECC_COORD18  0x32u
#define ECC_COORD19  0x33u
#define ECC_COORD20  0x34u
#define ECC_COORD21  0x35u
#define ECC_COORD22  0x36u
#define ECC_COORD23  0x37u
#define ECC_COORD24  0x38u
#define ECC_COORD25  0x39u
#define ECC_COORD26  0x3Au
#define ECC_COORD27  0x3Bu

#define ECC_NO_OF_VIRTUALS  ECC_PS


/**
 * CPU workarea layout of ECC APIs.
 */
typedef struct
{
    uint32_t wordNumCpuWa;  /* number of words (uint32_t) used in CPU workarea */
    uint32_t wordNumPkcWa;  /* number of words (uint32_t) used in PKC workarea */
    mcuxClPkc_State_t pkcStateBackup;
    uint32_t pOperands32[];
} mcuxClEcc_CpuWa_t;



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
 * Macro to provide truncated digest length
 */
#define MCUXCLECC_TRUNCATED_HASH_LEN(hash, max_len) (((hash) < (max_len)) ? (hash) : (max_len))

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


#define MCUXCLECC_ALIGNED_SIZE(byteLength)  \
    ((((byteLength) + (sizeof(uint32_t)) - 1u) / (sizeof(uint32_t))) * (sizeof(uint32_t)))



/**********************************************************/
/*                                                        */
/* Internal function declarations                         */
/*                                                        */
/**********************************************************/

/** Helper macro to get the minimum of two given constants. */
#define MCUXCLECC_MIN(value0, value1)  (((value0) < (value1)) ? (value0) : (value1))

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
