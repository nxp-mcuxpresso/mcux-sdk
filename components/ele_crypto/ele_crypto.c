/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "ele_crypto.h"
#include "ele_crypto_internal.h"
#include "fsl_s3mu.h"
#if defined(ELE_CACHE_HANDLING) && (ELE_CACHE_HANDLING > 0u)
#include "fsl_cache.h"
#endif /* defined(ELE_CACHE_HANDLING) */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static uint32_t *nvm_storage_export_req(S3MU_Type *mu, uint32_t *out, size_t *size);
static status_t nvm_storage_get_req(S3MU_Type *mu, ele_data_storage_t *conf);
static status_t construct_dek_key_blob_input(generate_key_blob_input_t *conf, uint32_t *payload);
static status_t construct_otfad_key_blob_input(generate_key_blob_input_t *conf, uint32_t *payload);
static status_t construct_iee_key_blob_input(generate_key_blob_input_t *conf, uint32_t *payload);
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Macros and computing data offset */
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && (__CORTEX_M == 7U)
#include "fsl_memory.h"
#define ADD_OFFSET(addr) MEMORY_ConvertMemoryMapAddress(addr, kMEMORY_Local2DMA)
#else  /* !FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
#define ADD_OFFSET(addr) (addr)
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */

/*******************************************************************************
 * Code
 ******************************************************************************/

/* Weak function to handle nvm manager requests from ELE */
/* If NVM Manager is defined, this function can be over-ridden */
__WEAK status_t nvm_storage_handle_req(S3MU_Type *mu, uint32_t *buf, uint32_t wordCount)
{
    return kStatus_Fail;
}

