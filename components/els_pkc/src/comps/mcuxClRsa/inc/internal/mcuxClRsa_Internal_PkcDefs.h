/*--------------------------------------------------------------------------*/
/* Copyright 2021, 2023 NXP                                                 */
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
 * @file  mcuxClRsa_Internal_PkcDefs.h
 * @brief Internal definitions of the mcuxClRsa component
 */

#ifndef MCUXCLRSA_INTERNAL_PKCDEFS_H_
#define MCUXCLRSA_INTERNAL_PKCDEFS_H_

#include <mcuxClConfig.h> // Exported features flags header

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************/
/* Indices of operands in PKC workarea and UPTR table for                   */
/* the mcuxClRsa_public                                                      */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_ MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_
 * @brief UPTR table defines for function mcuxClRsa_public.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_X         (0u) ///< UPTR table index for buffer x
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_R         (1u) ///< UPTR table index for buffer r
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_N         (2u) ///< UPTR table index for buffer n
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T1        (3u) ///< UPTR table index for buffer t1
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T2        (4u) ///< UPTR table index for buffer t2
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_OUTPUT    (5u) ///< UPTR table index for buffer output
#define MCUXCLRSA_INTERNAL_PUBLIC_UPTRT_SIZE           (6u) ///< UPTR table size of function mcuxClRsa_public
/** @} */

/****************************************************************************/
/* Indices of operands in PKC workarea and UPTR table for                   */
/* the mcuxClRsa_privatePlain                                                */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_ MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_
 * @brief UPTR table defines for function mcuxClRsa_privatePlain.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_X         (0u) ///< UPTR table index for buffer x
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_R         (1u) ///< UPTR table index for buffer r
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_N         (2u) ///< UPTR table index for buffer n
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_T0        (3u) ///< UPTR table index for buffer t0
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_T1        (4u) ///< UPTR table index for buffer t1
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_T2        (5u) ///< UPTR table index for buffer t2
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_T3        (6u) ///< UPTR table index for buffer t3
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_TE        (7u) ///< UPTR table index for buffer te
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_RAND      (8u) ///< UPTR table index for the buffer with random data used for bliding
#define MCUXCLRSA_INTERNAL_PRIVPLAIN_UPTRT_SIZE           (9u) ///< UPTR table size of function mcuxClRsa_privatePlain

/** @} */

/****************************************************************************/
/* Indices of operands in PKC workarea and UPTR table for                   */
/* the mcuxClRsa_privateCRT                                                  */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_ MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_
 * @brief UPTR table defines for function mcuxClRsa_privateCRT.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_INPUT       (0u) ///< UPTR table index for the input buffer
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_RAND        (1u) ///< UPTR table index for the buffer with random data used for bliding
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PQ_B        (2u) ///< UPTR table index for buffer pq_b
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET0     (3u) ///< UPTR table index for buffer primeT0
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET1     (4u) ///< UPTR table index for buffer primeT1
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET2     (5u) ///< UPTR table index for buffer primeT2
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET3     (6u) ///< UPTR table index for buffer primeT3
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET4     (7u) ///< UPTR table index for buffer primeT4
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_TE          (8u) ///< UPTR table index for buffer primeTE
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_R           (9u) ///< UPTR table index for buffer r
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET5     (10u) ///< UPTR table index for buffer primeT5
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_M           (11u) ///< UPTR table index for buffer m
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_MODT1       (12u) ///< UPTR table index for buffer modT1
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_MODT2       (13u) ///< UPTR table index for buffer modT2
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_MODT3       (14u) ///< UPTR table index for buffer modT3
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_MODT4       (15u) ///< UPTR table index for buffer modT4
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_N           (16u) ///< UPTR table index for buffer n
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_CONST0      (17u) ///< UPTR table index for constant 0
#define MCUXCLRSA_INTERNAL_PRIVCRT_UPTRT_SIZE             (18u) ///< UPTR table size of function mcuxClRsa_privateCRT
/** @} */

