/*
 * Copyright (c) 2022 ITE.
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_it6161.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
it6161_cfg_t it6161                   = {0};
const display_operations_t it6161_ops = {
    .init   = IT6161_Init,
    .deinit = IT6161_Deinit,
    .start  = IT6161_Start,
    .stop   = IT6161_Stop,
};

/*******************************************************************************
 * Code
 ******************************************************************************/

static status_t IT6161_Identify(display_handle_t *handle)
{
    status_t status;
    uint8_t reg[2]  = {0U};
    uint8_t i2cAddr = (((const it6161_resource_t *)(handle->resource))->i2cAddr);

    status = IT6161_I2C_ReadRegs(handle, i2cAddr, IT6161_VENDER_ID_REG, &reg, sizeof(reg));
    if ((kStatus_Success != status) || (IT6161_VENDER_ID_VALUE_L != reg[0]) || (IT6161_VENDER_ID_VALUE_H != reg[1]))
    {
        return status;
    }

    status = IT6161_I2C_ReadRegs(handle, i2cAddr, IT6161_DEVICE_ID_REG, &reg, sizeof(reg));
    if ((kStatus_Success != status) || (IT6161_DEVICE_ID_VALUE_L != reg[0]) || (IT6161_DEVICE_ID_VALUE_H != reg[1]))
    {
        return status;
    }

    return status;
}

static void it6161_MIPIRX_LogicReset(display_handle_t *handle)
{
    /* software REFCLK clock domain reset */
    MIPIRX_SetI2C_Byte(handle, MIPI_RX_SOFT_RESET_REG05, MIPI_RX_SOFT_RESET_REG05_RefSoftREFRst_MASK,
                       MIPI_RX_SOFT_RESET_REG05_RefSoftREFRst(0x01U));
}

static void it6161_MIPIRX_LogicResetRelease(display_handle_t *handle)
{
    /* software REFCLK clock domain reset */
    MIPIRX_SetI2C_Byte(handle, MIPI_RX_SOFT_RESET_REG05, MIPI_RX_SOFT_RESET_REG05_RefSoftREFRst_MASK,
                       MIPI_RX_SOFT_RESET_REG05_RefSoftREFRst(0x00U));
}

static void it6161_MIPIRX_IntMaskDisable(display_handle_t *handle)
{
    MIPIRX_SetI2C_Byte(handle, MIPI_RX_SYS_STATUS_REG0F, 0x03U,
                       0x00U); /* Don't know what's meaning about this from it6161 programming guide */

    MIPIRX_WriteI2C_Byte(handle, MIPI_RX_INT_MASK_REG09, 0x00U);
    MIPIRX_WriteI2C_Byte(handle, MIPI_RX_INT_MASK_REG0A, 0x00U);

    MIPIRX_WriteI2C_Byte(handle, MIPI_RX_INT_MASK_REG0B, 0x00U);
}

