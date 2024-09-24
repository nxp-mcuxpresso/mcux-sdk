/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_JPEGDEC_H_
#define _FSL_JPEGDEC_H_

#include "fsl_common.h"

/*!
 * @addtogroup jpegdec
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define JPEG_ALIGN_SIZE(size, align) (((size) + (align)-1U) & ~((align)-1U))

/*! @name Driver version */
/*@{*/
/*! @brief JPEG decoder driver version 2.0.0. */
#define FSL_JPEGDEC_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

/*! @brief JPEG decoder structure definition. */
typedef struct
{
    JPEGDEC_Type *core;        /*!< Pointer to decoder core. */
    JPGDECWRP_Type *wrapper;   /*!< Pointer to decoder wrapper. */
} JPEG_DECODER_Type;

/*! @brief Error codes for the JPEG decoder driver. */
enum
{
    kStatus_JPEGDEC_NotSupported =
        MAKE_STATUS(kStatusGroup_JPEGDEC, 0), /*!< Unsupported pixel format or image resolution. */
};

/*!
 * @brief JPEG decoding pixel format.
 */
typedef enum _jpegdec_pixel_format
{
    kJPEGDEC_PixelFormatYUV420   = 0U, /*!< YUV420 format, Y at first plane, UV at second plane. */
    kJPEGDEC_PixelFormatYUV422   = 1U, /*!< YUV422, 1 planar in the YUYV sequence. */
    kJPEGDEC_PixelFormatRGB      = 2U, /*!< RGB packed format. */
    kJPEGDEC_PixelFormatYUV444   = 3U, /*!< YUV444, 1 planar in the YUVYUV sequence. */
    kJPEGDEC_PixelFormatGray     = 4U, /*!< 8-bit or 12-bit gray scale. */
    kJPEGDEC_PixelFormatReserved = 5U, /*!< Reserved. */
    kJPEGDEC_PixelFormatYCCK     = 6U, /*!< YCCK format. */
} jpegdec_pixel_format_t;

/*!
 * @brief JPEG decoding pixel depth.
 */
typedef enum _jpegdec_pixel_depth
{
    kJPEGDEC_PixelDepth8Bit  = 0U, /*!< 8-bit per pixel. */
    kJPEGDEC_PixelDepth12Bit = 1U, /*!< 12-bit per pixel. */
} jpegdec_pixel_depth_t;

/*! @brief JPEG decoder configuration. */
typedef struct _jpegdec_decoder_config
{
    uint32_t outBufAddr0;        /*!< Base address for output frame buffer0. 16-byte aligned(4 LSBs are zero). */
    uint32_t outBufAddr1;        /*!< Base address for output frame buffer1, only used for YUV420 second plane. 16-byte
                                    aligned(4 LSBs are zero). */
    uint32_t outBufPitch : 16;   /*!< Output buffer pitch. */
    uint32_t : 16;               /*!< Reserved. */
    uint32_t jpegBufAddr;        /*!< Base address of the JPEG stream buffer for decoding. 16-byte aligned(4 LSBs are
                                    zero). */
    uint32_t jpegBufSize;        /*!< Size of the JPEG stream buffer. 1k-byte aligned(10 LSBs are zero). */
    uint32_t height : 14;        /*!< Image height in pixel. Max supported is 8K(2000h), must be integer times of 8. */
    uint32_t : 2;                /*!< Reserved. */
    uint32_t width : 14;         /*!< Image width in pixel. Max supported is 8K(2000h), must be integer times of 8. */
    uint32_t : 2;                /*!< Reserved. */
    uint32_t : 2;                /*!< Reserved. */
    uint32_t pixelDepth : 1;     /*!< Pixel depth, @ref jpegdec_pixel_depth_t. */
    uint32_t pixelFormat : 4;    /*!< The image pixel format, @ref jpegdec_pixel_format_t. */
    uint32_t clearStreamBuf : 1; /*!< Set to true to clear the saved bit stream buffer. */
    uint32_t autoStart : 1; /*!< Set to true to automatically start the decoding when this descriptor is switched on. */
    uint32_t : 23;          /*!< Reserved. */
} jpegdec_decoder_config_t;

