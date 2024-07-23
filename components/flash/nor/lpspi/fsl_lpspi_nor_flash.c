/*
 * Copyright 2022, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <string.h>
#include "board.h"
#include "fsl_lpspi_nor_flash.h"
#include "fsl_nor_flash.h"
#include "fsl_lpspi_mem_adapter.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
extern uint32_t BOARD_GetLpspiClock(void);
extern uint32_t BOARD_GetNorFlashBaudrate(void);
extern LPSPI_Type *BOARD_GetLpspiForNorFlash(void);
/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Initialize NOR FLASH devices.
 *
 *  This function initialize NOR Flash controller and NOR Flash.
 *
 * @param config    NOR flash configuration.
 *        The "memControlConfig" and "driverBaseAddr" are controller specific structure.
 *        please set those two parameter with your Nand controller configuration structure type pointer.
 *        such as for SEMC:
 *
 *        spifi_mem_nor_config_t spifiNorconfig =
 *        {
 *            .....
 *        }
 *        nor_config_t config =
 *        {
 *            .memControlConfig = (void *)\&spifiNorconfig;
 *            .driverBaseAddr   = (void *)SPIFI0;
 *        }
 * @param handle    The NOR Flash handler.
 * @retval execution status
 */
status_t Nor_Flash_Init(nor_config_t *config, nor_handle_t *handle)
{
    assert(config);
    assert(handle);

    uint32_t baudRate   = BOARD_GetNorFlashBaudrate();
    status_t initStatus = kStatus_Fail;
    lpspi_memory_config_t *memConfig = (lpspi_memory_config_t *)(config->memControlConfig);

    handle->bytesInSectorSize = memConfig->bytesInSectorSize;
    handle->bytesInPageSize   = memConfig->bytesInPageSize;
    handle->driverBaseAddr    = BOARD_GetLpspiForNorFlash();

    do
    {
        uint32_t spiClock_Hz = BOARD_GetLpspiClock();

        spi_master_config_t spiMasterCfg;
        spiMasterCfg.baudRate  = baudRate;
        spiMasterCfg.clockFreq = spiClock_Hz;
        spiMasterCfg.whichPcs  = 0;
        status_t status        = LPSPI_MemInit(&spiMasterCfg, handle->driverBaseAddr);
        if (status != kStatus_Success)
        {
            break;
        }

        flash_id_t flashId;

        status = LPSPI_MemReadId(&flashId, handle->driverBaseAddr);
        if (status != kStatus_Success)
        {
            break;
        }

        initStatus = kStatus_Success;
    } while (false);

    return initStatus;
}

/*!
 * @brief Read page data from NOR Flash.
 *
 * @param handle    The NOR Flash handler.
 * @param address  NOR flash start address to read data from.
 * @param buffer  NOR flash buffer to read data to.
 * @param length  NOR flash read length.
 * @retval execution status
 */
status_t Nor_Flash_Read(nor_handle_t *handle, uint32_t address, uint8_t *buffer, uint32_t length)
{
    assert(handle);

    status_t readStatus = kStatus_Fail;

    LPSPI_Type *base = (LPSPI_Type *)handle->driverBaseAddr;

    assert(base);

    readStatus = LPSPI_MemRead(address, buffer, length, true, base);

    return readStatus;
}

/*!
 * @brief Initialize NOR FLASH devices.
 *
 *  This function initialize NOR Flash controller and NOR Flash.
 *
 * @param config    NOR flash configuration.
 * @param handle    The NOR Flash handler.
 * @retval execution status
 */
status_t Nor_Flash_Initialization(nor_config_t *config, nor_handle_t *handle)
{
    return Nor_Flash_Init(config, handle);
}

/*!
 * @brief Program page data to NOR Flash.
 *
 * @param handle    The NOR Flash handler.
 * @param address  The address to be programed.
 * @param buffer  The buffer to be programed to the page.
 * @retval execution status
 */
status_t Nor_Flash_Page_Program(nor_handle_t *handle, uint32_t address, uint8_t *buffer)
{
    assert(handle);

    LPSPI_Type *base = (LPSPI_Type *)handle->driverBaseAddr;

    assert(base);

    status_t status = kStatus_Fail;

    bool blocking = true;

    if (handle->deviceSpecific != NULL)
    {
        blocking = (*(bool *)(handle->deviceSpecific));
    }

    status = LPSPI_MemWritePage(address, buffer, handle->bytesInPageSize, blocking, base);

    return status;
}

/*!
 * @brief Program data to NOR Flash.
 *
 * @param handle    The NOR Flash handler.
 * @param address  The address to be programed.
 * @param buffer  The buffer to be programed to the page.
 * @param length  The data length to be programed to the page.
 * @retval execution status
 */
