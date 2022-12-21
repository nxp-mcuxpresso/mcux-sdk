/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __HAL_AUDIO_ADAPTER_H__
#define __HAL_AUDIO_ADAPTER_H__

#include "fsl_common.h"

/*!
 * @addtogroup Audio_Adapter
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#if defined(SAI_XFER_QUEUE_SIZE)
#define HAL_AUDIO_QUEUE_SIZE ((uint32_t)SAI_XFER_QUEUE_SIZE)
#elif defined(I2S_NUM_BUFFERS)
#define HAL_AUDIO_QUEUE_SIZE ((uint32_t)I2S_NUM_BUFFERS)
#else
#define HAL_AUDIO_QUEUE_SIZE (4U)
#endif

#ifndef HAL_AUDIO_DMA_INIT_ENABLE
#define HAL_AUDIO_DMA_INIT_ENABLE (1U)
#endif /* HAL_AUDIO_DMA_INIT_ENABLE */

#if defined(__GIC_PRIO_BITS)
#ifndef HAL_AUDIO_ISR_PRIORITY
#define HAL_AUDIO_ISR_PRIORITY (25U)
#endif /* HAL_AUDIO_ISR_PRIORITY */
#else  /* __GIC_PRIO_BITS */
#if defined(configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY)
#ifndef HAL_AUDIO_ISR_PRIORITY
#define HAL_AUDIO_ISR_PRIORITY (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY)
#endif /* HAL_AUDIO_ISR_PRIORITY */
#else
/* The default value 3 is used to support different ARM Core, such as CM0P, CM4, CM7, and CM33, etc.
 * The minimum number of priority bits implemented in the NVIC is 2 on these SOCs. The value of mininum
 * priority is 3 (2^2 - 1). So, the default value is 3.
 */
#ifndef HAL_AUDIO_ISR_PRIORITY
#define HAL_AUDIO_ISR_PRIORITY (3U)
#endif /* HAL_AUDIO_ISR_PRIORITY */
#endif /* configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY */
#endif /* __GIC_PRIO_BITS */

#if (defined(FSL_FEATURE_SOC_FLEXCOMM_COUNT) && (FSL_FEATURE_SOC_FLEXCOMM_COUNT > 0U)) && \
    (defined(FSL_FEATURE_SOC_I2S_COUNT) && (FSL_FEATURE_SOC_I2S_COUNT > 0U))
#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
#define HAL_AUDIO_I2S_DMA_HANDLE_SIZE (HAL_AUDIO_QUEUE_SIZE * 8U + 48U)
#define HAL_AUDIO_HANDLE_SIZE_TEMP    (HAL_AUDIO_I2S_DMA_HANDLE_SIZE + 12U)
#else
#error This SOC does not have DMA available!
#endif /* FSL_FEATURE_SOC_DMA_COUNT */

#elif (defined(FSL_FEATURE_SOC_I2S_COUNT) && (FSL_FEATURE_SOC_I2S_COUNT > 0U))
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U)) || \
    (defined(FSL_FEATURE_SOC_DMA4_COUNT) && (FSL_FEATURE_SOC_DMA4_COUNT > 0U))
#define HAL_AUDIO_SAI_EDMA_HANDLE_SIZE (HAL_AUDIO_QUEUE_SIZE * 44U + 92U)
#define HAL_AUDIO_HANDLE_SIZE_TEMP     (HAL_AUDIO_SAI_EDMA_HANDLE_SIZE + 12U)
#elif (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
#define HAL_AUDIO_SAI_DMA_HANDLE_SIZE (HAL_AUDIO_QUEUE_SIZE * 12U + 12U)
#define HAL_AUDIO_HANDLE_SIZE_TEMP    (HAL_AUDIO_SAI_DMA_HANDLE_SIZE + 12U)
#else
#error This SOC does not have DMA or EDMA available!
#endif /*FSL_FEATURE_SOC_EDMA_COUNT or FSL_FEATURE_SOC_DMA_COUNT */

#else  /* FSL_FEATURE_SOC_FLEXCOMM_COUNT && FSL_FEATURE_SOC_I2S_COUNT */
#endif /* FSL_FEATURE_SOC_FLEXCOMM_COUNT && FSL_FEATURE_SOC_I2S_COUNT */

/*! @brief Definition of audio adapter handle size. */
#define HAL_AUDIO_HANDLE_SIZE (HAL_AUDIO_HANDLE_SIZE_TEMP)

/*! @brief HAL Audio status. */
typedef enum _hal_AUDIO_status
{
    kStatus_HAL_AudioSuccess   = kStatus_Success,                      /*!< Successfully */
    kStatus_HAL_AudioError     = MAKE_STATUS(kStatusGroup_HAL_I2S, 1), /*!< Error occurs on HAL Audio */
    kStatus_HAL_AudioBusy      = MAKE_STATUS(kStatusGroup_HAL_I2S, 2), /*!< HAL Audio is busy with current transfer */
    kStatus_HAL_AudioIdle      = MAKE_STATUS(kStatusGroup_HAL_I2S, 3), /*!< HAL Audio transmitter is idle */
    kStatus_HAL_AudioQueueFull = MAKE_STATUS(kStatusGroup_HAL_I2S, 4), /*!< Transfer queue is full */
} hal_audio_status_t;

