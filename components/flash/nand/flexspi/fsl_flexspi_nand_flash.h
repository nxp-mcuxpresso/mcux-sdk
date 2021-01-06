/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_flexspi.h"

/*!
 * @addtogroup flexspi_nand_flash
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief LUT sequence index for READ cache sequence  */
#define NAND_CMD_LUT_SEQ_IDX_READCACHE 0
/*! @brief LUT sequence index for Read Status sequence */
#define NAND_CMD_LUT_SEQ_IDX_READSTATUS 1
/*! @brief LUT sequence index for Read ID sequence */
#define NAND_CMD_LUT_SEQ_IDX_READJEDECID 2
/*! @brief LUT sequence index for write enable sequence */
#define NAND_CMD_LUT_SEQ_IDX_WRITEENABLE 3
/*! @brief LUT sequence index for Read cache for odd blocks */
#define NAND_CMD_LUT_SEQ_IDX_READCACHE_ODD 4
/*! @brief LUT sequence index for erase block */
#define NAND_CMD_LUT_SEQ_IDX_ERASEBLOCK 5
/*! @brief LUT sequence index for program load */
#define NAND_CMD_LUT_SEQ_IDX_PROGRAMLOAD 6
/*! @brief LUT sequence index for program load for odd blocks */
#define NAND_CMD_LUT_SEQ_IDX_PROGRAMLOAD_ODD 7
/*! @brief LUT sequence index for program load for read page */
#define NAND_CMD_LUT_SEQ_IDX_READPAGE 8
/*! @brief LUT sequence index for read ecc status  */
#define NAND_CMD_LUT_SEQ_IDX_READECCSTAT 9
/*! @brief LUT sequence index for program execute */
#define NAND_CMD_LUT_SEQ_IDX_PROGRAMEXECUTE 10
/*! @brief LUT sequence index for get parameter table */
#define NAND_CMD_LUT_SEQ_IDX_SETFEATURE 11
/*! @brief Unlock all blocks */
#define NAND_CMD_LUT_SEQ_IDX_UNLOCKALL 12

/* !@brief FlexSPI Memory Configuration Block */
typedef struct _flexspi_memory_config
{
    flexspi_device_config_t deviceConfig; /*!< Device configuration structure */
    flexspi_port_t devicePort;     /*!< Device connected to which port, SS0_A means port A1, SS0_B means port B1*/
    uint32_t dataBytesPerPage;     /*!< Data Size in one page, usually it is 2048 or 4096*/
    uint32_t bytesInPageSpareArea; /*!< Total size in one page, usually, it equals 2 ^ width of column address*/
    uint32_t pagesPerBlock;        /*!< Pages per block*/
    uint16_t busyOffset; /*!< Busy offset, valid value: 0-31, only need for check option kNandReadyCheckOption_RB */
    uint16_t busyBitPolarity; /*!< Busy flag polarity, 0 - busy flag is 1 when flash device is busy, 1 -busy flag is 0
                                   when flash device is busy, only need for check option kNandReadyCheckOption_RB */
    uint32_t eccStatusMask;   /*!< ECC status mask */
    uint32_t eccFailureMask;  /*!< ECC failure mask */
    uint32_t lookupTable[64]; /*!< Lookup table holds Flash command sequences */
} flexspi_mem_config_t;

/*!@brief NAND Flash handle info*/
typedef struct _flexspi_mem_nand_handle
{
    flexspi_port_t port; /*!< Device connected to which port, SS0_A means port A1, SS0_B means port B1*/
    uint16_t busyOffset; /*!< Busy offset, valid value: 0-31, only need for check option kNandReadyCheckOption_RB */
    uint16_t busyBitPolarity; /*!< Busy flag polarity, 0 - busy flag is 1 when flash device is busy, 1 -busy flag is 0
                                   when flash device is busy, only need for check option kNandReadyCheckOption_RB */
    uint32_t eccStatusMask;   /*!< ECC status mask */
    uint32_t eccFailureMask;  /*!< ECC failure mask */
} flexspi_mem_nand_handle_t;
/*! @} */
