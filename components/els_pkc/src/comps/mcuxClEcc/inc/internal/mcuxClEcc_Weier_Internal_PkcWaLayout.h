/*--------------------------------------------------------------------------*/
/* Copyright 2020-2023 NXP                                                  */
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
 * @file  mcuxClEcc_Weier_Internal_PkcWaLayout.h
 * @brief internal header for short Weierstrass curves
 */


#ifndef MCUXCLECC_WEIER_INTERNAL_PKCWALAYOUT_H_
#define MCUXCLECC_WEIER_INTERNAL_PKCWALAYOUT_H_


#include <mcuxClConfig.h> // Exported features flags header

#include <internal/mcuxClEcc_Internal_PkcWaLayout.h>

#ifdef __cplusplus
extern "C" {
#endif


/**********************************************************/
/** PKC workarea memory layout for Weierstrass functions. */
/**********************************************************/
#define WEIER_VX0  ECC_V0
#define WEIER_VY0  ECC_V1
#define WEIER_VZ0  ECC_V2
#define WEIER_VZ   ECC_V3

#define WEIER_VX1  ECC_V4
#define WEIER_VY1  ECC_V5
#define WEIER_VT2  ECC_V6
#define WEIER_VT3  ECC_V7

#define WEIER_VX2  ECC_V8
#define WEIER_VY2  ECC_V9
#define WEIER_VZ2  ECC_VA
#define WEIER_VT   ECC_VB

#define WEIER_A    ECC_CP0
#define WEIER_B    ECC_CP1

#define WEIER_XA  ECC_COORD00
#define WEIER_YA  ECC_COORD01
#define WEIER_ZA  ECC_COORD02
#define WEIER_Z   ECC_COORD03
#define WEIER_X0  ECC_COORD04
#define WEIER_Y0  ECC_COORD05
#define WEIER_X1  ECC_COORD06
#define WEIER_Y1  ECC_COORD07
#define WEIER_X2  ECC_COORD08
#define WEIER_Y2  ECC_COORD09
#define WEIER_X3  ECC_COORD10
#define WEIER_Y3  ECC_COORD11

#define ECC_KEYGEN_NO_OF_VIRTUALS     ECC_NO_OF_VIRTUALS
#define ECC_KEYGEN_NO_OF_BUFFERS      (WEIER_Y1 + 1u - ECC_KEYGEN_NO_OF_VIRTUALS)

#define ECC_SIGN_NO_OF_VIRTUALS       ECC_NO_OF_VIRTUALS
#define ECC_SIGN_NO_OF_BUFFERS        (WEIER_Y1 + 1u - ECC_SIGN_NO_OF_VIRTUALS)

#define ECC_VERIFY_NO_OF_VIRTUALS     ECC_NO_OF_VIRTUALS
#define ECC_VERIFY_NO_OF_BUFFERS      (WEIER_Y3 + 1u - ECC_VERIFY_NO_OF_VIRTUALS)

#define ECC_POINTMULT_NO_OF_VIRTUALS  ECC_NO_OF_VIRTUALS
#define ECC_POINTMULT_NO_OF_BUFFERS   (WEIER_Y1 + 1u - ECC_POINTMULT_NO_OF_VIRTUALS)







#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLECC_WEIER_INTERNAL_PKCWALAYOUT_H_ */
