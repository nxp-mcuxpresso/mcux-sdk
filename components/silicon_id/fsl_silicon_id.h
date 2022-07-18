/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_SILICON_ID_H_
#define _FSL_SILICON_ID_H_

#include "fsl_common.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "component.silicon_id"
#endif

#define SILICONID_MAX_LENGTH 16U

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Get the silicon ID.
 *
 * @param siliconId[out]  Memory address to store silicon ID, array length depends on specific Soc. The
 * SILICONID_MAX_LENGTH is the maximun length of all supported Socs.
 * @param idLen[out]  Return silicon ID byte length.
 * @retval kStatus_Success  Succeed to get silicon ID.
 * @retval kStatus_Fail  Fail to get silicon ID.
 */
status_t SILICONID_GetID(uint8_t *siliconId, uint32_t *idLen);

/*!
 * @brief Get and convert the silicon ID to ethernet MAC address.
 *
 * @param macAddr[out]  Memory address to store ethernet MAC address.
 * @retval kStatus_Success  Succeed to get silicon ID and finish conversion.
 * @retval kStatus_Fail  Fail to get silicon ID and finish conversion.
 */
status_t SILICONID_ConvertToMacAddr(uint8_t (*macAddr)[6]);

#if defined(__cplusplus)
}
#endif

#endif /* _FSL_SILICON_ID_H_ */
