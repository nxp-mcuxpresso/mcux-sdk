/*
 * Copyright 2022-2023 NXP
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <mcuxClPsaDriver_Oracle_Utils.h>
#include <mcuxClPsaDriver_Oracle_ElsUtils.h>
#include <mcuxClPsaDriver_Oracle_Macros.h>

#include <mbedtls/platform.h>

#include "mcuxClEls_Types.h"

#include "stdlib.h"

// Tags used in PSA commands
#define PSA_CMD_TAG_MAGIC               0x40U
#define PSA_CMD_TAG_KEY_ID              0x41U
#define PSA_CMD_TAG_PERMITTED_ALGORITHM 0x42U
#define PSA_CMD_TAG_KEY_USAGE_FLAGS     0x43U
#define PSA_CMD_TAG_KEY_TYPE            0x44U
#define PSA_CMD_TAG_KEY_BITS            0x45U
#define PSA_CMD_TAG_KEY_LIFETIME        0x46U
#define PSA_CMD_TAG_WRAPPING_KEY_ID     0x50U
#define PSA_CMD_TAG_WRAPPING_ALGORITHM  0x51U
#define PSA_CMD_TAG_IV                  0x52U
#define PSA_CMD_TAG_SIGNATURE_KEY_ID    0x53U
#define PSA_CMD_TAG_SIGNATURE_ALGORITHM 0x54U
#define PSA_CMD_TAG_KEYIN_CMD           0x55U
#define PSA_CMD_TAG_SIGNATURE           0x5EU

// Algorithms used in EL2GO blobs
#define BLOB_SIGN_ALGORITHM_CMAC    0x01U
#define BLOB_WRAP_ALGORITHM_RFC3394 0x01U
#define BLOB_WRAP_ALGORITHM_AES_CBC 0x02U

// PSA command context
typedef struct psa_cmd_s
{
    psa_key_attributes_t attributes;
    const uint8_t *magic;
    size_t magic_size;
    uint32_t wrapping_key_id;
    uint32_t wrapping_algorithm;
    const uint8_t *iv;
    size_t iv_size;
    uint32_t signature_key_id;
    uint32_t signature_algorithm;
    const uint8_t *keyincmd;
    size_t keyincmd_size;
    const uint8_t *signature;
    size_t signature_size;
} psa_cmd_t;

// We only support NISTP-256 in S50
#define PUBLIC_KEY_SIZE 64U

#define CMAC_BLOCK_SIZE 16U

css_key_slot_handler_t slot_handler_array[MCUXCLELS_KEY_SLOTS] = {0};

static size_t ceil_to_blocksize(size_t len, size_t blocksize)
{
    return ((len + (blocksize - 1u)) / blocksize) * blocksize;
}

/** @brief Pads the data following iso7816
 *
 */
static psa_status_t pad_iso7816d4(uint8_t *data, size_t unpadded_length, size_t blocksize, size_t *padded_length)
{
    psa_status_t psa_status = PSA_SUCCESS;

    *padded_length        = ceil_to_blocksize(unpadded_length + 1u /* always inserted padding 0x80 */, blocksize);
    data[unpadded_length] = 0x80u;
    (void)memset(&data[unpadded_length + 1u], 0, *padded_length - (unpadded_length + 1u));
    return psa_status;
}

/** @brief Unpads the data following iso7816
 *
 */
static psa_status_t unpad_iso7816d4(uint8_t *data, size_t *data_size)
{
    psa_status_t psa_status = PSA_SUCCESS;

    PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(data_size != NULL && *data_size > 0u, PSA_ERROR_INVALID_ARGUMENT,
                                         "iso_7816_unpad failed, null data");

    uint32_t count = *data_size - 1u;
    while (count > 0u && data[count] == 0u)
    {
        count--;
    }

    PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(data[count] == 0x80u, PSA_ERROR_INVALID_ARGUMENT,
                                         "iso_7816_unpad failed, pad block corrupted");

    *data_size -= *data_size - count;
exit:
    return psa_status;
}

/** @brief Gets the 32-bit value from the value buffer.
 *
 */
static uint32_t get_uint32_val(const uint8_t *input)
{
    uint32_t output = 0U;
    output          = *(input);
    output <<= 8;
    output |= *(input + 1u);
    output <<= 8;
    output |= *(input + 2u);
    output <<= 8;
    output |= *(input + 3u);
    return output;
}

/** @brief Gets the 16-bit value from the value buffer.
 *
 */
static uint16_t get_uint16_val(const uint8_t *input)
{
    uint16_t output = 0U;
    output          = *input;
    output <<= 8;
    output |= *(input + 1u);
    return output;
}

// Function taken from MbedTLS
static int get_len(const unsigned char **p, const unsigned char *end, size_t *len)
{
    if ((end - *p) < 1)
    {
        return (PSA_ERROR_INVALID_ARGUMENT);
    }

    if ((**p & 0x80u) == 0u)
    {
        *len = *(*p)++;
    }
    else
    {
        switch (**p & 0x7Fu)
        {
            case 1:
                if ((end - *p) < 2)
                {
                    return (PSA_ERROR_INVALID_ARGUMENT);
                }

                *len = (*p)[1];
                (*p) += 2;
                break;

            case 2:
                if ((end - *p) < 3)
                {
                    return (PSA_ERROR_INVALID_ARGUMENT);
                }

                *len = ((size_t)(*p)[1] << 8) | (*p)[2];
                (*p) += 3;
                break;

            case 3:
                if ((end - *p) < 4)
                {
                    return (PSA_ERROR_INVALID_ARGUMENT);
                }

                *len = ((size_t)(*p)[1] << 16) | ((size_t)(*p)[2] << 8) | (*p)[3];
                (*p) += 4;
                break;

            case 4:
                if ((end - *p) < 5)
                {
                    return (PSA_ERROR_INVALID_ARGUMENT);
                }

                *len = ((size_t)(*p)[1] << 24) | ((size_t)(*p)[2] << 16) | ((size_t)(*p)[3] << 8) | (*p)[4];
                (*p) += 5;
                break;

            default:
                return (PSA_ERROR_INVALID_ARGUMENT);
        }
    }
    if (*len > (size_t)(end - *p))
    {
        return (PSA_ERROR_INVALID_ARGUMENT);
    }
    return (0);
}
// Function taken from MbedTLS
static int get_tag(const unsigned char **p, const unsigned char *end, size_t *len, uint8_t tag)
{
    if ((end - *p) < 1)
    {
        return (PSA_ERROR_INVALID_ARGUMENT);
    }

    if (**p != tag)
    {
        return (PSA_ERROR_INVALID_ARGUMENT);
    }

    (*p)++;

    return (get_len(p, end, len));
}

