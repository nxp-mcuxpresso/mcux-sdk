/*
 * Copyright 2022-2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/** \file mcux_psa_s4xx_opaque_key_generation.c
 *
 * This file contains the implementation of the entry points associated to the
 * key generation (i.e. random generation and extraction of public keys) as
 * described by the PSA Cryptoprocessor Driver interface specification
 *
 */

/* Included to get definiition of PSA_CRYPTO_ELE_S4XX_LOCATION. */
#include "ele_s4xx.h"

#include "mcux_psa_s4xx_opaque_key_generation.h"
#include "mcux_psa_s4xx_common_key_management.h"
#include "mcux_psa_s4xx_common_init.h"

#include "psa/crypto.h"

/* It is essential to have NVM Manager defined with opaque driver. Return PSA_ERROR_NOT_SUPPORTED
 * if the NVM manager is not present. Since psa_crypto_wrapper will be auto-generated, we can't add
 * the check there. hence implementing it in opaque drivers for ELE.
 */
#if !defined(PSA_ELE_S4XX_SD_NVM_MANAGER)

psa_status_t ele_s4xx_opaque_destroy_key(const psa_key_attributes_t *attributes,
                                         uint8_t *key_buffer, size_t key_buffer_size)
{
    return PSA_ERROR_NOT_SUPPORTED;
}

size_t ele_s4xx_opaque_size_function(psa_key_type_t key_type, size_t key_bits)
{
    /* We will save the key ID returned by ELE FW in this buffer */
    return 0;
}

