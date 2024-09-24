/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef NBOOT_API_H_
#define NBOOT_API_H_

#include <stdlib.h>
#include <stdint.h>
#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 *******************************************************************************/
#define NBOOT_ROOT_CERT_COUNT                                  (4u)
#define NXPCLSB3_DIGEST_LENGTH_SHA256                          (32u)
#define NXPCLSB3_DIGEST_LENGTH_SHA384                          (48u)
#define NXPCLSB3_MAX_DIGEST_LENGTH                             (48u)
#define NBOOT_CONTEXT_RUNTIME_FINGERPRINT_BYTELEN              (32u)
#define NBOOT_CONTEXT_CRYPTOLIB_MULTIPART_CMAC_CONTEXT_BYTELEN (256u)
#define NBOOT_CONTEXT_GDET_CONF_BUFFER_BYTELEN                 (16u)
#define NBOOT_CONTEXT_CRYPTOLIB_MULTIPART_DRBG_CONTEXT_BYTELEN (544u)
#define NBOOT_GET_WORDLEN_FROM_BYTELEN(bytelen)                ((bytelen + 3) / sizeof(uint32_t))
#define NBOOT_KEYINFO_WORDLEN                                  (23u)
#define NXPCLHASH_WA_SIZE_MAX                                  (128u + 64u)
#define NBOOT_CONTEXT_BYTELEN                                  (192u + NXPCLHASH_WA_SIZE_MAX)
#define NBOOT_CONTEXT_WORDLEN                                  (NBOOT_CONTEXT_BYTELEN / sizeof(uint32_t))
#define NXPCLCSS_HASH_RTF_OUTPUT_SIZE                          ((size_t)32U) ///< Size of RTF appendix to hash output buffer, in bytes

#define NBOOT_EC_COORDINATE_256_SIZE_IN_BYTES (32u)
#define NBOOT_EC_COORDINATE_384_SIZE_IN_BYTES (48u)
#define NBOOT_EC_COORDINATE_521_SIZE_IN_BYTES (66u)

#define NBOOT_EC_COORDINATE_MAX_SIZE         NBOOT_EC_COORDINATE_384_SIZE_IN_BYTES
#define NBOOT_EC_MIN_SIGNATURE_SIZE_IN_BYTES (2u * NBOOT_EC_COORDINATE_256_SIZE_IN_BYTES)

#define NBOOT_ROOT_OF_TRUST_HASH_SIZE_IN_BYTES (48u)

/* SB3.1 */
#define NBOOT_SB3_MANIFEST_MAX_LENGTH_IN_BYTES \
    ((712u) + NBOOT_ISK_USER_DATA_MAX_SIZE_IN_BYTES) /* 712 + user data size */
#define NBOOT_SB3_MANIFEST_MIN_LENGTH_IN_BYTES \
    (236u) /* sb3.1 header (60) + sha256 hash (32) + min cert block (80) + secp256 signature (64) */
#define NBOOT_SB3_CHUNK_SIZE_IN_BYTES         (256u)
#define NBOOT_SB3_BLOCK_HASH256_SIZE_IN_BYTES (32u)
#define NBOOT_SB3_BLOCK_HASH384_SIZE_IN_BYTES (48u)

/*!
 * @brief NBOOT type for a timestamp
 *
 * This type defines the NBOOT timestamp
 *
 */
typedef uint32_t nboot_timestamp_t[2];

/*!
 * @brief NBOOT SB3.1 header type
 *
 * This type defines the header used in the SB3.1 manifest
 *
 */
typedef struct _nboot_sb3_header
{
    uint32_t magic;         /*!< offset 0x00: Fixed 4-byte string of 'sbv3' without the trailing NULL */
    uint32_t formatVersion; /*!< offset 0x04: (major = 3, minor = 1); The format version determines the manifest
                               (block0) size. */
    uint32_t flags;         /*!< offset 0x08: not defined yet, keep zero for future compatibility */
    uint32_t blockCount;    /*!< offset 0x0C: Number of blocks not including the manifest (block0). */
    uint32_t
        blockSize; /*!< offset 0x10: Size in bytes of data block (repeated blockCount times for SB3 data stream). */
    nboot_timestamp_t timeStamp;     /*!< offset 0x14: 64-bit value used as key derivation data. */
    uint32_t firmwareVersion;        /*!< offset 0x1c: Version number of the included firmware */
    uint32_t imageTotalLength;       /*!< offset 0x20: Total manifest length in bytes, including signatures etc. */
    uint32_t imageType;              /*!< offset 0x24: image type and flags */
    uint32_t certificateBlockOffset; /*!< offset 0x28: Offset from start of header block to the certificate block. */
    uint8_t description[16];         /*!< offset 0x32: This field provides description of the file. It is an arbitrary
                                                      string injected by the signing tool, which helps to identify the file. */
} nboot_sb3_header_t;

