/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_ROMAPI_FLEXSPI_H_
#define _FSL_ROMAPI_FLEXSPI_H_

#include <stdlib.h>
#include <stdint.h>
#include "fsl_common.h"

typedef struct
{
    uint8_t time_100ps;  // Data valid time, in terms of 100ps
    uint8_t delay_cells; // Data valid time, in terms of delay cells
} flexspi_dll_time_t;

//!@brief FlexSPI Pad Configuration Override
typedef struct
{
    uint8_t pu_pd_override_en;
    uint8_t pu_pd_value;
    uint8_t sr_config_override_en;
    uint8_t sr_config_value;
} flexspi_pad_config_override_t;

//!@brief FlexSPI LUT Sequence structure
typedef struct _lut_sequence
{
    uint8_t seqNum; //!< Sequence Number, valid number: 1-16
    uint8_t seqId;  //!< Sequence Index, valid number: 0-15
    uint16_t reserved;
} flexspi_lut_seq_t;

//!@brief FlexSPI Memory Configuration Block
typedef struct _FlexSPIConfig
{
    uint32_t tag;               //!< [0x000-0x003] Tag, fixed value 0x42464346UL
    uint32_t version;           //!< [0x004-0x007] Version,[31:24] -'V', [23:16] - Major, [15:8] - Minor, [7:0] - bugfix
    uint32_t reserved0;         //!< [0x008-0x00b] Reserved for future use
    uint8_t readSampleClkSrc;   //!< [0x00c-0x00c] Read Sample Clock Source, valid value: 0/1/3
    uint8_t csHoldTime;         //!< [0x00d-0x00d] CS hold time, default value: 3
    uint8_t csSetupTime;        //!< [0x00e-0x00e] CS setup time, default value: 3
    uint8_t columnAddressWidth; //!< [0x00f-0x00f] Column Address with, for HyperBus protocol, it is fixed to 3, For
    //! Serial NAND, need to refer to datasheet
    uint8_t deviceModeCfgEnable; //!< [0x010-0x010] Device Mode Configure enable flag, 1 - Enable, 0 - Disable
    uint8_t deviceModeType; //!< [0x011-0x011] Specify the configuration command type:Quad Enable, DPI/QPI/OPI switch,
    //! Generic configuration, etc.
    uint16_t waitTimeCfgCommands; //!< [0x012-0x013] Wait time for all configuration commands, unit: 100us, Used for
    //! DPI/QPI/OPI switch or reset command
    flexspi_lut_seq_t deviceModeSeq; //!< [0x014-0x017] Device mode sequence info, [7:0] - LUT sequence id, [15:8] - LUt
    //! sequence number, [31:16] Reserved
    uint32_t deviceModeArg;    //!< [0x018-0x01b] Argument/Parameter for device configuration
    uint8_t configCmdEnable;   //!< [0x01c-0x01c] Configure command Enable Flag, 1 - Enable, 0 - Disable
    uint8_t configModeType[3]; //!< [0x01d-0x01f] Configure Mode Type, similar as deviceModeTpe
    flexspi_lut_seq_t
        configCmdSeqs[3]; //!< [0x020-0x02b] Sequence info for Device Configuration command, similar as deviceModeSeq
    uint32_t reserved1;   //!< [0x02c-0x02f] Reserved for future use
    uint32_t configCmdArgs[3];     //!< [0x030-0x03b] Arguments/Parameters for device Configuration commands
    uint32_t reserved2;            //!< [0x03c-0x03f] Reserved for future use
    uint32_t controllerMiscOption; //!< [0x040-0x043] Controller Misc Options, see Misc feature bit definitions for more
    //! details
    uint8_t deviceType;    //!< [0x044-0x044] Device Type:  See Flash Type Definition for more details
    uint8_t sflashPadType; //!< [0x045-0x045] Serial Flash Pad Type: 1 - Single, 2 - Dual, 4 - Quad, 8 - Octal
    uint8_t serialClkFreq; //!< [0x046-0x046] Serial Flash Frequencey, device specific definitions, See System Boot
    //! Chapter for more details
    uint8_t lutCustomSeqEnable; //!< [0x047-0x047] LUT customization Enable, it is required if the program/erase cannot
    //! be done using 1 LUT sequence, currently, only applicable to HyperFLASH
    uint32_t reserved3[2]; //!< [0x048-0x04f] Reserved for future use
    uint32_t sflashA1Size; //!< [0x050-0x053] Size of Flash connected to A1
    uint32_t sflashA2Size; //!< [0x054-0x057] Size of Flash connected to A2 (unused/not applicable on RW610)
    uint32_t sflashB1Size; //!< [0x058-0x05b] Size of Flash connected to B1
    uint32_t sflashB2Size; //!< [0x05c-0x05f] Size of Flash connected to B2 (unused/not applicable on RW610)
    flexspi_pad_config_override_t csPadSettingOverride;   //!< [0x060-0x063] CS pad setting override value
    flexspi_pad_config_override_t sclkPadSettingOverride; //!< [0x064-0x067] SCK pad setting override value
    flexspi_pad_config_override_t dataPadSettingOverride; //!< [0x068-0x06b] data pad setting override value
    flexspi_pad_config_override_t dqsPadSettingOverride;  //!< [0x06c-0x06f] DQS pad setting override value
    uint32_t timeoutInMs;                                 //!< [0x070-0x073] Timeout threshold for read status command
    uint32_t commandInterval;                             //!< [0x074-0x077] CS deselect interval between two commands
    flexspi_dll_time_t dataValidTime[2]; //!< [0x078-0x07b] CLK edge to data valid time for PORT A and PORT B
    uint16_t busyOffset;                 //!< [0x07c-0x07d] Busy offset, valid value: 0-31
    uint16_t busyBitPolarity; //!< [0x07e-0x07f] Busy flag polarity, 0 - busy flag is 1 when flash device is busy, 1 -
    //! busy flag is 0 when flash device is busy
    uint32_t lookupTable[64];           //!< [0x080-0x17f] Lookup table holds Flash command sequences
    flexspi_lut_seq_t lutCustomSeq[12]; //!< [0x180-0x1af] Customizable LUT Sequences
    uint32_t dll0CrVal;                 //!> [0x1b0-0x1b3] Customizable DLL0CR setting
    uint32_t dll1CrVal;                 //!> [0x1b4-0x1b7] Customizable DLL1CR setting
    uint32_t reserved4[2];              //!< [0x1b8-0x1bf] Reserved for future use
} flexspi_mem_config_t;

