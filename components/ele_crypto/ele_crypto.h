/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef __ELE_CRYPTO_H__
#define __ELE_CRYPTO_H__

#include "fsl_common.h"
#include "fsl_device_registers.h"

/*!
 * @addtogroup ele_crypto
 * @{
 */

/*******************************************************************************
 * Definitions
 *******************************************************************************/
/*! @name Version */
/*! @{ */
/*! @brief Defines ELE Crypto version 2.10.0.
 *
 * Change log:
 *
 * - Version 2.10.0
 *   - Add support for updated Fast MAC
 *   - Add RNG reseed option to ELE_RngGetRandom()
 *
 * - Version 2.9.0
 *   - Add option for user to specify a key ID in ELE_GenerateKey()
 *   - Fix incompatible pointer type warning on ARMGCC
 *   - Add Enable OTFAD API
 *   - Add Clock Change API
 *   - Add Key Blob Generation, Key Blob Loading
 *   - Add Import Key API
 *   - Add CACHE handling in write-trough mode
 *   - Fix MISRA
 *   - Add TRNG Get State API
 *   - Fix missing salt size field in ELE_Sign() and ELE_Verify()
 *
 * - Version 2.8.0
 *   - Fix incorrect value for kPermitted_All_Cipher
 *   - Fix missing call to ADD_OFFSET()
 *
 * - Version 2.7.0
 *   - Add ELE_InitServices, support OFB/CFB cipher modes in HSM
 *   - Add Fast HMAC API
 *   - Support RSA in HSM
 *   - Update key/data storage APIs
 *   - Fix MISRA
 *
 * - Version 2.6.0
 *   - Add CTR, OFB and CFB modes of operation to AES
 *   - Add baseline API: Attestation
 *
 * - Version 2.5.0
 *   - Add signature size output parameter to ELE_Sign()
 *   - Add hash size output parameter to ELE_Hash(), ELE_Hash_Finish(),
 *     and ELE_GenericHmac()
 *   - Make the order of parameters more uniform across these functions
 *   - Add support for RSA sign / verify flag setting
 *   - Support for (-1) salt size
 *   - Add key size output parameter to key generation functions
 *   - Add MAC size output parameter to ELE_Mac()
 *   - Add support for starting the ELE RNG with ELE_StartRng()
 *   - Remove check for NULL input message in ELE_Hash() and ELE_GenericHmac()
 *   - Add ELE_DeleteKey() and add support to ELE_GenerateKey() for setting flags
 *
 * - Version 2.4.0
 *   - Added support of NVM Manager Registration.
 *   - Added API's for key/chunk management from/to NVM.
 *
 * - Version 2.3.0
 *   - Added Cipher commands
 *   - Added NVM Keystore and key/chunk management
 *
 * - Version 2.2.0
 *   - Added base API commands
 *
 * - Version 2.1.0
 *   - Add NVM memory support
 *
 * - Version 2.0.0
 *   - initial version
 */
#define FSL_ELE_CRYPTO_VERSION (MAKE_VERSION(2, 10, 0))
/*! @} */

enum
{
    kStatus_ELE_BufferTooSmall =
        MAKE_STATUS(kStatusGroup_ELE, 0x1u), /*!< ELE status for buffer sizes that are too small. */
};

/*******************************************************************************
 * CACHE Handling Definitions
 ******************************************************************************/
/*!
 * @addtogroup ele_crypto_cache
 * @{
 */
#if defined(CACHE_MODE_WRITE_THROUGH) && (CACHE_MODE_WRITE_THROUGH > 0u)
#define ELE_CACHE_HANDLING (1u)
/* Note: CACHE handling on ELE Crypto level work only with cache policy set to write-trough,
 *       because ELE doesn't own the buffers. If write-back is required,
 *       user needs to handle it on system/application level.
 */
#endif

/*!
 *@}
 */ /* end of ele_crypto_cache */

/*******************************************************************************
 * HASH Definitions
 ******************************************************************************/
/*!
 * @addtogroup ele_crypto_hash
 * @{
 */

/*! @brief Supported cryptographic block cipher functions for HASH creation (PSA values) */
typedef enum _hash_algo_t
{
    kELE_Sha224 = 0x02000008, /*!< SHA_224  */
    kELE_Sha256 = 0x02000009, /*!< SHA_256  */
    kELE_Sha384 = 0x0200000A, /*!< SHA_384  */
    kELE_Sha512 = 0x0200000B, /*!< SHA_512  */
    kELE_SM3256 = 0x02000014, /*!< SM3_256  */
} hash_algo_t;

/*!
 *@}
 */ /* end of ele_crypto_hash */

/*******************************************************************************
 * KEYSTORE Definitions
 ******************************************************************************/
/*!
 * @addtogroup ele_crypto_keystore
 * @{
 */

/*! @brief ELE KeyStore structure. */
typedef struct _ele_keystore
{
    uint32_t id;          /*!< User defined word identifying the key store */
    uint32_t nonce;       /*!< Nonce used as authentication proof for accessing the key store */
    uint16_t max_updates; /*!< Maximum number of updates authorized on this storage. */
    bool min_mac_check;   /*!< If set TRUE, minimal MAC length check is used */
    uint8_t min_mac_len;  /*!< The minimum MAC length (in bits) accepted by the EdgeLock Enclave to perform MAC
                             verification operations */
} ele_keystore_t;

/*!
 *@}
 */ /* end of ele_crypto_keystore */

/*******************************************************************************
 * KEY GROUP MANAGE Definitions
 ******************************************************************************/
/*!
 * @addtogroup ele_crypto_key_group_mng
 * @{
 */

/*! @brief Supported key group manage operations */
typedef enum _key_group_mng_t
{
    kELE_keyMngLock   = 0x1u, /*!< Lock the key group */
    kELE_keyMngUnlock = 0x2u, /*!< Unlock the key group */
    kELE_keyMngImport = 0x4u, /*!< Import the key group. It will trigger a Storage get chunk. */
    kELE_keyMngExport = 0x8u, /*!< Export the key group. It will trigger a Storage chunk export. */
} key_group_mng_t;

#define MASTER_CHUNK_SIZE 0x64u /*!< Master chunk size is always 100 Bytes */
#define SYNC_OP           0x80u /*!< Sync operation. The request is completed only when the key group, */
                                /*!< keystore and master chunks are exported. */
#define SYNC_OP_NO_KEY 0x40u    /*!< Sync operation. Only Keystore and Master storage chunks are exported. */
#define SYNC_MONOTONIC 0x20u    /*!< Update monotonic counter (anti-rollback protection). */

/*!< keystore chunk and master chunk has been written in the NVM and the monotonic counter has been updated. */

/*! @brief ELE Chunks container structure. */
typedef struct _ele_chunks_t
{
    uint32_t MasterChunk[MASTER_CHUNK_SIZE / sizeof(uint32_t)]; /*!< Master storage chunk. Always 100 Bytes */
    uint32_t *KeyStoreChunk; /*!< Key store chunk destination. If null HEAP is used. One per keystore, minimal lenght 64
                               Bytes, maximal 4160 Bytes */
    uint32_t *KeyGroupChunk; /*!< Key group chunk destination. If null HEAP is used. Up to 1024 per keystore, minimal
                               lenght 64 Bytes, maximal 4160 Bytes */
    size_t KeyStoreSize;     /*!< Key store chunk size, set by SW if HEAP for key store destination is used */
    size_t KeyGroupSize;     /*!< Key group chunk size, set by SW if HEAP for key group destination is used */
} ele_chunks_t;

/*!
 *@}
 */ /* end of ele_crypto_key_group_mng */

/*******************************************************************************
 * KEY GENERATE Definitions
 ******************************************************************************/
/*!
 * @addtogroup ele_crypto_key_gen
 * @{
 */

/*! @brief Key types */
/*! NOTE: For asymmetric keys, even if the key type is mentioned as KEY PAIR, only the private key is stored in the key
 * group. */
/*! Public key can be exported with this command or with Public key exportation command. */
typedef enum _key_type_t
{
    kKeyType_AES = 0x2400u, /*!< Cipher Encrypt/Decrypt, Authenticated encryption, MAC Generate/Verify (CMAC), Import
                               key (as KEK) */
    kKeyType_DERIVE                   = 0x1200u, /*!< TLS 1.2 compute key block, TLS finish data */
    kKeyType_HMAC                     = 0x1100u, /*!< MAC Generate/Verify */
    kKeyType_SM4                      = 0x2405u, /*!< Cipher Encrypt/Decrypt */
    kKeyType_ECC_PUB_KEY_BRAINPOOL_R1 = 0x4130u, /*!< Verify signature */
    kKeyType_ECC_PUB_KEY_SECP_NIST    = 0x4112u, /*!< Verify signature */
    kKeyType_RSA_PUB_KEY              = 0x4001u, /*!< Verify signature */
    kKeyType_ECC_KEY_PAIR_BRAINPOOL_R1 =
        0x7130u,                     /*!< Generate signature, Key exchange, TLS 1.2 key derivation and agreement */
    kKeyType_ECC_KEY_PAIR_SECP_R1_NIST =
        0x7112u,                     /*!< Generate signature, Key exchange, TLS 1.2 key derivation and agreement */
    kKeyType_RSA_KEY_PAIR = 0x7001u, /*!< Generate signature, Verify signature */
} key_type_t;

/*! @brief Key Lifetime */
typedef enum _key_lifetime_t
{
    kKey_Volatile            = 0x100,
    kKey_Persistent          = 0x101,
    kKey_VolatilePermanent   = 0x180,
    kKey_PersistentPermanent = 0x181,
} key_lifetime_t;

/*! @brief Key Usage. NOTE: As these values are bitmap values, several usage could be set. */
typedef enum _key_usage_t
{
    kKeyUsage_Export  = 0x0001u, /*!< Symmetric key or asymmetric private key can be exported. */
    kKeyUsage_Encrypt = 0x0100u, /*!< Permission to encrypt a message with the key. It could be cipher encryption, AEAD
                                    encryption or asymmetric encryption operation. */
    kKeyUsage_Decrypt = 0x0200u, /*!< Permission to decrypt a message with the key. It could be cipher decryption, AEAD
                                    decryption or asymmetric decryption operation. */
    kKeyUsage_SignMessage = 0x0400u, /*!< Permission to sign a message with the key. It could be a MAC generation or an
                                        asymmetric message signature operation. */
    kKeyUsage_VerifyMessage = 0x0800u, /*!< Permission to verify a message signature with the key. It could be a MAC
                                          verification or an asymmetric message signature verification operation. */
    kKeyUsage_SignHash =
        0x1000u, /*!< Permission to sign a hashed message with the key with an asymmetric signature operation.   */
    kKeyUsage_VerifyHash = 0x2000u, /*!< Permission to verify a hashed message signature with the key with an asymmetric
                                       signature verification operation.   */
    kKeyUsage_Derive = 0x4000u,     /*!< Permission to derive other keys from this key.  */
} key_usage_t;