/*! @brief HAL Audio channel number */
typedef enum _hal_audio_channel
{
    kHAL_AudioMono      = 0x7FU, /*!< Only one channel on bus. */
    kHAL_AudioMonoRight = 0x0U,  /*!< Only Right channel have sound. */
    kHAL_AudioMonoLeft,          /*!< Only left channel have sound. */
    kHAL_AudioStereo,            /*!< Stereo sound. */
    kHAL_AudioStereo3Channel,    /*!< Stereo 3 channel sound. */
    kHAL_AudioStereo4Channel,    /*!< Stereo 4 channel sound. */
    kHAL_AudioStereo5Channel,    /*!< Stereo 5 channel sound. */
    kHAL_AudioStereo6Channel,    /*!< Stereo 6 channel sound. */
    kHAL_AudioStereo7Channel,    /*!< Stereo 7 channel sound. */
    kHAL_AudioStereo8Channel,    /*!< Stereo 8 channel sound. */
    kHAL_AudioStereo9Channel,    /*!< Stereo 9 channel sound. */
    kHAL_AudioStereo10Channel,   /*!< Stereo 10 channel sound. */
    kHAL_AudioStereo11Channel,   /*!< Stereo 11 channel sound. */
    kHAL_AudioStereo12Channel,   /*!< Stereo 12 channel sound. */
    kHAL_AudioStereo13Channel,   /*!< Stereo 13 channel sound. */
    kHAL_AudioStereo14Channel,   /*!< Stereo 14 channel sound. */
    kHAL_AudioStereo15Channel,   /*!< Stereo 15 channel sound. */
    kHAL_AudioStereo16Channel,   /*!< Stereo 16 channel sound. */
} hal_audio_channel_t;

/*! @brief HAL Audio sample rate */
typedef enum _hal_audio_sample_rate
{
    kHAL_AudioSampleRate8KHz    = 8000U,   /*!< Sample rate 8000 Hz */
    kHAL_AudioSampleRate11025Hz = 11025U,  /*!< Sample rate 11025 Hz */
    kHAL_AudioSampleRate12KHz   = 12000U,  /*!< Sample rate 12000 Hz */
    kHAL_AudioSampleRate16KHz   = 16000U,  /*!< Sample rate 16000 Hz */
    kHAL_AudioSampleRate22050Hz = 22050U,  /*!< Sample rate 22050 Hz */
    kHAL_AudioSampleRate24KHz   = 24000U,  /*!< Sample rate 24000 Hz */
    kHAL_AudioSampleRate32KHz   = 32000U,  /*!< Sample rate 32000 Hz */
    kHAL_AudioSampleRate44100Hz = 44100U,  /*!< Sample rate 44100 Hz */
    kHAL_AudioSampleRate48KHz   = 48000U,  /*!< Sample rate 48000 Hz */
    kHAL_AudioSampleRate96KHz   = 96000U,  /*!< Sample rate 96000 Hz */
    kHAL_AudioSampleRate192KHz  = 192000U, /*!< Sample rate 192000 Hz */
    kHAL_AudioSampleRate384KHz  = 384000U, /*!< Sample rate 384000 Hz */
} hal_audio_sample_rate_t;

/*! @brief HAL Audio bit width */
typedef enum _hal_audio_bit_width
{
    kHAL_AudioWordWidth8bits  = 8U,  /*!< Audio data width 8 bits */
    kHAL_AudioWordWidth16bits = 16U, /*!< Audio data width 16 bits */
    kHAL_AudioWordWidth24bits = 24U, /*!< Audio data width 24 bits */
    kHAL_AudioWordWidth32bits = 32U, /*!< Audio data width 32 bits */
} hal_audio_bit_width_t;

/*! @brief HAL Audio bit clock polarity */
typedef enum _hal_audio_bclk_polarity
{
    kHAL_AudioSampleOnFallingEdge = 0x00U, /*!< Data samples at the falling edge. */
    kHAL_AudioSampleOnRisingEdge,          /*!< Data samples at the rising edge. */
} hal_audio_bclk_polarity_t;

/*! @brief HAL Audio frame sync width */
typedef enum _hal_audio_frame_sync_width
{
    kHAL_AudioFrameSyncWidthOneBitClk = 0x00U, /*!< 1 bit clock frame sync len for DSP mode */
    kHAL_AudioFrameSyncWidthPerWordWidth,      /*!< Frame sync length decided by word width */
    kHAL_AudioFrameSyncWidthHalfFrame,         /*!< Frame sync length is half of frame length */
} hal_audio_frame_sync_width_t;

/*! @brief HAL Audio frame sync polarity */
typedef enum _hal_audio_frame_sync_polarity
{
    kHAL_AudioBeginAtRisingEdge = 0x00U, /*!< Frame sync begins at the rising edge. */
    kHAL_AudioBeginAtFallingEdge,        /*!< Frame sync begins at the falling edge. */
} hal_audio_frame_sync_polarity_t;

