/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_ASRC_H_
#define _FSL_ASRC_H_

#include "fsl_common.h"

/*!
 * @addtogroup asrc_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
#define FSL_ASRC_DRIVER_VERSION (MAKE_VERSION(2, 0, 3)) /*!< Version 2.0.3 */
/*@}*/

/*! @brief ASRC fifo depth */
#define FSL_ASRC_INPUT_FIFO_DEPTH  (128U)
#define FSL_ASRC_OUTPUT_FIFO_DEPTH (64U)
/*! @brief ASRC support maximum channel number of context */
#define ASRC_SUPPORT_MAXIMUM_CONTEXT_PROCESSOR_NUMBER 4U

/*! @brief ASRC return status, _asrc_status*/
enum
{
    kStatus_ASRCIdle                     = MAKE_STATUS(kStatusGroup_ASRC, 0),  /*!< ASRC  is idle. */
    kStatus_ASRCBusy                     = MAKE_STATUS(kStatusGroup_ASRC, 1),  /*!< ASRC  is busy. */
    kStatus_ASRCInvalidArgument          = MAKE_STATUS(kStatusGroup_ASRC, 2),  /*!< ASRC invalid argument. */
    kStatus_ASRCConfigureFailed          = MAKE_STATUS(kStatusGroup_ASRC, 3),  /*!< ASRC configure failed */
    kStatus_ASRCConvertError             = MAKE_STATUS(kStatusGroup_ASRC, 4),  /*!< ASRC convert error failed */
    kStatus_ASRCNotSupport               = MAKE_STATUS(kStatusGroup_ASRC, 5),  /*!< ASRC not support */
    kStatus_ASRCQueueFull                = MAKE_STATUS(kStatusGroup_ASRC, 6),  /*!< ASRC queue full */
    kStatus_ASRCQueueIdle                = MAKE_STATUS(kStatusGroup_ASRC, 7),  /*!< ASRC quue idle */
    kStatus_ASRCLoadFirmwareFailed       = MAKE_STATUS(kStatusGroup_ASRC, 8),  /*!< ASRC load firmware failed*/
    kStatus_ASRCResamplerConfigureFailed = MAKE_STATUS(kStatusGroup_ASRC, 9),  /*!< ASRC resampler configured failed */
    kStatus_ASRCPrefilterConfigureFailed = MAKE_STATUS(kStatusGroup_ASRC, 10), /*!< ASRC prefilter configured failed */
};

/*! @brief asrc context id */
typedef enum _asrc_context
{
    kASRC_Context0 = 0, /*!< Context 0 value */
    kASRC_Context1 = 1, /*!< Context 1 value */
    kASRC_Context2 = 2, /*!< Context 2 value */
    kASRC_Context3 = 3, /*!< Context 3 value */
} asrc_context_t;

/*! @brief The ASRC interrupt enable flag, _asrc_interrupt_mask*/
enum
{
    kASRC_Context0InputFifoOverflow = 1U,       /*!< context 0 input fifo overflow */
    kASRC_Context1InputFifoOverflow = 1U << 1U, /*!< context 1 input fifo overflow */
    kASRC_Context2InputFifoOverflow = 1U << 2U, /*!< context 2 input fifo overflow */
    kASRC_Context3InputFifoOverflow = 1U << 3U, /*!< context 3 input fifo overflow */

    kASRC_Context0OutFifoReadEmpty = 1U << 4U, /*!< context 0 out fifo read empty */
    kASRC_Context1OutFifoReadEmpty = 1U << 5U, /*!< context 1 out fifo read empty */
    kASRC_Context2OutFifoReadEmpty = 1U << 6U, /*!< context 2 out fifo read empty */
    kASRC_Context3OutFifoReadEmpty = 1U << 7U, /*!< context 3 out fifo read empty */