/*! @brief Key Size */
typedef enum _key_size_t
{
    kKeySize_AES_128                       = 128u,
    kKeySize_AES_192                       = 192u,
    kKeySize_AES_256                       = 256u,
    kKeySize_DERIVE_256                    = 256u,
    kKeySize_DERIVE_384                    = 384u,
    kKeySize_HMAC_224                      = 224u,
    kKeySize_HMAC_256                      = 256u,
    kKeySize_HMAC_384                      = 384u,
    kKeySize_HMAC_512                      = 512u,
    kKeySize_SM4_128                       = 128u,
    kKeySize_ECC_KEY_PAIR_BRAINPOOL_R1_224 = 224u,
    kKeySize_ECC_KEY_PAIR_BRAINPOOL_R1_256 = 256u,
    kKeySize_ECC_KEY_PAIR_BRAINPOOL_R1_384 = 384u,
    kKeySize_ECC_KEY_PAIR_SECP_R1_NIST_224 = 224u,
    kKeySize_ECC_KEY_PAIR_SECP_R1_NIST_256 = 256u,
    kKeySize_ECC_KEY_PAIR_SECP_R1_NIST_384 = 384u,
    kKeySize_ECC_KEY_PAIR_SECP_R1_NIST_521 = 521u,
    kKeySize_RSA_KEY_PAIR_2048             = 2048u,
    kKeySize_RSA_KEY_PAIR_3072             = 3072u,
    kKeySize_RSA_KEY_PAIR_4096             = 4096u,
} key_size_t;

/*! @brief Key Permitted algorithm */
typedef enum _key_permitted_alg_t
{
    kPermitted_HMAC_SHA256 = 0x03800009u,
    kPermitted_HMAC_SHA384 =
        0x0380000Au, /*!< Permitted algorithms values computation allows to truncate the HMAC output length */
    /*!< or to set a minimum MAC output length. The following section describe how to encode truncated MAC algorithm.
         LEN (Bit 16 to 21):
         -	LEN = 0 specifies the default output MAC length. Its only compatible with W set to 0.
         -	LEN > 0x08 specifies a truncated output MAC length. It could be a specific or a minimum length according to W
       bit value. W (Bit 15): -	W = 0 indicates a specific output MAC length. In this case, the output MAC length set by
       the user must be equal to the value set by LEN bits. -	W = 1 indicates a minimum output MAC length. It must be at
       least 8 and cannot be greater that the default algorithm MAC length. In this case, the output MAC length set by
       the user must greater than or equal to the value set by LEN bits and less than or equal to the default algorithm
       MAC length (hash algorithm length). HASH_TYPE (Bit 0 to 7): -	HASH_TYPE = 0x09 indicates SHA256 algorithm. -
       HASH_TYPE = 0x0A indicates SHA384 algorithm. -	No other values are supported. */
    kPermitted_CMAC = 0x03C00200u, /*!< Default output CMAC length is 16 bytes */
    kPermitted_CTR  = 0x04C01000u,
    kPermitted_ECB  = 0x04404400u, /*!< No padding */
    kPermitted_CBC  = 0x04404000u, /*!< No padding */
    kPermitted_CFB  = 0x04C01100u,
    kPermitted_OFB  = 0x04C01200u,
    kPermitted_All_Cipher =
        0x84C0FF00u, /*!< Only available at key creation (CMAC, CTR, ECB no padding, CBC no padding) */
    kPermitted_CCM                         = 0x05500100u,
    kPermitted_GCM                         = 0x05500200u,
    kPermitted_All_AEAD                    = 0x8550FF00u, /*!< Only available at key creation (CCM, GCM) */
    kPermitted_KEK_CCM                     = 0x85500100u, /*!< Import */
    kPermitted_KEK_GCM                     = 0x85500200u, /*!< Import */
    kPermitted_RSA_PKCS1_V1_5_SHA1         = 0x06000205u,
    kPermitted_RSA_PKCS1_V1_5_SHA224       = 0x06000208u,
    kPermitted_RSA_PKCS1_V1_5_SHA256       = 0x06000209u,
    kPermitted_RSA_PKCS1_V1_5_SHA384       = 0x0600020Au,
    kPermitted_RSA_PKCS1_V1_5_SHA512       = 0x0600020Bu,
    kPermitted_RSA_PKCS1_V1_5_ANY_HASH     = 0x060002FFu, /*!< Only available at key creation */
    kPermitted_RSA_PKCS1_PSS_MGF1_SHA1     = 0x06000305u,
    kPermitted_RSA_PKCS1_PSS_MGF1_SHA224   = 0x06000308u,
    kPermitted_RSA_PKCS1_PSS_MGF1_SHA256   = 0x06000309u,
    kPermitted_RSA_PKCS1_PSS_MGF1_SHA384   = 0x0600030Au,
    kPermitted_RSA_PKCS1_PSS_MGF1_SHA512   = 0x0600030Bu,
    kPermitted_RSA_PKCS1_PSS_MGF1_ANY_HASH = 0x060003FFu, /*!< Only available at key creation */
    kPermitted_ECDSA_SHA224                = 0x06000608u,
    kPermitted_ECDSA_SHA256                = 0x06000609u,
    kPermitted_ECDSA_SHA384                = 0x0600060Au,
    kPermitted_ECDSA_SHA512                = 0x0600060Bu,
    kPermitted_ECDH_SHA_256                = 0x8902EF09u,
    kPermitted_TLS_1_2_PRF_ECDH_SHA256     = 0x09020209u,
    kPermitted_TLS_1_2_PRF_ECDH_SHA384     = 0x0902020Au,
} key_permitted_alg_t;

/*! @brief Key Lifecycle */
typedef enum _key_lifecycle_t
{
    kKeylifecycle_Open          = 0x1u,
    kKeylifecycle_Closed        = 0x2u,
    kKeylifecycle_Closed_Locked = 0x4u,
} key_lifecycle_t;

/*! @brief Key generation structure */
typedef struct _ele_gen_key_t
{
    uint16_t pub_key_size;  /*!< Size in bytes of the output where to store the generated public key. */
                            /*!< Ignored if a symmetric key is generated.*/
    uint16_t key_group;     /*!< Key Group It must be a value in the range 0-100 */
    uint32_t key_lifetime;  /*!< Key lifetime attribute. Refer to key_lifetime_t enum */
    uint32_t key_usage;     /*!< Key usage attribute. Refer to key_usage_t enum */
    uint16_t key_type;      /*!< Key type. Refer to key_type_t enum */
    uint16_t key_size;      /*!< Key size. Refer to key_size_t enum */
    uint32_t permitted_alg; /*!< Permitted algorithm attribute. Refer to key_permitted_alg_t enum */
    uint32_t pub_key_addr;  /*!< Address in the requester space where to store the public key */
    uint32_t key_lifecycle; /*!< Key lifecycle attribute. Refer to key_lifecycle_t */
    uint32_t key_id;        /*!< Key identifier. User specified ID only supported by persistent and permanent keys.
                               Set to 0 to let FW choose an ID - supported by all persistence levels.
                               For supported ID ranges, refer to the ELE API documentation. */
} ele_gen_key_t;

/*!
 *@}
 */ /* end of ele_crypto_key_gen */

/*******************************************************************************
 * IMPORT KEY Definitions
 ******************************************************************************/
/*!
 * @addtogroup ele_crypto_import_key
 * @{
 */

typedef enum
{
    kImportKeyOption_ELE   = 0u, /*!< The TLV payload is an ELE blob */
    kImportKeyOption_EL2GO = 1u, /*!< The TLV payload is an EdgeLock2Go blob */
} ele_import_key_option_t;

/*!
 *@}
 */ /* end of ele_crypto_import_key*/

/*******************************************************************************
 * MAC Definitions
 ******************************************************************************/
/*!
 * @addtogroup ele_crypto_mac
 * @{
 */

/* Verification status values returned by ELE_Mac() in kMAC_Verify mode */
#define MAC_VERIFY_SUCCESS (0x6c1aa1c6u) /*!< MAC Verification success */
#define MAC_VERIFY_FAIL    (0x0u)        /*!< MAC Verification failure */

/*! @brief MAC mode */
typedef enum _mac_mode_t
{
    kMAC_Verify   = 0x0u, /*!< MAC is generated in ELE local memory and compared with MAC at MAC adress */
    kMAC_Generate = 0x1u  /*!< MAC is generated and copied at the MAC adress */
} mac_mode_t;

/*! @brief Supported cryptographic functions for MAC creation (PSA values) */
typedef enum _hmac_algo_t
{
    kELE_Hmac256 = 0x03800009, /*!< SHA_256  */
    kELE_Hmac384 = 0x0380000A, /*!< SHA_384  */
    kELE_Cmac    = 0x03C00200, /*!< CMAC     */
} mac_algo_t;

/*! @brief ELE MAC structure. */
typedef struct _ele_mac
{
    uint32_t mac_handle_id;  /*!< Unique Cipher handle ID obtained by calling ELE_OpenMacService() */
    uint32_t key_id;         /*!< Key ID obtained by calling ELE_GenerateKey() */
    uint32_t payload;        /*!< Pointer where payload data can be found */
    uint32_t payload_size;   /*!< Size of payload data in bytes */
    uint32_t mac;            /*!< Pointer to MAC data */
    uint16_t mac_size;       /*!< Size of MAC data in bytes */
    key_permitted_alg_t alg; /*!< Algorithm identifier Refer to key_permitted_alg_t enum */
    mac_mode_t mode;         /*!< Mode identifier Refer to mac_mode_t */
} ele_mac_t;

/**
 * FastMAC-specific definitions for the 'Fast MAC Proceed' command
 * flags to be OR'd together as per the user's needs. See FastMAC documentation
 * for specifics.
 */

/*!< Preload msg buffer 0. */
#define FAST_MAC_PRELOAD_BUFF_0 (0x00000001u)
/*!< Preload msg buffer 1. */
#define FAST_MAC_PRELOAD_BUFF_1 (0x00000002u)
/*!< Preload msg buffer 2. */
#define FAST_MAC_PRELOAD_BUFF_2 (0x00000004u)
/*!< Preload msg buffer 3. */
#define FAST_MAC_PRELOAD_BUFF_3 (0x00000008u)

/*!< HMAC proceed over msg buffer 0. */
#define FAST_MAC_PROCEED_BUFF_0 (0x00000010u)
/*!< HMAC proceed over msg buffer 1. */
#define FAST_MAC_PROCEED_BUFF_1 (0x00000020u)
/*!< HMAC proceed over msg buffer 2. */
#define FAST_MAC_PROCEED_BUFF_2 (0x00000040u)
/*!< HMAC proceed over msg buffer 3. */
#define FAST_MAC_PROCEED_BUFF_3 (0x00000080u)
/*!< HMAC proceed all four buffers. */
#define FAST_MAC_PROCEED_ALL_BUFF \
    (FAST_MAC_PROCEED_BUFF_0 | FAST_MAC_PROCEED_BUFF_1 | FAST_MAC_PROCEED_BUFF_2 | FAST_MAC_PROCEED_BUFF_3)