static void it6161_MIPIRX_CONF(display_handle_t *handle)
{
    /* power down OCLK, MCLK, PCLK, RCLK */
    MIPIRX_SetI2C_Byte(handle, MIPI_RX_CLKBUF_CTRL_REG10,
                       MIPI_RX_CLKBUF_CTRL_REG10_RegGateOCLK_MASK | MIPI_RX_CLKBUF_CTRL_REG10_RegGateMCLK_MASK |
                           MIPI_RX_CLKBUF_CTRL_REG10_RegGatePCLK_MASK | MIPI_RX_CLKBUF_CTRL_REG10_RegGateRCLK_MASK,
                       MIPI_RX_CLKBUF_CTRL_REG10_RegGateOCLK(0x00U) | MIPI_RX_CLKBUF_CTRL_REG10_RegGateMCLK(0x00U) |
                           MIPI_RX_CLKBUF_CTRL_REG10_RegGatePCLK(0x00U) | MIPI_RX_CLKBUF_CTRL_REG10_RegGateRCLK(0x00U));

    it6161_MIPIRX_LogicReset(handle);
    it6161_MIPIRX_LogicResetRelease(handle);

    it6161_MIPIRX_IntMaskDisable(handle);
    /* Setup INT pin: active low */
    MIPIRX_SetI2C_Byte(handle, MIPI_RX_SYS_CONF_REG0D, MIPI_RX_SYS_CONF_REG0D_REGINTPOL_MASK,
                       MIPI_RX_SYS_CONF_REG0D_REGINTPOL(0x00U));
    /* Setup swap(dp/dn, lane), lane numbers */
    MIPIRX_SetI2C_Byte(handle, MIPI_RX_SYS_CONF_REG0C,
                       MIPI_RX_SYS_CONF_REG0C_RegLaneNum_MASK | MIPI_RX_SYS_CONF_REG0C_RegEnPNSwap_MASK |
                           MIPI_RX_SYS_CONF_REG0C_RegEnLaneSwap_MASK,
                       MIPI_RX_SYS_CONF_REG0C_RegEnLaneSwap((uint32_t)it6161.mipi_rx.mipirx_lane_swap) |
                           MIPI_RX_SYS_CONF_REG0C_RegEnPNSwap((uint32_t)it6161.mipi_rx.mipirx_dpdn_swap) |
                           MIPI_RX_SYS_CONF_REG0C_RegLaneNum((uint32_t)it6161.mipi_rx.lanes));
    /* Setup mclk, pclk, standby mode, standby to reset, iddq mode */
    MIPIRX_SetI2C_Byte(handle, MIPI_RX_CLKBUF_CTRL_REG11,
                       MIPI_RX_CLKBUF_CTRL_REG11_RegInvMCLK_MASK | MIPI_RX_CLKBUF_CTRL_REG11_RegInvPCLK_MASK |
                           MIPI_RX_CLKBUF_CTRL_REG11_RegEnStandby_MASK | MIPI_RX_CLKBUF_CTRL_REG11_RegEnStb2Rst_MASK |
                           MIPI_RX_CLKBUF_CTRL_REG11_RegEnIDDQ_MASK,
                       MIPI_RX_CLKBUF_CTRL_REG11_RegInvMCLK((uint32_t)it6161.mipi_rx.inverse_mclk) |
                           MIPI_RX_CLKBUF_CTRL_REG11_RegInvPCLK((uint32_t)it6161.mipi_rx.inverse_pclk) |
                           MIPI_RX_CLKBUF_CTRL_REG11_RegEnStandby((uint32_t)it6161.mipi_rx.enable_standby_mode) |
                           MIPI_RX_CLKBUF_CTRL_REG11_RegEnStb2Rst((uint32_t)it6161.mipi_rx.enable_standby_to_reset) |
                           MIPI_RX_CLKBUF_CTRL_REG11_RegEnIDDQ((uint32_t)it6161.mipi_rx.enable_iddq_mode));
    /* Setup reference clock */
    MIPIRX_SetI2C_Byte(handle, MIPI_RX_CLKBUF_CTRL_REG12,
                       MIPI_RX_CLKBUF_CTRL_REG12_RegPDREFCLK_MASK | MIPI_RX_CLKBUF_CTRL_REG12_RegPDREFCNT_MASK,
                       MIPI_RX_CLKBUF_CTRL_REG12_RegPDREFCLK((uint32_t)it6161.mipi_rx.pd_ref_clk) |
                           MIPI_RX_CLKBUF_CTRL_REG12_RegPDREFCNT((uint32_t)it6161.mipi_rx.pd_ref_cnt));
    /* Setup PHY-Protocol Interface(hs settle numbers, hs trailing skip stage, enable sync bit error tolerance) */
    MIPIRX_SetI2C_Byte(
        handle, MIPI_RX_PPI_REG18,
        MIPI_RX_PPI_REG18_RegHSSetNum_MASK | MIPI_RX_PPI_REG18_RegSkipStg_MASK | MIPI_RX_PPI_REG18_RegEnSyncErr_MASK,
        MIPI_RX_PPI_REG18_RegHSSetNum((uint32_t)it6161.mipi_rx.hs_settle_num) |
            MIPI_RX_PPI_REG18_RegSkipStg((uint32_t)it6161.mipi_rx.hs_trailing_skip_stage) |
            MIPI_RX_PPI_REG18_RegEnSyncErr((uint32_t)it6161.mipi_rx.enable_sync_bit_error_tolerance));
    /* Setup PHY-Protocol Interface(enable multi lane deskew, force continuous clock mode, ppi debug selection)*/
    MIPIRX_SetI2C_Byte(
        handle, MIPI_RX_PPI_REG19,
        MIPI_RX_PPI_REG19_RegEnDeSkew_MASK | MIPI_RX_PPI_REG19_RegEnContCK_MASK | MIPI_RX_PPI_REG19_RegPPIDbgSel_MASK,
        MIPI_RX_PPI_REG19_RegEnDeSkew((uint32_t)it6161.mipi_rx.enable_multi_lane_deskew) |
            MIPI_RX_PPI_REG19_RegEnContCK((uint32_t)it6161.mipi_rx.force_continuous_clock_mode) |
            MIPI_RX_PPI_REG19_RegPPIDbgSel((uint32_t)it6161.mipi_rx.ppi_debug_selection));
    /* Setup lane merge & packet decoder (ignore null packet, ignore blank packet, dummy ecc error, recognize EOTP) */
    MIPIRX_SetI2C_Byte(
        handle, MIPI_RX_LANE_MERGE_PACKET_DECODER_REG20,
        MIPI_RX_LANE_MERGE_PACKET_DECODER_REG20_RegIgnrNull_MASK |
            MIPI_RX_LANE_MERGE_PACKET_DECODER_REG20_RegIgnrBlk_MASK |
            MIPI_RX_LANE_MERGE_PACKET_DECODER_REG20_RegEnDummyECC_MASK |
            MIPI_RX_LANE_MERGE_PACKET_DECODER_REG20_RegSelEOTP_MASK,
        MIPI_RX_LANE_MERGE_PACKET_DECODER_REG20_RegIgnrNull((uint32_t)it6161.mipi_rx.ignore_null_packet) |
            MIPI_RX_LANE_MERGE_PACKET_DECODER_REG20_RegIgnrBlk((uint32_t)it6161.mipi_rx.ignore_blank_packet) |
            MIPI_RX_LANE_MERGE_PACKET_DECODER_REG20_RegEnDummyECC((uint32_t)it6161.mipi_rx.enable_dummy_ecc_error) |
            MIPI_RX_LANE_MERGE_PACKET_DECODER_REG20_RegSelEOTP((uint32_t)it6161.mipi_rx.sel_eotp));
    MIPIRX_SetI2C_Byte(
        handle, MIPI_RX_LANE_MERGE_PACKET_DECODER_REG21, MIPI_RX_LANE_MERGE_PACKET_DECODER_REG21_RegSelLMDbg_MASK,
        MIPI_RX_LANE_MERGE_PACKET_DECODER_REG21_RegSelLMDbg((uint32_t)it6161.mipi_rx.lm_debug_selection));
    /* Setup packed pixel stream, timing generator and pattern generation(auto sync falling, interlaced mode, user
     * define timming register, prec and mrec update) */
    MIPIRX_SetI2C_Byte(
        handle, MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG44,
        MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG44_RegAutoSyncF_MASK |
            MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG44_RegMipi_Interlaced_MASK |
            MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG44_RegSEModeUdef_MASK |
            MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG44_RegPRec_UPdate_MASK |
            MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG44_RegMRec_UPdate_MASK,
        MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG44_RegAutoSyncF(
            (uint32_t)it6161.mipi_rx.auto_sync_falling) |
            MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG44_RegMipi_Interlaced(
                (uint32_t)it6161.mipi_rx.interlaced_mode) |
            MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG44_RegSEModeUdef(
                (uint32_t)it6161.mipi_rx.user_define_timming) |
            MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG44_RegPRec_UPdate(
                (uint32_t)it6161.mipi_rx.prec_update) |
            MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG44_RegMRec_UPdate(
                (uint32_t)it6161.mipi_rx.mrec_update));
    MIPIRX_SetI2C_Byte(handle, MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG4B,
                       MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG4B_RegVREnhSel_MASK |
                           MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG4B_RegVREnh_MASK |
                           MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG4B_RegFReSyncEn_MASK,
                       MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG4B_RegVREnhSel(
                           (uint32_t)it6161.mipi_rx.v_timing_resync_selction) |
                           MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG4B_RegVREnh(
                               (uint32_t)it6161.mipi_rx.enable_v_timing_resync_enhance_mode) |
                           MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG4B_RegFReSyncEn(
                               (uint32_t)it6161.mipi_rx.enable_frame_resync));
    MIPIRX_SetI2C_Byte(handle, MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG4C,
                       MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG4C_RegFFRdStg_MASK,
                       MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG4C_RegFFRdStg(
                           (uint32_t)it6161.mipi_rx.pps_fifo_read_start_point & 0xFFU));
    MIPIRX_SetI2C_Byte(handle, MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG4E,
                       MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG4E_RegHReSyncEn_MASK |
                           MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG4E_RegVReSyncEn_MASK,
                       MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG4E_RegHReSyncEn(
                           (uint32_t)it6161.mipi_rx.enable_h_timing_resync) |
                           MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG4E_RegVReSyncEn(
                               (uint32_t)it6161.mipi_rx.enable_v_timing_resync));
    MIPIRX_SetI2C_Byte(
        handle, MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG4F,
        MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG4F_RegPPSFFAutoRst_MASK |
            MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG4F_RegEnPPSFFOv2Rst_MASK,
        MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG4F_RegPPSFFAutoRst(
            (uint32_t)it6161.mipi_rx.enable_fifo_auto_reset) |
            MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG4F_RegEnPPSFFOv2Rst(
                (uint32_t)it6161.mipi_rx.enable_overflow_auto_reset));
    MIPIRX_SetI2C_Byte(handle, MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG70,
                       MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG70_RegEnMAvg_MASK,
                       MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG70_RegEnMAvg(
                           (uint32_t)it6161.mipi_rx.enable_mclk_horizontal_average));
    MIPIRX_WriteI2C_Byte(handle, MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG72,
                         MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG72_RegMShift(
                             (uint32_t)it6161.mipi_rx.allowable_mclk_horizontal_shift_value));
    MIPIRX_WriteI2C_Byte(handle, MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG73,
                         MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG73_RegPShift(
                             (uint32_t)it6161.mipi_rx.allowable_pclk_horizontal_shift_value));
    MIPIRX_SetI2C_Byte(handle, MIPI_RX_AFE_REG80, MIPI_RX_AFE_REG80_RegEnExtPCLK_MASK,
                       MIPI_RX_AFE_REG80_RegEnExtPCLK((uint32_t)it6161.mipi_rx.enable_external_pclk));
    MIPIRX_WriteI2C_Byte(handle, MIPI_RX_LANE_MERGE_PACKET_DECODER_REG21, 0x00U);
    /* Select termination value of all of the channels: 116 ohm */
    MIPIRX_SetI2C_Byte(handle, MIPI_RX_AFE_REG84, MIPI_RX_AFE_REG84_REGRTERM_MASK, MIPI_RX_AFE_REG84_REGRTERM(0x00U));
    MIPIRX_SetI2C_Byte(handle, MIPI_RX_TX_PATTERN_CONTENT_REGA0, MIPI_RX_TX_PATTERN_CONTENT_REGA0_RegMBPM_MASK,
                       MIPI_RX_TX_PATTERN_CONTENT_REGA0_RegMBPM((uint32_t)it6161.mipi_rx.bypass_through_mode));
    /* Enable auto detect format */
    MIPIRX_SetI2C_Byte(handle, MIPI_RX_LANE_MERGE_PACKET_DECODER_REG21, 0x08U, 0x08U);

    MIPIRX_SetI2C_Byte(handle, MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG70,
                       MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG70_RegEnMAvg_MASK,
                       MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG70_RegEnMAvg(
                           (uint32_t)it6161.mipi_rx.enable_mclk_horizontal_average));

    /* Video Clock Domain Reset */
    MIPIRX_SetI2C_Byte(handle, MIPI_RX_SOFT_RESET_REG05, MIPI_RX_SOFT_RESET_REG05_RegSoftMRst_MASK,
                       MIPI_RX_SOFT_RESET_REG05_RegSoftMRst(0x01U));
    if (it6161.mipi_rx.bypass_through_mode != 0x0U)
    {
        /* Setup BYPASS MODE HFP OFFSET */
        MIPIRX_WriteI2C_Byte(handle, MIPI_RX_TX_PATTERN_CONTENT_REGA1, 0x00U);

        /* Setup BYPASS MODE VFP OFFSET */
        MIPIRX_WriteI2C_Byte(handle, MIPI_RX_TX_PATTERN_CONTENT_REGA2, 0x00U);

        /* Setup BYPASS MODE HSW */
        MIPIRX_WriteI2C_Byte(handle, MIPI_RX_TX_PATTERN_CONTENT_REGA3, 0x08U);
        /* Setup BYPASS MODE VSW */
        MIPIRX_WriteI2C_Byte(handle, MIPI_RX_TX_PATTERN_CONTENT_REGA5, 0x04U);
    }

    if (it6161.mipi_rx.user_define_timming == 0x0U)
    {
        MIPIRX_SetI2C_Byte(
            handle, MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG31,
            MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG31_RegEnUsrHFP_MASK,
            MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG31_RegEnUsrHFP(0x00U));
        MIPIRX_SetI2C_Byte(
            handle, MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG33,
            MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG33_RegEnUsrHSW_MASK,
            MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG33_RegEnUsrHSW(0x00U));
        MIPIRX_SetI2C_Byte(
            handle, MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG35,
            MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG35_RegEnUsrHBP_MASK,
            MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG35_RegEnUsrHBP(0x00U));
        MIPIRX_SetI2C_Byte(
            handle, MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG37,
            MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG37_RegEnUsrHDEW_MASK,
            MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG37_RegEnUsrHDEW(0x00U));
        MIPIRX_SetI2C_Byte(
            handle, MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG39,
            MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG39_RegEnUsrHVR2nd_MASK,
            MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG39_RegEnUsrHVR2nd(0x00U));
        MIPIRX_SetI2C_Byte(
            handle, MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG3A, 0x80U,
            0x00U); /* Does it means to disable User defined Mipi_VFP of REG3B? if yes, need change 3A to 3B */
        MIPIRX_SetI2C_Byte(
            handle, MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG3C, 0x80U,
            0x00U); /* Does it means to disable User defined Mipi_VSW of REG3D? if yes, need change 3C to 3D */
        MIPIRX_SetI2C_Byte(
            handle, MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG3E, 0x80U,
            0x00U); /* Does it means to disable User defined Mipi_VBP of REG3F? if yes, need change 3E to 3F */
        MIPIRX_SetI2C_Byte(
            handle, MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG41,
            MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG41_RegEnUsrVDEW_MASK,
            MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG41_RegEnUsrVDEW(0x00U));
        MIPIRX_SetI2C_Byte(
            handle, MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG43,
            MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG43_RegEnUsrVFP2nd_MASK,
            MIPI_RX_PACKED_PIXEL_STREAM_TIMING_GENERATOR_AND_PATTERN_GENERATION_REG43_RegEnUsrVFP2nd(0x00U));
    }
}

