/*
 * Copyright 2022-2023 NXP
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUX_PSA_S4XX_SDMMC_NVM_MANAGER_H
#define MCUX_PSA_S4XX_SDMMC_NVM_MANAGER_H

/** \file mcux_psa_s4xx_sdmmc_nvm_manager.h
 *
 * This file contains the declaration of the entry points associated to
 * driver initialisation and de-initialisation procedures.
 *
 */

#include "fsl_common.h"

#ifdef __cplusplus
extern "C" {
#endif

uint32_t *sd_file_read(uint32_t blob_id_msb,
                       uint32_t blob_id_lsb,
                       uint32_t blob_id_ext,
                       uint32_t *chunk,
                       size_t *sz);
status_t sd_file_write(uint32_t blob_id_msb,
                       uint32_t blob_id_lsb,
                       uint32_t blob_ext,
                       uint32_t *chunk,
                       size_t chunk_sz);
int sd_ele_fs_initialize(void);

#ifdef __cplusplus
}
#endif

#endif /* MCUX_PSA_S4XX_SDMMC_NVM_MANAGER_H */
