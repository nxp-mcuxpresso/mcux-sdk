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

#ifndef MCUXCLAES_INTERNAL_CONSTANTS_H_
#define MCUXCLAES_INTERNAL_CONSTANTS_H_

#include <mcuxClConfig.h> // Exported features flags header

#ifdef __cplusplus
extern "C" {
#endif

#define MCUXCLAES_MASKED_KEY_SIZE               (32u)
#define MCUXCLAES_MASKED_KEY_SIZE_IN_WORDS      (MCUXCLAES_MASKED_KEY_SIZE / sizeof(uint32_t))

#define MCUXCLAES_GCM_H_KEY_SIZE                (16u)


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLAES_INTERNAL_CONSTANTS_H_ */