static RegSetTable_t HDMITX_Init_Table[] = {

    {0x0F, 0x40, 0x00},

    /* PLL Reset */
    {0x62, 0x08, 0x00}, /* XP_RESETB */
    {0x64, 0x04, 0x00}, /* IP_RESETB */

    {0x0F, 0x01, 0x00}, // bank 0;

    {0x8D, 0xFF, HDMI_TX_CEC_I2C_SLAVE_ADDR},
    {HDMI_TX_PATTERN_GENERATOR_REGA9, HDMI_TX_PATTERN_GENERATOR_REGA9_RegHBPM_SHIFT,
     HDMI_TX_PATTERN_GENERATOR_REGA9_RegHBPM(EN_HDMITX_BYPASS_MODE)},
    {HDMI_TX_PATTERN_GENERATOR_REGBF, 0x80, NRTXRCLK << 7}, /* Cannot find it from it6161 programming guide */

    {0xF8, 0xFF, 0xC3},
    {0xF8, 0xFF, 0xA5},
    {0xF4, 0x0C, 0x00},
    {0xF3, 0x02, 0x00},
    {0xF8, 0xFF, 0xFF},

    {0x5A, 0x0C, 0x0C},
    {HDMI_TX_HDMI_CONTROL_REGD1, HDMI_TX_HDMI_CONTROL_REGD1_RegStableDbgMd_MASK,
     (FORCE_TXCLK_STABLE << 3) | (STABLE_LINEPIEXELCNT_SENSITIVITY << 1)},
    {HDMI_TX_CLOCK_CONTROL_REG5D, 0x04, (RCLK_FREQ_SEL << 2)}, /* Cannot find it from it6161 programming guide */
    {0x65, 0x03, 0x00},
    {0x71, 0xF9,
     0x18}, /* XP_Lock stable time: 00: 75us; check XP_lock for TX fifo reset: 0: disable; reset TX fifo when PLL
               unlock: 0: disable; TX fifo auto reset enable: 1: enable; TX fifo manual reset: 0: disable */
    {0xCF, 0xFF, 0x00}, /* packet blan guard band option: 00: +4; packet limit guard band option: 00: +32; packet keep
                           out guard band option: 00: +8; guard band for packet transmission in blank period: 0:
                           disable; guard band for packet transmission in limit period: 0: disable */
    {0xD1, 0x02, 0x00}, /* stable linepixelcnt sensitivity: 0: low sensitivity */

    {0x59, 0xD0, 0x40}, /* VCLK frequncy depends on REGManualPLLPR when REGDisLockPR=1: 01: 2x; 0: internal pixel clock
                           frequency depends on pixel repetition factor in AVI infoframe */
    {0xE1, 0x20, 0x00}, /* 0: use rising edge to sample WS and I2S */
    {0xF5, 0x40, 0x00}, /* cannot find the field from it6161 programming guide */
    {0x05, 0xC0, 0x40}, /* 0: INT active low; 1: Open-Drain mode */
    {0x0C, 0xFF, 0xFF}, /* Clear the interrupt */
    {0x0D, 0xFF, 0x00}, /* Don't know what's meaning? */
    {0x0E, 0x02, 0x00}, /* Clear AduCTS interrupt? unsure */

    {0x0C, 0xFF, 0x00},
    {0x0D, 0xFF, 0x00},
    {0x0E, 0x02, 0x00},
    {0x20, 0x01, 0x00},
};

