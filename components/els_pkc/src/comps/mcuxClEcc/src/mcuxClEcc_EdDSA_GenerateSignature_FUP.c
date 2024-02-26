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
 * @file  mcuxClEcc_EdDSA_GenerateKeyPair_FUP.c
 * @brief FUP programs for EdDSA Signature Generation
 */


#include <internal/mcuxClPkc_FupMacros.h>
#include <internal/mcuxClEcc_EdDSA_Internal_PkcWaLayout.h>
#include <internal/mcuxClEcc_EdDSA_GenerateSignature_FUP.h>

const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_EdDSA_GenerateSignature_Compute_S[10] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0xd9u,0x44u,0xc0u,0xc6u},{0xc0u,0x00u,0x1eu,0x17u,0x01u,0x1du},{0xc0u,0x00u,0x1au,0x17u,0x01u,0x1fu},{0x80u,0x00u,0x18u,0x17u,0x01u,0x1bu},{0x80u,0x2au,0x01u,0x1bu,0x01u,0x1bu},{0x80u,0x00u,0x1bu,0x1du,0x01u,0x19u},{0x80u,0x21u,0x01u,0x19u,0x1cu,0x19u},{0x80u,0x00u,0x1bu,0x1fu,0x01u,0x1du},{0x80u,0x2au,0x01u,0x19u,0x1du,0x19u},{0x81u,0x2au,0x01u,0x19u,0x01u,0x19u}};
const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_EdDSA_GenerateSignature_ReduceScalarModN[10] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0x12u,0x9fu,0xbfu,0x50u},{0x00u,0x3eu,0x00u,0x00u,0x03u,0x1bu},{0x00u,0x1au,0x00u,0x04u,0x02u,0x04u},{0x80u,0x00u,0x1bu,0x17u,0x01u,0x1du},{0x80u,0x00u,0x1du,0x17u,0x01u,0x1bu},{0x80u,0x2au,0x01u,0x1bu,0x01u,0x1bu},{0xc0u,0x00u,0x1eu,0x1bu,0x01u,0x1du},{0xc0u,0x00u,0x19u,0x1bu,0x01u,0x1fu},{0x80u,0x2au,0x01u,0x1du,0x01u,0x1du},{0x80u,0x2au,0x01u,0x1du,0x1fu,0x1cu}};




/**
 * FUP program to securely reduce the secret scalar r modulo n
 *
 * Prerequisites:
 *  - ECC_V0 points to the second PKC word of ECC_T1
 *  - ECC_S3 contains the blinded secret scalar (r + rndR) (of size (operandSize + bufferSize)
 *  - ECC_T0 contains the blinding rndR (of size (operandSize + bufferSize)
 *  - PS2 lengths set to (operandSize + bufferSize, operandSize)
 */
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()

/**
 * FUP program to securely compute the EdDSA signature value S
 *
 * Prerequisites:
 *  - ECC_S3 contains the blinding s + rndS of the secret scalar s (considered as of size 2*operandSize)
 *  - ECC_S1 contains the blinding rndS (considered as of size 2*operandSize) with MSByte set to 0
 *  - ECC_S0 contains H := H(prefix || R^{enc} || Q^{enc} || m') mod n
 *  - ECC_S2 contains the secret scalar r
 *  - PS2 lengths set to (2u * operandSize, operandSize)
 */
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
