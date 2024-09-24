/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_xspi_nor_flash.h"
#include "fsl_nor_flash.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define XSPI_INSTR_CMD_IDX   (0U)
#define XSPI_INSTR_RADDR_IDX (1U)
#define XSPI_INSTR_CADDR_IDX (2U)
#define XSPI_INSTR_READ_IDX  (3U)
#define XSPI_INSTR_WRITE_IDX (4U)
#define XSPI_INSTR_MODE_IDX  (5U)
#define XSPI_INSTR_MODE2_IDX (6U)
#define XSPI_INSTR_MODE4_IDX (7U)

const xspi_lut_instr_t g_xspiCommonInstr[2][8] = {
    {kXSPI_Command_SDR, kXSPI_Command_RADDR_SDR, kXSPI_Command_CADDR_SDR, kXSPI_Command_READ_SDR,
     kXSPI_Command_WRITE_SDR, kXSPI_Command_MODE_SDR, kXSPI_Command_MODE2_SDR, kXSPI_Command_MODE4_SDR},
    {kXSPI_Command_DDR, kXSPI_Command_RADDR_DDR, kXSPI_Command_CADDR_DDR, kXSPI_Command_READ_DDR,
     kXSPI_Command_WRITE_DDR, kXSPI_Command_MODE_DDR, kXSPI_Command_MODE2_DDR, kXSPI_Command_MODE4_DDR}};

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
typedef struct _lut_seq_entry
{
    uint32_t insrOperandPair1;
    uint32_t insrOperandPair2;
    uint32_t insrOperandPair3;
    uint32_t insrOperandPair4;
    uint32_t insrOperandPair5;
} lut_seq_entry_t;

typedef struct _lut_seq_instr_operand
{
    uint16_t operand : 8U;
    uint16_t padNum : 2U;
    uint16_t instr : 6U;
} lut_seq_instr_operand_t;
/*******************************************************************************
 * Variables
 ******************************************************************************/

XSPI_Type *curXSPIBase = NULL;
xspi_mem_nor_handle_t xspiMemNorHandle;

static uint32_t s_socXspiAmbaBase[] = XSPI_AMBA_BASES;

lut_seq_entry_t g_xspiLut[16] = {0UL};
/*******************************************************************************
 * Code
 ******************************************************************************/

static status_t XSPI_NOR_ReadSFDP(uint32_t address, uint32_t *buffer, uint32_t bytes)
{
    xspi_transfer_t flashXfer;
    status_t status = kStatus_InvalidArgument;

    uint32_t xspiInstanceId = XSPI_GetInstance(curXSPIBase);

    flashXfer.deviceAddress = s_socXspiAmbaBase[xspiInstanceId] + address;
    flashXfer.cmdType       = kXSPI_Read;
    flashXfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_READ_SFDP;
    flashXfer.data          = (uint32_t *)(void *)buffer;
    flashXfer.dataSize      = bytes;
    flashXfer.targetGroup   = xspiMemNorHandle.selectedTg; /* Target group selection is from application. */

    status = XSPI_TransferBlocking(curXSPIBase, &flashXfer);

    return status;
}

static status_t XSPI_NOR_ProbeNorFlashSfdpHeader(void)
{
    uint8_t sfdpLutIndex = 0U;
    xspi_device_config_t tmpNorFlashConfig;
    sfdp_protocol_type_t tmpProtocol = kSFDP_Protocol_1s1s1s;
    /* Data strobe used for 4s-4d-4d and 8D-8D-8D. */
    xspi_device_ddr_config_t tmpDeviceDDRConfig;

    struct _probedInfo
    {
        sfdp_protocol_type_t protocolMode;
        uint8_t addrWidth;
    } probedInfo[12] = {
        {kSFDP_Protocol_1s1s1s, 24U}, {kSFDP_Protocol_2s2s2s, 24U}, {kSFDP_Protocol_4s4s4s, 24U},
        {kSFDP_Protocol_4s4d4d, 24U}, {kSFDP_Protocol_8d8d8d, 32U}, {kSFDP_Protocol_8d8d8d, 32U},
        {kSFDP_Protocol_8d8d8d, 24U}, {kSFDP_Protocol_8d8d8d, 24U}, {kSFDP_Protocol_8s8s8s, 32U},
        {kSFDP_Protocol_8s8s8s, 32U}, {kSFDP_Protocol_8s8s8s, 24U}, {kSFDP_Protocol_8s8s8s, 24U},
    };
    /* Read SFDP command can be used with device supported mode if (1s-1s-1s), (2s-2s-2s),
          (4s-4s-4s), (4s-4d-4d) and (8D-8D-8D). For the (8D-8D-8D) mode, the instruction 5Ah and 50 MHz requirements
          remain the same, while 24 or 32 address bit, and a variable number of wait states may be used. */
    lut_seq_entry_t sfdp_lut[12] = {
        /* Read SFDP in 1s-1s-1s mode. */
        {
            XSPI_LUT_SEQ(kXSPI_Command_SDR, kXSPI_1PAD, 0x5A, kXSPI_Command_RADDR_SDR, kXSPI_1PAD, 24),
            XSPI_LUT_SEQ(kXSPI_Command_DUMMY_SDR, kXSPI_1PAD, 8, kXSPI_Command_READ_SDR, kXSPI_1PAD, 0xFF),
            0UL,
            0UL,
            0UL,
        },

        /* Read SFDP in 2s-2s-2s mode. */
        {
            XSPI_LUT_SEQ(kXSPI_Command_SDR, kXSPI_2PAD, 0x5A, kXSPI_Command_RADDR_SDR, kXSPI_2PAD, 24),
            XSPI_LUT_SEQ(kXSPI_Command_DUMMY_SDR, kXSPI_2PAD, 8, kXSPI_Command_READ_SDR, kXSPI_2PAD, 0xFF),
            0UL,
            0UL,
            0UL,
        },
        /* Read SFDP in 4s-4s-4s mode. */
        {
            XSPI_LUT_SEQ(kXSPI_Command_SDR, kXSPI_4PAD, 0x5A, kXSPI_Command_RADDR_SDR, kXSPI_4PAD, 24),
            XSPI_LUT_SEQ(kXSPI_Command_DUMMY_SDR, kXSPI_4PAD, 8, kXSPI_Command_READ_SDR, kXSPI_4PAD, 0xFF),
            0UL,
            0UL,
            0UL,
        },
        /* Read SFDP in 4s-4d-4d mode. */
        {
            XSPI_LUT_SEQ(kXSPI_Command_SDR, kXSPI_4PAD, 0x5A, kXSPI_Command_RADDR_DDR, kXSPI_4PAD, 24),
            XSPI_LUT_SEQ(kXSPI_Command_READ_DDR, kXSPI_4PAD, 0xFF, 0U, 0U, 0U),
            0UL,
            0UL,
            0UL,
        },
        /* Read SFDP in 8D-8D-8D mode, with extension is the inverse of the command and 32 bit address */
        {
            XSPI_LUT_SEQ(kXSPI_Command_DDR, kXSPI_8PAD, 0x5AU, kXSPI_Command_DDR, kXSPI_8PAD, 0xA5U),
            XSPI_LUT_SEQ(kXSPI_Command_RADDR_DDR, kXSPI_8PAD, 32U, kXSPI_Command_DUMMY_SDR, kXSPI_8PAD, 20U),
            XSPI_LUT_SEQ(kXSPI_Command_READ_DDR, kXSPI_8PAD, 0xFFU, 0U, 0U, 0U),
            0UL,
            0UL,
        },
        /* Read SFDP in 8D-8D-8D mode, with same extension cmd and 32 bit address */
        {
            XSPI_LUT_SEQ(kXSPI_Command_DDR, kXSPI_8PAD, 0x5A, kXSPI_Command_DDR, kXSPI_8PAD, 0x5A),
            XSPI_LUT_SEQ(kXSPI_Command_RADDR_DDR, kXSPI_8PAD, 32, kXSPI_Command_DUMMY_SDR, kXSPI_8PAD, 20U),
            XSPI_LUT_SEQ(kXSPI_Command_READ_DDR, kXSPI_8PAD, 0xFF, 0U, 0U, 0U),
            0UL,
            0UL,
        },
        /* Read SFDP in 8D-8D-8D mode, with same extension cmd and 24 bit address */
        {
            XSPI_LUT_SEQ(kXSPI_Command_DDR, kXSPI_8PAD, 0x5A, kXSPI_Command_DDR, kXSPI_8PAD, 0x5A),
            XSPI_LUT_SEQ(kXSPI_Command_RADDR_DDR, kXSPI_8PAD, 24, kXSPI_Command_DUMMY_SDR, kXSPI_8PAD, 20U),
            XSPI_LUT_SEQ(kXSPI_Command_READ_DDR, kXSPI_8PAD, 0xFF, 0U, 0U, 0U),
            0UL,
            0UL,
        },

        /* Read SFDP in 8D-8D-8D mode, with extension is the inverse of the command and 24 bit address */
        {
            XSPI_LUT_SEQ(kXSPI_Command_DDR, kXSPI_8PAD, 0x5A, kXSPI_Command_DDR, kXSPI_8PAD, 0xA5),
            XSPI_LUT_SEQ(kXSPI_Command_RADDR_DDR, kXSPI_8PAD, 24, kXSPI_Command_DUMMY_SDR, kXSPI_8PAD, 20U),
            XSPI_LUT_SEQ(kXSPI_Command_READ_DDR, kXSPI_8PAD, 0xFF, 0U, 0U, 0U),
            0UL,
            0UL,
        },
        /* Read SFDP in 8S-8S-8S mode, with extension is the inverse of the command and 32 bit address */
        {
            XSPI_LUT_SEQ(kXSPI_Command_SDR, kXSPI_8PAD, 0x5AU, kXSPI_Command_SDR, kXSPI_8PAD, 0xA5U),
            XSPI_LUT_SEQ(kXSPI_Command_RADDR_SDR, kXSPI_8PAD, 32U, kXSPI_Command_DUMMY_SDR, kXSPI_8PAD, 20U),
            XSPI_LUT_SEQ(kXSPI_Command_READ_SDR, kXSPI_8PAD, 0xFFU, 0U, 0U, 0U),
            0UL,
            0UL,
        },
        /* Read SFDP in 8S-8S-8S mode, with same extension cmd and 32 bit address */
        {
            XSPI_LUT_SEQ(kXSPI_Command_SDR, kXSPI_8PAD, 0x5A, kXSPI_Command_SDR, kXSPI_8PAD, 0x5A),
            XSPI_LUT_SEQ(kXSPI_Command_RADDR_SDR, kXSPI_8PAD, 32, kXSPI_Command_DUMMY_SDR, kXSPI_8PAD, 20U),
            XSPI_LUT_SEQ(kXSPI_Command_READ_SDR, kXSPI_8PAD, 0xFF, 0U, 0U, 0U),
            0UL,
            0UL,
        },
        /* Read SFDP in 8S-8S-8S mode, with same extension cmd and 24 bit address */
        {
            XSPI_LUT_SEQ(kXSPI_Command_SDR, kXSPI_8PAD, 0x5A, kXSPI_Command_SDR, kXSPI_8PAD, 0x5A),
            XSPI_LUT_SEQ(kXSPI_Command_RADDR_SDR, kXSPI_8PAD, 24, kXSPI_Command_DUMMY_SDR, kXSPI_8PAD, 20U),
            XSPI_LUT_SEQ(kXSPI_Command_READ_SDR, kXSPI_8PAD, 0xFF, 0U, 0U, 0U),
            0UL,
            0UL,
        },

        /* Read SFDP in 8S-8S-8S mode, with extension is the inverse of the command and 24 bit address */
        {
            XSPI_LUT_SEQ(kXSPI_Command_SDR, kXSPI_8PAD, 0x5A, kXSPI_Command_SDR, kXSPI_8PAD, 0xA5),
            XSPI_LUT_SEQ(kXSPI_Command_RADDR_SDR, kXSPI_8PAD, 24, kXSPI_Command_DUMMY_SDR, kXSPI_8PAD, 20U),
            XSPI_LUT_SEQ(kXSPI_Command_READ_SDR, kXSPI_8PAD, 0xFF, 0U, 0U, 0U),
            0UL,
            0UL,
        },
    };

    for (sfdpLutIndex = 0U; sfdpLutIndex < ARRAY_SIZE(sfdp_lut); sfdpLutIndex++)
    {
        tmpNorFlashConfig.addrMode                                                = kXSPI_DeviceByteAddressable;
        tmpNorFlashConfig.columnAddrWidth                                         = 0U;
        tmpNorFlashConfig.CSHoldTime                                              = 3U;
        tmpNorFlashConfig.CSSetupTime                                             = 3U;
        tmpNorFlashConfig.deviceInterface                                         = kXSPI_StrandardExtendedSPI;
        tmpNorFlashConfig.enableCASInterleaving                                   = false;
        tmpNorFlashConfig.enableCknPad                                            = false;
        tmpNorFlashConfig.interfaceSettings.strandardExtendedSPISettings.pageSize = 256U;
        tmpNorFlashConfig.ptrDeviceDdrConfig                                      = NULL;
        tmpNorFlashConfig.ptrDeviceRegInfo                                        = NULL;
        tmpNorFlashConfig.sampleClkConfig.dllConfig.dllMode                       = kXSPI_AutoUpdateMode;
        tmpNorFlashConfig.sampleClkConfig.dllConfig.useRefValue                   = true;
        tmpNorFlashConfig.sampleClkConfig.enableDQSLatency                        = false;
        tmpNorFlashConfig.sampleClkConfig.sampleClkSource                         = kXSPI_SampleClkFromDqsPadLoopback;
        tmpNorFlashConfig.deviceSize[0]                                           = 0x40;
        tmpNorFlashConfig.deviceSize[1]                                           = 0x40;
        tmpNorFlashConfig.xspiRootClk = xspiMemNorHandle.clkFreq; /* Set as 50MHz to read SFDP. */

        tmpProtocol = probedInfo[sfdpLutIndex].protocolMode;

        if (((uint32_t)tmpProtocol & 0x100UL) != 0UL)
        {
            tmpDeviceDDRConfig.enableDdr = true;
        }
        else
        {
            tmpDeviceDDRConfig.enableDdr = false;
        }

        if (sfdpLutIndex >= 3U)
        {
            tmpDeviceDDRConfig.enableByteSwapInOctalMode      = false;
            tmpDeviceDDRConfig.ddrDataAlignedClk              = kXSPI_DDRDataAlignedWith2xInternalRefClk;
            tmpNorFlashConfig.sampleClkConfig.sampleClkSource = kXSPI_SampleClkFromExternalDQS;
            tmpNorFlashConfig.ptrDeviceDdrConfig              = &tmpDeviceDDRConfig;
        }

        XSPI_SetDeviceConfig(curXSPIBase, &tmpNorFlashConfig);
        XSPI_EnableModule(curXSPIBase, true);

        XSPI_UpdateLUT(curXSPIBase, NOR_CMD_LUT_SEQ_IDX_READ_SFDP * 5U, &(sfdp_lut[sfdpLutIndex].insrOperandPair1), 5U);

        sfdp_ret_type_t ret;
        ret = SFDP_ReadSFDPHeader(xspiMemNorHandle.ptrSfdpHandle, XSPI_NOR_ReadSFDP);

        if ((ret == kSFDP_RET_Success) && (sfdpLutIndex < ARRAY_SIZE(sfdp_lut)))
        {
            /* successfully to read SFDP header from external device. */

            /* recode current protocol type and address width. */
            xspiMemNorHandle.curProtocolType = probedInfo[sfdpLutIndex].protocolMode;
            xspiMemNorHandle.addrSize        = probedInfo[sfdpLutIndex].addrWidth;
            break;
        }
        else if ((sfdpLutIndex == (ARRAY_SIZE(sfdp_lut) - 1U)) && (ret != kSFDP_RET_Success))
        {
            return kStatus_Fail;
        }
        else
        {
        }
    }

    return kStatus_Success;
}

