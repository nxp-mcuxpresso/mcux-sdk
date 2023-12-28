/*
 * Copyright (c) 2022 ITE.
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_it6161.h"
#include "hdmi_tx.h"
#include "fsl_debug_console.h"

static RX_CAP RxCapability;
static uint8_t CommonBuff[128] = {0U};

static uint8_t bCSCMtx_RGB2YUV_ITU601_16_235[] = {0x00, 0x80, 0x00, 0xB2, 0x04, 0x65, 0x02, 0xE9, 0x00, 0x93, 0x3C,
                                                  0x18, 0x04, 0x55, 0x3F, 0x49, 0x3D, 0x9F, 0x3E, 0x18, 0x04};

static uint8_t bCSCMtx_RGB2YUV_ITU601_0_255[] = {0x10, 0x80, 0x10, 0x09, 0x04, 0x0E, 0x02, 0xC9, 0x00, 0x0F, 0x3D,
                                                 0x84, 0x03, 0x6D, 0x3F, 0xAB, 0x3D, 0xD1, 0x3E, 0x84, 0x03};

static uint8_t bCSCMtx_RGB2YUV_ITU709_16_235[] = {0x00, 0x80, 0x00, 0xB8, 0x05, 0xB4, 0x01, 0x94, 0x00, 0x4a, 0x3C,
                                                  0x17, 0x04, 0x9F, 0x3F, 0xD9, 0x3C, 0x10, 0x3F, 0x17, 0x04};

static uint8_t bCSCMtx_RGB2YUV_ITU709_0_255[] = {0x10, 0x80, 0x10, 0xEa, 0x04, 0x77, 0x01, 0x7F, 0x00, 0xD0, 0x3C,
                                                 0x83, 0x03, 0xAD, 0x3F, 0x4B, 0x3D, 0x32, 0x3F, 0x83, 0x03};

static uint8_t bCSCMtx_YUV2RGB_ITU601_16_235[] = {0x00, 0x00, 0x00, 0x00, 0x08, 0x6B, 0x3A, 0x50, 0x3D, 0x00, 0x08,
                                                  0xF5, 0x0A, 0x02, 0x00, 0x00, 0x08, 0xFD, 0x3F, 0xDA, 0x0D};

static uint8_t bCSCMtx_YUV2RGB_ITU601_0_255[] = {0x04, 0x00, 0xA7, 0x4F, 0x09, 0x81, 0x39, 0xDD, 0x3C, 0x4F, 0x09,
                                                 0xC4, 0x0C, 0x01, 0x00, 0x4F, 0x09, 0xFD, 0x3F, 0x1F, 0x10};

static uint8_t bCSCMtx_YUV2RGB_ITU709_16_235[] = {0x00, 0x00, 0x00, 0x00, 0x08, 0x55, 0x3C, 0x88, 0x3E, 0x00, 0x08,
                                                  0x51, 0x0C, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x84, 0x0E};

static uint8_t bCSCMtx_YUV2RGB_ITU709_0_255[] = {0x04, 0x00, 0xA7, 0x4F, 0x09, 0xBA, 0x3B, 0x4B, 0x3E, 0x4F, 0x09,
                                                 0x57, 0x0E, 0x02, 0x00, 0x4F, 0x09, 0xFE, 0x3F, 0xE8, 0x10};

void HDMITX_LoadRegSetting(display_handle_t *handle, RegSetTable_t *table, uint32_t table_sz)
{
    uint32_t i;

    for (i = 0U; i < table_sz / sizeof(RegSetTable_t); i++)
    {
        if (table[i].invAndMask == 0xFFU)
        {
            HDMITX_WriteI2C_Byte(handle, table[i].offset, table[i].OrMask);
        }
        else
        {
            HDMITX_SetI2C_Byte(handle, table[i].offset, table[i].invAndMask, table[i].OrMask);
        }
    }
}

static void HDMITX_DisableAudioOutput(display_handle_t *handle)
{
    HDMITX_SetI2C_Byte(handle, HDMI_TX_GENERAL_REG04, (B_HDMITX_AUD_RST | B_TX_AREF_RST),
                       (B_HDMITX_AUD_RST | B_TX_AREF_RST));
    HDMITX_SetI2C_Byte(handle, 0x0F, 0x10, 0x10);
}

void HDMITX_VideoReset(display_handle_t *handle)
{
    HDMITX_SetI2C_Byte(handle, HDMI_TX_GENERAL_REG04, B_HDMITX_VID_RST, B_HDMITX_VID_RST);
    HDMITX_SetI2C_Byte(handle, HDMI_TX_GENERAL_REG04, B_HDMITX_VID_RST, 0x00);
    delay1ms(10);
}

static inline void HDMITX_ChangeBank(display_handle_t *handle, uint8_t value)
{
    HDMITX_SetI2C_Byte(handle, 0x0F, 0x03, (uint32_t)value & 0x03U);
}

static void DumpHDMITXReg(display_handle_t *handle)
{
#if (DEBUG_DUMP_HDMITX_REGISTER == 0x01U)
    int i = 0, j = 0;
    uint8_t ucData = 0U;

    PRINTF("       ");
    for (j = 0; j < 16; j++)
    {
        PRINTF(" %02X", j);
        if ((j == 3) || (j == 7) || (j == 11))
        {
            PRINTF("  ");
        }
    }
    PRINTF("\r\n        -----------------------------------------------------\r\n");

    HDMITX_ChangeBank(handle, 0);

    for (i = 0; i < 0x100; i += 16)
    {
        PRINTF("[%3X]  ", i);
        for (j = 0; j < 16; j++)
        {
            if ((i + j) != 0x17)
            {
                HDMITX_ReadI2C_Byte(handle, (uint8_t)((i + j) & 0xFFU), &ucData);
                PRINTF(" %02X", (int)ucData);
            }
            else
            {
                PRINTF(" XX", (int)ucData); // for DDC FIFO
            }
            if ((j == 3) || (j == 7) || (j == 11))
            {
                PRINTF(" -");
            }
        }
        PRINTF("\r\n");
        if ((i % 0x40) == 0x30)
        {
            PRINTF("        -----------------------------------------------------\r\n");
        }
    }
    HDMITX_ChangeBank(handle, 1);
    for (i = 0x130; i < 0x200; i += 16)
    {
        PRINTF("[%3X]  ", i);
        for (j = 0; j < 16; j++)
        {
            HDMITX_ReadI2C_Byte(handle, (uint8_t)((i + j) & 0xFF), &ucData);
            PRINTF(" %02X", (int)ucData);
            if ((j == 3) || (j == 7) || (j == 11))
            {
                PRINTF(" -");
            }
        }
        PRINTF("\r\n");
        if ((i % 0x40) == 0x20)
        {
            PRINTF("        -----------------------------------------------------\r\n");
        }
    }
    PRINTF("        -----------------------------------------------------\r\n");
    HDMITX_ChangeBank(handle, 0);
#endif
}

static void HDMITX_DisableVideoOutput(display_handle_t *handle)
{
    HDMITX_SetI2C_Byte(handle, HDMI_TX_GENERAL_REG04, B_HDMITX_VID_RST, B_HDMITX_VID_RST);
    HDMITX_WriteI2C_Byte(handle, REG_TX_AFE_DRV_CTRL, B_TX_AFE_DRV_RST | B_TX_AFE_DRV_PWD);
    HDMITX_SetI2C_Byte(handle, 0x62, 0x90, 0x00);
    HDMITX_SetI2C_Byte(handle, 0x64, 0x89, 0x00);
}

static inline bool HDMITX_GetSinkHpd(display_handle_t *handle)
{
    uint8_t tx_sys_status = 0;

    HDMITX_ReadI2C_Byte(handle, HDMI_TX_SYS_STATUS_REG0E, &tx_sys_status);

    return (bool)(tx_sys_status & HDMI_TX_SYS_STATUS_REG0E_RHPDetect_MASK);
}

static void HDMITX_ClearDDCFIFO(display_handle_t *handle)
{
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_SYS_DDC_CTRL_REG10, HDMI_TX_SYS_DDC_CTRL_REG10_Reg_MasterSel_MASK);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_SYS_DDC_CTRL_REG15, HDMI_TX_SYS_DDC_CTRL_REG15_RDDC_Req_DDC_FIFO_clear);
}

static void HDMITX_AbortDDC(display_handle_t *handle)
{
    uint8_t SWReset = 0U;
    uint8_t uc = 0U, timeout = 0U, i = 0U;

    // save the SW reset,DDC master,and CP Desire setting.
    HDMITX_ReadI2C_Byte(handle, HDMI_TX_GENERAL_REG04, &SWReset);

    HDMITX_WriteI2C_Byte(handle, HDMI_TX_GENERAL_REG04, (uint32_t)SWReset | (uint32_t)B_TX_HDCP_RST_HDMITX);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_SYS_DDC_CTRL_REG10, HDMI_TX_SYS_DDC_CTRL_REG10_Reg_MasterSel_MASK);

    for (i = 0; i < 2U; i++)
    {
        HDMITX_WriteI2C_Byte(handle, HDMI_TX_SYS_DDC_CTRL_REG15, HDMI_TX_SYS_DDC_CTRL_REG15_RDDC_Req_Abort_DDC_CMD);

        for (timeout = 0; timeout < 200U; timeout++)
        {
            HDMITX_ReadI2C_Byte(handle, HDMI_TX_SYS_DDC_CTRL_REG16, &uc);
            if ((uc & HDMI_TX_SYS_DDC_CTRL_REG16_RDDC_Status_Done_MASK) != 0U)
            {
                break; // success
            }
            if ((uc & (HDMI_TX_SYS_DDC_CTRL_REG16_RDDC_Status_NoACK_MASK |
                       HDMI_TX_SYS_DDC_CTRL_REG16_RDDC_Status_WaitBus_MASK |
                       HDMI_TX_SYS_DDC_CTRL_REG16_RDDC_Status_ArbiLose_MASK)) != 0U)
            {
                break;
            }
            delay1ms(1); // delay 1 ms to stable.
        }
    }
}

static bool getHDMITX_EDIDBytes(
    display_handle_t *handle, uint8_t *pData, uint8_t bSegment, uint8_t offset, uint16_t Count)
{
    uint16_t RemainedCount = 0U, ReqCount = 0U;
    uint8_t bCurrOffset = 0U;
    uint16_t TimeOut    = 0U;
    uint8_t *pBuff      = pData;
    uint8_t ucdata      = 0U;
    uint8_t value       = 0U;

    if (pData == NULL)
    {
        return false;
    }
    HDMITX_ReadI2C_Byte(handle, HDMI_TX_INT_FLAGS_REG06, &value);
    if ((value & HDMI_TX_INT_FLAGS_REG06_RInt_DDCBusHang_MASK) != 0U)
    {
        HDMITX_DEBUG_PRINTF("Called hdmitx_AboutDDC()\n");
        HDMITX_AbortDDC(handle);
    }

    HDMITX_ClearDDCFIFO(handle);

    RemainedCount = Count;
    bCurrOffset   = offset;

    HDMITX_ChangeBank(handle, 0);

    while (RemainedCount > 0U)
    {
        ReqCount = (RemainedCount > DDC_FIFO_MAXREQ) ? DDC_FIFO_MAXREQ : RemainedCount;
        HDMITX_DEBUG_PRINTF("getHDMITX_EDIDBytes(): ReqCount = %d,bCurrOffset = %d\n", (int)ReqCount, (int)bCurrOffset);

        HDMITX_WriteI2C_Byte(handle, HDMI_TX_SYS_DDC_CTRL_REG10, HDMI_TX_SYS_DDC_CTRL_REG10_Reg_MasterSel_MASK);
        HDMITX_WriteI2C_Byte(handle, HDMI_TX_SYS_DDC_CTRL_REG15, HDMI_TX_SYS_DDC_CTRL_REG15_RDDC_Req_DDC_FIFO_clear);

        for (TimeOut = 0; TimeOut < 200U; TimeOut++)
        {
            HDMITX_ReadI2C_Byte(handle, HDMI_TX_SYS_DDC_CTRL_REG16, &value);
            if ((value & HDMI_TX_SYS_DDC_CTRL_REG16_RDDC_Status_Done_MASK) != 0U)
            {
                break;
            }
            HDMITX_ReadI2C_Byte(handle, HDMI_TX_INT_FLAGS_REG06, &ucdata);
            if ((value & (HDMI_TX_SYS_DDC_CTRL_REG16_RDDC_Status_NoACK_MASK |
                          HDMI_TX_SYS_DDC_CTRL_REG16_RDDC_Status_WaitBus_MASK |
                          HDMI_TX_SYS_DDC_CTRL_REG16_RDDC_Status_ArbiLose_MASK)) != 0U ||
                (ucdata & HDMI_TX_INT_FLAGS_REG06_RInt_DDCBusHang_MASK) != 0U)
            {
                HDMITX_DEBUG_PRINTF("Called hdmitx_AboutDDC()\n");
                HDMITX_AbortDDC(handle);
                return false;
            }
        }
        HDMITX_WriteI2C_Byte(handle, HDMI_TX_SYS_DDC_CTRL_REG10, HDMI_TX_SYS_DDC_CTRL_REG10_Reg_MasterSel_MASK);
        HDMITX_WriteI2C_Byte(handle, HDMI_TX_SYS_DDC_CTRL_REG11, HDMI_TX_DDC_EDID_ADDR); // for EDID ucdata get
        HDMITX_WriteI2C_Byte(handle, HDMI_TX_SYS_DDC_CTRL_REG12, bCurrOffset);
        HDMITX_WriteI2C_Byte(handle, HDMI_TX_SYS_DDC_CTRL_REG13, (uint8_t)ReqCount);
        HDMITX_WriteI2C_Byte(handle, HDMI_TX_SYS_DDC_CTRL_REG14, bSegment);
        HDMITX_WriteI2C_Byte(handle, HDMI_TX_SYS_DDC_CTRL_REG15, HDMI_TX_SYS_DDC_CTRL_REG15_RDDC_Req_EDID_read);

        bCurrOffset += (uint8_t)ReqCount;
        RemainedCount -= ReqCount;

        for (TimeOut = 250; TimeOut > 0U; TimeOut--)
        {
            delay1ms(1);
            HDMITX_ReadI2C_Byte(handle, HDMI_TX_SYS_DDC_CTRL_REG16, &ucdata);
            if ((ucdata & HDMI_TX_SYS_DDC_CTRL_REG16_RDDC_Status_Done_MASK) != 0U)
            {
                break;
            }
            if ((ucdata & (HDMI_TX_SYS_DDC_CTRL_REG16_RDDC_Status_NoACK_MASK |
                           HDMI_TX_SYS_DDC_CTRL_REG16_RDDC_Status_WaitBus_MASK |
                           HDMI_TX_SYS_DDC_CTRL_REG16_RDDC_Status_ArbiLose_MASK)) != 0U)
            {
                HDMITX_DEBUG_PRINTF("getHDMITX_EDIDBytes(): DDC_STATUS = %02X,fail.\n", (int)ucdata);
                return false;
            }
        }
        if (TimeOut == 0U)
        {
            HDMITX_DEBUG_PRINTF("getHDMITX_EDIDBytes(): DDC TimeOut. \n", (int)ucdata);
            return false;
        }
        do
        {
            HDMITX_ReadI2C_Byte(handle, HDMI_TX_SYS_DDC_CTRL_REG17, pBuff);
            pBuff++;
            ReqCount--;
        } while (ReqCount > 0U);
    }
    return true;
}

static bool getHDMITX_EDIDBlock(display_handle_t *handle, int32_t EDIDBlockID, uint8_t *pEDIDData)
{
    if (pEDIDData == NULL)
    {
        return false;
    }
    return getHDMITX_EDIDBytes(handle, pEDIDData, (uint8_t)EDIDBlockID / 2U, (uint8_t)((EDIDBlockID % 2) * 128), 128);
}

static bool ParseCEAEDID(uint8_t *pCEAEDID)

{
    uint8_t offset = 0U, End = 0U;
    uint8_t count = 0U;
    uint8_t tag   = 0U;
    uint8_t i     = 0U;

    if (pCEAEDID[0] != 0x02U || pCEAEDID[1] != 0x03U)
    {
        return false;  // not a CEA BLOCK.
    }
    End = pCEAEDID[2]; // CEA description.

    RxCapability.VDOMode[0] = 0x00;
    RxCapability.VDOMode[1] = 0x00;
    RxCapability.VDOMode[2] = 0x00;
    RxCapability.VDOMode[3] = 0x00;
    RxCapability.VDOMode[4] = 0x00;
    RxCapability.VDOMode[5] = 0x00;
    RxCapability.VDOMode[6] = 0x00;
    RxCapability.VDOMode[7] = 0x00;
    RxCapability.PA[0]      = 0x00;
    RxCapability.PA[1]      = 0x00;

    RxCapability.VideoMode = pCEAEDID[3];

    RxCapability.NativeVDOMode = 0xff;

    for (offset = 4; offset < End;)
    {
        tag   = pCEAEDID[offset] >> 5U;
        count = pCEAEDID[offset] & 0x1fU;
        switch (tag)
        {
            case 0x01: // Audio Data Block ;
                RxCapability.AUDDesCount = count / 3U;
                HDMITX_DEBUG_PRINTF("RxCapability.AUDDesCount = %d\n", (int)RxCapability.AUDDesCount);
                offset++;
                for (i = 0U; i < RxCapability.AUDDesCount && i < MAX_AUDDES_COUNT; i++)
                {
                    RxCapability.AUDDes[i].uc[0] = pCEAEDID[offset + i * 3U];
                    RxCapability.AUDDes[i].uc[1] = pCEAEDID[offset + i * 3U + 1U];
                    RxCapability.AUDDes[i].uc[2] = pCEAEDID[offset + i * 3U + 2U];
                }
                offset += count;
                break;

            case 0x02: // Video Data Block ;
                offset++;
                for (i = 0U; i < count; i++)
                {
                    uint8_t VIC                = 0U;
                    RxCapability.NativeVDOMode = 0xff;

                    VIC = (uint8_t)(pCEAEDID[offset + i] & (~0x80U));
                    if (VIC < 64U)
                    {
                        RxCapability.VDOMode[VIC / 8U] |= (1U << (VIC % 8U));
                        HDMITX_DEBUG_PRINTF("VIC = %d, RxCapability.VDOMode[%d]=%02X\n", (int)VIC, (int)VIC / 8,
                                            (int)RxCapability.VDOMode[VIC / 8]);
                        if (((pCEAEDID[offset + i] & 0x80U) != 0U) && (RxCapability.NativeVDOMode == 0xFFU))
                        {
                            RxCapability.NativeVDOMode = VIC;
                            HDMITX_DEBUG_PRINTF("native = %d\n", RxCapability.NativeVDOMode);
                        }
                    }
                }
                offset += count;
                break;

            case 0x03: // Vendor Specific Data Block ;
                offset++;
                RxCapability.IEEEOUI = (uint32_t)pCEAEDID[offset + 2U];
                RxCapability.IEEEOUI <<= 8;
                RxCapability.IEEEOUI += (uint32_t)pCEAEDID[offset + 1U];
                RxCapability.IEEEOUI <<= 8;
                RxCapability.IEEEOUI += (uint32_t)pCEAEDID[offset];
                HDMITX_DEBUG_PRINTF("IEEEOUI = %02X %02X %02X %lx", (int)pCEAEDID[offset + 2],
                                    (int)pCEAEDID[offset + 1], (int)pCEAEDID[offset], RxCapability.IEEEOUI);
                if (RxCapability.IEEEOUI == 0x0C03U)
                {
                    uint8_t nextoffset = 0U;

                    RxCapability.ValidHDMI = 1U;

                    RxCapability.PA[0] = pCEAEDID[offset + 3U];
                    RxCapability.PA[1] = pCEAEDID[offset + 4U];
                    if (count > 5U)
                    {
                        RxCapability.dc.uc = pCEAEDID[offset + 5U] & 0x70U;
                    }
                    if (count > 6U)
                    {
                        RxCapability.MaxTMDSClock = pCEAEDID[offset + 6U];
                    }
                    if (count > 7U)
                    {
                        nextoffset = 8;
                        if ((pCEAEDID[offset + 7U] & 0x80U) != 0U)
                        {
                            nextoffset += 2U;
                        } // latency
                        if ((pCEAEDID[offset + 7U] & 0x40U) != 0U)
                        {
                            nextoffset += 2U;
                        } // interlace latency
                        if ((pCEAEDID[offset + 7U] & 0x20U) != 0U)
                        {
                            HDMITX_DEBUG_PRINTF("next offset = %d", (int)nextoffset);
                            RxCapability.Valid3D = ((pCEAEDID[offset + nextoffset] & 0x80U) != 0U) ? 1U : 0U;
                        } // interlace latency
                    }
                }
                offset += count; // ignore the remaind.

                break;

            case 0x04: // Speaker Data Block ;
                offset++;
                RxCapability.SpeakerAllocBlk.uc[0] = pCEAEDID[offset];
                RxCapability.SpeakerAllocBlk.uc[1] = pCEAEDID[offset + 1U];
                RxCapability.SpeakerAllocBlk.uc[2] = pCEAEDID[offset + 2U];
                offset += 3U;
                break;
            case 0x05: // VESA Data Block ;
                offset += count + 1U;
                break;
            case 0x07:                // Extended Data Block ;
                offset += count + 1U; // ignore
                break;
            default:
                offset += count + 1U; // ignore
                break;
        }
    }
    RxCapability.ValidCEA = 1;

    return true;
}

static uint8_t ParseEDID(display_handle_t *handle)
{
    // collect the EDID ucdata of segment 0
    unsigned char *EDID_Buf = NULL;
    uint8_t CheckSum        = 0U;
    uint8_t BlockCount      = 0U;
    uint8_t err             = 0U;
    // uint8_t bValidCEA = false ;
    uint8_t i = 0U;
    uint8_t j = 0U;

    EDID_Buf               = CommonBuff;
    RxCapability.ValidCEA  = 0;
    RxCapability.ValidHDMI = 0;
    RxCapability.dc.uc     = 0;
    RxCapability.IEEEOUI   = 0;
    getHDMITX_EDIDBlock(handle, 0, EDID_Buf);

    for (i = 0, CheckSum = 0; i < 128U; i++)
    {
        CheckSum += EDID_Buf[i];
        CheckSum &= 0xFFU;
    }
    if (CheckSum != 0U)
    {
        return 0;
    }
    if (EDID_Buf[0] != 0x00U || EDID_Buf[1] != 0xFFU || EDID_Buf[2] != 0xFFU || EDID_Buf[3] != 0xFFU ||
        EDID_Buf[4] != 0xFFU || EDID_Buf[5] != 0xFFU || EDID_Buf[6] != 0xFFU || EDID_Buf[7] != 0x00U)
    {
        return 0;
    }

    BlockCount = EDID_Buf[0x7E];

    if (BlockCount == 0U)
    {
        return 1; // do nothing.
    }
    else if (BlockCount > 4U)
    {
        BlockCount = 4;
    }
    // read all segment for test
    for (i = 1; i <= BlockCount; i++)
    {
        err = (uint8_t)getHDMITX_EDIDBlock(handle, (int32_t)i, EDID_Buf);

        HDMITX_DEBUG_PRINTF("\r\n");
        for (j = 0; j < 128U; j++)
        {
            HDMITX_DEBUG_PRINTF("%02X%c", (int)EDID_Buf[j], ' ');
            if ((j & 7U) == 7U)
            {
                HDMITX_DEBUG_PRINTF("\r\n");
            }
        }

        if (err != 0U)
        {
            if ((RxCapability.ValidHDMI == 0U) && EDID_Buf[0] == 0x2U && EDID_Buf[1] == 0x3U)
            {
                err = (uint8_t)ParseCEAEDID(EDID_Buf);
                HDMITX_DEBUG_PRINTF("err = %s\n", err ? "SUCCESS" : "FAIL");
                if (err != 0U)
                {
                    HDMITX_DEBUG_PRINTF("RxCapability.IEEEOUI = %lx\n", RxCapability.IEEEOUI);
                }
            }
        }
    }
    return err;
}

static bool HDMITX_GetVideoState(display_handle_t *handle)
{
    uint8_t value = 0U;

    HDMITX_ReadI2C_Byte(handle, HDMI_TX_SYS_STATUS_REG0E, &value);

    return (bool)(HDMI_TX_SYS_STATUS_REG0E_TxVidStable_MASK & value);
}

static int32_t HDMITX_CalcRclk(display_handle_t *handle)
{
    uint32_t i   = 0;
    uint32_t sum = 0, RCLKCNT = 0, TimeLoMax = 0, retry = 5;
    uint8_t value = 0U;

    /* Init CEC  */
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_COLOR_SPACE_CONVERSION_REG8D,
                         (HDMI_TX_COLOR_SPACE_CONVERSION_REG8D_RegCECSlvAdr(HDMI_TX_CEC_SLAVE_ADDR) |
                          HDMI_TX_COLOR_SPACE_CONVERSION_REG8D_RegEnCRCLK_MASK));
    delay1ms(10);

    for (i = 0U; i < retry; i++)
    {
        HDMITX_CEC_WriteI2C_Byte(handle, 0x09, 1);
        delay1ms(100);
        HDMITX_CEC_WriteI2C_Byte(handle, 0x09, 0);
        HDMITX_CEC_ReadI2C_Byte(handle, 0x47, &value);
        RCLKCNT = (uint32_t)value;
        RCLKCNT <<= 8U;
        HDMITX_CEC_ReadI2C_Byte(handle, 0x46, &value);
        RCLKCNT |= (uint32_t)value;
        RCLKCNT <<= 8U;
        HDMITX_CEC_ReadI2C_Byte(handle, 0x45, &value);
        RCLKCNT |= (uint32_t)value;
        sum += RCLKCNT;
    }

    sum /= retry;
    RCLKCNT = sum / 1000U;
    HDMITX_CEC_WriteI2C_Byte(handle, 0x0C, (RCLKCNT & 0xFFU));

    /* Disable CEC  */
    HDMITX_SetI2C_Byte(handle, HDMI_TX_COLOR_SPACE_CONVERSION_REG8D,
                       HDMI_TX_COLOR_SPACE_CONVERSION_REG8D_RegEnCRCLK_MASK,
                       HDMI_TX_COLOR_SPACE_CONVERSION_REG8D_RegEnCRCLK(0x00U));

    it6161.hdmi_tx.rclk = (sum << 4U) / 108U;
    HDMITX_DEBUG_PRINTF("hdmi tx rclk = %d.%d MHz", it6161.hdmi_tx.rclk / 1000, it6161.hdmi_tx.rclk % 1000);

    TimeLoMax = (sum << 4) / 10U; /* 10*TxRCLK; */
    if (TimeLoMax > 0x3FFFFU)
    {
        TimeLoMax = 0x3FFFFU;
    }
    HDMITX_WriteI2C_Byte(handle, 0x47, (TimeLoMax & 0xFFU));
    HDMITX_WriteI2C_Byte(handle, 0x48, ((TimeLoMax & 0xFF00U) >> 8U));
    HDMITX_WriteI2C_Byte(handle, 0x49, 0x23);

    return (int32_t)it6161.hdmi_tx.rclk;
}

