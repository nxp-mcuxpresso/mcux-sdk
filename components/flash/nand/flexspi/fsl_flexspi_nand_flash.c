/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fsl_nand_flash.h"
#include "fsl_flexspi_nand_flash.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static flexspi_mem_nand_handle_t flexspiMemHandle;
/*******************************************************************************
 * Code
 ******************************************************************************/
/* NAND Flash write enable */
static status_t flexspi_nand_write_enable(FLEXSPI_Type *base, flexspi_port_t port, uint32_t baseAddr)
{
    flexspi_transfer_t flashXfer;
    status_t status;

    /* Write enable */
    flashXfer.deviceAddress = baseAddr;
    flashXfer.port          = port;
    flashXfer.cmdType       = kFLEXSPI_Command;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NAND_CMD_LUT_SEQ_IDX_WRITEENABLE;

    status = FLEXSPI_TransferBlocking(base, &flashXfer);

    return status;
}

/* NAND Flash wait status busy */
static status_t flexspi_nand_wait_bus_busy(FLEXSPI_Type *base, flexspi_mem_nand_handle_t *handle, uint32_t baseAddr)
{
    /* Wait status ready. */
    bool isBusy = true;
    uint32_t readValue;
    status_t status;
    flexspi_transfer_t flashXfer;

    flashXfer.deviceAddress = baseAddr;
    flashXfer.port          = handle->port;
    flashXfer.cmdType       = kFLEXSPI_Read;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NAND_CMD_LUT_SEQ_IDX_READSTATUS;
    flashXfer.data          = &readValue;
    flashXfer.dataSize      = 1;

    do
    {
        status = FLEXSPI_TransferBlocking(base, &flashXfer);

        if (status != kStatus_Success)
        {
            return status;
        }

        if (handle->busyBitPolarity)
        {
            isBusy = (~readValue) & (1 << handle->busyOffset);
        }
        else
        {
            isBusy = readValue & (1 << handle->busyOffset);
        }

    } while (isBusy);

    return status;
}

static status_t flexspi_nand_check_ecc_status(FLEXSPI_Type *base,
                                              flexspi_mem_nand_handle_t *handle,
                                              uint32_t baseAddr,
                                              bool *isCheckPassed)
{
    flexspi_transfer_t flashXfer;
    status_t status;
    uint32_t eccStatus;

    /* Write neable */
    flashXfer.deviceAddress = baseAddr;
    flashXfer.port          = handle->port;
    flashXfer.cmdType       = kFLEXSPI_Read;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NAND_CMD_LUT_SEQ_IDX_READECCSTAT;
    flashXfer.data          = &eccStatus;
    flashXfer.dataSize      = 1;

    status = FLEXSPI_TransferBlocking(base, &flashXfer);
    if (status != kStatus_Success)
    {
        return status;
    }

    *isCheckPassed = false;

    if ((eccStatus & handle->eccStatusMask) != handle->eccFailureMask)
    {
        *isCheckPassed = true;
    }

    return status;
}

status_t flexspi_nand_unlock_all_blocks(FLEXSPI_Type *base, flexspi_port_t port)
{
    uint32_t temp;
    flexspi_transfer_t flashXfer;
    status_t status = kStatus_Success;

    /* unlock all blocks. */
    temp                    = 0;
    flashXfer.deviceAddress = 0;
    flashXfer.port          = port;
    flashXfer.cmdType       = kFLEXSPI_Write;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NAND_CMD_LUT_SEQ_IDX_UNLOCKALL;
    flashXfer.data          = &temp;
    flashXfer.dataSize      = 1;

    status = FLEXSPI_TransferBlocking(base, &flashXfer);

    return status;
}

