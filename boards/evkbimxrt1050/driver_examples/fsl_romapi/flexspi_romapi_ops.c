/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_romapi.h"

#if !defined(XIP_EXTERNAL_FLASH) || (XIP_EXTERNAL_FLASH != 1)
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEDATA 6U
#define HYPERFLASH_CMD_LUT_SEQ_IDX_READDATA  7U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static status_t FLEXSPI_NorFlash_HyperBusWrite(uint32_t instance, uint32_t addr, uint32_t *buffer, uint32_t bytes);
static status_t FLEXSPI_NorFlash_HyperBusRead(uint32_t instance, uint32_t addr, uint32_t *buffer, uint32_t bytes);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

static status_t FLEXSPI_NorFlash_HyperBusWrite(uint32_t instance, uint32_t addr, uint32_t *buffer, uint32_t bytes)
{
    flexspi_xfer_t xfer;
    xfer.operation            = kFLEXSPIOperation_Write;
    xfer.seqId                = HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEDATA;
    xfer.seqNum               = 1U;
    xfer.baseAddress          = addr * 2U; // word address for HyperFlash
    xfer.isParallelModeEnable = false;
    xfer.txBuffer             = buffer;
    xfer.txSize               = bytes;

    status_t status = ROM_FLEXSPI_NorFlash_CommandXfer(instance, &xfer);

    return status;
}

static status_t FLEXSPI_NorFlash_HyperBusRead(uint32_t instance, uint32_t addr, uint32_t *buffer, uint32_t bytes)
{
    flexspi_xfer_t xfer;
    xfer.operation            = kFLEXSPIOperation_Read;
    xfer.seqId                = HYPERFLASH_CMD_LUT_SEQ_IDX_READDATA;
    xfer.seqNum               = 1U;
    xfer.baseAddress          = addr * 2U; // word address for HyperFlash
    xfer.isParallelModeEnable = false;
    xfer.rxBuffer             = buffer;
    xfer.rxSize               = bytes;

    status_t status = ROM_FLEXSPI_NorFlash_CommandXfer(instance, &xfer);

    return status;
}

/*
 * @brief Read ID-CFI Parameters
 */
status_t FLEXSPI_NorFlash_VerifyID(uint32_t instance)
{
    status_t status = kStatus_InvalidArgument;
    uint32_t lut_seq[4];

    memset(lut_seq, 0, sizeof(lut_seq));
    // Write
    lut_seq[0] = FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x20, RADDR_DDR, FLEXSPI_8PAD, 0x18);
    lut_seq[1] = FSL_ROM_FLEXSPI_LUT_SEQ(CADDR_DDR, FLEXSPI_8PAD, 0x10, WRITE_DDR, FLEXSPI_8PAD, 0x02);
    ROM_FLEXSPI_NorFlash_UpdateLut(instance, HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEDATA, (const uint32_t *)lut_seq, 1U);

    // Read
    memset(lut_seq, 0, sizeof(lut_seq));
    lut_seq[0] = FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0xA0, RADDR_DDR, FLEXSPI_8PAD, 0x18);
    lut_seq[1] = FSL_ROM_FLEXSPI_LUT_SEQ(CADDR_DDR, FLEXSPI_8PAD, 0x10, READ_DDR, FLEXSPI_8PAD, 0x04);
    ROM_FLEXSPI_NorFlash_UpdateLut(instance, HYPERFLASH_CMD_LUT_SEQ_IDX_READDATA, (const uint32_t *)lut_seq, 1U);

    // CFI Entry
    uint32_t buffer[2];
    uint8_t data[4] = {0x00, 0x98};
    status          = FLEXSPI_NorFlash_HyperBusWrite(instance, 0x555U, (uint32_t *)data, 2U);
    if (status != kStatus_Success)
    {
        return status;
    }

    // ID-CFI Read
    // Read Query Unique ASCII String
    status = FLEXSPI_NorFlash_HyperBusRead(instance, 0x10U, &buffer[0], sizeof(buffer));
    if (status != kStatus_Success)
    {
        return status;
    }

    buffer[1] &= 0xFFFF;
    // Check that the data read out is  unicode "QRY" in big-endian order
    if ((buffer[0] != 0x52005100U) || (buffer[1] != 0x5900U))
    {
        status = kStatus_ROM_FLEXSPINOR_Flash_NotFound;
        return status;
    }
    // ASO Exit 0xF000
    data[1] = 0xF0U;
    status  = FLEXSPI_NorFlash_HyperBusWrite(instance, 0x0U, (uint32_t *)data, 2U);
    if (status != kStatus_Success)
    {
        return status;
    }

    return status;
}
#endif // XIP_EXTERNAL_FLASH