static status_t XSPI_NOR_Enter4ByteMode(void)
{
    status_t status                             = kStatus_Success;
    sfdp_4_byte_addr_enter_method_t enterMethod = SFDP_Get4ByteAddrModeEnterMethod(xspiMemNorHandle.ptrSfdpHandle);
    uint32_t xspiInstanceId                     = XSPI_GetInstance(curXSPIBase);
    xspi_transfer_t flashXfer;

    switch (enterMethod)
    {
        case kSFDP_4ByteAddrEnterMethod0:
        {
            memset((void *)&g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ALT].insrOperandPair1, 0UL, sizeof(lut_seq_entry_t));
            g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ALT].insrOperandPair1 =
                XSPI_LUT_SEQ(kXSPI_Command_SDR, kXSPI_1PAD, 0xB7U, kXSPI_Command_STOP, kXSPI_1PAD, 0U);

            XSPI_UpdateLUT(curXSPIBase, NOR_CMD_LUT_SEQ_IDX_ALT * 5U,
                           &(g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ALT].insrOperandPair1), 5U);

            flashXfer.deviceAddress   = s_socXspiAmbaBase[xspiInstanceId];
            flashXfer.cmdType         = kXSPI_Command;
            flashXfer.data            = NULL;
            flashXfer.dataSize        = 0U;
            flashXfer.lockArbitration = false;
            flashXfer.seqIndex        = NOR_CMD_LUT_SEQ_IDX_ALT;
            flashXfer.targetGroup     = xspiMemNorHandle.selectedTg;

            status = XSPI_TransferBlocking(curXSPIBase, &flashXfer);
            if (status != kStatus_Success)
            {
                return status;
            }
            break;
        }
        case kSFDP_4ByteAddrEnterMethod1:
        {
            memset((void *)&g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ALT].insrOperandPair1, 0UL, sizeof(lut_seq_entry_t));
            g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ALT].insrOperandPair1 =
                XSPI_LUT_SEQ(kXSPI_Command_SDR, kXSPI_1PAD, 0x06U, kXSPI_Command_SDR, kXSPI_1PAD, 0xB7U);

            XSPI_UpdateLUT(curXSPIBase, NOR_CMD_LUT_SEQ_IDX_ALT * 5U,
                           &(g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ALT].insrOperandPair1), 5U);

            flashXfer.deviceAddress   = s_socXspiAmbaBase[xspiInstanceId];
            flashXfer.cmdType         = kXSPI_Command;
            flashXfer.data            = NULL;
            flashXfer.dataSize        = 0U;
            flashXfer.lockArbitration = false;
            flashXfer.seqIndex        = NOR_CMD_LUT_SEQ_IDX_ALT;
            flashXfer.targetGroup     = xspiMemNorHandle.selectedTg;

            status = XSPI_TransferBlocking(curXSPIBase, &flashXfer);
            break;
        }
        case kSFDP_4ByteAddrEnterMethod2:
        {
            break;
        }
        case kSFDP_4ByteAddrEnterMethod3:
        {
            break;
        }
        case kSFDP_4ByteAddrEnterMethod4:
        {
            break;
        }
        case kSFDP_4ByteAddrEnterMethod5:
        {
            /* The flash device support dedicated 4-byte address instruction set, no actions to do. */
            break;
        }
        case kSFDP_4ByteAddrEnterMethod6:
        {
            /* Always operats in 4-byte address mode, no action to do. */
            break;
        }
        default:
        {
            assert(false);
        }
    }

    return status;
}