/****************************************************************************/
/* Indices of operands in PKC workarea and UPTR table for                   */
/* the mcuxClRsa_noEncode                                                    */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_INTERNAL_UPTRTINDEX_NOENCODE_ MCUXCLRSA_INTERNAL_UPTRTINDEX_NOENCODE_
 * @brief UPTR table defines for function mcuxClRsa_noEncode.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_NOENCODE_OUT          (0u) ///< UPTR table index for buffer input
#define MCUXCLRSA_INTERNAL_NOENCODE_UPTRT_SIZE              (1u) ///< UPTR table size of function mcuxClRsa_noEncode
/** @} */

/****************************************************************************/
/* Indices of operands in PKC workarea and UPTR table for                   */
/* the mcuxClRsa_noVerify                                                    */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_INTERNAL_UPTRTINDEX_NOVERIFY_ MCUXCLRSA_INTERNAL_UPTRTINDEX_NOVERIFY_
 * @brief UPTR table defines for function mcuxClRsa_noVerify.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_NOVERIFY_IN           (0u) ///< UPTR table index for buffer input
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_NOVERIFY_TMP          (1u) ///< UPTR table index for buffer tmp
#define MCUXCLRSA_INTERNAL_NOVERIFY_UPTRT_SIZE              (2u) ///< UPTR table size of function mcuxClRsa_noVerify
/** @} */



/****************************************************************************/
/* Indices of operands in PKC workarea and UPTR table for                   */
/* the mcuxClRsa_KeyGeneration_Plain                                         */
/****************************************************************************/
/**
* @defgroup MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_PLAIN_ MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_PLAIN_
* @brief UPTR table defines for function mcuxClRsa_KeyGeneration_Plain.
* @ingroup mcuxClRsa_Internal_Macros
* @{
*/
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_PLAIN_P         (0u) ///< UPTR table index for buffer p
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_PLAIN_Q         (1u) ///< UPTR table index for buffer q
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_PLAIN_E         (2u) ///< UPTR table index for buffer e
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_PLAIN_N         (3u) ///< UPTR table index for buffer n
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_PLAIN_D         (4u) ///< UPTR table index for buffer d
#define MCUXCLRSA_INTERNAL_KEYGENERATION_PLAIN_UPTRT_SIZE           (5u) ///< UPTR table size of function mcuxClRsa_KeyGeneration_Plain
/** @} */

