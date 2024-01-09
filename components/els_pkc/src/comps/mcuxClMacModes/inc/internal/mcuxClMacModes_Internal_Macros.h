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

#ifndef MCUXCLMACMODES_INTERNAL_MACROS_H_
#define MCUXCLMACMODES_INTERNAL_MACROS_H_

#include <mcuxClConfig.h> // Exported features flags header

/* TODO CLNS-5054: Move these macros to a central location */

/* Macro used to align the size to the CPU wordsize */
#define MCUXCLMACMODES_INTERNAL_ALIGN_SIZE_TO_CPUWORDS(size)  \
    (((uint32_t) (((uint32_t) (size)) + ((sizeof(uint32_t)) - 1U))) & ((uint32_t) (~((sizeof(uint32_t)) - 1U))))

/* Macro used to compute number of CPU words */
#define MCUXCLMACMODES_INTERNAL_COMPUTE_CPUWORDS(size)  \
    (MCUXCLMACMODES_INTERNAL_ALIGN_SIZE_TO_CPUWORDS(size) / (sizeof(uint32_t)))

#endif /* MCUXCLMACMODES_INTERNAL_MACROS_H_ */