/*! @brief HAL Audio master or slave mode */
typedef enum _hal_audio_master_slave
{
    kHAL_AudioMaster = 0x0U,            /*!< Master mode include bclk and frame sync */
    kHAL_AudioSlave,                    /*!< Slave mode  include bclk and frame sync */
    kHAL_AudioBclkMasterFrameSyncSlave, /*!< BCLK in master mode, frame sync in slave mode */
    kHAL_AudioBclkSlaveFrameSyncMaster, /*!< BCLK in slave mode, frame sync in master mode */
} hal_audio_master_slave_t;

/*! @brief Synchronous or asynchronous mode, only for SAI configuration */
typedef enum _hal_audio_sai_sync_mode
{
    kHAL_AudioSaiModeAsync = 0x0U, /*!< Asynchronous mode */
    kHAL_AudioSaiModeSync,         /*!< Synchronous mode (with receiver or transmit) */
} hal_audio_sai_sync_mode_t;

/*! @brief HAL Audio data format */
typedef enum _hal_audio_data_format
{
    kHAL_AudioDataFormatI2sClassic = 0x0U, /*!< I2S classic mode */
    kHAL_AudioDataFormatLeftJustified,     /*!< Left-Justified mode */
    kHAL_AudioDataFormatRightJustified,    /*!< Right-Justified mode */
    kHAL_AudioDataFormatDspModeA,          /*!< DSP mode A, channel is available on 2nd rising edge of BCLK
                                                following a rising edge of frame sync */
    kHAL_AudioDataFormatDspModeB,          /*!< DSP mode B, channel is available on 1st rising edge of BCLK
                                                following a rising edge of frame sync */
} hal_audio_data_format_t;

/*! @brief HAL Audio DMA channel priority */
typedef enum _hal_audio_dma_channel_priority
{
    kHAL_AudioDmaChannelPriority0 = 0x0U,
    kHAL_AudioDmaChannelPriority1,
    kHAL_AudioDmaChannelPriority2,
    kHAL_AudioDmaChannelPriority3,
    kHAL_AudioDmaChannelPriority4,
    kHAL_AudioDmaChannelPriority5,
    kHAL_AudioDmaChannelPriority6,
    kHAL_AudioDmaChannelPriority7,
    kHAL_AudioDmaChannelPriority8,
    kHAL_AudioDmaChannelPriority9,
    kHAL_AudioDmaChannelPriority10,
    kHAL_AudioDmaChannelPriority11,
    kHAL_AudioDmaChannelPriority12,
    kHAL_AudioDmaChannelPriority13,
    kHAL_AudioDmaChannelPriority14,
    kHAL_AudioDmaChannelPriority15,
    kHAL_AudioDmaChannelPriority16,
    kHAL_AudioDmaChannelPriority17,
    kHAL_AudioDmaChannelPriority18,
    kHAL_AudioDmaChannelPriority19,
    kHAL_AudioDmaChannelPriority20,
    kHAL_AudioDmaChannelPriority21,
    kHAL_AudioDmaChannelPriority22,
    kHAL_AudioDmaChannelPriority23,
    kHAL_AudioDmaChannelPriority24,
    kHAL_AudioDmaChannelPriority25,
    kHAL_AudioDmaChannelPriority26,
    kHAL_AudioDmaChannelPriority27,
    kHAL_AudioDmaChannelPriority28,
    kHAL_AudioDmaChannelPriority29,
    kHAL_AudioDmaChannelPriority30,
    kHAL_AudioDmaChannelPriority31,
    kHAL_AudioDmaChannelPriorityDefault = 0xFFU, /*!< Use default value, not to configure priority. */
} hal_audio_dma_channel_priority_t;

/*! @brief HAL Audio DMA mux user configuration */
typedef struct _hal_audio_dma_mux_config_t
{
    union
    {
        struct
        {
            uint8_t dmaMuxInstance;
            uint32_t dmaRequestSource;
        } dmaMuxConfig;
    };
} hal_audio_dma_mux_config_t;

/*! @brief HAL Audio DMA channel mux user configuration */
typedef struct _hal_audio_dma_channel_mux_config_t
{
    union
    {
        struct
        {
            uint32_t dmaRequestSource;
        } dmaChannelMuxConfig;
    };
} hal_audio_dma_channel_mux_config_t;

/*! @brief HAL Audio DMA extra user configuration */
typedef struct _hal_audio_dma_extra_config_t
{
    union
    {
        /* DMA4 use this structure */
        struct
        {
            bool enableMasterIdReplication;
        } edmaExtraConfig;
    };
} hal_audio_dma_extra_config_t;

