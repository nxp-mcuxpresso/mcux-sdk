/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_ROMAPI_NBOOT_H_
#define _FSL_ROMAPI_NBOOT_H_

#include <stdlib.h>
#include <stdint.h>
#include "fsl_common.h"


/**********************************************
 * CONSTANTS
 **********************************************/
#define NBOOT_RESET_VALUE 0x0U

#define NBOOT_IMG_LENGTH_OFFSET 0x20U
#define NBOOT_IMG_TYPE_OFFSET 0x24U
#define NBOOT_IMG_EXTHEADER_OFFSET 0x28U

#define NBOOT_IMG_TYPE_PLAIN 0x0U
#define NBOOT_IMG_TYPE_PLAIN_SIGNED 0x1U
#define NBOOT_IMG_TYPE_PLAIN_CRC 0x2U
#define NBOOT_IMG_TYPE_ENCRYPTED_SIGNED 0x3U
#define NBOOT_IMG_TYPE_XIPPLAINSIGNED 0x4U
#define NBOOT_IMG_TYPE_XIPPLAINCRC 0x5U
#define NBOOT_IMG_TYPE_SB3MANIFEST 0x6U
#define NBOOT_IMG_TYPE_SB3MANIFEST_NXPKEYS 0x7U
#define NBOOT_IMG_TYPE_XIPPLAINSIGNED_NXPKEYS 0x8U
#define NBOOT_IMG_TYPE_PLAIN_RADIO 0x40U
#define NBOOT_IMG_TYPE_SB3MANIFEST_RADIO_NXPKEYS 0x47U

#define NBOOT_IMG_TYPE_MASK 0xFFU

#define NBOOT_IMG_SELECTOR_MBI 0xAA55AA55U
#define NBOOT_IMG_SELECTOR_SB3 0x55AA55AAU

#define NBOOT_IMG_ROOTCERT_DIRECT_SIGN_TRUE 0x80000000U
#define NBOOT_IMG_ROOTCERT_DIRECT_SIGN_FALSE 0x00000000U
#define NBOOT_IMG_ROOTCERT_DIRECT_SIGN_MASK 0x80000000U

#define NBOOT_IMG_FORCECERTCHAIN_BIT 0x1U

#define NBOOT_IMG_CERTBLOCK_MAGIC 0x72646863U
#define NBOOT_IMG_IMGMANIFEST_MAGIC 0x6d676d69U
#define NBOOT_IMG_IMGMANIFEST_MIN_SIZE_IN_BYTES (20u) /* image manifest header (20) */

#define NBOOT_ROOT_CERT_FLAG_CURVE_MASK 0xFU
#define NBOOT_ROOT_CERT_FLAG_CURVE_OFFSET 0x0U
#define NBOOT_ROOT_CERT_FLAG_CURVE_P256 0x1U
#define NBOOT_ROOT_CERT_FLAG_CURVE_P384 0x2U
#define NBOOT_ROOT_CERT_FLAG_NR_ROOTKEYHASHES_MASK 0xFU
#define NBOOT_ROOT_CERT_FLAG_NR_ROOTKEYHASHES_OFFSET 0x4U
#define NBOOT_ROOT_CERT_FLAG_ROOTKEY_INDEX_MASK 0xFU
#define NBOOT_ROOT_CERT_FLAG_ROOTKEY_INDEX_OFFSET 0x8U

#define NBOOT_ISK_CERT_FLAG_CURVE_MASK 0xFU
#define NBOOT_ISK_CERT_FLAG_CURVE_OFFSET 0x0U
#define NBOOT_ISK_CERT_FLAG_CURVE_P256 0x1U
#define NBOOT_ISK_CERT_FLAG_CURVE_P384 0x2U
#define NBOOT_ISK_USER_DATA_MAX_SIZE_IN_BYTES (96u)

#define NBOOT_CERTBLOCK_MAX_LENGTH_IN_BYTES ((508u) + NBOOT_ISK_USER_DATA_MAX_SIZE_IN_BYTES) /* 508 + user data size */
#define NBOOT_CERTBLOCK_MIN_LENGTH_IN_BYTES (80u) /* Certificate block header (12) + flags (4) + secp256 public key (64) */

