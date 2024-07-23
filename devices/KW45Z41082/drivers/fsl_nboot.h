/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_NBOOT_H_
#define _FSL_NBOOT_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* sb3 file size definitions*/
#define NBOOT_SB3_MANIFEST_MAX_SIZE_IN_BYTES (0x328U)
#define NBOOT_SB3_BLOCK_MAX_SIZE_IN_BYTES    (0x134U)
#define NBOOT_SB3_CHUNK_SIZE_IN_BYTES        (256U)
#define NBOOT_SB3_IMAGE_ALIGNMENT            (16U)

/* debug authentication definitions */
#define NBOOT_DBG_AUTH_CHALLENGE_SIZE_P256         (104U) /*!< Challenge packet size for P256 */
#define NBOOT_DBG_AUTH_CHALLENGE_SIZE_P384         (104U) /*!< Challenge packet size for P384 */
#define NBOOT_DBG_AUTH_CHALLENGE_MAX_SIZE_IN_BYTES NBOOT_DBG_AUTH_CHALLENGE_SIZE_P384 /*!< Max challenge packet size*/
#define NBOOT_DBG_AUTH_RESPONSE_MAX_SIZE_P256      (444U) /*!< Maximal response packet size for P256 */
#define NBOOT_DBG_AUTH_RESPONSE_MAX_SIZE_P384      (636U) /*!< Maximal response packet size for P384 */
#define NBOOT_DBG_AUTH_RESPONSE_MAX_SIZE_IN_BYTES                  \
    NBOOT_DBG_AUTH_RESPONSE_MAX_SIZE_P384 /*!< Max response packet \
                                             size*/
#define NBOOT_DBG_AUTH_ANTI_POLE_BASE_MASK (0x0000FFFFU)

/* fault analysis request definitions */
#define NBOOT_FA_REQUEST_SIZE_IN_BYTES (784U)

/* size of internal nboot context */
#define NBOOT_CONTEXT_SIZE (156U)

/* definition of return values */
#define NBOOT_MEMCMP_EQUAL   (0x5AA53CC3U)
#define NBOOT_MEMCMP_UNEQUAL (0xA55AC33CU)

/* nboot fuse list */
#define NBOOT_FUSEID_TESTER_LOCK                      (0x00)
#define NBOOT_FUSEID_NXP_PROD_PRootHSMX_MK_SHARE_LOCK (0x01)
#define NBOOT_FUSEID_NXP_DIE_DRootR_MK_SHARE_LOCK     (0x02)
#define NBOOT_FUSEID_NXP_PROD_PrivFW_AUTH_PUK_LOCK    (0x03)
#define NBOOT_FUSEID_NXP_PROD_nPrivFW_AUTH_PUK_LOCK   (0x04)
#define NBOOT_FUSEID_CUST_PROD_OEMFW_AUTH_PUK_LOCK    (0x05)
#define NBOOT_FUSEID_CUST_PROD_OEMFW_ENC_SK_LOCK      (0x06)
#define NBOOT_FUSEID_OEM_Enablement_Token_LOCK        (0x07)
#define NBOOT_FUSEID_DCFG_CC_SOCU_L1_LOCK             (0x08)
#define NBOOT_FUSEID_DCFG_CC_SOCU_L2_LOCK             (0x09)
#define NBOOT_FUSEID_LIFECYCLE                        (0x0A)
#define NBOOT_FUSEID_DBG_EN_LOCK                      (0x0B)
#define NBOOT_FUSEID_DBG_AUTH_DIS                     (0x0C)
#define NBOOT_FUSEID_TZM_EN                           (0x0D)
#define NBOOT_FUSEID_DICE_EN                          (0x0E)
#define NBOOT_FUSEID_PUF_SETKEY_DIS                   (0x0F)
#define NBOOT_FUSEID_PUF_ENROLL_DIS                   (0x10)
#define NBOOT_FUSEID_SERIAL_DIS                       (0x11)
#define NBOOT_FUSEID_WAKEUP_DIS                       (0x12)
#define NBOOT_FUSEID_CUST_PROD_OEMFW_AUTH_PUK_REVOKE  (0x13)
#define NBOOT_FUSEID_SWD_ID                           (0x14)
#define NBOOT_FUSEID_DBG_AUTH_VU                      (0x15)
#define NBOOT_FUSEID_IMG_KEY_REVOKE                   (0x16)
#define NBOOT_FUSEID_PUFD_S3D_TRNGT                   (0x17)
#define NBOOT_FUSEID_SECURE_PHANTOM_CONFIG            (0x18)
#define NBOOT_FUSEID_ECID                             (0x19)
#define NBOOT_FUSEID_ROM_PATCH                        (0x1a)
#define NBOOT_FUSEID_NXP_PROD_PRootHSMX_MK_SHARE      (0x1b)
#define NBOOT_FUSEID_NXP_DIE_DRootR_MK_SHARE          (0x1c)
#define NBOOT_FUSEID_NXP_PROD_PrivFW_AUTH_PUK         (0x1d)
#define NBOOT_FUSEID_NXP_PROD_nPrivFW_AUTH_PUK        (0x1e)
#define NBOOT_FUSEID_CUST_PROD_OEMFW_AUTH_PUK         (0x1f)
#define NBOOT_FUSEID_CUST_PROD_OEMFW_ENC_SK           (0x20)
#define NBOOT_FUSEID_OEM_Enablement_Token             (0x21)
#define NBOOT_FUSEID_DCFG_CC_SOCU_L1                  (0x22)
#define NBOOT_FUSEID_DCFG_CC_SOCU_L2                  (0x23)
#define NBOOT_FUSEID_SOC_VER_CNT                      (0x24)
#define NBOOT_FUSEID_CM33_S_VER_CNT                   (0x25)
#define NBOOT_FUSEID_CM33_NS_VER_CNT                  (0x26)
#define NBOOT_FUSEID_RADIO_VER_CNT                    (0x27)
#define NBOOT_FUSEID_SNT_VER_CNT                      (0x28)
#define NBOOT_FUSEID_CM33_BOOTLOADER_VER_CNT          (0x29)
#define NBOOT_FUSEID_LAST                             (0x2a)

