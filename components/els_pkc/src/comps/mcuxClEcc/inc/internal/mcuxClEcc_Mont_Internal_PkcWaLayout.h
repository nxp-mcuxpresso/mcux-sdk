/*--------------------------------------------------------------------------*/
/* Copyright 2021-2022 NXP                                                  */
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
 * @file  mcuxClEcc_Mont_Internal_PkcWaLayout.h
 * @brief internal header of mcuxClEcc MontDh PKC workarea layout
 */


#ifndef MCUXCLECC_MONT_INTERNAL_PKCWALAYOUT_H_
#define MCUXCLECC_MONT_INTERNAL_PKCWALAYOUT_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <internal/mcuxClEcc_Internal.h>


/**********************************************************/
/** PKC workarea memory layout used for MontDh functions. */
/**********************************************************/
#define MONT_V0   ECC_V0
#define MONT_V1   ECC_V1
#define MONT_V2   ECC_V2
#define MONT_V3   ECC_V3
#define MONT_V4   ECC_V4
#define MONT_V5   ECC_V5
#define MONT_V6   ECC_V6
#define MONT_V7   ECC_V7

#define MONT_VX1  ECC_V8
#define MONT_VZ1  ECC_V9
#define MONT_VX2  ECC_VA
#define MONT_VZ2  ECC_VB

#define MONT_X0   ECC_COORD00
#define MONT_Z0   ECC_COORD01
#define MONT_X1   ECC_COORD02
#define MONT_Z1   ECC_COORD03
#define MONT_X2   ECC_COORD04
#define MONT_Z2   ECC_COORD05

/* Virtual and real buffer amounts definition for Mont functions */
#define ECC_MONTDH_NO_OF_VIRTUALS  ECC_NO_OF_VIRTUALS
#define ECC_MONTDH_NO_OF_BUFFERS   (MONT_Z2 + 1u - ECC_MONTDH_NO_OF_VIRTUALS)


#endif /* MCUXCLECC_MONT_INTERNAL_PKCWALAYOUT_H_ */
