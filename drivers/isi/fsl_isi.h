/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_ISI_H_
#define _FSL_ISI_H_

#include "fsl_common.h"

#define ISI_ROI_NUM 4U /* The Number of "Region Of Interest (ROI)" */

/*!
 * @addtogroup isi
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief ISI driver version */
#define FSL_ISI_DRIVER_VERSION (MAKE_VERSION(2, 0, 1)) /*!< Version 2.0.1. */
/*@}*/

/*! @brief ISI interrupts. */
enum _isi_interrupt
{
    kISI_MemReadCompletedInterrupt = ISI_CHNL_IER_MEM_RD_DONE_EN_MASK, /*!< Input memory read completed. */
    kISI_LineReceivedInterrupt     = ISI_CHNL_IER_LINE_RCVD_EN_MASK,   /*!< Line received. */
    kISI_FrameReceivedInterrupt    = ISI_CHNL_IER_FRM_RCVD_EN_MASK,    /*!< Frame received. */
    kISI_AxiWriteErrorVInterrupt =
        ISI_CHNL_IER_AXI_WR_ERR_V_EN_MASK, /*!< AXI Bus write error when storing V data to memory. */
    kISI_AxiWriteErrorUInterrupt =
        ISI_CHNL_IER_AXI_WR_ERR_U_EN_MASK, /*!< AXI Bus write error when storing U data to memory. */
    kISI_AxiWriteErrorYInterrupt =
        ISI_CHNL_IER_AXI_WR_ERR_Y_EN_MASK, /*!< AXI Bus write error when storing Y data to memory. */
    kISI_AxiReadErrorInterrupt = ISI_CHNL_IER_AXI_RD_ERR_EN_MASK, /*!< AXI Bus error when reading the input memory. */
    kISI_OverflowAlertVInterrupt =
        ISI_CHNL_IER_OFLW_PANIC_V_BUF_EN_MASK, /*!< V output buffer overflow threshold accrossed. */
    kISI_ExcessOverflowVInterrupt =
        ISI_CHNL_IER_EXCS_OFLW_V_BUF_EN_MASK,                  /*!< V output buffer excess overflow interrupt. */
    kISI_OverflowVInterrupt = ISI_CHNL_IER_OFLW_V_BUF_EN_MASK, /*!< V output buffer overflow interrupt. */
    kISI_OverflowAlertUInterrupt =
        ISI_CHNL_IER_OFLW_PANIC_U_BUF_EN_MASK, /*!< U output buffer overflow threshold accrossed. */
    kISI_ExcessOverflowUInterrupt =
        ISI_CHNL_IER_EXCS_OFLW_U_BUF_EN_MASK,                  /*!< U output buffer excess overflow interrupt. */
    kISI_OverflowUInterrupt = ISI_CHNL_IER_OFLW_U_BUF_EN_MASK, /*!< U output buffer overflow interrupt. */
    kISI_OverflowAlertYInterrupt =
        ISI_CHNL_IER_OFLW_PANIC_Y_BUF_EN_MASK, /*!< V output buffer overflow threshold accrossed. */
    kISI_ExcessOverflowYInterrupt =
        ISI_CHNL_IER_EXCS_OFLW_Y_BUF_EN_MASK,                  /*!< V output buffer excess overflow interrupt. */
    kISI_OverflowYInterrupt = ISI_CHNL_IER_OFLW_Y_BUF_EN_MASK, /*!< V output buffer overflow interrupt. */
};

