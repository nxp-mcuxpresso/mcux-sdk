/*
 * Copyright 2019-2022 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_SMARTDMA_H_
#define _FSL_SMARTDMA_H_

#include "fsl_common.h"

/*!
 * @addtogroup smartdma
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief SMARTDMA driver version */
#define FSL_SMARTDMA_DRIVER_VERSION (MAKE_VERSION(2, 7, 0))
/*@}*/

/*! @brief The firmware used for display. */
extern const uint8_t s_smartdmaDisplayFirmware[];

/*! @brief The s_smartdmaDisplayFirmware firmware memory address. */
#define SMARTDMA_DISPLAY_MEM_ADDR 0x24100000

/*! @brief Size of s_smartdmaDisplayFirmware */
#define SMARTDMA_DISPLAY_FIRMWARE_SIZE (s_smartdmaDisplayFirmwareSize)

/*! @brief Size of s_smartdmaDisplayFirmware */
extern const uint32_t s_smartdmaDisplayFirmwareSize;

/*! @brief Compatibility redefinition. */
#define s_smartdmaFlexioMcuLcdFirmware       s_smartdmaDisplayFirmware
#define SMARTDMA_FLEXIO_MCULCD_MEM_ADDR      SMARTDMA_DISPLAY_MEM_ADDR
#define SMARTDMA_FLEXIO_MCULCD_FIRMWARE_SIZE SMARTDMA_DISPLAY_FIRMWARE_SIZE
#define s_smartdmaFlexioMcuLcdFirmwareSize   s_smartdmaDisplayFirmwareSize

/*!
 * @brief The API index when using s_smartdmaFlexioMcuLcdFirmware.
 */
enum _smartdma_flexio_mculcd_api
{
    kSMARTDMA_FlexIO_DMA_Endian_Swap = 0U,
    kSMARTDMA_FlexIO_DMA_Reverse32,
    kSMARTDMA_FlexIO_DMA,
    kSMARTDMA_FlexIO_DMA_Reverse,              /*!< Send data to FlexIO with reverse order. */
    kSMARTDMA_RGB565To888,                     /*!< Convert RGB565 to RGB888 and save to output memory, use parameter
                                                  smartdma_rgb565_rgb888_param_t. */
    kSMARTDMA_FlexIO_DMA_RGB565To888,          /*!< Convert RGB565 to RGB888 and send to FlexIO, use parameter
                                                  smartdma_flexio_mculcd_param_t. */
    kSMARTDMA_FlexIO_DMA_ARGB2RGB,             /*!< Convert ARGB to RGB and send to FlexIO, use parameter
                                                  smartdma_flexio_mculcd_param_t. */
    kSMARTDMA_FlexIO_DMA_ARGB2RGB_Endian_Swap, /*!< Convert ARGB to RGB, then swap endian, and send to FlexIO, use
                                                 parameter smartdma_flexio_mculcd_param_t. */
    kSMARTDMA_FlexIO_DMA_ARGB2RGB_Endian_Swap_Reverse, /*!< Convert ARGB to RGB, then swap endian and reverse, and send
                                                 to FlexIO, use parameter smartdma_flexio_mculcd_param_t. */
    kSMARTDMA_MIPI_RGB565_DMA,        /*!< Send RGB565 data to MIPI DSI, use parameter smartdma_dsi_param_t. */
    kSMARTDMA_MIPI_RGB565_DMA2D,      /*!< Send RGB565 data to MIPI DSI, use parameter smartdma_dsi_2d_param_t. */
    kSMARTDMA_MIPI_RGB888_DMA,        /*!< Send RGB888 data to MIPI DSI, use parameter smartdma_dsi_param_t. */
    kSMARTDMA_MIPI_RGB888_DMA2D,      /*!< Send RGB565 data to MIPI DSI, use parameter smartdma_dsi_2d_param_t. */
    kSMARTDMA_MIPI_XRGB2RGB_DMA,      /*!< Send XRGB8888 data to MIPI DSI, use parameter smartdma_param_t */
    kSMARTDMA_MIPI_XRGB2RGB_DMA2D,    /*!< Send XRGB8888 data to MIPI DSI, use parameter smartdma_dsi_2d_param_t. */
    kSMARTDMA_MIPI_RGB565_R180_DMA,   /*!< Send RGB565 data to MIPI DSI, Rotate 180, use parameter smartdma_dsi_param_t.
                                       */
    kSMARTDMA_MIPI_RGB888_R180_DMA,   /*!< Send RGB888 data to MIPI DSI, Rotate 180, use parameter smartdma_dsi_param_t.
                                       */
    kSMARTDMA_MIPI_XRGB2RGB_R180_DMA, /*!< Send XRGB8888 data to MIPI DSI, Rotate 180, use parameter
                                         smartdma_dsi_param_t */

    kSMARTDMA_FlexIO_DMA_ONELANE, /*!< FlexIO DMA for one SHIFTBUF, Write Data to SHIFTBUF[OFFSET] */
};

/*!
 * @brief Parameter for FlexIO MCULCD except kSMARTDMA_FlexIO_DMA_ONELANE
 */
typedef struct _smartdma_flexio_mculcd_param
{
    uint32_t *p_buffer;
    uint32_t buffersize;
    uint32_t *smartdma_stack;
} smartdma_flexio_mculcd_param_t;

/*!
 * @brief Parameter for kSMARTDMA_FlexIO_DMA_ONELANE
 */
