/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <string.h>
#include "fsl_spifi_nor_flash.h"
#include "fsl_nor_flash.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SPIFI_MAX_24BIT_ADDRESSING_SIZE (16UL * 1024 * 1024)
#define SPIFI_256K_SECTOR_SIZE_OFFSET   (18U)
#define NOR_SFDP_SIGNATURE              0x50444653 /* ASCII: SFDP */

enum
{
    kSerialFlash_ReadSFDP           = 0x5A,
    kSerialFlash_ReadManufacturerId = 0x9F,
};

enum
{
    kSfdp_Version_Major_1_0 = 1,
    kSfdp_Version_Minor_0   = 0, /* JESD216 */
    kSfdp_Version_Minor_A   = 5, /* JESD216A */
    kSfdp_Version_Minor_B   = 6, /* JESD216B */
    kSfdp_Version_Minor_C   = 7, /* JESD216C */

    kSfdp_BasicProtocolTableSize_Rev0 = 36,
    kSfdp_BasicProtocolTableSize_RevA = 64,
    kSfdp_BasicProtocolTableSize_RevB = kSfdp_BasicProtocolTableSize_RevA,
    kSfdp_BasicProtocolTableSize_RevC = 80,
};

enum
{
    kParameterID_BasicSpiProtocol = 0xFF00,
    /* New Table added in JESD216B */
    kParameterID_SectorMap                    = 0xFF81,
    kParameterID_4ByteAddressInstructionTable = 0xFF84,
    /* New Table added in JESD216C */
    kParameterID_xSpiProfile1_0   = 0xFF85,
    kParameterID_xSpiOrofile2_0   = 0xFF86,
    kParameterID_StaCtrlCfgRegMap = 0xFF87,
    kParameterID_OpiEnableSeq     = 0xFF09,
};

typedef struct _sfdp_header
{
    uint32_t signature;
    uint8_t minor_rev;
    uint8_t major_rev;
    uint8_t param_hdr_num;
    uint8_t sfdp_access_protocol; /* Defined in JESD216C, reserved for older version */
} sfdp_header_t;

/*!@brief SFDP Parameter Header, see JESD216B doc for more details */
typedef struct _sfdp_parameter_header
{
    uint8_t parameter_id_lsb;
    uint8_t minor_rev;
    uint8_t major_rev;
    uint8_t table_length_in_32bit;
    uint8_t parameter_table_pointer[3];
    uint8_t parameter_id_msb;
} sfdp_parameter_header_t;

/*!@brief Basic Flash Parameter Table, see JESD216B doc for more details */
typedef struct _jedec_flash_param_table
{
    struct
    {
        uint32_t erase_size : 2;
        uint32_t write_granularity : 1;
        uint32_t reserved0 : 2;
        uint32_t unused0 : 3;
        uint32_t erase4k_inst : 8;
        uint32_t support_1_1_2_fast_read : 1;
        uint32_t address_bits : 2;
        uint32_t support_ddr_clocking : 1;
        uint32_t support_1_2_2_fast_read : 1;
        uint32_t supports_1_4_4_fast_read : 1;
        uint32_t support_1_1_4_fast_read : 1;
        uint32_t unused1 : 9;
    } misc;
    uint32_t flash_density;
    struct
    {
        uint32_t dummy_clocks_1_4_4_read : 5;
        uint32_t mode_clocks_1_4_4_read : 3;
        uint32_t inst_1_4_4_read : 8;
        uint32_t dummy_clocks_1_1_4_read : 5;
        uint32_t mode_clocks_1_1_4_read : 3;
        uint32_t inst_1_1_4_read : 8;
    } read_1_4_info;
    struct
    {
        uint32_t dummy_clocks_1_2_2_read : 5;
        uint32_t mode_clocks_1_2_2_read : 3;
        uint32_t inst_1_2_2_read : 8;
        uint32_t dummy_clocks_1_1_2_read : 5;
        uint32_t mode_clocks_1_1_2_read : 3;
        uint32_t inst_1_1_2_read : 8;
    } read_1_2_info;

    struct
    {
        uint32_t support_2_2_2_fast_read : 1;
        uint32_t reserved0 : 3;
        uint32_t support_4_4_4_fast_read : 1;
        uint32_t reserved1 : 27;
    } read_22_44_check;

    struct
    {
        uint32_t reserved0 : 16;
        uint32_t dummy_clocks_2_2_2_read : 5;
        uint32_t mode_clocks_2_2_2_read : 3;
        uint32_t inst_2_2_2_read : 8;
    } read_2_2_info;
    struct
    {
        uint32_t reserved0 : 16;
        uint32_t dummy_clocks_4_4_4_read : 5;
        uint32_t mode_clocks_4_4_4_read : 3;
        uint32_t inst_4_4_4_read : 8;
    } read_4_4_info;

    struct
    {
        uint8_t size;
        uint8_t inst;
    } erase_info[4];

    uint32_t erase_timing;
    struct
    {
        uint32_t reserved0 : 4;
        uint32_t page_size : 4;
        uint32_t reserved1 : 24;
    } chip_erase_progrm_info;

    struct
    {
        uint32_t suspend_resume_spec;
        uint32_t suspend_resume_inst;
    } suspend_resume_info;

    struct
    {
        uint32_t reserved0 : 2;
        uint32_t busy_status_polling : 6;
        uint32_t reserved1 : 24;
    } busy_status_info;

    struct
    {
        uint32_t mode_4_4_4_disable_seq : 4;
        uint32_t mode_4_4_4_enable_seq : 5;
        uint32_t support_mode_0_4_4 : 1;
        uint32_t mode_0_4_4_exit_method : 6;
        uint32_t mode_0_4_4_entry_method : 4;
        uint32_t quad_enable_requirement : 3;
        uint32_t hold_reset_disable : 1;
        uint32_t reserved0 : 8;
    } mode_4_4_info;

    struct
    {
        uint32_t status_reg_write_enable : 7;
        uint32_t reserved0 : 1;
        uint32_t soft_reset_rescue_support : 6;
        uint32_t exit_4_byte_addressing : 10;
        uint32_t enter_4_byte_addrssing : 8;
    } mode_config_info;
} jedec_flash_param_table_t;