/* Initialize NAND Flash device */
status_t Nand_Flash_Init(nand_config_t *config, nand_handle_t *handle)
{
    assert(config);
    assert(handle);

    flexspi_mem_config_t *memConfig = (flexspi_mem_config_t *)config->memControlConfig;

    /* Cleanup nand operation info */
    memset(handle, 0, sizeof(handle));

    handle->deviceSpecific           = &flexspiMemHandle;
    handle->driverBaseAddr           = config->driverBaseAddr;
    flexspiMemHandle.port            = memConfig->devicePort;
    flexspiMemHandle.busyOffset      = memConfig->busyOffset;
    flexspiMemHandle.busyBitPolarity = memConfig->busyBitPolarity;
    flexspiMemHandle.eccStatusMask   = memConfig->eccStatusMask;
    flexspiMemHandle.eccFailureMask  = memConfig->eccFailureMask;

    /* Configure flash settings according to serial flash feature. */
    FLEXSPI_SetFlashConfig((FLEXSPI_Type *)handle->driverBaseAddr, &(memConfig->deviceConfig), memConfig->devicePort);

    /* Fill default look up table */
    memset(memConfig->lookupTable, 0, sizeof(memConfig->lookupTable));
    /* Read Cache 1X */
    memConfig->lookupTable[4 * NAND_CMD_LUT_SEQ_IDX_READCACHE] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x03, kFLEXSPI_Command_CADDR_SDR, kFLEXSPI_1PAD, 0x10),
                               memConfig->lookupTable[4 * NAND_CMD_LUT_SEQ_IDX_READCACHE + 1] =
                                   FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DUMMY_SDR, kFLEXSPI_1PAD, 0x08,
                                                   kFLEXSPI_Command_READ_SDR, kFLEXSPI_1PAD, 0x80),

                               /* Read Status */
        memConfig->lookupTable[4 * NAND_CMD_LUT_SEQ_IDX_READSTATUS] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x0F, kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0xC0),
                               memConfig->lookupTable[4 * NAND_CMD_LUT_SEQ_IDX_READSTATUS + 1] =
                                   FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_SDR, kFLEXSPI_1PAD, 0x01,
                                                   kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),

                               /* Write Enable */
        memConfig->lookupTable[4 * NAND_CMD_LUT_SEQ_IDX_WRITEENABLE] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x06, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),

                               /* Erase block */
        memConfig->lookupTable[4 * NAND_CMD_LUT_SEQ_IDX_ERASEBLOCK] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0xD8, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, 0x18),

                               /* Page Program Load */
        memConfig->lookupTable[4 * NAND_CMD_LUT_SEQ_IDX_PROGRAMLOAD] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x02, kFLEXSPI_Command_CADDR_SDR, kFLEXSPI_1PAD, 0x10),
                               memConfig->lookupTable[4 * NAND_CMD_LUT_SEQ_IDX_PROGRAMLOAD + 1] =
                                   FLEXSPI_LUT_SEQ(kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_1PAD, 0x40,
                                                   kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),

                               /* Page Program Execute */
        memConfig->lookupTable[4 * NAND_CMD_LUT_SEQ_IDX_PROGRAMEXECUTE] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x10, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, 0x18),

                               /* Read Page */
        memConfig->lookupTable[4 * NAND_CMD_LUT_SEQ_IDX_READPAGE] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x13, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, 0x18),

                               /* Read ECC status */
        memConfig->lookupTable[4 * NAND_CMD_LUT_SEQ_IDX_READECCSTAT] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x0F, kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0xC0),
                               memConfig->lookupTable[4 * NAND_CMD_LUT_SEQ_IDX_READECCSTAT + 1] =
                                   FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_SDR, kFLEXSPI_1PAD, 0x01,
                                                   kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),

                               /* Read JEDEC ID */
        memConfig->lookupTable[4 * NAND_CMD_LUT_SEQ_IDX_READJEDECID] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x9F, kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0),
                               memConfig->lookupTable[4 * NAND_CMD_LUT_SEQ_IDX_READJEDECID + 1] =
                                   FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_SDR, kFLEXSPI_1PAD, 0x01,
                                                   kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),

                               /* Unlock all blocks */
        memConfig->lookupTable[4 * NAND_CMD_LUT_SEQ_IDX_UNLOCKALL] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x1F, kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0xA0),
                               memConfig->lookupTable[4 * NAND_CMD_LUT_SEQ_IDX_UNLOCKALL + 1] =
                                   FLEXSPI_LUT_SEQ(kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_1PAD, 0x00,
                                                   kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),

                               /* Update LUT table. */
        FLEXSPI_UpdateLUT((FLEXSPI_Type *)config->driverBaseAddr, 0, memConfig->lookupTable,
                          ARRAY_SIZE(memConfig->lookupTable));

    /* Do software reset. */
    FLEXSPI_SoftwareReset((FLEXSPI_Type *)config->driverBaseAddr);

    handle->bytesInPageDataArea  = memConfig->dataBytesPerPage;
    handle->bytesInPageSpareArea = memConfig->bytesInPageSpareArea;
    handle->pagesInBlock         = memConfig->pagesPerBlock;

    return kStatus_Success;
}

