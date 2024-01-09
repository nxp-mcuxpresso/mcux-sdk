/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_ROMAPI_IAP_H_
#define _FSL_ROMAPI_IAP_H_

#include <stdlib.h>
#include <stdint.h>
#include "fsl_common.h"
#include "fsl_romapi_flexspi.h"
#include "fsl_romapi_nboot.h"
#include "fsl_kb_api.h"
#include "fsl_sbloader_v3.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define API_GROUP (1000UL)

//! @brief Memory Interface count
#define MEM_INTERFACE_COUNT (2U)

/*******************************************************************************
 *
 *      Memory Identifier definitions
 *
 * *****************************************************************************/
#define kMemoryID_Internal   (0x0U)      //!< Internal FLASH/RAM ID
#define kMemoryID_FlexspiNor (0x9U)      //!< FlexSPI NOR ID
#define MEMORY_GROUP(id)     ((id) >> 8) //!< Get the Memory group

/* Memory belongs to internal memory space (addressable) */
#define kMemoryGroup_Internal (0U)
/* Memory belongs to external memory space (non-addressable) */
#define kMemoryGroup_External (1U)

//! @brief Contiguous RAM region count
#define RAM_REGION_COUNT (2U)

//! @brief Contiguous FLEXSPINOR meomry count
#define FLEXSPINOR_REGION_COUNT (1U)

/*! @brief iap version for ROM*/
enum iap_version_constants
{
    kIAP_VersionName   = 'I', /*!< IAP version name.*/
    kIAP_VersionMajor  = 1,   /*!< Major IAP version.*/
    kIAP_VersionMinor  = 0,   /*!< Minor IAP version.*/
    kIAP_VersionBugfix = 0    /*!< Bugfix for IAP version.*/
};

//!@brief ROM API status definitions
enum
{
    //!< IAP API execution succedded
    kStatus_IAP_Success = kStatus_Success,
    //!< IAP API exeution failed
    kStatus_IAP_Fail = kStatus_Fail,
    //!< Invalid argument detected during API execution
    kStatus_IAP_InvalidArgument = MAKE_STATUS(API_GROUP, 1U),
    //!< The Heap size is not enough during API execution
    kStatus_IAP_OutOfMemory = MAKE_STATUS(API_GROUP, 2U),
    //!< The read memory operation is disallowed during API execution
    kStatus_IAP_ReadDisallowed = MAKE_STATUS(API_GROUP, 3U),
    //!< The FLASH region to be programmed is not empty
    kStatus_IAP_CumulativeWrite = MAKE_STATUS(API_GROUP, 4U),
    //!< Erase operation failed
    kStatus_IAP_EraseFailure = MAKE_STATUS(API_GROUP, 5U),
    //!< The specific command is not supported
    kStatus_IAP_CommandNotSupported = MAKE_STATUS(API_GROUP, 6U),
    //!< Memory access is disabled, typically occurred on the FLEXSPI NOR if it is not configured properly
    kStatus_IAP_MemoryAccessDisabled = MAKE_STATUS(API_GROUP, 7U),
};

typedef struct _arena_context
{
    uint32_t start_1;
    uint32_t end_1;
    uint32_t nextAddr;
} arena_context_t;

//!@brief Memory region information table
typedef struct mem_region
{
    uint32_t start_2;
    uint32_t end_2;
} mem_region_t;

//! @brief Memory Attribute Structure
typedef struct _mem_attribute
{
    uint32_t memId;
    uint32_t regionCount;
    mem_region_t *memRegions;
    void *context;
} mem_attribute_t;

//!@brief Memory region interface structure
typedef struct api_memory_region_interface
{
    status_t (*init)(mem_attribute_t *attr);
#if defined(ROM_API_HAS_FEATURE_MEM_READ) && (ROM_API_HAS_FEATURE_MEM_READ == 1u)
    status_t (*read)(mem_attribute_t *attr, uint32_t addr, uint32_t leth, uint8_t *buf);
#endif
    status_t (*write)(mem_attribute_t *attr, uint32_t addr, uint32_t len, const uint8_t *buf);
    status_t (*fill)(mem_attribute_t *attr, uint32_t addr, uint32_t len, uint32_t pattern);
    status_t (*flush)(mem_attribute_t *attr);
    status_t (*erase)(mem_attribute_t *attr, uint32_t addr, uint32_t const len);
    status_t (*config)(mem_attribute_t *attr, uint32_t *buf);
    status_t (*erase_all)(mem_attribute_t *attr);
    status_t (*alloc_ctx)(arena_context_t *ctx, mem_attribute_t *attr, void *miscParams);
} api_memory_region_interface_t;

//!@brief Memory entry data structure
typedef struct memory_map_entry
{
    mem_attribute_t *memoryAttribute;
    const api_memory_region_interface_t *memoryInterface;
} api_memory_map_entry_t;
//!@brief API initialization data structure
typedef struct kb_api_parameter_struct
{
    uint32_t allocStart;
    uint32_t allocSize;
} kp_api_init_param_t;