#define NBOOT_SB3_MANIFEST_MAX_SIZE_IN_BYTES                                                                  \
    (sizeof(nboot_sb3_header_t) + NBOOT_SB3_BLOCK_HASH384_SIZE_IN_BYTES + sizeof(nboot_certificate_block_t) + \
     NBOOT_EC_COORDINATE_MAX_SIZE * 2)
#define NBOOT_SB3_BLOCK_MAX_SIZE_IN_BYTES \
    (4 /* blockNumber */ + NBOOT_SB3_BLOCK_HASH384_SIZE_IN_BYTES + NBOOT_SB3_CHUNK_SIZE_IN_BYTES)

/*! @brief The size of the blob with Key Blob. */
#define NBOOT_KEY_BLOB_SIZE_IN_BYTE_256 (32U)
#define NBOOT_KEY_BLOB_SIZE_IN_BYTE_384 (48U)
#define NBOOT_KEY_BLOB_SIZE_IN_BYTE_MAX (NBOOT_KEY_BLOB_SIZE_IN_BYTE_384)

#define SB3_DATA_BUFFER_SIZE_IN_BYTE (MAX(128, NBOOT_KEY_BLOB_SIZE_IN_BYTE_MAX))

/*!
 * @brief Boolean type for the NBOOT functions
 *
 * This type defines boolean values used by NBOOT functions that are not easily disturbed by Fault Attacks
 *
 */
typedef enum _nboot_bool
{
    kNBOOT_TRUE                = 0x3C5AC33Cu, /*!< Value for TRUE.  */
    kNBOOT_TRUE256             = 0x3C5AC35Au, /*!< Value for TRUE when P256 was used to sign the image.  */
    kNBOOT_TRUE384             = 0x3C5AC3A5u, /*!< Value for TRUE when P384 was used to sign the image.  */
    kNBOOT_FALSE               = 0x5AA55AA5u, /*!< Value for FALSE. */
    kNBOOT_OperationAllowed    = 0x3c5a33ccU,
    kNBOOT_OperationDisallowed = 0x5aa5cc33U,
} nboot_bool_t;

/*! @brief Data structure holding secure counter value used by nboot library */
typedef struct _nboot_secure_counter
{
    uint32_t sc;
    uint32_t scAp;
} nboot_secure_counter_t;

/** Type for nboot protected status codes */
/** Lower 32-bits holds status value eg. kStatus_NBOOT_Success, upper 32-bits are flow protection value */
typedef uint64_t nboot_status_protected_t;
/** Type for nboot status codes */
typedef uint32_t nboot_status_t;

/**
 * \defgroup nbootStatusValues  This type defines status return values used by NBOOT functions that are not easily
 * disturbed by Fault Attacks
 * @{
 */
#define kStatus_NBOOT_Success                ((nboot_status_t)0x5A5A5A5Au) /*!< Operation completed successfully. */
#define kStatus_NBOOT_Fail                   ((nboot_status_t)0x5A5AA5A5u) /*!< Operation failed. */
#define kStatus_NBOOT_InvalidArgument        ((nboot_status_t)0x5A5AA5F0u) /*!< Invalid argument passed to the function. */
#define kStatus_NBOOT_RequestTimeout         ((nboot_status_t)0x5A5AA5E1u) /*!< Operation timed out. */
#define kStatus_NBOOT_KeyNotLoaded           ((nboot_status_t)0x5A5AA5E2u) /*!< The requested key is not loaded. */
#define kStatus_NBOOT_AuthFail               ((nboot_status_t)0x5A5AA5E4u) /*!< Authentication failed. */
#define kStatus_NBOOT_OperationNotAvaialable ((nboot_status_t)0x5A5AA5E5u) /*!< Operation not available on this HW. */
#define kStatus_NBOOT_KeyNotAvailable        ((nboot_status_t)0x5A5AA5E6u) /*!< Key is not avaialble. */
#define kStatus_NBOOT_IvCounterOverflow      ((nboot_status_t)0x5A5AA5E7u) /*!< Overflow of IV counter (PRINCE/IPED). */
#define kStatus_NBOOT_SelftestFail           ((nboot_status_t)0x5A5AA5E8u) /*!< FIPS self-test failure. */
#define kStatus_NBOOT_InvalidDataFormat      ((nboot_status_t)0x5A5AA5E9u) /*!< Invalid data format for example antipole */
#define kStatus_NBOOT_IskCertUserDataTooBig \
    ((nboot_status_t)0x5A5AA5EAu) /*!< Size of User data in ISK certificate is greater than 96 bytes */
