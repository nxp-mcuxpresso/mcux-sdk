/*
 * Copyright 2024 NXP
 *
 * All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_sfdp_parser.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
const uint8_t g_sfdpXspiProfile1OpiCmdShift[SFDP_XSPI_PROFILE_OPI_CMD_COUNT] = {31U, 28U, 26U, 20U, 25U, 0xFFU, 0xFFU};
const uint8_t g_sfdpXspiProfile2OpiCmdShift[SFDP_XSPI_PROFILE_OPI_CMD_COUNT] = {0xFFU, 13U, 12U,  0xFFU,
                                                                                17U,   19U, 0xFFU};
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
typedef struct _sfdp_func_table_info
{
    uint32_t indexOfArray : 7U;
    uint32_t supported : 1U;
    uint32_t paramTableRevision : 16U;
    uint32_t reserved : 8U;
} sfdp_func_table_info_t;

struct
{
    sfdp_func_table_info_t sectorMapTable;
    sfdp_func_table_info_t rpmcTable;
    sfdp_func_table_info_t fourByteAddrInstTable;
    sfdp_func_table_info_t xSPIProfile1Table;
    sfdp_func_table_info_t xSPIProfile2Table;
    sfdp_func_table_info_t SCCRegMapTable;
    sfdp_func_table_info_t SCCRegMapxSPIProfile2Table;
    sfdp_func_table_info_t SCCRegMapMultiChipTable;
    sfdp_func_table_info_t cmdSeq2OctalDDR;
    sfdp_func_table_info_t x4QualIOWithDS;
    sfdp_func_table_info_t cmdSeq2QuadDDR;
    sfdp_func_table_info_t securePacketRWTable;
} g_sfdpFuncTables;

/*******************************************************************************
 * Code
 ******************************************************************************/

/************************** Static Functions Start ****************************/

static inline uint16_t SFDP_GetParamId(sfdp_param_header_t *ptrParamHeader)
{
    return (ptrParamHeader->idMsb << 8U) | (ptrParamHeader->idLsb);
}

static inline uint16_t SFDP_GetParamRevision(sfdp_param_header_t *ptrParamHeader)
{
    return (ptrParamHeader->majorRev << 8U) | (ptrParamHeader->minorRev);
}

static void SFDP_InterpretSFDPParamHeaders(sfdp_param_header_t *ptrSfdpParamHeaders, sfdp_handle_t *handle)
{
    uint8_t paramTableCount                = handle->nph + 1U;
    sfdp_param_header_t *ptrCurParamHeader = NULL;
    SFDP_SpiReadFunc spiReadTable          = handle->spiRead;

    (void)memset(&g_sfdpFuncTables, 0UL, sizeof(g_sfdpFuncTables));

    for (uint8_t i = 0U; i < paramTableCount; i++)
    {
        ptrCurParamHeader = &(ptrSfdpParamHeaders[i]);
        switch (SFDP_GetParamId(ptrCurParamHeader))
        {
            case 0xFF00U:
            {
                (void)spiReadTable(ptrCurParamHeader->ptp, (uint32_t *)((uint32_t)(&(handle->bfp))),
                                   (4UL * ptrCurParamHeader->len));
                break;
            }
            case 0xFF81U:
            {
                g_sfdpFuncTables.sectorMapTable.supported          = 1U;
                g_sfdpFuncTables.sectorMapTable.indexOfArray       = i;
                g_sfdpFuncTables.sectorMapTable.paramTableRevision = SFDP_GetParamRevision(&(ptrSfdpParamHeaders[i]));
                (void)spiReadTable(ptrCurParamHeader->ptp, (uint32_t *)((uint32_t)(&(handle->sectorMapTable))),
                                   (4UL * ptrCurParamHeader->len));
                break;
            }
            case 0xFF03U:
            {
                g_sfdpFuncTables.rpmcTable.supported    = 1U;
                g_sfdpFuncTables.rpmcTable.indexOfArray = i;
                g_sfdpFuncTables.fourByteAddrInstTable.paramTableRevision =
                    SFDP_GetParamRevision(&(ptrSfdpParamHeaders[i]));
                (void)spiReadTable(ptrCurParamHeader->ptp, (uint32_t *)((uint32_t)(&(handle->rpmcTable))),
                                   (4UL * ptrCurParamHeader->len));
                break;
            }
            case 0xFF84U:
            {
                g_sfdpFuncTables.fourByteAddrInstTable.supported    = 1U;
                g_sfdpFuncTables.fourByteAddrInstTable.indexOfArray = i;
                g_sfdpFuncTables.fourByteAddrInstTable.paramTableRevision =
                    SFDP_GetParamRevision(&(ptrSfdpParamHeaders[i]));
                (void)spiReadTable(ptrCurParamHeader->ptp, (uint32_t *)((uint32_t)(&(handle->fourByteAddrInstTable))),
                                   (4UL * ptrCurParamHeader->len));
                break;
            }
            case 0xFF05U:
            {
                g_sfdpFuncTables.xSPIProfile1Table.supported    = 1U;
                g_sfdpFuncTables.xSPIProfile1Table.indexOfArray = i;
                g_sfdpFuncTables.xSPIProfile1Table.paramTableRevision =
                    SFDP_GetParamRevision(&(ptrSfdpParamHeaders[i]));
                (void)spiReadTable(ptrCurParamHeader->ptp, (uint32_t *)((uint32_t)(&(handle->xSPIProfile1Table))),
                                   (4UL * ptrCurParamHeader->len));
                break;
            }
            case 0xFF06U:
            {
                g_sfdpFuncTables.xSPIProfile2Table.supported    = 1U;
                g_sfdpFuncTables.xSPIProfile2Table.indexOfArray = i;
                g_sfdpFuncTables.xSPIProfile2Table.paramTableRevision =
                    SFDP_GetParamRevision(&(ptrSfdpParamHeaders[i]));
                (void)spiReadTable(ptrCurParamHeader->ptp, (uint32_t *)((uint32_t)(&(handle->xSPIProfile2Table))),
                                   (4UL * ptrCurParamHeader->len));
                break;
            }
            case 0xFF87U:
            {
                g_sfdpFuncTables.SCCRegMapTable.supported          = 1U;
                g_sfdpFuncTables.SCCRegMapTable.indexOfArray       = i;
                g_sfdpFuncTables.SCCRegMapTable.paramTableRevision = SFDP_GetParamRevision(&(ptrSfdpParamHeaders[i]));
                (void)spiReadTable(ptrCurParamHeader->ptp, (uint32_t *)((uint32_t)(&(handle->SCCRegMapTable))),
                                   (4UL * ptrCurParamHeader->len));
                break;
            }
            case 0xFF88U:
            {
                g_sfdpFuncTables.SCCRegMapMultiChipTable.supported    = 1U;
                g_sfdpFuncTables.SCCRegMapMultiChipTable.indexOfArray = i;
                g_sfdpFuncTables.SCCRegMapMultiChipTable.paramTableRevision =
                    SFDP_GetParamRevision(&(ptrSfdpParamHeaders[i]));
                (void)spiReadTable(ptrCurParamHeader->ptp, (uint32_t *)((uint32_t)(&(handle->SCCRegMapMultiChipTable))),
                                   (4UL * ptrCurParamHeader->len));
                break;
            }
            case 0xFF09U:
            {
                g_sfdpFuncTables.SCCRegMapxSPIProfile2Table.supported    = 1U;
                g_sfdpFuncTables.SCCRegMapxSPIProfile2Table.indexOfArray = i;
                g_sfdpFuncTables.SCCRegMapxSPIProfile2Table.paramTableRevision =
                    SFDP_GetParamRevision(&(ptrSfdpParamHeaders[i]));
                (void)spiReadTable(ptrCurParamHeader->ptp,
                                   (uint32_t *)((uint32_t)(&(handle->SCCRegMapxSPIProfile2Table))),
                                   (4UL * ptrCurParamHeader->len));
                break;
            }
            case 0xFF0AU:
            {
                g_sfdpFuncTables.cmdSeq2OctalDDR.supported          = 1U;
                g_sfdpFuncTables.cmdSeq2OctalDDR.indexOfArray       = i;
                g_sfdpFuncTables.cmdSeq2OctalDDR.paramTableRevision = SFDP_GetParamRevision(&(ptrSfdpParamHeaders[i]));
                (void)spiReadTable(ptrCurParamHeader->ptp, (uint32_t *)((uint32_t)(&(handle->cmdSeq2OctalDDR))),
                                   (4UL * ptrCurParamHeader->len));
                break;
            }
            case 0xFF0C:
            {
                g_sfdpFuncTables.x4QualIOWithDS.supported          = 1U;
                g_sfdpFuncTables.x4QualIOWithDS.indexOfArray       = i;
                g_sfdpFuncTables.x4QualIOWithDS.paramTableRevision = SFDP_GetParamRevision(&(ptrSfdpParamHeaders[i]));
                (void)spiReadTable(ptrCurParamHeader->ptp, (uint32_t *)((uint32_t)(&(handle->x4QualIOWithDS))),
                                   (4UL * ptrCurParamHeader->len));
                break;
            }
            case 0xFF8D:
            {
                g_sfdpFuncTables.cmdSeq2QuadDDR.supported          = 1U;
                g_sfdpFuncTables.cmdSeq2QuadDDR.indexOfArray       = i;
                g_sfdpFuncTables.cmdSeq2QuadDDR.paramTableRevision = SFDP_GetParamRevision(&(ptrSfdpParamHeaders[i]));
                (void)spiReadTable(ptrCurParamHeader->ptp, (uint32_t *)((uint32_t)(&(handle->cmdSeq2QuadDDR))),
                                   (4UL * ptrCurParamHeader->len));
                break;
            }
            case 0xFF8E:
            {
                g_sfdpFuncTables.securePacketRWTable.supported    = 1U;
                g_sfdpFuncTables.securePacketRWTable.indexOfArray = i;
                g_sfdpFuncTables.securePacketRWTable.paramTableRevision =
                    SFDP_GetParamRevision(&(ptrSfdpParamHeaders[i]));
                (void)spiReadTable(ptrCurParamHeader->ptp, (uint32_t *)((uint32_t)(&(handle->securePacketRWTable))),
                                   (4UL * ptrCurParamHeader->len));
                break;
            }
            default:
            {
                break;
            }
        }
    }
}

