/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_SSD1963_H_
#define _FSL_SSD1963_H_

#include "fsl_dbi.h"

/*!
 * @addtogroup ssd1963
 * @{
 */

/*
 * Change log:
 *
 *   1.1.2
 *     - Fix MISRA 2012 issues.
 *
 *   1.1.1
 *     - Support RGB565/RGB888/BGR565/BGR888.
 *
 *   1.1.0
 *     - Add 8-bit data bus support. Currently support 8-bit and 16bit data bus,
 *       configured by the macro SSD1963_DATA_WITDH.
 *     - Remove the dependency on flexio_mcu_lcd driver.
 *     - Add more generic functions SSD1963_ReadMemory and SSD1963_WriteMemory.
 *     - Remove the function SSD1963_WriteSamePixels.
 *     - Change the video memory access functions to non-blocking functions.
 *
 *   1.0.0
 *     - Initial version
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Data width between host and SSD1963 controller, only supports 8 and 16. */
#ifndef SSD1963_DATA_WITDH
#define SSD1963_DATA_WITDH (16U)
#endif

/*! @brief SSD1963 command. */
#define SSD1963_NOP                      0x00U
#define SSD1963_SOFT_RESET               0x01U
#define SSD1963_GET_POWER_MODE           0x0AU
#define SSD1963_GET_ADDRESS_MODE         0x0BU
#define SSD1963_GET_DISPLAY_MODE         0x0DU
#define SSD1963_GET_TEAR_EFFECT_STATUS   0x0EU
#define SSD1963_ENTER_SLEEP_MODE         0x10U
#define SSD1963_EXIT_SLEEP_MODE          0x11U
#define SSD1963_ENTER_PARTIAL_MODE       0x12U
#define SSD1963_ENTER_NORMAL_MODE        0x13U
#define SSD1963_EXIT_INVERT_MODE         0x20U
#define SSD1963_ENTER_INVERT_MODE        0x21U
#define SSD1963_SET_GAMMA_CURVE          0x26U
#define SSD1963_SET_DISPLAY_OFF          0x28U
#define SSD1963_SET_DISPLAY_ON           0x29U
#define SSD1963_SET_COLUMN_ADDRESS       0x2AU
#define SSD1963_SET_PAGE_ADDRESS         0x2BU
#define SSD1963_WRITE_MEMORY_START       0x2CU
#define SSD1963_READ_MEMORY_START        0x2EU
#define SSD1963_SET_PARTIAL_AREA         0x30U
#define SSD1963_SET_SCROLL_AREA          0x33U
#define SSD1963_SET_TEAR_OFF             0x34U
#define SSD1963_SET_TEAR_ON              0x35U
#define SSD1963_SET_ADDRESS_MODE         0x36U
#define SSD1963_SET_SCROLL_START         0x37U
#define SSD1963_EXIT_IDLE_MODE           0x38U
#define SSD1963_ENTER_IDLE_MODE          0x39U
#define SSD1963_WRITE_MEMORY_CONTINUE    0x3CU
#define SSD1963_READ_MEMORY_CONTINUE     0x3EU
#define SSD1963_SET_TEAR_SCANLINE        0x44U
#define SSD1963_GET_SCANLINE             0x45U
#define SSD1963_READ_DDB                 0xA1U
#define SSD1963_SET_LCD_MODE             0xB0U
#define SSD1963_GET_LCD_MODE             0xB1U
#define SSD1963_SET_HORI_PERIOD          0xB4U
#define SSD1963_GET_HORI_PERIOD          0xB5U
#define SSD1963_SET_VERT_PERIOD          0xB6U
#define SSD1963_GET_VERT_PERIOD          0xB7U
#define SSD1963_SET_GPIO_CONF            0xB8U
#define SSD1963_GET_GPIO_CONF            0xB9U
#define SSD1963_SET_GPIO_VALUE           0xBAU
#define SSD1963_GET_GPIO_STATUS          0xBBU
#define SSD1963_SET_POST_PROC            0xBCU
#define SSD1963_GET_POST_PROC            0xBDU
#define SSD1963_SET_PWM_CONF             0xBEU
#define SSD1963_GET_PWM_CONF             0xBFU
#define SSD1963_GET_LCD_GEN0             0xC0U
#define SSD1963_SET_LCD_GEN0             0xC1U
#define SSD1963_GET_LCD_GEN1             0xC2U
#define SSD1963_SET_LCD_GEN1             0xC3U
#define SSD1963_GET_LCD_GEN2             0xC4U
#define SSD1963_SET_LCD_GEN2             0xC5U
#define SSD1963_GET_LCD_GEN3             0xC6U
#define SSD1963_SET_LCD_GEN3             0xC7U
#define SSD1963_SET_GPIO0_ROP            0xC8U
#define SSD1963_GET_GPIO0_ROP            0xC9U
#define SSD1963_SET_GPIO1_ROP            0xCAU
#define SSD1963_GET_GPIO1_ROP            0xCBU
#define SSD1963_SET_GPIO2_ROP            0xCCU
#define SSD1963_GET_GPIO2_ROP            0xCDU
#define SSD1963_SET_GPIO3_ROP            0xCEU
#define SSD1963_GET_GPIO3_ROP            0xCFU
#define SSD1963_SET_DBC_CONF             0xD0U
#define SSD1963_GET_DBC_CONF             0xD1U
#define SSD1963_SET_DBC_TH               0xD4U
#define SSD1963_GET_DBC_TH               0xD5U
#define SSD1963_SET_PLL                  0xE0U
#define SSD1963_SET_PLL_MN               0xE2U
#define SSD1963_GET_PLL_MN               0xE3U
#define SSD1963_GET_PLL_STATUS           0xE4U
#define SSD1963_SET_DEEP_SLEEP           0xE5U
#define SSD1963_SET_LSHIFT_FREQ          0xE6U
#define SSD1963_GET_LSHIFT_FREQ          0xE7U
#define SSD1963_SET_PIXEL_DATA_INTERFACE 0xF0U
#define SSD1963_GET_PIXEL_DATA_INTERFACE 0xF1U