typedef struct _smartdma_flexio_onelane_mculcd_param
{
    uint32_t *p_buffer;
    uint32_t buffersize;
    uint32_t offset;
    uint32_t *smartdma_stack;
} smartdma_flexio_onelane_mculcd_param_t;

/*!
 * @brief Parameter for MIPI DSI
 */
typedef struct _smartdma_dsi_param
{
    /*! Pointer to the buffer to send. */
    const uint8_t *p_buffer;
    /*! Buffer size in byte. */
    uint32_t buffersize;
    /*! Stack used by SMARTDMA. */
    uint32_t *smartdma_stack;
    /*!
     * If set to 1, the pixels are filled to MIPI DSI FIFO directly.
     * If set to 0, the pixel bytes are swapped then filled to
     * MIPI DSI FIFO. For example, when set to 0 and frame buffer pixel
     * format is RGB565:
     * LSB                                           MSB
     * B0 B1 B2 B3 B4 G0 G1 G2 | G3 G4 G5 R0 R1 R2 R3 R4
     * Then the pixel filled to DSI FIFO is:
     * LSB                                           MSB
     * G3 G4 G5 R0 R1 R2 R3 R4 | B0 B1 B2 B3 B4 G0 G1 G2
     */
    uint32_t disablePixelByteSwap;
} smartdma_dsi_param_t;

typedef struct _smartdma_dsi_2d_param_t
{
    /*! Pointer to the buffer to send. */
    const uint8_t *p_buffer;
    /*! SRC data transfer in a minor loop */
    uint32_t minorLoop;
    /*! SRC data offset added after a minor loop */
    uint32_t minorLoopOffset;
    /*! SRC data transfer in a major loop */
    uint32_t majorLoop;
    /*! Stack used by SMARTDMA. */
    uint32_t *smartdma_stack;
    /*!
     * If set to 1, the pixels are filled to MIPI DSI FIFO directly.
     * If set to 0, the pixel bytes are swapped then filled to
     * MIPI DSI FIFO. For example, when set to 0 and frame buffer pixel
     * format is RGB565:
     * LSB                                           MSB
     * B0 B1 B2 B3 B4 G0 G1 G2 | G3 G4 G5 R0 R1 R2 R3 R4
     * Then the pixel filled to DSI FIFO is:
     * LSB                                           MSB
     * G3 G4 G5 R0 R1 R2 R3 R4 | B0 B1 B2 B3 B4 G0 G1 G2
     */
    uint32_t disablePixelByteSwap;
} smartdma_dsi_2d_param_t;

/*!
 * @brief Parameter for RGB565To888
 */
typedef struct _smartdma_rgb565_rgb888_param
{
    uint32_t *inBuf;
    uint32_t *outBuf;
    uint32_t buffersize;
    uint32_t *smartdma_stack;
} smartdma_rgb565_rgb888_param_t;

/*! @brief Callback function prototype for the smartdma driver. */
typedef void (*smartdma_callback_t)(void *param);

/*******************************************************************************
 * APIs
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Initialize the SMARTDMA.
 *
 * @param apiMemAddr The address firmware will be copied to.
 * @param firmware The firmware to use.
 * @param firmwareSizeByte Size of firmware.
 * @deprecated Do not use this function. It has been superceded by @ref GPIO_PinWrite.
 * @ref SMARTDMA_InitWithoutFirmware and @ref SMARTDMA_InstallFirmware.
 */
void SMARTDMA_Init(uint32_t apiMemAddr, const void *firmware, uint32_t firmwareSizeByte);

/*!
 * @brief Initialize the SMARTDMA.
 *
 * This function is similar with @ref SMARTDMA_Init, the difference is this function
 * does not install the firmware, the firmware could be installed using
 * @ref SMARTDMA_InstallFirmware.
 */
void SMARTDMA_InitWithoutFirmware(void);

/*!
 * @brief Install the firmware.
 *
 * @param apiMemAddr The address firmware will be copied to.
 * @param firmware The firmware to use.
 * @param firmwareSizeByte Size of firmware.
 * @note Only call this function when SMARTDMA is not busy.
 */
void SMARTDMA_InstallFirmware(uint32_t apiMemAddr, const void *firmware, uint32_t firmwareSizeByte);

/*!
 * @brief Install the complete callback function.
 *
 * @param callback The callback called when smartdma program finished.
 * @param param Parameter for the callback.
 * @note Only call this function when SMARTDMA is not busy.
 */
void SMARTDMA_InstallCallback(smartdma_callback_t callback, void *param);

/*!
 * @brief Boot the SMARTDMA to run program.
 *
 * @param apiIndex Index of the API to call.
 * @param pParam Pointer to the parameter.
 * @param mask Value set to SMARTDMA_ARM2SMARTDMA[0:1].
 * @note Only call this function when SMARTDMA is not busy.
 */
void SMARTDMA_Boot(uint32_t apiIndex, void *pParam, uint8_t mask);

/*!
 * @brief Deinitialize the SMARTDMA.
 */
void SMARTDMA_Deinit(void);

/*!
 * @brief Reset the SMARTDMA.
 */
void SMARTDMA_Reset(void);

/*!
 * @brief SMARTDMA IRQ.
 */
void SMARTDMA_HandleIRQ(void);

#if defined(__cplusplus)
}
#endif

/* @} */

#endif /* _FSL_SMARTDMA_H_ */