static status_t XSPI_NOR_SetNorFlashDeviceConfig(xspi_memory_config_t *ptrUserInputMemConfig)
{
    xspi_device_ddr_config_t externalDeviceDdrConfig;
    xspi_device_status_reg_info_t norFlashStatusRegInfo;
    xspi_device_config_t externNorFlashConfig;
    status_t status;

    externalDeviceDdrConfig.enableDdr                 = SFDP_CheckDTRSupported(xspiMemNorHandle.ptrSfdpHandle);
    externalDeviceDdrConfig.enableByteSwapInOctalMode = SFDP_CheckByteSwapInOctalMode(xspiMemNorHandle.ptrSfdpHandle);
    externalDeviceDdrConfig.ddrDataAlignedClk         = kXSPI_DDRDataAlignedWith2xInternalRefClk;

    sfdp_wip_bit_info_t wipInfo;
    SFDP_GetBusyBitInfo(xspiMemNorHandle.ptrSfdpHandle, (sfdp_flash_pad_num_t)ptrUserInputMemConfig->numPadUsed,
                        &wipInfo);

    norFlashStatusRegInfo.wipLocation           = wipInfo.location;
    norFlashStatusRegInfo.value1Expired         = wipInfo.polarity;
    norFlashStatusRegInfo.upperHalfWordSelected = wipInfo.upperHalfWordSelected;

    (void)memset((void *)(uint32_t)&externNorFlashConfig, 0UL, sizeof(externNorFlashConfig));

    externNorFlashConfig.ptrDeviceRegInfo   = &norFlashStatusRegInfo;
    externNorFlashConfig.deviceSize[0]      = SFDP_GetFlashDensity(xspiMemNorHandle.ptrSfdpHandle);
    externNorFlashConfig.deviceSize[1]      = externNorFlashConfig.deviceSize[0];
    externNorFlashConfig.ptrDeviceDdrConfig = &externalDeviceDdrConfig;
    externNorFlashConfig.enableCknPad       = ptrUserInputMemConfig->enableClknPad;
    externNorFlashConfig.deviceInterface    = kXSPI_StrandardExtendedSPI;
    externNorFlashConfig.interfaceSettings.strandardExtendedSPISettings.pageSize =
        SFDP_GetPageSize(xspiMemNorHandle.ptrSfdpHandle);
    externNorFlashConfig.addrMode              = ptrUserInputMemConfig->addrMode;
    externNorFlashConfig.columnAddrWidth       = 0U;
    externNorFlashConfig.CSHoldTime            = 3U;
    externNorFlashConfig.CSSetupTime           = 3U;
    externNorFlashConfig.enableCASInterleaving = false;
    externNorFlashConfig.sampleClkConfig       = ptrUserInputMemConfig->sampleClkConfig;
    externNorFlashConfig.xspiRootClk           = ptrUserInputMemConfig->xspiRootClk;

    status = XSPI_SetDeviceConfig(curXSPIBase, &externNorFlashConfig);

    xspiMemNorHandle.memSizeInByte         = externNorFlashConfig.deviceSize[0] * 1024UL;
    xspiMemNorHandle.norFlashStatusRegInfo = norFlashStatusRegInfo;

    return status;
}

static void XSPI_NOR_FillPageProgramLutSeq(void)
{
    xspi_lut_instr_t cmdInstr;
    xspi_lut_instr_t raddrInstr;
    xspi_lut_instr_t writeInstr;

    sfdp_flash_pad_num_t instrPad;
    uint8_t instrDDR;
    sfdp_flash_pad_num_t addrPad;
    uint8_t addrDDR;
    sfdp_flash_pad_num_t dataPad;
    uint8_t dataDDR;

    SFDP_DECODE_PROTOCOL_TYPE(xspiMemNorHandle.curProtocolType);

    cmdInstr   = g_xspiCommonInstr[instrDDR][XSPI_INSTR_CMD_IDX];
    raddrInstr = g_xspiCommonInstr[addrDDR][XSPI_INSTR_RADDR_IDX];
    writeInstr = g_xspiCommonInstr[dataDDR][XSPI_INSTR_WRITE_IDX];

    sfdp_page_program_cmd_info_t pageProgramCmdInfo;

    SFDP_GetPageProgramCmdInfo(xspiMemNorHandle.ptrSfdpHandle, xspiMemNorHandle.curProtocolType, &pageProgramCmdInfo);

    if (xspiMemNorHandle.curProtocolType == kSFDP_Protocol_8d8d8d)
    {
        uint8_t cmdInstrExtension =
            SFDP_GetOctalDTRCmdExtension(xspiMemNorHandle.ptrSfdpHandle, pageProgramCmdInfo.instruction);

        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM].insrOperandPair1 =
            XSPI_LUT_SEQ(cmdInstr, (xspi_pad_t)instrPad, pageProgramCmdInfo.instruction, cmdInstr, (xspi_pad_t)instrPad,
                         cmdInstrExtension);
        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM].insrOperandPair2 = XSPI_LUT_SEQ(
            raddrInstr, (xspi_pad_t)addrPad, xspiMemNorHandle.addrSize, writeInstr, (xspi_pad_t)dataPad, 0x8U);
    }
    else
    {
        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM].insrOperandPair1 =
            XSPI_LUT_SEQ(cmdInstr, (xspi_pad_t)instrPad, pageProgramCmdInfo.instruction, raddrInstr,
                         (xspi_pad_t)addrPad, xspiMemNorHandle.addrSize);
        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM].insrOperandPair2 =
            XSPI_LUT_SEQ(writeInstr, (xspi_pad_t)dataPad, 0x8U, 0x0U, 0x0U, 0x0U);
    }
}

static void XSPI_NOR_FillSectorEraseLutSeq(void)
{
    xspi_lut_instr_t cmdInstr;
    xspi_lut_instr_t raddrInstr;
    sfdp_flash_pad_num_t instrPad;
    uint8_t instrDDR;
    sfdp_flash_pad_num_t addrPad;
    uint8_t addrDDR;
    sfdp_flash_pad_num_t dataPad;
    uint8_t dataDDR;

    SFDP_DECODE_PROTOCOL_TYPE(xspiMemNorHandle.curProtocolType);

    cmdInstr   = g_xspiCommonInstr[instrDDR][XSPI_INSTR_CMD_IDX];
    raddrInstr = g_xspiCommonInstr[addrDDR][XSPI_INSTR_RADDR_IDX];

    sfdp_erase_cmd_info_t sectorEraseCmdInfo;

    if (SFDP_GetSectorEraseCmdInfo(xspiMemNorHandle.ptrSfdpHandle, kSFDP_EraseCmdType1, &sectorEraseCmdInfo) ==
        kSFDP_RET_Success)
    {
        if (xspiMemNorHandle.curProtocolType == kSFDP_Protocol_8d8d8d)
        {
            uint8_t cmdInstrExtension =
                SFDP_GetOctalDTRCmdExtension(xspiMemNorHandle.ptrSfdpHandle, sectorEraseCmdInfo.instruction);

            g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ERASESECTOR].insrOperandPair1 =
                XSPI_LUT_SEQ(cmdInstr, instrPad, sectorEraseCmdInfo.instruction, cmdInstr, instrPad, cmdInstrExtension);
            g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ERASESECTOR].insrOperandPair2 =
                XSPI_LUT_SEQ(raddrInstr, addrPad, xspiMemNorHandle.addrSize, kXSPI_Command_STOP, instrPad, 0U);
        }
        else
        {
            g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ERASESECTOR].insrOperandPair1 = XSPI_LUT_SEQ(
                cmdInstr, instrPad, sectorEraseCmdInfo.instruction, raddrInstr, addrPad, xspiMemNorHandle.addrSize);
            g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ERASESECTOR].insrOperandPair2 =
                XSPI_LUT_SEQ(kXSPI_Command_STOP, instrPad, 0x0U, 0x0U, 0x0U, 0x0U);
        }
    }

    xspiMemNorHandle.sectorSizeInByte = sectorEraseCmdInfo.eraseSize;
    (void)dataPad;
    (void)dataDDR;
}

static void XSPI_NOR_FillBlockEraseLutSeq(void)
{
    xspi_lut_instr_t cmdInstr;
    xspi_lut_instr_t raddrInstr;
    sfdp_flash_pad_num_t instrPad;
    uint8_t instrDDR;
    sfdp_flash_pad_num_t addrPad;
    uint8_t addrDDR;
    sfdp_flash_pad_num_t dataPad;
    uint8_t dataDDR;

    SFDP_DECODE_PROTOCOL_TYPE(xspiMemNorHandle.curProtocolType);

    cmdInstr   = g_xspiCommonInstr[instrDDR][XSPI_INSTR_CMD_IDX];
    raddrInstr = g_xspiCommonInstr[addrDDR][XSPI_INSTR_RADDR_IDX];

    sfdp_erase_cmd_info_t sectorEraseCmdInfo;

    if (SFDP_GetSectorEraseCmdInfo(xspiMemNorHandle.ptrSfdpHandle, kSFDP_EraseCmdType2, &sectorEraseCmdInfo) ==
        kSFDP_RET_Success)
    {
        if (xspiMemNorHandle.curProtocolType == kSFDP_Protocol_8d8d8d)
        {
            uint8_t cmdInstrExtension =
                SFDP_GetOctalDTRCmdExtension(xspiMemNorHandle.ptrSfdpHandle, sectorEraseCmdInfo.instruction);
            g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ERASEBLOCK].insrOperandPair1 =
                XSPI_LUT_SEQ(cmdInstr, instrPad, sectorEraseCmdInfo.instruction, cmdInstr, instrPad, cmdInstrExtension);
            g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ERASEBLOCK].insrOperandPair2 =
                XSPI_LUT_SEQ(raddrInstr, addrPad, xspiMemNorHandle.addrSize, kXSPI_Command_STOP, instrPad, 0U);
        }
        else
        {
            g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ERASEBLOCK].insrOperandPair1 = XSPI_LUT_SEQ(
                cmdInstr, instrPad, sectorEraseCmdInfo.instruction, raddrInstr, addrPad, xspiMemNorHandle.addrSize);

            g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ERASEBLOCK].insrOperandPair2 =
                XSPI_LUT_SEQ(kXSPI_Command_STOP, instrPad, 0x0U, 0x0U, 0x0U, 0x0U);
        }
    }

    (void)dataPad;
    (void)dataDDR;
}

