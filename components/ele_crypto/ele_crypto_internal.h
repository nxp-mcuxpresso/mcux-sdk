/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef __ELE_CRYPTO_INTERNAL_H__
#define __ELE_CRYPTO_INTERNAL_H__

#include "fsl_common.h"
#include "fsl_device_registers.h"
#include "fsl_s3mu.h"

/*******************************************************************************
 * Definitions
 *******************************************************************************/
#define RESPONSE_SUCCESS                    (0xd6u)
#define RESPONSE_ERROR_SIZE                 (0x1d29u)
#define SHIFT_16                            (16u)
#define SHIFT_8                             (8u)
#define MSG_TAG_CMD                         (0x17u)
#define MSG_TAG_RESP                        (0xE1u)
#define MSG_RESPONSE_MAX                    (16u)
#define NEGATIVE_ONE_TWOS_COMPLEMENT_16_BIT (0xffffu)

#define LOAD_FW                  (0x17020406u)
#define LOAD_FW_SIZE             (0x4u)
#define LOAD_FW_RESPONSE_HDR     (0xe1020206u)
#define LOAD_FW_RESPONSE_SUCCESS (0x000000d6u)

#define INIT_SERVICES              (0x17170107u)
#define INIT_SERVICES_SIZE         (1u)
#define INIT_SERVICES_RESPONSE_HDR (0xe1170207u)

#define OPEN_SESSION              (0x17100307u)
#define OPEN_SESSION_SIZE         (0x3u)
#define OPEN_SESSION_RESPONSE_HDR (0xe1100307u)

#define CLOSE_SESSION              (0x17110207u)
#define CLOSE_SESSION_SIZE         (0x2u)
#define CLOSE_SESSION_RESPONSE_HDR (0xe1110207u)

#define OPEN_HASH_SESSION              (0x17900607u)
#define OPEN_HASH_SESSION_SIZE         (0x6u)
#define OPEN_HASH_SESSION_RESPONSE_HDR (0xe1900307u)

#define CLOSE_HASH_SESSION              (0x17910207u)
#define CLOSE_HASH_SESSION_SIZE         (0x2u)
#define CLOSE_HASH_SESSION_RESPONSE_HDR (0xe1910207u)

#define OPEN_CIPHER_SESSION              (0x17600607u)
#define OPEN_CIPHER_SESSION_SIZE         (0x6u)
#define OPEN_CIPHER_SESSION_RESPONSE_HDR (0xe1600307u)

#define CLOSE_CIPHER_SESSION              (0x17610207u)
#define CLOSE_CIPHER_SESSION_SIZE         (0x2u)
#define CLOSE_CIPHER_SESSION_RESPONSE_HDR (0xe1610207u)

#define CIPHER_ONE_GO              (0x17620B07u)
#define CIPHER_ONE_GO_SIZE         (0xBu)
#define CIPHER_ONE_GO_RESPONSE_HDR (0xe1620307u)

#define CIPHER_AEAD              (0x17640D07u)
#define CIPHER_AEAD_SIZE         (0xDu)
#define CIPHER_AEAD_RESPONSE_HDR (0xe1640307u)

#define OPEN_MAC_SESSION              (0x17500607u)
#define OPEN_MAC_SESSION_SIZE         (0x6u)
#define OPEN_MAC_SESSION_RESPONSE_HDR (0xe1500307u)

#define CLOSE_MAC_SESSION              (0x17510207u)
#define CLOSE_MAC_SESSION_SIZE         (0x2u)
#define CLOSE_MAC_SESSION_RESPONSE_HDR (0xe1510207u)

#define MAC_ONE_GO               (0x17520907u)
#define MAC_ONE_GO_SIZE          (0x9u)
#define MAC_ONE_GO_RESPONSE_HDR  (0xe1520407u)
#define MAC_ONE_GO_MAC_SIZE_MASK (0xffffu)

#define OPEN_RNG_SESSION              (0x17200607u)
#define OPEN_RNG_SESSION_SIZE         (0x6u)
#define OPEN_RNG_SESSION_RESPONSE_HDR (0xe1200307u)

#define CLOSE_RNG_SESSION              (0x17210207u)
#define CLOSE_RNG_SESSION_SIZE         (0x2u)
#define CLOSE_RNG_SESSION_RESPONSE_HDR (0xe1210207u)

#define GET_RNG_RANDOM              (0x17CD0407u)
#define GET_RNG_RANDOM_SIZE         (0x4u)
#define GET_RNG_RANDOM_RESPONSE_HDR (0xe1CD0207u)