/*!< Verify internally. When this flag is set while also utilizing preloading, ELE assumes that Message address field
is a concatenation of message and expected HMAC. Message = (message || expected_HMAC). At the end of the HMAC
computation, ELE will compare expteced_HMAC with the calculated HMAC and report the status. In this scenario, message
size API input must be size of message + size of expected HMAC in bytes. */
#define FAST_MAC_VERIFY_INTERNALLY (0x00000100u)

/*!< One shot mode. One shot: Do not use preload mechanism. When this flag is set, Message field is the message,
and MAC field is the output buffer or expected HMAC buffer depending on verify internally flag */
#define FAST_MAC_ONE_SHOT (0x00000200u)

/*!< Use key 0 for the specified message. */
#define FAST_MAC_USE_KEY_0 (0x00000000u)
/*!< Use key 1 for the specified message. */
#define FAST_MAC_USE_KEY_1 (0x00000400u)

/*!< HMAC trunctation to 8 Bytes. */
#define FAST_MAC_TRUNCATE_08B (0x00000800u)
/*!< HMAC trunctation to 16 Bytes. */
#define FAST_MAC_TRUNCATE_16B (0x00001000u)
/*!< HMAC trunctation to 24 Bytes. */
#define FAST_MAC_TRUNCATE_24B (0x00001800u)
/*!< HMAC trunctation to 32 Bytes (no truncation done). */
#define FAST_MAC_TRUNCATE_32B (0x00003800u)

/*!< Check buffer 0 internal verification status returned by ELE_FastMacProceed(). Returns 1 if verification success. */
#define FAST_MAC_CHECK_VERIFICATION_SUCCESS_BUF_0(x) ((uint32_t)x & 0x01)
/*!< Check buffer 1 internal verification status returned by ELE_FastMacProceed(). Returns 1 if verification success. */
#define FAST_MAC_CHECK_VERIFICATION_SUCCESS_BUF_1(x) (((uint32_t)x & 0x02) >> 1)
/*!< Check buffer 2 internal verification status returned by ELE_FastMacProceed(). Returns 1 if verification success. */
#define FAST_MAC_CHECK_VERIFICATION_SUCCESS_BUF_2(x) (((uint32_t)x & 0x04) >> 2)
/*!< Check buffer 3 internal verification status returned by ELE_FastMacProceed(). Returns 1 if verification success. */
#define FAST_MAC_CHECK_VERIFICATION_SUCCESS_BUF_3(x) (((uint32_t)x & 0x08) >> 3)
/*!< Check oneshot internal verification status returned by ELE_FastMacProceed(). Returns 1 if verification success. */
#define FAST_MAC_CHECK_VERIFICATION_SUCCESS_ONESHOT(x) (((uint32_t)x & 0x80) >> 7)

/*!< Check buffer 0 internal verification status returned by ELE_FastMacProceed(). Returns 1 if verification failure. */
#define FAST_MAC_CHECK_VERIFICATION_FAILURE_BUF_0(x) ((uint32_t)x & 0x0100 >> 8)
/*!< Check buffer 1 internal verification status returned by ELE_FastMacProceed(). Returns 1 if verification failure. */
#define FAST_MAC_CHECK_VERIFICATION_FAILURE_BUF_1(x) (((uint32_t)x & 0x0200) >> 9)
/*!< Check buffer 2 internal verification status returned by ELE_FastMacProceed(). Returns 1 if verification failure. */
#define FAST_MAC_CHECK_VERIFICATION_FAILURE_BUF_2(x) (((uint32_t)x & 0x0400) >> 10)
/*!< Check buffer 3 internal verification status returned by ELE_FastMacProceed(). Returns 1 if verification failure. */
#define FAST_MAC_CHECK_VERIFICATION_FAILURE_BUF_3(x) (((uint32_t)x & 0x0800) >> 11)
/*!< Check oneshot internal verification status returned by ELE_FastMacProceed(). Returns 1 if verification failure. */
#define FAST_MAC_CHECK_VERIFICATION_FAILURE_ONESHOT(x) (((uint32_t)x & 0x8000) >> 15)

/*!
 *@}
 */ /* end of ele_crypto_mac */

/*******************************************************************************
 * SIGN and VERIFY Definitions
 ******************************************************************************/
/*!
 * @addtogroup ele_crypto_sign_verify
 * @{
 */

/*! @brief Signature scheme  */
typedef enum _key_sig_scheme_t
{
    kSig_RSA_PKCS1_V1_5_SHA1       = 0x06000205u,
    kSig_RSA_PKCS1_V1_5_SHA224     = 0x06000208u,
    kSig_RSA_PKCS1_V1_5_SHA256     = 0x06000209u,
    kSig_RSA_PKCS1_V1_5_SHA384     = 0x0600020Au,
    kSig_RSA_PKCS1_V1_5_SHA512     = 0x0600020Bu,
    kSig_RSA_PKCS1_PSS_MGF1_SHA1   = 0x06000305u,
    kSig_RSA_PKCS1_PSS_MGF1_SHA224 = 0x06000308u,
    kSig_RSA_PKCS1_PSS_MGF1_SHA256 = 0x06000309u,
    kSig_RSA_PKCS1_PSS_MGF1_SHA384 = 0x0600030Au,
    kSig_RSA_PKCS1_PSS_MGF1_SHA512 = 0x0600030Bu,
    kSig_ECDSA_SHA224              = 0x06000608u,
    kSig_ECDSA_SHA256              = 0x06000609u,
    kSig_ECDSA_SHA384              = 0x0600060Au,
    kSig_ECDSA_SHA512              = 0x0600060Bu,
} key_sig_scheme_t;

/*! @brief Sign generation structure */
typedef struct _ele_sign
{
    uint32_t key_id;         /*!< Key ID to be used for signing */
    uint8_t const *msg;      /*!< Address where the data to be signed can be found */
    uint32_t msg_size;       /*!< Size of message */
    uint8_t *signature;      /*!< Address where the signature will be written */
    uint16_t sig_size;       /*!< Size of signature */
    key_sig_scheme_t scheme; /*!< Used signature scheme */
    bool input_flag;         /*!< When set input is the actual message, message digest if not */
    uint16_t salt_size;      /*!< The salt size in bytes */
} ele_sign_t;

/*! @brief Verify generation structure */
typedef struct _ele_verify
{
    uint8_t const *pub_key;     /*!< Public Key to be used for verification */
    uint16_t key_size;          /*!< Size of public key */
    uint8_t const *msg;         /*!< Address where the data to be signed can be found */
    uint32_t msg_size;          /*!< Size of message */
    uint8_t *signature;         /*!< Address where the signature will be written */
    uint16_t sig_size;          /*!< Size of signature */
    key_type_t keypair_type;    /*!< Used kay pair type */
    key_sig_scheme_t scheme;    /*!< Used signature scheme */
    uint16_t key_security_size; /*!< Key security size in bits */
    bool input_flag;            /*!< When set input is the actual message, if not message digest */
    bool internal;              /*!< When set key is an internal reference (See import Public key) */
    uint16_t salt_size;         /*!< The salt size in bytes */
} ele_verify_t;

/*!
 *@}
 */ /* end of ele_crypto_sign_verify */

/*******************************************************************************
 * Data Storage Definitions
 ******************************************************************************/
/*!
 * @addtogroup ele_crypto_data_storage
 * @{
 */

/*! @brief Data storage operation */
typedef enum _data_storage_operation_t
{
    kDataRetrieve = 0x00UL, /*!< Retrieve data */
    kDataStore    = 0x01UL, /*!< Store data */
} data_storage_operation_t;

/*! @brief Data storage option */
typedef enum _data_storage_option_t
{
    kStandardOption = 0x00UL, /*!< Standard option */
    kEL2GOOption    = 0x01UL, /*!< EdgeLock2Go option (see documentation for data format) */
} data_storage_option_t;

/*! @brief Data storage structure */
typedef struct _ele_data_storage
{
    uint16_t dataID;              /*!< Identifier of the data block (user defined) */
    uint32_t *data;               /*!< Address in system memory where data to be store/retrieve can be found */
    size_t data_size;             /*!< Data size in bytes */
    uint32_t *chunk_addr;         /*!< Output address where encrypted chunk is stored (dynamically allocated) */
    size_t chunk_size;            /*!< Output chunk size (additional 36(CHUNK_META_SIZE) Bytes to payload data) */
    data_storage_option_t option; /*!< Selects the Standard or EL2GO option (only needed for Store operation) */
} ele_data_storage_t;

/* Size of additional meta data in chunk */
#define CHUNK_META_SIZE (36u)

/*!
 *@}
 */ /* end of ele_crypto_data_storage */

/*******************************************************************************
 * Generic crypto
 ******************************************************************************/
/*!
 * @addtogroup ele_crypto_generic
 * @{
 */

/*! @brief RNG reseed flags */
typedef enum _rng_reseed_flag_t
{
    kNoReseed          = 0x0u, /*!< Do not reseed RNG */
    kReseedNonBlocking = 0x1u, /*!< If ELE is not ready to reseed, return failure */
    kReseedBlocking    = 0x2u, /*!< If ELE is not ready to reseed, wait until ready */
} rng_reseed_flag_t;

/*! @brief AES generic cipher algo  */
typedef enum _generic_cipher_algo_t
{
    kAES_ECB = 0x02u,
    kAES_CBC = 0x03u,
    kAES_CTR = 0x04u,
    kAES_OFB = 0x43u,
    kAES_CFB = 0x44u
} generic_cipher_algo_t;

/*! @brief AES generic AEAD algo  */
typedef enum _generic_aead_algo_t
{
    kAES_GCM = 0x05u,
    kAES_CCM = 0x06u
} generic_aead_algo_t;

/*! @brief ECDSA generic algo  */
typedef enum _generic_ecdsa_algo_t
{
    kECDSA_P224_SHA224 = 0x06000608,
    kECDSA_P256_SHA256 = 0x06000609,
    kECDSA_P384_SHA384 = 0x0600060A,
    kECDSA_P521_SHA512 = 0x0600060B,
} generic_ecdsa_algo_t;

/*! @brief RSA generic algo  */
typedef enum _generic_rsa_algo_t
{
    RSA_PKCS1_V1_5_SHA224_SIGN = 0x06000208u, /* Sign */
    RSA_PKCS1_V1_5_SHA256_SIGN = 0x06000209u,
    RSA_PKCS1_V1_5_SHA384_SIGN = 0x0600020Au,
    RSA_PKCS1_V1_5_SHA512_SIGN = 0x0600020Bu,
    RSA_PKCS1_PSS_MGF1_SHA224  = 0x06000308u,
    RSA_PKCS1_PSS_MGF1_SHA256  = 0x06000309u,
    RSA_PKCS1_PSS_MGF1_SHA384  = 0x0600030Au,
    RSA_PKCS1_PSS_MGF1_SHA512  = 0x0600030Bu,
    RSA_PKCS1_V1_5_CRYPT       = 0x07000200u, /* Encryption */
    RSA_PKCS1_OAEP_SHA1        = 0x07000305u,
    RSA_PKCS1_OAEP_SHA224      = 0x07000308u,
    RSA_PKCS1_OAEP_SHA256      = 0x07000309u,
    RSA_PKCS1_OAEP_SHA384      = 0x0700030Au,
    RSA_PKCS1_OAEP_SHA512      = 0x0700030Bu
} generic_rsa_algo_t;

