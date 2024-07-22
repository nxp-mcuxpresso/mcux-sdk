/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _API_LPSPI_FLASH_H_
#define _API_LPSPI_FLASH_H_

#include "fsl_common.h"

/*!
 * @addtogroup lpspi_flash
 * @{
 */
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define kROM_StatusGroup_LPSPI 4 /*!< ROM Group number for LPSPI status codes. */

/*! @brief Status for the LPSPI driver.*/
enum
{
    kStatus_ROM_LPSPI_Busy       = MAKE_STATUS(kROM_StatusGroup_LPSPI, 0), /*!< LPSPI transfer is busy.*/
    kStatus_ROM_LPSPI_Error      = MAKE_STATUS(kROM_StatusGroup_LPSPI, 1), /*!< LPSPI driver error. */
    kStatus_ROM_LPSPI_Idle       = MAKE_STATUS(kROM_StatusGroup_LPSPI, 2), /*!< LPSPI is idle.*/
    kStatus_ROM_LPSPI_OutOfRange = MAKE_STATUS(kROM_StatusGroup_LPSPI, 3)  /*!< LPSPI transfer out Of range. */
};

/*! @brief The type of Read eeprom command.*/
enum
{
    EepormCmd_GeneralRead = false, /*!< Use the general Read command to read eeprom.*/
    EepormCmd_FastRead    = true,  /*!< Use Fast Read command to read data from eeprom.*/
};

/*! @brief The length, given in bytes to be erased.*/
typedef enum
{
    kSize_ErasePage = 0x1, /*!< A page data of eeprom will be erased.*/
    kSize_Erase4K   = 0x2, /*!< 4*1024 bytes data of eeprom will be erased.*/
    kSize_Erase32K  = 0x3,
    kSize_Erase64K  = 0x4,
    kSize_EraseAll  = 0x5,
} eraseOptions_t;

//! @brief Interface for the external flash driver via SPI NOR/EEPROM
typedef struct LpspiFlashDriverInterface
{
    status_t (*spi_eeprom_init)(uint32_t baudRate);
    status_t (*spi_eeprom_read)(uint8_t *dest, uint32_t length, uint32_t address, bool requestFastRead);
    status_t (*spi_eeprom_write)(uint8_t *data, uint32_t length, uint32_t address);
    status_t (*spi_eeprom_erase)(uint32_t address, eraseOptions_t option);
    void (*spi_eeprom_finalize)(void);
} lpspi_flash_driver_interface_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initialize SPI NOR/EEPROM
 *
 * @param baudRate Config baudrate for SPI.
 *
 * @retval #kStatus_Fail EEPROM initialization failed.
 * @retval #kStatus_InvalidArgument Invalid input parameter.
 * @retval #kStatus_ROM_LPSPI_Busy LPSPI transfer is busy.
 * @retval #kStatus_Success The eeprom is initialized successfully.
 */
status_t SPI_EepromInit(uint32_t baudRate);

/*!
 * @brief Read data via SPI NOR/EEPROM
 *
 * @param dest A pointer to the buffer of data that is to be read from eeprom.
 * @param length The length, given in bytes to be read.
 * @param address The start address of the desired eeprom memory to be read.
 * @param requestFastRead The type of Read eeprom command.
 *        FALSE: Use the general Read command to read eeprom
 *        TRUE: Use Fast Read command to read data from eeprom.
 *
 * @retval #kStatus_Fail Failed to read data from eeprom.
 * @retval #kStatus_Success Read data from eeprom successfully.
 * @retval #kStatus_InvalidArgument Invalid input parameter.
 * @retval #kStatus_ROM_LPSPI_Busy LPSPI transfer is busy.
 */
status_t SPI_EepromRead(uint8_t *dest, uint32_t length, uint32_t address, bool requestFastRead);

/*!
 * @brief Write data via SPI NOR/EEPROM
 *
 * @param data A pointer to the source buffer of data that is to be programmed into the eeprom.
 * @param length The length, given in bytes to be programmed.
 * @param address The start address of the desired eeprom memory to be programed.
 *
 * @retval #kStatus_Fail Failed to write data to eeprom.
 * @retval #kStatus_Success Successfully write data to eeprom.
 * @retval #kStatus_InvalidArgument Invalid input parameter.
 * @retval #kStatus_ROM_LPSPI_Busy LPSPI transfer is busy.
 */
status_t SPI_EepromWrite(uint8_t *data, uint32_t length, uint32_t address);

/*!
 * @brief Erase data via SPI NOR/EEPROM
 *
 * @param address The start address of the desired eeprom memory to be erased.
 * @param option The length, given in bytes to be erased.
 *
 * @retval #kStatus_Fail Failed to erase data frome the eeprom.
 * @retval #kStatus_Success Erase data from eeprom successfully.
 * @retval #kStatus_InvalidArgument Invalid input parameter.
 * @retval #kStatus_ROM_LPSPI_Busy LPSPI transfer is busy.
 */
status_t SPI_EepromErase(uint32_t address, eraseOptions_t option);

/*! @brief De-initialize LPSPI
 */
void SPI_EepromFinalize(void);

#if defined(__cplusplus)
}
#endif

/*!
 *@}
 */

#endif /* _API_LPSPI_FLASH_H_ */