#define START_RNG              (0x17a30106u)
#define START_RNG_SIZE         (0x1u)
#define START_RNG_RESPONSE_HDR (0xe1a30206u)

#define HASH_HDR             (0x17CC0A07u)
#define HASH_SIZE            (0xau)
#define HASH_RESPONSE_HDR    (0xe1cc0407u)
#define HASH_CTX_SIZE_SHA224 (112u)
#define HASH_CTX_SIZE_SHA256 (112u)
#define HASH_CTX_SIZE_SHA384 (216u)
#define HASH_CTX_SIZE_SHA512 (216u)
#define HASH_CTX_SIZE_SM3256 (216u)

#define HMAC_GENERIC_HDR          (0x17CE0907u)
#define HMAC_GENERIC_SIZE         (0x9u)
#define HMAC_GENERIC_RESPONSE_HDR (0xe1ce0207u)

#define FAST_MAC_START_SIZE         (0x4u)
#define FAST_MAC_START              (0x17d00407u)
#define FAST_MAC_START_RESPONSE_HDR (0xe1d00207u)

#define FAST_MAC_PROCEED_SIZE         (0x4u)
#define FAST_MAC_PROCEED              (0x17d10407u)
#define FAST_MAC_PROCEED_RESPONSE_HDR (0xe1d10307u)

#define FAST_MAC_END_SIZE         (0x1u)
#define FAST_MAC_END              (0x17d20107u)
#define FAST_MAC_END_RESPONSE_HDR (0xe1d20207u)

#define OPEN_KEY_STORE              (0x17300607u)
#define OPEN_KEY_STORE_SIZE         (0x6u)
#define OPEN_KEY_STORE_RESPONSE_HDR (0xe1300307u)
#define MIN_MAC_LEN_SHIFT           (24u)
#define MIN_MAC_FLAG_SHIFT          (19u)
#define KEYSTORE_CREATE_SHIFT       (16u)

#define CLOSE_KEY_STORE              (0x17310307u)
#define CLOSE_KEY_STORE_SIZE         (0x3u)
#define CLOSE_KEY_STORE_RESPONSE_HDR (0xe1310207u)

#define KEY_MNG_OPEN              (0x17400607u)
#define KEY_MNG_OPEN_SIZE         (0x6u)
#define KEY_MNG_OPEN_RESPONSE_HDR (0xe1400307u)

#define KEY_MNG_CLOSE              (0x17410207u)
#define KEY_MNG_CLOSE_SIZE         (0x2u)
#define KEY_MNG_CLOSE_RESPONSE_HDR (0xe1410207u)

#define KEY_MNG_GROUP              (0x17450307u)
#define KEY_MNG_GROUP_SIZE         (0x3u)
#define KEY_MNG_GROUP_RESPONSE_HDR (0xe1450207u)

#define KEY_GEN               (0x17420C07u)
#define KEY_GEN_SIZE          (0xcu)
#define KEY_GEN_RESPONSE_HDR  (0xe1420407u)
#define KEY_GEN_KEY_SIZE_MASK (0xffffu)

#define PUB_KEY_GEN               (0x17320707u)
#define PUB_KEY_GEN_SIZE          (0x7u)
#define PUB_KEY_GEN_RESPONSE_HDR  (0xe1320307u)
#define PUB_KEY_GEN_KEY_SIZE_MASK (0xffffu)

#define KEY_DEL              (0x174e0407u)
#define KEY_DEL_SIZE         (0x4u)
#define KEY_DEL_RESPONSE_HDR (0xe14e0207u)

#define SIGN_OPEN              (0x17700607u)
#define SIGN_OPEN_SIZE         (0x6u)
#define SIGN_OPEN_RESPONSE_HDR (0xe1700307u)

#define SIGN_CLOSE              (0x17710207u)
#define SIGN_CLOSE_SIZE         (0x2u)
#define SIGN_CLOSE_RESPONSE_HDR (0xe1710207u)

#define SIGN_CMD                 (0x17720a07u)
#define SIGN_SIZE                (0xau)
#define SIGN_RESPONSE_HDR        (0xe1720307u)
#define SIGN_SIGNATURE_SIZE_MASK (0xffffu)

#define VERIFY_OPEN              (0x17800607u)
#define VERIFY_OPEN_SIZE         (0x6u)
#define VERIFY_OPEN_RESPONSE_HDR (0xe1800307u)