static void XSPI_NOR_FillWriteEnableLutSeq(void)
{
    xspi_lut_instr_t cmdInstr;
    sfdp_flash_pad_num_t instrPad;
    uint8_t instrDDR;
    sfdp_flash_pad_num_t addrPad;
    uint8_t addrDDR;
    sfdp_flash_pad_num_t dataPad;
    uint8_t dataDDR;

    SFDP_DECODE_PROTOCOL_TYPE(xspiMemNorHandle.curProtocolType);
    (void)addrPad;
    (void)addrDDR;
    (void)dataPad;
    (void)dataDDR;

    cmdInstr = g_xspiCommonInstr[instrDDR][XSPI_INSTR_CMD_IDX];

    uint8_t wrenInstr = 0x06U;
    if (xspiMemNorHandle.curProtocolType == kSFDP_Protocol_8d8d8d)
    {
        uint8_t wrenInstrExtension = SFDP_GetOctalDTRCmdExtension(xspiMemNorHandle.ptrSfdpHandle, wrenInstr);

        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_WRITEENABLE].insrOperandPair1 =
            XSPI_LUT_SEQ(cmdInstr, instrPad, wrenInstr, cmdInstr, instrPad, wrenInstrExtension);
        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_WRITEENABLE].insrOperandPair2 =
            XSPI_LUT_SEQ(kXSPI_Command_STOP, instrPad, 0x0U, 0x0U, 0x0U, 0x0U);
    }
    else
    {
        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_WRITEENABLE].insrOperandPair1 =
            XSPI_LUT_SEQ(cmdInstr, instrPad, wrenInstr, kXSPI_Command_STOP, instrPad, 0x0U);
    }
}

static void XSPI_NOR_FillReadIdLutSeq(void)
{
    uint8_t readIdInstr = 0x9F;
    xspi_lut_instr_t cmdInstr;
    xspi_lut_instr_t readInstr;
    xspi_lut_instr_t raddrInstr;

    sfdp_flash_pad_num_t instrPad;
    uint8_t instrDDR;
    sfdp_flash_pad_num_t addrPad;
    uint8_t addrDDR;
    sfdp_flash_pad_num_t dataPad;
    uint8_t dataDDR;

    SFDP_DECODE_PROTOCOL_TYPE(xspiMemNorHandle.curProtocolType);

    cmdInstr   = g_xspiCommonInstr[instrDDR][XSPI_INSTR_CMD_IDX];
    readInstr  = g_xspiCommonInstr[dataDDR][XSPI_INSTR_READ_IDX];
    raddrInstr = g_xspiCommonInstr[addrDDR][XSPI_INSTR_RADDR_IDX];

    if (xspiMemNorHandle.curProtocolType == kSFDP_Protocol_8d8d8d)
    {
        uint8_t instrExtension = SFDP_GetOctalDTRCmdExtension(xspiMemNorHandle.ptrSfdpHandle, readIdInstr);
        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_READID].insrOperandPair1 =
            XSPI_LUT_SEQ(cmdInstr, instrPad, readIdInstr, cmdInstr, instrPad, instrExtension);
        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_READID].insrOperandPair2 =
            XSPI_LUT_SEQ(raddrInstr, addrPad, xspiMemNorHandle.addrSize, kXSPI_Command_DUMMY_SDR, instrPad, 0x4U);
        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_READID].insrOperandPair3 =
            XSPI_LUT_SEQ(readInstr, dataPad, 0x08U, kXSPI_Command_STOP, kXSPI_1PAD, 0x0U);
    }
    else
    {
        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_READID].insrOperandPair1 =
            XSPI_LUT_SEQ(cmdInstr, instrPad, readIdInstr, raddrInstr, addrPad, xspiMemNorHandle.addrSize);
        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_READID].insrOperandPair2 =
            XSPI_LUT_SEQ(kXSPI_Command_DUMMY_SDR, instrPad, 0x4U, readInstr, dataPad, 0x08U);
        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_READID].insrOperandPair3 =
            XSPI_LUT_SEQ(kXSPI_Command_STOP, kXSPI_1PAD, 0x0U, 0x0U, 0x0U, 0x0U);
    }
}

static void XSPI_NOR_FillReadDataLutSeq(void)
{
    xspi_lut_instr_t cmdInstr;
    xspi_lut_instr_t readInstr;
    xspi_lut_instr_t raddrInstr;

    sfdp_flash_pad_num_t instrPad;
    uint8_t instrDDR;
    sfdp_flash_pad_num_t addrPad;
    uint8_t addrDDR;
    sfdp_flash_pad_num_t dataPad;
    uint8_t dataDDR;

    SFDP_DECODE_PROTOCOL_TYPE(xspiMemNorHandle.curProtocolType);

    cmdInstr   = g_xspiCommonInstr[instrDDR][XSPI_INSTR_CMD_IDX];
    readInstr  = g_xspiCommonInstr[dataDDR][XSPI_INSTR_READ_IDX];
    raddrInstr = g_xspiCommonInstr[addrDDR][XSPI_INSTR_RADDR_IDX];

    sfdp_read_cmd_info_t readCmdInfo;
    uint32_t clkFreq = xspiMemNorHandle.clkFreq;

    if (SFDP_CheckDTRSupported(xspiMemNorHandle.ptrSfdpHandle) == true)
    {
        clkFreq /= 2UL;
    }

    SFDP_GetReadCmdInfo(xspiMemNorHandle.ptrSfdpHandle, xspiMemNorHandle.curProtocolType, clkFreq, &readCmdInfo);

    /* @TODO: In case of dummy cycle is updated in ROM, read register to check current dummy cycle value. */

    if (xspiMemNorHandle.curProtocolType == kSFDP_Protocol_8d8d8d)
    {
        uint8_t instrExtension = SFDP_GetOctalDTRCmdExtension(xspiMemNorHandle.ptrSfdpHandle, readCmdInfo.instruction);

        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_READ].insrOperandPair1 =
            XSPI_LUT_SEQ(cmdInstr, instrPad, readCmdInfo.instruction, cmdInstr, instrPad, instrExtension);
        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_READ].insrOperandPair2 = XSPI_LUT_SEQ(
            raddrInstr, addrPad, xspiMemNorHandle.addrSize, kXSPI_Command_DUMMY_SDR, instrPad, readCmdInfo.dummyCycle);
        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_READ].insrOperandPair3 =
            XSPI_LUT_SEQ(readInstr, dataPad, 0x8U, kXSPI_Command_STOP, instrPad, 0U);
    }
    else
    {
        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_READ].insrOperandPair1 =
            XSPI_LUT_SEQ(cmdInstr, instrPad, readCmdInfo.instruction, raddrInstr, addrPad, xspiMemNorHandle.addrSize);
        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_READ].insrOperandPair2 =
            XSPI_LUT_SEQ(kXSPI_Command_DUMMY_SDR, instrPad, readCmdInfo.dummyCycle, readInstr, dataPad, 0x8U);
        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_READ].insrOperandPair3 =
            XSPI_LUT_SEQ(kXSPI_Command_STOP, instrPad, 0U, 0U, 0U, 0U);
    }
}

static void XSPI_NOR_FillChipEraseLutSeq(void)
{
    xspi_lut_instr_t cmdInstr;

    sfdp_flash_pad_num_t instrPad;
    uint8_t instrDDR;
    sfdp_flash_pad_num_t addrPad;
    uint8_t addrDDR;
    sfdp_flash_pad_num_t dataPad;
    uint8_t dataDDR;

    SFDP_DECODE_PROTOCOL_TYPE(xspiMemNorHandle.curProtocolType);
    (void)addrDDR;
    (void)addrPad;
    (void)dataPad;
    (void)dataDDR;

    cmdInstr = g_xspiCommonInstr[instrDDR][XSPI_INSTR_CMD_IDX];
    sfdp_chip_erase_cmd_info_t chipEraseCmdInfo;

    SFDP_GetChipEraseCmdInfo(xspiMemNorHandle.ptrSfdpHandle, &chipEraseCmdInfo);
    if (xspiMemNorHandle.curProtocolType == kSFDP_Protocol_8d8d8d)
    {
        uint8_t instrExtension =
            SFDP_GetOctalDTRCmdExtension(xspiMemNorHandle.ptrSfdpHandle, chipEraseCmdInfo.instruction);

        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_CHIPERASE].insrOperandPair1 =
            XSPI_LUT_SEQ(cmdInstr, instrPad, chipEraseCmdInfo.instruction, cmdInstr, instrPad, instrExtension);
        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_CHIPERASE].insrOperandPair2 =
            XSPI_LUT_SEQ(kXSPI_Command_STOP, instrPad, 0U, 0U, 0U, 0U);
    }
    else
    {
        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_CHIPERASE].insrOperandPair1 =
            XSPI_LUT_SEQ(cmdInstr, instrPad, chipEraseCmdInfo.instruction, kXSPI_Command_STOP, instrPad, 0U);
    }
}

