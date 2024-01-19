/*
 * Copyright (c) 2022 ITE.
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_it6161.h"
#include "mipi_rx.h"
#include "hdmi_tx.h"
#include "fsl_debug_console.h"

static uint32_t RxRCLK = 0U;
uint32_t MCLK          = 0U;
uint32_t RxPCLK        = 0U;
static uint32_t MHFP, MHSW, MHBP, MHDEW, MHVR2nd;
static uint32_t MVFP, MVSW, MVBP, MVDEW, MVFP2nd;
static uint32_t PHFP, PHSW, PHBP, PHDEW, PHVR2nd;
static uint32_t PVFP, PVSW, PVBP, PVDEW, PVFP2nd;
uint32_t MHBlank, MVTotal, PHTotal, PVTotal;

void MIPIRX_DumpRegs(display_handle_t *handle)
{
#if (DEBUG_DUMP_MIPIRX_REGISTER == 0x01U)
    int i         = 0;
    int j         = 0;
    uint8_t value = 0U;

    PRINTF("\r\n---------------------------------------------------------------------------\r\n");
    PRINTF("\r\nMIPIRX Reg\r\n");
    PRINTF("       ");
    for (j = 0; j < 16; j++)
    {
        PRINTF(" %02X", (int)j);
        if ((j == 3) || (j == 7) || (j == 11))
        {
            PRINTF("  ");
        }
    }
    PRINTF("\r\n---------------------------------------------------------------------------\r\n");

    for (i = 0; i < 0x100; i += 16)
    {
        PRINTF("[%3X]  ", i);
        for (j = 0; j < 16; j++)
        {
            MIPIRX_ReadI2C_Byte(handle, ((i + j) & 0xFF), &value);
            PRINTF(" %02X", value);
            if ((j == 3) || (j == 7) || (j == 11))
            {
                PRINTF(" -");
            }
        }
        PRINTF("\r\n");
        if ((i % 0x40) == 0x30)
        {
            PRINTF("-----------------------------------------------------\r\n");
        }
    }
    PRINTF("-------------------------------------------------------------\r\n");
#endif // DEBUG_DUMP_MIPIRX_REGISTER
}

void MIPIRX_CalRclk(display_handle_t *handle)
{
    uint8_t i         = 0U;
    uint32_t t10usint = 0U;
    uint32_t sum      = 0U;
    uint8_t retry     = 5U;

    for (i = 0U; i < retry; i++)
    {
        MIPIRX_SetI2C_Byte(handle, 0x94, 0x80, 0x80); // Enable RCLK 100ms count
        delay1ms(100);
        MIPIRX_SetI2C_Byte(handle, 0x94, 0x80, 0x00); // Disable RCLK 100ms count

        MIPIRX_ReadI2C_Byte(handle, 0x97, &RxRCLK);
        RxRCLK <<= 8;
        MIPIRX_ReadI2C_Byte(handle, 0x96, &RxRCLK);
        RxRCLK <<= 8;
        MIPIRX_ReadI2C_Byte(handle, 0x95, &RxRCLK);
        sum += RxRCLK;
    }
    sum /= retry;

    RxRCLK   = sum / 108U;
    t10usint = RxRCLK;
    MIPIRX_DEBUG_PRINTF("RxRCLK = %d,%03d,%03d\r\n", (sum * 10) / 1000000, ((sum * 10) % 1000000) / 1000,
                        ((sum * 10) % 100));
    MIPIRX_DEBUG_PRINTF("T10usInt=0x%03X\r\n", (int)t10usint);
    MIPIRX_WriteI2C_Byte(handle, 0x91, t10usint & 0xFFU);
}

#define MAX_SUPPORT_LANES_CNT (0x03U) /* Support 1, 2, 4 lanes number, so maximum supported lanes count is 3  */
static uint8_t MIPIRX_REG80_SETUP_LANES[][MAX_SUPPORT_LANES_CNT] = {
    {
        0x02U, /* MIPIRX PCLKSel = 1; 4-lane, MCLK = 1/1 PCLK */
        0x05U, /* MPPCLKSel = 6; 2-lane : MCLK = 1/1 PCLK */
        0x08U, /* MPPCLKSel = 8; 1-lane : MCLK = 3/4 PCLK */
    },         /* for data type RGB_18b */
    {
        0x02U, /* MPPCLKSel = 1; 4-lane : MCLK = 3/4 PCLK */
        0x05U, /* MPPCLKSel = 3; 2-lane : MCLK = 3/4 PCLK */
        0x0BU, /* MPPCLKSel = 5; 1-lane : MCLK = 3/4 PCLK */
    },         /* for other data type */
};

