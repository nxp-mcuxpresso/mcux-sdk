/*
 * Copyright 2022-2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/** @file  mcuxClPsaDriver_Oracle_Utils.h
 *  @brief API definition of the Utils functions used in the Driver Wrapper */

#ifndef _MCUXCLPSADRIVER_ORACLE_UTILS_
#define _MCUXCLPSADRIVER_ORACLE_UTILS_

#include <common.h>
#include <psa/crypto.h>

#include <stdint.h>
#include <stddef.h>
#include "mcuxClEls_Ecc.h"
#include "mcuxClEls_Kdf.h"

// in case the key is derived as a process including several key derivation execution,
// the intermediate keys will have a temporary storage assigned to them and they will
// be deleted at the end of the derivation command
#define STORAGE_TEMP_KEY  0x00U
#define STORAGE_FINAL_KEY 0x01U

// ELS slot numbers and PSA key IDs for deriving builtin keys & blob import keys
#define NXP_DIE_EL2GOOEM_MK_SK_SLOT      0x04U
#define NXP_DIE_EL2GOIMPORT_KEK_SK_ID    0x7FFF816EU
#define NXP_DIE_EL2GOIMPORTTFM_KEK_SK_ID 0x7FFF816FU
#define NXP_DIE_EL2GOIMPORT_AUTH_SK_ID   0x7FFF8170U

#define NXP_DIE_EL2GOPUBLIC_MK_SK_SLOT  0x06U
#define NXP_DIE_EL2GOCONN_AUTH_PRK_ID   0x7FFF816CU
#define NXP_DIE_EL2GOATTEST_AUTH_PRK_ID 0x7FFF8174U

typedef enum key_recipe_operation_t
{
    OP_CKDF,
    OP_KEYGEN,
    OP_KDELETE,
} key_recipe_operation_t;

typedef struct _key_recipe_step_ckdf_t
{
    mcuxClEls_KeyIndex_t source_key_slot;
    mbedtls_svc_key_id_t target_key_id;
    mcuxClEls_KeyProp_t key_properties;
    uint8_t derivation_data[MCUXCLELS_CKDF_DERIVATIONDATA_SIZE];
} key_recipe_step_ckdf_t;

typedef struct _key_recipe_step_keygen_t
{
    mbedtls_svc_key_id_t target_key_id;
    mcuxClEls_KeyProp_t key_properties;
    mcuxClEls_EccKeyGenOption_t options;
} key_recipe_step_keygen_t;

typedef struct _key_recipe_step_kdelete_t
{
    mbedtls_svc_key_id_t target_key_id;
} key_recipe_step_kdelete_t;

typedef struct _key_recipe_step_t
{
    key_recipe_operation_t operation;
    uint32_t storage;
    union
    {
        key_recipe_step_ckdf_t ckdf;
        key_recipe_step_keygen_t keygen;
        key_recipe_step_kdelete_t kdelete;
    };
} key_recipe_step_t;

typedef struct _key_recipe_t
{
    size_t number_of_steps;
    key_recipe_step_t steps[];
} key_recipe_t;

extern const key_recipe_t recipe_el2goimport_kek_sk;
extern const key_recipe_t recipe_el2goimporttfm_kek_sk;
extern const key_recipe_t recipe_el2goimport_auth_sk;
extern const key_recipe_t recipe_el2goconn_auth_prk;
extern const key_recipe_t recipe_el2goattest_auth_prk;

typedef struct css_key_slot_handler_s
{
    uint32_t busy;
    mbedtls_svc_key_id_t key_id;
    uint8_t storage;
    uint8_t *public_key;
    size_t public_key_size;
} css_key_slot_handler_t;

extern css_key_slot_handler_t slot_handler_array[MCUXCLELS_KEY_SLOTS];

/**
 * @brief Calculate the size of a key recipe.
 * @param[in] recipe the recipe to determine the size of
 */
static inline size_t mcuxClPsaDriver_Oracle_Utils_GetRecipeSize(const key_recipe_t *recipe)
{
    return offsetof(key_recipe_t, steps) + recipe->number_of_steps * sizeof(key_recipe_step_t);
}

/**
 * @brief Gets the slot ID for the give key id
 *
 * @param[in] key_id the ID of the key from PSA view
 * @param[out] slot_id the ID of the key as stored in ELS
 *
 * @retval PSA_SUCCESS                 The operation was succesful
 * @retval PSA_ERROR_DOES_NOT_EXIST    There is no slot associated with key id
 */
psa_status_t mcuxClPsaDriver_Oracle_Utils_GetSlotFromKeyId(mbedtls_svc_key_id_t key_id, mcuxClEls_KeyIndex_t *slot_id);

