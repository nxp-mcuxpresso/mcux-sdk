/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_PNGDEC_H_
#define _FSL_PNGDEC_H_

#include "fsl_common.h"

/*!
 * @addtogroup pngdec
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief PNGDEC driver version 2.0.0. */
#define FSL_PNGDEC_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

/*! @brief Error codes for the PNGDEC driver. */
enum
{
    kStatus_PNGDEC_NotSupported  = MAKE_STATUS(kStatusGroup_PNGDEC, 0), /*!< Interlace data chunk is not supported. */
    kStatus_PNGDEC_WidthTooLarge = MAKE_STATUS(kStatusGroup_PNGDEC, 1), /*!< The image width is larger than 1024. */
};

/*! @brief Interrupt enable/disable mask. */
enum _pngdec_interrupt_enable
{
    kPNGDEC_ChecksumErrorFlag   = (1U << 0U), /*!< ADLER-32 checksum error status and interrupt enable. */
    kPNGDEC_CrcErrorFlag        = (1U << 1U), /*!< CRC error status and interrupt enable. */
    kPNGDEC_HeaderErrorFlag     = (1U << 2U), /*!< Header error status and interrupt enable. */
    kPNGDEC_BtypeErrorFlag      = (1U << 3U), /*!< B type error status and interrupt enable. TODO*/
    kPNGDEC_ZlibHeaderErrorFlag = (1U << 4U), /*!< Zlib header error status and interrupt enable. */
    kPNGDEC_BitDepthErrorFlag =
        (1U << 5U), /*!< Bit depth error status and interrupt enable. Bit depth less than 8 bit not supported. */
    kPNGDEC_InterlaceErrorFlag =
        (1U << 6U), /*!< Interlace error status and interrupt enable. Interlace is not supported. */
    kPNGDEC_WidthErrorFlag          = (1U << 7U), /*!< Width error status and interrupt enable. Max image width 1024. */
    kPNGDEC_EncodeDataDoneFlag      = (1U << 8U), /*!< Data encoding done status and interrupt enable. */
    kPNGDEC_DecodePixelDoneFlag     = (1U << 9U), /*!< Pixel data decoding done status and interrupt enable. */
    kPNGDEC_DecodeAncillaryDoneFlag = (1U << 10U), /*!< Ancillary data decoding done status and interrupt enable. */

    kPNGDEC_ErrorFlags = kPNGDEC_ChecksumErrorFlag | kPNGDEC_CrcErrorFlag | kPNGDEC_HeaderErrorFlag |
                         kPNGDEC_BtypeErrorFlag | kPNGDEC_ZlibHeaderErrorFlag | kPNGDEC_BitDepthErrorFlag |
                         kPNGDEC_InterlaceErrorFlag | kPNGDEC_WidthErrorFlag,
};

/*!
 * @brief PNG decode endian mode.
 */
typedef enum _pngdec_endian_mode
{
    kPNGDEC_LittleEndian = 0U, /*!< Little endian. */
    kPNGDEC_BigEndian    = 1U, /*!< Big endian. */
} pngdec_endian_mode_t;

/*! @brief Configuration for PNGDEC. */
typedef struct _pngdec_config
{
    bool enableAncillary;            /*!< Enable ancillary data drop. */
    bool enable;                     /*!< Enables the decode IP. */
} pngdec_config_t;

/*!
 * @brief PNG color type.
 */
typedef enum _pngdec_color_type
{
    kPNGDEC_PixelFormatY8              = 0U, /*!< 8-bit monochrome(gray scale). */
    kPNGDEC_PixelFormatYA88            = 1U, /*!< 16-bit monochrome(gray scale) with alpha. */
    kPNGDEC_PixelFormatRGB888          = 2U, /*!< 24-bit RGB true color, 8-bit each palette. */
    kPNGDEC_PixelFormatRGBA8888        = 3U, /*!< 32-bit RGBA true color with alpha, 8-bit each palette. */
    kPNGDEC_PixelFormatRGB16_16_16     = 4U, /*!< 48-bit RGB true color, 16-bit each palette. */
    kPNGDEC_PixelFormatRGBA16_16_16_16 = 5U, /*!< 64-bit RGBA true color with alpha, 16-bit each palette. */
    kPNGDEC_PixelFormatLUT8            = 6U, /*!< 8-bit Indexed Color. */
} pngdec_color_type_t;

