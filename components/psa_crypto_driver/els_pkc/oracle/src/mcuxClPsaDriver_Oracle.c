/*
 * Copyright 2022-2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <mcuxClPsaDriver_Oracle.h>
#include <mcuxClPsaDriver_Oracle_Utils.h>
#include <mcuxClPsaDriver_Oracle_Macros.h>
#include <mcuxClPsaDriver.h>

#include <mbedtls/platform.h>
#include <string.h>

/* If TF-M Builtin keys are being used in project,
 then use rw61x specific plat builtin keys */
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)
#include "tfm_crypto_defs.h"
#include "tfm_plat_crypto_keys.h"
#include "mcuxClPsaDriver_Oracle_Interface_builtin_key_ids.h"
#endif /* PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER */

#include "mcuxClPsaDriver_Oracle_ElsUtils.h"

#include <internal/mcuxClPsaDriver_Internal.h>
#include <internal/mcuxClKey_Types_Internal.h>
#include <internal/mcuxClKey_Functions_Internal.h>

#if !defined(MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER)
#define MBEDTLS_NXP_DIE_EL2GOIMPORT_KEK_SK_ID    NXP_DIE_EL2GOIMPORT_KEK_SK_ID
#define MBEDTLS_NXP_DIE_EL2GOIMPORTTFM_KEK_SK_ID NXP_DIE_EL2GOIMPORTTFM_KEK_SK_ID
#define MBEDTLS_NXP_DIE_EL2GOIMPORT_AUTH_SK_ID   NXP_DIE_EL2GOIMPORT_AUTH_SK_ID
#define MBEDTLS_NXP_DIE_EL2GOCONN_AUTH_PRK_ID    NXP_DIE_EL2GOCONN_AUTH_PRK_ID
#define MBEDTLS_NXP_DIE_EL2GOATTEST_AUTH_PRK_ID  NXP_DIE_EL2GOATTEST_AUTH_PRK_ID
#else
#define MBEDTLS_NXP_DIE_EL2GOIMPORT_KEK_SK_ID                                                 \
    {                                                                                         \
        .MBEDTLS_PRIVATE(owner) = 0, .MBEDTLS_PRIVATE(key_id) = NXP_DIE_EL2GOIMPORT_KEK_SK_ID \
    }
#define MBEDTLS_NXP_DIE_EL2GOIMPORTTFM_KEK_SK_ID                                                 \
    {                                                                                            \
        .MBEDTLS_PRIVATE(owner) = 0, .MBEDTLS_PRIVATE(key_id) = NXP_DIE_EL2GOIMPORTTFM_KEK_SK_ID \
    }
#define MBEDTLS_NXP_DIE_EL2GOIMPORT_AUTH_SK_ID                                                 \
    {                                                                                          \
        .MBEDTLS_PRIVATE(owner) = 0, .MBEDTLS_PRIVATE(key_id) = NXP_DIE_EL2GOIMPORT_AUTH_SK_ID \
    }
#define MBEDTLS_NXP_DIE_EL2GOCONN_AUTH_PRK_ID                                                 \
    {                                                                                         \
        .MBEDTLS_PRIVATE(owner) = 0, .MBEDTLS_PRIVATE(key_id) = NXP_DIE_EL2GOCONN_AUTH_PRK_ID \
    }
#define MBEDTLS_NXP_DIE_EL2GOATTEST_AUTH_PRK_ID                                                 \
    {                                                                                           \
        .MBEDTLS_PRIVATE(owner) = 0, .MBEDTLS_PRIVATE(key_id) = NXP_DIE_EL2GOATTEST_AUTH_PRK_ID \
    }
#endif

static const mbedtls_svc_key_id_t el2goimport_kek_sk_id    = MBEDTLS_NXP_DIE_EL2GOIMPORT_KEK_SK_ID;
static const mbedtls_svc_key_id_t el2goimporttfm_kek_sk_id = MBEDTLS_NXP_DIE_EL2GOIMPORTTFM_KEK_SK_ID;
static const mbedtls_svc_key_id_t el2goimport_auth_sk_id   = MBEDTLS_NXP_DIE_EL2GOIMPORT_AUTH_SK_ID;

