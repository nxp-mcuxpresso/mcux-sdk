/*
 * Copyright 2017-2018 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _ISI_EXAMPLE_H_
#define _ISI_EXAMPLE_H_

/*******************************************************************************
 * Configuration
 ******************************************************************************/
/* Use DPU prefetch. */
#define APP_DPU_USE_PREFETCH 1

/* Display interface type. */
#define DPU_DI_MIPI 0
#define DPU_DI_LVDS 1

/* Camera interface. */
#define ISI_MIPI_CSI2 0
#define ISI_CI_PI     1

#define CAMERA_DEVICE_OV5640  0
#define CAMERA_DEVICE_MAX9286 1

/* Configuration for DPU. */
#define APP_DPU_BASE DC__IRIS_MVPL_BASE
#define APP_DPU      ((IRIS_MVPL_Type *)APP_DPU_BASE)
#define APP_DPU_TIMING_FLAGS                                                                      \
    (kDPU_DisplayHsyncActiveLow | kDPU_DisplayVsyncActiveLow | kDPU_DisplayDataEnableActiveHigh | \
     kDPU_DisplayPixelActiveHigh)

#if !APP_DISPLAY_EXTERNAL_CONVERTOR
#define APP_FRAME_HEIGHT 1920
#define APP_FRAME_WIDTH  1080
#define APP_HFP          8
#define APP_HBP          8
#define APP_HSW          4
#define APP_VFP          7
#define APP_VBP          7
#define APP_VSW          2

/* Pixel clock = ((APP_HFP + APP_HBP + APP_HSW) * (APP_VFP + APP_VBP + APP_VSW)) * frame rate */
#define APP_PIXEL_CLOCK_HZ (108000000) /* 108MHz. */

#else

#define APP_FRAME_HEIGHT   1080
#define APP_FRAME_WIDTH    1920
#define APP_HFP            88
#define APP_HBP            148
#define APP_HSW            44
#define APP_VFP            4
#define APP_VBP            36
#define APP_VSW            5

/* Pixel clock = ((APP_HFP + APP_HBP + APP_HSW) * (APP_VFP + APP_VBP + APP_VSW)) * frame rate */
#define APP_PIXEL_CLOCK_HZ 148500000 /* 148.5 MHz. */
#endif

/*
 * The frame buffer alignment. The ISI has an overflow issue, ISI uses VSYNC to
 * switch output buffer, but if the input frame VSYNC is missed because of noise
 * or camera and ISI not synchronized, the ISI will not switch output buffer,
 * it continue saving the input data in the previous buffer and overflow happens.
 * To protect the other data from overwritten by ISI, XRDC is used to limit
 * ISI write permission to the frame buffer region. XRDC memory region should be
 * 4K byte aligned.
 */
#define APP_FB_ALIGN_BYTE 4096

#if defined(APP_DPU_USE_PREFETCH) && APP_DPU_USE_PREFETCH
#include "fsl_dpu.h"
#define APP_FB_STRIDE_ALIGN_BYTE DPU_FETCH_UNIT_BURST_SIZE
#endif

/* Configuration for display interface. */
#if DPU_EXAMPLE_DI == DPU_DI_MIPI
#define APP_MIPI_DSI_BASE     DI_MIPI_DSI_LVDS_0__MIPI_DSI_HOST_BASE
#define APP_MIPI_DSI          ((MIPI_DSI_HOST_Type *)APP_MIPI_DSI_BASE)
#define APP_MIPI_DSI_LANE_NUM 4 /* Lane number. */
#if (APP_MIPI_DSI_BASE == DI_MIPI_DSI_LVDS_0__MIPI_DSI_HOST_BASE)
#define APP_DPU_DISPLAY_INDEX 0
#else
#define APP_DPU_DISPLAY_INDEX 1
#endif
#elif DPU_EXAMPLE_DI == DPU_DI_LVDS
#define APP_LDB_BASE MIPI_DSI_LVDS_COMBO0_CSR_BASE
#define APP_LDB      ((LDB_Type *)APP_LDB_BASE)
#define APP_LDB_CH   0
#if (APP_LDB_BASE == MIPI_DSI_LVDS_COMBO0_CSR_BASE)
#define APP_DPU_DISPLAY_INDEX 0
#else
#define APP_DPU_DISPLAY_INDEX 1
#endif
#endif

