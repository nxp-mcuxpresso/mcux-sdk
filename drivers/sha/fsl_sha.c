/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_sha.h"

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.sha"
#endif

/*!< SHA-1 and SHA-256 block size  */
#define SHA_BLOCK_SIZE 64U
#define MAX_HASH_CHUNK (SHA_MEMCTRL_COUNT_MASK >> 16)

/*!< Use standard C library memcpy  */
#define sha_memcpy memcpy

/*! Internal states of the HASH creation process */
typedef enum _sha_algo_state
{
    kSHA_HashInit = 1u, /*!< Init state, the NEW bit in SHA Control register has not been written yet. */
    kSHA_HashUpdate, /*!< Update state, DIGEST registers contain running hash, NEW bit in SHA control register has been
                         written. */
    kSHA_HashDone,   /*!< Done state, computing of hash has been completed */
    kSHA_HashError,  /*!< Error state*/
} sha_algo_state_t;

/*! 64-byte block represented as byte array of 16 32-bit words */
typedef union _sha_hash_block
{
    uint32_t w[SHA_BLOCK_SIZE / 4]; /*!< array of 32-bit words */
    uint8_t b[SHA_BLOCK_SIZE];      /*!< byte array */
} sha_block_t;

/*! internal sha context structure */
typedef struct _sha_ctx_internal
{
    sha_block_t blk;        /*!< memory buffer. only full 64-byte blocks are written to SHA during hash updates */
    size_t blksz;           /*!< number of valid bytes in memory buffer */
    sha_algo_t algo;        /*!< selected algorithm from the set of supported algorithms */
    sha_algo_state_t state; /*!< finite machine state of the hash software process */
    size_t fullMessageSize; /*!< track message size during SHA_Update(). The value is used for padding. */
    uint8_t *pMessage;      /*!< current message address */
    SHA_Type *base;         /*!< SHA base address */
} sha_ctx_internal_t;

/*!< SHA-1 and SHA-256 digest length in bytes  */
enum _sha_digest_len
{
    kSHA_OutLenSha1   = 20u,
    kSHA_OutLenSha256 = 32u,
};

/*! pointer to hash context structure used by isr */
static sha_ctx_internal_t *s_shaCtx = NULL;

/*!< macro for checking build time condition. It is used to assure the sha_ctx_internal_t can fit into sha_ctx_t */
#define BUILD_ASSERT(condition, msg) extern int msg[1 - 2 * (!(condition))] __attribute__((unused))

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief LDM to SHA engine INDATA and ALIAS registers.
 *
 * This function writes 16 words starting from the src address (must be word aligned)
 * to the dst address. Dst address does not increment (destination is peripheral module register INDATA).
 * Src address increments to load 16 consecutive words.
 *
 * @param dst peripheral register address (word aligned)
 * @param src address of the input 512-bit block (16 words) (word aligned)
 *
 */
#if defined(SHA_ALIAS_DATA_MASK)
__STATIC_INLINE void sha_ldm_stm_16_words(SHA_Type *base, const uint32_t *src)
{
    base->INDATA = src[0];
    for (int i = 0; i < 7; i++)
    {
        base->ALIAS[i] = src[i + 1];
    }
    src += 8u;
    base->INDATA = src[0];
    for (int i = 0; i < 7; i++)
    {
        base->ALIAS[i] = src[i + 1];
    }
}
#else
__STATIC_INLINE void sha_ldm_stm_16_words(volatile uint32_t *dst, const uint32_t *src)
{
    for (int i = 0; i < 8; i++)
    {
        dst[i] = src[i];
    }
    src += 8u;
    for (int i = 0; i < 8; i++)
    {
        dst[i] = src[i];
    }
}
#endif
/*!
 * @brief Swap bytes withing 32-bit word.
 *
 * This function changes endianess of a 32-bit word.
 *
 * @param in 32-bit unsigned integer
 * @return 32-bit unsigned integer with different endianess (big endian to little endian and vice versa).
 */
static uint32_t swap_bytes(uint32_t in)
{
    return (((in & 0x000000ffu) << 24) | ((in & 0x0000ff00u) << 8) | ((in & 0x00ff0000u) >> 8) |
            ((in & 0xff000000u) >> 24));
}

