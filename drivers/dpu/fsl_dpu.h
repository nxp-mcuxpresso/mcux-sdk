/*
 * Copyright 2017, 2019-2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_DPU_H_
#define _FSL_DPU_H_

#include "fsl_common.h"

/*!
 * @addtogroup dpu
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief Driver version. */
#define FSL_DPU_DRIVER_VERSION (MAKE_VERSION(2, 1, 1))
/*@}*/

/*! @brief DPU palette entery number. */
#define DPU_PALETTE_ENTRY_NUM (256U)

/*! @brief DPU fetch unit burst length, should be less than 16. */
#ifndef DPU_FETCH_UNIT_BURST_LENGTH
#define DPU_FETCH_UNIT_BURST_LENGTH (16U)
#endif

/*! @brief DPU fetch unit burst size.
 *
 * If prefetch is used, the frame buffer stride and base address should be
 * aligned to the burst size.
 */
#define DPU_FETCH_UNIT_BURST_SIZE (8U * DPU_FETCH_UNIT_BURST_LENGTH)

#define DPU_USE_GENERATE_HEADER 0

/*!
 * @name Macros for the DPU unit input source.
 *
 * The DPU unit input source is controlled by the register pixencfg_\<unit\>_dynamic,
 * the macros @ref DPU_MAKE_SRC_REG1, @ref DPU_MAKE_SRC_REG2, and @ref DPU_MAKE_SRC_REG3
 * are used to define the register value of pixencfg_\<unit\>_dynamic. @ref DPU_MAKE_SRC_REG1
 * defines register for DPU unit that has one input source. Accordingly,
 * @ref DPU_MAKE_SRC_REG2 and @ref DPU_MAKE_SRC_REG3 are used to define the register for
 * units that have two and three input source. See @ref _dpu_unit_source for the
 * input source details.
 * @{
 */
/*! Macro for one input source unit. */
#define DPU_MAKE_SRC_REG1(src) (((uint32_t)(src)) & 0x3FU)
/*! Macro for two input source unit. */
#define DPU_MAKE_SRC_REG2(primSrc, secSrc) \
    ((((uint32_t)(primSrc)) & 0x3FU) | (((((uint32_t)(secSrc)) & 0x3FU) << 0x8U)))
/*! Macro for three input source unit. */
#define DPU_MAKE_SRC_REG3(primSrc, secSrc, tertSrc)                               \
    ((((uint32_t)(primSrc)) & 0x3FU) | ((((uint32_t)(secSrc)) & 0x3FU) << 0x8U) | \
     (((((uint32_t)(tertSrc)) & 0x3FU) << 0x10U)))
/*!@}*/

/*! @brief Define the const value that write to \<unit\>_ConstantColor. */
#define DPU_MAKE_CONST_COLOR(red, green, blue, alpha) \
    ((((uint32_t)(red)) << 24U) | (((uint32_t)(green)) << 16U) | (((uint32_t)(blue)) << 8U) | ((uint32_t)(alpha)))

/*!
 * @name Macros define the FrameGen interrupt mode.
 *
 * These macros are used by the function @ref DPU_SetFrameGenInterruptConfig
 * to set the FrameGen interrupt mode.
 * @{
 */
/*! Disable FrameGen interrupt. */
#define DPU_FRAME_GEN_INT_DISABLE 0U
/*! Generate FrameGen interrupt every line at the colnum @p colNum. */
#define DPU_FRAME_GEN_INT_PER_LINE(colNum) ((1U << 31U) | (1U << 15U) | (((uint32_t)colNum) & (0x3FFFU)))
/*! Generate FrameGen interrupt every frame at the row @p rowNum. */
#define DPU_FRAME_GEN_INT_PER_FRAME(rowNum) ((1U << 31U) | (((uint32_t)rowNum) & 0x3FFF0000U))
/*!@}*/

/*
 * Macros to define the DPU unit, these are internal macros and should not be
 * used by upper layer.
 *
 * type: Type of the unit, see _dpu_unit_type.
 * attr: Unit attribute, OR'ed value of _dpu_unit_attr.
 * offset: Control block register offset in DPU memory map.
 */
#define DPU_UNIT_TYPE_SHIFT   (24U)
#define DPU_UNIT_TYPE_MASK    (0xFF000000U)
#define DPU_UNIT_ATTR_SHIFT   (20U)
#define DPU_UNIT_ATTR_MASK    (0x00F00000U)
#define DPU_UNIT_OFFSET_SHIFT (0U)
#define DPU_UNIT_OFFSET_MASK  (0x0001FFFFU)

#define DPU_MAKE_UNIT_TYPE(type)     (((uint32_t)(type)) << DPU_UNIT_TYPE_SHIFT)
#define DPU_MAKE_UNIT_ATTR(attr)     (((uint32_t)(attr)) << DPU_UNIT_ATTR_SHIFT)
#define DPU_MAKE_UNIT_OFFSET(offset) (((uint32_t)(offset)) << DPU_UNIT_OFFSET_SHIFT)

#define DPU_GET_UNIT_TYPE(unit)   ((((uint32_t)(unit)) & DPU_UNIT_TYPE_MASK) >> DPU_UNIT_TYPE_SHIFT)
#define DPU_GET_UNIT_ATTR(unit)   ((((uint32_t)(unit)) & DPU_UNIT_ATTR_MASK) >> DPU_UNIT_ATTR_SHIFT)
#define DPU_GET_UNIT_OFFSET(unit) ((((uint32_t)(unit)) & DPU_UNIT_OFFSET_MASK) >> DPU_UNIT_OFFSET_SHIFT)

#define DPU_MAKE_UNIT(type, attr, offset) \
    (DPU_MAKE_UNIT_TYPE(type) | DPU_MAKE_UNIT_ATTR(attr) | DPU_MAKE_UNIT_OFFSET(offset))

/* DPU init offset definitions, these offset are for driver internal use only. */
#define DPU_UNIT_OFFSET(unit) (uint32_t)(&((IRIS_MVPL_Type *)0)->unit)
#if DPU_USE_GENERATE_HEADER
#define DPU_FETCH_ECO9_OFFSET       DPU_UNIT_OFFSET(FETCHECO9)
#define DPU_FETCH_DECODE9_OFFSET    DPU_UNIT_OFFSET(FETCHDECODE9)
#define DPU_FETCH_WARP9_OFFSET      DPU_UNIT_OFFSET(FETCHWARP9)
#define DPU_BLITBLEND9_OFFSET       DPU_UNIT_OFFSET(BLITBLEND9)
#define DPU_ROP9_OFFSET             DPU_UNIT_OFFSET(ROP9)
#define DPU_STORE9_OFFSET           DPU_UNIT_OFFSET(STORE9)
#define DPU_H_SCALER9_OFFSET        DPU_UNIT_OFFSET(H_SCALER9)
#define DPU_V_SCALER9_OFFSET        DPU_UNIT_OFFSET(V_SCALER9)
#define DPU_CONST_FRAME0_OFFSET     DPU_UNIT_OFFSET(CONSTFRAME0)
#define DPU_EXT_DST0_OFFSET         DPU_UNIT_OFFSET(EXTDST0)
#define DPU_CONST_FRAME4_OFFSET     DPU_UNIT_OFFSET(CONSTFRAME4)
#define DPU_EXT_DST4_OFFSET         DPU_UNIT_OFFSET(EXTDST4)
#define DPU_CONST_FRAME1_OFFSET     DPU_UNIT_OFFSET(CONSTFRAME1)
#define DPU_EXT_DST1_OFFSET         DPU_UNIT_OFFSET(EXTDST1)
#define DPU_CONST_FRAME5_OFFSET     DPU_UNIT_OFFSET(CONSTFRAME5)
#define DPU_EXT_DST5_OFFSET         DPU_UNIT_OFFSET(EXTDST5)
#define DPU_FETCH_WARP2_OFFSET      DPU_UNIT_OFFSET(FETCHWARP2)
#define DPU_FETCH_ECO2_OFFSET       DPU_UNIT_OFFSET(FETCHECO2)
#define DPU_FETCH_DECODE0_OFFSET    DPU_UNIT_OFFSET(FETCHDECODE0)
#define DPU_FETCH_ECO0_OFFSET       DPU_UNIT_OFFSET(FETCHECO0)
#define DPU_FETCH_DECODE1_OFFSET    DPU_UNIT_OFFSET(FETCHDECODE1)
#define DPU_FETCH_ECO1_OFFSET       DPU_UNIT_OFFSET(FETCHECO1)
#define DPU_FETCH_LAYER0_OFFSET     DPU_UNIT_OFFSET(FETCHLAYER0)
#define DPU_H_SCALER4_OFFSET        DPU_UNIT_OFFSET(H_SCALER4)
#define DPU_V_SCALER4_OFFSET        DPU_UNIT_OFFSET(V_SCALER4)
#define DPU_H_SCALER5_OFFSET        DPU_UNIT_OFFSET(HSCALER5)
#define DPU_V_SCALER5_OFFSET        DPU_UNIT_OFFSET(V_SCALER5)
#define DPU_LAYER_BLEND0_OFFSET     DPU_UNIT_OFFSET(LAYERBLEND0)
#define DPU_LAYER_BLEND1_OFFSET     DPU_UNIT_OFFSET(LAYERBLEND1)
#define DPU_LAYER_BLEND2_OFFSET     DPU_UNIT_OFFSET(LAYERBLEND2)
#define DPU_LAYER_BLEND3_OFFSET     DPU_UNIT_OFFSET(LAYERBLEND3)
#define DPU_FRAME_GEN0_OFFSET       DPU_UNIT_OFFSET(FRAMEGEN0)
#define DPU_TCON0_OFFSET            DPU_UNIT_OFFSET(TCON0)
#define DPU_SIG0_OFFSET             DPU_UNIT_OFFSET(SIG0)
#define DPU_FRAME_GEN1_OFFSET       DPU_UNIT_OFFSET(FRAMEGEN1)
#define DPU_TCON1_OFFSET            DPU_UNIT_OFFSET(TCON1)
#define DPU_SIG1_OFFSET             DPU_UNIT_OFFSET(SIG1)
#define DPU_PIPELINE_EXTDST0_OFFSET DPU_UNIT_OFFSET(PIXENGCFG.EXTDST0_LOCKUNLOCK)
#define DPU_PIPELINE_EXTDST1_OFFSET DPU_UNIT_OFFSET(PIXENGCFG.EXTDST1_LOCKUNLOCK)
#define DPU_PIPELINE_EXTDST4_OFFSET DPU_UNIT_OFFSET(PIXENGCFG.EXTDST4_LOCKUNLOCK)
#define DPU_PIPELINE_EXTDST5_OFFSET DPU_UNIT_OFFSET(PIXENGCFG.EXTDST5_LOCKUNLOCK)
#define DPU_PIPELINE_STORE9_OFFSET  DPU_UNIT_OFFSET(PIXENGCFG.STORE9_LOCKUNLOCK)
#else
#define DPU_COMCTRL_OFFSET          0x0000U
#define DPU_FETCH_DECODE9_OFFSET    0x1000U
#define DPU_FETCH_WARP9_OFFSET      0x1800U
#define DPU_FETCH_ECO9_OFFSET       0x1C00U
#define DPU_ROP9_OFFSET             0x2000U
#define DPU_H_SCALER9_OFFSET        0x3000U
#define DPU_V_SCALER9_OFFSET        0x3400U
#define DPU_BLITBLEND9_OFFSET       0x3C00U
#define DPU_STORE9_OFFSET           0x4000U
#define DPU_CONST_FRAME0_OFFSET     0x4400U
#define DPU_EXT_DST0_OFFSET         0x4800U
#define DPU_CONST_FRAME4_OFFSET     0x4c00U
#define DPU_EXT_DST4_OFFSET         0x5000U
#define DPU_CONST_FRAME1_OFFSET     0x5400U
#define DPU_EXT_DST1_OFFSET         0x5800U
#define DPU_CONST_FRAME5_OFFSET     0x5c00U
#define DPU_EXT_DST5_OFFSET         0x6000U
#define DPU_FETCH_WARP2_OFFSET      0x6400U
#define DPU_FETCH_ECO2_OFFSET       0x6800U
#define DPU_FETCH_DECODE0_OFFSET    0x6c00U
#define DPU_FETCH_ECO0_OFFSET       0x7400U
#define DPU_FETCH_DECODE1_OFFSET    0x7800U
#define DPU_FETCH_ECO1_OFFSET       0x8000U
#define DPU_FETCH_LAYER0_OFFSET     0x8400U
#define DPU_H_SCALER4_OFFSET        0x9000U
#define DPU_V_SCALER4_OFFSET        0x9400U
#define DPU_H_SCALER5_OFFSET        0x9c00U
#define DPU_V_SCALER5_OFFSET        0xa000U
#define DPU_LAYER_BLEND0_OFFSET     0xa400U
#define DPU_LAYER_BLEND1_OFFSET     0xa800U
#define DPU_LAYER_BLEND2_OFFSET     0xac00U
#define DPU_LAYER_BLEND3_OFFSET     0xb000U
#define DPU_DISENGCONF_OFFSET       0xb400U
#define DPU_FRAME_GEN0_OFFSET       0xb800U
#define DPU_TCON0_OFFSET            0xc800U
#define DPU_SIG0_OFFSET             0xd000U
#define DPU_FRAME_GEN1_OFFSET       0xd400U
#define DPU_TCON1_OFFSET            0xe400U
#define DPU_SIG1_OFFSET             0xec00U
#define DPU_PIPELINE_EXTDST0_OFFSET 0x0980U
#define DPU_PIPELINE_EXTDST1_OFFSET 0x0a00U
#define DPU_PIPELINE_EXTDST4_OFFSET 0x09C0U
#define DPU_PIPELINE_EXTDST5_OFFSET 0x0a40U
#define DPU_PIPELINE_STORE9_OFFSET  0x0940U

