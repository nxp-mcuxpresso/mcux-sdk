/*
 * Copyright 2022-2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/** @file  mcuxClPsaDriver_Oracle_ElsUtils.h
 *  @brief API definition of the ELS Utils functions used in the Driver Wrapper */

#ifndef _MCUXCLPSADRIVER_ORACLE_ELSUTILS_
#define _MCUXCLPSADRIVER_ORACLE_ELSUTILS_

#include <common.h>
#include <mcuxClEls.h>
#include <stdbool.h>
#include <string.h>

/**
 * @brief Retrieve the key properties of a key in an S50 keyslot.
 *
 * @param[in] keyIdx Key index to check
 * @param[out] keyProperties The key properties of the key
 *
 * @retval PSA_SUCCESS                 The operation was succesful
 * @retval PSA_ERROR_HARDWARE_FAILURE  The ELS operation failed
 */
psa_status_t mcuxClPsaDriver_Oracle_ElsUtils_GetKeyProperties(mcuxClEls_KeyIndex_t keyIdx,
                                                              mcuxClEls_KeyProp_t *keyProperties);

/**
 * @brief Check that a given keyslot is free to use for a key.
 *
 * @param[in] keyIdx Key index to check
 * @param[in] requiredKeyslots The number of (consecutive) slots that are required.
 *
 * @retval true  There is enough free slots.
 * @retval false  There are not enough free slots.
 */
bool mcuxClPsaDriver_Oracle_ElsUtils_IsFreeKeySlot(mcuxClEls_KeyIndex_t keyIdx, uint32_t requiredKeyslots);

/**
 * @brief Retrieve the next keyslot which provides enough space.
 *
 * @param[in] requiredKeyslots The number of (consecutive) slots that are required.
 *
 * @return The index of the available keyslot. If no keyslot could be found,
 *   the returned value is >= MCUXCLELS_KEY_SLOTS.
 */
mcuxClEls_KeyIndex_t mcuxClPsaDriver_Oracle_ElsUtils_GetFreeKeySlot(uint32_t requiredKeyslots);

/**
 * @brief Performs a CKDF to derive key in S50
 *
 * @param[in] derivationKeyIdx Key index used for derivation
 * @param[in] targetKeyIdx Key bank number of the derived key
 * @param[in] targetKeyProperties Requested properties for the derived key. Only set usage bits.
 * @param[in] pDerivationData The algorithm-specific derivation data, the length is
 *
 * @retval PSA_SUCCESS                 The operation was succesful
 * @retval PSA_ERROR_HARDWARE_FAILURE  The ELS operation failed
 */
psa_status_t mcuxClPsaDriver_Oracle_ElsUtils_Ckdf(mcuxClEls_KeyIndex_t derivationKeyIdx,
                                                  mcuxClEls_KeyIndex_t targetKeyIdx,
                                                  mcuxClEls_KeyProp_t targetKeyProperties,
                                                  uint8_t const *pDerivationData);

/**
 * @brief Generates a key in S50
 *
 * @param[in]  options                The command options. For more information, see #mcuxClEls_EccKeyGenOption_t.
 * @param[in]  privateKeyIdx          Output key index.
 * @param[in]  generatedKeyProperties The desired key properties of the generated key.
 * @param[out] pPublicKey             Pointer to the memory area which receives the public key and optionally the key
 *
 * @retval PSA_SUCCESS                 The operation was succesful
 * @retval PSA_ERROR_HARDWARE_FAILURE  The ELS operation failed
 */
psa_status_t mcuxClPsaDriver_Oracle_ElsUtils_EccKeyGen(mcuxClEls_EccKeyGenOption_t options,
                                                       mcuxClEls_KeyIndex_t privateKeyIdx,
                                                       mcuxClEls_KeyProp_t generatedKeyProperties,
                                                       uint8_t *pPublicKey);

/**
 * @brief Deletes a key in S50
 *
 * @param[in]  targetKeyIdx           The index of the key to be deleted.
 *
 * @retval PSA_SUCCESS                 The operation was succesful
 * @retval PSA_ERROR_HARDWARE_FAILURE  The ELS operation failed
 */
psa_status_t mcuxClPsaDriver_Oracle_ElsUtils_KeyDelete(mcuxClEls_KeyIndex_t targetKeyIdx);

/**
 * @brief Executes KeyIn command in S50
 *
 * @param[in]  keyin_command_blob      The KeyIn Command blob.
 * @param[in]  keyin_command_blob_size The KeyIn Command blob size.
 * @param[in]  unwrapKeyIdx            The index of the key that will be used for unwrap operation.
 * @param[in]  targetKeyIdx            The index of the key that will be loaded.
 *
 * @retval PSA_SUCCESS                 The operation was succesful
 * @retval PSA_ERROR_HARDWARE_FAILURE  The ELS operation failed
 */
psa_status_t mcuxClPsaDriver_Oracle_ElsUtils_KeyIn(const uint8_t *keyin_command_blob,
                                                   size_t keyin_command_blob_size,
                                                   mcuxClEls_KeyIndex_t unwrapKeyIdx,
                                                   mcuxClEls_KeyIndex_t targetKeyIdx);

/**
 * @brief Executes CMAC command in S50
 *
 * @param[in]  data                      The  data to be authenticated.
 * @param[in]  data_size                 The data size.
 * @param[in]  authKeyIdx                The index of the auth key that will be used for cmac operation.
 * @param[out] pCmac                     The cmac value.
 *
 * @retval PSA_SUCCESS                 The operation was succesful
 * @retval PSA_ERROR_HARDWARE_FAILURE  The ELS operation failed
 */
psa_status_t mcuxClPsaDriver_Oracle_ElsUtils_Cmac(uint8_t *data,
                                                  size_t data_size,
                                                  mcuxClEls_KeyIndex_t authKeyIdx,
                                                  uint8_t *pCmac);

/**
 * @brief Executes Cipher decrypt command in S50
 *
 * @param[in]  data                      The  data to be decrypted.
 * @param[in]  data_size                 The data size.
 * @param[in]  tfmKekKeyIdx              The index of the tfm kek key that will be used for decrypt operation.
 * @param[in]  iv                        The inital vector value.
 * @param[out] pOut                      The decrypted value.
 *
 * @retval PSA_SUCCESS                 The operation was succesful
 * @retval PSA_ERROR_HARDWARE_FAILURE  The ELS operation failed
 */
psa_status_t mcuxClPsaDriver_Oracle_ElsUtils_Cipher_Decrypt(
    const uint8_t *data, size_t data_size, mcuxClEls_KeyIndex_t tfmKekKeyIdx, const uint8_t *iv, uint8_t *pOut);

#endif //_MCUXCLPSADRIVER_ORACLE_ELSUTILS_
