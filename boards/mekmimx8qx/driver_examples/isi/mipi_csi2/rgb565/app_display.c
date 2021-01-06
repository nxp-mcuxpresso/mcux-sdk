/*
 * Copyright 2017, 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "app_display.h"
#include "isi_config.h"
#include "isi_example.h"
#include "fsl_dpu.h"

#if (defined(APP_DPU_USE_PREFETCH) && APP_DPU_USE_PREFETCH)
#include "fsl_prg.h"
#include "fsl_dpr.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

typedef struct
{
    uint32_t activeFb;
    uint32_t inactiveFb;
    app_display_callback_t callback;
    volatile bool isFramePending;
} app_display_handle_t;

#ifndef APP_RESIZE_CAMERA_IMAGE
#define APP_RESIZE_CAMERA_IMAGE 0
#endif

/*
 * Scaler unit.
 * For up-scaling horizontally, the path is ->VSCALER -> HSCALER ->
 * For Down-scaling horizontally, the path is ->HSCALER -> VSCALER ->
 */
#if APP_RESIZE_CAMERA_IMAGE

#if (APP_CAMERA_WIDTH < APP_FRAME_WIDTH)
/* FETCHDECODE ->VSCALER -> HSCALER -> LAYERBLEND. */
#define APP_LAYERBLEND_SECOND_SRC kDPU_UnitSrcHScaler4
#define APP_VSCALER_SRC           kDPU_UnitSrcFetchDecode0
#define APP_HSCALER_SRC           kDPU_UnitSrcVScaler4

#else
/* FETCHDECODE ->HSCALER -> VSCALER -> LAYERBLEND. */
#define APP_LAYERBLEND_SECOND_SRC kDPU_UnitSrcVScaler4
#define APP_VSCALER_SRC           kDPU_UnitSrcHScaler4
#define APP_HSCALER_SRC           kDPU_UnitSrcFetchDecode0

#endif

#else
#define APP_LAYERBLEND_SECOND_SRC kDPU_UnitSrcFetchDecode0
#endif /* APP_RESIZE_CAMERA_IMAGE */

/*******************************************************************************
 * Variables
 ******************************************************************************/
static app_display_handle_t s_displayHandle;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void APP_StartDisplayInterface(void);

/*******************************************************************************
 * Codes
 ******************************************************************************/

/*
  The DPU path is configured like this:


               |  Input frame
               v
       +-----------------+     +-----------------+       +-----------------+
       |                 |     |                 |       |                 |
       |   FetchDecode0  |     |  Const Frame 0  |       |  Const Frame 4  |
       |                 |     |                 |       |                 |
       +-----------------+     +-----------------+       +-----------------+
               |                        |                         |
               |                        v                         |
               |               +-----------------+                |
               |               |                 |                |
               +-------------->|   LayerBlend 0  |                |
                               |                 |                |
                               +-----------------+                |
                                        |                         |
                                        v                         v
                               +-----------------+       +-----------------+
                               |                 |       |                 |
                               |  ExtDst 0 or 1  |       |  ExtDst 4 or 5  |
                               |                 |       |                 |
                               +-----------------+       +-----------------+
                                        |                         |
                                        |                         v
                                        |                +-----------------+
                                        |                |                 |
                                        +--------------->| FrameGen 0 or 1 |
                                                         |                 |
                                                         +-----------------+
                                                                  |
                                                                  v

 */
