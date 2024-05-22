/*--------------------------------------------------------------------------*/
/* Copyright 2023 NXP                                                       */
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

/** @file  mcuxClHashModes_Internal.h
 *  @brief Definitions and declarations of the *INTERNAL* layer of the
 *         @ref mcuxClHashModes component
 */

#ifndef MCUXCLHASHMODES_INTERNAL_H_
#define MCUXCLHASHMODES_INTERNAL_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClCore_Platform.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslAnalysis.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClHash_Types.h>
#include <internal/mcuxClHash_Internal.h>
#include <internal/mcuxClHashModes_Internal_Memory.h>
#include <mcuxClEls_Hash.h>
#include <internal/mcuxClHashModes_Internal_els_sha2.h>
#include <internal/mcuxClHashModes_Core_els_sha2.h>

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************
 * CONSTANTS
 **********************************************/

#define MCUXCLHASHMODES_SHAKE_PHASE_INIT       (0UL) /* Initialization phase of Shake: buffer will be cleared */
#define MCUXCLHASHMODES_SHAKE_PHASE_ABSORB     (1UL) /* Absorb phase of Shake: don't clear any more, but also don't add padding yet */
#define MCUXCLHASHMODES_SHAKE_PHASE_SQUEEZE    (2UL) /* Squeeze phase of Shake: padding has been added, from now on only permute on the state */

/**********************************************
 * Type declarations
 **********************************************/

/**
 * @brief Internal Hash Algorithm structure
 *
 */
typedef struct mcuxClHashModes_Internal_AlgorithmDescriptor
{
  mcuxClHashModes_els_AlgoCore_t els_core;                       ///< ELS hash core function (access to ELS coprocessor)
  uint32_t protection_token_els_core;                           ///< Protection token value for the used core
  uint32_t rtfSize;                                             ///< Size of the Runtime Fingerprint used by the hash function; has to be set to zero when not supported
  mcuxClEls_HashOption_t hashOptions;
#ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
  mcuxClHashModes_AlgoDmaProtection_t dmaProtection;             ///< DMA protection function
  uint32_t protection_token_dma_protection;                     ///< Protection token value for the used DMA protection function
#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */
  uint32_t dummyValue;                                          ///< needed in the absense of any algorithm using internal algorithm properties
} mcuxClHashModes_Internal_AlgorithmDescriptor_t;
/**@}*/

/**********************************************
 * Function declarations
 **********************************************/

#define MCUXCLHASHMODES_SWITCH_4BYTE_ENDIANNESS(val)   \
        ((((val) & 0xFFu)       << 24)   \
        | (((val) & 0xFF00u)     << 8)   \
        | (((val) & 0xFF0000u)   >> 8)   \
        | (((val) & 0xFF000000u) >> 24))   ///< Macro to switch the endianness of a CPU word

#define MCUXCLHASHMODES_SWITCH_8BYTE_ENDIANNESS(val)      \
         ((((val) << 56u) & 0xFF00000000000000u) |  \
          (((val) << 40u) & 0x00FF000000000000u) |  \
          (((val) << 24u) & 0x0000FF0000000000u) |  \
          (((val) << 8u ) & 0x000000FF00000000u) |  \
          (((val) >> 8u ) & 0x00000000FF000000u) |  \
          (((val) >> 24u) & 0x0000000000FF0000u) |  \
          (((val) >> 40u) & 0x000000000000FF00u) |  \
          (((val) >> 56u) & 0x00000000000000FFu))


/**
 * @brief Function to switch endianness of arbitrary size words in a buffer
 *
 * This function switches the endianness of byteLen buffer consisting of wordLen words
 * pointed to by ptr
 * Only endianness of full words within the buffer with be switched.
 *
 * @param[in/out] ptr      Pointer to the buffer
 * @param[in]     byteLen  Byte length of buffer pointed to by ptr
 *
 * @return void
 */
static inline void mcuxClHashModes_internal_c_genericSwitchEndiannessOfBufferWords(uint32_t *ptr, uint32_t byteLen, uint32_t wordLen)
{
  if(sizeof(uint32_t) == wordLen)
  {
    for(uint32_t i = 0u; i < (byteLen / sizeof(uint32_t)); i++)
    {
        ptr[i] = MCUXCLHASHMODES_SWITCH_4BYTE_ENDIANNESS(ptr[i]);
    }
  }
  else if(sizeof(uint64_t) == wordLen)
  {
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_CASTING("Accessing 64 bit data with 32 bit alignment is supported on target platform")
    uint64_t * ptr64 = (uint64_t *)ptr;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_CASTING()
    for(uint32_t i = 0u; i < (byteLen / sizeof(uint64_t)); i++)
    {
        ptr64[i] = MCUXCLHASHMODES_SWITCH_8BYTE_ENDIANNESS(ptr64[i]);
    }
  }
  else
  {
    /* not supported */
  }
}

/**
 * @brief convert 128 bit number of bytes to number of bits
 */
static inline void mcuxClHashModes_processedLength_toBits(uint64_t *pLen128)
{
  pLen128[1] = (pLen128[1] << 3u) | (pLen128[0] >> 61u);
  pLen128[0] = pLen128[0] << 3u;
}



#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLHASHMODES_INTERNAL_H_ */