/*! @brief ISI output image format. */
typedef enum _isi_output_format
{
    kISI_OutputRGBA8888    = 0U,   /*!< RGBA8888. */
    kISI_OutputABGR8888    = 1U,   /*!< ABGR8888. */
    kISI_OutputARGB8888    = 2U,   /*!< ARGB8888. */
    kISI_OutputRGBX8888    = 3U,   /*!< RGBX8888 unpacked and MSB aligned in 32-bit. */
    kISI_OutputXBGR8888    = 4U,   /*!< XBGR8888 unpacked and LSB aligned in 32-bit. */
    kISI_OutputXRGB8888    = 5U,   /*!< XRGB8888 unpacked and LSB aligned in 32-bit. */
    kISI_OutputRGB888      = 6U,   /*!< RGB888 packed into 32-bit. */
    kISI_OutputBGR888      = 7U,   /*!< BGR888 packed into 32-bit. */
    kISI_OutputA2BGR10     = 8U,   /*!< BGR format with 2-bits alpha in MSB; 10-bits per color component. */
    kISI_OutputA2RGB10     = 9U,   /*!< RGB format with 2-bits alpha in MSB; 10-bits per color component. */
    kISI_OutputRGB565      = 10U,  /*!< RGB565 packed into 32-bit. */
    kISI_OutputRaw8        = 11U,  /*!< 8-bit raw data packed into 32-bit. */
    kISI_OutputRaw10       = 12U,  /*!< 10-bit raw data packed into 16-bit with 6 LSBs wasted. */
    kISI_OutputRaw10P      = 13U,  /*!< 10-bit raw data packed into 32-bit. */
    kISI_OutputRaw12P      = 14U,  /*!< 16-bit raw data packed into 16-bit with 4 LSBs wasted. */
    kISI_OutputRaw16P      = 15U,  /*!< 16-bit raw data packed into 32-bit. */
    kISI_OutputYUV444_1P8P = 16U,  /*!< 8-bits per color component; 1-plane, YUV interleaved packed bytes. */
    kISI_OutputYUV444_2P8P = 17U,  /*!< 8-bits per color component; 2-plane, UV interleaved packed bytes. */
    kISI_OutputYUV444_3P8P = 18U,  /*!< 8-bits per color component; 3-plane, non-interleaved packed bytes. */
    kISI_OutputYUV444_1P8  = 19U,  /*!< 8-bits per color component; 1-plane YUV interleaved unpacked bytes (8 MSBs waste
                                      bits in 32-bit DWORD). */
    kISI_OutputYUV444_1P10 = 20U,  /*!< 10-bits per color component; 1-plane, YUV interleaved unpacked bytes (6 LSBs
                                     waste bits in 16-bit WORD). */
    kISI_OutputYUV444_2P10 = 21U,  /*!< 10-bits per color component; 2-plane, UV interleaved unpacked bytes (6 LSBs
                                     waste bits in 16-bit WORD). */
    kISI_OutputYUV444_3P10 = 22U,  /*!< 10-bits per color component; 3-plane, non-interleaved unpacked bytes (6 LSBs
                                     waste bits in 16-bit WORD). */
    kISI_OutputYUV444_1P10P = 24U, /*!< 10-bits per color component; 1-plane, YUV interleaved packed bytes (2 MSBs
                                     waste bits in 32-bit DWORD). */
    kISI_OutputYUV444_2P10P = 25U, /*!< 10-bits per color component; 2-plane, UV interleaved packed bytes (2 MSBs waste
                                     bits in 32-bit DWORD). */
    kISI_OutputYUV444_3P10P = 26U, /*!< 10-bits per color component; 3-plane, non-interleaved packed bytes (2 MSBs
                                     waste bits in 32-bit DWORD). */
    kISI_OutputYUV444_1P12 = 28U,  /*!< 12-bits per color component; 1-plane, YUV interleaved unpacked bytes (4 LSBs
                                     waste bits in 16-bit WORD). */
    kISI_OutputYUV444_2P12 = 29U,  /*!< 12-bits per color component; 2-plane, UV interleaved unpacked bytes (4 LSBs
                                     waste bits in 16-bit WORD). */
    kISI_OutputYUV444_3P12 = 30U,  /*!< 12-bits per color component; 3-plane, non-interleaved unpacked bytes (4 LSBs
                                     waste bits in 16-bit WORD). */
    kISI_OutputYUV422_1P8P = 32U,  /*!< 8-bits per color component; 1-plane, YUV interleaved packed bytes. */
    kISI_OutputYUV422_2P8P = 33U,  /*!< 8-bits per color component; 2-plane, UV interleaved packed bytes. */
    kISI_OutputYUV422_3P8P = 34U,  /*!< 8-bits per color component; 3-plane, non-interleaved packed bytes. */
    kISI_OutputYUV422_1P10 = 36U,  /*!< 10-bits per color component; 1-plane, YUV interleaved unpacked bytes (6 LSBs
                                     waste bits in 16-bit WORD). */
    kISI_OutputYUV422_2P10 = 37U,  /*!< 10-bits per color component; 2-plane, UV interleaved unpacked bytes (6 LSBs
                                     waste bits in 16-bit WORD). */
    kISI_OutputYUV422_3P10 = 38U,  /*!< 10-bits per color component; 3-plane, non-interleaved unpacked bytes (6 LSBs
                                     waste bits in 16-bit WORD). */
    kISI_OutputYUV422_1P10P = 40U, /*!< 10-bits per color component; 1-plane, YUV interleaved packed bytes (2 MSBs
                                     waste bits in 32-bit DWORD). */
    kISI_OutputYUV422_2P10P = 41U, /*!< 10-bits per color component; 2-plane, UV interleaved packed bytes (2 MSBs waste
                                     bits in 32-bit DWORD). */
    kISI_OutputYUV422_3P10P = 42U, /*!< 10-bits per color component; 3-plane, non-interleaved packed bytes (2 MSBs
                                     waste bits in 32-bit DWORD). */
    kISI_OutputYUV422_1P12 = 44U,  /*!< 12-bits per color component; 1-plane, YUV interleaved unpacked bytes (4 LSBs
                                     waste bits in 16-bit WORD). */
    kISI_OutputYUV422_2P12 = 45U,  /*!< 12-bits per color component; 2-plane, UV interleaved unpacked bytes (4 LSBs
                                     waste bits in 16-bit WORD). */
    kISI_OutputYUV422_3P12 = 46U,  /*!< 12-bits per color component; 3-plane, non-interleaved unpacked bytes (4 LSBs
                                     waste bits in 16-bit WORD). */
    kISI_OutputYUV420_2P8P = 49U,  /*!< 8-bits per color component; 2-plane, UV interleaved packed bytes. */
    kISI_OutputYUV420_3P8P = 50U,  /*!< 8-bits per color component; 3-plane, non-interleaved packed bytes. */
    kISI_OutputYUV420_2P10 = 53U,  /*!< 10-bits per color component; 2-plane, UV interleaved unpacked bytes (6 LSBs
                                     waste bits in 16-bit WORD). */
    kISI_OutputYUV420_3P10 = 54U,  /*!< 10-bits per color component; 3-plane, non-interleaved unpacked bytes (6 LSBs
                                     waste bits in 16-bit WORD). */
    kISI_OutputYUV420_2P10P = 57U, /*!< 10-bits per color component; 2-plane, UV interleaved packed bytes (2 MSBs waste
                                     bits in 32-bit DWORD). */
    kISI_OutputYUV420_3P10P = 58U, /*!< 10-bits per color component; 3-plane, non-interleaved packed bytes (2 MSBs
                                     waste bits in 32-bit DWORD). */
    kISI_OutputYUV420_2P12 = 61U,  /*!< 12-bits per color component; 2-plane, UV interleaved unpacked bytes (4 LSBs
                                     waste bits in 16-bit WORD). */
    kISI_OutputYUV420_3P12 = 62U,  /*!< 12-bits per color component; 3-plane, non-interleaved unpacked bytes (4 LSBs
                                     waste bits in 16-bit WORD). */

} isi_output_format_t;