#define RECIPE_STEP_CREATE_NXP_DIE_EL2GOIMPORT_KEK_SK                                                              \
    {                                                                                                              \
        .operation = OP_CKDF, .storage = STORAGE_FINAL_KEY,                                                        \
        .ckdf = {                                                                                                  \
            .source_key_slot           = NXP_DIE_EL2GOOEM_MK_SK_SLOT,                                              \
            .target_key_id             = MBEDTLS_NXP_DIE_EL2GOIMPORT_KEK_SK_ID,                                    \
            .key_properties.word.value = 0x40800021U,                                                              \
            .derivation_data           = {0x00, 0x65, 0x32, 0x67, 0x69, 0x6b, 0x65, 0x6b, 0x5f, 0x73, 0x6b, 0x00}, \
        },                                                                                                         \
    }

const key_recipe_t recipe_el2goimport_kek_sk = {
    .number_of_steps = 1,
    .steps =
        {
            RECIPE_STEP_CREATE_NXP_DIE_EL2GOIMPORT_KEK_SK,
        },
};

#define RECIPE_STEP_CREATE_NXP_DIE_EL2GOIMPORTTFM_KEK_SK                                                           \
    {                                                                                                              \
        .operation = OP_CKDF, .storage = STORAGE_FINAL_KEY,                                                        \
        .ckdf = {                                                                                                  \
            .source_key_slot           = NXP_DIE_EL2GOOEM_MK_SK_SLOT,                                              \
            .target_key_id             = MBEDTLS_NXP_DIE_EL2GOIMPORTTFM_KEK_SK_ID,                                 \
            .key_properties.word.value = 0x40100021U,                                                              \
            .derivation_data           = {0x00, 0x65, 0x32, 0x67, 0x69, 0x74, 0x66, 0x6d, 0x5f, 0x73, 0x6b, 0x00}, \
        },                                                                                                         \
    }

const key_recipe_t recipe_el2goimporttfm_kek_sk = {
    .number_of_steps = 1,
    .steps =
        {
            RECIPE_STEP_CREATE_NXP_DIE_EL2GOIMPORTTFM_KEK_SK,
        },
};

#define RECIPE_STEP_CREATE_NXP_DIE_EL2GOIMPORT_AUTH_SK                                                             \
    {                                                                                                              \
        .operation = OP_CKDF, .storage = STORAGE_FINAL_KEY,                                                        \
        .ckdf = {                                                                                                  \
            .source_key_slot           = NXP_DIE_EL2GOOEM_MK_SK_SLOT,                                              \
            .target_key_id             = MBEDTLS_NXP_DIE_EL2GOIMPORT_AUTH_SK_ID,                                   \
            .key_properties.word.value = 0x40002021U,                                                              \
            .derivation_data           = {0x00, 0x65, 0x32, 0x67, 0x69, 0x61, 0x75, 0x74, 0x5f, 0x73, 0x6b, 0x00}, \
        },                                                                                                         \
    }

const key_recipe_t recipe_el2goimport_auth_sk = {
    .number_of_steps = 1,
    .steps =
        {
            RECIPE_STEP_CREATE_NXP_DIE_EL2GOIMPORT_AUTH_SK,
        },
};

#define RECIPE_STEP_CREATE_NXP_DIE_EL2GOCONN_AUTH_PRK_SEED                                                         \
    {                                                                                                              \
        .operation = OP_CKDF, .storage = STORAGE_TEMP_KEY,                                                         \
        .ckdf = {                                                                                                  \
            .source_key_slot           = NXP_DIE_EL2GOPUBLIC_MK_SK_SLOT,                                           \
            .target_key_id             = MBEDTLS_NXP_DIE_EL2GOCONN_AUTH_PRK_ID,                                    \
            .key_properties.word.value = 0x84000021U,                                                              \
            .derivation_data           = {0x00, 0x65, 0x32, 0x67, 0x63, 0x6f, 0x6e, 0x5f, 0x73, 0x65, 0x00, 0x00}, \
        },                                                                                                         \
    }