/*!@brief 4Byte Addressing Instruction Table, see JESD216B doc for more details */
typedef struct _jedec_4byte_addressing_inst_table
{
    struct
    {
        uint32_t support_1_1_1_read : 1;
        uint32_t support_1_1_1_fast_read : 1;
        uint32_t support_1_1_2_fast_read : 1;
        uint32_t support_1_2_2_fast_read : 1;
        uint32_t support_1_1_4_fast_read : 1;
        uint32_t support_1_4_4_fast_read : 1;
        uint32_t support_1_1_1_page_program : 1;
        uint32_t support_1_1_4_page_program : 1;
        uint32_t support_1_4_4_page_program : 1;
        uint32_t support_erase_type1_size : 1;
        uint32_t support_erase_type2_size : 1;
        uint32_t support_erase_type3_size : 1;
        uint32_t support_erase_type4_size : 1;
        uint32_t support_1_1_1_dtr_read : 1;
        uint32_t support_1_2_2_dtr_read : 1;
        uint32_t support_1_4_4_dtr_read : 1;
        uint32_t support_volatile_sector_lock_read_cmd : 1;
        uint32_t support_volatile_sector_lock_write_cmd : 1;
        uint32_t support_nonvolatile_sector_lock_read_cmd : 1;
        uint32_t support_nonvolatile_sector_lock_write_cmd : 1;
        uint32_t reserved : 12;
    } cmd_4byte_support_info;

    struct
    {
        uint8_t erase_inst[4];
    } erase_inst_info;
} jedec_4byte_addressing_inst_table_t;

typedef struct _jdec_query_table
{
    uint32_t standard_version; /* JESD216 version */
    uint32_t flash_param_tbl_size;
    jedec_flash_param_table_t flash_param_tbl;
    bool has_4b_addressing_inst_table;
    jedec_4byte_addressing_inst_table_t flash_4b_inst_tbl;
} jedec_info_table_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*! @brief Send Write Enable command to Serial NOR via SPIFI */
static status_t spifi_nor_write_enable(SPIFI_Type *base,
                                       spifi_mem_nor_handle_t *handle,
                                       spifi_command_format_t cmdFormat);
/*! @brief Send read status command to Serial NOR via SPIFI */
static uint8_t spifi_nor_read_status(SPIFI_Type *base, uint8_t readCmd);
/*! @brief Enable nor flash quad mode via SPIFI */
static status_t spifi_nor_quad_mode_enable(SPIFI_Type *base,
                                           spifi_nor_config_t *config,
                                           spifi_mem_nor_handle_t *memHandle);
/*! @brief Parse SFDP parameters and then fill into SPIFI Serial NOR Configuration Block */
static status_t spifi_nor_parse_sfdp(spifi_nor_config_t *config,
                                     jedec_info_table_t *tbl,
                                     spifi_mem_nor_config_t *memConfig,
                                     nor_handle_t *handle);
/*! @brief Read SFDP information via SPIFI */
static status_t spifi_nor_read_sfdp_info(SPIFI_Type *base, jedec_info_table_t *tbl);
/*! @brief Read SFDP info specified by arguments */
static status_t spifi_nor_read_sfdp(SPIFI_Type *base, uint32_t address, uint32_t *buffer, uint32_t bytes);
/*! @brief Get page/sector size from SFDP */
static status_t spifi_get_page_sector_size_from_sfdp(nor_handle_t *handle, jedec_info_table_t *tbl);
/*! @brief Sector erase with the minimum supported sector size */
static status_t spifi_nor_erase_sector(nor_handle_t *handle, uint32_t address);
/*! @brief Sector write protection disabled */
static status_t spifi_nor_writeprotect_disable(SPIFI_Type *base, spifi_mem_nor_handle_t *memHandle);
/*******************************************************************************
 * Variables
 ******************************************************************************/
spifi_mem_nor_handle_t spifi_handle;

/*******************************************************************************
 * Code
 ******************************************************************************/

