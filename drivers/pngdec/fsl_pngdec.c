/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_pngdec.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.pngdec"
#endif

#define PNG_MARKER        0x89504e47UL
#define PNG_HEADER_MARKER 0x49484452UL
#define PNG_GET_U32(p) \
    ((((uint32_t)(*(p))) << 24) + (((uint32_t)(*((p) + 1))) << 16) + (((uint32_t)(*((p) + 2))) << 8) + ((uint32_t)(*((p) + 3))))

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get the PNGDEC instance from the peripheral base address.
 *
 * @param base PNGDEC peripheral base address.
 * @return PNGDEC instance.
 */
static uint32_t PNGDEC_GetInstance(PNGDEC_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Array of PNGDEC peripheral base address. */
static PNGDEC_Type *const s_pngdecBases[] = PNGDEC_BASE_PTRS;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/* Clock name of PNGDEC. */
static const clock_ip_name_t s_pngdecClock[] = PNGDEC_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
#if defined(PNGDEC_RSTS)
/* Reset array */
static const reset_ip_name_t s_pngdecResets[] = PNGDEC_RSTS;
#endif
/*******************************************************************************
 * Codes
 ******************************************************************************/
static uint32_t PNGDEC_GetInstance(PNGDEC_Type *base)
{
    uint32_t instance = 0U;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_pngdecBases); instance++)
    {
        if (MSDK_REG_SECURE_ADDR(s_pngdecBases[instance]) == MSDK_REG_SECURE_ADDR(base))
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_pngdecBases));

    return instance;
}

/*!
 * brief Initializes the PNGDEC.
 *
 * The default configuration can be got by calling PNGDEC_GetDefaultConfig().
 *
 * param base PNGDEC peripheral base address.
 * param config Pointer to PNGDEC configuration structure.
 */