static psa_status_t parse_psa_import_command(const uint8_t *data, size_t data_size, psa_cmd_t *psa_cmd)
{
    psa_status_t psa_status = PSA_ERROR_INVALID_ARGUMENT;

    uint8_t tag    = 0U; // the tag of the current TLV
    size_t cmd_len = 0U; // the length of the current TLV

    const uint8_t *cmd_ptr = NULL;
    const uint8_t *end     = NULL;

    PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(data != NULL, PSA_ERROR_INVALID_ARGUMENT, "The command is null");
    PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(psa_cmd != NULL, PSA_ERROR_INVALID_ARGUMENT,
                                         "The key attributes context is null");

    (void)memset(psa_cmd, 0, sizeof(psa_cmd_t));
    psa_cmd->attributes = psa_key_attributes_init();

    cmd_ptr = data;
    end     = cmd_ptr + data_size;

    while ((cmd_ptr + 1) < end)
    {
        tag        = *cmd_ptr;
        psa_status = get_tag(&cmd_ptr, end, &cmd_len, tag);
        PSA_DRIVER_SUCCESS_OR_EXIT_MSG("get_tag failed: 0x%x", psa_status);

        switch (tag)
        {
            case PSA_CMD_TAG_MAGIC:
                psa_cmd->magic      = cmd_ptr;
                psa_cmd->magic_size = cmd_len;
                break;
            case PSA_CMD_TAG_KEY_ID:
                psa_set_key_id(&psa_cmd->attributes, mbedtls_svc_key_id_make(0, (psa_key_id_t)get_uint32_val(cmd_ptr)));
                break;
            case PSA_CMD_TAG_PERMITTED_ALGORITHM:
                psa_set_key_algorithm(&psa_cmd->attributes, (psa_algorithm_t)get_uint32_val(cmd_ptr));
                break;
            case PSA_CMD_TAG_KEY_USAGE_FLAGS:
                psa_set_key_usage_flags(&psa_cmd->attributes, (psa_key_usage_t)get_uint32_val(cmd_ptr));
                break;
            case PSA_CMD_TAG_KEY_TYPE:
                psa_set_key_type(&psa_cmd->attributes, (psa_key_type_t)get_uint16_val(cmd_ptr));
                break;
            case PSA_CMD_TAG_KEY_BITS:
                psa_set_key_bits(&psa_cmd->attributes, (size_t)get_uint32_val(cmd_ptr));
                break;
            case PSA_CMD_TAG_KEY_LIFETIME:
                psa_set_key_lifetime(&psa_cmd->attributes, (psa_key_lifetime_t)get_uint32_val(cmd_ptr));
                break;
            case PSA_CMD_TAG_WRAPPING_KEY_ID:
                psa_cmd->wrapping_key_id = get_uint32_val(cmd_ptr);
                break;
            case PSA_CMD_TAG_WRAPPING_ALGORITHM:
                psa_cmd->wrapping_algorithm = get_uint32_val(cmd_ptr);
                break;
            case PSA_CMD_TAG_IV:
                psa_cmd->iv      = cmd_ptr;
                psa_cmd->iv_size = cmd_len;
                break;
            case PSA_CMD_TAG_SIGNATURE_KEY_ID:
                psa_cmd->signature_key_id = get_uint32_val(cmd_ptr);
                break;
            case PSA_CMD_TAG_SIGNATURE_ALGORITHM:
                psa_cmd->signature_algorithm = get_uint32_val(cmd_ptr);
                break;
            case PSA_CMD_TAG_KEYIN_CMD:
                psa_cmd->keyincmd      = cmd_ptr;
                psa_cmd->keyincmd_size = cmd_len;
                break;
            case PSA_CMD_TAG_SIGNATURE:
                psa_cmd->signature      = cmd_ptr;
                psa_cmd->signature_size = cmd_len;
                break;
            default:
                PSA_DRIVER_ERROR("Unknown tag: 0x%x", tag);
                break;
        }
        cmd_ptr += cmd_len;
    }

exit:

    return psa_status;
}

static inline size_t get_key_bits(const mcuxClEls_KeyProp_t *prop)
{
    return prop->bits.ksize == MCUXCLELS_KEYPROPERTY_KEY_SIZE_128 ? 128U : 256U;
}

static mcuxClEls_KeyIndex_t get_usable_key_slot(size_t key_bits)
{
    uint32_t required_keyslots = (key_bits + 127U) / 128U;
    return mcuxClPsaDriver_Oracle_ElsUtils_GetFreeKeySlot(required_keyslots);
}

static psa_status_t free_key_in_slot_handler(mcuxClEls_KeyIndex_t slot_id)
{
    if (slot_handler_array[slot_id].busy != 0u)
    {
        slot_handler_array[slot_id].key_id  = MBEDTLS_SVC_KEY_ID_INIT;
        slot_handler_array[slot_id].storage = STORAGE_TEMP_KEY;
        mbedtls_free(slot_handler_array[slot_id].public_key);
        slot_handler_array[slot_id].public_key      = NULL;
        slot_handler_array[slot_id].public_key_size = 0U;
        slot_handler_array[slot_id].busy            = 0x00;
        return PSA_SUCCESS;
    }

    return PSA_ERROR_DOES_NOT_EXIST;
}