#define RECIPE_STEP_CREATE_NXP_DIE_EL2GOCONN_AUTH_PRK                           \
    {                                                                           \
        .operation = OP_KEYGEN, .storage = STORAGE_FINAL_KEY,                   \
        .keygen = {                                                             \
            .target_key_id             = MBEDTLS_NXP_DIE_EL2GOCONN_AUTH_PRK_ID, \
            .key_properties.word.value = 0x80040001U,                           \
        },                                                                      \
    }

const key_recipe_t recipe_el2goconn_auth_prk = {
    .number_of_steps = 2,
    .steps =
        {
            RECIPE_STEP_CREATE_NXP_DIE_EL2GOCONN_AUTH_PRK_SEED,
            RECIPE_STEP_CREATE_NXP_DIE_EL2GOCONN_AUTH_PRK,
        },
};

#define RECIPE_STEP_CREATE_NXP_DIE_EL2GOATTEST_AUTH_PRK_SEED                                                       \
    {                                                                                                              \
        .operation = OP_CKDF, .storage = STORAGE_TEMP_KEY,                                                         \
        .ckdf = {                                                                                                  \
            .source_key_slot           = NXP_DIE_EL2GOPUBLIC_MK_SK_SLOT,                                           \
            .target_key_id             = MBEDTLS_NXP_DIE_EL2GOATTEST_AUTH_PRK_ID,                                  \
            .key_properties.word.value = 0x84000021U,                                                              \
            .derivation_data           = {0x00, 0x65, 0x32, 0x67, 0x61, 0x74, 0x74, 0x5f, 0x73, 0x65, 0x00, 0x00}, \
        },                                                                                                         \
    }

#define RECIPE_STEP_CREATE_NXP_DIE_EL2GOATTEST_AUTH_PRK                           \
    {                                                                             \
        .operation = OP_KEYGEN, .storage = STORAGE_FINAL_KEY,                     \
        .keygen = {                                                               \
            .target_key_id             = MBEDTLS_NXP_DIE_EL2GOATTEST_AUTH_PRK_ID, \
            .key_properties.word.value = 0x80040001U,                             \
        },                                                                        \
    }

const key_recipe_t recipe_el2goattest_auth_prk = {
    .number_of_steps = 2,
    .steps =
        {
            RECIPE_STEP_CREATE_NXP_DIE_EL2GOATTEST_AUTH_PRK_SEED,
            RECIPE_STEP_CREATE_NXP_DIE_EL2GOATTEST_AUTH_PRK,
        },
};

/*  For now assumes that when location is PSA_KEY_LOCATION_S50_TEMP_STORAGE the slot is passed
    in key_buffer (stored in pKey->container.pData) otherwise that pointer is considered to contain
    a plain key. All keys are considered to be alreay loaded into S50 or memory.

    To closer match the use case, the keys should be loaded here.
*/
psa_status_t mcuxClPsaDriver_Oracle_GetBuiltinKeyBufferSize(mbedtls_svc_key_id_t key_id, size_t *key_buffer_size)
{
    psa_status_t status;
    switch (MBEDTLS_SVC_KEY_ID_GET_KEY_ID(key_id))
    {
/* If TF-M Builtin keys are being used in project,
 then use rw61x specific plat builtin keys */
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)
        case TFM_BUILTIN_KEY_ID_EL2GO_CONN_AUTH:
            *key_buffer_size = mcuxClPsaDriver_Oracle_Utils_GetRecipeSize(&recipe_el2goconn_auth_prk);
            status           = PSA_SUCCESS;
            break;
#endif /*PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER*/
#ifdef TFM_PARTITION_INITIAL_ATTESTATION
        case TFM_BUILTIN_KEY_ID_IAK:
            *key_buffer_size = mcuxClPsaDriver_Oracle_Utils_GetRecipeSize(&recipe_el2goattest_auth_prk);
            status           = PSA_SUCCESS;
            break;
#endif // TFM_PARTITION_INITIAL_ATTESTATION
        default:
            status = PSA_ERROR_INVALID_ARGUMENT;
            break;
    }
    return status;
}

