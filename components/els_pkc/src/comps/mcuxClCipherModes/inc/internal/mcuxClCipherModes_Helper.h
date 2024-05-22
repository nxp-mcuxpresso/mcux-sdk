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

#ifndef MCUXCLCIPHERMODES_HELPER_H_
#define MCUXCLCIPHERMODES_HELPER_H_

#include <stdint.h>

#include <mcuxCsslFlowProtection.h>

/*
 * Helper macros
 */

/* Macro used to align the size to the CPU wordsize */
#define MCUXCLCIPHERMODES_INTERNAL_ALIGN_SIZE_TO_CPUWORDS(size)  \
    (((uint32_t) (((uint32_t) (size)) + ((sizeof(uint32_t)) - 1U))) & ((uint32_t) (~((sizeof(uint32_t)) - 1U))))

/* Macro used to compute number of CPU words */
#define MCUXCLCIPHERMODES_INTERNAL_COMPUTE_CPUWORDS(size)  \
    (MCUXCLCIPHERMODES_INTERNAL_ALIGN_SIZE_TO_CPUWORDS(size) / (sizeof(uint32_t)))


/*
 * Helper functions
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCipherModes_MemClear)
void mcuxClCipherModes_MemClear(uint8_t *pDst, uint32_t length);

#endif /* MCUXCLCIPHERMODES_HELPER_H_ */
