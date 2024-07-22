/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUX_PSA_S2XX_COMMON_INIT_H
#define MCUX_PSA_S2XX_COMMON_INIT_H

/** \file ele_s2xx_transparent_psa_init.h
 *
 * This file contains the declaration of the entry points associated to
 * driver initialisation and de-initialisation procedures.
 *
 */

#include "psa/crypto.h"

#include "fsl_common.h"
#include "osal_mutex.h"

#include "fsl_sss_mgmt.h"
#include "fsl_sss_sscp.h"
#include "fsl_sscp_mu.h"

typedef struct
{
    sss_sscp_key_store_t keyStore;
    sss_sscp_session_t sssSession;
    sscp_context_t sscpContext;
    sss_sscp_rng_t rngctx;

    bool is_fw_loaded;

} ele_s2xx_ctx_t;

#define ELE_MAX_SUBSYSTEM_WAIT (0xFFFFFFFFu)
#define ELE_SUBSYSTEM          (kType_SSS_Ele200)
#define ELE_HIGH_QUALITY_RNG   1

/* MUTEX FOR HW Modules*/
extern mcux_mutex_t ele_hwcrypto_mutex;

extern ele_s2xx_ctx_t g_ele_ctx; /* Global context for S200 */

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Application init for Crypto blocks.
 *
 * This function is provided to be called by MCUXpresso SDK applications.
 * It calls basic init for Crypto Hw acceleration and Hw entropy modules.
 */
status_t CRYPTO_InitHardware(void);

/*!
 * @brief Application Deinit for Crypto blocks.
 *
 * This function is provided to be called by MCUXpresso SDK applications.
 * It calls basic deinit for Crypto Hw acceleration and Hw entropy modules.
 */
status_t CRYPTO_DeinitHardware(void);

/*!
 * @brief  Convert ELE error to PSA status
 *
 * @return PSA_SUCCESS on success. Error code from psa_status_t on
 *          failure
 */
psa_status_t ele_to_psa_status(status_t ele_status);

#ifdef __cplusplus
}
#endif

#endif /* MCUX_PSA_S2XX_COMMON_INIT_H */
