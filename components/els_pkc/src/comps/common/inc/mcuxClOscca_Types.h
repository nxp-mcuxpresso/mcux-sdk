/*--------------------------------------------------------------------------*/
/* Copyright 2016, 2021 NXP                                                 */
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
/* Security Classification:  Company Confidential                           */
/*--------------------------------------------------------------------------*/

/**
 *
 * @file:  mcuxClOscca_Types.h
 * @brief: Global type definitions
 *
 */

#ifndef MCUXCLOSCCA_TYPES_H_
#define MCUXCLOSCCA_TYPES_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef __RNG_TYPES_DEFINED_
/**
* \brief The RNG context forward declaration
*/
typedef struct mcuxClOscca_Rng_Ctx_t mcuxClOscca_Rng_Ctx_t;
#endif

/** \brief Structure for multi-precision integer used in asymetric cryptography. */
typedef struct mcuxClOscca_MPInt_t
{
  uint8_t const *pMPInt;    /**< Pointer to the multi precision integer. */
  uint16_t wNumBytes;       /**< Length in bytes of multi precision integer. */
} mcuxClOscca_MPInt_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLOSCCA_TYPES_H_ */
