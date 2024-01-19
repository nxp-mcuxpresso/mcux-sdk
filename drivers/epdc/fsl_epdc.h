/*
 * Copyright 2021,2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_EPDC_H_
#define FSL_EPDC_H_

#include "fsl_common.h"

/*!
 * @addtogroup epdc_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
#define FSL_EPDC_DRIVER_VERSION (MAKE_VERSION(2, 0, 2))
/*! @} */

/* Definitions for interrupts and status. */

/*!
 * @brief EPDC non LUT complete interrupts.
 * @note These enumerations are meant to be OR'd together to form a bit mask.
 *       EPDC also has 64 independent LUT complete interrupts.
 */
enum _epdc_interrupt_enable
{
    kEPDC_WbCompleteInterruptEnable           = 1UL << 0U, /*!< Working buffer complete interrupt. */
    kEPDC_LutCollisionDetetionInterruptEnable = 1UL << 1U, /*!< Collision detection interrupt for all LUTs. */
    kEPDC_FifoUnderRunInterruptEnable         = 1UL << 2U, /*!< Pixel FIFO underrun interrupt. */
    kEPDC_FrameCompleteInterruptEnable =
        1UL << 3U, /*!< Current frame is complete and in vertical blanking period interrupt. */
    kEPDC_AxiBusErrorInterruptEnable    = 1UL << 4U, /*!< AXI bus error occur interrupt. */
    kEPDC_TceIdleInterruptEnable        = 1UL << 5U, /*!< TCE finished frame scan and in isle state interrupt. */
    kEPDC_UpdateCompleteInterruptEnable = 1UL << 6U, /*!< Update complete interrupt.TODO */
    kEPDC_PowerInterruptEnable          = 1UL << 7U, /*!< Power interrupt.TODO */
};

/*!
 * @brief EPDC non LUT complete status flags.
 * @note These enumerations are meant to be OR'd together to form a bit mask.
 *       EPDC also has 64 independent LUT complete interrupt status.
 */
enum _epdc_status_flags
{
    kEPDC_WbBusyFlag =
        EPDC_STATUS_WB_BUSY_MASK, /*!< Working buffer process is busy and cannot accept new update requests. */
    kEPDC_LutBusyFlag = EPDC_STATUS_LUTS_BUSY_MASK, /*!< All the LUTs ary busy. */
    kEPDC_LutUnderrunFlag =
        EPDC_STATUS_LUTS_UNDERRUN_MASK, /*!< Not enough time for active luts read during blanking period. */
    kEPDC_UpdateBufferVoidFlag = EPDC_STATUS_UPD_VOID_MASK, /*!< Update buffer is void indicating no pixels need
                                                               updating or all pixels were collided. */
    kEPDC_WbCompleteInterruptFlag           = 1UL << 4U,    /*!< Working buffer complete interrupt flag. */
    kEPDC_LutCollisionDetetionInterruptFlag = 1UL << 5U,    /*!< Collision detection interrupt flag for all LUTs. */
    kEPDC_FifoUnderRunInterruptFlag         = 1UL << 6U,    /*!< Pixel FIFO underrun interrupt flag. */
    kEPDC_FrameCompleteInterruptFlag =
        1UL << 7U, /*!< Interrupt flag indicating current frame is complete and in vertical blanking period. */
    kEPDC_AxiBusErrorInterruptFlag = 1UL << 8U, /*!< AXI bus error occur interrupt flag. */
    kEPDC_TceIdleInterruptFlag =
        1UL << 9U, /*!< Interrupt flag indicationg TCE has finished frame scan and in isle state. */
    kEPDC_UpdateCompleteInterruptFlag = 1UL << 10U, /*!< Update complete interrupt flag.TODO */
    kEPDC_PowerInterruptFlag          = 1UL << 11U, /*!< Power interrupt flag.TODO */
};

/* Definitions for display parameters. */

/*! @brief EPDC TFT pixel format. */
typedef enum _epdc_pixel_format
{
    kEPDC_Pixel2bit     = 0x0U,
    kEPDC_Pixel2bitVcom = 0x1U,
    kEPDC_Pixel4bit     = 0x2U,
    kEPDC_Pixel4bitVcom = 0x3U,
} epdc_pixel_format_t;

/*! @brief EPDC working buffer type. */
typedef enum _epdc_wb_type
{
    kEPDC_WbInternal = 0x0U, /*!< Internal Working Buffer written by EPDC itself. */
    kEPDC_WbWaveform = 0x1U, /*!< Working buffer is actually holding waveform. */
    kEPDC_Wb16bit    = 0x2U, /*!< 16bit working buffer written by PXP or CPU. */
    kEPDC_Wb32bit    = 0x3U, /*!< 32bit working buffer written by PXP or CPU. */
} epdc_wb_type_t;

/*! @brief EPDC data swizzle type for update date or LUT data. */
typedef enum _epdc_data_swizzle
{
    kEPDC_NoSwap             = 0x0U, /*!< Little endian, no byte swapping. */
    kEPDC_SwapAllBytes       = 0x1U, /*!< Big endian, byte 0|1|2|3 -> 3|2|1|0. */
    kEPDC_SwapHalfWord       = 0x2U, /*!< byte 0|1|2|3 -> 2|3|0|1. */
    kEPDC_SwapWithinHalfWord = 0x3U, /*!< byte 0|1|2|3 -> 1|0|3|2. */
} epdc_data_swizzle_t;