psa_status_t mcuxClPsaDriver_Oracle_GetBuiltinKeyBuffer(psa_key_attributes_t *attributes,
                                                        uint8_t *key_buffer,
                                                        size_t key_buffer_size,
                                                        size_t *key_buffer_length)
{
    if (attributes == NULL)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    mbedtls_svc_key_id_t key_id     = psa_get_key_id(attributes);
    size_t required_key_buffer_size = 0;
    psa_status_t status             = mcuxClPsaDriver_Oracle_GetBuiltinKeyBufferSize(key_id, &required_key_buffer_size);
    if (status != PSA_SUCCESS)
    {
        return PSA_ERROR_NOT_PERMITTED;
    }

    if (key_buffer_size < required_key_buffer_size)
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    if (key_buffer == NULL || key_buffer_length == NULL)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    psa_key_usage_t usage = psa_get_key_usage_flags(attributes);
/* If TF-M Builtin keys are being used in project,
 then use rw61x specific plat builtin keys */
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)
    /* Retrieve the usage policy based on the key_id and the user of the key */
    const tfm_plat_builtin_key_policy_t *policy_table = NULL;
    size_t number_of_keys                             = tfm_plat_builtin_key_get_policy_table_ptr(&policy_table);

    for (size_t idx = 0; idx < number_of_keys; idx++)
    {
        if (policy_table[idx].key_id == MBEDTLS_SVC_KEY_ID_GET_KEY_ID(key_id))
        {
            if (policy_table[idx].per_user_policy == 0u)
            {
                usage = policy_table[idx].usage;
            }
            else
            {
                /* The policy depedends also on the user of the key */
                size_t num_users                                       = policy_table[idx].per_user_policy;
                const tfm_plat_builtin_key_per_user_policy_t *p_policy = policy_table[idx].policy_ptr;

                for (size_t j = 0; j < num_users; j++)
                {
                    if (p_policy[j].user == MBEDTLS_SVC_KEY_ID_GET_OWNER_ID(key_id))
                    {
                        usage = p_policy[j].usage;
                        break;
                    }
                }
            }
            break;
        }
    }
#endif /* PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER */
    psa_set_key_usage_flags(attributes, usage);
    psa_status_t psa_status;
    switch (MBEDTLS_SVC_KEY_ID_GET_KEY_ID(key_id))
    {
/* If TF-M Builtin keys are being used in project,
 then use rw61x specific plat builtin keys */
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)
        case TFM_BUILTIN_KEY_ID_EL2GO_CONN_AUTH:
            (void)memcpy(key_buffer, (const uint8_t *)&recipe_el2goconn_auth_prk, required_key_buffer_size);
            *key_buffer_length = required_key_buffer_size;
            psa_set_key_algorithm(attributes, PSA_ALG_ECDSA(PSA_ALG_SHA_256));
            psa_set_key_type(attributes, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1));
            psa_set_key_bits(attributes, 256);
            psa_status = PSA_SUCCESS;
            break;
#endif /* PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER */
#ifdef TFM_PARTITION_INITIAL_ATTESTATION
        case TFM_BUILTIN_KEY_ID_IAK:
            (void)memcpy(key_buffer, (const uint8_t *)&recipe_el2goattest_auth_prk, required_key_buffer_size);
            *key_buffer_length = required_key_buffer_size;
            psa_set_key_algorithm(attributes, PSA_ALG_ECDSA(PSA_ALG_SHA_256));
            psa_set_key_type(attributes, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1));
            psa_set_key_bits(attributes, 256);
            psa_status = PSA_SUCCESS;
            break;
#endif // TFM_PARTITION_INITIAL_ATTESTATION
        default:
            psa_status = PSA_ERROR_INVALID_ARGUMENT;
            break;
    }
    return psa_status;
}

static psa_status_t mcuxClPsaDriver_Oracle_FillKeyDescriptorFromKeySlot(mcuxClEls_KeyIndex_t key_slot,
                                                                        mcuxClKey_Descriptor_t *out_key_descriptor)
{
    psa_status_t psa_status = PSA_SUCCESS;
    mcuxClEls_KeyProp_t key_properties;
    psa_status = mcuxClPsaDriver_Oracle_ElsUtils_GetKeyProperties(key_slot, &key_properties);
    PSA_DRIVER_SUCCESS_OR_EXIT_MSG("mcuxClPsaDriver_Oracle_ElsUtils_GetKeyProperties returned 0x%x", psa_status);
    mcuxClKey_setLoadedKeyData(out_key_descriptor, NULL);
    mcuxClKey_setLoadedKeyLength(out_key_descriptor,
                                 (key_properties.bits.ksize == MCUXCLELS_KEYPROPERTY_KEY_SIZE_128) ? 16u : 32u);
    mcuxClKey_setLoadedKeySlot(out_key_descriptor, key_slot);
    mcuxClKey_setLoadStatus(out_key_descriptor, MCUXCLKEY_LOADSTATUS_COPRO);

exit:
    return psa_status;
}