psa_status_t ele_s4xx_opaque_export_public_key(const psa_key_attributes_t *attributes,
                                               const uint8_t *key_buffer,
                                               size_t key_buffer_size, uint8_t *data,
                                               size_t data_size, size_t *data_length)
{
    return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t ele_s4xx_opaque_generate_key(const psa_key_attributes_t *attributes,
                                          uint8_t *key_buffer, size_t key_buffer_size,
                                          size_t *key_buffer_length)
{
    return PSA_ERROR_NOT_SUPPORTED;
}

#else

extern ele_s4xx_ctx_t g_ele_ctx;

static inline psa_status_t psa_validate_ele_key_type_and_size(enum _key_type_t key_type,
                                                              size_t bits)
{
    switch (key_type) {
        case kKeyType_AES:
            if (bits != 128 && bits != 192 && bits != 256) {
                return PSA_ERROR_INVALID_ARGUMENT;
            }
            break;
        case kKeyType_HMAC:
            if (bits != 224 && bits != 256 && bits != 384 && bits != 512) {
                return PSA_ERROR_INVALID_ARGUMENT;
            }
            break;
        case kKeyType_ECC_KEY_PAIR_BRAINPOOL_R1:
            if (bits != 224 && bits != 256 && bits != 384) {
                return PSA_ERROR_INVALID_ARGUMENT;
            }
            break;
        case kKeyType_ECC_KEY_PAIR_SECP_R1_NIST:
            if (bits != 224 && bits != 256 && bits != 384 && bits != 521) {
                return PSA_ERROR_INVALID_ARGUMENT;
            }
            break;
        case kKeyType_RSA_KEY_PAIR:
            if (bits != 2048 && bits != 3072 && bits != 4096) {
                return PSA_ERROR_INVALID_ARGUMENT;
            }
            break;
        default:
            return PSA_ERROR_NOT_SUPPORTED;
    }

    return PSA_SUCCESS;

}

static inline psa_status_t psa_key_type_to_ele(psa_key_type_t key_type, uint16_t *ele_type)
{

    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;
    /* ELE key types are compatible with PSA Key types. So just assign for now.
     * However if a key-type is not supported by ele, we might not get the right error from ELE FW
     * Also an additional call to FW. TBD - should we do checks here ??
     */
    *ele_type = key_type;

    switch (*ele_type) {
        case kKeyType_AES:
        case kKeyType_HMAC:
        case kKeyType_ECC_KEY_PAIR_BRAINPOOL_R1:
        case kKeyType_ECC_KEY_PAIR_SECP_R1_NIST:
        case kKeyType_RSA_KEY_PAIR:
            status = PSA_SUCCESS;
            break;
        default:
            status = PSA_ERROR_NOT_SUPPORTED;
            break;
    }

    return status;
}

static inline psa_status_t psa_key_usage_to_ele(psa_key_type_t key_type,
                                                psa_key_usage_t key_usage,
                                                uint32_t *ele_usage)
{

    /* ELE key Usage is compatible with PSA Key usage. So just assign for now.
     * However if a key-type is not supported by ele, we might not get the right error from ELE FW
     * Also an additional call to FW. TBD - should we do checks here ??
     * EXPORT_USAGE should not be allowed at all/.
     */
    if (key_usage & ~ELE_KEY_USAGE_MASK) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Further checks can be added -> what key type supports what key usage here */

    /* ELE FW doesn't allow key generation without appropriate usage set. Hence return error */
    if (!key_usage) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    *ele_usage = key_usage;

    return PSA_SUCCESS;
}

static inline psa_status_t psa_key_algo_to_ele(psa_algorithm_t key_algo, uint32_t *ele_algo)
{
    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;

    /* ELE key Algo is compatible with PSA Key Algo. So just assign for now and check if it is upported by ELE
     * There would be further correspondence between key type and algo. Not checking it for now.
     * Once errors are more granular from ELE, we may be able to give better errors to user.
     */

    *ele_algo = key_algo;

    switch (*ele_algo) {
        case kPermitted_HMAC_SHA256:
        case kPermitted_HMAC_SHA384:
        case kPermitted_CMAC:
        case kPermitted_CTR:
        case kPermitted_ECB:
        case kPermitted_CBC:
        case kPermitted_All_Cipher:
        case kPermitted_CCM:
        case kPermitted_GCM:
        case kPermitted_All_AEAD:
        case kPermitted_KEK_CCM:
        case kPermitted_KEK_GCM:
        case kPermitted_RSA_PKCS1_V1_5_SHA1:
        case kPermitted_RSA_PKCS1_V1_5_SHA224:
        case kPermitted_RSA_PKCS1_V1_5_SHA256:
        case kPermitted_RSA_PKCS1_V1_5_SHA384:
        case kPermitted_RSA_PKCS1_V1_5_SHA512:
        case kPermitted_RSA_PKCS1_V1_5_ANY_HASH:
        case kPermitted_RSA_PKCS1_PSS_MGF1_SHA1:
        case kPermitted_RSA_PKCS1_PSS_MGF1_SHA224:
        case kPermitted_RSA_PKCS1_PSS_MGF1_SHA256:
        case kPermitted_RSA_PKCS1_PSS_MGF1_SHA384:
        case kPermitted_RSA_PKCS1_PSS_MGF1_SHA512:
        case kPermitted_RSA_PKCS1_PSS_MGF1_ANY_HASH:
        case kPermitted_ECDSA_SHA224:
        case kPermitted_ECDSA_SHA256:
        case kPermitted_ECDSA_SHA512:
        case kPermitted_ECDSA_SHA384:
        case kPermitted_ECDH_SHA_256:
        case kPermitted_TLS_1_2_PRF_ECDH_SHA256:
        case kPermitted_TLS_1_2_PRF_ECDH_SHA384:
            status = PSA_SUCCESS;
            break;
        default:
            status = PSA_ERROR_NOT_SUPPORTED;
            break;
    }

    return status;
}

/* This can be set to any value. Using 0x1 to avoid clash with LOCAL STORAGE */
#define ELE_LOCATION_STANDARD               0x1
#define ELE_LOCATION_IMPORT_KEY_EL2GO       0xE00000
#define ELE_LOCATION_IMPORT_DATA_EL2GO      0xE08000
#define ELE_LOCATION_IMPORT_KEY             0xC00200

static inline psa_status_t psa_key_lifetime_to_ele(psa_key_lifetime_t key_lifetime,
                                                   uint32_t *ele_lifetime)
{

    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(key_lifetime);
    uint32_t ele_location = 0;

    switch (location) {
        case PSA_CRYPTO_ELE_S4XX_LOCATION:
            ele_location = ELE_LOCATION_STANDARD;
            break;
        default:
            return PSA_ERROR_INVALID_ARGUMENT;
    }

    psa_key_persistence_t persistence = PSA_KEY_LIFETIME_GET_PERSISTENCE(key_lifetime);

    *ele_lifetime = PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(persistence, ele_location);

    return PSA_SUCCESS;
}

psa_status_t ele_internal_gen_keypair(const psa_key_attributes_t *attributes,
                                      uint8_t *key_buffer, size_t key_buffer_size,
                                      size_t *key_buffer_length)
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    status_t ele_status = kStatus_Fail;
    psa_key_lifetime_t lifetime = psa_get_key_lifetime(attributes);
    psa_key_type_t key_type = psa_get_key_type(attributes);
    psa_key_usage_t key_usage = psa_get_key_usage_flags(attributes);
    psa_algorithm_t key_algo = psa_get_key_algorithm(attributes);
    psa_key_id_t pers_key_id = psa_get_key_id(attributes);
    size_t key_bits = psa_get_key_bits(attributes);
    ele_gen_key_t NISTkeyGenParam = { 0 };
    uint32_t key_id = 0;
    uint16_t size = 0;
    bool sync = false;
    bool mono = false;

    if (key_buffer_size < sizeof(key_id)) {
        return PSA_ERROR_INSUFFICIENT_MEMORY;
    }

    if ((status = psa_key_type_to_ele(key_type, &NISTkeyGenParam.key_type)) != PSA_SUCCESS) {
        return status;
    }

    if ((status = psa_validate_ele_key_type_and_size(key_type, key_bits))  != PSA_SUCCESS) {
        return status;
    }

    if ((status =
             psa_key_usage_to_ele(key_type, key_usage,
                                  &NISTkeyGenParam.key_usage)) != PSA_SUCCESS) {
        return status;
    }

    if ((status = psa_key_algo_to_ele(key_algo, &NISTkeyGenParam.permitted_alg)) != PSA_SUCCESS) {
        return status;
    }

    if ((status =
             psa_key_lifetime_to_ele(lifetime, &NISTkeyGenParam.key_lifetime)) != PSA_SUCCESS) {
        return status;
    }

    if ((status = get_ele_key_group(lifetime, &NISTkeyGenParam.key_group)) != PSA_SUCCESS) {
        return status;
    }

    NISTkeyGenParam.key_lifecycle = kKeylifecycle_Open;         /* TBD -> how to fill this ??? - May be get current lifecycle */
    NISTkeyGenParam.key_size      = key_bits;

    /* We are not exporting key here */
    NISTkeyGenParam.pub_key_addr  = 0;
    NISTkeyGenParam.pub_key_size  = 0;
    NISTkeyGenParam.key_id  = 0;

    /* For peristent keys set sync as true*/
    if (!PSA_KEY_LIFETIME_IS_VOLATILE(lifetime)) {
        NISTkeyGenParam.key_id = pers_key_id;
        sync = true;
    }

    if (mcux_mutex_lock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_COMMUNICATION_FAILURE;
    }

    ele_status = ELE_GenerateKey(S3MU,
                                 g_ele_ctx.key_management_handle,
                                 &NISTkeyGenParam,
                                 &key_id,
                                 &size,
                                 mono,
                                 sync);
    status = ele_to_psa_status(ele_status);

    /* Check if key_id generated is same as passed to the ELE */
    if (status == PSA_SUCCESS && !PSA_KEY_LIFETIME_IS_VOLATILE(lifetime)) {
        if (key_id != pers_key_id) {
            status = PSA_ERROR_HARDWARE_FAILURE;
        }
    }

    if (mcux_mutex_unlock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_BAD_STATE;
    }

    /* The key_id returned needs to be saved in data for perisstent keys for now */
    memcpy(key_buffer, (void *) &key_id, sizeof(key_id));
    *key_buffer_length = sizeof(key_id);

    return status;
}