static inline bool SFDP_CheckSignature(sfdp_header_t *ptrSfdpHeader)
{
    return (bool)(ptrSfdpHeader->signature == 0x50444653UL);
}

static void SFDP_Get1PadReadCmd(sfdp_handle_t *handle,
                                sfdp_protocol_type_t protocolType,
                                sfdp_read_cmd_info_t *ptr1PadReadCmdInfo)
{
    if (protocolType == kSFDP_Protocol_1s1s1s)
    {
        ptr1PadReadCmdInfo->dummyCycle  = 8U;
        ptr1PadReadCmdInfo->instruction = 0x0BU;
        if ((handle->addrMode != kSFDP_AddrMode_3ByteOnly) && (g_sfdpFuncTables.fourByteAddrInstTable.supported != 0U))
        {
            /* In case of 4-byte instruction supported. */
            if ((handle->fourByteAddrInstTable.dw1 & 0x2UL) != 0UL)
            {
                ptr1PadReadCmdInfo->instruction = 0x0CU;
            }
        }
    }
    else
    {
        ptr1PadReadCmdInfo->dummyCycle  = handle->bfp.dw22 & 0x1FUL;
        ptr1PadReadCmdInfo->instruction = (handle->bfp.dw22 & 0xFF00UL) >> 8UL;
        if ((handle->addrMode != kSFDP_AddrMode_3ByteOnly) && (g_sfdpFuncTables.fourByteAddrInstTable.supported != 0U))
        {
            /* In case of 4-byte instruction supported. */
            if ((handle->fourByteAddrInstTable.dw1 & 0x2000UL) != 0UL)
            {
                ptr1PadReadCmdInfo->instruction = 0x0EU;
            }
        }
        ptr1PadReadCmdInfo->modeClocks = (handle->bfp.dw22 & 0xE0UL) >> 5UL;
    }
}

static void SFDP_Get2PadReadCmd(sfdp_handle_t *handle,
                                sfdp_protocol_type_t protocolType,
                                sfdp_read_cmd_info_t *ptr2PadReadCmdInfo)
{
    if (protocolType == kSFDP_Protocol_1s1s2s)
    {
        ptr2PadReadCmdInfo->dummyCycle  = (uint8_t)(handle->bfp.dw4 & 0x1FUL);
        ptr2PadReadCmdInfo->modeClocks  = (uint8_t)((handle->bfp.dw4 & 0xE0UL) >> 5UL);
        ptr2PadReadCmdInfo->instruction = (uint8_t)((handle->bfp.dw4 & 0xFF00UL) >> 8UL);
    }
    else if (protocolType == kSFDP_Protocol_1s2s2s)
    {
        ptr2PadReadCmdInfo->dummyCycle  = (uint8_t)((handle->bfp.dw4 & 0x1F0000UL) >> 16UL);
        ptr2PadReadCmdInfo->modeClocks  = (uint8_t)((handle->bfp.dw4 & 0xE00000UL) >> 21UL);
        ptr2PadReadCmdInfo->instruction = (uint8_t)((handle->bfp.dw4 & 0xFF000000UL) >> 24UL);
    }
    else if (protocolType == kSFDP_Protocol_1s2d2d)
    {
        ptr2PadReadCmdInfo->dummyCycle  = (uint8_t)((handle->bfp.dw22 & 0x1F0000UL) >> 16UL);
        ptr2PadReadCmdInfo->modeClocks  = (uint8_t)((handle->bfp.dw22 & 0xE00000UL) >> 21UL);
        ptr2PadReadCmdInfo->instruction = (uint8_t)((handle->bfp.dw22 & 0xFF000000UL) >> 24UL);
        if ((handle->addrMode != kSFDP_AddrMode_3ByteOnly) && (g_sfdpFuncTables.fourByteAddrInstTable.supported != 0U))
        {
            /* In case of 4 byte address mode. */
            if ((handle->fourByteAddrInstTable.dw1 & 0x4000UL) != 0UL)
            {
                ptr2PadReadCmdInfo->instruction = 0xBEU;
            }
        }
    }
    else if (protocolType == kSFDP_Protocol_2s2s2s)
    {
        ptr2PadReadCmdInfo->dummyCycle  = (uint8_t)((handle->bfp.dw6 & 0x1F0000UL) >> 16UL);
        ptr2PadReadCmdInfo->modeClocks  = (uint8_t)((handle->bfp.dw6 & 0xE00000UL) >> 21UL);
        ptr2PadReadCmdInfo->instruction = (uint8_t)((handle->bfp.dw6 & 0xFF000000UL) >> 24UL);
    }
    else
    {
    }
}

static void SFDP_Get4PadReadCmd(sfdp_handle_t *handle,
                                sfdp_protocol_type_t protocolType,
                                uint32_t clkFreq,
                                sfdp_read_cmd_info_t *ptr4PadReadCmdInfo)
{
    if (protocolType == kSFDP_Protocol_1s1s4s)
    {
        ptr4PadReadCmdInfo->dummyCycle  = (uint8_t)((handle->bfp.dw3 & 0x1F0000UL) >> 16UL);
        ptr4PadReadCmdInfo->modeClocks  = (uint8_t)((handle->bfp.dw3 & 0xE00000UL) >> 21UL);
        ptr4PadReadCmdInfo->instruction = (uint8_t)((handle->bfp.dw3 & 0xFF000000UL) >> 24UL);

        if ((handle->addrMode != kSFDP_AddrMode_3ByteOnly) && (g_sfdpFuncTables.fourByteAddrInstTable.supported != 0U))
        {
            if ((handle->fourByteAddrInstTable.dw1 & 0x80UL) != 0UL)
            {
                /* In case of 4byte address mode support for 1s-1s-4s fast read command. */
                ptr4PadReadCmdInfo->instruction = 0x6CU;
            }
        }
    }
    else if (protocolType == kSFDP_Protocol_1s4s4s)
    {
        ptr4PadReadCmdInfo->dummyCycle  = (uint8_t)(handle->bfp.dw3 & 0x1FUL);
        ptr4PadReadCmdInfo->modeClocks  = (uint8_t)((handle->bfp.dw3 & 0xE0UL) >> 5UL);
        ptr4PadReadCmdInfo->instruction = (uint8_t)((handle->bfp.dw3 & 0xFF00UL) >> 8UL);

        if ((handle->addrMode != kSFDP_AddrMode_3ByteOnly) && (g_sfdpFuncTables.fourByteAddrInstTable.supported != 0U))
        {
            if ((handle->fourByteAddrInstTable.dw1 & 0x100UL) != 0UL)
            {
                /* In case of 4byte address mode support for 1s-4s-4s fast read command. */
                ptr4PadReadCmdInfo->instruction = 0xECU;
            }
        }
    }
    else if (protocolType == kSFDP_Protocol_1s4d4d)
    {
        ptr4PadReadCmdInfo->dummyCycle  = handle->bfp.dw23 & 0x1FUL;
        ptr4PadReadCmdInfo->modeClocks  = (handle->bfp.dw23 & 0xE0UL) >> 5UL;
        ptr4PadReadCmdInfo->instruction = (handle->bfp.dw23 & 0xFF00UL) >> 8UL;
        if ((handle->addrMode != kSFDP_AddrMode_3ByteOnly) && (g_sfdpFuncTables.fourByteAddrInstTable.supported != 0U))
        {
            if ((handle->fourByteAddrInstTable.dw1 & 0x8000UL) != 0UL)
            {
                ptr4PadReadCmdInfo->instruction = 0xEEU;
            }
        }
    }
    else if (protocolType == kSFDP_Protocol_4s4s4s)
    {
        ptr4PadReadCmdInfo->dummyCycle  = (uint8_t)((handle->bfp.dw7 & 0x1F0000UL) >> 16UL);
        ptr4PadReadCmdInfo->modeClocks  = (uint8_t)((handle->bfp.dw7 & 0xE00000UL) >> 21UL);
        ptr4PadReadCmdInfo->instruction = (uint8_t)((handle->bfp.dw7 & 0xFF000000UL) >> 24UL);
    }
    else if (protocolType == kSFDP_Protocol_4s4d4d)
    {
        ptr4PadReadCmdInfo->dummyCycle  = (uint8_t)((handle->bfp.dw23 & 0x1F0000UL) >> 16UL);
        ptr4PadReadCmdInfo->modeClocks  = (uint8_t)((handle->bfp.dw23 & 0xE00000UL) >> 21UL);
        ptr4PadReadCmdInfo->instruction = (uint8_t)((handle->bfp.dw23 & 0xFF000000UL) >> 24UL);
        if ((g_sfdpFuncTables.x4QualIOWithDS.supported != 0U) && SFDP_CheckDSSupportedForQpiDtrMode(handle))
        {
            if (clkFreq == 100000000UL)
            {
                ptr4PadReadCmdInfo->dummyCycle = (uint8_t)((handle->x4QualIOWithDS.dw5 & 0xF80UL) >> 7UL);
            }
            else if (clkFreq == 133000000UL)
            {
                ptr4PadReadCmdInfo->dummyCycle = (uint8_t)((handle->x4QualIOWithDS.dw5 & 0x3E0000UL) >> 17UL);
            }
            else if (clkFreq == 166000000UL)
            {
                ptr4PadReadCmdInfo->dummyCycle = (uint8_t)((handle->x4QualIOWithDS.dw5 & 0xF8000000UL) >> 27UL);
            }
            else if (clkFreq == 200000000UL)
            {
                ptr4PadReadCmdInfo->dummyCycle = (uint8_t)((handle->x4QualIOWithDS.dw4 & 0xF80UL) >> 7UL);
            }
            else
            {
            }
        }
    }
    else
    {
    }
}

