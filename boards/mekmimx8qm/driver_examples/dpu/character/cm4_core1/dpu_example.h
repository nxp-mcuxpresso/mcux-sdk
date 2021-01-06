/*
 * Copyright 2018, 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _DPU_EXAMPLE_H_
#define _DPU_EXAMPLE_H_

/*******************************************************************************
 * Configuration
 ******************************************************************************/
/* Use DPU prefetch. */
#define APP_DPU_USE_PREFETCH 1

#define DPU_DI_MIPI 0
#define DPU_DI_LVDS 1

/* Whether use external convertor such as MIPI2HDMI convertor (ADV7535) */
#ifndef APP_DISPLAY_EXTERNAL_CONVERTOR
#define APP_DISPLAY_EXTERNAL_CONVERTOR 0
#endif

/* Use the MIPI DSI interface. */
#define DPU_EXAMPLE_DI DPU_DI_MIPI

/* Configuration for DPU. */
#define APP_DPU_BASE DC_0__IRIS_MVPL_BASE
#define APP_DPU      ((IRIS_MVPL_Type *)APP_DPU_BASE)
#define APP_DPU_TIMING_FLAGS                                                                      \
    (kDPU_DisplayHsyncActiveLow | kDPU_DisplayVsyncActiveLow | kDPU_DisplayDataEnableActiveHigh | \
     kDPU_DisplayPixelActiveHigh)

#if (DPU_EXAMPLE_DI == DPU_DI_LVDS)
#define APP_DPU_DISPLAY_INDEX 1
#elif DPU_EXAMPLE_DI == DPU_DI_MIPI
#define APP_DPU_DISPLAY_INDEX 0
#endif

#if !APP_DISPLAY_EXTERNAL_CONVERTOR
#define APP_PANEL_HEIGHT 1920
#define APP_PANEL_WIDTH  1080
#define APP_HFP          8
#define APP_HBP          8
#define APP_HSW          4
#define APP_VFP          7
#define APP_VBP          7
#define APP_VSW          2

/* Pixel clock = ((APP_HFP + APP_HBP + APP_HSW) * (APP_VFP + APP_VBP + APP_VSW)) * frame rate */
#define APP_PIXEL_CLOCK_HZ (108000000) /* 108MHz. */

#else

#define APP_PANEL_HEIGHT   1080
#define APP_PANEL_WIDTH    1920
#define APP_HFP            88
#define APP_HBP            148
#define APP_HSW            44
#define APP_VFP            4
#define APP_VBP            36
#define APP_VSW            5

/* Pixel clock = ((APP_HFP + APP_HBP + APP_HSW) * (APP_VFP + APP_VBP + APP_VSW)) * frame rate */
#define APP_PIXEL_CLOCK_HZ 148500000 /* 148.5 MHz. */
#endif

/* Configuration for display interface. */
#if DPU_EXAMPLE_DI == DPU_DI_MIPI
#define APP_MIPI_DSI_BASE     MIPI_DSI_HOST0_BASE
#define APP_MIPI_DSI          ((MIPI_DSI_HOST_Type *)APP_MIPI_DSI_BASE)
#define APP_MIPI_DSI_LANE_NUM 4 /* Lane number. */
#elif DPU_EXAMPLE_DI == DPU_DI_LVDS
#define APP_LDB_BASE DI_LVDS_0__LDB_BASE
#define APP_LDB      ((LDB_Type *)APP_LDB_BASE)
#define APP_LDB_CH   0
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#if (0 == APP_DPU_DISPLAY_INDEX)
#define APP_CONTENT_STREAM_PIPELINE   kDPU_PipelineExtDst0
#define APP_CONTENT_STREAM_EXTDST     kDPU_ExtDst0
#define APP_CONTENT_STREAM_INT_GROUP0 kDPU_Group0ExtDst0ShadowLoadInterrupt
#define APP_CONTENT_STREAM_INT_GROUP1 0U
#define APP_SAFETY_STREAM_PIPELINE    kDPU_PipelineExtDst4
#define APP_SAFETY_STREAM_EXTDST      kDPU_ExtDst4
#define APP_SAFETY_STREAM_INT_GROUP0  kDPU_Group0ExtDst4ShadowLoadInterrupt
#define APP_SAFETY_STREAM_INT_GROUP1  0U
#define APP_SIG_SHD_LD_INT_GROUP0     kDPU_Group0Sig0ShadowLoadInterrupt
#define APP_SIG_SHD_LD_INT_GROUP1     0U
#define APP_DISPLAY_STREAM_INT_GROUP0 kDPU_Group0Display0ShadowLoadInterrupt
#define APP_DISPLAY_STREAM_INT_GROUP1 0U
#else
#define APP_CONTENT_STREAM_PIPELINE   kDPU_PipelineExtDst1
#define APP_CONTENT_STREAM_EXTDST     kDPU_ExtDst1
#define APP_CONTENT_STREAM_INT_GROUP0 kDPU_Group0ExtDst1ShadowLoadInterrupt
#define APP_CONTENT_STREAM_INT_GROUP1 0U
#define APP_SAFETY_STREAM_PIPELINE    kDPU_PipelineExtDst5
#define APP_SAFETY_STREAM_EXTDST      kDPU_ExtDst5
#define APP_SAFETY_STREAM_INT_GROUP0  kDPU_Group0ExtDst5ShadowLoadInterrupt
#define APP_SAFETY_STREAM_INT_GROUP1  0U
#define APP_SIG_SHD_LD_INT_GROUP0     0U
#define APP_SIG_SHD_LD_INT_GROUP1     kDPU_Group1Sig1ShadowLoadInterrupt
#define APP_DISPLAY_STREAM_INT_GROUP0 kDPU_Group0Display1ShadowLoadInterrupt
#define APP_DISPLAY_STREAM_INT_GROUP1 0U
#endif