static void save_key_in_slot_handler(mcuxClEls_KeyIndex_t slot_id,
                                     mbedtls_svc_key_id_t key_id,
                                     uint8_t storage,
                                     uint8_t *public_key,
                                     size_t public_key_size)
{
    (void)free_key_in_slot_handler(slot_id);

    slot_handler_array[slot_id].key_id  = key_id;
    slot_handler_array[slot_id].storage = storage;
    if ((public_key != NULL) && (public_key_size != 0U))
    {
        slot_handler_array[slot_id].public_key      = public_key;
        slot_handler_array[slot_id].public_key_size = public_key_size;
    }
    slot_handler_array[slot_id].busy = 0xFF;
}

static psa_status_t get_slot_from_key_id(mbedtls_svc_key_id_t key_id, mcuxClEls_KeyIndex_t *slot_id, bool all_keys)
{
    *slot_id = 0U;
    for (mcuxClEls_KeyIndex_t slot_id_i = 0U; slot_id_i < MCUXCLELS_KEY_SLOTS; slot_id_i++)
    {
        if ((slot_handler_array[slot_id_i].busy != 0u) &&
            (mbedtls_svc_key_id_equal(slot_handler_array[slot_id_i].key_id, key_id) != 0) &&
            (all_keys || (slot_handler_array[slot_id_i].storage == STORAGE_FINAL_KEY)))
        {
            *slot_id = slot_id_i;
            return PSA_SUCCESS;
        }
    }
    return PSA_ERROR_DOES_NOT_EXIST;
}

psa_status_t mcuxClPsaDriver_Oracle_Utils_GetSlotFromKeyId(mbedtls_svc_key_id_t key_id, mcuxClEls_KeyIndex_t *slot_id)
{
    return get_slot_from_key_id(key_id, slot_id, false);
}

psa_status_t mcuxClPsaDriver_Oracle_Utils_GetPublicKeyFromHandler(mbedtls_svc_key_id_t key_id,
                                                                  uint8_t **public_key,
                                                                  size_t *public_key_size)
{
    mcuxClEls_KeyIndex_t slot_id = 0U;
    psa_status_t psa_status      = PSA_ERROR_DOES_NOT_EXIST;

    psa_status = mcuxClPsaDriver_Oracle_Utils_GetSlotFromKeyId(key_id, &slot_id);
    PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error in getting the slot from the key ID");

    if ((slot_handler_array[slot_id].public_key != NULL) && (slot_handler_array[slot_id].public_key_size != 0u))
    {
        *public_key      = slot_handler_array[slot_id].public_key;
        *public_key_size = slot_handler_array[slot_id].public_key_size;
        return PSA_SUCCESS;
    }
exit:
    return psa_status;
}

static psa_status_t execute_ckdf_step(mbedtls_svc_key_id_t key_id,
                                      const key_recipe_step_t *step,
                                      mcuxClEls_KeyIndex_t *target_key_slot)
{
    psa_status_t psa_status = PSA_SUCCESS;
    mcuxClEls_KeyIndex_t source_key_slot = 0U;
    uint8_t dd_data[MCUXCLELS_CKDF_DERIVATIONDATA_SIZE] = { 0 };
    
    PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(step != NULL, PSA_ERROR_INVALID_ARGUMENT, "Invalid input pointer");

    *target_key_slot = get_usable_key_slot(get_key_bits(&step->ckdf.key_properties));
    PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(*target_key_slot < MCUXCLELS_KEY_SLOTS, PSA_ERROR_BAD_STATE,
                                         "No usable keyslot found");

    if (step->ckdf.source == SOURCE_KEY_ID) {
       get_slot_from_key_id(step->ckdf.source_key_id, &source_key_slot, true);
    } else {
       source_key_slot = step->ckdf.source_key_slot;
    }
    
    if (step->ckdf.dd_src == DERIVATION_DATA_SOURCE_DYNAMIC) {
        (*(step->ckdf.derivation_fn))(dd_data);
    } else {
        memcpy(dd_data, step->ckdf.derivation_data, sizeof(step->ckdf.derivation_data));
    }


#if defined(MCUXCL_FEATURE_PLATFORM_MCXN)
    if (step->ckdf.kdf_mask) {
        SYSCON0->ELS_KDF_MASK = step->ckdf.kdf_mask;
    }
#endif
    
    psa_status = mcuxClPsaDriver_Oracle_ElsUtils_Ckdf(source_key_slot, *target_key_slot,
                                                      step->ckdf.key_properties, dd_data);
    PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error in ELS CKDF function execution");

    mbedtls_svc_key_id_t target_key_id = (step->storage == STORAGE_TEMP_KEY) ? step->ckdf.target_key_id : key_id;
    save_key_in_slot_handler(*target_key_slot, target_key_id, (uint8_t)step->storage, NULL, 0U);

exit:
    return psa_status;
}

