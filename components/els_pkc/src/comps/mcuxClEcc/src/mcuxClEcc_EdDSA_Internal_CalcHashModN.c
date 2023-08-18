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
 * @file  mcuxClEcc_EdDSA_CalcHashModN.c
 * @brief Function to calculate the hash H(prefix||Renc||Qenc||m') mod n
 */


#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClHash.h>

#include <internal/mcuxClPkc_Macros.h>
#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClEcc_EdDSA_Internal.h>
#include <internal/mcuxClEcc_EdDSA_Internal_Hash.h>
#include <internal/mcuxClEcc_EdDSA_Internal_CalcHashModN_FUP.h>


/**
 * This function calculates the hash H(prefix||Renc||Qenc||m') mod n using the hash function algoHash
 * specified in the EdDSA domain parameters.
 *
 * Input:
 *  - pSession          Handle for the current CL session
 *  - pCtx              Pointer to hash context
 *  - pDomainParams     Pointer to ECC common domain parameters structure
 *  - pHashPrefix       Pointer to prefix
 *  - hashPrefixLen     Byte length of prefix
 *  - pSignatureR       Pointer to Renc
 *  - pPubKey           Pointer to Qenc
 *  - pIn               Pointer to input for hash algorithm
 *  - inSize            Size of pIn
 *
 * Prerequisites:
 * - ps1Len = (operandSize, operandSize)
 * - Buffer ECC_NFULL contains n'||n
 * - Buffer ECC_N contains n
 *
 * Result:
 *  - The result H(prefix||Renc||Qenc||m') mod n is stored in buffer ECC_S0 in NR
 *
 * Return values:
 *  - MCUXCLECC_STATUS_OK            if the function executed successfully
 *  - MCUXCLECC_STATUS_FAULT_ATTACK  if the hashing failed
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_EdDSA_CalcHashModN)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_EdDSA_CalcHashModN(
    mcuxClSession_Handle_t pSession,
    mcuxClHash_Context_t pCtx,
    mcuxClEcc_EdDSA_DomainParams_t *pDomainParams,
    const uint8_t *pHashPrefix,
    uint32_t hashPrefixLen,
    const uint8_t *pSignatureR,
    const uint8_t *pPubKey,
    const uint8_t *pIn,
    uint32_t inSize
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_EdDSA_CalcHashModN);

    /* Step 1: Calculate the hash value H(prefix||Renc||Qenc||m') and store it in the consecutive buffers ECC_S0 and ECC_T0. */
    /* Encoded length = M = 32-byte for Ed25519 (b = 256 = 32*8) */
    /*                   or 57-byte for Ed448 (b = 456 = 57*8).  */
    const uint32_t encodedLen = (uint32_t) pDomainParams->b / 8u;
    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    uint8_t *pS0 = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_S0]);

    /* Clear T0 with 0's, so ECC_S0 and ECC_T0 will only contain h and thereafter modular reduction can be done */
    uint32_t operandSize = MCUXCLPKC_PS1_GETOPLEN();
    const uint32_t bufferSize = operandSize + MCUXCLPKC_WORDSIZE;
    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_PS2_SETLENGTH(0u, bufferSize);
    MCUXCLPKC_FP_CALC_OP2_CONST(ECC_T0, 0u);

    /* Calculate 2b-bit hash of (prefix||Renc||Qenc||m'). */
    MCUXCLECC_FP_EDDSA_SIGN_VERIFY_CALC_HASH(pSession,
                                pCtx,
                                pDomainParams->algoHash,
                                pHashPrefix, hashPrefixLen,
                                pSignatureR, encodedLen,
                                pPubKey, encodedLen,
                                pIn, inSize,
                                pS0);

    /* Step 2: Use the PKC to calculate H(prefix||Renc||Qenc||m') mod n, and store the result in ECC_S0. */
    /* Calculate the Montgomery parameter Q' = 2 ^ (8*(operandSize + bufferSize)) mod n and store it in ECC_T1
     *
     * NOTE: The scalar r is of byte length b/4, i.e. we have, irrespective of the underlying PKC word size
     *        - for Ed25519: byteLen(h) = 64  = 2*operandSize < operandSize + bufferSize
     *        - for Ed448:   byteLen(h) = 114 < operandSize + bufferSize.
     *       Thus, we can obtain h mod n by a multiplication of h (considered as operand of size
     *       (operandSize + bufferSize)) with Q' modulo n
     *      Which is:
     *      MM(H(..), 2^(8*(operandSize(H(..)))), n) = H(..) * 2^(8*(operandSize(H(..)))) * 2^(-8*(operandSize(H(..)))) mod n
     *                                               = H(..) mod n
     *      with: operandSize(H(..)) = operandSize + bufferSize = operandSize + operandSize + PKC_WORDSIZE */
    const uint8_t *pT1 = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_T1]);
    MCUXCLPKC_WAITFORREADY();
    pOperands[ECC_V0] = MCUXCLPKC_PTR2OFFSET(&pT1[MCUXCLPKC_WORDSIZE]);
    MCUXCLPKC_PS2_SETLENGTH(operandSize + bufferSize, operandSize);
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_EdDSA_Internal_CalcHashModN_ModN,
                        mcuxClEcc_FUP_EdDSA_Internal_CalcHashModN_ModN_LEN);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_CalcHashModN, MCUXCLECC_STATUS_OK,
        /* Step 1 */
        MCUXCLECC_FP_CALLED_EDDSA_SIGN_VERIFY_CALC_HASH,
        MCUXCLPKC_FP_CALLED_CALC_OP2_CONST,
        /* Step 2 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) );
}