#define DPU_ROP_CONTROL_Mode_MASK      (1U << 0U)
#define DPU_ROP_CONTROL_RedMode_MASK   (1U << 7U)
#define DPU_ROP_CONTROL_GreenMode_MASK (1U << 6U)
#define DPU_ROP_CONTROL_BlueMode_MASK  (1U << 5U)
#define DPU_ROP_CONTROL_AlphaMode_MASK (1U << 4U)
#define DPU_ROP_CONTROL_TertDiv2_MASK  (1U << 10U)
#define DPU_ROP_CONTROL_SecDiv2_MASK   (1U << 9U)
#define DPU_ROP_CONTROL_PrimDiv2_MASK  (1U << 8U)

#define DPU_DISENGCONF_POLARITYCTRL_PixInv_MASK (1U << 3U)
#define DPU_DISENGCONF_POLARITYCTRL_PolEn_MASK  (1U << 2U)
#define DPU_DISENGCONF_POLARITYCTRL_PolVs_MASK  (1U << 1U)
#define DPU_DISENGCONF_POLARITYCTRL_PolHs_MASK  (1U << 0U)

#define DPU_SIG_EVALCONTROL_EnGlobalPanic_MASK (1U << 17U)
#define DPU_SIG_EVALCONTROL_EnLocalPanic_MASK  (1U << 16U)
#define DPU_SIG_EVALCONTROL_AlphaInv_MASK      (1U << 9U)
#define DPU_SIG_EVALCONTROL_AlphaMask_MASK     (1U << 8U)
#define DPU_SIG_EVALCONTROL_EnCRC_MASK         (1U << 1U)
#define DPU_SIG_EVALCONTROL_EnEvalWin_MASK     (1U << 0U)

#define DPU_SIG_STATUS_StsSigIdle_MASK  (1U << 20U)
#define DPU_SIG_STATUS_StsSigValid_MASK (1U << 16U)
#define DPU_SIG_STATUS_StsSigError_MASK (0xFU << 0U)

#define DPU_SIG_EVALUPPERLEFT_XEvalUpperLeft_SHIFT    (0U)
#define DPU_SIG_EVALUPPERLEFT_YEvalUpperLeft_SHIFT    (16U)
#define DPU_SIG_EVALLOWERRIGHT_XEvalLowerRight_SHIFT  (0U)
#define DPU_SIG0_EVALLOWERRIGHT_YEvalLowerRight_SHIFT (16U)

#define DPU_SIG_SHADOWLOAD_ShdLdReq_MASK (0xFFU)
#endif

/* DPU unit type, internal used for DPU_MAKE_UNIT, _dpu_unit_type. */
enum
{
    kDPU_Pipeline,
    kDPU_BlitBlend,
    kDPU_Rop,
    kDPU_FetchDecode,
    kDPU_FetchWarp,
    kDPU_FetchEco,
    kDPU_FetchLayer,
    kDPU_HScaler,
    kDPU_VScaler,
    kDPU_ConstFrame,
    kDPU_ExtDst,
    kDPU_LayerBlend,
    kDPU_Store,
};

/* DPU unit attribute, internal used for DPU_MAKE_UNIT, _dpu_unit_attr. */
enum
{
    kDPU_UnitAttrIsFetch  = (1U << 0U), /* Is fetch unit.              */
    kDPU_UnitAttrHasSrc   = (1U << 1U), /* Has input source selection. */
    kDPU_UnitAttrNoShdow  = (1U << 2U), /* Does not support shadow load. */
    kDPU_UnitAttrSubLayer = (1U << 3U)  /* Has sub layer. */
};

/*! @brief DPU units. */
typedef enum _dpu_unit
{
    /*
     * In DPU driver, the pipeline is also treated as a unit. For example, the
     * kDPU_PipelineExtDst4 means the pipeline with ExtDst4 as its endpoint.
     * The driver uses the endpoint control registers in "Pixel Engine Top Level"
     * as the pipeline's control block.
     */
    kDPU_PipelineStore9 = DPU_MAKE_UNIT(kDPU_Pipeline, 0U, DPU_PIPELINE_STORE9_OFFSET),
    kDPU_FetchWarp9     = DPU_MAKE_UNIT(
        kDPU_FetchWarp, kDPU_UnitAttrIsFetch | kDPU_UnitAttrHasSrc | kDPU_UnitAttrSubLayer, DPU_FETCH_WARP9_OFFSET),
    kDPU_FetchDecode9 =
        DPU_MAKE_UNIT(kDPU_FetchDecode, kDPU_UnitAttrIsFetch | kDPU_UnitAttrHasSrc, DPU_FETCH_DECODE9_OFFSET),
    kDPU_FetchEco9 = DPU_MAKE_UNIT(kDPU_FetchEco, kDPU_UnitAttrIsFetch, DPU_FETCH_ECO9_OFFSET),
    kDPU_Hscaler9  = DPU_MAKE_UNIT(kDPU_HScaler, kDPU_UnitAttrHasSrc, DPU_H_SCALER9_OFFSET),
    kDPU_Vscaler9  = DPU_MAKE_UNIT(kDPU_VScaler, kDPU_UnitAttrHasSrc, DPU_V_SCALER9_OFFSET),

    kDPU_Rop9       = DPU_MAKE_UNIT(kDPU_Rop, kDPU_UnitAttrHasSrc, DPU_ROP9_OFFSET),
    kDPU_BlitBlend9 = DPU_MAKE_UNIT(kDPU_BlitBlend, kDPU_UnitAttrHasSrc, DPU_BLITBLEND9_OFFSET),
    kDPU_Store9     = DPU_MAKE_UNIT(kDPU_Store, kDPU_UnitAttrHasSrc, DPU_STORE9_OFFSET),

    kDPU_PipelineExtDst0 = DPU_MAKE_UNIT(kDPU_Pipeline, 0U, DPU_PIPELINE_EXTDST0_OFFSET),
    kDPU_PipelineExtDst1 = DPU_MAKE_UNIT(kDPU_Pipeline, 0U, DPU_PIPELINE_EXTDST1_OFFSET),
    kDPU_PipelineExtDst4 = DPU_MAKE_UNIT(kDPU_Pipeline, 0U, DPU_PIPELINE_EXTDST4_OFFSET),
    kDPU_PipelineExtDst5 = DPU_MAKE_UNIT(kDPU_Pipeline, 0U, DPU_PIPELINE_EXTDST5_OFFSET),
    kDPU_ConstFrame0     = DPU_MAKE_UNIT(kDPU_ConstFrame, 0U, DPU_CONST_FRAME0_OFFSET),
    kDPU_ExtDst0         = DPU_MAKE_UNIT(kDPU_ExtDst, kDPU_UnitAttrHasSrc, DPU_EXT_DST0_OFFSET),
    kDPU_ConstFrame4     = DPU_MAKE_UNIT(kDPU_ConstFrame, 0U, DPU_CONST_FRAME4_OFFSET),
    kDPU_ExtDst4         = DPU_MAKE_UNIT(kDPU_ExtDst, kDPU_UnitAttrHasSrc, DPU_EXT_DST4_OFFSET),
    kDPU_ConstFrame1     = DPU_MAKE_UNIT(kDPU_ConstFrame, 0U, DPU_CONST_FRAME1_OFFSET),
    kDPU_ExtDst1         = DPU_MAKE_UNIT(kDPU_ExtDst, kDPU_UnitAttrHasSrc, DPU_EXT_DST1_OFFSET),
    kDPU_ConstFrame5     = DPU_MAKE_UNIT(kDPU_ConstFrame, 0U, DPU_CONST_FRAME5_OFFSET),
    kDPU_ExtDst5         = DPU_MAKE_UNIT(kDPU_ExtDst, kDPU_UnitAttrHasSrc, DPU_EXT_DST5_OFFSET),
    kDPU_FetchWarp2      = DPU_MAKE_UNIT(
        kDPU_FetchWarp, kDPU_UnitAttrIsFetch | kDPU_UnitAttrHasSrc | kDPU_UnitAttrSubLayer, DPU_FETCH_WARP2_OFFSET),
    kDPU_FetchEco2 = DPU_MAKE_UNIT(kDPU_FetchEco, kDPU_UnitAttrIsFetch, DPU_FETCH_ECO2_OFFSET),
    kDPU_FetchDecode0 =
        DPU_MAKE_UNIT(kDPU_FetchDecode, kDPU_UnitAttrIsFetch | kDPU_UnitAttrHasSrc, DPU_FETCH_DECODE0_OFFSET),
    kDPU_FetchEco0 = DPU_MAKE_UNIT(kDPU_FetchEco, kDPU_UnitAttrIsFetch, DPU_FETCH_ECO0_OFFSET),
    kDPU_FetchDecode1 =
        DPU_MAKE_UNIT(kDPU_FetchDecode, kDPU_UnitAttrIsFetch | kDPU_UnitAttrHasSrc, DPU_FETCH_DECODE1_OFFSET),
    kDPU_FetchEco1 = DPU_MAKE_UNIT(kDPU_FetchEco, kDPU_UnitAttrIsFetch, DPU_FETCH_ECO1_OFFSET),
    kDPU_FetchLayer0 =
        DPU_MAKE_UNIT(kDPU_FetchLayer, kDPU_UnitAttrIsFetch | kDPU_UnitAttrSubLayer, DPU_FETCH_LAYER0_OFFSET),
    kDPU_Hscaler4    = DPU_MAKE_UNIT(kDPU_HScaler, kDPU_UnitAttrHasSrc, DPU_H_SCALER4_OFFSET),
    kDPU_Vscaler4    = DPU_MAKE_UNIT(kDPU_VScaler, kDPU_UnitAttrHasSrc, DPU_V_SCALER4_OFFSET),
    kDPU_Hscaler5    = DPU_MAKE_UNIT(kDPU_HScaler, kDPU_UnitAttrHasSrc, DPU_H_SCALER5_OFFSET),
    kDPU_Vscaler5    = DPU_MAKE_UNIT(kDPU_VScaler, kDPU_UnitAttrHasSrc, DPU_V_SCALER5_OFFSET),
    kDPU_LayerBlend0 = DPU_MAKE_UNIT(kDPU_LayerBlend, kDPU_UnitAttrHasSrc, DPU_LAYER_BLEND0_OFFSET),
    kDPU_LayerBlend1 = DPU_MAKE_UNIT(kDPU_LayerBlend, kDPU_UnitAttrHasSrc, DPU_LAYER_BLEND1_OFFSET),
    kDPU_LayerBlend2 = DPU_MAKE_UNIT(kDPU_LayerBlend, kDPU_UnitAttrHasSrc, DPU_LAYER_BLEND2_OFFSET),
    kDPU_LayerBlend3 = DPU_MAKE_UNIT(kDPU_LayerBlend, kDPU_UnitAttrHasSrc, DPU_LAYER_BLEND3_OFFSET),
} dpu_unit_t;

/*! @brief DPU interrupt. */
enum _dpu_interrupt
{
    kDPU_Group0Store9ShadowLoadInterrupt      = (1U << 0U),  /*!< Store9 shadow load interrupt. */
    kDPU_Group0Store9FrameCompleteInterrupt   = (1U << 1U),  /*!< Store9 frame complete interrupt. */
    kDPU_Group0Store9SeqCompleteInterrupt     = (1U << 2U),  /*!< Store9 sequence complete interrupt. */
    kDPU_Group0ExtDst0ShadowLoadInterrupt     = (1U << 3U),  /*!< ExtDst0 shadow load interrupt. */
    kDPU_Group0ExtDst0FrameCompleteInterrupt  = (1U << 4U),  /*!< ExtDst0 frame complete interrupt. */
    kDPU_Group0ExtDst0SeqCompleteInterrupt    = (1U << 5U),  /*!< ExtDst0 sequence complete interrupt. */
    kDPU_Group0ExtDst4ShadowLoadInterrupt     = (1U << 6U),  /*!< ExtDst4 shadow load interrupt. */
    kDPU_Group0ExtDst4FrameCompleteInterrupt  = (1U << 7U),  /*!< ExtDst4 frame complete interrupt. */
    kDPU_Group0ExtDst4SeqCompleteInterrupt    = (1U << 8U),  /*!< ExtDst4 sequence complete interrupt. */
    kDPU_Group0ExtDst1ShadowLoadInterrupt     = (1U << 9U),  /*!< ExtDst1 shadow load interrupt. */
    kDPU_Group0ExtDst1FrameCompleteInterrupt  = (1U << 10U), /*!< ExtDst1 frame complete interrupt. */
    kDPU_Group0ExtDst1SeqCompleteInterrupt    = (1U << 11U), /*!< ExtDst1 sequence complete interrupt. */
    kDPU_Group0ExtDst5ShadowLoadInterrupt     = (1U << 12U), /*!< ExtDst5 shadow load interrupt. */
    kDPU_Group0ExtDst5FrameCompleteInterrupt  = (1U << 13U), /*!< ExtDst5 frame complete interrupt. */
    kDPU_Group0ExtDst5SeqCompleteInterrupt    = (1U << 14U), /*!< ExtDst5 sequence complete interrupt. */
    kDPU_Group0Display0ShadowLoadInterrupt    = (1U << 15U), /*!< Display stream 0 shadow load interrupt. */
    kDPU_Group0Display0FrameCompleteInterrupt = (1U << 16U), /*!< Display stream 0 frame complete interrupt. */
    kDPU_Group0Display0SeqCompleteInterrupt   = (1U << 17U), /*!< Display stream 0 sequence complete interrupt. */
    kDPU_Group0FrameGen0Int0Interrupt         = (1U << 18U), /*!< FrameGen 0 interrupt 0. */
    kDPU_Group0FrameGen0Int1Interrupt         = (1U << 19U), /*!< FrameGen 0 interrupt 1. */
    kDPU_Group0FrameGen0Int2Interrupt         = (1U << 20U), /*!< FrameGen 0 interrupt 2. */
    kDPU_Group0FrameGen0Int3Interrupt         = (1U << 21U), /*!< FrameGen 0 interrupt 3. */
    kDPU_Group0Sig0ShadowLoadInterrupt        = (1U << 22U), /*!< Sig0 shadow load interrupt. */
    kDPU_Group0Sig0ValidInterrupt             = (1U << 23U), /*!< Sig0 measurement valid interrupt. */
    kDPU_Group0Sig0ErrorInterrupt             = (1U << 24U), /*!< Sig0 error interrupt. */
    kDPU_Group0Display1ShadowLoadInterrupt    = (1U << 25U), /*!< Display stream 1 shadow load interrupt. */
    kDPU_Group0Display1FrameCompleteInterrupt = (1U << 26U), /*!< Display stream 1 frame complete interrupt. */
    kDPU_Group0Display1SeqCompleteInterrupt   = (1U << 27U), /*!< Display stream 1 sequence complete interrupt. */
    kDPU_Group0FrameGen1Int0Interrupt         = (1U << 28U), /*!< FrameGen 1 interrupt 0. */
    kDPU_Group0FrameGen1Int1Interrupt         = (1U << 29U), /*!< FrameGen 1 interrupt 1. */
    kDPU_Group0FrameGen1Int2Interrupt         = (1U << 30U), /*!< FrameGen 1 interrupt 2. */
    kDPU_Group0FrameGen1Int3Interrupt         = (1U << 31U), /*!< FrameGen 1 interrupt 3. */
    kDPU_Group1Sig1ShadowLoadInterrupt        = (1U << 0U),  /*!< Sig1 shadow load interrupt. */
    kDPU_Group1Sig1ValidInterrupt             = (1U << 1U),  /*!< Sig1 measurement valid interrupt. */
    kDPU_Group1Sig1ErrorInterrupt             = (1U << 2U),  /*!< Sig1 error interrupt. */
    kDPU_Group1CmdSeqErrorInterrupt           = (1U << 4U),  /*!< Command sequencer error interrupt. */
    kDPU_Group1SoftwareInt0Interrupt          = (1U << 5U),  /*!< Common software interrupt 0. */
    kDPU_Group1SoftwareInt1Interrupt          = (1U << 6U),  /*!< Common software interrupt 1. */
    kDPU_Group1SoftwareInt2Interrupt          = (1U << 7U),  /*!< Common software interrupt 2. */
    kDPU_Group1SoftwareInt3Interrupt          = (1U << 8U),  /*!< Common software interrupt 3. */
    kDPU_Group1FrameGen0PrimSyncOnInterrupt   = (1U << 9U),  /*!< Safety stream 0 synchronized interrupt. */
    kDPU_Group1FrameGen0PrimSyncOffInterrupt  = (1U << 10U), /*!< Safety stream 0 loss synchronization interrupt. */
    kDPU_Group1FrameGen0SecSyncOnInterrupt    = (1U << 11U), /*!< Content stream 0 synchronized interrupt. */
    kDPU_Group1FrameGen0SecSyncOffInterrupt   = (1U << 12U), /*!< Content stream 0 loss synchronization interrupt. */
    kDPU_Group1FrameGen1PrimSyncOnInterrupt   = (1U << 13U), /*!< Safety stream 1 synchronized interrupt. */
    kDPU_Group1FrameGen1PrimSyncOffInterrupt  = (1U << 14U), /*!< Safety stream 1 loss synchronization interrupt. */
    kDPU_Group1FrameGen1SecSyncOnInterrupt    = (1U << 15U), /*!< Content stream 1 synchronized interrupt. */
    kDPU_Group1FrameGen1SecSyncOffInterrupt   = (1U << 16U), /*!< Content stream 1 loss synchronization interrupt. */
};