/*! @brief Generic mode */
typedef enum _generic_cipher_mode_t
{
    kEncrypt = 0x41u,
    kDecrypt = 0x42u,
    kSign    = 0x43u,
    kVerify  = 0x44u
} generic_mode_t;

/*! @brief Generic mode */

typedef enum _generic_rsa_mode_t
{
    kEncryption   = 0x0001,
    kDecryption   = 0x0002,
    kSignGen      = 0x0003,
    kVerification = 0x0004
} generic_rsa_mode_t;

/*! @brief Generic flags */
typedef enum _generic_rsa_flags_t
{
    kFlagDigest    = 0x00u, /*!< Input is digest */
    kFlagActualMsg = 0x01u  /*!< Input is message, ELE will hash internally */
} generic_rsa_flags_t;

/*! @brief Generic verify status */
typedef enum _generic_verify_status_t
{
    kSignatureVeritificationNotTriggered = 0x0u,
    kVerifySuccess                       = 0x5a3cc3a5u,
    kVerifyFailure                       = 0x2b4dd4b2u
} generic_verify_status_t;

/*! @brief Generic cipher structure */
typedef struct _ele_generic_cipher_t
{
    uint32_t data;              /*!< Source data address */
    uint32_t output;            /*!< Destination data address */
    uint32_t size;              /*!< Data byte length */
    uint32_t key;               /*!< Cipher key address */
    uint32_t key_size;          /*!< Cipher key byte length */
    uint32_t iv;                /*!< Initialization vector address */
    uint32_t iv_size;           /*!< Initialization vector  byte length*/
    generic_cipher_algo_t algo; /*!< Algorithm identifier */
    generic_mode_t mode;        /*!< Mode identifier */
} ele_generic_cipher_t;

/*! @brief Generic AEAD structure */
typedef struct _ele_generic_aead_t
{
    uint32_t data;            /*!< Source data address */
    uint32_t output;          /*!< Destination data address */
    uint32_t size;            /*!< Data byte length */
    uint32_t key;             /*!< Cipher key address */
    uint32_t key_size;        /*!< Cipher key byte length */
    uint32_t iv;              /*!< Initialization vector address */
    uint32_t iv_size;         /*!< Initialization vector byte length */
    uint32_t aad;             /*!< Additional authentication data address */
    uint32_t aad_size;        /*!< Additional authentication data address byte length*/
    uint32_t tag;             /*!< Tag vector address */
    uint32_t tag_size;        /*!< Tag vector byte length */
    generic_aead_algo_t algo; /*!< Algorithm identifier */
    generic_mode_t mode;      /*!< Mode identifier */
} ele_generic_aead_t;

/*! @brief Generic ECDSA structure */
typedef struct _ele_generic_ecdsa_t
{
    uint32_t digest;                       /*!< Digest address */
    uint32_t digest_size;                  /*!< Digest byte length */
    uint32_t key;                          /*!< Key address */
    uint32_t key_size;                     /*!< Key byte length */
    uint32_t signature;                    /*!< Signature address */
    uint32_t signature_size;               /*!< Signature byte length */
    generic_ecdsa_algo_t algo;             /*!< Algorithm identifier */
    generic_mode_t mode;                   /*!< Mode identifier */
    generic_verify_status_t verify_status; /*!< Verify status */
} ele_generic_ecdsa_t;

/*! @brief Generic RSA keygen structure */
typedef struct _ele_generic_rsa_t
{
    uint32_t modulus;            /*!< Modulus address */
    uint32_t priv_exponent;      /*!< Private exponent address */
    uint32_t priv_exponent_size; /*!< Private exponent size */
    uint32_t modulus_size;       /*!< Modulus size */
    uint32_t pub_exponent;       /*!< Public exponent address */
    uint32_t pub_exponent_size;  /*!< Public exponent size */
    uint32_t key_size;           /*!< Key size */
    generic_rsa_algo_t algo;
    generic_rsa_mode_t mode;
    uint32_t digest;
    uint32_t signature;
    uint32_t plaintext;
    uint32_t ciphertext;
    uint16_t digest_size;
    uint16_t signature_size;
    uint16_t plaintext_size;
    uint16_t ciphertext_size;
    uint32_t label;
    uint16_t label_size;
    int16_t salt_size;          /*!< Salt length for RSA PSS */
    generic_verify_status_t verify_status;
    uint32_t out_plaintext_len; /*!< Contain the decrypted plaintext valid length in bytes */
    generic_rsa_flags_t flags;  /*!< Flags for the requested operation */
} ele_generic_rsa_t;

#define ELE_HASH_CTX_SIZE 216u /* Maximum HASH ctx size is 216 Bytes (112 Bytes for SHA2-224/256) */
/*! @brief ELE HASH Context structure */
typedef struct _ele_hash_ctx_t
{
    uint8_t x[ELE_HASH_CTX_SIZE]; /*!< storage */
} ele_hash_ctx_t;

/*!
 *@}
 */ /* end of ele_crypto_generic */

/*******************************************************************************
 * Cipher
 ******************************************************************************/
/*!
 * @addtogroup ele_crypto
 * @{
 */

/*! @brief AES mode */
typedef enum _cipher_mode_t
{
    kHSM_Decrypt = 0x0u,
    kHSM_Encrypt = 0x1u
} cipher_mode_t;

/*! @brief AES IV generation flags */
typedef enum _cipher_iv_generation_t
{
    kHSM_IV_User                   = 0x0u, /*!< IV supplied by user */
    kHSM_Generate_Full_IV          = 0x2u, /*!< Full IV data generated internally - relevant for GCM only */
    kHSM_Use_Counter_IV_generation = 0x4u /*!< User must supply 4 bytes of IV data, rest is generated internally using a
                                             counter - relevant for GCM only */
} iv_generation_t;

/*! @brief HSM Cipher structure */
typedef struct _ele_hsm_cipher_t
{
    uint32_t keyID;      /*!< keyID Key ID obtained by calling ELE_GenerateKey() */
    uint32_t input;      /*!< input pointer where input data can be found */
    size_t input_size;   /*!< input_size size of input data in bytes */
    uint32_t output;     /*!< output pointer where output data must be stored */
    size_t *output_size; /*!< output_size size of output data in bytes, not used if NULL */
    uint32_t iv;         /*!< iv pointer where IV data can be found if applicable, otherwise 0 */
    size_t iv_size; /*!< iv_size size of iv data in bytes, CBC IV is fixed to 16 bytes, CTR IV size is fixed to 8 bytes,
                       must be 0 for algorithm not using IV */
                    /*!< For GCM 0, 4 or 12 bytes depending on iv_gen_flags parameter. For CCM 12 */
    key_permitted_alg_t alg; /*!< alg Algorithm identifier Refer to key_permitted_alg_t enum */
    cipher_mode_t mode;      /*!< mode Mode identifier - encryption or decryption Refer to mode_t enum  */
} ele_hsm_cipher_t;

/*!
 *@}
 */ /* end of ele_crypto_generic */
/*******************************************************************************
 * Baseline API
 ******************************************************************************/
/*!
 * @addtogroup ele_crypto_baseline
 * @{
 */

/*! @brief Signed message type  */
typedef enum _signed_msg_type_t
{
    kKeyStoreReprovisioningEnable                = 0x01u,
    kRootKeyEncryptionKeyExportEnable            = 0x02u,
    kKeyExchangeKeyEncryptionKeyGenerationEnable = 0x03u,
    kWrite_Secure_Fuse                           = 0x91u,
    kReturn_Lifecycle_Update                     = 0xA0u
} signed_msg_type_t;

/*! @brief Structure for device attestation nonce */
typedef struct _attestation_nonce_t
{
    uint32_t nonce_word_1;
    uint32_t nonce_word_2;
    uint32_t nonce_word_3;
    uint32_t nonce_word_4;
} attestation_nonce_t;

/*! @brief Flag selecting the generated blob type */
typedef enum _ele_key_blob_type_t
{
    kBlob_Type_DEK   = 1u, /*!< DEK blob type */
    kBlob_Type_OTFAD = 2u, /*!< OTFAD blob type */
    kBlob_Type_IEE   = 3u, /*!< IEE blob type */
} ele_key_blob_type_t;

/*! @brief Valid sizes for the payload size depending on configuration */
typedef enum _ele_key_blob_payload_size_t
{
    kBlob_Size_128   = 0x10u, /*!< Valid size for DEK AES CBC / DEK SM4 CBC / IEE AES CTR */
    kBlob_Size_192   = 0x18u, /*!< Valid size for DEK AES CBC */
    kBlob_Size_256   = 0x20u, /*!< Valid size for DEK AES CBC / IEE AES XTS / IEE AES CTR */
    kBlob_Size_512   = 0x40u, /*!< Valid size for IEE AES XTS */
    kBlob_Size_OTFAD = 0x28u, /*!< Valid size for OTFAD */
} ele_key_blob_payload_size_t;

/*! @brief Valid algorithms for the key blob generation payload header */
typedef enum _ele_key_blob_algorithm_t
{
    kBlob_Algo_AES_CBC = 0x03u,
    kBlob_Algo_AES_CTR = 0x04u,
    kBlob_Algo_SM4_CBC = 0x2bu, /*!< Available only with OSCCA enabled */
    kBlob_Algo_AES_XTS = 0x37u,
} ele_key_blob_algorithm_t;

/*! @brief IEE AES key size for key blob generation */
typedef enum _ele_key_blob_iee_key_size_t
{
    kBlob_IEE_AES_CTR128XTS256 = 0u, /*!< AES 128 bits (CTR), 256 bits (XTS) */
    kBlob_IEE_AES_CTR256XTS512 = 1u  /*!< AES 256 bits (CTR), 512 bits (XTS) */
} ele_key_blob_iee_key_size_t;

/*! @brief IEE AES enablement/bypass for key blob generation */
typedef enum _ele_key_blob_iee_bypass_t
{
    kBlob_IEE_UseModeField = 0u, /*!< AES encryption/decryption enabled using specified mode */
    kBlob_IEE_Bypass       = 1u  /*!< AES encryption/decryption bypass */
} ele_key_blob_iee_bypass_t;