    kASRC_Context0RunStopDone       = 1U << 8U,  /*!< context 0 run stop done interrupt */
    kASRC_Context1RunStopDone       = 1U << 9U,  /*!< context 1 run stop done interrupt */
    kASRC_Context2RunStopDone       = 1U << 10U, /*!< context 2 run stop done interrupt */
    kASRC_Context3RunStopDone       = 1U << 11U, /*!< context 3 run stop done interrupt */
    kASRC_ContextAllInterruptStatus = 0xFFFU,    /*!< all the context interrupt status */
};

/*! @brief ASRC fifo status, _asrc_fifo_status*/
enum
{
    kASRC_FifoStatusInputFifoWatermarkFlag =
        ASRC_SAMPLE_FIFO_STATUS_INFIFO_WTMK_MASK, /*!< input water mark flag raised */
    kASRC_FifoStatusOutputFifoWatermarkFlag =
        ASRC_SAMPLE_FIFO_STATUS_OUTFIFO_WTMK_MASK, /*!< output water mark flag raised */
};

/*! @brief arsc data endianness */
typedef enum _asrc_data_endianness
{
    kASRC_DataEndianLittle = 0U, /*!< context data little endian */
    kASRC_DataEndianBig    = 1U, /*!< context data big endian */
} asrc_data_endianness_t;

/*! @brief data width */
typedef enum _asrc_data_width
{
    kASRC_DataWidth32Bit = 3U, /*!< data width 32bit */
    kASRC_DataWidth24Bit = 2U, /*!< data width 24bit */
    kASRC_DataWidth20Bit = 1U, /*!< data width 20bit */
    kASRC_DataWidth16Bit = 0U, /*!< data width 16bit */
} asrc_data_width_t;

/*! @brief data type */
typedef enum _asrc_data_type
{
    kASRC_DataTypeInteger = 0U, /*!< data type int */
    kASRC_DataTypeFloat   = 1U, /*!< data type float, single precision floating point format */
} asrc_data_type_t;

/*! @brief sign extension */
typedef enum _asrc_data_sign
{
    kASRC_DataSigned   = 0U, /*!< input data is signed */
    kASRC_DataUnsigned = 1U, /*!< input data is unsinged */
} asrc_data_sign_t;

/*! @brief  asrc prefilter and resampler sample buffer init mode */
typedef enum _asrc_sampleBuffer_init_mode
{
    kASRC_SampleBufferNoPreFillOnInit = 0U, /*!< do not pre-fill */
    kASRC_SampleBufferFillFirstSampleOnInit =
        1U, /*!< replicate the first sample to fill the right half of the sample buffer */
    kASRC_SampleBufferFillZeroOnInit = 2U, /*!< zero fill the right half og the sample buffer */
} asrc_sampleBuffer_init_mode_t;

/*! @brief  asrc prefilter and resampler sample buffer stop mode */
typedef enum _asrc_sampleBuffer_stop_mode
{
    kASRC_SampleBufferFillLastSampleOnStop =
        0U,                                /*!< replicate the last sample to fill the left half of the sample buffer */
    kASRC_SampleBufferFillZeroOnStop = 1U, /*!< zero fill the left half of the sample buffer */
} asrc_sampleBuffer_stop_mode_t;

/*! @brief ASRC prefilter stage1 result format */
typedef enum _asrc_prefilter_stage1_result
{
    kASRC_PrefilterStage1ResultInt   = 0U, /*!< prefilter stage1 results are stored in 32 bit int format */
    kASRC_PrefilterStage1ResultFloat = 1U, /*!< prefilter stage1 results are stored in 32 bit float format */
} asrc_prefilter_stage1_result_t;

/*! @brief ASRC resampler taps */
typedef enum _asrc_resampler_taps
{
    kASRC_ResamplerTaps_32  = 32U,  /*!< resampler taps 32 */
    kASRC_ResamplerTaps_64  = 64U,  /*!< resampler taps 64 */
    kASRC_ResamplerTaps_128 = 128U, /*!< resampler taps 128 */
} asrc_resampler_taps_t;