/*!
 * @brief Check validity of algoritm.
 *
 * This function checks the validity of input argument.
 *
 * @param algo Tested algorithm value.
 * @return kStatus_Success if valid, kStatus_InvalidArgument otherwise.
 */
static status_t sha_check_input_alg(sha_algo_t algo)
{
    if ((algo != kSHA_Sha1) && (algo != kSHA_Sha256))
    {
        return kStatus_InvalidArgument;
    }
    return kStatus_Success;
}

#if defined(FSL_FEATURE_SHA_HAS_MEMADDR_DMA) && (FSL_FEATURE_SHA_HAS_MEMADDR_DMA > 0)
/*!
 * @brief Check if input data are stored in SRAMX/0.
 *
 * This function checks if input data are stored in SRAMX or SRAM0.
 * The requirements for MEMADDR (pseudo DMA) are that the data are on a x4 boundary
 * and only SRAMX and SRAM0 addresses can be used. SRAM1-SRAM3 are illegal.
 *
 * @param message Pointer to input data
 * @param messageSize Message size in bytes
 * @return kStatus_Success if valid, kStatus_InvalidArgument otherwise.
 */
static status_t sha_check_memory_boundry(const uint8_t *message, size_t messageSize)
{
#if defined(SRAMX_BASE) && defined(SRAM0_BASE) && defined(SRAMX_SIZE) && defined(SRAM0_SIZE)
    /* Message is not in SRAMX and SRAM0*/
    if ((((uint32_t)message + messageSize) > (SRAMX_BASE + SRAMX_SIZE)) && ((uint32_t)message < SRAM0_BASE))
    {
        return kStatus_Fail;
    }
    /* Message is in SRAM1 or higher */
    else if (((uint32_t)message + messageSize) > (SRAM0_BASE + SRAM0_SIZE))
    {
        return kStatus_Fail;
    }
    /* Message is not 4-byte aligned */
    else if (((uint32_t)message & 0x3U) != 0U)
    {
        return kStatus_Fail;
    }
    else
    {
        return kStatus_Success;
    }
#else
    return kStatus_Fail;
#endif /* defined(SRAMX_BASE) && defined(SRAM0_BASE) && defined(SRAMX_SIZE) && defined(SRAM0_SIZE) */
}
#endif /* defined(FSL_FEATURE_SHA_HAS_MEMADDR_DMA) && (FSL_FEATURE_SHA_HAS_MEMADDR_DMA > 0) */

/*!
 * @brief Check validity of input arguments.
 *
 * This function checks the validity of input arguments.
 *
 * @param base SHA peripheral base address.
 * @param ctx Memory buffer given by user application where the SHA_Init/SHA_Update/SHA_Finish store context.
 * @param algo Tested algorithm value.
 * @return kStatus_Success if valid, kStatus_InvalidArgument otherwise.
 */
static status_t sha_check_input_args(SHA_Type *base, sha_ctx_t *ctx, sha_algo_t algo)
{
    /* Check validity of input algorithm */
    if (kStatus_Success != sha_check_input_alg(algo))
    {
        return kStatus_InvalidArgument;
    }

    if ((NULL == ctx) || (NULL == base))
    {
        return kStatus_InvalidArgument;
    }

    return kStatus_Success;
}

/*!
 * @brief Check validity of internal software context.
 *
 * This function checks if the internal context structure looks correct.
 *
 * @param ctxInternal Internal context.
 * @param message Input message address.
 * @return kStatus_Success if valid, kStatus_InvalidArgument otherwise.
 */
static status_t sha_check_context(sha_ctx_internal_t *ctxInternal, const uint8_t *message)
{
    if ((NULL == message) || (NULL == ctxInternal) || (kStatus_Success != sha_check_input_alg(ctxInternal->algo)))
    {
        return kStatus_InvalidArgument;
    }
    return kStatus_Success;
}

/*!
 * @brief Initialize the SHA engine for new hash.
 *
 * This function sets NEW and MODE fields in SHA Control register to start new hash.
 *
 * @param base SHA peripheral base address.
 * @param ctxInternal Internal context.
 */
