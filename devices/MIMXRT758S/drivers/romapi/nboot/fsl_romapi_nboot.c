/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_romapi_nboot.h"
#include "fsl_romapi.h"

#define NBOOT_API_TREE ((nboot_interface_t *)(((uint32_t *)ROM_API_TREE_ADDR)[10]))

nboot_status_t NBOOT_ContextInit(nboot_context_t *context)
{
    assert(NBOOT_API_TREE);
    return NBOOT_API_TREE->nboot_context_init(context);
}

nboot_status_t NBOOT_ContextDeinit(nboot_context_t *context)
{
    assert(NBOOT_API_TREE);
    return NBOOT_API_TREE->nboot_context_deinit(context);
}

nboot_status_protected_t NBOOT_Sb3LoadManifest(nboot_context_t *context,
                                               uint32_t *manifest,
                                               nboot_sb3_load_manifest_parms_t *parms)
{
    assert(NBOOT_API_TREE);
    return NBOOT_API_TREE->nboot_sb3_load_manifest(context, manifest, parms);
}

nboot_status_protected_t NBOOT_Sb3LoadBlock(nboot_context_t *context, uint32_t *block)
{
    assert(NBOOT_API_TREE);
    return NBOOT_API_TREE->nboot_sb3_load_block(context, block);
}

nboot_status_protected_t NBOOT_Sb3CheckAuthenticityAndCompleteness(nboot_context_t *context,
                                                                   uint32_t *address,
                                                                   nboot_sb3_load_manifest_parms_t *parms)
{
    assert(NBOOT_API_TREE);
    return NBOOT_API_TREE->nboot_sb3_check_authenticity_and_completeness(context, address, parms);
}

nboot_status_protected_t NBOOT_ImgAuthenticateEcdsa(nboot_context_t *context,
                                                    uint8_t imageStartAddress[],
                                                    nboot_bool_t *isSignatureVerified,
                                                    nboot_img_auth_ecdsa_parms_t *parms)
{
    assert(NBOOT_API_TREE);
    return NBOOT_API_TREE->nboot_img_authenticate_ecdsa(context, imageStartAddress, isSignatureVerified, parms);
}

nboot_status_protected_t NBOOT_ImgAuthenticateCmac(nboot_context_t *context,
                                                   uint8_t imageStartAddress[],
                                                   nboot_bool_t *isSignatureVerified,
                                                   nboot_img_authenticate_cmac_parms_t *parms)
{
    assert(NBOOT_API_TREE);
    return NBOOT_API_TREE->nboot_img_authenticate_cmac(context, imageStartAddress, isSignatureVerified, parms);
}
