/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_ROMAPI_IAP_H_
#define FSL_ROMAPI_IAP_H_

#include <stdlib.h>
#include <stdint.h>
#include "fsl_common.h"
#include "fsl_romapi_nboot.h"
#include "fsl_sbloader_v3.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Bootloader status group numbers */
#define kStatusGroup_SBLoader (101UL)

/*! @brief SB loader status codes.*/
enum
{
    kStatusRomLdrSectionOverrun         = MAKE_STATUS(kStatusGroup_SBLoader, 0),
    kStatusRomLdrSignature              = MAKE_STATUS(kStatusGroup_SBLoader, 1),
    kStatusRomLdrSectionLength          = MAKE_STATUS(kStatusGroup_SBLoader, 2),
    kStatusRomLdrEOFReached             = MAKE_STATUS(kStatusGroup_SBLoader, 4),
    kStatusRomLdrChecksum               = MAKE_STATUS(kStatusGroup_SBLoader, 5),
    kStatusRomLdrCrc32Error             = MAKE_STATUS(kStatusGroup_SBLoader, 6),
    kStatusRomLdrUnknownCommand         = MAKE_STATUS(kStatusGroup_SBLoader, 7),
    kStatusRomLdrIdNotFound             = MAKE_STATUS(kStatusGroup_SBLoader, 8),
    kStatusRomLdrDataUnderrun           = MAKE_STATUS(kStatusGroup_SBLoader, 9),
    kStatusRomLdrJumpReturned           = MAKE_STATUS(kStatusGroup_SBLoader, 10),
    kStatusRomLdrCallFailed             = MAKE_STATUS(kStatusGroup_SBLoader, 11),
    kStatusRomLdrKeyNotFound            = MAKE_STATUS(kStatusGroup_SBLoader, 12),
    kStatusRomLdrSecureOnly             = MAKE_STATUS(kStatusGroup_SBLoader, 13),
    kStatusRomLdrResetReturned          = MAKE_STATUS(kStatusGroup_SBLoader, 14),
    kStatusRomLdrRollbackBlocked        = MAKE_STATUS(kStatusGroup_SBLoader, 15),
    kStatusRomLdrInvalidSectionMacCount = MAKE_STATUS(kStatusGroup_SBLoader, 16),
    kStatusRomLdrUnexpectedCommand      = MAKE_STATUS(kStatusGroup_SBLoader, 17),
    kStatusRomLdrBadSBKEK               = MAKE_STATUS(kStatusGroup_SBLoader, 18),
};

/*!@brief API initialization data structure*/
typedef struct kb_api_parameter_struct
{
    uint32_t allocStart;
    uint32_t allocSize;
} kp_api_init_param_t;

/*!@brief The API context structure */
typedef struct api_core_context
{
    uint32_t reserved0[166];
    ldr_Context_v3_t *sbloaderCtx;
    nboot_context_t *nbootCtx;
    uint32_t reserved1[5];
} api_core_context_t;

/*
 *!@brief Structure of version property.
 *
 */
typedef union StandardVersion
{
    struct
    {
        uint8_t bugfix; /*!< bugfix version [7:0]*/
        uint8_t minor;  /*!< minor version [15:8]*/
        uint8_t major;  /*!< major version [23:16]*/
        char name;      /*!< name [31:24]*/
    };
    uint32_t version;   /*!< combined version numbers*/
} standard_version_t;

/*! @brief IAP API Interface structure */
typedef struct iap_api_interface_struct
{
    standard_version_t version; /*!< IAP API version number. */
    status_t (*api_init)(api_core_context_t *coreCtx, const kp_api_init_param_t *param);
    status_t (*api_deinit)(api_core_context_t *coreCtx);
    const uint32_t reserved[8]; /*!< Reserved */
    status_t (*sbloader_init)(api_core_context_t *ctx);
    status_t (*sbloader_pump)(api_core_context_t *ctx, uint8_t *data, uint32_t length);
    status_t (*sbloader_finalize)(api_core_context_t *ctx);
} iap_api_interface_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!@brief Get IAP Driver version */
uint32_t iap_api_version(void);

/*!@brief Initialize the IAP API runtime environment*/
status_t iap_api_init(api_core_context_t *coreCtx, const kp_api_init_param_t *param);

/*!@brief Deinitialize the IAP API runtime environment*/
status_t iap_api_deinit(api_core_context_t *coreCtx);

/*!@brief Perform the Sbloader runtime environment initialization */
status_t iap_sbloader_init(api_core_context_t *ctx);

/*!@brief Handle the SB data stream */
status_t iap_sbloader_pump(api_core_context_t *ctx, uint8_t *data, uint32_t length);

/*!@brief Finish the sbloader handling */
status_t iap_sbloader_finalize(api_core_context_t *ctx);

#endif /* FSL_ROMAPI_IAP_H_ */
