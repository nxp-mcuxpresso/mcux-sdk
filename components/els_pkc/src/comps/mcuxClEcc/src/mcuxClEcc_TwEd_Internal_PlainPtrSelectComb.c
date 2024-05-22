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
 * @file  mcuxClEcc_TwEd_Internal_PrecPointImportAndValidate.c
 * @brief Function to import, convert and validate the coordinates of a pre-computed point
 */

#include <mcuxClToolchain.h>
#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#include <internal/mcuxClPkc_ImportExport.h>
#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClEcc_TwEd_Internal.h>


/**
 * For a given 4 bit scalar digit (i3 i2 i1 i0)_2, this function sets TWED_PP_VX0 to the buffer
 * storing the X-coordinate of PP = P_{(i3 i2 i1)_2 ^ (i0 i0 i0)_2 ^ (1 1 1)_2} and
 *  - if i0 = 1, sets TWED_PP_VY0 and TWED_PP_VT0 to the buffers storing the Y- and T-coordinates of PP.
 *  - if i0 = 0, sets TWED_PP_VY0 and TWED_PP_VT0 to buffers ECC_T2 and ECC_T3 and store the negative Y-
 *    and T-coordinates of PP in buffers ECC_T2 and ECC_T3.
 *
 * The function is not implemented to protect against side-channel attacks.
 *
 * Parameters:
 *  - pSession              Handle for the current CL session
 *  - scalarWord            CPU word containing the digit (i3 i2 i1 i0)_2
 *  - scalarDigitOffset     Bit offset in scalarWord of the digit (i3 i2 i1 i0)_2
 *
 * Prerequisites:
 *  - ps1Len = (operandSize, operandSize)
 *  - Buffer ECC_PFULL contains p'||p
 *  - Buffer ECC_PS contains the shifted modulus associated to p
 *
 * Result:
 *  - Virtual pointers TWED_PP_VX0, TWED_PP_VY0 and TWED_PP_VT0 as well as buffers ECC_T2 and ECC_T3 are prepared as described above.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_TwEd_PlainPtrSelectComb, mcuxClEcc_TwEd_PtrSelectFunction_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_TwEd_PlainPtrSelectComb(
    mcuxClSession_Handle_t pSession UNUSED_PARAM,
    uint32_t scalarWord,
    uint8_t scalarDigitOffset
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_TwEd_PlainPtrSelectComb);

    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();

    /* Step 1: Derive digit (i3 i2 i1 i0)_2 from scalarWord. */
    uint32_t nibble = (scalarWord >> scalarDigitOffset) & MCUXCLECC_TWED_FIXSCALARMULT_DIGITMASK;

    /* Step 2: Derive table index tiX of buffer storing the X-coordinate of PP = P_{(i3 i2 i1)_2 ^ (i0 i0 i0)_2 ^ (1 1 1)_2}. */
    uint32_t tiX = TWED_PP_X0 + 3u * ( ((nibble & 0xEu)>>1) ^ (7u * (nibble & 0x1u)) ^ (0x7u));

    /* Step 3: Set virtual pointers TWED_PP_VX0, TWED_PP_VY0 and TWED_PP_VT0 to the pointer table entries with indices tiX, tiX+1 and tiX+2. */
    MCUXCLPKC_WAITFORREADY();
    pOperands[TWED_PP_VX0] = (uint16_t) pOperands[tiX];
    pOperands[TWED_PP_VY0] = (uint16_t) pOperands[tiX + 1u];
    pOperands[TWED_PP_VT0] = (uint16_t) pOperands[tiX + 2u];

    if(0u == (nibble & 0x1u))
    {
        /* Step 4: If i0 == 0:
         *   - Compute ECC_T2 = ECC_P - TWED_PP_VX0 and ECC_T3 = ECC_P - TWED_PP_VT0.
         *   - Set virtual pointers TWED_PP_VX0 and TWED_PP_VT0 to buffers ECC_T2 and ECC_T3. */
        MCUXCLPKC_FP_CALC_OP1_SUB(ECC_T2, ECC_P, TWED_PP_VX0);
        MCUXCLPKC_FP_CALC_OP1_SUB(ECC_T3, ECC_P, TWED_PP_VT0);
        pOperands[TWED_PP_VX0] = (uint16_t) pOperands[ECC_T2];
        pOperands[TWED_PP_VT0] = (uint16_t) pOperands[ECC_T3];
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_TwEd_PlainPtrSelectComb, MCUXCLECC_STATUS_OK,
        MCUX_CSSL_FP_CONDITIONAL(0u == (nibble & 0x1u),
                                MCUXCLPKC_FP_CALLED_CALC_OP1_SUB,
                                MCUXCLPKC_FP_CALLED_CALC_OP1_SUB)
    );
}