static uint8_t spifi_nor_read_status(SPIFI_Type *base, uint8_t readCmd)
{
    spifi_command_t cmd;
    uint8_t value;

    cmd.dataLen           = 0x01U;
    cmd.isPollMode        = false;
    cmd.direction         = kSPIFI_DataInput;
    cmd.intermediateBytes = 0;
    cmd.format            = kSPIFI_CommandAllSerial;
    cmd.type              = kSPIFI_CommandOpcodeOnly;
    cmd.opcode            = readCmd;
    SPIFI_SetCommand(base, &cmd);
    value = *(uint8_t *)&base->DATA;

    return value;
}

static status_t spifi_check_norflash_finish(SPIFI_Type *base, spifi_mem_nor_handle_t *handle)
{
    spifi_command_t cmd;
    uint8_t value;

    /* Using hardware POLL mode to get matched status value.
     * And set DATALEN as 0 means choosing bit0 of Norflash status register to compare with bit3,
     * if both of them are 0, that is, flash is in IDLE state, will trigger INIRQ as 1 in
     * STATUS register.
     */
    cmd.dataLen           = 0x00;
    cmd.isPollMode        = true;
    cmd.direction         = kSPIFI_DataInput;
    cmd.intermediateBytes = 0;
    cmd.format            = kSPIFI_CommandAllSerial;
    cmd.type              = kSPIFI_CommandOpcodeOnly;
    cmd.opcode            = handle->commandSet.readStatusCommand;

    /* Clear INTRQ bit first, perhaps set by the previous operation. */
    base->STAT = SPIFI_STAT_INTRQ_MASK;
    SPIFI_SetCommand(base, &cmd);
    while ((base->STAT & SPIFI_STAT_INTRQ_MASK) == 0U)
    {
    }
    value = *(uint8_t *)&base->DATA;

    return (value & 0x01U) ? kStatus_Fail : kStatus_Success;
}

static status_t spifi_nor_write_enable(SPIFI_Type *base,
                                       spifi_mem_nor_handle_t *handle,
                                       spifi_command_format_t cmdFormat)
{
    spifi_command_t cmd;
    status_t status;
    uint8_t value;

    /* Enable write operation. */
    cmd.dataLen           = 0;
    cmd.isPollMode        = false;
    cmd.direction         = kSPIFI_DataOutput;
    cmd.intermediateBytes = 0;
    cmd.format            = cmdFormat;
    cmd.type              = kSPIFI_CommandOpcodeOnly;
    cmd.opcode            = handle->commandSet.writeEnableCommand;
    SPIFI_SetCommand(base, &cmd);

    status = spifi_check_norflash_finish(base, handle);
    /* check whether enable write operation success. */
    value = spifi_nor_read_status(base, handle->commandSet.readStatusCommand);
    if (0 == (value & 0x2U))
    {
        return kStatus_Fail;
    }

    return status;
}

static status_t spifi_nor_quad_mode_enable(SPIFI_Type *base,
                                           spifi_nor_config_t *config,
                                           spifi_mem_nor_handle_t *memHandle)
{
    spifi_command_t cmd;
    status_t status;
    uint8_t quadValue;
    uint8_t valueAfter;

    if (kSerialNorCmd_Invalid == config->quadDualreadCommand)
    {
        return kStatus_InvalidArgument;
    }

    /* Read status register which contain quad/dual enable bit. */
    quadValue = spifi_nor_read_status(base, config->quadDualreadCommand);
    /* Check whether the mode need to switich.
       Only consider the bit value in the quad spi mode is 1 here.*/
    if (quadValue & (0x1U << config->quadDualEnableBitShift))
    {
        return kStatus_Success;
    }

    do
    {
        /* Enable write operation. */
        status = spifi_nor_write_enable(base, memHandle, kSPIFI_CommandAllSerial);
        if (kStatus_Success != status)
        {
            return status;
        }

        if (true == config->writeTwoStausBytes)
        {
            uint8_t valueStatus;
            uint16_t valueSwitch;
            /* Read status register1 to combine the value of two status registers, then write it back.
               This opration can maintain the state of all other writable status register bits*/
            valueStatus = spifi_nor_read_status(base, memHandle->commandSet.readStatusCommand);
            valueSwitch = valueStatus | ((quadValue | (0x1U << config->quadDualEnableBitShift)) << 8);

            /* Enable quad/dual spi mode. */
            cmd.dataLen           = 0x02U;
            cmd.isPollMode        = false;
            cmd.direction         = kSPIFI_DataOutput;
            cmd.intermediateBytes = 0;
            cmd.format            = kSPIFI_CommandAllSerial;
            cmd.type              = kSPIFI_CommandOpcodeOnly;
            cmd.opcode            = memHandle->commandSet.writeStatusCommand;
            SPIFI_SetCommand(base, &cmd);
            SPIFI_WriteDataHalfword(base, valueSwitch);
        }
        else
        {
            /* Enable quad/dual spi mode. */
            cmd.dataLen           = 0x01U;
            cmd.isPollMode        = false;
            cmd.direction         = kSPIFI_DataOutput;
            cmd.intermediateBytes = 0;
            cmd.format            = kSPIFI_CommandAllSerial;
            cmd.type              = kSPIFI_CommandOpcodeOnly;
            cmd.opcode            = config->quadDualEnableCommand;
            SPIFI_SetCommand(base, &cmd);
            SPIFI_WriteDataByte(base, (quadValue | (0x1U << config->quadDualEnableBitShift)));
        }

        status = spifi_check_norflash_finish(base, memHandle);
        if (kStatus_Success != status)
        {
            return status;
        }

        /* Read status register which contain quad/dual enable bit to check whether swtich opration success. */
        valueAfter = spifi_nor_read_status(base, config->quadDualreadCommand);
    } while ((valueAfter & (0x1U << config->quadDualEnableBitShift)) == 0);

    return kStatus_Success;
}