#define SSD1963_ADDR_MODE_FLIP_VERT           (1U << 0)
#define SSD1963_ADDR_MODE_FLIP_HORZ           (1U << 1)
#define SSD1963_ADDR_MODE_LATCH_RIGHT_TO_LEFT (1U << 2)
#define SSD1963_ADDR_MODE_BGR                 (1U << 3)
#define SSD1963_ADDR_MODE_REFRESH_BOTTOM_UP   (1U << 4)
#define SSD1963_ADDR_MODE_PAG_COL_ADDR_ORDER  (1U << 5)
#define SSD1963_ADDR_MODE_COL_ADDR_ORDER      (1U << 6)
#define SSD1963_ADDR_MODE_PAGE_ADDR_ORDER     (1U << 7)

/*! @brief ssd1963 handle. */
typedef struct _ssd1963_handle
{
    uint8_t addrMode;              /*!< The parameter of set_address_mode and get_address_mode. */
    uint16_t panelWidth;           /*!< Width of the panel. */
    uint16_t panelHeight;          /*!< Height of the panel. */
    const dbi_xfer_ops_t *xferOps; /*!< Bus transfer operations. */
    void *xferOpsData;             /*!< Data used for transfer operations. */
} ssd1963_handle_t;

/*! @brief SSD1963 TFT interface timing polarity flags. */
enum _ssd1963_polarity_flags
{
    kSSD1963_HsyncActiveHigh            = (1U << 1U), /*!< Set then the HSYNC will be active high. */
    kSSD1963_VsyncActiveHigh            = (1U << 0U), /*!< Set then the VSYNC will be active high. */
    kSSD1963_LatchDataInClockRisingEdge = (1U << 2U), /*!< Set then the data latched in clock rising edge. */
};

/*! @brief The data width between SSD1963 and TFT panel. */
typedef enum _ssd1963_panel_data_width
{
    kSSD1963_PanelData18Bit = 0 << 5, /*!< 18-bit panel data. */
    kSSD1963_PanelData24Bit = 1 << 5, /*!< 24-bit panel data. */
} ssd1963_panel_data_width_t;

/*!
 * @brief The pixel data interface format.
 * Currently only supports such formats
 *  - 16-bits interface, pixel format BGR565, every pixel is sent by one cycle.
 *  - 8-bits interface, pixel format BGR888, every pixel is sent by 3 cycles.
 */
typedef enum _ssd1963_pixel_interface
{
#if (8 == SSD1963_DATA_WITDH)
    kSSD1963_PixelInterface8BitBGR888 = 0,               /*!< 8-bits interface, pixel format BGR888, deprecated.
                                                              Use kSSD1963_BGR888 instead. */
    kSSD1963_BGR888 = kSSD1963_PixelInterface8BitBGR888, /*!< 8-bits interface, pixel format BGR888. */
    kSSD1963_RGB888 = 1,                                 /*!< 8-bits interface, pixel format BGR888. */
#else
    kSSD1963_PixelInterface16Bit565 = 0,               /*!< 16-bits interface, pixel format BGR565, deprecated.
                                                     Use kSSD1963_RGB565 instead  */
    kSSD1963_RGB565 = kSSD1963_PixelInterface16Bit565, /*!< 16-bits interface, pixel format RGB565. */
    kSSD1963_BGR565 = 1,                               /*!< 16-bits interface, pixel format BGR565. */
#endif
} ssd1963_pixel_interface_t;