/*! @brief HAL Audio DMA user configuration */
typedef struct _hal_audio_dma_config
{
    uint8_t instance;                          /*!< DMA instance */
    uint8_t channel;                           /*!< DMA channel */
    hal_audio_dma_channel_priority_t priority; /*!< DMA channel priority */

    bool enablePreemption;     /*!< If true, a channel can be suspended by other channel with higher priority.
                                    Not all SOCs support this feature. For example, EDMA, DMA4 supports this feature.
                                    For detailed information please refer to the SOC corresponding RM.
                                    If not supported, the value should be set to false. */
    bool enablePreemptAbility; /*!< If true, a channel can suspend other channel with low priority
                                    Not all SOCs support this feature. For example, EDMA, DMA4 supports this feature.
                                    For detailed information please refer to the SOC corresponding RM.
                                    If not supported, the value should be set to false. */
    void *dmaMuxConfig;        /*!< The pointer points to an entity defined by hal_audio_dma_mux_config_t.
                                    Not all SOCs support this feature. In general, when the macro
                                    FSL_FEATURE_SOC_DMAMUX_COUNT is defined as non-zero, the SOC supports this
                                    feature. For detailed information please refer to the SOC corresponding RM.
                                    If not supported, the pointer should be set to NULL. */
    void *dmaChannelMuxConfig; /*!< The pointer points to an entity defined by hal_audio_dma_channel_mux_config_t.
                                    Not all SOCs support this feature. In general, when the macro
                                    FSL_FEATURE_EDMA_HAS_CHANNEL_MUX is defined as non-zero, the SOC supports this
                                    feature. For detailed information please refer to the SOC corresponding RM.
                                    If not supported, the pointer should be set to NULL. */
    void *dmaChannelConfig;    /*!< The pointer points to an entity defined by channel configuration structure
                                    that is defined in dma driver, such as edma_channel_config_t.
                                    Not all SOCs support this feature. In general, when the macro
                                    FSL_FEATURE_EDMA_HAS_CHANNEL_CONFIG is defined as non-zero, the SOC supports this
                                    feature. For detailed information please refer to the SOC corresponding RM.
                                    If not supported, the pointer should be set to NULL. */
    void *dmaExtraConfig;      /*!< The pointer points to an entity defined by hal_audio_dma_extra_config_t.
                                    Some DMA IPs have extra configurations, such as EDMA, DMA4.
                                    The structure is used for these extra configurations.
                                    Not all SOCs support this feature. For detailed information please refer to the
                                    SOC corresponding RM. If not supported, the pointer should be set to NULL. */
} hal_audio_dma_config_t;

/*! @brief HAL Audio IP specific feature configuration */
typedef struct _hal_audio_ip_config
{
    union
    {
        /* SAI port use this structure */
        struct
        {
            uint32_t lineMask; /*!< Writing one to the corresponding bit reprsents the corresponding data line is
                                  enabled. lineMask = 0x1U, represents RX0/TX0 data line is enabled.
                                    lineMask = 0xFU, represents RX0-3/TX0-3 data line are enabled. */
            hal_audio_sai_sync_mode_t syncMode; /*!< SAI sync mode, control Tx/Rx clock sync */
        } sai;
    };
} hal_audio_ip_config_t;

/*! @brief HAL Audio configuration structure. */
typedef struct _hal_audio_config
{
    hal_audio_dma_config_t *dmaConfig; /*!< DMA configuration */
    void *ipConfig;                    /*!< IP specific feature configuration. The pointer
                                            points to an entity defined by hal_audio_ip_config_t.
                                            If there is no specific feature configuration, it should be set to NULL. */

    uint32_t srcClock_Hz;   /*!< Source clock  */
    uint32_t sampleRate_Hz; /*!< Sample rate */
    uint16_t frameLength;   /*!< Only flexcomm_i2s uses this field. In most cases, frameLength is equal to bitWidth
                                 times lineChannels. In some cases, frameLength needs to be set to other value.
                                 For example, when the number of bit clock on the bus between two neighboring WS
                                 value is greater than bitWidth times lineChannels, frameLength needs to be set to
                                 the value that is equal to the number of bit clock between two neighboring WS signal.
                                 SAI does not use this field because frameLength can be determined internally
                                 by bitWidth and lineChannels. */

    uint16_t fifoWatermark; /*!< FIFO watermark value. Generally, the value is set to half the number of FIFO(F).
                                 Note that the receive(R) or transmit length(T) is related to fifoWatermark(W) and
                                 bitWidth(B). The relationship between them is: R = N * W * B, T = N * (F - W) * B
                                 (N is integer). On some SOCs, the W and (F - W) is constant 1 and setting the W
                                 does not take effect. In that case the fifoWatermark does not need to be set.
                                 If the value set by application is greater than the number of FIFO,
                                 a maximum value will be used. For example, if the number of FIFO is 32 on a SOC
                                 but the watermark is set to 64 by application, the real value that is written to
                                 register will be 31. */

    hal_audio_master_slave_t msaterSlave;   /*!< master or slave, configure where the bclk and frame sync come from. */
    hal_audio_bclk_polarity_t bclkPolarity; /*!< bclk polarity, data sample on rising edge or falling edge. */

    hal_audio_frame_sync_width_t frameSyncWidth; /*!< Only DSP mode uses this field. For other data format, this field
                                                      does not need to be set and the frameSyncWidth is determined
                                                      internally that depends on different mode. For example, for I2S
                                                      classic mode, frameSyncWidth is equal to bitWidth. */
    hal_audio_frame_sync_polarity_t frameSyncPolarity; /*!< frame sync polarity, frame sync begin at rising or falling
                                                            edge. This field is not used now and reserved for future
                                                            use. The frameSyncPolarity is set internally that depends
                                                            on different mode. For example, for I2S classic mode,
                                                            frameSyncWidth is equal to kHAL_AudioBeginAtFallingEdge. */

    hal_audio_channel_t lineChannels;   /*!< Configure the number of channel on the data line. */
    hal_audio_data_format_t dataFormat; /*!< data format on bus */

    uint8_t bitWidth; /*!< Bit Width */
    uint8_t instance; /*!< Instance (0 - I2S0/SAI0, 1 - I2S1/SAI1, ...), for detailed information please refer to the
                           SOC corresponding RM. Invalid instance value will cause initialization failure. */
} hal_audio_config_t;