/*! @brief EPDC display configuration. */
typedef struct _epdc_display_config
{
    uint32_t waveformAddr; /*!< 64-bit aligned waveform table address. */
    uint32_t wbAddr;       /*!< 64-bit aligned working buffer address. */
    uint32_t
        tempIdx;   /*!< Temperature index, used by the EPDC to access the correct temperature compensated waveform. */
    uint16_t resX; /*!< Horizontal resolution in pixels. */
    uint16_t resY; /*!< Vertical resolution in pixels. */
    uint8_t defaltTftPixelValue; /*!< The source-driver voltage value for either partial updates where a pixel has not
                               changed or for any part of the screen which is not being updated during active frame
                               scans. */
    epdc_pixel_format_t pixelFormat; /*!< How many bits of the SDDO bus are required per pixel. This field must be
                                        consistent with the waveform and panel architecture. */
    epdc_wb_type_t wbType;           /*!< Working buffer type. */
    epdc_data_swizzle_t updSwizzle;  /*!< How to swap the bytes for the UPD data before the WB construction. */
    epdc_data_swizzle_t lutSwizzle;  /*!< How to swap the bytes for the LUT data before store to LUTRAM. */
} epdc_display_config_t;

/* Definitions for FIFO control parameters. */

/*! @brief EPDC FIFO control configuration. */
typedef struct _epdc_fifo_config
{
    uint32_t lowLevel : 10U;     /*!< Low level for panic function. */
    uint32_t highLevel : 10U;    /*!< High level for panic function. */
    uint32_t prefillLevel : 10U; /*!< EPDC pre-fill pixel FIFO to this level before TCE starts refresh operations. Must
                                    be less than VERTICAL x HORIZONTAL / 4. */
    uint32_t : 1U;               /*!< Reserved. */
    uint32_t panicEnable : 1U; /*!< Enable epdc_panic output signal for priority elevation. Signal asserts when data in
                                  FIFO is below the low level and de-asserts when above the high level. When asserted,
                                  EPDC transaction requests have elevated priority at SoC-level bus arbitration. */
} epdc_fifo_config_t;

/* Definitions for TCE configuration. */

/*! @brief The VCOM value configuration. */
typedef enum _epdc_tce_vcom_mode
{
    kEPDC_VcomManual = 0x0U, /*!< VCOM value is set manually, call EPDC_SetGpioOutput to set the VCOM value output. */
    kEPDC_VcomAuto   = 0x1U, /*!< VCOM value is used from waveform. */
} epdc_tce_vcom_mode_t;

/*! @brief The data output mode using DATA0 - DATA15. */
typedef enum _epdc_data_output_mode
{
    kEPDC_Sdr8bit  = 0x0U,  /*!< Data driven only on positive edge of SDCLK. Connect to 8-bit SDDO. */
    kEPDC_Sdr16bit = 0x1U,  /*!< Data driven only on positive edge of SDCLK. Connect to 8-bit SDDO. */
    kEPDC_Ddr8bit  = 0x40U, /*!< Data driven on both edge of SDCLK. Connect to 8-bit SDDO. */
    kEPDC_Ddr16bit = 0x41U, /*!< Data driven on both edge of SDCLK. Connect to 16-bit SDDO. */
    kEPDC_Lvds = 0x71U, /*!< DATA[15:8] is for differencial signalling. Requires data driven on both edge of SDCLK and
                           connect to 16-bit SDDO. */
    kEPDC_SdrDualScan = 0x3U,  /*!< Data driven only on positive edge of SDCLK. DATA[7:0] and DATA[15:8] drive the
                                  upper/lower half of the panel. */
    kEPDC_DdrDualScan = 0x43U, /*!< Data driven on both edge of SDCLK. DATA[7:0] and DATA[15:8] drive the upper/lower
                                  half of the panel. */
} epdc_data_output_mode_t;

/*! @brief The vertical scan direction in dual scan mode. */
typedef enum _epdc_dualscan_direction
{
    kEPDC_DualScanToptoBottom = 0x0U, /*!< Scan this region from top to bottom. */
    kEPDC_DualScanBottomtoTop = 0x1U, /*!< Scan this region from bottom to top. */
} epdc_dualscan_direction_t;

/*! @brief The signal output polarity for SDCE/SDLE/SDOE in source driver and GDOE/GDSP in gate driver. */
typedef enum _epdc_polarity
{
    kEPDC_ActiveLow  = 0x0U,
    kEPDC_ActiveHigh = 0x1U,
} epdc_polarity_t;

/*! @brief The data reverse configuration for source driver configuration. */
typedef enum _epdc_data_reverse
{
    kEPDC_DataUnchanged = 0x0U,
    kEPDC_DataReversed =
        0x1U, /*!< Reverse the pixel order on SDDO, eg: 2B/pixel on 8-bit bus, P3,P2,P1,P0->P0,P1,P2,P3. */
} epdc_data_reverse_t;

/*! @brief Shift direction for SDSHR/GDRL signal for sourece/gate driver configuration.TODO */
typedef enum _epdc_shift_direction
{
    kEPDC_ShiftRight = 0x0U,
    kEPDC_ShiftLeft  = 0x1U,
} epdc_shift_direction_t;

