/*
 * Copyright 2022-2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUX_PSA_ELS_PKC_ENTROPY_H
#define MCUX_PSA_ELS_PKC_ENTROPY_H

/** \file mcux_psa_els_pkc_entropy.h
 *
 * This file contains the declaration of the entry points associated
 * to the entropy capability as described by the PSA Cryptoprocessor
 * Driver interface specification
 *
 */

#include "psa/crypto.h"
#include "mcux_psa_els_pkc_common_init.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief Collect entropy from a TRNG source
 *
 * \param[in]  flags         Flags to be passed to the TRNG source
 * \param[out] estimate_bits Estimation of the obtained entropy in bits
 * \param[out] output        Collected entropy from the TRNG source
 * \param[in]  output_size   Size of the output buffer
 *
 * \retval  PSA_SUCCESS on success. Error code from \ref psa_status_t on
 *          failure
 */
psa_status_t els_pkc_get_entropy(uint32_t flags, size_t *estimate_bits,
                             uint8_t *output, size_t output_size);
#ifdef __cplusplus
}
#endif
#endif /* MCUX_PSA_ELS_PKC_ENTROPY_H */