/*! @brief ISI line buffer chain mode. */
typedef enum _isi_chain_mode
{
    kISI_ChainDisable = 0U, /*!< No line buffers chained, for 2048 or less horizontal resolution. */
    kISI_ChainTwo     = 1U, /*!< Line buffers of channel n and n+1 chained, for 4096 horizontal resolution. */
} isi_chain_mode_t;

/*! @brief ISI de-interlacing mode. */
typedef enum _isi_deint_mode
{
    kISI_DeintDisable           = 0U, /*!< No de-interlacing. */
    kISI_DeintWeaveOddOnTop     = 2U, /*!< Weave de-interlacing (Odd, Even) method used. */
    kISI_DeintWeaveEvenOnTop    = 3U, /*!< Weave de-interlacing (Even, Odd) method used. */
    kISI_DeintBlendingOddFirst  = 4U, /*!< Blending or linear interpolation (Odd + Even). */
    kISI_DeintBlendingEvenFirst = 5U, /*!< Blending or linear interpolation (Even + Odd). */
    kISI_DeintDoublingOdd       = 6U, /*!< Doubling odd frame and discard even frame. */
    kISI_DeintDoublingEven      = 7U, /*!< Doubling even frame and discard odd frame. */
} isi_deint_mode_t;

/*! @brief ISI overflow panic alert threshold. */
typedef enum _isi_threshold
{
    kISI_ThresholdDisable   = 0U, /*!< No panic alert will be asserted. */
    kISI_Threshold25Percent = 1U, /*!< Panic will assert when the buffers are 25% full. */
    kISI_Threshold50Percent = 2U, /*!< Panic will assert when the buffers are 50% full. */
    kISI_Threshold75Percent = 3U  /*!< Panic will assert when the buffers are 75% full. */
} isi_threshold_t;

/*! @brief ISI basic configuration. */
typedef struct _isi_config
{
    bool isChannelBypassed;           /*!< Bypass the channel, if bypassed, the scaling and
                                           color space conversion could not work.  */
    bool isSourceMemory;              /*!< Whether the input source is memory or not. */
    bool isYCbCr;                     /*!< Whether the input source is YCbCr mode or not. */
    isi_chain_mode_t chainMode;       /*!< The line buffer chain mode. */
    isi_deint_mode_t deintMode;       /*!< The de-interlacing mode. */
    uint8_t blankPixel;               /*!< The pixel to insert into image when overflow occors. */
    uint8_t sourcePort;               /*!< Input source port selection. */
    uint8_t mipiChannel;              /*!< MIPI virtual channel, ignored if input source is not MIPI CSI. */
    uint16_t inputHeight;             /*!< Input image height(lines). */
    uint16_t inputWidth;              /*!< Input image width(pixels). */
    isi_output_format_t outputFormat; /*!< Output image format. */
    uint16_t outputLinePitchBytes;    /*< Output buffer pitch in bytes. */
    isi_threshold_t thresholdY;       /*!< Panic alert threshold for RGB or Luma (Y) buffer. */
    isi_threshold_t thresholdU;       /*!< Panic alert threshold for Chroma (U/Cb/UV/CbCr) buffer. */
    isi_threshold_t thresholdV;       /*!< Panic alert threshold for Chroma (V/Cr) buffer. */
} isi_config_t;