typedef enum _FlexSPIOperationType
{
    kFlexSpiOperation_Command, //!< FlexSPI operation: Only command, both TX and
    //! RX buffer are ignored.
    kFlexSpiOperation_Config, //!< FlexSPI operation: Configure device mode, the
    //! TX FIFO size is fixed in LUT.
    kFlexSpiOperation_Write, //!< FlexSPI operation: Write,  only TX buffer is
    //! effective
    kFlexSpiOperation_Read, //!< FlexSPI operation: Read, only Rx Buffer is
    //! effective.
    kFlexSpiOperation_End = kFlexSpiOperation_Read,
} flexspi_operation_t;

//!@brief FlexSPI Transfer Context
typedef struct _FlexSpiXfer
{
    flexspi_operation_t operation; //!< FlexSPI operation
    uint32_t baseAddress;          //!< FlexSPI operation base address
    uint32_t seqId;                //!< Sequence Id
    uint32_t seqNum;               //!< Sequence Number
    bool isParallelModeEnable;     //!< Is a parallel transfer
    bool keepState;                //!< Keep the data in the FIFO before triggering the operation
    uint32_t *txBuffer;            //!< Tx buffer
    uint32_t txSize;               //!< Tx size in bytes
    uint32_t *rxBuffer;            //!< Rx buffer
    uint32_t rxSize;               //!< Rx size in bytes
} flexspi_xfer_t;

