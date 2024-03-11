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


/** @file  mcuxClOsccaCipherModes_MemoryConsumption.h
 *  @brief Memory consumption of the mcuxClOsccaCipherModes component */
 
#ifndef MCUXCLOSCCACIPHERMODES_MEMORYCONSUMPTION_H_
#define MCUXCLOSCCACIPHERMODES_MEMORYCONSUMPTION_H_

/* Workarea sizes */
#ifdef MCUXCL_FEATURE_CIPHERMODES_SM4

#define MCUXCLOSCCACIPHER_SM4_CRYPT_CPU_WA_BUFFER_SIZE            (584u)
#define MCUXCLOSCCACIPHER_SM4_CRYPT_CPU_WA_BUFFER_SIZE_IN_WORDS   (MCUXCLOSCCACIPHER_SM4_CRYPT_CPU_WA_BUFFER_SIZE / sizeof(uint32_t))

#define MCUXCLOSCCACIPHER_MAX_SM4_CPU_WA_BUFFER_SIZE              (MCUXCLOSCCACIPHER_SM4_CRYPT_CPU_WA_BUFFER_SIZE)
#define MCUXCLOSCCACIPHER_MAX_SM4_CPU_WA_BUFFER_SIZE_IN_WORDS     (MCUXCLOSCCACIPHER_SM4_CRYPT_CPU_WA_BUFFER_SIZE_IN_WORDS)



#define MCUXCLOSCCACIPHER_SM4_INIT_CPU_WA_BUFFER_SIZE             (4u)
#define MCUXCLOSCCACIPHER_SM4_PROCESS_CPU_WA_BUFFER_SIZE          (4u)
#define MCUXCLOSCCACIPHER_SM4_FINISH_CPU_WA_BUFFER_SIZE           (4u)
#define MCUXCLOSCCACIPHER_SM4_INIT_CPU_WA_BUFFER_SIZE_IN_WORDS    (MCUXCLOSCCACIPHER_SM4_INIT_CPU_WA_BUFFER_SIZE / sizeof(uint32_t))
#define MCUXCLOSCCACIPHER_SM4_PROCESS_CPU_WA_BUFFER_SIZE_IN_WORDS (MCUXCLOSCCACIPHER_SM4_PROCESS_CPU_WA_BUFFER_SIZE / sizeof(uint32_t))
#define MCUXCLOSCCACIPHER_SM4_FINISH_CPU_WA_BUFFER_SIZE_IN_WORDS  (MCUXCLOSCCACIPHER_SM4_FINISH_CPU_WA_BUFFER_SIZE / sizeof(uint32_t))

/* Context sizes */
#define MCUXCLOSCCACIPHER_SM4_CONTEXT_SIZE                        (584u)
#define MCUXCLOSCCACIPHER_SM4_CONTEXT_SIZE_IN_WORDS               (MCUXCLOSCCACIPHER_SM4_CONTEXT_SIZE / sizeof(uint32_t))
#endif /* MCUXCL_FEATURE_CIPHERMODES_SM4 */

#endif /* MCUXCLOSCCACIPHERMODES_MEMORYCONSUMPTION_H_ */