/*!
 * @brief JPEG decoder descriptor.
 *
 * This structure is used to configure the linked decoding descriptor for one or more slots in Single Bit Stream Repeat
 * mode or Context Switch mode.
 */
typedef struct _jpegdec_descpt
{
    uint32_t nextDescptAddr;         /*!< Address of the next decoding descriptor. */
    jpegdec_decoder_config_t config; /*!< The decoding configuration for this descriptor. */
} jpegdec_descpt_t;

/*! @brief Decoder slot Interrupt status and enable/disable flags. */
enum _jpegdec_flags
{
    kJPEGDEC_StreamBufferHalfDoneFlag = (1U << 0U),  /*!< Slot's bit stream buffer pointer has passed half the size. */
    kJPEGDEC_StreamBufferDoneFlag     = (1U << 1U),  /*!< Slot's bit stream buffer pointer has finished. */
    kJPEGDEC_SwitchInFlag             = (1U << 2U),  /*!< Current slot is switched in. */
    kJPEGDEC_DecodeCompleteFlag       = (1U << 3U),  /*!< Current slot finished decoding. */
    kJPEGDEC_DecodeErrorFlag          = (1U << 8U),  /*!< Current slot has error during decoding. */
    kJPEGDEC_DescptReadErrorFlag      = (1U << 9U),  /*!< Descriptor read error when switching in current slot. */
    kJPEGDEC_BitReadErrorFlag         = (1U << 10U), /*!< Read JPEG stream error. */
    kJPEGDEC_PixelWriteErrorFlag      = (1U << 11U), /*!< Write decoded pixel error. */

    kJPEGDEC_ErrorFlags = kJPEGDEC_DecodeErrorFlag | kJPEGDEC_DescptReadErrorFlag | kJPEGDEC_BitReadErrorFlag |
                          kJPEGDEC_PixelWriteErrorFlag,

    kJPEGDEC_AllFlags = kJPEGDEC_StreamBufferHalfDoneFlag | kJPEGDEC_StreamBufferDoneFlag | kJPEGDEC_SwitchInFlag |
                        kJPEGDEC_DecodeCompleteFlag | kJPEGDEC_ErrorFlags,
};

/*! @brief JPEG decoding Slot. */
enum _jpegdec_slots
{
    kJPEGDEC_Slot0 = (1U << 0U), /*!< Decoding slot 0. */
    kJPEGDEC_Slot1 = (1U << 1U), /*!< Decoding slot 1. */
    kJPEGDEC_Slot2 = (1U << 2U), /*!< Decoding slot 2. */
    kJPEGDEC_Slot3 = (1U << 3U), /*!< Decoding slot 3. */
};

/*!
 * @brief JPEG stream data format.
 */
typedef enum _jpegdec_endian_mode
{
    kJPEGDEC_BigEndian    = 0U, /*!< JPEG data format is big endian. */
    kJPEGDEC_LittleEndian = 1U, /*!< JPEG data format is little endian. */
} jpegdec_endian_mode_t;

