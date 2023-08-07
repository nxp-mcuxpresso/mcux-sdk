/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "board.h"
#include "fsl_common.h"
#include "fsl_device_registers.h"
#include "fsl_lpspi_mem_adapter.h"
#if (FSL_FEATURE_SOC_LPSPI_COUNT > 0)
#include "fsl_lpspi.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
enum
{
    kFlashCmd_ReadId          = 0x9F,
    kFlashCmd_ReadStatus      = 0x05,
    kFlashCmd_ReadMemory24Bit = 0x03,
    kFlashCmd_FastRead        = 0x0B,

    kFlashCmd_WriteEnable  = 0x06,
    kFlashCmd_WriteDisable = 0x04,
    kFlashCmd_PageProgram  = 0x02,

    kFlashCmd_ErasePage = 0x81,
    kFlashCmd_Erase4K   = 0x20,
    kFlashCmd_Erase32K  = 0x52,
    kFlashCmd_Erase64K  = 0xD8,
    kFlashCmd_EraseAll  = 0x60,
};

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
extern void BOARD_LpspiPcsPinControl(bool isSelected);
extern void BOARD_LpspiIomuxConfig(spi_pin_mode_t pinMode);

static status_t LPSPI_MemWaitBusy(LPSPI_Type *base);

/*******************************************************************************
 * Codes
 ******************************************************************************/
status_t LPSPI_MemInit(spi_master_config_t *config, LPSPI_Type *base)
{
    status_t status = kStatus_Fail;
    do
    {
        if (config == NULL)
        {
            status = kStatus_InvalidArgument;
            break;
        }

        BOARD_LpspiIomuxConfig(kSpiIomux_SpiMode);

        lpspi_master_config_t lpspiMasterCfg;
        LPSPI_MasterGetDefaultConfig(&lpspiMasterCfg);

        lpspiMasterCfg.baudRate                      = config->baudRate;
        lpspiMasterCfg.pcsToSckDelayInNanoSec        = 1000000000U / lpspiMasterCfg.baudRate;
        lpspiMasterCfg.lastSckToPcsDelayInNanoSec    = 1000000000U / lpspiMasterCfg.baudRate;
        lpspiMasterCfg.betweenTransferDelayInNanoSec = 1000000000U / lpspiMasterCfg.baudRate;

        LPSPI_Type *lpspiInstance = base;
        BOARD_LpspiPcsPinControl(false);

        LPSPI_MasterInit(lpspiInstance, &lpspiMasterCfg, config->clockFreq);
        status = kStatus_Success;
    } while (false);

    return status;
}

