/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/** \file mcux_psa_s4xx_opaque_mac.c
 *
 * This file contains the implementation of the entry points associated to the
 * mac capability (single-part and multipart) as described by the PSA
 * Cryptoprocessor Driver interface specification
 *
 */

#include "mcux_psa_s4xx_opaque_mac.h"
#include "ele_crypto.h"
#include "mcux_psa_s4xx_common_key_management.h"

#include "mcux_psa_s4xx_common_init.h"

/* To be able to include the PSA style configuration */
#include "mbedtls/build_info.h"

extern ele_s4xx_ctx_t g_ele_ctx;

/* It is essential to have NVM Manager defined with opaque driver. Return PSA_ERROR_NOT_SUPPORTED
 * if the NVM manager is not present. Since psa_crypto_wrapper will be auto-generated, we can't add
 * the check there. hence implementing it in opaque drivers for ELE.
 */
#if !defined(PSA_ELE_S4XX_SD_NVM_MANAGER)
psa_status_t ele_s4xx_opaque_mac_compute(const psa_key_attributes_t *attributes,
                                         const uint8_t *key_buffer,
                                         size_t key_buffer_size, psa_algorithm_t alg,
                                         const uint8_t *input, size_t input_length,
                                         uint8_t *mac, size_t mac_size,
                                         size_t *mac_length)
{
    return PSA_ERROR_NOT_SUPPORTED;
}

#else

psa_status_t get_ele_mac_alg(psa_algorithm_t alg, psa_key_type_t key_type,
                             key_permitted_alg_t *ele_alg)
{
    psa_status_t status = PSA_ERROR_NOT_SUPPORTED;

#if defined(PSA_WANT_ALG_CMAC)
    if (PSA_ALG_FULL_LENGTH_MAC(alg) == PSA_ALG_CMAC) {
        if (key_type == PSA_KEY_TYPE_AES) {
            *ele_alg = alg;
            status = PSA_SUCCESS;
        }
    } else
#endif /* PSA_WANT_ALG_CMAC */
#if defined(PSA_WANT_ALG_HMAC)
    if (PSA_ALG_IS_HMAC(alg)) {
        switch (PSA_ALG_HMAC_GET_HASH(alg)) {
            case PSA_ALG_SHA_256:
            case PSA_ALG_SHA_384:
                break;
            default:
                return PSA_ERROR_NOT_SUPPORTED;
        }
        if (key_type == PSA_KEY_TYPE_HMAC) {
            *ele_alg = alg;
            status = PSA_SUCCESS;
        }
    } else
#endif /* PSA_WANT_ALG_HMAC */
    {
        status = PSA_ERROR_NOT_SUPPORTED;
    }

    return status;
}

/*
 * TBD - Wrapper for mac verify doesn't exist in psa driver wrapper file. It internally calls the
 * MAC computer and then does a memcmp. hence no wrapper in this file for verify even though
 * ELE supports it.
 */

psa_status_t ele_s4xx_opaque_mac_compute(const psa_key_attributes_t *attributes,
                                         const uint8_t *key_buffer,
                                         size_t key_buffer_size, psa_algorithm_t alg,
                                         const uint8_t *input, size_t input_length,
                                         uint8_t *mac, size_t mac_size,
                                         size_t *mac_length)
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    status_t ele_status = kStatus_Fail;
    psa_key_type_t key_type = psa_get_key_type(attributes);
    key_permitted_alg_t ele_alg = 0;
    uint32_t macHandleID = 0;
    uint32_t verify_status = 0;
    uint16_t length = 0;
    uint32_t key_id = 0;
    ele_mac_t macParam = { 0 };

    /* Chec input*/
    if (!input || !input_length) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Check MAC buffer */
    if (!mac || !mac_length) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Check key type and get ele algorithm */
    status = get_ele_mac_alg(alg, key_type, &ele_alg);
    if (status != PSA_SUCCESS) {
        return status;
    }

    /* Check and get key from key buffer */
    if (ele_get_key_id_from_buf(attributes, key_buffer, key_buffer_size, &key_id)) {
        if (status != PSA_SUCCESS) {
            return status;
        }
    }

    macParam.alg = ele_alg;
    macParam.key_id = key_id;
    macParam.mac = (uint32_t) mac;
    macParam.mac_size = mac_size;
    macParam.mode = kMAC_Generate;
    macParam.payload = (uint32_t) input;
    macParam.payload_size = input_length;

    ele_status = ELE_OpenMacService(S3MU, g_ele_ctx.key_store_handle, &macHandleID);
    status = ele_to_psa_status(ele_status);
    if (status != PSA_SUCCESS) {
        goto out;
    }

    ele_status = ELE_Mac(S3MU,
                         &macParam,
                         &verify_status,
                         &length);
    status = ele_to_psa_status(ele_status);

    if (status == PSA_SUCCESS) {
        *mac_length = (uint32_t) length;
    }

    ele_status = ELE_CloseMacService(S3MU, macHandleID);
    status = ele_to_psa_status(ele_status);

out:
    if (mcux_mutex_unlock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_BAD_STATE;
    }

    return status;
}

/* These are left as function prototypes for multi-part operations. Not implemented now
 * as ELE doesn't support them. When implemnting them define ele_mac_operation_t as needed
 * in ele_crypto_primitives.h
 */
#if 0
/** \defgroup psa_mac PSA driver entry points for MAC operations
 *
 *  Entry points for MAC computation and verification as described by the PSA
 *  Cryptoprocessor Driver interface specification
 *
 *  @{
 */
psa_status_t ele_s4xx_opaque_mac_sign_setup(ele_mac_operation_t *operation,
                                            const psa_key_attributes_t *attributes,
                                            const uint8_t *key_buffer,
                                            size_t key_buffer_size, psa_algorithm_t alg)
{
    return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t ele_s4xx_opaque_mac_verify_setup(ele_mac_operation_t *operation,
                                              const psa_key_attributes_t *attributes,
                                              const uint8_t *key_buffer,
                                              size_t key_buffer_size, psa_algorithm_t alg)
{
    return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t ele_s4xx_opaque_mac_update(ele_mac_operation_t *operation,
                                        const uint8_t *input, size_t input_length)
{
    return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t ele_s4xx_opaque_mac_sign_finish(ele_mac_operation_t *operation,
                                             uint8_t *mac, size_t mac_size,
                                             size_t *mac_length)
{
    return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t ele_s4xx_opaque_mac_verify_finish(ele_mac_operation_t *operation,
                                               const uint8_t *mac, size_t mac_length)
{
    return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t ele_s4xx_opaque_mac_abort(ele_mac_operation_t *operation)
{
    return PSA_ERROR_NOT_SUPPORTED;
}

#endif
#endif
/** @} */ // end of psa_mac