int32_t HDMITX_CalcPclk(display_handle_t *handle)
{
    uint8_t uc = 0U, RCLKFreqSelRead = 0U;
    int32_t div = 0, i = 0;
    uint32_t sum = 0, count = 0;
    uint32_t value = 0U;

    HDMITX_ChangeBank(handle, 0);
    HDMITX_ReadI2C_Byte(handle, 0x5D, &value);
    RCLKFreqSelRead = (uint8_t)(value & 0x04U) >> 2U;
    /* PCLK Count Pre-Test */
    HDMITX_SetI2C_Byte(handle, 0xD7, 0xF0, 0x80);
    delay1ms(1);
    HDMITX_SetI2C_Byte(handle, 0xD7, 0x80, 0x00);

    HDMITX_ReadI2C_Byte(handle, 0xD7, &value);
    count = value & 0xFU;
    count <<= 8U;
    HDMITX_ReadI2C_Byte(handle, 0xD8, &value);
    count |= value;

    if (RCLKFreqSelRead != 0U)
    {
        count <<= 1U;
    }

    for (div = 7; div > 0; div--)
    {
        if (count < (1U << (uint32_t)(11 - div)))
        {
            break;
        }
    }

    if (div < 0)
    {
        div = 0;
    }

    HDMITX_SetI2C_Byte(handle, 0xD7, 0x70, (uint32_t)div << 4U);

    HDMITX_ReadI2C_Byte(handle, 0xD7, &value);
    uc = (uint8_t)value & 0x7FU;
    for (i = 0, sum = 0; i < 100; i++)
    {
        HDMITX_WriteI2C_Byte(handle, 0xD7, (uint32_t)uc | 0x80U);
        delay1ms(1);
        HDMITX_WriteI2C_Byte(handle, 0xD7, uc);

        HDMITX_ReadI2C_Byte(handle, 0xD7, &value);
        count = value & 0xFU;
        count <<= 8U;
        HDMITX_ReadI2C_Byte(handle, 0xD8, &value);
        count |= value;
        if (RCLKFreqSelRead != 0U)
        {
            count <<= 1U;
        }
        sum += count;
    }
    sum /= 100U;
    count = sum;

    it6161.hdmi_tx.pclk = it6161.hdmi_tx.rclk * 128U / count * 16U; /* 128*16=2048 */
    it6161.hdmi_tx.pclk *= (uint32_t)(1U << (uint32_t)div);

    HDMITX_DEBUG_PRINTF("hdmi tx pclk = %d.%d MHz", it6161.hdmi_tx.pclk / 1000, it6161.hdmi_tx.pclk % 1000);
    return (int32_t)it6161.hdmi_tx.pclk;
}