psa_status_t mcuxClPsaDriver_Oracle_LoadKey(mcuxClKey_Descriptor_t *pKey)
{
    // in pKey pointer pKey->container.pData is assigned to the key buffer loaded in the memory
    // which must not be modified; in this case is including the whole blob
    // pKey->location.pData is the output pointer, which should point to the key when
    // exiting the function
    psa_status_t psa_status = PSA_SUCCESS;

    uint8_t *decrypted_key      = NULL;
    size_t decrypted_key_length = 0;

    psa_key_attributes_t *attributes = (psa_key_attributes_t *)pKey->container.pAuxData;
    psa_key_location_t location      = PSA_KEY_LIFETIME_GET_LOCATION(psa_get_key_lifetime(attributes));

    if (MCUXCLPSADRIVER_IS_S50_TEMP_STORAGE(location))
    {
        /* Assigning value to key slot as per stored pData in case of S50_TEMP_STORAGE*/
        mcuxClEls_KeyIndex_t key_slot =
            (mcuxClEls_KeyIndex_t)PSA_DRIVER_LITTLE_ENDIAN_FROM_U8_TO_U32(&pKey->container.pData[0]);

        psa_status = mcuxClPsaDriver_Oracle_FillKeyDescriptorFromKeySlot(key_slot, pKey);
        PSA_DRIVER_SUCCESS_OR_EXIT_MSG("mcuxClPsaDriver_Oracle_FillKeyDescriptorFromKeySlot failed: 0x%x", psa_status);
    }
    else if (MCUXCLPSADRIVER_IS_S50_KEY_GEN_STORAGE(location))
    {
        mcuxClEls_KeyIndex_t key_slot = 0;
        psa_status = mcuxClPsaDriver_Oracle_Utils_GetSlotFromKeyId(psa_get_key_id(attributes), &key_slot);
        if (psa_status == PSA_ERROR_DOES_NOT_EXIST)
        {
            key_recipe_t *recipe = (key_recipe_t *)pKey->container.pData;
            psa_status = mcuxClPsaDriver_Oracle_Utils_ExecuteKeyRecipe(psa_get_key_id(attributes), // psa reference
                                                                       recipe, &key_slot);
            PSA_DRIVER_SUCCESS_OR_EXIT_MSG("mcuxClPsaDriver_Oracle_Utils_ExecuteKeyRecipe returned 0x%x", psa_status);
        }

        PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error in getting the slot from the key ID");
        psa_status = mcuxClPsaDriver_Oracle_FillKeyDescriptorFromKeySlot(key_slot, pKey);
        PSA_DRIVER_SUCCESS_OR_EXIT_MSG("mcuxClPsaDriver_Oracle_FillKeyDescriptorFromKeySlot failed: 0x%x", psa_status);
    }
    else if (MCUXCLPSADRIVER_IS_S50_BLOB_STORAGE(location))
    {
        mcuxClEls_KeyIndex_t key_slot = 0;
        psa_status = mcuxClPsaDriver_Oracle_Utils_GetSlotFromKeyId(psa_get_key_id(attributes), &key_slot);
        if (psa_status == PSA_ERROR_DOES_NOT_EXIST)
        {
            // derive the NXP_DIE_EL2GOIMPORT_KEK_SK key in the keyslot
            mcuxClEls_KeyIndex_t el2goimport_kek_sk_slot = 0;
            psa_status =
                mcuxClPsaDriver_Oracle_Utils_ExecuteKeyRecipe(el2goimport_kek_sk_id, // psa reference
                                                              &recipe_el2goimport_kek_sk, &el2goimport_kek_sk_slot);
            PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error in dispatching the key command to ELS");

            // load blob on free S50 slot
            psa_status = mcuxClPsaDriver_Oracle_Utils_ExecuteElsKeyIn(psa_get_key_id(attributes), // psa reference
                                                                      pKey->container.pData, pKey->container.length,
                                                                      el2goimport_kek_sk_slot, &key_slot);

            //  regardless of the status of the KEYIN, we need to free the keyslot of the wrap key
            psa_status_t psa_status_remove_key = mcuxClPsaDriver_Oracle_Utils_RemoveKeyFromEls(el2goimport_kek_sk_id);
            if (PSA_SUCCESS != psa_status_remove_key)
            {
                PSA_DRIVER_ERROR("Error,  EL2GOIMPORT_KEK_SK key removal failed");
            }
            PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error,  KeyIn command failed");
        }

        PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error in getting the slot from the key ID");
        psa_status = mcuxClPsaDriver_Oracle_FillKeyDescriptorFromKeySlot(key_slot, pKey);
        PSA_DRIVER_SUCCESS_OR_EXIT_MSG("mcuxClPsaDriver_Oracle_FillKeyDescriptorFromKeySlot failed: 0x%x", psa_status);
    }
    else if (MCUXCLPSADRIVER_IS_S50_ENC_STORAGE(location))
    {
        psa_status = mcuxClPsaDriver_Oracle_Utils_GetSlotFromKeyId(psa_get_key_id(attributes), &pKey->location.slot);
        if (psa_status == PSA_ERROR_DOES_NOT_EXIST)
        {
            // derive the NXP_DIE_EL2GOIMPORTTFM_KEK_SK key in the keyslot
            mcuxClEls_KeyIndex_t el2goimporttfm_kek_sk_slot;
            psa_status = mcuxClPsaDriver_Oracle_Utils_ExecuteKeyRecipe(el2goimporttfm_kek_sk_id, // psa reference
                                                                       &recipe_el2goimporttfm_kek_sk,
                                                                       &el2goimporttfm_kek_sk_slot);
            PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error in dispatching the key command to ELS");

            // parse blob and decrypt data on S50 slot
            psa_status = mcuxClPsaDriver_Oracle_Utils_ExecuteElsDecryptCbc(
                pKey->container.pData, pKey->container.length, &decrypted_key, &decrypted_key_length,
                el2goimporttfm_kek_sk_slot);

            //  regardless of the status of the decryption, we need to free the keyslot of the enc key
            psa_status_t psa_status_remove_key =
                mcuxClPsaDriver_Oracle_Utils_RemoveKeyFromEls(el2goimporttfm_kek_sk_id);
            if (PSA_SUCCESS != psa_status_remove_key)
            {
                PSA_DRIVER_ERROR("Error,  EL2GOIMPORTTFM_KEK_SK key removal failed");
            }
            PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error,  Els Decrypt command failed");

            // Hand over ownership of the decrypted key
            pKey->location.length = decrypted_key_length;
            pKey->location.pData  = decrypted_key;
            decrypted_key         = NULL;
        }

        PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error in getting the slot from the key ID");
        pKey->location.status = MCUXCLKEY_LOADSTATUS_MEMORY;
    }
    else
    {
        pKey->location.status = MCUXCLKEY_LOADSTATUS_MEMORY;
    }

exit:
    if (decrypted_key != NULL)
    {
        mbedtls_platform_zeroize(decrypted_key, decrypted_key_length);
    }
    mbedtls_free(decrypted_key);
    return psa_status;
}