static RegSetTable_t HDMITX_PwrOn_Table[] = {
    /* PwrOn RCLK , IACLK ,TXCLK */
    {0x0F, 0x70, 0x00},
    /* PLL PwrOn */
    /* PwrOn DRV */
    {0x61, 0x20, 0x00},
    /* PwrOn XPLL */
    {0x62, 0x44, 0x00},
    /* PwrOn IPLL */
    {0x64, 0x40, 0x00},
    /* PLL Reset OFF */
    /* DRV_RST */
    {0x61, 0x10, 0x00},
    /* XP_RESETB */
    {0x62, 0x08, 0x08},
    /* IP_RESETB */
    {0x64, 0x04, 0x04},
};

void it6161_HDMITX_Init(display_handle_t *handle)
{
    HDMITX_LoadRegSetting(handle, HDMITX_Init_Table, sizeof(HDMITX_Init_Table));
    HDMITX_LoadRegSetting(handle, HDMITX_PwrOn_Table, sizeof(HDMITX_PwrOn_Table));
}

static void it6161_MIPIRX_Init(display_handle_t *handle)
{
    it6161_MIPIRX_CONF(handle);
    /* Enable MIPI RX clock domain */
    MIPIRX_SetI2C_Byte(handle, MIPI_RX_SOFT_RESET_REG05,
                       MIPI_RX_SOFT_RESET_REG05_RegSoftORst_MASK | MIPI_RX_SOFT_RESET_REG05_RegSoftMRst_MASK, 0x00U);
}