#define kStatus_NBOOT_IskCertSignatureOffsetTooSmall \
    ((nboot_status_t)0x5A5AA5EBu) /*!< Signature offset in ISK certificate is smaller than expected */
#define kStatus_NBOOT_MemcpyFail ((nboot_status_t)0x5A5A845A) /*!< Unexpected error detected during nboot_memcpy() */

/**@}*/

typedef uint32_t nboot_root_key_revocation_t;
typedef uint32_t nboot_root_key_usage_t;
typedef uint32_t nboot_root_key_type_and_length_t;

/*! @brief Enumeration for SoC Lifecycle. */
#define nboot_lc_nxpBlank       (0xFFFF0000u)
#define nboot_lc_nxpFab         (0xFFFE0001u)
#define nboot_lc_nxpDev         (0xFF0300FCu)
#define nboot_lc_nxpProvisioned (0xFFFC0003u)
#define nboot_lc_oemOpen        (0xFFFC0003u)
#define nboot_lc_oemSecureWorld (0xFFF80007u)
#define nboot_lc_oemClosed      (0xFFF0000Fu)
#define nboot_lc_oemLocked      (0xFF3000CFu)
#define nboot_lc_oemFieldReturn (0xFFE0001Fu)
#define nboot_lc_nxpFieldReturn (0xFF80007Fu)
#define nboot_lc_shredded       (0xFF0000FFu)
typedef uint32_t nboot_soc_lifecycle_t;

typedef struct _nboot_rot_auth_parms
{
    /* trusted information originated from CFPA */
    nboot_root_key_revocation_t soc_rootKeyRevocation[NBOOT_ROOT_CERT_COUNT]; /*!< Provided by caller based on NVM
                                                                                 information in CFPA: ROTKH_REVOKE */
    uint32_t soc_imageKeyRevocation; /*!< Provided by caller based on NVM information in CFPA: IMAGE_KEY_REVOKE */

    /* trusted information originated from CMPA */
    uint32_t soc_rkh[12];          /*!< Provided by caller based on NVM information in CMPA: ROTKH (hash of hashes) */
                                   /*!< In case of kNBOOT_RootKey_Ecdsa_P384, sock_rkh[0..11] are used */
                                   /*!< In case of kNBOOT_RootKey_Ecdsa_P256, sock_rkh[0..7] are used */

    uint32_t soc_numberOfRootKeys; /* unsigned int, between minimum = 1 and maximum = 4; */
    nboot_root_key_usage_t soc_rootKeyUsage[NBOOT_ROOT_CERT_COUNT]; /* CMPA */
    nboot_root_key_type_and_length_t
        soc_rootKeyTypeAndLength; /* static selection between ECDSA P-256 or ECDSA P-384 based root keys */

    /* trusted information originated from OTP fuses */
    nboot_soc_lifecycle_t soc_lifecycle;
} nboot_rot_auth_parms_t;

typedef struct _nboot_sb3_load_manifest_parms
{
    nboot_rot_auth_parms_t soc_RoTNVM;   /*! trusted information originated from CFPA and NMPA */
    uint32_t soc_trustedFirmwareVersion; /*!< Provided by caller based on NVM information in CFPA: Secure_FW_Version */
    uint8_t pckBlob[48];
} nboot_sb3_load_manifest_parms_t;

typedef struct _nboot_img_auth_ecdsa_parms
{
    /* trusted information originated from CFPA and NMPA */
    nboot_rot_auth_parms_t soc_RoTNVM;

    uint32_t soc_trustedFirmwareVersion; /*!< Provided by caller based on NVM information in CFPA: Secure_FW_Version */
} nboot_img_auth_ecdsa_parms_t;

typedef struct _nboot_cmac_authenticate_parms
{
    uint32_t expectedMAC[4]; /*!< expected MAC result */
} nboot_img_authenticate_cmac_parms_t;