/*! @brief SDCLK/SDLE signal delay. */
typedef enum _epdc_signal_delay
{
    kEPDC_NoDelay     = 0x0U, /*!< No delay. */
    kEPDC_Delay1Cycle = 0x1U, /*!< Delay 1 SDCLK cycle. */
    kEPDC_Delay2Cycle = 0x2U, /*!< Delay 2 SDCLK cycle. */
    kEPDC_Delay3Cycle = 0x3U, /*!< Delay 3 SDCLK cycle. */
} epdc_signal_delay_t;

/*! @brief EPDC source driver configuration. Source driver controls the timing for horizontal scan. */
typedef struct _epdc_sd_config
{
    uint32_t sdcePol : 1U;         /*!< SDCE polarity. Refer @ref epdc_polarity_t. */
    uint32_t sdlePol : 1U;         /*!< SDLE polarity. Refer @ref epdc_polarity_t. */
    uint32_t sdoePol : 1U;         /*!< SDOE polarity, including SDOE/SDOEZ/SDOED. Refer @ref epdc_polarity_t. */
    uint32_t sdclk_delay : 2;      /*!< Additional delay to the SDCLK generation. Refer @ref epdc_signal_delay_t. */
    uint32_t : 1U;                 /*!< Reserved. */
    uint32_t sdclk_invert : 1;     /*!< Invert the SDCLK signal. */
    uint32_t sdle_delay : 2;       /*!< Additional delay to the SDLE generation. Refer @ref epdc_signal_delay_t. */
    uint32_t : 4U;                 /*!< Reserved. */
    uint32_t dataInvert : 1U;      /*!< Invert the polarity of each SDDO bit, eg: 0xAAAA -> 0x5555. */
    uint32_t pixelReverse : 2U;    /*!< Reverse the pixel order on SDDO, eg: 2B/pixel on 8-bit bus,
                                      P3,P2,P1,P0->P0,P1,P2,P3. Refer @ref epdc_data_reverse_t. */
    uint32_t sdceCount : 4U;       /*!< The total count of source driver IC chip-enable pins. Make sure the horizontal
                                      resolution can be evenly devided by it. */
    uint32_t shiftDir : 1U;        /*!< The value of the SDSHR output signal controlling shift direction. Refer @ref
                                      epdc_shift_direction_t. */
    uint32_t clockHoldEnable : 1U; /*!< Enable to hold the SDCLK low furing line begin phase. */
    uint32_t : 10U;                /*!< Reserved. */
    uint32_t sdoezDelay : 8U;      /*!< Number of PIXCLK cycles from SDLE falling edge to SDOEZ rising. */
    uint32_t sdoezWidth : 8U;      /*!< Number of PIXCLK cycles from SDOEZ high to SDOEZ falling. */
    uint32_t sdoedDelay : 8U;      /*!< Number of PIXCLK cycles from SDOEZ low to SDOED rising. */
    uint32_t sdoedWidth : 8U;      /*!< Number of PIXCLK cycles from SDOED high to SDOED falling. */
} epdc_sd_config_t;

/*! @brief The output mode for GDOE signal. */
typedef enum _epdc_gdoe_mode
{
    kEPDC_GDOEActiveBesideSync = 0x0U, /*!< GDOE is driven at all times during the frame-scan except FRAME_SYNC. */
    kEPDC_GDOEActiveDelayedSck =
        0x1U, /*!< GDOE is driven as a delayed version of GDCLK, and only active during the frame-data time. */
} epdc_gdoe_mode_t;

/*! @brief The output mode for GDSP signal. */
typedef enum _epdc_gdsp_mode
{
    kEPDC_GDSPActiveOnBegin = 0x0U, /*!< GDSP is driven on the first line clock of FRAME_BEGIN for one GDCLK period, and
                                       can be shifted using the GDSP_OFFSET control. */
    kEPDC_GDSPActiveDuringSync =
        0x1U, /*!< GDSP is active during the entire FRAME_SYNC, and GDSP_OFFSET has no effect. */
} epdc_gdsp_mode_t;

/*! @brief EPDC gate driver configuration. Gate driver controls the timing for vertical scan. */
typedef struct _epdc_gd_config
{
    epdc_shift_direction_t
        shiftDir; /*!< The value of the GDRL output signal controlling gate driver pulse shift direction. */
    epdc_gdoe_mode_t gdoeMode; /*!< GDOE(gate driver output enable) signal mode. */
    epdc_gdsp_mode_t gdspMode; /*!< GDSP(gate driver start pulse) signal mode. */
    epdc_polarity_t gdoePol;   /*!< GDOE polarity. */
    epdc_polarity_t gdspPol;   /*!< GDSP polarity. */
    uint16_t gdoeOffset;       /*!< Delay GDOE in the terms of PIXCLK. */
    uint16_t
        gdspOffset; /*!< Delay GDSP in the terms of PIXCLK, only works when GDSP mode is kEPDC_GDSPActiveOnBegin. */
    uint16_t gdClkOffset; /*!< Delay GDCLK from the line time in the terms of PIXCLK. */
    uint16_t gdClkHigh; /*!< GDCLK high-pulse width in PIXCLK. The GDCLK cycle(high+low) always equal to line timing. */
} epdc_gd_config_t;