void it6161_SetIntActiveLevel(display_handle_t *handle, enum it6161_active_level level)
{
    MIPIRX_SetI2C_Byte(
        handle, MIPI_RX_SYS_CONF_REG0D, MIPI_RX_SYS_CONF_REG0D_REGINTPOL_MASK,
        ((level == HIGH_LVL) ? (MIPI_RX_SYS_CONF_REG0D_REGINTPOL(0x01U)) : (MIPI_RX_SYS_CONF_REG0D_REGINTPOL(0x00U))));
    HDMITX_SetI2C_Byte(
        handle, HDMI_TX_GENERAL_REG05, HDMI_TX_GENERAL_REG05_REGINTPOL_MASK | HDMI_TX_GENERAL_REG05_REGINTIOMODE_MASK,
        ((level == HIGH_LVL) ? (HDMI_TX_GENERAL_REG05_REGINTPOL(0x01U) | HDMI_TX_GENERAL_REG05_REGINTIOMODE(0x00U)) :
                               (HDMI_TX_GENERAL_REG05_REGINTPOL(0x00U) | HDMI_TX_GENERAL_REG05_REGINTIOMODE(0x01U))));
}
void it6161_IntMaskEnable(display_handle_t *handle)
{
    MIPIRX_SetI2C_Byte(handle, MIPI_RX_SYS_STATUS_REG0F, 0x03U,
                       0x00U); /* Cannot find relative information about these fields from it6161 programming guide */

    MIPIRX_WriteI2C_Byte(handle, MIPI_RX_INT_MASK_REG09,
                         MIPI_RX_INT_MASK_REG09_REnPPSMVidStbChgInt | MIPI_RX_INT_MASK_REG09_REnPPSPVidStbChgInt);
    MIPIRX_WriteI2C_Byte(handle, MIPI_RX_INT_MASK_REG0A,
                         MIPI_RX_INT_MASK_REG0A_REnPPGVidStbChgInt | MIPI_RX_INT_MASK_REG0A_REnPPSDByteErrInt |
                             MIPI_RX_INT_MASK_REG0A_REnCMOffInt | MIPI_RX_INT_MASK_REG0A_REnCMOnInt |
                             MIPI_RX_INT_MASK_REG0A_REnShutDoneInt | MIPI_RX_INT_MASK_REG0A_REnTurnOnInt);
    // MIPI_RX_INT_MASK_REG0A_REnFIFOOvRdInt | MIPI_RX_INT_MASK_REG0A_REnFIFOOvWrInt);
    // MIPI_RX_INT_MASK_REG0A_REnFIFOOvRdInt);

    MIPIRX_WriteI2C_Byte(handle, MIPI_RX_INT_MASK_REG0B,
                         MIPI_RX_INT_MASK_REG0B_REnECC1bErrInt | MIPI_RX_INT_MASK_REG0B_REnECC2bErrInt |
                             MIPI_RX_INT_MASK_REG0B_REnLMFIFOErrInt | MIPI_RX_INT_MASK_REG0B_REnCRCErrInt |
                             MIPI_RX_INT_MASK_REG0B_REnMCLKOffInt | MIPI_RX_INT_MASK_REG0B_REnPPIFifoOvWrInt);

    /* select bank0, 0x00~0xff */
    HDMITX_SetI2C_Byte(handle, HDMI_TX_SYS_STATUS_REG0F, HDMI_TX_SYS_STATUS_REG0F_REGBANKSEL_MASK,
                       HDMI_TX_SYS_STATUS_REG0F_REGBANKSEL(0x00U));
    HDMITX_WriteI2C_Byte(handle, HDMI_TX_INT_MASK_REG09,
                         HDMI_TX_INT_MASK_REG09_REG_AudioOvFlw(0x00U) | HDMI_TX_INT_MASK_REG09_REG_DDCNoACK(0x00U) |
                             HDMI_TX_INT_MASK_REG09_REG_DDCFIFOErr(0x00U) |
                             HDMI_TX_INT_MASK_REG09_REG_DDCBusHang(0x00U) | HDMI_TX_INT_MASK_REG09_REG_RxSEN(0x00U) |
                             HDMI_TX_INT_MASK_REG09_REG_HPD(0x00U));
    HDMITX_SetI2C_Byte(handle, HDMI_TX_INT_MASK_REG0B, HDMI_TX_INT_MASK_REG0B_REG_VidStable_MASK,
                       HDMI_TX_INT_MASK_REG0B_REG_VidStable(0x00U));
}

