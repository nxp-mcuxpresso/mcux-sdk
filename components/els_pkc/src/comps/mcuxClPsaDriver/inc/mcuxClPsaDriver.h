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

/** @file  mcuxClPsaDriver.h
 *  @brief Additional macros for the ARM PSA driver
 */

#ifndef MCUXCLPSADRIVER_H_
#define MCUXCLPSADRIVER_H_


#include <common.h>
#include <psa/crypto.h>
#include <psa_crypto_driver_wrappers.h>
#include <mcuxClConfig.h> // Exported features flags header

/* Include TF-M builtin key driver added from TFM v1.8 updates */
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)
#include "tfm_builtin_key_loader.h"
#endif /* PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER */

/* If TF-M builtin key driver is enabled (only aplicable for tfm examples) */
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)
#define MCUXCLPSADRIVER_IS_LOCAL_STORAGE(location) ((location) == PSA_KEY_LOCATION_LOCAL_STORAGE || (location) == TFM_BUILTIN_KEY_LOADER_KEY_LOCATION)
#else
#define MCUXCLPSADRIVER_IS_LOCAL_STORAGE(location) ((location) == PSA_KEY_LOCATION_LOCAL_STORAGE)
#endif

#define PSA_KEY_LOCATION_EXTERNAL_STORAGE ((psa_key_location_t)(PSA_KEY_LOCATION_VENDOR_FLAG | 0x00U))

#endif /* MCUXCLPSADRIVER_H_ */