/*! @brief IEE AES mode for key blob generation */
typedef enum _ele_key_blob_iee_mode_t
{
    kBlob_IEE_Mode_None             = 0u, /*!< AES NONE mode */
    kBlob_IEE_Mode_AES_XTS          = 1u, /*!< AES XTS mode */
    kBlob_IEE_Mode_AES_CTRWAddress  = 2u, /*!< AES CTR w address binding mode */
    kBlob_IEE_Mode_AES_CTRWOAddress = 3u, /*!< AES CTR w/o address binding mode */
    kBlob_IEE_Mode_AES_CTRkeystream = 4u  /*!< AES CTR keystream only mode */
} ele_key_blob_iee_mode_t;

/*! @brief IEE lock region key, attribute, and offset configurations */
typedef enum _ele_key_blob_iee_lock_t
{
    kBlob_IEE_NoLock = 0u, /*!< Do not lock the registers */
    kBlob_IEE_Lock   = 1u  /*!< Lock the registers */
} ele_key_blob_iee_lock_t;

/*! @brief Specify if an IEE key should be automatically randomly generated */
typedef enum _ele_key_blob_iee_rand_keygen_t
{
    kBlob_IEE_UseInputKeys       = 0u, /*!< Use keys specified in the key fields */
    kBlob_IEE_GenerateRandomKeys = 1u  /*!< Generate random keys in blob; key field must be padded with 0�s */
} ele_key_blob_iee_rand_gen_t;

/*! @brief OTFAD-specific settings for key blob generation */
typedef struct _ele_key_blob_otfad_settings_t
{
    uint32_t start_addr;
    uint32_t end_addr;
    uint8_t valid;             /*!< Set to 1 if fetched context is valid */
    uint8_t enable_decryption; /*!< Set to 1 to decrypt fetched data */
    uint8_t read_only;         /*!< Set to 1 if context registers are read-only */
} ele_key_blob_otfad_settings_t;

/*! @brief IEE-specific settings for key blob generation */
typedef struct _ele_key_blob_iee_settings_t
{
    uint8_t region_number;
    ele_key_blob_iee_lock_t lock;
    ele_key_blob_iee_rand_gen_t rand_keys;
    ele_key_blob_iee_bypass_t bypass;
    ele_key_blob_iee_key_size_t key_size;
    ele_key_blob_iee_mode_t mode;
    uint32_t page_offset;
} ele_key_blob_iee_settings_t;

/*! @brief Keyblob generation config */
typedef struct _generate_key_blob_input_t
{
    // General command settings
    ele_key_blob_type_t blob_type;
    ele_key_blob_algorithm_t algorithm;
    ele_key_blob_payload_size_t size;

    // Common blob settings
    uint8_t *key; /*!< Pointer to the key for DEK, OTFAD, or IEE based on general settings */
    uint8_t *ctr; /*!< Pointer to counter for OTFAD and IEE based on general settings */

    // OTFAD settings
    ele_key_blob_otfad_settings_t otfad;

    // IEE settings
    ele_key_blob_iee_settings_t iee;
} generate_key_blob_input_t;

/*!
 *@}
 */ /* end of ele_crypto_baseline */

/*******************************************************************************
 * Random Number Generator
 ******************************************************************************/
/*!
 * @addtogroup ele_rng
 * @{
 */

/*! @brief ELE TRNG State */
typedef enum _ele_trng_state_t
{
    kELE_TRNG_program  = 0x1u, /*!< TRNG is in program mode */
    kELE_TRNG_generate = 0x2u, /*!< TRNG is still generating entropy */
    kELE_TRNG_ready    = 0x3u, /*!< TRNG entropy is valid and ready to be read */
    kELE_TRNG_error    = 0x4u, /*!< TRNG encounter an error while generating entropy. */
} ele_trng_state_t;

/*! @brief ELE TRNG CSAL (Cryptolib) context state */
typedef enum _ele_trng_csal_state_t
{
    kELE_TRNG_CSAL_not_ready = 0x0u, /*!< Crypto Lib random context initialization is not done yet */
    kELE_TRNG_CSAL_busy      = 0x1u, /*!< Crypto Lib random context initialization is on-going */
    kELE_TRNG_CSAL_success   = 0x2u, /*!< Crypto Lib random context initialization succeed */
    kELE_TRNG_CSAL_fail      = 0x3u, /*!< Crypto Lib random context initialization failed */
    kELE_TRNG_CSAL_pause     = 0x4u, /*!< Crypto Lib random context initialization is in pause mode */
} ele_trng_csal_state_t;

/*!
 *@}
 */ /* end of ele_rng */

/*******************************************************************************
 * BBSM (Battery-Backed Security Module)
 ******************************************************************************/
/*!
 * @addtogroup ele_bbsm
 * @{
 */

/*! @brief ELE BBSM Alert level policy */
typedef enum _ele_bbsm_policy_t
{
    kELE_BBSM_Alert1_BBSM_log_event   = 0x1u,        /*!< ELE will log an event */
    kELE_BBSM_Alert1_BBSM_abort       = 0x2u,        /*!< ELE will abort */
    kELE_BBSM_Alert1_BBSM_irq         = 0x4u,        /*!< ELE will trigger an interrupt to user core */
    kELE_BBSM_Alert1_BBSM_disable_sab = 0x8u,        /*!< ELE will disable crypto sensitive services (SAB) */

    kELE_BBSM_Alert2_BBSM_log_event   = 0x1u << 4u,  /*!< ELE will log an event */
    kELE_BBSM_Alert2_BBSM_abort       = 0x2u << 4u,  /*!< ELE will abort */
    kELE_BBSM_Alert2_BBSM_irq         = 0x4u << 4u,  /*!< ELE will trigger an interrupt to user core */
    kELE_BBSM_Alert2_BBSM_disable_sab = 0x8u << 4u,  /*!< ELE will disable crypto sensitive services (SAB) */

    kELE_BBSM_Alert3_BBSM_log_event   = 0x1u << 8u,  /*!< ELE will log an event */
    kELE_BBSM_Alert3_BBSM_abort       = 0x2u << 8u,  /*!< ELE will abort */
    kELE_BBSM_Alert3_BBSM_irq         = 0x4u << 8u,  /*!< ELE will trigger an interrupt to user core */
    kELE_BBSM_Alert3_BBSM_disable_sab = 0x8u << 8u,  /*!< ELE will disable crypto sensitive services (SAB) */

    kELE_BBSM_Alert4_BBSM_log_event   = 0x1u << 12u, /*!< ELE will log an event */
    kELE_BBSM_Alert4_BBSM_abort       = 0x2u << 12u, /*!< ELE will abort */
    kELE_BBSM_Alert4_BBSM_irq         = 0x4u << 12u, /*!< ELE will trigger an interrupt to user core */
    kELE_BBSM_Alert4_BBSM_disable_sab = 0x8u << 12u, /*!< ELE will disable crypto sensitive services (SAB) */
} ele_bbsm_policy_t;

/*!
 *@}
 */ /* end of ele_bbsm */
/*******************************************************************************
 * Get Event
 ******************************************************************************/
/*!
 * @addtogroup ele_event
 * @{
 */

#define ELE_MAX_EVENTS 8u /* Maximum capacity of the event buffer  */
typedef struct _ele_events_t
{
    uint32_t event[ELE_MAX_EVENTS]; /*!< Events buffer */
} ele_events_t;

/*!
 *@}
 */ /* end of ele_event */
/*******************************************************************************
 * API
 *******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Load ELE FW
 *
 * This function Loads firmware into EdgeLock Enclave.
 *
 * @param mu MU peripheral base address
 * @param fw pointer in system memory where FW can be found
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_LoadFw(S3MU_Type *mu, const uint8_t *fw);

/*!
 * @brief Initialize ELE services
 *
 * This function initializes the EdgeLock Enclave services and needs to be
 * called at least once before using these services (e.g. ELE_OpenSession()).
 *
 * @param mu MU peripheral base address
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_InitServices(S3MU_Type *mu);

/*!
 * @brief Open ELE Session
 *
 * This function opens Session for EdgeLock Enclave.
 *
 * @param mu MU peripheral base address
 * @param sessionID pointer where store unique session ID word
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_OpenSession(S3MU_Type *mu, uint32_t *sessionID);

/*!
 * @brief Close ELE Session
 *
 * This function closes the Session for EdgeLock Enclave.
 *
 * @param mu MU peripheral base address
 * @param sessionID unique session ID obtained by calling ELE_OpenSession()
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_CloseSession(S3MU_Type *mu, uint32_t sessionID);

/*!
 * @brief ELE HASH
 *
 * This function computes HASH (ONE GO) of a given message using EdgeLock Enclave.
 *
 * @param mu MU peripheral base address
 * @param msg pointer where data to be hashed can be found, may be zero
 * @param size size of data in byte, may be zero
 * @param out pointer to output HASH data (size is defined by used algorithm),
 *            user must ensure this memory is available to ELE
 * @param out_size the size of the output buffer, which must be equal or larger
 *        than the resulting HASH
 * @param out_length pointer where to output the resulting length of the generated HASH,
 *        or the expected out_size of the output buffer if it is found to be too small
 * @param alg define used hash algorithm, see hash_algo_t
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail,
 *         kStatus_InvalidArgument if invalid argument
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange,
 *                  kStatus_ELE_BufferTooSmall
 */
status_t ELE_Hash(S3MU_Type *mu,
                  const uint8_t *msg,
                  size_t size,
                  uint8_t *out,
                  uint32_t out_size,
                  uint32_t *out_length,
                  hash_algo_t alg);

/*!
 * @brief ELE HASH
 *
 * This function initialize ELE context for streaming HASH oprations.
 *
 * @param mu MU peripheral base address
 * @param ctx Pointer to context of ELE HASH streaming operations used by ELE.
 * @param alg define used hash algorithm, see hash_algo_t
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_Hash_Init(S3MU_Type *mu, ele_hash_ctx_t *ctx, hash_algo_t alg);

/*!
 * @brief ELE HASH
 *
 * This function update ELE digest in context with new data.
 *
 * @param mu MU peripheral base address
 * @param ctx Pointer to context of ELE HASH streaming operations used by ELE.
 * @param alg define used hash algorithm, see hash_algo_t
 * @param msg pointer where data to be hashed can be found, may be zero
 * @param size size of data in byte, may be zero
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_Hash_Update(S3MU_Type *mu, ele_hash_ctx_t *ctx, hash_algo_t alg, const uint8_t *msg, size_t size);

/*!
 * @brief ELE HASH
 *
 * This function update last data block (if needed) and provide final HASH digest in out buffer.
 *
 * @param mu MU peripheral base address
 * @param ctx Pointer to context of ELE HASH streaming operations used by ELE.
 * @param alg define used hash algorithm, see hash_algo_t
 * @param out pointer to output HASH data (size is defined by used algorithm),
 *            user must ensure this memory is available to ELE
 * @param out_size the size of the output buffer, which must be equal or larger
 *        than the resulting HASH
 * @param out_length pointer where to output the resulting length of the generated HASH,
 *        or the expected out_size of the output buffer if it found to be too small
 * @param msg pointer where data to be hashed can be found, may be zero
 * @param size size of data in byte, may be zero
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail,
 *         kStatus_InvalidArgument if invalid argument
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange,
 *                  kStatus_ELE_BufferTooSmall
 */
