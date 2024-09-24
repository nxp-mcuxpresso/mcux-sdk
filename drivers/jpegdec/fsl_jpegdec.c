/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_jpegdec.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.jpegdec"
#endif

#if defined(JPEGDEC_RSTS)
#define JPEGDEC_RESETS_ARRAY JPEGDEC_RSTS
#endif

#define JPEG_SOF0_MARKER 0xC0UL
#define JPEG_SOF1_MARKER 0xC1UL
#define JPEG_GET_U16(p)  ((((uint16_t)(*(p))) << 8) + ((uint16_t)(*((p) + 1))))

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get the jpegdec instance from the peripheral base address.
 *
 * @param base JPEG decoder peripheral base address.
 * @return JPEG decoder instance.
 */
static uint32_t JPEGDEC_GetInstance(JPEG_DECODER_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Array of JPEG decoder core peripheral base address. */
static JPEGDEC_Type *const s_jpegdecBases[] = JPEGDEC_BASE_PTRS;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/* Clock name of JPEG decoder. */
static const clock_ip_name_t s_jpegdecClock[] = JPEGDEC_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
/* Array of JPEG decoder peripheral resets. */
#if defined(JPEGDEC_RESETS_ARRAY)
/* Reset array */
static const reset_ip_name_t s_jpegdecResets[] = JPEGDEC_RESETS_ARRAY;
#endif

/*******************************************************************************
 * Codes
 ******************************************************************************/
static uint32_t JPEGDEC_GetInstance(JPEG_DECODER_Type *base)
{
    uint32_t instance = 0U;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_jpegdecBases); instance++)
    {
        if (MSDK_REG_SECURE_ADDR(s_jpegdecBases[instance]) == MSDK_REG_SECURE_ADDR(base->core))
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_jpegdecBases));

    return instance;
}

/*!
 * brief Gets the default configuration for JPEG decoder.
 *
 * This function initializes the user configuration structure to default value. The default value are:
 *
 * Example:
   code
   config->endianMode = kJPEGDEC_LittleEndian;
   config->slots      = 0xFU;
   config->enable     = true;
   config->enableLp   = false;
   endcode
 *
 * param config Pointer to JPEG decoder configuration structure.
 */
void JPEGDEC_GetDefaultConfig(jpegdec_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    /* Fill default configuration */
    config->endianMode = kJPEGDEC_LittleEndian;
    config->slots      = 0xFU; /* Enable all 4 slots. */
    config->enable     = true;
    config->enableLp   = false;
}

/*!
 * brief Initializes the JPEG decoder.
 *
 * The default configuration can be got by calling @ref JPEGDEC_GetDefaultConfig().
 *
 * param base JPEG decoder peripheral base address.
 * param config Pointer to JPEG decoder configuration structure.
 */