static psa_status_t execute_keygen_step(mbedtls_svc_key_id_t key_id,
                                        const key_recipe_step_t *step,
                                        mcuxClEls_KeyIndex_t *target_key_slot)
{
    psa_status_t psa_status = PSA_SUCCESS;

    uint8_t *public_key = NULL;

    PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(step != NULL, PSA_ERROR_INVALID_ARGUMENT, "Invalid input pointer");

    if (step->keygen.options.bits.kgsrc == MCUXCLELS_ECC_OUTPUTKEY_DETERMINISTIC)
    {
        psa_status = get_slot_from_key_id(step->keygen.target_key_id, target_key_slot, true);
        PSA_DRIVER_SUCCESS_OR_EXIT_MSG("No keyslot found for target key ID");
    }
    else
    {
        *target_key_slot = get_usable_key_slot(get_key_bits(&step->keygen.key_properties));
        PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(*target_key_slot < MCUXCLELS_KEY_SLOTS, PSA_ERROR_BAD_STATE,
                                             "No usable keyslot found");
    }

    public_key = mbedtls_calloc(1, PUBLIC_KEY_SIZE);
    PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(public_key != NULL, PSA_ERROR_INSUFFICIENT_MEMORY,
                                         "Insufficient memory for public key allocation");

    // first byte of the key must be prepend manually
    psa_status = mcuxClPsaDriver_Oracle_ElsUtils_EccKeyGen(step->keygen.options, *target_key_slot,
                                                           step->keygen.key_properties, public_key);
    PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error in ELS ECC Key Generation function execution");

    // Hand over ownership of the public key
    mbedtls_svc_key_id_t target_key_id = (step->storage == STORAGE_TEMP_KEY) ? step->keygen.target_key_id : key_id;
    save_key_in_slot_handler(*target_key_slot, target_key_id, (uint8_t)step->storage, public_key, PUBLIC_KEY_SIZE);
    public_key = NULL;

exit:
    mbedtls_free(public_key);
    return psa_status;
}

static psa_status_t execute_kdelete_step(mbedtls_svc_key_id_t key_id, const key_recipe_step_t *step)
{
    psa_status_t psa_status = PSA_SUCCESS;

    PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(step != NULL, PSA_ERROR_INVALID_ARGUMENT, "Invalid input pointer");

    mbedtls_svc_key_id_t target_key_id = (step->storage == STORAGE_TEMP_KEY) ? step->kdelete.target_key_id : key_id;

    mcuxClEls_KeyIndex_t target_key_slot;
    psa_status = get_slot_from_key_id(target_key_id, &target_key_slot, true);
    PSA_DRIVER_SUCCESS_OR_EXIT_MSG("No keyslot found for target key ID");

    psa_status = mcuxClPsaDriver_Oracle_ElsUtils_KeyDelete(target_key_slot);
    PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error in key deletion");
    psa_status = free_key_in_slot_handler(target_key_slot);
    PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error in free_key_in_slot_handler");
exit:
    return psa_status;
}

psa_status_t mcuxClPsaDriver_Oracle_Utils_ExecuteKeyRecipe(mbedtls_svc_key_id_t key_id,
                                                           const key_recipe_t *recipe,
                                                           mcuxClEls_KeyIndex_t *target_key_slot)
{
    psa_status_t psa_status = PSA_SUCCESS;

    PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(recipe != NULL, PSA_ERROR_INVALID_ARGUMENT, "recipe is NULL");
    PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(target_key_slot != NULL, PSA_ERROR_INVALID_ARGUMENT,
                                         "target_key_slot is NULL");

    for (size_t i = 0; i < recipe->number_of_steps; i++)
    {
        const key_recipe_step_t *step = &recipe->steps[i];
        switch (step->operation)
        {
            case OP_CKDF:
                psa_status = execute_ckdf_step(key_id, step, target_key_slot);
                PSA_DRIVER_SUCCESS_OR_EXIT_MSG("execute_ckdf_recipe returned 0x%x", psa_status);
                break;
            case OP_KEYGEN:
                psa_status = execute_keygen_step(key_id, step, target_key_slot);
                PSA_DRIVER_SUCCESS_OR_EXIT_MSG("execute_ckdf_recipe returned 0x%x", psa_status);
                break;
            case OP_KDELETE:
                psa_status = execute_kdelete_step(key_id, step);
                PSA_DRIVER_SUCCESS_OR_EXIT_MSG("execute_kdelete_recipe returned 0x%x", psa_status);
                break;
            default:
                PSA_DRIVER_ERROR("Unknown recipe operation: 0x%x", step->operation);
                goto exit;
        }
    }
exit:
    return psa_status;
}

psa_status_t mcuxClPsaDriver_Oracle_Utils_RemoveKeyFromElsSlot(mcuxClEls_KeyIndex_t slot_id)
{
    psa_status_t psa_status = PSA_SUCCESS;
    // In case at least one key in ELS has the associated key_id, the function the psa_status
    // will be set to PSA_SUCCESS after the successful deletion of the key
    psa_status = mcuxClPsaDriver_Oracle_ElsUtils_KeyDelete(slot_id);
    PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error in key deletion");
    /* The key may or may not be Oracle maintained key slot handler */
    psa_status = free_key_in_slot_handler(slot_id);
exit:
    return psa_status;
}

psa_status_t mcuxClPsaDriver_Oracle_Utils_RemoveKeyFromEls(mbedtls_svc_key_id_t key_id)
{
    // In case at least one key in ELS has the associated key_id, the function the psa_status
    // will be set to PSA_SUCCESS after the successful deletion of the key
    mcuxClEls_KeyIndex_t slot_id = 0U;
    psa_status_t psa_status      = PSA_ERROR_DOES_NOT_EXIST;

    psa_status = mcuxClPsaDriver_Oracle_Utils_GetSlotFromKeyId(key_id, &slot_id);
    PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error in getting slot from key id");

    psa_status = mcuxClPsaDriver_Oracle_ElsUtils_KeyDelete(slot_id);
    PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error in key deletion");
    psa_status = free_key_in_slot_handler(slot_id);
    PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error in free_key_in_slot_handler");
exit:
    return psa_status;
}