/**
 * @brief Gets the public key associated with key id
 *
 * @param[in] key_id the ID of the key from PSA view
 * @param[out] public key
 * @param[out] size of public key
 *
 * @retval PSA_SUCCESS                 The operation was succesful
 * @retval PSA_ERROR_DOES_NOT_EXIST    There is no public key associated with key id
 */
psa_status_t mcuxClPsaDriver_Oracle_Utils_GetPublicKeyFromHandler(mbedtls_svc_key_id_t key_id,
                                                                  uint8_t **public_key,
                                                                  size_t *public_key_size);

/**
 * @brief Executes a parsed key recipe.
 *
 * No more input validation is done on the structured input data!
 *
 * @param[in] key_id the ID of the key from PSA view
 * @param[in] recipe a list of steps making up the recipe to get the key
 * @param[out] target_key_slot the ELS key slot that the final key is occupying
 *
 * @retval PSA_SUCCESS                 The operation was succesful
 * @retval PSA_ERROR_INVALID_ARGUMENT  Derivation data doesn't include a valid command
 * @retval PSA_ERROR_HARDWARE_FAILURE  The ELS operation failed
 */
psa_status_t mcuxClPsaDriver_Oracle_Utils_ExecuteKeyRecipe(mbedtls_svc_key_id_t key_id,
                                                           const key_recipe_t *recipe,
                                                           mcuxClEls_KeyIndex_t *target_key_slot);

/**
 * @brief Deletes the keys associated with the PSA key ID form ELS and internal handler
 *
 * @param[in] key_id the ID of the key from PSA view
 *
 * @retval PSA_SUCCESS                 The operation was succesful
 * @retval PSA_ERROR_DOES_NOT_EXIST    No key with the associated key_id found in ELS
 */
psa_status_t mcuxClPsaDriver_Oracle_Utils_RemoveKeyFromEls(mbedtls_svc_key_id_t key_id);

/**
 * @brief Parses psa_import_blob and executes the KEYIN command on the ELS
 *
 * @param[in] key_id psa key id reference
 * @param[in] psa_import_blob buffer holding psa import command
 * @param[in] psa_import_blob_size the length of the buffer
 * @param[in] wrap_key_slot The ELS key slot of the wrapping key
 * @param[out] target_key_slot The ELS key slot the target key is occupying
 *
 * @retval PSA_SUCCESS                 The operation was successful
 * @retval PSA_ERROR_HARDWARE_FAILURE  The ELS operation failed
 */
psa_status_t mcuxClPsaDriver_Oracle_Utils_ExecuteElsKeyIn(mbedtls_svc_key_id_t key_id,
                                                          uint8_t *psa_import_blob,
                                                          size_t psa_import_blob_size,
                                                          mcuxClEls_KeyIndex_t wrap_key_slot,
                                                          mcuxClEls_KeyIndex_t *target_key_slot);

/**
 * @brief Parses psa_import_blob, verifies blob integrity and validates provided attributes against attributes from psa
 * blob.
 *
 * @param[in] attributes provided key attributes
 * @param[in] psa_import_blob buffer holding psa import command
 * @param[in] psa_import_blob_size the length of the buffer
 * @param[in] auth_key_slot The ELS key slot of the auth key that will be used for CMAC
 *
 * @retval PSA_SUCCESS                 The operation was successful
 * @retval PSA_ERROR_INVALID_ARGUMENT  Argument validation failed
 */
psa_status_t mcuxClPsaDriver_Oracle_Utils_ValidateBlobAttributes(const psa_key_attributes_t *attributes,
                                                                 const uint8_t *psa_import_blob,
                                                                 size_t psa_import_blob_size,
                                                                 mcuxClEls_KeyIndex_t auth_key_slot);

/**
 * @brief Parses psa_import_external_blob and decrypts it.
 *
 * @param[in] psa_external_blob buffer holding psa import command
 * @param[in] psa_external_blob_size the length of the buffer
 * @param[in] key_data the decrypted key buffer
 * @param[in] key_size the length of the key buffer
 * @param[in] enc_key_slot The ELS key slot of the enc key that will be used for decryption
 *
 * @retval PSA_SUCCESS                 The operation was successful
 * @retval PSA_ERROR_INVALID_ARGUMENT  Argument validation failed
 */
psa_status_t mcuxClPsaDriver_Oracle_Utils_ExecuteElsDecryptCbc(uint8_t *psa_external_blob,
                                                               size_t psa_external_blob_size,
                                                               uint8_t **key_data,
                                                               size_t *key_size,
                                                               mcuxClEls_KeyIndex_t enc_key_slot);
#endif //_MCUXCLPSADRIVER_ORACLE_UTILS_
