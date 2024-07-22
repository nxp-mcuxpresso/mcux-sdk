/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "ele_crypto.h"
#include "ele_crypto_internal.h"
#include "ele_nvm_manager.h"
#include "fsl_s3mu.h"

static ele_nvm_manager_t *g_ELE_NVM_Manager = NULL;

#define STORAGE_MASTER_BLOB_ID 0

/*******************************************************************************
 * Code
 ******************************************************************************/

/* Static function to handle export chunk request from ELE      */
/* If success, return address and size of encrypted chunk, NULL otherwise */
static uint32_t *nvm_storage_handle_export_req(
    S3MU_Type *mu, uint32_t *buf, uint32_t wordCount, uint8_t *out, size_t *size)
{
    status_t status = kStatus_Fail;
    chunk_master_export_respond_t chunk_master_respond;
    chunk_export_respond_t chunk_response;
    chunk_export_req_t *chunk_req;
    chunk_export_finish_t finish;
    uint32_t *chunk_address;
    size_t chunk_sz;

    chunk_req = (chunk_export_req_t *)buf;

    /* ----- Step 2) Send response to ELE with address where to store the chunk */
    /* Check command request header from Secure Sub-System */
    switch (chunk_req->header.value)
    {
        case STORAGE_EXPORT_RESPONSE_REQ_HDR:
            /* Regular (data storage, key group or keystore) chunk export. */
            chunk_response.header.value  = EXPORT_CHUNK_RESPONSE_HDR;
            chunk_response.response_code = RESPONSE_SUCCESS;
            chunk_sz                     = chunk_req->chunk_size;

            /* Check if out is not NULL, it's size is sufficient for chunk.
               Ideally BUFFEr SHORT error should be returned with required size in *size,
               but function prototype doesn;t allow it,
               so returning back NULL.
             */
            if (out != NULL && *size < chunk_sz)
            {
                return NULL;
            }

            *size = chunk_sz;
            /* If out address is null, use HEAP */
            chunk_address             = (uint32_t *)malloc_if_not_null(out, *size);
            chunk_response.chunk_addr = (uint32_t)chunk_address;

            /* Send export chunk address message to Security Sub-System */
            status = S3MU_SendMessage(mu, (uint32_t *)&chunk_response, STORAGE_EXPORT_CHUNK_SIZE);

            break;

        case STORAGE_EXPORT_MASTER_RESPONSE_REQ_HDR:
            /* Master storage export request */
            chunk_master_respond.header.value   = EXPORT_MASTER_CHUNK_RESPONSE_HDR;
            chunk_master_respond.storage_handle = chunk_req->storage_handle;
            chunk_master_respond.response_code  = RESPONSE_SUCCESS;
            chunk_sz                            = chunk_req->chunk_size;

            /* Check if out is not NULL, it's size is sufficient for chunk.
               Ideally BUFFEr SHORT error should be returned with required size in *size,
               but function prototype doesn;t allow it,
               so returning back NULL.
             */
            if (out != NULL && *size < chunk_sz)
            {
                return NULL;
            }

            *size = chunk_sz;

            /* If out address is null, use HEAP */
            chunk_address                   = (uint32_t *)malloc_if_not_null(out, *size);
            chunk_master_respond.chunk_addr = (uint32_t)chunk_address;

            /* Send export chunk address message to Security Sub-System */
            status = S3MU_SendMessage(mu, (uint32_t *)&chunk_master_respond, STORAGE_MASTER_EXPORT_CHUNK_SIZE);

            break;

        default:
            status = kStatus_Fail;

            break;
    }

    if (status != kStatus_Success)
    {
        return NULL;
    }

    /* ----- Step 3) Get export finish request from ELE */
    /* Get Storage export finish command from Security Sub-System */
    status = S3MU_GetResponse(mu, (uint32_t *)&finish);
    if (status != kStatus_Success)
    {
        return NULL;
    }

    if (finish.header.value != EXPORT_FINISH_HDR && finish.status != EXPORT_STATUS_SUCCESS)
    {
        return NULL;
    }

    /* ----- Step 4) Send Export finish response to ELE */
    /* Send Storage export finish response to Security Sub-System */
    status = ELE_StorageExportFinish(mu, finish.storage_handle);
    if (status != kStatus_Success)
    {
        return NULL;
    }

    return chunk_address;
}