/*! @brief EPDC scan configuration. Including horizontal scan(line timing) and vertical scan(fram timing). */
typedef struct _epdc_scan_config
{
    uint16_t lineSync;  /*!< Number of PIXCLK cycles for line sync duration. */
    uint16_t lineBegin; /*!< Number of PIXCLK cycles for line begin duration. */
    uint16_t lineEnd;   /*!< Number of PIXCLK cycles for line end duration. */
    uint8_t frameSync;  /*!< Number of lines for frame sync duration. */
    uint8_t frameBegin; /*!< Number of lines for frame begin duration. */
    uint8_t frameEnd;   /*!< Number of lines for frame end duration. */
} epdc_scan_config_t;

/*! @brief EPDC TCE(timing controller engine) configuration. */
typedef struct _epdc_tce_config
{
    uint32_t tceWbAddr;    /*!< Working buffer address for TCE. */
    uint16_t vscanHoldoff; /*!< 9-bit max. Hold off the vertical scan timing during the blanking period to allow more
                              smaller updates to be processed and included in the frame scan. Note the remainder of the
                              blanking period is reserved for pre-filling the TCE pixel FIFOs so make sure enough time
                              is left to prevent FIFO underrun. */
    uint8_t vcomVal;       /*!< 2-bit max. The VCOM value when mode is manual. */
    epdc_tce_vcom_mode_t vcomMode;                /*!< The method to driver VCOM signal. */
    epdc_data_output_mode_t outMode;              /*!< The data output mode. */
    epdc_dualscan_direction_t upperScanDirection; /*!< The scan direction of the upper half in dual scan mode. */
    epdc_dualscan_direction_t lowerScanDirection; /*!< The scan direction of the lower half in dual scan mode. */
    epdc_sd_config_t sdConfig;                    /*!< Source driver configuration */
    epdc_gd_config_t gdConfig;                    /*!< Gate driver configuration */
    epdc_scan_config_t scanConfig;                /*!< Scan configuration */
} epdc_tce_config_t;

/* Pigeon mode configuration parameters. */

/*! @brief Local counter tick event. */
typedef enum _epdc_pigeon_localCounter_tickEvent
{
    kEPDC_TickOnPclk          = 0x0U, /*!< Counter tick on pixel clock. */
    kEPDC_TickOnLineStart     = 0x1U, /*!< Counter tick on line start pulse. */
    kEPDC_TickOnFrameStart    = 0x2U, /*!< Counter tick on frame start pulse. */
    kEPDC_TickOnAnotherSignal = 0x3U, /*!< Use another signal as tick event. */
} epdc_pigeon_localCounter_tickEvent_t;

/*!
 * @brief Global counter select for pigeon signal's local counter start event.
 * If selecting any of the pclk/line/frame cycle, need to call @ref EPDC_ConfigPigeonCycle to set the cycle period
 * first. The cycle configuration applies to all pigeon signals.
 */
typedef enum _epdc_pigeon_globalCounter
{
    kEPDC_PclkCounterReset = 0x0U, /*!< Use pclk counter as global counter, counter reset when state changes. */
    kEPDC_PclkCycleReset = 0x1U, /*!< Use pclk cycle as global counter, counter reset when state changes. Refer to @ref
                                    epdc_pigeon_cycle_config_t for the definition of cycle. */
    kEPDC_LineCounterReset = 0x2U, /*!< Use line counter as global counter, counter reset when state changes. */
    kEPDC_LineCycleReset = 0x3U, /*!< Use line cycle as global counter, counter reset when state changes. Refer to @ref
                                    epdc_pigeon_cycle_config_t for the definition of cycle. */
    kEPDC_FrameCounter = 0x4U,   /*!< Use frame counter as global counter. */
    kEPDC_FrameCycle   = 0x5U, /*!< Use frame cycle as global counter. Refer to @ref epdc_pigeon_cycle_config_t for the
                                  definition of cycle. */
    kEPDC_PclkCounter = 0x6U,  /*!< Use pclk counter as global counter. */
    kEPDC_LineCounter = 0x7U,  /*!< Use line counter as global counter. */
} epdc_pigeon_globalCounter_t;

/*!
 * @brief The event for the pigeon signal's local counter to start ticking.
 * Chose one or more frame events and one or more line events, OR them together to form the final event.
 * eg: Use (kEPDC_FrameData | kEPDC_LineBegin), then the local counter will start ticking when line begin starts on the
 * frame data phase.
 */
enum _epdc_pigeon_localCounter_startEvent
{
    kEPDC_FrameSync  = 1U << 0U,
    kEPDC_FrameBegin = 1U << 1U,
    kEPDC_FrameData  = 1U << 2U,
    kEPDC_FrameEnd   = 1U << 3U,
    kEPDC_LineSync   = 1U << 4U,
    kEPDC_LineBegin  = 1U << 5U,
    kEPDC_LineData   = 1U << 6U,
    kEPDC_LineEnd    = 1U << 7U,
};