status_t IT6161_Init(display_handle_t *handle, const display_config_t *config)
{
    status_t status;

    assert(handle);

    status = IT6161_Identify(handle);
    if (kStatus_Success != status)
    {
        return status;
    }

    it6161.mipi_rx.hs_settle_num                   = 0x01U;
    it6161.mipi_rx.hs_trailing_skip_stage          = 0x04U;
    it6161.mipi_rx.enable_sync_bit_error_tolerance = 0x00U;
    it6161.mipi_rx.enable_multi_lane_deskew        = 0x01U;
    it6161.mipi_rx.force_continuous_clock_mode     = 0x01U;
    it6161.mipi_rx.ppi_debug_selection             = 0x0CU;
    it6161.mipi_rx.ignore_null_packet              = 0x01U;
    it6161.mipi_rx.ignore_blank_packet             = 0x01U;
    it6161.mipi_rx.enable_dummy_ecc_error          = 0x00U;
    it6161.mipi_rx.sel_eotp                        = 0x00U;
    it6161.mipi_rx.lm_debug_selection              = 0x00U;

    it6161.mipi_rx.auto_sync_falling   = 0x01U;
    it6161.mipi_rx.interlaced_mode     = 0x00U;
    it6161.mipi_rx.user_define_timming = 0x00U;
    it6161.mipi_rx.prec_update         = PREC_UPDATE;
    it6161.mipi_rx.mrec_update         = MREC_UPDATE;

    it6161.mipi_rx.v_timing_resync_selction              = 0x01U;
    it6161.mipi_rx.enable_v_timing_resync_enhance_mode   = 0x00U;
    it6161.mipi_rx.enable_frame_resync                   = 0x00U;
    it6161.mipi_rx.pps_fifo_read_start_point             = 0x04U;
    it6161.mipi_rx.enable_h_timing_resync                = 0x00U;
    it6161.mipi_rx.enable_v_timing_resync                = 0x00U;
    it6161.mipi_rx.enable_fifo_auto_reset                = 0x01U;
    it6161.mipi_rx.enable_overflow_auto_reset            = 0x00U;
    it6161.mipi_rx.enable_mclk_horizontal_average        = 0x01U;
    it6161.mipi_rx.allowable_mclk_horizontal_shift_value = 0x08U;
    it6161.mipi_rx.allowable_pclk_horizontal_shift_value = 0x03U;
    it6161.mipi_rx.enable_external_pclk                  = 0x00U;
    it6161.mipi_rx.bypass_through_mode                   = EN_MIPIRX_BYPASS_MODE;
    it6161.mipi_rx.enable_ttl_tx_crc                     = 0x01U;
    it6161.mipi_rx.crc_frame_number                      = 0x20U;

    it6161.mipi_rx.mipirx_lane_swap = 0x00U;
    it6161.mipi_rx.mipirx_dpdn_swap = 0x00U;
    it6161.mipi_rx.lanes            = config->dsiLanes;
    it6161.mipi_rx.inverse_mclk     = 0x01U;

    it6161.hdmi_tx.hdmitx_bypass_mode       = EN_HDMITX_BYPASS_MODE;
    it6161.hdmi_tx.tx_clk_stable            = FORCE_TX_CLK_STABLE;
    it6161.hdmi_tx.tx_vid_stable            = FORCE_TX_VID_STABLE;
    it6161.hdmi_tx.de_generation_enable     = 0x00U; /* The DE input received are used for HDMI output */
    it6161.hdmi_tx.vertical_sync_polarity   = V_SYNC_POL;
    it6161.hdmi_tx.horizontal_sync_polarity = H_SYNC_POL;
    it6161.hdmi_tx.de_only_in               = 0x01U;

    /* Use these arguments to generate hdmi blank timing */
    it6161.hdmi_tx.mode.hdisplay    = FSL_VIDEO_EXTRACT_WIDTH(config->resolution);
    it6161.hdmi_tx.mode.hsync_start = FSL_VIDEO_EXTRACT_WIDTH(config->resolution) + config->hfp;
    it6161.hdmi_tx.mode.hsync_end   = FSL_VIDEO_EXTRACT_WIDTH(config->resolution) + config->hfp + config->hsw;
    it6161.hdmi_tx.mode.htotal = FSL_VIDEO_EXTRACT_WIDTH(config->resolution) + config->hfp + config->hsw + config->hbp;
    it6161.hdmi_tx.mode.vdisplay    = FSL_VIDEO_EXTRACT_HEIGHT(config->resolution);
    it6161.hdmi_tx.mode.vsync_start = FSL_VIDEO_EXTRACT_HEIGHT(config->resolution) + config->vfp;
    it6161.hdmi_tx.mode.vsync_end   = FSL_VIDEO_EXTRACT_HEIGHT(config->resolution) + config->vfp + config->vsw;
    it6161.hdmi_tx.mode.vtotal = FSL_VIDEO_EXTRACT_HEIGHT(config->resolution) + config->vfp + config->vsw + config->vbp;
    it6161.hdmi_tx.support_audio = HDMI_TX_SUPPORT_AUDIO;
    if (it6161.hdmi_tx.support_audio != 0x0U)
    {
        it6161.hdmi_tx.output_channel          = HDMI_TX_OUTPUT_CHANNEL;
        it6161.hdmi_tx.input_audio_type        = HDMI_TX_INPUT_AUDIO_TYPE;
        it6161.hdmi_tx.input_audio_interface   = (uint8_t)HDMI_TX_INPUT_AUDIO_INTERFACE;
        it6161.hdmi_tx.input_audio_sample_freq = HDMI_TX_INPUT_AUDIO_SAMPLE_FREQ;
    }
    it6161.hdmi_tx.pclk_div2 = HDMI_TX_PCLK_DIV2;

    it6161_MIPIRX_Init(handle);
    it6161_HDMITX_Init(handle);
    /* set it6161's active level as high level */
    it6161_SetIntActiveLevel(handle, HIGH_LVL);

    it6161_IntMaskEnable(handle);

    return status;
}

status_t IT6161_Deinit(display_handle_t *handle)
{
    return kStatus_Success;
}

status_t IT6161_Start(display_handle_t *handle)
{
    return kStatus_Success;
}

status_t IT6161_Stop(display_handle_t *handle)
{
    return kStatus_Success;
}

void IT6161_Interrupt(display_handle_t *handle)
{
    MIPIRX_DevLoopProc(handle);
    HDMITX_DevLoopProc(handle);
}