psa_status_t mcuxClPsaDriver_Oracle_ImportKey(
    mcuxClKey_Descriptor_t *pKey, const uint8_t *data, size_t data_length, size_t *key_buffer_length, size_t *bits)
{
    psa_status_t psa_status = PSA_ERROR_INVALID_ARGUMENT;

    uint32_t key_buffer_size               = pKey->container.length;
    const psa_key_attributes_t *attributes = (psa_key_attributes_t *)pKey->container.pAuxData;
    uint8_t *key_buffer                    = pKey->container.pData;

    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(psa_get_key_lifetime(attributes));
    if ((MCUXCLPSADRIVER_IS_S50_BLOB_STORAGE(location)) || (MCUXCLPSADRIVER_IS_S50_ENC_STORAGE(location)))
    {
        // derive the NXP_DIE_EL2GOIMPORT_AUTH_SK key in the keyslot
        mcuxClEls_KeyIndex_t el2goimport_auth_sk_slot;
        psa_status =
            mcuxClPsaDriver_Oracle_Utils_ExecuteKeyRecipe(el2goimport_auth_sk_id, // psa reference
                                                          &recipe_el2goimport_auth_sk, &el2goimport_auth_sk_slot);
        PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error in dispatching the key command to ELS");

        // validate blob attributes
        psa_status = mcuxClPsaDriver_Oracle_Utils_ValidateBlobAttributes(attributes, data, data_length,
                                                                         el2goimport_auth_sk_slot);

        // regardless of the status of the blob validation, we need to free the keyslot of the auth key
        psa_status_t psa_status_remove_key = mcuxClPsaDriver_Oracle_Utils_RemoveKeyFromEls(el2goimport_auth_sk_id);
        if (PSA_SUCCESS != psa_status_remove_key)
        {
            PSA_DRIVER_ERROR("Error,  EL2GOIMPORT_AUTH_SK key removal failed");
        }
        PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error in Validating Blob Attributes");

        // Store the blob as is in the PSA keystore.
        if (key_buffer_size < data_length)
        {
            return PSA_ERROR_INVALID_ARGUMENT;
        }

        (void)memcpy(key_buffer, data, data_length);
        *key_buffer_length = data_length;

        return PSA_SUCCESS;
    }
#ifdef MCUXCLPSADRIVER_KEY_RECIPE_IMPORT_ENABLE
    else if (MCUXCLPSADRIVER_IS_S50_KEY_GEN_STORAGE(location))
    {
        // TODO: Validate key recipe

        // Store the recipe as is in the PSA keystore.
        if (key_buffer_size < data_length)
        {
            return PSA_ERROR_INVALID_ARGUMENT;
        }

        (void)memcpy(key_buffer, data, data_length);
        *key_buffer_length = data_length;

        return PSA_SUCCESS;
    }
#endif
    // TODO: check which return code is better to use
    return PSA_ERROR_NOT_SUPPORTED;

exit:
    return psa_status;
}

