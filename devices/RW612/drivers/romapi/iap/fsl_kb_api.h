/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_KB_API_H_
#define _FSL_KB_API_H_

#include <stdlib.h>
#include <stdint.h>
#include "fsl_common.h"

//! @brief Details of the operation to be performed by the ROM.
//
//! The #kRomAuthenticateImage operation requires the entire signed image to be
//! available to the application.
typedef enum
{
    kRomAuthenticateImage = 1, //!< Authenticate a signed image.
    kRomLoadImage         = 2, //!< Load SB file.
    kRomOperationCount    = 3,
} kb_operation_t;

//! @brief Memory region definition.
typedef struct
{
    uint32_t address;
    uint32_t length;
} kb_region_t;

//! @brief User-provided options passed into kb_init().
//!
//! The @a buffer field is a pointer to memory provided by the caller for use by
//! Kboot during execution of the operation. Minimum size is the size of each
//! certificate in the chain plus 432 bytes additional per certificate.
//!
//! The @a profile field is a mask that specifies which features are required in
//! the SB file or image being processed. This includes the minimum AES and RSA
//! key sizes. See the _kb_security_profile enum for profile mask constants.
//! The image being loaded or authenticated must match the profile or an error will
//! be returned.
//!
//! @a minBuildNumber is an optional field that can be used to prevent version
//! rollback. The API will check the build number of the image, and if it is less
//! than @a minBuildNumber will fail with an error.
//!
//! @a maxImageLength is used to verify the @a offsetToCertificateBlockHeaderInBytes
//! value at the beginning of a signed image. It should be set to the length of
//! the SB file. If verifying an image in flash, it can be set to the internal
//! flash size or a large number like 0x10000000.
//!
//! @a userRHK can optionally be used by the user to override the RHK in IFR. If
//! @a userRHK is not NULL, it points to a 32-byte array containing the SHA-256 of
//! the root certificate's RSA public key.
//!
//! The @a regions field points to an array of memory regions that the SB file being
//! loaded is allowed to access. If regions is NULL, then all memory is
//! accessible by the SB file. This feature is required to prevent a malicious
//! image from erasing good code or RAM contents while it is being loaded, only
//! for us to find that the image is inauthentic when we hit the end of the
//! section.
//!
//! @a overrideSBBootSectionID lets the caller override the default section of the
//! SB file that is processed during a #kKbootLoadSB operation. By default,
//! the section specified in the firstBootableSectionID field of the SB header
//! is loaded. If @a overrideSbBootSectionID is non-zero, then the section with
//! the given ID will be loaded instead.
//!
//! The @a userSBKEK field lets a user provide their own AES-256 key for unwrapping
//! keys in an SB file during the #kKbootLoadSB operation. @a userSBKEK should point
//! to a 32-byte AES-256 key. If @a userSBKEK is NULL then the IFR SBKEK will be used.
//! After kb_init() returns, the caller should zero out the data pointed to by @a
//! userSBKEK, as the API will have installed the key in the CAU3.

typedef struct
{
    uint32_t profile;
    uint32_t minBuildNumber;
    uint32_t overrideSBBootSectionID;
    uint32_t *userSBKEK;
    uint32_t regionCount;
    const kb_region_t *regions;
} kb_load_sb_t;

typedef struct
{
    uint32_t profile;
    uint32_t minBuildNumber;
    uint32_t maxImageLength;
    uint32_t *userRHK;
} kb_authenticate_t;

typedef struct
{
    uint32_t version; //!< Should be set to #kKbootApiVersion.
    uint8_t *buffer;  //!< Caller-provided buffer used by Kboot.
    uint32_t bufferLength;
    kb_operation_t op;
    union
    {
        //! Settings for #kKbootAuthenticate operation.
        kb_authenticate_t authenticate;
        //! Settings for #kKbootLoadSB operation.
        kb_load_sb_t loadSB;
    };
} kb_options_t;

#endif /* _FSL_KB_API_H_ */