typedef struct nboot_sb3_context_t
{
    uint8_t kblk;                                     /*! reference into the nboot key table for used kblk */
    uint32_t expectedHashLen;                         /*! Length of expected hash of next block */
    uint8_t expectedHash[NXPCLSB3_MAX_DIGEST_LENGTH]; /*! Expected hash of next block */
} nboot_sb3_context_t;

/*!
 * @brief NBOOT context type
 *
 * This type defines the NBOOT context
 *
 */
typedef struct _nboot_context
{
    uint32_t totalBlocks; /*!< holds number of SB3 blocks. Initialized by nboot_sb3_load_header(). */
    uint32_t processData; /*!< flag, initialized by nboot_sb3_load_header().
                             SB3 related flag set by NBOOT in case the nboot_sb3_load_block()
                             provides plain data to output buffer (for processing by ROM SB3 loader */
    uint32_t timeout;     /*!< timeout value for css operation. In case it is 0, infinite wait is performed */
    uint32_t keyinfo[NBOOT_KEYINFO_WORDLEN]; /*!< data for NBOOT key management. */
    nboot_sb3_context_t
        sb3; /*!< state for stateful SB3 APIs, shared between nboot_sb3_load_manifest and nboot_sb3_load_block */
    uint32_t uuid[4];           /*!< holds UUID value from NMPA */
    uint32_t prngReadyFlag;     /*!< flag, used by nboot_rng_generate_lq_random() to determine whether CSS is ready to
                                   generate rnd number */
    uint32_t oemShareValidFlag; /*!< flag, used during TP to determine whether valid oemShare was set by
                                   nboot_tp_isp_gen_oem_master_share() */
    uint32_t oemShare[8]; /*!< buffer to store OEM_SHARE computed by nxpCLTrustProv_nboot_isp_gen_oem_master_share()
                               Only first 128-bits are actually used, but since CSS always uses 256-bit key shares,
                               remaining data must be zero filled. Pointer to this buffer is used as input to CSS during
                             KEYPROV */
    nboot_secure_counter_t secureCounter; /*!< Secure counter used by nboot */
    uint32_t rtf[NBOOT_GET_WORDLEN_FROM_BYTELEN(NBOOT_CONTEXT_RUNTIME_FINGERPRINT_BYTELEN)];
    uint32_t imageHash[48 / sizeof(uint32_t)];
    uint32_t authStatus;
    uint32_t disableProvisioningFirmwareNXP;
    uint32_t cryptolib_multipartCmacContext[NBOOT_GET_WORDLEN_FROM_BYTELEN(
        NBOOT_CONTEXT_CRYPTOLIB_MULTIPART_CMAC_CONTEXT_BYTELEN)];
} nboot_context_t;

/*!
 * @brief NBOOT type for an ECC coordinate
 *
 * This type defines the NBOOT ECC coordinate type
 *
 */
typedef uint8_t
    nboot_ecc_coordinate_t[NBOOT_EC_COORDINATE_MAX_SIZE]; /*!ECC point coordinate, up to 384-bits. big endian. */

/*!
 * @brief NBOOT type for an ECC signature
 *
 * This type defines the NBOOT ECC signature type
 *
 */
typedef struct
{
    nboot_ecc_coordinate_t r; /*! r portion of the ECDSA signature, up to 384-bits. big endian. */
    nboot_ecc_coordinate_t s; /*! s portion of the ECDSA signature, up to 384-bits. big endian. */
} nboot_ecdsa_signature_t;

/*!
 * @brief NBOOT type for an ECC point
 *
 * This type defines the NBOOT ECC point type
 *
 */
typedef struct
{
    nboot_ecc_coordinate_t x; /*! x portion of the ECDSA public key, up to 384-bits. big endian. */
    nboot_ecc_coordinate_t y; /*! y portion of the ECDSA public key, up to 384-bits. big endian. */
} nboot_ecdsa_public_key_t;

typedef uint8_t nboot_ctrk_hash_t[NBOOT_ROOT_OF_TRUST_HASH_SIZE_IN_BYTES];

/*!
 * @brief NBOOT type for the hash table
 *
 * This type defines the NBOOT hash table
 *
 */
typedef struct _nboot_ctrk_hash_table
{
    nboot_ctrk_hash_t ctrkHashTable[NBOOT_ROOT_CERT_COUNT];
} nboot_ctrk_hash_table_t;

/*!
 * @brief NBOOT type for the isk block
 *
 * This type defines the constant length part of an NBOOT isk block
 *
 */