/*
 *  Serial NOR configuration block
 */
typedef struct _flexspi_nor_config
{
    flexspi_mem_config_t memConfig; //!< Common memory configuration info via FlexSPI
    uint32_t pageSize;              //!< Page size of Serial NOR
    uint32_t sectorSize;            //!< Sector size of Serial NOR
    uint8_t ipcmdSerialClkFreq;     //!< Clock frequency for IP command
    uint8_t isUniformBlockSize;     //!< Sector/Block size is the same
    uint8_t isDataOrderSwapped;     //!< Data order (D0, D1, D2, D3) is swapped (D1,D0, D3, D2)
    uint8_t reserved0[1];           //!< Reserved for future use
    uint8_t serialNorType;          //!< Serial NOR Flash type: 0/1/2/3
    uint8_t needExitNoCmdMode;      //!< Need to exit NoCmd mode before other IP command
    uint8_t halfClkForNonReadCmd;   //!< Half the Serial Clock for non-read command: true/false
    uint8_t needRestoreNoCmdMode;   //!< Need to Restore NoCmd mode after IP commmand execution
    uint32_t blockSize;             //!< Block size
    uint32_t flashStateCtx;         //!< Flash State Context
    uint32_t reserve2[10];          //!< Reserved for future use
} flexspi_nor_config_t;

/*
 * Serial NOR Configuration Option
 */
typedef struct _serial_nor_config_option
{
    union
    {
        struct
        {
            uint32_t max_freq : 4;          //!< Maximum supported Frequency
            uint32_t misc_mode : 4;         //!< miscellaneous mode
            uint32_t quad_mode_setting : 4; //!< Quad mode setting
            uint32_t cmd_pads : 4;          //!< Command pads
            uint32_t query_pads : 4;        //!< SFDP read pads
            uint32_t device_type : 4;       //!< Device type
            uint32_t option_size : 4;       //!< Option size, in terms of uint32_t, size = (option_size + 1) * 4
            uint32_t tag : 4;               //!< Tag, must be 0x0C
        } B;
        uint32_t U;
    } option0;

    union
    {
        struct
        {
            uint32_t dummy_cycles : 8;     //!< Dummy cycles before read
            uint32_t status_override : 8;  //!< Override status register value during device mode configuration
            uint32_t pinmux_group : 4;     //!< The pinmux group selection
            uint32_t dqs_pinmux_group : 4; //!< The DQS Pinmux Group Selection
            uint32_t drive_strength : 4;   //!< The Drive Strength of FlexSPI Pads
            uint32_t flash_connection : 4; //!< Flash connection option: 0 - Single Flash connected to port A, 1 -
            //! Parallel mode, 2 - Single Flash connected to Port B
        } B;
        uint32_t U;
    } option1;

} serial_nor_config_option_t;