/****************************************************************************/
/* Indices of operands in PKC workarea and UPTR table for                   */
/* the mcuxClRsa_KeyGeneration_Crt                                           */
/****************************************************************************/
/**
* @defgroup MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_ MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_
* @brief UPTR table defines for function mcuxClRsa_KeyGeneration_Crt.
* @ingroup mcuxClRsa_Internal_Macros
* @{
*/
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_E         (0u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_P         (1u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_Q         (2u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_DP        (3u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_DQ        (4u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_QINV      (5u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_N         (6u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_T1        (7u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_T2        (8u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_T3        (9u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_CONSTANT0 (10u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_CONSTANT1 (11u)
#define MCUXCLRSA_INTERNAL_KEYGENERATION_CRT_UPTRT_SIZE           (12u) ///< UPTR table size of function mcuxClRsa_KeyGeneration_Crt
/** @} */

/****************************************************************************/
/* Indices of operands in PKC workarea and UPTR table for                   */
/* the mcuxClRsa_TestPrimeCandidate                                          */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_ MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_
 * @brief UPTR table defines for function mcuxClRsa_TestPrimeCandidate.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_E                 (0u) ///< UPTR table index for buffer e
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_CANDIDATE         (1u) ///< UPTR table index for buffer with prime candidate
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_CANDIDATE_64MOST  (2u) ///< UPTR table index for 64 most significant bits of prime candidate
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_NUMTOCOMPARE      (3u) ///< UPTR table index for buffer with number to compare
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_A0                (4u) ///< UPTR table index for buffer A0
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_GCD1              (5u) ///< UPTR table index for the first gcd operand
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_GCD2              (6u) ///< UPTR table index for the second gcd operand
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_CONSTANT0         (7u) ///< UPTR table index for the constant 0 
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_CONSTANT1         (8u) ///< UPTR table index for the constant 1
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_CONSTANT2         (9u) ///< UPTR table index for the constant 2
#define MCUXCLRSA_INTERNAL_TESTPRIME_UPTRT_SIZE                   (10u) ///< UPTR table size of function mcuxClRsa_TestPrimeCandidate
/** @} */

/****************************************************************************/
/* Indices of operands in PKC workarea and UPTR table for                   */
/* the mcuxClRsa_GenerateProbablePrime                                       */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_INTERNAL_UPTRTINDEX_GENPRIME_ MCUXCLRSA_INTERNAL_UPTRTINDEX_GENPRIME_
 * @brief UPTR table defines for function mcuxClRsa_GenerateProbablePrime.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_GENPRIME_NUMTOCOMPARE      (0u) ///< UPTR table index for buffer with number to compare
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_GENPRIME_A0                (1u) ///< UPTR table index for buffer A0
#define MCUXCLRSA_INTERNAL_GENPRIME_UPTRT_SIZE                   (2u) ///< UPTR table size of function mcuxClRsa_GenerateProbablePrime
/** @} */

/****************************************************************************/
/* Indices of operands in PKC workarea and UPTR table for                   */
/* the mcuxClRsa_MillerRabinTest                                             */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_ MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_
 * @brief UPTR table defines for function mcuxClRsa_MillerRabinTest
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_PRIMECANDIDATE   (0u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_QSQUARED         (1u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_RESULT           (2u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_X                (3u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_T0               (4u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_T1               (5u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_T2               (6u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_T3               (7u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_TE               (8u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_CONSTANT         (9u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_UPTRT_SIZE       (10u)
/** @} */

/****************************************************************************/
/* Indices of operands in PKC workarea and UPTR table for                   */
/* the mcuxClRsa_ComputeD                                                    */ 
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_ MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_
 * @brief UPTR table defines for function mcuxClRsa_ComputeD
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_P                (0u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_Q                (1u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_D                (2u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_E                (3u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_PSUB1            (4u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_QSUB1            (5u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_PHI              (6u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_LCM              (7u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_T                (8u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_CONSTANT         (9u)
#define MCUXCLRSA_INTERNAL_COMPD_UPTRT_SIZE                  (10u)
/** @} */

/****************************************************************************/
/* Indices of operands in PKC workarea and UPTR table for                   */
/* the mcuxClRsa_TestPQDistance                                              */ 
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPQDISTANCE_ MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPQDISTANCE_
 * @brief UPTR table defines for function mcuxClRsa_ComputeD
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_INTERNAL_TESTPQDISTANCE_P128MSB       (0u)
#define MCUXCLRSA_INTERNAL_TESTPQDISTANCE_Q128MSB       (1u)
#define MCUXCLRSA_INTERNAL_TESTPQDISTANCE_P100MSB       (2u)
#define MCUXCLRSA_INTERNAL_TESTPQDISTANCE_Q100MSB       (3u)
#define MCUXCLRSA_INTERNAL_TESTPQDISTANCE_CONSTANT28    (4u)
#define MCUXCLRSA_INTERNAL_TESTPQDISTANCE_UPTRT_SIZE    (5u)


/****************************************************************************/
/* Indices of operands in PKC workarea and UPTR table for                   */
/* the mcuxClRsa_RemoveBlinding                                              */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_INTERNAL_UPTRTINDEX_REMOVEBLINDING_ MCUXCLRSA_INTERNAL_UPTRTINDEX_REMOVEBLINDING_
 * @brief UPTR table defines for function mcuxClRsa_RemoveBlinding
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_REMOVEBLINDING_B             (0u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_REMOVEBLINDING_NB            (1u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_REMOVEBLINDING_X             (2u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_REMOVEBLINDING_R             (3u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_REMOVEBLINDING_T1            (4u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_REMOVEBLINDING_T2            (5u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_REMOVEBLINDING_ZERO          (6u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_REMOVEBLINDING_UPTRT_SIZE    (7u)


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLRSA_INTERNAL_PKCDEFS_H_ */


