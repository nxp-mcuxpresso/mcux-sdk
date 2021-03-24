/*
 * Copyright 2017, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SRTM_SERVICE_H__
#define __SRTM_SERVICE_H__

#include "srtm_defs.h"

/*!
 * @addtogroup srtm
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
 * @brief Destroy SRTM service.
 *
 * @param service SRTM service to destroy.
 */
void SRTM_Service_Destroy(srtm_service_t service);

/*!
 * @brief Call SRTM service for a request.
 *
 * @param service SRTM service to call.
 * @param request SRTM request to process.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_Service_Request(srtm_service_t service, srtm_request_t request);

/*!
 * @brief Call SRTM service for a notification.
 *
 * @param service SRTM service to call.
 * @param notification SRTM notification to process.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_Service_Notify(srtm_service_t service, srtm_notification_t notification);

#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* __SRTM_SERVICE_H__ */
