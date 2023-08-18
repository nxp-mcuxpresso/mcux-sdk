/*--------------------------------------------------------------------------*/
/* Copyright 2020-2023 NXP                                                  */
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

/** @file  mcuxClHash_MemoryConsumption.h
 *  @brief Defines the memory consumption for the mcuxClHash component */

#ifndef MCUXCLHASH_MEMORYCONSUMPTION_H_
#define MCUXCLHASH_MEMORYCONSUMPTION_H_

/**
 * @defgroup MCUXCLHASH_WA MCUXCLHASH_WA
 * @brief Definitions of workarea sizes for the mcuxClHash functions.
 * @ingroup mcuxClHash_Constants
 * @{
 */

/****************************************************************************/
/* Definitions of workarea buffer sizes for the mcuxClHash functions.        */
/****************************************************************************/

#define MCUXCLHASH_COMPUTE_CPU_WA_BUFFER_SIZE_MIYAGUCHI_PRENEEL	(1u)	///< Defines the workarea size required by mcuxClHash_compute for Miyaguchi Preneel
#define MCUXCLHASH_COMPUTE_CPU_WA_BUFFER_SIZE_MD5          		(1u)   ///< Defines the workarea size required by mcuxClHash_compute for MD5
#define MCUXCLHASH_COMPUTE_CPU_WA_BUFFER_SIZE_SHA_1        		(1u)  ///< Defines the workarea size required by mcuxClHash_compute for SHA-1
#define MCUXCLHASH_COMPUTE_CPU_WA_BUFFER_SIZE_SHA2_224     		(96u)  ///< Defines the workarea size required by mcuxClHash_compute for SHA2-224
#define MCUXCLHASH_COMPUTE_CPU_WA_BUFFER_SIZE_SHA2_256     		(96u)  ///< Defines the workarea size required by mcuxClHash_compute for SHA2-256
#define MCUXCLHASH_COMPUTE_CPU_WA_BUFFER_SIZE_SHA2_384     		(192u)  ///< Defines the workarea size required by mcuxClHash_compute for SHA2-384
#define MCUXCLHASH_COMPUTE_CPU_WA_BUFFER_SIZE_SHA2_512     		(192u)  ///< Defines the workarea size required by mcuxClHash_compute for SHA2-512
#define MCUXCLHASH_COMPUTE_CPU_WA_BUFFER_SIZE_SHA2_512_224 		(192u)  ///< Defines the workarea size required by mcuxClHash_compute for SHA2-512/224
#define MCUXCLHASH_COMPUTE_CPU_WA_BUFFER_SIZE_SHA2_512_256 		(192u)  ///< Defines the workarea size required by mcuxClHash_compute for SHA2-512/256
#define MCUXCLHASH_COMPUTE_CPU_WA_BUFFER_SIZE_SHA3         		(1u)  ///< Defines the workarea size required by mcuxClHash_compute for all SHA3 modes
#define MCUXCLHASH_COMPUTE_CPU_WA_BUFFER_SIZE_MAX          		(192u)  ///< Defines the max workarea size required by mcuxClHash_compute


