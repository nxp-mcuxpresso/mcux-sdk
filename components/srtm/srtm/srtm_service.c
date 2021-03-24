/*
 * Copyright 2017, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>

#include "srtm_service.h"
#include "srtm_service_struct.h"
#include "srtm_message.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
void SRTM_Service_Destroy(srtm_service_t service)
{
    assert(service);
    assert(service->destroy);
    service->destroy(service);
}

srtm_status_t SRTM_Service_Request(srtm_service_t service, srtm_request_t request)
{
    assert(service);
    assert(service->request);

    return service->request(service, request);
}

srtm_status_t SRTM_Service_Notify(srtm_service_t service, srtm_notification_t notification)
{
    assert(service);
    assert(service->notify);

    return service->notify(service, notification);
}

srtm_status_t SRTM_Service_CheckVersion(srtm_service_t service, srtm_message_t msg, uint16_t svcVer)
{
    uint16_t msgVer = SRTM_CommMessage_GetVersion(msg);

    if (SRTM_MESSAGE_MAJOR_VERSION(msgVer) != SRTM_MESSAGE_MAJOR_VERSION(svcVer))
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN,
                           "SRTM_WARN: SRTM_Service_CheckVersion mismatch req %d, service %d!\r\n", msgVer, svcVer);
        return SRTM_Status_ServiceVerMismatch;
    }

    return SRTM_Status_Success;
}