/*! @brief ISI color space conversion mode. */
typedef enum _isi_csc_mode
{
    kISI_CscYUV2RGB,   /*!< Convert YUV to RGB. */
    kISI_CscYCbCr2RGB, /*!< Convert YCbCr to RGB. */
    kISI_CscRGB2YUV,   /*!< Convert RGB to YUV. */
    kISI_CscRGB2YCbCr  /*!< Convert RGB to YCbCr. */
} isi_csc_mode_t;

/*!
 * @brief ISI color space conversion configurations.
 *
 * (a) RGB to YUV (or YCbCr) conversion
 *  - Y = (A1 x R) + (A2 x G) + (A3 x B) + D1
 *  - U = (B1 x R) + (B2 x G) + (B3 x B) + D2
 *  - V = (C1 x R) + (C2 x G) + (C3 x B) + D3
 *
 * (b) YUV (or YCbCr) to RGB conversion
 *  - R = (A1 x (Y + D1)) + (A2 x (U + D2)) + (A3 x (V + D3))
 *  - G = (B1 x (Y + D1)) + (B2 x (U + D2)) + (B3 x (V + D3))
 *  - B = (C1 x (Y + D1)) + (C2 x (U + D2)) + (C3 x (V + D3))
 *
 * Overflow for the three channels are saturated at 0x255 and underflow is saturated at 0x00.
 */
typedef struct _isi_csc_config
{
    isi_csc_mode_t mode; /*!< Convertion mode. */
    float A1;            /*!< Must be in the range of [-3.99609375, 3.99609375]. */
    float A2;            /*!< Must be in the range of [-3.99609375, 3.99609375]. */
    float A3;            /*!< Must be in the range of [-3.99609375, 3.99609375]. */
    float B1;            /*!< Must be in the range of [-3.99609375, 3.99609375]. */
    float B2;            /*!< Must be in the range of [-3.99609375, 3.99609375]. */
    float B3;            /*!< Must be in the range of [-3.99609375, 3.99609375]. */
    float C1;            /*!< Must be in the range of [-3.99609375, 3.99609375]. */
    float C2;            /*!< Must be in the range of [-3.99609375, 3.99609375]. */
    float C3;            /*!< Must be in the range of [-3.99609375, 3.99609375]. */
    int16_t D1;          /*!< Must be in the range of [-256, 255]. */
    int16_t D2;          /*!< Must be in the range of [-256, 255]. */
    int16_t D3;          /*!< Must be in the range of [-256, 255]. */
} isi_csc_config_t;

/*! @brief ISI flipping mode. */
typedef enum _isi_flip_mode
{
    kISI_FlipDisable    = 0U,                                                               /*!< Flip disabled. */
    kISI_FlipHorizontal = ISI_CHNL_IMG_CTRL_HFLIP_EN_MASK,                                  /*!< Horizontal flip. */
    kISI_FlipVertical   = ISI_CHNL_IMG_CTRL_VFLIP_EN_MASK,                                  /*!< Vertical flip. */
    kISI_FlipBoth       = ISI_CHNL_IMG_CTRL_VFLIP_EN_MASK | ISI_CHNL_IMG_CTRL_HFLIP_EN_MASK /*!< Flip both direction. */
} isi_flip_mode_t;

/*! @brief ISI cropping configurations. */
typedef struct _isi_crop_config
{
    uint16_t upperLeftX;  /*!< X of upper left corner. */
    uint16_t upperLeftY;  /*!< Y of upper left corner. */
    uint16_t lowerRightX; /*!< X of lower right corner. */
    uint16_t lowerRightY; /*!< Y of lower right corner. */
} isi_crop_config_t;

/*! @brief ISI regional region alpha configurations. */
typedef struct _isi_regoin_alpha_config
{
    uint16_t upperLeftX;  /*!< X of upper left corner. */
    uint16_t upperLeftY;  /*!< Y of upper left corner. */
    uint16_t lowerRightX; /*!< X of lower right corner. */
    uint16_t lowerRightY; /*!< Y of lower right corner. */
    uint8_t alpha;        /*!< Alpha value. */
} isi_region_alpha_config_t;

