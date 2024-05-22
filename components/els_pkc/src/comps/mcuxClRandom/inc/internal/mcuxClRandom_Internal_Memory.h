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
 * @file  mcuxClRandom_Internal_Memory.h
 * @brief Provides macros for usage and FP balancing of memory options depneding on the platform
 */

#ifndef MCUXCLRANDOM_INTERNAL_MEMORY_H_
#define MCUXCLRANDOM_INTERNAL_MEMORY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <mcuxClMemory.h>
#include <internal/mcuxClMemory_Copy_Internal.h>
#define MCUXCLRANDOM_SECURECOPY(callerID, errorReturn, pTarget, pSource, length)                \
    do{                                                                                        \
        MCUXCLMEMORY_FP_MEMORY_COPY(pTarget, pSource, length);                                  \
    } while(false)

#define MCUXCLRANDOM_SECURECLEAR(callerID, errorReturn, pTarget, length)                        \
    do{                                                                                        \
        MCUXCLMEMORY_FP_MEMORY_CLEAR(pTarget, length);                                          \
    } while(false)

#define MCUXCLRANDOM_FP_CALLED_SECURECOPY  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)

#define MCUXCLRANDOM_FP_CALLED_SECURECLEAR  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLRANDOM_INTERNAL_TYPES_H_ */
