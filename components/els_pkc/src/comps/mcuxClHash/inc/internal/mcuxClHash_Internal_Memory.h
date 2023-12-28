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

/** @file  mcuxClHash_Internal_Memory.h
 *  @brief Internal memory consumption definitions of the mcuxClHash component */

#ifndef MCUXCLHASH_INTERNAL_MEMORY_H_
#define MCUXCLHASH_INTERNAL_MEMORY_H_

#include <internal/mcuxClHashModes_Internal_Memory.h>
#if defined(MCUXCL_FEATURE_HASH_HW_SM3)
#include <internal/mcuxClOsccaSm3_Internal.h>
#endif /* defined(MCUXCL_FEATURE_HASH_SW_SM3) || defined(MCUXCL_FEATURE_HASH_HW_SM3) */

#if defined(MCUXCL_FEATURE_HASH_HW_SM3)
#define MCUXCLHASH_INTERNAL_WACPU_MAX            MCUXCLHASHMODES_MAX(MCUXCLHASHMODES_INTERNAL_WACPU_MAX, MCUXCLOSCCASM3_WACPU_SIZE_SM3)
#define MCUXCLHASH_CONTEXT_MAX_SIZE_INTERNAL     MCUXCLHASHMODES_MAX(MCUXCLHASHMODES_CONTEXT_MAX_SIZE_INTERNAL, MCUXCLOSCCASM3_CONTEXT_SIZE_SM3)
#else
#define MCUXCLHASH_INTERNAL_WACPU_MAX            MCUXCLHASHMODES_INTERNAL_WACPU_MAX
#define MCUXCLHASH_CONTEXT_MAX_SIZE_INTERNAL     MCUXCLHASHMODES_CONTEXT_MAX_SIZE_INTERNAL
#endif

#endif /* MCUXCLHASH_INTERNAL_MEMORY_H_ */