#define MCUXCLHASH_COMPARE_CPU_WA_BUFFER_SIZE_MIYAGUCHI_PRENEEL	MCUXCLHASH_COMPUTE_CPU_WA_BUFFER_SIZE_MIYAGUCHI_PRENEEL	///< Defines the workarea size required by mcuxClHash_compare for Miyaguchi Preneel
#define MCUXCLHASH_COMPARE_CPU_WA_BUFFER_SIZE_MD5          		MCUXCLHASH_COMPUTE_CPU_WA_BUFFER_SIZE_MD5  ///< Defines the workarea size required for mcuxClHash_compare on MD5
#define MCUXCLHASH_COMPARE_CPU_WA_BUFFER_SIZE_SHA_1        		MCUXCLHASH_COMPUTE_CPU_WA_BUFFER_SIZE_SHA_1  ///< Defines the workarea size required for mcuxClHash_compare on SHA-1
#define MCUXCLHASH_COMPARE_CPU_WA_BUFFER_SIZE_SHA2_224     		MCUXCLHASH_COMPUTE_CPU_WA_BUFFER_SIZE_SHA2_224  ///< Defines the workarea size required for mcuxClHash_compare on SHA2-224
#define MCUXCLHASH_COMPARE_CPU_WA_BUFFER_SIZE_SHA2_256     		MCUXCLHASH_COMPUTE_CPU_WA_BUFFER_SIZE_SHA2_256  ///< Defines the workarea size required for mcuxClHash_compare on SHA2-256
#define MCUXCLHASH_COMPARE_CPU_WA_BUFFER_SIZE_SHA2_384     		MCUXCLHASH_COMPUTE_CPU_WA_BUFFER_SIZE_SHA2_384  ///< Defines the workarea size required for mcuxClHash_compare on SHA2-384
#define MCUXCLHASH_COMPARE_CPU_WA_BUFFER_SIZE_SHA2_512     		MCUXCLHASH_COMPUTE_CPU_WA_BUFFER_SIZE_SHA2_512  ///< Defines the workarea size required for mcuxClHash_compare on SHA2-512
#define MCUXCLHASH_COMPARE_CPU_WA_BUFFER_SIZE_SHA2_512_224 		MCUXCLHASH_COMPUTE_CPU_WA_BUFFER_SIZE_SHA2_512_224  ///< Defines the workarea size required for mcuxClHash_compare on SHA2-512/224
#define MCUXCLHASH_COMPARE_CPU_WA_BUFFER_SIZE_SHA2_512_256 		MCUXCLHASH_COMPUTE_CPU_WA_BUFFER_SIZE_SHA2_512_256  ///< Defines the workarea size required for mcuxClHash_compare on SHA2-512/256
#define MCUXCLHASH_COMPARE_CPU_WA_BUFFER_SIZE_SHA3         		MCUXCLHASH_COMPUTE_CPU_WA_BUFFER_SIZE_SHA3  ///< Defines the workarea size required for mcuxClHash_compare on all SHA3 modes
#define MCUXCLHASH_COMPARE_CPU_WA_BUFFER_SIZE_MAX          		MCUXCLHASH_COMPUTE_CPU_WA_BUFFER_SIZE_MAX  ///< Defines the max workarea size required for mcuxClHash_compare

#define MCUXCLHASH_INIT_CPU_WA_BUFFER_SIZE                 		(0u)  ///< Defines the max workarea size required for mcuxClHash_init

#define MCUXCLHASH_PROCESS_CPU_WA_BUFFER_SIZE_MIYAGUCHI_PRENEEL	(0u)  ///< Defines the workarea size required for mcuxClHash_process for Miyaguchi Preneel
#define MCUXCLHASH_PROCESS_CPU_WA_BUFFER_SIZE_MD5          		(1u)  ///< Defines the workarea size required for mcuxClHash_process on MD5
#define MCUXCLHASH_PROCESS_CPU_WA_BUFFER_SIZE_SHA_1        		(1u)  ///< Defines the workarea size required for mcuxClHash_process on SHA-1
#define MCUXCLHASH_PROCESS_CPU_WA_BUFFER_SIZE_SHA2_224     		(1u)  ///< Defines the workarea size required for mcuxClHash_process on SHA2-224
#define MCUXCLHASH_PROCESS_CPU_WA_BUFFER_SIZE_SHA2_256     		(1u)  ///< Defines the workarea size required for mcuxClHash_process on SHA2-256
#define MCUXCLHASH_PROCESS_CPU_WA_BUFFER_SIZE_SHA2_384     		(1u)  ///< Defines the workarea size required for mcuxClHash_process on SHA2-384
#define MCUXCLHASH_PROCESS_CPU_WA_BUFFER_SIZE_SHA2_512     		(1u)  ///< Defines the workarea size required for mcuxClHash_process on SHA2-512
#define MCUXCLHASH_PROCESS_CPU_WA_BUFFER_SIZE_SHA2_512_224 		(1u)  ///< Defines the workarea size required for mcuxClHash_process on SHA2-512/224
#define MCUXCLHASH_PROCESS_CPU_WA_BUFFER_SIZE_SHA2_512_256 		(1u)  ///< Defines the workarea size required for mcuxClHash_process on SHA2-512/256
#define MCUXCLHASH_PROCESS_CPU_WA_BUFFER_SIZE_SHA3         		(0u)  ///< Defines the workarea size required for mcuxClHash_process on all SHA3 modes
#define MCUXCLHASH_PROCESS_CPU_WA_BUFFER_SIZE_MAX          		(4u)  ///< Defines the max workarea size required for mcuxClHash_process