psa_status_t mcuxClPsaDriver_Oracle_Utils_ExecuteElsDecryptCbc(uint8_t *psa_external_blob,
                                                               size_t psa_external_blob_size,
                                                               uint8_t **key_data,
                                                               size_t *key_size,
                                                               mcuxClEls_KeyIndex_t enc_key_slot)
{
    psa_status_t psa_status = PSA_SUCCESS;

    uint8_t *decrypted_key      = NULL;
    size_t decrypted_key_length = 0;

    psa_cmd_t psa_cmd;
    psa_status = parse_psa_import_command(psa_external_blob, psa_external_blob_size, &psa_cmd);
    PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error while parsing import blob");

    // ISO7816-4 padding ensures ciphertext and plaintext having the same length
    decrypted_key_length = psa_cmd.keyincmd_size;
    decrypted_key        = mbedtls_calloc(1, decrypted_key_length);
    PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(decrypted_key != NULL, PSA_ERROR_INSUFFICIENT_MEMORY,
                                         "Insufficient memory for decrypted key allocation");

    // decrypt blob with key on S50 slot
    psa_status = mcuxClPsaDriver_Oracle_ElsUtils_Cipher_Decrypt(psa_cmd.keyincmd, psa_cmd.keyincmd_size, enc_key_slot,
                                                                psa_cmd.iv, decrypted_key);
    PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error,  Cipher command failed");

    psa_status = unpad_iso7816d4(decrypted_key, &decrypted_key_length);
    PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error,  unpad_iso7816d4 failed");

    // Hand over ownership of the decrypted key
    *key_size     = decrypted_key_length;
    *key_data     = decrypted_key;
    decrypted_key = NULL;

exit:
    if (decrypted_key != NULL)
    {
        mbedtls_platform_zeroize(decrypted_key, decrypted_key_length);
    }
    mbedtls_free(decrypted_key);
    return psa_status;
}

psa_status_t mcuxClPsaDriver_Oracle_Utils_ExecuteElsKeyIn(const psa_key_attributes_t *attributes,
                                                          uint8_t *psa_import_blob,
                                                          size_t psa_import_blob_size,
                                                          mcuxClEls_KeyIndex_t wrap_key_slot,
                                                          mcuxClEls_KeyIndex_t *target_key_slot)
{
    psa_status_t psa_status = PSA_SUCCESS;

    uint8_t *public_key = NULL;
    const uint8_t *keyin_buf = NULL;
    size_t keyin_buf_size = 0;
    mbedtls_svc_key_id_t key_id = psa_get_key_id(attributes);
    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(psa_get_key_lifetime(attributes));

    psa_key_type_t key_type = psa_get_key_type(attributes);
    
    // Using Location to determine blob type. We can declare an enum too
    if (MCUXCLPSADRIVER_IS_S50_RFC3394_STORAGE(location))
    {
        // We are trusting the key properties passed by user to get the slot.
        *target_key_slot = get_usable_key_slot(psa_get_key_bits(attributes));
        PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(*target_key_slot < MCUXCLELS_KEY_SLOTS, PSA_ERROR_BAD_STATE,
                                         "No usable keyslot found");
        
        keyin_buf = psa_import_blob;
        keyin_buf_size = psa_import_blob_size;
    }
    else // EL2GO Blob
    {     
        psa_cmd_t psa_cmd;
        psa_status = parse_psa_import_command(psa_import_blob, psa_import_blob_size, &psa_cmd);
        PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error while parsing import blob");

        PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(target_key_slot != NULL, PSA_ERROR_INVALID_ARGUMENT,
                                             "target_key_slot is NULL");

        *target_key_slot = get_usable_key_slot(psa_get_key_bits(&psa_cmd.attributes));
        PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(*target_key_slot < MCUXCLELS_KEY_SLOTS, PSA_ERROR_BAD_STATE,
                                             "No usable keyslot found");
        
        keyin_buf = psa_cmd.keyincmd;
        keyin_buf_size = psa_cmd.keyincmd_size;
        
        /* Overwrite the keytype from EL2GO blob */
        key_type = psa_get_key_type(&psa_cmd.attributes);
    }
    
    psa_status =
        mcuxClPsaDriver_Oracle_ElsUtils_KeyIn(keyin_buf, keyin_buf_size, wrap_key_slot, *target_key_slot);
    PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error in ELS keyin command execution");

    if (PSA_KEY_TYPE_IS_ECC(key_type))
    {
        // If we get here the ELS KEYIN was done, the key is in the slot. We can read the
        // properties of the key from ELS (so the KEYGEN result gets the same as the original).
        mcuxClEls_KeyProp_t keyProperties;
        psa_status = mcuxClPsaDriver_Oracle_ElsUtils_GetKeyProperties(*target_key_slot, &keyProperties);
        PSA_DRIVER_SUCCESS_OR_EXIT_MSG("mcuxClPsaDriver_Oracle_ElsUtils_GetKeyProperties failed");
        
        if (keyProperties.bits.ukgsrc != MCUXCLELS_KEYPROPERTY_INPUT_FOR_ECC_TRUE)
        {
          psa_status = PSA_ERROR_INVALID_ARGUMENT;
            PSA_DRIVER_SUCCESS_OR_EXIT_MSG("The RFC blob for ECC Key Pair is invalid");
        }
        
        mcuxClEls_EccKeyGenOption_t key_gen_options;
        key_gen_options.word.value    = 0u;
        key_gen_options.bits.kgsign   = MCUXCLELS_ECC_PUBLICKEY_SIGN_DISABLE;
        key_gen_options.bits.kgsrc    = MCUXCLELS_ECC_OUTPUTKEY_DETERMINISTIC;
        key_gen_options.bits.skip_pbk = MCUXCLELS_ECC_GEN_PUBLIC_KEY;
        
        public_key = mbedtls_calloc(1, PUBLIC_KEY_SIZE);
        PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(public_key != NULL, PSA_ERROR_INSUFFICIENT_MEMORY,
                                             "Insufficient memory for public key allocation");

        psa_status =
            mcuxClPsaDriver_Oracle_ElsUtils_EccKeyGen(key_gen_options, *target_key_slot, keyProperties, public_key);
        PSA_DRIVER_SUCCESS_OR_EXIT_MSG("mcuxClPsaDriver_Oracle_ElsUtils_EccKeyGen failed");
    }

    // Hand over ownership of the public key
    save_key_in_slot_handler(*target_key_slot, key_id, STORAGE_FINAL_KEY, public_key, PUBLIC_KEY_SIZE);
    public_key = NULL;
    
exit:
    mbedtls_free(public_key);
    return psa_status;
}