status_t ELE_Hash_Finish(S3MU_Type *mu,
                         ele_hash_ctx_t *ctx,
                         hash_algo_t alg,
                         uint8_t *out,
                         uint32_t out_size,
                         uint32_t *out_length,
                         const uint8_t *msg,
                         size_t size);

/*!
 * @brief ELE HMAC Generic
 *
 * This function computes HMAC (One Go) of a given message using EdgeLock Enclave.
 *
 * @param mu MU peripheral base address
 * @param msg pointer where input message data can be found, may be zero
 * @param size size of input data in bytes, may be zero
 * @param out pointer where the MAC buffer must be written by ELE (size depends on used alg)
 * @param out_size pointer to the resulting output size of the chosen HMAC
 * @param key pointer where the buffer with key in plaintext can be found
 * @param key_size size of key in bytes
 * @param alg define algorithm used for HMAC, see mac_algo_t
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail,
 *         kStatus_InvalidArgument if invalid argument
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_GenericHmac(S3MU_Type *mu,
                         const uint8_t *msg,
                         uint16_t size,
                         uint8_t *out,
                         uint32_t *out_size,
                         const uint8_t *key,
                         uint16_t key_size,
                         mac_algo_t alg);

/*!
 * @brief Open ELE Cipher Service
 *
 * This function opens Cipher Service for EdgeLock Enclave.
 *
 * @param mu MU peripheral base address
 * @param keystoreHandleID unique session ID obtained by calling ELE_CreateKeystore()
 * @param cipherHandleID pointer to unique Cipher session handle ID word
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_OpenCipherService(S3MU_Type *mu, uint32_t keystoreHandleID, uint32_t *cipherHandleID);

/*!
 * @brief Close ELE Cipher Service
 *
 * This function closes the Cipher Service for EdgeLock Enclave.
 *
 * @param mu MU peripheral base address
 * @param cipherHandleID unique Cipher handle ID obtained by calling ELE_OpenCipherService()
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_CloseCipherService(S3MU_Type *mu, uint32_t cipherHandleID);

/*!
 * @brief ELE Cipher
 *
 * This function encrypt or decrypt data usign crypto cipher (AES-ECB/CBC/CTR) with keys in EdgeLock Enclave service.
 *
 * @param mu MU peripheral base address
 * @param cipherHandleID unique Cipher handle ID obtained by calling ELE_OpenCipherService()
 * @param conf Pointer where HSM cipher configuration structure can be found
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_Cipher(S3MU_Type *mu, uint32_t cipherHandleID, ele_hsm_cipher_t *conf);

/*!
 * @brief Open ELE AEAD Cipher
 *
 * This function encrypt or decrypt data usign crypto AES AEAD with keys in EdgeLock Enclave service.
 *
 * @param mu MU peripheral base address
 * @param cipherHandleID unique Cipher handle ID obtained by calling ELE_OpenCipherService()
 * @param conf Pointer where HSM cipher configuration structure can be found
 * @param aad pointer where a additional authenticated data can be found
 * @param aad_size size of aad data in bytes
 * @param iv_gen_flags Relevant for GCM only. Specifies mode of generating IV for GCM, for CCM must be 0
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_Aead(S3MU_Type *mu,
                  uint32_t cipherHandleID,
                  ele_hsm_cipher_t *conf,
                  uint32_t aad,
                  size_t aad_size,
                  iv_generation_t iv_gen_flags);

/*!
 * @brief Open ELE MAC Service
 *
 * This function opens MAC Service for EdgeLock Enclave.
 *
 * @param mu MU peripheral base address
 * @param keystoreHandleID unique session ID obtained by calling ELE_OpenKeystore()
 * @param MacHandleID pointer to output unique MAC session handle ID word
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_OpenMacService(S3MU_Type *mu, uint32_t keystoreHandleID, uint32_t *MacHandleID);

/*!
 * @brief Close ELE MAC Service
 *
 * This function closes the MAC Service for EdgeLock Enclave.
 *
 * @param mu MU peripheral base address
 * @param MacHandleID unique MAC handle ID obtained by calling ELE_OpenMacService()
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_CloseMacService(S3MU_Type *mu, uint32_t MacHandleID);

/*!
 * @brief ELE MAC
 *
 * This function is used to perform one-shot MAC generation or verification.
 *
 * @param mu MU peripheral base address
 * @param conf pointer where the MAC configuration structure can be found
 * @param verify_status pointer to verification  status in kMAC_Verify mode. Value MAC_VERIFY_SUCCESS (0x6C1AA1C6) is
 * verification success. Value 0x0 is failure. This value has no sense in kMAC_Generate mode, so can be NULL.
 * @param out_mac_size pointer where to save the size, in bytes, of the resulting MAC in kMAC_Generate mode,
 *        or the input MAC size in kMAC_Verify mode
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 *        kStatus_InvalidArgument if invalid argument
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange,
 *                  kStatus_ELE_BufferTooSmall
 */
status_t ELE_Mac(S3MU_Type *mu, ele_mac_t *conf, uint32_t *verify_status, uint16_t *out_mac_size);

/*!
 * @brief Open ELE RNG Get random
 *
 * This function gets random number from ELE RNG.
 *
 * @param mu MU peripheral base address
 * @param output pointer to output buffer where to store random number
 * @param size size of requested random data
 * @param reseed_flag option to reseed the DRBG instance
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_RngGetRandom(S3MU_Type *mu, uint32_t *output, size_t size, rng_reseed_flag_t reseed_flag);

/*!
 * @brief Open and Create Key Store
 *
 * This function create key store and open key store services in the EdgeLock Enclave.
 *
 * @param mu MU peripheral base address
 * @param sessionID unique session ID obtained by calling ELE_OpenSession()
 * @param conf pointer where keystore configuration structure can be found
 * @param keystoreHandleID pointer where unique Keystore handle ID word will be stored
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_CreateKeystore(S3MU_Type *mu, uint32_t sessionID, ele_keystore_t *conf, uint32_t *keystoreHandleID);

/*!
 * @brief Open and Create Key Store
 *
 * This function create key store and open key store services in the EdgeLock Enclave.
 *
 * @param mu MU peripheral base address
 * @param sessionID unique session ID obtained by calling ELE_OpenSession()
 * @param conf pointer where keystore configuration structure can be found
 * @param keystoreHandleID pointer where unique Keystore handle ID word will be stored
 * @param keystoreChunk pointer to Keystore chunk exported via ELE_ExportChunks()
 * @param chunkSize size of chunk to be imported. Obtained via ELE_ExportChunks()
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_OpenKeystore(S3MU_Type *mu,
                          uint32_t sessionID,
                          ele_keystore_t *conf,
                          uint32_t *keystoreHandleID,
                          uint32_t *keystoreChunk,
                          size_t chunkSize);

/*!
 * @brief Close Key Store
 *
 * This function closes key store and its services in the EdgeLock Enclave.
 *
 * @param mu MU peripheral base address
 * @param keystoreHandleID unique session ID obtained by calling ELE_CreateKeystore()
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_CloseKeystore(S3MU_Type *mu, uint32_t keystoreHandleID);

/*!
 * @brief Open ELE Key Management Service
 *
 * This function opens Key Management Service for EdgeLock Enclave.
 *
 * @param mu MU peripheral base address
 * @param keystoreHandleID unique session ID obtained by calling ELE_CreateKeystore()
 * @param keyHandleID pointer where unique key management handle ID word will be stored
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_OpenKeyService(S3MU_Type *mu, uint32_t keystoreHandleID, uint32_t *keyHandleID);

/*!
 * @brief ELE Key Management Service
 *
 * This function provides the Key Group Management Service for EdgeLock Enclave.
 *
 * @param mu MU peripheral base address
 * @param keyHandleID unique key management handle ID obtained by calling ELE_OpenKeyService()
 * @param operation Requested opration, see key_group_mng_t enum
 * @param addr If operation with chunks is requested, this address is used to either Import or Export chunk.
 * @param size If operation with chunks is requested, this size is used to either Import or Export chunk.
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_ManageKeyGroup(
    S3MU_Type *mu, uint32_t keyHandleID, uint32_t keyGroupID, key_group_mng_t operation, uint32_t *addr, size_t size);

/*!
 * @brief Close ELE Key Management Service
 *
 * This function closes the Key Management Service for EdgeLock Enclave.
 *
 * @param mu MU peripheral base address
 * @param keyHandleID unique key management handle ID obtained by calling ELE_OpenKeyService()
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_CloseKeyService(S3MU_Type *mu, uint32_t keyHandleID);

/*!
 * @brief ELE Storage Master Import Service
 *
 * This function provides Storage Master Import Service for EdgeLock Enclave.
 * This must be called prior opening keystore stored in the NVM.
 *
 * @param mu MU peripheral base address
 * @param nvmStorageID unique session ID obtained by calling ELE_OpenNvmStorageService()
 * @param addr Address of storage master chunk to be imported
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_StorageMasterImport(S3MU_Type *mu, uint32_t nvmStorageID, uint32_t *addr);

/*!
 * @brief ELE Export Chunks Management Service
 *
 * This function provides the Key Group Management Service for exporting keygroup, keystore and storage master chunks.
 *
 * @param mu MU peripheral base address
 * @param keyHandleID unique key management handle ID obtained by calling ELE_OpenKeyService()
 * @param exportKeyGroup If true, key group (keyGroupID) chunk is exported, if false, only keystore and master
 * @param keyGroupID unique key group ID choosen by user. Not used if exportKeyGroup is false
 * @param monotonic  If true, Monotonic counter increment happen (anti-rollback protection)
 * @param chunks ELE Chunks container structure, see ele_chunks_t.
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_ExportChunks(S3MU_Type *mu,
                          uint32_t keyHandleID,
                          bool exportKeyGroup,
                          uint32_t keyGroupID,
                          bool monotonic,
                          ele_chunks_t *chunks);

/*!
 * @brief ELE Generate Key
 *
 * This function generates a key inside given keys store in the EdgeLock Enclave.
 *
 * @param mu MU peripheral base address
 * @param keyHandleID unique key management handle ID obtained by calling ELE_OpenKeyService()
 * @param conf pointer where key generate configuration structure can be found
 * @param keyID pointer where unique Key ID word will be stored
 * @param outSize pointer where to save the resulting key size or the expected
 *        size of the key buffer, if the buffer is found to be too small, in which case
 *        an error is also returned
 * @param monotonic if true, the monotonic counter flag is set
 * @param sync if true, the SYNC flag is set
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail,
 *         kStatus_InvalidArgument if invalid argument
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange,
 *                  kStatus_ELE_BufferTooSmall
 */