typedef struct
{
    uint32_t signatureOffset; /*! Offset of signature in ISK block. */
    uint32_t constraints;     /*! Version number of signing certificate. */
    uint32_t iskFlags;        /*! Reserved for definiton of ISK certificate flags. */
    nboot_ecdsa_public_key_t
        iskPubKey; /*! Public key of signing certificate. Variable length; only used to determine start address*/
    nboot_ecdsa_public_key_t userData; /*! Space for at lest one addition public key*/
    nboot_ecdsa_signature_t iskSign;   /*! ISK signature*/
} nboot_isk_block_t;

/*!
 * @brief NBOOT type for the root certificate block
 *
 * This type defines the NBOOT root certificate block, it is part of the nboot_certificate_block_t
 *
 */
typedef struct _nboot_root_certificate_block
{
    uint32_t flags;                         //!< root certificate flags
    nboot_ctrk_hash_table_t ctrkHashTable;  //!< hash table
    nboot_ecdsa_public_key_t rootPublicKey; //!< root public key
} nboot_root_certificate_block_t;

/*!
 * @brief NBOOT type for the header of the certificate block
 *
 * This type defines the NBOOT header of the certificate block, it is part of the nboot_certificate_block_t
 *
 */
typedef struct _nboot_certificate_header_block
{
    uint32_t magic;                   //!< magic number.
    uint32_t formatMajorMinorVersion; //!< format major minor version
    uint32_t certBlockSize;           //!< Size of the full certificate block
} nboot_certificate_header_block_t;

/*!
 * @brief NBOOT type for the certificate block
 *
 * This type defines the constant length part of an NBOOT certificate block
 *
 */
typedef struct _nboot_certificate_block
{
    nboot_certificate_header_block_t header;
    nboot_root_certificate_block_t rootCertBlock; /*! Details of selected root certificate (root certificate which will
                                                     be used for ISK signing/SB3 header signing) */
    nboot_isk_block_t iskBlock;
} nboot_certificate_block_t;

typedef struct
{
    nboot_status_t (*nboot_context_init)(nboot_context_t *context);
    nboot_status_t (*nboot_context_deinit)(nboot_context_t *context);
    nboot_status_protected_t (*nboot_sb3_load_manifest)(nboot_context_t *context,
                                                        uint32_t *manifest,
                                                        nboot_sb3_load_manifest_parms_t *parms);
    nboot_status_protected_t (*nboot_sb3_load_block)(nboot_context_t *context, uint32_t *block);
    nboot_status_protected_t (*nboot_sb3_check_authenticity_and_completeness)(nboot_context_t *context,
                                                                              uint32_t *address,
                                                                              nboot_sb3_load_manifest_parms_t *parms);
    nboot_status_protected_t (*nboot_img_authenticate_ecdsa)(nboot_context_t *context,
                                                             uint8_t imageStartAddress[],
                                                             nboot_bool_t *isSignatureVerified,
                                                             nboot_img_auth_ecdsa_parms_t *parms);
    nboot_status_protected_t (*nboot_img_authenticate_cmac)(nboot_context_t *context,
                                                            uint8_t imageStartAddress[],
                                                            nboot_bool_t *isSignatureVerified,
                                                            nboot_img_authenticate_cmac_parms_t *parms);
} nboot_interface_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief The function is used for initializing of the nboot context data structure.
 *        It should be called prior to any other calls of nboot API.
 *
 * @param nbootCtx Pointer to nboot_context_t structure.
 *
 * @retval #kStatus_NBOOT_Success Operation successfully finished
 * @retval #kStatus_NBOOT_Fail Error occured during operation
 */
nboot_status_t NBOOT_ContextInit(nboot_context_t *context);

/*!
 * @brief The function is used to deinitialize nboot context data structure.
 * Its contents are overwritten with random data so that any sensitive data does not remain in memory.
 *
 * @param context Pointer to nboot_context_t structure.

 * @retval #kStatus_NBOOT_Success Operation successfully finished
 * @retval #kStatus_NBOOT_Fail Error occured during operation
 */
nboot_status_t NBOOT_ContextDeinit(nboot_context_t *context);

