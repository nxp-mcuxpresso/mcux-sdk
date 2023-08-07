/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef __FSL_SPIFI_NOR_FLASH_H__
#define __FSL_SPIFI_NOR_FLASH_H__

#include "fsl_common.h"
#include "fsl_spifi.h"

/*!
 * @addtogroup spifi_nor_flash
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Serial NOR command codes. */
enum _serial_nor_command
{
    /*------------- Below commands are common for NOR----------------*/
    kSerialNorCmd_Invalid           = 0x00U,
    kSerialNorCmd_WriteStatus       = 0x01U, /*!< WRSR: Write Status Register*/
    kSerialNorCmd_WriteSecStatus_31 = 0x31U, /*!< WRSR: Write second Status Register*/
    kSerialNorCmd_WriteSecStatus_3E = 0x3EU, /*!< WRSR: Write second Status Register*/
    kSerialNorCmd_WriteMemory = 0x02U, /*!< WRITE: Write Byte/Page Data to Memory Array with less than 4-byte address*/
    kSerialNorCmd_WriteMemoryA32      = 0x12U, /*!< 4PP: Write Byte/Page Data to Memory Array with 4-byte address*/
    kSerialNorCmd_WriteEnable         = 0x06U, /*!< WREN: Set Write Enable Latch*/
    kSerialNorCmd_WriteDisable        = 0x04U, /*!< WRDI: Reset Write Enable Latch*/
    kSerialNorCmd_ReadStatus          = 0x05U, /*!< RDSR: Read Status Register*/
    kSerialNorCmd_ReadSecStatus_35    = 0x35U, /*!< RDSR: Read second Status Register*/
    kSerialNorCmd_ReadSecStatus_3F    = 0x3FU, /*!< RDSR: Read second Status Register*/
    kSerialNorCmd_ReadMemory          = 0x03U, /*!< READ: Read Data from Memory Array with less than 4-byte address*/
    kSerialNorCmd_ReadMemoryA32       = 0x13U, /*!< 4READ: Read Data from Memory Array with 4-byte address*/
    kSerialNorCmd_ReadMemorySDR_1_1_2 = 0x3BU, /*!< READ: Read Data from Memory with 1(opcode)_1(address)_2(data) mode*/
    kSerialNorCmd_ReadMemorySDR_1_2_2 = 0xBBU, /*!< READ: Read Data from Memory with 1(opcode)_2(address)_2(data) mode*/
    kSerialNorCmd_ReadMemorySDR_1_1_4 = 0x6BU, /*!< READ: Read Data from Memory with 1(opcode)_1(address)_4(data) mode*/
    kSerialNorCmd_ReadMemorySDR_1_4_4 = 0xEBU, /*!< READ: Read Data from Memory with 1(opcode)_4(address)_4(data) mode*/
    kSerialNorCmd_ReadMemorySDR_1_4_4_A32 =
        0xECU, /*!< READ: Read Data from 4-bytes address Memory with 1(opcode)_4(address)_4(data) mode*/
    kSerialNorCmd_ReadMemorySDR_1_1_4_A32 =
        0x6CU, /*!< READ: Read Data from 4-bytes address Memory with 1(opcode)_1(address)_4(data) mode*/
    kSerialNorCmd_EraseChipNor      = 0x60U, /*!< CE */
    kSerialNorCmd_EraseChip         = 0xc7U, /*!< CE */
    kSerialNorCmd_ErasePage         = 0x42U, /*!< PE */
    kSerialNorCmd_EraseSector4KB    = 0x20U, /*!< SE4KB */
    kSerialNorCmd_EraseSector32KB   = 0x52U, /*!< SE32KB */
    kSerialNorCmd_EraseSector       = 0xd8U, /*!< SE */
    kSerialNorCmd_EraseSector4KBA32 = 0x21U, /*!< 4SE4KB */
    kSerialNorCmd_EraseSectorA32    = 0xdcU, /*!< 4SE */
};

/*! @brief SPIFI clock init with different clock frequency. */
typedef enum _spifi_nor_clock_init
{
    kSpifiNorClockInit_Sdfp = 0x0U,
    kSpifiNorClockInit_Max
} spifi_nor_clock_init_t;

/*! @brief Serial NOR quad mode enable setting requirements. */
enum
{
    kSerialNorQuadMode_NotConfig            = 0,
    kSerialNorQuadMode_StatusReg1_Bit6      = 1,
    kSerialNorQuadMode_StatusReg2_Bit1      = 2,
    kSerialNorQuadMode_StatusReg2_Bit7      = 3,
    kSerialNorQuadMode_StatusReg2_Bit1_0x31 = 4,
};

/*
 *  Spifi module configuration block
 */
/*! @brief Serial Spifi module configuration block. */
typedef struct _spifi_nor_config
{
    bool isQuadDualNeedEnable;      /*!< Wether quad/dual enable is needed: 1 - Enable, 0 - Disable */
    bool writeTwoStausBytes;        /*!< Wether need to write two status bytes to enable quad/dual mode */
    uint8_t quadDualEnableCommand;  /*!< Write status command which can enable quad/dual mode */
    uint8_t quadDualEnableBitShift; /*!< The shift of quad/dual enable bit in the status register */
    uint8_t quadDualreadCommand;    /*!< Read status command which can read quad/dual mode enable bit */
    spifi_config_t memConfig;       /*!< Common memory configuration info via SPIFI */
} spifi_nor_config_t;

/*
 *  Serial NOR basic command set structure
 */
typedef struct __serial_nor_command_set
{
    uint8_t writeStatusCommand;
    uint8_t pageWriteMemoryCommand;
    uint8_t readMemoryCommand;
    uint8_t writeDisableCommand;
    uint8_t readStatusCommand;
    uint8_t writeEnableCommand;
    uint8_t eraseSectorCommand;
    uint8_t eraseChipCommand;
} serial_nor_command_set_t;

typedef void (*clock_init)(spifi_nor_clock_init_t param);

/*
 *  Serial NOR configuration block
 */
typedef struct _spifi_mem_nor_config
{
    clock_init clockInit;       /*!< Clock init for different clock frequency requirement. */
    uint32_t cmd_format;        /*!< Command formt for read memory opration */
    uint32_t quad_mode_setting; /*!< Quad mode enable setting requirements */
} spifi_mem_nor_config_t;

/*
 *  Serial NOR handler
 */
typedef struct _spifi_mem_nor_handle
{
    spifi_command_type_t commandType;           /*!< Opcode and address type */
    spifi_command_format_t readmemCommandFormt; /*!< Command formt for read memory opration */
    uint8_t intermediateLen;                    /*!< Intermediate bytes precede the data  */
    serial_nor_command_set_t commandSet;        /*!< Serial NOR basic command set */
} spifi_mem_nor_handle_t;

/*! @}*/

#endif /* __FSL_SPIFI_NOR_FLASH_H__ */
