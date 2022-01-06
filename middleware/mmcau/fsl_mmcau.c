/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2017,2021, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_mmcau.h"
#include "cau_api.h"

#define MMCAU_AES_BLOCK_SIZE (16)
#define MMCAU_DES_BLOCK_SIZE (8)

#define MMCAU_MD5_STATE_SIZE    (16)
#define MMCAU_SHA1_STATE_SIZE   (20)
#define MMCAU_SHA256_STATE_SIZE (32)

/* these are maximum for CAU API has functions. HAST_STATE shall be set to maximum of MD5_STATE,SHA1_STATE and
 * SHA256_STATE */
#define MMCAU_HASH_STATE_SIZE (32)
#define MMCAU_HASH_BLOCK_SIZE (64)

/* typedef for pointer to CAU API functions */
typedef void (*cau_hash_api_t)(const uint8_t *msgData, const int numBlocks, uint32_t *hashState);
typedef void (*cau_hash_md5_api_t)(const uint8_t *msgData, const int numBlocks, uint8_t *hashState);

/*******************************************************************************
 * Code
 ******************************************************************************/
static void mmcau_memcpy(void *dst, const void *src, size_t size)
{
    register uint8_t *to         = dst;
    register const uint8_t *from = src;
    while (size != 0U)
    {
        *to = *from;
        size--;
        to++;
        from++;
    }
}

/* check if in pointer is aligned. if not, copy in to inAlign. return pointer to aligned data. */
static const void *mmcau_align_const(const void *in, void *inAlign, size_t size)
{
    const void *inWork  = in;
    const uint32_t *src = (const uint32_t *)in;
    /* if one or two least significant bits in the address are set, the address is unaligned */
    if (0U != ((uint32_t)src & 0x3u))
    {
        mmcau_memcpy(inAlign, in, size);
        inWork = inAlign;
    }

    return inWork;
}

/* check if out pointer is aligned. if not, set bool variable to notify caller. return pointer to aligned data. */
static void *mmcau_align(void *out, void *outAlign, bool *copyOut)
{
    void *outWork;
    uint32_t *dst = (uint32_t *)out;
    /* if one or two least significant bits in the address are set, the address is unaligned */
    if (0U != ((uint32_t)dst & 0x3u))
    {
        outWork  = outAlign;
        *copyOut = true;
    }
    else
    {
        outWork  = out;
        *copyOut = false;
    }

    return outWork;
}

/* common function for AES process. "encrypt" argument selects between en-/de-cryption */
static status_t mmcau_AesCrypt(const uint8_t *in, const uint8_t *keySch, uint32_t aesRounds, uint8_t *out, bool encrypt)
{
    status_t status;

    /* check validity of input arguments */
    if (((aesRounds != 10u) && (aesRounds != 12u) && (aesRounds != 14u)) || (NULL == in) || (NULL == out) ||
        (NULL == keySch))
    {
        status = kStatus_InvalidArgument;
    }
    else
    {
        uint8_t inAlign[MMCAU_AES_BLOCK_SIZE];  /* 16 bytes aligned input block */
        uint8_t outAlign[MMCAU_AES_BLOCK_SIZE]; /* 16 bytes aligned output block */
        uint32_t keySchAlign[60];               /* max 60 longwords in case of 32 bytes AES key */
        size_t keySchSize = 0;
        const uint8_t *keySchWork;
        const uint8_t *inWork;
        uint8_t *outWork;
        bool copyOut;

        /* compute keySchSize in bytes per CAU API documentation */
        if (aesRounds == 10u)
        {
            keySchSize = 44u * sizeof(uint32_t);
        }
        else if (aesRounds == 12u)
        {
            keySchSize = 52u * sizeof(uint32_t);
        }
        else /* aesRounds = 14u */
        {
            keySchSize = 60u * sizeof(uint32_t);
        }

        /* align pointers */
        inWork     = mmcau_align_const(in, inAlign, MMCAU_AES_BLOCK_SIZE);
        keySchWork = mmcau_align_const(keySch, keySchAlign, keySchSize);
        outWork    = mmcau_align(out, outAlign, &copyOut);

        /* call actual CAU API */
        if (encrypt)
        {
            cau_aes_encrypt(inWork, keySchWork, (int)aesRounds, outWork);
        }
        else
        {
            cau_aes_decrypt(inWork, keySchWork, (int)aesRounds, outWork);
        }
        /* copy to unaligned out pointer */
        if (copyOut)
        {
            mmcau_memcpy(out, outAlign, MMCAU_AES_BLOCK_SIZE);
        }

        status = kStatus_Success;
    }
    return status;
}

