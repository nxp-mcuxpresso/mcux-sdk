/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_romapi_iap.h"
#include "fsl_romapi.h"

#define IAP_API_TREE ((iap_api_interface_t *)(((uint32_t *)ROM_API_TREE_ADDR)[7]))

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

status_t iap_mem_init(api_core_context_t *coreCtx)
{
    assert(IAP_API_TREE);
    return IAP_API_TREE->mem_init_api(coreCtx);
}

status_t iap_mem_write(
    api_core_context_t *coreCtx, uint32_t start, uint32_t lengthInBytes, const uint8_t *buf, uint32_t memoryId)
{
    assert(IAP_API_TREE);
    return IAP_API_TREE->mem_write(coreCtx, start, lengthInBytes, buf, memoryId);
}

status_t iap_mem_read(
    api_core_context_t *coreCtx, uint32_t start, uint32_t lengthInBytes, uint8_t *buf, uint32_t memoryId)
{
    assert(IAP_API_TREE);
    return IAP_API_TREE->mem_read(coreCtx, start, lengthInBytes, buf, memoryId);
}

status_t iap_mem_fill(
    api_core_context_t *coreCtx, uint32_t start, uint32_t lengthInBytes, uint32_t pattern, uint32_t memoryId)
{
    assert(IAP_API_TREE);
    return IAP_API_TREE->mem_fill(coreCtx, start, lengthInBytes, pattern, memoryId);
}

status_t iap_mem_erase(api_core_context_t *coreCtx, uint32_t start, uint32_t lengthInBytes, uint32_t memoryId)
{
    assert(IAP_API_TREE);
    return IAP_API_TREE->mem_erase(coreCtx, start, lengthInBytes, memoryId);
}

status_t iap_mem_erase_all(api_core_context_t *coreCtx, uint32_t memoryId)
{
    assert(IAP_API_TREE);
    return IAP_API_TREE->mem_erase_all(coreCtx, memoryId);
}

status_t iap_mem_config(api_core_context_t *coreCtx, uint32_t *config, uint32_t memoryId)
{
    assert(IAP_API_TREE);
    return IAP_API_TREE->mem_config(coreCtx, config, memoryId);
}

status_t iap_mem_flush(api_core_context_t *coreCtx)
{
    assert(IAP_API_TREE);
    return IAP_API_TREE->mem_flush(coreCtx);
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