#define NBOOT_ROOT_CERT_COUNT (4u)
#define NBOOT_CONTEXT_BYTELEN (192u + NXPCLHASH_WA_SIZE_MAX)
#define NBOOT_CONTEXT_WORDLEN (NBOOT_CONTEXT_BYTELEN/sizeof(uint32_t))
#define NBOOT_KEYINFO_WORDLEN (23u)
#define NBOOT_EC_COORDINATE_256_SIZE_IN_BYTES (32u)
#define NBOOT_EC_COORDINATE_384_SIZE_IN_BYTES (48u)
#define NBOOT_EC_COORDINATE_521_SIZE_IN_BYTES (66u)

#define NBOOT_EC_COORDINATE_MAX_SIZE NBOOT_EC_COORDINATE_384_SIZE_IN_BYTES
#define NBOOT_EC_MIN_SIGNATURE_SIZE_IN_BYTES (2u*NBOOT_EC_COORDINATE_256_SIZE_IN_BYTES)

#define NBOOT_ROOT_OF_TRUST_HASH_SIZE_IN_BYTES (48u)

/* SB3.1 */
#define NBOOT_SB3_MANIFEST_MAX_LENGTH_IN_BYTES  ((712u) + NBOOT_ISK_USER_DATA_MAX_SIZE_IN_BYTES) /* 712 + user data size */
#define NBOOT_SB3_MANIFEST_MIN_LENGTH_IN_BYTES  (236u) /* sb3.1 header (60) + sha256 hash (32) + min cert block (80) + secp256 signature (64) */
#define NBOOT_SB3_CHUNK_SIZE_IN_BYTES           (256u)
#define NBOOT_SB3_BLOCK_HASH256_SIZE_IN_BYTES   (32u)
#define NBOOT_SB3_BLOCK_HASH384_SIZE_IN_BYTES   (48u)

/* authStatus */
#define NBOOT_MBI_AUTH_P384_MASK (1u << 0)
#define NBOOT_MBI_AUTH_P256_MASK (1u << 1)
#define NBOOT_CSS_INITIALIZED (1u << 2)
#define NBOOT_AUTH_STATUS_SB3_TYPE_NXP_MFW (1u << 3)
#define NBOOT_AUTH_STATUS_SB3_TYPE_OEM_MFW (1u << 4)
#define NBOOT_AUTH_STATUS_SB3_TYPE_MASK (NBOOT_AUTH_STATUS_SB3_TYPE_NXP_MFW | NBOOT_AUTH_STATUS_SB3_TYPE_OEM_MFW)
#define NBOOT_MBI_AUTH_ROOT_KEY_INDEX_SHIFT (16)
#define NBOOT_MBI_AUTH_ROOT_KEY_INDEX_MASK (0x3u << NBOOT_MBI_AUTH_ROOT_KEY_INDEX_SHIFT)

#define NBOOT_STATE_SB3_TYPE_SHIFT (24)
#define NBOOT_STATE_SB3_TYPE_MASK (0x3u << NBOOT_STATE_SB3_TYPE_SHIFT)
#define NBOOT_STATE_FIPS_CKDF_SHIFT (23)
#define NBOOT_STATE_FIPS_HMAC_SHIFT (22)
#define NBOOT_STATE_FIPS_DRBG_SHIFT (21)
#define NBOOT_STATE_FIPS_ECDSA_SHIFT (20)
#define NBOOT_STATE_FIPS_AES_SHIFT (19)
#define NBOOT_STATE_FIPS_SHA_SHIFT (18)
#define NBOOT_STATE_FIPS_ALL_MASK ((1u << NBOOT_STATE_FIPS_CKDF_SHIFT) | (1u << NBOOT_STATE_FIPS_HMAC_SHIFT) | \
                                   (1u << NBOOT_STATE_FIPS_DRBG_SHIFT) | (1u << NBOOT_STATE_FIPS_ECDSA_SHIFT) | \
                                   (1u << NBOOT_STATE_FIPS_AES_SHIFT) | (1u << NBOOT_STATE_FIPS_SHA_SHIFT))
/* SB 3.1 manifest flags */
#define NBOOT_SB3_MANIFEST_FLAGS_PROV_MFW      (0x00000001u)
#define NBOOT_SB3_MANIFEST_FLAGS_PROV_MFW_MASK (0x00000001u)