/* common function for DES process. "encrypt" argument selects between en-/de-cryption */
static status_t mmcau_DesCrypt(const uint8_t *in, const uint8_t *key, uint8_t *out, bool encrypt)
{
    status_t status;

    if ((in != NULL) && (key != NULL) && (out != NULL))
    {
        uint8_t keyAlign[MMCAU_DES_BLOCK_SIZE]; /* 8 bytes key size aligned */
        uint8_t inAlign[MMCAU_DES_BLOCK_SIZE];  /* 8 bytes input block aligned */
        uint8_t outAlign[MMCAU_DES_BLOCK_SIZE]; /* 8 bytes output block aligned */
        const uint8_t *inWork;
        const uint8_t *keyWork;
        uint8_t *outWork;
        bool copyOut;

        /* align pointers */
        inWork  = mmcau_align_const(in, inAlign, MMCAU_DES_BLOCK_SIZE);
        keyWork = mmcau_align_const(key, keyAlign, MMCAU_DES_BLOCK_SIZE);
        outWork = mmcau_align(out, outAlign, &copyOut);

        /* call CAU API */
        if (encrypt)
        {
            cau_des_encrypt(inWork, keyWork, outWork);
        }
        else
        {
            cau_des_decrypt(inWork, keyWork, outWork);
        }

        if (copyOut)
        {
            mmcau_memcpy(out, outAlign, MMCAU_DES_BLOCK_SIZE);
        }
        status = kStatus_Success;
    }
    else
    {
        status = kStatus_InvalidArgument;
    }

    return status;
}

static status_t mmcau_hash_API(
    cau_hash_api_t cauFunc, const uint8_t *msgData, uint32_t numBlocks, void *hashState, size_t stateSize)
{
    status_t status;

    if ((msgData != NULL) && (hashState != NULL) && (numBlocks != 0U))
    {
        const uint8_t *msgDataWork;
        void *hashStateWork;
        uint8_t msgDataAlign[MMCAU_HASH_BLOCK_SIZE];
        uint8_t hashStateAlign[MMCAU_HASH_STATE_SIZE];
        bool copyInOut;

        /* get aligned pointers */
        msgDataWork   = mmcau_align_const(msgData, msgDataAlign, MMCAU_HASH_BLOCK_SIZE);
        hashStateWork = mmcau_align(hashState, hashStateAlign, &copyInOut);
        if (copyInOut)
        {
            mmcau_memcpy(hashStateAlign, hashState, stateSize);
        }
        /* CAU API */
        cauFunc(msgDataWork, numBlocks, hashStateWork);
        /* copy result to misaligned address */
        if (copyInOut)
        {
            mmcau_memcpy(hashState, hashStateAlign, stateSize);
        }
        status = kStatus_Success;
    }
    else
    {
        status = kStatus_InvalidArgument;
    }
    return status;
}

static status_t mmcau_hash_MD5API(
    cau_hash_md5_api_t cauFunc, const uint8_t *msgData, uint32_t numBlocks, void *hashState, size_t stateSize)
{
    status_t status;

    if ((msgData != NULL) && (hashState != NULL) && (numBlocks != 0U))
    {
        const uint8_t *msgDataWork;
        void *hashStateWork;
        uint8_t msgDataAlign[MMCAU_HASH_BLOCK_SIZE];
        uint8_t hashStateAlign[MMCAU_HASH_STATE_SIZE];
        bool copyInOut;

        /* get aligned pointers */
        msgDataWork   = mmcau_align_const(msgData, msgDataAlign, MMCAU_HASH_BLOCK_SIZE);
        hashStateWork = mmcau_align(hashState, hashStateAlign, &copyInOut);
        if (copyInOut)
        {
            mmcau_memcpy(hashStateAlign, hashState, stateSize);
        }
        /* CAU API */
        cauFunc(msgDataWork, numBlocks, hashStateWork);
        /* copy result to misaligned address */
        if (copyInOut)
        {
            mmcau_memcpy(hashState, hashStateAlign, stateSize);
        }
        status = kStatus_Success;
    }
    else
    {
        status = kStatus_InvalidArgument;
    }
    return status;
}