#define NBOOT_MAX_LIFECYCLE_VALUE (0xffU)

/* nboot list of open keys*/
#define NBOOT_NPX (0x80000007U)

/* nboot property list */
#define NBOOT_PROPERTY_ID_DICE_CDI        (0x10U)
#define NBOOT_PROPERTY_ID_IMAGE_HASH      (0x20U)
#define NBOOT_PROPERTY_ID_PSA_BOOT_SEED   (0x30U)
#define NBOOT_PROPERTY_ID_LAST_AUTH_STATE (0x40U)
#define NBOOT_PROPERTY_ID_SSS_ROM_VERSION (0x50U)
/* if no SSS fw loaded, returns 0xFFFFFFFF as 1st word, else loaded FW version, returns two words, 1st - version, 2nd -
 * commit id */
#define NBOOT_PROPERTY_ID_SSS_FW_VERSION   (0x51)
#define NBOOT_PROPERTY_ID_DTRK_ATTEST_PUBK (0x60U)
#define NBOOT_PROPERTY_ID_DTRK_ID_PUBK     (0x70U)
/* if NXP returns 0x0, if OEM1 returns 0xAABBCCDDu, OEM2 returns 0xaabbccddu*/
#define NBOOT_PROPERTY_NBU_NXP            (0x0U)
#define NBOOT_PROPERTY_NBU_OEM1           (0xAABBCCDDU)
#define NBOOT_PROPERTY_NBU_OEM2           (0xDDCCBBAAU)
#define NBOOT_PROPERTY_ID_RADIO_IMG_OWNER (0x80)
#define NBOOT_PROPERTY_ID_UUID            (0x90)

/* value indicating processing of internal sentinel FW*/
#define NBOOT_IGNORE_SB3_COMMANDS (0x4c4c4c4cU)
/* tag used for idication of new SB3 command*/
#define NBOOT_RANGE_SECTION_TAG (0x55aaaa55U)

