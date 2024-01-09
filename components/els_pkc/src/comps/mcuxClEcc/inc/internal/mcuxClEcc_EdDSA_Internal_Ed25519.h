/*--------------------------------------------------------------------------*/
/* Copyright 2023 NXP                                                       */
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
 * @file  mcuxClEcc_EdDSA_Internal_Ed25519.h
 * @brief internal header of mcuxClEcc Ed25519's functionalities
 */


#ifndef MCUXCLECC_EDDSA_INTERNAL_ED25519_H_
#define MCUXCLECC_EDDSA_INTERNAL_ED25519_H_


#include <mcuxClCore_Platform.h>

#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#include <internal/mcuxClEcc_Internal.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Declaration of the point decoding function on Ed25519
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_EdDSA_DecodePoint_Ed25519, mcuxClEcc_EdDSA_DecodePointFunction_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_EdDSA_DecodePoint_Ed25519(
    mcuxClEcc_EdDSA_DomainParams_t *pDomainParams,
    const uint8_t *pEncPoint
    );

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLECC_EDDSA_INTERNAL_ED25519_H_ */
