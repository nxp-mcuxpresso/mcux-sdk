/*--------------------------------------------------------------------------*/
/* Copyright 2021-2023 NXP                                                  */
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
 * @file  mcuxClEcc_Internal_Types.c
 * @brief Instantiation of the type descriptors supported by the mcuxClEcc component.
 */

#include <internal/mcuxClEcc_EdDSA_Internal.h>

/**********************************************************/
/* Key pair generation descriptors                        */
/**********************************************************/

const mcuxClEcc_EdDSA_GenerateKeyPairDescriptor_t mcuxClEcc_EdDsa_GeneratePrivKeyDescriptor =
{
    .options       = MCUXCLECC_EDDSA_PRIVKEY_GENERATE,
    .pPrivKeyInput = NULL
};


/**********************************************************/
/* Signature protocol descriptors                         */
/**********************************************************/
const mcuxClEcc_EdDSA_SignatureProtocolDescriptor_t mcuxClEcc_EdDsa_Ed25519ProtocolDescriptor =
{
    .generateOption     = 0u,
    .verifyOption       = 0u,
    .pHashPrefix        = NULL,
    .hashPrefixLen  = 0u
};

