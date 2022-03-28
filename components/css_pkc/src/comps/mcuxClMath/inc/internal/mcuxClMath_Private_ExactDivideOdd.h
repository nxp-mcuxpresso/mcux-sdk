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
 * @file  mcuxClMath_Private_ExactDivideOdd.h
 * @brief mcuxClMath: private header of exact divide with odd divisor
 */


#ifndef MCUXCLMATH_PRIVATE_EXACTDIVIDEODD_H_
#define MCUXCLMATH_PRIVATE_EXACTDIVIDEODD_H_


#include <stdint.h>
#include <stdbool.h>

#include <mcuxCsslFlowProtection.h>
#include <internal/mcuxClPkc_FupMacros.h>
#include <mcuxClMath_Types.h>

#include <mcuxClMath_ExactDivideOdd_FUP.h>


/**********************************************************/
/* Indices of operands in PKC workarea and UPTR table     */
/**********************************************************/
#define DivOdd_T   0u
#define DivOdd_Y   1u
#define DivOdd_X   2u
#define DivOdd_R   3u
#define DivOdd_T1  4u
#define DivOdd_Ri  5u
#define DivOdd_Xa  6u
#define DivOdd_Xb  7u
#define DivOdd_UPTRT_SIZE  8u


/**********************************************************/
/* FUP program declaration                                */
/**********************************************************/
//MCUXCLPKC_FUP_EXT_ROM_DECLARE(mcuxClMath_Fup_ExactDivideOdd_NDashY);
#define mcuxClMath_Fup_ExactDivideOdd_NDashY_LEN  4u    

//MCUXCLPKC_FUP_EXT_ROM_DECLARE(mcuxClMath_Fup_ExactDivideOdd_DivideLoop);
#define mcuxClMath_Fup_ExactDivideOdd_DivideLoop_LEN  5u    


#endif /* MCUXCLMATH_PRIVATE_EXACTDIVIDEODD_H_ */