void MIPIRX_AfeCfg(display_handle_t *handle)
{
    /* reference: MIPI Alliance Specification for DSI Ch8.7 Table 16 Data Types for Processor-sourced Packets */
    uint8_t dataType       = 0U;
    uint8_t MIPIRX_LaneNum = 0U;
    uint8_t dataTypeIdx    = 0U;

    MIPIRX_ReadI2C_Byte(handle, 0x28, &dataType);
    MIPIRX_LaneNum = it6161.mipi_rx.lanes - 1U;
    dataTypeIdx    = (int8_t)dataType == RGB_18b ? (0x00U) : (0x01U);

    MIPIRX_DEBUG_PRINTF("mipi receive video format: 0x%02x\r\n", dataType);
    MIPIRX_SetI2C_Byte(handle, 0x80, 0x1F, MIPIRX_REG80_SETUP_LANES[dataTypeIdx][MIPIRX_LaneNum]);
}

void MIPIRX_CalMclk(display_handle_t *handle)
{
    uint8_t i;
    uint32_t rddata = 0U;
    uint32_t sum    = 0U;
    uint8_t retry   = 3U;
    uint8_t value   = 0U;

    for (i = 0U; i < retry; i++)
    {
        MIPIRX_SetI2C_Byte(handle, 0x9B, 0x80, 0x80);
        delay1ms(5);
        MIPIRX_SetI2C_Byte(handle, 0x9B, 0x80, 0x00);

        MIPIRX_ReadI2C_Byte(handle, 0x9A, &value);
        rddata = value;
        MIPIRX_ReadI2C_Byte(handle, 0x9B, &value);
        rddata = (((uint32_t)value & 0x0FU) << 8) + rddata;

        sum += rddata;
    }

    sum /= retry;

    MCLK = RxRCLK * 2048U / sum;
    MIPIRX_DEBUG_PRINTF("MCLK = %d,%03d MHz\r\n", (MCLK) / 1000, MCLK % 1000);
}

void MIPIRX_CalPclk(display_handle_t *handle)
{
    uint8_t i;
    uint32_t rddata = 0U;
    uint32_t sum    = 0U;
    uint8_t retry   = 3U;
    uint8_t value   = 0U;

    MIPIRX_SetI2C_Byte(handle, 0x99, 0x80, 0x00);
    for (i = 0U; i < retry; i++)
    {
        MIPIRX_SetI2C_Byte(handle, 0x99, 0x80, 0x80);
        delay1ms(5);
        MIPIRX_SetI2C_Byte(handle, 0x99, 0x80, 0x00);

        MIPIRX_ReadI2C_Byte(handle, 0x98, &value);
        rddata = value;
        MIPIRX_ReadI2C_Byte(handle, 0x99, &value);
        rddata = (((uint32_t)value & 0x0FU) << 8) + rddata;

        sum += rddata;
    }

    sum /= retry;

    RxPCLK = (RxRCLK * 2048U) / sum;
    MIPIRX_DEBUG_PRINTF("RxPCLK = %d,%03d MHz\r\n", (RxPCLK) / 1000U, (RxPCLK % 1000U));
}