/* Configuration for MIPI CSI2 */
#if ISI_EXAMPLE_CI == ISI_MIPI_CSI2
#define APP_MIPI_CSI2_BASE MIPI_CSI__MIPI_CSI2RX_BASE
#define APP_MIPI_CSI2      ((MIPI_CSI2RX_Type *)APP_MIPI_CSI2_BASE)
#if (CAMERA_DEVICE == CAMERA_DEVICE_OV5640)
#define APP_MIPI_CSI_VC    0
#define APP_MIPI_CSI_LANES 2
#elif (CAMERA_DEVICE == CAMERA_DEVICE_MAX9286)
#define APP_MIPI_CSI_VC    0
#define APP_MIPI_CSI_LANES 4
#endif /* CAMERA_DEVICE */
#endif

/* Configuration for CI_PI */
#if ISI_EXAMPLE_CI == ISI_CI_PI
#define APP_CI_PI_BASE CI_PI_CSR_BASE
#define APP_CI_PI      ((CI_PI_CSR_Type *)APP_CI_PI_BASE)

#define CI_PI_MODE_CCIR656        0
#define CI_PI_MODE_GATE_CLOCK     1
#define CI_PI_MODE_NON_GATE_CLOCK 2

#define APP_CI_PI_MODE CI_PI_MODE_CCIR656

#endif

/* Configuration for camera. */
#if ISI_EXAMPLE_CI == ISI_MIPI_CSI2
#define APP_CAMERA_CONTROL_FLAGS 0
#define APP_CAMERA_FRAME_RATE    30
#elif (ISI_EXAMPLE_CI == ISI_CI_PI)
#define APP_CAMERA_CONTROL_FLAGS (kCAMERA_VsyncActiveLow | kCAMERA_HrefActiveLow | kCAMERA_DataLatchOnFallingEdge)
#define APP_CAMERA_FRAME_RATE    15
#endif
#if (CAMERA_DEVICE == CAMERA_DEVICE_OV5640)
#define APP_CAMERA_HEIGHT 1080
#define APP_CAMERA_WIDTH  1920
#elif (CAMERA_DEVICE == CAMERA_DEVICE_MAX9286)
#define APP_CAMERA_HEIGHT 800
#define APP_CAMERA_WIDTH  1280
#endif
#define APP_ISI_BASE IMAGING__ISI0_BASE
#define APP_ISI      ((ISI_Type *)APP_ISI_BASE)