static status_t spifi_nor_read_sfdp(SPIFI_Type *base, uint32_t address, uint32_t *buffer, uint32_t bytes)
{
    spifi_command_t cmd;

    cmd.isPollMode        = false;
    cmd.direction         = kSPIFI_DataInput;
    cmd.intermediateBytes = 1;
    cmd.format            = kSPIFI_CommandAllSerial;
    cmd.type              = kSPIFI_CommandOpcodeAddrThreeBytes;
    cmd.opcode            = kSerialFlash_ReadSFDP;
    SPIFI_SetMemoryCommand(base, &cmd);

    memcpy(buffer, (void *)(address + FSL_FEATURE_SPIFI_START_ADDR), bytes);
    /* Reset to command mode. */
    SPIFI_ResetCommand(base);

    return kStatus_Success;
}

static status_t spifi_nor_writeprotect_disable(SPIFI_Type *base, spifi_mem_nor_handle_t *memHandle)
{
    spifi_command_t cmd;

    /* Disable write protection. */
    cmd.dataLen           = 1U;
    cmd.isPollMode        = false;
    cmd.direction         = kSPIFI_DataOutput;
    cmd.intermediateBytes = 0;
    cmd.format            = kSPIFI_CommandAllSerial;
    cmd.type              = kSPIFI_CommandOpcodeOnly;
    cmd.opcode            = memHandle->commandSet.writeStatusCommand;
    SPIFI_SetCommand(base, &cmd);
    *(uint8_t *)&base->DATA = 0x00;

    return spifi_check_norflash_finish(base, memHandle);
}

static status_t spifi_nor_read_sfdp_info(SPIFI_Type *base, jedec_info_table_t *tbl)
{
    status_t status = kStatus_Fail;
    do
    {
        if (tbl == NULL)
        {
            status = kStatus_InvalidArgument;
            break;
        }

        sfdp_header_t sfdp_header;
        uint32_t address;
        /* Read SFDP header */
        status = spifi_nor_read_sfdp(base, 0, (uint32_t *)&sfdp_header, sizeof(sfdp_header));
        if (status != kStatus_Success)
        {
            break;
        }

        if (sfdp_header.signature != NOR_SFDP_SIGNATURE)
        {
            break;
        }

        tbl->standard_version = sfdp_header.minor_rev;

        uint32_t parameter_header_number = sfdp_header.param_hdr_num + 1;
        sfdp_parameter_header_t sfdp_param_hdrs[10];
        uint32_t max_hdr_count = parameter_header_number > 10 ? 10 : parameter_header_number;
        address                = 0x08;
        /* Read parameter headers */
        status = spifi_nor_read_sfdp(base, address, (uint32_t *)&sfdp_param_hdrs[0],
                                     max_hdr_count * sizeof(sfdp_parameter_header_t));
        if (status != kStatus_Success)
        {
            break;
        }
        memset(tbl, 0, sizeof(*tbl));

        for (uint32_t i = 0; i < max_hdr_count; i++)
        {
            uint32_t parameter_id =
                sfdp_param_hdrs[i].parameter_id_lsb + ((uint32_t)sfdp_param_hdrs[i].parameter_id_msb << 8);

            if ((parameter_id == kParameterID_BasicSpiProtocol) ||
                (parameter_id == kParameterID_4ByteAddressInstructionTable))
            {
                address = 0;
                for (int32_t index = 2; index >= 0; index--)
                {
                    address <<= 8;
                    address |= sfdp_param_hdrs[i].parameter_table_pointer[index];
                }
                uint32_t table_size = sfdp_param_hdrs[i].table_length_in_32bit * sizeof(uint32_t);

                if (parameter_id == kParameterID_BasicSpiProtocol)
                {
                    /* Limit table size to the max supported standard */
                    if (table_size > sizeof(jedec_flash_param_table_t))
                    {
                        table_size = sizeof(jedec_flash_param_table_t);
                    }
                    /* Read Basic SPI Protocol Table */
                    status = spifi_nor_read_sfdp(base, address, (uint32_t *)&tbl->flash_param_tbl, table_size);
                    if (status != kStatus_Success)
                    {
                        break;
                    }
                    tbl->flash_param_tbl_size = table_size;
                }
                else if (parameter_id == kParameterID_4ByteAddressInstructionTable)
                {
                    /* Read 4-byte Address Instruction Table */
                    status = spifi_nor_read_sfdp(base, address, (uint32_t *)&tbl->flash_4b_inst_tbl, table_size);
                    if (status != kStatus_Success)
                    {
                        break;
                    }
                    tbl->has_4b_addressing_inst_table = true;
                }
            }
            else
            {
                /* Unsupported parameter type, ignore */
            }
        }

    } while (0);

    return status;
}