/*! @brief DPU unit input source. */
enum _dpu_unit_source
{
    kDPU_UnitSrcNone         = 0,   /*!< Disable the input source. */
    kDPU_UnitSrcFetchDecode9 = 1U,  /*!< The input source is fetch decode 9. */
    kDPU_UnitSrcFetchWarp9   = 2U,  /*!< The input source is fetch warp 9. */
    kDPU_UnitSrcFetchEco9    = 3U,  /*!< The input source is fetch eco 9. */
    kDPU_UnitSrcRop9         = 4U,  /*!< The input source is rop 9. */
    kDPU_UnitSrcClut9        = 5U,  /*!< The input source is CLUT 9 */
    kDPU_UnitSrcMatrix9      = 6U,  /*!< The input source is matrix 9. */
    kDPU_UnitSrcHScaler9     = 7U,  /*!< The input source is HScaler 9. */
    kDPU_UnitSrcVScaler9     = 8U,  /*!< The input source is VScaler 9. */
    kDPU_UnitSrcFilter9      = 9U,  /*!< The input source is Filter 9. */
    kDPU_UnitSrcBlitBlend9   = 10U, /*!< The input source is BlitBlend 9. */
    kDPU_UnitSrcStore9       = 11U, /*!< The input source is Store 9. */
    kDPU_UnitSrcConstFrame0  = 12U, /*!< The input source is ConstFrame 0. */
    kDPU_UnitSrcConstFrame1  = 16U, /*!< The input source is ConstFrame 1. */
    kDPU_UnitSrcConstFrame4  = 14U, /*!< The input source is ConstFrame 4. */
    kDPU_UnitSrcConstFrame5  = 18U, /*!< The input source is ConstFrame 5. */
    kDPU_UnitSrcFetchWarp2   = 20U, /*!< The input source is FetchWarp 2. */
    kDPU_UnitSrcFetchEco2    = 21U, /*!< The input source is FetchEco 2. */
    kDPU_UnitSrcFetchDecode0 = 22U, /*!< The input source is FetchDecode 0. */
    kDPU_UnitSrcFetchEco0    = 23U, /*!< The input source is FetchEco 0. */
    kDPU_UnitSrcFetchDecode1 = 24U, /*!< The input source is FetchDecode 1. */
    kDPU_UnitSrcFetchEco1    = 25U, /*!< The input source is FetchEco 1. */
    kDPU_UnitSrcFetchLayer0  = 26U, /*!< The input source is FetchLayer 0. */
    kDPU_UnitSrcMatrix4      = 27U, /*!< The input source is Matrix 4. */
    kDPU_UnitSrcHScaler4     = 28U, /*!< The input source is HScaler 4. */
    kDPU_UnitSrcVScaler4     = 29U, /*!< The input source is VScaler 4. */
    kDPU_UnitSrcMatrix5      = 30U, /*!< The input source is Matrix 5. */
    kDPU_UnitSrcHScaler5     = 31U, /*!< The input source is HScaler 5. */
    kDPU_UnitSrcVScaler5     = 32U, /*!< The input source is VScaler 5. */
    kDPU_UnitSrcLayerBlend0  = 33U, /*!< The input source is LayerBlend 0. */
    kDPU_UnitSrcLayerBlend1  = 34U, /*!< The input source is LayerBlend 1. */
    kDPU_UnitSrcLayerBlend2  = 35U, /*!< The input source is LayerBlend 2. */
    kDPU_UnitSrcLayerBlend3  = 36U, /*!< The input source is LayerBlend 3. */
};

/*!
 * @brief DPU pixel format.
 *
 * To support more pixel format, enhance this enum and the array s_dpuColorComponentFormats.
 */
typedef enum _dpu_pixel_format
{
    kDPU_PixelFormatGray8    = 0, /*!< 8-bit gray. */
    kDPU_PixelFormatRGB565   = 1, /*!< RGB565, 16-bit per pixel. */
    kDPU_PixelFormatARGB8888 = 2, /*!< ARGB8888, 32-bit per pixel. */
    kDPU_PixelFormatRGB888   = 3, /*!< RGB888, 24-bit per pixel. */
    kDPU_PixelFormatARGB1555 = 4, /*!< ARGB1555, 16-bit per pixel. */
} dpu_pixel_format_t;

/*! @brief Configuration structure for fetch units. */
typedef struct _dpu_fetch_unit_config
{
    uint32_t srcReg;      /*!< This value will be set to register pixengcfg_fetchX_dynamic
                               to set the unit input source, see @ref DPU_MAKE_SRC_REG1. */
    uint16_t frameHeight; /*!< Frame height. */
    uint16_t frameWidth;  /*!< Frame width. */
} dpu_fetch_unit_config_t;

/*!
 * @brief Configuration structure for the arbitrary warping re-sampling coordinates.
 *
 * The coordinate layer supports:
 *
 * - 32 bpp: 2 x s12.4 (signed fix-point)
 * - 24 bpp: 2 x s8.
 * - 16 bpp: 2 x s4.4
 * - 8 bpp: 2 x s0.4
 * - 4 bpp: 2 x s(-2).4 (means total value size = 2 bits and lowest bit = 2^-4)
 * - 2 bpp: 2 x s(-3).4
 * - 1 bpp: 1 x s(-3).4 (x and y alternating)
 */
typedef struct _dpu_coordinates_config
{
    uint8_t bitsPerPixel; /*!< Number of bits per pixel in the source buffer. Must be 1, 2, 4, 8, 16, 32. */
    uint16_t strideBytes; /*!< Source buffer stride in bytes. */
    uint32_t baseAddr;    /*!< Source buffer base address. */
    uint16_t frameHeight; /*!< Frame height. */
    uint16_t frameWidth;  /*!< Frame width. */
} dpu_coordinates_config_t;

/*! @brief FetchWarp unit warp coordinate mode. */
typedef enum _dpu_warp_coordinate_mode
{
    kDPU_WarpCoordinateModePNT   = 0U, /*!< Sample points positions are read from coordinate layer. */
    kDPU_WarpCoordinateModeDPNT  = 1U, /*!< Sample points start position and delta are read from coordinate layer. */
    kDPU_WarpCoordinateModeDDPNT = 2U  /*!< Sample points initial value and delta increase
                                            value are read from coordinate layer. */
} dpu_warp_coordinate_mode_t;

/*! @brief Warp configuration structure for FetchWarp unit. */
typedef struct _dpu_warp_config
{
    uint32_t srcReg;                      /*!< This value will be set to register pixengcfg_fetchX_dynamic
                                               to set the unit input source, see @ref DPU_MAKE_SRC_REG1. */
    uint16_t frameHeight;                 /*!< Frame height. */
    uint16_t frameWidth;                  /*!< Frame width. */
    uint8_t warpBitsPerPixel;             /*!< Pixel bits of the coordinate layer. */
    bool enableSymmetricOffset;           /*!< Enables symmetric range for negative and positive coordinate
                                            values by adding an offset of +0.03125 internally to all
                                            coordinate input values. Recommended for small coordinate formats
                                            in DD_PNT mode. */
    dpu_warp_coordinate_mode_t coordMode; /*!< Coordinate layer mode. */
    uint32_t arbStartX; /*!< X of start point position. Signed 16.5 fix-point. Used in D_PNT and DD_PNT. */
    uint32_t arbStartY; /*!< Y of start point position. Signed 16.5 fix-point. Used in D_PNT and DD_PNT. */
    uint8_t arbDeltaYY; /*!< Y of vector between start and first sample point. Signed 3.5 fix-point. Used in DD_PNT. */
    uint8_t arbDeltaYX; /*!< X of vector between start and first sample point. Signed 3.5 fix-point. Used in DD_PNT. */
    uint8_t arbDeltaXY; /*!< Y of vector between first and second sample point. Signed 3.5 fix-point. Used in DD_PNT. */
    uint8_t arbDeltaXX; /*!< X of vector between first and second sample point. Signed 3.5 fix-point. Used in DD_PNT. */
} dpu_warp_config_t;

/*!
 * @brief Fetch unit source buffer configuration structure.
 *
 * Base address and stride alignment restrictions:
 *   32 bpp: Base address and stride must be a multiple of 4 bytes.
 *   16 bpp: Base address and stride must be a multiple of 2 bytes.
 *   others: any byte alignment allowed
 *
 * Generally, the @ref bitsPerPixel and @ref pixelFormat specify the pixel format
 * in frame buffer, they should match. But when the color palette is used, the
 * @ref bitsPerPixel specify the format in framebuffer, the @ref pixelFormat
 * specify the format in color palette entry.
 */
typedef struct _dpu_src_buffer_config
{
    uint32_t baseAddr;              /*!< Source buffer base address, see alignment restrictions. */
    uint16_t strideBytes;           /*!< Source buffer stride in bytes, see alignment restrictions. */
    uint8_t bitsPerPixel;           /*!< Bits per pixel in frame buffer. */
    dpu_pixel_format_t pixelFormat; /*!< Pixel format. */
    uint16_t bufferHeight;          /*!< Buffer height. */
    uint16_t bufferWidth;           /*!< Buffer width. */
    uint32_t constColor; /*!< Const color shown in the region out of frame buffer, see @ref DPU_MAKE_CONST_COLOR. */
} dpu_src_buffer_config_t;

/*! @brief Fetch unit clip window configuration structure. */
typedef struct _dpu_clip_window_config
{
    uint16_t windowOffsetX; /*!< Horizontal offset of the clip window. */
    uint16_t windowOffsetY; /*!< Vertical offset of the clip window. */
    uint16_t windowHeight;  /*!< Height of the clip window. */
    uint16_t windowWidth;   /*!< Width of the clip window. */
} dpu_clip_window_config_t;

/*! @brief Define the color to take for pixels that do not lie inside the clip window of any layer */
typedef enum _dpu_clip_color_mode
{
    kDPU_ClipColorNull,     /*!< Use null color. */
    kDPU_ClipColorSublayer, /*!< Use color of sublayer. */
} dpu_clip_color_mode_t;
/*!
 * @brief Store unit Destination buffer configuration structure.
 *
 * Base address and stride alignment restrictions:
 *   32 bpp: Base address and stride must be a multiple of 4 bytes.
 *   16 bpp: Base address and stride must be a multiple of 2 bytes.
 *   others: any byte alignment allowed
 */
typedef struct _dpu_dst_buffer_config
{
    uint32_t baseAddr;              /*!< Destination buffer base address, see alignment restrictions. */
    uint16_t strideBytes;           /*!< Destination buffer stride in bytes, see alignment restrictions. */
    uint8_t bitsPerPixel;           /*!< Bits per pixel. */
    dpu_pixel_format_t pixelFormat; /*!< Pixel format. */
    uint16_t bufferHeight;          /*!< Buffer height. */
    uint16_t bufferWidth;           /*!< Buffer width. */
} dpu_dst_buffer_config_t;