void JPEGDEC_Init(JPEG_DECODER_Type *base, const jpegdec_config_t *config)
{
    assert(NULL != config);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Open clock gate. */
    CLOCK_EnableClock(s_jpegdecClock[JPEGDEC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if defined(JPEGDEC_RESETS_ARRAY)
    RESET_ReleasePeripheralReset(s_jpegdecResets[JPEGDEC_GetInstance(base)]);
#endif

    JPEGDEC_Reset(base);

    JPEGDEC_EnableSlots(base, config->slots);
    JPEGDEC_SetEndian(base, config->endianMode);
    JPEGDEC_Enable(base, config->enable);
    JPEGDEC_EnableLp(base, config->enableLp);
}

/*!
 * brief Deinitializes the JPEG decoder.
 *
 * param base JPEG decoder peripheral base address.
 */
void JPEGDEC_Deinit(JPEG_DECODER_Type *base)
{
    /* Disable the module. */
    JPEGDEC_Enable(base, false);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable clock gate. */
    CLOCK_DisableClock(s_jpegdecClock[JPEGDEC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Gets the current active slot
 *
 * param base JPEG decoder peripheral base address.
 * param slot Pointer to the variable that stores the enabled slot.
 * retval #kStatus_Success Successfully get the current active slot.
 * retval #kStatus_Fail Current JPEG decoder is idle, no slot is active.
 */
status_t JPEGDEC_GetActiveSlot(JPEG_DECODER_Type *base, uint8_t *slot)
{
    if ((base->wrapper->COM_STATUS & JPGDECWRP_COM_STATUS_DEC_ONGOING_MASK) != 0U)
    {
        *slot = (uint8_t)((base->wrapper->COM_STATUS & JPGDECWRP_COM_STATUS_CUR_SLOT_MASK) >>
                          JPGDECWRP_COM_STATUS_CUR_SLOT_SHIFT);
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Sets the address and length of the JPEG image.
 *
 * param[out] config Decoder configuration.
 * param data Start address of the buffer of the raw JPEG image, shall be 8-byte aligned.
 * param length Size of the buffer.
 */
void JPEGDEC_SetJpegBuffer(jpegdec_decoder_config_t *config, uint8_t *buffer, size_t length)
{
    assert(((uint32_t)buffer & 0xFU) == 0U); /* Has to be 16-byte aligned. */

    config->jpegBufAddr = (uint32_t)buffer;
    config->jpegBufSize = JPEG_ALIGN_SIZE(length, 0x400U); /* Has to be integer times of 1K. */
}

/*!
 * brief Sets the address of the decoded data.
 *
 * param[out] config Decoder configuration.
 * param imageData0 address of the output buffer0, shall be 16-byte aligned.
 * param imageData1 address of the output buffer1, only used when output format is YUV420, shall be 16-byte aligned.
 */
void JPEGDEC_SetOutputBuffer(jpegdec_decoder_config_t *config, uint8_t *imageData0, uint8_t *imageData1)
{
    assert(imageData0 != NULL);
    assert(((uint32_t)imageData0 & 0xFU) == 0U); /* Has to be 16-byte aligned. */
    assert(((uint32_t)imageData1 & 0xFU) == 0U);

    config->outBufAddr0 = (uint32_t)imageData0;
    config->outBufAddr1 = (uint32_t)imageData1;
}

/*!
 * brief Parses the JPEG header and stores the info in the decoder configuration structure.
 *
 * param[out] config Decoder configuration.
 * retval kStatus_Success Header parsing success.
 * retval kStatus_Fail JPEG header parsing failed due corrupted header.
 * retval kStatus_JPEGDEC_NotSupported Header parsing failed due to the image pixel format is not supported
   or image width/height is larger than 8k or image width/height is not 8-byte or 16-byte aligned.
 */
status_t JPEGDEC_ParseHeader(jpegdec_decoder_config_t *config)
{
    status_t result = kStatus_Success;
    /* Get the JPEG image buffer and length. */
    uint8_t *imageBuf    = (uint8_t *)config->jpegBufAddr;
    uint32_t imageLength = config->jpegBufSize;
    uint16_t width, height;

    /* Find the SOF0 marker, SOF image info need at least 16 bytes. */
    imageLength = config->jpegBufSize;
    imageBuf    = (uint8_t *)config->jpegBufAddr;
    while (imageLength-- > 16U)
    {
        if (*imageBuf++ == 0xFFU)
        {
            if ((*imageBuf == JPEG_SOF0_MARKER) || (*imageBuf == JPEG_SOF1_MARKER))
            {
                imageBuf++;
                break;
            }
        }
    }

    if (imageLength == 16U)
    {
        /* Can not find the SOF marker, return error. */
        return kStatus_Fail;
    }

    /* Get the pixel depth. */
    if (imageBuf[2] == 8U)
    {
        config->pixelDepth = (uint32_t)kJPEGDEC_PixelDepth8Bit;
    }
    else if (imageBuf[2] == 12U)
    {
        config->pixelDepth = (uint32_t)kJPEGDEC_PixelDepth12Bit;
    }
    else
    {
        /* Undefined pixel depth, return error. */
        return kStatus_Fail;
    }

    /* Check component number. */
    switch (imageBuf[7U])
    {
        case 1U:
            config->pixelFormat = (uint32_t)kJPEGDEC_PixelFormatGray;
            break;
        case 3U:
            /* Componnet ids are 0x1, 0x2 and 0x3 means YUV format. */
            if ((imageBuf[8U] == 0x1U) && (imageBuf[11U] == 0x2U) && (imageBuf[14U] == 0x3U))
            {
                /* UV component x/y sample points is 1/1. */
                if ((imageBuf[12U] == 0x11U) && (imageBuf[15U] == 0x11U))
                {
                    /* Y component x/y sample points is also 1/1, means each Y component has 1 UV component, format
                     * YUV444. */
                    if (imageBuf[9U] == 0x11U)
                    {
                        config->pixelFormat = (uint32_t)kJPEGDEC_PixelFormatYUV444;
                    }
                    /* Y component x/y sample points is 2/1 or 1/2, means in each line/row every 2 Y componnets share 1
                     * UV component, format YUV422. */
                    else if ((imageBuf[9U] == 0x21U) || (imageBuf[9U] == 0x12U))
                    {
                        config->pixelFormat = (uint32_t)kJPEGDEC_PixelFormatYUV422;
                    }
                    /* Y component sample points is 2/2, means in each line and each column, every 2 Y componnets share
                     * 1 U or V component, format YUV420. */
                    else if (imageBuf[9U] == 0x22U)
                    {
                        config->pixelFormat = (uint32_t)kJPEGDEC_PixelFormatYUV420;
                    }
                    else
                    {
                        /* Unsupported pixel format. */
                        return kStatus_JPEGDEC_NotSupported;
                    }
                }
                else
                {
                    /* Unsupported pixel format. */
                    return kStatus_JPEGDEC_NotSupported;
                }
            }
            /* Componnet ids are 0x52, 0x47 and 0x42 means RGB format. */
            else if ((imageBuf[8U] == 0x52U) && (imageBuf[11U] == 0x47U) && (imageBuf[14U] == 0x42U))
            {
                /* Component ID = "RGB" */
                config->pixelFormat = (uint32_t)kJPEGDEC_PixelFormatRGB;
            }
            else
            {
                /* Unsupported pixel format. */
                return kStatus_JPEGDEC_NotSupported;
            }
            break;
        case 4U:
            config->pixelFormat = (uint32_t)kJPEGDEC_PixelFormatYCCK;
            break;
        default:
            /* Unknown component number, return error. */
            result = kStatus_JPEGDEC_NotSupported;
            break;
    }

    if (result != kStatus_Success)
    {
        return result;
    }

    /* Get the height and width. */
    height = JPEG_GET_U16(&imageBuf[3]);
    width  = JPEG_GET_U16(&imageBuf[5]);
    if ((height > 0x2000U) || (width > 0x2000U) || (height < 64U) || (width < 64U))
    {
        /* Max support 8K width/height, min support 64 width/height. Picture with width/height that is
           smaller than 64 will corrupt the next frame to be decoded. Errata ERR050135. */
        return kStatus_JPEGDEC_NotSupported;
    }

    config->height = (uint32_t)height;
    config->width  = (uint32_t)width;

    if (config->pixelFormat == (uint32_t)kJPEGDEC_PixelFormatYUV420)
    {
        if (((height & 0xFU) != 0U) || ((width & 0xFU) != 0U))
        {
            result = kStatus_JPEGDEC_NotSupported;
        }
    }
    else if (config->pixelFormat == (uint32_t)kJPEGDEC_PixelFormatYUV422)
    {
        /* For YUV422, width and height shall be divisible by 16 and 8. */
        if (((height & 0x7U) != 0U) || ((width & 0xFU) != 0U))
        {
            result = kStatus_JPEGDEC_NotSupported;
        }
    }
    else
    {
        /* For YUV420, width and height shall all be divisible by 8. */
        if (((height & 0x7U) != 0U) || ((width & 0x7U) != 0U))
        {
            result = kStatus_JPEGDEC_NotSupported;
        }
    }

    return result;
}

/*!
 * brief Sets the decode option.
 *
 * param[out] config Decoder configuration.
 * param pitch Output buffer pitch.
 * param clearStreamBuf Set to true to clear the saved bit stream buffer, not used in single frame mode.
 * param autoStart Set to true to automatically start the decoding when this descriptor is switched, not used in single
   frame mode.
 */
void JPEGDEC_SetDecodeOption(jpegdec_decoder_config_t *config, uint16_t pitch, bool clearStreamBuf, bool autoStart)
{
    config->outBufPitch    = (uint32_t)pitch;
    config->clearStreamBuf = (uint32_t)clearStreamBuf;
    config->autoStart      = (uint32_t)autoStart;
}

/*!
 * brief Sets JPEG decoder decoder configuration.
 *
 * Call this API to set the decoder configuration and then call @ref JPEGDEC_StartDecode
 * to start decode. Need to enable at least one slot in @ref jpegdec_config_t first.
 *
 * param base JPEG decoder peripheral base address.
 * param config Decoder configuration.
 */
void JPEGDEC_ConfigDecoder(JPEG_DECODER_Type *base, const jpegdec_decoder_config_t *config)
{
    assert((config->outBufAddr0 & 0xFU) == 0U);
    assert((config->outBufAddr1 & 0xFU) == 0U);
    assert((config->jpegBufAddr & 0xFU) == 0U);
    assert((config->jpegBufSize & 0x3FFU) == 0U);

    base->wrapper->OUT_BUF_BASE0 = config->outBufAddr0;
    base->wrapper->OUT_BUF_BASE1 = config->outBufAddr1;
    base->wrapper->OUT_PITCH     = (uint32_t)config->outBufPitch;
    base->wrapper->STM_BUFBASE   = config->jpegBufAddr;
    base->wrapper->STM_BUFSIZE   = config->jpegBufSize;
    base->wrapper->IMGSIZE       = (uint32_t)config->height | ((uint32_t)config->width << 16U);
    base->wrapper->STM_CTRL      = (config->pixelDepth << JPGDECWRP_STM_CTRL_PIXEL_PRECISION_SHIFT) |
                              (config->pixelFormat << JPGDECWRP_STM_CTRL_IMAGE_FORMAT_SHIFT) |
                              (config->clearStreamBuf << JPGDECWRP_STM_CTRL_BITBUF_PTR_CLR_SHIFT) |
                              (config->autoStart << JPGDECWRP_STM_CTRL_AUTO_START_SHIFT);
}

/*!
 * brief Sets the address of the next decoder descriptor for certain slot
 *
 * Call this API to set the decoder descriptor for certain slot, and then call
 * @ref JPEGDEC_EnableSlotNextDescpt to enable the descriptor. If the decode configuration
 * of this descriptor has enabled autoStart then decode will start automatically.
 * Otherwise user has to call @ref JPEGDEC_StartDecode manually. Need to enable the
 * slot in @ref jpegdec_config_t first.
 *
 * param base JPEG decoder peripheral base address.
 * param slot Slot number.
 * param descriptor Pointer to the descriptor structure.
 */
void JPEGDEC_SetSlotNextDescpt(JPEG_DECODER_Type *base, uint8_t slot, jpegdec_descpt_t *descriptor)
{
    assert(slot < 4U);
    assert(((uint32_t)descriptor & 0x3U) == 0U);
    assert((descriptor->config.outBufAddr0 & 0xFU) == 0U);
    assert((descriptor->config.outBufAddr1 & 0xFU) == 0U);
    assert((descriptor->config.jpegBufAddr & 0xFU) == 0U);
    assert((descriptor->config.jpegBufSize & 0x3FFU) == 0U);

    base->wrapper->SLOT_REGS[slot].SLOT_NXT_DESCPT_PTR = (uint32_t)descriptor;
}

/*!
 * brief Sets all fields to default values for the descriptor structure.
 *
 * param descriptor Pointer to the descriptor structure.
 * note This function enables the auto start feature.
 */
void JPEGDEC_DescptReset(jpegdec_descpt_t *descriptor)
{
    assert(descriptor != NULL);

    /* Reset channel descriptor */
    descriptor->nextDescptAddr        = 0U;
    descriptor->config.outBufAddr0    = 0U;
    descriptor->config.outBufAddr0    = 0U;
    descriptor->config.outBufPitch    = 0U;
    descriptor->config.jpegBufAddr    = 0U;
    descriptor->config.jpegBufSize    = 0U;
    descriptor->config.height         = 0U;
    descriptor->config.width          = 0U;
    descriptor->config.pixelDepth     = (uint32_t)kJPEGDEC_PixelDepth8Bit;
    descriptor->config.pixelFormat    = (uint32_t)kJPEGDEC_PixelFormatYUV420;
    descriptor->config.clearStreamBuf = (uint32_t) false;
    /* Enable auto start. */
    descriptor->config.autoStart = (uint32_t) true;
}