/*! @brief ASRC support sample rate, _asrc_sample_rate */
enum
{
    kASRC_SampleRate_8000   = 8000,   /*!< 8K sample rate */
    kASRC_SampleRate_11025  = 11025,  /*!< 11025 sample rate */
    kASRC_SampleRate_12000  = 12000,  /*!< 12K sample rate */
    kASRC_SampleRate_16000  = 16000,  /*!< 16K sample rate */
    kASRC_SampleRate_22050  = 22050,  /*!< 22.05K sample rate */
    kASRC_SampleRate_24000  = 24000,  /*!< 24K sample rate */
    kASRC_SampleRate_32000  = 32000,  /*!< 32K sample rate */
    kASRC_SampleRate_44100  = 44100,  /*!< 44.1K sample rate */
    kASRC_SampleRate_48000  = 48000,  /*!< 48K sample rate */
    kASRC_SampleRate_64000  = 64000,  /*!< 64K sample rate */
    kASRC_SampleRate_88200  = 88200,  /*!< 88.2K sample rate */
    kASRC_SampleRate_96000  = 96000,  /*!< 96K sample rate */
    kASRC_SampleRate_128000 = 128000, /*!< 128K sample rate */
    kASRC_SampleRate_176400 = 176400, /*!< 176K sample rate */
    kASRC_SampleRate_192000 = 192000, /*!< 256K sample rate */
    kASRC_SampleRate_256000 = 256000, /*!< 256K sample rate */
    kASRC_SampleRate_352800 = 352800, /*!< 352.8K sample rate */
    kASRC_SampleRate_384000 = 384000, /*!< 384K sample rate */
    kASRC_SampleRate_768000 = 768000, /*!< 768K sample rate */
};

/*! @brief asrc context data format */
typedef struct _asrc_data_format
{
    uint8_t dataPosition;                  /*!< context input data sample position */
    asrc_data_endianness_t dataEndianness; /*!< context input data endianness */
    asrc_data_width_t dataWidth;           /*!< context input data width */
    asrc_data_type_t dataType;             /*!< context input data type */
    asrc_data_sign_t dataSign;             /*!< context input data signed or unsigned */
} asrc_data_format_t;

/*! @brief asrc context access control
 * The ASRC provides interleaving support in hardware to ensure that a variety of sample source can be internally
 * combined tp confir with this format. The interleave patter is controlled using 3 register fields: GROUP_LENGTH,
 * ACCESS_LENGTH, ITERATIONIS. This is intended to support hardware configurations which distribute a single context
 * across samples from multiple audio sources. Take a example as below: accessGroupLen = 6, the sample group length is 6
 * samples accessIterations = 2, the 2 sequential ACCESS_LENGTH read from single source accessLen = 2, the 2 samples
 * fetch from one source.
 */
typedef struct _asrc_access_ctrl
{
    uint8_t accessIterations; /*!< number of sequential fetches per source */
    uint8_t accessGroupLen;   /*!< number of channels in a context */
    uint8_t accessLen;        /*!< number of channels per source1 */
} asrc_access_ctrl_t;

/*! @brief asrc context input configuration */
typedef struct _asrc_context_input_config
{
    uint32_t sampleRate;           /*!< input audio data sample rate */
    uint8_t watermark;             /*!< input water mark per samples */
    asrc_access_ctrl_t accessCtrl; /*!< input access control */
    asrc_data_format_t dataFormat; /*!< input data format */
} asrc_context_input_config_t;

/*! @brief asrc context output configuration */
typedef struct _asrc_context_output_config
{
    uint32_t sampleRate;           /*!< output audio data sample rate */
    uint8_t watermark;             /*!< output water mark per samples */
    asrc_access_ctrl_t accessCtrl; /*!< output access control */
    asrc_data_format_t dataFormat; /*!< output data format */
    bool enableDither;   /*!< output path contains a TPDF dither function. The dither function support all fixed output
                            modes(16, 20, 24, 32bits)   dither is not supported in 32bit floating point output mode */
    bool enableIEC60958; /*!< output IEC60958 bit field insertion enable */
} asrc_context_output_config_t;