status_t ELE_GenerateKey(S3MU_Type *mu,
                         uint32_t keyHandleID,
                         ele_gen_key_t *conf,
                         uint32_t *keyID,
                         uint16_t *outSize,
                         bool monotonic,
                         bool sync);

/*!
 * @brief ELE Generate Public Key
 *
 * This function generates a public key from private asymmetric key inside EdgeLock Enclave.
 *
 * @param mu MU peripheral base address
 * @param keystoreHandleID unique session ID obtained by calling ELE_OpenKeystore()
 * @param conf pointer where key generate configuration structure can be found
 * @param keyID Identifier of asymmetric key inside ELE
 * @param output output bufer where the public key will be written
 * @param outKeySize Length in bytes of output key buffer
 * @param outSize pointer where to save the resulting key size or the expected
 *        size of the key buffer, if the buffer is found to be too small, in which case
 *        an error is also returned
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail,
 *         kStatus_InvalidArgument if invalid argument
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange,
 *                  kStatus_ELE_BufferTooSmall
 */
status_t ELE_GeneratePubKey(
    S3MU_Type *mu, uint32_t keystoreHandleID, uint32_t keyID, uint32_t *output, uint32_t outKeySize, uint16_t *outSize);

/*!
 * @brief ELE Delete Key
 *
 * This function deletes a key from a keystore in the EdgeLock Enclave.
 *
 * @param mu MU peripheral base address
 * @param keyHandleID unique key management handle ID obtained by calling ELE_OpenKeyService()
 * @param keyID unique key ID obtained by calling ELE_GenerateKey()
 * @param monotonic if true, the monotonic counter flag is set
 * @param sync if true, the SYNC flag is set
 *
 * @return kStatus_Success if success, kStatus_Fail if fail,
 *         kStatus_InvalidArgument if invalid argument
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_DeleteKey(S3MU_Type *mu, uint32_t keyHandleID, uint32_t keyID, bool monotonic, bool sync);

/*!
 * @brief Open ELE Sign Service
 *
 * This function opens Sign generation service for EdgeLock Enclave.
 *
 * @param mu MU peripheral base address
 * @param keystoreHandleID unique session ID obtained by calling ELE_CreateKeystore()
 * @param signHandleID pointer where unique sign handle ID word will be stored
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_OpenSignService(S3MU_Type *mu, uint32_t keystoreHandleID, uint32_t *signHandleID);

/*!
 * @brief Close ELE Sign Service
 *
 * This function closes the Sign generation service for EdgeLock Enclave.
 *
 * @param mu MU peripheral base address
 * @param signHandleID unique session ID obtained by calling ELE_OpenSignService()
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_CloseSignService(S3MU_Type *mu, uint32_t signHandleID);

/*!
 * @brief Open ELE Sign
 *
 * This function generates signiture based on provided data and keys using EdgeLock Enclave.
 *
 * @param mu MU peripheral base address
 * @param signHandleID unique session ID obtained by calling ELE_OpenSignService()
 * @param conf pointer where sign generate configuration structure can be found
 * @param signature_size pointer where to save the resulting signature size or the expected
 *        size of the signature buffer, if the buffer is found to be too small, in which case
 *        an error is also returned
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail,
 *         kStatus_InvalidArgument if invalid argument
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange,
 *                  kStatus_ELE_BufferTooSmall
 */
status_t ELE_Sign(S3MU_Type *mu, uint32_t signHandleID, ele_sign_t *conf, uint32_t *signature_size);

/*!
 * @brief Open ELE Verify Service
 *
 * This function opens Verify service for EdgeLock Enclave.
 *
 * @param mu MU peripheral base address
 * @param sessionID unique session ID obtained by calling ELE_OpenSession()
 * @param verifyHandleID pointer where unique verify handle ID word will be stored
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_OpenVerifyService(S3MU_Type *mu, uint32_t sessionID, uint32_t *verifyHandleID);

/*!
 * @brief Close ELE Verify Service
 *
 * This function closes Verify service for EdgeLock Enclave.
 *
 * @param mu MU peripheral base address
 * @param verifyHandleID unique session ID obtained by calling ELE_OpenVerifyService()
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_CloseVerifyService(S3MU_Type *mu, uint32_t verifyHandleID);

/*!
 * @brief Open ELE Verify
 *
 * This function is used to proceed with a signature verification operation using EdgeLock Enclave.
 *
 * @param mu MU peripheral base address
 * @param signHandleID unique session ID obtained by calling ELE_OpenVerifyService()
 * @param conf pointer where verification configuration structure can be found
 * @param result true if verification success, false otherwise
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_Verify(S3MU_Type *mu, uint32_t verifyHandleID, ele_verify_t *conf, bool *result);

/*!
 * @brief Open NVM Storage Service
 *
 * This function opens non-volatile storage services for EdgeLock Enclave.
 *
 * @param mu MU peripheral base address
 * @param sessionID unique session ID obtained by calling ELE_OpenSession()
 * @param nvmStorageID pointer where unique NVM storage handle ID word will be stored
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_OpenNvmStorageService(S3MU_Type *mu, uint32_t sessionID, uint32_t *nvmStorageID);

/*!
 * @brief Close ELE NVM Storage Service
 *
 * This function closes Non-volatile memory storage service for EdgeLock Enclave.
 * Service is used for importing and exporting data to/from ELE.
 *
 * @param mu MU peripheral base address
 * @param nvmStorageID unique session ID obtained by calling ELE_OpenNvmStorageService()
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_CloseNvmStorageService(S3MU_Type *mu, uint32_t nvmStorageID);

/*!
 * @brief Open Data Storage Service
 *
 * This function opens data storage service for EdgeLock Enclave.
 *
 * @param mu MU peripheral base address
 * @param keystoreHandleID unique session ID obtained by calling ELE_CreateKeystore()
 * @param dataStorageID Pointer where unique storage handle ID word will be stored
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_OpenDataStorage(S3MU_Type *mu, uint32_t keystoreHandleID, uint32_t *dataStorageID);

/*!
 * @brief Close ELE Data Storage Service
 *
 * This function closes data storage service for EdgeLock Enclave.
 *
 * @param mu MU peripheral base address
 * @param dataStorageID unique session ID obtained by calling ELE_OpenDataStorage()
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_CloseDataStorage(S3MU_Type *mu, uint32_t dataStorageID);

/*!
 * @brief Store Data Storage
 *
 * This function stores data using EdgeLock Enclave data storage services and
 * places the data at the address specified by conf.chunk_addr. If this address
 * is set to NULL, heap is allocated, the data is placed there, and the allocated heap
 * address is returned in the same variable.
 *
 * @param mu MU peripheral base address
 * @param storageHandleID Unique session ID obtained by calling ELE_OpenStorageService()
 * @param conf Pointer where data storage configuration structure can be found
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_StoreDataStorage(S3MU_Type *mu, uint32_t storageHandleID, ele_data_storage_t *conf);

/*!
 * @brief Retrieve Data Storage
 *
 * This function retrieves data using EdgeLock Enclave data storage services and
 * places the data at the address specified by conf.data. If this address is set
 * to NULL, heap is allocated, the data is placed there, and the allocated heap
 * address is returned in the same variable.
 *
 * @param mu MU peripheral base address
 * @param storageHandleID Unique session ID obtained by calling ELE_OpenStorageService()
 * @param conf Pointer where data storage configuration structure can be found
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_RetrieveDataStorage(S3MU_Type *mu, uint32_t storageHandleID, ele_data_storage_t *conf);

/*!
 * @brief Open ELE Generic Cipher
 *
 * This function encrypt or decrypt data usign generic crypto cipher EdgeLock Enclave service.
 *
 * @param mu MU peripheral base address
 * @param conf Pointer where generic cipher configuration structure can be found
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_GenericCipher(S3MU_Type *mu, ele_generic_cipher_t *conf);

/*!
 * @brief Open ELE Generic Cipher
 *
 * This function encrypt or decrypt data usign generic crypto AES AEAD EdgeLock Enclave service.
 *
 * @param mu MU peripheral base address
 * @param conf Pointer where generic AEAD configuration structure can be found
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_GenericAead(S3MU_Type *mu, ele_generic_aead_t *conf);

#define ECDSA_GENERIC_NOT_SUPPORTED (1u)
#if !ECDSA_GENERIC_NOT_SUPPORTED
/*!
 * @brief ELE Generic ECDSA
 *
 * This function sign or verify data using generic ECDSA EdgeLock Enclave service.
 *
 * @param mu MU peripheral base address
 * @param conf Pointer where generic ECDSA configuration structure can be found
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_GenericEcdsa(S3MU_Type *mu, ele_generic_ecdsa_t *conf);
#endif /* !ECDSA_GENERIC_NOT_SUPPORTED */