static void SFDP_Get8PadReadCmd(sfdp_handle_t *handle,
                                sfdp_protocol_type_t protocolType,
                                uint32_t clkFreq,
                                sfdp_read_cmd_info_t *ptr8PadReadCmdInfo)
{
    if (protocolType == kSFDP_Protocol_1s1s8s)
    {
        ptr8PadReadCmdInfo->dummyCycle  = (uint8_t)((handle->bfp.dw17 & 0x1F0000UL) >> 16UL);
        ptr8PadReadCmdInfo->modeClocks  = (uint8_t)((handle->bfp.dw17 & 0xE00000UL) >> 21UL);
        ptr8PadReadCmdInfo->instruction = (uint8_t)((handle->bfp.dw17 & 0xFF000000UL) >> 24UL);
        if ((handle->addrMode != kSFDP_AddrMode_3ByteOnly) && (g_sfdpFuncTables.fourByteAddrInstTable.supported != 0U))
        {
            /* In case of 4 byte address mode. */
            if ((handle->fourByteAddrInstTable.dw1 & 0x800000UL) != 0UL)
            {
                ptr8PadReadCmdInfo->instruction = 0x7CU;
            }
        }
    }
    else if (protocolType == kSFDP_Protocol_1s8s8s)
    {
        ptr8PadReadCmdInfo->dummyCycle  = (uint8_t)(handle->bfp.dw17 & 0x1FUL);
        ptr8PadReadCmdInfo->modeClocks  = (uint8_t)((handle->bfp.dw17 & 0xE0UL) >> 5UL);
        ptr8PadReadCmdInfo->instruction = (uint8_t)((handle->bfp.dw17 & 0xFF00UL) >> 8UL);
        if ((handle->addrMode != kSFDP_AddrMode_3ByteOnly) && (g_sfdpFuncTables.fourByteAddrInstTable.supported != 0U))
        {
            /* In case of 4 byte address mode. */
            if ((handle->fourByteAddrInstTable.dw1 & 0x1000000UL) != 0UL)
            {
                ptr8PadReadCmdInfo->instruction = 0xCCU;
            }
        }
    }
    else if (protocolType == kSFDP_Protocol_1s8d8d)
    {
        if (g_sfdpFuncTables.fourByteAddrInstTable.supported != 0U)
        {
            if ((handle->fourByteAddrInstTable.dw1 & 0x400000UL) != 0UL)
            {
                ptr8PadReadCmdInfo->instruction = 0xFDU;
                ptr8PadReadCmdInfo->dummyCycle  = 16U;
                ptr8PadReadCmdInfo->modeClocks  = 0U;
            }
        }
    }
    else if (protocolType == kSFDP_Protocol_8s8s8s)
    {
        ptr8PadReadCmdInfo->instruction = 0xECU;
        ptr8PadReadCmdInfo->dummyCycle  = 16U;
        ptr8PadReadCmdInfo->modeClocks  = 0U;

        if (g_sfdpFuncTables.xSPIProfile1Table.supported != 0U)
        {
            if (clkFreq == 100000000UL)
            {
                ptr8PadReadCmdInfo->dummyCycle = (uint8_t)((handle->xSPIProfile1Table.dw5 & 0xF80UL) >> 7UL);
            }
            else if (clkFreq == 133000000UL)
            {
                ptr8PadReadCmdInfo->dummyCycle = (uint8_t)((handle->xSPIProfile1Table.dw5 & 0x3E0000UL) >> 12UL);
            }
            else if (clkFreq == 166000000UL)
            {
                ptr8PadReadCmdInfo->dummyCycle = (uint8_t)((handle->xSPIProfile1Table.dw5 & 0xF8000000UL) >> 27UL);
            }
            else if (clkFreq == 200000000UL)
            {
                ptr8PadReadCmdInfo->dummyCycle = (uint8_t)((handle->xSPIProfile1Table.dw4 & 0xF80UL) >> 7UL);
            }
            else
            {
            }
        }
        else if (g_sfdpFuncTables.xSPIProfile2Table.supported != 0U)
        {
            if (clkFreq == 100000000UL)
            {
                ptr8PadReadCmdInfo->dummyCycle = (uint8_t)((handle->xSPIProfile2Table.dw3 & 0xF80UL) >> 7UL);
            }
            else if (clkFreq == 133000000UL)
            {
                ptr8PadReadCmdInfo->dummyCycle = (uint8_t)((handle->xSPIProfile2Table.dw3 & 0x3E0000UL) >> 12UL);
            }
            else if (clkFreq == 166000000UL)
            {
                ptr8PadReadCmdInfo->dummyCycle = (uint8_t)((handle->xSPIProfile2Table.dw3 & 0xF8000000UL) >> 27UL);
            }
            else if (clkFreq == 200000000UL)
            {
                ptr8PadReadCmdInfo->dummyCycle = (uint8_t)((handle->xSPIProfile2Table.dw2 & 0xF80UL) >> 7UL);
            }
            else
            {
            }
        }
    }
    else if (protocolType == kSFDP_Protocol_8d8d8d)
    {
        ptr8PadReadCmdInfo->instruction = 0xCCU;
        ptr8PadReadCmdInfo->dummyCycle  = 16U;
        ptr8PadReadCmdInfo->modeClocks  = 0U;
        if (g_sfdpFuncTables.xSPIProfile1Table.supported != 0U)
        {
            ptr8PadReadCmdInfo->instruction = (uint8_t)((handle->xSPIProfile1Table.dw1 & 0xFF00UL) >> 8UL);
            if (clkFreq == 100000000UL)
            {
                ptr8PadReadCmdInfo->dummyCycle = (uint8_t)((handle->xSPIProfile1Table.dw5 & 0xF80UL) >> 7UL);
            }
            else if (clkFreq == 133000000UL)
            {
                ptr8PadReadCmdInfo->dummyCycle = (uint8_t)((handle->xSPIProfile1Table.dw5 & 0x3E0000UL) >> 12UL);
            }
            else if (clkFreq == 166000000UL)
            {
                ptr8PadReadCmdInfo->dummyCycle = (uint8_t)((handle->xSPIProfile1Table.dw5 & 0xF8000000UL) >> 27UL);
            }
            else if (clkFreq == 200000000UL)
            {
                ptr8PadReadCmdInfo->dummyCycle = (uint8_t)((handle->xSPIProfile1Table.dw4 & 0xF80UL) >> 7UL);
            }
            else
            {
            }
        }
        else if (g_sfdpFuncTables.xSPIProfile2Table.supported != 0U)
        {
            if (clkFreq == 100000000UL)
            {
                ptr8PadReadCmdInfo->dummyCycle = (uint8_t)((handle->xSPIProfile2Table.dw3 & 0xF80UL) >> 7UL);
            }
            else if (clkFreq == 133000000UL)
            {
                ptr8PadReadCmdInfo->dummyCycle = (uint8_t)((handle->xSPIProfile2Table.dw3 & 0x3E0000UL) >> 12UL);
            }
            else if (clkFreq == 166000000UL)
            {
                ptr8PadReadCmdInfo->dummyCycle = (uint8_t)((handle->xSPIProfile2Table.dw3 & 0xF8000000UL) >> 27UL);
            }
            else if (clkFreq == 200000000UL)
            {
                ptr8PadReadCmdInfo->dummyCycle = (uint8_t)((handle->xSPIProfile2Table.dw2 & 0xF80UL) >> 7UL);
            }
            else
            {
            }
        }
    }
    else
    {
    }
}

/************************** Static Functions End ****************************/

/************************ Read SFDP Data Sets Start *************************/

/*!
 * @brief Read SFDP header, and check if SFDP signature is correct.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[in] spiRead The function to read sfdp header.
 *
 * @retval kSFDP_RET_HardwareIssue Fail to read SFDP header due to some hardware issue.
 * @retval kSFDP_RET_Invalid Fail to read SFDP header due to invalid SFDP signature.
 * @retval kSFDP_RET_Success Successfully to read sfdp header.
 */
