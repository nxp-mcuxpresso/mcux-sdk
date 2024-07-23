/*
 * Copyright  2016-2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_SDMA_H_
#define FSL_SDMA_H_

#include "fsl_common.h"
#include "fsl_sdma_script.h"

/*!
 * @addtogroup sdma
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief SDMA driver version */
#define FSL_SDMA_DRIVER_VERSION (MAKE_VERSION(2, 4, 2)) /*!< Version 2.4.2. */
/*! @} */

#ifndef SDMA_DRIVER_LOAD_RAM_SCRIPT
#define SDMA_DRIVER_LOAD_RAM_SCRIPT (1)
#endif

#ifndef SDMA_DRIVER_LOAD_RAM_SCRIPT
#define SDMA_DRIVER_LOAD_RAM_SCRIPT (1)
#endif

/*! @brief SDMA transfer configuration */
typedef enum _sdma_transfer_size
{
    kSDMA_TransferSize1Bytes = 0x1U, /*!< Source/Destination data transfer size is 1 byte every time */
    kSDMA_TransferSize2Bytes = 0x2U, /*!< Source/Destination data transfer size is 2 bytes every time */
    kSDMA_TransferSize3Bytes = 0x3U, /*!< Source/Destination data transfer size is 3 bytes every time */
    kSDMA_TransferSize4Bytes = 0x0U, /*!< Source/Destination data transfer size is 4 bytes every time */
} sdma_transfer_size_t;

/*! @brief SDMA buffer descriptor status */
typedef enum _sdma_bd_status
{
    kSDMA_BDStatusDone       = 0x1U,  /*!< BD ownership, 0 means ARM core owns the BD, while 1 means SDMA owns BD. */
    kSDMA_BDStatusWrap       = 0x2U,  /*!< While this BD is last one, the next BD will be the first one */
    kSDMA_BDStatusContinuous = 0x4U,  /*!< Buffer is allowed to transfer/receive to/from multiple buffers */
    kSDMA_BDStatusInterrupt  = 0x8U,  /*!< While this BD finished, send an interrupt. */
    kSDMA_BDStatusError      = 0x10U, /*!< Error occurred on buffer descriptor command. */
    kSDMA_BDStatusLast =
        0x20U, /*!< This BD is the last BD in this array. It means the transfer ended after this buffer */
    kSDMA_BDStatusExtend = 0x80U, /*!< Buffer descriptor extend status for SDMA scripts */
} sdma_bd_status_t;

/*! @brief SDMA buffer descriptor command */
typedef enum _sdma_bd_command
{
    kSDMA_BDCommandSETDM  = 0x1U, /*!< Load SDMA data memory from ARM core memory buffer. */
    kSDMA_BDCommandGETDM  = 0x2U, /*!< Copy SDMA data memory to ARM core memory buffer. */
    kSDMA_BDCommandSETPM  = 0x4U, /*!< Load SDMA program memory from ARM core memory buffer. */
    kSDMA_BDCommandGETPM  = 0x6U, /*!< Copy SDMA program memory to ARM core memory buffer. */
    kSDMA_BDCommandSETCTX = 0x7U, /*!< Load context for one channel into SDMA RAM from ARM platform memory buffer. */
    kSDMA_BDCommandGETCTX = 0x3U, /*!< Copy context for one channel from SDMA RAM to ARM platform memory buffer. */
} sdma_bd_command_t;

/*! @brief SDMA context switch mode */
typedef enum _sdma_context_switch_mode
{
    kSDMA_ContextSwitchModeStatic = 0x0U,     /*!< SDMA context switch mode static */
    kSDMA_ContextSwitchModeDynamicLowPower,   /*!< SDMA context switch mode dynamic with low power */
    kSDMA_ContextSwitchModeDynamicWithNoLoop, /*!< SDMA context switch mode dynamic with no loop */
    kSDMA_ContextSwitchModeDynamic,           /*!< SDMA context switch mode dynamic */
} sdma_context_switch_mode_t;

/*! @brief SDMA core clock frequency ratio to the ARM DMA interface. */
typedef enum _sdma_clock_ratio
{
    kSDMA_HalfARMClockFreq = 0x0U, /*!< SDMA core clock frequency half of ARM platform */
    kSDMA_ARMClockFreq,            /*!< SDMA core clock frequency equals to ARM platform */
} sdma_clock_ratio_t;

/*! @brief SDMA transfer type */
typedef enum _sdma_transfer_type
{
    kSDMA_MemoryToMemory = 0x0U,  /*!< Transfer from memory to memory */
    kSDMA_PeripheralToMemory,     /*!< Transfer from peripheral to memory */
    kSDMA_MemoryToPeripheral,     /*!< Transfer from memory to peripheral */
    kSDMA_PeripheralToPeripheral, /*!< Transfer from peripheral to peripheral */
} sdma_transfer_type_t;