psa_status_t mcuxClPsaDriver_Oracle_ExportPublicKey(
    mcuxClKey_Descriptor_t *pKey, uint8_t *data, size_t data_size, size_t *data_length, bool internal_representation)
{
    psa_status_t psa_status          = PSA_ERROR_NOT_SUPPORTED;
    uint8_t *public_key              = NULL;
    size_t public_key_size           = 0U;
    psa_key_attributes_t *attributes = (psa_key_attributes_t *)pKey->container.pAuxData;
    psa_key_location_t location      = PSA_KEY_LIFETIME_GET_LOCATION(psa_get_key_lifetime(attributes));

    if ((MCUXCLPSADRIVER_IS_S50_BLOB_STORAGE(location)) || (MCUXCLPSADRIVER_IS_S50_KEY_GEN_STORAGE(location)))
    {
        psa_status = mcuxClPsaDriver_Oracle_Utils_GetPublicKeyFromHandler(psa_get_key_id(attributes), &public_key,
                                                                          &public_key_size);

        if (psa_status == PSA_SUCCESS)
        {
            if ((public_key == NULL) || (public_key_size == 0U))
            {
                return PSA_ERROR_DATA_INVALID;
            }
            if (data_size < (public_key_size + 1U))
            {
                return PSA_ERROR_INSUFFICIENT_MEMORY;
            }
            if (internal_representation)
            {
                if (data_size < public_key_size)
                {
                    return PSA_ERROR_BUFFER_TOO_SMALL;
                }
                *data_length = public_key_size;
                (void)memcpy(data, public_key, public_key_size);
            }
            else
            {
                if (data_size < (public_key_size + 1U))
                {
                    return PSA_ERROR_BUFFER_TOO_SMALL;
                }
                *data_length = public_key_size + 1U;
                *data        = 0x04u;
                (void)memcpy(data + 1, public_key, public_key_size);
            }
        }
    }

    return psa_status;
}