/*!
 * @brief Verify NBOOT SB3.1 manifest (header message)
 *
 * This function verifies the NBOOT SB3.1 manifest (header message), initializes
 * the context and loads keys into the CSS key store so that they can be used by nboot_sb3_load_block
 * function. The NBOOT context has to be initialized by the function nboot_context_init before calling
 * this function. Please note that this API is intended to be used only by users who needs to split
 * FW update process (loading of SB3.1 file) to partial steps to customize whole operation.
 * For regular SB3.1 processing, please use API described in chapter KB APIs.
 *
 * @param nbootCtx Pointer to nboot_context_t structure.
 * @param manifest Pointer to the input manifest buffer
 * @param params additional input parameters. Please refer to nboot_sb3_load_manifest_parms_t definition for details.
 *
 * @retval #kStatus_NBOOT_Success Operation successfully finished
 * @retval #kStatus_NBOOT_Fail Error occured during operation
 */
nboot_status_protected_t NBOOT_Sb3LoadManifest(nboot_context_t *context,
                                               uint32_t *manifest,
                                               nboot_sb3_load_manifest_parms_t *parms);

/*!
 * @brief Verify NBOOT SB3.1 block
 *
 * This function verifies and decrypts an NBOOT SB3.1 block. Decryption is performed in-place.
 * The NBOOT context has to be initialized by the function nboot_context_init before calling this function.
 * Please note that this API is intended to be used only by users who needs to split FW update process
 * (loading of SB3.1 file) to partial steps to customize whole operation. For regular SB3.1 processing,
 * please use API described in KB APIs.
 *
 * @param context Pointer to nboot_context_t structure.
 * @param block Pointer to the input SB3.1 data block
 *
 * @retval #kStatus_NBOOT_Success successfully finished
 * @retval #kStatus_NBOOT_Fail occured during operation
 */
nboot_status_protected_t NBOOT_Sb3LoadBlock(nboot_context_t *context, uint32_t *block);

/*!
 * @brief This function verifies and decrypts an NBOOT SB3.1 block. Decryption is performed in-place.The NBOOT context
 * has to be initialized by the function nboot_context_init before calling this function.
 *
 * @param context Pointer to nboot_context_t structure.
 * @param address Pointer to start of the image in memory
 * @param parms Pointer to a data structure in trusted memory
 *
 * @retval #kStatus_NBOOT_Success successfully finished
 * @retval #kStatus_NBOOT_Fail occured during operation
 */
nboot_status_protected_t NBOOT_Sb3CheckAuthenticityAndCompleteness(nboot_context_t *context,
                                                                   uint32_t *address,
                                                                   nboot_sb3_load_manifest_parms_t *parms);

/*!
 * @brief This function authenticates image with asymmetric cryptography.
 *        The NBOOT context has to be initialized by the function nboot_context_init
 *        before calling this function.
 *
 * @param context Pointer to nboot_context_t structure.
 * @param imageStartAddress Pointer to start of the image in memory.
 * @param isSignatureVerified Pointer to memory holding function call result.
 *                            After the function returns, the value will be set to kNBOOT_TRUE when the image is
 * authentic. Any other value means the authentication does not pass.
 *
 * @param parms Pointer to a data structure in trusted memory, holding input parameters for the algorithm.
 *              The data structure shall be correctly filled before the function call.
 *
 * @retval #kStatus_NBOOT_Success Operation successfully finished
 * @retval #kStatus_NBOOT_Fail Returned in all other cases. Doesn't always mean invalid image,
 *         it could also mean transient error caused by short time environmental conditions.
 */
nboot_status_protected_t NBOOT_ImgAuthenticateEcdsa(nboot_context_t *context,
                                                    uint8_t imageStartAddress[],
                                                    nboot_bool_t *isSignatureVerified,
                                                    nboot_img_auth_ecdsa_parms_t *parms);

/*!
 * @brief This function calculates the CMAC over the given image and compares it to the expected value.
 * To be more resistant against SPA, it is recommended that imageStartAddress is word aligned.
 * The NBOOT context has to be initialized by the nboot_context_init() before calling this function.
 *
 * @param context Pointer to nboot_context_t structure.
 * @param imageStartAddress Pointer to start of the image in memory.
 * @param isSignatureVerified Pointer to memory holding function call result.
                              After the function returns, the value will be set to
 * @param parms Pointer to a data structure in trusted memory, holding the reference MAC.
                The data structure shall be correctly filled before the function call.
 *
 * @retval kStatus_NBOOT_Success
 * @retval kStatus_NBOOT_Fail
 */
nboot_status_protected_t NBOOT_ImgAuthenticateCmac(nboot_context_t *context,
                                                   uint8_t imageStartAddress[],
                                                   nboot_bool_t *isSignatureVerified,
                                                   nboot_img_authenticate_cmac_parms_t *parms);

#endif /* FSL_ROMAPI_NBOOT_H_ */