/*! @brief Signal output logic . */
typedef enum _epdc_pigeon_output_logic
{
    kEPDC_NoLogic = 0x0U, /*!< No logic operation, use the chosen another signal directly as the output. */
    kEPDC_SignalAndAnother =
        0x1U,                     /*!< Use the pigeon signal AND this chosen another signal to form the final output. */
    kEPDC_SignalOrAnother = 0x2U, /*!< Use the pigeon signal OR this chosen another signal to form the final output. */
    kEPDC_StartPointAndAnother =
        0x3U, /*!< Use local counter's start point AND this chosen another signal to form the final output.TODO */
} epdc_pigeon_output_logic_t;

/*!
 * @brief Signal pigeon mode configuration.
 * Each pigeon signal has one local counter with a configurable start/tick event. The counter value is compared to
 * setCount/clearCount for signal assertion/de-assertion.
 */
typedef struct _epdc_pigeon_config
{
    uint32_t enablePigeon : 1U;          /*!< Enable pigeon mode for this signal. */
    uint32_t polarity : 1U;              /*!< Polarty of the signal output. */
    uint32_t localCounterTickEvent : 2U; /*!< The tick event selection for local counter. Refer @ref
                                            epdc_pigeon_localCounter_tickEvent_t. */
    uint32_t offset : 4U;                /*!< The offset of pclk unit, to let the signal come out earlier/later.TODO */
    uint32_t globalCounterSelect : 4U;   /*!< To use a more accurate local counter start event than
                                            localCounterStartEvent, a global counter combined with startCount can be used.
                                            Refer @ref epdc_pigeon_globalCounter_t. */
    uint32_t startCount : 12U; /*!< When the value of the selected global counter matches the count, the local counter
                                  starts. */
    uint32_t localCounterStartEvent : 8U; /*!< The event to start the local counter. Refer @ref
                                             _epdc_pigeon_localCounter_startEvent. */
    uint32_t setCount : 16U;              /*!< Assert signal when local counter matches this value. */
    uint32_t clearCount : 16U;            /*!< De-assert signal when local counter matches this value. */
    uint32_t outputLogic : 4U; /*!< When localCounterTickEvent is kEPDC_TickOnOtherSignal, use this logic to form the
                                  final output. Refer @ref epdc_pigeon_output_logic_t. */
    uint32_t anotherSignalNum : 5U; /*!< When localCounterTickEvent is kEPDC_TickOnOtherSignal, use the pigeon signal of
                                       this number to form the tick event. */
    uint32_t : 23U;                 /*!< Reserved. */
} epdc_pigeon_config_t;

/*! @brief The pixle/line/frame cycle definition for global counter, shared by all pegion signals. */
typedef struct _epdc_pigeon_cycle_config
{
    uint32_t lineCount : 12U; /*!< If chosing kEPDC_LineCycleReset, n lines in a frame are considered as one cycle, when
                                 the period count matches startCount global counter starts ticking. */
    uint32_t : 4U;            /*!< Reserved. */
    uint32_t pixCount : 12U;  /*!< If chosing kEPDC_PclkCycleReset, n pixles in a line are considered as one cycle, when
                                 the period count matches startCount global counter starts ticking. */
    uint32_t : 4U;            /*!< Reserved. */
    uint32_t frameCount : 12U; /*!< If chosing kEPDC_FrameCycle, n frames are considered as one cycle, when the period
                                  count matches startCount global counter starts ticking. */
    uint32_t : 4U;             /*!< Reserved. */
    uint32_t maxframeCycle : 12U; /*!< The max cycles of frame cycle counter, frame cycle counter resets when reaches
                                     this value. */
    uint32_t : 4U;                /*!< Reserved. */
} epdc_pigeon_cycle_config_t;

/* Definitions for panel update structure. */

/*! @brief Waveform mode. */
typedef enum _epdc_waveform_mode
{
    kEPDC_WaveformInit =
        0x0U, /*!< Panel initialization. Completely erase the display and leave it in the white state. */
    kEPDC_WaveformDU =
        0x1U, /*!< Direct update. Very fast, non-flashy, transitions from any graytone to black or white only. */
    kEPDC_WaveformGC16 = 0x2U, /*!< Grayscale clearing. High image quality, has 16 unique gray levels. */
    kEPDC_WaveformGL16 = 0x3U, /*!< Used to update scattered content on a white background with reduced flash, has 16
                                  unique gray levels. */
    /* For the AF waveform, GLR16 and GLD16 waveform data points to the same voltage lists as the GL16 data and does not
       need to be stored in a separate memory. */
    kEPDC_WaveformGLR16 = 0x4U, /*!< Similar to GL16, but if a separately-supplied image preprocessing algorithm is
                                   used, display quality is improved when transitions to pixel states 29 and 31. */
    kEPDC_WaveformGLD16 =
        0x5U, /*!< Similar to GL16, but if a separately-supplied image preprocessing algorithm is used, display quality
                 is improved when transitions to pixel states 29 and 31, with lighter flash of the background compared
                 to GC16 mode, and reduce image artifacts even more compared to the GLR16 mode. */
    kEPDC_WaveformA2  = 0x6U, /*!< Very fast, non-flashy, transitions from black or white to black or white only. */
    kEPDC_WaveformDU4 = 0x7U, /*!< Direct update 4. Very fast, non-flashy, from any graytone to gray tones 1,6,11,16
                                 represented by pixel states [0 10 20 30]. */
} epdc_waveform_mode_t;