status_t Nand_Flash_Read_Page(nand_handle_t *handle, uint32_t pageIndex, uint8_t *buffer, uint32_t length)
{
    status_t status = kStatus_Success;

    flexspi_transfer_t flashXfer;
    uint32_t readAddress                 = pageIndex * (2 * handle->bytesInPageDataArea);
    flexspi_mem_nand_handle_t *memHandle = (flexspi_mem_nand_handle_t *)handle->deviceSpecific;
    flexspi_port_t port                  = memHandle->port;

    /* Read page. */
    flashXfer.deviceAddress = readAddress;
    flashXfer.port          = port;
    flashXfer.cmdType       = kFLEXSPI_Command;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NAND_CMD_LUT_SEQ_IDX_READPAGE;

    status = FLEXSPI_TransferBlocking((FLEXSPI_Type *)handle->driverBaseAddr, &flashXfer);

    if (status != kStatus_Success)
    {
        return status;
    }

    status = flexspi_nand_wait_bus_busy((FLEXSPI_Type *)handle->driverBaseAddr, memHandle, readAddress);
    if (status != kStatus_Success)
    {
        return status;
    }

    flashXfer.deviceAddress = readAddress;
    flashXfer.port          = port;
    flashXfer.cmdType       = kFLEXSPI_Read;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NAND_CMD_LUT_SEQ_IDX_READCACHE;
    flashXfer.data          = (uint32_t *)buffer;
    flashXfer.dataSize      = length;

    status = FLEXSPI_TransferBlocking((FLEXSPI_Type *)handle->driverBaseAddr, &flashXfer);

    if (status != kStatus_Success)
    {
        return status;
    }

    bool isCheckPassed;
    status =
        flexspi_nand_check_ecc_status((FLEXSPI_Type *)handle->driverBaseAddr, memHandle, readAddress, &isCheckPassed);

    if (status != kStatus_Success)
    {
        return status;
    }

    if (isCheckPassed == false)
    {
        status = kStatus_Fail;
    }

    return status;
}