/* nboot bits to be combined with image type on offsett 0x24 */
#define NBOOT_IMAGE_TYPE_MASK                     (0x3FU)
#define NBOOT_IMAGE_SUBTYPE_MASK                  (0xC0U)
#define NBOOT_IMAGE_TYPE_FULL_MASK                (NBOOT_IMAGE_TYPE_MASK | NBOOT_IMAGE_SUBTYPE_MASK)
#define NBOOT_IMAGE_TOTAL_SIZE_OFFSET_IN_WORDS    (0x8U)
#define NBOOT_IMAGE_TYPE_OFFSET_IN_WORDS          (0x9U)
#define NBOOT_IMAGE_CERTBLOCK_OFFSET_IN_WORDS     (0xAU)
#define NBOOT_IMAGE_CERTBLOCKSIZE_OFFSET_IN_BYTES (8U)
#define NBOOT_IMAGE_FWVERSION_OFFSET_IN_BYTES     (8U)

/* please validate that a is valid pointer before usage of macro*/
/* (a) is ponter to MBI start. */
#define NBOOT_GET_MBI_IMG_TYPE(a) ((((uint32_t *)a)[NBOOT_IMAGE_TYPE_OFFSET_IN_WORDS]) & NBOOT_IMAGE_TYPE_MASK)
/* (a) is ponter to MBI start. */
#define NBOOT_GET_MBI_IMG_SUBTYPE(a) ((((uint32_t *)a)[NBOOT_IMAGE_TYPE_OFFSET_IN_WORDS]) & NBOOT_IMAGE_SUBTYPE_MASK)
/* a) is ponter to MBI start. */
#define NBOOT_GET_MBI_IMG_FULLTYPE(a) ((((uint32_t *)a)[NBOOT_IMAGE_TYPE_OFFSET_IN_WORDS]) & NBOOT_IMAGE_TYPE_FULL_MASK)

/* nboot secured memory operations protected by secure counter*/
#define nboot_memcpy(ctx, dst, src, len) \
    nboot_s_memcpy((ctx), (dst), (src), (len), ((uint32_t)(dst) ^ (uint32_t)(src) ^ (len)))
#define nboot_memset(ctx, dst, value, len) \
    nboot_s_memset((ctx), (dst), (value), (len), ((uint32_t)(dst) ^ (value) ^ (len)))
#define nboot_memcmp(ctx, dst, src, len) \
    nboot_s_memcmp((ctx), (dst), (src), (len), ((uint32_t)(dst) ^ (uint32_t)(src) ^ (len)))
#define NBOOT_SC_S_MEMCPY (0x2d40U)
#define NBOOT_SC_S_MEMSET (0x2a33U)
#define NBOOT_SC_S_MEMCMP (0x2b44U)

typedef enum
{
    kSB3_COMMAND_none            = 0x0U,
    kSB3_COMMAND_erase           = 0x1U,
    kSB3_COMMAND_load            = 0x2U,
    kSB3_COMMAND_execute         = 0x3U,
    kSB3_COMMAND_call            = 0x4U,
    kSB3_COMMAND_programFuses    = 0x5U,
    kSB3_COMMAND_programIfr      = 0x6U,
    kSB3_COMMAND_loadCmac        = 0x7U,
    kSB3_COMMAND_copy            = 0x8U,
    kSB3_COMMAND_loadHashlocking = 0x9U,
    kSB3_COMMAND_loadKeyBlob     = 0xAU,
    kSB3_COMMAND_configMemory    = 0xBU,
    kSB3_COMMAND_fillMemory      = 0xCU,
    /*Add new values always before kSB3_COMMAND_end and update the value.*/
    kSB3_COMMAND_end = 0x4u
} nboot_sb3_command_t;

typedef enum
{
    kSECURE_TRUE                       = 0xc33cc33cU,
    kSECURE_FALSE                      = 0x5aa55aa5U,
    kSECURE_CALLPROTECT_SECURITY_FLAGS = 0xc33c5aa5U,
    kSECURE_CALLPROTECT_IS_APP_READY   = 0x5aa5c33cU,
    kSECURE_TRACKER_VERIFIED           = 0x55aacc33U,
} secure_bool_t;

typedef enum
{
    kNBOOT_TRUE                = 0x3C5AC33CU, /*!< Value for TRUE.  */
    kNBOOT_TRUE256             = 0x3C5AC35AU, /*!< Value for TRUE when P256 was used to sign the image.  */
    kNBOOT_TRUE384             = 0x3C5AC3A5U, /*!< Value for TRUE when P384 was used to sign the image.  */
    kNBOOT_FALSE               = 0x5AA55AA5U, /*!< Value for FALSE. */
    kNBOOT_OperationAllowed    = 0x3c5a33ccU,
    kNBOOT_OperationDisallowed = 0x5aa5cc33U,
} nboot_bool_t;