psa_status_t mcuxClPsaDriver_Oracle_Utils_ValidateBlobAttributes(const psa_key_attributes_t *attributes,
                                                                 const uint8_t *psa_import_blob,
                                                                 size_t psa_import_blob_size,
                                                                 mcuxClEls_KeyIndex_t auth_key_slot)
{
    psa_status_t psa_status = PSA_SUCCESS;

    uint8_t *psa_import_blob_tbs = NULL;

    psa_cmd_t psa_cmd;
    psa_status = parse_psa_import_command(psa_import_blob, psa_import_blob_size, &psa_cmd);
    PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error while parsing import blob");

    // Validate input PSA attributes
    PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(0 == mbedtls_svc_key_id_is_null(psa_get_key_id(attributes)),
                                         PSA_ERROR_INVALID_ARGUMENT, "Invalid input key_id");

    // Attention: Permitted algorithm can be 0 (PSA_ALG_NONE for X.509/Binary)
    // Attention: Permitted usage can be 0 (PSA_KEY_USAGE_NONE for static public keys)

    PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(psa_get_key_type(attributes) != (psa_key_type_t)0, PSA_ERROR_INVALID_ARGUMENT,
                                         "Invalid input key_type");

    PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(psa_get_key_bits(attributes) != (size_t)0, PSA_ERROR_INVALID_ARGUMENT,
                                         "Invalid input key_length");

    PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(psa_get_key_lifetime(attributes) != (psa_key_lifetime_t)0,
                                         PSA_ERROR_INVALID_ARGUMENT, "Invalid input key_lifetime");

    // Validate blob PSA attributes
    PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(MBEDTLS_SVC_KEY_ID_GET_KEY_ID(psa_get_key_id(attributes)) ==
                                             MBEDTLS_SVC_KEY_ID_GET_KEY_ID(psa_get_key_id(&psa_cmd.attributes)),
                                         PSA_ERROR_INVALID_ARGUMENT, "provided key_id does not match with blob key_id");

    PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(
        psa_get_key_algorithm(attributes) == psa_get_key_algorithm(&psa_cmd.attributes), PSA_ERROR_INVALID_ARGUMENT,
        "provided permitted_alg does not match with blob permitted_alg");

    PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(
        psa_get_key_usage_flags(attributes) == psa_get_key_usage_flags(&psa_cmd.attributes), PSA_ERROR_INVALID_ARGUMENT,
        "provided key_usage does not match with blob key_usage");

    PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(psa_get_key_type(attributes) == psa_get_key_type(&psa_cmd.attributes),
                                         PSA_ERROR_INVALID_ARGUMENT,
                                         "provided key_type does not match with blob key_type");

    PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(psa_get_key_bits(attributes) == psa_get_key_bits(&psa_cmd.attributes),
                                         PSA_ERROR_INVALID_ARGUMENT,
                                         "provided key_length does not match with blob key_length");

    PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(psa_get_key_lifetime(attributes) == psa_get_key_lifetime(&psa_cmd.attributes),
                                         PSA_ERROR_INVALID_ARGUMENT,
                                         "provided key_lifetime does not match with blob key_lifetime");

    // Validate blob lifetime and wrapping parameters
    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(psa_get_key_lifetime(attributes));
    if (MCUXCLPSADRIVER_IS_S50_BLOB_STORAGE(location))
    {
        PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(NXP_DIE_EL2GOIMPORT_KEK_SK_ID == psa_cmd.wrapping_key_id,
                                             PSA_ERROR_INVALID_ARGUMENT, "Unknown blob wrapping_key_id");
        PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(BLOB_WRAP_ALGORITHM_RFC3394 == psa_cmd.wrapping_algorithm,
                                             PSA_ERROR_INVALID_ARGUMENT, "Unknown blob wrapping_algorithm");
    }
    else if (MCUXCLPSADRIVER_IS_S50_ENC_STORAGE(location))
    {
        PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(NXP_DIE_EL2GOIMPORTTFM_KEK_SK_ID == psa_cmd.wrapping_key_id,
                                             PSA_ERROR_INVALID_ARGUMENT, "Unknown blob wrapping_key_id");
        // We only support AES CBC wrapping via PSA
        PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(BLOB_WRAP_ALGORITHM_AES_CBC == psa_cmd.wrapping_algorithm,
                                             PSA_ERROR_INVALID_ARGUMENT, "Unknown blob wrapping_algorithm");
    }
    else
    {
        PSA_DRIVER_EXIT_STATUS_MSG(PSA_ERROR_INVALID_ARGUMENT, "Unknown blob key_lifetime")
    }

    // Validate signature parameters
    PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(NXP_DIE_EL2GOIMPORT_AUTH_SK_ID == psa_cmd.signature_key_id,
                                         PSA_ERROR_INVALID_ARGUMENT, "Unknown blob signature_key_id");

    PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(BLOB_SIGN_ALGORITHM_CMAC == psa_cmd.signature_algorithm,
                                         PSA_ERROR_INVALID_ARGUMENT, "Unknown blob signature_algorithm");

    PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(CMAC_BLOCK_SIZE == psa_cmd.signature_size, PSA_ERROR_INVALID_ARGUMENT,
                                         "Invalid blob CMAC size");

    // We do allocate enough memory here to also fit the padding into the buffer. This is achieved implicitly because
    // the blob size used here still includes the CMAC. The CMAC, however is excluded from the data to be signed and
    // thus in the copied buffer replaced by the padding.
    psa_import_blob_tbs = mbedtls_calloc(1, psa_import_blob_size);
    PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(psa_import_blob_tbs != NULL, PSA_ERROR_INSUFFICIENT_MEMORY,
                                         "Insufficient memory for padded blob allocation");

    // remove cmac value (last 16 bytes) from the copy
    psa_import_blob_size = psa_import_blob_size - CMAC_BLOCK_SIZE;
    (void)memcpy(psa_import_blob_tbs, psa_import_blob, psa_import_blob_size);

    // pad data
    size_t psa_import_blob_tbs_padded_length = 0;
    psa_status =
        pad_iso7816d4(psa_import_blob_tbs, psa_import_blob_size, CMAC_BLOCK_SIZE, &psa_import_blob_tbs_padded_length);
    PSA_DRIVER_SUCCESS_OR_EXIT_MSG("padding data failed");

    uint8_t pCmac[CMAC_BLOCK_SIZE];
    psa_status =
        mcuxClPsaDriver_Oracle_ElsUtils_Cmac(psa_import_blob_tbs,
                                             psa_import_blob_size, // Attention, ELS expects size before padding
                                             auth_key_slot, &pCmac[0]);
    PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error in VerifyCmac keyin command execution");

    for (size_t i = 0; i < CMAC_BLOCK_SIZE; i++)
    {
        if (psa_cmd.signature[i] != pCmac[i])
        {
            psa_status = PSA_ERROR_INVALID_SIGNATURE;
            PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error, Blob cmac value does not match calculated cmac value");
        }
    }

exit:
    mbedtls_free(psa_import_blob_tbs);
    return psa_status;
}