//!@brief FLEXSPI Flash driver API Interface
typedef struct
{
    uint32_t version;
    status_t (*init)(uint32_t instance, flexspi_nor_config_t *config);
    status_t (*wait_busy)(uint32_t instance, flexspi_nor_config_t *config, uint32_t address, bool keepState);
    status_t (*page_program)(
        uint32_t instance, flexspi_nor_config_t *config, uint32_t dstAddr, const uint32_t *src, bool keepState);
    status_t (*erase_all)(uint32_t instance, flexspi_nor_config_t *config);
    status_t (*erase)(uint32_t instance, flexspi_nor_config_t *config, uint32_t start, uint32_t length);
    status_t (*erase_sector)(uint32_t instance, flexspi_nor_config_t *config, uint32_t address);
    status_t (*erase_block)(uint32_t instance, flexspi_nor_config_t *config, uint32_t address);
    status_t (*read)(uint32_t instance, flexspi_nor_config_t *config, uint32_t *dst, uint32_t start, uint32_t bytes);
    void (*config_clock)(uint32_t instance, uint32_t freqOption, uint32_t sampleClkMode);
    status_t (*set_clock_source)(uint32_t clockSrc);
    status_t (*get_config)(uint32_t instance, flexspi_nor_config_t *config, serial_nor_config_option_t *option);
    void (*hw_reset)(uint32_t instance, uint32_t reset_logic);
    status_t (*xfer)(uint32_t instance, flexspi_xfer_t *xfer);
    status_t (*update_lut)(uint32_t instance, uint32_t seqIndex, const uint32_t *lutBase, uint32_t numberOfSeq);
    status_t (*partial_program)(uint32_t instance,
                                flexspi_nor_config_t *config,
                                uint32_t dstAddr,
                                const uint32_t *src,
                                uint32_t length,
                                bool keepState);
} flexspi_nor_flash_driver_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

uint32_t flexspi_nor_flash_version(void);

//!@brief Initialize Serial NOR devices via FlexSPI
status_t flexspi_nor_flash_init(uint32_t instance, flexspi_nor_config_t *config);

//!@brief Wait until Serial NOR device is idle
status_t flexspi_nor_flash_wait_busy(uint32_t instance, flexspi_nor_config_t *config, uint32_t address, bool keepState);
//!@brief Program data to Serial NOR via FlexSPI
status_t flexspi_nor_flash_page_program(
    uint32_t instance, flexspi_nor_config_t *config, uint32_t dstAddr, const uint32_t *src, bool keepState);

//!@brief Erase all the Serial NOR devices connected on FlexSPI
status_t flexspi_nor_flash_erase_all(uint32_t instance, flexspi_nor_config_t *config);

//!@brief Erase Flash Region specified by address and length
status_t flexspi_nor_flash_erase(uint32_t instance, flexspi_nor_config_t *config, uint32_t start, uint32_t length);

//!@brief Erase one sector specified by address
status_t flexspi_nor_flash_erase_sector(uint32_t instance, flexspi_nor_config_t *config, uint32_t address);

//!@brief Erase one block specified by address
status_t flexspi_nor_flash_erase_block(uint32_t instance, flexspi_nor_config_t *config, uint32_t address);

//!@brief Read data from Serial NOR
status_t flexspi_nor_flash_read(
    uint32_t instance, flexspi_nor_config_t *config, uint32_t *dst, uint32_t start, uint32_t bytes);

//!@brief Configure Clock for FlexSPI
void flexspi_clock_config(uint32_t instance, uint32_t freq, uint32_t sampleClkMode);

//!@brief Set the clock source for FlexSPI NOR
status_t flexspi_nor_set_clock_source(uint32_t clockSource);

//!@brief Get FlexSPI NOR Configuration Block based on specified option
status_t flexspi_nor_get_config(uint32_t instance, flexspi_nor_config_t *config, serial_nor_config_option_t *option);

//!@brief Reset FlexSPI NOR Flash
void flexspi_nor_hw_reset(uint32_t instance, uint32_t reset_logic);

//!@brief Perform FlexSPI command
status_t flexspi_command_xfer(uint32_t instance, flexspi_xfer_t *xfer);

//!@brief Configure FlexSPI Lookup table
status_t flexspi_update_lut(uint32_t instance, uint32_t seqIndex, const uint32_t *lutBase, uint32_t numberOfSeq);

//!@brief Partially Program data to Serial NOR via FlexSPI
status_t flexspi_nor_flash_partial_program(uint32_t instance,
                                           flexspi_nor_config_t *config,
                                           uint32_t dstAddr,
                                           const uint32_t *src,
                                           uint32_t length,
                                           bool keepState);

#endif /* _FSL_ROMAPI_FLEXSPI_H_ */