void MIPIRX_ShowMRec(display_handle_t *handle)
{
    uint8_t value = 0U;

    MIPIRX_ReadI2C_Byte(handle, 0x52, &value);
    MHSW = value;
    MIPIRX_ReadI2C_Byte(handle, 0x53, &value);
    MHSW += ((uint32_t)value & 0x3FU) << 8;

    MIPIRX_ReadI2C_Byte(handle, 0x50, &value);
    MHFP = value;
    MIPIRX_ReadI2C_Byte(handle, 0x51, &value);
    MHFP += ((uint32_t)value & 0x3FU) << 8;

    MIPIRX_ReadI2C_Byte(handle, 0x54, &value);
    MHBP = value;
    MIPIRX_ReadI2C_Byte(handle, 0x55, &value);
    MHBP += ((uint32_t)value & 0x3FU) << 8;

    MIPIRX_ReadI2C_Byte(handle, 0x56, &value);
    MHDEW = value;
    MIPIRX_ReadI2C_Byte(handle, 0x57, &value);
    MHDEW += ((uint32_t)value & 0x3FU) << 8;

    MIPIRX_ReadI2C_Byte(handle, 0x58, &value);
    MHVR2nd = value;
    MIPIRX_ReadI2C_Byte(handle, 0x59, &value);
    MHVR2nd += ((uint32_t)value & 0x3FU) << 8;

    MHBlank = MHFP + MHSW + MHBP;

    MIPIRX_ReadI2C_Byte(handle, 0x5C, &value);
    MVSW = value;
    MIPIRX_ReadI2C_Byte(handle, 0x5D, &value);
    MVSW += ((uint32_t)value & 0x3FU) << 8;

    MIPIRX_ReadI2C_Byte(handle, 0x5A, &value);
    MVFP = value;
    MIPIRX_ReadI2C_Byte(handle, 0x5B, &value);
    MVFP += ((uint32_t)value & 0x3FU) << 8;

    MIPIRX_ReadI2C_Byte(handle, 0x5E, &value);
    MVBP = value;
    MIPIRX_ReadI2C_Byte(handle, 0x5F, &value);
    MVBP += ((uint32_t)value & 0x3FU) << 8;

    MIPIRX_ReadI2C_Byte(handle, 0x60, &value);
    MVDEW = value;
    MIPIRX_ReadI2C_Byte(handle, 0x61, &value);
    MVDEW += ((uint32_t)value & 0x3FU) << 8;

    MIPIRX_ReadI2C_Byte(handle, 0x62, &value);
    MVFP2nd = value;
    MIPIRX_ReadI2C_Byte(handle, 0x63, &value);
    MVFP2nd += ((uint32_t)value & 0x3FU) << 8;

    MVTotal = MVFP + MVSW + MVBP + MVDEW;

    MIPIRX_DEBUG_PRINTF("MHFP    = %d\r\n", MHFP);
    MIPIRX_DEBUG_PRINTF("MHSW    = %d\r\n", MHSW);
    MIPIRX_DEBUG_PRINTF("MHBP    = %d\r\n", MHBP);
    MIPIRX_DEBUG_PRINTF("MHDEW   = %d\r\n", MHDEW);
    MIPIRX_DEBUG_PRINTF("MHVR2nd = %d\r\n", MHVR2nd);
    MIPIRX_DEBUG_PRINTF("MHBlank  = %d\r\n", MHBlank);

    MIPIRX_DEBUG_PRINTF("MVFP    = %d\r\n", MVFP);
    MIPIRX_DEBUG_PRINTF("MVSW    = %d\r\n", MVSW);
    MIPIRX_DEBUG_PRINTF("MVBP   = %d\r\n", MVBP);
    MIPIRX_DEBUG_PRINTF("MVDEW   = %d\r\n", MVDEW);
    MIPIRX_DEBUG_PRINTF("MVFP2nd   = %d\r\n", MVFP2nd);
    MIPIRX_DEBUG_PRINTF("MVTotal = %d\r\n", MVTotal);

    MIPIRX_DEBUG_PRINTF("\r\n");
}

void MIPIRX_ResetPDomain(display_handle_t *handle)
{
    /* P Clock Domain Reset */
    MIPIRX_SetI2C_Byte(handle, MIPI_RX_SOFT_RESET_REG05, MIPI_RX_SOFT_RESET_REG05_RegMPSoftPRst_MASK,
                       MIPI_RX_SOFT_RESET_REG05_RegMPSoftPRst(0x01U));
    /* Release Video Clock Domain Reset */
    MIPIRX_SetI2C_Byte(handle, MIPI_RX_SOFT_RESET_REG05, MIPI_RX_SOFT_RESET_REG05_RegMPSoftPRst_MASK,
                       MIPI_RX_SOFT_RESET_REG05_RegMPSoftPRst(0x00U));
}