/*! @brief Panel update configuration. */
typedef struct _epdc_update_config
{
    uint32_t
        bufferAddress; /*!< Address pointing to the update region which will be processed into the working buffer. If
                          stride is zero(disabled), the address must start and end on the 8-byte aligned addresses. */
    uint32_t stride;   /*!< Line stride. */
    uint32_t coordinateX : 13;     /*!< X coordinate of the new update region. */
    uint32_t : 3;                  /*!< Reserved. */
    uint32_t coordinateY : 13;     /*!< Y coordinate of the new update region. */
    uint32_t : 3;                  /*!< Reserved. */
    uint32_t width : 13;           /*!< The width of the new update region in pixels. */
    uint32_t : 3;                  /*!< Reserved. */
    uint32_t height : 13;          /*!< The height of the new update region in pixels. */
    uint32_t : 3;                  /*!< Reserved. */
    uint32_t cpValue : 8;          /*!< The CP value if using fixed CP. */
    uint32_t npValue : 8;          /*!< The NP value if using fixed NP. */
    uint32_t : 14;                 /*!< Reserved. */
    uint32_t fixedCpEnable : 1;    /*!< Enable fixed CP, need to set fixedEnable first. */
    uint32_t fixedNpEnable : 1;    /*!< Enable fixed NP, need to set fixedEnable first. */
    uint32_t fullUpdateEnable : 1; /*!< Enable full update. */
    uint32_t dryRunEnable : 1; /*!< Enable dryrun which runs an update to obtain information without performing any real
                                  action. */
    uint32_t autoWaveEnable : 1; /*!< Enable automatical waveform mode selection. After completes the update buffer
                                    processing, EPDC reports the minimal grey level, retrieves the mapped waveform mode
                                    and program it into UPD_CTRL[WAVEFORM_MODE]. To use autowave the waveform map should
                                    be programmed in advance. */
    uint32_t pauseEnable : 1;    /*!< Enable pause after auto waveform selection. User can choose to check and alter the
                                    waveform mode then initiate the update by calling @ref EPDC_ConfigureWaveform. */
    uint32_t voidUpdateCancleDisable : 1; /*!< Disable the feature of cancelling void update(due to collision). */
    uint32_t : 3;                         /*!< Reserved. */
    uint32_t waveformMode : 8;            /*!< Waveform used for the update. Refer @ref epdc_waveform_mode_t. */
    uint32_t lutNum : 6;                  /*!< The LUT number used for the update, can use EPDC_GetNextAvailableLUT. */
    uint32_t : 9;                         /*!< Reserved. */
    uint32_t fixedEnable : 1;             /*!< Use fixed pixel values. */
} epdc_update_config_t;

/*! @brief Autowave map configuration. */
typedef struct _epdc_autowave_map
{
    uint32_t greyLevel : 3;    /*!< Grey level. */
    uint32_t : 13;             /*!< Reserved. */
    uint32_t waveformMode : 8; /*!< Waveform mode. Refer @epdc_waveform_mode_t. */
    uint32_t : 8;              /*!< Reserved. */
} epdc_autowave_map_t;

/* GPIO configuration */

/*! @brief GPIO pin output configuration. */
typedef struct _epdc_gpio_config
{
    uint32_t bdrOutput : 2;     /*!< The BDR(0,1) pin output value. */
    uint32_t pwrCtrlOutput : 4; /*!< The PWR_CTRL(0,1,2,3) pin output value. */
    uint32_t pwrComOutput : 1;  /*!< The PWR_COM pin output value. */
    uint32_t pwrWakeOutput : 1; /*!< The PWR_WAKE pin output value. */
    uint32_t : 24;              /*!< Reserved. */
} epdc_gpio_config_t;

/* LUT collision status */

