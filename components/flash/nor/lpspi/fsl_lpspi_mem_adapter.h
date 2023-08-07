/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef __SPI_MEM_ADAPTER_H__
#define __SPI_MEM_ADAPTER_H__

#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
//!@brief SPI Master Configuration for Adapter
typedef struct
{
    uint32_t whichPcs;  //!< PCS index
    uint32_t clockFreq; //!< Clock requency for SPI
    uint32_t baudRate;  //!< Baudrate for SPI
} spi_master_config_t;

//!@brief SPI Memory transfer mode defintions
typedef enum _spi_mem_xfer_mode
{
    kSpiMem_Xfer_CommandOnly,      //!< Command Only
    kSpiMem_Xfer_CommandWriteData, //!< Command then Write Data
    kSpiMem_Xfer_CommandReadData,  //!< Comamdn then Read Data
} spi_mem_xfer_mode_t;

//!@brief SPI Memory Transfer Context
typedef struct __spi_mem_xfer
{
    uint8_t *cmd;             //!< Command buffer
    uint8_t *data;            //!< Data Buffer
    size_t cmdSize;           //!< Command buffer size
    size_t dataSize;          //!< Data buffer size
    spi_mem_xfer_mode_t mode; //!< Transfer mode
} spi_mem_xfer_t;

//!@brief Flash ID definition
typedef struct _flash_id
{
    uint8_t mid;    //!< Manufacturer Identifier
    uint8_t did[2]; //!< Device Identifier
    uint8_t reserved[17];
} flash_id_t;

typedef enum
{
    kSpiIomux_SpiMode,
    kSpiIomux_DefaultMode
} spi_pin_mode_t;

typedef enum
{
    kSpiClockMode_Spi,
    kSpiClockMode_Default
} spi_clock_mode_t;

typedef enum
{
    kSize_ErasePage = 0x1,
    kSize_Erase4K   = 0x2,
    kSize_Erase32K  = 0x3,
    kSize_Erase64K  = 0x4,
    kSize_EraseAll  = 0x5,
} eraseOptions_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

//!@brief Initialize SPI Memory
status_t LPSPI_MemInit(spi_master_config_t *config, LPSPI_Type *base);

//!@brief Issue SPI Memory Transfer
status_t LPSPI_MemXfer(spi_mem_xfer_t *xfer, LPSPI_Type *base);

//!@brief Read SPI Memory ID
status_t LPSPI_MemReadId(flash_id_t *flashId, LPSPI_Type *base);

//!@brief Read Data from SPI Memory
status_t LPSPI_MemRead(uint32_t addr, uint8_t *buffer, uint32_t lengthInBytes, bool isFastRead, LPSPI_Type *base);

//!@brief Enable SPI flash writes
status_t LPSPI_MemWriteEnable(LPSPI_Type *base);

//!@brief Write Data to SPI Memory
status_t LPSPI_MemWritePage(uint32_t addr, uint8_t *buffer, uint32_t lengthInBytes, bool blocking, LPSPI_Type *base);

//!@brief Erase data from SPI Memory to 0xFF
status_t LPSPI_MemErase(uint32_t addr, eraseOptions_t option, bool blocking, LPSPI_Type *base);

//!@brief Get the busy status of the NOR flash.
status_t LPSPI_MemIsBusy(LPSPI_Type *base, bool *isBusy);

//!@brief Deinitialize the SPI memory
status_t LPSPI_MemDeinit(LPSPI_Type *base);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif // SPI_ADAPTER_H__