void HDMITX_GenerateBlankTiming(display_handle_t *handle)
{
    uint32_t hsync_start, hsync_end, vsync_start, vsync_end, htotal, hde_start, vtotal;
    uint32_t vsync_start_2nd = 0x00U, vsync_end_2nd = 0x00U, vsync_rising_at_h_2nd;

    hsync_start = (uint32_t)it6161.hdmi_tx.mode.hsync_start - (uint32_t)it6161.hdmi_tx.mode.hdisplay - 0x01U;
    hsync_end   = hsync_start + ((uint32_t)it6161.hdmi_tx.mode.hsync_end - (uint32_t)it6161.hdmi_tx.mode.hsync_start);
    vsync_rising_at_h_2nd = hsync_start + ((uint32_t)it6161.hdmi_tx.mode.htotal / 0x02U);
    hde_start             = (uint32_t)it6161.hdmi_tx.mode.htotal - (uint32_t)it6161.hdmi_tx.mode.hsync_start;
    htotal                = (uint32_t)it6161.hdmi_tx.mode.htotal - 0x01U;

    vsync_start = (uint32_t)it6161.hdmi_tx.mode.vsync_start - (uint32_t)it6161.hdmi_tx.mode.vdisplay;
    vsync_end   = (uint32_t)it6161.hdmi_tx.mode.vsync_end - (uint32_t)it6161.hdmi_tx.mode.vdisplay;
    /* Force tx clk/vid stable */
    HDMITX_SetI2C_Byte(
        handle, HDMI_TX_HDMI_CONTROL_REGD1,
        HDMI_TX_HDMI_CONTROL_REGD1_RegStableDbgMd_TxCLKStable_MASK |
            HDMI_TX_HDMI_CONTROL_REGD1_RegStableDbgMd_TxVidStable_MASK,
        HDMI_TX_HDMI_CONTROL_REGD1_RegStableDbgMd_TxCLKStable((uint32_t)it6161.hdmi_tx.tx_clk_stable) |
            HDMI_TX_HDMI_CONTROL_REGD1_RegStableDbgMd_TxVidStable((uint32_t)it6161.hdmi_tx.tx_vid_stable));

    HDMITX_SetI2C_Byte(handle, HDMI_TX_PATTERN_GENERATOR_REGA9, HDMI_TX_PATTERN_GENERATOR_REGA9_RegHBPM_MASK,
                       HDMI_TX_PATTERN_GENERATOR_REGA9_RegHBPM((uint32_t)it6161.hdmi_tx.hdmitx_bypass_mode));
    HDMITX_SetI2C_Byte(
        handle, HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG90, HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG90_Reg_GenDE_MASK,
        HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG90_Reg_GenDE((uint32_t)it6161.hdmi_tx.de_generation_enable));

    /* Setup pattern generation horizontal total */
    HDMITX_SetI2C_Byte(
        handle, HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG91, HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG91_Reg_PGHTotal_MASK,
        HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG91_Reg_PGHTotal((vsync_rising_at_h_2nd & 0x0FF0U) >> 0x04U));
    HDMITX_SetI2C_Byte(handle, HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG90,
                       HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG90_Reg_PGHTotal_MASK,
                       HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG90_Reg_PGHTotal(vsync_rising_at_h_2nd & 0x000FU));
    /* Setup polarity */
    HDMITX_SetI2C_Byte(
        handle, HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG90,
        HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG90_RegVSPol_MASK | HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG90_RegHSPol_MASK,
        HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG90_RegVSPol((uint32_t)it6161.hdmi_tx.vertical_sync_polarity) |
            HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG90_RegHSPol((uint32_t)it6161.hdmi_tx.horizontal_sync_polarity));

    HDMITX_SetI2C_Byte(handle, HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG95,
                       HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG95_Reg_PGHRS_MASK,
                       HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG95_Reg_PGHRS(hsync_start & 0xFFU));
    HDMITX_SetI2C_Byte(handle, HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG96,
                       HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG96_Reg_PGHRE_MASK,
                       HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG96_Reg_PGHRE(hsync_end & 0xFFU));
    HDMITX_SetI2C_Byte(handle, HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG97,
                       HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG97_Reg_PGHRE_MASK |
                           HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG97_Reg_PGHRS_MASK,
                       HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG97_Reg_PGHRE((hsync_end & 0x0F00U) >> 0x08U) |
                           HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG97_Reg_PGHRS((hsync_start & 0x0F00U) >> 0x08U));

    if (it6161.mipi_rx.interlaced_mode == 0x0U)
    {
        vsync_start_2nd = 0x0FFFU;
        vsync_end_2nd   = 0x3FU;
        vtotal          = (uint32_t)it6161.hdmi_tx.mode.vtotal - 0x01U;
    }
    else
    {
        vtotal = (uint32_t)it6161.hdmi_tx.mode.vtotal * 2U;
    }

    HDMITX_SetI2C_Byte(
        handle, HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA5,
        HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA5_Reg_PGInterlaced_MASK,
        HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA5_Reg_PGInterlaced((uint32_t)it6161.mipi_rx.interlaced_mode));
    HDMITX_SetI2C_Byte(handle, HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA0,
                       HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA0_Reg_PGVRS_MASK,
                       HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA0_Reg_PGVRS((uint32_t)vsync_start));
    HDMITX_SetI2C_Byte(handle, HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA1,
                       HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA1_Reg_PGVRE_MASK |
                           HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA1_Reg_PGVRS_MASK,
                       HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA1_Reg_PGVRS((vsync_start & 0xF00U) >> 0x08U) |
                           HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA1_Reg_PGVRE(vsync_end & 0x0FU));
    HDMITX_SetI2C_Byte(handle, HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA2,
                       HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA2_Reg_PGVRS2nd_MASK,
                       HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA2_Reg_PGVRS2nd((uint32_t)vsync_start_2nd));
    HDMITX_SetI2C_Byte(handle, HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA6,
                       HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA2_Reg_PGVRS2nd_MASK |
                           HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA6_Reg_PGVRE2nd_MASK,
                       HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA6_Reg_PGVRE2nd((vsync_end_2nd & 0x00F0U) >> 0x04U) |
                           HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA6_Reg_PGVRE((vsync_end & 0x00F0U) >> 0x04U));
    HDMITX_SetI2C_Byte(handle, HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA3,
                       HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA3_Reg_PGVRE2nd_MASK |
                           HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA3_Reg_PGVRS2nd_MASK,
                       HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA3_Reg_PGVRE2nd(vsync_end_2nd & 0x000FU) |
                           HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA3_Reg_PGVRS2nd(vsync_start_2nd & 0xFF00U >> 0x08U));
    HDMITX_SetI2C_Byte(handle, HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA4,
                       HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA4_Reg_PGEn2ndVRRise_MASK,
                       HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA4_Reg_PGEn2ndVRRise((uint32_t)vsync_rising_at_h_2nd));

    HDMITX_SetI2C_Byte(handle, HDMI_TX_PATTERN_GENERATOR_REGB1,
                       HDMI_TX_PATTERN_GENERATOR_REGB1_Reg_PGHRE_MASK | HDMI_TX_PATTERN_GENERATOR_REGB1_Reg_PGHRS_MASK |
                           HDMI_TX_PATTERN_GENERATOR_REGB1_Reg_PGHDES_MASK,
                       HDMI_TX_PATTERN_GENERATOR_REGB1_Reg_PGHRE((hsync_end & 0x1000U) >> 12) |
                           HDMI_TX_PATTERN_GENERATOR_REGB1_Reg_PGHRS((hsync_start & 0x1000U) >> 12) |
                           HDMI_TX_PATTERN_GENERATOR_REGB1_Reg_PGHDES((hde_start & 0x1000U) >> 12));
    HDMITX_SetI2C_Byte(
        handle, HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA5,
        HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA5_Reg_DEOnlyIn_MASK |
            HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA5_Reg_PGEn2ndVRRise_MASK,
        HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA5_Reg_DEOnlyIn((uint32_t)it6161.hdmi_tx.de_only_in) |
            HDMI_TX_PATTERN_SYNC_DE_GENERATION_REGA5_Reg_PGEn2ndVRRise((vsync_rising_at_h_2nd & 0x0F00U) >> 8));

    HDMITX_SetI2C_Byte(
        handle, HDMI_TX_PATTERN_GENERATOR_REGB2,
        HDMI_TX_PATTERN_GENERATOR_REGB2_Reg_PGEn2ndVRRise_MASK | HDMI_TX_PATTERN_GENERATOR_REGB2_Reg_PGHTotal_MASK,
        HDMI_TX_PATTERN_GENERATOR_REGB2_Reg_PGEn2ndVRRise((vsync_rising_at_h_2nd & 0x1000U) >> 12) |
            HDMI_TX_PATTERN_GENERATOR_REGB2_Reg_PGHTotal((vsync_rising_at_h_2nd & 0x1000U) >> 12));

    HDMITX_SetI2C_Byte(handle, HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG90,
                       HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG90_Reg_PGHTotal_MASK,
                       HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG90_Reg_PGHTotal(htotal & 0x000FU));
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG91,
                         HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG91_Reg_PGHTotal((htotal & 0x0FF0U) >> 0x04U));
    HDMITX_SetI2C_Byte(handle, HDMI_TX_PATTERN_GENERATOR_REGB2, HDMI_TX_PATTERN_GENERATOR_REGB2_Reg_PGHTotal_MASK,
                       HDMI_TX_PATTERN_GENERATOR_REGB2_Reg_PGHTotal((htotal & 0x1000U) >> 12));
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG98,
                         HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG98_Reg_PGVTotal(vtotal & 0x0FFU));
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG99,
                         HDMI_TX_PATTERN_SYNC_DE_GENERATION_REG99_Reg_PGVTotal((vtotal & 0xF00U) >> 0x08U));
}