/*!
 * brief Get response from MU
 *
 * This function reads response data from EdgeLock Enclave if available.
 *
 * param mu MU peripheral base address
 * param buf buffer to store read data
 * param wordCount size of data in words
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ele_mu_get_response(S3MU_Type *mu, uint32_t *buf)
{
    status_t status                 = kStatus_Fail;
    uint32_t rmsg[MSG_RESPONSE_MAX] = {0u};
    mu_hdr_t *msg                   = (mu_hdr_t *)rmsg;

    do
    {
        status = S3MU_GetResponse(mu, rmsg);
        if (status != kStatus_Success)
        {
            break;
        }

        if (msg->hdr_byte.tag == MSG_TAG_RESP)
        {
            (void)memcpy((void *)buf, (void *)msg, (uint32_t)(msg->hdr_byte.size * sizeof(uint32_t)));
            break;
        }
        else if (msg->hdr_byte.tag == MSG_TAG_CMD)
        {
            status = nvm_storage_handle_req(mu, rmsg, msg->hdr_byte.size);
            if (status != kStatus_Success)
            {
                break;
            }
        }
        else
        {
            return kStatus_Fail;
        }
    } while (msg->hdr_byte.tag != MSG_TAG_RESP);

    return status;
}

/*!
 * brief Load ELE FW
 *
 * This function Loads firmware into EdgeLock Enclave.
 *
 * param mu MU peripheral base address
 * param fw pointer in system memory where FW can be found
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_LoadFw(S3MU_Type *mu, const uint8_t *fw)
{
    status_t status              = kStatus_Fail;
    uint32_t tmsg[LOAD_FW_SIZE]  = {0u};
    uint32_t rmsg[S3MU_RR_COUNT] = {0u};

    /****************** Load EdgeLock FW message ***********************/
    tmsg[0] = LOAD_FW;                  // LOAD_FW Command Header
    tmsg[1] = ADD_OFFSET((uint32_t)fw); // EdgeLock FW address
    tmsg[2] = 0x0u;                     // Reserved
    tmsg[3] = ADD_OFFSET((uint32_t)fw); // EdgeLock FW address
    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, LOAD_FW_SIZE);
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
    if (rmsg[0] == LOAD_FW_RESPONSE_HDR && rmsg[1] == LOAD_FW_RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Initialize ELE services
 *
 * This function initializes the EdgeLock Enclave services and needs to be
 * called at least once before using these services (e.g. ELE_OpenSession()).
 *
 * param mu MU peripheral base address
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_InitServices(S3MU_Type *mu)
{
    status_t status                   = kStatus_Fail;
    uint32_t tmsg[INIT_SERVICES_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]      = {0u};

    tmsg[0] = INIT_SERVICES; // INIT Command Header

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, INIT_SERVICES_SIZE);
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
    if (rmsg[0] == INIT_SERVICES_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Open ELE Session
 *
 * This function opens Session for EdgeLock Enclave.
 *
 * param mu MU peripheral base address
 * param sessionID pointer to output unique session ID word
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_OpenSession(S3MU_Type *mu, uint32_t *sessionID)
{
    status_t status                  = kStatus_Fail;
    uint32_t tmsg[OPEN_SESSION_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]     = {0u};

    tmsg[0] = OPEN_SESSION; // OPEN_SESSION Command Header
    tmsg[1] = 0x02000001u;  // EdgeLock ID
    tmsg[2] = 0x00000000u;  // Operating mode | Priority
    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, OPEN_SESSION_SIZE);
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
    if (rmsg[0] == OPEN_SESSION_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        /* read Session ID data */
        *sessionID = rmsg[2];
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Close ELE Session
 *
 * This function closes the Session for EdgeLock Enclave.
 *
 * param mu MU peripheral base address
 * param sessionID unique session ID obtained by calling ELE_OpenSession()
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_CloseSession(S3MU_Type *mu, uint32_t sessionID)
{
    status_t status                   = kStatus_Fail;
    uint32_t tmsg[CLOSE_SESSION_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]      = {0u};

    tmsg[0] = CLOSE_SESSION; // CLOSE_SESSION Command Header
    tmsg[1] = sessionID;     // Session ID

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, CLOSE_SESSION_SIZE);
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
    if (rmsg[0] == CLOSE_SESSION_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief ELE HASH
 *
 * This function computes HASH (One Go) of a given message using EdgeLock Enclave.
 *
 * param mu MU peripheral base address
 * param msg pointer where data to be hashed can be found, may be zero
 * param size size of data in byte, may be zero
 * param out pointer to output HASH data (size is defined by used algorithm),
 *           user must ensure this memory is available to ELE
 * param out_size the size of the output buffer, which must be equal or larger
 *       than the resulting HASH
 * param out_length pointer where to output the resulting length of the generated HASH,
 *       or the expected out_size of the output buffer if it is found to be too small
 * param alg define used hash algorithm, see hash_algo_t
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail,
 *        kStatus_InvalidArgument if invalid argument
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange,
 *                  kStatus_ELE_BufferTooSmall
 */
status_t ELE_Hash(S3MU_Type *mu,
                  const uint8_t *msg,
                  size_t size,
                  uint8_t *out,
                  uint32_t out_size,
                  uint32_t *out_length,
                  hash_algo_t alg)
{
    status_t status              = kStatus_Fail;
    uint32_t tmsg[HASH_SIZE]     = {0u};
    uint32_t rmsg[S3MU_RR_COUNT] = {0u};

    /* Check argument validity */
    if (mu == NULL || out == NULL || out_length == NULL)
    {
        return kStatus_InvalidArgument;
    }

    /* Check supported algorithms */
    if (alg != kELE_Sha224 && alg != kELE_Sha256 && alg != kELE_Sha384 && alg != kELE_Sha512 && alg != kELE_SM3256)
    {
        return kStatus_InvalidArgument;
    }

    tmsg[0] = HASH_HDR;                  // HASH Command Header
    tmsg[1] = 0u;                        // MSB address (not used)
    tmsg[2] = 0u;                        // CTX address, not used for ONE GO
    tmsg[3] = ADD_OFFSET((uint32_t)msg); // Input Hash address
    tmsg[4] = ADD_OFFSET((uint32_t)out); // Output Hash address
    tmsg[5] = size;                      // Input size
    tmsg[6] = out_size;                  // Output size
    tmsg[7] = 0x1u;                      // CTX size (not used for ONE GO) | Flag (Bit0 = 1 -> ONE GO)
    tmsg[8] = (uint32_t)alg;             // Alg
    tmsg[9] = S3MU_ComputeMsgCrc(tmsg, HASH_SIZE - 1u);
    // CRC sum of all the words of the message (excluding the CRC itself)

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, HASH_SIZE);
    if (status != kStatus_Success)
    {
        return status;
    }
    /* Wait for response from Security Sub-System */
    if (ele_mu_get_response(mu, rmsg) != kStatus_Success)
    {
        return status;
    }

    /* Check that response corresponds to the sent command */
    if (rmsg[0] != HASH_RESPONSE_HDR)
    {
        return kStatus_Fail;
    }

    /* Header OK, check for success */
    if (rmsg[1] == RESPONSE_SUCCESS)
    {
        *out_length = rmsg[2];

#if defined(ELE_CACHE_HANDLING) && (ELE_CACHE_HANDLING > 0u)
        DCACHE_InvalidateByRange((uint32_t)out, *out_length);
#endif /* defined(ELE_CACHE_HANDLING) */

        return kStatus_Success;
    }
    else if (rmsg[1] == RESPONSE_ERROR_SIZE)
    {
        *out_length = rmsg[2];
        return kStatus_ELE_BufferTooSmall;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief ELE HASH
 *
 * This function initialize ELE context for streaming HASH oprations.
 *
 * param mu MU peripheral base address
 * param ctx Context of ELE HASH streaming operations used by ELE.
 * param alg define used hash algorithm, see hash_algo_t
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_Hash_Init(S3MU_Type *mu, ele_hash_ctx_t *ctx, hash_algo_t alg)
{
    status_t status              = kStatus_Fail;
    uint32_t tmsg[HASH_SIZE]     = {0u};
    uint32_t rmsg[S3MU_RR_COUNT] = {0u};
    uint16_t ctxSize             = 0u;

    switch (alg)
    {
        case kELE_Sha224:
            ctxSize = HASH_CTX_SIZE_SHA224;
            break;
        case kELE_Sha256:
            ctxSize = HASH_CTX_SIZE_SHA256;
            break;
        case kELE_Sha384:
            ctxSize = HASH_CTX_SIZE_SHA384;
            break;
        case kELE_Sha512:
            ctxSize = HASH_CTX_SIZE_SHA512;
            break;
        case kELE_SM3256:
            ctxSize = HASH_CTX_SIZE_SM3256;
            break;

        default:
            status = kStatus_InvalidArgument;
            break;
    }

    if (status == kStatus_InvalidArgument)
    {
        return status;
    }

    tmsg[0] = HASH_HDR;                             // HASH Command Header
    tmsg[1] = 0u;                                   // MSB address (not used)
    tmsg[2] = ADD_OFFSET((uint32_t)ctx->x);         // CTX address, not used for ONE GO
    tmsg[3] = 0u;                                   // Input Hash address (not used for init)
    tmsg[4] = 0u;                                   // Output Hash address (not used for init)
    tmsg[5] = 0u;                                   // Input size (not used for init)
    tmsg[6] = 0u;                                   // Output size (not used for init)
    tmsg[7] = (uint32_t)ctxSize << SHIFT_16 | 0x2u; // CTX size | Flag (Bit1 = 1 -> Init)
    tmsg[8] = (uint32_t)alg;                        // Alg
    tmsg[9] = S3MU_ComputeMsgCrc(tmsg, HASH_SIZE - 1u);
    // CRC sum of all the words of the message (excluding the CRC itself)

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, HASH_SIZE);
    if (status != kStatus_Success)
    {
        return status;
    }
    /* Wait for response from Security Sub-System */
    if (ele_mu_get_response(mu, rmsg) != kStatus_Success)
    {
        return status;
    }

#if defined(ELE_CACHE_HANDLING) && (ELE_CACHE_HANDLING > 0u)
    DCACHE_InvalidateByRange((uint32_t)ctx->x, ctxSize);
#endif /* defined(ELE_CACHE_HANDLING) */

    /* Check that response corresponds to the sent command */
    if (rmsg[0] == HASH_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief ELE HASH
 *
 * This function update ELE digest in context with new data.
 *
 * param mu MU peripheral base address
 * param ctx Context of ELE HASH streaming operations used by ELE.
 * param alg define used hash algorithm, see hash_algo_t
 * param msg pointer where data to be hashed can be found, may be zero
 * param size size of data in byte, may be zero
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_Hash_Update(S3MU_Type *mu, ele_hash_ctx_t *ctx, hash_algo_t alg, const uint8_t *msg, size_t size)
{
    status_t status              = kStatus_Fail;
    uint32_t tmsg[HASH_SIZE]     = {0u};
    uint32_t rmsg[S3MU_RR_COUNT] = {0u};
    uint16_t ctxSize             = 0u;

    switch (alg)
    {
        case kELE_Sha224:
            ctxSize = HASH_CTX_SIZE_SHA224;
            break;
        case kELE_Sha256:
            ctxSize = HASH_CTX_SIZE_SHA256;
            break;
        case kELE_Sha384:
            ctxSize = HASH_CTX_SIZE_SHA384;
            break;
        case kELE_Sha512:
            ctxSize = HASH_CTX_SIZE_SHA512;
            break;
        case kELE_SM3256:
            ctxSize = HASH_CTX_SIZE_SM3256;
            break;

        default:
            status = kStatus_InvalidArgument;
            break;
    }

    if (status == kStatus_InvalidArgument)
    {
        return status;
    }

    tmsg[0] = HASH_HDR;                             // HASH Command Header
    tmsg[1] = 0u;                                   // MSB address (not used)
    tmsg[2] = ADD_OFFSET((uint32_t)ctx->x);         // CTX address
    tmsg[3] = ADD_OFFSET((uint32_t)msg);            // Input Hash address
    tmsg[4] = 0u;                                   // Output Hash address (not used in update)
    tmsg[5] = size;                                 // Input size
    tmsg[6] = 0u;                                   // Output size (not used in update)
    tmsg[7] = (uint32_t)ctxSize << SHIFT_16 | 0x4u; // CTX size | Flag (Bit3 = 1 -> Update)
    tmsg[8] = (uint32_t)alg;                        // Alg
    tmsg[9] = S3MU_ComputeMsgCrc(tmsg, HASH_SIZE - 1u);
    // CRC sum of all the words of the message (excluding the CRC itself)

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, HASH_SIZE);
    if (status != kStatus_Success)
    {
        return status;
    }
    /* Wait for response from Security Sub-System */
    if (ele_mu_get_response(mu, rmsg) != kStatus_Success)
    {
        return status;
    }

#if defined(ELE_CACHE_HANDLING) && (ELE_CACHE_HANDLING > 0u)
    DCACHE_InvalidateByRange((uint32_t)ctx->x, ctxSize);
#endif /* defined(ELE_CACHE_HANDLING) */

    /* Check that response corresponds to the sent command */
    if (rmsg[0] == HASH_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief ELE HASH
 *
 * This function update last data block (if needed) and provide final HASH digest in out buffer.
 *
 * param mu MU peripheral base address
 * param ctx Context of ELE HASH streaming operations used by ELE.
 * param alg define used hash algorithm, see hash_algo_t
 * param out pointer to output HASH data (size is defined by used algorithm),
 *       user must ensure this memory is available to ELE
 * param out_size the size of the output buffer, which must be equal or larger
 *       than the resulting HASH
 * param out_length pointer where to output the resulting length of the generated HASH,
 *       or the expected out_size of the output buffer if it is found to be too small
 * param msg pointer where data to be hashed can be found, may be zero
 * param size size of data in byte, may be zero
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail,
 *        kStatus_InvalidArgument if invalid argument
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange,
 *                  kStatus_ELE_BufferTooSmall
 */
status_t ELE_Hash_Finish(S3MU_Type *mu,
                         ele_hash_ctx_t *ctx,
                         hash_algo_t alg,
                         uint8_t *out,
                         uint32_t out_size,
                         uint32_t *out_length,
                         const uint8_t *msg,
                         size_t size)
{
    status_t status              = kStatus_Fail;
    uint32_t tmsg[HASH_SIZE]     = {0u};
    uint32_t rmsg[S3MU_RR_COUNT] = {0u};
    uint16_t ctxSize             = 0u;

    /* Check argument validity */
    if (mu == NULL || ctx == NULL || out == NULL || out_length == NULL)
    {
        return kStatus_InvalidArgument;
    }

    switch (alg)
    {
        case kELE_Sha224:
            ctxSize = HASH_CTX_SIZE_SHA224;
            break;
        case kELE_Sha256:
            ctxSize = HASH_CTX_SIZE_SHA256;
            break;
        case kELE_Sha384:
            ctxSize = HASH_CTX_SIZE_SHA384;
            break;
        case kELE_Sha512:
            ctxSize = HASH_CTX_SIZE_SHA512;
            break;
        case kELE_SM3256:
            ctxSize = HASH_CTX_SIZE_SM3256;
            break;

        default:
            status = kStatus_InvalidArgument;
            break;
    }

    if (status == kStatus_InvalidArgument)
    {
        return status;
    }

    tmsg[0] = HASH_HDR;                             // HASH Command Header
    tmsg[1] = 0u;                                   // MSB address (not used)
    tmsg[2] = ADD_OFFSET((uint32_t)ctx->x);         // CTX address
    tmsg[3] = ADD_OFFSET((uint32_t)msg);            // Input Hash address
    tmsg[4] = ADD_OFFSET((uint32_t)out);            // Output Hash address
    tmsg[5] = size;                                 // Input size
    tmsg[6] = out_size;                             // Output size (not used in update)
    tmsg[7] = (uint32_t)ctxSize << SHIFT_16 | 0x8u; // CTX size | Flag (Bit4 = 1 -> Finish)
    tmsg[8] = (uint32_t)alg;                        // Alg
    tmsg[9] = S3MU_ComputeMsgCrc(tmsg, HASH_SIZE - 1u);
    // CRC sum of all the words of the message (excluding the CRC itself)

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, HASH_SIZE);
    if (status != kStatus_Success)
    {
        return status;
    }
    /* Wait for response from Security Sub-System */
    if (ele_mu_get_response(mu, rmsg) != kStatus_Success)
    {
        return status;
    }

    /* Check that response corresponds to the sent command */
    if (rmsg[0] != HASH_RESPONSE_HDR)
    {
        return kStatus_Fail;
    }

#if defined(ELE_CACHE_HANDLING) && (ELE_CACHE_HANDLING > 0u)
    DCACHE_InvalidateByRange((uint32_t)out, out_size);
    DCACHE_InvalidateByRange((uint32_t)ctx->x, ctxSize);
#endif /* defined(ELE_CACHE_HANDLING) */

    /* Header OK, check for success */
    if (rmsg[1] == RESPONSE_SUCCESS)
    {
        *out_length = rmsg[2];
        return kStatus_Success;
    }
    else if (rmsg[1] == RESPONSE_ERROR_SIZE)
    {
        *out_length = rmsg[2];
        return kStatus_ELE_BufferTooSmall;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief ELE HMAC Generic
 *
 * This function computes HMAC (One Go) of a given message using EdgeLock Enclave.
 *
 * param mu MU peripheral base address
 * param msg pointer where input message data can be found, may be zero
 * param size size of input data in bytes, may be zero
 * param out pointer where the MAC buffer must be written by ELE (size depends on used alg)
 * param out_size pointer to the resulting output size of the chosen HMAC
 * param key pointer where the buffer with key in plaintext can be found
 * param key_size size of key in bytes
 * param alg define algorithm used for HMAC, see mac_algo_t
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail,
 *        kStatus_InvalidArgument if invalid argument
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_GenericHmac(S3MU_Type *mu,
                         const uint8_t *msg,
                         uint16_t size,
                         uint8_t *out,
                         uint32_t *out_size,
                         const uint8_t *key,
                         uint16_t key_size,
                         mac_algo_t alg)
{
    status_t status                  = kStatus_Fail;
    uint32_t tmsg[HMAC_GENERIC_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]     = {0u};
    uint16_t outSize                 = 0u;

    /* Check argument validity */
    if (mu == NULL || out == NULL || out_size == NULL || key == NULL)
    {
        return kStatus_InvalidArgument;
    }

    /* Currently ELE supports only SHA256 for MAC */
    switch (alg)
    {
        case kELE_Hmac256:
            outSize = 256u / 8u;
            break;
        default:
            status = kStatus_InvalidArgument;
            break;
    }

    if (status == kStatus_InvalidArgument)
    {
        return status;
    }

    tmsg[0] = HMAC_GENERIC_HDR;                         // HASH Command Header
    tmsg[1] = ADD_OFFSET((uint32_t)msg);                // Input msg address
    tmsg[2] = ADD_OFFSET((uint32_t)out);                // Output MAC address
    tmsg[3] = ADD_OFFSET((uint32_t)key);                // Key address
    tmsg[4] = size;                                     // Input size
    tmsg[5] = (uint32_t)key_size << SHIFT_16 | outSize; // Output size
    tmsg[6] = (uint32_t)alg;                            // Alg
    tmsg[7] = S3MU_ComputeMsgCrc(tmsg, HMAC_GENERIC_SIZE - 1u);
    // CRC sum of all the words of the message (excluding the CRC itself)

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, HMAC_GENERIC_SIZE);
    if (status != kStatus_Success)
    {
        return status;
    }
    /* Wait for response from Security Sub-System */
    if (ele_mu_get_response(mu, rmsg) != kStatus_Success)
    {
        return status;
    }

    /* Check that response corresponds to the sent command */
    if (rmsg[0] == HMAC_GENERIC_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        *out_size = (uint32_t)outSize;

#if defined(ELE_CACHE_HANDLING) && (ELE_CACHE_HANDLING > 0u)
        DCACHE_InvalidateByRange((uint32_t)out, *out_size);
#endif /* defined(ELE_CACHE_HANDLING) */

        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Open ELE Cipher Service
 *
 * This function opens Cipher Service for EdgeLock Enclave.
 *
 * param mu MU peripheral base address
 * param keystoreHandleID unique session ID obtained by calling ELE_OpenKeystore()
 * param cipherHandleID pointer to output unique Cipher session handle ID word
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_OpenCipherService(S3MU_Type *mu, uint32_t keystoreHandleID, uint32_t *cipherHandleID)
{
    status_t status                         = kStatus_Fail;
    uint32_t tmsg[OPEN_CIPHER_SESSION_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]            = {0u};

    tmsg[0] = OPEN_CIPHER_SESSION; // OPEN_SESSION Command Header
    tmsg[1] = keystoreHandleID;    // Key store handle ID
    tmsg[2] = 0x00000000u;         // User Input address extension (UIA) - not used
    tmsg[3] = 0x00000000u;         // User Output address extension (UOA) - not used
    tmsg[4] = 0x00000000u;         // Flags (reserved)
    tmsg[5] = S3MU_ComputeMsgCrc(tmsg, OPEN_CIPHER_SESSION_SIZE - 1u);
    // CRC sum of all the words of the message (excluding the CRC itself)

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, OPEN_CIPHER_SESSION_SIZE);
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
    if (rmsg[0] == OPEN_CIPHER_SESSION_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        /* read Cipher Handle ID data */
        *cipherHandleID = rmsg[2];
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Close ELE Cipher Service
 *
 * This function closes the Cipher Service for EdgeLock Enclave.
 *
 * param mu MU peripheral base address
 * param cipherHandleID unique Cipher handle ID obtained by calling ELE_OpenCipherService()
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_CloseCipherService(S3MU_Type *mu, uint32_t cipherHandleID)
{
    status_t status                          = kStatus_Fail;
    uint32_t tmsg[CLOSE_CIPHER_SESSION_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]             = {0u};

    tmsg[0] = CLOSE_CIPHER_SESSION; // Close Cipher session Command Header
    tmsg[1] = cipherHandleID;       // Cipher handle ID

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, CLOSE_CIPHER_SESSION_SIZE);
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
    if (rmsg[0] == CLOSE_CIPHER_SESSION_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief ELE Cipher
 *
 * This function encrypt or decrypt data usign crypto cipher (AES-ECB/CBC/CTR) with keys in EdgeLock Enclave service.
 *
 * param mu MU peripheral base address
 * param cipherHandleID unique Cipher handle ID obtained by calling ELE_OpenCipherService()
 * param conf Pointer where HSM cipher configuration structure can be found
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_Cipher(S3MU_Type *mu, uint32_t cipherHandleID, ele_hsm_cipher_t *conf)
{
    status_t status                   = kStatus_Fail;
    uint32_t tmsg[CIPHER_ONE_GO_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]      = {0u};

    tmsg[0]  = CIPHER_ONE_GO;                                    // CIPHER_ONE_GO Command Header
    tmsg[1]  = cipherHandleID;                                   // Cipher handle ID
    tmsg[2]  = conf->keyID;                                      // key ID
    tmsg[3]  = ADD_OFFSET(conf->iv);                             // Initialization vector address
    tmsg[4]  = (uint32_t)conf->mode << SHIFT_16 | conf->iv_size; // Mode identifier |Initialization vector byte length
    tmsg[5]  = (uint32_t)conf->alg;                              // Algorithm identifier
    tmsg[6]  = ADD_OFFSET(conf->input);                          // Input data address
    tmsg[7]  = ADD_OFFSET(conf->output);                         // Output data address
    tmsg[8]  = conf->input_size;                                 // Input byte length
    tmsg[9]  = conf->input_size;                                 // Output byte length = Input byte length
    tmsg[10] = S3MU_ComputeMsgCrc(tmsg, CIPHER_ONE_GO_SIZE - 1u);
    // CRC sum of all the words of the message (excluding the CRC itself)

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, CIPHER_ONE_GO_SIZE);
    if (status != kStatus_Success)
    {
        return status;
    }
    /* Wait for response from Security Sub-System */
    if (ele_mu_get_response(mu, rmsg) != kStatus_Success)
    {
        return status;
    }
    /* Check that response corresponds to the sent command */
    if (rmsg[0] == CIPHER_ONE_GO_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        /* Write output size from ELE if required */
        if (conf->output_size != NULL)
        {
            *conf->output_size = rmsg[2];
        }

#if defined(ELE_CACHE_HANDLING) && (ELE_CACHE_HANDLING > 0u)
        DCACHE_InvalidateByRange((uint32_t)conf->output, conf->input_size);
#endif /* defined(ELE_CACHE_HANDLING) */

        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Open ELE AEAD Cipher
 *
 * This function encrypt or decrypt data usign crypto AES AEAD with keys in EdgeLock Enclave service.
 *
 * param mu MU peripheral base address
 * param cipherHandleID unique Cipher handle ID obtained by calling ELE_OpenCipherService()
 * param conf Pointer where HSM cipher configuration structure can be found
 * param aad pointer where a additional authenticated data can be found
 * param aad_size size of aad data in bytes
 * param iv_gen_flags Relevant for GCM only. Specifies mode of generating IV for GCM, for CCM must be 0
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_Aead(S3MU_Type *mu,
                  uint32_t cipherHandleID,
                  ele_hsm_cipher_t *conf,
                  uint32_t aad,
                  size_t aad_size,
                  iv_generation_t iv_gen_flags)
{
    status_t status                 = kStatus_Fail;
    uint32_t tmsg[CIPHER_AEAD_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]    = {0u};

    uint32_t flags = (uint32_t)iv_gen_flags | (uint32_t)conf->mode; // IV generation flags | Mode

    tmsg[0]  = CIPHER_AEAD;                                         // GENERIC_AEAD Command Header
    tmsg[1]  = cipherHandleID;                                      // Cipher handle ID
    tmsg[2]  = conf->keyID;                                         // key ID
    tmsg[3]  = ADD_OFFSET(conf->iv);                                // Initialization vector address
    tmsg[4]  = flags << SHIFT_16 | conf->iv_size;                   // Flags | Initialization vector  byte length
    tmsg[5]  = (uint32_t)conf->alg;                                 // Algorithm identifier
    tmsg[6]  = ADD_OFFSET(aad);                                     // Additional authentication data address
    tmsg[7]  = aad_size;                                            // Additional authentication data size
    tmsg[8]  = ADD_OFFSET(conf->input);                             // Input data address
    tmsg[9]  = ADD_OFFSET(conf->output);                            // Output data address
    tmsg[10] = conf->input_size;                                    // Input byte length
    tmsg[11] = (uint32_t)*conf->output_size;                        // Output byte length
    tmsg[12] = S3MU_ComputeMsgCrc(tmsg, CIPHER_AEAD_SIZE - 1u);
    // CRC sum of all the words of the message (excluding the CRC itself)

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, CIPHER_AEAD_SIZE);
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
    if (rmsg[0] == CIPHER_AEAD_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        /* read output size from ELE */
        if (conf->output_size != NULL)
        {
            *conf->output_size = rmsg[2];
        }

#if defined(ELE_CACHE_HANDLING) && (ELE_CACHE_HANDLING > 0u)
        DCACHE_InvalidateByRange((uint32_t)conf->output, conf->input_size);
#endif /* defined(ELE_CACHE_HANDLING) */

        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Open ELE MAC Service
 *
 * This function opens MAC Service for EdgeLock Enclave.
 *
 * param mu MU peripheral base address
 * param keystoreHandleID unique session ID obtained by calling ELE_OpenKeystore()
 * param MacHandleID pointer to output unique MAC session handle ID word
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_OpenMacService(S3MU_Type *mu, uint32_t keystoreHandleID, uint32_t *MacHandleID)
{
    status_t status                      = kStatus_Fail;
    uint32_t tmsg[OPEN_MAC_SESSION_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]         = {0u};

    tmsg[0] = OPEN_MAC_SESSION; // OPEN_SESSION Command Header
    tmsg[1] = keystoreHandleID; // Key store handle ID
    tmsg[2] = 0x00000000u;      // User Input address extension (UIA) - not used
    tmsg[3] = 0x00000000u;      // User Output address extension (UOA) - not used
    tmsg[4] = 0x00000000u;      // Flags (reserved)
    tmsg[5] = S3MU_ComputeMsgCrc(tmsg, OPEN_MAC_SESSION_SIZE - 1u);
    // CRC sum of all the words of the message (excluding the CRC itself)

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, OPEN_MAC_SESSION_SIZE);
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
    if (rmsg[0] == OPEN_MAC_SESSION_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        /* read MAC Handle ID data */
        *MacHandleID = rmsg[2];
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Close ELE MAC Service
 *
 * This function closes the MAC Service for EdgeLock Enclave.
 *
 * param mu MU peripheral base address
 * param MacHandleID unique MAC handle ID obtained by calling ELE_OpenMacService()
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_CloseMacService(S3MU_Type *mu, uint32_t MacHandleID)
{
    status_t status                       = kStatus_Fail;
    uint32_t tmsg[CLOSE_MAC_SESSION_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]          = {0u};

    tmsg[0] = CLOSE_MAC_SESSION; // Close MAC session Command Header
    tmsg[1] = MacHandleID;       // MAC handle ID

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, CLOSE_MAC_SESSION_SIZE);
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
    if (rmsg[0] == CLOSE_MAC_SESSION_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief ELE MAC
 *
 * This function is used to perform one-shot MAC generation or verification.
 *
 * param mu MU peripheral base address
 * param conf pointer where the MAC configuration structure can be found
 * param verify_status pointer to verification status in kMAC_Verify mode. Value MAC_VERIFY_SUCCESS (0x6C1AA1C6) is
 * verification success. Value 0x0 is failure. This value has no sense in kMAC_Generate mode, so can be NULL.
 * param out_mac_size pointer where to save the size, in bytes, of the resulting MAC in kMAC_Generate mode,
 *       or the input MAC size in kMAC_Verify mode
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 *        kStatus_InvalidArgument if invalid argument
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange,
 *                  kStatus_ELE_BufferTooSmall
 */
status_t ELE_Mac(S3MU_Type *mu, ele_mac_t *conf, uint32_t *verify_status, uint16_t *out_mac_size)
{
    status_t status                = kStatus_Fail;
    uint32_t tmsg[MAC_ONE_GO_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]   = {0u};

    /* Check argument validity */
    if (mu == NULL || conf == NULL || out_mac_size == NULL)
    {
        return kStatus_InvalidArgument;
    }

    /* Cannot be NULL with kMAC_Verify */
    if (verify_status == NULL && conf->mode == kMAC_Verify)
    {
        return kStatus_InvalidArgument;
    }

    tmsg[0] = MAC_ONE_GO;                                        // MAC_ONE_GO Command Header
    tmsg[1] = conf->mac_handle_id;                               // MAC handle ID
    tmsg[2] = conf->key_id;                                      // key ID
    tmsg[3] = ADD_OFFSET(conf->payload);                         // Payload data address
    tmsg[4] = ADD_OFFSET(conf->mac);                             // MAC data address
    tmsg[5] = conf->payload_size;                                // Payload byte length
    tmsg[6] = (uint32_t)conf->mode << SHIFT_16 | conf->mac_size; // Flags | MAC size
    tmsg[7] = (uint32_t)conf->alg;                               // Algorithm identifier
    tmsg[8] = S3MU_ComputeMsgCrc(tmsg, MAC_ONE_GO_SIZE - 1u);
    // CRC sum of all the words of the message (excluding the CRC itself)

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, MAC_ONE_GO_SIZE);
    if (status != kStatus_Success)
    {
        return status;
    }

    /* Wait for response from Security Sub-System */
    if (ele_mu_get_response(mu, rmsg) != kStatus_Success)
    {
        return status;
    }

    /* Check that response corresponds to the sent command */
    if (rmsg[0] != MAC_ONE_GO_RESPONSE_HDR)
    {
        return kStatus_Fail;
    }

    /* Header OK, check for success */
    if (rmsg[1] == RESPONSE_SUCCESS)
    {
        /* Checking verification status has meaning only for kMAC_Verify mode */
        if (conf->mode == kMAC_Verify)
        {
            /* read verification status from ELE */
            *verify_status = rmsg[2];
        }

        /* Return the output MAC size field from the response */
        *out_mac_size = (uint16_t)(rmsg[3] & MAC_ONE_GO_MAC_SIZE_MASK);

        if (conf->mode == kMAC_Generate)
        {
#if defined(ELE_CACHE_HANDLING) && (ELE_CACHE_HANDLING > 0u)
            DCACHE_InvalidateByRange((uint32_t)conf->mac, *out_mac_size);
#endif /* defined(ELE_CACHE_HANDLING) */
        }

        return kStatus_Success;
    }
    else if (rmsg[1] == RESPONSE_ERROR_SIZE)
    {
        /* Return the expected size and fail with error */
        *out_mac_size = (uint16_t)(rmsg[3] & MAC_ONE_GO_MAC_SIZE_MASK);
        return kStatus_ELE_BufferTooSmall;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief ELE RNG Get random
 *
 * This function gets random number from ELE RNG.
 *
 * param mu MU peripheral base address
 * param output pointer to output buffer where to store random number
 * param size size of requested random data
 * param reseed_flag option to reseed the DRBG instance
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_RngGetRandom(S3MU_Type *mu, uint32_t *output, size_t size, rng_reseed_flag_t reseed_flag)
{
    status_t status                    = kStatus_Fail;
    uint32_t tmsg[GET_RNG_RANDOM_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]       = {0u};

    tmsg[0] = GET_RNG_RANDOM;                    // GET_RNG_RANDOM Command Header
    tmsg[1] = (uint16_t)reseed_flag << SHIFT_16; // Reseed flag
    tmsg[2] = ADD_OFFSET((uint32_t)output);      // Output buffer
    tmsg[3] = size;                              // Size of requested data

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, GET_RNG_RANDOM_SIZE);
    if (status != kStatus_Success)
    {
        return status;
    }
    /* Wait for response from Security Sub-System */
    status = S3MU_GetResponse(mu, rmsg);
    if (status != kStatus_Success)
    {
        return status;
    }
    /* Check that response corresponds to the sent command */
    if (rmsg[0] == GET_RNG_RANDOM_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
#if defined(ELE_CACHE_HANDLING) && (ELE_CACHE_HANDLING > 0u)
        DCACHE_InvalidateByRange((uint32_t)output, size);
#endif /* defined(ELE_CACHE_HANDLING) */

        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Open and Create Key Store
 *
 * This function create key store and open key store services in the EdgeLock Enclave.
 *
 * param mu MU peripheral base address
 * param sessionID unique session ID obtained by calling ELE_OpenSession()
 * param conf pointer where keystore configuration structure can be found
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_CreateKeystore(S3MU_Type *mu, uint32_t sessionID, ele_keystore_t *conf, uint32_t *keystoreHandleID)
{
    status_t status                    = kStatus_Fail;
    uint32_t tmsg[OPEN_KEY_STORE_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]       = {0u};

    /* Create Flag word */

    /*   +----------------+----------+------------------------+
     *   | Min MAC length |  Flags   |      Max updates       |
     *   +----------------+----------+------------------------+
     *   | bit 31-24      | Bit 23-16|       Bit 15-0         |
     *   +----------------+----------+------------------------+
     */
    uint32_t flags = ((uint32_t)conf->min_mac_len << MIN_MAC_LEN_SHIFT) |
                     ((uint32_t)conf->min_mac_check << MIN_MAC_FLAG_SHIFT) | (1UL << KEYSTORE_CREATE_SHIFT) |
                     (conf->max_updates);

    tmsg[0] = OPEN_KEY_STORE; // OPEN_KEY_STORE Command Header
    tmsg[1] = sessionID;      // Session handle ID
    tmsg[2] = conf->id;       // Key Store ID (User defined)
    tmsg[3] = conf->nonce;    // Authentication nonce
    tmsg[4] = flags;          // MAC Min length (bit 31-24) | Flag (bit 23-16) | MAX update: (bit 15-0)
    tmsg[5] = S3MU_ComputeMsgCrc(tmsg, OPEN_KEY_STORE_SIZE - 1u);

    /* Send message Security Sub-System */
    if (S3MU_SendMessage(mu, tmsg, OPEN_KEY_STORE_SIZE) != kStatus_Success)
    {
        return status;
    }
    /* Wait for response from Security Sub-System */
    if (ele_mu_get_response(mu, rmsg) != kStatus_Success)
    {
        return status;
    }

    /* Check that response corresponds to the sent command */
    if (rmsg[0] == OPEN_KEY_STORE_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        /* read Key Store ID data */
        *keystoreHandleID = rmsg[2];
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Open and Create Key Store
 *
 * This function create key store and open key store services in the EdgeLock Enclave.
 *
 * param mu MU peripheral base address
 * param sessionID unique session ID obtained by calling ELE_OpenSession()
 * param conf pointer where keystore configuration structure can be found
 * param keystoreHandleID pointer where unique Keystore handle ID word will be stored
 * param keystoreChunk pointer to Keystore chunk exported via ELE_ExportChunks()
 * param chunkSize size of chunk to be imported. Obtained via ELE_ExportChunks()
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_OpenKeystore(S3MU_Type *mu,
                          uint32_t sessionID,
                          ele_keystore_t *conf,
                          uint32_t *keystoreHandleID,
                          uint32_t *keystoreChunk,
                          size_t chunkSize)
{
    status_t status                    = kStatus_Fail;
    uint32_t tmsg[OPEN_KEY_STORE_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]       = {0u};

    /* Create Flag word */

    /*   +----------------+----------+------------------------+
     *   | Min MAC length |  Flags   |      Max updates       |
     *   +----------------+----------+------------------------+
     *   | bit 31-24      | Bit 23-16|       Bit 15-0         |
     *   +----------------+----------+------------------------+
     */
    uint32_t flags = (uint32_t)((uint32_t)conf->min_mac_len << MIN_MAC_LEN_SHIFT) |
                     (uint32_t)((uint32_t)conf->min_mac_check << MIN_MAC_FLAG_SHIFT) | (0UL << KEYSTORE_CREATE_SHIFT) |
                     (conf->max_updates);

    tmsg[0] = OPEN_KEY_STORE; // OPEN_KEY_STORE Command Header
    tmsg[1] = sessionID;      // Session handle ID
    tmsg[2] = conf->id;       // Key Store ID (User defined)
    tmsg[3] = conf->nonce;    // Authentication nonce
    tmsg[4] = flags;          // MAC Min length (bit 31-24) | Flag (bit 23-16) | MAX update: (bit 15-0)
    tmsg[5] = S3MU_ComputeMsgCrc(tmsg, OPEN_KEY_STORE_SIZE - 1u);

    /* Send message Security Sub-System */
    if (S3MU_SendMessage(mu, tmsg, OPEN_KEY_STORE_SIZE) != kStatus_Success)
    {
        return status;
    }

    if ((keystoreChunk != NULL) && (chunkSize != 0u))
    {
        /* Prepare data for chunk import */
        ele_data_storage_t storage_conf;
        storage_conf.chunk_size = chunkSize;
        storage_conf.chunk_addr = (uint32_t *)ADD_OFFSET((uint32_t)keystoreChunk);

        /* Import chunk into the ELE */
        status = nvm_storage_get_req(mu, &storage_conf);
        if (status != kStatus_Success)
        {
            return status;
        }
    }

    /* Wait for response from Security Sub-System */
    if (ele_mu_get_response(mu, rmsg) != kStatus_Success)
    {
        return status;
    }

    /* Check that response corresponds to the sent command */
    if (rmsg[0] == OPEN_KEY_STORE_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        /* read Key Store ID data */
        *keystoreHandleID = rmsg[2];
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Close Key Store
 *
 * This function closes key store and its services in the EdgeLock Enclave.
 *
 * param mu MU peripheral base address
 * param keystoreHandleID unique session ID obtained by calling ELE_OpenKeystore()
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_CloseKeystore(S3MU_Type *mu, uint32_t keystoreHandleID)
{
    status_t status                    = kStatus_Fail;
    uint32_t tmsg[OPEN_KEY_STORE_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]       = {0u};

    tmsg[0] = CLOSE_KEY_STORE;  // CLOSE_KEY_STORE Command Header
    tmsg[1] = keystoreHandleID; // Key Store HandleID
    tmsg[2] = 0x0;              // Flags (reserved)

    /* Send message Security Sub-System */
    if (S3MU_SendMessage(mu, tmsg, CLOSE_KEY_STORE_SIZE) != kStatus_Success)
    {
        return status;
    }
    /* Wait for response from Security Sub-System */
    if (ele_mu_get_response(mu, rmsg) != kStatus_Success)
    {
        return status;
    }

    /* Check that response corresponds to the sent command */
    if (rmsg[0] == CLOSE_KEY_STORE_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Open ELE Key Management Service
 *
 * This function opens Key Management Service for EdgeLock Enclave.
 *
 * param mu MU peripheral base address
 * param keystoreHandleID unique session ID obtained by calling ELE_OpenKeystore()
 * param keyHandleID pointer where unique key management handle ID word will be stored
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_OpenKeyService(S3MU_Type *mu, uint32_t keystoreHandleID, uint32_t *keyHandleID)
{
    status_t status                  = kStatus_Fail;
    uint32_t tmsg[KEY_MNG_OPEN_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]     = {0u};

    tmsg[0] = KEY_MNG_OPEN;     // KEY_MNG_OPEN Command Header
    tmsg[1] = keystoreHandleID; // Session handle ID
    tmsg[2] = 0x00000000u;      // User Input address extension (UIA) - not used
    tmsg[3] = 0x00000000u;      // User Output address extension (UOA) - not used
    tmsg[4] = 0x00000000u;      // Flag (reserved)
    tmsg[5] = S3MU_ComputeMsgCrc(tmsg, KEY_MNG_OPEN_SIZE - 1u);

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, KEY_MNG_OPEN_SIZE);
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
    if (rmsg[0] == KEY_MNG_OPEN_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        /* read Key Management Handle ID data */
        *keyHandleID = rmsg[2];
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Close ELE Key Management Service
 *
 * This function closes the Key Management Service for EdgeLock Enclave.
 *
 * param mu MU peripheral base address
 * param keyHandleID unique key management handle ID obtained by calling ELE_OpenKeyService()
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_CloseKeyService(S3MU_Type *mu, uint32_t keyHandleID)
{
    status_t status                  = kStatus_Fail;
    uint32_t tmsg[KEY_MNG_OPEN_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]     = {0u};

    tmsg[0] = KEY_MNG_CLOSE; // KEY_MNG_CLOSE Command Header
    tmsg[1] = keyHandleID;   // Key Management handle ID

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, KEY_MNG_CLOSE_SIZE);
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
    if (rmsg[0] == KEY_MNG_CLOSE_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief ELE Generate Key
 *
 * This function generates a key inside given keys store in the EdgeLock Enclave.
 *
 * param mu MU peripheral base address
 * param keyHandleID unique key management handle ID obtained by calling ELE_OpenKeyService()
 * param conf pointer where key generate configuration structure can be found
 * param keyID pointer where unique Key ID word will be stored
 * param outSize pointer where to save the resulting key size or the expected
 *       size of the key buffer, if the buffer is found to be too small, in which case
 *       an error is also returned
 * param monotonic if true, the monotonic counter flag is set
 * param sync if true, the SYNC flag is set
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 *        kStatus_InvalidArgument if invalid argument
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange,
 *                  kStatus_ELE_BufferTooSmall
 */
status_t ELE_GenerateKey(S3MU_Type *mu,
                         uint32_t keyHandleID,
                         ele_gen_key_t *conf,
                         uint32_t *keyID,
                         uint16_t *outSize,
                         bool monotonic,
                         bool sync)
{
    status_t status              = kStatus_Fail;
    uint32_t tmsg[KEY_GEN_SIZE]  = {0u};
    uint32_t rmsg[S3MU_RR_COUNT] = {0u};
    uint32_t flags               = 0u;

    if (mu == NULL || conf == NULL || keyID == NULL || outSize == NULL)
    {
        return kStatus_InvalidArgument;
    }

    if (conf->key_group > 100u)
    {
        return kStatus_OutOfRange;
    }

    /* Set flags */
    if (monotonic == true)
    {
        flags |= SYNC_MONOTONIC;
    }

    if (sync == true)
    {
        flags |= SYNC_OP;
    }

    tmsg[0]  = KEY_GEN;                                                    // KEY_GEN Command Header
    tmsg[1]  = keyHandleID;                                                // Key handle ID
    tmsg[2]  = conf->key_id;                                               // Key ID (0 = FW will choose)
    tmsg[3]  = (uint32_t)conf->key_group << SHIFT_16 | conf->pub_key_size; // Key Group | Public key size
    tmsg[4]  = (uint32_t)conf->key_size << SHIFT_16 | conf->key_type;      // Key size | Key Type
    tmsg[5]  = (uint32_t)conf->key_lifetime;                               // Lifetime
    tmsg[6]  = (uint32_t)conf->key_usage;                                  // Key Usage
    tmsg[7]  = conf->permitted_alg;                                        // Permited algorithms
    tmsg[8]  = conf->key_lifecycle;                                        // Key Lifecycle (1 = OPEN);
    tmsg[9]  = flags;                                                      // FLAGS (Monotonic counter, SYNC)
    tmsg[10] = ADD_OFFSET(conf->pub_key_addr);                             // Output buffer address for public key
    tmsg[11] = S3MU_ComputeMsgCrc(tmsg, KEY_GEN_SIZE - 1u);

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, KEY_GEN_SIZE);
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
    if (rmsg[0] != KEY_GEN_RESPONSE_HDR)
    {
        return kStatus_Fail;
    }

    /* Header is OK, check for success */
    if (rmsg[1] == RESPONSE_SUCCESS)
    {
        /* Read Key pair ID data and key size */
        *keyID   = rmsg[2];
        *outSize = (uint16_t)(rmsg[3] & KEY_GEN_KEY_SIZE_MASK);

#if defined(ELE_CACHE_HANDLING) && (ELE_CACHE_HANDLING > 0u)
        DCACHE_InvalidateByRange((uint32_t)conf->pub_key_addr, *outSize);
#endif /* defined(ELE_CACHE_HANDLING) */

        return kStatus_Success;
    }
    else if (rmsg[1] == RESPONSE_ERROR_SIZE)
    {
        /* Save expected key size */
        *outSize = (uint16_t)(rmsg[3] & KEY_GEN_KEY_SIZE_MASK);
        return kStatus_ELE_BufferTooSmall;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief ELE Generate Public Key
 *
 * This function generates a public key from private asymmetric key inside EdgeLock Enclave.
 *
 * param mu MU peripheral base address
 * param keystoreHandleID unique session ID obtained by calling ELE_OpenKeystore()
 * param conf pointer where key generate configuration structure can be found
 * param keyID Identifier of asymmetric key inside ELE
 * param output output bufer where the public key will be written
 * param outKeySize Length in bytes of output key buffer
 * param outSize pointer where to save the resulting key size or the expected
 *       size of the key buffer, if the buffer is found to be too small, in which case
 *       an error is also returned
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail,
 *        kStatus_InvalidArgument if invalid argument
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange,
 *                  kStatus_ELE_BufferTooSmall
 */
status_t ELE_GeneratePubKey(
    S3MU_Type *mu, uint32_t keystoreHandleID, uint32_t keyID, uint32_t *output, uint32_t outKeySize, uint16_t *outSize)
{
    status_t status              = kStatus_Fail;
    uint32_t tmsg[KEY_GEN_SIZE]  = {0u};
    uint32_t rmsg[S3MU_RR_COUNT] = {0u};

    if (mu == NULL || output == NULL || outSize == NULL)
    {
        return kStatus_InvalidArgument;
    }

    tmsg[0] = PUB_KEY_GEN;                  // KEY_GEN Command Header
    tmsg[1] = keystoreHandleID;             // Keystore handle ID
    tmsg[2] = keyID;                        // Asymmetric Key ID
    tmsg[3] = 0u;                           // MSB address (not used)
    tmsg[4] = ADD_OFFSET((uint32_t)output); // Pubblic key output address
    tmsg[5] = outKeySize;                   // Length in bytes of output key buffer
    tmsg[6] = S3MU_ComputeMsgCrc(tmsg, PUB_KEY_GEN_SIZE - 1u);

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, PUB_KEY_GEN_SIZE);
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
    if (rmsg[0] != PUB_KEY_GEN_RESPONSE_HDR)
    {
        return kStatus_Fail;
    }

    /* Header is OK, check for success */
    if (rmsg[1] == RESPONSE_SUCCESS)
    {
        *outSize = (uint16_t)(rmsg[2] & PUB_KEY_GEN_KEY_SIZE_MASK);

#if defined(ELE_CACHE_HANDLING) && (ELE_CACHE_HANDLING > 0u)
        DCACHE_InvalidateByRange((uint32_t)output, *outSize);
#endif /* defined(ELE_CACHE_HANDLING) */

        return kStatus_Success;
    }
    else if (rmsg[1] == RESPONSE_ERROR_SIZE)
    {
        *outSize = (uint16_t)(rmsg[2] & PUB_KEY_GEN_KEY_SIZE_MASK);
        return kStatus_ELE_BufferTooSmall;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief ELE Delete Key
 *
 * This function deletes a key from a keystore in the EdgeLock Enclave.
 *
 * param mu MU peripheral base address
 * param keyHandleID unique key management handle ID obtained by calling ELE_OpenKeyService()
 * param keyID unique key ID obtained by calling ELE_GenerateKey()
 * param monotonic if true, the monotonic counter flag is set
 * param sync if true, the SYNC flag is set
 *
 * return kStatus_Success if success, kStatus_Fail if fail,
 *         kStatus_InvalidArgument if invalid argument
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_DeleteKey(S3MU_Type *mu, uint32_t keyHandleID, uint32_t keyID, bool monotonic, bool sync)
{
    status_t status              = kStatus_Fail;
    uint32_t tmsg[KEY_DEL_SIZE]  = {0u};
    uint32_t rmsg[S3MU_RR_COUNT] = {0u};
    uint32_t flags               = 0u;

    if (mu == NULL)
    {
        return kStatus_InvalidArgument;
    }

    /* Set flags */
    if (monotonic == true)
    {
        flags |= SYNC_MONOTONIC;
    }

    if (sync == true)
    {
        flags |= SYNC_OP;
    }

    tmsg[0] = KEY_DEL;           // KEY_DEL Command Header
    tmsg[1] = keyHandleID;       // Key management handle ID
    tmsg[2] = keyID;             // Key ID
    tmsg[3] = flags << SHIFT_16; // FLAGS (Monotonic counter, SYNC)

    /* Send message to Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, KEY_DEL_SIZE);
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

    /* Check if response header corresponds to the sent command and if success */
    if (rmsg[0] == KEY_DEL_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief ELE Export Chunks Management Service
 *
 * This function provides the Key Group Management Service for exporting keygroup, keystore and storage master chunks.
 *
 * param mu MU peripheral base address
 * param keyHandleID unique key management handle ID obtained by calling ELE_OpenKeyService()
 * param exportKeyGroup If true, key group (keyGroupID) chunk is exported, if false, only keystore and master
 * param keyGroupID unique key group ID choosen by user. Not used if exportKeyGroup is false
 * param monotonic  If true, Monotonic counter increment happen (anti-rollback protection)
 * param chunks ELE Chunks container structure, see ele_chunks_t.
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_ExportChunks(
    S3MU_Type *mu, uint32_t keyHandleID, bool exportKeyGroup, uint32_t keyGroupID, bool monotonic, ele_chunks_t *chunks)
{
    status_t status                   = kStatus_Fail;
    uint32_t tmsg[KEY_MNG_GROUP_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]      = {0u};
    size_t unused_size;
    uint32_t flags = 0u;

    if (chunks == NULL)
    {
        /* Operation with chunk(s) requested, but no address for import or export provided */
        return kStatus_Fail;
    }

    if (exportKeyGroup == false)
    {
        flags      = SYNC_OP_NO_KEY;
        keyGroupID = 0u;
    }
    else
    {
        flags = SYNC_OP;
    }

    /* This will trigger update anti-roolback counter in fuse */
    if (monotonic == true)
    {
        flags |= SYNC_MONOTONIC;
    }

    tmsg[0] = KEY_MNG_GROUP;                  // KEY_MNG_GROUP Command Header
    tmsg[1] = keyHandleID;                    // Key Management handle ID
    tmsg[2] = flags << SHIFT_16 | keyGroupID; // Sync Operation

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, KEY_MNG_GROUP_SIZE);
    if (status != kStatus_Success)
    {
        return status;
    }

    /* Skip key group export if only keystore and master are required */
    if (exportKeyGroup == true)
    {
        /* Handle export of key group chunk */
        chunks->KeyGroupChunk = nvm_storage_export_req(mu, chunks->KeyGroupChunk, &chunks->KeyGroupSize);
        if (chunks->KeyGroupChunk == NULL)
        {
            return kStatus_Fail;
        }

#if defined(ELE_CACHE_HANDLING) && (ELE_CACHE_HANDLING > 0u)
        DCACHE_InvalidateByRange((uint32_t)chunks->KeyGroupChunk, chunks->KeyGroupSize);
#endif /* defined(ELE_CACHE_HANDLING) */
    }

    /* Handle export of key store chunk */
    chunks->KeyStoreChunk = nvm_storage_export_req(mu, chunks->KeyStoreChunk, &chunks->KeyStoreSize);
    if (chunks->KeyStoreChunk == NULL)
    {
        return kStatus_Fail;
    }
#if defined(ELE_CACHE_HANDLING) && (ELE_CACHE_HANDLING > 0u)
    DCACHE_InvalidateByRange((uint32_t)chunks->KeyStoreChunk, chunks->KeyStoreSize);
#endif /* defined(ELE_CACHE_HANDLING) */

    /* Handle export of storage master chunk */
    if (nvm_storage_export_req(mu, chunks->MasterChunk, &unused_size) == NULL || unused_size != MASTER_CHUNK_SIZE)
    {
        /* Even if chunks->MasterChunk is allocated as spart of ele_chunks_t structure,
         * nvm_storage_export_req() return it's address if success, NULL otherwise.
         */
        return kStatus_Fail;
    }
#if defined(ELE_CACHE_HANDLING) && (ELE_CACHE_HANDLING > 0u)
    DCACHE_InvalidateByRange((uint32_t)chunks->MasterChunk, MASTER_CHUNK_SIZE);
#endif /* defined(ELE_CACHE_HANDLING) */

    /* Wait for response from Security Sub-System */
    status = S3MU_GetResponse(mu, rmsg);
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
 * brief ELE Key Management Service
 *
 * This function provides the Key Group Management Service for EdgeLock Enclave.
 *
 * param mu MU peripheral base address
 * param keyHandleID unique key management handle ID obtained by calling ELE_OpenKeyService()
 * param operation Requested opration, see key_group_mng_t enum
 * param addr If operation with chunks is requested, this address is used to either Import or Export chunk.
 * param size If operation with chunks is requested, this size is used to either Import or Export chunk.
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_ManageKeyGroup(
    S3MU_Type *mu, uint32_t keyHandleID, uint32_t keyGroupID, key_group_mng_t operation, uint32_t *addr, size_t size)
{
    status_t status                   = kStatus_Fail;
    uint32_t tmsg[KEY_MNG_GROUP_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]      = {0u};
    ele_data_storage_t storage_conf;

    if ((operation == kELE_keyMngImport || operation == kELE_keyMngExport) && addr == NULL)
    {
        /* Operation with chunk(s) requested, but no address for import or export provided */
        return kStatus_Fail;
    }

    tmsg[0] = KEY_MNG_GROUP; // KEY_MNG_GROUP Command Header
    tmsg[1] = keyHandleID;   // Key Management handle ID
    tmsg[2] = (uint32_t)operation << SHIFT_16 | keyGroupID;

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, KEY_MNG_GROUP_SIZE);
    if (status != kStatus_Success)
    {
        return status;
    }

    switch (operation)
    {
        case kELE_keyMngImport:
            /* Prepare data for chunk import */
            storage_conf.chunk_size = size;
            storage_conf.chunk_addr = (uint32_t *)addr;

            /* Import chunk into the ELE */
            status = nvm_storage_get_req(mu, &storage_conf);
            if (status != kStatus_Success)
            {
                return status;
            }

            break;
        case kELE_keyMngExport:
            /* Handle export of key group chunk */
            addr = nvm_storage_export_req(mu, addr, &size);
            if (addr == NULL)
            {
                return kStatus_Fail;
            }

            break;
        default:
            /* Unlock or lock - no chunk needed */
            break;
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
 * brief ELE Storage Master Export Finish
 *
 * This function provides Storage Master Export Finish Service for EdgeLock Enclave.
 * This is sent to ELE as acknowledgement after exporting master chunk.
 *
 * param mu MU peripheral base address
 * param nvmStorageID unique session ID obtained by calling ELE_OpenNvmStorageService()
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_StorageExportFinish(S3MU_Type *mu, uint32_t nvmStorageID)
{
    chunk_export_finish_t finish_response;

    finish_response.header.value   = EXPORT_FINISH_RESPONSE_HDR;
    finish_response.storage_handle = nvmStorageID; /* NVM Storage handle ID */
    finish_response.status         = RESPONSE_SUCCESS;

    /* Send Storage export finish response to Security Sub-System */
    return S3MU_SendMessage(mu, &finish_response, STORAGE_EXPORT_CHUNK_SIZE);
}

/*!
 * brief ELE Storage Master Import Service
 *
 * This function provides Storage Master Import Service for EdgeLock Enclave.
 * This must be called prior opening keystore stored in the NVM.
 *
 * param mu MU peripheral base address
 * param nvmStorageID unique session ID obtained by calling ELE_OpenNvmStorageService()
 * param addr Address of storage master chunk to be imported
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_StorageMasterImport(S3MU_Type *mu, uint32_t nvmStorageID, uint32_t *addr)
{
    status_t status                       = kStatus_Fail;
    uint32_t tmsg[NVM_MASTER_IMPORT_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]          = {0u};

    if (addr == NULL)
    {
        /* No address for import provided */
        return kStatus_Fail;
    }

    tmsg[0] = NVM_MASTER_IMPORT;          // NVM_MASTER_IMPORT Command Header
    tmsg[1] = nvmStorageID;               // NVM storage ID handle ID
    tmsg[2] = ADD_OFFSET((uint32_t)addr); // Address of master chunk
    tmsg[3] = MASTER_CHUNK_SIZE;          // Master chunk size

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, NVM_MASTER_IMPORT_SIZE);
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
    if (rmsg[0] == NVM_MASTER_IMPORT_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Open ELE Sign Service
 *
 * This function opens Sign generation service for EdgeLock Enclave.
 *
 * param mu MU peripheral base address
 * param keystoreHandleID unique session ID obtained by calling ELE_OpenKeystore()
 * param signHandleID pointer where unique sign handle ID word will be stored
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_OpenSignService(S3MU_Type *mu, uint32_t keystoreHandleID, uint32_t *signHandleID)
{
    status_t status               = kStatus_Fail;
    uint32_t tmsg[SIGN_OPEN_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]  = {0u};

    tmsg[0] = SIGN_OPEN;        // SIGN_OPEN Command Header
    tmsg[1] = keystoreHandleID; // Key Store handle ID
    tmsg[2] = 0x00000000u;      // User Input address extension (UIA) - not used
    tmsg[3] = 0x00000000u;      // User Output address extension (UOA) - not used
    tmsg[4] = 0x00000000u;      // Flag (reserved)
    tmsg[5] = S3MU_ComputeMsgCrc(tmsg, SIGN_OPEN_SIZE - 1u);

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, SIGN_OPEN_SIZE);
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
    if (rmsg[0] == SIGN_OPEN_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        /* read Key pair ID data */
        *signHandleID = rmsg[2];
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Close ELE Sign Service
 *
 * This function closes the Sign generation service for EdgeLock Enclave.
 *
 * param mu MU peripheral base address
 * param signHandleID unique session ID obtained by calling ELE_OpenSignService()
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_CloseSignService(S3MU_Type *mu, uint32_t signHandleID)
{
    status_t status                = kStatus_Fail;
    uint32_t tmsg[SIGN_CLOSE_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]   = {0u};

    tmsg[0] = SIGN_CLOSE;   // SIGN_CLOSE Command Header
    tmsg[1] = signHandleID; // Sign handle ID

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, SIGN_CLOSE_SIZE);
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
    if (rmsg[0] == SIGN_CLOSE_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Open ELE Sign
 *
 * This function generates signiture based on provided data and keys using EdgeLock Enclave.
 *
 * param mu MU peripheral base address
 * param signHandleID unique session ID obtained by calling ELE_OpenSignService()
 * param conf pointer where sign generate configuration structure can be found
 * param signature_size pointer where to save the resulting signature size or the expected
 *        size of the signature buffer, if the buffer is found to be too small, in which case
 *        an error is also returned
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail,
 *        kStatus_InvalidArgument if invalid argument
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange,
 *                  kStatus_ELE_BufferTooSmall
 */
status_t ELE_Sign(S3MU_Type *mu, uint32_t signHandleID, ele_sign_t *conf, uint32_t *signature_size)
{
    status_t status              = kStatus_Fail;
    uint32_t tmsg[SIGN_SIZE]     = {0u};
    uint32_t rmsg[S3MU_RR_COUNT] = {0u};

    /* Check argument validity */
    if (mu == NULL || conf == NULL || signature_size == NULL)
    {
        return kStatus_InvalidArgument;
    }

    tmsg[0] = SIGN_CMD;                              // SIGN_CMD Command Header
    tmsg[1] = signHandleID;                          // Sign service handle ID
    tmsg[2] = conf->key_id;                          // Key ID to be used for signing
    tmsg[3] = ADD_OFFSET((uint32_t)conf->msg);       // Address where the message digest to be signed can be found.
    tmsg[4] = ADD_OFFSET((uint32_t)conf->signature); // Address where the signature will be written
    tmsg[5] = conf->msg_size;                        // Size of message
    tmsg[6] = (uint32_t)conf->input_flag << SHIFT_16 | conf->sig_size; // Flag | size of signature + 8 bit for Ry
    tmsg[7] = (uint32_t)conf->scheme;
    tmsg[8] = (uint32_t)conf->salt_size;
    tmsg[9] = S3MU_ComputeMsgCrc(tmsg, SIGN_SIZE - 1u);

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, SIGN_SIZE);
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
    if (rmsg[0] != SIGN_RESPONSE_HDR)
    {
        return kStatus_Fail;
    }

    /* Correct header, check for success, assign signature size where needed */
    if (rmsg[1] == RESPONSE_SUCCESS)
    {
        *signature_size = rmsg[2] & SIGN_SIGNATURE_SIZE_MASK;

#if defined(ELE_CACHE_HANDLING) && (ELE_CACHE_HANDLING > 0u)
        DCACHE_InvalidateByRange((uint32_t)conf->signature, *signature_size);
#endif /* defined(ELE_CACHE_HANDLING) */

        return kStatus_Success;
    }
    else if (rmsg[1] == RESPONSE_ERROR_SIZE)
    {
        *signature_size = rmsg[2] & SIGN_SIGNATURE_SIZE_MASK;
        return kStatus_ELE_BufferTooSmall;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Open ELE Verify Service
 *
 * This function opens Verify service for EdgeLock Enclave.
 *
 * param mu MU peripheral base address
 * param sessionID unique session ID obtained by calling ELE_OpenSession()
 * param verifyHandleID pointer where unique verify handle ID word will be stored
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_OpenVerifyService(S3MU_Type *mu, uint32_t sessionID, uint32_t *verifyHandleID)
{
    status_t status                 = kStatus_Fail;
    uint32_t tmsg[VERIFY_OPEN_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]    = {0u};

    tmsg[0] = VERIFY_OPEN; // VERIFY_OPEN Command Header
    tmsg[1] = sessionID;   // Key Store handle ID
    tmsg[2] = 0x00000000u; // User Input address extension (UIA) - not used
    tmsg[3] = 0x00000000u; // User Output address extension (UOA) - not used
    tmsg[4] = 0x00000000u; // Flag (reserved)
    tmsg[5] = S3MU_ComputeMsgCrc(tmsg, VERIFY_OPEN_SIZE - 1u);

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, VERIFY_OPEN_SIZE);
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
    if (rmsg[0] == VERIFY_OPEN_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        /* read Key pair ID data */
        *verifyHandleID = rmsg[2];
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Close ELE Verify Service
 *
 * This function closes Verify service for EdgeLock Enclave.
 *
 * param mu MU peripheral base address
 * param verifyHandleID unique session ID obtained by calling ELE_OpenVerifyService()
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_CloseVerifyService(S3MU_Type *mu, uint32_t verifyHandleID)
{
    status_t status                  = kStatus_Fail;
    uint32_t tmsg[VERIFY_CLOSE_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]     = {0u};

    tmsg[0] = VERIFY_CLOSE;   // VERIFY_OPEN Command Header
    tmsg[1] = verifyHandleID; // Verify handle ID

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, VERIFY_CLOSE_SIZE);
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
    if (rmsg[0] == VERIFY_CLOSE_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Open ELE Verify
 *
 * This function is used to proceed with a signature verification operation using EdgeLock Enclave.
 *
 * param mu MU peripheral base address
 * param verifyHandleID unique session ID obtained by calling ELE_OpenVerifyService()
 * param conf pointer where verification configuration structure can be found
 * param result true if verification success, false otherwise
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_Verify(S3MU_Type *mu, uint32_t verifyHandleID, ele_verify_t *conf, bool *result)
{
    status_t status              = kStatus_Fail;
    uint32_t tmsg[VERIFY_SIZE]   = {0u};
    uint32_t rmsg[S3MU_RR_COUNT] = {0u};

    tmsg[0]  = VERIFY_CMD;                            // VERIFY_CMD Command Header
    tmsg[1]  = verifyHandleID;                        // Verify service handle ID
    tmsg[2]  = ADD_OFFSET((uint32_t)conf->pub_key);   // Public Key address to be used
    tmsg[3]  = ADD_OFFSET((uint32_t)conf->msg);       // Address where the message to be verified can be found
    tmsg[4]  = ADD_OFFSET((uint32_t)conf->signature); // Address where the signature can be found
    tmsg[5]  = conf->msg_size;                        // Size of message
    tmsg[6]  = (uint32_t)conf->key_size << SHIFT_16 | conf->sig_size; // Public key size | Signature size
    tmsg[7]  = (uint32_t)conf->keypair_type << SHIFT_16 | conf->key_security_size;
    tmsg[8]  = (uint32_t)conf->internal << VERIFY_FLAG_INTERNAL_SHIFT | (uint32_t)conf->input_flag; // Flags
    tmsg[9]  = (uint32_t)conf->scheme;                                                              // Signatrure Scheme
    tmsg[10] = (uint32_t)conf->salt_size;
    tmsg[11] = S3MU_ComputeMsgCrc(tmsg, VERIFY_SIZE - 1u);

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, VERIFY_SIZE);
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
    if (rmsg[0] == VERIFY_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        /* If success, test result */
        if (rmsg[2] == VERIFY_RESPONSE_SUCCESS)
        {
            *result = true;
        }
        else
        {
            *result = false;
        }
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Open NVM Storage Service
 *
 * This function opens non-volatile storage services for EdgeLock Enclave.
 * Service is used for importing and exporting data to/from ELE.
 *
 * param mu MU peripheral base address
 * param sessionID unique session ID obtained by calling ELE_OpenSession()
 * param nvmStorageID pointer where unique NVM storage handle ID word will be stored
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_OpenNvmStorageService(S3MU_Type *mu, uint32_t sessionID, uint32_t *nvmStorageID)
{
    status_t status                      = kStatus_Fail;
    uint32_t tmsg[NVM_STORAGE_OPEN_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]         = {0u};

    tmsg[0] = NVM_STORAGE_OPEN; // NVM_STORAGE_OPEN Command Header
    tmsg[1] = sessionID;        // Session handle ID
    tmsg[2] = 0x00000000u;      // User Input address extension (UIA) - not used
    tmsg[3] = 0x00000000u;      // User Output address extension (UOA) - not used
    tmsg[4] = 0x00000000u;      // Flag (reserved)
    tmsg[5] = S3MU_ComputeMsgCrc(tmsg, NVM_STORAGE_OPEN_SIZE - 1u);

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, NVM_STORAGE_OPEN_SIZE);
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
    if (rmsg[0] == NVM_STORAGE_OPEN_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        /* read storage ID data */
        *nvmStorageID = rmsg[2];
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Close ELE NVM Storage Service
 *
 * This function closes Non-volatile memory storage service for EdgeLock Enclave.
 * Service is used for importing and exporting data to/from ELE.
 *
 * param mu MU peripheral base address
 * param nvmStorageID unique session ID obtained by calling ELE_OpenNvmStorageService()
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_CloseNvmStorageService(S3MU_Type *mu, uint32_t nvmStorageID)
{
    status_t status                       = kStatus_Fail;
    uint32_t tmsg[NVM_STORAGE_CLOSE_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]          = {0u};

    tmsg[0] = NVM_STORAGE_CLOSE; // NVM_STORAGE_CLOSE Command Header
    tmsg[1] = nvmStorageID;      // NVM storage handle ID

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, NVM_STORAGE_CLOSE_SIZE);
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
    if (rmsg[0] == NVM_STORAGE_CLOSE_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Open Storage Service
 *
 * This function opens data storage service for EdgeLock Enclave.
 *
 * param mu MU peripheral base address
 * param keystoreHandleID Unique session ID obtained by calling ELE_OpenKeystore()
 * param dataStorageID Pointer where unique storage handle ID word will be stored
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_OpenDataStorage(S3MU_Type *mu, uint32_t keystoreHandleID, uint32_t *dataStorageID)
{
    status_t status                       = kStatus_Fail;
    uint32_t tmsg[DATA_STORAGE_OPEN_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]          = {0u};

    tmsg[0] = DATA_STORAGE_OPEN; // DATA_STORAGE_OPEN Command Header
    tmsg[1] = keystoreHandleID;  // Key Store handle ID
    tmsg[2] = 0x00000000u;       // User Input address extension (UIA) - not used
    tmsg[3] = 0x00000000u;       // User Output address extension (UOA) - not used
    tmsg[4] = 0x00000000u;       // Flag (reserved)
    tmsg[5] = S3MU_ComputeMsgCrc(tmsg, DATA_STORAGE_OPEN_SIZE - 1u);

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, DATA_STORAGE_OPEN_SIZE);
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
    if (rmsg[0] == DATA_STORAGE_OPEN_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        /* read storage ID data */
        *dataStorageID = rmsg[2];
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Close ELE Data Storage Service
 *
 * This function closes data storage service for EdgeLock Enclave.
 *
 * param mu MU peripheral base address
 * param dataStorageID unique session ID obtained by calling ELE_OpenDataStorage()
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_CloseDataStorage(S3MU_Type *mu, uint32_t dataStorageID)
{
    status_t status                        = kStatus_Fail;
    uint32_t tmsg[DATA_STORAGE_CLOSE_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]           = {0u};

    tmsg[0] = DATA_STORAGE_CLOSE; // DATA_STORAGE_CLOSE Command Header
    tmsg[1] = dataStorageID;      // Data storage handle ID

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, DATA_STORAGE_CLOSE_SIZE);
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
    if (rmsg[0] == DATA_STORAGE_CLOSE_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/* If addr is NULL, allocate on heap, eitherway return a given addr */
void *malloc_if_not_null(void *addr, size_t size)
{
    /* If out address is null, use HEAP */
    if (addr == NULL && size > 0u)
    {
        return addr = malloc(size);
    }
    else
    {
        return addr;
    }
}

/* Static function to handle export chunk request from ELE      */
/* If success, return address and size of encrypted chunk, NULL otherwise */
static uint32_t *nvm_storage_export_req(S3MU_Type *mu, uint32_t *out, size_t *size)
{
    status_t status = kStatus_Fail;
    chunk_master_export_respond_t chunk_master_respond;
    chunk_export_respond_t chunk_response;
    chunk_export_req_t chunk_req;
    chunk_export_finish_t finish;
    uint32_t *chunk_address;

    /* ----- Step 1) Get request and check */
    /* Obtain chunk export request from Security Sub-System */
    status = S3MU_GetResponse(mu, (void *)&chunk_req);
    if (status != kStatus_Success)
    {
        return NULL;
    }

    /* ----- Step 2) Send response to ELE with address where to store the chunk */
    /* Check command request header from Secure Sub-System */
    switch (chunk_req.header.value)
    {
        case STORAGE_EXPORT_RESPONSE_REQ_HDR:
            /* Regular (data storage, key group or keystore) chunk export. */
            chunk_response.header.value  = EXPORT_CHUNK_RESPONSE_HDR;
            chunk_response.response_code = RESPONSE_SUCCESS;
            *size                        = chunk_req.chunk_size;

            /* If out address is null, use HEAP */
            chunk_address             = (uint32_t *)malloc_if_not_null(out, *size);
            chunk_response.chunk_addr = ADD_OFFSET((uint32_t)chunk_address);

            /* Send export chunk address message to Security Sub-System */
            status = S3MU_SendMessage(mu, (void *)&chunk_response, STORAGE_EXPORT_CHUNK_SIZE);
            if (status != kStatus_Success)
            {
                return NULL;
            }

            break;

        case STORAGE_EXPORT_MASTER_RESPONSE_REQ_HDR:
            /* Master storage export request */
            chunk_master_respond.header.value   = EXPORT_MASTER_CHUNK_RESPONSE_HDR;
            chunk_master_respond.storage_handle = chunk_req.storage_handle;
            chunk_master_respond.response_code  = RESPONSE_SUCCESS;
            *size                               = chunk_req.chunk_size;

            /* If out address is null, use HEAP */
            chunk_address                   = (uint32_t *)malloc_if_not_null(out, *size);
            chunk_master_respond.chunk_addr = ADD_OFFSET((uint32_t)chunk_address);

            /* Send export chunk address message to Security Sub-System */
            status = S3MU_SendMessage(mu, (void *)&chunk_master_respond, STORAGE_MASTER_EXPORT_CHUNK_SIZE);
            if (status != kStatus_Success)
            {
                return NULL;
            }

            break;

        default:
            chunk_address = NULL;
            break;
    }

    if (chunk_address == NULL)
    {
        return NULL;
    }

    /* ----- Step 3) Get export finish request from ELE */
    /* Get Storage export finish command from Security Sub-System */
    status = S3MU_GetResponse(mu, (void *)&finish);
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

/*!
 * brief Store Data Storage
 *
 * This function stores data using EdgeLock Enclave data storage services and
 * places the data at the address specified by conf.chunk_addr. If this address
 * is set to NULL, heap is allocated, the data is placed there, and the allocated heap
 * address is returned in the same variable.
 *
 * param mu MU peripheral base address
 * param storageHandleID Unique session ID obtained by calling ELE_OpenStorageService()
 * param conf Pointer where data storage configuration structure can be found
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_StoreDataStorage(S3MU_Type *mu, uint32_t storageHandleID, ele_data_storage_t *conf)
{
    status_t status                  = kStatus_Fail;
    uint32_t tmsg[STORAGE_DATA_SIZE] = {0u};
    uint32_t rmsg[STORAGE_DATA_SIZE] = {0u};
    uint32_t flags                   = 0u;
    size_t chunk_size                = 0u;

    if (conf->data == NULL || conf == NULL || mu == NULL)
    {
        return kStatus_InvalidArgument;
    }

    flags = (uint32_t)(((uint32_t)kDataStore << STORAGE_DATA_OPERATION_SHIFT) |
                       ((uint32_t)conf->option << STORAGE_DATA_OPTION_SHIFT));

    tmsg[0] = STORAGE_DATA;                                     // STORAGE_DATA Command Header
    tmsg[1] = storageHandleID;                                  // Storage handle ID
    tmsg[2] = flags;                                            // Flags
    tmsg[3] = (uint32_t)conf->dataID;                           // Data ID
    tmsg[4] = ADD_OFFSET((uint32_t)conf->data);                 // Address of data to be stored
    tmsg[5] = (uint32_t)conf->data_size;                        // Size of data in bytes
    tmsg[6] = 0u;                                               // Reserved
    tmsg[7] = S3MU_ComputeMsgCrc(tmsg, STORAGE_DATA_SIZE - 1u); // CRC

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, STORAGE_DATA_SIZE);
    if (status != kStatus_Success)
    {
        return status;
    }

    /* Handle Storage chunk export request from Security Sub-System */
    /* If chunk_addr is NULL, output data are dynamically allocated */
    conf->chunk_addr = nvm_storage_export_req(mu, conf->chunk_addr, &chunk_size);
    conf->chunk_size = chunk_size; /* Always add metadata (36B) on top of encrypted data */

    /* Get Storage data response from Security Sub-System */
    status = ele_mu_get_response(mu, rmsg);
    if (status != kStatus_Success)
    {
        return status;
    }

    if (rmsg[0] != STORAGE_DATA_RESPONSE_HDR && rmsg[1] != RESPONSE_SUCCESS)
    {
        return kStatus_Fail;
    }

#if defined(ELE_CACHE_HANDLING) && (ELE_CACHE_HANDLING > 0u)
    DCACHE_InvalidateByRange((uint32_t)conf->chunk_addr, conf->chunk_size);
#endif /* defined(ELE_CACHE_HANDLING) */

    return status;
}

/* Static function to handle get chunk request from ELE */
/* If success return address of decrypted data, NULL otherwise */
static status_t nvm_storage_get_req(S3MU_Type *mu, ele_data_storage_t *conf)
{
    status_t status = kStatus_Fail;
    chunk_get_req_t chunk_req;
    chunk_get_respond_t get_response;
    chunk_get_done_t get_done;
    chunk_get_done_resp_t get_done_resp;

    /* Obtain chunk get request from Security Sub-System */
    status = S3MU_GetResponse(mu, (void *)&chunk_req);
    if (status != kStatus_Success)
    {
        return status;
    }

    /* Check request comman header from Secure Sub-System */
    if (chunk_req.header.value != STORAGE_GET_RESPONSE_REQ_HDR)
    {
        return kStatus_Fail;
    }

    get_response.header.value  = GET_CHUNK_RESPONSE_HDR;
    get_response.chunk_size    = conf->chunk_size;
    get_response.chunk_addr    = ADD_OFFSET((uint32_t)conf->chunk_addr);
    get_response.response_code = RESPONSE_SUCCESS;

    /* Send export chunk address message to Security Sub-System */
    status = S3MU_SendMessage(mu, (void *)&get_response, STORAGE_GET_CHUNK_SIZE);
    if (status != kStatus_Success)
    {
        return kStatus_Fail;
    }

    /* Obtain Storage get chunk done command from Security Sub-System */
    status = S3MU_GetResponse(mu, (void *)&get_done);
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
    status = S3MU_SendMessage(mu, (void *)&get_done_resp, GET_DONE_RESPONSE_SIZE);

    return status;
}

/*!
 * brief Retrieve Data Storage
 *
 * This function retrieves data using EdgeLock Enclave data storage services and
 * places the data at the address specified by conf.data. If this address is set
 * to NULL, heap is allocated, the data is placed there, and the allocated heap
 * address is returned in the same variable.
 *
 * param mu MU peripheral base address
 * param storageHandleID Unique session ID obtained by calling ELE_OpenStorageService()
 * param conf Pointer where data storage configuration structure can be found
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_RetrieveDataStorage(S3MU_Type *mu, uint32_t storageHandleID, ele_data_storage_t *conf)
{
    status_t status                  = kStatus_Fail;
    uint32_t tmsg[STORAGE_DATA_SIZE] = {0u};
    uint32_t rmsg[STORAGE_DATA_SIZE] = {0u};
    uint32_t flags                   = 0u;

    if (mu == NULL || conf->chunk_addr == NULL || conf == NULL)
    {
        return kStatus_InvalidArgument;
    }

    /* Check that provided local buffer size is enough */
    if (conf->data != NULL && (conf->data_size < (conf->chunk_size - CHUNK_META_SIZE)))
    {
        return kStatus_InvalidArgument;
    }

    /* If Output data buffer not set allocate HEAP for output data */
    if (conf->data == NULL)
    {
        conf->data      = (uint32_t *)malloc(conf->chunk_size - CHUNK_META_SIZE);
        conf->data_size = conf->chunk_size - CHUNK_META_SIZE;
    }

    if (conf->data == NULL)
    {
        return kStatus_Fail;
    }

    /* Set up the flags (Option flag is only needed when doing data store) */
    flags = (uint32_t)((uint32_t)kDataRetrieve << STORAGE_DATA_OPERATION_SHIFT);

    tmsg[0] = STORAGE_DATA;                                     // STORAGE_DATA Command Header
    tmsg[1] = storageHandleID;                                  // Storage handle ID
    tmsg[2] = flags;                                            // Flags
    tmsg[3] = (uint32_t)conf->dataID;                           // Data ID
    tmsg[4] = ADD_OFFSET((uint32_t)conf->data);                 // Address of data to be retrieved
    tmsg[5] = (uint32_t)conf->data_size;                        // Size of data in bytes
    tmsg[6] = 0u;                                               // Reserved
    tmsg[7] = S3MU_ComputeMsgCrc(tmsg, STORAGE_DATA_SIZE - 1u); // CRC

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, STORAGE_DATA_SIZE);
    if (status != kStatus_Success)
    {
        return status;
    }

    /* Handle Storage chunk get request from Security Sub-System */
    status = nvm_storage_get_req(mu, conf);
    if (status != kStatus_Success)
    {
        return status;
    }

    /* Get Storage data response from Security Sub-System */
    status = ele_mu_get_response(mu, rmsg);
    if (status != kStatus_Success)
    {
        return status;
    }

    /* Check results */
    if (rmsg[0] != STORAGE_DATA_RESPONSE_HDR && rmsg[1] != RESPONSE_SUCCESS)
    {
        return kStatus_Fail;
    }

#if defined(ELE_CACHE_HANDLING) && (ELE_CACHE_HANDLING > 0u)
    DCACHE_InvalidateByRange((uint32_t)conf->data, conf->data_size);
#endif /* defined(ELE_CACHE_HANDLING) */

    return status;
}

/*!
 * brief Open ELE Generic Cipher
 *
 * This function encrypt or decrypt data using generic crypto cipher EdgeLock Enclave service.
 *
 * param mu MU peripheral base address
 * param conf Pointer where generic cipher configuration structure can be found
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_GenericCipher(S3MU_Type *mu, ele_generic_cipher_t *conf)
{
    status_t status                    = kStatus_Fail;
    uint32_t tmsg[GENERIC_CIPHER_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]       = {0u};

    tmsg[0] = GENERIC_CIPHER;                                         // GENERIC_CIPHER Command Header
    tmsg[1] = ADD_OFFSET(conf->data);                                 // Source data address
    tmsg[2] = ADD_OFFSET(conf->output);                               // Destination data address
    tmsg[3] = conf->size;                                             // Data byte length
    tmsg[4] = ADD_OFFSET(conf->key);                                  // Cipher key address
    tmsg[5] = conf->key_size;                                         // Cipher key byte length
    tmsg[6] = ADD_OFFSET(conf->iv);                                   // Initialization vector address
    tmsg[7] = conf->iv_size;                                          // Initialization vector size
    tmsg[8] = (uint32_t)conf->mode << SHIFT_8 | (uint32_t)conf->algo; // Algorithm | Mode
    tmsg[9] = S3MU_ComputeMsgCrc(tmsg, GENERIC_CIPHER_SIZE - 1u);
    // CRC sum of all the words of the message (excluding the CRC itself)

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, GENERIC_CIPHER_SIZE);
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

#if defined(ELE_CACHE_HANDLING) && (ELE_CACHE_HANDLING > 0u)
    DCACHE_InvalidateByRange((uint32_t)conf->output, conf->size);
#endif /* defined(ELE_CACHE_HANDLING) */

    /* Check that response corresponds to the sent command */
    if (rmsg[0] == GENERIC_CIPHER_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Open ELE Generic Cipher
 *
 * This function encrypt or decrypt data using generic crypto AES AEAD EdgeLock Enclave service.
 *
 * param mu MU peripheral base address
 * param conf Pointer where generic AEAD configuration structure can be found
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_GenericAead(S3MU_Type *mu, ele_generic_aead_t *conf)
{
    status_t status                  = kStatus_Fail;
    uint32_t tmsg[GENERIC_AEAD_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]     = {0u};

    tmsg[0]  = GENERIC_AEAD;                                           // GENERIC_AEAD Command Header
    tmsg[1]  = ADD_OFFSET(conf->data);                                 // Source data address
    tmsg[2]  = ADD_OFFSET(conf->output);                               // Destination data address
    tmsg[3]  = conf->size;                                             // Data byte length
    tmsg[4]  = ADD_OFFSET(conf->key);                                  // Cipher key address
    tmsg[5]  = conf->key_size;                                         // Cipher key byte length
    tmsg[6]  = ADD_OFFSET(conf->iv);                                   // Initialization vector address
    tmsg[7]  = conf->iv_size;                                          // Initialization vector size
    tmsg[8]  = ADD_OFFSET(conf->aad);                                  // Additional authentication data address
    tmsg[9]  = conf->aad_size;                                         // Additional authentication data size
    tmsg[10] = ADD_OFFSET(conf->tag);                                  // Tag data address
    tmsg[11] = conf->tag_size;                                         // Tag data size
    tmsg[12] = (uint32_t)conf->mode << SHIFT_8 | (uint32_t)conf->algo; // Algorithm | Mode
    tmsg[13] = S3MU_ComputeMsgCrc(tmsg, GENERIC_AEAD_SIZE - 1u);
    // CRC sum of all the words of the message (excluding the CRC itself)

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, GENERIC_AEAD_SIZE);
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

#if defined(ELE_CACHE_HANDLING) && (ELE_CACHE_HANDLING > 0u)
    DCACHE_InvalidateByRange((uint32_t)conf->output, conf->size);
    DCACHE_InvalidateByRange((uint32_t)conf->tag, conf->tag_size);
#endif /* defined(ELE_CACHE_HANDLING) */

    /* Check that response corresponds to the sent command */
    if (rmsg[0] == GENERIC_AEAD_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

#define ECDSA_GENERIC_NOT_SUPPORTED (1u)
#if !ECDSA_GENERIC_NOT_SUPPORTED
/*!
 * brief ELE Generic ECDSA
 *
 * This function sign or verify data using generic ECDSA EdgeLock Enclave service.
 *
 * param mu MU peripheral base address
 * param conf Pointer where generic ECDSA configuration structure can be found
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_GenericEcdsa(S3MU_Type *mu, ele_generic_ecdsa_t *conf)
{
    status_t status                        = kStatus_Fail;
    uint32_t tmsg[GENERIC_ASYMMETRIC_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]           = {0u};

    tmsg[0]  = GENERIC_ASYMMETRIC;          // GENERIC_ASYMMETRIC Command Header
    tmsg[1]  = 0u;
    tmsg[2]  = conf->algo;                  // Algorithm
    tmsg[3]  = conf->key_size << SHIFT_16 | conf->mode;
    tmsg[4]  = ADD_OFFSET(conf->digest);    // Key byte length
    tmsg[5]  = ADD_OFFSET(conf->signature); // Signature address to verify/generate
    tmsg[6]  = conf->digest_size;
    tmsg[7]  = conf->signature_size;        // Signature byte length
    tmsg[8]  = ADD_OFFSET(conf->key);
    tmsg[9]  = 0u;
    tmsg[10] = conf->key_size;
    tmsg[11] = 0u;
    tmsg[12] = 0u;
    tmsg[13] = 0u;
    tmsg[14] = 0u;
    tmsg[15] = S3MU_ComputeMsgCrc(tmsg, GENERIC_ASYMMETRIC_SIZE - 1u);
    // CRC sum of all the words of the message (excluding the CRC itself)

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, GENERIC_ASYMMETRIC_SIZE);
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
    if (rmsg[0] == GENERIC_ASYMMETRIC_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        /* Get Verify status from ELE */
        conf->verify_status = (generic_verify_status_t)rmsg[2];
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}
#endif /* ECDSA_GENERIC_NOT_SUPPORTED */

/*!
 * brief ELE Generic RSA
 *
 * This function sign, verify, encrypt or decrypt data using generic RSA EdgeLock Enclave service.
 *
 * param mu MU peripheral base address
 * param conf Pointer where generic RSA configuration structure can be found
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail,
 *        kStatus_InvalidArgument if invalid argument
 */
status_t ELE_GenericRsa(S3MU_Type *mu, ele_generic_rsa_t *conf)
{
    status_t status                        = kStatus_Fail;
    uint32_t tmsg[GENERIC_ASYMMETRIC_SIZE] = {0u};
    uint32_t rmsg[6u]                      = {0u};

    uint32_t digestOrPlain, signatureOrCipher, pubOrPrivExp;
    uint16_t digestOrPlain_size, signatureOrCipher_size, pubOrPrivExp_size;

    /* Check argument validity */
    if (mu == NULL || conf == NULL)
    {
        return kStatus_InvalidArgument;
    }

    /* Check if salt length is valid */
    if (conf->salt_size < 0 && conf->salt_size != GENERIC_ASYMMETRIC_SALT_SIZE_EQ_HASH_SIZE)
    {
        return kStatus_InvalidArgument;
    }

    /* Set inputs accoring to requested operation */
    if (conf->mode == kEncryption || conf->mode == kDecryption)
    {
        /* Check flag validity; bit 0 cannot be set for this mode */
        if (((uint32_t)conf->flags & GENERIC_RSA_INPUT_TYPE_FLAG_MASK) == (uint32_t)kFlagActualMsg)
        {
            return kStatus_InvalidArgument;
        }

        digestOrPlain          = (uint32_t)conf->plaintext;
        signatureOrCipher      = (uint32_t)conf->ciphertext;
        digestOrPlain_size     = (uint16_t)conf->plaintext_size;
        signatureOrCipher_size = (uint16_t)conf->ciphertext_size;

        if (conf->mode == kEncryption)
        {
            pubOrPrivExp      = (uint32_t)conf->pub_exponent;
            pubOrPrivExp_size = (uint16_t)conf->pub_exponent_size;
        }
        else if (conf->mode == kDecryption)
        {
            pubOrPrivExp      = (uint32_t)conf->priv_exponent;
            pubOrPrivExp_size = (uint16_t)conf->priv_exponent_size;
        }
        else
        {
            return kStatus_InvalidArgument;
        }
    }
    else if (conf->mode == kSignGen || conf->mode == kVerification)
    {
        digestOrPlain          = (uint32_t)conf->digest;
        signatureOrCipher      = (uint32_t)conf->signature;
        digestOrPlain_size     = (uint16_t)conf->digest_size;
        signatureOrCipher_size = (uint16_t)conf->signature_size;

        if (conf->mode == kVerification)
        {
            pubOrPrivExp      = (uint32_t)conf->pub_exponent;
            pubOrPrivExp_size = (uint16_t)conf->pub_exponent_size;
        }
        else if (conf->mode == kSignGen)
        {
            pubOrPrivExp      = (uint32_t)conf->priv_exponent;
            pubOrPrivExp_size = (uint16_t)conf->priv_exponent_size;
        }
        else
        {
            return kStatus_InvalidArgument;
        }
    }
    else
    {
        return kStatus_InvalidArgument;
    }

    uint32_t saltSize;
    if (conf->salt_size == GENERIC_ASYMMETRIC_SALT_SIZE_EQ_HASH_SIZE)
    {
        /* The MU always expects -1 in two's complement */
        saltSize = NEGATIVE_ONE_TWOS_COMPLEMENT_16_BIT;
    }
    else
    {
        /* Positive numbers can be cast */
        saltSize = (uint32_t)conf->salt_size;
    }

    tmsg[0] = GENERIC_ASYMMETRIC;   // GENERIC_ASYMMETRIC Command Header
    tmsg[1] = 0u;                   // Reserved
    tmsg[2] = (uint32_t)conf->algo; // Algorithm
    tmsg[3] =
        conf->key_size << SHIFT_16 | (uint32_t)conf->flags << SHIFT_8 | (uint32_t)conf->mode; // Key size | Flags | Mode
    tmsg[4]  = ADD_OFFSET(digestOrPlain);                                                     // Digest or plaintext
    tmsg[5]  = ADD_OFFSET(signatureOrCipher); // Signature (sign/verif) or Cipher (enc/dec) address
    tmsg[6]  = digestOrPlain_size;            // Digest (sign/verif) or Plaintext (enc/dec) size
    tmsg[7]  = signatureOrCipher_size;        // Signature (sign/verif) or Cipher (enc/dec) size
    tmsg[8]  = ADD_OFFSET(conf->modulus);     // Modulus address
    tmsg[9]  = ADD_OFFSET(pubOrPrivExp);      // Public (enc) or Private (dec) exponent address
    tmsg[10] = (uint32_t)pubOrPrivExp_size << SHIFT_16 | conf->modulus_size; // Exponent and modulus size
    tmsg[11] = 0u;                                                           // Reserved
    tmsg[12] = 0u;                                                           // Reserved
    tmsg[13] = ADD_OFFSET(conf->label);                                      // Label address
    tmsg[14] = saltSize << SHIFT_16 | conf->label_size;                      // Salt and label size
    tmsg[15] = S3MU_ComputeMsgCrc(tmsg, GENERIC_ASYMMETRIC_SIZE - 1u);
    // CRC sum of all the words of the message (excluding the CRC itself)

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, GENERIC_ASYMMETRIC_SIZE);
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
    if (rmsg[0] == GENERIC_ASYMMETRIC_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        if (conf->mode == kVerification)
        {
            /* Get Verify status from ELE */
            conf->verify_status = (generic_verify_status_t)rmsg[3];
        }

        if (conf->mode == kSignGen)
        {
#if defined(ELE_CACHE_HANDLING) && (ELE_CACHE_HANDLING > 0u)
            DCACHE_InvalidateByRange((uint32_t)signatureOrCipher, signatureOrCipher_size);
#endif /* defined(ELE_CACHE_HANDLING) */
        }

        if (conf->mode == kDecryption)
        {
            /* Get Verify status from ELE */
            conf->out_plaintext_len = rmsg[2];
#if defined(ELE_CACHE_HANDLING) && (ELE_CACHE_HANDLING > 0u)
            DCACHE_InvalidateByRange((uint32_t)digestOrPlain, conf->out_plaintext_len);
#endif /* defined(ELE_CACHE_HANDLING) */
        }

        if (conf->mode == kEncryption)
        {
#if defined(ELE_CACHE_HANDLING) && (ELE_CACHE_HANDLING > 0u)
            DCACHE_InvalidateByRange((uint32_t)signatureOrCipher, signatureOrCipher_size);
#endif /* defined(ELE_CACHE_HANDLING) */
        }

        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief ELE Generic RSA key gen
 *
 * This function generates RSA key-pair using generic RSA EdgeLock Enclave service.
 *
 * param mu MU peripheral base address
 * param conf Pointer where generic RSA configuration structure can be found
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 */
status_t ELE_GenericRsaKeygen(S3MU_Type *mu, ele_generic_rsa_t *conf)
{
    status_t status                        = kStatus_Fail;
    uint32_t tmsg[GENERIC_RSA_KEYGEN_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]           = {0u};

    tmsg[0]  = GENERIC_RSA_KEYGEN;                                          // GENERIC_RSA_KEYGEN Command Header
    tmsg[1]  = 0u;                                                          // MSB Buffer address (not used)
    tmsg[2]  = ADD_OFFSET(conf->modulus);                                   // Modulus address
    tmsg[3]  = ADD_OFFSET(conf->priv_exponent);                             // Key adress
    tmsg[4]  = ADD_OFFSET(conf->pub_exponent);                              // Public exponent address
    tmsg[5]  = conf->priv_exponent_size << SHIFT_16 | conf->modulus_size;   // Exponent and modulus size
    tmsg[6]  = conf->pub_exponent_size;                                     // Signature address to verify/generate
    tmsg[7]  = conf->key_size << SHIFT_16 | (uint32_t)GENERIC_RSA_KEY_PAIR; // Key size | Key type (RSA)
    tmsg[8]  = 0u;                                                          // Reserved
    tmsg[9]  = 0u;                                                          // Reserved
    tmsg[10] = S3MU_ComputeMsgCrc(tmsg, GENERIC_RSA_KEYGEN_SIZE - 1u);
    // CRC sum of all the words of the message (excluding the CRC itself)

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, GENERIC_RSA_KEYGEN_SIZE);
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
    if (rmsg[0] == GENERIC_RSA_KEYGEN_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
#if defined(ELE_CACHE_HANDLING) && (ELE_CACHE_HANDLING > 0u)
        DCACHE_InvalidateByRange((uint32_t)conf->modulus, conf->modulus_size);
        DCACHE_InvalidateByRange((uint32_t)conf->priv_exponent, conf->priv_exponent_size);
        DCACHE_InvalidateByRange((uint32_t)conf->pub_exponent, conf->pub_exponent_size);
#endif /* defined(ELE_CACHE_HANDLING) */

        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Ping ELE
 *
 * This function Ping EdgeLock Enclave, can be sent at any time to verify ELE is alive.
 * Additionally, this command reloads the fuse shadow registers and kick the Sentinel active bit.
 * This active bit must be kicked at least once every day (24 hours).
 *
 * param mu MU peripheral base address
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_Ping(S3MU_Type *mu)
{
    status_t status              = kStatus_Fail;
    uint32_t tmsg[PING_SIZE]     = {0u};
    uint32_t rmsg[S3MU_RR_COUNT] = {0u};

    /****************** PING ELE message ***********************/
    tmsg[0] = PING; // PING Command Header
    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, PING_SIZE);
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
    if (rmsg[0] == PING_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Get ELE FW Version
 *
 * This function is used to retrieve the Sentinel FW version.
 *
 * param mu MU peripheral base address
 * param EleFwVersion Pointer where ElE firmware version will be stored
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_GetFwVersion(S3MU_Type *mu, uint32_t *EleFwVersion)
{
    status_t status                    = kStatus_Fail;
    uint32_t tmsg[GET_FW_VERSION_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]       = {0u};

    /****************** Get firmware version ELE message ***********************/
    tmsg[0] = GET_FW_VERSION; // Get firmware version Command Header
    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, GET_FW_VERSION_SIZE);
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
    if (rmsg[0] == GET_FW_VERSION_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        /* read FW version */
        *EleFwVersion = rmsg[2];
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Get ELE FW Status
 *
 * This function is used to retrieve the Sentinel FW status.
 * If value in EleFwStatus is 0 there is no loaded ELE FW, if 1 ELE FW is authenticated and operational.
 *
 * param mu MU peripheral base address
 * param EleFwStatus Pointer where ElE firmware status will be stored
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_GetFwStatus(S3MU_Type *mu, uint32_t *EleFwStatus)
{
    status_t status                   = kStatus_Fail;
    uint32_t tmsg[GET_FW_STATUS_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]      = {0u};

    /****************** Get firmware status ELE message ***********************/
    tmsg[0] = GET_FW_STATUS; // Get firmware status Command Header
    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, GET_FW_STATUS_SIZE);
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
    if (rmsg[0] == GET_FW_STATUS_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        /* read FW status */
        *EleFwStatus = rmsg[2];
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Enable APC (Application core)
 *
 * This function is used by RTC (real time core) to release APC (Application core) when needed.
 *
 * param mu MU peripheral base address
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_EnableAPC(S3MU_Type *mu)
{
    status_t status                = kStatus_Fail;
    uint32_t tmsg[ENABLE_APC_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]   = {0u};

    /****************** Enable APC ELE message ***********************/
    tmsg[0] = ENABLE_APC; // Enable APC Command Header
    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, ENABLE_APC_SIZE);
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
    if (rmsg[0] == ENABLE_APC_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Forward Lifecycle update
 *
 * This function is to change chip lifecycle
 *  0x01U for NXP provisoned
 *  0x02U for OEM Open
 *  0x08U for OEM Closed
 *  0x80U for OEM Locked
 *
 * param mu MU peripheral base address
 * param Lifecycle to switch
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_ForwardLifecycle(S3MU_Type *mu, uint32_t Lifecycle)
{
    status_t status                       = kStatus_Fail;
    uint32_t tmsg[FORWARD_LIFECYCLE_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]          = {0u};

    /****************** Forward lifecycle ELE message ***********************/
    tmsg[0] = FORWARD_LIFECYCLE; // Forward lifecycle Command Header
    tmsg[1] = Lifecycle;         // Lifecycle to switch to
    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, FORWARD_LIFECYCLE_SIZE);
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
    if (rmsg[0] == FORWARD_LIFECYCLE_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Read common fuse
 *
 * This function is used to read non-security fuses that are not available through the FSB module
 *
 * param mu MU peripheral base address
 * param FuseID ID of fuse to be read
 * param Fuses Pointer where the value of the read fuse is stored
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_ReadFuse(S3MU_Type *mu, uint32_t FuseID, uint32_t *Fuse)
{
    status_t status               = kStatus_Fail;
    uint32_t tmsg[READ_FUSE_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]  = {0u};

    /****************** Read fuse ELE message ***********************/
    tmsg[0] = READ_FUSE; // Read fuse Command Header
    tmsg[1] = FuseID;    // FuseID to be readed
    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, READ_FUSE_SIZE);
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
    if (rmsg[0] == READ_FUSE_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        /* read fuse */
        *Fuse = rmsg[2];
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Release RDC
 *
 * This function is used to release specifed RDC to the core identified in this function.
 * The RDC will be released only if the FW of the core to which is the RDC ownership is going to be
 * transferred has been properly authenticated and verified.
 *
 * param mu MU peripheral base address
 * param RdcID Resource Domain Control identifier
 * param CoreID Core identifier
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_ReleaseRDC(S3MU_Type *mu, uint32_t RdcID, uint32_t CoreID)
{
    status_t status                 = kStatus_Fail;
    uint32_t tmsg[RELEASE_RDC_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]    = {0u};

    /****************** Release RDC ELE message ***********************/
    tmsg[0] = RELEASE_RDC;               // Release RDC Command Header
    tmsg[1] = RdcID << SHIFT_8 | CoreID; // RDC_ID | CoreID
    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, RELEASE_RDC_SIZE);
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
    if (rmsg[0] == RELEASE_RDC_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Write fuse
 *
 * This function is used to write fuses.
 * Example bit granularity - write bit 5 and 7 of fuse word index 10. BitPosition = 10*32+5 = 0x145. BitLength = 3.
 * Payload is 0b101 = 0x5 . Example word granularity - write fuse word index 10. BitPosition = 10*32 = 0x140. BitLength
 * = 32 = 0x60. Payload 0xWord1.
 *
 * param mu MU peripheral base address
 * param BitPosition Fuse identifier expressed as its position in bit in the fuse map.
 * param BitLength Number of bits to be written
 * param Payload Data to be written in fuse
 * param lock Write lock requirement, when set to 1 fuse words are locked, when set to 0 no write lock done
 * param Processed_idx Pointer where the index of last proccesed fuse is stored. Value is valid if !=0xffff
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_WriteFuse(
    S3MU_Type *mu, uint32_t BitPosition, uint32_t BitLength, uint32_t Payload, bool lock, uint32_t *Processed_idx)
{
    status_t status                = kStatus_Fail;
    uint32_t tmsg[WRITE_FUSE_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]   = {0u};

    /* Create word specifing which fuse and how many bits will be written*/

    /*   +----------------------------------------------------+
     *   | Lock  |           |  Bit Length  |   Bit position  |
     *   +---------------------------+------------------------+
     *   | bit 31| Bit 30-29 |  Bit 29-16   |    Bit 15-0     |
     *   +----------------------------------------------------+
     */
    uint32_t FuseWord = (uint32_t)((uint32_t)lock << LOCK_SHIFT) | (BitLength << BIT_LENGTH_SHIFT) | (BitPosition);

    /****************** Write fuse ELE message ***********************/
    tmsg[0] = WRITE_FUSE; // Write fuse Command Header
    tmsg[1] = FuseWord;   // Specify fuse and how many bits will be written
    tmsg[2] = Payload;    // Payload
    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, WRITE_FUSE_SIZE);
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
    if (rmsg[0] == WRITE_FUSE_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        /* read last processed fuse index */
        /* Value is valid if ! 0xffff*/
        *Processed_idx = rmsg[2];

        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Send signed message
 *
 * This function sends Signed message. SignedMsg must be formatted according to specification
 *
 * param mu MU peripheral base address
 * param Type type of signed message
 * param SignedMsg pointer in system memory where Signed message block can be found
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_SendSignedMsg(S3MU_Type *mu, signed_msg_type_t Type, uint32_t *SignedMsg)
{
    status_t status                 = kStatus_Fail;
    uint32_t tmsg[SEND_SIGNED_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]    = {0u};

    /****************** Send signed message ***********************/
    tmsg[0] = (uint32_t)((uint32_t)Type << SHIFT_16) | SEND_SIGNED; // Send signed message Command Header
    tmsg[1] = 0x0u;                                                 // Reserved
    tmsg[2] = ADD_OFFSET((uint32_t)SignedMsg);                      // Address where signed command payload can be found
    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, SEND_SIGNED_SIZE);
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
    if ((rmsg[0] == ((uint32_t)((uint32_t)Type << SHIFT_16) | SEND_SIGNED_RESPONSE_HDR)) &&
        (rmsg[1] == RESPONSE_SUCCESS))
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Start the initialization of the RNG context.
 *
 * The RNG must be started before using some of the ELE services.
 *
 * param mu MU peripheral base address
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_StartRng(S3MU_Type *mu)
{
    status_t status               = kStatus_Fail;
    uint32_t tmsg[START_RNG_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]  = {0u};

    /****************** Start RNG ***********************/
    tmsg[0] = START_RNG; // Start RNG message Command Header

    /* Send message to Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, START_RNG_SIZE);
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
    if (rmsg[0] == START_RNG_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Get TRNG State
 *
 * This command is used to get TRNG state from ELE.
 *
 * param mu MU peripheral base address
 * param state output buffer where response data will be writen, user must ensure atleast 4 bytes
 * avaliable. Lower byte map to TRNG state, upper byte to CSAL (Cryptolib) context state.
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_GetTrngState(S3MU_Type *mu, uint32_t *state)
{
    status_t status                    = kStatus_Fail;
    uint32_t tmsg[GET_TRNG_STATE_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]       = {0u};

    /****************** Get info message ***********************/
    tmsg[0] = GET_TRNG_STATE; // Get trng state message Command Header
    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, GET_TRNG_STATE_SIZE);
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
    if (rmsg[0] == GET_TRNG_STATE_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        *state = rmsg[2];
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Get info
 *
 * This command is used to get various information from ELE.
 *
 * param mu MU peripheral base address
 * param ResponseData pointer to output buffer where response data will be writen, user must ensure atleast 160 bytes
 * avaliable
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_GetInfo(S3MU_Type *mu, uint8_t *ResponseData)
{
    status_t status              = kStatus_Fail;
    uint32_t tmsg[GET_INFO_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT] = {0u};

    /****************** Get info message ***********************/
    tmsg[0] = GET_INFO;                           // Get info message Command Header
    tmsg[1] = 0x0u;
    tmsg[2] = ADD_OFFSET((uint32_t)ResponseData); // Output buffer
    tmsg[3] = 160u;                               // Size of ResponseData length
    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, GET_INFO_SIZE);
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
    if (rmsg[0] == GET_INFO_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
#if defined(ELE_CACHE_HANDLING) && (ELE_CACHE_HANDLING > 0u)
        DCACHE_InvalidateByRange((uint32_t)ResponseData, 160u);
#endif /* defined(ELE_CACHE_HANDLING) */
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Enable an instance of OTFAD.
 *
 * param mu MU peripheral base address
 * param OtfadID ID of the OTFAD instance to enable - used only if there are
 * multiple instances on the SoC
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_EnableOtfad(S3MU_Type *mu, uint8_t OtfadID)
{
    status_t status                  = kStatus_Fail;
    uint32_t tmsg[ENABLE_OTFAD_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]     = {0u};

    /****************** Enable OTFAD message ***********************/
    tmsg[0] = ENABLE_OTFAD;      // Enable OTFAD message Command Header
#if defined(FSL_FEATURE_SOC_OTFAD_COUNT) && (FSL_FEATURE_SOC_OTFAD_COUNT > 1)
    tmsg[1] = (uint32_t)OtfadID; // ID of the OTFAD instance
#else
    (void)OtfadID; /* Prevent an unused variable warning */
#endif

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, ENABLE_OTFAD_SIZE);
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
    if (rmsg[0] == ENABLE_OTFAD_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Get device attestation
 *
 * This command is used to get signature-certified information from ELE.
 *
 * param mu MU peripheral base address
 * param Nonce is the input nonce for the attestation service - see baseline API documentation
 * if words 2-4 are reserved and should be set to 0 on specific devices
 * param ResponseData pointer to output buffer where response data will be writen, user must ensure atleast 272 bytes
 * avaliable
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_Attest(S3MU_Type *mu, attestation_nonce_t Nonce, uint8_t *ResponseData)
{
    status_t status              = kStatus_Fail;
    uint32_t tmsg[ATTEST_SIZE]   = {0u};
    uint32_t rmsg[S3MU_RR_COUNT] = {0u};

    /****************** Attestation message ***********************/
    tmsg[0] = ATTEST;                             // Get device attestation Command Header
    tmsg[1] = 0x0u;
    tmsg[2] = ADD_OFFSET((uint32_t)ResponseData); // Output buffer
    tmsg[3] = 272u;                               // Size of ResponseData length
    tmsg[4] = Nonce.nonce_word_1;                 // Nonce words
    tmsg[5] = Nonce.nonce_word_2;
    tmsg[6] = Nonce.nonce_word_3;
    tmsg[7] = Nonce.nonce_word_4;
    tmsg[8] = S3MU_ComputeMsgCrc(tmsg, ATTEST_SIZE - 1u); // CRC

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, ATTEST_SIZE);
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
    if (rmsg[0] == ATTEST_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
#if defined(ELE_CACHE_HANDLING) && (ELE_CACHE_HANDLING > 0u)
        DCACHE_InvalidateByRange((uint32_t)ResponseData, 272u);
#endif /* defined(ELE_CACHE_HANDLING) */
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Start the clock change process
 *
 * param mu MU peripheral base address
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_ClockChangeStart(S3MU_Type *mu)
{
    status_t status                        = kStatus_Fail;
    uint32_t tmsg[CLOCK_CHANGE_START_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]           = {0u};

    /****************** Clock change start message ***********************/
    tmsg[0] = CLOCK_CHANGE_START; // Clock Change Start Command Header

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, CLOCK_CHANGE_START_SIZE);
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
    if (rmsg[0] == CLOCK_CHANGE_START_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Change ELE and/or CM33 clock
 *
 * It is valid to pass both parameters at the same time if the SoC supports both.
 *
 * param mu MU peripheral base address
 * param NewClockRateELE the new clock rate for ELE
 * param NewClockRateCM33 the new clock rate for the CM33 core
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_ClockChangeFinish(S3MU_Type *mu, uint8_t NewClockRateELE, uint8_t NewClockRateCM33)
{
    status_t status                         = kStatus_Fail;
    uint32_t tmsg[CLOCK_CHANGE_FINISH_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]            = {0u};

    /****************** Clock change finish message ***********************/
    tmsg[0] = CLOCK_CHANGE_FINISH;                                                // Clock Change Finish Command Header
    tmsg[1] = (uint32_t)NewClockRateCM33 << SHIFT_16 | (uint32_t)NewClockRateELE; // New CM33 and ELE clock rates

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, CLOCK_CHANGE_FINISH_SIZE);
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
    if (rmsg[0] == CLOCK_CHANGE_FINISH_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Fast Mac Start
 *
 * This command is used to enter in "Fast MAC" operation mode. This is the first step of the fast MAC API.
 * During this step, ELE will copy key into internal memory in order to accelerate future usage of the key.
 * ELE will also enter in a special mode where only Fast MAC will be accepted. All other commands will be rejected.
 *
 * param base MU peripheral base address
 * param key  Pointer to key data buffer, which is expected to be 64 Bytes long consisting of two 256 bit keys.
 *            The key size is hardcoded to 256 bits and other key sizes are not supported.
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_FastMacStart(S3MU_Type *mu, const uint8_t *key)
{
    status_t status                    = kStatus_Fail;
    uint32_t tmsg[FAST_MAC_START_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]       = {0u};

    tmsg[0] = FAST_MAC_START;            // FAST_MAC_START Command Header
    tmsg[1] = ADD_OFFSET((uint32_t)key); // HMAC key address
    tmsg[2] = 0x0u;                      // Reserved
    tmsg[3] = 0x0u;                      // Reserved

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, FAST_MAC_START_SIZE);
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
    if (rmsg[0] == FAST_MAC_START_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Fast Mac Proceed
 *
 * This command is used to proceed with a Fast MAC generation. The user gives as input the message buffer and size,
 * and ELE output to the User's MAC buffer the computed MAC. ELE use the key given in Start API.
 *
 * param base MU peripheral base address.
 * param msg pointer where input message data can be found.
 * param mac pointer to a buffer where the MAC data are written by ELE.
 *           If doing a OneShot operation with internal verification enabled,
 *           this buffer must hold the expected MAC value.
 * param msgSize size of message in bytes. If doing a Preload operation with
 *               internal verification enabled, this must be the length of the
 *               input message + the length of the concatenated expected MAC.
 *               note: If oneshot, limit is UIN16_MAX, otherwise 512 Bytes.
 * param flags the flags specifying Fast MAC Proceed behavior.
 *             See the FAST_MAC_* macros in ele_crypto.h.
 * param verifStatus returns the verification status after MAC computation if
 *                   the internal verification flag was enabled. May be NULL.
 *                   See the FAST_MAC_CHECK_VERIFICATION_* macros for
 *                   checking the returned status.
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_FastMacProceed(
    S3MU_Type *mu, const uint8_t *msg, uint8_t *mac, uint16_t msgSize, uint16_t flags, uint32_t *verifStatus)
{
    status_t status                      = kStatus_Fail;
    uint32_t tmsg[FAST_MAC_PROCEED_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]         = {0u};

    tmsg[0] = FAST_MAC_PROCEED;          // FAST_MAC_PROCEED Command Header
    tmsg[1] = ADD_OFFSET((uint32_t)msg); // Message address
    tmsg[2] = ADD_OFFSET((uint32_t)mac); // output Mac buffer address
    tmsg[3] = ((uint32_t)flags << 16u) | (uint32_t)msgSize;

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, FAST_MAC_PROCEED_SIZE);
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

    if (NULL != verifStatus)
    {
        *verifStatus = rmsg[2];
    }

    /* Check that response corresponds to the sent command */
    if (rmsg[0] == FAST_MAC_PROCEED_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
#if defined(ELE_CACHE_HANDLING) && (ELE_CACHE_HANDLING > 0u)
        DCACHE_InvalidateByRange((uint32_t)mac, 32u);
#endif /* defined(ELE_CACHE_HANDLING) */
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Fast Mac End
 *
 * This command is used to exit from "Fast MAC" mode.
 *
 * param base MU peripheral base address
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_FastMacEnd(S3MU_Type *mu)
{
    status_t status                  = kStatus_Fail;
    uint32_t tmsg[FAST_MAC_END_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]     = {0u};

    tmsg[0] = FAST_MAC_END; // FAST_MAC_END Command Header
    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, FAST_MAC_END_SIZE);
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
    if (rmsg[0] == FAST_MAC_END_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

static status_t construct_dek_key_blob_input(generate_key_blob_input_t *conf, uint32_t *payload)
{
    /* For DEK, just copy the key to the payload */
    (void)memcpy((void *)payload, (void *)conf->key, (size_t)conf->size);

    return kStatus_Success;
}

static status_t construct_otfad_key_blob_input(generate_key_blob_input_t *conf, uint32_t *payload)
{
    if ((conf->otfad.start_addr > conf->otfad.end_addr) || (conf->key == NULL) || (conf->ctr == NULL))
    {
        return kStatus_InvalidArgument;
    }

    /* The OTFAD key and counter */
    (void)memcpy((void *)&payload[0], (void *)conf->key, 16u);
    (void)memcpy((void *)&payload[4], (void *)conf->ctr, 8u);

    /* Address range */
    payload[6] = (conf->otfad.start_addr & OTFAD_RGD_W0_SRTADDR_MASK);
    payload[7] = (conf->otfad.end_addr & OTFAD_RGD_W1_ENDADDR_MASK);

    /* Flags in lower part of end address word */
    payload[7] |= OTFAD_RGD_W1_RO(conf->otfad.read_only) | OTFAD_RGD_W1_ADE(conf->otfad.enable_decryption) |
                  OTFAD_RGD_W1_VLD(conf->otfad.valid);

    /* Reserved and CRC fields */
    payload[8] = 0x0u;
    payload[9] = 0x0u; // CRC disabled due to side-channel vulnerability

    return kStatus_Success;
}

static status_t construct_iee_key_blob_input(generate_key_blob_input_t *conf, uint32_t *payload)
{
    /* Set bypass, key size, mode, page offset */
    payload[0] =
        IEE_REGATTR_BYP(conf->iee.bypass) | IEE_REGATTR_MD(conf->iee.mode) | IEE_REGATTR_KS(conf->iee.key_size);
    payload[1] = IEE_REGPO_PGOFF(conf->iee.page_offset);

    /* Zero out the key buffers in case keys are shorter than 256-bit */
    (void)memset(&payload[2], 0, 32u);
    (void)memset(&payload[10], 0, 32u);

    /* Set the keys */
    if ((conf->iee.rand_keys == kBlob_IEE_UseInputKeys) && (conf->algorithm == kBlob_Algo_AES_CTR))
    {
        if ((conf->key == NULL) || (conf->ctr == NULL))
        {
            return kStatus_InvalidArgument;
        }

        /* contf->key is an AES key of size conf->size, conf->ctr is 128-bit counter*/
        (void)memcpy((void *)&payload[2], (void *)conf->key, (size_t)conf->size);
        (void)memcpy((void *)&payload[10], (void *)conf->ctr, 16u);
    }

    if ((conf->iee.rand_keys == kBlob_IEE_UseInputKeys) && (conf->algorithm == kBlob_Algo_AES_XTS))
    {
        if (conf->key == NULL)
        {
            return kStatus_InvalidArgument;
        }

        /* conf->key is either a 256-bit or 512-bit key */
        if (conf->size == kBlob_Size_256)
        {
            (void)memcpy((void *)&payload[2], (void *)conf->key, (size_t)conf->size);
        }
        else if (conf->size == kBlob_Size_512)
        {
            const size_t key_size_half = (size_t)conf->size / 2u;

            (void)memcpy((void *)&payload[2], (void *)conf->key, key_size_half);
            (void)memcpy((void *)&payload[10], (void *)(conf->key + key_size_half), key_size_half);
        }
        else
        {
            return kStatus_InvalidArgument;
        }
    }

    /* Region lock and region number */
    payload[18] = (((uint32_t)conf->iee.lock << SHIFT_8) & KEY_BLOB_PAYLOAD_IEE_LOCK_MASK) |
                  (((uint32_t)conf->iee.region_number) & KEY_BLOB_PAYLOAD_IEE_REGION_MASK);

    /* CRC */
    payload[19] = 0x0u; // CRC disabled due to side-channel vulnerability

    return kStatus_Success;
}

static const uint32_t key_blob_header_template[] = {
    0x81000000u, /* Tag, Length, Version */
    0x00000000u, /* Reserved, Algorithm, Size, Flags */
};

/*!
 * brief Generate a key blob
 *
 * Used to encapsulate sensitive keys in a specific structure called a blob,
 * which provides both confidentiality and integrity protection.
 *
 * param mu MU peripheral base address
 * param KeyID key ID or OTFAD settings, depends on blob type, see baseline API documentation
 * param Conf is a pointer to the key blob generation configuration struct
 * param OutputBuffer is a pointer to the output buffer, where the key blob is placed, must be 64-bit aligned
 * param OutputBufferSize is the size of the output buffer
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail,
 * kStatus_InvalidArgument if invalid argument
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_GenerateKeyBlob(
    S3MU_Type *mu, uint32_t KeyID, generate_key_blob_input_t *Conf, uint8_t *OutputBuffer, uint16_t OutputBufferSize)
{
    status_t status                               = kStatus_Fail;
    uint32_t tmsg[GENERATE_KEY_BLOB_SIZE]         = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]                  = {0u};
    SDK_ALIGN(uint32_t payload_internal[22u], 8u) = {0u};

    /* Copy the blob input header template */
    (void)memcpy(payload_internal, key_blob_header_template, sizeof(key_blob_header_template));

    /* Set payload length */
    const uint32_t payload_size =
        (Conf->blob_type == kBlob_Type_IEE) ? KEY_BLOB_IEE_PAYLOAD_LENGTH : (uint32_t)Conf->size;
    const uint32_t payload_length_with_hdr = KEY_BLOB_PAYLOAD_HDR_LENGTH + payload_size;

    payload_internal[0] |= ((uint32_t)payload_length_with_hdr << SHIFT_8) & KEY_BLOB_PAYLOAD_LENGTH_MASK;

    /* Set algorithm, size, blob type */
    payload_internal[1] |= ((uint32_t)Conf->algorithm << SHIFT_16) & KEY_BLOB_PAYLOAD_ALGORITHM_MASK;
    payload_internal[1] |= ((uint32_t)Conf->size << SHIFT_8) & KEY_BLOB_PAYLOAD_SIZE_MASK;
    payload_internal[1] |= ((uint32_t)Conf->blob_type) & KEY_BLOB_PAYLOAD_TYPE_MASK;

    /* Form the key blob input payload */
    switch (Conf->blob_type)
    {
        case kBlob_Type_DEK:
            status = construct_dek_key_blob_input(Conf, &payload_internal[2]);
            break;
        case kBlob_Type_OTFAD:
            status = construct_otfad_key_blob_input(Conf, &payload_internal[2]);
            break;
        case kBlob_Type_IEE:
            status = construct_iee_key_blob_input(Conf, &payload_internal[2]);
            break;
        default:
            status = kStatus_Fail;
            break;
    }
    if (status != kStatus_Success)
    {
        (void)memset(payload_internal, 0, sizeof(payload_internal));
        return status;
    }

    /****************** Generate key blob message ***********************/
    tmsg[0] = GENERATE_KEY_BLOB;                                     // Generate Key Blob Command Header
    tmsg[1] = KeyID;                                                 // Key ID or OTFAD settings
    tmsg[2] = 0u;                                                    // Input address extension - unused
    tmsg[3] = ADD_OFFSET((uint32_t)payload_internal);                // Input
    tmsg[4] = 0u;                                                    // Output address extension - unused
    tmsg[5] = ADD_OFFSET((uint32_t)OutputBuffer);                    // Output
    tmsg[6] = ((uint32_t)Conf->iee.rand_keys << SHIFT_8) |
              (uint32_t)OutputBufferSize;                            // Random keys flag | Output buffer size
    tmsg[7] = S3MU_ComputeMsgCrc(tmsg, GENERATE_KEY_BLOB_SIZE - 1u); // CRC

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, GENERATE_KEY_BLOB_SIZE);
    if (status != kStatus_Success)
    {
        (void)memset(payload_internal, 0, sizeof(payload_internal));
        return status;
    }

    /* Wait for response from Security Sub-System */
    status = ele_mu_get_response(mu, rmsg);

    /* Clear the payload to not leave key material in memory */
    (void)memset(payload_internal, 0, sizeof(payload_internal));

    if (status != kStatus_Success)
    {
        return status;
    }

    /* Check that response corresponds to the sent command */
    if (rmsg[0] == GENERATE_KEY_BLOB_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
#if defined(ELE_CACHE_HANDLING) && (ELE_CACHE_HANDLING > 0u)
        DCACHE_InvalidateByRange((uint32_t)OutputBuffer, OutputBufferSize);
#endif /* defined(ELE_CACHE_HANDLING) */
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Import keys from key blob to corresponding HW block - currently only IEE supported
 *
 * param mu MU peripheral base address
 * param KeyID identical to the one used for ELE_GenerateKeyBlob()
 * param BlobAddress pointer to the blob generated with ELE_GenerateKeyBlob()
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail,
 * kStatus_InvalidArgument if invalid argument
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_LoadKeyBlob(S3MU_Type *mu, uint32_t KeyID, uint8_t *BlobAddress)
{
    status_t status                   = kStatus_Fail;
    uint32_t tmsg[LOAD_KEY_BLOB_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]      = {0u};

    /****************** Load key blob message ***********************/
    tmsg[0] = LOAD_KEY_BLOB;                     // Load Key Blob Command Header
    tmsg[1] = KeyID;                             // Key ID
    tmsg[2] = 0u;                                // Address extension - unused
    tmsg[3] = ADD_OFFSET((uint32_t)BlobAddress); // Blob address

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, LOAD_KEY_BLOB_SIZE);
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
    if (rmsg[0] == LOAD_KEY_BLOB_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Import an EdgeLock2Go or ELE key.
 *
 * param mu MU peripheral base address
 * param keyHandleID identifier of a key management sevice opened with ELE_OpenKeyService()
 * param input pointer to the TLV blob containing the key to be imported
 * param inputSize the size of the input TLV blob in Bytes
 * param keyGroupAuto set to true to let ELE select the key group to import the key into
 * param keyGroupID identifier of the keygroup to import the key into if keyGroupAuto is false
 * param option specifies if the TLV blob is an EdgeLock2Go option or an ELE option
 * param monotonic if true, the monotonic counter flag is set
 * param sync if true, the SYNC flag is set
 * param keyID output parameter returning the ID of the imported key
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail,
 * kStatus_InvalidArgument if invalid argument
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_ImportKey(S3MU_Type *mu,
                       uint32_t keyHandleID,
                       uint8_t *input,
                       uint32_t inputSize,
                       bool keyGroupAuto,
                       uint16_t keyGroupID,
                       ele_import_key_option_t option,
                       bool sync,
                       bool monotonic,
                       uint32_t *keyID)
{
    status_t status                = kStatus_Fail;
    uint32_t tmsg[IMPORT_KEY_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]   = {0u};
    uint32_t flags                 = 0u;

    if (input == NULL || keyID == NULL)
    {
        return kStatus_InvalidArgument;
    }

    /* Set the option, sync, monotonic, and the automatic key group selection flags */
    flags = (uint32_t)option;

    if (monotonic == true)
    {
        flags |= (uint32_t)1u << IMPORT_KEY_MONOTONIC_FLAG_SHIFT;
    }

    if (sync == true)
    {
        flags |= (uint32_t)1u << IMPORT_KEY_SYNC_FLAG_SHIFT;
    }

    if (keyGroupAuto == false)
    {
        /* If the key group is not chosen automatically, set the flag */
        flags |= (uint32_t)1u << IMPORT_KEY_GROUP_AUTO_FLAG_SHIFT;
    }

    /****************** Load key blob message ***********************/
    tmsg[0] = IMPORT_KEY;                                                   // Import Key Command Header
    tmsg[1] = keyHandleID;                                                  // Key Management Handle ID
    tmsg[2] = flags;                                                        // Flags
    tmsg[3] = ADD_OFFSET((uint32_t)input);                                  // The input TLV payload
    tmsg[4] = inputSize;                                                    // Size of the input
    tmsg[5] = (uint32_t)(option == kImportKeyOption_ELE ? keyGroupID : 0u); // Key Group ID if ELE option is used
    tmsg[6] = S3MU_ComputeMsgCrc(tmsg, IMPORT_KEY_SIZE - 1u);               // CRC

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, IMPORT_KEY_SIZE);
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
    if (rmsg[0] == IMPORT_KEY_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        /* Save the returned key ID on success */
        *keyID = rmsg[2];

        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Write BBSM
 *
 * This function is used to program Battery-Backed Security Module registers inside ELE
 *
 * param mu MU peripheral base address
 * param offset Offset of the register to perform the operation
 * param value value to be written into BBSM register
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_WriteBbsm(S3MU_Type *mu, uint32_t offset, uint32_t value)
{
    status_t status                  = kStatus_Fail;
    uint32_t tmsg[PROGRAM_BBSM_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]     = {0u};

    /****************** BBSM program ELE message ***********************/
    tmsg[0] = PROGRAM_BBSM;          // Program BBSM Command Header
    tmsg[1] = PROGRAM_BBSM_WRITE_OP; // Write operation
    tmsg[2] = offset;                // Register offset
    tmsg[3] = value;                 // New register value to be written
    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, PROGRAM_BBSM_SIZE);
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
    if (rmsg[0] == PROGRAM_BBSM_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Read BBSM
 *
 * This function is used to read Battery-Backed Security Module registers inside ELE
 *
 * param mu MU peripheral base address
 * param offset Offset of the register to perform the operation
 * param value value read from BBSM register
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_ReadBbsm(S3MU_Type *mu, uint32_t offset, uint32_t *value)
{
    status_t status                  = kStatus_Fail;
    uint32_t tmsg[PROGRAM_BBSM_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]     = {0u};

    /****************** BBSM program ELE message ***********************/
    tmsg[0] = PROGRAM_BBSM;         // Program BBSM Command Header
    tmsg[1] = PROGRAM_BBSM_READ_OP; // Write operation
    tmsg[2] = offset;               // Register offset
    tmsg[3] = 0u;                   // Unused when read
    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, PROGRAM_BBSM_SIZE);
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
    if (rmsg[0] == PROGRAM_BBSM_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        *value = rmsg[2u];
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Set BBSM policy
 *
 * This function is used to set policy for Battery-Backed Security Module in case of events
 *
 * param mu MU peripheral base address
 * param policy_mask policy to be set (refer to ele_bbsm_policy_t)
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_SetPolicyBbsm(S3MU_Type *mu, uint32_t policy_mask)
{
    status_t status                  = kStatus_Fail;
    uint32_t tmsg[PROGRAM_BBSM_SIZE] = {0u};
    uint32_t rmsg[S3MU_RR_COUNT]     = {0u};

    /****************** BBSM program ELE message ***********************/
    tmsg[0] = PROGRAM_BBSM;                                      // Program BBSM Command Header
    tmsg[1] = policy_mask << SHIFT_16 | PROGRAM_BBSM_SET_POLICY; // Write operation
    tmsg[2] = 0u;                                                // Unused when setting policy
    tmsg[3] = 0u;                                                // Unused when setting policy
    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, PROGRAM_BBSM_SIZE);
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
    if (rmsg[0] == PROGRAM_BBSM_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * brief Set ELE Get Event
 *
 * This function is used to retrieve any singular event that has occurred since the FW has started.
 * A singular event occurs when the second word of a response to any request is different from ELE_SUCCESS.
 * That includes commands with failure response as well as commands with successful response containing an indication
 * (i.e. warning response).
 *
 * The events are stored by ELE in a fixed sized buffer. When the capacity of the buffer is exceeded, new occurring
 * events are lost.
 *
 * The event buffer is systematically returned in full to the requester independently of the actual numbers of events
 * stored
 *
 * param mu MU peripheral base address
 * param events Events buffer (refer to ele_events_t)
 *
 * return Status kStatus_Success if success, kStatus_Fail if fail
 * Possible errors: kStatus_S3MU_InvalidArgument, kStatus_S3MU_AgumentOutOfRange
 */
status_t ELE_GetEvent(S3MU_Type *mu, ele_events_t *events)
{
    status_t status                   = kStatus_Fail;
    uint32_t tmsg[GET_EVENT_SIZE]     = {0u};
    uint32_t rmsg[GET_EVENT_RSP_SIZE] = {0u};

    /****************** BBSM program ELE message ***********************/
    tmsg[0] = GET_EVENT; // Get Event Command Header

    /* Send message Security Sub-System */
    status = S3MU_SendMessage(mu, tmsg, GET_EVENT_SIZE);
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
    if (rmsg[0] == GET_EVENT_RESPONSE_HDR && rmsg[1] == RESPONSE_SUCCESS)
    {
        memcpy(events, &rmsg[3u], ELE_MAX_EVENTS);
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}