typedef enum
{
    kStatus_NBOOT_Success                = 0x5a5a5a5aU,
    kStatus_NBOOT_Fail                   = 0x5a5aa5a5U,
    kStatus_NBOOT_InvalidArgument        = 0x5a5aa501U,
    kStatus_NBOOT_RequestTimeout         = 0x5a5aa502U,
    kStatus_NBOOT_ResourceBusy           = 0x5a5aa503U,
    kStatus_NBOOT_RomPatchVerifyFail     = 0x5a5aa5a4U,
    kStatus_NBOOT_OperationNotAvaialable = 0x5a5aa5e5U,
    kStatus_NBOOT_MemcpyFail             = 0x5a5a845aU,
} nboot_status_t;

typedef enum
{
    kNBOOT_ImageTypePlain = 0x0,
    /* Image types with image header compatible with ARM-v7m and ARM-v8m vector
       table */
    kNBOOT_ImageTypePlainSigned       = 0x1U,
    kNBOOT_ImageTypePlainCrc          = 0x2U,
    kNBOOT_ImageTypeEncryptedSigned   = 0x3U,
    kNBOOT_ImageTypeXipPlainSigned    = 0x4U,
    kNBOOT_ImageTypeXipPlainCrc       = 0x5U,
    kNBOOT_ImageTypeSb3               = 0x6U,
    kNBOOT_ImageTypeSb3Nxp            = 0x7U,
    kNBOOT_ImageTypeXipPlainSignedNxp = 0x8U,
    /*Add new values always before kNBOOT_ImageTypeEnd and update the value.*/
    kNBOOT_ImageTypeEnd = 0x9u
} nboot_image_type_t;

/* SoC specific image subtypes definition */
typedef enum
{
    kNBOOT_ImageSubtypeDefault = 0x0U,
    kNBOOT_ImageSubtypeNbu     = 0x40U,
} nboot_image_subtype_t;

typedef struct
{
    uint32_t magic;                  /*! offset 0x00: Fixed 4-byte string of 'sbv3' without the
                                        trailing NULL */
    uint32_t formatVersion;          /*! offset 0x04: (major = 3, minor = 0); The format
                                        version determines the header block size. */
    uint32_t flags;                  /*! offset 0x08: not defined yet, keep zero for future
                                        compatibility */
    uint32_t blockCount;             /*! offset 0x0C: Number of blocks not including the
                                        header block. */
    uint32_t blockSize;              /*! offset 0x10: Size in bytes of all subsequent blocks. */
    uint32_t timeStamp[2];           /*! offset 0x14: 64-bit timestamp in microseconds since
                                        1-1-2000 00:00 when the image was created. */
    uint32_t firmwareVersion;        /*! offset 0x1c: Version number of the included
                                        firmware */
    uint32_t imageTotalLength;       /*! offset 0x20: total image length in bytes,
                                        including signatures etc. */
    uint32_t imageType;              /*! offset 0x24: image type and flags */
    uint32_t certificateBlockOffset; /*! offset 0x28: Offset from start of header
                                        block to the certificate block. This
                                        allows the signed image verification code
                                        to verify the signature over the header
                                        block. */
    uint8_t decription[16];          /*! text description of SB3.1 file */
} nboot_sb3_header_t;

/* SB3 commands strutures start */

/* basic SB3 command header */
typedef struct
{
    uint32_t tag;
    uint32_t startAddress;
    uint32_t length;
    uint32_t cmd;
} nboot_range_header_t;

/* basic SB3 command header data extension with memory ID */
typedef struct
{
    uint32_t memoryId;
    uint32_t _pad0;
    uint32_t _pad1;
    uint32_t _pad2;
} nboot_range_header_memory_data_t;

/* load key blob command header */
typedef struct
{
    uint32_t tag;
    uint16_t offset;
    uint16_t keyWrapId;
    uint32_t length;
    uint32_t cmd;
} nboot_load_key_range_header_t;

/* header of fill memory command */
typedef struct
{
    uint32_t tag;
    uint32_t memoryId;
    uint32_t address;
    uint32_t cmd;
} nboot_config_memory_range_header_t;

