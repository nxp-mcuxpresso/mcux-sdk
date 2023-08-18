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

/**
 * @file  mcuxClMath_Internal_ModInv.h
 * @brief mcuxClMath: internal header of modular inverse
 */


#ifndef MCUXCLMATH_INTERNAL_MODINV_H_
#define MCUXCLMATH_INTERNAL_MODINV_H_

#include <mcuxClCore_Platform.h>


/**********************************************************/
/* Indices of operands in PKC workarea and UPTR table     */
/**********************************************************/
#define MODINV_T   0u
#define MODINV_N   1u
#define MODINV_X   2u
#define MODINV_R   3u
#define MODINV_T1  4u
#define MODINV_CONST1  5u
#define MODINV_CONST0  6u
#define MODINV_UPTRT_SIZE  7u


#endif /* MCUXCLMATH_INTERNAL_MODINV_H_ */
