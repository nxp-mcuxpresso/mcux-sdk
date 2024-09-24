/*
 * Copyright 2019, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_DBI_H_
#define _FSL_DBI_H_

#include "fsl_common.h"
#include "fsl_video_common.h"

/*!
 * @addtogroup dbi
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Use the legacy way */
#ifndef MCUX_DBI_LEGACY
#define MCUX_DBI_LEGACY 1
#endif

#ifndef MCUX_DBI_IFACE_ENABLE_READ
#define MCUX_DBI_IFACE_ENABLE_READ 0
#endif

/*!
 * @brief MIPI DBI command, same with the MIPI DSC (Display Command Set)
 */
enum _mipi_dbi_cmd
{
    kMIPI_DBI_Nop                  = 0x00u,
    kMIPI_DBI_SoftReset            = 0x01u,
    kMIPI_DBI_GetRedChannel        = 0x06u,
    kMIPI_DBI_GetGreenChannel      = 0x07u,
    kMIPI_DBI_GetBlueChannel       = 0x08u,
    kMIPI_DBI_GetPowerMode         = 0x0Au,
    kMIPI_DBI_GetAddressMode       = 0x0Bu,
    kMIPI_DBI_GetPixelFormat       = 0x0Cu,
    kMIPI_DBI_GetDisplayMode       = 0x0Du,
    kMIPI_DBI_GetSignalMode        = 0x0Eu,
    kMIPI_DBI_GetDiagnosticResult  = 0x0Fu,
    kMIPI_DBI_EnterSleepMode       = 0x10u,
    kMIPI_DBI_ExitSleepMode        = 0x11u,
    kMIPI_DBI_EnterPartialMode     = 0x12u,
    kMIPI_DBI_EnterNormalMode      = 0x13u,
    kMIPI_DBI_ExitInvertMode       = 0x20u,
    kMIPI_DBI_EnterInvertMode      = 0x21u,
    kMIPI_DBI_SetGammaCurve        = 0x26u,
    kMIPI_DBI_SetDisplayOff        = 0x28u,
    kMIPI_DBI_SetDisplayOn         = 0x29u,
    kMIPI_DBI_SetColumnAddress     = 0x2au,
    kMIPI_DBI_SetPageAddress       = 0x2bu,
    kMIPI_DBI_WriteMemoryStart     = 0x2Cu,
    kMIPI_DBI_WriteLUT             = 0x2Du,
    kMIPI_DBI_ReadMemoryStart      = 0x2Eu,
    kMIPI_DBI_SetPartialRows       = 0x30u,
    kMIPI_DBI_SetPartialColumns    = 0x31u,
    kMIPI_DBI_SetScrollArea        = 0x33u,
    kMIPI_DBI_SetTearOff           = 0x34u,
    kMIPI_DBI_SetTearOn            = 0x35u,
    kMIPI_DBI_SetAddressMode       = 0x36u,
    kMIPI_DBI_SetScrollStart       = 0x37u,
    kMIPI_DBI_ExitIdleMode         = 0x38u,
    kMIPI_DBI_EnterIdleMode        = 0x39u,
    kMIPI_DBI_SetPixelFormat       = 0x3Au,
    kMIPI_DBI_WriteMemoryContinue  = 0x3Cu,
    kMIPI_DBI_Set3DControl         = 0x3Du,
    kMIPI_DBI_ReadMemoryContinue   = 0x3Eu,
    kMIPI_DBI_Get3DControl         = 0x3Fu,
    kMIPI_DBI_SetVsyncTiming       = 0x40u,
    kMIPI_DBI_SetTearScanline      = 0x44u,
    kMIPI_DBI_GetScanline          = 0x45u,
    kMIPI_DBI_SetDisplayBrightness = 0x51u,
    kMIPI_DBI_GetDisplayBrightness = 0x52u,
    kMIPI_DBI_WriteControlDisplay  = 0x53u,
    kMIPI_DBI_GetControlDisplay    = 0x54u,
    kMIPI_DBI_WritePowerSave       = 0x55u,
    kMIPI_DBI_GetPowerSave         = 0x56u,
    kMIPI_DBI_SetCABCMinBrightness = 0x5Eu,
    kMIPI_DBI_GetCABCMinBrightness = 0x5Fu,
    kMIPI_DBI_ReadDDBStart         = 0xA1u,
    kMIPI_DBI_ReadDDBContinue      = 0xA8u,
};

/*!
 * @brief Callback function when the writeMemory or readMemory finished.
 *
 * If transfer done successfully, the @p status is kStatus_Success.
 */
typedef void (*dbi_mem_done_callback_t)(status_t status, void *userData);