void MIPIRX_ShowPrec(display_handle_t *handle)
{
    uint8_t value = 0U;

    MIPIRX_ReadI2C_Byte(handle, 0x30, &value);
    PHFP = value;
    MIPIRX_ReadI2C_Byte(handle, 0x31, &value);
    PHFP += ((uint32_t)value & 0x3FU) << 8;

    MIPIRX_ReadI2C_Byte(handle, 0x32, &value);
    PHSW = value;
    MIPIRX_ReadI2C_Byte(handle, 0x33, &value);
    PHSW += ((uint32_t)value & 0x3FU) << 8;

    MIPIRX_ReadI2C_Byte(handle, 0x34, &value);
    PHBP = value;
    MIPIRX_ReadI2C_Byte(handle, 0x35, &value);
    PHBP += ((uint32_t)value & 0x3FU) << 8;

    MIPIRX_ReadI2C_Byte(handle, 0x36, &value);
    PHDEW = value;
    MIPIRX_ReadI2C_Byte(handle, 0x37, &value);
    PHDEW += ((uint32_t)value & 0x3FU) << 8;

    MIPIRX_ReadI2C_Byte(handle, 0x38, &value);
    PHVR2nd = value;
    MIPIRX_ReadI2C_Byte(handle, 0x39, &value);
    PHVR2nd += ((uint32_t)value & 0x3FU) << 8;

    PHTotal = PHFP + PHSW + PHBP + PHDEW;

    MIPIRX_ReadI2C_Byte(handle, 0x3A, &value);
    PVFP = value;
    MIPIRX_ReadI2C_Byte(handle, 0x3B, &value);
    PVFP += ((uint32_t)value & 0x3FU) << 8;

    MIPIRX_ReadI2C_Byte(handle, 0x3C, &value);
    PVSW = value;
    MIPIRX_ReadI2C_Byte(handle, 0x3D, &value);
    PVSW += ((uint32_t)value & 0x3FU) << 8;

    MIPIRX_ReadI2C_Byte(handle, 0x3E, &value);
    PVBP = value;
    MIPIRX_ReadI2C_Byte(handle, 0x3F, &value);
    PVBP += ((uint32_t)value & 0x3FU) << 8;

    MIPIRX_ReadI2C_Byte(handle, 0x40, &value);
    PVDEW = value;
    MIPIRX_ReadI2C_Byte(handle, 0x41, &value);
    PVDEW += ((uint32_t)value & 0x3FU) << 8;

    MIPIRX_ReadI2C_Byte(handle, 0x42, &value);
    PVFP2nd = value;
    MIPIRX_ReadI2C_Byte(handle, 0x43, &value);
    PVFP2nd += ((uint32_t)value & 0x3FU) << 8;

    PVTotal = PVFP + PVSW + PVBP + PVDEW;

    MIPIRX_DEBUG_PRINTF("PHFP    = %d\r\n", PHFP);
    MIPIRX_DEBUG_PRINTF("PHSW    = %d\r\n", PHSW);
    MIPIRX_DEBUG_PRINTF("PHBP   = %d\r\n", PHBP);
    MIPIRX_DEBUG_PRINTF("PHDEW   = %d\r\n", PHDEW);
    MIPIRX_DEBUG_PRINTF("PHVR2nd   = %d\r\n", PHVR2nd);
    MIPIRX_DEBUG_PRINTF("PHTotal = %d\r\n", PHTotal);

    MIPIRX_DEBUG_PRINTF("PVFP    = %d\r\n", PVFP);
    MIPIRX_DEBUG_PRINTF("PVSW    = %d\r\n", PVSW);
    MIPIRX_DEBUG_PRINTF("PVBP   = %d\r\n", PVBP);
    MIPIRX_DEBUG_PRINTF("PVDEW   = %d\r\n", PVDEW);
    MIPIRX_DEBUG_PRINTF("PVFP2nd   = %d\r\n", PVFP2nd);
    MIPIRX_DEBUG_PRINTF("PVTotal = %d\r\n", PVTotal);
    MIPIRX_DEBUG_PRINTF("\r\n");
}