/*! @brief Configuration for JPEG decoder. */
typedef struct _jpegdec_config
{
    bool enable;                      /*!< Enables the decode IP. */
    bool enableLp;                    /*!< Enables the core to enter low power mode. */
    jpegdec_endian_mode_t endianMode; /*!< Endian mode for the souce/decoded image.*/
    uint8_t slots;                    /*!< Mask of enabled slots @ref _jpegdec_slots. */
} jpegdec_config_t;

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @name Initialization and deinitialization
 * @{
 */
/*!
 * @brief Gets the default configuration for JPEG decoder.
 *
 * This function initializes the user configuration structure to default value. The default value are:
 *
 * Example:
   @code
   config->endianMode = kJPEGDEC_LittleEndian;
   config->slots      = 0xFU;
   config->enable     = true;
   config->enableLp   = false;
   @endcode
 *
 * @param config Pointer to JPEG decoder configuration structure.
 */
void JPEGDEC_GetDefaultConfig(jpegdec_config_t *config);

/*!
 * @brief Initializes the JPEG decoder.
 *
 * The default configuration can be got by calling @ref JPEGDEC_GetDefaultConfig.
 *
 * @param base JPEG decoder peripheral base address.
 * @param config Pointer to JPEG decoder configuration structure.
 */
void JPEGDEC_Init(JPEG_DECODER_Type *base, const jpegdec_config_t *config);

/*!
 * @brief Deinitializes the JPEG decoder.
 *
 * @param base JPEG decoder peripheral base address.
 */
void JPEGDEC_Deinit(JPEG_DECODER_Type *base);
/* @} */

/*!
 * @name Interrupts
 * @{
 */
/*!
 * @brief Enables interrupts for certain slot.
 *
 * @param base JPEG decoder peripheral base address.
 * @param slot Slot number.
 * @param mask Interrupts mask formed by flags OR'ed together. @ref _jpegdec_flags.
 */
static inline void JPEGDEC_EnableInterrupts(JPEG_DECODER_Type *base, uint8_t slot, uint32_t mask)
{
    base->wrapper->SLOT_REGS[slot].SLOT_IRQ_EN |= mask;
}

/*!
 * @brief Disables interrupts for certain slot.
 *
 * @param base JPEG decoder peripheral base address.
 * @param slot Slot number.
 * @param mask Interrupts mask formed by flags OR'ed together. @ref _jpegdec_flags.
 */
static inline void JPEGDEC_DisableInterrupts(JPEG_DECODER_Type *base, uint8_t slot, uint32_t mask)
{
    base->wrapper->SLOT_REGS[slot].SLOT_IRQ_EN &= ~mask;
}
/* @} */

/*!
 * @name Status
 * @{
 */
/*!
 * @brief Gets status flags for certain slot.
 *
 * @param base JPEG decoder peripheral base address.
 * @param slot Slot number.
 * @return Status flags asserted mask formed by flags OR'ed together. See "_jpegdec_flags".
 */
static inline uint32_t JPEGDEC_GetStatusFlags(JPEG_DECODER_Type *base, uint8_t slot)
{
    return base->wrapper->SLOT_REGS[slot].SLOT_STATUS;
}

/*!
 * @brief Clears status flags for certain slot.
 *
 * @param base JPEG decoder peripheral base address.
 * @param slot Slot number.
 * @param mask Status flags mask formed by flags OR'ed together. See "_jpegdec_flags".
 */
static inline void JPEGDEC_ClearStatusFlags(JPEG_DECODER_Type *base, uint8_t slot, uint32_t mask)
{
    base->wrapper->SLOT_REGS[slot].SLOT_STATUS = mask;
}
/* @} */

/*!
 * @name Basic Operations
 * @{
 */
/*!
 * @brief Enables the JPEG decoder module
 *
 * @param base JPEG decoder peripheral base address.
 * @param enable True to enable, false to disable.
 */
static inline void JPEGDEC_Enable(JPEG_DECODER_Type *base, bool enable)
{
    if (enable)
    {
        base->wrapper->GLB_CTRL |= JPGDECWRP_GLB_CTRL_JPG_DEC_EN_MASK;
        base->core->CTRL |= JPEGDEC_CTRL_GO_MASK;
    }
    else
    {
        base->wrapper->GLB_CTRL &= ~JPGDECWRP_GLB_CTRL_JPG_DEC_EN_MASK;
        base->core->CTRL &= ~JPEGDEC_CTRL_GO_MASK;
    }
}

/*!
 * @brief Enables the JPEG decoder core to enter low power mode
 *
 * @param base JPEG decoder peripheral base address.
 * @param enable True to enable, false to disable.
 */
static inline void JPEGDEC_EnableLp(JPEG_DECODER_Type *base, bool enable)
{
    if (enable)
    {
        base->core->CTRL |= JPEGDEC_CTRL_LP_MASK;
    }
    else
    {
        base->core->CTRL &= ~JPEGDEC_CTRL_LP_MASK;
    }
}

/*!
 * @brief Resets the JPEG decoder.
 *
 * @param base JPEG decoder peripheral base address.
 */
static inline void JPEGDEC_Reset(JPEG_DECODER_Type *base)
{
    base->wrapper->GLB_CTRL |= JPGDECWRP_GLB_CTRL_SFTRST_MASK;
    base->core->CTRL |= JPEGDEC_CTRL_SWR_MASK;
    base->core->CTRL &= ~JPEGDEC_CTRL_SWR_MASK;
}

/*!
 * @brief Starts the JPEG decode
 *
 * After calling this API the JPEG decoder will start decoding on a frame basis. The decoding process stops
 * after the frame decoding is complete and if there are no other valid descriptors available. Auto-clear.
 *
 * @param base JPEG decoder peripheral base address.
 */
static inline void JPEGDEC_StartDecode(JPEG_DECODER_Type *base)
{
    base->wrapper->GLB_CTRL |= JPGDECWRP_GLB_CTRL_DEC_GO_MASK;
}

/*!
 * @brief Enables the JPEG decoding slot(s)
 *
 * @param base JPEG decoder peripheral base address.
 * @param slot Masks of the enabled slot, @ref _jpegdec_slots.
 */
static inline void JPEGDEC_EnableSlots(JPEG_DECODER_Type *base, uint8_t slots)
{
    base->wrapper->GLB_CTRL |= (base->wrapper->GLB_CTRL & ~JPGDECWRP_GLB_CTRL_SLOT_EN_MASK) | JPGDECWRP_GLB_CTRL_SLOT_EN((uint32_t)slots);
}

/*!
 * @brief Gets the current active slot
 *
 * @param base JPEG decoder peripheral base address.
 * @param[out] slot Pointer to the variable that stores the enabled slot.
 * @retval #kStatus_Success Successfully get the current active slot.
 * @retval #kStatus_Fail Current JPEG decoder is idle, no slot is active.
 */
status_t JPEGDEC_GetActiveSlot(JPEG_DECODER_Type *base, uint8_t *slot);

/*!
 * @brief Sets the JPEG decoder endian mode for decoded data.
 *
 * @param base JPEG decoder peripheral base address.
 * @param mode Endian mode.
 */
static inline void JPEGDEC_SetEndian(JPEG_DECODER_Type *base, jpegdec_endian_mode_t mode)
{
    if (mode == kJPEGDEC_LittleEndian)
    {
        base->wrapper->GLB_CTRL |= JPGDECWRP_GLB_CTRL_L_ENDIAN_MASK;
    }
    else
    {
        base->wrapper->GLB_CTRL &= ~JPGDECWRP_GLB_CTRL_L_ENDIAN_MASK;
    }
}
/* @} */

/*!
 * @name Image decode
 * @{
 */
/*!
 * @brief Sets the address and length of the JPEG image.
 *
 * @param[out] config Decoder configuration.
 * @param data Start address of the buffer of the raw JPEG image, shall be 8-byte aligned.
 * @param length Size of the buffer.
 */
void JPEGDEC_SetJpegBuffer(jpegdec_decoder_config_t *config, uint8_t *buffer, size_t length);

/*!
 * @brief Sets the address of the decoded data.
 *
 * @param[out] config Decoder configuration.
 * @param imageData0 Address of the output buffer0, shall be 16-byte aligned.
 * @param imageData1 Address of the output buffer1, only used when output format is YUV420, shall be 16-byte aligned.
 */
void JPEGDEC_SetOutputBuffer(jpegdec_decoder_config_t *config, uint8_t *imageData0, uint8_t *imageData1);

/*!
 * @brief Parses the JPEG header and stores the info in the decoder configuration structure.
 *
 * @param[out] config Decoder configuration.
 * @retval kStatus_Success Header parsing success.
 * @retval kStatus_Fail JPEG header parsing failed due corrupted header.
 * @retval kStatus_JPEGDEC_NotSupported Header parsing failed due to the image pixel format is not supported
   or image width/height is larger than 8k or image width/height is not 8-byte aligned.
 */
status_t JPEGDEC_ParseHeader(jpegdec_decoder_config_t *config);

/*!
 * @brief Sets the decode option.
 *
 * @param[out] config Decoder configuration.
 * @param pitch Output buffer pitch.
 * @param clearStreamBuf Set to true to clear the saved bit stream buffer, not used in single frame mode.
 * @param autoStart Set to true to automatically start the decoding when this descriptor is switched on, not used in
 single frame mode.
 */
void JPEGDEC_SetDecodeOption(jpegdec_decoder_config_t *config, uint16_t pitch, bool clearStreamBuf, bool autoStart);

/*!
 * @brief Sets JPEG decoder decoder configuration.
 *
 * Call this API to set the decoder configuration and then call @ref JPEGDEC_StartDecode
 * to start decode. Need to enable at least one slot in @ref jpegdec_config_t first.
 *
 * @param base JPEG decoder peripheral base address.
 * @param config Decoder configuration.
 */
void JPEGDEC_ConfigDecoder(JPEG_DECODER_Type *base, const jpegdec_decoder_config_t *config);

/*!
 * @brief Sets the address of the next decoder descriptor for certain slot.
 *
 * Call this API to set the decoder descriptor for certain slot, and then call
 * @ref JPEGDEC_EnableSlotNextDescpt to enable the descriptor. If the decode configuration
 * of this descriptor has enabled autoStart then decode will start automatically.
 * Otherwise user has to call @ref JPEGDEC_StartDecode manually. Need to enable the
 * slot in @ref jpegdec_config_t first.
 *
 * @param base JPEG decoder peripheral base address.
 * @param slot Slot number.
 * @param descriptor Pointer to the descriptor structure.
 */
void JPEGDEC_SetSlotNextDescpt(JPEG_DECODER_Type *base, uint8_t slot, jpegdec_descpt_t *descriptor);

/*!
 * @brief Enables the next decoder descriptor for certain slot.
 *
 * Call this API after calling JPEGDEC_SetSlotNextDescpt to set valid descriptor for certain slot.
 * User can also call @ref JPEGDEC_EnableLinkedDescpt before calling @ref JPEGDEC_SetSlotNextDescpt,
 * then the descriptor will be loaded automatically.
 *
 * @param base JPEG decoder peripheral base address.
 * @param slot Slot number.
 */
static inline void JPEGDEC_EnableSlotNextDescpt(JPEG_DECODER_Type *base, uint8_t slot)
{
    base->wrapper->SLOT_REGS[slot].SLOT_NXT_DESCPT_PTR |= JPGDECWRP_SLOT_NXT_DESCPT_PTR_NXT_DESCPT_EN_MASK;
}

/*!
 * @brief Enables the next linked descriptor.
 *
 * Call this API before calling @ref JPEGDEC_SetSlotNextDescpt, then the descriptor will be loaded
 * automatically. Otherwise call @ref JPEGDEC_EnableSlotNextDescpt after calling @ref JPEGDEC_SetSlotNextDescpt.
 *
 * @param[out] descriptor Pointer to the descriptor structure.
 */
static inline void JPEGDEC_EnableLinkedDescpt(jpegdec_descpt_t *descriptor)
{
    /* The 1LSB for nextDescptAddr is used to specify the */
    descriptor->nextDescptAddr |= 0x1U;
}

/*!
 * @brief Sets all fields to default values for the descriptor structure.
 *
 * @param descriptor Pointer to the descriptor structure.
 * @note This function enables the auto start feature.
 */
void JPEGDEC_DescptReset(jpegdec_descpt_t *descriptor);
/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_JPEGDEC_H_ */