#define NBOOT_SB3_MANIFEST_FLAGS_RADIO_TYPE_WIFI (0x00000001u)
#define NBOOT_SB3_MANIFEST_FLAGS_RADIO_TYPE_BLE  (0x00000002u)
#define NBOOT_SB3_MANIFEST_FLAGS_RADIO_TYPE_15_4 (0x00000003u)
#define NBOOT_SB3_MANIFEST_FLAGS_RADIO_TYPE_MASK (0x0000000Fu)

/* TP flags */
#define NBOOT_OEM_SHARE_VALID_FLAG 0x95959595u


#define NBOOT_RCS_ARRAY(NAME, SIZE) NAME[SIZE] __attribute__((section(".rcs." #NAME))) __USED


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
    uint32_t magic;                  /*! offset 0x00: Fixed 4-byte string of 'sbv3' without the trailing NULL */
    uint32_t formatVersion;          /*! offset 0x04: (major = 3, minor = 1); The format version determines the manifest (block0) size. */
    uint32_t flags;                  /*! offset 0x08: not defined yet, keep zero for future compatibility */
    uint32_t blockCount;             /*! offset 0x0C: Number of blocks not including the manifest (block0). */
    uint32_t blockSize;              /*! offset 0x10: Size in bytes of data block (repeated blockCount times for SB3 data stream). */
    nboot_timestamp_t timeStamp;     /*! offset 0x14: 64-bit value used as key derivation data. */
    uint32_t firmwareVersion;        /*! offset 0x1c: Version number of the included firmware */
    uint32_t imageTotalLength;       /*! offset 0x20: Total manifest length in bytes, including signatures etc. */
    uint32_t imageType;              /*! offset 0x24: image type and flags */
    uint32_t certificateBlockOffset; /*! offset 0x28: Offset from start of header block to the certificate block. */
    uint8_t description[16];         /*! offset 0x32: This field provides description of the file. It is an arbitrary
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

/**********************************************
 * TYPEDEFS
 **********************************************/
/*!
 * @brief Boolean type for the NBOOT functions
 *
 * This type defines boolean values used by NBOOT functions that are not easily disturbed by Fault Attacks
 *
 */
typedef enum _nboot_bool
{
    kNBOOT_TRUE                   = 0x3C5AC33Cu,    /*!< Value for TRUE.  */
    kNBOOT_TRUE256                = 0x3C5AC35Au,    /*!< Value for TRUE when P256 was used to sign the image.  */
    kNBOOT_TRUE384                = 0x3C5AC3A5u,    /*!< Value for TRUE when P384 was used to sign the image.  */
    kNBOOT_FALSE                  = 0x5AA55AA5u,    /*!< Value for FALSE. */
    kNBOOT_OperationAllowed       = 0x3c5a33ccU,
    kNBOOT_OperationDisallowed    = 0x5aa5cc33U,
} nboot_bool_t;

/*! @brief Data structure holding secure counter value used by nboot library */
typedef struct _nboot_secure_counter
{
    uint32_t sc;
    uint32_t scAp;
} nboot_secure_counter_t;

/** Type for nboot protected status codes */
typedef uint64_t nboot_status_protected_t;

/** Type for nboot status codes */
typedef uint32_t nboot_status_t;

typedef int romapi_status_t;

#define kStatusGroup_NBOOT_PUF (0x69u)
#define kStatusGroup_NBOOT_PRINCE (0x6au)

//! @brief Interface to memory operations for one region of memory.
typedef struct
{
    status_t (*init)(void);
    status_t (*read)(uint32_t address, uint32_t length, uint8_t *buffer);
    status_t (*write)(uint32_t address, uint32_t length, const uint8_t *buffer);
    status_t (*fill)(uint32_t address, uint32_t length, uint32_t pattern);
    status_t (*flush)(void);
    status_t (*erase)(uint32_t address, uint32_t length);
    status_t (*config)(uint32_t *buffer);
    status_t (*erase_all)(void);
} memory_region_interface_t;

//! @brief Structure of a memory map entry.
typedef struct
{
    uint32_t startAddress;
    uint32_t endAddress;
    uint32_t memoryProperty;
    uint32_t memoryId;
    const memory_region_interface_t *memoryInterface;
} memory_map_entry_t;


/**
 * \defgroup nbootStatusValues  This type defines status return values used by NBOOT functions that are not easily disturbed by Fault Attacks
 * @{
 */
