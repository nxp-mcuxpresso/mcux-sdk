/*--------------------------------------------------------------------------*/
/* Copyright 2022-2023 NXP                                                  */
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
 * @file  mcuxClKey_DerivationAlgorithms.h
 * @brief Supported algorithms for key derivation
 */

#ifndef MCUXCLKEY_DERIVATIONALGORITHMS_H_
#define MCUXCLKEY_DERIVATIONALGORITHMS_H_

#include <mcuxClConfig.h> // Exported features flags header

#ifdef MCUXCL_FEATURE_KEY_DERIVATION_NIST_SP800_108
#include <mcuxClKey_DerivationAlgorithms_NIST_SP800_108.h>
#endif
#ifdef MCUXCL_FEATURE_KEY_DERIVATION_NIST_SP800_56C
#include <mcuxClKey_DerivationAlgorithms_NIST_SP800_56C.h>
#endif
#ifdef MCUXCL_FEATURE_KEY_DERIVATION_HKDF
#include <mcuxClKey_DerivationAlgorithms_HKDF.h>
#endif
#ifdef MCUXCL_FEATURE_KEY_DERIVATION_PBKDF2
#include <mcuxClKey_DerivationAlgorithms_PBKDF2.h>
#endif

#endif /* MCUXCLKEY_DERIVATIONALGORITHMS_H_ */