#if defined(__ICCARM__)
#pragma optimize = speed
#endif
status_t LPSPI_MemXfer(spi_mem_xfer_t *xfer, LPSPI_Type *base)
{
    status_t status = kStatus_Fail;

    do
    {
        if (xfer == NULL)
        {
            status = kStatus_InvalidArgument;
            break;
        }

#if (FSL_FEATURE_SOC_LPSPI_COUNT > 0)
        BOARD_LpspiPcsPinControl(true);

        switch (xfer->mode)
        {
            case kSpiMem_Xfer_CommandOnly:
            {
                lpspi_transfer_t txXfer;
                txXfer.txData      = xfer->cmd;
                txXfer.dataSize    = xfer->cmdSize;
                txXfer.rxData      = NULL;
                txXfer.configFlags = (uint32_t)kLPSPI_MasterPcs0 | (uint32_t)kLPSPI_MasterPcsContinuous;
                status             = LPSPI_MasterTransferBlocking(base, &txXfer);
            }
            break;
            case kSpiMem_Xfer_CommandWriteData:
            {
                lpspi_transfer_t cmdXfer;
                cmdXfer.txData      = xfer->cmd;
                cmdXfer.dataSize    = xfer->cmdSize;
                cmdXfer.rxData      = NULL;
                cmdXfer.configFlags = (uint32_t)kLPSPI_MasterPcs0 | (uint32_t)kLPSPI_MasterPcsContinuous;
                lpspi_transfer_t dataXfer;
                dataXfer.txData      = xfer->data;
                dataXfer.dataSize    = xfer->dataSize;
                dataXfer.rxData      = NULL;
                dataXfer.configFlags = (uint32_t)kLPSPI_MasterPcs0 | (uint32_t)kLPSPI_MasterPcsContinuous;
                status               = LPSPI_MasterTransferBlocking(base, &cmdXfer);
                if (status != kStatus_Success)
                {
                    break;
                }
                status = LPSPI_MasterTransferBlocking(base, &dataXfer);
            }
            break;
            case kSpiMem_Xfer_CommandReadData:
            {
                lpspi_transfer_t cmdXfer;
                cmdXfer.txData      = xfer->cmd;
                cmdXfer.dataSize    = xfer->cmdSize;
                cmdXfer.rxData      = NULL;
                cmdXfer.configFlags = (uint32_t)kLPSPI_MasterPcs0 | (uint32_t)kLPSPI_MasterPcsContinuous;
                lpspi_transfer_t dataXfer;
                dataXfer.txData      = NULL;
                dataXfer.dataSize    = xfer->dataSize;
                dataXfer.rxData      = xfer->data;
                dataXfer.configFlags = (uint32_t)kLPSPI_MasterPcs0 | (uint32_t)kLPSPI_MasterPcsContinuous;
                status               = LPSPI_MasterTransferBlocking(base, &cmdXfer);
                if (status != kStatus_Success)
                {
                    break;
                }
                status = LPSPI_MasterTransferBlocking(base, &dataXfer);
            }
            break;
            default:
                /* To avoid MISRA-C 2012 rule 16.4 issue. */
                break;
        }
        BOARD_LpspiPcsPinControl(false);

#endif
    } while (false);

    return status;
}

status_t LPSPI_MemReadId(flash_id_t *flashId, LPSPI_Type *base)
{
    status_t status = kStatus_Fail;

    do
    {
        if (flashId == NULL)
        {
            status = kStatus_InvalidArgument;
            break;
        }

        uint8_t cmdBuffer[1] = {kFlashCmd_ReadId};
        uint8_t dataBuffer[sizeof(flash_id_t)];
        spi_mem_xfer_t spiMemXfer;
        spiMemXfer.cmd      = cmdBuffer;
        spiMemXfer.cmdSize  = sizeof(cmdBuffer);
        spiMemXfer.data     = dataBuffer;
        spiMemXfer.dataSize = sizeof(dataBuffer);
        spiMemXfer.mode     = kSpiMem_Xfer_CommandReadData;
        status              = LPSPI_MemXfer(&spiMemXfer, base);

        if (status != kStatus_Success)
        {
            break;
        }

        (void)memcpy(&flashId->mid, dataBuffer, sizeof(flash_id_t));

        // According to JEP106AV, the valid ID starts from 0x01 to 0xFE, in which bit7 is the odd checksum bit,
        // and 0x7F is Continuation code
        uint32_t tempMid = flashId->mid;
        // Invalid manufacturer id
        if ((tempMid == 0u) || (tempMid == 0xFFu))
        {
            status = kStatus_Fail;
            break;
        }

        uint8_t *id_buf = (uint8_t *)dataBuffer;
        for (uint32_t i = 0u; i < sizeof(flash_id_t); i++)
        {
            if (*id_buf == 0x7Fu)
            {
                ++id_buf;
                continue;
            }
            break;
        }

        tempMid              = *id_buf;
        uint32_t oddBitCount = 0u;
        for (uint32_t i = 0u; i < 8u; i++)
        {
            if ((tempMid & 1u) != 0U)
            {
                ++oddBitCount;
            }
            tempMid >>= 1u;
        }
        // Parity: Odd
        if ((oddBitCount & 1u) == 0u)
        {
            status = kStatus_Fail;
            break;
        }

        flashId->mid    = id_buf[0];
        flashId->did[0] = id_buf[1];
        flashId->did[1] = id_buf[2];

        status = kStatus_Success;

    } while (false);

    return status;
}

