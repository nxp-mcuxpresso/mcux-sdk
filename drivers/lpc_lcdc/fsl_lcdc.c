/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_lcdc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lpc_lcdc"
#endif

/* Max value of LCD_POL[PCD]. */
#define LCD_PCD_MAX                                                                 \
    ((uint32_t)(((uint32_t)LCD_POL_PCD_LO_MASK >> (uint32_t)LCD_POL_PCD_LO_SHIFT) | \
                ((uint32_t)LCD_POL_PCD_HI_MASK >> ((uint32_t)LCD_POL_PCD_HI_SHIFT - (uint32_t)LCD_POL_PCD_LO_SHIFT))))

/* Macro to contruct the LCD_POL[PCD]. */
#if (LCD_POL_PCD_LO_MASK != 0x1F)
#error LCD_POL_PCD_LO is not 5-bit. The macro LCD_POL_PCD_LO_WIDTH should be updated.
#endif
#define LCD_POL_PCD_LO_WIDTH 5U
#define LCD_POL_PCD(pcd)     (LCD_POL_PCD_LO(pcd) | LCD_POL_PCD_HI((pcd) >> LCD_POL_PCD_LO_WIDTH))

/* Cursor interrupt. */
#define LCDC_CURSOR_INT_MASK LCD_CRSR_INTMSK_CRSRIM_MASK

/* Interrupts except cursor interrupt. */
#define LCDC_NORMAL_INT_MASK \
    (LCD_INTMSK_FUFIM_MASK | LCD_INTMSK_LNBUIM_MASK | LCD_INTMSK_VCOMPIM_MASK | LCD_INTMSK_BERIM_MASK)

/* Detect the cursor interrupt and normal interrupt bits overlap. */
#if (LCDC_CURSOR_INT_MASK & LCDC_NORMAL_INT_MASK)
#error Cursor interrupt and normal interrupt overlap. The driver should be updated.
#endif

/* The max cursor clip value. */
#define LCDC_CLIP_MAX (LCD_CRSR_CLIP_CRSRCLIPX_MASK >> LCD_CRSR_CLIP_CRSRCLIPX_SHIFT)

/*******************************************************************************
 * Variables
 ******************************************************************************/
static LCD_Type *const s_lcdBases[] = LCD_BASE_PTRS;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
static const clock_ip_name_t s_lcdClocks[] = LCD_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
static const reset_ip_name_t s_lcdResets[] = LCD_RSTS;
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Gets the LCD instance according to the LCD base
 *
 * @param base LCD peripheral base address.
 * @return LCD instance.
 */
static uint32_t LCDC_GetInstance(LCD_Type *base);

/*!
 * @brief Calculate the clock divider to generate desired panel clock.
 *
 * @param config Pointer to the LCD configuration.
 * @param srcClock_Hz The LCD input clock (LCDCLK) frequency in Hz.
 * @param divider The divider result.
 * @return Return false if no divider available to generate the desired clock,
 * otherwise return true;
 */
static bool LCDC_GetClockDivider(const lcdc_config_t *config, uint32_t srcClock_Hz, uint32_t *divider);

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t LCDC_GetInstance(LCD_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_lcdBases); instance++)
    {
        if (s_lcdBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_lcdBases));

    return instance;
}