/*! @brief ISI image format of the input memory. */
typedef enum _isi_input_mem_format
{
    kISI_InputMemBGR888 = 0U,        /*!< BGR format with 8-bits per color component,
                                       packed into 32-bit, 24 bits per pixel. */
    kISI_InputMemRGB888 = 1U,        /*!< RGB format with 8-bits per color component,
                                       packed into 32-bit, 24 bits per pixel. */
    kISI_InputMemXRGB8888 = 2U,      /*!< RGB format with 8-bits per color component,
                                       unpacked and LSB aligned in 32-bit, 32 bits per pixel.  */
    kISI_InputMemRGBX8888 = 3U,      /*!< RGB format with 8-bits per color component,
                                       unpacked and MSB alinged in 32-bit, 32 bits per pixel.  */
    kISI_InputMemXBGR8888 = 4U,      /*!< BGR format with 8-bits per color component,
                                       unpacked and LSB aligned in 32-bit, 32 bits per pixel.  */
    kISI_InputMemRGB565      = 5U,   /*!< RGB format with 5-bits of R, B; 6-bits of G (packed into 32-bit) */
    kISI_InputMemA2BGR10     = 6U,   /*!< BGR format with 2-bits alpha in MSB; 10-bits per color component. */
    kISI_InputMemA2RGB10     = 7U,   /*!< RGB format with 2-bits alpha in MSB; 10-bits per color component. */
    kISI_InputMemYUV444_1P8P = 8U,   /*!< 8-bits per color component; 1-plane, YUV interleaved packed bytes. */
    kISI_InputMemYUV444_1P10 = 9U,   /*!< 10-bits per color component; 1-plane, YUV interleaved unpacked bytes (6 LSBs
                                        waste bits in 16-bit WORD). */
    kISI_InputMemYUV444_1P10P = 10U, /*!< 10-bits per color component; 1-plane, YUV interleaved packed bytes (2 MSBs
                                        waste bits in 32-bit WORD). */
    kISI_InputMemYUV444_1P12 = 11U,  /*!< 12-bits per color component; 1-plane, YUV interleaved unpacked bytes (4 LSBs
                                        waste bits in 16-bit WORD). */
    kISI_InputMemYUV444_1P8 = 12U,   /*!< 8-bits per color component; 1-plane YUV interleaved unpacked bytes
                                       (8 MSBs waste bits in 32-bit DWORD). */
    kISI_InputMemYUV422_1P8P = 13U,  /*!< 8-bits per color component; 1-plane YUV interleaved packed bytes. */
    kISI_InputMemYUV422_1P10 = 14U,  /*!< 10-bits per color component; 1-plane, YUV interleaved unpacked bytes (6 LSBs
                                        waste bits in 16-bit WORD). */
    kISI_InputMemYUV422_1P12 = 15U,  /*!< 12-bits per color component; 1-plane, YUV interleaved packed bytes (4 MSBs
                                        waste bits in 16-bit WORD). */
} isi_input_mem_format_t;

/*! @brief ISI input memory configurations. */
typedef struct _isi_input_mem_config
{
    uint32_t adddr;                /*!< Address of the input memory. */
    uint16_t linePitchBytes;       /*!< Line phtch in bytes. */
    uint16_t framePitchBytes;      /*!< Frame phtch in bytes. */
    isi_input_mem_format_t format; /*!< Image format of the input memory. */
} isi_input_mem_config_t;

/*******************************************************************************
 * APIs
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @name ISI initialization and de-initialization
 * @{
 */

/*!
 * @brief Initializes the ISI peripheral.
 *
 * This function ungates the ISI clock, it should be called before any other
 * ISI functions.
 *
 * @param base ISI peripheral base address.
 */
void ISI_Init(ISI_Type *base);

/*!
 * @brief Deinitializes the ISI peripheral.
 *
 * This function gates the ISI clock.
 *
 * @param base ISI peripheral base address.
 */
void ISI_Deinit(ISI_Type *base);

/*!
 * @brief Reset the ISI peripheral.
 *
 * This function resets the ISI channel processing pipeline similar to a hardware
 * reset. The channel will need to be reconfigured after reset before it can be used.
 *
 * @param base ISI peripheral base address.
 */
void ISI_Reset(ISI_Type *base);

/* @} */

/*!
 * @name ISI interrupts
 * @{
 */

/*!
 * @brief Enables ISI interrupts.
 *
 * @param base ISI peripheral base address
 * @param mask Interrupt source, OR'ed value of @ref _isi_interrupt.
 * @return OR'ed value of the enabled interrupts before calling this function.
 */
static inline uint32_t ISI_EnableInterrupts(ISI_Type *base, uint32_t mask)
{
    uint32_t reg   = base->CHNL_IER;
    base->CHNL_IER = reg | mask;
    return reg;
}

