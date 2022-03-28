/*--------------------------------------------------------------------------*/
/* Copyright 2020 NXP                                                       */
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

/** @file  mcuxClKey_KeyTypes.c
 *  @brief Instantiation of the key types supported by the mcuxClKey component. */

#include <mcuxClKey_KeyTypes.h>
#include <stddef.h>

// fully supported key types
const mcuxClKey_Type_t mcuxKey_keyType_Aes128 = {MCUXCLKEY_ALGO_ID_AES + MCUXCLKEY_ALGO_ID_SYMMETRIC_KEY, MCUXCLKEY_SIZE_128, NULL};
const mcuxClKey_Type_t mcuxKey_keyType_Aes256 = {MCUXCLKEY_ALGO_ID_AES + MCUXCLKEY_ALGO_ID_SYMMETRIC_KEY, MCUXCLKEY_SIZE_256, NULL};
// key types supported by key from memory only
const mcuxClKey_Type_t mcuxKey_keyType_Aes192 = {MCUXCLKEY_ALGO_ID_AES + MCUXCLKEY_ALGO_ID_SYMMETRIC_KEY, MCUXCLKEY_SIZE_192, NULL};