/*! @brief Peripheral type use SDMA */
typedef enum sdma_peripheral
{
    kSDMA_PeripheralTypeMemory = 0x0, /*!< Peripheral DDR memory */
    kSDMA_PeripheralTypeUART,         /*!< UART use SDMA */
    kSDMA_PeripheralTypeUART_SP,      /*!< UART instance in SPBA use SDMA */
    kSDMA_PeripheralTypeSPDIF,        /*!< SPDIF use SDMA */
    kSDMA_PeripheralNormal,           /*!< Normal peripheral use SDMA */
    kSDMA_PeripheralNormal_SP,        /*!< Normal peripheral in SPBA use SDMA */
    kSDMA_PeripheralMultiFifoPDM,     /*!< multi fifo PDM */
    kSDMA_PeripheralMultiFifoSaiRX,   /*!< multi fifo sai rx use SDMA */
    kSDMA_PeripheralMultiFifoSaiTX,   /*!< multi fifo sai tx use SDMA */
    kSDMA_PeripheralASRCM2P,          /*!< asrc m2p */
    kSDMA_PeripheralASRCP2M,          /*!< asrc p2m */
    kSDMA_PeripheralASRCP2P,          /*!< asrc p2p */
} sdma_peripheral_t;

/*! @brief _sdma_transfer_status SDMA transfer status */
enum
{
    kStatus_SDMA_ERROR = MAKE_STATUS(kStatusGroup_SDMA, 0), /*!< SDMA context error. */
    kStatus_SDMA_Busy  = MAKE_STATUS(kStatusGroup_SDMA, 1), /*!< Channel is busy and can't handle the
                                                                 transfer request. */
};

/*! @brief _sdma_multi_fifo_mask SDMA multi fifo mask */
enum
{
    kSDMA_MultiFifoWatermarkLevelMask = 0xFFFU, /*!< multi fifo watermark level mask */
    kSDMA_MultiFifoNumsMask           = 0xFU,   /*!< multi fifo nums mask */
    kSDMA_MultiFifoOffsetMask         = 0xFU,   /*!< multi fifo offset mask */
    kSDMA_MultiFifoSwDoneMask         = 0x1U,   /*!< multi fifo sw done mask */
    kSDMA_MultiFifoSwDoneSelectorMask = 0xFU,   /*!< multi fifo sw done selector mask */
};

/*! @brief _sdma_multi_fifo_shift SDMA multi fifo shift */
enum
{
    kSDMA_MultiFifoWatermarkLevelShift = 0U,  /*!< multi fifo watermark level shift */
    kSDMA_MultiFifoNumsShift           = 12U, /*!< multi fifo nums shift */
    kSDMA_MultiFifoOffsetShift         = 16U, /*!< multi fifo offset shift */
    kSDMA_MultiFifoSwDoneShift         = 23U, /*!< multi fifo sw done shift */
    kSDMA_MultiFifoSwDoneSelectorShift = 24U, /*!< multi fifo sw done selector shift */
};

/*! @brief _sdma_done_channel SDMA done channel */
enum
{
    kSDMA_DoneChannel0 = 0U, /*!< SDMA done channel 0 */
    kSDMA_DoneChannel1 = 1U, /*!< SDMA done channel 1 */
    kSDMA_DoneChannel2 = 2U, /*!< SDMA done channel 2 */
    kSDMA_DoneChannel3 = 3U, /*!< SDMA done channel 3 */
    kSDMA_DoneChannel4 = 4U, /*!< SDMA done channel 4 */
    kSDMA_DoneChannel5 = 5U, /*!< SDMA done channel 5 */
    kSDMA_DoneChannel6 = 6U, /*!< SDMA done channel 6 */
    kSDMA_DoneChannel7 = 7U, /*!< SDMA done channel 7 */
};

