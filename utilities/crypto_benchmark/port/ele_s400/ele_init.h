/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef ELE_INIT_H
#define ELE_INIT_H

#include "fsl_common.h"

#if defined(MIMXRT1189_cm33_SERIES)
#define S3MU MU_RT_S3MUA
#elif defined(MIMXRT1189_cm7_SERIES)
#define S3MU MU_APPS_S3MUA
#else
#error "No valid SoC defined"
#endif /* MIMXRT1189_cm33_SERIES | MIMXRT1189_cm7_SERIES */

typedef struct
{
    uint32_t session_handle;
    bool is_fw_loaded;
} ele_ctx_t;

/*!
 * @brief Application init for Crypto blocks.
 *
 * This function is provided to be called by MCUXpresso SDK applications.
 * It calls basic init for Crypto Hw acceleration and Hw entropy modules.
 */
status_t CRYPTO_InitHardware(void);

/*!
 * @brief Application deinit for Crypto blocks.
 *
 * This function is provided to be called by MCUXpresso SDK applications.
 * It calls basic deinit for Crypto Hw acceleration and Hw entropy modules.
 */
status_t CRYPTO_DeinitHardware(void);

#ifdef __cplusplus
}
#endif

#endif /* ELE_INIT_H */