/*! @brief asrc context prefilter configuration */
typedef struct _asrc_context_prefilter_config
{
    asrc_sampleBuffer_init_mode_t initMode;      /*!< prefilter initial mode */
    asrc_sampleBuffer_stop_mode_t stopMode;      /*!< prefilter stop mode */
    asrc_prefilter_stage1_result_t stage1Result; /*!< stage1 data store format */
    /*
     * applciation can untouch below configuration by set filterCoeffAddress to NULL , driver will load it from the
     * driver firmware table, otherwise driver will use the value directly.
     */
    uint32_t filterSt1Taps;             /*!< prefilter stage1 taps */
    uint32_t filterSt2Taps;             /*!< prefilter stage2 taps */
    uint32_t filterSt1Exp;              /*!< prefilter stage1 expansion factor */
    const uint32_t *filterCoeffAddress; /*!< prefilter coeff address */
} asrc_context_prefilter_config_t;

/*! @brief asrc context resampler configuration */
typedef struct _asrc_context_resampler_config
{
    asrc_sampleBuffer_init_mode_t initMode; /*!< initial mode */
    asrc_sampleBuffer_stop_mode_t stopMode; /*!< resampler stop mode */
    asrc_resampler_taps_t tap;              /*!< resampleer taps */
    /*
     * applciation can untouch below configuration by set filterCoeffAddress to NULL , driver will load it from the
     * driver firmware table, otherwise driver will use the value directly.
     */
    uint32_t filterPhases;              /*!< interpolation phases */
    uint64_t filterCenterTap;           /*!< interpolation center tap */
    const uint32_t *filterCoeffAddress; /*!< interpolation coeff address */
} asrc_context_resampler_config_t;

/*! @brief asrc context configuration */
typedef struct _asrc_context_config
{
    uint8_t contextChannelNums;                       /*!< context channel numbers */
    asrc_context_input_config_t contextInput;         /*!< context input configuration */
    asrc_context_output_config_t contextOutput;       /*!< context output configuration */
    asrc_context_prefilter_config_t contextPrefilter; /*!< context pre filter configuration */
    asrc_context_resampler_config_t contextResampler; /*!< context resampler configuration */
} asrc_context_config_t;

/*! @brief ASRC transfer */
typedef struct _asrc_transfer
{
    uint32_t *inDataAddr;  /*!< address of audio data to be converted */
    uint32_t inDataSize;   /*!< size of the audio data */
    uint32_t *outDataAddr; /*!< address of audio data that is been converted */
    uint32_t outDataSize;  /*!< size of the audio data */
} asrc_transfer_t;
/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /*_cplusplus*/

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Get instance number of the ASRC peripheral.
 *
 * @param base ASRC base pointer.
 */
uint32_t ASRC_GetInstance(ASRC_Type *base);

/*!
 * brief Initializes the asrc peripheral.
 *
 * This API gates the asrc clock. The asrc module can't operate unless ASRC_Init is called to enable the clock.
 *
 * param base asrc base pointer.
 */
void ASRC_Init(ASRC_Type *base);

/*!
 * @brief De-initializes the ASRC peripheral.
 *
 * This API gates the ASRC clock and disable ASRC module. The ASRC module can't operate unless ASRC_Init
 *
 * @param base ASRC base pointer.
 */
void ASRC_Deinit(ASRC_Type *base);

/*!
 * @brief ASRC get context default configuration.
 *
 * @param config ASRC context configuration pointer.
 * @param channels input audio data channel numbers.
 * @param inSampleRate input sample rate.
 * @param outSampleRate output sample rate.
 */
void ASRC_GetContextDefaultConfig(asrc_context_config_t *config,
                                  uint32_t channels,
                                  uint32_t inSampleRate,
                                  uint32_t outSampleRate);

/*!
 * @brief ASRC configure context.
 *
 * @param base ASRC base pointer.
 * @param context index of asrc context, reference asrc_context_t.
 * @param config ASRC context configuration pointer.
 * @retval kStatus_InvalidArgument invalid parameters.
 *        kStatus_ASRCConfigureFailed context configure failed.
 *        kStatus_Success context configure success.
 */