/*! @brief HAL Audio transfer structure. */
typedef struct _hal_audio_transfer
{
    uint8_t *data;   /*!< A transfer buffer. */
    size_t dataSize; /*!< A transfer size. */
} hal_audio_transfer_t;

/*! @brief HAL Audio transfer handle. */
typedef void *hal_audio_handle_t;

/*!
 * @brief Defines the Audio handle
 *
 * This macro is used to define a 4 byte aligned Audio handle.
 * Then use "(hal_audio_handle_t)name" to get the Audio handle.
 *
 * The macro should be global and could be optional. You could also define Audio handle by yourself.
 *
 * This is an example,
 * @code
 *   HAL_AUDIO_HANDLE_DEFINE(audioTxHandle);
 * @endcode
 *
 * @param name The name string of the Audio transfer handle.
 */
#define HAL_AUDIO_HANDLE_DEFINE(name) uint32_t name[(HAL_AUDIO_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t)]

/*!
 * @brief HAL Audio completion callback function pointer type.
 *
 * This callback is used only for the non-blocking Audio transfer API. Specify the callback you wish to use
 * in the call to HAL_AudioTxInstallCallback() or HAL_AudioRxInstallCallback().
 *
 * @param handle audio transfer handle pointer, this should be a static variable.
 * @param completionStatus Either #kStatus_HAL_AudioIdle or an error code describing how the transfer completed.
 * @param callbackParam Arbitrary pointer-sized value passed from the application.
 */
typedef void (*hal_audio_transfer_callback_t)(hal_audio_handle_t handle,
                                              hal_audio_status_t completionStatus,
                                              void *callbackParam);

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /*_cplusplus. */

/*!
 * @name Initialization and de-initialization
 * @{
 */