static void XSPI_NOR_FillReadStatusLutSeq(void)
{
    xspi_lut_instr_t cmdInstr;
    xspi_lut_instr_t raddrInstr;
    xspi_lut_instr_t readInstr;

    sfdp_flash_pad_num_t instrPad;
    uint8_t instrDDR;
    sfdp_flash_pad_num_t addrPad;
    uint8_t addrDDR;
    sfdp_flash_pad_num_t dataPad;
    uint8_t dataDDR;

    SFDP_DECODE_PROTOCOL_TYPE(xspiMemNorHandle.curProtocolType);

    cmdInstr   = g_xspiCommonInstr[instrDDR][XSPI_INSTR_CMD_IDX];
    raddrInstr = g_xspiCommonInstr[addrDDR][XSPI_INSTR_RADDR_IDX];
    readInstr  = g_xspiCommonInstr[dataDDR][XSPI_INSTR_READ_IDX];

    sfdp_read_status_cmd_info_t readStatusCmdInfo;
    SFDP_GetReadStatusCmdInfo(xspiMemNorHandle.ptrSfdpHandle, xspiMemNorHandle.curProtocolType, &readStatusCmdInfo);

    /* @TODO: In case of dummy cycle is updated. */

    if (xspiMemNorHandle.curProtocolType == kSFDP_Protocol_8d8d8d)
    {
        uint8_t instrExtension =
            SFDP_GetOctalDTRCmdExtension(xspiMemNorHandle.ptrSfdpHandle, readStatusCmdInfo.instruction);

        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_READSTATUS].insrOperandPair1 =
            XSPI_LUT_SEQ(cmdInstr, instrPad, readStatusCmdInfo.instruction, cmdInstr, instrPad, instrExtension);
        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_READSTATUS].insrOperandPair2 =
            XSPI_LUT_SEQ(raddrInstr, addrPad, readStatusCmdInfo.addrSize, kXSPI_Command_DUMMY_SDR, instrPad,
                         readStatusCmdInfo.dummyCycle);
        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_READSTATUS].insrOperandPair3 =
            XSPI_LUT_SEQ(readInstr, dataPad, 0x4, kXSPI_Command_STOP, instrPad, 0x0U);
    }
    else if (xspiMemNorHandle.curProtocolType == kSFDP_Protocol_1s1s1s)
    {
        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_READSTATUS].insrOperandPair1 =
            XSPI_LUT_SEQ(cmdInstr, instrPad, readStatusCmdInfo.instruction, readInstr, dataPad, 0x8);
    }
    else
    {
        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_READSTATUS].insrOperandPair1 = XSPI_LUT_SEQ(
            cmdInstr, instrPad, readStatusCmdInfo.instruction, raddrInstr, addrPad, readStatusCmdInfo.addrSize);
        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_READSTATUS].insrOperandPair2 =
            XSPI_LUT_SEQ(kXSPI_Command_DUMMY_SDR, instrPad, readStatusCmdInfo.dummyCycle, readInstr, dataPad, 0x8);
        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_READSTATUS].insrOperandPair3 =
            XSPI_LUT_SEQ(kXSPI_Command_STOP, instrPad, 0x0U, 0x0U, 0x0U, 0x0U);
    }
}

static void XSPI_NOR_FillWriteStatusLutSeq(void)
{
    xspi_lut_instr_t cmdInstr;
    xspi_lut_instr_t writeInstr;

    sfdp_flash_pad_num_t instrPad;
    uint8_t instrDDR;
    sfdp_flash_pad_num_t addrPad;
    uint8_t addrDDR;
    sfdp_flash_pad_num_t dataPad;
    uint8_t dataDDR;

    SFDP_DECODE_PROTOCOL_TYPE(xspiMemNorHandle.curProtocolType);

    cmdInstr   = g_xspiCommonInstr[instrDDR][XSPI_INSTR_CMD_IDX];
    writeInstr = g_xspiCommonInstr[dataDDR][XSPI_INSTR_WRITE_IDX];

    (void)addrPad;
    (void)addrDDR;

    sfdp_write_status_cmd_info_t writeStatusCmdInfo;
    SFDP_GetWriteStatusCmdInfo(xspiMemNorHandle.ptrSfdpHandle, &writeStatusCmdInfo);

    if (xspiMemNorHandle.curProtocolType == kSFDP_Protocol_8d8d8d)
    {
        uint8_t instrExtension =
            SFDP_GetOctalDTRCmdExtension(xspiMemNorHandle.ptrSfdpHandle, writeStatusCmdInfo.instruction);
        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_WRITESTATUS].insrOperandPair1 =
            XSPI_LUT_SEQ(cmdInstr, instrPad, writeStatusCmdInfo.instruction, cmdInstr, instrPad, instrExtension);
        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_WRITESTATUS].insrOperandPair2 =
            XSPI_LUT_SEQ(writeInstr, dataPad, 0x4U, kXSPI_Command_STOP, instrPad, 0x0U);
    }
    else
    {
        g_xspiLut[NOR_CMD_LUT_SEQ_IDX_WRITESTATUS].insrOperandPair1 =
            XSPI_LUT_SEQ(cmdInstr, instrPad, writeStatusCmdInfo.instruction, writeInstr, dataPad, 0x4U);
    }
}

static status_t XSPI_NOR_UpdateLut(nor_handle_t *handle, xspi_memory_config_t *ptrUserInputMemConfig)
{
    /* If user input customized LUT use directly, else fill LUT from SFDP. */
    if (ptrUserInputMemConfig->ptrCustomLut == NULL)
    {
        XSPI_NOR_FillReadDataLutSeq();
        XSPI_NOR_FillReadStatusLutSeq();
        XSPI_NOR_FillWriteStatusLutSeq();
        XSPI_NOR_FillWriteEnableLutSeq();
        XSPI_NOR_FillSectorEraseLutSeq();
        XSPI_NOR_FillReadIdLutSeq();
        XSPI_NOR_FillPageProgramLutSeq();
        XSPI_NOR_FillChipEraseLutSeq();
        XSPI_NOR_FillBlockEraseLutSeq();
    }
    else
    {
        memcpy((void *)g_xspiLut, (void *)(ptrUserInputMemConfig->ptrCustomLut), 80U * 4U);
    }

    XSPI_UpdateLUT(curXSPIBase, 0U, (uint32_t const *)&g_xspiLut, 80U);

    return kStatus_Success;
}

static status_t XSPI_NOR_WriteEnable(nor_handle_t *handle, uint32_t address)
{
    xspi_transfer_t flashXfer;
    status_t status = kStatus_InvalidArgument;

    uint32_t xspiInstanceId = XSPI_GetInstance(curXSPIBase);

    if (address >= s_socXspiAmbaBase[xspiInstanceId])
    {
        flashXfer.deviceAddress = address;
    }
    else
    {
        flashXfer.deviceAddress = s_socXspiAmbaBase[xspiInstanceId] + address;
    }
    flashXfer.cmdType         = kXSPI_Command;
    flashXfer.seqIndex        = NOR_CMD_LUT_SEQ_IDX_WRITEENABLE;
    flashXfer.data            = NULL;
    flashXfer.dataSize        = 0UL;
    flashXfer.targetGroup     = xspiMemNorHandle.selectedTg;
    flashXfer.lockArbitration = false;

    status = XSPI_TransferBlocking(curXSPIBase, &flashXfer);

    return status;
}

sfdp_protocol_type_t XSPI_NOR_FindProtocolType(xspi_memory_config_t *ptrXspiMemConfig)
{
    sfdp_protocol_type_t calculatedProtocolType;
    sfdp_cmd_policy_t policy           = kSFDP_CmdPolicy_HighestThroughput;
    sfdp_ret_type_t ret                = kSFDP_RET_Success;
    sfdp_xspi_profile_opi_cmd_t opiCmd = kSFDP_OPICmd_Erase4K;

    while ((uint8_t)policy < SFDP_CMD_POLICY_COUNT)
    {
        calculatedProtocolType = SFDP_GetFlashProtocolType(xspiMemNorHandle.ptrSfdpHandle, policy,
                                                           (sfdp_flash_pad_num_t)(ptrXspiMemConfig->numPadUsed));

        if (calculatedProtocolType == kSFDP_Protocol_8d8d8d)
        {
            do
            {
                ret = SFDP_CheckOPICmdSupported(xspiMemNorHandle.ptrSfdpHandle, opiCmd);
                opiCmd++;
            } while ((ret == kSFDP_RET_Success) && ((uint8_t)opiCmd < SFDP_XSPI_PROFILE_OPI_CMD_COUNT));

            if (ret != kSFDP_RET_Success)
            {
                policy++;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    return calculatedProtocolType;
}

static status_t XSPI_NOR_QuadEnable(void)
{
    status_t status                            = kStatus_Success;
    sfdp_quad_enable_method_t quadEnableMethod = SFDP_GetQuadEnableMethod(xspiMemNorHandle.ptrSfdpHandle);

    switch (quadEnableMethod)
    {
        case kSFDP_QuadEnableNotSupported:
        {
            /*Device doest not have a QE bit, device detects 1s-1s-4s and 1s-4s-4s reads based on instruction.  */
            break;
        }
        case kSFDP_QuadEnableMethod1:
        {
            break;
        }
        case kSFDP_QuadEnableMethod2:
        {
            break;
        }
        case kSFDP_QuadEnableMethod3:
        {
            break;
        }
        case kSFDP_QuadEnableMethod4:
        {
            break;
        }
        case kSFDP_QuadEnableMethod5:
        {
            break;
        }
        case kSFDP_QuadEnableMethod6:
        {
            break;
        }
        default:
        {
            assert(false);
        }
    }

    return status;
}

static status_t XSPI_NOR_EnterQuadSSRMode(void)
{
    status_t status                               = kStatus_Success;
    sfdp_4s4s4s_mode_enable_method_t enableMethod = SFDP_Get4s4s4sModeEnableMethod(xspiMemNorHandle.ptrSfdpHandle);
    uint32_t xspiInstanceId                       = XSPI_GetInstance(curXSPIBase);
    xspi_transfer_t flashXfer;

    switch (enableMethod)
    {
        case kSFDP_4s4s4sModeEnableMethod0:
        {
            XSPI_NOR_QuadEnable();

            memset((void *)&g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ALT].insrOperandPair1, 0UL, sizeof(lut_seq_entry_t));
            g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ALT].insrOperandPair1 =
                XSPI_LUT_SEQ(kXSPI_Command_SDR, kXSPI_1PAD, 0x38U, kXSPI_Command_STOP, kXSPI_1PAD, 0U);

            XSPI_UpdateLUT(curXSPIBase, NOR_CMD_LUT_SEQ_IDX_ALT * 5U,
                           &(g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ALT].insrOperandPair1), 5U);

            flashXfer.deviceAddress   = s_socXspiAmbaBase[xspiInstanceId];
            flashXfer.cmdType         = kXSPI_Command;
            flashXfer.data            = NULL;
            flashXfer.dataSize        = 0U;
            flashXfer.lockArbitration = false;
            flashXfer.seqIndex        = NOR_CMD_LUT_SEQ_IDX_ALT;
            flashXfer.targetGroup     = xspiMemNorHandle.selectedTg;

            status = XSPI_TransferBlocking(curXSPIBase, &flashXfer);
            if (status != kStatus_Success)
            {
                return status;
            }
            break;
        }
        case kSFDP_4s4s4sModeEnableMethod1:
        {
            g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ALT].insrOperandPair1 =
                XSPI_LUT_SEQ(kXSPI_Command_SDR, kXSPI_1PAD, 0x38U, kXSPI_Command_STOP, kXSPI_1PAD, 0U);

            XSPI_UpdateLUT(curXSPIBase, NOR_CMD_LUT_SEQ_IDX_ALT * 5U,
                           &(g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ALT].insrOperandPair1), 5U);

            flashXfer.deviceAddress   = s_socXspiAmbaBase[xspiInstanceId];
            flashXfer.cmdType         = kXSPI_Command;
            flashXfer.data            = NULL;
            flashXfer.dataSize        = 0U;
            flashXfer.lockArbitration = false;
            flashXfer.seqIndex        = NOR_CMD_LUT_SEQ_IDX_ALT;
            flashXfer.targetGroup     = xspiMemNorHandle.selectedTg;

            status = XSPI_TransferBlocking(curXSPIBase, &flashXfer);
            if (status != kStatus_Success)
            {
                return status;
            }
            break;
        }
        case kSFDP_4s4s4sModeEnableMethod2:
        {
            g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ALT].insrOperandPair1 =
                XSPI_LUT_SEQ(kXSPI_Command_SDR, kXSPI_1PAD, 0x35U, kXSPI_Command_STOP, kXSPI_1PAD, 0U);

            XSPI_UpdateLUT(curXSPIBase, NOR_CMD_LUT_SEQ_IDX_ALT * 5U,
                           &(g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ALT].insrOperandPair1), 5U);

            flashXfer.deviceAddress   = s_socXspiAmbaBase[xspiInstanceId];
            flashXfer.cmdType         = kXSPI_Command;
            flashXfer.data            = NULL;
            flashXfer.dataSize        = 0U;
            flashXfer.lockArbitration = false;
            flashXfer.seqIndex        = NOR_CMD_LUT_SEQ_IDX_ALT;
            flashXfer.targetGroup     = xspiMemNorHandle.selectedTg;

            status = XSPI_TransferBlocking(curXSPIBase, &flashXfer);
            if (status != kStatus_Success)
            {
                return status;
            }
            break;
        }
        case kSFDP_4s4s4sModeEnableMethod3:
        {
            /*!< Read configuration using instruction 65h followed by address 800003h,
                set bit 6, write configuration using instruction 71h followed by
                address 800003h. */
            break;
        }
        case kSFDP_4s4s4sModeEnableMethod4:
        {
            /*!< Read volatile enhanced configuration using instruction 65h, no
                address is required, set bit 7 to 1, write volatile enhanced
                configuration using instruction 61h, no address is required. */
            break;
        }
    }

    return status;
}