status_t ASRC_SetContextConfig(ASRC_Type *base, asrc_context_t context, asrc_context_config_t *config);

/*!
 * @brief ASRC configure context output.
 *
 * @param base ASRC base pointer.
 * @param context index of asrc context, reference asrc_context_t.
 * @param config ASRC context output configuration pointer.
 */
status_t ASRC_SetContextOutputConfig(ASRC_Type *base, asrc_context_t context, asrc_context_output_config_t *config);

/*!
 * @brief ASRC configure context input.
 *
 * @param base ASRC base pointer.
 * @param context index of asrc context, reference asrc_context_t.
 * @param config ASRC context input configuration pointer.
 */
status_t ASRC_SetContextInputConfig(ASRC_Type *base, asrc_context_t context, asrc_context_input_config_t *config);

/*!
 * @brief ASRC context enable run.
 * All control fileds associated with a context must be stable prior to setting context run enable.
 *
 * @param base ASRC base pointer.
 * @param context ASRC context index.
 * @param enable true is enable, inform the datapath begin processing sample data for the context.
 *               false is disable, data processing will halt immediately.
 */
static inline void ASRC_EnableContextRun(ASRC_Type *base, asrc_context_t context, bool enable)
{
    if (enable)
    {
        base->CTX_CTRL[context] |= ASRC_CTX_CTRL_RUN_EN_MASK;
    }
    else
    {
        base->CTX_CTRL[context] &= ~ASRC_CTX_CTRL_RUN_EN_MASK;
    }
}

/*!
 * @brief ASRC context enable run stop.
 * This function used to flush the ASRC pipeline and completely end processing for a context.
 *
 * @param base ASRC base pointer.
 * @param context ASRC context index.
 * @param enable true is enable, false is disable.
 */
static inline void ASRC_EnableContextRunStop(ASRC_Type *base, asrc_context_t context, bool enable)
{
    if (enable)
    {
        base->CTX_CTRL[context] |= ASRC_CTX_CTRL_RUN_STOP_MASK;
    }
    else
    {
        base->CTX_CTRL[context] &= ~ASRC_CTX_CTRL_RUN_STOP_MASK;
    }
}

/*!
 * @brief ASRC context input DMA request enable.
 *
 * @param base ASRC base pointer.
 * @param context ASRC context index.
 * @param enable true is enable, false is disable.
 */
static inline void ASRC_EnableContextInDMA(ASRC_Type *base, asrc_context_t context, bool enable)
{
    if (enable)
    {
        base->CTX_CTRL[context] |= ASRC_CTX_CTRL_FWMDE_MASK;
    }
    else
    {
        base->CTX_CTRL[context] &= ~ASRC_CTX_CTRL_FWMDE_MASK;
    }
}

/*!
 * @brief ASRC context output DMA request enable.
 *
 * @param base ASRC base pointer.
 * @param context ASRC context index.
 * @param enable true is enable, false is disable.
 */
static inline void ASRC_EnableContextOutDMA(ASRC_Type *base, asrc_context_t context, bool enable)
{
    if (enable)
    {
        base->CTX_OUT_CTRL[context] |= ASRC_CTX_OUT_CTRL_FWMDE_MASK;
    }
    else
    {
        base->CTX_OUT_CTRL[context] &= ~ASRC_CTX_OUT_CTRL_FWMDE_MASK;
    }
}

/*!
 * @brief ASRC prefilter bypass mode
 * This function enable or disable the ASRC prefilter bypass mode.
 *
 * @param base ASRC peripheral base address.
 * @param context context processor number.
 * @param bypass true is bypass, false is normal mode.
 */