/* Static function to handle get chunk request from ELE */
/* If success return address of decrypted data, NULL otherwise */
static status_t nvm_storage_handle_get_req(S3MU_Type *mu, uint32_t *buf, uint32_t wordCount, ele_data_storage_t *conf)
{
    status_t status = kStatus_Fail;
    chunk_get_req_t *chunk_req;
    chunk_get_respond_t get_response;
    chunk_get_done_t get_done;
    chunk_get_done_resp_t get_done_resp;

    /* Obtain chunk get request from Security Sub-System */
    chunk_req = (chunk_get_req_t *)buf;

    /* Check request comman header from Secure Sub-System */
    if (chunk_req->header.value != STORAGE_GET_RESPONSE_REQ_HDR)
    {
        return kStatus_Fail;
    }

    get_response.header.value  = GET_CHUNK_RESPONSE_HDR;
    get_response.chunk_size    = conf->chunk_size;
    get_response.chunk_addr    = (uint32_t)conf->chunk_addr;
    get_response.response_code = RESPONSE_SUCCESS;

    /* Send export chunk address message to Security Sub-System */
    status = S3MU_SendMessage(mu, (uint32_t *)&get_response, STORAGE_GET_CHUNK_SIZE);
    if (status != kStatus_Success)
    {
        return kStatus_Fail;
    }

    /* Obtain Storage get chunk done command from Security Sub-System */
    status = S3MU_GetResponse(mu, (uint32_t *)&get_done);
    if (status != kStatus_Success)
    {
        return kStatus_Fail;
    }

    if (get_done.header.value != GET_DONE_HDR || get_done.status != GET_STATUS_SUCCESS)
    {
        return kStatus_Fail;
    }

    get_done_resp.header.value = GET_DONE_RESPONSE_HDR;
    get_done_resp.status       = RESPONSE_SUCCESS;

    /* Send Storage export finish response to Security Sub-System */
    status = S3MU_SendMessage(mu, (uint32_t *)&get_done_resp, GET_DONE_RESPONSE_SIZE);

    return status;
}

status_t nvm_storage_handle_req(S3MU_Type *mu, uint32_t *buf, uint32_t wordCount)
{
    status_t status = kStatus_Fail;
    mu_hdr_t *msg   = (mu_hdr_t *)buf;
    uint32_t *chunk;
    size_t chunk_sz = 0;
    chunk_export_req_t *chunk_export_request;
    chunk_get_req_t *chunk_req;
    ele_data_storage_t storage_conf;

    /* The request can be handled only if NVM Manager is registered */
    if (g_ELE_NVM_Manager == NULL)
    {
        return kStatus_Fail;
    }

    switch (msg->hdr_byte.command)
    {
        case STORAGE_MASTER_EXPORT_CMD:
            /* Chunk will be allocated by nvm_storage_export_req() */
            chunk = nvm_storage_handle_export_req(mu, buf, wordCount, NULL, &chunk_sz);
            if (chunk == NULL)
            {
                return kStatus_Fail;
            }

            /* Blob ID -> 0 fixed for storage master. */
            status = g_ELE_NVM_Manager->nvm_write(STORAGE_MASTER_BLOB_ID, STORAGE_MASTER_BLOB_ID, 0, chunk, chunk_sz);

            /* Free the chunk allocated by nvm_storage_export_req() */
            free(chunk);
            break;

        case STORAGE_CHUNK_EXPORT_CMD:
            chunk_export_request = (chunk_export_req_t *)buf;
            /* Chunk will be allocated by nvm_storage_export_req() */
            chunk = nvm_storage_handle_export_req(mu, buf, wordCount, NULL, &chunk_sz);
            if (chunk == NULL)
            {
                return kStatus_Fail;
            }

            /* use full blob ID (MSB and LSB) and extension */
            /* NVM manager call to Store chunk in actual NVM */
            status = g_ELE_NVM_Manager->nvm_write(chunk_export_request->blob_id_msb, chunk_export_request->blob_id_lsb,
                                                  chunk_export_request->blob_id_ext, chunk, chunk_sz);

            /* Free the chunk allocated by nvm_storage_export_req() */
            free(chunk);
            break;

        case STORAGE_GET_CHUNK_CMD:
            chunk_req = (chunk_get_req_t *)buf;

            /* Retreive chunk from NVM
             * NVMmgr allocates chunk based on size of data and returns a pointer.
             */
            chunk = g_ELE_NVM_Manager->nvm_read(chunk_req->blob_id_msb, chunk_req->blob_id_lsb, chunk_req->blob_id_ext,
                                                NULL, &chunk_sz);
            if (chunk == NULL)
            {
                return kStatus_Fail;
            }
            storage_conf.chunk_size = chunk_sz;
            storage_conf.chunk_addr = chunk;

            /* Import chunk into the ELE */
            status = nvm_storage_handle_get_req(mu, buf, wordCount, &storage_conf);

            free(chunk);
            break;
        default:
            status = kStatus_Fail;
            break;
    }

    return status;
}

status_t ELE_Register_NVM_Manager(ele_nvm_manager_t *manager)
{
    if (manager == NULL || manager->nvm_read == NULL || manager->nvm_write == NULL)
    {
        return kStatus_Fail;
    }

    if (g_ELE_NVM_Manager != NULL)
    {
        return kStatus_Busy;
    }

    g_ELE_NVM_Manager = malloc(sizeof(struct ele_nvm_manager));
    if (g_ELE_NVM_Manager == NULL)
    {
        return kStatus_Fail;
    }

    g_ELE_NVM_Manager->nvm_read  = manager->nvm_read;
    g_ELE_NVM_Manager->nvm_write = manager->nvm_write;

    return kStatus_Success;
}

