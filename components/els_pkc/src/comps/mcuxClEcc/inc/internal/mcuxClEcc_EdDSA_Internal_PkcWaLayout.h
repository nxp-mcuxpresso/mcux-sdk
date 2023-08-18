/*--------------------------------------------------------------------------*/
/* Copyright 2022 NXP                                                       */
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
 * @file  mcuxClEcc_EdDSA_Internal_PkcWaLayout.h
 * @brief internal header of mcuxClEcc TwEd PKC workarea layout
 */


#ifndef MCUXCLECC_EDDSA_INTERNAL_PKCWALAYOUT_H_
#define MCUXCLECC_EDDSA_INTERNAL_PKCWALAYOUT_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <internal/mcuxClEcc_Internal.h>

/**********************************************************/
/** PKC workarea memory layout used for TwEd functions.   */
/**********************************************************/
#define TWED_V0      ECC_V0
#define TWED_V1      ECC_V1
#define TWED_V2      ECC_V2
#define TWED_V3      ECC_V3
#define TWED_V4      ECC_V4
#define TWED_V5      ECC_V5
#define TWED_PP_VX1  ECC_V6
#define TWED_PP_VY1  ECC_V7
#define TWED_PP_VT1  ECC_V8
#define TWED_PP_VX0  ECC_V9
#define TWED_PP_VY0  ECC_VA
#define TWED_PP_VT0  ECC_VB

#define TWED_VY1     ECC_V8
#define TWED_VZ1     ECC_V9
#define TWED_VY2     ECC_VA
#define TWED_VZ2     ECC_VB

#define TWED_X       ECC_COORD00
#define TWED_Y       ECC_COORD01
#define TWED_Z       ECC_COORD02
#define TWED_T       ECC_COORD03

#define TWED_ML_Y1   ECC_COORD04
#define TWED_ML_Z1   ECC_COORD05
#define TWED_ML_Y2   ECC_COORD06
#define TWED_ML_Z2   ECC_COORD07

#define TWED_PP_X0   ECC_COORD04
#define TWED_PP_Y0   ECC_COORD05
#define TWED_PP_T0   ECC_COORD06
#define TWED_PP_X1   ECC_COORD07
#define TWED_PP_Y1   ECC_COORD08
#define TWED_PP_T1   ECC_COORD09
#define TWED_PP_X2   ECC_COORD10
#define TWED_PP_Y2   ECC_COORD11
#define TWED_PP_T2   ECC_COORD12
#define TWED_PP_X3   ECC_COORD13
#define TWED_PP_Y3   ECC_COORD14
#define TWED_PP_T3   ECC_COORD15
#define TWED_PP_X4   ECC_COORD16
#define TWED_PP_Y4   ECC_COORD17
#define TWED_PP_T4   ECC_COORD18
#define TWED_PP_X5   ECC_COORD19
#define TWED_PP_Y5   ECC_COORD20
#define TWED_PP_T5   ECC_COORD21
#define TWED_PP_X6   ECC_COORD22
#define TWED_PP_Y6   ECC_COORD23
#define TWED_PP_T6   ECC_COORD24
#define TWED_PP_X7   ECC_COORD25
#define TWED_PP_Y7   ECC_COORD26
#define TWED_PP_T7   ECC_COORD27


/* Virtual and real buffer amounts definition for EdDSA functions */
#define ECC_EDDSA_NO_OF_VIRTUALS  (ECC_NO_OF_VIRTUALS)
#define ECC_EDDSA_NO_OF_BUFFERS   (TWED_PP_T7 + 1u - ECC_EDDSA_NO_OF_VIRTUALS)


#endif /* MCUXCLECC_EDDSA_INTERNAL_PKCWALAYOUT_H_ */