static void HDMITX_GetDisplayMode(display_handle_t *handle)
{
    int32_t interlaced = 0;
    uint32_t htotal = 0, hdes = 0, hdee = 0, hsyncw = 0, H2ndVRRise = 0;
    uint32_t vtotal = 0, vdes = 0, vdee = 0, vdes2nd = 0, vdee2nd = 0;
    uint32_t VRS2nd = 0;
    uint8_t rega9   = 0;
    uint8_t value   = 0U;

    HDMITX_CalcRclk(handle);
    HDMITX_CalcPclk(handle);

    /* enable video timing read back */
    HDMITX_SetI2C_Byte(handle, 0xA8, 0x08, 0x08);
    HDMITX_ReadI2C_Byte(handle, 0xa9, &value);
    rega9      = value;
    interlaced = (int32_t)((rega9 & 0x04U) >> 2U);

    HDMITX_ReadI2C_Bytes(handle, 0x98, (uint8_t *)&htotal, 2);
    htotal = htotal & 0x0FFFU;
    HDMITX_ReadI2C_Bytes(handle, 0x90, (uint8_t *)&hdes, 2);
    hdes = hdes & 0x0FFFU;
    HDMITX_ReadI2C_Bytes(handle, 0x92, (uint8_t *)&hdee, 2);
    hdee = hdee & 0x0FFFU;
    HDMITX_ReadI2C_Bytes(handle, 0x94, (uint8_t *)&hsyncw, 2);
    hsyncw = hsyncw & 0x0FFFU;

    HDMITX_ReadI2C_Bytes(handle, 0xA6, (uint8_t *)&vtotal, 2);
    vtotal = vtotal & 0x0FFFU;
    HDMITX_ReadI2C_Bytes(handle, 0x9C, (uint8_t *)&vdes, 2);
    vdes = vdes & 0x0FFFU;
    HDMITX_ReadI2C_Bytes(handle, 0x9E, (uint8_t *)&vdee, 2);
    vdee = vdee & 0x0FFFU;
    if (interlaced != 0)
    {
        HDMITX_ReadI2C_Bytes(handle, 0xA2, (uint8_t *)&vdes2nd, 2);
        vdes2nd &= 0x0FFFU;
        HDMITX_ReadI2C_Bytes(handle, 0xA4, (uint8_t *)&vdee2nd, 2);
        vdee2nd &= 0x0FFFU;
        HDMITX_ReadI2C_Bytes(handle, 0xB1, (uint8_t *)&VRS2nd, 2);
        VRS2nd &= 0x0FFFU;
        HDMITX_ReadI2C_Bytes(handle, 0x96, (uint8_t *)&H2ndVRRise, 2);
        H2ndVRRise &= 0x0FFFU;

#if HDMITX_DEBUG_PRINTF
        uint32_t vsyncw2nd = 0, vdew2nd = 0, vfph2nd = 0, vbph2nd = 0;
        uint8_t value = 0U;

        HDMITX_ReadI2C_Byte(handle, 0xA1, &value);
        vsyncw2nd = value;
        vdew2nd   = vdee2nd - vdes2nd;
        vfph2nd   = VRS2nd - vdee;
        vbph2nd   = vdes2nd - VRS2nd - vsyncw2nd;
        HDMITX_DEBUG_PRINTF("vdew2nd    = %d\n", vdew2nd);
        HDMITX_DEBUG_PRINTF("vfph2nd    = %d\n", vfph2nd);
        HDMITX_DEBUG_PRINTF("vbph2nd    = %d\n", vbph2nd);
        HDMITX_DEBUG_PRINTF("VSyncW2nd  = %d\n", vsyncw2nd);
        HDMITX_DEBUG_PRINTF("H2ndVRRise = %d\n", H2ndVRRise);
#endif
    }

    /* disable video timing read back */
    HDMITX_SetI2C_Byte(handle, 0xA8, 0x08, 0x00);
}