#define VERIFY_CLOSE              (0x17810207u)
#define VERIFY_CLOSE_SIZE         (0x2u)
#define VERIFY_CLOSE_RESPONSE_HDR (0xe1810207u)

#define VERIFY_CMD                 (0x17820c07u)
#define VERIFY_SIZE                (0xcu)
#define VERIFY_RESPONSE_HDR        (0xe1820307u)
#define VERIFY_RESPONSE_SUCCESS    (0x5a3cc3a5u)
#define VERIFY_FLAG_INTERNAL_SHIFT (2u)

#define NVM_STORAGE_OPEN              (0x17E00607u)
#define NVM_STORAGE_OPEN_SIZE         (0x6u)
#define NVM_STORAGE_OPEN_RESPONSE_HDR (0xe1E00307u)

#define NVM_STORAGE_CLOSE              (0x17E10207u)
#define NVM_STORAGE_CLOSE_SIZE         (0x2u)
#define NVM_STORAGE_CLOSE_RESPONSE_HDR (0xe1E10207u)

#define NVM_MASTER_IMPORT              (0x17E20407u)
#define NVM_MASTER_IMPORT_SIZE         (0x4u)
#define NVM_MASTER_IMPORT_RESPONSE_HDR (0xe1E20207u)

#define DATA_STORAGE_OPEN              (0x17A00607u)
#define DATA_STORAGE_OPEN_SIZE         (0x6u)
#define DATA_STORAGE_OPEN_RESPONSE_HDR (0xe1A00307u)

#define DATA_STORAGE_CLOSE              (0x17A10207u)
#define DATA_STORAGE_CLOSE_SIZE         (0x2u)
#define DATA_STORAGE_CLOSE_RESPONSE_HDR (0xe1A10207u)

#define STORAGE_DATA                 (0x17A20807u)
#define STORAGE_DATA_SIZE            (0x8u)
#define STORAGE_DATA_RESPONSE_HDR    (0xE1A20307u)
#define STORAGE_DATA_OPTION_SHIFT    (0u)
#define STORAGE_DATA_OPERATION_SHIFT (1u)

#define STORAGE_EXPORT_CHUNK_SIZE              (0x3u)
#define STORAGE_MASTER_EXPORT_CHUNK_SIZE       (0x4u)
#define STORAGE_EXPORT_RESPONSE_REQ_HDR        (0x17e50707u)
#define STORAGE_EXPORT_MASTER_RESPONSE_REQ_HDR (0x17e30307u)
#define EXPORT_CHUNK_RESPONSE_HDR              (0xE1E50307u)
#define EXPORT_MASTER_CHUNK_RESPONSE_HDR       (0xE1E30407u)
#define EXPORT_FINISH_HDR                      (0x17e40307u)
#define EXPORT_STATUS_SUCCESS                  (0xba2cc2abu)
#define EXPORT_FINISH_RESPONSE_HDR             (0xE1E40307u)

#define STORAGE_GET_CHUNK_SIZE       (4u)
#define STORAGE_GET_RESPONSE_REQ_HDR (0x17e60607u)
#define GET_CHUNK_RESPONSE_HDR       (0xE1E60407u)
#define GET_DONE_HDR                 (0x17e70307u)
#define GET_STATUS_SUCCESS           (0xca3bb3acu)
#define GET_DONE_RESPONSE_HDR        (0xE1E70207u)
#define GET_DONE_RESPONSE_SIZE       (2u)

#define GENERIC_CIPHER              (0x17c80a07u)
#define GENERIC_CIPHER_SIZE         (0xau)
#define GENERIC_CIPHER_RESPONSE_HDR (0xe1c80207u)

#define GENERIC_AEAD              (0x17c90e07u)
#define GENERIC_AEAD_SIZE         (0xeu)
#define GENERIC_AEAD_RESPONSE_HDR (0xe1c90207u)

#define GENERIC_ASYMMETRIC                        (0x17ca1007u)
#define GENERIC_ASYMMETRIC_SIZE                   (0x10u)
#define GENERIC_ASYMMETRIC_RESPONSE_HDR           (0xe1ca0607u)
#define GENERIC_ASYMMETRIC_SALT_SIZE_EQ_HASH_SIZE (-1)

#define GENERIC_RSA_KEYGEN               (0x17cb0b07u)
#define GENERIC_RSA_KEYGEN_SIZE          (0xbu)
#define GENERIC_RSA_KEYGEN_RESPONSE_HDR  (0xe1cb0207u)
#define GENERIC_RSA_KEY_PAIR             (0x7001u)
#define GENERIC_RSA_INPUT_TYPE_FLAG_MASK (0x01u)

