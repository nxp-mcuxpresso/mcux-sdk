/*--------------------------------------------------------------------------*/
/* Copyright 2020 NXP                                                       */
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

/** @file  mcuxClEcc_Internal_NIST.h
 *  @brief Internal definitions supporting only NIST curves
 */

#include <mcuxClEcc_NIST_FUP.h>

#ifndef MCUXCLECC_INTERNAL_NIST_H_
#define MCUXCLECC_INTERNAL_NIST_H_

#define ECC_VERIFY_P384_NO_OF_BUFFERS   0x1Au
#define ECC_VERIFY_P384_NO_OF_VIRTUALS  0x12u

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_RepeatPointDouble_NIST)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_RepeatPointDouble_NIST(uint32_t iteration);

#define MCUXCLECC_FP_REPEATPOINTDOUBLE_NIST(iteration)  \
    do{ \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClEcc_RepeatPointDouble_NIST(iteration));  \
        (void) retValTemp;    \
    } while (false)

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_Int_PointMult_NIST)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_Int_PointMult_NIST(uint8_t iScalar, uint32_t scalarBitLen);

#define MCUXCLECC_FP_INT_POINTMULT_NIST(iScalar, scalarBitLen)  \
    do{ \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClEcc_Int_PointMult_NIST(iScalar, scalarBitLen));  \
        (void) retValTemp;    \
    } while (false)

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_PointCheckAffineNR_NIST)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_PointCheckAffineNR_NIST(void);

#define MCUXCLECC_FP_POINTCHECKAFFINENR_NIST()  \
    ({ \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClEcc_PointCheckAffineNR_NIST());  \
        (retValTemp);  \
    })

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_PointFullAdd_NIST)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_PointFullAdd_NIST(void);

#define MCUXCLECC_FP_POINTFULLADD_NIST()  \
    ({ \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClEcc_PointFullAdd_NIST());  \
        (retValTemp);  \
    })

#define mcuxClEcc_Fup_RepeatDouble_NIST_Len1  3u
#define mcuxClEcc_Fup_RepeatDouble_NIST_Len2  18u
#define mcuxClEcc_Fup_RepeatDouble_NIST_Len3  3u
#define mcuxClEcc_Fup_RepeatDouble_NIST_Len   24u

#define MCUXCLECC_FP_CALCFUP_ONE_DOUBLE_NIST()  \
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_RepeatDouble_NIST,  \
                        mcuxClEcc_Fup_RepeatDouble_NIST_Len1  \
                        + mcuxClEcc_Fup_RepeatDouble_NIST_Len2)
#define MCUXCLECC_FP_CALLED_CALCFUP_ONE_DOUBLE_NIST  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)

#define mcuxClEcc_Fup_PointCheckAffNR_NIST_Len  11u

#endif
