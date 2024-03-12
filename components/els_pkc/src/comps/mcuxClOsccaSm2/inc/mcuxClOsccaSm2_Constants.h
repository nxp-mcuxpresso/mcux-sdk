/*--------------------------------------------------------------------------*/
/* Copyright 2016, 2021-2023 NXP                                            */
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
 *
 * @file:    mcuxClOsccaSm2_Constants.h
 * @brief:   Platform related definitions for the OSCCA SM2 component
 *
 */

#ifndef MCUXCLOSCCASM2_CONSTANTS_H_
#define MCUXCLOSCCASM2_CONSTANTS_H_

#include <mcuxClOscca_Types.h>
#include <mcuxClOscca_Memory.h>
#include <mcuxClOsccaSm2_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MCUXCL_FEATURE_SM2_KEYAGREEMENT
/************************************************************************************************/
/** @brief Definition of some constant used by additional inputs for SM2 key agreement through internal call */
/************************************************************************************************/
#define MCUXCLOSCCASM2_KEYAGREEMENT_NUM_OF_ADDITIONAL_INPUTS         7u
#define MCUXCLOSCCASM2_KEYAGREEMENT_PREHASH_INITIATOR                0u
#define MCUXCLOSCCASM2_KEYAGREEMENT_PREHASH_RESPONDER                1u
#define MCUXCLOSCCASM2_KEYAGREEMENT_PRIVATEEPHEMERALKEY              2u
#define MCUXCLOSCCASM2_KEYAGREEMENT_PUBLICEPHEMERALPOINT             3u
#define MCUXCLOSCCASM2_KEYAGREEMENT_PUBLICEPHEMERALPOINT_PARTY2      4u
#define MCUXCLOSCCASM2_KEYAGREEMENT_CONFIRMATION_R2I                 5u
#define MCUXCLOSCCASM2_KEYAGREEMENT_CONFIRMATION_I2R                 6u
#endif /* MCUXCL_FEATURE_SM2_KEYAGREEMENT */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLOSCCASM2_CONSTANTS_H_ */
