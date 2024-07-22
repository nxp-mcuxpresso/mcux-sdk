/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_romapi_nboot.h"
#include "fsl_romapi.h"

#define NBOOT_API_TREE ((nboot_interface_t *)(((uint32_t *)ROM_API_TREE_ADDR)[4]))

romapi_status_t romapi_rng_generate_random(uint8_t *output, size_t outputByteLen)
{
    assert(NBOOT_API_TREE);
    return NBOOT_API_TREE->rng_generate_random(output, outputByteLen);
}

nboot_status_t nboot_context_init(nboot_context_t *context)
{
    assert(NBOOT_API_TREE);
    return NBOOT_API_TREE->context_init(context);
}

nboot_status_t nboot_context_deinit(nboot_context_t *context)
{
    assert(NBOOT_API_TREE);
    return NBOOT_API_TREE->context_deinit(context);
}

nboot_status_protected_t nboot_sb3_load_manifest(nboot_context_t *context,
                                                 uint32_t *manifest,
                                                 nboot_sb3_load_manifest_parms_t *parms)
{
    assert(NBOOT_API_TREE);
    return NBOOT_API_TREE->sb3_load_manifest(context, manifest, parms);
}

nboot_status_protected_t nboot_sb3_load_block(nboot_context_t *context, uint32_t *block)
{
    assert(NBOOT_API_TREE);
    return NBOOT_API_TREE->sb3_load_block(context, block);
}

nboot_status_protected_t nboot_img_authenticate_ecdsa(nboot_context_t *context,
                                                      uint8_t imageStartAddress[],
                                                      nboot_bool_t *isSignatureVerified,
                                                      nboot_img_auth_ecdsa_parms_t *parms)
{
    assert(NBOOT_API_TREE);
    return NBOOT_API_TREE->img_authenticate_ecdsa(context, imageStartAddress, isSignatureVerified, parms);
}