static status_t XSPI_NOR_EnterQuadDDRMode(void)
{
    status_t status = kStatus_Success;
    sfdp_4s4d4d_entry_seq_t quadEntrySeq;

    if (SFDP_Get4s4d4dEntrySeq(xspiMemNorHandle.ptrSfdpHandle, &quadEntrySeq) != kSFDP_RET_Success)
    {
        return kStatus_Fail;
    }

    uint8_t seqLength = 0U;
    uint32_t i        = 0U;
    lut_seq_instr_operand_t altSeq[10];
    xspi_transfer_t flashXfer;
    uint32_t xspiInstanceId = XSPI_GetInstance(curXSPIBase);
    uint32_t delayCount     = 0UL;

    sfdp_entry_seq_format_t *ptrSeq = &(quadEntrySeq.seq1);
    for (uint8_t seqId = 0U; seqId < 4U; seqId++)
    {
        if (ptrSeq->seqStruct.length != 0U)
        {
            seqLength = ptrSeq->seqStruct.length;
            memset(altSeq, 0UL, sizeof(altSeq));
            for (i = 0U; i < seqLength; i++)
            {
                altSeq[i].operand = SFDP_GET_SEQ_CMD((*ptrSeq), i + 1U);
                altSeq[i].instr   = kXSPI_Command_SDR;
                altSeq[i].padNum  = kXSPI_1PAD;
            }
            memset((void *)&g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ALT].insrOperandPair1, 0UL, sizeof(lut_seq_entry_t));
            memcpy((void *)&g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ALT].insrOperandPair1, (void *)&altSeq[0],
                   seqLength * sizeof(altSeq));

            XSPI_UpdateLUT(curXSPIBase, NOR_CMD_LUT_SEQ_IDX_ALT * 5U,
                           &(g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ALT].insrOperandPair1), 5U);

            flashXfer.deviceAddress   = s_socXspiAmbaBase[xspiInstanceId];
            flashXfer.cmdType         = kXSPI_Command;
            flashXfer.data            = NULL;
            flashXfer.dataSize        = 0U;
            flashXfer.lockArbitration = false;
            flashXfer.seqIndex        = NOR_CMD_LUT_SEQ_IDX_ALT;
            flashXfer.targetGroup     = xspiMemNorHandle.selectedTg;

            status = XSPI_TransferBlocking(curXSPIBase, &flashXfer);
            __ISB();
            __DSB();
            for (delayCount = 0U; delayCount < 2000U; delayCount++)
            {
                /* Delay to make sure command effect. */
                __NOP();
            }
        }
        if (status != kStatus_Success)
        {
            break;
        }
        ptrSeq++;
    }

    return status;
}

static status_t XSPI_NOR_OctalEnable(void)
{
    status_t status                              = kStatus_Success;
    sfdp_octal_enable_method_t octalEnableMethod = SFDP_GetOctalEnableMethod(xspiMemNorHandle.ptrSfdpHandle);

    switch (octalEnableMethod)
    {
        case kSFDP_OctalEnableNotSupported:
        {
            /* Not supported. */
            break;
        }
        case kSFDP_OctalEnableMethod1:
        {
            /*!< Octal enable is bit 3 of status register, it is set via write status register2
            instruction 31h with one data byte where bit 3 is one, it is cleared via write
            register instruction 3Eh with one data byte where bit 3 is zero, the status
            register 2 is read using instruction 65h with address byte 02h and one dummy
            cycle. */
            break;
        }
        default:
        {
            assert(false);
        }
    }

    return status;
}

static status_t XSPI_NOR_EnterOctalSSRMode(void)
{
    status_t status                               = kStatus_Success;
    sfdp_8s8s8s_mode_enable_method_t enableMethod = SFDP_Get8s8s8sModeEnableMethod(xspiMemNorHandle.ptrSfdpHandle);
    uint32_t xspiInstanceId                       = XSPI_GetInstance(curXSPIBase);
    xspi_transfer_t flashXfer;

    switch (enableMethod)
    {
        case kSFDP_8s8s8sModeEnableMethod0:
        {
            memset((void *)&g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ALT].insrOperandPair1, 0UL, sizeof(lut_seq_entry_t));
            g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ALT].insrOperandPair1 =
                XSPI_LUT_SEQ(kXSPI_Command_SDR, kXSPI_1PAD, 0x06U, kXSPI_Command_SDR, kXSPI_1PAD, 0xE8U);

            XSPI_UpdateLUT(curXSPIBase, NOR_CMD_LUT_SEQ_IDX_ALT * 5U,
                           &(g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ALT].insrOperandPair1), 5U);

            flashXfer.deviceAddress   = s_socXspiAmbaBase[xspiInstanceId];
            flashXfer.cmdType         = kXSPI_Command;
            flashXfer.data            = NULL;
            flashXfer.dataSize        = 0U;
            flashXfer.lockArbitration = false;
            flashXfer.seqIndex        = NOR_CMD_LUT_SEQ_IDX_ALT;
            flashXfer.targetGroup     = xspiMemNorHandle.selectedTg;

            status = XSPI_TransferBlocking(curXSPIBase, &flashXfer);
            break;
        }
        case kSFDP_8s8s8sModeEnableMethod1:
        {
            memset((void *)&g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ALT].insrOperandPair1, 0UL, sizeof(lut_seq_entry_t));
            g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ALT].insrOperandPair1 =
                XSPI_LUT_SEQ(kXSPI_Command_SDR, kXSPI_1PAD, 0x06U, kXSPI_Command_SDR, kXSPI_1PAD, 0x72U);

            XSPI_UpdateLUT(curXSPIBase, NOR_CMD_LUT_SEQ_IDX_ALT * 5U,
                           &(g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ALT].insrOperandPair1), 5U);

            flashXfer.deviceAddress   = s_socXspiAmbaBase[xspiInstanceId];
            flashXfer.cmdType         = kXSPI_Command;
            flashXfer.data            = NULL;
            flashXfer.dataSize        = 0U;
            flashXfer.lockArbitration = false;
            flashXfer.seqIndex        = NOR_CMD_LUT_SEQ_IDX_ALT;
            flashXfer.targetGroup     = xspiMemNorHandle.selectedTg;

            status = XSPI_TransferBlocking(curXSPIBase, &flashXfer);
            break;
        }
        default:
        {
            assert(false);
        }
    }

    return status;
}

