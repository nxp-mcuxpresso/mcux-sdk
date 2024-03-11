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
 * @file  mcuxClEcc_Weier_Internal.h
 * @brief internal header for short Weierstrass curves
 */


#ifndef MCUXCLECC_WEIER_INTERNAL_H_
#define MCUXCLECC_WEIER_INTERNAL_H_


#include <stdbool.h>
#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClMemory.h>
#include <mcuxClKey_Types.h>
#include <mcuxClMac.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClSession.h>
#include <mcuxClBuffer.h>
#include <mcuxClEcc_Types.h>

#include <internal/mcuxClEcc_Internal.h>
#include <internal/mcuxClEcc_Weier_Internal_PkcWaLayout.h>

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
/* Helper macros of import/export with flow protection    */
/**********************************************************/

/** Helper macro to call #mcuxClMemory_copy for importing data to PKC workarea with flow protection. */
#define MCUXCLECC_FP_IMPORT_TO_PKC_BUFFER(pOffsetTable, iTarget, pSource, byteLen)  \
    MCUXCLECC_FP_MEMORY_COPY(MCUXCLPKC_OFFSET2PTR((pOffsetTable)[iTarget]), pSource, byteLen)

#define MCUXCLECC_FP_CALLED_MEMORY_COPY  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)
#define MCUXCLECC_FP_CALLED_IMPORT_TO_PKC_BUFFER  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)



/**********************************************************/
/* Internal function declaration - Setup Environment      */
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
/* Internal function declaration - point/params checks    */
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
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_WeierECC_BlindedSecretKeyGen_RandomWithExtraBits)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_WeierECC_BlindedSecretKeyGen_RandomWithExtraBits(
    mcuxClSession_Handle_t pSession,
    uint32_t nByteLength);

#ifdef MCUXCL_FEATURE_ECC_ECDSA_DETERMINISTIC
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_DeterministicECDSA_BlindedSecretKeyGen)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_DeterministicECDSA_BlindedSecretKeyGen(
    mcuxClSession_Handle_t pSession,
    uint32_t nByteLength,
    const mcuxClEcc_Sign_Param_t * pParam);
#endif /* MCUXCL_FEATURE_ECC_ECDSA_DETERMINISTIC */




#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLECC_WEIER_INTERNAL_H_ */