#define PING              (0x17010106u)
#define PING_SIZE         (0x1u)
#define PING_RESPONSE_HDR (0xe1010206u)

#define GET_FW_VERSION              (0x179D0106u)
#define GET_FW_VERSION_SIZE         (0x1u)
#define GET_FW_VERSION_RESPONSE_HDR (0xe19D0406u)

#define GET_FW_STATUS              (0x17C50106u)
#define GET_FW_STATUS_SIZE         (0x1u)
#define GET_FW_STATUS_RESPONSE_HDR (0xe1C50306u)

#define ENABLE_APC              (0x17D20106u)
#define ENABLE_APC_SIZE         (0x1u)
#define ENABLE_APC_RESPONSE_HDR (0xe1D20206u)

#define FORWARD_LIFECYCLE              (0x17950206u)
#define FORWARD_LIFECYCLE_SIZE         (0x2u)
#define FORWARD_LIFECYCLE_RESPONSE_HDR (0xe1950206u)

#define READ_FUSE              (0x17970206u)
#define READ_FUSE_SIZE         (0x2u)
#define READ_FUSE_RESPONSE_HDR (0xe1970306u)

#define RELEASE_RDC              (0x17C40206u)
#define RELEASE_RDC_SIZE         (0x2u)
#define RELEASE_RDC_RESPONSE_HDR (0xe1C40206u)

#define WRITE_FUSE              (0x17d60306u)
#define WRITE_FUSE_SIZE         (0x03u)
#define WRITE_FUSE_RESPONSE_HDR (0xe1d60306u)
#define LOCK_SHIFT              (31u)
#define BIT_LENGTH_SHIFT        (16u)

/* 00 is replaced by actual command in ELE_SendSignedMsg() */
#define SEND_SIGNED              (0x17000306u)
#define SEND_SIGNED_SIZE         (0x3u)
#define SEND_SIGNED_RESPONSE_HDR (0xe1000306u)

#define GET_TRNG_STATE              (0x17a40106u)
#define GET_TRNG_STATE_SIZE         (0x1u)
#define GET_TRNG_STATE_RESPONSE_HDR (0xe1a40306u)

#define GET_INFO              (0x17DA0406u)
#define GET_INFO_SIZE         (0x4u)
#define GET_INFO_RESPONSE_HDR (0xe1DA0206u)

#if defined(FSL_FEATURE_SOC_OTFAD_COUNT) && (FSL_FEATURE_SOC_OTFAD_COUNT > 1)
#define ENABLE_OTFAD      (0x17c60206u)
#define ENABLE_OTFAD_SIZE (2u)
#else
#define ENABLE_OTFAD      (0x17c60106u)
#define ENABLE_OTFAD_SIZE (1u)
#endif /* FSL_FEATURE_SOC_OTFAD_COUNT */
#define ENABLE_OTFAD_RESPONSE_HDR (0xe1c60206u)

#define ATTEST              (0x17DB0906u)
#define ATTEST_SIZE         (0x9u)
#define ATTEST_RESPONSE_HDR (0xe1DB0206u)

#define CLOCK_CHANGE_START              (0x17100106u)
#define CLOCK_CHANGE_START_SIZE         (0x1u)
#define CLOCK_CHANGE_START_RESPONSE_HDR (0xe1100206u)

#define CLOCK_CHANGE_FINISH              (0x17110206u)
#define CLOCK_CHANGE_FINISH_SIZE         (0x2u)
#define CLOCK_CHANGE_FINISH_RESPONSE_HDR (0xe1110206u)
#define GENERATE_KEY_BLOB                (0x17af0806u)
#define GENERATE_KEY_BLOB_SIZE           (0x8u)
#define GENERATE_KEY_BLOB_RESPONSE_HDR   (0xe1af0206u)

#define LOAD_KEY_BLOB              (0x17a70406u)
#define LOAD_KEY_BLOB_SIZE         (0x4u)
#define LOAD_KEY_BLOB_RESPONSE_HDR (0xe1a70206u)

#define KEY_BLOB_PAYLOAD_HDR_LENGTH (8u)
#define KEY_BLOB_IEE_PAYLOAD_LENGTH (80u)