void PNGDEC_Init(PNGDEC_Type *base, const pngdec_config_t *config)
{
    assert(NULL != config);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Open clock gate. */
    CLOCK_EnableClock(s_pngdecClock[PNGDEC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if defined(PNGDEC_RSTS)
    RESET_ReleasePeripheralReset(s_pngdecResets[PNGDEC_GetInstance(base)]);
#endif

    /* Reset the module before configuring it. */
    PNGDEC_Reset(base);

    base->GLB_CTRL = PNGDEC_GLB_CTRL_ANC_DROP_EN((uint32_t)config->enableAncillary) |
                     PNGDEC_GLB_CTRL_DEC_EN((uint32_t)config->enable);
}

/*!
 * brief Deinitializes the PNGDEC.
 *
 * param base PNGDEC peripheral base address.
 */
void PNGDEC_Deinit(PNGDEC_Type *base)
{
    /* Disable the module. */
    PNGDEC_Enable(base, false);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable clock gate. */
    CLOCK_DisableClock(s_pngdecClock[PNGDEC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Gets the default configuration for PNGDEC.
 *
 * This function initializes the user configuration structure to default value. The default value are:
 *
 * Example:
   code
   config->enableAncillary = false;
   config->enable = true;
   endcode
 *
 * param config Pointer to PNGDEC configuration structure.
 */
void PNGDEC_GetDefaultConfig(pngdec_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    /* Fill default configuration */
    config->enableAncillary = false;
    config->enable          = true;
}

/*!
 * brief Sets the address and length of the raw PNG image.
 *
 * param base PNGDEC peripheral base address.
 * param data Start address of the buffer of the raw PNG image, shall be 8-byte aligned.
 * param length Size of the buffer.
 */
void PNGDEC_SetPngBuffer(PNGDEC_Type *base, uint8_t *buffer, size_t length)
{
    assert(((uint32_t)buffer & 0x7U) == 0U);
    assert(length > 32U);

    base->ENC_DATA_DMA_SRC_ADDR = (uint32_t)buffer;
    base->ENC_DATA_DMA_SRC_LEN  = length;
}

/*!
 * brief Parses the PNG header and stores the info in the decoded image info structure.
 *
 * param image Pointer to PNGDEC decoded image info structure.
 * param pngBuf Pointer to PNG file buffer.
 * retval kStatus_Success Header parsing success.
 * retval kStatus_Fail PNG header parsing failed due corrupted header.
 * retval kStatus_PNGDEC_WidthTooLarge Header parsing failed due to the image width is larger than 1024.
 * retval kStatus_PNGDEC_NotSupported Header parsing failed due to the image is interlaced or the bit depth is less
   than 8.
 */
status_t PNGDEC_ParseHeader(pngdec_image_t *image, uint8_t *pngBuf)
{
    assert(pngBuf != NULL);

    /* Initializes the structure to zero. */
    (void)memset(image, 0, sizeof(*image));

    status_t result = kStatus_Success;
    uint8_t bitDepth;
    bool isInterlaced;
    uint8_t colorType;

    /* Check if the file is a PNG file and PNG header marker is there. */
    if ((PNG_GET_U32(pngBuf) != PNG_MARKER) || (PNG_GET_U32(&pngBuf[12U]) != PNG_HEADER_MARKER))
    {
        return kStatus_Fail;
    }

    image->width = PNG_GET_U32(&pngBuf[16U]);

    /* Check if the PNG width is larger than the max value supported. */
    if (image->width > 1024U)
    {
        return kStatus_PNGDEC_WidthTooLarge;
    }

    image->height = PNG_GET_U32(&pngBuf[20U]);
    bitDepth      = pngBuf[24U];
    isInterlaced  = (bool)pngBuf[28U];
    colorType     = 0U;

    /* Check whether the bit depth is less than 8 or the image is interlaced. */
    if ((bitDepth < 8U) || (isInterlaced == true))
    {
        return kStatus_PNGDEC_NotSupported;
    }

    if ((bitDepth != 8U) && (bitDepth != 16U))
    {
        /* Corrupt header info, unrecognized bit depth. */
        return kStatus_Fail;
    }

    switch (pngBuf[25U])
    {
        case 3U:
            image->colorType = kPNGDEC_PixelFormatLUT8;
            break;
        case 4U:
            colorType = 1U;
        case 0U:
            colorType += (uint8_t)kPNGDEC_PixelFormatY8;
            image->colorType = (pngdec_color_type_t)colorType;
            if (bitDepth != 8U)
            {
                result = kStatus_Fail;
            }
            break;
        case 6U:
            colorType = 1U;
        case 2U:
            if (bitDepth == 8U)
            {
                colorType += (uint8_t)kPNGDEC_PixelFormatRGB888;
            }
            else
            {
                colorType += (uint8_t)kPNGDEC_PixelFormatRGB16_16_16;
            }
            image->colorType = (pngdec_color_type_t)colorType;
            break;
        default:
            /* Corrupt header info, unrecognized image type. */
            result = kStatus_Fail;
            break;
    }

    return result;
}

/*!
 * brief Decodes the PNG image.
 *
 * This function performs the PNG decoding in blocking way and stores the decoded info in decoded image info structure.
 *
 * param base PNGDEC peripheral base address.
 * param image Pointer to PNGDEC decoded image info structure.
 * param status Pointer to decoded status. When retval is kStatus_Fail, Checksum/Crc/Header/Btype/ZlibHeader error may
 occur due to PNG file corruption, user can check which error(s) occured if necessary.
 * retval kStatus_Success PNG decoding success.
 * retval kStatus_Fail PNG decoding failed due to CRC/header/B type/Alder error or invalid PNG file.
 * retval kStatus_PNGDEC_WidthTooLarge PNG decoding failed due to the image width is larger than 1024.
 * retval kStatus_PNGDEC_NotSupported PNG decoding failed due to the image is interlaced or the bit depth is less
 * than 8.
 */
status_t PNGDEC_Decode(PNGDEC_Type *base, pngdec_image_t *image, uint32_t *status)
{
    status_t result = kStatus_Success;
    uint32_t statusFlags;
    uint32_t DoneFlags = (uint32_t)kPNGDEC_DecodePixelDoneFlag;

    image->imageData     = (uint8_t *)(base->DEC_PIXEL_DMA_DES_ADDR);
    image->ancillaryData = (uint8_t *)(base->DEC_ANC_DMA_DES_ADDR);

    /* Clear dirty counter, write 1 then clear. */
    base->CNT_CTRL_CLR = PNGDEC_CNT_CTRL_CLR_CNT_CTRL_CLR_MASK;
    base->CNT_CTRL_CLR = 0U;

    /* Clear all status. */
    base->DEC_INT_STS = 0xFFFFU;

    /* Start decoding. */
    PNGDEC_StartDecode(base);

    /* Wait for the decoding done. */
    if ((base->GLB_CTRL & PNGDEC_GLB_CTRL_ANC_DROP_EN_MASK) != 0U)
    {
        DoneFlags |= (uint32_t)kPNGDEC_DecodeAncillaryDoneFlag;
    }
    statusFlags = PNGDEC_GetStatusFlags(base);
    while ((PNGDEC_GetStatusFlags(base) & DoneFlags) != DoneFlags)
    {
        statusFlags = PNGDEC_GetStatusFlags(base);
        if ((statusFlags & (uint32_t)kPNGDEC_ErrorFlags) != 0U)
        {
            result = kStatus_Fail;
            break;
        }
    }

    if ((statusFlags & (uint32_t)kPNGDEC_ErrorFlags) != 0U)
    {
        if ((statusFlags & (uint32_t)kPNGDEC_WidthErrorFlag) != 0U)
        {
            result = kStatus_PNGDEC_WidthTooLarge;
        }
        if ((statusFlags & ((uint32_t)kPNGDEC_BitDepthErrorFlag | (uint32_t)kPNGDEC_InterlaceErrorFlag)) != 0U)
        {
            result = kStatus_PNGDEC_NotSupported;
        }
    }
    else
    {
        image->ancillaryLength = base->DEC_ANC_DMA_DES_LEN;
    }

    if (status != NULL)
    {
        *status = statusFlags;
    }

    return result;
}