void MIPIRX_Reg06_Process(display_handle_t *handle, uint8_t Reg06)
{
    uint8_t value = 0U;

    // Interrupt Reg06
    MIPIRX_ReadI2C_Byte(handle, 0x0D, &value);
    if ((Reg06 & 0x01U) != 0x0U)
    {
        MIPIRX_WriteI2C_Byte(handle, 0x06, 0x01);
        MIPIRX_DEBUG_PRINTF("PPS MVidStb Change Interrupt ...reg0D %x\r\n", value);

        if ((value & 0x10U) != 0x0U)
        {
            MIPIRX_DEBUG_PRINTF("MVidStb Change to HIGH,\r\n");
            MIPIRX_CalRclk(handle);
            MIPIRX_CalMclk(handle);
            MIPIRX_ShowMRec(handle);
            MIPIRX_AfeCfg(handle);
            MIPIRX_ResetPDomain(handle);
        }
        else
        {
            MIPIRX_DEBUG_PRINTF("MVidStb Change to LOW ...\r\n");
        }
    }

    if ((Reg06 & 0x02U) != 0x0U)
    {
        MIPIRX_WriteI2C_Byte(handle, 0x06, 0x02);
    }
#if (!EnMBPM)
    if ((Reg06 & 0x04U) != 0x0U)
    {
        MIPIRX_WriteI2C_Byte(handle, 0x06, 0x04);
        MIPIRX_DEBUG_PRINTF("PPS MHDE Error Interrupt !!!\r\n");
    }
#endif // #if (EnMBPM == false)

    if ((Reg06 & 0x08U) != 0x0U)
    {
        MIPIRX_WriteI2C_Byte(handle, 0x06, 0x08);
        MIPIRX_DEBUG_PRINTF("PPS MVSync Error Interrupt !!!\r\n");
    }

    if ((Reg06 & 0x10U) != 0x0U)
    {
        MIPIRX_WriteI2C_Byte(handle, 0x06, 0x10);
        MIPIRX_DEBUG_PRINTF("PPS PVidStb Change Interrupt ...\r\n");
        if ((value & 0x30U) != 0x0U)
        {
            MIPIRX_DEBUG_PRINTF("PVidStb Change to HIGH, ");
            MIPIRX_CalRclk(handle);
            MIPIRX_CalPclk(handle);
            MIPIRX_ShowPrec(handle);
            MIPIRX_WriteI2C_Byte(handle, MIPI_RX_CRC_REGC0,
                                 MIPI_RX_CRC_REGC0_RegEnTTLTxCRC((uint32_t)it6161.mipi_rx.enable_ttl_tx_crc) +
                                     MIPI_RX_CRC_REGC0_RegTTLTxCRCNum((uint16_t)it6161.mipi_rx.crc_frame_number));
            // Setup 1 sec timer interrupt
            MIPIRX_SetI2C_Byte(handle, 0x0b, 0x40, 0x40);
            if (it6161.hdmi_tx.hdmitx_bypass_mode != 0x0U)
            {
                HDMITX_SetI2C_Byte(
                    handle, HDMI_TX_PATTERN_GENERATOR_REGA9, HDMI_TX_PATTERN_GENERATOR_REGA9_RegHBPM_MASK,
                    HDMI_TX_PATTERN_GENERATOR_REGA9_RegHBPM((uint32_t)it6161.hdmi_tx.hdmitx_bypass_mode));
            }
            else
            {
                HDMITX_GenerateBlankTiming(handle);
            }
            HDMITX_VideoReset(handle);
        }
        else
        {
            MIPIRX_DEBUG_PRINTF("PVidStb Change to LOW ...\r\n");
        }
    }

    if ((Reg06 & 0x20U) != 0x0U)
    {
        MIPIRX_WriteI2C_Byte(handle, 0x06, 0x20);
#if (!DisPHSyncErr)
        MIPIRX_DEBUG_PRINTF("PPS PHSync Error Interrupt !!!\r\n");
#endif // #if (DisPHSyncErr == false)
    }

#if (!EnMBPM)
    if ((Reg06 & 0x40U) != 0x0U)
    {
        MIPIRX_WriteI2C_Byte(handle, 0x06, 0x40);
        MIPIRX_DEBUG_PRINTF("PPS PHDE Error Interrupt !!!\r\n");
    }

    if ((Reg06 & 0x80U) != 0x0U)
    {
        MIPIRX_WriteI2C_Byte(handle, 0x06, 0x80);
        MIPIRX_DEBUG_PRINTF("PPS MVDE Error Interrupt !!!\r\n");
    }
#endif // #if (EnMBPM == false)
}