/* Keyblob generation masks */
#define KEY_BLOB_PAYLOAD_LENGTH_MASK     (0x00ffff00u)
#define KEY_BLOB_PAYLOAD_ALGORITHM_MASK  (0x00ff0000u)
#define KEY_BLOB_PAYLOAD_SIZE_MASK       (0x0000ff00u)
#define KEY_BLOB_PAYLOAD_TYPE_MASK       (0x00000007u)
#define KEY_BLOB_PAYLOAD_IEE_LOCK_MASK   (0x00000100u)
#define KEY_BLOB_PAYLOAD_IEE_REGION_MASK (0x000000ffu)

#define STORAGE_MASTER_EXPORT_CMD  (0xE3u)
#define STORAGE_EXPORT_FINISH_CMD  (0xE4u)
#define STORAGE_CHUNK_EXPORT_CMD   (0xE5u)
#define STORAGE_GET_CHUNK_CMD      (0xE6u)
#define STORAGE_GET_CHUNK_DONE_CMD (0xE7u)

#define IMPORT_KEY              (0x174f0706u)
#define IMPORT_KEY_SIZE         (0x7u)
#define IMPORT_KEY_RESPONSE_HDR (0xe14f0306u)

#define PROGRAM_BBSM              (0x17bb0406u)
#define PROGRAM_BBSM_SIZE         (0x4u)
#define PROGRAM_BBSM_RESPONSE_HDR (0xe1bb0306u)
#define PROGRAM_BBSM_WRITE_OP     (0x71u)
#define PROGRAM_BBSM_READ_OP      (0x6au)
#define PROGRAM_BBSM_SET_POLICY   (0xcau)

#define GET_EVENT              (0x17a20106u)
#define GET_EVENT_SIZE         (0x1u)
#define GET_EVENT_RSP_SIZE     (0xcu)
#define GET_EVENT_RESPONSE_HDR (0xe1a20c06u)

/* Key Import flag shifts */
#define IMPORT_KEY_GROUP_AUTO_FLAG_SHIFT (2u)
#define IMPORT_KEY_MONOTONIC_FLAG_SHIFT  (5u)
#define IMPORT_KEY_SYNC_FLAG_SHIFT       (7u)

typedef struct chunk_export_req
{
    mu_hdr_t header;
    uint32_t storage_handle;
    uint32_t chunk_size;
    uint32_t blob_id_msb;
    uint32_t blob_id_lsb;
    uint32_t blob_id_ext;
    uint32_t crc;
} chunk_export_req_t;

typedef struct chunk_export_respond
{
    mu_hdr_t header;
    uint32_t response_code;
    uint32_t chunk_addr;
} chunk_export_respond_t;

typedef struct chunk_master_export_respond
{
    mu_hdr_t header;
    uint32_t storage_handle;
    uint32_t response_code;
    uint32_t chunk_addr;
} chunk_master_export_respond_t;

typedef struct chunk_get_req
{
    mu_hdr_t header;
    uint32_t storage_handle;
    uint32_t blob_id_msb;
    uint32_t blob_id_lsb;
    uint32_t blob_id_ext;
    uint32_t crc;
} chunk_get_req_t;

typedef struct chunk_get_respond
{
    mu_hdr_t header;
    uint32_t chunk_size;
    uint32_t chunk_addr;
    uint32_t response_code;
} chunk_get_respond_t;

typedef struct chunk_get_done
{
    mu_hdr_t header;
    uint32_t storage_handle;
    uint32_t status;
} chunk_get_done_t;

typedef struct chunk_get_done_resp
{
    mu_hdr_t header;
    uint32_t status;
} chunk_get_done_resp_t;

/*! @brief ELE Chunk export finish command structure. */
typedef struct chunk_export_finish
{
    mu_hdr_t header;         /*!< Command header */
    uint32_t storage_handle; /*!< NVM storage ID */
    uint32_t status;         /*!< Status of export operation*/
} chunk_export_finish_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
status_t ELE_StorageExportFinish(S3MU_Type *mu, uint32_t nvmStorageID);

status_t nvm_storage_handle_req(S3MU_Type *mu, uint32_t *buf, uint32_t wordCount);

/*!
 * brief Get response from MU
 *
 * This function reads response data from EdgeLock Enclave if available.
 *
 * param base MU peripheral base address
 * param buf buffer to store read data
 * param wordCount size of data in words
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ele_mu_get_response(S3MU_Type *mu, uint32_t *buf);

/* If addr is NULL, allocate on heap, eitherway return a given addr */
void *malloc_if_not_null(void *addr, size_t size);

#endif /* __ELE_CRYPTO_INTERNAL_H__ */