/** \defgroup psa_key_generation PSA driver entry points for key handling
 *
 *  Entry points for random key generation and key format manipulation and
 *  translation as described by the PSA Cryptoprocessor Driver interface
 *  specification
 *
 *  @{
 */
psa_status_t ele_s4xx_opaque_generate_key(const psa_key_attributes_t *attributes,
                                          uint8_t *key_buffer, size_t key_buffer_size,
                                          size_t *key_buffer_length)
{


    psa_key_type_t key_type = psa_get_key_type(attributes);
    psa_status_t err = PSA_ERROR_NOT_SUPPORTED;

    /* Initialise the return value to 0 */
    *key_buffer_length = 0;

    /* These checks are mainly to check WANT_KEY_TYPE */
    if (PSA_KEY_TYPE_IS_KEY_PAIR(key_type)) {
#if defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_GENERATE)
        if (PSA_KEY_TYPE_IS_ECC(key_type)) {
            if (PSA_KEY_TYPE_ECC_GET_FAMILY(key_type) ==
                PSA_ECC_FAMILY_BRAINPOOL_P_R1 ||
                PSA_KEY_TYPE_ECC_GET_FAMILY(key_type) ==
                PSA_ECC_FAMILY_SECP_R1) {
                err = ele_internal_gen_keypair(
                    attributes, key_buffer, key_buffer_size, key_buffer_length);
            }
        } else
#endif /* PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_GENERATE */
#if defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_GENERATE)
        if (PSA_KEY_TYPE_IS_RSA(key_type)) {
            err = ele_internal_gen_keypair(
                attributes, key_buffer, key_buffer_size, key_buffer_length);
        }
#endif /* PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_GENERATE */
    } else if (PSA_KEY_TYPE_IS_UNSTRUCTURED(key_type)) {
#if defined(PSA_WANT_KEY_TYPE_AES) || defined(PSA_WANT_KEY_TYPE_HMAC)
        if (key_type == PSA_KEY_TYPE_AES || key_type == PSA_KEY_TYPE_HMAC) {
            err = ele_internal_gen_keypair(
                attributes, key_buffer, key_buffer_size, key_buffer_length);
        }
#endif /* PSA_WANT_KEY_TYPE_AES || PSA_WANT_KEY_TYPE_HMAC */
    }

    return err;
}