status_t Nand_Flash_Read_Page_Partial(
    nand_handle_t *handle, uint32_t pageIndex, uint32_t offset_bytes, uint8_t *buffer, uint32_t length)
{
    status_t status = kStatus_Success;

    flexspi_transfer_t flashXfer;
    uint32_t readAddress                 = pageIndex * (2 * handle->bytesInPageDataArea);
    flexspi_mem_nand_handle_t *memHandle = (flexspi_mem_nand_handle_t *)handle->deviceSpecific;
    flexspi_port_t port                  = memHandle->port;

    /* Read page. */
    flashXfer.deviceAddress = readAddress;
    flashXfer.port          = port;
    flashXfer.cmdType       = kFLEXSPI_Command;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NAND_CMD_LUT_SEQ_IDX_READPAGE;

    status = FLEXSPI_TransferBlocking((FLEXSPI_Type *)handle->driverBaseAddr, &flashXfer);

    if (status != kStatus_Success)
    {
        return status;
    }

    status = flexspi_nand_wait_bus_busy((FLEXSPI_Type *)handle->driverBaseAddr, memHandle, readAddress);
    if (status != kStatus_Success)
    {
        return status;
    }

    flashXfer.deviceAddress = (readAddress + offset_bytes);
    flashXfer.port          = port;
    flashXfer.cmdType       = kFLEXSPI_Read;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NAND_CMD_LUT_SEQ_IDX_READCACHE;
    flashXfer.data          = (uint32_t *)buffer;
    flashXfer.dataSize      = length;

    status = FLEXSPI_TransferBlocking((FLEXSPI_Type *)handle->driverBaseAddr, &flashXfer);

    if (status != kStatus_Success)
    {
        return status;
    }

    bool isCheckPassed;
    status =
        flexspi_nand_check_ecc_status((FLEXSPI_Type *)handle->driverBaseAddr, memHandle, readAddress, &isCheckPassed);

    if (status != kStatus_Success)
    {
        return status;
    }

    if (isCheckPassed == false)
    {
        status = kStatus_Fail;
    }

    return status;
}
status_t Nand_Flash_Page_Program(nand_handle_t *handle, uint32_t pageIndex, const uint8_t *src, uint32_t length)
{
    status_t status;
    flexspi_transfer_t flashXfer;
    uint32_t address                     = pageIndex * (handle->bytesInPageDataArea + handle->bytesInPageSpareArea);
    flexspi_mem_nand_handle_t *memHandle = (flexspi_mem_nand_handle_t *)handle->deviceSpecific;
    flexspi_port_t port                  = memHandle->port;

    /* Write enable. */
    status = flexspi_nand_write_enable((FLEXSPI_Type *)handle->driverBaseAddr, port, address);
    if (status != kStatus_Success)
    {
        return status;
    }

    /* Send page load command. */
    flashXfer.deviceAddress = address;
    flashXfer.port          = port;
    flashXfer.cmdType       = kFLEXSPI_Write;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NAND_CMD_LUT_SEQ_IDX_PROGRAMLOAD;
    flashXfer.data          = (uint32_t *)src;
    flashXfer.dataSize      = length;

    status = FLEXSPI_TransferBlocking((FLEXSPI_Type *)handle->driverBaseAddr, &flashXfer);
    if (status != kStatus_Success)
    {
        return status;
    }

    /* Send program execute command. */
    flashXfer.deviceAddress = address;
    flashXfer.port          = port;
    flashXfer.cmdType       = kFLEXSPI_Command;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NAND_CMD_LUT_SEQ_IDX_PROGRAMEXECUTE;
    status                  = FLEXSPI_TransferBlocking((FLEXSPI_Type *)handle->driverBaseAddr, &flashXfer);
    if (status != kStatus_Success)
    {
        return status;
    }

    status = flexspi_nand_wait_bus_busy((FLEXSPI_Type *)handle->driverBaseAddr, memHandle, address);
    if (status != kStatus_Success)
    {
        return status;
    }

    bool isCheckPassed;
    status = flexspi_nand_check_ecc_status((FLEXSPI_Type *)handle->driverBaseAddr, memHandle, address, &isCheckPassed);

    if (status != kStatus_Success)
    {
        return status;
    }

    if (isCheckPassed == false)
    {
        status = kStatus_Fail;
    }

    return status;
}

status_t Nand_Flash_Erase_Block(nand_handle_t *handle, uint32_t blockIndex)
{
    flexspi_mem_nand_handle_t *memHandle = (flexspi_mem_nand_handle_t *)handle->deviceSpecific;
    flexspi_port_t port                  = memHandle->port;
    status_t status;
    flexspi_transfer_t flashXfer;

    uint32_t address = blockIndex * (handle->bytesInPageDataArea * 2) * handle->pagesInBlock;

    /* Unlock block */
    flexspi_nand_unlock_all_blocks((FLEXSPI_Type *)handle->driverBaseAddr, port);

    /* Write enable */
    status = flexspi_nand_write_enable((FLEXSPI_Type *)handle->driverBaseAddr, port, address);
    if (status != kStatus_Success)
    {
        return status;
    }

    /* Send erase command. */
    flashXfer.deviceAddress = address;
    flashXfer.port          = port;
    flashXfer.cmdType       = kFLEXSPI_Command;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NAND_CMD_LUT_SEQ_IDX_ERASEBLOCK;

    status = FLEXSPI_TransferBlocking((FLEXSPI_Type *)handle->driverBaseAddr, &flashXfer);
    if (status != kStatus_Success)
    {
        return status;
    }

    status = flexspi_nand_wait_bus_busy((FLEXSPI_Type *)handle->driverBaseAddr, memHandle, address);
    if (status != kStatus_Success)
    {
        return status;
    }

    return status;
}
