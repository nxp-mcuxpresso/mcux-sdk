/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_silicon_id.h"
#if defined(OCOTP)
#elif defined(SIM)
#include "fsl_sim.h"
#elif defined(FSL_FEATURE_SYSCON_IAP_ENTRY_LOCATION)
#include "fsl_iap.h"
#elif defined(SOC_UID_IN_SCFW) // Need to define in project by self
#include "svc/misc/misc_api.h"
#endif

status_t SILICONID_GetID(uint8_t *siliconId, uint32_t *idLen)
{
    status_t result = kStatus_Fail;

#if defined(OCOTP)
#ifdef OCOTP_CFG0_BITS_MASK
    *((uint32_t *)(uintptr_t)&siliconId[0]) = OCOTP->CFG0;
    *((uint32_t *)(uintptr_t)&siliconId[4]) = OCOTP->CFG1;
#else
    *((uint32_t *)(uintptr_t)&siliconId[0]) = OCOTP->FUSEN[16].FUSE;
    *((uint32_t *)(uintptr_t)&siliconId[4]) = OCOTP->FUSEN[17].FUSE;
#endif
    *idLen = 8;
    result = kStatus_Success;
#elif defined(SIM)
    /* Unique ID in SIM. */
    assert(sizeof(sim_uid_t) <= SILICONID_MAX_LENGTH);
    sim_uid_t uid;
    SIM_GetUniqueId(&uid);
    (void)memcpy((void *)&siliconId[0], (void *)(uint8_t *)&uid, sizeof(sim_uid_t));
    *idLen = sizeof(sim_uid_t);
    result = kStatus_Success;
#elif defined(FSL_FEATURE_SYSCON_IAP_ENTRY_LOCATION)
    result = IAP_ReadUniqueID((uint32_t *)(uintptr_t)&siliconId[0]);
    if (result != kStatus_Success)
    {
        return kStatus_Fail;
    }
    *idLen = 16;
    result = kStatus_Success;
#elif defined(SOC_UID_IN_SCFW)
    uint32_t idL, idH;
    sc_ipc_t ipcHandle = SystemGetScfwIpcHandle();
    sc_misc_unique_id(ipcHandle, &idL, &idH);
    *((uint32_t *)(uintptr_t)&siliconId[0]) = idL;
    *((uint32_t *)(uintptr_t)&siliconId[4]) = idH;
    *idLen                                  = 8;
    result                                  = kStatus_Success;
#endif

    return result;
}

status_t SILICONID_ConvertToMacAddr(uint8_t (*macAddr)[6])
{
    status_t result;

    uint8_t siliconId[SILICONID_MAX_LENGTH];
    uint32_t idLen;

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