#define kStatus_NBOOT_Success         ((nboot_status_t) 0x5A5A5A5Au)    /*!< Operation completed successfully. */
#define kStatus_NBOOT_Fail            ((nboot_status_t) 0x5A5AA5A5u)    /*!< Operation failed. */
#define kStatus_NBOOT_InvalidArgument ((nboot_status_t) 0x5A5AA5F0u)    /*!< Invalid argument passed to the function. */
#define kStatus_NBOOT_RequestTimeout  ((nboot_status_t) 0x5A5AA5E1u)    /*!< Operation timed out. */
#define kStatus_NBOOT_KeyNotLoaded    ((nboot_status_t) 0x5A5AA5E2u)    /*!< The requested key is not loaded. */
#define kStatus_NBOOT_AuthFail        ((nboot_status_t) 0x5A5AA5E4u)    /*!< Authentication failed. */
#define kStatus_NBOOT_OperationNotAvaialable        ((nboot_status_t) 0x5A5AA5E5u)    /*!< Operation not available on this HW. */
#define kStatus_NBOOT_KeyNotAvailable        ((nboot_status_t) 0x5A5AA5E6u)    /*!< Key is not avaialble. */
#define kStatus_NBOOT_IvCounterOverflow        ((nboot_status_t) 0x5A5AA5E7u)    /*!< Overflow of IV counter (PRINCE/IPED). */
#define kStatus_NBOOT_SelftestFail    ((nboot_status_t) 0x5A5AA5E8u)    /*!< FIPS self-test failure. */
#define kStatus_NBOOT_InvalidDataFormat    ((nboot_status_t) 0x5A5AA5E9u)    /*!< Invalid data format for example antipole */
#define kStatus_NBOOT_IskCertUserDataTooBig    ((nboot_status_t) 0x5A5AA5EAu)    /*!< Size of User data in ISK certificate is greater than 96 bytes */
#define kStatus_NBOOT_IskCertSignatureOffsetTooSmall ((nboot_status_t) 0x5A5AA5EBu)    /*!< Signature offset in ISK certificate is smaller than expected */
#define kStatus_NBOOT_MemcpyFail      ((nboot_status_t)0x5A5A845A)      /*!< Unexpected error detected during nboot_memcpy() */

#define NXPCLCSS_HASH_RTF_OUTPUT_SIZE ((size_t)32U) ///< Size of run-time fingerprint appended to the hash in @p pDigest in bytes, if #NXPCLCSS_HASH_RTF_OUTPUT_ENABLE was specified
#define NXPCLHASH_WA_SIZE_MAX (128u+64u)

/**@}*/

/*!
 * @brief NBOOT context type
 *
 * This type defines the NBOOT context
 *
 */
typedef struct _nboot_context
{
    uint32_t totalBlocks;   /*!< holds number of SB3 blocks. Initialized by nboot_sb3_load_header(). */
    uint32_t processData;   /*!< flag, initialized by nboot_sb3_load_header().
                               SB3 related flag set by NBOOT in case the nboot_sb3_load_block()
                               provides plain data to output buffer (for processing by ROM SB3 loader */
    uint32_t timeout;       /*!< timeout value for css operation. In case it is 0, infinite wait is performed */
    uint32_t keyinfo[NBOOT_KEYINFO_WORDLEN]; /*!< data for NBOOT key management. */
    uint32_t context[NBOOT_CONTEXT_WORDLEN]; /*!< work area for NBOOT lib. */
    uint32_t uuid[4]; /*!< holds UUID value from NMPA */
    uint32_t prngReadyFlag; /*!< flag, used by nboot_rng_generate_lq_random() to determine whether CSS is ready to generate rnd number */
    uint32_t multipartMacBuffer[1024/sizeof(uint32_t)];
    uint32_t oemShareValidFlag; /*!< flag, used during TP to determine whether valid oemShare was set by nboot_tp_isp_gen_oem_master_share() */
    uint32_t oemShare[4]; /*!< buffer to store OEM_SHARE computed by nxpCLTrustProv_nboot_isp_gen_oem_master_share() */
    nboot_secure_counter_t secureCounter; /*!< Secure counter used by nboot */
    uint32_t rtf[NXPCLCSS_HASH_RTF_OUTPUT_SIZE/sizeof(uint32_t)];
    uint32_t imageHash[48/sizeof(uint32_t)];
    uint32_t authStatus;
    nboot_bool_t disableProvisioningFirmwareNXP; /*!< Flag to disable execution of NXP signed provisioning Firmwares */
} nboot_context_t;