sfdp_ret_type_t SFDP_ReadSFDPHeader(sfdp_handle_t *handle, SFDP_SpiReadFunc spiRead)
{
    assert(handle != NULL);
    assert(spiRead != NULL);

    status_t status = kStatus_Success;

    /* Read SFDP header: address is 0, size is 8 bytes. */
    sfdp_header_t tmpSfdpHeader;

    status = spiRead(0UL, (uint32_t *)((uint32_t)&tmpSfdpHeader), 8UL);

    if (status != kStatus_Success)
    {
        return kSFDP_RET_HardwareIssue;
    }

    if (SFDP_CheckSignature(&tmpSfdpHeader) == false)
    {
        return kSFDP_RET_Invalid;
    }

    handle->spiRead         = spiRead;
    handle->curJEDECVersion = (sfdp_revsion_t)SFDP_REVISION(tmpSfdpHeader.majorRev, tmpSfdpHeader.minorRev);
    handle->nph             = tmpSfdpHeader.nph;
    handle->access          = tmpSfdpHeader.access;
    return kSFDP_RET_Success;
}

/*!
 * @brief Read SFDP parameter header.
 *
 * @param[out] ptrSfdpParamHeader Pointer to the variable in type of @ref sfdp_param_header_t
                                to store sfdp parameter header.
 * @param[in] nph Number of parameter header.
 * @param[in] spiRead Function to read sfdp parameter header.
 *
 * @retval kStatus_Success Successfully to read SFDP parameter header.
 * @retval kSFDP_RET_HardwareIssue Fail to read SFDP parameter header due to some hardware issues.
 */
sfdp_ret_type_t SFDP_ReadSFDPParameterHeader(sfdp_param_header_t *ptrSfdpParamHeader,
                                             uint8_t nph,
                                             SFDP_SpiReadFunc spiRead)
{
    status_t status;

    status = spiRead(0x8UL, (uint32_t *)((uint32_t)ptrSfdpParamHeader), 8UL * (nph + 1UL));

    if (status != kStatus_Success)
    {
        return kSFDP_RET_HardwareIssue;
    }

    return kSFDP_RET_Success;
}

/*!
 * @brief Read all current serial flash device supported parameter tables.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 *
 * @retval kSFDP_RET_HardwareIssue Fail to read SFDP parameter header due to some hardware issues.
 * @retval kSFDP_RET_Success Successfully to read all supported parameter tables.
 */
sfdp_ret_type_t SFDP_ReadAllSupportedTable(sfdp_handle_t *handle)
{
    sfdp_ret_type_t ret;

    sfdp_param_header_t *ptrSfdpParamHeader = NULL;

    ptrSfdpParamHeader = (sfdp_param_header_t *)(uint32_t)malloc((handle->nph + 1U) * 8U);
    ret                = SFDP_ReadSFDPParameterHeader(ptrSfdpParamHeader, handle->nph, handle->spiRead);

    if (ret != kSFDP_RET_Success)
    {
        free((void *)(uint32_t)ptrSfdpParamHeader);
        return kSFDP_RET_HardwareIssue;
    }

    SFDP_InterpretSFDPParamHeaders(ptrSfdpParamHeader, handle);
    free((void *)(uint32_t)ptrSfdpParamHeader);

    handle->addrMode = SFDP_GetAddressBytes(handle);

    return kSFDP_RET_Success;
}
/************************ Read SFDP Data Sets End *************************/

/******************* Get Flash Basic Attributes Start *********************/
/*!
 * @brief Get Flash Density, the result is in unit of KB.

 * @param[in] ptrBfp Pointer to the variable in type of @ref sfdp_basic_flash_param_table_t.
 *
 * @return In unit of KB, 64 means 64KB(512 Kb)
 */
uint32_t SFDP_GetFlashDensity(sfdp_handle_t *handle)
{
    assert(handle != NULL);

    uint32_t dw        = handle->bfp.dw2;
    uint64_t bitsCount = 0ULL;

    if ((dw & (1UL << 31UL)) == 0UL)
    {
        /* For densities 2 gigabits or less, bit 31 is set to 0b. The field 30:0 defines the size in bits.  */
        bitsCount = (uint64_t)dw + 1ULL;
    }
    else
    {
        dw &= ((1UL << 31UL) - 1UL);
        /* For densities 4 gigabits and above, bit 31 is set to 1. The field 30:0 defines "N" when density is computed
            2^N bits. */
        bitsCount = (1ULL << dw);
    }

    return (uint32_t)(bitsCount >> 13UL);
}

/*!
 * @brief Get page size, the result in unit of Byte.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 *
 * @return The size of page.
 */
uint32_t SFDP_GetPageSize(sfdp_handle_t *handle)
{
    assert(handle != NULL);

    uint8_t n = 0U;

    n = (handle->bfp.dw11 & 0xF0) >> 4U;

    if (n == 0U)
    {
        return 256;
    }
    else
    {
        return 1UL << (uint32_t)n;
    }
}

/*!
 * @brief Get flash interface mode based on input policy, and number of data pad.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[in] cmdPolicy The policy used to select interface mode, in type of @ref sfdp_cmd_policy_t.
 * @param[in] flashPadNum The number of data pad, in type of @ref sfdp_flash_pad_num_t
 *
 * @return Calculated protocol type, in type of @ref sfdp_protocol_type_t.
 */
sfdp_protocol_type_t SFDP_GetFlashProtocolType(sfdp_handle_t *handle,
                                               sfdp_cmd_policy_t cmdPolicy,
                                               sfdp_flash_pad_num_t flashPadNum)
{
    sfdp_protocol_type_t protocolTypeSelected = kSFDP_Protocol_1s1s1s;

    switch (flashPadNum)
    {
        case kSFDP_Flash1Pad:
        {
            if (cmdPolicy >= kSFDP_CmdPolicy_LowestThroughput)
            {
                protocolTypeSelected = kSFDP_Protocol_1s1s1s;
            }
            else
            {
                if ((handle->bfp.dw21 & 0x1UL) != 0UL)
                {
                    protocolTypeSelected = kSFDP_Protocol_1s1d1d;
                }
            }
            break;
        }
        case kSFDP_Flash2Pad:
        {
            if ((cmdPolicy == kSFDP_CmdPolicy_DdrIO) || (cmdPolicy == kSFDP_CmdPolicy_HighestThroughput))
            {
                if ((handle->bfp.dw21 & 0x2UL) != 0UL)
                {
                    protocolTypeSelected = kSFDP_Protocol_1s2d2d;
                }
            }
            else if (cmdPolicy == kSFDP_CmdPolicy_SdrIO)
            {
                if ((handle->bfp.dw1 & 0x100000UL) != 0UL)
                {
                    protocolTypeSelected = kSFDP_Protocol_1s2s2s;
                }
                if ((handle->bfp.dw5 & 0x1UL) != 0UL)
                {
                    protocolTypeSelected = kSFDP_Protocol_2s2s2s;
                }
            }
            else if ((cmdPolicy == kSFDP_CmdPolicy_SdrOutput) || (cmdPolicy == kSFDP_CmdPolicy_LowestThroughput))
            {
                if ((handle->bfp.dw1 & 0x10000UL) != 0UL)
                {
                    protocolTypeSelected = kSFDP_Protocol_1s1s2s;
                }
            }
            else
            {
            }
            break;
        }
        case kSFDP_Flash4Pad:
        {
            if (cmdPolicy == kSFDP_CmdPolicy_DdrIO)
            {
                if ((handle->curJEDECVersion > kSFDP_JESD216E) && ((handle->bfp.dw21 & 0x4UL) != 0UL))
                {
                    protocolTypeSelected = kSFDP_Protocol_1s4d4d;
                }
            }
            else if (cmdPolicy == kSFDP_CmdPolicy_HighestThroughput)
            {
                if ((handle->curJEDECVersion > kSFDP_JESD216E) && ((handle->bfp.dw21 & 0x8UL) != 0UL))
                {
                    protocolTypeSelected = kSFDP_Protocol_4s4d4d;
                }
            }
            else if (cmdPolicy == kSFDP_CmdPolicy_SdrIO)
            {
                if ((handle->bfp.dw1 & 0x200000UL) != 0UL)
                {
                    protocolTypeSelected = kSFDP_Protocol_1s4s4s;
                }

                if ((handle->bfp.dw5 & 0x10UL) != 0UL)
                {
                    protocolTypeSelected = kSFDP_Protocol_4s4s4s;
                }
            }
            else if ((cmdPolicy == kSFDP_CmdPolicy_SdrOutput) || (cmdPolicy == kSFDP_CmdPolicy_LowestThroughput))
            {
                if ((handle->bfp.dw1 & 0x400000UL) != 0UL)
                {
                    protocolTypeSelected = kSFDP_Protocol_1s1s4s;
                }
            }
            else
            {
            }

            break;
        }
        case kSFDP_Flash8Pad:
        {
            if (cmdPolicy == kSFDP_CmdPolicy_SdrIO)
            {
                if ((handle->curJEDECVersion >= kSFDP_JESD216A) && ((handle->bfp.dw17 & 0xFF00UL) != 0UL))
                {
                    protocolTypeSelected = kSFDP_Protocol_1s8s8s;
                }

                protocolTypeSelected = kSFDP_Protocol_8s8s8s;
            }
            else if ((cmdPolicy == kSFDP_CmdPolicy_SdrOutput) || (cmdPolicy == kSFDP_CmdPolicy_LowestThroughput))
            {
                if ((handle->curJEDECVersion >= kSFDP_JESD216A) && ((handle->bfp.dw17 & 0xFF000000UL) != 0UL))
                {
                    protocolTypeSelected = kSFDP_Protocol_1s1s8s;
                }
            }
            else if (cmdPolicy == kSFDP_CmdPolicy_DdrOutput)
            {
                protocolTypeSelected = kSFDP_Protocol_1s8d8d;
            }
            else if (cmdPolicy == kSFDP_CmdPolicy_HighestThroughput)
            {
                protocolTypeSelected = kSFDP_Protocol_8d8d8d;
            }

            break;
        }
        default:
        {
            assert(false);
        }
    }

    return protocolTypeSelected;
}