/* Default RSA public exponent is 65537, which has a length of 3 bytes */
#define DEFAULT_RSA_PUB_EXP_LEN 3

static psa_status_t export_rsa_public_key(psa_key_type_t key_type,
                                          uint32_t key_id,
                                          size_t key_bits,
                                          uint8_t *data,
                                          size_t data_size, size_t *data_length)
{
    uint16_t out_size = 0;

    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    status_t ele_status = kStatus_Fail;
    /* Calculate the end of buffer */
    uint8_t *pos = data + data_size;
    /* Allocate tmp based on RSA key size */
    int exponent = 65537;
    uint32_t size = key_bits / 8;
#if defined(USE_MALLOC)
    uint8_t *tmp;
#else
    uint8_t tmp[MAX_RSA_KEYSIZE];
    size = MAX_RSA_KEYSIZE;
#endif

    if (key_type != kKeyType_RSA_KEY_PAIR) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* the size should be what is required for AS format. Need to check how to calculate that */
    if (data_size < key_bits / 8) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

#if defined(USE_MALLOC)
    tmp = malloc(key_bits / 8);
    if (!tmp) {
        return PSA_ERROR_INSUFFICIENT_MEMORY;
    }
#endif

    memset(tmp, 0, size);
    memset(data, 0, data_size);

    if (mcux_mutex_lock(&ele_hwcrypto_mutex)) {
        free(tmp);
        return PSA_ERROR_COMMUNICATION_FAILURE;
    }

    ele_status = ELE_GeneratePubKey(S3MU, g_ele_ctx.key_store_handle, key_id,
                                    (uint32_t *) tmp, data_size, &out_size);
    status = ele_to_psa_status(ele_status);

    if (mcux_mutex_unlock(&ele_hwcrypto_mutex)) {
        free(tmp);
        return PSA_ERROR_BAD_STATE;
    }

    if (status == PSA_SUCCESS) {
        int ret = mcux_write_rsa_pubkey_in_asn(&pos, data, tmp, out_size, exponent);
        /* If data length is 0, return error */
        if (!ret) {
            status = PSA_ERROR_BAD_STATE;
        }

        /* The mcux_write_rsa_pubkey_in_asn function write to the end of the buffer.
         * Move the data to the beginning and erase remaining data
         * at the original location. */
        if (2 * (size_t) ret <= data_size) {
            memcpy(data, data + data_size - ret, ret);
            memset(data + data_size - ret, 0, ret);
        } else if ((size_t) ret < data_size) {
            memmove(data, data + data_size - ret, ret);
            memset(data + ret, 0, data_size - ret);
        }

        *data_length = ret;

    }

#if defined(USE_MALLOC)
    /* Free the allocated buffer */
    free(tmp);
#endif

    return status;
}

