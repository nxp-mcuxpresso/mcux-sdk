/*
 * Copyright 2017-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_WM8524_H_
#define _FSL_WM8524_H_

#include "fsl_common.h"

/*!
 * @addtogroup wm8524
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @name Driver version */
/*@{*/
/*! @brief WM8524 driver version 2.1.1. */
#define FSL_WM8524_DRIVER_VERSION (MAKE_VERSION(2, 1, 1))
/*@}*/

/*!< mute control io function pointer */
typedef void (*wm8524_setMuteIO)(uint32_t output);
/*!< format control io function pointer */
typedef void (*wm8524_setProtocolIO)(uint32_t output);

/*! @brief The audio data transfer protocol. */
typedef enum _wm8524_protocol
{
    kWM8524_ProtocolLeftJustified  = 0x0, /*!< Left justified mode */
    kWM8524_ProtocolI2S            = 0x1, /*!< I2S mode */
    kWM8524_ProtocolRightJustified = 0x2, /*!< Right justified mode */
} wm8524_protocol_t;

/*! @brief wm8524 mute operation */
enum _wm8524_mute_control
{
    kWM8524_Mute   = 0U, /*!< mute left and right channel DAC */
    kWM8524_Unmute = 1U, /*!< unmute left and right channel DAC */
};

/*!< @brief WM8524 configurations */
typedef struct _wm8524_config
{
    wm8524_setMuteIO setMute;         /*!< mute io control function pointer */
    wm8524_setProtocolIO setProtocol; /*!< format io control function pointer */
    wm8524_protocol_t protocol;       /*!< Protocol of the codec */
} wm8524_config_t;

/*!@brief WM8524 handler */
typedef struct _wm8524_handle_t
{
    wm8524_config_t *config; /*!< wm8524 config pointer */
} wm8524_handle_t;
/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes WM8524.
 *
 * @param handle WM8524 handle structure.
 * @param config WM8524 configure structure.
 * @return kStatus_Success.
 */
status_t WM8524_Init(wm8524_handle_t *handle, wm8524_config_t *config);

/*!
 * @brief Configure WM8524 audio protocol.
 *
 * @param handle WM8524 handle structure.
 * @param protocol WM8524 configuration structure.
 */
void WM8524_ConfigFormat(wm8524_handle_t *handle, wm8524_protocol_t protocol);

/*!
 * @brief Sets the codec mute state.
 *
 * @param handle WM8524 handle structure.
 * @param isMute true means mute, false means normal.
 */
void WM8524_SetMute(wm8524_handle_t *handle, bool isMute);

#if defined(__cplusplus)
}
#endif

/*! @} */
#endif /* _FSL_WM8524_H_ */