static inline void HDMITX_DisableAviInfoframe(display_handle_t *handle)
{
    HDMITX_ChangeBank(handle, 0);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_HDMI_CONTROL_REGCD, 0x00);
}

static inline void HDMITX_EnableAviInfoframe(display_handle_t *handle)
{
    HDMITX_ChangeBank(handle, 0);
    HDMITX_WriteI2C_Byte(
        handle, HDMI_TX_HDMI_CONTROL_REGCD,
        HDMI_TX_HDMI_CONTROL_REGCD_REGPktAVIInfoEn_MASK | HDMI_TX_HDMI_CONTROL_REGCD_REGPktAVIInfoRpt_MASK);
}

void HDMI_AviInfoframeInit(struct hdmi_avi_infoframe *frame)
{
    memset(frame, 0, sizeof(*frame));

    frame->type    = HDMI_INFOFRAME_TYPE_AVI;
    frame->version = 2;
    frame->length  = HDMI_AVI_INFOFRAME_SIZE;
}

static int32_t HDMI_SetupAviInfoframe(struct hdmi_avi_infoframe *frame)
{
    enum hdmi_picture_aspect picture_aspect = HDMI_PICTURE_ASPECT_NONE;
    uint8_t vic                             = 0U;

    if (frame == NULL)
    {
        return -1;
    }
    HDMI_AviInfoframeInit(frame);
    frame->pixel_repeat = 0;

    vic = 2;

    frame->picture_aspect = HDMI_PICTURE_ASPECT_NONE;

    frame->content_type = HDMI_CONTENT_TYPE_GRAPHICS;
    frame->itc          = 0;

    picture_aspect = HDMI_PICTURE_ASPECT_4_3;

    frame->video_code     = vic;
    frame->picture_aspect = picture_aspect;
    frame->active_aspect  = HDMI_ACTIVE_ASPECT_PICTURE;
    frame->scan_mode      = HDMI_SCAN_MODE_UNDERSCAN;

    return 0;
}

uint8_t HDMI_InfoframeChecksum(void *buffer, int32_t size)
{
    uint8_t csum = 0;
    uint8_t *ptr = buffer;
    int32_t i    = 0;

    /* compute checksum */
    for (i = 0; i < size; i++)
    {
        csum += ptr[i];
    }
    return (uint8_t)(256U - csum);
}

void HDMI_InfoframeSetChecksum(void *buffer, int32_t size)
{
    uint8_t *ptr = buffer;

    ptr[3] = HDMI_InfoframeChecksum(buffer, size);
}

int32_t HDMI_AviInfoframePack(struct hdmi_avi_infoframe *frame, void *buffer, int32_t size)
{
    int32_t length = 0;
    uint8_t *ptr   = buffer;

    if (frame->type != HDMI_INFOFRAME_TYPE_AVI || frame->version != 2U || frame->length != HDMI_AVI_INFOFRAME_SIZE)
    {
        return -1;
    }
    length = HDMI_INFOFRAME_HEADER_SIZE + frame->length;

    if (size < length)
    {
        return -1;
    }

    memset(buffer, 0, (uint32_t)size);

    ptr[0] = (uint8_t)frame->type;
    ptr[1] = frame->version;
    ptr[2] = frame->length;
    ptr[3] = 0; /* checksum */

    /* start infoframe payload */
    ptr += HDMI_INFOFRAME_HEADER_SIZE;

    ptr[0] = (((uint8_t)frame->colorspace & 0x3U) << 5U) | ((uint8_t)frame->scan_mode & 0x3U);

    /* Data byte 1, bit 4 has to be set if we provide the active format aspect ratio */
    if (((uint8_t)(frame->active_aspect) & 0xFU) != 0U)
    {
        ptr[0] |= BIT(4);
    }

    /* Bit 3 and 2 indicate if we transmit horizontal/vertical bar data */
    if ((bool)frame->top_bar || (bool)frame->bottom_bar)
    {
        ptr[0] |= BIT(3);
    }

    if ((bool)frame->left_bar || (bool)frame->right_bar)
    {
        ptr[0] |= BIT(2);
    }

    ptr[1] = (((uint8_t)frame->colorimetry & 0x3U) << 6U) | (((uint8_t)frame->picture_aspect & 0x3U) << 4U) |
             ((uint8_t)frame->active_aspect & 0xFU);

    ptr[2] = (((uint8_t)frame->extended_colorimetry & 0x7U) << 4U) |
             (((uint8_t)frame->quantization_range & 0x3U) << 2U) | ((uint8_t)frame->nups & 0x3U);

    if (frame->itc)
    {
        ptr[2] |= BIT(7);
    }

    ptr[3] = frame->video_code & 0x7FU;

    ptr[4] = (((uint8_t)frame->ycc_quantization_range & 0x3U) << 6U) | (((uint8_t)frame->content_type & 0x3U) << 2U) |
             ((uint8_t)frame->pixel_repeat & 0xFU);

    ptr[5]  = (uint8_t)(frame->top_bar & 0xFFU);
    ptr[6]  = (uint8_t)((frame->top_bar >> 8U) & 0xFFU);
    ptr[7]  = (uint8_t)(frame->bottom_bar & 0xFFU);
    ptr[8]  = (uint8_t)((frame->bottom_bar >> 8U) & 0xFFU);
    ptr[9]  = (uint8_t)(frame->left_bar & 0xFFU);
    ptr[10] = (uint8_t)((frame->left_bar >> 8U) & 0xFFU);
    ptr[11] = (uint8_t)(frame->right_bar & 0xFFU);
    ptr[12] = (uint8_t)((frame->right_bar >> 8U) & 0xFFU);

    HDMI_InfoframeSetChecksum(buffer, length);

    return length;
}

static int32_t HDMITX_AviInfoframeSet(display_handle_t *handle)
{
    struct hdmi_avi_infoframe *frame = &it6161.source_avi_infoframe;
    uint8_t buf[32] = {0U}, i = 0U, *ptr = NULL;
    int32_t ret = 0;

    HDMITX_DEBUG_PRINTF("avinfo set\n");
    HDMITX_DisableAviInfoframe(handle);

    ret = HDMI_SetupAviInfoframe(frame);
    if (ret != 0)
    {
        HDMITX_DEBUG_PRINTF("Failed to setup AVI infoframe: %d", ret);
        return ret;
    }
    if ((it6161.hdmi_tx.output_color_space & F_MODE_CLRMOD_MASK) == F_MODE_RGB444)
    {
        frame->colorspace = HDMI_COLORSPACE_RGB;
    }
    if ((it6161.hdmi_tx.output_color_space & F_MODE_CLRMOD_MASK) == F_MODE_YUV444)
    {
        frame->colorspace = HDMI_COLORSPACE_YUV444;
    }
    if ((it6161.hdmi_tx.output_color_space & F_MODE_CLRMOD_MASK) == F_MODE_YUV422)
    {
        frame->colorspace = HDMI_COLORSPACE_YUV422;
    }
    ret = HDMI_AviInfoframePack(&it6161.source_avi_infoframe, buf, (int32_t)sizeof(buf));
    if (ret < 0)
    {
        HDMITX_DEBUG_PRINTF("Failed to pack AVI infoframe: %d", ret);
        return ret;
    }

    /* fill PB */
    HDMITX_ChangeBank(handle, 1);
    ptr = buf + HDMI_INFOFRAME_HEADER_SIZE;
    for (i = 0; i < it6161.source_avi_infoframe.length; i++)
    {
        HDMITX_WriteI2C_Byte(handle, (uint32_t)HDMI_TX_AVIINFO_DB1 + (uint32_t)i, ptr[i]);
    }
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AVIINFO_SUM, buf[3]);

    /* Enable */
    HDMITX_EnableAviInfoframe(handle);

    return 0;
}