status_t MMCAU_AES_SetKey(const uint8_t *key, const size_t keySize, uint8_t *keySch)
{
    status_t status;

    /* check validity of input arguments */
    if (((keySize != 16u) && (keySize != 24u) && (keySize != 32u)) || (NULL == key) || (NULL == keySch))
    {
        status = kStatus_InvalidArgument;
    }
    else
    {
        uint8_t keyAlign[32]     = {0}; /* max 32 bytes key supported by CAU lib */
        uint32_t keySchAlign[60] = {0}; /* max 60 longwords in case of 32 bytes AES key */
        const uint8_t *keyWork;         /* aligned CAU lib input address argument */
        uint8_t *keySchWork;            /* aligned CAU lib output address argument */
        bool copyOut;
        size_t sizeOut = 0;

        keyWork    = mmcau_align_const(key, keyAlign, sizeof(keyAlign));
        keySchWork = mmcau_align(keySch, keySchAlign, &copyOut);

        /* call CAU lib API with all addresses aligned */
        cau_aes_set_key(keyWork, ((int)keySize * 8), keySchWork);

        /* in case we have aligned output to local, copy the result out */
        if (copyOut)
        {
            if (keySize == 16u)
            {
                sizeOut = 44u * sizeof(uint32_t);
            }
            else if (keySize == 24u)
            {
                sizeOut = 52u * sizeof(uint32_t);
            }
            else /* keySize = 32u */
            {
                sizeOut = 60u * sizeof(uint32_t);
            }

            mmcau_memcpy(keySch, keySchAlign, sizeOut);
        }

        status = kStatus_Success;
    }

    return status;
}

status_t MMCAU_AES_EncryptEcb(const uint8_t *in, const uint8_t *keySch, uint32_t aesRounds, uint8_t *out)
{
    return mmcau_AesCrypt(in, keySch, aesRounds, out, true /* true for encryption */);
}

status_t MMCAU_AES_DecryptEcb(const uint8_t *in, const uint8_t *keySch, uint32_t aesRounds, uint8_t *out)
{
    return mmcau_AesCrypt(in, keySch, aesRounds, out, false /* false for decryption */);
}

status_t MMCAU_DES_ChkParity(const uint8_t *key)
{
    status_t status;

    if (key != NULL)
    {
        uint8_t keyAlign[8]; /* 8 bytes key size aligned */
        const uint8_t *keyWork;

        /* align key[] */
        keyWork = mmcau_align_const(key, keyAlign, sizeof(keyAlign));

        /* call CAU API */
        if (0 == cau_des_chk_parity(keyWork))
        {
            status = kStatus_Success;
        }
        else
        {
            status = kStatus_Fail;
        }
    }
    else
    {
        status = kStatus_InvalidArgument;
    }

    return status;
}

status_t MMCAU_DES_EncryptEcb(const uint8_t *in, const uint8_t *key, uint8_t *out)
{
    return mmcau_DesCrypt(in, key, out, true /* 1 for encryption */);
}

status_t MMCAU_DES_DecryptEcb(const uint8_t *in, const uint8_t *key, uint8_t *out)
{
    return mmcau_DesCrypt(in, key, out, false /* 0 for decryption */);
}

/* cau_md5_initialize_output() */
status_t MMCAU_MD5_InitializeOutput(uint32_t *md5State)
{
    status_t status;

    if (md5State != NULL)
    {
        uint8_t hashStateAlign[MMCAU_HASH_STATE_SIZE];
        void *hashStateWork;
        bool copyInOut;
        /* align pointer */
        hashStateWork = mmcau_align(md5State, hashStateAlign, &copyInOut);
        if (copyInOut)
        {
            mmcau_memcpy(hashStateAlign, md5State, MMCAU_MD5_STATE_SIZE);
        }
        /* CAU API */
        cau_md5_initialize_output(hashStateWork);
        /* copy result to unaligned pointer */
        if (copyInOut)
        {
            mmcau_memcpy(md5State, hashStateAlign, MMCAU_MD5_STATE_SIZE);
        }
        status = kStatus_Success;
    }
    else
    {
        status = kStatus_InvalidArgument;
    }
    return status;
}

