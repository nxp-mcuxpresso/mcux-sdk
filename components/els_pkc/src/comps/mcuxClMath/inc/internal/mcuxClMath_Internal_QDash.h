/*--------------------------------------------------------------------------*/
/* Copyright 2021-2023 NXP                                                  */
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
 * @file  mcuxClMath_Internal_QDash.h
 * @brief mcuxClMath: internal header of mcuxClMath_QDash
 */


#ifndef MCUXCLMATH_INTERNAL_QDASH_H_
#define MCUXCLMATH_INTERNAL_QDASH_H_

#include <mcuxClCore_Platform.h>


/**********************************************************/
/* Indices of operands in PKC workarea and UPTR table     */
/**********************************************************/
#define QDASH_T      0u
#define QDASH_N      1u
#define QDASH_NS     2u
#define QDASH_QDASH  3u
#define QDASH_CONST0 4u
#define QDASH_UPTRT_SIZE  5u

#endif /* MCUXCLMATH_INTERNAL_QDASH_H_ */