void APP_InitDisplay(uint32_t frameBuffer, app_display_callback_t callback)
{
    dpu_display_timing_config_t displayTimingConfig;
    dpu_const_frame_config_t cfConfig;
    dpu_layer_blend_config_t lbConfig;
    dpu_fetch_unit_config_t fetchConfig;
    dpu_src_buffer_config_t sbConfig;
    dpu_display_config_t displayConfig;
#if APP_RESIZE_CAMERA_IMAGE
    dpu_scaler_config_t scConfig;
#endif
#if (defined(APP_DPU_USE_PREFETCH) && APP_DPU_USE_PREFETCH)
    dpr_buffer_config_t dprConfig;
    prg_buffer_config_t prgConfig;
#endif

    memset(&s_displayHandle, 0, sizeof(s_displayHandle));

    DPU_Init(APP_DPU);

    DPU_PreparePathConfig(APP_DPU);

    /* Step 1: Configure the safety stream */

    /* Pipeline. */
    DPU_InitPipeline(APP_DPU, APP_SAFETY_STREAM_PIPELINE);

    /* ExtDst. */
    DPU_InitExtDst(APP_DPU, APP_SAFETY_STREAM_EXTDST, DPU_MAKE_SRC_REG1(kDPU_UnitSrcConstFrame4));

    /* Const frame. */
    cfConfig.frameWidth  = APP_FRAME_WIDTH;
    cfConfig.frameHeight = APP_FRAME_HEIGHT;
    cfConfig.constColor  = DPU_MAKE_CONST_COLOR(0, 0, 0, 0);
    DPU_InitConstFrame(APP_DPU, kDPU_ConstFrame4);
    DPU_SetConstFrameConfig(APP_DPU, kDPU_ConstFrame4, &cfConfig);

    /* Configuration complete, trigger the shadow load. */
    DPU_TriggerPipelineShadowLoad(APP_DPU, APP_SAFETY_STREAM_PIPELINE);

    /* Step 2: Configure the content stream */
    /* Pipeline. */
    DPU_InitPipeline(APP_DPU, APP_CONTENT_STREAM_PIPELINE);

    /* ExtDst. */
    DPU_InitExtDst(APP_DPU, APP_CONTENT_STREAM_EXTDST, DPU_MAKE_SRC_REG1(kDPU_UnitSrcLayerBlend0));

    /* Layer Blend. */
    DPU_InitLayerBlend(APP_DPU, kDPU_LayerBlend0,
                       DPU_MAKE_SRC_REG2(kDPU_UnitSrcConstFrame0, APP_LAYERBLEND_SECOND_SRC));
    DPU_LayerBlendGetDefaultConfig(&lbConfig);
    DPU_SetLayerBlendConfig(APP_DPU, kDPU_LayerBlend0, &lbConfig);
    DPU_EnableLayerBlend(APP_DPU, kDPU_LayerBlend0, true);

    /* Const frame. */
    cfConfig.frameWidth  = APP_FRAME_WIDTH;
    cfConfig.frameHeight = APP_FRAME_HEIGHT;
    cfConfig.constColor  = DPU_MAKE_CONST_COLOR(0, 0, 0, 0);
    DPU_InitConstFrame(APP_DPU, kDPU_ConstFrame0);
    DPU_SetConstFrameConfig(APP_DPU, kDPU_ConstFrame0, &cfConfig);

#if APP_RESIZE_CAMERA_IMAGE
    /* Scaler */
    DPU_ScalerGetDefaultConfig(&scConfig);

    DPU_InitScaler(APP_DPU, kDPU_Hscaler4);
    scConfig.srcReg     = DPU_MAKE_SRC_REG1(APP_HSCALER_SRC);
    scConfig.inputSize  = APP_CAMERA_WIDTH;
    scConfig.outputSize = APP_FRAME_WIDTH;
    DPU_SetScalerConfig(APP_DPU, kDPU_Hscaler4, &scConfig);

    DPU_InitScaler(APP_DPU, kDPU_Vscaler4);
    scConfig.srcReg     = DPU_MAKE_SRC_REG1(APP_VSCALER_SRC);
    scConfig.inputSize  = APP_CAMERA_HEIGHT;
    scConfig.outputSize = APP_FRAME_HEIGHT;
    DPU_SetScalerConfig(APP_DPU, kDPU_Vscaler4, &scConfig);
#endif /* APP_RESIZE_CAMERA_IMAGE */

    /*
     * Fetch unit.
     */
    DPU_FetchUnitGetDefaultConfig(&fetchConfig);
#if APP_RESIZE_CAMERA_IMAGE
    fetchConfig.frameHeight = APP_CAMERA_HEIGHT;
    fetchConfig.frameWidth  = APP_CAMERA_WIDTH;
#else
    fetchConfig.frameHeight = APP_FRAME_HEIGHT;
    fetchConfig.frameWidth  = APP_FRAME_WIDTH;
#endif
    DPU_InitFetchUnit(APP_DPU, kDPU_FetchDecode0, &fetchConfig);

    /* Fetch unit source buffer configure. */
    DPU_SrcBufferGetDefaultConfig(&sbConfig);

    sbConfig.bitsPerPixel = 16;
    sbConfig.pixelFormat  = kDPU_PixelFormatRGB565;
    sbConfig.constColor   = DPU_MAKE_CONST_COLOR(0, 0, 0, 0);

    /* Sublayer 0. */
    sbConfig.strideBytes  = 2 * APP_CAMERA_WIDTH;
    sbConfig.bufferHeight = APP_CAMERA_HEIGHT;
    sbConfig.bufferWidth  = APP_CAMERA_WIDTH;
    sbConfig.baseAddr     = frameBuffer;
    DPU_SetFetchUnitSrcBufferConfig(APP_DPU, kDPU_FetchDecode0, 0, &sbConfig);
    DPU_EnableFetchUnitSrcBuffer(APP_DPU, kDPU_FetchDecode0, 0, true);

#if (defined(APP_DPU_USE_PREFETCH) && APP_DPU_USE_PREFETCH)
    /* Configure PRG. */
    PRG_BufferGetDefaultConfig(&prgConfig);
    prgConfig.width       = sbConfig.bufferWidth;
    prgConfig.height      = sbConfig.bufferHeight;
    prgConfig.strideBytes = sbConfig.strideBytes;
    prgConfig.dataType    = kPRG_DataType16Bpp;

    PRG_Init(APP_FETCH_DECODE0_PRG);
    PRG_SetBufferConfig(APP_FETCH_DECODE0_PRG, &prgConfig);
    PRG_SetBufferAddr(APP_FETCH_DECODE0_PRG, sbConfig.baseAddr);
    PRG_Enable(APP_FETCH_DECODE0_PRG, true);
    PRG_UpdateRegister(APP_FETCH_DECODE0_PRG);

    /* Configure DPR. */
    DPR_BufferGetDefaultConfig(&dprConfig);
    dprConfig.width       = sbConfig.bufferWidth;
    dprConfig.height      = sbConfig.bufferHeight;
    dprConfig.strideBytes = sbConfig.strideBytes;
    dprConfig.dataType    = kDPR_DataType16Bpp;

    DPR_Init(APP_FETCH_DECODE0_DPR);
    DPR_SetBufferConfig(APP_FETCH_DECODE0_DPR, &dprConfig);
    DPR_SetBufferAddr(APP_FETCH_DECODE0_DPR, sbConfig.baseAddr);
    DPR_Start(APP_FETCH_DECODE0_DPR);
#endif

    DPU_TriggerPipelineShadowLoad(APP_DPU, APP_CONTENT_STREAM_PIPELINE);

    /* Step 3: Configure the display stream. */
    DPU_DisplayTimingGetDefaultConfig(&displayTimingConfig);

    displayTimingConfig.flags  = APP_DPU_TIMING_FLAGS;
    displayTimingConfig.width  = APP_FRAME_WIDTH;
    displayTimingConfig.hsw    = APP_HSW;
    displayTimingConfig.hfp    = APP_HFP;
    displayTimingConfig.hbp    = APP_HBP;
    displayTimingConfig.height = APP_FRAME_HEIGHT;
    displayTimingConfig.vsw    = APP_VSW;
    displayTimingConfig.vfp    = APP_VFP;
    displayTimingConfig.vbp    = APP_VBP;

    DPU_InitDisplayTiming(APP_DPU, APP_DPU_DISPLAY_INDEX, &displayTimingConfig);

    DPU_DisplayGetDefaultConfig(&displayConfig);

    /* Only show the content stream in normal mode. */
    displayConfig.displayMode = kDPU_DisplayOnlySec;
    /* Show the test pattern in panic mode. */
    displayConfig.displayModeInPanic = kDPU_DisplayTest;

    displayConfig.secAreaStartX = 1;
    displayConfig.secAreaStartY = 1;

    DPU_SetDisplayConfig(APP_DPU, APP_DPU_DISPLAY_INDEX, &displayConfig);

    DPU_TriggerDisplayShadowLoad(APP_DPU, APP_DPU_DISPLAY_INDEX);

    /*
     * Initialize workflow:
     * 1. Init DPU
     * 2. Configure pixel link.
     * 3. Init and start display interface.
     * 4. Start DPU
     */
    APP_InitPixelLink();

    APP_StartDisplayInterface();

    DPU_StartDisplay(APP_DPU, APP_DPU_DISPLAY_INDEX);

#if (defined(APP_DPU_USE_PREFETCH) && APP_DPU_USE_PREFETCH)
    PRG_EnableShadowLoad(APP_FETCH_DECODE0_PRG, true);
    PRG_UpdateRegister(APP_FETCH_DECODE0_PRG);
    DPR_StartRepeat(APP_FETCH_DECODE0_DPR);
#endif

    /* Wait for the initial setting shadow load finished. */
    while (1)
    {
        if ((APP_CONTENT_STREAM_INT_GROUP0 & DPU_GetInterruptsPendingFlags(APP_DPU, 0)) ||
            (APP_CONTENT_STREAM_INT_GROUP1 & DPU_GetInterruptsPendingFlags(APP_DPU, 1)))
        {
            break;
        }
    }

    DPU_ClearInterruptsPendingFlags(APP_DPU, 0, APP_CONTENT_STREAM_INT_GROUP0);
    DPU_ClearInterruptsPendingFlags(APP_DPU, 1, APP_CONTENT_STREAM_INT_GROUP1);

    s_displayHandle.callback       = callback;
    s_displayHandle.activeFb       = frameBuffer;
    s_displayHandle.isFramePending = false;

    DPU_EnableInterrupts(APP_DPU, 0, APP_CONTENT_STREAM_INT_GROUP0);
    DPU_EnableInterrupts(APP_DPU, 1, APP_CONTENT_STREAM_INT_GROUP1);
}