/*! @brief Update collision status structure. */
typedef struct _epdc_collision_status
{
    uint16_t minX;    /*!< The x offset of the ULC of the collision region. */
    uint16_t minY;    /*!< The y offset of the ULC of the collision region. */
    uint16_t width;   /*!< The width of the collision region. */
    uint16_t height;  /*!< The height of the collision region. */
    uint64_t lutlist; /*!< 64-bit LUT list of the victim LUT(s), if LUT17 is being collided, then the bit17 of the list
                         is set. */
} epdc_collision_status_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Interrupt Sub-group
 * @{
 */
/*!
 * @brief Enables non LUT complete EPDC interrupt source.
 *
 * @param base EPDC base pointer
 * @param interrupts The interrupt source mask, can be a single source or several sources in #_epdc_interrupt_enable
 * ORed together.
 */
static inline void EPDC_EnableInterrupts(EPDC_Type *base, uint8_t interrupts)
{
    base->IRQ_MASK.SET = ((uint32_t)interrupts << 16U);
}

/*!
 * @brief Diables non LUT complete EPDC interrupt source.
 *
 * @param base EPDC base pointer
 * @param interrupts The interrupt source mask, can be a single source or several sources in #_epdc_interrupt_enable
 * ORed together.
 */
static inline void EPDC_DisableInterrupts(EPDC_Type *base, uint8_t interrupts)
{
    base->IRQ_MASK.CLR = ((uint32_t)interrupts << 16U);
}

/*!
 * @brief Gets all the enabled non LUT complete interrupt sources.
 *
 * @param base EPDC base pointer
 * @return The interrupt source mask, can be a single source or several sources in #_epdc_interrupt_enable ORed
 * together.
 */
static inline uint8_t EPDC_GetEnabledInterrupts(EPDC_Type *base)
{
    return (uint8_t)(base->IRQ_MASK.RW >> 16U);
}

/*!
 * @brief Gets the EPDC status flags.
 *
 * @param base EPDC base pointer
 * @return the mask of status flags, can be a single flag or several flags in #_epdc_status_flags ORed together.
 */
static inline uint16_t EPDC_GetStatusFlags(EPDC_Type *base)
{
    return (uint16_t)((base->IRQ.RW >> 12U) | (base->STATUS.RW & 0xFU));
}

/*!
 * @brief Clears the EPDC status flags.
 *
 * @param base EPDC base pointer
 * @param statusFlags The status flag mask, can be a single flag or several flags in #_epdc_status_flags ORed together.
 */
static inline void EPDC_ClearStatusFlags(EPDC_Type *base, uint16_t statusFlags)
{
    base->IRQ.CLR = ((uint32_t)statusFlags << 12U);
}
/*! @} */

/*!
 * @name LUT complete Interrupt Sub-group
 * @{
 */
/*!
 * @brief Enables LUT complete interrupt source.
 *
 * @param base EPDC base pointer
 * @param interrupts The interrupt source mask of single source or several sources up to all 64 interrupt sources.
 *  If user wants to enable the complete interrupt for LUT17, set the bit 17 in this param.
 */
static inline void EPDC_EnableLutCompleteInterrupts(EPDC_Type *base, uint64_t interrupts)
{
    base->IRQ_MASK1.SET = (uint32_t)interrupts;
    base->IRQ_MASK2.SET = (uint32_t)(interrupts >> 32U);
}

/*!
 * @brief Disables LUT complete interrupt source.
 *
 * @param base EPDC base pointer
 * @param interrupts The interrupt source mask of single source or several sources up to all 64 interrupt sources.
 *  If user wants to disable the complete interrupt for LUT17, set the bit 17 in this param.
 */
static inline void EPDC_DisableLutCompleteInterrupts(EPDC_Type *base, uint64_t interrupts)
{
    base->IRQ_MASK1.CLR = (uint32_t)interrupts;
    base->IRQ_MASK2.CLR = (uint32_t)(interrupts >> 32U);
}

/*!
 * @brief Gets all the enabled LUT complete interrupts.
 *
 * @param base EPDC base pointer
 * @return The interrupt source mask, can be a single source or several sources up to all 64 interrupt sources.
 *  If complete interrupt for LUT17 is enabled, bit 17 is set.
 */
static inline uint64_t EPDC_GetEnabledLutCompleteInterrupts(EPDC_Type *base)
{
    return (((uint64_t)(base->IRQ_MASK2.RW) << 32U) | (uint64_t)base->IRQ_MASK1.RW);
}

/*!
 * @brief Gets the LUT complete status flags.
 *
 * @param base EPDC base pointer
 * @return the mask of status flags, can be a single flag or several flags up to all 64 interrupt flags.
 *  If LUT17 has completed, bit 17 is set.
 */
static inline uint64_t EPDC_GetLutCompleteStatusFlags(EPDC_Type *base)
{
    return (uint64_t)base->IRQ1.RW | ((uint64_t)base->IRQ2.RW << 32U);
}

/*!
 * @brief Clears the LUT complete status flags.
 *
 * @param base EPDC base pointer
 * @param the mask of status flags, can be a single flag or several flags up to all 64 interrupt flags.
 *  If user wants to clear LUT17 completion, set bit 17 in this param.
 */
static inline void EPDC_ClearLutCompleteStatusFlags(EPDC_Type *base, uint64_t statusFlags)
{
    base->IRQ1.CLR = (uint32_t)statusFlags;
    base->IRQ2.CLR = (uint32_t)(statusFlags >> 32U);
}
/*! @} */

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Resets the EPDC to initialized state.
 *
 * @param base EPDC base pointer
 */
void EPDC_ResetToInit(EPDC_Type *base);

/*!
 * @brief Initializes the EPDC.
 *
 * This function enables the EPDC peripheral clock, and resets the EPDC registers
 * to default status.
 *
 * @param base EPDC base pointer
 */
void EPDC_Init(EPDC_Type *base);

/*!
 * @brief De-initializes the EPDC.
 *
 * This function disables the EPDC peripheral clock.
 *
 * @param base EPDC base pointer
 */
void EPDC_Deinit(EPDC_Type *base);
/*! @} */

/*!
 * @name Display Parameters Initialization
 * @{
 */
/*!
 * @brief Initializes the EPDC dispaly parameters.
 *
 * @param base EPDC base pointer
 * @param config Pointer to EPDC display configuration structure
 * @retval kStatus_Success Successfully initialized the display parameters
 * @retval kStatus_InvalidArgument parameter(s) is(are) not valid
 */
status_t EPDC_InitDisplay(EPDC_Type *base, const epdc_display_config_t *config);
/*! @} */

/*!
 * @name FIFO control
 * @{
 */
/*!
 * @brief Configures the FIFO control parameters, including panic function and pre-fill level.
 *
 * @param base EPDC base pointer
 * @param config Pointer to EPDC FIFO control configuration structure
 * @retval kStatus_Success Successfully configured the FIFO
 * @retval kStatus_InvalidArgument parameter(s) is(are) not valid
 */
status_t EPDC_ConfigFifo(EPDC_Type *base, const epdc_fifo_config_t *config);

/*!
 * @brief Enables/disables the panic funtion for FIFO control.
 *
 * @param base EPDC base pointer
 * @param enable true to enable panic function, false to disable
 */
static inline void EPDC_EnableFifoPanic(EPDC_Type *base, bool enable)
{
    if (enable)
    {
        base->FIFOCTRL.SET = EPDC_FIFOCTRL_ENABLE_PRIORITY_MASK;
    }
    else
    {
        base->FIFOCTRL.CLR = EPDC_FIFOCTRL_ENABLE_PRIORITY_MASK;
    }
}
/*! @} */

/*!
 * @name TCE(timing controller engine) configuration
 * @{
 */
/*!
 * @brief Configures the TCE parameters before initiating the panel update.
 *
 * @note Make sure to configure the display parameters by @ref EPDC_InitDisplay before calling this API.
 *
 * @param base EPDC base pointer
 * @param config Pointer to EPDC TCE control configuration structure
 * @retval kStatus_Success Successfully configured the TCE
 * @retval kStatus_InvalidArgument parameter(s) is(are) not valid
 */
status_t EPDC_ConfigTCE(EPDC_Type *base, const epdc_tce_config_t *config);
/*! @} */

/*!
 * @name PIGEON mode configuration
 * @{
 */
/*!
 * @brief Configures the signal output format for signals that support pigeon mode.
 *
 * @note Refer to the soc reference manual to check the configurable pigeon signal.
 *       No need to call this API if not using the pigeon mode.
 *
 * @param base EPDC base pointer
 * @param signalNum The number of the pigeon signal to be configured
 * @param config Pointer to EPDC pigeon mode configuration structure
 */
void EPDC_ConfigPigeon(EPDC_Type *base, uint8_t signalNum, const epdc_pigeon_config_t *config);

/*!
 * @brief Configures the cycle's period.
 *
 * When selecting any of the pclk/line/frame cycle as global counter, call this API forst to set the proper cycle
 * period. The configuraton is shared for all pigeon signals.
 *
 * @param base EPDC base pointer
 * @param config Pointer to EPDC pigeon mode cycle configuration structure
 */
void EPDC_ConfigPigeonCycle(EPDC_Type *base, const epdc_pigeon_cycle_config_t *config);
/*! @} */

/*!
 * @name Panel Update
 * @{
 */
/*!
 * @brief Gets the number of the next available LUT.
 *
 * @param base EPDC base pointer
 * @param lutNum Pointer to LUT number
 * @retval kStatus_Success Successfully got the LUT number
 * @retval kStatus_Fail no valid LUT present, all LUTs are busy
 */
status_t EPDC_GetNextAvailableLUT(EPDC_Type *base, uint8_t *lutNum);

/*!
 * @brief Configures the waveform mode and initiate the panel update.
 *
 * @param base EPDC base pointer
 * @param waveformMode Waveform mode
 */
static inline void EPDC_ConfigureWaveform(EPDC_Type *base, uint8_t waveformMode)
{
    base->UPD_CTRL.RW = (base->UPD_CTRL.RW & ~EPDC_UPD_CTRL_WAVEFORM_MODE_MASK) | EPDC_UPD_CTRL_WAVEFORM_MODE(waveformMode);
}

/*!
 * @brief Initiates a panel display update.
 *
 * @param base EPDC base pointer
 * @param config Pointer to update configuration structure
 * @retval kStatus_Success Successfully initiate an update
 * @retval kStatus_Fail update failed due to busy working buffer or LUT
 * @retval kStatus_InvalidArgument parameter(s) is(are) not valid
 */
status_t EPDC_UpdateDisplay(EPDC_Type *base, epdc_update_config_t *config);

/*!
 * @brief Sets one map between a grey level and its waveform mode.
 *
 * Call this API multiple times until all the maps are set.
 *
 * @param base EPDC base pointer
 * @param config Pointer to autowave configuration structure
 */
void EPDC_SetAutowaveMap(EPDC_Type *base, const epdc_autowave_map_t *config);
/*! @} */

/*!
 * @name Panel Update
 * @{
 */
/*!
 * @brief Sets the GPIO output value for BDR(0,1), PWR_CTRL(0,1,2,3), PWR_COM and PWR_WAKE pins.
 *
 * @param base EPDC base pointer
 * @param config Pointer to GPIO configuration structure
 */
void EPDC_SetGpioOutput(EPDC_Type *base, const epdc_gpio_config_t *config);
/*! @} */

/*!
 * @name Update collision
 * @{
 */
/*!
 * @brief Gets the status of the collision
 *
 * @param base EPDC base pointer
 * @param status Pointer to collision status structure
 */
void EPDC_GetCollisionStatus(EPDC_Type *base, epdc_collision_status_t *status);
/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_EPDC_H_ */