static status_t spifi_get_page_sector_size_from_sfdp(nor_handle_t *handle, jedec_info_table_t *tbl)
{
    jedec_flash_param_table_t *param_tbl              = &tbl->flash_param_tbl;
    jedec_4byte_addressing_inst_table_t *flash_4b_tbl = &tbl->flash_4b_inst_tbl;
    spifi_mem_nor_handle_t *memHandle                 = (spifi_mem_nor_handle_t *)handle->deviceSpecific;

    uint32_t flash_size;
    uint32_t flash_density = tbl->flash_param_tbl.flash_density;

    if (flash_density & (1U << 0x1F))
    {
        /* Flash size >= 4G bits */
        flash_size = 1U << ((flash_density & ~(1U << 0x1F)) - 3);
    }
    else
    {
        /* Flash size < 4G bits */
        flash_size = (flash_density + 1) >> 3;
    }
    handle->bytesInMemorySize = flash_size;

    /* Calculate Page size */
    uint32_t page_size;
    if (tbl->flash_param_tbl_size < 64U)
    {
        handle->bytesInPageSize = 256U;
    }
    else
    {
        page_size               = 1 << (param_tbl->chip_erase_progrm_info.page_size);
        handle->bytesInPageSize = page_size == (1 << 15) ? 256U : page_size;
    }

    /* Calculate Sector Size */
    uint32_t sector_size       = 1U << SPIFI_256K_SECTOR_SIZE_OFFSET;
    uint32_t sector_erase_type = 0;

    for (uint32_t index = 0; index < 4; index++)
    {
        if (param_tbl->erase_info[index].size != 0)
        {
            uint32_t current_erase_size = 1U << param_tbl->erase_info[index].size;
            if ((current_erase_size < sector_size) && (current_erase_size < (1024U * 1024U)))
            {
                sector_size       = current_erase_size;
                sector_erase_type = index;
            }
        }
    }

    handle->bytesInSectorSize = sector_size;

    if (handle->bytesInMemorySize > SPIFI_MAX_24BIT_ADDRESSING_SIZE)
    {
        if (tbl->has_4b_addressing_inst_table)
        {
            memHandle->commandSet.eraseSectorCommand = flash_4b_tbl->erase_inst_info.erase_inst[sector_erase_type];
        }
        else
        {
            switch (param_tbl->erase_info[sector_erase_type].inst)
            {
                case kSerialNorCmd_EraseSector4KB:
                    memHandle->commandSet.eraseSectorCommand = kSerialNorCmd_EraseSector4KBA32;
                    break;
                case kSerialNorCmd_EraseSector:
                    memHandle->commandSet.eraseSectorCommand = kSerialNorCmd_EraseSectorA32;
                    break;
            }
        }
    }
    else
    {
        memHandle->commandSet.eraseSectorCommand = param_tbl->erase_info[sector_erase_type].inst;
    }

    return kStatus_Success;
}

