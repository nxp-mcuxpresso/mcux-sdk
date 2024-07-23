/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_ST7796S_H_
#define _FSL_ST7796S_H_

#include <stdbool.h>

#include "fsl_dbi.h"

/*!
 * @addtogroup st7796s
 * @{
 */

/*
 * Change log:
 *
 *   1.0.0
 *     - Initial version
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Panel driver preset. */
typedef enum _st7796s_driver_preset
{
    kST7796S_DriverPresetLCDPARS035, /*!< Driving preset for LCD-PAR-S035. */
} st7796s_driver_preset_t;

/*! @brief Display Orientation. */
typedef enum _st7796s_orientation_mode
{
    kST7796S_Orientation0   = 0x08U, /*!< Rotation 0 degrees */
    kST7796S_Orientation90  = 0x68U, /*!< Rotation 90 degrees */
    kST7796S_Orientation180 = 0xC8U, /*!< Rotation 180 degrees */
    kST7796S_Orientation270 = 0xA8U, /*!< Rotation 270 degrees */
} st7796s_orientation_mode_t;

/*! @brief Pixel format, does not affect interface width */
typedef enum _st7796s_pixel_format
{
    kST7796S_PixelFormatRGB565 = 5U, /*!< Pixel format RGB565, 16bits per pixel */
    kST7796S_PixelFormatRGB666 = 6U, /*!< Pixel format RGB666, 18bits per pixel */
    kST7796S_PixelFormatRGB888 = 7U, /*!< Pixel format RGB888, 24bits per pixel, internally dithered to 18bits */
    kST7796S_PixelFormatRGB444 = 3U, /*!< Pixel format RGB444, 12bits per pixel */
} st7796s_pixel_format_t;

/*! @brief TE (tearing effect) output configuration */
typedef enum _st7796s_te_config
{
    kST7796S_TEDisabled, /*!< TE output disabled (no output) */
    kST7796s_TEVSync,    /*!< TE output enabled on VSync */
    kST7796S_TEHVSync,   /*!< TE output enabled on both HSync and VSync */
} st7796s_te_config_t;

/*! @brief Panel configuration structure */
typedef struct _st7796s_config
{
    st7796s_driver_preset_t driverPreset;       /*!< Driver configuration preset */
    st7796s_pixel_format_t pixelFormat;         /*!< Color format */
    st7796s_orientation_mode_t orientationMode; /*!< Display orientation */
    st7796s_te_config_t teConfig;               /*!< TE line configuration */
    bool invertDisplay;                         /*!< Invert display color */
    bool flipDisplay;                           /*!< Mirror display image */
    bool bgrFilter;                             /*!< Use BGR color filter instead of RGB */
} st7796s_config_t;

/*! @brief ST7796S driver handle structure */
typedef struct _st7796s_handle
{
#if MCUX_DBI_LEGACY
    const dbi_xfer_ops_t *xferOps; /*!< Bus transfer operations. */
    void *xferOpsData;             /*!< Data used for transfer operations. */
#else
    dbi_iface_t *dbiIface; /*!< DBI interface handle. */
#endif
    st7796s_orientation_mode_t orientationMode; /*!< Current orientation mode */
} st7796s_handle_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

#if MCUX_DBI_LEGACY
/*!
 * @brief Initialize ST7796S controller.
 *
 * This function performs a software reset and initialize the display driver using
 * a preset configuration. This function does not turn on the display, application
 * could perform the @ref ST7796S_EnableDisplay later after filling the frame buffer.
 *
 * @param handle ST7796S handle structure.
 * @param config Pointer to the panel configuration structure.
 * @param xferOps DBI interface transfer operation functions.
 * @param xferOpsData Private data used by the DBI interface.
 *
 * @return This function returns kStatus_Success after successfully initialized.
 *         Appropriate kStatus_ prefixed errors will be given when an error occurred.
 *         Please refer to the corresponding modules for an specific error coding.
 */
status_t ST7796S_Init(st7796s_handle_t *handle,
                      const st7796s_config_t *config,
                      const dbi_xfer_ops_t *xferOps,
                      void *xferOpsData);
#else
/*!
 * @brief Initialize ST7796S controller.
 *
 * This function performs a software reset and initialize the display driver using
 * a preset configuration. This function does not turn on the display, application
 * could perform the @ref ST7796S_EnableDisplay later after filling the frame buffer.
 *
 * @param handle ST7796S handle structure.
 * @param config Pointer to the panel configuration structure.
 * @param dbiIface DBI interface handle.
 *
 * @return This function returns kStatus_Success after successfully initialized.
 *         Appropriate kStatus_ prefixed errors will be given when an error occurred.
 *         Please refer to the corresponding modules for an specific error coding.
 */
status_t ST7796S_Init(st7796s_handle_t *handle, const st7796s_config_t *config, dbi_iface_t *dbiIface);
#endif

/*!
 * @brief Invert or restore display color.
 *
 * This function invert the display color to the panel. Invert is also related
 * to the panel technology, for instance, an IPS panel will need the display color
 * to be inverted, while traditional TFT panels will not.
 *
 * @param handle ST7796S handle structure.
 * @param invert Whether to invert the display color.
 *
 * @return This function returns kStatus_Success after successfully executed.
 *         Appropriate kStatus_ prefixed errors will be given when an error occurred.
 *         Please refer to the corresponding modules for an specific error coding.
 */
