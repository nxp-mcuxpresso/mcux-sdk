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
 * @file  mcuxClEcc_TwEd_Internal_PlainPtrSelectML.c
 * @brief Function to set the virtual pointers of coordinates of accumulated ladder points
 *  to be used by the upcoming Montgomery Ladder step depending on the current scalar bit b
 */

#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#include <internal/mcuxClPkc_Macros.h>

#include <mcuxClEcc_Types.h>
#include <internal/mcuxClEcc_Internal.h>
#include <internal/mcuxClEcc_TwEd_Internal.h>
#include <internal/mcuxClEcc_EdDSA_Internal_PkcWaLayout.h>

/**
 * Plain pointer selection function
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_TwEd_PlainPtrSelectML, mcuxClEcc_TwEd_PtrSelectFunction_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_TwEd_PlainPtrSelectML(
    mcuxClSession_Handle_t pSession,
    uint32_t scalarWord,
    uint8_t scalarBitOffset
)
{
    (void)pSession;

    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_TwEd_PlainPtrSelectML);

    /* Select bit b */
    uint32_t b = (scalarWord >> scalarBitOffset) & 0x01u;

    /* Select the pointers for the accumulated Montgomery ladder points.
     * As TWED_ML_Y1, ... TWED_ML_Z2 are four consecutive offsets in the UPTR table, the selection of
     * (TWED_ML_Y1, TWED_ML_Z1) or (TWED_ML_Y2, TWED_ML_Z2) can be done based on the value of the bit b,
     * to achieve the following:
     *     if (1u == b)
     *     {
     *         pOperands[TWED_VY1] = pOperands[TWED_ML_Y2];
     *         pOperands[TWED_VZ1] = pOperands[TWED_ML_Z2];
     *         pOperands[TWED_VY2] = pOperands[TWED_ML_Y1];
     *         pOperands[TWED_VZ2] = pOperands[TWED_ML_Z1];
     *     }
     *     else
     *     {
     *         pOperands[TWED_VY1] = pOperands[TWED_ML_Y1];
     *         pOperands[TWED_VZ1] = pOperands[TWED_ML_Z1];
     *         pOperands[TWED_VY2] = pOperands[TWED_ML_Y2];
     *         pOperands[TWED_VZ2] = pOperands[TWED_ML_Z2];
     *     };
     */
    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("32-bit aligned UPTRT table is assigned in CPU workarea")
    uint32_t *pOperands32 = (uint32_t *) pOperands;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()
    uint32_t offsets_VY1_VZ1 = pOperands32[(TWED_ML_Y1 / 2u) + b];
    uint32_t offsets_VY2_VZ2 = pOperands32[(TWED_ML_Y2 / 2u) - b];

    MCUXCLPKC_WAITFORREADY();

    MCUXCLECC_STORE_2OFFSETS(pOperands32, TWED_VY1, TWED_VZ1, offsets_VY1_VZ1);
    MCUXCLECC_STORE_2OFFSETS(pOperands32, TWED_VY2, TWED_VZ2, offsets_VY2_VZ2);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_TwEd_PlainPtrSelectML, MCUXCLECC_STATUS_OK);
}
