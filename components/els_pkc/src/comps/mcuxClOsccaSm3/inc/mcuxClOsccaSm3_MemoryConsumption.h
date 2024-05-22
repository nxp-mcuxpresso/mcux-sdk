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

/**
 * @file  mcuxClOsccaSm3_MemoryConsumption.h
 * @brief Defines the memory consumption for the mcuxClOsccaSm3 component
 */

#ifndef MCUXCLOSCCASM3_MEMORYCONSUMPTION_H_
#define MCUXCLOSCCASM3_MEMORYCONSUMPTION_H_

/**
 * @defgroup MCUXCLOSCCASM3_WA MCUXCLOSCCASM3_WA
 * @brief Definitions of workarea sizes for the mcuxClOsccaSm3 functions.
 * @ingroup mcuxClOsccaSm3_Constants
 * @{
 */

/****************************************************************************/
/* Definitions of workarea buffer sizes for the mcuxClOsccaSm3 functions.    */
/****************************************************************************/
#define MCUXCLOSCCASM3_COMPUTE_CPU_WA_BUFFER_SIZE_SM3          (160u)   ///< Defines the workarea size required for mcuxClOsccaSm3_compute on SM3
#define MCUXCLOSCCASM3_COMPUTE_CPU_WA_BUFFER_SIZE_MAX          (160u)  ///< Defines the max workarea size required for mcuxClOsccaSm3_compute


#define MCUXCLOSCCASM3_INIT_CPU_WA_BUFFER_SIZE                 (0u)  ///< Defines the max workarea size required for mcuxClOsccaSm3_init

#define MCUXCLOSCCASM3_PROCESS_CPU_WA_BUFFER_SIZE_SM3          (32u)  ///< Defines the workarea size required for mcuxClOsccaSm3_process on SM3
#define MCUXCLOSCCASM3_PROCESS_CPU_WA_BUFFER_SIZE_MAX          (32u)  ///< Defines the max workarea size required for mcuxClOsccaSm3_process

#define MCUXCLOSCCASM3_FINISH_CPU_WA_BUFFER_SIZE_SM3          (64u)  ///< Defines the workarea size required for mcuxClOsccaSm3_finish on SM3
#define MCUXCLOSCCASM3_FINISH_CPU_WA_BUFFER_SIZE_MAX          (64u)  ///< Defines the max workarea size required for mcuxClOsccaSm3_finish

#define MCUXCLOSCCASM3_MAX_CPU_WA_BUFFER_SIZE                 (160u)  ///< Defines the max workarea size required this component

/** @} */

/**
 * @defgroup MCUXCLOSCCASM3_CONTEXT MCUXCLOSCCASM3_CONTEXT
 * @brief Definitions of context sizes for the mcuxClOsccaSm3 multi-part functions.
 * @ingroup mcuxClOsccaSm3_Constants
 * @{
 */

/****************************************************************************/
/* Definitions of context sizes for the mcuxClOsccaSm3 multi-part functions. */
/****************************************************************************/

#define MCUXCLOSCCASM3_CONTEXT_SIZE (120u)
#define MCUXCLOSCCASM3_CONTEXT_SIZE_IN_WORDS (120u / sizeof(uint32_t)) ///< Defines the context size for streaming hashing interfaces

/********************************************************************************************/
/* Definitions of state buffer sizes for mcuxClHash_export_state and mcuxClHash_import_state  */
/********************************************************************************************/

#define MCUXCLOSCCASM3_EXPORT_IMPORT_CPU_WA_BUFFER_SIZE                  (40u)      ///< Defines the state size required for SM3

/**
 * @}
 */ /* mcuxClOsccaSm3_MemoryConsumption */

#endif /* MCUXCLOSCCASM3_MEMORYCONSUMPTION_H_ */
