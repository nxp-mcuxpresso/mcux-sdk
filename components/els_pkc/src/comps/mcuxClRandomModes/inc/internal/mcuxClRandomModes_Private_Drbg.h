/*--------------------------------------------------------------------------*/
/* Copyright 2021-2023 NXP                                                  */
/*                                                                          */
/* NXP Confidential. This software is owned or controlled by NXP and may    */
/* only be used strictly in accordance with the applicable license terms.   */
/* By expressly accepting such terms or by downloading, installing,         */
/* activating and/or otherwise using the software, you are agreeing that    */
/* you have read, and that you agree to comply with and are bound by, such  */
/* license terms. If you do not agree to be bound by the applicable license */
/* terms, then you may not retain, install, activate or otherwise use the   */
/* software.                                                                */
/*--------------------------------------------------------------------------*/

#ifndef MCUXCLRANDOMMODES_PRIVATE_DRBG_H_
#define MCUXCLRANDOMMODES_PRIVATE_DRBG_H_

#include <mcuxClConfig.h> // Exported features flags header

#include <mcuxClSession.h>
#include <mcuxClRandom_Types.h>


#ifdef __cplusplus
extern "C" {
#endif

#define MCUXCLRANDOMMODES_SELFTEST_RANDOMDATALENGTH (64u)

/*
 * Takes a byte size and returns a number of words
 */
#define MCUXCLRANDOMMODES_ROUNDED_UP_CPU_WORDSIZE(bytesize) \
    (((bytesize) + sizeof(uint32_t) - 1U ) / (sizeof(uint32_t)))

/*
 * Takes a byte size and returns the next largest multiple of MCUXCLAES_BLOCK_SIZE
 */
#define MCUXCLRANDOMMODES_ROUND_UP_TO_AES_BLOCKSIZE(bytesize) \
    ((((bytesize) + MCUXCLAES_BLOCK_SIZE - 1U) / MCUXCLAES_BLOCK_SIZE) * MCUXCLAES_BLOCK_SIZE)

/**
 * @brief Defines to specify which mode a DRBG is operated in
 */
#define MCUXCLRANDOMMODES_NORMALMODE  (0xa5a5a5a5u)
#define MCUXCLRANDOMMODES_TESTMODE    (0x5a5a5a5au)
#define MCUXCLRANDOMMODES_ELSMODE     (0xd3d3d3d3u)
#define MCUXCLRANDOMMODES_PATCHMODE   (0x3d3d3d3du)

/* Shared generic internal structure of a random context used by DRBGs:
 *   - reseedCounter    This value is used to count the number of generateAlgorithm function calls since the last reseedAlgorithm call.
 *   - reseedSeedOffset For PTG.3 in test mode, the reseedSeedOffset counts the number of entropy input bytes already drawn from the entropy input buffer
 *                      for reseeding during an mcuxClRandom_generate call. Otherwise it's set to zero.
 *                      This value is not taken into account during reseeding in normal mode. It is only used to determine the right offset
 *                      in the entropy buffer during mcuxClRandom_generate calls for PTG.3 in test mode. */
#define MCUXCLRANDOMMODES_CONTEXT_DRBG_ENTRIES  \
        uint64_t reseedCounter;  \
        uint32_t reseedSeedOffset;

typedef struct
{
    MCUXCLRANDOMMODES_CONTEXT_DRBG_ENTRIES
} mcuxClRandomModes_Context_Generic_t;

/* Signatures for internal functions */
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClRandomModes_instantiateAlgorithm_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) (* mcuxClRandomModes_instantiateAlgorithm_t)(
        mcuxClSession_Handle_t pSession,
        uint8_t *pEntropyInput
));

MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClRandomModes_reseedAlgorithm_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) (* mcuxClRandomModes_reseedAlgorithm_t)(
        mcuxClSession_Handle_t pSession,
        uint8_t *pEntropyInput
));

MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClRandomModes_generateAlgorithm_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) (* mcuxClRandomModes_generateAlgorithm_t)(
        mcuxClSession_Handle_t pSession,
        uint8_t *pOut,
        uint32_t outLength
));

MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClRandomModes_selftestAlgorithm_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) (* mcuxClRandomModes_selftestAlgorithm_t)(
        mcuxClSession_Handle_t pSession,
        mcuxClRandom_Context_t testCtx,
        mcuxClRandom_ModeDescriptor_t *mode
));

typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) (* mcuxClRandomModes_generatePrHandler_t)(
        mcuxClSession_Handle_t pSession
);

typedef struct
{
    /* Function pointers for DRBG algorithms */
    mcuxClRandomModes_instantiateAlgorithm_t instantiateAlgorithm;  ///< DRBG instantiation algorithm depending on the chosen DRBG variant
    mcuxClRandomModes_reseedAlgorithm_t reseedAlgorithm;            ///< DRBG reseeding algorithm depending on the chosen DRBG variant
    mcuxClRandomModes_generateAlgorithm_t generateAlgorithm;        ///< DRBG random number generation algorithm depending on the chosen DRBG variant
    mcuxClRandomModes_selftestAlgorithm_t selftestAlgorithm;        ///< DRBG self-test handler depending on the chosen DRBG variant

    /* Protection tokens of DRBG algorithm function pointers */
    uint32_t protectionTokenInstantiateAlgorithm;             ///< Protection token of DRBG instantiate algorithm
    uint32_t protectionTokenReseedAlgorithm;                  ///< Protection token of DRBG reseed algorithm
    uint32_t protectionTokenGenerateAlgorithm;                ///< Protection token of DRBG generate algorithm
    uint32_t protectionTokenSelftestAlgorithm;                ///< Protection token of DRBG generate algorithm
} mcuxClRandomModes_DrbgAlgorithmsDescriptor_t;

typedef struct
{
    uint64_t reseedInterval;           ///< reseed interval of chosen DRBG variant
    uint16_t seedLen;                  ///< seedLen parameter defined in NIST SP 800-90A
    uint16_t initSeedSize;             ///< Size of entropy input used for instantiating the DRBG
    uint16_t reseedSeedSize;           ///< Size of entropy input used for reseeding the DRBG
} mcuxClRandomModes_DrbgVariantDescriptor_t;

typedef struct
{
    const mcuxClRandomModes_DrbgAlgorithmsDescriptor_t *pDrbgAlgorithms;
    const mcuxClRandomModes_DrbgVariantDescriptor_t *pDrbgVariant;
    const uint32_t * const *pDrbgTestVectors;
    uint32_t continuousReseedInterval;
} mcuxClRandomModes_DrbgModeDescriptor_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLRANDOMMODES_PRIVATE_DRBG_H_ */