/*! @brief LayerBlend unit AlphaMask mode. */
typedef enum _dpu_alpha_mask_mode
{
    kDPU_AlphaMaskPrim,       /*!< Areas with primary input alpha > 128 mapped to alpha 255, the rest mapped to 0. */
    kDPU_AlphaMaskSec,        /*!< Areas with secondary input alpha > 128 mapped to alpha 255, the rest mapped to 0. */
    kDPU_AlphaMaskPrimOrSec,  /*!< Primary and secondary OR'ed together. */
    kDPU_AlphaMaskPrimAndSec, /*!< Primary and secondary AND'ed together. */
    kDPU_AlphaMaskPrimInv,    /*!< Primary input alpha inverted. */
    kDPU_AlphaMaskSecInv,     /*!< Secondary input alpha inverted. */
    kDPU_AlphaMaskPrimOrSecInv, /*!< Primary and inverted secondary OR'ed together. */
    kDPU_AlphaMaskPrimAndSecInv /*!< Primary and inverted secondary AND'ed together. */
} dpu_alpha_mask_mode_t;

/*! @brief LayerBlend unit alpha blend mode. */
typedef enum _dpu_blend_mode
{
    kDPU_BlendZero,          /*!< OUT = IN * 0. */
    kDPU_BlendOne,           /*!< OUT = IN * 1. */
    kDPU_BlendPrimAlpha,     /*!< OUT = IN * ALPHA_primary. */
    kDPU_BlendPrimAlphaInv,  /*!< OUT = IN * (1 - ALPHA_primary). */
    kDPU_BlendSecAlpha,      /*!< OUT = IN * ALPHA_secondary. */
    kDPU_BlendSecAlphaInv,   /*!< OUT = IN * (1 - ALPHA_secondary). */
    kDPU_BlendConstAlpha,    /*!< OUT = IN * ALPHA_const. */
    kDPU_BlendConstAlphaInv, /*!< OUT = IN * (1 - ALPHA_const). */
} dpu_blend_mode_t;

/*! @brief LayerBlend unit configuration structure. */
typedef struct _dpu_layer_blend_config
{
    uint8_t constAlpha;                  /*!< The const alpha value used in blend. */
    dpu_blend_mode_t secAlphaBlendMode;  /*!< Secondary (overlay) input alpha blending function. */
    dpu_blend_mode_t primAlphaBlendMode; /*!< Primary (background) input alpha blending function. */
    dpu_blend_mode_t secColorBlendMode;  /*!< Secondary (overlay) input color blending function. */
    dpu_blend_mode_t primColorBlendMode; /*!< Primary (background) input color blending function. */

    uint32_t srcReg;                     /*!< This value will be set to pixengcfg_layerblendX_dynamic
                                              to set the unit input source, see @ref DPU_MAKE_SRC_REG2. */
    bool enableAlphaMask;                /*!< Enable AlphaMask feature. */
    dpu_alpha_mask_mode_t alphaMaskMode; /*!< AlphaMask mode, only valid when enableAlphaMask is true. */
} dpu_layer_blend_config_t;

/*! @brief BlitBlend blend function. */
typedef enum _dpu_blit_blend_func
{
    kDPU_BlitBlendFuncGlZero               = 0,      /*!< GL_ZERO. */
    kDPU_BlitBlendFuncGlOne                = 1,      /*!< GL_ONE. */
    kDPU_BlitBlendFuncGlSrcColor           = 0x0300, /*!< GL_SRC_COLOR */
    kDPU_BlitBlendFuncGlOneMinusSrcColor   = 0x0301, /*!< GL_ONE_MINUS_SRC_COLOR */
    kDPU_BlitBlendFuncGlSrcAlpha           = 0x0302, /*!< GL_SRC_ALPHA */
    kDPU_BlitBlendFuncGlOneMinusSrcAlpha   = 0x0303, /*!< GL_ONE_MINUS_SRC_ALPHA */
    kDPU_BlitBlendFuncGlDstAlpha           = 0x0304, /*!< GL_DST_ALPHA */
    kDPU_BlitBlendFuncGlOneMinusDstAlpha   = 0x0305, /*!< GL_ONE_MINUS_DST_ALPHA */
    kDPU_BlitBlendFuncGlDstColor           = 0x0306, /*!< GL_DST_COLOR */
    kDPU_BlitBlendFuncGlOneMinusDstColor   = 0x0307, /*!< GL_ONE_MINUS_DST_COLOR */
    kDPU_BlitBlendFuncGlSrcAlphaSaturate   = 0x0308, /*!< GL_SRC_ALPHA_SATURATE */
    kDPU_BlitBlendFuncGlConstColor         = 0x8001, /*!< GL_CONSTANT_COLOR */
    kDPU_BlitBlendFuncGlOneMinusConstColor = 0x8002, /*!< GL_ONE_MINUS_CONSTANT_COLOR */
    kDPU_BlitBlendFuncGlConstAlpha         = 0x8003, /*!< GL_CONSTANT_ALPHA */
    kDPU_BlitBlendFuncGlOneMinusConstAlpha = 0x8004, /*!< GL_ONE_MINUS_CONSTANT_ALPHA */
} dpu_blit_blend_func_t;

/*! @brief BlitBlend blend mode. */
typedef enum _dpu_blit_blend_mode
{
    kDPU_BlitBlendModeGlFuncAdd             = 0x8006, /*!< GL_FUNC_ADD */
    kDPU_BlitBlendModeGlMin                 = 0x8007, /*!< GL_MIN */
    kDPU_BlitBlendModeGlMax                 = 0x8008, /*!< GL_MAX */
    kDPU_BlitBlendModeGlFuncSubtract        = 0x800A, /*!< GL_FUNC_SUBTRACT */
    kDPU_BlitBlendModeGlFuncReverseSubtract = 0x800B, /*!< GL_FUNC_REVERSE_SUBTRACT */
    kDPU_BlitBlendModeVgBlendSrc            = 0x2000, /*!< VG_BLEND_SRC */
    kDPU_BlitBlendModeVgBlendSrcOver        = 0x2001, /*!< VG_BLEND_SRC_OVER */
    kDPU_BlitBlendModeVgBlendDstOver        = 0x2002, /*!< VG_BLEND_DST_OVER */
    kDPU_BlitBlendModeVgBlendSrcIn          = 0x2003, /*!< VG_BLEND_SRC_IN */
    kDPU_BlitBlendModeVgBlendDstIn          = 0x2004, /*!< VG_BLEND_DST_IN */
    kDPU_BlitBlendModeVgBlendMultiply       = 0x2005, /*!< VG_BLEND_MULTIPLY */
    kDPU_BlitBlendModeVgBlendScreen         = 0x2006, /*!< VG_BLEND_SCREEN */
    kDPU_BlitBlendModeVgBlendDarken         = 0x2007, /*!< VG_BLEND_DARKEN */
    kDPU_BlitBlendModeVgBlendLighten        = 0x2008, /*!< VG_BLEND_LIGHTEN */
    kDPU_BlitBlendModeVgBlendAdditive       = 0x2009, /*!< VG_BLEND_ADDITIVE */
} dpu_blit_blend_mode_t;

/*! @brief BlitBlend neutral border mode. */
typedef enum _dpu_blit_blend_neutral_border_mode
{
    kDPU_BlitBlendNeutralBorderPrim = 0, /*!< Bypasses primary pixel. */
    kDPU_BlitBlendNeutralBorderSec  = 0, /*!< Bypasses secondary pixel. */
} dpu_blit_blend_neutral_border_mode_t;

/*! @brief BlitBlend unit configuration structure. */
typedef struct _dpu_blit_blend_config
{
    uint8_t neutralBorderRightPixels;                       /*!< Number of neutral right border pixels. */
    uint8_t neutralBorderLeftPixels;                        /*!< Number of neutral left border pixels. */
    dpu_blit_blend_neutral_border_mode_t neutralBorderMode; /*!< Neutral border mode. */
    uint32_t constColor; /*!< Const color used for blit blend, see @ref DPU_MAKE_CONST_COLOR. */

    dpu_blit_blend_func_t redBlendFuncSrc;   /*!< Red component source blend function */
    dpu_blit_blend_func_t redBlendFuncDst;   /*!< Red component destination blend function */
    dpu_blit_blend_func_t greenBlendFuncSrc; /*!< Green component source blend function */
    dpu_blit_blend_func_t greenBlendFuncDst; /*!< Green component destination blend function */
    dpu_blit_blend_func_t blueBlendFuncSrc;  /*!< Blue component source blend function */
    dpu_blit_blend_func_t blueBlendFuncDst;  /*!< Blue component destination blend function */
    dpu_blit_blend_func_t alphaBlendFuncSrc; /*!< Alpha component source blend function */
    dpu_blit_blend_func_t alphaBlendFuncDst; /*!< Alpha component destination blend function */
    dpu_blit_blend_mode_t redBlendMode;      /*!< Red component blend mode */
    dpu_blit_blend_mode_t greenBlendMode;    /*!< Green component blend mode */
    dpu_blit_blend_mode_t blueBlendMode;     /*!< Blue component blend mode */
    dpu_blit_blend_mode_t alphaBlendMode;    /*!< Alpha component blend mode */
} dpu_blit_blend_config_t;

/*! @brief ROp unit control flags. */
enum _dpu_rop_flags
{
    kDPU_RopAddRed =
        DPU_ROP_CONTROL_RedMode_MASK, /*!< Set to add the red component, otherwise raster with operation index. */
    kDPU_RopAddGreen =
        DPU_ROP_CONTROL_GreenMode_MASK, /*!< Set to add the green component, otherwise raster with operation index. */
    kDPU_RopAddBlue =
        DPU_ROP_CONTROL_BlueMode_MASK, /*!< Set to add the blue component, otherwise raster with operation index. */
    kDPU_RopAddAlpha =
        DPU_ROP_CONTROL_AlphaMode_MASK, /*!< Set to add the alpha component, otherwise raster with operation index. */
    kDPU_RopTertDiv2 = DPU_ROP_CONTROL_TertDiv2_MASK, /*!< In add mode, set this to divide tertiary port input by 2. */
    kDPU_RopSecDiv2  = DPU_ROP_CONTROL_SecDiv2_MASK,  /*!< In add mode, set this to divide secondary port input by 2. */
    kDPU_RopPrimDiv2 = DPU_ROP_CONTROL_PrimDiv2_MASK, /*!< In add mode, set this to divide primary port input by 2. */
};

/*! @brief ROp unit configuration structure. */
typedef struct _dpu_rop_config
{
    uint32_t controlFlags; /*!< Control flags, see @ref _dpu_rop_flags. */
    uint8_t alphaIndex;    /*!< Alpha operation index. */
    uint8_t blueIndex;     /*!< Blue operation index. */
    uint8_t greenIndex;    /*!< Green operation index. */
    uint8_t redIndex;      /*!< Red operation index. */
} dpu_rop_config_t;

/*! @brief ConstFrame unit configuration structure. */
typedef struct _dpu_const_frame_config
{
    uint16_t frameHeight; /*!< Frame height. */
    uint16_t frameWidth;  /*!< Frame width. */
    uint32_t constColor;  /*!< See @ref DPU_MAKE_CONST_COLOR. */
} dpu_const_frame_config_t;

/*! @brief Display timing configuration flags. */
enum _dpu_display_timing_flags
{
    kDPU_DisplayPixelActiveHigh = 0,                                       /*!< Pixel data active high. */
    kDPU_DisplayPixelActiveLow  = DPU_DISENGCONF_POLARITYCTRL_PixInv_MASK, /*!< Pixel data active low. */
    kDPU_DisplayDataEnableActiveHigh =
        DPU_DISENGCONF_POLARITYCTRL_PolEn_MASK, /*!< Set to make data enable high active. */
    kDPU_DisplayDataEnableActiveLow = 0,        /*!< Set to make data enable high low. */
    kDPU_DisplayHsyncActiveHigh     = DPU_DISENGCONF_POLARITYCTRL_PolHs_MASK, /*!< Set to make HSYNC high active. */
    kDPU_DisplayHsyncActiveLow      = 0,                                      /*!< Set to make HSYNC low active. */
    kDPU_DisplayVsyncActiveHigh     = DPU_DISENGCONF_POLARITYCTRL_PolVs_MASK, /*!< Set to make VSYNC high active. */
    kDPU_DisplayVsyncActiveLow      = 0,                                      /*!< Set to make VSYNC low active. */
};

/*! @brief Display timing configuration structure. */
typedef struct _dpu_display_timing_config
{
    uint16_t flags;  /*!< OR'ed value of @ref _dpu_display_timing_flags. */
    uint16_t width;  /*!< Active width. */
    uint16_t hsw;    /*!< HSYNC pulse width. */
    uint16_t hfp;    /*!< Horizontal front porch. */
    uint16_t hbp;    /*!< Horizontal back porch. */
    uint16_t height; /*!< Active height. */
    uint16_t vsw;    /*!< VSYNC pulse width. */
    uint16_t vfp;    /*!< Vrtical front porch. */
    uint16_t vbp;    /*!< Vertical back porch. */
} dpu_display_timing_config_t;

/*! @brief Display mode, safety stream is the primary input, content stream is the secondary input. */
typedef enum _dpu_display_mode
{
    kDPU_DisplayBlackBackground, /*!< Black background is shown. */
    kDPU_DisplayConstBackground, /*!< Const color background is shown. */
    kDPU_DisplayOnlyPrim,        /*!< Only primary input is shown. */
    kDPU_DisplayOnlySec,         /*!< Only secondary input is shown. */
    kDPU_DisplayPrimOnTop,       /*!< Both inputs overlaid with primary on top. */
    kDPU_DisplaySecOnTop,        /*!< Both inputs overlaid with secondary on top. */
    kDPU_DisplayTest             /*!< White background with test pattern shown. */
} dpu_display_mode_t;

