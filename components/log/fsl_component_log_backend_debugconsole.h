/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef __FSL_COMPONENT_LOG_BACKEND_DEBUGCONSOLE_H__
#define __FSL_COMPONENT_LOG_BACKEND_DEBUGCONSOLE_H__

#include "fsl_common.h"

/*
 * Log backend debug console usage:
 * Since, the multiple backend feature is supported by log component, the
 * backend should be initialized individually in application by calling
 * backend initialization function (for example,
 * LOG_InitBackendDebugconsole id the backend of log component is debug
 * console).
 * Also, the backend could be de-initialized by calling backend
 * de-initialization function (for example, LOG_DeinitBackendDebugconsole
 * is the backend of log component is debug console).
 */

/*!
 * @addtogroup fsl_component_log_backend_debug_console
 * @ingroup fsl_component_log
 * @{
 */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* _cplusplus */

/*!
 * @brief Initializes the backend debugconsole for log component.
 *
 * @details This function initializes the backend debugconsole for log component.
 * The function should be called in application layer. The function
 * should be called after the log component has been initialized
 * (the function LOG_Init has been called).
 */
void LOG_InitBackendDebugconsole(void);

/*!
 * @brief De-initializes the backend debugconsole for log component.
 *
 * @details This function de-initializes the backend debugconsole for log component.
 */
void LOG_DeinitBackendDebugconsole(void);

#if defined(__cplusplus)
}
#endif
/*! @} */

#endif /* __FSL_COMPONENT_LOG_BACKEND_DEBUGCONSOLE_H__ */