uint32_t mcuxClPsaDriver_Oracle_Utils_RFC3394ContainerSize(const psa_key_attributes_t *attributes)
{
    return (psa_get_key_bits(attributes) == 128) ? MCUXCLELS_RFC3394_CONTAINER_SIZE_128 : MCUXCLELS_RFC3394_CONTAINER_SIZE_256;
}

psa_status_t mcuxClPsaDriver_Oracle_Utils_GenerateSharedSecretECDH(
    const psa_key_attributes_t *attributes,
    mcuxClEls_KeyIndex_t *key_index_shared_secret)
{
    psa_status_t psa_status = PSA_ERROR_NOT_SUPPORTED;
    psa_key_type_t key_type = psa_get_key_type(attributes);
    
    // Generate ECC key Pair 1 in s50 slot.  Retain it and delete the private key from slot
    mcuxClEls_KeyIndex_t ecc_key1_index = mcuxClPsaDriver_Oracle_ElsUtils_GetFreeKeySlot(2);    
  
    mcuxClEls_KeyProp_t  keyProp;
    keyProp.word.value       = 0;
    keyProp.bits.ksize       = MCUXCLELS_KEYPROPERTY_KEY_SIZE_256;
    keyProp.bits.kactv       = MCUXCLELS_KEYPROPERTY_ACTIVE_TRUE;
    keyProp.bits.ukgsrc      = MCUXCLELS_KEYPROPERTY_INPUT_FOR_ECC_TRUE;
#if defined(MBEDTLS_PSA_CRYPTO_SPM)    
    keyProp.bits.upprot_priv = MCUXCLELS_KEYPROPERTY_PRIVILEGED_TRUE;
    keyProp.bits.upprot_sec  = MCUXCLELS_KEYPROPERTY_SECURE_TRUE;
#endif    

    mcuxClEls_EccKeyGenOption_t KeyGenOptions;
    KeyGenOptions.word.value    = 0u;
    KeyGenOptions.bits.kgsign   = MCUXCLELS_ECC_PUBLICKEY_SIGN_DISABLE;
    KeyGenOptions.bits.kgtypedh = MCUXCLELS_ECC_OUTPUTKEY_SIGN;
    KeyGenOptions.bits.kgsrc    = MCUXCLELS_ECC_OUTPUTKEY_RANDOM;
    KeyGenOptions.bits.skip_pbk = MCUXCLELS_ECC_GEN_PUBLIC_KEY;

    uint8_t *public_key1 = mbedtls_calloc(1, PUBLIC_KEY_SIZE);
    PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(public_key1 != NULL, PSA_ERROR_INSUFFICIENT_MEMORY,
                                        "Insufficient memory for public key allocation");
   
    psa_status =  mcuxClPsaDriver_Oracle_ElsUtils_EccKeyGen(KeyGenOptions, ecc_key1_index, keyProp, public_key1);
    PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error in generating first key pair in ELS");
    
    // Delete the private key
    psa_status = mcuxClPsaDriver_Oracle_ElsUtils_KeyDelete(ecc_key1_index);
    PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error in Key Deletion in ELS"); 
    
    // Generate ECC key pair 2 with Key exchange property set.
    keyProp.word.value       = 0;
    keyProp.bits.ksize       = MCUXCLELS_KEYPROPERTY_KEY_SIZE_256;
    keyProp.bits.kactv       = MCUXCLELS_KEYPROPERTY_ACTIVE_TRUE;
#if defined(MBEDTLS_PSA_CRYPTO_SPM)    
    keyProp.bits.upprot_priv = MCUXCLELS_KEYPROPERTY_PRIVILEGED_TRUE;
    keyProp.bits.upprot_sec  = MCUXCLELS_KEYPROPERTY_SECURE_TRUE;
#endif    

    KeyGenOptions.word.value    = 0u;
    KeyGenOptions.bits.kgsign   = MCUXCLELS_ECC_PUBLICKEY_SIGN_DISABLE;
    KeyGenOptions.bits.kgtypedh = MCUXCLELS_ECC_OUTPUTKEY_KEYEXCHANGE;
    KeyGenOptions.bits.kgsrc    = MCUXCLELS_ECC_OUTPUTKEY_RANDOM;    
    KeyGenOptions.bits.skip_pbk = MCUXCLELS_ECC_GEN_PUBLIC_KEY;

    uint8_t *public_key2 = mbedtls_calloc(1, PUBLIC_KEY_SIZE);
    PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(public_key2 != NULL, PSA_ERROR_INSUFFICIENT_MEMORY,
                                         "Insufficient memory for public key allocation");
      
    psa_status =  mcuxClPsaDriver_Oracle_ElsUtils_EccKeyGen(KeyGenOptions, ecc_key1_index, keyProp, public_key2);
    // Public Key 2 not needed
    free(public_key2);
    PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error in generating second key pair in ELS");    
    
    keyProp.word.value       = 0;
    if (PSA_KEY_TYPE_IS_ECC(key_type))
    {
        keyProp.bits.ukgsrc      = MCUXCLELS_KEYPROPERTY_INPUT_FOR_ECC_TRUE;
    } 
    else
    {
        /* We will use this key to derive symmetric keys via CKDF */
        keyProp.bits.uckdf      = MCUXCLELS_KEYPROPERTY_CKDF_TRUE;
    }
    
    keyProp.bits.wrpok       = MCUXCLELS_KEYPROPERTY_WRAP_TRUE;
#if defined(MBEDTLS_PSA_CRYPTO_SPM)    
    keyProp.bits.upprot_priv = MCUXCLELS_KEYPROPERTY_PRIVILEGED_TRUE;
    keyProp.bits.upprot_sec  = MCUXCLELS_KEYPROPERTY_SECURE_TRUE;
#endif    
  
    *key_index_shared_secret = mcuxClPsaDriver_Oracle_ElsUtils_GetFreeKeySlot(2);
   // Execute Key exchange and put the secret in a key slot.If key type is ECC use the key index passed
    psa_status = mcuxClPsaDriver_Oracle_ElsUtils_EccKeyAgreement(ecc_key1_index, public_key1, *key_index_shared_secret, keyProp);
    PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error in Key Exchange in ELS"); 

    // Delete the key generated for exchange
    psa_status = mcuxClPsaDriver_Oracle_ElsUtils_KeyDelete(ecc_key1_index);    
    PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error in Key Deletion in ELS"); 
    
exit:
    free(public_key1);
    
    return psa_status;
}