/*!
 * @brief Initializes the HAL Audio peripheral.
 *
 * @note This API should be called at the beginning of the application.
 * Otherwise, any operation to the HAL Audio module can cause a hard fault
 * because the clock is not enabled. This function configures the audio
 * with user-defined settings. The user can configure the configuration
 * structure. The parameter handle is a pointer to point to a memory space
 * of size #HAL_AUDIO_HANDLE_SIZE allocated by the caller.
 *
 * @note DMA will be initialized and enabled by default in this function and calling
 * HAL_AudioTransferSendNonBlocking or HAL_AudioTransferReceiveNonBlocking will use
 * DMA to transfer data. Thus application should avoid initializing DMA repeatedly
 * and dmaConfig should be configured.
 *
 * Example below shows how to use this API to configure the audio peripheral.
 * For SAI,
 * @code
 *   HAL_AUDIO_HANDLE_DEFINE(audioTxHandle);
 *   hal_audio_config_t audioConfig;
 *   hal_audio_dma_config_t dmaConfig;
 *   hal_audio_ip_config_t ipConfig;
 *   hal_audio_dma_mux_config_t dmaMuxConfig;
 *   dmaMuxConfig.dmaMuxConfig.dmaMuxInstance   = 0;
 *   dmaMuxConfig.dmaMuxConfig.dmaRequestSource = (uint32_t)kDmaRequestMuxSai1Tx;
 *   dmaConfig.instance                         = 0;
 *   dmaConfig.channel                          = 0;
 *   dmaConfig.priority                         = kHAL_AudioDmaChannelPriorityDefault;
 *   dmaConfig.enablePreemption                 = false;
 *   dmaConfig.enablePreemptAbility             = false;
 *   dmaConfig.dmaMuxConfig                     = &dmaMuxConfig;
 *   dmaConfig.dmaChannelMuxConfig              = NULL;
 *   ipConfig.sai.lineMask                      = 1U << 0U;
 *   ipConfig.sai.syncMode                      = kHAL_AudioSaiModeAsync;
 *   audioConfig.dmaConfig                      = &dmaConfig;
 *   audioConfig.ipConfig                       = &ipConfig;
 *   audioConfig.srcClock_Hz                    = 24576000;
 *   audioConfig.sampleRate_Hz                  = (uint32_t)kHAL_AudioSampleRate48KHz;
 *   audioConfig.fifoWatermark                  = 16;
 *   audioConfig.msaterSlave                    = kHAL_AudioMaster;
 *   audioConfig.bclkPolarity                   = kHAL_AudioSampleOnRisingEdge;
 *   audioConfig.frameSyncWidth                 = kHAL_AudioFrameSyncWidthHalfFrame;
 *   audioConfig.frameSyncPolarity              = kHAL_AudioBeginAtFallingEdge;
 *   audioConfig.lineChannels                   = kHAL_AudioStereo;
 *   audioConfig.dataFormat                     = kHAL_AudioDataFormatI2sClassic;
 *   audioConfig.bitWidth                       = (uint8_t)kHAL_AudioWordWidth16bits;
 *   audioConfig.instance                       = 0U;
 *   HAL_AudioTxInit((hal_audio_handle_t)audioTxHandle, &audioConfig);
 * @endcode
 * For I2S,
 * @code
 *   HAL_AUDIO_HANDLE_DEFINE(audioTxHandle);
 *   hal_audio_config_t     audioConfig;
 *   hal_audio_dma_config_t dmaConfig;
 *   dmaConfig.instance             = 0;
 *   dmaConfig.channel              = 0;
 *   dmaConfig.priority             = kHAL_AudioDmaChannelPriorityDefault;
 *   dmaConfig.enablePreemption     = false;
 *   dmaConfig.enablePreemptAbility = false;
 *   dmaConfig.dmaMuxConfig         = NULL;
 *   dmaConfig.dmaChannelMuxConfig  = NULL;
 *   audioConfig.dmaConfig          = &dmaConfig;
 *   audioConfig.ipConfig           = NULL;
 *   audioConfig.srcClock_Hz        = 24576000;
 *   audioConfig.sampleRate_Hz      = (uint32_t)kHAL_AudioSampleRate48KHz;
 *   audioConfig.fifoWatermark      = 0;
 *   audioConfig.msaterSlave        = kHAL_AudioMaster;
 *   audioConfig.bclkPolarity       = kHAL_AudioSampleOnRisingEdge;
 *   audioConfig.frameSyncWidth     = kHAL_AudioFrameSyncWidthHalfFrame;
 *   audioConfig.frameSyncPolarity  = kHAL_AudioBeginAtFallingEdge;
 *   audioConfig.lineChannels       = kHAL_AudioStereo;
 *   audioConfig.dataFormat         = kHAL_AudioDataFormatI2sClassic;
 *   audioConfig.bitWidth           = (uint8_t)kHAL_AudioWordWidth16bits;
 *   audioConfig.instance           = 0U;
 *   HAL_AudioTxInit((hal_audio_handle_t)audioTxHandle, &audioConfig);
 * @endcode
 *
 * @param handle Pointer to point to a memory space of size #HAL_AUDIO_HANDLE_SIZE allocated by the caller.
 * The handle should be 4 byte aligned, because unaligned access doesn't be supported on some devices.
 * You can define the handle in the following two ways:
 * #HAL_AUDIO_HANDLE_DEFINE(handle);
 * or
 * uint32_t handle[((HAL_AUDIO_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t))];
 * @param config A pointer to the audio configuration structure
 * @retval kStatus_HAL_AudioSuccess audio initialization succeed
 */
hal_audio_status_t HAL_AudioTxInit(hal_audio_handle_t handle, const hal_audio_config_t *config);