void APP_SetDisplayFrameBuffer(uint32_t frameBuffer)
{
#if (defined(APP_DPU_USE_PREFETCH) && APP_DPU_USE_PREFETCH)
    DPR_SetBufferAddr(APP_FETCH_DECODE0_DPR, frameBuffer);
    PRG_SetBufferAddr(APP_FETCH_DECODE0_PRG, frameBuffer);
    PRG_UpdateRegister(APP_FETCH_DECODE0_PRG);
#endif

    DPU_SetFetchUnitSrcBufferAddr(APP_DPU, kDPU_FetchDecode0, 0, frameBuffer);
    s_displayHandle.isFramePending = true;
    s_displayHandle.inactiveFb     = frameBuffer;
    DPU_TriggerPipelineShadowLoad(APP_DPU, APP_CONTENT_STREAM_PIPELINE);
}

bool APP_IsDisplayFramePending(void)
{
    return s_displayHandle.isFramePending;
}

void APP_DisplayIRQHandler(void)
{
    uint32_t intGroup0Flags, intGroup1Flags;
    uint32_t oldActiveFb;
    intGroup0Flags = DPU_GetInterruptsPendingFlags(APP_DPU, 0);
    intGroup1Flags = DPU_GetInterruptsPendingFlags(APP_DPU, 1);

    DPU_ClearInterruptsPendingFlags(APP_DPU, 0, intGroup0Flags);
    DPU_ClearInterruptsPendingFlags(APP_DPU, 1, intGroup1Flags);

    if ((intGroup0Flags & APP_CONTENT_STREAM_INT_GROUP0) || (intGroup1Flags & APP_CONTENT_STREAM_INT_GROUP1))
    {
        s_displayHandle.isFramePending = false;

        oldActiveFb = s_displayHandle.activeFb;

        if (s_displayHandle.callback)
        {
            s_displayHandle.activeFb = s_displayHandle.inactiveFb;
            s_displayHandle.callback(oldActiveFb);
        }
    }
    __DSB();
}

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
        .pixelPayloadSize = APP_FRAME_WIDTH,
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
        .panelHeight    = APP_FRAME_HEIGHT,
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

    APP_InitLcdPanel();

    SOC_ResetMipiDsi(APP_MIPI_DSI, kMIPI_DsiDpi, 1);
}