psa_status_t mcuxClPsaDriver_Oracle_SuspendKey(mcuxClKey_Descriptor_t *pKey)
{
    // TODO: We should be returning an error here for a with an unknown location. However, we get called also for non
    // "oracle keys" (cryptolib issue). Keep the return success for now. return PSA_ERROR_NOT_SUPPORTED;
    return PSA_SUCCESS;
}
psa_status_t mcuxClPsaDriver_Oracle_ResumeKey(mcuxClKey_Descriptor_t *pKey)
{
    // TODO: We should be returning an error here for a with an unknown location. However, we get called also for non
    // "oracle keys" (cryptolib issue). Keep the return success for now. return PSA_ERROR_NOT_SUPPORTED;
    return PSA_SUCCESS;
}
psa_status_t mcuxClPsaDriver_Oracle_UnloadKey(mcuxClKey_Descriptor_t *pKey)
{
    psa_key_attributes_t *attributes = (psa_key_attributes_t *)pKey->container.pAuxData;
    psa_key_location_t location      = PSA_KEY_LIFETIME_GET_LOCATION(psa_get_key_lifetime(attributes));
    // PSA_KEY_LOCATION_S50_ENC_STORAGE :as key is in RAM, no operation is required on slot.

    // Perform remove key operation on location where slot is relevant.
    if ((MCUXCLPSADRIVER_IS_S50_BLOB_STORAGE(location)) || (MCUXCLPSADRIVER_IS_S50_KEY_GEN_STORAGE(location)))
    {
        return mcuxClPsaDriver_Oracle_Utils_RemoveKeyFromEls(psa_get_key_id(attributes));
    }
    else if (MCUXCLPSADRIVER_IS_S50_TEMP_STORAGE(location))
    {
        // Don't touch TEMP storage keys.
        // They are not owned by the oracle.
    }
    else if (MCUXCLPSADRIVER_IS_S50_ENC_STORAGE(location))
    {
        if (pKey->location.pData != NULL)
        {
            mbedtls_platform_zeroize(pKey->location.pData, pKey->location.length);
        }
        mbedtls_free(pKey->location.pData);
    }
    // TODO: We should be returning an error here for a with an unknown location. However, we get called also for non
    // "oracle keys" (cryptolib issue). Keep the return success for now. return PSA_ERROR_NOT_SUPPORTED;
    return PSA_SUCCESS;
}

psa_status_t mcuxClPsaDriver_Oracle_ReserveKey(mcuxClKey_Descriptor_t *pKey)
{
    // TODO: We should be returning an error here for a with an unknown location. However, we get called also for non
    // "oracle keys" (cryptolib issue). Keep the return success for now. return PSA_ERROR_NOT_SUPPORTED;
    return PSA_SUCCESS;
}

psa_status_t mcuxClPsaDriver_Oracle_StoreKey(mcuxClKey_Descriptor_t *pKey)
{
    // TODO: We should be returning an error here for a with an unknown location. However, we get called also for non
    // "oracle keys" (cryptolib issue). Keep the return success for now. return PSA_ERROR_NOT_SUPPORTED;
    return PSA_SUCCESS;
}

psa_status_t mcuxClPsaDriver_Oracle_GetKeyBufferSizeFromKeyData(const psa_key_attributes_t *attributes,
                                                                const uint8_t *data,
                                                                size_t data_length,
                                                                size_t *key_buffer_length)
{
    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(psa_get_key_lifetime(attributes));
    if ((MCUXCLPSADRIVER_IS_S50_BLOB_STORAGE(location)) || (MCUXCLPSADRIVER_IS_S50_ENC_STORAGE(location)) ||
        (MCUXCLPSADRIVER_IS_S50_TEMP_STORAGE(location)))
    {
        *key_buffer_length = data_length;
        return PSA_SUCCESS;
    }
#ifdef MCUXCLPSADRIVER_KEY_RECIPE_IMPORT_ENABLE
    else if (MCUXCLPSADRIVER_IS_S50_KEY_GEN_STORAGE(location))
    {
        *key_buffer_length = data_length;
        return PSA_SUCCESS;
    }
#endif
    // TODO: check which return code is better to use
    return PSA_ERROR_NOT_SUPPORTED;
}