/*!
 * @brief ELE Generic RSA
 *
 * This function sign, verify, encrypt or decrypt data using generic RSA EdgeLock Enclave service.
 *
 * @param mu MU peripheral base address
 * @param conf Pointer where generic RSA configuration structure can be found
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_GenericRsa(S3MU_Type *mu, ele_generic_rsa_t *conf);

/*!
 * @brief ELE Generic RSA key gen
 *
 * This function generates RSA key-pair using generic RSA EdgeLock Enclave service.
 *
 * @param mu MU peripheral base address
 * @param conf Pointer where generic RSA configuration structure can be found
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_GenericRsaKeygen(S3MU_Type *mu, ele_generic_rsa_t *conf);

/*!
 * @brief Ping ELE
 *
 * This function Ping EdgeLock Enclave, can be sent at any time to verify ELE is alive.
 * Additionally, this command reloads the fuse shadow registers and kick the Sentinel active bit.
 * This active bit must be kicked at least once every day (24 hours).
 *
 * @param mu MU peripheral base address
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_Ping(S3MU_Type *mu);

/*!
 * @brief Get ELE FW Version
 *
 * This function is used to retrieve the Sentinel FW version.
 *
 * @param mu MU peripheral base address
 * @param EleFwVersion Pointer where ElE firmware version will be stored
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_GetFwVersion(S3MU_Type *mu, uint32_t *EleFwVersion);

/*!
 * @brief Get ELE FW Status
 *
 * This function is used to retrieve the Sentinel FW status.
 *
 * @param mu MU peripheral base address
 * @param EleFwStatus Pointer where ElE firmware status will be stored
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_GetFwStatus(S3MU_Type *mu, uint32_t *EleFwStatus);

/*!
 * @brief Enable APC (Application core)
 *
 * This function is used by RTC (real time core) to release APC (Application core) when needed.
 *
 * @param mu MU peripheral base address
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_EnableAPC(S3MU_Type *mu);

/*!
 * @brief Forward Lifecycle update
 *
 * This function is to change chip lifecycle
 *  0x01U for NXP provisoned
 *  0x02U for OEM Open
 *  0x08U for OEM Closed
 *  0x80U for OEM Locked
 *
 * @param mu MU peripheral base address
 * @param Lifecycle to switch
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_ForwardLifecycle(S3MU_Type *mu, uint32_t Lifecycle);

/*!
 * @brief Read common fuse
 *
 * This function is used to read non-security fuses that are not available through the FSB module
 *
 * @param mu MU peripheral base address
 * @param FuseID ID of fuse to be read
 * @param Fuses Pointer where the value of the read fuse is stored
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_ReadFuse(S3MU_Type *mu, uint32_t FuseID, uint32_t *Fuse);

/*!
 * @brief Release RDC
 *
 * This function is used to release specifed RDC to the core identified in this function.
 * The RDC will be released only if the FW of the core to which is the RDC ownership is going to be
 * transferred has been properly authenticated and verified.
 *
 * @param mu MU peripheral base address
 * @param RdcID Resource Domain Control identifier
 * @param CoreID Core identifier
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_ReleaseRDC(S3MU_Type *mu, uint32_t RdcID, uint32_t CoreID);

/*!
 * @brief Write fuse
 *
 * This function is used to write fuses.
 * Example bit granularity - write bit 5 and 7 of fuse word index 10. BitPosition = 10*32+5 = 0x145. BitLength = 3.
 * Payload is 0b101 = 0x5 . Example word granularity - write fuse word index 10. BitPosition = 10*32 = 0x140. BitLength
 * = 32 = 0x60. Payload 0xWord1.
 *
 * @param mu MU peripheral base address
 * @param BitPosition Fuse identifier expressed as its position in bit in the fuse map.
 * @param BitLength Number of bits to be written
 * @param Payload Data to be written in fuse
 * @param lock Write lock requirement, when set to 1 fuse words are locked, when set to 0 no write lock done
 * @param Payload Data to be written in fuse
 * @param Processed_idx Pointer where the index of last proccesed fuse is stored. Value is valid if !=0xffff
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_WriteFuse(
    S3MU_Type *mu, uint32_t BitPosition, uint32_t BitLength, uint32_t Payload, bool lock, uint32_t *Processed_idx);

/*!
 * @brief Send signed message
 *
 * This function sends Signed message. SignedMsg must be formatted according to specification
 *
 * @param mu MU peripheral base address
 * @param Type type of signed message
 * @param SignedMsg pointer in system memory where Signed message block can be found
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_SendSignedMsg(S3MU_Type *mu, signed_msg_type_t Type, uint32_t *SignedMsg);

/*!
 * @brief Start the initialization of the RNG context.
 *
 * The RNG must be started before using some of the ELE services.
 *
 * @param mu MU peripheral base address
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_StartRng(S3MU_Type *mu);

/*!
 * @brief Get TRNG State
 *
 * This command is used to get TRNG state from ELE.
 *
 * @param mu MU peripheral base address
 * @param state pointer to output buffer where response data will be writen, user must ensure atleast 4 bytes
 * avaliable
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_GetTrngState(S3MU_Type *mu, uint32_t *state);

/*!
 * @brief Get info
 *
 * This command is used to get various information from ELE.
 *
 * @param mu MU peripheral base address
 * @param ResponseData pointer to output buffer where to Response data will be writen, user must ensure atleast 160
 * bytes avaliable
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_GetInfo(S3MU_Type *mu, uint8_t *ResponseData);

/*!
 * @brief Enable an instance of OTFAD.
 *
 * @param mu MU peripheral base address
 * @param OtfadID ID of the OTFAD instance to enable - used only if there are
 * multiple instances on the SoC
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_EnableOtfad(S3MU_Type *mu, uint8_t OtfadID);

/*!
 * @brief Get device attestation
 *
 * This command is used to get signature-certified information from ELE.
 *
 * @param mu MU peripheral base address
 * @param Nonce is the input nonce for the attestation service - see baseline API documentation
 * if words 2-4 are reserved and should be set to 0 on specific devices
 * @param ResponseData pointer to output buffer where to response data will be writen, user must ensure atleast 272
 * bytes avaliable
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_Attest(S3MU_Type *mu, attestation_nonce_t Nonce, uint8_t *ResponseData);

/*!
 * @brief Start the clock change process
 *
 * @param mu MU peripheral base address
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_ClockChangeStart(S3MU_Type *mu);

/*!
 * @brief Change ELE and/or CM33 clock
 *
 * It is valid to pass both parameters at the same time if the SoC supports both.
 *
 * @param mu MU peripheral base address
 * @param NewClockRateELE the new clock rate for ELE
 * @param NewClockRateCM33 the new clock rate for the CM33 core
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_ClockChangeFinish(S3MU_Type *mu, uint8_t NewClockRateELE, uint8_t NewClockRateCM33);

/*!
 * @brief Fast Mac Start
 *
 * This command is used to enter in "Fast MAC" operation mode. This is the first step of the fast MAC API.
 * During this step, ELE will copy key into internal memory in order to accelerate future usage of the key.
 * ELE will also enter in a special mode where only Fast MAC will be accepted. All other commands will be rejected.
 *
 * @param base MU peripheral base address
 * @param key  Pointer to key data buffer, which is expected to be 64 Bytes long consisting of two 256 bit keys.
 *             The key size is hardcoded to 256 bits and other key sizes are not supported.
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_FastMacStart(S3MU_Type *mu, const uint8_t *key);

/*!
 * @brief Fast Mac Proceed
 *
 * This command is used to proceed with a Fast MAC generation. The user gives as input the message buffer and size,
 * and ELE output to the User's MAC buffer the computed MAC. ELE use the key given in Start API.
 *
 * @param base MU peripheral base address.
 * @param msg pointer where input message data can be found.
 * @param mac pointer to a buffer where the MAC data are written by ELE.
 *            If doing a OneShot operation with internal verification enabled,
 *            this buffer must hold the expected MAC value.
 * @param msgSize size of message in bytes. If doing a Preload operation with
 *                internal verification enabled, this must be the length of the
 *                input message + the length of the concatenated expected MAC.
 *                @note If oneshot, limit is UIN16_MAX, otherwise 512 Bytes.
 * @param flags the flags specifying Fast MAC Proceed behavior.
 *              See the FAST_MAC_* macros in ele_crypto.h.
 * @param verifStatus returns the verification status after MAC computation if
 *                    the internal verification flag was enabled. May be NULL.
 *                    See the FAST_MAC_CHECK_VERIFICATION_* macros for
 *                    checking the returned status.
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_FastMacProceed(
    S3MU_Type *mu, const uint8_t *msg, uint8_t *mac, uint16_t msgSize, uint16_t flags, uint32_t *verifStatus);

/*!
 * @brief Fast Mac End
 *
 * This command is used to exit from "Fast MAC" mode.
 *
 * @param mu MU peripheral base address
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_FastMacEnd(S3MU_Type *mu);

/*!
 * @brief Generate a key blob
 *
 * Used to encapsulate sensitive keys in a specific structure called a blob,
 * which provides both confidentiality and integrity protection.
 *
 * @param mu MU peripheral base address
 * @param KeyID depends on blob type, see baseline API documentation
 * @param Conf is a pointer to the key blob generation configuration struct
 * @param OutputBuffer is a pointer to the output buffer, where the key blob is placed, must be 64-bit aligned
 * @param OutputBufferSize is the size of the output buffer
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail,
 * kStatus_InvalidArgument if invalid argument
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_GenerateKeyBlob(
    S3MU_Type *mu, uint32_t KeyID, generate_key_blob_input_t *Conf, uint8_t *OutputBuffer, uint16_t OutputBufferSize);

/*!
 * @brief Import keys from key blob to corresponding HW block - currently only IEE supported
 *
 * @param mu MU peripheral base address
 * @param KeyID identical to the one used for ELE_GenerateKeyBlob()
 * @param BlobAddress pointer to the blob generated with ELE_GenerateKeyBlob()
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail,
 * kStatus_InvalidArgument if invalid argument
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_LoadKeyBlob(S3MU_Type *mu, uint32_t KeyID, uint8_t *BlobAddress);

/*!
 * @brief Import an EdgeLock2Go or ELE key.
 *
 * @param mu MU peripheral base address
 * @param keyHandleID identifier of a key management sevice opened with ELE_OpenKeyService()
 * @param input pointer to the TLV blob containing the key to be imported
 * @param inputSize the size of the input TLV blob in Bytes
 * @param keyGroupAuto set to true to let ELE select the key group to import the key into
 * @param keyGroupID identifier of the keygroup to import the key into if keyGroupAuto is false
 * @param option specifies if the TLV blob is an EdgeLock2Go option or an ELE option
 * @param monotonic if true, the monotonic counter flag is set
 * @param sync if true, the SYNC flag is set
 * @param keyID output parameter returning the ID of the imported key
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail,
 * kStatus_InvalidArgument if invalid argument
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_ImportKey(S3MU_Type *mu,
                       uint32_t keyHandleID,
                       uint8_t *input,
                       uint32_t inputSize,
                       bool keyGroupAuto,
                       uint16_t keyGroupID,
                       ele_import_key_option_t option,
                       bool sync,
                       bool monotonic,
                       uint32_t *keyID);

/*!
 * @brief Write BBSM
 *
 * This function is used to program Battery-Backed Security Module registers inside ELE.
 * For the BBSM registers description, please refer to Secure Reference Manual.
 *
 * @param mu MU peripheral base address
 * @param offset Offset of the register to perform the operation
 * @param value value to be written into BBSM register
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_WriteBbsm(S3MU_Type *mu, uint32_t offset, uint32_t value);

/*!
 * @brief Read BBSM
 *
 * This function is used to read Battery-Backed Security Module registers inside ELE
 * For the BBSM registers description, please refer to Secure Reference Manual.
 *
 * @param mu MU peripheral base address
 * @param offset Offset of the register to perform the operation
 * @param value address of 4B (word) buffer where read value from BBSM register is returned
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_ReadBbsm(S3MU_Type *mu, uint32_t offset, uint32_t *value);

/*!
 * @brief Set BBSM policy
 *
 * This function is used to set policy for Battery-Backed Security Module in case of events
 *
 * @param mu MU peripheral base address
 * @param policy_mask policy to be set (refer to ele_bbsm_policy_t)
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_SetPolicyBbsm(S3MU_Type *mu, uint32_t alert_mask);

/*!
 * @brief Set ELE Get Event
 *
 * This function is used to retrieve any singular event that has occurred since the FW has started.
 * A singular event occurs when the second word of a response to any request is different from ELE_SUCCESS.
 * That includes commands with failure response as well as commands with successful response containing an indication
 * (i.e. warning response).
 *
 * The events are stored by ELE in a fixed sized buffer. When the capacity of the buffer is exceeded, new occurring
 * events are lost.
 *
 * The event buffer is systematically returned in full to the requester independently of the actual numbers of events
 * stored
 *
 * @param mu MU peripheral base address
 * @param events Events buffer (refer to ele_events_t)
 *
 * @return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_GetEvent(S3MU_Type *mu, ele_events_t *events);

#if defined(__cplusplus)
}
#endif

/*! @} */ /* end of group s3mu */

#endif    /* __ELE_CRYPTO_H__ */