#define MCUXCLHASH_FINISH_CPU_WA_BUFFER_SIZE_MIYAGUCHI_PRENEEL	(1)  ///< Defines the workarea size required for mcuxClHash_finish for Miyaguchi Preneel
#define MCUXCLHASH_FINISH_CPU_WA_BUFFER_SIZE_MD5          		(1u)  ///< Defines the workarea size required for mcuxClHash_finish on MD5
#define MCUXCLHASH_FINISH_CPU_WA_BUFFER_SIZE_SHA_1        		(1u)  ///< Defines the workarea size required for mcuxClHash_finish on SHA-1
#define MCUXCLHASH_FINISH_CPU_WA_BUFFER_SIZE_SHA2_224     		(96u)  ///< Defines the workarea size required for mcuxClHash_finish on SHA2-224
#define MCUXCLHASH_FINISH_CPU_WA_BUFFER_SIZE_SHA2_256     		(96u)  ///< Defines the workarea size required for mcuxClHash_finish on SHA2-256
#define MCUXCLHASH_FINISH_CPU_WA_BUFFER_SIZE_SHA2_384     		(192u)  ///< Defines the workarea size required for mcuxClHash_finish on SHA2-384
#define MCUXCLHASH_FINISH_CPU_WA_BUFFER_SIZE_SHA2_512     		(192u)  ///< Defines the workarea size required for mcuxClHash_finish on SHA2-512
#define MCUXCLHASH_FINISH_CPU_WA_BUFFER_SIZE_SHA2_512_224 		(192u)  ///< Defines the workarea size required for mcuxClHash_finish on SHA2-512/224
#define MCUXCLHASH_FINISH_CPU_WA_BUFFER_SIZE_SHA2_512_256 		(192u)  ///< Defines the workarea size required for mcuxClHash_finish on SHA2-512/256
#define MCUXCLHASH_FINISH_CPU_WA_BUFFER_SIZE_SHA3         		(1u)  ///< Defines the workarea size required for mcuxClHash_finish on all SHA3 modes
#define MCUXCLHASH_FINISH_CPU_WA_BUFFER_SIZE_MAX          		(192u)  ///< Defines the max workarea size required for mcuxClHash_finish

#define MCUXCLHASH_VERIFY_CPU_WA_BUFFER_SIZE_MIYAGUCHI_PRENEEL	MCUXCLHASH_FINISH_CPU_WA_BUFFER_SIZE_MIYAGUCHI_PRENEEL	///< Defines the workarea size required for mcuxClHash_verify for Miyaguchi Preneel
#define MCUXCLHASH_VERIFY_CPU_WA_BUFFER_SIZE_MD5          		MCUXCLHASH_FINISH_CPU_WA_BUFFER_SIZE_MD5  ///< Defines the workarea size required for mcuxClHash_verify on MD5
#define MCUXCLHASH_VERIFY_CPU_WA_BUFFER_SIZE_SHA_1        		MCUXCLHASH_FINISH_CPU_WA_BUFFER_SIZE_SHA_1  ///< Defines the workarea size required for mcuxClHash_verify on SHA-1
#define MCUXCLHASH_VERIFY_CPU_WA_BUFFER_SIZE_SHA2_224     		MCUXCLHASH_FINISH_CPU_WA_BUFFER_SIZE_SHA2_224  ///< Defines the workarea size required for mcuxClHash_verify on SHA2-224
#define MCUXCLHASH_VERIFY_CPU_WA_BUFFER_SIZE_SHA2_256     		MCUXCLHASH_FINISH_CPU_WA_BUFFER_SIZE_SHA2_256  ///< Defines the workarea size required for mcuxClHash_verify on SHA2-256
#define MCUXCLHASH_VERIFY_CPU_WA_BUFFER_SIZE_SHA2_384     		MCUXCLHASH_FINISH_CPU_WA_BUFFER_SIZE_SHA2_384  ///< Defines the workarea size required for mcuxClHash_verify on SHA2-384
#define MCUXCLHASH_VERIFY_CPU_WA_BUFFER_SIZE_SHA2_512     		MCUXCLHASH_FINISH_CPU_WA_BUFFER_SIZE_SHA2_512  ///< Defines the workarea size required for mcuxClHash_verify on SHA2-512
#define MCUXCLHASH_VERIFY_CPU_WA_BUFFER_SIZE_SHA2_512_224 		MCUXCLHASH_FINISH_CPU_WA_BUFFER_SIZE_SHA2_512_224  ///< Defines the workarea size required for mcuxClHash_verify on SHA2-512/224
#define MCUXCLHASH_VERIFY_CPU_WA_BUFFER_SIZE_SHA2_512_256 		MCUXCLHASH_FINISH_CPU_WA_BUFFER_SIZE_SHA2_512_256  ///< Defines the workarea size required for mcuxClHash_verify on SHA2-512/256
#define MCUXCLHASH_VERIFY_CPU_WA_BUFFER_SIZE_SHA3         		MCUXCLHASH_FINISH_CPU_WA_BUFFER_SIZE_SHA3  ///< Defines the workarea size required for mcuxClHash_verify on all SHA3 modes
#define MCUXCLHASH_VERIFY_CPU_WA_BUFFER_SIZE_MAX          		MCUXCLHASH_FINISH_CPU_WA_BUFFER_SIZE_MAX  ///< Defines the max workarea size required for mcuxClHash_verify