void MIPIRX_Reg07_Process(display_handle_t *handle, uint8_t Reg07)
{
    // Interrupt Reg07
    if ((Reg07 & 0x01U) != 0x0U)
    {
        MIPIRX_WriteI2C_Byte(handle, 0x07, 0x01);
        MIPIRX_DEBUG_PRINTF("PatGen PPGVidStb change Interrupt !!!\r\n");
    }
    if ((Reg07 & 0x02U) != 0x0U)
    {
        MIPIRX_WriteI2C_Byte(handle, 0x07, 0x02);
        MIPIRX_DEBUG_PRINTF("PPS Data Byte Error Interrupt !!!\r\n");
    }

    if ((Reg07 & 0x04U) != 0x0U)
    {
        MIPIRX_WriteI2C_Byte(handle, 0x07, 0x04);
        MIPIRX_DEBUG_PRINTF("PPS CMOff Interrupt !!!\r\n");
    }

    if ((Reg07 & 0x08U) != 0x0U)
    {
        MIPIRX_WriteI2C_Byte(handle, 0x07, 0x08);
        MIPIRX_DEBUG_PRINTF("PPS CMOn Interrupt !!!\r\n");
    }

    if ((Reg07 & 0x10U) != 0x0U)
    {
        MIPIRX_WriteI2C_Byte(handle, 0x07, 0x10);
        MIPIRX_DEBUG_PRINTF("PPS ShutDone cmd Interrupt !!!\r\n");
    }

    if ((Reg07 & 0x20U) != 0x0U)
    {
        MIPIRX_WriteI2C_Byte(handle, 0x07, 0x20);
        MIPIRX_DEBUG_PRINTF("PPS TurnOn Interrupt !!!\r\n");
    }

    if ((Reg07 & 0x40U) != 0x0U || (Reg07 & 0x80U) != 0x0U)
    {
        if ((Reg07 & 0x40U) != 0x0U)
        {
            MIPIRX_DEBUG_PRINTF("PPS FIFO over read Interrupt !!!\r\n");
            MIPIRX_SetI2C_Byte(handle, 0x0a, 0x40, 0x40);
        }
        if ((Reg07 & 0x80U) != 0x0U)
        {
            MIPIRX_DEBUG_PRINTF("PPS FIFO over write Interrupt !!!\r\n");
            MIPIRX_SetI2C_Byte(handle, 0x0a, 0x80, 0x80);
        }
        MIPIRX_DEBUG_PRINTF("----------------------------------------------------\r\n");
    }
}