/*!
 * @brief Disables ISI interrupts.
 *
 * @param base ISI peripheral base address
 * @param mask Interrupt source, OR'ed value of @ref _isi_interrupt.
 * @return OR'ed value of the enabled interrupts before calling this function.
 */
static inline uint32_t ISI_DisableInterrupts(ISI_Type *base, uint32_t mask)
{
    uint32_t reg   = base->CHNL_IER;
    base->CHNL_IER = reg & ~mask;
    return reg;
}

/*!
 * @brief Get the ISI interrupt pending flags.
 *
 * All interrupt pending flags are returned, upper layer could compare with the
 * OR'ed value of @ref _isi_interrupt. For example, to check whether memory read
 * completed, use like this:
 * @code
   uint32_t mask = ISI_GetInterruptStatus(ISI);
   if (mask & kISI_MemReadCompletedInterrupt)
   {
       memory read completed
   }
   @endcode
 *
 * @param base ISI peripheral base address
 * @return The OR'ed value of the pending interrupt flags. of @ref _isi_interrupt.
 */
static inline uint32_t ISI_GetInterruptStatus(ISI_Type *base)
{
    return base->CHNL_STS & ~ISI_CHNL_STS_OFLW_BYTES_MASK;
}

/*!
 * @brief Clear ISI interrupt pending flags.
 *
 * This function could clear one or more flags at one time, the flags to clear
 * are passed in as an OR'ed value of @ref _isi_interrupt. For example, to clear
 * both line received interrupt flag and frame received flag, use like this:
 * @code
    ISI_ClearInterruptStatus(ISI, kISI_LineReceivedInterrupt | kISI_FrameReceivedInterrupt);
   @endcode
 *
 * @param base ISI peripheral base address
 * @param mask The flags to clear, it is OR'ed value of @ref _isi_interrupt.
 */
static inline void ISI_ClearInterruptStatus(ISI_Type *base, uint32_t mask)
{
    base->CHNL_STS = mask;
}

/* @} */

/*!
 * @brief Gets the number of valid pixel bytes lost due to overflow.
 *
 * If multiple output buffers overflow, then this function only returns the
 * status of the buffer with highest priority. The buffer priority is:
 * Y output buffer > U output buffer > V output buffer.
 *
 * @param base ISI peripheral base address
 * @return The number of valid pixel bytes lost due to overflow.
 */
static inline uint8_t ISI_GetOverflowBytes(ISI_Type *base)
{
    return (uint8_t)(base->CHNL_STS & ISI_CHNL_STS_OFLW_BYTES_MASK);
}

/*!
 * @brief Set the ISI channel basic configurations.
 *
 * This function sets the basic configurations, generally the channel could be
 * started to work after this function. To enable other features such as croping,
 * flipping, please call the functions accordingly.
 *
 * @param base ISI peripheral base address
 * @param config Pointer to the configuration structure.
 */
void ISI_SetConfig(ISI_Type *base, const isi_config_t *config);

/*!
 * @brief Get the ISI channel default basic configurations.
 *
 * The default value is:
 * @code
    config->isChannelBypassed = false;
    config->isSourceMemory = false;
    config->isYCbCr = false;
    config->chainMode = kISI_ChainDisable;
    config->deintMode = kISI_DeintDisable;
    config->blankPixel = 0xFFU;
    config->sourcePort = 0U;
    config->mipiChannel = 0U;
    config->inputHeight = 1080U;
    config->inputWidth = 1920U;
    config->outputFormat = kISI_OutputRGBA8888;
    config->outputLinePitchBytes = 0U;
    config->thresholdY = kISI_ThresholdDisable;
    config->thresholdU = kISI_ThresholdDisable;
    config->thresholdV = kISI_ThresholdDisable;
   @endcode
 *
 * @param config Pointer to the configuration structure.
 */
void ISI_GetDefaultConfig(isi_config_t *config);

/*!
 * @name ISI scaler
 * @{
 */

/*!
 * @brief Set the ISI channel scaler configurations.
 *
 * This function sets the scaling configurations. If the ISI channel is bypassed,
 * then the scaling feature could not be used.
 *
 * ISI only supports down scaling but not up scaling.
 *
 * @param base ISI peripheral base address
 * @param inputWidth Input image width.
 * @param inputHeight Input image height.
 * @param outputWidth Output image width.
 * @param outputHeight Output image height.
 * @note Total bytes in one line after down scaling must be more than 256 bytes.
 */
void ISI_SetScalerConfig(
    ISI_Type *base, uint16_t inputWidth, uint16_t inputHeight, uint16_t outputWidth, uint16_t outputHeight);

/* @} */

/*!
 * @name ISI color space conversion
 * @{
 */