status_t Nor_Flash_Program(nor_handle_t *handle, uint32_t address, uint8_t *buffer, uint32_t length)
{
    assert(handle);

    LPSPI_Type *base = (LPSPI_Type *)handle->driverBaseAddr;

    assert(base);

    status_t writeStatus = kStatus_Fail;

    bool blocking = true;

    if (handle->deviceSpecific != NULL)
    {
        blocking = (*(bool *)(handle->deviceSpecific));
    }

    do
    {
        while ((address & 0xFFu) + length > 0xFFu)
        {
            uint32_t bytes = 0x100u - (address & 0xFFu);

            writeStatus = LPSPI_MemWritePage(address, buffer, bytes, blocking, base);
            length -= bytes;
            address += bytes;
            buffer += bytes;

            if (writeStatus != kStatus_Success)
            {
                break;
            }
        }

        writeStatus = LPSPI_MemWritePage(address, buffer, length, blocking, base);
        if (writeStatus != kStatus_Success)
        {
            break;
        }
        writeStatus = kStatus_Success;

    } while (false);

    return writeStatus;
}

/*!
 * @brief Erase page.
 *
 * @note Not all device support to erase page.

 * @param handle    The NOR Flash handler.
 * @param address   The start address to be erased.
 * @retval execution status
 */
status_t Nor_Flash_Erase_Page(nor_handle_t *handle, uint32_t address)
{
    assert(handle);

    LPSPI_Type *base = (LPSPI_Type *)handle->driverBaseAddr;

    assert(base);

    status_t status = kStatus_Fail;

    bool blocking = true;

    if (handle->deviceSpecific != NULL)
    {
        blocking = (*(bool *)(handle->deviceSpecific));
    }

    status = LPSPI_MemErase(address, kSize_ErasePage, blocking, base);

    return status;
}

/*!
 * @brief Erase sector.
 *
 * @param handle    The NOR Flash handler.
 * @param address   The start address to be erased.
 * @retval execution status
 */
status_t Nor_Flash_Erase_Sector(nor_handle_t *handle, uint32_t address)
{
    assert(handle);

    LPSPI_Type *base = (LPSPI_Type *)handle->driverBaseAddr;

    assert(base);

    eraseOptions_t tmpEraseOption = kSize_Erase4K;
    status_t status = kStatus_Fail;

    bool blocking = true;

    if (handle->deviceSpecific != NULL)
    {
        blocking = (*(bool *)(handle->deviceSpecific));
    }

    switch (handle->bytesInSectorSize)
    {
        case 4096UL:
        {
            tmpEraseOption = kSize_Erase4K;
            break;
        }
        case 32768UL:
        {
            tmpEraseOption = kSize_Erase32K;
            break;
        }
        case 65536UL:
        {
            tmpEraseOption = kSize_Erase64K;
            break;
        }
        default:
        {
            return kStatus_OutOfRange;
        }
    }
    status = LPSPI_MemErase(address, tmpEraseOption, blocking, base);

    return status;
}

/*!
 * @brief Erase 4K block.
 *
 * @param handle    The NOR Flash handler.
 * @param address   The start address to be erased.
 * @retval execution status
 */
status_t Nor_Flash_Erase_Block_4K(nor_handle_t *handle, uint32_t address)
{
    assert(handle);

    LPSPI_Type *base = (LPSPI_Type *)handle->driverBaseAddr;

    assert(base);

    status_t status = kStatus_Fail;

    bool blocking = true;

    if (handle->deviceSpecific != NULL)
    {
        blocking = (*(bool *)(handle->deviceSpecific));
    }

    status = LPSPI_MemErase(address, kSize_Erase4K, blocking, base);

    return status;
}

/*!
 * @brief Erase 32K block.
 *
 * @param handle    The NOR Flash handler.
 * @param address   The start address to be erased.
 * @retval execution status
 */
status_t Nor_Flash_Erase_Block_32K(nor_handle_t *handle, uint32_t address)
{
    assert(handle);

    LPSPI_Type *base = (LPSPI_Type *)handle->driverBaseAddr;

    assert(base);

    status_t status = kStatus_Fail;

    bool blocking = true;

    if (handle->deviceSpecific != NULL)
    {
        blocking = (*(bool *)(handle->deviceSpecific));
    }

    status = LPSPI_MemErase(address, kSize_Erase32K, blocking, base);

    return status;
}

/*!
 * @brief Erase 64K block.
 *
 * @param handle    The NOR Flash handler.
 * @param address   The start address to be erased.
 * @retval execution status
 */
status_t Nor_Flash_Erase_Block_64K(nor_handle_t *handle, uint32_t address)
{
    assert(handle);

    LPSPI_Type *base = (LPSPI_Type *)handle->driverBaseAddr;

    assert(base);

    status_t status = kStatus_Fail;

    bool blocking = true;

    if (handle->deviceSpecific != NULL)
    {
        blocking = (*(bool *)(handle->deviceSpecific));
    }

    status = LPSPI_MemErase(address, kSize_Erase64K, blocking, base);

    return status;
}

