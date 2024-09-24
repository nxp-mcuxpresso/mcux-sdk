/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_xspi.h"
#include "fsl_sfdp_parser.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define NOR_CMD_LUT_SEQ_IDX_READ        0U  /*!< Read LUT sequence id in lookupTable stored in config block*/
#define NOR_CMD_LUT_SEQ_IDX_READSTATUS  1U  /*!< Read Status LUT sequence id in lookupTable stored in config block*/
#define NOR_CMD_LUT_SEQ_IDX_WRITESTATUS 2U  /*!< Write Status LUT sequence id in lookupTable stored in config block*/
#define NOR_CMD_LUT_SEQ_IDX_WRITEENABLE 3U  /*!< Write enable LUT sequence id in lookupTable stored in config block*/
#define NOR_CMD_LUT_SEQ_IDX_WRITECONFIG                                                                              \
    4U                                      /*!< Write configuration LUT sequence id in lookupTable stored in config \
                                               block*/
#define NOR_CMD_LUT_SEQ_IDX_ERASESECTOR 5U  /*!< Erase sector LUT sequence id in lookupTable stored in config block*/
#define NOR_CMD_LUT_SEQ_IDX_READCONFIG                                                                              \
    6U                                      /*!< Read configuration LUT sequence id in lookupTable stored in config \
                                               block*/

#define NOR_CMD_LUT_SEQ_IDX_RESTORESPI                                                                              \
    7U                                      /*!< Restore standard SPI mode LUT sequence id in lookupTable stored in \
                                               config block*/
#define NOR_CMD_LUT_SEQ_IDX_READID                                                                                   \
    8U                                      /*!< Read manifacture ID LUT sequence id in lookupTable stored in config \
                                               block*/
#define NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM 9U  /*!< Page program LUT sequence id in lookupTable stored in config block*/
#define NOR_CMD_LUT_SEQ_IDX_CHIPERASE   11U /*!< Chip erase LUT sequence id in lookupTable stored in config block*/
#define NOR_CMD_LUT_SEQ_IDX_ERASEBLOCK  12U /*!< Block erase LUT sequence id in lookupTable stored in config block*/

#define NOR_CMD_LUT_SEQ_IDX_ALT       (13U)

#define NOR_CMD_LUT_SEQ_IDX_READ_SFDP                                                                          \
    13U                                     /*!< Read SFDP information sequence id in lookupTable id stored in \
                                               config block*/
#define NOR_CMD_LUT_SEQ_IDX_EXIT_NOCMD \
    15U /*!< Exit 0-4-4/0-8-8 mode sequence id in lookupTable stored in config block*/

/*!
 * @brief The structure of AHB access configuration.
 * 
 */
typedef struct _xspi_nor_ahb_access_config
{
    bool enableAhbWrite; /*!< Enable AHB write to external NOR flash. */
    xspi_ahbBuffer_config_t ahbBuffer0Config;  /*!< AHB buffer 0 configuration. */
    xspi_ahbBuffer_config_t ahbBuffer1Config;  /*!< AHB buffer 1 configuration. */
    xspi_ahbBuffer_config_t ahbBuffer2Config;  /*!< AHB buffer 2 configuration. */
    xspi_ahbBuffer_config_t ahbBuffer3Config;  /*!< AHB buffer 3 configuration. */
    bool enablePrefetch;   /*!< Specify if enable prefetch.  */
} xspi_nor_ahb_access_config_t;

/*!
 * @brief The structure of IP access configuration.
 * 
 */
typedef struct _xspi_nor_ip_access_config
{
    xspi_sfp_frad_config_t *ptrSfpFradConfig; /*!< Pointer to the variable in type of @ref xspi_sfp_mdad_config_t to
                                        set SFP MDAD feature, set as NULL to disable SFP MDAD feature.  */
    xspi_sfp_mdad_config_t *ptrSfpMdadConfig; /*!< Pointer to the variable in type of @ref xspi_sfp_frad_config_t to
                                        set SFP FRAD feature, set as NULL to disable SFP FRAD feature. */
    uint32_t ipAccessTimeoutValue;            /*!< Specify the maximum time in IPS clock cycles for XSPI to wait fro an
                                                ongoing write or read command to complete before terminating the command. */
    uint32_t sfpArbitrationLockTimeoutValue;  /*!< Specify the time in IPS clock cycles before an unreleased
                                            arbitration triggers a timeout error. */
} xspi_nor_ip_access_config_t;

/*!
 * @brief The structure of xspi memory.
 * 
 */
typedef struct _xspi_memory_config
{
    bool enableXspiDoze;        /*!< Enable/disable XSPI Doze mode. */
    uint32_t *ptrCustomLut;     /*!< Pointer to the costumed LUT. */
    xspi_pad_t numPadUsed;      /*!< Number of data pad. */
    bool enableClknPad;         /*!< Enable/disable CLKn pad. */
    xspi_sample_clk_config_t sampleClkConfig; /*!< Sample clock configuration. */
    xspi_device_addr_mode_t addrMode;   /*!< Address mode of xspi. */
    uint32_t xspiRootClk;   /*!< The frequency of xspi clock. */
    xspi_target_group_t tgId;   /*!< Target ID used for IP access. */
    
    xspi_nor_ahb_access_config_t *ptrXspiNorAhbAccessConfig; /*!< Pointer to the AHB access configuration, set as NULL
                                                        to use default settings. */
    xspi_nor_ip_access_config_t  *ptrXspiNorIPAccessConfig; /*!< Pointer to the IP access configuration, set as NULL
                                                        to use default settings. */
} xspi_memory_config_t;

/*!
 * @brief xspi nor flash handle.
 */
typedef struct _xspi_mem_nor_handle
{
    xspi_target_group_t selectedTg;  /*!< Current selected target group. */
    xspi_device_status_reg_info_t norFlashStatusRegInfo;  /*!< Nor flash status register WIP bit information. */
    uint8_t addrSize;   /*!< Address size. */
    uint32_t sectorSizeInByte; /*!< Sector size in unit of byte. */
    uint32_t memSizeInByte; /*!< Nor flash size in unit of byte. */
    sfdp_protocol_type_t curProtocolType; /*!< Current protocol type. */
    sfdp_octal_dtr_cmd_type_t octalDTRCmdType; /*!< Octal DTR command type. */
    sfdp_handle_t *ptrSfdpHandle; /*!< Pointer to sfdp handle. */
    uint32_t clkFreq; /*!< Frequency of serial flash. */
} xspi_mem_nor_handle_t;