/******************* Get Flash Basic Attributes End *********************/

/*********************** Get QPI Attributes Start ***********************/
/*!
 * @brief Get sequence to entry 4s-4d-4d mode.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[out] ptrEntrySe The parameter to store sequences to enter 4s-4d-4d mode,
                        in type of @ref sfdp_4s4d4d_entry_seq_t.
 *
 * @retval kSFDP_RET_Success Successfully to get 4s-4d-4d entry sequence.
 * @retval kSFDP_RET_NotImplemented Current serial flash device does not support 4s-4d-4d entry sequence.
 */
sfdp_ret_type_t SFDP_Get4s4d4dEntrySeq(sfdp_handle_t *handle, sfdp_4s4d4d_entry_seq_t *ptrEntrySeq)
{
    if (g_sfdpFuncTables.cmdSeq2QuadDDR.supported != 0UL)
    {
        (void)memcpy((void *)ptrEntrySeq, (void *)(&(handle->cmdSeq2QuadDDR)), sizeof(sfdp_4s4d4d_entry_seq_t));
        return kSFDP_RET_Success;
    }
    else
    {
        return kSFDP_RET_NotImplemented;
    }
}

/*********************** Get QPI Attributes End ***********************/

/*********************** Get OPI Attributes Start ***********************/

/*!
 * @brief Get command extension of input command.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[in] cmd The octal command used to calculate command extension.
 *
 * @return The command extension based on current serial flash device's command policy.
 */
uint8_t SFDP_GetOctalDTRCmdExtension(sfdp_handle_t *handle, uint8_t cmd)
{
    sfdp_octal_dtr_cmd_type_t octalCmdType = SFDP_GetOctalDTRCmdType(handle);
    uint8_t cmdExtension                   = 0U;

    switch (octalCmdType)
    {
        case kSFDP_OctalDTRCmdExtensionSameAsCmd:
        {
            cmdExtension = cmd;
            break;
        }
        case kSFDP_OctalDTRCmdExtensionInvertCmd:
        {
            cmdExtension = (uint8_t)(~cmd);
            break;
        }
        case kSFDP_OctalDTRCmdExtensionCmdForm16Bit:
        {
            cmdExtension = (uint8_t)(0xFFFFU - cmd);
            break;
        }
        default:
        {
            assert(false);
        }
    }

    return cmdExtension;
}

/*!
 * @brief Check if current serial flash device support input OPI(octal spi) command.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param opiCmd The input octal spi command to check.
 *
 * @retval kSFDP_RET_OPICMDNotSupported The input opi command not supported.
 * @retval kSFDP_RET_Success The input opi command supported.
 */
sfdp_ret_type_t SFDP_CheckOPICmdSupported(sfdp_handle_t *handle, sfdp_xspi_profile_opi_cmd_t opiCmd)
{
    uint32_t mask = 0UL;
    uint8_t shift = 0U;

    if (g_sfdpFuncTables.xSPIProfile1Table.supported != 0UL)
    {
        shift = g_sfdpXspiProfile1OpiCmdShift[(uint8_t)opiCmd];
        if (shift != 0xFFU)
        {
            mask = 1UL << shift;
            if ((handle->xSPIProfile1Table.dw3 & mask) == 0UL)
            {
                return kSFDP_RET_OPICMDNotSupported;
            }
        }
    }

    if (g_sfdpFuncTables.xSPIProfile2Table.supported != 0UL)
    {
        shift = g_sfdpXspiProfile2OpiCmdShift[(uint8_t)opiCmd];
        if (shift != 0xFFU)
        {
            mask = 1UL << shift;
            if ((handle->xSPIProfile2Table.dw1 & mask) == 0UL)
            {
                return kSFDP_RET_OPICMDNotSupported;
            }
        }
    }

    if (g_sfdpFuncTables.SCCRegMapTable.supported != 0UL)
    {
        if ((handle->SCCRegMapTable.dw3 & 0x3C0UL) == 0x3C0UL)
        {
            return kSFDP_RET_OPICMDNotSupported;
        }
    }

    return kSFDP_RET_Success;
}

/*!
 * @brief Get 8d-8d-8d(octal DTR) mode entry sequences.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[out] ptrEntrySeq The variable to store sequences to enter 8d-8d-8d mode.
 *
 * @retval kSFDP_RET_Success Successfully to get sequences to enter 8d-8d-8d mode.
 * @retval kSFDP_RET_NotImplemented Current serial flash device do not support sequences to enter 8d-8d-8d mode.
 */
sfdp_ret_type_t SFDP_Get8d8d8dEntrySeq(sfdp_handle_t *handle, sfdp_8d8d8d_entry_seq_t *ptrEntrySeq)
{
    if (g_sfdpFuncTables.cmdSeq2OctalDDR.supported != 0UL)
    {
        (void)memcpy((void *)ptrEntrySeq, (void *)(&(handle->cmdSeq2OctalDDR)), sizeof(sfdp_8d8d8d_entry_seq_t));
        return kSFDP_RET_Success;
    }
    else
    {
        return kSFDP_RET_NotImplemented;
    }
}

/*********************** Get OPI Attributes End ***********************/

/********************* Get Device's Commands Start ********************/
/*!
 * @brief Get read command information.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[in] protocolType The protocol type for current serial flash device.
 * @param[in] clkFreq The frequency of serial clock.
 * @param[out] ptrReadCmdInfo The variable of store read command information,
 *                          please refer to @ref sfdp_read_cmd_info_t for details.
 */
void SFDP_GetReadCmdInfo(sfdp_handle_t *handle,
                         sfdp_protocol_type_t protocolType,
                         uint32_t clkFreq,
                         sfdp_read_cmd_info_t *ptrReadCmdInfo)
{
    assert(handle != NULL);

    if (protocolType >= kSFDP_Protocol_1s1s8s)
    {
        SFDP_Get8PadReadCmd(handle, protocolType, clkFreq, ptrReadCmdInfo);
    }
    else if (protocolType >= kSFDP_Protocol_1s1s4s)
    {
        SFDP_Get4PadReadCmd(handle, protocolType, clkFreq, ptrReadCmdInfo);
    }
    else if (protocolType >= kSFDP_Protocol_1s1s2s)
    {
        SFDP_Get2PadReadCmd(handle, protocolType, ptrReadCmdInfo);
    }
    else
    {
        SFDP_Get1PadReadCmd(handle, protocolType, ptrReadCmdInfo);
    }
}

/*!
 * @brief Get chip erase information.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[out] ptrChipEraseCmdInfo The variable to store chip erase command information,
 *                                  please refer to @ref sfdp_chip_erase_cmd_info_t for details.
 */
void SFDP_GetChipEraseCmdInfo(sfdp_handle_t *handle, sfdp_chip_erase_cmd_info_t *ptrChipEraseCmdInfo)
{
    assert(handle != NULL);

    ptrChipEraseCmdInfo->typicalTime = 0UL;
    if (handle->curJEDECVersion >= kSFDP_JESD216A)
    {
        uint8_t tmp8 = (uint8_t)((handle->bfp.dw11 & 0x7F0000000UL) >> 24UL);

        switch ((tmp8 & 0x60U) >> 5U)
        {
            case 0x0U:
            {
                ptrChipEraseCmdInfo->typicalTime = 16UL * (tmp8 & 0x1FU);
                break;
            }
            case 0x01U:
            {
                ptrChipEraseCmdInfo->typicalTime = 256UL * (tmp8 & 0x1FU);
                break;
            }
            case 0x02U:
            {
                ptrChipEraseCmdInfo->typicalTime = 4000UL * (tmp8 & 0x1FU);
                break;
            }
            case 0x03U:
            {
                ptrChipEraseCmdInfo->typicalTime = 64000UL * (tmp8 & 0x1FU);
                break;
            }
            default:
            {
                assert(false);
            }
        }
    }

    ptrChipEraseCmdInfo->instruction = 0x60U;
}

/*!
 * @brief Get sector erase command information.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[in] type Used to select erase command type, please refer to @ref sfdp_erase_cmd_type_t.
 * @param[out] ptrEraseCmdInfo The variable to store erase command information,
                                please refer to @ref sfdp_erase_cmd_info_t for details.
 *
 * @retval kSFDP_RET_EraseCMDNotSupported Selected type of erase command not supported.
 * @retval kSFDP_RET_Success Successfully to get selected erase command information.
 */