status_t ELE_Unregister_NVM_Manager(void)
{
    free(g_ELE_NVM_Manager);

    g_ELE_NVM_Manager = NULL;

    return kStatus_Success;
}

/*!
 * brief ELE Export Chunks Management Service with NVM Manager
 *
 * This function provides the Key Group Management Service for exporting keygroup, keystore and storage master chunks.
 *
 * param base MU peripheral base address
 * param keyHandleID unique key management handle ID obtained by calling ELE_OpenKeyService()
 * param exportKeyGroup If true, key group (keyGroupID) chunk is exported, if false, only keystore and master
 * param keyGroupID unique key group ID choosen by user. Not used if exportKeyGroup is false
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_ExportChunks_To_NVM(S3MU_Type *mu, uint32_t keyHandleID, bool exportKeyGroup, uint32_t keyGroupID)
{
    status_t status                   = kStatus_Fail;
    uint32_t tmsg[KEY_MNG_GROUP_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]      = {0u};

    uint32_t flags;
    if (exportKeyGroup == false)
    {
        flags      = SYNC_OP_NO_KEY;
        keyGroupID = 0u;
    }
    else
    {
        flags = SYNC_OP;
    }

    tmsg[0] = KEY_MNG_GROUP;                  // KEY_MNG_GROUP Command Header
    tmsg[1] = keyHandleID;                    // Key Management handle ID
    tmsg[2] = flags << SHIFT_16 | keyGroupID; // STRICT Operation

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, KEY_MNG_GROUP_SIZE);
    if (status != kStatus_Success)
    {
        return status;
    }

    /* Wait for response from Security Sub-System */
    status = ele_mu_get_response(mu, rmsg);
    if (status != kStatus_Success)
    {
        return status;
    }

    /* Check that response corresponds to the sent command */
    if (rmsg[0] == KEY_MNG_GROUP_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief ELE Key Management Service with NVM Manager
 *
 * This function provides the Key Group Management Service for EdgeLock Enclave.
 *
 * param base MU peripheral base address
 * param keyHandleID unique key management handle ID obtained by calling ELE_OpenKeyService()
 * param operation Requested opration, see key_group_mng_t enum
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_ManageKeyGroup_To_NVM(S3MU_Type *mu, uint32_t keyHandleID, uint32_t keyGroupID, key_group_mng_t operation)
{
    status_t status                   = kStatus_Fail;
    uint32_t tmsg[KEY_MNG_GROUP_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]      = {0u};

    tmsg[0] = KEY_MNG_GROUP; // KEY_MNG_GROUP Command Header
    tmsg[1] = keyHandleID;   // Key Management handle ID
    tmsg[2] = ((uint32_t)operation << SHIFT_16) | keyGroupID;

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, KEY_MNG_GROUP_SIZE);
    if (status != kStatus_Success)
    {
        return status;
    }

    /* Wait for response from Security Sub-System */
    status = ele_mu_get_response(mu, rmsg);
    if (status != kStatus_Success)
    {
        return status;
    }

    /* Check that response corresponds to the sent command */
    if (rmsg[0] == KEY_MNG_GROUP_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief ELE Storage Master Import Service
 *
 * This function provides Storage Master Import Service for EdgeLock Enclave.
 * This must be called prior opening keystore stored in the NVM.
 *
 * param base MU peripheral base address
 * param nvmStorageID unique session ID obtained by calling ELE_OpenNvmStorageService()
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_StorageMasterImport_From_NVM(S3MU_Type *mu, uint32_t nvmStorageID)
{
    status_t status                       = kStatus_Fail;
    uint32_t tmsg[NVM_MASTER_IMPORT_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]          = {0u};
    uint32_t *chunk                       = NULL;
    size_t chunk_sz                       = 0u;

    /* The request can be handled only if NVM Manager is registered */
    if (g_ELE_NVM_Manager == NULL)
    {
        return kStatus_Fail;
    }

    tmsg[0] = NVM_MASTER_IMPORT; // NVM_MASTER_IMPORT Command Header
    tmsg[1] = nvmStorageID;      // NVM storage ID handle ID

    chunk = g_ELE_NVM_Manager->nvm_read(STORAGE_MASTER_BLOB_ID, STORAGE_MASTER_BLOB_ID, 0, NULL, &chunk_sz);
    if (chunk == NULL && chunk_sz == 0u)
    {
        /* Master Chunk doesn't exist in NVM */
        return kStatus_NoData;
    }
    tmsg[2] = (uint32_t)chunk;    // Address of master chunk
    tmsg[3] = (uint32_t)chunk_sz; // Master chunk size

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, NVM_MASTER_IMPORT_SIZE);
    if (status != kStatus_Success)
    {
        free(chunk);
        return status;
    }
    /* Wait for response from Security Sub-System */
    status = ele_mu_get_response(mu, rmsg);

    /* Chunk was allocated by nvm_read, once response is received, free it */
    free(chunk);

    if (status != kStatus_Success)
    {
        return status;
    }

    /* Check that response corresponds to the sent command */
    if (rmsg[0] == NVM_MASTER_IMPORT_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}