/*!
 * @brief Initializes the HAL Audio peripheral.
 *
 * @note This API should be called at the beginning of the application.
 * Otherwise, any operation to the HAL Audio module can cause a hard fault
 * because the clock is not enabled. This function configures the audio
 * with user-defined settings. The user can configure the configuration
 * structure. The parameter handle is a pointer to point to a memory space
 * of size #HAL_AUDIO_HANDLE_SIZE allocated by the caller.
 *
 * @note DMA will be initialized and enabled by default in this function and calling
 * HAL_AudioTransferSendNonBlocking or HAL_AudioTransferReceiveNonBlocking will use
 * DMA to transfer data. Thus application should avoid initializing DMA repeatedly
 * and dmaConfig should be configured.
 *
 * Example below shows how to use this API to configure the audio peripheral.
 * For SAI,
 * @code
 *   HAL_AUDIO_HANDLE_DEFINE(audioRxHandle);
 *   hal_audio_config_t audioConfig;
 *   hal_audio_dma_config_t dmaConfig;
 *   hal_audio_ip_config_t ipConfig;
 *   hal_audio_dma_mux_config_t dmaMuxConfig;
 *   dmaMuxConfig.dmaMuxConfig.dmaMuxInstance   = 0;
 *   dmaMuxConfig.dmaMuxConfig.dmaRequestSource = (uint32_t)kDmaRequestMuxSai1Rx;
 *   dmaConfig.instance                         = 0;
 *   dmaConfig.channel                          = 0;
 *   dmaConfig.priority                         = kHAL_AudioDmaChannelPriorityDefault;
 *   dmaConfig.enablePreemption                 = false;
 *   dmaConfig.enablePreemptAbility             = false;
 *   dmaConfig.dmaMuxConfig                     = &dmaMuxConfig;
 *   dmaConfig.dmaChannelMuxConfig              = NULL;
 *   ipConfig.sai.lineMask                      = 1U << 0U;
 *   ipConfig.sai.syncMode                      = kHAL_AudioSaiModeAsync;
 *   audioConfig.dmaConfig                      = &dmaConfig;
 *   audioConfig.ipConfig                       = &ipConfig;
 *   audioConfig.srcClock_Hz                    = 24576000;
 *   audioConfig.sampleRate_Hz                  = (uint32_t)kHAL_AudioSampleRate48KHz;
 *   audioConfig.fifoWatermark                  = 16;
 *   audioConfig.msaterSlave                    = kHAL_AudioMaster;
 *   audioConfig.bclkPolarity                   = kHAL_AudioSampleOnRisingEdge;
 *   audioConfig.frameSyncWidth                 = kHAL_AudioFrameSyncWidthHalfFrame;
 *   audioConfig.frameSyncPolarity              = kHAL_AudioBeginAtFallingEdge;
 *   audioConfig.lineChannels                   = kHAL_AudioStereo;
 *   audioConfig.dataFormat                     = kHAL_AudioDataFormatI2sClassic;
 *   audioConfig.bitWidth                       = (uint8_t)kHAL_AudioWordWidth16bits;
 *   audioConfig.instance                       = 0U;
 *   HAL_AudioRxInit((hal_audio_handle_t)audioRxHandle, &audioConfig);
 * @endcode
 * For I2S,
 * @code
 *   HAL_AUDIO_HANDLE_DEFINE(audioRxHandle);
 *   hal_audio_config_t     audioConfig;
 *   hal_audio_dma_config_t dmaConfig;
 *   dmaConfig.instance             = 0;
 *   dmaConfig.channel              = 0;
 *   dmaConfig.priority             = kHAL_AudioDmaChannelPriorityDefault;
 *   dmaConfig.enablePreemption     = false;
 *   dmaConfig.enablePreemptAbility = false;
 *   dmaConfig.dmaMuxConfig         = NULL;
 *   dmaConfig.dmaChannelMuxConfig  = NULL;
 *   audioConfig.dmaConfig          = &dmaConfig;
 *   audioConfig.ipConfig           = NULL;
 *   audioConfig.srcClock_Hz        = 24576000;
 *   audioConfig.sampleRate_Hz      = (uint32_t)kHAL_AudioSampleRate48KHz;
 *   audioConfig.fifoWatermark      = 0;
 *   audioConfig.msaterSlave        = kHAL_AudioMaster;
 *   audioConfig.bclkPolarity       = kHAL_AudioSampleOnRisingEdge;
 *   audioConfig.frameSyncWidth     = kHAL_AudioFrameSyncWidthHalfFrame;
 *   audioConfig.frameSyncPolarity  = kHAL_AudioBeginAtFallingEdge;
 *   audioConfig.lineChannels       = kHAL_AudioStereo;
 *   audioConfig.dataFormat         = kHAL_AudioDataFormatI2sClassic;
 *   audioConfig.bitWidth           = (uint8_t)kHAL_AudioWordWidth16bits;
 *   audioConfig.instance           = 0U;
 *   HAL_AudioRxInit((hal_audio_handle_t)audioRxHandle, &audioConfig);
 * @endcode
 *
 * @param handle Pointer to point to a memory space of size #HAL_AUDIO_HANDLE_SIZE allocated by the caller.
 * The handle should be 4 byte aligned, because unaligned access doesn't be supported on some devices.
 * You can define the handle in the following two ways:
 * #HAL_AUDIO_HANDLE_DEFINE(handle);
 * or
 * uint32_t handle[((HAL_AUDIO_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t))];
 * @param config A pointer to the audio configuration structure
 * @retval kStatus_HAL_AudioSuccess audio initialization succeed
 */
hal_audio_status_t HAL_AudioRxInit(hal_audio_handle_t handle, const hal_audio_config_t *config);

/*!
 * @brief De-initializes the HAL Audio peripheral. Call this API to gate the HAL Audio clock.
 * The HAL Audio module can't work unless the HAL_AudioTxInit is called.
 *
 * @param handle audio handle pointer, this should be a static variable.
 * @retval kStatus_HAL_AudioSuccess audio de-initialization succeed */
hal_audio_status_t HAL_AudioTxDeinit(hal_audio_handle_t handle);
/*!
 * @brief De-initializes the HAL Audio peripheral. Call this API to gate the HAL Audio clock.
 * The HAL Audio module can't work unless the HAL_AudioRxInit is called.
 *
 * @param handle audio handle pointer, this should be a static variable.
 * @retval kStatus_HAL_AudioSuccess audio de-initialization succeed */
hal_audio_status_t HAL_AudioRxDeinit(hal_audio_handle_t handle);

/*! @} */

/*!
 * @name Transactional
 * @{
 */

/*!
 * @brief Installs a callback and callback parameter.
 *
 * This function is used to install the callback and callback parameter for audio module.
 * When any status of the audio changed, the driver will notify the upper layer by the installed callback
 * function. And the status is also passed as status parameter when the callback is called.
 *
 * @param handle audio handle pointer, this should be a static variable.
 * @param callback pointer to user callback function.
 * @param callbackParam user parameter passed to the callback function.
 * @retval kStatus_HAL_AudioSuccess audio tx transfer handle created
 */