/*!
 * @brief Set the ISI color space conversion configurations.
 *
 * This function sets the color space conversion configurations. After setting
 * the configuration, use the function @ref ISI_EnableColorSpaceConversion to
 * enable this feature. If the ISI channel is bypassed, then the color space
 * conversion feature could not be used.
 *
 * @param base ISI peripheral base address
 * @param config Pointer to the configuration structure.
 */
void ISI_SetColorSpaceConversionConfig(ISI_Type *base, const isi_csc_config_t *config);

/*!
 * @brief Get the ISI color space conversion default configurations.
 *
 * The default value is:
 * @code
    config->mode = kISI_CscYUV2RGB;
    config->A1 = 0.0;
    config->A2 = 0.0;
    config->A3 = 0.0;
    config->B1 = 0.0;
    config->B2 = 0.0;
    config->B3 = 0.0;
    config->C1 = 0.0;
    config->C2 = 0.0;
    config->C3 = 0.0;
    config->D1 = 0;
    config->D2 = 0;
    config->D3 = 0;
   @endcode
 *
 * @param config Pointer to the configuration structure.
 */
void ISI_ColorSpaceConversionGetDefaultConfig(isi_csc_config_t *config);

/*!
 * @brief Enable or disable the ISI color space conversion.
 *
 * If the ISI channel is bypassed, then the color space conversion feature could not
 * be used even enable using this function.
 *
 * @param base ISI peripheral base address
 * @param enable True to enable, false to disable.
 * @note The CSC is enabled by default. Disable it if it is not required.
 */
static inline void ISI_EnableColorSpaceConversion(ISI_Type *base, bool enable)
{
    if (enable)
    {
        base->CHNL_IMG_CTRL &= ~ISI_CHNL_IMG_CTRL_CSC_BYP_MASK;
    }
    else
    {
        base->CHNL_IMG_CTRL |= ISI_CHNL_IMG_CTRL_CSC_BYP_MASK;
    }
}

/* @} */

/*!
 * @name ISI cropping
 * @{
 */

/*!
 * @brief Set the ISI cropping configurations.
 *
 * This function sets the cropping configurations. After setting the configuration,
 * use the function @ref ISI_EnableCrop to enable the feature. Cropping still
 * works when the ISI channel is bypassed.
 *
 * @param base ISI peripheral base address
 * @param config Pointer to the configuration structure.
 * @note The upper left corner and lower right corner should be configured base on
 * the image resolution output from the scaler.
 */
void ISI_SetCropConfig(ISI_Type *base, const isi_crop_config_t *config);

/*!
 * @brief Get the ISI cropping default configurations.
 *
 * The default value is:
 * @code
    config->upperLeftX = 0U;
    config->upperLeftY = 0U;
    config->lowerRightX = 0U;
    config->lowerRightY = 0U;
   @endcode
 *
 * @param config Pointer to the configuration structure.
 */
void ISI_CropGetDefaultConfig(isi_crop_config_t *config);

/*!
 * @brief Enable or disable the ISI cropping.
 *
 * If the ISI channel is bypassed, the cropping still works.
 *
 * @param base ISI peripheral base address
 * @param enable True to enable, false to disable.
 */
static inline void ISI_EnableCrop(ISI_Type *base, bool enable)
{
    if (enable)
    {
        base->CHNL_IMG_CTRL |= ISI_CHNL_IMG_CTRL_CROP_EN_MASK;
    }
    else
    {
        base->CHNL_IMG_CTRL &= ~ISI_CHNL_IMG_CTRL_CROP_EN_MASK;
    }
}

/* @} */

/*!
 * @name ISI alpha
 * @{
 */

/*!
 * @brief Set the global alpha value.
 *
 * @param base ISI peripheral base address
 * @param alpha The global alpha value.
 */
static inline void ISI_SetGlobalAlpha(ISI_Type *base, uint8_t alpha)
{
    base->CHNL_IMG_CTRL =
        (base->CHNL_IMG_CTRL & ~ISI_CHNL_IMG_CTRL_GBL_ALPHA_VAL_MASK) | ISI_CHNL_IMG_CTRL_GBL_ALPHA_VAL(alpha);
}

/*!
 * @brief Enable the global alpha insertion.
 *
 * Alpha still works when channel bypassed.
 *
 * @param base ISI peripheral base address
 * @param enable True to enable, false to disable.
 */
static inline void ISI_EnableGlobalAlpha(ISI_Type *base, bool enable)
{
    if (enable)
    {
        base->CHNL_IMG_CTRL |= ISI_CHNL_IMG_CTRL_GBL_ALPHA_EN_MASK;
    }
    else
    {
        base->CHNL_IMG_CTRL &= ~ISI_CHNL_IMG_CTRL_GBL_ALPHA_EN_MASK;
    }
}