static status_t XSPI_NOR_EnterOctalDDRMode(void)
{
    sfdp_8d8d8d_entry_seq_t octalEntrySeq;
    status_t status = kStatus_Success;

    if (SFDP_Get8d8d8dEntrySeq(xspiMemNorHandle.ptrSfdpHandle, &octalEntrySeq) != kSFDP_RET_Success)
    {
        return kStatus_Fail;
    }
    uint8_t seqLength = 0U;
    uint32_t i        = 0U;
    lut_seq_instr_operand_t altSeq[10];
    xspi_transfer_t flashXfer;
    uint32_t xspiInstanceId = XSPI_GetInstance(curXSPIBase);
    uint32_t delayCount     = 0UL;

    sfdp_entry_seq_format_t *ptrSeq = &(octalEntrySeq.seq1);
    for (uint8_t seqId = 0U; seqId < 4U; seqId++)
    {
        if (ptrSeq->seqStruct.length != 0U)
        {
            seqLength = ptrSeq->seqStruct.length;
            memset(altSeq, 0UL, sizeof(altSeq));
            for (i = 0U; i < seqLength; i++)
            {
                altSeq[i].operand = SFDP_GET_SEQ_CMD((*ptrSeq), i + 1U);
                altSeq[i].instr   = kXSPI_Command_SDR;
                altSeq[i].padNum  = kXSPI_1PAD;
            }
            memset((void *)&g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ALT].insrOperandPair1, 0UL, sizeof(lut_seq_entry_t));
            memcpy((void *)&g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ALT].insrOperandPair1, (void *)&altSeq[0], sizeof(altSeq));

            XSPI_UpdateLUT(curXSPIBase, NOR_CMD_LUT_SEQ_IDX_ALT * 5U,
                           &(g_xspiLut[NOR_CMD_LUT_SEQ_IDX_ALT].insrOperandPair1), 5U);

            flashXfer.deviceAddress   = s_socXspiAmbaBase[xspiInstanceId];
            flashXfer.cmdType         = kXSPI_Command;
            flashXfer.data            = NULL;
            flashXfer.dataSize        = 0U;
            flashXfer.lockArbitration = false;
            flashXfer.seqIndex        = NOR_CMD_LUT_SEQ_IDX_ALT;
            flashXfer.targetGroup     = xspiMemNorHandle.selectedTg;

            status = XSPI_TransferBlocking(curXSPIBase, &flashXfer);
            __ISB();
            __DSB();
            for (delayCount = 0U; delayCount < 2000U; delayCount++)
            {
                /* Delay to make sure command effect. */
                __NOP();
            }
        }
        if (status != kStatus_Success)
        {
            break;
        }
        ptrSeq++;
    }

    return status;
}

