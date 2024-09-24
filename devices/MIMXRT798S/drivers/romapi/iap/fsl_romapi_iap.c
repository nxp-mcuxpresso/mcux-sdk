/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_romapi_iap.h"
#include "fsl_romapi.h"

#define IAP_API_TREE ((iap_api_interface_t *)(((uint32_t *)ROM_API_TREE_ADDR)[13]))

uint32_t iap_api_version(void)
{
    assert(IAP_API_TREE);
    return IAP_API_TREE->version.version;
}

status_t iap_api_init(api_core_context_t *coreCtx, const kp_api_init_param_t *param)
{
    assert(IAP_API_TREE);
    return IAP_API_TREE->api_init(coreCtx, param);
}

status_t iap_api_deinit(api_core_context_t *coreCtx)
{
    assert(IAP_API_TREE);
    return IAP_API_TREE->api_deinit(coreCtx);
}

status_t iap_sbloader_init(api_core_context_t *ctx)
{
    assert(IAP_API_TREE);
    return IAP_API_TREE->sbloader_init(ctx);
}

status_t iap_sbloader_pump(api_core_context_t *ctx, uint8_t *data, uint32_t length)
{
    assert(IAP_API_TREE);
    return IAP_API_TREE->sbloader_pump(ctx, data, length);
}

status_t iap_sbloader_finalize(api_core_context_t *ctx)
{
    assert(IAP_API_TREE);
    return IAP_API_TREE->sbloader_finalize(ctx);
}