sfdp_ret_type_t SFDP_GetSectorEraseCmdInfo(sfdp_handle_t *handle,
                                           sfdp_erase_cmd_type_t type,
                                           sfdp_erase_cmd_info_t *ptrEraseCmdInfo)
{
    uint32_t sizeFactor = 0UL;
    uint32_t tmp32      = 0UL;

    if (type <= kSFDP_EraseCmdType2)
    {
        tmp32 = handle->bfp.dw8;
    }
    else
    {
        tmp32 = handle->bfp.dw9;
    }

    tmp32 = (tmp32 >> (16UL * ((uint32_t)type % 2UL))) & 0xFFFFUL;

    sizeFactor = tmp32 & 0xFFUL;
    if (sizeFactor == 0UL)
    {
        return kSFDP_RET_EraseCMDNotSupported;
    }

    ptrEraseCmdInfo->eraseSize   = 1UL << sizeFactor;
    ptrEraseCmdInfo->instruction = (tmp32 & 0xFF00UL) >> 8UL;

    if ((handle->addrMode != kSFDP_AddrMode_3ByteOnly) && (g_sfdpFuncTables.fourByteAddrInstTable.supported != 0U))
    {
        ptrEraseCmdInfo->instruction = ((handle->fourByteAddrInstTable.dw2 >> (8 * (uint8_t)(type))) & 0xFFUL);
    }

    tmp32 = (handle->bfp.dw10) >> 4UL;
    tmp32 = (tmp32 >> (7UL * ((uint32_t)type % 2UL))) & 0x7FUL;

    switch ((tmp32 & 0x60U) >> 5U)
    {
        case 0x0UL:
        {
            ptrEraseCmdInfo->typicalTime = tmp32 & 0x1FUL;
            break;
        }
        case 0x1UL:
        {
            ptrEraseCmdInfo->typicalTime = (tmp32 & 0x1FUL) * 16UL;
            break;
        }
        case 0x2UL:
        {
            ptrEraseCmdInfo->typicalTime = (tmp32 & 0x1FUL) * 128UL;
            break;
        }
        case 0x3UL:
        {
            ptrEraseCmdInfo->typicalTime = (tmp32 & 0x1FUL) * 1000UL;
            break;
        }
        default:
        {
            assert(false);
        }
    }

    return kSFDP_RET_Success;
}

/*!
 * @brief Get page program command information.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[in] protocolType The protocol type for current serial flash device.
 * @param[out] ptrPageProgramCmdInfo The variable to store page program command information,
 *                                  please refer to @ref sfdp_page_program_cmd_info_t.
 */
void SFDP_GetPageProgramCmdInfo(sfdp_handle_t *handle,
                                sfdp_protocol_type_t protocolType,
                                sfdp_page_program_cmd_info_t *ptrPageProgramCmdInfo)
{
    uint32_t tmp32 = 0UL;
    if (handle->curJEDECVersion >= kSFDP_JESD216A)
    {
        tmp32 = ((handle->bfp.dw11 & 0x3F00UL) >> 8UL);
        if ((tmp32 & 0x20U) == 0U)
        {
            ptrPageProgramCmdInfo->typicalTime = ((tmp32 & 0x1FUL) + 1UL) * 8UL;
        }
        else
        {
            ptrPageProgramCmdInfo->typicalTime = ((tmp32 & 0x1FUL) + 1UL) * 64UL;
        }
    }

    ptrPageProgramCmdInfo->instruction = 0x02U;

    if ((handle->addrMode != kSFDP_AddrMode_3ByteOnly) && (g_sfdpFuncTables.fourByteAddrInstTable.supported != 0U))
    {
        /* In case of 4 byte address mode. */
        if (protocolType == kSFDP_Protocol_1s1s1s)
        {
            ptrPageProgramCmdInfo->instruction = 0x12U;
        }
        else if (protocolType == kSFDP_Protocol_1s1s4s)
        {
            ptrPageProgramCmdInfo->instruction = 0x34U;
        }
        else if (protocolType == kSFDP_Protocol_1s4s4s)
        {
            ptrPageProgramCmdInfo->instruction = 0x3EU;
        }
        else if (protocolType == kSFDP_Protocol_1s1s8s)
        {
            ptrPageProgramCmdInfo->instruction = 0x84U;
        }
        else if (protocolType == kSFDP_Protocol_1s8s8s)
        {
            ptrPageProgramCmdInfo->instruction = 0x8EU;
        }
        else if (protocolType == kSFDP_Protocol_8d8d8d)
        {
            ptrPageProgramCmdInfo->instruction = 0x12U;
        }
        else
        {
            /* Avoid violation of MISRA C-2012 rules. */
        }
    }
}

/*!
 * @brief Get read status command information.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[in] protocolType The protocol type for current serial flash device.
 * @param[out] ptrReadStatusCmdInfo The variable to store read status command information,
 *                              please refer to @ref sfdp_read_status_cmd_info_t.
 */
void SFDP_GetReadStatusCmdInfo(sfdp_handle_t *handle,
                               sfdp_protocol_type_t protocolType,
                               sfdp_read_status_cmd_info_t *ptrReadStatusCmdInfo)
{
    ptrReadStatusCmdInfo->instruction = 0x05U;
    uint32_t tmp32                    = 0UL;
    if ((g_sfdpFuncTables.SCCRegMapTable.supported != 0U))
    {
        tmp32                          = handle->SCCRegMapTable.dw3;
        ptrReadStatusCmdInfo->addrSize = 8U * (uint8_t)(((tmp32 & 0x30000000UL) >> 28UL) + 1UL);

        if (protocolType == kSFDP_Protocol_1s1s1s)
        {
            if ((tmp32 & 0xC000000UL) == 0x8000000UL)
            {
                ptrReadStatusCmdInfo->dummyCycle = (uint8_t)(tmp32 & 0xFUL);
            }
            else if ((tmp32 & 0xC000000UL) == 0UL)
            {
                ptrReadStatusCmdInfo->dummyCycle = 0U;
            }
            else if ((tmp32 & 0xC000000UL) == 0x4000000UL)
            {
                ptrReadStatusCmdInfo->dummyCycle = 8U;
            }
            else
            {
                assert(false);
            }
        }
        else if (protocolType == kSFDP_Protocol_2s2s2s)
        {
            ptrReadStatusCmdInfo->dummyCycle = (uint8_t)((tmp32 & 0x3C00000UL) >> 22UL);
        }
        else if (protocolType == kSFDP_Protocol_4s4s4s)
        {
            ptrReadStatusCmdInfo->dummyCycle = (uint8_t)((tmp32 & 0x3C0000UL) >> 18UL);
        }
        else if (protocolType == kSFDP_Protocol_4s4d4d)
        {
            ptrReadStatusCmdInfo->dummyCycle = (uint8_t)((tmp32 & 0x3C000UL) >> 14UL);
        }
        else if (protocolType == kSFDP_Protocol_8s8s8s)
        {
            ptrReadStatusCmdInfo->dummyCycle = (uint8_t)((tmp32 & 0x3C00UL) >> 10UL);
        }
        else if (protocolType == kSFDP_Protocol_8d8d8d)
        {
            ptrReadStatusCmdInfo->dummyCycle = (uint8_t)((tmp32 & 0x3C0UL) >> 6UL);
        }
        else
        {
            ptrReadStatusCmdInfo->dummyCycle = 0U;
        }
    }
    else if ((g_sfdpFuncTables.xSPIProfile2Table.supported != 0U) &&
             (g_sfdpFuncTables.SCCRegMapxSPIProfile2Table.supported != 0U))
    {
        ptrReadStatusCmdInfo->addrSize   = 48U;
        ptrReadStatusCmdInfo->dummyCycle = (uint8_t)((handle->SCCRegMapxSPIProfile2Table.dw3 & 0xF800000UL) >> 23UL);
    }
}

/*!
 * @brief Get write status command information.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[out] ptrWriteStatusCmdInfo The variable to stor write status command information,
 *                                  please refer to @ref sfdp_write_status_cmd_info_t.
 */
void SFDP_GetWriteStatusCmdInfo(sfdp_handle_t *handle, sfdp_write_status_cmd_info_t *ptrWriteStatusCmdInfo)
{
    ptrWriteStatusCmdInfo->instruction = 0x01U;
}

/*!
 * @brief Get erase suspend/resume command information.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[out] ptrEraseSuspendResumeCmdInfo The variable to store erase suspend/resume command information, please
 *                                          refer to @ref sfdp_erase_suspend_resume_cmd_info_t for details.
 */
void SFDP_GetEraseSuspendResumeCmdInfo(sfdp_handle_t *handle,
                                       sfdp_erase_suspend_resume_cmd_info_t *ptrEraseSuspendResumeCmdInfo)
{
    uint32_t tmp32                             = 0UL;
    ptrEraseSuspendResumeCmdInfo->suspendInstr = (uint8_t)((handle->bfp.dw13 & 0xFF000000UL) >> 24UL);
    ptrEraseSuspendResumeCmdInfo->resumeInstr  = (uint8_t)((handle->bfp.dw13 & 0xFF0000UL) >> 16UL);

    tmp32 = handle->bfp.dw12;

    if ((tmp32 & 0x60000000UL) == 0x0UL)
    {
        ptrEraseSuspendResumeCmdInfo->eraseMaxLatency = ((((tmp32 & 0x1F000000UL) >> 24UL) + 1UL) * 128UL);
    }
    else if (((tmp32 & 0x60000000UL) >> 29UL) == 0x1UL)
    {
        ptrEraseSuspendResumeCmdInfo->eraseMaxLatency = ((((tmp32 & 0x1F000000UL) >> 24UL) + 1UL) * 1000UL);
    }
    else if (((tmp32 & 0x60000000UL) >> 29UL) == 0x2UL)
    {
        ptrEraseSuspendResumeCmdInfo->eraseMaxLatency = ((((tmp32 & 0x1F000000UL) >> 24UL) + 1UL) * 8000UL);
    }
    else
    {
        ptrEraseSuspendResumeCmdInfo->eraseMaxLatency = ((((tmp32 & 0x1F000000UL) >> 24UL) + 1UL) * 64000UL);
    }

    ptrEraseSuspendResumeCmdInfo->resumeToSuspendInterval = (((tmp32 & 0xF00000UL) >> 20UL) + 1UL) * 64UL;
}

