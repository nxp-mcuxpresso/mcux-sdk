/*--------------------------------------------------------------------------*/
/* Copyright 2018-2023 NXP                                                  */
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

/*
 * @file: mcuxClOsccaSm2_FUP.c
 * @brief FUP programs for SM2
 */

#include <mcuxClOscca_Types.h>
#include <mcuxClOscca_PlatformTypes.h>
#include <internal/mcuxClOsccaSm2_Internal.h>

MCUXCLOSCCAPKC_FUP_EXT_ROM(mcuxClOsccaSm2_FUP_InvertPrivateKey,
    MCUXCLOSCCAPKC_CRC_ENTRY,
    /* suppose r2 = r2' * R^2 mod n, t3 = r1 * r2' * R mod n */
    FUP_MC1_MMUL(TI_tmp3, TI_tmp1, TI_tmp2, TI_m),
    /* t1 = d + r1 mod n */
    FUP_MC1_MADD(TI_tmp1, TI_tmp1, TI_privateKey, TI_ms),
    /* t4 = (d + r1) * r2' * R mod n */
    FUP_MC1_MMUL(TI_tmp4, TI_tmp1, TI_tmp2, TI_m),
    /* t1 = r2' * R mod n , in the range [1, n-1], becasue r2' != 0 mod n*/
    FUP_MC1_MRED(TI_tmp1, TI_tmp2, TI_m),
    /* t4 = (d + r1 + 1) * r2' * R mod n */
    FUP_MC1_MADD(TI_tmp4, TI_tmp1, TI_tmp4, TI_ms),
    /* t4 = (d + 1) * r2' * R mod n */
    FUP_MC1_MSUB(TI_tmp4, TI_tmp4, TI_tmp3, TI_ms),
    /* t2 = (d+1) * r2' mod n */
    FUP_MC1_MRED(TI_tmp2, TI_tmp4, TI_m),
    /* t2 is [0, n-1] */
    FUP_MC1_MSUB(TI_tmp2, TI_tmp2, TI_m, TI_m)
);
MCUXCLOSCCAPKC_FUP_EXT_ROM(mcuxClOsccaSm2_FUP_PointDouble,
    MCUXCLOSCCAPKC_CRC_ENTRY,
    FUP_MC1_MMUL(TI_t, TI_z1, TI_z, TI_modulus),        //Z1 = Z1'Z0
    FUP_MC1_MMUL(TI_s, TI_t, TI_t, TI_modulus),         //S = Z1^2
    FUP_MC1_MMUL(TI_t, TI_s, TI_s, TI_modulus),         //T = Z1^4
    FUP_MC1_MMUL(TI_s, TI_t, TI_a, TI_modulus),         //S = aZ1^4

    FUP_MC1_MMUL(TI_u, TI_xa, TI_xa, TI_modulus),       //U = X1^2
    FUP_MC1_MADD(TI_t, TI_u, TI_u, TI_moduluss),        //T = 2X1^2
    FUP_MC1_MADD(TI_v, TI_t, TI_u, TI_moduluss),        //V = 3X1^2
    FUP_MC1_MADD(TI_t, TI_v, TI_s, TI_moduluss),        //T= 3X1^2 + aZ1^4 = L
    FUP_MC1_MMUL(TI_v, TI_ya, TI_z1, TI_modulus),       //V = Y1Z1'
    FUP_MC1_MADD(TI_z1, TI_v, TI_v, TI_moduluss),       //Z1' = 2Y1Z1' = Z3'
    FUP_MC1_MMUL(TI_v, TI_ya, TI_ya, TI_modulus),       //V = Y1^2
    FUP_MC1_MADD(TI_ya, TI_v, TI_v, TI_moduluss),       //Y1 = 2Y1^2
    FUP_MC1_MMUL(TI_u, TI_xa, TI_ya, TI_modulus),       //U = 2X1Y1^2
    FUP_MC1_MADD(TI_v, TI_u, TI_u, TI_moduluss),        //V = 4X1Y1^2
    FUP_MC1_MMUL(TI_xa, TI_t, TI_t, TI_modulus),        //X1 = L^2
    FUP_MC1_MSUB(TI_u, TI_xa, TI_v, TI_moduluss),       //U = L^2 - 4X1Y1^2
    FUP_MC1_MSUB(TI_xa, TI_u, TI_v, TI_moduluss),       //X1 = L^2 - 8X1Y1^2 = X3
    FUP_MC1_MSUB(TI_u, TI_v, TI_xa, TI_moduluss),       //U = 4X1Y1^2 - X3
    FUP_MC1_MMUL(TI_v, TI_t, TI_u, TI_modulus),         //V = L(4X1Y1^2 - X3)
    FUP_MC1_MMUL(TI_u, TI_ya, TI_ya, TI_modulus),       //U = 4Y1^4
    FUP_MC1_MADD(TI_t, TI_u, TI_u, TI_moduluss),        //T = 8Y1^4
    FUP_MC1_MSUB(TI_ya, TI_v, TI_t, TI_moduluss)        //Y1 = L(4X1Y1^2 - X3) -8Y14 = Y3
);
MCUXCLOSCCAPKC_FUP_EXT_ROM(mcuxClOsccaSm2_FUP_PointAdd,
    MCUXCLOSCCAPKC_CRC_ENTRY,
    FUP_MC1_MMUL(TI_s, TI_z1, TI_z1, TI_modulus),       //S = Z1'^2
    FUP_MC1_MMUL(TI_t, TI_z1, TI_s, TI_modulus),        //T = Z1'^3
    FUP_MC1_MMUL(TI_u, TI_x0, TI_s, TI_modulus),        //U = X0*S = X2
    FUP_MC1_MMUL(TI_v, TI_y0, TI_t, TI_modulus),        //V = Y0*T = Y2

    FUP_MC1_MSUB(TI_t, TI_ya, TI_v, TI_moduluss),       //T=L=Y1-Y2
    FUP_MC1_MSUB(TI_v, TI_xa, TI_u, TI_moduluss),       //V = X1 - X2
    FUP_MC1_MMUL(TI_s, TI_z1, TI_v, TI_modulus),
    FUP_OP1_OR(TI_z1, TI_s, TI_s),                      //Z1' = (X1 - X2)Z1' = Z3'
    FUP_MC1_MMUL(TI_s, TI_v, TI_v, TI_modulus),
    FUP_MC1_MMUL(TI_v, TI_u, TI_s, TI_modulus),
    FUP_MC1_MMUL(TI_u, TI_xa, TI_s, TI_modulus),
    FUP_MC1_MMUL(TI_xa, TI_t, TI_t, TI_modulus),
    FUP_MC1_MSUB(TI_s, TI_xa, TI_v, TI_moduluss),
    FUP_MC1_MSUB(TI_xa, TI_s, TI_u, TI_moduluss),
    FUP_MC1_MSUB(TI_s, TI_u, TI_v, TI_moduluss),
    FUP_MC1_MMUL(TI_v, TI_ya, TI_s, TI_modulus),
    FUP_MC1_MSUB(TI_ya, TI_u, TI_xa, TI_moduluss),
    FUP_MC1_MMUL(TI_s, TI_ya, TI_t, TI_modulus),
    FUP_MC1_MSUB(TI_ya, TI_s, TI_v, TI_moduluss)        //Y1 = L(X1(X1-X2)^2 - X3)-Y1(X1-X2)^3 = Y3
);
MCUXCLOSCCAPKC_FUP_EXT_ROM(mcuxClOsccaSm2_FUP_PointCheckCoordinateX,
    MCUXCLOSCCAPKC_CRC_ENTRY,
    FUP_MC1_MMUL(TI_v, TI_z1, TI_z1, TI_modulus),       /* V = Z1'^2 */
    FUP_MC1_MMUL(TI_s, TI_x0, TI_v, TI_modulus),        /* S = X0 * Z1'^2 */
    FUP_MC1_MSUB(TI_u, TI_s, TI_xa, TI_moduluss),       /* U := X0 - XA fmod MODULUSS   */
    FUP_MC1_MRED(TI_t, TI_u, TI_modulus),               /* T := U fmod MODULUS          */
    FUP_MC1_MSUB(TI_u, TI_t, TI_modulus, TI_modulus)    /* U := T - MODULUS fmod MODULUS*/
);
MCUXCLOSCCAPKC_FUP_EXT_ROM(mcuxClOsccaSm2_FUP_PointCheckCoordinateY,
    MCUXCLOSCCAPKC_CRC_ENTRY,
    FUP_MC1_MMUL(TI_t, TI_v, TI_z1, TI_modulus),        /* T = Z1'^3 */
    FUP_MC1_MMUL(TI_s, TI_y0, TI_t, TI_modulus),        /* S = Y0 * Z1'^3 */
    FUP_MC1_MSUB(TI_u, TI_s, TI_ya, TI_moduluss),       /* U := Y0 - YA fmod MODULUSS   */
    FUP_MC1_MRED(TI_t, TI_u, TI_modulus),               /* T := U fmod MODULUS          */
    FUP_MC1_MSUB(TI_u, TI_t, TI_modulus, TI_modulus)    /* U := T - MODULUS fmod MODULUS*/
);
MCUXCLOSCCAPKC_FUP_EXT_ROM(mcuxClOsccaSm2_FUP_PointCheckCoordinateNegY,
    MCUXCLOSCCAPKC_CRC_ENTRY,
    FUP_MC1_MADD(TI_u, TI_s, TI_ya, TI_moduluss),       /* U := Y0 + YA fmod MODULUSS   */
    FUP_MC1_MRED(TI_t, TI_u, TI_modulus),               /* T := U fmod MODULUS          */
    FUP_MC1_MSUB(TI_u, TI_t, TI_modulus, TI_modulus)    /* U := T - MODULUS fmod MODULUS*/
);
MCUXCLOSCCAPKC_FUP_EXT_ROM(mcuxClOsccaSm2_FUP_EccTransAffinePoint2Jac,
    MCUXCLOSCCAPKC_CRC_ENTRY,
    /* Prepare S = Z^2 * R^2  and U = Z^3 * R^2  , TI_q2 is R^2*/
    FUP_MC1_MMUL(TI_u, TI_z, TI_z, TI_modulus),
    FUP_MC1_MMUL(TI_s, TI_u, TI_q2, TI_modulus),
    FUP_MC1_MMUL(TI_u, TI_z, TI_s, TI_modulus),

    FUP_OP1_OR(TI_v, TI_xa, TI_xa),
    /* X*Z^2*R */
    FUP_MC1_MMUL(TI_xa, TI_v, TI_s, TI_modulus),

    FUP_OP1_OR(TI_v, TI_ya, TI_ya),
    /* Y*Z^3*R */
    FUP_MC1_MMUL(TI_ya, TI_v, TI_u, TI_modulus)
);
MCUXCLOSCCAPKC_FUP_EXT_ROM(mcuxClOsccaSm2_FUP_JacPointCheck,
    MCUXCLOSCCAPKC_CRC_ENTRY,
    FUP_MC1_MMUL(TI_t, TI_z1, TI_z, TI_modulus),            //Z1 = Z1'Z0
    FUP_MC1_MMUL(TI_s, TI_t, TI_t, TI_modulus),             //S = Z1^2
    FUP_MC1_MMUL(TI_t, TI_s, TI_s, TI_modulus),             //T = Z1^4
    FUP_MC1_MMUL(TI_u, TI_t, TI_a, TI_modulus),             //U = aZ1^4
    FUP_MC1_MMUL(TI_v, TI_xa, TI_u, TI_modulus),            //V = aXZ^4

    FUP_MC1_MMUL(TI_u, TI_s, TI_t, TI_modulus),             //U = Z1^6
    FUP_MC1_MMUL(TI_t, TI_u, TI_b, TI_modulus),             //T = bZ1^6

    FUP_MC1_MADD(TI_u, TI_v, TI_t, TI_moduluss),            //U = aXZ^4 + bZ^6

    FUP_MC1_MMUL(TI_s, TI_xa, TI_xa, TI_modulus),
    FUP_MC1_MMUL(TI_t, TI_s, TI_xa, TI_modulus),            //T = X^3

    FUP_MC1_MADD(TI_v, TI_u, TI_t, TI_moduluss),            //V = X^3 + aXZ^4 + bZ^6

    FUP_MC1_MMUL(TI_u, TI_ya, TI_ya, TI_modulus),           //U = Y^2

    FUP_MC1_MSUB(TI_t, TI_u, TI_v, TI_moduluss),
    FUP_MC1_MRED(TI_u, TI_t, TI_modulus),
    FUP_MC1_MSUB(TI_t, TI_u, TI_modulus, TI_modulus)

);
MCUXCLOSCCAPKC_FUP_EXT_ROM(mcuxClOsccaSm2_FUP_CheckRPlusS,
    MCUXCLOSCCAPKC_CRC_ENTRY,
    FUP_MC1_MADD(TI_s, TI_scalar, TI_scalar1, TI_n),        /*s = R + S*/
    FUP_MC1_MSUB(TI_scalar, TI_s, TI_n, TI_n),              /*scalar in the range [0, n[*/
    FUP_MC1_MRED(TI_s, TI_scalar, TI_n),                    /*scalar * R^(-1)*/
    FUP_MC1_MSUB(TI_t, TI_s, TI_n, TI_n)                    /*scalar * R^(-1), in the range [0, n[ */
);
MCUXCLOSCCAPKC_FUP_EXT_ROM(mcuxClOsccaSm2_FUP_CheckSignature,
    MCUXCLOSCCAPKC_CRC_ENTRY,
    FUP_MC1_MADD(TI_s, TI_s, TI_xa, TI_n),
    FUP_MC1_MSUB(TI_v, TI_s, TI_u, TI_n),
    FUP_MC1_MRED(TI_s, TI_v, TI_n),
    FUP_MC1_MSUB(TI_v, TI_s, TI_n, TI_n)
);
MCUXCLOSCCAPKC_FUP_EXT_ROM(mcuxClOsccaSm2_FUP_Sign_Prepare_KD,
    MCUXCLOSCCAPKC_CRC_ENTRY,
    /* phi^-1, phi and k in MR */
    FUP_MC1_MMUL(TI_t, TI_k, TI_n2, TI_n),
    /* k' = k * phi^-1 */
    FUP_MC1_MMUL(TI_kDash, TI_t, TI_v, TI_n),

    /* phi1 in MR */
    FUP_MC1_MMUL(TI_phi1, TI_u, TI_n2, TI_n),
    /* d' = d + phi1 */
    FUP_MC1_MADD(TI_s, TI_d, TI_u, TI_nshift),
    /* d' in MR */
    FUP_MC1_MMUL(TI_dDash, TI_s, TI_n2, TI_n)
);
MCUXCLOSCCAPKC_FUP_EXT_ROM(mcuxClOsccaSm2_FUP_Sign_RPlusK,
    MCUXCLOSCCAPKC_CRC_ENTRY,
    /* phi in MR */
    FUP_MC1_MMUL(TI_phi, TI_t, TI_n2, TI_n),
    /* r * phi */
    FUP_MC1_MMUL(TI_u, TI_v, TI_phi, TI_n),
    /* k * phi */
    FUP_MC1_MMUL(TI_v, TI_t, TI_phi, TI_n),
    /* r * phi + k * phi */
    FUP_MC1_MADD(TI_s, TI_v, TI_u, TI_nshift),
    FUP_MC1_MRED(TI_t, TI_s, TI_n),
    FUP_MC1_MSUB(TI_t, TI_t, TI_n, TI_n)       /* k + sig_r, in the range [0, n[ */
);
MCUXCLOSCCAPKC_FUP_EXT_ROM(mcuxClOsccaSm2_FUP_Sign_Check_r,
    MCUXCLOSCCAPKC_CRC_ENTRY,
    FUP_MC1_MADD(TI_t, TI_e, TI_kGx, TI_nshift),        /* add e to kG.x */
    FUP_MC1_MMUL(TI_s, TI_t, TI_n2, TI_n),              /* convert (e + kG.x) to MR */
    FUP_MC1_MRED(TI_t, TI_s, TI_n),
    FUP_MC1_MSUB(TI_sig_r, TI_t, TI_n, TI_n)            /* sig_r = (e + kG.x) mod n, in the range [0, n[ */
);
MCUXCLOSCCAPKC_FUP_EXT_ROM(mcuxClOsccaSm2_FUP_Sign_Double_Check_r,
    MCUXCLOSCCAPKC_CRC_ENTRY,
    FUP_MC1_MADD(TI_t, TI_e, TI_kGx, TI_nshift),        /* add e to kG.x */
    FUP_MC1_MMUL(TI_s, TI_t, TI_n2, TI_n),              /* convert (e + kG.x) to MR */
    FUP_MC1_MRED(TI_t, TI_s, TI_n),
    FUP_MC1_MSUB(TI_s, TI_t, TI_n, TI_n),               /* sig_r = (e + kG.x) mod n, in the range [0, n[ */
    FUP_OP1_SUB(TI_s, TI_s, TI_sig_r)                   /* compare t1 and sig_r */
);
MCUXCLOSCCAPKC_FUP_EXT_ROM(mcuxClOsccaSm2_FUP_Sign_Compute_s,
    /* Compute s = (d+1)^{-1} (k-r*d) */
    MCUXCLOSCCAPKC_CRC_ENTRY,
    /* phi2 in MR */
    FUP_MC1_MMUL(TI_phi2, TI_t, TI_n2, TI_n),
    /* d_inv' = d_inv + phi2 */
    FUP_MC1_MADD(TI_s, TI_d_inv, TI_t, TI_nshift),
    /* d_inv' in MR */
    FUP_MC1_MMUL(TI_T, TI_s, TI_n2, TI_n),

    /* sig_r in MR */
    FUP_MC1_MMUL(TI_R, TI_sig_r, TI_n2, TI_n),

    /* k' + phi2 */
    FUP_MC1_MADD(TI_s, TI_kDash, TI_phi2, TI_nshift),
    /* (k' + phi2) * phi */
    FUP_MC1_MMUL(TI_t, TI_s, TI_phi, TI_n),
    /* phi2 * phi */
    FUP_MC1_MMUL(TI_u, TI_phi, TI_phi2, TI_n),
    /* d' * r */
    FUP_MC1_MMUL(TI_v, TI_dDash, TI_R, TI_n),
    /* A =  (k' + phi2) * phi - phi2 * phi - d' * r */
    FUP_MC1_MSUB(TI_s, TI_t, TI_u, TI_nshift),
    FUP_MC1_MSUB(TI_A, TI_s, TI_v, TI_nshift),

    /* T * A */
    FUP_MC1_MMUL(TI_t, TI_A, TI_T, TI_n),
    /* A * phi2 */
    FUP_MC1_MMUL(TI_s, TI_A, TI_phi2, TI_n),
    /*  T * A -  A * phi2 */
    FUP_MC1_MSUB(TI_u, TI_t, TI_s, TI_nshift),

    /* r * phi1 * T */
    FUP_MC1_MMUL(TI_v, TI_R, TI_phi1, TI_n),
    FUP_MC1_MMUL(TI_s, TI_v, TI_T, TI_n),
    /*  T * A -  A * phi2 + r * phi1 * T */
    FUP_MC1_MADD(TI_t, TI_u, TI_s, TI_nshift),

    /* r * phi1 * phi2 */
    FUP_MC1_MMUL(TI_v, TI_R, TI_phi1, TI_n),
    FUP_MC1_MMUL(TI_s, TI_v, TI_phi2, TI_n),
    /* T * A -  A * phi2 + r * phi1 * T -  r * phi1 * phi2 */
    FUP_MC1_MSUB(TI_u, TI_t, TI_s, TI_nshift),
    FUP_MC1_MRED(TI_sig_s, TI_u, TI_n),
    FUP_MC1_MSUB(TI_sig_s, TI_sig_s, TI_n, TI_n)
);
MCUXCLOSCCAPKC_FUP_EXT_ROM(mcuxClOsccaSm2_FUP_UpdateZ,
    MCUXCLOSCCAPKC_CRC_ENTRY,
    FUP_OP1_OR(TI_sx1, TI_xa, TI_const0),
    FUP_OP1_OR(TI_sy1, TI_ya, TI_const0),
    FUP_MC1_MSUB(TI_y_neg, TI_modulus, TI_ya, TI_moduluss),
    FUP_MC1_MMUL(TI_t, TI_z1, TI_z, TI_modulus),
    FUP_OP1_OR(TI_z, TI_t, TI_const0)
);
MCUXCLOSCCAPKC_FUP_EXT_ROM(mcuxClOsccaSm2_FUP_EccPointMultMontgomery_InitPoints,
    MCUXCLOSCCAPKC_CRC_ENTRY,
    FUP_OP1_XOR(TI_sx0, TI_const0, TI_const0),
    FUP_OP1_XOR(TI_sy0, TI_const0, TI_const0),
    FUP_OP1_XOR(TI_sz0_dash, TI_const0, TI_const0),

    FUP_OP1_OR(TI_sx, TI_sx1, TI_const0),
    FUP_OP1_OR(TI_sy, TI_sy1, TI_const0),
    FUP_OP1_NEG(TI_sz1_dash, TI_modulus)
);
MCUXCLOSCCAPKC_FUP_EXT_ROM(mcuxClOsccaSm2_FUP_EccPointMultMontgomery_CopyP1P0,
    MCUXCLOSCCAPKC_CRC_ENTRY,
    FUP_OP1_OR(TI_sx1, TI_sx0, TI_const0),
    FUP_OP1_OR(TI_sy1, TI_sy0, TI_const0),
    FUP_OP1_OR(TI_sz1_dash, TI_sz0_dash, TI_const0)
);
MCUXCLOSCCAPKC_FUP_EXT_ROM(mcuxClOsccaSm2_FUP_EccPointMultMontgomery_CopyP0P1,
    MCUXCLOSCCAPKC_CRC_ENTRY,
    FUP_OP1_OR(TI_sx0, TI_sx1, TI_const0),
    FUP_OP1_OR(TI_sy0, TI_sy1, TI_const0),
    FUP_OP1_OR(TI_sz0_dash, TI_sz1_dash, TI_const0)
);
MCUXCLOSCCAPKC_FUP_EXT_ROM(mcuxClOsccaSm2_FUP_EccPointConvert2Affine_PrepareZ3,
    MCUXCLOSCCAPKC_CRC_ENTRY,
    /* t = Z1'Z0 in MR */
    FUP_MC1_MMUL(TI_t, TI_z1, TI_z, TI_modulus),
    /* z3 in MR */
    FUP_OP1_OR(TI_z1, TI_t, TI_const0),
    /* z3 ^ 2 in MR*/
    FUP_MC1_MMUL(TI_v, TI_t, TI_t, TI_modulus),
    /* z3 ^ 2 in NR */
    FUP_MC1_MRED(TI_u, TI_v, TI_modulus)
);
MCUXCLOSCCAPKC_FUP_EXT_ROM(mcuxClOsccaSm2_FUP_EccImportInputPointInputPointWithInit_PrepareZ23,
    MCUXCLOSCCAPKC_CRC_ENTRY,
    /* Prepare S = Z^2 * R^2  and U = Z^3 * R^2  , _q2 is R^2*/
    FUP_MC1_MMUL(TI_u, TI_z, TI_z, TI_modulus),
    FUP_MC1_MMUL(TI_s, TI_u, TI_q2, TI_modulus),
    FUP_MC1_MMUL(TI_u, TI_z, TI_s, TI_modulus)
);
MCUXCLOSCCAPKC_FUP_EXT_ROM(mcuxClOsccaSm2_FUP_KeyExchgCalcTa,
    MCUXCLOSCCAPKC_CRC_ENTRY,
    FUP_MC1_MADD(TI_t, TI_t, TI_u, TI_n),
    FUP_MC1_MMUL(TI_scalar1, TI_scalar, TI_n2, TI_n),
    FUP_MC1_MSUB(TI_scalar, TI_scalar1, TI_n, TI_n),
    FUP_MC1_MMUL(TI_scalar1, TI_scalar, TI_u, TI_n),
    FUP_MC1_MSUB(TI_u, TI_scalar1, TI_n, TI_n),
    FUP_MC1_MMUL(TI_scalar1, TI_scalar, TI_t, TI_n),
    FUP_MC1_MADD(TI_s, TI_s, TI_scalar1, TI_n),
    FUP_MC1_MSUB(TI_s, TI_s, TI_n, TI_n),
    FUP_MC1_MSUB(TI_s, TI_s, TI_n, TI_n),
    FUP_MC1_MSUB(TI_scalar, TI_s, TI_u, TI_n)
);
