/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_SILICON_ID_SOC_H_
#define _FSL_SILICON_ID_SOC_H_

#include "fsl_common.h"

#if defined(__cplusplus)
extern "C" {
#endif

status_t SILICONID_ReadUniqueID(uint8_t *siliconId, uint32_t *idLen);

#if defined(__cplusplus)
}
#endif

#endif /* _FSL_SILICON_ID_SOC_H_ */