/*!
 * @brief Get program suspend/resume command information.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[out] ptrProgramSuspendResumeCmdInfo The variable to store program suspend/resume command information,
 * please refer to @ref sfdp_program_suspend_cmd_info_t for details.
 */
void SFDP_GetProgramSuspendResumeCmdInfo(sfdp_handle_t *handle,
                                         sfdp_program_suspend_cmd_info_t *ptrProgramSuspendResumeCmdInfo)
{
    uint32_t tmp32                               = 0UL;
    ptrProgramSuspendResumeCmdInfo->suspendInstr = (uint8_t)((handle->bfp.dw13 & 0xFF00UL) >> 8UL);
    ptrProgramSuspendResumeCmdInfo->resumeInstr  = (uint8_t)(handle->bfp.dw13 & 0xFFUL);

    tmp32 = handle->bfp.dw12;

    if ((tmp32 & 0xC0000UL) == 0UL)
    {
        ptrProgramSuspendResumeCmdInfo->eraseMaxLatency = ((((tmp32 & 0x3E000UL) >> 13UL) + 1UL) * 128UL);
    }
    else if ((tmp32 & 0xC0000UL) == (1UL << 18UL))
    {
        ptrProgramSuspendResumeCmdInfo->eraseMaxLatency = ((((tmp32 & 0x3E000UL) >> 13UL) + 1UL) * 1000UL);
    }
    else if ((tmp32 & 0xC0000UL) == (2UL << 18UL))
    {
        ptrProgramSuspendResumeCmdInfo->eraseMaxLatency = ((((tmp32 & 0x3E000UL) >> 13UL) + 1UL) * 8000UL);
    }
    else
    {
        ptrProgramSuspendResumeCmdInfo->eraseMaxLatency = ((((tmp32 & 0x3E000UL) >> 13UL) + 1UL) * 64000UL);
    }

    ptrProgramSuspendResumeCmdInfo->resumeToSuspendInterval = (((tmp32 & 0x1E00UL) >> 9UL) + 1UL) * 64UL;
}

/*!
 * @brief Get deep power down command information.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[out] ptrDeepPowerDownCmdInfo The variable to store deep power down command information, please refer to
 * @ref sfdp_deep_power_down_cmd_info_t for details.
 */
void SFDP_GetDeepPowerDownCmdInfo(sfdp_handle_t *handle, sfdp_deep_power_down_cmd_info_t *ptrDeepPowerDownCmdInfo)
{
    uint32_t tmp32                                   = handle->bfp.dw14;
    ptrDeepPowerDownCmdInfo->enterDeepPowerDownInstr = (uint8_t)((tmp32 & 0x7F800000UL) >> 23UL);
    ptrDeepPowerDownCmdInfo->exitDeepPowerDownDelay  = (uint8_t)((tmp32 & 0x7F8000UL) >> 15UL);

    if ((tmp32 & 0x6000) == 0UL)
    {
        ptrDeepPowerDownCmdInfo->exitDeepPowerDownDelay = (((tmp32 & 0x1F00UL) >> 8UL) + 1UL) * 128UL;
    }
    else if ((tmp32 & 0x6000) == (1UL << 13UL))
    {
        ptrDeepPowerDownCmdInfo->exitDeepPowerDownDelay = (((tmp32 & 0x1F00UL) >> 8UL) + 1UL) * 1000UL;
    }
    else if ((tmp32 & 0x6000) == (2UL << 13UL))
    {
        ptrDeepPowerDownCmdInfo->exitDeepPowerDownDelay = (((tmp32 & 0x1F00UL) >> 8UL) + 1UL) * 8000UL;
    }
    else
    {
        ptrDeepPowerDownCmdInfo->exitDeepPowerDownDelay = (((tmp32 & 0x1F00UL) >> 8UL) + 1UL) * 64000UL;
    }
}

/********************* Get Device's Commands End ********************/

/************** Get Device register bit field information Start ************/
/*!
 * @brief Get busy bit field information.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[in] padNum Number of data pad.
 * @param[out] ptrBusyBitInfo The variable to store busy bit information.
 *
 * @retval kSFDP_RET_Success Successfully to get busy bit field information.
 */
sfdp_ret_type_t SFDP_GetBusyBitInfo(sfdp_handle_t *handle,
                                    sfdp_flash_pad_num_t padNum,
                                    sfdp_wip_bit_info_t *ptrBusyBitInfo)
{
    assert(handle != NULL);

    uint32_t bfpDw14 = handle->bfp.dw14;
    uint32_t sccrDw5 = 0UL;

    ptrBusyBitInfo->upperHalfWordSelected = false;
    if ((bfpDw14 & 0x2UL) != 0UL)
    {
        ptrBusyBitInfo->readInstr  = 0x05U;
        ptrBusyBitInfo->writeInstr = 0x01U;
        ptrBusyBitInfo->polarity   = false;
        ptrBusyBitInfo->location   = 0U;
    }
    else if ((bfpDw14 & 0x4UL) != 0UL)
    {
        ptrBusyBitInfo->readInstr  = 0x70U;
        ptrBusyBitInfo->writeInstr = 0x50U;
        ptrBusyBitInfo->polarity   = true;
        ptrBusyBitInfo->location   = 7U;
    }
    else
    {
        /* Reserved. */
    }

    if ((padNum == kSFDP_Flash1Pad))
    {
        ptrBusyBitInfo->dummyCycles   = 0U;
        ptrBusyBitInfo->addrFollowCmd = false;
    }

    if (g_sfdpFuncTables.SCCRegMapTable.supported)
    {
        sccrDw5 = handle->SCCRegMapTable.dw5;
        if ((sccrDw5 & 0x80000000UL) != 0UL)
        {
            if ((sccrDw5 & 0x10000000UL) != 0UL)
            {
                ptrBusyBitInfo->addrFollowCmd = true;
            }
            else
            {
                ptrBusyBitInfo->addrFollowCmd = false;
            }

            ptrBusyBitInfo->polarity              = ((sccrDw5 & 0x40000000UL) != 0x0UL) ? true : false;
            ptrBusyBitInfo->readInstr             = (uint8_t)((sccrDw5 & 0xFF00UL) >> 8UL);
            ptrBusyBitInfo->upperHalfWordSelected = ((sccrDw5 & 0x10000000UL) != 0UL) ? true : false;
            ptrBusyBitInfo->location              = (uint8_t)((sccrDw5 & 0x7000000UL) >> 24UL);
            ptrBusyBitInfo->dummyCycles           = (uint8_t)((sccrDw5 & 0xF0000UL) >> 16UL);
        }
    }

    return kSFDP_RET_Success;
}

/*!
 * @brief Get WEL(write enable) bit field information.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[in] protocolType Current selected protocol type.
 * @param[out] ptrWelBitInfo The variable to store WEL bit information.
 *
 * @retval kSFDP_RET_Success Successfully to get WEL bit field information.
 */
sfdp_ret_type_t SFDP_GetWELBitInfo(sfdp_handle_t *handle,
                                   sfdp_protocol_type_t protocolType,
                                   sfdp_wel_bit_info_t *ptrWelBitInfo)
{
    assert(handle != NULL);

    uint32_t tmp32 = handle->SCCRegMapTable.dw6;

    if ((tmp32 & (1UL << 31UL)) == 0UL)
    {
        return kSFDP_RET_NotImplemented;
    }

    if ((tmp32 & (1UL << 29UL)) != 0UL)
    {
        return kSFDP_RET_RegBitNotSupported;
    }

    ptrWelBitInfo->dummyCycles = 0U;
    if ((tmp32 & (1UL << 28UL)) == 0UL)
    {
        ptrWelBitInfo->addrFollowCmd = false;

        if ((protocolType == kSFDP_Protocol_4s4s4s) && ((tmp32 & (1UL << 20UL)) != 0UL))
        {
            ptrWelBitInfo->dummyCycles = (uint8_t)((tmp32 & 0xF0000UL) >> 16UL);
        }

        if ((protocolType == kSFDP_Protocol_4s4d4d) && ((tmp32 & (1UL << 21UL)) != 0UL))
        {
            ptrWelBitInfo->dummyCycles = (uint8_t)((tmp32 & 0xF0000UL) >> 16UL);
        }

        if ((protocolType == kSFDP_Protocol_8s8s8s) && ((tmp32 & (1UL << 22UL)) != 0UL))
        {
            ptrWelBitInfo->dummyCycles = (uint8_t)((tmp32 & 0xF0000UL) >> 16UL);
        }

        if ((protocolType == kSFDP_Protocol_8d8d8d) && ((tmp32 & (1UL << 23UL)) != 0UL))
        {
            ptrWelBitInfo->dummyCycles = (uint8_t)((tmp32 & 0xF0000UL) >> 16UL);
        }
    }
    else
    {
        ptrWelBitInfo->addrFollowCmd = true;
    }

    ptrWelBitInfo->readInstr             = (uint8_t)((tmp32 & 0xFF00UL) >> 8UL);
    ptrWelBitInfo->writeInstr            = (uint8_t)(tmp32 & 0xFFUL);
    ptrWelBitInfo->polarity              = ((tmp32 & (1UL << 30UL)) != 0UL);
    ptrWelBitInfo->location              = (uint8_t)((tmp32 & 0x7000000UL) >> 24UL);
    ptrWelBitInfo->upperHalfWordSelected = (bool)((tmp32 & (1UL << 27UL)) != 0UL);
    return kSFDP_RET_Success;
}

