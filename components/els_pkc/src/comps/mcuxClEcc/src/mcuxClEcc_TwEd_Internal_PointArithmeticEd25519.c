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
 * @file  mcuxClEcc_TwEd_Internal_PointArithmeticEd25519.c
 * @brief Edwards curve internal point arithmetic for curve Ed25519
 */


#include <stdint.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#include <mcuxClPkc.h>
#include <mcuxClMath.h>
#include <mcuxClEcc.h>

#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClEcc_TwEd_Internal_Ed25519.h>
#include <internal/mcuxClEcc_TwEd_Internal_Ed25519_FUP.h>


MCUX_CSSL_ANALYSIS_START_SUPPRESS_TEXT_IN_COMMENTS("Links are allowed in comments.")
/**
 * This function implements a point doubling on Ed25519 in extended homogeneous coordinates.
 * More precisely, given a point P = (X:Y:Z:T) in extended homogeneous coordinates it calculates
 * 2*P = (Xres:Yres:Zres:Tres) according to the algorithm specified in Section 3.3 of
 * https://eprint.iacr.org/2008/522.pdf with a = -1.
 *
 * Input:
 *  - pSession  Handle for the current CL session
 *
 * Prerequisites:
 *  - Buffers TWED_X, TWED_Y, TWED_Z and TWED_T contain the homogeneous coordinates (X:Y:Z:T) of P in MR
 *  - ps1Len = (operandSize, operandSize)
 *  - Buffer ECC_PFULL contains p'||p
 *  - Buffer ECC_PS contains the shifted modulus associated to p
 *
 * Result:
 *  - The resulting coordinates (Xres:Yres:Zres:Tres) are stored in buffers TWED_X, TWED_Y, TWED_Z and TWED_T in MR.
 *
 * @attention The PKC calculation might be still on-going, call #mcuxClPkc_WaitForFinish before CPU accesses to the result.
 */
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TEXT_IN_COMMENTS()
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_TwEd_PointDoubleEd25519, mcuxClEcc_TwEd_PointDoubleFunction_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_TwEd_PointDoubleEd25519(void)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_TwEd_PointDoubleEd25519);

    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_TwEd_PointDoubleEd25519, mcuxClEcc_FUP_TwEd_PointDoubleEd25519_Len);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_TwEd_PointDoubleEd25519, MCUXCLECC_STATUS_OK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)
        );
}

MCUX_CSSL_ANALYSIS_START_SUPPRESS_TEXT_IN_COMMENTS("Links are allowed in comments.")
/**
 * This function implements a unified mixed extended point addition on Ed25519.
 * More precisely, given a point P1 = (X1:Y1:Z1:T1) in extended homogeneous
 * coordinates and a point P2 = (X2:Y2:1:T2) in extended affine coordinates,
 * it calculates the sum P1 + P2 in extended homogeneous coordinates
 * P1 = (Xres:Yres:Zres:Tres). To this end the a = -1 specific algorithm specified
 * in Section 3.1 of https://eprint.iacr.org/2008/522.pdf is used with Z2 = 1.
 *
 * Input:
 *  - pSession  Handle for the current CL session
 *
 * Prerequisites:
 *  - Buffers TWED_X, TWED_Y, TWED_Z and TWED_T contain the homogeneous coordinates (X1:Y1:Z1:T1) of P1 in MR
 *  - Pointers TWED_PP_VX0, TWED_PP_VY0 and TWED_PP_VT0 point to the coordinates X2, Y2 and T2 in MR.
 *  - ps1Len = (operandSize, operandSize)
 *  - Buffer ECC_PFULL contains p'||p
 *  - Buffer ECC_PS contains the shifted modulus associated to p
 *
 * Result:
 *  - The resulting coordinates (Xres:Yres:Zres:Tres) are stored in buffers TWED_X, TWED_Y, TWED_Z and TWED_T in MR.
 *
 * @attention The PKC calculation might be still on-going, call #mcuxClPkc_WaitForFinish before CPU accesses to the result.
 */
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TEXT_IN_COMMENTS()
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_TwEd_MixedPointAddEd25519, mcuxClEcc_TwEd_MixedPointAddFunction_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_TwEd_MixedPointAddEd25519(void)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_TwEd_MixedPointAddEd25519);

    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_TwEd_MixedPointAddEd25519, mcuxClEcc_FUP_TwEd_MixedPointAddEd25519_Len);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_TwEd_MixedPointAddEd25519, MCUXCLECC_STATUS_OK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)
        );
}
