/*
 * Copyright 2018-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef FSL_K4_FLASH_H_
#define FSL_K4_FLASH_H_

#include "fsl_k4_controller.h"

/*!
 * @addtogroup flash_driver
 * @{
 */
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @name Flash version
 * @{
 */
/*! @brief Flash driver version for SDK*/
#define FSL_FLASH_DRIVER_VERSION (MAKE_VERSION(2, 1, 1)) /*!< Version 2.1.1. */

/*! @brief Flash driver version for ROM*/
enum _flash_driver_version_constants
{
    kFLASH_DriverVersionName   = 'F', /*!< Flash driver version name.*/
    kFLASH_DriverVersionMajor  = 2,   /*!< Major flash driver version.*/
    kFLASH_DriverVersionMinor  = 1,   /*!< Minor flash driver version.*/
    kFLASH_DriverVersionBugfix = 0    /*!< Bugfix for flash driver version.*/
};

/*!
 * @brief Enumeration for various flash properties.
 */
typedef enum _flash_property_tag
{
    kFLASH_PropertyPflash0SectorSize         = 0x00U, /*!< Pflash sector size property.*/
    kFLASH_PropertyPflash0TotalSize          = 0x01U, /*!< Pflash total size property.*/
    kFLASH_PropertyPflash0BlockSize          = 0x02U, /*!< Pflash block size property.*/
    kFLASH_PropertyPflash0BlockCount         = 0x03U, /*!< Pflash block count property.*/
    kFLASH_PropertyPflash0BlockBaseAddr      = 0x04U, /*!< Pflash block base address property.*/
    kFLASH_PropertyPflash0FacSupport         = 0x05U, /*!< Pflash fac support property.*/
    kFLASH_PropertyPflash0AccessSegmentSize  = 0x06U, /*!< Pflash access segment size property.*/
    kFLASH_PropertyPflash0AccessSegmentCount = 0x07U, /*!< Pflash access segment count property.*/

    kFLASH_PropertyPflash1SectorSize         = 0x10U, /*!< Pflash sector size property.*/
    kFLASH_PropertyPflash1TotalSize          = 0x11U, /*!< Pflash total size property.*/
    kFLASH_PropertyPflash1BlockSize          = 0x12U, /*!< Pflash block size property.*/
    kFLASH_PropertyPflash1BlockCount         = 0x13U, /*!< Pflash block count property.*/
    kFLASH_PropertyPflash1BlockBaseAddr      = 0x14U, /*!< Pflash block base address property.*/
    kFLASH_PropertyPflash1FacSupport         = 0x15U, /*!< Pflash fac support property.*/
    kFLASH_PropertyPflash1AccessSegmentSize  = 0x16U, /*!< Pflash access segment size property.*/
    kFLASH_PropertyPflash1AccessSegmentCount = 0x17U, /*!< Pflash access segment count property.*/

    kFLASH_PropertyFlexRamBlockBaseAddr = 0x20U, /*!< FlexRam block base address property.*/
    kFLASH_PropertyFlexRamTotalSize     = 0x21U, /*!< FlexRam total size property.*/
} flash_property_tag_t;

#define FLASH_ADDR_MASK 0xEFFFFFFFu

/*!
 * @name Flash API key
 * @{
 */
/*!
 * @brief Enumeration for Flash driver API keys.
 *
 * @note The resulting value is built with a byte order such that the string
 * being readable in expected order when viewed in a hex editor, if the value
 * is treated as a 32-bit little endian value.
 */
enum _flash_driver_api_keys
{
    kFLASH_ApiEraseKey = FOUR_CHAR_CODE('l', 'f', 'e', 'k') /*!< Key value used to validate all flash erase APIs.*/
};
/*! @} */

/*!
 * @brief Flash memory descriptor.
 */
typedef struct _flash_mem_descriptor
{
    uint32_t blockBase;  /*!< Base address of the flash block */
    uint32_t totalSize;  /*!< The size of the flash block. */
    uint32_t blockCount; /*!< A number of flash blocks. */
} flash_mem_desc_t;

typedef struct _flash_ifr_desc
{
    uint32_t pflashIfr0Start;
    uint32_t pflashIfr0MemSize;
} flash_ifr_desc_t;

typedef struct _msf1_config
{
    flash_mem_desc_t flashDesc;
    flash_ifr_desc_t ifrDesc;
} msf1_config_t;

/*! @brief Flash driver state information.
 *
 * An instance of this structure is allocated by the user of the flash driver and
 * passed into each of the driver APIs.
 */
typedef struct _flash_config
{
    msf1_config_t msf1Config[2];
} flash_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization
 * @{
 */

/*!
 * @brief Initializes the global flash properties structure members.
 *
 * This function checks and initializes the Flash module for the other Flash APIs.
 *
 * @param config Pointer to the storage for the driver runtime state.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_CommandFailure Run-time error during the command execution.
 * @retval #kStatus_FLASH_CommandNotSupported Flash API is not supported.
 */
status_t FLASH_Init(flash_config_t *config);

/*! @} */

/*!
 * @name Erasing
 * @{
 */

/*!
 * @brief Erases the flash sectors encompassed by parameters passed into function.
 */
status_t FLASH_Erase(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes, uint32_t key);

/*!
 * @brief Erases entire flash and ifr
 */
status_t FLASH_EraseAll(FMU_Type *base, uint32_t key);

/*! @} */

/*!
 * @name Programming
 * @{
 */

/*!
 * @brief Programs flash phrases with data at locations passed in through parameters.
 */
status_t FLASH_Program(flash_config_t *config, FMU_Type *base, uint32_t start, uint8_t *src, uint32_t lengthInBytes);

/*!
 * @brief Programs flash pages with data at locations passed in through parameters.
 */
status_t FLASH_ProgramPage(
    flash_config_t *config, FMU_Type *base, uint32_t start, uint8_t *src, uint32_t lengthInBytes);

/*! @} */

/*!
 * @name Verification
 * @{
 */

/*!
 * @brief Verify that the flash phrases are erased
 */
status_t FLASH_VerifyErasePhrase(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes);

/*!
 * @brief Verify that the flash pages are erased
 */
status_t FLASH_VerifyErasePage(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes);

/*!
 * @brief Verify that the flash sectors are erased
 */
status_t FLASH_VerifyEraseSector(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes);

/*!
 * @brief Verify that all flash and IFR space is erased
 */
status_t FLASH_VerifyEraseAll(FMU_Type *base);

/*!
 * @brief Verify that a flash block is erased
 */
status_t FLASH_VerifyEraseBlock(flash_config_t *config, FMU_Type *base, uint32_t blockaddr);

/*!
 * @brief Verify that the ifr phrases are erased
 */
status_t FLASH_VerifyEraseIFRPhrase(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes);

/*!
 * @brief Verify that the ifr pages are erased
 */
status_t FLASH_VerifyEraseIFRPage(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes);

/*!
 * @brief Verify that the ifr sectors are erased
 */
status_t FLASH_VerifyEraseIFRSector(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes);

/*! @} */

/*!
 * @name Properties
 * @{
 */

/*!
 * @brief Returns the desired flash property.
 */
status_t FLASH_GetProperty(flash_config_t *config, flash_property_tag_t whichProperty, uint32_t *value);

/*! @} */

/*!
 * @name Read (Main Array or IFR) Into MISR
 * @{
 */

/*!
 * @brief Read into MISR
 *
 * The Read into MISR operation generates a signature based on the contents of the selected
 * flash memory using an embedded MISR.
 */
status_t Read_Into_MISR(
    flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t ending, uint32_t *seed, uint32_t *signature);

/*!
 * @brief Read IFR into MISR
 *
 * The Read IFR into MISR operation generates a signature based on the contents of the
 * selected IFR space using an embedded MISR.
 */
status_t Read_IFR_Into_MISR(
    flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t ending, uint32_t *seed, uint32_t *signature);

/*! @} */

void flash_cache_disable(void);

void flash_cache_speculation_control(bool isPreProcess, FMU_Type *base);

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_K4_FLASH_H_ */