#if (APP_ISI_BASE == IMAGING__ISI0_BASE)
#define ISI_RSRC           SC_R_ISI_CH0
#define APP_ISI_IRQn       IMAGING_PDMA_STREAM0_INT_IRQn
#define APP_ISI_IRQHandler IMAGING_PDMA_STREAM0_INT_IRQHandler
#elif (APP_ISI_BASE == IMAGING__ISI1_BASE)
#define ISI_RSRC           SC_R_ISI_CH1
#define APP_ISI_IRQn       IMAGING_PDMA_STREAM1_INT_IRQn
#define APP_ISI_IRQHandler IMAGING_PDMA_STREAM1_INT_IRQHandler
#elif (APP_ISI_BASE == IMAGING__ISI2_BASE)
#define ISI_RSRC           SC_R_ISI_CH2
#define APP_ISI_IRQn       IMAGING_PDMA_STREAM2_INT_IRQn
#define APP_ISI_IRQHandler IMAGING_PDMA_STREAM2_INT_IRQHandler
#elif (APP_ISI_BASE == IMAGING__ISI3_BASE)
#define ISI_RSRC           SC_R_ISI_CH3
#define APP_ISI_IRQn       IMAGING_PDMA_STREAM3_INT_IRQn
#define APP_ISI_IRQHandler IMAGING_PDMA_STREAM3_INT_IRQHandler
#elif (APP_ISI_BASE == IMAGING__ISI4_BASE)
#define ISI_RSRC           SC_R_ISI_CH4
#define APP_ISI_IRQn       IMAGING_PDMA_STREAM4_INT_IRQn
#define APP_ISI_IRQHandler IMAGING_PDMA_STREAM4_INT_IRQHandler
#elif (APP_ISI_BASE == IMAGING__ISI5_BASE)
#define ISI_RSRC           SC_R_ISI_CH5
#define APP_ISI_IRQn       IMAGING_PDMA_STREAM5_INT_IRQn
#define APP_ISI_IRQHandler IMAGING_PDMA_STREAM5_INT_IRQHandler
#elif (APP_ISI_BASE == IMAGING__ISI6_BASE)
#define ISI_RSRC           SC_R_ISI_CH6
#define APP_ISI_IRQn       IMAGING_PDMA_STREAM6_INT_IRQn
#define APP_ISI_IRQHandler IMAGING_PDMA_STREAM6_INT_IRQHandler
#else
#define ISI_RSRC           SC_R_ISI_CH7
#define APP_ISI_IRQn       IMAGING_PDMA_STREAM7_INT_IRQn
#define APP_ISI_IRQHandler IMAGING_PDMA_STREAM7_INT_IRQHandler
#endif

#define APP_RESIZE_CAMERA_IMAGE 1

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

#define APP_FETCH_DECODE9_PRG DC__PRG0
#define APP_FETCH_WARP9_PRG   DC__PRG1
#define APP_FETCH_LAYER0_PRG  DC__PRG2
#define APP_FETCH_DECODE0_PRG DC__PRG3
#define APP_FETCH_ECO0_PRG    DC__PRG4
#define APP_FETCH_DECODE1_PRG DC__PRG5
#define APP_FETCH_ECO1_PRG    DC__PRG6
#define APP_FETCH_WARP2_PRG   DC__PRG7
#define APP_FETCH_ECO2_PRG    DC__PRG8

#define APP_FETCH_DECODE9_DPR DC__DPR0_CH0
#define APP_FETCH_WARP9_DPR   DC__DPR0_CH1
#define APP_FETCH_LAYER0_DPR  DC__DPR0_CH2
#define APP_FETCH_DECODE0_DPR DC__DPR1_CH0
#define APP_FETCH_ECO0_DPR    DC__DPR1_CH0
#define APP_FETCH_DECODE1_DPR DC__DPR1_CH1
#define APP_FETCH_ECO1_DPR    DC__DPR1_CH1
#define APP_FETCH_WARP2_DPR   DC__DPR1_CH2
#define APP_FETCH_ECO2_DPR    DC__DPR1_CH2

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
/* Unprepare the display */
extern void BOARD_UnprepareDisplay(void);
/* Init the LCD panel. */
extern void BOARD_InitLcdPanel(void);
/* Deinit the LCD panel. */
extern void BOARD_DeinitLcdPanel(void);
/* Prepare the camera, such as enable camera module clock and interrupts. */
extern void BOARD_PrepareCamera(void);
/* UnPrepare the camera */
extern void BOARD_UnprepareCamera(void);
/* Init Camera Interaface */
extern void BOARD_InitCameraInterface(void);
/* Deinit Camera Interaface */
extern void BOARD_DeinitCameraInterface(void);
/* Init pixel link. */
extern void APP_InitPixelLink(void);
/* Set the ISI access permission to frame buffer. */
extern void SOC_SetIsiPermission(uint64_t startAddr, uint64_t endAddr);
/* Unset the ISI access permission to frame buffer. */
extern void SOC_UnsetIsiPermission(void);
#if DPU_EXAMPLE_DI == DPU_DI_MIPI
extern void SOC_ResetMipiDsi(MIPI_DSI_HOST_Type *base, mipi_dsi_part_t part, uint32_t reset);
#endif

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

#endif /* _ISI_EXAMPLE_H_ */