/* cau_md5_hash_n */
status_t MMCAU_MD5_HashN(const uint8_t *msgData, uint32_t numBlocks, uint32_t *md5State)
{
    return mmcau_hash_MD5API((cau_hash_md5_api_t)cau_md5_hash_n, msgData, numBlocks, md5State, MMCAU_MD5_STATE_SIZE);
}

/* cau_md5_update */
status_t MMCAU_MD5_Update(const uint8_t *msgData, uint32_t numBlocks, uint32_t *md5State)
{
    return mmcau_hash_MD5API((cau_hash_md5_api_t)cau_md5_update, msgData, numBlocks, md5State, MMCAU_MD5_STATE_SIZE);
}

/* cau_sha1_initialize_output */
status_t MMCAU_SHA1_InitializeOutput(uint32_t *sha1State)
{
    status_t status;

    if (sha1State != NULL)
    {
        uint8_t hashStateAlign[MMCAU_HASH_STATE_SIZE];
        void *hashStateWork;
        bool copyInOut;
        /* align pointer */
        hashStateWork = mmcau_align(sha1State, hashStateAlign, &copyInOut);
        if (copyInOut)
        {
            mmcau_memcpy(hashStateAlign, sha1State, MMCAU_SHA1_STATE_SIZE);
        }
        /* CAU API */
        cau_sha1_initialize_output(hashStateWork);
        /* copy result to unaligned pointer */
        if (copyInOut)
        {
            mmcau_memcpy(sha1State, hashStateAlign, MMCAU_SHA1_STATE_SIZE);
        }
        status = kStatus_Success;
    }
    else
    {
        status = kStatus_InvalidArgument;
    }
    return status;
}

/* cau_sha1_hash_n */
status_t MMCAU_SHA1_HashN(const uint8_t *msgData, uint32_t numBlocks, uint32_t *sha1State)
{
    return mmcau_hash_API((cau_hash_api_t)cau_sha1_hash_n, msgData, numBlocks, sha1State, MMCAU_SHA1_STATE_SIZE);
}

/* cau_sha1_update */
status_t MMCAU_SHA1_Update(const uint8_t *msgData, uint32_t numBlocks, uint32_t *sha1State)
{
    return mmcau_hash_API((cau_hash_api_t)cau_sha1_update, msgData, numBlocks, sha1State, MMCAU_SHA1_STATE_SIZE);
}

/* cau_sha256_initialize_output(). not this function has different return value (int) that the other two (void) */
status_t MMCAU_SHA256_InitializeOutput(uint32_t *sha256State)
{
    status_t status;
    int ret;

    if (sha256State != NULL)
    {
        uint8_t hashStateAlign[MMCAU_HASH_STATE_SIZE];
        void *hashStateWork;
        bool copyInOut;
        /* align pointer */
        hashStateWork = mmcau_align(sha256State, hashStateAlign, &copyInOut);
        if (copyInOut)
        {
            mmcau_memcpy(hashStateAlign, sha256State, MMCAU_SHA256_STATE_SIZE);
        }
        /* CAU API */
        ret = cau_sha256_initialize_output(hashStateWork);
        /* copy result to unaligned pointer */
        if (copyInOut)
        {
            mmcau_memcpy(sha256State, hashStateAlign, MMCAU_SHA256_STATE_SIZE);
        }
        if (ret == 0)
        {
            status = kStatus_Success;
        }
        else
        {
            status = kStatus_Fail;
        }
    }
    else
    {
        status = kStatus_InvalidArgument;
    }
    return status;
}

/* cau_sha256_hash_n */
status_t MMCAU_SHA256_HashN(const uint8_t *input, uint32_t numBlocks, uint32_t *sha256State)
{
    return mmcau_hash_API((cau_hash_api_t)cau_sha256_hash_n, input, numBlocks, sha256State, MMCAU_SHA256_STATE_SIZE);
}

/* cau_sha256_update */
status_t MMCAU_SHA256_Update(const uint8_t *input, uint32_t numBlocks, uint32_t *sha256State)
{
    return mmcau_hash_API((cau_hash_api_t)cau_sha256_update, input, numBlocks, sha256State, MMCAU_SHA256_STATE_SIZE);
}
