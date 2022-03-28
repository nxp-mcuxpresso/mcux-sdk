/*--------------------------------------------------------------------------*/
/* Copyright 2021 NXP                                                       */
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
 * @file  mcuxClMath_FUP_programs.h
 * @brief mcuxClMath: private header of secure modular exponentiation
 */


#ifndef MCUXCLMATH_FUP_PROGRAMS_H_
#define MCUXCLMATH_FUP_PROGRAMS_H_


#include <mcuxClMath_ModInv_FUP.h>
#include <mcuxClMath_NDash_FUP.h>
#include <mcuxClMath_QDash_FUP.h>


#define MODINV_T   0u
#define MODINV_N   1u
#define MODINV_X   2u
#define MODINV_R   3u
#define MODINV_T1  4u
#define MODINV_CONST1  5u
#define MODINV_UPTRT_SIZE  6u

#define NDASH_T      0u
#define NDASH_N      1u
#define NDASH_NDASH  2u
#define NDASH_C2     3u
#define NDASH_UPTRT_SIZE  4u

#define QDASH_T      0u
#define QDASH_N      1u
#define QDASH_NS     2u
#define QDASH_QDASH  3u
#define QDASH_UPTRT_SIZE  4u

//MCUXCLPKC_FUP_EXT_ROM_DECLARE(mcuxClMath_ModInv_Fup1);
#define mcuxClMath_ModInv_Fup1_LEN  7u  

//MCUXCLPKC_FUP_EXT_ROM_DECLARE(mcuxClMath_ModInv_Fup3a);
//MCUXCLPKC_FUP_EXT_ROM_DECLARE(mcuxClMath_ModInv_Fup3b);
#define mcuxClMath_ModInv_Fup3_LEN 3u  

//MCUXCLPKC_FUP_EXT_ROM_DECLARE(mcuxClMath_NDash_Fup);
#define mcuxClMath_NDash_Fup_LEN  5u  

//MCUXCLPKC_FUP_EXT_ROM_DECLARE(mcuxClMath_QDash_Fup_Init);
#define mcuxClMath_QDash_Fup_Init_LEN  3u  

//MCUXCLPKC_FUP_EXT_ROM_DECLARE(mcuxClMath_QDash_Fup_Loop0);
#define mcuxClMath_QDash_Fup_Loop0_LEN  3u  

//MCUXCLPKC_FUP_EXT_ROM_DECLARE(mcuxClMath_QDash_Fup_Loop1);
#define mcuxClMath_QDash_Fup_Loop1_LEN  3u  



#endif /* MCUXCLMATH_FUP_PROGRAMS_H_ */