static status_t spifi_nor_parse_sfdp(spifi_nor_config_t *config,
                                     jedec_info_table_t *tbl,
                                     spifi_mem_nor_config_t *memConfig,
                                     nor_handle_t *handle)
{
    status_t status                   = kStatus_InvalidArgument;
    spifi_mem_nor_handle_t *memHandle = (spifi_mem_nor_handle_t *)handle->deviceSpecific;

    do
    {
        jedec_flash_param_table_t *param_tbl              = &tbl->flash_param_tbl;
        jedec_4byte_addressing_inst_table_t *flash_4b_tbl = &tbl->flash_4b_inst_tbl;
        uint8_t quadModeSetting                           = kSerialNorQuadMode_NotConfig;

        uint32_t dummy_cycles = 0;
        uint8_t mode_cycles   = 0;
        uint32_t address_bits = 24U;

        spifi_get_page_sector_size_from_sfdp(handle, tbl);

        if (param_tbl->misc.address_bits == 2U)
        {
            memHandle->commandType = kSPIFI_CommandOpcodeAddrFourBytes;
        }
        else
        {
            memHandle->commandType = kSPIFI_CommandOpcodeAddrThreeBytes;
        }

        if (handle->bytesInMemorySize > SPIFI_MAX_24BIT_ADDRESSING_SIZE)
        {
            address_bits                                 = 32U;
            memHandle->commandSet.pageWriteMemoryCommand = kSerialNorCmd_WriteMemoryA32;
            memHandle->commandSet.readMemoryCommand      = kSerialNorCmd_ReadMemoryA32;
        }

        memHandle->readmemCommandFormt = (spifi_command_format_t)memConfig->cmd_format;

        if (kSPIFI_CommandAllSerial != memHandle->readmemCommandFormt)
        {
            if (kSPIFI_CommandOpcodeSerial == memHandle->readmemCommandFormt &&
                param_tbl->misc.supports_1_4_4_fast_read)
            {
                mode_cycles  = param_tbl->read_1_4_info.mode_clocks_1_4_4_read;
                dummy_cycles = param_tbl->read_1_4_info.dummy_clocks_1_4_4_read;
                /* Calculate intermediate bytes precede the data */
                memHandle->intermediateLen              = (mode_cycles + dummy_cycles) / 2U;
                memHandle->commandSet.readMemoryCommand = kSerialNorCmd_ReadMemorySDR_1_4_4;
                if ((address_bits == 32U) && flash_4b_tbl->cmd_4byte_support_info.support_1_4_4_fast_read)
                {
                    memHandle->commandSet.readMemoryCommand = kSerialNorCmd_ReadMemorySDR_1_4_4_A32;
                }
            }
            else if (kSPIFI_CommandDataQuad == memHandle->readmemCommandFormt &&
                     param_tbl->misc.support_1_1_4_fast_read)
            {
                mode_cycles  = param_tbl->read_1_4_info.mode_clocks_1_1_4_read;
                dummy_cycles = param_tbl->read_1_4_info.dummy_clocks_1_1_4_read;
                /* Calculate intermediate bytes precede the data */
                memHandle->intermediateLen              = (mode_cycles + dummy_cycles) / 8U;
                memHandle->commandSet.readMemoryCommand = kSerialNorCmd_ReadMemorySDR_1_1_4;
                if ((address_bits == 32U) && flash_4b_tbl->cmd_4byte_support_info.support_1_1_4_fast_read)
                {
                    memHandle->commandSet.readMemoryCommand = kSerialNorCmd_ReadMemorySDR_1_1_4_A32;
                }
            }

            /* Ideally, we only need one condition here, however, for some Flash devices that actually support JESD216A
             before the stanadard is publicly released, the JESD minor revsion is still the initial version. That is why
             we use two conditions to handle below logic. */
            if ((tbl->standard_version >= kSfdp_Version_Minor_A) ||
                (tbl->flash_param_tbl_size >= kSfdp_BasicProtocolTableSize_RevA))
            {
                switch (param_tbl->mode_4_4_info.quad_enable_requirement)
                {
                    case 1:
                    case 4:
                    case 5:
                        quadModeSetting = kSerialNorQuadMode_StatusReg2_Bit1;
                        break;
                    case 2:
                        quadModeSetting = kSerialNorQuadMode_StatusReg1_Bit6;
                        break;
                    case 3:
                        quadModeSetting = kSerialNorQuadMode_StatusReg2_Bit7;
                        break;
                    case 6:
                        quadModeSetting = kSerialNorQuadMode_StatusReg2_Bit1_0x31;
                        break;
                    case 0:
                    default:
                        quadModeSetting = kSerialNorQuadMode_NotConfig;
                        break;
                }
            }
            else
            {
                /* Use quad mode setting paraments provided in the configure option block.
                 This setting is used for the flash devices which only support JESD216 initial version. */
                quadModeSetting = memConfig->quad_mode_setting;
            }
            switch (quadModeSetting)
            {
                /* Need write status register1 and register2 at the same time with command 0x01.
                 See JESD216B doc for more details. */
                case kSerialNorQuadMode_StatusReg2_Bit1:
                    config->isQuadDualNeedEnable   = true;
                    config->writeTwoStausBytes     = true;
                    config->quadDualreadCommand    = kSerialNorCmd_ReadSecStatus_35;
                    config->quadDualEnableBitShift = 1;
                    break;
                /* Need write status register1 directly with command 0x01. */
                case kSerialNorQuadMode_StatusReg1_Bit6:
                    config->isQuadDualNeedEnable   = true;
                    config->writeTwoStausBytes     = false;
                    config->quadDualreadCommand    = kSerialNorCmd_ReadStatus;
                    config->quadDualEnableCommand  = kSerialNorCmd_WriteStatus;
                    config->quadDualEnableBitShift = 6;
                    break;
                /* Need write status register2 directly with special command 0x3E. */
                case kSerialNorQuadMode_StatusReg2_Bit7:
                    config->isQuadDualNeedEnable   = true;
                    config->writeTwoStausBytes     = false;
                    config->quadDualreadCommand    = kSerialNorCmd_ReadSecStatus_3F;
                    config->quadDualEnableCommand  = kSerialNorCmd_WriteSecStatus_3E;
                    config->quadDualEnableBitShift = 7;
                    break;
                /* Need write status register2 directly with special command 0x31. */
                case kSerialNorQuadMode_StatusReg2_Bit1_0x31:
                    config->isQuadDualNeedEnable   = true;
                    config->writeTwoStausBytes     = false;
                    config->quadDualreadCommand    = kSerialNorCmd_ReadSecStatus_35;
                    config->quadDualEnableCommand  = kSerialNorCmd_WriteSecStatus_31;
                    config->quadDualEnableBitShift = 1;
                    break;
                case kSerialNorQuadMode_NotConfig:
                default:
                    config->isQuadDualNeedEnable = false;
                    break;
            }
        }

        status = kStatus_Success;
    } while (0);

    return status;
}