int32_t HDMI_AudioInfoframePack(struct hdmi_audio_infoframe *frame, void *buffer, int32_t size)
{
    int32_t length   = 0;
    uint8_t channels = 0U;
    uint8_t *ptr     = buffer;

    if (frame->type != HDMI_INFOFRAME_TYPE_AUDIO || frame->version != 1U || frame->length != HDMI_AUDIO_INFOFRAME_SIZE)
    {
        return -1;
    }

    length = HDMI_INFOFRAME_HEADER_SIZE + frame->length;
    if (size < length)
    {
        return -1;
    }

    memset(buffer, 0, (uint32_t)size);

    if (frame->channels >= 2U)
    {
        channels = frame->channels - 1U;
    }
    else
    {
        channels = 0;
    }

    ptr[0] = (uint8_t)frame->type;
    ptr[1] = frame->version;
    ptr[2] = frame->length;
    ptr[3] = 0; /* checksum */

    /* start infoframe payload */
    ptr += HDMI_INFOFRAME_HEADER_SIZE;

    ptr[0] = (((uint8_t)frame->coding_type & 0xFU) << 4U) | (channels & 0x7U);
    ptr[1] = (((uint8_t)frame->sample_frequency & 0x7U) << 2U) | ((uint8_t)frame->sample_size & 0x3U);
    ptr[2] = (uint8_t)frame->coding_type_ext & 0x1FU;
    ptr[3] = (uint8_t)frame->channel_allocation;
    ptr[4] = ((uint8_t)frame->level_shift_value & 0xFU) << 3U;

    if (frame->downmix_inhibit)
    {
        ptr[4] |= BIT(7);
    }

    HDMI_InfoframeSetChecksum(buffer, length);

    return length;
}

static void HDMITX_AudioInfoframeSet(display_handle_t *handle, uint8_t channels)
{
    struct hdmi_audio_infoframe frame;
    uint8_t buf[16] = {0U};
    int32_t ret     = 0;

    memset((void *)&frame, 0, sizeof(frame));
    frame.channels    = channels;
    frame.coding_type = HDMI_AUDIO_CODING_TYPE_STREAM;

    ret = HDMI_AudioInfoframePack(&frame, buf, (int32_t)sizeof(buf));
    if (ret < 0)
    {
        HDMITX_DEBUG_PRINTF("failed to pack audio infoframe: %d\n", ret);
        return;
    }

    /* set audio Data byte */
    HDMITX_ChangeBank(handle, 1);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_PKT_AUDINFO_SUM, buf[3]);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_PKT_AUDINFO_CC, buf[4]);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_PKT_AUDINFO_SF, buf[5]);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_PKT_AUDINFO_CA, buf[7]);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_PKT_AUDINFO_DM_LSV, buf[8]);

    /* Enable Audio info frame */
    HDMITX_ChangeBank(handle, 0);
    HDMITX_WriteI2C_Byte(
        handle, HDMI_TX_HDMI_CONTROL_REGCE,
        HDMI_TX_HDMI_CONTROL_REGCE_REGPktAudInfoEn_MASK | HDMI_TX_HDMI_CONTROL_REGCE_REGPktAudInfoRpt_MASK);
}

static void setHDMITX_ChStat(display_handle_t *handle, uint8_t ucIEC60958ChStat[])
{
    uint8_t uc = 0U;

    HDMITX_ChangeBank(handle, 1);
    uc = (ucIEC60958ChStat[0] << 1U) & 0x7CU;
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDCHST_MODE, uc);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDCHST_CAT, ucIEC60958ChStat[1]);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDCHST_SRCNUM, (uint32_t)ucIEC60958ChStat[2] & 0xFU);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUD0CHST_CHTNUM, ((uint32_t)ucIEC60958ChStat[2] >> 4U) & 0xFU);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDCHST_CA_FS, ucIEC60958ChStat[3]);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDCHST_OFS_WL, ucIEC60958ChStat[4]);
    HDMITX_ChangeBank(handle, 0);
}

static void setHDMITX_LPCMAudio(display_handle_t *handle, uint8_t AudioSrcNum, uint8_t AudSWL, uint8_t bAudInterface)
{
    uint8_t AudioEnable = 0, AudioFormat = 0, bTDMSetting = 0U;

    switch (AudSWL)
    {
        case 16:
            AudioEnable |= HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudSWL_16bits;
            break;
        case 18:
            AudioEnable |= HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudSWL_18bits;
            break;
        case 20:
            AudioEnable |= HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudSWL_20bits;
            break;
        case 24:
        default:
            AudioEnable |= HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudSWL_24bits;
            break;
    }
    if (bAudInterface == (uint8_t)AUDIO_IF_SPDIF)
    {
        AudioFormat &= (uint8_t)~0x40U; /* not full packet mode */
        AudioEnable |=
            HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudSel_SPDIF | HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudioEn_Enable_Audio_Source_0;
    }
    else
    {
        AudioFormat |= 0x40U; /* full packet mode */
        switch (AudioSrcNum)
        {
            case 4:
                AudioEnable |= HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudioEn_Enable_Audio_Source_3 |
                               HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudioEn_Enable_Audio_Source_2 |
                               HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudioEn_Enable_Audio_Source_1 |
                               HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudioEn_Enable_Audio_Source_0;
                break;

            case 3:
                AudioEnable |= 2U | HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudioEn_Enable_Audio_Source_1 |
                               HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudioEn_Enable_Audio_Source_0;
                break;

            case 2:
                AudioEnable |= 1U | HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudioEn_Enable_Audio_Source_0;
                break;

            case 1:
            default:
                AudioFormat &= (uint8_t)~0x40U;
                AudioEnable |= 0U;
                break;
        }
    }
    AudioFormat |= 0x01U;
    it6161.hdmi_tx.bAudioChannelEnable = AudioEnable;

    HDMITX_ChangeBank(handle, 0);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE0, (uint32_t)AudioEnable & 0xF0U);

    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE1, AudioFormat);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE2, 0xE4);

    if (bAudInterface == (uint8_t)AUDIO_IF_SPDIF)
    {
        HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE3, HDMI_TX_AUDIO_CHANNEL_REGE3_REGChStSel_MASK);
    }
    else
    {
        HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE3, 0);
    }
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE4, 0x00);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE5, 0x00);

    if (bAudInterface == (uint8_t)AUDIO_IF_SPDIF)
    {
        uint8_t i = 0U, value = 0U;

        HDMITX_SetI2C_Byte(handle, 0x5c, (1U << 6U), (1U << 6U));
        for (i = 0; i < 100U; i++)
        {
            HDMITX_ReadI2C_Byte(handle, HDMI_TX_CLOCK_CONTROL_REG5F, &value);
            if ((value & HDMI_TX_CLOCK_CONTROL_REG5F_OSFreqLock_MASK) != 0U)
            {
                break; /* stable clock. */
            }
        }
    }
    else
    {
        HDMITX_ReadI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE5, &bTDMSetting);
        if (bAudInterface == (uint8_t)AUDIO_IF_TDM)
        {
            bTDMSetting |= HDMI_TX_AUDIO_CHANNEL_REGE5_RegEnTDM_MASK;
            bTDMSetting &= 0x9FU;
            bTDMSetting |= (AudioSrcNum - 1U) << 5U;
        }
        else
        {
            bTDMSetting &= (uint8_t)~HDMI_TX_AUDIO_CHANNEL_REGE5_RegEnTDM_MASK;
        }

        /* 1 channel NLPCM, no TDM mode. */
        HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE5, bTDMSetting);
    }
}

static void setHDMITX_NLPCMAudio(display_handle_t *handle, uint8_t bAudInterface)
{
    uint8_t AudioEnable = 0U;
    uint8_t i = 0U, value = 0U;

    /* NLPCM must use standard I2S mode. */
    if (bAudInterface == (uint8_t)AUDIO_IF_SPDIF)
    {
        AudioEnable = HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudSWL_24bits | HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudSel_SPDIF;
    }
    else
    {
        AudioEnable = HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudSWL_24bits;
    }

    HDMITX_ChangeBank(handle, 0);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE0, AudioEnable);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE1, 0x01);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE2, 0xE4);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE3, HDMI_TX_AUDIO_CHANNEL_REGE3_REGChStSel_MASK);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE4, 0x00);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE5, 0x00);

    if (bAudInterface == (uint8_t)AUDIO_IF_SPDIF)
    {
        for (i = 0; i < 100U; i++)
        {
            HDMITX_ReadI2C_Byte(handle, HDMI_TX_CLOCK_CONTROL_REG5F, &value);
            if ((value & HDMI_TX_CLOCK_CONTROL_REG5F_OSFreqLock_MASK) != 0U)
            {
                break;
            }
        }
    }
    else
    {
        HDMITX_ReadI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE5, &value);
        value &= (uint8_t)~HDMI_TX_AUDIO_CHANNEL_REGE5_RegEnTDM_MASK;
        /* 2 channel NLPCM, no TDM mode. */
        HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE5, value);
    }
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE0, (uint32_t)AudioEnable | 0U);
}

static void setHDMITX_HBRAudio(display_handle_t *handle, uint8_t bAudInterface)
{
    HDMITX_ChangeBank(handle, 0);

    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE1, 0x47);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE2, 0xE4);

    if (bAudInterface == (uint8_t)AUDIO_IF_SPDIF)
    {
        HDMITX_WriteI2C_Byte(
            handle, HDMI_TX_AUDIO_CHANNEL_REGE0,
            HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudSWL_24bits | HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudSel_SPDIF);
        HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE3, HDMI_TX_AUDIO_CHANNEL_REGE3_REGChStSel_MASK);
    }
    else
    {
        HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE0, HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudSWL_24bits);
        HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE3, 0);
    }
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE4, 0x08);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE5, HDMI_TX_AUDIO_CHANNEL_REGE5_RegAudHBR_MASK);

    if (bAudInterface == (uint8_t)AUDIO_IF_SPDIF)
    {
        uint8_t i = 0U, value = 0U;

        for (i = 0; i < 100U; i++)
        {
            HDMITX_ReadI2C_Byte(handle, HDMI_TX_CLOCK_CONTROL_REG5F, &value);
            if ((value & HDMI_TX_CLOCK_CONTROL_REG5F_OSFreqLock_MASK) != 0U)
            {
                break;
            }
        }
        HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE0,
                             HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudSWL_24bits |
                                 HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudSel_SPDIF |
                                 HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudioEn_Enable_Audio_Source_0);
    }
    else
    {
        HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE0,
                             HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudSWL_24bits | 3U |
                                 HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudioEn_Enable_Audio_Source_2 | 1U |
                                 HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudioEn_Enable_Audio_Source_0);
    }
    HDMITX_SetI2C_Byte(handle, 0x5c, 1U << 6U, 0x00);
    HDMITX_ReadI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE0, &it6161.hdmi_tx.bAudioChannelEnable);
}