static inline void ASRC_EnablePreFilterBypass(ASRC_Type *base, asrc_context_t context, bool bypass)
{
    if (bypass)
    {
        base->CTX_CTRL_EXT1[context] |= ASRC_CTX_CTRL_EXT1_PF_BYPASS_MODE_MASK;
        base->CTX_CTRL_EXT1[context] &= ~ASRC_CTX_CTRL_EXT1_PF_EXPANSION_FACTOR_MASK;
        base->CTX_CTRL_EXT2[context] &= ~ASRC_CTX_CTRL_EXT2_ST1_NUM_TAPS_MASK;
    }
    else
    {
        base->CTX_CTRL_EXT1[context] &= ~ASRC_CTX_CTRL_EXT1_PF_BYPASS_MODE_MASK;
    }
}

/*!
 * @brief ASRC resampler bypass mode
 * This function enable or disable the ASRC resampler bypass mode.
 *
 * @param base ASRC peripheral base address.
 * @param context context processor number.
 * @param bypass true is bypass, false is normal mode.
 */
static inline void ASRC_EnableResamplerBypass(ASRC_Type *base, asrc_context_t context, bool bypass)
{
    if (bypass)
    {
        base->CTX_CTRL_EXT1[context] |= ASRC_CTX_CTRL_EXT1_RS_BYPASS_MODE_MASK;
    }
    else
    {
        base->CTX_CTRL_EXT1[context] &= ~ASRC_CTX_CTRL_EXT1_RS_BYPASS_MODE_MASK;
    }
}

/*!
 * @brief ASRC set context channel number.
 * Note: The maximum channel number in one context can not exceed 32.
 *
 * @param base ASRC peripheral base address.
 * @param context context  number.
 * @param channels channel number, should <= 32.
 */
static inline void ASRC_SetContextChannelNumber(ASRC_Type *base, asrc_context_t context, uint32_t channels)
{
    base->CTX_CTRL[context] &= ~ASRC_CTX_CTRL_NUM_CH_EN_MASK;
    base->CTX_CTRL[context] |= ASRC_CTX_CTRL_NUM_CH_EN(channels - 1U);
}

/*!
 * @brief ASRC get output sample count.
 *
 * @param inSampleRate output sample rate.
 * @param inSamplesSize input sample rate.
 * @param inWidth input samples buffer size, the size of buffer should be converted to align with 4 byte .
 * @param outSampleRate input sample width.
 * @param outWidth Output width.
 * @retval output samples size.
 */
uint32_t ASRC_GetContextOutSampleSize(
    uint32_t inSampleRate, uint32_t inSamplesSize, uint32_t inWidth, uint32_t outSampleRate, uint32_t outWidth);

/*! @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief ASRC interrupt enable
 * This function enable the ASRC interrupt with the provided mask.
 *
 * @param base ASRC peripheral base address.
 * @param mask The interrupts to enable. Logical OR of _asrc_interrupt_mask.
 */
static inline void ASRC_EnableInterrupt(ASRC_Type *base, uint32_t mask)
{
    base->IRQ_CTRL &= ~mask;
}

/*!
 * @brief ASRC interrupt disable
 * This function disable the ASRC interrupt with the provided mask.
 *
 * @param base ASRC peripheral base address.
 * @param mask The interrupts to disable. Logical OR of _asrc_interrupt_mask.
 */
static inline void ASRC_DisableInterrupt(ASRC_Type *base, uint32_t mask)
{
    base->IRQ_CTRL |= mask;
}
/*! @} */

/*!
 * @name Status
 * @{
 */

/*!
 * @brief Gets the ASRC interrupt status flag state.
 *
 * @param base ASRC base pointer
 * @return ASRC Tx status flag value. Use the Status Mask to get the status value needed.
 */
static inline uint32_t ASRC_GetInterruptStatus(ASRC_Type *base)
{
    return base->IRQ_FLAGS;
}

/*!
 * @brief clear the ASRC interrupt status flag state.
 *
 * @param base ASRC base pointer
 * @param status status flag to be cleared.
 */
static inline void ASRC_ClearInterruptStatus(ASRC_Type *base, uint32_t status)
{
    base->IRQ_FLAGS |= status;
}

/*!
 * @brief Gets the ASRC fifo status flag.
 *
 * @param base ASRC base pointer
 * @param context context id
 */