psa_status_t mcuxClPsaDriver_Oracle_Utils_GenerateKey(
    const psa_key_attributes_t *attributes,
    mcuxClEls_KeyIndex_t *key_index)
{
    psa_key_type_t key_type = psa_get_key_type(attributes);
    size_t key_bits = psa_get_key_bits(attributes);
    psa_algorithm_t alg = psa_get_key_algorithm(attributes);
    
    if (PSA_KEY_TYPE_IS_ECC(key_type)) {
        if ((PSA_KEY_TYPE_ECC_GET_FAMILY(key_type) != PSA_ECC_FAMILY_SECP_R1) || 
            (PSA_ALG_SIGN_GET_HASH(alg) != PSA_ALG_SHA_256))
         {
              return PSA_ERROR_NOT_SUPPORTED;
         }
         else 
         {
              return mcuxClPsaDriver_Oracle_Utils_GenerateSharedSecretECDH(attributes, key_index);         
         }       
    }
    else 
    {      
        mcuxClEls_KeyProp_t  keyProp = { 0 };
        keyProp.word.value       = 0;
        psa_status_t psa_status = PSA_ERROR_NOT_SUPPORTED;
        mcuxClEls_KeyIndex_t tmp_idx = 0;
        const uint8_t dd_data[MCUXCLELS_CKDF_DERIVATIONDATA_SIZE] = { 'R','F','C','3','3','9','4','B','L','O','B', 0x0u };
        
        switch (key_type) {
        case PSA_KEY_TYPE_AES:
          switch (alg) {
          case PSA_ALG_CTR:
          case PSA_ALG_ECB_NO_PADDING:
          case PSA_ALG_CBC_NO_PADDING:
          case PSA_ALG_GCM:
              keyProp.bits.uaes = MCUXCLELS_KEYPROPERTY_AES_TRUE;
              break;
          case PSA_ALG_CMAC:
              keyProp.bits.ucmac = MCUXCLELS_KEYPROPERTY_CMAC_TRUE;
              break;
          default:
              return PSA_ERROR_NOT_SUPPORTED;
          }
          break;
        case PSA_KEY_TYPE_HMAC:
          if (key_bits == 256) {
              keyProp.bits.uhmac = MCUXCLELS_KEYPROPERTY_HMAC_TRUE;
          } else {
              return PSA_ERROR_NOT_SUPPORTED;
          }
            break;
        default:
            return PSA_ERROR_NOT_SUPPORTED;
        }
        
        if (key_bits == 128) {
            keyProp.bits.ksize = MCUXCLELS_KEYPROPERTY_KEY_SIZE_128;
        } else if (key_bits == 256) {
            keyProp.bits.ksize = MCUXCLELS_KEYPROPERTY_KEY_SIZE_256;            
        } else {
            return PSA_ERROR_NOT_SUPPORTED;
        }
        
        keyProp.bits.wrpok       = MCUXCLELS_KEYPROPERTY_WRAP_TRUE;
#if defined(MBEDTLS_PSA_CRYPTO_SPM)    
        keyProp.bits.upprot_priv = MCUXCLELS_KEYPROPERTY_PRIVILEGED_TRUE;
        keyProp.bits.upprot_sec  = MCUXCLELS_KEYPROPERTY_SECURE_TRUE;
#endif    
       
        psa_status = mcuxClPsaDriver_Oracle_Utils_GenerateSharedSecretECDH(attributes, &tmp_idx);
        PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error in ELS ECDH function execution");

        *key_index = get_usable_key_slot(key_bits);
        
        psa_status = mcuxClPsaDriver_Oracle_ElsUtils_Ckdf(tmp_idx, *key_index,
                                                          keyProp, dd_data);
        PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error in ELS CKDF function execution");
        
        // needs to shift to in exit
        psa_status = mcuxClPsaDriver_Oracle_ElsUtils_KeyDelete(tmp_idx);    
        PSA_DRIVER_SUCCESS_OR_EXIT_MSG("Error in Key Deletion in ELS"); 

    exit:      
        return psa_status;          
    }
}