/* copy command additional data */
typedef struct
{
    uint32_t destinationAddress;
    uint32_t memoryIdFrom;
    uint32_t memoryIdDest;
    uint32_t _pad0;
} nboot_copy_command_data_t;

/* fillMemory command additional data */
typedef struct
{
    uint32_t pattern;
    uint32_t memortId;
    uint32_t _pad0;
    uint32_t _pad1;
} nboot_fill_command_data_t;
/* SB3 commands strutures end*/

/* nboot context structure with public and private part (context array)*/
typedef struct
{
    uint32_t blockSize;
    uint32_t totalBlocks;
    uint32_t processData;
    uint8_t context[NBOOT_CONTEXT_SIZE];
} nboot_context_t;

/* ROM API structure*/
typedef struct
{
    nboot_status_t (*nboot_context_init)(nboot_context_t *context);
    nboot_status_t (*nboot_context_free)(nboot_context_t *context);
    nboot_status_t (*nboot_sb3_load_manifest)(nboot_context_t *context, uint32_t *manifest);
    nboot_status_t (*nboot_sb3_load_block)(nboot_context_t *context, uint32_t *block);
    nboot_status_t (*nboot_sb3_load_s200_fw)(nboot_context_t *context, uint32_t *sb3Data);
    nboot_status_t (*nboot_img_authenticate_ecdsa)(nboot_context_t *context,
                                                   uint8_t imageStart[],
                                                   nboot_bool_t *isSignatureVerified);
    nboot_status_t (*nboot_rng_random)(nboot_context_t *context, void *buf, size_t bufLen);
    nboot_status_t (*nboot_rng_random_hq)(nboot_context_t *context, void *buf, size_t bufLen);
    nboot_status_t (*nboot_fuse_program)(nboot_context_t *context,
                                         uint32_t addr,
                                         uint32_t *data,
                                         uint32_t systemClockFrequencyMHz);
    nboot_status_t (*nboot_fuse_read)(nboot_context_t *context,
                                      uint32_t addr,
                                      uint32_t *data,
                                      uint32_t systemClockFrequencyMHz);
    nboot_status_t (*nboot_property_get)(nboot_context_t *context,
                                         uint32_t propertyId,
                                         uint8_t *destData,
                                         size_t *dataLen);
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
 * @param context Pointer to nboot_context_t structure.
 *
 * @retval #kStatus_NBOOT_Success Operation successfully finished.
 * @retval #kStatus_NBOOT_Fail Error occured during operation.
 */
nboot_status_t NBOOT_ContextInit(nboot_context_t *context);

/*!
 * @brief The function is used to deinitialize nboot context data structure.
 * Its contents are overwritten with random data so that any sensitive data does not remain in memory.
 *
 * @param context Pointer to nboot_context_t structure.

 * @retval #kStatus_NBOOT_Success Operation successfully finished.
 * @retval #kStatus_NBOOT_Fail Error occured during operation.
 */
nboot_status_t NBOOT_ContextFree(nboot_context_t *context);

/*!
 * @brief Verify NBOOT SB3.1 manifest (header message).
 * This function verifies  the NBOOT SB3.1 manifest, initializes the context and loads keys into the.
 * CSS key store so that they can be used by nboot_sb3_load_block function
 * The NBOOT context has to be initialized by the function nboot_context_init before calling this function.
 *
 * @param context NBOOT context data struct.
 * @param manifest pointer to the input manifest buffer
 *
 * @retval #kStatus_NBOOT_Success Returned when the operation completed successfully
 * @retval #kStatus_NBOOT_Fail Returned in case of error.
 */
nboot_status_t NBOOT_SB3LoaderManifest(nboot_context_t *context, uint32_t *manifest);

/*!
 * @brief Verify NBOOT SB3.1 block.
 *
 * This function verifies and decrypts an NBOOT SB3.1 block. Decryption is performed in-place.
 * The NBOOT context has to be initialized by the function nboot_context_init before calling this function.
 *
 * @param context NBOOT context data struct.
 * @param block pointer to the input block
 *
 * @retval #kStatus_NBOOT_Success Returned when the operation completed successfully
 * @retval #kStatus_NBOOT_Fail Returned in case of error.
 */
nboot_status_t NBOOT_SB3LoaderBlock(nboot_context_t *context, uint32_t *block);

/*!
 * @brief Authenticate and load Sentinel200 firmware at once
 *
 * This function verifies and decrypts SB3.1 file with S200 firmware. Decryption is performed to S200 RAM and firmware
 * automaticly started after sucessfull load. The NBOOT context has to be initialized by the function nboot_context_init
 * before calling this function.
 *
 * @param context NBOOT context data struct.
 * @param sb3Data pointer to the sb3.1 block wit s200 firmware
 *
 * @retval #kStatus_NBOOT_Success Returned when the operation completed successfully
 * @retval #kStatus_NBOOT_Fail Returned in case of error.
 */
nboot_status_t NBOOT_SB3LoaderS200Fw(nboot_context_t *context, uint32_t *sb3Data);

/*!
 * @brief Secure boot image authentication.
 *
 * This function authenticates image with asymmetric cryptography.
 *
 * @param context NBOOT context data struct (work area).
 * @param imageStart Pointer to start of the image in memory.
 * @param isSignatureVerified Pointer to memory holding function call result.
 *        After the function returns, the value will be set to kNBOOT_TRUE when the image is authentic.
 *        Any other value means the authentication does not pass.
 *
 * @retval #kStatus_NBOOT_Success Returned when the image is authentic.
 * @retval #kStatus_NBOOT_Fail Returned in all other cases. Doesn't always mean invalid image,
 *                            it could also mean transient error caused by short time environmental conditions.
 */
nboot_status_t NBOOT_ImgAuthenticateEcdsa(nboot_context_t *context,
                                          uint8_t imageStart[],
                                          nboot_bool_t *isSignatureVerified);

/*!
 * @brief Get random number in the highest quality, which is currently avaibale, no delay with TRNG initialization.
 *
 * @param context NBOOT context data struct (work area).
 * @param buf Pointer to buffer in memory to store random number.
 * @param bufLen Buffer length in number of bytes.
 *
 * @retval Please refer to nboot_status_t.
 */
nboot_status_t NBOOT_RngRandom(nboot_context_t *context, void *buf, size_t bufLen);

/*!
 * @brief Get high quality random number(s)
 *
 * @param context NBOOT context data struct (work area).
 * @param buf Pointer to buffer in memory to store random number.
 * @param bufLen Buffer length in number of bytes.
 *
 * @retval Please refer to nboot_status_t.
 */
nboot_status_t NBOOT_RngRandomHq(nboot_context_t *context, void *buf, size_t bufLen);

/*!
 * @brief Program a fuse word
 * Programs a fuse word at given address with new data.
 *
 * @param context NBOOT context data struct (work area).
 * @param addr Fuse index.
 * @param data Pointer to data expected to be programmed in fuse.
 * @param systemClockFrequencyMHz Boot frequency.
 *
 * @retval Please refer to nboot_status_t.
 */
nboot_status_t NBOOT_FuseProgram(nboot_context_t *context,
                                 uint32_t addr,
                                 uint32_t *data,
                                 uint32_t systemClockFrequencyMHz);

/*!
 * @brief Reads a fuse word
 * Reads a fuse word.
 *
 * @param context NBOOT context data struct (work area).
 * @param addr Fuse index.
 * @param data Pointer to data buffer expecting fuse contents after successful read.
 * @param systemClockFrequencyMHz Boot frequency.
 *
 * @retval Please refer to nboot_status_t.
 */
nboot_status_t NBOOT_FuseRead(nboot_context_t *context,
                              uint32_t addr,
                              uint32_t *data,
                              uint32_t systemClockFrequencyMHz);

/*!
 * @brief Read property
 * One of the important properties that can be read is the property that last
 * authentication of signed image container has succeeded.
 *
 * @param context NBOOT context data struct (work area).
 * @param propertyId Property ID must be supported by nboot.
 * @param destData Pointer to data buffer for storing returned contents.
 * @param dataLen Data buffer length.
 *
 * @retval Please refer to nboot_status_t.
 */
nboot_status_t NBOOT_PropertyGet(nboot_context_t *context, uint32_t propertyId, uint8_t *destData, size_t *dataLen);

#if defined(__cplusplus)
}
#endif

#endif /* _FSL_NBOOT_H_ */
