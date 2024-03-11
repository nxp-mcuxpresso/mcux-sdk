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

/** @file  mcuxClOsccaMacModes_MemoryConsumption.h
 *  @brief Memory consumption of the mcuxClOsccaMacModes component */

#ifndef MCUXCLOSCCAMACMODES_MEMORYCONSUMPTION_H_
#define MCUXCLOSCCAMACMODES_MEMORYCONSUMPTION_H_

#define MCUXCLOSCCAMACMODES_SM4_COMPUTE_CPU_WA_BUFFER_SIZE (192u)
#define MCUXCLOSCCAMACMODES_SM4_COMPUTE_CPU_WA_BUFFER_SIZE_IN_WORDS (MCUXCLOSCCAMACMODES_SM4_COMPUTE_CPU_WA_BUFFER_SIZE / sizeof(uint32_t))


#define MCUXCLOSCCAMACMODES_SM4_INIT_CPU_WA_BUFFER_SIZE    (4u)
#define MCUXCLOSCCAMACMODES_SM4_INIT_CPU_WA_BUFFER_SIZE_IN_WORDS (MCUXCLOSCCAMACMODES_SM4_INIT_CPU_WA_BUFFER_SIZE / sizeof(uint32_t))
#define MCUXCLOSCCAMACMODES_SM4_PROCESS_CPU_WA_BUFFER_SIZE (128u)
#define MCUXCLOSCCAMACMODES_SM4_PROCESS_CPU_WA_BUFFER_SIZE_IN_WORDS (MCUXCLOSCCAMACMODES_SM4_PROCESS_CPU_WA_BUFFER_SIZE / sizeof(uint32_t))
#define MCUXCLOSCCAMACMODES_SM4_FINISH_CPU_WA_BUFFER_SIZE  (160u)
#define MCUXCLOSCCAMACMODES_SM4_FINISH_CPU_WA_BUFFER_SIZE_IN_WORDS (MCUXCLOSCCAMACMODES_SM4_FINISH_CPU_WA_BUFFER_SIZE / sizeof(uint32_t))

#define MCUXCLOSCCAMACMODES_SM4_MAX_CPU_WA_BUFFER_SIZE     (224u)
#define MCUXCLOSCCAMACMODES_SM4_MAX_CPU_WA_BUFFER_SIZE_IN_WORDS (MCUXCLOSCCAMACMODES_SM4_MAX_CPU_WA_BUFFER_SIZE / sizeof(uint32_t))


#define MCUXCLOSCCAMACMODES_CTX_SIZE               (48u)
#define MCUXCLOSCCAMACMODES_CTX_SIZE_IN_WORDS      (MCUXCLOSCCAMACMODES_CTX_SIZE / sizeof(uint32_t))

#endif /* MCUXCLOSCCAMACMODES_MEMORYCONSUMPTION_H_ */