static status_t LPSPI_MemWaitBusy(LPSPI_Type *base)
{
    bool isBusy     = true;
    status_t status = kStatus_Fail;
    do
    {
        uint8_t cmdBuffer[] = {kFlashCmd_ReadStatus};
        uint8_t flashStatus = 0u;
        spi_mem_xfer_t spiMemXfer;
        spiMemXfer.cmd      = cmdBuffer;
        spiMemXfer.cmdSize  = sizeof(cmdBuffer);
        spiMemXfer.data     = &flashStatus;
        spiMemXfer.dataSize = 1u;
        spiMemXfer.mode     = kSpiMem_Xfer_CommandReadData;

        status = LPSPI_MemXfer(&spiMemXfer, base);
        if (status != kStatus_Success)
        {
            break;
        }

        isBusy = (flashStatus & 1U) != 0U;
    } while (isBusy);

    return status;
}

status_t LPSPI_MemIsBusy(LPSPI_Type *base, bool *isBusy)
{
    status_t status = kStatus_Fail;

    uint8_t cmdBuffer[] = {kFlashCmd_ReadStatus};
    uint8_t flashStatus = 0u;
    spi_mem_xfer_t spiMemXfer;
    spiMemXfer.cmd      = cmdBuffer;
    spiMemXfer.cmdSize  = sizeof(cmdBuffer);
    spiMemXfer.data     = &flashStatus;
    spiMemXfer.dataSize = 1u;
    spiMemXfer.mode     = kSpiMem_Xfer_CommandReadData;

    status = LPSPI_MemXfer(&spiMemXfer, base);
    if (status != kStatus_Success)
    {
        return status;
    }

    *isBusy = (flashStatus & 1U) != 0U;

    return status;
}

status_t LPSPI_MemRead(uint32_t addr, uint8_t *buffer, uint32_t lengthInBytes, bool isFastRead, LPSPI_Type *base)
{
    status_t status = kStatus_Fail;

    uint8_t cmdBuffer[5];
    uint32_t cmdSize = 4u;

    if (isFastRead)
    {
        cmdBuffer[0] = kFlashCmd_FastRead;
        cmdSize      = 5u;
        cmdBuffer[4] = 0x00u; // DUMMY byte for fast read operation.
    }
    else
    {
        cmdBuffer[0] = kFlashCmd_ReadMemory24Bit;
    }

    uint32_t tmpAddr = addr;
    for (uint32_t i = 3u; i > 0u; i--)
    {
        cmdBuffer[i] = (uint8_t)(tmpAddr & 0xFFu);
        tmpAddr >>= 8u;
    }

    spi_mem_xfer_t spiMemXfer;
    spiMemXfer.cmd      = cmdBuffer;
    spiMemXfer.cmdSize  = cmdSize;
    spiMemXfer.data     = buffer;
    spiMemXfer.dataSize = lengthInBytes;
    spiMemXfer.mode     = kSpiMem_Xfer_CommandReadData;

    status = LPSPI_MemXfer(&spiMemXfer, base);

    return status;
}

status_t LPSPI_MemWriteEnable(LPSPI_Type *base)
{
    status_t status = kStatus_Fail;

    uint8_t cmdBuffer[5];
    uint32_t cmdSize = 4u;

    cmdBuffer[0] = kFlashCmd_WriteEnable;
    cmdSize      = 1u;

    spi_mem_xfer_t spiMemXfer;
    spiMemXfer.cmd      = cmdBuffer;
    spiMemXfer.cmdSize  = cmdSize;
    spiMemXfer.data     = NULL;
    spiMemXfer.dataSize = 0U;
    spiMemXfer.mode     = kSpiMem_Xfer_CommandOnly;

    status = LPSPI_MemXfer(&spiMemXfer, base);

    return status;
}

