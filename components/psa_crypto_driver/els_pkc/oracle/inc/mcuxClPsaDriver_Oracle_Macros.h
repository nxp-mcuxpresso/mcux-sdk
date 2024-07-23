/*
 * Copyright 2022-2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/** @file  mcuxClPsaDriver_Oracle_Macros.h
 *  @brief Macros used by the Oracle and Utils functions */

#ifndef _MCUXCLPSADRIVER_ORACLE_MACROS_
#define _MCUXCLPSADRIVER_ORACLE_MACROS_

#include "mcuxClPsaDriver_Oracle_Interface_key_locations.h"

#ifndef PRINTF
#ifdef PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER
/* oracle is part of TF-M S */
#define PRINTF(...)
#define PSA_DRIVER_ERROR(...)
#else /* PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER */
/* define PRINTF */
#include <stdio.h>
#define PRINTF printf
#endif /* PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER */
#endif /* PRINTF */

/**
 * @brief Converts a little-endian order uint8_t array to a 32-bit unsigned int.
 * @note Implementation is platform independent.
 * @param[in]       src : pointer to a 4 byte little-endian order
 * uint8_t buffer that will be converted to an unsigned integer
 */
#define PSA_DRIVER_LITTLE_ENDIAN_FROM_U8_TO_U32(src)                                                     \
    ((((uint32_t)((const uint8_t *)(src))[0]) << 0u) | (((uint32_t)((const uint8_t *)(src))[1]) << 8u) | \
     (((uint32_t)((const uint8_t *)(src))[2]) << 16u) | (((uint32_t)((const uint8_t *)(src))[3]) << 24u))

#ifndef PSA_DRIVER_ERROR
#define PSA_DRIVER_ERROR(...)                                \
    for (;;)                                                 \
    {                                                        \
        (void)PRINTF("ERROR: %s L#%d ", __func__, __LINE__); \
        (void)PRINTF(__VA_ARGS__);                           \
        (void)PRINTF("\r\n");                                \
        break;                                               \
    }
#endif /* PSA_DRIVER_ERROR */

#define PSA_DRIVER_EXIT_STATUS_MSG(STATUS, ...) \
    psa_status = STATUS;                        \
    PSA_DRIVER_ERROR(__VA_ARGS__);              \
    goto exit;

#define PSA_DRIVER_SUCCESS_OR_EXIT_MSG(...) \
    if (PSA_SUCCESS != psa_status)          \
    {                                       \
        PSA_DRIVER_ERROR(__VA_ARGS__);      \
        goto exit;                          \
    }

#define PSA_DRIVER_SUCCESS_OR_EXIT() PSA_DRIVER_SUCCESS_OR_EXIT_MSG("psa_status is not success but [0x%x]", psa_status)

#define PSA_DRIVER_SET_STATUS_SUCCESS_AND_EXIT() \
    psa_status = PSA_SUCCESS;                    \
    goto exit;

#define PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(CONDITION, STATUS, ...) \
    if (!(CONDITION))                                                \
    {                                                                \
        PSA_DRIVER_EXIT_STATUS_MSG(STATUS, __VA_ARGS__);             \
    }

#define PSA_DRIVER_ASSERT_BUFFER_SIZE_OR_EXIT_STATUS_MSG(BASE, LENGTH, END, STATUS, ...) \
    PSA_DRIVER_ASSERT_OR_EXIT_STATUS_MSG(((BASE + LENGTH) > BASE) && ((BASE + LENGTH) <= END), STATUS, __VA_ARGS__)

#endif //_MCUXCLPSADRIVER_ORACLE_MACROS_
