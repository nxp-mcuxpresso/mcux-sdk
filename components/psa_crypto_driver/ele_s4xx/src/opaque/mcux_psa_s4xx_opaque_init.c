/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "mcux_psa_s4xx_common_init.h" /* ELE Crypto port layer */

psa_status_t ele_s4xx_opaque_init(void)
{
    status_t ele_status = CRYPTO_InitHardware();

    return ele_to_psa_status(ele_status);
}

psa_status_t ele_s4xx_opaque_free(void)
{
    status_t ele_status = CRYPTO_DeinitHardware();

    return ele_to_psa_status(ele_status);
}