/*! @brief SDMA done source */
typedef enum _sdma_done_src
{
    kSDMA_DoneSrcSW         = 0U,  /*!< software done */
    kSDMA_DoneSrcHwEvent0U  = 1U,  /*!< HW event 0 is used for DONE event */
    kSDMA_DoneSrcHwEvent1U  = 2U,  /*!< HW event 1 is used for DONE event */
    kSDMA_DoneSrcHwEvent2U  = 3U,  /*!< HW event 2 is used for DONE event */
    kSDMA_DoneSrcHwEvent3U  = 4U,  /*!< HW event 3 is used for DONE event */
    kSDMA_DoneSrcHwEvent4U  = 5U,  /*!< HW event 4 is used for DONE event */
    kSDMA_DoneSrcHwEvent5U  = 6U,  /*!< HW event 5 is used for DONE event */
    kSDMA_DoneSrCHwEvent6U  = 7U,  /*!< HW event 6 is used for DONE event */
    kSDMA_DoneSrcHwEvent7U  = 8U,  /*!< HW event 7 is used for DONE event */
    kSDMA_DoneSrcHwEvent8U  = 9U,  /*!< HW event 8 is used for DONE event */
    kSDMA_DoneSrcHwEvent9U  = 10U, /*!< HW event 9 is used for DONE event */
    kSDMA_DoneSrcHwEvent10U = 11U, /*!< HW event 10 is used for DONE event */
    kSDMA_DoneSrcHwEvent11U = 12U, /*!< HW event 11 is used for DONE event */
    kSDMA_DoneSrcHwEvent12U = 13U, /*!< HW event 12 is used for DONE event */
    kSDMA_DoneSrcHwEvent13U = 14U, /*!< HW event 13 is used for DONE event */
    kSDMA_DoneSrcHwEvent14U = 15U, /*!< HW event 14 is used for DONE event */
    kSDMA_DoneSrcHwEvent15U = 16U, /*!< HW event 15 is used for DONE event */
    kSDMA_DoneSrcHwEvent16U = 17U, /*!< HW event 16 is used for DONE event */
    kSDMA_DoneSrcHwEvent17U = 18U, /*!< HW event 17 is used for DONE event */
    kSDMA_DoneSrcHwEvent18U = 19U, /*!< HW event 18 is used for DONE event */
    kSDMA_DoneSrcHwEvent19U = 20U, /*!< HW event 19 is used for DONE event */
    kSDMA_DoneSrcHwEvent20U = 21U, /*!< HW event 20 is used for DONE event */
    kSDMA_DoneSrcHwEvent21U = 22U, /*!< HW event 21 is used for DONE event */
    kSDMA_DoneSrcHwEvent22U = 23U, /*!< HW event 22 is used for DONE event */
    kSDMA_DoneSrcHwEvent23U = 24U, /*!< HW event 23 is used for DONE event */
    kSDMA_DoneSrcHwEvent24U = 25U, /*!< HW event 24 is used for DONE event */
    kSDMA_DoneSrcHwEvent25U = 26U, /*!< HW event 25 is used for DONE event */
    kSDMA_DoneSrcHwEvent26U = 27U, /*!< HW event 26 is used for DONE event */
    kSDMA_DoneSrcHwEvent27U = 28U, /*!< HW event 27 is used for DONE event */
    kSDMA_DoneSrcHwEvent28U = 29U, /*!< HW event 28 is used for DONE event */
    kSDMA_DoneSrcHwEvent29U = 30U, /*!< HW event 29 is used for DONE event */
    kSDMA_DoneSrcHwEvent30U = 31U, /*!< HW event 30 is used for DONE event */
    kSDMA_DoneSrcHwEvent31U = 32U, /*!< HW event 31 is used for DONE event */
} sdma_done_src_t;

/*! @brief SDMA global configuration structure.*/
typedef struct _sdma_config
{
    bool enableRealTimeDebugPin;   /*!< If enable real-time debug pin, default is closed to reduce power consumption.*/
    bool isSoftwareResetClearLock; /*!< If software reset clears the LOCK bit which prevent writing SDMA scripts into
                                      SDMA.*/
    sdma_clock_ratio_t ratio;      /*!< SDMA core clock ratio to ARM platform DMA interface */
} sdma_config_t;

/*! @brief SDMA multi fifo configurations.*/
typedef struct _sdma_multi_fifo_config
{
    uint8_t fifoNums;   /*!< fifo numbers */
    uint8_t fifoOffset; /*!< offset between multi fifo data register address */
} sdma_multi_fifo_config_t;

/*! @brief SDMA sw done configurations.*/
typedef struct _sdma_sw_done_config
{
    bool enableSwDone; /*!< true is enable sw done, false is disable */
    uint8_t swDoneSel; /*!< sw done channel number per peripheral type */
} sdma_sw_done_config_t;

/*! @brief SDMA peripheral to peripheral R7 config*/
typedef struct _sdma_p2p_config
{
    uint8_t sourceWatermark; /*!< lower watermark value */
    uint8_t destWatermark;   /*!< higher water makr value */
    bool continuousTransfer; /*!< 0: the amount of samples to be transferred is equal to the cont field of mode word
                                      1: the amount of samples to be transferred is unknown and script will keep on
                                transferring as long as both events are detected and script must be stopped by
                                application.*/
} sdma_p2p_config_t;

/*!
 * @brief SDMA transfer configuration
 *
 * This structure configures the source/destination transfer attribute.
 */
