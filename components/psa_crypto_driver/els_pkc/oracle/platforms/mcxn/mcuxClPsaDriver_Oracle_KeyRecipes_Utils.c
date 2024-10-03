/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <mcuxClPsaDriver.h>

#include <mbedtls/platform.h>
#include <string.h>

#include "mcuxClPsaDriver_Oracle_ElsUtils.h"
#include "mcuxClPsaDriver_Functions.h"

#define NBOOT_MAX_ROTKH_SIZE_IN_BYTES 48u
#define CMPA_RKTH_ADDR 0x01004060u
/**
 * @defgroup NXPCLCSS_HASH_BLOCK_SIZE_ NXPCLCSS_HASH_BLOCK_SIZE_
 * @brief Defines block sizes used by the supported hash algorithms
 * @ingroup nxpClCss_Hash_Macros
 * @{s
 */
#define NXPCLCSS_HASH_BLOCK_SIZE_SHA_256  64U ///< SHA-256 output size: 512 bit (64 bytes)

psa_status_t el2go_get_device_rkth(uint32_t *rkth, size_t *rkth_size)
{
    psa_status_t status = PSA_ERROR_GENERIC_ERROR;
 
    memcpy(rkth, (uint8_t*)CMPA_RKTH_ADDR, NBOOT_MAX_ROTKH_SIZE_IN_BYTES);
    if ((rkth[8] == 0u) && (rkth[9] == 0u) && (rkth[10] == 0u) && (rkth[11] == 0u))
    {
        *rkth_size = 32u;
        status = PSA_SUCCESS;
    }
    else
    {
        *rkth_size = NBOOT_MAX_ROTKH_SIZE_IN_BYTES;
        status = PSA_SUCCESS;
    }
    
    return status;
}

uint32_t el2go_get_device_lifecycle()
{
    return SYSCON0->ELS_OTP_LC_STATE;
}

/* Computes derivation data for NXP_DIE_EL2GOOEM_MK_SK from device RKTH and lifecycle */
psa_status_t get_el2goem_mk_dd(uint8_t* dd)
{
    psa_status_t status = PSA_ERROR_GENERIC_ERROR;
    uint32_t rkth[NBOOT_MAX_ROTKH_SIZE_IN_BYTES / sizeof(uint32_t)];
    uint32_t lifecycle = el2go_get_device_lifecycle();
    size_t rkth_size;
    
    status = el2go_get_device_rkth(rkth, &rkth_size);

    do {
        // Data to hash must match the blocksize. We have at most 48 bytes 
        // of RKTH + 1 byte of LC + 1 min byte of padding + 8 bytes of length, resulting 
        // in max 58 bytes. SHA256 blocksize is 64 bytes, this will always fit.
        uint8_t data_to_hash[NXPCLCSS_HASH_BLOCK_SIZE_SHA_256] = { 0 };
        uint32_t* data_to_hash_as_uint32 = (uint32_t*) &data_to_hash[0];
        
        // Copy RKTH.
        assert(data_to_hash_as_uint32);
        assert(rkth_size <= NBOOT_MAX_ROTKH_SIZE_IN_BYTES);

        for (uint32_t i = 0U; i < (rkth_size / 4U); i++)
        {
            data_to_hash_as_uint32[i] = *(rkth + i);
        }

        // Add lifecycle
        data_to_hash[rkth_size] = lifecycle;
        
        // Calculate the hash.
        psa_algorithm_t alg = PSA_ALG_SHA_256;
        uint8_t digest[32] = { 0 };
        size_t hash_length = 0;
        status = mcuxClPsaDriver_psa_driver_wrapper_hash_compute(alg,
                                                             data_to_hash,
                                                             (rkth_size + 1u),
                                                             digest,
                                                             sizeof(digest),
                                                             &hash_length);

        

        memcpy(dd, digest, MCUXCLELS_CKDF_DERIVATIONDATA_SIZE);

        status = PSA_SUCCESS;
    } while(0);
    return status;
}