#if MCUX_DBI_LEGACY
/*!
 * @brief DBI interface (MCU LCD) transfer operation.
 *
 * The API @ref writeCommand and @ref writeData are blocking method, they returns
 * only when transfer finished. They are usually used to transfer small data, for
 * example, sending the cofigurations.
 *
 * The API @ref writeMemory and @ref readMemory are non-blocking method, they are
 * used to write or read the LCD contoller video memory. These APIs start transfer
 * and return directly, upper layer could be notified by callback when transfer
 * done. The callback function is set by @ref setMemoryDoneCallback.
 */
typedef struct _dbi_xfer_ops
{
    status_t (*writeCommand)(void *dbiXferHandle, uint32_t command);           /*!< Write command. */
    status_t (*writeData)(void *dbiXferHandle, void *data, uint32_t len_byte); /*!< Write data. */
    status_t (*writeCommandData)(void *dbiXferHandle,
                                 uint32_t command,
                                 const void *data,
                                 uint32_t len_byte); /*!< Write command and data in blocking way. */
    status_t (*writeMemory)(void *dbiXferHandle,
                            uint32_t command,
                            const void *data,
                            uint32_t len_byte); /*!< Write to the memory. */
    status_t (*readMemory)(void *dbiXferHandle,
                           uint32_t command,
                           void *data,
                           uint32_t len_byte); /*!< Read from the memory. */
    void (*setMemoryDoneCallback)(void *dbiXferHandle,
                                  dbi_mem_done_callback_t callback,
                                  void *userData); /*!< Set the memory access done callback. */
} dbi_xfer_ops_t;

#else /* not MCUX_DBI_LEGACY */

/* Define a function pointer prototype to toggle D/C pin. */
typedef void (*dbi_dc_pin_func_t)(bool high);

typedef struct _dbi_iface dbi_iface_t;

/*!
 * @brief DBI interface (MCU LCD) transfer operation.
 *
 * The API @ref writeCommandData and @ref readData are blocking method, they returns
 * only when transfer finished. They are usually used to transfer small data, for
 * example, sending the cofigurations, read LCD controller ID to verify the connection.
 *
 * The API @ref writeMemory is non-blocking method, it is to write the LCD contoller
 * video memory(or graphics memory, GRAM). These APIs start transfer
 * and return directly, upper layer could be notified by callback when transfer
 * done. The callback function is set by @ref setMemoryDoneCallback.
 */
typedef struct _dbi_iface_xfer_ops
{
    status_t (*writeCommandData)(dbi_iface_t *dbiIface,
                                 uint32_t command,
                                 const void *data,
                                 uint32_t len_byte); /*!< Write command and data in blocking way. MUST Have */

#if MCUX_DBI_IFACE_ENABLE_READ
    status_t (*readData)(dbi_iface_t *dbiIface,
                         uint32_t command,
                         void *data,
                         uint32_t len_byte); /*!< Read data from LCD controller in blocking way. It can be
                         used to read ID of LCD controller. Optional. */
#endif /* MCUX_DBI_IFACE_ENABLE_READ */

    status_t (*writeMemory)(dbi_iface_t *dbiIface,
                            uint32_t command,
                            const void *data,
                            uint32_t len_byte); /*!< Write to the memory. MUST Have */

    status_t (*writeMemory2D)(dbi_iface_t *dbiIface,
                              uint32_t command,
                              const void *data,
                              uint32_t len_byte,
                              uint32_t stride); /*!< Write to the memory. Optional. */
} dbi_iface_xfer_ops_t;

typedef struct _dbi_config_ops
{
    status_t (*setPixelFormat)(dbi_iface_t *dbiIface, video_pixel_format_t format);
} dbi_config_ops_t;

/*@brief DBI transfer interface.*/
struct _dbi_iface
{
    const dbi_iface_xfer_ops_t *xferOps; /*!< Pointer to the DBI transfer operations. */
    const dbi_config_ops_t
        *configOps; /*!< Pointer to the DBI configuration operations. Can be NULL if the IP does not support. */
    void *prvData;  /*!< DBI interface specific private data. */
    dbi_mem_done_callback_t memDoneCallback; /*!< The callback function when video memory access done. */
    void *memDoneCallbackParam;              /*!< Parameter of @ref memDoneCallback */
};

#endif /* MCUX_DBI_LEGACY */

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

#if !MCUX_DBI_LEGACY
/*!
 * @brief Write command and data to the LCD controller.
 *
 * @param[in] dbiIface Pointer to the DBI device.
 * @param[in] command The command to be sent.
 * @param[in] data The data to be sent.
 * @param[in] length The length of the data to be sent.
 * @return Execution status.
 */
static inline status_t DBI_IFACE_WriteCmdData(dbi_iface_t *dbiIface, uint8_t cmd, const uint8_t *data, uint32_t length)
{
    return dbiIface->xferOps->writeCommandData(dbiIface, cmd, data, length);
}

