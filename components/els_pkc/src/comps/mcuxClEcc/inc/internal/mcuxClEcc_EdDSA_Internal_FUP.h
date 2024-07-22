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
 * @file  mcuxClEcc_EdDSA_Internal_FUP.h
 * @brief defines FUP programs byte arrays
 */


#ifndef MCUXCLECC_EDDSA_INTERNAL_FUP_H_
#define MCUXCLECC_EDDSA_INTERNAL_FUP_H_

#include <mcuxClCore_Platform.h>
#include <mcuxCsslAnalysis.h>

#include <internal/mcuxClPkc_FupMacros.h>

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_ANALYSIS_START_PATTERN_EXTERNAL_LINKAGE_FUP()

/**********************************************************/
/* FUPs for GenerateKeyPair functionality                 */
/**********************************************************/

/**
 * FUP program declaration mcuxClEcc_FUP_EdDSA_GenerateKeyPair_Prepare_S
 */
#define mcuxClEcc_FUP_EdDSA_GenerateKeyPair_Prepare_S_LEN  6u

extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_EdDSA_GenerateKeyPair_Prepare_S[mcuxClEcc_FUP_EdDSA_GenerateKeyPair_Prepare_S_LEN];


/**********************************************************/
/* FUPs for GenerateSignature functionality               */
/**********************************************************/

/**
 * FUP program declaration mcuxClEcc_FUP_EdDSA_GenerateSignature_ReduceScalarModN
 */
#define mcuxClEcc_FUP_EdDSA_GenerateSignature_ReduceScalarModN_LEN  10u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_EdDSA_GenerateSignature_ReduceScalarModN[mcuxClEcc_FUP_EdDSA_GenerateSignature_ReduceScalarModN_LEN];

/**
 * FUP program declaration mcuxClEcc_FUP_EdDSA_GenerateSignature_Compute_S
 */
#define mcuxClEcc_FUP_EdDSA_GenerateSignature_Compute_S_LEN  10u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_EdDSA_GenerateSignature_Compute_S[mcuxClEcc_FUP_EdDSA_GenerateSignature_Compute_S_LEN];


/**********************************************************/
/* FUPs for CalcHashModN functionality                    */
/**********************************************************/

/**
 * FUP program declaration mcuxClEcc_FUP_EdDSA_Internal_CalcHashModN_ModN
 */
#define mcuxClEcc_FUP_EdDSA_Internal_CalcHashModN_ModN_LEN  7u

extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_EdDSA_Internal_CalcHashModN_ModN[mcuxClEcc_FUP_EdDSA_Internal_CalcHashModN_ModN_LEN];


/**********************************************************/
/* FUPs for DecodePoint functionality                     */
/**********************************************************/

/**
 * FUP program declaration mcuxClEcc_FUP_EdDSA_Internal_DecodePoint_PrepareExp_Common
 */
#define mcuxClEcc_FUP_EdDSA_Internal_DecodePoint_PrepareExp_Common_LEN  7u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_EdDSA_Internal_DecodePoint_PrepareExp_Common[mcuxClEcc_FUP_EdDSA_Internal_DecodePoint_PrepareExp_Common_LEN];


/**
 * FUP program declaration mcuxClEcc_FUP_EdDSA_Internal_DecodePoint_PrepareExp_Ed25519
 */
#define mcuxClEcc_FUP_EdDSA_Internal_DecodePoint_PrepareExp_Ed25519_LEN  7u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_EdDSA_Internal_DecodePoint_PrepareExp_Ed25519[mcuxClEcc_FUP_EdDSA_Internal_DecodePoint_PrepareExp_Ed25519_LEN];

/**
 * FUP program declaration mcuxClEcc_FUP_EdDSA_Internal_DecodePoint_ComputeXCandidate_Ed25519
 */
#define mcuxClEcc_FUP_EdDSA_Internal_DecodePoint_ComputeXCandidate_Ed25519_LEN  7u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_EdDSA_Internal_DecodePoint_ComputeXCandidate_Ed25519[mcuxClEcc_FUP_EdDSA_Internal_DecodePoint_ComputeXCandidate_Ed25519_LEN];


MCUX_CSSL_ANALYSIS_STOP_PATTERN_EXTERNAL_LINKAGE_FUP()
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()

#endif /* MCUXCLECC_EDDSA_INTERNAL_FUP_H_ */