/*! @brief The decoded image info structure. */
typedef struct _pngdec_image
{
    uint32_t width;                /*!< Decoded image width. */
    uint32_t height;               /*!< Decoded image height. */
    pngdec_color_type_t colorType; /*!< Color type for the generated image. */
    uint8_t *imageData;            /*!< Pointer to the buffer for decoded image data. */
    uint8_t *ancillaryData;        /*!< Pointer to the buffer for decoded ancillary data. */
    uint32_t ancillaryLength;      /*!< Length of the ancillary data. */
} pngdec_image_t;

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
 * @brief Initializes the PNGDEC.
 *
 * The default configuration can be got by calling PNGDEC_GetDefaultConfig().
 *
 * @param base PNGDEC peripheral base address.
 * @param config Pointer to PNGDEC configuration structure.
 */
void PNGDEC_Init(PNGDEC_Type *base, const pngdec_config_t *config);

/*!
 * @brief Deinitializes the PNGDEC.
 *
 * @param base PNGDEC peripheral base address.
 */
void PNGDEC_Deinit(PNGDEC_Type *base);

/*!
 * @brief Gets the default configuration for PNGDEC.
 *
 * This function initializes the user configuration structure to default value. The default value are:
 *
 * Example:
   @code
   config->enableAncillary = false;
   config->enable = false;
   @endcode
 *
 * @param config Pointer to PNGDEC configuration structure.
 */
void PNGDEC_GetDefaultConfig(pngdec_config_t *config);
/* @} */

/*!
 * @name Interrupts
 * @{
 */
/*!
 * @brief Enables interrupts.
 *
 * @param base PNGDEC peripheral base address.
 * @param mask Interrupts mask. See "_pngdec_interrupt_enable".
 */
static inline void PNGDEC_EnableInterrupts(PNGDEC_Type *base, uint32_t mask)
{
    base->DEC_INT_STS_EN |= mask;
}

/*!
 * @brief Disables interrupts.
 *
 * @param base PNGDEC peripheral base address.
 * @param mask Interrupts mask. See "_pngdec_interrupt_enable".
 */
static inline void PNGDEC_DisableInterrupts(PNGDEC_Type *base, uint32_t mask)
{
    base->DEC_INT_STS_EN &= ~mask;
}
/* @} */

/*!
 * @name Status
 * @{
 */
/*!
 * @brief Gets status flags.
 *
 * @param base PNGDEC peripheral base address.
 * @return Status flags asserted mask. See "_pngdec_status_flags".
 */
static inline uint32_t PNGDEC_GetStatusFlags(PNGDEC_Type *base)
{
    return base->DEC_INT_STS;
}

/*!
 * @brief Clears status flags.
 *
 * @param base PNGDEC peripheral base address.
 * @param mask Status flags mask. See "_pngdec_status_flags".
 */
static inline void PNGDEC_ClearStatusFlags(PNGDEC_Type *base, uint32_t mask)
{
    base->DEC_INT_STS = mask;
}
/* @} */

/*!
 * @name Basic Operations
 * @{
 */
/*!
 * @brief Resets the PNGDEC code and DMA logic.
 *
 * @param base PNGDEC peripheral base address.
 */
static inline void PNGDEC_Reset(PNGDEC_Type *base)
{
    base->GLB_CTRL |= (PNGDEC_GLB_CTRL_DMA_SW_LOGIC_RST_EN_MASK | PNGDEC_GLB_CTRL_IPCORE_SW_LOGIC_RST_EN_MASK);
    base->CNT_CTRL_CLR = PNGDEC_CNT_CTRL_CLR_CNT_CTRL_CLR_MASK;
    base->GLB_CTRL &= ~(PNGDEC_GLB_CTRL_DMA_SW_LOGIC_RST_EN_MASK | PNGDEC_GLB_CTRL_IPCORE_SW_LOGIC_RST_EN_MASK);
    base->CNT_CTRL_CLR = 0U;
}

/*!
 * @brief Enables or disables the PNGDEC.
 *
 * @param base PNGDEC peripheral base address.
 * @param enable True to enable the PNGDEC.
 */