#if MCUX_DBI_IFACE_ENABLE_READ
/*!
 * @brief Read data from the LCD controller.
 *
 * @param[in] dbiIface Pointer to the DBI interface.
 * @param[in] command The command to be sent.
 * @param[out] data The data to be read.
 * @param[in] length The length of the data to be read.
 * @return Execution status.
 */
static inline status_t DBI_IFACE_ReadData(dbi_iface_t *dbiIface, uint8_t cmd, uint8_t *data, uint32_t length)
{
    return dbiIface->xferOps->readData(dbiIface, cmd, data, length);
}
#endif

/*!
 * @brief Soft reset the LCD controller.
 *
 * @param[in] dbiIface Pointer to the DBI interface.
 * @return Execution status.
 */
static inline status_t DBI_IFACE_SoftReset(dbi_iface_t *dbiIface)
{
    return dbiIface->xferOps->writeCommandData(dbiIface, kMIPI_DBI_SoftReset, NULL, 0);
}

/*!
 * @brief Set the display on of off.
 *
 * @param[in] dbiIface Pointer to the DBI interface.
 * @param[in] on True for display on, false for display off.
 */
static inline status_t DBI_IFACE_SetDiplayOn(dbi_iface_t *dbiIface, bool on)
{
    uint8_t cmd = (on ? kMIPI_DBI_SetDisplayOn : kMIPI_DBI_SetDisplayOff);

    return dbiIface->xferOps->writeCommandData(dbiIface, cmd, NULL, 0);
}

/*!
 * @brief Select the area to update next.
 *
 * @param[in] dbiIface Pointer to the DBI interface.
 * @param[in] startX The start X position of the area.
 * @param[in] startY The start Y position of the area.
 * @param[in] endX The end X position of the area.
 * @param[in] endY The end Y position of the area.
 * @return Execution status.
 */
status_t DBI_IFACE_SelectArea(dbi_iface_t *dbiIface, uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY);

/*!
 * @brief Set the pixel format of the source image.
 *
 * @param[in] dbiIface Pointer to the DBI interface.
 * @param[in] format Pixel format.
 * @return Execution status.
 */
static inline status_t DBI_IFACE_SetPixelFormat(dbi_iface_t *dbiIface, video_pixel_format_t format)
{
    if (dbiIface->configOps->setPixelFormat != NULL)
    {
        return dbiIface->configOps->setPixelFormat(dbiIface, format);
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * @brief Write data to the LCD controller video memory.
 *
 * @param[in] dbiIface Pointer to the DBI device.
 * @param[in] data The data to be sent.
 * @param[in] length The length of the data to be sent.
 * @return Execution status.
 * @note This function is non-blocking, upper layer could be notified by callback when transfer done.
 */
static inline status_t DBI_IFACE_WriteMemory(dbi_iface_t *dbiIface, const uint8_t *data, uint32_t length)
{
    return dbiIface->xferOps->writeMemory(dbiIface, kMIPI_DBI_WriteMemoryStart, data, length);
}

/*!
 * @brief Write data to the LCD controller video memory in 2-dimensions.
 *
 * The stride bytes are larger than the bytes of each line. Each line of pixel is interleaved.
 *
 * @param[in] dbiIface Pointer to the DBI device.
 * @param[in] data The data to be sent.
 * @param[in] length The length of the data to be sent.
 * @return Execution status.
 * @note This function is non-blocking, upper layer could be notified by callback when transfer done.
 */
static inline status_t DBI_IFACE_WriteMemory2D(dbi_iface_t *dbiIface,
                                               const uint8_t *data,
                                               uint32_t length,
                                               uint32_t stride)
{
    if (dbiIface->xferOps->writeMemory2D != NULL)
    {
        return dbiIface->xferOps->writeMemory2D(dbiIface, kMIPI_DBI_WriteMemoryStart, data, length, stride);
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * @brief Write data to the LCD controller video memory.
 *
 * @param[in] dbiIface Pointer to the DBI device.
 * @param[in] data The data to be sent.
 * @param[in] length The length of the data to be sent.
 * @return Execution status.
 * @note This function is non-blocking, upper layer could be notified by callback when transfer done.
 */
static inline status_t DBI_IFACE_WriteMemoryContinue(dbi_iface_t *dbiIface, const uint8_t *data, uint32_t length)
{
    return dbiIface->xferOps->writeMemory(dbiIface, kMIPI_DBI_WriteMemoryContinue, data, length);
}

/*!
 * @brief Register the callback function called when memory function done.
 *
 * The memory write function is non-blocking function, when transaction
 * finished, callback is called to inform higher layer.
 *
 * @param[in] dbiIface Pointer to the DBI device.
 * @param[in] callback The callback when memory read or write finished.
 * @param[in] userData Parameter of the callback.
 */
void DBI_IFACE_SetMemoryDoneCallback(dbi_iface_t *dbiIface, dbi_mem_done_callback_t callback, void *userData);
#endif /* !MCUX_DBI_LEGACY */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_DBI_H_ */