static void sha_engine_init(SHA_Type *base, sha_ctx_internal_t *ctxInternal)
{
    uint32_t shaCtrl;

    if (kSHA_Sha1 == ctxInternal->algo)
    {
        shaCtrl = SHA_CTRL_MODE(1) | SHA_CTRL_NEW(1);
    }
    else
    {
        shaCtrl = SHA_CTRL_MODE(2) | SHA_CTRL_NEW(1);
    }
    base->CTRL = shaCtrl;
}

/*!
 * @brief Load 512-bit block (16 words) into SHA engine.
 *
 * This function aligns the input block and moves it into SHA engine INDATA.
 * CPU polls the WAITING bit and then moves data by using LDM and STM instructions.
 *
 * @param base SHA peripheral base address.
 * @param blk 512-bit block
 */
static void sha_one_block(SHA_Type *base, const uint8_t *blk)
{
    uint32_t temp[SHA_BLOCK_SIZE / sizeof(uint32_t)];
    const uint32_t *actBlk;

    /* make sure the 512-bit block is word aligned */
    if (((uintptr_t)blk & 0x3u) != 0U)
    {
        (void)sha_memcpy(temp, (const uint32_t *)(uintptr_t)blk, SHA_BLOCK_SIZE);
        actBlk = (const uint32_t *)(uintptr_t)temp;
    }
    else
    {
        actBlk = (const uint32_t *)(uintptr_t)blk;
    }

    /* poll waiting. */
    while (0U == (base->STATUS & SHA_STATUS_WAITING_MASK))
    {
    }
/* feed INDATA (and ALIASes). use STM instruction. */
#if defined(SHA_ALIAS_DATA_MASK)
    sha_ldm_stm_16_words(base, actBlk);
#else
    sha_ldm_stm_16_words(&base->INDATA[0], actBlk);
#endif
}

/*!
 * @brief Adds message to current hash.
 *
 * This function merges the message to fill the internal buffer, empties the internal buffer if
 * it becomes full, then process all remaining message data.
 *
 *
 * @param base SHA peripheral base address.
 * @param ctxInternal Internal context.
 * @param message Input message.
 * @param messageSize Size of input message in bytes.
 * @return kStatus_Success.
 */
static status_t sha_process_message_data(SHA_Type *base,
                                         sha_ctx_internal_t *ctxInternal,
                                         const uint8_t *message,
                                         size_t messageSize)
{
    /* first fill the internal buffer to full block */
    size_t toCopy = SHA_BLOCK_SIZE - ctxInternal->blksz;
    (void)sha_memcpy(&ctxInternal->blk.b[ctxInternal->blksz], message, toCopy);
    message += toCopy;
    messageSize -= toCopy;

    /* process full internal block */
    sha_one_block(base, &ctxInternal->blk.b[0]);

    /* process all full blocks in message[] */
    while (messageSize >= SHA_BLOCK_SIZE)
    {
        sha_one_block(base, message);
        message += SHA_BLOCK_SIZE;
        messageSize -= SHA_BLOCK_SIZE;
    }

    /* copy last incomplete message bytes into internal block */
    (void)sha_memcpy(&ctxInternal->blk.b[0], message, messageSize);
    ctxInternal->blksz = messageSize;
    ctxInternal->state = kSHA_HashDone;
    return kStatus_Success;
}

/*!
 * @brief Finalize the running hash to make digest.
 *
 * This function empties the internal buffer, adds padding bits, and generates final digest.
 *
 * @param base SHA peripheral base address.
 * @param ctxInternal Internal context.
 * @return kStatus_Success.
 */