/*!
 * @brief NBOOT type for an ECC coordinate
 *
 * This type defines the NBOOT ECC coordinate type
 *
 */
typedef uint8_t nboot_ecc_coordinate_t[NBOOT_EC_COORDINATE_MAX_SIZE]; /*!ECC point coordinate, up to 384-bits. big endian. */

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
    uint32_t signatureOffset;            /*! Offset of signature in ISK block. */
    uint32_t constraints;                /*! Version number of signing certificate. */
    uint32_t iskFlags;                   /*! Reserved for definiton of ISK certificate flags. */
    nboot_ecdsa_public_key_t iskPubKey;  /*! Public key of signing certificate. Variable length; only used to determine start address*/
    nboot_ecdsa_public_key_t userData;   /*! Space for at lest one addition public key*/
    nboot_ecdsa_signature_t iskSign;     /*! ISK signature*/
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
    uint32_t magic;                         //!< magic number.
    uint32_t formatMajorMinorVersion;       //!< format major minor version
    uint32_t certBlockSize;                 //!< Size of the full certificate block
} nboot_certificate_header_block_t;

/*!
 * @brief NBOOT type for the certificate block
 *
 * This type defines the constant length part of an NBOOT image manifest
 *
 */
typedef struct _nboot_image_manifest_block
{
    uint32_t magic;                     //!< magic number
    uint32_t formatMajorMinorVersion;   //!< format major minor version
    uint32_t firmwareVersion;           //!< firmware versino number
    uint32_t imageManifestSize;         //!< Size of image manifest
    uint32_t flags;                     //!< image manifest flags
} nboot_image_manifest_block_t;

/*!
 * @brief NBOOT type for the certificate block
 *
 * This type defines the constant length part of an NBOOT certificate block
 *
 */
typedef struct _nboot_certificate_block
{
    nboot_certificate_header_block_t header;
    nboot_root_certificate_block_t rootCertBlock; /*! Details of selected root certificate (root certificate which will be used for ISK signing/SB3 header signing) */
    nboot_isk_block_t iskBlock;
} nboot_certificate_block_t;
/*!
 * @brief NBOOT type for the root key revocation
 *
 * This type defines the NBOOT root key revocation
 *
 */
#define kNBOOT_RootKey_Enabled (0xAAu)
#define kNBOOT_RootKey_Revoked (0xBBu)
/* any other value means the root key is revoked */
typedef uint32_t nboot_root_key_revocation_t;

/*!
 * @brief NBOOT type for the root key usage
 *
 * This type defines the NBOOT root key usage
 *
 */
#define kNBOOT_RootKeyUsage_DebugCA_ImageCA_FwCA_ImageKey_FwKey (0x0u)
#define kNBOOT_RootKeyUsage_DebugCA (0x1u)
#define kNBOOT_RootKeyUsage_ImageCA_FwCA (0x2u)
#define kNBOOT_RootKeyUsage_DebugCA_ImageCA_FwCA (0x3u)
#define kNBOOT_RootKeyUsage_ImageKey_FwKey (0x4u)
#define kNBOOT_RootKeyUsage_ImageKey (0x5u)
#define kNBOOT_RootKeyUsage_FwKey (0x6u)
#define kNBOOT_RootKeyUsage_Unused (0x7u)
/* any other value means the root key is not valid (treat as if revoked) */
typedef uint32_t nboot_root_key_usage_t;

/*! @brief Enumeration for SoC Lifecycle. */
#define nboot_lc_nxpBlank           (0xFFFF0000u)
#define nboot_lc_nxpDevNonSec       (0xFF0200FDu)
#define nboot_lc_nxpDevSec          (0xFF0100FEu)
#define nboot_lc_nxpProvisioned     (0xFFFE0001u)
#define nboot_lc_oemOpen            (0xFFFC0003u)
#define nboot_lc_oemSecureWorld     (0xFFF80007u)
#define nboot_lc_oemClosed          (0xFFF0000Fu)
#define nboot_lc_oemLocked          (0xFF3000CFu)
#define nboot_lc_oemFieldReturn     (0xFFE0001Fu)
#define nboot_lc_nxpFieldReturn     (0xFFC0003Fu)
#define nboot_lc_shredded           (0xFF0000FFu)
typedef uint32_t nboot_soc_lifecycle_t;