typedef struct _sdma_transfer_config
{
    uint32_t srcAddr;                      /*!< Source address of the transfer */
    uint32_t destAddr;                     /*!< Destination address of the transfer */
    sdma_transfer_size_t srcTransferSize;  /*!< Source data transfer size. */
    sdma_transfer_size_t destTransferSize; /*!< Destination data transfer size. */
    uint32_t bytesPerRequest;              /*!< Bytes to transfer in a minor loop*/
    uint32_t transferSzie;                 /*!< Bytes to transfer for this descriptor */
    uint32_t scriptAddr;                   /*!< SDMA script address located in SDMA ROM. */
    uint32_t eventSource;  /*!< Event source number for the channel. 0 means no event, use software trigger */
    uint32_t eventSource1; /*!< event source 1 */
    bool isEventIgnore;    /*!< True means software trigger, false means hardware trigger */
    bool
        isSoftTriggerIgnore; /*!< If ignore the HE bit, 1 means use hardware events trigger, 0 means software trigger */
    sdma_transfer_type_t type;          /*!< Transfer type, transfer type used to decide the SDMA script. */
    sdma_multi_fifo_config_t multiFifo; /*!< multi fifo configurations */
    sdma_sw_done_config_t swDone;       /*!< sw done selector */
    uint32_t watermarkLevel;            /*!< watermark level */
    uint32_t eventMask0;                /*!< event mask 0 */
    uint32_t eventMask1;                /*!< event mask 1 */

} sdma_transfer_config_t;

/*!
 * @brief SDMA buffer descriptor structure.
 *
 * This structure is a buffer descriptor, this structure describes the buffer start address and other options
 */
typedef struct _sdma_buffer_descriptor
{
    uint32_t count : 16;       /*!< Bytes of the buffer length for this buffer descriptor. */
    uint32_t status : 8;       /*!< E,R,I,C,W,D status bits stored here */
    uint32_t command : 8;      /*!< command mostlky used for channel 0 */
    uint32_t bufferAddr;       /*!< Buffer start address for this descriptor. */
    uint32_t extendBufferAddr; /*!< External buffer start address, this is an optional for a transfer. */
} sdma_buffer_descriptor_t;

/*!
 * @brief SDMA channel control descriptor structure.
 */
typedef struct _sdma_channel_control
{
    uint32_t currentBDAddr; /*!< Address of current buffer descriptor processed  */
    uint32_t baseBDAddr;    /*!< The start address of the buffer descriptor array */
    uint32_t channelDesc;   /*!< Optional for transfer */
    uint32_t status;        /*!< Channel status */
} sdma_channel_control_t;

/*!
 * @brief SDMA context structure for each channel. This structure can be load into SDMA core, with this structure, SDMA
 * scripts can start work.
 */
typedef struct _sdma_context_data
{
    uint32_t PC : 14;
    uint32_t unused1 : 1;
    uint32_t T : 1;
    uint32_t RPC : 14;
    uint32_t unused0 : 1;
    uint32_t SF : 1;
    uint32_t SPC : 14;
    uint32_t unused2 : 1;
    uint32_t DF : 1;
    uint32_t EPC : 14;
    uint32_t LM : 2;
    uint32_t GeneralReg[8]; /*!< 8 general regsiters used for SDMA RISC core */
    uint32_t MDA;
    uint32_t MSA;
    uint32_t MS;
    uint32_t MD;
    uint32_t PDA;
    uint32_t PSA;
    uint32_t PS;
    uint32_t PD;
    uint32_t CA;
    uint32_t CS;
    uint32_t DDA;
    uint32_t DSA;
    uint32_t DS;
    uint32_t DD;
    uint32_t Scratch0;
    uint32_t Scratch1;
    uint32_t Scratch2;
    uint32_t Scratch3;
    uint32_t Scratch4;
    uint32_t Scratch5;
    uint32_t Scratch6;
    uint32_t Scratch7;
} sdma_context_data_t;

/*! @brief Callback for SDMA */
struct _sdma_handle;

/*! @brief Define callback function for SDMA. */
typedef void (*sdma_callback)(struct _sdma_handle *handle, void *userData, bool transferDone, uint32_t bdIndex);

/*! @brief SDMA transfer handle structure */
typedef struct _sdma_handle
{
    sdma_callback callback;           /*!< Callback function for major count exhausted. */
    void *userData;                   /*!< Callback function parameter. */
    SDMAARM_Type *base;               /*!< SDMA peripheral base address. */
    sdma_buffer_descriptor_t *BDPool; /*!< Pointer to memory stored BD arrays. */
    uint32_t bdCount;                 /*!< How many buffer descriptor   */
    uint32_t bdIndex;                 /*!< How many buffer descriptor   */
    uint32_t eventSource;             /*!< Event source count for the channel */
    uint32_t eventSource1;            /*!< Event source 1 count for the channel */
    sdma_context_data_t *context;     /*!< Channel context to exectute in SDMA */
    uint8_t channel;                  /*!< SDMA channel number. */
    uint8_t priority;                 /*!< SDMA channel priority */
    uint8_t flags;                    /*!< The status of the current channel. */
} sdma_handle_t;