static inline uint32_t ASRC_GetFifoStatus(ASRC_Type *base, asrc_context_t context)
{
    return (uint32_t)(base->SAMPLE_FIFO_STATUS[context] &
                      (ASRC_SAMPLE_FIFO_STATUS_OUTFIFO_WTMK_MASK | ASRC_SAMPLE_FIFO_STATUS_INFIFO_WTMK_MASK));
}

/*! @} */

/*!
 * @name fifo Operations
 * @{
 */
/*!
 * @brief write the ASRC context fifo.
 *
 * @param base ASRC base pointer.
 * @param context context id.
 * @param data data to write.
 */
static inline void ASRC_WriteContextFifo(ASRC_Type *base, asrc_context_t context, uint32_t data)
{
    base->WRFIFO[context] = data;
}

/*!
 * @brief read the ASRC context fifo.
 *
 * @param base ASRC base pointer.
 * @param context context id.
 * @retval read data.
 */
static inline uint32_t ASRC_ReadContextFifo(ASRC_Type *base, asrc_context_t context)
{
    return base->RDFIFO[context];
}

/*!
 * @brief Get ASRC write fifo address.
 *
 * @param base ASRC base pointer.
 * @param context context id.
 * @retval write fifo address.
 */
static inline uint32_t ASRC_GetWriteContextFifoAddr(ASRC_Type *base, asrc_context_t context)
{
    return (uint32_t)&base->WRFIFO[context];
}

/*!
 * @brief Get the ASRC read context fifo address.
 *
 * @param base ASRC base pointer.
 * @param context context id.
 * @retval read fifo address.
 */
static inline uint32_t ASRC_GetReadContextFifoAddr(ASRC_Type *base, asrc_context_t context)
{
    return (uint32_t)&base->RDFIFO[context];
}

/*!
 * @brief Get the ASRC read fifo remained samples.
 * Since the DMA request will be triggered only when the sample group in read fifo is bigger then the watermark, so when
 * the data size cannot be divisible by the (watermark + 1), then part of sample will left in read fifo, application
 * should call this api to get the left samples.
 *
 * @param base ASRC base pointer.
 * @param context context id.
 * @param outAddr address to receive remained sample in read fifo.
 * @param outWidth output data width.
 * @param sampleCount specify the read sample count.
 * @retval sample counts actual read from output fifo.
 */
uint32_t ASRC_ReadFIFORemainedSample(
    ASRC_Type *base, asrc_context_t context, uint32_t *outAddr, uint32_t outWidth, uint32_t sampleCount);

/*! @} */

/*!
 * @name Transactional
 * @{
 */

/*!
 * @brief ASRC blocking convert audio sample rate.
 * This function depends on the configuration of input and output, so it should be called after the
 * ASRC_SetContextConfig. The data format it supports:
 * 1.16bit 16bit per sample in input buffer, input buffer size
 * should be calculate as: samples 2U output buffer size can be calculated by call function
 * ASRC_GetContextOutSampleSize, the parameter outWidth should be 2
 * 2.20bit 24bit per sample in input buffer, input buffer size should be calculate as: samples 3U output buffer size can
 * be calculated by call function ASRC_GetContextOutSampleSize, the outWidth should be 3. 3.24bit 24bit per sample in
 * input buffer, input buffer size should be calculate as: samples * 3U output buffer size can be calculated by call
 * function ASRC_GetContextOutSampleSize, the outWidth should be 3. 4.32bit 32bit per sample in input buffer, input
 * buffer size should be calculate as: samples * 4U output buffer size can be calculated by call function
 * ASRC_GetContextOutSampleSize, the outWidth should be 4.
 *
 * @param base ASRC base pointer.
 * @param context context id.
 * @param xfer .xfer configuration.
 * @retval kStatus_Success.
 */
status_t ASRC_TransferBlocking(ASRC_Type *base, asrc_context_t context, asrc_transfer_t *xfer);

/*! @} */

#if defined(__cplusplus)
}
#endif /*_cplusplus*/

/*! @} */

#endif /* _FSL_ASRC_H_ */