static void setHDMITX_DSDAudio(display_handle_t *handle)
{
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE1, 0x41);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE2, 0xE4);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE0, HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudSWL_24bits);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE3, 0);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE4, 0x00);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE5, HDMI_TX_AUDIO_CHANNEL_REGE5_Reg1BAud_MASK);

    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE0,
                         HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudSWL_24bits | 3U |
                             HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudioEn_Enable_Audio_Source_2 |
                             HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudioEn_Enable_Audio_Source_1 |
                             HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudioEn_Enable_Audio_Source_0);
}

static void setHDMITX_NCTS(display_handle_t *handle, uint8_t Fs)
{
    uint32_t n = 0U, LastCTS = 0;
    bool HBR_mode = false;
    uint8_t value = 0U;

    HDMITX_ReadI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE5, &value);
    if ((HDMI_TX_AUDIO_CHANNEL_REGE5_RegAudHBR_MASK & value) != 0U)
    {
        HBR_mode = true;
    }
    else
    {
        HBR_mode = false;
    }

    switch (Fs)
    {
        case AUDFS_32KHz:
            n = 4096;
            break;
        case AUDFS_44p1KHz:
            n = 6272;
            break;
        case AUDFS_48KHz:
            n = 6144;
            break;
        case AUDFS_88p2KHz:
            n = 12544;
            break;
        case AUDFS_96KHz:
            n = 12288;
            break;
        case AUDFS_176p4KHz:
            n = 25088;
            break;
        case AUDFS_192KHz:
            n = 24576;
            break;
        case AUDFS_768KHz:
            n = 24576;
            break;
        default:
            n = 6144;
            break;
    }

    HDMITX_ChangeBank(handle, 1);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_REGPktAudN0, n & 0xFFU);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_REGPktAudN1, (n >> 8U) & 0xFFU);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_REGPktAudN2, (n >> 16U) & 0xFU);

    HDMITX_WriteI2C_Byte(handle, HDMI_TX_REGPktAudCTS0, LastCTS & 0xFFU);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_REGPktAudCTS1, (LastCTS >> 8U) & 0xFFU);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_REGPktAudCTS2, (LastCTS >> 16U) & 0xFU);
    HDMITX_ChangeBank(handle, 0);

    HDMITX_WriteI2C_Byte(handle, 0xF8, 0xC3);
    HDMITX_WriteI2C_Byte(handle, 0xF8, 0xA5);
    /* D[1] = 0, HW auto count CTS */
    HDMITX_SetI2C_Byte(handle, HDMI_TX_HDMI_CONTROL_REGC5, HDMI_TX_HDMI_CONTROL_REGC5_REGPktAudNCTSSel_MASK, 0x00);
    HDMITX_WriteI2C_Byte(handle, 0xF8, 0xFF);

    if (false == HBR_mode)
    {
        /* LPCM */
        uint8_t uData = 0U, value = 0U;

        HDMITX_ChangeBank(handle, 1);
        Fs = AUDFS_768KHz;
        HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDCHST_CA_FS, 0x00U | (uint32_t)Fs);
        /* OFS is the one's complement of FS */
        Fs = ~Fs;

        HDMITX_ReadI2C_Byte(handle, HDMI_TX_AUDCHST_OFS_WL, &value);
        uData = (0x0fU & value);
        HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDCHST_OFS_WL, ((uint32_t)Fs << 4U) | (uint32_t)uData);
        HDMITX_ChangeBank(handle, 0);
    }
}

static void HDMITX_EnableAudioOutput(display_handle_t *handle,
                                     uint8_t AudioType,
                                     uint8_t bAudInterface,
                                     uint32_t SampleFreq,
                                     uint8_t ChNum,
                                     uint8_t *pIEC60958ChStat)
{
    static uint8_t ucIEC60958ChStat[5] = {0U};
    uint8_t Fs                         = {0U};

    it6161.hdmi_tx.bAudioChannelEnable = 0;
    HDMITX_SetI2C_Byte(handle, HDMI_TX_GENERAL_REG04, (B_HDMITX_AUD_RST | B_TX_AREF_RST),
                       (B_HDMITX_AUD_RST | B_TX_AREF_RST));
    HDMITX_WriteI2C_Byte(
        handle, HDMI_TX_CLOCK_CONTROL_REG58,
        HDMI_TX_CLOCK_CONTROL_REG58_REGAutoOSCLK_MASK | HDMI_TX_CLOCK_CONTROL_REG58_REGMCLKFreq_2x128Fs | 0x01U);

    /* Power on the TxCLK (for CSC) */
    HDMITX_SetI2C_Byte(handle, 0x0F, 0x10, 0x00);

    if (bAudInterface == (uint8_t)AUDIO_IF_SPDIF)
    {
        if (AudioType == (uint8_t)T_AUDIO_HBR)
        {
            HDMITX_WriteI2C_Byte(handle, HDMI_TX_CLOCK_CONTROL_REG58, 0x81);
        }

        HDMITX_SetI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE0, HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudSel_SPDIF,
                           HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudSel_SPDIF);
    }
    else
    {
        HDMITX_SetI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE0, HDMI_TX_AUDIO_CHANNEL_REGE0_REGAudSel_SPDIF, 0x00);
    }

    if (AudioType != T_AUDIO_DSD)
    {
        /* one bit audio have no channel status. */
        switch (SampleFreq)
        {
            case 44100L:
                Fs = AUDFS_44p1KHz;
                break;
            case 88200L:
                Fs = AUDFS_88p2KHz;
                break;
            case 176400L:
                Fs = AUDFS_176p4KHz;
                break;
            case 32000L:
                Fs = AUDFS_32KHz;
                break;
            case 48000L:
                Fs = AUDFS_48KHz;
                break;
            case 96000L:
                Fs = AUDFS_96KHz;
                break;
            case 192000L:
                Fs = AUDFS_192KHz;
                break;
            case 768000L:
                Fs = AUDFS_768KHz;
                break;
            default:
                SampleFreq = 48000L;
                Fs         = AUDFS_48KHz;
                break;
        }

        setHDMITX_NCTS(handle, Fs);
        if (pIEC60958ChStat == NULL)
        {
            ucIEC60958ChStat[0] = 0;
            ucIEC60958ChStat[1] = 0;
            ucIEC60958ChStat[2] = (ChNum + 1U) / 2U;

            if (ucIEC60958ChStat[2] < 1U)
            {
                ucIEC60958ChStat[2] = 1;
            }
            else if (ucIEC60958ChStat[2] > 4U)
            {
                ucIEC60958ChStat[2] = 4;
            }
            ucIEC60958ChStat[3] = Fs;
            ucIEC60958ChStat[4] = (((~Fs) << 4U) & 0xF0U) | CHTSTS_SWCODE;
            pIEC60958ChStat     = ucIEC60958ChStat;
        }
    }
    HDMITX_SetI2C_Byte(handle, HDMI_TX_GENERAL_REG04, (B_HDMITX_AUD_RST | B_TX_AREF_RST), B_TX_AREF_RST);

    switch (AudioType)
    {
        case T_AUDIO_HBR:
            HDMITX_DEBUG_PRINTF("T_AUDIO_HBR\n");
            pIEC60958ChStat[0] |= 1U << 1U;
            pIEC60958ChStat[2] = 0;
            pIEC60958ChStat[3] &= 0xF0U;
            pIEC60958ChStat[3] |= AUDFS_768KHz;
            pIEC60958ChStat[4] |= (((~AUDFS_768KHz) << 4U) & 0xF0U) | 0xBU;
            setHDMITX_ChStat(handle, pIEC60958ChStat);
            setHDMITX_HBRAudio(handle, bAudInterface);
            break;
        case T_AUDIO_DSD:
            HDMITX_DEBUG_PRINTF("T_AUDIO_DSD\n");
            setHDMITX_DSDAudio(handle);
            break;
        case T_AUDIO_NLPCM:
            HDMITX_DEBUG_PRINTF("T_AUDIO_NLPCM\n");
            pIEC60958ChStat[0] |= 1U << 1U;
            setHDMITX_ChStat(handle, pIEC60958ChStat);
            setHDMITX_NLPCMAudio(handle, bAudInterface);
            break;
        case T_AUDIO_LPCM:
            HDMITX_DEBUG_PRINTF("T_AUDIO_LPCM\n");
            pIEC60958ChStat[0] &= (uint8_t) ~(1U << 1U);

            setHDMITX_ChStat(handle, pIEC60958ChStat);
            setHDMITX_LPCMAudio(handle, (ChNum + 1U) / 2U, SUPPORT_AUDI_AudSWL, bAudInterface);
            break;
    }
    HDMITX_SetI2C_Byte(handle, HDMI_TX_INT_MASK_REG09, HDMI_TX_INT_MASK_REG09_REG_AudioOvFlw_MASK, 0x00);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AUDIO_CHANNEL_REGE0, it6161.hdmi_tx.bAudioChannelEnable);

    HDMITX_SetI2C_Byte(handle, HDMI_TX_GENERAL_REG04, (B_HDMITX_AUD_RST | B_TX_AREF_RST), 0);
}

static void HDMITX_AudioProcess(display_handle_t *handle)
{
    if (it6161.hdmi_tx.support_audio != 0U)
    {
        HDMITX_DEBUG_PRINTF("%s: %d, it6161.support_audio = 0x%x\n", __func__, __LINE__, it6161.hdmi_tx.support_audio);
        HDMITX_AudioInfoframeSet(handle, (uint8_t)it6161.hdmi_tx.output_channel);
        HDMITX_EnableAudioOutput(handle, it6161.hdmi_tx.input_audio_type, it6161.hdmi_tx.input_audio_interface,
                                 it6161.hdmi_tx.input_audio_sample_freq, it6161.hdmi_tx.output_channel, NULL);
    }
}

