/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_epdc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.epdc"
#endif

#if defined(EPDC_RSTS)
#define EPDC_RESETS_ARRAY EPDC_RSTS
#endif

typedef union
{
    epdc_fifo_config_t _fifo_config;                 /* 32-bit */
    epdc_autowave_map_t _autowave_map;               /* 32-bit */
    epdc_gpio_config_t _gpio_config;                 /* 32-bit */
    epdc_pigeon_cycle_config_t _pigeon_cycle_config; /* 64-bit */
    epdc_sd_config_t _source_driver_config;          /* 64-bit */
    epdc_pigeon_config_t _pigeon_config;             /* 96-bit */
    epdc_update_config_t _update_config;             /* 192-bit */
    uint32_t _u32;
    uint64_t _u64;
} epdc_reg_convert_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! brief Pointers to EPDC bases for each instance. */
static EPDC_Type *const s_epdcBases[] = EPDC_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! brief Pointers to EPDC clocks for each EPDC submodule. */
static const clock_ip_name_t s_epdcClocks[] = EPDC_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if defined(EPDC_RESETS_ARRAY)
/* Reset array */
static const reset_ip_name_t s_epdcResets[] = EPDC_RESETS_ARRAY;
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t EPDC_GetInstance(EPDC_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_epdcBases); instance++)
    {
        if (s_epdcBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_epdcBases));

    return instance;
}

/*!
 * brief Resets the EPDC to initialized state.
 *
 * param base EPDC base pointer
 */
void EPDC_ResetToInit(EPDC_Type *base)
{
    /* Set software reset. */
    base->CTRL.SET = EPDC_CTRL_SFTRST_MASK;
    /* Wait for clock gate to set. */
    while ((base->CTRL.RW & EPDC_CTRL_CLKGATE_MASK) == 0U)
    {
    }
    /* Clear software reset and clock gate. */
    base->CTRL.CLR = (EPDC_CTRL_SFTRST_MASK | EPDC_CTRL_CLKGATE_MASK);
    /* Wait for these bits to be cleared */
    while ((base->CTRL.RW & (EPDC_CTRL_CLKGATE_MASK | EPDC_CTRL_SFTRST_MASK)) != 0U)
    {
    }
}

/*!
 * brief Initializes the EPDC.
 *
 * This function enables the EPDC peripheral clock, and resets the EPDC registers
 * to default status.
 *
 * param base EPDC base pointer
 */
void EPDC_Init(EPDC_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_EnableClock(s_epdcClocks[EPDC_GetInstance(base)]);
#endif

#if defined(EPDC_RESETS_ARRAY)
    RESET_ReleasePeripheralReset(s_epdcResets[EPDC_GetInstance(base)]);
#endif

    EPDC_ResetToInit(base);
}

/*!
 * brief De-initializes the EPDC.
 *
 * This function disables the EPDC peripheral clock.
 *
 * param base EPDC base pointer
 */
void EPDC_Deinit(EPDC_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_DisableClock(s_epdcClocks[EPDC_GetInstance(base)]);
#endif
}

/*!
 * brief Initializes the EPDC dispaly parameters.
 *
 * param base EPDC base pointer
 * param config Pointer to EPDC display configuration structure
 * retval kStatus_Success Successfully initialized the display parameters
 * retval kStatus_InvalidArgument parameter(s) is(are) not valid
 */
status_t EPDC_InitDisplay(EPDC_Type *base, const epdc_display_config_t *config)
{
    assert(config != NULL);

    /* waveform address and working buffer address must be 64-bit aligned. */
    if (((config->waveformAddr & 0x3FUL) != 0U) || ((config->wbAddr & 0x3FUL) != 0U))
    {
        return kStatus_InvalidArgument;
    }

    base->WVADDR    = config->waveformAddr;
    base->WB_ADDR   = config->wbAddr;
    base->TEMP      = config->tempIdx;
    base->RES       = (uint32_t)config->resX | ((uint32_t)config->resY << 16U);
    base->FORMAT.RW = EPDC_FORMAT_DEFAULT_TFT_PIXEL((uint32_t)config->defaltTftPixelValue) |
                      EPDC_FORMAT_WB_TYPE((uint32_t)config->wbType) |
                      EPDC_FORMAT_TFT_PIXEL_FORMAT((uint32_t)config->pixelFormat);
    base->CTRL.RW = (base->CTRL.RW & ~(EPDC_CTRL_UPD_DATA_SWIZZLE_MASK | EPDC_CTRL_LUT_DATA_SWIZZLE_MASK)) |
                    EPDC_CTRL_UPD_DATA_SWIZZLE((uint32_t)config->updSwizzle) |
                    EPDC_CTRL_LUT_DATA_SWIZZLE((uint32_t)config->lutSwizzle);

    return kStatus_Success;
}