static status_t sha_finalize(SHA_Type *base, sha_ctx_internal_t *ctxInternal)
{
    sha_block_t lastBlock;

    (void)memset(&lastBlock, 0, sizeof(sha_block_t));

    /* this is last call, so need to flush buffered message bytes along with padding */
    if (ctxInternal->blksz <= 55u)
    {
        /* last data is 440 bits or less. */
        (void)sha_memcpy(&lastBlock.b[0], &ctxInternal->blk.b[0], ctxInternal->blksz);
        lastBlock.b[ctxInternal->blksz]       = (uint8_t)0x80U;
        lastBlock.w[SHA_BLOCK_SIZE / 4U - 1U] = swap_bytes(8u * ctxInternal->fullMessageSize);
        sha_one_block(base, &lastBlock.b[0]);
    }
    else
    {
        if (ctxInternal->blksz < SHA_BLOCK_SIZE)
        {
            ctxInternal->blk.b[ctxInternal->blksz] = (uint8_t)0x80U;
            for (uint32_t i = ctxInternal->blksz + 1u; i < SHA_BLOCK_SIZE; i++)
            {
                ctxInternal->blk.b[i] = 0;
            }
        }
        else
        {
            lastBlock.b[0] = (uint8_t)0x80U;
        }

        sha_one_block(base, &ctxInternal->blk.b[0]);
        lastBlock.w[SHA_BLOCK_SIZE / 4U - 1U] = swap_bytes(8u * ctxInternal->fullMessageSize);
        sha_one_block(base, &lastBlock.b[0]);
    }
    /* poll wait for final digest */
    while (0U == (base->STATUS & SHA_STATUS_DIGEST_MASK))
    {
    }
    return kStatus_Success;
}

/*!
 * @brief Read DIGEST registers.
 *
 * This function copies DIGEST to output buffer.
 *
 * @param base SHA peripheral base address.
 * @param[out] output Output buffer.
 * @param Number of bytes to copy.
 * @return kStatus_Success.
 */
static void sha_get_digest(SHA_Type *base, uint8_t *output, size_t outputSize)
{
    uint32_t digest[8];

    for (int i = 0; i < 8; i++)
    {
        digest[i] = swap_bytes(base->DIGEST[i]);
    }

    if (outputSize > sizeof(digest))
    {
        outputSize = sizeof(digest);
    }
    (void)sha_memcpy(output, (const uint8_t *)digest, outputSize);
}

/*!
 * brief Initialize HASH context
 *
 * This function initializes new hash context.
 *
 * param base SHA peripheral base address
 * param[out] ctx Output hash context
 * param algo Underlaying algorithm to use for hash computation. Either SHA-1 or SHA-256.
 * return Status of initialization
 */
status_t SHA_Init(SHA_Type *base, sha_ctx_t *ctx, sha_algo_t algo)
{
    status_t status;

    sha_ctx_internal_t *ctxInternal;
    /* compile time check for the correct structure size */
    BUILD_ASSERT(sizeof(sha_ctx_t) >= sizeof(sha_ctx_internal_t), sha_ctx_t_size);
    uint32_t i;

    status = sha_check_input_args(base, ctx, algo);
    if (status != kStatus_Success)
    {
        return status;
    }

    /* set algorithm in context struct for later use */
    ctxInternal        = (sha_ctx_internal_t *)(uint32_t)ctx;
    ctxInternal->algo  = algo;
    ctxInternal->blksz = 0u;
    size_t j;
    j = (sizeof(ctxInternal->blk.w) / sizeof(ctxInternal->blk.w[0]));
    for (i = 0; i < j; i++)
    {
        ctxInternal->blk.w[0] = 0u;
    }
    ctxInternal->state           = kSHA_HashInit;
    ctxInternal->fullMessageSize = 0;
    ctxInternal->base            = base;
    return status;
}

/*!
 * brief Add data to current HASH
 *
 * Add data to current HASH. This can be called repeatedly with an arbitrary amount of data to be
 * hashed.
 *
 * param base SHA peripheral base address
 * param[in,out] ctx HASH context
 * param message Input message
 * param messageSize Size of input message in bytes
 * param manual 0 use nonblocking MEMADDR, MEMCRL (pseudo-DMA), 1 - manual load
 * return Status of the hash update operation
 */
