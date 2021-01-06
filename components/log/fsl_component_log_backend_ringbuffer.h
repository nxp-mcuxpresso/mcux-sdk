/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef __FSL_COMPONENT_LOG_BACKEND_RINGBUFFER_H__
#define __FSL_COMPONENT_LOG_BACKEND_RINGBUFFER_H__

#include "fsl_common.h"

/*
 * Log backend ring buffer usage:
 * Since, the multiple backend feature is supported by log component, the
 * backend should be initialized individually in application by calling
 * backend initialization function (for example,
 * LOG_InitBackendRingbuffer id the backend of log component is ring
 * buffer).
 * Also, the backend could be de-initialized by calling backend
 * de-initialization function (for example, LOG_DeinitBackendRingbuffer
 * is the backend of log component is ring buffer).
 */

/*!
 * @addtogroup fsl_component_log_backend_ring_buffer
 * @ingroup fsl_component_log
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief ring buffer configuration structure */
typedef struct log_backend_ring_buffer_config
{
    uint8_t *ringBuffer;     /*!< ring buffer address */
    size_t ringBufferLength; /*!< ring buffer length */
} log_backend_ring_buffer_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* _cplusplus */

/*!
 * @brief Initializes the backend ringbuffer for log component.
 *
 * @details This function initializes the backend ringbuffer for log component.
 * The function should be called in application layer. The function
 * should be called after the log component has been initialized
 * (the function LOG_Init has been called).
 *
 * @param config Ring buffer configuration for backend ring buffer.
 */
void LOG_InitBackendRingbuffer(log_backend_ring_buffer_config_t *config);

/*!
 * @brief De-initializes the backend ringbuffer for log component.
 *
 * @details This function de-initializes the backend ringbuffer for log component.
 */
void LOG_DeinitBackendRingbuffer(void);

#if defined(__cplusplus)
}
#endif
/*! @} */

#endif /* __FSL_COMPONENT_LOG_BACKEND_RINGBUFFER_H__ */