#define APP_BLIT_SHD_LD_INT_GROUP0 kDPU_Group0Store9ShadowLoadInterrupt
#define APP_BLIT_SHD_LD_INT_GROUP1 0U
#define APP_BLIT_SEQ_INT_GROUP0    kDPU_Group0Store9SeqCompleteInterrupt
#define APP_BLIT_SEQ_INT_GROUP1    0U
#define APP_BLIT_COM_INT_GROUP0    kDPU_Group0Store9FrameCompleteInterrupt
#define APP_BLIT_COM_INT_GROUP1    0U

#if (APP_DPU_BASE == DC_1__IRIS_MVPL_BASE)

#define APP_FETCH_DECODE9_PRG DC_1__PRG0
#define APP_FETCH_WARP9_PRG   DC_1__PRG1
#define APP_FETCH_LAYER0_PRG  DC_1__PRG2
#define APP_FETCH_DECODE0_PRG DC_1__PRG3
#define APP_FETCH_ECO0_PRG    DC_1__PRG4
#define APP_FETCH_DECODE1_PRG DC_1__PRG5
#define APP_FETCH_ECO1_PRG    DC_1__PRG6
#define APP_FETCH_WARP2_PRG   DC_1__PRG7
#define APP_FETCH_ECO2_PRG    DC_1__PRG8

#define APP_FETCH_DECODE9_DPR DC_1__DPR0_CH0
#define APP_FETCH_WARP9_DPR   DC_1__DPR0_CH1
#define APP_FETCH_LAYER0_DPR  DC_1__DPR0_CH2
#define APP_FETCH_DECODE0_DPR DC_1__DPR1_CH0
#define APP_FETCH_ECO0_DPR    DC_1__DPR1_CH0
#define APP_FETCH_DECODE1_DPR DC_1__DPR1_CH1
#define APP_FETCH_ECO1_DPR    DC_1__DPR1_CH1
#define APP_FETCH_WARP2_DPR   DC_1__DPR1_CH2
#define APP_FETCH_ECO2_DPR    DC_1__DPR1_CH2

#else /* APP_DPU_BASE */

#define APP_FETCH_DECODE9_PRG DC_0__PRG0
#define APP_FETCH_WARP9_PRG   DC_0__PRG1
#define APP_FETCH_LAYER0_PRG  DC_0__PRG2
#define APP_FETCH_DECODE0_PRG DC_0__PRG3
#define APP_FETCH_ECO0_PRG    DC_0__PRG4
#define APP_FETCH_DECODE1_PRG DC_0__PRG5
#define APP_FETCH_ECO1_PRG    DC_0__PRG6
#define APP_FETCH_WARP2_PRG   DC_0__PRG7
#define APP_FETCH_ECO2_PRG    DC_0__PRG8

#define APP_FETCH_DECODE9_DPR DC_0__DPR0_CH0
#define APP_FETCH_WARP9_DPR   DC_0__DPR0_CH1
#define APP_FETCH_LAYER0_DPR  DC_0__DPR0_CH2
#define APP_FETCH_DECODE0_DPR DC_0__DPR1_CH0
#define APP_FETCH_ECO0_DPR    DC_0__DPR1_CH0
#define APP_FETCH_DECODE1_DPR DC_0__DPR1_CH1
#define APP_FETCH_ECO1_DPR    DC_0__DPR1_CH1
#define APP_FETCH_WARP2_DPR   DC_0__DPR1_CH2
#define APP_FETCH_ECO2_DPR    DC_0__DPR1_CH2

#endif /* APP_DPU_BASE */

#if DPU_EXAMPLE_DI == DPU_DI_MIPI
extern uint32_t mipiDsiTxEscClkFreq_Hz;
extern uint32_t mipiDsiRxEscClkFreq_Hz;
extern uint32_t mipiDsiDphyRefClkFreq_Hz;
extern uint32_t mipiDsiDphyBitClkFreq_Hz;
extern uint32_t mipiDsiDpiClkFreq_Hz;

typedef enum _mipi_dsi_part
{
    /* Don't change the value of these items. */
    kMIPI_DsiDpi = 0,
    kMIPI_DsiEsc = 1,
    kMIPI_DsiPhy = 2,
} mipi_dsi_part_t;

#elif DPU_EXAMPLE_DI == DPU_DI_LVDS
extern uint32_t displayPixelClkFreq_Hz;
#endif

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/* Prepare the display, such as enable display module clock and interrupts. */
extern void BOARD_PrepareDisplay(void);
/* Init the LCD panel. */
extern void BOARD_InitLcdPanel(void);
/* Init and start the display interface, such as MIPI. */
extern void APP_StartDisplayInterface(void);
/* Init pixel link. */
extern void APP_InitPixelLink(void);
#if DPU_EXAMPLE_DI == DPU_DI_MIPI
extern void SOC_ResetMipiDsi(MIPI_DSI_HOST_Type *base, mipi_dsi_part_t part, uint32_t reset);
#endif

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

#endif /* _DPU_EXAMPLE_H_ */
