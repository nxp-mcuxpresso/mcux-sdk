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

/** @file  mcuxClPsaDriver_ExternalMacroWrappers.h
 *  @brief Defines the memory consumption for the mcuxClPsaDriver component
 */

#ifndef MCUXCLPSADRIVER_EXTERNAL_MACRO_WRAPPERS_H_
#define MCUXCLPSADRIVER_EXTERNAL_MACRO_WRAPPERS_H_

#include <psa/crypto.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @defgroup mcuxClPsaDriver_ExternalMacroWrappers mcuxClPsaDriver_ExternalMacroWrappers
 * @brief Defines the External Macro Wrappers for the @ref mcuxClPsaDriver component
 * @ingroup mcuxClPsaDriver
 * @{
 */

#define MCUXCLPSADRIVER_PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(aead_alg) \
    (MCUX_CSSL_ANALYSIS_START_SUPPRESS_INVALID_WIDTH_IN_SHIFT_OPERATIONS("External code. Operation is safe on target platform.") \
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_CONVERSIONS_WITH_INAPPROPRIATE_TYPE("External code. Operation is safe on target platform.") \
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_OPERATIONS_ON_INAPPROPRIATE_TYPE("External code. Operation is safe on target platform.") \
        PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(aead_alg) \
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INVALID_WIDTH_IN_SHIFT_OPERATIONS() \
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_CONVERSIONS_WITH_INAPPROPRIATE_TYPE() \
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_OPERATIONS_ON_INAPPROPRIATE_TYPE())

#define MCUXCLPSADRIVER_PSA_AEAD_FINISH_OUTPUT_SIZE(key_type, alg) \
    (MCUX_CSSL_ANALYSIS_START_SUPPRESS_CONVERSIONS_WITH_INAPPROPRIATE_TYPE("External code. Operation is safe on target platform.") \
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_OPERATIONS_ON_INAPPROPRIATE_TYPE("External code. Operation is safe on target platform.") \
        PSA_AEAD_FINISH_OUTPUT_SIZE(key_type, alg) \
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_CONVERSIONS_WITH_INAPPROPRIATE_TYPE() \
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_OPERATIONS_ON_INAPPROPRIATE_TYPE())


#define MCUXCLPSADRIVER_PSA_AEAD_ENCRYPT_OUTPUT_SIZE(key_type, alg, plaintext_length) \
    (MCUX_CSSL_ANALYSIS_START_SUPPRESS_CONVERSIONS_WITH_INAPPROPRIATE_TYPE("External code. Operation is safe on target platform.") \
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_OPERATIONS_ON_INAPPROPRIATE_TYPE("External code. Operation is safe on target platform.") \
        PSA_AEAD_ENCRYPT_OUTPUT_SIZE(key_type, alg, plaintext_length) \
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_CONVERSIONS_WITH_INAPPROPRIATE_TYPE() \
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_OPERATIONS_ON_INAPPROPRIATE_TYPE())

#define MCUXCLPSADRIVER_PSA_AEAD_DECRYPT_OUTPUT_SIZE(key_type, alg, ciphertext_length) \
    (MCUX_CSSL_ANALYSIS_START_SUPPRESS_CONVERSIONS_WITH_INAPPROPRIATE_TYPE("External code. Operation is safe on target platform.") \
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_OPERATIONS_ON_INAPPROPRIATE_TYPE("External code. Operation is safe on target platform.") \
        PSA_AEAD_DECRYPT_OUTPUT_SIZE(key_type, alg, ciphertext_length) \
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_CONVERSIONS_WITH_INAPPROPRIATE_TYPE() \
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_OPERATIONS_ON_INAPPROPRIATE_TYPE())

#define MCUXCLPSADRIVER_PSA_MAC_LENGTH(key_type, key_bits, alg) \
    (MCUX_CSSL_ANALYSIS_START_SUPPRESS_CONVERSIONS_WITH_INAPPROPRIATE_TYPE("External code. Operation is safe on target platform.") \
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_OPERATIONS_ON_INAPPROPRIATE_TYPE("External code. Operation is safe on target platform.") \
        PSA_MAC_LENGTH(key_type, key_bits, alg) \
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_CONVERSIONS_WITH_INAPPROPRIATE_TYPE() \
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_OPERATIONS_ON_INAPPROPRIATE_TYPE())

#define MCUXCLPSADRIVER_PSA_KEY_TYPE_ECC_GET_FAMILY(type)  \
    (MCUX_CSSL_ANALYSIS_START_SUPPRESS_CONVERSIONS_WITH_INAPPROPRIATE_TYPE("External code. Operation is safe on target platform.") \
        PSA_KEY_TYPE_ECC_GET_FAMILY(type)  \
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_CONVERSIONS_WITH_INAPPROPRIATE_TYPE())

#define MCUXCLPSADRIVER_PSA_ALG_SIGN_GET_HASH(alg) \
    (MCUX_CSSL_ANALYSIS_START_SUPPRESS_CONVERSIONS_WITH_INAPPROPRIATE_TYPE("External code. Operation is safe on target platform.") \
        PSA_ALG_SIGN_GET_HASH(alg) \
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_CONVERSIONS_WITH_INAPPROPRIATE_TYPE())

#define MCUXCLPSADRIVER_MBEDTLS_BYTE_0(x_) \
    (MCUX_CSSL_ANALYSIS_START_SUPPRESS_CONVERSIONS_WITH_INAPPROPRIATE_TYPE("External code. Operation is safe on target platform.") \
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_OPERATIONS_ON_INAPPROPRIATE_TYPE("External code. Operation is safe on target platform.") \
        MBEDTLS_BYTE_0(x_) \
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_OPERATIONS_ON_INAPPROPRIATE_TYPE() \
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_CONVERSIONS_WITH_INAPPROPRIATE_TYPE())

#define MCUXCLPSADRIVER_MBEDTLS_BYTE_1(x_) \
    (MCUX_CSSL_ANALYSIS_START_SUPPRESS_CONVERSIONS_WITH_INAPPROPRIATE_TYPE("External code. Operation is safe on target platform.") \
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_OPERATIONS_ON_INAPPROPRIATE_TYPE("External code. Operation is safe on target platform.") \
        MBEDTLS_BYTE_1(x_) \
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_CONVERSIONS_WITH_INAPPROPRIATE_TYPE() \
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_OPERATIONS_ON_INAPPROPRIATE_TYPE())

#define MCUXCLPSADRIVER_PSA_ALG_IS_DETERMINISTIC_ECDSA(alg) \
    (MCUX_CSSL_ANALYSIS_START_SUPPRESS_CONVERSIONS_WITH_INAPPROPRIATE_TYPE("External code. Operation is safe on target platform.") \
        PSA_ALG_IS_DETERMINISTIC_ECDSA(alg) \
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_OPERATIONS_ON_INAPPROPRIATE_TYPE())

#define MCUXCLPSADRIVER_PSA_ALG_IS_ECDSA(alg) \
    (MCUX_CSSL_ANALYSIS_START_SUPPRESS_CONVERSIONS_WITH_INAPPROPRIATE_TYPE("External code. Operation is safe on target platform.") \
    PSA_ALG_IS_ECDSA(alg) \
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_CONVERSIONS_WITH_INAPPROPRIATE_TYPE())

/**
 * @}
 */ /* mcuxClPsaDriver_ExternalMacroWrappers */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLPSADRIVER_EXTERNAL_MACRO_WRAPPERS_H_ */

