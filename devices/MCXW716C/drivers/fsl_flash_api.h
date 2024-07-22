/*
 * Copyright 2021,2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_FLASH_API_H_
#define _FSL_FLASH_API_H_

#include "fsl_common.h"

/*!
 * @addtogroup flash_driver_api
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
#define FSL_FLASH_DRIVER_VERSION (MAKE_VERSION(1, 2, 0)) /*!< Version 1.2.0. */
/*@}*/

/*! @brief Constructs the four character code for the Flash driver API key. */
#if !defined(FOUR_CHAR_CODE)
#define FOUR_CHAR_CODE(a, b, c, d) (((d) << 24) | ((c) << 16) | ((b) << 8) | ((a)))
#endif

/*! @brief Alignment(down) utility. */
#if !defined(ALIGN_DOWN)
#define ALIGN_DOWN(x, a) (((uint32_t)(x)) & ~((uint32_t)(a)-1u))
#endif

/*! @brief Flash driver version for ROM*/
enum _flash_driver_version_constants
{
    kFLASH_DriverVersionName   = 'F', /*!< Flash driver version name.*/
    kFLASH_DriverVersionMajor  = 1,   /*!< Major flash driver version.*/
    kFLASH_DriverVersionMinor  = 1,   /*!< Minor flash driver version.*/
    kFLASH_DriverVersionBugfix = 0    /*!< Bugfix for flash driver version.*/
};

/*!
 * @name FLASH status
 * @{
 */
/*! @brief FLASH driver status group. */
enum
{
    kStatusGroupGeneric     = 0,
    kStatusGroupFlashDriver = 1,
};

/*!
 * @brief FLASH driver status codes.
 */
enum
{
    kStatus_FLASH_Success         = MAKE_STATUS(kStatusGroupGeneric, 0),     /*!< API is executed successfully*/
    kStatus_FLASH_InvalidArgument = MAKE_STATUS(kStatusGroupGeneric, 4),     /*!< Invalid argument*/
    kStatus_FLASH_SizeError       = MAKE_STATUS(kStatusGroupFlashDriver, 0), /*!< Error size*/
    kStatus_FLASH_AlignmentError =
        MAKE_STATUS(kStatusGroupFlashDriver, 1), /*!< Parameter is not aligned with the specified baseline*/
    kStatus_FLASH_AddressError = MAKE_STATUS(kStatusGroupFlashDriver, 2), /*!< Address is out of range */
    kStatus_FLASH_AccessError =
        MAKE_STATUS(kStatusGroupFlashDriver, 3), /*!< Invalid instruction codes and out-of bound addresses */
    kStatus_FLASH_ProtectionViolation = MAKE_STATUS(
        kStatusGroupFlashDriver, 4), /*!< The program/erase operation is requested to execute on protected areas */
    kStatus_FLASH_CommandFailure =
        MAKE_STATUS(kStatusGroupFlashDriver, 5), /*!< Run-time error during command execution. */
    kStatus_FLASH_UnknownProperty = MAKE_STATUS(kStatusGroupFlashDriver, 6), /*!< Unknown property.*/
    kStatus_FLASH_EraseKeyError   = MAKE_STATUS(kStatusGroupFlashDriver, 7), /*!< API erase key is invalid.*/
    kStatus_FLASH_RegionExecuteOnly =
        MAKE_STATUS(kStatusGroupFlashDriver, 8), /*!< The current region is execute-only.*/
    kStatus_FLASH_ExecuteInRamFunctionNotReady =
        MAKE_STATUS(kStatusGroupFlashDriver, 9), /*!< Execute-in-RAM function is not available.*/
    kStatus_FLASH_PartitionStatusUpdateFailure =
        MAKE_STATUS(kStatusGroupFlashDriver, 10), /*!< Failed to update partition status.*/
    kStatus_FLASH_SetFlexramAsEepromError =
        MAKE_STATUS(kStatusGroupFlashDriver, 11), /*!< Failed to set FlexRAM as EEPROM.*/
    kStatus_FLASH_RecoverFlexramAsRamError =
        MAKE_STATUS(kStatusGroupFlashDriver, 12), /*!< Failed to recover FlexRAM as RAM.*/
    kStatus_FLASH_SetFlexramAsRamError = MAKE_STATUS(kStatusGroupFlashDriver, 13), /*!< Failed to set FlexRAM as RAM.*/
    kStatus_FLASH_RecoverFlexramAsEepromError =
        MAKE_STATUS(kStatusGroupFlashDriver, 14), /*!< Failed to recover FlexRAM as EEPROM.*/
    kStatus_FLASH_CommandNotSupported = MAKE_STATUS(kStatusGroupFlashDriver, 15), /*!< Flash API is not supported.*/
    kStatus_FLASH_SwapSystemNotInUninitialized =
        MAKE_STATUS(kStatusGroupFlashDriver, 16), /*!< Swap system is not in an uninitialzed state.*/
    kStatus_FLASH_SwapIndicatorAddressError =
        MAKE_STATUS(kStatusGroupFlashDriver, 17), /*!< The swap indicator address is invalid.*/
    kStatus_FLASH_ReadOnlyProperty = MAKE_STATUS(kStatusGroupFlashDriver, 18), /*!< The flash property is read-only.*/
    kStatus_FLASH_InvalidPropertyValue =
        MAKE_STATUS(kStatusGroupFlashDriver, 19), /*!< The flash property value is out of range.*/
    kStatus_FLASH_InvalidSpeculationOption =
        MAKE_STATUS(kStatusGroupFlashDriver, 20), /*!< The option of flash prefetch speculation is invalid.*/
    kStatus_FLASH_CommandAborOption =
        MAKE_STATUS(kStatusGroupFlashDriver, 21), /*!< The option of flash prefetch speculation is invalid.*/
};
/*@}*/

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
/*@}*/