/*!
 * @brief Erase block.
 *
 * @param handle    The NOR Flash handler.
 * @param address   The start address to be erased.
 * @retval execution status
 */
status_t Nor_Flash_Erase_Block(nor_handle_t *handle, uint32_t address)
{
    assert(handle);

    status_t status = kStatus_Fail;

    status = Nor_Flash_Erase_Block_4K(handle, address);

    return status;
}

/*!
 * @brief Erase flash.
 *
 * @param handle    The NOR Flash handler.
 * @param address   The start address to be erased.
 * @param size_Byte The size to be erased.
 * @retval execution status
 */
status_t Nor_Flash_Erase(nor_handle_t *handle, uint32_t address, uint32_t size_Byte)
{
    assert(handle);

    status_t status  = kStatus_Fail;
    LPSPI_Type *base = (LPSPI_Type *)handle->driverBaseAddr;

    assert((size_Byte == 256U) || (size_Byte == 4096U) || (size_Byte == 32768U) || (size_Byte == 65536U));
    assert(base);

    bool blocking = true;

    if (handle->deviceSpecific != NULL)
    {
        blocking = (*(bool *)(handle->deviceSpecific));
    }

    switch (size_Byte)
    {
        case 256U:
            status = LPSPI_MemErase(address, kSize_ErasePage, blocking, base);
            break;
        case 4096U:
            status = LPSPI_MemErase(address, kSize_Erase4K, blocking, base);
            break;
        case 32768U:
            status = LPSPI_MemErase(address, kSize_Erase32K, blocking, base);
            break;
        case 65536U:
            status = LPSPI_MemErase(address, kSize_Erase64K, blocking, base);
            break;
        default:
            /* All the cases have been listed above, the default clause should not be reached. */
            assert(false);
            break;
    }

    return status;
}

/*!
 * @brief Erase Chip NOR Flash .
 *
 * @param handle    The NOR Flash handler.
 * @retval execution status
 */
status_t Nor_Flash_Erase_Chip(nor_handle_t *handle)
{
    assert(handle);

    status_t status = kStatus_Fail;

    LPSPI_Type *base = (LPSPI_Type *)handle->driverBaseAddr;

    assert(base);

    bool blocking = true;

    if (handle->deviceSpecific != NULL)
    {
        blocking = (*(bool *)(handle->deviceSpecific));
    }

    status = LPSPI_MemErase(0x0, kSize_EraseAll, blocking, base);

    return status;
}

/*!
 * @brief Deinitialize NOR FLASH devices.
 *
 * @param handle    The NOR Flash handler.
 * @retval execution status
 */
status_t Nor_Flash_DeInit(nor_handle_t *handle)
{
    assert(handle);

    status_t status = kStatus_Fail;

    LPSPI_Type *base = (LPSPI_Type *)handle->driverBaseAddr;

    assert(base);

    status = LPSPI_MemDeinit(base);

    return status;
}

/*!
 * @brief  Get the busy status of the NOR Flash.
 *
 * @param handle    The NOR Flash handler.
 * @retval execution status
 */
status_t Nor_Flash_Is_Busy(nor_handle_t *handle, bool *isBusy)
{
    assert(handle);

    status_t status = kStatus_Fail;

    LPSPI_Type *base = (LPSPI_Type *)handle->driverBaseAddr;

    assert(base);

    status = LPSPI_MemIsBusy(base, isBusy);

    return status;
}

status_t Nor_Flash_Enter_Lowpower(nor_handle_t *handle)
{
    status_t status = kStatus_Fail;
    bool busy;

    assert(handle);

    do
    {
        /* Make sure the flash is not busy */
        (void)Nor_Flash_Is_Busy(handle, &busy);
    } while (busy == true);

    status = Nor_Flash_DeInit(handle);

    return status;
}

status_t Nor_Flash_Exit_Lowpower(nor_handle_t *handle)
{
    assert(handle);

    uint32_t baudRate   = BOARD_GetNorFlashBaudrate();
    status_t initStatus = kStatus_Fail;

    handle->bytesInSectorSize = 256U;
    handle->bytesInPageSize   = 256U;
    handle->driverBaseAddr    = BOARD_GetLpspiForNorFlash();

    do
    {
        uint32_t spiClock_Hz = BOARD_GetLpspiClock();

        spi_master_config_t spiMasterCfg;
        spiMasterCfg.baudRate  = baudRate;
        spiMasterCfg.clockFreq = spiClock_Hz;
        spiMasterCfg.whichPcs  = 0;
        status_t status        = LPSPI_MemInit(&spiMasterCfg, handle->driverBaseAddr);
        if (status != kStatus_Success)
        {
            break;
        }

        initStatus = kStatus_Success;
    } while (false);

    return initStatus;
}