/*******************************************************************************
 * APIs
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @name SDMA initialization and de-initialization
 * @{
 */

/*!
 * @brief Initializes the SDMA peripheral.
 *
 * This function ungates the SDMA clock and configures the SDMA peripheral according
 * to the configuration structure.
 *
 * @param base SDMA peripheral base address.
 * @param config A pointer to the configuration structure, see "sdma_config_t".
 * @note This function enables the minor loop map feature.
 */
void SDMA_Init(SDMAARM_Type *base, const sdma_config_t *config);

/*!
 * @brief Deinitializes the SDMA peripheral.
 *
 * This function gates the SDMA clock.
 *
 * @param base SDMA peripheral base address.
 */
void SDMA_Deinit(SDMAARM_Type *base);

/*!
 * @brief Gets the SDMA default configuration structure.
 *
 * This function sets the configuration structure to default values.
 * The default configuration is set to the following values.
 * @code
 *   config.enableRealTimeDebugPin = false;
 *   config.isSoftwareResetClearLock = true;
 *   config.ratio = kSDMA_HalfARMClockFreq;
 * @endcode
 *
 * @param config A pointer to the SDMA configuration structure.
 */
void SDMA_GetDefaultConfig(sdma_config_t *config);

/*!
 * @brief Sets all SDMA core register to reset status.
 *
 * If only reset ARM core, SDMA register cannot return to reset value, shall call this function to reset all SDMA
 * register to reset value. But the internal status cannot be reset.
 *
 * @param base SDMA peripheral base address.
 */
void SDMA_ResetModule(SDMAARM_Type *base);

/*! @} */
/*!
 * @name SDMA Channel Operation
 * @{
 */
/*!
 * @brief Enables the interrupt source for the SDMA error.
 *
 * Enable this will trigger an interrupt while SDMA occurs error while executing scripts.
 *
 * @param base SDMA peripheral base address.
 * @param channel SDMA channel number.
 */
static inline void SDMA_EnableChannelErrorInterrupts(SDMAARM_Type *base, uint32_t channel)
{
    base->INTRMASK |= (1UL << channel);
}

/*!
 * @brief Disables the interrupt source for the SDMA error.
 *
 * @param base SDMA peripheral base address.
 * @param channel SDMA channel number.
 */
static inline void SDMA_DisableChannelErrorInterrupts(SDMAARM_Type *base, uint32_t channel)
{
    base->INTRMASK &= ~(1UL << channel);
}

/*! @} */
/*!
 * @name SDMA Buffer Descriptor Operation
 * @{
 */

/*!
 * @brief Sets buffer descriptor contents.
 *
 * This function sets the descriptor contents such as source, dest address and status bits.
 *
 * @param bd Pointer to the buffer descriptor structure.
 * @param srcAddr Source address for the buffer descriptor.
 * @param destAddr Destination address for the buffer descriptor.
 * @param busWidth The transfer width, it only can be a member of sdma_transfer_size_t.
 * @param bufferSize Buffer size for this descriptor, this number shall less than 0xFFFF. If need to transfer a big
 * size,
 * shall divide into several buffer descriptors.
 * @param isLast Is the buffer descriptor the last one for the channel to transfer. If only one descriptor used for
 * the channel, this bit shall set to TRUE.
 * @param enableInterrupt If trigger an interrupt while this buffer descriptor transfer finished.
 * @param isWrap Is the buffer descriptor need to be wrapped. While this bit set to true, it will automatically wrap
 * to the first buffer descrtiptor to do transfer.
 * @param type Transfer type, memory to memory, peripheral to memory or memory to peripheral.
 */
void SDMA_ConfigBufferDescriptor(sdma_buffer_descriptor_t *bd,
                                 uint32_t srcAddr,
                                 uint32_t destAddr,
                                 sdma_transfer_size_t busWidth,
                                 size_t bufferSize,
                                 bool isLast,
                                 bool enableInterrupt,
                                 bool isWrap,
                                 sdma_transfer_type_t type);

/*! @} */
/*!
 * @name SDMA Channel Transfer Operation
 * @{
 */

/*!
 * @brief Set SDMA channel priority.
 *
 * This function sets the channel priority. The default value is 0 for all channels, priority 0 will prevents
 * channel from starting, so the priority must be set before start a channel.
 *
 * @param base SDMA peripheral base address.
 * @param channel SDMA channel number.
 * @param priority SDMA channel priority.
 */
static inline void SDMA_SetChannelPriority(SDMAARM_Type *base, uint32_t channel, uint8_t priority)
{
    base->SDMA_CHNPRI[channel] = priority;
}

