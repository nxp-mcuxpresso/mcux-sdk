/*
 * Copyright 2022-2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/** \file mcux_psa_els_pkc_opaque_key_generation.c
 *
 * This file contains the implementation of the entry points associated to the
 * key generation (i.e. random generation and extraction of public keys) as
 * described by the PSA Cryptoprocessor Driver interface specification
 *
 */
#include "mcuxClEls.h"
#include "mcuxClPsaDriver_Functions.h"
#include "mcux_psa_els_pkc_opaque_key_generation.h"
#include "mcuxClPsaDriver_Oracle.h"

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
#include "mcux_psa_els_pkc_common_init.h"
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

size_t els_pkc_opaque_size_function_key_buff_size(mbedtls_svc_key_id_t key_id)
{
    size_t key_buffer_size=0;

#if defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS)
    if ((bool)psa_key_id_is_builtin(MBEDTLS_SVC_KEY_ID_GET_KEY_ID(key_id)))
    {

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

        psa_status_t status = mcuxClPsaDriver_Oracle_GetBuiltinKeyBufferSize(key_id,
                                                                             &key_buffer_size);
        if (status != PSA_SUCCESS)
        {
          key_buffer_size = 0;
        }

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */
    }
#endif
    return key_buffer_size;
}

/** \defgroup psa_key_generation PSA driver entry points for key handling
 *
 *  Entry points for random key generation and key format manipulation and
 *  translation as described by the PSA Cryptoprocessor Driver interface
 *  specification
 *
 *  @{
 */
psa_status_t els_pkc_opaque_generate_key(const psa_key_attributes_t *attributes,
                                          uint8_t *key_buffer, size_t key_buffer_size,
                                          size_t *key_buffer_length)
{
    psa_status_t status;

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    /* The driver handles multiple storage locations,
    call it first then default to builtin driver */
    status = mcuxClPsaDriver_psa_driver_wrapper_key_generate(
                    attributes, key_buffer, key_buffer_size, key_buffer_length );

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    return status;

}


psa_status_t els_pkc_opaque_export_public_key(const psa_key_attributes_t *attributes,
                                               const uint8_t *key_buffer,
                                               size_t key_buffer_size, uint8_t *data,
                                               size_t data_size, size_t *data_length)
{
    psa_status_t status;

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    /* The driver handles multiple storage locations,
    call it first then default to builtin driver */
    status = mcuxClPsaDriver_psa_driver_wrapper_export_public_key(attributes,
                                                        key_buffer,
                                                        key_buffer_size,
                                                        data,
                                                        data_size,
                                                        data_length);

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    return status;
}

psa_status_t els_pkc_opaque_export_key(const psa_key_attributes_t *attributes,
                                               const uint8_t *key_buffer,
                                               size_t key_buffer_size, uint8_t *data,
                                               size_t data_size, size_t *data_length)
{
    psa_status_t status;

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    status = mcuxClPsaDriver_psa_driver_wrapper_exportKey(attributes,
                                                        key_buffer,
                                                        key_buffer_size,
                                                        data,
                                                        data_size,
                                                        data_length);

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    return status;
}

psa_status_t els_pkc_opaque_destroy_key(const psa_key_attributes_t *attributes,
                                         uint8_t *key_buffer, size_t key_buffer_size)
{
    psa_status_t status=PSA_SUCCESS;

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    // TBD - Code to be added once corresponding functionality is available in els_pkc_crypto

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    return status;

}

size_t els_pkc_opaque_size_function(const psa_key_attributes_t *attributes,
    const uint8_t *data,size_t data_length)
{
    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(
                                      psa_get_key_lifetime( attributes ) );
    size_t key_buffer_size=0;
    if(false == (MCUXCLPSADRIVER_IS_LOCAL_STORAGE(location)) )
    {
        psa_status_t status = mcuxClPsaDriver_Oracle_GetKeyBufferSizeFromKeyData(
                    attributes,
                    data,
                    data_length,
                    &key_buffer_size);
        if (PSA_SUCCESS != status)
        {
            key_buffer_size = 0;
        }
    }
    return key_buffer_size;
}

psa_status_t els_pkc_opaque_import_key(const psa_key_attributes_t *attributes,
    const uint8_t *data, size_t data_length, uint8_t *key_buffer,
    size_t key_buffer_size, size_t *key_buffer_length, size_t *bits)
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(
                                      psa_get_key_lifetime( attributes ) );
    
    if(false == (MCUXCLPSADRIVER_IS_LOCAL_STORAGE(location)) )        
    {                                                                 
        mcuxClKey_Descriptor_t key_descriptor = {0};
                                                                      
        /* prepare the key container as expected by oracle */
        key_descriptor.container.pData    = (uint8_t *)key_buffer;
        key_descriptor.container.length   = (uint16_t)key_buffer_size;
        key_descriptor.container.used     = (uint16_t)key_buffer_size;
        key_descriptor.container.pAuxData = (void *)attributes;

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

        status = mcuxClPsaDriver_Oracle_ImportKey(&key_descriptor,
                                                  data,
                                                  data_length,
                                                  key_buffer_length,
                                                  bits);

        if (PSA_ERROR_NOT_SUPPORTED == status)
        {
            *key_buffer_length = data_length;
        }

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */
    }
    else
    {
        /* transparent key location case*/
        status = PSA_ERROR_NOT_SUPPORTED;
    }
    return status;

}

//refers to oracle 
psa_status_t els_pkc_opaque_get_builtin_key(psa_drv_slot_number_t slot_number,
    psa_key_attributes_t *attributes,
    uint8_t *key_buffer, size_t key_buffer_size, size_t *key_buffer_length)
{
    psa_status_t status = PSA_ERROR_DOES_NOT_EXIST;

#if defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS)
    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(
                                      psa_get_key_lifetime( attributes ) );
    if (false == (MCUXCLPSADRIVER_IS_LOCAL_STORAGE(location)))
    {
#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
        if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
            return PSA_ERROR_GENERIC_ERROR;
        }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

        status = mcuxClPsaDriver_Oracle_GetBuiltinKeyBuffer(
            attributes,
            key_buffer, key_buffer_size, key_buffer_length);
        if ((PSA_SUCCESS == status) || (PSA_ERROR_BUFFER_TOO_SMALL == status))
        {
            return status;
        }
        if (PSA_ERROR_INVALID_ARGUMENT != status)
        {
            return status;
        }

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
        if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
            return PSA_ERROR_GENERIC_ERROR;
        }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */
    }
#endif // defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS)
    return status;
}

psa_status_t els_pkc_opaque_key_agreement( const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *peer_key,
    size_t peer_key_length,
    uint8_t *shared_secret,
    size_t shared_secret_size,
    size_t *shared_secret_length)
{
    psa_status_t status;

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    status = mcuxClPsaDriver_psa_driver_wrapper_key_agreement( attributes,
                                                    key_buffer,
                                                    key_buffer_size,
                                                    alg,
                                                    peer_key,
                                                    peer_key_length,
                                                    shared_secret,
                                                    shared_secret_size,
                                                    shared_secret_length );

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    return status;
}
/** @} */ // end of psa_key_generation