static bool LCDC_GetClockDivider(const lcdc_config_t *config, uint32_t srcClock_Hz, uint32_t *divider)
{
    uint16_t cpl;
    uint32_t pcd;

    *divider = 0U;

    /* Find the PCD. */
    pcd = (srcClock_Hz + (config->panelClock_Hz / 2U)) / config->panelClock_Hz;

    if (pcd <= 1U)
    {
        if (kLCDC_DisplayTFT == config->display)
        {
            pcd      = 0U;
            *divider = LCD_POL_BCD_MASK;
        }
        else
        {
            return false;
        }
    }
    else
    {
        pcd -= 2U;

        /* Verify the PCD value. */
        if (pcd > LCD_PCD_MAX)
        {
            return false;
        }

        if (((kLCDC_DisplaySingleColorSTN8Bit == config->display) && (pcd < 1U)) ||
            ((kLCDC_DisplayDualColorSTN8Bit == config->display) && (pcd < 4U)) ||
            ((kLCDC_DisplaySingleMonoSTN4Bit == config->display) && (pcd < 2U)) ||
            ((kLCDC_DisplaySingleMonoSTN8Bit == config->display) && (pcd < 6U)) ||
            ((kLCDC_DisplayDualMonoSTN4Bit == config->display) && (pcd < 6U)) ||
            ((kLCDC_DisplayDualMonoSTN8Bit == config->display) && (pcd < 14U)))
        {
            return false;
        }
    }

    if (0U != ((uint32_t)(config->display) & LCD_CTRL_LCDTFT_MASK))
    {
        /* TFT panel. */
        cpl = config->ppl - 1U;
    }
    else
    {
        if (0U != ((uint32_t)(config->display) & LCD_CTRL_LCDBW_MASK))
        {
            if (0U != ((uint32_t)(config->display) & LCD_CTRL_LCDMONO8_MASK))
            {
                /* 8-bit monochrome STN panel. */
                cpl = (config->ppl / 8U) - 1U;
            }
            else
            {
                /* 4-bit monochrome STN panel. */
                cpl = (config->ppl / 4U) - 1U;
            }
        }
        else
        {
            /* Color STN panel. */
            cpl = ((config->ppl * 3U) / 8U) - 1U;
        }
    }

    *divider |= (LCD_POL_CPL(cpl) | LCD_POL_PCD(pcd));

    return true;
}

/*!
 * brief Initialize the LCD module.
 *
 * param base LCD peripheral base address.
 * param config Pointer to configuration structure, see to ref lcdc_config_t.
 * param srcClock_Hz The LCD input clock (LCDCLK) frequency in Hz.
 * retval kStatus_Success LCD is initialized successfully.
 * retval kStatus_InvalidArgument Initlialize failed because of invalid argument.
 */