/*! @brief Display mode configuration structure. */
typedef struct _dpu_display_config
{
    bool enablePrimAlpha;                  /*!< Enable primary input alpha for screen composition. */
    bool enableSecAlpha;                   /*!< Enable secondary input alpha for screen composition. */
    dpu_display_mode_t displayMode;        /*!< Display mode. */
    bool enablePrimAlphaInPanic;           /*!< Enable primary input alpha for screen composition in panic mode. */
    bool enableSecAlphaInPanic;            /*!< Enable secondary input alpha for screen composition in panic mode. */
    dpu_display_mode_t displayModeInPanic; /*!< Display mode in panic mode. */
    uint16_t constRed;                     /*!< Const red value, 10-bit. */
    uint16_t constGreen;                   /*!< Const green value, 10-bit. */
    uint16_t constBlue;                    /*!< Const green value, 10-bit. */
    uint8_t constAlpha;                    /*!< Const alpha value, 1-bit. */
    uint16_t primAreaStartX;               /*!< Primary screen upper left corner, x component. 14-bit , start from 1. */
    uint16_t primAreaStartY;               /*!< Primary screen upper left corner, y component. 14-bit, start from 1. */
    uint16_t secAreaStartX; /*!< Secondary screen upper left corner, x component. 14-bit, start from 1. */
    uint16_t secAreaStartY; /*!< Secondary screen upper left corner, y component. 14-bit, start from 1. */
} dpu_display_config_t;

/*! @brief VScaler and HScaler configuration structure. */
typedef struct _dpu_scaler_config
{
    uint32_t srcReg;     /*!< This value will be set to register pixengcfg_slacer_dynamic
                              to set the unit input source, see @ref DPU_MAKE_SRC_REG1.
                              When down-scaling horizontally, the path should be -> HScaler -> VScaler ->,
                              When up-scaling horizontally, the path should be -> VScaler -> HScaler ->.  */
    uint16_t inputSize;  /*!< For HScaler, it is frame width, for VScaler, it is frame height. */
    uint16_t outputSize; /*!< For HScaler, it is frame width, for VScaler, it is frame height. */

} dpu_scaler_config_t;

/*! @brief Signature unit static configuration. */
typedef struct _dpu_signature_config
{
    uint8_t errorThreshold;      /*!< Number of frames with signature violation before signature error is set for an
                                    evaluation window. */
    uint8_t errorResetThreshold; /*!< Number of consecutive frames without signature violation before signature error is
                                   reset for an
                                   evaluation window. */
    uint8_t panicRed;            /*!< Constant color shown in the window when local panic happens. */
    uint8_t panicGreen;          /*!< Constant color shown in the window when local panic happens. */
    uint8_t panicBlue;           /*!< Constant color shown in the window when local panic happens. */
    uint8_t panicAlpha;          /*!< Constant color shown in the window when local panic happens. Must be 0 or 1 */
} dpu_signature_config_t;

/*! @brief Signature unit evaluation window control flags. */
enum _dpu_signature_window_flags
{
    kDPU_SignatureWindowEnableGlobalPanic = DPU_SIG_EVALCONTROL_EnGlobalPanic_MASK,
    /*!< When enabled the window error will activate display stream the panic mode. */
    kDPU_SignatureWindowEnableLocalPanic = DPU_SIG_EVALCONTROL_EnLocalPanic_MASK,
    /*!< When enabled the window error will replace pixels in window to the const panic color. */
    kDPU_SignatureWindowEnableAlphaMask = DPU_SIG_EVALCONTROL_AlphaMask_MASK,
    /*!< When enabled pixels with alpha bit = 0 are ignored for signature computation. */
    kDPU_SignatureWindowInvertAlpha = DPU_SIG_EVALCONTROL_AlphaInv_MASK,
    /*!< When enabled pixels with alpha bit = 1 are ignored for signature computation. */
    kDPU_SignatureWindowDontSkipWindow = DPU_SIG_EVALCONTROL_EnCRC_MASK,
};

/*! @brief Signature unit evaluation window configuration. */
typedef struct _dpu_signature_window_config
{
    uint32_t controlFlags; /*!< Control flags, OR'ed valud of @ref _dpu_signature_window_flags. */
    uint16_t upperLeftX;   /*!< X coordinate of the upper left corner. */
    uint16_t upperLeftY;   /*!< Y coordinate of the upper left corner. */
    uint16_t lowerRightX;  /*!< X coordinate of the lower right corner. */
    uint16_t lowerRightY;  /*!< Y coordinate of the lower right corner. */
} dpu_signature_window_config_t;