static status_t spifi_nor_erase_sector(nor_handle_t *handle, uint32_t address)
{
    if ((!handle) || (!handle->deviceSpecific))
    {
        return kStatus_InvalidArgument;
    }

    spifi_command_t cmd;
    status_t status;
    spifi_mem_nor_handle_t *memSpifiHandler = (spifi_mem_nor_handle_t *)(handle->deviceSpecific);
    SPIFI_Type *base                        = (SPIFI_Type *)handle->driverBaseAddr;
    uint8_t opcode                          = memSpifiHandler->commandSet.eraseSectorCommand;
    address &= ~(handle->bytesInSectorSize - 1);
    spifi_command_type_t cmdType = memSpifiHandler->commandType;

    /* Enable write operation. */
    status = spifi_nor_write_enable(base, memSpifiHandler, kSPIFI_CommandAllSerial);
    if (kStatus_Success != status)
    {
        return status;
    }
    /* Set address. */
    SPIFI_SetCommandAddress(base, address);

    /* Do erase operation. */
    cmd.dataLen           = 0;
    cmd.isPollMode        = false;
    cmd.direction         = kSPIFI_DataOutput;
    cmd.intermediateBytes = 0;
    cmd.format            = kSPIFI_CommandAllSerial;
    cmd.type              = cmdType;
    cmd.opcode            = opcode;
    SPIFI_SetCommand(base, &cmd);

    /* Check if finished. */
    status = spifi_check_norflash_finish(base, memSpifiHandler);

    return status;
}

status_t Nor_Flash_Init(nor_config_t *config, nor_handle_t *handle)
{
    assert(config);
    assert(handle);

    /* Set SPIFI configuration parameter. */
    SPIFI_Type *base = (SPIFI_Type *)config->driverBaseAddr;
    status_t status;
    jedec_info_table_t jedec_info_tbl;
    spifi_mem_nor_config_t *memSpiNorConfig = (spifi_mem_nor_config_t *)config->memControlConfig;
    spifi_nor_config_t spiNorConfig;

    /* Clear spifi nor flash configuration. */
    memset(&spiNorConfig, 0, sizeof(spifi_nor_config_t));
    memset(&spifi_handle, 0, sizeof(spifi_handle));
    /* Set default configuration to configuration block. */
    SPIFI_GetDefaultConfig(&spiNorConfig.memConfig);
    /* Store parameters in handler. */
    handle->driverBaseAddr                         = config->driverBaseAddr;
    handle->deviceSpecific                         = (void *)&spifi_handle;
    handle->bytesInMemorySize                      = SPIFI_MAX_24BIT_ADDRESSING_SIZE;
    spifi_handle.commandSet.readStatusCommand      = kSerialNorCmd_ReadStatus;
    spifi_handle.commandSet.eraseSectorCommand     = kSerialNorCmd_EraseSector;
    spifi_handle.commandSet.pageWriteMemoryCommand = kSerialNorCmd_WriteMemory;
    spifi_handle.commandSet.readMemoryCommand      = kSerialNorCmd_ReadMemory;
    spifi_handle.commandSet.writeDisableCommand    = kSerialNorCmd_WriteDisable;
    spifi_handle.commandSet.writeEnableCommand     = kSerialNorCmd_WriteEnable;
    spifi_handle.commandSet.writeStatusCommand     = kSerialNorCmd_WriteStatus;
    spifi_handle.commandSet.eraseChipCommand       = kSerialNorCmd_EraseChip;

    /* SPIFI Clock setting with the low frequency to get the sfdp first. */
    memSpiNorConfig->clockInit(kSpifiNorClockInit_Sdfp);
    /* Init SPIFI NOR flash based on default configure value for reading SFDP */
    SPIFI_Init(base, &spiNorConfig.memConfig);

    /* Read SFDP information via SPIFI */
    status = spifi_nor_read_sfdp_info(base, &jedec_info_tbl);
    if (status != kStatus_Success)
    {
        return status;
    }
    /* Parse SFDP parameters and then fill into SPIFI Serial NOR Configuration Block */
    status = spifi_nor_parse_sfdp(&spiNorConfig, &jedec_info_tbl, memSpiNorConfig, handle);
    if (status != kStatus_Success)
    {
        return status;
    }

    /* SPIFI Clock setting with the maximum frequency. */
    memSpiNorConfig->clockInit(kSpifiNorClockInit_Max);
    /* Switch to quad mode if it is needed. */
    if (true == spiNorConfig.isQuadDualNeedEnable)
    {
        status = spifi_nor_quad_mode_enable(base, &spiNorConfig, &spifi_handle);
        if (status != kStatus_Success)
        {
            return status;
        }
    }
    /* Default disable write protection. */
    spifi_nor_writeprotect_disable(base, &spifi_handle);
    return status;
}