status_t LPSPI_MemWritePage(uint32_t addr, uint8_t *buffer, uint32_t lengthInBytes, bool blocking, LPSPI_Type *base)
{
    status_t status = kStatus_Fail;

    do
    {
        if (lengthInBytes == 0u)
        {
            status = kStatus_Success;
            break;
        }

        uint8_t cmdBuffer[5];
        uint32_t cmdSize = 4u;

        status = LPSPI_MemWriteEnable(base);
        if (status != kStatus_Success)
        {
            break;
        }

        cmdBuffer[0]     = kFlashCmd_PageProgram;
        uint32_t tmpAddr = addr;

        for (uint32_t i = 3u; i > 0u; i--)
        {
            cmdBuffer[i] = (uint8_t)(tmpAddr & 0xFFu);
            tmpAddr >>= 8u;
        }

        spi_mem_xfer_t spiMemXfer;
        spiMemXfer.cmd      = cmdBuffer;
        spiMemXfer.cmdSize  = cmdSize;
        spiMemXfer.data     = buffer;
        spiMemXfer.dataSize = lengthInBytes;
        spiMemXfer.mode     = kSpiMem_Xfer_CommandWriteData;

        status = LPSPI_MemXfer(&spiMemXfer, base);
        if (status != kStatus_Success)
        {
            break;
        }

        if (true == blocking)
        {
            status = LPSPI_MemWaitBusy(base);
        }
    } while (false);

    return status;
}

status_t LPSPI_MemErase(uint32_t addr, eraseOptions_t option, bool blocking, LPSPI_Type *base)
{
    status_t status = kStatus_Fail;

    do
    {
        uint8_t cmdBuffer[5];
        uint32_t cmdSize = 4u;

        status = LPSPI_MemWriteEnable(base);
        if (status != kStatus_Success)
        {
            break;
        }

        if (option == kSize_EraseAll)
        {
            cmdBuffer[0] = kFlashCmd_EraseAll;
            cmdSize      = 1u;
        }
        else
        {
            switch (option)
            {
                case kSize_ErasePage:
                    cmdBuffer[0] = kFlashCmd_ErasePage;
                    break;

                case kSize_Erase4K:
                    cmdBuffer[0] = kFlashCmd_Erase4K;
                    break;

                case kSize_Erase32K:
                    cmdBuffer[0] = kFlashCmd_Erase32K;
                    break;

                case kSize_Erase64K:
                    cmdBuffer[0] = kFlashCmd_Erase64K;
                    break;

                default:
                    status = kStatus_Fail;
                    break;
            }
            if (status != kStatus_Success)
            {
                break;
            }
            uint32_t tmpAddr = addr;
            for (uint32_t i = 3u; i > 0u; i--)
            {
                cmdBuffer[i] = (uint8_t)(tmpAddr & 0xFFu);
                tmpAddr >>= 8u;
            }
        }

        spi_mem_xfer_t spiMemXfer;
        spiMemXfer.cmd      = cmdBuffer;
        spiMemXfer.cmdSize  = cmdSize;
        spiMemXfer.data     = NULL;
        spiMemXfer.dataSize = 0U;
        spiMemXfer.mode     = kSpiMem_Xfer_CommandOnly;

        status = LPSPI_MemXfer(&spiMemXfer, base);
        if (status != kStatus_Success)
        {
            break;
        }

        if (true == blocking)
        {
            status = LPSPI_MemWaitBusy(base);
        }
    } while (false);

    return status;
}

status_t LPSPI_MemDeinit(LPSPI_Type *base)
{
    status_t status = kStatus_Fail;
    do
    {
        // Assert the PCS to high first
        BOARD_LpspiPcsPinControl(true);
        // De-initialize LPSPI
        LPSPI_Type *lpspiInstance = base;
        LPSPI_Deinit(lpspiInstance);

        BOARD_LpspiIomuxConfig(kSpiIomux_DefaultMode);

        status = kStatus_Success;
    } while (false);

    return status;
}
