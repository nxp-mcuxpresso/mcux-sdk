/*
 * Copyright 2022-2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_silicon_id.h"
#if defined(SIM)
#include "fsl_sim.h"
#elif defined(FSL_FEATURE_SYSCON_IAP_ENTRY_LOCATION)
#include "fsl_iap.h"
#elif (defined(FSL_FEATURE_SYSCON_ROMAPI) && (FSL_FEATURE_SYSCON_ROMAPI == 1))
#include "fsl_flash.h"
#include "fsl_flash_ffr.h"
#endif

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "component.silicon_id"
#endif

status_t SILICONID_GetID(uint8_t *siliconId, uint32_t *idLen)
{
    assert((siliconId != NULL) && (idLen != NULL) && (*idLen != 0U));

    status_t result = kStatus_Fail;

#if defined(SIM)
    assert(sizeof(sim_uid_t) <= SILICONID_MAX_LENGTH);
    uint32_t readBytes = *idLen;
    sim_uid_t uid;
    SIM_GetUniqueId(&uid);
    readBytes = (readBytes > sizeof(sim_uid_t)) ? sizeof(sim_uid_t) : readBytes;
    (void)memcpy((void *)&siliconId[0], (void *)(uint8_t *)&uid, readBytes);
    *idLen = readBytes;
    result = kStatus_Success;
#elif defined(FSL_FEATURE_SYSCON_IAP_ENTRY_LOCATION)
    uint32_t readBytes = *idLen;
    uint8_t uid[16];
    result = IAP_ReadUniqueID((uint32_t *)(uintptr_t)&uid[0]);
    if (result == kStatus_Success)
    {
        readBytes = (readBytes > 16U) ? 16U : readBytes;
        (void)memcpy((void *)&siliconId[0], (void *)&uid[0], readBytes);
        *idLen = readBytes;
    }
    else
    {
        *idLen = 0;
    }
#elif (defined(FSL_FEATURE_SYSCON_ROMAPI) && FSL_FEATURE_SYSCON_ROMAPI)
    flash_config_t s_flashDriver;
    (void)memset(&s_flashDriver, 0, sizeof(flash_config_t));

    result = FLASH_Init(&s_flashDriver);

    if (result == kStatus_Success)
    {
        result = FFR_Init(&s_flashDriver);

        if (result == kStatus_Success)
        {
            result = FFR_GetUUID(&s_flashDriver, siliconId);
            *idLen = 4;
        }
    }
#else
    extern status_t SILICONID_ReadUniqueID(uint8_t *siliconId, uint32_t *idLen);
    result = SILICONID_ReadUniqueID(&siliconId[0], idLen);
#endif

    return result;
}

status_t SILICONID_ConvertToMacAddr(uint8_t (*macAddr)[6])
{
    status_t result;

    uint8_t siliconId[SILICONID_MAX_LENGTH];
    uint32_t idLen = sizeof(siliconId);

    result = SILICONID_GetID(&siliconId[0], &idLen);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Valid ID should > 3. */
    assert(idLen >= 3U);

    /* Set NXP OUI. */
    macAddr[0][0] = 0x54;
    macAddr[0][1] = 0x27;
    macAddr[0][2] = 0x8d;

    /* Set with silicon id. */
    macAddr[0][3] = siliconId[0];
    macAddr[0][4] = siliconId[1];
    macAddr[0][5] = siliconId[2];

    return result;
}