/*!
 * @brief NBOOT type specifying the elliptic curve to be used
 *
 * This type defines the elliptic curve type and length
 *
 */
#define kNBOOT_RootKey_Ecdsa_P256 (0x0000FE01u)
#define kNBOOT_RootKey_Ecdsa_P384 (0x0000FD02u)
typedef uint32_t nboot_root_key_type_and_length_t;

/*!
 * @brief NBOOT type for the root of trust parameters
 *
 * This type defines the NBOOT root of trust parameters
 *
 */
 #define kNBOOT_SocRkh_Size_Words_P384 (12u)
 #define kNBOOT_SocRkh_Size_Words_P256 (8u)
 typedef struct _nboot_rot_auth_parms
{
    /* trusted information originated from CFPA */
    nboot_root_key_revocation_t soc_rootKeyRevocation[NBOOT_ROOT_CERT_COUNT]; /*!< Provided by caller based on NVM information in CFPA: ROTKH_REVOKE */
    uint32_t soc_imageKeyRevocation; /*!< Provided by caller based on NVM information in CFPA: IMAGE_KEY_REVOKE */

    /* trusted information originated from CMPA */
    uint32_t soc_rkh[kNBOOT_SocRkh_Size_Words_P384]; /*!< Provided by caller based on NVM information in CMPA: ROTKH (hash of hashes) */
                          /*!< In case of kNBOOT_RootKey_Ecdsa_P384, sock_rkh[0..11] are used */
                          /*!< In case of kNBOOT_RootKey_Ecdsa_P256, sock_rkh[0..7] are used */

    uint32_t soc_numberOfRootKeys; /* unsigned int, between minimum = 1 and maximum = 4; */
    nboot_root_key_usage_t soc_rootKeyUsage[NBOOT_ROOT_CERT_COUNT]; /* CMPA */
    nboot_root_key_type_and_length_t soc_rootKeyTypeAndLength; /* static selection between ECDSA P-256 or ECDSA P-384 based root keys */

    /* trusted information originated from OTP fuses */
    nboot_soc_lifecycle_t soc_lifecycle;
} nboot_rot_auth_parms_t;

/*! @brief Data structure holding input arguments to POR secure boot (authentication) algorithm. Shall be read from SoC trusted NVM or SoC fuses. */
typedef struct _nboot_img_auth_ecdsa_parms
{
    /* trusted information originated from CFPA and NMPA */
    nboot_rot_auth_parms_t soc_RoTNVM;

    uint32_t soc_trustedFirmwareVersion; /*!< Provided by caller based on NVM information in CFPA: Secure_FW_Version */
} nboot_img_auth_ecdsa_parms_t;

/*!
 * @brief  manifest loading parameters
 *
 * This type defines the NBOOT SB3.1 manifest loading parameters
 *
 */typedef struct _nboot_sb3_load_manifest_parms
{
    nboot_rot_auth_parms_t soc_RoTNVM;      /*! trusted information originated from CFPA and NMPA */
    uint32_t soc_trustedFirmwareVersion;    /*!< Provided by caller based on NVM information in CFPA: Secure_FW_Version */
    uint8_t pckBlob[48];                    /*! CSSv2 protected blob with Part Common Key (PCK) */
} nboot_sb3_load_manifest_parms_t;

/*! @brief Data structure holding input arguments for CMAC authentication */
typedef struct _nboot_cmac_authenticate_parms
{
    uint32_t expectedMAC[4];  /*!< expected MAC result */
} nboot_cmac_authenticate_parms_t;

typedef struct
{
    romapi_status_t (*rng_generate_random)(uint8_t *output, size_t outputByteLen);
    nboot_status_t (*context_init)(nboot_context_t *context);
    nboot_status_t (*context_deinit)(nboot_context_t *context);
    nboot_status_protected_t (*sb3_load_manifest)(nboot_context_t *context,
                                                        uint32_t *manifest,
                                                        nboot_sb3_load_manifest_parms_t *parms);
    nboot_status_protected_t (*sb3_load_block)(nboot_context_t *context,
                                                     uint32_t *block);
    nboot_status_protected_t (*img_authenticate_ecdsa)(nboot_context_t *context,
                                                             uint8_t imageStartAddress[],
                                                             nboot_bool_t *isSignatureVerified,
                                                             nboot_img_auth_ecdsa_parms_t *parms);
} nboot_interface_t;