/*!
 * @brief Flash memory descriptor.
 */
typedef struct _flash_mem_descriptor
{
    uint32_t blockBase;  /*!< A base address of the flash block */
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

/*! @brief Interface for the flash driver.*/
typedef struct FlashDriverInterface
{
    status_t (*flash_init)(flash_config_t *config);
    status_t (*flash_erase_sector)(
        flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes, uint32_t key);
    status_t (*flash_program_phrase)(
        flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t *src, uint32_t lengthInBytes);
    status_t (*flash_program_page)(
        flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t *src, uint32_t lengthInBytes);
    status_t (*flash_verify_erase_all)(FMU_Type *base);
    status_t *reserved;
    status_t (*flash_verify_erase_phrase)(flash_config_t *config,
                                          FMU_Type *base,
                                          uint32_t start,
                                          uint32_t lengthInBytes);
    status_t (*flash_verify_erase_page)(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes);
    status_t (*flash_verify_erase_sector)(flash_config_t *config,
                                          FMU_Type *base,
                                          uint32_t start,
                                          uint32_t lengthInBytes);
    status_t (*flash_read_into_misr)(
        flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t end, uint32_t *seed, uint32_t *signature);
    status_t (*flash_get_property)(flash_config_t *config, flash_property_tag_t whichProperty, uint32_t *value);
    // IFR driver
    status_t (*ifr_verify_erase_phrase)(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes);
    status_t (*ifr_verify_erase_page)(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes);
    status_t (*ifr_verify_erase_sector)(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes);
    status_t (*ifr_read_into_misr)(
        flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t end, uint32_t *seed, uint32_t *signature);
} flash_driver_interface_t;

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

/*@}*/

/*!
 * @name Erasing
 * @{
 */

/*!
 * @brief Erases the Dflash sectors encompassed by parameters passed into function.
 *
 * This function erases the appropriate number of flash sectors based on the
 * desired start address and length.
 *
 * @param config The pointer to the storage for the driver runtime state.
 * @param start The start address of the desired flash memory to be erased,
 *         Must be phrase-aligned.
 * @param lengthInBytes The length, given in bytes to be erased, It is recommended
 *        that the length is aligned with the sector.
 * @param base FMU base address.
 * @param key The value used to validate all flash erase APIs.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_AlignmentError The parameter is not aligned with the specified baseline.
 * @retval #kStatus_FLASH_AddressError The address is out of range.
 * @retval #kStatus_FLASH_EraseKeyError The API erase key is invalid.
 * @retval #kStatus_FLASH_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FLASH_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FLASH_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FLASH_CommandFailure Run-time error during the command execution.
 */
status_t FLASH_Erase(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes, uint32_t key);

/*@}*/

/*!
 * @name Programming
 * @{
 */

/*!
 * @brief Programs flash phrases with data at locations passed in through parameters.
 *
 * This function programs the flash memory with the desired data for a given
 * flash area as determined by the start address and the length.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param base FMU base address.
 * @param start The start address of the desired flash memory to be programmed,
 *        Must be phrase-aligned.
 * @param src A pointer to the source buffer of data that is to be programmed
 *            into the flash.
 * @param lengthInBytes The length, given in bytes must be phrase-aligned.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_AlignmentError Parameter is not aligned with the specified baseline.
 * @retval #kStatus_FLASH_AddressError Address is out of range.
 * @retval #kStatus_FLASH_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FLASH_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FLASH_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FLASH_CommandFailure Run-time error during the command execution.
 */
status_t FLASH_Program(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t *src, uint32_t lengthInBytes);

/*!
 * @brief Programs flash pages with data at locations passed in through parameters.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param base FMU base address.
 * @param start The start address of the desired flash memory to be programmed. Must be
 *              page-aligned.
 * @param src A pointer to the source buffer of data that is to be programmed
 *            into the flash.
 * @param lengthInBytes The length, given in bytes (not words or long-words),
 *                      to be programmed. Must be page-aligned.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_AlignmentError Parameter is not aligned with the specified baseline.
 * @retval #kStatus_FLASH_AddressError Address is out of range.
 * @retval #kStatus_FLASH_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FLASH_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FLASH_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FLASH_CommandFailure Run-time error during the command execution.
 */
status_t FLASH_ProgramPage(
    flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t *src, uint32_t lengthInBytes);

/*@}*/

/*!
 * @name Verification
 * @{
 */
/*!
 * @brief Verify that all flash and IFR space is erased
 *
 * @param base FMU base address.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FLASH_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FLASH_CommandFailure Run-time error during the command execution.
 * @retval #kStatus_FLASH_CommandAborOption
 */
status_t FLASH_VerifyEraseAll(FMU_Type *base);

/*!
 * @brief Verify that the flash phrases are erased
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param base FMU base address.
 * @param start The start address of the desired flash memory to be verified.
 *        The start address need to be phrase-aligned.
 * @param lengthInBytes The length, It is recommended that the length is aligned with the phrase.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_AlignmentError Parameter is not aligned with specified baseline.
 * @retval #kStatus_FLASH_AddressError Address is out of range.
 * @retval #kStatus_FLASH_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FLASH_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FLASH_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FLASH_CommandFailure Run-time error during the command execution.
 */
status_t FLASH_VerifyErasePhrase(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes);

/*!
 * @brief Verify that the flash pages are erased
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param base FMU base address.
 * @param start The start address of the desired flash memory to be verified.
 *        The start address must be page-aligned.
 * @param lengthInBytes The length, It is recommended that the length is aligned with the page.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_AlignmentError Parameter is not aligned with specified baseline.
 * @retval #kStatus_FLASH_AddressError Address is out of range.
 * @retval #kStatus_FLASH_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FLASH_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FLASH_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FLASH_CommandFailure Run-time error during the command execution.
 */
status_t FLASH_VerifyErasePage(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes);

/*!
 * @brief Verify that the flash sector are erased
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param base FMU base address.
 * @param start The start address of the desired flash memory to be verified.
 *        The start address need to be sector-aligned.
 * @param lengthInBytes The length, It is recommended that the length is aligned with the page.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_AlignmentError Parameter is not aligned with specified baseline.
 * @retval #kStatus_FLASH_AddressError Address is out of range.
 * @retval #kStatus_FLASH_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FLASH_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FLASH_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FLASH_CommandFailure Run-time error during the command execution.
 */
status_t FLASH_VerifyEraseSector(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes);

/*!
 * @brief Verify that the ifr phrases are erased
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param base FMU base address.
 * @param start The start address of the desired ifr memory to be verified.
 *        The start address need to be phrase-aligned.
 * @param lengthInBytes The length, it is recommended that the length is aligned with the phrase.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_AlignmentError Parameter is not aligned with specified baseline.
 * @retval #kStatus_FLASH_AddressError Address is out of range.
 * @retval #kStatus_FLASH_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FLASH_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FLASH_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FLASH_CommandFailure Run-time error during the command execution.
 */
status_t FLASH_VerifyEraseIFRPhrase(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes);

/*!
 * @brief Verify that the ifr pages are erased
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param base FMU base address.
 * @param start The start address of the desired ifr memory to be verified.
 *        The start address need to be page-aligned.
 * @param lengthInBytes The length, it is recommended that the length is aligned with the page.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_AlignmentError Parameter is not aligned with specified baseline.
 * @retval #kStatus_FLASH_AddressError Address is out of range.
 * @retval #kStatus_FLASH_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FLASH_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FLASH_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FLASH_CommandFailure Run-time error during the command execution.
 */
status_t FLASH_VerifyEraseIFRPage(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes);

/*!
 * @brief Verify that the ifr sectors are erased
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param base FMU base address.
 * @param start The start address of the desired ifr memory to be verified.
 *        The start address need to be sector-aligned.
 * @param lengthInBytes The length, it is recommended that the length is aligned with the page.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_AlignmentError Parameter is not aligned with specified baseline.
 * @retval #kStatus_FLASH_AddressError Address is out of range.
 * @retval #kStatus_FLASH_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FLASH_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FLASH_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FLASH_CommandFailure Run-time error during the command execution.
 */
status_t FLASH_VerifyEraseIFRSector(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes);

/*@}*/

/*!
 * @name Properties
 * @{
 */

/*!
 * @brief Returns the desired flash property.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param whichProperty The desired property from the list of properties in
 *        enum flash_property_tag_t
 * @param value A pointer to the value returned for the desired flash property.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_UnknownProperty An unknown property tag.
 */
status_t FLASH_GetProperty(flash_config_t *config, flash_property_tag_t whichProperty, uint32_t *value);

/*@}*/

/*!
 * @name Read (Main Array or IFR) Into MISR
 * @{
 */
/*!
 * @brief Read into MISR
 *
 * The Read into MISR operation generates a signature based on the contents of the selected
 * flash memory using an embedded MISR.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param base FMU base address.
 * @param start The start address of the desired flash memory to be programed.
 *        The start address need to be page-aligned.
 * @param endAddr The end address of the desired flash memory to be programed.
 * @param seed A pointer to the source buffer of seed that is to be programmed
 *            into the signature register .
 * @param signature Returns the generated signature frome the flash specified area.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_UnknownProperty An unknown property tag.
 * @retval #kStatus_FLASH_CommandFailure Run-time error during command execution.
 * @retval #kStatus_FLASH_AccessError Invalid instruction codes and out-of bound addresses
 * @retval #kStatus_FLASH_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FLASH_CommandAborOption The option of flash prefetch speculation is invalid.
 */
status_t FLASH_ReadIntoMisr(
    flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t endAddr, uint32_t *seed, uint32_t *signature);

/*!
 * @brief Read IFR into MISR
 *
 * The Read IFR into MISR operation generates a signature based on the contents of the
 * selected IFR space using an embedded MISR.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param base FMU base address.
 * @param start The start address of the desired ifr memory to be programed.
 *        The start address need to be page-aligned.
 * @param endAddr The end address of the desired ifr memory to be programed.
 * @param seed A pointer to the source buffer of seed that is to be programmed
 *            into the signature register .
 * @param signature Returns the generated signature frome the ifr specified area.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FLASH_UnknownProperty An unknown property tag.
 * @retval #kStatus_FLASH_CommandFailure Run-time error during command execution.
 * @retval #kStatus_FLASH_AccessError Invalid instruction codes and out-of bound addresses.
 * @retval #kStatus_FLASH_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FLASH_CommandAborOption The option of flash prefetch speculation is invalid.
 */
status_t FLASH_ReadIFRIntoMisr(
    flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t endAddr, uint32_t *seed, uint32_t *signature);

/*@}*/

/*!
 * @brief FLASH_CACHE_Disable
 *
 * FLASH_CACHE_Disable disables the cache of FMU0, but not radio FMU
 */
void FLASH_CACHE_Disable(void);

/*!
 * @brief FLASH_CACHE_Clear
 *
 * FLASH_CACHE_Clear clears cache of FMU0, but not radio FMU
 *
 * @param isPreProcess, set to true if it's before program/erase execution,
          set ti false if it's after the program/erase execution
 */
void FLASH_CACHE_Clear(bool isPreProcess);

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_FLASH_API_H_ */