/*!
 * @brief Set SDMA request source mapping channel.
 *
 * This function sets which channel will be triggered by the dma request source.
 *
 * @param base SDMA peripheral base address.
 * @param source SDMA dma request source number.
 * @param channelMask SDMA channel mask. 1 means channel 0, 2 means channel 1, 4 means channel 3. SDMA supports
 * an event trigger multi-channel. A channel can also be triggered by several source events.
 */
static inline void SDMA_SetSourceChannel(SDMAARM_Type *base, uint32_t source, uint32_t channelMask)
{
    base->CHNENBL[source] = channelMask;
}

/*!
 * @brief Start a SDMA channel by software trigger.
 *
 * This function start a channel.
 *
 * @param base SDMA peripheral base address.
 * @param channel SDMA channel number.
 */
static inline void SDMA_StartChannelSoftware(SDMAARM_Type *base, uint32_t channel)
{
    base->HSTART = (1UL << channel);
}

/*!
 * @brief Start a SDMA channel by hardware events.
 *
 * This function start a channel.
 *
 * @param base SDMA peripheral base address.
 * @param channel SDMA channel number.
 */
static inline void SDMA_StartChannelEvents(SDMAARM_Type *base, uint32_t channel)
{
    base->EVTPEND = (1UL << channel);
}

/*!
 * @brief Stop a SDMA channel.
 *
 * This function stops a channel.
 *
 * @param base SDMA peripheral base address.
 * @param channel SDMA channel number.
 */
static inline void SDMA_StopChannel(SDMAARM_Type *base, uint32_t channel)
{
    base->STOP_STAT = (1UL << channel);
}

/*!
 * @brief Set the SDMA context switch mode.
 *
 * @param base SDMA peripheral base address.
 * @param mode SDMA context switch mode.
 */
void SDMA_SetContextSwitchMode(SDMAARM_Type *base, sdma_context_switch_mode_t mode);

/*! @} */

/*!
 * @name SDMA Channel Status Operation
 * @{
 */

/*!
 * @brief Gets the SDMA interrupt status of all channels.
 *
 * @param base SDMA peripheral base address.
 * @return The interrupt status for all channels. Check the relevant bits for specific channel.
 */
static inline uint32_t SDMA_GetChannelInterruptStatus(SDMAARM_Type *base)
{
    return base->INTR;
}

/*!
 * @brief Clear the SDMA channel interrupt status of specific channels.
 *
 * @param base SDMA peripheral base address.
 * @param mask The interrupt status need to be cleared.
 */
static inline void SDMA_ClearChannelInterruptStatus(SDMAARM_Type *base, uint32_t mask)
{
    base->INTR = mask;
}

/*!
 * @brief Gets the SDMA stop status of all channels.
 *
 * @param base SDMA peripheral base address.
 * @return The stop status for all channels. Check the relevant bits for specific channel.
 */
static inline uint32_t SDMA_GetChannelStopStatus(SDMAARM_Type *base)
{
    return base->STOP_STAT;
}

/*!
 * @brief Clear the SDMA channel stop status of specific channels.
 *
 * @param base SDMA peripheral base address.
 * @param mask The stop status need to be cleared.
 */
static inline void SDMA_ClearChannelStopStatus(SDMAARM_Type *base, uint32_t mask)
{
    base->STOP_STAT = mask;
}

/*!
 * @brief Gets the SDMA channel pending status of all channels.
 *
 * @param base SDMA peripheral base address.
 * @return The pending status for all channels. Check the relevant bits for specific channel.
 */
static inline uint32_t SDMA_GetChannelPendStatus(SDMAARM_Type *base)
{
    return base->EVTPEND;
}

/*!
 * @brief Clear the SDMA channel pending status of specific channels.
 *
 * @param base SDMA peripheral base address.
 * @param mask The pending status need to be cleared.
 */
static inline void SDMA_ClearChannelPendStatus(SDMAARM_Type *base, uint32_t mask)
{
    base->EVTPEND = mask;
}

/*!
 * @brief Gets the SDMA channel error status.
 *
 * SDMA channel error flag is asserted while an incoming DMA request was detected and it triggers a channel
 * that is already pending or being serviced. This probably means there is an overflow of data for that channel.
 *
 * @param base SDMA peripheral base address.
 * @return The error status for all channels. Check the relevant bits for specific channel.
 */
static inline uint32_t SDMA_GetErrorStatus(SDMAARM_Type *base)
{
    return base->EVTERR;
}

/*!
 * @brief Gets the SDMA request source pending status.
 *
 * @param base SDMA peripheral base address.
 * @param source DMA request source number.
 * @return True means the request source is pending, otherwise not pending.
 */
bool SDMA_GetRequestSourceStatus(SDMAARM_Type *base, uint32_t source);

/*! @} */
/*!
 * @name SDMA Transactional Operation
 */