/*!
 * @brief Get program error bit field information.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[in] protocolType Specify the protocol type to use.
 * @param[out] ptrProgramErrorBitInfo The variable to store program error bit information.
 *
 * @retval kSFDP_RET_NotImplemented Current serial flash do not implement the parameter table.
 * @retval kSFDP_RET_RegBitNotSupported Current serial flash do not support program error bit.
 * @retval kSFDP_RET_Success Successfully to get program error bit field information.
 */
sfdp_ret_type_t SFDP_GetProgramErrorBitInfo(sfdp_handle_t *handle,
                                            sfdp_protocol_type_t protocolType,
                                            sfdp_program_error_bit_info_t *ptrProgramErrorBitInfo)
{
    assert(handle != NULL);

    uint32_t tmp32 = handle->SCCRegMapTable.dw7;

    if ((tmp32 & (1UL << 31UL)) == 0UL)
    {
        return kSFDP_RET_NotImplemented;
    }

    if ((tmp32 & (1UL << 29UL)) != 0UL)
    {
        return kSFDP_RET_RegBitNotSupported;
    }

    ptrProgramErrorBitInfo->dummyCycles = 0U;
    if ((tmp32 & (1UL << 28UL)) == 0UL)
    {
        ptrProgramErrorBitInfo->addrFollowCmd = false;

        if ((protocolType == kSFDP_Protocol_4s4s4s) && ((tmp32 & (1UL << 20UL)) != 0UL))
        {
            ptrProgramErrorBitInfo->dummyCycles = (uint8_t)((tmp32 & 0xF0000UL) >> 16UL);
        }

        if ((protocolType == kSFDP_Protocol_4s4d4d) && ((tmp32 & (1UL << 21UL)) != 0UL))
        {
            ptrProgramErrorBitInfo->dummyCycles = (uint8_t)((tmp32 & 0xF0000UL) >> 16UL);
        }

        if ((protocolType == kSFDP_Protocol_8s8s8s) && ((tmp32 & (1UL << 22UL)) != 0UL))
        {
            ptrProgramErrorBitInfo->dummyCycles = (uint8_t)((tmp32 & 0xF0000UL) >> 16UL);
        }

        if ((protocolType == kSFDP_Protocol_8d8d8d) && ((tmp32 & (1UL << 23UL)) != 0UL))
        {
            ptrProgramErrorBitInfo->dummyCycles = (uint8_t)((tmp32 & 0xF0000UL) >> 16UL);
        }
    }
    else
    {
        ptrProgramErrorBitInfo->addrFollowCmd = true;
    }

    ptrProgramErrorBitInfo->readInstr             = (uint8_t)((tmp32 & 0xFF00UL) >> 8UL);
    ptrProgramErrorBitInfo->writeInstr            = (uint8_t)(tmp32 & 0xFFUL);
    ptrProgramErrorBitInfo->polarity              = ((tmp32 & (1UL << 30UL)) != 0UL);
    ptrProgramErrorBitInfo->location              = (uint8_t)((tmp32 & 0x7000000UL) >> 24UL);
    ptrProgramErrorBitInfo->upperHalfWordSelected = (bool)((tmp32 & (1UL << 27UL)) != 0UL);
    return kSFDP_RET_Success;
}

/*!
 * @brief Get erase error bit field information.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[in] protocolType Specify the protocol type to use.
 * @param[out] ptrEraseErrorBitInfo The variable to store erase error bit information.
 *
 * @retval kSFDP_RET_NotImplemented Current serial flash do not implement the parameter table.
 * @retval kSFDP_RET_RegBitNotSupported Current serial flash do not support erase error bit.
 * @retval kSFDP_RET_Success Successfully to get erase error bit field information.
 */
sfdp_ret_type_t SFDP_GetEraseErrorBitInfo(sfdp_handle_t *handle,
                                          sfdp_protocol_type_t protocolType,
                                          sfdp_erase_error_bit_info_t *ptrEraseErrorBitInfo)
{
    assert(handle != NULL);

    uint32_t tmp32 = handle->SCCRegMapTable.dw8;

    if ((tmp32 & (1UL << 31UL)) == 0UL)
    {
        return kSFDP_RET_NotImplemented;
    }

    if ((tmp32 & (1UL << 29UL)) != 0UL)
    {
        return kSFDP_RET_RegBitNotSupported;
    }

    ptrEraseErrorBitInfo->dummyCycles = 0U;
    if ((tmp32 & (1UL << 28UL)) == 0UL)
    {
        ptrEraseErrorBitInfo->addrFollowCmd = false;

        if ((protocolType == kSFDP_Protocol_4s4s4s) && ((tmp32 & (1UL << 20UL)) != 0UL))
        {
            ptrEraseErrorBitInfo->dummyCycles = (uint8_t)((tmp32 & 0xF0000UL) >> 16UL);
        }

        if ((protocolType == kSFDP_Protocol_4s4d4d) && ((tmp32 & (1UL << 21UL)) != 0UL))
        {
            ptrEraseErrorBitInfo->dummyCycles = (uint8_t)((tmp32 & 0xF0000UL) >> 16UL);
        }

        if ((protocolType == kSFDP_Protocol_8s8s8s) && ((tmp32 & (1UL << 22UL)) != 0UL))
        {
            ptrEraseErrorBitInfo->dummyCycles = (uint8_t)((tmp32 & 0xF0000UL) >> 16UL);
        }

        if ((protocolType == kSFDP_Protocol_8d8d8d) && ((tmp32 & (1UL << 23UL)) != 0UL))
        {
            ptrEraseErrorBitInfo->dummyCycles = (uint8_t)((tmp32 & 0xF0000UL) >> 16UL);
        }
    }
    else
    {
        ptrEraseErrorBitInfo->addrFollowCmd = true;
    }

    ptrEraseErrorBitInfo->readInstr             = (uint8_t)((tmp32 & 0xFF00UL) >> 8UL);
    ptrEraseErrorBitInfo->writeInstr            = (uint8_t)(tmp32 & 0xFFUL);
    ptrEraseErrorBitInfo->polarity              = ((tmp32 & (1UL << 30UL)) != 0UL);
    ptrEraseErrorBitInfo->location              = (uint8_t)((tmp32 & 0x7000000UL) >> 24UL);
    ptrEraseErrorBitInfo->upperHalfWordSelected = (bool)((tmp32 & (1UL << 27UL)) != 0UL);
    return kSFDP_RET_Success;
}

/*!
 * @brief Get variable dummy cycle information.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[in] protocolType Specify the protocol type to use.
 * @param[out] ptrVariableDCInfo The variable to updated dummy cycle value..
 *
 * @retval kSFDP_RET_NotImplemented Current serial flash do not implement the parameter table.
 * @retval kSFDP_RET_RegBitNotSupported Current serial flash do not support variable dummy cycle bit.
 * @retval kSFDP_RET_Success Successfully to get variable dummy cycle bit field information.
 */
sfdp_ret_type_t SFDP_GetVolatileVariableDummyCycleInfo(sfdp_handle_t *handle,
                                                       sfdp_protocol_type_t protocolType,
                                                       sfdp_variable_dummy_cycle_t *ptrVariableDCInfo)
{
    assert(handle != NULL);

    uint32_t tmp32 = handle->SCCRegMapTable.dw9;

    if ((tmp32 & (1UL << 31UL)) == 0UL)
    {
        return kSFDP_RET_NotImplemented;
    }

    if ((tmp32 & (1UL << 29UL)) != 0UL)
    {
        return kSFDP_RET_RegBitNotSupported;
    }

    ptrVariableDCInfo->dummyCycles = 0U;
    if ((tmp32 & (1UL << 28UL)) == 0UL)
    {
        ptrVariableDCInfo->addrFollowCmd = false;

        if ((protocolType == kSFDP_Protocol_4s4s4s) && ((tmp32 & (1UL << 20UL)) != 0UL))
        {
            ptrVariableDCInfo->dummyCycles = (uint8_t)((tmp32 & 0xF0000UL) >> 16UL);
        }

        if ((protocolType == kSFDP_Protocol_4s4d4d) && ((tmp32 & (1UL << 21UL)) != 0UL))
        {
            ptrVariableDCInfo->dummyCycles = (uint8_t)((tmp32 & 0xF0000UL) >> 16UL);
        }

        if ((protocolType == kSFDP_Protocol_8s8s8s) && ((tmp32 & (1UL << 22UL)) != 0UL))
        {
            ptrVariableDCInfo->dummyCycles = (uint8_t)((tmp32 & 0xF0000UL) >> 16UL);
        }

        if ((protocolType == kSFDP_Protocol_8d8d8d) && ((tmp32 & (1UL << 23UL)) != 0UL))
        {
            ptrVariableDCInfo->dummyCycles = (uint8_t)((tmp32 & 0xF0000UL) >> 16UL);
        }
    }
    else
    {
        ptrVariableDCInfo->addrFollowCmd = true;
    }

    ptrVariableDCInfo->readInstr             = (uint8_t)((tmp32 & 0xFF00UL) >> 8UL);
    ptrVariableDCInfo->writeInstr            = (uint8_t)(tmp32 & 0xFFUL);
    ptrVariableDCInfo->bitFieldWidth         = ((tmp32 & 0x60000000UL) >> 29UL);
    ptrVariableDCInfo->location              = (uint8_t)((tmp32 & 0x7000000UL) >> 24UL);
    ptrVariableDCInfo->upperHalfWordSelected = (bool)((tmp32 & (1UL << 27UL)) != 0UL);

    return kSFDP_RET_Success;
}
/************** Get Device register bit field information End ************/
