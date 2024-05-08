/*
 * Copyright 2018-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef FSL_K4_CONTROLLER_H_
#define FSL_K4_CONTROLLER_H_

#include "fsl_common.h"
#include "fsl_flash_adapter.h"
#include "fsl_flash_utilities.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*!
 * @name FLASH status
 * @{
 */
/*! @brief FLASH driver status group. */
#if defined(kStatusGroup_FlashDriver)
#define kStatusGroupGeneric     kStatusGroup_Generic
#define kStatusGroupFlashDriver kStatusGroup_FlashDriver
#elif defined(kStatusGroup_FLASH)
#define kStatusGroupGeneric     kStatusGroup_Generic
#define kStatusGroupFlashDriver kStatusGroup_FLASH
#else
#define kStatusGroupGeneric     0
#define kStatusGroupFlashDriver 1
#endif

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
    kStatus_FLASH_EccFaultDetected = MAKE_STATUS(kStatusGroupFlashDriver, 22), /*!< An ECC double fault occurred.*/
};
/*! @} */
/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Erasing
 * @{
 */

/*!
 * @brief Erases the flash sectors encompassed by parameters passed into function.
 *
 * This function erases the appropriate number of flash sectors based on the
 * desired start address and length.
 */
status_t FLASH_CMD_EraseSector(FMU_Type *base, uint32_t start);

/*!
 * @brief Erase all flash and IFR space
 */
status_t FLASH_CMD_EraseAll(FMU_Type *base);

/*! @} */

/*!
 * @name Programming
 * @{
 */

/*!
 * @brief Programs flash phrases with data at locations passed in through parameters.
 *
 * This function programs the flash memory with the desired data for a given
 * flash area as determined by the start address and the length.
 */
status_t FLASH_CMD_ProgramPhrase(FMU_Type *base, uint32_t start, uint32_t *src);

/*!
 * @brief Programs flash pages with data at locations passed in through parameters.
 *
 * This function programs the flash memory with the desired data for a given
 * flash area as determined by the start address and the length.
 */
status_t FLASH_CMD_ProgramPage(FMU_Type *base, uint32_t start, uint32_t *src);

/*! @} */

/*!
 * @name Verification
 * @{
 */

/*!
 * @brief Verify that the flash phrases are erased
 *
 * This function checks the appropriate number of flash phrases based on
 * the desired start address and length to check whether the flash is erased
 */
status_t FLASH_CMD_VerifyErasePhrase(FMU_Type *base, uint32_t start);

/*!
 * @brief Verify that the flash pages are erased
 *
 * This function checks the appropriate number of flash pages based on
 * the desired start address and length to check whether the flash is erased
 */
status_t FLASH_CMD_VerifyErasePage(FMU_Type *base, uint32_t start);

/*!
 * @brief Verify that the flash sectors are erased
 *
 * This function checks the appropriate number of flash sectors based on
 * the desired start address and length to check whether the flash is erased
 */
status_t FLASH_CMD_VerifyEraseSector(FMU_Type *base, uint32_t start);

/*!
 * @brief Verify that a flash block is erased
 */
status_t FLASH_CMD_VerifyEraseBlock(FMU_Type *base, uint32_t blockaddr);

/*!
 * @brief Verify that all flash and IFR space is erased
 */
status_t FLASH_CMD_VerifyEraseAll(FMU_Type *base);

/*!
 * @brief Verify that the ifr phrases are erased
 *
 * This function checks the appropriate number of ifr phrases based on
 * the desired start address and length to check whether the flash is erased
 */
status_t FLASH_CMD_VerifyEraseIFRPhrase(FMU_Type *base, uint32_t start);

/*!
 * @brief Verify that the ifr pages are erased
 *
 * This function checks the appropriate number of ifr pages based on
 * the desired start address and length to check whether the flash is erased
 */
status_t FLASH_CMD_VerifyEraseIFRPage(FMU_Type *base, uint32_t start);

/*!
 * @brief Verify that the ifr sectors are erased
 *
 * This function checks the appropriate number of ifr sectors based on
 * the desired start address and length to check whether the flash is erased
 */
status_t FLASH_CMD_VerifyEraseIFRSector(FMU_Type *base, uint32_t start);

/*! @} */

/*!
 * @name Read Into MISR
 * @{
 */

/*!
 * @brief Read into MISR
 *
 * The Read into MISR operation generates a signature based on the contents of the selected
 * flash memory using an embedded MISR.
 */
status_t FLASH_CMD_ReadIntoMISR(FMU_Type *base, uint32_t start, uint32_t ending, uint32_t *seed, uint32_t *signature);

/*!
 * @brief Read IFR into MISR
 *
 * The Read IFR into MISR operation generates a signature based on the contents of the
 * selected IFR space using an embedded MISR.
 */
status_t FLASH_CMD_ReadIFRIntoMISR(
    FMU_Type *base, uint32_t start, uint32_t ending, uint32_t *seed, uint32_t *signature);

/*! @} */

#if defined(__cplusplus)
}
#endif

#endif /* FSL_K4_CONTROLLER_H_ */
