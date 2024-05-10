/*
 * Copyright 2022-2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUX_PSA_ELS_PKC_INIT_H
#define MCUX_PSA_ELS_PKC_INIT_H

/** \file mcux_psa_els_pkc_init.h
 *
 * This file contains the declaration of the entry points associated to
 * driver initialisation and de-initialisation procedures.
 *
 */
#include "psa/crypto.h"
#include "mcux_psa_els_pkc_common_init.h"


#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief  Initialises the ELE driver
 *
 * @return PSA_SUCCESS on success. Error code from psa_status_t on
 *          failure
 */
psa_status_t els_pkc_transparent_init(void);

/*!
 * @brief  De-Initialises the ELE driver
 *
 * @return PSA_SUCCESS on success. Error code from psa_status_t on
 *          failure
 */
psa_status_t els_pkc_transparent_free(void);


#ifdef __cplusplus
}
#endif

#endif /* MCUX_PSA_ELS_PKC_INIT_H */