status_t LCDC_Init(LCD_Type *base, const lcdc_config_t *config, uint32_t srcClock_Hz)
{
    assert(NULL != config);
    assert(0U != srcClock_Hz);
    assert((config->ppl & 0xFU) == 0U);
    assert((config->upperPanelAddr & 0x07U) == 0U);
    assert((config->lowerPanelAddr & 0x07U) == 0U);

    uint32_t reg;
    uint32_t divider;
    uint32_t instance;

    /* Verify the clock here. */
    if (!LCDC_GetClockDivider(config, srcClock_Hz, &divider))
    {
        return kStatus_InvalidArgument;
    }

    instance = LCDC_GetInstance(base);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_EnableClock(s_lcdClocks[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
    /* Reset the module. */
    RESET_PeripheralReset(s_lcdResets[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */

    /* Set register CTRL. */
    reg = base->CTRL & (LCD_CTRL_LCDVCOMP_MASK | LCD_CTRL_WATERMARK_MASK);
    reg |= (uint32_t)(config->dataFormat) | (uint32_t)(config->display) | LCD_CTRL_LCDBPP(config->bpp);

    if (config->swapRedBlue)
    {
        reg |= LCD_CTRL_BGR_MASK;
    }

    base->CTRL = reg;

    /* Clean pending interrupts and disable all interrupts. */
    base->INTCLR      = LCDC_NORMAL_INT_MASK;
    base->CRSR_INTCLR = LCDC_CURSOR_INT_MASK;
    base->INTMSK      = 0U;
    base->CRSR_INTMSK = 0U;

    /* Configure timing. */
    base->TIMH = LCD_TIMH_PPL(((uint32_t)config->ppl / 16U) - 1U) | LCD_TIMH_HSW((uint32_t)config->hsw - 1U) |
                 LCD_TIMH_HFP((uint32_t)config->hfp - 1U) | LCD_TIMH_HBP((uint32_t)config->hbp - 1U);

    base->TIMV = LCD_TIMV_LPP((uint32_t)config->lpp - 1U) | LCD_TIMV_VSW((uint32_t)config->vsw - 1U) |
                 LCD_TIMV_VFP((uint32_t)config->vfp - 1U) | LCD_TIMV_VBP((uint32_t)config->vbp - 1U);

    base->POL = (uint32_t)(config->polarityFlags) | LCD_POL_ACB((uint32_t)config->acBiasFreq - 1U) | divider;

    /* Line end configuration. */
    if (config->enableLineEnd)
    {
        base->LE = LCD_LE_LED((uint32_t)config->lineEndDelay - 1U) | LCD_LE_LEE_MASK;
    }
    else
    {
        base->LE = 0U;
    }

    /* Set panel frame base address. */
    base->UPBASE = config->upperPanelAddr;
    base->LPBASE = config->lowerPanelAddr;

    return kStatus_Success;
}

/*!
 * brief Deinitialize the LCD module.
 *
 * param base LCD peripheral base address.
 */
void LCDC_Deinit(LCD_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_EnableClock(s_lcdClocks[LCDC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Gets default pre-defined settings for initial configuration.
 *
 * This function initializes the configuration structure. The default values are:
 *
   code
    config->panelClock_Hz = 0U;
    config->ppl = 0U;
    config->hsw = 0U;
    config->hfp = 0U;
    config->hbp = 0U;
    config->lpp = 0U;
    config->vsw = 0U;
    config->vfp = 0U;
    config->vbp = 0U;
    config->acBiasFreq = 1U;
    config->polarityFlags = 0U;
    config->enableLineEnd = false;
    config->lineEndDelay = 0U;
    config->upperPanelAddr = 0U;
    config->lowerPanelAddr = 0U;
    config->bpp = kLCDC_1BPP;
    config->dataFormat = kLCDC_LittleEndian;
    config->swapRedBlue = false;
    config->display = kLCDC_DisplayTFT;
   endcode
 *
 * param config Pointer to configuration structure.
 */
void LCDC_GetDefaultConfig(lcdc_config_t *config)
{
    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->panelClock_Hz  = 0U;
    config->ppl            = 0U;
    config->hsw            = 0U;
    config->hfp            = 0U;
    config->hbp            = 0U;
    config->lpp            = 0U;
    config->vsw            = 0U;
    config->vfp            = 0U;
    config->vbp            = 0U;
    config->acBiasFreq     = 1U;
    config->polarityFlags  = 0U;
    config->enableLineEnd  = false;
    config->lineEndDelay   = 0U;
    config->upperPanelAddr = 0U;
    config->lowerPanelAddr = 0U;
    config->bpp            = kLCDC_1BPP;
    config->dataFormat     = kLCDC_LittleEndian;
    config->swapRedBlue    = false;
    config->display        = kLCDC_DisplayTFT;
}

/*!
 * brief Sets panel frame base address
 *
 * param base LCD peripheral base address.
 * param panel Which panel to set.
 * param addr Frame base address, must be doubleword(64-bit) aligned.
 */
void LCDC_SetPanelAddr(LCD_Type *base, lcdc_panel_t panel, uint32_t addr)
{
    /* The base address must be doubleword aligned. */
    assert((addr & 0x07U) == 0U);

    if (kLCDC_UpperPanel == panel)
    {
        base->UPBASE = addr;
    }
    else
    {
        base->LPBASE = addr;
    }
}

/*!
 * brief Sets palette
 *
 * param base LCD peripheral base address.
 * param palette Pointer to the palette array.
 * param count_words Length of the palette array to set (how many words), it should
 * not be larger than LCDC_PALETTE_SIZE_WORDS.
 */
void LCDC_SetPalette(LCD_Type *base, const uint32_t *palette, uint8_t count_words)
{
    assert(count_words <= ARRAY_SIZE(base->PAL));

    uint32_t i;

    for (i = 0; i < count_words; i++)
    {
        base->PAL[i] = palette[i];
    }
}

/*!
 * brief Enable LCD interrupts.
 *
 * Example to enable LCD base address update interrupt and vertical compare
 * interrupt:
 *
 * code
   LCDC_EnableInterrupts(LCD, kLCDC_BaseAddrUpdateInterrupt | kLCDC_VerticalCompareInterrupt);
   endcode
 *
 * param base LCD peripheral base address.
 * param mask Interrupts to enable, it is OR'ed value of ref _lcdc_interrupts.
 */
void LCDC_EnableInterrupts(LCD_Type *base, uint32_t mask)
{
    uint32_t reg;

    reg = mask & LCDC_CURSOR_INT_MASK;
    if (0U != reg)
    {
        base->CRSR_INTMSK |= reg;
    }

    reg = mask & LCDC_NORMAL_INT_MASK;
    if (0U != reg)
    {
        base->INTMSK |= reg;
    }
}

/*!
 * brief Disable LCD interrupts.
 *
 * Example to disable LCD base address update interrupt and vertical compare
 * interrupt:
 *
 * code
   LCDC_DisableInterrupts(LCD, kLCDC_BaseAddrUpdateInterrupt | kLCDC_VerticalCompareInterrupt);
   endcode
 *
 * param base LCD peripheral base address.
 * param mask Interrupts to disable, it is OR'ed value of ref _lcdc_interrupts.
 */
void LCDC_DisableInterrupts(LCD_Type *base, uint32_t mask)
{
    uint32_t reg;

    reg = mask & LCDC_CURSOR_INT_MASK;
    if (0U != reg)
    {
        base->CRSR_INTMSK &= ~reg;
    }

    reg = mask & LCDC_NORMAL_INT_MASK;
    if (0U != reg)
    {
        base->INTMSK &= ~reg;
    }
}

/*!
 * brief Get LCD interrupt pending status.
 *
 * Example:
 *
 * code
   uint32_t status;

   status = LCDC_GetInterruptsPendingStatus(LCD);

   if (kLCDC_BaseAddrUpdateInterrupt & status)
   {
       LCD base address update interrupt occurred.
   }

   if (kLCDC_VerticalCompareInterrupt & status)
   {
       LCD vertical compare interrupt occurred.
   }
   endcode
 *
 * param base LCD peripheral base address.
 * return Interrupts pending status, it is OR'ed value of ref _lcdc_interrupts.
 */
uint32_t LCDC_GetInterruptsPendingStatus(LCD_Type *base)
{
    uint32_t reg;

    reg = base->CRSR_INTRAW;
    reg |= base->INTRAW;

    return reg;
}

/*!
 * brief Get LCD enabled interrupt pending status.
 *
 * This function is similar with ref LCDC_GetInterruptsPendingStatus, the only
 * difference is, this function only returns the pending status of the
 * interrupts that have been enabled using ref LCDC_EnableInterrupts.
 *
 * param base LCD peripheral base address.
 * return Interrupts pending status, it is OR'ed value of ref _lcdc_interrupts.
 */
uint32_t LCDC_GetEnabledInterruptsPendingStatus(LCD_Type *base)
{
    uint32_t reg;

    reg = base->CRSR_INTSTAT;
    reg |= base->INTSTAT;

    return reg;
}

/*!
 * brief Clear LCD interrupts pending status.
 *
 * Example to clear LCD base address update interrupt and vertical compare
 * interrupt pending status:
 *
 * code
   LCDC_ClearInterruptsStatus(LCD, kLCDC_BaseAddrUpdateInterrupt | kLCDC_VerticalCompareInterrupt);
   endcode
 *
 * param base LCD peripheral base address.
 * param mask Interrupts to disable, it is OR'ed value of ref _lcdc_interrupts.
 */
void LCDC_ClearInterruptsStatus(LCD_Type *base, uint32_t mask)
{
    uint32_t reg;

    reg = mask & LCDC_CURSOR_INT_MASK;
    if (0U != reg)
    {
        base->CRSR_INTCLR = reg;
    }

    reg = mask & LCDC_NORMAL_INT_MASK;
    if (0U != reg)
    {
        base->INTCLR = reg;
    }
}

/*!
 * brief Set the hardware cursor configuration
 *
 * This function should be called before enabling the hardware cursor.
 * It supports initializing multiple cursor images at a time when using
 * 32x32 pixels cursor.
 *
 * For example:
 *
 * code
   uint32_t cursor0Img[LCDC_CURSOR_IMG_32X32_WORDS] = {...};
   uint32_t cursor2Img[LCDC_CURSOR_IMG_32X32_WORDS] = {...};

   lcdc_cursor_config_t cursorConfig;

   LCDC_CursorGetDefaultConfig(&cursorConfig);

   cursorConfig.image[0] = cursor0Img;
   cursorConfig.image[2] = cursor2Img;

   LCDC_SetCursorConfig(LCD, &cursorConfig);

   LCDC_ChooseCursor(LCD, 0);
   LCDC_SetCursorPosition(LCD, 0, 0);

   LCDC_EnableCursor(LCD);
   endcode
 *
 * In this example, cursor 0 and cursor 2 image data are initialized, but cursor 1
 * and cursor 3 image data are not initialized because image[1] and image[2] are
 * all NULL. With this, application could initializes all cursor images it will
 * use at the beginning and call ref LCDC_SetCursorImage directly to display the
 * one which it needs.
 *
 * param base LCD peripheral base address.
 * param config Pointer to the hardware cursor configuration structure.
 */
void LCDC_SetCursorConfig(LCD_Type *base, const lcdc_cursor_config_t *config)
{
    assert(NULL != config);

    uint8_t i;

    base->CRSR_CFG = LCD_CRSR_CFG_CRSRSIZE(config->size) | LCD_CRSR_CFG_FRAMESYNC(config->syncMode);

    /* Set position. */
    LCDC_SetCursorPosition(base, 0, 0);

    /* Palette. */
    base->CRSR_PAL0 = ((uint32_t)config->palette0.red << LCD_CRSR_PAL0_RED_SHIFT) |
                      ((uint32_t)config->palette0.blue << LCD_CRSR_PAL0_BLUE_SHIFT) |
                      ((uint32_t)config->palette0.green << LCD_CRSR_PAL0_GREEN_SHIFT);
    base->CRSR_PAL1 = ((uint32_t)config->palette1.red << LCD_CRSR_PAL1_RED_SHIFT) |
                      ((uint32_t)config->palette1.blue << LCD_CRSR_PAL1_BLUE_SHIFT) |
                      ((uint32_t)config->palette1.green << LCD_CRSR_PAL1_GREEN_SHIFT);

    /* Image of cursors. */
    if (kLCDC_CursorSize64 == config->size)
    {
        assert(NULL != config->image[0]);
        LCDC_SetCursorImage(base, config->size, 0, config->image[0]);
    }
    else
    {
        for (i = 0; i < LCDC_CURSOR_COUNT; i++)
        {
            if (NULL != config->image[i])
            {
                LCDC_SetCursorImage(base, config->size, i, config->image[i]);
            }
        }
    }
}

/*!
 * brief Get the hardware cursor default configuration
 *
 * The default configuration values are:
 *
 * code
    config->size = kLCDC_CursorSize32;
    config->syncMode = kLCDC_CursorAsync;
    config->palette0.red = 0U;
    config->palette0.green = 0U;
    config->palette0.blue = 0U;
    config->palette1.red = 255U;
    config->palette1.green = 255U;
    config->palette1.blue = 255U;
    config->image[0] = (uint32_t *)0;
    config->image[1] = (uint32_t *)0;
    config->image[2] = (uint32_t *)0;
    config->image[3] = (uint32_t *)0;
   endcode
 *
 * param config Pointer to the hardware cursor configuration structure.
 */
void LCDC_CursorGetDefaultConfig(lcdc_cursor_config_t *config)
{
    uint32_t i;

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->size           = kLCDC_CursorSize32;
    config->syncMode       = kLCDC_CursorAsync;
    config->palette0.red   = 0U;
    config->palette0.green = 0U;
    config->palette0.blue  = 0U;
    config->palette1.red   = 255U;
    config->palette1.green = 255U;
    config->palette1.blue  = 255U;

    for (i = 0; i < LCDC_CURSOR_COUNT; i++)
    {
        config->image[i] = (uint32_t *)0;
    }
}

/*!
 * brief Set the position of cursor
 *
 * When synchronization mode is ref kLCDC_CursorSync, position change effects
 * in the next frame. When synchronization mode is ref kLCDC_CursorAsync,
 * position change effects immediately.
 *
 * param base LCD peripheral base address.
 * param positionX X ordinate of the cursor top-left measured in pixels
 * param positionY Y ordinate of the cursor top-left measured in pixels
 */
void LCDC_SetCursorPosition(LCD_Type *base, int32_t positionX, int32_t positionY)
{
    uint32_t clipX;
    uint32_t clipY;

    if (positionX < 0)
    {
        clipX     = (uint32_t)(-positionX);
        positionX = 0;

        /* If clip value too large, set to the max value. */
        if (clipX > LCDC_CLIP_MAX)
        {
            clipX = LCDC_CLIP_MAX;
        }
    }
    else
    {
        clipX = 0U;
    }

    if (positionY < 0)
    {
        clipY     = (uint32_t)-positionY;
        positionY = 0;

        /* If clip value too large, set to the max value. */
        if (clipY > LCDC_CLIP_MAX)
        {
            clipY = LCDC_CLIP_MAX;
        }
    }
    else
    {
        clipY = 0U;
    }

    base->CRSR_CLIP = LCD_CRSR_CLIP_CRSRCLIPX(clipX) | LCD_CRSR_CLIP_CRSRCLIPY(clipY);
    base->CRSR_XY   = LCD_CRSR_XY_CRSRX(positionX) | LCD_CRSR_XY_CRSRY(positionY);
}

/*!
 * brief Set the cursor image.
 *
 * The interrupt ref kLCDC_CursorInterrupt indicates that last cursor pixel is
 * displayed. When the hardware cursor is enabled,
 *
 * param base LCD peripheral base address.
 * param size The cursor size.
 * param index Index of the cursor to set when using 32x32 cursor.
 * param image Pointer to the cursor image. When using 32x32 cursor, the image
 * size should be LCDC_CURSOR_IMG_32X32_WORDS. When using 64x64 cursor, the image
 * size should be LCDC_CURSOR_IMG_64X64_WORDS.
 */
void LCDC_SetCursorImage(LCD_Type *base, lcdc_cursor_size_t size, uint8_t index, const uint32_t *image)
{
    uint32_t regStart;
    uint32_t i;
    uint32_t len;

    if (kLCDC_CursorSize64 == size)
    {
        regStart = 0U;
        len      = LCDC_CURSOR_IMG_64X64_WORDS;
    }
    else
    {
        regStart = (uint32_t)index * LCDC_CURSOR_IMG_32X32_WORDS;
        len      = LCDC_CURSOR_IMG_32X32_WORDS;
    }

    for (i = 0U; i < len; i++)
    {
        base->CRSR_IMG[regStart + i] = image[i];
    }
}
