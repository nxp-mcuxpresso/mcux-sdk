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

/** @file  mcuxClPsaDriver_Oracle.h
 *  @brief API definition of the PSA driver Oracle */

#ifndef MCUXCLPSADRIVERORACLE_H_
#define MCUXCLPSADRIVERORACLE_H_

#include <crypto.h>
#include <mcuxClKey.h>
#include <mcuxClConfig.h> // Exported features flags header

#ifdef __cplusplus
extern "C" {
#endif

// GENERAL NOTE
// do not use mcuxClKey_setKeyproperties on any of these keys as it will overwrite pAuxData

/**
 * @brief Oracle function for exporting of the public key created in ELS during KEY_GEN command
 *
 * @param[in] pKey is the reference to the key descriptor of the ELS
 * @param[out] data is the buffer including the exported public key
 * @param[in] data_size is the size of the allocated memory for the data buffer
 * @param[out] data_length is the lenght of the exported key
 * @param[in] internal_representation is the flag to indicate internal representation
 *
 * @retval PSA_SUCCESS                 The operation was succesful
 * @retval PSA_ERROR_DOES_NOT_EXIST    No key with the associated key_id found in ELS
 */
psa_status_t mcuxClPsaDriver_Oracle_ExportPublicKey(mcuxClKey_Descriptor_t *pKey,
                                                   uint8_t *data,
                                                   size_t data_size,
                                                   size_t *data_length,
                                                   bool internal_representation);

/**
    @brief Oracle function for loading a key

    This function loads an encoded or internal key to memory or the S50 key store.

    PRECONDITION:
        The fields of @p pKey are initialized as follows:
        - container.pData    : points to the psa key buffer (key_buffer)
        - container.length   : set to the length of the psa key buffer (key_buffer_size)
        - container.used     : set to the length of the psa key buffer (key_buffer_size)
        - container.pAuxData : points to the psa attributes (attributes)
        All other fields can be uninitialized

    POSTCONDITION:
        In case the key is loaded into memory the fields of @p pKey are initialized as follows:
        - location.pData  : points to the memory location where the key is loaded, this memory is
                            allocated by the Oracle
        - location.length : the length of the key that was loaded to memory; i.e. the buffer length
        - location.slot   : does not matter, suggest using 0xFFFFFFu
        - location.status : MCUXCLKEY_LOADSTATUS_MEMORY
        In case the key is loaded into an S50 key slot the fields of @p pKey are initialized as follows:
        - location.pData  : does not matter, suggest NULL
        - location.length : the length of the key that was loaded to the S50 key slot
        - location.slot   : the S50 key slot to which the key was loaded
        - location.status : MCUXCLKEY_LOADSTATUS_COPRO

    OPERATION:
        Depending on the location attribute in the psa attributes, the Oracle allocates a memory location
        or free key slot in the S50 (the Oracle is responsible for the memory management) and loads the
        key there. How the location attributes map to endoding or derivation methods is entirely up to
        the design of the Oracle; e.g. a key could be decrypted from a blob or derived from a master key.

    @retval PSA_SUCCESS                 The operation was succesful
    @retval PSA_ERROR_NOT_SUPPORTED     The Oracle shall never return this error code
    @retval PSA_ERROR_GENERIC_ERROR     The operation failed (other error codes can be used as well if more specific)

*/
psa_status_t mcuxClPsaDriver_Oracle_LoadKey( mcuxClKey_Descriptor_t   *pKey );

/**
    @brief Oracle function for 'suspending' a key

    This function indicates to the Oracle that the key will temporarily not be used by the psa driver.
    This allows the Oracle to perform memory management operations on this key.

    @retval PSA_SUCCESS                 The operation was succesful
    @retval PSA_ERROR_NOT_SUPPORTED     The Oracle shall never return this error code
    @retval PSA_ERROR_GENERIC_ERROR     The operation failed (other error codes can be used as well if more specific)

*/
psa_status_t mcuxClPsaDriver_Oracle_SuspendKey( mcuxClKey_Descriptor_t   *pKey );

/**
    @brief Oracle function for 'resuming' a previously 'suspended' key

    This function indicates to the Oracle that the key will be used agian by the psa driver.
    The Oracle should assure it is available again and may therefore need to re-allocate, re-load the key
    and update the key fields.

    @retval PSA_SUCCESS                 The operation was succesful
    @retval PSA_ERROR_NOT_SUPPORTED     The Oracle shall never return this error code
    @retval PSA_ERROR_GENERIC_ERROR     The operation failed (other error codes can be used as well if more specific)

*/
psa_status_t mcuxClPsaDriver_Oracle_ResumeKey( mcuxClKey_Descriptor_t   *pKey );

/**
    @brief Oracle function for 'unloading' a previously loaded key

    This function indicates to the Oracle that the key will not be used any more by the psa driver.
    This allows the Oracle to free the allocated storage for this key.

    @retval PSA_SUCCESS                 The operation was succesful
    @retval PSA_ERROR_NOT_SUPPORTED     The Oracle shall never return this error code
    @retval PSA_ERROR_GENERIC_ERROR     The operation failed (other error codes can be used as well if more specific)

*/
psa_status_t mcuxClPsaDriver_Oracle_UnloadKey( mcuxClKey_Descriptor_t   *pKey );

/**
    @brief Oracle function for allocating storage for a key that will be created by the psa driver

    This function requests storage space from the Oracle for a key that will be created by the psa driver.
    The Oracle shall allocate memory space or a key slot capable of holding the to be generated key.

    @retval PSA_SUCCESS                 The operation was succesful
    @retval PSA_ERROR_NOT_SUPPORTED     The Oracle shall never return this error code
    @retval PSA_ERROR_GENERIC_ERROR     The operation failed (other error codes can be used as well if more specific)

*/
psa_status_t mcuxClPsaDriver_Oracle_ReserveKey( mcuxClKey_Descriptor_t   *pKey );

/**
    @brief Oracle function for saving a key

    This function saves a key from memory or the S50 key store to an encoded format (blob).

    @retval PSA_SUCCESS                 The operation was succesful
    @retval PSA_ERROR_NOT_SUPPORTED     The Oracle shall never return this error code
    @retval PSA_ERROR_GENERIC_ERROR     The operation failed (other error codes can be used as well if more specific)

*/
psa_status_t mcuxClPsaDriver_Oracle_StoreKey( mcuxClKey_Descriptor_t   *pKey );

/**
 * @brief Oracle function for executing S50 specific activities when the import of key is done
 * the PSA library will proceed with storing the key. After the evaluation the function will generate
 * the buffer which will be stored in the memory by the PSA
 *
 * @param[in] attributes defines the attributes associated with the input buffer
 *   PRECONDITION:
 *       The fields of pKey are initialized as follows:
 *       - container.pData    : points to the psa key buffer (key_buffer)
 *       - container.length   : set to the length of the psa key buffer (key_buffer_size)
 *       - container.used     : set to the length of the psa key buffer (key_buffer_size)
 *       - container.pAuxData : points to the psa attributes (attributes)
 *       All other fields shall be initialized
 *
 * @param[in] pKey  is the reference to the key descriptor of the ELS
 * @param[in] data is the buffer including public key for import
 * @param[in] data_length is the length of data
 * @param[out] key_buffer_length is the effective number of data filled in the key_buffer returned by the function
 * @param[out] bits is the number of bits representing the key (e.g. 256 for the NISTP 256 key)
 *
 * @retval PSA_SUCCESS                          The operation was succesful
 * @retval PSA_ERROR_NOT_SUPPORTED              The lifetime is not supported, meaning that fallback functions will be
 *                                              executed by Oracle
 * @retval PSA_ERROR_INSUFFICIENT_MEMORY        The key_buffer size is not enough to include data to be stored
 */
psa_status_t mcuxClPsaDriver_Oracle_ImportKey(mcuxClKey_Descriptor_t  *pKey,
                                             const uint8_t *data,
                                             size_t data_length,
                                             size_t *key_buffer_length,
                                             size_t *bits);

/**
 * @brief Oracle function for determine the size required for a key buffer from the data supplied when
 * importing a key.
 *
 * The size of the data required to store a key is not necessarily the same as the size of the date supplied when
 * importing a key. In particular for key recipes, the recipe gets parsed upon import and stored in an internal
 * representation which consumes a different amount of space.
 *
 * @param[in] attributes defines the attributes associated with the input buffer
 * @param[in] data includes the input buffer as passed to the psa import function
 * @param[in] data_length is the length of data
 * @param[out] key_buffer is the buffer which will be stored by PSA in the memory
 * @param[out] key_buffer_length is the required number of bytes required as key_buffer
 *
 * @retval PSA_SUCCESS                          The operation was succesful
 * @retval PSA_ERROR_NOT_SUPPORTED              The lifetime is not supported, meaning that fallback functions will be
 * executed by Oracle
 * @retval PSA_ERROR_INSUFFICIENT_MEMORY        The key_buffer size is not enough to include data to be stored
 */
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_Oracle_GetKeyBufferSizeFromKeyData(const psa_key_attributes_t *attributes,
                                                               const uint8_t *data,
                                                               size_t data_length,
                                                               size_t *key_buffer_length);
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()

/**
 * @brief Oracle function for making keys that are installed upon boot in S50 and keys derived
 * from those (built-in) available to be used with PSA API.
 *
 * PSA does store information about such keys (either the S50 slot number or a
 * derivation recipe). Therefore it needs to know the size to reserve for a particular key.
 *
 * @param[in] key_id the PSA key id of a built-in key
 * @param[out] key_buffer_size the required size of the buffer to store a built-in key
 */
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_Oracle_GetBuiltinKeyBufferSize(mbedtls_svc_key_id_t key_id, size_t *key_buffer_size);
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()

/**
 * @brief Oracle function for making keys that are installed upon boot in S50 and keys derived
 * from those (built-in) available to be used with PSA API.
 *
 * PSA does store information about such keys (either the S50 slot number or a
 * derivation recipe). This function fills the PSA owned buffer with the required information to use the key.
 *
 * @param[in] attributes defines the attributes associated with the input buffer
 * @param[out] key_buffer is the buffer which will be stored by PSA in the memory
 * @param[in] key_buffer_size is the size of the allocated
 * @param[out] key_buffer_length is the effective number of data filled in the key_buffer by the function
 */
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_Oracle_GetBuiltinKeyBuffer(psa_key_attributes_t *attributes,
                                                       uint8_t *key_buffer,
                                                       size_t key_buffer_size,
                                                       size_t *key_buffer_length);
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLPSADRIVERORACLE_H_ */