void APP_StopDisplayInterface(void)
{
    SOC_ResetMipiDsi(APP_MIPI_DSI, kMIPI_DsiDpi, 0);
    APP_DeinitLcdPanel();
    SOC_ResetMipiDsi(APP_MIPI_DSI, kMIPI_DsiEsc, 0);
    SOC_ResetMipiDsi(APP_MIPI_DSI, kMIPI_DsiPhy, 0);

    DSI_DeinitDphy(APP_MIPI_DSI);
    DSI_Deinit(APP_MIPI_DSI);
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
        .outputBus = kLDB_OutputRGB888_7Bit_JEIDA,
        .inputFlag = kLDB_InputVsyncActiveLow | kLDB_InputHsyncActiveLow | kLDB_InputDataLatchOnRisingEdge,
        .pixelClock_Hz = displayPixelClkFreq_Hz,
    };

    LDB_Init(APP_LDB);

    APP_InitLcdPanel();

    LDB_InitChannel(APP_LDB, APP_LDB_CH, &ldbConfig);
}

void APP_StopDisplayInterface(void)
{
    LDB_DeinitChannel(APP_LDB, APP_LDB_CH);
    APP_DeinitLcdPanel();
    LDB_Deinit(APP_LDB);
}

#else /* DPU_EXAMPLE_DI == DPU_DI_MIPI */
#error Unsupported display interface
#endif /* DPU_EXAMPLE_DI == DPU_DI_MIPI */

void APP_InitCameraInterface(void)
{
    BOARD_InitCameraInterface();
}

void APP_DeinitCameraInterface(void)
{
    BOARD_DeinitCameraInterface();
}

void APP_PrepareCamera(void)
{
    BOARD_PrepareCamera();
}

void APP_UnprepareCamera(void)
{
    BOARD_UnprepareCamera();
}

void APP_SetIsiPermission(uint64_t startAddr, uint64_t endAddr)
{
    SOC_SetIsiPermission(startAddr, endAddr);
}

void APP_UnsetIsiPermission(void)
{
    SOC_UnsetIsiPermission();
}

void APP_PrepareDisplay(void)
{
    BOARD_PrepareDisplay();
}

void APP_UnprepareDisplay(void)
{
    BOARD_UnprepareDisplay();
}

void APP_InitLcdPanel(void)
{
    BOARD_InitLcdPanel();
}

void APP_DeinitLcdPanel(void)
{
    BOARD_DeinitLcdPanel();
}