static inline void PNGDEC_Enable(PNGDEC_Type *base, bool enable)
{
    if (enable)
    {
        base->GLB_CTRL |= PNGDEC_GLB_CTRL_DEC_EN_MASK;
    }
    else
    {
        base->GLB_CTRL &= ~PNGDEC_GLB_CTRL_DEC_EN_MASK;
    }
}

/*!
 * @brief Enables or disables the PNGDEC ancillary drop.
 *
 * @param base PNGDEC peripheral base address.
 * @param enable True to enable the PNGDEC ancillary drop.
 */
static inline void PNGDEC_EnableAncillary(PNGDEC_Type *base, bool enable)
{
    if (enable)
    {
        base->GLB_CTRL |= PNGDEC_GLB_CTRL_ANC_DROP_EN_MASK;
    }
    else
    {
        base->GLB_CTRL &= ~PNGDEC_GLB_CTRL_ANC_DROP_EN_MASK;
    }
}

/*!
 * @brief Starts the PNG decode
 *
 * @param base PNGDEC peripheral base address.
 */
static inline void PNGDEC_StartDecode(PNGDEC_Type *base) // TODO self clear?
{
    base->DMA_TRIG = PNGDEC_DMA_TRIG_DMA_TRIG_MASK;
    base->DMA_TRIG = 0U;
}
/* @} */

/*!
 * @name Image decode
 * @{
 */

/*!
 * @brief Sets the address and length of the raw PNG image.
 *
 * @param base PNGDEC peripheral base address.
 * @param data Start address of the buffer of the raw PNG image, shall be 8-byte aligned.
 * @param length Size of the buffer.
 */
void PNGDEC_SetPngBuffer(PNGDEC_Type *base, uint8_t *buffer, size_t length);

/*!
 * @brief Sets the address of the decoded data.
 *
 * @param base PNGDEC peripheral base address.
 * @param imageData Start address of the buffer for the decoded image data, shall be 8-byte aligned.
 * @param ancillaryData Start address of the buffer for the decoded ancillary data, shall be 8-byte aligned.
 */
static inline void PNGDEC_SetOutputBuffer(PNGDEC_Type *base, uint8_t *imageData, uint8_t *ancillaryData)
{
    assert(((uint32_t)imageData & 0x7U) == 0U);
    assert(((uint32_t)ancillaryData & 0x7U) == 0U);

    base->DEC_PIXEL_DMA_DES_ADDR = (uint32_t)imageData;
    base->DEC_ANC_DMA_DES_ADDR   = (uint32_t)ancillaryData;
}

/*!
 * @brief Parses the PNG header and stores the info in the decoded image info structure.
 *
 * @param image Pointer to PNGDEC decoded image info structure.
 * @param pngBuf Pointer to PNG file buffer.
 * @retval kStatus_Success Header parsing success.
 * @retval kStatus_Fail PNG header parsing failed due corrupted header.
 * @retval kStatus_PNGDEC_WidthTooLarge Header parsing failed due to the image width is larger than 1024.
 * @retval kStatus_PNGDEC_NotSupported Header parsing failed due to the image is interlaced or the bit depth is less
   than 8.
 */
status_t PNGDEC_ParseHeader(pngdec_image_t *image, uint8_t *pngBuf);

/*!
 * @brief Decodes the PNG image.
 *
 * This function performs the PNG decoding in blocking way and stores the decoded info in decoded image info structure.
 *
 * @param base PNGDEC peripheral base address.
 * @param image Pointer to PNGDEC decoded image info structure.
 * @param status Pointer to decoded status. When retval is kStatus_Fail, Checksum/Crc/Header/Btype/ZlibHeader error may occur
   due to PNG file corruption, user can check which error(s) occured if necessary.
 * @retval kStatus_Success PNG decoding success.
 * @retval kStatus_Fail PNG decoding failed due to CRC/header/B type/Alder error or invalid PNG file.
 * @retval kStatus_PNGDEC_WidthTooLarge PNG decoding failed due to the image width is larger than 1024.
 * @retval kStatus_PNGDEC_NotSupported PNG decoding failed due to the image is interlaced or the bit depth is less
   than 8.
 */
status_t PNGDEC_Decode(PNGDEC_Type *base, pngdec_image_t *image, uint32_t *status);
/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_PNGDEC_H_ */