/*!
 * brief Configures the FIFO control parameters, including panic function and pre-fill level.
 *
 * param base EPDC base pointer
 * param config Pointer to EPDC FIFO control configuration structure
 * retval kStatus_Success Successfully configured the FIFO
 * retval kStatus_InvalidArgument parameter(s) is(are) not valid
 */
status_t EPDC_ConfigFifo(EPDC_Type *base, const epdc_fifo_config_t *config)
{
    assert(config != NULL);
    if (config->lowLevel >= config->highLevel)
    {
        return kStatus_InvalidArgument;
    }

    epdc_reg_convert_t pid;

    pid._fifo_config  = *config;
    base->FIFOCTRL.RW = pid._u32;

    return kStatus_Success;
}

/*!
 * brief Configures the TCE parameters before initiating the panel update.
 *
 * note Make sure to configure the display parameters by @ref EPDC_InitDisplay before calling this API.
 *
 * param base EPDC base pointer
 * param config Pointer to EPDC TCE control configuration structure
 * retval kStatus_Success Successfully configured the TCE
 * retval kStatus_InvalidArgument parameter(s) is(are) not valid
 */
status_t EPDC_ConfigTCE(EPDC_Type *base, const epdc_tce_config_t *config)
{
    assert(config != NULL);

    uint16_t resX = (uint16_t)((base->RES & EPDC_RES_HORIZONTAL_MASK) >> EPDC_RES_HORIZONTAL_SHIFT);

    /* The horizontal resolution must be evenly divided by the count of souce sriver control enable signal. */
    if ((resX % config->sdConfig.sdceCount) != 0U)
    {
        return kStatus_InvalidArgument;
    }

    if (config->sdConfig.pixelReverse > (uint32_t)kEPDC_DataReversed)
    {
        return kStatus_InvalidArgument;
    }

    epdc_reg_convert_t pid;
    pid._source_driver_config = config->sdConfig;
    uint8_t piexelPerClk      = 2U; /* Default is 4pixel/clock, 2^2. */

    base->WB_ADDR_TCE = config->tceWbAddr;
    base->TCE_CTRL.RW = EPDC_TCE_CTRL_VSCAN_HOLDOFF((uint32_t)config->vscanHoldoff) |
                        EPDC_TCE_CTRL_VCOM_VAL((uint32_t)config->vcomVal) |
                        EPDC_TCE_CTRL_VCOM_MODE((uint32_t)config->vcomMode) |
                        ((uint32_t)config->outMode << EPDC_TCE_CTRL_SDDO_WIDTH_SHIFT) |
                        EPDC_TCE_CTRL_SCAN_DIR_0((uint32_t)config->upperScanDirection) |
                        EPDC_TCE_CTRL_SCAN_DIR_1((uint32_t)config->lowerScanDirection);
    base->TCE_SDCFG.RW = ((uint32_t)pid._u64 & ~EPDC_TCE_SDCFG_PIXELS_PER_CE_MASK) |
                         (EPDC_TCE_SDCFG_PIXELS_PER_CE(resX / config->sdConfig.sdceCount));
    base->TCE_GDCFG.RW = EPDC_TCE_GDCFG_GDSP_MODE((uint32_t)config->gdConfig.gdspMode) |
                         EPDC_TCE_GDCFG_GDOE_MODE((uint32_t)config->gdConfig.gdoeMode) |
                         EPDC_TCE_GDCFG_GDRL((uint32_t)config->gdConfig.shiftDir);
    base->TCE_HSCAN1.RW = ((uint32_t)config->scanConfig.lineSync << 16U) | (uint32_t)config->scanConfig.lineSync;
    base->TCE_HSCAN2.RW = ((uint32_t)config->scanConfig.lineEnd << 16U) | (uint32_t)config->scanConfig.lineBegin;
    base->TCE_VSCAN.RW  = ((uint32_t)config->scanConfig.frameEnd << 16U) |
                         ((uint32_t)config->scanConfig.frameBegin << 8U) | (uint32_t)config->scanConfig.frameSync;
    base->TCE_OE.RW       = (uint32_t)(pid._u64 >> 32U);
    base->TCE_POLARITY.RW = ((uint32_t)pid._u64 & 0x7UL) |
                            EPDC_TCE_POLARITY_GDOE_POL((uint32_t)config->gdConfig.gdoePol) |
                            EPDC_TCE_POLARITY_GDSP_POL((uint32_t)config->gdConfig.gdspPol);
    base->TCE_TIMING1.RW = ((uint32_t)pid._u64 >> 3U) & 0x3FUL;
    base->TCE_TIMING2.RW = ((uint32_t)config->gdConfig.gdClkHigh << 16U) | (uint32_t)config->gdConfig.gdspOffset;
    base->TCE_TIMING3.RW = ((uint32_t)config->gdConfig.gdoeOffset << 16U) | (uint32_t)config->gdConfig.gdClkOffset;

    /* Calculate the pixel per clock value. */
    if ((base->TCE_CTRL.RW & EPDC_TCE_CTRL_DDR_MODE_MASK) != 0U)
    {
        piexelPerClk += 1U;
    }
    if ((base->TCE_CTRL.RW & EPDC_TCE_CTRL_SDDO_WIDTH_MASK) != 0U)
    {
        piexelPerClk += 1U;
    }
    if ((base->TCE_CTRL.RW & EPDC_TCE_CTRL_LVDS_MODE_MASK) != 0U)
    {
        piexelPerClk -= 1U;
    }
    if ((base->TCE_CTRL.RW & EPDC_TCE_CTRL_DUAL_SCAN_MASK) != 0U)
    {
        piexelPerClk -= 1U;
    }
    if (((base->FORMAT.RW & EPDC_FORMAT_TFT_PIXEL_FORMAT_MASK) >> EPDC_FORMAT_TFT_PIXEL_FORMAT_SHIFT) >=
        (uint32_t)kEPDC_Pixel4bit)
    {
        piexelPerClk -= 1U;
    }

    /* Pixel clock cannot be larger than 8. */
    if (piexelPerClk > 3U)
    {
        return kStatus_InvalidArgument;
    }

    base->TCE_CTRL.RW =
        (base->TCE_CTRL.RW & ~EPDC_TCE_CTRL_PIXELS_PER_SDCLK_MASK) | EPDC_TCE_CTRL_PIXELS_PER_SDCLK(piexelPerClk);

    return kStatus_Success;
}