/*!
 * @brief Set the alpha value for region of interest.
 *
 * Set the alpha insertion configuration for specific region of interest.
 * The function @ref ISI_EnableRegionAlpha could be used to enable the alpha
 * insertion. Alpha insertion still works when channel bypassed.
 *
 * @param base ISI peripheral base address
 * @param index Index of the region of interest, Could be 0, 1, 2, and 3.
 * @param config Pointer to the configuration structure.
 * @note The upper left corner and lower right corner should be configured base on
 * the image resolution output from the scaler.
 */
void ISI_SetRegionAlphaConfig(ISI_Type *base, uint8_t index, const isi_region_alpha_config_t *config);

/*!
 * @brief Get the regional alpha insertion default configurations.
 *
 * The default configuration is:
 * @code
    config->upperLeftX = 0U;
    config->upperLeftY = 0U;
    config->lowerRightX = 0U;
    config->lowerRightY = 0U;
    config->alpha = 0U;
   @endcode
 *
 * @param config Pointer to the configuration structure.
 */
void ISI_RegionAlphaGetDefaultConfig(isi_region_alpha_config_t *config);

/*!
 * @brief Enable or disable the alpha value insertion for region of interest.
 *
 * Alpha insertion still works when channel bypassed.
 *
 * @param base ISI peripheral base address
 * @param index Index of the region of interest, Could be 0, 1, 2, and 3.
 * @param enable True to enable, false to disable.
 */
void ISI_EnableRegionAlpha(ISI_Type *base, uint8_t index, bool enable);

/* @} */

/*!
 * @name ISI input memory.
 * @{
 */

/*!
 * @brief Set the input memory configuration.
 *
 * @param base ISI peripheral base address
 * @param config Pointer to the configuration structure.
 */
void ISI_SetInputMemConfig(ISI_Type *base, const isi_input_mem_config_t *config);

/*!
 * @brief Get the input memory default configurations.
 *
 * The default configuration is:
 * @code
    config->adddr = 0U;
    config->linePitchBytes = 0U;
    config->framePitchBytes = 0U;
    config->format = kISI_InputMemBGR8P;
   @endcode
 *
 * @param config Pointer to the configuration structure.
 */
void ISI_InputMemGetDefaultConfig(isi_input_mem_config_t *config);

/*!
 * @brief Set the input memory address.
 *
 * This function only sets the input memory address, it is used for fast run-time setting.
 *
 * @param base ISI peripheral base address
 * @param addr Input memory address.
 */
static inline void ISI_SetInputMemAddr(ISI_Type *base, uint32_t addr)
{
    base->CHNL_IN_BUF_ADDR = addr;
}

/*!
 * @brief Trigger the ISI pipeline to read the input memory.
 *
 * @param base ISI peripheral base address
 */
void ISI_TriggerInputMemRead(ISI_Type *base);

/* @} */

/*!
 * @name ISI misc control.
 * @{
 */

/*!
 * @brief Set the ISI channel flipping mode.
 *
 * @param base ISI peripheral base address
 * @param mode Flipping mode.
 */
static inline void ISI_SetFlipMode(ISI_Type *base, isi_flip_mode_t mode)
{
    base->CHNL_IMG_CTRL =
        (base->CHNL_IMG_CTRL & ~(ISI_CHNL_IMG_CTRL_VFLIP_EN_MASK | ISI_CHNL_IMG_CTRL_HFLIP_EN_MASK)) | (uint32_t)mode;
}

/*!
 * @brief Set the ISI output buffer address.
 *
 * This function sets the output buffer address and trigger the ISI to shadow the
 * address, it is used for fast run-time setting.
 *
 * @param base ISI peripheral base address
 * @param index Index of output buffer, could be 0 and 1.
 * @param addrY RGB or Luma (Y) output buffer address.
 * @param addrU Chroma (U/Cb/UV/CbCr) output buffer address.
 * @param addrV Chroma (V/Cr) output buffer address.
 */
void ISI_SetOutputBufferAddr(ISI_Type *base, uint8_t index, uint32_t addrY, uint32_t addrU, uint32_t addrV);

/*!
 * @brief Start the ISI channel.
 *
 * Start the ISI channel to work, this function should be called after all channel
 * configuration finished.
 *
 * @param base ISI peripheral base address
 */
static inline void ISI_Start(ISI_Type *base)
{
    base->CHNL_CTRL |= ISI_CHNL_CTRL_CHNL_EN_MASK;
}

/*!
 * @brief Stop the ISI channel.
 *
 * @param base ISI peripheral base address
 */
static inline void ISI_Stop(ISI_Type *base)
{
    base->CHNL_CTRL &= ~ISI_CHNL_CTRL_CHNL_EN_MASK;
}

/* @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/* @} */

#endif /*_FSL_ISI_H_*/