status_t ST7796S_InvertDisplay(st7796s_handle_t *handle, bool invert);

/*!
 * @brief Enable or disable the display output.
 *
 * This function enables or disables the panel driving output. When driving
 * output is enabled, the panel will scanning out the frame buffer content.
 * When driving output is disabled, the panel will display a blank screen
 * depending the panel technology (un-driven state).
 *
 * @param handle ST7796S handle structure.
 * @param enable Whether to enable driving output
 *
 * @return This function returns kStatus_Success after successfully executed.
 *         Appropriate kStatus_ prefixed errors will be given when an error occurred.
 *         Please refer to the corresponding modules for an specific error coding.
 */
status_t ST7796S_EnableDisplay(st7796s_handle_t *handle, bool enable);

/*!
 * @brief Set display pixel format.
 *
 * This function set the pixel format of the controller. The controller supports one of the
 * pixel formats defined in @ref st7796s_pixel_format_t. This does not affect the hardware interface selection.
 *
 * @param handle ST7796S handle structure.
 * @param pixelFormat Pixel format to be set
 *
 * @return This function returns kStatus_Success after successfully executed.
 *         Appropriate kStatus_ prefixed errors will be given when an error occurred.
 *         Please refer to the corresponding modules for an specific error coding.
 */
status_t ST7796S_SetPixelFormat(st7796s_handle_t *handle, st7796s_pixel_format_t pixelFormat);

/*!
 * @brief Configure the Tearing Effect (TE) line output.
 *
 * This function configures the TE line output to one of the following states:
 * Disabled: No TE output
 * VSync: TE asserts on the V-blanking periods only
 * HVSync: TE asserts on both H-blanking periods and V-blanking periods
 * Refer to @ref st7796s_te_config_t.
 *
 * @param handle ST7796S handle structure.
 * @param teConfig TE line configuration to be set.
 *
 * @return This function returns kStatus_Success after successfully executed.
 *         Appropriate kStatus_ prefixed errors will be given when an error occurred.
 *         Please refer to the corresponding modules for an specific error coding.
 */
status_t ST7796S_SetTEConfig(st7796s_handle_t *handle, st7796s_te_config_t teConfig);

/*!
 * @brief Set panel configurations.
 *
 * This function configures some vital parameters of the display panel. Please refer to
 * @ref st7796s_config_t for available configuration items.
 *
 * @param handle ST7796S handle structure.
 * @param config Pointer to the configuration structure.
 *
 * @return This function returns kStatus_Success after successfully executed.
 *         Appropriate kStatus_ prefixed errors will be given when an error occurred.
 *         Please refer to the corresponding modules for an specific error coding.
 */
status_t ST7796S_Config(st7796s_handle_t *handle, const st7796s_config_t *config);

/*!
 * @brief Select draw area of the frame buffer.
 *
 * This function will set the internal write area to the rectangle specified by the coordinate.
 * After the write area is set, pixels will be stored start from the top left of the area, and
 * will be wrapped back to top left if more pixels are written to the frame memory. This function
 * internally reset the write pointer to the start point.
 *
 * @param handle ST7796S handle structure.
 * @param startX X start point
 * @param startY Y start point
 * @param endX X end point
 * @param endY Y end point
 *
 * @return This function returns kStatus_Success after successfully executed.
 *         Appropriate kStatus_ prefixed errors will be given when an error occurred.
 *         Please refer to the corresponding modules for an specific error coding.
 */
status_t ST7796S_SelectArea(st7796s_handle_t *handle, uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY);

/*!
 * @brief Write pixels to LCD frame buffer
 *
 * This function will perform a write to the internal frame buffer on the ST7796S controller. The start and end points
 * are provided by previous call to the ST7796S, and will self-increment after each write. This function will return
 * immediately after called, and user has to set a callback using @ref ST7796S_SetMemoryDoneCallback to check the
 * result and get notified when the background DMA operation is completed.
 *
 * @param handle ST7796S handle structure.
 * @param pixels buffer to be updated to the controller
 * @param len pixel count.
 *
 * @return This function returns kStatus_Success after successfully executed.
 *         Appropriate kStatus_ prefixed errors will be given when an error occurred.
 *         Please refer to the corresponding modules for an specific error coding.
 */
status_t ST7796S_WritePixels(st7796s_handle_t *handle, uint16_t *pixels, uint32_t len);

#if MCUX_DBI_LEGACY
/*!
 * @brief Set the memory access done callback.
 *
 * @param handle ST7796S handle structure.
 * @param callback Callback function when the video memory operation finished.
 *        @ref ST7796S_WritePixels is non-blocking function, upper layer is notified
 *        by this callback function after transfer done.
 * @param userData Parameter of @ref dbi_mem_done_callback_t.
 */
void ST7796S_SetMemoryDoneCallback(st7796s_handle_t *handle, dbi_mem_done_callback_t callback, void *userData);
#endif

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif // _FSL_ST7796S_H_
