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
 * @file  mcuxClEcc_Internal_RecodeAndReorderScalar.c
 * @brief mcuxClEcc: implementation of mcuxClEcc_RecodeAndReorderScalar
 */

#include <mcuxClToolchain.h>
#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClPkc.h>
#include <mcuxClMath.h>

#include <mcuxClEcc.h>

#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClEcc_Internal.h>
#include <internal/mcuxClEcc_Internal_UPTRT_access.h>
#include <internal/mcuxClEcc_Internal_Interleave_FUP.h>
#include <internal/mcuxClMath_Internal_Utils.h>


/**
 * This function recodes an odd, potentially secret, scalar lambda = (lambda_{f*K-1},...,lambda_0)_2 of (not necessarily exact) bit length f*K,
 * into non-zero BSD representation by rotating it right by one bit to obtain
 *
 *      lambda~ = (lambda~_{f*K-1},...,lambda~_0)_2 = (lambda_{f*K-1},...,lambda_0)_2.
 *
 * Further, it reorders the bits of lambda~ for usage within the comb method by splitting it into f parts and interleaving them to obtain
 *
 *      lambda' = (lambda~_{f*K-1}, lambda~_{(f-1)*K-1},...,lambda~_{K-1},...,lambda~_{(f-1)*K},lambda~_{(f-2)*K},...,lambda~_0)_2
 *
 * Input:
 *   - pSession         Handle for the current CL session
 *   - scalarIndex      Table index of buffer storing the scalar lambda to be blinded
 *   - f                Number of parts into which the scalar will be divided; must be a power of two
 *   - scalarBitLength  scalar length in bits, must be a multiple of f.
 *
 * Prerequisites:
 *   - ps1Len = (operandSize, operandSize)
 *
 * Result:
 *   - The recoded and reordered scalar lambda' is contained in the buffer with table index scalarIndex.
 *
 * Other modifications:
 *   - Buffers ECC_T0 and ECC_T1 are modified (as temp).
 *   - Offsets pOperands[ECC_V0/ECC_V1/ECC_V3] are modified.
 *   - ps2 LEN and MCLEN are modified.
 *
 * @attention The PKC calculation might be still on-going, call #mcuxClPkc_WaitForFinish before CPU accesses to the result.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_RecodeAndReorderScalar)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_RecodeAndReorderScalar(mcuxClSession_Handle_t pSession UNUSED_PARAM,
                                                                        uint8_t scalarIndex,
                                                                        uint8_t f,
                                                                        uint32_t scalarBitLength)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_RecodeAndReorderScalar);

    /* Step 1:
     * Set the pointer in ECC_V0 to the buffer corresponding to scalarIndex.
     */
    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    MCUXCLPKC_WAITFORREADY();
    pOperands[ECC_V0] = pOperands[scalarIndex];

    /* Step 2:
     * Use PKC to rotate the buffer ECC_V0 to the right by one bit.
     */
    MCUXCLPKC_FP_CALC_OP1_ROTR(ECC_V0, ECC_V0, 1u);

    /* Step 3:
     * Use the PKC to move the MSBit of the buffer to bit position f*K-1 of the buffer ECC_V0. The buffer now contains lambda~.
     */
    // TODO: Moving the MSBit still to be done (but not necessary for Ed25519 and Ed448 with f = 4) -> CLNS-6486

    /* Step 4:
     * Successively ( log_2(f) times ) do the following:
     *   - Shift upper half of the f*K bit value in ECC_V0 to the next FAME word boundary
     *   - Use PKC to square lower and upper half of the value in ECC_V0 and store the results in ECC_T0 and ECC_T1, respectively
     *   - Left shift ECC_T1 by one bit
     *   - Set ECC_V0 = ECC_T0 | ECC_T1
     *
     * This is all done by mcuxClEcc_InterleaveScalar.
     */
    uint32_t fLog = 32u - mcuxClMath_CountLeadingZerosWord((uint32_t) f) - 1u;
    MCUXCLECC_FP_INTERLEAVESCALAR(scalarIndex, scalarBitLength, fLog);

    /* Step 5:
     * Complete pkc operations
     */
    MCUXCLPKC_WAITFORREADY();

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_RecodeAndReorderScalar, MCUXCLECC_STATUS_OK,
        MCUXCLPKC_FP_CALLED_CALC_OP1_ROTR,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_InterleaveScalar));
}
