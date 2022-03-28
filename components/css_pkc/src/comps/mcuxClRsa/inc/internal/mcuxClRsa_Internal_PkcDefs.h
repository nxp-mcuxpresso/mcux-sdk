/*--------------------------------------------------------------------------*/
/* Copyright 2021 NXP                                                       */
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
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_X         (0u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_R         (1u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_N         (2u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T1        (3u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_T2        (4u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PUBLIC_OUTPUT    (5u)
#define MCUXCLRSA_INTERNAL_PUBLIC_UPTRT_SIZE           (6u)
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
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_X         (0u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_R         (1u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_N         (2u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_T0        (3u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_T1        (4u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_T2        (5u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_T3        (6u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVPLAIN_TE        (7u)
#define MCUXCLRSA_INTERNAL_PRIVPLAIN_UPTRT_SIZE           (8u)
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
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_INPUT       (0u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_RAND        (1u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PQ_B        (2u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET0     (3u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET1     (4u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET2     (5u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET3     (6u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET4     (7u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_TE          (8u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_R           (9u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_PRIMET5     (10u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_M           (11u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_MODT1       (12u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_MODT2       (13u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_MODT3       (14u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_MODT4       (15u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_PRIVCRT_N           (16u)
#define MCUXCLRSA_INTERNAL_PRIVCRT_UPTRT_SIZE             (17u)
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
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_NOENCODE_OUT          (0u)
#define MCUXCLRSA_INTERNAL_NOENCODE_UPTRT_SIZE              (1u)
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
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_NOVERIFY_IN           (0u)
#define MCUXCLRSA_INTERNAL_UPTRTINDEX_NOVERIFY_TMP          (1u)
#define MCUXCLRSA_INTERNAL_NOVERIFY_UPTRT_SIZE              (2u)
/** @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLRSA_INTERNAL_PKCDEFS_H_ */