static void HDMITX_SetAvMute(display_handle_t *handle, uint8_t bEnable)
{
    HDMITX_ChangeBank(handle, 0);
    HDMITX_SetI2C_Byte(handle, HDMI_TX_HDMI_CONTROL_REGC1, HDMI_TX_HDMI_CONTROL_REGC1_REGAVMute_MASK,
                       bEnable != 0U ? HDMI_TX_HDMI_CONTROL_REGC1_REGAVMute_MASK : 0U);
    HDMITX_WriteI2C_Byte(
        handle, HDMI_TX_HDMI_CONTROL_REGC6,
        HDMI_TX_HDMI_CONTROL_REGC6_REGPktGenCtrlEn_MASK | HDMI_TX_HDMI_CONTROL_REGC6_REGPktGenCtrlRpt_MASK);
}

static void HDMITX_SetupPclkDiv2(display_handle_t *handle)
{
    if (HDMI_TX_PCLK_DIV2)
    {
        HDMITX_DEBUG_PRINTF("PCLK Divided by 2 mode");
        HDMITX_SetI2C_Byte(handle, HDMI_TX_INPUT_DATA_FORMAT_REG70, HDMI_TX_INPUT_DATA_FORMAT_REG70_Reg_PCLKDiv2_MASK,
                           HDMI_TX_INPUT_DATA_FORMAT_REG70_Reg_PCLKDiv2_MASK);
    }
}

/*************************************************************************
 * Function: HDMITX_SetupCsc
 * Parameter: input_mode -
 *      D[1:0] - Color Mode
 *      D[4] - Colorimetry 0: ITU_BT601 1: ITU_BT709
 *      D[5] - Quantization 0: 0_255 1: 16_235
 *      D[6] - Up/Dn Filter 'Required'
 *         0: no up/down filter
 *         1: enable up/down filter when csc need.
 *      D[7] - Dither Filter 'Required'
 *         0: no dither enabled.
 *         1: enable dither and dither free go "when required".
 * output_mode -
 *      D[1:0] - Color mode.
 * Return: N/A
 * Remark: reg72~reg8D will be programmed depended the input with table
 * **********************************************************************/
static void HDMITX_SetupCsc(display_handle_t *handle)
{
    uint32_t ucData = 0U, csc = 0, i = 0U;
    uint8_t filter      = 0; /* filter is for Video CTRL DN_FREE_GO,EN_DITHER,and ENUDFILT */
    uint8_t input_mode  = it6161.hdmi_tx.input_color_space;
    uint8_t output_mode = it6161.hdmi_tx.output_color_space;
    uint8_t *ptable     = NULL;

    /* (1) YUV422 in,RGB/YUV444 output (Output is 8-bit,input is 12-bit)
     * (2) YUV444/422  in,RGB output (CSC enable,and output is not YUV422)
     * (3) RGB in,YUV444 output   (CSC enable,and output is not YUV422)
     *
     * YUV444/RGB24 <-> YUV422 need set up/down filter.
     */
    HDMITX_DEBUG_PRINTF("hdmi_tx_setup_csc(uint8_t input_mode = %x,uint8_t output_mode = %x)\n", (int)input_mode,
                        (int)output_mode);

    switch (input_mode & F_MODE_CLRMOD_MASK)
    {
        /* YUV444 INPUT */
        case F_MODE_YUV444:
            switch (output_mode & F_MODE_CLRMOD_MASK)
            {
                case F_MODE_YUV444:
                    csc = HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_CSCSel_BYPASS;
                    break;
                case F_MODE_YUV422:
                    /* YUV444 to YUV422 need up/down filter for processing. */
                    if ((input_mode & F_VIDMODE_EN_UDFILT) != 0U)
                    {
                        filter |= HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_EN_UDFILTER_MASK;
                    }
                    csc = HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_CSCSel_BYPASS;
                    break;
                case F_MODE_RGB444:
                    csc = HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_CSCSel_YUV2RGB;
                    /* YUV444 to RGB24 need dither */
                    if ((input_mode & F_VIDMODE_EN_DITHER) != 0U)
                    {
                        filter |= HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_EN_DITHER_MASK |
                                  HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_DNFREE_GO_MASK;
                    }
                    break;
            }

        /* YUV422 INPUT */
        case F_MODE_YUV422:
            switch (output_mode & F_MODE_CLRMOD_MASK)
            {
                case F_MODE_YUV444:
                    csc = HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_CSCSel_BYPASS;
                    if ((input_mode & F_VIDMODE_EN_UDFILT) != 0U)
                    {
                        filter |= HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_EN_UDFILTER_MASK;
                    }
                    else if ((input_mode & F_VIDMODE_EN_DITHER) != 0U)
                    {
                        filter |= HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_EN_DITHER_MASK |
                                  HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_DNFREE_GO_MASK;
                    }
                    break;
                case F_MODE_YUV422:
                    csc = HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_CSCSel_BYPASS;
                    break;
                case F_MODE_RGB444:
                    csc = HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_CSCSel_YUV2RGB;
                    if ((input_mode & F_VIDMODE_EN_UDFILT) != 0U)
                    {
                        filter |= HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_EN_UDFILTER_MASK;
                    }
                    else if ((input_mode & F_VIDMODE_EN_DITHER) != 0U)
                    {
                        filter |= HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_EN_DITHER_MASK |
                                  HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_DNFREE_GO_MASK;
                    }
                    break;
            }

        /* RGB444 INPUT */
        case F_MODE_RGB444:
            switch (output_mode & F_MODE_CLRMOD_MASK)
            {
                case F_MODE_YUV444:
                    csc = HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_CSCSel_RGB2YUV;
                    if ((input_mode & F_VIDMODE_EN_DITHER) != 0U)
                    {
                        filter |= HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_EN_DITHER_MASK |
                                  HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_DNFREE_GO_MASK;
                    }
                    break;
                case F_MODE_YUV422:
                    if ((input_mode & F_VIDMODE_EN_UDFILT) != 0U)
                    {
                        filter |= HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_EN_UDFILTER_MASK;
                    }
                    else if ((input_mode & F_VIDMODE_EN_DITHER) != 0U)
                    {
                        filter |= HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_EN_DITHER_MASK |
                                  HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_DNFREE_GO_MASK;
                    }
                    csc = HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_CSCSel_RGB2YUV;
                    break;
                case F_MODE_RGB444:
                    csc = HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_CSCSel_BYPASS;
                    break;
            }
    }

    /* set the CSC metrix registers by colorimetry and quantization */
    if (csc == HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_CSCSel_RGB2YUV)
    {
        switch (input_mode & (F_VIDMODE_ITU709 | F_VIDMODE_16_235))
        {
            case F_VIDMODE_ITU709 | F_VIDMODE_16_235:
                ptable = bCSCMtx_RGB2YUV_ITU709_16_235;
                break;
            case F_VIDMODE_ITU709 | F_VIDMODE_0_255:
                ptable = bCSCMtx_RGB2YUV_ITU709_0_255;
                break;
            case F_VIDMODE_ITU601 | F_VIDMODE_16_235:
                ptable = bCSCMtx_RGB2YUV_ITU601_16_235;
                break;
            case F_VIDMODE_ITU601 | F_VIDMODE_0_255:
            default:
                ptable = bCSCMtx_RGB2YUV_ITU601_0_255;
                break;
        }
    }

    if (csc == HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_CSCSel_YUV2RGB)
    {
        switch (input_mode & (F_VIDMODE_ITU709 | F_VIDMODE_16_235))
        {
            case F_VIDMODE_ITU709 | F_VIDMODE_16_235:
                ptable = bCSCMtx_YUV2RGB_ITU709_16_235;
                break;
            case F_VIDMODE_ITU709 | F_VIDMODE_0_255:
                ptable = bCSCMtx_YUV2RGB_ITU709_0_255;
                break;
            case F_VIDMODE_ITU601 | F_VIDMODE_16_235:
                ptable = bCSCMtx_YUV2RGB_ITU601_16_235;
                break;
            case F_VIDMODE_ITU601 | F_VIDMODE_0_255:
            default:
                ptable = bCSCMtx_YUV2RGB_ITU601_0_255;
                break;
        }
    }

    if (csc == HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_CSCSel_BYPASS)
    {
        HDMITX_SetI2C_Byte(handle, 0xF, 0x10, 0x10);
    }
    else
    {
        if (ptable != NULL)
        {
            for (i = 0; i < SIZEOF_CSCMTX; i++)
            {
                HDMITX_WriteI2C_Byte(handle, (uint32_t)HDMI_TX_COLOR_SPACE_CONVERSION_REG73 + (uint32_t)i, ptable[i]);
            }
        }
        HDMITX_SetI2C_Byte(handle, 0xF, 0x10, 0x00);
    }

    HDMITX_ReadI2C_Byte(handle, HDMI_TX_INPUT_DATA_FORMAT_REG72, &ucData);
    ucData &=
        ~(HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_CSCSel_MASK | HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_DNFREE_GO_MASK |
          HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_EN_DITHER_MASK | HDMI_TX_INPUT_DATA_FORMAT_REG72_Reg_EN_UDFILTER_MASK);
    ucData |= filter | csc;

    HDMITX_WriteI2C_Byte(handle, HDMI_TX_INPUT_DATA_FORMAT_REG72, ucData);
}

static void HDMITX_SetupAfe(display_handle_t *handle, uint8_t level)
{
    HDMITX_WriteI2C_Byte(handle, REG_TX_AFE_DRV_CTRL, B_TX_AFE_DRV_RST);
    switch (level)
    {
        case PCLK_HIGH:
            HDMITX_SetI2C_Byte(handle, 0x62, 0x90, 0x80);
            HDMITX_SetI2C_Byte(handle, 0x64, 0x89, 0x80);
            HDMITX_SetI2C_Byte(handle, 0x68, 0x10, 0x00);
            HDMITX_SetI2C_Byte(handle, 0x66, 0x80, 0x80);
            break;
        default:
            HDMITX_SetI2C_Byte(handle, 0x62, 0x90, 0x10);
            HDMITX_SetI2C_Byte(handle, 0x64, 0x89, 0x09);
            HDMITX_SetI2C_Byte(handle, 0x68, 0x10, 0x10);
            break;
    }
    HDMITX_DEBUG_PRINTF("setup afe: %s", level ? "high" : "low");
}

