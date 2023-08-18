/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021, 2023 NXP                                            */
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

/** @file  mcuxClEcc_Weier_Internal_ConvertPoint_FUP.h
*  @brief defines FUP programs byte arrays
*/
#ifndef MCUXCLECC_WEIER_INTERNAL_CONVERTPOINT_FUP_H_
#define MCUXCLECC_WEIER_INTERNAL_CONVERTPOINT_FUP_H_
#include <internal/mcuxClPkc_FupMacros.h>

extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_ConvertAffinePoint_ToJacobian[5];
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_ConvertAffinePointsToJac[7];
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_ConvertJacToAffine[10];
extern const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_ConvertPoint_ToAffine[11];

#endif /* MCUXCLECC_WEIER_INTERNAL_CONVERTPOINT_FUP*/ 
