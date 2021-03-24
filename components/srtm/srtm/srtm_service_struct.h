/*
 * Copyright 2017, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SRTM_SERVICE_STRUCT_H__
#define __SRTM_SERVICE_STRUCT_H__

#include "srtm_defs.h"
#include "srtm_list.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/**
 * @brief SRTM service struct
 */
struct _srtm_service
{
    srtm_list_t node; /*!< SRTM service list node to link to a list */
    srtm_dispatcher_t dispatcher;
    uint8_t category;

    void (*destroy)(srtm_service_t service);
    srtm_status_t (*request)(srtm_service_t service, srtm_request_t request);
    srtm_status_t (*notify)(srtm_service_t service, srtm_notification_t notification);
};

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Compare message and service version to see if the service can serve.
 *
 * @param service SRTM service handle.
 * @param msg The message to check.
 * @param svcVer The service version to check.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_Service_CheckVersion(srtm_service_t service, srtm_message_t msg, uint16_t svcVer);

#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* __SRTM_SERVICE_STRUCT_H__ */