/*!
 * @brief Creates the SDMA handle.
 *
 * This function is called if using the transactional API for SDMA. This function
 * initializes the internal state of the SDMA handle.
 *
 * @param handle SDMA handle pointer. The SDMA handle stores callback function and parameters.
 * @param base SDMA peripheral base address.
 * @param channel SDMA channel number.
 * @param context Context structure for the channel to download into SDMA. Users shall make sure the context located
 * in a non-cacheable memory, or it will cause SDMA run fail. Users shall not touch the context contents, it only be
 * filled by SDMA driver in SDMA_SubmitTransfer function.
 */
void SDMA_CreateHandle(sdma_handle_t *handle, SDMAARM_Type *base, uint32_t channel, sdma_context_data_t *context);

/*!
 * @brief Installs the BDs memory pool into the SDMA handle.
 *
 * This function is called after the SDMA_CreateHandle to use multi-buffer feature.
 *
 * @param handle SDMA handle pointer.
 * @param BDPool A memory pool to store BDs. It must be located in non-cacheable address.
 * @param BDCount The number of BD slots.
 */
void SDMA_InstallBDMemory(sdma_handle_t *handle, sdma_buffer_descriptor_t *BDPool, uint32_t BDCount);

/*!
 * @brief Installs a callback function for the SDMA transfer.
 *
 * This callback is called in the SDMA IRQ handler. Use the callback to do something after
 * the current major loop transfer completes.
 *
 * @param handle SDMA handle pointer.
 * @param callback SDMA callback function pointer.
 * @param userData A parameter for the callback function.
 */
void SDMA_SetCallback(sdma_handle_t *handle, sdma_callback callback, void *userData);

/*!
 * @brief multi fifo configurations.
 *
 * This api is used to support multi fifo for SDMA, if user want to get multi fifo data, then this api
 * shoule be called before submit transfer.
 *
 * @param config transfer configurations.
 * @param fifoNums fifo numbers that multi fifo operation perform, support up to 15 fifo numbers.
 * @param fifoOffset fifoOffset = fifo address offset / sizeof(uint32_t) - 1.
 */
void SDMA_SetMultiFifoConfig(sdma_transfer_config_t *config, uint32_t fifoNums, uint32_t fifoOffset);

/*!
 * @brief enable sdma sw done feature.
 *
 * @deprecated Do not use this function. It has been superceded by @ref SDMA_SetDoneConfig.
 *
 * @param base SDMA base.
 * @param config transfer configurations.
 * @param sel sw done selector.
 * @param type peripheral type is used to determine the corresponding peripheral sw done selector bit.
 */
void SDMA_EnableSwDone(SDMAARM_Type *base, sdma_transfer_config_t *config, uint8_t sel, sdma_peripheral_t type);

/*!
 * @brief sdma channel done configurations.
 *
 * @param base SDMA base.
 * @param config transfer configurations.
 * @param type peripheral type.
 * @param doneSrc reference sdma_done_src_t.
 */
void SDMA_SetDoneConfig(SDMAARM_Type *base,
                        sdma_transfer_config_t *config,
                        sdma_peripheral_t type,
                        sdma_done_src_t doneSrc);

/*!
 * @brief load script to sdma program memory.
 *
 * @param base SDMA base.
 * @param destAddr dest script address, should be SDMA program memory address.
 * @param srcAddr source address of target script.
 * @param bufferSizeBytes bytes size of script.
 */
void SDMA_LoadScript(SDMAARM_Type *base, uint32_t destAddr, void *srcAddr, size_t bufferSizeBytes);

/*!
 * @brief dump script from sdma program memory.
 *
 * @param base SDMA base.
 * @param srcAddr should be SDMA program memory address.
 * @param destAddr address to store scripts.
 * @param bufferSizeBytes bytes size of script.
 */
void SDMA_DumpScript(SDMAARM_Type *base, uint32_t srcAddr, void *destAddr, size_t bufferSizeBytes);

/*!
 * @brief Get RAM script version.
 *
 * @param base SDMA base.
 * @return The script version of RAM.
 */
static inline const char * SDMA_GetRamScriptVersion(SDMAARM_Type *base)
{
    return FSL_SDMA_SCRIPT_VERSION;
}

/*!
 * @brief Prepares the SDMA transfer structure.
 *
 * This function prepares the transfer configuration structure according to the user input.
 *
 * @param config The user configuration structure of type sdma_transfer_t.
 * @param srcAddr SDMA transfer source address.
 * @param destAddr SDMA transfer destination address.
 * @param srcWidth SDMA transfer source address width(bytes).
 * @param destWidth SDMA transfer destination address width(bytes).
 * @param bytesEachRequest SDMA transfer bytes per channel request.
 * @param transferSize SDMA transfer bytes to be transferred.
 * @param eventSource Event source number for the transfer, if use software trigger, just write 0.
 * @param peripheral Peripheral type, used to decide if need to use some special scripts.
 * @param type SDMA transfer type. Used to decide the correct SDMA script address in SDMA ROM.
 * @note The data address and the data width must be consistent. For example, if the SRC
 *       is 4 bytes, the source address must be 4 bytes aligned, or it results in
 *       source address error.
 */
