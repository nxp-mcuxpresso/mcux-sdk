/*
 * Copyright 2017-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "dpu_example.h"

#if DPU_EXAMPLE_DI == DPU_DI_MIPI
#include "fsl_mipi_dsi.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint32_t mipiDsiTxEscClkFreq_Hz;
uint32_t mipiDsiRxEscClkFreq_Hz;
uint32_t mipiDsiDphyRefClkFreq_Hz;
uint32_t mipiDsiDphyBitClkFreq_Hz;
uint32_t mipiDsiDpiClkFreq_Hz;

/*******************************************************************************
 * Codes
 ******************************************************************************/
void APP_StartDisplayInterface(void)
{
    dsi_config_t dsiConfig;
    dsi_dphy_config_t dphyConfig;

    const dsi_dpi_config_t dpiConfig = {
        .pixelPayloadSize = APP_PANEL_WIDTH,
        .dpiColorCoding   = kDSI_Dpi24Bit,
        .pixelPacket      = kDSI_PixelPacket24Bit,
#if APP_DISPLAY_EXTERNAL_CONVERTOR
        .videoMode = kDSI_DpiNonBurstWithSyncPulse,
#else
        .videoMode = kDSI_DpiBurst,
#endif
        .bllpMode       = kDSI_DpiBllpLowPower,
        .polarityFlags  = kDSI_DpiVsyncActiveLow | kDSI_DpiHsyncActiveLow,
        .hfp            = APP_HFP,
        .hbp            = APP_HBP,
        .hsw            = APP_HSW,
        .vfp            = APP_VFP,
        .vbp            = APP_VBP,
        .panelHeight    = APP_PANEL_HEIGHT,
        .virtualChannel = 0
    };

    SOC_ResetMipiDsi(APP_MIPI_DSI, kMIPI_DsiDpi, 0);
    SOC_ResetMipiDsi(APP_MIPI_DSI, kMIPI_DsiEsc, 0);
    SOC_ResetMipiDsi(APP_MIPI_DSI, kMIPI_DsiPhy, 0);

    /*
     * dsiConfig.numLanes = 4;
     * dsiConfig.enableNonContinuousHsClk = false;
     * dsiConfig.autoInsertEoTp = true;
     * dsiConfig.numExtraEoTp = 0;
     * dsiConfig.htxTo_ByteClk = 0;
     * dsiConfig.lrxHostTo_ByteClk = 0;
     * dsiConfig.btaTo_ByteClk = 0;
     */
    DSI_GetDefaultConfig(&dsiConfig);
    dsiConfig.numLanes = APP_MIPI_DSI_LANE_NUM;
#if APP_DISPLAY_EXTERNAL_CONVERTOR
    dsiConfig.autoInsertEoTp = false;
#else
    dsiConfig.autoInsertEoTp = true;
#endif

    DSI_GetDphyDefaultConfig(&dphyConfig, mipiDsiDphyBitClkFreq_Hz, mipiDsiTxEscClkFreq_Hz);

    /* Init the DSI module. */
    DSI_Init(APP_MIPI_DSI, &dsiConfig);

    /* Init DPHY. */
    DSI_InitDphy(APP_MIPI_DSI, &dphyConfig, mipiDsiDphyRefClkFreq_Hz);

    /* Init DPI interface. */
    DSI_SetDpiConfig(APP_MIPI_DSI, &dpiConfig, APP_MIPI_DSI_LANE_NUM, mipiDsiDpiClkFreq_Hz, mipiDsiDphyBitClkFreq_Hz);

    /* DSI out of reset. */
    SOC_ResetMipiDsi(APP_MIPI_DSI, kMIPI_DsiPhy, 1);
    SOC_ResetMipiDsi(APP_MIPI_DSI, kMIPI_DsiEsc, 1);

    BOARD_InitLcdPanel();

    SOC_ResetMipiDsi(APP_MIPI_DSI, kMIPI_DsiDpi, 1);
}

#elif DPU_EXAMPLE_DI == DPU_DI_LVDS

#include "fsl_ldb.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint32_t displayPixelClkFreq_Hz;

/*******************************************************************************
 * Codes
 ******************************************************************************/
void APP_StartDisplayInterface(void)
{
    ldb_channel_config_t ldbConfig = {
        .outputBus     = kLDB_OutputRGB888_7Bit_JEIDA,
        .inputFlag     = kLDB_InputVsyncActiveLow | kLDB_InputHsyncActiveLow | kLDB_InputDataLatchOnRisingEdge,
        .pixelClock_Hz = displayPixelClkFreq_Hz,
    };

    LDB_Init(APP_LDB);

    BOARD_InitLcdPanel();

    LDB_InitChannel(APP_LDB, APP_LDB_CH, &ldbConfig);
}

#else
#error Unsupported display interface
#endif