#define MCUXCLHASH_MAX_CPU_WA_BUFFER_SIZE               (MCUXCLHASH_COMPUTE_CPU_WA_BUFFER_SIZE_MAX > MCUXCLHASH_FINISH_CPU_WA_BUFFER_SIZE_MAX ?   \
														MCUXCLHASH_COMPUTE_CPU_WA_BUFFER_SIZE_MAX : MCUXCLHASH_FINISH_CPU_WA_BUFFER_SIZE_MAX)		 ///< Defines the max workarea size required this component

/** @} */

/**
 * @defgroup MCUXCLHASH_STATE MCUXCLHASH_STATE
 * @brief Definitions of state sizes for extration of states of a hash operation.
 * @ingroup mcuxClHash_Constants
 * @{
 */

/********************************************************************************************/
/* Definitions of state buffer sizes for mcuxClHash_export_state and mcuxClHash_import_state  */
/********************************************************************************************/

#define MCUXCLHASH_EXPORT_IMPORT_STATE_SIZE_MD5           (1u)  ///< Defines the state size required for MD5
#define MCUXCLHASH_EXPORT_IMPORT_STATE_SIZE_SHA_1         (1u)  ///< Defines the state size required for SHA-1
#define MCUXCLHASH_EXPORT_IMPORT_STATE_SIZE_SHA2_224      (1u)  ///< Defines the state size required for SHA2-224
#define MCUXCLHASH_EXPORT_IMPORT_STATE_SIZE_SHA2_256      (1u)  ///< Defines the state size required for SHA2-256
#define MCUXCLHASH_EXPORT_IMPORT_STATE_SIZE_SHA2_384      (1u)  ///< Defines the state size required for SHA2-384
#define MCUXCLHASH_EXPORT_IMPORT_STATE_SIZE_SHA2_512      (1u)  ///< Defines the state size required for SHA2-512
#define MCUXCLHASH_EXPORT_IMPORT_STATE_SIZE_SHA2_512_224  (1u)  ///< Defines the state size required for SHA2-512/224
#define MCUXCLHASH_EXPORT_IMPORT_STATE_SIZE_SHA2_512_256  (1u)  ///< Defines the state size required for SHA2-512/256
#define MCUXCLHASH_EXPORT_IMPORT_STATE_SIZE_MAX           (1u)  ///< Defines the max state size required for this component


/** @} */

/**
 * @defgroup MCUXCLHASH_CONTEXT MCUXCLHASH_CONTEXT
 * @brief Definitions of context sizes for the mcuxClHash multi-part functions.
 * @ingroup mcuxClHash_Constants
 * @{
 */

/****************************************************************************/
/* Definitions of context sizes for the mcuxClHash multi-part functions.     */
/****************************************************************************/

#define MCUXCLHASH_CONTEXT_SIZE (224u) ///< Defines the context size for streaming hashing interfaces

/** @} */


#endif /* MCUXCLHASH_MEMORYCONSUMPTION_H_ */