/*! @brief Signature unit status. */
enum _dpu_signature_status
{
    kDPU_SignatureIdle  = DPU_SIG_STATUS_StsSigIdle_MASK,  /*!< Signature unit is in idle status. */
    kDPU_SignatureValid = DPU_SIG_STATUS_StsSigValid_MASK, /*!< Signature unit is in idle status. */
};

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @name DPU Initialization and de-initialization
 * @{
 */

/*!
 * @brief Initializes the DPU peripheral.
 *
 * This function ungates the DPU clock.
 *
 * @param base DPU peripheral base address.
 *
 */
void DPU_Init(IRIS_MVPL_Type *base);

/*!
 * @brief Deinitializes the DPU peripheral.
 *
 * This function gates the DPU clock.
 *
 * @param base DPU peripheral base address.
 */
void DPU_Deinit(IRIS_MVPL_Type *base);

/*!
 * @brief Prepare the unit path configuration.
 *
 * The DPU has a default path configuration. Before changing the configuration,
 * this function could be used to break all the original path. This make sure
 * one pixel engine unit is not used in multiple pipelines.
 *
 * @param base DPU peripheral base address.
 */
void DPU_PreparePathConfig(IRIS_MVPL_Type *base);

/* @} */

/*!
 * @name DPU interrupts
 * @{
 */

/*!
 * @brief Enable the selected DPU interrupts.
 *
 * For example, to enable Store9 shadow load interrupt and Store9 frame complete
 * interrupt, use like this:
 *
 * @code
   DPU_EnableInterrupts(DPU, 0, kDPU_Group0Store9ShadowLoadInterrupt |
                                kDPU_Group0Store9FrameCompleteInterrupt);
   @endcode
 *
 * @param base DPU peripheral base address.
 * @param group Interrupt group index.
 * @param mask The interrupts to enable, this is a logical OR of members in
 *             @ref _dpu_interrupt.
 * @note Only the members in the same group could be OR'ed, at the same time,
 * the parameter @p group should be passed in correctly.
 */
void DPU_EnableInterrupts(IRIS_MVPL_Type *base, uint8_t group, uint32_t mask);

/*!
 * @brief Disable the selected DPU interrupts.
 *
 * For example, to disable Store9 shadow load interrupt and Store9 frame complete
 * interrupt, use like this:
 *
 * @code
   DPU_DisableInterrupts(DPU, 0, kDPU_Group0Store9ShadowLoadInterrupt |
                                 kDPU_Group0Store9FrameCompleteInterrupt);
   @endcode
 *
 * @param base DPU peripheral base address.
 * @param group Interrupt group index.
 * @param mask The interrupts to disable, this is a logical OR of members in
 *             @ref _dpu_interrupt.
 * @note Only the members in the same group could be OR'ed, at the same time,
 * the parameter @p group should be passed in correctly.
 */
void DPU_DisableInterrupts(IRIS_MVPL_Type *base, uint8_t group, uint32_t mask);

/*!
 * @brief Get the DPU interrupts pending status.
 *
 * The pending status are returned as mask. For example, to check the Store9
 * shadow load interrupt and Store9 frame complete interrupt pending status,
 * use like this.
 *
 * @code
   uint32_t pendingStatus = DPU_GetInterruptsPendingFlags(DPU, 0);
   if (pendingStatus & kDPU_Group0Store9ShadowLoadInterrupt)
   {
       Store9 shadow load interrupt occurs, handle it.
   }
   if (pendingStatus & kDPU_Group0Store9FrameCompleteInterrupt)
   {
       Store9 frame complete interrupt occurs, handle it.
   }
   @endcode
 *
 * @param base DPU peripheral base address.
 * @param group Interrupt group index.
 * @return The interrupts pending status mask value, see @ref _dpu_interrupt.
 */
uint32_t DPU_GetInterruptsPendingFlags(IRIS_MVPL_Type *base, uint8_t group);

/*!
 * @brief Clear the specified DPU interrupts pending status.
 *
 * For example, to disable Store9 shadow load interrupt and Store9 frame complete
 * interrupt pending status, use like this:
 *
 * @code
   DPU_ClearInterruptsPendingFlags(DPU, 0, kDPU_Group0Store9ShadowLoadInterrupt |
                                           kDPU_Group0Store9FrameCompleteInterrupt);
   @endcode
 *
 * @param base DPU peripheral base address.
 * @param group Interrupt group index.
 * @param mask The interrupt pending flags to clear, this is a logical OR of members in
 *             @ref _dpu_interrupt.
 * @note Only the members in the same group could be OR'ed, at the same time,
 * the parameter @p group should be passed in correctly.
 */
void DPU_ClearInterruptsPendingFlags(IRIS_MVPL_Type *base, uint8_t group, uint32_t mask);

/*!
 * @brief Set the specified DPU interrupts pending status.
 *
 * This function sets the interrupts pending flags, this is a method to trigger
 * interrupts by software.
 *
 * @param base DPU peripheral base address.
 * @param group Interrupt group index.
 * @param mask The interrupt pending flags to set, this is a logical OR of members in
 *             @ref _dpu_interrupt.
 * @note Only the members in the same group could be OR'ed, at the same time,
 * the parameter @p group should be passed in correctly.
 */
void DPU_SetInterruptsPendingFlags(IRIS_MVPL_Type *base, uint8_t group, uint32_t mask);

/*!
 * @brief Mask the selected DPU user interrupts.
 *
 * The only difference between DPU user interrupt and normal interrupt is user
 * interrupts could be masked by @ref DPU_MaskUserInterrupts. All other APIs
 * useage are the same.
 *
 * @param base DPU peripheral base address.
 * @param group Interrupt group index.
 * @param mask The interrupts to mask, this is a logical OR of members in
 *             @ref _dpu_interrupt.
 */
void DPU_MaskUserInterrupts(IRIS_MVPL_Type *base, uint8_t group, uint32_t mask);

/*!
 * @brief Enable the selected DPU user interrupts.
 *
 * The only difference between DPU user interrupt and normal interrupt is user
 * interrupts could be masked by @ref DPU_MaskUserInterrupts.
 *
 * @param base DPU peripheral base address.
 * @param group Interrupt group index.
 * @param mask The interrupts to enable, this is a logical OR of members in
 *             @ref _dpu_interrupt.
 */
void DPU_EnableUserInterrupts(IRIS_MVPL_Type *base, uint8_t group, uint32_t mask);

/*!
 * @brief Disable the selected DPU user interrupts.
 *
 * The only difference between DPU user interrupt and normal interrupt is user
 * interrupts could be masked by @ref DPU_MaskUserInterrupts.
 *
 * @param base DPU peripheral base address.
 * @param group Interrupt group index.
 * @param mask The interrupts to disable, this is a logical OR of members in
 *             @ref _dpu_interrupt.
 */
void DPU_DisableUserInterrupts(IRIS_MVPL_Type *base, uint8_t group, uint32_t mask);

/*!
 * @brief Get the DPU user interrupts pending status.
 *
 * The only difference between DPU user interrupt and normal interrupt is user
 * interrupts could be masked by @ref DPU_MaskUserInterrupts.
 *
 * @param base DPU peripheral base address.
 * @param group Interrupt group index.
 * @return The interrupts pending status mask value, see @ref _dpu_interrupt.
 */
uint32_t DPU_GetUserInterruptsPendingFlags(IRIS_MVPL_Type *base, uint8_t group);

/*!
 * @brief Clear the specified DPU user interrupts pending status.
 *
 * The only difference between DPU user interrupt and normal interrupt is user
 * interrupts could be masked by @ref DPU_MaskUserInterrupts.
 *
 * @param base DPU peripheral base address.
 * @param group Interrupt group index.
 * @param mask The interrupt pending flags to clear, this is a logical OR of members in
 *             @ref _dpu_interrupt.
 */
void DPU_ClearUserInterruptsPendingFlags(IRIS_MVPL_Type *base, uint8_t group, uint32_t mask);

/*!
 * @brief Set the specified DPU user interrupts pending status.
 *
 * The only difference between DPU user interrupt and normal interrupt is user
 * interrupts could be masked by @ref DPU_MaskUserInterrupts.
 *
 * @param base DPU peripheral base address.
 * @param group Interrupt group index.
 * @param mask The interrupt pending flags to set, this is a logical OR of members in
 *             @ref _dpu_interrupt.
 */
void DPU_SetUserInterruptsPendingFlags(IRIS_MVPL_Type *base, uint8_t group, uint32_t mask);

/* @} */

/*!
 * @name Shadow load related.
 * @{
 */

/*!
 * @brief Enable or disable the register shadowing for the DPU process units.
 *
 * For example, to enable the shadowing of all RWS registers of the pipeline with endpoint Store9.
 * @code
   DPU_EnableShadowLoad(DPU, kDPU_PipelineStore9, true);
   @endcode
 *
 * @param base DPU peripheral base address.
 * @param unit The unit whose shadow load to enable or disable, see @ref dpu_unit_t.
 * @param enable True to enable, false to disable.
 * @retval kStatus_Success The shadow load is enabled or disabled successfully.
 * @retval kStatus_InvalidArgument The unit does not support shadow load.
 */
status_t DPU_EnableShadowLoad(IRIS_MVPL_Type *base, dpu_unit_t unit, bool enable);
/* @} */

/*!
 * @name Pipline.
 * @{
 */

/*!
 * @brief Initialize the pipeline.
 *
 * @param base DPU peripheral base address.
 * @param unit The DPU pipeline unit.
 */
void DPU_InitPipeline(IRIS_MVPL_Type *base, dpu_unit_t unit);

/*!
 * @brief Deinitializes the pipeline.
 *
 * Power down the pipeline and disable the shadow load feature.
 *
 * @param base DPU peripheral base address.
 * @param unit The DPU pipeline unit.
 */
void DPU_DeinitPipeline(IRIS_MVPL_Type *base, dpu_unit_t unit);

/*!
 * @brief Trigger the pipeline shadow load.
 *
 * This function triggers the pipeline reconfiguration.
 *
 * @param base DPU peripheral base address.
 * @param unit The DPU pipeline unit.
 */
void DPU_TriggerPipelineShadowLoad(IRIS_MVPL_Type *base, dpu_unit_t unit);

/*!
 * @brief Trigger the pipeline.
 *
 * This function triggers the pipeline sequence complete interrupt. After
 * triggered, this interrupt occurs when the pipeline is empty and no more
 * operations are pending. It will occur immediately, when this is the case
 * already during activation of the trigger. Generally this is used for the
 * blit operation, to make sure all operations finished.
 *
 * @param base DPU peripheral base address.
 * @param unit The DPU pipeline unit.
 */
void DPU_TriggerPipelineCompleteInterrupt(IRIS_MVPL_Type *base, dpu_unit_t unit);

/*!
 * @brief Set the DPU unit input source selection.
 *
 * Sets the DPU unit input source, the input source is controlled by the
 * register \<unit\>_dynamic in "Pixel Engin Top Level". This function writes
 * the register \<unit\>_dynamic directly, please check the reference manual
 * for the register details. This function only changes the input source
 * control bits in register.
 *
 * @param base DPU peripheral base address.
 * @param unit The DPU pipeline unit.
 * @param srcReg The value written to register \<unit\>_dynamic. Could be
 *               generated using @ref DPU_MAKE_SRC_REG1, @ref DPU_MAKE_SRC_REG2,
 *               and @ref DPU_MAKE_SRC_REG3.
 */
void DPU_SetUnitSrc(IRIS_MVPL_Type *base, dpu_unit_t unit, uint32_t srcReg);

/*! @} */

/*!
 * @name Fetch Units
 *
 * The Fetch unit input frame buffer is used like this:
 *
 * @verbatim

                  <----------------- frameWidth -------------------->
               ^  +-------------------------------------------------+
               |  |         ^                  ^           Frame    |
               |  |         |                  |                    |
               |  |         | offsetY          | Clip window offsetY|
               |  |         v                  |                    |
               |  |<------->+------------------|------+----+        |
   frameHeight |  | offsetX | Source Buffer    |      |    |        |
               |  |         |                  v      |    |        |
               |  |         |            +----------------------+   |
               |  |         |            |Clip Window           |   |
               |  | Clip window offsetX  |                      |   |
               |  |<-------------------->|                      |   |
               |  |         |            |                      |   |
               |  |         |            +----------------------+   |
               |  |         |                         |    |        |
               |  |         +-------------------------+----+        |
               |  |                                                 |
               |  |                                                 |
               v  +-------------------------------------------------+
   @endverbatim
 * @{
 */

/*!
 * @brief Get the default configuration for fetch unit.
 *
 * The default value is:
 * @code
    config->srcReg = 0U;
    config->frameHeight = 320U;
    config->frameWidth = 480U;
   @endcode
 *
 * @param config Pointer to the configuration structure.
 */
void DPU_FetchUnitGetDefaultConfig(dpu_fetch_unit_config_t *config);

/*!
 * @brief Initialize the fetch unit.
 *
 * This function initializes the fetch unit for the basic use, for other use
 * case such as arbitrary warping, use the functions @ref DPU_InitFetchUnitWarp
 * and @ref DPU_InitWarpCoordinates.
 *
 * The input source of fetch unit could be:
 *  - @ref kDPU_UnitSrcNone
 *  - @ref kDPU_UnitSrcFetchWarp9
 *  - @ref kDPU_UnitSrcFetchEco2
 *  - @ref kDPU_UnitSrcFetchEco9
 *  - @ref kDPU_UnitSrcFetchEco0
 *  - @ref kDPU_UnitSrcFetchEco1
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be fetch unit here.
 * @param config Pointer to the configuration structure.
 */
void DPU_InitFetchUnit(IRIS_MVPL_Type *base, dpu_unit_t unit, const dpu_fetch_unit_config_t *config);

/*!
 * @brief Set the color palette index width for fetch unit.
 *
 * The palette index width could be 1 to 8. Note the difference between palette
 * index width and the pixel width in framebuffer.
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be FetchDecode or FetchLayer here.
 * @param indexWidth The palette index width.
 * @retval kStatus_Success Initialization success.
 * @retval kStatus_InvalidArgument Wrong argument.
 */
status_t DPU_SetColorPaletteIndexWidth(IRIS_MVPL_Type *base, dpu_unit_t unit, uint8_t indexWidth);

/*!
 * @brief Updates the color palette for fetch unit.
 *
 * This function updates the fetch unit color palette, the palette values specified
 * by @p palette are loaded to fetch unit from @p startIndex. The load count is
 * specified by @p count.
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be FetchDecode or FetchLayer here.
 * @param startIndex The start index of the fetch unit palette to update.
 * @param palette Pointer to the palette.
 * @param count Count of @p palette.
 * @retval kStatus_Success Initialization success.
 * @retval kStatus_InvalidArgument Wrong argument.
 */
status_t DPU_UpdateColorPalette(
    IRIS_MVPL_Type *base, dpu_unit_t unit, uint32_t startIndex, const uint32_t *palette, uint32_t count);

/*!
 * @brief Enable or disable color palette for some sublayer.
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be FetchDecode or FetchLayer here.
 * @param sublayer Sublayer index, should be 0 to 7.
 * @param enable True to enable, false to disable.
 */
void DPU_EnableColorPalette(IRIS_MVPL_Type *base, dpu_unit_t unit, uint8_t sublayer, bool enable);

/*!
 * @brief Get the default configuration structure for arbitrary warping re-sampling coordinates.
 *
 * The default value is:
 * @code
    config->bitsPerPixel = 0U;
    config->strideBytes = 0x500U;
    config->baseAddr = 0U;
    config->frameHeight = 320U;
    config->frameWidth = 480U;
   @endcode
 *
 * @param config Pointer to the configuration structure.
 */
void DPU_CorrdinatesGetDefaultConfig(dpu_coordinates_config_t *config);

/*!
 * @brief Initialize the arbitrary warping coordinates.
 *
 * This function initializes the FetchEco unit, so that it could
 * be used as the arbitrary warping coordinates.
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be FetchEco here.
 * @param config Pointer to the configuration structure.
 * @retval kStatus_Success Initialization success.
 * @retval kStatus_InvalidArgument Wrong argument.
 */
status_t DPU_InitWarpCoordinates(IRIS_MVPL_Type *base, dpu_unit_t unit, const dpu_coordinates_config_t *config);

/*!
 * @brief Get the default warp configuration for FetchWarp unit.
 *
 * The default value is:
 * @code
    config->srcReg = 0U;
    config->frameHeight = 320U;
    config->frameWidth = 480U;
    config->warpBitsPerPixel = 0U;
    config->enableSymmetricOffset = false;
    config->coordMode = kDPU_WarpCoordinateModePNT;
    config->arbStartX = 0U;
    config->arbStartY = 0U;
    config->arbDeltaYY = 0U;
    config->arbDeltaYX = 0U;
    config->arbDeltaXY = 0U;
    config->arbDeltaXX = 0U;
   @endcode
 *
 * @param config Pointer to the configuration structure.
 */
void DPU_FetcUnitGetDefaultWarpConfig(dpu_warp_config_t *config);

/*!
 * @brief Initialize the Warp function for FetchWarp unit.
 *
 * This function initializes the FetchWarp unit for the arbitrary warping.
 *
 * The valid source of fetch warp unit could be:
 *  - @ref kDPU_UnitSrcNone
 *  - @ref kDPU_UnitSrcFetchEco2
 *  - @ref kDPU_UnitSrcFetchEco9
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be FetchWarp unit here.
 * @param config Pointer to the configuration structure.
 * @retval kStatus_Success Initialization success.
 * @retval kStatus_InvalidArgument Wrong argument.
 */
status_t DPU_InitFetchUnitWarp(IRIS_MVPL_Type *base, dpu_unit_t unit, const dpu_warp_config_t *config);

/*!
 * @brief Get default configuration structure for fetch unit source buffer.
 *
 * The default value is:
 * @code
    config->baseAddr = 0U;
    config->strideBytes = 0x500U;
    config->bitsPerPixel = 32U;
    config->pixelFormat = kDPU_PixelFormatARGB8888;
    config->bufferHeight = 0U;
    config->bufferWidth = 0U;
    config->constColor = DPU_MAKE_CONST_COLOR(0, 0, 0, 0);
   @endcode
 *
 * @param config Pointer to the configuration structure.
 */
void DPU_SrcBufferGetDefaultConfig(dpu_src_buffer_config_t *config);

/*!
 * @brief Set the fetch unit sublayer source buffer.
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be fetch unit here.
 * @param sublayer Sublayer index, should be 0 to 7.
 * @param config Pointer to the configuration structure.
 * @retval kStatus_Success Initialization success.
 * @retval kStatus_InvalidArgument Wrong argument.
 */
status_t DPU_SetFetchUnitSrcBufferConfig(IRIS_MVPL_Type *base,
                                         dpu_unit_t unit,
                                         uint8_t sublayer,
                                         const dpu_src_buffer_config_t *config);

/*!
 * @brief Set the fetch unit sublayer source buffer base address.
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be fetch unit here.
 * @param sublayer Sublayer index, should be 0 to 7.
 * @param baseAddr Source buffer base address.
 */
void DPU_SetFetchUnitSrcBufferAddr(IRIS_MVPL_Type *base, dpu_unit_t unit, uint8_t sublayer, uint32_t baseAddr);

/*!
 * @brief Set the fetch unit frame size.
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be fetch unit here.
 * @param height Frame height.
 * @param width Frame width.
 */
void DPU_SetFetchUnitFrameSize(IRIS_MVPL_Type *base, dpu_unit_t unit, uint16_t height, uint16_t width);

/*!
 * @brief Set the fetch unit sublayer offset.
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be fetch unit here.
 * @param sublayer Sublayer index, should be 0 to 7.
 * @param offsetX Horizontal offset.
 * @param offsetY Vertical offset.
 */
void DPU_SetFetchUnitOffset(
    IRIS_MVPL_Type *base, dpu_unit_t unit, uint8_t sublayer, uint16_t offsetX, uint16_t offsetY);

/*!
 * @brief Enable or disable fetch unit sublayer source buffer.
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be fetch unit here.
 * @param sublayer Sublayer index, should be 0 to 7.
 * @param enable True to enable, false to disable.
 */
void DPU_EnableFetchUnitSrcBuffer(IRIS_MVPL_Type *base, dpu_unit_t unit, uint8_t sublayer, bool enable);

/*!
 * @brief Get default configuration structure for clip window.
 *
 * The default value is:
 * @code
    config->windowOffsetX = 0U;
    config->windowOffsetY = 0U;
    config->windowHeight = 0U;
    config->windowWidth = 0U;
   @endcode
 *
 * @param config Pointer to the configuration structure.
 */
void DPU_ClipWindowGetDefaultConfig(dpu_clip_window_config_t *config);

/*!
 * @brief Set the fetch unit sublayer clip window.
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be fetch unit here.
 * @param sublayer Sublayer index, should be 0 to 7.
 * @param config Pointer to the configuration structure.
 */
void DPU_SetFetchUnitClipWindowConfig(IRIS_MVPL_Type *base,
                                      dpu_unit_t unit,
                                      uint8_t sublayer,
                                      const dpu_clip_window_config_t *config);

/*!
 * @brief Enable or disable the fetch unit sublayer clip window.
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be fetch unit here.
 * @param sublayer Sublayer index, should be 0 to 7.
 * @param enable True to enable, false to disable.
 */
void DPU_EnableFetchUnitClipWindow(IRIS_MVPL_Type *base, dpu_unit_t unit, uint8_t sublayer, bool enable);

/*!
 * @brief Set the fetch unit clip color mode.
 *
 * This function selects which color to take for pixels that do not lie inside
 * the clip window of any layer.
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be fetch unit here.
 * @param clipColorMode Select null color or use sublayer color.
 * @param sublayer Select which sublayer's color to use when @p clipColorMode
 * is @ref kDPU_ClipColorSublayer.
 */
void DPU_SetFetchUnitClipColor(IRIS_MVPL_Type *base,
                               dpu_unit_t unit,
                               dpu_clip_color_mode_t clipColorMode,
                               uint8_t sublayer);

/* @} */

/*!
 * @name ExtDst Units
 * @{
 */

/*!
 * @brief Initialize the ExtDst unit.
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be ExtDst unit here.
 * @param srcReg Input source selecte register value, pixencfg_extdstX_dynamic see @ref DPU_MAKE_SRC_REG1.
 * The valid source:
 * - @ref kDPU_UnitSrcNone
 * - @ref kDPU_UnitSrcBlitBlend9
 * - @ref kDPU_UnitSrcConstFrame0
 * - @ref kDPU_UnitSrcConstFrame1
 * - @ref kDPU_UnitSrcConstFrame4
 * - @ref kDPU_UnitSrcConstFrame5
 * - @ref kDPU_UnitSrcHScaler4
 * - @ref kDPU_UnitSrcVScaler4
 * - @ref kDPU_UnitSrcHScaler5
 * - @ref kDPU_UnitSrcVScaler5
 * - @ref kDPU_UnitSrcLayerBlend0
 * - @ref kDPU_UnitSrcLayerBlend1
 * - @ref kDPU_UnitSrcLayerBlend2
 * - @ref kDPU_UnitSrcLayerBlend3
 */
void DPU_InitExtDst(IRIS_MVPL_Type *base, dpu_unit_t unit, uint32_t srcReg);

/* @} */

/*!
 * @name Store Units
 *
 * The Store unit output buffer is like this:
 *
 * @verbatim

                   <-------------------- Stride -------------------->
                   <------------- bufferWidth ---------------->
                ^  +------------------------------------------------+
                |  |         ^                                |     |
                |  |         |             Destination Buffer |     |
                |  |         | offsetY                        |     |
                |  |         v                                |     |
                |  |<------->+===============+                |     |
   bufferHeight |  | offsetX "               "                |     |
                |  |         "  Input Frame  "                |     |
                |  |         "               "                |     |
                |  |         +===============+                |     |
                |  |                                          |     |
                |  |                                          |     |
                |  |                                          |     |
                v  +------------------------------------------------+
   @endverbatim
 *
 * @{
 */

/*!
 * @brief Initialize the Store unit.
 *
 * The valid input source of the store unit could be:
 *  - @ref kDPU_UnitSrcNone
 *  - @ref kDPU_UnitSrcHScaler9
 *  - @ref kDPU_UnitSrcVScaler9
 *  - @ref kDPU_UnitSrcVScaler9
 *  - @ref kDPU_UnitSrcFilter9
 *  - @ref kDPU_UnitSrcBlitBlend9
 *  - @ref kDPU_UnitSrcFetchDecode9
 *  - @ref kDPU_UnitSrcFetchWarp9
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be Store unit here.
 * @param srcReg Input source selecte register value, pixencfg_extdstX_dynamic
 * see @ref DPU_MAKE_SRC_REG1.
 */
void DPU_InitStore(IRIS_MVPL_Type *base, dpu_unit_t unit, uint32_t srcReg);

/*!
 * @brief Set the Store unit Destination buffer configuration.
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be Store unit here.
 * @param config Pointer to the configuration.
 * @retval kStatus_Success Initialization success.
 * @retval kStatus_InvalidArgument Wrong argument.
 */
status_t DPU_SetStoreDstBufferConfig(IRIS_MVPL_Type *base, dpu_unit_t unit, const dpu_dst_buffer_config_t *config);

/*!
 * @brief Get the default configuration for Store unit.
 *
 * The default value is:
 * @code
    config->baseAddr = 0U;
    config->strideBytes = 0x500U;
    config->bitsPerPixel = 32U,
    config->pixelFormat = kDPU_PixelFormatARGB8888;
    config->bufferHeight = 0U;
    config->bufferWidth = 0U;
   @endcode
 * @param config Pointer to the configuration.
 */
void DPU_DstBufferGetDefaultConfig(dpu_dst_buffer_config_t *config);

/*!
 * @brief Set the Store unit Destination buffer base address.
 *
 * This function is run time used for better performance.
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be Store unit here.
 * @param baseAddr Base address of the Destination buffer to set.
 */
void DPU_SetStoreDstBufferAddr(IRIS_MVPL_Type *base, dpu_unit_t unit, uint32_t baseAddr);

/*!
 * @brief Set the Store unit output offset.
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be Store unit here.
 * @param offsetX Horizontal offset.
 * @param offsetY Vertical offset.
 * @note The horizontal offset has limitations for some formats. It must be a multiple of
 *   - 8 for 1 bpp buffers
 *   - 4 for 2 bpp and 18 bpp buffers
 *   - 2 for 4 bpp buffers
 */
void DPU_SetStoreOffset(IRIS_MVPL_Type *base, dpu_unit_t unit, uint16_t offsetX, uint16_t offsetY);

/*!
 * @brief Start the Store unit.
 *
 * This function starts the Store unit to save the frame to output buffer. When
 * the frame store completed, the interrupt flag @ref kDPU_Group0Store9FrameCompleteInterrupt
 * asserts.
 *
 * This is an example shows how to use Store unit:
 *
 * @code
   Initialize the Store unit, use FetchDecode9 output as its input.
   DPU_InitStore(DPU, kDPU_Store9, DPU_MAKE_SRC_REG1(kDPU_UnitSrcFetchDecode9));

   Configure the Store unit output buffer.
   DPU_SetStoreDstBufferConfig(DPU, kDPU_Store9, &DstBufferConfig);

   Configure FetchDecode9 unit, including source buffer setting and so on.
   ...

   Initialize the Store9 pipeline
   DPU_InitPipeline(DPU, kDPU_PipelineStore9);

   DPU_ClearUserInterruptsPendingFlags(DPU, kDPU_Group0Store9ShadowLoadInterrupt);

   Trigger the shadow load
   DPU_TriggerPipelineShadowLoad(DPU, kDPU_PipelineStore9);

   DPU_ClearUserInterruptsPendingFlags(DPU, kDPU_Group0Store9FrameCompleteInterrupt);

   Start the Store9 to convert and output.
   DPU_StartStore(DPU, kDPU_Store9);

   Wait for Store 9 completed, this could also be monitored by interrupt.
   while (!(kDPU_Group0Store9FrameCompleteInterrupt & DPU_GetUserInterruptsPendingFlags(DPU, 0))
   {
   }
   @endcode
 *
 * For better performance, it is allowed to set next operation while current is still in progress.
 * Upper layer could set next operation immediately after shadow load finished.
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be Store unit here.
 */
void DPU_StartStore(IRIS_MVPL_Type *base, dpu_unit_t unit);
/* @} */

/*!
 * @name Rop units
 *
 * Rop unit combines up to three input frames to a single output frame, all having
 * the same dimension. It supports:
 *
 * 1. Logic Operations
 * Each bit of the RGBA input code is combined with the same bit from the same pixel
 * from the other inputs by any logical operation (= 3 to 1 bit function). The input
 * and output relationship is:
 * @verbatim

     Tertiary Input  | Secondary Input | Primary Input |       Output
   ==========================================================================
           0         |        0        |       0       |  operation index[0]
   --------------------------------------------------------------------------
           0         |        0        |       1       |  operation index[1]
   --------------------------------------------------------------------------
           0         |        1        |       0       |  operation index[2]
   --------------------------------------------------------------------------
           0         |        1        |       1       |  operation index[3]
   --------------------------------------------------------------------------
           1         |        0        |       0       |  operation index[4]
   --------------------------------------------------------------------------
           1         |        0        |       1       |  operation index[5]
   --------------------------------------------------------------------------
           1         |        1        |       0       |  operation index[6]
   --------------------------------------------------------------------------
           1         |        1        |       1       |  operation index[7]
   ==========================================================================
   @endverbatim
 * 2. Arithmetic Operations
 * Input RGBA codes can simply be added for each pixel, optionally with an factor
 * 0.5 being applied for averaging two frames.
 *
 * @{
 */

/*!
 * @brief Initialize the ROp unit.
 *
 * The primary input source of the unit could be:
 *   - @ref kDPU_UnitSrcNone
 *   - @ref kDPU_UnitSrcFetchDecode9
 *   - @ref kDPU_UnitSrcFetchWarp9
 *
 * The secondary input source of the unit could be:
 *   - @ref kDPU_UnitSrcNone
 *   - @ref kDPU_UnitSrcFetchEco9
 *
 * The tert input source of the unit could be:
 *   - @ref kDPU_UnitSrcNone
 *   - @ref kDPU_UnitSrcFetchDecode9
 *   - @ref kDPU_UnitSrcFetchWarp9
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be Rop unit here.
 * @param srcReg Unit source selection, see @ref DPU_MAKE_SRC_REG3.
 */
void DPU_InitRop(IRIS_MVPL_Type *base, dpu_unit_t unit, uint32_t srcReg);

/*!
 * @brief Get the default ROp unit configuration.
 *
 * The default configuration is:
 *
 * @code
    config->controlFlags = 0U;
    config->alphaIndex = 0U;
    config->blueIndex = 0U;
    config->greenIndex = 0U;
    config->redIndex = 0U;
   @endcode
 * @param config Pointer to the configuration structure.
 */
void DPU_RopGetDefaultConfig(dpu_rop_config_t *config);

/*!
 * @brief Set the ROp unit configuration.
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be Rop unit here.
 * @param config Pointer to the configuration structure.
 */
void DPU_SetRopConfig(IRIS_MVPL_Type *base, dpu_unit_t unit, const dpu_rop_config_t *config);

/*!
 * @brief Enable or disable the ROp unit.
 *
 * If disabled, only the primary input is output.
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be Rop unit here.
 * @param enable Pass true to enable, false to disable.
 */
void DPU_EnableRop(IRIS_MVPL_Type *base, dpu_unit_t unit, bool enable);

/* @} */

/*!
 * @name BlitBlend units
 * @{
 */

/*!
 * @brief Initialize the BlitBlend unit.
 *
 * The valid input primary source could be:
 * - @ref kDPU_UnitSrcNone
 * - @ref kDPU_UnitSrcHScaler9
 * - @ref kDPU_UnitSrcVScaler9
 * - @ref kDPU_UnitSrcFilter9
 * - @ref kDPU_UnitSrcRop9
 *
 * The valid input secondary source could be:
 * - @ref kDPU_UnitSrcNone
 * - @ref kDPU_UnitSrcFetchDecode9
 * - @ref kDPU_UnitSrcFetchWarp9
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be BlitBlend unit here.
 * @param srcReg Unit source selection, see @ref DPU_MAKE_SRC_REG2.
 */
void DPU_InitBlitBlend(IRIS_MVPL_Type *base, dpu_unit_t unit, uint32_t srcReg);

/*!
 * @brief Get the default BlitBlend unit configuration.
 *
 * The default configuration is:
 * @code
    config->neutralBorderRightPixels = 0U;
    config->neutralBorderLeftPixels = 0U;
    config->neutralBorderMode = kDPU_BlitBlendNeutralBorderPrim;
    config->constColor = DPU_MAKE_CONST_COLOR(0, 0, 0, 0);
    config->redBlendFuncSrc = kDPU_BlitBlendFuncGlSrcColor;
    config->redBlendFuncDst = kDPU_BlitBlendFuncGlSrcColor;
    config->greenBlendFuncSrc = kDPU_BlitBlendFuncGlSrcColor;
    config->greenBlendFuncDst = kDPU_BlitBlendFuncGlSrcColor;
    config->blueBlendFuncSrc = kDPU_BlitBlendFuncGlSrcColor;
    config->blueBlendFuncDst = kDPU_BlitBlendFuncGlSrcColor;
    config->alphaBlendFuncSrc = kDPU_BlitBlendFuncGlSrcColor;
    config->alphaBlendFuncDst = kDPU_BlitBlendFuncGlSrcColor;
    config->redBlendMode = kDPU_BlitBlendModeGlFuncAdd;
    config->greenBlendMode = kDPU_BlitBlendModeGlFuncAdd;
    config->blueBlendMode = kDPU_BlitBlendModeGlFuncAdd;
    config->alphaBlendMode = kDPU_BlitBlendModeGlFuncAdd;
   @endcode
 * @param config Pointer to the configuration structure.
 */
void DPU_BlitBlendGetDefaultConfig(dpu_blit_blend_config_t *config);

/*!
 * @brief Set the BlitBlend unit configuration.
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be BlitBlend unit here.
 * @param config Pointer to the configuration structure.
 */
void DPU_SetBlitBlendConfig(IRIS_MVPL_Type *base, dpu_unit_t unit, const dpu_blit_blend_config_t *config);

/*!
 * @brief Enable or disable the BlitBlend unit.
 *
 * The BlitBlend unit could be runtime enabled or disabled, when disabled, the
 * primary input is output directly.
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be BlitBlend unit here.
 * @param enable Pass true to enable, false to disable.
 */
void DPU_EnableBlitBlend(IRIS_MVPL_Type *base, dpu_unit_t unit, bool enable);

/* @} */

/*!
 * @name LayerBlend units
 * @{
 */

/*!
 * @brief Get default configuration structure for LayerBlend.
 *
 * The default value is:
 * @code
    config->constAlpha = 0U;
    config->secAlphaBlendMode = kDPU_BlendOne;
    config->primAlphaBlendMode = kDPU_BlendZero;
    config->secColorBlendMode = kDPU_BlendOne;
    config->primColorBlendMode = kDPU_BlendZero;
    config->enableAlphaMask = true;
    config->alphaMaskMode = kDPU_AlphaMaskPrim;
   @endcode
 *
 * @param config Pointer to the configuration structure.
 */
void DPU_LayerBlendGetDefaultConfig(dpu_layer_blend_config_t *config);

/*!
 * @brief Initialize the LayerBlend.
 *
 * The valid primary source:
 * - @ref kDPU_UnitSrcNone
 * - @ref kDPU_UnitSrcConstFrame0
 * - @ref kDPU_UnitSrcConstFrame1
 * - @ref kDPU_UnitSrcConstFrame4
 * - @ref kDPU_UnitSrcConstFrame5
 * - @ref kDPU_UnitSrcHScaler4
 * - @ref kDPU_UnitSrcVScaler4
 * - @ref kDPU_UnitSrcHScaler5
 * - @ref kDPU_UnitSrcVScaler5
 * - @ref kDPU_UnitSrcMatrix4
 * - @ref kDPU_UnitSrcMatrix5
 * - @ref kDPU_UnitSrcLayerBlend0
 * - @ref kDPU_UnitSrcLayerBlend1
 * - @ref kDPU_UnitSrcLayerBlend2
 * - @ref kDPU_UnitSrcLayerBlend3
 *
 * The valid secondary source:
 * - @ref kDPU_UnitSrcNone
 * - @ref kDPU_UnitSrcConstFrame0
 * - @ref kDPU_UnitSrcConstFrame1
 * - @ref kDPU_UnitSrcConstFrame4
 * - @ref kDPU_UnitSrcConstFrame5
 * - @ref kDPU_UnitSrcHScaler4
 * - @ref kDPU_UnitSrcVScaler4
 * - @ref kDPU_UnitSrcHScaler5
 * - @ref kDPU_UnitSrcVScaler5
 * - @ref kDPU_UnitSrcMatrix4
 * - @ref kDPU_UnitSrcMatrix5
 * - @ref kDPU_UnitSrcLayerBlend0
 * - @ref kDPU_UnitSrcLayerBlend1
 * - @ref kDPU_UnitSrcLayerBlend2
 * - @ref kDPU_UnitSrcLayerBlend3
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be LayerBlend unit here.
 * @param srcReg Unit source selection, see @ref DPU_MAKE_SRC_REG2.
 */
void DPU_InitLayerBlend(IRIS_MVPL_Type *base, dpu_unit_t unit, uint32_t srcReg);

/*!
 * @brief Set the LayerBlend unit configuration.
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be LayerBlend unit here.
 * @param config Pointer to the configuration structure.
 */
void DPU_SetLayerBlendConfig(IRIS_MVPL_Type *base, dpu_unit_t unit, const dpu_layer_blend_config_t *config);

/*!
 * @brief Enable or disable the LayerBlend unit.
 *
 * If enabled, the blend result is output, otherwise, the primary input is output.
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be LayerBlend unit here.
 * @param enable Pass true to enable, false to disable.
 */
void DPU_EnableLayerBlend(IRIS_MVPL_Type *base, dpu_unit_t unit, bool enable);

/* @} */

/*!
 * @name ConstFrame units
 * @{
 */

/*!
 * @brief Initialize the ConstFrame unit.
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be ConstFrame unit here.
 */
void DPU_InitConstFrame(IRIS_MVPL_Type *base, dpu_unit_t unit);

/*!
 * @brief Get default configuration structure for ConstFrame unit.
 *
 * The default value is:
   @code
    config->frameHeight = 320U;
    config->frameWidth = 480U;
    config->constColor = DPU_MAKE_CONST_COLOR(0xFF, 0xFF, 0xFF, 0xFF);
   @endcode
 *
 * @param config Pointer to the configuration structure.
 */
void DPU_ConstFrameGetDefaultConfig(dpu_const_frame_config_t *config);

/*!
 * @brief Set the ConstFrame unit configuration.
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be ConstFrame unit here.
 * @param config Pointer to the configuration structure.
 */
void DPU_SetConstFrameConfig(IRIS_MVPL_Type *base, dpu_unit_t unit, const dpu_const_frame_config_t *config);

/* @} */

/*!
 * @name VScaler and HScaler units
 *
 * @note When both horizontal and vertical scaling is active, then the sequence
 * of both units in the Pixelbus configuration should be
 *
 *     -> HScaler -> VScaler ->    when down-scaling horizontally
 *     -> VScaler -> HScaler ->    when up-scaling horizontally
 *
 * @{
 */

/*!
 * @brief Initialize the VScaler or HScaler unit.
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be HScaler or VScaler unit here.
 */
void DPU_InitScaler(IRIS_MVPL_Type *base, dpu_unit_t unit);

/*!
 * @brief Get default configuration structure for VScaler and HScaler.
 *
 * The default value is:
   @code
    config->srcReg = 0U;
    config->inputSize = 0U;
    config->outputSize = 0U;
   @endcode
 *
 * @param config Pointer to the configuration structure.
 */
void DPU_ScalerGetDefaultConfig(dpu_scaler_config_t *config);

/*!
 * @brief Set the VScaler or HScaler units configuration.
 *
 * The valid input source could be:
 *  - @ref kDPU_UnitSrcNone
 *  - @ref kDPU_UnitSrcFetchDecode0
 *  - @ref kDPU_UnitSrcMatrix4
 *  - @ref kDPU_UnitSrcVScaler4
 *  - @ref kDPU_UnitSrcHScaler4
 *  - @ref kDPU_UnitSrcFetchDecode1
 *  - @ref kDPU_UnitSrcMatrix5
 *  - @ref kDPU_UnitSrcVScaler5
 *  - @ref kDPU_UnitSrcHScaler5
 *  - @ref kDPU_UnitSrcVScaler9
 *  - @ref kDPU_UnitSrcHScaler9
 *  - @ref kDPU_UnitSrcFilter9
 *  - @ref kDPU_UnitSrcMatrix9
 *
 * @param base DPU peripheral base address.
 * @param unit DPU unit, see @ref dpu_unit_t, must be HScaler or VScaler unit here.
 * @param config Pointer to the configuration structure.
 */
void DPU_SetScalerConfig(IRIS_MVPL_Type *base, dpu_unit_t unit, const dpu_scaler_config_t *config);

/* @} */

/*!
 * @name Display engine
 * @{
 */

/*!
 * @brief Get default configuration structure for display mode.
 *
 * The default value is:
 * @code
    config->flags = kDPU_DisplayDeActiveHigh;
    config->width = 320U;
    config->hsw = 32U;
    config->hfp = 8U;
    config->hbp = 40U;
    config->height = 240U;
    config->vsw = 4U;
    config->vfp = 13U;
    config->vbp = 6U;
   @endcode
 *
 * @param config Pointer to the configuration structure.
 */
void DPU_DisplayTimingGetDefaultConfig(dpu_display_timing_config_t *config);

/*!
 * @brief Initialize the display timing.
 *
 * @param base DPU peripheral base address.
 * @param displayIndex Index of the display.
 * @param config Pointer to the configuration structure.
 */
void DPU_InitDisplayTiming(IRIS_MVPL_Type *base, uint8_t displayIndex, const dpu_display_timing_config_t *config);

/*!
 * @brief Get default configuration structure for display frame mode.
 *
 * The default value is:
   @code
    config->enablePrimAlpha = false;
    config->enableSecAlpha = false;
    config->displayMode = kDPU_DisplayTest;
    config->enablePrimAlphaInPanic = false;
    config->enableSecAlphaInPanic = false;
    config->displayModeInPanic = kDPU_DisplayTest;
    config->constRed = 0x3FFU;
    config->constGreen = 0x3FFU;
    config->constBlue = 0x3FFU;
    config->constAlpha = 1U;
    config->primAreaStartX = 1U;
    config->primAreaStartY = 1U;
    config->secAreaStartX = 1U;
    config->secAreaStartY = 1U;
   @endcode
 *
 * @param config Pointer to the configuration structure.
 */
void DPU_DisplayGetDefaultConfig(dpu_display_config_t *config);

/*!
 * @brief Set the display mode.
 *
 * @param base DPU peripheral base address.
 * @param displayIndex Index of the display.
 * @param config Pointer to the configuration structure.
 */
void DPU_SetDisplayConfig(IRIS_MVPL_Type *base, uint8_t displayIndex, const dpu_display_config_t *config);

/*!
 * @brief Start the display.
 *
 * @param base DPU peripheral base address.
 * @param displayIndex Index of the display.
 */
void DPU_StartDisplay(IRIS_MVPL_Type *base, uint8_t displayIndex);

/*!
 * @brief Stop the display.
 *
 * This function stops the display and wait the sequence complete.
 *
 * @param base DPU peripheral base address.
 * @param displayIndex Index of the display.
 */
void DPU_StopDisplay(IRIS_MVPL_Type *base, uint8_t displayIndex);

/*!
 * @brief Clear the FrameGen unit status flags.
 *
 * @param base DPU peripheral base address.
 * @param displayIndex Display index.
 * @param interruptIndex Interrupt index, there could be 4 interrupts for each display.
 * @param intConfig Interrupt mode, could be one of DPU_FRAME_GEN_INT_DISABLE,
 * DPU_FRAME_GEN_INT_PER_LINE, and DPU_FRAME_GEN_INT_PER_FRAME.
 */
void DPU_SetFrameGenInterruptConfig(IRIS_MVPL_Type *base,
                                    uint8_t displayIndex,
                                    uint8_t interruptIndex,
                                    uint32_t intConfig);

/*!
 * @brief Trigger the display stream shadow load token.
 *
 * Trigger the display stream shadow load token, then the shadow register will
 * be loaded at the begining of next frame.
 *
 * @param base DPU peripheral base address.
 * @param displayIndex Display index.
 */
void DPU_TriggerDisplayShadowLoad(IRIS_MVPL_Type *base, uint8_t displayIndex);

/* @} */

/*!
 * @name Signature unit
 *
 * The Signature unit could compute the CRC value of interested region and compare
 * to the reference value to detect incorrect display output.
 *
 * Up to 8 evaluation windows can be setup. Signature computation and reference check
 * is done individually for each window.
 *
 * A pixel of the input frame does not contribute to more than one window. In case of
 * overlapping windows, the window with larger index is on top.
 *
 * Alpha mask could be involved into the signature evaluation, thus any kind of shape
 * could be monitored.
 *
 * Note that the mask is considered for checksum computation only, not for assignment
 * of individual pixels to a certain evaluation window. So, a non-rectangular overlap
 * between different windows is not possible.
 *
 * An evaluation window could be configured as skipped. This provides another method for
 * monitoring non-rectangular windows. For example:
 *
 * @verbatim
     +------------------------------------------------+
     |                                                |
     |                                                |
     |    +-------------------+                       |
     |    | Window 0 xxxxxxxxx|                       |
     |    |xxxxxxxxxxxxxxxxxxx|                       |
     |    |xxxxxxxx+-------------------------------+  |
     |    |xxxxxxxx|  Window 1 (Skipped)           |  |
     |    |xxxxxxxx|                               |  |
     |    +--------|                               |  |
     |             |                               |  |
     |             +-------------------------------+  |
     |                                                |
     +------------------------------------------------+
   @endverbatim
 *
 * In this example, windows 1 is skipped, in this case, only the shadow part of
 * window 0 is monitored.
 *
 * @{
 */

/*!
 * @brief Get Signature unit default configuration.
 *
 * The default configuration is:
 *
 * @code
    config->errorThreshold = 0U;
    config->errorResetThreshold = 8U;
    config->panicRed = 0U;
    config->panicGreen = 0U;
    config->panicBlue = 0U;
    config->panicAlpha = 0U;
   @endcode
 * @param config Pointer to the configuration.
 */
void DPU_SignatureGetDefaultConfig(dpu_signature_config_t *config);

/*!
 * @brief Initialize the Signature unit.
 *
 * @param base DPU peripheral base address.
 * @param displayIndex Display index.
 * @param config Pointer to the configuration.
 */
void DPU_InitSignature(IRIS_MVPL_Type *base, uint8_t displayIndex, const dpu_signature_config_t *config);

/*!
 * @brief Get Signature unit validate window default configuration.
 *
 * The default configuration is:
 *
 * @code
    config->controlFlags = 0U;
    config->upperLeftX = 0U;
    config->upperLeftY = 0U;
    config->lowerRightX = 0U;
    config->lowerRightY = 0U;
   @endcode
 *
 * @param config Pointer to the configuration.
 */
void DPU_SignatureWindowGetDefaultConfig(dpu_signature_window_config_t *config);

/*!
 * @brief Set the Signature unit evaluation window configuration.
 *
 * @param base DPU peripheral base address.
 * @param displayIndex Display index.
 * @param windowIndex Evaluation window index, should be 0 to 7.
 * @param config Pointer to the configuration.
 */
void DPU_SetSignatureWindowConfig(IRIS_MVPL_Type *base,
                                  uint8_t displayIndex,
                                  uint8_t windowIndex,
                                  const dpu_signature_window_config_t *config);

/*!
 * @brief Enable or disable the Signature unit evaluation window CRC value computation.
 *
 * When enabled, a CRC signature is computed for all pixels inside this evaluation window,
 * When disabled, the internal status for this window is reset (StsSigError bit and frame counters)
 *
 * @param base DPU peripheral base address.
 * @param displayIndex Display index.
 * @param windowIndex Evaluation window index, should be 0 to 7.
 * @param enable Pass true to enable, false to disable.
 */
void DPU_EnableSignatureWindowCompute(IRIS_MVPL_Type *base, uint8_t displayIndex, uint8_t windowIndex, bool enable);

/*!
 * @brief Enable or disable the Signature unit evaluation window CRC value check.
 *
 * When enabled, the measured signature is checked against a reference value.
 *
 * @param base DPU peripheral base address.
 * @param displayIndex Display index.
 * @param windowIndex Evaluation window index, should be 0 to 7.
 * @param enable Pass true to enable, false to disable.
 */
void DPU_EnableSignatureWindowCheck(IRIS_MVPL_Type *base, uint8_t displayIndex, uint8_t windowIndex, bool enable);

/*!
 * @brief Get the measured signature value of the evaluation window.
 *
 * @param base DPU peripheral base address.
 * @param displayIndex Display index.
 * @param windowIndex Evaluation window index, should be 0 to 7.
 * @param redCRC Measured signature value of red.
 * @param greenCRC Measured signature value of green.
 * @param blueCRC Measured signature value of blue.
 */
void DPU_GetSignatureWindowCrc(IRIS_MVPL_Type *base,
                               uint8_t displayIndex,
                               uint8_t windowIndex,
                               uint32_t *redCRC,
                               uint32_t *greenCRC,
                               uint32_t *blueCRC);

/*!
 * @brief Set the reference signature value of the evaluation window.
 *
 * @param base DPU peripheral base address.
 * @param displayIndex Display index.
 * @param windowIndex Evaluation window index, should be 0 to 7.
 * @param redCRC Reference signature value of red.
 * @param greenCRC Referencesignature value of green.
 * @param blueCRC Reference signature value of blue.
 */
void DPU_SetSignatureWindowRefCrc(IRIS_MVPL_Type *base,
                                  uint8_t displayIndex,
                                  uint8_t windowIndex,
                                  uint32_t redCRC,
                                  uint32_t greenCRC,
                                  uint32_t blueCRC);

/*!
 * @brief Get the signature unit status.
 *
 * This function returns the signature unit status. The return value could be
 * compared to check the status defined in @ref _dpu_signature_status.
 * For example:
 *
 * @code
   uint32_t status = DPU_GetSignatureStatus(DPU, 0);

   if (kDPU_SignatureValid & status)
   {
       DPU_GetSignatureWindowCrc(...);
   }
   @endcode
 *
 * The error flags are also returned as an mask value, upper layer could get specific
 * window status by checking the returned bit accordingly. For example,
 *
 * @code
   uint32_t status = DPU_GetSignatureStatus(DPU, 0);

   if ((1<<3) & status)
   {
       Window 3 error detected.
   }

   if ((1<<5) & status)
   {
       Window 5 error detected.
   }

   @endcode
 *
 * @param base DPU peripheral base address.
 * @param displayIndex Display index.
 * @return Mask value of status.
 */
uint32_t DPU_GetSignatureStatus(IRIS_MVPL_Type *base, uint8_t displayIndex);

/*!
 * @brief Trigger the Signature unit configuration shadow load.
 *
 * When new configuration set by @ref DPU_SetSignatureWindowConfig,
 * @ref DPU_EnableSignatureWindowCheck, @ref DPU_EnableSignatureWindowCompute,
 * and @ref DPU_SetSignatureWindowRefCrc, use this function to trigger the
 * shadow load, then the new configuration takes effect.
 *
 * Upper layer should monitor the @ref kDPU_Group0Sig0ShadowLoadInterrupt or
 * @ref kDPU_Group1Sig1ShadowLoadInterrupt to wait shadow load finished. New
 * configurations should only be set after shadow load finished.
 *
 * @param base DPU peripheral base address.
 * @param displayIndex Display index.
 */
void DPU_TriggerSignatureShadowLoad(IRIS_MVPL_Type *base, uint8_t displayIndex);

/* @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/* @} */

#endif /* _FSL_DPU_H_ */