void SDMA_PrepareTransfer(sdma_transfer_config_t *config,
                          uint32_t srcAddr,
                          uint32_t destAddr,
                          uint32_t srcWidth,
                          uint32_t destWidth,
                          uint32_t bytesEachRequest,
                          uint32_t transferSize,
                          uint32_t eventSource,
                          sdma_peripheral_t peripheral,
                          sdma_transfer_type_t type);

/*!
 * @brief Prepares the SDMA P2P transfer structure.
 *
 * This function prepares the transfer configuration structure according to the user input.
 *
 * @param config The user configuration structure of type sdma_transfer_t.
 * @param srcAddr SDMA transfer source address.
 * @param destAddr SDMA transfer destination address.
 * @param srcWidth SDMA transfer source address width(bytes).
 * @param destWidth SDMA transfer destination address width(bytes).
 * @param bytesEachRequest SDMA transfer bytes per channel request.
 * @param transferSize SDMA transfer bytes to be transferred.
 * @param eventSource Event source number for the transfer.
 * @param eventSource1 Event source1 number for the transfer.
 * @param peripheral Peripheral type, used to decide if need to use some special scripts.
 * @param p2p sdma p2p configuration pointer.
 * @note The data address and the data width must be consistent. For example, if the SRC
 *       is 4 bytes, the source address must be 4 bytes aligned, or it results in
 *       source address error.
 */
void SDMA_PrepareP2PTransfer(sdma_transfer_config_t *config,
                             uint32_t srcAddr,
                             uint32_t destAddr,
                             uint32_t srcWidth,
                             uint32_t destWidth,
                             uint32_t bytesEachRequest,
                             uint32_t transferSize,
                             uint32_t eventSource,
                             uint32_t eventSource1,
                             sdma_peripheral_t peripheral,
                             sdma_p2p_config_t *p2p);

/*!
 * @brief Submits the SDMA transfer request.
 *
 * This function submits the SDMA transfer request according to the transfer configuration structure.
 *
 * @param handle SDMA handle pointer.
 * @param config Pointer to SDMA transfer configuration structure.
 */
void SDMA_SubmitTransfer(sdma_handle_t *handle, const sdma_transfer_config_t *config);

/*!
 * @brief SDMA starts transfer.
 *
 * This function enables the channel request. Users can call this function after submitting the transfer request
 * or before submitting the transfer request.
 *
 * @param handle SDMA handle pointer.
 */
void SDMA_StartTransfer(sdma_handle_t *handle);

/*!
 * @brief SDMA stops transfer.
 *
 * This function disables the channel request to pause the transfer. Users can call SDMA_StartTransfer()
 * again to resume the transfer.
 *
 * @param handle SDMA handle pointer.
 */
void SDMA_StopTransfer(sdma_handle_t *handle);

/*!
 * @brief SDMA aborts transfer.
 *
 * This function disables the channel request and clear transfer status bits.
 * Users can submit another transfer after calling this API.
 *
 * @param handle DMA handle pointer.
 */
void SDMA_AbortTransfer(sdma_handle_t *handle);

/*!
 * @brief Get transferred bytes while not using BD pools.
 *
 * This function returns the buffer descriptor count value if not using buffer descriptor.
 * While do a simple transfer, which only uses one descriptor, the SDMA driver inside handle the
 * buffer descriptor. In uart receive case, it can tell users how many data already received, also
 * it can tells users how many data transfferd while error occurred.
 * Notice, the count would not change while transfer is on-going using default SDMA script.
 *
 * @param handle DMA handle pointer.
 * @return Transferred bytes.
 */
uint32_t SDMA_GetTransferredBytes(sdma_handle_t *handle);

#if defined FSL_FEATURE_SOC_SPBA_COUNT && (FSL_FEATURE_SOC_SPBA_COUNT > 0)
/*!
 * @brief Judge if address located in SPBA.
 *
 * @param addr Address which need to judge.
 * @retval True means located in SPBA, false means not.
 */
bool SDMA_IsPeripheralInSPBA(uint32_t addr);
#endif /* FSL_FEATURE_SOC_SPBA_COUNT */

/*!
 * @brief SDMA IRQ handler for complete a buffer descriptor transfer.
 *
 * This function clears the interrupt flags and also handle the CCB for the channel.
 *
 * @param handle SDMA handle pointer.
 */
void SDMA_HandleIRQ(sdma_handle_t *handle);

/*! @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /*FSL_SDMA_H_*/
