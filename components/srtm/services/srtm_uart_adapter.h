/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SRTM_UART_ADAPTER_H__
#define __SRTM_UART_ADAPTER_H__

#include "srtm_uart_service.h"
#include "fsl_component_serial_manager.h"

/*!
 * @addtogroup srtm_service
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Create Uart adapter.
 *
 */
srtm_uart_adapter_t SRTM_UartAdapter_Create(serial_handle_t serial_handles[], serial_write_handle_t write_handles[], serial_read_handle_t read_handles[], uint32_t handleNum);

/*!
 * @brief Destroy UART adapter.
 *
 * @param adapter UART adapter to destroy.
 */
void SRTM_UartAdapter_Destroy(srtm_uart_adapter_t adapter);

#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* __SRTM_UART_ADAPTER_H__ */