/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/* NBOOT ROM API function */
/* Specifically designed to be used in both secure and non-secure devices */
/*!
 * @brief Returns random number
 *
 * This function returns random number with specified length
 *
 * @param output                            [in] Pointer to random number
 * @param outputByteLen                     [in] length of generated random number in bytes
 *                                          Length has to be in range <1, 2^16>
 *
 * @retval kStatus_NBOOT_InvalidArgument    Invalid input parameters (Input poiters points to NULL or invalid length)
 * @retval kStatus_NBOOT_Success            Operation successfully finished
 * @retval kStatus_NBOOT_Fail               Error occured during operation
 *
 */
romapi_status_t romapi_rng_generate_random(uint8_t *output, size_t outputByteLen);

/*!
 * @brief Initialize nboot context data struct
 * @param context                           [in] Nboot context
 * @retval kStatus_NBOOT_Success            Operation successfully finished
 * @retval kStatus_NBOOT_Fail               Error occured during operation
 */
nboot_status_t nboot_context_init(nboot_context_t *context);

/*!
 * @brief Deinitialize nboot context data struct
 * @param context                           [in] Nboot context
 * @retval kStatus_NBOOT_Success            Operation successfully finished
 * @retval kStatus_NBOOT_Fail               Error occured during operation
 */
nboot_status_t nboot_context_deinit(nboot_context_t *context);

/*!
 * @brief Verify NBOOT SB3.1 manifest (header message)
 *
 * This function verifies  the NBOOT SB3.1 manifest, initializes the context and loads keys into the
 * CSS key store so that they can be used by nboot_sb3_load_block function
 * The NBOOT context has to be initialized by the function nboot_key_store_init before calling this function.
 *
 * @param   context                     [in] NBOOT context data struct.
 * @param   manifest                    [in] pointer to the input manifest buffer
 * @param   params                      [in] additional input parameters; refer to nboot_sb3_load_manifest_parms_t for details
 * @return A code-flow protected error code (see @ref nxpCsslFlowProtection)
 * @retval  kStatus_NBOOT_Success       Returned when the operation completed successfully
 * @retval  kStatus_NBOOT_Fail          Returned in case of error.
 */
nboot_status_protected_t nboot_sb3_load_manifest( nboot_context_t *context, uint32_t *manifest,
                                        nboot_sb3_load_manifest_parms_t  *parms);

/*!
 * @brief Verify NBOOT SB3.1 block
 *
 * This function verifies and decrypts an NBOOT SB3.1 block. Decryption is performed in-place.
 * The NBOOT context has to be initialized by the function nboot_key_store_init before calling this function.
 * To be more resistant against SPA, it is recommended that block is word aligned.
 *
 * @param   context                     [in] NBOOT context data struct.
 * @param   block                       [in] pointer to the input block
 * @return A code-flow protected error code (see @ref nxpCsslFlowProtection)
 * @retval  kStatus_NBOOT_Success       Returned when the operation completed successfully
 * @retval  kStatus_NBOOT_Fail          Returned in case of error.
 */
nboot_status_protected_t nboot_sb3_load_block(nboot_context_t *context, uint32_t *block );


/*!
 * @brief Secure boot image authentication
 *
 * This function authenticates image with asymmetric cryptography.
 * !NOTE! BootROM shall link this function to hidden ROM region !NOTE!
 *
 * @param context NBOOT context data struct (work area).
 * @param imageStartAddress Pointer to start of the image in memory.
 * @param isSignatureVerified Pointer to memory holding function call result.
 *             After the function returns, the value will be set to kNBOOT_TRUE when the image is authentic.
 *             Any other value means the authentication does not pass.
 * @param parms Pointer to a data structure in trusted memory, holding input parameters for the algorithm.
 *              The data structure shall be correctly filled before the function call.
 * @retval kStatus_NBOOT_Success Returned when the image is authentic.
 * @retval kStatus_NBOOT_Fail Returned in all other cases. Doesn't always mean invalid image,
 *                            it could also mean transient error caused by short time environmental conditions.
 */
nboot_status_protected_t nboot_img_authenticate_ecdsa(nboot_context_t *context,
                                                   uint8_t imageStartAddress[],
                                                   nboot_bool_t *isSignatureVerified,
                                                   nboot_img_auth_ecdsa_parms_t *parms);

#endif /* _FSL_ROMAPI_NBOOT_H_ */
