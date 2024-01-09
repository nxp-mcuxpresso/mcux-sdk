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
 * @file  mcuxClEcc_EdDSA_Internal_DecodePoint_FUP.h
 * @brief defines FUP programs byte arrays
 */


#ifndef MCUXCLECC_EDDSA_INTERNAL_DECODEPOINT_FUP_H_
#define MCUXCLECC_EDDSA_INTERNAL_DECODEPOINT_FUP_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <internal/mcuxClPkc_FupMacros.h>


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

/**
 * FUP program declaration mcuxClEcc_FUP_EdDSA_Internal_DecodePoint_PrepareExp_Ed448
 */
#define mcuxClEcc_FUP_EdDSA_Internal_DecodePoint_PrepareExp_Ed448_LEN  7u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_EdDSA_Internal_DecodePoint_PrepareExp_Ed448[mcuxClEcc_FUP_EdDSA_Internal_DecodePoint_PrepareExp_Ed448_LEN];

/**
 * FUP program declaration mcuxClEcc_FUP_EdDSA_Internal_DecodePoint_ComputeXCandidate_Ed448
 */
#define mcuxClEcc_FUP_EdDSA_Internal_DecodePoint_ComputeXCandidate_Ed448_LEN  6u
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_EdDSA_Internal_DecodePoint_ComputeXCandidate_Ed448[mcuxClEcc_FUP_EdDSA_Internal_DecodePoint_ComputeXCandidate_Ed448_LEN];


#endif /* MCUXCLECC_EDDSA_INTERNAL_DECODEPOINT_FUP_H_ */