static psa_status_t export_ecc_public_key(psa_key_type_t key_type,
                                          uint32_t key_id, uint8_t *data,
                                          size_t data_size, size_t *data_length)
{
    uint16_t out_size = 0;
    /* Pointer to offset 1 of the buffer as ECC key will have 0x4 at first offset */
    uint8_t *tmp = data + 1;
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    status_t ele_status = kStatus_Fail;

    if (key_type != kKeyType_ECC_KEY_PAIR_SECP_R1_NIST &&
        key_type != kKeyType_ECC_KEY_PAIR_BRAINPOOL_R1) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if (mcux_mutex_lock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_COMMUNICATION_FAILURE;
    }

    ele_status = ELE_GeneratePubKey(S3MU, g_ele_ctx.key_store_handle, key_id,
                                    (uint32_t *) tmp, data_size - 1, &out_size);
    status = ele_to_psa_status(ele_status);

    if (mcux_mutex_unlock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_BAD_STATE;
    }

    /* ECC key will have 0x4 at first offset */
    *data = 0x4;
    *data_length = out_size + 1;

    return status;
}

psa_status_t ele_s4xx_opaque_export_public_key(const psa_key_attributes_t *attributes,
                                               const uint8_t *key_buffer,
                                               size_t key_buffer_size, uint8_t *data,
                                               size_t data_size, size_t *data_length)
{
#if !defined(PSA_ELE_S4XX_SD_NVM_MANAGER)
    return PSA_ERROR_NOT_SUPPORTED;
#endif

    uint32_t key_id;
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_type_t key_type = psa_get_key_type(attributes);
    size_t key_bits = psa_get_key_bits(attributes);

    if (!data || data_size < PSA_EXPORT_PUBLIC_KEY_OUTPUT_SIZE(key_type, key_bits)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if (!PSA_KEY_TYPE_IS_ECC(key_type) && !PSA_KEY_TYPE_IS_RSA(key_type)) {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    status = ele_get_key_id_from_buf(attributes, key_buffer, key_buffer_size, &key_id);
    if (status != PSA_SUCCESS) {
        return status;
    }

    if (PSA_KEY_TYPE_IS_ECC(key_type)) {
        status = export_ecc_public_key(key_type, key_id, data,
                                       data_size, data_length);
    } else
    if (PSA_KEY_TYPE_IS_RSA(key_type)) {
        status = export_rsa_public_key(key_type, key_id, key_bits,
                                       data, data_size, data_length);
    } else {
        status = PSA_ERROR_NOT_SUPPORTED;
    }

    return status;
}

psa_status_t ele_s4xx_opaque_destroy_key(const psa_key_attributes_t *attributes,
                                         uint8_t *key_buffer, size_t key_buffer_size)
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    status_t ele_status = kStatus_Fail;
    psa_key_lifetime_t lifetime = psa_get_key_lifetime(attributes);
    bool sync = false;
    bool mono = false;
    uint32_t key_id;

    if (key_buffer_size < sizeof(key_id)) {
        return PSA_ERROR_INSUFFICIENT_MEMORY;
    }

    status = ele_get_key_id_from_buf(attributes, key_buffer, key_buffer_size, &key_id);
    if (status != PSA_SUCCESS) {
        return status;
    }

    /* For peristent keys set sync as true*/
    if (!PSA_KEY_LIFETIME_IS_VOLATILE(lifetime)) {
        sync = true;
    }

    if (mcux_mutex_lock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_COMMUNICATION_FAILURE;
    }

    ele_status = ELE_DeleteKey(S3MU, g_ele_ctx.key_management_handle, key_id, mono, sync);
    status = ele_to_psa_status(ele_status);

    if (mcux_mutex_unlock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_BAD_STATE;
    }

    return status;
}

size_t ele_s4xx_opaque_size_function(psa_key_type_t key_type, size_t key_bits)
{
    /* We will save the key ID returned by ELE FW in this buffer */
    return sizeof(uint32_t);
}

#endif
/** @} */ // end of psa_key_generation
