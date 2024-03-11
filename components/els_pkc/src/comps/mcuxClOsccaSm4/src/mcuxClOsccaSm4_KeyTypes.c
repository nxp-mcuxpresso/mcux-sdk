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

/** @file  mcuxClOsccaSm4_KeyTypes.c
 *  @brief Instantiation of the key types supported by the mcuxClOsccaSm4 component. */

#include <stddef.h>
#include <mcuxClKey.h>
#include <mcuxClOsccaSm4_KeyTypes.h>
#include <internal/mcuxClKey_Types_Internal.h>

// oscca sm4 key
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_SM4 = {MCUXCLKEY_ALGO_ID_SM4 + MCUXCLKEY_ALGO_ID_SYMMETRIC_KEY, MCUXCLKEY_SIZE_128, NULL};