void MIPIRX_Reg08_Process(display_handle_t *handle, uint8_t Reg08)
{
    uint8_t value = 0U;

    // Interrupt Reg08
    if ((Reg08 & 0x01U) != 0x0U)
    {
        MIPIRX_WriteI2C_Byte(handle, 0x08, 0x01);
#if (!DisECCErr)
        MIPIRX_DEBUG_PRINTF("ECC 1-bit Error Interrupt !!!\r\n");
#endif // #if (DisECCErr == false)
    }

    if ((Reg08 & 0x02U) != 0x0U)
    {
        MIPIRX_WriteI2C_Byte(handle, 0x08, 0x02);
#if (!DisECCErr)
        MIPIRX_DEBUG_PRINTF("ECC 2-bit Error Interrupt !!!\r\n");
#endif // #if (DisECCErr == false)
    }

    if ((Reg08 & 0x04U) != 0x0U)
    {
        MIPIRX_WriteI2C_Byte(handle, 0x08, 0x04);
        MIPIRX_DEBUG_PRINTF("LM FIFO Error Interrupt !!!\r\n");
    }

    if ((Reg08 & 0x08U) != 0x0U)
    {
        MIPIRX_WriteI2C_Byte(handle, 0x08, 0x08);
        MIPIRX_DEBUG_PRINTF("CRC Error Interrupt !!!\r\n");
    }

    if ((Reg08 & 0x10U) != 0x0U)
    {
        MIPIRX_WriteI2C_Byte(handle, 0x08, 0x10);
        MIPIRX_DEBUG_PRINTF("MCLK Off Interrupt !!!\r\n");
    }

    if ((Reg08 & 0x20U) != 0x0U)
    {
        MIPIRX_WriteI2C_Byte(handle, 0x08, 0x20);
        MIPIRX_DEBUG_PRINTF("PPI FIFO OverWrite Interrupt !!!\r\n");
    }

    if ((Reg08 & 0x40U) != 0x0U)
    {
        MIPIRX_WriteI2C_Byte(handle, 0x08, 0x40);

        MIPIRX_DEBUG_PRINTF("FW Timer Interrupt !!!\r\n");
        MIPIRX_SetI2C_Byte(handle, 0x0b, 0x40, 0x00);
        MIPIRX_ReadI2C_Byte(handle, 0xC1, &value);
        if ((value & 0x03U) == 0x03U)
        {
            MIPIRX_DEBUG_PRINTF("CRC Fail !!!\r\n");
        }
        if ((value & 0x05U) == 0x05U)
        {
            MIPIRX_DEBUG_PRINTF("CRC Pass !!!\r\n");
            MIPIRX_DEBUG_PRINTF("CRCR = 0x%02X !!!\r\n", MIPIRX_ReadI2C_Byte(handle, 0xC2, &value));
            MIPIRX_DEBUG_PRINTF("CRCG = 0x%02X !!!\r\n", MIPIRX_ReadI2C_Byte(handle, 0xC3, &value));
            MIPIRX_DEBUG_PRINTF("CRCR = 0x%02X !!!\r\n", MIPIRX_ReadI2C_Byte(handle, 0xC4, &value));
        }
    }
}

void MIPIRX_DevLoopProc(display_handle_t *handle) // mipirx_irq
{
    uint8_t Reg06 = 0U, Reg07 = 0U, Reg08 = 0U;

    MIPIRX_ReadI2C_Byte(handle, 0x06, &Reg06);
    MIPIRX_ReadI2C_Byte(handle, 0x07, &Reg07);
    MIPIRX_ReadI2C_Byte(handle, 0x08, &Reg08);
    if (Reg06 == 0x00U && Reg07 == 0x00U && Reg08 == 0x00U)
    {
        return;
    }

    MIPIRX_Reg08_Process(handle, Reg08);
    MIPIRX_Reg06_Process(handle, Reg06);
    MIPIRX_Reg07_Process(handle, Reg07);
    MIPIRX_DumpRegs(handle);
}
