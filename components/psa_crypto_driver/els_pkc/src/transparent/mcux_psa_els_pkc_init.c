/*
 * Copyright 2023 NXP
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "mcux_psa_els_pkc_init.h" /* ELS_PKC Crypto port layer */

psa_status_t els_pkc_transparent_init(void)
{
    status_t els_pkc_status = CRYPTO_InitHardware();

    return els_pkc_to_psa_status(els_pkc_status);
}

psa_status_t els_pkc_transparent_free(void)
{
    status_t els_pkc_status = CRYPTO_DeinitHardware();

    return els_pkc_to_psa_status(els_pkc_status);
}