/*! @brief Initailize structure of ssd1963 */
typedef struct _ssd1963_config
{
    uint32_t pclkFreq_Hz;                      /*!< Pixel clock (LSHIFT clock) frequency in Hz. */
    ssd1963_pixel_interface_t pixelInterface;  /*!< Pixel interface format. */
    ssd1963_panel_data_width_t panelDataWidth; /*!< Panel data width. */
    uint8_t polarityFlags;                     /*!< OR'ed value of @ref _ssd1963_polarity_flags. */
    uint16_t panelWidth;                       /*!< How many pixels per line. */
    uint16_t panelHeight;                      /*!< How many lines per panel. */
    uint16_t hsw;                              /*!< HSYNC pulse width. */
    uint16_t hfp;                              /*!< Horizontal front porch. */
    uint16_t hbp;                              /*!< Horizontal back porch. */
    uint16_t vsw;                              /*!< VSYNC pulse width. */
    uint16_t vfp;                              /*!< Vrtical front porch. */
    uint16_t vbp;                              /*!< Vertical back porch. */
} ssd1963_config_t;

/*! @brief SSD1963 flip mode. */
typedef enum _ssd1963_flip_mode
{
    kSSD1963_FlipNone       = 0U,                          /*!< No flip. */
    kSSD1963_FlipVertical   = SSD1963_ADDR_MODE_FLIP_VERT, /*!< Flip vertical, set_address_mode A[0] */
    kSSD1963_FlipHorizontal = SSD1963_ADDR_MODE_FLIP_HORZ, /*!< Flip horizontal, set_address_mode A[1] */
    kSSD1963_FlipBoth =
        SSD1963_ADDR_MODE_FLIP_VERT | SSD1963_ADDR_MODE_FLIP_HORZ, /*!< Flip both vertical and horizontal. */
} ssd1963_flip_mode_t;

/*!
 * @brief SSD1963 orientation mode.
 * After setting the orientation mode, the accress order from host processor to
 * frame buffer will be changed.
 */
typedef enum _ssd1963_orientation_mode_t
{
    kSSD1963_Orientation0 = 0U, /*!< Rotate 0 degree. */
    kSSD1963_Orientation90 =
        SSD1963_ADDR_MODE_PAGE_ADDR_ORDER | SSD1963_ADDR_MODE_PAG_COL_ADDR_ORDER, /*!< Rotate 90 degree. */
    kSSD1963_Orientation180 =
        SSD1963_ADDR_MODE_PAGE_ADDR_ORDER | SSD1963_ADDR_MODE_COL_ADDR_ORDER, /*!< Rotate 180 degree. */
    kSSD1963_Orientation270 =
        SSD1963_ADDR_MODE_COL_ADDR_ORDER | SSD1963_ADDR_MODE_PAG_COL_ADDR_ORDER, /*!< Rotate 270 degree. */
} ssd1963_orientation_mode_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initailize the SSD1963.
 *
 * This function configures the SSD1963 contoller, and setups the interface
 * between LCD panel. This function does not turn on the display, application
 * could turn on the display after filling the frame buffer.
 *
 * @param handle SSD1963 handle structure.
 * @param config Pointer to the SSD1963 configuration structure.
 * @param xferOps DBI interface transfer operation functions.
 * @param xferOpsData Private data used by the DBI interface.
 * @param srcClock_Hz The external reference clock(XTAL or CLK) frequency in Hz.
 *
 * @retval kStatus_Success Initailize successfully.
 * @retval kStatus_InvalidArgument Initailize failed because of invalid argument.
 */
status_t SSD1963_Init(ssd1963_handle_t *handle,
                      const ssd1963_config_t *config,
                      const dbi_xfer_ops_t *xferOps,
                      void *xferOpsData,
                      uint32_t srcClock_Hz);

/*!
 * @brief Set the memory access done callback.
 *
 * @param handle SSD1963 handle structure.
 * @param callback Callback function when the video memory operation finished.
 *        the video memory functions include @ref SSD1963_WriteMemory,
 *        @ref SSD1963_ReadMemory, @ref SSD1963_WritePixels, and @ref SSD1963_ReadPixels
 *        these functions are non-blocking functions, upper layer is notified
 *        by this callback function after transfer done.
 * @param userData Parameter of @ref memDoneCallback.
 */
void SSD1963_SetMemoryDoneCallback(ssd1963_handle_t *handle, dbi_mem_done_callback_t callback, void *userData);

/*!
 * @brief Deinitailize the SSD1963.
 *
 * @param handle SSD1963 handle structure.
 */
void SSD1963_Deinit(ssd1963_handle_t *handle);

/*!
 * @brief Set display on.
 *
 * @param handle SSD1963 handle structure.
 */
