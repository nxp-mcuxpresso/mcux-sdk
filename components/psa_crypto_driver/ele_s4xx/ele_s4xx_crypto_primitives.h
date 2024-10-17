/*
 * Copyright 2023 NXP
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef ELE_S4XX_CRYPTO_PRIMITIVES_H
#define ELE_S4XX_CRYPTO_PRIMITIVES_H

/** \file ele_s4xx_crypto_primtives.h
 *
 * This file contains the declaration of the context structures related
 * to the ele driver
 *
 */

#include "ele_crypto.h"

typedef struct {
    ele_hash_ctx_t ctx;
    hash_algo_t mode;
} ele_s4xx_hash_operation_t;

#endif /* ELE_S4XX_CRYPTO_PRIMITIVES_H */