status_t SHA_Update(SHA_Type *base, sha_ctx_t *ctx, const uint8_t *message, size_t messageSize, bool manual)
{
    bool isUpdateState;
    status_t status;
    sha_ctx_internal_t *ctxInternal;
    size_t blockSize;

    if (messageSize == 0U)
    {
        return kStatus_Success;
    }

    ctxInternal = (sha_ctx_internal_t *)(uint32_t)ctx;
    status      = sha_check_context(ctxInternal, message);
    if (kStatus_Success != status)
    {
        ctxInternal->state = kSHA_HashError;
        return status;
    }

    ctxInternal->fullMessageSize += messageSize;
    blockSize = SHA_BLOCK_SIZE;
    /* if we are still less than 64 bytes, keep only in context */
    if ((ctxInternal->blksz + messageSize) <= blockSize)
    {
        (void)sha_memcpy((&ctxInternal->blk.b[0]) + ctxInternal->blksz, message, messageSize);
        ctxInternal->blksz += messageSize;
        return status;
    }
    else
    {
        isUpdateState = ctxInternal->state == kSHA_HashUpdate;
        if (!isUpdateState)
        {
            /* start NEW hash */
            sha_engine_init(base, ctxInternal);
            ctxInternal->state = kSHA_HashUpdate;
        }
    }

#if defined(FSL_FEATURE_SHA_HAS_MEMADDR_DMA) && (FSL_FEATURE_SHA_HAS_MEMADDR_DMA > 0)
    /* Check if address is outisde of SRAMX or SRAM0, thus data must be loaded manually */
    if (kStatus_Success != sha_check_memory_boundry(message, messageSize) || manual)
    {
        /* process message data */
        status = sha_process_message_data(base, ctxInternal, message, messageSize);
    }
    /* If entirely contained in SRAMX or SRAM0, SHA engine will be set up as AHB bus master automatically
    load blocks of memory for hashing. */
    else
    {
        uint32_t num512BitBlocks = ctxInternal->fullMessageSize >> 6;

        /* If requested to hash 0 blocks this is an error */
        if (0U == num512BitBlocks)
        {
            ctxInternal->state = kSHA_HashError;
            return kStatus_Fail;
        }

        if (num512BitBlocks > MAX_HASH_CHUNK)
        {
            num512BitBlocks = MAX_HASH_CHUNK;
        }
        ctxInternal->blksz    = ctxInternal->fullMessageSize - (num512BitBlocks << 6);
        ctxInternal->pMessage = (uint8_t *)(uintptr_t)message + (num512BitBlocks << 6);

        /* Write address  and number of 512bit blocks */
        ctxInternal->base->MEMADDR = (uint32_t)message;

        /* Start the hash by setting the count */
        ctxInternal->base->MEMCTRL = 1U | ((num512BitBlocks & MAX_HASH_CHUNK) << 16);

        /* Enable IRQ on waiting and digest ready */
        ctxInternal->base->INTENSET = (SHA_STATUS_DIGEST_MASK | SHA_STATUS_ERROR_MASK);
        s_shaCtx                    = ctxInternal;
        NVIC_EnableIRQ(SHA_IRQn);
    }
#else  /* SHA engine does not have MEMADDR DMA, so data are processed manually */
    status = sha_process_message_data(base, ctxInternal, message, messageSize);
#endif /* defined(FSL_FEATURE_SHA_HAS_MEMADDR_DMA) && (FSL_FEATURE_SHA_HAS_MEMADDR_DMA > 0) */
    return status;
}

/*!
 * brief Finalize hashing
 *
 * Outputs the final hash and erases the context. SHA-1 or SHA-256 padding bits are automatically added by this
 * function.
 *
 * param base SHA peripheral base address
 * param[in,out] ctx HASH context
 * param[out] output Output hash data
 * param[in,out] outputSize On input, determines the size of bytes of the output array. On output, tells how many bytes
 * have been written to output.
 * return Status of the hash finish operation
 */