status_t Nor_Flash_Page_Program(nor_handle_t *handle, uint32_t address, uint8_t *buffer)
{
    if (!buffer)
    {
        return kStatus_InvalidArgument;
    }

    uint32_t data, i;
    spifi_command_t cmd;
    status_t status;
    spifi_mem_nor_handle_t *memSpifiHandler = (spifi_mem_nor_handle_t *)(handle->deviceSpecific);
    uint32_t pageSize                       = handle->bytesInPageSize;
    SPIFI_Type *base                        = (SPIFI_Type *)handle->driverBaseAddr;

    /* Enable write operation. */
    status = spifi_nor_write_enable(base, memSpifiHandler, kSPIFI_CommandAllSerial);
    if (kStatus_Success != status)
    {
        return status;
    }

    /* Keep address as page align. */
    address &= ~(pageSize - 1U);
    SPIFI_SetCommandAddress(base, address);

    cmd.dataLen           = pageSize;
    cmd.isPollMode        = false;
    cmd.direction         = kSPIFI_DataOutput;
    cmd.intermediateBytes = 0;
    cmd.format            = kSPIFI_CommandAllSerial;
    cmd.type              = memSpifiHandler->commandType;
    cmd.opcode            = memSpifiHandler->commandSet.pageWriteMemoryCommand;
    SPIFI_SetCommand(base, &cmd);
    for (i = 0; i < pageSize; i += 4U)
    {
        data = *(uint32_t *)buffer;
        buffer += 4U;
        SPIFI_WriteData(base, data);
    }

    status = spifi_check_norflash_finish(base, memSpifiHandler);

    return status;
}

status_t Nor_Flash_Erase_Sector(nor_handle_t *handle, uint32_t address, uint32_t size_Byte)
{
    uint32_t endAddress = address + size_Byte;
    status_t status;

    if (endAddress > FSL_FEATURE_SPIFI_START_ADDR + handle->bytesInMemorySize)
    {
        return kStatus_InvalidArgument;
    }

    address &= ~(handle->bytesInSectorSize - 1);

    status = spifi_nor_erase_sector(handle, address);

    return status;
}

status_t Nor_Flash_Erase_Block(nor_handle_t *handle, uint32_t address, uint32_t size_Byte)
{
    uint32_t endAddress = address + size_Byte;
    status_t status;

    if (endAddress > FSL_FEATURE_SPIFI_START_ADDR + handle->bytesInMemorySize)
    {
        return kStatus_InvalidArgument;
    }

    address &= ~(handle->bytesInSectorSize - 1);

    while (address < endAddress)
    {
        status = spifi_nor_erase_sector(handle, address);
        if (kStatus_Success != status)
        {
            return status;
        }
        address += handle->bytesInSectorSize;
    }

    return status;
}

status_t Nor_Flash_Erase_Chip(nor_handle_t *handle)
{
    if ((!handle) || (!handle->deviceSpecific))
    {
        return kStatus_InvalidArgument;
    }

    spifi_command_t cmd;
    spifi_command_type_t cmdType = kSPIFI_CommandOpcodeOnly;
    status_t status;
    spifi_mem_nor_handle_t *memSpifiHandler = (spifi_mem_nor_handle_t *)(handle->deviceSpecific);
    SPIFI_Type *base                        = (SPIFI_Type *)handle->driverBaseAddr;
    uint8_t opcode                          = memSpifiHandler->commandSet.eraseChipCommand;

    /* Enable write operation. */
    status = spifi_nor_write_enable(base, memSpifiHandler, kSPIFI_CommandAllSerial);
    if (kStatus_Success != status)
    {
        return status;
    }
    /* Set address. */
    SPIFI_SetCommandAddress(base, FSL_FEATURE_SPIFI_START_ADDR);

    /* Do erase operation. */
    cmd.dataLen           = 0;
    cmd.isPollMode        = false;
    cmd.direction         = kSPIFI_DataOutput;
    cmd.intermediateBytes = 0;
    cmd.format            = kSPIFI_CommandAllSerial;
    cmd.type              = cmdType;
    cmd.opcode            = opcode;
    SPIFI_SetCommand(base, &cmd);

    /* Check if finished. */
    status = spifi_check_norflash_finish(base, memSpifiHandler);

    return status;
}

status_t Nor_Flash_Read(nor_handle_t *handle, uint32_t address, uint8_t *buffer, uint32_t length)
{
    /* Parameter check. */
    if ((!handle) || (!buffer))
    {
        return kStatus_InvalidArgument;
    }

    spifi_command_t cmd;
    status_t status                         = kStatus_Success;
    spifi_mem_nor_handle_t *memSpifiHandler = (spifi_mem_nor_handle_t *)(handle->deviceSpecific);
    SPIFI_Type *base                        = (SPIFI_Type *)handle->driverBaseAddr;

    cmd.dataLen           = 0;
    cmd.isPollMode        = false;
    cmd.direction         = kSPIFI_DataInput;
    cmd.intermediateBytes = memSpifiHandler->intermediateLen;
    cmd.format            = memSpifiHandler->readmemCommandFormt;
    cmd.type              = memSpifiHandler->commandType;
    cmd.opcode            = memSpifiHandler->commandSet.readMemoryCommand;
    SPIFI_SetMemoryCommand(base, &cmd);

    memcpy(buffer, (void *)address, length);
    /* Reset to command mode. */
    SPIFI_ResetCommand(base);

    return status;
}