//!@brief Memory context structure
typedef struct memory_context_struct
{
    status_t (*flush)(mem_attribute_t *attr);
    mem_attribute_t *attr;
} mem_context_t;

typedef struct soc_memory_map_struct
{
    struct
    {
        uint32_t starts;
        uint32_t ends;
    } ramRegions[RAM_REGION_COUNT];
    struct
    {
        uint32_t starts_1;
        uint32_t ends_1;
    } flexspiNorRegions[FLEXSPINOR_REGION_COUNT];
} soc_mem_regions_t;

//!@brief The API context structure
typedef struct api_core_context
{
    soc_mem_regions_t memRegions;
    arena_context_t arenaCtx;
    flexspi_nor_config_t flexspinorCfg;
    mem_context_t memCtx;
    ldr_Context_v3_t *sbloaderCtx;
    nboot_context_t *nbootCtx;
    uint8_t *sharedBuf;
    api_memory_map_entry_t memEntries[MEM_INTERFACE_COUNT];
} api_core_context_t;

/*
 *!@brief Structure of version property.
 *
 */
typedef union StandardVersion
{
    struct
    {
        uint8_t bugfix; //!< bugfix version [7:0]
        uint8_t minor;  //!< minor version [15:8]
        uint8_t major;  //!< major version [23:16]
        char name;      //!< name [31:24]
    };
    uint32_t version; //!< combined version numbers
} standard_version_t;

//!@brief IAP API Interface structure
typedef struct iap_api_interface_struct
{
    standard_version_t version; //!< IAP API version number.
    status_t (*api_init)(api_core_context_t *coreCtx, const kp_api_init_param_t *param);
    status_t (*api_deinit)(api_core_context_t *coreCtx);
    status_t (*mem_init_api)(api_core_context_t *ctx);
    status_t (*mem_read)(api_core_context_t *ctx, uint32_t addr, uint32_t len, uint8_t *buf, uint32_t memoryId);
    status_t (*mem_write)(api_core_context_t *ctx, uint32_t addr, uint32_t len, const uint8_t *buf, uint32_t memoryId);
    status_t (*mem_fill)(api_core_context_t *ctx, uint32_t addr, uint32_t len, uint32_t pattern, uint32_t memoryId);
    status_t (*mem_flush)(api_core_context_t *ctx);
    status_t (*mem_erase)(api_core_context_t *ctx, uint32_t addr, uint32_t len, uint32_t memoryId);
    status_t (*mem_config)(api_core_context_t *ctx, uint32_t *buf, uint32_t memoryId);
    status_t (*mem_erase_all)(api_core_context_t *ctx, uint32_t memoryId);
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

//!@brief Get IAP Driver version
uint32_t iap_api_version(void);

//!@brief Initialize the IAP API runtime environment
status_t iap_api_init(api_core_context_t *coreCtx, const kp_api_init_param_t *param);

//!@brief Deinitialize the IAP API runtime environment
status_t iap_api_deinit(api_core_context_t *coreCtx);

//!@brief Intialize the memory interface of the IAP API
status_t iap_mem_init(api_core_context_t *coreCtx);

//!@brief Perform the memory write operation
status_t iap_mem_write(
    api_core_context_t *coreCtx, uint32_t start, uint32_t lengthInBytes, const uint8_t *buf, uint32_t memoryId);

//!@brief Perform the Memory read operation
status_t iap_mem_read(
    api_core_context_t *coreCtx, uint32_t start, uint32_t lengthInBytes, uint8_t *buf, uint32_t memoryId);

//!@brief Perform the Fill operation
status_t iap_mem_fill(
    api_core_context_t *coreCtx, uint32_t start, uint32_t lengthInBytes, uint32_t pattern, uint32_t memoryId);

//!@brief Perform the Memory erase operation
status_t iap_mem_erase(api_core_context_t *coreCtx, uint32_t start, uint32_t lengthInBytes, uint32_t memoryId);

//!@brief Perform the full Memory erase operation for specify MemoryID
status_t iap_mem_erase_all(api_core_context_t *coreCtx, uint32_t memoryId);

//!@brief Perform the Memory configuration operation
status_t iap_mem_config(api_core_context_t *coreCtx, uint32_t *config, uint32_t memoryId);

//!@brief Perform the Memory Flush operation
status_t iap_mem_flush(api_core_context_t *coreCtx);

//!@brief Perform the Sbloader runtime environment initialization
status_t iap_sbloader_init(api_core_context_t *ctx);

//!@brief Handle the SB data stream
status_t iap_sbloader_pump(api_core_context_t *ctx, uint8_t *data, uint32_t length);

//!@brief Finish the sbloader handling
status_t iap_sbloader_finalize(api_core_context_t *ctx);

#endif /* _FSL_ROMAPI_IAP_H_ */
