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

/** @file  mcuxClHmac_MemoryConsumption.h
 *  @brief Defines the memory consumption for the mcuxClHmac component
 *         All work area sizes in bytes are a multiple of CPU wordsize.
 */

#ifndef MCUXCLHMAC_MEMORYCONSUMPTION_H_
#define MCUXCLHMAC_MEMORYCONSUMPTION_H_

/**
 * @defgroup mcuxClHmac_MemoryConsumption mcuxClHmac_MemoryConsumption
 * @brief Defines the memory consumption for the mcuxClHmac component
 * @ingroup mcuxClHmac
 * @{
 */

/**
 * @brief Helper macro to calculate size aligned to CPU word.
 */
#define MCUXCLHMAC_SIZE_IN_CPUWORDS(size)  ((((size) + sizeof(uint32_t) - 1u) / sizeof(uint32_t)))

/* Workarea sizes */
#define MCUXCLHMAC_COMPUTE_CPU_WA_BUFFER_SIZE            (360u)
#define MCUXCLHMAC_COMPUTE_CPU_WA_BUFFER_SIZE_IN_WORDS   MCUXCLHMAC_SIZE_IN_CPUWORDS(MCUXCLHMAC_COMPUTE_CPU_WA_BUFFER_SIZE)
#define MCUXCLHMAC_INIT_CPU_WA_BUFFER_SIZE               (360u)
#define MCUXCLHMAC_INIT_CPU_WA_BUFFER_SIZE_IN_WORDS      MCUXCLHMAC_SIZE_IN_CPUWORDS(MCUXCLHMAC_INIT_CPU_WA_BUFFER_SIZE)
#define MCUXCLHMAC_PROCESS_CPU_WA_BUFFER_SIZE            (4u)
#define MCUXCLHMAC_PROCESS_CPU_WA_BUFFER_SIZE_IN_WORDS   MCUXCLHMAC_SIZE_IN_CPUWORDS(MCUXCLHMAC_PROCESS_CPU_WA_BUFFER_SIZE)
#define MCUXCLHMAC_FINISH_CPU_WA_BUFFER_SIZE             (168u)
#define MCUXCLHMAC_FINISH_CPU_WA_BUFFER_SIZE_IN_WORDS    MCUXCLHMAC_SIZE_IN_CPUWORDS(MCUXCLHMAC_FINISH_CPU_WA_BUFFER_SIZE)

#define MCUXCLHMAC_MAX_CPU_WA_BUFFER_SIZE                (360u)
#define MCUXCLHMAC_MAX_CPU_WA_BUFFER_SIZE_IN_WORDS       MCUXCLHMAC_SIZE_IN_CPUWORDS(MCUXCLHMAC_MAX_CPU_WA_BUFFER_SIZE)

/* Context sizes */
#define MCUXCLHMAC_CONTEXT_SIZE_SW                       (572u)
#define MCUXCLHMAC_CONTEXT_SIZE_SW_IN_WORDS              MCUXCLHMAC_SIZE_IN_CPUWORDS(MCUXCLHMAC_CONTEXT_SIZE_SW)
#define MCUXCLHMAC_CONTEXT_SIZE_ELS                      (72u)
#define MCUXCLHMAC_CONTEXT_SIZE_ELS_IN_WORDS             MCUXCLHMAC_SIZE_IN_CPUWORDS(MCUXCLHMAC_CONTEXT_SIZE_ELS)
#define MCUXCLHMAC_MAX_CONTEXT_SIZE                      (572u)
#define MCUXCLHMAC_MAX_CONTEXT_SIZE_IN_WORDS             MCUXCLHMAC_SIZE_IN_CPUWORDS(MCUXCLHMAC_MAX_CONTEXT_SIZE)

/* Mode descriptor sizes */
#define MCUXCLHMAC_HMAC_MODE_DESCRIPTOR_SIZE             (48u)
#define MCUXCLHMAC_HMAC_MODE_DESCRIPTOR_SIZE_IN_WORDS    MCUXCLHMAC_SIZE_IN_CPUWORDS(MCUXCLHMAC_HMAC_MODE_DESCRIPTOR_SIZE)

/**
 * @}
 */ /* mcuxClMac_MemoryConsumption */

#endif /* MCUXCLHMAC_MEMORYCONSUMPTION_H_ */