/* force abort DDC and reset DDC bus */
static void HDMITX_AbortDdc(display_handle_t *handle)
{
    uint8_t sw_reset = 0U, retry = 2;
    uint8_t uc = 0U, timeout = 0U, i = 0U;

    HDMITX_DEBUG_PRINTF("ddc abort\n");
    /* save the sw reset, ddc master and cp desire setting */
    HDMITX_ReadI2C_Byte(handle, HDMI_TX_GENERAL_REG04, &sw_reset);

    HDMITX_WriteI2C_Byte(handle, HDMI_TX_GENERAL_REG04, (uint32_t)sw_reset | (uint32_t)B_TX_HDCP_RST_HDMITX);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_SYS_DDC_CTRL_REG10, HDMI_TX_SYS_DDC_CTRL_REG10_Reg_MasterSel_MASK);

    /* do abort DDC */
    for (i = 0; i < retry; i++)
    {
        HDMITX_WriteI2C_Byte(handle, HDMI_TX_SYS_DDC_CTRL_REG15, HDMI_TX_SYS_DDC_CTRL_REG15_RDDC_Req_Abort_DDC_CMD);
        HDMITX_WriteI2C_Byte(handle, HDMI_TX_SYS_DDC_CTRL_REG15,
                             HDMI_TX_SYS_DDC_CTRL_REG15_RDDC_Req_GenerateSCL_clock_pulse);

        for (timeout = 0; timeout < 200U; timeout++)
        {
            HDMITX_ReadI2C_Byte(handle, HDMI_TX_SYS_DDC_CTRL_REG16, &uc);
            if ((uc & HDMI_TX_SYS_DDC_CTRL_REG16_RDDC_Status_Done_MASK) != 0U)
            {
                break;
            }

            if ((uc & (HDMI_TX_SYS_DDC_CTRL_REG16_RDDC_Status_NoACK_MASK |
                       HDMI_TX_SYS_DDC_CTRL_REG16_RDDC_Status_WaitBus_MASK |
                       HDMI_TX_SYS_DDC_CTRL_REG16_RDDC_Status_ArbiLose_MASK)) != 0U)
            {
                HDMITX_DEBUG_PRINTF("HDMITX_AbortDdc Fail by reg16=%02X\n", (int)uc);
                break;
            }
            /* delay 1 ms to stable */
            delay1ms(1);
        }
    }
}

/* DDC master will set to be host */
static void HDMITX_ClrDdcFifo(display_handle_t *handle)
{
    HDMITX_ChangeBank(handle, 0);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_SYS_DDC_CTRL_REG10, HDMI_TX_SYS_DDC_CTRL_REG10_Reg_MasterSel_MASK);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_SYS_DDC_CTRL_REG15, HDMI_TX_SYS_DDC_CTRL_REG15_RDDC_Req_DDC_FIFO_clear);
    HDMITX_SetI2C_Byte(handle, HDMI_TX_SYS_DDC_CTRL_REG10, HDMI_TX_SYS_DDC_CTRL_REG10_Reg_MasterSel_MASK, 0x00);
}

static void HDMITX_ClrInt(display_handle_t *handle, uint8_t Reg06, uint8_t Reg07, uint8_t Reg08, uint8_t RegEE)
{
    uint8_t intClear = 0U;

    if ((Reg06 & HDMI_TX_INT_FLAGS_REG06_RInt_AudioOvFlwStus_MASK) != 0U)
    {
        HDMITX_DEBUG_PRINTF("HDMI_TX_INT_FLAGS_REG06_RInt_AudioOvFlwStus_MASK");
        HDMITX_SetI2C_Byte(handle, HDMI_TX_GENERAL_REG04, (B_HDMITX_AUD_RST | B_TX_AREF_RST),
                           (B_HDMITX_AUD_RST | B_TX_AREF_RST));
        HDMITX_SetI2C_Byte(handle, HDMI_TX_GENERAL_REG04, B_HDMITX_AUD_RST | B_TX_AREF_RST, 0x00);
    }
    else if ((Reg06 & HDMI_TX_INT_FLAGS_REG06_RInt_DDCFIFOErr_MASK) != 0U)
    {
        HDMITX_DEBUG_PRINTF("DDC FIFO Error");
        HDMITX_ClrDdcFifo(handle);
    }
    else if ((Reg06 & HDMI_TX_INT_FLAGS_REG06_RInt_DDCBusHang_MASK) != 0U)
    {
        HDMITX_DEBUG_PRINTF("DDC BUS HANG");
        HDMITX_AbortDdc(handle);
    }

    /* clear ext interrupt */
    HDMITX_WriteI2C_Byte(handle, 0xEE, RegEE);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_INT_CLEAR_REG0C, 0xFF);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_INT_CLEAR_REG0D, 0xFF);
    /* write HDMI_TX_SYS_STATUS_REG0E_Reg_IntActDone_MASK '1' to trigger clear interrupt */
    HDMITX_ReadI2C_Byte(handle, HDMI_TX_SYS_STATUS_REG0E, &intClear);
    intClear |= HDMI_TX_SYS_STATUS_REG0E_Reg_AudCTSClr_MASK | HDMI_TX_SYS_STATUS_REG0E_Reg_IntActDone_MASK;
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_SYS_STATUS_REG0E, intClear);
}

void HDMITX_Reg06_Process(display_handle_t *handle, uint8_t Reg06)
{
    if ((Reg06 & HDMI_TX_INT_FLAGS_REG06_RInt_HPDStus_MASK) != 0U)
    {
        if (HDMITX_GetSinkHpd(handle))
        {
            HDMITX_DEBUG_PRINTF("HDMI Cable Plug In");
            HDMITX_VideoReset(handle);
            ParseEDID(handle);
            it6161.hdmi_tx.hdmi_mode = RxCapability.VideoMode;
        }
        else
        {
            HDMITX_DEBUG_PRINTF("HDMI Cable Plug Out");
            HDMITX_DisableVideoOutput(handle);
        }
    }
}

static void HDMITX_FireAfe(display_handle_t *handle)
{
    HDMITX_ChangeBank(handle, 0x00U);
    HDMITX_WriteI2C_Byte(handle, REG_TX_AFE_DRV_CTRL, 0x00);
}

static void HDMITX_EnableVideoOutput(display_handle_t *handle, uint8_t level)
{
    HDMITX_WriteI2C_Byte(handle, REG_TX_SW_RST, B_HDMITX_AUD_RST | B_TX_AREF_RST | B_TX_HDCP_RST_HDMITX);
    HDMITX_ChangeBank(handle, 1);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_AVIINFO_DB1, 0x00);
    HDMITX_ChangeBank(handle, 0);

    if (it6161.hdmi_tx.hdmi_mode != 0U)
    {
        HDMITX_SetAvMute(handle, 1U);
    }

    HDMITX_SetupPclkDiv2(handle);
    HDMITX_SetupCsc(handle);
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_HDMI_CONTROL_REGC0,
                         it6161.hdmi_tx.hdmi_mode != 0U ? HDMI_TX_HDMI_CONTROL_REGC0_REGHDMIMode_HDMI_MODE :
                                                          HDMI_TX_HDMI_CONTROL_REGC0_REGHDMIMode_DVI_MODE);
    HDMITX_SetupAfe(handle, level);
    HDMITX_FireAfe(handle);
}

static void HDMITX_SetOutputProcess(display_handle_t *handle)
{
    uint8_t level      = 0U;
    uint32_t TMDSClock = 0U;

    TMDSClock = it6161.hdmi_tx.pclk * 1000U * (it6161.source_avi_infoframe.pixel_repeat + 1U);

    HDMITX_DEBUG_PRINTF(
        "%s: %d, TMDSClock = 0x%x, it6161.hdmi_tx.pclk = 0x%x, it6161.source_avi_infoframe.pixel_repeat = 0x%x\n",
        __func__, __LINE__, TMDSClock, it6161.hdmi_tx.pclk, it6161.source_avi_infoframe.pixel_repeat);
    HDMITX_DisableAudioOutput(handle);
    HDMITX_DisableAviInfoframe(handle);

    if (TMDSClock > 80000000U)
    {
        level = (uint8_t)PCLK_HIGH;
    }
    else if (TMDSClock > 20000000U)
    {
        level = (uint8_t)PCLK_MEDIUM;
    }
    else
    {
        level = (uint8_t)PCLK_LOW;
    }

    HDMITX_EnableVideoOutput(handle, level);

    /* Power on the TxCLK (for CSC) */
    HDMITX_SetI2C_Byte(handle, 0x0F, 0x10, 0x00);
    if (it6161.hdmi_tx.hdmi_mode != 0U)
    {
        HDMITX_AviInfoframeSet(handle);
        HDMITX_AudioProcess(handle);
    }

    HDMITX_SetAvMute(handle, 0U);
}

void HDMITX_Reg08_Process(display_handle_t *handle, uint8_t Reg08)
{
    if ((Reg08 & HDMI_TX_INT_FLAGS_REG08_RInt_VidStableStus_MASK) != 0U)
    {
        HDMITX_WriteI2C_Byte(handle, HDMI_TX_INT_FLAGS_REG08, Reg08);
        if (HDMITX_GetVideoState(handle))
        {
            HDMITX_GetDisplayMode(handle);

            HDMITX_SetOutputProcess(handle);
            HDMITX_SetAvMute(handle, 0U);
        }
    }
}

void HDMITX_RegEE_Process(display_handle_t *handle, uint8_t RegEE)
{
    if (RegEE != 0x00U)
    {
        HDMITX_DEBUG_PRINTF("%s%s%s%s%s%s%s", (RegEE & 0x40) ? "video parameter change " : "",
                            (RegEE & 0x20) ? "HDCP Pj check done " : "", (RegEE & 0x10) ? "HDCP Ri check done " : "",
                            (RegEE & 0x8) ? "DDC bus hang " : "", (RegEE & 0x4) ? "Video input FIFO auto reset " : "",
                            (RegEE & 0x2) ? "o audio input interrupt  " : "",
                            (RegEE & 0x1) ? "Audio decode error interrupt " : "");
    }
}

void HDMITX_DevLoopProc(display_handle_t *handle)
{
    uint8_t Reg06 = 0U, Reg07 = 0U, Reg08 = 0U, RegEE = 0U;

    HDMITX_ReadI2C_Byte(handle, 0x06, &Reg06);
    HDMITX_ReadI2C_Byte(handle, 0x07, &Reg07);
    HDMITX_ReadI2C_Byte(handle, 0x08, &Reg08);
    HDMITX_ReadI2C_Byte(handle, 0xEE, &RegEE);

    if ((Reg06 != 0U) || (Reg07 != 0U) || (Reg08 != 0U))
    {
        HDMITX_ClrInt(handle, Reg06, Reg07, Reg08, RegEE);
    }
    HDMITX_Reg06_Process(handle, Reg06);
    HDMITX_Reg08_Process(handle, Reg08);
    HDMITX_RegEE_Process(handle, RegEE);
    DumpHDMITXReg(handle);
}