/*!
 * brief Configures the signal output format for signals that support pigeon mode.
 *
 * note Refer to the soc reference manual to check the configurable pigeon signal.
 *       No need to call this API if not using the pigeon mode.
 *
 * param base EPDC base pointer
 * param signalNum The number of the pigeon signal to be configured
 * param config Pointer to EPDC pigeon mode configuration structure
 */
void EPDC_ConfigPigeon(EPDC_Type *base, uint8_t signalNum, const epdc_pigeon_config_t *config)
{
    assert(config != NULL);
    assert(signalNum <= 16U);

    epdc_reg_convert_t pid;
    pid._pigeon_config = *config;

    uint32_t dataAddr = (uint32_t) & (pid._u32);

    base->PIGEON_X[signalNum].PIGEON_0 = *(uint32_t *)dataAddr;
    dataAddr += 4U;
    base->PIGEON_X[signalNum].PIGEON_1 = *(uint32_t *)dataAddr;
    dataAddr += 4U;
    base->PIGEON_X[signalNum].PIGEON_2 = *(uint32_t *)dataAddr;
}

/*!
 * brief Configures the cycle's period.
 *
 * When selecting any of the pclk/line/frame cycle as global counter, call this API forst to set the proper cycle
 * period. The configuraton is shared for all pigeon signals.
 *
 * param base EPDC base pointer
 * param config Pointer to EPDC pigeon mode cycle configuration structure
 */
void EPDC_ConfigPigeonCycle(EPDC_Type *base, const epdc_pigeon_cycle_config_t *config)
{
    assert(config != NULL);

    epdc_reg_convert_t pid;
    pid._pigeon_cycle_config = *config;

    base->PIGEON_CTRL0.RW = (uint32_t)pid._u64;
    base->PIGEON_CTRL1.RW = (uint32_t)(pid._u64 >> 32U);
}

/*!
 * brief Gets the number of the next available LUT.
 *
 * param base EPDC base pointer
 * param lutNum Pointer to LUT number
 * retval kStatus_Success Successfully got the LUT number
 * retval kStatus_Fail no valid LUT present, all LUTs are busy
 */