status_t Nor_Flash_Init(nor_config_t *config, nor_handle_t *handle)
{
    assert(config != NULL);

    xspi_memory_config_t xspiNorMemConfig = *(xspi_memory_config_t *)(config->memControlConfig);

    xspiMemNorHandle.selectedTg = xspiNorMemConfig.tgId;
    xspiMemNorHandle.clkFreq    = xspiNorMemConfig.xspiRootClk;

    xspi_ahb_write_config_t xspiAhbWriteConfig;
    xspi_ahb_access_config_t xspiAhbAccessConfig;
    xspi_ip_access_config_t xspiIpAccessConfig;
    xspi_config_t xspiConfig;

    curXSPIBase = (XSPI_Type *)(uint32_t)(config->driverBaseAddr);
    XSPI_ResetSfmAndAhbDomain(curXSPIBase);

    XSPI_UpdateByteOrder(curXSPIBase, kXSPI_32BitLE);

    sfdp_handle_t sfdpHandle;
    (void)memset((void *)&sfdpHandle, 0UL, sizeof(sfdpHandle));

    xspiMemNorHandle.ptrSfdpHandle = &sfdpHandle;

    xspiConfig.enableDoze         = xspiNorMemConfig.enableXspiDoze;
    xspiConfig.ptrAhbAccessConfig = &xspiAhbAccessConfig;
    xspiConfig.ptrIpAccessConfig  = &xspiIpAccessConfig;
    XSPI_GetDefaultConfig(&xspiConfig);

    if (xspiNorMemConfig.ptrXspiNorAhbAccessConfig != NULL)
    {
        /* In case of user customized AHB access configurations, overwrite the default settings.  */
        xspiAhbAccessConfig.buffer[0]         = xspiNorMemConfig.ptrXspiNorAhbAccessConfig->ahbBuffer0Config;
        xspiAhbAccessConfig.buffer[1]         = xspiNorMemConfig.ptrXspiNorAhbAccessConfig->ahbBuffer1Config;
        xspiAhbAccessConfig.buffer[2]         = xspiNorMemConfig.ptrXspiNorAhbAccessConfig->ahbBuffer2Config;
        xspiAhbAccessConfig.buffer[3]         = xspiNorMemConfig.ptrXspiNorAhbAccessConfig->ahbBuffer3Config;
        xspiAhbAccessConfig.enableAHBPrefetch = xspiNorMemConfig.ptrXspiNorAhbAccessConfig->enablePrefetch;
        if (xspiNorMemConfig.ptrXspiNorAhbAccessConfig->enableAhbWrite)
        {
            xspiAhbAccessConfig.ptrAhbWriteConfig = &xspiAhbWriteConfig;
        }
        else
        {
            xspiAhbAccessConfig.ptrAhbWriteConfig = NULL;
        }
    }

    xspiAhbAccessConfig.ahbAlignment                = kXSPI_AhbAlignmentNoLimit;
    xspiAhbAccessConfig.ahbErrorPayload.highPayload = 0x5A5A5A5AUL; /* hard code in component. */
    xspiAhbAccessConfig.ahbErrorPayload.lowPayload  = 0x5A5A5A5AUL; /* hard code in component. */
    xspiAhbAccessConfig.ahbSplitSize                = kXSPI_AhbSplitSizeDisabled;
    xspiAhbAccessConfig.ARDSeqIndex                 = NOR_CMD_LUT_SEQ_IDX_READ;

    xspiAhbAccessConfig.enableAHBBufferWriteFlush = true;

    if (xspiNorMemConfig.ptrXspiNorIPAccessConfig != NULL)
    {
        /* In case of user customized IP access configurations, overwrite the default settings.  */
        xspiIpAccessConfig.ipAccessTimeoutValue = xspiNorMemConfig.ptrXspiNorIPAccessConfig->ipAccessTimeoutValue;
        xspiIpAccessConfig.ptrSfpFradConfig     = xspiNorMemConfig.ptrXspiNorIPAccessConfig->ptrSfpFradConfig;
        xspiIpAccessConfig.ptrSfpMdadConfig     = xspiNorMemConfig.ptrXspiNorIPAccessConfig->ptrSfpMdadConfig;
        xspiIpAccessConfig.sfpArbitrationLockTimeoutValue =
            xspiNorMemConfig.ptrXspiNorIPAccessConfig->sfpArbitrationLockTimeoutValue;
    }

    /* initialize host controller. */
    XSPI_Init(curXSPIBase, &xspiConfig);

    if (XSPI_NOR_ProbeNorFlashSfdpHeader() != kStatus_Success)
    {
        return kStatus_Fail;
    }

    if (SFDP_ReadAllSupportedTable(&sfdpHandle) != kSFDP_RET_Success)
    {
        return kStatus_Fail;
    }

    if ((SFDP_GetAddressBytes(&sfdpHandle) != kSFDP_AddrMode_3ByteOnly) && (xspiMemNorHandle.addrSize != 32U))
    {
        XSPI_NOR_Enter4ByteMode();
        xspiMemNorHandle.addrSize = 32U;
    }

    sfdp_protocol_type_t targetProtocolType = XSPI_NOR_FindProtocolType(&xspiNorMemConfig);

    if ((targetProtocolType >= kSFDP_Protocol_1s1s4s) && (targetProtocolType <= kSFDP_Protocol_4s4d4d))
    {
        if (targetProtocolType <= kSFDP_Protocol_1s4d4d)
        {
            if (XSPI_NOR_QuadEnable() != kStatus_Success)
            {
                return kStatus_Fail;
            }
        }
        else if (targetProtocolType == kSFDP_Protocol_4s4s4s)
        {
            if (XSPI_NOR_EnterQuadSSRMode() != kStatus_Success)
            {
                return kStatus_Fail;
            }
        }
        else
        {
            if (XSPI_NOR_EnterQuadDDRMode() != kStatus_Success)
            {
                return kStatus_Fail;
            }
        }
    }
    if (targetProtocolType >= kSFDP_Protocol_1s1s8s)
    {
        if (targetProtocolType <= kSFDP_Protocol_1s8d8d)
        {
            if (XSPI_NOR_OctalEnable() != kStatus_Success)
            {
                return kStatus_Fail;
            }
        }
        else if (targetProtocolType == kSFDP_Protocol_8s8s8s)
        {
            if (XSPI_NOR_EnterOctalSSRMode() != kStatus_Success)
            {
                return kStatus_Fail;
            }
        }
        else
        {
            if (XSPI_NOR_EnterOctalDDRMode() != kStatus_Success)
            {
                return kStatus_Fail;
            }
        }
    }

    xspiMemNorHandle.curProtocolType = targetProtocolType;

    if (XSPI_NOR_SetNorFlashDeviceConfig(&xspiNorMemConfig) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    if (XSPI_NOR_UpdateLut(handle, &xspiNorMemConfig) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    /* Update handle for other interfaces. */
    handle->driverBaseAddr    = config->driverBaseAddr;
    handle->deviceSpecific    = (void *)(uint32_t)(&xspiMemNorHandle);
    handle->bytesInSectorSize = xspiMemNorHandle.sectorSizeInByte;
    handle->bytesInMemorySize = xspiMemNorHandle.memSizeInByte;
    handle->bytesInPageSize   = SFDP_GetPageSize(&sfdpHandle);

    return kStatus_Success;
}

status_t Nor_Flash_Read(nor_handle_t *handle, uint32_t address, uint8_t *buffer, uint32_t length)
{
    assert(handle != NULL);
    assert(buffer != NULL);

    xspi_transfer_t flashXfer;
    status_t status                            = kStatus_Success;
    xspi_mem_nor_handle_t *ptrXspiMemNorHandle = (xspi_mem_nor_handle_t *)(uint32_t)(handle->deviceSpecific);

    uint32_t xspiInstanceId = XSPI_GetInstance(curXSPIBase);

    if (address >= s_socXspiAmbaBase[xspiInstanceId])
    {
        flashXfer.deviceAddress = address;
    }
    else
    {
        flashXfer.deviceAddress = s_socXspiAmbaBase[xspiInstanceId] + address;
    }
    flashXfer.cmdType  = kXSPI_Read;
    flashXfer.seqIndex = NOR_CMD_LUT_SEQ_IDX_READ; /* Hard code as 0, the first sequence of LUT is used to read
                                                   data from Flash device. */
    flashXfer.data            = (uint32_t *)(void *)buffer;
    flashXfer.dataSize        = length;
    flashXfer.targetGroup     = ptrXspiMemNorHandle->selectedTg; /* Target group selection is from application. */
    flashXfer.lockArbitration = false;

    status = XSPI_TransferBlocking((XSPI_Type *)handle->driverBaseAddr, &flashXfer);

    return status;
}

status_t Nor_Flash_Page_Program(nor_handle_t *handle, uint32_t address, uint8_t *buffer)
{
    assert(handle != NULL);
    assert(buffer != NULL);

    xspi_transfer_t flashXfer;
    status_t status = kStatus_Success;
    bool isBusy     = true;

    /* Write Enable. */
    if (XSPI_NOR_WriteEnable(handle, address) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    uint32_t xspiInstanceId = XSPI_GetInstance(curXSPIBase);

    if (address >= s_socXspiAmbaBase[xspiInstanceId])
    {
        flashXfer.deviceAddress = address;
    }
    else
    {
        flashXfer.deviceAddress = s_socXspiAmbaBase[xspiInstanceId] + address;
    }
    flashXfer.cmdType         = kXSPI_Write;
    flashXfer.seqIndex        = NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM;
    flashXfer.data            = (uint32_t *)(void *)buffer;
    flashXfer.dataSize        = handle->bytesInPageSize;
    flashXfer.targetGroup     = xspiMemNorHandle.selectedTg;
    flashXfer.lockArbitration = true;

    status = XSPI_TransferBlocking((XSPI_Type *)handle->driverBaseAddr, &flashXfer);

    if (status == kStatus_Success)
    {
        /* Loop until WIP is cleared  */
        do
        {
            (void)Nor_Flash_Is_Busy(handle, &isBusy);
        } while (isBusy == true);
    }

    return status;
}

status_t Nor_Flash_Program(nor_handle_t *handle, uint32_t address, uint8_t *buffer, uint32_t length)
{
    assert(handle != NULL);
    assert(buffer != NULL);

    assert(handle != NULL);
    assert(buffer != NULL);
    uint32_t startAddress = address;
    status_t status       = kStatus_Success;

    for (uint32_t i = 0x00U; i <= (length / handle->bytesInPageSize); i++)
    {
        status = Nor_Flash_Page_Program(handle, startAddress, buffer);
        /* Avoid buffer overflow. */
        if (length >= handle->bytesInPageSize)
        {
            buffer += handle->bytesInPageSize;
            startAddress += handle->bytesInPageSize;
        }
    }

    return status;
}

status_t Nor_Flash_Erase_Sector(nor_handle_t *handle, uint32_t address)
{
    assert(handle != NULL);

    xspi_transfer_t flashXfer;
    bool isBusy     = true;
    status_t status = kStatus_Success;

    /* Write Enable. */
    if (XSPI_NOR_WriteEnable(handle, address) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    uint32_t xspiInstanceId = XSPI_GetInstance(curXSPIBase);

    if (address >= s_socXspiAmbaBase[xspiInstanceId])
    {
        flashXfer.deviceAddress = address;
    }
    else
    {
        flashXfer.deviceAddress = s_socXspiAmbaBase[xspiInstanceId] + address;
    }
    flashXfer.cmdType         = kXSPI_Command;
    flashXfer.seqIndex        = NOR_CMD_LUT_SEQ_IDX_ERASESECTOR;
    flashXfer.data            = NULL;
    flashXfer.dataSize        = 0UL;
    flashXfer.targetGroup     = xspiMemNorHandle.selectedTg;
    flashXfer.lockArbitration = false;

    status = XSPI_TransferBlocking((XSPI_Type *)handle->driverBaseAddr, &flashXfer);

    if (status == kStatus_Success)
    {
        /* Loop until WIP is cleared  */
        do
        {
            (void)Nor_Flash_Is_Busy(handle, &isBusy);
        } while (isBusy == true);
    }

    return status;
}

status_t Nor_Flash_Erase_Block(nor_handle_t *handle, uint32_t address)
{
    assert(handle != NULL);

    xspi_transfer_t flashXfer;
    status_t status                            = kStatus_Success;
    xspi_mem_nor_handle_t *ptrXspiMemNorHandle = (xspi_mem_nor_handle_t *)(uint32_t)(handle->deviceSpecific);
    bool isBusy                                = false;

    /* Write Enable. */
    if (XSPI_NOR_WriteEnable(handle, address) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    uint32_t xspiInstanceId = XSPI_GetInstance(curXSPIBase);

    if (address >= s_socXspiAmbaBase[xspiInstanceId])
    {
        flashXfer.deviceAddress = address;
    }
    else
    {
        flashXfer.deviceAddress = s_socXspiAmbaBase[xspiInstanceId] + address;
    }
    flashXfer.cmdType         = kXSPI_Command;
    flashXfer.seqIndex        = NOR_CMD_LUT_SEQ_IDX_ERASEBLOCK;
    flashXfer.data            = NULL;
    flashXfer.dataSize        = 0UL;
    flashXfer.targetGroup     = ptrXspiMemNorHandle->selectedTg;
    flashXfer.lockArbitration = false;

    status = XSPI_TransferBlocking((XSPI_Type *)handle->driverBaseAddr, &flashXfer);

    if (status == kStatus_Success)
    {
        /* Loop until WIP is cleared  */
        do
        {
            (void)Nor_Flash_Is_Busy(handle, &isBusy);
        } while (isBusy == false);
    }

    return status;
}

status_t Nor_Flash_Erase(nor_handle_t *handle, uint32_t address, uint32_t size_Byte)
{
    assert(handle != NULL);
    assert(size_Byte > 0x00U);
    uint32_t startAddress = address;
    status_t status       = kStatus_Success;

    for (uint32_t i = 0x00U; i <= (size_Byte / handle->bytesInSectorSize); i++)
    {
        status = Nor_Flash_Erase_Sector(handle, startAddress);
        startAddress += handle->bytesInSectorSize;
    }

    return status;
}

status_t Nor_Flash_Erase_Chip(nor_handle_t *handle)
{
    assert(handle != NULL);

    xspi_transfer_t flashXfer;
    status_t status                            = kStatus_Success;
    xspi_mem_nor_handle_t *ptrXspiMemNorHandle = (xspi_mem_nor_handle_t *)(uint32_t)(handle->deviceSpecific);
    bool isBusy                                = false;

    uint32_t xspiInstanceId = XSPI_GetInstance(curXSPIBase);

    /* Write Enable. */
    if (XSPI_NOR_WriteEnable(handle, s_socXspiAmbaBase[xspiInstanceId]) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    flashXfer.deviceAddress   = s_socXspiAmbaBase[xspiInstanceId];
    flashXfer.cmdType         = kXSPI_Command;
    flashXfer.seqIndex        = NOR_CMD_LUT_SEQ_IDX_CHIPERASE;
    flashXfer.data            = NULL;
    flashXfer.dataSize        = 0UL;
    flashXfer.targetGroup     = ptrXspiMemNorHandle->selectedTg;
    flashXfer.lockArbitration = false;

    status = XSPI_TransferBlocking((XSPI_Type *)handle->driverBaseAddr, &flashXfer);

    if (status == kStatus_Success)
    {
        /* Loop until WIP is cleared  */
        do
        {
            (void)Nor_Flash_Is_Busy(handle, &isBusy);
        } while (isBusy == false);
    }

    return status;
}

status_t Nor_Flash_Is_Busy(nor_handle_t *handle, bool *isBusy)
{
    assert(handle != NULL);

    xspi_transfer_t flashXfer;
    status_t status                            = kStatus_Success;
    xspi_mem_nor_handle_t *ptrXspiMemNorHandle = (xspi_mem_nor_handle_t *)(uint32_t)(handle->deviceSpecific);
    uint32_t readBuffer                        = 0UL;
    bool wip                                   = true;

    uint32_t xspiInstanceId = XSPI_GetInstance(curXSPIBase);

    flashXfer.deviceAddress   = s_socXspiAmbaBase[xspiInstanceId];
    flashXfer.cmdType         = kXSPI_Read;
    flashXfer.seqIndex        = NOR_CMD_LUT_SEQ_IDX_READSTATUS;
    flashXfer.data            = &readBuffer;
    flashXfer.dataSize        = 2UL;
    flashXfer.targetGroup     = ptrXspiMemNorHandle->selectedTg;
    flashXfer.lockArbitration = false;

    status = XSPI_TransferBlocking((XSPI_Type *)handle->driverBaseAddr, &flashXfer);

    if (status == kStatus_Success)
    {
        /* Check if WIP is cleared. */
        if (ptrXspiMemNorHandle->norFlashStatusRegInfo.value1Expired)
        {
            wip =
                (((1U << ptrXspiMemNorHandle->norFlashStatusRegInfo.wipLocation) & readBuffer) != 0x0U) ? false : true;
        }
        else
        {
            wip =
                (((1U << ptrXspiMemNorHandle->norFlashStatusRegInfo.wipLocation) & readBuffer) != 0x0U) ? true : false;
        }

        *isBusy = wip;
    }

    return status;
}

status_t Nor_Flash_DeInit(nor_handle_t *handle)
{
    XSPI_Deinit((XSPI_Type *)handle->driverBaseAddr);

    return kStatus_Success;
}