status_t SHA_Finish(SHA_Type *base, sha_ctx_t *ctx, uint8_t *output, size_t *outputSize)
{
    size_t algOutSize = 0;
    status_t status;
    sha_ctx_internal_t *ctxInternal;
    uint32_t *ctxW;
    uint32_t i;
    volatile sha_algo_state_t tempState;

    ctxInternal = (sha_ctx_internal_t *)(uint32_t)ctx;
    status      = sha_check_context(ctxInternal, output);
    if (kStatus_Success != status)
    {
        return status;
    }

    tempState = ctxInternal->state;
    if (tempState == kSHA_HashInit)
    {
        sha_engine_init(base, ctxInternal);
    }
    else
    {
        /* Wait for the hash to complete */
        tempState = ctxInternal->state;
        while (tempState != kSHA_HashDone)
        {
            if (tempState == kSHA_HashError)
            {
                return kStatus_Fail;
            }
            tempState = ctxInternal->state;
            __NOP();
        }
    }

    size_t outSize = 0u;

    /* compute algorithm output length */
    switch (ctxInternal->algo)
    {
        case kSHA_Sha1:
            outSize = (uint32_t)kSHA_OutLenSha1;
            break;
        case kSHA_Sha256:
            outSize = (uint32_t)kSHA_OutLenSha256;
            break;
        default:
            /* No valid length*/
            break;
    }
    algOutSize = outSize;

    /* flush message last incomplete block, if there is any, and add padding bits */
    status = sha_finalize(base, ctxInternal);

    if (outputSize != NULL)
    {
        if (algOutSize < *outputSize)
        {
            *outputSize = algOutSize;
        }
        else
        {
            algOutSize = *outputSize;
        }
    }

    sha_get_digest(base, &output[0], algOutSize);

    ctxW = (uint32_t *)(uint32_t)ctx;
    for (i = 0; i < SHA_CTX_SIZE; i++)
    {
        ctxW[i] = 0u;
    }
    return status;
}

void SHA_ClkInit(SHA_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* ungate clock */
    CLOCK_EnableClock(kCLOCK_Sha0);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

void SHA_ClkDeinit(SHA_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* gate clock */
    CLOCK_DisableClock(kCLOCK_Sha0);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

void SHA_DriverIRQHandler(void);
void SHA_DriverIRQHandler(void)
{
    sha_ctx_internal_t *ctxInternal = s_shaCtx;

    /* Record status */
    uint32_t status = ctxInternal->base->STATUS & (SHA_STATUS_DIGEST_MASK | SHA_STATUS_ERROR_MASK);

    /* If we need to setup for the next chunk */
    if ((0U != (ctxInternal->blksz >> 6)) && ((status & SHA_STATUS_ERROR_MASK) == 0U))
    {
        uint32_t num512BitBlocks = ctxInternal->blksz >> 6;

        /* send more blocks using AHB master */
        num512BitBlocks--;
        if (num512BitBlocks > MAX_HASH_CHUNK)
        {
            num512BitBlocks = MAX_HASH_CHUNK;
        }

        /* account for the number of blocks we are about to check */
        ctxInternal->blksz    = ((ctxInternal->blksz >> 6) - (num512BitBlocks + 1U)) << 6;
        ctxInternal->pMessage = (uint8_t *)ctxInternal->base->MEMADDR + ((num512BitBlocks + 1U) << 6);

        /* transfer one 512-bit block manually first to workaround the silicon bug - artf251591 */
        struct tmp
        {
            uint32_t data[8];
        } *src = (struct tmp *)ctxInternal->base->MEMADDR, *dst = (struct tmp *)(uintptr_t)&ctxInternal->base->INDATA;
        *dst = *src;
        src++;
        while (0U == (ctxInternal->base->STATUS & SHA_INTENSET_WAITING_MASK))
        {
        }
        *dst = *src;
        src++;

        /* if no more data, return, else post an AHB master transfer */
        if (num512BitBlocks == 0U)
        {
            return;
        }

        /* AHB master transfer */
        ctxInternal->base->MEMADDR = (uint32_t)src;

        /* set the next block size */
        ctxInternal->base->MEMCTRL = 1U | ((num512BitBlocks & MAX_HASH_CHUNK) << SHA_MEMCTRL_COUNT_SHIFT);

        /* Done setting up for the next block so exit */
        return;
    }

    /* copy last incomplete message bytes into internal block */
    (void)sha_memcpy(&ctxInternal->blk.b[0], ctxInternal->pMessage, ctxInternal->blksz);

    /* Disable SHA IRQ's and restore IRQ mask */
    if ((status & SHA_STATUS_ERROR_MASK) == 0U)
    {
        ctxInternal->state = kSHA_HashDone;
    }
    else
    {
        ctxInternal->state = kSHA_HashError;
    }

    ctxInternal->base->INTENCLR = (SHA_STATUS_DIGEST_MASK | SHA_STATUS_ERROR_MASK);
    NVIC_DisableIRQ(SHA_IRQn);
    SDK_ISR_EXIT_BARRIER;
}
