/*--------------------------------------------------------------------------*/
/* Copyright 2022 NXP                                                       */
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

/** @file  mcuxClPsaDriver_Macros.h
 *  @brief Defines the memory consumption for the mcuxClPsaDriver component
 */

#ifndef MCUXCLPSADRIVER_MACROS_H_
#define MCUXCLPSADRIVER_MACROS_H_

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @defgroup mcuxClPsaDriver_Macros mcuxClPsaDriver_Macros
 * @brief Defines the types for the @ref mcuxClPsaDriver component
 * @ingroup mcuxClPsaDriver
 * @{
 */

/* Macro determining maximum value */
#define MCUXCLPSADRIVER_MAX(a, b) ((a) > (b) ? (a) : (b))


/**
 * @}
 */ /* mcuxClPsaDriver_Macros */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLPSADRIVER_MACROS_H_ */

