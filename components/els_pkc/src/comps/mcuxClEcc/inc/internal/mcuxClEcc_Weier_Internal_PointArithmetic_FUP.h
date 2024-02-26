/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021 NXP                                                  */
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
 * @file  mcuxClEcc_Weier_Internal_PointArithmetic_FUP.h
 * @brief defines FUP programs byte arrays
 */


#ifndef MCUXCLECC_WEIER_INTERNAL_POINTARITHMETIC_FUP_H_
#define MCUXCLECC_WEIER_INTERNAL_POINTARITHMETIC_FUP_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <internal/mcuxClPkc_FupMacros.h>


/**
 * FUP program declaration mcuxClEcc_FUP_Weier_DoubleAdd
 */
#define mcuxClEcc_FUP_Weier_DoubleAdd_Len1   5u
#define mcuxClEcc_FUP_Weier_DoubleAdd_Len2  15u
#define mcuxClEcc_FUP_Weier_DoubleAdd_Len   (mcuxClEcc_FUP_Weier_DoubleAdd_Len1 + mcuxClEcc_FUP_Weier_DoubleAdd_Len2)
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_DoubleAdd[mcuxClEcc_FUP_Weier_DoubleAdd_Len];

#define MCUXCLECC_FP_CALCFUP_ADD_ONLY()  \
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_Weier_DoubleAdd, mcuxClEcc_FUP_Weier_DoubleAdd_Len)
#define MCUXCLECC_FP_CALLED_CALCFUP_ADD_ONLY  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)

#define MCUXCLECC_FP_CALCFUP_DOUBLE_ADD()  \
    do{  \
        MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_Weier_DoubleAdd, mcuxClEcc_FUP_Weier_DoubleAdd_Len);  \
        MCUXCLPKC_FP_CALCFUP_OFFSET(mcuxClEcc_FUP_Weier_DoubleAdd, mcuxClEcc_FUP_Weier_DoubleAdd_Len1,  \
                                   mcuxClEcc_FUP_Weier_DoubleAdd_Len2);  \
    } while (false)
#define MCUXCLECC_FP_CALLED_CALCFUP_DOUBLE_ADD  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)

/**
 * FUP program declaration mcuxClEcc_FUP_Weier_RepeatDouble
 */
#define mcuxClEcc_FUP_Weier_RepeatDouble_Len1  5u
#define mcuxClEcc_FUP_Weier_RepeatDouble_Len2  16u
#define mcuxClEcc_FUP_Weier_RepeatDouble_Len3  3u
#define mcuxClEcc_FUP_Weier_RepeatDouble_Len   (mcuxClEcc_FUP_Weier_RepeatDouble_Len1 + mcuxClEcc_FUP_Weier_RepeatDouble_Len2 + mcuxClEcc_FUP_Weier_RepeatDouble_Len3)
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_RepeatDouble[mcuxClEcc_FUP_Weier_RepeatDouble_Len];

#define MCUXCLECC_FP_CALCFUP_ONE_DOUBLE()  \
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_Weier_RepeatDouble,  \
                        mcuxClEcc_FUP_Weier_RepeatDouble_Len1 + mcuxClEcc_FUP_Weier_RepeatDouble_Len2)
#define MCUXCLECC_FP_CALLED_CALCFUP_ONE_DOUBLE  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)


#endif /* MCUXCLECC_WEIER_INTERNAL_POINTARITHMETIC_FUP_H_ */
