/*
 * Copyright 2024 NXP
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "mcux_psa_s2xx_init.h" /* ELE Crypto port layer */

psa_status_t ele_s2xx_transparent_init(void)
{
    status_t ele_status = CRYPTO_InitHardware();

    return ele_to_psa_status(ele_status);
}

psa_status_t ele_s2xx_transparent_free(void)
{
    status_t ele_status = CRYPTO_DeinitHardware();

    return ele_to_psa_status(ele_status);
}
