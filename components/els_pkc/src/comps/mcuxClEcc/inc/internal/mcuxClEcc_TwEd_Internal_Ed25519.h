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
 * @file  mcuxClEcc_TwEd_Internal_Ed25519.h
 * @brief internal header of mcuxClEcc Twisted Edward's functionalities
 */


#ifndef MCUXCLECC_TWED_INTERNAL_ED25519_H_
#define MCUXCLECC_TWED_INTERNAL_ED25519_H_


#include <stdint.h>

#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClCore_Buffer.h>
#include <mcuxClMemory.h>
#include <mcuxClPkc.h>
#include <mcuxClHash_Types.h>

#include <internal/mcuxClEcc_Internal.h>
#include <internal/mcuxClEcc_EdDSA_Internal_PkcWaLayout.h>


/**
 * Declaration of the point doubling function on Ed25519
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_TwEd_PointDoubleEd25519, mcuxClEcc_TwEd_PointDoubleFunction_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_TwEd_PointDoubleEd25519(void);

/**
 * Declaration of the mixed point addition function on Ed25519
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_TwEd_MixedPointAddEd25519, mcuxClEcc_TwEd_MixedPointAddFunction_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_TwEd_MixedPointAddEd25519(void);

/**
 * Declaration of function to perform plain (not protected against side-channel attacks) scalar multiplication with the base point on Ed25519
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_TwEd_PlainFixScalarMult25519, mcuxClEcc_ScalarMultFunction_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_TwEd_PlainFixScalarMult25519(
    mcuxClSession_Handle_t pSession,                 ///<  [in]  pSession            Handle for the current CL session
    mcuxClEcc_CommonDomainParams_t *pDomainParams,   ///<  [in]  pDomainParams       Pointer to ECC common domain parameters structure
    uint8_t iScalar,                                ///<  [in]  iScalar             Pointer table index of secret scalar lambda
    uint32_t scalarBitLength,                       ///<  [in]  scalarBitLength     Bit length of the scalar; must be a multiple of 4
    uint32_t options                                ///<  [in]  options             Parameter to pass options
);


#endif /* MCUXCLECC_TWED_INTERNAL_ED25519_H_ */