status_t EPDC_GetNextAvailableLUT(EPDC_Type *base, uint8_t *lutNum)
{
    assert(lutNum != NULL);
    if ((base->STATUS_NEXTLUT & EPDC_STATUS_NEXTLUT_NEXT_LUT_VALID_MASK) == 0U)
    {
        /* No idle LUT available */
        return kStatus_Fail;
    }

    *lutNum =
        (uint8_t)((base->STATUS_NEXTLUT & EPDC_STATUS_NEXTLUT_NEXT_LUT_MASK) >> EPDC_STATUS_NEXTLUT_NEXT_LUT_SHIFT);
    return kStatus_Success;
}

/*!
 * brief Initiates a panel display update.
 *
 * param base EPDC base pointer
 * param config Pointer to update configuration structure
 * retval kStatus_Success Successfully initiated an update
 * retval kStatus_Fail update failed due to busy working buffer or LUT
 * retval kStatus_InvalidArgument parameter(s) is(are) not valid
 */
status_t EPDC_UpdateDisplay(EPDC_Type *base, epdc_update_config_t *config)
{
    assert(config != NULL);

    uint32_t updateBits =
        config->width * config->height * 2U *
        (((base->FORMAT.RW & EPDC_FORMAT_TFT_PIXEL_FORMAT_MASK) >> (EPDC_FORMAT_TFT_PIXEL_FORMAT_SHIFT + 1U)) + 1U);
    /* If stride disabled, the buffer address must start and end on 8 byte address. */
    if ((((config->bufferAddress & 0x3FUL) != 0U) || ((updateBits & 0x3FUL) != 0U)) && (config->stride == 0U))
    {
        return kStatus_InvalidArgument;
    }

    epdc_reg_convert_t pid;
    pid._update_config = *config;

    uint32_t dataAddr = (uint32_t) & (pid._u32);

    base->UPD_ADDR = *(uint32_t *)dataAddr;
    dataAddr += 4U;
    base->UPD_STRIDE = *(uint32_t *)dataAddr;
    dataAddr += 4U;
    base->UPD_CORD = *(uint32_t *)dataAddr;
    dataAddr += 4U;
    base->UPD_SIZE = *(uint32_t *)dataAddr;
    dataAddr += 4U;
    base->UPD_FIXED.RW = *(uint32_t *)dataAddr;
    dataAddr += 4U;

    /* Make sure the working buffer and lookup table are not busy. */
    if ((base->STATUS.RW & (EPDC_STATUS_WB_BUSY_MASK | EPDC_STATUS_LUTS_BUSY_MASK)) != 0U)
    {
        return kStatus_Fail;
    }
    base->UPD_CTRL.RW = *(uint32_t *)dataAddr;

    return kStatus_Success;
}

/*!
 * brief Sets one map between a grey level and its waveform mode.
 *
 * Call this API multiple times until all the maps are set.
 *
 * param base EPDC base pointer
 * param config Pointer to autowave configuration structure
 */
void EPDC_SetAutowaveMap(EPDC_Type *base, const epdc_autowave_map_t *config)
{
    assert(config != NULL);

    epdc_reg_convert_t pid;
    pid._autowave_map = *config;

    base->AUTOWV_LUT = pid._u32;
}

/*!
 * brief Sets the GPIO output value for BDR(0,1), PWR_CTRL(0,1,2,3), PWR_COM and PWR_WAKE pins.
 *
 * param base EPDC base pointer
 * param config Pointer to GPIO configuration structure
 */
void EPDC_SetGpioOutput(EPDC_Type *base, const epdc_gpio_config_t *config)
{
    assert(config != NULL);

    epdc_reg_convert_t pid;
    pid._gpio_config = *config;

    base->GPIO.RW = pid._u32;
}

/*!
 * brief Gets the status of the collision
 *
 * param base EPDC base pointer
 * param status Pointer to collision status structure
 */
void EPDC_GetCollisionStatus(EPDC_Type *base, epdc_collision_status_t *status)
{
    assert(NULL != status);
    /* Initializes the status structure to zero. */
    (void)memset(status, 0, sizeof(*status));

    status->minX    = (uint16_t)base->UPD_COL_CORD;
    status->minY    = (uint16_t)(base->UPD_COL_CORD >> 16U);
    status->width   = (uint16_t)base->UPD_COL_SIZE;
    status->height  = (uint16_t)(base->UPD_COL_SIZE >> 16U);
    status->lutlist = (uint64_t)(base->STATUS_COL1.RW) | ((uint64_t)(base->STATUS_COL2.RW) << 32U);
}
