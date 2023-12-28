/*--------------------------------------------------------------------------*/
/* Copyright 2023 NXP                                                       */
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
 * @file:  mcuxClRsa_Internal_PkcTypes.h
 * @brief: Redefinition of types related to PKC.
 *
 */

#ifndef MCUXCLRSA_INTERNAL_PKCTYPES_H_
#define MCUXCLRSA_INTERNAL_PKCTYPES_H_

#include <mcuxClCore_Platform.h>
#include <mcuxCsslFlowProtection.h>


#ifdef __cplusplus
extern "C"
{
#endif


#include <mcuxClPkc_Types.h>
/** @brief PKC wordsize in byte */
#define MCUXCLRSA_PKC_WORDSIZE MCUXCLPKC_WORDSIZE
/** @brief Round-up a length to a multiple of PKC wordsize. */
#define MCUXCLRSA_PKC_ROUNDUP_SIZE(byteLen) MCUXCLPKC_ROUNDUP_SIZE(byteLen)


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLRSA_INTERNAL_PKCTYPES_H_ */