status_t SSD1963_StartDisplay(ssd1963_handle_t *handle);

/*!
 * @brief Set display off.
 *
 * @param handle SSD1963 handle structure.
 */
status_t SSD1963_StopDisplay(ssd1963_handle_t *handle);

/*!
 * @brief Set display flip mode.
 *
 * @param handle SSD1963 handle structure.
 * @param mode The flip mode.
 */
status_t SSD1963_SetFlipMode(ssd1963_handle_t *handle, ssd1963_flip_mode_t mode);

/*!
 * @brief Set display orientation mode.
 *
 * @param handle SSD1963 handle structure.
 * @param mode The orientation mode.
 */
status_t SSD1963_SetOrientationMode(ssd1963_handle_t *handle, ssd1963_orientation_mode_t mode);

/*!
 * @brief Set the backlight value.
 *
 * @param handle SSD1963 handle structure.
 * @param value Backlight value, must be in the range of 0 to 255.
 */
status_t SSD1963_SetBackLight(ssd1963_handle_t *handle, uint8_t value);

/*!
 * @brief Select area to read or write.
 *
 * @param handle SSD1963 handle structure.
 * @param startX Start point X coordination.
 * @param startY Start point Y coordination.
 * @param endX End point X coordination.
 * @param endY End point Y coordination.
 */
status_t SSD1963_SelectArea(ssd1963_handle_t *handle, uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY);

#if (16 == SSD1963_DATA_WITDH)
/*!
 * @brief Read pixel data from the selected area.
 *
 * This function reads pixel data to the area selected by the function
 * @ref SSD1963_SelectArea. The pixel data will be read from the start of
 * the area, it could not read the pixels out of the selected area.
 *
 * @param handle SSD1963 handle structure.
 * @param pixels Pointer to the memory to save the read pixels.
 * @param length Length of the pixel array @p pixels.
 * @note This function should only be used when @ref kSSD1963_PixelInterface16Bit565
 * used.
 * @deprecated Use @ref SSD1963_ReadMemory instead, note the @p length of this function
 * is pixel count, and the @p length of @ref SSD1963_ReadMemory is byte count.
 */
status_t SSD1963_ReadPixels(ssd1963_handle_t *handle, uint16_t *pixels, uint32_t length);

/*!
 * @brief Write pixel data to the selected area.
 *
 * This function writes pixel data to the area selected by the function
 * @ref SSD1963_SelectArea. The pixel data will be written from the start of
 * the area, if the pixel data written is larger than the area size, the part
 * out of range will be ignored.
 *
 * @param handle SSD1963 handle structure.
 * @param pixels Pointer to the pixels to write.
 * @param length Length of the pixel array @p pixels.
 * @note This function should only be used when @ref kSSD1963_PixelInterface16Bit565
 * used.
 * @deprecated Use @ref SSD1963_WriteMemory instead, note the @p length of this function
 * is pixel count, and the @p length of @ref SSD1963_WriteMemory is byte count.
 */
status_t SSD1963_WritePixels(ssd1963_handle_t *handle, const uint16_t *pixels, uint32_t length);
#endif

/*!
 * @brief Read pixel data from the selected area in controller memory.
 *
 * This function reads pixel data to the area selected by the function
 * @ref SSD1963_SelectArea. The pixel data will be read from the start of
 * the area, it could not read the pixels out of the selected area.
 *
 * @param handle SSD1963 handle structure.
 * @param data Pointer to the memory to save the read pixels.
 * @param length Length of the data to read (in byte).
 */
status_t SSD1963_ReadMemory(ssd1963_handle_t *handle, uint8_t *data, uint32_t length);

/*!
 * @brief Write pixel data to the selected area.
 *
 * This function writes pixel data to the area selected by the function
 * @ref SSD1963_SelectArea. The pixel data will be written from the start of
 * the area, if the pixel data written is larger than the area size, the part
 * out of range will be ignored.
 *
 * @param handle SSD1963 handle structure.
 * @param data Pointer to the pixels to write.
 * @param length Length of the data to write (in byte).
 */
status_t SSD1963_WriteMemory(ssd1963_handle_t *handle, const uint8_t *data, uint32_t length);

/*!
 * @brief Enable or disable tear effect signal.
 *
 * @param handle SSD1963 handle structure.
 * @param enable Pass in true to enable, false to disable.
 */
status_t SSD1963_EnableTearEffect(ssd1963_handle_t *handle, bool enable);

/*!
 * @brief Set the pixel format.
 *
 * @param handle SSD1963 handle structure.
 * @param pixelFormat Pixel format to set.
 */
status_t SSD1963_SetPixelFormat(ssd1963_handle_t *handle, ssd1963_pixel_interface_t pixelFormat);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_SSD1963_H_ */