hal_audio_status_t HAL_AudioTxInstallCallback(hal_audio_handle_t handle,
                                              hal_audio_transfer_callback_t callback,
                                              void *callbackParam);
/*!
 * @brief Installs a callback and callback parameter.
 *
 * This function is used to install the callback and callback parameter for audio module.
 * When any status of the audio changed, the driver will notify the upper layer by the installed callback
 * function. And the status is also passed as status parameter when the callback is called.
 *
 * @param handle audio handle pointer, this should be a static variable.
 * @param callback pointer to user callback function.
 * @param callbackParam user parameter passed to the callback function.
 * @retval kStatus_HAL_AudioSuccess audio rx transfer handle created
 */
hal_audio_status_t HAL_AudioRxInstallCallback(hal_audio_handle_t handle,
                                              hal_audio_transfer_callback_t callback,
                                              void *callbackParam);

/*!
 * @brief Performs a DMA non-blocking send on the data bus.
 *
 * @note Calling the API returns immediately after transfer initiates. The user can
 * call HAL_AudioTransferGetSendCount to poll the transfer status to check whether
 * the transfer is finished. If the return status is kStatus_HAL_AudioIdle, the transfer
 * is finished.
 *
 * @param handle audio handle pointer, this should be a static variable.
 * @param xfer pointer to hal_audio_transfer_t structure.
 *
 * @note The transmit length(T) is related to fifoWatermark(W), bitWidth(B) and the number of FIFO(F).
 * The relationship between them is: T = N * (F - W) * B (N is integer).
 *
 * @retval kStatus_HAL_AudioSuccess Successfully start the data transmission.
 * @retval kStatus_HAL_AudioBusy Previous transmission still not finished.
 * @retval kStatus_HAL_AudioError An error occurred.
 */
hal_audio_status_t HAL_AudioTransferSendNonBlocking(hal_audio_handle_t handle, hal_audio_transfer_t *xfer);

/*!
 * @brief Performs a DMA non-blocking receive on the HAL Audio bus.
 *
 * @note Calling the API returns immediately after transfer initiates. The user can
 * call HAL_AudioTransferGetReceiveCount to poll the transfer status to check whether
 * the transfer is finished. If the return status is kStatus_HAL_AudioIdle, the transfer
 * is finished.
 *
 * @param handle audio handle pointer, this should be a static variable.
 * @param xfer pointer to hal_audio_transfer_t structure.
 *
 * @note The receive length(R) is related to fifoWatermark(W), bitWidth(B) and the number of FIFO(F).
 * The relationship between them is: R = N * W * B (N is integer).
 *
 * @retval kStatus_HAL_AudioSuccess Successfully start the data transmission.
 * @retval kStatus_HAL_AudioBusy Previous transmission still not finished.
 * @retval kStatus_HAL_AudioError An error occurred.
 */
hal_audio_status_t HAL_AudioTransferReceiveNonBlocking(hal_audio_handle_t handle, hal_audio_transfer_t *xfer);

/*!
 * @brief Aborts a DMA non-blocking transfer early.
 *
 * @note This API can be called at any time when a DMA non-blocking transfer initiates
 * to abort the transfer early.
 *
 * @param handle audio handle pointer, this should be a static variable.
 * @retval kStatus_HAL_AudioSuccess Successfully abort the transfer.
 */
hal_audio_status_t HAL_AudioTransferAbortSend(hal_audio_handle_t handle);

/*!
 * @brief Aborts a DMA non-blocking transfer early.
 *
 * @note This API can be called at any time when a DMA non-blocking transfer initiates
 * to abort the transfer early.
 *
 * @param handle audio handle pointer, this should be a static variable.
 * @retval kStatus_HAL_AudioSuccess Successfully abort the transfer.
 */
hal_audio_status_t HAL_AudioTransferAbortReceive(hal_audio_handle_t handle);

/*!
 * @brief Gets the tx transfer status during a DMA non-blocking transfer.
 *
 * @param handle audio handle pointer, this should be a static variable.
 * @param count Number of bytes sent so far by the non-blocking transaction.
 * @retval kStatus_HAL_AudioSuccess Successfully return the count.
 * @retval kStatus_HAL_AudioIdle Previous transmission has been finished.
 * @retval kStatus_HAL_AudioError An error occurred.
 */
hal_audio_status_t HAL_AudioTransferGetSendCount(hal_audio_handle_t handle, size_t *count);
/*!
 * @brief Gets the rx transfer status during a DMA non-blocking transfer.
 *
 * @param handle audio handle pointer, this should be a static variable.
 * @param count Number of bytes received so far by the non-blocking transaction.
 * @retval kStatus_HAL_AudioSuccess Successfully return the count.
 * @retval kStatus_HAL_AudioIdle Previous transmission has been finished.
 * @retval kStatus_HAL_AudioError An error occurred.
 */
hal_audio_status_t HAL_AudioTransferGetReceiveCount(hal_audio_handle_t handle, size_t *count);

/*! @} */

#if defined(__cplusplus)
}
#endif /*_cplusplus. */
/*! @} */

#endif /* __HAL_AUDIO_ADAPTER_H__*/
